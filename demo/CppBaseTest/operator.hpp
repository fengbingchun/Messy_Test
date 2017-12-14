#ifndef FBC_MESSY_TEST_OPERATOR_HPP_
#define FBC_MESSY_TEST_OPERATOR_HPP_

#include <istream>
#include <ostream>
#include <iostream>
#include <string>

namespace operator_ {
/////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/f6s9k9ta.aspx
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

///////////////////////////////////////////////////////////
// 函数调用运算符 operator ()
struct absInt {
	int operator () (int val) const
	{
		return val < 0 ? -val : val;
	}
};

///////////////////////////////////////////////////////////
// 含有状态的函数对象类
class PrintString {
public:
	PrintString(std::ostream& o = std::cout, char c = ' ') : os(o), sep(c) {}
	void operator () (const std::string& s) const
	{
		os << s << sep;
	}

private:
	std::ostream& os;
	char sep;
};

//////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/operators
//           http://www.geeksforgeeks.org/operator-overloading-c/
class Fraction {
	int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
	int n, d;
public:
	Fraction(int n, int d = 1) : n(n / gcd(n, d)), d(d / gcd(n, d)) { }
	int num() const { return n; }
	int den() const { return d; }
	Fraction& operator *= (const Fraction& rhs)
	{
		int new_n = n * rhs.n / gcd(n * rhs.n, d * rhs.d);
		d = d * rhs.d / gcd(n * rhs.n, d * rhs.d);
		n = new_n;
		return *this;
	}

	// conversion operator: return float value of fraction
	//operator float() const {
	//	return float(n) / float(d);
	//}
};

/////////////////////////////////////////////////////////////
// reference: http://www.learncpp.com/cpp-tutorial/92-overloading-the-arithmetic-operators-using-friend-functions/
class Cents
{
private:
	int m_cents;

public:
	Cents(int cents) { m_cents = cents; }

	// add Cents + Cents using a friend function
	friend Cents operator+(const Cents &c1, const Cents &c2);

	int getCents() const { return m_cents; }
};

//////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/5tk49fh2.aspx
struct Complex {
	Complex(double r, double i) : re(r), im(i) {}
	Complex operator+(Complex &other);
	void Display() { std::cout << re << ", " << im << std::endl; }
private:
	double re, im;
};

////////////////////////////////////////////////
int test_operator_1();
int test_operator_2();
int test_operator_3();
int test_operator_4();
int test_operator_5();
int test_operator_6();

} // namespace operator_

#endif // FBC_MESSY_TEST_OPERATOR_HPP_
