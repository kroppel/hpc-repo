        .text
        .type load_store_2, %function
        .global load_store_2
        /*
        * Loads 2x64bit of data from one location and stores it at another.
        *
        * @param x0: address from where we load the data.
        * @param x1: address to which we store the data.
        */
load_store_2:
        ldp x2, x3, [x0] // -> assembles to 'a940 0c22'
        stp x2, x3, [x1] // -> assembles to 'a900 03c0'

        ret
        .size   load_store_2, (. - load_store_2)
        