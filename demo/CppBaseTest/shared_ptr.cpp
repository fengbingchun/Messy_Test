#include "shared_ptr.hpp"
#include <iostream>
#include <memory> // shared_ptr
#include <thread>
#include <chrono>
#include <mutex>
#include <algorithm>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52202007

//////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/memory/shared_ptr
struct Base
{
	Base() { std::cout << "  Base::Base()\n"; }
	// Note: non-virtual destructor is OK here
	~Base() { std::cout << "  Base::~Base()\n"; }
};

struct Derived : public Base
{
	Derived() { std::cout << "  Derived::Derived()\n"; }
	~Derived() { std::cout << "  Derived::~Derived()\n"; }
};

void thr(std::shared_ptr<Base> p)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::shared_ptr<Base> lp = p; // thread-safe, even though the shared use_count is incremented
	{
		static std::mutex io_mutex;
		std::lock_guard<std::mutex> lk(io_mutex);
		std::cout << "local pointer in a thread:\n"
			<< "  lp.get() = " << lp.get()
			<< ", lp.use_count() = " << lp.use_count() << '\n';
	}
}

int test_shared_ptr1()
{
	std::shared_ptr<Base> p = std::make_shared<Derived>();

	std::cout << "Created a shared Derived (as a pointer to Base)\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n';
	std::thread t1(thr, p), t2(thr, p), t3(thr, p);
	p.reset(); // release ownership from main
	std::cout << "Shared ownership between 3 threads and released\n"
		<< "ownership from main:\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n';
	t1.join(); t2.join(); t3.join();
	std::cout << "All threads completed, the last one deleted Derived\n";

	return 0;
}

///////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/memory/shared_ptr/shared_ptr/
int test_shared_ptr2()
{
	struct C { int* data; };

	// shared_ptr constructor example
	std::shared_ptr<int> p1;
	std::shared_ptr<int> p2(nullptr);
	std::shared_ptr<int> p3(new int);
	std::shared_ptr<int> p4(new int, std::default_delete<int>());
	std::shared_ptr<int> p5(new int, [](int* p){delete p; }, std::allocator<int>());
	std::shared_ptr<int> p6(p5);
	std::shared_ptr<int> p7(std::move(p6));
	std::shared_ptr<int> p8(std::unique_ptr<int>(new int));
	std::shared_ptr<C> obj(new C);
	std::shared_ptr<int> p9(obj, obj->data);

	std::cout << "use_count:\n";
	std::cout << "p1: " << p1.use_count() << '\n'; // 0
	std::cout << "p2: " << p2.use_count() << '\n'; // 0
	std::cout << "p3: " << p3.use_count() << '\n'; // 1
	std::cout << "p4: " << p4.use_count() << '\n'; // 1
	std::cout << "p5: " << p5.use_count() << '\n'; // 2
	std::cout << "p6: " << p6.use_count() << '\n'; // 0
	std::cout << "p7: " << p7.use_count() << '\n'; // 2
	std::cout << "p8: " << p8.use_count() << '\n'; // 1
	std::cout << "p9: " << p9.use_count() << '\n'; // 2

	return 0;
}

//////////////////////////////////////////////////////////
// reference: https://oopscenities.net/2013/10/06/smart-pointers-part-4-shared_ptr/
class Integer
{
	int n;
public:
	Integer(int n) : n(n) { }
	~Integer() { printf("Deleting %d\n", n); }
	int get() const { return n; }
};

int test_shared_ptr3()
{
	auto a = std::make_shared<Integer>(10);
	auto b = std::make_shared<Integer>(20);
	auto c = a;
	auto d = std::make_shared<Integer>(30);
	auto e = b;
	a = d;
	b = std::make_shared<Integer>(40);
	auto f = c;
	b = f;

	printf("%d\n", a->get());
	printf("%d\n", b->get());
	printf("%d\n", c->get());
	printf("%d\n", d->get());
	printf("%d\n", e->get());
	printf("%d\n", f->get());

	return 0;
}

//////////////////////////////////////////////
// reference: http://www.linux-magazin.de/Ausgaben/2013/04/C-11
struct MyInt{
	MyInt(int v) :val(v){
		std::cout << "  Hello: " << val << std::endl;
	}
	~MyInt(){
		std::cout << "  Good Bye: " << val << std::endl;
	}
	int val;
};

int test_shared_ptr4()
{
	std::shared_ptr<MyInt> sharPtr(new MyInt(1998));
	std::cout << "    My value: " << sharPtr->val << std::endl;
	std::cout << "sharedPtr.use_count(): " << sharPtr.use_count() << std::endl;

	{
		std::shared_ptr<MyInt> locSharPtr(sharPtr);
		std::cout << "locSharPtr.use_count(): " << locSharPtr.use_count() << std::endl;
	}
	std::cout << "sharPtr.use_count(): " << sharPtr.use_count() << std::endl;

	std::shared_ptr<MyInt> globSharPtr = sharPtr;
	std::cout << "sharPtr.use_count(): " << sharPtr.use_count() << std::endl;
	globSharPtr.reset();
	std::cout << "sharPtr.use_count(): " << sharPtr.use_count() << std::endl;

	sharPtr = std::shared_ptr<MyInt>(new MyInt(2011));

	return 0;
}

////////////////////////////////////////////////////////
// reference: http://www.linux-magazin.de/Ausgaben/2013/04/C-11
template <typename T>
struct Deleter{
	void operator()(T *ptr){
		++Deleter::count;
		delete ptr;
	}
	static int count;
};

template <typename T>
int Deleter<T>::count = 0;

typedef Deleter<int> IntDeleter;
typedef Deleter<double> DoubleDeleter;
typedef Deleter<MyInt> MyIntDeleter;

int test_shared_ptr5()
{
	{
		std::shared_ptr<int> sharedPtr1(new int(1998), IntDeleter());
		std::shared_ptr<int> sharedPtr2(new int(2011), IntDeleter());
		std::shared_ptr<double> sharedPtr3(new double(3.17), DoubleDeleter());
		std::shared_ptr<MyInt> sharedPtr4(new MyInt(2017), MyIntDeleter());
	}

	std::cout << "Deleted " << IntDeleter().count << " int values." << std::endl;
	std::cout << "Deleted " << DoubleDeleter().count << " double value." << std::endl;
	std::cout << "Deleted " << MyIntDeleter().count << " MyInt value." << std::endl;

	return 0;
}

////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/memory/shared_ptr/reset/
int test_shared_ptr_reset()
{
	std::shared_ptr<int> sp;  // empty

	sp.reset(new int);       // takes ownership of pointer
	*sp = 10;
	std::cout << *sp << '\n';

	sp.reset(new int);       // deletes managed object, acquires new pointer
	*sp = 20;
	std::cout << *sp << '\n';

	sp.reset();               // deletes managed object

	return 0;
}

//////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/memory/shared_ptr/get/
int test_shared_ptr_get()
{
	int* p = new int(10);
	std::shared_ptr<int> a(p);

	if (a.get() == p)
		std::cout << "a and p point to the same location\n";

	// three ways of accessing the same address:
	std::cout << *a.get() << "\n";
	std::cout << *a << "\n";
	std::cout << *p << "\n";

	return 0;
}

///////////////////////////////////////////////////////////////
struct C { int a; int b; };

int test_shared_ptr_operator()
{
	// reference: http://www.cplusplus.com/reference/memory/shared_ptr/operator%20bool/
	// std::shared_ptr::operator bool: The function returns the same as get()!=0.
	std::shared_ptr<int> foo;
	std::shared_ptr<int> bar(new int(34));

	if (foo) std::cout << "foo points to " << *foo << '\n';
	else std::cout << "foo is null\n";

	if (bar) std::cout << "bar points to " << *bar << '\n';
	else std::cout << "bar is null\n";

	// reference: http://www.cplusplus.com/reference/memory/shared_ptr/operator*/
	// std::shared_ptr::operator*: It is equivalent to: *get().
	std::shared_ptr<int> foo_2(new int);
	std::shared_ptr<int> bar_2(new int(100));

	*foo_2 = *bar_2 * 2;

	std::cout << "foo_2: " << *foo_2 << '\n';
	std::cout << "bar_2: " << *bar_2 << '\n';

	// reference: http://www.cplusplus.com/reference/memory/shared_ptr/operator-%3E/
	// std::shared_ptr::operator->: It returns the same value as get()
	std::shared_ptr<C> foo_3;
	std::shared_ptr<C> bar_3(new C);

	foo_3 = bar_3;

	foo_3->a = 10;
	bar_3->b = 20;

	if (foo_3) std::cout << "foo_3: " << foo_3->a << ' ' << foo_3->b << '\n';
	if (bar_3) std::cout << "bar_3: " << bar_3->a << ' ' << bar_3->b << '\n';

	// reference: http://www.cplusplus.com/reference/memory/shared_ptr/operator=/
	std::shared_ptr<int> foo_4;
	std::shared_ptr<int> bar_4(new int(10));

	foo_4 = bar_4;                          // copy

	bar_4 = std::make_shared<int>(20);   // move

	std::unique_ptr<int> unique(new int(30));
	foo_4 = std::move(unique);            // move from unique_ptr

	std::cout << "*foo_4: " << *foo_4 << '\n';
	std::cout << "*bar_4: " << *bar_4 << '\n';

	return 0;
}

//////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/memory/shared_ptr/owner_before/
int test_shared_ptr_owner_before()
{
	int * p = new int(10);

	std::shared_ptr<int> a(new int(20));
	std::shared_ptr<int> b(a, p);  // alias constructor

	// owner_before: true if the object is considered to be different from x and
	// go before it in a strict weak order based on ownership. false otherwise.
	std::cout << "comparing a and b...\n" << std::boolalpha;
	std::cout << "value-based: " << (!(a<b) && !(b<a)) << '\n';
	std::cout << "owner-based: " << (!a.owner_before(b) && !b.owner_before(a)) << '\n';

	delete p;
	return 0;
}

/////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/memory/shared_ptr/swap/
int test_shared_ptr_swap()
{
	std::shared_ptr<int> foo(new int(10));
	std::shared_ptr<int> bar(new int(20));

	foo.swap(bar);

	std::cout << "*foo: " << *foo << '\n';
	std::cout << "*bar: " << *bar << '\n';

	return 0;
}

//////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/memory/shared_ptr/unique/
int test_shared_ptr_unique()
{
	// std::shared_ptr::unique: This function shall return the same as (use_count()==1),
	// although it may do so in a more efficient way.
	std::shared_ptr<int> foo;
	std::shared_ptr<int> bar(new int);

	std::cout << "foo unique?\n" << std::boolalpha;

	std::cout << "1: " << foo.unique() << '\n';  // false (empty)

	foo = bar;
	std::cout << "2: " << foo.unique() << '\n';  // false (shared with bar)

	bar = nullptr;
	std::cout << "3: " << foo.unique() << '\n';  // true

	return 0;
}

/////////////////////////////////////////////////////
int test_shared_ptr_reset_delete()
{
	// new int[], with shard_ptr'reset function delete
	int* p1 = new int[10];
{
	std::for_each(p1, p1 + 10, [](int& v){v = 5; });

	std::shared_ptr<int> p2;
	// p2和p1指向同一个内存空间
	p2.reset(p1, [](int* p) {delete[] p; });

	for (int i = 0; i < 10; ++i) {
		fprintf(stdout, "p1:  %d  \n", p1[i]);
		fprintf(stdout, "p2:  %d  \n", p2.get()[i]);
	}
}
	// 运行到大括号外，此时p1的空间已经被释放
	for (int i = 0; i < 10; ++i) {
		fprintf(stdout, "p1:  %d  \n", p1[i]);
	}
	//delete[] p1; // p1已释放，不能再delete

	int* pa = new int[10];
{
	std::for_each(pa, pa + 10, [](int& v){v = 8; });

	std::shared_ptr<int> pb;
	// pb和pa指向同一个内存空间
	pb.reset(pa, [](int*) { });

	for (int i = 0; i < 10; ++i) {
		fprintf(stdout, "pa:  %d  \n", pa[i]);
		fprintf(stdout, "pb:  %d  \n", pb.get()[i]);
	}
}
	// 运行到大括号外，此时pa的空间没有被释放
	for (int i = 0; i < 10; ++i) {
		fprintf(stdout, "pa:  %d  \n", pa[i]);
	}
	delete[] pa; // pa没有被释放，需要delete

	return 0;
}
