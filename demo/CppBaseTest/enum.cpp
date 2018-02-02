#include "enum.hpp"

#include <iostream>
#include <string>
#include <algorithm>

// Blog: http://blog.csdn.net/fengbingchun/article/details/51778977

/////////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/enum
// enum that takes 16 bits
enum smallenum : int16_t {
	a,
	b,
	c
};


// color may be red (value 0), yellow (value 1), green (value 20), or blue (value 21)
enum color {
	red,
	yellow,
	green = 20,
	blue
};

// altitude may be altitude::high or altitude::low
enum class altitude : char {
	high = 'h',
	low = 'l', // C++11 allows the extra comma
};

// the constant d is 0, the constant e is 1, the constant f is 3
enum {
	d,
	e,
	f = e + 2
};

// enumeration types (both scoped and unscoped) can have overloaded operators
std::ostream& operator << (std::ostream& os, color c)
{
	switch (c) {
		case red: os << "red";    break;
		case yellow: os << "yellow"; break;
		case green: os << "green";  break;
		case blue: os << "blue";   break;
		default: os.setstate(std::ios_base::failbit);
	}

	return os;
}

std::ostream& operator << (std::ostream& os, altitude al)
{
	return os << static_cast<char>(al);
}

int test_enum1()
{
	color col = red;
	altitude a;
	a = altitude::low;

	std::cout << "col = " << col << '\n' // col = red
		<< "a = " << a << '\n' // a = 1
		<< "f = " << f << '\n'; // f = 3

	return 0;
}

/////////////////////////////////////////////////////////
// reference: http://www.learncpp.com/cpp-tutorial/45-enumerated-types/
enum ItemType
{
	ITEMTYPE_SWORD,
	ITEMTYPE_TORCH,
	ITEMTYPE_POTION
};

std::string getItemName(ItemType itemType)
{
	if (itemType == ITEMTYPE_SWORD)
		return std::string("Sword");
	if (itemType == ITEMTYPE_TORCH)
		return std::string("Torch");
	if (itemType == ITEMTYPE_POTION)
		return std::string("Potion");
}

int test_enum2()
{
	// ItemType is the enumerated type we've declared above.
	// itemType (lower case i) is the name of the variable we're defining (of type ItemType).
	// ITEMTYPE_TORCH is the enumerated value we're initializing variable itemType with.
	ItemType itemType(ITEMTYPE_TORCH);

	std::cout << "You are carrying a " << getItemName(itemType) << "\n"; // You are carrying a Torch

	return 0;
}

////////////////////////////////////////////////////////////////////////////
// reference: http://www.yolinux.com/TUTORIALS/C++Enum.html
int test_enum3()
{
	enum {
		monday, tuesday, wednesday, thursday, friday, saturday, sunday
	} day;

	day = wednesday;

	if (day == saturday || day == sunday)
		std::cout << "Day is a weekend day" << std::endl;
	else if (day == wednesday)
		std::cout << "Day is hump day - middle of the work week" << std::endl; // Day is hump day - middle of the work week

	return 0;
}

//////////////////////////////////////////////////////////////////////////
int test_enum4()
{
	typedef enum DAY_{
		saturday = 0,
		sunday = 0,
		monday,
		tuesday,
		wednesday,
		thursday,
		friday
	} DAY;

	DAY day_ = sunday;

	if (day_ == 0)
		std::cout << "Day is a weekend day" << std::endl; // Day is a weekend day
	else if (day_ == wednesday)
		std::cout << "Day is hump day - middle of the work week" << std::endl;

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// Constructors
Day::Day(void) : m_enum(sunday), m_string("Sunday"), m_value(0)
{}

Day::Day(Enum _e) : m_enum(_e), m_string(toString(_e)), m_value(0)
{}

Day::Day(const std::string& _s) : m_enum(fromString(_s)), m_string(_s), m_value(toValue(m_enum))
{}

// Assignment operators
Day& Day::operator= (const Day& _c)
{
	m_string = _c.m_string;
	m_enum = _c.m_enum;
	m_value = _c.m_value;
	return *this;
}

Day& Day::operator= (const std::string& _s)
{
	m_string = _s;
	m_enum = fromString(_s);
	m_value = toValue(m_enum);
	return *this;
}

Day& Day::operator= (Enum _e)
{
	m_enum = _e;
	m_string = toString(_e);
	m_value = toValue(_e);
	return *this;
}

bool Day::operator< (const Day& _c) const
{
	return (m_value < _c.m_value);
}

bool Day::operator< (Enum _e) const
{
	return (m_value < toValue(_e));
}

bool Day::operator<= (const Day& _c) const
{
	return (m_value <= _c.m_value);
}

bool Day::operator<= (Enum _e) const
{
	return (m_value <= toValue(_e));
}

bool Day::operator> (const Day& _c) const
{
	return (m_value > _c.m_value);
}

bool Day::operator> (Enum _e) const
{
	return (m_value > toValue(_e));
}

bool Day::operator>= (const Day& _c) const
{
	return (m_value >= _c.m_value);
}

bool Day::operator>= (Enum _e) const
{
	return (m_value >= toValue(_e));
}

bool Day::operator== (const Day& _c) const
{
	return (m_enum == _c.m_enum);
}

bool Day::operator== (const std::string& _s) const
{
	return (m_string == _s);
}

bool Day::operator== (const Enum _e) const
{
	return (m_enum == _e);
}

bool Day::operator!= (const Day& _c) const
{
	return (m_enum != _c.m_enum);
}

bool Day::operator!= (const std::string& _s) const
{
	return (m_string != _s);
}

bool Day::operator!= (const Enum _e) const
{
	return (m_enum != _e);
}

Day::Enum Day::fromString(std::string _s)
{
	// Case insensitive - make all upper case
	transform(_s.begin(), _s.end(), _s.begin(), toupper);
	if (_s == "SUNDAY")         return sunday;
	else if (_s == "MONDAY")    return monday;
	else if (_s == "TUESDAY")   return tuesday;
	else if (_s == "WEDNESDAY") return wednesday;
	else if (_s == "THURSDAY")  return thursday;
	else if (_s == "FRIDAY")    return friday;
	else if (_s == "SATURDAY")  return saturday;

	throw std::range_error("Not a valid Day value: " + _s);
	return InvalidDay;
};

std::string Day::toString(Day::Enum _e)
{
	switch (_e) {
		case sunday:    { return "SUNDAY";    }
		case monday:    { return "MONDAY";    }
		case tuesday:   { return "TUESDAY";   }
		case wednesday: { return "WEDNESDAY"; }
		case thursday:  { return "THURSDAY";  }
		case friday:    { return "FRIDAY";    }
		case saturday:  { return "SATURDAY";  }
	}
	return "InvalidDay";
}

int Day::toValue(Day::Enum _e)
{
	switch (_e) {
		case sunday:    { return 0; }
		case monday:    { return 2; }
		case tuesday:   { return 3; }
		case wednesday: { return 4; }
		case thursday:  { return 5; }
		case friday:    { return 6; }
		case saturday:  { return 7; }
	}
	return 8;  // Invalid
}

int test_enum5()
{
	Day day;

	day = "Saturday";

	if (day == Day::saturday || day == Day::sunday)
		std::cout << "Day is a weekend day" << std::endl; // Day is a weekend day

	return 0;
}

/////////////////////////////////////////////////////////////
int test_enum6()
{
	typedef enum {
		monday, tuesday, wednesday, thursday, friday, saturday, sunday
	} Day;

	const char *day_str[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

	Day day = saturday;

	if (day == saturday || day == sunday)
		std::cout << day_str[day] << std::endl; // Saturday

	return 0;
}
