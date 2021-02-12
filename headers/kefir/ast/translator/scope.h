#ifndef KEFIR_AST_TRANSLATOR_SCOPE_H_
#define KEFIR_AST_TRANSLATOR_SCOPE_H_

#include "kefir/core/mem.h"
#include "kefir/ast/type.h"
#include "kefir/ast/constants.h"
#include "kefir/core/hashtree.h"
#include "kefir/core/tree.h"

typedef enum kefir_ast_scoped_identifier_class {
    KEFIR_AST_SCOPE_IDENTIFIER_OBJECT,
    KEFIR_AST_SCOPE_IDENTIFIER_FUNCTION,
    KEFIR_AST_SCOPE_IDENTIFIER_TYPE_TAG,
    KEFIR_AST_SCOPE_IDENTIFIER_TYPE_DEFINITION,
    KEFIR_AST_SCOPE_IDENTIFIER_LABEL
} kefir_ast_scoped_identifier_class_t;

typedef enum kefir_ast_scoped_identifier_linkage {
    KEFIR_AST_SCOPED_IDENTIFIER_EXTERNAL_LINKAGE,
    KEFIR_AST_SCOPED_IDENTIFIER_INTERNAL_LINKAGE,
    KEFIR_AST_SCOPED_IDENTIFIER_NONE_LINKAGE
} kefir_ast_scoped_identifier_linkage_t;

typedef struct kefir_ast_scoped_identifier {
    kefir_ast_scoped_identifier_class_t klass;
    union {
        struct {
            const struct kefir_ast_type *type;
            kefir_ast_scoped_identifier_linkage_t linkage;
        } object;
        const struct kefir_ast_type *type;
    };
} kefir_ast_scoped_identifier_t;

typedef struct kefir_ast_identifier_flat_scope_iterator {
    struct kefir_hashtree_node_iterator iter;
} kefir_ast_identifier_flat_scope_iterator_t;

typedef struct kefir_ast_identifier_flat_scope {
    struct kefir_hashtree content;
} kefir_ast_identifier_flat_scope_t;

kefir_result_t kefir_ast_identifier_flat_scope_init(struct kefir_ast_identifier_flat_scope *);
kefir_result_t kefir_ast_identifier_flat_scope_free(struct kefir_mem *,
                                           struct kefir_ast_identifier_flat_scope *);
kefir_result_t kefir_ast_identifier_flat_scope_insert(struct kefir_mem *,
                                             struct kefir_ast_identifier_flat_scope *,
                                             const char *,
                                             const struct kefir_ast_scoped_identifier *);
kefir_result_t kefir_ast_identifier_flat_scope_at(const struct kefir_ast_identifier_flat_scope *,
                                         const char *,
                                         const struct kefir_ast_scoped_identifier **);
kefir_result_t kefir_ast_identifier_flat_scope_iter(const struct kefir_ast_identifier_flat_scope *,
                                           struct kefir_ast_identifier_flat_scope_iterator *,
                                           const char **,
                                           const struct kefir_ast_scoped_identifier **);
kefir_result_t kefir_ast_identifier_flat_scope_next(const struct kefir_ast_identifier_flat_scope *,
                                           struct kefir_ast_identifier_flat_scope_iterator *,
                                           const char **,
                                           const struct kefir_ast_scoped_identifier **);

typedef struct kefir_ast_identifier_block_scope {
    struct kefir_tree_node root;
    struct kefir_tree_node *top_scope;
} kefir_ast_identifier_block_scope_t;

typedef struct kefir_ast_identifier_block_scope_iterator {
    struct kefir_ast_identifier_flat_scope_iterator current_scope_iter;
    struct kefir_tree_node_iterator tree_iter;
} kefir_ast_identifier_block_scope_iterator_t;

kefir_result_t kefir_ast_identifier_block_scope_init(struct kefir_mem *,
                                      struct kefir_ast_identifier_block_scope *);
kefir_result_t kefir_ast_identifier_block_scope_free(struct kefir_mem *,
                                      struct kefir_ast_identifier_block_scope *);
struct kefir_ast_identifier_flat_scope *kefir_ast_identifier_block_scope_top(const struct kefir_ast_identifier_block_scope *);
kefir_result_t kefir_ast_identifier_block_scope_push(struct kefir_mem *,
                                      struct kefir_ast_identifier_block_scope *);
kefir_result_t kefir_ast_identifier_block_scope_pop(struct kefir_ast_identifier_block_scope *);

kefir_result_t kefir_ast_identifier_block_scope_insert(struct kefir_mem *,
                                        const struct kefir_ast_identifier_block_scope *,
                                        const char *,
                                        const struct kefir_ast_scoped_identifier *);
kefir_result_t kefir_ast_identifier_block_scope_at(const struct kefir_ast_identifier_block_scope *,
                                    const char *,
                                    const struct kefir_ast_scoped_identifier **);


#endif