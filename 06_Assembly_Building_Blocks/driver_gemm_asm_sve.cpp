#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <cmath>

extern "C" {

    void gemm_asm_sve_64_6_1( float const * i_a,
                            float const * i_b,
                            float       * io_c );
}


void gemm_ref( float        const * i_a,
               float        const * i_b,
               float              * io_c,
               unsigned int         i_m,
               unsigned int         i_n,
               unsigned int         i_k,
               unsigned int         i_lda,
               unsigned int         i_ldb,
               unsigned int         i_ldc) {
    for (unsigned int m = 0; m < i_m; m++) {
        for (unsigned int n = 0; n < i_n; n++) {
            for (unsigned int k = 0; k < i_k; k++) {
                io_c[n*i_ldc+m] += i_a[k*i_lda+m]*i_b[n*i_ldb+k];
            }
        }
    }
}

double mat_diff_sum(float * c1, float * c2, unsigned int m, unsigned int n) {
    double diff = 0;
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < m; j++) {
            diff += std::abs(c1[i*n+j]-c2[i*n+j]);
        }
    }
    return diff;
}


int main(){
    const float l_a[64] = {0,1,2,0.5,1,2,0,0.3,
                            0,1,2,0.5,1,2,0,0.3,
                            0,1,2,0.5,1,2,0,0.3,
                            0,1,2,0.5,1,2,0,0.3,
                            0,1,2,0.5,1,2,0,0.3,
                            0,1,2,0.5,1,2,0,0.3,
                            0,1,2,0.5,1,2,0,0.3,
                            0,1,2,0.5,1,2,0,0.3};

    const float l_b[6] = {1,0,1,0.5,0.3,1};
    

    float l_c_ref[6*64] = {0};
    
    gemm_ref(l_a, l_b, l_c_ref, 64, 6, 1, 64, 1, 64);


    float l_c[6*64] = {0};


    

    gemm_asm_sve_64_6_1(    l_a, l_b, l_c  );



    //testing for correctness
    double diff = mat_diff_sum(l_c, l_c_ref, 64, 6);
    std::cout << "Difference is " << diff << "\n";
    assert(diff < 0.05);
    
    return EXIT_SUCCESS;    
}

