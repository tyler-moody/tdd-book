#ifndef _CircularBuffer_h
#define _CircularBuffer_h

#include <cstddef>

typedef enum {FAILURE=0, SUCCESS} status_t;

typedef struct CircularBuffer_t* CircularBuffer;

// typedef struct CircularBuffer_t* CircularBuffer;

void CircularBuffer_create(CircularBuffer c);

size_t CircularBuffer_getCapacity(CircularBuffer c);

size_t CircularBuffer_getSize(CircularBuffer c);

status_t CircularBuffer_setCapacity(CircularBuffer c, size_t capacity);

status_t CircularBuffer_insert(CircularBuffer c, int i);

status_t CircularBuffer_remove(CircularBuffer c, int* pInt);


#endif
