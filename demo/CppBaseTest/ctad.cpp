#include "ctad.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <mutex>
#include <array>

// Blog: https://blog.csdn.net/fengbingchun/article/details/136631451
namespace {

template<int num> // declare a non-type template parameter of type int named num
void print() { std::cout << "num: " << num << "\n"; }

// C++17之前
template <typename Type, Type value>
constexpr Type constant = value;
constexpr auto const int_constant_88 = constant<int, 88>;
constexpr auto const char_constant_y = constant<char, 'Y'>;

// C++17
template <auto value> // 不再需要明确地拼写类型
constexpr auto constant2 = value;
constexpr auto const int_constant2_88 = constant2<88>;
constexpr auto const char_constant2_y = constant2<'Y'>;

template<auto value>
void print_value() { std::cout << "value: " << value << "\n"; }

template<const auto* P> // 可以修饰auto, 例如,可以确保参数类型必须是个指针
struct S {};

// reference: https://github.com/MeouSker77/Cpp17/blob/master/markdown/src/ch13.md
// 定义一个既可能是字符也可能是字符串的模板参数
template<auto Sep = ' ', typename First, typename... Args>
void print(const First& first, const Args&... args)
{
	std::cout << first;
	auto outWithSep = [](const auto& arg) {
		std::cout << Sep << arg;
	};
	(..., outWithSep(args));
	std::cout << '\n';
}

// 定义编译期常量
template<auto v>
struct constant3
{
	static constexpr auto value = v;
};

using i = constant3<88>;
using c = constant3<'Y'>;
using b = constant3<true>;

// 使用auto作为变量模板的参数
template<typename T, auto N> std::array<T, N> arr;

void print_arr()
{
	std::cout << "arr<int, 5>:  ";
	for (const auto& elem : arr<int, 5>) {
		std::cout << elem << ' ';
	}

	std::cout << "\narr<int, 5u>: ";
	for (const auto& elem : arr<int, 5u>) {
		std::cout << elem << ' ';
	}
	std::cout << '\n';
}

} // namespace

int test_template_argument_auto()
{
	print<88>(); // num: 88


	std::cout << "constant: " << int_constant_88 << ", " << char_constant_y << "\n"; // constant: 88, Y
	std::cout << "constant2: " << int_constant2_88 << ", " << char_constant2_y << "\n"; // constant2: 88, Y

	print_value<88>(); // value: 88
	print_value<'Y'>(); // value: Y


	const std::string s{ "world" };
	print(7.5, "hello", s); // 7.5 hello world

	print<'-'>(7.5, "hello", s); // 7.5-hello-world
	print<-11>(7.5, "hello", s); // 7.5-11hello-11world

	static const char sep[] = ", ";
	print<sep>(7.5, "hello", s); // 7.5, hello, world

	std::cout << "i: " << i::value << ", c: " << c::value << ", b: " << b::value << "\n"; // i: 88, c: Y, b: 1


	arr<int, 5>[0] = 17;
	arr<int, 5>[3] = 42;
	arr<int, 5u>[1] = 11;
	arr<int, 5u>[3] = 33;
	print_arr(); // arr<int, 5>:  17 0 0 42 0
				 // arr<int, 5u>: 0 11 0 33 0

	return 0;
}

/////////////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/136484544
namespace {

template<typename T>
class Foo {
public:
	Foo(T value)
	{
		std::cout << "Created Foo, type id: " << typeid(T).name() << ", value: " << value << "\n";
	}
};

template<typename T>
class Foo2 {
public:
	Foo2(T value)
	{
		std::cout << "Created Foo2, type id: " << typeid(T).name() << ", value: " << value << "\n";
	}
};

// User-defined deduction guide 
template<typename T> Foo2(T)->Foo2<T>;

template<typename T> using MyAlias = T;

template<typename T>
class Foo3 {
public:
	Foo3(const std::initializer_list<T>& list) : vec_(list) {}
	void print() const
	{
		for (const auto& val : vec_) {
			std::cout << val << " ";
		}
		std::cout << "\n";
	}

private:
	std::vector<T> vec_;
};

} // namespace

int test_ctad()
{
	// 只要能根据初始值推导出所有模板参数就可以使用类模板参数推导
	// 推导过程支持所有方式的初始化(只要保证初始化是有效的)
	std::pair p(2, 4.5);     // deduces to std::pair<int, double> p(2, 4.5);
	std::tuple t(4, 3, 2.5); // same as auto t = std::make_tuple(4, 3, 2.5);
	std::complex c{ 5.1, 3.3 }; // std::complex<double>
	std::mutex mx;
	std::lock_guard lg{ mx }; // std::lock_guard<std::mutex>
	std::vector vec{ "hello", "world" }; // std::vector<const char*>

	std::vector v1{ 42 };
	std::vector v2{ v1 }; // v2也是一个std::vector<int>,这是花括号初始化总是把列表中的参数作为元素这一规则的一个例外
	// 然而,如果用多于一个元素的初值列来初始化的话,就会把传入的参数作为元素并推导出其类型作为模板参数
	std::vector vv{ v1, v2 }; // vv是一个vector<vector<int>>


	// 1.Class Template Argument Deduction(CTAD)
	// not specifying the type of the template
	auto foo11 = Foo(88); // Created Foo, type id: int, value: 88
	auto foo12 = Foo("Beijing"); // Created Foo, type id: char const * __ptr64, value: Beijing

	// specifying the type of the template
	Foo<int> foo21(88); // Created Foo, type id: int, value: 88
	Foo<const char*> foo22("Beijing"); // Created Foo, type id: char const * __ptr64, value: Beijing


	// 2.User-defined deduction guides
	// not specifying the type of the template
	auto foo31 = Foo2(88); // Created Foo2, type id: int, value: 88
	auto foo32 = Foo2("Beijing"); // Created Foo2, type id: char const * __ptr64, value: Beijing


	// 3.the deduction for alias templates
	MyAlias<int> alias1{ 88 };
	MyAlias<std::string> alias2{ "Beijing" };

	std::cout << "alias1: " << alias1 << "\n"; // alias1: 88
	std::cout << "alias2: " << alias2 << "\n"; // alias2: Beijing

	// reference: https://www.geeksforgeeks.org/class-template-argument-deduction-in-cpp-17/
	auto foo41 = Foo3({ 1, 2, 3, 4, 5 });
	foo41.print(); // 1 2 3 4 5

	return 0;
}
