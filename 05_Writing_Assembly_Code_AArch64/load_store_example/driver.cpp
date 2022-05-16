#include <iostream>
 
extern "C" {
    void load_store_2( int64_t const * i_a, int64_t * o_b );
}

int main() {
    int64_t l_array0[2] = {10, 20};
    int64_t l_array1[2] = {0};
    load_store_2(l_array0, l_array1);
    std::cout << "l_array1: {" << l_array1[0] << ", "<< l_array1[1] << "}\n";

    return EXIT_SUCCESS;
}