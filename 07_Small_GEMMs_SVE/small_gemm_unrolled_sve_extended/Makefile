BUILD_DIR = ./build

gemm_asm_sve: driver_gemm_asm_sve.cpp
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -g -c gemm_asm_sve_128_6_48.s -o ${BUILD_DIR}/gemm_asm_sve_128_6_48.o
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -g -c gemm_asm_sve_128_48_48.s -o ${BUILD_DIR}/gemm_asm_sve_128_48_48.o
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -g -c gemm_asm_sve_63_6_48.s -o ${BUILD_DIR}/gemm_asm_sve_63_6_48.o
		g++ -pedantic -Wall -Wextra -Werror -g driver_gemm_asm_sve.cpp  ${BUILD_DIR}/gemm_asm_sve_128_6_48.o ${BUILD_DIR}/gemm_asm_sve_128_48_48.o ${BUILD_DIR}/gemm_asm_sve_63_6_48.o -o ${BUILD_DIR}/gemm_asm_sve

all: gemm_asm_sve

$(shell mkdir -p build)