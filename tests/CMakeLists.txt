# MUT for can_promote
add_executable(can_promote_test can_promote_test.cpp)
target_link_libraries(can_promote_test PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(can_promote_test)

# MUT for can_add
add_executable(can_add_test can_add_test.cpp)
target_link_libraries(can_add_test PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(can_add_test)
