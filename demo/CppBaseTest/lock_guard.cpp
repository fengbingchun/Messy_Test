#include "lock_guard.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <stdexcept>
#include <list>
#include <algorithm>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78649260

namespace lock_guard_ {

///////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/mutex/lock_guard/
namespace {
std::mutex mtx;

void print_even(int x) {
	if (x % 2 == 0) std::cout << x << " is even\n";
	else throw (std::logic_error("not even"));
}

void print_thread_id(int id) {
	try {
		// using a local lock_guard to lock mtx guarantees unlocking on destruction / exception:
		std::lock_guard<std::mutex> lck(mtx);
		print_even(id);
	} catch (std::logic_error&) {
		std::cout << "[exception caught]\n";
	}
}
}

int test_lock_guard_1()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(print_thread_id, i + 1);

	for (auto& th : threads) th.join();

	return 0;
}

///////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/mutex/lock_guard/lock_guard/
namespace {
std::mutex mtx2;           // mutex for critical section

void print_thread_id2(int id) {
	mtx2.lock();
	std::lock_guard<std::mutex> lck(mtx2, std::adopt_lock);
	std::cout << "thread #" << id << '\n';
}
}

int test_lock_guard_2()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(print_thread_id2, i + 1);

	for (auto& th : threads) th.join();

	return 0;
}

////////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/thread/lock_guard
namespace {
int g_i = 0;
std::mutex g_i_mutex;  // protects g_i

void safe_increment()
{
	std::lock_guard<std::mutex> lock(g_i_mutex);
	++g_i;

	std::cout << std::this_thread::get_id() << ": " << g_i << '\n';

	// g_i_mutex is automatically released when lock goes out of scope
}
}

int test_lock_guard_3()
{
	std::cout << "main: " << g_i << '\n';

	std::thread t1(safe_increment);
	std::thread t2(safe_increment);

	t1.join();
	t2.join();

	std::cout << "main: " << g_i << '\n';

	return 0;
}

//////////////////////////////////////////////////////////////////////
// reference: http://www.bogotobogo.com/cplusplus/C11/7_C11_Thread_Sharing_Memory.php
namespace {
// a global variable
std::list<int> myList;

// a global instance of std::mutex to protect global variable
std::mutex myMutex;

void addToList(int max, int interval)
{
	// the access to this function is mutually exclusive
	std::lock_guard<std::mutex> guard(myMutex);
	for (int i = 0; i < max; i++) {
		if ((i % interval) == 0) myList.push_back(i);
	}
}

void printList()
{
	// the access to this function is mutually exclusive
	std::lock_guard<std::mutex> guard(myMutex);
	for (auto itr = myList.begin(), end_itr = myList.end(); itr != end_itr; ++itr) {
		std::cout << *itr << ",";
	}
}
}
int test_lock_guard_4()
{
	int max = 100;

	std::thread t1(addToList, max, 1);
	std::thread t2(addToList, max, 10);
	std::thread t3(printList);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}

} // namespace lock_guard_

