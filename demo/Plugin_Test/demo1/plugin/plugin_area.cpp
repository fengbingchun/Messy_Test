#include <string.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include "plugin.hpp"

class Area : public Base {
public:
	Area() = default;
	~Area() = default;

	const char* version() override { return "1.0.0"; }
	const char* name() override { return "plugin_area"; }
	int get_area(const fbc_rect_t& rect) override { return ((rect.right - rect.left) * (rect.bottom - rect.top) + 10); }
};

#ifdef __cplusplus
extern "C" {
#endif

FBC_API Base* get_plugin_instance(const char* name)
{
	Area* area = new Area();
	if (strcmp(area->name(), name) != 0) {
		fprintf(stderr, "plugin name mismatch: %s, %s\n", area->name(), name);
		delete area;
		throw std::runtime_error("plugin name mismatch");
		return nullptr;
	}

	return area;
}

FBC_API std::string get_plugin_name_version(Base* handle)
{
	if (!handle) {
		fprintf(stdout, "handle cann't equal nullptr\n");
		throw std::runtime_error("handle cann't equal nullptr");
		return "";
	}

	Area* area = dynamic_cast<Area*>(handle);
	std::string str(area->name());
	str += ".fbc.";
	str += area->version();
	return str;
}

FBC_API void release_plugin_instance(Base* handle)
{
	delete dynamic_cast<Area*>(handle);
}

#ifdef __cplusplus
}
#endif 