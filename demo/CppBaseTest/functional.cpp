#include "functional.hpp"
#include <functional>
#include <iostream>
#include <algorithm>
#include <utility>
#include <iterator>
#include <numeric>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78006735

// reference: http://www.cplusplus.com/reference/functional/

namespace functional_ {
///////////////////////////////////////////////////////
// a function: (also works with function object: std::divides<double> my_divide;)
static double my_divide(double x, double y) { return x / y; }

struct MyPair {
	double a, b;
	double multiply() { return a*b; }
};

int test_functional_bind()
{
	using namespace std::placeholders;    // adds visibility of _1, _2, _3,...

	// binding functions:
	auto fn_five = std::bind(my_divide, 10, 2);               // returns 10/2
	std::cout << fn_five() << '\n';                           // 5

	auto fn_half = std::bind(my_divide, _1, 2);               // returns x/2
	std::cout << fn_half(10) << '\n';                         // 5

	auto fn_invert = std::bind(my_divide, _2, _1);            // returns y/x
	std::cout << fn_invert(10, 2) << '\n';                    // 0.2

	auto fn_rounding = std::bind<int>(my_divide, _1, _2);     // returns int(x/y)
	std::cout << fn_rounding(10, 3) << '\n';                  // 3

	MyPair ten_two{ 10, 2 };

	// binding members:
	auto bound_member_fn = std::bind(&MyPair::multiply, _1); // returns x.multiply()
	std::cout << bound_member_fn(ten_two) << '\n';           // 20

	auto bound_member_data = std::bind(&MyPair::a, ten_two); // returns ten_two.a
	std::cout << bound_member_data() << '\n';                // 10

	return 0;
}

//////////////////////////////////////////////
int test_functional_cref()
{
	int foo(10);

	auto bar = std::cref(foo);
	std::cout << bar << '\n'; // 10

	++foo;
	std::cout << bar << '\n'; // 11

	return 0;
}

/////////////////////////////////////////////
int test_functional_ref()
{
	int foo(10);

	auto bar = std::ref(foo);
	std::cout << bar << '\n'; // 10

	++bar;
	std::cout << foo << '\n'; // 11
	std::cout << bar << '\n'; // 11

	return 0;
}

//////////////////////////////////////////////////
struct int_holder {
	int value;
	int triple() { return value * 3; }
};

int test_functional_mem_fn()
{
	int_holder five{ 5 };

	// call member directly:
	std::cout << five.triple() << '\n'; // 15

	// same as above using a mem_fn:
	auto triple = std::mem_fn(&int_holder::triple);
	std::cout << triple(five) << '\n'; // 15

	return 0;
}

//////////////////////////////////////
struct IsOdd {
	bool operator() (const int& x) const { return x % 2 == 1; }
	typedef int argument_type;
};

int test_functional_not1()
{
	int values[] = { 1, 2, 3, 4, 5 };
	int cx = std::count_if(values, values + 5, std::not1(IsOdd()));
	std::cout << "There are " << cx << " elements with even values.\n"; // 2

	return 0;
}

////////////////////////////////////////
int test_functional_not2()
{
	int foo[] = { 10, 20, 30, 40, 50 };
	int bar[] = { 0, 15, 30, 45, 60 };
	std::pair<int*, int*> firstmatch, firstmismatch;
	firstmismatch = std::mismatch(foo, foo + 5, bar, std::equal_to<int>());
	firstmatch = std::mismatch(foo, foo + 5, bar, std::not2(std::equal_to<int>()));
	std::cout << "First mismatch in bar is " << *firstmismatch.second << '\n'; // 0
	std::cout << "First match in bar is " << *firstmatch.second << '\n'; // 30

	return 0;
}

//////////////////////////////////////////
int test_functional_binary_negate()
{
	std::equal_to<int> equality;
	std::binary_negate < std::equal_to<int> > nonequality(equality);
	int foo[] = { 10, 20, 30, 40, 50 };
	int bar[] = { 0, 15, 30, 45, 60 };

	std::pair<int*, int*> firstmatch, firstmismatch;
	firstmismatch = std::mismatch(foo, foo + 5, bar, equality);
	firstmatch = std::mismatch(foo, foo + 5, bar, nonequality);
	std::cout << "First mismatch in bar is " << *firstmismatch.second << "\n"; // 0
	std::cout << "First match in bar is " << *firstmatch.second << "\n"; // 30

	return 0;
}

////////////////////////////////////////////////////
struct IsOdd_class {
	bool operator() (const int& x) const { return x % 2 == 1; }
	typedef int argument_type;
} IsOdd_object;

int test_functional_unary_negate()
{
	std::unary_negate<IsOdd_class> IsEven_object(IsOdd_object);
	int values[] = { 1, 2, 3, 4, 5 };
	int cx;
	cx = std::count_if(values, values + 5, IsEven_object);
	std::cout << "There are " << cx << " elements with even values.\n"; // 2

	return 0;
}

////////////////////////////////////////////
// a function:
static int half(int x) { return x / 2; }

// a function object class:
struct third_t {
	int operator()(int x) { return x / 3; }
};

// a class with data members:
struct MyValue {
	int value;
	int fifth() { return value / 5; }
};

int test_functional_function()
{
	std::function<int(int)> fn1 = half;                       // function
	std::function<int(int)> fn2 = &half;                      // function pointer
	std::function<int(int)> fn3 = third_t();                  // function object
	std::function<int(int)> fn4 = [](int x){return x / 4; };  // lambda expression
	std::function<int(int)> fn5 = std::negate<int>();         // standard function object

	std::cout << "fn1(60): " << fn1(60) << '\n'; // 30
	std::cout << "fn2(60): " << fn2(60) << '\n'; // 30
	std::cout << "fn3(60): " << fn3(60) << '\n'; // 20
	std::cout << "fn4(60): " << fn4(60) << '\n'; // 15
	std::cout << "fn5(60): " << fn5(60) << '\n'; // -06

	// stuff with members:
	std::function<int(MyValue)> value = &MyValue::value;  // pointer to data member
	std::function<int(MyValue)> fifth = &MyValue::fifth;  // pointer to member function

	MyValue sixty{ 60 };

	std::cout << "value(sixty): " << value(sixty) << '\n'; // 60
	std::cout << "fifth(sixty): " << fifth(sixty) << '\n'; // 12

	return 0;
}

////////////////////////////////////////////////
int test_functional_reference_wrapper()
{
	int a(10), b(20), c(30);

	// an array of "references":
	std::reference_wrapper<int> refs[] = { a, b, c };

	std::cout << "refs:";
	for (int& x : refs) std::cout << ' ' << x; // 10 20 30
	std::cout << '\n';

	return 0;
}

//////////////////////////////////////////
int test_functional_bit()
{
{
	int values[] = { 100, 200, 300, 400, 500 };
	int masks[] = { 0xf, 0xf, 0xf, 255, 255 };
	int results[5];

	std::transform(values, std::end(values), masks, results, std::bit_and<int>());

	std::cout << "results:";
	for (const int& x : results)
		std::cout << ' ' << x; // 4 8 12 144 244
	std::cout << '\n';
}

{
	int flags[] = { 1, 2, 4, 8, 16, 32, 64, 128 };
	int acc = std::accumulate(flags, std::end(flags), 0, std::bit_or<int>());
	std::cout << "accumulated: " << acc << '\n'; // 255
}

{
	int flags[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int acc = std::accumulate(flags, std::end(flags), 0, std::bit_xor<int>());
	std::cout << "xor: " << acc << '\n'; // 11
}

	return 0;
}

//////////////////////////////////////////
int test_functional_arithmetic()
{
{
	int first[] = { 1, 2, 3, 4, 5 };
	int second[] = { 10, 20, 30, 40, 50 };
	int results[5];
	std::transform(first, first + 5, second, results, std::plus<int>());
	for (int i = 0; i<5; i++)
		std::cout << results[i] << ' '; // 11 22 33 44 55
	std::cout << '\n';
}

{
	int numbers[] = { 10, 20, 30 };
	int result;
	result = std::accumulate(numbers, numbers + 3, 100, std::minus<int>());
	std::cout << "The result of 100-10-20-30 is " << result << ".\n"; // 40
}

{
	int numbers[9];
	int factorials[9];
	for (int i = 0; i<9; i++) numbers[i] = i + 1;
	std::partial_sum(numbers, numbers + 9, factorials, std::multiplies<int>());
	for (int i = 0; i<9; i++)
		std::cout << numbers[i] << "! is " << factorials[i] << '\n'; // 1 2 6 24 120 720 5040 40320 362880
}

{
	int first[] = { 10, 40, 90, 40, 10 };
	int second[] = { 1, 2, 3, 4, 5 };
	int results[5];
	std::transform(first, first + 5, second, results, std::divides<int>());
	for (int i = 0; i<5; i++)
		std::cout << results[i] << ' '; // 10 20 30 10 2
	std::cout << '\n';
}

{
	int numbers[] = { 1, 2, 3, 4, 5 };
	int remainders[5];
	std::transform(numbers, numbers + 5, remainders, std::bind2nd(std::modulus<int>(), 2));
	for (int i = 0; i < 5; i++)
		std::cout << numbers[i] << " is " << (remainders[i] == 0 ? "even" : "odd") << '\n';
}

{
	int numbers[] = { 10, -20, 30, -40, 50 };
	std::transform(numbers, numbers + 5, numbers, std::negate<int>());
	for (int i = 0; i<5; i++)
		std::cout << numbers[i] << ' '; // -10 20 -30 40 -50
	std::cout << '\n';
}

	return 0;
}

///////////////////////////////////////
int test_functional_compare()
{
{
	std::pair<int*, int*> ptiter;
	int foo[] = { 10, 20, 30, 40, 50 };
	int bar[] = { 10, 20, 40, 80, 160 };
	ptiter = std::mismatch(foo, foo + 5, bar, std::equal_to<int>());
	std::cout << "First mismatching pair is: " << *ptiter.first; // 30
	std::cout << " and " << *ptiter.second << '\n'; // 40
}

{
	int numbers[] = { 10, 10, 10, 20, 20 };
	int* pt = std::adjacent_find(numbers, numbers + 5, std::not_equal_to<int>()) + 1;
	std::cout << "The first different element is " << *pt << '\n'; // 20
}

{
	int numbers[] = { 20, 40, 50, 10, 30 };
	std::sort(numbers, numbers + 5, std::greater<int>());
	for (int i = 0; i<5; i++)
		std::cout << numbers[i] << ' '; // 50 40 30 20 10
	std::cout << '\n';
}

{
	int foo[] = { 10, 20, 5, 15, 25 };
	int bar[] = { 15, 10, 20 };
	std::sort(foo, foo + 5, std::less<int>());  // 5 10 15 20 25
	std::sort(bar, bar + 3, std::less<int>());  //   10 15 20
	if (std::includes(foo, foo + 5, bar, bar + 3, std::less<int>()))
		std::cout << "foo includes bar.\n"; // foo includes bar
}

{
	int numbers[] = { 20, -30, 10, -40, 0 };
	int cx = std::count_if(numbers, numbers + 5, std::bind2nd(std::greater_equal<int>(), 0));
	std::cout << "There are " << cx << " non-negative elements.\n"; // 3
}

{
	int numbers[] = { 25, 50, 75, 100, 125 };
	int cx = std::count_if(numbers, numbers + 5, std::bind2nd(std::less_equal<int>(), 100));
	std::cout << "There are " << cx << " elements lower than or equal to 100.\n"; // 4
}

	return 0;
}

///////////////////////////////////
int test_functional_logical()
{
{
	bool foo[] = { true, false, true, false };
	bool bar[] = { true, true, false, false };
	bool result[4];
	std::transform(foo, foo + 4, bar, result, std::logical_and<bool>());
	std::cout << std::boolalpha << "Logical AND:\n";
	for (int i = 0; i<4; i++)
		std::cout << foo[i] << " AND " << bar[i] << " = " << result[i] << "\n"; // true false false false
}

{
	bool foo[] = { true, false, true, false };
	bool bar[] = { true, true, false, false };
	bool result[4];
	std::transform(foo, foo + 4, bar, result, std::logical_or<bool>());
	std::cout << std::boolalpha << "Logical OR:\n";
	for (int i = 0; i<4; i++)
		std::cout << foo[i] << " OR " << bar[i] << " = " << result[i] << "\n"; // true true true false
}

{
	bool values[] = { true, false };
	bool result[2];
	std::transform(values, values + 2, result, std::logical_not<bool>());
	std::cout << std::boolalpha << "Logical NOT:\n";
	for (int i = 0; i<2; i++)
		std::cout << "NOT " << values[i] << " = " << result[i] << "\n"; // false true
}

	return 0;
}

////////////////////////////////////////////////
int test_functional_bad_function_call()
{
	std::function<int(int, int)> foo = std::plus<int>();
	std::function<int(int, int)> bar;

	try {
		std::cout << foo(10, 20) << '\n'; // 30
		std::cout << bar(10, 20) << '\n';
	} catch (std::bad_function_call& e)
	{
		std::cout << "ERROR: Bad function call\n"; // ERROR: Bad function call
	}

	return 0;
}

//////////////////////////////////////////////////
int test_functional_hash()
{
	char nts1[] = "Test";
	char nts2[] = "Test";
	std::string str1(nts1);
	std::string str2(nts2);

	std::hash<char*> ptr_hash;
	std::hash<std::string> str_hash;

	std::cout << "same hashes:\n" << std::boolalpha;
	std::cout << "nts1 and nts2: " << (ptr_hash(nts1) == ptr_hash(nts2)) << '\n'; // false
	std::cout << "str1 and str2: " << (str_hash(str1) == str_hash(str2)) << '\n'; // true

	return 0;
}

/////////////////////////////////////////
int test_functional_is_bind_expression()
{
	using namespace std::placeholders;  // introduces _1
	auto increase_int = std::bind(std::plus<int>(), _1, 1);

	std::cout << std::boolalpha;
	std::cout << std::is_bind_expression<decltype(increase_int)>::value << '\n'; // true

	return 0;
}

/////////////////////////////////////////////////
int test_functional_is_placeholder()
{
	using namespace std::placeholders;  // introduces _1

	std::cout << std::is_placeholder<decltype(_1)>::value << '\n'; // 1
	std::cout << std::is_placeholder<decltype(_2)>::value << '\n'; // 2
	std::cout << std::is_placeholder<int>::value << '\n'; // 0

	return 0;
}

} // namespace functional_
