#include "fill.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <list>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52895344

///////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/algorithm/fill/
int test_fill_1()
{
	std::vector<int> myvector(8); // myvector: 0 0 0 0 0 0 0 0

	std::fill(myvector.begin(), myvector.begin() + 4, 5); // myvector: 5 5 5 5 0 0 0 0
	std::fill(myvector.begin() + 3, myvector.end() - 2, 8); // myvector: 5 5 5 8 8 8 0 0

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}

int test_fill_2()
{
	float arr[10];

	std::fill(&arr[0], &arr[0] + 10, 1.23);
	for (int i = 0; i < 10; i++)
		fprintf(stderr, "%f  ", arr[i]);
	fprintf(stderr, "\n");

	return 0;
}

/////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/algorithm/fill_n/
int test_fill_n_1()
{
	std::vector<int> myvector(8, 10); // myvector: 10 10 10 10 10 10 10 10

	std::fill_n(myvector.begin(), 4, 20); // myvector: 20 20 20 20 10 10 10 10
	std::fill_n(myvector.begin() + 3, 3, 33); // myvector: 20 20 20 33 33 33 10 10

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}
