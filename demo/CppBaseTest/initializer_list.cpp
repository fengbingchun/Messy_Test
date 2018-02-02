#include "initializer_list.hpp"
#include <initializer_list>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Blog: http://blog.csdn.net/fengbingchun/article/details/77938005

///////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/initializer_list/initializer_list/
struct myclass {
	std::string str;
	myclass(std::initializer_list<int> args) {
		std::stringstream ss;
		std::initializer_list<int>::iterator it;  // same as: const int* it
		for (it = args.begin(); it != args.end(); ++it) ss << ' ' << *it;
		str = ss.str();
	}
};

template<class T>
struct simple_container {
	T * data;
	unsigned n;
	simple_container(std::initializer_list<int> args) {
		data = new T[args.size()];
		n = 0;
		for (T x : args) { data[n++] = x; }
	}
	T* begin() { return data; }
	T* end() { return data + n; }
};

template<class T>
void print_list(std::initializer_list<T> il)
{
	for (const T* it = std::begin(il); it != std::end(il); ++it) std::cout << ' ' << *it;
	std::cout << '\n';
}

int test_initializer_list_1()
{
{
	std::initializer_list<int> mylist;
	mylist = { 10, 20, 30 };
	std::cout << "mylist contains:";
	for (int x : mylist) std::cout << ' ' << x;
	std::cout << '\n';
}

{
	myclass myobject{ 10, 20, 30 };
	std::cout << "myobject contains:" << myobject.str << '\n';
}

{
	simple_container<int> myobject{ 10, 20, 30 };
	std::cout << "myobject contains:";
	for (int x : myobject) std::cout << ' ' << x;
	std::cout << '\n';
}

{
	print_list({ 10, 20, 30 });
}

{
	// 编译器从花括号(brace)封闭的、元素由逗号分隔开的初始化列表自动构造initializer_list模板类
	auto il = { 10, 20, 30 };
	for (auto i : il)
		std::cout << i << "    ";
	std::cout << std::endl;
}

	return 0;
}

////////////////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/utility/initializer_list
template <class T>
struct S {
	std::vector<T> v;
	S(std::initializer_list<T> l) : v(l) {
		std::cout << "constructed with a " << l.size() << "-element list\n";
	}
	void append(std::initializer_list<T> l) {
		v.insert(v.end(), l.begin(), l.end());
	}
	std::pair<const T*, std::size_t> c_arr() const {
		return{ &v[0], v.size() };  // copy list-initialization in return statement
		// this is NOT a use of std::initializer_list
	}
};

template <typename T>
void templated_fn(T) {}

int test_initializer_list_2()
{
	S<int> s = { 1, 2, 3, 4, 5 }; // copy list-initialization
	s.append({ 6, 7, 8 });      // list-initialization in function call

	std::cout << "The vector size is now " << s.c_arr().second << " ints:\n";

	for (auto n : s.v)
		std::cout << n << ' ';
	std::cout << '\n';

	std::cout << "Range-for over brace-init-list: \n";

	for (int x : {-1, -2, -3}) // the rule for auto makes this ranged-for work
		std::cout << x << ' ';
	std::cout << '\n';

	auto al = { 10, 11, 12 };   // special rule for auto

	std::cout << "The list bound to auto has size() = " << al.size() << '\n';

	//    templated_fn({1, 2, 3}); // compiler error! "{1, 2, 3}" is not an expression,
	// it has no type, and so T cannot be deduced
	templated_fn<std::initializer_list<int>>({ 1, 2, 3 }); // OK
	templated_fn<std::vector<int>>({ 1, 2, 3 });           // also OK

	return 0;
}
