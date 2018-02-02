#include "stack.hpp"
#include <iostream>
#include <stack>
#include <vector>
#include <deque>
#include <list>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/72773603

////////////////////////////////////////////////////////////
// https://msdn.microsoft.com/en-us/library/56fa1zk5.aspx
int test_stack_2()
{
	using namespace std;

	// Declares stack with default deque base container  
	stack <char> dsc1;

	//Explicitly declares a stack with deque base container  
	stack <char, deque<char> > dsc2;

	// Declares a stack with vector base containers  
	stack <int, vector<int> > vsi1;

	// Declares a stack with list base container  
	stack <int, list<int> > lsi;

	// The second member function copies elements from a container  
	vector<int> v1;
	v1.push_back(1);
	stack <int, vector<int> > vsi2(v1);
	cout << "The element at the top of stack vsi2 is "
		<< vsi2.top() << "." << endl;

	return 0;
}

///////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/stack/stack/
int test_stack_1()
{
{ // stack::stack: Constructs a stack container adaptor object
	std::deque<int> mydeque(3, 100);          // deque with 3 elements
	std::vector<int> myvector(2, 200);        // vector with 2 elements

	std::stack<int> first;                    // empty stack
	std::stack<int> second(mydeque);         // stack initialized to copy of deque

	std::stack<int, std::vector<int> > third;  // empty stack using vector
	std::stack<int, std::vector<int> > fourth(myvector);

	std::cout << "size of first: " << first.size() << '\n';
	std::cout << "size of second: " << second.size() << '\n';
	std::cout << "size of third: " << third.size() << '\n';
	std::cout << "size of fourth: " << fourth.size() << '\n';
}

{ // stack::emplace: c++11, Adds a new element at the top of the stack, above its current top element.
  // This new element is constructed in place passing args as the arguments for its constructor
	std::stack<std::string> mystack;

	mystack.emplace("First sentence");
	mystack.emplace("Second sentence");

	std::cout << "mystack contains:\n";
	while (!mystack.empty()) {
		std::cout << mystack.top() << '\n';
		mystack.pop();
	}
}

{ // stack::empty: Returns whether the stack is empty: i.e. whether its size is zero
  // stack::pop: Removes the element on top of the stack, effectively reducing its size by one
  // stack::push: Inserts a new element at the top of the stack, above its current top element.
  // The content of this new element is initialized to a copy of val.
	std::stack<int> mystack;
	int sum(0);

	for (int i = 1; i <= 10; i++) mystack.push(i);

	while (!mystack.empty()) {
		sum += mystack.top();
		mystack.pop();
	}

	std::cout << "total: " << sum << '\n';
}

{ // stack::size: Returns the number of elements in the stack.
	std::stack<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i = 0; i < 5; i++) myints.push(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';
}

{ // stack::swap: Exchanges the contents of the container adaptor (*this) by those of x.
	std::stack<int> foo, bar;
	foo.push(10); foo.push(20); foo.push(30);
	bar.push(111); bar.push(222);

	foo.swap(bar);
	// std::swap(foo, bar);

	std::cout << "size of foo: " << foo.size() << '\n';
	std::cout << "size of bar: " << bar.size() << '\n';
}

{ // stack::top: Returns a reference to the top element in the stack. 
	std::stack<int> mystack;

	mystack.push(10);
	mystack.push(20);

	mystack.top() -= 5;

	std::cout << "mystack.top() is now " << mystack.top() << '\n';
}

	return 0;
}


