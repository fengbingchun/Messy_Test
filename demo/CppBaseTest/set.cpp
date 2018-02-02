#include "set.hpp"
#include <set>
#include <iostream>
#include <string>
#include <cassert>
#include <chrono>
#include <functional>
#include <iomanip>

// Blog: http://blog.csdn.net/fengbingchun/article/details/63268962

// reference: http://www.cplusplus.com/reference/set/set/
static bool fncomp(int lhs, int rhs) { return lhs<rhs; }

struct classcomp {
	bool operator() (const int& lhs, const int& rhs) const
	{
		return lhs<rhs;
	}
};

int test_set_cplusplus()
{
{ // set:构造函数
	std::set<int> first;                           // empty set of ints

	int myints[] = { 10, 20, 30, 40, 50 };
	std::set<int> second(myints, myints + 5);        // range

	std::set<int> third(second);                  // a copy of second

	std::set<int> fourth(second.begin(), second.end());  // iterator ctor.

	std::set<int, classcomp> fifth;                 // class as Compare

	bool(*fn_pt)(int, int) = fncomp;
	std::set<int, bool(*)(int, int)> sixth(fn_pt);  // function pointer as Compare
}

{ // begin/end:返回指向第一个元素的迭代/返回指向最后一个元素之后的迭代器，不是最后一个元素
	int myints[] = { 75, 23, 65, 42, 13 };
	std::set<int> myset(myints, myints + 5);

	std::cout << "myset contains:";
	for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';
}

{ // clear:清除所有元素
	std::set<int> myset;

	myset.insert(100);
	myset.insert(200);
	myset.insert(300);

	std::cout << "myset contains:";
	for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	myset.clear();
	myset.insert(1101);
	myset.insert(2202);

	std::cout << "myset contains:";
	for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // count:判断某一个关键字是否在set内，返回0或者1
	std::set<int> myset;

	// set some initial values:
	for (int i = 1; i<5; ++i) myset.insert(i * 3);    // set: 3 6 9 12

	for (int i = 0; i < 10; ++i) {
		std::cout << i;
		if (myset.count(i) != 0)
			std::cout << " is an element of myset.\n";
		else
			std::cout << " is not an element of myset.\n";
	}

}

{ // cbegin/cend(c++11): Returns a const_iterator pointing to the first element in the container/
	// Returns a const_iterator pointing to the past-the-end element in the container
	std::set<int> myset = { 50, 20, 60, 10, 25 };

	std::cout << "myset contains:";
	for (auto it = myset.cbegin(); it != myset.cend(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';
}

{ // crbegin/crend(c++11):Return const_reverse_iterator to reverse beginning/
	// Return const_reverse_iterator to reverse end
	std::set<int> myset = { 50, 20, 60, 10, 25 };

	std::cout << "myset backwards:";
	for (auto rit = myset.crbegin(); rit != myset.crend(); ++rit)
		std::cout << ' ' << *rit;

	std::cout << '\n';
}

{ // emplace(c++11):如果新元素的值是唯一的，将插入该元素
	std::set<std::string> myset;

	myset.emplace("foo");
	myset.emplace("bar");
	auto ret = myset.emplace("foo");

	if (!ret.second) std::cout << "foo already exists in myset\n";
}

{ // emplace_hint(c++11):Construct and insert element with hint
	std::set<std::string> myset;
	auto it = myset.cbegin();

	myset.emplace_hint(it, "alpha");
	it = myset.emplace_hint(myset.cend(), "omega");
	it = myset.emplace_hint(it, "epsilon");
	it = myset.emplace_hint(it, "beta");

	std::cout << "myset contains:";
	for (const std::string& x : myset)
		std::cout << ' ' << x;
	std::cout << '\n';
}

{ // empty:如果集合为空，返回true
	std::set<int> myset;

	myset.insert(20);
	myset.insert(30);
	myset.insert(10);

	std::cout << "myset contains:";
	while (!myset.empty()) {
		std::cout << ' ' << *myset.begin();
		myset.erase(myset.begin());
	}
	std::cout << '\n';
}

{ // equal_range:返回集合中与给定值相等的上下限的两个迭代器
	std::set<int> myset;

	for (int i = 1; i <= 5; i++) myset.insert(i * 10);   // myset: 10 20 30 40 50

	std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator> ret;
	ret = myset.equal_range(30);

	std::cout << "the lower bound points to: " << *ret.first << '\n';
	std::cout << "the upper bound points to: " << *ret.second << '\n';
}

{ // erase:删除集合中的元素
	std::set<int> myset;
	std::set<int>::iterator it;

	// insert some values:
	for (int i = 1; i<10; i++) myset.insert(i * 10);  // 10 20 30 40 50 60 70 80 90

	it = myset.begin();
	++it;                                         // "it" points now to 20

	myset.erase(it);

	myset.erase(40);

	it = myset.find(60);
	myset.erase(it, myset.end());

	std::cout << "myset contains:";
	for (it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // find:返回一个指向被查找到元素的迭代器，如果没找到则返回end()
	std::set<int> myset;
	std::set<int>::iterator it;

	// set some initial values:
	for (int i = 1; i <= 5; i++) myset.insert(i * 10);    // set: 10 20 30 40 50

	it = myset.find(20);
	myset.erase(it);
	myset.erase(myset.find(40));

	std::cout << "myset contains:";
	for (it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // get_allocator:返回集合set的分配器
	std::set<int> myset;
	int * p;
	unsigned int i;

	// allocate an array of 5 elements using myset's allocator:
	p = myset.get_allocator().allocate(5);

	// assign some values to array
	for (i = 0; i<5; i++) p[i] = (i + 1) * 10;

	std::cout << "The allocated array contains:";
	for (i = 0; i<5; i++) std::cout << ' ' << p[i];
	std::cout << '\n';

	myset.get_allocator().deallocate(p, 5);
}

{ // insert:在集合中插入元素
	std::set<int> myset;
	std::set<int>::iterator it;
	std::pair<std::set<int>::iterator, bool> ret;

	// set some initial values:
	for (int i = 1; i <= 5; ++i) myset.insert(i * 10);    // set: 10 20 30 40 50

	ret = myset.insert(20);               // no new element inserted

	if (ret.second == false) it = ret.first;  // "it" now points to element 20

	myset.insert(it, 25);                 // max efficiency inserting
	myset.insert(it, 24);                 // max efficiency inserting
	myset.insert(it, 26);                 // no max efficiency inserting

	int myints[] = { 5, 10, 15 };              // 10 already in set, not inserted
	myset.insert(myints, myints + 3);

	std::cout << "myset contains:";
	for (it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // key_comp:Returns a copy of the comparison object used by the container
	std::set<int> myset;
	int highest;

	std::set<int>::key_compare mycomp = myset.key_comp();

	for (int i = 0; i <= 5; i++) myset.insert(i);

	std::cout << "myset contains:";

	highest = *myset.rbegin();
	std::set<int>::iterator it = myset.begin();
	do {
		std::cout << ' ' << *it;
	} while (mycomp(*(++it), highest));

	std::cout << '\n';
}

{ // lower_bond:返回指向大于（或等于）某值的第一个元素的迭代器
	std::set<int> myset;
	std::set<int>::iterator itlow, itup;

	for (int i = 1; i<10; i++) myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

	itlow = myset.lower_bound(30);                //       ^
	itup = myset.upper_bound(60);                 //                   ^

	myset.erase(itlow, itup);                     // 10 20 70 80 90

	std::cout << "myset contains:";
	for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // max_size:返回集合能容纳的元素的最大限值
	int i;
	std::set<int> myset;

	if (myset.max_size() > 1000) {
		for (i = 0; i<1000; i++) myset.insert(i);
		std::cout << "The set contains 1000 elements.\n";
	} else
		std::cout << "The set could not hold 1000 elements.\n";
}

{ // operator =:Assigns new contents to the container, replacing its current content
	int myints[] = { 12, 82, 37, 64, 15 };
	std::set<int> first(myints, myints + 5);   // set with 5 ints
	std::set<int> second;                    // empty set

	second = first;                          // now second contains the 5 ints
	first = std::set<int>();                 // and first is empty

	std::cout << "Size of first: " << int(first.size()) << '\n';
	std::cout << "Size of second: " << int(second.size()) << '\n';
}

{ // rbegin/rend:返回指向集合中最后一个元素的反向迭代器/返回指向集合中第一个元素的反向迭代器
	int myints[] = { 21, 64, 17, 78, 49 };
	std::set<int> myset(myints, myints + 5);

	std::set<int>::reverse_iterator rit;

	std::cout << "myset contains:";
	for (rit = myset.rbegin(); rit != myset.rend(); ++rit)
		std::cout << ' ' << *rit;

	std::cout << '\n';
}

{ // size:集合中元素的数目
	std::set<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i = 0; i<10; ++i) myints.insert(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.insert(100);
	std::cout << "2. size: " << myints.size() << '\n';

	myints.erase(5);
	std::cout << "3. size: " << myints.size() << '\n';
}

{ // swap:交换两个集合变量
	int myints[] = { 12, 75, 10, 32, 20, 25 };
	std::set<int> first(myints, myints + 3);     // 10,12,75
	std::set<int> second(myints + 3, myints + 6);  // 20,25,32

	first.swap(second);

	std::cout << "first contains:";
	for (std::set<int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second contains:";
	for (std::set<int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // upper_bound:返回大于某个值元素的迭代器
	std::set<int> myset;
	std::set<int>::iterator itlow, itup;

	for (int i = 1; i<10; i++) myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

	itlow = myset.lower_bound(30);                //       ^
	itup = myset.upper_bound(60);                 //                   ^

	myset.erase(itlow, itup);                     // 10 20 70 80 90

	std::cout << "myset contains:";
	for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

{ // value_comp:Returns a copy of the comparison object used by the container
	std::set<int> myset;

	std::set<int>::value_compare mycomp = myset.value_comp();

	for (int i = 0; i <= 5; i++) myset.insert(i);

	std::cout << "myset contains:";

	int highest = *myset.rbegin();
	std::set<int>::iterator it = myset.begin();
	do {
		std::cout << ' ' << *it;
	} while (mycomp(*(++it), highest));

	std::cout << '\n';
}

{ // relational operators:==/!=/</<=/>/>=
	std::set<int> foo, bar;
	foo.insert(10);
	bar.insert(20);
	bar.insert(30);
	foo.insert(40);

	// foo ({10,40}) vs bar ({20,30}):
	if (foo == bar) std::cout << "foo and bar are equal\n";
	if (foo != bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
	if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
}

	return 0;
}

// reference: http://en.cppreference.com/w/cpp/container/set
struct Point { double x, y; };
struct PointCmp {
	bool operator()(const Point& lhs, const Point& rhs) const {
		return std::hypot(lhs.x, lhs.y) < std::hypot(rhs.x, rhs.y);
	}
};

static void display_sizes(const std::set<int> &nums1, const std::set<int> &nums2, const std::set<int> &nums3)
{
	std::cout << "nums1: " << nums1.size()
		<< " nums2: " << nums2.size()
		<< " nums3: " << nums3.size() << '\n';
}

class Dew
{
private:
	int a;
	int b;
	int c;

public:
	Dew(int _a, int _b, int _c)
		: a(_a), b(_b), c(_c)
	{}

	bool operator<(const Dew &other) const
	{
		if (a < other.a)
			return true;
		if (a == other.a && b < other.b)
			return true;
		return (a == other.a && b == other.b && c < other.c);
	}
};

const int nof_operations = 120;

int set_emplace() {
	std::set<Dew> set;
	for (int i = 0; i < nof_operations; ++i)
	for (int j = 0; j < nof_operations; ++j)
	for (int k = 0; k < nof_operations; ++k)
		set.emplace(i, j, k);

	return set.size();
}

int set_insert() {
	std::set<Dew> set;
	for (int i = 0; i < nof_operations; ++i)
	for (int j = 0; j < nof_operations; ++j)
	for (int k = 0; k < nof_operations; ++k)
		set.insert(Dew(i, j, k));

	return set.size();
}

void timeit(std::function<int()> set_test, std::string what = "") {
	auto start = std::chrono::system_clock::now();
	int setsize = set_test();
	auto stop = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> time = stop - start;
	if (what.size() > 0 && setsize > 0) {
		std::cout << std::fixed << std::setprecision(2)
			<< time.count() << "  ms for " << what << '\n';
	}
}

int test_set_cppreference()
{
{ // constructor: constructs the set 
	// (1) Default constructor
	std::set<std::string> a;
	a.insert("cat");
	a.insert("dog");
	a.insert("horse");
	for (auto& str : a) std::cout << str << ' ';
	std::cout << '\n';

	// (2) Iterator constructor
	std::set<std::string> b(a.find("dog"), a.end());
	for (auto& str : b) std::cout << str << ' ';
	std::cout << '\n';

	// (3) Copy constructor
	std::set<std::string> c(a);
	c.insert("another horse");
	for (auto& str : c) std::cout << str << ' ';
	std::cout << '\n';

	// (4) Move constructor
	std::set<std::string> d(std::move(a));
	for (auto& str : d) std::cout << str << ' ';
	std::cout << '\n';
	std::cout << "moved-from set is ";
	for (auto& str : a) std::cout << str << ' ';
	std::cout << '\n';

	// (5) Initializer list constructor
	std::set<std::string> e{ "one", "two", "three", "five", "eight" };
	for (auto& str : e) std::cout << str << ' ';
	std::cout << '\n';

	// custom comparison
	std::set<Point, PointCmp> z = { { 2, 5 }, { 3, 4 }, { 1, 1 } };
	z.insert({ 1, -1 }); // this fails because the magnitude of 1,-1 equals 1,1
	for (auto& p : z) std::cout << '(' << p.x << ',' << p.y << ") ";
	std::cout << '\n';
}

{ // operator = : assigns values to the container 
	std::set<int> nums1{ 3, 1, 4, 6, 5, 9 };
	std::set<int> nums2;
	std::set<int> nums3;

	std::cout << "Initially:\n";
	display_sizes(nums1, nums2, nums3);

	// copy assignment copies data from nums1 to nums2
	nums2 = nums1;

	std::cout << "After assigment:\n";
	display_sizes(nums1, nums2, nums3);

	// move assignment moves data from nums1 to nums3,
	// modifying both nums1 and nums3
	nums3 = std::move(nums1);

	std::cout << "After move assigment:\n";
	display_sizes(nums1, nums2, nums3);
}

{ // get_allocator: returns the associated allocator 
}

{ // begin/end(cbegin/cend): returns an iterator to the beginning /returns an iterator to the end
	std::set<int> set = { 6, 1, 3, 4, 2, 5 };
	for (auto it = set.begin(); it != set.end(); ++it)
		std::cout << *it << "\n";
}

{ // rbegin/rend(crbegin/crend): returns a reverse iterator to the beginning /returns a reverse iterator to the end 
}

{ // empty: checks whether the container is empty 
	std::set<int> numbers;
	std::cout << "Initially, numbers.empty(): " << numbers.empty() << '\n';

	numbers.insert(42);
	numbers.insert(13317);
	std::cout << "After adding elements, numbers.empty(): " << numbers.empty() << '\n';
}

{ // size: returns the number of elements 
	std::set<int> nums{ 1, 3, 5, 7 };

	std::cout << "nums contains " << nums.size() << " elements.\n";
}

{ // max_size: returns the maximum possible number of elements 
	std::set<char> s;
	std::cout << "Maximum size of a 'set' is " << s.max_size() << "\n";
}

{ // clear: clears the contents 
}

{ // insert: inserts elements
	std::set<int> set;

	auto result_1 = set.insert(3);
	assert(result_1.first != set.end()); // it's a valid iterator
	assert(*result_1.first == 3);
	if (result_1.second)
		std::cout << "insert done\n";

	auto result_2 = set.insert(3);
	assert(result_2.first == result_1.first); // same iterator
	assert(*result_2.first == 3);
	if (!result_2.second)
		std::cout << "no insertion\n";
}

{ // emplace(c++11): constructs element in-place 
	set_insert();
	timeit(set_insert, "insert");
	timeit(set_emplace, "emplace");
	timeit(set_insert, "insert");
	timeit(set_emplace, "emplace");
}

{ // emplace_hint(c++11): constructs elements in-place using a hint 
	// reference: http://en.cppreference.com/w/cpp/container/set/emplace_hint
}

{ // erase: erases elements 
	std::set<int> c = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	// erase all odd numbers from c
	for (auto it = c.begin(); it != c.end();)
	if (*it % 2 == 1)
		it = c.erase(it);
	else
		++it;
	for (int n : c)
		std::cout << n << ' ';
}

{ // swap: swaps the contents 
}

{ // count: returns the number of elements matching specific key 
}

{ // find: finds element with specific key 
	std::set<int> example = { 1, 2, 3, 4 };

	auto search = example.find(2);
	if (search != example.end()) {
		std::cout << "Found " << (*search) << '\n';
	}
	else {
		std::cout << "Not found\n";
	}
}

{ // equal_range: returns range of elements matching a specific key 
}

{ // lower_bound: returns an iterator to the first element not less than the given key 
}

{ // upper_bound: returns an iterator to the first element greater than the given key 
}

{ // key_comp: returns the function that compares keys 
}

{ // value_comp: returns the function that compares keys in objects of type value_type
}

	return 0;
}
