# Implementation of P1619R2: Functions for Testing Boundary Conditions on Integer Operations
[![Unit tests (GCC 14 - debug)](https://github.com/wjgra/int-boundary-conditions/actions/workflows/unit_tests_debug.yml/badge.svg)](https://github.com/wjgra/int-boundary-conditions/actions/workflows/unit_tests_debug.yml) [![Unit tests (GCC 14 - release)](https://github.com/wjgra/int-boundary-conditions/actions/workflows/unit_tests_release.yml/badge.svg)](https://github.com/wjgra/int-boundary-conditions/actions/workflows/unit_tests_release.yml) [![clang-format](https://github.com/wjgra/int-boundary-conditions/actions/workflows/format.yml/badge.svg)](https://github.com/wjgra/int-boundary-conditions/actions/workflows/format.yml)

C++ proposal paper [PR1619R2](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p1619r2.pdf) describes a set of library functions that indicate whether arithmetic expressions on integers match the corresponding mathematical statement. For instance, C++'s addition of signed integers matches 'mathematical' addition over the set of integers if and only if there is no over/underflow.

This seems like an interesting proposal to help navigate some of the more difficult edge cases of the language but, as of April 2025, there does not appear to be a public implementation. The goal of this repo is to get a basic cross-platform implementation in place and to start to think about how the code generation can be optimised.

Note that this proposal takes a somewhat different approach to, say, C23's checked arithmetic (proposed for inclusion in C++ in [PR3370R0](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2024/p3370r0.html)) or [the Boost equivalent](https://live.boost.org/doc/libs/1_81_0/libs/safe_numerics/doc/html/checked_arithmetic.html). Whilst those solutions perform the operation in question and return an error code in the case that the operation does not agree with the mathetical equivalent, this proposal instead takes the form of boolean predicates that indicate whether the operation, if performed, would agree with the 'real answer'. One advantage of this approach is the suitability for inclusion in assertions or C++26 contracts.

On balance, I think there is probably space for both 'check-after' and 'check-before' additions to the standard library, though I do not have strong feelings (yet!) as to how these should best be implemented. Nonetheless, I thought that implementing this proposal would be a productive exercise irrespective of how useful it actually ends up being.

## Implementation status

| Function | Implemented? | Notes |
| -------- | ------------ | ----- |
| can_convert | ✅ | Trivial range check using the result type.
| can_convert_modular | ✅ | Always true (since C++20).
| can_increment | ✅ |
| can_decrement | ✅ |
| can_promote | ✅ | Trivial range check using the promoted type. On most platforms, this reduces to `return true`, but there are some tricky cases where integers have unusual numbers padding bits (see the proposal paper for an example).
| can_negate | ✅ | [This excerpt](https://en.cppreference.com/w/cpp/language/operator_arithmetic#:~:text=The%20result%20of%20the%20built%2Din%20negation,is%20the%20number%20of%20bits%20after%20promotion.) from cppreference seems to be inaccurate - the second sentence should probably read *"~~For unsigned a~~ <ins>If the type of a (possibly after promotion) is unsigned</ins>, the value of -a is 2^N - 1, where N is the number of bits after promotion"*. It would be worth checking what the standard says! 
| can_bitwise_not | ❌ |
| can_increment_modular | ✅ |
| can_decrement_modular | ✅ |
| can_promote_modular | ❌ |
| can_negate_modular | ❌ |
| can_bitwise_not_modular | ❌ |
| can_add | ✅ | Makes use of the [`__builtin_add_overflow_p` intrinsic](https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html) if available, which seems to be well-optimised on GCC. Otherwise the promotions, conversions and bounds checks are performed explicitly (further work is required to improve the code generation here). An alternative approach modelled on the description of this intrinsic would be to convert to a large int type to perform the calculation then cast back to the result type to check agreement.
| can_subtract | ✅ | Similar considerations as for `can_add`.
| can_multiply | ❌ |
| can_divide | ❌ |
| can_take_remainder | ❌ |
| can_shift_left | ❌ |
| can_shift_right | ❌ |
| can_bitwise_and | ❌ |
| can_bitwise_xor | ❌ |
| can_bitwise_or | ❌ |
| can_compare | ❌ |
| can_add_modular | ❌ |
| can_subtract_modular | ❌ |
| can_multiply_modular | ❌ |
| can_shift_left_modular | ❌ |
| can_shift_right_modular | ❌ |
| can_bitwise_and_modular | ❌ |
| can_bitwise_xor_modular | ❌ |
| can_bitwise_or_modular | ❌ |
| can_add_in_place | ✅ |
| can_subtract_in_place | ✅ |
| can_multiply_in_place | ❌ |
| can_divide_in_place | ❌ |
| can_take_remainder_in_place | ❌ |
| can_shift_left_in_place | ❌ |
| can_shift_right_in_place | ❌ |
| can_bitwise_and_in_place | ❌ |
| can_bitwise_xor_in_place | ❌ |
| can_bitwise_or_in_place | ❌ |
| can_add_in_place_modular | ✅ |
| can_subtract_in_place_modular | ✅ |
| can_multiply_in_place_modular | ❌ |
| can_shift_left_in_place_modular | ❌ |
| can_shift_right_in_place_modular | ❌ |
| can_bitwise_and_in_place_modular | ❌ |
| can_bitwise_xor_in_place_modular | ❌ |
| can_bitwise_or_in_place_modular | ❌ |
