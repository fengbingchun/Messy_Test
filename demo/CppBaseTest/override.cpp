#include "override.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52304284

//////////////////////////////////////////////
// reference: http://stackoverflow.com/questions/18198314/what-is-the-override-keyword-in-c-used-for
struct base_override {
	virtual void foo() = 0;
};

struct derived_override : base_override {
	virtual void foo() override
	{
		std::cout << "__PRETTY_FUNCTION__" << std::endl;
	}
};

int test_override1()
{
	base_override* override = new derived_override();
	override->foo();

	return 0;
}

//////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/override
struct A {
	virtual void foo();
	void bar();
};

struct B : A {
	// void foo() const override; // Error: B::foo does not override A::foo (signature mismatch)
	void foo() override; // OK: B::foo overrides A::foo
	// void bar() override; // Error: A::bar is not virtual
};

//////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/jj678987.aspx
class BaseClass
{
	virtual void funcA();
	virtual void funcB() const;
	virtual void funcC(int = 0);
	void funcD();
};

class DerivedClass : public BaseClass
{
	virtual void funcA() override; // ok

	// virtual void funcB() override; // compiler error: DerivedClass::funcB() does not 
	// override BaseClass::funcB() const

	// virtual void funcC(double = 0.0) override; // compiler error: 
	// DerivedClass::funcC(double) does not 
	// override BaseClass::funcC(int)

	// void funcD() override; // compiler error: DerivedClass::funcD() does not 
	// override the non-virtual BaseClass::funcD()
};

//////////////////////////////////////
// reference: https://segmentfault.com/a/1190000003698366
struct B_ {
	virtual void f();
	virtual void g() const;
	virtual void h(char);
	void k();      // non-virtual
	virtual void m() final;
};

struct D_ : B_ {
	void f() override;     // OK: 重写 B::f()
	// void g() override;     // error: 不同的函数声明，不能重写
	virtual void h(char);  // 重写 B::h( char ); 可能会有警告
	// void k() override;     // error: B::k() 不是虚函数
	// virtual void m();       // error: m()在基类中声明禁止重写
};
