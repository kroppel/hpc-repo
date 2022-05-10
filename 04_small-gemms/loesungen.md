Serie 4  


1. Write a driver in the file driver.cpp which acts as an entry point for your future work.  

2. Implement a C/C++ reference kernel for the operation C += A*B . The respective function should be implemented in the file gemm_ref.cpp and have the following signature:  

void gemm_ref( float        const * i_a,  
               float        const * i_b,  
               float              * io_c,  
               unsigned int         i_m,  
               unsigned int         i_n,  
               unsigned int         i_k,  
               unsigned int         i_lda,  
               unsigned int         i_ldb,  
               unsigned int         i_ldc );  
Implement unit tests for gemm_ref. These should exemplary cover different sizes and leading dimensions, about five variants are sufficient. Consider using Catch2 for your tests.  



3. Given the matrix dimensions M,N,K how many floating point operations are required to perform the (dense) matrix-matrix multiplication?  

Die Ergebnismatrix hat M*N Elemente. Pro Element muss k Mal eine Multiplikation durchgeführt werden und alle Ergebnisse aus der Multiplikation müssen aufaddiert werden. Daher ergeben sich 2K Operationen.  

--> #floating point operations done per kernel call = M*N*2*K  


4. Add a simple loop in your driver which repeatedly calls your reference kernel implemented in gemm_ref. The kernel should be executed often enough such that the loop takes about one second to complete.  

5. Use std::chrono outside of your loop doing repetitions to measure the average time per kernel call:  

    Use std::chrono::high_resolution_clock::now() to get the current time before and after the loop.  

    Use std::chrono::duration_cast< std::chrono::duration< double> >() to get the duration between your two measurements.  



6. Print the average duration and the sustained GFLOPS of the repeated kernel calls.  

7. Try optimization flags, e.g., -O2 or -O3, and report performance numbers for the following matrix-sizes and leading dimensions:  

    M=N=K=ldA=ldB=ldC=λ  

with  

    λ ∈ {4,8,12,16,24,32,48,64}  


8. Implement a C/C++ matrix-matrix multiplication kernel through three nested loops over M,N and K:

    The loop over M should be the outer-loop.
    The loop over N should be the in the middle.
    The loop over K should be the inner-loop.

The kernel should assume fixed matrix-sizes and leading dimensions:

    M = N = K = 32
    ldA = ldB = ldC = 32

The kernel should be implemented in the file gemm_compiler_32_32_32_32_32_32.cpp and have the following signature:

void gemm_compiler_32_32_32_32_32_32_mnk( float const * i_a,
                                          float const * i_b,
                                          float       * io_c );

9. Implement a C/C++ matrix-matrix multiplication kernel through three nested loops over ,  and . Assumptions as before, however the loop-ordering shall be:

    The loop over  should be the outer-loop.
    The loop over  should be the in the middle.
    The loop over  should be the inner-loop.

As before, implement the kernel in the file gemm_compiler_32_32_32_32_32_32.cpp but use the following signature:

void gemm_compiler_32_32_32_32_32_32_nkm( float const * i_a,
                                          float const * i_b,
                                          float       * io_c );
Make sure that the two kernels produce the same results (up to a small epsilon) as your reference kernel gemm_ref.

Try optimization flags, e.g., -O2 or -O3, and report performance numbers for gemm_compiler_32_32_32_32_32_32_mnk and gemmCompiler_32_32_32_32_32_32_nkm.



