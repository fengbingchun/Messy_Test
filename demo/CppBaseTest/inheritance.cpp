#include "inheritance.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52079305

///////////////////////////////////////////////
// reference: http://www.tutorialspoint.com/cplusplus/cpp_inheritance.htm
// Base class
class Shape
{
public:
	void setWidth(int w)
	{
		width = w;
	}
	void setHeight(int h)
	{
		height = h;
	}
protected:
	int width;
	int height;
};

// Derived class
class Rectangle : public Shape
{
public:
	int getArea()
	{
		return (width * height);
	}
};

int test_inheritance1()
{
	Rectangle Rect;

	Rect.setWidth(5);
	Rect.setHeight(7);

	// Print the area of the object.
	std::cout << "Total area: " << Rect.getArea() << std::endl;

	return 0;
}

///////////////////////////////////////////////////////////
// reference: http://www.tutorialspoint.com/cplusplus/cpp_inheritance.htm
// Base class PaintCost
class PaintCost
{
public:
	int getCost(int area)
	{
		return area * 70;
	}
};

// Derived class
class Rectangle_2 : public Shape, public PaintCost
{
public:
	int getArea()
	{
		return (width * height);
	}
};

int test_inheritance2()
{
	Rectangle_2 Rect;
	int area;

	Rect.setWidth(5);
	Rect.setHeight(7);

	area = Rect.getArea();

	// Print the area of the object.
	std::cout << "Total area: " << Rect.getArea() << std::endl;

	// Print the total cost of painting
	std::cout << "Total paint cost: $" << Rect.getCost(area) << std::endl;

	return 0;
}

/////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/doc/tutorial/inheritance/
class Mother {
public:
	Mother()
	{
		std::cout << "Mother: no parameters\n";
	}
	Mother(int a)
	{
		std::cout << "Mother: int parameter\n";
	}
};

class Daughter : public Mother {
public:
	Daughter(int a)
	{
		std::cout << "Daughter: int parameter\n\n";
	}
};

class Son : public Mother {
public:
	Son(int a) : Mother(a)
	{
		std::cout << "Son: int parameter\n\n";
	}
};

int test_inheritance3()
{
	/* print: Mother: no parameters
		  Daughter: int parameters
	*/
	Daughter kelly(0);

	/* print: Mother: int parameters
		  Son: int parameters
	*/
	Son bud(0);

	return 0;
}

//////////////////////////////////////////
// reference: http://www.dev-hq.net/c++/16--inheritance-and-friends
class Fish
{
protected:
	int speed;
public:
	Fish() : speed(0) {}
	void speed_up() { speed += 10; }
	void slow_down() { speed -= 10; }
	void output() const { std::cout << speed << std::endl; }
};

class Cod : public Fish
{
public:
	Cod() { speed = 10; } //Cods start with a speed of 10
	void speed_up() { speed += 20; } //Overwrite base 'speed_up' member function
};

int test_inheritance4()
{
	Cod bob; //A new "Cod"
	bob.speed_up();
	bob.output(); // 10

	Fish freddie; //A new "Fish" (not a "Cod"!)
	freddie.speed_up();
	freddie.output(); // 30

	return 0;
}
