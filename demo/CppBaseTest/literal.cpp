#include "literal.hpp"
#include <iostream>
#include <typeinfo>

// Blog: https://blog.csdn.net/fengbingchun/article/details/131340606

int test_literal_17_1()
{
	char c1 = u8'A'; // C++17
	char c2[2] = u8"A";

	char u1 = 'A';          // 'A'
	char u2 = '\101';       // octal, 'A'
	char u3 = '\x41';       // hexadecimal, 'A'
	char u4 = '\u0041';     // \u UCN 'A'
	char u5 = '\U00000041'; // \U UCN 'A'

	return 0;
}

int test_literal_2()
{
	char c = 'a'; // 字符字面值
	char str[] = "hello world"; // 字符串字面值

	std::cout << "csdn address: "
		"https://blog.csdn.net/fengbingchun/;	"
		"github address: "
		"https://github.com/fengbingchun"<< std::endl;

	std::cout << "\12" << "\0" << "\115" << "\40" << "\x4d" << "\n";
	std::cout << "Hi \x4dO\115!\n"; // Hi MOM!
	std::cout << "\1154\n"; // M4
	//std::cout << "\x1234\n"; // error C2022: “4660”: 对字符来说太大

	auto x1 = L'a'; // 宽字符型字面值,类型是wchar_t
	auto x2 = u8"Hi"; // utf-8字符串字面值(utf-8用8位编码一个Unicode字符)
	auto x3 = U"Bei";
	std::cout << "x1 type:" << typeid(x1).name()
			  << ", x2 type:" << typeid(x2).name()
			  << ", x3 type:" << typeid(x3).name() << "\n"; // x1 type:wchar_t, x2 type:char const * __ptr64, x3 type:char32_t const * __ptr64

	return 0;
}

// Blog: https://blog.csdn.net/fengbingchun/article/details/131152441

int test_literal_14_1()
{
	auto v1 = 0b110;
	auto v2 = 0b1111'1111;
	auto v3 = 0B1111'1111;
	std::cout << "v1:" << v1 << ", v2:" << v2 <<", v3:" << v3 << "\n"; // v1:6, v2:255, v3:255
	std::cout << "v1 type:" << typeid(v1).name()
		      << ", v2 type:" << typeid(v2).name()
		      << ", v3 type:" << typeid(v3).name() << "\n"; // v1 type:int, v2 type:int, v3 type:int

	auto v4 = 0b10U;
	auto v5 = 0B10L;
	auto v6 = 0b0000'0010ULL;
	std::cout << "v4:" << v4 << ", v5:" << v5 << ", v6:" << v6 << "\n"; // v4:2, v5:2, v6:2
	std::cout << "v4 type:" << typeid(v4).name()
			  << ", v5 type:" << typeid(v5).name()
			  << ", v6 type:" << typeid(v6).name() << "\n"; // v4 type:unsigned int, v5 type:long, v6 type:unsigned __int64

	return 0;
}

int test_literal_1()
{
	int d = 42; // decimal notation
	int o = 052; // octal notation
	int x = 0x2a; // hexadecimal notation
	int X = 0X2A; // hexadecimal notation
	std::cout << "d:" << d << ", o:" << o << ", x:" << x << ", X:" << X << "\n"; // d:42, o:42, x:42, X:42

	auto v1 = 42U; // or 42u: 将从unsigned int, unsigned long和unsigned long long中选择能匹配的空间最小的一个作为其数据类型
	auto v2 = 42L; // or 42l: 字面值的类型至少是long
	auto v3 = 42UL; // or 42ul: 数据类型将根据具体数值情况或者取unsigned long,或者取unsigned long long
	std::cout << "v1:" << v1 << ", v2:" << v2 << ", v3:" << v3 << "\n"; // v1:42, v2:42, v3:42
	std::cout << "v1 type:" << typeid(v1).name() << ", v2 type:" << typeid(v2).name() << ", v3 type:" << typeid(v3).name() << "\n"; // v1 type:unsigned int, v2 type:long, v3 type:unsigned long

	return 0;
}
