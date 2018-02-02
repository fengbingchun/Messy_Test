#include <vector>
#include <iostream>
#include <assert.h>

#include "vector.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/51510916

int test_vector_init()
{
	std::vector<int> a; // 声明一个int型向量a,size为0
	std::vector<int> b(10); // 声明一个初始size为10的向量
	std::vector<int> c(10, 1); // 声明一个初始size为10且初始值都为1的向量
	std::vector<int> d(b); // 声明并用向量b初始化向量d
	std::vector<int> e(c.begin(), c.begin() + 3); // 将c向量中从第0个到第2个(共3个)作为向量e的初始值,size为3

	int n[] = { 1, 2, 3, 4, 5 };
	std::vector<int> f(n, n + 5); // 将数组n的前5个元素作为向量f的初值,size为5
	std::vector<int> g(&n[1], &n[4]); // 将n[1] - n[4]范围内的元素作为向量g的初值,size为3

	std::vector<std::string> v(5, "hello");
	std::vector<std::string> v2(v.begin(), v.end());
	assert(v == v2);

	assert(v.begin() + v.size() == v.end());
	assert(v.end() - v.size() == v.begin());

	std::vector<int> array{ 9, 7, 5, 3, 1 };
	std::cout << "array size: "<< array.size() << std::endl; // 5

	return 0;
}

int test_vector_access()
{
	int n[10];
	for (int i = 0; i < 10; i++) {
		n[i] = i;
	}

	std::vector<int> a(n, n + 10);

	// 对其中部分元素进行输入
	std::cin >> a[2];
	std::cin >> a[5];
	std::cin >> a[6];

	// 输出
	for (int i = 0; i < a.size(); i++) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;

	// 使用遍历器(又称迭代器)进行输出
	// vector类的迭代器除了支持通用的前缀自增运算符外，还支持算术运算：it + n、it - n、it2 - it1
	std::vector<int>::iterator t;
	for (t = a.begin(); t != a.end(); t++) {
		std::cout << *t << " ";
	}
	std::cout << std::endl;

	for (std::vector<int>::const_iterator p = a.begin(); p != a.end(); p++) {
		std::cout << *p << " ";
	}
	std::cout << std::endl;

	size_t i = 0;
	int* x = a.data(); //返回指向内存中数组第一个元素的指针
	*x = -111;
	std::cout << "a[0]: " << a[0] << std::endl; // -111

	return 0;
}

int test_vector_operation()
{
	int n[10], m[15];
	for (int i = 0; i < 10; i++) {
		n[i] = i;
		m[i] = i + 20;
	}

	std::vector<int> a(n, n + 10);
	std::vector<int> b(m, m + 15);
	std::vector<int> x;
	x = a; // 赋值

	std::cout << "x size: "<<a.size() << std::endl; // 获取向量中的元素个数, 10
	std::cout << "x capacity: " << x.capacity() << std::endl; // 返回当前存储空间能够容纳的元素数，容器x能够存储的元素个数，10 (x.capacity() >= x.size())
	std::cout << "x max size: " << x.max_size() << std::endl; // 容器x能容纳的最大元素个数, 4611686018427387903
	x.reserve(15); // 预留存储空间，确保x.capacity() >= 15
	std::cout << "x capacity after reserve: " << x.capacity() << std::endl; // 15
	x.shrink_to_fit();
	x.resize(5); // 改变容器中可存储元素的个数,确保返回后，有x.size() == 5, 如果之前x.size() < 5, 那么用默认值补全
	std::cout << "x size after resize: " << x.size() << std::endl; // 5

	std::vector<int>::reference ref1 = b.front(); // 返回容器中第一个元素的引用(容器必须非空), 20
	std::vector<int>::reference ref2 = x.back(); // 返回容器中最后一个元素的引用(容器必须非空), 4
	int value = b[5]; // 返回下标为5的元素的引用(下标从0开始，如果下标不正确，则属于未定义行为)， 25
	std::vector<int>::reference ref3 = b.at(5); // 返回下标为pos的元素的引用；如果下标不正确，则抛出异常, 25
	x.push_back(-100); // 将元素添加到容器末尾,向容器末尾添加一个元素
	value = x[x.size() - 1]; // -100
	std::cout << "x size after push_back: " << x.size() << std::endl; // 6
	x.pop_back(); // 删除最后一个元素, 弹出容器中最后一个元素（容器必须非空）
	value = x[x.size() - 1]; // 4
	std::cout << "x size after pop_back: " << x.size() << std::endl; // 5

	x.assign(10, -1); // 赋值，用指定元素序列替换容器内所有元素
	std::cout << "x size after assign: " << x.size() << std::endl; // 10
	std::cout << "x[0]: " << x[0] << std::endl; // -1

	std::cout << "a is empty: "<< a.empty() << std::endl; // 判断向量是否为空, 0
	std::cout << "a size: " << a.size() << std::endl; // 获取向量中的元素个数, 10
	a.clear(); // 删除全部内容, 清空向量中的元素,相当于调用erase(begin(), end())
	std::cout << "size after clear: " << a.size() << std::endl; // 0

	std::vector<int> c;
	c = b; // 将b向量复制到c向量中

	std::cout << "a == b ?: " << (a == b) << std::endl; // == 、 != 、>、 >= 、<、 <= , 采用字典排序策略比较,a向量与b向量比较, 相等则返回1, 0
	std::cout << "c == b ?: " << (c == b) << std::endl; // == 、 != 、>、 >= 、<、 <= , 采用字典排序策略比较,c向量与b向量比较, 相等则返回1, 1

	// 插入和删除操作将发生元素的移动（为了保持连续存储的性质），所以之前的迭代器可能失效
	// 任何改变容器大小的操作都可能造成以前的迭代器失效
	std::cout << "b size: " << b.size() << std::endl; // 15
	b.insert(b.begin(), -1); // 将-1插入到向量b的起始位置前
	std::cout << "b[0]: " << b[0] << std::endl; // -1
	std::cout << "b size: " << b.size() << std::endl; // 16

	b.insert(b.begin() + 5, 3, -1); //将-1分别插入到向量元素位置的5-8处(共3个元素)
	for (int i = 0; i < b.size(); i++) {
		std::cout << b[i] << "  "; // -1 20 21 22 23 -1 -1 -1 24 25 ...
	}
	std::cout<<std::endl;

	std::vector<int> d(5, 1);
	std::vector<int> e(10);
	e.insert(e.begin(), d.begin(), d.end()); //将d.begin(), d.end()之间的全部元素插入到e.begin()前
	for (int i = 0; i < e.size(); i++) {
		std::cout << e[i] << "  "; // 1 1 1 1 1 0 0 0 ...
	}
	std::cout << std::endl;

	std::cout << "b size: " << b.size() << std::endl; // 19
	b.erase(b.begin()); // 将起始位置的元素删除
	std::cout << "b size: " << b.size() << std::endl; // 18
	b.erase(b.begin(), b.begin() + 3); // 将(b.begin(), b.begin()+3)之间的元素删除
	std::cout << "b size: " << b.size() << std::endl; // 15

	b.swap(c); // 交换vector的内容, a向量与c向量进行交换
	for (int i = 0; i < b.size(); i++) {
		std::cout << b[i] << "  ";
	}
	std::cout << std::endl;

	for (int i = 0; i < c.size(); i++) {
		std::cout << c[i] << "  ";
	}
	std::cout << std::endl;

	return 0;
}

int test_vector_two_dimension()
{
	// reference: http://www.cnblogs.com/mr-wid/archive/2013/01/22/2871105.html

	std::vector< std::vector<int> > b(10, std::vector<int>(5, -1));

	// 对部分数据进行输入
	std::cin >> b[1][1];
	std::cin >> b[2][2];
	std::cin >> b[3][3];

	// 全部输出
	for (int m = 0; m < b.size(); m++) { //b.size()获取行向量的大小
		for (int n = 0; n < b[m].size(); n++) { //获取向量中具体每个向量的大小
			std::cout << b[m][n] << "  ";
		}
		std::cout << std::endl;
	}

	return 0;
}

