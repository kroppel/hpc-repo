cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(small-gemms LANGUAGES CXX)

# search for OpenMP, REQUIRED -> fatal error if not found
find_package(OpenMP REQUIRED)

# add an interface library -> does not generate build output by itself
add_library(small-gemms-lib STATIC include/gemm-ref.h src/gemm-ref.cpp)

target_include_directories(small-gemms-lib PUBLIC include PUBLIC src)

add_executable(small-gemms-driver include/gemm-ref.h src/driver-small-gemms.cpp)
target_link_libraries(small-gemms-driver PUBLIC small-gemms-lib PUBLIC OpenMP::OpenMP_CXX)