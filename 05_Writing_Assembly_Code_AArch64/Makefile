BUILD_DIR = ./build

load_store_example: driver.cpp load_store_example.s
		gcc -pedantic -Wall -Wextra -Werror -c load_store_example.s -o ${BUILD_DIR}/load_store_example.o
		g++ -pedantic -Wall -Wextra -Werror -O2 -fopenmp driver.cpp  ${BUILD_DIR}/load_store_example.o -o ${BUILD_DIR}/load_store_example

all: load_store_example

$(shell mkdir -p build)