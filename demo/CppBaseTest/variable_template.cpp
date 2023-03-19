#include "variable_template.hpp"
#include <iostream>

// Blog: https://blog.csdn.net/fengbingchun/article/details/129648691

namespace {

// reference: https://en.cppreference.com/w/cpp/language/variable_template
template<class T>
constexpr T pi = T(3.1415926535897932385);  // variable template

template<class T>
T circular_area(T r) // function template
{
	return pi<T> * r * r; // pi<T> is a variable template instantiation
}

struct limits {
	template<typename T>
	static const T min; // declaration of a static data member template
};

template<typename T>
const T limits::min = { T(1.2) }; // definition of a static data member template

template<class T>
class X {
public:
	static T s; // declaration of a non-template static data member of a class template
};

template<class T>
T X<T>::s = 1.2; // definition of a non-template data member of a class template

// reference: https://www.anycodings.com/1questions/4931124/c14-variable-templates-what-is-their-purpose-any-usage-example
template<int N>
const int square = N * N;

template<typename T>
T n = T(5);

} // namespace

int test_variable_template()
{
	// 1. function template
	std::cout << "int value:" << circular_area(1) << "\n"; // int value:3
	std::cout << "float value:" << circular_area(1.f) << "\n"; // float value:3.14159

	// 2. static data member template
	std::cout << "int limits::min:" << limits::min<int> << "\n"; // int limits::min:1
	std::cout << "float limits::min:" << limits::min<float> << "\n"; // float limits::min:1.2

	std::cout << "int X::s:" << X<int>::s << "\n"; // int X::s:1
	std::cout << "float X::s:" << X<float>::s << "\n"; // float X::s:1.2

	// 3. compile time code
	std::cout << "square:" << square<5> << "\n"; // square:25

	// 4. it seems to instantiate the variables separately for the type
	n<int> = 10;
	std::cout << "n<int>:" << n<int> << "\n"; // n<int>:10
	std::cout << "n<float>:" << n<float> << "\n"; // n<float>:5

	return 0;
}
