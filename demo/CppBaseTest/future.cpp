#include "future.hpp"
#include <iostream>
#include <future>
#include <chrono>
#include <utility>
#include <thread>
#include <functional>
#include <memory>
#include <exception> 
#include <numeric>
#include <vector>
#include <cmath>
#include <string>
#include <mutex>

namespace future_ {

// Blog: https://blog.csdn.net/fengbingchun/article/details/104133494

///////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/future/async/
int test_async_1()
{
	auto is_prime = [](int x) {
		std::cout << "Calculating. Please, wait...\n";
		for (int i = 2; i < x; ++i) if (x%i == 0) return false;
		return true;
	};

	// call is_prime(313222313) asynchronously:
	std::future<bool> fut = std::async(is_prime, 313222313);

	std::cout << "Checking whether 313222313 is prime.\n";
	// ...

	bool ret = fut.get(); // waits for is_prime to return
	if (ret) std::cout << "It is prime!\n";
	else std::cout << "It is not prime.\n";

	return 0;
}

///////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/future/launch/
int test_async_2()
{
	auto print_ten = [](char c, int ms) {
		for (int i = 0; i < 10; ++i) {
			std::this_thread::sleep_for(std::chrono::milliseconds(ms));
			std::cout << c;
		}
	};

	std::cout << "with launch::async:\n";
	std::future<void> foo = std::async(std::launch::async, print_ten, '*', 100);
	std::future<void> bar = std::async(std::launch::async, print_ten, '@', 200);
	// async "get" (wait for foo and bar to be ready):
	foo.get(); // 注：注释掉此句，也会输出'*'
	bar.get();
	std::cout << "\n\n";

	std::cout << "with launch::deferred:\n";
	foo = std::async(std::launch::deferred, print_ten, '*', 100);
	bar = std::async(std::launch::deferred, print_ten, '@', 200);
	// deferred "get" (perform the actual calls):
	foo.get(); // 注：注释掉此句，则不会输出'**********'
	bar.get();
	std::cout << '\n';

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://en.cppreference.com/w/cpp/thread/async
std::mutex m;

struct X {
	void foo(int i, const std::string& str) {
		std::lock_guard<std::mutex> lk(m);
		std::cout << str << ' ' << i << '\n';
	}
	void bar(const std::string& str) {
		std::lock_guard<std::mutex> lk(m);
		std::cout << str << '\n';
	}
	int operator()(int i) {
		std::lock_guard<std::mutex> lk(m);
		std::cout << i << '\n';
		return i + 10;
	}
};

template <typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end)
{
	auto len = end - beg;
	if (len < 1000)
		return std::accumulate(beg, end, 0);

	RandomIt mid = beg + len / 2;
	auto handle = std::async(std::launch::async, parallel_sum<RandomIt>, mid, end);
	int sum = parallel_sum(beg, mid);
	return sum + handle.get();
}

int test_async_3()
{
	std::vector<int> v(10000, 1);
	std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';

	X x;
	// Calls (&x)->foo(42, "Hello") with default policy:
	// may print "Hello 42" concurrently or defer execution
	auto a1 = std::async(&X::foo, &x, 42, "Hello");
	// Calls x.bar("world!") with deferred policy
	// prints "world!" when a2.get() or a2.wait() is called
	auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
	// Calls X()(43); with async policy
	// prints "43" concurrently
	auto a3 = std::async(std::launch::async, X(), 43);
	a2.wait();                     // prints "world!"
	std::cout << a3.get() << '\n'; // prints "53"

	return 0;
} // if a1 is not done at this point, destructor of a1 prints "Hello 42" here

///////////////////////////////////////////////////////////
// reference: https://thispointer.com/c11-multithreading-part-9-stdasync-tutorial-example/
int test_async_4()
{
	using namespace std::chrono;

	auto fetchDataFromDB = [](std::string recvdData) {
		// Make sure that function takes 5 seconds to complete
		std::this_thread::sleep_for(seconds(5));
		//Do stuff like creating DB Connection and fetching Data
		return "DB_" + recvdData;
	};

	auto fetchDataFromFile = [](std::string recvdData) {
		// Make sure that function takes 5 seconds to complete
		std::this_thread::sleep_for(seconds(5));
		//Do stuff like fetching Data File
		return "File_" + recvdData;
	};

	// Get Start Time
	system_clock::time_point start = system_clock::now();

	std::future<std::string> resultFromDB = std::async(std::launch::async, fetchDataFromDB, "Data");

	//Fetch Data from File
	std::string fileData = fetchDataFromFile("Data");

	//Fetch Data from DB
	// Will block till data is available in future<std::string> object.
	std::string dbData = resultFromDB.get();

	// Get End Time
	auto end = system_clock::now();
	auto diff = duration_cast <std::chrono::seconds> (end - start).count();
	std::cout << "Total Time Taken = " << diff << " Seconds" << std::endl;

	//Combine The Data
	std::string data = dbData + " :: " + fileData;
	//Printing the combined Data
	std::cout << "Data = " << data << std::endl;

	return 0;
}


// Blog: https://blog.csdn.net/fengbingchun/article/details/104127352

///////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/future/packaged_task/
int test_packaged_task_1()
{

{ // constructor/get_future/operator=/valid
	std::packaged_task<int(int)> foo; // default-constructed
	std::packaged_task<int(int)> bar([](int x) { return x * 2; }); // initialized

	foo = std::move(bar); // move-assignment
	std::cout << "valid: " << foo.valid() << "\n";
	std::future<int> ret = foo.get_future(); // get future
	std::thread(std::move(foo), 10).detach(); // spawn thread and call task

	int value = ret.get(); // wait for the task to finish and get result
	std::cout << "The double of 10 is " << value << ".\n";
}

{ // reset/operator()
	std::packaged_task<int(int)> tsk([](int x) { return x * 3; }); // package task

	std::future<int> fut = tsk.get_future();
	tsk(33);
	std::cout << "The triple of 33 is " << fut.get() << ".\n";

	// re-use same task object:
	tsk.reset();
	fut = tsk.get_future();
	std::thread(std::move(tsk), 99).detach();
	std::cout << "Thre triple of 99 is " << fut.get() << ".\n";
}

{ // constructor/get_future
	auto countdown = [](int from, int to) {
		for (int i = from; i != to; --i) {
			std::cout << i << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		std::cout << "Lift off!\n";
		return from - to;
	};

	std::packaged_task<int(int, int)> tsk(countdown); // set up packaged_task
	std::future<int> ret = tsk.get_future(); // get future

	std::thread th(std::move(tsk), 5, 0); // spawn thread to count down from 5 to 0

	int value = ret.get(); // wait for the task to finish and get result
	std::cout << "The countdown lasted for " << value << " seconds.\n";

	th.join();
}

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://en.cppreference.com/w/cpp/thread/packaged_task
int test_packaged_task_2()
{
{ // lambda
	std::packaged_task<int(int, int)> task([](int a, int b) { return std::pow(a, b);});
	std::future<int> result = task.get_future();

	task(2, 9);
	std::cout << "task_lambda:\t" << result.get() << '\n';
}

{ // bind
	std::packaged_task<int()> task(std::bind([](int x, int y) { return std::pow(x, y); }, 2, 11));
	std::future<int> result = task.get_future();

	task();
	std::cout << "task_bind:\t" << result.get() << '\n';
}

{ // thread
	std::packaged_task<int(int, int)> task([](int x, int y) { return std::pow(x, y); });
	std::future<int> result = task.get_future();

	std::thread task_td(std::move(task), 2, 10);
	task_td.join();
	std::cout << "task_thread:\t" << result.get() << '\n';
}

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://thispointer.com/c11-multithreading-part-10-packaged_task-example-and-tutorial/
struct DBDataFetcher {
	std::string operator()(std::string token)
	{
		// Do some stuff to fetch the data
		std::string data = "Data From " + token;
		return data;
	}
};

int test_packaged_task_3()
{
	// Create a packaged_task<> that encapsulated a Function Object
	std::packaged_task<std::string(std::string)> task(std::move(DBDataFetcher()));

	// Fetch the associated future<> from packaged_task<>
	std::future<std::string> result = task.get_future();

	// Pass the packaged_task to thread to run asynchronously
	std::thread th(std::move(task), "Arg");

	// Join the thread. Its blocking and returns when thread is finished.
	th.join();

	// Fetch the result of packaged_task<> i.e. value returned by getDataFromDB()
	std::string data = result.get();
	std::cout << data << std::endl;

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://stackoverflow.com/questions/18143661/what-is-the-difference-between-packaged-task-and-async
int test_packaged_task_4()
{
	// sleeps for one second and returns 1
	auto sleep = []() {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return 1;
	};

{ // std::packaged_task
	// >>>>> A packaged_task won't start on it's own, you have to invoke it
	std::packaged_task<int()> task(sleep);

	auto f = task.get_future();
	task(); // invoke the function

	// You have to wait until task returns. Since task calls sleep
	// you will have to wait at least 1 second.
	std::cout << "You can see this after 1 second\n";

	// However, f.get() will be available, since task has already finished.
	std::cout << f.get() << std::endl;
}

{ // std::async
	// >>>>> On the other hand, std::async with launch::async will try to run the task in a different thread :
	auto f = std::async(std::launch::async, sleep);
	std::cout << "You can see this immediately!\n";

	// However, the value of the future will be available after sleep has finished
	// so f.get() can block up to 1 second.
	std::cout << f.get() << "This will be shown after a second!\n";
}

	return 0;
}


// Blog: https://blog.csdn.net/fengbingchun/article/details/104124174

///////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/future/promise/
int test_promise_1()
{

{ // constructor/get_future/set_value
		std::promise<int> foo; // create promise
		std::promise<int> bar = std::promise<int>(std::allocator_arg, std::allocator<int>());
		std::future<int> fut = bar.get_future(); // engagement with future
		//std::future<int> fut2 = bar.get_future(); // crash, 每个promise共享状态只能被一个std::future对象检索或关联
		//std::future<int> fut = foo.get_future();
		auto print_int = [&fut]() { int x = fut.get(); fprintf(stdout, "value: %d\n", x); };
		std::thread th1(print_int); // send future to new thread
		bar.set_value(10); // fulfill promise(synchronizes with getting the future)
		//bar.set_value(10); // crash, 每个promise的set_value仅能被调用一次
		//foo.set_value(10);
		th1.join();
}

{ // operator =
	std::promise<int> prom;
	auto print_promise = [&prom]() {
		std::future<int> fut = prom.get_future();
		int x = fut.get();
		std::cout << "value: " << x << '\n';
	};

	std::thread th1(print_promise);
	prom.set_value(10);
	th1.join();

	prom = std::promise<int>(); // reset, by move-assigning a new promise
	std::thread th2(print_promise);
	prom.set_value(20);
	th2.join();
}

{ // set_exception
	std::promise<int> prom;
	std::future<int> fut = prom.get_future();

	auto get_int = [&prom]() {
		int x;
		std::cout << "Please, enter an integer value: ";
		std::cin.exceptions(std::ios::failbit); // throw on failbit
		try {
			std::cin >> x; // sets failbit if input is not int
			prom.set_value(x);
		} catch (std::exception&) {
			prom.set_exception(std::current_exception());
		}
	};

	auto print_int = [&fut]() {
		try {
			int x = fut.get();
			std::cout << "value: " << x << '\n';
		} catch (std::exception& e) {
			std::cout << "[exception caught: " << e.what() << "]\n";
		}
	};

	std::thread th1(print_int);
	std::thread th2(get_int);

	th1.join();
	th2.join();
}

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://en.cppreference.com/w/cpp/thread/promise
void accumulate(std::vector<int>::iterator first, std::vector<int>::iterator last, std::promise<int> accumulate_promise)
{
	int sum = std::accumulate(first, last, 0);
	accumulate_promise.set_value(sum);  // Notify future
}

void do_work(std::promise<void> barrier)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	barrier.set_value();
}

int test_promise_2()
{
	// Demonstrate using promise<int> to transmit a result between threads.
	std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
	std::promise<int> accumulate_promise;
	std::future<int> accumulate_future = accumulate_promise.get_future();
	std::thread work_thread(accumulate, numbers.begin(), numbers.end(), std::move(accumulate_promise));

	// future::get() will wait until the future has a valid result and retrieves it.
	// Calling wait() before get() is not needed
	//accumulate_future.wait();  // wait for result
	std::cout << "result=" << accumulate_future.get() << '\n';
	work_thread.join();  // wait for thread completion

	// Demonstrate using promise<void> to signal state between threads.
	std::promise<void> barrier;
	std::future<void> barrier_future = barrier.get_future();
	std::thread new_work_thread(do_work, std::move(barrier));
	barrier_future.wait();
	new_work_thread.join();

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://en.cppreference.com/w/cpp/thread/promise/set_value_at_thread_exit
int test_promise_3()
{
#ifdef _MSC_VER
	// set_value_at_thread_exit
	using namespace std::chrono_literals;
	std::promise<int> p;
	std::future<int> f = p.get_future();
	std::thread([&p] {
		std::this_thread::sleep_for(1s);
		p.set_value_at_thread_exit(9); // gcc 4.9 don't support this function
	}).detach();

	std::cout << "Waiting..." << std::flush;
	f.wait();
	std::cout << "Done!\nResult is: " << f.get() << '\n';
#endif

	return 0;
}


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

