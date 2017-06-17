#include "thread2.hpp"
#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>
#include <iomanip>
#include <ctime>

///////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/thread/thread/thread/
std::atomic<int> global_counter(0);

static void increase_global(int n) { for (int i = 0; i<n; ++i) ++global_counter; }

static void increase_reference(std::atomic<int>& variable, int n) { for (int i = 0; i<n; ++i) ++variable; }

struct C : std::atomic<int> {
	C() : std::atomic<int>(0) {}
	void increase_member(int n) { for (int i = 0; i<n; ++i) fetch_add(1); }
};

int test_thread_thread()
{
	// thread::thread: Constructs a thread object
	std::vector<std::thread> threads;

	std::cout << "increase global counter with 10 threads...\n";
	for (int i = 1; i <= 10; ++i)
		threads.push_back(std::thread(increase_global, 1000));

	std::cout << "increase counter (foo) with 10 threads using reference...\n";
	std::atomic<int> foo(0);
	for (int i = 1; i <= 10; ++i)
		threads.push_back(std::thread(increase_reference, std::ref(foo), 1000));

	std::cout << "increase counter (bar) with 10 threads using member...\n";
	C bar;
	for (int i = 1; i <= 10; ++i)
		threads.push_back(std::thread(&C::increase_member, std::ref(bar), 1000));

	std::cout << "synchronizing all threads...\n";
	for (auto& th : threads) th.join();

	std::cout << "global_counter: " << global_counter << '\n';
	std::cout << "foo: " << foo << '\n';
	std::cout << "bar: " << bar << '\n';

	return 0;
}

////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/thread/thread/detach/
static void pause_thread(int n)
{
	std::this_thread::sleep_for(std::chrono::seconds(n));
	std::cout << "pause of " << n << " seconds ended\n";
}

int test_thread_detach()
{
	// thread::detach: Detaches the thread represented by the object from the calling thread,
	// allowing them to execute independently from each other.
	std::cout << "Spawning and detaching 3 threads...\n";
	std::thread(pause_thread, 1).detach();
	std::thread(pause_thread, 2).detach();
	std::thread(pause_thread, 3).detach();
	std::cout << "Done spawning threads.\n";

	std::cout << "(the main thread will now pause for 5 seconds)\n";
	// give the detached threads time to finish (but not guaranteed!):
	pause_thread(5);

	return 0;
}

//////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/thread/thread/get_id/
std::thread::id main_thread_id = std::this_thread::get_id();

static void is_main_thread()
{
	// this_thread::get_id: Returns the thread id of the calling thread.
	// This value uniquely identifies the thread.
	if (main_thread_id == std::this_thread::get_id())
		std::cout << "This is the main thread.\n";
	else
		std::cout << "This is not the main thread.\n";
}

int test_thread_get_id()
{
	// thread::get_id: Returns the thread id
	// If the thread object is joinable, the function returns a value that uniquely identifies the thread.
	// If the thread object is not joinable, the function returns a default - constructed object of member type thread::id.
	is_main_thread();
	std::thread th(is_main_thread);
	th.join();

	return 0;
}

/////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/thread/thread/join/
int test_thread_join()
{
	// thread::join: The function returns when the thread execution has completed.
	std::cout << "Spawning 3 threads...\n";
	std::thread t1(pause_thread, 1);
	std::thread t2(pause_thread, 2);
	std::thread t3(pause_thread, 3);
	std::cout << "Done spawning threads. Now waiting for them to join:\n";
	t1.join();
	t2.join();
	t3.join();
	std::cout << "All threads joined!\n";

	return 0;
}

///////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/thread/thread/joinable/
static void mythread()
{
	// do stuff...
}

int test_thread_joinable()
{
	// thread::joinable: Returns whether the thread object is joinable.
	// A thread object is joinable if it represents a thread of execution.
	std::thread foo;
	std::thread bar(mythread);

	std::cout << "Joinable after construction:\n" << std::boolalpha;
	std::cout << "foo: " << foo.joinable() << '\n';
	std::cout << "bar: " << bar.joinable() << '\n';

	if (foo.joinable()) foo.join();
	if (bar.joinable()) bar.join();

	std::cout << "Joinable after joining:\n" << std::boolalpha;
	std::cout << "foo: " << foo.joinable() << '\n';
	std::cout << "bar: " << bar.joinable() << '\n';

	return 0;
}

//////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/thread/thread/operator=/
int test_thread_operator()
{
	// thread::operator=: Move-assign thread
	// If the object is currently not joinable, it acquires the thread of execution represented by rhs(if any).
	// If it is joinable, terminate() is called.
	// After the call, rhs no longer represents any thread of execution(as if default - constructed).
	std::thread threads[5];                         // default-constructed threads

	std::cout << "Spawning 5 threads...\n";
	for (int i = 0; i<5; ++i)
		threads[i] = std::thread(pause_thread, i + 1);   // move-assign threads

	std::cout << "Done spawning threads. Now waiting for them to join:\n";
	for (int i = 0; i<5; ++i)
		threads[i].join();

	std::cout << "All threads joined!\n";

	return 0;
}

//////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/thread/this_thread/sleep_for/
int test_this_thread_sleep_for()
{
	// this_thread::sleep_for: Blocks execution of the calling thread during the span of time specified by rel_time.
	// The execution of the current thread is stopped until at least rel_time has passed from now.
	// Other threads continue their execution.
	std::cout << "countdown:\n";
	for (int i = 10; i>0; --i) {
		std::cout << i << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Lift off!\n";

	return 0;
}

/////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/thread/this_thread/sleep_until/
int test_this_thread_sleep_until()
{
	// this_thread::sleep_until: Blocks the calling thread until abs_time.
	// The execution of the current thread is stopped until at least abs_time, while other threads may continue to advance.
	using std::chrono::system_clock;
	std::time_t tt = system_clock::to_time_t(system_clock::now());

	struct std::tm * ptm = std::localtime(&tt);
	std::cout << "Current time: " << std::put_time(ptm, "%X") << '\n';

	std::cout << "Waiting for the next minute to begin...\n";
	++ptm->tm_min; ptm->tm_sec = 0;
	std::this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));

	std::cout << std::put_time(ptm, "%X") << " reached!\n";

	return 0;
}

/////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/thread/this_thread/yield/
std::atomic<bool> ready(false);

static void count1m(int id)
{
	while (!ready) {             // wait until main() sets ready...
		std::this_thread::yield();
	}
	for (volatile int i = 0; i<1000000; ++i) {}
	std::cout << id << std::endl;
}

int test_this_thread_yield()
{
	// this_thread::yield: The calling thread yields, offering the implementation the opportunity to reschedule.
	// This function shall be called when a thread waits for other threads to advance without blocking.
	std::thread threads[10];
	std::cout << "race of 10 threads that count to 1 million:\n";
	for (int i = 0; i<10; ++i) threads[i] = std::thread(count1m, i);
	ready = true;               // go!
	for (auto& th : threads) th.join();
	std::cout << '\n';

	return 0;
}
