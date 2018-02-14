#include "test_parse_cvs.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "parse_csv.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/79324555

namespace parse_cvs_ {

int test_parse_cvs_1()
{
	std::ifstream file("E:/GitCode/Messy_Test/testdata/test_csv.csv");

	std::vector<std::vector<std::string>> data;
	CSVIterator loop(file);
	for (; loop != CSVIterator(); ++loop) {
		CSVRow row = *loop;
		std::vector<std::string> tmp(row.size());
		for (int i = 0; i < row.size(); ++i) {
			tmp[i] = row[i];
		}
		data.emplace_back(tmp);
	}

	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			fprintf(stdout, "%s\t", data[i][j].c_str());
		}
		fprintf(stdout, "\n");
	}

	return 0;
}

} // namespace parse_cvs_
