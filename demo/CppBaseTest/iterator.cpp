#include "iterator.hpp"
#include <iterator>
#include <iostream>
#include <typeinfo>
#include <list>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>

// reference: http://www.cplusplus.com/reference/iterator/

namespace iterator_ {
///////////////////////////////////////////////////
class MyIterator : public std::iterator<std::input_iterator_tag, int>
{
public:
	MyIterator(int* x) :p(x) {}
	MyIterator(const MyIterator& mit) : p(mit.p) {}
	MyIterator& operator++() { ++p; return *this; }
	MyIterator operator++(int) { MyIterator tmp(*this); operator++(); return tmp; }
	bool operator==(const MyIterator& rhs) const { return p == rhs.p; }
	bool operator!=(const MyIterator& rhs) const { return p != rhs.p; }
	int& operator*() { return *p; }
private:
	int* p;
};

int test_iterator_1()
{
	// std::iterator: 迭代器基类
	int numbers[] = { 10, 20, 30, 40, 50 };
	MyIterator from(numbers);
	MyIterator until(numbers + 5);
	for (MyIterator it = from; it != until; it++)
		std::cout << *it << ' ';
	std::cout << '\n';

	return 0;
}

/////////////////////////////////////////////////
int test_iterator_2()
{
	// std::iterator_traits: 定义迭代器属性
	typedef std::iterator_traits<int*> traits;
	if (typeid(traits::iterator_category) == typeid(std::random_access_iterator_tag))
		std::cout << "int* is a random-access iterator" << std::endl;;

	return 0;
}

///////////////////////////////////////////////
int test_iterator_3()
{
	// std::advance: 将迭代器推进到n个元素位置，可以是负值
	std::list<int> mylist;
	for (int i = 0; i<10; i++) mylist.push_back(i * 10);

	std::list<int>::iterator it = mylist.begin();

	std::advance(it, 5);

	std::cout << "The sixth element in mylist is: " << *it << '\n'; // 50

	return 0;
}

////////////////////////////////////////////////////////
int test_iterator_4()
{
	// std::back_inserter: 构造一个在x的末尾插入新元素的后插入迭代器
	std::vector<int> foo, bar;
	for (int i = 1; i <= 5; i++) {
		foo.push_back(i); bar.push_back(i * 10);
	}

	std::copy(bar.begin(), bar.end(), std::back_inserter(foo));

	std::cout << "foo contains:";
	for (std::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it; // 1 2 3 4 5 10 20 30 40 50
	std::cout << '\n';

	return 0;
}

//////////////////////////////////////////////////////
int test_iterator_5()
{
	// std::begin: 返回指向序列中第一个元素的迭代器
	// std::end: 返回指向序列中过去的最后一个元素的迭代器
	int foo[] = { 10, 20, 30, 40, 50 };
	std::vector<int> bar;

	// iterate foo: inserting into bar
	for (auto it = std::begin(foo); it != std::end(foo); ++it)
		bar.push_back(*it);

	// iterate bar: print contents:
	std::cout << "bar contains:";
	for (auto it = std::begin(bar); it != std::end(bar); ++it)
		std::cout << ' ' << *it; // 10 20 30 40 50
	std::cout << '\n';

	return 0;
}

//////////////////////////////////////////
int test_iterator_6()
{
	// std::distance: 计算first和last之间的元素数量
	std::list<int> mylist;
	for (int i = 0; i<10; i++) mylist.push_back(i * 10);

	std::list<int>::iterator first = mylist.begin();
	std::list<int>::iterator last = mylist.end();

	std::cout << "The distance is: " << std::distance(first, last) << '\n'; // 10

	return 0;
}

////////////////////////////////////////
int test_iterator_7()
{
	// std::front_inserter: 构造一个前插入迭代器，在x的开头插入新元素
	std::deque<int> foo, bar;
	for (int i = 1; i <= 5; i++) {
		foo.push_back(i); bar.push_back(i * 10);
	}

	std::copy(bar.begin(), bar.end(), std::front_inserter(foo));

	std::cout << "foo contains:";
	for (std::deque<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it; // 50 40 30 20 10 1 2 3 4 5
	std::cout << '\n';

	return 0;
}

//////////////////////////////////////////////////
int test_iterator_8()
{
	// std::inserter: 构造一个插入迭代器，从指向的位置开始，在连续的位置中插入新元素x
	std::list<int> foo, bar;
	for (int i = 1; i <= 5; i++) {
		foo.push_back(i); bar.push_back(i * 10);
	}

	std::list<int>::iterator it = foo.begin();
	std::advance(it, 3);

	std::copy(bar.begin(), bar.end(), std::inserter(foo, it));

	std::cout << "foo contains:";
	for (std::list<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it; // 1 2 3 10 20 30 40 50 4 5
	std::cout << '\n';

	return 0;
}

////////////////////////////////////////////////////
int test_iterator_9()
{
	// std::make_move_iterator: 从it构造一个move_iterator对象
	std::vector<std::string> foo(3);
	std::vector<std::string> bar{ "one", "two", "three" };

	std::copy(std::make_move_iterator(bar.begin()), std::make_move_iterator(bar.end()), foo.begin());

	// bar now contains unspecified values; clear it:
	bar.clear();

	std::cout << "foo:";
	for (std::string& x : foo) std::cout << ' ' << x; // one two three
	std::cout << '\n';

	return 0;
}

//////////////////////////////////////////////
int test_iterator_10()
{
	// std::next: 获取下一个元素的迭代器
	std::list<int> mylist;
	for (int i = 0; i<10; i++) mylist.push_back(i * 10);

	std::cout << "mylist:";
	std::for_each(mylist.begin(), std::next(mylist.begin(), 5), [](int x) {std::cout << ' ' << x; }); // 0 10 20 30 40 50

	std::cout << '\n';

	return 0;
}

//////////////////////////////////////
int test_iterator_11()
{
	// std::prev: 获取前一个元素的迭代器
	std::list<int> mylist;
	for (int i = 0; i<10; i++) mylist.push_back(i * 10);

	std::cout << "The last element is " << *std::prev(mylist.end()) << '\n'; // 90

	return 0;
}

////////////////////////////////////////
int test_iterator_12()
{
	// std::back_insert_iterator: 在容器末尾插入元素的迭代器
	std::vector<int> foo, bar;
	for (int i = 1; i <= 5; i++) {
		foo.push_back(i); bar.push_back(i * 10);
	}

	std::back_insert_iterator< std::vector<int> > back_it(foo);

	std::copy(bar.begin(), bar.end(), back_it);

	std::cout << "foo:";
	for (std::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it; // 1 2 3 4 5 10 20 30 40 50 
	std::cout << '\n';

	return 0;
}

///////////////////////////////////////////////
int test_iterator_13()
{
	// std::front_insert_iterator: 在容器开头插入元素的迭代器
	std::deque<int> foo, bar;
	for (int i = 1; i <= 5; i++) {
		foo.push_back(i); bar.push_back(i * 10);
	}

	std::front_insert_iterator< std::deque<int> > front_it(foo);

	std::copy(bar.begin(), bar.end(), front_it);

	std::cout << "foo:";
	for (std::deque<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it; // 50 40 30 20 10 1 2 3 4 5
	std::cout << '\n';

	return 0;
}

//////////////////////////////////////////////
int test_iterator_14()
{
	// std::insert_iterator: 插入迭代器
	std::list<int> foo, bar;
	for (int i = 1; i <= 5; i++) {
		foo.push_back(i); bar.push_back(i * 10);
	}

	std::list<int>::iterator it = foo.begin();
	std::advance(it, 3);

	std::insert_iterator< std::list<int> > insert_it(foo, it);

	std::copy(bar.begin(), bar.end(), insert_it);

	std::cout << "foo:";
	for (std::list<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it; // 1 2 3 10 20 30 40 50 4 5
	std::cout << '\n';

	return 0;
}

///////////////////////////////////////////////////////
int test_iterator_15()
{
	// std::istreambuf_iterator: 输入流缓存迭代器
	std::istreambuf_iterator<char> eos;                    // end-of-range iterator
	std::istreambuf_iterator<char> iit(std::cin.rdbuf()); // stdin iterator
	std::string mystring;

	std::cout << "Please, enter your name: ";

	while (iit != eos && *iit != '\n') mystring += *iit++;

	std::cout << "Your name is " << mystring << ".\n";

	return 0;
}

///////////////////////////////////////////////////
int test_iterator_16()
{
	// std::istream_iterator: 从输入流读取连续元素的输入迭代器
	double value1, value2;
	std::cout << "Please, insert two values: ";

	std::istream_iterator<double> eos;              // end-of-stream iterator
	std::istream_iterator<double> iit(std::cin);   // stdin iterator

	if (iit != eos) value1 = *iit;

	++iit;
	if (iit != eos) value2 = *iit;

	std::cout << value1 << "*" << value2 << "=" << (value1*value2) << '\n';

	return 0;
}

///////////////////////////////////////////////////////
int test_iterator_17()
{
	// std::move_iterator: 用于解引用(Dereference)到一个右值引用(Rvalue reference)的迭代器
	std::vector<std::string> foo(3);
	std::vector<std::string> bar{ "one", "two", "three" };

	typedef std::vector<std::string>::iterator Iter;

	std::copy(std::move_iterator<Iter>(bar.begin()), std::move_iterator<Iter>(bar.end()), foo.begin());

	// bar now contains unspecified values; clear it:
	bar.clear();

	std::cout << "foo:";
	for (std::string& x : foo) std::cout << ' ' << x; // one two three
	std::cout << '\n';

	return 0;
}

///////////////////////////////////////////////////////
int test_iterator_18()
{
	// std::ostreambuf_iterator: 输出流缓存迭代器
	std::string mystring("Some text here...\n");
	std::ostreambuf_iterator<char> out_it(std::cout); // stdout iterator

	std::copy(mystring.begin(), mystring.end(), out_it); // Some text here...

	return 0;
}

/////////////////////////////////////////
int test_iterator_19()
{
	// std::ostream_iterator: 顺序写入输出流的输出迭代器
	std::vector<int> myvector;
	for (int i = 1; i<10; ++i) myvector.push_back(i * 10);

	std::ostream_iterator<int> out_it(std::cout, ", ");
	std::copy(myvector.begin(), myvector.end(), out_it); // 10, 20, 30, 40, 50, 60, 70, 80, 90, 

	return 0;
}

///////////////////////////////////////////
int test_iterator_20()
{
	// std::reverse_iterator: 反向迭代器
	std::vector<int> myvector;
	for (int i = 0; i<10; i++) myvector.push_back(i);

	typedef std::vector<int>::iterator iter_type;
							      // ? 0 1 2 3 4 5 6 7 8 9 ?
	iter_type from(myvector.begin());                     //   ^
							      //         ------>
	iter_type until(myvector.end());                      //                       ^
							      //
	std::reverse_iterator<iter_type> rev_until(from);     // ^
							      //         <------
	std::reverse_iterator<iter_type> rev_from(until);     //                     ^

	std::cout << "myvector:";
	while (rev_from != rev_until)
		std::cout << ' ' << *rev_from++; // 9 8 7 6 5 4 3 2 1 0
	std::cout << '\n';

	return 0;
}

} // namespace iterator_

