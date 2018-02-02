#include "condition_variable.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

// Blog: http://blog.csdn.net/fengbingchun/article/details/73695596

namespace condition_variable_ {

//////////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/condition_variable/condition_variable/
std::mutex mtx;
std::condition_variable cv;
bool ready = false;

static void print_id(int id)
{
	std::unique_lock<std::mutex> lck(mtx);
	while (!ready) cv.wait(lck);
	// ...
	std::cout << "thread " << id << '\n';
}

static void go()
{
	std::unique_lock<std::mutex> lck(mtx);
	ready = true;
	cv.notify_all();
}

int test_condition_variable_1()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(print_id, i);

	std::cout << "10 threads ready to race...\n";
	go();                       // go!

	for (auto& th : threads) th.join();

	return 0;
}

/////////////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/condition_variable/condition_variable/wait/
// condition_variable::wait: Wait until notified,
// The execution of the current thread (which shall have locked lck's mutex) is blocked until notified.
// At the moment of blocking the thread, the function automatically calls lck.unlock(), allowing other locked threads to continue.
// If pred is specified, the function only blocks if pred returns false,
// and notifications can only unblock the thread when it becomes true (which is specially useful to check against spurious wake-up calls).
std::mutex mtx2;
std::condition_variable cv2;

int cargo = 0;
static bool shipment_available() { return cargo != 0; }

static void consume(int n)
{
	for (int i = 0; i<n; ++i) {
		std::unique_lock<std::mutex> lck(mtx2);
		cv2.wait(lck, shipment_available);
		// consume:
		std::cout << cargo << '\n';
		cargo = 0;
		std::cout << "****: " << cargo << std::endl;
	}
}

int test_condition_variable_wait()
{
	std::thread consumer_thread(consume, 10);

	// produce 10 items when needed:
	for (int i = 0; i<10; ++i) {
		while (shipment_available()) std::this_thread::yield();
		std::unique_lock<std::mutex> lck(mtx2);
		cargo = i + 1;
		cv2.notify_one();
	}

	consumer_thread.join();

	return 0;
}

///////////////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/condition_variable/condition_variable/wait_for/
// condition_variable::wait_for: Wait for timeout or until notified
// The execution of the current thread (which shall have locked lck's mutex) is blocked during rel_time,
// or until notified (if the latter happens first).
// At the moment of blocking the thread, the function automatically calls lck.unlock(),
// allowing other locked threads to continue.
std::condition_variable cv3;
int value;

static void read_value()
{
	std::cin >> value;
	cv3.notify_one();
}

int test_condition_variable_wait_for()
{
	std::cout << "Please, enter an integer (I'll be printing dots): \n";
	std::thread th(read_value);

	std::mutex mtx;
	std::unique_lock<std::mutex> lck(mtx);
	while (cv3.wait_for(lck, std::chrono::seconds(1)) == std::cv_status::timeout) {
		std::cout << '.' << std::endl;
	}
	std::cout << "You entered: " << value << '\n';

	th.join();

	return 0;
}

//////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/condition_variable/condition_variable/notify_one/
// condition_variable::notify_one: Notify one, Unblocks one of the threads currently waiting for this condition.
// If no threads are waiting, the function does nothing.
// If more than one, it is unspecified which of the threads is selected.
std::mutex mtx4;
std::condition_variable produce4, consume4;

int cargo4 = 0;     // shared value by producers and consumers

static void consumer4()
{
	std::unique_lock<std::mutex> lck(mtx4);
	while (cargo4 == 0) consume4.wait(lck);
	std::cout << cargo4 << '\n';
	cargo4 = 0;
	produce4.notify_one();
}

static void producer(int id)
{
	std::unique_lock<std::mutex> lck(mtx4);
	while (cargo4 != 0) produce4.wait(lck);
	cargo4 = id;
	consume4.notify_one();
}

int test_condition_variable_notify_one()
{
	std::thread consumers[10], producers[10];
	// spawn 10 consumers and 10 producers:
	for (int i = 0; i<10; ++i) {
		consumers[i] = std::thread(consumer4);
		producers[i] = std::thread(producer, i + 1);
	}

	// join them back:
	for (int i = 0; i<10; ++i) {
		producers[i].join();
		consumers[i].join();
	}

	return 0;
}

/////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/condition_variable/condition_variable/notify_all/
// condition_variable::notify_all: Notify all, Unblocks all threads currently waiting for this condition.
// If no threads are waiting, the function does nothing.
std::mutex mtx5;
std::condition_variable cv5;
bool ready5 = false;

static void print_id5(int id) {
	std::unique_lock<std::mutex> lck(mtx5);
	while (!ready5) cv5.wait(lck);
	// ...
	std::cout << "thread " << id << '\n';
}

static void go5()
{
	std::unique_lock<std::mutex> lck(mtx5);
	ready5 = true;
	cv5.notify_all();
}

int test_condition_variable_notify_all()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(print_id5, i);

	std::cout << "10 threads ready to race...\n";
	go5();                       // go!

	for (auto& th : threads) th.join();

	return 0;
}

////////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/thread/condition_variable
std::mutex m;
std::condition_variable cv6;
std::string data;
bool ready6 = false;
bool processed = false;

static void worker_thread()
{
	// Wait until main() sends data
	std::unique_lock<std::mutex> lk(m);
	cv6.wait(lk, []{return ready6; });

	// after the wait, we own the lock.
	std::cout << "Worker thread is processing data\n";
	data += " after processing";

	// Send data back to main()
	processed = true;
	std::cout << "Worker thread signals data processing completed\n";

	// Manual unlocking is done before notifying, to avoid waking up
	// the waiting thread only to block again (see notify_one for details)
	lk.unlock();
	cv6.notify_one();
}

int test_condition_variable_2()
{
	std::thread worker(worker_thread);

	data = "Example data";
	// send data to the worker thread
	{
		std::lock_guard<std::mutex> lk(m);
		ready6 = true;
		std::cout << "main() signals data ready for processing\n";
	}
	cv6.notify_one();

	// wait for the worker
	{
		std::unique_lock<std::mutex> lk(m);
		cv6.wait(lk, []{return processed; });
	}
	std::cout << "Back in main(), data = " << data << '\n';

	worker.join();

	return 0;
}

} // namespace condition_variable_
