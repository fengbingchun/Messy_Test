#ifndef FBC_CPPBASE_TEST_TEST_LIBRARY_HPP_
#define FBC_CPPBASE_TEST_TEST_LIBRARY_HPP_

#ifdef _MSC_VER

#include "../Library/library.hpp"

namespace test_library_ {

#ifdef __cplusplus
	extern "C" {
#endif

__declspec(dllimport) int library_add(int, int);
__declspec(dllimport) int value;

#ifdef __cplusplus
	}
#endif

int test_library_1();
int test_library_2();
int test_library_3();
int test_library_4();

} // namespace test_library_

#endif

#endif // FBC_CPPBASE_TEST_TEST_LIBRARY_HPP_
