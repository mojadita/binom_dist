/* bin_dist.c -- simulator of a binomial distribution.
 * Author: Luis Colorado <luis.colorado@gmail.com>
 * Date: Fri Dec 16 14:50:15 EET 2022
 * Copyright: (c) 2022 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define DEF_N                (100)
#define DEF_n                 (10)
#define DEF_p                (0.5)

unsigned N = DEF_N,
		 n = DEF_n;
double   p = DEF_p;

double *prob_table = NULL;

unsigned long comb(int n, int c);

int
main(int argc, char **argv)
{
	int opt;
	while ((opt = getopt(argc, argv, "N:n:p:")) != EOF) {
		switch (opt) {
		case 'N': /* number of experiment repetitions */
		case 'n': /* number of coins to toss in each exp. */
		case 'p': /* probability of getting head (1.0 - p) will
				   * be the probability of getting other. */

	} /* while */

	/* allocate probabilities */
	prob_table = calloc(n, sizeof *prob_table);

	double accum_prob = 0.0;

	int total_cases = pow(2.0, n);

	for (int c = 0; c < n; c++) { /* probability of exactly c coins */
		double prob = comb(n, c)
					* pow(p, c)
					* pow(p, n - c)
					/ total_cases;
		accum_prob += prob;
		printf("prob(c == %d) = %0.12g\n", c, accum_prob);
	}
	printf("proc_table[%d] = 1.0\n", n);

} /* main */


unsigned getint(char *s, )
{
	int result = -1;
	if (sscanf(s, "%u", &result) != 1) {
		
	}

		
