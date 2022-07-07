BUILD_DIR = ./build

BUILD_OPTIONS=-g -pedantic -Wall -Wextra -O2 -fopenmp -march=native

triad_offloading: driver.cpp kernels/triad_offloading.cpp
	${CXX} ${BUILD_OPTIONS} -c kernels/triad_offloading.cpp -o ${BUILD_DIR}/kernels/triad_offloading.o
	${CXX} ${BUILD_OPTIONS} driver.cpp ${BUILD_DIR}/kernels/triad_offloading.o -o ${BUILD_DIR}/triad_offloading

$(shell mkdir -p build)
$(shell mkdir -p build/kernels)
