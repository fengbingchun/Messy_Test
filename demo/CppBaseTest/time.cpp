#include "time.hpp"
#include <time.h>
#include <string.h>
#include <string>

namespace time_ {

// Blog: https://blog.csdn.net/fengbingchun/article/details/112062634
void test_time()
{
	time_t rawtime = time(nullptr); //time_t rawtime; time(&rawtime);

	struct tm* timeinfo = localtime(&rawtime);
	fprintf(stdout, "The current local date/time is: %s", asctime(timeinfo));

	timeinfo = gmtime(&rawtime);
	fprintf(stdout, "The current utc date/time is: %s", asctime(timeinfo));

	fprintf(stdout, "The current local date/time is: %s", ctime(&rawtime));

	timeinfo = localtime(&rawtime);
	timeinfo->tm_hour = timeinfo->tm_min = timeinfo->tm_sec = timeinfo->tm_mon = 0; timeinfo->tm_mday = 1;
	fprintf(stdout, "%.f seconds since new year in the current timezone\n", difftime(rawtime, mktime(timeinfo)));

	timeinfo = localtime(&rawtime);
	char buffer[64];
	strftime(buffer, 64, "Now it's %I:%M%p", timeinfo);
	fprintf(stdout, "buffer: %s\n", buffer);
}

void test_date_to_timestamp_local()
{
	// timestamp --> date
	time_t timestamp = time(nullptr);
	struct tm* timeinfo = localtime(&timestamp);
	int year = timeinfo->tm_year + 1900; // years since 1900
	int month = timeinfo->tm_mon + 1; // monthes since January - [0, 11]
	int day = timeinfo->tm_mday;
	int date = year * 10000 + month * 100 + day;
	int hour = timeinfo->tm_hour;
	int minute = timeinfo->tm_min;
	int second = timeinfo->tm_sec;
	fprintf(stdout, "timestamp: %ld, date: %d %.2d:%.2d:%.2d\n", timestamp, date, hour, minute, second);

	// date --> timestamp
	int date2 = 20211122;
	struct tm timeinfo2;
	memset(&timeinfo2, 0, sizeof(struct tm));
	timeinfo2.tm_year = date2 / 10000 - 1900;
	timeinfo2.tm_mon = date2 % 10000 / 100 - 1;
	timeinfo2.tm_mday = date2 % 100;
	time_t timestamp2 = mktime(&timeinfo2);
	fprintf(stdout, "date2: %d, timestamp2: %ld\n", date2, timestamp2);
}

#ifdef _MSC_VER
#define timegm _mkgmtime
#endif

void test_date_to_timestamp_utc()
{
	// timestamp --> date
	time_t timestamp = 86470; // 1day = 24 * 60 * 60 = 86400
	struct tm* timeinfo = gmtime(&timestamp);
	int year = timeinfo->tm_year + 1900; // years since 1900
	int month = timeinfo->tm_mon + 1; // monthes since January - [0, 11]
	int day = timeinfo->tm_mday;
	int date = year * 10000 + month * 100 + day;
	int hour = timeinfo->tm_hour;
	int minute = timeinfo->tm_min;
	int second = timeinfo->tm_sec;
	fprintf(stdout, "timestamp: %ld, date: %d %.2d:%.2d:%.2d\n", timestamp, date, hour, minute, second);

	// date --> timestamp
	int date2 = 19700102;
	struct tm timeinfo2;
	memset(&timeinfo2, 0, sizeof(struct tm));
	timeinfo2.tm_year = date2 / 10000 - 1900;
	timeinfo2.tm_mon = date2 % 10000 / 100 - 1;
	timeinfo2.tm_mday = date2 % 100;
	time_t timestamp2 = timegm(&timeinfo2);
	fprintf(stdout, "date2: %d, timestamp2: %ld\n", date2, timestamp2);
}

int test_date_timestamp()
{
	//test_time();
	//test_date_to_timestamp_local();
	test_date_to_timestamp_utc();

	return 0;
}


///////////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/107023645
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
