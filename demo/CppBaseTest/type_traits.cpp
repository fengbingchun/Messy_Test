#include "type_traits.hpp"
#include <type_traits>
#include <iostream>
#include <array>
#include <string>
#include <complex>

// Blog: https://blog.csdn.net/fengbingchun/article/details/115427439

// code reference: 
//		https://www.cplusplus.com/reference/type_traits/
//		https://en.cppreference.com/w/cpp/types

namespace type_traits_ {

template <unsigned n>
struct factorial : std::integral_constant<int, n * factorial<n - 1>::value> {};

template <>
struct factorial<0> : std::integral_constant<int, 1> {};

constexpr unsigned test_integral_constant() noexcept { return factorial<5>::value; }
static_assert(test_integral_constant() == 120, "value should be 120");

// reference: https://stackoverflow.com/questions/58694521/what-is-stdfalse-type-or-stdtrue-type
struct true_type {
	static constexpr bool value = true;
	constexpr operator bool() const noexcept { return value; }
	// ...
};

struct false_type {
	static constexpr bool value = false;
	constexpr operator bool() const noexcept { return value; }
	// ...
};

int test_type_traits_helper_classes()
{
	// std::integral_constant: 编译时将常量作为类型，一般用做trait type的基类
	static_assert(factorial<5>::value == 120, "value should be 120");
	fprintf(stdout, "result: %u\n", factorial<5>::value); // constexpr(no calculations on runtime)

	// std::true_type: ==> std::integral_constant<bool, true>, 实例化integral_constant用以表示布尔值true
	static constexpr bool value1 = true;
	static_assert(std::integral_constant<bool, value1>::value == true, "value should be true");

	// std::false_type: ==> std::integral_constant<bool, false>, 实例化integral_constant用以表示布尔值false
	static constexpr bool value2 = false;
	static_assert(std::integral_constant<bool, value2>::value == false, "value should be false");

	return 0;
}

int func(int i) { return i; }
class A { public: void func() {} };
struct B { int func(int a) { return a; } };
union C { int i; float f; };
enum class D { x, y, z };
struct F { int a; };
struct G { virtual void func() = 0; };
struct H { virtual void func() {} };
struct I : G { void func() override {} };
struct J { ~J() {} };
struct K { int x; K(const K& k) : x(k.x){}; };
struct L { virtual ~L() {} };
struct M { M& operator=(M&&) = delete; };
struct N { N& operator=(const A&) { return *this; } };
struct P { P(int) {} };
struct Q { ~Q() = delete; };
struct R : B { };
struct S {};

int test_type_traits_type_traits()
{
	// 1.Primary type categories
	// std::is_array: T是不是数组类型，注意：此函数不会将数组类模板的实例化视为数组类型
	static_assert(std::is_array<A>::value == false, "");
	static_assert(std::is_array<A[3]>::value == true, "");
	static_assert(std::is_array<std::array<int, 3>>::value == false, "");

	// std::is_class: T是不是类类型
	static_assert(std::is_class<A>::value == true, "");
	static_assert(std::is_class<B>::value == true, "");
	static_assert(std::is_class<int>::value == false, "");

	// std::is_enum: T是不是枚举类型
	static_assert(std::is_enum<D>::value == true, "");
	static_assert(std::is_enum<A>::value == false, "");

	// std::is_floating_point: T是不是浮点类型
	static_assert(std::is_floating_point<float>::value == true, "");
	static_assert(std::is_floating_point<float&>::value == false, "");
	static_assert(std::is_floating_point<const double>::value == true, "");

	// std::is_function: T是不是函数类型
	static_assert(std::is_function<decltype(func)>::value == true, "");
	static_assert(std::is_function<int(int)>::value == true, "");

	// std::is_integral: T是不是整数类型
	static_assert(std::is_integral<const int>::value == true, "");
	static_assert(std::is_integral<bool>::value == true, "");
	static_assert(std::is_integral<char>::value == true, "");

	// std::is_lvalue_reference: T是不是左值引用类型
	static_assert(std::is_lvalue_reference<const A&>::value == true, "");
	static_assert(std::is_lvalue_reference<const A&&>::value == false, "");

	// std::is_rvalue_reference: T是不是右值引用类型
	static_assert(std::is_rvalue_reference<const A&>::value == false, "");
	static_assert(std::is_rvalue_reference<const A&&>::value == true, "");

	// std::is_member_function_pointer: T是不是非静态成员函数指针类型
	void(A::*pt)() = &A::func;
	static_assert(std::is_member_function_pointer<decltype(pt)>::value == true, "");
	static_assert(std::is_member_function_pointer<void(B::*)()>::value == true, "");
	static_assert(std::is_member_function_pointer<A*>::value == false, "");

	// std::is_member_object_pointer: T是不是非静态成员数据指针类型
	int F::* pt2 = &F::a;
	static_assert(std::is_member_object_pointer<decltype(pt2)>::value == true, "");
	static_assert(std::is_member_object_pointer<int F::*>::value == true, "");

	// std::is_pointer: T是不是指针类型
	static_assert(std::is_pointer<int*>::value == true, "");
	static_assert(std::is_pointer<int**>::value == true, "");
	static_assert(std::is_pointer<int(*)(int)>::value == true, "");

	//  std::is_union: T是不是联合体类型
	static_assert(std::is_union<C>::value == true, "");
	static_assert(std::is_union<A>::value == false, "");

	// std::is_void: T是不是void类型
	static_assert(std::is_void<void>::value == true, "");
	static_assert(std::is_void<A>::value == false, "");

	// 2.Composite type categories: 复合类型
	// std::is_arithmetic: T是不是算术类型
	static_assert(std::is_arithmetic<char>::value == true, "");
	static_assert(std::is_arithmetic<char*>::value == false, "");

	// std::is_compound: T是不是复合类型，即不是基础类型
	static_assert(std::is_compound<char>::value == false, "");
	static_assert(std::is_compound<char*>::value == true, "");
	static_assert(std::is_compound<char&>::value == true, "");

	// std::is_fundamental: T是不是基础类型
	static_assert(std::is_fundamental<char>::value == true, "");
	static_assert(std::is_fundamental<char*>::value == false, "");
	static_assert(std::is_fundamental<void>::value == true, "");

	// std::is_member_pointer: T是不是非静态成员指针类型
	int F::* pt3 = &F::a;
	static_assert(std::is_member_pointer<int F::*>::value == true, "");
	static_assert(std::is_member_pointer<decltype(pt3)>::value == true, "");
	static_assert(std::is_member_pointer<void(B::*)()>::value == true, "");

	// std::is_object: T是不是对象类型,除函数、引用、void之外的所有类型
	static_assert(std::is_object<float>::value == true, "");
	static_assert(std::is_object<float&>::value == false, "");
	static_assert(std::is_object<int(int)>::value == false, "");
	static_assert(std::is_object<int(*)(int)>::value == true, "");

	// std::is_reference: T是不是引用类型，左值引用或右值引用
	static_assert(std::is_reference<int&>::value == true, "");
	static_assert(std::is_reference<int&&>::value == true, "");

	// std::is_scalar: T是不是标量类型，基础类型
	static_assert(std::is_scalar<int&>::value == false, "");
	static_assert(std::is_scalar<int*>::value == true, "");
	static_assert(std::is_scalar<A>::value == false, "");

	// 3.Type properties
	// std::is_abstract: T是不是抽象类
	static_assert(std::is_abstract<G>::value == true, "");
	static_assert(std::is_abstract<H>::value == false, "");
	static_assert(std::is_abstract<I>::value == false, "");

	// std::is_const: T是不是const限定类型
	static_assert(std::is_const<const int>::value == true, "");
	static_assert(std::is_const<const int*>::value == false, "");
	static_assert(std::is_const<int* const>::value == true, "");

	// std::is_empty: T是不是空类,空类是不存储任何数据的类，即没有非静态数据成员、没有虚函数、也没有虚基类
	static_assert(std::is_empty<F>::value == false, "");
	static_assert(std::is_empty<A>::value == true, "");
	static_assert(std::is_empty<H>::value == false, "");

	// std::is_literal_type: T是不是literal类型，可视为constexpr类型，标量、引用、certain 类，以及这些类型的数组都是literal类型
	//static_assert(std::is_literal_type<A>::value == true, ""); // std::is_literal_type and std::is_literal_type_v are deprecated in C++17
	//static_assert(std::is_literal_type<D>::value == true, "");
	//static_assert(std::is_literal_type<J>::value == false, "");

	// std::is_pod: T是不是POD(Plain Old Data)类型，C语言支持的数据类型，若是类，它需要是trial(普通的)和standard-layout
	static_assert(std::is_pod<A>::value == true, "");
	static_assert(std::is_pod<G>::value == false, "");
	static_assert(std::is_pod<J>::value == false, "");

	// std::is_polymorphic: T是不是多态类
	static_assert(std::is_polymorphic<A>::value == false, "");
	static_assert(std::is_polymorphic<G>::value == true, "");
	static_assert(std::is_polymorphic<I>::value == true, "");

	// std::is_signed: T是不是有符号算术类型
	static_assert(std::is_signed<A>::value == false, "");
	static_assert(std::is_signed<char>::value == true, "");
	static_assert(std::is_signed<int&>::value == false, "");

	// std::is_standard_layout: T是不是standard layout类型，如标量；若是类，则要求没有虚函数、虚基类、
	// 所有的非静态数据成员都具有相同的访问权限、在派生类中没有非静态数据成员
	static_assert(std::is_standard_layout<int>::value == true, "");
	static_assert(std::is_standard_layout<C>::value == true, "");
	static_assert(std::is_standard_layout<H>::value == false, "");

	// std::is_trivial: T是不是trivial(普通的)类型，如标量，存储连续；若是类，要求是默认构造/拷贝/移动拷贝/析构,没有虚成员
	static_assert(std::is_trivial<float>::value == true, "");
	static_assert(std::is_trivial<C>::value == true, "");
	static_assert(std::is_trivial<F>::value == true, "");

	// std::is_trivially_copyable: T是不是普通的拷贝类型，如标量；若是类，要求使用隐式定义的拷贝/移动函数、析构函数，没有虚成员
	#ifdef _MSC_VER
		static_assert(std::is_trivially_copyable<unsigned int>::value == true, "");
		static_assert(std::is_trivially_copyable<C>::value == true, "");
		static_assert(std::is_trivially_copyable<K>::value == false, "");
	#endif

	// std::is_unsigned: T是不是无符号算术类型
	static_assert(std::is_unsigned<unsigned int>::value == true, "");
	static_assert(std::is_unsigned<double>::value == false, "");

	// std::is_volatile: T是不是volatile-qualified类型
	static_assert(std::is_volatile<unsigned int>::value == false, "");
	static_assert(std::is_volatile<volatile int>::value == true, "");
	static_assert(std::is_volatile<volatile int*>::value == false, "");
	static_assert(std::is_volatile<int* volatile>::value == true, "");

	// 4.Type features
	// std::has_virtual_destructor: T是不是具有虚析构函数的类
	static_assert(std::has_virtual_destructor<A>::value == false, "");
	static_assert(std::has_virtual_destructor<L>::value == true, "");

	// std::is_assignable: U是不是赋值给T的类型; std::is_copy_assignable/std::is_move_assignable: T是不是拷贝/移动赋值类型
	static_assert(std::is_assignable<N, A>::value == true, "");
	static_assert(std::is_assignable<A, N>::value == false, "");
	static_assert(std::is_copy_assignable<int>::value == true, "");
	static_assert(std::is_copy_assignable<L>::value == true, "");
	static_assert(std::is_copy_assignable<M>::value == false, "");
	static_assert(std::is_move_assignable<L>::value == true, "");
	static_assert(std::is_move_assignable<M>::value == false, "");

	// std::is_constructible: 使用指定的参数，T是不是可构造类型
	// std::is_copy_constructible/std::is_default_constructible/std::is_move_constructible: T是不是拷贝构造/默认构造/移动构造类型
	static_assert(std::is_constructible<int>::value == true, "");
	static_assert(std::is_constructible<P, int>::value == true, "");
	static_assert(std::is_constructible<P, int, int>::value == false, "");
	static_assert(std::is_copy_constructible<M>::value == false, "");
	static_assert(std::is_copy_constructible<P>::value == true, "");
	static_assert(std::is_default_constructible<P>::value == false, "");
	static_assert(std::is_default_constructible<L>::value == true, "");
	static_assert(std::is_move_constructible<L>::value == true, "");
	static_assert(std::is_move_constructible<M>::value == false, "");

	// std::is_destructible: T是不是destructible类型,其析构函数不会被删除，且在派生类中是可访问的
	static_assert(std::is_destructible<int>::value == true, "");
	static_assert(std::is_destructible<L>::value == true, "");
	static_assert(std::is_destructible<Q>::value == false, "");

	#ifdef _MSC_VER
		static_assert(std::is_trivially_assignable<F, F>::value == true, "");
		static_assert(std::is_trivially_constructible<F>::value == true, "");
		static_assert(std::is_trivially_destructible<J>::value == false, "");
	#endif

	static_assert(std::is_nothrow_assignable<F, F>::value == true, "");
	static_assert(std::is_nothrow_constructible<F>::value == true, "");
	static_assert(std::is_nothrow_destructible<J>::value == true, "");

	// 5.Type relationships
	// std::is_base_of: 判断基类是不是派生类的基类
	static_assert(std::is_base_of<int, int>::value == false, "");
	static_assert(std::is_base_of<G, I>::value == true, "");
	static_assert(std::is_base_of<I, G>::value == false, "");

	// std::is_convertible: 判断From是不是可以隐式转换到To
	static_assert(std::is_convertible<int, double>::value == true, "");
	static_assert(std::is_convertible<B, R>::value == false, "");
	static_assert(std::is_convertible<R, B>::value == true, "");

	// std::is_same: 判断U和T是不是属于相同的类型,当且仅当一个是另一种的typedef时，才认为两个不同的类型名代表相同的类型
	static_assert(std::is_same<int, const int>::value == false, "");
	typedef int integer_type;
	static_assert(std::is_same<int, integer_type>::value == true, "");
	typedef R R1;
	static_assert(std::is_same<R1, R>::value == true, "");

	// 6.Property queries
	// std::alignment_of: 返回类型T的对齐值
	static_assert(std::alignment_of<int>::value == 4, "");
	static_assert(std::alignment_of<S>::value == 1, "");
	static_assert(std::alignment_of<H*>::value == 8, "");

	// std::extent: 获取类型T第i维的范围
	typedef int mytype[][24][60];
	static_assert(std::extent<mytype, 0>::value == 0, "");
	static_assert(std::extent<mytype, 1>::value == 24, "");
	static_assert(std::extent<mytype, 2>::value == 60, "");
	static_assert(std::extent<mytype, 3>::value == 0, "");

	return 0;
}

int test_type_traits_type_transformations()
{
	// 1.Const-volatile qualifications
	// std::add_const/std::remove_const: 对类型T添加/移除const限定符
	typedef std::add_const<int>::type Ax;         // const int
	typedef std::add_const<const int>::type Bx;   // const int(unchanged)
	typedef std::add_const<const int*>::type Cx;  // const int* const
	typedef std::add_const<int* const>::type Dx;  // int* const(unchanged)
	typedef std::add_const<const int&>::type Ex;  // const int&(unchanged

	static_assert(std::is_const<Ax>::value == true, "");
	static_assert(std::is_const<Bx>::value == true, "");
	static_assert(std::is_const<Cx>::value == true, "");
	static_assert(std::is_const<Dx>::value == true, "");
	static_assert(std::is_const<Ex>::value == false, "");

	typedef std::remove_const<const char>::type Fx;
	static_assert(std::is_same<char, Fx>::value == true, "");

	// std::add_cv/std::remove_cv: 对类型T添加/移除const volatile限定符
	typedef std::add_cv<int>::type Ay;
	typedef std::add_cv<const int>::type By;
	typedef std::add_cv<volatile int>::type Cy;
	typedef std::add_cv<const volatile int>::type Dy;

	static_assert(std::is_same<const volatile int, Ay>::value == true, "");
	static_assert(std::is_same<const volatile int, By>::value == true, "");
	static_assert(std::is_same<const volatile int, Cy>::value == true, "");
	static_assert(std::is_same<const volatile int, Dy>::value == true, "");

	typedef std::remove_cv<const volatile char>::type Fy;
	static_assert(std::is_same<char, Fy>::value == true, "");

	// std::add_volatile/std::remove_volatile: 对类型T添加/移除volatile限定符
	typedef std::add_volatile<int>::type Az;            // volatile int
	typedef std::add_volatile<volatile int>::type Bz;   // volatile int(unchanged)
	typedef std::add_volatile<int* volatile>::type Cz;  // int* volatile(unchanged)
	typedef std::add_volatile<volatile int*>::type Dz;  // volatile int* volatile
	typedef std::add_volatile<volatile int&>::type Ez;  // volatile int&(unchanged)

	static_assert(std::is_volatile<Az>::value == true, "");
	static_assert(std::is_volatile<Bz>::value == true, "");
	static_assert(std::is_volatile<Cz>::value == true, "");
	static_assert(std::is_volatile<Dz>::value == true, "");
	static_assert(std::is_volatile<Ez>::value == false, "");

	typedef std::remove_volatile<volatile char>::type Fz;
	static_assert(std::is_same<char, Fz>::value == true, "");

	// 2.Compound type alterations
	// std::add_pointer/std::remove_pointer: 获取/移除T的指针类型
	typedef std::add_pointer<int>::type Ap;        // int*
	typedef std::add_pointer<const int>::type Bp;  // const int*
	typedef std::add_pointer<int&>::type Cp;       // int*
	typedef std::add_pointer<int*>::type Dp;       // int**
	typedef std::add_pointer<int(int)>::type Ep;   // int(*)(int)

	static_assert(std::is_same<int*, Ap>::value == true, "");
	static_assert(std::is_same<const int*, Bp>::value == true, "");
	static_assert(std::is_same<int*, Cp>::value == true, "");
	static_assert(std::is_same<int**, Dp>::value == true, "");
	static_assert(std::is_same<int*, Ep>::value == false, "");

	typedef std::remove_pointer<int**>::type Fp;
	static_assert(std::is_same<int*, Fp>::value == true, "");

	// std::add_lvalue_reference/std::add_rvalue_reference:获取T左值/右值引用类型；std::remove_reference: 获取T非引用类型
	typedef std::add_lvalue_reference<int>::type Aq;    // int&
	typedef std::add_lvalue_reference<int&>::type Bq;   // int&
	typedef std::add_lvalue_reference<int&&>::type Cq;  // int&
	typedef std::add_lvalue_reference<int*>::type Dq;   // int*&

	static_assert(std::is_same<int&, Aq>::value == true, "");
	static_assert(std::is_same<int&, Bq>::value == true, "");
	static_assert(std::is_same<int&, Cq>::value == true, "");
	static_assert(std::is_same<int&, Dq>::value == false, "");

	typedef std::add_rvalue_reference<int>::type Ar;    // int&&
	typedef std::add_rvalue_reference<int&>::type Br;   // int&  (no change)
	typedef std::add_rvalue_reference<int&&>::type Cr;  // int&& (no change)
	typedef std::add_rvalue_reference<int*>::type Dr;   // int*&&

	static_assert(std::is_same<int&&, Ar>::value == true, "");
	static_assert(std::is_same<int&&, Br>::value == false, "");
	static_assert(std::is_same<int&&, Cr>::value == true, "");
	static_assert(std::is_same<int&&, Dr>::value == false, "");

	typedef std::remove_reference<int&>::type Fq;
	typedef std::remove_reference<int&&>::type Fr;
	static_assert(std::is_same<int, Fq>::value == true, "");
	static_assert(std::is_same<int, Fr>::value == true, "");

	// std::decay: 获得T的decay(退化)类型
	typedef std::decay<int>::type As;           // int
	typedef std::decay<int&>::type Bs;          // int
	typedef std::decay<int&&>::type Cs;         // int
	typedef std::decay<const int&>::type Ds;    // int
	typedef std::decay<int[2]>::type Es;        // int*
	typedef std::decay<int(int)>::type Fs;      // int(*)(int)

	static_assert(std::is_same<int, As>::value == true, "");
	static_assert(std::is_same<int, Bs>::value == true, "");
	static_assert(std::is_same<int, Cs>::value == true, "");
	static_assert(std::is_same<int, Ds>::value == true, "");
	static_assert(std::is_same<int, Es>::value == false, "");
	static_assert(std::is_same<int, Fs>::value == false, "");

	// std::make_signed/std::make_unsigned: 获取与T对应的带符号/无符号类型，并保留所有cv限定符
	typedef std::make_signed<int>::type At;                // int
	typedef std::make_signed<unsigned>::type Bt;           // int
	typedef std::make_signed<const unsigned>::type Ct;     // const int

	static_assert(std::is_same<int, At>::value == true, "");
	static_assert(std::is_same<int, Bt>::value == true, "");
	static_assert(std::is_same<int, Ct>::value == false, "");

	typedef std::make_unsigned<int>::type Au;                // unsigned int
	static_assert(std::is_same<unsigned, Au>::value == true, "");

	// std::remove_all_extents/std::remove_extent: 移除所有/数组范围
	typedef std::remove_all_extents<int>::type Av;                // int
	typedef std::remove_all_extents<int[24]>::type Bv;            // int
	typedef std::remove_all_extents<int[24][60]>::type Cv;        // int
	typedef std::remove_all_extents<int[][60]>::type Dv;          // int
	typedef std::remove_all_extents<const int[10]>::type Ev;      // const int

	static_assert(std::is_same<int, Av>::value == true, "");
	static_assert(std::is_same<int, Bv>::value == true, "");
	static_assert(std::is_same<int, Cv>::value == true, "");
	static_assert(std::is_same<int, Dv>::value == true, "");
	static_assert(std::is_same<int, Ev>::value == false, "");

	typedef std::remove_extent<int[24][60]>::type Cw;        // int[60]
	typedef std::remove_extent<int[][60]>::type Dw;          // int[60]
	static_assert(std::is_same<int, Cw>::value == false, "");
	static_assert(std::is_same<int, Dw>::value == false, "");

	// std::underlying_type: 获取枚举类型T的基础类型
	enum class Aa { a, b, c };
	enum Ba : short { x, y, z };
	typedef std::underlying_type<Aa>::type A_under;   // int
	typedef std::underlying_type<Ba>::type B_under;   // short

	static_assert(std::is_same<int, A_under>::value == true, "");
	static_assert(std::is_same<int, B_under>::value == false, "");

	// 3.Other type generators
	// std::aligned_storage: 将内存分配与对象创建分离时使用
	// std::aligned_union: Obtains a POD type suitable for use as storage for any object whose type is listed in Types, and a size of at least Len

	// std::common_type: 在类型列表中获取所有类型都可以转换为的通用类型
	typedef std::common_type<char, short, int>::type Ab;           // int
	typedef std::common_type<float, double>::type Bb;              // double
	typedef std::common_type<R, B>::type Cb;					   // B
	typedef std::common_type<const int, volatile int>::type Db;    // int

	static_assert(std::is_same<int, Ab>::value == true, "");
	static_assert(std::is_same<int, Bb>::value == false, "");
	static_assert(std::is_same<int, Cb>::value == false, "");
	static_assert(std::is_same<int, Db>::value == true, "");

	// std::conditional: 根据cond是true还是false，获取成员类型
	typedef std::conditional<true, int, float>::type Ac;                      // int
	typedef std::conditional<false, int, float>::type Bc;                     // float
	typedef std::conditional<std::is_integral<Ac>::value, long, int>::type Cc; // long
	typedef std::conditional<std::is_integral<Bc>::value, long, int>::type Dc; // int

	static_assert(std::is_same<int, Ac>::value == true, "");
	static_assert(std::is_same<int, Bc>::value == false, "");
	static_assert(std::is_same<int, Cc>::value == false, "");
	static_assert(std::is_same<int, Dc>::value == true, "");

	// std::enable_if: 如果条件满足则启用类型
	// std::result_of: Obtains the result type of a call to Fn with arguments of the types listed in ArgTypes

	return 0;
}

} // namespace type_traits_
