cmake_minimum_required(VERSION 3.22.1)

project(int-boundary-conditions LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_TESTS "Enable tests" ON)

add_compile_options(-Wall -Wextra -Wpedantic -Werror -O2)

find_package(Catch2 3 REQUIRED)
include(CTest)
include(Catch)

include_directories(include)
add_subdirectory(tests)
