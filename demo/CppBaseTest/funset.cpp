#include "funset.hpp"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <string>
#include <cstdint>
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
