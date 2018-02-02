#include "for_each.hpp"
#include <iostream>
#include <algorithm> // for_each
#include <vector>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52294862

////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/algorithm/for_each
struct Sum {
	Sum() : sum{ 0 } { }
	void operator()(int n) { sum += n; }
	int sum;
};

int test_for_each1()
{
	std::vector<int> nums{ 3, 4, 2, 8, 15, 267 };

	std::cout << "before:";
	for (auto const &n : nums) {
		std::cout << ' ' << n;
	}
	std::cout << '\n';

	std::for_each(nums.begin(), nums.end(), [](int &n){ n++; });

	// calls Sum::operator() for each number
	Sum s = std::for_each(nums.begin(), nums.end(), Sum());

	std::cout << "after: ";
	for (auto const &n : nums) {
		std::cout << ' ' << n;
	}
	std::cout << '\n';
	std::cout << "sum: " << s.sum << '\n';

	return 0;
}

////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/algorithm/for_each/
void myfunction(int i) {  // function:
	std::cout << ' ' << i;
}

struct myclass {           // function object type:
	void operator() (int i) { std::cout << ' ' << i; }
} myobject;

int test_for_each2()
{
	std::vector<int> myvector;
	myvector.push_back(10);
	myvector.push_back(20);
	myvector.push_back(30);

	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(), myfunction);
	std::cout << '\n';

	// or:
	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(), myobject);
	std::cout << '\n';

	return 0;
}

/////////////////////////////////////////////////
// reference: http://thispointer.com/stdfor_each-tutorial-usage-details-with-examples/
void addNames(std::vector<std::string> & vecNames)
{
	vecNames.push_back("Varun");
	vecNames.push_back("Ajay");
	vecNames.push_back("John");
	vecNames.push_back("Rita");
}
void printName(std::string name)
{
	std::cout << name << std::endl;
}

class NameChecker {
	std::string m_biggerName;
	int m_nameCount;
public:
	NameChecker() : m_biggerName(""), m_nameCount(0)
	{}
	void operator()(std::string name)
	{
		if (m_biggerName.size() < name.size())
			m_biggerName = name;
		m_nameCount++;
	}

	const std::string& getBiggerName() const {
		return m_biggerName;
	}

	int getNameCount() const {
		return m_nameCount;
	}
};

void example_1(std::vector<std::string> & vecNames)
{
	// Display Each name in vector using std::for_each and global function
	std::for_each(vecNames.begin(), vecNames.end(), printName);
}

void example_2(std::vector<std::string> & vecNames)
{
	// Now Display Each name in vector using std::for_each and Lambda function
	std::for_each(vecNames.begin(), vecNames.end(), [](std::string name)
	{
		std::cout << name << std::endl;
	});
}
void example_3(std::vector<std::string> & vecNames)
{
	// Now count the number of names and in end print the biggest name
	// Let's do this with std::for_each and a function object.
	NameChecker nameCheckerObj = std::for_each(vecNames.begin(), vecNames.end(), NameChecker());

	std::cout << std::endl << "Biggest Name = " << nameCheckerObj.getBiggerName() << std::endl;
	std::cout << std::endl << "Total Names = " << nameCheckerObj.getNameCount() << std::endl;

}

int test_for_each3()
{
	std::vector<std::string> vecNames;
	addNames(vecNames);

	example_1(vecNames);
	example_2(vecNames);
	example_3(vecNames);

	return 0;
}

///////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/e5sk9w9k.aspx
// The function object multiplies an element by a Factor
template <class Type>
class MultValue {
private:
	Type Factor;   // The value to multiply by
public:
	// Constructor initializes the value to multiply by
	MultValue(const Type& _Val) : Factor(_Val) {
	}

	// The function call for the element to be multiplied
	void operator ( ) (Type& elem) const
	{
		elem *= Factor;
	}
};

// The function object to determine the average
class Average {
private:
	long num;      // The number of elements
	long sum;      // The sum of the elements
public:
	// Constructor initializes the value to multiply by
	Average() : num(0), sum(0)
	{
	}

	// The function call to process the next elment
	void operator ( ) (int elem)
	{
		num++;      // Increment the element count
		sum += elem;   // Add the value to the partial sum
	}

	// return Average
	operator double()
	{
		return  static_cast <double> (sum) / static_cast <double> (num);
	}
};

int test_for_each4()
{
	using namespace std;
	vector <int> v1;
	vector <int>::iterator Iter1;

	// Constructing vector v1
	for (int i = -4; i <= 2; i++) {
		v1.push_back(i);
	}

	cout << "Original vector  v1 = ( ";
	for (Iter1 = v1.begin(); Iter1 != v1.end(); Iter1++)
		cout << *Iter1 << " ";
	cout << ")." << endl;

	// Using for_each to multiply each element by a Factor
	for_each(v1.begin(), v1.end(), MultValue<int>(-2));

	cout << "Multiplying the elements of the vector v1\n "
		<< "by the factor -2 gives:\n v1mod1 = ( ";
	for (Iter1 = v1.begin(); Iter1 != v1.end(); Iter1++)
		cout << *Iter1 << " ";
	cout << ")." << endl;

	// The function object is templatized and so can be
	// used again on the elements with a different Factor
	for_each(v1.begin(), v1.end(), MultValue<int>(5));

	cout << "Multiplying the elements of the vector v1mod\n "
		<< "by the factor 5 gives:\n v1mod2 = ( ";
	for (Iter1 = v1.begin(); Iter1 != v1.end(); Iter1++)
		cout << *Iter1 << " ";
	cout << ")." << endl;

	// The local state of a function object can accumulate
	// information about a sequence of actions that the
	// return value can make available, here the Average
	double avemod2 = for_each(v1.begin(), v1.end(), Average());
	cout << "The average of the elements of v1 is:\n Average ( v1mod2 ) = "
		<< avemod2 << "." << endl;

	return 0;
}

//////////////////////////////////////////////////////
// reference: https://www.tutorialcup.com/cplusplus/for-each-loop.htm
void fun1(int x)
{
	std::cout << x << " ";
}

struct Class1 { // object type function
	void operator() (int x)
	{
		std::cout << x << " ";
	}
} obj1;

int test_for_each5()
{
	int arr[] = { 11, 21, 4, 13 };
	std::for_each(arr, arr + 4, fun1);
	std::cout << std::endl;
	std::for_each(arr, arr + 4, obj1);

	return 0;
}
