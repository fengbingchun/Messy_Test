#include "normal_distribution.hpp"
#include <iostream>
#include <random>
#include <string>
#include <chrono>
#include <map>
#include <iomanip>

// Blog: http://blog.csdn.net/fengbingchun/article/details/73770856

///////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/random/normal_distribution/
int test_normal_distribution_1()
{
{
	const int nrolls = 10000;  // number of experiments
	const int nstars = 100;    // maximum number of stars to distribute

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(5.0, 2.0);

	int p[10] = {};

	for (int i = 0; i<nrolls; ++i) {
		double number = distribution(generator);
		if ((number >= 0.0) && (number<10.0)) ++p[int(number)];
	}

	std::cout << "normal_distribution (5.0,2.0):" << std::endl;

	for (int i = 0; i<10; ++i) {
		std::cout << i << "-" << (i + 1) << ": ";
		std::cout << std::string(p[i] * nstars / nrolls, '*') << std::endl;
	}
}

{ // (1)、normal_distribution::normal_distribution: Constructs a normal_distribution object,
//   adopting the distribution parameters specified either by mean and stddev or by object parm.
//   (2)、normal_distribution::max: Returns the least upper bound of the range of values potentially returned by member operator().
//   (3)、normal_distribution::min: Returns the greatest lower bound of the range of values potentially returned by member operator().
//   (4)、normal_distribution::mean: Returns the mean(μ)parameter associated with the normal_distribution object
//   (5)、normal_distribution::stddev: Returns the standard deviation (σ) associated with the normal_distribution object
//   (6)、normal_distribution::operator(): Returns a new random number that follows the distribution's parameters associated
//    to the object (version 1) or those specified by parm (version 2).

	// construct a trivial random generator engine from a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::normal_distribution<double> distribution(0.0, 1.0);

	std::cout << "some Normal-distributed(0.0,1.0) results:" << std::endl;
	for (int i = 0; i<10; ++i)
		std::cout << distribution(generator) << std::endl;
	std::cout << "max: " << distribution.max() << std::endl;
	std::cout << "min: " << distribution.min() << std::endl;
	std::cout << "mean: " << distribution.mean() << std::endl;
	std::cout << "stddev: " << distribution.stddev() << std::endl;
}

{ // normal_distribution::param: Distribution parameters
	std::default_random_engine generator;
	std::normal_distribution<double> d1(0.0, 1.0);
	std::normal_distribution<double> d2(d1.param());

	// print two independent values:
	std::cout << d1(generator) << std::endl;
	std::cout << d2(generator) << std::endl;
}

{ // normal_distribution::reset: Resets the distribution,
//   so that subsequent uses of the object do not depend on values already produced by it.
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0.0, 1.0);

	// print two independent values:
	std::cout << distribution(generator) << std::endl;
	distribution.reset();
	std::cout << distribution(generator) << std::endl;
}

	return 0;
}

///////////////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/numeric/random/normal_distribution
int test_normal_distribution_2()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// values near the mean are the most likely
	// standard deviation affects the dispersion of generated values from the mean
	std::normal_distribution<> d(5, 2);

	std::map<int, int> hist;
	for (int n = 0; n<10000; ++n) {
		++hist[std::round(d(gen))];
	}
	for (auto p : hist) {
		std::cout << std::fixed << std::setprecision(1) << std::setw(2)
			<< p.first << ' ' << std::string(p.second / 200, '*') << '\n';
	}

	return 0;
}

////////////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/bb982827.aspx
static void test(const double m, const double s, const int samples)
{
	using namespace std;
	// uncomment to use a non-deterministic seed  
	//    random_device gen;  
	//    mt19937 gen(rd());  
	mt19937 gen(1701);

	normal_distribution<> distr(m, s);

	cout << endl;
	cout << "min() == " << distr.min() << endl;
	cout << "max() == " << distr.max() << endl;
	cout << "m() == " << fixed << setw(11) << setprecision(10) << distr.mean() << endl;
	cout << "s() == " << fixed << setw(11) << setprecision(10) << distr.stddev() << endl;

	// generate the distribution as a histogram  
	map<double, int> histogram;
	for (int i = 0; i < samples; ++i) {
		++histogram[distr(gen)];
	}

	// print results  
	cout << "Distribution for " << samples << " samples:" << endl;
	int counter = 0;
	for (const auto& elem : histogram) {
		cout << fixed << setw(11) << ++counter << ": "
			<< setw(14) << setprecision(10) << elem.first << endl;
	}
	cout << endl;
}

int test_normal_distribution_3()
{
	using namespace std;

	double m_dist = 0;// 1;
	double s_dist = 1;
	int samples = 10;

	cout << "Use CTRL-Z to bypass data entry and run using default values." << endl;
	cout << "Enter a floating point value for the 'mean' distribution parameter: ";
	//cin >> m_dist;
	cout << "Enter a floating point value for the 'stddev' distribution parameter (must be greater than zero): ";
	//cin >> s_dist;
	cout << "Enter an integer value for the sample count: ";
	//cin >> samples;

	test(m_dist, s_dist, samples);

	return 0;
}
