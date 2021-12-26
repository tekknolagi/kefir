#include "kefir/ast/context.h"
#include "kefir/core/error.h"
#include "kefir/core/util.h"

kefir_result_t kefir_ast_context_configuration_defaults(struct kefir_ast_context_configuration *config) {
    REQUIRE(config != NULL, KEFIR_SET_ERROR(KEFIR_INVALID_PARAMETER, "Expected valid AST context configuration"));

    *config = (struct kefir_ast_context_configuration){.analysis = {.non_strict_qualifiers = false}};
    return KEFIR_OK;
}
