#ifndef KEFIR_AST_ANALYZER_NODES_H_
#define KEFIR_AST_ANALYZER_NODES_H_

#include "kefir/ast/node.h"
#include "kefir/ast/context.h"

#define ANALYZE_NODE(id, type) \
kefir_result_t kefir_ast_analyze_##id##_node(struct kefir_mem *, \
                                         const struct kefir_ast_context *, \
                                         const type *, \
                                         struct kefir_ast_node_base *)
                                
ANALYZE_NODE(constant, struct kefir_ast_constant);
ANALYZE_NODE(identifier, struct kefir_ast_identifier);
ANALYZE_NODE(unary_operation, struct kefir_ast_unary_operation);
ANALYZE_NODE(binary_operation, struct kefir_ast_binary_operation);
ANALYZE_NODE(array_subscript, struct kefir_ast_array_subscript);
ANALYZE_NODE(function_call, struct kefir_ast_function_call);
ANALYZE_NODE(struct_member, struct kefir_ast_struct_member);
ANALYZE_NODE(string_literal, struct kefir_ast_string_literal);
ANALYZE_NODE(type_name, struct kefir_ast_type_name);
ANALYZE_NODE(cast_operator, struct kefir_ast_cast_operator);
ANALYZE_NODE(generic_selection, struct kefir_ast_generic_selection);
ANALYZE_NODE(conditional_operator, struct kefir_ast_conditional_operator);
ANALYZE_NODE(assignment_operator, struct kefir_ast_assignment_operator);
ANALYZE_NODE(comma_operator, struct kefir_ast_comma_operator);

#undef ANALYZE_NODE

#endif