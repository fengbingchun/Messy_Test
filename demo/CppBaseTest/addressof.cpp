#include "addressof.hpp"
#include <iostream>
#include <memory> // std::addressof

// Blog: http://blog.csdn.net/fengbingchun/article/details/70406274

////////////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/memory/addressof
template<class T>
struct Ptr {
	T* pad; // add pad to show difference between 'this' and 'data'
	T* data;
	Ptr(T* arg) : pad(nullptr), data(arg)
	{
		std::cout << "Ctor this = " << this << std::endl;
	}

	~Ptr() { delete data; }
	T** operator&() { return &data; }
};

template<class T>
void f(Ptr<T>* p)
{
	std::cout << "Ptr   overload called with p = " << p << '\n';
}

void f(int** p)
{
	std::cout << "int** overload called with p = " << p << '\n';
}

int test_addressof_1()
{
	Ptr<int> p(new int(42));
	f(&p);                 // calls int** overload
	f(std::addressof(p));  // calls Ptr<int>* overload, (= this)

	return 0;
}

////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/memory/addressof/
struct unreferenceable {
	int x;
	unreferenceable* operator&() { return nullptr; }
};

void print(unreferenceable* m) {
	if (m) std::cout << m->x << '\n';
	else std::cout << "[null pointer]\n";
}

int test_addressof_2()
{
	void(*pfn)(unreferenceable*) = &print; // void(*pfn)(unreferenceable*); pfn = &print;

	unreferenceable val{ 10 };
	unreferenceable* foo = &val;
	unreferenceable* bar = std::addressof(val);

	(*pfn)(foo);   // prints [null pointer]
	(*pfn)(bar);   // prints 10

	return 0;
}

/////////////////////////////////////////////////////////
// reference: http://cppisland.com/?p=414
class Buffer
{
private:
	static const size_t buffer_size = 256;
	int bufferId;
	char buffer[buffer_size];

public:
	Buffer(int bufferId_) : bufferId(bufferId_) {}
	Buffer* operator&() { return reinterpret_cast<Buffer*> (&buffer); }  //BAD practice, only for illustration!
};

template<typename T>
void getAddress(T t)
{
	std::cout << "Address returned by & operator: " << std::ios::hex << &t << "\n";
	std::cout << "Address returned by addressof: " << std::ios::hex << std::addressof(t) << "\n";
}

int test_addressof_3()
{
	int a = 3;
	fprintf(stderr, "a &: %p, address of: %p\n", &a, std::addressof(a));

	Buffer b(1);
	std::cout << "Getting the address of a Buffer type: \n";
	getAddress(b);

	return 0;
}

/////////////////////////////////////////////////////////
// reference: https://wizardforcel.gitbooks.io/beyond-stl/content/38.html
class codebreaker {
public:
	int operator&() const {
		return 13;
	}
};

int test_addressof_4()
{
	codebreaker c;

	std::cout << "&c: " << (&c) << '\n';
	std::cout << "addressof(t): " << std::addressof(c) << '\n';

	return 0;
}
