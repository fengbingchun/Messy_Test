#include "try_catch.hpp"
#include <iostream>
#include <exception>
#include <vector>

// Blog: http://blog.csdn.net/fengbingchun/article/details/65939258

//////////////////////////////////////////////////
// reference: http://www.cplusplus.com/doc/tutorial/exceptions/
int test_exception1()
{
	try {
		throw 20;
	}
	catch (int e) {
		std::cout << "An exception occurred. Exception Nr. " << e << '\n';
	}

	return 0;
}

class myexception : public std::exception
{
	virtual const char* what() const throw()
	{
		return "My exception happened";
	}
} myex;

int test_exception2()
{
	try {
		throw myex;
	}
	catch (std::exception& e) { // catches exception objects by reference (notice the ampersand & after the type)
		std::cout << e.what() << '\n';
	}

	return 0;
}

int test_exception3()
{
/*
	exception		description
	bad_alloc		thrown by new on allocation failure
	bad_cast		thrown by dynamic_cast when it fails in a dynamic cast
	bad_exception		thrown by certain dynamic exception specifiers
	bad_typeid		thrown by typeid
	bad_function_call	thrown by empty function objects
	bad_weak_ptr		thrown by shared_ptr when passed a bad weak_ptr
*/
	try {
		int* myarray = new int[1000];
	}
	catch (std::exception& e) { // Takes a reference to an 'exception' object
		std::cout << "Standard exception: " << e.what() << std::endl;
	}

	return 0;
}

///////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/try_catch
int test_exception4()
{
	try {
		std::cout << "Throwing an integer exception...\n";
		throw 42;
	}
	catch (int i) {
		std::cout << " the integer exception was caught, with value: " << i << '\n';
	}

	try {
		std::cout << "Creating a vector of size 5... \n";
		std::vector<int> v(5);
		std::cout << "Accessing the 11th element of the vector...\n";
		std::cout << v.at(10); // vector::at() throws std::out_of_range
	}
	catch (const std::exception& e) { // caught by reference to base
		std::cout << " a standard exception was caught, with message '"
			<< e.what() << "'\n";
	}

	return 0;
}

/////////////////////////////////////////////////
// reference: https://www.tutorialspoint.com/cplusplus/cpp_exceptions_handling.htm
static int division(int a, int b) {
	if (b == 0) {
		throw "Division by zero condition!";
	}
	return (a / b);
}

int test_exception5()
{
	int x{ 50 }, y{ 0 }, z{ 0 };

	try {
		z = division(x, y);
		std::cout << z << std::endl;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}

	return 0;
}

struct MyException : public std::exception
{
	const char * what() const throw () {
		return "C++ Exception";
	}
};

int test_exception6()
{
	try {
		throw MyException();
	}
	catch (MyException& e) {
		std::cout << "MyException caught" << std::endl;
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e) {
		//Other errors
	}

	return 0;
}

int test_exception7()
{
	try {
		char* str = nullptr;
		str = new char[10];
		if (str == nullptr) throw "Allocation failure";
		for (int n = 0; n <= 100; n++) {
			if (n > 9) throw n;
			str[n] = 'z';
		}
	}
	catch (int i) {
		std::cout << "Exception: ";
		std::cout << "index " << i << " is out of range" << std::endl;
	}
	catch (char * str) {
		std::cout << "Exception: " << str << std::endl;
	}

	return 0;
}
