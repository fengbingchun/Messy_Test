#include "funset.hpp"
#include <iostream>
#include "Condition.hpp"
#include "Thread.h"
#include "ThreadPool.h"

// Blog: https://blog.csdn.net/fengbingchun/article/details/128889558

int test_threadpool_1()
{
	eterfree::Thread thread;
	std::cout << thread.getID() << std::endl;

	thread.configure([] { std::cout << "Eterfree" << std::endl; }, nullptr);
	std::cout << std::boolalpha << thread.notify() << std::endl;
	thread.destroy();

	thread.create();
	std::cout << thread.getID() << std::endl;

	thread.configure([] { std::cout << "solifree" << std::endl; }, nullptr);
	std::cout << std::boolalpha << thread.notify() << std::endl;
	thread.destroy();

	return 0;
}

namespace {

std::atomic<bool> valid = true;
eterfree::Condition condition;

void task()
{
	condition.wait([] {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "this thread id: " << std::this_thread::get_id() << std::endl;
		return !valid.load(std::memory_order_relaxed);
	});
}

void print(const eterfree::ThreadPool& threadPool)
{
	auto proxy = threadPool.getProxy();
	std::cout << proxy.getCapacity() << ' ' \
		<< proxy.getTotalSize() << ' ' \
		<< proxy.getIdleSize() << ' ' \
		<< proxy.getTaskSize() << std::endl;
}

} // namespace

int test_threadpool_2()
{
	eterfree::ThreadPool threadPool;
	auto proxy = threadPool.getProxy();
	auto capacity = proxy.getCapacity();
	for (decltype(capacity) index = 0; index < capacity; ++index)
		proxy.pushTask(task);

	std::this_thread::sleep_for(std::chrono::seconds(2));
	print(threadPool);

	proxy.pushTask([] {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "this thread id: " << std::this_thread::get_id() << std::endl;
		std::cout << "eterfree::ThreadPool" << std::endl;
	});

	std::this_thread::sleep_for(std::chrono::seconds(1));
	print(threadPool);

	proxy.setCapacity(capacity + 1);

	std::this_thread::sleep_for(std::chrono::seconds(2));
	print(threadPool);

	valid.store(false, std::memory_order_relaxed);
	condition.exit();

	return 0;
}
