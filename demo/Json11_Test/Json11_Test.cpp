#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json11.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/51396932

#ifdef _MSC_VER
#include <Windows.h>
static std::string utf8_to_gbk(const char* utf8) {
	char gbk[256];
	const int maxlen = 256;
	wchar_t unicode_str[maxlen];
	int outlen = MultiByteToWideChar(CP_UTF8, 0, utf8, strlen(utf8), unicode_str, maxlen);
	outlen = WideCharToMultiByte(CP_ACP, 0, unicode_str, outlen, gbk, 256, NULL, NULL);
	gbk[outlen] = '\0';

	std::string str;
	str.assign(gbk);
	return str;
}
#endif

int test1();
int test2();
int test3();
int test4();

int main()
{
	test4();

	std::cout << "ok" << std::endl;
	return 0;
}

int test4()
{
	//std::istringstream  
	std::filebuf in;
	if (!in.open("E:/GitCode/Messy_Test/testdata/json.data", std::ios::in)) {
		std::cout << "fail to open file" << std::endl;
		return -1;
	}

	std::istream iss(&in);

	std::istreambuf_iterator<char> eos;
	std::string s(std::istreambuf_iterator<char>(iss), eos);
	std::string err;
	auto json = json11::Json::parse(s, err);
	if (!err.empty()) {
		in.close();
		return -1;
	}

	std::cout << "************** show file info *****************" << std::endl;
	std::string json_str = json.dump();
	std::cout << json_str << std::endl;

	std::cout << "*************** start parse ****************" << std::endl;

	std::string name = json["name"].string_value();
	std::string addr = json["address"].string_value();
	int age = json["age"].int_value();
	
	json11::Json::array array_ = json["value1"].array_items();
	std::vector<std::vector<float>> value1;
	value1.resize(array_.size());
	for (int i = 0; i < array_.size(); i++) {
		json11::Json::array tmp = array_[i].array_items();

		value1[i].resize(tmp.size());
		for (int j = 0; j < tmp.size(); j++) {
			value1[i][j] = tmp[j].number_value();
		}
	}
	
	std::vector<float> value2;
	array_ = json["value2"].array_items();
	value2.resize(array_.size());
	for (int i = 0; i < array_.size(); i++) {
		value2[i] = array_[i].number_value();
	}

	std::string beijing_addr;
	bool beijing_car, beijing_cat;
	if (json["bei_jing"].is_null()) {
		std::cout << "failed to get bei_jing info" << std::endl;
	} else {
		json11::Json::object object_ = json["bei_jing"].object_items();

		beijing_addr = object_["address"].string_value();
		beijing_car = object_["car"].bool_value();
		beijing_cat = object_["cat"].bool_value();
	}

	std::string shandong_addr, tmp_addr;
	std::vector<std::string> shandong_value1;
	if (json["shan_dong"].is_null()) {
		std::cout << "failed to get shan_dong info" << std::endl;
	} else {
		json11::Json::object object_ = json["shan_dong"].object_items();

		tmp_addr = object_["tmp"].string_value();
		if (tmp_addr == "") {
			std::cout << "tmp is null" << std::endl;
		}

		shandong_addr = object_["address"].string_value();

		json11::Json::array tmp = object_["value1"].array_items();
		shandong_value1.resize(array_.size());
		json11::Json json_ = tmp[0];
		shandong_value1[0] = json_["ji_nan"].string_value();
		json_ = tmp[1];
		shandong_value1[1] = json_["tai_an"].string_value();
	}

	std::cout << "************** parse result ***************" << std::endl;
	std::cout << "name: " << utf8_to_gbk(name.c_str()) << std::endl;
	std::cout << "address: " << utf8_to_gbk(addr.c_str()) << std::endl;
	std::cout << "age: " << age << std::endl;

	std::cout << "value1: " << std::endl;
	for (int i = 0; i < value1.size(); i++) {
		for (int j = 0; j < value1[i].size(); j++) {
			std::cout << "  " << value1[i][j];
		}
		std::cout << std::endl;
	}

	std::cout << "value2: " << std::endl;
	for (int i = 0; i < value2.size(); i++) {
		std::cout << "  " << value2[i];
	}
	std::cout << std::endl;

	std::cout << "bei_jing info: " << std::endl;
	std::cout << "  address: " << utf8_to_gbk(beijing_addr.c_str()) << std::endl;
	std::cout << "  car: " << beijing_car << std::endl;
	std::cout << "  cat: " << beijing_cat << std::endl;

	std::cout << "shan_dong info: " << std::endl;
	std::cout << "  address: " << utf8_to_gbk(shandong_addr.c_str()) << std::endl;
	std::cout << "  value1: " << std::endl;
	std::cout << "    ji_nan: " << utf8_to_gbk(shandong_value1[0].c_str()) << std::endl;
	std::cout << "    tai_an: " << utf8_to_gbk(shandong_value1[1].c_str()) << std::endl;

	in.close();
	return 0;
}

int test1()
{
	json11::Json my_json = json11::Json::object{
			{ "中国", "北京" },
			{ "key2", false },
			{ "key3", json11::Json::array { 1, 2, 3 } },
	};
	std::string json_str = my_json.dump();
	std::string key_1 = my_json["中国"].string_value();

	std::cout << json_str << std::endl;
	std::cout << key_1 << std::endl;

	return 0;
}

int test2()
{
	class Point {
	public:
		int x;
		int y;
		Point(int x, int y) : x(x), y(y) {}
		json11::Json to_json() const { return json11::Json::array { x, y }; }
	};

	std::vector<Point> points = { { 1, 2 }, { 10, 20 }, { 100, 200 } };
	std::string points_json = json11::Json(points).dump();

	std::cout << points_json << std::endl;

	return 0;
}

int test3()
{
	json11::Json json = json11::Json::array { json11::Json::object{ { "k", "v" } } };
	std::string str = json[0]["k"].string_value();

	std::cout << str << std::endl;

	return 0;
}
