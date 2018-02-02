#include "transform.hpp"
#include <algorithm> // std::transform
#include <string>
#include <cctype> // std::toupper
#include <iostream>
#include <vector>
#include <functional> // std::plus c++14

// Blog: http://blog.csdn.net/fengbingchun/article/details/63252470

/*
// reference: http://en.cppreference.com/w/cpp/algorithm/transform

template< class InputIt, class OutputIt, class UnaryOperation >
OutputIt transform( InputIt first1, InputIt last1, OutputIt d_first, UnaryOperation unary_op )
{
  while (first1 != last1) {
  *d_first++ = binary_op(*first1++, *first2++);
  }
  return d_first;
}

template< class InputIt1, class InputIt2, class OutputIt, class BinaryOperation >
OutputIt transform( InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt d_first, BinaryOperation binary_op );

std::transform applies the given function to a range and stores the result in another range, beginning at d_first.
(1): The unary operation unary_op is applied to the range defined by [first1, last1).
(2): The binary operation binary_op is applied to pairs of elements from two ranges:
     one defined by [first1, last1) and the other beginning at first2.

Parameters:
  first1, last1: the first range of elements to transform
  first2: the beginning of the second range of elements to transform
  d_first:the beginning of the destination range, may be equal to first1 or first2
  unary_op: unary operation function object that will be applied.
  binary_op: binary operation function object that will be applied.
Return value: Output iterator to the element past the last element transformed.

std::for_each: ignores the return value of the function and guarantees order of execution.
std::transform: assigns the return value to the iterator, and does not guarantee the order of execution.
*/

int test_transform1()
{
	std::string s("Hello");
	std::transform(s.begin(), s.end(), s.begin(),
		[](unsigned char c) { return std::toupper(c); });
	std::cout << s << std::endl; // HELLO

	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	std::cout << s << std::endl; // hello

	////////////////////////////////
	std::vector<int> arr{ 1, 3, 5 };
	std::vector<int> arr2{ 1, 3, 5 };
	std::vector<int> arr3{ 1, 3, 5 };

	std::transform(arr.begin(), arr.end(), arr.begin(),
		[](int d) -> int {return d * 5; }); // for_each
	for (auto value : arr) {
		std::cout << value << "    "; // 5 15 25
	}
	std::cout<<std::endl;

	std::for_each(arr2.begin(), arr2.end(), [](int& a) {a *= 5; });
	for (auto value : arr2) {
		std::cout << value << "    "; // 5 15 25
	}
	std::cout << std::endl;

	for (auto& value : arr3) {
		value *= 5;
	}
	for (auto value : arr3) {
		std::cout << value << "    "; // 5 15 25
	}
	std::cout << std::endl;

	std::vector<std::string> names = { "hi", "test", "foo" };
	std::vector<std::size_t> name_sizes;

	///////////////////////////
	std::transform(names.begin(), names.end(), std::back_inserter(name_sizes),
		[](std::string name) { return name.size(); });
	for (auto value : name_sizes) {
		std::cout << value << "    "; // 2 4 3
	}
	std::cout << std::endl;

	std::for_each(name_sizes.begin(), name_sizes.end(), [](std::size_t name_size) {
		std::cout << name_size << "    "; // 2 4 3
	});
	std::cout << std::endl;

	return 0;
}

/////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/algorithm/transform/
static int op_increase(int i) { return ++i; }

int test_transform2()
{
	std::vector<int> foo;
	std::vector<int> bar;

	// set some values:
	for (int i = 1; i<6; i++)
		foo.push_back(i * 10); // foo: 10 20 30 40 50

	bar.resize(foo.size()); // allocate space

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

