#include "call_once.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <future>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78681323

/*
template< class Callable, class... Args >
void call_once( std::once_flag& flag, Callable&& f, Args&&... args );

Calls fn passing args as arguments, unless another thread has already executed
(or is currently executing) a call to call_once with the same flag.

If another thread is already actively executing a call to call_once with the same flag,
it causes a passive execution: Passive executions do not call fn but do not return until
the active execution itself has returned, and all visible side effects are synchronized at
that point among all concurrent calls to this function with the same flag.

If an active call to call_once ends by throwing an exception (which is propagated
to its calling thread) and passive executions exist, one is selected among these
passive executions, and called to be the new active call instead.

Note that once an active execution has returned, all current passive executions
and future calls to call_once (with the same flag) also return without becoming active executions.

The active execution uses decay copies of the lvalue or rvalue references of fn and args,
ignoring the value returned by fn.
*/

namespace call_once_ {
/////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/thread/call_once
namespace {
std::once_flag flag1, flag2;

void simple_do_once()
{
	std::call_once(flag1, [](){ std::cout << "Simple example: called once\n"; });
}

void may_throw_function(bool do_throw)
{
	if (do_throw) {
		std::cout << "throw: call_once will retry\n"; // this may appear more than once
		throw std::exception();
	}
	std::cout << "Didn't throw, call_once will not attempt again\n"; // guaranteed once
}

void do_once(bool do_throw)
{
	try {
		std::call_once(flag2, may_throw_function, do_throw);
	}
	catch (...) {
	}
}
}

int test_call_once_1()
{
	std::thread st1(simple_do_once);
	std::thread st2(simple_do_once);
	std::thread st3(simple_do_once);
	std::thread st4(simple_do_once);
	st1.join();
	st2.join();
	st3.join();
	st4.join();

	/*std::thread t1(do_once, true);
	std::thread t2(do_once, true);
	std::thread t3(do_once, false);
	std::thread t4(do_once, true);
	t1.join();
	t2.join();
	t3.join();
	t4.join();*/

	return 0;
}

///////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/mutex/call_once/
namespace {
int winner;
void set_winner(int x) { winner = x; }
std::once_flag winner_flag;

void wait_1000ms(int id) {
	// count to 1000, waiting 1ms between increments:
	for (int i = 0; i<1000; ++i)
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	// claim to be the winner (only the first such call is executed):
	std::call_once(winner_flag, set_winner, id);
}
}

int test_call_once_2()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(wait_1000ms, i + 1);

	std::cout << "waiting for the first among 10 threads to count 1000 ms...\n";

	for (auto& th : threads) th.join();
	std::cout << "winner thread: " << winner << '\n';

	return 0;
}

////////////////////////////////////////////////////////////////////
// reference: http://www.modernescpp.com/index.php/thread-safe-initialization-of-a-singleton
namespace {
/*constexpr*/const auto tenMill = 10000;

class MySingleton{
public:
	static MySingleton& getInstance(){
		std::call_once(initInstanceFlag, &MySingleton::initSingleton);
		// volatile int dummy{};
		return *instance;
	}
private:
	MySingleton() = default;
	~MySingleton() = default;
	MySingleton(const MySingleton&) = delete;
	MySingleton& operator=(const MySingleton&) = delete;

	static MySingleton* instance;
	static std::once_flag initInstanceFlag;

	static void initSingleton(){
		instance = new MySingleton;
	}
};

MySingleton* MySingleton::instance = nullptr;
std::once_flag MySingleton::initInstanceFlag;

std::chrono::duration<double> getTime(){

	auto begin = std::chrono::system_clock::now();
	for (size_t i = 0; i <= tenMill; ++i){
		MySingleton::getInstance();
	}
	return std::chrono::system_clock::now() - begin;

};
}

int test_call_once_3()
{
	auto fut1 = std::async(std::launch::async, getTime);
	auto fut2 = std::async(std::launch::async, getTime);
	auto fut3 = std::async(std::launch::async, getTime);
	auto fut4 = std::async(std::launch::async, getTime);

	auto total = fut1.get() + fut2.get() + fut3.get() + fut4.get();

	std::cout << total.count() << std::endl;

	return 0;
}

} // namespace call_once_

