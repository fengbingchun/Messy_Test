#include "ThreadPool.h"
#include "Thread.h"
#include "Condition.hpp"
#include "DoubleQueue.hpp"

#include <cstdint>
#include <atomic>
#include <thread>

ETERFREE_SPACE_BEGIN

// 生成原子的设置函数
#define SET_ATOMIC(SizeType, Arithmetic, functor, field) \
SizeType functor(SizeType _size, Arithmetic _arithmetic) noexcept \
{ \
	constexpr auto MEMORY_ORDER = std::memory_order_relaxed; \
	switch (_arithmetic) \
	{ \
	case Arithmetic::REPLACE: \
		return field.exchange(_size, MEMORY_ORDER); \
	case Arithmetic::INCREASE: \
		return field.fetch_add(_size, MEMORY_ORDER); \
	case Arithmetic::DECREASE: \
		return field.fetch_sub(_size, MEMORY_ORDER); \
	default: \
		return field.load(MEMORY_ORDER); \
	} \
}

// 线程池数据结构体
struct ThreadPool::Structure
{
	// 算术枚举
	enum class Arithmetic : std::uint8_t
	{
		REPLACE,	// 替换
		INCREASE,	// 自增
		DECREASE	// 自减
	};

	using CONDITION = Condition<>;
	using QueueType = DoubleQueue<TaskType>;
	using Callback = Thread::Callback;

	CONDITION _condition;					// 强化条件变量
	std::thread _thread;					// 守护线程
	std::list<Thread> _threadTable;			// 线程表

	std::atomic<SizeType> _capacity;		// 线程池容量
	std::atomic<SizeType> _totalSize;		// 总线程数量
	std::atomic<SizeType> _idleSize;		// 闲置线程数量

	std::shared_ptr<QueueType> _taskQueue;	// 任务队列
	Callback _callback;						// 回调函数子

	// 过滤任务
	template <typename _TaskQueue>
	static auto filterTask(_TaskQueue& _taskQueue);

	/*
	 * 默认构造函数
	 * 若先以运算符new创建实例，再交由共享指针std::shared_ptr托管，
	 * 则至少二次分配内存，先为实例分配内存，再为共享指针的控制块分配内存。
	 * 而std::make_shared典型地仅分配一次内存，实例内存和控制块内存连续。
	 */
	Structure() : \
		_taskQueue(std::make_shared<QueueType>()) {}

	// 获取线程池容量
	auto getCapacity() const noexcept
	{
		return _capacity.load(std::memory_order_relaxed);
	}

	// 设置线程池容量
	void setCapacity(SizeType _capacity, bool _notified = false);

	// 获取总线程数量
	auto getTotalSize() const noexcept
	{
		return _totalSize.load(std::memory_order_relaxed);
	}

	// 设置总线程数量
	SET_ATOMIC(SizeType, Arithmetic, setTotalSize, _totalSize);

	// 获取闲置线程数量
	auto getIdleSize() const noexcept
	{
		return _idleSize.load(std::memory_order_relaxed);
	}

	// 设置闲置线程数量
	SET_ATOMIC(SizeType, Arithmetic, setIdleSize, _idleSize);

	// 放入任务
	bool pushTask(const TaskType& _task);
	bool pushTask(TaskType&& _task);

	// 批量放入任务
	bool pushTask(TaskQueue& _taskQueue);
	bool pushTask(TaskQueue&& _taskQueue);
};

#undef SET_ATOMIC

// 过滤无效任务
template <typename _TaskQueue>
auto ThreadPool::Structure::filterTask(_TaskQueue& _taskQueue)
{
	decltype(_taskQueue.size()) size = 0;
	for (auto iterator = _taskQueue.cbegin(); \
		iterator != _taskQueue.cend();)
		if (!*iterator)
			iterator = _taskQueue.erase(iterator);
		else
		{
			++iterator;
			++size;
		}
	return size;
}

// 设置线程池容量
void ThreadPool::Structure::setCapacity(SizeType _capacity, \
	bool _notified)
{
	auto capacity = this->_capacity.exchange(_capacity, \
		std::memory_order_relaxed);
	if (_notified && capacity != _capacity)
		_condition.notify_one(CONDITION::Strategy::RELAXED);
}

// 放入任务
bool ThreadPool::Structure::pushTask(const TaskType& _task)
{
	// 若放入任务之前，任务队列为空，则通知守护线程
	auto result = _taskQueue->push(_task);
	if (result && result.value() == 0)
		_condition.notify_one(CONDITION::Strategy::RELAXED);
	return result.has_value();
}

// 放入任务
bool ThreadPool::Structure::pushTask(TaskType&& _task)
{
	// 若放入任务之前，任务队列为空，则通知守护线程
	auto result = _taskQueue->push(std::forward<TaskType>(_task));
	if (result && result.value() == 0)
		_condition.notify_one(CONDITION::Strategy::RELAXED);
	return result.has_value();
}

// 批量放入任务
bool ThreadPool::Structure::pushTask(TaskQueue& _taskQueue)
{
	// 过滤无效任务
	if (filterTask(_taskQueue) <= 0) return false;

	// 若放入任务之前，任务队列为空，则通知守护线程
	auto result = this->_taskQueue->push(_taskQueue);
	if (result && result.value() == 0)
		_condition.notify_one(CONDITION::Strategy::RELAXED);
	return result.has_value();
}

// 批量放入任务
bool ThreadPool::Structure::pushTask(TaskQueue&& _taskQueue)
{
	// 过滤无效任务
	if (filterTask(_taskQueue) <= 0) return false;

	// 若放入任务之前，任务队列为空，则通知守护线程
	auto result = this->_taskQueue->push(std::forward<TaskQueue>(_taskQueue));
	if (result && result.value() == 0)
		_condition.notify_one(CONDITION::Strategy::RELAXED);
	return result.has_value();
}

// 获取线程池容量
auto ThreadPool::Proxy::getCapacity() const noexcept \
-> SizeType
{
	return _data ? _data->getCapacity() : 0;
}

// 设置线程池容量
bool ThreadPool::Proxy::setCapacity(SizeType _capacity)
{
	if (_capacity <= 0 || !_data) return false;

	_data->setCapacity(_capacity, true);
	return true;
}

// 获取总线程数量
auto ThreadPool::Proxy::getTotalSize() const noexcept \
-> SizeType
{
	return _data ? _data->getTotalSize() : 0;
}

// 获取闲置线程数量
auto ThreadPool::Proxy::getIdleSize() const noexcept \
-> SizeType
{
	return _data ? _data->getIdleSize() : 0;
}

// 获取任务数量
auto ThreadPool::Proxy::getTaskSize() const noexcept \
-> SizeType
{
	return _data ? _data->_taskQueue->size() : 0;
}

// 放入任务
bool ThreadPool::Proxy::pushTask(const TaskType& _task)
{
	return _task && _data && _data->pushTask(_task);
}

// 放入任务
bool ThreadPool::Proxy::pushTask(TaskType&& _task)
{
	return _task && _data \
		&& _data->pushTask(std::forward<TaskType>(_task));
}

// 批量放入任务
bool ThreadPool::Proxy::pushTask(TaskQueue& _taskQueue)
{
	return _data && _data->pushTask(_taskQueue);
}

// 批量放入任务
bool ThreadPool::Proxy::pushTask(TaskQueue&& _taskQueue)
{
	return _data \
		&& _data->pushTask(std::forward<TaskQueue>(_taskQueue));
}

// 批量取出任务
bool ThreadPool::Proxy::popTask(TaskQueue& _taskQueue)
{
	return _data && _data->_taskQueue->pop(_taskQueue);
}

// 清空任务
void ThreadPool::Proxy::clearTask()
{
	if (_data)
		_data->_taskQueue->clear();
}

// 创建线程池
void ThreadPool::create(DataType&& _data, SizeType _capacity)
{
	using Arithmetic = Structure::Arithmetic;

	// 定义回调函数子
	_data->_callback = [_data = std::weak_ptr(_data)](Thread::ThreadID _id, bool _idle)
	{
		// 线程并非闲置状态
		if (!_idle) return;

		// 若未增加之前，无闲置线程，则通知守护线程
		if (auto data = _data.lock(); \
			data && data->setIdleSize(1, Arithmetic::INCREASE) == 0)
			data->_condition.notify_one(Structure::CONDITION::Strategy::RELAXED);
	};

	// 初始化线程并放入线程表
	_capacity = _capacity > 0 ? _capacity : 1;
	for (decltype(_capacity) index = 0; index < _capacity; ++index)
	{
		Thread thread;
		thread.configure(_data->_taskQueue, _data->_callback);
		_data->_threadTable.push_back(std::move(thread));
	}

	_data->setCapacity(_capacity); // 设置线程池容量
	_data->setTotalSize(_capacity, Arithmetic::REPLACE); // 设置总线程数量
	_data->setIdleSize(_capacity, Arithmetic::REPLACE); // 设置闲置线程数量

	// 创建std::thread对象，即守护线程，以_data为参数，执行函数execute
	_data->_thread = std::thread(execute, _data);
}

// 销毁线程池
void ThreadPool::destroy(DataType&& _data)
{
	// 避免重复销毁
	if (!_data->_condition) return;

	// 分离守护线程
	//_data->_thread.detach();

	// 通知守护线程退出
	_data->_condition.exit();

	// 挂起直到守护线程退出
	if (_data->_thread.joinable())
		_data->_thread.join();

	using Arithmetic = Structure::Arithmetic;
	_data->setCapacity(0); // 设置线程池容量
	_data->setTotalSize(0, Arithmetic::REPLACE); // 设置总线程数量
	_data->setIdleSize(0, Arithmetic::REPLACE); // 设置闲置线程数量
}

// 调整线程数量
ThreadPool::SizeType ThreadPool::adjust(DataType& _data)
{
	auto size = _data->getTotalSize();
	auto capacity = _data->getCapacity();

	// 1.删减线程
	if (size >= capacity) return size - capacity;

	// 2.增加线程
	size = capacity - size;

	// 添加线程至线程表
	for (decltype(size) index = 0; index < size; ++index)
	{
		Thread thread;
		thread.configure(_data->_taskQueue, _data->_callback);
		_data->_threadTable.push_back(std::move(thread));
	}

	using Arithmetic = Structure::Arithmetic;

	// 增加总线程数量
	_data->setTotalSize(size, Arithmetic::INCREASE);

	// 增加闲置线程数量
	_data->setIdleSize(size, Arithmetic::INCREASE);
	return 0;
}

// 守护线程主函数
void ThreadPool::execute(DataType _data)
{
	/*
	 * 条件变量的谓词，不必等待通知的条件
	 * 1.强化条件变量无效。
	 * 2.任务队列非空并且存在闲置线程。
	 * 3.任务队列非空并且需要增加线程。
	 * 4.存在闲置线程并且需要删减线程。
	 */
	auto predicate = [&_data]
	{
		bool empty = _data->_taskQueue->empty();
		bool idle = _data->getIdleSize() > 0;
		auto size = _data->getTotalSize();
		auto capacity = _data->getCapacity();
		return !empty && (idle || size < capacity) \
			|| idle && size > capacity;
	};

	// 若谓词非真，自动解锁互斥元，阻塞守护线程，直至通知激活，再次锁定互斥元
	_data->_condition.wait(predicate);

	// 守护线程退出通道
	while (_data->_condition)
	{
		// 调整线程数量
		auto size = adjust(_data);

		// 遍历线程表，访问闲置线程
		for (auto iterator = _data->_threadTable.begin(); \
			iterator != _data->_threadTable.end() \
			&& _data->getIdleSize() > 0;)
		{
			// 若线程处于闲置状态
			if (auto& thread = *iterator; thread.idle())
			{
				using Arithmetic = Structure::Arithmetic;

				// 若通知线程执行任务成功，则减少闲置线程数量
				if (thread.notify())
					_data->setIdleSize(1, Arithmetic::DECREASE);
				// 删减线程
				else if (size > 0)
				{
					iterator = _data->_threadTable.erase(iterator);
					_data->setIdleSize(1, Arithmetic::DECREASE);
					_data->setTotalSize(1, Arithmetic::DECREASE);
					--size;
					continue;
				}
			}
			++iterator;
		}

		// 根据谓词真假，决定是否阻塞守护线程
		_data->_condition.wait(predicate);
	}

	// 清空线程
	_data->_threadTable.clear();
}

// 获取支持的并发线程数量
ThreadPool::SizeType ThreadPool::getConcurrency() noexcept
{
	auto concurrency = std::thread::hardware_concurrency();
	return concurrency > 0 ? concurrency : 1;
}

// 默认构造函数
ThreadPool::ThreadPool(SizeType _capacity) : \
	_data(std::make_shared<Structure>())
{
	create(load(), _capacity);
}

// 构造函数
ThreadPool::ThreadPool(SizeType _size, \
	SizeType _capacity) : \
	_data(std::make_shared<Structure>())
{
	create(load(), _capacity);
}

// 默认移动赋值运算符函数
ThreadPool& ThreadPool::operator=(ThreadPool&& _another)
{
	if (&_another != this)
	{
		std::scoped_lock lock(this->_mutex, _another._mutex);
		this->_data = std::move(_another._data);
	}
	return *this;
}

// 获取线程池容量
ThreadPool::SizeType ThreadPool::getCapacity() const
{
	auto data = load();
	return data ? data->getCapacity() : 0;
}

// 设置线程池容量
bool ThreadPool::setCapacity(SizeType _capacity)
{
	if (_capacity > 0)
		if (auto data = load())
		{
			data->setCapacity(_capacity, true);
			return true;
		}
	return false;
}

// 获取总线程数量
ThreadPool::SizeType ThreadPool::getTotalSize() const
{
	auto data = load();
	return data ? data->getTotalSize() : 0;
}

// 获取闲置线程数量
ThreadPool::SizeType ThreadPool::getIdleSize() const
{
	auto data = load();
	return data ? data->getIdleSize() : 0;
}

// 获取任务数量
ThreadPool::SizeType ThreadPool::getTaskSize() const
{
	auto data = load();
	return data ? data->_taskQueue->size() : 0;
}

// 放入任务
bool ThreadPool::pushTask(const TaskType& _task)
{
	// 过滤无效任务
	if (!_task) return false;

	auto data = load();
	return data && data->pushTask(_task);
}

// 放入任务
bool ThreadPool::pushTask(TaskType&& _task)
{
	// 过滤无效任务
	if (!_task) return false;

	auto data = load();
	return data \
		&& data->pushTask(std::forward<TaskType>(_task));
}

// 批量放入任务
bool ThreadPool::pushTask(TaskQueue& _taskQueue)
{
	auto data = load();
	return data && data->pushTask(_taskQueue);
}

// 批量放入任务
bool ThreadPool::pushTask(TaskQueue&& _taskQueue)
{
	auto data = load();
	return data \
		&& data->pushTask(std::forward<TaskQueue>(_taskQueue));
}

// 批量取出任务
bool ThreadPool::popTask(TaskQueue& _taskQueue)
{
	auto data = load();
	return data && data->_taskQueue->pop(_taskQueue);
}

// 清空任务
void ThreadPool::clearTask()
{
	if (auto data = load())
		data->_taskQueue->clear();
}

// 获取代理
ThreadPool::Proxy ThreadPool::getProxy() const
{
	return load();
}

ETERFREE_SPACE_END
