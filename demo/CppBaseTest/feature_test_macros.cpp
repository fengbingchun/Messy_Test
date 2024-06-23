#include "feature_test_macros.hpp"
#include <iostream>
#include <version>

// Blog: https://blog.csdn.net/fengbingchun/article/details/139896405

int test_feature_test_macros()
{
	// language features
#ifdef __cpp_constexpr
	std::cout << "support constexpr" << std::endl;
#else
	std::cout << "Warning: unsupport constexpr" << std::endl;
#endif

#ifdef __cpp_structured_bindings
	std::cout << "support structured bindings" << std::endl;
#else
	std::cout << "Warning: unsupport structured bingdings" << std::endl;
#endif

#ifdef __cpp_consteval
	std::cout << "support consteval" << std::endl;
#else
	std::cout << "Warning: unsupport consteval" << std::endl;
#endif

#ifdef __cpp_aggregate_paren_init
	std::cout << "support aggregate paren init" << std::endl;
#else
	std::cout << "Warning: unsupport aggregate paren init" << std::endl;
#endif

	// library features
#ifdef __cpp_lib_ranges
	std::cout << "ranges library available" << std::endl;
#else
	std::cout << "Warning: ranges library unavailable" << std::endl;
#endif

#ifdef __cpp_lib_filesystem
	std::cout << "filesystem library available" << std::endl;
#else
	std::cout << "Warning: filesystme library unavailable" << std::endl;
#endif

#ifdef __cpp_lib_any
	std::cout << "any library available" << std::endl;
#else
	std::cout << "Warning: any library unavailable" << std::endl;
#endif

#ifdef __cpp_lib_fbc
	std::cout << "fbc library available" << std::endl;
#else
	std::cout << "Warning: fbc library unavailable" << std::endl;
#endif

	return 0;
}