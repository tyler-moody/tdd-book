#ifndef _FormatOutputSpy_h
#define _FormatOutputSpy_h

#include <cstddef>

void FormatOutputSpy_Create(size_t length);
void FormatOutputSpy_Destroy();

int FormatOutputSpy(const char* fmt, ...);

const char* FormatOutputSpy_GetOutput();

#endif
