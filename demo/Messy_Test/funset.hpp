#ifndef FBC_MESSY_TEST_FUNSET_HPP_
#define FBC_MESSY_TEST_FUNSET_HPP_

// SQL Server ODBC
int test_sqlserver_odbc();

// ThreadPool
int test_threadpool_1();
int test_threadpool_2();

// jemalloc
int test_jemalloc();

// tinyxml2
int test_tinyxml2_create();
int test_tinyxml2_parse();

// libuuid
int test_libuuid(); // generate uuid

// yaml-cpp
int test_parse_yaml_file(); // read yaml file
int test_generate_yaml_file(); // write yaml file

// rapidjson
int test_rapidjson_parse(); // parse json file
int test_rapidjson_write(); // write json file

#endif // FBC_MESSY_TEST_FUNSET_HPP_
