#include <cstdint>
#include <cstdlib>
#include <iostream>

extern "C" {

  void copy_asm( uint32_t const * i_a,
                 uint64_t       * o_b );

  void copy_c( uint32_t const * i_a,
               uint64_t       * o_b );

}

int main() {

  uint32_t l_a[7] = { 1, 21, 43, 78, 89, 91, 93 };
  uint64_t l_b[7] = { 0 };
  uint64_t l_c[7] = { 0 };

  copy_asm(l_a, l_b);

  copy_c(l_a, l_c);

  std::cout << "l_b: ";
  for (uint64_t b:l_b) {
    std::cout << b << ", ";
  }

  std::cout << "l_c: ";
  for (uint64_t c:l_c) {
    std::cout << c << ", ";
  }

  return EXIT_SUCCESS;
}