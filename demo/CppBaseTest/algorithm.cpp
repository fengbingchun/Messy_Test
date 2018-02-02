#include "algorithm.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <cctype>
#include <array>
#include <ctime>
#include <cstdlib>
#include <string>
#include <random>
#include <chrono>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78034969

// reference: http://www.cplusplus.com/reference/algorithm/

namespace algorithm_ {

///////////////////////////////////////
static bool myfunction(int i, int j) { return (i == j); }
static bool comp_case_insensitive(char c1, char c2) { return (std::tolower(c1) == std::tolower(c2)); }
static bool IsOdd(int i) { return ((i % 2) == 1); }

int test_algorithm_find()
{
{
	int myints[] = { 5, 20, 5, 30, 30, 20, 10, 10, 20 };
	std::vector<int> myvector(myints, myints + 8);
	std::vector<int>::iterator it;

	// using default comparison:
	it = std::adjacent_find(myvector.begin(), myvector.end());

	if (it != myvector.end())
		std::cout << "the first pair of repeated elements are: " << *it << '\n'; // 30

	//using predicate comparison:
	it = std::adjacent_find(++it, myvector.end(), myfunction);

	if (it != myvector.end())
		std::cout << "the second pair of repeated elements are: " << *it << '\n'; // 10
}

{
	// using std::find with array and pointer:
	int myints[] = { 10, 20, 30, 40 };
	int * p;

	p = std::find(myints, myints + 4, 30);
	if (p != myints + 4)
		std::cout << "Element found in myints: " << *p << '\n'; // 30
	else
		std::cout << "Element not found in myints\n";

	// using std::find with vector and iterator:
	std::vector<int> myvector(myints, myints + 4);
	std::vector<int>::iterator it;

	it = std::find(myvector.begin(), myvector.end(), 30);
	if (it != myvector.end())
		std::cout << "Element found in myvector: " << *it << '\n'; // 30
	else
		std::cout << "Element not found in myvector\n";
}

{
	int myints[] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };
	std::vector<int> haystack(myints, myints + 10);

	int needle1[] = { 1, 2, 3 };

	// using default comparison:
	std::vector<int>::iterator it;
	it = std::find_end(haystack.begin(), haystack.end(), needle1, needle1 + 3);

	if (it != haystack.end())
		std::cout << "needle1 last found at position " << (it - haystack.begin()) << '\n'; // 5

	int needle2[] = { 4, 5, 1 };

	// using predicate comparison:
	it = std::find_end(haystack.begin(), haystack.end(), needle2, needle2 + 3, myfunction);

	if (it != haystack.end())
		std::cout << "needle2 last found at position " << (it - haystack.begin()) << '\n'; // 3
}

{
	int mychars[] = { 'a', 'b', 'c', 'A', 'B', 'C' };
	std::vector<char> haystack(mychars, mychars + 6);
	std::vector<char>::iterator it;

	int needle[] = { 'A', 'B', 'C' };

	// using default comparison:
	it = find_first_of(haystack.begin(), haystack.end(), needle, needle + 3);

	if (it != haystack.end())
		std::cout << "The first match is: " << *it << '\n'; // A

	// using predicate comparison:
	it = find_first_of(haystack.begin(), haystack.end(), needle, needle + 3, comp_case_insensitive);

	if (it != haystack.end())
		std::cout << "The first match is: " << *it << '\n'; // a
}

{
	std::vector<int> myvector;

	myvector.push_back(10);
	myvector.push_back(25);
	myvector.push_back(40);
	myvector.push_back(55);

	std::vector<int>::iterator it = std::find_if(myvector.begin(), myvector.end(), IsOdd);
	std::cout << "The first odd value is " << *it << '\n'; // 25
}

{
	std::array<int, 5> foo = { 1, 2, 3, 4, 5 };

	std::array<int, 5>::iterator it = std::find_if_not(foo.begin(), foo.end(), [](int i){return i % 2; });
	std::cout << "The first even value is " << *it << '\n'; // 2
}

	return 0;
}

////////////////////////////////////////////
int test_algorithm_all_of()
{
{
	std::array<int, 8> foo = { 3, 5, 7, 11, 13, 17, 19, 23 };

	if (std::all_of(foo.begin(), foo.end(), [](int i){return i % 2; }))
		std::cout << "All the elements are odd numbers.\n"; // All the elements are odd numbers
}

{
	std::array<int, 7> foo = { 0, 1, -1, 3, -3, 5, -5 };

	if (std::any_of(foo.begin(), foo.end(), [](int i){return i<0; }))
		std::cout << "There are negative elements in the range.\n"; // There are negative elements in the range
}

{
	std::array<int, 8> foo = { 1, 2, 4, 8, 16, 32, 64, 128 };

	if (std::none_of(foo.begin(), foo.end(), [](int i){return i<0; }))
		std::cout << "There are no negative elements in the range.\n"; // There are no negative elements in the range
}

	return 0;
}

////////////////////////////////////////////////
static bool myfunction2(int i, int j) { return (i<j); }
static bool mypredicate(int i, int j) { return (i == j); }

int test_algorithm_search()
{
{
	int myints[] = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };
	std::vector<int> v(myints, myints + 9);

	// using default comparison:
	std::sort(v.begin(), v.end());

	std::cout << "looking for a 3... ";
	if (std::binary_search(v.begin(), v.end(), 3)) std::cout << "found!\n"; // found!
	else std::cout << "not found.\n";

	// using myfunction as comp:
	std::sort(v.begin(), v.end(), myfunction2);

	std::cout << "looking for a 6... ";
	if (std::binary_search(v.begin(), v.end(), 6, myfunction2)) std::cout << "found!\n";
	else std::cout << "not found.\n"; // not found.
}

{
	std::vector<int> haystack;

	// set some values:        haystack: 10 20 30 40 50 60 70 80 90
	for (int i = 1; i<10; i++) haystack.push_back(i * 10);

	// using default comparison:
	int needle1[] = { 40, 50, 60, 70 };
	std::vector<int>::iterator it;
	it = std::search(haystack.begin(), haystack.end(), needle1, needle1 + 4);

	if (it != haystack.end())
		std::cout << "needle1 found at position " << (it - haystack.begin()) << '\n'; // 3
	else
		std::cout << "needle1 not found\n";

	// using predicate comparison:
	int needle2[] = { 20, 30, 50 };
	it = std::search(haystack.begin(), haystack.end(), needle2, needle2 + 3, mypredicate);

	if (it != haystack.end())
		std::cout << "needle2 found at position " << (it - haystack.begin()) << '\n';
	else
		std::cout << "needle2 not found\n"; // needle2 not found
}

{
	int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };
	std::vector<int> myvector(myints, myints + 8);

	std::vector<int>::iterator it;

	// using default comparison:
	it = std::search_n(myvector.begin(), myvector.end(), 2, 30);

	if (it != myvector.end())
		std::cout << "two 30s found at position " << (it - myvector.begin()) << '\n'; // 2
	else
		std::cout << "match not found\n";

	// using predicate comparison:
	it = std::search_n(myvector.begin(), myvector.end(), 2, 10, mypredicate);

	if (it != myvector.end())
		std::cout << "two 10s found at position " << int(it - myvector.begin()) << '\n'; // 5
	else
		std::cout << "match not found\n";
}

	return 0;
}

//////////////////////////////////////////////
int test_algorithm_copy()
{
{
	int myints[] = { 10, 20, 30, 40, 50, 60, 70 };
	std::vector<int> myvector(7);

	std::copy(myints, myints + 7, myvector.begin());

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 10 20 30 40 50 60 70

	std::cout << '\n';
}

{
	std::vector<int> myvector;

	// set some values:
	for (int i = 1; i <= 5; i++)
		myvector.push_back(i * 10);          // myvector: 10 20 30 40 50

	myvector.resize(myvector.size() + 3);  // allocate space for 3 more elements

	std::copy_backward(myvector.begin(), myvector.begin() + 5, myvector.end());

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 10 20 30 10 20 30 40 50
	std::cout << '\n';
}

{
	std::vector<int> foo = { 25, 15, 5, -5, -15 };
	std::vector<int> bar(foo.size());

	// copy only positive numbers:
	auto it = std::copy_if(foo.begin(), foo.end(), bar.begin(), [](int i){return !(i<0); });
	bar.resize(std::distance(bar.begin(), it));  // shrink container to new size

	std::cout << "bar contains:";
	for (int& x : bar) std::cout << ' ' << x; // 25 15 5
	std::cout << '\n';
}

{
	int myints[] = { 10, 20, 30, 40, 50, 60, 70 };
	std::vector<int> myvector;

	myvector.resize(7);   // allocate space for 7 elements

	std::copy_n(myints, 7, myvector.begin());

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 10 20 30 40 50 60 70

	std::cout << '\n';
}

	return 0;
}

///////////////////////////////////////////////
int test_algorithm_count()
{
{
	// counting elements in array:
	int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };   // 8 elements
	int mycount = std::count(myints, myints + 8, 10);
	std::cout << "10 appears " << mycount << " times.\n"; // 3

	// counting elements in container:
	std::vector<int> myvector(myints, myints + 8);
	mycount = std::count(myvector.begin(), myvector.end(), 20);
	std::cout << "20 appears " << mycount << " times.\n"; // 3
}

{
	std::vector<int> myvector;
	for (int i = 1; i<10; i++) myvector.push_back(i); // myvector: 1 2 3 4 5 6 7 8 9

	int mycount = count_if(myvector.begin(), myvector.end(), IsOdd);
	std::cout << "myvector contains " << mycount << " odd values.\n"; // 5
}

	return 0;
}

//////////////////////////////////////////
static bool mygreater(int i, int j) { return (i>j); }

int test_algorithm_equal()
{
{
	int myints[] = { 20, 40, 60, 80, 100 };               // myints: 20 40 60 80 100
	std::vector<int>myvector(myints, myints + 5);       // myvector: 20 40 60 80 100

	// using default comparison:
	if (std::equal(myvector.begin(), myvector.end(), myints))
		std::cout << "The contents of both sequences are equal.\n"; // equal
	else
		std::cout << "The contents of both sequences differ.\n";

	myvector[3] = 81;                                 // myvector: 20 40 60 81 100

	// using predicate comparison:
	if (std::equal(myvector.begin(), myvector.end(), myints, mypredicate))
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n"; // differ
}

{
	int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };
	std::vector<int> v(myints, myints + 8);                         // 10 20 30 30 20 10 10 20
	std::pair<std::vector<int>::iterator, std::vector<int>::iterator> bounds;

	// using default comparison:
	std::sort(v.begin(), v.end());                              // 10 10 10 20 20 20 30 30
	bounds = std::equal_range(v.begin(), v.end(), 20);          //          ^        ^

	std::cout << "bounds at positions " << (bounds.first - v.begin()); // 3
	std::cout << " and " << (bounds.second - v.begin()) << '\n'; // 6

	// using "mygreater" as comp:
	std::sort(v.begin(), v.end(), mygreater);                     // 30 30 20 20 20 10 10 10
	bounds = std::equal_range(v.begin(), v.end(), 20, mygreater); //       ^        ^

	std::cout << "bounds at positions " << (bounds.first - v.begin()); // 2
	std::cout << " and " << (bounds.second - v.begin()) << '\n'; // 5
}

{
	int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };
	std::vector<int> v(myints, myints + 8);       // 10 20 30 30 20 10 10 20

	std::sort(v.begin(), v.end());                // 10 10 10 20 20 20 30 30

	std::vector<int>::iterator low, up;
	low = std::lower_bound(v.begin(), v.end(), 20);
	up = std::upper_bound(v.begin(), v.end(), 20);

	std::cout << "lower_bound at position " << (low - v.begin()) << '\n'; // 3
	std::cout << "upper_bound at position " << (up - v.begin()) << '\n'; // 6
}

	return 0;
}

//////////////////////////////////////////
int test_algorithm_fill()
{
{
	std::vector<int> myvector(8);                       // myvector: 0 0 0 0 0 0 0 0

	std::fill(myvector.begin(), myvector.begin() + 4, 5);   // myvector: 5 5 5 5 0 0 0 0
	std::fill(myvector.begin() + 3, myvector.end() - 2, 8);   // myvector: 5 5 5 8 8 8 0 0

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 5 5 5 8 8 8 0 0
	std::cout << '\n';
}

{
	std::vector<int> myvector(8, 10);        // myvector: 10 10 10 10 10 10 10 10

	std::fill_n(myvector.begin(), 4, 20);     // myvector: 20 20 20 20 10 10 10 10
	std::fill_n(myvector.begin() + 3, 3, 33);   // myvector: 20 20 20 33 33 33 10 10

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 20 20 20 33 33 33 10 10
	std::cout << '\n';
}

	return 0;
}

///////////////////////////////////////////
void myfunction3(int i) {  // function:
	std::cout << ' ' << i;
}

struct myclass {           // function object type:
	void operator() (int i) { std::cout << ' ' << i; }
} myobject;

int test_algorithm_for_each()
{
	std::vector<int> myvector;
	myvector.push_back(10);
	myvector.push_back(20);
	myvector.push_back(30);

	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(), myfunction3); // 10 20 30
	std::cout << '\n';

	// or:
	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(), myobject); // 10 20 30
	std::cout << '\n';

	return 0;
}

////////////////////////////////////////////////
// function generator:
int RandomNumber() { return (std::rand() % 100); }

// class generator:
struct c_unique {
	int current;
	c_unique() { current = 0; }
	int operator()() { return ++current; }
} UniqueNumber;

int current = 0;
int UniqueNumber2() { return ++current; }

int test_algorithm_generate()
{
{
	std::srand(unsigned(std::time(0)));

	std::vector<int> myvector(8);

	std::generate(myvector.begin(), myvector.end(), RandomNumber);

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::generate(myvector.begin(), myvector.end(), UniqueNumber);

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 1 2 3 4 5 6 7 8
	std::cout << '\n';
}

{
	int myarray[9];

	std::generate_n(myarray, 9, UniqueNumber2);

	std::cout << "myarray contains:";
	for (int i = 0; i<9; ++i)
		std::cout << ' ' << myarray[i]; // 1 2 3 4 5 6 7 8 9
	std::cout << '\n';
}

	return 0;
}

////////////////////////////////////////////////
int test_algorithm_includes()
{
	int container[] = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 };
	int continent[] = { 40, 30, 20, 10 };

	std::sort(container, container + 10);
	std::sort(continent, continent + 4);

	// using default comparison:
	if (std::includes(container, container + 10, continent, continent + 4))
		std::cout << "container includes continent!\n"; // container includes continent

	// using myfunction as comp:
	if (std::includes(container, container + 10, continent, continent + 4, myfunction2))
		std::cout << "container includes continent!\n"; // container includes continent

	return 0;
}

///////////////////////////////////////////////////////////
int test_algorithm_merge()
{
{
	int first[] = { 5, 10, 15, 20, 25 };
	int second[] = { 50, 40, 30, 20, 10 };
	std::vector<int> v(10);
	std::vector<int>::iterator it;

	std::sort(first, first + 5);
	std::sort(second, second + 5);

	it = std::copy(first, first + 5, v.begin());
	std::copy(second, second + 5, it);

	std::inplace_merge(v.begin(), v.begin() + 5, v.end());

	std::cout << "The resulting vector contains:";
	for (it = v.begin(); it != v.end(); ++it)
		std::cout << ' ' << *it; // 5 10 10 15 20 20 25 30 40 50
	std::cout << '\n';
}

{
	int first[] = { 5, 10, 15, 20, 25 };
	int second[] = { 50, 40, 30, 20, 10 };
	std::vector<int> v(10);

	std::sort(first, first + 5);
	std::sort(second, second + 5);
	std::merge(first, first + 5, second, second + 5, v.begin());

	std::cout << "The resulting vector contains:";
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << ' ' << *it; // 5 10 10 15 20 20 25 30 40 50
	std::cout << '\n';
}

	return 0;
}

////////////////////////////////////////
int test_algorithm_heap()
{
{
	std::vector<int> foo{ 9, 5, 2, 6, 4, 1, 3, 8, 7 };

	if (!std::is_heap(foo.begin(), foo.end()))
		std::make_heap(foo.begin(), foo.end());

	std::cout << "Popping out elements:";
	while (!foo.empty()) {
		std::pop_heap(foo.begin(), foo.end());   // moves largest element to back
		std::cout << ' ' << foo.back();         // prints back // 9 8 7 6 5 4 3 2 1
		foo.pop_back();                         // pops element out of container
	}
	std::cout << '\n';
}

{
	std::vector<int> foo{ 2, 6, 9, 3, 8, 4, 5, 1, 7 };

	std::sort(foo.begin(), foo.end());
	std::reverse(foo.begin(), foo.end());

	auto last = std::is_heap_until(foo.begin(), foo.end());

	std::cout << "The " << (last - foo.begin()) << " first elements are a valid heap:"; // 9
	for (auto it = foo.begin(); it != last; ++it)
		std::cout << ' ' << *it; // 9 8 7 6 5 4 3 2 1
	std::cout << '\n';
}

{
	int myints[] = { 10, 20, 30, 5, 15 };
	std::vector<int> v(myints, myints + 5);

	std::make_heap(v.begin(), v.end());
	std::cout << "initial max heap   : " << v.front() << '\n'; // 30

	std::pop_heap(v.begin(), v.end()); v.pop_back();
	std::cout << "max heap after pop : " << v.front() << '\n'; // 20

	v.push_back(99); std::push_heap(v.begin(), v.end());
	std::cout << "max heap after push: " << v.front() << '\n'; // 99

	std::sort_heap(v.begin(), v.end());

	std::cout << "final sorted range :";
	for (unsigned i = 0; i<v.size(); i++)
		std::cout << ' ' << v[i]; // 5 10 15 20 99

	std::cout << '\n';
}

	return 0;
}

////////////////////////////////////////////
int test_algorithm_partition()
{
{
	std::array<int, 7> foo{ 1, 2, 3, 4, 5, 6, 7 };

	// print contents:
	std::cout << "foo:"; for (int& x : foo) std::cout << ' ' << x;
	if (std::is_partitioned(foo.begin(), foo.end(), IsOdd))
		std::cout << " (partitioned)\n";
	else
		std::cout << " (not partitioned)\n"; // not partitioned

	// partition array:
	std::partition(foo.begin(), foo.end(), IsOdd);

	// print contents again:
	std::cout << "foo:"; for (int& x : foo) std::cout << ' ' << x; // 1 7 3 5 4 6 2
	if (std::is_partitioned(foo.begin(), foo.end(), IsOdd))
		std::cout << " (partitioned)\n"; // partitioned
	else
		std::cout << " (not partitioned)\n";
}

{
	std::vector<int> myvector;

	// set some values:
	for (int i = 1; i<10; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

	std::vector<int>::iterator bound;
	bound = std::partition(myvector.begin(), myvector.end(), IsOdd);

	// print out content:
	std::cout << "odd elements:";
	for (std::vector<int>::iterator it = myvector.begin(); it != bound; ++it)
		std::cout << ' ' << *it; // 1 9 3 7 5
	std::cout << '\n';

	std::cout << "even elements:";
	for (std::vector<int>::iterator it = bound; it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 6 4 8 2
	std::cout << '\n';
}

{
	std::vector<int> foo{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<int> odd, even;

	// resize vectors to proper size:
	unsigned n = std::count_if(foo.begin(), foo.end(), IsOdd);
	odd.resize(n); even.resize(foo.size() - n);

	// partition:
	std::partition_copy(foo.begin(), foo.end(), odd.begin(), even.begin(), IsOdd);

	// print contents:
	std::cout << "odd: ";  for (int& x : odd)  std::cout << ' ' << x; std::cout << '\n'; // 1 3 5 7 9
	std::cout << "even: "; for (int& x : even) std::cout << ' ' << x; std::cout << '\n'; // 2 4 6 8
}

{
	std::vector<int> foo{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<int> odd;

	std::partition(foo.begin(), foo.end(), IsOdd);

	auto it = std::partition_point(foo.begin(), foo.end(), IsOdd);
	odd.assign(foo.begin(), it);

	// print contents of odd:
	std::cout << "odd:";
	for (int& x : odd) std::cout << ' ' << x; // 1 9 3 7 5
	std::cout << '\n';
}

{
	std::vector<int> myvector;

	// set some values:
	for (int i = 1; i<10; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

	std::vector<int>::iterator bound;
	bound = std::stable_partition(myvector.begin(), myvector.end(), IsOdd);

	// print out content:
	std::cout << "odd elements:";
	for (std::vector<int>::iterator it = myvector.begin(); it != bound; ++it)
		std::cout << ' ' << *it; // 1 3 5 7 9
	std::cout << '\n';

	std::cout << "even elements:";
	for (std::vector<int>::iterator it = bound; it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 2 4 6 8
	std::cout << '\n';
}

	return 0;
}

//////////////////////////////////////
int test_algorithm_permutation()
{
{
	std::array<int, 5> foo = { 1, 2, 3, 4, 5 };
	std::array<int, 5> bar = { 3, 1, 4, 5, 2 };

	if (std::is_permutation(foo.begin(), foo.end(), bar.begin()))
		std::cout << "foo and bar contain the same elements.\n"; // foo and bar contain the same elements
}

{
	int myints[] = { 1, 2, 3 };

	std::sort(myints, myints + 3);

	std::cout << "The 3! possible permutations with 3 elements:\n";
	do {
		std::cout << myints[0] << ' ' << myints[1] << ' ' << myints[2] << '\n';
	} while (std::next_permutation(myints, myints + 3));

	std::cout << "After loop: " << myints[0] << ' ' << myints[1] << ' ' << myints[2] << '\n'; // 1 2 3
}

{
	int myints[] = { 1, 2, 3 };

	std::sort(myints, myints + 3);
	std::reverse(myints, myints + 3);

	std::cout << "The 3! possible permutations with 3 elements:\n";
	do {
		std::cout << myints[0] << ' ' << myints[1] << ' ' << myints[2] << '\n';
	} while (std::prev_permutation(myints, myints + 3));

	std::cout << "After loop: " << myints[0] << ' ' << myints[1] << ' ' << myints[2] << '\n'; // 3 2 1
}

	return 0;
}

/////////////////////////////////////////////
struct myclass2 {
	bool operator() (int i, int j) { return (i<j); }
} myobject2;

bool compare_as_ints(double i, double j) { return (int(i)<int(j)); }

int test_algorithm_sort()
{
{
	std::array<int, 4> foo{ 2, 4, 1, 3 };

	do {
		// try a new permutation:
		std::prev_permutation(foo.begin(), foo.end());

		// print range:
		std::cout << "foo:";
		for (int& x : foo) std::cout << ' ' << x;
		std::cout << '\n';

	} while (!std::is_sorted(foo.begin(), foo.end()));

	std::cout << "the range is sorted!\n";
}

{
	std::array<int, 4> foo{ 2, 4, 1, 3 };
	std::array<int, 4>::iterator it;

	do {
		// try a new permutation:
		std::prev_permutation(foo.begin(), foo.end());

		// print range:
		std::cout << "foo:";
		for (int& x : foo) std::cout << ' ' << x;
		it = std::is_sorted_until(foo.begin(), foo.end());
		std::cout << " (" << (it - foo.begin()) << " elements sorted)\n";

	} while (it != foo.end());

	std::cout << "the range is sorted!\n";
}

{
	std::vector<int> myvector;

	// set some values:
	for (int i = 1; i<10; i++) myvector.push_back(i);   // 1 2 3 4 5 6 7 8 9

	std::random_shuffle(myvector.begin(), myvector.end());

	// using default comparison (operator <):
	std::nth_element(myvector.begin(), myvector.begin() + 5, myvector.end());

	// using function as comp
	std::nth_element(myvector.begin(), myvector.begin() + 5, myvector.end(), myfunction2);

	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 1 2 3 4 5 6 7 8 9
	std::cout << '\n';
}

{
	int myints[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	std::vector<int> myvector(myints, myints + 9);

	// using default comparison (operator <):
	std::partial_sort(myvector.begin(), myvector.begin() + 5, myvector.end());

	// using function as comp
	std::partial_sort(myvector.begin(), myvector.begin() + 5, myvector.end(), myfunction2);

	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 1 2 3 4 5 9 8 7 6
	std::cout << '\n';
}

{
	int myints[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	std::vector<int> myvector(5);

	// using default comparison (operator <):
	std::partial_sort_copy(myints, myints + 9, myvector.begin(), myvector.end());

	// using function as comp
	std::partial_sort_copy(myints, myints + 9, myvector.begin(), myvector.end(), myfunction2);

	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 1 2 3 4 5
	std::cout << '\n';
}

{
	int myints[] = { 32, 71, 12, 45, 26, 80, 53, 33 };
	std::vector<int> myvector(myints, myints + 8);               // 32 71 12 45 26 80 53 33

	// using default comparison (operator <):
	std::sort(myvector.begin(), myvector.begin() + 4);           //(12 32 45 71)26 80 53 33

	// using function as comp
	std::sort(myvector.begin() + 4, myvector.end(), myfunction2); // 12 32 45 71(26 33 53 80)

	// using object as comp
	std::sort(myvector.begin(), myvector.end(), myobject2);     //(12 26 32 33 45 53 71 80)

	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 12 26 32 33 45 53 71 80
	std::cout << '\n';
}

{
	double mydoubles[] = { 3.14, 1.41, 2.72, 4.67, 1.73, 1.32, 1.62, 2.58 };

	std::vector<double> myvector;

	myvector.assign(mydoubles, mydoubles + 8);

	std::cout << "using default comparison:";
	std::stable_sort(myvector.begin(), myvector.end());
	for (std::vector<double>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 1.32 1.41 1.62 1.73 2.58 2.72 3.14 4.67
	std::cout << '\n';

	myvector.assign(mydoubles, mydoubles + 8);

	std::cout << "using 'compare_as_ints' :";
	std::stable_sort(myvector.begin(), myvector.end(), compare_as_ints);
	for (std::vector<double>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 1.41 1.73 1.32 1.62 2.72 2.58 3.14 4.67
	std::cout << '\n';
}

	return 0;
}

////////////////////////////////////////////////////
int test_algorithm_swap()
{
{
	int myints[] = { 10, 20, 30, 40, 50 };              //   myints:  10  20  30  40  50
	std::vector<int> myvector(4, 99);                   // myvector:  99  99  99  99

	std::iter_swap(myints, myvector.begin());     //   myints: [99] 20  30  40  50
						      // myvector: [10] 99  99  99

	std::iter_swap(myints + 3, myvector.begin() + 2); //   myints:  99  20  30 [99] 50
						          // myvector:  10  99 [40] 99

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 10 99 40 99
	std::cout << '\n';
}

{
	int x = 10, y = 20;                              // x:10 y:20
	std::swap(x, y);                                 // x:20 y:10

	std::vector<int> foo(4, x), bar(6, y);       // foo:4x20 bar:6x10
	std::swap(foo, bar);                         // foo:6x10 bar:4x20

	std::cout << "foo contains:";
	for (std::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it; // 10 10 10 10 10 10
	std::cout << '\n';
}

{
	std::vector<int> foo(5, 10);        // foo: 10 10 10 10 10
	std::vector<int> bar(5, 33);        // bar: 33 33 33 33 33

	std::swap_ranges(foo.begin() + 1, foo.end() - 1, bar.begin());

	// print out results of swap:
	std::cout << "foo contains:";
	for (std::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it; // 10 33 33 33 10
	std::cout << '\n';

	std::cout << "bar contains:";
	for (std::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
		std::cout << ' ' << *it; // 10 10 10 33 33
	std::cout << '\n';
}

	return 0;
}

///////////////////////////////////////////////
static bool mycomp(char c1, char c2) { return std::tolower(c1)<std::tolower(c2); }

int test_algorithm_lexicographical_compare()
{
	char foo[] = "Apple";
	char bar[] = "apartment";

	std::cout << std::boolalpha;

	std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

	std::cout << "Using default comparison (operator<): ";
	std::cout << std::lexicographical_compare(foo, foo + 5, bar, bar + 9); // true
	std::cout << '\n';

	std::cout << "Using mycomp as comparison object: ";
	std::cout << std::lexicographical_compare(foo, foo + 5, bar, bar + 9, mycomp); // false
	std::cout << '\n';

	return 0;
}

//////////////////////////////////////
static bool myfn(int i, int j) { return i<j; }

int test_algorithm_min_max()
{
{
	std::cout << "min(1, 2)==" << std::min(1, 2) << '\n'; // 1
	std::cout << "min(2, 1)==" << std::min(2, 1) << '\n'; // 1
	std::cout << "min('a', 'z')==" << std::min('a', 'z') << '\n'; // a
	std::cout << "min(3.14, 2.72)==" << std::min(3.14, 2.72) << '\n'; // 2.72
}

{
	int myints[] = { 3, 7, 2, 5, 6, 4, 9 };

	// using default comparison:
	std::cout << "The smallest element is " << *std::min_element(myints, myints + 7) << '\n'; // 2
	std::cout << "The largest element is " << *std::max_element(myints, myints + 7) << '\n'; // 9

	// using function myfn as comp:
	std::cout << "The smallest element is " << *std::min_element(myints, myints + 7, myfn) << '\n'; // 2
	std::cout << "The largest element is " << *std::max_element(myints, myints + 7, myfn) << '\n'; // 9

	// using object myobj as comp:
	std::cout << "The smallest element is " << *std::min_element(myints, myints + 7, myobject2) << '\n'; // 2
	std::cout << "The largest element is " << *std::max_element(myints, myints + 7, myobject2) << '\n'; // 9
}

{
	std::cout << "max(1,2)==" << std::max(1, 2) << '\n'; // 2
	std::cout << "max(2,1)==" << std::max(2, 1) << '\n'; // 2
	std::cout << "max('a','z')==" << std::max('a', 'z') << '\n'; // z
	std::cout << "max(3.14,2.73)==" << std::max(3.14, 2.73) << '\n'; // 3.14
}

{
	auto result = std::minmax({ 1, 2, 3, 4, 5 });

	std::cout << "minmax({1,2,3,4,5}): ";
	std::cout << result.first << ' ' << result.second << '\n'; // 1 5
}

{
	std::array<int, 7> foo{ 3, 7, 2, 9, 5, 8, 6 };

	auto result = std::minmax_element(foo.begin(), foo.end());

	// print result:
	std::cout << "min is " << *result.first; // 2
	std::cout << ", at position " << (result.first - foo.begin()) << '\n'; // 2
	std::cout << "max is " << *result.second; // 9
	std::cout << ", at position " << (result.second - foo.begin()) << '\n'; // 3
}

	return 0;
}

///////////////////////////////////////////
int test_algorithm_mismatch()
{
	std::vector<int> myvector;
	for (int i = 1; i<6; i++) myvector.push_back(i * 10); // myvector: 10 20 30 40 50

	int myints[] = { 10, 20, 80, 320, 1024 };                //   myints: 10 20 80 320 1024

	std::pair<std::vector<int>::iterator, int*> mypair;

	// using default comparison:
	mypair = std::mismatch(myvector.begin(), myvector.end(), myints);
	std::cout << "First mismatching elements: " << *mypair.first; // 30
	std::cout << " and " << *mypair.second << '\n'; // 80

	++mypair.first; ++mypair.second;

	// using predicate comparison:
	mypair = std::mismatch(mypair.first, myvector.end(), mypair.second, mypredicate);
	std::cout << "Second mismatching elements: " << *mypair.first; // 40
	std::cout << " and " << *mypair.second << '\n'; // 320

	return 0;
}

//////////////////////////////////////////
/* The behavior of std::move_backward template is equivalent to:
template<class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 move_backward ( BidirectionalIterator1 first,
	BidirectionalIterator1 last,
	BidirectionalIterator2 result )
{
	while (last!=first) *(--result) = std::move(*(--last));
	return result;
}
*/
int test_algorithm_move()
{
{
	std::vector<std::string> foo = { "air", "water", "fire", "earth" };
	std::vector<std::string> bar(4);

	// moving ranges:
	std::cout << "Moving ranges...\n";
	std::move(foo.begin(), foo.begin() + 4, bar.begin());

	std::cout << "foo contains " << foo.size() << " elements:";// 4
	std::cout << " (each in an unspecified but valid state)";
	std::cout << '\n';

	std::cout << "bar contains " << bar.size() << " elements:"; // 4
	for (std::string& x : bar) std::cout << " [" << x << "]"; // [air] [water] [fire] [earch]
	std::cout << '\n';

	// moving container:
	std::cout << "Moving container...\n";
	foo = std::move(bar);

	std::cout << "foo contains " << foo.size() << " elements:"; // 4
	for (std::string& x : foo) std::cout << " [" << x << "]"; // [air] [water] [fire] [earch]
	std::cout << '\n';
	std::cout << "bar contains " << bar.size() << " elements" << std::endl; // 0
	//std::cout << "bar is in an unspecified but valid state";
	//std::cout << '\n';
}

{
	std::string elems[10] = { "air", "water", "fire", "earth" };

	// insert new element at the beginning:
	std::move_backward(elems, elems + 4, elems + 5);
	elems[0] = "ether";

	std::cout << "elems contains:";
	for (int i = 0; i<10; ++i)
		std::cout << " [" << elems[i] << "]"; // [ether] [air] [water] [fire] [earch]
	std::cout << '\n';
}

	return 0;
}

//////////////////////////////////////////////
// random generator function:
int myrandom(int i) { return std::rand() % i; }

int test_algorithm_shuffle()
{
{
	std::srand(unsigned(std::time(0)));
	std::vector<int> myvector;

	// set some values:
	for (int i = 1; i<10; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

	// using built-in random generator:
	std::random_shuffle(myvector.begin(), myvector.end());

	// using myrandom:
	std::random_shuffle(myvector.begin(), myvector.end(), myrandom);

	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';
}

{
	std::array<int, 5> foo{ 1, 2, 3, 4, 5 };

	// obtain a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	shuffle(foo.begin(), foo.end(), std::default_random_engine(seed));

	std::cout << "shuffled elements:";
	for (int& x : foo) std::cout << ' ' << x;
	std::cout << '\n';
}

	return 0;
}

//////////////////////////////////////////
int test_algorithm_remove()
{
{
	int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };      // 10 20 30 30 20 10 10 20

	// bounds of range:
	int* pbegin = myints;                                   // ^
	int* pend = myints + sizeof(myints) / sizeof(int);      // ^                       ^

	pend = std::remove(pbegin, pend, 20);                   // 10 30 30 10 10 ?  ?  ?
	                                                        // ^              ^
	std::cout << "range contains:";
	for (int* p = pbegin; p != pend; ++p)
		std::cout << ' ' << *p; // 10 30 30 10 10
	std::cout << '\n';
}

{
	int myints[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };            // 1 2 3 4 5 6 7 8 9

	// bounds of range:
	int* pbegin = myints;                                    // ^
	int* pend = myints + sizeof(myints) / sizeof(int);       // ^                 ^

	pend = std::remove_if(pbegin, pend, IsOdd);              // 2 4 6 8 ? ? ? ? ?
	                                                         // ^       ^
	std::cout << "the range contains:";
	for (int* p = pbegin; p != pend; ++p)
		std::cout << ' ' << *p; // 2 4 6 8
	std::cout << '\n';
}

{
	int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };               // 10 20 30 30 20 10 10 20
	std::vector<int> myvector(8);

	std::remove_copy(myints, myints + 8, myvector.begin(), 20);      // 10 30 30 10 10 0 0 0

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 10 30 30 10 10 0 0 0
	std::cout << '\n';
}

{
	int myints[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<int> myvector(9);

	std::remove_copy_if(myints, myints + 9, myvector.begin(), IsOdd);

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 2 4 6 8 0 0 0 0 0
	std::cout << '\n';
}

	return 0;
}

//////////////////////////////////////////////
int test_algorithm_replace()
{
{
	int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };
	std::vector<int> myvector(myints, myints + 8);            // 10 20 30 30 20 10 10 20

	std::replace(myvector.begin(), myvector.end(), 20, 99);   // 10 99 30 30 99 10 10 99

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 10 99 30 30 99 10 10 99
	std::cout << '\n';
}

{
	std::vector<int> myvector;

	// set some values:
	for (int i = 1; i<10; i++) myvector.push_back(i);               // 1 2 3 4 5 6 7 8 9

	std::replace_if(myvector.begin(), myvector.end(), IsOdd, 0);    // 0 2 0 4 0 6 0 8 0

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 0 2 0 4 0 6 0 8 0
	std::cout << '\n';
}

{
	int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };

	std::vector<int> myvector(8);
	std::replace_copy(myints, myints + 8, myvector.begin(), 20, 99);

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 10 99 30 30 99 10 10 99
	std::cout << '\n';
}

{
	std::vector<int> foo, bar;

	// set some values:
	for (int i = 1; i<10; i++) foo.push_back(i);                         // 1 2 3 4 5 6 7 8 9

	bar.resize(foo.size());   // allocate space
	std::replace_copy_if(foo.begin(), foo.end(), bar.begin(), IsOdd, 0); // 0 2 0 4 0 6 0 8 0

	std::cout << "bar contains:";
	for (std::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
		std::cout << ' ' << *it; // 0 2 0 4 0 6 0 8 0
	std::cout << '\n';
}

	return 0;
}

///////////////////////////////////////////////////
int test_algorithm_reverse()
{
{
	std::vector<int> myvector;

	// set some values:
	for (int i = 1; i<10; ++i) myvector.push_back(i);   // 1 2 3 4 5 6 7 8 9

	std::reverse(myvector.begin(), myvector.end());     // 9 8 7 6 5 4 3 2 1

	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 9 8 7 6 5 4 3 2 1
	std::cout << '\n';
}

{
	int myints[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<int> myvector;

	myvector.resize(9);    // allocate space

	std::reverse_copy(myints, myints + 9, myvector.begin());

	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 9 8 7 6 5 4 3 2 1

	std::cout << '\n';
}

	return 0;
}

////////////////////////////////////////////
/*
The behavior of std::rotate template (C++98) is equivalent to:

template <class ForwardIterator>
void rotate (ForwardIterator first, ForwardIterator middle, ForwardIterator last)
{
	ForwardIterator next = middle;
	while (first!=next) {
		swap (*first++,*next++);
		if (next==last) next=middle;
		else if (first==middle) middle=next;
	}
}
*/

int test_algorithm_rotate()
{
{
	std::vector<int> myvector;

	// set some values:
	for (int i = 1; i<10; ++i) myvector.push_back(i);                    // 1 2 3 4 5 6 7 8 9

	std::rotate(myvector.begin(), myvector.begin() + 3, myvector.end()); // 4 5 6 7 8 9 1 2 3
	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 4 5 6 7 8 9 1 2 3
	std::cout << '\n';
}

{
	int myints[] = { 10, 20, 30, 40, 50, 60, 70 };

	std::vector<int> myvector(7);

	std::rotate_copy(myints, myints + 3, myints + 7, myvector.begin());

	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 40 50 60 70 10 20 30
	std::cout << '\n';
}

	return 0;
}

//////////////////////////////////////
/*
The behavior of std::set_difference template is equivalent to:

template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_difference (InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2, OutputIterator result)
{
	while (first1!=last1 && first2!=last2) {
		if (*first1<*first2) { *result = *first1; ++result; ++first1; }
		else if (*first2<*first1) ++first2;
		else { ++first1; ++first2; }
	}
	return std::copy(first1,last1,result);
}
*/

int test_algorithm_set()
{
{
	int first[] = { 5, 10, 15, 20, 25 };
	int second[] = { 50, 40, 30, 20, 10 };
	std::vector<int> v(10);                      // 0  0  0  0  0  0  0  0  0  0
	std::vector<int>::iterator it;

	std::sort(first, first + 5);     //  5 10 15 20 25
	std::sort(second, second + 5);   // 10 20 30 40 50

	it = std::set_difference(first, first + 5, second, second + 5, v.begin());
						       //  5 15 25  0  0  0  0  0  0  0
	v.resize(it - v.begin());                      //  5 15 25

	std::cout << "The difference has " << (v.size()) << " elements:\n"; // 3
	for (it = v.begin(); it != v.end(); ++it)
		std::cout << ' ' << *it; // 5 15 25
	std::cout << '\n';
}

{
	int first[] = { 5, 10, 15, 20, 25 };
	int second[] = { 50, 40, 30, 20, 10 };
	std::vector<int> v(10);                      // 0  0  0  0  0  0  0  0  0  0
	std::vector<int>::iterator it;

	std::sort(first, first + 5);     //  5 10 15 20 25
	std::sort(second, second + 5);   // 10 20 30 40 50

	it = std::set_intersection(first, first + 5, second, second + 5, v.begin());
	                                               // 10 20 0  0  0  0  0  0  0  0
	v.resize(it - v.begin());                      // 10 20

	std::cout << "The intersection has " << (v.size()) << " elements:\n"; // 2
	for (it = v.begin(); it != v.end(); ++it)
		std::cout << ' ' << *it; // 10 20
	std::cout << '\n';
}

{
	int first[] = { 5, 10, 15, 20, 25 };
	int second[] = { 50, 40, 30, 20, 10 };
	std::vector<int> v(10);                      // 0  0  0  0  0  0  0  0  0  0
	std::vector<int>::iterator it;

	std::sort(first, first + 5);     //  5 10 15 20 25
	std::sort(second, second + 5);   // 10 20 30 40 50

	it = std::set_symmetric_difference(first, first + 5, second, second + 5, v.begin());
						       //  5 15 25 30 40 50  0  0  0  0
	v.resize(it - v.begin());                      //  5 15 25 30 40 50

	std::cout << "The symmetric difference has " << (v.size()) << " elements:\n"; // 6
	for (it = v.begin(); it != v.end(); ++it)
		std::cout << ' ' << *it; // 5 15 25 30 40 50
	std::cout << '\n';
}

{
	int first[] = { 5, 10, 15, 20, 25 };
	int second[] = { 50, 40, 30, 20, 10 };
	std::vector<int> v(10);                      // 0  0  0  0  0  0  0  0  0  0
	std::vector<int>::iterator it;

	std::sort(first, first + 5);     //  5 10 15 20 25
	std::sort(second, second + 5);   // 10 20 30 40 50

	it = std::set_union(first, first + 5, second, second + 5, v.begin());
						       // 5 10 15 20 25 30 40 50  0  0
	v.resize(it - v.begin());                      // 5 10 15 20 25 30 40 50

	std::cout << "The union has " << (v.size()) << " elements:\n"; // 8
	for (it = v.begin(); it != v.end(); ++it)
		std::cout << ' ' << *it; // 5 10 15 20 25 30 40 50
	std::cout << '\n';
}

	return 0;
}

/////////////////////////////////////
int op_increase(int i) { return ++i; }

int test_algorithm_transform()
{
	std::vector<int> foo;
	std::vector<int> bar;

	// set some values:
	for (int i = 1; i<6; i++)
		foo.push_back(i * 10);                         // foo: 10 20 30 40 50

	bar.resize(foo.size());                         // allocate space

	std::transform(foo.begin(), foo.end(), bar.begin(), op_increase);
	                                                       // bar: 11 21 31 41 51

	// std::plus adds together its two arguments:
	std::transform(foo.begin(), foo.end(), bar.begin(), foo.begin(), std::plus<int>());
	                                                       // foo: 21 41 61 81 101

	std::cout << "foo contains:";
	for (std::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it; // 21 41 61 81 101
	std::cout << '\n';

	return 0;
}

/////////////////////////////////////////
int test_algorithm_unique()
{
{
	int myints[] = { 10, 20, 20, 20, 30, 30, 20, 20, 10 };           // 10 20 20 20 30 30 20 20 10
	std::vector<int> myvector(myints, myints + 9);

	// using default comparison:
	std::vector<int>::iterator it;
	it = std::unique(myvector.begin(), myvector.end());              // 10 20 30 20 10 ?  ?  ?  ?
	                                                                 //                ^

	myvector.resize(std::distance(myvector.begin(), it));            // 10 20 30 20 10

	// using predicate comparison:
	std::unique(myvector.begin(), myvector.end(), myfunction);   // (no changes)

	// print out content:
	std::cout << "myvector contains:";
	for (it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 10 20 30 20 10
	std::cout << '\n';
}

{
	int myints[] = { 10, 20, 20, 20, 30, 30, 20, 20, 10 };
	std::vector<int> myvector(9);                                   // 0  0  0  0  0  0  0  0  0

	// using default comparison:
	std::vector<int>::iterator it;
	it = std::unique_copy(myints, myints + 9, myvector.begin());   // 10 20 30 20 10 0  0  0  0
	                                                               //                ^

	std::sort(myvector.begin(), it);                               // 10 10 20 20 30 0  0  0  0
	                                                               //                ^

	// using predicate comparison:
	it = std::unique_copy(myvector.begin(), it, myvector.begin(), myfunction);
	                                                               // 10 20 30 20 30 0  0  0  0
	                                                               //          ^

	myvector.resize(std::distance(myvector.begin(), it));    // 10 20 30

	// print out content:
	std::cout << "myvector contains:";
	for (it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it; // 10 20 30
	std::cout << '\n';
}

	return 0;
}

} // namespace algorithm_
