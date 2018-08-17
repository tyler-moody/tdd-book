#include "CircularBuffer.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(CircularBuffer)
{
    CircularBuffer c;

    void setup(){
        CircularBuffer_create(c);
    }

    void teardown(){
    }
};

TEST(CircularBuffer, ZeroCapacityAfterCreate){
    LONGS_EQUAL(0, CircularBuffer_getCapacity(c));
}

TEST(CircularBuffer, SetCapacityToFive){
    status_t status = CircularBuffer_setCapacity(c, 5);
    LONGS_EQUAL(SUCCESS, status);
}

TEST(CircularBuffer, CapacityIsUpdatedBySet){
    size_t expected = 7;
    status_t status = CircularBuffer_setCapacity(c, 7);
    LONGS_EQUAL(expected, CircularBuffer_getCapacity(c));
}

TEST(CircularBuffer, SizeIncrementsOnInsert){
    size_t initial = CircularBuffer_getSize(c);
    status_t status = CircularBuffer_insert(c, 3);
    LONGS_EQUAL(initial+1, CircularBuffer_getSize(c));
}

TEST(CircularBuffer, SizeDecrementsOnRemove){
    size_t initial = CircularBuffer_getSize(c);
    int output;
    status_t status = CircularBuffer_remove(c, &output);
    LONGS_EQUAL(initial-1, CircularBuffer_getSize(c));
}
