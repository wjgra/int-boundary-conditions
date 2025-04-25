// (C) William Grace 2025 - this was a fun exercise, until I realised I could just do decltype(A{} + B{})

#pragma once

#include <concepts>
#include <cstdint>
#include <limits>
#include <utility>

namespace boundary_conditons {

namespace internal {

/**
 * @brief Traits class for retrieving the type resulting from an integral promotion.
 */
template <std::integral A>
struct promoted_type {
    using name = decltype([] -> auto { return +A{}; }());
};

enum class int_conversion_rank { char_r, short_r, int_r, long_r, long_long_r };

// clang-format off
template <std::integral A>
struct integer_conversion_rank {
    constexpr static int_conversion_rank value = [] -> auto {
        if      constexpr (std::same_as<A, char>)           { return int_conversion_rank::char_r; }
        else if constexpr (std::same_as<A, unsigned char>)  { return int_conversion_rank::char_r; }
        else if constexpr (std::same_as<A, signed char>)    { return int_conversion_rank::char_r; }
        else if constexpr (std::same_as<A, unsigned short>) { return int_conversion_rank::short_r; }
        else if constexpr (std::same_as<A, signed short>)   { return int_conversion_rank::short_r; }
        else if constexpr (std::same_as<A, unsigned int>)   { return int_conversion_rank::int_r; }
        else if constexpr (std::same_as<A, signed int>)     { return int_conversion_rank::int_r; }
        else if constexpr (std::same_as<A, unsigned long>)  { return int_conversion_rank::long_r; }
        else if constexpr (std::same_as<A, signed long>)    { return int_conversion_rank::long_r; }
        else if constexpr (std::same_as<A, long long>)      { return int_conversion_rank::long_long_r; }
        else if constexpr (std::same_as<A, long long>)      { return int_conversion_rank::long_long_r; }
    }();
};
// clang-format on

template <std::integral A, std::integral B>
struct common_type {
private:
    using A1 = promoted_type<A>::name;
    using B1 = promoted_type<B>::name;
    using greater_rank = decltype([] -> auto {
        if constexpr (integer_conversion_rank<A1>::value > integer_conversion_rank<B1>::value) {
            return A1{};
        }
        else {
            return B1{};
        }
    }());

public:
    using name = decltype([] -> auto {
        if constexpr (std::is_same<A1, B1>::value) {
            return A1{};
        }
        else if constexpr ((std::signed_integral<A1> && std::signed_integral<B1>) ||
                           (std::unsigned_integral<A1> && std::unsigned_integral<B1>)) {
            return greater_rank{};
        }
        else {
            // At this point, exactly one type is signed and exactly one is unsigned
            using U = decltype([] -> auto {
                if constexpr (std::signed_integral<A1>) {
                    return A1{};
                }
                else {
                    return B1{};
                }
            });

            using S = decltype([] -> auto {
                if constexpr (std::unsigned_integral<A1>) {
                    return A1{};
                }
                else {
                    return B1{};
                }
            });

            if constexpr (integer_conversion_rank<U>::value >= integer_conversion_rank<S>::value) {
                return U{};
            }
            else if constexpr (/* S can represent all values of U */
                               std::in_range<S>(std::numeric_limits<U>::max()) &&
                               std::in_range<S>(
                                   std::numeric_limits<U>::min())) { // zero is always in range...?
                return S{};
            }
            else {
                return std::make_unsigned<S>{};
            }
        }
    }());
};

} // namespace internal

}