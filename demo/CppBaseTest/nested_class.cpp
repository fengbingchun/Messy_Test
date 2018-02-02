#include "nested_class.hpp"
#include <iostream>
#include <vector>
#include <typeinfo>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78513239

namespace nested_class_ {
//////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/nested_types
int x, y; // globals
class enclose { // enclosing class
	int x; // note: private members
	static int s;
public:
	struct inner { // nested class
		void f(int i) {
			//x = i; // Error: can't write to non-static enclose::x without instance
			//int a = sizeof(x); // Error until C++11,
					   // OK in C++11: operand of sizeof is unevaluated,
					   // this use of the non-static enclose::x is allowed.
			s = i;   // OK: can assign to the static enclose::s
			::nested_class_::x = i; // OK: can assign to global x
			y = i;   // OK: can assign to global y
		}
		void g(enclose* p, int i) {
			p->x = i; // OK: assign to enclose::x
		}
	};
};

class enclose_ {
	struct nested { // private member
		void g() {}
	};
public:
	static nested f() { return nested{}; }
};

int test_nested_class_1()
{
	//enclose_::nested n1 = enclose_::f(); // error: 'nested' is private

	enclose_::f().g(); // OK: does not name 'nested'
	auto n2 = enclose_::f(); // OK: does not name 'nested'
	n2.g();

	return 0;
}

////////////////////////////////////////////////////////
// reference: http://www.sanfoundry.com/c-tutorials-nested-structure-access/
/* structure A declared */
typedef struct A {
	int a;
	float b;
} New_a;

/* structure B declared */
typedef struct B {
	int c;
	float d;
	struct A e;    /* member 'e' is itself a structure */
} New_b;

int test_nested_class_2()
{
	/* Let's declare variables of New_a and New_b */
	New_a bread;
	New_b butter;        /* 'butter' is a nested structure */

	/* Let's access bread using dot operator */
	bread.a = 10;        /* assigned member a value 10 */
	bread.b = 25.50;

	/* Let's access butter using dot operator */
	butter.c = 10;
	butter.d = 50.00;

	/* Let's access member 'e' which is a nested structure */
	butter.e.a = 20;
	butter.e.b = 20.00;

	/* Display values of members of 'butter.e' structure */
	printf("butter.e.a is %4d\n", butter.e.a);
	printf("butter.e.b is %.2f\n", butter.e.b);

	return 0;
}

////////////////////////////////////////////////////
// reference: http://www.geeksforgeeks.org/nested-classes-in-c/
/* start of Enclosing class declaration */
class Enclosing {

	int x;

	/* start of Nested class declaration */
	class Nested {
		int y;
		void NestedFun(Enclosing *e) {
			std::cout << e->x;  // works fine: nested class can access
			// private members of Enclosing class
		}
	}; // declaration Nested class ends here
}; // declaration Enclosing class ends here

int test_nested_class_3()
{
	return 0;
}

////////////////////////////////////////////////////////////
// reference: http://www.oopweb.com/CPP/Documents/CPPAnnotations/Volume/cplusplus16.html
class Clonable {
public:
	class Base {
	public:
		virtual ~Base() {}
		virtual Base *clone() const = 0;
	};

private:
	Base *d_bp;

public:
	Clonable() : d_bp(0) {}
	~Clonable() { delete d_bp; }
	Clonable(Clonable const &other) { copy(other); }

	Clonable &operator=(Clonable const &other)
	{
		if (this != &other) {
			delete d_bp;
			copy(other);
		}
		return *this;
	}

	// New for virtual constructions:
	Clonable(Base const &bp)
	{
		d_bp = bp.clone();      // allows initialization from
	}                           // Base and derived objects

	Base &get() const
	{
		return *d_bp;
	}

private:
	void copy(Clonable const &other)
	{
		if ((d_bp = other.d_bp))
			d_bp = d_bp->clone();
	}
};

class Derived1 : public Clonable::Base
{
public:
	~Derived1()
	{
		std::cout << "~Derived1() called\n";
	}
	virtual Clonable::Base *clone() const
	{
		return new Derived1(*this);
	}
};

int test_nested_class_4()
{
	std::vector<Clonable> bv;

	bv.push_back(Derived1());
	std::cout << "==\n";

	std::cout << typeid(bv[0].get()).name() << std::endl;
	std::cout << "==\n";

	std::vector<Clonable> v2(bv);
	std::cout << typeid(v2[0].get()).name() << std::endl;
	std::cout << "==\n";

	return 0;
}

/////////////////////////////////////////////////////////
// reference: http://www.sanfoundry.com/cpp-program-illustrate-nested-classes/
class Stack {
	class Node {
	public:
		int data;
		Node* next;
		Node(int data, Node* next);
		~Node();
	}*head;
public:
	Stack();
	Stack(const Stack& s);
	void operator=(const Stack& s);
	~Stack();
	void push(int data);
	int peek() const;
	int pop();
};

Stack::Node::Node(int data, Node* next)
{
	this->data = data;
	this->next = next;
}

Stack::Node::~Node() { }

Stack::Stack() { head = NULL; }

Stack::Stack(const Stack& s)
{
	head = s.head;
}

void Stack::operator=(const Stack& s)
{
	head = s.head;
}

void Stack::push(int data)
{
	head = new Node(data, head);
}

int Stack::peek() const {
	if (head == 0) {
		std::cerr << "Stack empty!" << std::endl;
		return -1;
	}
	else
		return head->data;
}

int Stack::pop()
{
	if (head == NULL) return -1;
	int result = head->data;
	Node* oldNode = head;
	head = head->next;
	delete oldNode;
	return result;
}

Stack::~Stack()
{
	if (head != NULL) {
		while (head->next != NULL) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
}

int test_nested_class_5()
{
	Stack Integers;
	int value, num;

	std::cout << "Enter the number of elements ";
	std::cin >> num;
	while (num > 0) {
		std::cin >> value;
		Integers.push(value);
		num--;
	}
	while ((value = Integers.pop()) != -1)
		std::cout << "Top element of stack  " << value << std::endl;

	return 0;
}

//////////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/71dw8xzh.aspx
class X
{

	template <class T>
	struct Y {
		T m_t;
		Y(T t) : m_t(t) { }
	};

	Y<int> yInt;
	Y<char> yChar;

public:
	X(int i, char c) : yInt(i), yChar(c) { }
	void print()
	{
		std::cout << yInt.m_t << " " << yChar.m_t << std::endl;
	}
};

int test_nested_class_6()
{
	X x(1, 'a');
	x.print();

	return 0;
}

///////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/71dw8xzh.aspx
template <class T>
class X_
{
	template <class U>
	class Y {
		U* u;
	public:
		Y();
		U& Value();
		void print();
		~Y();
	};

	Y<int> y;
public:
	X_(T t) { y.Value() = t; }
	void print() { y.print(); }
};

template <class T>
template <class U>
X_<T>::Y<U>::Y()
{
	std::cout << "X_<T>::Y<U>::Y()" << std::endl;
	u = new U();
}

template <class T>
template <class U>
U& X_<T>::Y<U>::Value()
{
	return *u;
}

template <class T>
template <class U>
void X_<T>::Y<U>::print()
{
	std::cout << this->Value() << std::endl;
}

template <class T>
template <class U>
X_<T>::Y<U>::~Y()
{
	std::cout << "X_<T>::Y<U>::~Y()" << std::endl;
	delete u;
}

int test_nested_class_7()
{
	X_<int>* xi = new X_<int>(10);
	X_<char>* xc = new X_<char>('c');
	xi->print();
	xc->print();
	delete xi;
	delete xc;

	return 0;
}

} // namespace nested_class_

