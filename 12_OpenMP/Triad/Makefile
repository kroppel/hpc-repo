BUILD_DIR = ./build

BUILD_OPTIONS=-g -pedantic -Wall -Wextra -Werror -O2 -fopenmp -march=native

triad: driver.cpp kernels/triad.cpp
	${CXX} ${BUILD_OPTIONS} ${BUILD_OPT_REPORT} -c kernels/triad.cpp -o ${BUILD_DIR}/kernels/triad.o
	${CXX} ${BUILD_OPTIONS} driver.cpp ${BUILD_DIR}/kernels/triad.o -o ${BUILD_DIR}/triad

$(shell mkdir -p build)
$(shell mkdir -p build/kernels)
