#include "operator_new.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78991749

namespace operator_new_ {
////////////////////////////////////////////////////////////////
// reference: http://zh.cppreference.com/w/cpp/memory/new/operator_new
class New1 {
public:
	New1() = default;

	void* operator new(std::size_t sz){
		std::printf("global op new called, size = %zu\n", sz);
		return std::malloc(sz);
	}

	void operator delete(void* ptr) /*noexcept*/
	{
		std::puts("global op delete called");
		std::free(ptr);
	}
};

struct New2 {
	static void* operator new(std::size_t sz)
	{
		std::cout << "custom new for size " << sz << '\n';
		return ::operator new(sz);
	}

	static void* operator new[](std::size_t sz)
	{
		std::cout << "custom new for size " << sz << '\n';
		return ::operator new(sz);
	}

	static void operator delete(void* ptr, std::size_t sz)
	{
		std::cout << "custom delete for size " << sz << '\n';
		::operator delete(ptr);
	}

	static void operator delete[](void* ptr, std::size_t sz)
	{
		std::cout << "custom delete for size " << sz << '\n';
		::operator delete(ptr);
	}
};

struct New3 {
	New3() { throw std::runtime_error(""); }

	static void* operator new(std::size_t sz, bool b){
		std::cout << "custom placement new called, b = " << b << '\n';
		return ::operator new(sz);
	}

	static void operator delete(void* ptr, bool b)
	{
		std::cout << "custom placement delete called, b = " << b << '\n';
		::operator delete(ptr);
	}
};

int test_operator_new_1()
{
	New1* new1 = new New1;
	delete new1;

	New2* p1 = new New2;
	delete p1;
	New2* p2 = new New2[10];
	delete[] p2;

	try {
		New3* p1 = new (true) New3;
	} catch (const std::exception&) {}



	return 0;
}

///////////////////////////////////////////////////////////////
// https://www.geeksforgeeks.org/overloading-new-delete-operator-c/
class student
{
	std::string name;
	int age;
public:
	student()
	{
		std::cout << "Constructor is called\n";
	}

	student(std::string name, int age)
	{
		std::cout << "Constructor params is called\n";
		this->name = name;
		this->age = age;
	}

	void display()
	{
		std::cout << "Name:" << name << std::endl;
		std::cout << "Age:" << age << std::endl;
	}

	void * operator new(size_t size)
	{
		std::cout << "Overloading new operator with size: " << size << std::endl;
		void * p = ::new student();
		//void * p = malloc(size); will also work fine

		return p;
	}

	void operator delete(void * p)
	{
		std::cout << "Overloading delete operator " << std::endl;
		free(p);
	}
};

int test_operator_new_2()
{
	student * p = new student("Yash", 24);

	p->display();
	delete p;

	return 0;
}

////////////////////////////////////////////////////////////////
// reference: http://thispointer.com/overloading-new-and-delete-operators-at-global-and-class-level/
class Dummy
{
public:
	Dummy()
	{
		std::cout << "Dummy :: Constructor" << std::endl;
	}

	~Dummy()
	{
		std::cout << "Dummy :: Destructor" << std::endl;
	}

	// Overloading CLass specific new operator
	static void* operator new(size_t sz)
	{
		void* m = malloc(sz);
		std::cout << "Dummy :: Operator new" << std::endl;
		return m;
	}

	// Overloading CLass specific delete operator
	static void operator delete(void* m)
	{
		std::cout << "Dummy :: Operator delete" << std::endl;
		free(m);
	}
};

int test_operator_new_3()
{
	Dummy * dummyPtr = new Dummy;
	delete dummyPtr;

	return 0;
}

//////////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/kftdy56f.aspx
class Blanks
{
public:
	Blanks() { std::cout << "Constructor " << std::endl; }
	void* operator new(size_t stAllocateBlock, char chInit);
};

void* Blanks::operator new(size_t stAllocateBlock, char chInit)
{
	std::cout << "size:" << stAllocateBlock << ",chInit:" << chInit << "end" << std::endl;
	void *pvTemp = malloc(stAllocateBlock);
	if (pvTemp != 0)
		memset(pvTemp, chInit, stAllocateBlock);
	return pvTemp;
}

int test_operator_new_4()
{
	Blanks *a5 = new(0xa5) Blanks;
	std::cout << (a5 != 0) << std::endl;

	return 0;
}

////////////////////////////////////////////////////////////
// reference: http://www.interviewsansar.com/2015/07/15/write-syntax-to-overload-new-and-delete-operator-in-a-class/
class CustomMemory {
private:
	int i; // size of int is 4 byte
public:
	CustomMemory(){
		std::cout << "Constructor" << "\n";
	}
	~CustomMemory(){
		std::cout << "Destructor" << "\n";
	}

	//Overloaded new
	void* operator new(size_t objectSize)
	{
		std::cout << "Custom memory allocation" << "\n";
		//Write allocation algorithm here
		return malloc(objectSize);

	}

	//Overloaded 2 arguments new operator
	void* operator new(size_t objectSize, int x)
	{
		std::cout << "Custom 2 argument memory allocation" << "\n";
		CustomMemory *ptr = (CustomMemory*)malloc(objectSize);
		ptr->i = x;

		return ptr;
	}

	//Overloaded delete
	void operator delete(void* ptr)
	{
		std::cout << "Custom memory de- allocation" << "\n";
		free(ptr);
	}

	void Display()
	{
		std::cout << "Value of i =" << i << "\n";
	}
};

int test_operator_new_5()
{
	CustomMemory* obj = new CustomMemory(); // call overloaded new from the class delete obj;
	delete obj; // call overloaded delete

	//overloaded 2 argument new
	CustomMemory * ptr = new(5)CustomMemory();
	ptr->Display();
	delete ptr;

	return 0;
}

} // namespace operator_new_

