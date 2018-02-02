#include "map.hpp"
#include <iostream>
#include <map>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52074286

//////////////////////////////////////////////////
// reference: https://www.sgi.com/tech/stl/Map.html
int test_map1()
{
	struct ltstr {
		bool operator()(const char* s1, const char* s2) const
		{
			return strcmp(s1, s2) > 0;
		}
	};

	std::map<const char*, int, ltstr> months;

	months["january"] = 31;
	months["february"] = 28;
	months["march"] = 31;
	months["april"] = 30;
	months["may"] = 31;
	months["june"] = 30;
	months["july"] = 31;
	months["august"] = 31;
	months["september"] = 30;
	months["october"] = 31;
	months["november"] = 30;
	months["december"] = 31;

	int tmp1 = months.count("aaa");
	int tmp2 = months.count("july");

	std::cout << "june -> " << months["june"] << std::endl;
	std::map<const char*, int, ltstr>::iterator cur = months.find("june");
	std::map<const char*, int, ltstr>::iterator prev = cur;
	std::map<const char*, int, ltstr>::iterator next = cur;
	++next;
	--prev;
	std::cout << "Previous (in alphabetical order) is " << (*prev).first << std::endl;
	std::cout << "Next (in alphabetical order) is " << (*next).first << std::endl;

	// show content:
	for (std::map<const char*, int, ltstr>::const_iterator it = months.begin(); it != months.end(); ++it) {
		std::cout << it->first << " => " << it->second << '\n';
	}

	return 0;
}

///////////////////////////////////////////////////////////////
// reference: http://www.yolinux.com/TUTORIALS/CppStlMultiMap.html
int test_map2()
{
	std::map<std::string, int> Employees;

	// Examples of assigning Map container contents

	// 1) Assignment using array index notation
	Employees["Mike C."] = 5234;
	Employees["Charlie M."] = 3374;

	// 2) Assignment using member function insert() and STL pair
	Employees.insert(std::pair<std::string, int>("David D.", 1923));

	// 3) Assignment using member function insert() and "value_type()"
	Employees.insert(std::map<std::string, int>::value_type("John A.", 7582));

	// 4) Assignment using member function insert() and "make_pair()"
	Employees.insert(std::make_pair("Peter Q.", 5328));

	std::cout << "Map size: " << Employees.size() << std::endl;

	for (std::map<std::string, int>::iterator ii = Employees.begin(); ii != Employees.end(); ++ii) {
		std::cout << (*ii).first << ": " << (*ii).second << std::endl;
	}

	Employees.erase("David D.");

	std::cout << "Map size: " << Employees.size() << std::endl;

	for (std::map<std::string, int>::iterator ii = Employees.begin(); ii != Employees.end(); ++ii) {
		std::cout << (*ii).first << ": " << (*ii).second << std::endl;
	}

	Employees.clear();
	std::cout << "Map size: " << Employees.size() << std::endl;
	std::cout << "Map empty: " << Employees.empty() << std::endl;

	return 0;
}

////////////////////////////////////////////////////////////
// reference: http://www.yolinux.com/TUTORIALS/CppStlMultiMap.html
class AAA
{
	friend std::ostream &operator<<(std::ostream &, const AAA &);

public:
	int x;
	int y;
	float z;

	AAA();
	AAA(const AAA &);
	~AAA(){};
	AAA &operator=(const AAA &rhs);
	int operator==(const AAA &rhs) const;
	int operator<(const AAA &rhs) const;
};

AAA::AAA()   // Constructor
{
	x = 0;
	y = 0;
	z = 0;
}

AAA::AAA(const AAA &copyin)   // Copy constructor to handle pass by value.
{
	x = copyin.x;
	y = copyin.y;
	z = copyin.z;
}

std::ostream &operator<<(std::ostream &output, const AAA &aaa)
{
	output << aaa.x << ' ' << aaa.y << ' ' << aaa.z << std::endl;
	return output;
}

AAA& AAA::operator=(const AAA &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return *this;
}

int AAA::operator==(const AAA &rhs) const
{
	if (this->x != rhs.x) return 0;
	if (this->y != rhs.y) return 0;
	if (this->z != rhs.z) return 0;
	return 1;
}

int AAA::operator<(const AAA &rhs) const
{
	if (this->x == rhs.x && this->y == rhs.y && this->z < rhs.z) return 1;
	if (this->x == rhs.x && this->y < rhs.y) return 1;
	if (this->x < rhs.x) return 1;
	return 0;
}

int test_map3()
{
	std::map<std::string, AAA> M;
	AAA Ablob;

	Ablob.x = 7;
	Ablob.y = 2;
	Ablob.z = 4.2355;
	M["C"] = Ablob;

	Ablob.x = 5;
	M["B"] = Ablob;

	Ablob.z = 3.2355;
	M["A"] = Ablob;

	Ablob.x = 3;
	Ablob.y = 7;
	Ablob.z = 7.2355;
	M["D"] = Ablob;

	for (std::map<std::string, AAA>::iterator ii = M.begin(); ii != M.end(); ++ii) {
		std::cout << (*ii).first << ": " << (*ii).second << std::endl;
	}

	return 0;
}

///////////////////////////////////////////////
// reference: http://www.yolinux.com/TUTORIALS/CppStlMultiMap.html
class Person
{
	friend class PersonLessThan;
public:
	std::string firstName;
	std::string lastName;

	Person(const std::string &firstName, const std::string &lastName);
};

Person::Person(const std::string &_firstName, const std::string &_lastName)
	: firstName(_firstName), lastName(_lastName)
{}

class PersonLessThan
{
public:
	bool operator( )(const Person& p1, const Person& p2) const {
		if (p1.lastName < p2.lastName)
			return(true);
		else if (p1.lastName == p2.lastName)
			return(p1.firstName < p2.firstName);
		else
			return(false);
	}
};

int test_map4()
{
	std::map<Person, bool, PersonLessThan> M;
	Person p_1("Wilma", "Flintstone");
	Person p_2("Betty", "Rubble");
	Person p_3("Fred", "Flintstone");
	Person p_4("Barney", "Rubble");

	M[p_1] = true;
	M[p_2] = true;
	M[p_3] = true;
	M[p_4] = true;

	for (std::map<Person, bool>::iterator ii = M.begin(); ii != M.end(); ++ii) {
		std::cout << ((*ii).first).lastName << ", " << ((*ii).first).firstName << ": " << (*ii).second << std::endl;
	}

	return 0;
}

/////////////////////////////////////////////////
// reference: http://thispointer.com/stdmap-tutorial-part-1-usage-detail-with-examples/
int test_map5()
{
	std::map<std::string, int> mapOfWords;
	// Inserting data in std::map
	mapOfWords.insert(std::make_pair("earth", 1));
	mapOfWords.insert(std::make_pair("moon", 2));
	mapOfWords["sun"] = 3;
	// Will replace the value of already added key i.e. earth
	mapOfWords["earth"] = 4;
	// Iterate through all elements in std::map
	std::map<std::string, int>::iterator it = mapOfWords.begin();
	while (it != mapOfWords.end()) {
		std::cout << it->first << " :: " << it->second << std::endl;
		it++;
	}
	// Check if insertion is successful or not
	if (mapOfWords.insert(std::make_pair("earth", 1)).second == false) {
		std::cout << "Element with key 'earth' not inserted because already existed" << std::endl;
	}
	// Searching element in std::map by key.
	if (mapOfWords.find("sun") != mapOfWords.end())
		std::cout << "word 'sun' found" << std::endl;
	if (mapOfWords.find("mars") == mapOfWords.end())
		std::cout << "word 'mars' not found" << std::endl;

	return 0;
}
