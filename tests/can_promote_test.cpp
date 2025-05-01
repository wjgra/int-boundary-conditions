#include <catch2/catch_test_macros.hpp>
#include <ranges>

#include "boundary_conditions.hpp"

// Open question: how should we test for correctness on unusual platforms? For instance, int types
// with extra padding bits.

template <std::integral T>
void can_promote_test_exhaustive()
{
    for (const auto i : std::views::iota(std::numeric_limits<T>::min())) {
        REQUIRE(wjg::boundary_conditons::can_promote(i));
        if (i == std::numeric_limits<T>::max())
            break;
    }
}

/**
 * @brief Exhaustive test of uint8_t promotion.
 */
TEST_CASE("can_promote_u8")
{
    // uint8_t promotes to int, which can always hold the value of the uint8_t.
    static_assert(std::is_same<decltype(+uint8_t{}), int>::value);
    can_promote_test_exhaustive<uint8_t>();
}

/**
 * @brief Exhaustive test of uint16_t promotion.
 */
TEST_CASE("can_promote_u16")
{
    // uint16_t promotes to int, which can always hold the value of the uint16_t.
    static_assert(std::is_same<decltype(+uint16_t{}), int>::value);
    can_promote_test_exhaustive<uint16_t>();
}

/**
 * @brief Exhaustive test of int8_t promotion.
 */
TEST_CASE("can_promote_i8")
{
    // int8_t promotes to int, which can always hold the value of the int8_t.
    static_assert(std::is_same<decltype(+int8_t{}), int>::value);
    can_promote_test_exhaustive<int8_t>();
}

/**
 * @brief Exhaustive test of int16_t promotion.
 */
TEST_CASE("can_promote_i16")
{
    // int16_t promotes to int, which can always hold the value of the int16_t.
    static_assert(std::is_same<decltype(+int16_t{}), int>::value);
    can_promote_test_exhaustive<int16_t>();
}

// TO DO: non-exhaustive test cases for larger int types