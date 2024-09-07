#include <iostream>
#include <string>
#include <stdexcept>
#include "template.hpp"

// Blog: https://blog.csdn.net/fengbingchun/article/details/141994463
namespace {
template<int N> // int non-type template parameter
struct Array {
	static_assert(N > 0, "N must be greater than 0");
	int data[N];
};

template<float v> // c++20
void print_value()
{
	static_assert(v < 0, "v must be less than 0");
	std::cout << "v: " << v << std::endl;
}

// literal class type
struct Foo {
	constexpr Foo() {}
	constexpr Foo(int value): has_value(true), value(value) {}

	const int value{};
	const bool has_value{ false };
};

template <Foo f> // c++20
void print_foo() {
	if constexpr (f.has_value)
		std::cout << "value: " << f.value << std::endl;
	else
		std::cout << "no value" << std::endl;
}

} // namespace

int test_template_20()
{
	Array<5> arr;
	arr.data[3] = {6};
	std::cout << "arr[3]: " << arr.data[3] << std::endl;

	print_value<-1.1f>();

	print_foo < Foo{ 66 } > ();
	print_foo < Foo{} > ();

	return 0;
}

/////////////////////////////////////////////////////////////////
// Blog: http://blog.csdn.net/fengbingchun/article/details/51339659
void test_template1()
{
	int a = 3, b = 7;
	float x = 3.0, y = 7.0;
	//Calling template function
	std::cout << maximum<int>(a, b) << std::endl; //输出 7
	std::cout << maximum(a, b) << std::endl; //自动补充类型声明,输出 7
	std::cout << maximum<double>(x, y) << std::endl; //输出 7
}

void test_template2()
{
	int i = 39;
	int j = 20;
	std::cout << "Max(i, j): " << Max(i, j) << std::endl;

	double f1 = 13.5;
	double f2 = 20.7;
	std::cout << "Max(f1, f2): " << Max(f1, f2) << std::endl;

	std::string s1 = "Hello";
	std::string s2 = "World";
	std::cout << "Max(s1, s2): " << Max(s1, s2) << std::endl;
}

void test_template3()
{
	try {
		Stack<int>         intStack;  // stack of ints 
		Stack<std::string> stringStack;    // stack of strings 

		// manipulate int stack 
		intStack.push(7);
		std::cout << intStack.top() << std::endl;

		// manipulate string stack 
		stringStack.push("hello");
		std::cout << stringStack.top() << std::endl;
		stringStack.pop();
		//stringStack.pop();
	} catch (std::exception const& ex) {
		std::cerr << "Exception: " << ex.what() << std::endl;
		return;
	}
}

void test_template4()
{
	pair <int> myints(100, 75);
	pair <float> myfloats(100.0, 75.0);

	std::cout << myints.module() << std::endl;
	std::cout << myfloats.module() << std::endl;
}

void test_template5()
{
	PrintType<int> type_int;
	std::cout << type_int.type()<<std::endl;

	PrintType<float> type_float;
	std::cout << type_float.type() << std::endl;

	PrintType<std::string> type_string;
	std::cout << type_string.type() << std::endl;
}

void test_template6()
{
	int ret = 0, a = 5, b = 7;
	ret = max_mum(a, b);
	std::cout << ret << std::endl;
}

void test_template7()
{
	A<int> a;
	a.f();
}

