#include "namespace.hpp"
#include <iostream>
#include <vector>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78575978

namespace namespace_ {

////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/namespace
namespace A {
	int x;
}

namespace B {
	int i;
	struct g { };
	struct x { };
	void f(int) { fprintf(stdout, "%s, %d\n", __FUNCTION__, __LINE__); };
	void f(double) { fprintf(stdout, "%s, %d\n", __FUNCTION__, __LINE__); };
	void g(char) { fprintf(stdout, "%s, %d\n", __FUNCTION__, __LINE__); }; // OK: function name g hides struct g
}

int test_namespace_1()
{
	int i;
	//using B::i; // error: i declared twice

	void f(char);
	using B::f; // OK: f(char), f(int), f(double) are overloads
	f(3.5); // calls B::f(double)

	using B::g;
	g('a');      // calls B::g(char)
	struct g g1; // declares g1 to have type struct B::g

	using B::x;
	using A::x;  // OK: hides struct B::x
	x = 99;      // assigns to A::x
	struct x x1; // declares x1 to have type struct B::x

	return 0;
}

/////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/namespace
namespace D {
	int d1;
	void f(char) { fprintf(stdout, "%s, %d\n", __FUNCTION__, __LINE__); };
}
using namespace D; // introduces D::d1, D::f, D::d2, D::f,
//  E::e, and E::f into global namespace!

int d1; // OK: no conflict with D::d1 when declaring
namespace E {
	int e;
	void f(int) { fprintf(stdout, "%s, %d\n", __FUNCTION__, __LINE__); };
}
namespace D { // namespace extension
	int d2;
	using namespace E; // transitive using-directive
	void f(int) { fprintf(stdout, "%s, %d\n", __FUNCTION__, __LINE__); };
}

int test_namespace_2()
{
	//d1++; // error: ambiguous ::d1 or D::d1?
	::namespace_::d1++; // OK
	D::d1++; // OK
	d2++; // OK, d2 is D::d2
	e++; // OK: e is E::e due to transitive using
	//f(1); // error: ambiguous: D::f(int) or E::f(int)?
	f('a'); // OK: the only f(char) is D::f(char)

	return 0;
}

//////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/namespace
namespace vec {

	template< typename T >
	class vector {
		// ...
	};

} // of vec

int test_namespace_3()
{
	std::vector<int> v1; // Standard vector.
	vec::vector<int> v2; // User defined vector.

	//v1 = v2; // Error: v1 and v2 are different object's type.

	{
		using namespace std;
		vector<int> v3; // Same as std::vector
		v1 = v3; // OK
	}

	{
		using vec::vector;
		vector<int> v4; // Same as vec::vector
		v2 = v4; // OK
	}

	return 0;
}

///////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/5cb46ksf.aspx
/*namespace Test {
	namespace old_ns {
		std::string Func() { return std::string("Hello from old"); }
	}

	inline namespace new_ns {
		std::string Func() { return std::string("Hello from new"); }
	}
}

int test_namespace_4()
{
	using namespace Test;
	using namespace std;

	string s = Func();
	std::cout << s << std::endl; // "Hello from new"
	return 0;
} */

///////////////////////////////////////////////////////
// reference: https://www.tutorialspoint.com/cplusplus/cpp_namespaces.htm
// first name space
namespace first_space {
	void func() {
		std::cout << "Inside first_space" << std::endl;
	}

	// second name space
	namespace second_space {
		void func() {
			std::cout << "Inside second_space" << std::endl;
		}
	}
}

int test_namespace_5()
{
	using namespace first_space::second_space;

	// This calls function from second name space.
	func();

	return 0;
}

/////////////////////////////////////////////////////
// reference: http://www.geeksforgeeks.org/namespace-in-c/
// A C++ code to demonstrate that we can define methods outside namespace.
// Creating a namespace
namespace ns {
	void display();

	class geek {
	public:
		void display();
	};
}

// Defining methods of namespace
void ns::geek::display()
{
	std::cout << "ns::geek::display()\n";
}

void ns::display()
{
	std::cout << "ns::display()\n";
}

int test_namespace_6()
{
	ns::geek obj;
	ns::display();
	obj.display();

	return 0;
}

} // using namespace_

