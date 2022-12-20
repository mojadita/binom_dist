/* comb.c -- combinatorial numbers.
 * Author: Luis Colorado <luis.colorado@gmail.com>
 * Date: Fri Dec 16 16:00:11 EET 2022
 * Copyright: (c) Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "comb.h"

double comb(unsigned n, unsigned m)
{
    {   /* preliminaries */
        assert(m <= n);
        unsigned n_minus_m = n - m;
        if (n_minus_m < m) {
            m = n_minus_m;
        }
    } /* block */

    /* simple cases: This covers cases
     *              (0,0)                  [1]
     *          (1,0) (1,1)               [1,1]
     *       (2,0) (2,1) (2,2)           [1,2,1]
     *    (3,0) (3,1) (3,2) (3,3)       [1,3,3,1]
     * (4,0) (4,1)  ...  (4,3) (4,4)   [1,4,.,4,1]
     *(5,0) (5,1) ... ... (5,4) (5,5) [1,5,...,5,1]
     * ...
     * (n,0) (n,1)  ... (n,n-1) (n,1) [1,n,...,n,1]
     * (we work only on the ellipsis zone of the triangle)
     */
    if (n < 2 || m == 0) return 1;
    if (m == 1) return n;

    n -= 4; m -= 1;

    static const double initial[] = { 6.0, 4.0, 1.0 };
    double *l      = calloc(m, sizeof l[0]),
           *l_prev = calloc(m, sizeof l_prev[0]);
    for (unsigned i = 0; i < 3; i++) {
        l[i] = initial[i];
    }


    for (unsigned i = 0; i < n; i++) {
        /* exchange the lists */
        double *l_temp = l;
        l = l_prev; l_prev = l_temp;

        /* calculate the list elements */
        l[0] = l_prev[0] + i + 4.0;
        for (unsigned j = 1; j < m; j++) {
            l[j] = l_prev[j] + l_prev[j-1];
        }
    }
    double result = l[m-1];
    free(l); free(l_prev);
    return result;
} /* comb */
