#include "sstream.hpp"
#include <iostream>
#include <sstream> // ostringstream/istringstream/stringstream
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/69788873

// reference: http://www.cplusplus.com/reference/sstream/ostringstream/
int test_ostringstream()
{
	// ostringstream: Output stream class to operate on strings
	// 1. rdbuf: Returns a pointer to the internal stringbuf object
	std::ostringstream oss1;
	// using stringbuf directly
	std::stringbuf *pbuf = oss1.rdbuf();
	pbuf->sputn("Sample string", 13);
	std::cout << pbuf->str() << std::endl;

	// 2. str(): returns a string object with a copy of the current contents of the stream
	// str(const string& s):  sets s as the contents of the stream, discarding any previous contents.
	// The object preserves its open mode: if this includes ios_base::ate,
	// the writing position is moved to the end of the new sequence
	std::ostringstream oss2;
	oss2 << "One hundred and one: " << 101;
	std::string s1 = oss2.str();
	std::cout << s1 << '\n';

	// 3. swap: c++11, Exchanges all internal data between x and *this
	std::ostringstream foo;
	std::ostringstream bar;
	foo << 100;
	bar << 200;
	foo.swap(bar);
	std::cout << "foo: " << foo.str() << '\n';
	std::cout << "bar: " << bar.str() << '\n';

	// 4. swap: Exchanges the values of the ostringstream objects x and y
	std::ostringstream foo2;
	std::ostringstream bar2;
	foo2 << 100;
	bar2 << 200;
	std::swap(foo2, bar2); // unqualified (uses argument-dependent lookup)
	std::cout << "foo2: " << foo2.str() << '\n';
	std::cout << "bar2: " << bar2.str() << '\n';

	// 5. ostringstream constructor: Construct an object and optionally initialize its content
	// explicit ostringstream ( openmode which = ios_base::out );
	// explicit ostringstream ( const string & str, openmode which = ios_base::out );
	std::ostringstream foo3;                            // out
	std::ostringstream bar3(std::ostringstream::ate);  // out|ate
	foo3.str("Test string"); // str: sets s as the contents of the stream, discarding any previous contents
	bar3.str("Test string");
	foo3 << 101;
	bar3 << 101;
	std::cout << foo3.str() << '\n'; // 101t string
	std::cout << bar3.str() << '\n'; // Test string101

	std::string s{ "abcde" };
	std::ostringstream foo4(s); // 创建存储s的副本的ostringstream对象
	std::cout << "foo4: " << foo4.str() << std::endl;

	// reference: https://latedev.wordpress.com/2011/11/16/c-stringstreams/
	std::ostringstream os;
	os << "the ";
	os << "quick ";
	os << "brown ";
	os << "fox";
	std::string s2 = os.str();
	std::cout << s2 << std::endl;

	// double to string ==> c++11 to_string
	double d = 123.45;
	std::ostringstream os3;
	os3 << d;
	std::string s3 = "The value of d is " + os3.str();
	std::cout << s3 << std::endl;

	return 0;
}

// reference: http://www.cplusplus.com/reference/sstream/istringstream/
int test_istringstream()
{
	// istringstream: Input stream class to operate on strings
	// 1. istringstream constructor
	std::istringstream is("the quick brown fox");
	std::string s;
	while (is >> s) {
		std::cout << s << std::endl;
	}

	std::string stringvalues = "125 320 512 750 333";
	std::istringstream iss6(stringvalues);

	for (int n = 0; n<5; n++) {
		int val;
		// Elements in a character stream are considered to be separated by 'white space'
		// which is basically space, tab and newline characters
		iss6 >> val;
		std::cout << val * 2 << '\n';
	}

	// 2. rdbuf: Returns a pointer to the internal stringbuf object, with which the object was associated on construction
	std::istringstream iss;
	std::stringbuf *pbuf = iss.rdbuf();

	// using stringbuf directly:
	pbuf->str("Example string");

	int size = pbuf->in_avail();
	while (pbuf->in_avail()>0)
		std::cout << static_cast<char>(pbuf->sbumpc());
	std::cout << std::endl;

	// 3. str(): returns a string object with a copy of the current contents of the stream
	// str(const string& s): sets str as the contents of the stream, discarding any previous contents.
	// The object preserves its open mode: if this includes ios_base::ate,
	// the writing position is moved to the end of the new sequence
	std::istringstream iss2;
	std::string strvalues = "32 240 2 1450";
	iss2.str(strvalues);

	for (int n = 0; n<4; n++) {
		int val;
		// Elements in a character stream are considered to be separated by 'white space'
		// which is basically space, tab and newline characters
		iss2 >> val;
		std::cout << val << '\n';
	}
	std::cout << "Finished writing the numbers in: ";
	std::cout << iss2.str() << '\n';

	// 4. swap: c++11, Exchanges all internal data between x and *this.
	std::istringstream foo("100");
	std::istringstream bar("200");

	foo.swap(bar);

	int val;
	foo >> val; std::cout << "foo: " << val << '\n'; // 200
	bar >> val; std::cout << "bar: " << val << '\n'; // 100

	// 5. swap: Exchanges the values of the istringstream objects x and y
	std::istringstream foo2("100");
	std::istringstream bar2("200");

	swap(foo2, bar2);    // unqualified (uses argument-dependent lookup)
	int val2;
	foo2 >> val2; std::cout << "foo2: " << val2<< '\n'; // 200
	bar2 >> val2; std::cout << "bar2: " << val2 << '\n'; // 100

	return 0;
}

// reference: http://www.cplusplus.com/reference/sstream/stringstream/
int test_stringstream()
{
	// 1. stringstream: Stream class to operate on strings
	std::stringstream ss;
	ss << 100 << ' ' << 200;

	int foo, bar;
	ss >> foo >> bar;

	std::cout << "foo: " << foo << '\n'; // 100
	std::cout << "bar: " << bar << '\n'; // 200

	// 2. rdbuf: Returns a pointer to the internal stringbuf object, with which the object was associated on construction
	std::stringstream ss2;

	// using stringbuf directly:
	std::stringbuf *pbuf = ss2.rdbuf();
	pbuf->sputn("Example string", 13);

	char buffer[80];
	pbuf->sgetn(buffer, 80);

	std::cout << buffer << std::endl;

	// 3. str(): returns a string object with a copy of the current contents of the stream
	// str(const string& s): sets s as the contents of the stream, discarding any previous contents.
	// The object preserves its open mode: if this includes ios_base::ate,
	// the writing position is moved to the end of the new sequence
	std::stringstream ss3;
	ss3.str("Example string");
	std::string s3 = ss3.str();
	std::cout << s3 << '\n';

	// 4.1 swap: c++11, Exchanges all internal data between x and *this
	std::stringstream foo4;
	std::stringstream bar4;

	foo4 << 100;
	bar4 << 200;

	foo4.swap(bar4);
	int val;
	foo4 >> val; std::cout << "foo4: " << val << '\n'; // 200
	bar4 >> val; std::cout << "bar4: " << val << '\n'; // 100

	// 4.2 swap(stringstream): Exchanges the values of the stringstream objects x and y
	std::stringstream foo5;
	std::stringstream bar5;

	foo5 << 100;
	bar5 << 200;

	std::swap(foo5, bar5);
	int val5;
	foo5 >> val5; std::cout << "foo5: " << val5 << '\n'; // 200
	bar5 >> val5; std::cout << "bar5: " << val5 << '\n'; // 100

	return 0;
}
