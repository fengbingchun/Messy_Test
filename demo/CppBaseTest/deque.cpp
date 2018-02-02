#include "deque.hpp"
#include <iostream>
#include <deque>
#include <vector>

// Blog: http://blog.csdn.net/fengbingchun/article/details/72757856

////////////////////////////////////////////////////////
// https://msdn.microsoft.com/en-us/library/22a9t119.aspx
int test_deque_2()
{
{ // deque::at: Returns a reference to the element at a specified location in the deque.
	using namespace std;
	deque <int> c1;

	c1.push_back(10);
	c1.push_back(20);

	const int& i = c1.at(0);
	int& j = c1.at(1);
	cout << "The first element is " << i << endl;
	cout << "The second element is " << j << endl;
}

{ // deque::back: Returns a reference to the last element of the deque.
	using namespace std;
	deque <int> c1;

	c1.push_back(10);
	c1.push_back(11);

	int& i = c1.back();
	const int& ii = c1.front();

	cout << "The last integer of c1 is " << i << endl; // 11
	i--;
	cout << "The next-to-last integer of c1 is " << ii << endl; // 10
	cout << "The last integer of c1 is " << c1.back() << endl; // 10
}

{ // deque::clear: Erases all the elements of a deque.
	using namespace std;
	deque <int> c1;

	c1.push_back(10);
	c1.push_back(20);
	c1.push_back(30);

	cout << "The size of the deque is initially " << c1.size() << endl;
	c1.clear();
	cout << "The size of the deque after clearing is " << c1.size() << endl;
}

{ // deque::const_reference: A type that provides a reference to a const element stored in a deque for reading and performing const operations
	using namespace std;
	deque <int> c1;

	c1.push_back(10);
	c1.push_back(20);

	const deque <int> c2 = c1;
	const int &i = c2.front();
	const int &j = c2.back();
	cout << "The first element is " << i << endl;
	cout << "The second element is " << j << endl;

	// The following line would cause an error as c2 is const
	// c2.push_back( 30 );
}

{ // deque::crbegin: Returns a const iterator to the first element in a reversed deque
	using namespace std;
	deque <int> v1;
	deque <int>::iterator v1_Iter;
	deque <int>::const_reverse_iterator v1_rIter;

	v1.push_back(1);
	v1.push_back(2);

	v1_Iter = v1.begin();
	cout << "The first element of deque is "
		<< *v1_Iter << "." << endl;

	v1_rIter = v1.crbegin();
	cout << "The first element of the reversed deque is "
		<< *v1_rIter << "." << endl;
}

{ // deque::emplace: Inserts an element constructed in place into the deque at a specified position.
	using namespace std;
	deque <int> v1;
	deque <int>::iterator Iter;

	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);

	cout << "v1 =";
	for (Iter = v1.begin(); Iter != v1.end(); Iter++)
		cout << " " << *Iter;
	cout << endl;

	// initialize a deque of deques by moving v1  
	deque < deque <int> > vv1;

	vv1.emplace(vv1.begin(), move(v1));
	if (vv1.size() != 0 && vv1[0].size() != 0) {
		cout << "vv1[0] =";
		for (Iter = vv1[0].begin(); Iter != vv1[0].end(); Iter++)
			cout << " " << *Iter;
		cout << endl;
	}
}

	return 0;
}

/////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/deque/deque/
int test_deque_1()
{
{ // deque::deque: Construct deque container
	unsigned int i;

	// constructors used in the same order as described above:
	std::deque<int> first;                                // empty deque of ints
	std::deque<int> second(4, 100);                       // four ints with value 100
	std::deque<int> third(second.begin(), second.end());  // iterating through second
	std::deque<int> fourth(third);                       // a copy of third

	// the iterator constructor can be used to copy arrays:
	int myints[] = { 16, 2, 77, 29 };
	std::deque<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

	std::cout << "The contents of fifth are:";
	for (std::deque<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it; // 16 2 77 29
	std::cout << '\n';
}

{ // deque::assign: Assigns new contents to the deque container,
  // replacing its current contents, and modifying its size accordingly.

	std::deque<int> first;
	std::deque<int> second;
	std::deque<int> third;

	first.assign(7, 100);             // 7 ints with a value of 100

	std::deque<int>::iterator it;
	it = first.begin() + 1;

	second.assign(it, first.end() - 1); // the 5 central values of first

	int myints[] = { 1776, 7, 4 };
	third.assign(myints, myints + 3);   // assigning from array.

	std::cout << "Size of first: " << int(first.size()) << '\n'; // 7
	std::cout << "Size of second: " << int(second.size()) << '\n'; // 5
	std::cout << "Size of third: " << int(third.size()) << '\n'; // 3
}

{ // deque::at: Returns a reference to the element at position n in the deque container object.
	std::deque<unsigned> mydeque(10);   // 10 zero-initialized unsigneds

	// assign some values:
	for (unsigned i = 0; i < mydeque.size(); i++)
		mydeque.at(i) = i;

	std::cout << "mydeque contains:";
	for (unsigned i = 0; i < mydeque.size(); i++)
		std::cout << ' ' << mydeque.at(i); // 0 1 2 3 4 5 6 7 8 9
	std::cout << '\n';
}

{ // deque::back: Returns a reference to the last element in the container.
  // deque::push_back: Adds a new element at the end of the deque container,
  // after its current last element. The content of val is copied (or moved) to the new element
	std::deque<int> mydeque;
	mydeque.push_back(10);

	while (mydeque.back() != 0)
		mydeque.push_back(mydeque.back() - 1);

	std::cout << "mydeque contains:";
	for (std::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // deque::begin: Return iterator to beginning
  // deque::end: Return iterator to end
	std::deque<int> mydeque;
	for (int i = 1; i <= 5; i++) mydeque.push_back(i);

	std::cout << "mydeque contains:";
	std::deque<int>::iterator it = mydeque.begin();

	while (it != mydeque.end())
		std::cout << ' ' << *it++;
	std::cout << '\n';
}

{ // deque::cbegin: c++11, Return const_iterator to beginning
  // deque::cend: c++11, Return const_iterator to end
	std::deque<int> mydeque = { 10, 20, 30, 40, 50 };

	std::cout << "mydeque contains:";
	for (auto it = mydeque.cbegin(); it != mydeque.cend(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // deque::clear: Clear content
	unsigned int i;
	std::deque<int> mydeque;
	mydeque.push_back(100);
	mydeque.push_back(200);
	mydeque.push_back(300);

	std::cout << "mydeque contains:";
	for (std::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	mydeque.clear();
	mydeque.push_back(1101);
	mydeque.push_back(2202);

	std::cout << "mydeque contains:";
	for (std::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // deque::crbegin: c++11, Return const_reverse_iterator to reverse beginning
  // deque::crend: c++11, Return const_reverse_iterator to reverse end
	std::deque<int> mydeque = { 1, 2, 3, 4, 5 };

	std::cout << "mydeque backwards:";
	for (auto rit = mydeque.crbegin(); rit != mydeque.crend(); ++rit)
		std::cout << ' ' << *rit;
	std::cout << '\n';
}

{ // deque::emplace: c++11, Construct and insert element
	std::deque<int> mydeque = { 10, 20, 30 };

	auto it = mydeque.emplace(mydeque.begin() + 1, 100);
	mydeque.emplace(it, 200);
	mydeque.emplace(mydeque.end(), 300);

	std::cout << "mydeque contains:";
	for (auto& x : mydeque)
		std::cout << ' ' << x;
	std::cout << '\n';
}

{ // deque::emplace_back: c++11, Construct and insert element at the end
	std::deque<int> mydeque = { 10, 20, 30 };

	mydeque.emplace_back(100);
	mydeque.emplace_back(200);

	std::cout << "mydeque contains:";
	for (auto& x : mydeque)
		std::cout << ' ' << x;
	std::cout << '\n';
}

{ // deque::emplace_front: c++11, Construct and insert element at beginning
	std::deque<int> mydeque = { 10, 20, 30 };

	mydeque.emplace_front(111);
	mydeque.emplace_front(222);

	std::cout << "mydeque contains:";
	for (auto& x : mydeque)
		std::cout << ' ' << x;
	std::cout << '\n';
}

{ // deque::empty: Test whether container is empty
	std::deque<int> mydeque;
	int sum(0);

	for (int i = 1; i <= 10; i++) mydeque.push_back(i);

	while (!mydeque.empty()) {
		sum += mydeque.front();
		mydeque.pop_front();
	}

	std::cout << "total: " << sum << '\n';
}

{ // deque::erase: Erase elements
	std::deque<int> mydeque;

	// set some values (from 1 to 10)
	for (int i = 1; i <= 10; i++) mydeque.push_back(i);

	// erase the 6th element
	mydeque.erase(mydeque.begin() + 5);

	// erase the first 3 elements:
	mydeque.erase(mydeque.begin(), mydeque.begin() + 3);

	std::cout << "mydeque contains:";
	for (std::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // deque::front: Access first element, Returns a reference to the first element in the deque containe
  // deque::push_front: Inserts a new element at the beginning of the deque container,
  // right before its current first element. The content of val is copied (or moved) to the inserted element
	std::deque<int> mydeque;

	mydeque.push_front(77);
	mydeque.push_back(20);

	mydeque.front() -= mydeque.back();

	std::cout << "mydeque.front() is now " << mydeque.front() << '\n';
}

{ // deque::get_allocator: Returns a copy of the allocator object associated with the deque object
	std::deque<int> mydeque;
	int * p;
	unsigned int i;

	// allocate an array with space for 5 elements using deque's allocator:
	p = mydeque.get_allocator().allocate(5);

	// construct values in-place on the array:
	for (i = 0; i < 5; i++) mydeque.get_allocator().construct(&p[i], i);

	std::cout << "The allocated array contains:";
	for (i = 0; i < 5; i++) std::cout << ' ' << p[i];
	std::cout << '\n';

	// destroy and deallocate:
	for (i = 0; i < 5; i++) mydeque.get_allocator().destroy(&p[i]);
	mydeque.get_allocator().deallocate(p, 5);
}

{ // deque::insert: Insert elements
	std::deque<int> mydeque;

	// set some initial values:
	for (int i = 1; i < 6; i++) mydeque.push_back(i); // 1 2 3 4 5

	std::deque<int>::iterator it = mydeque.begin();
	++it;

	it = mydeque.insert(it, 10);                  // 1 10 2 3 4 5
	// "it" now points to the newly inserted 10

	mydeque.insert(it, 2, 20);                     // 1 20 20 10 2 3 4 5
	// "it" no longer valid!

	it = mydeque.begin() + 2;

	std::vector<int> myvector(2, 30);
	mydeque.insert(it, myvector.begin(), myvector.end());
	// 1 20 30 30 20 10 2 3 4 5

	std::cout << "mydeque contains:";
	for (it = mydeque.begin(); it != mydeque.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // deque::max_size: Return maximum size
	unsigned int i;
	std::deque<int> mydeque;

	std::cout << "Enter number of elements: ";
	i = 100; //std::cin >> i;

	if (i < mydeque.max_size()) mydeque.resize(i);
	else std::cout << "That size exceeds the limit.\n";
	fprintf(stderr, "max size: %d\n", mydeque.max_size());
}

{ // deque::operator=: Assigns new contents to the container, replacing its current contents, and modifying its size accordingly
	std::deque<int> first(3);    // deque with 3 zero-initialized ints
	std::deque<int> second(5);   // deque with 5 zero-initialized ints

	second = first;
	first = std::deque<int>();

	std::cout << "Size of first: " << int(first.size()) << '\n';
	std::cout << "Size of second: " << int(second.size()) << '\n';
}

{ // deque::operator[]: Returns a reference to the element at position n in the deque container
	std::deque<int> mydeque(10);   // 10 zero-initialized elements
	std::deque<int>::size_type sz = mydeque.size();

	// assign some values:
	for (unsigned i = 0; i < sz; i++) mydeque[i] = i;

	// reverse order of elements using operator[]:
	for (unsigned i = 0; i < sz / 2; i++) {
		int temp;
		temp = mydeque[sz - 1 - i];
		mydeque[sz - 1 - i] = mydeque[i];
		mydeque[i] = temp;
	}

	// print content:
	std::cout << "mydeque contains:";
	for (unsigned i = 0; i < sz; i++)
		std::cout << ' ' << mydeque[i];
	std::cout << '\n';
}

{ // deque::pop_back: Removes the last element in the deque container, effectively reducing the container size by one
	std::deque<int> mydeque;
	int sum(0);
	mydeque.push_back(10);
	mydeque.push_back(20);
	mydeque.push_back(30);

	while (!mydeque.empty()) {
		sum += mydeque.back();
		mydeque.pop_back();
	}

	std::cout << "The elements of mydeque add up to " << sum << '\n';
}

{ // deque::pop_front: Removes the first element in the deque container, effectively reducing its size by one.
	std::deque<int> mydeque;

	mydeque.push_back(100);
	mydeque.push_back(200);
	mydeque.push_back(300);

	std::cout << "Popping out the elements in mydeque:";
	while (!mydeque.empty()) {
		std::cout << ' ' << mydeque.front();
		mydeque.pop_front();
	}

	std::cout << "\nThe final size of mydeque is " << int(mydeque.size()) << '\n';
}

{ // deque::rbegin: Returns a reverse iterator pointing to the last element in the container
	// deque::rend: Returns a reverse iterator pointing to the theoretical element preceding the first element in the deque container
	std::deque<int> mydeque(5);  // 5 default-constructed ints

	std::deque<int>::reverse_iterator rit = mydeque.rbegin();

	int i = 0;
	for (rit = mydeque.rbegin(); rit != mydeque.rend(); ++rit)
		*rit = ++i;

	std::cout << "mydeque contains:";
	for (std::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // deque::resize: Resizes the container so that it contains n elements
	std::deque<int> mydeque;
	std::deque<int>::iterator it;

	// set some initial content:
	for (int i = 1; i < 10; ++i) mydeque.push_back(i);

	mydeque.resize(5);
	mydeque.resize(8, 100);
	mydeque.resize(12);

	std::cout << "mydeque contains:";
	for (std::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // deque::shrink_to_fit: c++11, Requests the container to reduce its memory usage to fit its size.
	// deque::size: Returns the number of elements in the deque container
	std::deque<int> mydeque(100);
	std::cout << "1. size of mydeque: " << mydeque.size() << '\n';

	mydeque.resize(10);
	std::cout << "2. size of mydeque: " << mydeque.size() << '\n';

	mydeque.shrink_to_fit();
	fprintf(stderr, "3. size of mydeque: %d\n", mydeque.size());
}

{ // deque::swap: Exchanges the content of the container by the content of x,
	// which is another deque object containing elements of the same type. Sizes may differ.
	unsigned int i;
	std::deque<int> foo(3, 100);   // three ints with a value of 100
	std::deque<int> bar(5, 200);   // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (std::deque<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "bar contains:";
	for (std::deque<int>::iterator it = bar.begin(); it != bar.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // relational operators: compare
	std::deque<int> foo(3, 100);   // three ints with a value of 100
	std::deque<int> bar(2, 200);   // two ints with a value of 200

	if (foo == bar) std::cout << "foo and bar are equal\n";
	if (foo != bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
	if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
}

{ // std::swap: The contents of container x are exchanged with those of y.
  // Both container objects must be of the same type (same template parameters), although sizes may differ
	unsigned int i;
	std::deque<int> foo(3, 100);   // three ints with a value of 100
	std::deque<int> bar(5, 200);   // five ints with a value of 200

	swap(foo, bar);

	std::cout << "foo contains:";
	for (std::deque<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "bar contains:";
	for (std::deque<int>::iterator it = bar.begin(); it != bar.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

	return 0;
}

