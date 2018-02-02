#include "exception.hpp"
#include <exception>
#include <typeinfo>
#include <iostream>
#include <utility>
#include <cstring>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78303734

// Fix: error C3646: 'noexcept' : unknown override specifier
#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

namespace exception_ {
/////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/exception/exception/
class Polymorphic { 
	virtual void member(){}
};

int test_exception_1()
{
	try {
		Polymorphic * pb = 0;
		typeid(*pb); // throws a bad_typeid exception
	} catch (std::exception& e) { // std::std::bad_typeid
		std::cerr << "exception caught: " << e.what() << '\n'; // exception caught: Attempted a typeid of Null pointer!
	}

	return 0;
}

struct ooops : std::exception {
	const char* what()  const NOEXCEPT /*noexcept*/ override{ return "Ooops!\n"; }
};

int test_exception_2()
{
	ooops e;
	std::exception* p = &e;
	try {
		throw e;       // throwing copy-constructs: ooops(e)
	} catch (std::exception& ex) {
		std::cout << ex.what(); // 0oops!
	}
	
	try {
		throw *p;      // throwing copy-constructs: std::exception(*p)
	} catch (std::exception& ex) {
		std::cout << ex.what(); // Unknown exception
	}

	return 0;
}

// text_exception uses a dynamically-allocated internal c-string for what():
class text_exception : public std::exception {
public:
	text_exception(const char* text) {
		text_ = new char[std::strlen(text) + 1];
		std::strcpy(text_, text);
	}
	text_exception(const text_exception& e) {
		text_ = new char[std::strlen(e.text_) + 1];
		std::strcpy(text_, e.text_);
	}
	~text_exception() NOEXCEPT /*throw()*/ {
		delete[] text_;
	}
	const char* what() const NOEXCEPT /*noexcept*/ override { return text_; }

private:
	char* text_;
};

int test_exception_3()
{
	try {
		throw text_exception("custom text\n");
	} catch (std::exception& ex) {
		std::cout << ex.what(); // custom text
	}

	return 0;
}

} // namespace exception_
