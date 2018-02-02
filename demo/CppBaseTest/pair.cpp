#include "pair.hpp"
#include <iostream>
#include <vector>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52205149

////////////////////////////////////////////
// reference: https://www.quora.com/How-can-I-use-pair-int-int-v-in-C++-language
int test_pair1()
{
	std::pair <int, int> foo;
	std::pair <int, int> bar;

	foo = std::make_pair(10, 20);
	bar = std::make_pair(10.5, 'A'); // ok: implicit conversion from pair<double,char>

	std::cout << "foo: " << foo.first << ", " << foo.second << '\n'; // foo: 10, 20
	std::cout << "bar: " << bar.first << ", " << bar.second << '\n'; // bar: 10, 65

	return 0;
}

//////////////////////////////////////////////
// reference: http://stackoverflow.com/questions/2164942/how-can-i-store-a-pair-of-numbers-in-c/2164969#2164969
int test_pair2()
{
	typedef std::pair<int, int> IntPair;

	std::vector<IntPair> pairs;
	pairs.push_back(std::make_pair(1, 2));
	pairs.push_back(std::make_pair(3, 4));

	for (int i = 0; i < pairs.size(); i++) {
		std::cout << pairs[i].first << "    " << pairs[i].second << std::endl;
	}

	return 0;
}

////////////////////////////////////////////
int test_pair3()
{
	std::pair<std::string, int> name1("Som", 15);
	std::pair<std::string, int> name2(name1);
	std::cout << "name2: " << name2.first << "    " << name2.second << std::endl;
	
	std::pair<std::string, int> name3 = std::make_pair("Som", 15);
	if (name1 == name3) {
		std::cout << "they are the same people" << std::endl;
	} else {
		std::cout << "they are not the same people" << std::endl;
	}

	std::pair<std::string, int> name4;
	name4 = name1;
	std::cout << "name4: " << name4.first << "    " << name4.second << std::endl;

	std::pair<std::string, int> name5("Som", 16);
	if (name1 > name5) {
		std::cout << "name1 > name5" << std::endl;
	} else if (name1 < name5) {
		std::cout << "name1 < name5" << std::endl;
	} else {
		std::cout << "name1 == name5" << std::endl;
	}

	std::pair<std::string, int> name6("Take", 11);
	std::cout << "name1: " << name1.first << "    " << name1.second << std::endl;
	std::cout << "name6: " << name6.first << "    " << name6.second << std::endl;
	std::swap(name1, name6); // C++11::endl;
	std::cout << "after std::swap: " << std::endl;
	std::cout << "name1: " << name1.first << "    " << name1.second << std::endl;
	std::cout << "name6: " << name6.first << "    " << name6.second << std::endl;

	return 0;
}
