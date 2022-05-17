BUILD_DIR = ./build

#braucht man bugs?
bugs: driver_bugs.cpp load_asm.s
		gcc -pedantic -Wall -Wextra -Werror -g -c driver_bugs.s -o ${BUILD_DIR}/driver_bugs.o
		g++ -pedantic -Wall -Wextra -Werror -g driver_bugs.cpp  ${BUILD_DIR}/driver_bugs.o -o ${BUILD_DIR}/driver_bugs


gemm_asm_gp: driver_gemm_asm_gp.cpp gemm_asm_gp.s
		gcc -pedantic -Wall -Wextra -Werror -g -c gemm_asm_gp.s -o ${BUILD_DIR}/gemm_asm_gp.o
		g++ -pedantic -Wall -Wextra -Werror -g driver_gemm_asm_gp.cpp  ${BUILD_DIR}/gemm_asm_gp.o -o ${BUILD_DIR}/gemm_asm_gp

all: bugs gemm_asm_gp

$(shell mkdir -p build)