cmake_minimum_required (VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
project(log_parser)

set(SOURCES
        src/log_parser.cpp
        )

add_library(log_parser ${SOURCES})
target_include_directories(log_parser PUBLIC include)

add_executable(main src/main.cpp)
target_link_libraries(main log_parser)