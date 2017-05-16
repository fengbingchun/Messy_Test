#include "funset.hpp"

// reference: googletest/samples

///////////////////////////////////////////////////////////////////
// Returns n! (the factorial of n).  For negative n, n! is defined to be 1.
int Factorial(int n) {
	int result = 1;
	for (int i = 1; i <= n; i++) {
		result *= i;
	}

	return result;
}

// Returns true iff n is a prime number.
bool IsPrime(int n) {
	// Trivial case 1: small numbers
	if (n <= 1) return false;

	// Trivial case 2: even numbers
	if (n % 2 == 0) return n == 2;

	// Now, we have that n is odd and n >= 3.

	// Try to divide n by every odd number i, starting from 3
	for (int i = 3;; i += 2) {
		// We only have to try i up to the squre root of n
		if (i > n / i) break;

		// Now, we have i <= n/i < n.
		// If n is divisible by i, n is not prime.
		if (n % i == 0) return false;
	}

	// n has no integer factor in the range (1, n), and thus is prime.
	return true;
}

///////////////////////////////////////////////////////////////////
// Clones a 0-terminated C string, allocating memory using new.
const char* MyString::CloneCString(const char* a_c_string) {
	if (a_c_string == NULL) return NULL;

	const size_t len = strlen(a_c_string);
	char* const clone = new char[len + 1];
	memcpy(clone, a_c_string, len + 1);

	return clone;
}

// Sets the 0-terminated C string this MyString object
// represents.
void MyString::Set(const char* a_c_string) {
	// Makes sure this works when c_string == c_string_
	const char* const temp = MyString::CloneCString(a_c_string);
	delete[] c_string_;
	c_string_ = temp;
}
