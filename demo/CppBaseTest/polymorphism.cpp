#include "polymorphism.hpp"
#include <iostream>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52142629

///////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/doc/tutorial/polymorphism/
class Polygon {
protected:
	int width, height;
public:
	void set_values(int a, int b)
	{
		width = a; height = b;
	}
};

class Rectangle : public Polygon {
public:
	int area()
	{
		return width * height;
	}
};

class Triangle : public Polygon {
public:
	int area()
	{
		return (width * height / 2);
	}
};

int test_polymorphism1()
{
	Rectangle rect;
	Triangle trgl;
	Polygon poly;
	Polygon* ppoly1 = &rect;
	Polygon* ppoly2 = &trgl;

	ppoly1->set_values(4, 5);
	ppoly2->set_values(4, 5);

	std::cout << rect.area() << '\n';
	std::cout << trgl.area() << '\n';

	return 0;
}

////////////////////////////////////////////////////////////
// reference: http://www.tutorialspoint.com/cplusplus/cpp_polymorphism.htm
class Shape_2 {
protected:
	int width, height;
public:
	Shape_2(int a = 0, int b = 0)
	{
		width = a;
		height = b;
	}
	virtual int area()
	{
		std::cout << "Parent class area :" << std::endl;
		return 0;
	}
};

class Rectangle_2 : public Shape_2{
public:
	Rectangle_2(int a = 0, int b = 0) :Shape_2(a, b) { }
	int area()
	{
		std::cout << "Rectangle class area :" << std::endl;
		return (width * height);
	}
};

class Triangle_2 : public Shape_2{
public:
	Triangle_2(int a = 0, int b = 0) :Shape_2(a, b) { }
	int area()
	{
		std::cout << "Triangle class area :" << std::endl;
		return (width * height / 2);
	}
};

int test_polymorphism2()
{
	Shape_2 *shape;
	Rectangle_2 rec(10, 7);
	Triangle_2 tri(10, 5);

	// store the address of Rectangle
	shape = &rec;
	// call rectangle area.
	shape->area();

	// store the address of Triangle
	shape = &tri;
	// call triangle area.
	shape->area();

	return 0;
}

///////////////////////////////////////////////////////
// reference: http://www.learncpp.com/cpp-tutorial/122-virtual-functions/
class Animal
{
protected:
	std::string m_strName;

	// We're making this constructor protected because
	// we don't want people creating Animal objects directly,
	// but we still want derived classes to be able to use it.
	Animal(std::string strName) : m_strName(strName) {}

public:
	std::string GetName() { return m_strName; }
	virtual const char* Speak() { return "???"; }
};

class Cat : public Animal
{
public:
	Cat(std::string strName) : Animal(strName) {}

	virtual const char* Speak() { return "Meow"; }
};

class Dog : public Animal
{
public:
	Dog(std::string strName) : Animal(strName) {}

	virtual const char* Speak() { return "Woof"; }
};

static void Report(Animal &rAnimal)
{
	std::cout << rAnimal.GetName() << " says " << rAnimal.Speak() << std::endl;
}

int test_polymorphism3()
{
	Cat cCat("Fred");
	Dog cDog("Garbo");

	Report(cCat); // Fred says Meow
	Report(cDog); // Garbo says Woof

	Cat cFred("Fred"), cTyson("Tyson"), cZeke("Zeke");
	Dog cGarbo("Garbo"), cPooky("Pooky"), cTruffle("Truffle");

	// Set up an array of pointers to animals, and set those pointers to our Cat and Dog objects
	Animal *apcAnimals[] = { &cFred, &cGarbo, &cPooky, &cTruffle, &cTyson, &cZeke };
	for (int iii = 0; iii < 6; iii++)
		std::cout << apcAnimals[iii]->GetName() << " says " << apcAnimals[iii]->Speak() << std::endl;

	return 0;
}

//////////////////////////////////////////////////////////////
// reference: http://www.cprogramming.com/snippets/source-code/polymorphism-example
// abstract base class
class base
{
protected:  // attribute section
	int num1;
	int num2;
	int result;
public:  // behavior section
	void setVar(int n1, int n2)
	{
		num1 = n1;
		num2 = n2;
	}
	virtual void op() = 0;  // pure virtual function
	int getresult() { return result; }
};

class add : public base  // add class inherits from base class
{
public:
	void op() { result = num1 + num2; }
};

//sub class inherit base class
class sub : public base
{
public:
	void op() { result = num1 - num2; }
};

int test_polymorphism4()
{
	int x, y;
	base *m; //pointer variable declaration of type base class
	add ad;  //create object1 for addition process
	sub su;  //create object2 for subtraction process
	std::cout << "\nEnter two numbers seperated by space, or press Ctrl+z to Exit: ";

	while (std::cin >> x >> y) {
		m = &ad;
		m->setVar(x, y);
		m->op(); //addition process, even though call is on pointer to base!
		std::cout << "\nResult of summation = " << m->getresult();
		m = &su;
		m->setVar(x, y);
		m->op(); //subtraction process, even though call is on pointer to base!
		std::cout << "\nResult of subtraction = " << m->getresult() << std::endl << std::endl;
		std::cout << "\nEnter two numbers seperated by space or press Ctrl+z to Exit: ";
	}

	return 0;
}
