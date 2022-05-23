# Serie 6

## Aufgabenstellung:

### SVE: Getting Started

- Browse over the Hot Chips 28 presentation ARMv8-A Next-Generation Vector Architecture for HPC.

- Check out the presentation Introduction to ARM SVE by ARM Software Developers.

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



### Conditions and Loops



1. Explain in 1-2 sentences what every of the eight functions does.

2. Implement the functions in assembly language. Use the file names low_level.h and low_level.cpp and matching names for the functions, i.e., low_lvl_0, low_lvl_1, …, low_lvl_7.

3. Verify your low-level versions by extending the driver.
