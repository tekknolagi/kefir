#ifndef KEFIR_AST_CONTEXT_H_
#define KEFIR_AST_CONTEXT_H_

#include "kefir/ast/scope.h"
#include "kefir/ast/target_environment.h"

typedef struct kefir_ast_context {
    kefir_result_t (*resolve_ordinary_identifier)(const struct kefir_ast_context *,
                                                const char *,
                                                const struct kefir_ast_scoped_identifier **);
    kefir_result_t (*resolve_tag_identifier)(const struct kefir_ast_context *,
                                           const char *,
                                           const struct kefir_ast_scoped_identifier **);

    struct kefir_symbol_table *symbols;
    const struct kefir_ast_type_traits *type_traits;
    struct kefir_ast_type_bundle *type_bundle;
    const struct kefir_ast_target_environment *target_env;

    void *payload;
} kefir_ast_context_t;

#endif