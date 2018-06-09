#include "string.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstddef> // std::size_t
#include <fstream>
#include <cstring>

// Blog: http://blog.csdn.net/fengbingchun/article/details/62417284

/*
	typedef basic_string<char, char_traits<char>, allocator<char> >			string;
	typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >	wstring;
	typedef basic_string<char16_t, char_traits<char16_t>, allocator<char16_t> >	u16string;
	typedef basic_string<char32_t, char_traits<char32_t>, allocator<char32_t> >	u32string;
*/

int test_string_init()
{
	// ���ʹ�õȺ�(=)��ʼ��һ��������ʵ����ִ�е��ǿ�����ʼ�����������ѵȺ��Ҳ�ĳ�ʼ���������´����Ķ�����ȥ��
	// ��֮�෴�������ʹ�õȺţ���ִ�е���ֱ�ӳ�ʼ��
	std::string s1; // Ĭ�ϳ�ʼ����s1��һ���մ�
	std::string s2(s1); // s2��s1�ĸ���
	std::string s3 = s1; // �ȼ���s3(s1)��s3��s1�ĸ���
	std::string s4("value"); // s4������ֵ"value"�ĸ�������������ֵ�����Ǹ����ַ��⣬ֱ�ӳ�ʼ��
	std::string s5 = "value"; // �ȼ���s5("value"),s5������ֵ"value"�ĸ���,������ʼ��
	std::string s6(10, 'c'); // ��s6��ʼ��Ϊ������10���ַ�c��ɵĴ���ֱ�ӳ�ʼ��
	// �����ö��ֵ���г�ʼ�����������Ҫ�ÿ�����ʼ���ķ�ʽ������Ҳ���ǲ����ԣ�
	// ������Ҫ��ʾ�ش���һ��(��ʱ)�������ڿ���
	std::string s7 = std::string(10, 'c'); // ������ʼ�����ȼ��ڣ� std::string tmp(10, 'c'); std::string s7 = tmp;
	// string s(s2, pos2) : s��string s2���±�pos2��ʼ���ַ��Ŀ�������pos2>s2.size()�����캯������Ϊδ����
	std::string s8(s4, 2);
	// string s(cp, n) : s��cpָ���������ǰn���ַ��Ŀ���������������Ӧ�ð���n���ַ�
	char cp[6] {"abcde"};
	std::string s9(cp, 2);
	// string s(s2, pos2, len2) : s��string s2���±�pos2��ʼlen2���ַ��Ŀ�������pos2>s2.size(),���캯������Ϊδ����.
	// ����len2��ֵ�Ƕ��٣����캯�����࿽��s2.size()-pos2���ַ�
	std::string s10(s4, 1, 2);

	return 0;
}

int test_string_base()
{
	int num{ 0 };
	std::cin >> num;

	switch (num) {
	case 0: {
		// ��дstring����
		std::string s1;
		std::cin >> s1; // ��string�������s1,�����հ�ֹͣ, string������Զ���Ȼ��ͷ�Ŀհ�(���ո�������з����Ʊ����)
				// ���ӵ�һ���������ַ���ʼ����ֱ��������һ���հ�Ϊֹ
		std::cout << s1 << std::endl; // ���s1;

		std::string s2, s3;
		std::cin >> s2 >> s3; // �������������������д��һ��
		std::cout << s2 << s3 << std::endl;
	}
	break;
	case 1: {
		// ��ȡδ֪������string����
		std::string s4;
		while (std::cin >> s4) { // ������ȡ��ֱ�������ļ�ĩβ(ctrl+z)
			std::cout << s4 << std::endl; // ���������ʣ�ÿ�����ʺ�����һ������
		}
	}
	break;
	case 2: {
		// ʹ��getline��ȡһ����,getlineֻҪһ�������з��ͽ�����ȡ���������ؽ��
		std::string s5;
		while (std::getline(std::cin, s5)) { // ��ctrl+z�˳�ѭ��
			std::cout << s5 << std::endl; // ����getline�������ص��Ǹ����з�ʵ���ϱ��������ˣ�
						      // �õ���string�����в��������û��з�
		}
	}
	break;
	case 3: {
		// empty���Ƿ�Ϊ�շ���һ����Ӧ�Ĳ���ֵ
		// ÿ�ζ���һ���У���������ֱ������
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
		// size�� ����string����ĳ���(��string�������ַ��ĸ���)
		std::string s7;
		while (std::getline(std::cin, s7)) {
			auto len = s7.size(); // size�������ص���һ��std::string::size_type���͵�ֵ��
					      // ����һ���޷������͵�ֵ���������㹻������κ�string����Ĵ�С,
			std::cout << "string size: " << len << std::endl;
		}
	}
	break;
	case 5: {
		// �Ƚ�string���󣺴�Сд��У�==��!=��<��<=��>��>=
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
		// +: �������ǰ���������������Ҳ��������󴮽�
		std::string s1{ "hello, " }, s2{ "world" }, s3;
		s3 = s1 + s2;
		std::cout << "s3: " << s3 << std::endl;

		// ����string������ַ�����ֵ���ַ�������ֵ����һ�������ʹ��ʱ��
		// ����ȷ��ÿ���ӷ������(+)������Ķ���������һ����string,
		// ���ܰ�����ֱֵ�����
		// Note: �ַ�������ֵ��string�ǲ�ͬ������
		std::string s4{ "csdn blog" }, s5{ "http://blog.csdn.net/" }, s6;
		s6 = s4 + ": " + s5 + "fengbingchun";
		std::cout << s6 << std::endl;
	}
	break;
	case 7: {
		// substr: ����һ��string������ԭʼstring��һ���ֻ�ȫ���Ŀ���,
		// ���Դ��ݸ�substrһ����ѡ�Ŀ�ʼλ�úͼ���ֵ
		std::string s{ "hello world" };
		std::string s2 = s.substr(0, 5); // s2 = hello
		std::string s3 = s.substr(6); // s3 = world
		std::string s4 = s.substr(6, 11); // s3 = world
		//std::string s5 = s.substr(12); // �׳�һ��out_of_range�쳣
		fprintf(stderr, "s2: %s; s3: %s; s4: %s\n", s2.c_str(), s3.c_str(), s4.c_str());

		// insert��erase��assign
		s.insert(s.size(), 5, '!'); // ��sĩβ����5����̾��
		fprintf(stdout, "s:  %s\n", s.c_str());
		s.erase(s.size() - 5, 5); // ��sɾ�����5���ַ�
		fprintf(stdout, "s: %s\n", s.c_str());

		const char* cp = "Stately, plump Buck";
		s.assign(cp, 7); // s = "Stately"
		fprintf(stdout, "s: %s\n", s.c_str());
		s.insert(s.size(), cp + 7); // s = "Stately, plump Buck"
		fprintf(stdout, "s: %s\n", s.c_str());

		std::string s5{ " some string " }, s6{ " some other string " };
		s5.insert(0, s6); // ��s5��λ��0֮ǰ����s6�Ŀ���
		fprintf(stdout, "s5: %s\n", s5.c_str());
		s5.insert(0, s6, 0, s6.size()); // ��s5[0]֮ǰ����s6��s6[0]��ʼ��s6.size()���ַ�
		fprintf(stdout, "s5: %s\n", s5.c_str());

		// append: ����ĩβ���в��������һ�ּ�д��ʽ
		std::string s7{ "C++ Primer" }, s8{ s7 };
		s7.insert(s7.size(), " 5th Ed.");
		s8.append(" 5th Ed.");
		fprintf(stdout, "s7: %s; s8: %s\n", s7.c_str(), s8.c_str());

		// replace: �ǵ���erase��insert��һ�ּ�д��ʽ
		s7.replace(11, 3, "Fifth"); // s7.erase(11, 3); s7.insert(11, "Fifth");
		fprintf(stdout, "s7: %s\n", s7.c_str());

		/*
			s.find(args)������s��args��һ�γ��ֵ�λ��
			s.rfind(args)������s��args���һ�γ��ֵ�λ��
			s.find_first_of(args)����s�в���args���κ�һ���ַ���һ�γ��ֵ�λ��
			s.find_last_of(args)����s�в���args���κ�һ���ַ����һ�γ��ֵ�λ��
			s.find_first_not_of(args)����s�в��ҵ�һ������args�е��ַ�
			s.find_last_not_of(args)����s�в������һ������args�е��ַ�
		*/
		
		// find: ���ص�һ��ƥ��λ�õ��±�
		std::string s9{ "AnnaBelle" };
		auto pos1 = s9.find("Belle");
		auto pos2 = s9.find("xxx");
		fprintf(stdout, "pos1: %d, pos2: %d\n", pos1, pos2); // 4, -1

		// find_first_of: ����������ַ������κ�һ���ַ�ƥ���λ��
		std::string numbers{ "0123456789" }, name{ "r2d2" };
		auto pos3 = name.find_first_of(numbers);
		fprintf(stdout, "pos3: %d\n", pos3); // 1, name�е�һ�����ֵ��±�

		// find_first_not_of: ��һ�����ڲ����е��ַ�
		std::string s10{ "03714p3" };
		auto pos4 = s10.find_first_not_of(numbers);
		fprintf(stdout, "pos4: %d\n", pos4); // 5

		// compare: ����0(����)������(����)����(С��)
		auto ret = numbers.compare(name);
		fprintf(stdout, "compare result: %d\n", ret);// -1

		// ��ֵ������string֮���ת��
		int i{ 43 };
		std::string s11 = std::to_string(i); // ������iת��Ϊ�ַ���ʾ��ʽ
		double d = std::stod(s11); // ���ַ���s11ת��Ϊ������
		fprintf(stdout, "s11: %s, d: %f\n", s11.c_str(), d);

		/*
			to_string(val):һ�����غ�����������ֵval��string��ʾ��val�������κ���������
			stoi(s,p,b)/stol(s,p,b)/stoul(s,p,b)/stoll(s,p,b)/stoull(s,p,b)������s����ʼ�Ӵ�(��ʾ��������)����ֵ��
				�������ͷֱ���int��long��unsigned long��long long��unsigned long long��b��ʾת�����õĻ�����
				Ĭ��ֵΪ10.p��size_tָ�룬��������s�е�һ������ֵ�ַ����±꣬pĬ����0�����������������±ꡣ
			stof(s,p)/stod(s,p)/stold(s,p)������s����ʼ�Ӵ�(��ʾ����������)����ֵ������ֵ���ͷֱ���float��double��
				long double.����p������������ת��������һ����
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
		isalnum(c)����c����ĸ������ʱΪ��
		isalpha(c)����c����ĸʱΪ��
		isblank(c)����c�ǿհ��ַ�ʱΪ��(C++11)
		iscntrl(c)����cʱ�����ַ�ʱΪ��
		isdigit(c)����c������ʱΪ��
		isgraph(c)����c���ǿո񵫿ɴ�ӡʱΪ��
		islower(c)����c��Сд��ĸʱΪ��
		isprint(c)����c�ǿɴ�ӡ�ַ�ʱΪ��(��c�ǿո��c���п�����ʽ)
		ispunct(c)����c�Ǳ�����ʱΪ��(��c���ǿ����ַ������֡���ĸ���ɴ�ӡ�հ��е�һ��)
		isspace(c)����c�ǿհ�ʱΪ��(��c�ǿո񡢺����Ʊ���������Ʊ�����س��������з�����ֽ���е�һ��)
		isupper(c)����c�Ǵ�д��ĸʱΪ��
		isxdigit(c)����c��ʮ����������ʱΪ��
		tolower(c)�����c�Ǵ�д��ĸ�������Ӧ��Сд��ĸ������ԭ�����c
		toupper(c)�����c��Сд��ĸ�������Ӧ�Ĵ�д��ĸ������ԭ�����c
	*/

	std::string s1{ "Hello World!!!" };

	decltype(s1.size()) punct_cnt{ 0 };
	for (auto c : s1) {
		if (ispunct(c))
			++punct_cnt;
	}
	std::cout << punct_cnt << " punctutation characters in " << s1 << std::endl;

	for (auto &c : s1) { // ����s1�е�ÿ���ַ�(Note:c������)
		c = toupper(c); // c��һ�����ã���˸�ֵ��佫�ı�s���ַ���ֵ
	}
	std::cout << "toupper s1: " << s1 << std::endl;

	// string������±������ڵ���0��С��s.size()
	// Note��C++��׼����Ҫ���׼�����±��Ƿ�Ϸ���һ��ʹ����һ��������Χ���±꣬�ͻ��������Ԥ֪�Ľ��
	std::string s2{"some string"};
	for (decltype(s2.size()) index = 0; index != s2.size() && !isspace(s2[index]); ++index) {
		s2[index] = toupper(s2[index]);
	}
	std::cout << "s2: " << s2 << std::endl;

	// ʹ���±�ִ���������
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

int test_string_name_match()
{
	const std::vector<std::string> all{ "abc.jpg", "de1.png", "saf.jpg", "sdvv.jpg", "fsd.jpg", "32f.jpg", "12.png",
		"Del.png", "sAF.jpg", "fad.jpg", "fsf.png", "12.jpg", "saf.png", "fad.png", "sdvv.png" };

	std::vector<std::string> vec_jpg, vec_png;
	for (auto& name : all) {
		std::string tmp = name;
		int pos = tmp.find_last_of(".");
		std::string prefix = tmp.substr(0, pos);
		std::string suffix = tmp.substr(pos + 1);
		//fprintf(stdout, "prefix: %s, suffix: %s\n", prefix.c_str(), suffix.c_str());

		if (suffix == "jpg") vec_jpg.emplace_back(prefix);
		else if (suffix == "png") vec_png.emplace_back(prefix);
	}

	std::sort(vec_jpg.begin(), vec_jpg.end());
	std::sort(vec_png.begin(), vec_png.end());

	std::vector<std::string> ret;
	for (int i = 0; i < vec_jpg.size(); ++i) {
		std::string& tmp1 = vec_jpg[i];

		for (int j = 0; j < vec_png.size(); ++j) {
			std::string& tmp2 = vec_png[j];
			if (tmp1 == tmp2) {
				ret.emplace_back(tmp1);
				break;
			}
		}
	}

	for (auto& name : ret) {
		fprintf(stdout, "name: %s\n", name.c_str());
	}

	return 0;
}
