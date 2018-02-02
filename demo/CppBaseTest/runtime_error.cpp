#include "runtime_error.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78306461

namespace runtime_error_ {
//////////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/tyahh3a9.aspx
int test_runtime_error_1()
{
	try {
		std::locale loc("test");
	} catch (std::exception& e) {
		std::cerr << "Caught " << e.what() << std::endl; // Caught bad locale name
		std::cerr << "Type " << typeid(e).name() << std::endl; // Type class std::runtime_error
	};

	return 0;
}

/////////////////////////////////////////////////////////////
// reference: http://www.java2s.com/Tutorial/Cpp/0120__Exceptions/Throwyourownexceptionclassbasedonruntimeerror.htm
class DivideByZeroException : public std::runtime_error {
public:
	DivideByZeroException::DivideByZeroException() : runtime_error("attempted to divide by zero") {}
};

static double quotient(int numerator, int denominator)
{
	throw DivideByZeroException(); // terminate function
	return 0;
}

int test_runtime_error_2()
{
	try {
		double result = quotient(1, 1);
		std::cout << "The quotient is: " << result << std::endl;
	} catch (DivideByZeroException& divideByZeroException) {
		std::cout << "Exception occurred: " << divideByZeroException.what() << std::endl; // Exception occurred: attempted to divide by zero
	}

	return 0;
}

////////////////////////////////////////////////////////////////
class CppBase_RunTime_Exception : public std::runtime_error {
public :
	CppBase_RunTime_Exception(int error_code_) : runtime_error(""), error_code(error_code_) {}
	CppBase_RunTime_Exception(int error_code_, const std::string& info_) : runtime_error(info_), error_code(error_code_) {}
	int get_error_code() const { return error_code; }
private:
	int error_code = 0;
};

static int calc(int a)
{
	if (a > 0) {
		throw CppBase_RunTime_Exception(1, __FUNCTION__);
	}

	if (a < 0) {
		throw CppBase_RunTime_Exception(-1, __FUNCTION__);
	}

	throw CppBase_RunTime_Exception(0);

	return 0;
}

int test_runtime_error_3()
{
	const int a{ 2 }, b{ -3 }, c{ 0 };

	try {
		calc(a);
	} catch (const CppBase_RunTime_Exception& e) {
		std::cerr << "error fun name: " << e.what() << ", error code: " << e.get_error_code() << std::endl;
	}

	try {
		calc(b);
	} catch (const CppBase_RunTime_Exception& e) {
		std::cerr << "error fun name: " << e.what() << ", error code: " << e.get_error_code() << std::endl;
	}

	try {
		calc(c);
	} catch (const CppBase_RunTime_Exception& e) {
		std::cerr << "error fun name: " << e.what() << ", error code: " << e.get_error_code() << std::endl;
	}

	std::cout << "over" << std::endl;

	return 0;
}

} // namespace runtime_error_

