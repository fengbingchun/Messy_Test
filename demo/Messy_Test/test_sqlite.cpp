#ifdef _MSC_VER
#include "funset.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <filesystem>
#include <cstring>

#include <sqlite3.h>
#include "common.hpp"

// Blog: https://blog.csdn.net/fengbingchun/article/details/143641492

//#pragma execution_character_set("utf-8") // 支持中文:已过时

namespace {
const std::string table_teacher{ "CREATE TABLE teacher ("
						"id INTEGER PRIMARY KEY NOT NULL CHECK(id>1000),"
						"name TEXT NOT NULL,"
						"addr TEXT DEFAULT 'BeiJing',"
						"sex TEXT NOT NULL);" };
const std::string table_student{ "CREATE TABLE student ("
						"id INTEGER PRIMARY KEY NOT NULL,"
						"name CHAR(32) NOT NULL,"
						"addr CHAR(64) DEFAULT 'TianJin',"
						"age INTEGER,"
						"score REAL,"
						"date CHAR(24),"
						"sex CHAR(8) NOT NULL);" };

int create_database(const std::string& dbname)
{
	sqlite3* db{ nullptr };
	auto ret = sqlite3_open(dbname.c_str(), &db); // 如果数据库不存在,则会创建它
	if (ret != SQLITE_OK)
		std::cerr << "Error: fail to sqlite3_open: " << ret << ", " << sqlite3_errmsg(db) << std::endl;

	sqlite3_close(db);
	return ret;
}

int delete_database(const std::string& dbname)
{
	namespace fs = std::filesystem;
	fs::path file{ dbname };
	if (fs::exists(file)) {
		try {
			fs::remove(file);
		}
		catch (const fs::filesystem_error& e) {
			std::cerr << "Error: " << e.what() << std::endl;
			return -1;
		}
	} else {
		std::cerr << "Warning: database file does not exist: " << dbname << std::endl;
		return -1;
	}

	return 0;
}

int create_table(const std::string& dbname, const std::string& command)
{
	sqlite3* db{ nullptr };
	auto ret = sqlite3_open(dbname.c_str(), &db);
	if (ret != SQLITE_OK)
		std::cerr << "Error: fail to sqlite3_open: " << ret << ", " << sqlite3_errmsg(db) << std::endl;

	char* errmsg{ nullptr };
	ret = sqlite3_exec(db, command.c_str(), nullptr, nullptr, &errmsg);
	if (ret != SQLITE_OK) {
		std::cerr << "Error: fail to create table: " << ret << ", " << errmsg << std::endl;
		sqlite3_free(errmsg);
	}

	sqlite3_close(db);
	return ret;
}

int drop_table(const std::string& dbname, const std::string& tablename)
{
	sqlite3* db{ nullptr };
	auto ret = sqlite3_open(dbname.c_str(), &db);
	if (ret != SQLITE_OK)
		std::cerr << "Error: fail to sqlite3_open: " << ret << ", " << sqlite3_errmsg(db) << std::endl;

	char* errmsg{ nullptr };
	const std::string str{ "DROP TABLE " };
	ret = sqlite3_exec(db, (str+tablename).c_str(), nullptr, nullptr, &errmsg);
	if (ret != SQLITE_OK) {
		std::cerr << "Error: fail to drop table: " << ret << ", " << errmsg << std::endl;
		sqlite3_free(errmsg);
	}

	sqlite3_close(db);
	return ret;
}

int insert_into_teacher(const std::string& dbname, int id, const std::string& name, const std::string& addr, const std::string& sex)
{
	sqlite3* db{ nullptr };
	auto ret = sqlite3_open(dbname.c_str(), &db);
	if (ret != SQLITE_OK)
		std::cerr << "Error: fail to sqlite3_open: " << ret << ", " << sqlite3_errmsg(db) << std::endl;
	
	char* errmsg{ nullptr };
	std::string str{ "INSERT INTO teacher (id, name, addr, sex) VALUES (" };
	str = str + std::to_string(id) + ", '" + name + "', '" + addr + "', '" + sex + "');";
	ret = sqlite3_exec(db, str.c_str(), nullptr, nullptr, &errmsg);
	if (ret != SQLITE_OK) {
		std::cerr << "Error: fail to insert into teacher: " << ret << ", " << errmsg << std::endl;
		sqlite3_free(errmsg);
	}

	sqlite3_close(db);
	return ret;
}

std::string get_current_time()
{
	auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm* now_tm = std::localtime(&timenow);
	std::ostringstream oss;
	oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}

int insert_into_student(const std::string& dbname, int id, const std::string& name, const std::string& addr, int age,
	float score, const std::string& date, const std::string& sex)
{
	sqlite3* db{ nullptr };
	auto ret = sqlite3_open(dbname.c_str(), &db);
	if (ret != SQLITE_OK)
		std::cerr << "Error: fail to sqlite3_open: " << ret << ", " << sqlite3_errmsg(db) << std::endl;

	char* errmsg{ nullptr };
	std::string str{ "INSERT INTO student (id, name, addr, age, score, date, sex) VALUES (" };
	str = str + std::to_string(id) + ", '" + name + "', '" + addr + "'," + std::to_string(age) + "," +
		std::to_string(score) + ", '" + date + "', '" + sex + "'); ";
	ret = sqlite3_exec(db, str.c_str(), nullptr, nullptr, &errmsg);
	if (ret != SQLITE_OK) {
		std::cerr << "Error: fail to insert into student: " << ret << ", " << errmsg << std::endl;
		sqlite3_free(errmsg);
	}

	sqlite3_close(db);
	return ret;
}

int alter_table(const std::string& dbname)
{
	sqlite3* db{ nullptr };
	auto ret = sqlite3_open(dbname.c_str(), &db);
	if (ret != SQLITE_OK)
		std::cerr << "Error: fail to sqlite3_open: " << ret << ", " << sqlite3_errmsg(db) << std::endl;

	char* errmsg{ nullptr };
	const std::string str{ "ALTER TABLE teacher " };

	const std::string str1{ "ADD COLUMN hobbies CHAR(64) DEFAULT swim;" };
	ret = sqlite3_exec(db, (str+str1).c_str(), nullptr, nullptr, &errmsg);
	if (ret != SQLITE_OK) {
		std::cerr << "Error: fail to add cloumn: " << ret << ", " << errmsg << std::endl;
		sqlite3_free(errmsg);
	}

	const std::string str2{ "DROP COLUMN addr;" };
	ret = sqlite3_exec(db, (str + str2).c_str(), nullptr, nullptr, &errmsg);
	if (ret != SQLITE_OK) {
		std::cerr << "Error: fail to drop column: " << ret << ", " << errmsg << std::endl;
		sqlite3_free(errmsg);
	}

	sqlite3_close(db);
	return ret;
}

int delete_table_data(const std::string& dbname)
{
	sqlite3* db{ nullptr };
	auto ret = sqlite3_open(dbname.c_str(), &db);
	if (ret != SQLITE_OK)
		std::cerr << "Error: fail to sqlite3_open: " << ret << ", " << sqlite3_errmsg(db) << std::endl;

	char* errmsg{ nullptr };
	const std::string str{ "DELETE FROM teacher WHERE id > 10000 OR sex='女';" };
	ret = sqlite3_exec(db, str.c_str(), nullptr, nullptr, &errmsg);
	if (ret != SQLITE_OK) {
		std::cerr << "Error: fail to delete data from teachar: " << ret << ", " << errmsg << std::endl;
		sqlite3_free(errmsg);
	}

	sqlite3_close(db);
	return ret;
}

int update_table_data(const std::string& dbname)
{
	sqlite3* db{ nullptr };
	auto ret = sqlite3_open(dbname.c_str(), &db);
	if (ret != SQLITE_OK)
		std::cerr << "Error: fail to sqlite3_open: " << ret << ", " << sqlite3_errmsg(db) << std::endl;

	char* errmsg{ nullptr };
	const std::string str1 = std::string("UPDATE teacher SET sex = 'man' WHERE sex = ") + "\'" + gbk_to_utf8("男") + "\';";
	ret = sqlite3_exec(db, str1.c_str(), nullptr, nullptr, &errmsg);
	if (ret != SQLITE_OK) {
		std::cerr << "Error: fail to update data from teachar: " << ret << ", " << errmsg << std::endl;
		sqlite3_free(errmsg);
	}

	const std::string str2 = std::string("UPDATE teacher SET sex = ") + "\'" + gbk_to_utf8("女") + "\'" + " WHERE sex = 'woman';";
	ret = sqlite3_exec(db, str2.c_str(), nullptr, nullptr, &errmsg);
	if (ret != SQLITE_OK) {
		std::cerr << "Error: fail to update data from teachar: " << ret << ", " << errmsg << std::endl;
		sqlite3_free(errmsg);
	}

	sqlite3_close(db);
	return ret;
}

int select_table_data(const std::string& dbname)
{
	sqlite3* db{ nullptr };
	auto ret = sqlite3_open(dbname.c_str(), &db);
	if (ret != SQLITE_OK)
		std::cerr << "Error: fail to sqlite3_open: " << ret << ", " << sqlite3_errmsg(db) << std::endl;

	const std::string query{ "SELECT * FROM student WHERE age >= 20 AND DATETIME(date) > DATETIME('2024-11-07 17:54:30');" };
	char* errmsg{ nullptr };
	sqlite3_stmt* stmt{ nullptr };
	ret = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
	if (ret != SQLITE_OK) {
		std::cerr << "Error: fail to sqlite3_prepare_v2: " << ret << ", " << sqlite3_errmsg(db) << std::endl;
		return ret;
	}

	std::cout << "id\tname\taddr\tage\tscore\tdate\t\t\t\tsex" << std::endl;
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		auto id = sqlite3_column_int(stmt, 0);
		auto name = utf8_to_gbk(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))));
		auto addr = utf8_to_gbk(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))));
		auto age = sqlite3_column_int(stmt, 3);
		auto score = sqlite3_column_double(stmt, 4);
		auto date = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
		auto sex = utf8_to_gbk(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6))));

		std::cout << id << "\t" << name << "\t" << addr << "\t" << age << "\t" << score << "\t"
			<< date << "\t\t" << sex << std::endl;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return ret;
}

} // namespace

int test_sqlite()
{
	const std::string dbname{ "info.db" };

	//create_database(dbname);
	delete_database(dbname);

	create_table(dbname, table_teacher);
	create_table(dbname, table_student);

	//drop_table(dbname, "teacher");
	//drop_table(dbname, "student");

	insert_into_teacher(dbname, 1111, gbk_to_utf8("Tom"), gbk_to_utf8("HeBei"), gbk_to_utf8("man"));
	insert_into_teacher(dbname, 5555, gbk_to_utf8("Tom"), gbk_to_utf8("北京"), gbk_to_utf8("男"));
	insert_into_teacher(dbname, 2222, gbk_to_utf8("小张"), gbk_to_utf8("天津"), gbk_to_utf8("woman"));
	insert_into_teacher(dbname, 16625, gbk_to_utf8("小王"), gbk_to_utf8("Tianjin"), gbk_to_utf8("女"));

	insert_into_student(dbname, 8, gbk_to_utf8("小王"), gbk_to_utf8("HeBei"), 32, 88.8f, get_current_time(), gbk_to_utf8("男"));
	insert_into_student(dbname, 28, gbk_to_utf8("小何"), gbk_to_utf8("深圳"), 8, 22.22f, get_current_time(), gbk_to_utf8("女"));
	std::this_thread::sleep_for(std::chrono::minutes(1));
	insert_into_student(dbname, 29, gbk_to_utf8("Lucy"), gbk_to_utf8("北京"), 18, 22.22f, get_current_time(), gbk_to_utf8("woman"));
	insert_into_student(dbname, 33, gbk_to_utf8("Tom"), gbk_to_utf8("深圳"), 28, 22.22f, get_current_time(), gbk_to_utf8("woman"));
	insert_into_student(dbname, 18, gbk_to_utf8("小李"), gbk_to_utf8("上海"), 28, 66.6f, get_current_time(), gbk_to_utf8("女"));
	std::this_thread::sleep_for(std::chrono::seconds(5));
	insert_into_student(dbname, 48, gbk_to_utf8("Tom"), gbk_to_utf8("深圳"), 38, 22.22f, get_current_time(), gbk_to_utf8("woman"));

	alter_table(dbname);
	delete_table_data(dbname);
	update_table_data(dbname);
	select_table_data(dbname);

	return 0;
}

#endif // _MSC_VER
