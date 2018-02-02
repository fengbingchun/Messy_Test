#include "queue.hpp"
#include <iostream>
#include <queue> // std::queue
#include <vector>
#include <string>
#include <list>

// Blog: http://blog.csdn.net/fengbingchun/article/details/70495791

//////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/queue/queue/
int test_queue_1()
{
{ // std::queue::back: Access last element, Returns a reference to the last element in the queue.
  // queue::front: access the first element, queue::back: access the last element
	std::queue<int> myqueue;

	myqueue.push(12);
	myqueue.push(20);
	myqueue.push(75);   // this is now the back

	fprintf(stderr, "myqueue.back: %d, myqueue.front: %d\n", myqueue.back(), myqueue.front());
	myqueue.back() -= myqueue.front(); // 75 -= 12
	std::cout << "myqueue.back() is now " << myqueue.back() << '\n'; // myqueue.back() is now 63
}

{ // std::queue::front: Access next element, Returns a reference to the next element in the queue.
  // The next element is the "oldest" element in the queue and
  // the same element that is popped out from the queue when queue::pop is called.
	std::queue<int> myqueue;

	myqueue.push(77);
	myqueue.push(20);
	myqueue.push(16);

	fprintf(stderr, "myqueue.back: %d, myqueue.front: %d\n", myqueue.back(), myqueue.front());
	myqueue.front() -= myqueue.back();    // 77-16=61
	std::cout << "myqueue.front() is now " << myqueue.front() << '\n';
}

{ // std::queue::push: Inserts a new element at the end of the queue, after its current last element
  // std::queue::pop: Remove next element, Removes the next element in the queue, effectively reducing its size by one.
  // std::queue::empty: Test whether container is empty, Returns whether the queue is empty: i.e. whether its size is zero.
	std::queue<int> myqueue;
	int myint;

	std::cout << "Please enter some integers (enter 0 to end):\n";
	std::vector<int> vec{ 1, 2, 3, 4, 5 };

	for (const auto& value : vec) {
		myqueue.push(value);
	}

	fprintf(stderr, "myqueue.back: %d, myqueue.front: %d\n", myqueue.back(), myqueue.front());
	std::cout << "myqueue contains: ";
	while (!myqueue.empty()) {
		std::cout << ' ' << myqueue.front();
		myqueue.pop();
	}
	std::cout << '\n';
}

{ // std::queue::emplace: C++11, Construct and insert element.
  // Adds a new element at the end of the queue, after its current last element.
  // The element is constructed in-place, i.e. no copy or move operations are performed.
  // queue::push: inserts element at the end , queue::emplace: constructs element in-place at the end
  // queue::pop: removes the first element 
	std::queue<std::string> myqueue;

	myqueue.emplace("First sentence");
	myqueue.emplace("Second sentence");

	std::cout << "myqueue contains:\n";
	while (!myqueue.empty()) {
		std::cout << myqueue.front() << '\n';
		myqueue.pop();
	}
}

{ // std::queue::size: Returns the number of elements in the queue
	std::queue<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i = 0; i < 5; i++) myints.push(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';
}

{ // std::queue::swap: C++11, Exchanges the contents of the container adaptor
  // std::swap (queue): Exchanges the contents of x and y.
	std::queue<int> foo, bar;
	foo.push(10); foo.push(20); foo.push(30);
	bar.push(111); bar.push(222);

	foo.swap(bar);
	// std::swap(foo, bar);

	std::cout << "size of foo: " << foo.size() << '\n';
	std::cout << "size of bar: " << bar.size() << '\n';
	std::cout << "foo contains: ";
	while (!foo.empty()) {
		std::cout << ' ' << foo.front();
		foo.pop();
	}
	std::cout << '\n';
	std::cout << "bar contains: ";
	while (!bar.empty()) {
		std::cout << ' ' << bar.front();
		bar.pop();
	}
	std::cout << '\n';
}

	return 0;
}

////////////////////////////////////////////////
// reference: http://stackoverflow.com/questions/709146/how-do-i-clear-the-stdqueue-efficiently
static void clear(std::queue<int> &q)
{
	std::queue<int> empty;
	std::swap(q, empty);
}

int test_queue_2()
{
	// clear queue, avoid to pop in a loop
	// A common idiom for clearing standard containers is swapping with an empty version of the container
	std::queue<int> foo;
	foo.push(10); foo.push(20); foo.push(30);
	fprintf(stderr, "foo size: %d\n", foo.size());

	clear(foo);
	fprintf(stderr, "foo size: %d\n", foo.size());

	return 0;
}

//////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/s23s3de6.aspx
int test_queue_3()
{
{ // queue::back: Returns a reference to the last and most recently added element at the back of the queue.
	// The last element of the queue. If the queue is empty, the return value is undefined.
	using namespace std;
	queue <int> q1;

	q1.push(10);
	q1.push(11);

	int& i = q1.back();
	const int& ii = q1.front();

	cout << "The integer at the back of queue q1 is " << i << "." << endl;
	cout << "The integer at the front of queue q1 is " << ii << "." << endl;
}

{ // queue::empty: true if the queue is empty; false if the queue is nonempty.
	using namespace std;

	// Declares queues with default deque base container
	queue <int> q1, q2;

	q1.push(1);

	if (q1.empty()) cout << "The queue q1 is empty." << endl;
	else cout << "The queue q1 is not empty." << endl;

	if (q2.empty()) cout << "The queue q2 is empty." << endl;
	else cout << "The queue q2 is not empty." << endl;
}

{ // queue::front: Returns a reference to the first element at the front of the queue
  // queue::size_type: An unsigned integer type that can represent the number of elements in a queue.
	using namespace std;
	queue <int> q1;

	q1.push(10);
	q1.push(20);
	q1.push(30);

	queue <int>::size_type i;
	i = q1.size();
	cout << "The queue length is " << i << "." << endl;

	int& ii = q1.back();
	int& iii = q1.front();

	cout << "The integer at the back of queue q1 is " << ii << "." << endl;
	cout << "The integer at the front of queue q1 is " << iii << "." << endl;
}

{ // queue::pop: Removes an element from the front of the queue
	using namespace std;
	queue <int> q1, s2;

	q1.push(10);
	q1.push(20);
	q1.push(30);

	queue <int>::size_type i;
	i = q1.size();
	cout << "The queue length is " << i << "." << endl;

	i = q1.front();
	cout << "The element at the front of the queue is " << i << "." << endl;

	q1.pop();

	i = q1.size();
	cout << "After a pop the queue length is " << i << "." << endl;

	i = q1.front();
	cout << "After a pop, the element at the front of the queue is " << i << "." << endl;
}

{ // queue::push: Adds an element to the back of the queue.
	using namespace std;
	queue <int> q1;

	q1.push(10);
	q1.push(20);
	q1.push(30);

	queue <int>::size_type i;
	i = q1.size();
	cout << "The queue length is " << i << "." << endl;

	i = q1.front();
	cout << "The element at the front of the queue is " << i << "." << endl;
}

{ // queue::queue: Constructs a queue that is empty or that is a copy of a base container object.
	using namespace std;

	// Declares queue with default deque base container
	queue <char> q1;

	// Explicitly declares a queue with deque base container
	queue <char, deque<char> > q2;

	// These lines don't cause an error, even though they
	// declares a queue with a vector base container
	queue <int, vector<int> > q3;
	q3.push(10);
	// but the following would cause an error because vector has
	// no pop_front member function
	// q3.pop( );

	// Declares a queue with list base container
	queue <int, list<int> > q4;

	// The second member function copies elements from a container
	list<int> li1;
	li1.push_back(1);
	li1.push_back(2);
	queue <int, list<int> > q5(li1);
	cout << "The element at the front of queue q5 is " << q5.front() << "." << endl;
	cout << "The element at the back of queue q5 is " << q5.back() << "." << endl;
}

{ // queue::size: Returns the number of elements in the queue
	using namespace std;
	queue <int> q1, q2;
	queue <int>::size_type i;

	q1.push(1);
	i = q1.size();
	cout << "The queue length is " << i << "." << endl;

	q1.push(2);
	i = q1.size();
	cout << "The queue length is now " << i << "." << endl;
}

{ // queue::value_type: A type that represents the type of object stored as an element in a queue.
	using namespace std;

	// Declares queues with default deque base container
	queue<int>::value_type AnInt;

	AnInt = 69;
	cout << "The value_type is AnInt = " << AnInt << endl;

	queue<int> q1;
	q1.push(AnInt);
	cout << "The element at the front of the queue is " << q1.front() << "." << endl;
}

	return 0;
}
