#include "catch.hpp"
#include "../include/gemm-ref.h"
#include <algorithm>
#include <iterator>

TEST_CASE("Squared matrix of type int with b=identity", "[correctness]") {
    int i_m = 3; 
    int i_n = 3; 
    int i_k = 3;
    int i_lda = 3;
    int i_ldb = 3;
    int i_ldc = 3;


    float mat_a[9] = {1,2,3,4,5,6,7,8,9};
    float mat_b[9] = {1,0,0,0,1,0,0,0,1};
    float mat_c[9] = {0};

    gemm_ref(mat_a, mat_b, mat_c, i_m, i_n, i_k, i_lda, i_ldb, i_ldc);

    REQUIRE(std::equal(std::begin(mat_c), std::end(mat_c), std::begin(mat_a)));
}