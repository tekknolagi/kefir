/*
    SPDX-License-Identifier: GPL-3.0

    Copyright (C) 2020-2021  Jevgenijs Protopopovs

    This file is part of Sloked project.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdio.h>
#include "kefir/ir/function.h"
#include "kefir/ir/builder.h"
#include "kefir/ir/module.h"
#include "kefir/core/mem.h"
#include "kefir/core/util.h"
#include "kefir/codegen/amd64-sysv.h"

kefir_result_t kefir_int_test(struct kefir_mem *mem) {
    struct kefir_codegen_amd64 codegen;
    kefir_codegen_amd64_sysv_init(&codegen, stdout);

    struct kefir_ir_module module;
    REQUIRE_OK(kefir_ir_module_alloc(mem, &module));
    struct kefir_ir_type *decl_params = kefir_ir_module_new_type(mem, &module, 1, NULL),
                         *decl_result = kefir_ir_module_new_type(mem, &module, 1, NULL);
    struct kefir_ir_function_decl *decl =
        kefir_ir_module_new_function_declaration(mem, &module, "trunc1", decl_params, false, decl_result);
    REQUIRE(decl != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function *func = kefir_ir_module_new_function(mem, &module, decl, NULL, 2);
    REQUIRE(func != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE_OK(kefir_ir_module_declare_global(mem, &module, decl->name));
    kefir_irbuilder_type_append_v(mem, func->declaration->params, KEFIR_IR_TYPE_LONG, 0, 0);
    kefir_irbuilder_type_append_v(mem, func->declaration->result, KEFIR_IR_TYPE_BOOL, 0, 0);
    kefir_irbuilder_block_appendi64(mem, &func->body, KEFIR_IROPCODE_TRUNCATE1, 0);
    kefir_irbuilder_block_appendi64(mem, &func->body, KEFIR_IROPCODE_RET, 0);

    decl_params = kefir_ir_module_new_type(mem, &module, 1, NULL);
    decl_result = kefir_ir_module_new_type(mem, &module, 1, NULL);
    decl = kefir_ir_module_new_function_declaration(mem, &module, "extend8", decl_params, false, decl_result);
    REQUIRE(decl != NULL, KEFIR_INTERNAL_ERROR);
    func = kefir_ir_module_new_function(mem, &module, decl, NULL, 2);
    REQUIRE(func != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE_OK(kefir_ir_module_declare_global(mem, &module, decl->name));
    kefir_irbuilder_type_append_v(mem, func->declaration->params, KEFIR_IR_TYPE_LONG, 0, 0);
    kefir_irbuilder_type_append_v(mem, func->declaration->result, KEFIR_IR_TYPE_CHAR, 0, 0);
    kefir_irbuilder_block_appendi64(mem, &func->body, KEFIR_IROPCODE_EXTEND8, 0);
    kefir_irbuilder_block_appendi64(mem, &func->body, KEFIR_IROPCODE_RET, 0);

    decl_params = kefir_ir_module_new_type(mem, &module, 1, NULL);
    decl_result = kefir_ir_module_new_type(mem, &module, 1, NULL);
    decl = kefir_ir_module_new_function_declaration(mem, &module, "extend16", decl_params, false, decl_result);
    REQUIRE(decl != NULL, KEFIR_INTERNAL_ERROR);
    func = kefir_ir_module_new_function(mem, &module, decl, NULL, 2);
    REQUIRE(func != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE_OK(kefir_ir_module_declare_global(mem, &module, decl->name));
    kefir_irbuilder_type_append_v(mem, func->declaration->params, KEFIR_IR_TYPE_LONG, 0, 0);
    kefir_irbuilder_type_append_v(mem, func->declaration->result, KEFIR_IR_TYPE_SHORT, 0, 0);
    kefir_irbuilder_block_appendi64(mem, &func->body, KEFIR_IROPCODE_EXTEND16, 0);
    kefir_irbuilder_block_appendi64(mem, &func->body, KEFIR_IROPCODE_RET, 0);

    decl_params = kefir_ir_module_new_type(mem, &module, 1, NULL);
    decl_result = kefir_ir_module_new_type(mem, &module, 1, NULL);
    decl = kefir_ir_module_new_function_declaration(mem, &module, "extend32", decl_params, false, decl_result);
    REQUIRE(decl != NULL, KEFIR_INTERNAL_ERROR);
    func = kefir_ir_module_new_function(mem, &module, decl, NULL, 2);
    REQUIRE(func != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE_OK(kefir_ir_module_declare_global(mem, &module, decl->name));
    kefir_irbuilder_type_append_v(mem, func->declaration->params, KEFIR_IR_TYPE_LONG, 0, 0);
    kefir_irbuilder_type_append_v(mem, func->declaration->result, KEFIR_IR_TYPE_INT, 0, 0);
    kefir_irbuilder_block_appendi64(mem, &func->body, KEFIR_IROPCODE_EXTEND32, 0);
    kefir_irbuilder_block_appendi64(mem, &func->body, KEFIR_IROPCODE_RET, 0);
    KEFIR_CODEGEN_TRANSLATE(mem, &codegen.iface, &module);

    REQUIRE_OK(kefir_ir_module_free(mem, &module));
    KEFIR_CODEGEN_CLOSE(&codegen.iface);
    return EXIT_SUCCESS;
}
