#include <iostream>
#include <arm_bf16.h>
#include <arm_neon.h>

extern "C" {
    void bfmmla_example(bfloat16_t    const * i_a,
                bfloat16_t    const * i_b,
                float          * o_c );
}


int main(){

    bfloat16_t a[16] = {    0.0, 1.0, 2.0, 3.0,
                            4.0, 5.0, 6.0, 7.0,
                            8.0, 9.0, 10.0, 11.0,
                            12.0, 13.0, 14.0, 15.0  };

    bfloat16_t b[16] = { 0.5, 0.5, 0.5, 0.5,
                        0.5, 0.5, 0.5, 0.5,
                        0.5, 0.5, 0.5, 0.5,
                        0.5, 0.5, 0.5, 0.5  };
                        
    float c[8] = {  0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0  };


    std::cout << "A: \n";
    for (int i = 0; i < 16; i++) {
        std::cout << vcvtah_f32_bf16(a[i]) << " ";
        if (i % 4 == 3)
            std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << "B: \n";
    for (int i = 0; i < 8; i++) {
        std::cout << vcvtah_f32_bf16(b[i]) << " ";
        if (i % 2 == 1)
            std::cout << "\n";
    }
    std::cout << "\n";

    bfmmla_example(a, b, c);

    std::cout << "C: \n";
    for (int i = 0; i < 8; i++) {
        std::cout << c[i] << " ";
        if (i % 2 == 1)
            std::cout << "\n";
    }
    std::cout << "\n";

    return EXIT_SUCCESS;    
}

