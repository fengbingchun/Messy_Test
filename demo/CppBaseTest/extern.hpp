#ifndef FBC_CPPBASE_TEST_EXTERN_HPP_
#define FBC_CPPBASE_TEST_EXTERN_HPP_

namespace extern_ {

extern const int bufsize; // 与.cpp中定义的bufsize是同一个

int test_extern_1();
int test_extern_2();

} // namespace extern_

#endif // FBC_CPPBASE_TEST_EXTERN_HPP_
