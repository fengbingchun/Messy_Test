#include "volatile_mutable.hpp"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <mutex>
#include <string.h>

// Blog: https://blog.csdn.net/fengbingchun/article/details/104109696

namespace volatile_mutable_ {

///////////////////////////////////////////////////////////
int test_volatile_1()
{
	volatile int i1 = 0; // correct
	int volatile i2 = 0; // correct

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://en.cppreference.com/w/c/language/volatile
int test_volatile_2()
{
{ // Any attempt to read or write to an object whose type is volatile-qualified through a non-volatile lvalue results in undefined behavior
	volatile int n = 1; // object of volatile-qualified type
	int* p = (int*)&n;
	int val = *p; // undefined behavior in C, Note: link does not report an error under C++
	fprintf(stdout, "val: %d\n", val);
}

{ // A member of a volatile-qualified structure or union type acquires the qualification of the type it belongs to
	typedef struct ss { int i; const int ci; } s;
	// the type of s.i is int, the type of s.ci is const int
	volatile s vs = { 1, 2 };
	// the types of vs.i and vs.ci are volatile int and const volatile int
}

{ // If an array type is declared with the volatile type qualifier (through the use of typedef), the array type is not volatile-qualified, but its element type is
	typedef int A[2][3];
	volatile A a = { {4, 5, 6}, {7, 8, 9} }; // array of array of volatile int
	//int* pi = a[0]; // Error: a[0] has type volatile int*
	volatile int* pi = a[0];
}

{ // A pointer to a non-volatile type can be implicitly converted to a pointer to the volatile-qualified version of the same or compatible type. The reverse conversion can be performed with a cast expression
	int* p = nullptr;
	volatile int* vp = p; // OK: adds qualifiers (int to volatile int)
	//p = vp; // Error: discards qualifiers (volatile int to int)
	p = (int*)vp; // OK: cast
}

{ // volatile disable optimizations
	clock_t t = clock();
	double d = 0.0;
	for (int n = 0; n < 10000; ++n)
		for (int m = 0; m < 10000; ++m)
			d += d * n*m; // reads and writes to a non-volatile 
	fprintf(stdout, "Modified a non-volatile variable 100m times. Time used: %.2f seconds\n", (double)(clock() - t) / CLOCKS_PER_SEC);

	t = clock();
	volatile double vd = 0.0;
	for (int n = 0; n < 10000; ++n)
		for (int m = 0; m < 10000; ++m)
			vd += vd * n*m; // reads and writes to a volatile 
	fprintf(stdout, "Modified a volatile variable 100m times. Time used: %.2f seconds\n", (double)(clock() - t) / CLOCKS_PER_SEC);
}

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://en.cppreference.com/w/cpp/language/cv
int test_volatile_3()
{
	int n1 = 0;           // non-const object
	const int n2 = 0;     // const object
	int const n3 = 0;     // const object (same as n2)
	volatile int n4 = 0;  // volatile object
	const struct {
		int n1;
		mutable int n2;
	} x = { 0, 0 };      // const object with mutable member

	n1 = 1; // ok, modifiable object
	//n2 = 2; // error: non-modifiable object
	n4 = 3; // ok, treated as a side-effect
	//x.n1 = 4; // error: member of a const object is const
	x.n2 = 4; // ok, mutable member of a const object isn't const

	const int& r1 = n1; // reference to const bound to non-const object
	//r1 = 2; // error: attempt to modify through reference to const
	const_cast<int&>(r1) = 2; // ok, modifies non-const object n1
	fprintf(stdout, "n1: %d\n", n1); // 2

	const int& r2 = n2; // reference to const bound to const object
	//r2 = 2; // error: attempt to modify through reference to const
	const_cast<int&>(r2) = 2; // undefined behavior: attempt to modify const object n2, Note: link does not report an error under C++
	fprintf(stdout, "n2: %d\n", n2); // 0

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://www.geeksforgeeks.org/understanding-volatile-qualifier-in-c/
int test_volatile_4()
{
{
	const int local = 10;
	int *ptr = (int*)&local;
	fprintf(stdout, "Initial value of local : %d \n", local); // 10

	*ptr = 100;
	fprintf(stdout, "Modified value of local: %d \n", local); // 10
}

{
	const volatile int local = 10;
	int *ptr = (int*)&local;
	fprintf(stdout, "Initial value of local : %d \n", local); // 10

	*ptr = 100;
	fprintf(stdout, "Modified value of local: %d \n", local); // 100
}

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://en.cppreference.com/w/cpp/language/cv
int test_mutable_1()
{
	// Mutable is used to specify that the member does not affect the externally visible state of the class (as often used for mutexes,
	// memo caches, lazy evaluation, and access instrumentation)
	class ThreadsafeCounter {
	public:
		int get() const {
			std::lock_guard<std::mutex> lk(m);
			return data;
		}
		void inc() {
			std::lock_guard<std::mutex> lk(m);
			++data;
		}

	private:
		mutable std::mutex m; // The "M&M rule": mutable and mutex go together
		int data = 0;
	};

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://www.tutorialspoint.com/cplusplus-mutable-keyword
int test_mutable_2()
{
	class Test {
	public:
		Test(int x = 0, int y = 0) : a(x), b(y) {}

		void seta(int x = 0) { a = x; }
		void setb(int y = 0) { b = y; }
		void disp() { fprintf(stdout, "a: %d, b: %d\n", a, b); }

	public:
		int a;
		mutable int b;
	};

	const Test t(10, 20);
	fprintf(stdout, "t.a: %d, t.b: %d \n", t.a, t.b); // 10, 20

	//t.a=30; // Error occurs because a can not be changed, because object is constant.
	t.b = 100; // b still can be changed, because b is mutable.
	fprintf(stdout, "t.a: %d, t.b: %d \n", t.a, t.b); // 10, 100

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://www.geeksforgeeks.org/c-mutable-keyword/
int test_mutable_3()
{
	using std::cout;
	using std::endl;

	class Customer {
	public:
		Customer(char* s, char* m, int a, int p)
		{
			strcpy(name, s);
			strcpy(placedorder, m);
			tableno = a;
			bill = p;
		}

		void changePlacedOrder(char* p) const { strcpy(placedorder, p); }
		void changeBill(int s) const { bill = s; }

		void display() const
		{
			cout << "Customer name is: " << name << endl;
			cout << "Food ordered by customer is: " << placedorder << endl;
			cout << "table no is: " << tableno << endl;
			cout << "Total payable amount: " << bill << endl;
		}

	private:
		char name[25];
		mutable char placedorder[50];
		int tableno;
		mutable int bill;
	};

	const Customer c1("Pravasi Meet", "Ice Cream", 3, 100);
	c1.display();
	c1.changePlacedOrder("GulabJammuns");
	c1.changeBill(150);
	c1.display();

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://stackoverflow.com/questions/105014/does-the-mutable-keyword-have-any-purpose-other-than-allowing-the-variable-to
int test_mutable_4()
{
	int x = 0;
	auto f1 = [=]() mutable { x = 42; }; // OK
	//auto f2 = [=]() { x = 42; }; // Error: a by-value capture cannot be modified in a non-mutable lambda
	fprintf(stdout, "x: %d\n", x); // 0

	return 0;
}

} // namespace volatile_mutable_

