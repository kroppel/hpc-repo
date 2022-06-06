BUILD_DIR = ./build

triad: driver_triad.cpp triad_low_sve_agnostic.s triad_high.cpp triad_high.h
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -g -c triad_low_sve_agnostic.s -o ${BUILD_DIR}/triad_low_sve_agnostic.o
		g++ -pedantic -Wall -Wextra -g driver_triad.cpp triad_high.cpp ${BUILD_DIR}/triad_low_sve_agnostic.o -o ${BUILD_DIR}/triad

all: triad

clean:
	rm -rf build

$(shell mkdir -p build)