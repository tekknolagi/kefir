#include <stdbool.h>
#include "kefir/core/error.h"
#include "kefir/core/util.h"
#include "kefir/codegen/util.h"
#include "kefir/codegen/amd64/system-v/abi/data_layout.h"
#include "kefir/codegen/amd64/system-v/abi/data.h"
#include "kefir/codegen/amd64/system-v/abi/vararg.h"

static kefir_result_t kefir_amd64_sysv_scalar_type_layout(kefir_ir_typecode_t typecode,
                                                      kefir_size_t *size_ptr,
                                                      kefir_size_t *alignment_ptr) {
    REQUIRE(size_ptr != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid size pointer"));
    REQUIRE(alignment_ptr != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid alignment pointer"));

    switch (typecode) {
        case KEFIR_IR_TYPE_BOOL:
        case KEFIR_IR_TYPE_CHAR:
        case KEFIR_IR_TYPE_INT8:
            *size_ptr = 1;
            *alignment_ptr = 1;
            break;

        case KEFIR_IR_TYPE_SHORT:
        case KEFIR_IR_TYPE_INT16:
            *size_ptr = 2;
            *alignment_ptr = 2;
            break;

        case KEFIR_IR_TYPE_INT:
        case KEFIR_IR_TYPE_INT32:
            *size_ptr = 4;
            *alignment_ptr = 4;
            break;

        case KEFIR_IR_TYPE_LONG:
        case KEFIR_IR_TYPE_WORD:
        case KEFIR_IR_TYPE_INT64:
            *size_ptr = 8;
            *alignment_ptr = 8;
            break;

        case KEFIR_IR_TYPE_BITS:
            return KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "IR bits type has variable width and alignment");

        default:
            return KEFIR_SET_ERROR(KEFIR_INTERNAL_ERROR,
                KEFIR_AMD64_SYSV_ABI_ERROR_PREFIX "Unexpectedly encountered non-integral type");
    }
    return KEFIR_OK;
}

static kefir_result_t visitor_not_supported(const struct kefir_ir_type *type,
                                            kefir_size_t index,
                                            const struct kefir_ir_typeentry *typeentry,
                                            void *payload) {
    UNUSED(type);
    UNUSED(index);
    UNUSED(typeentry);
    UNUSED(payload);
    return KEFIR_SET_ERROR(KEFIR_NOT_SUPPORTED, KEFIR_AMD64_SYSV_ABI_ERROR_PREFIX "Encountered not supported type code while traversing type");
}

struct compound_type_layout {
    struct kefir_ir_type_visitor *visitor;
    struct kefir_vector *vector;
    kefir_size_t offset;
    kefir_size_t max_alignment;
    kefir_size_t max_size;
    bool aggregate;
    bool aligned;
};

static kefir_result_t update_compound_type_layout(struct compound_type_layout *compound_type_layout,
                                       struct kefir_amd64_sysv_data_layout *data,
                                       const struct kefir_ir_typeentry *typeentry) {
    if (typeentry->alignment != 0) {
        data->aligned = typeentry->alignment >= data->alignment;
        data->alignment = typeentry->alignment;
    }
    if (compound_type_layout->aggregate) {
        compound_type_layout->offset = kefir_codegen_pad_aligned(compound_type_layout->offset, data->alignment);
    }
    compound_type_layout->max_alignment = MAX(compound_type_layout->max_alignment, data->alignment);
    compound_type_layout->max_size = MAX(compound_type_layout->max_size, data->size);
    if (compound_type_layout->aligned && !data->aligned) {
        compound_type_layout->aligned = false;
    }
    data->relative_offset = compound_type_layout->offset;
    if (compound_type_layout->aggregate) {
        compound_type_layout->offset += data->size;
    }
    return KEFIR_OK;
}

static kefir_result_t calculate_integer_layout(const struct kefir_ir_type *type,
                               kefir_size_t index,
                               const struct kefir_ir_typeentry *typeentry,
                               void *payload) {
    UNUSED(type);
    struct compound_type_layout *compound_type_layout = (struct compound_type_layout *) payload;
    ASSIGN_DECL_CAST(struct kefir_amd64_sysv_data_layout *, data,
        kefir_vector_at(compound_type_layout->vector, index));
    
    if (typeentry->typecode != KEFIR_IR_TYPE_BITS) {
        REQUIRE_OK(kefir_amd64_sysv_scalar_type_layout(typeentry->typecode, &data->size, &data->alignment));
    } else {
        kefir_ir_typecode_t base;
        kefir_size_t bits = 0;
        kefir_size_t pad = 0;
        KEFIR_IR_BITS_PARAM_GET(typeentry->param, &base, &bits, &pad);

        kefir_size_t bitwidth = pad + bits;
        kefir_size_t size = bitwidth / 8 + (bitwidth % 8 != 0 ? 1 : 0);

        kefir_size_t base_size = 0;
        kefir_size_t base_alignment = 0;
        REQUIRE_OK(kefir_amd64_sysv_scalar_type_layout(base, &base_size, &base_alignment));
        REQUIRE(bitwidth <= base_size * 8, KEFIR_SET_ERROR(KEFIR_OUT_OF_BOUNDS, "IR bits field width exceeds base type"));

        kefir_size_t current_offset = compound_type_layout->offset;
        kefir_size_t unit_end = current_offset + base_size;
        unit_end -= unit_end % base_alignment;

        data->size = size;
        if (size <= unit_end - current_offset) {
            // Bitfield fits into current unit
            data->alignment = 1;
            compound_type_layout->max_alignment = MAX(compound_type_layout->max_alignment, base_alignment);
        } else {
            // New unit shall be allocated
            data->alignment = base_alignment;
        }
    }
    data->aligned = true;
    return update_compound_type_layout(compound_type_layout, data, typeentry);
}

static kefir_result_t calculate_sse_layout(const struct kefir_ir_type *type,
                               kefir_size_t index,
                               const struct kefir_ir_typeentry *typeentry,
                               void *payload) {
    UNUSED(type);
    struct compound_type_layout *compound_type_layout = (struct compound_type_layout *) payload;
    ASSIGN_DECL_CAST(struct kefir_amd64_sysv_data_layout *, data,
        kefir_vector_at(compound_type_layout->vector, index));
    switch (typeentry->typecode) {
        case KEFIR_IR_TYPE_FLOAT32:
            data->size = 4;
            data->alignment = 4;
            break;

        case KEFIR_IR_TYPE_FLOAT64:
            data->size = 8;
            data->alignment = 8;
            break;

        default:
            return KEFIR_SET_ERROR(KEFIR_INTERNAL_ERROR,
                KEFIR_AMD64_SYSV_ABI_ERROR_PREFIX "Unexpectedly encountered non-floating point type");
    }
    data->aligned = true;
    return update_compound_type_layout(compound_type_layout, data, typeentry);
}

static kefir_result_t calculate_amorphous_layout(const struct kefir_ir_type *type,
                               kefir_size_t index,
                               const struct kefir_ir_typeentry *typeentry,
                               void *payload) {
    UNUSED(type);
    struct compound_type_layout *compound_type_layout = (struct compound_type_layout *) payload;
    ASSIGN_DECL_CAST(struct kefir_amd64_sysv_data_layout *, data,
        kefir_vector_at(compound_type_layout->vector, index));
    
    switch (typeentry->typecode) {
        case KEFIR_IR_TYPE_PAD:
            data->size = typeentry->param;
            data->alignment = 1;
            break;

        case KEFIR_IR_TYPE_MEMORY:
            data->size = typeentry->param;
            data->alignment = 1;
            break;

        case KEFIR_IR_TYPE_ALIGN:
            data->size = 0;
            data->alignment = 1;
            compound_type_layout->max_alignment = MAX(compound_type_layout->max_alignment, (kefir_size_t) typeentry->param);
            break;

        default:
            return KEFIR_SET_ERROR(KEFIR_INTERNAL_ERROR,
                KEFIR_AMD64_SYSV_ABI_ERROR_PREFIX "Unexpectedly encountered structured type");
    }
    data->aligned = true;
    return update_compound_type_layout(compound_type_layout, data, typeentry);
}

static kefir_result_t calculate_struct_union_layout(const struct kefir_ir_type *type,
                               kefir_size_t index,
                               const struct kefir_ir_typeentry *typeentry,
                               void *payload) {
    struct compound_type_layout *compound_type_layout = (struct compound_type_layout *) payload;
    ASSIGN_DECL_CAST(struct kefir_amd64_sysv_data_layout *, data,
        kefir_vector_at(compound_type_layout->vector, index));
    struct compound_type_layout nested_compound_type_layout = {
        .visitor = compound_type_layout->visitor,
        .vector = compound_type_layout->vector,
        .offset = 0,
        .max_alignment = 0,
        .max_size = 0,
        .aggregate = typeentry->typecode == KEFIR_IR_TYPE_STRUCT,
        .aligned = true
    };
    REQUIRE_OK(kefir_ir_type_visitor_list_nodes(type,
        compound_type_layout->visitor, (void *) &nested_compound_type_layout, index + 1, typeentry->param));
    data->alignment = nested_compound_type_layout.max_alignment;
    data->aligned = nested_compound_type_layout.aligned;
    data->size = kefir_codegen_pad_aligned(
        typeentry->typecode == KEFIR_IR_TYPE_STRUCT
            ? nested_compound_type_layout.offset
            :  nested_compound_type_layout.max_size,
        data->alignment
    );
    return update_compound_type_layout(compound_type_layout, data, typeentry);
}

static kefir_result_t calculate_array_layout(const struct kefir_ir_type *type,
                               kefir_size_t index,
                               const struct kefir_ir_typeentry *typeentry,
                               void *payload) {
    struct compound_type_layout *compound_type_layout = (struct compound_type_layout *) payload;
    ASSIGN_DECL_CAST(struct kefir_amd64_sysv_data_layout *, data,
        kefir_vector_at(compound_type_layout->vector, index));
    struct compound_type_layout nested_compound_type_layout = {
        .visitor = compound_type_layout->visitor,
        .vector = compound_type_layout->vector,
        .offset = 0,
        .max_alignment = 0,
        .max_size = 0,
        .aggregate = false,
        .aligned = true
    };
    REQUIRE_OK(kefir_ir_type_visitor_list_nodes(type,
        compound_type_layout->visitor, (void *) &nested_compound_type_layout, index + 1, 1));
    data->alignment = nested_compound_type_layout.max_alignment;
    data->aligned = nested_compound_type_layout.aligned;
    data->size = nested_compound_type_layout.max_size * typeentry->param;
    return update_compound_type_layout(compound_type_layout, data, typeentry);
}


static kefir_result_t calculate_builtin_layout(const struct kefir_ir_type *type,
                               kefir_size_t index,
                               const struct kefir_ir_typeentry *typeentry,
                               void *payload) {
    UNUSED(type);
    struct compound_type_layout *compound_type_layout = (struct compound_type_layout *) payload;
    ASSIGN_DECL_CAST(struct kefir_amd64_sysv_data_layout *, data,
        kefir_vector_at(compound_type_layout->vector, index));
    kefir_ir_builtin_type_t builtin = (kefir_ir_builtin_type_t) typeentry->param;
    REQUIRE(builtin < KEFIR_IR_TYPE_BUILTIN_COUNT, KEFIR_SET_ERROR(KEFIR_INTERNAL_ERROR, "Unknown built-in type"));
    const struct kefir_codegen_amd64_sysv_builtin_type *builtin_type =
        KEFIR_CODEGEN_AMD64_SYSV_BUILTIN_TYPES[builtin];
    REQUIRE_OK(builtin_type->layout(builtin_type, typeentry, data));
    return update_compound_type_layout(compound_type_layout, data, typeentry);
}

static kefir_result_t calculate_layout(const struct kefir_ir_type *type,
                                     kefir_size_t index,
                                     kefir_size_t count,
                                     struct kefir_vector *vector) {
    struct kefir_ir_type_visitor visitor;
    struct compound_type_layout compound_type_layout = {
        .visitor = &visitor,
        .vector = vector,
        .offset = 0,
        .max_alignment = 0,
        .max_size = 0,
        .aggregate = true,
        .aligned = true
    };
    REQUIRE_OK(kefir_ir_type_visitor_init(&visitor, visitor_not_supported));
    KEFIR_IR_TYPE_VISITOR_INIT_INTEGERS(&visitor, calculate_integer_layout);
    KEFIR_IR_TYPE_VISITOR_INIT_FIXED_FP(&visitor, calculate_sse_layout);
    visitor.visit[KEFIR_IR_TYPE_PAD] = calculate_amorphous_layout;
    visitor.visit[KEFIR_IR_TYPE_ALIGN] = calculate_amorphous_layout;
    visitor.visit[KEFIR_IR_TYPE_MEMORY] = calculate_amorphous_layout;
    visitor.visit[KEFIR_IR_TYPE_STRUCT] = calculate_struct_union_layout;
    visitor.visit[KEFIR_IR_TYPE_UNION] = calculate_struct_union_layout;
    visitor.visit[KEFIR_IR_TYPE_ARRAY] = calculate_array_layout;
    visitor.visit[KEFIR_IR_TYPE_BUILTIN] = calculate_builtin_layout;
    return kefir_ir_type_visitor_list_nodes(type, &visitor,
        (void *) &compound_type_layout, index, count);
}

kefir_result_t kefir_amd64_sysv_type_layout_of(struct kefir_mem *mem,
                                           const struct kefir_ir_type *type,
                                           kefir_size_t index,
                                           kefir_size_t count,
                                           struct kefir_vector *layout) {
    REQUIRE(type != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid IR type"));
    REQUIRE(mem != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid memory allocator"));
    REQUIRE(layout != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid layout vector"));

    const kefir_size_t length = kefir_ir_type_total_length(type);
    REQUIRE_OK(kefir_vector_alloc(mem,
                                sizeof(struct kefir_amd64_sysv_data_layout),
                                length,
                                layout));
    kefir_result_t res = kefir_vector_extend(layout, length);
    REQUIRE_ELSE(res == KEFIR_OK, {
        kefir_vector_free(mem, layout);
        return res;
    });
    res = calculate_layout(type, index, count, layout);
    REQUIRE_ELSE(res == KEFIR_OK, {
        kefir_vector_free(mem, layout);
        return res;
    });
    return KEFIR_OK;
}

kefir_result_t kefir_amd64_sysv_type_layout(const struct kefir_ir_type *type,
                                        struct kefir_mem *mem,
                                        struct kefir_vector *layout) {
    REQUIRE(type != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid IR type"));
    REQUIRE(mem != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid memory allocator"));
    REQUIRE(layout != NULL, KEFIR_SET_ERROR(KEFIR_MALFORMED_ARG, "Expected valid layout vector"));
    
    REQUIRE_OK(kefir_amd64_sysv_type_layout_of(mem, type, 0, kefir_ir_type_nodes(type), layout));
    return KEFIR_OK;
}