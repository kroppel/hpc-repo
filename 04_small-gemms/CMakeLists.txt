cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(build_and_test LANGUAGES CXX)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
            "Choose the type of build, options are: Debug Release
RelWithDebInfo MinSizeRel."
            FORCE)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories for testing
add_subdirectory(catch)
add_subdirectory(test)
add_subdirectory(small-gemms)

enable_testing()
add_test(NAME MY-TEST COMMAND small-gemms-tests)
