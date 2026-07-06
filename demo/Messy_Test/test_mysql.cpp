#ifdef _MSC_VER
#include <iostream>
#include <fstream>
#include <string>
#include <mysql.h>

// Blog: https://blog.csdn.net/fengbingchun/article/details/162621400

int test_client_mysql()
{
    constexpr char host[]{ "192.168.19.205" }, user[]{ "feo" }, passwd[]{ "Sante@888" }, db[]{ "info" };
    constexpr unsigned int port{ 3306 }, timeout_sec{5};
    constexpr char starttime[]{ "2026-06-01 00:00:00" }, endtime[]{ "2026-07-01 00:00:00" };
    constexpr char csv_name[]{ "feo.csv" };
    const std::string table_name{ "time_values2" }, time_column{ "receive_date" }, value_column{ "Feo" };

	auto conn = mysql_init(nullptr);
    if (!conn) {
        std::cerr << "failed to mysql init" << std::endl;
        return -1;
    }

    if (auto ret = mysql_options(conn, MYSQL_SET_CHARSET_NAME, "utf8mb4"); ret != 0) {
        std::cerr << "failed to set charset name: " << mysql_error(conn) << std::endl;
        return -1;
    }

    if (auto ret = mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec); ret != 0) {
        std::cerr << "failed to set connect timeout: " << mysql_error(conn) << std::endl;
        return -1;
    }

    if (!mysql_real_connect(conn, host, user, passwd, db, port, nullptr, 0)) {
        std::cerr << "failed to connect:" << mysql_error(conn) << std::endl;
        return -1;
    }

    auto stmt = mysql_stmt_init(conn);
    if (!stmt) {
        std::cerr << "failed to stmt init: " << mysql_error(conn) << std::endl;
        return -1;
    }

    std::string sql =
        "SELECT " + time_column + ", " + value_column +
        " FROM " + table_name +
        " WHERE " + time_column + " >= ?"
        " AND " + time_column + " < ?"
        " ORDER BY " + time_column + " DESC";

    if (mysql_stmt_prepare(stmt, sql.c_str(), static_cast<unsigned long>(sql.length())) != 0) {
        std::cerr << "failed to stmp prepare: " << mysql_stmt_error(stmt) << std::endl;
        mysql_stmt_close(stmt);
        return -1;
    }

    MYSQL_BIND param[2]{};
    memset(param, 0, sizeof(param));
    param[0].buffer_type = MYSQL_TYPE_STRING;
    param[0].buffer = (void*)starttime;
    param[0].buffer_length = (unsigned long)strlen(starttime);
    param[1].buffer_type = MYSQL_TYPE_STRING;
    param[1].buffer = (void*)endtime;
    param[1].buffer_length = (unsigned long)strlen(endtime);

    if (mysql_stmt_bind_param(stmt, param) != 0) {
        std::cerr << "failed to stmt bind param: " << mysql_stmt_error(stmt) << std::endl;
        return -1;
    }

    if (mysql_stmt_execute(stmt) != 0) {
        std::cerr << "failed to stmt execute: " << mysql_stmt_error(stmt) << std::endl;
        return -1;
    }

    char receive_date[32]{}, feo[32]{};
    unsigned long date_len{ 0 }, feo_len{ 0 };
    bool date_null{ 0 }, feo_null{ 0 };

    MYSQL_BIND result[2]{};
    memset(result, 0, sizeof(result));
    result[0].buffer_type = MYSQL_TYPE_STRING;
    result[0].buffer = receive_date;
    result[0].buffer_length = sizeof(receive_date);
    result[0].length = &date_len;
    result[0].is_null = &date_null;
    result[1].buffer_type = MYSQL_TYPE_STRING;
    result[1].buffer = feo;
    result[1].buffer_length = sizeof(feo);
    result[1].length = &feo_len;
    result[1].is_null = &feo_null;

    if (mysql_stmt_bind_result(stmt, result) != 0) {
        std::cerr << "failed to stmt bind result: " << mysql_stmt_error(stmt) << std::endl;
        return -1;
    }

    std::ofstream csv(csv_name);
    if (!csv.is_open()) {
        std::cerr << "failed to open csv file: " << csv_name << std::endl;
        return -1;
    }

    int count{ 0 };
    while (true) {
        auto ret = mysql_stmt_fetch(stmt);
        if (ret == MYSQL_NO_DATA)
            break;

        if (ret == 0) {
            receive_date[date_len] = '\0';
            feo[feo_len] = '\0';

            csv << receive_date << "," << feo << "\n";
            ++count;
        }
        else {
            std::cerr << "failed to fetch: " << ret << ", " << mysql_stmt_error(stmt) << std::endl;
        }
    }

    std::cout << "number of valid data rows: " << count << std::endl;
    mysql_stmt_close(stmt);
    mysql_close(conn);
	return 0;
}


#endif // _MSC_VER