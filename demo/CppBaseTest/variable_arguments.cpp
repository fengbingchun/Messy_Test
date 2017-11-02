#include "variable_arguments.hpp"
#include <stdarg.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

namespace variable_arguments_ {
///////////////////////////////////////////////////////////
#define LOG(...) { \
	fprintf(stderr, "%s: Line %d:\t", __FILE__, __LINE__); \
	fprintf(stderr, __VA_ARGS__); \
	fprintf(stderr, "\n"); \
}

int test_variable_arguments_macro_1()
{
	int value{ 5 };
	LOG("value = %d", value);

	return 0;
}

///////////////////////////////////////////////////////////////
static double SumOfFloat(int count, ...)
{
	va_list ap;
	double sum{ 0.f };
	va_start(ap, count);

	for (int i = 0; i < count; ++i) {
		sum += va_arg(ap, double);
	}

	va_end(ap);

	return sum;
}

int test_variable_arguments_function_1()
{
	fprintf(stdout, "sum: %f\n", SumOfFloat(3, 1.2f, -2.3f, 5.8f));

	return 0;
}

///////////////////////////////////////////////////////
// reference: 《深入理解C++11----C++11新特性解析与应用》 6.2
template <long... nums> struct Multiply;

template<long first, long... last>
struct Multiply<first, last...> {
	static const long val = first * Multiply<last...>::val;
};

template<>
struct Multiply<> {
	static const long val = 1;
};

int test_variable_arguments_template_class_1()
{
	fprintf(stdout, "%ld\n", Multiply<2, 3, 4, 5>::val); // 120
	fprintf(stdout, "%ld\n", Multiply<22, 44, 66, 88, 9>::val); // 50599296

	return 0;
}

///////////////////////////////////////////////////////////////////
void Printf(const char* s)
{
	while (*s) {
		if (*s == '%' && *++s != '%')
			throw std::runtime_error("invalid format string: missing arguments");
		std::cout << *s++;
	}
}

template<typename T, typename... Args>
void Printf(const char* s, T value, Args... args)
{
	while (*s) {
		if (*s == '%' && *++s != '%') {
			std::cout << value;
			return Printf(++s, args...);
		}

		std::cout << *s++;
	}

	throw std::runtime_error("extra arguments provided to Printf");
}

int test_variable_arguments_template_function_1()
{
	Printf("hello %s\n", std::string("world")); // hello world

	return 0;
}

/////////////////////////////////////////////////////////////
template<typename... T>
void DummyWrapper(T... t) {}

template<typename T>
T pr(T t)
{
	std::cout << t;
	return t;
}

template<typename... A>
void VTPrint(A... a)
{
	DummyWrapper(pr(a)...);
}

int test_variable_arguments_template_function_2()
{
	VTPrint(1, ", ", 1.2, ", abc\n");

	return 0;
}

/////////////////////////////////////////////////////////////
// 用来终止递归并打印最后一个元素的函数，此函数必须在可变参数版本的print定义之前声明
template<typename T>
std::ostream& print(std::ostream& os, const T& t)
{
	return os << t; // 包中最后一个元素之后不打印分隔符
}

// 包中除了最后一个元素之外的其它元素都会调用这个版本的print
template<typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& t, const Args&... rest)
{
	os << t << ", "; // 打印第一个字符
	return print(os, rest...); // 递归调用，打印其它实参
}

int test_variable_arguments_template_function_3()
{
	// 对于最后一个调用，两个函数提供同样好的匹配。但是，非可变参数模板比可变参数模板更
	// 特例化，因此编译器选择非可变参数版本
	char i{ 'A' }, s{ 'b' };
	print(std::cout, i, s, 42);

	// 当定义可变参数版本的print时，非可变参数版本的声明必须在作用域中，否则，可变参数版本会无限递归。

	return 0;
}

///////////////////////////////////////////////////////////
template<class... A>
void Print(A... arg)
{
	assert(false);
}

void Print(int a1, int a2, int a3, int a4, int a5, int a6)
{
	fprintf(stdout, "%d, %d, %d, %d, %d, %d\n", a1, a2, a3, a4, a5, a6);
}

template<class... A>
int Vaargs(A... args)
{
	int size = sizeof...(A);

	switch (size) {
	case 0: Print(99, 99, 99, 99, 99, 99);
		break;
	case 1: Print(99, 99, args..., 99, 99, 99);
		break;
	case 2: Print(99, 99, args..., 99, 99);
		break;
	case 3: Print(args..., 99, 99, 99);
		break;
	case 4: Print(99, args..., 99);
		break;
	case 5: Print(99, args...);
		break;
	case 6: Print(args...);
		break;
	default:
		Print(0, 0, 0, 0, 0, 0);
	}

	return size;
}

int test_variable_arguments_sizeof_1()
{
	Vaargs();
	Vaargs(1);
	Vaargs(1, 2);
	Vaargs(1, 2, 3);
	Vaargs(1, 2, 3, 4);
	Vaargs(1, 2, 3, 4, 5);
	Vaargs(1, 2, 3, 4, 5, 6);
	Vaargs(1, 2, 3, 4, 5, 6, 7);

	return 0;
}

} // namespace variable_arguments_

