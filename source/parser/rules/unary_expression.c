#include "kefir/parser/rule_helpers.h"
#include "kefir/parser/builder.h"

static kefir_result_t builder_callback(struct kefir_mem *mem, struct kefir_parser_ast_builder *builder, void *payload) {
    UNUSED(payload);
    REQUIRE(mem != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid memory allocator"));
    REQUIRE(builder != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid parser AST builder"));
    struct kefir_parser *parser = builder->parser;

    if (PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_DOUBLE_PLUS)) {
        REQUIRE_OK(PARSER_SHIFT(parser));
        REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, KEFIR_PARSER_RULE_FN(cast_expression), NULL));
        REQUIRE_OK(kefir_parser_ast_builder_unary_operation(mem, builder, KEFIR_AST_OPERATION_PREFIX_INCREMENT));
    } else if (PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_DOUBLE_MINUS)) {
        REQUIRE_OK(PARSER_SHIFT(parser));
        REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, KEFIR_PARSER_RULE_FN(cast_expression), NULL));
        REQUIRE_OK(kefir_parser_ast_builder_unary_operation(mem, builder, KEFIR_AST_OPERATION_PREFIX_DECREMENT));
    } else if (PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_AMPERSAND)) {
        REQUIRE_OK(PARSER_SHIFT(parser));
        REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, KEFIR_PARSER_RULE_FN(cast_expression), NULL));
        REQUIRE_OK(kefir_parser_ast_builder_unary_operation(mem, builder, KEFIR_AST_OPERATION_ADDRESS));
    } else if (PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_STAR)) {
        REQUIRE_OK(PARSER_SHIFT(parser));
        REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, KEFIR_PARSER_RULE_FN(cast_expression), NULL));
        REQUIRE_OK(kefir_parser_ast_builder_unary_operation(mem, builder, KEFIR_AST_OPERATION_INDIRECTION));
    } else if (PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_PLUS)) {
        REQUIRE_OK(PARSER_SHIFT(parser));
        REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, KEFIR_PARSER_RULE_FN(cast_expression), NULL));
        REQUIRE_OK(kefir_parser_ast_builder_unary_operation(mem, builder, KEFIR_AST_OPERATION_PLUS));
    } else if (PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_MINUS)) {
        REQUIRE_OK(PARSER_SHIFT(parser));
        REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, KEFIR_PARSER_RULE_FN(cast_expression), NULL));
        REQUIRE_OK(kefir_parser_ast_builder_unary_operation(mem, builder, KEFIR_AST_OPERATION_NEGATE));
    } else if (PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_TILDE)) {
        REQUIRE_OK(PARSER_SHIFT(parser));
        REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, KEFIR_PARSER_RULE_FN(cast_expression), NULL));
        REQUIRE_OK(kefir_parser_ast_builder_unary_operation(mem, builder, KEFIR_AST_OPERATION_INVERT));
    } else if (PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_EXCLAMATION_MARK)) {
        REQUIRE_OK(PARSER_SHIFT(parser));
        REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, KEFIR_PARSER_RULE_FN(cast_expression), NULL));
        REQUIRE_OK(kefir_parser_ast_builder_unary_operation(mem, builder, KEFIR_AST_OPERATION_LOGICAL_NEGATE));
    } else if (PARSER_TOKEN_IS_KEYWORD(parser, 0, KEFIR_KEYWORD_SIZEOF) &&
               PARSER_TOKEN_IS_PUNCTUATOR(parser, 1, KEFIR_PUNCTUATOR_LEFT_PARENTHESE)) {
        REQUIRE_OK(PARSER_SHIFT(parser));
        REQUIRE_OK(PARSER_SHIFT(parser));
        REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, KEFIR_PARSER_RULE_FN(type_name), NULL));
        REQUIRE(PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_RIGHT_PARENTHESE),
                KEFIR_SET_ERROR(KEFIR_SYNTAX_ERROR, "Expected right parenthese"));
        REQUIRE_OK(kefir_parser_ast_builder_unary_operation(mem, builder, KEFIR_AST_OPERATION_SIZEOF));
    } else if (PARSER_TOKEN_IS_KEYWORD(parser, 0, KEFIR_KEYWORD_SIZEOF)) {
        REQUIRE_OK(PARSER_SHIFT(parser));
        REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, KEFIR_PARSER_RULE_FN(unary_expression), NULL));
        REQUIRE_OK(kefir_parser_ast_builder_unary_operation(mem, builder, KEFIR_AST_OPERATION_SIZEOF));
    } else if (PARSER_TOKEN_IS_KEYWORD(parser, 0, KEFIR_KEYWORD_ALIGNAS)) {
        REQUIRE_OK(PARSER_SHIFT(parser));
        REQUIRE(PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_LEFT_PARENTHESE),
                KEFIR_SET_ERROR(KEFIR_SYNTAX_ERROR, "Expected left parenthese"));
        REQUIRE_OK(PARSER_SHIFT(parser));
        REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, KEFIR_PARSER_RULE_FN(type_name), NULL));
        REQUIRE(PARSER_TOKEN_IS_PUNCTUATOR(parser, 0, KEFIR_PUNCTUATOR_RIGHT_PARENTHESE),
                KEFIR_SET_ERROR(KEFIR_SYNTAX_ERROR, "Expected right parenthese"));
        REQUIRE_OK(kefir_parser_ast_builder_unary_operation(mem, builder, KEFIR_AST_OPERATION_ALIGNOF));
    } else {
        REQUIRE_OK(kefir_parser_ast_builder_scan(mem, builder, KEFIR_PARSER_RULE_FN(postfix_expression), NULL));
    }
    return KEFIR_OK;
}

kefir_result_t KEFIR_PARSER_RULE_FN(unary_expression)(struct kefir_mem *mem, struct kefir_parser *parser,
                                                      struct kefir_ast_node_base **result, void *payload) {
    APPLY_PROLOGUE(mem, parser, result, payload);
    REQUIRE_OK(kefir_parser_ast_builder_wrap(mem, parser, result, builder_callback, NULL));
    return KEFIR_OK;
}
