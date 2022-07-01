        .text
        .align 4
        .type fmlalx, %function
        .global fmlalx

fmlalx:
        ldr z0, [x0]
        ldr z1, [x1]
        ldr z2, [x2]

        fmlalb z2.s, z1.h, z0.h
        fmlalt z2.s, z1.h, z0.h

        str z2, [x2]

        ret
        .size fmlalx, (. - fmlalx)
