#include "cmath.hpp"
#include <cmath>
#include <iostream>
#include <fenv.h> // fegetround, FE_*
#include <float.h> // FLT_RADIX

// Blog: http://blog.csdn.net/fengbingchun/article/details/78171987

// reference: http://www.cplusplus.com/reference/cmath/

#define PI 3.14159265

namespace cmath_ {

int test_cmath_abs()
{
{ // std::abs: double/float/long double/T
	std::cout << "abs (3.141611111) = " << std::abs(3.141611111) << '\n'; // 3.14161
	std::cout << "abs (-10.6)  = " << std::abs(-10.6f) << '\n'; // 10.6
	std::cout << "abs ((int)-10)  = " << std::abs((int)-10) << '\n'; // 10
}

{ // std::fabs: double/float/long double/T
	std::cout << "fabs (3.141611111) = " << std::fabs(3.141611111) << '\n'; // 3.14161
	std::cout << "fabs (-10.6)  = " << std::fabs(-10.6f) << '\n'; // 10.6
}

{ // std::fma: Returns x*y+z
	double x, y, z, result;
	x = 10.0, y = 20.0, z = 30.0;

	result = std::fma(x, y, z);

	printf("10.0 * 20.0 + 30.0 = %f\n", result); // 230.0
}

	return 0;
}

int test_cmath_triangle()
{
{ // std::sin: double/float/long double/T
	double param, result;
	param = 30.0;
	result = std::sin(param*PI / 180);
	fprintf(stdout, "The sine of %f degrees is %f.\n", param, result); // 0.5
}

{ // std::asin: double/float/long double/T
	double param, result;
	param = 0.5;
	result = std::asin(param) * 180.0 / PI;
	fprintf(stdout, "The arc sine of %f is %f degrees\n", param, result); // 30.0
}

{ // std::sinh: double/float/long double/T
	double param, result;
	param = log(2.0);
	result = std::sinh(param);
	printf("The hyperbolic sine of %f is %f.\n", param, result); // 0.75
}

{ // std::asinh double/float/long double/T
	double param, result;
	param = std::exp(2) - std::cosh(2);
	result = std::asinh(param);
	fprintf(stdout, "The area hyperbolic sine of %f is %f.\n", param, result); // 2.0
}

{ // std::cos double/float/long double/T
	double param, result;
	param = 60.0;
	result = std::cos(param * PI / 180.0);
	fprintf(stdout, "The cosine of %f degrees is %f.\n", param, result); // 0.5
}

{// std::acos: double/float/long double/T
	double param, result;
	param = 0.5;
	result = std::acos(param) * 180.0 / PI;
	fprintf(stdout, "The arc cosine of %f is %f degrees.\n", param, result); // 60.0
}

{ // std::cosh double/float/long double/T
	double param, result;
	param = std::log(2.0);
	result = std::cosh(param);
	fprintf(stdout, "The hyperbolic cosine of %f is %f.\n", param, result); // 1.25
}

{ // std::acosh: double/float/long double/T
	double param, result;
	param = std::exp(2) - std::sinh(2);
	result = std::acosh(param);
	fprintf(stdout, "The area hyperbolic cosine of %f is %f radians.\n", param, result); // 2.0
}

{ // std::tan: double/float/long double/T
	double param, result;
	param = 45.0;
	result = std::tan(param * PI / 180.0);
	fprintf(stdout, "The tangent of %f degrees is %f.\n", param, result); // 1.0
}

{ // std::atan: double/float/long double/T
	double param, result;
	param = 1.0;
	result = std::atan(param) * 180 / PI;
	fprintf(stdout, "The arc tangent of %f is %f degrees\n", param, result); // 45.0
}

{ // std::atan2: double/float/long double/T
	double x, y, result;
	x = -10.0;
	y = 10.0;
	result = std::atan2(y, x) * 180 / PI;
	fprintf(stdout, "The arc tangent for (x=%f, y=%f) is %f degrees\n", x, y, result); // 135.0
}

{ // std::tanh: double/float/long double/T
	double param, result;
	param = std::log(2.0);
	result = std::tanh(param);
	fprintf(stdout, "The hyperbolic tangent of %f is %f.\n", param, result); // 0.6
}

{ // std::atanh: double/float/long double/T
	double param, result;
	param = std::tanh(1);
	result = std::atanh(param);
	fprintf(stdout, "The area hyperbolic tangent of %f is %f.\n", param, result); // 1
}

	return 0;
}

int test_cmath_pow()
{
{ // std::sqrt(x): Returns the square root of x
	double param, result;
	param = 1024.0;
	result = std::sqrt(param);
	printf("sqrt(%f) = %f\n", param, result); // 32.0
}

{ // std::cbrt: Compute cubic root
	double param, result;
	param = 27.0;
	result = std::cbrt(param);
	fprintf(stdout, "cbrt (%f) = %f\n", param, result); // 3.0
}

{ // std::hypot(x, y): sqrt(x^2+y^2)
	double leg_x, leg_y, result;
	leg_x = 3;
	leg_y = 4;
	result = std::hypot(leg_x, leg_y);
	fprintf(stdout, "%f, %f and %f form a right-angled triangle.\n", leg_x, leg_y, result); // 5.0
}

{ // std::pow(x, y): x^y
	fprintf(stdout, "7 ^ 3 = %f\n", std::pow(7.0, 3.0)); // 343.0
	fprintf(stdout, "4.73 ^ 12 = %f\n", std::pow(4.73, 12.0)); // 125410439.217423
	fprintf(stdout, "32.01 ^ 1.54 = %f\n", std::pow(32.01, 1.54)); // 208.036691
	fprintf(stdout, "4 ^ 3 = %f\n", std::pow((int)4, (int)3)); // 64.0
}

	return 0;
}

int test_cmath_integer()
{
{ // std::ceil(x): returning the smallest integral value that is not less than x
	fprintf(stdout, "ceil of 2.3 is %.1f\n", std::ceil(2.3)); // 3.0
	fprintf(stdout, "ceil of 3.8 is %.1f\n", std::ceil(3.8)); // 4.0
	fprintf(stdout, "ceil of -2.3 is %.1f\n", std::ceil(-2.3)); // -2.0
	fprintf(stdout, "ceil of -3.8 is %.1f\n", std::ceil(-3.8)); // -3.0
}

{ // std::floor returning the largest integral value that is not greater than x
	fprintf(stdout, "floor of 2.3 is %.1lf\n", std::floor(2.3)); // 2.0
	fprintf(stdout, "floor of 3.8 is %.1lf\n", std::floor(3.8)); // 3.0
	fprintf(stdout, "floor of -2.3 is %.1lf\n", std::floor(-2.3)); // -2.0
	fprintf(stdout, "floor of -3.8 is %.1lf\n", std::floor(-3.8)); // -3.0
}

{ // std::fmod: Returns the floating-point remainder of numer/denom(rounded towards zero)
	printf("fmod of 5.3 / 2 is %f\n", std::fmod(5.3, 2)); // fmod of 5.3 / 2 is 1.3
	printf("fmod of 18.5 / 4.2 is %f\n", std::fmod(18.5, 4.2)); // fmod of 18.5 / 4.2 is 1.7
}

{ // std::trunc(x): Rounds x toward zero, returning the nearest integral value that is not larger in magnitude than x.
  // std::round(x): Returns the integral value that is nearest to x
	const char * format = "%.1f \t%.1f \t%.1f \t%.1f \t%.1f\n";
	printf("value\tround\tfloor\tceil\ttrunc\n");
	printf("-----\t-----\t-----\t----\t-----\n");				 // round  floor  ceil  trunc
	printf(format, 2.3, std::round(2.3), std::floor(2.3), std::ceil(2.3), std::trunc(2.3));	 // 2.0     2.0    3.0   2.0
	printf(format, 3.8, std::round(3.8), std::floor(3.8), std::ceil(3.8), std::trunc(3.8));	 // 4.0     3.0    4.0   3.0
	printf(format, 5.5, std::round(5.5), std::floor(5.5), std::ceil(5.5), std::trunc(5.5));	 // 6.0     5.0    6.0   5.0
	printf(format, -2.3, std::round(-2.3), std::floor(-2.3), std::ceil(-2.3), std::trunc(-2.3)); // -2.0    -3.0   -2.0  -2.0
	printf(format, -3.8, std::round(-3.8), std::floor(-3.8), std::ceil(-3.8), std::trunc(-3.8)); // -4.0    -4.0   -3.0  -3.0
	printf(format, -5.5, std::round(-5.5), std::floor(-5.5), std::ceil(-5.5), std::trunc(-5.5)); // -6.0    -6.0   -5.0  -5.0
}

{ // std::lround: Returns the integer value that is nearest in value to x
	printf("lround (2.3) = %ld\n", std::lround(2.3)); // 2
	printf("lround (3.8) = %ld\n", std::lround(3.8)); // 4
	printf("lround (-2.3) = %ld\n", std::lround(-2.3)); // -2
	printf("lround (-3.8) = %ld\n", std::lround(-3.8)); // -4
}

{ // std::llround(x): Returns the integer value that is nearest in value to x
	printf("llround (2.3) = %lld\n", std::llround(2.3)); // 2
	printf("llround (3.8) = %lld\n", std::llround(3.8)); // 4
	printf("llround (-2.3) = %lld\n", std::llround(-2.3)); // -2
	printf("llround (-3.8) = %lld\n", std::llround(-3.8)); // -4
}

{ // std::nearbyint: Round to nearby integral value
	printf("rounding using ");
	switch (fegetround()) {
	case FE_DOWNWARD: printf("downward"); break;
	case FE_TONEAREST: printf("to-nearest"); break; // to-nearest
	case FE_TOWARDZERO: printf("toward-zero"); break;
	case FE_UPWARD: printf("upward"); break;
	default: printf("unknown");
	}
	printf(" rounding:\n");

	printf("nearbyint (2.3) = %.1f\n", std::nearbyint(2.3)); // 2.0
	printf("nearbyint (3.8) = %.1f\n", std::nearbyint(3.8)); // 4.0
	printf("nearbyint (-2.3) = %.1f\n", std::nearbyint(-2.3)); // -2.0
	printf("nearbyint (-3.8) = %.1f\n", std::nearbyint(-3.8)); // -4.0
}

{ // std::remainder: Returns the floating-point remainder of numer/denom(rounded to nearest)
	printf("remainder of 5.3 / 2 is %f\n", std::remainder(5.3, 2)); // remainder of 5.3 / 2 is -0.7
	printf("remainder of 18.5 / 4.2 is %f\n", std::remainder(18.5, 4.2)); // remainder of 18.5 / 4.2 is 1.7
}

{ // std::remquo: Returns the same as remainder, but it additionally stores the quotient
  // internally used to determine its result in the object pointed by quot
	double numer = 10.3;
	double denom = 4.5;
	int quot;
	double result = std::remquo(numer, denom, &quot);
	printf("numerator: %f\n", numer); // 10.3
	printf("denominator: %f\n", denom); // 4.5
	printf("remainder: %f\n", result); // 1.3
	printf("quotient: %d\n", quot); // 2
}

{ // std::rint: Round to integral value
	printf("rounding using ");
	switch (fegetround()) {
		case FE_DOWNWARD: printf("downward"); break;
		case FE_TONEAREST: printf("to-nearest"); break; // to-nearest
		case FE_TOWARDZERO: printf("toward-zero"); break;
		case FE_UPWARD: printf("upward"); break;
		default: printf("unknown");
	}
	printf(" rounding:\n");

	printf("rint (2.3) = %.1f\n", std::rint(2.3)); // 2.0
	printf("rint (3.8) = %.1f\n", std::rint(3.8)); // 4.0
	printf("rint (-2.3) = %.1f\n", std::rint(-2.3)); // -2.0
	printf("rint (-3.8) = %.1f\n", std::rint(-3.8)); // -4.0
}

{ // std::lrint: Rounds x to an integral value, and returns it as a value of type long int.
	printf("rounding using ");
	switch (fegetround()) {
		case FE_DOWNWARD: printf("downward"); break;
		case FE_TONEAREST: printf("to-nearest"); break; // to-nearest
		case FE_TOWARDZERO: printf("toward-zero"); break;
		case FE_UPWARD: printf("upward"); break;
		default: printf("unknown");
	}
	printf(" rounding:\n");

	printf("lrint (2.3) = %ld\n", std::lrint(2.3)); // 2
	printf("lrint (3.8) = %ld\n", std::lrint(3.8)); // 4
	printf("lrint (-2.3) = %ld\n", std::lrint(-2.3)); // -2
	printf("lrint (-3.8) = %ld\n", std::lrint(-3.8)); // -4
}

{ // std::llrint: Rounds x to an integral value,returns it as a value of type long long int
	printf("rounding using ");
	switch (fegetround()) {
		case FE_DOWNWARD: printf("downward"); break;
		case FE_TONEAREST: printf("to-nearest"); break; // to-nearest
		case FE_TOWARDZERO: printf("toward-zero"); break;
		case FE_UPWARD: printf("upward"); break;
		default: printf("unknown");
	}
	printf(" rounding:\n");

	printf("llrint (2.3) = %lld\n", std::llrint(2.3)); // 2
	printf("llrint (3.8) = %lld\n", std::llrint(3.8)); // 4
	printf("llrint (-2.3) = %lld\n", std::llrint(-2.3)); // -2
	printf("llrint (-3.8) = %lld\n", std::llrint(-3.8)); // -4
}

	return 0;
}

int test_cmath_exp()
{
{ // std::exp: Returns the base-e exponential function of x, e^x
	double param, result;
	param = 1.0;
	result = std::exp(param);
	printf("The exponential value of %f is %f.\n", param, result); // 1.0 2.718282
}

{ // std::frexp(x, int* exp):Breaks the floating point number x into its binary significand
  // (a floating point with an absolute value between 0.5(included) and 1.0(excluded)) and an integral exponent for 2
  // x = significand * (2 ^ exponent)
	double param, result;
	int n;

	param = 8.0;
	result = std::frexp(param, &n);
	printf("%f = %f * 2^%d\n", param, result, n); // 8.0 = 0.5 * 2^4
}

{ // std::ldexp: Returns the result of multiplying x (the significand) by 2 raised to the power of exp (the exponent)
	double param, result;
	int n;

	param = 0.95;
	n = 4;
	result = std::ldexp(param, n);
	printf("%f * 2^%d = %f\n", param, n, result); // 0.95 * 2^4 = 15.2
}

{ // std::exp2: Returns the base-2 exponential function of x
	double param, result;
	param = 8.0;
	result = std::exp2(param);
	printf("2 ^ %f = %f.\n", param, result); // 2^8 = 256
}

{ // std::expm1: Compute exponential minus one
	double param, result;
	param = 1.0;
	result = std::expm1(param);
	printf("expm1 (%f) = %f.\n", param, result); // expm1(1.0) = 1.718282
}

{ // std::scalbn: Scales x by FLT_RADIX raised to the power of n
	double param, result;
	int n;

	param = 1.50;
	n = 4;
	result = std::scalbn(param, n);
	printf("%f * %d^%d = %f\n", param, FLT_RADIX, n, result); // 1.5 * 2^4 = 24.0
}

{ // std::scalbln: Scales x by FLT_RADIX raised to the power of n
	double param, result;
	long n;

	param = 1.50;
	n = 4L;
	result = std::scalbln(param, n);
	printf("%f * %d^%d = %f\n", param, FLT_RADIX, n, result); // 1.5 * 2^4 = 24.0
}

	return 0;
}

int test_cmath_log()
{
{ // std::log: Returns the natural logarithm of x
  // The natural logarithm is the base-e logarithm: the inverse of the natural exponential function (exp)
	double param, result;
	param = 5.5;
	result = std::log(param);
	printf("log(%f) = %f\n", param, result); // ln(5.5) = 1.704748
}

{ // std::log10: Returns the common (base-10) logarithm of x
	double param, result;
	param = 1000.0;
	result = std::log10(param);
	printf("log10(%f) = %f\n", param, result); // log10(1000.0) = 3.0
}

{ // std::modf: Breaks x into an integral and a fractional part
	double param, fractpart, intpart;

	param = 3.14159265;
	fractpart = std::modf(param, &intpart);
	printf("%f = %f + %f \n", param, intpart, fractpart); // 3.14159265 = 3.0 + 0.141593
}

{ // std::ilogb: Returns the integral part of the logarithm of |x|, using FLT_RADIX as base for the logarithm.
	double param;
	int result;

	param = 10.0;
	result = std::ilogb(param);
	printf("ilogb(%f) = %d\n", param, result); // ilogb(10.0) = 3
}

{ // std::log1p: Returns the natural logarithm of one plus x
	double param, result;
	param = 1.0;
	result = std::log1p(param);
	printf("log1p (%f) = %f.\n", param, result); // log1p(1.0) = 0.693147
}

{ // std::log2: Returns the binary (base-2) logarithm of x.
	double param, result;
	param = 1024.0;
	result = std::log2(param);
	printf("log2 (%f) = %f.\n", param, result); // log2(1024.0) = 10.0
}

{ // std::logb: Returns the logarithm of |x|, using FLT_RADIX as base for the logarithm
	double param, result;
	param = 1024.0;
	result = std::logb(param);
	printf("logb (%f) = %f.\n", param, result); // logb(1024.0) = 10.0
}

	return 0;
}

int test_cmath_error()
{
{ // std::erf: Returns the error function value for x.
	double param, result;
	param = 1.0;
	result = std::erf(param);
	printf("erf (%f) = %f\n", param, result); // erf(1.0) = 0.842701
}

{ // std::erfc: Returns the complementary error function value for x
	double param, result;
	param = 1.0;
	result = std::erfc(param);
	printf("erfc(%f) = %f\n", param, result); // erfc(1.0) = 0.157299
}

{ // std::tgamma: Compute gamma function
	double param, result;
	param = 0.5;
	result = std::tgamma(param);
	printf("tgamma(%f) = %f\n", param, result); // tgamma(0.5) = 1.772454
}

{ // std::lgamma: Compute log-gamma function
	double param, result;
	param = 0.5;
	result = std::lgamma(param);
	printf("lgamma(%f) = %f\n", param, result); // lgamma(0.5) = 0.572365
}

	return 0;
}

int test_cmath_1()
{
{ // std::copysign: Returns a value with the magnitude of x and the sign of y
	printf("copysign ( 10.0,-1.0) = %f\n", std::copysign(10.0, -1.0)); // -10.0
	printf("copysign (-10.0,-1.0) = %f\n", std::copysign(-10.0, -1.0)); // -10.0
	printf("copysign (-10.0, 1.0) = %f\n", std::copysign(-10.0, 1.0)); // 10.0
}

{ // std::nan: Returns a quiet NaN (Not-A-Number) value of type double.

}

{ // std::nextafter: Returns the next representable value after x in the direction of y
	printf("first representable value greater than zero: %e\n", std::nextafter(0.0, 1.0)); // 4.940656e-324
	printf("first representable value less than zero: %e\n", std::nextafter(0.0, -1.0)); // -4.940656e-324
}

{ // std::nexttoward: Returns the next representable value after x in the direction of y
	printf("first representable value greater than zero: %e\n", std::nexttoward(0.0, 1.0L)); // 4.940656e-324
	printf("first representable value less than zero: %e\n", std::nexttoward(0.0, -1.0L)); // -4.940656e-324
}

	return 0;
}

int test_cmath_2()
{
{ // std::fdim: The function returns x-y if x>y, and zero otherwise.
	printf("fdim (2.0, 1.0) = %f\n", std::fdim(2.0, 1.0)); // 1.0
	printf("fdim (1.0, 2.0) = %f\n", std::fdim(1.0, 2.0)); // 0.0
	printf("fdim (-2.0, -1.0) = %f\n", std::fdim(-2.0, -1.0)); // 0.0
	printf("fdim (-1.0, -2.0) = %f\n", std::fdim(-1.0, -2.0)); // 1.0
}

{ // std::fmax: Returns the larger of its arguments: either x or y
	printf("fmax (100.0, 1.0) = %f\n", std::fmax(100.0, 1.0)); // 100.0
	printf("fmax (-100.0, 1.0) = %f\n", std::fmax(-100.0, 1.0)); // 1.0
	printf("fmax (-100.0, -1.0) = %f\n", std::fmax(-100.0, -1.0)); // -1.0
}

{ // std::fmin: Returns the smaller of its arguments: either x or y
	printf("fmin (100.0, 1.0) = %f\n", std::fmin(100.0, 1.0)); // 1.0
	printf("fmin (-100.0, 1.0) = %f\n", std::fmin(-100.0, 1.0)); // -100.0
	printf("fmin (-100.0, -1.0) = %f\n", std::fmin(-100.0, -1.0)); // -100.0
}

	return 0;
}

int test_cmath_classify()
{
{ // std::fpclassify: Returns a value of type int that matches one of the classification
  // macro constants, depending on the value of x
	double d = std::sqrt(-1.0); // 1.0 / 0.0;
	switch (std::fpclassify(d)) {
		case FP_INFINITE:  printf("infinite");  break;
		case FP_NAN:       printf("NaN");       break; // NaN
		case FP_ZERO:      printf("zero");      break;
		case FP_SUBNORMAL: printf("subnormal"); break;
		case FP_NORMAL:    printf("normal");    break;
	}

	if (std::signbit(d)) printf(" negative\n"); // negative
	else printf(" positive or unsigned\n");
}

{ // std::isfinite: Returns whether x is a finite value
	printf("isfinite(0.0)       : %d\n", std::isfinite(0.0)); // 1
	//printf("isfinite(1.0/0.0)   : %d\n", std::isfinite(1.0 / 0.0));
	//printf("isfinite(-1.0/0.0)  : %d\n", std::isfinite(-1.0 / 0.0));
	printf("isfinite(sqrt(-1.0)): %d\n", std::isfinite(std::sqrt(-1.0))); // 0
}

{ // std::isinf: Returns whether x is an infinity value 
	printf("isinf(0.0)       : %d\n", std::isinf(0.0)); // 0
	//printf("isinf(1.0/0.0)   : %d\n", std::isinf(1.0 / 0.0));
	//printf("isinf(-1.0/0.0)  : %d\n", std::isinf(-1.0 / 0.0));
	printf("isinf(sqrt(-1.0)): %d\n", std::isinf(std::sqrt(-1.0))); // 0
}

{ // std::isnan: Returns whether x is a NaN (Not-A-Number) value.
	printf("isnan(0.0)       : %d\n", std::isnan(0.0)); // 0
	//printf("isnan(1.0/0.0)   : %d\n", std::isnan(1.0 / 0.0));
	//printf("isnan(-1.0/0.0)  : %d\n", std::isnan(-1.0 / 0.0));
	printf("isnan(sqrt(-1.0)): %d\n", std::isnan(std::sqrt(-1.0))); // 1
}

{ // std::isnormal: Returns whether x is a normal value
  // i.e., whether it is neither infinity, NaN, zero or subnormal
	printf("isnormal(1.0)    : %d\n", std::isnormal(1.0)); // 1
	printf("isnormal(0.0)    : %d\n", std::isnormal(0.0)); // 0
	//printf("isnormal(1.0/0.0): %d\n", std::isnormal(1.0 / 0.0));
}

{ // std::signbit: Returns whether the sign of x is negative
	printf("signbit(0.0)       : %d\n", std::signbit(0.0)); // 0
	//printf("signbit(1.0/0.0)   : %d\n", std::signbit(1.0 / 0.0));
	//printf("signbit(-1.0/0.0)  : %d\n", std::signbit(-1.0 / 0.0));
	printf("signbit(sqrt(-1.0)): %d\n", std::signbit(std::sqrt(-1.0))); // 1
}

	return 0;
}

int test_cmath_compare()
{
	double result;
	result = std::log(10.0);

{ // std::isgreater: Returns whether x is greater than y
	if (std::isgreater(result, 0.0))
		printf("log(10.0) is positive\n"); // log(10.0) is positive
	else
		printf("log(10.0) is not positive\n");
}

{ // std::isgreaterequal: Returns whether x is greater than or equal to y
	if (std::isgreaterequal(result, 0.0))
		printf("log(10.0) is not negative\n"); // log(10.0) is not negative
	else
		printf("log(10.0) is negative\n");
}

{ // std::isless: Returns whether x is less than y
	if (std::isless(result, 0.0))
		printf("log(10.0) is negative\n");
	else
		printf("log(10.0) is not negative\n"); // log(10.0) is not negative
}

{ // std::islessequal: Returns whether x is less than or equal to y
	if (std::islessequal(result, 0.0))
		printf("log(10.0) is not positive\n");
	else
		printf("log(10.0) is positive\n"); // log(10.0) is positive
}

{ // std::islessgreater: Returns whether x is less than or greater than y
	if (islessgreater(result, 0.0))
		printf("log(10.0) is not zero\n"); // log(10.0) is not zero
	else
		printf("log(10.0) is zero\n");
}

{ // std::isunordered: Returns whether x or y are unordered values
	double result;
	result = std::sqrt(-1.0);

	if (std::isunordered(result, 0.0))
		printf("sqrt(-1.0) and 0.0 cannot be ordered\n"); // sqrt(-1.0) and 0.0 cannot be ordered
	else
		printf("sqrt(-1.0) and 0.0 can be ordered\n");
}

	return 0;
}

} // namespace cmath_

