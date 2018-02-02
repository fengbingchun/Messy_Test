#include "iostream.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/63685373

// reference: http://www.tutorialspoint.com/cplusplus/cpp_basic_input_output.htm
int test_iostream_cout()
{
	char str[] = "Hello C++";
	std::cout << "Value of str is : " << str << std::endl;

	return 0;
}

int test_iostream_cin()
{
	char name[50];

	std::cout << "Please enter your name: ";
	std::cin >> name;
	std::cout << "Your name is: " << name << std::endl;

	return 0;
}

int test_iostream_clog()
{
	char str[] = "Unable to read....";
	std::clog << "Error message : " << str << std::endl;

	return 0;
}

int test_iostream_cerr()
{
	char str[] = "Unable to read....";
	std::cerr << "Error message : " << str << std::endl;

	return 0;
}

// reference: https://msdn.microsoft.com/en-us/library/6xwbdak2(v=vs.80).aspx
static void TestWide()
{
	int i = 0;
	std::wcout << L"Enter a number: ";
	std::wcin >> i;
	std::wcerr << L"test for wcerr" << std::endl;
	std::wclog << L"test for wclog" << std::endl;
}

int test_iostream_w()
{
	int i = 0;
	std::cout << "Enter a number: ";
	std::cin >> i;
	std::cerr << "test for cerr" << std::endl;
	std::clog << "test for clog" << std::endl;

	TestWide();

	return 0;
}

