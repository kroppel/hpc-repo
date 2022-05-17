BUILD_DIR = ./build

copy_data: driver_copy.cpp copy.c
		gcc -pedantic -Wall -Wextra -Werror -c copy.c -o ${BUILD_DIR}/copy.o
		gcc -pedantic -Wall -Wextra -Werror -c copy_asm.s -o ${BUILD_DIR}/copy_asm.o
		g++ -pedantic -Wall -Wextra -Werror -O2 driver_copy.cpp ${BUILD_DIR}/copy.o ${BUILD_DIR}/copy_asm.o -o ${BUILD_DIR}/copy

all: copy_data

$(shell mkdir -p build)