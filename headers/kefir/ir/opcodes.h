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

#ifndef KEFIR_IR_OPCODES_H_
#define KEFIR_IR_OPCODES_H_

#include "kefir/core/base.h"

// Do not edit this file. It is autogenerated. Edit resources/opcodes.xml instead.
typedef enum kefir_iropcode {
    KEFIR_IROPCODE_RESERVED = 0x0,
    KEFIR_IROPCODE_NOP = 0x01,
    KEFIR_IROPCODE_JMP = 0x02,
    KEFIR_IROPCODE_BRANCH = 0x03,
    KEFIR_IROPCODE_RET = 0x04,
    KEFIR_IROPCODE_INVOKE = 0x05,
    KEFIR_IROPCODE_INVOKEV = 0x06,
    KEFIR_IROPCODE_PUSHI64 = 0x10,
    KEFIR_IROPCODE_PUSHU64 = 0x11,
    KEFIR_IROPCODE_PUSHSTRING = 0x12,
    KEFIR_IROPCODE_POP = 0x13,
    KEFIR_IROPCODE_PICK = 0x14,
    KEFIR_IROPCODE_PUT = 0x15,
    KEFIR_IROPCODE_INSERT = 0x16,
    KEFIR_IROPCODE_XCHG = 0x17,
    KEFIR_IROPCODE_DROP = 0x18,
    KEFIR_IROPCODE_IADD = 0x20,
    KEFIR_IROPCODE_IADD1 = 0x21,
    KEFIR_IROPCODE_ISUB = 0x22,
    KEFIR_IROPCODE_IMUL = 0x23,
    KEFIR_IROPCODE_IDIV = 0x24,
    KEFIR_IROPCODE_IMOD = 0x25,
    KEFIR_IROPCODE_UDIV = 0x26,
    KEFIR_IROPCODE_UMOD = 0x27,
    KEFIR_IROPCODE_INEG = 0x28,
    KEFIR_IROPCODE_INOT = 0x29,
    KEFIR_IROPCODE_IAND = 0x2a,
    KEFIR_IROPCODE_IOR = 0x2b,
    KEFIR_IROPCODE_IXOR = 0x2c,
    KEFIR_IROPCODE_ILSHIFT = 0x2d,
    KEFIR_IROPCODE_IRSHIFT = 0x2e,
    KEFIR_IROPCODE_IARSHIFT = 0x2f,
    KEFIR_IROPCODE_IEQUALS = 0x30,
    KEFIR_IROPCODE_IGREATER = 0x31,
    KEFIR_IROPCODE_ILESSER = 0x32,
    KEFIR_IROPCODE_IABOVE = 0x33,
    KEFIR_IROPCODE_IBELOW = 0x34,
    KEFIR_IROPCODE_BAND = 0x35,
    KEFIR_IROPCODE_BOR = 0x36,
    KEFIR_IROPCODE_BNOT = 0x37,
    KEFIR_IROPCODE_TRUNCATE1 = 0x40,
    KEFIR_IROPCODE_EXTEND8 = 0x41,
    KEFIR_IROPCODE_EXTEND16 = 0x42,
    KEFIR_IROPCODE_EXTEND32 = 0x43,
    KEFIR_IROPCODE_OFFSETPTR = 0x50,
    KEFIR_IROPCODE_ELEMENTPTR = 0x51,
    KEFIR_IROPCODE_GETGLOBAL = 0x52,
    KEFIR_IROPCODE_GETLOCALS = 0x53,
    KEFIR_IROPCODE_LOAD8U = 0x54,
    KEFIR_IROPCODE_LOAD8I = 0x55,
    KEFIR_IROPCODE_LOAD16U = 0x56,
    KEFIR_IROPCODE_LOAD16I = 0x57,
    KEFIR_IROPCODE_LOAD24U = 0x58,
    KEFIR_IROPCODE_LOAD32U = 0x59,
    KEFIR_IROPCODE_LOAD32I = 0x5a,
    KEFIR_IROPCODE_LOAD40U = 0x5b,
    KEFIR_IROPCODE_LOAD48U = 0x5c,
    KEFIR_IROPCODE_LOAD56U = 0x5d,
    KEFIR_IROPCODE_LOAD64 = 0x5e,
    KEFIR_IROPCODE_LOADLD = 0x5f,
    KEFIR_IROPCODE_STORE8 = 0x60,
    KEFIR_IROPCODE_STORE16 = 0x61,
    KEFIR_IROPCODE_STORE24 = 0x62,
    KEFIR_IROPCODE_STORE32 = 0x63,
    KEFIR_IROPCODE_STORE40 = 0x64,
    KEFIR_IROPCODE_STORE48 = 0x65,
    KEFIR_IROPCODE_STORE56 = 0x66,
    KEFIR_IROPCODE_STORE64 = 0x67,
    KEFIR_IROPCODE_STORELD = 0x68,
    KEFIR_IROPCODE_BZERO = 0x69,
    KEFIR_IROPCODE_BCOPY = 0x6a,
    KEFIR_IROPCODE_EXTUBITS = 0x6b,
    KEFIR_IROPCODE_EXTSBITS = 0x6c,
    KEFIR_IROPCODE_INSERTBITS = 0x6d,
    KEFIR_IROPCODE_GETTHRLOCAL = 0x6e,
    KEFIR_IROPCODE_VARARG_START = 0x70,
    KEFIR_IROPCODE_VARARG_COPY = 0x71,
    KEFIR_IROPCODE_VARARG_GET = 0x72,
    KEFIR_IROPCODE_VARARG_END = 0x73,
    KEFIR_IROPCODE_ALLOCA = 0x74,
    KEFIR_IROPCODE_PUSHSCOPE = 0x75,
    KEFIR_IROPCODE_POPSCOPE = 0x76,
    KEFIR_IROPCODE_PUSHF32 = 0x80,
    KEFIR_IROPCODE_PUSHF64 = 0x81,
    KEFIR_IROPCODE_PUSHLD = 0x82,
    KEFIR_IROPCODE_F32ADD = 0x83,
    KEFIR_IROPCODE_F32SUB = 0x84,
    KEFIR_IROPCODE_F32MUL = 0x85,
    KEFIR_IROPCODE_F32DIV = 0x86,
    KEFIR_IROPCODE_F32NEG = 0x87,
    KEFIR_IROPCODE_F64ADD = 0x88,
    KEFIR_IROPCODE_F64SUB = 0x89,
    KEFIR_IROPCODE_F64MUL = 0x8a,
    KEFIR_IROPCODE_F64DIV = 0x8b,
    KEFIR_IROPCODE_F64NEG = 0x8c,
    KEFIR_IROPCODE_LDADD = 0x8d,
    KEFIR_IROPCODE_LDSUB = 0x8e,
    KEFIR_IROPCODE_LDMUL = 0x8f,
    KEFIR_IROPCODE_LDDIV = 0x90,
    KEFIR_IROPCODE_LDNEG = 0x91,
    KEFIR_IROPCODE_F32EQUALS = 0xa0,
    KEFIR_IROPCODE_F32GREATER = 0xa1,
    KEFIR_IROPCODE_F32LESSER = 0xa2,
    KEFIR_IROPCODE_F64EQUALS = 0xa3,
    KEFIR_IROPCODE_F64GREATER = 0xa4,
    KEFIR_IROPCODE_F64LESSER = 0xa5,
    KEFIR_IROPCODE_LDEQUALS = 0xa6,
    KEFIR_IROPCODE_LDGREATER = 0xa7,
    KEFIR_IROPCODE_LDLESSER = 0xa8,
    KEFIR_IROPCODE_LDTRUNC1 = 0xa9,
    KEFIR_IROPCODE_F32CINT = 0xb0,
    KEFIR_IROPCODE_F64CINT = 0xb1,
    KEFIR_IROPCODE_LDCINT = 0xb2,
    KEFIR_IROPCODE_INTCF32 = 0xb3,
    KEFIR_IROPCODE_INTCF64 = 0xb4,
    KEFIR_IROPCODE_INTCLD = 0xb5,
    KEFIR_IROPCODE_UINTCF32 = 0xb6,
    KEFIR_IROPCODE_UINTCF64 = 0xb7,
    KEFIR_IROPCODE_UINTCLD = 0xb8,
    KEFIR_IROPCODE_F32CF64 = 0xb9,
    KEFIR_IROPCODE_F32CLD = 0xba,
    KEFIR_IROPCODE_F64CF32 = 0xbb,
    KEFIR_IROPCODE_F64CLD = 0xbc,
    KEFIR_IROPCODE_LDCF32 = 0xbd,
    KEFIR_IROPCODE_LDCF64 = 0xbe
} kefir_iropcode_t;

#endif
