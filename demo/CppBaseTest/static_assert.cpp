#include "static_assert.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/51228813

void test_static_assert1()
{
	// static_assert 声明具有命名空间范围。由于编译器知道类型 void * 的大小，因此可以立即计算表达式
	//该static_assert用来确保编译仅在32位的平台上进行，不支持64位的平台
	//static_assert(sizeof(void *) == 4, "64-bit code generation is not supported."); // sizeof(void *) = 8 ?
}

void test_static_assert2()
{
	basic_string<char> bs;
}

void test_static_assert3()
{
	Foo::bar;
}

void test_static_assert4(int a)
{
	assert(a / 2 == 0);
}
