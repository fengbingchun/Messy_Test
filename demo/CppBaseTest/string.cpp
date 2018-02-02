#include "string.hpp"
#include <string>
#include <iostream>
#include <cctype>
#include <cstddef> // std::size_t
#include <fstream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/62417284

/*
	typedef basic_string<char, char_traits<char>, allocator<char> >			string;
	typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >	wstring;
	typedef basic_string<char16_t, char_traits<char16_t>, allocator<char16_t> >	u16string;
	typedef basic_string<char32_t, char_traits<char32_t>, allocator<char32_t> >	u32string;
*/

int test_string_init()
{
	// 如果使用等号(=)初始化一个变量，实际上执行的是拷贝初始化，编译器把等号右侧的初始化拷贝到新创建的对象中去。
	// 与之相反，如果不使用等号，则执行的是直接初始化
	std::string s1; // 默认初始化，s1是一个空串
	std::string s2(s1); // s2是s1的副本
	std::string s3 = s1; // 等价于s3(s1)，s3是s1的副本
	std::string s4("value"); // s4是字面值"value"的副本，除了字面值最后的那个空字符外，直接初始化
	std::string s5 = "value"; // 等价于s5("value"),s5是字面值"value"的副本,拷贝初始化
	std::string s6(10, 'c'); // 把s6初始化为由连续10个字符c组成的串，直接初始化
	// 对于用多个值进行初始化的情况，非要用拷贝初始化的方式来处理也不是不可以，
	// 不过需要显示地创建一个(临时)对象用于拷贝
	std::string s7 = std::string(10, 'c'); // 拷贝初始化，等价于： std::string tmp(10, 'c'); std::string s7 = tmp;
	// string s(s2, pos2) : s是string s2从下标pos2开始的字符的拷贝，若pos2>s2.size()，构造函数的行为未定义
	std::string s8(s4, 2);
	// string s(cp, n) : s是cp指向的数组中前n个字符的拷贝，此数组至少应该包含n个字符
	char cp[6] {"abcde"};
	std::string s9(cp, 2);
	// string s(s2, pos2, len2) : s是string s2从下标pos2开始len2个字符的拷贝。若pos2>s2.size(),构造函数的行为未定义.
	// 不管len2的值是多少，构造函数至多拷贝s2.size()-pos2个字符
	std::string s10(s4, 1, 2);

	return 0;
}

int test_string_base()
{
	int num{ 0 };
	std::cin >> num;

	switch (num) {
	case 0: {
		// 读写string对象
		std::string s1;
		std::cin >> s1; // 将string对象读入s1,遇到空白停止, string对象会自动忽然开头的空白(即空格符、换行符、制表符等)
				// 并从第一个真正的字符开始读起，直到遇见下一个空白为止
		std::cout << s1 << std::endl; // 输出s1;

		std::string s2, s3;
		std::cin >> s2 >> s3; // 多个输入或多个输出可以连写在一起
		std::cout << s2 << s3 << std::endl;
	}
	break;
	case 1: {
		// 读取未知数量的string对象
		std::string s4;
		while (std::cin >> s4) { // 反复读取，直至到达文件末尾(ctrl+z)
			std::cout << s4 << std::endl; // 逐个输出单词，每个单词后面紧跟一个换行
		}
	}
	break;
	case 2: {
		// 使用getline读取一整行,getline只要一遇到换行符就结束读取操作并返回结果
		std::string s5;
		while (std::getline(std::cin, s5)) { // 按ctrl+z退出循环
			std::cout << s5 << std::endl; // 触发getline函数返回的那个换行符实际上被丢弃掉了，
						      // 得到的string对象中并不包含该换行符
		}
	}
	break;
	case 3: {
		// empty：是否为空返回一个对应的布尔值
		// 每次读入一整行，遇到空行直接跳过
		std::string s6;
		while (std::getline(std::cin, s6)) {
			if (!s6.empty())
				std::cout << s6 << std::endl;
			else
				std::cout << "it is empty" << std::endl;
		}
	}
	break;
	case 4: {
		// size： 返回string对象的长度(即string对象中字符的个数)
		std::string s7;
		while (std::getline(std::cin, s7)) {
			auto len = s7.size(); // size函数返回的是一个std::string::size_type类型的值，
					      // 它是一个无符号类型的值，而且能足够存放下任何string对象的大小,
			std::cout << "string size: " << len << std::endl;
		}
	}
	break;
	case 5: {
		// 比较string对象：大小写敏感：==、!=、<、<=、>、>=
		std::string s1{ "hello" }, s2{ "Hello" }, s3{"Hello world"};
		if (s1 > s2)
			std::cout << "s1 > s2" << std::endl;
		else if (s1 == s2)
			std::cout << "s1 == s2" << std::endl;
		else if (s1 < s2)
			std::cout << "s1 < s2" << std::endl;

		if (s2 <= s3)
			std::cout << "s2 <= s3" << std::endl;

	}
	break;
	case 6: {
		// +: 其内容是把左侧的运算对象与右侧的运算对象串接
		std::string s1{ "hello, " }, s2{ "world" }, s3;
		s3 = s1 + s2;
		std::cout << "s3: " << s3 << std::endl;

		// 当把string对象和字符字面值及字符串字面值混在一条语句中使用时，
		// 必须确保每个加法运算符(+)的两侧的对象至少有一个是string,
		// 不能把字面值直接相加
		// Note: 字符串字面值与string是不同的类型
		std::string s4{ "csdn blog" }, s5{ "http://blog.csdn.net/" }, s6;
		s6 = s4 + ": " + s5 + "fengbingchun";
		std::cout << s6 << std::endl;
	}
	break;
	case 7: {
		// substr: 返回一个string，它是原始string的一部分或全部的拷贝,
		// 可以传递给substr一个可选的开始位置和计数值
		std::string s{ "hello world" };
		std::string s2 = s.substr(0, 5); // s2 = hello
		std::string s3 = s.substr(6); // s3 = world
		std::string s4 = s.substr(6, 11); // s3 = world
		//std::string s5 = s.substr(12); // 抛出一个out_of_range异常
		fprintf(stderr, "s2: %s; s3: %s; s4: %s\n", s2.c_str(), s3.c_str(), s4.c_str());

		// insert、erase、assign
		s.insert(s.size(), 5, '!'); // 在s末尾插入5个感叹号
		fprintf(stdout, "s:  %s\n", s.c_str());
		s.erase(s.size() - 5, 5); // 从s删除最后5个字符
		fprintf(stdout, "s: %s\n", s.c_str());

		const char* cp = "Stately, plump Buck";
		s.assign(cp, 7); // s = "Stately"
		fprintf(stdout, "s: %s\n", s.c_str());
		s.insert(s.size(), cp + 7); // s = "Stately, plump Buck"
		fprintf(stdout, "s: %s\n", s.c_str());

		std::string s5{ " some string " }, s6{ " some other string " };
		s5.insert(0, s6); // 在s5中位置0之前插入s6的拷贝
		fprintf(stdout, "s5: %s\n", s5.c_str());
		s5.insert(0, s6, 0, s6.size()); // 在s5[0]之前插入s6中s6[0]开始的s6.size()个字符
		fprintf(stdout, "s5: %s\n", s5.c_str());

		// append: 是在末尾进行插入操作的一种简写形式
		std::string s7{ "C++ Primer" }, s8{ s7 };
		s7.insert(s7.size(), " 5th Ed.");
		s8.append(" 5th Ed.");
		fprintf(stdout, "s7: %s; s8: %s\n", s7.c_str(), s8.c_str());

		// replace: 是调用erase和insert的一种简写形式
		s7.replace(11, 3, "Fifth"); // s7.erase(11, 3); s7.insert(11, "Fifth");
		fprintf(stdout, "s7: %s\n", s7.c_str());

		/*
			s.find(args)：查找s中args第一次出现的位置
			s.rfind(args)：查找s中args最后一次出现的位置
			s.find_first_of(args)：在s中查找args中任何一个字符第一次出现的位置
			s.find_last_of(args)：在s中查找args中任何一个字符最后一次出现的位置
			s.find_first_not_of(args)：在s中查找第一个不在args中的字符
			s.find_last_not_of(args)：在s中查找最后一个不在args中的字符
		*/
		
		// find: 返回第一个匹配位置的下标
		std::string s9{ "AnnaBelle" };
		auto pos1 = s9.find("Belle");
		auto pos2 = s9.find("xxx");
		fprintf(stdout, "pos1: %d, pos2: %d\n", pos1, pos2); // 4, -1

		// find_first_of: 查找与给定字符串中任何一个字符匹配的位置
		std::string numbers{ "0123456789" }, name{ "r2d2" };
		auto pos3 = name.find_first_of(numbers);
		fprintf(stdout, "pos3: %d\n", pos3); // 1, name中第一个数字的下标

		// find_first_not_of: 第一个不在参数中的字符
		std::string s10{ "03714p3" };
		auto pos4 = s10.find_first_not_of(numbers);
		fprintf(stdout, "pos4: %d\n", pos4); // 5

		// compare: 返回0(等于)、正数(大于)或负数(小于)
		auto ret = numbers.compare(name);
		fprintf(stdout, "compare result: %d\n", ret);// -1

		// 数值数据与string之间的转换
		int i{ 43 };
		std::string s11 = std::to_string(i); // 将整数i转换为字符表示形式
		double d = std::stod(s11); // 将字符串s11转换为浮点数
		fprintf(stdout, "s11: %s, d: %f\n", s11.c_str(), d);

		/*
			to_string(val):一组重载函数，返回数值val的string表示。val可以是任何算术类型
			stoi(s,p,b)/stol(s,p,b)/stoul(s,p,b)/stoll(s,p,b)/stoull(s,p,b)：返回s的起始子串(表示整数内容)的数值，
				返回类型分别是int、long、unsigned long、long long、unsigned long long。b表示转换所用的基数，
				默认值为10.p是size_t指针，用来保存s中第一个非数值字符的下标，p默认是0，即，函数不保存下标。
			stof(s,p)/stod(s,p)/stold(s,p)：返回s的起始子串(表示浮点数内容)的数值，返回值类型分别是float、double或
				long double.参数p的作用与整数转换函数中一样。
		*/
	}
	break;
	default:
		break;
	}
	
	return 0;
}

int test_string_cctype()
{
	/* include <cctype>
		isalnum(c)：当c是字母或数字时为真
		isalpha(c)：当c是字母时为真
		isblank(c)：当c是空白字符时为真(C++11)
		iscntrl(c)：当c时控制字符时为真
		isdigit(c)：当c是数字时为真
		isgraph(c)：当c不是空格但可打印时为真
		islower(c)：当c是小写字母时为真
		isprint(c)：当c是可打印字符时为真(即c是空格或c具有可视形式)
		ispunct(c)：当c是标点符号时为真(即c不是控制字符、数字、字母、可打印空白中的一种)
		isspace(c)：当c是空白时为真(即c是空格、横向制表符、纵向制表符、回车符、换行符、进纸符中的一种)
		isupper(c)：当c是大写字母时为真
		isxdigit(c)：当c是十六进制数字时为真
		tolower(c)：如果c是大写字母，输出对应的小写字母；否则原样输出c
		toupper(c)：如果c是小写字母，输出对应的大写字母；否则原样输出c
	*/

	std::string s1{ "Hello World!!!" };

	decltype(s1.size()) punct_cnt{ 0 };
	for (auto c : s1) {
		if (ispunct(c))
			++punct_cnt;
	}
	std::cout << punct_cnt << " punctutation characters in " << s1 << std::endl;

	for (auto &c : s1) { // 对于s1中的每个字符(Note:c是引用)
		c = toupper(c); // c是一个引用，因此赋值语句将改变s中字符的值
	}
	std::cout << "toupper s1: " << s1 << std::endl;

	// string对象的下标必须大于等于0而小于s.size()
	// Note：C++标准并不要求标准库检测下标是否合法。一旦使用了一个超出范围的下标，就会产生不可预知的结果
	std::string s2{"some string"};
	for (decltype(s2.size()) index = 0; index != s2.size() && !isspace(s2[index]); ++index) {
		s2[index] = toupper(s2[index]);
	}
	std::cout << "s2: " << s2 << std::endl;

	// 使用下标执行随机访问
	const std::string s3{"0123456789ABCDEF"};
	std::cout << "Enter a series of numbers between 0 and 15"
		<< "separated by spaces. Hit ENTER when finished: " << std::endl;
	std::string result;
	std::string::size_type n;
	while (std::cin >> n) {
		if (n < s3.size())
			result += s3[n];

		std::cout << "Your hex number is: " << result << std::endl;
	}

	return 0;
}

static void SplitFilename(const std::string& str)
{
	std::cout << "Splitting: " << str << '\n';
	std::size_t found = str.find_last_of("/\\");
	std::cout << " path: " << str.substr(0, found) << '\n';
	std::cout << " file: " << str.substr(found + 1) << '\n';
}

int test_string_func()
{
	// reference: http://www.cplusplus.com/reference/string/string/

	{ // append
		std::string str;
		std::string str2 = "Writing ";
		std::string str3 = "print 10 and then 5 more";

		// used in the same order as described above:
		str.append(str2);                       // "Writing "
		str.append(str3, 6, 3);                   // "10 "
		str.append("dots are cool", 5);          // "dots "
		str.append("here: ");                   // "here: "
		str.append(10u, '.');                    // ".........."
		str.append(str3.begin() + 8, str3.end());  // " and then 5 more"
		str.append(5, 0x2E);                // "....."

		std::cout << str << '\n';
	}

	{ // assign
	std::string str;
	std::string base = "The quick brown fox jumps over a lazy dog.";

	// used in the same order as described above:
	str.assign(base);
	std::cout << str << '\n';

	str.assign(base, 10, 9);
	std::cout << str << '\n';         // "brown fox"

	str.assign("pangrams are cool", 7);
	std::cout << str << '\n';         // "pangram"

	str.assign("c-string");
	std::cout << str << '\n';         // "c-string"

	str.assign(10, '*');
	std::cout << str << '\n';         // "**********"

	str.assign(10, 0x2D);
	std::cout << str << '\n';         // "----------"

	str.assign(base.begin() + 16, base.end() - 12);
	std::cout << str << '\n';         // "fox jumps over"
}

	{ // at
		std::string str("Test string");
		for (unsigned i = 0; i<str.length(); ++i) {
			std::cout << str.at(i);
		}
		std::cout << '\n';
	}

	{ // back(c++11)
		std::string str("hello world.");
		str.back() = '!';
		std::cout << str << '\n';
	}

	{ // begin/end
		std::string str("Test string");
		for (std::string::iterator it = str.begin(); it != str.end(); ++it)
			std::cout << *it;
		std::cout << '\n';
	}

	{ // capacity
		std::string str("Test string");
		std::cout << "size: " << str.size() << "\n";
		std::cout << "length: " << str.length() << "\n";
		std::cout << "capacity: " << str.capacity() << "\n";
		std::cout << "max_size: " << str.max_size() << "\n";
	}

	{ // cbegin/cend(c++11)
		std::string str("Lorem ipsum");
		for (auto it = str.cbegin(); it != str.cend(); ++it)
			std::cout << *it;
		std::cout << '\n';
	}

	{ // clear
		char c;
		std::string str;
		std::cout << "Please type some lines of text. Enter a dot (.) to finish:\n";
		do {
			c = std::cin.get();
			str += c;
			if (c == '\n') {
				std::cout << str;
				str.clear();
			}
		} while (c != '.');
	}

	{ // compare
		std::string str1("green apple");
		std::string str2("red apple");

		if (str1.compare(str2) != 0)
			std::cout << str1 << " is not " << str2 << '\n';

		if (str1.compare(6, 5, "apple") == 0)
			std::cout << "still, " << str1 << " is an apple\n";

		if (str2.compare(str2.size() - 5, 5, "apple") == 0)
			std::cout << "and " << str2 << " is also an apple\n";

		if (str1.compare(6, 5, str2, 4, 5) == 0)
			std::cout << "therefore, both are apples\n";
	}

	{ // copy
		char buffer[20];
		std::string str("Test string...");
		std::size_t length = str.copy(buffer, 6, 5);
		buffer[length] = '\0';
		std::cout << "buffer contains: " << buffer << '\n';
	}

	{ // crbegin/crend(c++11)
		std::string str("lorem ipsum");
		for (auto rit = str.crbegin(); rit != str.crend(); ++rit)
			std::cout << *rit;
		std::cout << '\n';
	}

	{ // c_str
		std::string str("Please split this sentence into tokens");

		char * cstr = new char[str.length() + 1];
		std::strcpy(cstr, str.c_str());

		// cstr now contains a c-string copy of str
		char * p = std::strtok(cstr, " ");
		while (p != 0) {
			std::cout << p << '\n';
			p = std::strtok(NULL, " ");
		}

		delete[] cstr;
	}

	{ // data
		int length;

		std::string str = "Test string";
		char* cstr = "Test string";

		if (str.length() == std::strlen(cstr)) {
			std::cout << "str and cstr have the same length.\n";

			if (memcmp(cstr, str.data(), str.length()) == 0)
				std::cout << "str and cstr have the same content.\n";
		}
	}

	{ // empty
		std::string content;
		std::string line;
		std::cout << "Please introduce a text. Enter an empty line to finish:\n";
		do {
			getline(std::cin, line);
			content += line + '\n';
		} while (!line.empty());
		std::cout << "The text you introduced was:\n" << content;
	}

	{ // erase
		std::string str("This is an example sentence.");
		std::cout << str << '\n';
		// "This is an example sentence."
		str.erase(10, 8);                        //            ^^^^^^^^
		std::cout << str << '\n';
		// "This is an sentence."
		str.erase(str.begin() + 9);               //           ^
		std::cout << str << '\n';
		// "This is a sentence."
		str.erase(str.begin() + 5, str.end() - 9);  //       ^^^^^
		std::cout << str << '\n';
		// "This sentence."
	}

	{ // find
		std::string str("There are two needles in this haystack with needles.");
		std::string str2("needle");

		// different member versions of find in the same order as above:
		std::size_t found = str.find(str2);
		if (found != std::string::npos)
			std::cout << "first 'needle' found at: " << found << '\n';

		found = str.find("needles are small", found + 1, 6);
		if (found != std::string::npos)
			std::cout << "second 'needle' found at: " << found << '\n';

		found = str.find("haystack");
		if (found != std::string::npos)
			std::cout << "'haystack' also found at: " << found << '\n';

		found = str.find('.');
		if (found != std::string::npos)
			std::cout << "Period found at: " << found << '\n';

		// let's replace the first needle:
		str.replace(str.find(str2), str2.length(), "preposition");
		std::cout << str << '\n';
	}

	{ // find_first_not_of
		std::string str("look for non-alphabetic characters...");

		std::size_t found = str.find_first_not_of("abcdefghijklmnopqrstuvwxyz ");

		if (found != std::string::npos) {
			std::cout << "The first non-alphabetic character is " << str[found];
			std::cout << " at position " << found << '\n';
		}
	}

	{ // find_first_of
		std::string str("Please, replace the vowels in this sentence by asterisks.");
		std::size_t found = str.find_first_of("aeiou");
		while (found != std::string::npos) {
			str[found] = '*';
			found = str.find_first_of("aeiou", found + 1);
		}

		std::cout << str << '\n';
	}

	{ // find_last_not_of
		std::string str("Please, erase trailing white-spaces   \n");
		std::string whitespaces(" \t\f\v\n\r");

		std::size_t found = str.find_last_not_of(whitespaces);
		if (found != std::string::npos)
			str.erase(found + 1);
		else
			str.clear();            // str is all whitespace

		std::cout << '[' << str << "]\n";
	}

	{ // find_last_of
		std::string str1("/usr/bin/man");
		std::string str2("c:\\windows\\winhelp.exe");

		SplitFilename(str1);
		SplitFilename(str2);
	}

	{ // front(c++11)
		std::string str("test string");
		str.front() = 'T';
		std::cout << str << '\n';
	}

	{ // get_allocator
		// reference: http://www.tenouk.com/cpluscodesnippet/cplusbasic_stringget_allocator.html
		// using the default allocator
		std::string str1 = "1234";
		std::basic_string <char> str2 = "567ABC";
		std::basic_string <char, std::char_traits<char>, std::allocator<char> > str3 = "DefauLt";
		std::cout << "str1 = " << str1 << std::endl;
		std::cout << "str2 = " << str2 << std::endl;
		std::cout << "str3 = " << str3 << std::endl;

		// str4 will use the same allocator class as str1
		std::basic_string <char> str4(str1.get_allocator());
		std::basic_string <char>::allocator_type xchar = str1.get_allocator();
		str4 = "Just a string";
		std::cout << "str4 = " << str4 << std::endl;

		if (xchar == str1.get_allocator())
			std::cout << "The allocator objects xchar and str1.get_allocator() are equal." << std::endl;
		else
			std::cout << "The allocator objects xchar and str1.get_allocator() are not equal." << std::endl;

		// you can now call functions on the allocator class xchar used by str1
		std::string str5(xchar);
	}

	{ // insert
		std::string str = "to be question";
		std::string str2 = "the ";
		std::string str3 = "or not to be";
		std::string::iterator it;

		// used in the same order as described above:
		str.insert(6, str2);                 // to be (the )question
		str.insert(6, str3, 3, 4);             // to be (not )the question
		str.insert(10, "that is cool", 8);    // to be not (that is )the question
		str.insert(10, "to be ");            // to be not (to be )that is the question
		str.insert(15, 1, ':');               // to be not to be(:) that is the question
		it = str.insert(str.begin() + 5, ','); // to be(,) not to be: that is the question
		str.insert(str.end(), 3, '.');       // to be, not to be: that is the question(...)
		str.insert(it + 2, str3.begin(), str3.begin() + 3); // (or )

		std::cout << str << '\n';
	}

	{ // length
		std::string str("Test string");
		std::cout << "The size of str is " << str.length() << " bytes.\n";
	}

	{ // max_size
		std::string str("Test string");
		std::cout << "size: " << str.size() << "\n";
		std::cout << "length: " << str.length() << "\n";
		std::cout << "capacity: " << str.capacity() << "\n";
		std::cout << "max_size: " << str.max_size() << "\n";
	}

	{ // operator +=
		std::string name("John");
		std::string family("Smith");
		name += " K. ";         // c-string
		name += family;         // string
		name += '\n';           // character

		std::cout << name;
	}

	{ // operator =
		std::string str1, str2, str3;
		str1 = "Test string: ";   // c-string
		str2 = 'x';               // single character
		str3 = str1 + str2;       // string

		std::cout << str3 << '\n';
	}

	{ // operator []
		std::string str("Test string");
		for (int i = 0; i<str.length(); ++i) {
			std::cout << str[i];
		}
	}

	{ // pop_back(c++11)
		std::string str("hello world!");
		str.pop_back();
		std::cout << str << '\n';
	}

	{ // push_back
		std::string str;
		std::ifstream file("test.txt", std::ios::in);
		if (file) {
			while (!file.eof()) str.push_back(file.get());
		}
		std::cout << str << '\n';
	}

	{ // rbegin/rend
		std::string str("now step live...");
		for (std::string::reverse_iterator rit = str.rbegin(); rit != str.rend(); ++rit)
			std::cout << *rit;
	}

	{ // replace
		std::string base = "this is a test string.";
		std::string str2 = "n example";
		std::string str3 = "sample phrase";
		std::string str4 = "useful.";

		// replace signatures used in the same order as described above:

		// Using positions:                 0123456789*123456789*12345
		std::string str = base;           // "this is a test string."
		str.replace(9, 5, str2);          // "this is an example string." (1)
		str.replace(19, 6, str3, 7, 6);     // "this is an example phrase." (2)
		str.replace(8, 10, "just a");     // "this is just a phrase."     (3)
		str.replace(8, 6, "a shorty", 7);  // "this is a short phrase."    (4)
		str.replace(22, 1, 3, '!');        // "this is a short phrase!!!"  (5)

		// Using iterators:                                               0123456789*123456789*
		str.replace(str.begin(), str.end() - 3, str3);                    // "sample phrase!!!"      (1)
		str.replace(str.begin(), str.begin() + 6, "replace");             // "replace phrase!!!"     (3)
		str.replace(str.begin() + 8, str.begin() + 14, "is coolness", 7);    // "replace is cool!!!"    (4)
		str.replace(str.begin() + 12, str.end() - 4, 4, 'o');                // "replace is cooool!!!"  (5)
		str.replace(str.begin() + 11, str.end(), str4.begin(), str4.end());// "replace is useful."    (6)
		std::cout << str << '\n';
	}

	{ // reserve
		std::string str;

		std::ifstream file("test.txt", std::ios::in | std::ios::ate);
		if (file) {
			std::ifstream::streampos filesize = file.tellg();
			str.reserve(filesize);

			file.seekg(0);
			while (!file.eof()) {
				str += file.get();
			}
			std::cout << str;
		}
	}

	{ // resize
		std::string str("I like to code in C");
		std::cout << str << '\n';

		unsigned sz = str.size();

		str.resize(sz + 2, '+');
		std::cout << str << '\n';

		str.resize(14);
		std::cout << str << '\n';
	}

	{ // rfind
		std::string str("The sixth sick sheik's sixth sheep's sick.");
		std::string key("sixth");

		std::size_t found = str.rfind(key);
		if (found != std::string::npos)
			str.replace(found, key.length(), "seventh");

		std::cout << str << '\n';
	}

	{ // shrink_to_fit(c++11)
		std::string str(100, 'x');
		std::cout << "1. capacity of str: " << str.capacity() << '\n';

		str.resize(10);
		std::cout << "2. capacity of str: " << str.capacity() << '\n';

		str.shrink_to_fit();
		std::cout << "3. capacity of str: " << str.capacity() << '\n';
	}

	{ // size
		std::string str("Test string");
		std::cout << "The size of str is " << str.size() << " bytes.\n";
	}

	{ // substr
		std::string str = "We think in generalities, but we live in details.";
		// (quoting Alfred N. Whitehead)

		std::string str2 = str.substr(3, 5);     // "think"

		std::size_t pos = str.find("live");      // position of "live" in str

		std::string str3 = str.substr(pos);     // get from "live" to the end

		std::cout << str2 << ' ' << str3 << '\n';
	}

	{ // swap
		std::string buyer("money");
		std::string seller("goods");

		std::cout << "Before the swap, buyer has " << buyer;
		std::cout << " and seller has " << seller << '\n';

		seller.swap(buyer);

		std::cout << " After the swap, buyer has " << buyer;
		std::cout << " and seller has " << seller << '\n';
	}

	{ // npos
		/*
		std::string::npos : public static member constant
		static const size_t npos = -1;
		npos is a static member constant value with the greatest possible value for an element of type size_t.
		This constant is defined with a value of -1, which because size_t is an unsigned integral type,
		it is the largest possible representable value for this type.
		*/
	}

	{ // getline
		std::string name;

		std::cout << "Please, enter your full name: ";
		std::getline(std::cin, name);
		std::cout << "Hello, " << name << "!\n";
	}

	{ // operator +
		std::string firstlevel("com");
		std::string secondlevel("cplusplus");
		std::string scheme("http://");
		std::string hostname;
		std::string url;

		hostname = "www." + secondlevel + '.' + firstlevel;
		url = scheme + hostname;

		std::cout << url << '\n';
	}

	{ // operator <<
		std::string str = "Hello world!";
		std::cout << str << '\n';
	}

	{ // operator >>
		std::string name;

		std::cout << "Please, enter your name: ";
		std::cin >> name;
		std::cout << "Hello, " << name << "!\n";
	}

	{ // string comparisons
		std::string foo = "alpha";
		std::string bar = "beta";

		if (foo == bar) std::cout << "foo and bar are equal\n";
		if (foo != bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
		if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
	}

	{ // swap strings
		std::string buyer("money");
		std::string seller("goods");

		std::cout << "Before the swap, buyer has " << buyer;
		std::cout << " and seller has " << seller << '\n';

		swap(buyer, seller);

		std::cout << " After the swap, buyer has " << buyer;
		std::cout << " and seller has " << seller << '\n';
	}

	{ // stod(c++11)
		std::string orbits("365.24 29.53");
		std::string::size_type sz;     // alias of size_t

		double earth = std::stod(orbits, &sz);
		double moon = std::stod(orbits.substr(sz));
		std::cout << "The moon completes " << (earth / moon) << " orbits per Earth year.\n";
	}

	{ // stof(c++11)
		std::string orbits("686.97 365.24");
		std::string::size_type sz;     // alias of size_t

		float mars = std::stof(orbits, &sz);
		float earth = std::stof(orbits.substr(sz));
		std::cout << "One martian year takes " << (mars / earth) << " Earth years.\n";
	}

	{ // stoi(c++11)
		std::string str_dec = "2001, A Space Odyssey";
		std::string str_hex = "40c3";
		std::string str_bin = "-10010110001";
		std::string str_auto = "0x7f";

		std::string::size_type sz;   // alias of size_t

		int i_dec = std::stoi(str_dec, &sz);
		int i_hex = std::stoi(str_hex, nullptr, 16);
		int i_bin = std::stoi(str_bin, nullptr, 2);
		int i_auto = std::stoi(str_auto, nullptr, 0);

		std::cout << str_dec << ": " << i_dec << " and [" << str_dec.substr(sz) << "]\n";
		std::cout << str_hex << ": " << i_hex << '\n';
		std::cout << str_bin << ": " << i_bin << '\n';
		std::cout << str_auto << ": " << i_auto << '\n';
	}

	{ // stol(c++11)
		std::string str_dec = "1987520";
		std::string str_hex = "2f04e009";
		std::string str_bin = "-11101001100100111010";
		std::string str_auto = "0x7fffff";

		std::string::size_type sz;   // alias of size_t

		long li_dec = std::stol(str_dec, &sz);
		long li_hex = std::stol(str_hex, nullptr, 16);
		long li_bin = std::stol(str_bin, nullptr, 2);
		long li_auto = std::stol(str_auto, nullptr, 0);

		std::cout << str_dec << ": " << li_dec << '\n';
		std::cout << str_hex << ": " << li_hex << '\n';
		std::cout << str_bin << ": " << li_bin << '\n';
		std::cout << str_auto << ": " << li_auto << '\n';
	}

	{ // stold(c++11)
		std::string orbits("90613.305 365.24");
		std::string::size_type sz;     // alias of size_t

		long double pluto = std::stod(orbits, &sz);
		long double earth = std::stod(orbits.substr(sz));
		std::cout << "Pluto takes " << (pluto / earth) << " years to complete an orbit.\n";
	}

	{ // stoll(c++11)
		std::string str = "8246821 0xffff 020";

		std::string::size_type sz = 0;   // alias of size_t

		while (!str.empty()) {
			long long ll = std::stoll(str, &sz, 0);
			std::cout << str.substr(0, sz) << " interpreted as " << ll << '\n';
			str = str.substr(sz);
		}
	}

	{ // stoul(c++11)
		std::string str{ "1111" };
		//std::cout << "Enter an unsigned number: ";
		//std::getline(std::cin, str);
		unsigned long ul = std::stoul(str, nullptr, 0);
		std::cout << "You entered: " << ul << '\n';
	}

	{ // stoull(c++11)
		std::string str = "8246821 0xffff 020 -1";

		std::string::size_type sz = 0;   // alias of size_t

		while (!str.empty()) {
			unsigned long long ull = std::stoull(str, &sz, 0);
			std::cout << str.substr(0, sz) << " interpreted as " << ull << '\n';
			str = str.substr(sz);
		}
	}

	{ // to_string(c++11)
		/*
		string to_string (int val);
		string to_string (long val);
		string to_string (long long val);
		string to_string (unsigned val);
		string to_string (unsigned long val);
		string to_string (unsigned long long val);
		string to_string (float val);
		string to_string (double val);
		string to_string (long double val);
		*/

		std::string pi = "pi is " + std::to_string(3.1415926);
		std::string perfect = std::to_string(1 + 2 + 4 + 7 + 14) + " is a perfect number";
		std::cout << pi << '\n';
		std::cout << perfect << '\n';
	}

	{ // to_wstring(c++11)
		/*
		wstring to_wstring (int val);
		wstring to_wstring (long val);
		wstring to_wstring (long long val);
		wstring to_wstring (unsigned val);
		wstring to_wstring (unsigned long val);
		wstring to_wstring (unsigned long long val);
		wstring to_wstring (float val);
		wstring to_wstring (double val);
		wstring to_wstring (long double val);
		*/

		std::wstring pi = L"pi is " + std::to_wstring(3.1415926);
		std::wstring perfect = std::to_wstring(1 + 2 + 4 + 7 + 14) + L" is a perfect number";
		std::wcout << pi << L'\n';
		std::wcout << perfect << L'\n';
	}

	return 0;
}

int test_string_ifstream_to_string()
{
	// reference: http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
	std::ifstream file("E:/GitCode/Messy_Test/testdata/regex.txt");
	if (!file) {
		fprintf(stderr, "read file failed!\n");
		return -1;
	}

	std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	fprintf(stderr, "file content: \n%s\n", str.c_str());

	return 0;
}
