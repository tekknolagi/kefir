#include "kefir/parser/rule_helpers.h"
#include "kefir/parser/builder.h"

static kefir_result_t scan_subscript(struct kefir_mem *mem, struct kefir_parser_ast_builder *builder) {
    REQUIRE_OK(PARSER_SHIFT(builder->parser));
    REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, kefir_parser_apply_rule_expression, NULL));
    REQUIRE(PARSER_TOKEN_IS_PUNCTUATOR(builder->parser, 0, KEFIR_PUNCTUATOR_RIGHT_BRACKET),
            KEFIR_SET_ERROR(KEFIR_SYNTAX_ERROR, "Expected right bracket"));
    REQUIRE_OK(PARSER_SHIFT(builder->parser));
    return KEFIR_OK;
}

static kefir_result_t scan_argument_list(struct kefir_mem *mem, struct kefir_parser_ast_builder *builder) {
    REQUIRE_OK(PARSER_SHIFT(builder->parser));
    while (!PARSER_TOKEN_IS_PUNCTUATOR(builder->parser, 0, KEFIR_PUNCTUATOR_RIGHT_PARENTHESE)) {
        REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, kefir_parser_apply_rule_assignment_expression, NULL));
        REQUIRE_OK(kefir_parser_ast_builder_function_call_append(mem, builder));

        if (PARSER_TOKEN_IS_PUNCTUATOR(builder->parser, 0, KEFIR_PUNCTUATOR_COMMA)) {
            REQUIRE_OK(PARSER_SHIFT(builder->parser));
        } else {
            REQUIRE(PARSER_TOKEN_IS_PUNCTUATOR(builder->parser, 0, KEFIR_PUNCTUATOR_RIGHT_PARENTHESE),
                    KEFIR_SET_ERROR(KEFIR_SYNTAX_ERROR, "Expected either comma, or right parenthese"));
        }
    }
    REQUIRE_OK(PARSER_SHIFT(builder->parser));
    return KEFIR_OK;
}

static kefir_result_t scan_member(struct kefir_mem *mem, struct kefir_parser_ast_builder *builder) {
    kefir_bool_t direct = PARSER_TOKEN_IS_PUNCTUATOR(builder->parser, 0, KEFIR_PUNCTUATOR_DOT);
    REQUIRE_OK(PARSER_SHIFT(builder->parser));
    REQUIRE(PARSER_TOKEN_IS_IDENTIFIER(builder->parser, 0), KEFIR_SET_ERROR(KEFIR_SYNTAX_ERROR, "Expected identifier"));
    const struct kefir_token *token = PARSER_CURSOR(builder->parser, 0);
    REQUIRE_OK(PARSER_SHIFT(builder->parser));
    REQUIRE_OK(kefir_parser_ast_builder_struct_member(mem, builder, direct, token->identifier));
    return KEFIR_OK;
}

static kefir_result_t scan_postfixes(struct kefir_mem *mem, struct kefir_parser_ast_builder *builder) {
    struct kefir_parser *parser = builder->parser;
    kefir_bool_t scan_postfix = true;

    REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, kefir_parser_apply_rule_primary_expression, NULL));
    do {
        if (PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_LEFT_BRACKET)) {
            REQUIRE_OK(scan_subscript(mem, builder));
            REQUIRE_OK(kefir_parser_ast_builder_array_subscript(mem, builder));
        } else if (PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_LEFT_PARENTHESE)) {
            REQUIRE_OK(kefir_parser_ast_builder_function_call(mem, builder));
            REQUIRE_OK(scan_argument_list(mem, builder));
        } else if (PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_DOT) ||
                   PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_RIGHT_ARROW)) {
            REQUIRE_OK(scan_member(mem, builder));
        } else if (PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_PLUS_PLUS)) {
            REQUIRE_OK(PARSER_SHIFT(parser));
            REQUIRE_OK(kefir_parser_ast_builder_unary_operation(mem, builder, KEFIR_AST_OPERATION_POSTFIX_INCREMENT));
        } else if (PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_MINUS_MINUS)) {
            REQUIRE_OK(PARSER_SHIFT(parser));
            REQUIRE_OK(kefir_parser_ast_builder_unary_operation(mem, builder, KEFIR_AST_OPERATION_POSTFIX_DECREMENT));
        } else {
            scan_postfix = false;
        }
    } while (scan_postfix);
    return KEFIR_OK;
}

static kefir_result_t builder_callback(struct kefir_mem *mem, struct kefir_parser_ast_builder *builder, void *payload) {
    UNUSED(payload);
    REQUIRE(mem != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid memory allocator"));
    REQUIRE(builder != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid parser AST builder"));

    kefir_result_t res = kefir_parser_ast_builder_scan(mem, builder, kefir_parser_apply_rule_compound_literal, NULL);
    if (res == KEFIR_NO_MATCH) {
        res = scan_postfixes(mem, builder);
    }
    REQUIRE_OK(res);
    return KEFIR_OK;
}

kefir_result_t kefir_parser_apply_rule_postfix_expression(struct kefir_mem *mem, struct kefir_parser *parser,
                                                          struct kefir_ast_node_base **result, void *payload) {
    APPLY_PROLOGUE(mem, parser, result, payload);
    REQUIRE_OK(kefir_parser_ast_builder_wrap(mem, parser, result, builder_callback, NULL));
    return KEFIR_OK;
}
