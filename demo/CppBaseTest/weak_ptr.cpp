#include "weak_ptr.hpp"
#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52203825

///////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/memory/weak_ptr
std::weak_ptr<int> gw;

void f()
{
	if (auto spt = gw.lock()) { // Has to be copied into a shared_ptr before usage
		std::cout << *spt << "\n";
	}
	else {
		std::cout << "gw is expired\n";
	}
}

int test_weak_ptr1()
{
	{
		auto sp = std::make_shared<int>(42);
		gw = sp;

		f();
	}

	f();

	return 0;
}

/////////////////////////////////////////////////
// reference: http://stackoverflow.com/questions/12030650/when-is-stdweak-ptr-useful
int test_weak_ptr2()
{
	// OLD, problem with dangling pointer
	// PROBLEM: ref will point to undefined data!
	int* ptr = new int(10);
	int* ref = ptr;
	delete ptr;

	// NEW
	// SOLUTION: check expired() or lock() to determine if pointer is valid
	// empty definition
	std::shared_ptr<int> sptr;

	// takes ownership of pointer
	sptr.reset(new int);
	*sptr = 10;

	// get pointer to data without taking ownership
	std::weak_ptr<int> weak1 = sptr;

	// deletes managed object, acquires new pointer
	sptr.reset(new int);
	*sptr = 5;

	// get pointer to new data without taking ownership
	std::weak_ptr<int> weak2 = sptr;

	// weak1 is expired!

	if (auto tmp = weak1.lock())
		std::cout << *tmp << '\n';
	else
		std::cout << "weak1 is expired\n";

	// weak2 points to new data (5)

	if (auto tmp = weak2.lock())
		std::cout << *tmp << '\n';
	else
		std::cout << "weak2 is expired\n";

	return 0;
}

//////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/hh279672.aspx
class Controller
{
public:
	int Num;
	std::string Status;
	std::vector<std::weak_ptr<Controller>> others;
	explicit Controller(int i) : Num(i), Status("On")
	{
		std::cout << "Creating Controller" << Num << std::endl;
	}

	~Controller()
	{
		std::cout << "Destroying Controller" << Num << std::endl;
	}

	// Demonstrates how to test whether the pointed-to memory still exists or not.
	void CheckStatuses() const
	{
		for_each(others.begin(), others.end(), [](std::weak_ptr<Controller> wp) {
			try {
				auto p = wp.lock();
				std::cout << "Status of " << p->Num << " = " << p->Status << std::endl;
			}
			catch (std::bad_weak_ptr b) {
				std::cout << "Null object" << std::endl;
			}
		});
	}
};

void RunTest()
{
	std::vector<std::shared_ptr<Controller>> v;

	v.push_back(std::shared_ptr<Controller>(new Controller(0)));
	v.push_back(std::shared_ptr<Controller>(new Controller(1)));
	v.push_back(std::shared_ptr<Controller>(new Controller(2)));
	v.push_back(std::shared_ptr<Controller>(new Controller(3)));
	v.push_back(std::shared_ptr<Controller>(new Controller(4)));

	// Each controller depends on all others not being deleted.
	// Give each controller a pointer to all the others. 
	for (int i = 0; i < v.size(); ++i) {
		for_each(v.begin(), v.end(), [v, i](std::shared_ptr<Controller> p) {
			if (p->Num != i) {
				v[i]->others.push_back(std::weak_ptr<Controller>(p));
				std::cout << "push_back to v[" << i << "]: " << p->Num << std::endl;
			}
		});
	}

	for_each(v.begin(), v.end(), [](std::shared_ptr<Controller>& p) {
		std::cout << "use_count = " << p.use_count() << std::endl;
		p->CheckStatuses();
	});
}

int test_weak_ptr3()
{
	RunTest();
	std::cout << "Press any key" << std::endl;
	char ch;
	std::cin.getline(&ch, 1);

	return 0;
}

////////////////////////////////////////////////
// reference: https://oopscenities.net/2014/08/03/c-smart-pointers-part-5-weak_ptr/
struct Child;
struct Parent
{
	std::shared_ptr<Child> child;

	~Parent() { std::cout << "Bye Parent" << std::endl; }

	void hi() const { std::cout << "Hello" << std::endl; }
};

struct Child
{
	std::weak_ptr<Parent> parent;
	//std::shared_ptr<Parent> parent; // memory leak

	~Child() { std::cout << "Bye Child" << std::endl; }
};

int test_weak_ptr4()
{
	auto parent = std::make_shared<Parent>();
	auto child = std::make_shared<Child>();

	parent->child = child;
	child->parent = parent;
	child->parent.lock()->hi();
	// child->parent->hi();

	return 0;
}

/////////////////////////////////////////////////////
// reference: http://thispointer.com/shared_ptr-binary-trees-and-the-problem-of-cyclic-references/
class Node
{
	int value;
public:
	std::shared_ptr<Node> leftPtr;
	std::shared_ptr<Node> rightPtr;
	// Just Changed the shared_ptr to weak_ptr
	std::weak_ptr<Node> parentPtr;
	Node(int val) : value(val)     {
		std::cout << "Contructor" << std::endl;
	}
	~Node()     {
		std::cout << "Destructor" << std::endl;
	}
};

int test_weak_ptr5()
{
	std::shared_ptr<Node> ptr = std::make_shared<Node>(4);
	ptr->leftPtr = std::make_shared<Node>(2);
	ptr->leftPtr->parentPtr = ptr;
	ptr->rightPtr = std::make_shared<Node>(5);
	ptr->rightPtr->parentPtr = ptr;
	std::cout << "ptr reference count = " << ptr.use_count() << std::endl;
	std::cout << "ptr->leftPtr reference count = " << ptr->leftPtr.use_count() << std::endl;
	std::cout << "ptr->rightPtr reference count = " << ptr->rightPtr.use_count() << std::endl;
	std::cout << "ptr->rightPtr->parentPtr reference count = " << ptr->rightPtr->parentPtr.lock().use_count() << std::endl;
	std::cout << "ptr->leftPtr->parentPtr reference count = " << ptr->leftPtr->parentPtr.lock().use_count() << std::endl;

	return 0;
}
