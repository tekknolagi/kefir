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
#include "kefir/core/util.h"
#include "kefir/test/unit_test.h"

int preinc(int *);
int postinc(int *);
int predec(int *);
int postdec(int *);

int main(int argc, const char **argv) {
    UNUSED(argc);
    UNUSED(argv);
    for (int i = -100, a = i, b = i; i < 100; i++) {
        ASSERT(a == i);
        ASSERT(b == i);
        ASSERT(preinc(&a) == i + 1);
        ASSERT(postinc(&b) == i);
        ASSERT(a == i + 1);
        ASSERT(b == i + 1);
    }
    for (int i = 100, a = i, b = i; i > -100; i--) {
        ASSERT(a == i);
        ASSERT(b == i);
        ASSERT(predec(&a) == i - 1);
        ASSERT(postdec(&b) == i);
        ASSERT(a == i - 1);
        ASSERT(b == i - 1);
    }
    return EXIT_SUCCESS;
}
