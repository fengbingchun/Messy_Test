#ifndef FBC_MESSY_TEST_STATIC_ASSERT_HPP
#define FBC_MESSY_TEST_STATIC_ASSERT_HPP

#ifndef __cplusplus
	#error static_assert.hpp header must be compiled as C++
#endif

#include <type_traits>
#include <iosfwd>
#include <cassert>

// reference: https://msdn.microsoft.com/zh-cn/library/dd293588.aspx

// static_assert ���������෶Χ�� static_assert ��֤ģ������Ƿ�Ϊ�������� (POD) ���͡�
// �������������� static_assert ����ʱ������������������ constant-expression ������ֱ���� main() ��ʵ���� basic_string ��ģ��
#ifdef _MSC_VER
template <class CharT, class Traits = std::char_traits<CharT> >
class basic_string {
	static_assert(std::tr1::is_pod<CharT>::value, "Template argument CharT must be a POD type in class template basic_string");
	// ...
};
#endif

struct NonPOD {
	NonPOD(const NonPOD &) {}
	virtual ~NonPOD() {}
};

// reference: http://stackoverflow.com/questions/1647895/what-does-static-assert-do-and-what-would-you-use-it-for
class Foo
{
public:
	static const int bar = 5; // 3
};

static_assert(Foo::bar > 4, "Foo::bar is too small :(");


void test_static_assert1();
void test_static_assert2();
void test_static_assert3();
void test_static_assert4(int a);

#endif // FBC_MESSY_TEST_STATIC_ASSERT_HPP

