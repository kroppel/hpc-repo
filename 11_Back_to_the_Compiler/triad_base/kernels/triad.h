#include <cstdint>

/**
 * A simple implementation of the triad c[:] = a[:] + 2.0f * b[:]
 *
 * @param i_nValues number of values in the arrays.
 * @param i_a pointer to array a.
 * @param i_b pointer to array b.
 * @param o_c pointer to array c.
 **/
void triad_simple( uint64_t         i_nValues,
                   float    const * i_a,
                   float    const * i_b,
                   float          * o_c );