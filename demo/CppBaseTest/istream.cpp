#include <iostream>
#include <fstream>
#include <string>
#include "istream.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/51287210

void test_istream()
{
	//std::istringstream
	std::filebuf in;
	if (!in.open("E:/GitCode/Messy_Test/testdata/istream.data", std::ios::in)) {
		std::cout << "fail to open file" << std::endl;
		return;
	}

	std::istream iss(&in);
	std::string str;
	int count = 0;

	while (!iss.eof()) {
		if (iss.bad()) {
			std::cout << "input stream corrupted" << std::endl;
			break;
		}

		if (iss.fail()) {
			std::cout << "bad data" << std::endl;
			iss.clear(std::istream::failbit);
			iss.ignore(256, '\n');
			continue;
		}

		std::getline(iss, str);

		if (str == "#filename:") {
			iss >> str;
			std::cout << "file name: " << str << std::endl;
		}

		if (str == "#content:") {
			std::getline(iss, str);
			std::cout << "file content: " << str << std::endl;
		}

		if (str == "#add operation:") {
			int a, b;
			iss >> a >> b;
			std::cout << "a + b = " << (a + b) << std::endl;
		}

		if (str == "#char array:") {
			char a, b, c, d, e, f;
			iss >> a >> b >> c >> d >> e >> f;
			std::cout << a << "  " << b << "  " << c << "  " << d << "  " << e << "  " << f << std::endl;
		}

		if (str == "#int array:") {
			int arr[2][3];
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 3; j++) {
					iss >> arr[i][j];
				}
			}

			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 3; j++) {
					std::cout << arr[i][j] << "    ";
				}
				std::cout << std::endl;
			}
		}

		if (str == "#mean value:") {
			float mean_value;
			iss >> mean_value;
			std::cout << "mean_value = " << mean_value << std::endl;
		}
	}

	in.close();
}

