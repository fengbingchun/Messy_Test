#include "encapsulation.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52078478

/////////////////////////////////////////////////
// reference: http://www.tutorialspoint.com/cplusplus/cpp_data_encapsulation.htm
class Adder{
public:
	// constructor
	Adder(int i = 0)
	{
		total = i;
	}
	// interface to outside world
	void addNum(int number)
	{
		total += number;
	}
	// interface to outside world
	int getTotal()
	{
		return total;
	};
private:
	// hidden data from outside world
	int total;
};

int test_encapsulation1()
{
	Adder a;

	a.addNum(10);
	a.addNum(20);
	a.addNum(30);

	std::cout << "Total " << a.getTotal() << std::endl;
	return 0;
}
