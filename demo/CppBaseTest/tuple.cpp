#include "tuple.hpp"
#include <iostream>
#include <tuple>
#include <string>
#include <functional>
#include <utility>

// Blog: http://blog.csdn.net/fengbingchun/article/details/72858282

//////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/tuple/tuple/
int test_tuple_4()
{
{ // tuple::tuple: Constructs a tuple object. This involves individually constructing its elements,
  // with an initialization that depends on the constructor form invoke
	std::tuple<int, char> first;                             // default
	std::tuple<int, char> second(first);                    // copy
	std::tuple<int, char> third(std::make_tuple(20, 'b'));   // move
	std::tuple<long, char> fourth(third);                   // implicit conversion
	std::tuple<int, char> fifth(10, 'a');                    // initialization
	std::tuple<int, char> sixth(std::make_pair(30, 'c'));    // from pair / move

	std::cout << "sixth contains: " << std::get<0>(sixth);
	std::cout << " and " << std::get<1>(sixth) << '\n';
}

{ // std::tuple::operator=: Each of the elements in the tuple object is assigned its corresponding element
	std::pair<int, char> mypair(0, ' ');

	std::tuple<int, char> a(10, 'x');
	std::tuple<long, char> b, c;

	b = a;                                // copy assignment
	c = std::make_tuple(100L, 'Y');       // move assignment
	a = c;                                // conversion assignment
	c = std::make_tuple(100, 'z');        // conversion / move assignment
	a = mypair;                           // from pair assignment
	a = std::make_pair(2, 'b');           // form pair /move assignment

	std::cout << "c contains: " << std::get<0>(c);
	std::cout << " and " << std::get<1>(c) << '\n';
}

{ // std::tuple::swap: Exchanges the content of the tuple object by the content of tpl,
  // which is another tuple of the same type (containing objects of the same types in the same order)
	std::tuple<int, char> a(10, 'x');
	std::tuple<int, char> b(20, 'y');

	a.swap(b);
	std::cout << "a contains: " << std::get<0>(a);
	std::cout << " and " << std::get<1>(a) << '\n';

	std::swap(a, b);
	std::cout << "a contains: " << std::get<0>(a);
	std::cout << " and " << std::get<1>(a) << '\n';
}

{ // std::relational operators: Performs the appropriate comparison operation between the tuple objects lhs and rhs
	std::tuple<int, char> a(10, 'x');
	std::tuple<char, char> b(10, 'x');
	std::tuple<char, char> c(10, 'y');

	if (a == b) std::cout << "a and b are equal\n";
	if (b != c) std::cout << "b and c are not equal\n";
	if (b<c) std::cout << "b is less than c\n";
	if (c>a) std::cout << "c is greater than a\n";
	if (a <= c) std::cout << "a is less than or equal to c\n";
	if (c >= b) std::cout << "c is greater than or equal to b\n";
}

	return 0;
}

////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/bb982771.aspx
int test_tuple_3()
{
	typedef std::tuple<int, double, int, double> Mytuple;

	Mytuple c0(0, 1, 2, 3);
	// display contents " 0 1 2 3" 
	std::cout << " " << std::get<0>(c0);
	std::cout << " " << std::get<1>(c0);
	std::cout << " " << std::get<2>(c0);
	std::cout << " " << std::get<3>(c0);
	std::cout << std::endl;

	Mytuple c1;
	c1 = c0;
	// display contents " 0 1 2 3" 
	std::cout << " " << std::get<0>(c1);
	std::cout << " " << std::get<1>(c1);
	std::cout << " " << std::get<2>(c1);
	std::cout << " " << std::get<3>(c1);
	std::cout << std::endl;

	std::tuple<char, int> c2(std::make_pair('x', 4));
	// display contents " x 4" 
	std::cout << " " << std::get<0>(c2);
	std::cout << " " << std::get<1>(c2);
	std::cout << std::endl;

	Mytuple c3(c0);
	// display contents " 0 1 2 3" 
	std::cout << " " << std::get<0>(c3);
	std::cout << " " << std::get<1>(c3);
	std::cout << " " << std::get<2>(c3);
	std::cout << " " << std::get<3>(c3);
	std::cout << std::endl;

	typedef std::tuple<int, float, int, float> Mytuple2;

	Mytuple c4(Mytuple2(4, 5, 6, 7));
	// display contents " 4 5 6 7" 
	std::cout << " " << std::get<0>(c4);
	std::cout << " " << std::get<1>(c4);
	std::cout << " " << std::get<2>(c4);
	std::cout << " " << std::get<3>(c4);
	std::cout << std::endl;

	return (0);
}

///////////////////////////////////////////////////
// reference: http://zh.cppreference.com/w/cpp/utility/tuple
static std::tuple<double, char, std::string> get_student(int id)
{
	if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
	if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
	if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
	throw std::invalid_argument("id");
}

int test_tuple_2()
{
	auto student0 = get_student(0);
	std::cout << "ID: 0, "
		<< "GPA: " << std::get<0>(student0) << ", "
		<< "grade: " << std::get<1>(student0) << ", "
		<< "name: " << std::get<2>(student0) << '\n';

	double gpa1;
	char grade1;
	std::string name1;
	std::tie(gpa1, grade1, name1) = get_student(1);
	std::cout << "ID: 1, "
		<< "GPA: " << gpa1 << ", "
		<< "grade: " << grade1 << ", "
		<< "name: " << name1 << '\n';

	return 0;
}

///////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/tuple/
static void print_pack(std::tuple<std::string&&, int&&> pack)
{
	std::cout << std::get<0>(pack) << ", " << std::get<1>(pack) << '\n';
}

static void fun(int &a)
{
	a = 15;
}

int test_tuple_1()
{
{ // std::tuple_element: class template, Class designed to access the type of the Ith element in a tuple.
  // It is a simple class with a single member type, tuple_element::type,
  // defined as an alias of the type of the Ith element in a tuple of type T.
	auto mytuple = std::make_tuple(10, 'a');

	std::tuple_element<0, decltype(mytuple)>::type first = std::get<0>(mytuple);
	std::tuple_element<1, decltype(mytuple)>::type second = std::get<1>(mytuple);

	std::cout << "mytuple contains: " << first << " and " << second << '\n';
}

{ // std::tuple_size: Class template designed to access the number of elements in a tuple
	std::tuple<int, char, double> mytuple(10, 'a', 3.14);

	std::cout << "mytuple has ";
	std::cout << std::tuple_size<decltype(mytuple)>::value;
	std::cout << " elements." << '\n';
}

{ // std::forward_as_tuple: function template, Constructs a tuple object with rvalue references
  // to the elements in args suitable to be forwarded as argument to a function.
	std::string str("John");
	print_pack(std::forward_as_tuple(str + " Smith", 25));
	print_pack(std::forward_as_tuple(str + " Daniels", 22));
}

{ // std::get: funtion template, Returns a reference to the Ith element of tuple tpl.
	std::tuple<int, char> mytuple(10, 'a');

	std::get<0>(mytuple) = 20;

	std::cout << "mytuple contains: ";
	std::cout << std::get<0>(mytuple) << " and " << std::get<1>(mytuple);
	std::cout << std::endl;
}

{ // std::make_tuple: function template, Constructs an object of the appropriate tuple type
  // to contain the elements specified in args
	auto first = std::make_tuple(10, 'a');             // tuple < int, char >

	const int a = 0; int b[3];                         // decayed types:
	auto second = std::make_tuple(a, b);               // tuple < int, int* >

	auto third = std::make_tuple(std::ref(a), "abc");  // tuple < const int&, const char* >

	std::cout << "third contains: " << std::get<0>(third);
	std::cout << " and " << std::get<1>(third);
	std::cout << std::endl;
}

{ // std::tie: function template, Constructs a tuple object whose elements are references
  // to the arguments in args, in the same order
  // std::ignore: object, This object ignores any value assigned to it. It is designed to be used as an
  // argument for tie to indicate that a specific element in a tuple should be ignored.
	int myint;
	char mychar;

	std::tuple<int, float, char> mytuple;

	mytuple = std::make_tuple(10, 2.6, 'a');          // packing values into tuple

	std::tie(myint, std::ignore, mychar) = mytuple;   // unpacking tuple into variables

	std::cout << "myint contains: " << myint << '\n';
	std::cout << "mychar contains: " << mychar << '\n';
}

{ // std::tuple_cat: function template, Constructs an object of the appropriate tuple type
  // to contain a concatenation of the elements of all the tuples in tpls, in the same order
	std::tuple<float, std::string> mytuple(3.14, "pi");
	std::pair<int, char> mypair(10, 'a');

	auto myauto = std::tuple_cat(mytuple, std::tuple<int, char>(mypair));

	std::cout << "myauto contains: " << '\n';
	std::cout << std::get<0>(myauto) << '\n';
	std::cout << std::get<1>(myauto) << '\n';
	std::cout << std::get<2>(myauto) << '\n';
	std::cout << std::get<3>(myauto) << '\n';
}

{ // tuple::tuple: A tuple is an object capable to hold a collection of elements.
	// Each element can be of a different type.
	std::tuple<int, char> foo(10, 'x');
	auto bar = std::make_tuple("test", 3.1, 14, 'y');

	std::get<2>(bar) = 100;                                    // access element

	int myint; char mychar;

	std::tie(myint, mychar) = foo;                            // unpack elements
	std::tie(std::ignore, std::ignore, myint, mychar) = bar;  // unpack (with ignore)

	mychar = std::get<3>(bar);

	std::get<0>(foo) = std::get<2>(bar);
	std::get<1>(foo) = mychar;

	std::cout << "foo contains: ";
	std::cout << std::get<0>(foo) << ' ';
	std::cout << std::get<1>(foo) << '\n';
}

{
	std::tuple<int, char> foo{ 12, 'a' };
	std::cout << std::get<0>(foo) << "\n"; // 12
	fun(std::get<0>(foo));
	std::cout << std::get<0>(foo) << "\n"; // 15
}

	return 0;
}
