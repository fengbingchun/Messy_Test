#ifndef FBC_MESSY_TEST_OPERATOR_HPP_
#define FBC_MESSY_TEST_OPERATOR_HPP_

#include <istream>
#include <ostream>
#include <iostream>

namespace operator_ {

class Point {
public:
	// various constructors
	Point() : x(0), y(0) {}
	Point(int x_, int y_) : x(x_), y(y_) {}
	Point(const Point& pt_) : x(pt_.x), y(pt_.y) {}

	// assignment operator: =
	Point& operator = (const Point& pt_);

	// compound assignment operators: += -= *= /= %= &= |= ^= <<= >>=
	Point& operator += (const Point& pt_);
	Point& operator -= (const Point& pt_);
	Point& operator *= (const Point& pt_);

	// comparison operators: == != > < >= <=
	bool operator == (const Point& pt_) const;
	bool operator != (const Point& pt_) const;
	bool operator > (const Point& pt_) const;

	// bitwise operators: ^ | & ~ << >>
	// note: this function is not a member function
	friend std::ostream& operator << (std::ostream& out, const Point& pt_); // output
	// note: this function is not a member function
	friend std::istream& operator >> (std::istream& in, Point& pt_); // input

	// logical operators: ! && ||

	//increment and decrement operators: ++ --
	Point& operator ++ (); // prefix: ++
	Point& operator ++ (int); // postfix: ++

public:
	int x, y; //< the point coordinates
};

// note: these function are not member function
Point operator + (const Point& pt_, int a);
Point operator + (const Point& a, const Point& b);
Point operator - (const Point& a, const Point& b);
Point operator * (const Point& a, const Point& b);

int test_operator_1();

} // namespace operator_

#endif // FBC_MESSY_TEST_OPERATOR_HPP_
