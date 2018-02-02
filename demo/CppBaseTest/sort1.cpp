#include "sort1.hpp"
#include <iostream>
#include <algorithm> // std::sort
#include <functional> // std::greater
#include <vector>
#include <array>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/71305229

///////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/algorithm/sort/
static bool myfunction(int i, int j) { return (i < j); }

static struct myclass {
	bool operator() (int i, int j) { return (i < j); }
} myobject;

int test_sort_1()
{
	int myints[] { 32, 71, 12, 45, 26, 80, 53, 33 };
	std::vector<int> myvector(myints, myints + 8);               // 32 71 12 45 26 80 53 33

	// using default comparison (operator <):
	std::sort(myvector.begin(), myvector.begin() + 4);           //(12 32 45 71)26 80 53 33

	// using function as comp
	std::sort(myvector.begin() + 4, myvector.end(), myfunction); // 12 32 45 71(26 33 53 80)

	// using object as comp
	std::sort(myvector.begin(), myvector.end(), myobject);     //(12 26 32 33 45 53 71 80)

	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	myvector.assign(myints, myints + 8);
	std::sort(myvector.begin(), myvector.end(), std::greater<int>()); // descending is to use std::greater()
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	// use std::sort to sort an array in C++11: std::begin/std::end
	std::sort(std::begin(myints), std::end(myints));
	for (int i = 0; i < 8; ++i) {
		std::cout << " " << myints[i];
	}
	std::cout << "\n";

	return 0;
}

/////////////////////////////////////////////////
// reference: https://www.codeproject.com/Articles/38381/STL-Sort-Comparison-Function
class Person_sort4 {
public:
	// default constructor
	Person_sort4() : age(0) {}
	Person_sort4(int age, std::string name) {
		this->age = age; this->name = name;
	}
	bool operator<(const Person_sort4& rhs) { // define a member < operator for the Person class
		return this->age < rhs.age;
	}

	int age;
	std::string name;
};

int test_sort_4()
{
	std::vector<Person_sort4> vecPerson;
	vecPerson.push_back(Person_sort4(24, "Calvin"));
	vecPerson.push_back(Person_sort4(30, "Benny"));
	vecPerson.push_back(Person_sort4(28, "Alison"));

	std::sort(vecPerson.begin(), vecPerson.end());

	for (size_t i = 0; i<vecPerson.size(); ++i)
		std::cout << vecPerson[i].age << ", " << vecPerson[i].name << std::endl;

	return 0;
}

/////////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/articles/NhA0RXSz/
struct Person_sort {
	// Left out making a constructor for simplicity's sake.
	std::string name;
	int age;
	std::string favoriteColor;
};

// Sort Container by name function
static bool sortByName(const Person_sort &lhs, const Person_sort &rhs) { return lhs.name < rhs.name; }

// Sort Container by age function
static bool sortByAge(const Person_sort &lhs, const Person_sort &rhs) { return lhs.age < rhs.age; }

// Sort Container by favorite color
// We can just sort alphabetically and then it will group the color together.
static bool sortByColor(const Person_sort &lhs, const Person_sort &rhs) { return lhs.favoriteColor < rhs.favoriteColor; }

// A global const variable to hold how many people to ask for input for.
const unsigned numberOfPeople = 2;

int test_sort_2()
{
	using std::vector;
	using std::cout;
	using std::cin;
	using std::endl;
	using std::sort;
	using std::string;

	// Make a vector that holds 5 blank Person_sort Objects
	vector<Person_sort> people { { "Tom", 23, "Red" }, {"Jim", 11, "Green"} };

	// This will ask for user input to populate the container
	// with 5 different indivuals.
	//for (vector<Person_sort>::size_type i = 0; i != numberOfPeople; ++i) {
	//	cout << "Person_sort #" << i + 1 << " name: ";
	//	cin >> people[i].name;

	//	cout << "Person_sort #" << i + 1 << " age: ";
	//	cin >> people[i].age;

	//	cout << "Person_sort #" << i + 1 << " favorite color: ";
	//	cin >> people[i].favoriteColor;
	//}
	//cout << "\n\n";

	// Sort by name
	sort(people.begin(), people.end(), sortByName);
	for (Person_sort &n : people)
		cout << n.name << " ";
	cout << endl;

	// Sory by age
	sort(people.begin(), people.end(), sortByAge);
	for (Person_sort &n : people)
		cout << n.age << " ";
	cout << endl;

	// Sort by color
	sort(people.begin(), people.end(), sortByColor);
	for (Person_sort &n : people)
		cout << n.favoriteColor << " ";
	cout << endl;

	return 0;
}

/////////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/algorithm/sort
int test_sort_3()
{
	std::array<int, 10> s = { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };

	// sort using the default operator<
	std::sort(s.begin(), s.end());
	for (auto a : s) {
		std::cout << a << " ";
	}
	std::cout << '\n';

	// sort using a standard library compare function object
	std::sort(s.begin(), s.end(), std::greater<int>());
	for (auto a : s) {
		std::cout << a << " ";
	}
	std::cout << '\n';

	// sort using a custom function object
	struct {
		bool operator()(int a, int b) const {
			return a < b;
		}
	} customLess;
	std::sort(s.begin(), s.end(), customLess);
	for (auto a : s) {
		std::cout << a << " ";
	}
	std::cout << '\n';

	// sort using a lambda expression 
	std::sort(s.begin(), s.end(), [](int a, int b) {
		return b < a;
	});
	for (auto a : s) {
		std::cout << a << " ";
	}
	std::cout << '\n';

	return 0;
}

/////////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/algorithm/stable_sort/
static bool compare_as_ints(double i, double j)
{
	return (int(i)<int(j));
}

int test_stable_sort_1()
{
	double mydoubles[] { 3.14, 1.41, 2.72, 4.67, 1.73, 1.32, 1.62, 2.58 };

	std::vector<double> myvector;
	myvector.assign(mydoubles, mydoubles + 8);

	std::cout << "using default comparison:";
	std::stable_sort(myvector.begin(), myvector.end());
	for (std::vector<double>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	myvector.assign(mydoubles, mydoubles + 8);

	std::cout << "using 'compare_as_ints' :";
	std::stable_sort(myvector.begin(), myvector.end(), compare_as_ints);
	for (std::vector<double>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}

/////////////////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/algorithm/stable_sort
struct Employee_sort {
	Employee_sort(int age, std::string name) : age(age), name(name) { }
	int age;
	std::string name;  // Does not particpate in comparisons
};

static bool operator<(const Employee_sort &lhs, const Employee_sort &rhs)
{
	return lhs.age < rhs.age;
}

int test_stable_sort_2()
{
	std::vector<Employee_sort> v = {
		Employee_sort(108, "Zaphod"),
		Employee_sort(32, "Arthur"),
		Employee_sort(108, "Ford"),
	};

	std::stable_sort(v.begin(), v.end());

	for (const Employee_sort &e : v) {
		std::cout << e.age << ", " << e.name << '\n';
	}

	return 0;
}

////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/algorithm/partial_sort/
int test_partial_sort_1()
{
	int myints[] { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	std::vector<int> myvector(myints, myints + 9);

	// using default comparison (operator <):
	std::partial_sort(myvector.begin(), myvector.begin() + 5, myvector.end());

	// using function as comp
	std::partial_sort(myvector.begin(), myvector.begin() + 5, myvector.end(), myfunction);

	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}
