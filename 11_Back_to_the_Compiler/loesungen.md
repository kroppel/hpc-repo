# Serie 11

## Aufgabenstellung:

### 11.1. Automatic Vectorization


![Task 11.1.](https://github.com/kroppel/hpc-repo/blob/main/11_Back_to_the_Compiler/images/11.1.png)

#### 1. Read the Coding Considerations of the Arm Compiler Scalable Vector Extension User Guide Version. Name three hints which you consider most helpful for your future work and explain why. Explain at least one pragma which guides auto-vectorization.

1. Use the __restrict__ keyword to tell the compiler that a specific pointer does not alias with any other pointer,
that means does not point to the same or overlapping location in memory. By doing this, the compiler might be able
to use vector instructions when processing the pointers, because he knows that they can be processed independently.

2. Prefer using signed integer index variables, as the compiler does not need to prove that it overflows and can optimize the code more easily. (Of course the programmer in this case has to make sure himself that no undefined behaviour occurs due to overflow).
When writing loops using a unsigned integer index variable, prefer the usage of "<" as condition instead of "<=". This makes it easier for the compiler to prove that the variable does not wrap before loop termination leading to a non terminating loop.

3. By using pragmas one can encourage or suppress auto-vectorization. The pragma only affects the immediatly following loop statement. If the code contains multiple nested loops, one has to insert a pragma before each loop in order to affect every loop in the nest. If the loop contains dependencies which hinder parallelism, auto-vectorization might not be performed. If the data dependencies between loop iterations doesnt prevent vectorization, one uses the "assume_safety" directive. The syntax looks like the following:  
#pragma clang loop vectorize(assume_safety)


#### 2. Build the code with the GCC and LLVM toolchains. Generate vectorization reports with both toolchains. Convince at least one compiler to generate SVE code and disassemble it.

GCC toolchain disassembler output:  

![triad disassembler output](https://github.com/kroppel/hpc-repo/blob/main/11_Back_to_the_Compiler/images/disassembler_output_triad.png)

GCC vectorization report:  

![vectorization report gcc](https://github.com/kroppel/hpc-repo/blob/main/11_Back_to_the_Compiler/images/vectorization_report_gcc.png)

CLANG vectorization report:  

![vectorization report clang](https://github.com/kroppel/hpc-repo/blob/main/11_Back_to_the_Compiler/images/vectorization_report_clang.png)

#### 3. Verify optimization levels and flags for enabling/disabling vectorization discussed in the lectures.



Additional compilation flags gcc: -g -pedantic -Wall -Wextra -Werror -fopenmp -ftree-vectorize -fopt-info-vec-all
Additional compilation flags llvm: -g -pedantic -Wall -Wextra -Werror -fopenmp -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize

| Optimization Level | GCC       | LLVM      |
| :----              | :----:    | :----:    |
| O0                 | ![no vectorization performed](https://github.com/kroppel/hpc-repo/blob/main/11_Back_to_the_Compiler/images/disassembly-gcc-O0-with-additional-flags.png) | ![no vectorization performed](https://github.com/kroppel/hpc-repo/blob/main/11_Back_to_the_Compiler/images/disassembly-clang-O0-with-additional-flags.png) |
| O2                 | ![vectorization with NEON instructions performed](https://github.com/kroppel/hpc-repo/blob/main/11_Back_to_the_Compiler/images/disassembly-gcc-O2-with-additional-flags.png) | ![vectorization with NEON instructions performed](https://github.com/kroppel/hpc-repo/blob/main/11_Back_to_the_Compiler/images/disassembly-clang-O2-with-additional-flags.png) |

For GCC, unexpectedly the compiler did not perform any auto-vectorization for O0, even though the flag -ftree-vectorize was set.
For LLVM it was surprising that there was no auto-vectorization for O0 as well, as it should be done so by default.
In both cases it seems like the compiler did not evaluate possible vectorization options as benefitial for the overall performance.
It also seems that higher optimization levels enabled the compiler to alter the code structure in a way that he could perform auto
vectorization more easily.

#### 4. Illustrate the impact of auto-vectorization by using an 1024 values for each of the three arrays. As always, repeat the experiment often enough such that the runtime exceeds one second.

| Toolchain | Metrics no auto-vectorization | Metrics with auto-vectorization | Metrics with SVE auto-vectorization |
| :----     | :----                         | :----                           | :----                               |
| GCC       | _working with:_<br /> - N_VALUES: 1024, this means 0.00390625 MiB per array<br /> - N_REPEATS: 1000000<br />   _performance:_<br />- duration: 2.85349 seconds<br />- GFLOPS: 0.717718<br />- GiB/s: 4.01056<br /> | _working with:_<br /> - N_VALUES: 1024, this means 0.00390625 MiB per array<br /> - N_REPEATS: 10000000<br />   _performance:_<br />- duration: 1.12866 seconds<br />- GFLOPS: 18.1454<br />- GiB/s: 101.395<br /> | _working with:_<br /> - N_VALUES: 1024, this means 0.00390625 MiB per array<br /> - N_REPEATS: 10000000<br />   _performance:_<br />- duration: 1.13649 seconds<br />- GFLOPS: 18.0204<br />- GiB/s: 100.697<br /> |
| LLVM       | _working with:_<br /> - N_VALUES: 1024, this means 0.00390625 MiB per array<br /> - N_REPEATS: 1000000<br />   _performance:_<br />- duration: 2.56674 seconds<br />- GFLOPS: 0.797899<br />- GiB/s: 4.45861<br /> | _working with:_<br /> - N_VALUES: 1024, this means 0.00390625 MiB per array<br /> - N_REPEATS: 10000000<br />   _performance:_<br />- duration: 1.34253 seconds<br />- GFLOPS: 15.2548<br />- GiB/s: 85.2426<br /> | _working with:_<br /> - N_VALUES: 1024, this means 0.00390625 MiB per array<br /> - N_REPEATS: 10000000<br />   _performance:_<br />- duration: 1.15006 seconds<br />- GFLOPS: 17.8078<br />- GiB/s: 99.5087<br /> |

Both compilers can boost performance significantly with auto-vectorization, especially GCC, which improves by a factor of over 25.
SVE for this example kernel shows no significant improvement in performance over NEON.  
LLVM's generated code performs much worse than GCC's for NEON vectorization, but comes close to GCC's performance with SVE instrution usage.

#### 5. Identify requirements on loops such that they are vectorizable. Now, deliberately break the auto-vectorization of the compiler by rewriting the triad function. Do this at least by making the loop uncountable and by using an external function inside of the loop. Confirm your experiments through respective vectorization reports and by disassembling the generated code.