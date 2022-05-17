#include <cstdint>
#include <cstlib>
#include <cassert>
#include <iostream>

extern "C" {
    void gemm_asm_gp(   uint32_t const * i_a,
                        uint32_t const * i_b,
                        uint32_t       * io_c);
}

int main(){
    uint32_t l_a[2][4] = {  {0,1,2,3},
                            {4,5,6,7}   };

    uint32_t l_b[2][2] = {  {10,11},
                            {12,13}   };
    

    uint32_t l_c[2][4] = {  {14,15,16,17},
                            {18,19,20,21}   };

    std::cout << "A:" << std::endl;
    for(    unsigned short l_ro = 0; l_ro < 4; l_ro++) {
        std::cout << l_a[0][l_ro] << "\t" << l_a[1][l_ro] << std::endl;
    }

    std::cout << "\nB:" << std::endl;
    for(    unsigned short l_ro = 0; l_ro < 2; l_ro++) {
        std::cout << l_b[0][l_ro] << "\t" << l_b[1][l_ro] << std::endl; 
    }

    std::cout << "\nC (in):" << std::endl;
    for(    unsigned short l_ro = 0; l_ro < 4; l_ro++) {
        std::cout << l_c[0][l_ro] << "\t" << l_c[1][l_ro] << std::endl; 
    }

    gemm_asm_gp(    l_a[0],
                    l_b[0],
                    l_c[0]  );

    std::cout << "\nC (out):" << std::endl;
    for( unsigned short l_ro = 0; l_ro < 4; l_ro++) {
        std::cout << l_c[0][l_ro] << "\t " << l_c[1][l_ro] << std::endl;
    }

    // ....
    assert( l_c[0][0] == 58     );
    assert( l_c[0][1] == 80     );
    assert( l_c[0][2] == 102    );
    assert( l_c[0][3] == 124    );
    assert( l_c[1][0] == 70     );
    assert( l_c[1][1] == 96     );
    assert( l_c[1][2] == 122    );
    assert( l_c[1][3] == 148    );
    
    return EXIT_SUCCESS;    
}

