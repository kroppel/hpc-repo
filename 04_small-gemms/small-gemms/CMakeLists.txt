cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(small-gemms LANGUAGES CXX)

# add an interface library -> does not generate build output by itself
add_library(small-gemms-lib STATIC include/gemm-ref.h src/gemm-ref.cpp include/gemm_compiler_32_32_32_32_32_32.h src/gemm_compiler_32_32_32_32_32_32.cpp)
target_compile_options(small-gemms-lib PRIVATE -O3)
target_include_directories(small-gemms-lib PUBLIC include PUBLIC src)

add_executable(small-gemms-driver include/gemm-ref.h src/driver-small-gemms.cpp include/gemm_compiler_32_32_32_32_32_32.h)
target_compile_options(small-gemms-driver PRIVATE -O3)
target_link_libraries(small-gemms-driver PUBLIC small-gemms-lib)