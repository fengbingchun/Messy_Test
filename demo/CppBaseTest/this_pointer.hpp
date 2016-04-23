#ifndef FBC_MESSY_TEST_THIS_POINTER_HPP
#define FBC_MESSY_TEST_THIS_POINTER_HPP

#include <iostream>

// reference: http://www.tutorialspoint.com/cplusplus/cpp_this_pointer.htm
class Box
{
public:
	// Constructor definition
	Box(double l = 2.0, double b = 2.0, double h = 2.0)
	{
		std::cout << "Constructor called." << std::endl;
		length = l;
		breadth = b;
		height = h;
	}
	double Volume()
	{
		return length * breadth * height;
	}
	int compare(Box box)
	{
		return this->Volume() > box.Volume();
	}
private:
	double length;     // Length of a box
	double breadth;    // Breadth of a box
	double height;     // Height of a box
};

/*void Date::setMonth(int mn)
{
	month = mn; // These three statements are equivalent
	this->month = mn;
	(*this).month = mn;
}*/

// reference: https://msdn.microsoft.com/en-us/library/y0dddwwd.aspx
class Buf
{
public:
	Buf(char* szBuffer, size_t sizeOfBuffer);
	Buf& operator=(const Buf &);
	void Display();

private:
	char* buffer;
	size_t sizeOfBuffer;
};

// reference: http://en.cppreference.com/w/cpp/language/this
class T
{
	int x;

	void foo()
	{
		x = 6;       // same as this->x = 6;
		this->x = 5; // explicit use of this->
	}

	void foo() const
	{
		//        x = 7; // Error: *this is constant
	}

	void foo(int x) // parameter x shadows the member with the same name
	{
		this->x = x; // unqualified x refers to the parameter
		// 'this->' required for disambiguation
	}

	int y;
	T(int x) : x(x), // uses parameter x to initialize member x
		y(this->x) // uses member x to initialize member y
	{}

	T& operator= (const T& b)
	{
		x = b.x;
		return *this; // many overloaded operators return *this
	}
};

class Outer {
	//int a[sizeof(*this)]; // error: not inside a member function
	unsigned int sz = sizeof(*this); // OK: in default member initializer
	void f() {
		int b[sizeof(*this)]; // OK
		struct Inner {
			//int c[sizeof(*this)]; // error: not inside a member function of Inner
		};
	}
}

void test_this_pointer1();
void test_this_pointer2();

#endif // FBC_MESSY_TEST_THIS_POINTER_HPP
