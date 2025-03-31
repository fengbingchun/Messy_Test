#include "effective_modern_cplusplus.hpp"
#include <cstddef>
#include <cstdint>
#include <string.h>
#include <cmath>
#include <functional>
#include <iostream>
#include <array>
#include <vector>
#include <initializer_list>
#include <typeinfo>
#include <memory>
#include <map>
#include <unordered_map>
#include <atomic>
#include <numeric>
#include <limits>
#include <mutex>
#include <thread>
#include <list>
#include <type_traits>
#include <algorithm>
#include <iterator>
#include <array>
#include <type_traits>
#include <set>
#include <future>
#include <regex>
#include <chrono>

// Blog: https://blog.csdn.net/fengbingchun/article/details/104136592

// reference: 《Effective Modern C++》

namespace effective_modern_cplusplus_ {

/////////////////////////////////////////////////
//template<typename T>
//void f(ParamType param);

template<typename T>
void f(T& param) {} // param是个引用

template<typename T>
void f2(T* param) {} // param现在是个指针

template<typename T>
void f3(T&& param) {} // param现在是个万能引用

template<typename T>
void f4(T param) {} // param现在是按值传递

// 以编译期常量形式返回数组尺寸(该数组形参未起名字，因为我们只关系其含有的元素个数)
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept // 将该函数声明为constexpr，能够使得其返回值在编译期就可用。从而就可以在
{						   // 声明一个数组时，指定其尺寸和另一数组相同，而后者的尺寸则从花括号初始化式(braced initializer)计算得出
	return N;
}

void someFunc(int, double) {} // someFunc是个函数，其型别为void(int, double)

int test_item_1()
{
	//f(expr); // 已某表达式调用f
	// 在编译期，编译器会通过expr推导两个型别：一个是T的型别，另一个是ParamType的型别，这两个型别往往不一样

	int x = 27; // x的型别是int
	const int cx = x; // cx的型别是const int
	const int& rx = x; // rx是x的型别为const int的引用

	f(x); // T的型别是int, param的型别是int&
	f(cx); // T的型别是const int, param的型别是const int&
	f(rx); // T的型别是const int, param的型别是const int&, 注意：即使rx具有引用型别，T也并未被推导成一个引用，原因在于，rx的引用性(reference-ness)会在型别推导过程中被忽略

	const int* px = &x; // px is ptr to x as a const int
	f2(&x); // T is int, param's type is int*
	f2(px); // T is const int, param's type is const int*

	f3(x); // x is lvalue, so T is int&, param's type is also int&
	f3(cx); // cx is lvalue, so T is const int&, param's type is also const int&
	f3(rx); // rx is lvalue, so T is const int&, param's type is also const int&
	f3(27); // 27 is rvalue, so T is int, param's type is therefore int&&

	// param是个完全独立于cx和rx存在的对象----是cx和rx的一个副本
	f4(x); // T's and param's types are both int
	f4(cx); // T's and param's types are again both int
	f4(rx); // T's and param's types are still both int

	const char* const ptr = "Fun with pointers"; // ptr is const pointer to const object
	f4(ptr); // pass arg of type const char* const

	const char name[] = "J. P. Briggs"; // name's type is const char[13]
	const char* ptrToName = name; // array decays to pointer

	f4(name); // name is array, but T deduced as const char*
	f(name); // pass array to f, T的型别推导结果是const char[13], 而f的形参(该数组的一个引用)型别则被推导为const char (&)[13]

	int keyVals[] = {1, 3, 7, 9, 11, 22, 35};
	fprintf(stdout, "array length: %d\n", arraySize(keyVals)); // 7
	int mappedVals[arraySize(keyVals)]; // mappedVals被指定与之相同
	std::array<int, arraySize(keyVals)> mappedVals2; // mappedVals2也指定为7个元素

	f4(someFunc); // param被推导为函数指针(ptr-to-func)，具体型别是void (*)(int, double)
	f(someFunc); // param被推导为函数引用(ref-to-func), 具体型别是void (&)(int, double)

	return 0;
}

/////////////////////////////////////////////////
//template<typename T>
//void f(ParamType param);

void someFunc2(int, double) {} // someFunc是个函数，其型别为void(int, double)

/*auto createInitlist()
{
	return {1, 2, 3}; // error: can't deduce type for {1, 2, 3}
}*/

int test_item_2()
{
	//f(expr); // 已某表达式调用f
	// 当某变量采用auto来声明时，auto就扮演了模板中的T这个角色，而变量的型别饰词则扮演的是ParamType的角色
	auto x = 27; // x的型别饰词(type specifier)就是auto自身, x既非指针也非引用
	const auto cx = x; // 型别饰词成了const auto, cx既非指针也非引用
	const auto& rx = x; // 型别饰词又成了const auto&, rx是个引用，但不是万能引用

	auto&& uref1 = x; // x的型别是int,且是左值，所以uref1的型别是int&
	auto&& uref2 = cx; // cx的型别是const int, 且是左值，所以uref2的型别是const int&
	auto&& uref3 = 27; // 27的型别是int,且是右值，所以uref3的型别是int&&

	const char name[] = "R. N. Briggs"; // name的型别是const char[13]
	auto arr1 = name; // arr1's type is const char*
	auto& arr2 = name; // arr2's type is const char (&)[13]

	auto func1 = someFunc2; // func1's type is void(*)(int, double)
	auto& func2 = someFunc2; // func2's type is void(&)(int, double)

	// 若要声明一个int，并将其初始化为值27，C++98中有两种可选语法
	int x1 = 27;
	int x2(27);
	// 而C++11为了支持统一初始化(uniform initialization),增加了下面的语法选项
	int x3 = {27};
	int x4{27};

	auto x1_1 = 27; // type is int, value is 27
	auto x2_1(27); // type is int, value is 27
	auto x3_1 = {27}; // type is std::initializer_list<int>, value is {27}
	auto x4_1{27}; // type is std::initializer_list<int>, value is {27}
	//auto x5_1 = {1, 2, 3.0}; // error, can't deduce T for std::initializer_list<T> 

	std::vector<int> v;
	auto resetV = [&v](const auto& newValue) { v = newValue; }; // C++14
	//resetV({1, 2, 3}); // error, can't deduce type for {1, 2, 3}

	return 0;
}

/////////////////////////////////////////////////
class Widget3 {};
bool f5(const Widget3& w) { return true; } // decltype(w) is const Widget3&; decltype(f5) is bool(const Widgeet3&)

template<typename Container, typename Index>
// 这里的auto只为说明这里使用了C++11中的返回值型别尾序语法(trailing return type syntax),即该函数的返回值型别将在形参列表之后(在"->"之后)
// 尾序返回值的好处在于，在指定返回值型别时可以使用函数形参
//auto authAndAccess(Container&& c, Index i) -> decltype(std::forward<Container>(c)[i]) // C++11
decltype(auto) authAndAccess(Container&& c, Index i) // C++14, c is now a universal reference
{
	return std::forward<Container>(c)[i];
}

struct Point {
	int x, y; // decltype(Point::x) is int; decltype(Point::y) is int
};

decltype(auto) ff3_1()
{
	int x = 0;
	return x; // decltype(x)是int,所以ff3_1返回的是int
	//return (x); // decltype((x))是int&,所以ff3_1返回的是int&
}

int test_item_3()
{
	const int i = 0; // decltype(i) is const int
	Widget3 w; // decltype(w) is Widget3
	if (f5(w)) {} // decltype(f5(w)) is bool
	std::vector<int> v; // decltype(v) is vector<int>

	const Widget3& cw = w;
	auto myWidget31 = cw; // auto型别推导:myWidget31的型别是Widget3
	decltype(auto) myWidget32 = cw; // decltype型别推导:myWidget32的型别是const Widget3&

	return 0;
}

/////////////////////////////////////////////////
int test_item_4()
{
	const int theAnswer = 42;
	auto x = theAnswer; // int
	auto y = &theAnswer; // const int*
	fprintf(stdout, "%s, %s\n", typeid(x).name(), typeid(y).name());

	return 0;
}

/////////////////////////////////////////////////
class Widget5 {};
bool operator<(const Widget5& lhs, const Widget5& rhs) { return true; }

int test_item_5()
{
	int x1; // potentially uninitialized
	//auto x2; // error, initializer required
	auto x3 = 0; // fine, x's value is well-defined

	auto derefUPLess = [](const std::unique_ptr<Widget5>& p1, const std::unique_ptr<Widget5>& p2) { return *p1 < *p2; }; // comparison func. for Widget5 pointed to by std::unique_ptrs
	auto derefLess = [](const auto& p1, const auto& p2) { return *p1 < *p2; }; // C++14 comparison function for values pointed to by anything pointer-like

	// bool(const std::unique_ptr<Widget5>&, const std::unique_ptr<Widget5>&) // C++11 signature for std::unique_ptr<Widget5> comparison function
	std::function<bool(const std::unique_ptr<Widget5>&, const std::unique_ptr<Widget5>&)> func;

	// 在C++11中，不用auto也可以声明derefUPLess
	std::function<bool(const std::unique_ptr<Widget5>&, const std::unique_ptr<Widget5>&)> derefUPLess2 = [](const std::unique_ptr<Widget5>& p1, const std::unique_ptr<Widget5>& p2) { return *p1 < *p2; };

	std::vector<int> v{1, 2, 3};
	unsigned sz1 = v.size(); // 不推荐,32位和64位windows上,unsigned均是32位，而在64位windows上，std::vector<int>::size_type则是64位
	auto sz2 = v.size(); // 推荐，sz2's type is std::vector<int>::size_type
	
	std::unordered_map<std::string, int> m;
	for (const std::pair<std::string, int>& p : m) {} // 显式型别声明，不推荐,the key part of a std::unordered_map is const， so the type of std::pair in the hash table is std::<const std::string, int>, 需要进行隐式转换，会产生临时对象
	for (const auto& p : m) {} // 推荐

	return 0;
}

/////////////////////////////////////////////////
class Widget6 {};
std::vector<bool> features(const Widget6& w)
{
	return std::vector<bool>{true, true, false, false, true, false};
}

void processWidget6(const Widget6& w, bool highPriority) {}

double calcEpsilon() { return 1.0; }

int test_item_6()
{
	Widget6 w;
	bool highPriority =features(w)[5]; // 正确,显式声明highPriority的型别
	processWidget6(w, highPriority);

	// 把highPriority从显示型别改成auto
	auto highPriority2 = features(w)[5]; // highPriority2的型别由推导而得,std::vector<bool>的operator[]的返回值并不是容器中一个元素的引用(单单bool是个例外),返回的是个std::vector<bool>::reference型别的对象,返回一个std::vector<bool>型别的临时对象
	processWidget6(w, highPriority2); // undefined behavior, highPriority2 contains dangling pointer(空悬指针)

	auto highPriority3 = static_cast<bool>(features(w)[5]); // 正确
	processWidget6(w, highPriority3);

	float ep = calcEpsilon(); // 隐式转换 double-->float,这种写法难以表明"我故意降低了函数的返回值精度"
	auto ep2 = static_cast<float>(calcEpsilon()); // 推荐

	return 0;
}

/////////////////////////////////////////////////
class Widget7 {
public:
	Widget7(int i, bool b) {} // constructor not declaring std::initializer_list params
	Widget7(int i, double d) {}
	Widget7(std::initializer_list<long double> il) { fprintf(stdout, "std::initializer_list params\n"); }
	Widget7() = default;
	Widget7(int) {}

	operator float() const { return 1.0f; } // 强制转换成float型别, 注意：此函数的作用,下面的w13和w15

private:
	int x{0}; // fine, x's default value is 0
	int y = 0; // also fine
	//int z(0); // error
};

int test_item_7()
{
	int x(0); // 初始化物在小括号内
	int y = 0; // 初始化物在等号之后
	int z{0}; // 初始化物在大括号内
	int z2 = {0}; // 使用等号和大括号来指定初始化物，一般C++会把它和只有大括号的语法同样处理

	Widget7 w1; // call default constructor
	Widget7 w2 = w1; // not an assignment; calls copy constructor
	w1 = w2; // an assignment; calls copy operator=

	std::vector<int> v{1, 3, 5}; // v's initial content is 1, 3, 5

	std::atomic<int> ai1{0}; // fine
	std::atomic<int> ai2(0); // fine
	//std::atomic<int> ai3 = 0; // error

	double a{std::numeric_limits<double>::max()}, b{std::numeric_limits<double>::max()}, c{std::numeric_limits<double>::max()};
	//int sum1{a + b + c}; // error, sum of doubles may not be expressible as int
	int sum2(a + b + c); // okey(value of expression truncated to an int)
	int sum3 = a + b + c; // okey(value of expression truncated to an int)

	Widget7 w3(10); // call Widget7 constructor with argument 10
	Widget7 w4(); // most vexing parse! declares a function named w4 that returns a Widget7
	Widget7 w5{}; // call Widget7 constructor with no args

	Widget7 w6(10, true); // calls first constructor
	Widget7 w7{10, true}; // alse calls first constructor, 假设没有Widget7(std::initializer_list<long double>)构造函数
	Widget7 w8(10, 5.0); // calls second constructor
	Widget7 w9{10, 5.0}; // also calls second constructor, 假设没有Widget7(std::initializer_list<long double>)构造函数

	Widget7 w10{10, true}; // 使用大括号，调用的是带有std::initializer_list型别形参的构造函数(10和true被强制转换为long double)
	Widget7 w11{10, 5.0}; // 使用大括号，调用的是带有std::initializer_list型别形参的构造函数(10和5.0被强制转换为long double) 

	Widget7 w12(w11); // 使用小括号，调用的是拷贝构造函数
	Widget7 w13{w11}; // 使用大括号，调用的是带有std::initializer_list型别形参的构造函数(w11的返回值被强制转换成float,随后float又被强制转换成long double)
	Widget7 w14(std::move(w11)); // 使用小括号，调用的是移动构造函数
	Widget7 w15{std::move(w11)}; // 使用大括号，调用的是带有std::initializer_list型别形参的构造函数(和w13的结果理由相同)
	
	Widget7 w16{}; // call Widget7 constructor with no args,调用无参的构造函数，而非调用带有std::initializer_list型别形参的构造函数
	Widget7 w17({}); // 调用带有std::initializer_list型别形参的构造函数，传入一个空的std::initializer_list
	Widget7 w18{{}}; // 调用带有std::initializer_list型别形参的构造函数，传入一个空的std::initializer_list

	std::vector<int> v1(10, 20); // 调用了形参中没有任何一个具备std::initializer_list型别的构造函数，结果是：创建了一个含有10个元素的std::vector，所有的元素的值都是20
	std::vector<int> v2{10, 20}; // 调用了形参中含有std::initializer_list型别的构造函数，结果是：创建了一个含有2个元素的std::vector，元素的值分别为10和20
	fprintf(stdout, "v1 length: %d, v2 length: %d\n", v1.size(), v2.size());

	return 0;
}

/////////////////////////////////////////////////
void f8(int) { fprintf(stdout, "f8(int)\n"); }
void f8(bool) { fprintf(stdout, "f8(bool)\n"); }
void f8(void*) { fprintf(stdout, "f8(void*)\n"); }

class Widget8 {};
int f8_1(std::shared_ptr<Widget8> spw) { return 0; }
double f8_2(std::unique_ptr<Widget8> upw) { return 1.f; }
bool f8_3(Widget8* pw) { return false; }

template<typename FuncType, typename MuxType, typename PtrType>
//auto lockAddCall(FuncType func, MuxType& mutex, PtrType ptr) -> decltype(func(ptr)) // C++11
decltype(auto) lockAndCall(FuncType func, MuxType& mutex, PtrType ptr) // C++14
{
	using MuxGuard = std::lock_guard<std::mutex>; // C++11 typedef
	MuxGuard g(mutex);
	return func(ptr);
}

int test_item_8()
{
	f8(0); // calls f8(int), not f8(void*)
	//f8(NULL); // might not compile, but typically calls f8(int), never calls f8(void*)
	f8(nullptr); // calls f(void*) overload

	std::mutex f1m, f2m, f3m;
	//auto result1 = lockAndCall(f8_1, f1m, 0); // error, ‘void result1’ has incomplete type
	//auto result2 = lockAndCall(f8_2, f2m, NULL); // error: ‘void result2’ has incomplete type
	auto result3 = lockAndCall(f8_3, f3m, nullptr);

	return 0;
}

/////////////////////////////////////////////////
class Widget9 {};

typedef void (*FP1)(int, const std::string&);
using FP2 = void (*)(int, const std::string&);

template<typename T>
using MyAllocList1 = std::list<T/*, MyAlloc<T>*/>; // C++11,  MyAllocList1<T>是std::list<T, MyAlloc<T>>的同义词

template<typename T>
struct MyAllocList2 { // MyAllocList<T>::type 是std::list<T, MyAlloc<T>>的同义词
	typedef std::list<T/*, MyAlloc<T>*/> type;
};

template<typename T>
class Widget9_2 { // Widget9_2<T>含一个MyAllocList2<T>型别的数据成员
private:
	typename MyAllocList2<T>::type list; // MyAllocList2<T>::type代表一个依赖于模板型别形参(T)的型别，所以MyAllocList2<T>::type称为带依赖型别，C++中规则之一就是带依赖型别必须前面加个typename
};

template<typename T>
class Widget9_1 {
private:
	MyAllocList1<T> list; // 不再有"typename"和"::type"
};

int test_item_9()
{
	typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS1;
	using UPtrMapSS2 = std::unique_ptr<std::unordered_map<std::string, std::string>>; // C++11, alias declaration

	MyAllocList1<Widget9> lw1;
	MyAllocList2<Widget9>::type lw2;

	typedef const char cc;
	std::remove_const<cc>::type a; // char a
	std::remove_const<const char*>::type b; // const char* b

	typedef int&& rval_int;
	typedef std::remove_reference<int>::type A;

	//std::remove_const<T>::type // C++11: const T --> T
	//std::remove_const_t<T>     // C++14中的等价物
	//template<class T>
	//using remove_const_t = typename remove_const<T>::type;

	//std::remove_reference<T>::type // C++11: T&/T&& --> T
	//std::remove_reference_t<T>     // C++14中的等价物
	//template<class T>
	//using remove_reference_t = typename remove_reference<T>::type;

	return 0;
}

/////////////////////////////////////////////////
std::vector<std::size_t> primeFactors(std::size_t x) { return std::vector<std::size_t>(); }

enum class Status; // 前置声明, 默认底层型别(underlying type)是int
enum class Status2: std::uint32_t; // Status2的底层型别是std::uint32_t
enum Color: std::uint8_t; // 不限范围的枚举型别的前置声明，底层型别是std::uint8_t

int test_item_10()
{
	enum Color1 { black, white, red }; // 不限范围的(unscoped)枚举型别：black, white, red所在作用域和Color1相同
	//auto white = false; // error, white already declared in this scope
	Color1 c1 = black;

	enum class Color2 { black2, white2, red2 }; // C++11, 限定作用域的(scoped)枚举型别:black2, white2, red2所在作用域被限定在Color2内
	auto white2 = false; // 没问题，范围内并无其它"white2"
	//Color2 c1 = black2; // 错误，范围内并无名为"black2"的枚举量
	Color2 c2 = Color2::black2; // fine
	auto c3 = Color2::black2; // also fine

	if (c1 < 14.5) // 将Color1型别和double型别值作比较,怪胎
		auto factors = primeFactors(c1);

	//if (c2 < 14.5) // 错误，不能将Color型别和double型别值作比较
	//	auto facotrs = primeFactors(c2); // 错误，不能将Color2型别传入要求std::size_t型别形参的函数

	return 0;
}

/////////////////////////////////////////////////
class Widget11 {
public:
	Widget11(const Widget11&) = delete;
	Widget11& operator=(const Widget11&) = delete;

	template<typename T>
	void processPointer(T* ptr) {}
};

template<>
void Widget11::processPointer<void>(void*) = delete;

bool isLucky(int number) { return false; } // 原始版本
bool isLucky(char) = delete; // 拒绝char型别
bool isLucky(bool) = delete; // 拒绝bool型别
bool isLucky(double) = delete; // 拒绝double和float型别

template<typename T>
void processPointer(T* ptr) {}
template<>
void processPointer<void>(void*) = delete; // 不可以使用void*来调用processPointer
template<>
void processPointer<char>(char*) = delete; // 不可以使用char*来调用processPointer

int test_item_11()
{
	//if (isLucky('a')) {} // error, call to deleted function

	return 0;
}

/////////////////////////////////////////////////
class Base {
public:
	virtual void doWork() {} // 基类中的虚函数
};

class Derived : public Base {
public:
	virtual void doWork() override {} // 改写(override)了Base:doWork(“virtual”在这可写可不写)
};

class Widget12 {
public:
	void doWork() & { fprintf(stdout, "&\n"); } // 这个版本的doWork仅在*this是左值时调用
	void doWork() && { fprintf(stdout, "&&\n"); } // 这个版本的doWork仅在*this是右值时调用

	using DataType = std::vector<double>;
	DataType& data() & { fprintf(stdout, "data() &\n"); return values; } // 对于左值Widget12型别，返回左值
	DataType data() && { fprintf(stdout, "data() &&\n"); return std::move(values); } // 对于右值Widget12型别，返回右值

private:
	DataType values;
};

Widget12 makeWidget() // 工厂函数(返回右值)
{
	Widget12 w;
	return w;
}

void doSomething(Widget12& w) {} // 仅接受左值的Widget12型别
void doSomething(Widget12&& w) {} // 仅接受右值的Widget12型别

int test_item_12()
{
	std::unique_ptr<Base> upb = std::make_unique<Derived>(); // 创建基类指针，指涉到派生类对象
	upb->doWork(); // 通过基类指针调用doWork,结果是派生类函数被调用

	Widget12 w; // 普通对象(左值)
	w.doWork(); // 以左值调用Widget12::doWork(即Widget12::doWork &)
	makeWidget().doWork(); // 以右值调用Widget12::doWork(即Widget12::doWork &&)

	auto vals1 = w.data(); // 调用Widget12::data的左值重载版本,vals1拷贝构造完成初始化
	auto vals2 = makeWidget().data(); // 调用Widget12::data的右值重载版本，vals2采用移动构造完成初始化

	return 0;
}

/////////////////////////////////////////////////
template<class C>
auto cbegin_(const C& container) -> decltype(std::begin(container)) // cbegin的一个实现
{
	return std::begin(container);
}

template<class C>
auto cend_(const C& container) -> decltype(std::end(container)) // cend的一个实现
{
	return std::end(container);
}

int test_item_13()
{
	std::vector<int> values{1, 10, 1000};
	auto it = std::find(values.cbegin(), values.cend(), 1983); // use cbegin and cend
	values.insert(it, 1998);

#ifdef _MSC_VER
	auto it2 = std::find(std::cbegin(values), std::cend(values), 1983); // C++14,非成员函数版本的cbegin, cend, gcc 4.9.4 don't support
	values.insert(it2, 1998);
#endif

	auto it3 = std::find(cbegin_(values), cend_(values), 1983);
	values.insert(it3, 1998);

	return 0;
}

/////////////////////////////////////////////////
int f14_1(int x) throw() { return 1; } // f14_1不会发射异常: C++98风格
int f14_2(int x) noexcept { return 2; } // f14_2不会发射异常: C++11风格

//RetType function(params) noexcept; // 最优化
//RetType function(params) throw(); // 优化不够
//RetType function(params); // 优化不够

int test_item_14()
{
	return 0;
}

/////////////////////////////////////////////////
// pow前面写的那个constexpr并不表明pow要返回一个const值，它表明的是如果base和exp是编译期常量，pow的返回结果
// 就可以当一个编译期常量使用；如果base和exp中有一个不是编译期常量，则pow的返回结果就将在执行期计算
constexpr int pow(int base, int exp) noexcept // pow is a constexpr func that never throws
{
	return (exp == 0 ? 1 : base * pow(base, exp - 1)); // C++11
	//auto result = 1; // C++14
	//for (int i = 0; i < exp; ++i) result *= base;
	//return result;
}

auto readFromDB(const std::string& str) { return 1; }

class Point15 {
public:
	constexpr Point15(double xVal = 0, double yVal = 0) noexcept : x(xVal), y(yVal) {}
	constexpr double xValue() const noexcept { return x; }
	constexpr double yValue() const noexcept { return y; }
	void setX(double newX) noexcept { x = newX; }
	//constexpr void setX(double newX) noexcept { x = newX; } // C++14
	void setY(double newY) noexcept { y = newY; }
	//constexpr void setY(double newY) noexcept { y = newY; } // C++14
private:
	double x, y;
};

constexpr Point15 midpoint(const Point15& p1, const Point15& p2) noexcept
{
	return { (p1.xValue() + p2.xValue()) / 2, (p1.yValue() + p2.yValue()) / 2}; // call constexpr member function
}

int test_item_15()
{
	int sz = 0; // non-constexpr variable
	//constexpr auto arraySize1 = sz; // error, sz's value not known at compilation
	//std::array<int, sz> data1; // error, sz's value not known at compilation
	constexpr auto arraySize2 = 10; // fine, 10 is a compile-time constant
	std::array<int, arraySize2> data2; // fine, arraySize2 is constexpr

	// 注意：const对象不一定经由编译器已知值来初始化
	const auto arraySize3 = sz; // fine, arraySize3 is const copy of sz,arraySize3是sz的一个const副本
	//std::array<int arraySize3> data3; // error, arraySize3.s value not known at compilation

	constexpr auto numConds = 5;
	std::array<int, pow(3, numConds)> results; // results has 3^numConds elements

	auto base = readFromDB("base"); // get these values at runtime
	auto exp = readFromDB("exponent");
	auto baseToExp = pow(base, exp); // call pow function at runtime

	constexpr Point15 p1(9.4, 27.7); // fine, "runs" constexpr constructor during compilation
	constexpr Point15 p2(28.8, 5.3);

	constexpr auto mid = midpoint(p1, p2); // 使用constexpr函数的结果来初始化constexpr对象

	return 0;
}

/////////////////////////////////////////////////
class Point16 { // 使用std::atomic型别的对象来计算调用次数
public:
	double distanceFromOrigin() const noexcept
	{
		++callCount; // 带原子性的自增操作
		return std::sqrt((x*x) + (y*y));
	}

private:
	mutable std::atomic<unsigned> callCount{0};
	double x, y;
};

class Widget16 {
public:
	int magicValue() const
	{
		std::lock_guard<std::mutex> guard(m); // lock m
		if (cacheValid) return cachedValue;
		else {
			auto val1 = expensiveComputation1();
			auto val2 = expensiveComputation2();
			cachedValue = val1 + val2;
			cacheValid = true;
			return cachedValue;
		}
	} // unlock m

private:
	int expensiveComputation1() const { return 1; }
	int expensiveComputation2() const { return 2; }

	mutable std::mutex m;
	mutable int cachedValue; // no longer atomic
	mutable bool cacheValid{false};
};

int test_item_16()
{
	return 0;
}

/////////////////////////////////////////////////
class Widget17 {
public:
	Widget17(Widget17&& rhs); // move constructor
	Widget17& operator=(Widget17&& rhs); // move assignment operator

	Widget17(const Widget17&) = default; // default copy constructor, behavior is OK
	Widget17& operator=(const Widget17&) = default; // default copy assign, behavior is OK
};

int test_item_17()
{
	return 0;
}

/////////////////////////////////////////////////
class Investment { // 投资
public:
	virtual ~Investment() {}
};
class Stock : public Investment {}; // 股票
class Bond : public Investment {}; // 债券
class RealEstate : public Investment {}; // 不动产

void makeLogEntry(Investment*) {}

auto delInvmt1 = [](Investment* pInvestment) { // custom deleter(a lambda expression), 使用无状态lambda表达式作为自定义析构器
			makeLogEntry(pInvestment);
			delete pInvestment;
		};

void delInvmt2(Investment* pInvestment) // 使用函数作为自定义析构器
{
	makeLogEntry(pInvestment);
	delete pInvestment;
}

template<typename... Ts>
//std::unique_ptr<Investment> makeInvestment(Ts&&... params) // return std::unique_ptr to an object created from the given args
std::unique_ptr<Investment, decltype(delInvmt1)> makeInvestment(Ts&&... params) // 改进的返回类型,返回值尺寸与Investment*相同
//std::unique_ptr<Investment, void(*)(Investment*)> makeInvestment(Ts&&... params) // 返回值尺寸等于Investment*的尺寸+至少函数指针的尺寸
{
	//std::unique_ptr<Investment> pInv(nullptr);
	std::unique_ptr<Investment, decltype(delInvmt1)> pInv(nullptr, delInvmt1); // ptr to be returned

	if (nullptr/* a Stoc object should be created*/) {
		pInv.reset(new Stock(std::forward<Ts>(params)...));
	} else if (nullptr/*a Bond object should be created*/) {
		pInv.reset(new Bond(std::forward<Ts>(params)...));
	} else if (nullptr/*a RealEstate object should be created*/) {
		pInv.reset(new RealEstate(std::forward<Ts>(params)...));
	}

	return pInv;
}

int test_item_18()
{
	//auto pInvestment = makeInvestment(arguments); // pInvestment is of type std::unique_ptr<Investment>
	//std::shared_ptr<Investment> sp = makeInvestment(arguments); // converts std::unique_ptr to std::shared_ptr

	return 0;
} // destroy *pInvestment

/////////////////////////////////////////////////
class Widget19 {};
void makeLogEntry(Widget19*) {}
auto loggingDel = [](Widget19* pw) { makeLogEntry(pw); delete pw; }; // custom deleter,自定义析构器

int test_item_19()
{
	std::unique_ptr<Widget19, decltype(loggingDel)> upw(new Widget19, loggingDel); // 析构器型别是智能指针型别的一部分
	std::shared_ptr<Widget19> spw(new Widget19, loggingDel); // 析构器型别不是智能指针型别的一部分

	auto pw = new Widget19; // pw是个裸指针
	//std::shared_ptr<Widget19> spw1(pw, loggingDel); // 为*pw创建一个控制块
	//std::shared_ptr<Widget19> spw2(pw, loggingDel); // 为*pw创建了第二个控制块
	// 以上两行语句会导致*pw被析构两次，第二次析构将会引发未定义行为,不推荐上面的用法

	std::shared_ptr<Widget19> spw1(new Widget19, loggingDel); // 直接传递new表达式
	std::shared_ptr<Widget19> spw2(spw1); // spw2使用的是和spw1同一个控制块

	return 0;
}

/////////////////////////////////////////////////
class Widget20 {};

int test_item_20()
{
	auto spw = std::make_shared<Widget20>(); // spw构造完成后，指涉到Widget20的引用计数置为1
	std::weak_ptr<Widget20> wpw(spw); // wpw和spw指涉到同一个Widget20，引用计数保持为1
	spw = nullptr; // 引用计数变为0,Widget20对象被析构，wpw空悬(dangle)
	if (wpw.expired()) // 若wpw不再指涉到任何对象
	      fprintf(stdout, "wpw doesn't point to an object\n");

	std::shared_ptr<Widget20> spw1 = wpw.lock(); // 若wpw失效，则spw1为空
	auto spw2 = wpw.lock(); // 使用auto,同上，若wpw失效，则spw2为空
	if (spw2 == nullptr) fprintf(stdout, "wpw expired\n");

	std::shared_ptr<Widget20> spw3(wpw); // 若wpw失效,抛出std::bad_weak_ptr型别的异常

	return 0;
}

/////////////////////////////////////////////////
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params) // std::make_unique的一个基础版本，不支持数组和自定义析构器
{
	return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

class Widget21 {};

int test_item_21()
{
	// 使用了new的版本将被创建对象的型别重复写了两遍，但是make系列函数则没有
	auto upw1(std::make_unique<Widget21>()); // 使用make系列函数
	std::unique_ptr<Widget21> upw2(new Widget21); // 不使用make系列函数
	auto spw1(std::make_shared<Widget21>()); // 使用make系列函数
	std::shared_ptr<Widget21> spw2(new Widget21); // 不使用make系列函数

	return 0;
}

/////////////////////////////////////////////////
// 以下代码假设位于gadget.h文件中
typedef struct Gadget { // Gadget is some userdefined type
	int x, y;
	std::string str;
};

// 以下代码假设位于widget.h文件中
class Widget22 {
public:
	Widget22();
	// 注意：这里仅声明，不能定义，定义必须放在widget.cpp文件中，因为Impl是个不完整类型
	~Widget22(); // declaration only

	// 添加支持移动操作,注意：这里仅声明，不能定义，定义必须放在widget.cpp文件中,因为Impl是个不完整类型
	Widget22(Widget22&& rhs); // declaration only
	Widget22& operator=(Widget22&& rhs); // declaration only

	// 添加拷贝操作
	Widget22(const Widget22& rhs); // declaration only
	Widget22& operator=(const Widget22& rhs); // declaration only

private:
	// 原数据成员
	//std::string name;
	//std::vector<double> data;
	//Gadget g1, g2, g3;

	struct Impl; // declare implementation struct
	//Impl* pImpl; // and pointer to it
	std::unique_ptr<Impl> pImpl; // 使用智能指针代替裸指针(raw pointer)
	// 如果使用std::shared_ptr而非std::unique_ptr，则无需再有析构函数或移动操作的声明
};

// 以下代码假设位于widget.cpp中
//#include "widget.h"
//#include "gadget.h"
//#include <string>
//#include <vector>

struct Widget22::Impl { // Widget22::Impl的实现，包括此前在Widget22中的数据成员
	std::string name;
	std::vector<double> data;
	Gadget g1, g2, g3;
};

//Widget22::Widget22() : pImpl(new Impl) {} // allocate data members for this Widget22 object
Widget22::Widget22() : pImpl(std::make_unique<Impl>()) {}
//Widget22::~Widget22() { delete pImpl; } // destroy data members for this Widget22 object
Widget22::~Widget22() = default; // ~Widget22 definition
Widget22::Widget22(Widget22&& rhs) = default;
Widget22& Widget22::operator=(Widget22&& rhs) = default;
Widget22::Widget22(const Widget22& rhs) : pImpl(std::make_unique<Impl>(*rhs.pImpl)) {}
Widget22& Widget22::operator=(const Widget22& rhs) { *pImpl = *rhs.pImpl; return *this; }

int test_item_22()
{
	Widget22 w1;
	auto w2(std::move(w1));
	Widget22 w3(w2);
	w1 = std::move(w2);

	return 0;
}

/////////////////////////////////////////////////
// 比较接近C++11中std::move的示例实现,它不完全符合标准的所有细节
template<typename T> // in namespace std
typename std::remove_reference<T>::type&& move(T&& param)
{
	using ReturnType = typename std::remove_reference<T>::type&&; // 别名声明
	return static_cast<ReturnType>(param);
}

// C++14中比较接近的std::move示例实现
template<typename T> // C++14, still in namespace std
decltype(auto) move(T&& param)
{
	using ReturnType = std::remove_reference_t<T>&&;
	return static_cast<ReturnType>(param);
}

class Widget23 {};

void process(const Widget23& lvalArg)  { fprintf(stderr, "process lvalues\n"); } // process lvalues
void process(Widget23&& rvalArg) { fprintf(stderr, "process rvalues\n"); } // process rvalues

template<typename T>
void logAndProcess(T&& param) // template that passes param to process
{
	process(std::forward<T>(param));
}

int test_item_23()
{
	Widget23 w;
	logAndProcess(w); // call with lvalue
	logAndProcess(std::move(w)); // call with rvalue

	return 0;
}

/////////////////////////////////////////////////
class Widget24 {};

void f24(Widget24&& param) { fprintf(stdout, "Widget24&&\n"); } // no type deduction(不涉及型别推导), param is an rvalue reference
template<typename T>
void f24_1(std::vector<T>&& param) { fprintf(stdout, "std::vector<T>&&\n"); } // param is an rvalue reference
template<typename T>
void f24(T&& param) { fprintf(stdout, "T&&\n"); } // not rvalue reference, param is a universal reference
template<typename T>
void f24(const T&& param) {} // param is an rvalue reference

int test_item_24()
{
	Widget24&& var1 = Widget24(); // no type deduction, var1 is an rvalue reference
	auto&& var2 = var1; // not rvalue reference, var2 is a universal reference

	Widget24 w;
	f24(w); // lvalue passed to f, param's type is Widget24&(an lvalue reference)
	f24(std::move(w)); // rvalue passed to f, param's type is Widget24&&(an rvalue reference)

	std::vector<int> v;
	//f24_1(v); // error, can't bind lvalue to rvalue reference
	f24_1(std::move(v));
	//f24(v); // will call: void f24(T&& param)

	return 0;
}

/////////////////////////////////////////////////
class Widget25 {
public:
	Widget25(Widget25&& rhs) : name(std::move(rhs.name)), p(std::move(rhs.p)) {} // rhs is rvalue reference
	template<typename T>
	void setName(T&& newName) { name = std::forward<T>(newName); } // newName is universal reference

private:
	std::string name;
	typedef struct SomeDataStructure {} SomeDataStructure;
	std::shared_ptr<SomeDataStructure> p;
};

class Matrix {
public:
	Matrix& operator+=(const Matrix& rhs) { return *this; }
	void reduce() {}
};

Matrix operator+(Matrix&& lhs, const Matrix& rhs) // 按值返回
{
	lhs += rhs;
	return std::move(lhs); // 将lhs移入返回值
}

template<typename T>
Matrix reduceAndCopy(T&& mat) // 按值返回，万能引用形参
{
	mat.reduce();
	return std::forward<T>(mat); // 对于右值是移入返回值;对于左值是拷贝入返回值
}

int test_item_25()
{
	return 0;
}

/////////////////////////////////////////////////
std::multiset<std::string> names; // global data structure

//void logAndAdd(const std::string& name) // 第一种实现方法
template<typename T>
void logAndAdd(T&& name) // universal reference，第二种实现方法
{
	auto now = std::chrono::system_clock::now();
	fprintf(stdout, "time point\n");
	//names.emplace(name);
	names.emplace(std::forward<T>(name));
}

std::string nameFromIdx(int idx) // 返回索引对应的名字
{
	return std::string("xxx");
}

void logAndAdd(int idx) // 新的重载函数
{
	auto now = std::chrono::system_clock::now();
	fprintf(stdout, "time point2\n");
	names.emplace(nameFromIdx(idx));
}

int test_item_26()
{
	std::string petName("Darla");

	logAndAdd(petName); // as before, copy lvalue into multiset
	logAndAdd(std::string("Persephone")); // move rvalue instead of copying it
	logAndAdd("Patty Dog"); // create std::string in multiset instead of copying a temporary std::string

	logAndAdd(22); // 调用形参型别为int的重载版本

	short nameIdx = 100;
	//logAndAdd(nameIdx); // error c2664, 形参型别为T&&的版本可以将T推导为short, 对于short型别的实参来说，万能引用产生了比int更好的匹配

	return 0;
}

/////////////////////////////////////////////////
std::multiset<std::string> names27; // global data structure
std::string nameFromIdx27(int idx) { return std::string("xxx"); }

template<typename T>
void logAndAddImpl(T&& name, std::false_type) // 非整型实参
{
	auto now = std::chrono::system_clock::now();
	fprintf(stdout, "time point: no int\n");
	names27.emplace(std::forward<T>(name));
}

void logAndAddImpl(int idx, std::true_type) // 整型实参
{
	auto now = std::chrono::system_clock::now();
	fprintf(stdout, "time point: int\n");
	names.emplace(nameFromIdx(idx));
}

template<typename T>
void logAndAdd27(T&& name) // name to data structure
{
	logAndAddImpl(std::forward<T>(name), std::is_integral<typename std::remove_reference<T>::type>());
}

class Person {
public:
	//template<typename T, typename = typename std::enable_if<!std::is_same<Person, typename std::decay<T>::type>::value>::type>
	//template<typename T, typename = typename std::enable_if<!std::is_base_of<Person, typename std::decay<T>::type>::value>::type> // 可使继承自Person的类，当调用基类的构造函数时走的是基类的拷贝或移动构造函数
	//template<typename T, typename = std::enable_if_t<!std::is_base_of<Person, std::decay_t<T>>::value>> // C++14
	template<typename T, typename = std::enable_if_t<!std::is_base_of<Person, std::decay_t<T>>::value &&
														!std::is_integral<std::remove_reference_t<T>>::value>> // C++14
	explicit Person(T&& n) // 只有指定的条件满足了才会启用此模板, constructor for string and args convertible to string
		: name(std::forward<T>(n)) 
	{
		// assert that a std::string can be created from a T object
		static_assert(std::is_constructible<std::string, T>::value, "Parameter n can't be used to construct a std::string");
	}

	explicit Person(int idx) // constructor for integral args
		: name(nameFromIdx27(idx)) {}

private:
	std::string name;
};

int test_item_27()
{
	// 注意：test_item_26()与test_item_27()实现的差异
	std::string petName("Darla");

	logAndAdd27(petName);
	logAndAdd27(std::string("Persephone"));
	logAndAdd27("Patty Dog");

	logAndAdd27(22);

	short nameIdx = 100;
	logAndAdd27(nameIdx);

	return 0;
}

/////////////////////////////////////////////////
class Widget28 {};

template<typename T>
void func(T&& param) {}

Widget28 widget28Factory() // function returning rvalue
{
	return Widget28();
}

int test_item_28()
{
	Widget28 w; // a variable(an lvalue)
	func(w); // call func with lvalue, T deduced to be Widget28&

	func(widget28Factory()); // call func with rvalue, T deduced to be Widget28

	auto&& w1 = w; // w1是左值引用
	auto&& w2 = widget28Factory(); // w2是右值引用

	return 0;
}

/////////////////////////////////////////////////
class Widget29 {};

int test_item_29()
{

	std::vector<Widget29> vw1;
	// ... // put data into vw1
	// move vw1 into vw2. runs in constant time. only ptrs in vw1 and vw2 are modified
	auto vw2 = std::move(vw1);

	std::array<Widget29, 10000> aw1;
	// ... // put data into aw1
	// move aw1 into aw2. runs in linear time. all elements in aw1 are moved into aw2
	auto aw2 = std::move(aw1);

	return 0;
}

/////////////////////////////////////////////////
void f30(const std::vector<int>& v) {}
void f30_2(std::size_t val) {}

template<typename T>
void fwd(T&& param) // accept any argument
{
	f30(std::forward<T>(param)); // forward it to f30
}

template<typename T>
void fwd30_2(T&& param) // accept any argument
{
	f30_2(std::forward<T>(param)); // forward it to f30_2
}

class Widget30 {
public:
	static const std::size_t MinVals = 28; // MinVals' declaration
};
//const std::size_t Widget30::MinVals; // no define for MinVals

struct IPv4Header {
	std::uint32_t version : 4,
		IHL : 4,
		DSCP : 6,
		ECN : 2,
		totalLength : 16;
};

int test_item_30()
{
	f30({ 1, 2, 3 }); // fine, "{1, 2, 3}"implicitly converted to std::vector<int>
	//fwd({ 1, 2, 3 }); // error, 大括号初始化物的运用，就是一种完美转发失败的情形
	auto il = { 1, 2, 3 }; // il's type deduced to be std::initializer_list<int>
	fwd(il); // fine, prefect-forwards il to f

	std::vector<int> widget30Data;
	widget30Data.reserve(Widget30::MinVals); // use of MinVals

	f30_2(Widget30::MinVals); // fine, treated as "f30_2(28)"
	//fwd30_2(Widget30::MinVals); // error, shouldn't link, note: windows can link

	IPv4Header h;
	memset(&h, 0, sizeof(IPv4Header));
	f30_2(h.totalLength); // fine

	//fwd30_2(h.totalLength); // error
	auto length = static_cast<std::uint16_t>(h.totalLength);
	fwd30_2(length); // forward the copy

	return 0;
}

/////////////////////////////////////////////////
using FilterContainer = std::vector<std::function<bool(int)>>;
FilterContainer filters;

class Widget31 {
public:
	void addFilter() const // add an entry to filters
	{
		//filters.emplace_back([=](int value) { return value % divisor == 0; } );
		// 捕获只能针对于在创建lambda式的作用域内可见的非静态局部变量(包括形参)
		//filters.emplace_back([](int value) { return value % divisor == 0; }); // error, divisor not available
		//filters.emplace_back([divisor](int value) { return value % divisor == 0; }); // error, no local divisor to capture

		auto currentObjectPtr = this;
		filters.emplace_back([currentObjectPtr](int value) { return value % currentObjectPtr->divisor == 0; });

		auto divisorCopy = divisor; // copy data member
		filters.emplace_back([divisorCopy](int value) { return value % divisorCopy == 0; }); // capture the copy use the copy

		static int xxx = 2;
		//filters.emplace_back([xxx](int value) { return value % xxx == 0; }); // error
		//filters.emplace_back([=](int value) { return value % xxx == 0; });
		++xxx;
	}

private:
	int divisor; // used in Widget31's filter
};

int test_item_31()
{

	filters.emplace_back(
		[](int value) { return value % 5 == 0; } // 不捕获任何外部变量
	);
	filters.emplace_back(
		[&](int value) { return value % 5 == 0; } // 以引用形式捕获所有外部变量
	);
	filters.emplace_back(
		[=](int value) { return value % 5 == 0; } // 以值的形式捕获所有外部变量
	);

	return 0;
}

/////////////////////////////////////////////////
class Widget32 {
public:
	bool isValidated() const { return true; }
	bool isProcessed() const { return true; }
	bool isArchived() const { return true; }

private:
};

class IsValAndArch { // is validated and archived
public:
	using DataType = std::unique_ptr<Widget32>;

	explicit IsValAndArch(DataType&& ptr) : pw(std::move(ptr)) {}

	bool operator()() const
	{
		return pw->isValidated() && pw->isArchived();
	}

private:
	DataType pw;
};

std::vector<double> data32; // 欲移入闭包的对象

int test_item_32()
{
	auto pw = std::make_unique<Widget32>();
	auto func = [pw = std::move(pw)]{ return pw->isValidated() && pw->isArchived(); }; // C++14, 采用std::move(pw)初始化闭包类的数据成员
	// pw = std::move(pw): 初始化捕获，位于"="左侧的，在你所指定的闭包类中数据成员的名字，而位于"="右侧的则是初始化表达式
	// "="左右两侧处于不同的作用域。左侧作用域就是闭包类的作用域，而右侧的作用域与定义lambda式的作用域相同
	// "pw = std::move(pw)"表达了"在闭包类中创建一个数据成员pw,然后使用针对局部变量pw实施std::move的结果来初始化该数据成员"
	
	auto func2 = [pw = std::make_unique<Widget32>()]{ return pw->isValidated() && pw->isArchived(); }; // C++14, 闭包类数据成员可以由std::make_unique直接初始化
	auto func7 = std::bind([](const std::unique_ptr<Widget32>& pw) {return pw->isValidated() && pw->isArchived(); }, std::make_unique<Widget32>()); // C++11

	auto func3 = IsValAndArch(std::make_unique<Widget32>()); // C++11

	auto func4 = [data32 = std::move(data32)]{ /*use of data*/ }; // C++14
	auto func5 = std::bind([](const std::vector<double>& data32) { /*use of data*/ }, std::move(data32)); // 初始化捕获的C++11模拟
	auto func6 = std::bind([](std::vector<double>& data32) mutable {/*use of data*/}, std::move(data32)); // 初始化捕获的C++11模拟，for mutable lambda

	return 0;
}

/////////////////////////////////////////////////
int test_item_33()
{
	auto f1 = [](auto x) { return func33(normalize(x)); };
	auto f2 = [](auto&& param) { return func33(normalize(std::forward<decltype(param)>(param))); };
	auto f3 = [](auto&&... param) { return func33(normalize(std::forward<decltype(param)>(param)...)); };

	return 0;
}

/////////////////////////////////////////////////
using Time = std::chrono::steady_clock::time_point; // typedef for a point in time
enum class Sound { Beep, Siren, Whistle };
using Duration = std::chrono::steady_clock::duration; // typedef for a length of time

void setAlarm(Time t, Sound s, Duration d) {} // at time t, make sound s for duration d

int test_item_34()
{
	// setSoundL("L" for "lambda") is a function object allowing a sound to be specified for a 30-sec alarm to go off an hour after it's set
	auto setSoundL1 = [](Sound s) {
		using namespace std::chrono;
		setAlarm(steady_clock::now() + hours(1), s, seconds(30));
	};

	auto setSoundL2 = [](Sound s) {
		using namespace std::chrono;
		using namespace std::literals; // C++14
		setAlarm(steady_clock::now() + 1h, s, 30s); // C++14
	};

	setSoundL1(Sound::Siren);
	setSoundL2(Sound::Siren);

	using namespace std::chrono;
	using namespace std::literals; // C++14
	using namespace std::placeholders; // needed for use of "_1"
	auto setSoundB1 = std::bind(setAlarm, std::bind(std::plus<>(), steady_clock::now(), 1h), _1, 30s); // C++14
	auto setSoundB2 = std::bind(setAlarm, std::bind(std::plus<steady_clock::time_point>(), steady_clock::now(), hours(1)), _1, seconds(30)); // C++11

	setSoundB1(Sound::Siren);
	//setSoundB2(Sound::Siren);

	using SetAlarm3ParamType = void(*)(Time t, Sound s, Duration d);

	return 0;
}

/////////////////////////////////////////////////
int doAsyncWork() { return 1; }

int test_item_35()
{
	std::thread t(doAsyncWork);
	t.join();
	
	auto fut = std::async(doAsyncWork);

	return 0;
}

/////////////////////////////////////////////////
void f36()
{
	using namespace std::literals; // for C++14 duration suffixes
	std::this_thread::sleep_for(1s);
	//std::this_thread::sleep_for(std::chrono::seconds(1)); // C++11
}

//template<typename F, typename... Ts> // std::result_of: since C++11, deprecated in C++17, removed in C++20
//inline std::future<typename std::result_of<F(Ts...)>::type> reallyAsync(F&& f, Ts&&... params) // C++11, return future for asynchronous call to f(params...)
//{
//	return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(params)...);
//}

template<typename F, typename... Ts>
inline auto reallyAsync2(F&& f, Ts&&... params) // C++14
{
	return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(params)...);
}

int test_item_36()
{
	// 下面两个调用有着完全相同的意义
	auto fut1 = std::async(f36); // run f using default launch policy
	auto fut2 = std::async(std::launch::async | std::launch::deferred, f36); // run f either async or dererred

	auto fut = std::async(f36);
	using namespace std::literals;
	if (fut.wait_for(0s) == std::future_status::deferred) { // 如果任务被推迟了
		// use wait or get on fut to call f synchronously
	} else { // task isn't deferred
		while (fut.wait_for(100s) != std::future_status::ready) { // 不可能死循环(前提假设f36会结束)
			// task is neither deferred nor ready, so do concurrent work until it's ready
		}

		// fut is ready
	}

	auto fut3 = std::async(std::launch::async, f36); // launch f asynchronously

	//auto fut4 = reallyAsync(f36); // 以异步方式运行f，如果std::async会抛出异常reallyAsync也会抛出异常
	auto fut5 = reallyAsync2(f36);

	return 0;
}

/////////////////////////////////////////////////
void f37() {}

// 下面这个类允许调用者在销毁ThreadRAII对象(用于std::thread的RAII对象)时是调用join还是detach
class ThreadRAII {
public:
	enum class DtorAction { join, detach };

	// 构造函数只接受右值型别的std::thread
	ThreadRAII(std::thread&& t, DtorAction a) : action(a), t(std::move(t)) {}

	~ThreadRAII()
	{
		if (t.joinable()) {
			if (action == DtorAction::join) {
				t.join();
			} else {
				t.detach();
			}
		}
	}

	// support moving
	ThreadRAII(ThreadRAII&&) = default;
	ThreadRAII& operator=(ThreadRAII&&) = default;

	std::thread& get() { return t; }

private:
	DtorAction action;
	std::thread t;
};

int test_item_37()
{
	ThreadRAII trall(std::thread(f37), ThreadRAII::DtorAction::join);

	return 0;
}

/////////////////////////////////////////////////
class Widget38 { // Widget38 objects might block in their destructor
public: 

private:
	std::shared_future<double> fut;
};

int calcValue() { return 1; }

int test_item_38()
{
	// this container might block in its destructor, because one or more contained futures could refer to a shared state for a nondeferred task launched via std::async
	std::vector<std::future<void>> futs;

	std::packaged_task<int()> pt(calcValue); // 给calcValue加上包装使之能以异步方式运行
	auto fut = pt.get_future(); // get future for pt
	std::thread t(std::move(pt));
	t.join();
	
	return 0;
}

/////////////////////////////////////////////////
std::promise<void> p;

void react() {} // function for reacting task

void detect() // function for detecting task, 暂停线程一次
{
	std::thread t([] {p.get_future().wait(); react(); }); // create thread, suspend t until future is set

	// ... // here, t is suspended prior to call to react

	p.set_value(); // unsuspend t (and thus call react)

	// ... // do additional work

	t.join(); // make t unjoinable
}

void detect_multi() // now for multiple reacting tasks
{
	auto sf = p.get_future().share(); // sf's type is std::shared_future<void>
	std::vector<std::thread> vt; // container for reacting threads
	for (int i = 0; i < /*threadsToRun*/2; ++i) {
		vt.emplace_back([sf] {sf.wait(); react(); }); // wait on local copy of sf
	}

	// ... // detect hangs if this "…" code throws

	p.set_value(); // unsuspend all threads

	// ...

	for (auto& t : vt) { // make all threads unjoinable
		t.join();
	}
}

int test_item_39()
{
	return 0;
}

/////////////////////////////////////////////////
int test_item_40()
{
	std::atomic<int> ai(0); // initialize ai to 0
	ai = 10; // atomically set ai to 10
	std::cout << ai << std::endl; // atomically read ai's value
	++ai; // atomically increment ai to 11
	--ai; // atomically decrement ai to 10

	volatile int x = 0;
	auto y = x; // read x
	y = x; // read x again(can't be optimized away,不可以被优化掉)

	x = 10; // write x(can't be optimized away)
	x = 20; // write x again

	std::atomic<int> x2;
	std::atomic<int> y2(x2.load()); // read x2
	y2.store(x2.load()); // read x2 again

	register int z2 = x2.load(); // read x2 into register
	std::atomic<int> y2_(z2); // init y2_ with register value
	y2_.store(z2); // store register value into y2_

	volatile std::atomic<int> vai; // operations on vai are atomic and can't be optimized away

	return 0;
}

/////////////////////////////////////////////////
class Widget41 {
public:
	//// method 1: by-reference approaches
	//void addName(const std::string& newName) // 接受左值，对其实施拷贝
	//{
	//	names.push_back(newName);
	//}

	//void addName(std::string&& newName) // 接受右值，对其实施移动
	//{
	//	names.push_back(std::move(newName));
	//}

	//// method2: by-reference approaches
	//template<typename T>
	//void addName(T&& newName) // 万能引用，接受左值也接受右值，对左值实施拷贝，对右值实施移动
	//{
	//	names.push_back(std::forward<T>(newName));
	//}

	// method3: by-value approaches
	void addName(std::string newName) // 即接受左值也接受右值，对右值实施移动
	{
		names.push_back(std::move(newName));
	}

private:
	std::vector<std::string> names;
};

int test_item_41()
{
	Widget41 w;
	std::string name("Bart");
	w.addName(name); // call addName with lvalue
	w.addName(name + "Jenne"); // call addName with rvalue

	return 0;
}

/////////////////////////////////////////////////
int test_item_42()
{
	std::vector<std::string> vs;
	vs.push_back("xyzzy"); // 调用两次构造函数，一次析构函数
	vs.emplace_back("xyzzy"); // 调用一次构造函数，不涉及任何临时对象

	vs.emplace_back(50, 'x'); // insert std::string consisting of 50 'x' characters

	std::string queenOfDisco("Donna Summer");
	// 以下两条语句效果相同
	vs.push_back(queenOfDisco); // copy-construct queenOfDisco at end of vs
	vs.emplace_back(queenOfDisco); // copy-construct queenOfDisco at end of vs

	//std::regex r1 = nullptr; // 拷贝初始化(copy initialization),error, won't compile
	//std::regex r2(nullptr); // 直接初始化(direct initialization),can compile

	std::vector<std::regex> regexes;
	//regexes.emplace_back(nullptr); // 能编译，直接初始化允许使用接受指针的、带有explicit声明的std::regex构造函数
	//regexes.push_back(nullptr); // 不能编译，拷贝初始化禁止使用带指针的、explicit声明的std::regex构造函数

	return 0;
}

} // namespace effective_modern_cplusplus_
