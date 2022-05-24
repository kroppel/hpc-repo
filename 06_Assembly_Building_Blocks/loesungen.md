# Serie 6

## Aufgabenstellung:

### SVE: Getting Started

- Browse over the Hot Chips 28 presentation ARMv8-A Next-Generation Vector Architecture for HPC.
  
    Website under Maintenance

- Check out the presentation Introduction to ARM SVE by ARM Software Developers.

    SVE key features:  

    Vector Agnostic design -> portability of compiled code between different HW vector length implementations  
    gather-load & scatter-store  
    per-lane-predication  
    predicate-driven loop control  
    vector partitioning & software-managed speculation  
    FP horizontal reductions  


- Have a look at the paper The ARM Scalable Vector Extension.

- Have a look at the SVE entry point on the official homepages.

- Browse through the Arm Architecture Reference Manual Supplement, The Scalable Vector Extension.

- Browse through the SVE part of the ISA.

- Browse through the SVE Programming Examples Whitepaper.

- Have a look at the SVE examples of the Arm SVE Tools Tutorial.

- Read about the V1 and N2 microarchitectures, e.g, on AnandTech or The Next Platform.

- Search for additional information on SVE and its superset SVE2.


### Small GEMMs: Unrolled Part


Rules:

- Respect the procedure call standard. But: if you don’t modify a register, you don’t have to save it to the stack.

- Verify your kernels.

- Instrument your kernels for at least 1 second in your performance measurements through repeated executions.


1. Implement and verify the unrolled matrix kernel C += AB for M=64, N=6, K=1, ldA=64, ldB=1, ldC=64.

2. Tune your kernel to squeeze more performance out of the core. You may change everything, e.g., the type of the used instructions or the order of the used instructions but have to follow the rules above. Report and document your optimizations.

3. Add a loop over K to realize C += AB for M=64, N=6, K=48, ldA=64, ldB=48, ldC=64.

4. Come up with a creative team name and submit it together with your entries for “time (s)”, “#executions”, “GFLOPS” and “%peak” in the table above.

#### gemm_asm_sve_64_6_1_opt:

| Team name   | time (s)  | #Executions   | GFLOPS  | %PEAK | 
| ----------- | --------- | ------------  | ------- | ----- |  
| HPC-Lovers  | 3.72714   | 50000000      | 10.3477 | 8,98  |  

#### gemm_asm_sve_64_6_48_opt:

| Team name   | time (s)  | #Executions   | GFLOPS  | %PEAK |   
| ----------- | --------- | ------------  | ------- | ----- |    
| HPC-Lovers  | 2.44574   | 5000000       | 78.9579 | 68,54 |    


### Conditions and Loops



1. Explain in 1-2 sentences what every of the eight functions does.

#### int32_t high_lvl_0:
Takes in parameter of type int32_t and returns the input value.  

#### uint64_t high_lvl_1:
Takes in parameter of type uint64_t and returns 0.  

#### int32_t high_lvl_2:
Takes in parameter of type int32_t and returns 0 if input value is higher than  
31, 1 otherwise.  

#### void high_lvl_3:
Takes in 2 parameters of type int32_t * and sets value  
referenced by second parameter to 1 if value referenced  
by first parameter is lower than 25, otherwise it sets  
the value referenced by second parameter to 0.  

#### uint32_t high_lvl_4:
Takes in 3 parameters of type uint32_t and returns  
- 1 if first parameter is smaller than second and third  
- 2 if second parameter is smaller than first and third  
- 3 otherwise  

#### void high_lvl_5:
Takes in uint32_t and pointer to uint32_t parameters and  
and increments the value referenced by the second parameter  
n times with n being the first parameters value.  

#### void high_lvl_6:
Takes in two uint64_t parameters and 1 pointer to uint64_t and  
and adds the second parameters value to the value referenced to  
by the third parameter n times with n being the first parameters value.  
If the first parameter's value is smaller than 1, the addition will be  
executed exactly once.  

#### void high_lvl_7:
Takes in one uint64_t parameter and 2 pointer to uint64_t and  
and writes the value from the first array at index i to the second array  
at index i with in range from 0 to the first parameters value.  

2. Implement the functions in assembly language. Use the file names low_level.h and low_level.cpp and matching names for the functions, i.e., low_lvl_0, low_lvl_1, …, low_lvl_7.

3. Verify your low-level versions by extending the driver.
