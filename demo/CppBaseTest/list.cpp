#include "list.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <cmath>

// Blog: http://blog.csdn.net/fengbingchun/article/details/72859402

//////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/list/list/
// compare only integral part:
static bool mycomparison(double first, double second)
{
	return (int(first)<int(second));
}

// comparison, not case sensitive.
static bool compare_nocase(const std::string& first, const std::string& second)
{
	unsigned int i = 0;
	while ((i<first.length()) && (i<second.length())) {
		if (tolower(first[i])<tolower(second[i])) return true;
		else if (tolower(first[i])>tolower(second[i])) return false;
		++i;
	}
	return (first.length() < second.length());
}

// a predicate implemented as a function:
static bool single_digit(const int& value) { return (value<10); }

// a predicate implemented as a class:
struct is_odd {
	bool operator() (const int& value) { return (value % 2) == 1; }
};

// a binary predicate implemented as a function:
static bool same_integral_part(double first, double second)
{
	return (int(first) == int(second));
}

// a binary predicate implemented as a class:
struct is_near {
	bool operator() (double first, double second)
	{
		return (fabs(first - second)<5.0);
	}
};

int test_list_1()
{
{ // list::list: Constructs a list container object, initializing its contents depending on the constructor version used
	std::list<int> first;                                // empty list of ints
	std::list<int> second(4, 100);                       // four ints with value 100
	std::list<int> third(second.begin(), second.end());  // iterating through second
	std::list<int> fourth(third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = { 16, 2, 77, 29 };
	std::list<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

	std::cout << "The contents of fifth are: ";
	for (std::list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
}

{ // list::assign: Assigns new contents to the list container, replacing its current contents, and modifying its size accordingly
  // list::size: Returns the number of elements in the list container.
	std::list<int> first;
	std::list<int> second;

	first.assign(7, 100);                      // 7 ints with value 100

	second.assign(first.begin(), first.end()); // a copy of first

	int myints[] = { 1776, 7, 4 };
	first.assign(myints, myints + 3);            // assigning from array

	std::cout << "Size of first: " << int(first.size()) << '\n';
	std::cout << "Size of second: " << int(second.size()) << '\n';
}

{ // list::back: Returns a reference to the last element in the list container
  // list::front: Returns a reference to the first element in the list container.
	std::list<int> mylist;

	mylist.push_back(10);

	while (mylist.back() != 0) {
		mylist.push_back(mylist.back() - 1);
	}

	std::cout << "mylist contains:";
	for (std::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	mylist.push_back(77);
	mylist.push_back(22);

	mylist.front() -= mylist.back();
	std::cout << "mylist.front() is now " << mylist.front() << '\n';

}

{ // list::begin: Returns an iterator pointing to the first element in the list container
  // list::cbegin: C++11, Returns a const_iterator pointing to the first element in the container
  // list::crbegin: C++11, Returns a const_reverse_iterator pointing to the last element in the container (i.e., its reverse beginning)
  // list::rbegin: Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
  // list::end: Returns an iterator referring to the past-the-end element in the list container
  // list::cend: C++11, Returns a const_iterator pointing to the past-the-end element in the container
  // list::crend: C++11, Returns a const_reverse_iterator pointing to the theoretical element
  // preceding the first element in the container (which is considered its reverse end)
  // list::rend: Returns a reverse iterator pointing to the theoretical element preceding the first element
  // in the list container (which is considered its reverse end).
	int myints[] = { 75, 23, 65, 42, 13 };
	std::list<int> mylist(myints, myints + 5);

	std::cout << "mylist contains:";
	for (std::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	for (auto it = mylist.cbegin(); it != mylist.cend(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	for (auto rit = mylist.crbegin(); rit != mylist.crend(); ++rit)
		std::cout << ' ' << *rit;
	std::cout << '\n';

	std::cout << "mylist backwards:";
	for (std::list<int>::reverse_iterator rit = mylist.rbegin(); rit != mylist.rend(); ++rit)
		std::cout << ' ' << *rit;
	std::cout << '\n';
}

{ // list::clear: Removes all elements from the list container (which are destroyed),
  // and leaving the container with a size of 0
	std::list<int> mylist;
	std::list<int>::iterator it;

	mylist.push_back(100);
	mylist.push_back(200);
	mylist.push_back(300);

	std::cout << "mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	mylist.clear();
	mylist.push_back(1101);
	mylist.push_back(2202);

	std::cout << "mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // list::emplace: C++11, The container is extended by inserting a new element at position.
  // This new element is constructed in place using args as the arguments for its construction.
  // list::emplace_back: C++11, Inserts a new element at the end of the list, right after its current last element.
  // This new element is constructed in place using args as the arguments for its construction.
  // list::emplace_front: Inserts a new element at the beginning of the list, right before its current first element.
  // This new element is constructed in place using args as the arguments for its construction.
	std::list< std::pair<int, char> > mylist;

	mylist.emplace(mylist.begin(), 100, 'x');
	mylist.emplace(mylist.begin(), 200, 'y');

	std::cout << "mylist contains:";
	for (auto& x : mylist)
		std::cout << " (" << x.first << "," << x.second << ")";
	std::cout << '\n';

	mylist.emplace_back(10, 'a');
	mylist.emplace_back(20, 'b');
	mylist.emplace_back(30, 'c');

	std::cout << "mylist contains:";
	for (auto& x : mylist)
		std::cout << " (" << x.first << "," << x.second << ")";
	std::cout << std::endl;

	mylist.emplace_front(10, 'a');
	mylist.emplace_front(20, 'b');
	mylist.emplace_front(30, 'c');

	std::cout << "mylist contains:";
	for (auto& x : mylist)
		std::cout << " (" << x.first << "," << x.second << ")";
	std::cout << std::endl;
}

{ // list::empty: Returns whether the list container is empty (i.e. whether its size is 0).
	std::list<int> mylist;
	int sum(0);

	for (int i = 1; i <= 10; ++i) mylist.push_back(i);

	while (!mylist.empty()) {
		sum += mylist.front();
		mylist.pop_front();
	}

	std::cout << "total: " << sum << '\n';
}

{ // list::erase: Removes from the list container either a single element (position) or a range of elements ([first,last)).
	std::list<int> mylist;
	std::list<int>::iterator it1, it2;

	// set some values:
	for (int i = 1; i<10; ++i) mylist.push_back(i * 10);

				    // 10 20 30 40 50 60 70 80 90
	it1 = it2 = mylist.begin(); // ^^
	std::advance(it2, 6);            // ^                 ^
	++it1;                      //    ^              ^

	it1 = mylist.erase(it1);   // 10 30 40 50 60 70 80 90
				   //    ^           ^

	it2 = mylist.erase(it2);   // 10 30 40 50 60 80 90
				   //    ^           ^

	++it1;                      //       ^        ^
	--it2;                      //       ^     ^

	mylist.erase(it1, it2);     // 10 30 60 80 90
				    //        ^

	std::cout << "mylist contains:";
	for (it1 = mylist.begin(); it1 != mylist.end(); ++it1)
		std::cout << ' ' << *it1;
	std::cout << '\n';
}

{ // list::get_allocator: Returns a copy of the allocator object associated with the list container
	std::list<int> mylist;
	int * p;

	// allocate an array of 5 elements using mylist's allocator:
	p = mylist.get_allocator().allocate(5);

	// assign some values to array
	for (int i = 0; i<5; ++i) p[i] = i;

	std::cout << "The allocated array contains:";
	for (int i = 0; i<5; ++i) std::cout << ' ' << p[i];
	std::cout << '\n';

	mylist.get_allocator().deallocate(p, 5);
}

{ // list::insert: The container is extended by inserting new elements before the element at the specified position
	std::list<int> mylist;
	std::list<int>::iterator it;

	// set some initial values:
	for (int i = 1; i <= 5; ++i) mylist.push_back(i); // 1 2 3 4 5

	it = mylist.begin();
	++it;           // it points now to number 2           ^

	mylist.insert(it, 10);                        // 1 10 2 3 4 5

	// "it" still points to number 2                      ^
	mylist.insert(it, 2, 20);                      // 1 10 20 20 2 3 4 5

	--it;         // it points now to the second 20            ^

	std::vector<int> myvector(2, 30);
	mylist.insert(it, myvector.begin(), myvector.end());
						       // 1 10 20 30 30 20 2 3 4 5
						       //               ^
	std::cout << "mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // list::max_size: Returns the maximum number of elements that the list container can hold.
  // list::resize: Resizes the container so that it contains n elements
  // list::size_type: A type that counts the number of elements in a list.
	unsigned int i;
	std::list<int> mylist;

	i = 111111;

	if (i<mylist.max_size()) mylist.resize(i);
	else std::cout << "That size exceeds the limit.\n";

	std::list <int>::size_type ii;
	ii = mylist.max_size();
	std::cout << "Maximum possible length of the list is " << ii << "." << std::endl;
}

{ // list::merge: Merges x into the list by transferring all of its elements at their respective ordered positions
  // into the container (both containers shall already be ordered).
	std::list<double> first, second;

	first.push_back(3.1);
	first.push_back(2.2);
	first.push_back(2.9);

	second.push_back(3.7);
	second.push_back(7.1);
	second.push_back(1.4);

	first.sort();
	second.sort();

	first.merge(second);

	// (second is now empty)

	second.push_back(2.1);

	first.merge(second, mycomparison);

	std::cout << "first contains:";
	for (std::list<double>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // list::sort: Sorts the elements in the list, altering their position within the container
	std::list<std::string> mylist;
	std::list<std::string>::iterator it;
	mylist.push_back("one");
	mylist.push_back("two");
	mylist.push_back("Three");

	mylist.sort();

	std::cout << "mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	mylist.sort(compare_nocase);

	std::cout << "mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // list::operator=: Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
	std::list<int> first(3);      // list of 3 zero-initialized ints
	std::list<int> second(5);     // list of 5 zero-initialized ints

	second = first;
	first = std::list<int>();

	std::cout << "Size of first: " << int(first.size()) << '\n';
	std::cout << "Size of second: " << int(second.size()) << '\n';
}

{ // list::push_back: Adds a new element at the end of the list container, after its current last element.
  // list::push_front: Inserts a new element at the beginning of the list, right before its current first element.
  // list::pop_back: Removes the last element in the list container, effectively reducing the container size by one.
  // list::pop_front: Removes the first element in the list container, effectively reducing its size by on
	std::list<int> mylist;
	int sum(0);
	mylist.push_back(100);
	mylist.push_back(200);
	mylist.push_back(300);

	while (!mylist.empty()) {
		sum += mylist.back();
		mylist.pop_back();
	}

	std::cout << "The elements of mylist summed " << sum << '\n';

	mylist.push_back(100);
	mylist.push_back(200);
	mylist.push_back(300);

	mylist.push_front(200);
	mylist.push_front(300);

	std::cout << "Popping out the elements in mylist:";
	while (!mylist.empty()) {
		std::cout << ' ' << mylist.front();
		mylist.pop_front();
	}

	std::cout << "\nFinal size of mylist is " << mylist.size() << '\n';
}

{ // list::remove: Removes from the container all the elements that compare equal to val.
  // This calls the destructor of these objects and reduces the container size by the number of elements removed.
  // list::remove_if: Removes from the container all the elements for which Predicate pred returns true.
  // This calls the destructor of these objects and reduces the container size by the number of elements removed.
	int myints[] = { 89, 15, 36, 7, 17, 20, 39, 4, 1 };
	std::list<int> mylist(myints, myints + 9);

	mylist.remove(89);

	std::cout << "mylist contains:";
	for (std::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	mylist.remove_if(single_digit);           // 15 36 17 20 39
	mylist.remove_if(is_odd());               // 36 20

	std::cout << "mylist contains:";
	for (std::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // list::reverse: reverses the order of the elements in the list container.
	std::list<int> mylist;

	for (int i = 1; i<10; ++i) mylist.push_back(i);

	mylist.reverse();

	std::cout << "mylist contains:";
	for (std::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // list::splice: Transfers elements from x into the container, inserting them at position
	std::list<int> mylist1, mylist2;
	std::list<int>::iterator it;

	// set some initial values:
	for (int i = 1; i <= 4; ++i)
		mylist1.push_back(i);      // mylist1: 1 2 3 4

	for (int i = 1; i <= 3; ++i)
		mylist2.push_back(i * 10);   // mylist2: 10 20 30

	it = mylist1.begin();
	++it;                         // points to 2

	mylist1.splice(it, mylist2); // mylist1: 1 10 20 30 2 3 4
	// mylist2 (empty)
	// "it" still points to 2 (the 5th element)

	mylist2.splice(mylist2.begin(), mylist1, it);
	// mylist1: 1 10 20 30 3 4
	// mylist2: 2
	// "it" is now invalid.
	it = mylist1.begin();
	std::advance(it, 3);           // "it" points now to 30

	mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
	// mylist1: 30 3 4 1 10 20

	std::cout << "mylist1 contains:";
	for (it = mylist1.begin(); it != mylist1.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "mylist2 contains:";
	for (it = mylist2.begin(); it != mylist2.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // list::swap: Exchanges the content of the container by the content of x,
  // which is another list of the same type. Sizes may differ.
	std::list<int> first(3, 100);   // three ints with a value of 100
	std::list<int> second(5, 200);  // five ints with a value of 200

	first.swap(second);
	std::swap(first, second);

	std::cout << "first contains:";
	for (std::list<int>::iterator it = first.begin(); it != first.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second contains:";
	for (std::list<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // list::unique: Remove duplicate values
	double mydoubles[] = { 12.15, 2.72, 73.0, 12.77, 3.14,
			       12.77, 73.35, 72.25, 15.3, 72.25 };
	std::list<double> mylist(mydoubles, mydoubles + 10);

	mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
				   // 15.3,  72.25, 72.25, 73.0,  73.35

	mylist.unique();           //  2.72,  3.14, 12.15, 12.77
				    // 15.3,  72.25, 73.0,  73.35

	mylist.unique(same_integral_part);  //  2.72,  3.14, 12.15
					    // 15.3,  72.25, 73.0

	mylist.unique(is_near());           //  2.72, 12.15, 72.25

	std::cout << "mylist contains:";
	for (std::list<double>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // Performs the appropriate comparison operation between the list containers lhs and rhs
	std::list<int> a = { 10, 20, 30 };
	std::list<int> b = { 10, 20, 30 };
	std::list<int> c = { 30, 20, 10 };

	if (a == b) std::cout << "a and b are equal\n";
	if (b != c) std::cout << "b and c are not equal\n";
	if (b<c) std::cout << "b is less than c\n";
	if (c>b) std::cout << "c is greater than b\n";
	if (a <= b) std::cout << "a is less than or equal to b\n";
	if (a >= b) std::cout << "a is greater than or equal to b\n";
}

	return 0;
}

//////////////////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/802d66bt.aspx
int test_list_2()
{
	using namespace std;
	// Create an empty list c0  
	list <int> c0;

	// Create a list c1 with 3 elements of default value 0  
	list <int> c1(3);

	// Create a list c2 with 5 elements of value 2  
	list <int> c2(5, 2);

	// Create a list c3 with 3 elements of value 1 and with the   
	// allocator of list c2  
	list <int> c3(3, 1, c2.get_allocator());

	// Create a copy, list c4, of list c2  
	list <int> c4(c2);

	// Create a list c5 by copying the range c4[ first,  last)  
	list <int>::iterator c4_Iter = c4.begin();
	c4_Iter++;
	c4_Iter++;
	list <int> c5(c4.begin(), c4_Iter);

	// Create a list c6 by copying the range c4[ first,  last) and with   
	// the allocator of list c2  
	c4_Iter = c4.begin();
	c4_Iter++;
	c4_Iter++;
	c4_Iter++;
	list <int> c6(c4.begin(), c4_Iter, c2.get_allocator());

	cout << "c1 =";
	for (auto c : c1)
		cout << " " << c;
	cout << endl;

	cout << "c2 =";
	for (auto c : c2)
		cout << " " << c;
	cout << endl;

	cout << "c3 =";
	for (auto c : c3)
		cout << " " << c;
	cout << endl;

	cout << "c4 =";
	for (auto c : c4)
		cout << " " << c;
	cout << endl;

	cout << "c5 =";
	for (auto c : c5)
		cout << " " << c;
	cout << endl;

	cout << "c6 =";
	for (auto c : c6)
		cout << " " << c;
	cout << endl;

	// Move list c6 to list c7  
	list <int> c7(move(c6));
	cout << "c7 =";
	for (auto c : c7)
		cout << " " << c;
	cout << endl;

	// Construct with initializer_list  
	list<int> c8({ 1, 2, 3, 4 });
	cout << "c8 =";
	for (auto c : c8)
		cout << " " << c;
	cout << endl;

	return 0;
}
