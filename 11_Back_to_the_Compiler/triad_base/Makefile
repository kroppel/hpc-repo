BUILD_DIR = ./build

BUILD_OPTIONS=-g -pedantic -Wall -Wextra -Werror -O2 -fopenmp -march=armv8-a+sve
ifeq ($(CXX),g++)
BUILD_OPT_REPORT=-ftree-vectorize -fopt-info-vec-all
endif
ifeq ($(CXX),clang++)
BUILD_OPT_REPORT=-Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize
endif

gemm_asm_sve: driver.cpp
	${CXX} ${BUILD_OPTIONS} ${BUILD_OPT_REPORT} -c kernels/triad_non_vectorizable.cpp -o ${BUILD_DIR}/kernels/triad_non_vectorizable.o
	${CXX} ${BUILD_OPTIONS} driver.cpp ${BUILD_DIR}/kernels/triad_non_vectorizable.o -o ${BUILD_DIR}/auto_vec

$(shell mkdir -p build)
$(shell mkdir -p build/kernels)
