/* bin_dist.c -- simulator of a binomial distribution.
 * Author: Luis Colorado <luis.colorado@gmail.com>
 * Date: Fri Dec 16 14:50:15 EET 2022
 * Copyright: (c) 2022 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <fcntl.h>
#include <errno.h>
#include <getopt.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "log.h"
#include "input.h"
#include "comb.h"

#define FLAG_SHOW_TABLE_ACCUM (1 << 0)
#define FLAG_SHOW_TABLE_BINOM (1 << 1)
#define FLAG_SHOW_MATCHING    (1 << 2)
#define FLAG_SHOW_HISTOGRAM   (1 << 3)
#define FLAG_DRY_RUN		  (1 << 4)

#define DEF_N                    (100)
#define DEF_n                     (10)
#define DEF_p                    (0.5)
#define DEF_COLS			      (80)

unsigned N = DEF_N,
         n = DEF_n;
double   p = DEF_p;

double *prob_table = NULL;

int
main(int argc, char **argv)
{
    int opt;
	int flags = 0;
	unsigned num_columns = DEF_COLS;
    while ((opt = getopt(argc, argv, "abc:dhmN:n:p:")) != EOF) {
        switch (opt) {

		case 'a': /* print table of accumulated probabilities */
			flags |= FLAG_SHOW_TABLE_ACCUM;
			break;

		case 'b': /* print table of binomial probabilities */
			flags |= FLAG_SHOW_TABLE_BINOM;
			break;

		case 'c': /* num columns of output */
			num_columns = get_unsigned(optarg, DEF_COLS,
					"error parsing unsigned num of columns, "
					"assuming default (%u)\n", DEF_COLS);

		case 'd': /* dry run, don't output samples */
			flags |= FLAG_DRY_RUN;
			break;

		case 'h': /* print histogram */
			flags |= FLAG_SHOW_HISTOGRAM;
			break;

		case 'm': /* print how number of coins is determined */
			flags |= FLAG_SHOW_MATCHING;
			break;

        case 'N': /* number of experiment repetitions */
            N = get_unsigned(optarg, DEF_N,
                    "error parsing unsigned experiment repetitions, "
                    "assuming default (%u)\n",
                    DEF_N);
            break;

        case 'n': /* number of coins to toss in each exp. */
            n = get_unsigned(optarg, DEF_n,
                    "error parsing unsigned number of coins to toss, "
                    "assuming default (%u)\n",
                    DEF_n);
            break;

        case 'p': /* probability of getting heads (1.0 - p) will
                   * be the probability of getting tails. */
            p = get_double(optarg, DEF_p,
                    "error parsing double probability value, "
                    "assuming default (%g)\n",
                    DEF_p); break;

        } /* switch */
    } /* while */

	/* initialize random number generator */
	unsigned short seed[3];
	static const char *const dev = "/dev/urandom";
	int fd = open(dev, O_RDONLY);
	if (fd < 0) {
		ERR(EXIT_FAILURE,
			"open: %s: %s\n",
			dev, strerror(errno));
	}
	int res = read(fd, &seed, sizeof seed);
	if (res < 0) {
		ERR(EXIT_FAILURE,
			"read: %s: %s\n",
			dev, strerror(errno));
	}
	if (res < sizeof seed) {
		ERR(EXIT_FAILURE,
			"read: %s: incomplete read\n",
			dev);
	}
	close(fd);
	seed48(seed);

    /* allocate probabilities */
    prob_table = calloc(n + 1, sizeof *prob_table);
	unsigned *histogram = calloc(n + 1, sizeof *histogram);

    double accum_prob = 0.0;

    for (int i = 0; i < n; i++) {
		/* probability of exactly i coins */
        double prob = comb(n, i)
                    * pow(p, i)
                    * pow(1.0 - p, n - i);
        accum_prob += prob;  /* accumulate. */
        prob_table[i] = accum_prob;
		/* probability of P[ x <= i ] */
		if (flags & FLAG_SHOW_TABLE_ACCUM) {
			printf("P[x <= %d] = %g\n", i, prob_table[i]);
		} else if (flags & FLAG_SHOW_TABLE_BINOM) {
			printf("P[x == %d] = %g\n", i, prob);
		}
	} /* for */

	unsigned most_frequent = 0;

	/* repeat N experiments: */
	for (int i = 0; i < N; i++) {
		double x = drand48();
		int p;
		if (x <= prob_table[0]) {
			p = 0;
			if (flags & FLAG_SHOW_MATCHING) {
				printf("x(%lg) <= prob_table[0](%lg) --> p=0\n",
					   x, prob_table[0]);
			}
		} else if (x > prob_table[n-1]) {
			p = n;
			if (flags & FLAG_SHOW_MATCHING) {
				printf("prob_table[%d](%lg) < x(%lg) --> p=%d\n",
					   n-1, prob_table[n-1], x, p);
			}
		} else {
			/* (x > prob_table[0]) && (x <= prob_table[n-1]) */
			int l = 0, r = n-1;
			do {
				if (flags & FLAG_SHOW_MATCHING) {
					printf("prob_table[l=%d](%lg) < x(%lg) "
						   "<= prob_table[r=%d](%lg)",
						   l, prob_table[l], x, r, prob_table[r]);
				}
				p = (l + r) >> 1;
				if (x <= prob_table[p]) {
					r = p;
				} else { /* x > prob_table[p] */
					l = p;
				}
				if (flags & FLAG_SHOW_MATCHING) {
					printf(" --> l=%d, r=%d\n", l, r);
				}
			} while (l + 1 < r);
			p = r;
		}
		if (!(flags & FLAG_DRY_RUN)) {
			printf("%d\n", p);
		}
		histogram[p]++;
		if (most_frequent < histogram[p]) {
			most_frequent = histogram[p];
		}
	} /* for */

	if (flags & FLAG_SHOW_HISTOGRAM) {
		/* print the histogram */
		for (int i = 0; i <= n; ++i) {
			if (histogram[i] > 0) {
				/* only print the values > 0 */
				printf("%4d:", i);
				size_t n = (histogram[i] * num_columns
						 + (most_frequent >> 1))
						 / most_frequent;
				for (int j = 0; j < n; ++j) {
					fputc('#', stdout);
				}
				printf("<%u>\n", histogram[i]);
			}
		}
	}

} /* main */
