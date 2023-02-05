#pragma once

#ifndef __cplusplus
#error The file requires a C++ compiler.
#endif

// 字符串化
#define STRING(content) #content

// 拼接
#define SPLICE(front, back) front##back

// 弃用
#define DEPRECATED \
[[deprecated("The name for this item is deprecated.")]]

// 替换
#define REPLACEMENT(signature) \
[[deprecated("The name for this item is deprecated. " \
"Instead, use the name: " STRING(signature) ".")]]

// 自定义名称空间
#define ETERFREE_SPACE_BEGIN namespace eterfree {
#define ETERFREE_SPACE_END }
#define USING_ETERFREE_SPACE using namespace eterfree;

ETERFREE_SPACE_BEGIN

//template <typename _Type, const decltype(sizeof(0)) _SIZE>
//constexpr auto size(_Type(&_array)[_SIZE]) noexcept
//{
//	return sizeof _array / sizeof _array[0];
//}

template <typename _Type, const decltype(sizeof(0)) _SIZE>
constexpr auto size(_Type(&_array)[_SIZE]) noexcept
{
	return _SIZE;
}

ETERFREE_SPACE_END
