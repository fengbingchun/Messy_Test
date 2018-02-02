#include "typeid.hpp"
#include <assert.h>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

// Blog: http://blog.csdn.net/fengbingchun/article/details/51866559

int func(int a)
{
	return 0;
}

typedef int(*func_ptr)(int);
class Base { public: Base(){} };

int test_typeid1()
{
	char char_ = 'a';
	unsigned char uchar_ = 'b';
	short short_ = 2;
	unsigned short ushort_ = 3;
	int int_ = 1;
	unsigned int uint_ = 4;
	float float_ = 2.0;
	double double_ = 1.0;
	long long_ = 5;
	long long llong_ = 6;
	int array[10] = { 1};
	int* array_header = array;
	std::string string_;
	std::vector<int> int_vector;
	func_ptr f = func;
	Base Base_;
	Base* pBase_ = new Base;
	Base& Base__ = Base_;

	// 对于返回字符串的具体内容，与编译器有关
	std::cout << "char_ type: " << typeid(char_).name() << std::endl; // char_ type: char
	assert(typeid(char).name() == typeid(char_).name());
	
	std::cout << "uchar type: " << typeid(uchar_).name() << std::endl; // uchar type: unsigned char
	assert(typeid(unsigned char).name() == typeid(uchar_).name());
	
	std::cout << "short_ type: " << typeid(short_).name() << std::endl; // short_ type: short
	assert(typeid(short).name() == typeid(short_).name());
	
	std::cout << "ushort_ type: " << typeid(ushort_).name() << std::endl; // ushort_ type: unsigned short
	assert(typeid(unsigned short).name() == typeid(ushort_).name());

	std::cout << "int_ type: " << typeid(int_).name() << std::endl; // int_ type: int
	assert(typeid(int).name() == typeid(int_).name());
	
	std::cout << "uint_ type: " << typeid(uint_).name() << std::endl; // uint_ type: unsigned int
	assert(typeid(unsigned int).name() == typeid(uint_).name());
	
	std::cout << "float_ type: " << typeid(float_).name() << std::endl; // float_ type: float
	assert(typeid(float).name() == typeid(float_).name());

	std::cout << "double_ type: " << typeid(double_).name() << std::endl; // double_ type: double
	assert(typeid(double).name() == typeid(double_).name());

	std::cout << "long_ type: " << typeid(long_).name() << std::endl; // long_ type: long
	assert(typeid(long).name() == typeid(long_).name());

	std::cout << "llong_ type: " << typeid(llong_).name() << std::endl; // llong_ type: __int64
	assert(typeid(long long).name() == typeid(llong_).name());

	std::cout << "array[] type: " << typeid(array).name() << std::endl; // array[] type: int [10]
	assert(typeid(int [10]).name() == typeid(array).name());

	std::cout << "array_header type: " << typeid(array_header).name() << std::endl; // array_header type: int * __ptr64
	assert(typeid(int*).name() == typeid(array_header).name());
	
	std::cout << "string_ type: " << typeid(string_).name() << std::endl; // string_ type: class std::basic_string<char,struct std::char_traits<char>, class std::allocator<char>>
	assert(typeid(std::string).name() == typeid(string_).name());

	std::cout << "int_vector type: " << typeid(int_vector).name() << std::endl; // int_vector type: class std::vector<int,class std::allocator<int>>
	assert(typeid(std::vector<int>).name() == typeid(int_vector).name());

	std::cout << "f type: " << typeid(f).name() << std::endl; // f type : int(__cdecl*)(int)
	assert(typeid(int(*)(int)).name() == typeid(f).name());

	std::cout << "Base_ type: " << typeid(Base_).name() << std::endl; // Base_ type: class Base
	assert(typeid(class Base).name() == typeid(Base_).name());

	std::cout << "pBase_ type: " << typeid(pBase_).name() << std::endl; // pBase_ type: class Base * __ptr64
	assert(typeid(class Base*).name() == typeid(pBase_).name());

	std::cout << "Base__ type: " << typeid(Base__).name() << std::endl; // Base__ type: class Base
	assert(typeid(class Base).name() == typeid(Base__).name());

	delete pBase_;
	return 0;
}

////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/typeid
int test_typeid2()
{
	struct Base {}; // non-polymorphic
	struct Derived : Base {};

	struct Base2 { virtual void foo() {} }; // polymorphic
	struct Derived2 : Base2 {};

	int myint = 50;
	std::string mystr = "string";
	double *mydoubleptr = nullptr;

	std::cout << "myint has type: " << typeid(myint).name() << '\n' // myint has type: int
		<< "mystr has type: " << typeid(mystr).name() << '\n' // mystr has type: class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>
		<< "mydoubleptr has type: " << typeid(mydoubleptr).name() << '\n'; // mydoubleptr has type: double * __ptr64

	// std::cout << myint is a glvalue expression of polymorphic type; it is evaluated
	const std::type_info& r1 = typeid(std::cout << myint); // 50
	std::cout << "std::cout<<myint has type : " << r1.name() << '\n'; // std::cout<<myint has type: class std::basic_ostream<char, struct std::char_traits<char>>

	// std::printf() is not a glvalue expression of polymorphic type; NOT evaluated
	const std::type_info& r2 = typeid(std::printf("%d\n", myint));
	std::cout << "printf(\"%d\\n\",myint) has type : " << r2.name() << '\n'; // printf(\"%d\\n\",myint) has type : int

	// Non-polymorphic lvalue is a static type
	Derived d1;
	Base& b1 = d1;
	std::cout << "reference to non-polymorphic base: " << typeid(b1).name() << '\n'; // reference to non-polymorphic base: struct 'int __cdecl test_typeid2(void)'::'2'::Base

	Derived2 d2;
	Base2& b2 = d2;
	std::cout << "reference to polymorphic base: " << typeid(b2).name() << '\n'; // reference to polymorphic base: struct 'int __cdecl test_typeid2(void)'::'3'::Derived2

	try {
		// dereferencing a null pointer: okay for a non-polymoprhic expression
		std::cout << "mydoubleptr points to " << typeid(*mydoubleptr).name() << '\n'; // mydoubleptr points to double
		// dereferencing a null pointer: not okay for a polymorphic lvalue
		Derived2* bad_ptr = NULL;
		std::cout << "bad_ptr points to...";  // bad_ptr points to... 
		std::cout << typeid(*bad_ptr).name() << '\n';
	}
	catch (const std::bad_typeid& e) {
		std::cout << " caught " << e.what() << '\n'; // caught Attempted a typeid of NULL pointer!
	}

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/fyf39xec.aspx
template < typename T >
T max(T arg1, T arg2) {
	std::cout << typeid(T).name() << "s compared." << std::endl;
	return (arg1 > arg2 ? arg1 : arg2);
}

int test_typeid3()
{
	class Base {
	public:
		virtual void vvfunc() {}
	};

	class Derived : public Base {};

	Derived* pd = new Derived;
	Base* pb = pd;
	std::cout << typeid(pb).name() << std::endl;   //prints "class Base *" // class 'int __cdecl test_typeid3(void)'::'2'::Base * __ptr64
	std::cout << typeid(*pb).name() << std::endl;   //prints "class Derived" // class 'int __cdecl test_typeid3(void)'::'2'::Derived
	std::cout << typeid(pd).name() << std::endl;   //prints "class Derived *" // class 'int __cdecl test_typeid3(void)'::'2'::Derived * __ptr64
	std::cout << typeid(*pd).name() << std::endl;   //prints "class Derived" // class 'int __cdecl test_typeid3(void)'::'2'::Derived
	delete pd;

	float a = 1.2, b = 3.4;
	max(a, b); // floats compared

	return 0;
}
