#include "atomic.hpp"
#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <sstream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/73436710

namespace atomic {
/////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/atomic/atomic/atomic/
std::atomic<bool> ready(false);
// atomic_flag::atomic_flag: Constructs an atomic_flag object
// The atomic_flag is in an unspecified state on construction (either set or clear),
// unless it is explicitly initialized to ATOMIC_FLAG_INIT.
std::atomic_flag winner = ATOMIC_FLAG_INIT;

void count1m(int id)
{
	while (!ready) { std::this_thread::yield(); }      // wait for the ready signal
	for (volatile int i = 0; i < 1000000; ++i) {}          // go!, count to 1 million
	if (!winner.test_and_set()) { std::cout << "thread #" << id << " won!\n"; }
};

int test_atomic_atomic()
{
	// atomic::atomic: Constructs an atomic object
	std::vector<std::thread> threads;
	std::cout << "spawning 10 threads that count to 1 million...\n";
	for (int i = 1; i <= 10; ++i) threads.push_back(std::thread(count1m, i));
	ready = true;
	for (auto& th : threads) th.join();

	return 0;
}

/////////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/atomic/atomic/compare_exchange_weak/
// a simple global linked list:
struct Node { int value; Node* next; };
std::atomic<Node*> list_head(nullptr);

void append(int val)
{     // append an element to the list
	Node* oldHead = list_head;
	Node* newNode = new Node{ val, oldHead };

	// what follows is equivalent to: list_head = newNode, but in a thread-safe way:
	while (!list_head.compare_exchange_weak(oldHead, newNode))
		newNode->next = oldHead;
}

int test_atomic_compare_exchange_weak()
{
	// atomic::compare_exchange_weak: Compares the contents of the atomic object's contained value with expected:
	// -if true, it replaces the contained value with val(like store).
	// - if false, it replaces expected with the contained value
	// spawn 10 threads to fill the linked list:
	std::vector<std::thread> threads;
	for (int i = 0; i<10; ++i) threads.push_back(std::thread(append, i));
	for (auto& th : threads) th.join();

	// print contents:
	for (Node* it = list_head; it != nullptr; it = it->next)
		std::cout << ' ' << it->value;
	std::cout << '\n';

	// cleanup:
	Node* it; while (it = list_head) { list_head = it->next; delete it; }

	return 0;
}

///////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/atomic/atomic/exchange/
std::atomic<bool> winner_(false);

void count1m_(int id)
{
	while (!ready) {}                  // wait for the ready signal
	for (int i = 0; i<1000000; ++i) {}   // go!, count to 1 million
	if (!winner_.exchange(true)) { std::cout << "thread #" << id << " won!\n"; }
};

int test_atomic_exchange()
{
	// atomic::exchange: Replaces the contained value by val and returns the value it had immediately before
	std::vector<std::thread> threads;
	std::cout << "spawning 10 threads that count to 1 million...\n";
	for (int i = 1; i <= 10; ++i) threads.push_back(std::thread(count1m_, i));
	ready = true;
	for (auto& th : threads) th.join();

	return 0;
}

/////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/atomic/atomic/load/
std::atomic<int> foo(0);

void set_foo(int x)
{
	foo.store(x, std::memory_order_relaxed);     // set value atomically
}

void print_foo()
{
	int x;
	do {
		x = foo.load(std::memory_order_relaxed);  // get value atomically
	} while (x == 0);
	std::cout << "foo: " << x << '\n';
}

int test_atomic_load()
{
	// atomic::load: Returns the contained value.
	// The operation is atomic and follows the memory ordering specified by sync.
	std::thread first(print_foo);
	std::thread second(set_foo, 10);
	first.join();
	second.join();

	return 0;
}

////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/atomic/atomic/operator=/
std::atomic<int> foo_ = 0;

void set_foo_(int x)
{
	foo_ = x;
}

void print_foo_()
{
	while (foo_ == 0) {             // wait while foo_=0
		std::this_thread::yield();
	}
	std::cout << "foo_: " << foo_ << '\n';
}

int test_atomic_operator()
{
	// atomic::operator=: Replaces the stored value by val.
	// This operation is atomic and uses sequential consistency (memory_order_seq_cst).
	// To modify the value with a different memory ordering
	std::thread first(print_foo_);
	std::thread second(set_foo_, 10);
	first.join();
	second.join();

	return 0;
}

///////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/atomic/atomic/store/
int test_atomic_store()
{
	// atomic::store: Replaces the contained value with val.
	// The operation is atomic and follows the memory ordering specified by sync.
	std::thread first(print_foo);
	std::thread second(set_foo, 10);
	first.join();
	second.join();

	return 0;
}

/////////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/atomic/atomic_flag/clear/
std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;
std::stringstream stream;

void append_number(int x)
{
	while (lock_stream.test_and_set()) {}
	stream << "thread #" << x << '\n';
	lock_stream.clear();
}

int test_atomic_flag_atomic_clear()
{
	// atomic_flag::clear: Clears the atomic_flag (i.e., sets it to false)
	//Clearing the atomic_flag makes the next call to member atomic_flag::test_and_set on this object return false.
	// The operation is atomic and follows the memory ordering specified by sync.

	// atomic_flag::test_and_set: Sets the atomic_flag and returns whether it was already set immediately before the call
	// The entire operation is atomic (an atomic read-modify-write operation): the value is not affected by other threads
	// between the instant its value is read (to be returned) and the moment it is modified by this function.
	std::vector<std::thread> threads;
	for (int i = 1; i <= 10; ++i) threads.push_back(std::thread(append_number, i));
	for (auto& th : threads) th.join();

	std::cout << stream.str();
	return 0;
}

} // namespace atomic
