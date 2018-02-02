#include "class.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52075202

///////////////////////////////////////
// reference: http://www.cplusplus.com/doc/tutorial/classes/
class Circle {
private:
	double radius;
public:
	Circle(double r) : radius(r) { }
	double area() { return radius*radius*3.14159265; }
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
	return sqrt(re*re + Imag()*Imag());
}

int test_class2()
{
	Complex a(1.0, 1.0);
	Complex b(5.0);

	printf("a real = %f  a imaginary = %f\n", a.Real(), a.Imag());
	printf("b real = %f  b imaginary = %f\n", b.Real(), b.Imag());

	return 0;
}
