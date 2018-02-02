#include "enum_class.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78535754

namespace enum_class_ {

typedef short int16_t;

////////////////////////////////////////////////////////////////////
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

//enumeration types (both scoped and unscoped) can have overloaded operators
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

int test_enum_class_1()
{
	color col = red;
	altitude a;
	a = altitude::low;

	std::cout << "col = " << col << '\n'
		<< "a = " << a << '\n'
		<< "f = " << f << '\n';

	return 0;
}

////////////////////////////////////////////////////////////////////////
// reference: https://stackoverflow.com/questions/18335861/why-is-enum-class-preferred-over-plain-enum
// C++ has two kinds of enum: enum classes, Plain enums
enum Color { red1, green1, blue1 };                    // plain enum
enum Card { red_card, green_card, yellow_card };    // another plain enum
enum class Animal { dog, deer, cat, bird, human };  // enum class
enum class Mammal { kangaroo, deer, human };        // another enum class

int test_enum_class_2()
{
	// examples of bad use of plain enums:
	Color color = Color::red1;
	Card card = Card::green_card;

	int num = color;    // no problem

	if (color == Card::red_card) // no problem (bad)
		std::cout << "bad" << std::endl;

	if (card == Color::green1)   // no problem (bad)
		std::cout << "bad" << std::endl;

	// examples of good use of enum classes (safe)
	Animal a = Animal::deer;
	Mammal m = Mammal::deer;

	//int num2 = a;   // error
	//if (m == a)     // error (good)
	//	std::cout << "bad" << std::endl;

	//if (a == Mammal::deer) // error (good)
	//	std::cout << "bad" << std::endl;

	return 0;
}

////////////////////////////////////////////////////////
// reference: http://www.learncpp.com/cpp-tutorial/4-5a-enum-classes/
int test_enum_class_3()
{
	enum class Color { // "enum class" defines this as an scoped enumeration instead of a standard enumeration
		RED, // RED is inside the scope of Color
		BLUE
	};

	enum class Fruit {
		BANANA, // BANANA is inside the scope of Fruit
		APPLE
	};

	Color color = Color::RED; // note: RED is not directly accessible any more, we have to use Color::RED
	Fruit fruit = Fruit::BANANA; // note: BANANA is not directly accessible any more, we have to use Fruit::BANANA

	//if (color == fruit) // compile error here, as the compiler doesn't know how to compare different types Color and Fruit
	//	std::cout << "color and fruit are equal\n";
	//else
	//	std::cout << "color and fruit are not equal\n";

	if (color == Color::RED) // this is okay
		std::cout << "The color is red!\n";
	else if (color == Color::BLUE)
		std::cout << "The color is blue!\n";

	//std::cout << color; // won't work, because there's no implicit conversion to int
	color = Color::BLUE;
	std::cout << static_cast<int>(color) << std::endl; // will print 1

	return 0;
}

} // namespace enum_class_

