cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(my-test LANGUAGES CXX)

message(${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(small-gemms-tests main.cpp small-gemms-tests.cpp)

target_link_libraries(small-gemms-tests PRIVATE small-gemms-lib PRIVATE catch)