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
        ldp x2, x3, [x0] // -> assembles to 'a940 0c22'
        stp x2, x3, [x1] // -> assembles to 'a900 03c0'

        // Show that CMP and SUBS are aliases
        CMP x2, x3
        SUBS xzr, x2, x3

        ret
        .size   copy_asm, (. - copy_asm)