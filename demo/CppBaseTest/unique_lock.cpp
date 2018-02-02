#include "unique_lock.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78638138

namespace unique_lock_ {

//////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/mutex/unique_lock/unique_lock/
namespace {
std::mutex foo, bar;

void task_a()
{
	std::lock(foo, bar);         // simultaneous lock (prevents deadlock)
	std::unique_lock<std::mutex> lck1(foo, std::adopt_lock);
	std::unique_lock<std::mutex> lck2(bar, std::adopt_lock);
	std::cout << "task a\n";
	// (unlocked automatically on destruction of lck1 and lck2)
}

void task_b()
{
	// unique_lock::unique_lock: Constructs a unique_lock
	// foo.lock(); bar.lock(); // replaced by:
	std::unique_lock<std::mutex> lck1, lck2;
	lck1 = std::unique_lock<std::mutex>(bar, std::defer_lock);
	lck2 = std::unique_lock<std::mutex>(foo, std::defer_lock);
	std::lock(lck1, lck2);       // simultaneous lock (prevents deadlock)
	std::cout << "task b\n";
	// (unlocked automatically on destruction of lck1 and lck2)
}
}

int test_unique_lock_1()
{
	std::thread th1(task_a);
	std::thread th2(task_b);

	th1.join();
	th2.join();

	return 0;
}

/////////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/mutex/unique_lock/lock/
namespace {
std::mutex mtx;           // mutex for critical section

void print_thread_id(int id) {
	std::unique_lock<std::mutex> lck(mtx, std::defer_lock);
	// critical section (exclusive access to std::cout signaled by locking lck):
	// unique_lock::lock: Calls member lock of the managed mutex object.
	lck.lock();
	std::cout << "thread #" << id << '\n';
	// unique_lock::unlock: Calls member unlock of the managed mutex object, and sets the owning state to false
	lck.unlock();
}
}

int test_unique_lock_2()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(print_thread_id, i + 1);

	for (auto& th : threads) th.join();

	return 0;
}

//////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/mutex/unique_lock/mutex/
namespace {
class MyMutex : public std::mutex {
	int _id;
public:
	MyMutex(int id) : _id(id) {}
	int id() { return _id; }
};

MyMutex mtx3(101);

void print_ids(int id) {
	std::unique_lock<MyMutex> lck(mtx3);
	// unique_lock::mutex: Returns a pointer to the managed mutex object
	std::cout << "thread #" << id << " locked mutex " << lck.mutex()->id() << '\n';
}
}

int test_unique_lock_3()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(print_ids, i + 1);

	for (auto& th : threads) th.join();

	return 0;
}

//////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/mutex/unique_lock/operator=/
namespace {
std::mutex mtx4;           // mutex for critical section

void print_fifty(char c) {
	std::unique_lock<std::mutex> lck;         // default-constructed
	// unique_lock::operator=: Replaces the managed mutex object by the one in x, including its owning state
	lck = std::unique_lock<std::mutex>(mtx4);  // move-assigned
	for (int i = 0; i<50; ++i) { std::cout << c; }
	std::cout << '\n';
}
}

int test_unique_lock_4()
{
	std::thread th1(print_fifty, '*');
	std::thread th2(print_fifty, '$');

	th1.join();
	th2.join();

	return 0;
}

///////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/mutex/unique_lock/operator_bool/
namespace {
std::mutex mtx5;           // mutex for critical section

void print_star() {
	std::unique_lock<std::mutex> lck(mtx5, std::try_to_lock);
	// print '*' if successfully locked, 'x' otherwise:
	// unique_lock::operator bool: Return whether it owns a lock
	if (lck)
		std::cout << '*';
	else
		std::cout << 'x';
}
}

int test_unique_lock_5()
{
	std::vector<std::thread> threads;
	for (int i = 0; i<500; ++i)
		threads.emplace_back(print_star);

	for (auto& x : threads) x.join();

	return 0;
}

///////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/mutex/unique_lock/owns_lock/
namespace {
std::mutex mtx6;           // mutex for critical section

void print_star6() {
	std::unique_lock<std::mutex> lck(mtx6, std::try_to_lock);
	// print '*' if successfully locked, 'x' otherwise:
	// unique_lock::owns_lock: Returns whether the object owns a lock.
	if (lck.owns_lock())
		std::cout << '*';
	else
		std::cout << 'x';
}
}

int test_unique_lock_6()
{
	std::vector<std::thread> threads;
	for (int i = 0; i<500; ++i)
		threads.emplace_back(print_star6);

	for (auto& x : threads) x.join();

	return 0;
}


//////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/mutex/unique_lock/release/
namespace {
std::mutex mtx7;
int count = 0;

void print_count_and_unlock(std::mutex* p_mtx) {
	std::cout << "count: " << count << '\n';
	p_mtx->unlock();
}

void task() {
	std::unique_lock<std::mutex> lck(mtx7);
	++count;
	// unique_lock::release: Returns a pointer to the managed mutex object, releasing ownership over it
	print_count_and_unlock(lck.release());
}
}

int test_unique_lock_7()
{
	std::vector<std::thread> threads;
	for (int i = 0; i<10; ++i)
		threads.emplace_back(task);

	for (auto& x : threads) x.join();

	return 0;
}

/////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/mutex/unique_lock/try_lock/
namespace {
std::mutex mtx8;           // mutex for critical section

void print_star8() {
	std::unique_lock<std::mutex> lck(mtx8, std::defer_lock);
	// print '*' if successfully locked, 'x' otherwise:
	// unique_lock::try_lock: Lock mutex if not locked
	// true if the function succeeds in locking the managed mutex object, false otherwise.
	if (lck.try_lock())
		std::cout << '*';
	else
		std::cout << 'x';
}
}

int test_unique_lock_8()
{
	std::vector<std::thread> threads;
	for (int i = 0; i<500; ++i)
		threads.emplace_back(print_star8);

	for (auto& x : threads) x.join();

	return 0;
}

/////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/mutex/unique_lock/try_lock_for/
namespace {
std::timed_mutex mtx9;

void fireworks() {
	std::unique_lock<std::timed_mutex> lck(mtx9, std::defer_lock);
	// waiting to get a lock: each thread prints "-" every 200ms:
	// unique_lock::try_lock_for: Try to lock mutex during time span
	while (!lck.try_lock_for(std::chrono::milliseconds(200))) {
		std::cout << "-";
	}
	// got a lock! - wait for 1s, then this thread prints "*"
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "*\n";
}
}

int test_unique_lock_9()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(fireworks);

	for (auto& th : threads) th.join();

	return 0;
}

/////////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/thread/unique_lock
namespace {
struct Box {
	explicit Box(int num) : num_things{ num } {}

	int num_things;
	std::mutex m;
};

void transfer(Box& from, Box& to, int num)
{
	// don't actually take the locks yet
	std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
	std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);

	// lock both unique_locks without deadlock
	std::lock(lock1, lock2);

	from.num_things -= num;
	to.num_things += num;

	// 'from.m' and 'to.m' mutexes unlocked in 'unique_lock' dtors
}
}

int test_unique_lock_10()
{
	Box acc1(100);
	Box acc2(50);

	std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
	std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);

	t1.join();
	t2.join();

	return 0;
}

} // namespace unique_lock_

