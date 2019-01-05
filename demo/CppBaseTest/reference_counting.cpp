#include "reference_counting.hpp"
#include <iostream>
#include <chrono>
#include <string>
#include <string.h>

// Blog: https://blog.csdn.net/fengbingchun/article/details/85861776

namespace reference_counting_ {

// reference: 《提高C++性能的编程技术》：第十二章：引用计数
namespace {

// 为使引用计数更加方便，我们需要为每个BigInt对象关联一个引用计数。
// 实现这一操作的方式有两种，为BigInt直接添加refCount成员或使其继承自基类RCObject
// RCObject是引用计数对象的基类，并且封装了所有引用计数变量以及针对这些变量的操作
class RCObject {
public:
	void addReference() { ++refCount; }
	void removeReference() { if (--refCount == 0) delete this; }

	void markUnshareable() { shareable = false; }
	bool isShareable() const { return shareable; }
	bool isShared() const { return refCount > 1; }

protected:
	RCObject() : refCount(0), shareable(true) {}
	RCObject(const RCObject& rhs) : refCount(0), shareable(true) {}
	RCObject& operator=(const RCObject& rhs) { return *this; }
	virtual ~RCObject() {}

private:
	int refCount;
	bool shareable;
};

// BigInt类的功能是将正整数表示成用二进制编码的十进制形式
class BigInt : public RCObject {
friend BigInt operator+ (const BigInt&, const BigInt&);

public:
	BigInt(const char*);
	BigInt(unsigned = 0);
	BigInt(const BigInt&);
	BigInt& operator= (const BigInt&);
	BigInt& operator+= (const BigInt&);
	~BigInt();

	char* getDigits() const { return digits; }
	unsigned getNdigits() const { return ndigits; }
	void print() { fprintf(stdout, "digits: %s\n", digits); }

private:
	char* digits;
	unsigned ndigits;
	unsigned size; // 分配的字符串的大小
	BigInt(const BigInt&, const BigInt&);
	char fetch(unsigned i) const;
};

BigInt::BigInt(unsigned u)
{
	unsigned v = u;
	for (ndigits = 1; (v/=10) > 0; ++ndigits) {
		;
	}

	digits = new char[size=ndigits];
	for (unsigned i = 0; i < ndigits; ++i) {
		digits[i] = u%10;
		u /= 10;
	}
}

BigInt::~BigInt()
{
	delete [] digits;
}

BigInt& BigInt::operator=(const BigInt& rhs)
{
	if (this == &rhs) return *this;

	ndigits = rhs.ndigits;
	if (ndigits > size) {
		delete [] digits;
		digits = new char[size = ndigits];
	}

	for (unsigned i = 0; i < ndigits; ++i) {
		digits[i] = rhs.digits[i];
	}

	return *this;
}

BigInt::BigInt(const char* s)
{
	if (s[0] == '\0') {
		s = "0";
	}

	size = ndigits = strlen(s);
	digits = new char[size];
	for (unsigned i = 0; i < ndigits; ++i) {
		digits[i] = s[ndigits-1-i] - '0';
	}
}

BigInt::BigInt(const BigInt& copyFrom)
{
	size = ndigits = copyFrom.ndigits;
	digits = new char[size];

	for (unsigned i = 0; i < ndigits; ++i) {
		digits[i] = copyFrom.digits[i];
	}
}

// BigInt = left + right
BigInt::BigInt(const BigInt& left, const BigInt& right)
{
	size = 1 + (left.ndigits > right.ndigits ? left.ndigits : right.ndigits);
	digits = new char[size];
	ndigits = left.ndigits;
	for (unsigned i = 0; i < ndigits; ++i) {
		digits[i] = left.digits[i];
	}

	*this += right;
}

inline char BigInt::fetch(unsigned i) const
{
	return i < ndigits ? digits[i] : 0;
}

BigInt& BigInt::operator+=(const BigInt& rhs)
{
	unsigned max = 1 + (rhs.ndigits > ndigits ? rhs.ndigits : ndigits);
	if (size < max) {
		char* d = new char[size=max];
		for (unsigned i = 0; i < ndigits; ++i) {
			d[i] = digits[i];
		}

		delete [] digits;
		digits = d;
	}
	
	while (ndigits < max) {
		digits[ndigits++] = 0;
	}

	for (unsigned i = 0; i < ndigits; ++i) {
		digits[i] += rhs.fetch(i);
		if (digits[i] >= 10) {
			digits[i] -= 10;
			digits[i+1] = 1;
		}
	}

	if (digits[ndigits-1] == 0) {
		--ndigits;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, BigInt& bi)
{
	char c;
	const char* d = bi.getDigits();

	for (int i = bi.getNdigits() - 1; i >= 0; i--) {
		c = d[i] + '0';
		os << c;
	}

	os << std::endl;
	return os;
}

inline BigInt operator+(const BigInt& left, const BigInt& right)
{
	return BigInt(left, right);
}

// 智能指针：这种特殊指针的任务是对引用计数进行登记
template<class T>
class RCPtr {
public:
	RCPtr(T* realPtr = 0) : pointee(realPtr) { init(); }
	RCPtr(const RCPtr& rhs) : pointee(rhs.pointee) { init(); }
	~RCPtr() { if (pointee) pointee->removeReference(); }

	RCPtr& operator=(const RCPtr& rhs);
	T* operator->() const { return pointee; }
	T& operator*() const { return *pointee; }

private:
	T* pointee;
	void init();
};

template<class T>
void RCPtr<T>::init()
{
	if (0 == pointee) return;
	if (false == pointee->isShareable()) {
		pointee = new T(*pointee);
	}

	pointee->addReference();
}

template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr& rhs)
{
	if (pointee != rhs.pointee) {
		if (pointee) pointee->removeReference();
		pointee = rhs.pointee;
		init();
	}

	return *this;
}

// RCBigInt:构造BigInt的引用计数实现，RCBigInt需要指向一个真正的BigInt对象
// 如果是频繁赋值和复制RCBigInt对象的工作，RCBigInt会大显身手。另外，与直接使用简单BigInt相比，
// 由于创建了对新BigInt对象的初次引用，使用新RCBigInt对象的代价要更高一些。每当RCBigInt产生了
// 对BigInt的初次引用时，就会在堆内存中创建一个BigInt对象并指向它。对于基于堆栈(局部变量)的简单
// BigInt对象而言，则不必付出这种代价。此类的情况在移除最后一次BigInt引用时也会发生。这是因为
// 底层的BigInt对象被释放并还给堆内存。
class RCBigInt {
	friend RCBigInt operator+(const RCBigInt&, const RCBigInt&);

public:
	RCBigInt(const char* p) : value(new BigInt(p)) {}
	RCBigInt(unsigned u = 0) : value(new BigInt(u)) {}
	RCBigInt(const BigInt& bi) : value(new BigInt(bi)) {}

	void print() const { value->print(); }

private:
	RCPtr<BigInt> value;
};

inline RCBigInt operator+(const RCBigInt& left, const RCBigInt& right)
{
	return RCBigInt(*(left.value) + *(right.value));
}

} // namespace

int test_reference_counting_1()
{
	std::chrono::high_resolution_clock::time_point time_start, time_end;
	const int count{10000000};
 
{ // test BigInt create
	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count; ++i) {
		BigInt a = i;
		BigInt b = i + 1;
		BigInt c = i + 2;
		BigInt d = i + 3;
	}
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "BigInt create time spend: %f seconds\n",
		(std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // test RCBigInt create
	// RCBigInt测试会更多地忙于初次引用的创建及之后将其销毁的工作
	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count; ++i) {
		RCBigInt a = i;
		RCBigInt b = i + 1;
		RCBigInt c = i + 2;
		RCBigInt d = i + 3;
	}
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "RCBigInt create time spend: %f seconds\n",
		(std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // test BigInt assign
	BigInt a, b, c;
	BigInt d = 1;

	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count; ++i) {
		a = b = c = d;
	}
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "BigInt assign time spend: %f seconds\n",
		(std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // test RCBigInt assign
	// 对RCBigInt对象的赋值操作效率高于BigInt对象，但是创建和销毁对象时却相反
	RCBigInt a, b, c;
	RCBigInt d = 1;

	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count; ++i) {
		a = b = c = d;
	}
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "RCBigInt assign time spend: %f seconds\n",
		(std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

	return 0;
}

} // namespace reference_counting_

