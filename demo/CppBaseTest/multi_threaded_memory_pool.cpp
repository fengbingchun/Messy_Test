#include "multi_threaded_memory_pool.hpp"
#include <iostream>
#include <chrono>
#include <string>
#include <mutex>

// Blog: https://blog.csdn.net/fengbingchun/article/details/84592548

namespace multi_threaded_memory_pool_ {

// reference: 《提高C++性能的编程技术》：第七章：多线程内存池

////////////////////////////////////////////////
class Rational1 {
public:
	Rational1(int a = 0, int b = 1) : n(a), d(b) {}
private:
	int n; // 分子
	int d; // 分母
};

////////////////////////////////////////////
// 单线程可变大小内存管理器: 
// MemoryChunk类取代之前版本中使用的NextOnFreeList类，它用来把不同大小的内存块连接起来形成块序列
class MemoryChunk {
public:
	MemoryChunk(MemoryChunk* nextChunk, size_t chunkSize);
	// 析构函数释放构造函数获得的内存空间
	~MemoryChunk() { delete [] mem; }

	inline void* alloc(size_t size);
	inline void free(void* someElement);

	// 指向列表下一内存块的指针
	MemoryChunk* nextMemChunk() { return next; }
	// 当前内存块剩余空间大小
	size_t spaceAvailable() { return chunkSize - bytesAlreadyAllocated; }
	// 这是一个内存块的默认大小
	enum { DEFAULT_CHUNK_SIZE = 4096 };

private:
	MemoryChunk* next;
	void* mem;

	// 一个内存块的默认大小
	size_t chunkSize;
	// 当前内存块中已分配的字节数
	size_t bytesAlreadyAllocated;
};

// 构造函数首先确定内存块的适当大小，然后根据这个大小从堆上分配私有存储空间
// MemoryChunk将next成员指向输入参数nextChunk, nextChunk是列表先前的头部
MemoryChunk::MemoryChunk(MemoryChunk* nextChunk, size_t reqSize)
{
	chunkSize = (reqSize > DEFAULT_CHUNK_SIZE) ? reqSize : DEFAULT_CHUNK_SIZE;
	next = nextChunk;
	bytesAlreadyAllocated = 0;
	mem = new char[chunkSize];
}

// alloc函数处理内存分配请求，它返回一个指针，该指针指向mem所指向的MemoryChunk私有存储空间中的可用空间。
// 该函数通过更新该块中已分配的字节数来记录可用空间的大小
void* MemoryChunk::alloc(size_t requestSize)
{
	void* addr = static_cast<void*>(static_cast<char*>(mem) + bytesAlreadyAllocated);
	bytesAlreadyAllocated += requestSize;

	return addr;
}

// 在该实现中，不用担心空闲内存段的释放。当对象被删除后，整个内存块将被释放并且返回到堆上
inline void MemoryChunk::free(void* doomed)
{
}

// MemoryChunk只是一个辅助类，ByteMemoryPoll类用它来实现可变大小的内存管理
class ByteMemoryPool {
public:
	ByteMemoryPool(size_t initSize = MemoryChunk::DEFAULT_CHUNK_SIZE);
	~ByteMemoryPool();

	// 从私有内存池分配内存
	inline  void* alloc(size_t size);
	// 释放先前从内存池中分配的内存
	inline void free(void* someElement);

private:
	// 内存块列表，它是我们的私有存储空间
	MemoryChunk* listOfMemoryChunks = nullptr;
	// 向我们的私有存储空间添加一个内存块
	void expandStorage(size_t reqSize);
};

// 虽然内存块列表可能包含多个块，但只有第一块拥有可用于分配的内存。其它块表示已分配的内存。
// 列表的首个元素是唯一能够分配可以内存的块。

// 构造函数接收initSize参数来设定一个内存块的大小，即构造函数借此来设置单个内存块的大小。
// expandStorage方法使listOfMemoryChunks指向一个已分配的MemoryChunk对象
// 创建ByteMemoryPool对象，生成私有存储空间
ByteMemoryPool::ByteMemoryPool(size_t initSize)
{
	expandStorage(initSize);
}

// 析构函数遍历内存块列表并且删除它们
ByteMemoryPool::~ByteMemoryPool()
{
	MemoryChunk* memChunk = listOfMemoryChunks;

	while (memChunk) {
		listOfMemoryChunks = memChunk->nextMemChunk();
		delete memChunk;
		memChunk = listOfMemoryChunks;
	}
}

// alloc函数确保有足够的可用空间，而把分配任务托付给列表头的MemoryChunk
void* ByteMemoryPool::alloc(size_t requestSize)
{
	size_t space = listOfMemoryChunks->spaceAvailable();
	if (space < requestSize) {
		expandStorage(requestSize);
	}

	return listOfMemoryChunks->alloc(requestSize);
}

// 释放之前分配的内存的任务被委派给列表头部的MemoryChunk来完成
// MemoryChunk::free不做任何事情，因为ByteMemoryPool的实现不会重用之前分配的内存。如果需要更多内存，
// 我们将创建新的内存块以便今后分配使用。在内存池被销毁时，内存释放回堆中。ByteMemoryPool析构函数
// 释放所有的内存块到堆中
inline void ByteMemoryPool::free(void* doomed)
{
	listOfMemoryChunks->free(doomed);
}

// 若遇到内存块用尽这种不太可能的情况，我们通过创建新的内存块并把它添加到内存块列表的头部来扩展它
void ByteMemoryPool::expandStorage(size_t reqSize)
{
	listOfMemoryChunks = new MemoryChunk(listOfMemoryChunks, reqSize);
}

////////////////////////////////////////////////////////
// 多线程内存池实现
template<class POOLTYPE, class LOCK>
class MTMemoryPool {
public:
	// 从freeList里分配一个元素
	inline void* alloc(size_t size);
	// 返回一个元素给freeList
	inline void free(void* someElement);

private:
	POOLTYPE stPool; // 单线程池
	LOCK theLock;
};

// alloc方法将分配任务委托给内存池成员，而将锁定任务委托给锁成员
template<class M, class L>
inline void* MTMemoryPool<M, L>::alloc(size_t size)
{
	void* mem;
	theLock.lock();
	mem = stPool.alloc(size);
	theLock.unlock();

	return mem;
}

template<class M, class L>
inline void MTMemoryPool<M, L>::free(void* doomed)
{
	theLock.lock();
	stPool.free(doomed);
	theLock.unlock();
}

class ABCLock { // 抽象基类
public:
	virtual ~ABCLock() {}
	virtual void lock() = 0;
	virtual void unlock() = 0;
};

class MutexLock : public ABCLock {
public:
	MutexLock() {}
	~MutexLock() {}

	inline void lock() { mtx.lock(); }
	inline void unlock() { mtx.unlock(); }

private:
	std::mutex mtx; 
};

class Rational2 {
public:
	Rational2(int a = 0, int b = 1) : n(a),d(b) {}

	void* operator new(size_t size) { return memPool->alloc(size); }
	void operator delete(void* doomed, size_t size) { memPool->free(doomed); }

	static void newMemPool() { memPool = new MTMemoryPool<ByteMemoryPool, MutexLock>; }
	static void deleteMemPool() { delete memPool; }

private:
	int n; // 分子
	int d; // 分母
	static MTMemoryPool<ByteMemoryPool, MutexLock>* memPool;
};

MTMemoryPool<ByteMemoryPool, MutexLock>* Rational2::memPool = nullptr;

///////////////////////////////////////////////////////////////
// 多线程内存池实现应用在单线程环境中
class DummyLock : public ABCLock {
public:
	inline void lock() {}
	inline void unlock() {}
};

class Rational3 {
public:
	Rational3(int a = 0, int b = 1) : n(a),d(b) {}

	void* operator new(size_t size) { return memPool->alloc(size); }
	void operator delete(void* doomed, size_t size) { memPool->free(doomed); }

	static void newMemPool() { memPool = new MTMemoryPool<ByteMemoryPool, DummyLock>; }
	static void deleteMemPool() { delete memPool; }

private:
	int n; // 分子
	int d; // 分母
	static MTMemoryPool<ByteMemoryPool, DummyLock>* memPool;
};

MTMemoryPool<ByteMemoryPool, DummyLock>* Rational3::memPool = nullptr;

int test_multi_threaded_memory_pool_1()
{
	using namespace std::chrono;
	high_resolution_clock::time_point time_start, time_end;
	const int cycle_number1{10000}, cycle_number2{1000};

{ // 测试全局函数new()和delete()的基准性能
	Rational1* array[cycle_number2];

	time_start = high_resolution_clock::now();
	for (int j =0; j < cycle_number1; ++j) {
		for (int i =0; i < cycle_number2; ++i) {
			array[i] = new Rational1(i);
		}

		for (int i = 0; i < cycle_number2; ++i) {
			delete array[i];
		}	
	}
	time_end = high_resolution_clock::now();

	fprintf(stdout, "global function new/delete time spent: %f seconds\n",(duration_cast<duration<double>>(time_end - time_start)).count());
}

{ // 多线程内存池测试代码
	Rational2* array[cycle_number2];

	time_start = high_resolution_clock::now();
	Rational2::newMemPool();

	for (int j = 0; j < cycle_number1; ++j) {
		for (int i = 0; i < cycle_number2; ++i) {
			array[i] = new Rational2(i);
		}

		for (int i = 0; i < cycle_number2; ++i) {
			delete array[i];
		}
	}

	Rational2::deleteMemPool();
	time_end = high_resolution_clock::now();

	fprintf(stdout, "multi-threaded variable-size memory manager time spent: %f seconds\n",(duration_cast<duration<double>>(time_end - time_start)).count());	
}

{ // 多线程内存池应用在单线程环境下测试代码
	Rational3* array[cycle_number2];

	time_start = high_resolution_clock::now();
	Rational3::newMemPool();

	for (int j = 0; j < cycle_number1; ++j) {
		for (int i = 0; i < cycle_number2; ++i) {
			array[i] = new Rational3(i);
		}

		for (int i = 0; i < cycle_number2; ++i) {
			delete array[i];
		}
	}

	Rational3::deleteMemPool();
	time_end = high_resolution_clock::now();

	fprintf(stdout, "multi-threaded variable-size memory manager in single-threaded environment time spent: %f seconds\n",(duration_cast<duration<double>>(time_end - time_start)).count());	
}

	return 0;
}

} // namespace multi_threaded_memory_pool_

