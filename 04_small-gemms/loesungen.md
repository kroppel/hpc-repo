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

Benchmark of Reference Kernel:  
    n_gflops: 600000000  
    time: 0.963491s  
    GFLOPS: 0.0622735  
    Average Kernel Duration: 0.0622735  

7. Try optimization flags, e.g., -O2 or -O3, and report performance numbers for the following matrix-sizes and leading dimensions:  

    M=N=K=ldA=ldB=ldC=λ  

with  

    λ ∈ {4,8,12,16,24,32,48,64}  

No Optimizations:  
    Benchmark of Reference Kernel:  
        Dim: 4  
        n_gflops: 1000000000  
        time: 1.36721s  
        GFLOPS: 0.0731417  
        Average Kernel Duration: 1.75003e-07  
    Benchmark of Reference Kernel:  
        Dim: 8  
        n_gflops: 999999488  
        time: 1.31727s  
        GFLOPS: 0.0759147  
        Average Kernel Duration: 1.34888e-06  
    Benchmark of Reference Kernel:  
        Dim: 12  
        n_gflops: 999997056  
        time: 1.56656s  
        GFLOPS: 0.0638341  
        Average Kernel Duration: 5.41404e-06  
    Benchmark of Reference Kernel:  
        Dim: 16  
        n_gflops: 999997440  
        time: 1.6s  
        GFLOPS: 0.0624999  
        Average Kernel Duration: 1.31072e-05  
    Benchmark of Reference Kernel:  
        Dim: 24  
        n_gflops: 999972864  
        time: 2.88516s  
        GFLOPS: 0.0346592  
        Average Kernel Duration: 7.97709e-05  
    Benchmark of Reference Kernel:  
        Dim: 32  
        n_gflops: 999948288  
        time: 2.81024s  
        GFLOPS: 0.0355823  
        Average Kernel Duration: 0.000184181  
    Benchmark of Reference Kernel:  
        Dim: 48  
        n_gflops: 999972864  
        time: 2.71777s  
        GFLOPS: 0.0367939  
        Average Kernel Duration: 0.000601143  
    Benchmark of Reference Kernel:  
        Dim: 64  
        n_gflops: 999817216  
        time: 2.67373s  
        GFLOPS: 0.0373941  
        Average Kernel Duration: 0.00140206  

O2:  
    Benchmark of Reference Kernel:  
        Dim: 4  
        n_gflops: 1000000000  
        time: 1.36708s  
        GFLOPS: 0.0731486  
        Average Kernel Duration: 1.74986e-07  
    Benchmark of Reference Kernel:  
        Dim: 8  
        n_gflops: 999999488  
        time: 1.31724s  
        GFLOPS: 0.075916  
        Average Kernel Duration: 1.34886e-06  
    Benchmark of Reference Kernel:  
        Dim: 12  
        n_gflops: 999997056  
        time: 1.5665s  
        GFLOPS: 0.0638363  
        Average Kernel Duration: 5.41385e-06  
    Benchmark of Reference Kernel:  
        Dim: 16  
        n_gflops: 999997440  
        time: 1.59989s  
        GFLOPS: 0.0625043  
        Average Kernel Duration: 1.31063e-05  
    Benchmark of Reference Kernel:  
        Dim: 24  
        n_gflops: 999972864  
        time: 2.88508s  
        GFLOPS: 0.0346602  
        Average Kernel Duration: 7.97688e-05  
    Benchmark of Reference Kernel:  
        Dim: 32  
        n_gflops: 999948288  
        time: 2.81738s  
        GFLOPS: 0.0354921  
        Average Kernel Duration: 0.000184649  
    Benchmark of Reference Kernel:  
        Dim: 48  
        n_gflops: 999972864  
        time: 2.71685s  
        GFLOPS: 0.0368063  
        Average Kernel Duration: 0.000600941  
    Benchmark of Reference Kernel:  
        Dim: 64  
        n_gflops: 999817216  
        time: 2.67409s  
        GFLOPS: 0.037389  
        Average Kernel Duration: 0.00140225  

O3:  
    Benchmark of Reference Kernel:  
        Dim: 4  
        n_gflops: 1000000000  
        time: 1.37162s  
        GFLOPS: 0.0729067  
        Average Kernel Duration: 1.75567e-07  
    Benchmark of Reference Kernel:  
        Dim: 8  
        n_gflops: 999999488  
        time: 1.31991s  
        GFLOPS: 0.0757627  
        Average Kernel Duration: 1.35159e-06  
    Benchmark of Reference Kernel:  
        Dim: 12  
        n_gflops: 999997056  
        time: 1.5524s  
        GFLOPS: 0.0644162  
        Average Kernel Duration: 5.36511e-06  
    Benchmark of Reference Kernel:  
        Dim: 16  
        n_gflops: 999997440  
        time: 1.59052s  
        GFLOPS: 0.0628724  
        Average Kernel Duration: 1.30296e-05  
    Benchmark of Reference Kernel:  
        Dim: 24  
        n_gflops: 999972864  
        time: 2.89638s  
        GFLOPS: 0.034525  
        Average Kernel Duration: 8.00812e-05  
    Benchmark of Reference Kernel:  
        Dim: 32  
        n_gflops: 999948288  
        time: 2.81914s  
        GFLOPS: 0.03547  
        Average Kernel Duration: 0.000184765  
    Benchmark of Reference Kernel:  
        Dim: 48  
        n_gflops: 999972864  
        time: 2.72364s  
        GFLOPS: 0.0367146  
        Average Kernel Duration: 0.000602441  
    Benchmark of Reference Kernel:  
        Dim: 64  
        n_gflops: 999817216  
        time: 2.67716s  
        GFLOPS: 0.0373462  
        Average Kernel Duration: 0.00140386  

No big changes in the times for different optimizations.  
Kernel durations are increasing in cubic fashion depending on the dimension, as the number of FLOPs is given by n*m*k*2 which leads to asymptotic complexity of O(n^3) for n=m=k  

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

9. Implement a C/C++ matrix-matrix multiplication kernel through three nested loops over M, N and K. Assumptions as before, however the loop-ordering shall be:  

    The loop over N  should be the outer-loop.  
    The loop over K should be the in the middle.  
    The loop over M should be the inner-loop.  

As before, implement the kernel in the file gemm_compiler_32_32_32_32_32_32.cpp but use the following signature:  

void gemm_compiler_32_32_32_32_32_32_nkm( float const * i_a,  
                                          float const * i_b,  
                                          float       * io_c );  
Make sure that the two kernels produce the same results (up to a small epsilon) as your reference kernel gemm_ref.  

Try optimization flags, e.g., -O2 or -O3, and report performance numbers for gemm_compiler_32_32_32_32_32_32_mnk and gemmCompiler_32_32_32_32_32_32_nkm.  







