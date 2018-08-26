#include <stdarg.h>
#include <stdio.h>
#include "FormatOutput.h"

/*
static int FormatOutput_Impl(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    return 0;
}
*/

int (*FormatOutput)(const char* fmt, ...) = printf;
