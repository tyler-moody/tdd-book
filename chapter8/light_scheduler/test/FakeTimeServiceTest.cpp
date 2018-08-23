#include "CppUTest/TestHarness.h"
#include "FakeTimeService.hpp"

TEST_GROUP(FakeTimeService){

    void setup(){
        FakeTimeService_Reset();
    }

    void teardown(){
    }
};

TEST(FakeTimeService, Create){
    Time time;
    TimeService_GetTime(&time);
    LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
    LONGS_EQUAL(DAY_UNKNOWN, time.dayOfWeek);
}

TEST(FakeTimeService, Set){
    Time time;
    unsigned int minute = 42;
    day_t day = SATURDAY;
    FakeTimeService_SetMinute(minute);
    FakeTimeService_SetDay(day);
    TimeService_GetTime(&time);
    LONGS_EQUAL(minute, time.minuteOfDay);
    LONGS_EQUAL(day, time.dayOfWeek);
}

