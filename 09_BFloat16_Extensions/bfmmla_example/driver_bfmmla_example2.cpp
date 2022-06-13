#include <iostream>
#include <arm_bf16.h>
#include <arm_neon.h>

extern "C" {
    void bfmmla_example(bfloat16_t    const * i_a,
                bfloat16_t    const * i_b,
                float          * o_c );
}


int main(){

    bfloat16_t a[16] = {0.0};
    bfloat16_t b[8] = {0.0};
    float c[8] = {0};

    for (int i = 0; i < 16; i++) {
        a[i] = vcvth_bf16_f32((float32_t) i);
    }

    for (int i = 0; i < 8; i++) {
        b[i] = vcvth_bf16_f32((float32_t) 0.5);
    }

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

