#ifndef _WJG_BOUNDARY_CONDITIONS_HPP_
#define _WJG_BOUNDARY_CONDITIONS_HPP_

#include <concepts>
#include <cstdint>
#include <limits>
#include <print> // temp
#include <utility>

namespace wjg {

namespace boundary_conditons {

namespace internal {

#if defined __has_builtin && __has_builtin(__builtin_add_overflow_p)
constexpr bool has_builtin_add_overflow_p = true;
#else
constexpr bool has_builtin_add_overflow_p = false;
#endif

/**
 * @brief Traits class for retrieving the type resulting from an integral promotion.
 */
template <std::integral A>
struct promoted_type {
    using name = decltype([] -> auto {
        A a;
        return +a;
    }());
};

enum class int_conversion_rank { signed_char_r, short_r, int_r, long_r, long_long_r };

template <std::integral A>
constexpr int_conversion_rank integer_conversion_rank(A a) noexcept;

// clang-format off
// wjg - I guess these could be traits classes too, I'd just have to explicitly instantiate them
constexpr auto integer_conversion_rank(char) noexcept { return int_conversion_rank::signed_char_r; }
constexpr auto integer_conversion_rank(unsigned char) noexcept { return int_conversion_rank::signed_char_r; }
constexpr auto integer_conversion_rank(signed char) noexcept { return int_conversion_rank::signed_char_r; }
constexpr auto integer_conversion_rank(unsigned short) noexcept { return int_conversion_rank::short_r; }
constexpr auto integer_conversion_rank(signed short) noexcept { return int_conversion_rank::short_r; }
constexpr auto integer_conversion_rank(unsigned int) noexcept { return int_conversion_rank::int_r; }
constexpr auto integer_conversion_rank(signed int) noexcept { return int_conversion_rank::int_r; }
constexpr auto integer_conversion_rank(unsigned long) noexcept { return int_conversion_rank::long_r; }
constexpr auto integer_conversion_rank(signed long) noexcept { return int_conversion_rank::long_r; }
constexpr auto integer_conversion_rank(unsigned long long) noexcept { return int_conversion_rank::long_long_r; }
constexpr auto integer_conversion_rank(signed long long) noexcept { return int_conversion_rank::long_long_r; }
// clang-format on

// WJG: consider whether the promotion should be taken out of this...
template <std::integral A, std::integral B>
struct common_type {
private:
    using A1 = promoted_type<A>::name;
    using B1 = promoted_type<B>::name;
    using greater_rank = decltype([] -> auto {
        constexpr A1 a1{};
        constexpr B1 b1{};
        if constexpr (integer_conversion_rank(a1) > integer_conversion_rank(b1)) {
            return a1;
        }
        else {
            return b1;
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

            constexpr U u{};
            constexpr S s{};
            if constexpr (integer_conversion_rank(u) >= integer_conversion_rank(s)) {
                return u;
            }
            else if constexpr (/* S can represent all values of U */
                               std::in_range<S>(std::numeric_limits<U>::max()) &&
                               std::in_range<S>(
                                   std::numeric_limits<U>::min())) { // zero is always in range...?
                return s;
            }
            else {
                return std::make_unsigned<S>{};
            }
        }
    }());
};

} // namespace internal

template <class R, class A>
constexpr bool can_convert(A a) noexcept;

template <class R, class A>
constexpr bool can_convert_modular(A a) noexcept;

/**
 * @brief Determines whether the the result of evaluating the expression ++a matches the result of
 * evaluating the corresponding mathematical operation a + 1.
 * @param a an integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation, false otherwise.
 */
template <std::integral A>
constexpr bool can_increment(A a) noexcept
{
    // wjg: I'm not sure this handles out of range correctly if it ends up being negative - can
    // promotion do that?
    // return internal::promote(a) < std::numeric_limits<A>::max();
    using C = internal::common_type<A, decltype(1)>::name;

    // need to to the promotion separately and check whether we can promote - for now assume
    // promotion was okay
    return static_cast<C>(+a) < std::numeric_limits<C>::max() &&
           std::in_range<A>(static_cast<C>(+a) + static_cast<C>(+1));
}

/**
 * @brief Determines whether the the result of evaluating the expression --a matches the result of
 * evaluating the corresponding mathematical operation a - 1.
 * @param a an integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation, false otherwise.
 */
template <std::integral A>
constexpr bool can_decrement(A a) noexcept
{
    using C = internal::common_type<A, decltype(1)>::name;

    // need to to the promotion separately and check whether we can promote - for now assume
    // promotion was okay
    return static_cast<C>(+a) > std::numeric_limits<C>::min() &&
           std::in_range<A>(static_cast<C>(+a) - static_cast<C>(+1));
}

/**
 * @brief Determines whether the the result of evaluating the expression +a matches the result of
 * evaluating the corresponding mathematical operation a.
 * @param a an integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation, false otherwise.
 */
template <std::integral A>
constexpr bool can_promote(A a) noexcept
{
    return std::in_range<internal::promoted_type<A>::name>(a);
}

template <class A>
constexpr bool can_negate(A a) noexcept;

template <class A>
constexpr bool can_bitwise_not(A a) noexcept;

template <class A>
constexpr bool can_increment_modular(A a) noexcept;

template <class A>
constexpr bool can_decrement_modular(A a) noexcept;

template <class A>
constexpr bool can_promote_modular(A a) noexcept;

template <class A>
constexpr bool can_negate_modular(A a) noexcept;

template <class A>
constexpr bool can_bitwise_not_modular(A a) noexcept;

/**
 * Determines whether the the result of evaluating the expression a + b matches the result of
 * evaluating the corresponding mathematical operation a + b.
 * @param a the first integer
 * @param b the second integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation, false otherwise.
 */
template <class A, class B>
constexpr bool can_add(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_subtract(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_multiply(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_divide(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_take_remainder(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_shift_left(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_shift_right(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_bitwise_and(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_bitwise_xor(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_bitwise_or(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_compare(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_add_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_subtract_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_multiply_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_shift_left_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_shift_right_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_bitwise_and_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_bitwise_xor_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_bitwise_or_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_add_in_place(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_subtract_in_place(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_multiply_in_place(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_divide_in_place(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_take_remainder_in_place(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_shift_left_in_place(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_shift_right_in_place(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_bitwise_and_in_place(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_bitwise_xor_in_place(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_bitwise_or_in_place(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_add_in_place_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_subtract_in_place_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_multiply_in_place_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_shift_left_in_place_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_shift_right_in_place_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_bitwise_and_in_place_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_bitwise_xor_in_place_modular(A a, B b) noexcept;

template <class A, class B>
constexpr bool can_bitwise_or_in_place_modular(A a, B b) noexcept;

} // namespace boundary_conditons

} // namespace wjg

template <std::integral T>
constexpr bool wjg::boundary_conditons::can_add(const T a, const T b) noexcept
{
    // need to handle promotion
    if constexpr (wjg::boundary_conditons::internal::has_builtin_add_overflow_p) {
        return __builtin_add_overflow_p(a, b, static_cast<T>(0)) == false;
    }
    else {
        // TO IMPLEMENT
        return false;
    }
}

#endif