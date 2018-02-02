#include "local_class.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78511394

namespace local_class_ {
// reference: C++ Primer(Fifth Edition) 19.7
int a{ 0 }, val{ 0 };

void foo(int val)
{
	static int si;
	enum Loc {a = 1024, b};
	// Bar is local to foo
	struct Bar {
		Loc locVal; // ok: uses a local type name
		int barVal;

		void fooBar(Loc l = a) // ok: default argument si Loc::a
		{
			//barVal = val; // error: val is local to foo
			barVal = ::local_class_::val; // ok: uses a global object
			barVal = si; // ok: uses a static local object
			locVal = b; // ok: use an enumerator
		}
	};
}

int test_local_class_1()
{
	return 0;
}

////////////////////////////////////////////////
// reference: http://www.geeksforgeeks.org/local-class-in-c/
void fun()
{
	class Test { // local to fun
	public:
		// Fine as the method is defined inside the local class
		void method() {
			std::cout << "Local Class method() called" << std::endl;
		}
	};

	Test t;
	t.method();
}
int test_local_class_2()
{
	fun();
	return 0;
}

/////////////////////////////////////////////////////
// reference: http://www.geeksforgeeks.org/local-class-in-c/
void fun2()
{
	class Test { // local to fun
	public:
		static void method()
		{
			std::cout << "Local Class method() called"<<std::endl;
		}
	};

	Test::method();
}
int test_local_class_3()
{
	fun2();
	return 0;
}

/////////////////////////////////////////////////////
// http://www.geeksforgeeks.org/local-class-in-c/
void fun3()
{
	static int x = -3;
	enum { i = 1, j = 2 };

	// Local class
	class Test {
	public:
		void method() {
			std::cout << "x = " << x << std::endl;   // fine as x is static
			std::cout << "i = " << i << std::endl;   // fine as i is enum
		}
	};

	Test t;
	t.method();
}

int test_local_class_4()
{
	fun3();
	return 0;
}

///////////////////////////////////////////////////////////
// http://www.geeksforgeeks.org/local-class-in-c/
int x = 11;

void fun4()
{

	// First Local class
	class Test1 {
	public:
		Test1() { std::cout << "Test1::Test1()" << std::endl; }
	};

	// Second Local class
	class Test2 {
		// Fine: A local class can use other local classes of same function
		Test1 t1;
	public:
		void method() {
			// Fine: Local class member methods can access global variables.
			std::cout << "x = " << x << std::endl;
		}
	};

	Test2 t;
	t.method();
}

int test_local_class_5()
{
	fun4();
	return 0;
}

/////////////////////////////////////////////////////////
// reference: https://stackoverflow.com/questions/3235172/local-classes-in-c
int pqr()
{
	class abc {
		int x;
	public:
		abc() : x(4) { }
		friend int pqr();
	};
	return abc().x;
}

int test_local_class_6()
{
	std::cout << "Return " << pqr() << std::endl;
	return 0;
}

//////////////////////////////////////////////////////////
// reference: https://www.hscripts.com/tutorials/cpp/local-classes.php
int y;
void g()
{
	class local {
	public:
		void put(int n) { ::local_class_::y = n; }
		int get() { return ::local_class_::y; }
	} ab;

	ab.put(20);
	std::cout << "The value assigned to y is::" << ab.get() << std::endl;
}

int test_local_class_7()
{
	g();
	return 0;
}

//////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/class
int test_local_class_8()
{
	struct Local {
		bool operator()(int n, int m) {
			return n > m;
		}
	};

	std::vector<int> v{ 1, 2, 3 };
	std::sort(v.begin(), v.end(), Local()); // since C++11
	for (int n : v) std::cout << n << ' ';
	std::cout << std::endl;

	return 0;
}

} // namespace local_class_
