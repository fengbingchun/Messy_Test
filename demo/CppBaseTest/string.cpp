#include "string.hpp"
#include <string>
#include <iostream>
#include <cctype>

/*
	typedef basic_string<char, char_traits<char>, allocator<char> >			string;
	typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >	wstring;
	typedef basic_string<char16_t, char_traits<char16_t>, allocator<char16_t> >	u16string;
	typedef basic_string<char32_t, char_traits<char32_t>, allocator<char32_t> >	u32string;
*/

// reference: http://www.cplusplus.com/reference/string/string/
int test_string_func()
{
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

	{ // back
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

	{ // cbegin/cend
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

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	return 0;
}

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


