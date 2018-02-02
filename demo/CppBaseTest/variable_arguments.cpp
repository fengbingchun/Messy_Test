#include "variable_arguments.hpp"
#include <stdarg.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <initializer_list>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78483471

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

//////////////////////////////////////////////////
// reference: http://www.geeksforgeeks.org/variable-length-arguments-for-macros/
#define INFO 1
#define ERR 2
#define STD_OUT stdout
#define STD_ERR stderr

#define LOG_MESSAGE(prio, stream, msg, ...) do { \
	char *str; \
	if (prio == INFO) \
		str = "INFO"; \
	else if (prio == ERR) \
		str = "ERR"; \
	fprintf(stream, "[%s] : %s : %d : "msg" \n", \
			str, __FILE__, __LINE__, ##__VA_ARGS__); \
} while (0)

int test_variable_arguments_macro_2()
{
	char *s = "Hello";

	/* display normal message */
	LOG_MESSAGE(ERR, STD_ERR, "Failed to open file");

	/* provide string as argument */
	LOG_MESSAGE(INFO, STD_OUT, "%s Geeks for Geeks", s);

	/* provide integer as arguments */
	LOG_MESSAGE(INFO, STD_OUT, "%d + %d = %d", 10, 20, (10 + 20));

	return 0;
}

///////////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/ms177415.aspx
#define EMPTY

#define CHECK1(x, ...) if (!(x)) { printf(__VA_ARGS__); }
#define CHECK2(x, ...) if ((x)) { printf(__VA_ARGS__); }
#define CHECK3(...) { printf(__VA_ARGS__); }
#define MACRO(s, ...) printf(s, __VA_ARGS__)

int test_variable_arguments_macro_3()
{
	CHECK1(0, "here %s %s %s", "are", "some", "varargs1(1)\n");
	CHECK1(1, "here %s %s %s", "are", "some", "varargs1(2)\n");

	CHECK2(0, "here %s %s %s", "are", "some", "varargs2(3)\n");
	CHECK2(1, "here %s %s %s", "are", "some", "varargs2(4)\n");

	// always invokes printf in the macro
	CHECK3("here %s %s %s", "are", "some", "varargs3(5)\n");

	MACRO("hello, world\n");

	MACRO("error\n", EMPTY);

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

////////////////////////////////////////////////////////
template<typename T>
T sum(std::initializer_list<T> il)
{
	T data(0);
	for (T i : il)
		data += i;
	return data;
}

int test_variable_arguments_function_2()
{
	std::cout << sum({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }) << std::endl;
	return 0;
}

//////////////////////////////////////////////
// reference: https://stackoverflow.com/questions/41400/how-to-wrap-a-function-with-variable-length-arguments
void myprintf(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args); //  vprint, vsprintf, vfprintf: there are also 'safe' versions in Microsoft's C runtime that will prevent buffer overruns, etc.
	va_end(args);
}

int test_variable_arguments_function_3()
{
	int a = 9;
	int b = 10;
	char v = 'C';
	myprintf("This is a number: %d and \nthis is a character: %c and \n another number: %d\n", a, v, b);

	return 0;
}

//////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/fxhdxye9.aspx
//  ShowVar takes a format string of the form
//   "ifcs", where each character specifies the
//   type of the argument in that position.
//
//  i = int
//  f = float
//  c = char
//  s = string (char *)
//
//  Following the format specification is a variable
//  list of arguments. Each argument corresponds to
//  a format character in the format string to which
// the szTypes parameter points
void ShowVar(char* szTypes, ...)
{
	va_list vl;
	int i;

	//  szTypes is the last argument specified; you must access   
	//  all others using the variable-argument macros.  
	va_start(vl, szTypes);

	// Step through the list.  
	for (i = 0; szTypes[i] != '\0'; ++i) {
		union Printable_t {
			int     i;
			float   f;
			char    c;
			char   *s;
		} Printable;

		switch (szTypes[i]) {   // Type to expect.  
		case 'i':
			Printable.i = va_arg(vl, int);
			printf_s("%i\n", Printable.i);
			break;

		case 'f':
			Printable.f = va_arg(vl, double);
			printf_s("%f\n", Printable.f);
			break;

		case 'c':
			Printable.c = va_arg(vl, char);
			printf_s("%c\n", Printable.c);
			break;

		case 's':
			Printable.s = va_arg(vl, char *);
			printf_s("%s\n", Printable.s);
			break;

		default:
			break;
		}
	}
	va_end(vl);
}

int test_variable_arguments_function_4()
{
	ShowVar("fcsi", 32.4f, 'a', "Test string", 4);

	return 0;
}

//////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/cstdarg/va_arg/
int FindMax(int n, ...)
{
	int i, val, largest;
	va_list vl;
	va_start(vl, n);
	largest = va_arg(vl, int);
	for (i = 1; i<n; i++) {
		val = va_arg(vl, int);
		largest = (largest>val) ? largest : val;
	}
	va_end(vl);

	return largest;
}

int test_variable_arguments_function_5()
{
	int m;
	m = FindMax(7, 702, 422, 631, 834, 892, 104, 772);
	fprintf(stdout, "The largest value is: %d\n", m);

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

