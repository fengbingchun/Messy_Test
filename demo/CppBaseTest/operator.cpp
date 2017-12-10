#include <assert.h>
#include "operator.hpp"
#include "universal.hpp"

namespace operator_ {

Point& Point::operator = (const Point& pt_)
{
	if (this == &pt_) {
		return *this;
	}

	this->x = pt_.x;
	this->y = pt_.y;

	return *this;
}

Point& Point::operator += (const Point& pt_)
{
	this->x += pt_.x;
	this->y += pt_.y;

	return *this;
}

Point& Point::operator -= (const Point& pt_)
{
	this->x -= pt_.x;
	this->y -= pt_.y;

	return *this;
}

Point& Point::operator *= (const Point& pt_)
{
	this->x *= pt_.x;
	this->y *= pt_.y;

	return *this;
}

bool Point::operator == (const Point& pt_) const
{
	return (this->x == pt_.x && this->y == pt_.y);
}

bool Point::operator != (const Point& pt_) const
{
	return !(operator == (pt_));
}

bool Point::operator > (const Point& pt_) const
{
	return (this->x > pt_.x && this->y > pt_.y);
}

std::ostream& operator << (std::ostream& out, const Point& pt_) // output
{
	out << "x: " << pt_.x << std::endl;
	out << "y: " << pt_.y << std::endl;

	return out;
}

std::istream& operator >> (std::istream& in, Point& pt_) // input
{
	std::cout << "x: ";
	in >> pt_.x;
	std::cout << std::endl;
	std::cout << "y: ";
	in >> pt_.y;
	std::cout << std::endl;

	return in;
}

Point& Point::operator ++ ()
{
	++this->x;
	++this->y;

	return *this;
}

Point& Point::operator ++ (int)
{
	Point tmp(*this);
	operator++();

	return tmp;
}

Point operator + (const Point& pt_, int a)
{
	Point tmp;
	tmp.x = pt_.x + a;
	tmp.y = pt_.y + a;

	return tmp;
}

Point operator + (const Point& a, const Point& b)
{
	Point pt = a;
	pt += b;
	return pt;
}

Point operator - (const Point& a, const Point& b)
{
	//return Point((a.x - b.x), (a.y - b.y));
	Point pt = a;
	pt -= b;
	return pt;
}

Point operator * (const Point& a, const Point& b)
{
	//return Point((a.x * b.x), (a.y * b.y));
	Point pt = a;
	pt *= b;
	return pt;
}

int test_operator_1()
{
	Point pt1;
	Point pt2(1, 2);
	Point pt0(pt2);

	Point pt3;
	pt3 = pt2; // =, same as pt3.operator=(pt2);
	CHECK(pt3.x == 1 && pt3.y == 2);

	Point pt4(3, 4);
	pt4 += pt3;
	CHECK(pt4.x == 4 && pt4.y == 6);

	pt4 -= pt2;
	CHECK(pt4.x == 3 && pt4.y == 4);

	pt4 *= pt2;
	CHECK(pt4.x == 3 && pt4.y == 8);

	pt4 = pt3 + pt2;
	CHECK(pt4.x == 2 && pt4.y == 4);

	pt4 += pt2;
	CHECK(pt4.x == 3 && pt4.y == 6);

	Point pt5(3, 6);
	bool flag = (pt4 == pt5);
	CHECK(flag == true);

	flag = (pt4 != pt5);
	CHECK(flag == false);

	flag = (pt4 > pt2);
	CHECK(flag == true);

	Point pt6(4, 5);
	std::cout << pt4 << std::endl; // output

	std::cin >> pt1; // input
	std::cout << pt1 << std::endl;

	Point pt7(4, 5);
	++pt7;
	CHECK(pt7.x == 5 && pt7.y == 6);

	Point pt8(6, 7);
	pt7 = pt8++;
	CHECK(pt7.x == 6 && pt7.y == 7);

	int a = 10;
	pt7 = pt7 + a;
	CHECK(pt7.x == 16 && pt7.y == 17);

	return 0;
}

} // namespace operator_
