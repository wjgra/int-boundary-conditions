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

template <std::integral R, std::integral A>
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

template <std::integral A>
constexpr bool can_negate(A a) noexcept;

template <std::integral A>
constexpr bool can_bitwise_not(A a) noexcept;

template <std::integral A>
constexpr bool can_increment_modular(A a) noexcept;

template <std::integral A>
constexpr bool can_decrement_modular(A a) noexcept;

template <std::integral A>
constexpr bool can_promote_modular(A a) noexcept;

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

    using C = internal::common_type<A, B>::name;

    if (!can_promote(a) || !can_promote(b)) {
        return false;
    }

    // Get the values of a and b after integer promotion and usual arithmetic conversion.
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

    using C = internal::common_type<A, B>::name;

    if (!can_promote(a) || !can_promote(b)) {
        return false;
    }

    // Get the values of a and b after integer promotion and usual arithmetic conversion.
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

template <std::integral A, std::integral B>
constexpr bool can_add_in_place_modular(A a, B b) noexcept;

template <std::integral A, std::integral B>
constexpr bool can_subtract_in_place_modular(A a, B b) noexcept;

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