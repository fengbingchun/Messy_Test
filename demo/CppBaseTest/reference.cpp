#include "reference.hpp"
#include <iostream>
#include <utility> // std::move

// Blog: http://blog.csdn.net/fengbingchun/article/details/69820184

int test_reference_1()
{
	// 1. 普通的引用
	int ival = 1024;
	int &refVal = ival; // refVal指向ival(是ival的另一个名字)
	//int &refVal2; // error：引用必须被初始化
	int &refVal3 = refVal; // refVal3绑定到了那个与refVal绑定的对象上，这里就是绑定到ival上
	// 利用与refVal绑定的对象的值初始化变量i
	int i = refVal; // correct：i被初始化为ival的值
	// 允许在一条语句中定义多个引用，其中每个引用标识符都必须以符号&开头
	int i1 = 1024, i2 = 2048;
	int &r = i1, r2 = i2;
	int i3 = 1024, &ri = i3;
	int &r3 = i3, &r4 = i2; // r3和r4都是引用
	//int &refVal4 = 10; // error: 引用类型的初始值必须是一个对象
	double dval = 3.14;
	//int &refVal5 = dval; // error: 此处引用类型的初始值必须是int型对象
	const int &refVal6 = dval; // correct
	// 编译器把上述语句变成了如下形式：
	//const int temp = dval; // 由双精度浮点数生成一个临时的整型常量
	//const int &refVal6 = temp; // 让refVal6绑定这个临时量

	// 2. const的引用
	// 对常量的引用不能被用作修改它所绑定的对象
	const int ci = 1024;
	const int &r1 = ci; // correct: 引用及其对应的对象都是常量
	//r1 = 42; // error: r1是对常量的引用
	//int &r2 = ci; // error: 试图让一个非常量引用指向一个常量对象

	int i4 = 42;
	const int &r6 = i4; // 允许将const int&绑定到一个普通int对象上
	const int &r7 = 42; // correct: r7是一个常量引用
	const int &r8 = r6 * 2; // correct: r8是一个常量引用
	//int &r9 = r6 * 2; // error: r9是一个普通的非常量引用

	// 常量的引用仅对引用可参与的操作做出了限定，对于引用的对象本身是不是一个常量未作限定
	int x = 42;
	int &rx = x; // 引用rx绑定对象x
	const int &ry = x; // ry也绑定对象x,但是不允许通过ry修改x的值
	rx = 0; // rx并非常量，x的值修改为0
	//ry = 0; // error: ry是一个常量引用

	return 0;
}

// 该函数接受一个int对象的引用，然后将对象的值置为0
static void reset(int &i) // i是传给reset函数的对象的另一个名字
{
	i = 0; // 改变了i所引用对象的值
}

int test_reference_2()
{
	int j = 42;
	reset(j); // j采用引用方式，它的值被改变
	fprintf(stderr, "j = %d\n", j); // j = 0

	return 0;
}

int test_reference_3()
{
	int i = 42;
	int &r = i; // correct: r引用i
	//int &&rr = i; // error: 不能将一个右值引用绑定到一个左值上
	//int &r2 = i * 42; // error: i*42是一个右值
	const int &r3 = i * 42; // correct: 可以将一个const的引用绑定到一个右值上
	int &&rr2 = i * 42; // correct: 将rr2绑定到乘法结果上

	int &&rr1 = 42; // correct: 字面常量是右值
	//int &&rr3 = rr1; // error: 表达式rr1是左值
	int &&rr4 = std::move(rr1); // correct

	return 0;
}

