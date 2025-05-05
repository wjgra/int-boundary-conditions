#include <catch2/catch_test_macros.hpp>

#include "boundary_conditions.hpp"

/**
 * @brief Non-exhaustive test of uint8_t+uint8_t addition.
 */
TEST_CASE("can_add_u8_u8")
{
    // Since both operands get promoted to int, addition of two u8s is always possible. Test in a
    // neighbourhood of the endpoints.

    constexpr uint8_t nbhd_size = 10;
    constexpr uint8_t max_value = std::numeric_limits<uint8_t>::max();

    // Both args in neighbourhood of zero
    for (uint8_t i = 0; i < nbhd_size; ++i) {
        for (uint8_t j = 0; j <= i; ++j) {
            REQUIRE(wjg::boundary_conditons::can_add(i, j));
        }
    }

    // Both args in neighbourhood of UINT8_MAX
    uint8_t i = max_value - nbhd_size;
    do {
        uint8_t j = max_value - nbhd_size;
        do {
            REQUIRE(wjg::boundary_conditons::can_add(i, j));
            ++j;
        } while (j != i);
        ++i;
    } while (i != max_value);

    // One arg in neighbourhood of zero, the other in neighbourhood of UINT8_MAX
    for (uint8_t i = 0; i < nbhd_size; ++i) {
        uint8_t j = max_value - nbhd_size;
        do {
            REQUIRE(wjg::boundary_conditons::can_add(i, j));
            ++j;
        } while (j != max_value);
    }
}

/**
 * @brief Non-exhaustive test of uint8_t+int addition.
 */
TEST_CASE("can_add_u8_int")
{
    // Both operands get promoted to int - addition possible when the sum is within range of int.

    // Always succeeds in small neighbourhood of zero.
    constexpr int nbhd_size = 10;

    for (int i = 0; i < nbhd_size; ++i) {
        for (uint8_t j = 0; j < nbhd_size; ++j) {
            REQUIRE(wjg::boundary_conditons::can_add(i, j));
        }
    }

    // Always succeds when sum is INT_MAX
    int i = std::numeric_limits<int>::max();
    uint8_t j = 0;
    do {
        REQUIRE(wjg::boundary_conditons::can_add(i, j));
        --i;
        ++j;
    } while (j != std::numeric_limits<uint8_t>::max());

    // Always succeeds when sum is INT_MAX - 1
    i = std::numeric_limits<int>::max() - 1;
    j = 0;
    do {
        REQUIRE(wjg::boundary_conditons::can_add(i, j));
        --i;
        ++j;
    } while (j != std::numeric_limits<uint8_t>::max());

    // Never succeds when sum is INT_MAX + 1
    i = std::numeric_limits<int>::max();
    j = 1;
    do {
        REQUIRE_FALSE(wjg::boundary_conditons::can_add(i, j));
        --i;
        ++j;
    } while (j != std::numeric_limits<uint8_t>::max());
}
