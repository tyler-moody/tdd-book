//- Copyright (c) 2018 James Grenning -- See license.txt at https://github.com/jwgrenning/wingman-cyber-dojo

#include <memory>
#include <vector>
#include "CppUTest/TestHarness.h"
#include "CircularBuffer.h"


// Everything in the test group is available
// to associated test cases
TEST_GROUP(CircularBuffer)
{
    std::shared_ptr<CircularBuffer> circularBuffer = nullptr;
    const unsigned int capacity = 10;
    const int emptyValue = -1;

    void setup() {
        circularBuffer = std::make_shared<CircularBuffer>(capacity, emptyValue);
    }

    void teardown() {
    }
};

TEST(CircularBuffer, DefaultValue){
    LONGS_EQUAL(emptyValue, circularBuffer->get());
}

TEST(CircularBuffer, ReportCapacity) {
    LONGS_EQUAL(10, circularBuffer->capacity());
}

TEST(CircularBuffer, PutGetSingle) {
    circularBuffer->put(5);
    LONGS_EQUAL(5, circularBuffer->get());
}

TEST(CircularBuffer, PutGetMultiple) {
    std::vector<int> numbers = {1,3,5,7,9};
    for (auto x: numbers) {
        circularBuffer->put(x);
        LONGS_EQUAL(x, circularBuffer->get());
    }
}

TEST(CircularBuffer, FIFO) {
    circularBuffer->put(1);
    circularBuffer->put(1);
    circularBuffer->put(2);
    circularBuffer->put(3);
    circularBuffer->put(5);
    LONGS_EQUAL(1, circularBuffer->get());
    LONGS_EQUAL(1, circularBuffer->get());
    LONGS_EQUAL(2, circularBuffer->get());
    LONGS_EQUAL(3, circularBuffer->get());
    LONGS_EQUAL(5, circularBuffer->get());
}

TEST(CircularBuffer, isEmpty){
    CHECK_TRUE(circularBuffer->isEmpty());
    circularBuffer->put(5);
    CHECK_FALSE(circularBuffer->isEmpty());
}

void fill(std::shared_ptr<CircularBuffer> cb, size_t capacity, int value){
    for (size_t i = 0; i < capacity; ++i){
        cb->put(value);
    }
}

TEST(CircularBuffer, isFull){
    CHECK_FALSE(circularBuffer->isFull());
    fill(circularBuffer, capacity, 5);
    CHECK_TRUE(circularBuffer->isFull());
}

TEST(CircularBuffer, PutToFullDoesntModify){
    fill(circularBuffer, capacity, 5);
    CHECK_FALSE(circularBuffer->put(6));
    for (size_t i = 0; i < capacity; ++i){
        LONGS_EQUAL(5, circularBuffer->get());
    }
    CHECK_TRUE(circularBuffer->isEmpty());
}

TEST(CircularBuffer, GetWhenEmptyIsDefault){
    LONGS_EQUAL(emptyValue, circularBuffer->get());

    circularBuffer->put(2);
    circularBuffer->get();
    LONGS_EQUAL(emptyValue, circularBuffer->get());
}

/*
TEST(CircularBuffer, test_with_all_the_macros_you_should_need_for_this_exercise)
{
    LONGS_EQUAL(capacity, 10);
    LONGS_EQUAL(emptyValue, -1);
    CHECK(buffer != 0);
    CHECK(true);
    CHECK_TRUE(true);
    CHECK_FALSE(false);
}
*/
