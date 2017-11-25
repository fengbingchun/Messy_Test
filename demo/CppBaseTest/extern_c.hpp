#ifndef FBC_CPPBASE_EXTERN_C_HPP_
#define FBC_CPPBASE_EXTERN_C_HPP_

namespace extern_c_ {

// the first method
#ifdef __cplusplus
extern "C" {
#include "c_head.h"
}
#endif

// the second method
//extern "C" void tmp_f(void);

int test_extern_c_1();

} // namespace extern_c_


#endif // FBC_CPPBASE_EXTERN_C_HPP_

