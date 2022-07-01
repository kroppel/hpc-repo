BUILD_DIR = ./build

load: driver.cpp load.s
		gcc -pedantic -Wall -Wextra -Werror -c -g load.s -o ${BUILD_DIR}/load.o
		g++ -pedantic -Wall -Wextra -Werror -O2 -g driver.cpp  ${BUILD_DIR}/load.o -o ${BUILD_DIR}/load

all: load

$(shell mkdir -p build)
