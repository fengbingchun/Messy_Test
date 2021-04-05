#include "class.hpp"
#include <iostream>
#include <cmath>
#include<random>
#include <string>

namespace class_ {

// Blog: https://blog.csdn.net/fengbingchun/article/details/115440669
 
class Ops {
public:
	Ops() = default;
	Ops(const int* p1, const int* p2) : value1_(p1), value2_(p2) {}
	Ops(const std::string& str) : addr_(str) {}

	int add(int a, int b) { return (a + b); }
	void sub(int a, int b) { fprintf(stdout, "sub: %d\n", (a - b)); }

	int (Ops::* op)(int, int);
	
	const int *value1_ = nullptr, *value2_ = nullptr;
	std::string addr_ = "";
};

const int* Ops::* select()
{
	std::random_device rd; std::mt19937 generator(rd()); // 每次产生不固定的不同的值
	std::uniform_int_distribution<int> distribution(0, 2);

	if (distribution(generator)) return &Ops::value1_;
	else return &Ops::value2_;
}

void print(int a, int b, Ops& ops, int (Ops::* fp)(int, int))
{
	int value = (ops.*fp)(a, b);
	fprintf(stdout, "value: %d\n", value);
}

int test_class3()
{
	// 类的成员函数
	int (Ops::* func1)(int, int); // 一个类成员函数指针变量func1的定义
	func1 = &Ops::add; // 类成员函数指针变量func1被赋值

	Ops ops, *p;
	p = &ops;
	int ret = (ops.*func1)(2, 3); // 对实例ops，调用成员函数指针变量func1所指的函数
	fprintf(stdout, "add: %d\n", ret);
	ret = (p->*func1)(-2, -3);  // 对p所指的实例，调用成员函数指针变量func1所指的函数
	fprintf(stdout, "add2: %d\n", ret);

	void (Ops::* func2)(int, int);
	func2 = &Ops::sub; // 函数指针赋值要使用&
	(ops.*func2)(9, 3); 
	(ops.*func2)(3, 9);

	Ops ops2;
	int (Ops::* func3)(int, int) = &Ops::add; // 定义类成员函数指针并赋值
	ret = (ops2.*func3)(7, 4);
	fprintf(stdout, "add3: %d\n", ret);

	Ops ops5;
	print(1, 6, ops5, &Ops::add);

	Ops ops6;
	ops6.op = &Ops::add;
	fprintf(stdout, "value2: %d\n", (ops6.*(ops6.op))(-2, -6));

	// 类的数据成员
	const int a = 13, b = 15;
	Ops ops3(&a, &b);

	const int* Ops::* value = select();
	fprintf(stdout, "value1: %d\n", *(ops3.*value));

	std::string Ops::* str = &Ops::addr_; // 定义时和类关联
	Ops ops4("https://blog.csdn.net/fengbingchun");
	fprintf(stdout, "addr: %s\n", (ops4.*str).c_str()); // 使用时和对象关联

	Ops ops7;
	ops7.addr_ = "https://github.com/fengbingchun"; // 直接访问
	fprintf(stdout, "addr is: %s\n", ops7.addr_.c_str());
	std::string Ops::* addr2 = &Ops::addr_;
	ops7.*addr2 = "https://blog.csdn.net/fengbingchun"; // 通过指向成员的指针进行访问
	fprintf(stdout, "addr is: %s\n", ops7.addr_.c_str());

	return 0;
}


// Blog: http://blog.csdn.net/fengbingchun/article/details/52075202

///////////////////////////////////////
// reference: http://www.cplusplus.com/doc/tutorial/classes/
class Circle {
private:
	double radius;
public:
	Circle(double r) : radius(r) { }
	double area() { return radius * radius*3.14159265; }
};

class Cylinder {
private:
	Circle base;
	double height;
public:
	Cylinder(double r, double h) : base(r), height(h) {}
	double volume() { return base.area() * height; }
};

int test_class1()
{
	Cylinder foo(10, 20);

	std::cout << "foo's volume: " << foo.volume() << '\n';

	return 0;
}

////////////////////////////////////////////////////
// reference: http://www.cs.rochester.edu/u/nelson/courses/csc_173/review/CppClasses.html
class Complex
{
private:
	double re;
	double im;

public:
	Complex(float r, float i) { re = r; im = i; }
	Complex(float r) { re = r; im = 0.0; }
	~Complex() {};

	double Magnitude();        // calculate magnitude

	double Real() { return re; } // return real part
	inline double Imag();      // return imaginary part

	Complex operator+(Complex b)
	{
		return Complex(re + b.re, im + b.im);
	}

	Complex operator=(Complex b)
	{
		re = b.re; im = b.im;
		return *this;
	}
};

inline double Complex::Imag()
{
	return im;
}

double Complex::Magnitude()
{
	return std::sqrt(re*re + Imag()*Imag());
}

int test_class2()
{
	Complex a(1.0, 1.0);
	Complex b(5.0);

	printf("a real = %f  a imaginary = %f\n", a.Real(), a.Imag());
	printf("b real = %f  b imaginary = %f\n", b.Real(), b.Imag());

	return 0;
}

} // namespace class_
