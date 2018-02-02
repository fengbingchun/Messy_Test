#include "ratio.hpp"
#include <iostream>
#include <ratio>

// Blog: http://blog.csdn.net/fengbingchun/article/details/72934929

//////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/ratio/
int test_ratio_1()
{
	typedef std::ratio<1, 3> one_third;
	typedef std::ratio<2, 4> two_fourths;
	typedef std::ratio<2, 3> two_thirds;
	typedef std::ratio<1, 2> one_half;

	std::cout << "one_third= " << one_third::num << "/" << one_third::den << std::endl;
	std::cout << "two_fourths= " << two_fourths::num << "/" << two_fourths::den << std::endl; // Note: 1/2
	std::cout << "two_thirds= " << two_thirds::num << "/" << two_thirds::den << std::endl;
	std::cout << "one_half= " << one_half::num << "/" << one_half::den << std::endl;
	std::cout << std::endl;

{ // std::ratio
	typedef std::ratio_add<one_third, two_fourths> sum;

	std::cout << "sum= " << sum::num << "/" << sum::den;
	std::cout << " (which is: " << (double(sum::num) / sum::den) << ")" << std::endl;
	std::cout << "1 kilogram has " << (std::kilo::num / std::kilo::den) << " grams";
	std::cout << std::endl;
}

{ // std::ratio_add
	typedef std::ratio_add<one_half, two_thirds> sum;

	std::cout << "sum = " << sum::num << "/" << sum::den;
	std::cout << " (which is: " << (double(sum::num) / sum::den) << ")" << std::endl;
}

{ // std::ratio_subtract
	typedef std::ratio_subtract<two_thirds, one_half> diff;

	std::cout << "diff = " << diff::num << "/" << diff::den;
	std::cout << " (which is: " << (double(diff::num) / diff::den) << ")" << std::endl;
}

{ // std::ratio_multiply
	typedef std::ratio_multiply<one_half, one_third> result;

	std::cout << "result = " << result::num << "/" << result::den;
	std::cout << " (which is: " << (double(result::num) / result::den) << ")" << std::endl;
}

{ // std::ratio_divide
	typedef std::ratio_divide<one_half, one_third> result;

	std::cout << "result = " << result::num << "/" << result::den;
	std::cout << " (which is: " << (double(result::num) / result::den) << ")" << std::endl;
	std::cout << std::endl;
}

{ // std::ratio_equal
	std::cout << "1/2 == 2/4 ? " << std::boolalpha;
	std::cout << std::ratio_equal<one_half, two_fourths>::value << std::endl;
}

{ // std::ratio_greater
	std::cout << "1/3 > 1/2 ? " << std::boolalpha;
	std::cout << std::ratio_greater<one_third, one_half>::value << std::endl;
}

{ // std::ratio_greater_equal
	std::cout << "1/3 >= 1/2 ? " << std::boolalpha;
	std::cout << std::ratio_greater_equal<one_third, one_half>::value << std::endl;
}

{ // std::ratio_less
	std::cout << "1/3 < 1/2 ? " << std::boolalpha;
	std::cout << std::ratio_less<one_third, one_half>::value << std::endl;
}

{ // std::ratio_less_equal
	std::cout << "1/3 <= 1/2 ? " << std::boolalpha;
	std::cout << std::ratio_less_equal<one_third, one_half>::value << std::endl;
}

{ // std::ratio_not_equal
	std::cout << "1/2 != 2/4 ? " << std::boolalpha;
	std::cout << std::ratio_not_equal<one_half, two_fourths>::value << std::endl;
}
	std::cout << std::endl;

	return 0;
}

/////////////////////////////////////////////////////////////////////
// reference: https://stackoverflow.com/questions/25005205/why-can-i-have-a-ratio-object-in-c
int test_ratio_2()
{
	// If you don't use a typedef you're creating an instance of std::ratio<1, 3> named one_third,
	// which is not suitable for passing as a type argument.In that case you'll need to use decltype
	// to get to the appropriate type that can be passed to ratio_add
	std::ratio<1, 3> one_third;
	std::ratio<2, 4> two_fourths;
	std::ratio_add<decltype(one_third), decltype(two_fourths)> sum;
	std::cout << decltype(sum)::den << std::endl;

	return 0;
}

/*
template <typename R1, typename R2>
using ratio_add = ratio < R1::num*R2::den+R2::num*R1::den, R1::den*R2::den >

template <typename R1, typename R2>
using ratio_subtract = std::ratio < R1::num*R2::den-R2::num*R1::den, R1::den*R2::den >

template <typename R1, typename R2>
using ratio_multiply = std::ratio < R1::num * R2::num, R1::den * R2::den >;

template <typename R1, typename R2>
using ratio_divide = ratio < R1::num * R2::den, R2::num * R1::den >;

template <class R1, class R2>
struct ratio_equal : integral_constant<bool, R1::num==R2::num && R1::den==R2::den> {}

template <class R1, class R2>
struct ratio_less : integral_constant < bool, R1::num*R2::den < R2::num*R1::den > {};

template <class R1, class R2>
struct ratio_greater : integral_constant < bool, ratio_less<R2,R1>::value > {};

template <class R1, class R2>
struct ratio_greater_equal : integral_constant < bool, !ratio_less<R1,R2>::value > {};

template <class R1, class R2>
struct ratio_less_equal : integral_constant < bool, !ratio_less<R2,R1>::value > {}

template <class R1, class R2>
struct ratio_equal : integral_constant < bool, !ratio_equal<R1,R2>::value > {};
*/
