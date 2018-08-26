#include <cstdarg>
#include <cstdio>
#include <cstring>
#include "FormatOutput.h"
#include "FormatOutputSpy.h"

static char* buffer = nullptr;
static size_t length = 0;
static size_t offset = 0;

void FormatOutputSpy_Create(size_t len){
    length = len+1;
    buffer = new char[length];
    memset(buffer, 0, length);
    offset = 0;
}

void FormatOutputSpy_Destroy(){
    if (buffer != nullptr){
        delete[] buffer;
        buffer = nullptr;
    }
}

int FormatOutputSpy(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    size_t written = vsnprintf(buffer+offset, length-offset, fmt, args);
    va_end(args);
    offset += written;
    return written;
}

const char* FormatOutputSpy_GetOutput(){
    return buffer;
}
