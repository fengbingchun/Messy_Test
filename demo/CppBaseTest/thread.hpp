#ifndef FBC_MESSY_TEST_THREAD_HPP_
#define FBC_MESSY_TEST_THREAD_HPP_

// Blog: http://blog.csdn.net/fengbingchun/article/details/53726760

/* reference:
	http://locklessinc.com/articles/pthreads_on_windows/
	http://locklessinc.com/downloads/winpthreads.h
	http://www.jmhartsoftware.com/Pthreads_Emulation.html
	https://sourceforge.net/p/log4c/log4c/ci/a4d3e19b3e55c1d5d66a5dc09a2603d9dcfcff52/tree/src/sd/sd_xplatform.h
	https://git.libav.org/?p=libav.git;a=blob;f=compat/w32pthreads.h;h=2fe2a5ab979ff676d1e7dba4a360306dde29a0f0;hb=HEAD
	https://github.com/krux/zookeeper-pkg/blob/master/src/c/src/winport.c
	https://my.oschina.net/mjRao/blog/359870
*/

#ifdef _MSC_VER

#include <windows.h>
#include <sys/timeb.h>
#include <process.h>

typedef HANDLE pthread_mutex_t;
typedef int pthread_condattr_t;
typedef HANDLE pthread_t;
typedef DWORD pthread_attr_t;

#define pthread_create(thrp, attr, func, arg)                               \
    (((*(thrp) = CreateThread(NULL, 0,                                     \
        (LPTHREAD_START_ROUTINE)(func), (arg), 0, NULL)) == NULL) ? -1 : 0)
#define pthread_join(thr, statusp)                                          \
    ((WaitForSingleObject((thr), INFINITE) == WAIT_OBJECT_0) &&            \
    ((statusp == NULL) ? 0 :                            \
    (GetExitCodeThread((thr), (LPDWORD)(statusp)) ? 0 : -1)))

#define PTHREAD_MUTEX_INITIALIZER {(void*)-1,-1,0,0,0,0}
#define pthread_mutex_lock(pobject) WaitForSingleObject(*pobject,INFINITE)
#define pthread_mutex_unlock(pobject) ReleaseMutex(*pobject)
#define pthread_mutex_init(pobject,pattr) (*pobject=CreateMutex(NULL,FALSE,NULL))
#define pthread_mutex_destroy(pobject) CloseHandle(*pobject)

/* Windows doesn't have this, so declare it ourselves. */
typedef struct timespec {
	/* long long in windows is the same as long in unix for 64bit */
	long long tv_sec;
	long long tv_nsec;
} timespec;

typedef struct {
	int waiters_count_;
	// Number of waiting threads.

	CRITICAL_SECTION waiters_count_lock_;
	// Serialize access to <waiters_count_>.

	HANDLE sema_;
	// Semaphore used to queue up threads waiting for the condition to
	// become signaled. 

	HANDLE waiters_done_;
	// An auto-reset event used by the broadcast/signal thread to wait
	// for all the waiting thread(s) to wake up and be released from the
	// semaphore. 

	size_t was_broadcast_;
	// Keeps track of whether we were broadcasting or signaling.  This
	// allows us to optimize the code if we're just signaling.
} pthread_cond_t;

static unsigned long long _pthread_time_in_ms(void)
{
	struct __timeb64 tb;

	_ftime64(&tb);

	return tb.time * 1000 + tb.millitm;
}

static unsigned long long _pthread_time_in_ms_from_timespec(const struct timespec *ts)
{
	unsigned long long t = ts->tv_sec * 1000;
	t += ts->tv_nsec / 1000000;

	return t;
}

static unsigned long long _pthread_rel_time_in_ms(const struct timespec *ts)
{
	unsigned long long t1 = _pthread_time_in_ms_from_timespec(ts);
	unsigned long long t2 = _pthread_time_in_ms();

	/* Prevent underflow */
	if (t1 < t2) return 0;
	return t1 - t2;
}

static int pthread_cond_init(pthread_cond_t *cv, const pthread_condattr_t * ignore)
{
	cv->waiters_count_ = 0;
	cv->was_broadcast_ = 0;
	cv->sema_ = CreateSemaphore(NULL, // no security
				       0, // initially 0
			      0x7fffffff, // max count
			           NULL); // unnamed 
	if (cv->sema_ == NULL)
		return GetLastError();

	InitializeCriticalSection(&cv->waiters_count_lock_);
	cv->waiters_done_ = CreateEvent(NULL, // no security
		                       FALSE, // auto-reset
		                       FALSE, // non-signaled initially
		                       NULL); // unnamed
	return (cv->waiters_done_ == NULL) ? GetLastError() : 0;
}

static int pthread_cond_destroy(pthread_cond_t *cond)
{
	CloseHandle(cond->sema_);
	DeleteCriticalSection(&cond->waiters_count_lock_);
	return (CloseHandle(cond->waiters_done_) == 0) ? GetLastError() : 0;
}

static int pthread_cond_signal(pthread_cond_t *cv)
{
	int have_waiters;
	EnterCriticalSection(&(cv->waiters_count_lock_));
	have_waiters = cv->waiters_count_ > 0;
	LeaveCriticalSection(&cv->waiters_count_lock_);

	// If there aren't any waiters, then this is a no-op.  
	if (have_waiters){
		return (ReleaseSemaphore(cv->sema_, 1, 0) == 0) ? GetLastError() : 0;
	}
	else
		return 0;
}

static int pthread_cond_broadcast(pthread_cond_t *cv)
{
	// This is needed to ensure that <waiters_count_> and <was_broadcast_> are
	// consistent relative to each other.
	int have_waiters = 0;
	EnterCriticalSection(&cv->waiters_count_lock_);

	if (cv->waiters_count_ > 0) {
		// We are broadcasting, even if there is just one waiter...
		// Record that we are broadcasting, which helps optimize
		// <pthread_cond_wait> for the non-broadcast case.
		cv->was_broadcast_ = 1;
		have_waiters = 1;
	}

	if (have_waiters) {
		// Wake up all the waiters atomically.
		ReleaseSemaphore(cv->sema_, cv->waiters_count_, 0);

		LeaveCriticalSection(&cv->waiters_count_lock_);

		// Wait for all the awakened threads to acquire the counting
		// semaphore. 
		WaitForSingleObject(cv->waiters_done_, INFINITE);
		// This assignment is okay, even without the <waiters_count_lock_> held 
		// because no other waiter threads can wake up to access it.
		cv->was_broadcast_ = 0;
	}
	else
		LeaveCriticalSection(&cv->waiters_count_lock_);

	return 0;
}

static int pthread_cond_wait(pthread_cond_t *cv, pthread_mutex_t *external_mutex)
{
	int last_waiter;
	// Avoid race conditions.
	EnterCriticalSection(&cv->waiters_count_lock_);
	cv->waiters_count_++;
	LeaveCriticalSection(&cv->waiters_count_lock_);

	// This call atomically releases the mutex and waits on the
	// semaphore until <pthread_cond_signal> or <pthread_cond_broadcast>
	// are called by another thread.
	SignalObjectAndWait(*external_mutex, cv->sema_, INFINITE, FALSE);

	// Reacquire lock to avoid race conditions.
	EnterCriticalSection(&cv->waiters_count_lock_);

	// We're no longer waiting...
	cv->waiters_count_--;

	// Check to see if we're the last waiter after <pthread_cond_broadcast>.
	last_waiter = cv->was_broadcast_ && cv->waiters_count_ == 0;

	LeaveCriticalSection(&cv->waiters_count_lock_);

	// If we're the last waiter thread during this particular broadcast
	// then let all the other threads proceed.
	if (last_waiter)
		// This call atomically signals the <waiters_done_> event and waits until
		// it can acquire the <external_mutex>.  This is required to ensure fairness. 
		SignalObjectAndWait(cv->waiters_done_, *external_mutex, INFINITE, FALSE);
	else
		// Always regain the external mutex since that's the guarantee we
		// give to our callers. 
		WaitForSingleObject(*external_mutex, INFINITE);

	return 0;
}

#else // linux

#include <pthread.h>

#endif // _MSC_VER

#endif // FBC_MESSY_TEST_THREAD_HPP_
