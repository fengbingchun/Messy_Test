#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "funset.hpp"

// reference: googletest/samples

/////////////////////////////////////////////////////////////
// Tests factorial of negative numbers.
TEST(FactorialTest, Negative) {
	// This test is named "Negative", and belongs to the "FactorialTest"
	// test case.
	EXPECT_EQ(1, Factorial(-5));
	EXPECT_EQ(1, Factorial(-1));
	EXPECT_GT(Factorial(-10), 0);
}

// Tests factorial of 0.
TEST(FactorialTest, Zero) {
	EXPECT_EQ(1, Factorial(0));
}

// Tests factorial of positive numbers.
TEST(FactorialTest, Positive) {
	EXPECT_EQ(1, Factorial(1));
	EXPECT_EQ(2, Factorial(2));
	EXPECT_EQ(6, Factorial(3));
	EXPECT_EQ(40320, Factorial(8));
}

// Tests negative input.
TEST(IsPrimeTest, Negative) {
	// This test belongs to the IsPrimeTest test case.
	EXPECT_FALSE(IsPrime(-1));
	EXPECT_FALSE(IsPrime(-2));
	EXPECT_FALSE(IsPrime(INT_MIN));
}

// Tests some trivial cases.
TEST(IsPrimeTest, Trivial) {
	EXPECT_FALSE(IsPrime(0));
	EXPECT_FALSE(IsPrime(1));
	EXPECT_TRUE(IsPrime(2));
	EXPECT_TRUE(IsPrime(3));
}

// Tests positive input.
TEST(IsPrimeTest, Positive) {
	EXPECT_FALSE(IsPrime(4));
	EXPECT_TRUE(IsPrime(5));
	EXPECT_FALSE(IsPrime(6));
	EXPECT_TRUE(IsPrime(23));
}

/////////////////////////////////////////////////////////////
// Tests the default c'tor.
TEST(MyString, DefaultConstructor) {
	const MyString s;

	EXPECT_STREQ(NULL, s.c_string());
	EXPECT_EQ(0u, s.Length()) << "ok";
}

const char kHelloString[] = "Hello, world!";

// Tests the c'tor that accepts a C string.
TEST(MyString, ConstructorFromCString) {
	const MyString s(kHelloString);
	EXPECT_EQ(0, strcmp(s.c_string(), kHelloString));
	EXPECT_EQ(sizeof(kHelloString) / sizeof(kHelloString[0]) - 1, s.Length());
	fprintf(stderr, "Print Info: sizeof(kHelloString): %d, sizeof(kHelloString[0]): %d, s.Length(): %d\n",
		sizeof(kHelloString), sizeof(kHelloString[0]), s.Length());
}

// Tests the copy c'tor.
TEST(MyString, CopyConstructor) {
	const MyString s1(kHelloString);
	const MyString s2 = s1;
	EXPECT_EQ(0, strcmp(s2.c_string(), kHelloString));
}

// Tests the Set method.
TEST(MyString, Set) {
	MyString s;
	s.Set(kHelloString);
	EXPECT_EQ(0, strcmp(s.c_string(), kHelloString));

	// Set should work when the input pointer is the same as the one
	// already in the MyString object.
	s.Set(s.c_string());
	ASSERT_EQ(0, strcmp(s.c_string(), kHelloString));

	// Can we set the MyString to NULL?
	s.Set(NULL);
	EXPECT_STREQ(NULL, s.c_string());
}

////////////////////////////////////////////////////////
// More Assertions
TEST(MoreAssertionsTest, assertion_fail) {
	FAIL() << "oh, over"; // you can only use FAIL() in functions that return void
}

static int test_exception()
{
	try {
		throw 20;
	}
	catch (int e) {
		std::cout << "An exception occurred. Exception Nr. " << e << '\n';
	}

	return 0;
}

TEST(MoreAssertionsTest, assertion_throw) {
	EXPECT_THROW(test_exception, int);
}

static bool MutuallyPrime(int m, int n)
{
	if (n / m == 1) return true;
	else return false;
}

TEST(MoreAssertionsTest, assertion_predicate) {
	const int a = 3;
	const int b = 4;
	const int c = 10;

	EXPECT_PRED2(MutuallyPrime, a, b);
	EXPECT_PRED2(MutuallyPrime, b, c);
}

::testing::AssertionResult IsEven(int n)
{
	if ((n % 2) == 0)
		return ::testing::AssertionSuccess() << n << " is even";
	else
		return ::testing::AssertionFailure() << n << " is odd";
}

TEST(MoreAssertionsTest, assertion_result) {
	EXPECT_TRUE(IsEven(2));
	EXPECT_TRUE(IsEven(3));
	EXPECT_FALSE(IsEven(2));
}

///////////////////////////////////////////////////////////
// Floating-Point Comparison
TEST(FloatPointTest, float_double_eq) {
	float expected1{ 1.111111f }, actual1{ 1.11111111111f };
	EXPECT_FLOAT_EQ(expected1, actual1);

	double expected2{ 1.11111111f }, actual2{ 1.11111111111f };
	EXPECT_DOUBLE_EQ(expected2, actual2);
}

TEST(FloatPointTest, float_double_near) {
	float expected1{ 1.11f }, actual1{ 1.11111111111f };
	EXPECT_NEAR(expected1, actual1, 0.01f);
}

TEST(FloatPointTest, float_double_format2) {
	float expected1{ 1.111111f }, actual1{ 1.12f };
	ASSERT_PRED_FORMAT2(::testing::FloatLE, expected1, actual1);
}

////////////////////////////////////////////////
// Type Assertions
template <typename T>
class Foo {
public:
	void Bar() { ::testing::StaticAssertTypeEq<int, T>(); }
};

TEST(TypeAssertionsTest, int_test) {
	//Foo<bool> fooType1;
	//fooType1.Bar();

	Foo<int> fooType2;
	fooType2.Bar();
}

///////////////////////////////////////////////////////
// Death Tests
static void square_root()
{
	std::cerr << "Failed Foo";
	exit(0);
}

TEST(TestDeathTest, square_root_negative) {
	EXPECT_DEATH(square_root(), "");
	//EXPECT_DEATH(square_root(-22.0), " ");
}
