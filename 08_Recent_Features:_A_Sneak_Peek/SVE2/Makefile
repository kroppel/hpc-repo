BUILD_DIR = ./build

sve2: driver.cpp fmlalb.s
	gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -g -c fmlalb.s -o ${BUILD_DIR}/fmlalb.o
	g++ -pedantic -Wall -Wextra -g driver.cpp ${BUILD_DIR}/fmlalb.o -o ${BUILD_DIR}/sve2

all: sve2


clean:
	rm -rf ${BUILD_DIR}

$(shell mkdir -p build)
