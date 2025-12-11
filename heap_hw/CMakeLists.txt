cmake_minimum_required(VERSION 3.14)
project(heap_hw)

set(CMAKE_CXX_STANDARD 17)


#   Библиотека heap (header-only)

add_library(heap INTERFACE)
target_include_directories(heap INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


#   main

add_executable(main main.cpp)
target_link_libraries(main PRIVATE heap)


#       Т Е С Т Ы

enable_testing()

find_package(GTest REQUIRED)

add_executable(tests tests/tests.cpp)
target_link_libraries(tests PRIVATE heap GTest::gtest GTest::gtest_main)

add_test(NAME BasicHeapTest COMMAND tests)
