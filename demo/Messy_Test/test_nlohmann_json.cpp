#ifdef _MSC_VER
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <nlohmann/json.hpp>

// Blog: https://blog.csdn.net/fengbingchun/article/details/148431502

#pragma execution_character_set("utf-8") // when the json content contains Chinese content

namespace {
using json = nlohmann::json;
constexpr char file_name1[]{ "../../../testdata/test.json" };
constexpr char file_name2[]{ "../../../testdata/test.data" };

int dump()
{
	auto numbers = R"({"numbers": [1, 2, 3]})";
	if (!json::accept(numbers)) {
		std::cerr << "Error: invalid json: " << numbers << std::endl;
		return -1;
	}
	json j_numbers = json::parse(numbers);

	auto city = R"({"city":"天津"})";
	if (!json::accept(city)) {
		std::cerr << "Error: invalid json: " << city << std::endl;
		return -1;
	}
	json j_city = json::parse(city);

	json merged{};
	merged.update(j_numbers);;
	merged.update(j_city);

	auto csdn = R"({"csdn": {"addr": "https://blog.csdn.net/fengbingchun", "visits": 14000000, "fan": 14000}})";
	if (!json::accept(csdn)) {
		std::cerr << "Error: invalid json: " << csdn << std::endl;
		return -1;
	}
	json j_csdn = json::parse(csdn);
	merged.merge_patch(j_csdn);

	merged["github"] = { {"addr","https://github.com/fengbingchun"}, {"stars",1400} };

	json j_hobbies = json::parse(R"({"hobbies": ["swimming", "table tennis"]})");
	merged.merge_patch(j_hobbies);

	auto j_fruits = R"({"fruits": ["peaches", "bananas", "melons"]})"_json;
	merged.merge_patch(j_fruits);

	std::ofstream out_file(file_name1);
	if (!out_file.is_open()) {
		std::cerr << "Error: failed to open json file: " << file_name1 << std::endl;
		return -1;
	}

	out_file << merged.dump(4);
	return 0;
}

int parse()
{
	SetConsoleOutputCP(CP_UTF8); // Chinese output is garbled

	std::ifstream in_file(file_name1);
	if (!in_file.is_open()) {
		std::cerr << "Error: failed to open json file: " << file_name1 << std::endl;
		return -1;
	}
	json data = json::parse(in_file); 

	auto city = data["city"];
	std::cout << "city:" << city << std::endl;

	auto csdn = data["csdn"];
	std::cout << "csdn: addr: " << csdn["addr"] << ", fan: " << csdn["fan"] << ", visits: " << data["csdn"]["visits"] << std::endl;

	auto github = data["github"];
	std::cout << "github: addr:" << github["addr"] << ", stars:" << github["stars"] << std::endl;

	std::cout << "fruits: ";
	auto fruits = data["fruits"]; // std::vector<string>
	for (const auto& fruit : fruits) {
		std::cout << fruit << ",";
	}
	std::cout << std::endl;

	if (data.contains("hobbies")) { // field may not exist
		std::cout << "hobbies: ";
		for (const auto& hobby : data["hobbies"]) {
			std::cout << hobby << ",";
		}
		std::cout << std::endl;
	}

	std::cout << "numbers: ";
	for (const auto& number : data["numbers"]) { // std::vector<int>
		std::cout << number << ",";
	}
	std::cout << std::endl;

	return 0;
}

int dump_bson() // binary formats:BSON
{
	std::ifstream in_file(file_name1);
	if (!in_file.is_open()) {
		std::cerr << "Error: failed to open json file: " << file_name1 << std::endl;
		return -1;
	}
	json data = json::parse(in_file);

	std::vector<std::uint8_t> bson_data{};
	try {
		bson_data = json::to_bson(data);
	} catch (const json::type_error& e) {
		std::cerr << "Error: to_bson: " << e.what() << std::endl;
		return -1;
	}

	std::ofstream out_file(file_name2, std::ios::binary);
	if (!out_file.is_open()) {
		std::cerr << "Error: failed to open bson file: " << file_name2 << std::endl;
		return -1;
	}

	out_file.write(reinterpret_cast<const char*>(bson_data.data()), bson_data.size());
	   
	return 0;
}

int parse_bson()
{
	std::ifstream in_file(file_name2, std::ios::binary);
	if (!in_file.is_open()) {
		std::cerr << "Error: failed to open bson file: " << file_name2 << std::endl;
		return -1;
	}

	auto j = json::from_bson(in_file);
	if (j.empty()) {
		std::cerr << "Error: failed to load bson" << std::endl;
		return -1;
	}
	if (!j.is_object()) {
		std::cerr << "Error: top-level elements are not objects" << std::endl;
		return -1;
	}
	if (!j.contains("city")) {
		std::cerr << "Error: missing field: city" << std::endl;
		return -1;
	}
	if (!j["city"].is_string()) {
		std::cerr << "Error: wrong field type" << std::endl;
		return -1;
	}

	auto csdn = j["csdn"];
	std::cout << "csdn: addr: " << csdn["addr"] << ", fan: " << csdn["fan"] << ", visits: " << j["csdn"]["visits"] << std::endl;

	auto github = j["github"];
	std::cout << "github: addr:" << github["addr"] << ", stars:" << github["stars"] << std::endl;

	return 0;
}

} // namespace

int test_nlohmann_json()
{
	if (auto ret = dump(); ret != 0) {
		std::cerr << "Error: dump json" << std::endl;
		return -1;
	}

	if (auto ret = parse(); ret != 0) {
		std::cerr << "Error: parse json" << std::endl;
		return -1;
	}

	if (auto ret = dump_bson(); ret != 0) {
		std::cerr << "Error: dump bson" << std::endl;
		return -1;
	}

	if (auto ret = parse_bson(); ret != 0) {
		std::cerr << "Error: parse bson" << std::endl;
		return -1;
	}

	return 0;
}

#endif // _MSC_VER
