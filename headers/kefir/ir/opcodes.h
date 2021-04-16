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
    KEFIR_IROPCODE_INEG = 0x26,
    KEFIR_IROPCODE_INOT = 0x27,
    KEFIR_IROPCODE_IAND = 0x28,
    KEFIR_IROPCODE_IOR = 0x29,
    KEFIR_IROPCODE_IXOR = 0x2a,
    KEFIR_IROPCODE_ILSHIFT = 0x2b,
    KEFIR_IROPCODE_IRSHIFT = 0x2c,
    KEFIR_IROPCODE_IARSHIFT = 0x2d,
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
    KEFIR_IROPCODE_LOAD32U = 0x58,
    KEFIR_IROPCODE_LOAD32I = 0x59,
    KEFIR_IROPCODE_LOAD64 = 0x5a,
    KEFIR_IROPCODE_STORE8 = 0x5b,
    KEFIR_IROPCODE_STORE16 = 0x5c,
    KEFIR_IROPCODE_STORE32 = 0x5d,
    KEFIR_IROPCODE_STORE64 = 0x5e,
    KEFIR_IROPCODE_BZERO = 0x5f,
    KEFIR_IROPCODE_VARARG_START = 0x60,
    KEFIR_IROPCODE_VARARG_COPY = 0x61,
    KEFIR_IROPCODE_VARARG_GET = 0x62,
    KEFIR_IROPCODE_VARARG_END = 0x63,
    KEFIR_IROPCODE_PUSHF32 = 0x70,
    KEFIR_IROPCODE_PUSHF64 = 0x71,
    KEFIR_IROPCODE_F32ADD = 0x72,
    KEFIR_IROPCODE_F32SUB = 0x73,
    KEFIR_IROPCODE_F32MUL = 0x74,
    KEFIR_IROPCODE_F32DIV = 0x75,
    KEFIR_IROPCODE_F32NEG = 0x76,
    KEFIR_IROPCODE_F64ADD = 0x77,
    KEFIR_IROPCODE_F64SUB = 0x78,
    KEFIR_IROPCODE_F64MUL = 0x79,
    KEFIR_IROPCODE_F64DIV = 0x7a,
    KEFIR_IROPCODE_F64NEG = 0x7b,
    KEFIR_IROPCODE_F32EQUALS = 0x80,
    KEFIR_IROPCODE_F32GREATER = 0x81,
    KEFIR_IROPCODE_F32LESSER = 0x82,
    KEFIR_IROPCODE_F64EQUALS = 0x83,
    KEFIR_IROPCODE_F64GREATER = 0x84,
    KEFIR_IROPCODE_F64LESSER = 0x85,
    KEFIR_IROPCODE_F32CINT = 0x90,
    KEFIR_IROPCODE_F64CINT = 0x91,
    KEFIR_IROPCODE_INTCF32 = 0x92,
    KEFIR_IROPCODE_INTCF64 = 0x93,
    KEFIR_IROPCODE_UINTCF32 = 0x94,
    KEFIR_IROPCODE_UINTCF64 = 0x95,
    KEFIR_IROPCODE_F32CF64 = 0x96,
    KEFIR_IROPCODE_F64CF32 = 0x97
} kefir_iropcode_t;

#endif
