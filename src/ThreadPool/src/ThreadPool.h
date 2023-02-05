/*
* 文件名称：ThreadPool.h
* 语言标准：C++17
* 
* 创建日期：2017年09月22日
* 更新日期：2023年01月23日
* 
* 摘要
* 1.线程池类ThreadPool定义于此文件，实现于ThreadPool.cpp。
* 2.当无任务时，阻塞守护线程；当新增任务时，激活守护线程，通知线程获取任务。
* 3.当无闲置线程时，阻塞守护线程；当存在闲置线程时，激活守护线程，通知闲置线程获取任务。
* 4.当销毁线程池时，等待守护线程退出，而守护线程在退出之前，等待所有线程退出。
*   线程在退出之前，默认执行任务队列的所有任务。可选取出所有任务或者清空队列，以支持线程立即退出。
* 5.提供增删线程策略，由守护线程增删线程。
*   在任务队列非空之时，一次性增加线程；在存在闲置线程之时，逐个删减线程。
* 6.以原子操作确保接口的线程安全性，并且新增成员类Proxy，用于减少原子操作，针对频繁操作提升性能。
* 7.守护线程主函数声明为静态成员，除去与类成员指针this的关联性。
* 8.引入强化条件类模板Condition，当激活先于阻塞时，确保守护线程正常退出。
* 9.引入双缓冲队列类模板DoubleQueue，提高放入和取出任务的效率。
* 
* 作者：许聪
* 邮箱：solifree@qq.com
* 
* 版本：v2.2.0
* 变化
* v2.0.1
* 1.运用Condition的宽松策略，提升激活守护线程的性能。
* v2.0.2
* 1.消除谓词对条件实例有效性的重复判断。
* v2.0.3
* 1.修复条件谓词异常。
*   在延迟删减线程之时，未减少闲置线程数量，导致守护线程不必等待通知的条件谓词异常。
* v2.0.4
* 1.以原子操作确保移动语义的线程安全性。
* 2.新增成员类Proxy，提供轻量接口，减少原子操作。
* 3.新增任务可选复制语义或者移动语义。
* v2.1.0
* 1.修复线程池扩容问题。
*   由于未增加总线程数量，因此无限创建线程；同时未增加闲置线程数量，守护线程无法调度新线程执行任务，即线程泄漏。
* 2.修复线程池缩容问题。
*   在延迟删减线程之时，未减少总线程数量，导致线程池反复删减线程，直至线程池为空。
* v2.2.0
* 1.完善代码风格。
* 2.设置线程池容量函数返回合理值。
*/

#pragma once

#include <functional>
#include <utility>
#include <memory>
#include <list>
#include <mutex>

#include "Core.hpp"

ETERFREE_SPACE_BEGIN

class ThreadPool
{
	// 线程池数据结构体
	struct Structure;

public:
	// 线程池代理类
	class Proxy;

private:
	using DataType = std::shared_ptr<Structure>;

public:
	using TaskType = std::function<void()>;
	using TaskQueue = std::list<TaskType>;
	using SizeType = TaskQueue::size_type;

private:
	mutable std::mutex _mutex;
	DataType _data;

private:
	// 创建线程池
	static void create(DataType&& _data, \
		SizeType _capacity);

	// 销毁线程池
	static void destroy(DataType&& _data);

	// 调整线程数量
	static SizeType adjust(DataType& _data);

	// 守护线程主函数
	static void execute(DataType _data);

public:
	// 获取支持的并发线程数量
	static SizeType getConcurrency() noexcept;

private:
	// 加载非原子数据
	auto load() const
	{
		std::lock_guard lock(_mutex);
		return _data;
	}

public:
	// 默认构造函数
	ThreadPool(SizeType _capacity = getConcurrency());

	// 构造函数
	DEPRECATED
	ThreadPool(SizeType _size, SizeType _capacity);

	// 删除默认复制构造函数
	ThreadPool(const ThreadPool&) = delete;

	// 默认移动构造函数
	ThreadPool(ThreadPool&& _another)
	{
		std::lock_guard lock(_another._mutex);
		this->_data = std::move(_another._data);
	}

	// 默认析构函数
	~ThreadPool()
	{
		// 数据非空才进行销毁，以支持移动语义
		if (auto data = load())
			destroy(std::move(data));
	}

	// 删除默认复制赋值运算符函数
	ThreadPool& operator=(const ThreadPool&) = delete;

	// 默认移动赋值运算符函数
	ThreadPool& operator=(ThreadPool&& _another);

	// 获取线程最大数量
	REPLACEMENT(getCapacity)
	auto getMaxThreads() const
	{
		return getCapacity();
	}

	// 获取线程池容量
	SizeType getCapacity() const;

	// 设置线程最大数量
	REPLACEMENT(setCapacity)
	bool setMaxThreads(SizeType _capacity)
	{
		return setCapacity(_capacity);
	}

	// 设置线程池容量
	bool setCapacity(SizeType _capacity);

	// 获取线程数量
	REPLACEMENT(getTotalSize)
	auto getThreads() const
	{
		return getTotalSize();
	}

	// 获取线程数量
	REPLACEMENT(getTotalSize)
	auto getSize() const
	{
		return getTotalSize();
	}

	// 获取总线程数量
	SizeType getTotalSize() const;

	// 设置线程数量
	DEPRECATED
	bool setThreads(SizeType size)
	{
		return false;
	}

	// 获取空闲线程数量
	REPLACEMENT(getIdleSize)
	auto getFreeThreads() const
	{
		return getIdleSize();
	}

	// 获取闲置线程数量
	SizeType getIdleSize() const;

	// 获取任务数量
	REPLACEMENT(getTaskSize)
	auto getTasks() const
	{
		return getTaskSize();
	}

	// 获取任务数量
	SizeType getTaskSize() const;

	// 放入任务
	bool pushTask(const TaskType& _task);
	bool pushTask(TaskType&& _task);

	// 适配不同任务接口，推进线程池模板化
	template <typename _Functor>
	bool pushTask(const _Functor& _functor)
	{
		return pushTask(TaskType(_functor));
	}
	template <typename _Functor>
	bool pushTask(_Functor&& _functor)
	{
		return pushTask(TaskType(std::forward<_Functor>(_functor)));
	}
	template <typename _Functor, typename... _Args>
	bool pushTask(_Functor&& _functor, _Args&&... _args);

	// 批量放入任务
	bool pushTask(TaskQueue& _taskQueue);
	bool pushTask(TaskQueue&& _taskQueue);

	// 批量取出任务
	bool popTask(TaskQueue& _taskQueue);

	// 清空任务
	void clearTask();

	// 获取代理
	Proxy getProxy() const;
};

class ThreadPool::Proxy
{
	DataType _data;

public:
	Proxy(const decltype(_data)& _data) noexcept : \
		_data(_data) {}

	explicit operator bool() const noexcept
	{
		return static_cast<bool>(_data);
	}

	// 获取线程池容量
	SizeType getCapacity() const noexcept;

	// 设置线程池容量
	bool setCapacity(SizeType _capacity);

	// 获取线程数量
	REPLACEMENT(getTotalSize)
	auto getSize() const noexcept
	{
		return getTotalSize();
	}

	// 获取总线程数量
	SizeType getTotalSize() const noexcept;

	// 获取闲置线程数量
	SizeType getIdleSize() const noexcept;

	// 获取任务数量
	SizeType getTaskSize() const noexcept;

	// 放入任务
	bool pushTask(const TaskType& _task);
	bool pushTask(TaskType&& _task);

	// 适配不同任务接口，推进线程池模板化
	template <typename _Functor>
	bool pushTask(const _Functor& _functor)
	{
		return pushTask(TaskType(_functor));
	}
	template <typename _Functor>
	bool pushTask(_Functor&& _functor)
	{
		return pushTask(TaskType(std::forward<_Functor>(_functor)));
	}
	template <typename _Functor, typename... _Args>
	bool pushTask(_Functor&& _functor, _Args&&... _args);

	// 批量放入任务
	bool pushTask(TaskQueue& _taskQueue);
	bool pushTask(TaskQueue&& _taskQueue);

	// 批量取出任务
	bool popTask(TaskQueue& _taskQueue);

	// 清空任务
	void clearTask();
};

template <typename _Functor, typename... _Args>
bool ThreadPool::Proxy::pushTask(_Functor&& _functor, _Args&&... _args)
{
	auto functor = std::bind(std::forward<_Functor>(_functor), \
		std::forward<_Args>(_args)...);
	return pushTask(TaskType(functor));
}

template <typename _Functor, typename... _Args>
bool ThreadPool::pushTask(_Functor&& _functor, _Args&&... _args)
{
	auto functor = std::bind(std::forward<_Functor>(_functor), \
		std::forward<_Args>(_args)...);
	return pushTask(TaskType(functor));
}

ETERFREE_SPACE_END
