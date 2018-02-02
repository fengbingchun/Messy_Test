#include "this_pointer.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/51228177

Buf::Buf(char* szBuffer, size_t sizeOfBuffer)
{
	sizeOfBuffer++; // account for a NULL terminator

	buffer = new char[sizeOfBuffer];
	if (buffer)
	{
		strcpy_s(buffer, sizeOfBuffer, szBuffer);
		sizeOfBuffer = sizeOfBuffer;
	}
}

Buf& Buf::operator=(const Buf &otherbuf)
{
	if (&otherbuf != this) {
		if (buffer)
			delete[] buffer;

		sizeOfBuffer = strlen(otherbuf.buffer) + 1;
		buffer = new char[sizeOfBuffer];
		strcpy_s(buffer, sizeOfBuffer, otherbuf.buffer);
	}
	return *this;
}

void Buf::Display()
{
	std::cout << buffer << std::endl;
}

void test_this_pointer1()
{
	Box Box1(3.3, 1.2, 1.5);    // Declare box1
	Box Box2(8.5, 6.0, 2.0);    // Declare box2

	if (Box1.compare(Box2)) {
		std::cout << "Box2 is smaller than Box1" << std::endl;
	} else {
		std::cout << "Box2 is equal to or larger than Box1" << std::endl;
	}
}

void test_this_pointer2()
{
	Buf myBuf("my buffer", 10);
	Buf yourBuf("your buffer", 12);

	// Display 'my buffer'
	myBuf.Display();

	// assignment opperator
	myBuf = yourBuf;

	// Display 'your buffer'
	myBuf.Display();
}

