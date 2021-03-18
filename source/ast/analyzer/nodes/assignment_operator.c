#include "kefir/ast/analyzer/nodes.h"
#include "kefir/ast/analyzer/analyzer.h"
#include "kefir/ast/type_conv.h"
#include "kefir/core/util.h"
#include "kefir/core/error.h"

static kefir_result_t validate_simple_assignment(struct kefir_mem *mem,
                                               const struct kefir_ast_context *context,
                                               const struct kefir_ast_assignment_operator *node) {
    const struct kefir_ast_type *target_type = KEFIR_AST_TYPE_CONV_EXPRESSION_ALL(
            mem, context->type_bundle, node->target->properties.type);
    const struct kefir_ast_type *value_type = KEFIR_AST_TYPE_CONV_EXPRESSION_ALL(
            mem, context->type_bundle, node->value->properties.type);
    if (KEFIR_AST_TYPE_IS_ARITHMETIC_TYPE(target_type)) {
        if (target_type->tag != KEFIR_AST_TYPE_SCALAR_BOOL ||
            value_type->tag != KEFIR_AST_TYPE_SCALAR_POINTER) {
            REQUIRE(KEFIR_AST_TYPE_IS_ARITHMETIC_TYPE(value_type),
                KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Right assignment operand shall be arithmetic type"));
        }
    } else if (target_type->tag == KEFIR_AST_TYPE_STRUCTURE ||
        target_type->tag == KEFIR_AST_TYPE_UNION) {
        REQUIRE(KEFIR_AST_TYPE_COMPATIBLE(context->type_traits, target_type, value_type),
            KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Both assignment operands shall be compatible"));
    } else if (target_type->tag == KEFIR_AST_TYPE_SCALAR_POINTER &&
        value_type->tag == KEFIR_AST_TYPE_SCALAR_POINTER) {
        struct kefir_ast_type_qualification target_qualification, value_qualification;
        const struct kefir_ast_type *target_underlying = kefir_ast_unqualified_type(target_type->referenced_type);
        const struct kefir_ast_type *value_underlying = kefir_ast_unqualified_type(value_type->referenced_type);
        REQUIRE_OK(kefir_ast_type_retrieve_qualifications(&target_qualification, target_type->referenced_type));
        REQUIRE_OK(kefir_ast_type_retrieve_qualifications(&value_qualification, value_type->referenced_type));

        if (target_underlying->tag != KEFIR_AST_TYPE_VOID && value_underlying->tag != KEFIR_AST_TYPE_VOID) {
            REQUIRE(KEFIR_AST_TYPE_COMPATIBLE(context->type_traits, target_underlying, value_underlying),
                KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Both assignment operands shall be pointers to compatible types"));
        }
        REQUIRE((!value_qualification.constant || target_qualification.constant) &&
            (!value_qualification.restricted || target_qualification.restricted) &&
            (!value_qualification.volatile_type || target_qualification.volatile_type),
            KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Left assignment operand shall point to the type with all qualifications from right"));
    } else {
        REQUIRE(target_type->tag == KEFIR_AST_TYPE_SCALAR_POINTER,
            KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Left assignment operand shall be a pointer"));
        REQUIRE(KEFIR_AST_TYPE_IS_INTEGRAL_TYPE(value_type) && node->value->properties.expression_props.constant_expression,
            KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Right assignment operand shall be NULL pointer"));
    }
    return KEFIR_OK;
}

static kefir_result_t validate_compound_assignment(struct kefir_mem *mem,
                                                 const struct kefir_ast_context *context,
                                                 const struct kefir_ast_assignment_operator *node) {
    const struct kefir_ast_type *target_type = KEFIR_AST_TYPE_CONV_EXPRESSION_ALL(
            mem, context->type_bundle, node->target->properties.type);
    const struct kefir_ast_type *value_type = KEFIR_AST_TYPE_CONV_EXPRESSION_ALL(
            mem, context->type_bundle, node->value->properties.type);
    switch (node->operation) {
        case KEFIR_AST_ASSIGNMENT_MULTIPLY:
        case KEFIR_AST_ASSIGNMENT_DIVIDE:
            REQUIRE(KEFIR_AST_TYPE_IS_ARITHMETIC_TYPE(target_type) &&
                KEFIR_AST_TYPE_IS_ARITHMETIC_TYPE(value_type),
                KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Both assignment operands shall have arithmetic types"));
            break;

        case KEFIR_AST_ASSIGNMENT_MODULO:
        case KEFIR_AST_ASSIGNMENT_SHIFT_LEFT:
        case KEFIR_AST_ASSIGNMENT_SHIFT_RIGHT:
        case KEFIR_AST_ASSIGNMENT_BITWISE_AND:
        case KEFIR_AST_ASSIGNMENT_BITWISE_OR:
        case KEFIR_AST_ASSIGNMENT_BITWISE_XOR:
            REQUIRE(KEFIR_AST_TYPE_IS_INTEGRAL_TYPE(target_type) &&
                KEFIR_AST_TYPE_IS_INTEGRAL_TYPE(value_type),
                KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Both assignment operands shall have integral types"));
            break;

        case KEFIR_AST_ASSIGNMENT_ADD:
        case KEFIR_AST_ASSIGNMENT_SUBTRACT:
            if (target_type->tag == KEFIR_AST_TYPE_SCALAR_POINTER) {
                REQUIRE(!KEFIR_AST_TYPE_IS_INCOMPLETE(kefir_ast_unqualified_type(target_type->referenced_type)),
                    KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Left assignment operand shall be a pointer to complete type"));
                REQUIRE(KEFIR_AST_TYPE_IS_INTEGRAL_TYPE(value_type),
                    KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Right assignment operand shall have integral type"));
            } else {
                REQUIRE(KEFIR_AST_TYPE_IS_ARITHMETIC_TYPE(target_type) &&
                    KEFIR_AST_TYPE_IS_ARITHMETIC_TYPE(value_type),
                    KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Both assignment operands shall be arithmetic types"));
            }
            break;

        case KEFIR_AST_ASSIGNMENT_SIMPLE:
            return KEFIR_SET_ERROR(KEFIR_INTERNAL_ERROR, "Unexpected assignment type");
    }
    return KEFIR_OK;
}

kefir_result_t kefir_ast_analyze_assignment_operator_node(struct kefir_mem *mem,
                                                      const struct kefir_ast_context *context,
                                                      const struct kefir_ast_assignment_operator *node,
                                                      struct kefir_ast_node_base *base) {
    UNUSED(mem);
    UNUSED(context);
    REQUIRE(node != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid AST constant"));
    REQUIRE(base != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid AST base node"));

    REQUIRE_OK(kefir_ast_analyze_node(mem, context, node->target));
    REQUIRE_OK(kefir_ast_analyze_node(mem, context, node->value));

    REQUIRE(node->target->properties.category == KEFIR_AST_NODE_CATEGORY_EXPRESSION,
        KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Both assignment operands shall be expressions"));
    REQUIRE(node->value->properties.category == KEFIR_AST_NODE_CATEGORY_EXPRESSION,
        KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Both assignment operands shall be expressions"));

    REQUIRE(node->target->properties.expression_props.lvalue,
        KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected non-const lvalue as assignment left operand"));
    struct kefir_ast_type_qualification target_qualifications;
    REQUIRE_OK(kefir_ast_type_retrieve_qualifications(&target_qualifications, node->target->properties.type));
    REQUIRE(!target_qualifications.constant,
        KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected non-const lvalue as assignment left operand"));

    switch (node->operation) {
        case KEFIR_AST_ASSIGNMENT_SIMPLE:
            REQUIRE_OK(validate_simple_assignment(mem, context, node));
            break;
        
        default:
            REQUIRE_OK(validate_compound_assignment(mem, context, node));
            break;
    }

    REQUIRE_OK(kefir_ast_node_properties_init(&base->properties));
    base->properties.category = KEFIR_AST_NODE_CATEGORY_EXPRESSION;
    base->properties.type = KEFIR_AST_TYPE_CONV_EXPRESSION_ALL(mem, context->type_bundle, node->target->properties.type);
    return KEFIR_OK;
}