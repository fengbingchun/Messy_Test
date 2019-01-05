#include "standard_template_library.hpp"
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <ctime>
#include <memory>
#include <numeric>
#include <functional>

// Blog: https://blog.csdn.net/fengbingchun/article/details/85470197

namespace standard_template_library_ {

// reference: 《提高C++性能的编程技术》：第十一章：标准模板库
namespace {
template<class T>
void arrayInsert(T* a, const T* collection, int size)
{
	for (int k = 0; k < size; ++k) {
		a[k] = 	collection[k];
	}
}

template<class T>
void arrayTraverse(const T* a, int size)
{
	T sum = std::accumulate(&a[0], &a[size], 0);
}

template<class T>
void arrayFind(const T* a, const T* collection, int size)
{
	T const value = collection[size/2];
	T* tmp = const_cast<T*>(a);
	T* p = std::find(&tmp[0], &tmp[size], value); 
}

template<class T>
void vectorInsert(std::vector<T>* v, const T* collection, int size)
{
	for (int k = 0; k < size; ++k) {
		v->push_back(collection[k]);
	}
}

template<class T>
void vectorInsertFront(std::vector<T>* v, const T* collection, int size)
{
	for (int k = 0; k < size; ++k) {
		v->insert(v->begin(), collection[k]);
	}
}

template<class T>
void vectorDelete(std::vector<T>* v)
{
	while (!v->empty()) {
		v->pop_back();
	}
}

template<class T>
void vectorDeleteFront(std::vector<T>* v)
{
	while (!v->empty()) {
		v->erase(v->begin());
	}
}

template<class T>
void vectorTraverse(const std::vector<T>* v, int size)
{
	T sum = std::accumulate(v->cbegin(), v->cend(), 0);
}

template<class T>
void vectorFind(const std::vector<T>* v, const T* collection, int size)
{
	T const value = collection[size/2];
	auto it = std::find(v->cbegin(), v->cend(), value);
}

template<class T>
void listInsert(std::list<T>* l, const T* collection, int size)
{
	for (int k = 0; k < size; ++k) {
		l->push_back(collection[k]);
	}
}

template<class T>
void listInsertFront(std::list<T>* l, const T* collection, int size)
{
	for (int k = 0; k < size; ++k) {
		l->push_front(collection[k]);
	}
}

template<class T>
void listDelete(std::list<T>* l)
{
	while (!l->empty()) {
		l->pop_back();
	}
}

template<class T>
void listDeleteFront(std::list<T>* l)
{
	while (!l->empty()) {
		l->pop_front();
	}
}

template<class T>
void listTraverse(const std::list<T>* l, int size)
{
	T sum = std::accumulate(l->cbegin(), l->cend(), 0);
}

template<class T>
void listFind(const std::list<T>*l, const T* collection, int size)
{
	T const value = collection[size/2];
	auto it = std::find(l->cbegin(), l->cend(), value);
}

template<class T>
void multisetInsert(std::multiset<T>* s, const T* collection, int size)
{
	for (int k = 0; k < size; ++k) {
		s->insert(collection[k]);
	}
}

template<class T>
void multisetFind(const std::multiset<T>* s, const T* collection, int size)
{
	T const value = collection[size/2];
	
	// 当查找多重集容器时，使用std::find并不是最佳的选择
	//auto it = std::find(s->cbegin(), s->cend(), value);
	auto it = s->find(value);
}

int* genIntData(int size)
{
	std::srand(std::time(nullptr));
	int* data = new int[size];
	std::generate(&data[0], &data[size], std::rand);
	return data;
}

int mult(int x, int y)
{
	return (x*y);
}

class Mult {
public:
	int operator()(int x, int y) const { return (x*y); }
};

} // namespace

int test_standard_template_library_1()
{
	std::chrono::high_resolution_clock::time_point time_start, time_end;
	const int count{400000}, count2{10000}, count3{200000000};
	int* data = genIntData(count);

{ // normal array insert back operation
	std::unique_ptr<int[]> arr(new int[count]);	
	time_start = std::chrono::high_resolution_clock::now();
	arrayInsert(arr.get(), data, count);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "first value: %d, array insert back time spend: %f seconds\n",
		arr.get()[0], (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // vector insert back operation
	std::vector<int> vec;	
	time_start = std::chrono::high_resolution_clock::now();
	vectorInsert(&vec, data, count);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "first value: %d, vector insert back time spend: %f seconds\n",
		vec[0], (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // list insert back operation
	std::list<int> l;	
	time_start = std::chrono::high_resolution_clock::now();
	listInsert(&l, data, count);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "first value: %d, list insert back time spend: %f seconds\n",
		*(l.cbegin()), (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // multiset insert back operation
	std::multiset<int> s;	
	time_start = std::chrono::high_resolution_clock::now();
	multisetInsert(&s, data, count);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "first value: %d, multiset insert back time spend: %f seconds\n",
		*(s.cbegin()), (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // vector insert front operation
	std::vector<int> vec;	
	time_start = std::chrono::high_resolution_clock::now();
	vectorInsertFront(&vec, data, count);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "first value: %d, vector insert front time spend: %f seconds\n",
		vec[0], (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // list insert front operation
	std::list<int> l;	
	time_start = std::chrono::high_resolution_clock::now();
	listInsertFront(&l, data, count);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "first value: %d, list insert front time spend: %f seconds\n",
		*(l.cbegin()), (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // vector delete back operation
	std::vector<int> vec(data, data+count);
	time_start = std::chrono::high_resolution_clock::now();
	vectorDelete(&vec);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "vector size: %d, vector delete back time spend: %f seconds\n",
		vec.size(), (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // list delete back operation
	std::list<int> l(data, data+count);	
	time_start = std::chrono::high_resolution_clock::now();
	listDelete(&l);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "list size: %d, list delete back time spend: %f seconds\n",
		l.size(), (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // vector delete front operation
	std::vector<int> vec(data, data+count);
	time_start = std::chrono::high_resolution_clock::now();
	vectorDeleteFront(&vec);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "vector size: %d, vector delete front time spend: %f seconds\n",
		vec.size(), (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // list delete front operation
	std::list<int> l(data, data+count);	
	time_start = std::chrono::high_resolution_clock::now();
	listDeleteFront(&l);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "list size: %d, list delete front time spend: %f seconds\n",
		l.size(), (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // normal array traverse operation
	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count2; ++i)
		arrayTraverse(data, count);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "first value: %d, array traverse time spend: %f seconds\n",
		data[0], (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // vector traverse operation
	std::vector<int> vec(data, data+count);
	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count2; ++i)
		vectorTraverse(&vec, count);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "first value: %d, vector traverse time spend: %f seconds\n",
		vec[0], (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // list traverse operation
	std::list<int> l(data, data+count);	
	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count2; ++i)
		listTraverse(&l, count);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "first value: %d, list traverse time spend: %f seconds\n",
		*l.cbegin(), (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // normal array find operation
	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count2; ++i)
		arrayFind(data, data, count);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "first value: %d, array find time spend: %f seconds\n",
		data[0], (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // vector find operation
	std::vector<int> vec(data, data+count);
	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count2; ++i)
		vectorFind(&vec, data, count);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "first value: %d, vector find time spend: %f seconds\n",
		vec[0], (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // list find operation
	std::list<int> l(data, data+count);	
	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i< count2; ++i)
		listFind(&l, data, count);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "first value: %d, list find time spend: %f seconds\n",
		*l.cbegin(), (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // multiset find operation
	std::multiset<int> s;	
	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count2; ++i)
		multisetFind(&s, data, count);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "first value: %d, multiset find time spend: %f seconds\n",
		*(s.cbegin()), (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

	int a[10] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23};
	int init = 1, product = 0;

{ // accumulate operation: function pointer	
	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count3; ++i)
		product = std::accumulate(&a[0], &a[10], init, mult);
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "value: %d, accumulate function pointer time spend: %f seconds\n",
		product, (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // accumulate operation: function object
	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count3; ++i)
		product = std::accumulate(&a[0], &a[10], init, Mult());
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "value: %d, accumulate function object time spend: %f seconds\n",
		product, (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

{ // accumulate operation: function object(std)	
	time_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < count3; ++i)
		product = std::accumulate(&a[0], &a[10], init, std::multiplies<int>());
	time_end = std::chrono::high_resolution_clock::now();	
	fprintf(stdout, "value: %d, accumulate function object(std) time spend: %f seconds\n",
		product, (std::chrono::duration_cast<std::chrono::duration<double>>(time_end-time_start)).count());
}

	delete [] data;
	return 0;
}

} // namespace standard_template_library_


