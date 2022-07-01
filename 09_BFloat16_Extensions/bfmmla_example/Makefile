BUILD_DIR = ./build

bfmmla_example: driver_bfmmla_example.cpp bfmmla_example.s
		clang -Wall -Wextra -Werror -march=armv8-a+sve+bf16 -c bfmmla_example.s -o ${BUILD_DIR}/bfmmla_example.o
		clang++ -Wall -Wextra -Werror -march=armv8-a+sve+bf16 driver_bfmmla_example.cpp ${BUILD_DIR}/bfmmla_example.o -o ${BUILD_DIR}/bfmmla_example

all: bfmmla_example

clean:
	rm -rf ${BUILD_DIR}

$(shell mkdir -p build)
