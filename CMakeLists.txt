cmake_minimum_required (VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
project(log_parser)

set(SOURCES
        src/log_parser.cpp
        )

add_library(log_parser ${SOURCES})
target_include_directories(log_parser PUBLIC include)

add_executable(main src/main.cpp)
target_link_libraries(main log_parser)

enable_testing()

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(
  log_parser_test
  test/log_parser_tests.cpp
)

target_link_libraries(log_parser_test
 PRIVATE
  GTest::GTest
  log_parser)

add_test(log_parser_gtests log_parser_test)
