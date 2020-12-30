#ifndef KEFIR_IR_FUNCTION_H_
#define KEFIR_IR_FUNCTION_H_

#include "kefir/core/basic-types.h"
#include "kefir/core/util.h"
#include "kefir/ir/type.h"
#include "kefir/ir/instr.h"

typedef struct kefir_ir_function_decl {
    const char *identifier;
    struct kefir_ir_type params;
    struct kefir_ir_type result;
} kefir_ir_function_decl_t;

typedef struct kefir_ir_function {
    struct kefir_ir_function_decl *declaration;
    struct kefir_irblock body;
} kefir_ir_function_t;

kefir_result_t kefir_ir_function_decl_alloc(struct kefir_mem *,
                                       const char *,
                                       kefir_size_t,
                                       kefir_size_t,
                                       struct kefir_ir_function_decl *);
kefir_result_t kefir_ir_function_decl_free(struct kefir_mem *,
                                      struct kefir_ir_function_decl *);

kefir_result_t kefir_ir_function_alloc(struct kefir_mem *,
                                  struct kefir_ir_function_decl *,
                                  kefir_size_t,
                                  struct kefir_ir_function *);
kefir_result_t kefir_ir_function_free(struct kefir_mem *, struct kefir_ir_function *);

#endif