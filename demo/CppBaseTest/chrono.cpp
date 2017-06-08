#include "chrono.hpp"
#include <chrono>
#include <iostream>
#include <ratio>

///////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/chrono/duration/
int test_chrono_duration()
{
{ // duration::duration: Constructs a duration object
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

{ // 
}

{ // 
}

{ // 
}

{ // 
}

{ // 
}

{ // 
}

{ // 
}

{ // 
}

{ // 
}

	return 0;
}
