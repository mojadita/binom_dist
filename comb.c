/* comb.c -- combinatorial numbers.
 * Author: Luis Colorado <luis.colorado@gmail.com>
 * Date: Fri Dec 16 16:00:11 EET 2022
 * Copyright: (c) Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#include "comb.h"

uint64_t comb(unsigned n, unsigned m)
{
	{   /* preliminaries */
		assert(n > 0 && m <= n);
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
	 * ...
	 * (n,0) (n,1)  ... (n,n-1) (n,1) [1,n,...,n,1]
	*/
	if (n <= 1 || m == 1) return 1;
	switch (m) {
	case 0: return 1;
	case 1: return n;
	} /* switch */

	uint64_t *l_a = calloc((m + 1) << 1, sizeof lst[0]),
			 *l_b = l_a + m + 1;
	l_a[0] = n;
	for (int i = 1; i <= m; i++) {
