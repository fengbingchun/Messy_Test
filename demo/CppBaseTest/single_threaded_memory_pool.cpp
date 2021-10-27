#include "single_threaded_memory_pool.hpp"
#include <iostream>
#include <chrono>
#include <string>

// Blog: https://blog.csdn.net/fengbingchun/article/details/84497625

namespace single_threaded_memory_pool_ {

// reference: 《提高C++性能的编程技术》：第六章：单线程内存池

////////////////////////////////////////////////
class Rational1 {
public:
	Rational1(int a = 0, int b = 1) : n(a), d(b) {}
private:
	int n; // 分子
	int d; // 分母
}; // class Rational1

////////////////////////////////////////////////
// 专用Rational2内存管理器
// 为避免频繁地使用内存管理器,Rational2类要维护一个预分配的Rational2对象的静态连接列表,该列表列出空闲的可用对象.
// 当需要Rational2对象时,可以从空闲列表中取出一个,使用后再把它放回空闲列表以便今后分配. 
// 声明一个辅助结构来连接空闲列表的相邻元素
class NextOnFreeList {
public:
	NextOnFreeList* next;
}; // class NextOnFreeList

// 空闲列表被声明为一个由NextOnFreeList元素组成的列表
class Rational2 {
public:
	Rational2(int a = 0, int b = 1) : n(a),d(b) {}

	inline void* operator new(size_t size);
	inline void operator delete(void* doomed, size_t size);

	static void newMemPool() { expandTheFreeList(); }
	static void deleteMemPool();

private:
	static NextOnFreeList* freeList; // Rational2对象的空闲列表
	static void expandTheFreeList();
	enum { EXPANSION_SIZE = 32};

	int n; // 分子
	int d; // 分母
}; // class Rational2

NextOnFreeList* Rational2::freeList = nullptr;

// new()在空闲列表中分配一个Rational2对象.如果列表为空,则扩展列表
inline void* Rational2::operator new(size_t size)
{
	if (nullptr == freeList) { // 如果列表为空,则将其填满
		expandTheFreeList();
	}

	NextOnFreeList* head = freeList;
	freeList = head->next;

	return head;
}

// delete()把Rational2对象直接添加到空闲列表的头部,以返回Rational2对象
inline void Rational2::operator delete(void* doomed, size_t size)
{
	NextOnFreeList* head = static_cast<NextOnFreeList*>(doomed);
	head->next = freeList;
	freeList = head;
}

// 当空闲列表用完后,需要从堆上分配更多的Rational2对象.
// Rational2和NextOnFreeList之间的类型转换是有危险的,必须确保空闲列表的元素足够大以支持任意一种类型
// 当我们用Rational2对象填充空闲列表时,要记得比较Rational2和NextOnFreeList的大小,并且分配较大的那一个
void Rational2::expandTheFreeList()
{
	// 本质上，expandTheFreeList的实现并不是最优的.因为空闲列表中每增加一个元素，就调用一次new. 如果只调用一次new
	// 获得一大块内存,然后把它切分给多个元素,这样会更高效。孤立地看，这种想法很正确。然而我们创建内存管理器时，
	// 认为它不会频繁扩展和收缩,否则必须重新查看代码实现并修正它

	// 我们必须分配足够大的对象以包含下一个指针
	size_t size = sizeof(Rational2) > sizeof(NextOnFreeList*) ? sizeof(Rational2) : sizeof(NextOnFreeList*);
	NextOnFreeList* runner = static_cast<NextOnFreeList*>((void*)new char[size]);
	freeList = runner;

	for (int i = 0; i < EXPANSION_SIZE; ++i) {
		runner->next = static_cast<NextOnFreeList*>((void*)new char[size]);
		runner = runner->next;
	}

	runner->next = nullptr;
}

void Rational2::deleteMemPool()
{
	NextOnFreeList* nextPtr;
	for (nextPtr = freeList; nextPtr != nullptr; nextPtr = freeList) {
		freeList = freeList->next;
		delete [] nextPtr;
	}
}

///////////////////////////////////////////////////////////////
// 固定大小对象的内存池: 观察Rational2内存管理器的实现，会很清楚地发现内存管理逻辑实际上独立于特定的Rational2类.
// 它唯一依赖的是类对象的大小----这正是用模板实现内存池的原因
template<class T>
class MemoryPool1 {
public:
	MemoryPool1(size_t size = EXPANSION_SIZE);
	~MemoryPool1();

	// 从空闲列表中分配T元素
	inline void* alloc(size_t size);
	// 返回T元素到空闲列表中
	inline void free(void* someElement);

private:
	// 空闲列表的下一元素
	MemoryPool1<T>* next;
	// 如果空闲列表为空，按该大小扩展它
	enum { EXPANSION_SIZE = 32 };
	// 添加空闲元素至空闲列表
	void expandTheFreeList(int howMany = EXPANSION_SIZE);
};

// 构造函数初始化空闲列表，参数size指定空闲列表的初始化长度
template<class T>
MemoryPool1<T>::MemoryPool1(size_t size)
{
	expandTheFreeList(size);
}

// 析构函数遍历空闲列表并且删除所有元素
template<class T>
MemoryPool1<T>::~MemoryPool1()
{
	MemoryPool1<T>* nextPtr = next;
	for (nextPtr = next; nextPtr != nullptr; nextPtr = next) {
		next = next->next;
		delete [] static_cast<char*>(static_cast<void*>(nextPtr));
	}
}

// alloc函数为T元素分配足够大的空间，如果空闲列表用尽，则调用expandThrFreeList函数来扩充它
template<class T>
inline void* MemoryPool1<T>::alloc(size_t size)
{
	if (!next) {
		expandTheFreeList();
	}

	MemoryPool1<T>* head = next;
	next = head->next;

	return head;
}


// free函数把T元素放回空闲列表，以此来释放它
template<class T>
inline void MemoryPool1<T>::free(void* doomed)
{
	MemoryPool1<T>* head = static_cast<MemoryPool1<T>*>(doomed);
	head->next = next;
	next = head;
}

// expandTheFreeList函数用来向空闲列表添加新元素，首先从堆上分配新元素，然后把它们连接到列表中
// 该函数在空闲列表用尽时被调用
template<class T>
void MemoryPool1<T>::expandTheFreeList(int howMany)
{
	// 必须分配足够大的对象以包含下一个指针
	size_t size = sizeof(T) > sizeof(MemoryPool1<T>*) ? sizeof(T) : sizeof(MemoryPool1<T>*);
	MemoryPool1<T>* runner = static_cast<MemoryPool1<T>*>((void*)(new char[size]));
	next = runner;

	for (int i = 0; i < howMany; ++i) {
		runner->next = static_cast<MemoryPool1<T>*>((void*)(new char[size]));
		runner = runner->next;
	}

	runner->next = nullptr;
}

// Rational3类不再需要维护它自己的空闲列表，这项任务委托给了MemoryPool1类
class Rational3 {
public:
	Rational3(int a = 0, int b = 1) : n(a),d(b) {}

	void* operator new(size_t size) { return memPool->alloc(size); }
	void operator delete(void* doomed, size_t size) { memPool->free(doomed); }
	static void newMemPool() { memPool = new MemoryPool1<Rational3>; }
	static void deleteMemPool() { delete memPool; }

private:
	int n; // 分子
	int d; // 分母
	static MemoryPool1<Rational3>* memPool;
};

MemoryPool1<Rational3>* Rational3::memPool = nullptr;

/////////////////////////////////////////////////////////////////////
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

class Rational4 {
public:
	Rational4(int a = 0, int b = 1) : n(a),d(b) {}

	void* operator new(size_t size) { return memPool->alloc(size); }
	void operator delete(void* doomed, size_t size) { memPool->free(doomed); }

	static void newMemPool() { memPool = new ByteMemoryPool; }
	static void deleteMemPool() { delete memPool; }

private:
	int n; // 分子
	int d; // 分母
	static ByteMemoryPool* memPool;
};

ByteMemoryPool* Rational4::memPool = nullptr;

/////////////////////////////////////////////////////////////////
int test_single_threaded_memory_pool_1()
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

{ // 专用Rational2内存管理器测试
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

	fprintf(stdout, "specialized rational2 memory manager time spent: %f seconds\n",(duration_cast<duration<double>>(time_end - time_start)).count());	
}

{ // 固定大小对象的内存池测试
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

	fprintf(stdout, "fixed-size object memory pool time spent: %f seconds\n",(duration_cast<duration<double>>(time_end - time_start)).count());	
}

{ // 单线程可变大小内存管理器测试
	Rational4* array[cycle_number2];

	time_start = high_resolution_clock::now();
	Rational4::newMemPool();

	for (int j = 0; j < cycle_number1; ++j) {
		for (int i = 0; i < cycle_number2; ++i) {
			array[i] = new Rational4(i);
		}

		for (int i = 0; i < cycle_number2; ++i) {
			delete array[i];
		}
	}

	Rational4::deleteMemPool();
	time_end = high_resolution_clock::now();

	fprintf(stdout, "single-threaded variable-size memory manager time spent: %f seconds\n",(duration_cast<duration<double>>(time_end - time_start)).count());	

}
	return 0;
}

} // namespace single_threaded_memory_pool_

