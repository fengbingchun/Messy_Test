#include "for.hpp"
#include <iostream>
#include <vector>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52245142

////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/range-for
int test_for1()
{
	std::vector<int> v = { 0, 1, 2, 3, 4, 5 };

	for (const int& i : v) // access by const reference
		std::cout << i << ' ';
	std::cout << '\n';

	for (auto i : v) // access by value, the type of i is int
		std::cout << i << ' ';
	std::cout << '\n';

	for (auto&& i : v) // access by reference, the type of i is int&
		std::cout << i << ' ';
	std::cout << '\n';

	for (int n : {0, 1, 2, 3, 4, 5}) // the initializer may be a braced-init-list
		std::cout << n << ' ';
	std::cout << '\n';

	int a[] = { 0, 1, 2, 3, 4, 5 };
	for (int n : a) // the initializer may be an array
		std::cout << n << ' ';
	std::cout << '\n';

	for (int n : a)
		std::cout << 1 << ' '; // the loop variable need not be used
	std::cout << '\n';

	return 0;
}

///////////////////////////////////////////////////////
// reference: http://www.cprogramming.com/c++11/c++11-ranged-for-loop.html
int test_for2()
{
	// Modifying the Contents of the Vector
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);

	for (int& i : vec) {
		i++; // increments the value in the vector
	}
	for (int i : vec) {
		// show that the values are updated
		std::cout << i << std::endl;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////
// reference: http://www.cprogramming.com/c++11/c++11-ranged-for-loop.html
// forward-declaration to allow use in Iter
class IntVector;

class Iter {
public:
	Iter(const IntVector* p_vec, int pos) : _pos(pos), _p_vec(p_vec)
	{ }

	// these three methods form the basis of an iterator for use with a range-based for loop
	bool operator!= (const Iter& other) const
	{
		return _pos != other._pos;
	}

	// this method must be defined after the definition of IntVector since it needs to use it
	int operator* () const;

	const Iter& operator++ ()
	{
		++_pos;
		// although not strictly necessary for a range-based for loop
		// following the normal convention of returning a value from
		// operator++ is a good idea.
		return *this;
	}

private:
	int _pos;
	const IntVector *_p_vec;
};

class IntVector {
public:
	IntVector()
	{
	}

	int get(int col) const
	{
		return _data[col];
	}
	Iter begin() const
	{
		return Iter(this, 0);
	}

	Iter end() const
	{
		return Iter(this, 100);
	}

	void set(int index, int val)
	{
		_data[index] = val;
	}

private:
	int _data[100];
};

int Iter::operator* () const
{
	return _p_vec->get(_pos);
}

int test_for3()
{
	IntVector v;
	for (int i = 0; i < 100; i++) {
		v.set(i, i);
	}

	for (int i : v) {
		std::cout << i << std::endl;
	}

	return 0;
}
