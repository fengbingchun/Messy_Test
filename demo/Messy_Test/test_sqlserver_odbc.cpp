#ifdef _MSC_VER
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

// Blog: https://blog.csdn.net/fengbingchun/article/details/141106964

namespace {
// display error/warning information
void handle_diagnostic_record(SQLHANDLE handle, SQLSMALLINT type, RETCODE code)
{
	if (code == SQL_INVALID_HANDLE) {
		std::cerr << "Error: Invalid handle" << std::endl;
		return;
	}

	SQLSMALLINT number{ 0 };
	constexpr SQLSMALLINT buffer_length{ 1024 };
	SQLCHAR state[SQL_SQLSTATE_SIZE + 1] = { 0 }, message[buffer_length] = { 0 };
	SQLINTEGER  error{ 0 };
	while (SQLGetDiagRec(type, handle, ++number, state, &error, message, buffer_length, nullptr) == SQL_SUCCESS) {
		// hide data truncated ...
		if (std::strncmp((char*)state, "01004", SQL_SQLSTATE_SIZE))
			std::cerr << "Error: " << state << "," << message << ":" << error << std::endl;
	}
}

// call ODBC functions and report an error on failure
void check_error(SQLHANDLE handle, SQLSMALLINT type, RETCODE code)
{
	if (code != SQL_SUCCESS)
		handle_diagnostic_record(handle, type, code);

	if (code == SQL_ERROR) {
		std::cerr << "Error: code: " << code << std::endl;
		std::exit(1);
	}
}

} // namespace

int test_sqlserver_odbc()
{
	// allocate an environment
	SQLHENV henv{ nullptr };
	auto ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	if ( ret == SQL_ERROR) {
		std::cerr << "Error: Unable to allocate an environment handle" << std::endl;
		return -1;
	}

	// register this as an application that expects 3.x behavior, you must register something if you use AllocHandle
	check_error(henv, SQL_HANDLE_ENV, SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3, 0));

	// allocate a connection
	SQLHDBC hdbc{ nullptr };
	check_error(henv, SQL_HANDLE_ENV, SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc));

	// connect to the driver.use the connection string if supplied on the input,otherwise let the driver manager prompt for input
	//check_error(hdbc, SQL_HANDLE_DBC, SQLDriverConnect(hdbc, GetDesktopWindow(), (SQLCHAR*)"", SQL_NTS, nullptr, 0, nullptr, SQL_DRIVER_COMPLETE));
	check_error(hdbc, SQL_HANDLE_DBC, SQLConnect(hdbc, (SQLCHAR*)"TestODBC", SQL_NTS, (SQLCHAR*)"sa", SQL_NTS, (SQLCHAR*)"spring", SQL_NTS));
	
	SQLHSTMT hstmt{ nullptr };
	check_error(hdbc, SQL_HANDLE_DBC, SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt));

	// insert operation
	SQLCHAR sql1[] = "INSERT INTO student VALUES(1111, 'Sam', 'man', 16, '2000-12-15 08:00')";
	check_error(hstmt, SQL_HANDLE_STMT, SQLPrepare(hstmt, sql1, SQL_NTS));
	check_error(hstmt, SQL_HANDLE_STMT, SQLExecute(hstmt));

	SQLCHAR sql2[] = "INSERT INTO student VALUES(1112, '小李', '女', 22, '2010-12-15 08:00')";
	check_error(hstmt, SQL_HANDLE_STMT, SQLPrepare(hstmt, sql2, SQL_NTS));
	check_error(hstmt, SQL_HANDLE_STMT, SQLExecute(hstmt));

	// delete operation
	SQLCHAR sql5[] = "DELETE FROM student WHERE id = 1111";
	check_error(hstmt, SQL_HANDLE_STMT, SQLPrepare(hstmt, sql5, SQL_NTS));
	check_error(hstmt, SQL_HANDLE_STMT, SQLExecute(hstmt));

	// query operation
	SQLCHAR sql3[] = "SELECT * FROM student WHERE age > 20;";
	check_error(hstmt, SQL_HANDLE_STMT, SQLExecDirect(hstmt, sql3, SQL_NTS));

	int id{ 0 };
	char name[32] = { 0 };
	char sex[16] = { 0 };
    int age{ 0 };
	char brith[32] = { 0 };

	SQLLEN len = SQL_NTS;
	check_error(hstmt, SQL_HANDLE_STMT, SQLBindCol(hstmt, 1, SQL_INTEGER, &id, sizeof(id), 0));
	check_error(hstmt, SQL_HANDLE_STMT, SQLBindCol(hstmt, 2, SQL_CHAR, &name, sizeof(name), &len));
	check_error(hstmt, SQL_HANDLE_STMT, SQLBindCol(hstmt, 3, SQL_CHAR, &sex, sizeof(sex), &len));
	check_error(hstmt, SQL_HANDLE_STMT, SQLBindCol(hstmt, 4, SQL_INTEGER, &age, sizeof(age), 0));
	check_error(hstmt, SQL_HANDLE_STMT, SQLBindCol(hstmt, 5, SQL_CHAR, &brith, sizeof(brith), &len));

	ret = SQLFetch(hstmt);
	while (ret != SQL_NO_DATA) {
		std::cout << id << "\t" << name << "\t" << sex << "\t" << age << "\t" << brith << std::endl;

		id = 0;
		std::memset(name, 0, 32);
		std::memset(sex, 0, 16);
		age = 0;
		std::memset(brith, 0, 32);

		ret = SQLFetch(hstmt);
	}

	// delete operation
	if (hstmt)
		check_error(hdbc, SQL_HANDLE_DBC, SQLFreeHandle(SQL_HANDLE_STMT, hstmt));
	check_error(hdbc, SQL_HANDLE_DBC, SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt));

	SQLCHAR sql4[] = "DELETE FROM student WHERE id = 1112";
	check_error(hstmt, SQL_HANDLE_STMT, SQLPrepare(hstmt, sql4, SQL_NTS));
	check_error(hstmt, SQL_HANDLE_STMT, SQLExecute(hstmt));

	// update operation
	SQLCHAR sql6[] = "UPDATE student SET name = '小田' WHERE id = 1003";
	check_error(hstmt, SQL_HANDLE_STMT, SQLPrepare(hstmt, sql6, SQL_NTS));
	check_error(hstmt, SQL_HANDLE_STMT, SQLExecute(hstmt));

	// free ODBC handles
	if (hstmt)
		check_error(hdbc, SQL_HANDLE_DBC, SQLFreeHandle(SQL_HANDLE_STMT, hstmt));

	if (hdbc) {
		check_error(hdbc, SQL_HANDLE_DBC, SQLDisconnect(hdbc));
		check_error(hdbc, SQL_HANDLE_DBC, SQLFreeHandle(SQL_HANDLE_DBC, hdbc));
	}

	if (henv)
		check_error(hdbc, SQL_HANDLE_ENV, SQLFreeHandle(SQL_HANDLE_ENV, henv));

	return 0;
}

#endif // _MSC_VER
