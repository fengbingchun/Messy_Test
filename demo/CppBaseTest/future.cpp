#include "future.hpp"
#include <iostream>
#include <future>
#include <chrono>
#include <utility>
#include <thread>

namespace future_ {

// Blog: https://blog.csdn.net/fengbingchun/article/details/104118831

///////////////////////////////////////////////////////////
// reference: https://en.cppreference.com/w/cpp/thread/shared_future
int test_shared_future_1()
{
	std::promise<void> ready_promise, t1_ready_promise, t2_ready_promise;
	// 通过std::future移动构造std::shared_future对象,t1_ready_promise和t2_ready_promise均会用到ready_future
	std::shared_future<void> ready_future(ready_promise.get_future());

	std::chrono::time_point<std::chrono::high_resolution_clock> start;

	auto fun1 = [&, ready_future]() -> std::chrono::duration<double, std::milli> {
			t1_ready_promise.set_value();
			ready_future.wait(); // waits for the signal from main()
			return std::chrono::high_resolution_clock::now() - start;
		};

	auto fun2 = [&, ready_future]() -> std::chrono::duration<double, std::milli> {
		t2_ready_promise.set_value();
		ready_future.wait(); // waits for the signal from main()
		return std::chrono::high_resolution_clock::now() - start;
	};

	auto fut1 = t1_ready_promise.get_future();
	auto fut2 = t2_ready_promise.get_future();

	auto result1 = std::async(std::launch::async, fun1);
	auto result2 = std::async(std::launch::async, fun2);

	// wait for the threads to become ready
	fut1.wait();
	fut2.wait();

	// the threads are ready, start the clock
	start = std::chrono::high_resolution_clock::now();

	// signal the threads to go
	ready_promise.set_value();

	std::cout << "Thread 1 received the signal " << result1.get().count() << " ms after start\n"
		<< "Thread 2 received the signal " << result2.get().count() << " ms after start\n";

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://en.cppreference.com/w/cpp/thread/shared_future/wait
int fib(int n)
{
	if (n < 3) return 1;
	else return fib(n - 1) + fib(n - 2);
}

int test_shared_future_2()
{
	// 将std::shared_future<int>调整为std::future<int>也是正确的
	std::shared_future<int> f1 = std::async(std::launch::async, []() { return fib(20); });
	std::shared_future<int> f2 = std::async(std::launch::async, []() { return fib(25); });

	std::cout << "waiting...\n";
	f1.wait();
	f2.wait();

	std::cout << "f1: " << f1.get() << '\n';
	std::cout << "f2: " << f2.get() << '\n';

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://en.cppreference.com/w/cpp/thread/shared_future/wait_for
int test_shared_future_3()
{
	// 将std::shared_future<int>调整为std::future<int>也是正确的
	std::shared_future<int> future = std::async(std::launch::async, [](){ 
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 8;  
    }); 
 
    std::cout << "waiting...\n";
    std::future_status status;
    do {
        status = future.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::deferred) {
            std::cout << "deferred\n";
        } else if (status == std::future_status::timeout) {
            std::cout << "timeout\n";
        } else if (status == std::future_status::ready) {
            std::cout << "ready!\n";
        }
    } while (status != std::future_status::ready); 
 
    std::cout << "result is " << future.get() << '\n';

	return 0;
}


// Blog: https://blog.csdn.net/fengbingchun/article/details/104115489

///////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/future/future/
int test_future_1()
{
{ // constructor/get/operator=
	auto get_value = []() { return 10; };
	std::future<int> foo; // default-constructed
	std::future<int> bar = std::async(get_value); // move-constructed

	int x = bar.get();
	std::cout << "value: " << x << '\n'; // 10

	//int x2 = bar.get(); // crash, 对于每个future的共享状态，get函数最多仅被调用一次
	//std::cout << "value: " << x2 << '\n';

	std::future<int> foo2(std::async(get_value));
	std::cout << "value: " << foo2.get() << '\n'; // 10
}

{ // share
	std::future<int> fut = std::async([]() { return 10; });
	std::shared_future<int> shfut = fut.share();

	//std::cout << "value: " << fut.get() << '\n'; // crash, 执行完fut.share()后，fut对象将变得无效
	std::cout << "fut valid: " << fut.valid() << '\n';// 0

	// shared futures can be accessed multiple times:
	std::cout << "value: " << shfut.get() << '\n'; // 10
	std::cout << "its double: " << shfut.get() * 2 << '\n'; // 20, 对于std::shared_future对象，get函数可以被多次访问
}

{ // valid
	std::future<int> foo, bar;
	foo = std::async([]() { return 10; });
	bar = std::move(foo);

	if (foo.valid()) std::cout << "foo's value: " << foo.get() << '\n';
	else std::cout << "foo is not valid\n"; // foo is not valid

	if (bar.valid()) std::cout << "bar's value: " << bar.get() << '\n'; // 10
	else std::cout << "bar is not valid\n";
}

{ // wait
	auto is_prime = [](int x) {
		for (int i = 2; i < x; ++i) if (x%i == 0) return false;
		return true;
	};

	// call function asynchronously:
	std::future<bool> fut = std::async(is_prime, 194232491);

	std::cout << "checking...\n";
	fut.wait();

	std::cout << "\n194232491 ";
	if (fut.get()) // guaranteed to be ready (and not block) after wait returns
		std::cout << "is prime.\n";
	else
		std::cout << "is not prime.\n";
}

{ // wait_for
	auto is_prime = [](int x) {
		for (int i = 2; i < x; ++i) if (x%i == 0) return false;
		return true;
	};

	// call function asynchronously:
	std::future<bool> fut = std::async(is_prime, 700020007);

	// do something while waiting for function to set future:
	std::cout << "checking, please wait";
	std::chrono::milliseconds span(100);
	while (fut.wait_for(span) == std::future_status::timeout) // 可能多次调用std::future::wait_for函数
		std::cout << '.';

	bool x = fut.get(); // retrieve return value
	std::cout << "\n700020007 " << (x ? "is" : "is not") << " prime.\n";
}

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://en.cppreference.com/w/cpp/thread/future
int test_future_2()
{
	// future from a packaged_task
	std::packaged_task<int()> task([] { return 7; }); // wrap the function
	std::future<int> f1 = task.get_future();  // get a future
	std::thread t(std::move(task)); // launch on a thread

	// future from an async()
	std::future<int> f2 = std::async(std::launch::async, [] { return 8; });

#ifdef _MSC_VER
	// future from a promise
	std::promise<int> p;
	std::future<int> f3 = p.get_future();
	std::thread([&p] { p.set_value_at_thread_exit(9); }).detach(); // gcc 4.9 don't support this function
#endif

	std::cout << "Waiting..." << std::flush;
	f1.wait();
	f2.wait();
#ifdef _MSC_VER
	f3.wait();
#endif
	std::cout << "Done!\nResults are: " << f1.get() << ' ' << f2.get() << ' '
#ifdef _MSC_VER
		<< f3.get()
#endif
		<< '\n';
	t.join();

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://thispointer.com/c11-multithreading-part-8-stdfuture-stdpromise-and-returning-values-from-thread/
void initiazer(std::promise<int> * promObj)
{
	std::cout << "Inside Thread" << std::endl;
	promObj->set_value(35);
}

int test_future_3()
{
	std::promise<int> promiseObj;
	std::future<int> futureObj = promiseObj.get_future();
	std::thread th(initiazer, &promiseObj);
	std::cout << "value: " << futureObj.get() << std::endl;
	th.join();

	// If std::promise object is destroyed before setting the value the calling get() function on associated std::future object will throw exception.
	// A part from this, if you want your thread to return multiple values at different point of time then
	// just pass multiple std::promise objects in thread and fetch multiple return values from thier associated multiple std::future objects.

	return 0;
}

} // namespace future_

