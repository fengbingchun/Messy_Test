#include "static_assert.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/51228813

void test_static_assert1()
{
	// static_assert �������������ռ䷶Χ�����ڱ�����֪������ void * �Ĵ�С����˿�������������ʽ
	//��static_assert����ȷ���������32λ��ƽ̨�Ͻ��У���֧��64λ��ƽ̨
	//static_assert(sizeof(void *) == 4, "64-bit code generation is not supported."); // sizeof(void *) = 8 ?
}

void test_static_assert2()
{
#ifdef _MSC_VER
	basic_string<char> bs;
#endif
}

void test_static_assert3()
{
	Foo::bar;
}

void test_static_assert4(int a)
{
	assert(a / 2 == 0);
}
