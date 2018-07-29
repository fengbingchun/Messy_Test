#include "memory_alignment.hpp"
#include <iostream>
#include <cstdlib>
#include <stdint.h>


// Blog: https://blog.csdn.net/fengbingchun/article/details/81270326

//#pragma pack(1) // use #pragma pack set memory alignment

namespace memory_alignment_ {

//////////////////////////////////////////////////////
int test_memory_alignment_1()
{

{ // struct	
	typedef struct A {char c;} A;
	typedef struct B {int i;} B;
	typedef struct C {double d;} C;
	typedef struct D {char c; int i;} D;
	typedef struct E {char* p;} E; // 32bits is 4, 64bits is 8
	typedef struct F {char* p; int* p2;} F;
	typedef struct G {char c1; char c2; char c3;} G;
	typedef struct H {char c; int* p;} H;
	typedef struct I {char c; int* p; int i;} I;
	typedef struct J {char c; int i; int* p;} J;
	typedef struct K {} K; // C++ size is 1, but C is 0
	fprintf(stdout, "size: A: %d, B: %d, C: %d, D: %d, E: %d, F: %d, G: %d, H: %d, I: %d, J: %d, K: %d\n",
		sizeof(A), sizeof(B), sizeof(C), sizeof(D), sizeof(E), sizeof(F), sizeof(G), sizeof(H), sizeof(I), sizeof(J), sizeof(K));

	fprintf(stdout, "size: short: %d, long: %d, float: %d, long long: %d, double: %d, uint64_t: %d\n",
		sizeof(short), sizeof(long), sizeof(float), sizeof(long long), sizeof(double), sizeof(uint64_t));
}

	return 0;
}

//////////////////////////////////////////////////////////
// reference: https://stackoverflow.com/questions/17091382/memory-alignment-how-to-use-alignof-alignas
int test_memory_alignment_2()
{

#ifdef __linux__
{
	// alignas: 类型或对象或变量按指定的字节对齐
	// Alignment of 16 means that memory addresses that are a multiple of 16 are the only valid addresses.
	alignas(16) int a[4];
	alignas(1024) int b[4];
	fprintf(stdout, "address: %p\n", a);
	fprintf(stdout, "address: %p\n", b);

	// alignof: 查询指定类型的对齐要求，返回size_t类型值
	if (alignof(a) != 16 || (unsigned long long)a % 16 != 0) {
		fprintf(stderr, "a must be 16 byte aligned.\n");
		return -1;
	}

	if (alignof(b) != 1024 || (unsigned long long)b % 1024 != 0) {
		fprintf(stderr, "b must be 1024 byte aligned.\n");
		return -1;
	}
}

{
	// every object of type sse_t will be aligned to 16-byte boundary
	struct alignas(16) sse_t { float sse_data[4]; };
 	// the array "cacheline" will be aligned to 128-byte boundary
	alignas(128) char cacheline[128];
}
#endif

	return 0;
}

//////////////////////////////////////////////////////////////
// reference: https://en.cppreference.com/w/cpp/language/alignof
int test_memory_alignment_3()
{
#ifdef __linux__
	struct Foo {
		int   i;
		float f;
		char  c;
	};

	struct Empty {};

	struct alignas(64) Empty64{};

	std::cout << "Alignment of"  "\n"
		"- char             : " << alignof(char)    << "\n"
		"- pointer          : " << alignof(int*)    << "\n"
		"- class Foo        : " << alignof(Foo)     << "\n"
		"- empty class      : " << alignof(Empty)   << "\n"
		"- alignas(64) Empty: " << alignof(Empty64) << "\n";
#endif

	return 0;
}

//////////////////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/dn956973.aspx
int test_memory_alignment_4()
{
	struct x_ {
		char a;     // 1 byte  
		int b;      // 4 bytes  
		short c;    // 2 bytes  
		char d;     // 1 byte  
	} MyStruct;

	// The compiler pads this structure to enforce alignment naturally.
	// The following code example shows how the compiler places the padded structure in memory:Copy
	// Shows the actual memory layout  
	/*struct x_ {
		char a;            // 1 byte  
		char _pad0[3];     // padding to put 'b' on 4-byte boundary  
		int b;            // 4 bytes  
		short c;          // 2 bytes  
		char d;           // 1 byte  
		char _pad1[1];    // padding to make sizeof(x_) multiple of 4  
	} MyStruct; */

	// 1. Both declarations return sizeof(struct x_) as 12 bytes.
	// 2. The second declaration includes two padding elements:
	// 3. char _pad0[3] to align the int b member on a four-byte boundary
	// 4. char _pad1[1] to align the array elements of the structure struct _x bar[3];
	// 5. The padding aligns the elements of bar[3] in a way that allows natural access.

	return 0;
}

} // namespace memory_alignment_

