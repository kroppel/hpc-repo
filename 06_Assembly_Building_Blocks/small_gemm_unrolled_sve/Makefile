BUILD_DIR = ./build

gemm_asm_sve: driver_gemm_asm_sve.cpp gemm_asm_sve_64_6_1.s
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -g -c gemm_asm_sve_64_6_1.s -o ${BUILD_DIR}/gemm_asm_sve_64_6_1.o
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -g -c gemm_asm_sve_64_6_1_opt.s -o ${BUILD_DIR}/gemm_asm_sve_64_6_1_opt.o
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -g -c gemm_asm_sve_64_6_48.s -o ${BUILD_DIR}/gemm_asm_sve_64_6_48.o
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -g -c gemm_asm_sve_64_6_48_opt.s -o ${BUILD_DIR}/gemm_asm_sve_64_6_48_opt.o
		g++ -pedantic -Wall -Wextra -Werror -g driver_gemm_asm_sve.cpp  ${BUILD_DIR}/gemm_asm_sve_64_6_1.o ${BUILD_DIR}/gemm_asm_sve_64_6_48.o ${BUILD_DIR}/gemm_asm_sve_64_6_1_opt.o ${BUILD_DIR}/gemm_asm_sve_64_6_48_opt.o -o ${BUILD_DIR}/gemm_asm_sve

all: gemm_asm_sve

$(shell mkdir -p build)