#ifndef KEFIR_IR_BITFIELDS_H_
#define KEFIR_IR_BITFIELDS_H_

#include "kefir/core/basic-types.h"
#include "kefir/ir/type.h"
#include "kefir/ir/builder.h"

typedef struct kefir_ir_bitfield {
    kefir_size_t location;
    kefir_uint8_t offset;
    kefir_uint8_t width;
} kefir_ir_bitfield_t;

typedef struct kefir_ir_bitfield_allocator {
    kefir_result_t (*get_last_bitfield)(struct kefir_ir_bitfield_allocator *,
                                      const struct kefir_ir_bitfield **);
    kefir_result_t (*finalize)(struct kefir_mem *,
                             struct kefir_ir_bitfield_allocator *,
                             struct kefir_irbuilder_type *);
    kefir_result_t (*reset)(struct kefir_ir_bitfield_allocator *);
    kefir_result_t (*next)(struct kefir_mem *,
                         struct kefir_ir_bitfield_allocator *,
                         kefir_size_t,
                         struct kefir_ir_typeentry *,
                         uint8_t,
                         struct kefir_ir_bitfield *);
    kefir_result_t (*next_colocated)(struct kefir_mem *,
                                   struct kefir_ir_bitfield_allocator *,
                                   const struct kefir_ir_typeentry *,
                                   uint8_t,
                                   struct kefir_ir_bitfield *);
    kefir_result_t (*free)(struct kefir_mem *,
                         struct kefir_ir_bitfield_allocator *);

    void *payload;
} kefir_ir_bitfield_allocator_t;

#define KEFIR_IR_BITFIELD_ALLOCATOR_GET_LAST_BITFIELD(allocator, bitfield_p) \
    ((allocator)->get_last_bitfield((allocator), (bitfield_p)))
#define KEFIR_IR_BITFIELD_ALLOCATOR_FINALIZE(mem, allocator, builder) \
    ((allocator)->finalize((mem), (allocator), (builder)))
#define KEFIR_IR_BITFIELD_ALLOCATOR_RESET(allocator) \
    ((allocator)->reset((allocator)))
#define KEFIR_IR_BITFIELD_ALLOCATOR_NEXT(mem, allocator, index, typeentry, width, bitfield) \
    ((allocator)->next((mem), (allocator), (index), (typeentry), (width), (bitfield)))
#define KEFIR_IR_BITFIELD_ALLOCATOR_NEXT_COLOCATED(mem, allocator, typeentry, width, bitfield) \
    ((allocator)->next_colocated((mem), (allocator), (typeentry), (width), (bitfield)))
#define KEFIR_IR_BITFIELD_ALLOCATOR_FREE(mem, allocator) \
    ((allocator)->free((mem), (allocator)))

#endif