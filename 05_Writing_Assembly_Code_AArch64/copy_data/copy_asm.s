        .text
        .type copy_asm, %function
        .global copy_asm
        /*
        * Loads 2x64bit of data from one location and stores it at another.
        *
        * @param x0: address from where we load the data.
        * @param x1: address to which we store the data.
        */
copy_asm:
        eor x2, x2, x2
        ldr w2, [x0, #0*4]
        str w2, [x1, #0*8] 

        ldr w2, [x0, #1*4] 
        str w2, [x1, #1*8] 

        ldr w2, [x0, #2*4] 
        str w2, [x1, #2*8]

        ldr w2, [x0, #3*4] 
        str w2, [x1, #3*8]

        ldr w2, [x0, #4*4] 
        str w2, [x1, #4*8] 

        ldr w2, [x0, #5*4] 
        str w2, [x1, #5*8]

        ldr w2, [x0, #6*4] 
        str w2, [x1, #6*8] 

        ret
        .size   copy_asm, (. - copy_asm)
