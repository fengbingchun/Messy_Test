#include "return_value_optimization.hpp"
#include <iostream>
#include <chrono>

// Blog: https://blog.csdn.net/fengbingchun/article/details/84185474

namespace return_value_optimization_ {

// reference: 《提高C++性能的编程技术》：第四章：返回值优化

class Complex {
	friend Complex operator + (const Complex&, const Complex&);
	friend void Complex_Add(const Complex&, const Complex&, Complex&);
	friend Complex Complex_Add2(const Complex&, const Complex&);
	friend Complex Complex_Add3(const Complex&, const Complex&);

public:
	Complex(double r =0.0, double i =0.0) : real(r), imag(i) {} // 默认构造函数
	Complex(const Complex& c) : real(c.real), imag(c.imag) {} // 拷贝构造函数
	Complex(const Complex& a, const Complex& b) : real(a.real + b.real), imag(a.imag + b.imag) {} // 计算性构造函数
	Complex& operator = (const Complex& c) { this->real = c.real; this->imag = c.imag; return *this; }// 赋值运算符
	~Complex() {}

private:
	double real;
	double imag;

};

Complex operator + (const Complex& a, const Complex& b)
{
	Complex retVal;
	retVal.real = a.real + b.real;
	retVal.imag = a.imag + b.imag;

	return retVal;
}

// 消除局部对象retVal，直接把返回值放到__tempResult临时对象中来实现优化，这就是返回值优化(RVO)
void Complex_Add(const Complex& a, const Complex&b, Complex& __tempResult)
{
	__tempResult.real = a.real + b.real;
	__tempResult.imag = a.imag + b.imag;
}

Complex Complex_Add2(const Complex& a, const Complex& b)
{
	Complex retVal;
	retVal.real = a.real + b.real;
	retVal.imag = a.imag + b.imag;

	return retVal;
}

// 通过计算性构造函数来执行加操作
Complex Complex_Add3(const Complex& a, const Complex& b)
{
	return Complex(a, b);
}

int test_return_value_optimization_1()
{
	// 测试两种加操作的实现性能:普通加操作、RVO加操作
	using namespace std::chrono;
	high_resolution_clock::time_point time_start, time_end;
	const int cycle_number {100000000};

{ // 普通加操作
	Complex a(1, 0);
	Complex b(2, 0);
	Complex c;

	time_start = high_resolution_clock::now();
	for (int i = 0; i < cycle_number; ++i) {
		c = a + b;
	}
	time_end = high_resolution_clock::now();
	std::cout<<"common add time spent: "<<(duration_cast<duration<double>>(time_end - time_start)).count()<<" seconds\n";
}

{ // RVO加操作
	Complex a(1, 0);
	Complex b(2, 0);
	Complex c;
	
	time_start = high_resolution_clock::now();
	for (int i = 0; i < cycle_number; ++i) {
		Complex_Add(a, b, c);
	}
	time_end = high_resolution_clock::now();
	std::cout<<"RVO add time spent: "<<(duration_cast<duration<double>>(time_end - time_start)).count()<<" seconds\n";
}

	// 测试两种加操作的实现性能：普通加操作、使用计算性构造函数

{ // 普通加操作
	Complex a(1, 0);
	Complex b(2, 0);
	Complex c;

	time_start = high_resolution_clock::now();
	for (int i = 0; i < cycle_number; ++i) {
		c = Complex_Add2(a, b);
	}
	time_end = high_resolution_clock::now();
	std::cout<<"common add time spent: "<<(duration_cast<duration<double>>(time_end - time_start)).count()<<" seconds\n";
}

{ // 使用计算性构造函数
	Complex a(1, 0);
	Complex b(2, 0);
	Complex c;

	time_start = high_resolution_clock::now();
	for (int i = 0; i < cycle_number; ++i) {
		c = Complex_Add3(a, b);
	}
	time_end = high_resolution_clock::now();
	std::cout<<"Computational Constructors add time spent: "<<(duration_cast<duration<double>>(time_end - time_start)).count()<<" seconds\n";

}

	return 0;
}

} // namespace return_value_optimization_

