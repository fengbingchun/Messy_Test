#include "mutex.hpp"
#include <iostream>
#include <mutex>
#include <thread>

// Blog: http://blog.csdn.net/fengbingchun/article/details/73521630

namespace mutex_ {

///////////////////////////////////////////////////////////
// refrence: http://www.cplusplus.com/reference/mutex/mutex/
std::mutex mtx;           // mutex for critical section

static void print_block(int n, char c)
{
	// critical section (exclusive access to std::cout signaled by locking mtx):
	mtx.lock();
	for (int i = 0; i<n; ++i) { std::cout << c; }
	std::cout << '\n';
	mtx.unlock();
}

int test_mutex_1()
{
	std::thread th1(print_block, 50, '*');
	std::thread th2(print_block, 50, '$');

	th1.join();
	th2.join();

	return 0;
}

//////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/mutex/mutex/lock/
static void print_thread_id(int id)
{
	// std::mutex::lock: The calling thread locks the mutex
	// std::mutex::unlock: Unlocks the mutex, releasing ownership over it.
	// critical section (exclusive access to std::cout signaled by locking mtx):
	mtx.lock();
	std::cout << "thread #" << id << '\n';
	mtx.unlock();
}

int test_mutex_2()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(print_thread_id, i + 1);

	for (auto& th : threads) th.join();

	return 0;
}

/////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/mutex/mutex/try_lock/
volatile int counter(0); // non-atomic counter

static void attempt_10k_increases()
{
	// std::mutex::try_lock: Lock mutex if not locked,
	// true if the function succeeds in locking the mutex for the thread, false otherwise.
	for (int i = 0; i<10000; ++i) {
		if (mtx.try_lock()) {   // only increase if currently not locked:
			++counter;
			mtx.unlock();
		}
	}
}

int test_mutex_3()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(attempt_10k_increases);

	for (auto& th : threads) th.join();
	std::cout << counter << " successful increases of the counter.\n";

	return 0;
}

} // namespace mutex_
