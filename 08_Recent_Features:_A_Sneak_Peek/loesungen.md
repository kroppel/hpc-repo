# Serie 8

## Aufgabenstellung:

### 8.3 Arbitrary Values for M


1. Implement and verify the matrix kernel C += AB for M=63, N=6, K=48, ldA=63, ldB=48, ldC=63. Use predicated SVE instructions to tackle which is not a multiple of 16. Re-use the code of your microkernel, implemented in Section 7.2.

2. Optimize your matrix kernel. Respect the rules of Section 7.2. Report and document your optimizations.

3. Submit the metrics “time (s)”, “#executions”, “GFLOPS” and “%peak” together with your team name for your best-performing variant.

#### gemm_asm_sve_63_6_48:

| Team name   | time (s)  | #Executions   | GFLOPS  | %PEAK |   
| ----------- | --------- | ------------  | ------- | ----- |    
| HPC-Lovers  | 0.910881  | 2000000       | 79.6767 | 69.16 |

# Serie 9

## Aufgabenstellung:

### 9. Recent Features: A Sneak Peek

### 9.1. Arm Instruction Emulator

![Task 9.1.](https://github.com/rauschinger/hpc-repo/blob/main/08_Recent_Features:_A_Sneak_Peek/tasks_1.png)

https://developer.arm.com/documentation/102190/latest  


### 9.2. Vector Length Agnostic Programming

![Task 9.2.](https://github.com/rauschinger/hpc-repo/blob/main/08_Recent_Features:_A_Sneak_Peek/tasks_2.png)

triad_low_sve_agnostic ausgeführt mit ArmIE für verschiedene Registerbreiten:


```
[hgf_qei8127@ftp-a64n1 Vector_Length_Agnostic_Programming]$ armie -msve-vector-bits=128 ./build/triad  
Run benchmark triad_low  
Difference is 0  
 duration: 12.8207 seconds  
 #executions: 200000  
 GFLOPS: 0.00311995  
 %PEAK: 2.70829e-05  
[hgf_qei8127@ftp-a64n1 Vector_Length_Agnostic_Programming]$ armie -msve-vector-bits=256 ./build/triad  
Run benchmark triad_low  
Difference is 0  
 duration: 7.04753 seconds  
 #executions: 200000  
 GFLOPS: 0.00567575  
 %PEAK: 4.92686e-05  
[hgf_qei8127@ftp-a64n1 Vector_Length_Agnostic_Programming]$ armie -msve-vector-bits=512 ./build/triad  
Run benchmark triad_low  
Difference is 0  
 duration: 4.07983 seconds  
 #executions: 200000  
 GFLOPS: 0.00980432  
 %PEAK: 8.5107e-05  
[hgf_qei8127@ftp-a64n1 Vector_Length_Agnostic_Programming]$ armie -msve-vector-bits=2048 ./build/triad  
Run benchmark triad_low  
Difference is 0  
 duration: 3.93599 seconds  
 #executions: 200000  
 GFLOPS: 0.0101626  
 %PEAK: 8.82173e-05 
```



### 9.3. SVE2


 ![Task 9.3.](https://github.com/rauschinger/hpc-repo/blob/main/08_Recent_Features:_A_Sneak_Peek/tasks_3.png)


 https://developer.arm.com/documentation/102340/latest/

