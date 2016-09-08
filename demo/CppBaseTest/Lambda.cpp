#include "Lambda.hpp"
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>

///////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/lambda
int test_lambda1()
{
	int a = 1, b = 1, c = 1;

	auto m1 = [a, &b, &c]() mutable {
		auto m2 = [a, b, &c]() mutable {
			std::cout << a << b << c << '\n';
			a = 4; b = 4; c = 4;
		};
		a = 3; b = 3; c = 3;
		m2();
	};

	a = 2; b = 2; c = 2;

	m1();                             // calls m2() and prints 123
	std::cout << a << b << c << '\n'; // prints 234

	return 0;
}

///////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/lambda
int test_lambda2()
{
	std::vector<int> c = { 1, 2, 3, 4, 5, 6, 7 };
	int x = 5;
	c.erase(std::remove_if(c.begin(), c.end(), [x](int n) { return n < x; }), c.end());

	std::cout << "c: ";
	std::for_each(c.begin(), c.end(), [](int i){ std::cout << i << ' '; });
	std::cout << '\n';

	// the type of a closure cannot be named, but can be inferred with auto
	auto func1 = [](int i) { return i + 4; };
	std::cout << "func1: " << func1(6) << '\n';

	// like all callable objects, closures can be captured in std::function
	// (this may incur unnecessary overhead)
	std::function<int(int)> func2 = [](int i) { return i + 4; };
	std::cout << "func2: " << func2(6) << '\n';

	return 0;
}

///////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/dd293608.aspx
int test_lambda3()
{
	int m = 0;
	int n = 0;
	[&, n](int a) mutable { m = ++n + a; }(4);
	std::cout << m << std::endl << n << std::endl;

	return 0;
}

//////////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/dd293608.aspx
template <typename C>
void print(const std::string& s, const C& c)
{
	std::cout << s;

	for (const auto& e : c) {
		std::cout << e << " ";
	}

	std::cout << std::endl;
}

void fillVector(std::vector<int>& v)
{
	// A local static variable.
	static int nextValue = 1;

	// The lambda expression that appears in the following call to
	// the generate function modifies and uses the local static 
	// variable nextValue.
	generate(v.begin(), v.end(), [] { return nextValue++; });
	//WARNING: this is not thread-safe and is shown for illustration only
}

int test_lambda4()
{
	// The number of elements in the vector.
	const int elementCount = 9;

	// Create a vector object with each element set to 1.
	std::vector<int> v(elementCount, 1);

	// These variables hold the previous two elements of the vector.
	int x = 1;
	int y = 1;

	// Sets each element in the vector to the sum of the 
	// previous two elements.
	generate_n(v.begin() + 2,
		elementCount - 2,
		[=]() mutable throw() -> int { // lambda is the 3rd parameter
		// Generate current value.
		int n = x + y;
		// Update previous two values.
		x = y;
		y = n;
		return n;
	});
	print("vector v after call to generate_n() with lambda: ", v);

	// Print the local variables x and y.
	// The values of x and y hold their initial values because 
	// they are captured by value.
	std::cout << "x: " << x << " y: " << y << std::endl;

	// Fill the vector with a sequence of numbers
	fillVector(v);
	print("vector v after 1st call to fillVector(): ", v);
	// Fill the vector with the next sequence of numbers
	fillVector(v);
	print("vector v after 2nd call to fillVector(): ", v);

	return 0;
}
