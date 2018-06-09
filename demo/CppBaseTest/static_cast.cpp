#include "static_cast.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/51235498

void CCTest::setNumber(int num) { number = num; }

void CCTest::printNumber() const {
	std::cout << "\nBefore: " << number;
	//this ָ�����������Ϊ const CCTest *��
	//const_cast ������Ὣ this ָ����������͸���Ϊ CCTest *���������޸ĳ�Ա number��
	//ǿ��ת�����������ڵ�����е����ಿ�ֳ���
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

#ifdef _MSC_VER
unsigned short Hash(void *p) {
	//reinterpret_cast ����ָ����Ϊ�������͡������󽫰�λ��λ����������С��������������Ψһ������������Ψһ�Եĸ��ʷǳ��ߣ���
	//��������󱻱�׼ C ��ʽǿ��ת���ض�Ϊ�����ķ������͡�
	unsigned int val = reinterpret_cast<unsigned int>(p);
	return (unsigned short)(val ^ (val >> 16));
}
#endif

// C���ǿ������ת��
void test_static_cast1()
{
	float a = 1.1, b = 1.9;

	int ret1 = (int)a;
	int ret2 = int(b);

	std::cout << ret1 << "    " << ret2 << "    " << std::endl;
}

void test_static_cast2(B1* pb, D1* pd)
{
	//�� dynamic_cast ��ͬ��pb �� static_cast ת����ִ������ʱ��顣
	//�� pb ָ��Ķ�����ܲ��� D ���͵Ķ��������������ʹ�� *pd2 ���������Եġ�
	//���磬���� D �ࣨ���� B �ࣩ�ĳ�Ա�������ܻᵼ�·��ʳ�ͻ��
	D1* pd2 = static_cast<D1*>(pb);   // Not safe, D can have fields and methods that are not in B.
	B1* pb2 = static_cast<B1*>(pd);   // Safe conversion, D always contains all of B.
}

void test_static_cast3(B1* pb)
{
	//��� pb ȷʵָ�� D ���͵Ķ����� pd1 �� pd2 ����ȡ��ͬ��ֵ����� pb == 0������Ҳ����ȡ��ͬ��ֵ��
	//��� pb ָ�� B ���͵Ķ��󣬶���ָ�������� D �࣬�� dynamic_cast �����жϷ����㡣
	//���ǣ�static_cast �����ڳ���Ա�Ķ��ԣ��� pb ָ�� D ���͵Ķ������ֻ�Ƿ���ָ���Ǹ��ٶ��� D �����ָ�롣
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
	//��ת�����ͳ�Ϊ������ת��������Ϊ���������νṹ�ϵ�ָ�룬�����������Ƶ������������ࡣ����ת����һ����ʽת����
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

	//��ת�����ͳ�Ϊ������ת��������Ϊ���������νṹ�µ�ָ�룬�Ӹ��������Ƶ������������ࡣ
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
#ifdef _MSC_VER
		std::cout << Hash(a + i) << std::endl;
#endif
	}
}

