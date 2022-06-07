BUILD_DIR = ./build

sve2: driver.cpp fmlalx.s eor3.s
	clang -Wall -Wextra -Werror -march=armv8-a+sve2 -g -c fmlalx.s -o ${BUILD_DIR}/fmlalx.o
	clang -Wall -Wextra -Werror -march=armv8-a+sve2 -g -c eor3.s -o ${BUILD_DIR}/eor3.o
	clang++ -Wall -Wextra -g driver.cpp ${BUILD_DIR}/fmlalx.o ${BUILD_DIR}/eor3.o -o ${BUILD_DIR}/sve2
	#gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve2 -g -c fmlalb_fmlalt.s -o ${BUILD_DIR}/fmlalb_fmlalt.o
	#gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve2 -g -c eor3.s -o ${BUILD_DIR}/eor3.o
	#g++ -pedantic -Wall -Wextra -g driver.cpp ${BUILD_DIR}/fmlalb_fmlalt.o ${BUILD_DIR}/eor3.o -o ${BUILD_DIR}/sve2

all: sve2


clean:
	rm -rf ${BUILD_DIR}

$(shell mkdir -p build)
