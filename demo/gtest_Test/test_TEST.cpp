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

