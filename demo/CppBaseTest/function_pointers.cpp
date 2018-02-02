#include <stdio.h> // for printf
#include <string.h> // for strchr
#include <math.h>
#include <functional>
#include <algorithm> // for std::swap, use <utility> instead if C++11
#include <iostream>
#include "function_pointers.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/51713906

// reference: http://www.newty.de/fpt/intro.html

// reference: http://www.cprogramming.com/tutorial/function-pointers.html
void my_int_func(int x)
{
	printf("%d\n", x);
}

int test_function_pointers1()
{
	void (*foo)(int);
	// Initializing Function Pointers:
	// To initialize a function pointer, you must give it the address of a function in your program.
	// the ampersand is actually optional
	foo = &my_int_func;

	// call my_int_func (note that you do not need to write (*foo)(2) )
	foo(2); // 2
	// but if you want to, you may 
	(*foo)(2); // 2

	return 0;
}

int int_sorter(const void *first_arg, const void *second_arg)
{
	int first = *(int*)first_arg;
	int second = *(int*)second_arg;
	if (first < second) {
		return -1;
	} else if (first == second) {
		return 0;
	} else {
		return 1;
	}
}

int test_function_pointers2()
{
	int array[10];
	for (int i = 0; i < 10; ++i) {
		array[i] = 10 - i;
	}

	// void qsort(void *base, size_t nmemb, size_t size, int(*compar)(const void *, const void *));
	qsort(array, 10, sizeof(int), int_sorter);

	for (int i = 0; i < 10; ++i) {
		printf("%d\n", array[i]); // 1 2 3 4 5 6 7 8 9 10
	}

	return 0;
}

// Note our user-defined comparison is the third parameter
void selectionSort(int *array, int size, bool(*comparisonFcn)(int, int))
{
	// Step through each element of the array
	for (int startIndex = 0; startIndex < size; ++startIndex) {
		// smallestIndex is the index of the smallest element we've encountered so far.
		int smallestIndex = startIndex;

		// Look for smallest element remaining in the array (starting at startIndex+1)
		for (int currentIndex = startIndex + 1; currentIndex < size; ++currentIndex) {
			// If the current element is smaller than our previously found smallest
			if (comparisonFcn(array[smallestIndex], array[currentIndex])) // COMPARISON DONE HERE
				// This is the new smallest number for this iteration
				smallestIndex = currentIndex;
		}

		// Swap our start element with our smallest element
		std::swap(array[startIndex], array[smallestIndex]);
	}
}

// Here is a comparison function that sorts in ascending order
// (Note: it's exactly the same as the previous ascending() function)
bool ascending(int x, int y)
{
	return x > y; // swap if the first element is greater than the second
}

// Here is a comparison function that sorts in descending order
bool descending(int x, int y)
{
	return x < y; // swap if the second element is greater than the first
}

// This function prints out the values in the array
void printArray(int *array, int size)
{
	for (int index = 0; index < size; ++index)
		std::cout << array[index] << " ";
	std::cout << '\n';
}

// reference: http://www.learncpp.com/cpp-tutorial/78-function-pointers/
int test_function_pointers3()
{
	int array[9] = { 3, 7, 9, 5, 6, 1, 8, 2, 4 };

	// Sort the array in descending order using the descending() function
	selectionSort(array, 9, descending);
	printArray(array, 9); // 9 8 7 6 5 4 3 2 1

	// Sort the array in ascending order using the ascending() function
	selectionSort(array, 9, ascending);
	printArray(array, 9); // 1 2 3 4 5 6 7 8 9

	return 0;
}

bool evensFirst(int x, int y)
{
	// if x is even and y is odd, x goes first (no swap needed)
	if ((x % 2 == 0) && !(y % 2 == 0))
		return false;

	// if x is odd and y is even, y goes first (swap needed)
	if (!(x % 2 == 0) && (y % 2 == 0))
		return true;

	// otherwise sort in ascending order
	return ascending(x, y);
}

int test_function_pointers4()
{
	int array[9] = { 3, 7, 9, 5, 6, 1, 8, 2, 4 };

	selectionSort(array, 9, evensFirst);
	printArray(array, 9); // 2 4 6 8 1 3 5 7 9

	return 0;
}

int getInteger()
{
	std::cout << "Enter an integer: ";
	int x;
	std::cin >> x;
	return x;
}

char getOperation()
{
	char op;

	do {
		std::cout << "Enter an operation ('+', '-', '*', '/'): ";
		std::cin >> op;
	} while (op != '+' && op != '-' && op != '*' && op != '/');

	return op;
}

int add(int x, int y)
{
	return x + y;
}

int subtract(int x, int y)
{
	return x - y;
}

int multiply(int x, int y)
{
	return x * y;
}

int divide(int x, int y)
{
	return x / y;
}

typedef int(*arithmeticFcn)(int, int);

arithmeticFcn getArithmeticFcn(char op)
{
	switch (op) {
		default: // default will be to add
		case '+': return add;
		case '-': return subtract;
		case '*': return multiply;
		case '/': return divide;
	}
}

int test_function_pointers5()
{
	int x = getInteger(); // 5
	char op = getOperation(); // *
	int y = getInteger(); // 6

	arithmeticFcn fcn = getArithmeticFcn(op);
	std::cout << x << ' ' << op << ' ' << y << " = " << fcn(x, y) << '\n'; // 5 * 6 = 30

	return 0;
}

struct arithmeticStruct
{
	char op;
	arithmeticFcn fcn;
};

static arithmeticStruct arithmeticArray[] {
	{ '+', add },
	{ '-', subtract },
	{ '*', multiply },
	{ '/', divide }
};

arithmeticFcn getArithmeticFcn_(char op)
{
	for (auto &arith : arithmeticArray) {
		if (arith.op == op)
			return arith.fcn;
	}

	return add; // default will be to add
}

int test_function_pointers6()
{
	int x = getInteger();
	char op = getOperation();
	int y = getInteger();

	arithmeticFcn fcn = getArithmeticFcn_(op);
	std::cout << x << ' ' << op << ' ' << y << " = " << fcn(x, y) << '\n'; // 5 * 6 = 30

	return 0;
}

double cm_to_inches(double cm)
{
	return cm / 2.54;
}

// reference: https://en.wikipedia.org/wiki/Function_pointer
int test_function_pointers7()
{
	double(*func1)(double) = cm_to_inches;
	printf("%f\n", func1(15.0)); // 5.905512

	return 0;
}

// Function taking a function pointer as an argument
double compute_sum(double(*funcp)(double), double lo, double hi)
{
	double  sum = 0.0;

	// Add values returned by the pointed-to function '*funcp'
	for (int i = 0; i <= 100; i++) {
		double  x, y;

		// Use the function pointer 'funcp' to invoke the function
		x = i / 100.0 * (hi - lo) + lo;
		y = (*funcp)(x);
		sum += y;
	}

	return sum / 101.0;
}

int test_function_pointers8()
{
	double(*fp)(double); // Function pointer
	double  sum;

	// Use 'sin()' as the pointed-to function
	fp = sin;
	sum = compute_sum(fp, 0.0, 1.0);
	printf("sum(sin): %f\n", sum); // sum(sin): 0.459308

	// Use 'cos()' as the pointed-to function
	fp = cos;
	sum = compute_sum(fp, 0.0, 1.0);
	printf("sum(cos): %f\n", sum); // sum(cos): 0.840758

	return 0;
}

int add_(int first, int second)
{
	return first + second;
}

int subtract_(int first, int second)
{
	return first - second;
}

int operation(int first, int second, int(*functocall)(int, int))
{
	return (*functocall)(first, second);
}

int test_function_pointers9()
{
	int  a, b;
	int(*plus)(int, int) = add_;
	int(*minus)(int, int) = subtract_;

	a = operation(7, 5, plus);
	b = operation(20, a, minus);
	std::cout << "a = " << a << " and b = " << b << std::endl; // a = 12 and b = 8

	return 0;
}

static double derivative(const std::function<double(double)> &f, double x0, double eps)
{
	double eps2 = eps / 2;
	double lo = x0 - eps2;
	double hi = x0 + eps2;
	return (f(hi) - f(lo)) / eps;
}

static double f(double x)
{
	return x * x;
}

int test_function_pointers10()
{
	double x = 1;
	std::cout << "d/dx(x ^ 2) [@ x = " << x << "] = " << derivative(f, x, 1e-5) << std::endl; // d/dx(x ^ 2) [@ x = 1] = 2

	return 0;
}

class Foo {

public:
	int add(int i, int j)
	{
		return i + j;
	}
	int mult(int i, int j)
	{
		return i*j;
	}
	static int negate(int i)
	{
		return -i;
	}
};

int bar1(int i, int j, Foo* pFoo, int(Foo::*pfn)(int, int))
{
	return (pFoo->*pfn)(i, j);
}

typedef int(Foo::*Foo_pfn)(int, int);

int bar2(int i, int j, Foo* pFoo, Foo_pfn pfn)
{
	return (pFoo->*pfn)(i, j);
}

typedef int(*PFN)(int);

int bar3(int i, PFN pfn)
{
	return pfn(i);
}

int test_function_pointers11()
{
	Foo foo;
	std::cout << "Foo::add(2,4) = " << bar1(2, 4, &foo, &Foo::add) << std::endl; // Foo::add(2,3) = 6
	std::cout << "Foo::mult(3,5) = " << bar2(3, 5, &foo, &Foo::mult) << std::endl; // Foo::mult(3,5) = 15
	std::cout << "Foo::negate(6) = " << bar3(6, &Foo::negate) << std::endl; // Foo::negate(6) = -6

	return 0;
}

void one(int a, int b) { std::cout << a + b << "\n"; }
void two(int a, int b) { std::cout << a*b << "\n"; }

// reference: http://www.dev-hq.net/c++/20--function-pointers
int test_function_pointers12()
{
	//void(*fptr)(int, int); // Declare a function pointer to voids with two int params

	//fptr = one; // fptr -> one
	//fptr(12, 3); // => one(12, 3)

	//fptr = two; // fptr -> two
	//fptr(5, 4); // => two(5, 3)

	void(*fptr[2])(int, int);
	fptr[0] = one;
	fptr[1] = two;

	fptr[0](12, 3); // one(12, 3)  // 15
	fptr[1](5, 4); // two(5, 3)  // 20

	return 0;
}

class Number
{
public:
	int i;
	Number() { i = 0; }
	int one() { return i + 1; }
	int two() { return i + 2; }
};

int test_function_pointers13()
{
	Number object; // Create a new 'Number' object named 'object'
	// Declare a pointer array with two elements which are pointers to member functions in "Number" of type 'int' with takes no params
	int (Number::*NumberPtr[2])();

	NumberPtr[0] = &Number::one;
	NumberPtr[1] = &Number::two;

	std::cout << (object.*NumberPtr[0])() << std::endl; // 1
	std::cout << (object.*NumberPtr[1])() << std::endl; // 2

	return 0;
}

class Employee
{
public:
	Employee()
	{
		wageCalc = &Employee::CalculateWage; // wageCalc -> CalculateWage
	}
	void UpgradeToExperienced()
	{
		wageCalc = &Employee::CalculateExperiencedWage; // wageCalc -> CalculateExperiencedWage
	}
	double Pay(double hours)
	{
		return (this->*wageCalc)(hours); // => object.*wageCalc(hours)
	}

private:
	double (Employee::*wageCalc)(double hours); // The member function ptr
	double CalculateWage(double hours)
	{
		return 10 * hours;
	}
	double CalculateExperiencedWage(double hours)
	{
		return 20 * hours;
	}
};

int test_function_pointers14()
{
	Employee one;
	std::cout << one.Pay(10) << std::endl; // 100
	one.UpgradeToExperienced();
	std::cout << one.Pay(10) << std::endl; // 200

	return 0;
}

void add_1(int a, int b)
{
	printf("Addition is %d\n", a + b);
}
void subtract_1(int a, int b)
{
	printf("Subtraction is %d\n", a - b);
}
void multiply_1(int a, int b)
{
	printf("Multiplication is %d\n", a*b);
}

// reference: http://www.geeksforgeeks.org/function-pointer-in-c/
int test_function_pointers15()
{
	// fun_ptr_arr is an array of function pointers
	void(*fun_ptr_arr[])(int, int) = { add_1, subtract_1, multiply_1 };
	unsigned int ch, a = 15, b = 10;

	printf("Enter Choice: 0 for add, 1 for subtract and 2 for multiply\n");
	scanf("%d", &ch); // 1

	if (ch > 2) return 0;

	(*fun_ptr_arr[ch])(a, b); // Subtraction is 5

	return 0;
}

class Foo_{
public:
	int f(std::string str){
		std::cout << "Foo_::f()" << std::endl;
		return 1;
	}
};

// reference: http://www.codeguru.com/cpp/cpp/article.php/c17401/C-Tutorial-PointertoMember-Function.htm
int test_function_pointers16()
{
	int (Foo_::*fptr) (std::string) = &Foo_::f;
	Foo_ obj;
	(obj.*fptr)("str");//call: Foo::f() through an object // Foo_::f()
	Foo_* p = &obj;
	(p->*fptr)("str");//call: Foo::f() through a pointer // Foo_::f()

	return 0;
}

class Foo_1{
public:
	// A "static" member function has no "this" pointer
	static int f(std::string str){
		std::cout << "Foo::f()" << std::endl;
		return 1;
	}
};

int test_function_pointers17()
{
	//int (Foo_1::*fptr) (string) = &Foo_1::f; // error 
	int(*fptr) (std::string) = &Foo_1::f; // correct
	(*fptr)("str"); // call Foo_1::f() // Foo::f()

	return 0;
}

class Foo_2{
public:
	int f(char* c = 0){
		std::cout << "Foo_2::f()" << std::endl;
		return 1;
	}
};

class Bar{
public:
	void b(int i = 0){
		std::cout << "Bar::b()" << std::endl;
	}
};

class FooDerived :public Foo_2{
public:
	int f(char* c = 0){
		std::cout << "FooDerived::f()" << std::endl;
		return 1;
	}
};

int test_function_pointers18()
{
	typedef  int (Foo_2::*FPTR) (char*);
	typedef  void (Bar::*BPTR) (int);
	typedef  int (FooDerived::*FDPTR) (char*);

	FPTR fptr = &Foo_2::f;
	BPTR bptr = &Bar::b;
	FDPTR fdptr = &FooDerived::f;

	// Bptr = static_cast<void (Bar::*) (int)> (fptr); // error
	fdptr = static_cast<int (Foo_2::*) (char*)> (fptr); // OK: contravariance

	Bar obj;
	(obj.*(BPTR)fptr)(1); // call: Foo_2::f()  // Foo_2::f()

	return 0;
}

class Foo_3{
public:
	virtual int f(char* c = 0){
		std::cout << "Foo_3::f()" << std::endl;
		return 1;
	}
};

class Bar_3{
public:
	virtual void b(int i = 0){
		std::cout << "Bar_3::b()" << std::endl;
	}
};

class FooDerived_3 :public Foo_3{
public:
	int f(char* c = 0){
		std::cout << "FooDerived_3::f()" << std::endl;
		return 1;
	}
};

int test_function_pointers19()
{
	typedef  int (Foo_3::*FPTR) (char*);
	typedef  void (Bar_3::*BPTR) (int);
	FPTR fptr = &Foo_3::f;
	BPTR bptr = &Bar_3::b;

	FooDerived_3 objDer;
	(objDer.*fptr)(0); // call: FooDerived::f(), not Foo::f() // FooDerived::f()

	Bar_3 obj;
	(obj.*(BPTR)fptr)(1); // call: Bar::b() , not Foo::f() // Bar_3::b()

	return 0;
}

class Printer{ // An abstract printing machine
public:
	void Copy(char * buff, const char * source){ // copy the file
		strcpy(buff, source);
	}
	void Append(char * buff, const char * source){ // extend the file
		strcat(buff, source);
	}
};

enum OPTIONS { COPY, APPEND }; // two possible commands in the menu.
typedef void(Printer::*PTR) (char*, const char*); // pointer-to-member function 

void working(OPTIONS option, Printer* machine, char* buff, const char* infostr)
{
	PTR pmf[2] = { &Printer::Copy, &Printer::Append }; // pointer array 

	switch (option){
	case COPY:
		(machine->*pmf[COPY])(buff, infostr);
		break;
	case APPEND:
		(machine->*pmf[APPEND])(buff, infostr);
		break;
	}
}

int test_function_pointers20()
{
	OPTIONS option;
	Printer machine;
	char buff[40]; // target

	working(COPY, &machine, buff, "Strings ");
	working(APPEND, &machine, buff, "are concatenated! ");

	std::cout << buff << std::endl; // Strings are concatenated!

	return 0;
}

// reference: http://www.radmangames.com/programming/how-to-use-function-pointers-in-cplusplus
// 1. Declaring function pointer variables
// (1). Non member functions
// return_type (*varName)() = namespace::function; // no parameters 
// return_type(*varName)(paramType1, paramTypeN) = namespace::function;
// (2). Member functions
// return_type (Class::*varName)(paramType1, paramTypeN) = &Class::method;
// (3). Typedefs for function pointer types
// typedef return_type (*TypeName)(paramType1, paramTypeN);
// typedef return_type(ExampleClass::*TypeName)(paramType1, paramTypeN);
// static_cast<void(Class::*)()>(&Class::method)
// 2. Using function pointer variables
// (1). Calling a non-member function pointer
/*
void (*funcPtr)(paramType1, paramTypeN) = namespace::function;
funcPtr(parameter1, parameterN);
*/
// (2). Calling a member function pointer
/*
void (Class::*memberFuncPtr)() = &Class::method;

Class* ptrInstance = new Class();
(ptrInstance->*memberFuncPtr)();

Class refInstance;
(refInstance.*memberFuncPtr)();
*/

namespace
{
	int simple() { return 0; }
	float test1(int first, float second, char third) { return 0.0; }
	float test2(int first, float second, char third) { return 0.0; }

	template <typename T_Example>
	void templateExample(T_Example param) {}

	class Class
	{
	public: // interface 
		void method(int var) {}
		void overload(int var) {}
		void overload(int first, float second) {}

	}; // class 

	template <typename T_Example>
	class TemplateClass
	{
	public: // interface 
		void templateDo(T_Example templateParam, int extraParam) {}

	}; // class 

} // namespace 

int test_function_pointers21()
{
	// non-member examples 
	int(*simpleNonMember)() = simple;
	simpleNonMember();

	typedef float(*TestTypeFuncPtr)(int, float, char);

	TestTypeFuncPtr test1FuncPtr = test1;
	TestTypeFuncPtr test2FuncPtr = test2;
	test1(7, 12.5, 'c'); // directly 
	test1FuncPtr(7, 12.5, 'c'); // through the function pointer 
	test2FuncPtr(11, 857.2, 'r');

	// non-member template examples 
	void(*templateExampleFuncPtr1)(int) = templateExample<int>;
	void(*templateExampleFuncPtr2)(float) = templateExample<float>;
	templateExampleFuncPtr1(7);
	templateExampleFuncPtr2(7.f);

	// member examples 
	Class* classPtr = new Class();
	Class classRef;
	void (Class::*overload2FuncPtr)(int, float) = &Class::overload;
	(classRef.*overload2FuncPtr)(0, 2.f);

	typedef void (Class::*ClassIntParamTypeFuncPtr)(int);
	ClassIntParamTypeFuncPtr overload1AndMethodFuncPtr = nullptr;
	overload1AndMethodFuncPtr = &Class::method;
	overload1AndMethodFuncPtr = &Class::overload;
	(classPtr->*overload1AndMethodFuncPtr)(7);
	(classRef.*overload1AndMethodFuncPtr)(7);

	// template class member examples 
	TemplateClass<float>* templateClassPtr = new TemplateClass<float>();

	typedef void (TemplateClass<float>::*TemplateDoTypeFloat)(float, int);
	TemplateDoTypeFloat templateDoFuncPtr = &TemplateClass<float>::templateDo;
	(templateClassPtr->*templateDoFuncPtr)(11.f, 5);

	return 0;
}

