#ifndef _WJG_BOUNDARY_CONDITIONS_HPP_
#define _WJG_BOUNDARY_CONDITIONS_HPP_

#include <concepts>
#include <cstdint>
#include <limits>

namespace wjg {

template <class R, class A>
constexpr bool can_convert(A a) noexcept;

template <class R, class A>
constexpr bool can_convert_modular(A a) noexcept;

template <class A>
constexpr bool can_increment(A a) noexcept;

template <class A>
constexpr bool can_decrement(A a) noexcept;

template <class A>
constexpr bool can_promote(A a) noexcept;

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

namespace internal {
#if defined __has_builtin && __has_builtin(__builtin_add_overflow_p)
constexpr bool has_builtin_add_overflow_p = true;
#else
constexpr bool has_builtin_add_overflow_p = false;
#endif
} // namespace internal
} // namespace wjg

/* wjg::can_add() template specialisations */

// Specialisation for two unsigned integers of the same type.
template <std::unsigned_integral T>
constexpr bool wjg::can_add(const T a, const T b) noexcept
{
    if constexpr (wjg::internal::has_builtin_add_overflow_p) {
        return __builtin_add_overflow_p(a, b, static_cast<T>(0)) == false;
    }
    else {
        return b <= std::numeric_limits<T>::max() - a;
    }
}

// To implement: two unsigned integers of different widths (wid A < wid B and wid B < wid A)

#endif