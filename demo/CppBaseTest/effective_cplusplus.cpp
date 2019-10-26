#include "effective_cplusplus.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <iterator>
#include <new>

// Blog: https://blog.csdn.net/fengbingchun/article/details/102761542

// reference: 《Effective C++》第三版

namespace effective_cplusplus_ {

////////////////////////////////////
int test_item_1()
{
	return 0;
}

////////////////////////////////////
class GamePlayer {
private:
	static const int NumTurns = 5; // 常量声明式
	int scores[NumTurns]; // 使用该常量
};

// 注意：由于class常量已在声明时获得初值(设初值为5),因此定义时不可以再设初值
const int GamePlayer::NumTurns; // NumTurns的定义

void f(int) {}
#define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b)) // 不推荐
template<typename T>
inline void callWithMax(const T& a, const T& b) // 推荐
{
	f(a > b ? a : b);
}

int test_item_2()
{
	#define ASPECT_RATIO 1.653 // 不推荐
	const double AspectRatio = 1.653; // 推荐

	{const char* const authorName = "Scott Meyers";} // 推荐
	const std::string autorName("Scott Meyers"); // 更推荐

	return 0;
}

////////////////////////////////////
class TextBlock {
public:
	TextBlock(const std::string& str) { text = str; }
	// 两个成员函数如果只是常量性(constness)不同，可以被重载
	const char& operator[] (std::size_t position) const // operator[] for const对象
	{ return text[position]; }
	//char& operator[] (std::size_t position) // operator[] for non-const对象
	//{ return text[position]; }
	// 在const和non-const成员函数中避免重复
	char& operator[] (std::size_t position) // 现在只调用const op[]
	{ return const_cast<char&>( // 将const op[]返回值的const移除
		static_cast<const TextBlock&>(*this) // 为*this加上const，调用const op[]
		[position]); }

private:
	std::string text;
};

void print(const TextBlock& ctb) // ctb是const
{
	std::cout<< ctb[0]; // 调用const TextBlock::operator []
}

int test_item_3()
{
	char greeting[] = "Hello";
	{char* p = greeting;} // non-const pointer, non-const data
	{const char* p = greeting;} // non-const pointer, const data
	{char* const p = greeting;} // const pointer, non-const data
	{const char* const p = greeting;} //const pointer, const data

	std::vector<int> vec(1);
	const std::vector<int>::iterator iter = vec.begin(); // iter的作用像个T* const
	*iter = 10; // 没问题，改变iter所指物
	//++iter; // 错误，iter是const

	std::vector<int>::const_iterator cIter = vec.begin(); // cIter的作用像个const T*
	//*cIter = 10; // 错误，*cIter是const
	++cIter; // 没问题，改变cIter

	TextBlock tb("Hello");
	std::cout<< tb[0]; // 调用non-const TextBlock::operator []
	const TextBlock ctb("World");
	std::cout<< ctb[0]; // 调用const TextBlock::operator []
	print(ctb);
	print(tb);

	return 0;
}

////////////////////////////////////
class ABEntry {
public:
	ABEntry(const std::string& name, const std::string& address);
	ABEntry(const std::string& name, const std::string& address, int phones);
	ABEntry();
private:
	std::string theName;
	std::string theAddress;
	int thePhones;
};

ABEntry::ABEntry(const std::string& name, const std::string& address)
{
	// 这些都是赋值(assignments)而非初始化(initializations)
	// 首先调用default构造函数为这些变量设初值，然后立刻再对它们赋予新值
	theName = name;
	theAddress = address;
	thePhones = 2;
}

ABEntry::ABEntry(const std::string& name, const std::string& address, int phones)
	: theName(name), theAddress(address), thePhones(phones) // 这些都是初始化(initializations)
{} // 构造函数本体不必有任何动作

ABEntry::ABEntry() : theName(), theAddress(), thePhones(0) // 调用theName等的default构造函数
{}

int test_item_4()
{
	return 0;
}

////////////////////////////////////
class Empty {};

int test_item_5()
{
	Empty e1; // default构造函数
	Empty e2(e1); // copy构造函数
	e2 = e1; // copy assignment操作符

	return 0;
}

////////////////////////////////////
class Uncopyable {
protected:
	Uncopyable() {} // 允许derived对象构造和析构
	~Uncopyable() {}
private:
	Uncopyable(const Uncopyable&); // 但阻止copying
	Uncopyable& operator= (const Uncopyable&);
};

class HomeForSale: private Uncopyable {
// class不再声明copy构造函数或copy assign操作符
};

int test_item_6()
{
	HomeForSale h1;
	HomeForSale h2;
	//HomeForSale h3(h1); // 不会通过编译
	//h1 = h2; // 也不该通过编译

	return 0;
}

////////////////////////////////////
class AWOV { // AWOV = "Abstract w/o Virtuals"
public:
	virtual ~AWOV() = 0; // 声明pure virtual析构函数
};

AWOV::~AWOV() {} // 必须为这个pure virtual析构函数提供一份定义

int test_item_7()
{
	return 0;
}

////////////////////////////////////
int test_item_8()
{
	return 0;
}

////////////////////////////////////
int test_item_9()
{
	return 0;
}

////////////////////////////////////
class Widget {
public:
	Widget& operator= (const Widget& rhs) // 返回类型是个reference,指向当前对象
	{
		return *this;
	}

	Widget& operator+= (const Widget& rhs) // 这个协议适用于+=、-=、*=等等
	{
		return *this;
	}

	Widget& operator= (int rhs) // 此函数也适用，即使此一操作符的参数类型不符协定
	{
		return *this;
	}
};

int test_item_10()
{
	return 0;
}

////////////////////////////////////
class Widget11 {
public:
	void swap(Widget11& rhs) {} // 交换*this和rhs的数据

	Widget11& operator= (const Widget11& rhs)
	{
		Widget11 temp(rhs); // 为rhs数据制作一份复件(副本)
		swap(temp); // 将*this数据和上述复件的数据交换
		return *this;
	}
};

int test_item_11()
{
	Widget11 w;
	w = w; // 赋值给自己

	return 0;
}

////////////////////////////////////
void logCall(const std::string& funcName) {} // 制造一个log entry

class Customer {
public:
	Customer(const Customer& rhs)
		: name(rhs.name) // 复制rhs的数据
	{
		logCall("Customer copy constructor");
	}

	Customer& operator= (const Customer& rhs)
	{
		logCall("Customer copy assignment operator");
		name = rhs.name; // 复制rhs的数据
		return *this;
	}

private:
	std::string name;
};

class PriorityCustomer : public Customer {
public:
	PriorityCustomer(const PriorityCustomer& rhs)
		: Customer(rhs), // 调用base class的copy构造函数
		  priority(rhs.priority)
	{
		logCall("PriorityCustormer copy constructor");
	}

	PriorityCustomer& operator= (const PriorityCustomer& rhs)
	{
		logCall("PriorityCustomer copy assignment operator");
		Customer::operator=(rhs); // 对base class成分进行赋值操作
		priority =  rhs.priority;
		return*this;
	}

private:
	int priority;
};

int test_item_12()
{
	return 0;
}

////////////////////////////////////
int test_item_13()
{
	return 0;
}

////////////////////////////////////
int test_item_14()
{
	return 0;
}

////////////////////////////////////
int test_item_15()
{
	return 0;
}

////////////////////////////////////
int test_item_16()
{
	std::string* stringPtr1 = new std::string;
	std::string* stringPtr2 = new std::string[100];

	delete stringPtr1;    // 删除一个对象
	delete [] stringPtr2; // 删除一个由对象组成的数组

	typedef std::string AddressLines[4]; // 每个人的地址有4行，每行是一个string
	std::string* pal = new AddressLines; // 注意："new AddressLines"返回一个string*,就像"new string[4]"一样

	//delete pal;    // 行为未有定义
	delete [] pal; // 很好

	return 0;
}

////////////////////////////////////
class Widget17 {};
int priority() { return 0; }
void processWidget(std::shared_ptr<Widget17> pw, int priority) {}

int test_item_17()
{
	// 执行new Widget17; 调用priority; 调用std::shared_ptr构造函数，它们的执行顺序不确定
	processWidget(std::shared_ptr<Widget17>(new Widget17), priority()); // 可能泄露资源
	
	std::shared_ptr<Widget17> pw(new Widget17); // 在单独语句内以智能指针存储newed所得对象
	processWidget(pw, priority()); // 这个调用动作绝不至于造成泄露

	return 0;
}

////////////////////////////////////
int test_item_18()
{
	return 0;
}

////////////////////////////////////
int test_item_19()
{
	return 0;
}

////////////////////////////////////
int test_item_20()
{
	return 0;
}

////////////////////////////////////
class Rational {
public:
	Rational(int numerator = 0, int denominator = 1) : n(numerator), d(denominator)
	{}

private:
	int n, d; // 分子(numerator)和分母(denominator)

// 返回const Rational可以预防"没意思的赋值动作": Rational a, b, c; (a * b) = c;
friend const Rational operator* (const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.n * rhs.n, lhs.d * rhs.d);
}

};

int test_item_21()
{
	return 0;
}

////////////////////////////////////
int test_item_22()
{
	return 0;
}

////////////////////////////////////
int test_item_23()
{
	return 0;
}

////////////////////////////////////
class Rational24 {
public:
	Rational24(int numerator = 0, int denominator = 1) {} // 构造函数刻意不为explicit,允许int-to-Rational24隐式转换
	int numerator() const { return 1; } // 分子(numerator)的访问函数
	int denominator() const { return 2; } // 分母(denominator)的访问函数

	/*const Rational24 operator* (const Rational24& rhs) const
	{
		return Rational24(this->n * rhs.numerator(), this->d * rhs.denominator());
	}*/

private:
	int n, d;
};

const Rational24 operator* (const Rational24& lhs, const Rational24& rhs) // non-member函数
{
	return Rational24(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

int test_item_24()
{
	Rational24 oneEighth(1, 8);
	Rational24 oneHalf(1, 2);
	Rational24 result = oneHalf * oneEighth; // 很好
	result = result * oneEighth; // 很好

	result = oneHalf * 2; // 很好,隐式类型转换(implicit type conversion)
	result = 2 * oneHalf; // 错误, only non-member function success

	// 以对应的函数形式重写上述两个式子
	//result = oneHalf.operator*(2); // 很好, only member function success
	//result = 2.operator*(oneHalf); // 错误, only non-member function success

	result = operator*(2, oneHalf); // 错误, only non-member function success

	return 0;
}

////////////////////////////////////
class WidgetImpl { // 针对Widget25数据而设计的class
public:
private:
	int a, b, c; // 可能有许多数据，意味复制时间很长
	std::vector<double> v;
};

class Widget25 { // 这个class使用pimpl(pointer to implementation)手法
public:
	Widget25(const Widget25& rhs) {}
	Widget25& operator= (const Widget25& rhs) // 复制Widget25时，令它复制其WidgetImpl对象
	{
		*pImpl = *(rhs.pImpl);

		return *this;
	}

	void swap(Widget25& other)
	{
		using std::swap;
		swap(pImpl, other.pImpl); // 若要置换Widget25就置换其pImpl指针
	}

private:
	WidgetImpl* pImpl; // 指针，所指对象内含Widget25数据
};


int test_item_25()
{
	return 0;
}

////////////////////////////////////
int test_item_26()
{
	return 0;
}

////////////////////////////////////
int test_item_27()
{
	return 0;
}

////////////////////////////////////
class Point { // 这个class用来表述"点"
public:
	Point(int x, int y) {}
	void setX(int newVal) {}
	void setY(int newVal) {}
};

struct RectData { // 这些"点"数据用来表现一个矩形
	Point ulhc; // ulhc = "upper left-hand corner"(左上角)
	Point lrhc; // lrhc = "lower right-hand corner"(右上角)
};

class Rectangle {
public:
	Rectangle(const Point&, const Point&) {}
	Point& upperLeft() const { return pData->ulhc; }
	Point& lowerRight() const { return pData->lrhc; }

	// 有了这样的改变，客户可以读取矩形的Point，但不能涂写它们
	// 但即使如此，也可能导致dangling handles(空悬的号码牌):这种handles所指东西(的所属对象)不复存在
	//const Point& upperLeft() const { return pData->ulhc; }
	//const Point& lowerRight() const { return pData->lrhc; }

private:
	std::shared_ptr<RectData> pData;
};

int test_item_28()
{
	Point coord1(0, 0);
	Point coord2(100, 100);
	const Rectangle rec(coord1, coord2); // rec是个const矩形，从(0,0)到(100,100)

	// upperLeft的调用者能够使用被返回的reference(指向rec内部的Point成员变量)来更改成员，但rec其实应该是不可变的(const)
	rec.upperLeft().setX(50); // 现在rec却变成从(50,0)到(100,100)

	return 0;
}

////////////////////////////////////
int test_item_29()
{
	return 0;
}

////////////////////////////////////
inline void f() {} // 假设编译器有意愿inline“对f的调用”

int test_item_30()
{
	void (*pf)() = f; // pf指向f

	f(); // 这个调用将被inlined,因为它是一个正常调用
	pf(); // 这个调用或许不被inlined,因为它通过函数指针达成

	return 0;
}

////////////////////////////////////
int test_item_31()
{
	return 0;
}

////////////////////////////////////
int test_item_32()
{
	return 0;
}

////////////////////////////////////
class Base {
private:
	int x;

public:
	virtual void mf1() = 0;
	virtual void mf1(int) {}
	virtual void mf2() {}
	void mf3() {}
	void mf3(double) {}
};

class Derived : public Base {
public:
	virtual void mf1() {}
	void mf3() {}
	void mf4() {}
};

class Derived33 : public Base {
public:
	// 必须为那些原本会被遮掩的每个名称引入一个using声明式，否则某些你希望继承的名称会被遮掩
	using Base::mf1; // 让Base class内名为mf1和mf3的所有东西在Derived作用域内都可见(并且public)
	using Base::mf3;
	virtual void mf1() {}
	void mf3() {}
	void mf4() {}
};

int test_item_33()
{
	Derived d;
	int x = 0;

	d.mf1(); // 没问题，调用Derived::mf1
	//d.mf1(x); // 错误，因为Derived::mf1遮掩了Base::mf1
	d.mf2(); // 没问题，调用Base::mf2
	d.mf3(); // 没问题，调用Derived::mf3
	// Derived内的函数mf3遮掩了一个名为mf3但类型不同的Base函数
	//d.mf3(x); // 错误，因为Derived::mf3遮掩了Base::mf3

	Derived33 d2;

	d2.mf1(); // 仍然没问题，仍然调用Derived::mf1
	d2.mf1(x); // 现在没问题了，调用Base::mf1
	d2.mf2(); // 仍然没问题，调用Base::mf2
	d2.mf3(); // 没问题，调用Derived::mf3
	d2.mf3(x); // 现在没问题了，调用Base::mf3


	return 0;
}

////////////////////////////////////
int test_item_34()
{
	return 0;
}

////////////////////////////////////
class GameCharacter {
public:
	int healthValue() const // derived classes不重新定义它
	{
		// ... // 做一些事前工作
		int retVal = doHealthValue(); // 做真正的工作
		// ... // 做一些事后工作

		return retVal;
	}

private:
	virtual int doHealthValue() const // derived classes可重新定义它
	{
		return 10;
	}
};

// Strategy设计模式的简单应用
class GameCharacter35; // 前置声明(forward declaration)
int defaultHealthCalc(const GameCharacter35& gc) { return 1; }
class GameCharacter35 {
public:
	typedef int (*HealthCalcFunc)(const GameCharacter35&);
	explicit GameCharacter35(HealthCalcFunc hcf = defaultHealthCalc) : healthFunc(hcf) {}
	int healthValue() const
	{
		return healthFunc(*this); 
	}

private:
	HealthCalcFunc healthFunc;
};

class EvilBadGuy : public GameCharacter35 {
public:
	explicit EvilBadGuy(HealthCalcFunc hcf = defaultHealthCalc) : GameCharacter35(hcf) {}
};

int loseHealthQuickly(const GameCharacter35&) { return 2; } // 健康指数计算函数1
int loseHealthSlowly(const GameCharacter35&) { return 3; } // 健康指数计算函数2

// 藉由std::function完成Strategy模式
class GameCharacter35_1;
int defaultHealthCalc_1(const GameCharacter35_1& gc) { return 11; }
class GameCharacter35_1 {
public:
	// HealthCalcFunc可以是任何"可调用物"(callae entity),可被调用并接受
	// 任何兼容于GameCharacter35_1之物，返回任何兼容于int的东西
	typedef std::function<int (const GameCharacter35_1&)> HealthCalcFunc;
	explicit GameCharacter35_1(HealthCalcFunc hcf = defaultHealthCalc_1) : healthFunc(hcf) {}
	int healthValue() const
	{
		return healthFunc(*this);
	}

private:
	HealthCalcFunc healthFunc;
};

int test_item_35()
{
	EvilBadGuy ebg1(loseHealthQuickly); // 相同类型的人物搭配不同的健康计算方式
	EvilBadGuy ebg2(loseHealthSlowly);

	return 0;
}

////////////////////////////////////
class B {
public:
	void mf() { fprintf(stdout, "B::mf\n"); }
};

class D : public B {
public:
	void mf() { fprintf(stdout, "D::mf\n"); } // 遮掩(hides)了B::mf
};

int test_item_36()
{
	D x;
	B* pB = &x;
	// 由于pB被声明为一个pointer-to-B,通过pB调用的non-virtual函数永远是B所定义的版本，即使pB指向一个类型为"B派生之class"的对象
	pB->mf(); // 调用B::mf

	D* pD = &x;
	pD->mf(); // 调用D::mf

	return 0;
}

////////////////////////////////////
class Shape37 {
public:
	enum ShapeColor { Red, Green, Blud };
	// 所有形状都必须提供一个函数，用来绘出自己
	virtual void draw(ShapeColor color = Red) const = 0;
};

class Rectangle37 : public Shape37 {
public:
	// 注意，赋予不同的缺省参数值。这真糟糕!
	virtual void draw(ShapeColor color = Green) const
	{
		fprintf(stdout, "rectangle shape color: %d\n", color);
	}
};

class Circle37 : public Shape37 {
public:
	virtual void draw(ShapeColor color) const
	// 请注意，以上这么写则当客户以对象调用此函数，一定要指定参数值。因为静态绑定下这个函数并
	// 不从其base继承缺省参数值。但若以指针(或reference)调用此函数，可以不指定参数值，因为动态
	// 绑定下这个函数会从其base继承缺省参数值
	{
		fprintf(stdout, "circle shape color: %d\n", color);
	}
};

int test_item_37()
{
	Shape37* ps; // 静态类型为Shape37*；没有动态类型，因为它尚未指向任何对象
	Shape37* pc = new Circle37; // 静态类型为Shape37*,动态类型为Circle37*
	Shape37* pr = new Rectangle37; // 静态类型为Shape37*,动态类型为Rectangle37*

	pc->draw(Shape37::Red); // 调用Circle37::draw(Shape37::Red)
	pr->draw(Shape37::Red); // 调用Rectangle::draw(Shape37::Red)

	// 即使把指针换成references问题仍然存在
	pr->draw(); // 调用Rectangle37::draw(Shape37::Red)!

	return 0;
}

////////////////////////////////////
class Address {};
class PhoneNumber {};
class Person {
private:
	std::string name;        // 合成成分物(composed object)
	Address address;         // 同上
	PhoneNumber voiceNumber; // 同上
	PhoneNumber faxNumber;   // 同上
};

int test_item_38()
{
	return 0;
}

////////////////////////////////////
class Empty39 {};
class HoldsAnInt {
private:
	int x;
	Empty39 e;
};

class HoldsAnInt39 : private Empty39 { // EBO(empty base optimization)
private:
	int x;
};

int test_item_39()
{
	fprintf(stdout, "sizeof(Empty39): %d\n", sizeof(Empty39)); // 1
	fprintf(stdout, "sizeof(HoldsAnInt): %d\n", sizeof(HoldsAnInt)); // 8 
	fprintf(stdout, "sizeof(HoldsAnInt39): %d\n", sizeof(HoldsAnInt39)); // 4

	return 0;
}

////////////////////////////////////
int test_item_40()
{
	return 0;
}

////////////////////////////////////
// 隐式接口
template<typename T>
void doProcessing(T& w)
{
	T someNastyWidget;
	if (w.size() > 10 && w != someNastyWidget) {
		T temp(w);
		temp.normalize();
		temp.swap(w);
	}
}

// 显示接口
class Widget41 {
public:
	Widget41();
	virtual std::size_t size() const;
	virtual void normalize();
	void swap(Widget41& other);
};

int test_item_41()
{
	return 0;
}

////////////////////////////////////
template<typename C>
void print2nd(const C& container)
{
	if (container.size() >= 2) {
		// 一般性规则很简单：任何时候当你想要在template中指涉一个嵌套从属类型名称，就必须
		// 在紧临它的前一个位置放上关键字typename
		typename C::const_iterator iter(container.begin());
	}
}

template<typename C> //允许使用"typename"(或"class")
void f42(const C& container, // 不允许使用"typename",C并不是嵌套从属类型名称
	typename C::iterator iter); // 一定要使用"typename",C::iterator是个嵌套从属类型名称

template<typename T>
class Base42 {
	class Nested {
		Nested(int x) {}
	};
};

template<typename T>
class Derived42 : public Base42<T>::Nested { // base class list中不允许"typename"
public:
	explicit Derived42(int x) 
	: Base42<T>::Nested(x) // mem.init.list中不允许"typename"
	{
		typename Base42<T>::Nested temp; // 嵌套从属类型名称，既不在base class list中也不在
			// mem.init.list中，作为一个base class修饰符需加上typename
	}
};

template<typename IterT>
void workWithIterator(IterT iter)
{
	// 使用IterT对象所指物的相同类型将temp初始化为iter所指物
	// 如果IterT是vector<int>::iterator,temp的类型就是int
	// value_type被嵌套于iterator_traits<IterT>之内而IterT是个template参数，所以必须在它之前放置typename
	typename std::iterator_traits<IterT>::value_type temp(*iter);
	
	typedef typename std::iterator_traits<IterT>::value_type value_type;
	value_type temp2(*iter);
}

int test_item_42()
{
	return 0;
}

////////////////////////////////////
class CompanyA {
public:
	void sendCleartext(const std::string& msg) {}
	void sendEncrypted(const std::string& msg) {}
};

class CompanyB {
public:
	void sendCleartext(const std::string& msg) {}
	void sendEncrypted(const std::string& msg) {}
};

class CompanyZ {
public:
	void sendEncrypted(const std::string& msg) {}
};

class MsgInfo {};

template<typename Company>
class MsgSender {
public:
	void sendClear(const MsgInfo& info)
	{
		std::string msg;
		Company c;
		c.sendCleartext(msg);
	}

	void sendSecret(const MsgInfo& info)
	{
		std::string msg;
		Company c;
		c.sendEncrypted(msg);
	}
};

// 一个全特化的MsgSender,它和一般template相同，差别只在于它删掉了sendClear
// class定义式最前面的"template<>"语法象征这既不是template也不是标准class,而是个特化版的MsgSender template
template<>
class MsgSender<CompanyZ> {
public:
	void sendSecret(const MsgInfo& info)
	{
		std::string msg;
		CompanyZ c;
		c.sendEncrypted(msg);
	}
};

template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	//using MsgSender<Company>::sendClear;

	void sendClearMsg(const MsgInfo& info)
	{
		//sendClear(info); // 调用base class函数，无法通过编译

		//this->sendClear(info); // 成立，假设sendClear将被继承

		//sendClear(info); // using MsgSender<Company>::sendClear, ok,假设sendClear将被继承下来

		MsgSender<Company>::sendClear(info); // 明白指出被调用的函数位于base class内，ok,假设sendClear将被继承下来
	}
};

int test_item_43()
{
	return 0;
}

////////////////////////////////////
int test_item_44()
{
	return 0;
}

////////////////////////////////////
template<typename T>
class SmartPtr {
public:
	// 泛化copy构造函数并未被声明为explicit,那是蓄意的，因为原始指针类型之间的转换(例如从
	// derived class指针转为base class指针)是隐式转换，无需明白写出转型动作(cast)
	template<typename U>
	SmartPtr(const SmartPtr<U>& other) : heldPtr(other.get()) {}// 以other的heldPtr初始化this的heldPtr

	T* get() const { return heldPtr; }

private:
	T* heldPtr; // 这个SmartPtr持有的内置(原始)指针
};

int test_item_45()
{
	return 0;
}

////////////////////////////////////
template<typename T> class Rational46;
template<typename T>
const Rational46<T> doMutiply(const Rational46<T>& lhs, const Rational46<T>& rhs);

template<typename T>
class Rational46 {
public:
	Rational46(const T& numerator = 0, const T& denominator = 1) {}
	const T numerator() const { return (T)0; }
	const T denominator() const { return (T)0; }

	friend const Rational46 operator* (const Rational46& lhs, const Rational46& rhs)
	{
		//return Rational46(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
		
		// 令friend函数调用辅助函数
		return doMultiply(lhs, rhs);
	}
};

template<typename T>
const Rational46<T> doMultiply(const Rational46<T>& lhs, const Rational46<T>& rhs)
{
	return Rational46<T>(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

int test_item_46()
{
	Rational46<int> oneHalf(1, 2);
	Rational46<int> result = oneHalf * 2;

	return 0;
}

////////////////////////////////////
// 类型IterT的iterator_category
template<typename IterT>
struct iterator_traits {
	typedef typename IterT::iterator_category iterator_category;
};

// template偏特化，针对内置指针
template<typename IterT>
struct iterator_traits<IterT*> {
	typedef std::random_access_iterator_tag iterator_category;
};

// 实现用于random access迭代器
template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::random_access_iterator_tag)
{
	iter += d;
}

// 实现用于bidirectional迭代器
template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::bidirectional_iterator_tag)
{
	if (d >= 0) { while (d--) ++iter; }
	else { while (d++) --iter; }
}

// 实现用于input迭代器
template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::input_iterator_tag)
{
	if (d < 0) {
		throw std::out_of_range("Negative distance");
	}
	
	while (d--) ++iter;
}

template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d)
{
	doAdvance(iter, d, typename std::iterator_traits<IterT>::iterator_category());
}

int test_item_47()
{
	return 0;
}

////////////////////////////////////
// TMP的阶乘运算, 一般情况:Factorial<n>的值是n乘以Factorial<n-1>的值
template<unsigned n>
struct Factorial {
	enum { value = n * Factorial<n-1>::value };
};

// 特殊情况:Factorial<0>的值是1
template<>
struct Factorial<0> {
	enum { value = 1 };
};

int test_item_48()
{
	fprintf(stdout, "Factorial<5>::value: %d\n", Factorial<5>::value);
	fprintf(stdout, "Factorial<10>::value: %d\n", Factorial<10>::value);

	return 0;
}

////////////////////////////////////
// 当operator new无法分配足够内存时，该被调用的函数
void outOfMem()
{
	std::cerr<<"Unable to satisfy request for memory\n";
	std::abort();
}

class NewHandlerHolder {
public:
	explicit NewHandlerHolder(std::new_handler nh) : handler(nh) {} // 取得目前的new-handler
	~NewHandlerHolder() // 释放它
	{ std::set_new_handler(handler); }

private:
	std::new_handler handler; // 记录下来
	NewHandlerHolder(const NewHandlerHolder&); // 阻止copying
	NewHandlerHolder& operator= (const NewHandlerHolder&);
};

// "mixin"风格的base class,用以支持class专属的set_new_handler
template<typename T>
class NewHandlerSupport {
public:
	static std::new_handler set_new_handler(std::new_handler p) throw();
	static void* operator new(std::size_t size) throw(std::bad_alloc);

private:
	static std::new_handler currentHandler;
};

template<typename T>
std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler p) throw()
{
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

template<typename T>
void* NewHandlerSupport<T>::operator new(std::size_t size) throw(std::bad_alloc)
{
	NewHandlerHolder h(std::set_new_handler(currentHandler));
	return ::operator new(size);
}

template<typename T>
std::new_handler NewHandlerSupport<T>::currentHandler = NULL;

class Widget49 : public NewHandlerSupport<Widget> {};

int test_item_49()
{
	std::set_new_handler(outOfMem);
	int* pBigDataArray = new int[100000000L];

	Widget49::set_new_handler(outOfMem); // 设定outOfMem为Widget49的new-handling函数
	Widget49* pw1 = new Widget49; // 如果内存分配失败，调用outOfMem

	std::string* ps = new std::string; // 如果内存分配失败，调用global new-handling函数

	Widget49::set_new_handler(NULL); // 设定Widget49专属的new-handling函数为NULL
	Widget49* pw2 = new Widget49; // 如果内存分配失败，立刻抛出异常(clalss Widget49并没有专属的new-handling函数)

	return 0;
}

////////////////////////////////////
int test_item_50()
{
	return 0;
}

////////////////////////////////////
int test_item_51()
{
	return 0;
}

////////////////////////////////////
int test_item_52()
{
	return 0;
}

////////////////////////////////////
int test_item_53()
{
	return 0;
}

////////////////////////////////////
int test_item_54()
{
	return 0;
}

////////////////////////////////////
int test_item_55()
{
	return 0;
}


} // namespace effective_cplusplus_

// std::swap针对Widget25特化版本
namespace std {
template<>
void swap<effective_cplusplus_::Widget25>(effective_cplusplus_::Widget25& a, effective_cplusplus_::Widget25& b)
{
	a.swap(b); // 若要置换Widget25,调用其swap成员函数
}

}
