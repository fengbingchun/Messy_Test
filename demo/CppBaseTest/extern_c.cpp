#include "extern_c.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78634831

namespace extern_c_ {
//////////////////////////////////////////////////////////
// reference: http://www.thegeekstuff.com/2013/01/mix-c-and-cpp/
int test_extern_c_1()
{
	tmp_f();
	return 0;
}

///////////////////////////////////////////////////////////////
// reference: https://stackoverflow.com/questions/1292138/when-to-use-extern-c-in-c
/*
	extern "C" makes names not mangled.
	It used when:

	1. We need to use some C library in C++
		extern "C" int foo(int);
	2. We need export some C++ code to C
		extern "C" int foo(int) { something; }
	3. We need an ability to resolve symbol in shared library -- so we need to get rid mangling
		extern "C" int foo(int) { something; }

		typedef int (*foo_type)(int);
		foo_type f = (foo_type)dlsym(handle,"foo")
*/

} // namespace extern_c_

