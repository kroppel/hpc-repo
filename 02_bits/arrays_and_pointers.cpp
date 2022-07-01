#include <cstdlib>
#include <iostream>

int main() {
    // Print data type sizes
    std::cout << "Size of unsigned char: " << sizeof(unsigned char) << "\n";
    std::cout << "Size of char: " << sizeof(char) << "\n";
    std::cout << "Size of unsigned int: " << sizeof(unsigned int) << "\n";
    std::cout << "Size of int : " << sizeof(int) << "\n";
    std::cout << "Size of float: " << sizeof(float) << "\n";
    std::cout << "Size of double: " << sizeof(double) << "\n";

    std::cout << "Size of unsigned int pointer: " << sizeof(unsigned int*) << "\n";
    std::cout << "Size of float pointer: " << sizeof(float*) << "\n";


    int* array = (int*) malloc(1500*sizeof(int));
    for (int i = 0; i < 1500; i++) {
        array[i]=3*i;
    }
    std::cout << "Value at position 500: " << *(array+500) << "\n";
    std::cout << "Adress of element at position 250: " << &array[250] << "\n";
    std::cout << "Adress of element at position 750: " << &array[750] << "\n";
    std::cout << "Byte distance: " << array[750] - array[250] << "\n";
    free(array);

    return EXIT_SUCCESS;
}