#include "lazy_evaluation.hpp"
#include <string>
#include <array>

// Blog: https://blog.csdn.net/fengbingchun/article/details/125824232

namespace lazy_evaluation_ {

int test_evaluation_1()
{
    // 引用计数: 除非你确实需要,否则不去为任何东西制作拷贝.我们应该是lazy的,只要有可能就共享使用其它值
    std::string str1 = "hello";
    std::string str2 = str1; // str2和str1指向同一块内存地址
    fprintf(stdout, "pointer: str1: %p, str2: %p\n", // pointer: str1: 0x2061208, str2: 0x2061208
        static_cast<void*>(const_cast<char*>(str1.c_str())), static_cast<void*>(const_cast<char*>(str2.c_str())));

    str2 = "beijing"; // str2被重新赋值后,str2和str1不在指向同一块内存地址
    fprintf(stdout, "pointer: str1: %p, str2: %p\n", // pointer: str1: 0x2061208, str2: 0x2061648
        static_cast<void*>(const_cast<char*>(str1.c_str())), static_cast<void*>(const_cast<char*>(str2.c_str())));

    return 0;
}

using matrix = std::array<int, 2>;

// write this proxy
struct matrix_add {
    matrix_add(const matrix& a, const matrix& b) : a_(a), b_(b) { fprintf(stdout, "do nothing\n"); }

    // an implicit conversion operator from matrix_add to plain matrix
    // the evaluation takes place only when the final result is assigned to a matrix instance
    operator matrix() const {
        fprintf(stdout, "add operation\n");
        matrix result;
        for (int i = 0; i < 2; ++i)
            result[i] = a_[i] + b_[i];

        return result;
    }

    // calculate one element out of a matrix sum
    // it's of course wasteful to add the whole matrices
    int operator ()(unsigned int index) const {
        fprintf(stdout, "calculate *just one* element\n");
        return a_[index] + b_[index];
    }

private:
    const matrix& a_, b_;
};

// to make this function lazy, it's enough to return a proxy instead of the actual result
matrix_add operator + (const matrix& a, const matrix& b)
{
    return matrix_add(a, b);
}

int test_evaluation_2()
{
    // reference: https://stackoverflow.com/questions/414243/lazy-evaluation-in-c
    // 矩阵计算: 主要机制是运算符重载
    matrix mat1 = {2, 3}, mat2 = {7, 8};
    auto ret = mat1 + mat2;
    fprintf(stdout, "... ...\n");
    matrix mat3(ret); // implicit conversion from matrix_add to matrix

    fprintf(stdout, "one element sum: %d\n", ret(1));

    return 0;
}

} // namespace lazy_evaluation_
