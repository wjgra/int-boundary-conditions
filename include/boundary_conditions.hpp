#ifndef _WJG_BOUNDARY_CONDITIONS_HPP_
#define _WJG_BOUNDARY_CONDITIONS_HPP_

#include <concepts>
#include <limits>
#include <utility>

namespace wjg {

namespace boundary_conditons {

// clang-format off
template <std::integral R, std::integral A> constexpr bool can_convert(A a)                             noexcept;
template <std::integral R, std::integral A> constexpr bool can_convert_modular(A a)                     noexcept;
template <std::integral A>                  constexpr bool can_increment(A a)                           noexcept;
template <std::integral A>                  constexpr bool can_decrement(A a)                           noexcept;
template <std::integral A>                  constexpr bool can_promote(A a)                             noexcept;
template <std::integral A>                  constexpr bool can_negate(A a)                              noexcept;
template <std::integral A>                  constexpr bool can_bitwise_not(A a)                         noexcept;
template <std::integral A>                  constexpr bool can_increment_modular(A a)                   noexcept;
template <std::integral A>                  constexpr bool can_decrement_modular(A a)                   noexcept;
template <std::integral A>                  constexpr bool can_promote_modular(A a)                     noexcept;
template <std::integral A>                  constexpr bool can_negate_modular(A a)                      noexcept;
template <std::integral A>                  constexpr bool can_bitwise_not_modular(A a)                 noexcept;
template <std::integral A, std::integral B> constexpr bool can_add(A a, B b)                            noexcept;
template <std::integral A, std::integral B> constexpr bool can_subtract(A a, B b)                       noexcept;
template <std::integral A, std::integral B> constexpr bool can_multiply(A a, B b)                       noexcept;
template <std::integral A, std::integral B> constexpr bool can_divide(A a, B b)                         noexcept;
template <std::integral A, std::integral B> constexpr bool can_take_remainder(A a, B b)                 noexcept;
template <std::integral A, std::integral B> constexpr bool can_shift_left(A a, B b)                     noexcept;
template <std::integral A, std::integral B> constexpr bool can_shift_right(A a, B b)                    noexcept;
template <std::integral A, std::integral B> constexpr bool can_bitwise_and(A a, B b)                    noexcept;
template <std::integral A, std::integral B> constexpr bool can_bitwise_xor(A a, B b)                    noexcept;
template <std::integral A, std::integral B> constexpr bool can_bitwise_or(A a, B b)                     noexcept;
template <std::integral A, std::integral B> constexpr bool can_compare(A a, B b)                        noexcept;
template <std::integral A, std::integral B> constexpr bool can_add_modular(A a, B b)                    noexcept;
template <std::integral A, std::integral B> constexpr bool can_subtract_modular(A a, B b)               noexcept;
template <std::integral A, std::integral B> constexpr bool can_multiply_modular(A a, B b)               noexcept;
template <std::integral A, std::integral B> constexpr bool can_shift_left_modular(A a, B b)             noexcept;
template <std::integral A, std::integral B> constexpr bool can_shift_right_modular(A a, B b)            noexcept;
template <std::integral A, std::integral B> constexpr bool can_bitwise_and_modular(A a, B b)            noexcept;
template <std::integral A, std::integral B> constexpr bool can_bitwise_xor_modular(A a, B b)            noexcept;
template <std::integral A, std::integral B> constexpr bool can_bitwise_or_modular(A a, B b)             noexcept;
template <std::integral A, std::integral B> constexpr bool can_add_in_place(A a, B b)                   noexcept;
template <std::integral A, std::integral B> constexpr bool can_subtract_in_place(A a, B b)              noexcept;
template <std::integral A, std::integral B> constexpr bool can_multiply_in_place(A a, B b)              noexcept;
template <std::integral A, std::integral B> constexpr bool can_divide_in_place(A a, B b)                noexcept;
template <std::integral A, std::integral B> constexpr bool can_take_remainder_in_place(A a, B b)        noexcept;
template <std::integral A, std::integral B> constexpr bool can_shift_left_in_place(A a, B b)            noexcept;
template <std::integral A, std::integral B> constexpr bool can_shift_right_in_place(A a, B b)           noexcept;
template <std::integral A, std::integral B> constexpr bool can_bitwise_and_in_place(A a, B b)           noexcept;
template <std::integral A, std::integral B> constexpr bool can_bitwise_xor_in_place(A a, B b)           noexcept;
template <std::integral A, std::integral B> constexpr bool can_bitwise_or_in_place(A a, B b)            noexcept;
template <std::integral A, std::integral B> constexpr bool can_add_in_place_modular(A a, B b)           noexcept;
template <std::integral A, std::integral B> constexpr bool can_subtract_in_place_modular(A a, B b)      noexcept;
template <std::integral A, std::integral B> constexpr bool can_multiply_in_place_modular(A a, B b)      noexcept;
template <std::integral A, std::integral B> constexpr bool can_shift_left_in_place_modular(A a, B b)    noexcept;
template <std::integral A, std::integral B> constexpr bool can_shift_right_in_place_modular(A a, B b)   noexcept;
template <std::integral A, std::integral B> constexpr bool can_bitwise_and_in_place_modular(A a, B b)   noexcept;
template <std::integral A, std::integral B> constexpr bool can_bitwise_xor_in_place_modular(A a, B b)   noexcept;
template <std::integral A, std::integral B> constexpr bool can_bitwise_or_in_place_modular(A a, B b)    noexcept;
// clang-format on

namespace internal {

/**
 * @brief Traits class for retrieving the type resulting from an integral promotion.
 */
template <std::integral A>
struct promoted_type {
    using name = decltype(+A{});
};

/**
 * @brief Traits class for retrieving the common type of a binary arithmetic operation.
 */
template <std::integral A, std::integral B>
struct common_type {
    using name = decltype(A{} + B{});
};

#if defined __has_builtin && __has_builtin(__builtin_add_overflow_p)
/**
 * @brief Helper function wrapper for add intrinsic.
 */
template <std::integral A, std::integral B>
constexpr bool builtin_can_add(A a, B b) noexcept
{
    return __builtin_add_overflow_p(a, b, typename common_type<A, B>::name{}) == false;
}
#endif

#if !defined WJG_BOUNDARY_CONDITIONS_NO_BUILTINS && defined __has_builtin && \
    __has_builtin(__builtin_add_overflow_p)
constexpr bool has_builtin_add_overflow_p = true;
#else
constexpr bool has_builtin_add_overflow_p = false;
#endif

#if defined __has_builtin && __has_builtin(__builtin_sub_overflow_p)
/**
 * @brief Helper function wrapper for sub intrinsic.
 */
template <std::integral A, std::integral B>
constexpr bool builtin_can_sub(A a, B b) noexcept
{
    return __builtin_sub_overflow_p(a, b, typename common_type<A, B>::name{}) == false;
}
#endif

#if !defined WJG_BOUNDARY_CONDITIONS_NO_BUILTINS && defined __has_builtin && \
    __has_builtin(__builtin_sub_overflow_p)
constexpr bool has_builtin_sub_overflow_p = true;
#else
constexpr bool has_builtin_sub_overflow_p = false;
#endif

#if defined __has_builtin && __has_builtin(__builtin_mul_overflow_p)
/**
 * @brief Helper function wrapper for mul intrinsic.
 */
template <std::integral A, std::integral B>
constexpr bool builtin_can_mul(A a, B b) noexcept
{
    return __builtin_mul_overflow_p(a, b, typename common_type<A, B>::name{}) == false;
}
#endif

#if !defined WJG_BOUNDARY_CONDITIONS_NO_BUILTINS && defined __has_builtin && \
    __has_builtin(__builtin_mul_overflow_p)
constexpr bool has_builtin_mul_overflow_p = true;
#else
constexpr bool has_builtin_mul_overflow_p = false;
#endif

} // namespace internal

/**
 * @brief Determines whether the the result of evaluating the expression static_cast<R>(a) matches
 * the result of evaluating the corresponding mathematical operation a + 1.
 * @param a an integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation, false otherwise.
 */
template <std::integral R, std::integral A>
constexpr bool can_convert(A a) noexcept
{
    return std::in_range<R>(a);
}

/**
 * @brief Determines whether the the result of evaluating the expression static_cast<R>(a) matches
 * the result of evaluating the corresponding mathematical operation a + 1 modulo N, where N is the
 * range exponent of the result type.
 * @param a an integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation modulo N, false otherwise.
 */
template <std::integral R, std::integral A>
constexpr bool can_convert_modular(A a) noexcept
{
    // For unsigned integers, this has always been true. For signed integers, this has been true
    // since C++20.
    return true;
}

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
    return can_add_in_place(a, 1);
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
    return can_subtract_in_place(a, 1);
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
    return std::in_range<typename internal::promoted_type<A>::name>(a);
}

/**
 * @brief Determines whether the the result of evaluating the expression -a matches the result of
 * evaluating the corresponding mathematical operation -a.
 * @param a an integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation, false otherwise.
 */
template <std::integral A>
constexpr bool can_negate(A a) noexcept
{
    // Zero can always be negated, yielding zero.
    static_assert(A{} == -A{} && A{} == 0);
    if (a == 0) {
        return true;
    }

    using A_promoted = typename internal::promoted_type<A>::name;

    // If the promoted type is unsigned, then the negation is 2^N - a, where N is the width of the
    // promoted type. In this case, zero is the only value which can be negated.
    if constexpr (std::unsigned_integral<A_promoted>) {
        return false;
    }
    else {
        // If a is promoted without changing its value, then all values except the minimum are
        // negatable.
        static_assert(std::numeric_limits<A_promoted>::min() + 1 ==
                      -std::numeric_limits<A_promoted>::max());
        return can_promote(a) && (+a) != std::numeric_limits<A_promoted>::min();
    }
}

template <std::integral A>
constexpr bool can_bitwise_not(A a) noexcept;

/**
 * @brief Determines whether the the result of evaluating the expression ++a matches the result
 * of evaluating the corresponding mathematical operation a + 1 modulo N, where N is the
 * range exponent of the result type.
 * @param a an integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation modulo N, false otherwise.
 */
template <std::integral A>
constexpr bool can_increment_modular(A a) noexcept
{
    return can_add_in_place_modular(a, 1);
}

/**
 * @brief Determines whether the the result of evaluating the expression --a matches the result
 * of evaluating the corresponding mathematical operation a - 1 modulo N, where N is the
 * range exponent of the result type.
 * @param a an integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation modulo N, false otherwise.
 */
template <std::integral A>
constexpr bool can_decrement_modular(A a) noexcept
{
    return can_subtract_in_place_modular(a, 1);
}

/**
 * @brief NOT IMPLEMENTED
 */
template <std::integral A>
constexpr bool can_promote_modular(A a) noexcept
{
    // Temp implementation - to consider how this differs from can_promote()
    return can_promote(a);
}

template <std::integral A>
constexpr bool can_negate_modular(A a) noexcept;

template <std::integral A>
constexpr bool can_bitwise_not_modular(A a) noexcept;

/**
 * Determines whether the the result of evaluating the expression a + b matches the result of
 * evaluating the corresponding mathematical operation a + b.
 * @param a the first integer
 * @param b the second integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation, false otherwise.
 */
template <std::integral A, std::integral B>
constexpr bool can_add(A a, B b) noexcept
{
    // Use built-in if available
    if constexpr (internal::has_builtin_add_overflow_p) {
        return internal::builtin_can_add(a, b);
    }

    if (!can_promote(a) || !can_promote(b)) {
        return false;
    }

    // Get the values of a and b after integer promotion and usual arithmetic conversion.
    using C = internal::common_type<A, B>::name;
    const auto promoted_a = static_cast<C>(+a);
    const auto promoted_b = static_cast<C>(+b);

    // Check result fits in common type C
    if (promoted_b > 0 && promoted_a > (std::numeric_limits<C>::max() - promoted_b)) {
        return false;
    }
    if (promoted_b < 0 && promoted_a < (std::numeric_limits<C>::min() - promoted_b)) {
        return false;
    }
    return true;
}

/**
 * Determines whether the the result of evaluating the expression a - b matches the result of
 * evaluating the corresponding mathematical operation a - b.
 * @param a the first integer
 * @param b the second integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation, false otherwise.
 */
template <std::integral A, std::integral B>
constexpr bool can_subtract(A a, B b) noexcept
{
    // Use built-in if available
    if constexpr (internal::has_builtin_sub_overflow_p) {
        return internal::builtin_can_sub(a, b);
    }

    if (!can_promote(a) || !can_promote(b)) {
        return false;
    }

    // Get the values of a and b after integer promotion and usual arithmetic conversion.
    using C = internal::common_type<A, B>::name;
    const auto promoted_a = static_cast<C>(+a);
    const auto promoted_b = static_cast<C>(+b);

    // Check result fits in common type C
    if (promoted_b > 0 && promoted_a < (std::numeric_limits<C>::max() + promoted_b)) {
        return false;
    }
    if (promoted_b < 0 && promoted_a > (std::numeric_limits<C>::min() + promoted_b)) {
        return false;
    }
    return true;
}

template <std::integral A, std::integral B>
constexpr bool can_multiply(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_divide(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_take_remainder(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_left(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_right(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_and(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_xor(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_or(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_compare(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_add_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_subtract_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_multiply_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_left_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_right_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_and_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_xor_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_or_modular(A a, B b) noexcept;

/**
 * @brief Determines whether the the result of evaluating the expression a += b matches the result
 * of evaluating the corresponding mathematical operation a + b.
 * @param a an integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation, false otherwise.
 */
template <std::integral A, std::integral B>
constexpr bool can_add_in_place(A a, B b) noexcept
{
    return can_add(a, b) && std::in_range<A>(a + b);
}

/**
 * @brief Determines whether the the result of evaluating the expression a -= b matches the result
 * of evaluating the corresponding mathematical operation a - b.
 * @param a an integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation, false otherwise.
 */
template <std::integral A, std::integral B>
constexpr bool can_subtract_in_place(A a, B b) noexcept
{
    return can_subtract(a, b) && std::in_range<A>(a - b);
}

template <std::integral A, std::integral B>
constexpr bool can_multiply_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_divide_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_take_remainder_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_left_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_right_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_and_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_xor_in_place(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_or_in_place(A a, B b) noexcept;

/**
 * @brief Determines whether the the result of evaluating the expression a += b matches the result
 * of evaluating the corresponding mathematical operation a + b modulo N, where N is the
 * range exponent of the result type.
 * @param a an integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation modulo N, false otherwise.
 */
template <std::integral A, std::integral B>
constexpr bool can_add_in_place_modular(A a, B b) noexcept
{
    // WJG: I do not think the GCC intrinsics can be used here easily.

    if (!can_promote(a) || !can_promote(b)) {
        // WJG: Consider whether it is possible for errant promotions to yield the correct result
        // mod N. How does this relate to can_promote_modular(a)?
        return false;
    }

    // Get the values of a and b after integer promotion and usual arithmetic conversion.
    using C = internal::common_type<A, B>::name;
    const auto promoted_a = static_cast<C>(+a);
    const auto promoted_b = static_cast<C>(+b);

    // Check result fits in common type C - if it doesn't return false unless a) C is unsigned, so
    // overflow is well-defined and b) C is the same as the result type, so the overflow is
    // equivalent to operations modulo N.
    if (promoted_b > 0 && promoted_a > (std::numeric_limits<C>::max() - promoted_b)) {
        return std::unsigned_integral<C> && std::is_same<C, A>();
    }
    if (promoted_b < 0 && promoted_a < (std::numeric_limits<C>::min() - promoted_b)) {
        return std::unsigned_integral<C> && std::is_same<C, A>();
    }
    return true;
}

/**
 * @brief Determines whether the the result of evaluating the expression a -= b matches the result
 * of evaluating the corresponding mathematical operation a - b modulo N, where N is the
 * range exponent of the result type.
 * @param a an integer
 * @return true if the result of evaluating the expression matches the result of evaluating the
 * corresponding mathematical operation modulo N, false otherwise.
 */
template <std::integral A, std::integral B>
constexpr bool can_subtract_in_place_modular(A a, B b) noexcept
{
    // WJG: I do not think the GCC intrinsics can be used here easily.

    if (!can_promote(a) || !can_promote(b)) {
        // WJG: Consider whether it is possible for errant promotions to yield the correct result
        // mod N. How does this relate to can_promote_modular(a)?
        return false;
    }

    // Get the values of a and b after integer promotion and usual arithmetic conversion.
    using C = internal::common_type<A, B>::name;
    const auto promoted_a = static_cast<C>(+a);
    const auto promoted_b = static_cast<C>(+b);

    // Check result fits in common type C - if it doesn't return false unless a) C is unsigned, so
    // overflow is well-defined and b) C is the same as the result type, so the overflow is
    // equivalent to operations modulo N.
    if (promoted_b > 0 && promoted_a < (std::numeric_limits<C>::max() + promoted_b)) {
        return std::unsigned_integral<C> && std::is_same<C, A>();
    }
    if (promoted_b < 0 && promoted_a > (std::numeric_limits<C>::min() + promoted_b)) {
        return std::unsigned_integral<C> && std::is_same<C, A>();
    }
    return true;
}

template <std::integral A, std::integral B>
constexpr bool can_multiply_in_place_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_left_in_place_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_shift_right_in_place_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_and_in_place_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_xor_in_place_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_bitwise_or_in_place_modular(A a, B b) noexcept;

} // namespace boundary_conditons

} // namespace wjg

#endif