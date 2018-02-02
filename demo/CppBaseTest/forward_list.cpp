#include "forward_list.hpp"
#include <iostream>
#include <forward_list>
#include <array>
#include <functional>
#include <cmath>

// Blog: http://blog.csdn.net/fengbingchun/article/details/72858282

///////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/forward_list/forward_list/
template<class Container>
static Container by_two(const Container& x)
{
	Container temp(x);
	for (auto& x : temp) x *= 2;
	return temp;
}

// a predicate implemented as a function:
static bool single_digit(const int& value) { return (value<10); }

// a predicate implemented as a class:
class is_odd_class
{
public:
	bool operator() (const int& value) { return (value % 2) == 1; }
} is_odd_object;

// a binary predicate implemented as a function:
static bool same_integral_part(double first, double second)
{
	return (int(first) == int(second));
}

// a binary predicate implemented as a class:
class is_near_class
{
public:
	bool operator() (double first, double second)
	{
		return (fabs(first - second)<5.0);
	}
} is_near_object;

int test_forward_list_1()
{
{ // forward_list::forward_list: Constructs a forward_list container object,
  // initializing its contents depending on the constructor version used
	std::forward_list<int> first;                      // default: empty
	std::forward_list<int> second(3, 77);              // fill: 3 seventy-sevens
	std::forward_list<int> third(second.begin(), second.end()); // range initialization
	std::forward_list<int> fourth(third);            // copy constructor
	std::forward_list<int> fifth(std::move(fourth));  // move ctor. (fourth wasted)
	std::forward_list<int> sixth = { 3, 52, 25, 90 };    // initializer_list constructor

	std::cout << "first:"; for (int& x : first)  std::cout << " " << x; std::cout << '\n';
	std::cout << "second:"; for (int& x : second) std::cout << " " << x; std::cout << '\n';
	std::cout << "third:";  for (int& x : third)  std::cout << " " << x; std::cout << '\n';
	std::cout << "fourth:"; for (int& x : fourth) std::cout << " " << x; std::cout << '\n';
	std::cout << "fifth:";  for (int& x : fifth)  std::cout << " " << x; std::cout << '\n';
	std::cout << "sixth:";  for (int& x : sixth)  std::cout << " " << x; std::cout << '\n';
}

{ // forward_list::assign: Assigns new contents to the forward_list container,
  // replacing its current contents, and modifying its size accordingly
	std::forward_list<int> first;
	std::forward_list<int> second;

	first.assign(4, 15);                           // 15 15 15 15

	second.assign(first.begin(), first.end());     // 15 15 15 15

	first.assign({ 77, 2, 16 });                  // 77 2 16

	std::cout << "first contains: ";
	for (int& x : first) std::cout << ' ' << x;
	std::cout << '\n';

	std::cout << "second contains: ";
	for (int& x : second) std::cout << ' ' << x;
	std::cout << '\n';
}

{ // forward_list::before_begin: Returns an iterator pointing to the position before the first element in the container.
  // forward_list::cbefore_begin: Returns a const_iterator pointing to the position before the first element in the container.
	std::forward_list<int> mylist = { 20, 30, 40, 50 };

	mylist.insert_after(mylist.before_begin(), 11);
	mylist.insert_after(mylist.cbefore_begin(), 19);

	std::cout << "mylist contains:";
	for (int& x : mylist) std::cout << ' ' << x;
	std::cout << '\n';
}

{ // forward_list::begin: Returns an iterator pointing to the first element in the forward_list container.
  // forward_list::cbegin: Returns a const_iterator pointing to the first element in the container.
  // forward_list::end: Returns an iterator referring to the past-the-end element in the forward_list container
  // forward_list::cend: Returns a const_iterator pointing to the past-the-end element in the forward_list container
	std::forward_list<int> mylist = { 34, 77, 16, 2 };

	std::cout << "mylist contains:";
	for (auto it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	for (auto it = mylist.cbegin(); it != mylist.cend(); ++it)
		std::cout << ' ' << *it;   // cannot modify *it
	std::cout << '\n';
}

{ // forward_list::clear: Removes all elements from the forward_list container (which are destroyed),
  // and leaving the container with a size of 0
	std::forward_list<int> mylist = { 10, 20, 30 };

	std::cout << "mylist contains:";
	for (int& x : mylist) std::cout << ' ' << x;
	std::cout << '\n';

	mylist.clear();
	mylist.insert_after(mylist.before_begin(), { 100, 200 });

	std::cout << "mylist contains:";
	for (int& x : mylist) std::cout << ' ' << x;
	std::cout << '\n';
}

{ // forward_list::emplace_after: The container is extended by inserting a new element after the element at position.
  // This new element is constructed in place using args as the arguments for its construction.
  // forward_list::emplace_front: Inserts a new element at the beginning of the forward_list, right before its current first element.
  // This new element is constructed in place using args as the arguments for its construction.
	std::forward_list< std::pair<int, char> > mylist;
	auto it = mylist.before_begin();

	it = mylist.emplace_after(it, 100, 'x');
	it = mylist.emplace_after(it, 200, 'y');
	it = mylist.emplace_after(it, 300, 'z');

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
	std::cout << '\n';
}

{ // forward_list::empty: Returns a bool value indicating whether the forward_list container is empty, i.e. whether its size is 0
	std::forward_list<int> first;
	std::forward_list<int> second = { 20, 40, 80 };
	std::cout << "first " << (first.empty() ? "is empty" : "is not empty") << std::endl;
	std::cout << "second " << (second.empty() ? "is empty" : "is not empty") << std::endl;
}

{ // forward_list::erase_after: Removes from the forward_list container either a single element (the one after position) or a range of elements 
	std::forward_list<int> mylist = { 10, 20, 30, 40, 50 };

						  // 10 20 30 40 50
	auto it = mylist.begin();                 // ^

	it = mylist.erase_after(it);              // 10 30 40 50
						  //    ^
	it = mylist.erase_after(it, mylist.end()); // 10 30
						   //       ^

	std::cout << "mylist contains:";
	for (int& x : mylist) std::cout << ' ' << x;
	std::cout << '\n';
}

{ // forward_list::front: Returns a reference to the first element in the forward_list container.
	std::forward_list<int> mylist = { 2, 16, 77 };

	mylist.front() = 11;

	std::cout << "mylist now contains:";
	for (int& x : mylist) std::cout << ' ' << x;

	std::cout << '\n';
}

{ // forward_list::insert_after: The container is extended by inserting new elements after the element at position
	std::array<int, 3> myarray = { 11, 22, 33 };
	std::forward_list<int> mylist;
	std::forward_list<int>::iterator it;

	it = mylist.insert_after(mylist.before_begin(), 10);          // 10
								      //  ^  <- it
	it = mylist.insert_after(it, 2, 20);                          // 10 20 20
								      //        ^
	it = mylist.insert_after(it, myarray.begin(), myarray.end()); // 10 20 20 11 22 33
								      //                 ^
	it = mylist.begin();                                             //  ^
	it = mylist.insert_after(it, { 1, 2, 3 });                        // 10 1 2 3 20 20 11 22 33
									  //        ^

	std::cout << "mylist contains:";
	for (int& x : mylist) std::cout << ' ' << x;
	std::cout << '\n';
}

{ // forward_list::max_size: Returns the maximum number of elements that the forward_list container can hold
	std::forward_list<int> mylist = { 2, 16, 77 };
	std::cout << "mylist max size:" << mylist.max_size() << std::endl;
}

{ // forward_list::merge: Merges x into the forward_list by transferring all of its elements at their respective ordered positions
  // into the container (both containers shall already be ordered)
  // forward_list::sort: Sorts the elements in the forward_list, altering their position within the container
	std::forward_list<double> first = { 4.2, 2.9, 3.1 };
	std::forward_list<double> second = { 1.4, 7.7, 3.1 };
	std::forward_list<double> third = { 6.2, 3.7, 7.1 };

	first.sort();
	second.sort();
	first.merge(second);

	std::cout << "first contains:";
	for (double& x : first) std::cout << " " << x;
	std::cout << std::endl;

	first.sort(std::greater<double>());
	third.sort(std::greater<double>());
	first.merge(third, std::greater<double>());

	std::cout << "first contains:";
	for (double& x : first) std::cout << " " << x;
	std::cout << std::endl;
}

{ // forward_list::operator=: Assigns new contents to the container, replacing its current contents
	std::forward_list<int> first(4);      // 4 ints
	std::forward_list<int> second(3, 5);   // 3 ints with value 5

	first = second;                        // copy assignment
	second = by_two(first);                // move assignment

	std::cout << "first: ";
	for (int& x : first) std::cout << ' ' << x;
	std::cout << '\n';

	std::cout << "second: ";
	for (int& x : second) std::cout << ' ' << x;
	std::cout << '\n';
}

{ // forward_list::pop_front: Removes the first element in the forward_list container, effectively reducing its size by one.
	std::forward_list<int> mylist = { 10, 20, 30, 40 };

	std::cout << "Popping out the elements in mylist:";
	while (!mylist.empty()) {
		std::cout << ' ' << mylist.front();
		mylist.pop_front();
	}

	std::cout << '\n';
}

{ // forward_list::push_front: Inserts a new element at the beginning of the forward_list, right before its current first element.
  // The content of val is copied (or moved) to the inserted element
	using namespace std;

	forward_list<int> mylist = { 77, 2, 16 };
	mylist.push_front(19);
	mylist.push_front(34);

	std::cout << "mylist contains:";
	for (int& x : mylist) std::cout << ' ' << x;
	std::cout << '\n';
}

{ // forward_list::remove: Removes from the container all the elements that compare equal to val.
  // This calls the destructor of these objects and reduces the container size by the number of elements removed
	std::forward_list<int> mylist = { 10, 20, 30, 40, 30, 20, 10 };

	mylist.remove(20);

	std::cout << "mylist contains:";
	for (int& x : mylist) std::cout << ' ' << x;
	std::cout << '\n';
}

{ // forward_list::remove_if: Removes from the container all the elements for which Predicate pred returns true.
  // This calls the destructor of these objects and reduces the container size by the number of elements removed.
	std::forward_list<int> mylist = { 7, 80, 7, 15, 85, 52, 6 };

	mylist.remove_if(single_digit);      // 80 15 85 52

	mylist.remove_if(is_odd_object);     // 80 52

	std::cout << "mylist contains:";
	for (int& x : mylist) std::cout << ' ' << x;
	std::cout << '\n';
}

{ // forward_list::resize: Resizes the container to contain n elements
	std::forward_list<int> mylist = { 10, 20, 30, 40, 50 };
				      // 10 20 30 40 50
	mylist.resize(3);             // 10 20 30
	mylist.resize(5, 100);        // 10 20 30 100 100

	std::cout << "mylist contains:";
	for (int& x : mylist) std::cout << ' ' << x;
	std::cout << '\n';
}

{ // forward_list::reverse: Reverses the order of the elements in the forward_list container.
	std::forward_list<int> mylist = { 10, 20, 30, 40 };

	mylist.reverse();

	std::cout << "mylist contains:";
	for (int& x : mylist) std::cout << ' ' << x;
	std::cout << '\n';
}

{ // forward_list::splice_after: Transfers elements from fwdlst into the container inserting them after the element pointed by position.
	std::forward_list<int> first = { 1, 2, 3 };
	std::forward_list<int> second = { 10, 20, 30 };

	auto it = first.begin();  // points to the 1

	first.splice_after(first.before_begin(), second);
	// first: 10 20 30 1 2 3
	// second: (empty)
	// "it" still points to the 1 (now first's 4th element)

	second.splice_after(second.before_begin(), first, first.begin(), it);
	// first: 10 1 2 3
	// second: 20 30

	first.splice_after(first.before_begin(), second, second.begin());
	// first: 30 10 1 2 3
	// second: 20
	// * notice that what is moved is AFTER the iterator

	std::cout << "first contains:";
	for (int& x : first) std::cout << " " << x;
	std::cout << std::endl;

	std::cout << "second contains:";
	for (int& x : second) std::cout << " " << x;
	std::cout << std::endl;
}

{ // forward_list::swap: Exchanges the content of the container by the content of fwdlst,
	// which is another forward_list object of the same type. Sizes may differ
	std::forward_list<int> first = { 10, 20, 30 };
	std::forward_list<int> second = { 100, 200 };
	std::forward_list<int>::iterator it;

	first.swap(second);
	std::swap(first, second);

	std::cout << "first contains:";
	for (int& x : first) std::cout << ' ' << x;
	std::cout << '\n';

	std::cout << "second contains:";
	for (int& x : second) std::cout << ' ' << x;
	std::cout << '\n';
}

{ // forward_list::unique: Remove duplicate values
	std::forward_list<double> mylist = { 15.2, 73.0, 3.14, 15.85, 69.5,
					     73.0, 3.99, 15.2, 69.2, 18.5 };

	mylist.sort();                       //   3.14,  3.99, 15.2, 15.2, 15.85
					     //  18.5,  69.2,  69.5, 73.0, 73.0

	mylist.unique();                     //   3.14,  3.99, 15.2, 15.85
					      //  18.5,  69.2,  69.5, 73.0

	mylist.unique(same_integral_part);  //  3.14, 15.2, 18.5,  69.2, 73.0

	mylist.unique(is_near_object);      //  3.14, 15.2, 69.2

	std::cout << "mylist contains:";
	for (double& x : mylist) std::cout << ' ' << x;
	std::cout << '\n';
}

{ // Performs the appropriate comparison operation between the forward_list containers lhs and rhs.
	std::forward_list<int> a = { 10, 20, 30 };
	std::forward_list<int> b = { 10, 20, 30 };
	std::forward_list<int> c = { 30, 20, 10 };

	if (a == b) std::cout << "a and b are equal\n";
	if (b != c) std::cout << "b and c are not equal\n";
	if (b<c) std::cout << "b is less than c\n";
	if (c>b) std::cout << "c is greater than b\n";
	if (a <= b) std::cout << "a is less than or equal to b\n";
	if (a >= b) std::cout << "a is greater than or equal to b\n";
}

{ // get forward_list elements size
	std::forward_list<int> a = { 10, 20, 30 };

	size_t size = std::distance(a.begin(), a.end());
	std::cout << "a size: " << size << std::endl;
}

	return 0;
}

