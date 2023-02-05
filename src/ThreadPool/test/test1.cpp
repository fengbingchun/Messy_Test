#define ETERFREE
#define BOOST
//#define FILE_STREAM
//#define FILE_SYSTEM

#if defined ETERFREE
#include "ThreadPool.h"
#elif defined BOOST
#include <threadpool/threadpool.hpp>
#endif

#include <cstdlib>
#include <utility>
#include <chrono>
#include <iostream>
#include <atomic>
#include <thread>

#ifdef FILE_STREAM
#include <fstream>

#ifdef FILE_SYSTEM
#include <filesystem>
#endif
#endif

static std::atomic_ulong counter = 0;

static void task()
{
	for (volatile auto index = 0UL; index < 10000UL; ++index);
	std::this_thread::sleep_for(std::chrono::milliseconds(3));
	counter.fetch_add(1, std::memory_order_relaxed);
}

#if defined ETERFREE
using ThreadPool = eterfree::ThreadPool;

static void execute(ThreadPool& _threadPool)
{
	auto proxy = _threadPool.getProxy();
	for (auto index = 0UL; index < 20000UL; ++index)
		proxy.pushTask(task);

	ThreadPool::TaskQueue taskQueue;
	for (auto index = 0UL; index < 30000UL; ++index)
		taskQueue.push_back(task);
	proxy.pushTask(std::move(taskQueue));
}

static void terminate(ThreadPool&& _threadPool)
{
	_threadPool.clearTask();
	auto threadPool(std::forward<ThreadPool>(_threadPool));
	(void)threadPool;
}

#elif defined BOOST
static auto getConcurrency() noexcept
{
	auto concurrency = std::thread::hardware_concurrency();
	return concurrency > 0 ? \
		concurrency : static_cast<decltype(concurrency)>(1);
}

using ThreadPool = boost::threadpool::thread_pool<>;

static void execute(ThreadPool& _threadPool)
{
	for (auto index = 0UL; index < 20000UL; ++index)
		_threadPool.schedule(task);

	for (auto index = 0UL; index < 30000UL; ++index)
		_threadPool.schedule(task);
}

static void terminate(ThreadPool&& _threadPool)
{
	auto threadPool(std::forward<ThreadPool>(_threadPool));
	(void)threadPool;
}
#endif

int main()
{
	using std::cout, std::endl;

	constexpr auto load = []() noexcept
	{ return counter.load(std::memory_order_relaxed); };

#ifdef FILE_STREAM
	constexpr auto FILE = "ThreadPool.log";

#ifdef FILE_SYSTEM
	std::filesystem::remove(FILE);
#endif

	std::ofstream ofs(FILE, std::ios::app);
	auto os = cout.rdbuf(ofs.rdbuf());
#endif

#if defined ETERFREE
	ThreadPool threadPool;
#elif defined BOOST
	ThreadPool threadPool(getConcurrency());
#endif

	using namespace std::chrono;
	auto begin = system_clock::now();

	execute(threadPool);
	std::this_thread::sleep_for(seconds(10));

	auto count = load();
	auto end = system_clock::now();
	auto duration = duration_cast<milliseconds>(end - begin);

	cout << "任务数量：" << count << endl;
	cout << "执行时间：" << duration.count() << endl;

#ifdef FILE_STREAM
	cout << endl;
	cout.rdbuf(os);
#endif

	terminate(std::move(threadPool));
	cout << "任务总数：" << load() << endl;
	return EXIT_SUCCESS;
}
