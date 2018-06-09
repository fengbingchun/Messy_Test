#include "thread2.hpp"
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <list>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <chrono>
#include <iomanip>
#include <ctime>

// Blog: http://blog.csdn.net/fengbingchun/article/details/73393229

#ifdef _MSC_VER

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
	std::thread foo; // ȱʡ���캯�����̲߳���ִ��
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
#ifdef _MSC_VER
	std::cout << "Current time: " << std::put_time(ptm, "%X") << '\n';
#endif

	std::cout << "Waiting for the next minute to begin...\n";
	++ptm->tm_min; ptm->tm_sec = 0;
	std::this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));
#ifdef _MSC_VER
	std::cout << std::put_time(ptm, "%X") << " reached!\n";
#endif

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

//////////////////////////////////////////////////////////////
// reference: https://zh.wikibooks.org/zh-hans/C%2B%2B/STL/Thread
template<typename T>
class SyncQueue {
public:
	SyncQueue(int maxSize) :m_maxSize(maxSize), m_needStop(false) {}

	void Put(const T&x) { Add(x); }
	void Put(T&&x) { Add(std::forward<T>(x)); }

	void Take(std::list<T>& list)
	{
		std::unique_lock<std::mutex> locker(m_mutex);
		m_notEmpty.wait(locker, [this] {return m_needStop || NotEmpty(); });

		if (m_needStop) return;
		list = std::move(m_queue);
		m_notFull.notify_one();
	}

	void Take(T& t)
	{
		std::unique_lock<std::mutex> locker(m_mutex);
		m_notEmpty.wait(locker, [this] {return m_needStop || NotEmpty(); });

		if (m_needStop) return;
		t = m_queue.front();
		m_queue.pop_front();
		m_notFull.notify_one();
	}

	void Stop()
	{
		{
			std::lock_guard<std::mutex> locker(m_mutex);
			m_needStop = true;
		}
		m_notFull.notify_all();
		m_notEmpty.notify_all();
	}

	bool Empty()
	{
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_queue.empty();
	}

	bool Full()
	{
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_queue.size() == m_maxSize;
	}

	size_t Size()
	{
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_queue.size();
	}

	int Count()
	{
		return m_queue.size();
	}

private:
	bool NotFull() const
	{
		bool full = m_queue.size() >= m_maxSize;
		if (full)
			std::cout << "full, waiting��thread id: " << std::this_thread::get_id() << std::endl;
		return !full;
	}

	bool NotEmpty() const
	{
		bool empty = m_queue.empty();
		if (empty)
			std::cout << "empty,waiting��thread id: " << std::this_thread::get_id() << std::endl;
		return !empty;
	}

	template<typename F>
	void Add(F&&x)
	{
		std::unique_lock< std::mutex> locker(m_mutex);
		m_notFull.wait(locker, [this] {return m_needStop || NotFull(); });
		if (m_needStop) return;

		m_queue.push_back(std::forward<F>(x));
		m_notEmpty.notify_one();
	}

private:
	std::list<T> m_queue; //������
	std::mutex m_mutex; //�����������������������ʹ��
	std::condition_variable m_notEmpty;//��Ϊ�յ���������
	std::condition_variable m_notFull; //û��������������
	int m_maxSize; //ͬ����������size
	bool m_needStop; //ֹͣ�ı�־
};

const int MaxTaskCount = 100;
class ThreadPool {
public:
	using Task = std::function<void()>;
	ThreadPool(int numThreads = std::thread::hardware_concurrency()) : m_queue(MaxTaskCount)
	{
		Start(numThreads);
	}

	~ThreadPool(void)
	{
		//���û��ֹͣʱ������ֹͣ�̳߳�
		Stop();
	}

	void Stop()
	{
		std::call_once(m_flag, [this] {StopThreadGroup(); }); //��֤���߳������ֻ����һ��StopThreadGroup
	}

	void AddTask(Task&&task)
	{
		m_queue.Put(std::forward<Task>(task));
	}

	void AddTask(const Task& task)
	{
		m_queue.Put(task);
	}

private:
	void Start(int numThreads)
	{
		m_running = true;
		//�����߳���
		for (int i = 0; i <numThreads; ++i) {
			m_threadgroup.push_back(std::make_shared<std::thread>(&ThreadPool::RunInThread, this));
		}
	}

	void RunInThread()
	{
		while (m_running) {
			//ȡ����ֱ�ִ��
			std::list<Task> list;
			m_queue.Take(list);

			for (auto& task : list) {
				if (!m_running)
					return;

				task();
			}
		}
	}

	void StopThreadGroup()
	{
		m_queue.Stop(); //��ͬ�������е��߳�ֹͣ
		m_running = false; //��Ϊfalse�����ڲ��߳�����ѭ�����˳�

		for (auto thread : m_threadgroup) { //�ȴ��߳̽���
			if (thread)
				thread->join();
		}
		m_threadgroup.clear();
	}

	std::list<std::shared_ptr<std::thread>> m_threadgroup; //����������߳���
	SyncQueue<Task> m_queue; //ͬ������     
	std::atomic_bool m_running; //�Ƿ�ֹͣ�ı�־
	std::once_flag m_flag;
};

void TestThdPool()
{
	ThreadPool pool; bool runing = true;

	std::thread thd1([&pool, &runing] {
		while (runing) {
			std::cout << "produce " << std::this_thread::get_id() << std::endl;

			pool.AddTask([] {
				std::cout << "consume " << std::this_thread::get_id() << std::endl;
			});
		}
	});


	std::this_thread::sleep_for(std::chrono::seconds(10));
	runing = false;
	pool.Stop();

	thd1.join();
	getchar();
}

int test_thread_pool()
{
	TestThdPool();

	return 0;
}

//////////////////////////////////////////////////////////////
int test_thread_hardware_concurrency()
{
	std::cout << " the number of hardware thread contexts: " << std::thread::hardware_concurrency() << std::endl;
	return 0;
}

#endif