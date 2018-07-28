#include "typedef.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <ios>
#include <type_traits>
#include <typeinfo>

// Blog: https://blog.csdn.net/fengbingchun/article/details/81259210

namespace typedef_ {

///////////////////////////////////////////////
// reference: https://en.cppreference.com/w/cpp/language/typedef
 
// std::add_const, like many other metafunctions, use member typedefs
template< class T>
struct add_const {
	typedef const T type;
};

int test_typedef_1()
{
	// simple typedef
	typedef unsigned long ulong;
 
	// the following two objects have the same type
	unsigned long l1;
	ulong l2;

	// more complicated typedef
	typedef int int_t, *intp_t, (&fp)(int, ulong), arr_t[10];

	// the following two objects have the same type
	int a1[10];
	arr_t a2;
	for (int i = 0; i < 10; ++i)
		a2[i] = i;
	for (int i = 0; i < 10; ++i)
		fprintf(stdout, "a2 value: %d\n", a2[i]);
 
	// common C idiom to avoid having to write "struct S"
	typedef struct {int a; int b;} S, *pS;
 
	// the following two objects have the same type
	pS ps1;
	S* ps2;
 
	// error: storage-class-specifier cannot appear in a typedef declaration
	// typedef static unsigned int uint;
 
	// typedef can be used anywhere in the decl-specifier-seq
	long unsigned typedef int long ullong;
	// more conventionally spelled "typedef unsigned long long int ullong;"

	// std::add_const, like many other metafunctions, use member typedefs
	/*template< class T>
	struct add_const { // error: a template declaration cannot appear at block scope
		typedef const T type;
	};*/
 
	typedef struct Node {
    		//struct listNode* next; // declares a new (incomplete) struct type named listNode
	} listNode; // error: conflicts with the previously declared struct name

	struct Node2 {
		int data;
		struct Node2* nextptr;
	};

	// 使用typedef可以将上面的Node2改写为：
	typedef struct Node3 Node3;
	struct Node3 {
		int data;
		Node3* nextptr;
	};

	typedef double wages; // wages是double的同义词
	typedef wages base, *p; // base是double的同义词，p是double*的同义词
	
	return 0;
}

////////////////////////////////////////////
// reference: http://www.cplusplus.com/doc/tutorial/other_data_types/
int test_typedef_2()
{
	// In C++, there are two syntaxes for creating such type aliases:
	// The first, inherited from the C language, uses the typedef keyword:
	// typedef existing_type new_type_name;
{	
	typedef char C;
	typedef unsigned int WORD;
	typedef char * pChar;
	typedef char field [50];
	
	C mychar, anotherchar, *ptc1;
	WORD myword;
	pChar ptc2;
	field name;
}

	// a second syntax to define type aliases was introduced in the C++ language:
	// using new_type_name = existing_type;
{
	//the same type aliases as above could be defined as:
	using C = char;
	using WORD = unsigned int;
	using pChar = char *;
	using field = char [50];	
}

{
	// 注意： typedef int* INT; const INT p;相当于int* const p；而不是const int* p;
	typedef int* INT;
	int a[] = {1, 2, 3};
	const INT p1 = &a[0];
	const int* p2 = &a[0];
	//++p1; // error: increment of read-only variable 'p1'
	p1[0] = -100;
	fprintf(stdout, "a[0]: %d\n", a[0]);
	++p2;
	//p2[0] = -200; // error: assignment of read-only location '*p2' 
}

	return 0;
}

////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/dn467695.aspx
void actual_function(int arg) { fprintf(stdout, "value: %d\n", arg); }  
template<typename T>
using ptr2 = T*;

template<typename T>
struct MyAlloc {
	typedef T value_type;

	MyAlloc() { }
	template<typename U>
	MyAlloc(const MyAlloc<U>&) { }

	bool operator == (const MyAlloc&) const { return true; }
	bool operator != (const MyAlloc&) const { return false; }

	T* allocate(const size_t n) const {
		fprintf(stdout, "start allocate\n");
		if (n == 0) {
			return nullptr;
		 }

		if (n > static_cast<size_t>(-1) / sizeof(T)) {
			throw std::bad_array_new_length();
		 }

		void* const pv = malloc(n * sizeof(T));

		if (!pv) {
			 throw std::bad_alloc();
		 }

		return static_cast<T*>(pv);  
	}
  
	void deallocate(T* const p, size_t) const {
		fprintf(stdout, "start deallocate\n");
		free(p);
	}
};

using MyIntVector = std::vector<int, MyAlloc<int>>;

int test_typedef_3()
{

{ // An alias does not introduce a new type and cannot change the meaning of an existing type name
	// C++11  
	using counter = long;  
  
	// C++03 equivalent:  
	// typedef long counter; 
}

{ // Aliases also work with function pointers
	// C++11  
	using func = void(*)(int);  
  
	// C++03 equivalent:  
	// typedef void (*func)(int);  
  
	// func can be assigned to a function pointer value  
	func fptr = &actual_function;
	fptr(10);
}

{ // A limitation of the typedef mechanism is that it doesn't work with templates. However, the type alias syntax in C++11 enables the creation of alias templates:
	//template<typename T> using ptr = T*; // error: a template declaration cannot appear at block scope   
  
	// the name 'ptr<T>' is now an alias for pointer to T  
	ptr2<int> ptr_int;
}

{ // an alias template with a custom allocator
	MyIntVector foov = { 1701, 1764, 1664 };
	for (auto a: foov)
		fprintf(stdout, " %d ", a);
	fprintf(stdout, "\n");
}

	return 0;
}

///////////////////////////////////////////////////////
// reference: https://zh.wikipedia.org/zh-hk/Typedef
int do_math(float arg1, int arg2) { return arg2;  }

int call_a_func(int (*call_this)(float, int))
{
	int output = call_this(5.5, 7);
	return output;
}

// 将上面改为使用typedef,回调函数
typedef int (*MathFunc)(float, int);
int call_a_func2(MathFunc call_this)
{
	int output = call_this(5.5, 7);
	return output;
}

int test_typedef_4()
{
	int final_result = call_a_func(&do_math);
	fprintf(stdout, "final_result: %d\n", final_result);

	int final_result2 = call_a_func2(&do_math);
	fprintf(stdout, "final_result2: %d\n", final_result2);

	return 0;
}

////////////////////////////////////////////
// reference: https://en.cppreference.com/w/cpp/language/type_alias
// type alias, identical to
// typedef std::ios_base::fmtflags flags;
using flags = std::ios_base::fmtflags;
// the name 'flags' now denotes a type:
flags fl = std::ios_base::dec;
 
// type alias, identical to
// typedef void (*func)(int, int);
using func = void (*) (int, int);
// the name 'func' now denotes a pointer to function:
void example(int, int) {}
func f = example;
 
// alias template
template<class T>
using ptr = T*; 
// the name 'ptr<T>' is now an alias for pointer to T
ptr<int> x;
 
// type alias used to hide a template parameter 
template<class CharT>
using mystring = std::basic_string<CharT, std::char_traits<CharT>>;
mystring<char> str;
 
// type alias can introduce a member typedef name
template<typename T>
struct Container { using value_type = T; };
// which can be used in generic programming
template<typename Container>
void g(const Container& c)
{
	typename Container::value_type n;
	fprintf(stdout, "type: %s\n", typeid(n).name());
}
 
// type alias used to simplify the syntax of std::enable_if
template<typename T>
using Invoke = typename T::type;
template<typename Condition>
using EnableIf = Invoke<std::enable_if<Condition::value>>;
template<typename T, typename = EnableIf<std::is_polymorphic<T>>>
int fpoly_only(T t) { return 1; }
 
struct S { virtual ~S() {} };

int test_typedef_5()
{
	Container<int> c;
	g(c); // Container::value_type will be int in this function
	//fpoly_only(c); // error: enable_if prohibits this
	S s;
	fpoly_only(s); // okay: enable_if allows this

	return 0;
}

} // namespace typedef_

