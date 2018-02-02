#include "abstract_class.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52142844

///////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/c8whxhf1.aspx
// Declare an abstract base class with a pure virtual destructor.
class base {
public:
	base() {}
	virtual ~base() = 0;
};

// Provide a definition for destructor.
base::~base() { fprintf(stderr, " base destructor "); }

class derived :public base {
public:
	derived() {}
	~derived(){ fprintf(stderr, " derived destructor "); }
};

int test_abstract_class1()
{
	derived *pDerived = new derived;
	// When the object pointed to by pDerived is deleted,
	// the destructor for class derived is called and then the destructor for class base is called.
	delete pDerived; // derived destructor base destructor

	return 0;
}

//////////////////////////////////////////////
// reference: http://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm
// Base class
class Shape_
{
public:
	// pure virtual function providing interface framework.
	virtual int getArea() = 0;
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

// Derived classes
class Rectangle : public Shape_
{
public:
	int getArea()
	{
		return (width * height);
	}
};
class Triangle : public Shape_
{
public:
	int getArea()
	{
		return (width * height) / 2;
	}
};

int test_abstract_class2()
{
	Rectangle Rect;
	Triangle  Tri;

	Rect.setWidth(5);
	Rect.setHeight(7);
	// Print the area of the object.
	std::cout << "Total Rectangle area: " << Rect.getArea() << std::endl;

	Tri.setWidth(5);
	Tri.setHeight(7);
	// Print the area of the object.
	std::cout << "Total Triangle area: " << Tri.getArea() << std::endl;

	return 0;
}

//////////////////////////////////////////////////
// reference: https://www.codingunit.com/cplusplus-tutorial-polymorphism-and-abstract-base-class
class CPolygon
{
protected:
	int width, height;
public:
	void setup(int first, int second)
	{
		width = first;
		height = second;
	}
	virtual int area() = 0;
};

class CRectangle : public CPolygon
{
public:
	int area(void)
	{
		return (width * height);
	}
};

class CTriangle : public CPolygon
{
public:
	int area(void)
	{
		return (width * height / 2);
	}
};

int test_abstract_class3()
{
	CRectangle rectangle;
	CTriangle triangle;

	CPolygon * ptr_polygon1 = &rectangle;
	CPolygon * ptr_polygon2 = &triangle;

	ptr_polygon1->setup(2, 2);
	ptr_polygon2->setup(2, 2);

	std::cout << ptr_polygon1->area() << std::endl;
	std::cout << ptr_polygon2->area() << std::endl;

	return 0;
}

//////////////////////////////////////////////////
// reference: https://www.codingunit.com/cplusplus-tutorial-polymorphism-and-abstract-base-class
class CPolygon_4
{
protected:
	int width, height;
public:
	void setup(int first, int second)
	{
		width = first;
		height = second;
	}
	virtual int area(void) = 0;
	void onscreen(void)
	{
		std::cout << this->area() << std::endl;
	}
};

class CRectangle_4 : public CPolygon_4
{
public:
	int area(void)
	{
		return (width * height);
	}
};

class CTriangle_4 : public CPolygon_4
{
public:
	int area(void)
	{
		return (width * height / 2);
	}
};

int test_abstract_class4()
{
	{
		CRectangle_4 rectangle;
		CTriangle_4 triangle;

		CPolygon_4 * ptr_polygon1 = &rectangle;
		CPolygon_4 * ptr_polygon2 = &triangle;

		ptr_polygon1->setup(2, 2);
		ptr_polygon2->setup(2, 2);

		ptr_polygon1->onscreen();
		ptr_polygon2->onscreen();
	}

	{
		CPolygon_4 * ptr_polygon1 = new CRectangle_4;
		CPolygon_4 * ptr_polygon2 = new CTriangle_4;

		ptr_polygon1->setup(2, 2);
		ptr_polygon2->setup(2, 2);

		ptr_polygon1->onscreen();
		ptr_polygon2->onscreen();

		delete ptr_polygon1;
		delete ptr_polygon2;
	}

	return 0;
}

////////////////////////////////////
// reference: http://www.thegeekstuff.com/2014/07/cpp-inheritance-abstract-class/
class CFigure
{
protected:
	double dSide;
public:
	CFigure(double a){ dSide = a; };
	virtual       ~CFigure(){};
	virtual double Surface(void)const = 0;
	virtual double Circumference(void)const = 0;
	virtual double Side(void)const = 0;
};

class CSquare : public CFigure
{
public:
	CSquare(double a) :CFigure(a){};
	~CSquare(){};
	double Surface(void)const{ return dSide*dSide; }
	double Circumference(void)const{ return 4.0*dSide; }
	double Side(void)const{ return dSide; }
};

int test_abstract_class5()
{
	CSquare Square_1(1);

	std::cout << "Surface="
		<< Square_1.Surface() << std::endl
		<< "Circumference="
		<< Square_1.Circumference() << std::endl;

	CFigure* ptrFigure = new CSquare(2);
	std::cout << "Surface="
		<< ptrFigure->Surface() << std::endl
		<< "Circumference="
		<< ptrFigure->Circumference() << std::endl;

	delete ptrFigure;

	return 0;
}

///////////////////////////////////////////
// reference: https://www.eduonix.com/blog/system-programming/learn-abstract-classes-virtual-functions-c/
class point
{
protected:
	float x, y;
public:
	point(float px, float py)
	{
		x = px; y = py;
	}
};

class shape				// Abstract Class
{
public:
	virtual float perimeter() = 0;	//pure virtual function
	virtual float area() = 0;	//another pure virtual function
};

/* The circle class will inherit from both point and shape */
class circle : public point, public shape
{
	float radius;
public:
	circle(float x, float y, float rad) : point(x, y)
	{
		radius = rad;
	}
	float getRadius()
	{
		return radius;
	}
	float perimeter()
	{
		return 2 * 3.14 * radius;
	}
	float area()
	{
		return 3.14 * radius * radius;
	}
};

int test_abstract_class6()
{
	circle c(5, -1, 4);
	std::cout << "\nFor a circle with radius = " << c.getRadius();
	std::cout << "\nPerimeter: " << c.perimeter();
	std::cout << "\nArea: " << c.area() << std::endl;

	return 0;
}
