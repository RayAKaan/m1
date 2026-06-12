# Golden Output Catalog

Maps every `_test_*.c` golden file in `src/m1/` to its `.m1` source file in `tests/`.

| Stem | Source (.m1) | Inj file (lines) | Golden (.c) | Lines | Date | Temporal Ops |
|------|-------------|-------------------|-------------|-------|------|--------------|
| app | tests/module/app.m1 | 83 | _test_app.c | 7 | 2026-06-05 | none |
| bank | tests/module/bank.m1 | 87 | _test_bank.c | 402 | 2026-06-05 | now, when |
| calc | tests/functions/calc.m1 | 87 | _test_calc.c | 419 | 2026-06-05 | none |
| cycle_a | tests/module/cycle_a.m1 | 0 | _test_cycle_a.c | 0 | 2026-06-05 | none |
| cycle_b | tests/module/cycle_b.m1 | 0 | _test_cycle_b.c | 0 | 2026-06-05 | none |
| extern_test | tests/functions/extern_test.m1 | 82 | _test_extern_test.c | 395 | 2026-06-05 | none |
| fib | tests/algorithms/fib.m1 | 85 | _test_fib.c | 403 | 2026-06-05 | none |
| float_test | tests/floats/float_test.m1 | 84 | _test_float_test.c | 397 | 2026-06-05 | none |
| fn_test | tests/functions/fn_test.m1 | 82 | _test_fn_test.c | 402 | 2026-06-05 | none |
| freeze_readonly_test | tests/freeze/freeze_readonly_test.m1 | 86 | _test_freeze_readonly_test.c | 399 | 2026-06-05 | freeze |
| freeze_test | tests/freeze/freeze_test.m1 | 86 | _test_freeze_test.c | 398 | 2026-06-05 | freeze |
| frequency | tests/algorithms/frequency.m1 | 103 | _test_frequency.c | 410 | 2026-06-05 | none |
| lib | tests/module/lib.m1 | 81 | _test_lib.c | 393 | 2026-06-05 | none |
| map_test | tests/data_structures/map_test.m1 | 91 | _test_map_test.c | 396 | 2026-06-05 | none |
| match | tests/pattern_matching/match.m1 | 89 | _test_match.c | 403 | 2026-06-05 | none |
| math | tests/module/math.m1 | 80 | _test_math.c | 393 | 2026-06-05 | none |
| matrix_test | tests/data_structures/matrix_test.m1 | 93 | _test_matrix_test.c | 398 | 2026-06-05 | none |
| now_error_test | tests/now/now_error_test.m1 | 85 | _test_now_error_test.c | 398 | 2026-06-05 | now |
| now_mutation_test | tests/now/now_mutation_test.m1 | 86 | _test_now_mutation_test.c | 398 | 2026-06-05 | now |
| now_test | tests/now/now_test.m1 | 87 | _test_now_test.c | 398 | 2026-06-05 | now |
| phase_graph_simple_test | tests/phase_graph_simple_test.m1 | 86 | _test_phase_graph_simple_test.c | 399 | 2026-06-05 | none |
| records | tests/data_structures/records.m1 | 88 | _test_records.c | 413 | 2026-06-05 | none |
| sort_test | tests/sorting/sort_test.m1 | 93 | _test_sort_test.c | 398 | 2026-06-05 | none |
| stdlib_test | tests/stdlib/stdlib_test.m1 | 86 | _test_stdlib_test.c | 397 | 2026-06-05 | none |
| strings_test | tests/strings/strings_test.m1 | 91 | _test_strings_test.c | 399 | 2026-06-05 | none |
| task1_bank | tests/benchmark/task1_bank.m1 | 85 | _test_task1_bank.c | 396 | 2026-06-05 | now, when |
| task10_game | tests/benchmark/task10_game.m1 | 96 | _test_task10_game.c | 401 | 2026-06-05 | now, was, when |
| task2_order | tests/benchmark/task2_order.m1 | 94 | _test_task2_order.c | 400 | 2026-06-05 | was |
| task3_file | tests/benchmark/task3_file.m1 | 90 | _test_task3_file.c | 398 | 2026-06-05 | now, was, when, will |
| task4_session | tests/benchmark/task4_session.m1 | 94 | _test_task4_session.c | 399 | 2026-06-05 | freeze, now, was, when |
| task5_thermostat | tests/benchmark/task5_thermostat.m1 | 89 | _test_task5_thermostat.c | 396 | 2026-06-05 | now, when |
| task6_connection | tests/benchmark/task6_connection.m1 | 87 | _test_task6_connection.c | 398 | 2026-06-05 | when, will |
| task6_transaction | tests/benchmark/task6_transaction.m1 | 94 | _test_task6_transaction.c | 400 | 2026-06-05 | freeze, now, was, will |
| task7_cascade | tests/benchmark/task7_cascade.m1 | 87 | _test_task7_cascade.c | 398 | 2026-06-05 | when |
| task7_elevator | tests/benchmark/task7_elevator.m1 | 92 | _test_task7_elevator.c | 399 | 2026-06-05 | now, was, when |
| task8_inventory | tests/benchmark/task8_inventory.m1 | 89 | _test_task8_inventory.c | 396 | 2026-06-05 | now, when |
| task9_token | tests/benchmark/task9_token.m1 | 91 | _test_task9_token.c | 399 | 2026-06-05 | was, will |
| test_freeze_return | tests/benchmark/test_freeze_return.m1 | 84 | _test_test_freeze_return.c | 396 | 2026-06-05 | freeze, when |
| test_return | tests/benchmark/test_return.m1 | 87 | _test_test_return.c | 403 | 2026-06-05 | none |
| test_return2 | tests/benchmark/test_return2.m1 | 87 | _test_test_return2.c | 403 | 2026-06-05 | none |
| test_return3 | tests/benchmark/test_return3.m1 | 82 | _test_test_return3.c | 394 | 2026-06-05 | none |
| test_return4 | tests/benchmark/test_return4.m1 | 87 | _test_test_return4.c | 404 | 2026-06-05 | none |
| test_return_edge | tests/benchmark/test_return_edge.m1 | 90 | _test_test_return_edge.c | 404 | 2026-06-05 | none |
| test_simple_return | tests/benchmark/test_simple_return.m1 | 82 | _test_test_simple_return.c | 394 | 2026-06-05 | none |
| test_string | tests/stdlib/test_string.m1 | 89 | _test_test_string.c | 506 | 2026-06-05 | none |
| test_string2 | tests/stdlib/test_string2.m1 | 99 | _test_test_string2.c | 506 | 2026-06-05 | none |
| test_vector | tests/stdlib/test_vector.m1 | 97 | _test_test_vector.c | 497 | 2026-06-05 | none |
| test1_main | tests/module/test1_main.m1 | 82 | _test_test1_main.c | 7 | 2026-06-05 | none |
| test2_unqualified | tests/module/test2_unqualified.m1 | 82 | _test_test2_unqualified.c | 7 | 2026-06-05 | none |
| test3_cycle | tests/module/test3_cycle.m1 | 0 | _test_test3_cycle.c | 0 | 2026-06-05 | none |
| test4_missing | tests/module/test4_missing.m1 | 81 | _test_test4_missing.c | 7 | 2026-06-05 | none |
| test7_std | tests/module/test7_std.m1 | 82 | _test_test7_std.c | 463 | 2026-06-05 | none |
| test8_bank | tests/module/test8_bank.m1 | 84 | _test_test8_bank.c | 7 | 2026-06-05 | none |
| two_sum | tests/algorithms/two_sum.m1 | 100 | _test_two_sum.c | 417 | 2026-06-05 | none |
| vector_test | tests/data_structures/vector_test.m1 | 92 | _test_vector_test.c | 398 | 2026-06-05 | none |
| was_never_test | tests/was/was_never_test.m1 | 85 | _test_was_never_test.c | 398 | 2026-06-05 | was |
| was_test | tests/was/was_test.m1 | 86 | _test_was_test.c | 398 | 2026-06-05 | freeze, was |
| when_immediate_test | tests/when/when_immediate_test.m1 | 83 | _test_when_immediate_test.c | 396 | 2026-06-05 | when |
| when_never_test | tests/when/when_never_test.m1 | 84 | _test_when_never_test.c | 396 | 2026-06-05 | when |
| when_test | tests/when/when_test.m1 | 84 | _test_when_test.c | 396 | 2026-06-05 | when |
| will_error_test | tests/will/will_error_test.m1 | 84 | _test_will_error_test.c | 396 | 2026-06-05 | will |
| will_test | tests/will/will_test.m1 | 84 | _test_will_test.c | 396 | 2026-06-05 | will |
| wrapper_test | tests/functions/wrapper_test.m1 | 82 | _test_wrapper_test.c | 402 | 2026-06-05 | none |

**Summary**: 64 golden files, 22,799 total lines. 18 test files use temporal operators (freeze, now, was, when, will). 3 orphan 0-byte outputs (cycle tests).

**Gap**: A `_inj_freeze_error_compile_test.m1` (86 lines) exists but has NO corresponding `_test_*.c` output — the compiler rejects freeze assignment errors at compile time (consistent with Q4).
