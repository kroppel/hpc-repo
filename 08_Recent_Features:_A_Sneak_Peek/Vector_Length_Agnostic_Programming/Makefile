BUILD_DIR = ./build

gemm_asm_sve: driver_triad.cpp
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -g -c triad_low_sve_agnostic.s -o ${BUILD_DIR}/triad_low_sve_agnostic.o
		g++ -pedantic -Wall -Wextra -Werror -g driver_triad.cpp triad_high.h  ${BUILD_DIR}/triad_low_sve_agnostic.o -o ${BUILD_DIR}/triad

all: triad

$(shell mkdir -p build)