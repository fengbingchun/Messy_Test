#include "struct.hpp"
#include <cstring>
#include <cstdlib>
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52072206

///////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/64973255.aspx
struct PERSON {   // Declare PERSON struct type
	int age;   // Declare member types
	long ss;
	float weight;
	char name[25];
} family_member;   // Define object of type PERSON

struct CELL {   // Declare CELL bit field
	unsigned short character : 8;  // 00000000 ????????
	unsigned short foreground : 3;  // 00000??? 00000000
	unsigned short intensity : 1;  // 0000?000 00000000
	unsigned short background : 3;  // 0???0000 00000000
	unsigned short blink : 1;  // ?0000000 00000000
} screen[25][80];       // Array of bit fields 

int test_struct1()
{
	struct PERSON sister;   // C style structure declaration
	PERSON brother;   // C++ style structure declaration
	sister.age = 13;   // assign values to members
	brother.age = 7;
	std::cout << "sister.age = " << sister.age << '\n';
	std::cout << "brother.age = " << brother.age << '\n';

	CELL my_cell;
	my_cell.character = 1;
	std::cout << "my_cell.character = " << my_cell.character<<'\n';

	return 0;
}

//////////////////////////////////////////////////////////
// reference: http://www.tutorialspoint.com/cplusplus/cpp_data_structures.htm
struct Books {
	char  title[50];
	char  author[50];
	char  subject[100];
	int   book_id;
};

void printBook(struct Books book)
{
	std::cout << "Book title : " << book.title << std::endl;
	std::cout << "Book author : " << book.author << std::endl;
	std::cout << "Book subject : " << book.subject << std::endl;
	std::cout << "Book id : " << book.book_id << std::endl;
}

int test_struct2()
{
	struct Books Book1;        // Declare Book1 of type Book
	struct Books Book2;        // Declare Book2 of type Book

	// book 1 specification
	strcpy(Book1.title, "Learn C++ Programming");
	strcpy(Book1.author, "Chand Miyan");
	strcpy(Book1.subject, "C++ Programming");
	Book1.book_id = 6495407;

	// book 2 specification
	strcpy(Book2.title, "Telecom Billing");
	strcpy(Book2.author, "Yakit Singha");
	strcpy(Book2.subject, "Telecom");
	Book2.book_id = 6495700;

	// Print Book1 info
	printBook(Book1);

	// Print Book2 info
	printBook(Book2);

	return 0;
}

///////////////////////////////////////////////////////////
// reference: http://www.dummies.com/how-to/content/how-to-build-a-structure-template-in-c.html
template<typename T>
struct Volume {
	T height;
	T width;
	T length;

	Volume()
	{
		height = 0;
		width = 0;
		length = 0;
	}

	T getvolume()
	{
		return height * width * length;
	}

	T getvolume(T H, T W, T L)
	{
		height = H;
		width = W;
		length = L;
		return height * width * length;
	}
};

int test_struct3()
{
	Volume<int> first;
	std::cout << "First volume: " << first.getvolume() << std::endl;
	first.height = 2;
	first.width = 3;
	first.length = 4;
	std::cout << "First volume: " << first.getvolume() << std::endl;

	Volume<double> second;
	std::cout << "Second volume: " << second.getvolume(2.1, 3.2, 4.3) << std::endl;
	std::cout << "Height: " << second.height << std::endl;
	std::cout << "Width: " << second.width << std::endl;
	std::cout << "Length: " << second.length << std::endl;

	return 0;
}

///////////////////////////////////////////////////////
// reference: http://www.java2s.com/Code/Cpp/Class/Constructoranddestructorinsideastruct.htm
struct StringClass
{
	StringClass(char *ptr);
	~StringClass();
	void show();
private:
	char *p;
	int len;
};

StringClass::StringClass(char *ptr)
{
	len = strlen(ptr);
	p = (char *)malloc(len + 1);
	if (!p) {
		std::cout << "Allocation error\n";
		exit(1);
	}
	strcpy(p, ptr);
}

StringClass::~StringClass()
{
	std::cout << "Freeing p\n";
	free(p);
}

void StringClass::show()
{
	std::cout << p << " - length: " << len;
	std::cout << std::endl;
}

int test_struct4()
{
	StringClass stringObject1("www.java2s_1.com."), stringObject2("www.java2s_2.com.");

	stringObject1.show();
	stringObject2.show();

	return 0;
}
