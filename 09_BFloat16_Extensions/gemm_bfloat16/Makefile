BUILD_DIR = ./build

gemm_bfloat16: driver_gemm_bfloat16.cpp
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve+bf16 -g -c gemm_bfloat16.s -o ${BUILD_DIR}/gemm_bfloat16.o
		g++ -pedantic -Wall -Wextra -Werror -g -march=armv8-a+sve+bf16 driver_gemm_bfloat16.cpp  ${BUILD_DIR}/gemm_bfloat16.o -o ${BUILD_DIR}/gemm_bfloat16

all: gemm_bfloat16

$(shell mkdir -p build)
