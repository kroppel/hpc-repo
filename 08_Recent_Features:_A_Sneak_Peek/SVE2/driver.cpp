#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <cmath>
#include <chrono>

extern "C" {
    void fmlalb(      float    const * i_a,
                float    const * i_b,
                float          * o_c );
}

int main(){

    //Vectors A, B, C
    float const l_a[32] = {0};
    float const l_b[32] = {0};
    float l_c[16] = {0};

    for (int i = 0; i < 32; i++) {
        l_a = i;
        l_b = i;
    }

    fmlalb(l_a, l_b, l_c);

    std::cout << "C: ";
    for (int i = 0; i < 32; i++) {
        std::cout << i << ", ";
    } 
    std::cout << "\n";

    return EXIT_SUCCESS;    
}

