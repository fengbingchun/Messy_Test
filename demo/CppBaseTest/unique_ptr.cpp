#include "unique_ptr.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52203664

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
