# Serie 11

## Aufgabenstellung:

### 11.1. Automatic Vectorization


![Task 11.1.](https://github.com/rauschinger/hpc-repo/blob/main/11_Back_to_the_Compiler/images/11.1.png)

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

![triad disassembler output](https://github.com/rauschinger/hpc-repo/blob/main/11_Back_to_the_Compiler/images/disassembler_output_triad.png)

GCC vectorization report:  

![vectorization report gcc](https://github.com/rauschinger/hpc-repo/blob/main/11_Back_to_the_Compiler/images/vectorization_report_gcc.png)

CLANG vectorization report:  

![vectorization report clang](https://github.com/rauschinger/hpc-repo/blob/main/11_Back_to_the_Compiler/images/vectorization_report_clang.png)

#### 3. Verify optimization levels and flags for enabling/disabling vectorization discussed in the lectures.

Additional compilation flags gcc: -g -pedantic -Wall -Wextra -Werror -O3 -fopenmp -ftree-vectorize -fopt-info-vec-all
Additional compilation flags llvm: -g -pedantic -Wall -Wextra -Werror -O3 -fopenmp -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize

| Optimization Level | GCC       | LLVM      |
| :----              | :----:    | :----:    |
| O0                 | ![no vectorization performed](https://github.com/rauschinger/hpc-repo/blob/main/11_Back_to_the_Compiler/images/disassembly-gcc-O0-with-additional-flags.png) | ![no vectorization performed](https://github.com/rauschinger/hpc-repo/blob/main/11_Back_to_the_Compiler/images/clang-O0-with-additional-flags.png) |
| O2                 | ![vectorization with NEON instructions performed](https://github.com/rauschinger/hpc-repo/blob/main/11_Back_to_the_Compiler/images/disassembly-clang-O2-with-additional-flags.png) | ![vectorization with NEON instructions performed](https://github.com/rauschinger/hpc-repo/blob/main/11_Back_to_the_Compiler/images/gcc-O2-with-additional-flags.png) |




#### 4. Illustrate the impact of auto-vectorization by using an 1024 values for each of the three arrays. As always, repeat the experiment often enough such that the runtime exceeds one second.

#### 5. Identify requirements on loops such that they are vectorizable. Now, deliberately break the auto-vectorization of the compiler by rewriting the triad function. Do this at least by making the loop uncountable and by using an external function inside of the loop. Confirm your experiments through respective vectorization reports and by disassembling the generated code.