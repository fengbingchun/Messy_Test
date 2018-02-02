#include "static_cast.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/51235498

void CCTest::setNumber(int num) { number = num; }

void CCTest::printNumber() const {
	std::cout << "\nBefore: " << number;
	//this 指针的数据类型为 const CCTest *。
	//const_cast 运算符会将 this 指针的数据类型更改为 CCTest *，以允许修改成员 number。
	//强制转换仅对其所在的语句中的其余部分持续
	const_cast< CCTest * >(this)->number--;
	std::cout << "\nAfter: " << number;
}

void A3::f()
{

}

void B3::f()
{

}

void B4::f()
{

}

void D4::f()
{

}

unsigned short Hash(void *p) {
	//reinterpret_cast 允许将指针视为整数类型。结果随后将按位移位并与自身进行“异或”运算以生成唯一的索引（具有唯一性的概率非常高）。
	//该索引随后被标准 C 样式强制转换截断为函数的返回类型。
	unsigned int val = reinterpret_cast<unsigned int>(p);
	return (unsigned short)(val ^ (val >> 16));
}

// C风格强制类型转换
void test_static_cast1()
{
	float a = 1.1, b = 1.9;

	int ret1 = (int)a;
	int ret2 = int(b);

	std::cout << ret1 << "    " << ret2 << "    " << std::endl;
}

void test_static_cast2(B1* pb, D1* pd)
{
	//与 dynamic_cast 不同，pb 的 static_cast 转换不执行运行时检查。
	//由 pb 指向的对象可能不是 D 类型的对象，在这种情况下使用 *pd2 会是灾难性的。
	//例如，调用 D 类（而非 B 类）的成员函数可能会导致访问冲突。
	D1* pd2 = static_cast<D1*>(pb);   // Not safe, D can have fields and methods that are not in B.
	B1* pb2 = static_cast<B1*>(pd);   // Safe conversion, D always contains all of B.
}

void test_static_cast3(B1* pb)
{
	//如果 pb 确实指向 D 类型的对象，则 pd1 和 pd2 将获取相同的值。如果 pb == 0，它们也将获取相同的值。
	//如果 pb 指向 B 类型的对象，而非指向完整的 D 类，则 dynamic_cast 足以判断返回零。
	//但是，static_cast 依赖于程序员的断言，即 pb 指向 D 类型的对象，因而只是返回指向那个假定的 D 对象的指针。
	D1* pd1 = dynamic_cast<D1*>(pb);
	D1* pd2 = static_cast<D1*>(pb);
}

void test_static_cast4()
{
	char ch;
	int i = 65;
	float f = 2.5;
	double dbl;

	ch = static_cast<char>(i);   // int to char
	dbl = static_cast<double>(f);   // float to double
	i = static_cast<int>(ch);
}

void test_static_cast5()
{
	CCTest X;
	X.setNumber(8);
	X.printNumber();
}

void test_static_cast6(D2* pd)
{
	//此转换类型称为“向上转换”，因为它将在类层次结构上的指针，从派生的类移到该类派生的类。向上转换是一种隐式转换。
	C2* pc = dynamic_cast<C2*>(pd);   // ok: C is a direct base class pc points to C subobject of pd 
	B2* pb = dynamic_cast<B2*>(pd);   // ok: B is an indirect base class pb points to B subobject of pd
}

void test_static_cast7()
{
	A3* pa = new A3;
	B3* pb = new B3;
	void* pv = dynamic_cast<void*>(pa);// pv now points to an object of type A
	pv = dynamic_cast<void*>(pb);// pv now points to an object of type B
}

void test_static_cast8()
{
	B4* pb = new D4;   // unclear but ok
	B4* pb2 = new B4;

	//此转换类型称为“向下转换”，因为它将在类层次结构下的指针，从给定的类移到该类派生的类。
	D4* pd = dynamic_cast<D4*>(pb);   // ok: pb actually points to a D
	D4* pd2 = dynamic_cast<D4*>(pb2);   // pb2 points to a B not a D
}

void test_static_cast9()
{
	A3* pa = new A3;
	B3* pb = dynamic_cast<B3*>(pa);   // fails at runtime, not safe;B not derived from A
}

void test_static_cast10()
{
	int a[20];
	for (int i = 0; i < 20; i++) {
		std::cout << Hash(a + i) << std::endl;
	}
}

