#include "test_thread.hpp"
#include <iostream>
#include "thread.hpp"

// test code reference: http://blog.csdn.net/fengbingchun/article/details/48579725

void* run1(void* para)
{
	std::cout << "start new thread!" << std::endl;

	//sleep(5);//suspend 5 s，在正式的代码中，一般不要用sleep函数
	int* iptr = (int*)((void**)para)[0];
	float* fptr = (float*)((void**)para)[1];
	char* str = (char*)((void**)para)[2];
	std::cout << *iptr << "    " << *fptr << "    " << str << std::endl;

	std::cout << "end new thread!" << std::endl;

	return ((void *)0);
}

int test_create_thread()
{
	pthread_t pid;//thread handle
	int ival = 1;
	float fval = 10.0f;
	char buf[] = "func";
	void* para[3] = { &ival, &fval, buf };

	pthread_create(&pid, NULL, run1, para);

	// 新线程创建之后主线程如何运行----主线程按顺序继续执行下一行程序
	std::cout << "main thread!" << std::endl;

	// 新线程结束时如何处理----新线程先停止，然后作为其清理过程的一部分，等待与另一个线程合并或“连接”
	pthread_join(pid, NULL);

	return 0;
}

/////////////////////////////////////////////////////////
pthread_t tid[2];
int counter = 0;
pthread_mutex_t lock;

void* run2(void* arg)
{
	pthread_mutex_lock(&lock);

	unsigned long i = 0;
	counter += 1;
	std::cout << "Job " << counter << " started!" << std::endl;
	for (i = 0; i<(0xFFFFFFFF); i++);
	std::cout << "Job " << counter << " finished!" << std::endl;

	pthread_mutex_unlock(&lock);

	return NULL;
}

int test_thread_mutex()
{
	int i = 0, err = -1;

	pthread_mutex_init(&lock, NULL);

	while (i < 2) {
		pthread_create(&(tid[i]), NULL, &run2, NULL);
		i++;
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_mutex_destroy(&lock);

	return 0;
}

/////////////////////////////////////////////////
pthread_mutex_t count_lock1;
pthread_cond_t count_nonzero1;
unsigned count1 = 0;

void* decrement_count1(void* arg)
{
	pthread_mutex_lock(&count_lock1);
	std::cout << "decrement_count get count_lock" << std::endl;

	while (count1 == 0) {
		std::cout << "decrement_count count == 0" << std::endl;

		std::cout << "decrement_count before cond_wait" << std::endl;
		pthread_cond_wait(&count_nonzero1, &count_lock1);
		std::cout << "decrement_count after cond_wait" << std::endl;
	}

	count1 = count1 + 1;

	pthread_mutex_unlock(&count_lock1);

	return NULL;
}

void* increment_count1(void* arg)
{
	pthread_mutex_lock(&count_lock1);
	std::cout << "increment_count get count_lock" << std::endl;

	if (count1 == 0) {
		std::cout << "increment_count before cond_signal" << std::endl;
		pthread_cond_signal(&count_nonzero1);
		std::cout << "increment_count after cond_signal" << std::endl;
	}

	count1 = count1 + 1;

	pthread_mutex_unlock(&count_lock1);

	return NULL;
}

int test_thread_cond1()
{
	pthread_t tid1, tid2;

	pthread_mutex_init(&count_lock1, NULL);
	pthread_cond_init(&count_nonzero1, NULL);

	pthread_create(&tid1, NULL, decrement_count1, NULL);
	Sleep(2000); // == linux sleep(2)

	pthread_create(&tid2, NULL, increment_count1, NULL);
	Sleep(2000);

	std::cout << "count1 = " << count1 << std::endl;
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_mutex_destroy(&count_lock1);
	pthread_cond_destroy(&count_nonzero1);

	return 0;
}

////////////////////////////////////////////////////////////
pthread_mutex_t counter_lock2;
pthread_cond_t counter_nonzero2;
int counter2 = 0;

void* decrement_counter2(void* argv)
{
	std::cout << "counter(decrement): " << counter2 << std::endl;

	pthread_mutex_lock(&counter_lock2);
	while (counter2 == 0)
		pthread_cond_wait(&counter_nonzero2, &counter_lock2); //进入阻塞(wait)，等待激活(signal)

	std::cout << "counter--(decrement, before): " << counter2 << std::endl;
	counter2--; //等待signal激活后再执行
	std::cout << "counter--(decrement, after): " << counter2 << std::endl;
	pthread_mutex_unlock(&counter_lock2);

	return NULL;
}

void* increment_counter2(void* argv)
{
	std::cout << "counter(increment): " << counter2 << std::endl;

	pthread_mutex_lock(&counter_lock2);
	if (counter2 == 0)
		pthread_cond_signal(&counter_nonzero2); //激活(signal)阻塞(wait)的线程(先执行完signal线程，然后再执行wait线程)  

	std::cout << "counter++(increment, before): " << counter2 << std::endl;
	counter2++;
	std::cout << "counter++(increment, after): " << counter2 << std::endl;
	pthread_mutex_unlock(&counter_lock2);

	return NULL;
}

int test_thread_cond2()
{
	std::cout << "counter: " << counter2 << std::endl;
	pthread_mutex_init(&counter_lock2, NULL);
	pthread_cond_init(&counter_nonzero2, NULL);

	pthread_t thd1, thd2;

	pthread_create(&thd1, NULL, decrement_counter2, NULL);

	pthread_create(&thd2, NULL, increment_counter2, NULL);

	int counter2 = 0;
	while (counter2 != 10) {
		std::cout << "counter(main): " << counter2 << std::endl;
		Sleep(1);
		counter2++;
	}

	pthread_join(thd1, NULL);
	pthread_join(thd2, NULL);
	pthread_mutex_destroy(&counter_lock2);
	pthread_cond_destroy(&counter_nonzero2);

	return 0;
}

///////////////////////////////////////////////////
pthread_mutex_t counter_lock3_1, counter_lock3_2;
pthread_cond_t counter_nonzero3_1, counter_nonzero3_2;
int counter3 = 0;

void* decrement_increment_counter3(void* argv)
{
	std::cout << "start counter: " << counter3 << std::endl;

	pthread_mutex_lock(&counter_lock3_1);
	std::cout << "counter(decrement): " << counter3 << std::endl;
	while (counter3 == 1)
		pthread_cond_wait(&counter_nonzero3_1, &counter_lock3_1); //进入阻塞(wait)，等待激活(signal)

	std::cout << "counter--(decrement, before): " << counter3 << std::endl;
	counter3--; //等待signal激活后再执行  
	std::cout << "counter--(decrement, after): " << counter3 << std::endl;
	pthread_mutex_unlock(&counter_lock3_1);

	pthread_mutex_lock(&counter_lock3_2);
	std::cout << "counter(increment): " << counter3 << std::endl;
	if (counter3 == 0)
		pthread_cond_signal(&counter_nonzero3_2); //激活(signal)阻塞(wait)的线程(先执行完signal线程，然后再执行wait线程)  

	std::cout << "counter++(increment, before): " << counter3 << std::endl;
	counter3++;
	std::cout << "counter++(increment, after): " << counter3 << std::endl;
	pthread_mutex_unlock(&counter_lock3_2);

	return NULL;
}

int test_thread_cond3()
{
	std::cout << "counter: " << counter3 << std::endl;
	pthread_mutex_init(&counter_lock3_1, NULL);
	pthread_mutex_init(&counter_lock3_2, NULL);
	pthread_cond_init(&counter_nonzero3_1, NULL);
	pthread_cond_init(&counter_nonzero3_2, NULL);

	pthread_t thd;

	pthread_create(&thd, NULL, decrement_increment_counter3, NULL);

	counter3 = 0;
	while (counter3 != 10) {
		std::cout << "counter(main): " << counter3 << std::endl;
		Sleep(1000);
		counter3++;
	}

	pthread_join(thd, NULL);
	pthread_mutex_destroy(&counter_lock3_1);
	pthread_mutex_destroy(&counter_lock3_2);
	pthread_cond_destroy(&counter_nonzero3_1);
	pthread_cond_destroy(&counter_nonzero3_2);

	return 0;
}
