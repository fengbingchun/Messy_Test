#include "reverse.hpp"
#include <iostream>
#include <algorithm> // std::reverse/std::reverse_copy
#include <vector>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/70490297

/* The behavior of this function template(std::reverse) is equivalent to
template <class BidirectionalIterator>
void reverse (BidirectionalIterator first, BidirectionalIterator last)
{
	while ((first!=last)&&(first!=--last)) {
		std::iter_swap (first,last);
		++first;
	}
} */

/* The behavior of this function template(std::reverse_copy) is equivalent to:
template <class BidirectionalIterator, class OutputIterator>
OutputIterator reverse_copy (BidirectionalIterator first,
		BidirectionalIterator last, OutputIterator result)
{
	while (first!=last) {
		--last;
		*result = *last;
		++result;
	}
	return result;
} */

/////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/algorithm/reverse
int test_reverse_1()
{
	std::vector<int> v({ 1, 2, 3 });
	std::reverse(std::begin(v), std::end(v));
	std::cout << v[0] << v[1] << v[2] << '\n';

	int a[] = { 4, 5, 6, 7 };
	std::reverse(std::begin(a), std::end(a));
	std::cout << a[0] << a[1] << a[2] << a[3] << '\n';

	return 0;
}

/////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/algorithm/reverse/
int test_reverse_2()
{
	std::vector<int> myvector;

	// set some values:
	for (int i = 1; i<10; ++i) myvector.push_back(i);   // 1 2 3 4 5 6 7 8 9

	//std::reverse(myvector.begin(), myvector.end());    // 9 8 7 6 5 4 3 2 1
	std::reverse(myvector.begin(), myvector.begin()+5);    // 5 4 3 2 1 6 7 8 9

	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::string str{ "abcdef" };
	std::reverse(str.begin(), str.end());
	fprintf(stderr, "str: %s\n", str.c_str());

	return 0;
}

/////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/algorithm/reverse_copy/
int test_reverse_copy_1()
{
	int myints[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<int> myvector;

	myvector.resize(5);    // allocate space

	std::reverse_copy(myints, myints + 5, myvector.begin());

	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';

	return 0;
}

//////////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/algorithm/reverse_copy
int test_reverse_copy_2()
{
	std::vector<int> v({ 1, 2, 3 });
	for (const auto& value : v) {
		std::cout << value << " ";
	}
	std::cout << '\n';

	std::vector<int> destination(3);
	std::reverse_copy(std::begin(v), std::end(v), std::begin(destination));
	for (const auto& value : destination) {
		std::cout << value << " ";
	}
	std::cout << '\n';

	return 0;
}
