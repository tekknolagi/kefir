/*
    SPDX-License-Identifier: GPL-3.0

    Copyright (C) 2020-2021  Jevgenijs Protopopovs

    This file is part of Kefir project.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3.

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

    kefir_id_t func_params, func_returns, locals_id;
    struct kefir_ir_type *sum_params = kefir_ir_module_new_type(mem, &module, 2, &func_params),
                         *sum_result = kefir_ir_module_new_type(mem, &module, 1, &func_returns);
    REQUIRE(sum_params != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE(sum_result != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function_decl *sum_decl =
        kefir_ir_module_new_function_declaration(mem, &module, "ldouble_sum", func_params, false, func_returns);
    REQUIRE(sum_decl != NULL, KEFIR_INTERNAL_ERROR);
    kefir_irbuilder_type_append_v(mem, sum_decl->params, KEFIR_IR_TYPE_LONG_DOUBLE, 0, 0);
    kefir_irbuilder_type_append_v(mem, sum_decl->params, KEFIR_IR_TYPE_LONG_DOUBLE, 0, 0);
    kefir_irbuilder_type_append_v(mem, sum_decl->result, KEFIR_IR_TYPE_LONG_DOUBLE, 0, 0);

    struct kefir_ir_type *decl_params = kefir_ir_module_new_type(mem, &module, 2, &func_params),
                         *decl_result = kefir_ir_module_new_type(mem, &module, 1, &func_returns),
                         *func_locals = kefir_ir_module_new_type(mem, &module, 0, &locals_id);
    REQUIRE(decl_params != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE(decl_result != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE(func_locals != NULL, KEFIR_INTERNAL_ERROR);
    struct kefir_ir_function_decl *decl =
        kefir_ir_module_new_function_declaration(mem, &module, "ldouble_sum_proxy", func_params, false, func_returns);
    REQUIRE(decl != NULL, KEFIR_INTERNAL_ERROR);

    struct kefir_ir_function *func = kefir_ir_module_new_function(mem, &module, decl, locals_id, 1024);
    REQUIRE(func != NULL, KEFIR_INTERNAL_ERROR);
    REQUIRE_OK(kefir_ir_module_declare_global(mem, &module, decl->name));
    kefir_irbuilder_type_append_v(mem, func->declaration->params, KEFIR_IR_TYPE_LONG_DOUBLE, 0, 0);
    kefir_irbuilder_type_append_v(mem, func->declaration->params, KEFIR_IR_TYPE_LONG_DOUBLE, 0, 0);
    kefir_irbuilder_type_append_v(mem, func->declaration->result, KEFIR_IR_TYPE_LONG_DOUBLE, 0, 0);

    kefir_irbuilder_block_appendi64(mem, &func->body, KEFIR_IROPCODE_INVOKE, sum_decl->id);

    KEFIR_CODEGEN_TRANSLATE(mem, &codegen.iface, &module);

    KEFIR_CODEGEN_CLOSE(&codegen.iface);
    REQUIRE_OK(kefir_ir_module_free(mem, &module));
    return EXIT_SUCCESS;
}
