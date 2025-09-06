#ifdef _MSC_VER
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <OpenXLSX/OpenXLSX.hpp>
#include "common.hpp"

// Blog: https://blog.csdn.net/fengbingchun/article/details/151259362

int test_openxlsx_parse()
{
	constexpr char file_name[]{ "../../../testdata/测试.xlsx" };

	try {
		OpenXLSX::XLDocument doc;
		doc.open(gbk_to_utf8(file_name));

		auto workbook = doc.workbook();

		auto worksheet_names = workbook.worksheetNames();
		if (worksheet_names.size() == 0) {
			std::cerr << "Error: no worksheet: " << file_name << std::endl;
			return -1;
		}
		std::cout << "worksheet names: ";
		for (const auto& name : worksheet_names) {
			std::cout << utf8_to_gbk(name) << ", ";
		}
		std::cout << std::endl;

		auto worksheet_name = worksheet_names[0];
		auto worksheet = workbook.worksheet(worksheet_name);
		if (worksheet.rowCount() == 0) {
			std::cerr << "Error: excel table is empty: " << file_name << std::endl;
			return -1;
		}

		auto range = worksheet.range();
		auto rows = range.numRows();
		auto cols = range.numColumns();
		std::cout << "file name: " << file_name << ", work sheet name: " << utf8_to_gbk(worksheet_name) << ", rows: " << rows << ", cols: " << cols << std::endl;

		std::string str{};
		for (auto row = 1; row <= rows; ++row) {
			for (auto col = 1; col <= cols; ++col) {
				auto cell = worksheet.cell(row, col);

				if (cell.value().type() == OpenXLSX::XLValueType::String) {
					str = cell.value().get<std::string>();
					std::cout << utf8_to_gbk(str) << "\t";
				}
				else if (cell.value().type() == OpenXLSX::XLValueType::Integer) {
					std::cout << cell.value().get<int64_t>() << "\t";
				}
				else if (cell.value().type() == OpenXLSX::XLValueType::Float) {
					std::cout << cell.value().get<float>() << "\t";
				}
			}

			std::cout << std::endl;
		}

		const std::vector<std::string> header_row{ "代码", "-200大", "序号", "库存(T)", "名称" };
		for (auto col = 1; col <= cols; ++col) {
			auto cell = worksheet.cell(1, col);

			for (auto i = 0; i < header_row.size(); ++i) {
				if (cell.value().type() == OpenXLSX::XLValueType::String) {
					if (utf8_to_gbk(cell.value().get<std::string>()) == header_row[i]) {
						std::cout << "第 " << col << " 列表示:" << header_row[i] << std::endl;
						break;
					}
				}
			}
		}

		doc.close();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}

int test_openxlsx_create()
{
	constexpr char file_name[]{ "../../../testdata/创建.xlsx" };

	try {
		OpenXLSX::XLDocument doc;
		doc.create(gbk_to_utf8(file_name), OpenXLSX::XLForceOverwrite);

		auto workbook = doc.workbook();

		constexpr char sheet_name[]{ "信息" };
		workbook.addWorksheet(gbk_to_utf8(sheet_name));

		constexpr char default_sheet[]{ "Sheet1" };
		if (workbook.worksheetExists(default_sheet)) {
			workbook.deleteSheet(default_sheet);
		}
		
		const std::vector<std::string> header_row{ "序号","名称", "代码", "-200大",	"库存(T)" };
		using info = std::tuple<int, std::string, std::string, float, float>;
		const std::vector<info> infos{
			{1, "铁矿", "DAV382", 232.1, 10},
			{2, "Tiger", "234SCS", 2334, 18.5},
			{3, "香蕉B", "2349CX", 233.5, -192.4},
			{4, "Apple号", "232398", 8.48, 23} };

		auto worksheet = workbook.worksheet(gbk_to_utf8(sheet_name));

		int col = 1;
		for (const auto& value : header_row) {
			worksheet.cell(1, col).value() = gbk_to_utf8(value);
			++col;
		}

		auto float_to_string = [](float value) {
			std::ostringstream oss;
			oss << value;
			return oss.str();
		};

		int row = 2;
		for (const auto& [num, str1, str2, f1, f2] : infos) {
			worksheet.cell(row, 1).value() = num;
			worksheet.cell(row, 2).value() = gbk_to_utf8(str1);
			worksheet.cell(row, 3).value() = gbk_to_utf8(str2);
			worksheet.cell(row, 4).value() = f1; // 注:直接赋值f1,在excel表中显示与原始值有差异;使用float_to_string(f1)又会导致再次解析时此数据类型为string而不是float
			worksheet.cell(row, 5).value() = f2;
			++row;
		}

		doc.save();
		doc.close();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}

#endif // _MSC_VER
