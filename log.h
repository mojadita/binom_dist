/* log.h -- log header file to support the logging
 *          features to come.
 * Author: Luis Colorado <luis.colorado@spindrive.fi>
 * Date: Tue Nov  8 10:26:41 EET 2022
 * Copyright: (c) 2022 SpinDrive Oy, FI.  All rights reserved.
 */
#ifndef _LOG_H
#define _LOG_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define F(F_fmt) "%s:%d:%s:" F_fmt, __FILE__, __LINE__, __func__

#define LOG_TAIL(_lvl, LT_fmt, ...) do {        \
        fprintf(stderr, LT_fmt, ##__VA_ARGS__); \
    } while (0)

#define ERR(_cod, E_fmt, ...) do {  \
        LOG_TAIL(LOG_ERROR,         \
                F("ERROR: " E_fmt), \
                ##__VA_ARGS__);     \
        if (_cod) exit(_cod);       \
    } while (0)

#define WRN(W_fmt, ...) do {        \
        LOG_TAIL(LOG_WARN,          \
                F("WARNG: " W_fmt), \
                ##__VA_ARGS__);     \
    } while (0)

#define INF(I_fmt, ...) do {        \
        LOG_TAIL(LOG_INFO,          \
                F("INFO: " I_fmt),  \
                ##__VA_ARGS__);     \
    } while (0)

#define DEB(I_fmt, ...) do {        \
        LOG_TAIL(LOG_DEBUG,         \
                F("DEBUG: " I_fmt), \
                ##__VA_ARGS__);     \
    } while (0)

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* _LOG_H */
