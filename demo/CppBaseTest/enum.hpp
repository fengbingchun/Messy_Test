#ifndef FBC_MESSY_TEST_ENUM_HPP_
#define FBC_MESSY_TEST_ENUM_HPP_

#include <iostream>
#include <string>

typedef short                   int16_t;

// reference: http://www.yolinux.com/TUTORIALS/C++Enum.html
class Day
{
public:
	enum Enum
	{
		sunday = 0,
		monday,
		tuesday,
		wednesday,
		thursday,
		friday,
		saturday,
		InvalidDay
	};

	// Constructors
	Day(void);
	Day(Enum ee);
	explicit Day(const std::string& ss);

	// Overloaded assignment operators
	Day& operator = (const Day& cc);
	Day& operator = (const std::string& ss);
	Day& operator = (Enum ee);

	// Overloaded comparison operators
	bool operator<  (const Day& cc) const;
	bool operator<  (Enum ee) const;
	bool operator<= (const Day& cc) const;
	bool operator<= (Enum ee) const;
	bool operator>  (const Day& cc) const;
	bool operator>  (Enum ee) const;
	bool operator>= (const Day& cc) const;
	bool operator>= (Enum ee) const;
	bool operator== (const Day& cc) const;
	bool operator== (const std::string& ss) const;
	bool operator== (const Enum ee) const;
	bool operator!= (const Day& cc) const;
	bool operator!= (const std::string& ss) const;
	bool operator!= (const Enum ee) const;

	// Accessor functions
	inline std::string getString(void) const;
	inline Enum        getEnum(void) const;
	inline int         getValue(void) const;

private:
	// Static functions
	static Enum        fromString(std::string ss);
	static std::string toString(Enum ee);
	static int         toValue(Enum ee);

	// Data members
	Enum        m_enum;
	std::string m_string;
	int         m_value;
};

inline std::ostream& operator<< (std::ostream& _os, const Day& _e)
{
	_os << _e.getString();
	return _os;
}

inline std::string Day::getString(void) const
{
	return m_string;
}

Day::Enum Day::getEnum(void) const
{
	return m_enum;
}

int Day::getValue(void) const
{
	return m_value;
}

int test_enum1();
int test_enum2();
int test_enum3();
int test_enum4();
int test_enum5();
int test_enum6();

#endif // FBC_MESSY_TEST_ENUM_HPP_
