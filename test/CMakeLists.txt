cmake_minimum_required(VERSION 3.20)

add_executable(
  test_math
  test_math.cpp
)

target_link_libraries(
  test_math
  portal
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_math)