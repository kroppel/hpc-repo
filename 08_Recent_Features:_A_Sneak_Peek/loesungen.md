triad_low_sve_agnostic ausgeführt mit ArmIE für verschiedene Registerbreiten:


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