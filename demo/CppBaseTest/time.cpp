#include "time.hpp"
#include <ctime>
#include <string>

// Blog: https://blog.csdn.net/fengbingchun/article/details/107023645
namespace time_ {
void print_time(const std::string& type, const struct tm* timeinfo)
{
	int year = timeinfo->tm_year + 1900; // years since 1900
	int month = timeinfo->tm_mon + 1; // monthes since January - [0, 11]
	int day = timeinfo->tm_mday;
	int date = year * 10000 + month * 100 + day;

	int hour = timeinfo->tm_hour;
	int minute = timeinfo->tm_min;
	int second = timeinfo->tm_sec;

	fprintf(stdout, "type: %s\t, date: %d, time: %.2d:%.2d:%.2d\n", type.c_str(), date, hour, minute, second);
}

int test_gmtime_localtime()
{
{ // gmtime
	time_t rawtime;
	time(&rawtime);

	struct tm* timeinfo = gmtime(&rawtime);
	print_time("UTC", timeinfo);
}

{ // localtime
	time_t rawtime;
	time(&rawtime);

	struct tm* timeinfo = localtime(&rawtime);
	print_time("localtime", timeinfo);
}

	return 0;
}

} // namespace time_
