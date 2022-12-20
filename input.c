/* input.c -- auxiliary parsing routines for command line
 * parameters.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Tue Dec 20 08:53:21 EET 2022
 * Copyright: (c) 2022 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "input.h"

unsigned get_unsigned(
        const char *str,  /* string to parse */
        unsigned    dflt, /* default value assumed in error */
        const char *fmt,  /* error message format */
        ...)              /* ... and arguments */
{
    unsigned ret_val = dflt;
    int res = sscanf(str, "%u", &ret_val);
    if (res != 1) {
        va_list p;
        va_start(p, fmt);
        ERR(0, "\"%s\": erroneous parse of unsigned: ", str);
        vfprintf(stderr, fmt, p);
        va_end(p);
    }
    return ret_val;
} /* get_unsigned */

double get_double(
        const char *str,  /* string to parse */
        double      dflt, /* default value assumed in error */
        const char *fmt,  /* error message format */
        ...)              /* ... and arguments */
{
    double ret_val = dflt;
    int res = sscanf(str, "%lg", &ret_val);
    if (res != 1) {
        va_list p;
        va_start(p, fmt);
        ERR(0, "\"%s\": erroneous parse of double: ", str);
        vfprintf(stderr, fmt, p);
        va_end(p);
    }
    return ret_val;
} /* get_double */
