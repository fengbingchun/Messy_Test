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

inline std::string gbk_to_utf8(const std::string& str)
{
#ifdef _MSC_VER
	// gbk to wchar
	auto len = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
	std::wstring wstr(len, 0);
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wstr[0], len);

	// wchar to utf8
	len = ::WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	std::string u8str(len, 0);
	::WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &u8str[0], len, nullptr, nullptr);

	u8str.pop_back(); // remove '\0'
	return u8str;
#else
	return std::string{"Unimplemented"};
#endif
}

inline std::string utf8_to_gbk(const std::string& u8str)
{
#ifdef _MSC_VER
	// utf8 to wchar
	auto len = ::MultiByteToWideChar(CP_UTF8, 0, u8str.c_str(), -1, nullptr, 0);
	std::wstring wstr(len, 0);
	::MultiByteToWideChar(CP_UTF8, 0, u8str.c_str(), -1, &wstr[0], len);

	// wchar to gbk
	len = ::WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	std::string str(len, 0);
	::WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &str[0], len, nullptr, nullptr);

	str.pop_back(); // remove '\0' 
	return str;
#else
	return std::string{"Unimplemented"};
#endif
}

} // namespace


#endif // FBC_MESSY_TEST_COMMON_HPP_
