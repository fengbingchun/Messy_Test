#include "funset.hpp"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <string>
#include <cstdint>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>
#ifdef _MSC_VER
#include <intrin.h>
#include <Windows.h>
#include <Iphlpapi.h>

#pragma comment(lib, "IPHLPAPI.lib")
#else
#include <sys/ioctl.h>
#include <net/if.h> 
#include <unistd.h>
#include <netinet/in.h>
#endif

/////////////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/136154655
int test_variables_init()
{
	int val; // no initializer(default initialization): 在大多数情况下,默认初始化不执行初始化,并且使变量具有不确定的值


	// 1.using "="
	int val1 = 1; // copy initialization: 这种初始化形式是从C继承的
	std::cout << "val1:" << val1 << "\n"; // val1:1


	// 2.constructor initialization: parentheses
	int val2(2); // direct initialization
	std::cout << "val2:" << val2 << "\n"; // val2:2

	int val3 = (3);
	std::cout << "val3:" << val3 << "\n"; // val3:3

	// 构造函数初始化和旧的普通初始化方式(=)的区别在于,它总是返回括号中的最后一个值,无论它的大小或符号是什么
	int val4 = (4, 5, 6, 7, -8);
	std::cout << "val4:" << val4 << "\n"; // val4:-8


	// 3.uniform initialization: curly braces
	int val5{ 9 }; // direct list initialization
	std::cout << "val5:" << val5 << "\n"; // val5:9

	int val6 = { 10 }; // copy list initialization
	std::cout << "val6:" << val6 << "\n"; // val6:10

	// 与构造函数初始化不同,统一初始化方法只能采用大括号中的一个值,提供多个值将返回编译错误
	//int val7 = { 11, 12 }; // error C2440: "初始化": 无法从"initializer list"转换为"int"

	int val8{}; // value initialization
	int val12{ 0 }; // explicit initialization to value 0
	std::cout << "val8:" << val8 << "\n"; // val8:0

	// 列表初始化中的"缩小转换(narrowing conversions)"格式不正确
	//int val9{ 4.5 }; // error C2397: 从"double"转换到"int"需要收缩转换
	int val10 = 4.5; // warning C4244: "初始化": 从"double"转换到"int",可能丢失数据
	int val11(4.5); // warning C4244: "初始化": 从"double"转换到"int",可能丢失数据

	return 0;
}

/////////////////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/124559175
namespace common {

namespace internal {
	char* name() { return "spring"; }
	const char* city = "BeiJing";
} // namespace internal

namespace detail {
	class Addr {
	public:
		static char* csdn() { return "https://blog.csdn.net/fengbingchun"; }
		static char* github() { return "https://github.com/fengbingchun"; }

		Addr() = delete;
	}; // class Addr
} // namespace detail

} // namesapce common

int test_namespace_detail_internal()
{
	fprintf(stdout, "name: %s, city: %s\n", common::internal::name(), common::internal::city);
	fprintf(stdout, "csdn addr: %s\ngithub addr: %s\n", common::detail::Addr::csdn(), common::detail::Addr::github());
	return 0;
}

// Blog: https://blog.csdn.net/fengbingchun/article/details/117591214
int test_load_big_file()
{
	fprintf(stdout, "int32_t: %d, uint32_t: %d\n", sizeof(int32_t), sizeof(uint32_t));
	fprintf(stdout, "int64_t: %d, uint64_t: %d\n", sizeof(int64_t), sizeof(uint64_t));
	fprintf(stdout, "int: %d\n", sizeof(int));
	fprintf(stdout, "long: %d, long long: %d, size_t: %d\n", sizeof(long), sizeof(long long), sizeof(size_t));

#ifdef _MSC_VER
	const char* name = "../../../testdata/test.tar";
#else
	const char* name = "testdata/test.tar";
#endif

	FILE* file = fopen(name, "rb");
	if (!file) {
		fprintf(stderr, "fail to open file: %s\n", name);
		return -1;
	}

#ifdef _MSC_VER
	auto ret = _fseeki64(file, 0, SEEK_END);
	if (ret != 0) {
		fprintf(stderr, "fail to _fseeki64: %d\n", ret);
		return -1;
	}

	auto length = _ftelli64(file);
	fprintf(stdout, "file length: %lld\n", length);
#else
	auto ret = fseek(file, 0, SEEK_END);
	if (ret != 0) {
		fprintf(stderr, "fail to _fseeki64: %d\n", ret);
		return -1;
	}

	auto length = ftell(file);
	fprintf(stdout, "file length: %lld\n", length);
#endif

	fclose(file);
	return 0;
}

namespace {

#ifdef _MSC_VER
// Blog: https://blog.csdn.net/fengbingchun/article/details/108940548
int process_programming_windows()
{
	char filename[MAX_PATH];
	auto size = GetModuleFileName(nullptr, filename, MAX_PATH);
	if (size == 0) {
		fprintf(stderr, "fail to GetModuleFileName\n");
		return -1;
	}

	// reference: https://docs.microsoft.com/en-us/windows/win32/procthread/creating-processes
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	char argument[512];
	//sprintf(argument, "\"%s\" C:\\windows\\system32\\cmd.exe", filename);
	sprintf(argument, "C:\\windows\\system32\\cmd.exe");

	// Start the child process
	if (!CreateProcess(nullptr,
		argument,						// Command line
		nullptr,						// Process handle not inheritable
		nullptr,						// Thread handle not inheritable
		false,							// Set handle inheritance to FALSE
		0,								// No creation flags
		nullptr,						// Use parent's environment block
		nullptr,						// Use parent's starting directory 
		&si,							// Pointer to STARTUPINFO structure
		&pi)							// Pointer to PROCESS_INFORMATION structure
		) {
		fprintf(stderr, "fail to CreateProcess: %d\n", GetLastError());
		return -1;
	}

	fprintf(stdout, "##### success to create child process #####\n");
	// Wait until child process exits
	WaitForSingleObject(pi.hProcess, INFINITE);
	fprintf(stdout, "##### child process exit #####\n");

	// Close process and thread handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}
#endif

#ifdef __linux__
// Blog: https://blog.csdn.net/fengbingchun/article/details/108949575
void test_fork_1()
{
	// reference: https://www.geeksforgeeks.org/fork-system-call/
	fork();
	fork();
	fork();
	// "hello"的打印次数等于创建的进程数,进程总数为2^n,其中n是fork调用的数目
	fprintf(stdout, "hello\n"); // 注:总共会输出8次hello
}

void test_fork_2()
{
	// reference: https://www.geeksforgeeks.org/fork-system-call/
	pid_t f = fork();

	// child process because return value zero
	if (f == 0) {
		fprintf(stdout, "hello from child: parent pid: %d, my(child) pid: %d\n", getppid(), getpid());
	}
	// parent process because return value non-zero
	else if (f > 0) {
		fprintf(stdout,	"hello from parent: my(parent) pid: %d\n", getpid());
	} else {
		fprintf(stderr, "unable to create child process\n");
	}
}

int process_programming_linux()
{
	//test_fork_1();
	test_fork_2();
	return 0;
}
#endif

} // namespace

int test_process_programming_1()
{
#ifdef _MSC_VER
	return process_programming_windows();
#else
	return process_programming_linux();
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/108874436
namespace {

#ifdef __linux__
// reference: https://stackoverflow.com/questions/6491566/getting-the-machine-serial-number-and-cpu-id-using-c-c-in-linux
inline void native_cpuid(unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
{
	// ecx is often an input as well as an output
	asm volatile("cpuid"
		: "=a" (*eax),
		  "=b" (*ebx),
		  "=c" (*ecx),
		  "=d" (*edx)
		: "0" (*eax), "2" (*ecx));
}
#endif

} // namespace

int get_mac_and_cpuid()
{
	// get mac
#ifdef _MSC_VER
	// reference: https://stackoverflow.com/questions/13646621/how-to-get-mac-address-in-windows-with-c
	PIP_ADAPTER_INFO AdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
	if (AdapterInfo == nullptr) {
		fprintf(stderr, "fail to malloc\n");
		return -1;
	}

	DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);
	std::unique_ptr<char[]> mac_addr(new char[18]);

	// Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) {
		free(AdapterInfo);
		AdapterInfo = (IP_ADAPTER_INFO *)malloc(dwBufLen);
		if (AdapterInfo == nullptr) {
			fprintf(stderr, "fail to malloc\n");
			return -1;
		}
	}

	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
		for (PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo; pAdapterInfo != nullptr; pAdapterInfo = pAdapterInfo->Next) {
			// technically should look at pAdapterInfo->AddressLength and not assume it is 6.
			if (pAdapterInfo->AddressLength != 6) continue;
			if (pAdapterInfo->Type != MIB_IF_TYPE_ETHERNET) continue;

			sprintf(mac_addr.get(), "%02X:%02X:%02X:%02X:%02X:%02X",
				pAdapterInfo->Address[0], pAdapterInfo->Address[1],
				pAdapterInfo->Address[2], pAdapterInfo->Address[3],
				pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
			fprintf(stdout, "mac address: %s\n", mac_addr.get());

			break;
		}
	}
	free(AdapterInfo);
#else
	// reference: https://stackoverflow.com/questions/1779715/how-to-get-mac-address-of-your-machine-using-a-c-program/35242525
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		fprintf(stderr, "fail to socket: %d\n", sock);
		return -1;
	};

	struct ifconf ifc;
	char buf[1024];
	int success = 0;

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = buf;
	if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) {
		fprintf(stderr, "fail to ioctl: SIOCGIFCONF\n");
		return -1;
	}

	struct ifreq* it = ifc.ifc_req;
	const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));
	struct ifreq ifr;

	for (; it != end; ++it) {
		strcpy(ifr.ifr_name, it->ifr_name);
		if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
			if (!(ifr.ifr_flags & IFF_LOOPBACK)) { // don't count loopback
				if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
					success = 1;
					break;
				}
			}
		} else { 
			fprintf(stderr, "fail to ioctl: SIOCGIFFLAGS\n");
			return -1;
		 }
	}

	unsigned char mac_address[6];
	if (success) memcpy(mac_address, ifr.ifr_hwaddr.sa_data, 6);
	fprintf(stdout, "mac address: %02X:%02X:%02X:%02X:%02X:%02X\n", mac_address[0], mac_address[1], mac_address[2], mac_address[3], mac_address[4], mac_address[5]);
#endif

	// Capture vendor string
	char vendor[0x20];
	memset(vendor, 0, sizeof(vendor));

	// get cpid
#ifdef _MSC_VER
	// reference: https://docs.microsoft.com/en-us/cpp/intrinsics/cpuid-cpuidex?view=vs-2019
	std::array<int, 4> cpui;
	// Calling __cpuid with 0x0 as the function_id argument gets the number of the highest valid function ID
	__cpuid(cpui.data(), 0);
	int nIds_ = cpui[0];

	std::vector<std::array<int, 4>> data_;  
	for (int i = 0; i <= nIds_; ++i) {
		__cpuidex(cpui.data(), i, 0);
		data_.push_back(cpui);

		fprintf(stdout, "%08X-%08X-%08X-%08X\n", cpui[0], cpui[1], cpui[2], cpui[3]);
	}

	*reinterpret_cast<int*>(vendor) = data_[0][1];
	*reinterpret_cast<int*>(vendor + 4) = data_[0][3];
	*reinterpret_cast<int*>(vendor + 8) = data_[0][2];
	fprintf(stdout, "vendor: %s\n", vendor); // GenuineIntel or AuthenticAMD or other
	fprintf(stdout, "vendor serialnumber: %08X%08X\n", data_[1][3], data_[1][0]);
#else
	unsigned eax, ebx, ecx, edx;

	eax = 0; // processor info and feature bits
	native_cpuid(&eax, &ebx, &ecx, &edx);
	fprintf(stdout, "%d, %d, %d, %d\n", eax, ebx, ecx, edx);

	*reinterpret_cast<int*>(vendor) = ebx;
	*reinterpret_cast<int*>(vendor + 4) = edx;
	*reinterpret_cast<int*>(vendor + 8) = ecx;
	fprintf(stdout, "vendor: %s\n", vendor); // GenuineIntel or AuthenticAMD or other

	eax = 1; // processor serial number
	native_cpuid(&eax, &ebx, &ecx, &edx);

	// see the CPUID Wikipedia article on which models return the serial number in which registers
	printf("vendor serialnumber: %08X%08X\n", edx, eax);
#endif

	return 0;
}

/////////////////////////////////////////////////////////////////////
namespace {

std::atomic<bool> ready_write1_(false), ready_write2_(false);
std::mutex mtx1_, mtx2_;
std::condition_variable cv_;
const char *start1_ = nullptr, *start2_ = nullptr;
size_t length1_ = 0, length2_ = 0;
FILE* file_ = nullptr;
bool exit_ = false;

void run()
{
	while (1) {
		if (ready_write1_) {
			std::unique_lock<std::mutex> lock(mtx1_);
			fwrite(start1_, 1, length1_, file_);
			ready_write1_ = false;
			cv_.notify_all();
		}

		if (ready_write2_) {
			std::unique_lock<std::mutex> lock(mtx1_);
			fwrite(start2_, 1, length2_, file_);
			ready_write2_ = false;
			cv_.notify_all();
		}

		if (exit_) break;
	}
}

void test_read()
{
	FILE* file = fopen("../../../testdata/test.data", "rb");
	if (!file) {
		fprintf(stderr, "fail to open file\n");
		return;
	}

	auto flag = fseek(file, 0, SEEK_END);
	if (flag != 0) {
		fprintf(stderr, "fail to fseek\n");
		return;
	}

	auto length = ftell(file);
	rewind(file);
	std::unique_ptr<char[]> data(new char[length]);
	fread(data.get(), 1, length, file);

	fclose(file);
}

void test_time()
{
	using namespace std::chrono;

	char arr[1024] = {0};
	std::unique_ptr<char[]> tmp(new char[1024 * 10]);

	steady_clock::time_point t1 = steady_clock::now();
	for (int i = 0; i < 10; ++i) {
		memcpy(tmp.get() + i * 1024, arr, 1024);
	}
	steady_clock::time_point t2 = steady_clock::now();
	duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);
	fprintf(stdout, "memcpy time: %fs\n", time_span1.count());

	FILE* f = fopen("../../../testdata/tmp.data", "wb");
	steady_clock::time_point t3 = steady_clock::now();
	for (int i = 0; i < 10; ++i) {
		fwrite(arr, 1, 1024, f);
	}
	steady_clock::time_point t4 = steady_clock::now();
	duration<double> time_span2 = duration_cast<duration<double>>(t4 - t3);
	fprintf(stdout, "fwrite time: %fs\n", time_span2.count());
	fclose(f);
}

} // namespace

int test_two_threads_write_file()
{
	//test_read();
	//return -1;

	test_time();
	return -1;

	file_ = fopen("../../../testdata/test.data", "wb");
	if (!file_) {
		fprintf(stderr, "fail to open file\n");
		return -1;
	}

	const size_t size = 16;// 1024 * 1024 * 128;
	std::unique_ptr<char[]> data(new char[size * 2]);
	const char *p1 = data.get(), *p2 = data.get() + size;
	start1_ = p1;
	start2_ = p2;

	const size_t length = 5;
	unsigned char arr[length] = { 1,2,3,4,5 };

	std::thread th(run);

	size_t index = 0;
	do { // another function(arr, length)
		static size_t add1 = 0, add2 = 0;
		static bool flag1 = true, flag2 = false;
		char* p = nullptr;

		if (flag1) {
			p = const_cast<char*>(p1) + add1;

			if (add1 + length <= size) {
				std::unique_lock<std::mutex> lock(mtx2_);
				while (ready_write1_) {
					cv_.wait(lock);
				}

				memcpy(p, arr, length);
				add1 += length;
			} else {
				flag1 = false;
				flag2 = true;
				length1_ = add1;
				add1 = 0;

				ready_write1_ = true;
			}
		}

		if (flag2) {
			p = const_cast<char*>(p2) + add2;

			if (add2 + length <= size) {
				std::unique_lock<std::mutex> lock(mtx2_);
				while (ready_write2_) {
					cv_.wait(lock);
				}

				memcpy(p, arr, length);
				add2 += length;
			} else {
				flag1 = true;
				flag2 = false;
				length2_ = add2;
				add2 = 0;

				ready_write2_ = true;

				if (add1 + length <= size) {
					p = const_cast<char*>(p1) + add1;

					std::unique_lock<std::mutex> lock(mtx2_);
					while (ready_write1_) {
						cv_.wait(lock);
					}

					memcpy(p, arr, length);
					add1 += length;
				} else {
					fprintf(stderr, "out of scope\n");
					return -1;
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::microseconds(1));
		++index;
		//fprintf(stdout, "index: %d\n", index);
	} while (index < 10000);

	exit_ = true;
	th.join();
	fclose(file_);
	return 0;
}
