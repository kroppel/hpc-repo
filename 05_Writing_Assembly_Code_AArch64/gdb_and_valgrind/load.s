        .text
        .align 4
        .type   load_asm, %function
        .global load_asm
load_asm:
        /*
        * Preincrement address in x0 by 8,
        * then load value at resulting address
        * into register x1
        */ 
        ldr x1,     [x0, #8]!
        /*
        * Load value at address that resides in x0
        * into register x2 and x3
        */
        ldp x2, x3, [x0]
        /*
        * Load value at address that resides in x0
        * with a signed offset of 16 into x4 and x5
        */ 
        ldp x4, x5, [x0, #16]

        /*
        * Contents of registers as decimal values
        * X1: 400
        * X2: 400
        * X3: 500
        * X4: 600
        * X5: 700
        */
        ret
        .size load_asm, (. - load_asm)
