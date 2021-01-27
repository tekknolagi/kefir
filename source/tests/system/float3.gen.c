#include <stdlib.h>
#include <stdio.h>
#include "kefir/ir/function.h"
#include "kefir/ir/module.h"
#include "kefir/ir/builder.h"
#include "kefir/core/mem.h"
#include "kefir/core/util.h"
#include "kefir/codegen/amd64-sysv.h"

kefir_result_t kefir_int_test(struct kefir_mem *mem) {
    struct kefir_codegen_amd64 codegen;
    kefir_codegen_amd64_sysv_init(&codegen, stdout);

    struct kefir_ir_module module;
    REQUIRE_OK(kefir_ir_module_alloc(mem, &module));

    struct kefir_ir_type *fequals_decl_params = kefir_ir_module_new_type(mem, &module, 2, NULL),
                       *fequals_decl_result = kefir_ir_module_new_type(mem, &module, 1, NULL);
    REQUIRE(fequals_decl_params != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE(fequals_decl_result != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function_decl *fequals_decl =
        kefir_ir_module_new_function_declaration(mem, &module, "fequals", NULL, fequals_decl_params, false, fequals_decl_result);
    REQUIRE(fequals_decl != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function *fequals = kefir_ir_module_new_function(mem, &module, fequals_decl->identifier, NULL, 1024);
    REQUIRE(fequals != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE_OK(kefir_ir_module_declare_global(mem, &module, fequals_decl->identifier));
    kefir_irbuilder_type_append_v(mem, fequals->declaration->params, KEFIR_IR_TYPE_FLOAT32, 0, 0);
    kefir_irbuilder_type_append_v(mem, fequals->declaration->params, KEFIR_IR_TYPE_FLOAT32, 0, 0);
    kefir_irbuilder_type_append_v(mem, fequals->declaration->result, KEFIR_IR_TYPE_BOOL, 0, 3);
    kefir_irbuilder_block_append(mem, &fequals->body, KEFIR_IROPCODE_F32EQUALS, 0);

    struct kefir_ir_type *fgreater_decl_params = kefir_ir_module_new_type(mem, &module, 2, NULL),
                       *fgreater_decl_result = kefir_ir_module_new_type(mem, &module, 1, NULL);
    REQUIRE(fgreater_decl_params != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE(fgreater_decl_result != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function_decl *fgreater_decl =
        kefir_ir_module_new_function_declaration(mem, &module, "fgreater", NULL, fgreater_decl_params, false, fgreater_decl_result);
    REQUIRE(fgreater_decl != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function *fgreater = kefir_ir_module_new_function(mem, &module, fgreater_decl->identifier, NULL, 1024);
    REQUIRE(fgreater != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE_OK(kefir_ir_module_declare_global(mem, &module, fgreater_decl->identifier));
    kefir_irbuilder_type_append_v(mem, fgreater->declaration->params, KEFIR_IR_TYPE_FLOAT32, 0, 0);
    kefir_irbuilder_type_append_v(mem, fgreater->declaration->params, KEFIR_IR_TYPE_FLOAT32, 0, 0);
    kefir_irbuilder_type_append_v(mem, fgreater->declaration->result, KEFIR_IR_TYPE_BOOL, 0, 3);
    kefir_irbuilder_block_append(mem, &fgreater->body, KEFIR_IROPCODE_F32GREATER, 0);

    struct kefir_ir_type *flesser_decl_params = kefir_ir_module_new_type(mem, &module, 2, NULL),
                       *flesser_decl_result = kefir_ir_module_new_type(mem, &module, 1, NULL);
    REQUIRE(flesser_decl_params != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE(flesser_decl_result != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function_decl *flesser_decl =
        kefir_ir_module_new_function_declaration(mem, &module, "flesser", NULL, flesser_decl_params, false, flesser_decl_result);
    REQUIRE(flesser_decl != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function *flesser = kefir_ir_module_new_function(mem, &module, flesser_decl->identifier, NULL, 1024);
    REQUIRE(flesser != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE_OK(kefir_ir_module_declare_global(mem, &module, flesser_decl->identifier));
    kefir_irbuilder_type_append_v(mem, flesser->declaration->params, KEFIR_IR_TYPE_FLOAT32, 0, 0);
    kefir_irbuilder_type_append_v(mem, flesser->declaration->params, KEFIR_IR_TYPE_FLOAT32, 0, 0);
    kefir_irbuilder_type_append_v(mem, flesser->declaration->result, KEFIR_IR_TYPE_BOOL, 0, 3);
    kefir_irbuilder_block_append(mem, &flesser->body, KEFIR_IROPCODE_F32LESSER, 0);

    struct kefir_ir_type *dequals_decl_params = kefir_ir_module_new_type(mem, &module, 2, NULL),
                       *dequals_decl_result = kefir_ir_module_new_type(mem, &module, 1, NULL);
    REQUIRE(dequals_decl_params != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE(dequals_decl_result != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function_decl *dequals_decl =
        kefir_ir_module_new_function_declaration(mem, &module, "dequals", NULL, dequals_decl_params, false, dequals_decl_result);
    REQUIRE(dequals_decl != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function *dequals = kefir_ir_module_new_function(mem, &module, dequals_decl->identifier, NULL, 1024);
    REQUIRE(dequals != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE_OK(kefir_ir_module_declare_global(mem, &module, dequals_decl->identifier));
    kefir_irbuilder_type_append_v(mem, dequals->declaration->params, KEFIR_IR_TYPE_FLOAT64, 0, 0);
    kefir_irbuilder_type_append_v(mem, dequals->declaration->params, KEFIR_IR_TYPE_FLOAT64, 0, 0);
    kefir_irbuilder_type_append_v(mem, dequals->declaration->result, KEFIR_IR_TYPE_BOOL, 0, 3);
    kefir_irbuilder_block_append(mem, &dequals->body, KEFIR_IROPCODE_F64EQUALS, 0);

    struct kefir_ir_type *dgreater_decl_params = kefir_ir_module_new_type(mem, &module, 2, NULL),
                       *dgreater_decl_result = kefir_ir_module_new_type(mem, &module, 1, NULL);
    REQUIRE(dgreater_decl_params != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE(dgreater_decl_result != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function_decl *dgreater_decl =
        kefir_ir_module_new_function_declaration(mem, &module, "dgreater", NULL, dgreater_decl_params, false, dgreater_decl_result);
    REQUIRE(dgreater_decl != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function *dgreater = kefir_ir_module_new_function(mem, &module, dgreater_decl->identifier, NULL, 1024);
    REQUIRE(dgreater != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE_OK(kefir_ir_module_declare_global(mem, &module, dgreater_decl->identifier));
    kefir_irbuilder_type_append_v(mem, dgreater->declaration->params, KEFIR_IR_TYPE_FLOAT64, 0, 0);
    kefir_irbuilder_type_append_v(mem, dgreater->declaration->params, KEFIR_IR_TYPE_FLOAT64, 0, 0);
    kefir_irbuilder_type_append_v(mem, dgreater->declaration->result, KEFIR_IR_TYPE_BOOL, 0, 3);
    kefir_irbuilder_block_append(mem, &dgreater->body, KEFIR_IROPCODE_F64GREATER, 0);

    struct kefir_ir_type *dlesser_decl_params = kefir_ir_module_new_type(mem, &module, 2, NULL),
                       *dlesser_decl_result = kefir_ir_module_new_type(mem, &module, 1, NULL);
    REQUIRE(dlesser_decl_params != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE(dlesser_decl_result != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function_decl *dlesser_decl =
        kefir_ir_module_new_function_declaration(mem, &module, "dlesser", NULL, dlesser_decl_params, false, dlesser_decl_result);
    REQUIRE(dlesser_decl != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function *dlesser = kefir_ir_module_new_function(mem, &module, dlesser_decl->identifier, NULL, 1024);
    REQUIRE(dlesser != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE_OK(kefir_ir_module_declare_global(mem, &module, dlesser_decl->identifier));
    kefir_irbuilder_type_append_v(mem, dlesser->declaration->params, KEFIR_IR_TYPE_FLOAT64, 0, 0);
    kefir_irbuilder_type_append_v(mem, dlesser->declaration->params, KEFIR_IR_TYPE_FLOAT64, 0, 0);
    kefir_irbuilder_type_append_v(mem, dlesser->declaration->result, KEFIR_IR_TYPE_BOOL, 0, 3);
    kefir_irbuilder_block_append(mem, &dlesser->body, KEFIR_IROPCODE_F64LESSER, 0);

    KEFIR_CODEGEN_TRANSLATE(mem, &codegen.iface, &module);
    KEFIR_CODEGEN_CLOSE(&codegen.iface);
    REQUIRE_OK(kefir_ir_module_free(mem, &module));
    return EXIT_SUCCESS;
}