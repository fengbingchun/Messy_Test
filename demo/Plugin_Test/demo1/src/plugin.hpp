#ifndef FBC_PLUGIN_TEST_PLUGIN_HPP_
#define FBC_PLUGIN_TEST_PLUGIN_HPP_

#include "common.hpp"

class Base {
public:
	virtual const char* version() = 0;
	virtual const char* name() = 0;
	virtual int get_area(const fbc_rect_t& rect) = 0;

	virtual ~Base() = default;
};

#ifdef __cplusplus
extern "C" {
#endif

FBC_API Base* get_plugin_instance(const char* name);
FBC_API std::string get_plugin_name_version(Base* handle);
FBC_API void release_plugin_instance(Base* handle);

#ifdef __cplusplus
}
#endif 

#endif // FBC_PLUGIN_TEST_PLUGIN_HPP_