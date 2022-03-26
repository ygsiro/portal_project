cmake_minimum_required(VERSION 3.20)

project(portal
  VERSION 0.1.0
  LANGUAGES CXX
)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        e2239ee6043f73722e7aa812a459f54a28552929 # release-1.11.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(portal INTERFACE)

target_compile_features(portal INTERFACE cxx_std_20)

target_compile_options(portal INTERFACE
  $<$<CXX_COMPILER_ID:MSVC>: /utf-8 /W4 /permissive>
)

target_include_directories(portal INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(test)
add_subdirectory(source)