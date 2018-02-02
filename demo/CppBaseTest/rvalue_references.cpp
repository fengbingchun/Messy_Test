#include "rvalue_references.hpp"
#include <iostream>
#include <string>
#include <utility>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52562004

//////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/reference
void double_string(std::string& s)
{
	s += s; // 's' is the same object as main()'s 'str'
}

char& char_number(std::string& s, std::size_t n)
{
	return s.at(n); // string::at() returns a reference to char
}

int test_lvalue_references1()
{
	// 1. Lvalue references can be used to alias an existing object (optionally with different cv-qualification):
	std::string s = "Ex";
	std::string& r1 = s;
	const std::string& r2 = s;

	r1 += "ample";           // modifies s
	//  r2 += "!";               // error: cannot modify through reference to const
	std::cout << r2 << '\n'; // prints s, which now holds "Example"

	// 2. They can also be used to implement pass-by-reference semantics in function calls:
	std::string str = "Test";
	double_string(str);
	std::cout << str << '\n';

	// 3. When a function's return type is lvalue reference, the function call expression becomes an lvalue expression
	std::string str_ = "Test";
	char_number(str_, 1) = 'a'; // the function call is lvalue, can be assigned to
	std::cout << str_ << '\n';

	return 0;
}

//////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/reference
static void f(int& x)
{
	std::cout << "lvalue reference overload f(" << x << ")\n";
}

static void f(const int& x)
{
	std::cout << "lvalue reference to const overload f(" << x << ")\n";
}

static void f(int&& x)
{
	std::cout << "rvalue reference overload f(" << x << ")\n";
}

int test_rvalue_references1()
{
	// 1. Rvalue references can be used to extend the lifetimes of temporary objects
	// (note, lvalue references to const can extend the lifetimes of temporary objects too, but they are not modifiable through them):
	std::string s1 = "Test";
	//  std::string&& r1 = s1;           // error: can't bind to lvalue

	const std::string& r2 = s1 + s1; // okay: lvalue reference to const extends lifetime
	//  r2 += "Test";                    // error: can't modify through reference to const

	std::string&& r3 = s1 + s1;      // okay: rvalue reference extends lifetime
	r3 += "Test";                    // okay: can modify through reference to non-const
	std::cout << r3 << '\n';

	// 2. More importantly, when a function has both rvalue reference and lvalue reference overloads,
	// the rvalue reference overload binds to rvalues (including both prvalues and xvalues),
	// while the lvalue reference overload binds to lvalues:
	int i = 1;
	const int ci = 2;
	f(i);  // calls f(int&)
	f(ci); // calls f(const int&)
	f(3);  // calls f(int&&)
	// would call f(const int&) if f(int&&) overload wasn't provided
	f(std::move(i)); // calls f(int&&)

	// This allows move constructors, move assignment operators, and other move-aware functions
	// (e.g. vector::push_back() to be automatically selected when suitable.

	return 0;
}

/////////////////////////////////////////////////////
// reference: http://www.bogotobogo.com/cplusplus/C11/5_C11_Move_Semantics_Rvalue_Reference.php
static void printReference(int& value)
{
	std::cout << "lvalue: value = " << value << std::endl;
}

static void printReference(int&& value)
{
	std::cout << "rvalue: value = " << value << std::endl;
}

static int getValue()
{
	int temp_ii = 99;
	return temp_ii;
}

int test_rvalue_references2()
{
	int ii = 11;
	printReference(ii);
	printReference(getValue());  //  printReference(99);
	return 0;
}

////////////////////////////////////////////////////////////
// references: https://msdn.microsoft.com/en-us/library/dd293668.aspx
template<typename T> struct S;

// The following structures specialize S by 
// lvalue reference (T&), const lvalue reference (const T&), 
// rvalue reference (T&&), and const rvalue reference (const T&&).
// Each structure provides a print method that prints the type of 
// the structure and its parameter.
template<typename T> struct S<T&> {
	static void print(T& t)
	{
		std::cout << "print<T&>: " << t << std::endl;
	}
};

template<typename T> struct S<const T&> {
	static void print(const T& t)
	{
		std::cout << "print<const T&>: " << t << std::endl;
	}
};

template<typename T> struct S<T&&> {
	static void print(T&& t)
	{
		std::cout << "print<T&&>: " << t << std::endl;
	}
};

template<typename T> struct S<const T&&> {
	static void print(const T&& t)
	{
		std::cout << "print<const T&&>: " << t << std::endl;
	}
};

// This function forwards its parameter to a specialized
// version of the S type.
template <typename T> void print_type_and_value(T&& t)
{
	S<T&&>::print(std::forward<T>(t));
}

// This function returns the constant string "fourth".
const std::string fourth() { return std::string("fourth"); }

int test_rvalue_references3()
{
	// The following call resolves to:
	// print_type_and_value<string&>(string& && t)
	// Which collapses to:
	// print_type_and_value<string&>(string& t)
	std::string s1("first");
	print_type_and_value(s1);

	// The following call resolves to:
	// print_type_and_value<const string&>(const string& && t)
	// Which collapses to:
	// print_type_and_value<const string&>(const string& t)
	const std::string s2("second");
	print_type_and_value(s2);

	// The following call resolves to:
	// print_type_and_value<string&&>(string&& t)
	print_type_and_value(std::string("third"));

	// The following call resolves to:
	// print_type_and_value<const string&&>(const string&& t)
	print_type_and_value(fourth());

	return 0;
}
