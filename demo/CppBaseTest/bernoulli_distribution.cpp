#include "bernoulli_distribution.hpp"
#include <iostream>
#include <random>
#include <string>
#include <iomanip>
#include <map>

// Blog: http://blog.csdn.net/fengbingchun/article/details/73716003

/////////////////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/random/bernoulli_distribution/
int test_bernoulli_distribution_1()
{
{
	const int nrolls = 10000;

	std::default_random_engine generator;
	std::bernoulli_distribution distribution(0.5);

	int count = 0;  // count number of trues

	for (int i = 0; i<nrolls; ++i) if (distribution(generator)) ++count;

	std::cout << "bernoulli_distribution (0.5) x 10000:" << std::endl;
	std::cout << "true:  " << count << std::endl;
	std::cout << "false: " << nrolls - count << std::endl;
}

{ // (1)、bernoulli_distribution::bernoulli_distribution: Constructs a bernoulli_distribution object
//   with a probability of p (or with the probability specified by object parm)
//   (2)、bernoulli_distribution::operator(): Generate random number
//   Returns a new random value with the probability associated to the object (version 1) or
//   with the probability specified by parm (version 2)
//   (3)、bernoulli_distribution::p: Probability of true
//   Returns the parameter p associated with the bernoulli_distribution.
//   This parameter represents the probabily that member function operator() returns true.
//   (4)、bernoulli_distribution::max：Maximum value, Returns the least upper bound of the range of
//   values potentially returned by member operator(), which for bernoulli_distribution is true.
//   (5)、bernoulli_distribution::min: Minimum value, Returns the greatest lower bound of the range of
//   values potentially returned by member operator(), which for bernoulli_distribution is false.
	std::cout << "Please, enter a yes/no question (I will answer it):" << std::endl;
	std::string text;
	getline(std::cin, text);

	std::seed_seq seed(text.begin(), text.end());  // seed using question
	std::default_random_engine generator(seed);
	std::bernoulli_distribution distribution(0.91);

	bool result = distribution(generator);
	std::cout << (result ? "yes" : "no") << std::endl;
	std::cout << "p: " << distribution.p() << std::endl;
	std::cout << "max: " << distribution.max() << std::endl;
	std::cout << "min: " << distribution.min() << std::endl;
}

{ // bernoulli_distribution::param: Distribution parameters
//   A bernoulli_distribution is defined by a single parameter: its probability (p) of true results.
//   An object of type param_type carries this information, but it is meant to be used only to construct
//   or specify the parameters for a bernoulli_distribution object, not to inspect the individual parameter.
	std::default_random_engine generator;
	std::bernoulli_distribution d1(0.7);
	std::bernoulli_distribution d2(d1.param());

	// print two independent values:
	std::cout << std::boolalpha;
	std::cout << d1(generator) << std::endl;
	std::cout << d2(generator) << std::endl;
}

{ // bernoulli_distribution::reset: Resets the distribution,
//   so that subsequent uses of the object do not depend on values already produced by it.
	std::default_random_engine generator;
	std::bernoulli_distribution distribution;

	// print two independent values:
	std::cout << std::boolalpha;
	std::cout << distribution(generator) << std::endl;
	distribution.reset();
	std::cout << distribution(generator) << std::endl;
}

	return 0;
}

/////////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/numeric/random/bernoulli_distribution
int test_bernoulli_distribution_2()
{

	std::random_device rd;
	std::mt19937 gen(rd());
	// give "true" 1/4 of the time
	// give "false" 3/4 of the time
	std::bernoulli_distribution d(0.25);

	std::map<bool, int> hist;
	for (int n = 0; n<10000; ++n) {
		++hist[d(gen)];
	}
	for (auto p : hist) {
		std::cout << std::boolalpha << std::setw(5) << p.first
			<< ' ' << std::string(p.second / 500, '*') << '\n';
	}

	return 0;
}

/////////////////////////////////////////////////////////////
int test_bernoulli_distribution_3()
{
	std::random_device rd; std::mt19937 gen(rd()); // 每次产生不固定的不同的值
	//std::default_random_engine gen; // 每次产生固定的不同的值
	std::bernoulli_distribution d(0.5);

	for (int i = 0; i < 10; ++i)
		std::cout << d(gen);
	std::cout << std::endl;

	return 0;
}
