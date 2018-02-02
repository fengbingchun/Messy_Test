#include "numeric.hpp"
#include <iostream>
#include <functional>
#include <numeric>

// Blog: http://blog.csdn.net/fengbingchun/article/details/77949873

// reference: http://www.cplusplus.com/reference/numeric/

namespace numeric_ {

////////////////////////////////////////////////////
/*
std::accumulate: The behavior of this function template is equivalent to :
template <class InputIterator, class T>
T accumulate (InputIterator first, InputIterator last, T init)
{
	while (first!=last) {
		init = init + *first;  // or: init=binary_op(init,*first) for the binary_op version
		++first;
	}
	return init;
}
*/

static int myfunction(int x, int y) { return x + 2 * y; }

struct myclass {
	int operator()(int x, int y) { return x + 3 * y; }
} myobject;

int test_numeric_accumulate()
{
	int init = 100;
	int numbers[] = { 10, 20, 30 };

	std::cout << "using default accumulate: ";
	std::cout << std::accumulate(numbers, numbers + 3, init); // 160
	std::cout << '\n';

	std::cout << "using functional's minus: ";
	std::cout << std::accumulate(numbers, numbers + 3, init, std::minus<int>()); // 40 std::minus => x - y
	std::cout << '\n';

	std::cout << "using custom function: ";
	std::cout << std::accumulate(numbers, numbers + 3, init, myfunction); // 220
	std::cout << '\n';

	std::cout << "using custom object: ";
	std::cout << std::accumulate(numbers, numbers + 3, init, myobject); // 280
	std::cout << '\n';

	return 0;
}

///////////////////////////////////////////////////
/*
std::adjacent_difference: The behavior of this function template is equivalent to
template <class InputIterator, class OutputIterator>
OutputIterator adjacent_difference (InputIterator first, InputIterator last, OutputIterator result)
{
	if (first!=last) {
		typename iterator_traits<InputIterator>::value_type val,prev;
		*result = prev = *first;
		while (++first!=last) {
			val = *first;
			*++result = val - prev;  // or: *++result = binary_op(val,prev)
			prev = val;
		}
		++result;
	}
	return result;
}
*/

static int myop(int x, int y) { return x + y; }

int test_numeric_adjacent_difference()
{
	int val[] = { 1, 2, 3, 5, 9, 11, 12 };
	int result[7];

	std::adjacent_difference(val, val + 7, result);
	std::cout << "using default adjacent_difference: ";
	for (int i = 0; i<7; i++) std::cout << result[i] << ' '; // 1 1 1 2 4 2 1
	std::cout << '\n';

	std::adjacent_difference(val, val + 7, result, std::multiplies<int>()); // x * y
	std::cout << "using functional operation multiplies: ";
	for (int i = 0; i<7; i++) std::cout << result[i] << ' '; // 1 2 6 15 45 99 132
	std::cout << '\n';

	std::adjacent_difference(val, val + 7, result, myop); // 1 3 5 8 14 20 23
	std::cout << "using custom function: ";
	for (int i = 0; i<7; i++) std::cout << result[i] << ' ';
	std::cout << '\n';

	return 0;
}

////////////////////////////////////////////////
/*
std::inner_product: The behavior of this function template is equivalent to:
template <class InputIterator1, class InputIterator2, class T>
T inner_product (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init)
{
	while (first1!=last1) {
		init = init + (*first1)*(*first2);
		// or: init = binary_op1 (init, binary_op2(*first1,*first2));
		++first1; ++first2;
	}
	return init;
}
*/

static int myaccumulator(int x, int y) { return x - y; }
static int myproduct(int x, int y) { return x + y; }

int test_numeric_inner_product()
{
	int init = 100;
	int series1[] = { 10, 20, 30 };
	int series2[] = { 1, 2, 3 };

	std::cout << "using default inner_product: ";
	std::cout << std::inner_product(series1, series1 + 3, series2, init); // 240
	std::cout << '\n';

	std::cout << "using functional operations: ";
	std::cout << std::inner_product(series1, series1 + 3, series2, init, 
		std::minus<int>(), std::divides<int>()); // 70
	std::cout << '\n';

	std::cout << "using custom functions: ";
	std::cout << std::inner_product(series1, series1 + 3, series2, init,
		myaccumulator, myproduct); // 34
	std::cout << '\n';

	return 0;
}

//////////////////////////////////////////////
/*
std::partial_sum: The behavior of this function template is equivalent to:
template <class InputIterator, class OutputIterator>
OutputIterator partial_sum (InputIterator first, InputIterator last, OutputIterator result)
{
	if (first!=last) {
		typename iterator_traits<InputIterator>::value_type val = *first;
		*result = val;
		while (++first!=last) {
			val = val + *first;   // or: val = binary_op(val,*first)
			*++result = val;
		}
		++result;
	}
	return result;
}
*/

static int myop_(int x, int y) { return x + y + 1; }

int test_numeric_partial_sum()
{
	int val[] = { 1, 2, 3, 4, 5 };
	int result[5];

	std::partial_sum(val, val + 5, result);
	std::cout << "using default partial_sum: ";
	for (int i = 0; i<5; i++) std::cout << result[i] << ' '; // 1 3 6 10 15
	std::cout << '\n';

	std::partial_sum(val, val + 5, result, std::multiplies<int>());
	std::cout << "using functional operation multiplies: ";
	for (int i = 0; i<5; i++) std::cout << result[i] << ' '; // 1 2 6 24 120
	std::cout << '\n';

	std::partial_sum(val, val + 5, result, myop_);
	std::cout << "using custom function: ";
	for (int i = 0; i<5; i++) std::cout << result[i] << ' '; // 1 4 8 13 19
	std::cout << '\n';

	return 0;
}

///////////////////////////////////////////////
/*
std::iota: The behavior of this function template is equivalent to:
template <class ForwardIterator, class T>
void iota (ForwardIterator first, ForwardIterator last, T val)
{
	while (first!=last) {
		*first = val;
		++first;
		++val;
	}
}
*/

int test_numeric_iota()
{
	int numbers[10];

	std::iota(numbers, numbers + 10, 100);

	std::cout << "numbers:";
	for (int& i : numbers) std::cout << ' ' << i; // 100 101 102 103 104 105 106 107 108 109
	std::cout << '\n';

	return 0;
}

} // namespace numeric_
