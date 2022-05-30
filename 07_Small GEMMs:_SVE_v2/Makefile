BUILD_DIR = ./build

gemm_asm_sve: driver.cpp kernels/gemm_ref.cpp kernels/gemm_asm_sve_64_6_1.s kernels/gemm_asm_sve_128_6_48.s
		g++ -g -pedantic -Wall -Wextra -Werror -O2 -c kernels/gemm_ref.cpp -o ${BUILD_DIR}/gemm_ref.o
		gcc -g -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c kernels/gemm_asm_sve_64_6_1.s -o ${BUILD_DIR}/gemm_asm_sve_64_6_1.o
		gcc -g -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c kernels/gemm_asm_sve_128_6_48.s -o ${BUILD_DIR}/gemm_asm_sve_128_6_48.o
		g++ -g -pedantic -Wall -Wextra -Werror driver.cpp ${BUILD_DIR}/gemm_ref.o ${BUILD_DIR}/gemm_asm_sve_64_6_1.o ${BUILD_DIR}/gemm_asm_sve_128_6_48.o -o ${BUILD_DIR}/gemm_asm_sve
$(shell mkdir -p build)
