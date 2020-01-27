#ifndef FBC_CPP_BASE_TEST_STATIC_HPP_
#define FBC_CPP_BASE_TEST_STATIC_HPP_

#include <iostream>

namespace static_ {

class A {
public:
	static int func(); // 只能调用静态成员
	int func2();

public:
	static int val;
private:
	int val2 = 5;
	static int val3; // 必须在类外进行初始化
};

struct X {
private:
	int i;
	static int si;
public:
	void set_i(int arg) { i = arg; }
	static void set_si(int arg) { si = arg; }

	void print_i() {
		std::cout << "Value of i = " << i << std::endl;
		std::cout << "Again, value of i = " << this->i << std::endl;
	}

	static void print_si() {
		std::cout << "Value of si = " << si << std::endl;
		// A static member function does not have a this pointer
		//std::cout << "Again, value of si = " << this->si << std::endl; // error
	}
};

class C {
	// A static member function cannot be declared with the keywords virtual, const, volatile, or const volatile.
	// A static member function can access only the names of static members, enumerators, and nested types of the class in which it is declared.
	static void f() {
		std::cout << "Here is i: " << i << std::endl;
	}
	static int i;
	int j;
public:
	C(int firstj) : j(firstj) { }
	void printall();
};

class Singleton {
public:
	static Singleton& Instance();

private:
	Singleton(); // Singleton不可以被实例化，因此将其构造函数声明为protected或者直接声明为private
};

int test_static_1();
int test_static_2();
int test_static_3();
int test_static_4();
int test_static_5();
int test_static_6();
int test_static_7();

} // namespace static_


#endif // FBC_CPP_BASE_TEST_STATIC_HPP_
