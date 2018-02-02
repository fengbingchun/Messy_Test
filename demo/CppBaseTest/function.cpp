#include "function.hpp"
#include <iostream>
#include <string>
#include <functional>
#include <vector>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52562918

///////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/utility/functional/function
struct Foo {
	Foo(int num) : num_(num) {}
	void print_add(int i) const { std::cout << num_ + i << '\n'; }
	int num_;
};

void print_num(int i)
{
	std::cout << i << '\n';
}

struct PrintNum {
	void operator()(int i) const
	{
		std::cout << i << '\n';
	}
};

int test_function1()
{
	// store a free function
	std::function<void(int)> f_display = print_num;
	f_display(-9);

	// store a lambda
	std::function<void()> f_display_42 = []() { print_num(42); };
	f_display_42();

	// store the result of a call to std::bind
	std::function<void()> f_display_31337 = std::bind(print_num, 31337);
	f_display_31337();

	// store a call to a member function
	//std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
	const Foo foo(314159);
	//f_add_display(foo, 1);

	// store a call to a data member accessor
	//std::function<int(Foo const&)> f_num = &Foo::num_;
	//std::cout << "num_: " << f_num(foo) << '\n';

	// store a call to a member function and object
	using std::placeholders::_1;
	std::function<void(int)> f_add_display2 = std::bind(&Foo::print_add, foo, _1);
	f_add_display2(2);

	// store a call to a member function and object ptr
	std::function<void(int)> f_add_display3 = std::bind(&Foo::print_add, &foo, _1);
	f_add_display3(3);

	// store a call to a function object
	std::function<void(int)> f_display_obj = PrintNum();
	f_display_obj(18);

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://oopscenities.net/2012/02/24/c11-stdfunction-and-stdbind/
void execute(const std::vector<std::function<void()>>& fs)
{
	for (auto& f : fs)
		f();
}

void plain_old_func()
{
	std::cout << "I'm an old plain function" << std::endl;
}

class functor
{
public:
	void operator()() const
	{
		std::cout << "I'm a functor" << std::endl;
	}
};

int test_function2()
{
	std::vector<std::function<void()>> x;
	x.push_back(plain_old_func);

	functor functor_instance;
	x.push_back(functor_instance);
	x.push_back([]()
	{
		std::cout << "HI, I'm a lambda expression" << std::endl;
	});

	execute(x);

	return 0;
}

///////////////////////////////////////////////////////
// reference: http://shaharmike.com/cpp/lambdas-and-functions/
void global_f() {
	std::cout << "global_f()" << std::endl;
}

struct Functor {
	void operator()() { std::cout << "Functor" << std::endl; }
};

int test_function3()
{
	std::function<void()> f;
	std::cout << "sizeof(f) == " << sizeof(f) << std::endl;

	f = global_f;
	f();

	f = [](){ std::cout << "Lambda" << std::endl; };
	f();

	Functor functor;
	f = functor;
	f();

	return 0;
}
