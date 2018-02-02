#include "priority_queue.hpp"
#include <iostream>
#include <queue> // std::priority_queue
#include <string>
#include <vector>
#include <functional> // std::greater
#include <deque>
#include <list>

// Blog: http://blog.csdn.net/fengbingchun/article/details/70505628

//template < class T,
//	   class Container = vector<T>,
//	   class Compare = less<typename Container::value_type> >
//class priority_queue;

///////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/queue/priority_queue/
int test_priority_queue_1()
{
{ // std::priority_queue::push: Inserts a new element in the priority_queue.
  // The content of this new element is initialized to val. inserts element and sorts the underlying container
  // std::priority_queue::pop: Removes the element on top of the priority_queue, removes the top element,
  // effectively reducing its size by one. The element removed is the one with the highest value.
  // std::priority_queue::empty: Test whether container is empty
	std::priority_queue<int> mypq;

	mypq.push(30);
	mypq.push(100);
	mypq.push(25);
	mypq.push(40);

	std::cout << "Popping out elements...";
	while (!mypq.empty()) {
		std::cout << ' ' << mypq.top();
		mypq.pop();
	}
	std::cout << '\n';
}

{ // std::priority_queue::emplace: C++11, Adds a new element to the priority_queue.
  // This new element is constructed in place passing args as the arguments for its constructor.
	std::priority_queue<std::string> mypq;

	mypq.emplace("orange");
	mypq.emplace("strawberry");
	mypq.emplace("apple");
	mypq.emplace("pear");

	std::cout << "mypq contains:";
	while (!mypq.empty()) {
		std::cout << ' ' << mypq.top();
		mypq.pop();
	}
	std::cout << '\n';
}

{// std::priority_queue::size: Returns the number of elements in the priority_queue
	std::priority_queue<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i = 0; i < 5; i++) myints.push(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';
}

{ // std::priority_queue::top: Returns a constant reference to the top element in the priority_queue.
  // The top element is the element that compares higher in the priority_queue,
  // and the next that is removed from the container when priority_queue::pop is called.
	std::priority_queue<int> mypq;

	mypq.push(10);
	mypq.push(20);
	mypq.push(15);

	std::cout << "mypq.top() is now " << mypq.top() << '\n';
}

{ // std::priority_queue::swap: C++11, Exchanges the contents of the container adaptor by those of x,
  // swapping both the underlying container value and their comparison function using
  // the corresponding swap non-member functions (unqualified)
  // std::swap (priority_queue): Exchange contents of priority queues
	std::priority_queue<int> foo, bar;
	foo.push(15); foo.push(30); foo.push(10);
	bar.push(101); bar.push(202);

	foo.swap(bar);
	//std::swap(foo, bar);

	std::cout << "size of foo: " << foo.size() << '\n';
	std::cout << "size of bar: " << bar.size() << '\n';
}

	return 0;
}

//////////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/container/priority_queue
template<typename T>
static void print_queue(T& q) {
	while (!q.empty()) {
		std::cout << q.top() << " ";
		q.pop();
	}
	std::cout << '\n';
}

int test_priority_queue_2()
{
	std::priority_queue<int> q;
	for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
		q.push(n);
	print_queue(q);

	std::priority_queue<int, std::vector<int>, std::greater<int> > q2;
	for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
		q2.push(n);
	print_queue(q2);

	// Using lambda to compare elements.
	auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
	std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
	for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
		q3.push(n);
	print_queue(q3);

	return 0;
}

/////////////////////////////////////////////////////////
// reference: http://www.technical-recipes.com/2011/priority-queues-and-min-priority-queues-in-c/
struct compare {
	bool operator()(const int& l, const int& r) {
		return l > r;
	}
};

int test_priority_queue_3()
{
	using namespace std;
	priority_queue<int, vector<int>, compare > pq;

	pq.push(3);
	pq.push(5);
	pq.push(1);
	pq.push(8);


	std::cout << "pq contains:";
	while (!pq.empty()) {
		std::cout << ' ' << pq.top();
		pq.pop();
	}
	std::cout << '\n';

	return 0;
}

/////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/4ef4dae9.aspx
int test_priority_queue_4()
{
{ // priority_queue::container_type: A type that provides the base container to be adapted.
	// priority_queue::empty: Tests if a priority_queue is empty.
	// true if the priority_queue is empty; false if the priority_queue is nonempty.
	using namespace std;

	// Declares priority_queues with default deque base container
	priority_queue <int> q1, s2;
	q1.push(1);

	if (q1.empty()) cout << "The priority_queue q1 is empty." << endl;
	else cout << "The priority_queue q1 is not empty." << endl;

	if (s2.empty()) cout << "The priority_queue s2 is empty." << endl;
	else cout << "The priority_queue s2 is not empty." << endl;
}

{ // priority_queue::pop: Removes the largest element of the priority_queue from the top position.
	using namespace std;
	priority_queue <int> q1, s2;

	q1.push(10);
	q1.push(5);
	q1.push(30);

	priority_queue <int>::size_type i, iii;
	i = q1.size();
	cout << "The priority_queue length is " << i << "." << endl;

	const int& ii = q1.top();
	cout << "The element at the top of the priority_queue is " << ii << "." << endl;
	q1.pop();

	iii = q1.size();
	cout << "After a pop, the priority_queue length is " << iii << "." << endl;
	const int& iv = q1.top();
	cout << "After a pop, the element at the top of the " << "priority_queue is " << iv << "." << endl;
}

{ // priority_queue::priority_queue: Constructs a priority_queue that is empty or
	// that is a copy of a range of a base container object or of another priority_queue
	using namespace std;

	// The first member function declares priority_queue
	// with a default vector base container
	priority_queue <int> q1;
	cout << "q1 = ( ";
	while (!q1.empty()) {
		cout << q1.top() << " ";
		q1.pop();
	}
	cout << ")" << endl;

	// Explicitly declares a priority_queue with nondefault
	// deque base container
	priority_queue <int, deque <int> > q2;
	q2.push(5);
	q2.push(15);
	q2.push(10);
	cout << "q2 = ( ";
	while (!q2.empty()) {
		cout << q2.top() << " ";
		q2.pop();
	}
	cout << ")" << endl;

	// This method of printing out the elements of a priority_queue
	// removes the elements from the priority queue, leaving it empty
	cout << "After printing, q2 has " << q2.size() << " elements." << endl;

	// The third member function declares a priority_queue
	// with a vector base container and specifies that the comparison
	// function greater is to be used for ordering elements
	priority_queue <int, vector<int>, greater<int> > q3;
	q3.push(2);
	q3.push(1);
	q3.push(3);
	cout << "q3 = ( ";
	while (!q3.empty()) {
		cout << q3.top() << " ";
		q3.pop();
	}
	cout << ")" << endl;

	// The fourth member function declares a priority_queue and
	// initializes it with elements copied from another container:
	// first, inserting elements into q1, then copying q1 elements into q4
	q1.push(100);
	q1.push(200);
	q1.push(5);
	priority_queue <int> q4(q1);
	cout << "q4 = ( ";
	while (!q4.empty()) {
		cout << q4.top() << " ";
		q4.pop();
	}
	cout << ")" << endl;

	// Creates an auxiliary vector object v5 to be used to initialize q5
	vector <int> v5;
	vector <int>::iterator v5_Iter;
	v5.push_back(10);
	v5.push_back(30);
	v5.push_back(20);
	cout << "v5 = ( ";
	for (v5_Iter = v5.begin(); v5_Iter != v5.end(); v5_Iter++)
		cout << *v5_Iter << " ";
	cout << ")" << endl;

	// The fifth member function declares and
	// initializes a priority_queue q5 by copying the
	// range v5[ first,  last) from vector v5  
	priority_queue <int> q5(v5.begin(), v5.begin() + 2);
	cout << "q5 = ( ";
	while (!q5.empty()) {
		cout << q5.top() << " ";
		q5.pop();
	}
	cout << ")" << endl;

	// The sixth member function declares a priority_queue q6
	// with a comparison function greater and initializes q6
	// by copying the range v5[ first,  last) from vector v5
	priority_queue <int, vector<int>, greater<int> >
		q6(v5.begin(), v5.begin() + 2);
	cout << "q6 = ( ";
	while (!q6.empty()) {
		cout << q6.top() << " ";
		q6.pop();
	}
	cout << ")" << endl;
}

{ // priority_queue::push: Adds an element to the priority queue based on the priority of the element from operator<.
	using namespace std;
	priority_queue<int> q1;

	q1.push(10);
	q1.push(30);
	q1.push(20);

	priority_queue<int>::size_type i;
	i = q1.size();
	cout << "The priority_queue length is " << i << "." << endl;

	const int& ii = q1.top();
	cout << "The element at the top of the priority_queue is " << ii << "." << endl;
}

{ // priority_queue::size: Returns the number of elements in the priority_queue.
	// priority_queue::size_type: An unsigned integer type that can represent the number of elements in a priority_queue.
	using namespace std;
	priority_queue <int> q1, q2;
	priority_queue <int>::size_type i;

	q1.push(1);
	i = q1.size();
	cout << "The priority_queue length is " << i << "." << endl;

	q1.push(2);
	i = q1.size();
	cout << "The priority_queue length is now " << i << "." << endl;
}

{ // priority_queue::top: Returns a const reference to the largest element at the top of the priority_queue.
	using namespace std;
	priority_queue<int> q1;

	q1.push(10);
	q1.push(30);
	q1.push(20);

	priority_queue<int>::size_type i;
	i = q1.size();
	cout << "The priority_queue length is " << i << "." << endl;

	const int& ii = q1.top();
	cout << "The element at the top of the priority_queue is " << ii << "." << endl;
}

{ // priority_queue::value_type: A type that represents the type of object stored as an element in a priority_queue.
	using namespace std;

	// Declares priority_queues with default deque base container
	priority_queue<int>::value_type AnInt;

	AnInt = 69;
	cout << "The value_type is AnInt = " << AnInt << endl;

	priority_queue<int> q1;
	q1.push(AnInt);
	cout << "The element at the top of the priority_queue is " << q1.top() << "." << endl;
}

	return 0;
}
