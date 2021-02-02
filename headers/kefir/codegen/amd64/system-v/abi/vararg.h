#ifndef KEFIR_CODEGEN_AMD64_SYSTEM_V_ABI_VARARG_H_
#define KEFIR_CODEGEN_AMD64_SYSTEM_V_ABI_VARARG_H_

#include "kefir/ir/builtins.h"
#include "kefir/codegen/amd64/system-v/abi/data.h"
#include "kefir/codegen/amd64/system-v/abi/builtins.h"
#include "kefir/codegen/amd64/system-v/abi.h"
#include "kefir/codegen/amd64-sysv.h"

kefir_result_t kefir_codegen_amd64_sysv_vararg_instruction(struct kefir_mem *,
                                                struct kefir_codegen_amd64 *,
                                                struct kefir_codegen_amd64_sysv_module *,
                                                struct kefir_amd64_sysv_function *,
                                                const struct kefir_irinstr *);

#endif