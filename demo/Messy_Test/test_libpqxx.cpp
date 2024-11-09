#ifdef _MSC_VER
#include "funset.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <thread>
#include <pqxx/pqxx>

// Blog: https://blog.csdn.net/fengbingchun/article/details/143250318

namespace {
// reference: https://www.postgresql.org/docs/current/libpq-connect.html#LIBPQ-CONNSTRING
const std::string options{ "hostaddr=127.0.0.1 port=5432 user=postgres password=spring dbname=" };
const std::string table_teacher{ "CREATE TABLE teacher ("
						"id INTEGER PRIMARY KEY NOT NULL CHECK(id>1000),"
						"name CHAR(32) NOT NULL,"
						"addr CHAR(64) DEFAULT 'BeiJing',"
						"sex CHAR(8) NOT NULL)" };
const std::string table_student{ "CREATE TABLE student ("
						"id INTEGER PRIMARY KEY NOT NULL,"
						"name CHAR(32) NOT NULL,"
						"addr CHAR(64) DEFAULT 'TianJin',"
						"age INTEGER,"
						"score REAL,"
						"date TIMESTAMP,"
						"sex CHAR(8) NOT NULL)" };
std::ofstream outfile;

int create_database(const std::string& dbname)
{
	try {
		pqxx::connection c{ options + "postgres" }; // database postgres must already exist
		c.set_client_encoding("GBK");
		pqxx::nontransaction tx{ c };
		const std::string str{ "CREATE DATABASE " };
		tx.exec(str + dbname);
	}
	catch (const std::exception& e) {
		std::cerr << "Error:create database: " << e.what() << std::endl;
		outfile << "Error:create database: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}

int connect_database(const std::string& dbname)
{
	try {
		pqxx::connection c{ options + dbname };
		//c.set_client_encoding("GBK"); // GBK, default:UTF8
		if (c.is_open())
			std::cout << c.dbname() << " database was opened successfully" << std::endl;
		else {
			std::cerr << "Error:failed to open database:" << dbname << std::endl;
			return -1;
		}

		std::cout << "dbname:" << c.dbname() << ", username:" << c.username()
			<< ", hostname:" << c.hostname() << ", port:" << c.port()
			<< ", backendpid:" << c.backendpid() << ", sock:" << c.sock()
			<< ", protocol_version:" << c.protocol_version()
			<< ", server_version:" << c.server_version()
			<< ", get_client_encoding:" << c.get_client_encoding()
			<< ", encoding_id:" << c.encoding_id()
			<< ", get_notifs:" << c.get_notifs()
			<< std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error:connect database: " << e.what() << std::endl;
		outfile << "Error:connect database: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}

int drop_database(const std::string& dbname)
{
	try {
		pqxx::connection c{ options + "postgres" };
		c.set_client_encoding("GBK");
		pqxx::nontransaction tx{ c };
		const std::string str{ "DROP DATABASE " };
		tx.exec(str + dbname);
	}
	catch (const std::exception& e) {
		std::cerr << "Error:drop database: " << e.what() << std::endl;
		outfile << "Error:drop database: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}

int create_table(const std::string& dbname, const std::string& command)
{
	try {
		pqxx::connection c{ options + dbname };
		c.set_client_encoding("GBK");
		pqxx::work w(c);
		w.exec(command);
		w.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error:create table: " << e.what() << std::endl;
		outfile << "Error:create table: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}

int drop_table(const std::string& dbname, const std::string& tablename)
{
	try {
		pqxx::connection c{ options + dbname };
		c.set_client_encoding("GBK");
		pqxx::work w(c);
		const std::string str{ "DROP TABLE " };
		w.exec(str + tablename);
		w.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error:drop table: " << e.what() << std::endl;
		outfile << "Error:drop table: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}

int insert_into_teacher(const std::string& dbname, int id, const std::string& name, const std::string& addr, const std::string& sex)
{
	try {
		pqxx::connection c{ options + dbname + " options='-c client_encoding=GBK'" }; // 有中文时需设置client_encoding=GBK,否则数据库中会显示乱码,推荐使用:c.set_client_encoding("GBK")
		pqxx::work w(c);

		const std::string query{ "INSERT INTO teacher (id, name, addr, sex) VALUES ($1, $2, $3, $4)" };
		w.exec_params(query, id, name, addr, sex);
		w.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error:insert into: " << e.what() << std::endl;
		outfile << "Error:insert into: " << e.what() << std::endl;
		return -1;
	}

	return 0;
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
	try {
		pqxx::connection c{ options + dbname };
		c.set_client_encoding("GBK"); // 有中文时需设置client_encoding=GBK,否则数据库中会显示乱码
		pqxx::work w(c);

		const std::string query{ "INSERT INTO student (id, name, addr, age, score, date, sex) VALUES ($1, $2, $3, $4, $5, $6, $7)" };
		w.exec_params(query, id, name, addr, age, score, date, sex);
		w.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error:insert into: " << e.what() << std::endl;
		outfile << "Error:insert into: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}

int alter_table(const std::string& dbname)
{
	try {
		pqxx::connection c{ options + dbname };
		c.set_client_encoding("GBK");
		pqxx::work w(c);

		const std::string query{ "ALTER TABLE teacher " };
		w.exec(query + "ADD COLUMN hobbies CHAR(64) DEFAULT '游泳'");
		w.exec(query + "DROP COLUMN addr");
		w.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error:alter table: " << e.what() << std::endl;
		outfile << "Error:alter table: " << e.what() << std::endl;
		return -1;
	}
	return 0;
}

int delete_table_data(const std::string& dbname)
{
	try {
		pqxx::connection c{ options + dbname };
		c.set_client_encoding("GBK");
		pqxx::work w(c);

		const std::string query{ "DELETE FROM teacher WHERE id > 10000 OR sex='女'" };
		w.exec(query);
		w.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error:delete: " << e.what() << std::endl;
		outfile << "Error:delete: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}

int update_table_data(const std::string& dbname)
{
	try {
		pqxx::connection c{ options + dbname };
		c.set_client_encoding("GBK");
		pqxx::work w(c);

		const std::string query{ "UPDATE teacher SET " };
		w.exec(query + "sex='男' WHERE sex='man'");
		w.exec(query + "sex='女' WHERE sex='woman'");
		w.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error:update: " << e.what() << std::endl;
		outfile << "Error:update: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}

int select_table_data(const std::string& dbname)
{
	try {
		pqxx::connection c{ options + dbname };
		c.set_client_encoding("GBK");
		pqxx::work w(c);

		const std::string query{ "SELECT * FROM student WHERE age >= 20 AND date > '2024-10-25 16:43:06'" };
		pqxx::result r(w.exec(query));
		w.commit();

		std::cout << "empty:" << r.empty() << ", size:" << r.size() << ", columns:" << r.columns() << std::endl;
		std::cout << "column name: ";
		for (auto i = 0; i < r.columns(); ++i)
			std::cout << r.column_name(i) << "," << r.column_type(r.column_name(i)) << ";";
		std::cout << std::endl;

		for (const auto& row : r) {
			for (const auto& field : row) {
				std::cout << field.c_str() << "\t";
			}
			std::cout << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error:select: " << e.what() << std::endl;
		outfile << "Error:select: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}

} // namespace

int test_libpqxx()
{
#ifdef _MSC_VER
	outfile.open("../../../testdata/output.txt", std::ios::app);
#else
	outfile.open(../../testdata/output.txt", std::ios::app);
#endif
	if (!outfile.is_open()) {
		std::cerr << "Error:fail to open file to write\n";
		return -1;
	}

	// database
	create_database("Info"); // 创建数据库时,数据库中显示的名字为info，而不是Info
	connect_database("info"); // 连接数据库时指定的数据名区分大小写
	//drop_database("info");

	// table
	create_table("info", table_teacher);
	create_table("info", table_student);

	insert_into_teacher("info", 1111, "Tom", "HeBei", "man");
	insert_into_teacher("info", 5555, "Tom", "北京", "男");
	insert_into_teacher("info", 2222, "小张", "天津", "woman");
	insert_into_teacher("info", 16625, "xx", "xx", "女");

	insert_into_student("info", 8, "小王", "HeBei", 32, 88.8, get_current_time(), "男");
	std::this_thread::sleep_for(std::chrono::seconds(2));
	insert_into_student("info", 28, "小何", "深圳", 8, 22.22, get_current_time(), "女");
	insert_into_student("info", 29, "Lucy", "北京", 18, 22.22, get_current_time(), "woman");
	insert_into_student("info", 33, "Tom", "深圳", 28, 22.22, get_current_time(), "woman");
	insert_into_student("info", 18, "小李", "上海", 28, 66.6, get_current_time(), "女");
	std::this_thread::sleep_for(std::chrono::seconds(2));
	insert_into_student("info", 48, "Tom", "深圳", 38, 22.22, get_current_time(), "woman");

	alter_table("info");
	delete_table_data("info");
	update_table_data("info");
	select_table_data("info");
	drop_table("info", "teacher");

	outfile.close();
	return 0;
}

#endif // _MSC_VER
