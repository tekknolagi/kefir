#include "kefir/ast/node.h"
#include "kefir/ast/node_internal.h"
#include "kefir/core/util.h"
#include "kefir/core/error.h"

NODE_VISIT_IMPL(ast_identifier_visit, kefir_ast_identifier, identifier)

kefir_result_t ast_identifier_free(struct kefir_mem *mem, struct kefir_ast_node_base *base) {
    REQUIRE(mem != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid memory allocator"));
    REQUIRE(base != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid AST node base"));
    ASSIGN_DECL_CAST(struct kefir_ast_identifier *, node,
        base->self);
    KEFIR_FREE(mem, node);
    return KEFIR_OK;
}

const struct kefir_ast_node_class AST_IDENTIFIER_CLASS = {
    .type = KEFIR_AST_IDENTIFIER,
    .visit = ast_identifier_visit,
    .free = ast_identifier_free
};

struct kefir_ast_identifier *kefir_ast_new_identifier(struct kefir_mem *mem,
                                                  struct kefir_symbol_table *symbols,
                                                  const char *identifier) {
    REQUIRE(mem != NULL, NULL);
    REQUIRE(symbols != NULL, NULL);
    REQUIRE(identifier != NULL, NULL);
    const char *id_copy = kefir_symbol_table_insert(mem, symbols, identifier, NULL);
    REQUIRE(id_copy != NULL, NULL);
    struct kefir_ast_identifier *id = KEFIR_MALLOC(mem, sizeof(struct kefir_ast_identifier));
    REQUIRE(id != NULL, NULL);
    id->base.klass = &AST_IDENTIFIER_CLASS;
    id->base.self = id;
    id->base.expression_type = NULL;
    id->identifier = id_copy;
    return id;
}
