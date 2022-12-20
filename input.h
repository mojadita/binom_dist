/* input.h -- input data parsing functions.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Tue Dec 20 08:48:55 EET 2022
 * Copyright: (c) 2022 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#ifndef _INPUT_H
#define _INPUT_H

unsigned get_unsigned(
		const char *str,  /* string to parse */
		unsigned    dflt, /* default value assumed in error */
		const char *fmt,  /* error message format */
		...);             /* ... and arguments */

double get_double(
		const char *str,  /* string to parse */
		double      dflt, /* default value assumed in error */
		const char *fmt,  /* error message format */
		...);             /* ... and arguments */

#endif /* _INPUT_H */
