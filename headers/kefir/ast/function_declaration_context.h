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

#ifndef KEFIR_AST_FUNCTION_DECLARATION_CONTEXT_H_
#define KEFIR_AST_FUNCTION_DECLARATION_CONTEXT_H_

#include "kefir/core/mem.h"
#include "kefir/core/symbol_table.h"
#include "kefir/core/list.h"
#include "kefir/ast/scope.h"
#include "kefir/ast/context.h"

typedef struct kefir_ast_function_declaration_context {
    struct kefir_ast_context context;

    const struct kefir_ast_context *parent;
    struct kefir_ast_identifier_flat_scope ordinary_scope;
    struct kefir_ast_identifier_flat_scope tag_scope;
} kefir_ast_function_declaration_context_t;

kefir_result_t kefir_ast_function_declaration_context_init(struct kefir_mem *, const struct kefir_ast_context *,
                                                           struct kefir_ast_function_declaration_context *);
kefir_result_t kefir_ast_function_declaration_context_free(struct kefir_mem *,
                                                           struct kefir_ast_function_declaration_context *);

#endif
