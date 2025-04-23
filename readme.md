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
| can_convert | not implemented | not implemented |
| can_convert_modular | not implemented | not implemented |
| can_increment | not implemented | not implemented |
| can_decrement | not implemented | not implemented |
| can_promote | not implemented | not implemented |
| can_negate | not implemented | not implemented |
| can_bitwise_not | not implemented | not implemented |
| can_increment_modular | not implemented | not implemented |
| can_decrement_modular | not implemented | not implemented |
| can_promote_modular | not implemented | not implemented |
| can_negate_modular | not implemented | not implemented |
| can_bitwise_not_modular | not implemented | not implemented |

Function templates with two parameters:
| Function | \<unsigned, unsigned\> | \<signed, signed\> | \<signed, unsigned\> | \<unsigned, signed\> |
| -------- | ---------------------- | ------------------ | -------------------- | -------------------- |
| can_add | not implemented | not implemented | not implemented | not implemented |
| can_subtract | not implemented | not implemented | not implemented | not implemented |
| can_multiply | not implemented | not implemented | not implemented | not implemented |
| can_divide | not implemented | not implemented | not implemented | not implemented |
| can_take_remainder | not implemented | not implemented | not implemented | not implemented |
| can_shift_left | not implemented | not implemented | not implemented | not implemented |
| can_shift_right | not implemented | not implemented | not implemented | not implemented |
| can_bitwise_and | not implemented | not implemented | not implemented | not implemented |
| can_bitwise_xor | not implemented | not implemented | not implemented | not implemented |
| can_bitwise_or | not implemented | not implemented | not implemented | not implemented |
| can_compare | not implemented | not implemented | not implemented | not implemented |
| can_add_modular | not implemented | not implemented | not implemented | not implemented |
| can_subtract_modular | not implemented | not implemented | not implemented | not implemented |
| can_multiply_modular | not implemented | not implemented | not implemented | not implemented |
| can_shift_left_modular | not implemented | not implemented | not implemented | not implemented |
| can_shift_right_modular | not implemented | not implemented | not implemented | not implemented |
| can_bitwise_and_modular | not implemented | not implemented | not implemented | not implemented |
| can_bitwise_xor_modular | not implemented | not implemented | not implemented | not implemented |
| can_bitwise_or_modular | not implemented | not implemented | not implemented | not implemented |
| can_add_in_place | not implemented | not implemented | not implemented | not implemented |
| can_subtract_in_place | not implemented | not implemented | not implemented | not implemented |
| can_multiply_in_place | not implemented | not implemented | not implemented | not implemented |
| can_divide_in_place | not implemented | not implemented | not implemented | not implemented |
| can_take_remainder_in_place | not implemented | not implemented | not implemented | not implemented |
| can_shift_left_in_place | not implemented | not implemented | not implemented | not implemented |
| can_shift_right_in_place | not implemented | not implemented | not implemented | not implemented |
| can_bitwise_and_in_place | not implemented | not implemented | not implemented | not implemented |
| can_bitwise_xor_in_place | not implemented | not implemented | not implemented | not implemented |
| can_bitwise_or_in_place | not implemented | not implemented | not implemented | not implemented |
| can_add_in_place_modular | not implemented | not implemented | not implemented | not implemented |
| can_subtract_in_place_modular | not implemented | not implemented | not implemented | not implemented |
| can_multiply_in_place_modular | not implemented | not implemented | not implemented | not implemented |
| can_shift_left_in_place_modular | not implemented | not implemented | not implemented | not implemented |
| can_shift_right_in_place_modular | not implemented | not implemented | not implemented | not implemented |
| can_bitwise_and_in_place_modular | not implemented | not implemented | not implemented | not implemented |
| can_bitwise_xor_in_place_modular | not implemented | not implemented | not implemented | not implemented |
| can_bitwise_or_in_place_modular | not implemented | not implemented | not implemented | not implemented |
