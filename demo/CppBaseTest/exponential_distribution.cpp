#include "exponential_distribution.hpp"
#include <iostream>
#include <random>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>
#include <map>

// Blog: http://blog.csdn.net/fengbingchun/article/details/73826114

///////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/random/exponential_distribution/
int test_exponential_distribution_1()
{
{
	const int nrolls = 10000;  // number of experiments
	const int nstars = 100;    // maximum number of stars to distribute
	const int nintervals = 10; // number of intervals

	std::default_random_engine generator;
	std::exponential_distribution<double> distribution(3.5);

	int p[nintervals] = {};

	for (int i = 0; i<nrolls; ++i) {
		double number = distribution(generator);
		if (number<1.0) ++p[int(nintervals*number)];
	}

	std::cout << "exponential_distribution (3.5):" << std::endl;
	std::cout << std::fixed; std::cout.precision(1);

	for (int i = 0; i<nintervals; ++i) {
		std::cout << float(i) / nintervals << "-" << float(i + 1) / nintervals << ": ";
		std::cout << std::string(p[i] * nstars / nrolls, '*') << std::endl;
	}
}

{ // (1)、exponential_distribution::exponential_distribution: Construct exponential distribution,
//   Constructs an exponential_distribution object, adopting the distribution parameters specified either by lambda or by object parm.
//   (2)、exponential_distribution::lambda: Returns the parameter lambda (λ) associated with the exponential_distribution.
//   This parameter represents the number of times the random events are observed by interval, on average.
//   This parameter is set on construction.
//   (3)、exponential_distribution::max: Maximum value
//   Returns the least upper bound of the range of values potentially returned by member operator().
//   (4)、exponential_distribution::min: Minimum value
//   Returns the greatest lower bound of the range of values potentially returned by member operator(),
//   which for exponential_distribution is always zero.
//   (5)、exponential_distribution::operator(): Generate random number
//   Returns a new random number that follows the distribution's parameters associated to the object (version 1)
//   or those specified by parm (version 2).

	// construct a trivial random generator engine from a time-based seed:
	int seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::exponential_distribution<double> distribution(1.0);

	std::cout << "ten beeps, spread by 1 second, on average: " << std::endl;
	for (int i = 0; i<10; ++i) {
		double number = distribution(generator);
		std::chrono::duration<double> period(number);
		std::this_thread::sleep_for(std::chrono::seconds(1)/*period*/);
		std::cout << "beep!" << std::endl;
	}

	std::cout << "lambda: " << distribution.lambda() << std::endl;
	std::cout << "max: " << distribution.max() << std::endl;
	std::cout << "min: " << distribution.min() << std::endl;
}

{ // exponential_distribution::param: Distribution parameters
//   The first version(1) returns an object with the parameters currently associated with the distribution object.
//   The second version(2) associates the parameters in object parm to the distribution object.
	std::default_random_engine generator;
	std::exponential_distribution<double> d1(0.8);
	std::exponential_distribution<double> d2(d1.param());

	// print two independent values:
	std::cout << d1(generator) << std::endl;
	std::cout << d2(generator) << std::endl;
}

{ // exponential_distribution::reset: Resets the distribution, so that subsequent uses of the object do not depend on values already produced by it.
//   This function may have no effect if the library implementation for this distribution class produces independent values.
	std::default_random_engine generator;
	std::exponential_distribution<double> distribution(1.0);

	// print two independent values:
	std::cout << distribution(generator) << std::endl;
	distribution.reset();
	std::cout << distribution(generator) << std::endl;
}

	return 0;
}

////////////////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/numeric/random/exponential_distribution
int test_exponential_distribution_2()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// if particles decay once per second on average,
	// how much time, in seconds, until the next one?
	std::exponential_distribution<> d(1);

	std::map<int, int> hist;
	for (int n = 0; n<10000; ++n) {
		++hist[2 * d(gen)];
	}
	for (auto p : hist) {
		std::cout << std::fixed << std::setprecision(1)
			<< p.first / 2.0 << '-' << (p.first + 1) / 2.0 <<
			' ' << std::string(p.second / 200, '*') << '\n';
	}

	return 0;
}

////////////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/bb982914.aspx
static void test(const double l, const int s)
{
	// uncomment to use a non-deterministic generator
	//    std::random_device gen;
	std::mt19937 gen(1701);

	std::exponential_distribution<> distr(l);

	std::cout << std::endl;
	std::cout << "min() == " << distr.min() << std::endl;
	std::cout << "max() == " << distr.max() << std::endl;
	std::cout << "lambda() == " << std::fixed << std::setw(11) << std::setprecision(10) << distr.lambda() << std::endl;

	// generate the distribution as a histogram  
	std::map<double, int> histogram;
	for (int i = 0; i < s; ++i) {
		++histogram[distr(gen)];
	}

	// print results  
	std::cout << "Distribution for " << s << " samples:" << std::endl;
	int counter = 0;
	for (const auto& elem : histogram) {
		std::cout << std::fixed << std::setw(11) << ++counter << ": "
			<< std::setw(14) << std::setprecision(10) << elem.first << std::endl;
	}
	std::cout << std::endl;
}
int test_exponential_distribution_3()
{
	double l_dist = 0.5;
	int samples = 10;

	std::cout << "Use CTRL-Z to bypass data entry and run using default values." << std::endl;
	std::cout << "Enter a floating point value for the 'lambda' distribution parameter (must be greater than zero): ";
	//std::cin >> l_dist;
	std::cout << "Enter an integer value for the sample count: ";
	//std::cin >> samples;

	test(l_dist, samples);

	return 0;
}
