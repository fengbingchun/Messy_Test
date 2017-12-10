#ifndef FBC_CPPBASE_UNIVERSAL_HPP_
#define FBC_CPPBASE_UNIVERSAL_HPP_

#include <iostream>

#define CHECK(x) { \
if (x) {} \
	else { fprintf(stderr, "Check Failed: %s, file: %s, line: %d\n", #x, __FILE__, __LINE__); return -1; } \
}

#endif // FBC_CPPBASE_UNIVERSAL_HPP_

