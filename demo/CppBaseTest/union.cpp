#include "union.hpp"
#include <stdint.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

// Blog: http://blog.csdn.net/fengbingchun/article/details/51884282

///////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/union
union S
{
	int32_t n;     // occupies 4 bytes
	uint16_t s[2]; // occupies 4 bytes
	uint8_t c;     // occupies 1 byte
};

int test_union1()
{
	// The union is only as big as necessary to hold its largest data member.
	// The other data members are allocated in the same bytes as part of that largest member.
	S s = { 0x12345678 }; // initializes the first member, s.n is now the active member
	// at this point, reading from s.s or s.c is undefined behavior
	std::cout << std::hex << "s.n = " << s.n << '\n'; // s.n = 12345678
	s.s[0] = 0x0011; // s.s is now the active member
	// at this point, reading from n or c is UB but most compilers define it
	std::cout << "s.c is now " << +s.c << '\n' // 11 or 00, depending on platform // s.c is now 11
		<< "s.n is now " << s.n << '\n'; // 12340011 or 00115678 // s.n is now 12340011

	return 0;
}

/////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/union
// S_1 has one non-static data member (tag), three enumerator members (CHAR, INT, DOUBLE), 
// and three variant members (c, i, d)
struct S_1
{
	enum{ CHAR, INT, DOUBLE } tag;
	union
	{
		char c;
		int i;
		double d;
	};
};

void print_s(const S_1& s)
{
	switch (s.tag)
	{
		case S_1::CHAR: std::cout << s.c << '\n'; break;
		case S_1::INT: std::cout << s.i << '\n'; break;
		case S_1::DOUBLE: std::cout << s.d << '\n'; break;
	}
}

int test_union2()
{
	S_1 s = { S_1::CHAR, 'a' };
	print_s(s); // a
	s.tag = S_1::INT;
	s.i = 123;
	print_s(s); // 123

	return 0;
}

///////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/5dxy4b7b.aspx
union NumericType
{
	short       iValue;
	long        lValue;
	double      dValue;
};

int test_union3()
{
	union NumericType Values = { 10 };
	std::cout << Values.iValue << std::endl;// 10
	Values.dValue = 3.1416;
	std::cout << Values.dValue << std::endl; // 3.1416

	return 0;
}

