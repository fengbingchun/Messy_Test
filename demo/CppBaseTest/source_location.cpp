#include "source_location.hpp"
#include <iostream>
#include <source_location>

// Blog: https://blog.csdn.net/fengbingchun/article/details/143082167

namespace {

void log(const std::source_location location = std::source_location::current())
{
    std::clog << "file: "
        << location.file_name() << "("
        << location.line() << ":"
        << location.column() << "); function name: "
        << location.function_name()
        << std::endl;
}

void func()
{
    log();
}

} // namespace

int test_source_location()
{
    log();
    func();

	return 0;
}
