#include "syncstream.hpp"
#include <iostream>
#include <syncstream>
#include <fstream>
#include <thread>
#include <vector>

// Blog: https://blog.csdn.net/fengbingchun/article/details/143082575

namespace {

void func1(int id, std::ostream& sync_out)
{
	std::osyncstream sync_stream(sync_out);
	sync_stream << "thread " << id << " is running" << std::endl;
}

void func2(int id, std::ostream& out)
{
	out << "thread " << id << " is running" << std::endl;
}

void sync(std::ofstream& file_out)
{
	std::syncbuf sync_buf(file_out.rdbuf());
	std::ostream sync_out(&sync_buf);

	constexpr int num_threads{ 10 };
	std::vector<std::thread> threads;

	for (int i = 0; i < num_threads; ++i)
		threads.emplace_back(func1, i, std::ref(sync_out));

	for (auto& t : threads)
		t.join();
}

void common(std::ofstream& file_out)
{
	constexpr int num_threads{ 10 };
	std::vector<std::thread> threads;

	for (int i = 0; i < num_threads; ++i)
		threads.emplace_back(func2, i, std::ref(file_out));

	for (auto& t : threads)
		t.join();
}

} // namespace

int test_syncstream()
{
#ifdef _MSC_VER
	std::ofstream file_out1("../../../testdata/output1.txt");
	std::ofstream file_out2("../../../testdata/output2.txt");
#else
	std::ofstream file_out1("testdata/output1.txt");
	std::ofstream file_out2("testdata/output2.txt");
#endif

	if (!file_out1 || ! file_out2) {
		std::cerr << "fail to open file for writing" << std::endl;
		return -1;
	}

	sync(file_out1);
	common(file_out2);

	file_out1.close();
	file_out2.close();
	return 0;
}

