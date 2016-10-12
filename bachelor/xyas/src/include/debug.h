#ifndef __XYAS_DEBUG_H__
#define __XYAS_DEBUG_H__
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
enum {
    XYAS_OK = 0,
    XYAS_NOT_FOUND = 1000,
    XYAS_NO_TABLE,
    XYAS_NO_CONFIG,
    XYAS_NOT_SUPPORT,
};

#ifdef __XYAS_DEBUG__

#define debug_where() \
    printf("###FILE: %-16s ###LINE: %-4d ###FUC: %s\n", \
                    __FILE__, __LINE__, __FUNCTION__);
static inline void debug_print(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
#else
#define debug_where() 
static inline void debug_print(const char *format, ...)
{
}
#endif

#endif
