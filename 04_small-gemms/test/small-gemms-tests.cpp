#include "catch.hpp"
#include "gemm-ref.h"
#include "gemm_compiler_32_32_32_32_32_32.h"
#include <algorithm>
#include <iterator>

TEST_CASE("Squared matrix with B=identity", "[correctness]") {
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

TEST_CASE("Rectangular Matrices A, B, Quadratic Result, zero matrix", "[correctness]") {
    int i_m = 3; 
    int i_n = 3; 
    int i_k = 6;
    int i_lda = 3;
    int i_ldb = 6;
    int i_ldc = 3;


    float mat_a[18] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    float mat_b[18] = {0};
    float mat_c[36] = {0};

    float mat_res[36] = {0}; 

    gemm_ref(mat_a, mat_b, mat_c, i_m, i_n, i_k, i_lda, i_ldb, i_ldc);

    REQUIRE(std::equal(std::begin(mat_c), std::end(mat_c), std::begin(mat_res)));
}

TEST_CASE("LD = 3, Quadratic Matrices 2x2", "[correctness]") {
    int i_m = 2; 
    int i_n = 2; 
    int i_k = 2;
    int i_lda = 3;
    int i_ldb = 3;
    int i_ldc = 3;


    float mat_a[6] = {1,2,1,3,4,1};
    float mat_b[6] = {1,0,3,0,1,2};
    float mat_c[6] = {0,0,1,0,0,1};

    gemm_ref(mat_a, mat_b, mat_c, i_m, i_n, i_k, i_lda, i_ldb, i_ldc);

    REQUIRE(std::equal(std::begin(mat_c), std::end(mat_c), std::begin(mat_a)));
}

TEST_CASE("Dim=32 Kernel MNK", "[correctness]") {
    int i_m = 32; 
    int i_n = 32; 
    int i_k = 32;
    int i_lda = 32;
    int i_ldb = 32;
    int i_ldc = 32;


    float mat_a[32*32] = {1};
    float mat_b[32*32] = {1};
    float mat_c1[32*32] = {0};
    float mat_c2[32*32] = {0};

    gemm_ref(mat_a, mat_b, mat_c1, i_m, i_n, i_k, i_lda, i_ldb, i_ldc);
    gemm_compiler_32_32_32_32_32_32_mnk(mat_a, mat_b, mat_c2);

    REQUIRE(std::equal(std::begin(mat_c2), std::end(mat_c2), std::begin(mat_c1)));
}

TEST_CASE("Dim=32 Kernel NKM", "[correctness]") {
    int i_m = 32; 
    int i_n = 32; 
    int i_k = 32;
    int i_lda = 32;
    int i_ldb = 32;
    int i_ldc = 32;


    float mat_a[32*32] = {1};
    float mat_b[32*32] = {1};
    float mat_c1[32*32] = {0};
    float mat_c2[32*32] = {0};

    gemm_ref(mat_a, mat_b, mat_c1, i_m, i_n, i_k, i_lda, i_ldb, i_ldc);
    gemm_compiler_32_32_32_32_32_32_nkm(mat_a, mat_b, mat_c2);

    REQUIRE(std::equal(std::begin(mat_c2), std::end(mat_c2), std::begin(mat_c1)));
}