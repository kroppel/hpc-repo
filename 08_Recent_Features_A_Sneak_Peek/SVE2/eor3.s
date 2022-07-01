        .text
        .align 4
        .type eor3, %function
        .global eor3

eor3:
        ldr z0, [x0]
        ldr z1, [x1]
        ldr z2, [x2]

        eor3 z2.s, z2.s, z0.s, z1.s

        str z2, [x2]

        ret
        .size eor3, (. - eor3)