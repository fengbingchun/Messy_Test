#include <bit>
#include <iostream>
#include <bitset>
#include <cstdint>

// Blog: https://blog.csdn.net/fengbingchun/article/details/142025261
int test_bit()
{
	// 1.std::endian
    if constexpr (std::endian::native == std::endian::big)
        std::cout << "big-endian\n";
    else if constexpr (std::endian::native == std::endian::little)
        std::cout << "little-endian\n"; // little-endian
    else
        std::cout << "mixed-endian\n";

    // 2.std::bit_cast
    static_assert(sizeof(float) == sizeof(uint32_t));
    constexpr float value{ 123.456f };
    uint32_t v1 = std::bit_cast<uint32_t>(value);
    float v2 = std::bit_cast<float>(v1);
    std::cout << std::hex << "v1: " << v1 << ", v2: " << v2 << std::dec << std::endl; // v1: 42f6e979, v2: 123.456

    // 3.std::has_single_bit
    constexpr auto v3{ 4u }, v4{ 6u };
    std::cout << std::has_single_bit(v3) << "," << std::has_single_bit(v4) << std::endl; // 1,0

    // 4.std::bit_ceil
    using bin = std::bitset<8>;
    std::cout << bin(std::bit_ceil(3u)) << "," << bin(std::bit_ceil(9u)) << std::endl; // 00000100,00010000

    // 5.std::bit_floor
    std::cout << bin(std::bit_floor(3u)) << "," << bin(std::bit_floor(9u)) << std::endl; // 00000010,00001000

    // 6.std::bit_width
    std::cout <<  std::bit_width(0u) << "," << std::bit_width(3u) << std::endl; // 0,2
    
    // 7.std::rotl
    constexpr std::uint8_t i{ 0b00011101 };
    std::cout << bin(std::rotl(i, 1)) << "," << bin(std::rotl(i, 4)) << std::endl; // 00111010,11010001
    
    // 8.std::rotr
    std::cout << bin(std::rotr(i, 1)) << "," << bin(std::rotr(i, 4)) << std::endl; // 10001110,11010001
    
    // 9.std::countl_zero
    constexpr std::uint16_t s{ 0b00100011 };
    std::cout << std::countl_zero(i) << "," << std::countl_zero(s) << std::endl; // 3, 10

    // 10.std::countl_one
    constexpr std::uint32_t l{ 0b11111111101100110000000011111100 };
    std::cout << std::dec << std::countl_one(i) << "," << std::countl_one(l) << std::endl; // 0,9

    // 11.std::countr_zero
    std::cout << std::countr_zero(i) << "," << std::countr_zero(l) << std::endl; // 0,2

    // 12.std::countr_one
    std::cout << std::countr_one(i) << "," << std::countr_one(s) << std::endl; // 1,2

    // 13.std::popcount
    std::cout << std::popcount(s) << "," << std::popcount(l) << std::endl; // 3,19

	return 0;
}
