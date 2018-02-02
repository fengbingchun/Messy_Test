#ifndef FBC_MESSY_TEST_FORWARD_DECLARATION_HPP_
#define FBC_MESSY_TEST_FORWARD_DECLARATION_HPP_

// Blog: http://blog.csdn.net/fengbingchun/article/details/54957885

// reference: http://stackoverflow.com/questions/553682/when-can-i-use-a-forward-declaration

namespace forward_declaraion_ {
/*
	Put yourself in the compiler's position: when you forward declare a type,
	all the compiler knows is that this type exists; it knows nothing about
	its size, members, or methods. This is why it's called an incomplete type.
	Therefore, you cannot use the type to declare a member, or a base class,
	since the compiler would need to know the layout of the type.
	*/
// Assuming the following forward declaration.
class X;

// Here's what you can and cannot do.

// 1. What you can do with an incomplete type:
// 1.1 Declare a member to be a pointer or a reference to the incomplete type:
class Foo_1 {
	X *pt1;
	X &pt2;
};

// 1.2 Declare functions or methods which accept/return incomplete types:
void f1(X);
X f2();

/* 1.3 Define functions or methods which accept/return pointers/references to
	the incomplete type (but without using its members): */
namespace {
void f3(X*, X&) {}
X& f4() { X* x = nullptr; return *x; }
X* f5() { X* x = nullptr; return x; }
} // namespace

// 2. What you cannot do with an incomplete type:
// 2.1 Use it as a base class
// class Foo_2 : X {} // compiler error!

// 2.2 Use it to declare a member:
/* class Foo_2 {
	X m; // compiler error!
	}; */

// 2.3 Define functions or methods using this type
// void f6(X x) {} // compiler error!
// X f7() {} // compiler error!

/* 2.4 Use its methods or fields,
	in fact trying to dereference a variable with incomplete type */
/* class Foo_3 {
	X *m;
	void method() {
	m->someMethod();      // compiler error!
	int i = m->someField; // compiler error!
	}
	}; */

/*
	When it comes to templates, there is no absolute rule:
	whether you can use an incomplete type as a template parameter is
	dependent on the way the type is used in the template.
	*/

/*
	"In computer programming, a forward declaration is a declaration of an identifier
	(denoting an entity such as a type, a variable, or a function) for which the
	programmer has not yet given a complete definition."
	In C++, you should forward declare classes instead of including headers.
	Don¡¯t use an #include when a forward declaration would suffice.
	When you include a header file you introduce a dependency
	that will cause your code to be recompiled whenever the header file changes.
	If your header file includes other header files, any change to those files will
	cause any code that includes your header to be recompiled.
	Therefore, you should prefer to minimize includes,
	particularly includes of header files in other header files.
	You can significantly reduce the number of header files
	you need to include in your own header files by using forward declarations.
	*/

} // namespace forward_declaraion_

#endif // FBC_MESSY_TEST_FORWARD_DECLARATION_HPP_
