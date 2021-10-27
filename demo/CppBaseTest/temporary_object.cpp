#include "temporary_object.hpp"
#include <iostream>
#include <chrono>
#include <string>

// Blog: https://blog.csdn.net/fengbingchun/article/details/84192535

namespace temporary_object_ {

// reference: 《提高C++性能的编程技术》：第五章：临时对象

class Rational {
	friend Rational operator + (const Rational&, const Rational&);

public:
	Rational(int a = 0, int b = 1) : m(a), n(b) {}
private:
	int m; // 分子
	int n; // 分母
};

template<class T>
void g(T formalArg)
{

}

std::string f()
{
	std::string s;
	// ....
	return s;
}

int test_temporary_object_1()
{
{ // 对象定义
	// 实例化Rational对象: 只有第一种初始化形式可以保证在编译器的执行过程中不产生临时对象。如果使用第2种或第3种形式，很可能产生临时对象，这依赖于编译器的实现。
	// 实际上，大多数编译器会通过优化省去临时对象,所以此处给出的3种初始化形式在效率上是等效的
	Rational r1(100); // 1
	Rational r2 = Rational(100); // 2
	Rational r3 = 100; // 3
}

{ // 类型不匹配
	// Rational类没有声明接收整形参数的赋值运算符。然而编译器希望右边是Rational对象，这样可以按字节传给左边。所以，编译器必须想办法将我们提供的整形参数转换成Rational对象。幸运的是(对性能来说是不幸的),我们有构造函数知道如何根据一个整形参数创建Rational对象
	// 为了易于编程，编译器可以自由地转换类型。新的C++标准允许我们限制编译器禁止这种转换，可以通过声明构造函数为explicit来实现
	Rational r;
	r = 100;
	// 可以通过重载函数Rational::operator=()以接收整形参数，从而消除临时对象
	// Rational& operator = (int a) { m=a; n=1; return *this; }
	// 同样的原理可以推广到所有的函数调用。假设g()是一个接收string引用参数的函数调用
	// void g(const string& s) { ... }
	// 除非重载g()让它接收char*参数，否则调用g("message")会产生临时的string对象
}

{ // 按值传递
	// 因为存在局部参数formalArg, g()的激活记录在栈上设置了占位符。编译器复制对象t的内容至g()位于栈上的formalArg中。对此，一种常用的做法是生成临时对象
	// 编译器将创建int类型的临时对象，并且使用t作为输入参数来复制构造它.然后临时对象作为实参传递给g()。该新创建的临时对象将按引用方式传递给g(). 
	int t = 0;
	g(t);
}

{ // 按值返回
	// f()的返回值是string对象，编译器生成临时对象来存储返回值。然后存储f()返回值的临时对象赋给左边的对象p
	std::string p;
	p = f();

	std::string s1 = "Hello";
	std::string s2 = "Wold";
	std::string s3_1 = s1 + s2; // 此处没有临时对象
	std::string s3_2;
	s3_2 = s1 + s2; // 此处产生临时对象
}

{ // 使用op=()消除临时对象
	std::string s1, s2, s3;
	s1 = s2 + s3; // 此处产生临时对象
	s3 = s1; // operator=(),没有临时对象
	s3 += s2; // operator+=(),没有临时对象}
}

{ // 两种方式计算s5
	std::string s1, s2, s3, s4, s5;
	// 1. 产生三个临时对象
	s5 = s1 + s2 + s3 + s4;

	// 2. 虽然"丑陋"但更高效，因为它不产生临时对象
	s5 = s1;
	s5 += s2;
	s5 += s3;
	s5 += s4;
}

	return 0;
}

} // namespace temporary_object_

