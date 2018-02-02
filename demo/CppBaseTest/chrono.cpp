#include "chrono.hpp"
#include <chrono>
#include <iostream>
#include <ratio>
#include <ctime>
#include <iomanip>

// Blog: http://blog.csdn.net/fengbingchun/article/details/73302364

///////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/chrono/duration/
int test_chrono_duration()
{
{ // duration::duration: Constructs a duration object
  // chrono::duration_cast: Converts the value of dtn into some other duration type,
  // taking into account differences in their periods
	typedef std::chrono::duration<int> seconds_type;
	typedef std::chrono::duration<int, std::milli> milliseconds_type;
	typedef std::chrono::duration<int, std::ratio<60 * 60>> hours_type;

	hours_type h_oneday(24);                  // 24h
	seconds_type s_oneday(60 * 60 * 24);          // 86400s
	milliseconds_type ms_oneday(s_oneday);    // 86400000ms

	seconds_type s_onehour(60 * 60);            // 3600s
	//hours_type h_onehour (s_onehour);          // NOT VALID (type truncates), use:
	hours_type h_onehour(std::chrono::duration_cast<hours_type>(s_onehour));
	milliseconds_type ms_onehour(s_onehour);  // 3600000ms (ok, no type truncation)

	std::cout << ms_onehour.count() << "ms in 1h" << std::endl;
}

{ // duration operators: +、-、*、/、>、<、!=、and so on
	std::chrono::duration<int> foo;
	std::chrono::duration<int> bar(10);

	// counts: foo bar
	//         --- ---
	foo = bar;                 // 10  10
	foo = foo + bar;           // 20  10
	++foo;                     // 21  10
	--bar;                     // 21   9
	foo *= 2;                  // 42   9
	foo /= 3;                  // 14   9
	//bar +=  (foo % bar);      // 14  14

	std::cout << std::boolalpha;
	std::cout << "foo==bar: " << (foo == bar) << std::endl;
	std::cout << "foo: " << foo.count() << std::endl;
	std::cout << "bar: " << bar.count() << std::endl;
}

{ // duration::count: Returns the internal count (i.e., the representation value) of the duration object.
	using namespace std::chrono;
	// std::chrono::milliseconds is an instatiation of std::chrono::duration:
	milliseconds foo(1000); // 1 second
	foo *= 60;

	std::cout << "duration (in periods): ";
	std::cout << foo.count() << " milliseconds.\n";

	std::cout << "duration (in seconds): ";
	std::cout << foo.count() * milliseconds::period::num / milliseconds::period::den;
	std::cout << " seconds.\n";
}

{ // duration::max: Returns the maximum value of duration
  // duration::min: Returns the minimum value of duration
	std::cout << "system_clock durations can represent:\n";
	std::cout << "min: " << std::chrono::system_clock::duration::min().count() << "\n";
	std::cout << "max: " << std::chrono::system_clock::duration::max().count() << "\n";
}

{ // duration::zero: Returns a duration value of zero
	using std::chrono::steady_clock;

	steady_clock::time_point t1 = steady_clock::now();

	std::cout << "Printing out something...\n";

	steady_clock::time_point t2 = steady_clock::now();

	steady_clock::duration d = t2 - t1;

	if (d == steady_clock::duration::zero())
		std::cout << "The internal clock did not tick.\n";
	else
		std::cout << "The internal clock advanced " << d.count() << " periods.\n";
}

{ // chrono::time_point_cast: Converts the value of tp into a time_point type with a different duration internal object,
  // taking into account differences in their durations's periods.
	using namespace std::chrono;

	typedef duration<int, std::ratio<60 * 60 * 24>> days_type;

	time_point<system_clock, days_type> today = time_point_cast<days_type>(system_clock::now());

	std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;
}

	return 0;
}

//////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/chrono/high_resolution_clock/
int test_chrono_high_resolution_clock() 
{
	// high_resolution_clock::now: Returns the current time_point in the frame of the high_resolution_clock
	using namespace std::chrono;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	std::cout << "printing out 1000 stars...\n";
	for (int i = 0; i<1000; ++i) std::cout << "*";
	std::cout << std::endl;

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "It took me " << time_span.count() << " seconds.";
	std::cout << std::endl;

	return 0;
}

///////////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/chrono/steady_clock/
int test_chrono_steady_clock()
{
	// steady_clock is specifically designed to calculate time intervals.
	// steady_clock::now: Returns the current time_point in the frame of the steady_clock.
	using namespace std::chrono;

	steady_clock::time_point t1 = steady_clock::now();

	std::cout << "printing out 1000 stars...\n";
	for (int i = 0; i<1000; ++i) std::cout << "*";
	std::cout << std::endl;

	steady_clock::time_point t2 = steady_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "It took me " << time_span.count() << " seconds.";
	std::cout << std::endl;

	return 0;
}

//////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/chrono/system_clock/
int test_chrono_system_clock()
{
	// system_clock is a system-wide realtime clock.

{ // system_clock::from_time_t: Converts t into its equivalent of member type time_point.
	using namespace std::chrono;

	// create tm with 1/1/2000:
	std::tm timeinfo = std::tm();
	timeinfo.tm_year = 100;   // year: 2000
	timeinfo.tm_mon = 0;      // month: january
	timeinfo.tm_mday = 1;     // day: 1st
	std::time_t tt = std::mktime(&timeinfo);

	system_clock::time_point tp = system_clock::from_time_t(tt);
	system_clock::duration d = system_clock::now() - tp;

	// convert to number of days:
	typedef duration<int, std::ratio<60 * 60 * 24>> days_type;
	days_type ndays = duration_cast<days_type> (d);

	// display result:
	std::cout << ndays.count() << " days have passed since 1/1/2000";
	std::cout << std::endl;
}

{ // system_clock::now: Returns the current time_point in the frame of the system_clock
	using namespace std::chrono;

	duration<int, std::ratio<60 * 60 * 24> > one_day(1);

	system_clock::time_point today = system_clock::now();
	system_clock::time_point tomorrow = today + one_day;

	time_t tt;

	tt = system_clock::to_time_t(today);
	std::cout << "today is: " << ctime(&tt);

	tt = system_clock::to_time_t(tomorrow);
	std::cout << "tomorrow will be: " << ctime(&tt);
}

{ // system_clock::to_time_t: Converts tp into its equivalent of type time_t.
	using namespace std::chrono;

	duration<int, std::ratio<60 * 60 * 24> > one_day(1);

	system_clock::time_point today = system_clock::now();
	system_clock::time_point tomorrow = today + one_day;

	time_t tt;

	tt = system_clock::to_time_t(today);
	std::cout << "today is: " << ctime(&tt);

	tt = system_clock::to_time_t(tomorrow);
	std::cout << "tomorrow will be: " << ctime(&tt);
}

	return 0;
}

//////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/chrono/time_point/
int test_chrono_time_point()
{
{ // time_point operators: +、-、==、!=
	using namespace std::chrono;

	system_clock::time_point tp, tp2;                // epoch value
	system_clock::duration dtn(duration<int>(1));  // 1 second

	//  tp     tp2    dtn
	//  ---    ---    ---
	tp += dtn;          //  e+1s   e      1s
	tp2 -= dtn;         //  e+1s   e-1s   1s
	tp2 = tp + dtn;     //  e+1s   e+2s   1s
	tp = dtn + tp2;     //  e+3s   e+2s   1s
	tp2 = tp2 - dtn;    //  e+3s   e+1s   1s
	dtn = tp - tp2;     //  e+3s   e+1s   2s

	std::cout << std::boolalpha;
	std::cout << "tp == tp2: " << (tp == tp2) << std::endl;
	std::cout << "tp > tp2: " << (tp>tp2) << std::endl;
	std::cout << "dtn: " << dtn.count() << std::endl;
}

{ // time_point::time_point: Constructs a time_point object
	using namespace std::chrono;

	system_clock::time_point tp_epoch;	// epoch value

	time_point <system_clock, duration<int>> tp_seconds(duration<int>(1));

	system_clock::time_point tp(tp_seconds);

	std::cout << "1 second since system_clock epoch = ";
	std::cout << tp.time_since_epoch().count();
	std::cout << " system_clock periods." << std::endl;

	// display time_point:
	std::time_t tt = system_clock::to_time_t(tp);
	std::cout << "time_point tp is: " << ctime(&tt);
}

{ // time_point::time_since_epoch: Returns a duration object with the time span value between the epoch and the time point
	using namespace std::chrono;

	system_clock::time_point tp = system_clock::now();
	system_clock::duration dtn = tp.time_since_epoch();

	std::cout << "current time since epoch, expressed in:" << std::endl;
	std::cout << "periods: " << dtn.count() << std::endl;
	std::cout << "seconds: " << dtn.count() * system_clock::period::num / system_clock::period::den;
	std::cout << std::endl;
}

	return 0;
}

///////////////////////////////////////////////////////////////////
// reference: https://zh.wikibooks.org/wiki/C%2B%2B/STL/Chrono
static long fibonacci(unsigned n)
{
	if (n < 2) return n;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

int test_chrono_1()
{
{ // std::chrono::time_point
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
	std::cout << "24 hours ago, the time was " << now_c << '\n';

	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	std::cout << "Hello World\n";
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Printing took "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
}

{ // std::chrono::duration
	using shakes = std::chrono::duration<int, std::ratio<1, 100000000>>;
	using jiffies = std::chrono::duration<int, std::centi>;
	using microfortnights = std::chrono::duration<float, std::ratio<12096, 10000>>;
	using nanocenturies = std::chrono::duration<float, std::ratio<3155, 1000>>;

	std::chrono::seconds sec(1);

	std::cout << "1 second is:\n";

	std::cout << std::chrono::duration_cast<shakes>(sec).count() << " shakes\n";
	std::cout << std::chrono::duration_cast<jiffies>(sec).count() << " jiffies\n";
	std::cout << microfortnights(sec).count() << " microfortnights\n";
	std::cout << nanocenturies(sec).count() << " nanocenturies\n";
}

{ // 
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	std::cout << "f(42) = " << fibonacci(42) << '\n';
	end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "finished computation at " << std::ctime(&end_time)
		<< "elapsed time: " << elapsed_seconds.count() << "s\n";
}
	return 0;
}
