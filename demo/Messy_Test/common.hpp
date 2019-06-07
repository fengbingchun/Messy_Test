#ifndef FBC_MESSY_TEST_COMMON_HPP_
#define FBC_MESSY_TEST_COMMON_HPP_

#ifdef _MSC_VER
#include <Windows.h>
#endif

namespace {

inline char* utf8_to_gbk(const char* utf8)
{
#ifdef _MSC_VER
	const int maxlen = 256;
	char gbk[maxlen];
	wchar_t unicode_str[maxlen];
	int outlen = MultiByteToWideChar(CP_UTF8, 0, utf8, strlen(utf8), unicode_str, maxlen);
	outlen = WideCharToMultiByte(CP_ACP, 0, unicode_str, outlen, gbk, maxlen, NULL, NULL);
	gbk[outlen] = '\0';
	return gbk;
#else // linux
	return const_cast<char*>(utf8);
#endif
}


} // namespace


#endif // FBC_MESSY_TEST_COMMON_HPP_
