#include <iostream>
#include <string>
#include <stdexcept>
#ifdef _MSC_VER
#include <windows.h>
#else
#include <dlfcn.h>
#endif
#include "common.hpp"
#include "plugin.hpp"

// Blog: https://blog.csdn.net/fengbingchun/article/details/105104659

int main()
{
    // test general dynamic library
	fprintf(stdout, "csdn blog address: %s\n", get_csdn_blog_address());
	fprintf(stdout, "github address: %s\n", get_github_address());

    // test plugin
	const std::string plugin_name {"plugin_area"}, plugin_suffix {"fbc"};
	fbc_rect_t rect = {1, 2, 31, 52};

#ifdef _MSC_VER
    HINSTANCE handle = LoadLibrary((plugin_name+"."+plugin_suffix).c_str());
    if (!handle) {
        fprintf(stderr, "fail to load plugin: %s, %d\n", plugin_name.c_str(), GetLastError());
		return -1;
    }

	typedef Base* (*LPGETINSTANCE)(const char* name);
	LPGETINSTANCE lpGetInstance = (LPGETINSTANCE)GetProcAddress(handle, "get_plugin_instance");
	if (!lpGetInstance) {
		fprintf(stderr, "fail to GetProcAddress: get_plugin_instance, %d\n", GetLastError());
		return -1;
	}

	Base* instance = nullptr;
	try {
		instance = (*lpGetInstance)(plugin_name.c_str());
		fprintf(stdout, "plugin name: %s, version: %s\n", instance->name(), instance->version());
	} catch (const std::exception& e) {
		fprintf(stderr, "exception: %s\ntest fail\n", e.what());
		return -1;
	}

	fprintf(stdout, "area: %d\n", instance->get_area(rect));

	typedef std::string (*LPVERSIONNAME)(Base* base);
	LPVERSIONNAME lpVersionName = (LPVERSIONNAME)GetProcAddress(handle, "get_plugin_name_version");
	if (!lpVersionName) {
		fprintf(stderr, "fail to GetProcAddress: get_plugin_name_version, %d\n", GetLastError());
		return -1;
	}

	try {
		fprintf(stdout, "plugin name version: %s\n", (*lpVersionName)(instance).c_str());
	} catch (const std::exception& e) {
		fprintf(stderr, "exception: %s\ntest fail\n", e.what());
		return -1;
	}

	typedef void (*LPRELEASEINSTANCE)(Base* base);
	LPRELEASEINSTANCE lpReleaseInstance = (LPRELEASEINSTANCE)GetProcAddress(handle, "release_plugin_instance");
	if (!lpReleaseInstance) {
		fprintf(stderr, "fail to GetProcAddress: release_plugin_instance, %d\n", GetLastError());
		return -1;
	}
	fprintf(stdout, "destroy Base\n");
	(*lpReleaseInstance)(instance);

	FreeLibrary(handle);
#else
	void* handle = dlopen((plugin_name+"."+plugin_suffix).c_str(), RTLD_LAZY);
	if (!handle) {
		fprintf(stderr, "fail to load plugin: %s\n", plugin_name.c_str());
		return -1;
	}

	typedef Base* (*pGetInstance)(const char* name);
	pGetInstance pInstance = (pGetInstance)dlsym(handle, "get_plugin_instance");
	if (!pInstance) {
		fprintf(stderr, "fail to dlsym: get_plugin_instance\n");
		return -1;
	}

	Base* instance = nullptr;
	try {
		instance = (*pInstance)(plugin_name.c_str());
		fprintf(stdout, "plugin name: %s, version: %s\n", instance->name(), instance->version());
	} catch (const std::exception& e) {
		fprintf(stderr, "exception: %s\ntest fail\n", e.what());
		return -1;
	}

	fprintf(stdout, "area: %d\n", instance->get_area(rect));

	typedef std::string (*pVersionName)(Base* base);
	pVersionName pvername = (pVersionName)dlsym(handle, "get_plugin_name_version");
	if (!pvername) {
		fprintf(stderr, "fail to dlsym: get_plugin_name_version\n");
		return -1;
	}

	try {
		fprintf(stdout, "plugin name version: %s\n", (*pvername)(instance).c_str());
	} catch (const std::exception& e) {
		fprintf(stderr, "exception: %s\ntest fail\n", e.what());
		return -1;
	}

	typedef void (*pReleaseInstance)(Base* base);
	pReleaseInstance prelins = (pReleaseInstance)dlsym(handle, "release_plugin_instance");
	if (!prelins) {
		fprintf(stderr, "fail to dlsym: release_plugin_instance\n");
		return -1;
	}
	fprintf(stdout, "destroy Base\n");
	(*prelins)(instance);

	dlclose(handle);
#endif

	fprintf(stdout, "test finish\n");
	return 0;
}
