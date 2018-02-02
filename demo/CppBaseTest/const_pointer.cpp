#include <iostream>
#include "const_pointer.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/74656836

int test_const_pointer_1()
{
{ // reference: https://stackoverflow.com/questions/3247285/const-int-int-const
	int a			= 5;
	int *p1			= &a; //non-const pointer, non-const data
	const int *p2		= &a; //non-const pointer, const data, value pointed to by p2 can’t change
	int * const p3		= &a; //const pointer, non-const data, p3 cannot point to a different location
	const int * const p4	= &a; //const pointer, const data, both the pointer and the value pointed to cannot change
	int const * const p5 = &a; // 与 const int * const p5等价
}

{ // reference: https://stackoverflow.com/questions/162480/const-int-vs-int-const-as-function-parameter-in-c-and-c
	// read the declaration backwards (right-to-left):
	const int a1 = 1; // read as "a1 is an integer which is constant"
	int const a2 = 1; // read as "a2 is a constant integer"
	// a1 = 2; // Can't do because a1 is constant
	// a2 = 2; // Can't do because a2 is constant

	char a = 'a';
	const char *s = &a; // read as "s is a pointer to a char that is constant"
	char const *y = &a; // 与 const char *y 等价
	char c;
	char *const t = &c; // read as "t is a constant pointer to a char"

	// *s = 'A'; // Can't do because the char is constant
	s++;         // Can do because the pointer isn't constant
	*t = 'A';    // Can do because the char isn't constant
	// t++;      // Can't do because the pointer is constant
	// *y = 'A';
	y++;
}

{ // reference: http://www.geeksforgeeks.org/const-qualifier-in-c/
	int i = 10;
	int j = 20;
	int *ptr = &i;        /* pointer to integer */
	printf("*ptr: %d\n", *ptr);

	/* pointer is pointing to another variable */
	ptr = &j;
	printf("*ptr: %d\n", *ptr);

	/* we can change value stored by pointer */
	*ptr = 100;
	printf("*ptr: %d\n", *ptr);
}

{ // const int *ptr <==> int const *ptr
	int i = 10;
	int j = 20;
	const int *ptr = &i;    /* ptr is pointer to constant */

	printf("ptr: %d\n", *ptr);
	// *ptr = 100;        /* error: object pointed cannot be modified using the pointer ptr */

	ptr = &j;          /* valid */
	printf("ptr: %d\n", *ptr);
}

{ // int * const ptr
	int i = 10;
	int j = 20;
	int *const ptr = &i;    /* constant pointer to integer */

	printf("ptr: %d\n", *ptr);

	*ptr = 100;    /* valid */
	printf("ptr: %d\n", *ptr);

	// ptr = &j;        /* error */
}

{ // const int *const ptr;
	int i = 10;
	int j = 20;
	const int *const ptr = &i;        /* constant pointer to constant integer */

	printf("ptr: %d\n", *ptr);

	// ptr = &j;            /* error */
	// *ptr = 100;        /* error */
}

{ // reference: http://www.learncpp.com/cpp-tutorial/610-pointers-and-const/
	int value = 5;
	int *ptr = &value;
	*ptr = 6; // change value to 6

	const int value2 = 5; // value is const
	// int *ptr2 = &value2; // compile error: cannot convert const int* to int*

	const int *ptr3 = &value2; // this is okay, ptr3 is pointing to a "const int"
	// *ptr3 = 6; // not allowed, we can't change a const value

	const int *ptr4 = &value; // ptr4 points to a "const int"
	fprintf(stderr, "*ptr4: %d\n", *ptr4);
	value = 7; // the value is non-const when accessed through a non-const identifier
	fprintf(stderr, "*ptr4: %d\n", *ptr4);
}

	return 0;
}

//////////////////////////////////////////////////////////
// reference: https://en.wikipedia.org/wiki/Const_(computer_programming)
class C {
	int i;
public:
	int Get() const { // Note the "const" tag
		return i;
	}
	void Set(int j) { // Note the lack of "const"
		i = j;
	}
};

static void Foo_1(C& nonConstC, const C& constC)
{
	int y = nonConstC.Get(); // Ok
	int x = constC.Get();    // Ok: Get() is const

	nonConstC.Set(10); // Ok: nonConstC is modifiable
	// constC.Set(10);    // Error! Set() is a non-const method and constC is a const-qualified object
}

class MyArray {
	int data[100];
public:
	int &       Get(int i)       { return data[i]; }
	int const & Get(int i) const { return data[i]; }
};

static void Foo_2(MyArray & array, MyArray const & constArray) {
	// Get a reference to an array element
	// and modify its referenced value.

	array.Get(5) = 42; // OK! (Calls: int & MyArray::Get(int))
	// constArray.Get(5) = 42; // Error! (Calls: int const & MyArray::Get(int) const)
}

typedef struct S_ {
	int val;
	int *ptr;
} S;

void Foo_3(const S & s)
{
	int i = 42;
	// s.val = i;   // Error: s is const, so val is a const int
	// s.ptr = &i;  // Error: s is const, so ptr is a const pointer to int
	// *s.ptr = i;  // OK: the data pointed to by ptr is always mutable,
		     // even though this is sometimes not desirable
}

int test_const_pointer_2()
{
	C a, b;
	Foo_1(a, b);

	MyArray x, y;
	Foo_2(x, y);

	S s;
	Foo_3(s);

	return 0;
}
