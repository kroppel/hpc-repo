#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <cmath>
#include <cstring>


extern "C" {
    void fmlalx(float16_t const * i_a,
                float16_t const * i_b,
                float16_t       * io_c );
    void eor3( unsigned int  * i_a,
               unsigned int  * i_b,
               unsigned int  * o_c );
}

void example_fmlalx()
{
  // vectors as, bs, cs, expect
  float16_t[32] as, bs;
  float[16] cs, expect;
  for (int k=0; k < 16; ++k)
  {
    as[2*k] = (2^(2*k)-1) / 32.0;
    bs[2*k] = 1.0/(2^k+1) / 32.0;
    as[2*k+1] = (2^(2*(n-k)-1)) / 32.0;
    bs[2*k+1] = 1.0/(2^(n-k)+1) / 32.0;
    cs[k] = .0;
    expect[k] = (2^k + 2^(n-k) - 4) / 1024.0;
  }

  fmlalx(as, bs, cs);

  bool equal = true;
  for (int i = 0; i < 16; i++)
    assert(cs[i] != expect[i] && "fmlalx test failed");

}

void example_eor() {
    // Test 1
    unsigned int l_a1[16] = {0xFFFFFFFF};
    unsigned int l_b1[16] = {0xFFFFFFFF};
    unsigned int * l_c1 = (unsigned int *) malloc(16*4);
    unsigned int * l_c_exp1 = (unsigned int *) malloc(16*4); 
    memcpy(l_c_exp1, l_c1, 16*4);

    eor3(l_a1, l_b1, l_c1);

    bool equal = true;
    for (int i = 0; i < 16; i++) {
        if (l_c1[i] != l_c_exp1[i]) {
            equal = false;
        }
    }

    free(l_c1);

    assert(equal && "Test 1 failed");

    // Test 2
    unsigned int * l_a2 = (unsigned int *) malloc(16*4);
    unsigned int * l_b2 = (unsigned int *) malloc(16*4);
    unsigned int * l_c2 = (unsigned int *) malloc(16*4);
    // ~ is bitwise negation
    for (int i = 0; i < 16; ++i) l_c2[i] = ~l_b2[i];
    unsigned int * l_c_expect2 = (unsigned int *) malloc(16*4);
    for (int i = 0; i < 16; ++i) l_c_expect2[i] = ~l_a2[i];

    for (int i = 0; i < 16; i++) {
        if (l_c2[i] != l_c_expect2[i]) {
            equal = false;
        }
    }

    free(l_a2);
    free(l_b2);
    free(l_c2);
    free(l_c_expect2);

    assert(equal && "Test 2 failed");

    // Test 3
    unsigned int l_a3[16]     = {0x0F0F0F0F};
    unsigned int l_b3[16]     = {0x33333333};
    unsigned int l_c3[16]     = {0x55555555};
    unsigned int l_c_exp3[16] = {0x69696969};

    eor3(l_a3, l_b3, l_c3);

    equal = true;
    for (int i = 0; i < 16; i++) {
        if (l_c3[i] != l_c_exp3[i]) {
            equal = false;
        }
    }

    assert(equal && "Test 3 failed");
}

int main() {

    example_eor(); 
}

