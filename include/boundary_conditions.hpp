#ifndef _WJG_BOUNDARY_CONDITIONS_HPP_
#define _WJG_BOUNDARY_CONDITIONS_HPP_

namespace wjg
{
template <class R, class A> constexpr bool can_convert( A a ) noexcept;
template <class R, class A> constexpr bool can_convert_modular( A a ) noexcept;
template <class A> constexpr bool can_increment( A a ) noexcept;
template <class A> constexpr bool can_decrement( A a ) noexcept;
template <class A> constexpr bool can_promote( A a ) noexcept;
template <class A> constexpr bool can_negate( A a ) noexcept;
template <class A> constexpr bool can_bitwise_not( A a ) noexcept;
template <class A> constexpr bool can_increment_modular( A a ) noexcept;
template <class A> constexpr bool can_decrement_modular( A a ) noexcept;
template <class A> constexpr bool can_promote_modular( A a ) noexcept;
template <class A> constexpr bool can_negate_modular( A a ) noexcept;
template <class A> constexpr bool can_bitwise_not_modular( A a ) noexcept;
template <class A, class B> constexpr bool can_add(A a, B b) noexcept;
template <class A, class B> constexpr bool can_subtract(A a, B b) noexcept;
template <class A, class B> constexpr bool can_multiply(A a, B b) noexcept;
template <class A, class B> constexpr bool can_divide(A a, B b) noexcept;
template <class A, class B> constexpr bool can_take_remainder(A a, B b) noexcept;
template <class A, class B> constexpr bool can_shift_left(A a, B b) noexcept;
template <class A, class B> constexpr bool can_shift_right(A a, B b) noexcept;
template <class A, class B> constexpr bool can_bitwise_and(A a, B b) noexcept;
template <class A, class B> constexpr bool can_bitwise_xor(A a, B b) noexcept;
template <class A, class B> constexpr bool can_bitwise_or(A a, B b) noexcept;
template <class A, class B> constexpr bool can_compare(A a, B b) noexcept;
template <class A, class B> constexpr bool can_add_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_subtract_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_multiply_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_shift_left_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_shift_right_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_bitwise_and_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_bitwise_xor_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_bitwise_or_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_add_in_place(A a, B b) noexcept;
template <class A, class B> constexpr bool can_subtract_in_place(A a, B b) noexcept;
template <class A, class B> constexpr bool can_multiply_in_place(A a, B b) noexcept;
template <class A, class B> constexpr bool can_divide_in_place(A a, B b) noexcept;
template <class A, class B> constexpr bool can_take_remainder_in_place(A a, B b) noexcept;
template <class A, class B> constexpr bool can_shift_left_in_place(A a, B b) noexcept;
template <class A, class B> constexpr bool can_shift_right_in_place(A a, B b) noexcept;
template <class A, class B> constexpr bool can_bitwise_and_in_place(A a, B b) noexcept;
template <class A, class B> constexpr bool can_bitwise_xor_in_place(A a, B b) noexcept;
template <class A, class B> constexpr bool can_bitwise_or_in_place(A a, B b) noexcept;
template <class A, class B> constexpr bool can_add_in_place_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_subtract_in_place_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_multiply_in_place_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_shift_left_in_place_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_shift_right_in_place_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_bitwise_and_in_place_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_bitwise_xor_in_place_modular(A a, B b) noexcept;
template <class A, class B> constexpr bool can_bitwise_or_in_place_modular(A a, B b) noexcept;
}
#endif