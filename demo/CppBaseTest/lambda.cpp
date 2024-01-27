#include "lambda.hpp"
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <memory>
#include <array>
#include <thread>

// Blog: https://blog.csdn.net/fengbingchun/article/details/135888509
namespace {

class S {
public:
	void f()
	{
		int i{ 0 };

		auto l1 = [=] { use(i, x); }; // captures a copy of i and a copy of the this pointer
		i = 1; x = 1; l1();           // calls use(0, 1), as if i by copy and x by reference

		auto l2 = [i, this] { use(i, x); }; // same as above, made explicit
		i = 2; x = 2; l2();					// calls use(1, 2), as if i by copy and x by reference

		auto l3 = [&] { use(i, x); }; // captures i by reference and a copy of the this pointer
		i = 3; x = 2; l3();           // calls use(3, 2), as if i and x are both by reference

		auto l4 = [i, *this] { use(i, x); }; // makes a copy of *this, including a copy of x
		i = 4; x = 4; l4();					 // calls use(3, 2), as if i and x are both by copy
	}

private:
	int x{ 0 };

	void use(int i, int x) const { std::cout << "i = " << i << ", x = " << x << "\n"; }
};

struct MyObj {
	int value{ 123 };

	auto getValueCopy() {
		return [*this] { return value; }; // C++17
	}

	auto getValueRef() {
		return [this] { return value; }; // C++11
	}
};

class Data {
private:
	std::string name;

public:
	Data(const std::string& s) : name(s) { }

	auto startThreadWithCopyOfThis() const {
		// 开启并返回新线程,新线程将在3秒后使用this:
		std::thread t([*this] {
			using namespace std::literals;
			std::this_thread::sleep_for(3s);
			std::cout << "name: " << name << "\n";
		});

		return t;
	}
};


constexpr int addOne(int n) { return [n] { return n + 1; }(); } // reference: https://stackoverflow.com/questions/12662688/parentheses-at-the-end-of-a-c11-lambda-expression
constexpr auto addOne2(int n) { return [n] { return n + 1; }; } // 注:上下两条语句的区别
constexpr auto addOne3 = [](int n) { return n + 1; };

auto squared = [](auto val) { // 自从C++17起隐式constexpr
	constexpr int x{ 10 };
	return val * x;
};

// 为了确定一个lambda是否能用于编译期,你可以将它声明为constexpr
auto squared3 = [](auto val) constexpr { return val * val; }; // 自从C++17起
auto squared3i = [](int val) constexpr -> int { return val * val; };

// 自从C++17起,如果lambda被显式或隐式地定义为constexpr,那么生成的函数调用运算符将自动是constexpr
auto squared1 = [](auto val) constexpr { return val * val; }; // 编译期lambda调用
constexpr auto squared2 = [](auto val) { return val * val; }; // 编译期初始化squared2
constexpr auto squared4 = [](auto val) constexpr { return val * val; };

} // namespace

int test_lambda_17_constexpr()
{
	// 如果函数调用operator(或generic lambda的特化)为constexpr,则此函数为constexpr
	auto Fwd = [](int(*fp)(int), auto a) { return fp(a); };
	auto C = [](auto a) { return a; };
	static_assert(Fwd(C, 3) == 3);


	// reference: https://github.com/AnthonyCalandra/modern-cpp-features#constexpr-lambda
	auto identity = [](int n) constexpr { return n; };
	static_assert(identity(123) == 123);

	constexpr auto add = [](int x, int y) {
		auto L = [=] { return x; };
		auto R = [=] { return y; };
		return [=] { return L() + R(); };
	};
	static_assert(add(1, 2)() == 3);


	static_assert(addOne(1) == 2);
	static_assert(addOne2(1)() == 2);
	std::cout << "addOne:" << addOne(1) << ", addOne2: " << addOne2(1)() << "\n"; // addOne:2, addOne2: 2
	static_assert(addOne3(1) == 2);

	int v = [](int x, int y) { return x + y; }(5, 4);
	std::cout << "v: " << v << "\n"; // v: 9

	// 将一个lambda表达式嵌套在另一个lambda表达式中
	int v2 = [](int x) { return [](int y) { return y * 2; }(x)+3; }(5);
	std::cout << "v2: " << v2 << "\n"; // v2: 13


	// reference: https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
	// 当函数对象需要去修改通过副本传入的变量时,表达式必须用mutable修饰
	int m = 0, n = 0;
	[&, n](int a) mutable { m = ++n + a; }(4);
	std::cout << "m:" << m << ", n:" << n << "\n"; // m:5, n:0


	// 如果lambda的结果满足constexpr函数的要求,则它是隐式constexpr
	auto answer = [](int n) {
		return 32 + n;
	};

	constexpr int response = answer(10);
	static_assert(response == 42);

	// reference: https://github.com/MeouSker77/Cpp17/blob/master/markdown/src/ch06.md
	std::array<int, squared(5)> arr;  // 自从C++17起 => std::array<int, 50>


	// 如果lambda隐式或显式为constexpr,则转换为函数指针会生成constexpr函数
	auto Increment = [](int n) {
		return n + 1;
	};

	constexpr int(*inc)(int) = Increment;

	return 0;
}

int test_lambda_17_this()
{
	//reference: https://en.cppreference.com/w/cpp/language/lambda
	S s;
	s.f();


	// reference: https://github.com/AnthonyCalandra/modern-cpp-features#lambda-capture-this-by-value
	MyObj mo;
	auto valueCopy = mo.getValueCopy();
	auto valueRef = mo.getValueRef();
	std::cout << "valueCopy: " << valueCopy() << ", valueRef: " << valueRef() << "\n"; // valueCopy: 123, valueRef: 123

	mo.value = 321;
	valueCopy();
	valueRef();
	std::cout << "valueCopy: " << valueCopy() << ", valueRef: " << valueRef() << "\n"; // valueCopy: 123, valueRef: 321


	std::thread t;
	{
		Data d{ "c1" };
		t = d.startThreadWithCopyOfThis();
	}   // d不再有效
	t.join();

	return 0;
}


/////////////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/130659435
namespace {

//void print_elements(auto& C) // windows need to c++20
template<typename T>
void print_elements(const T& C)
{
	for (const auto& e : C)
		std::cout << e << " ";
	std::cout << "\n";
}

int factory(int i) { return i * 10; }

}

int test_lambda_14_1()
{
	// reference: https://www.geeksforgeeks.org/generalized-lambda-expressions-c14/
	/* Under the hood, the C++ implementation uses the closure type's operator() to overload a template function
	struct sum {
		template<typename T1, typename T2>
		auto operator()(T1 a, T2 b) const { return (a + b); }
	};
	*/
	auto sum = [](auto a, auto b) {
		return (a + b);
	};

	std::cout << "int sum:" << sum(10, 20) << "\n";
	std::cout << "float sum:" << sum(1.2f, 2.3f) << "\n";
	std::cout << "float sum:" << sum(10, 1.5f) << "\n";
	std::cout << "string sum:" << sum(std::string("csdn addr:"), std::string("https://blog.csdn.net/fengbingchun")) << "\n";


	auto greater = [](auto a, auto b) -> bool {
		return (a > b);
	};

	std::vector<int> vi = { 1, 4, 2, 6 };
	std::vector<float> vf = { 4.62f, 161.3f, 62.26f, 13.4f };
	std::vector<std::string> vs = { "Tom", "Harry", "Ram", "Shyam" };

	std::sort(vi.begin(), vi.end(), greater);
	std::sort(vf.begin(), vf.end(), greater);
	std::sort(vs.begin(), vs.end(), greater);

	print_elements(vi);
	print_elements(vf);
	print_elements(vs);


	std::vector<std::vector<int>> v = { {7, 8}, {1, 2}, {3, 7}, {4, 5} };
	std::sort(v.begin(), v.end(), [](std::vector<int>& a, std::vector<int>& b) {
		return (a[1] < b[1]);
	});

	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v[0].size(); ++j) {
			std::cout << v[i][j] << " ";
		}
		std::cout << "\n";
	}

	return 0;
}

int test_lambda_14_2()
{
	// reference: https://github.com/AnthonyCalandra/modern-cpp-features#lambda-capture-initializers
	auto f = [x = factory(2)] { return x; };
	std::cout << "f:" << f() << "\n";


	auto generator = [x = 0]() mutable {
		// this would not compile without 'mutable' as we are modifying x on each call
		return x++;
	};

	auto a = generator();
	auto b = generator();
	auto c = generator();
	std::cout << "a:" << a << ",b:" << b << ",c:" << c << "\n";


	auto p = std::make_unique<int>(1);
	//auto task1 = [=] { *p = 5; }; // ERROR: std::unique_ptr cannot be copied
	auto task2 = [p = std::move(p)] { *p = 5; return *p; }; // OK: p is move-constructed into the closure object
	// the original p is empty after task2 is created
	if (!p)
		std::cout << "p is empty" << "\n";
	std::cout << "task2:" << task2() << "\n";


	auto x = 2;
	auto f2 = [&r = x, x = x * 10] {
		++r;
		return r + x;
	};
	std::cout << "f2:" << f2() << ",x:" << x << "\n";

	return 0;
}


// Blog: http://blog.csdn.net/fengbingchun/article/details/52653313

///////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/lambda
int test_lambda1()
{
	/*
	[]		Capture nothing (or, a scorched earth strategy?)
	[&]		Capture any referenced variable by reference
	[=]		Capture any referenced variable by making a copy
	[=, &foo]	Capture any referenced variable by making a copy, but capture variable foo by reference
	[bar]		Capture bar by making a copy; don't copy anything else
	[this]		Capture the this pointer of the enclosing class
	*/
	int a = 1, b = 1, c = 1;

	auto m1 = [a, &b, &c]() mutable {
		auto m2 = [a, b, &c]() mutable {
			std::cout << a << b << c << '\n';
			a = 4; b = 4; c = 4;
		};
		a = 3; b = 3; c = 3;
		m2();
	};

	a = 2; b = 2; c = 2;

	m1();                             // calls m2() and prints 123
	std::cout << a << b << c << '\n'; // prints 234

	return 0;
}

///////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/lambda
int test_lambda2()
{
	std::vector<int> c = { 1, 2, 3, 4, 5, 6, 7 };
	int x = 5;
	c.erase(std::remove_if(c.begin(), c.end(), [x](int n) { return n < x; }), c.end());

	std::cout << "c: ";
	std::for_each(c.begin(), c.end(), [](int i){ std::cout << i << ' '; });
	std::cout << '\n';

	// the type of a closure cannot be named, but can be inferred with auto
	auto func1 = [](int i) { return i + 4; };
	std::cout << "func1: " << func1(6) << '\n';

	// like all callable objects, closures can be captured in std::function
	// (this may incur unnecessary overhead)
	std::function<int(int)> func2 = [](int i) { return i + 4; };
	std::cout << "func2: " << func2(6) << '\n';

	return 0;
}

///////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/dd293608.aspx
int test_lambda3()
{
	// The following example contains a lambda expression that explicitly captures the variable n by value
	// and implicitly captures the variable m by reference:
	int m = 0;
	int n = 0;
	[&, n](int a) mutable { m = ++n + a; }(4);

	// Because the variable n is captured by value, its value remains 0 after the call to the lambda expression.
	// The mutable specification allows n to be modified within the lambda.
	std::cout << m << std::endl << n << std::endl;

	return 0;
}

//////////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/dd293608.aspx
template <typename C>
void print(const std::string& s, const C& c)
{
	std::cout << s;

	for (const auto& e : c) {
		std::cout << e << " ";
	}

	std::cout << std::endl;
}

void fillVector(std::vector<int>& v)
{
	// A local static variable.
	static int nextValue = 1;

	// The lambda expression that appears in the following call to
	// the generate function modifies and uses the local static 
	// variable nextValue.
	generate(v.begin(), v.end(), [] { return nextValue++; });
	//WARNING: this is not thread-safe and is shown for illustration only
}

int test_lambda4()
{
	// The number of elements in the vector.
	const int elementCount = 9;

	// Create a vector object with each element set to 1.
	std::vector<int> v(elementCount, 1);

	// These variables hold the previous two elements of the vector.
	int x = 1;
	int y = 1;

	// Sets each element in the vector to the sum of the 
	// previous two elements.
	generate_n(v.begin() + 2,
		elementCount - 2,
		[=]() mutable throw() -> int { // lambda is the 3rd parameter
		// Generate current value.
		int n = x + y;
		// Update previous two values.
		x = y;
		y = n;
		return n;
	});
	print("vector v after call to generate_n() with lambda: ", v);

	// Print the local variables x and y.
	// The values of x and y hold their initial values because 
	// they are captured by value.
	std::cout << "x: " << x << " y: " << y << std::endl;

	// Fill the vector with a sequence of numbers
	fillVector(v);
	print("vector v after 1st call to fillVector(): ", v);
	// Fill the vector with the next sequence of numbers
	fillVector(v);
	print("vector v after 2nd call to fillVector(): ", v);

	return 0;
}

/////////////////////////////////////////////////
// reference: http://blogorama.nerdworks.in/somenotesonc11lambdafunctions/

template<typename T>
std::function<T()> makeAccumulator(T& val, T by) {
	return [=, &val]() {
		return (val += by);
	};
}

int test_lambda5()
{
	int val = 10;
	auto add5 = makeAccumulator(val, 5);
	std::cout << add5() << std::endl;
	std::cout << add5() << std::endl;
	std::cout << add5() << std::endl;
	std::cout << std::endl;

	val = 100;
	auto add10 = makeAccumulator(val, 10);
	std::cout << add10() << std::endl;
	std::cout << add10() << std::endl;
	std::cout << add10() << std::endl;

	return 0;
}

////////////////////////////////////////////////////////
// reference: http://blogorama.nerdworks.in/somenotesonc11lambdafunctions/
class Foo_lambda {
public:
	Foo_lambda() {
		std::cout << "Foo_lambda::Foo_lambda()" << std::endl;
	}

	Foo_lambda(const Foo_lambda& f) {
		std::cout << "Foo_lambda::Foo_lambda(const Foo_lambda&)" << std::endl;
	}

	~Foo_lambda() {
		std::cout << "Foo_lambda~Foo_lambda()" << std::endl;
	}
};

int test_lambda6()
{
	Foo_lambda f;
	auto fn = [f]() { std::cout << "lambda" << std::endl; };
	std::cout << "Quitting." << std::endl;
	return 0;
}

template<typename Cal>
static void display(Cal cal)
{
	fprintf(stderr, "start\n");
	cal();
}

int test_lambda7()
{
	int num { 1 };
	// create callback
	auto fun = [&](){
		if (num % 5 == 0) {
			fprintf(stderr, "****** reset ******\n");
			fprintf(stderr, "num = %d\n", num);

			num = 0;
		} else {
			fprintf(stderr, "++++++ continue ++++++\n");
			fprintf(stderr, "num = %d\n", num);
		}

		num++;
	};

	for (int i = 0; i < 20; i++) {
		fprintf(stderr, "========= i = %d\n", i);
		display(fun);
	}

	return 0;
}
