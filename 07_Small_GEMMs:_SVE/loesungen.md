# Serie 7
## Aufgabenstellung:

### 7.1 Loop over M


1. Implement and verify the matrix kernel C += AB for M=128, N=6, K=48, ldA=128, ldB=48, ldC=128. Re-use the code of your microkernel, implemented in Section 7.2.  

2. Optimize your matrix kernel. Respect the rules of Section 7.2. Report and document your optimizations.  

3. Submit the metrics “time (s)”, “#executions”, “GFLOPS” and “%peak” together with your team name for your best-performing variant.  
   
#### gemm_asm_sve_128_6_48:

| Team name   | time (s)  | #Executions   | GFLOPS  | %PEAK |   
| ----------- | --------- | ------------  | ------- | ----- |    
| HPC-Lovers  | 0.901105  | 1000000       | 81.8195 | 71.02 | 



### 7.2 Loop over N

1. Implement and verify the matrix kernel C += AB for M=128, N=48, K=48, ldA=128, ldB=48, ldC=128. Re-use the code of your kernel, implemented in Section 8.1.

2. Optimize your matrix kernel. Respect the rules of Section 7.2. Report and document your optimizations.

3. Submit the metrics “time (s)”, “#executions”, “GFLOPS” and “%peak” together with your team name for your best-performing variant.

#### gemm_asm_sve_128_48_48:

| Team name   | time (s)  | #Executions   | GFLOPS  | %PEAK |   
| ----------- | --------- | ------------  | ------- | ----- |    
| HPC-Lovers  | 1.45345   | 200000        | 81.1618 | 70.45 | 

### 7.3 Arbitrary values for M

1. Implement and verify the matrix kernel C += AB for M=63, N=6, K=48, ldA=63, ldB=48, ldC=63. Use predicated SVE instructions to tackle which is not a multiple of 16. Re-use the code of your microkernel, implemented in Section 7.2.

2. Optimize your matrix kernel. Respect the rules of Section 7.2. Report and document your optimizations.

3. Submit the metrics “time (s)”, “#executions”, “GFLOPS” and “%peak” together with your team name for your best-performing variant.

#### gemm_asm_sve_63_6_48:

| Team name   | time (s)  | #Executions   | GFLOPS  | %PEAK |   
| ----------- | --------- | ------------  | ------- | ----- |    
| HPC-Lovers  | 0.910881  | 2000000       | 79.6767 | 69.16 | 