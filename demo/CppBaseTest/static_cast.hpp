#ifndef FBC_MESSY_TEST_STATIC_CAST_HPP_
#define FBC_MESSY_TEST_STATIC_CAST_HPP_

#include <iostream>

// reference: https://msdn.microsoft.com/zh-cn/library/c36yw7x9.aspx
class B1 {
public:
	virtual void Test(){}
};

class D1 : public B1 {};

class CCTest {
public:
	void setNumber(int);
	void printNumber() const;
private:
	int number;
};

class B2 { };
class C2 : public B2 { };
class D2 : public C2 { };

class A3 { virtual void f(); };
class B3 { virtual void f(); };

class B4 { virtual void f(); };
class D4 : public B4 { virtual void f(); };

// Returns a hash code based on an address
unsigned short Hash(void *p);

void test_static_cast1();
void test_static_cast2(B1* pb, D1* pd);
void test_static_cast3(B1* pb);
void test_static_cast4();
void test_static_cast5();
void test_static_cast6();
void test_static_cast7();
void test_static_cast8();
void test_static_cast9();
void test_static_cast10();

#endif // FBC_MESSY_TEST_STATIC_CAST_HPP_