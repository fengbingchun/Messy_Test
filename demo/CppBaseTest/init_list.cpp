#include "init_list.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52505504

///////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/list_initialization
struct Foo {
	//std::vector<int> mem = { 1, 2, 3 }; // list-initialization of a non-static member
	//std::vector<int> mem2;
	//Foo() : mem2{ -1, -2, -3 } {} // list-initialization of a member in constructor
};

std::pair<std::string, std::string> f(std::pair<std::string, std::string> p)
{
	return{ p.second, p.first }; // list-initialization in return statement
}

int test_init_list1()
{
	int n0{};     // value-initialization (to zero)
	int n1{ 1 };    // direct-list-initialization
	std::string s1{ 'a', 'b', 'c', 'd' }; // initializer-list constructor call
	std::string s2{ s1, 2, 2 };           // regular constructor call
	std::string s3{ 0x61, 'a' }; // initializer-list ctor is preferred to (int, char)

	int n2 = { 1 }; // copy-list-initialization
	double d = double{ 1.2 }; // list-initialization of a temporary, then copy-init

	std::map<int, std::string> m = { // nested list-initialization
			{ 1, "a" },
			{ 2, { 'a', 'b', 'c' } },
			{ 3, s1 }
	};

	std::cout << f({ "hello", "world" }).first << '\n'; // list-initialization in function call

	const int(&ar)[2] = { 1, 2 }; // binds a lvalue reference to a temporary array
	int&& r1 = { 1 }; // binds a rvalue reference to a temporary int
	//  int& r2 = {2}; // error: cannot bind rvalue to a non-const lvalue ref

	//  int bad{1.0}; // error: narrowing conversion
	unsigned char uc1{ 10 }; // okay
	//  unsigned char uc2{-1}; // error: narrowing conversion

	Foo f;

	std::cout << n0 << ' ' << n1 << ' ' << n2 << '\n'
		<< s1 << ' ' << s2 << ' ' << s3 << '\n';
	for (auto p : m)
		std::cout << p.first << ' ' << p.second << '\n';
	//for (auto n : f.mem)
	//	std::cout << n << ' ';
	//for (auto n : f.mem2)
	//	std::cout << n << ' ';

	return 0;
}

////////////////////////////////////////////
// reference: https://mbevin.wordpress.com/2012/11/16/uniform-initialization/
int test_init_list2()
{
	int arr[]          { 1, 2, 3, 4, 5 };
	std::vector<int> v{ 1, 2, 3, 4, 5 };
	std::set<int> s{ 1, 2, 3, 4, 5 };
	std::map<int, std::string> m{ { 0, "zero" }, { 1, "one" }, { 2, "two" } };

	return 0;
}

///////////////////////////////////////////////////////
// reference: https://mbevin.wordpress.com/2012/11/16/uniform-initialization/
// 'aggregate' class - no user-declared constructor, no private/protected members, no base, no virtual function
struct ClassA {
	int x;
	double y;
};

// non-aggregate class
class ClassB {
private:
	int x;
	double y;
public:
	ClassB(int _x, double _y) :x(_x), y(_y) {}
};

std::pair<double, double> multiplyVectors(
	std::pair<double, double> v1,
	std::pair<double, double> v2) {
	return{ v1.first*v2.first, v1.second*v2.second };
}

int test_init_list3()
{
	int i{ 3 };
	int j{}; // empty braces initialize the object to it's default (0)
	std::string s{ "hello" };

	ClassA objA1{};
	ClassA objA2{ 1, 2.0 };
	ClassB objB1{ 1, 2.0 };
	ClassA arrOfAs[] = { { 1, 1.0 }, { 2, 2.0 }, { 3, 3.0 } };

	// ouch, the theory is that this should work in C++11, however this doesn't compile, at least with clang, comments?
	ClassB arrOfBs[] = { { 1, 1.0 }, { 2, 2.0 }, { 3, 3.0 } };

	// however, this does work
	std::vector<ClassB> vectorOfBs = { { 1, 1.0 }, { 2, 2.0 }, { 3, 3.0 } };

	auto result = multiplyVectors({ 1.0, 2.0 }, { 3.0, 4.0 });

	return 0;
}
