#ifndef FBC_MESSY_TEST_EXPLICIT_HPP
#define FBC_MESSY_TEST_EXPLICIT_HPP

// reference Bjarne Stroustrup sample
class String{
public:
	/*explicit*/ String(int n) {};
	String(const char *p) {};
};

void test_explicit();

#endif // FBC_MESSY_TEST_EXPLICIT_HPP

