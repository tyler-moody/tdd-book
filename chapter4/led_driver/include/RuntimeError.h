#ifndef _RuntimeError_h
#define _RuntimeError_h

void RuntimeError(const char* message, int parameter,
                  const char* file, int line);

#define RUNTIME_ERROR(description, parameter)\
    RuntimeError(description, parameter, __FILE__, __LINE__)

#endif
