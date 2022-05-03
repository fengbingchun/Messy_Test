#ifndef FBC_CPP_BASE_TEST_FUNSET_HPP_
#define FBC_CPP_BASE_TEST_FUNSET_HPP_

namespace common {

namespace internal {
	char* name();
} // namespace internal

} // namesapce common

int test_namespace_detail_internal();
int test_load_big_file();
int test_process_programming_1();
int get_mac_and_cpuid();
int test_thread_local_1();

#endif // FBC_CPP_BASE_TEST_FUNSET_HPP_
