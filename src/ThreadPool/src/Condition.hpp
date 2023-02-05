/*
* 文件名称：Condition.hpp
* 语言标准：C++17
* 
* 创建日期：2021年03月13日
* 更新日期：2022年03月19日
* 
* 摘要
* 1.参照C++17标准的条件变量类std::condition_variable封装条件类模板Condition。
* 2.结合临界区与条件变量，并且采用谓词作为条件变量之函数wait的参数，确保激活已经阻塞的线程，或者线程在等待之前，谓词为真而无需阻塞。
*	条件变量之函数notify并不会延迟通知，特别在精确调度事件之时，无法确保激活在调用notify之后，通过调用wait而阻塞的线程。
* 
* 作者：许聪
* 邮箱：solifree@qq.com
* 
* 版本：v1.2.0
* 变化
* v1.0.1
* 1.新增互斥策略枚举，优化无谓词notify，默认采用严格互斥策略。
*	严格互斥策略适用于无谓词wait，锁定互斥元之后激活线程，确保操作的原子性。
*	宽松互斥策略适用于带谓词wait，先锁定并解锁互斥元，再激活线程，从而减少线程的上下文切换次数。
* v1.1.0
* 1.修复无谓词wait_for和wait_until的逻辑错误。
*	若条件实例有效，则返回阻塞是否未超时，即是否被激活。而条件实例无效直接返回否定。
* 2.优化带谓词wait，减少使用Lambda，降低谓词层级。
* v1.1.1
* 1.修复部分谓词的判断逻辑错误。
* 2.删除基于xtime的wait_until。
* v1.2.0
* 1.新增函数enter，与函数exit相对，支持进入再退出，一次创建反复使用。
*/

#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "Core.hpp"

ETERFREE_SPACE_BEGIN

template <typename _Size = std::size_t>
class Condition
{
public:
	enum class Strategy : std::uint8_t
	{
		STRICT, RELAXED
	};

public:
	using Size = _Size;

private:
	std::mutex _mutex;
	std::atomic_bool _validity;
	std::condition_variable _condition;

public:
	Condition() : _validity(true) {}

	Condition(const Condition&) = delete;

	~Condition() { exit(); }

	Condition& operator=(const Condition&) = delete;

	explicit operator bool() const noexcept { return valid(); }

	bool valid() const noexcept
	{
		return _validity.load(std::memory_order_relaxed);
	}

	void enter() noexcept
	{
		_validity.store(true, std::memory_order_relaxed);
	}

	void exit();

	void notify_one(Strategy _strategy = Strategy::STRICT);

	void notify_all(Strategy _strategy = Strategy::STRICT);

	void notify(Size _size, Strategy _strategy = Strategy::STRICT);

	template <typename _Predicate>
	void notify_one(_Predicate _predicate);

	template <typename _Predicate>
	void notify_all(_Predicate _predicate);

	template <typename _Predicate>
	void notify(Size _size, _Predicate _predicate);

	void wait();

	template <typename _Predicate>
	void wait(_Predicate _predicate);

	template <typename _Rep, typename _Period>
	bool wait_for(const std::chrono::duration<_Rep, _Period>& _relative);

	template <typename _Rep, typename _Period, typename _Predicate>
	bool wait_for(const std::chrono::duration<_Rep, _Period>& _relative, \
		_Predicate _predicate);

	template <typename _Clock, typename _Duration>
	bool wait_until(const std::chrono::time_point<_Clock, _Duration>& _absolute);

	template <typename _Clock, typename _Duration, typename _Predicate>
	bool wait_until(const std::chrono::time_point<_Clock, _Duration>& _absolute, \
		_Predicate _predicate);
};

template <typename _Size>
void Condition<_Size>::exit()
{
	std::unique_lock lock(_mutex);
	if (!valid()) return;

	_validity.store(false, \
		std::memory_order_relaxed);
	lock.unlock();

	_condition.notify_all();
}

template <typename _Size>
void Condition<_Size>::notify_one(Strategy _strategy)
{
	std::unique_lock lock(_mutex);
	if (_strategy == Strategy::RELAXED) lock.unlock();

	_condition.notify_one();
}

template <typename _Size>
void Condition<_Size>::notify_all(Strategy _strategy)
{
	std::unique_lock lock(_mutex);
	if (_strategy == Strategy::RELAXED) lock.unlock();

	_condition.notify_all();
}

template <typename _Size>
void Condition<_Size>::notify(Size _size, \
	Strategy _strategy)
{
	std::unique_lock lock(_mutex);
	if (_strategy == Strategy::RELAXED)
		lock.unlock();

	for (decltype(_size) index = 0; \
		index < _size; ++index)
		_condition.notify_one();
}

template <typename _Size>
template <typename _Predicate>
void Condition<_Size>::notify_one(_Predicate _predicate)
{
	std::unique_lock lock(_mutex);
	if (!_predicate()) return;
	lock.unlock();

	_condition.notify_one();
}

template <typename _Size>
template <typename _Predicate>
void Condition<_Size>::notify_all(_Predicate _predicate)
{
	std::unique_lock lock(_mutex);
	if (!_predicate()) return;
	lock.unlock();

	_condition.notify_all();
}

template <typename _Size>
template <typename _Predicate>
void Condition<_Size>::notify(Size _size, \
	_Predicate _predicate)
{
	std::unique_lock lock(_mutex);
	if (!_predicate()) return;
	lock.unlock();

	for (decltype(_size) index = 0; \
		index < _size; ++index)
		_condition.notify_one();
}

template <typename _Size>
void Condition<_Size>::wait()
{
	std::unique_lock lock(_mutex);
	if (valid())
		_condition.wait(lock);
}

template <typename _Size>
template <typename _Predicate>
void Condition<_Size>::wait(_Predicate _predicate)
{
	std::unique_lock lock(_mutex);
	while (valid() && !_predicate())
		_condition.wait(lock);
}

template <typename _Size>
template <typename _Rep, typename _Period>
bool Condition<_Size>::wait_for(const std::chrono::duration<_Rep, _Period>& _relative)
{
	std::unique_lock lock(_mutex);
	return valid() \
		&& _condition.wait_for(lock, _relative) == std::cv_status::no_timeout;
}

template <typename _Size>
template <typename _Rep, typename _Period, typename _Predicate>
bool Condition<_Size>::wait_for(const std::chrono::duration<_Rep, _Period>& _relative, \
	_Predicate _predicate)
{
	std::unique_lock lock(_mutex);
	return _condition.wait_for(lock, _relative, \
		[this, &_predicate] { return !valid() || _predicate(); });
}

template <typename _Size>
template <typename _Clock, typename _Duration>
bool Condition<_Size>::wait_until(const std::chrono::time_point<_Clock, _Duration>& _absolute)
{
	std::unique_lock lock(_mutex);
	return valid() \
		&& _condition.wait_until(lock, _absolute) == std::cv_status::no_timeout;
}

template <typename _Size>
template <typename _Clock, typename _Duration, typename _Predicate>
bool Condition<_Size>::wait_until(const std::chrono::time_point<_Clock, _Duration>& _absolute, \
	_Predicate _predicate)
{
	std::unique_lock lock(_mutex);
	while (valid() && !_predicate() \
		&& _condition.wait_until(lock, _absolute) != std::cv_status::timeout);
	return _predicate();
}

ETERFREE_SPACE_END
