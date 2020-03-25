#ifndef FBC_PLUGIN_TEST_COMMON_HPP_
#define FBC_PLUGIN_TEST_COMMON_HPP_

#ifdef _MSC_VER
    #ifdef DLL_EXPORTS
        #define FBC_API __declspec(dllexport)
    #else
        #define FBC_API
    #endif // _MSC_VER
#else
    #ifdef DLL_EXPORTS
        #define FBC_API __attribute__((visibility("default")))
    #else
        #define FBC_API
    #endif
#endif

typedef struct fbc_rect_t {
    int left, top;
    int right, bottom;
} fbc_rect_t;

FBC_API char* get_csdn_blog_address();
FBC_API char* get_github_address();

#endif // FBC_PLUGIN_TEST_COMMON_HPP_