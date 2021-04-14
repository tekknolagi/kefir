#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kefir/ir/function.h"
#include "kefir/ir/module.h"
#include "kefir/ir/builder.h"
#include "kefir/core/mem.h"
#include "kefir/core/util.h"
#include "kefir/codegen/amd64-sysv.h"
#include "kefir/codegen/amd64/system-v/abi.h"

kefir_result_t kefir_int_test(struct kefir_mem *mem) {
    struct kefir_codegen_amd64 codegen;
    struct kefir_ir_module module;
    REQUIRE_OK(kefir_ir_module_alloc(mem, &module));
    REQUIRE_OK(kefir_codegen_amd64_sysv_init(&codegen, stdout));
    codegen.asmgen.settings.enable_comments = false;
    codegen.asmgen.settings.enable_identation = false;

    struct kefir_ir_type *decl_params = kefir_ir_module_new_type(mem, &module, 0, NULL),
                       *decl_result = kefir_ir_module_new_type(mem, &module, 0, NULL);
    REQUIRE(decl_params != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE(decl_result != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function_decl *decl =
        kefir_ir_module_new_function_declaration(mem, &module, "func1", NULL, decl_params, false, decl_result);
    REQUIRE(decl != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function *func = kefir_ir_module_new_function(mem, &module, decl->identifier, NULL, 1024);
    REQUIRE(func != NULL, KEFIR_INTERNAL_ERROR);

    kefir_id_t literal_id;
    const char *literal = "Hello, world!";
    REQUIRE_OK(kefir_ir_module_string_literal(mem, &module, literal, strlen(literal) + 1, &literal_id));
    kefir_irbuilder_block_appendi64(mem, &func->body, KEFIR_IROPCODE_PUSHSTRING, literal_id);

    literal = "Hello,\ncruel\tworld!";
    REQUIRE_OK(kefir_ir_module_string_literal(mem, &module, literal, strlen(literal) + 1, &literal_id));
    kefir_irbuilder_block_appendi64(mem, &func->body, KEFIR_IROPCODE_PUSHSTRING, literal_id);

    literal = "\n\n\n\t\t\t   \t\t\t\v\v\v\n";
    REQUIRE_OK(kefir_ir_module_string_literal(mem, &module, literal, strlen(literal) + 1, &literal_id));
    kefir_irbuilder_block_appendi64(mem, &func->body, KEFIR_IROPCODE_PUSHSTRING, literal_id);

    literal = "\'\"Hey ho!\"\'\\\"";
    REQUIRE_OK(kefir_ir_module_string_literal(mem, &module, literal, strlen(literal) + 1, &literal_id));
    kefir_irbuilder_block_appendi64(mem, &func->body, KEFIR_IROPCODE_PUSHSTRING, literal_id);

    literal = "\0\0\0\n\0";
    REQUIRE_OK(kefir_ir_module_string_literal(mem, &module, literal, 6, &literal_id));
    kefir_irbuilder_block_appendi64(mem, &func->body, KEFIR_IROPCODE_PUSHSTRING, literal_id);

    REQUIRE_OK(KEFIR_CODEGEN_TRANSLATE(mem, &codegen.iface, &module));
    REQUIRE_OK(KEFIR_CODEGEN_CLOSE(&codegen.iface));
    REQUIRE_OK(kefir_ir_module_free(mem, &module));
    return KEFIR_OK;
}