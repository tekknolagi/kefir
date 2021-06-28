#ifndef KEFIR_AST_CONSTANTS_H_
#define KEFIR_AST_CONSTANTS_H_

#include "kefir/core/basic-types.h"
#include <limits.h>

typedef enum kefir_ast_node_type {
    // Primary expressions
    KEFIR_AST_CONSTANT,
    KEFIR_AST_IDENTIFIER,
    KEFIR_AST_STRING_LITERAL,
    KEFIR_AST_GENERIC_SELECTION,
    // Postfix operators
    KEFIR_AST_ARRAY_SUBSCRIPT,
    KEFIR_AST_FUNCTION_CALL,
    KEFIR_AST_STRUCTURE_MEMBER,
    KEFIR_AST_STRUCTURE_INDIRECT_MEMBER,
    KEFIR_AST_COMPOUND_LITERAL,

    KEFIR_AST_UNARY_OPERATION,
    KEFIR_AST_BINARY_OPERATION,
    KEFIR_AST_CONDITIONAL_OPERATION,
    KEFIR_AST_ASSIGNMENT_OPERATOR,

    KEFIR_AST_DECLARATION,
    KEFIR_AST_TYPE_NAME,
    KEFIR_AST_CAST_OPERATOR,
    KEFIR_AST_COMMA_OPERATOR,

    KEFIR_AST_DECLARATOR,
    KEFIR_AST_DECLARATOR_SPECIFIER,
    KEFIR_AST_STATIC_ASSERTION,

    KEFIR_AST_LABELED_STATEMENT,
    KEFIR_AST_CASE_STATEMENT,
    KEFIR_AST_EXPRESSION_STATEMENT,
    KEFIR_AST_COMPOUND_STATEMENT,
    KEFIR_AST_CONDITIONAL_STATEMENT,
    KEFIR_AST_SWITCH_STATEMENT,
    KEFIR_AST_WHILE_STATEMENT,
    KEFIR_AST_DO_WHILE_STATEMENT,
    KEFIR_AST_FOR_STATEMENT,
    KEFIR_AST_GOTO_STATEMENT,
    KEFIR_AST_CONTINUE_STATEMENT,
    KEFIR_AST_BREAK_STATEMENT,
    KEFIR_AST_RETURN_STATEMENT,

    KEFIR_AST_FUNCTION_DEFINITION,
    KEFIR_AST_TRANSLATION_UNIT
} kefir_ast_node_type_t;

typedef enum kefir_ast_node_category {
    KEFIR_AST_NODE_CATEGORY_UNKNOWN,
    KEFIR_AST_NODE_CATEGORY_EXPRESSION,
    KEFIR_AST_NODE_CATEGORY_TYPE,
    KEFIR_AST_NODE_CATEGORY_DECLARATION,
    KEFIR_AST_NODE_CATEGORY_STATEMENT
} kefir_ast_node_category_t;

typedef enum kefir_ast_constant_type {
    KEFIR_AST_BOOL_CONSTANT,
    KEFIR_AST_CHAR_CONSTANT,
    KEFIR_AST_INT_CONSTANT,
    KEFIR_AST_UINT_CONSTANT,
    KEFIR_AST_LONG_CONSTANT,
    KEFIR_AST_ULONG_CONSTANT,
    KEFIR_AST_LONG_LONG_CONSTANT,
    KEFIR_AST_ULONG_LONG_CONSTANT,
    KEFIR_AST_FLOAT_CONSTANT,
    KEFIR_AST_DOUBLE_CONSTANT
} kefir_ast_constant_type_t;

typedef enum kefir_ast_unary_operation_type {
    KEFIR_AST_OPERATION_PLUS,
    KEFIR_AST_OPERATION_NEGATE,
    KEFIR_AST_OPERATION_INVERT,
    KEFIR_AST_OPERATION_LOGICAL_NEGATE,
    KEFIR_AST_OPERATION_POSTFIX_INCREMENT,
    KEFIR_AST_OPERATION_POSTFIX_DECREMENT,
    KEFIR_AST_OPERATION_PREFIX_INCREMENT,
    KEFIR_AST_OPERATION_PREFIX_DECREMENT,
    KEFIR_AST_OPERATION_ADDRESS,
    KEFIR_AST_OPERATION_INDIRECTION,
    KEFIR_AST_OPERATION_SIZEOF,
    KEFIR_AST_OPERATION_ALIGNOF
} kefir_ast_unary_operation_type_t;

typedef enum kefir_ast_binary_operation_type {
    KEFIR_AST_OPERATION_ADD,
    KEFIR_AST_OPERATION_SUBTRACT,
    KEFIR_AST_OPERATION_MULTIPLY,
    KEFIR_AST_OPERATION_DIVIDE,
    KEFIR_AST_OPERATION_MODULO,
    KEFIR_AST_OPERATION_SHIFT_LEFT,
    KEFIR_AST_OPERATION_SHIFT_RIGHT,
    KEFIR_AST_OPERATION_LESS,
    KEFIR_AST_OPERATION_LESS_EQUAL,
    KEFIR_AST_OPERATION_GREATER,
    KEFIR_AST_OPERATION_GREATER_EQUAL,
    KEFIR_AST_OPERATION_EQUAL,
    KEFIR_AST_OPERATION_NOT_EQUAL,
    KEFIR_AST_OPERATION_BITWISE_AND,
    KEFIR_AST_OPERATION_BITWISE_OR,
    KEFIR_AST_OPERATION_BITWISE_XOR,
    KEFIR_AST_OPERATION_LOGICAL_AND,
    KEFIR_AST_OPERATION_LOGICAL_OR
} kefir_ast_binary_operation_type_t;

typedef enum kefir_ast_assignment_operation {
    KEFIR_AST_ASSIGNMENT_SIMPLE,
    KEFIR_AST_ASSIGNMENT_MULTIPLY,
    KEFIR_AST_ASSIGNMENT_DIVIDE,
    KEFIR_AST_ASSIGNMENT_MODULO,
    KEFIR_AST_ASSIGNMENT_ADD,
    KEFIR_AST_ASSIGNMENT_SUBTRACT,
    KEFIR_AST_ASSIGNMENT_SHIFT_LEFT,
    KEFIR_AST_ASSIGNMENT_SHIFT_RIGHT,
    KEFIR_AST_ASSIGNMENT_BITWISE_AND,
    KEFIR_AST_ASSIGNMENT_BITWISE_OR,
    KEFIR_AST_ASSIGNMENT_BITWISE_XOR
} kefir_ast_assignment_operation_t;

typedef enum kefir_ast_storage_duration {
    KEFIR_AST_STORAGE_DURATION_STATIC,
    KEFIR_AST_STORAGE_DURATION_THREAD,
    KEFIR_AST_STORAGE_DURATION_AUTOMATIC,
    KEFIR_AST_STORAGE_DURATION_ALLOCATED
} kefir_ast_storage_duration_t;

typedef enum kefir_ast_scoped_identifier_class {
    KEFIR_AST_SCOPE_IDENTIFIER_OBJECT,
    KEFIR_AST_SCOPE_IDENTIFIER_ENUM_CONSTANT,
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

typedef enum kefir_ast_scoped_identifier_storage {
    KEFIR_AST_SCOPE_IDENTIFIER_STORAGE_TYPEDEF,
    KEFIR_AST_SCOPE_IDENTIFIER_STORAGE_EXTERN,
    KEFIR_AST_SCOPE_IDENTIFIER_STORAGE_STATIC,
    KEFIR_AST_SCOPE_IDENTIFIER_STORAGE_THREAD_LOCAL,
    KEFIR_AST_SCOPE_IDENTIFIER_STORAGE_EXTERN_THREAD_LOCAL,
    KEFIR_AST_SCOPE_IDENTIFIER_STORAGE_STATIC_THREAD_LOCAL,
    KEFIR_AST_SCOPE_IDENTIFIER_STORAGE_AUTO,
    KEFIR_AST_SCOPE_IDENTIFIER_STORAGE_REGISTER,
    KEFIR_AST_SCOPE_IDENTIFIER_STORAGE_UNKNOWN
} kefir_ast_scoped_identifier_storage_t;

typedef enum kefir_ast_function_specifier {
    KEFIR_AST_FUNCTION_SPECIFIER_NONE = 0,
    KEFIR_AST_FUNCTION_SPECIFIER_NORETURN,
    KEFIR_AST_FUNCTION_SPECIFIER_INLINE,
    KEFIR_AST_FUNCTION_SPECIFIER_INLINE_NORETURN
} kefir_ast_function_specifier_t;

typedef enum kefir_ast_type_specifier_type {
    KEFIR_AST_TYPE_SPECIFIER_VOID = 0,
    KEFIR_AST_TYPE_SPECIFIER_CHAR,
    KEFIR_AST_TYPE_SPECIFIER_SHORT,
    KEFIR_AST_TYPE_SPECIFIER_INT,
    KEFIR_AST_TYPE_SPECIFIER_LONG,
    KEFIR_AST_TYPE_SPECIFIER_FLOAT,
    KEFIR_AST_TYPE_SPECIFIER_DOUBLE,
    KEFIR_AST_TYPE_SPECIFIER_SIGNED,
    KEFIR_AST_TYPE_SPECIFIER_UNSIGNED,
    KEFIR_AST_TYPE_SPECIFIER_BOOL,
    KEFIR_AST_TYPE_SPECIFIER_COMPLEX,
    KEFIR_AST_TYPE_SPECIFIER_ATOMIC,
    KEFIR_AST_TYPE_SPECIFIER_STRUCT,
    KEFIR_AST_TYPE_SPECIFIER_UNION,
    KEFIR_AST_TYPE_SPECIFIER_ENUM,
    KEFIR_AST_TYPE_SPECIFIER_TYPEDEF,
    // Special value
    KEFIR_AST_TYPE_SPECIFIER_COUNT
} kefir_ast_type_specifier_type_t;

_Static_assert(KEFIR_AST_TYPE_SPECIFIER_COUNT <= sizeof(kefir_uint64_t) * CHAR_BIT,
               "Number of type specifiers exceeds the largest bit map size");

typedef enum kefir_ast_storage_class_specifier_type {
    KEFIR_AST_STORAGE_SPECIFIER_TYPEDEF = 0,
    KEFIR_AST_STORAGE_SPECIFIER_EXTERN,
    KEFIR_AST_STORAGE_SPECIFIER_STATIC,
    KEFIR_AST_STORAGE_SPECIFIER_THREAD_LOCAL,
    KEFIR_AST_STORAGE_SPECIFIER_AUTO,
    KEFIR_AST_STORAGE_SPECIFIER_REGISTER,
    // Special value
    KEFIR_AST_STORAGE_SPECIFIER_COUNT
} kefir_ast_storage_class_specifier_type_t;

_Static_assert(KEFIR_AST_STORAGE_SPECIFIER_COUNT <= sizeof(kefir_uint64_t) * CHAR_BIT,
               "Number of storage specifiers exceeds the largest bit map size");

typedef enum kefir_ast_type_qualifier_type {
    KEFIR_AST_TYPE_QUALIFIER_CONST = 0,
    KEFIR_AST_TYPE_QUALIFIER_RESTRICT,
    KEFIR_AST_TYPE_QUALIFIER_VOLATILE,
    KEFIR_AST_TYPE_QUALIFIER_ATOMIC,
    // Special value
    KEFIR_AST_TYPE_QUALIFIER_COUNT
} kefir_ast_type_qualifier_type_t;

_Static_assert(KEFIR_AST_TYPE_QUALIFIER_CONST <= sizeof(kefir_uint64_t) * CHAR_BIT,
               "Number of storage specifiers exceeds the largest bit map size");
typedef enum kefir_ast_function_specifier_type {
    KEFIR_AST_FUNCTION_SPECIFIER_TYPE_NORETURN = 0,
    KEFIR_AST_FUNCTION_SPECIFIER_TYPE_INLINE,
    // Special value
    KEFIR_AST_FUNCTION_SPECIFIER_TYPE_COUNT
} kefir_ast_function_specifier_type_t;

_Static_assert(KEFIR_AST_FUNCTION_SPECIFIER_TYPE_COUNT <= sizeof(kefir_uint64_t) * CHAR_BIT,
               "Number of function specifiers exceeds the largest bit map size");

typedef enum kefir_ast_declarator_specifier_class {
    KEFIR_AST_TYPE_SPECIFIER,
    KEFIR_AST_TYPE_QUALIFIER,
    KEFIR_AST_STORAGE_CLASS_SPECIFIER,
    KEFIR_AST_FUNCTION_SPECIFIER,
    KEFIR_AST_ALIGNMENT_SPECIFIER
} kefir_ast_declarator_specifier_class_t;

typedef enum kefir_ast_declarator_class {
    KEFIR_AST_DECLARATOR_IDENTIFIER,
    KEFIR_AST_DECLARATOR_POINTER,
    KEFIR_AST_DECLARATOR_ARRAY,
    KEFIR_AST_DECLARATOR_FUNCTION
} kefir_ast_declarator_class_t;

typedef enum kefir_ast_type_analysis_context {
    KEFIR_AST_TYPE_ANALYSIS_DEFAULT,
    KEFIR_AST_TYPE_ANALYSIS_FUNCTION_PARAMETER
} kefir_ast_type_analysis_context_t;

#endif
