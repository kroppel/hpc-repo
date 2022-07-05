# Serie 12

## Aufgabenstellung:
### 12.1. Triad
![Task 12.1.](https://github.com/kroppel/hpc-repo/blob/main/12_OpenMP/12_1.png)  

The benchmark was performed with OMP_NUM_THREADS=8. Results can be found in './Triad/benchmark_results'.  

Between the benchmarks for array lengths 1024 and 1024 * 1024 the results show a significant increase in
GFLOPS as well as used memory bandwidth. This is most likely due to the fact that during the first benchmark
the parallelization with 8 threads did not bring much performance gain, as there is not much work to do for each thread and
a lot of overhead incurred from spawning the threads for each iteration. Increasing the array size leads to less overhead, resulting
in a much better performance.



### 12.2. Monte Carlo Method


![Task 12.2.](https://github.com/kroppel/hpc-repo/blob/main/12_OpenMP/12_2.png)

The solution was discussed in the lecture from 29.06.



### 12.3. Tasking


![Task 12.3.](https://github.com/kroppel/hpc-repo/blob/main/12_OpenMP/12_3.png)
