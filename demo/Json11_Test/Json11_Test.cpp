#include <iostream>
#include <string>
#include "json11.hpp"

int test1();
int test2();
int test3();

int main()
{
	test3();

	std::cout << "ok" << std::endl;
	return 0;
}

int test1()
{
	json11::Json my_json = json11::Json::object{
			{ "中国", "value1" },
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
