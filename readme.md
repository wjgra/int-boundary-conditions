# Implementation of P1619R2: Functions for Testing Boundary Conditions on Integer Operations
As of April 2025, P1619R2 does not currently have a public implementation. This repo seeks to address this deficiency.

## Background (TBC)
To discuss:
- the proposal paper
- C: chk_add etc.
- any similar libraries that exist
- the importance of optimal code generation

## Implementation status
Function templates with one parameter:
| Function | \<unsigned\> | \<signed\> | 
| -------- | ------------ | ---------- |
| can_convert | ❌ | ❌ |
| can_convert_modular | ❌ | ❌ |
| can_increment | ✅ | ✅ |
| can_decrement | ✅ | ✅ |
| can_promote | ❌ | ❌ |
| can_negate | ❌ | ❌ |
| can_bitwise_not | ❌ | ❌ |
| can_increment_modular | ❌ | ❌ |
| can_decrement_modular | ❌ | ❌ |
| can_promote_modular | ❌ | ❌ |
| can_negate_modular | ❌ | ❌ |
| can_bitwise_not_modular | ❌ | ❌ |

Function templates with two parameters:
| Function | \<unsigned, unsigned\> | \<signed, signed\> | \<signed, unsigned\> | \<unsigned, signed\> |
| -------- | ---------------------- | ------------------ | -------------------- | -------------------- |
| can_add | ❌ | ❌ | ❌ | ❌ |
| can_subtract | ❌ | ❌ | ❌ | ❌ |
| can_multiply | ❌ | ❌ | ❌ | ❌ |
| can_divide | ❌ | ❌ | ❌ | ❌ |
| can_take_remainder | ❌ | ❌ | ❌ | ❌ |
| can_shift_left | ❌ | ❌ | ❌ | ❌ |
| can_shift_right | ❌ | ❌ | ❌ | ❌ |
| can_bitwise_and | ❌ | ❌ | ❌ | ❌ |
| can_bitwise_xor | ❌ | ❌ | ❌ | ❌ |
| can_bitwise_or | ❌ | ❌ | ❌ | ❌ |
| can_compare | ❌ | ❌ | ❌ | ❌ |
| can_add_modular | ❌ | ❌ | ❌ | ❌ |
| can_subtract_modular | ❌ | ❌ | ❌ | ❌ |
| can_multiply_modular | ❌ | ❌ | ❌ | ❌ |
| can_shift_left_modular | ❌ | ❌ | ❌ | ❌ |
| can_shift_right_modular | ❌ | ❌ | ❌ | ❌ |
| can_bitwise_and_modular | ❌ | ❌ | ❌ | ❌ |
| can_bitwise_xor_modular | ❌ | ❌ | ❌ | ❌ |
| can_bitwise_or_modular | ❌ | ❌ | ❌ | ❌ |
| can_add_in_place | ❌ | ❌ | ❌ | ❌ |
| can_subtract_in_place | ❌ | ❌ | ❌ | ❌ |
| can_multiply_in_place | ❌ | ❌ | ❌ | ❌ |
| can_divide_in_place | ❌ | ❌ | ❌ | ❌ |
| can_take_remainder_in_place | ❌ | ❌ | ❌ | ❌ |
| can_shift_left_in_place | ❌ | ❌ | ❌ | ❌ |
| can_shift_right_in_place | ❌ | ❌ | ❌ | ❌ |
| can_bitwise_and_in_place | ❌ | ❌ | ❌ | ❌ |
| can_bitwise_xor_in_place | ❌ | ❌ | ❌ | ❌ |
| can_bitwise_or_in_place | ❌ | ❌ | ❌ | ❌ |
| can_add_in_place_modular | ❌ | ❌ | ❌ | ❌ |
| can_subtract_in_place_modular | ❌ | ❌ | ❌ | ❌ |
| can_multiply_in_place_modular | ❌ | ❌ | ❌ | ❌ |
| can_shift_left_in_place_modular | ❌ | ❌ | ❌ | ❌ |
| can_shift_right_in_place_modular | ❌ | ❌ | ❌ | ❌ |
| can_bitwise_and_in_place_modular | ❌ | ❌ | ❌ | ❌ |
| can_bitwise_xor_in_place_modular | ❌ | ❌ | ❌ | ❌ |
| can_bitwise_or_in_place_modular | ❌ | ❌ | ❌ | ❌ |
