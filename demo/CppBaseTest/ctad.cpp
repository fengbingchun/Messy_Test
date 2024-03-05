#include "ctad.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <mutex>

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
