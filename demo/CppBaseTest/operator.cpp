#include <assert.h>
#include "operator.hpp"
#include "universal.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/51292506

namespace operator_ {
/////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////
int test_operator_2()
{
	int i = -42;
	absInt absobj;
	int ui = absobj(i);
	fprintf(stdout, "ui = %d\n", ui); // 42

	return 0;
}

/////////////////////////////////////////////
int test_operator_3()
{
	const std::string s{ "http://blog.csdn.net/fengbingchun/" };

	PrintString printer;
	printer(s);

	PrintString errors(std::cerr, '\n');
	errors(s);

	return 0;
}

////////////////////////////////////////
std::ostream& operator << (std::ostream& out, const Fraction& f)
{
	return out << f.num() << '/' << f.den();
}

bool operator == (const Fraction& lhs, const Fraction& rhs)
{
	return lhs.num() == rhs.num() && lhs.den() == rhs.den();
}

bool operator != (const Fraction& lhs, const Fraction& rhs)
{
	return !(lhs == rhs);
}

Fraction operator * (Fraction lhs, const Fraction& rhs)
{
	return lhs *= rhs;
}

int test_operator_4()
{
	Fraction f1(3, 8), f2(1, 2), f3(10, 2);
	std::cout << f1 << " * " << f2 << " = " << f1 * f2 << '\n'
		<< f2 << " * " << f3 << " = " << f2 * f3 << '\n'
		<< 2 << " * " << f1 << " = " << 2 * f1 << '\n';

	//Fraction f(2, 5);
	//float val = f;
	//std::cout << val <<std::endl;

	return 0;
}

///////////////////////////////////////////////////////
// note: this function is not a member function!
Cents operator+(const Cents &c1, const Cents &c2)
{
	// use the Cents constructor and operator+(int, int)
	// we can access m_cents directly because this is a friend function
	return Cents(c1.m_cents + c2.m_cents);
}

int test_operator_5()
{
	Cents cents1(6);
	Cents cents2(8);
	Cents centsSum = cents1 + cents2;
	std::cout << "I have " << centsSum.getCents() << " cents." << std::endl;

	return 0;
}

/////////////////////////////////////////////////////
// Operator overloaded using a member function
Complex Complex::operator+(Complex &other)
{
	return Complex(re + other.re, im + other.im);
}

int test_operator_6()
{
	Complex a = Complex(1.2, 3.4);
	Complex b = Complex(5.6, 7.8);
	Complex c = Complex(0.0, 0.0);

	c = a + b;
	c.Display();

	return 0;
}

} // namespace operator_
