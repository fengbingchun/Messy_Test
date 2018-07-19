#include "unique_ptr.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52203664

namespace unique_ptr_ {

///////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/memory/unique_ptr
struct Foo
{
	Foo()      { std::cout << "Foo::Foo\n"; }
	~Foo()     { std::cout << "Foo::~Foo\n"; }
	void bar() { std::cout << "Foo::bar\n"; }
};

void f(const Foo &)
{
	std::cout << "f(const Foo&)\n";
}

int test_unique_ptr1()
{
	std::unique_ptr<Foo> p1(new Foo);  // p1 owns Foo
	if (p1) p1->bar();

	{
		std::unique_ptr<Foo> p2(std::move(p1));  // now p2 owns Foo
		f(*p2);

		p1 = std::move(p2);  // ownership returns to p1
		std::cout << "destroying p2...\n";
	}

	if (p1) p1->bar();

	// Foo instance is destroyed when p1 goes out of scope

	return 0;
}

//////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/memory/unique_ptr/unique_ptr/
int test_unique_ptr2()
{
	std::default_delete<int> d;
	std::unique_ptr<int> u1;
	std::unique_ptr<int> u2(nullptr);
	std::unique_ptr<int> u3(new int);
	std::unique_ptr<int> u4(new int, d);
	std::unique_ptr<int> u5(new int, std::default_delete<int>());
	std::unique_ptr<int> u6(std::move(u5));
	std::unique_ptr<int> u7(std::move(u6));
	std::unique_ptr<int> u8(std::auto_ptr<int>(new int));

	std::cout << "u1: " << (u1 ? "not null" : "null") << '\n';
	std::cout << "u2: " << (u2 ? "not null" : "null") << '\n';
	std::cout << "u3: " << (u3 ? "not null" : "null") << '\n';
	std::cout << "u4: " << (u4 ? "not null" : "null") << '\n';
	std::cout << "u5: " << (u5 ? "not null" : "null") << '\n';
	std::cout << "u6: " << (u6 ? "not null" : "null") << '\n';
	std::cout << "u7: " << (u7 ? "not null" : "null") << '\n';
	std::cout << "u8: " << (u8 ? "not null" : "null") << '\n';

	return 0;
}

//////////////////////////////////////////////////////
// reference: http://eli.thegreenplace.net/2012/06/20/c11-using-unique_ptr-with-standard-library-containers
struct Foo_0 {
	Foo_0() { std::cerr << "Foo_0 [" << this << "] constructed\n"; }
	virtual ~Foo_0() { std::cerr << "Foo_0 [" << this << "] destructed\n"; }
};

void sink(std::unique_ptr<Foo_0> p) {
	std::cerr << "Sink owns Foo_0 [" << p.get() << "]\n";
}

std::unique_ptr<Foo_0> source() {
	std::cerr << "Creating Foo_0 in source\n";
	return std::unique_ptr<Foo_0>(new Foo_0);
}

int test_unique_ptr3()
{
	std::cerr << "Calling source\n";
	std::unique_ptr<Foo_0> pmain = source();  // Can also be written as
	// auto pmain = source();

	std::cerr << "Now pmain owns Foo [" << pmain.get() << "]\n";
	std::cerr << "Passing it to sink\n";
	// sink(pmain);                    // ERROR! can't copy unique_ptr
	sink(move(pmain));              // OK: can move it!

	std::cerr << "Main done\n";
	return 0;
}

////////////////////////////////////////////////////
// reference: http://www.codeguru.com/cpp/article.php/c17775/The-Smart-Pointer-That-Makes-Your-C-Applications-Safer--stduniqueptr.htm
void func(int*)
{

}

int test_unique_ptr4()
{
	// default construction
	std::unique_ptr<int> up; //creates an empty object

	// initialize with an argument
	std::unique_ptr<int> uptr(new int(3));
	double *pd = new double;
	std::unique_ptr<double> uptr2(pd);
	// overloaded * and ->
	*uptr2 = 23.5;
	std::unique_ptr<std::string> ups(new std::string("hello"));
	int len = ups->size();

	// Reset() releases the owned resource and optionally acquires a new resource:
	uptr2.reset(new double); //delete pd and acquire a new pointer
	uptr2.reset(); //delete the pointer acquired by the previous reset() call

	// If you need to access the owned pointer directly use get()
	func(uptr.get());

	// Unique_ptr has implicit conversion to bool.
	// This lets you use unique_ptr object in Boolean expressions such as this:
	if (ups) //implicit conversion to bool
		std::cout << *ups << std::endl;
	else
		std::cout << "an empty smart pointer" << std::endl;

	// Array Support: Unique_ptr can store arrays as well.
	// A unique_ptr that owns an array defines an overloaded operator [].
	// Obviously, the * and -> operators are not available.
	// Additionally, the default deleter calls delete[] instead of delete:
	std::unique_ptr<int[]> arrup(new int[5]);
	arrup[0] = 5;
	// std::cout << *arrup << std::endl; //error, operator * not defined 

	// Compatibility with Containers and Algorithms
	// You can safely store unique_ptr in Standard Library containers and let algorithms manipulate sequences of unique_ptr objects.
	std::vector<std::unique_ptr<int>> vi;
	vi.push_back(std::unique_ptr<int>(new int(0)));  // populate vector
	vi.push_back(std::unique_ptr<int>(new int(3)));
	vi.push_back(std::unique_ptr<int>(new int(2)));
	std::sort(vi.begin(), vi.end());  // result: {0, 2, 3}

	return 0;
}

//////////////////////////////////////////////////////////////////
template <typename T>
class Add {
public:
	T add_sub(T a, T b)
	{
		return (a + b) * (a - b);
	}
};


int test_unique_ptr5()
{
	std::unique_ptr<Add<int>> tt(new Add<int>());
	int a{ 10 }, b{ 5 };

	std::cout << tt->add_sub(a, b) << std::endl;

	return 0;
}

//////////////////////////////////////////////////////////////////
int test_unique_ptr6()
{
	std::unique_ptr<int[]> tmp(new int[100]);
	std::for_each(tmp.get(), tmp.get() + 100, [](int& n) {n = 66; });
	std::cout << tmp[99] << std::endl;

	return 0;
}

///////////////////////////////////////////////////////////////////////
// reference: https://en.cppreference.com/w/cpp/memory/unique_ptr
struct B {
	virtual void bar() { std::cout << "B::bar\n"; }
	virtual ~B() = default;
};
struct D : B
{
	D() { std::cout << "D::D\n"; }
	~D() { std::cout << "D::~D\n"; }
	void bar() override { std::cout << "D::bar\n"; }
};

// a function consuming a unique_ptr can take it by value or by rvalue reference
std::unique_ptr<D> pass_through(std::unique_ptr<D> p)
{
	p->bar();
	return p;
}

void close_file(std::FILE* fp) { std::fclose(fp); }

int test_unique_ptr7()
{
	std::cout << "unique ownership semantics demo\n";
	{
		auto p = std::make_unique<D>(); // p is a unique_ptr that owns a D
		auto q = pass_through(std::move(p));
		assert(!p); // now p owns nothing and holds a null pointer
		q->bar();   // and q owns the D object
	} // ~D called here

	std::cout << "Runtime polymorphism demo\n";
	{
		std::unique_ptr<B> p = std::make_unique<D>(); // p is a unique_ptr that owns a D
		// as a pointer to base
		p->bar(); // virtual dispatch

		std::vector<std::unique_ptr<B>> v;  // unique_ptr can be stored in a container
		v.push_back(std::make_unique<D>());
		v.push_back(std::move(p));
		v.emplace_back(new D);
		for (auto& p : v) p->bar(); // virtual dispatch
	} // ~D called 3 times

	std::cout << "Custom deleter demo\n";
	std::ofstream("demo.txt") << 'x'; // prepare the file to read
	{
		std::unique_ptr<std::FILE, decltype(&close_file)> fp(std::fopen("demo.txt", "r"), &close_file);
		if (fp) // fopen could have failed; in which case fp holds a null pointer
			std::cout << (char)std::fgetc(fp.get()) << '\n';
	} // fclose() called here, but only if FILE* is not a null pointer
	// (that is, if fopen succeeded)

	std::cout << "Custom lambda-expression deleter demo\n";
	{
		std::unique_ptr<D, std::function<void(D*)>> p(new D, [](D* ptr)
		{
			std::cout << "destroying from a custom deleter...\n";
			delete ptr;
		});  // p owns D
		p->bar();
	} // the lambda above is called and D is destroyed

	std::cout << "Array form of unique_ptr demo\n";
	{
		std::unique_ptr<D[]> p{ new D[3] };
	} // calls ~D 3 times

	return 0;
}

/////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/memory/unique_ptr/~unique_ptr/
int test_unique_ptr8()
{
	auto deleter = [](int*p){
		delete p;
		std::cout << "[deleter called]\n";
	};

	std::unique_ptr<int, decltype(deleter)> foo(new int, deleter);

	std::cout << "foo " << (foo ? "is not" : "is") << " empty\n";

	return 0;                        // [deleter called]
}

/////////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/memory/unique_ptr/get_deleter/
class state_deleter {  // a deleter class with state
	int count_;
public:
	state_deleter() : count_(0) {}
	template <class T>
	void operator()(T* p) {
		std::cout << "[deleted #" << ++count_ << "]\n";
		delete p;
	}
};

int test_unique_ptr9()
{
	state_deleter del;

	std::unique_ptr<int> p;   // uses default deleter

	// alpha and beta use independent copies of the deleter:
	std::unique_ptr<int, state_deleter> alpha(new int);
	std::unique_ptr<int, state_deleter> beta(new int, alpha.get_deleter());

	// gamma and delta share the deleter "del" (deleter type is a reference!):
	std::unique_ptr<int, state_deleter&> gamma(new int, del);
	std::unique_ptr<int, state_deleter&> delta(new int, gamma.get_deleter());

	std::cout << "resetting alpha..."; alpha.reset(new int);
	std::cout << "resetting beta..."; beta.reset(new int);
	std::cout << "resetting gamma..."; gamma.reset(new int);
	std::cout << "resetting delta..."; delta.reset(new int);

	std::cout << "calling gamma/delta deleter...";
	gamma.get_deleter()(new int);

	alpha.get_deleter() = state_deleter();  // a brand new deleter for alpha

	// additional deletions when unique_ptr objects reach out of scope
	// (in inverse order of declaration)

	return 0;
}

//////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/memory/unique_ptr/operator=/
int test_unique_ptr10()
{
	std::unique_ptr<int> foo;
	std::unique_ptr<int> bar;

	foo = std::unique_ptr<int>(new int(101));  // rvalue

	bar = std::move(foo);                       // using std::move

	std::cout << "foo: ";
	if (foo) std::cout << *foo << '\n'; else std::cout << "empty\n";

	std::cout << "bar: ";
	if (bar) std::cout << *bar << '\n'; else std::cout << "empty\n";

	return 0;
}

/////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/memory/unique_ptr/release/
int test_unique_ptr11()
{
	std::unique_ptr<int> auto_pointer(new int);
	int * manual_pointer;

	*auto_pointer = 10;

	manual_pointer = auto_pointer.release();
	// (auto_pointer is now empty)

	std::cout << "manual_pointer points to " << *manual_pointer << '\n';

	delete manual_pointer;

	return 0;

}

///////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/memory/unique_ptr/swap/
int test_unique_ptr12()
{
	std::unique_ptr<int> foo(new int(10)), foo2(new int(10));
	std::unique_ptr<int> bar(new int(20)), bar2(new int(20));

	foo.swap(bar);
	std::cout << "foo: " << *foo << '\n';
	std::cout << "bar: " << *bar << '\n';

	std::swap(foo2, bar2);
	std::cout << "foo2: " << *foo2 << '\n';
	std::cout << "bar2: " << *bar2 << '\n';

	return 0;
}

////////////////////////////////////////////////////////////////
void math_add(int* a)
{
	int b = ++(*a);
	delete a;
	fprintf(stdout, "add operation: %d\n", b);
}

void math_subtract(int* a)
{
	int b = --(*a);
	delete a;
	fprintf(stdout, "subtraction operation: %d\n", b);
}

int test_unique_ptr13()
{
	{
		std::unique_ptr<int, decltype(&math_add)> A(new int, &math_add);
		if (!A) {
			fprintf(stderr, "A is nullptr\n");
			return -1;
		}

		*A = 10;
	}

	{
		typedef std::unique_ptr<int, std::function<void(int*)>> Oper;

		Oper A(new int, math_add);
		*A = 10;

		Oper B(new int, math_subtract);
		*B = 10;
	}

	return 0;
}

} // namespace unique_ptr_
