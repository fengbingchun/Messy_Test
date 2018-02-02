#include "friend.hpp"

#include <sstream>
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/51747056

// reference: https://msdn.microsoft.com/zh-cn/library/465sdshe.aspx
class Point_ {
	friend void ChangePrivate(Point_ &);
public:
	Point_(void) : m_i(0) {}
	void PrintPrivate(void){ std::cout << m_i << std::endl; }

private:
	int m_i;
};

// friend 函数可以访问其接受为参数的 Point_ 对象的私有数据成员
void ChangePrivate(Point_ &i)
{
	i.m_i++;
}

int test_friend1()
{
	Point_ sPoint;
	sPoint.PrintPrivate(); // 0
	ChangePrivate(sPoint);
	sPoint.PrintPrivate(); // 1

	return 0;
}

////////////////////////////////////////////////////////////
class B_f;

class A_f {
public:
	int Func1(B_f& b);
private:
	int Func2(B_f& b);
};

class B_f {
private:
	int _b;

	// A::Func1 is a friend function to class B
	// so A::Func1 has access to all members of B
	// 类成员函数可以声明为其他类中的友元
	friend int A_f::Func1(B_f&);
};

int A_f::Func1(B_f& b) { return b._b; }   // OK
//int A_f::Func2(Bf_& b) { return b._b; }   // C2248

///////////////////////////////////////////////////////////////
class YourClass {
	// friend 类是其所有成员函数都是类的友元函数的类，即，其成员函数具有对类的私有成员和受保护成员访问权限.
	// 友元关系不是相互的，除非显式指定。YourClass 的成员函数无法访问 YourOtherClass 的私有成员.
	// 友元关系不能继承，这意味着从 YourOtherClass 派生的类不能访问 YourClass 的私有成员.
	// 友元关系不可传递，因此 YourOtherClass 的友元类无法访问 YourClass 的私有成员。
	friend class YourOtherClass;  // Declare a friend class
public:
	YourClass() : topSecret(0){}
	void printMember() { std::cout << topSecret << std::endl; }
private:
	int topSecret;
};

class YourOtherClass {
public:
	void change(YourClass& yc, int x){ yc.topSecret = x; }
};

int test_friend2()
{
	YourClass yc1;
	YourOtherClass yoc1;
	yc1.printMember(); // 0
	yoc1.change(yc1, 5);
	yc1.printMember(); // 5

	return 0;
}

///////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/friend
template<typename T>
class Foo {
public:
	Foo(const T& val) : data(val) {}
private:
	T data;

	// generates a non-template operator<< for this T
	friend std::ostream& operator<<(std::ostream& os, const Foo& obj)
	{
		return os << obj.data;
	}
};

int test_friend3()
{
	Foo<double> obj(1.23);
	std::cout << obj << '\n'; // 1.23

	return 0;
}

///////////////////////////////////////////////////////////
template<typename T>
class Foo_; // forward declare to make function declaration possible

template<typename T> // declaration
std::ostream& operator<<(std::ostream&, const Foo_<T>&);

template<typename T>
class Foo_ {
public:
	Foo_(const T& val) : data(val) {}
private:
	T data;

	// refers to a full specialization for this particular T 
	friend std::ostream& operator<< <> (std::ostream&, const Foo_&);
	// note: this relies on template argument deduction in declarations
	// can also specify the template argument with operator<< <T>"
};

// definition
template<typename T>
std::ostream& operator<<(std::ostream& os, const Foo_<T>& obj)
{
	return os << obj.data;
}

int test_friend4()
{
	Foo_<double> obj(1.23);
	std::cout << obj << '\n'; // 1.23

	return 0;
}

///////////////////////////////////////////////////////
class MyClass {
	int i;

	friend std::ostream& operator<<(std::ostream& out, const MyClass& o);
	friend std::istream& operator>>(std::istream& in, MyClass& o);
public:
	MyClass(int i = 0) : i(i) {}
};

std::ostream& operator<<(std::ostream& out, const MyClass& mc)
{
	return out << mc.i;
}

std::istream& operator>>(std::istream& in, MyClass& mc)
{
	return in >> mc.i;
}

int test_friend5()
{
	MyClass mc(7);
	std::cout << mc << '\n'; // 7
	std::istringstream("100") >> mc;
	std::cout << mc << '\n'; // 100

	return 0;
}

///////////////////////////////////////////////
// reference: http://www.cplusplus.com/doc/tutorial/inheritance/
class Rectangle {
	int width, height;
public:
	Rectangle() {}
	Rectangle(int x, int y) : width(x), height(y) {}
	int area() { return width * height; }
	friend Rectangle duplicate(const Rectangle&);
};

Rectangle duplicate(const Rectangle& param)
{
	Rectangle res;
	res.width = param.width * 2;
	res.height = param.height * 2;
	return res;
}

int test_friend6()
{
	Rectangle foo;
	Rectangle bar(2, 3);
	foo = duplicate(bar);
	std::cout << foo.area() << '\n'; // 24

	return 0;
}

////////////////////////////////////////////////////////
class Square_;

class Rectangle_ {
	int width, height;
public:
	int area()
	{
		return (width * height);
	}
	void convert(Square_ a);
};

class Square_ {
	friend class Rectangle_;
private:
	int side;
public:
	Square_(int a) : side(a) {}
};

void Rectangle_::convert(Square_ a) {
	width = a.side;
	height = a.side;
}

int test_friend7()
{
	Rectangle_ rect;
	Square_ sqr(4);
	rect.convert(sqr);
	std::cout << rect.area(); // 16

	return 0;
}

///////////////////////////////////////
// reference: http://www.tutorialspoint.com/cplusplus/cpp_friend_functions.htm
class Box
{
	double width;
public:
	friend void printWidth(Box box);
	void setWidth(double wid);
};

// Member function definition
void Box::setWidth(double wid)
{
	width = wid;
}

// Note: printWidth() is not a member function of any class.
void printWidth(Box box)
{
	/* Because printWidth() is a friend of Box, it can
	directly access any member of this class */
	std::cout << "Width of box : " << box.width << std::endl;
}

int test_friend8()
{
	Box box;

	// set box width with member function
	box.setWidth(10.0);

	// Use friend function to print the wdith.
	printWidth(box); // 10.0

	return 0;
}

/////////////////////////////////////////////
// reference: http://www.programiz.com/cpp-programming/friend-function-class
class Distance
{
private:
	int meter;
public:
	Distance() : meter(0){ }
	friend int func(Distance);  //friend function
};

int func(Distance d)            //function definition
{
	d.meter = 5;         //accessing private data from non-member function
	return d.meter;
}

int test_friend9()
{
	Distance D;
	std::cout << "Distace: " << func(D); // 5
	return 0;
}

///////////////////////////////////////////////////
class B;     // forward declaration

class A {
private:
	int data;
public:
	A() : data(12){ }
	friend int func(A, B);   //friend function Declaration
};

class B {
private:
	int data;
public:
	B() : data(1){ }
	friend int func(A, B);  //friend function Declaration
};

int func(A d1, B d2)
/*Function func() is the friend function of both classes A and B. So, the private data of both class can be accessed from this function.*/
{
	return (d1.data + d2.data);
}

int test_friend10()
{
	A a;
	B b;
	std::cout << "Data: " << func(a, b); // 13

	return 0;
}

///////////////////////////////////////////
// reference: https://www.codingunit.com/cplusplus-tutorial-friend-function-and-friend-class
//Must be known to TWO before declaration of ONE.
class ONE;

class TWO
{
public:
	void print(ONE& x);
};

class ONE
{
	int a, b;
	friend void TWO::print(ONE& x);
public:
	ONE() : a(1), b(2) { }
};

void TWO::print(ONE& x)
{
	std::cout << "a is " << x.a << std::endl; // a is 1
	std::cout << "b is " << x.b << std::endl; // b is 2
}

int test_friend11()
{
	ONE xobj;
	TWO yobj;
	yobj.print(xobj);

	return 0;
}

//////////////////////////////////
class MyClass_
{
	// Declare a friend class
	friend class SecondClass;

public:
	MyClass_() : Secret(0){}
	void printMember()
	{
		std::cout << Secret << std::endl;
	}
private:
	int Secret;
};

class SecondClass
{
public:
	void change(MyClass_& yourclass, int x)
	{
		yourclass.Secret = x;
	}
};

int test_friend12()
{
	MyClass_ my_class;
	SecondClass sec_class;
	my_class.printMember(); // 0
	sec_class.change(my_class, 5);
	my_class.printMember(); // 5

	return 0;
}

///////////////////////////////////////////
// reference: http://www.learncpp.com/cpp-tutorial/813-friend-functions-and-classes/
// A function can be a friend of more than one class at the same time.
class Humidity;

class Temperature
{
private:
	int m_temp;
public:
	Temperature(int temp = 0) { m_temp = temp; }

	void setTemperature(int temp) { m_temp = temp; }

	friend void printWeather(const Temperature &temperature, const Humidity &humidity);
};

class Humidity
{
private:
	int m_humidity;
public:
	Humidity(int humidity = 0) { m_humidity = humidity; }

	void setHumidity(int humidity) { m_humidity = humidity; }

	friend void printWeather(const Temperature &temperature, const Humidity &humidity);
};

void printWeather(const Temperature &temperature, const Humidity &humidity)
{
	std::cout << "The temperature is " << temperature.m_temp <<      // 12
		" and the humidity is " << humidity.m_humidity << '\n'; // 10
}

int test_friend13()
{
	Humidity hum(10);
	Temperature temp(12);

	printWeather(temp, hum);

	return 0;
}

////////////////////////////////////////////////////////////////
class Storage
{
private:
	int m_nValue;
	double m_dValue;
public:
	Storage(int nValue, double dValue)
	{
		m_nValue = nValue;
		m_dValue = dValue;
	}

	// Make the Display class a friend of Storage
	friend class Display;
};

class Display
{
private:
	bool m_displayIntFirst;

public:
	Display(bool displayIntFirst) { m_displayIntFirst = displayIntFirst; }

	void displayItem(Storage &storage)
	{
		if (m_displayIntFirst)
			std::cout << storage.m_nValue << " " << storage.m_dValue << '\n';
		else // display double first
			std::cout << storage.m_dValue << " " << storage.m_nValue << '\n';// 6.7 5
	}
};

int test_friend14()
{
	Storage storage(5, 6.7);
	Display display(false);

	display.displayItem(storage);

	return 0;
}

/////////////////////////////////////
class Storage_; // forward declaration for class Storage

class Display_
{
private:
	bool m_displayIntFirst;

public:
	Display_(bool displayIntFirst) { m_displayIntFirst = displayIntFirst; }

	void displayItem(Storage_ &storage); // forward declaration above needed for this declaration line
};

class Storage_
{
private:
	int m_nValue;
	double m_dValue;
public:
	Storage_(int nValue, double dValue)
	{
		m_nValue = nValue;
		m_dValue = dValue;
	}

	// Make the Display class a friend of Storage (requires seeing the full declaration of class Display, as above)
	friend void Display_::displayItem(Storage_& storage);
};

// Now we can define Display::displayItem, which needs to have seen the full declaration of class Storage
void Display_::displayItem(Storage_ &storage)
{
	if (m_displayIntFirst)
		std::cout << storage.m_nValue << " " << storage.m_dValue << '\n';
	else // display double first
		std::cout << storage.m_dValue << " " << storage.m_nValue << '\n'; // 6.7 5
}

int test_friend15()
{
	Storage_ storage(5, 6.7);
	Display_ display(false);

	display.displayItem(storage);

	return 0;
}
