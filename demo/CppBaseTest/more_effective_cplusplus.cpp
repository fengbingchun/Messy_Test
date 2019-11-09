#include "more_effective_cplusplus.hpp"
#include <string>
#include <new>
#include <iostream>
#include <vector>
#include <iomanip>
#include <list>
#include <algorithm>
#include <string.h>
#include <memory>

// Blog: https://blog.csdn.net/fengbingchun/article/details/102990753

// reference: 《More Effective C++》

namespace more_effective_cplusplus_ {

////////////////////////////////////
void printDouble(const double& rd)
{
	std::cout<<rd; // 不需要测试rd,它肯定指向一个double值
}

void printDouble(const double* pd)
{
	if (pd) { // 检查是否为NULL
		std::cout<<*pd;
	}
}

int test_item_1()
{
	char* pc = 0; // 设置指针为空值
	char& rc = *pc; // 让指针指向空值，这是非常有害的，结果将是不确定的

	//std::string& rs; // 错误，引用必须被初始化
	std::string s("xyzzy");
	std::string& rs = s; // 正确,rs指向s
	std::string* ps; // 未初始化的指针，合法但危险

{
	std::string s1("Nancy");
	std::string s2("Clancy");
	std::string& rs = s1; // rs引用s1
	std::string* ps = &s1; // ps指向s1
	rs = s2; // rs仍旧引用s1,但是s1的值现在是"Clancy"
	ps = &s2; // ps现在指向s2,s1没有改变
}

	std::vector<int> v(10);
	v[5] = 10; // 这个被赋值的目标对象就是操作符[]返回的值，如果操作符[]
		   // 返回一个指针，那么后一个语句就得这样写: *v[5] = 10;

	return 0;
}

////////////////////////////////////
class Widget {
public:
	virtual void func() {}
};

class SpecialWidget : public Widget {
public:
	virtual void func() {}
};

void update(SpecialWidget* psw) {}
void updateViaRef(SpecialWidget& rsw) {}

typedef void (*FuncPtr)(); // FuncPtr是一个指向函数的指针
int doSomething() { return 1; };

int test_item_2()
{
	int firstNumber = 1, secondNumber = 1;
	double result1 = ((double)firstNumber) / secondNumber; // C风格
	double result2 = static_cast<double>(firstNumber) / secondNumber; // C++风格类型转换

	SpecialWidget sw; // sw是一个非const对象
	const SpecialWidget& csw = sw; // csw是sw的一个引用，它是一个const对象
	//update(&csw); // 错误，不能传递一个const SpecialWidget*变量给一个处理SpecialWidget*类型变量的函数
	update(const_cast<SpecialWidget*>(&csw)); // 正确，csw的const显示地转换掉(csw和sw两个变量值在update函数中能被更新)
	update((SpecialWidget*)&csw); // 同上，但用了一个更难识别的C风格的类型转换

	Widget* pw = new SpecialWidget;
	//update(pw); // 错误，pw的类型是Widget*，但是update函数处理的是SpecialWidget*类型
	//update(const_cast<SpecialWidget*>(pw)); // 错误，const_cast仅能被用在影响constness or volatileness的地方，不能用在向继承子类进行类型转换

	Widget* pw2 = nullptr;;
	update(dynamic_cast<SpecialWidget*>(pw2)); // 正确，传递给update函数一个指针是指向变量类型为SpecialWidget的pw2的指针， 如果pw2确实指向一个对象，否则传递过去的将是空指针

	Widget* pw3 = new SpecialWidget;
	updateViaRef(dynamic_cast<SpecialWidget&>(*pw3)); // 正确，传递给updateViaRef函数SpecailWidget pw3指针，如果pw3确实指向了某个对象，否则将抛出异常

	//double result3 = dynamic_cast<double>(firstNumber) / secondNumber; // 错误，没有继承关系
	const SpecialWidget sw4;
	//update(dynamic_cast<SpecialWidget*>(&sw4)); // 错误，dynamic_cast不能转换掉const

	FuncPtr funcPtrArray[10]; // funcPtrArray是一个能容纳10个FuncPtr指针的数组
	//funcPtrArray[0] = &doSomething; // 错误，类型不匹配
	funcPtrArray[0] = reinterpret_cast<FuncPtr>(&doSomething); // 转换函数指针的代码是不可移植的(C++不保证所有的函数指针都被用一样的方法表示)，在一些情况下这样的转换会产生不正确的结果，所以应该避免转换函数指针类型

	return 0;
}

////////////////////////////////////
class BST {
public:
	virtual ~BST() { fprintf(stdout, "BST::~BST\n"); }
private:
	int score;
};

class BalancedBST : public BST {
public:
	virtual ~BalancedBST() { fprintf(stdout, "BalancedBST::~BalancedBST\n"); }
private:
	int length;
	int size; // 如果增加此一个int成员，执行test_item_3会segmentation fault，注释掉此变量，运行正常
};

int test_item_3()
{
	fprintf(stdout, "BST size: %d\n", sizeof(BST)); // 16
	fprintf(stdout, "BalancedBST size: %d\n", sizeof(BalancedBST)); // 24

	BST* p = new BalancedBST[10];
	delete [] p; // 如果sizeof(BST) != sizeof(BalancedBST)，则会segmentation fault

	return 0;
}

////////////////////////////////////
class EquipmentPiece {
public:
	EquipmentPiece(int IDNumber) {}
};

int test_item_4()
{
	//EquipmentPiece bestPieces[10]; // 错误，没有正确调用EquipmentPiece构造函数
	//EquipmentPiece* bestPieces2 = new EquipmentPiece[10]; // 错误，与上面的问题一样

	int ID1 = 1, ID2 = 2;
	EquipmentPiece bestPieces3[] = { EquipmentPiece(ID1), EquipmentPiece(ID2) }; // 正确，提供了构造函数的参数

	// 利用指针数组来代替一个对象数组
	typedef EquipmentPiece* PEP; // PEP指针指向一个EquipmentPiece对象
	PEP bestPieces4[10]; // 正确，没有调用构造函数
	PEP* bestPieces5 = new PEP[10]; // 也正确
	// 在指针数组里的每一个指针被重新赋值，以指向一个不同的EquipmentPiece对象
	for (int i = 0; i < 10; ++i)
		bestPieces5[i] = new EquipmentPiece(ID1);

	// 为数组分配raw memory,可以避免浪费内存，使用placement new方法在内存中构造EquipmentPiece对象
	void* rawMemory = operator new[](10*sizeof(EquipmentPiece));
	// make bestPieces6 point to it so it can be treated as an EquipmentPiece array
	EquipmentPiece* bestPieces6 = static_cast<EquipmentPiece*>(rawMemory);
	// construct the EquipmentPiece objects in the memory使用"placement new"
	for (int i = 0; i < 10; ++i)
		new(&bestPieces6[i]) EquipmentPiece(ID1);
	// ...
	// 以与构造bestPieces6对象相反的顺序解构它
	for (int i = 9; i >= 0; --i)
		bestPieces6[i].~EquipmentPiece(); // 如果使用普通的数组删除方法，程序的运行将是不可预测的
	// deallocate the raw memory
	delete [] rawMemory;

	return 0;
}

////////////////////////////////////i
class Name {
public:
	Name(const std::string& s); // 转换string到Name
};

class Rational {
public:
	Rational(int numerator = 0, int denominator = 1) // 转换int到有理数类
	{
		n = numerator;
		d = denominator;
	}

	operator double() const // 转换Rational类成double类型
	{
		return static_cast<double>(n) / d;
	}

	double asDouble() const
	{
		return static_cast<double>(n) / d;
	}

private:
	int n, d;
};

template<class T>
class Array {
public:
	Array(int lowBound, int highBound) {}
	explicit Array(int size) {}
	T& operator[](int index) { return data[index]; }

private:
	T* data;
};

bool operator== (const Array<int>& lhs, const Array<int>& rhs)
{ return false; }

int test_item_5()
{
	Rational r(1, 2); // r的值是1/2
	double d = 0.5 * r; // 转换r到double,然后做乘法
	fprintf(stdout, "value: %f\n", d);

	std::cout<<r<<std::endl; // 应该打印出"1/2",但事与愿违,是一个浮点数，而不是一个有理数,隐式类型转换的缺点
				 // 解决方法是不使用语法关键字的等同的函数来替代转换运算符,如增加asDouble函数，去掉operator double

	Array<int> a(10);
	Array<int> b(10);
	for (int i = 0; i < 10; ++i) {
		//if (a == b[i]) {} // 如果构造函数Array(int size)没有explicit关键字，编译器将能通过调用Array<int>构造函数能转换int类型到Array<int>类型，这个构造函数只有一个int类型的参数,加上explicit关键字则可避免隐式转换

		if (a == Array<int>(b[i])) {} // 正确，显示从int到Array<int>转换(但是代码的逻辑不合理)
		if (a == static_cast<Array<int>>(b[i]))	 {} // 同样正确，同样不合理
		if (a == (Array<int>)b[i]) {} // C风格的转换也正确，但是逻辑依旧不合理
	}
	return 0;
}

////////////////////////////////////
class UPInt { // unlimited precision int
public:
	// 注意：前缀与后缀形式返回值类型是不同的，前缀形式返回一个引用，后缀形式返回一个const类型
	UPInt& operator++() // ++前缀
	{
		//*this += 1; // 增加
		i += 1;
		return *this; // 取回值
	}

	const UPInt operator++(int) // ++后缀
	{
		// 注意：建立了一个显示的临时对象，这个临时对象必须被构造并在最后被析构，前缀没有这样的临时对象
		UPInt oldValue = *this; // 取回值
		// 后缀应该根据它们的前缀形式来实现
		++(*this); // 增加
		return oldValue; // 返回被取回的值
	}

	UPInt& operator--() // --前缀
	{
		i -= 1;
		return *this;
	}

	const UPInt operator--(int) // --后缀
	{
		UPInt oldValue = *this;
		--(*this);
		return oldValue;
	}

	UPInt& operator+=(int a) // +=操作符，UPInt与int相运算
	{
		i += a;
		return *this;
	}

	UPInt& operator-=(int a)
	{
		i -= a;
		return *this;
	}

private:
	int i;
}; 

int test_item_6()
{
	UPInt i;
	++i; // 调用i.operator++();
	i++; // 调用i.operator++(0);
	--i; // 调用i.operator--();
	i--; // 调用i.operator--(0);

	//i++++; // 注意：++后缀返回的是const UPInt

	return 0;
}

////////////////////////////////////
int test_item_7()
{
	// if (expression1 && expression2)
	// 如果重载了操作符&&，对于编译器来说，等同于下面代码之一
	// if (expression1.operator&&(expression2)) // when operator&& is a member function
	// if (operator&&(expression1, expression2)) // when operator&& is a global function

	return 0;
}

////////////////////////////////////
class Widget8 {
public:
	Widget8(int widget8Size) {}
};

void* mallocShared(size_t size)
{
	return operator new(size);
}

void freeShared(void* memory)
{
	operator delete(memory);
}

Widget8* constructWidget8InBuffer(void* buffer, int widget8Size)
{
	return new(buffer) Widget8(widget8Size); // new操作符的一个用法，需要使用一个额外的变量(buffer)，当new操作符隐含调用operator new函数时，把这个变量传递给它
	// 被调用的operator new函数除了待有强制的参数size_t外，还必须接受void*指针参数，指向构造对象占用的内存空间。这个operator new就是placement new,它看上去像这样:
	// void * operator new(size_t, void* location) { return location; }
}

int test_item_8()
{
	std::string* ps = new std::string("Memory Management"); // 使用的new是new操作符(new operator)
	//void * operator new(size_t size); // 函数operator new通常声明
	void* rawMemory = operator new(sizeof(std::string)); // 操作符operator new将返回一个指针，指向一块足够容纳一个string类型对象的内存
	operator delete(rawMemory);

	delete ps; // ps->~std::string(); operator delete(ps);

	void* buffer = operator new(50*sizeof(char)); // 分配足够的内存以容纳50个char，没有调用构造函数
	operator delete(buffer); // 释放内存，没有调用析构函数. 这与在C中调用malloc和free等同OA

	void* sharedMemory = mallocShared(sizeof(Widget8));
	Widget8* pw = constructWidget8InBuffer(sharedMemory, 10); // placement new
	//delete pw; // 结果不确定，共享内存来自mallocShared,而不是operator new
	pw->~Widget8(); // 正确，析构pw指向的Widget8,但是没有释放包含Widget8的内存
	freeShared(pw); // 正确，释放pw指向的共享内存，但是没有调用析构函数

	return 0;
}

////////////////////////////////////
int test_item_9()
{
	return 0;
}

////////////////////////////////////
int test_item_10()
{
	return 0;
}

////////////////////////////////////
int test_item_11()
{
	return 0;
}

////////////////////////////////////
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
	return 0;
}

////////////////////////////////////
int test_item_17()
{
	return 0;
}

////////////////////////////////////
int test_item_18()
{
	return 0;
}

////////////////////////////////////
size_t countChar(const std::string& str, char ch)
{
	// 建立一个string类型的临时对象，通过以buffer做为参数调用string的构造函数来初始化这个临时对象,
	// countChar的参数str被绑定在这个临时的string对象上，当countChar返回时，临时对象自动释放

	// 将countChar(const std::string& str, char ch)修改为countChar(std::string& str, char ch)则会error
	return 1;
}

#define MAX_STRING_LEN 64

int test_item_19()
{
	char buffer[MAX_STRING_LEN];
	char c;

	std::cin >> c >> std::setw(MAX_STRING_LEN) >> buffer;
	std::cout<<"There are "<<countChar(buffer, c)<<" occurrences of the character "<<c<<" in "<<buffer<<std::endl;

	return 0;
}

////////////////////////////////////
class Rational20 {
public:
	Rational20(int numerator = 0, int denominator = 1) {}

	int numerator() const { return 1; }
	int denominator() const { return 2; }
};

const Rational20 operator*(const Rational20& lhs, const Rational20& rhs)
{
	// 以某种方法返回对象，能让编译器消除临时对象的开销：这种技巧是返回constructor argument而不是直接返回对象
	return Rational20(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

int test_item_20()
{
	Rational20 a = 10;
	Rational20 b(1, 2);
	Rational20 c = a * b; 

	return 0;
}

////////////////////////////////////
class UPInt21 { // unlimited precision integers class
public:
	UPInt21() {}
	UPInt21(int value) {}
};

const UPInt21 operator+(const UPInt21& lhs, const UPInt21& rhs) // add UPInt21+UPInt21
{
	return UPInt21(1);
}

const UPInt21 operator+(const UPInt21& lhs, int rhs) // add UPInt21+int
{
	return UPInt21(1);
}

const UPInt21 operator+(int lhs, const UPInt21& rhs) // add int+UPInt21
{
	return UPInt21(1);
}

int test_item_21()
{
	UPInt21 upi1, upi2;
	UPInt21 upi3 = upi1 + upi2; // 正确，没有由upi1或upi2生成临时对象
	upi3 = upi1 + 10; // 正确,没有由upi1或10生成临时对象
	upi3 = 10 + upi2; // 正确，没有由10或upi2生成临时对象

	// 注意：注释掉上面的operator+(UPInt21&, int)和operator+(int, UPInt21&)也正确，但是会通过临时对象把10转换为UPInt21

	return 0;
}

////////////////////////////////////
class Rational22 {
public:
	Rational22(int numerator = 0, int denominator = 1) {}
	Rational22& operator+=(const Rational22& rhs) { return *this; }
	Rational22& operator-=(const Rational22& rhs) { return *this; }
};

// operator+根据operator+=实现
const Rational22 operator+(const Rational22& lhs, const Rational22& rhs)
{
	return Rational22(lhs) += rhs;
}

// operator-根据operator-=实现
const Rational22 operator-(const Rational22& lhs, const Rational22& rhs)
{
	return Rational22(lhs) -= rhs;
}

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
int test_item_24()
{
	return 0;
}

////////////////////////////////////
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
// 判断一个对象是否在堆中, HeapTracked不能用于内建类型，因为内建类型没有this指针
typedef const void* RawAddress;
class HeapTracked { // 混合类，跟踪
public:
	class MissingAddress {}; // 从operator new返回的ptr异常类
	virtual ~HeapTracked() = 0;
	static void* operator new(size_t size);
	static void operator delete(void* ptr);
	bool isOnHeap() const;

private:
	static std::list<RawAddress> addresses;
};

std::list<RawAddress> HeapTracked::addresses;

HeapTracked::~HeapTracked() {}

void* HeapTracked::operator new(size_t size)
{
	void* memPtr = ::operator new(size);
	addresses.push_front(memPtr);
	return memPtr;
}

void HeapTracked::operator delete(void* ptr)
{
	std::list<RawAddress>::iterator it = std::find(addresses.begin(), addresses.end(), ptr);
	if (it != addresses.end()) {
		addresses.erase(it);
		::operator delete(ptr);
	} else {
		throw MissingAddress(); // ptr就不是用operator new分配的，所以抛出一个异常
	}
}

bool HeapTracked::isOnHeap() const
{
	// 生成的指针将指向"原指针指向对象内存"的开始处
	// 如果HeapTracked::operator new为当前对象分配内存，这个指针就是HeapTracked::operator new返回的指针
	const void* rawAddress = dynamic_cast<const void*>(this);
	std::list<RawAddress>::iterator it = std::find(addresses.begin(), addresses.end(), rawAddress);
	return it != addresses.end();
}

class Asset : public HeapTracked {};

// 禁止堆对象
class UPNumber27 {
private:
	static void* operator new(size_t size);
	static void operator delete(void* ptr);
};

void* UPNumber27::operator new(size_t size)
{
	return ::operator new(size);
}

void UPNumber27::operator delete(void* ptr)
{
	::operator delete(ptr);
}

class Asset27 {
public:
	Asset27(int initValue) {}

private:
	UPNumber27 value;
};

int test_item_27()
{
	UPNumber27 n1; // okay
	static UPNumber27 n2; // also okay
	//UPNumber27* p = new UPNumber27; // error, attempt to call private operator new

	// UPNumber27的operator new是private这一点 不会对包含UPNumber27成员对象的对象的分配产生任何影响
	Asset27* pa = new Asset27(100); // 正确，调用Asset::operator new或::operator new,不是UPNumber27::operator new

	return 0;
}

////////////////////////////////////
// 大多数灵巧指针模板
template<class T>
class SmartPtr {
public:
	SmartPtr(T* realPtr = 0); // 建立一个灵巧指针指向dumb pointer(内建指针)所指的对象，未初始化的指针，缺省值为0(null)
	SmartPtr(const SmartPtr& rhs); // 拷贝一个灵巧指针
	~SmartPtr(); // 释放灵巧指针
	// make an assignment to a smart ptr
	SmartPtr& operator=(const SmartPtr& rhs);
	T* operator->() const; // dereference一个灵巧指针以访问所指对象的成员
	T& operator*() const; // dereference灵巧指针

private:
	T* pointee; // 灵巧指针所指的对象
};

int test_item_28()
{
	return 0;
}

////////////////////////////////////
class String {
public:
	String(const char* initValue = "");
	String(const String& rhs);
	String& operator=(const String& rhs);
	const char& operator[](int index) const; // for const String
	char& operator[](int index); // for non-const String
	~String();

private:
	// StringValue的主要目的是提供一个空间将一个特别的值和共享此值的对象的数目联系起来
	struct StringValue { // holds a reference count and a string value
		int refCount;
		char* data;
		bool shareable; // 标志，以指出它是否为可共享的
		StringValue(const char* initValue);
		~StringValue();
	};

	StringValue* value; // value of this String
};

String::String(const char* initValue) : value(new StringValue(initValue))
{}

String::String(const String& rhs)
{
	if (rhs.value->shareable) {
		value = rhs.value;
		++value->refCount;
	} else {
		value = new StringValue(rhs.value->data);
	}
}

String& String::operator=(const String& rhs)
{
	if (value == rhs.value) { // do nothing if the values are already the same
		return *this;
	}

	if (value->shareable && --value->refCount == 0) { // destroy *this's value if no one else is using it
		delete value;
	}

	if (rhs.value->shareable) {
		value = rhs.value; // have *this share rhs's value
		++value->refCount;
	} else {
		value = new StringValue(rhs.value->data);
	}

	return *this;
}

const char& String::operator[](int index) const
{
	return value->data[index];
}

char& String::operator[](int index)
{
	// if we're sharing a value with other String objects, break off a separate copy of the value fro ourselves
	if (value->refCount > 1) {
		--value->refCount; // decrement current value's refCount, becuase we won't be using that value any more
		value = new StringValue(value->data); // make a copy of the value for ourselves
	}

	value->shareable = false;
	// return a reference to a character inside our unshared StringValue object
	return value->data[index];
}

String::~String()
{
	if (--value->refCount == 0) {
		delete value;
	}
}

String::StringValue::StringValue(const char* initValue) : refCount(1), shareable(true)
{
	data = new char[strlen(initValue) + 1];
	strcpy(data, initValue);
}

String::StringValue::~StringValue()
{
	delete[] data;
}

// 基类，任何需要引用计数的类都必须从它继承
class RCObject {
public:
	void addReference() { ++refCount; }
	void removeReference() { if (--refCount == 0) delete this; } // 必须确保RCObject只能被构建在堆中
	void markUnshareable() { shareable = false; }
	bool isShareable() const { return shareable; }
	bool isShared() const { return refCount > 1; }

protected:
	RCObject() : refCount(0), shareable(true) {}
	RCObject(const RCObject& rhs) : refCount(0), shareable(true) {}
	RCObject& operator=(const RCObject& rhs) { return *this; }
	virtual ~RCObject() = 0;

private:
	int refCount;
	bool shareable;

};

RCObject::~RCObject() {} // virtual dtors must always be implemented, even if they are pure virtual and do nothing

// template class for smart pointers-to-T objects. T must support the RCObject interface, typically by inheriting from RCObject
template<class T>
class RCPtr {
public:
	RCPtr(T* realPtr = 0) : pointee(realPtr) { init(); }
	RCPtr(const RCPtr& rhs) : pointee(rhs.pointee) { init(); }
	~RCPtr() { if (pointee) pointee->removeReference(); }

	RCPtr& operator=(const RCPtr& rhs)
	{
		if (pointee != rhs.pointee) { // skip assignments where the value doesn't change
			if (pointee)
				pointee->removeReference(); // remove reference to current value

			pointee = rhs.pointee; // point to new value
			init(); // if possible, share it else make own copy
		}

		return *this;
	}

	T* operator->() const { return pointee; }
	T& operator*() const { return *pointee; }

private:
	T* pointee; // dumb pointer this object is emulating

	void init() // common initialization
	{
		if (pointee == 0) // if the dumb pointer is null, so is the smart one
			return;

		if (pointee->isShareable() == false) // if the value isn't shareable copy it
			pointee = new T(*pointee);

		pointee->addReference(); // note that there is now a new reference to the value
	}
};

// 将StringValue修改为是从RCObject继承
// 将引用计数功能移入一个新类(RCObject)，增加了灵巧指针(RCPtr)来自动处理引用计数
class String2 {
public:
	String2(const char* value = "") : value(new StringValue(value)) {}
	const char& operator[](int index) const { return value->data[index]; } // for const String2
	
	char& operator[](int index) // for non-const String2
	{
		if (value->isShared())
			value = new StringValue(value->data);
		value->markUnshareable();
		return value->data[index];
	}

private:
	// StringValue的主要目的是提供一个空间将一个特别的值和共享此值的对象的数目联系起来
	struct StringValue : public RCObject { // holds a reference count and a string value
		char* data;

		StringValue(const char* initValue) { init(initValue); }
		StringValue(const StringValue& rhs) { init(rhs.data); }

		void init(const char* initValue)
		{
			data = new char[strlen(initValue) + 1];
			strcpy(data, initValue);
		}

		~StringValue() { delete [] data; }
	};

	RCPtr<StringValue> value; // value of this String2

};

int test_item_29()
{
	String s1("More Effective C++");
	String s2 = s1;
	s1 = s2;
	fprintf(stdout, "char: %c\n", s1[2]);
	String s3 = s1;
	s3[5] = 'x';

	return 0;
}

////////////////////////////////////
template<class T>
class Array2D { // 使用代理实现二维数组
public:
	Array2D(int i, int j) : i(i), j(j)
	{
		data.reset(new T[i*j]);
	}

	class Array1D { // Array1D是一个代理类，它的实例扮演的是一个在概念上不存在的一维数组
	public:
		Array1D(T* data) : data(data) {}
		T& operator[](int index) { return data[index]; }
		const T& operator[](int index) const { return data[index]; }

	private:
		T* data;
	};

	Array1D operator[](int index) { return Array1D(data.get()+j*index); }
	const Array1D operator[](int index) const { return Array1D(data.get()+j*index); }

private:
	std::unique_ptr<T[]> data;
	int i, j;
};

// 可以通过代理类帮助区分通过operator[]进行的是读操作还是写操作
class String30 {
public:
	String30(const char* value = "") : value(new StringValue(value)) {}
	
	class CharProxy { // proxies for string chars
	public:
		CharProxy(String30& str, int index) : theString(str), charIndex(index) {}

		CharProxy& operator=(const CharProxy& rhs)
		{
			// if the string is haring a value with other String objects,
			// break off a separate copy of the value for this string only
			if (theString.value->isShared())
				theString.value = new StringValue(theString.value->data);

			// now make the assignment: assign the value of the char
			// represented by rhs to the char represented by *this
			theString.value->data[charIndex] = rhs.theString.value->data[rhs.charIndex];
			return *this;
		}
		
		CharProxy& operator=(char c)
		{
			if (theString.value->isShared())
				theString.value = new StringValue(theString.value->data);
			theString.value->data[charIndex] = c;
			return *this;
		}

		operator char() const { return theString.value->data[charIndex]; }

	private:
		String30& theString;
		int charIndex;
	};

	const CharProxy operator[](int index) const // for const String30
	{
		return CharProxy(const_cast<String30&>(*this), index);
	}

	CharProxy operator[](int index) // for non-const String30
	{
		return CharProxy(*this, index);
	}

	//friend class CharProxy;
private:
	// StringValue的主要目的是提供一个空间将一个特别的值和共享此值的对象的数目联系起来
	struct StringValue : public RCObject { // holds a reference count and a string value
		char* data;

		StringValue(const char* initValue) { init(initValue); }
		StringValue(const StringValue& rhs) { init(rhs.data); }

		void init(const char* initValue)
		{
			data = new char[strlen(initValue) + 1];
			strcpy(data, initValue);
		}

		~StringValue() { delete [] data; }
	};

	RCPtr<StringValue> value; // value of this String30

};

int test_item_30()
{
	Array2D<float> data(10, 20);
	fprintf(stdout, "%f\n", data[3][6]);

	String30 s1("Effective C++"), s2("More Effective C++"); // reference-counted strings using proxies
	fprintf(stdout, "%c\n", s1[5]); // still legal, still works
	s2[5] = 'x'; // also legal, also works
	s1[3] = s2[8]; // of course it's legal, of course it works

	//char* p = &s1[1]; // error, 通常,取proxy对象地址的操作与取实际对象地址的操作得到的指针，其类型是不同的,重载CharProxy类的取地址运算可消除这个不同

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
int test_item_33()
{
	return 0;
}

////////////////////////////////////
int test_item_34()
{
	return 0;
}

////////////////////////////////////
int test_item_35()
{
	return 0;
}


} // namespace more_effective_cplusplus_

