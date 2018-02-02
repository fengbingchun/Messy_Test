#include "static_inline.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/51234209

void test_static_inline1()
{
	float a = 4.1, b = 4.9;

	FastMath math;
	int ret1 = math.round(a);
	int ret2 = math.floor(a);
	int ret3 = math.round(b);
	int ret4 = math.floor(b);

	std::cout << ret1 << "   " << ret2 << "    " << ret3 << "    " << ret4 << std::endl;
}

void test_static_inline2()
{
	float a = 4.1, b = 4.9;

	int ret1 = Ceil(a);
	int ret2 = Ceil(b);

	std::cout << ret1 << "    " << ret2 << "    " << std::endl;
}

