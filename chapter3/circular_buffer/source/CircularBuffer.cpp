#include "CircularBuffer.h"

static size_t capacity;
static size_t size;

void CircularBuffer_create(CircularBuffer c){
    capacity = 0;
    size = 0;
}

size_t CircularBuffer_getCapacity(CircularBuffer c){
    return capacity;
}

size_t CircularBuffer_getSize(CircularBuffer c){
    return size;
}

status_t CircularBuffer_setCapacity(CircularBuffer c, size_t newCapacity){
    capacity = newCapacity;
    return SUCCESS;
}

status_t CircularBuffer_insert(CircularBuffer c, int i){
    size += 1;
    return SUCCESS;
}

status_t CircularBuffer_remove(CircularBuffer c, int* i){
    size -= 1;
    return SUCCESS;
}
