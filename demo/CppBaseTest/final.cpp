#include "final.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52318564

/////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/final
struct Base {
	virtual void foo();
};

struct A : Base {
	virtual void foo() final; // A::foo is final
	// void bar() final; // Error: non-virtual function cannot be final
};

struct B final : A { // struct B is final
	// void foo(); // Error: foo cannot be overridden as it's final in A
};

// struct C : B { }; // Error: B is final

////////////////////////////////////////////////////////
// reference: http://blog.smartbear.com/c-plus-plus/use-c11-inheritance-control-keywords-to-prevent-inconsistencies-in-class-hierarchies/
struct A_ {
	virtual void func() const;
};

struct B_ : A_ {
	void func() const override final; //OK
};

// struct C_ : B_ { void func()const; }; //error, B::func is final

