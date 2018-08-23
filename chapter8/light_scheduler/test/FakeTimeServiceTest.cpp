#include <memory>
#include "CppUTest/TestHarness.h"
#include "FakeTimeService.hpp"

TEST_GROUP(FakeTimeService){
    std::unique_ptr<FakeTimeService> timeservice;

    void setup(){
        timeservice.reset(new FakeTimeService());
    }

    void teardown(){
    }
};

TEST(FakeTimeService, Create){
    Time time;
    timeservice->getTime(&time);
    LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
    LONGS_EQUAL(Day::DAY_UNKNOWN, time.dayOfWeek);
}

TEST(FakeTimeService, Set){
    Time time;
    unsigned int minute = 42;
    Day day = Day::SATURDAY;
    timeservice->setMinute(minute);
    timeservice->setDay(day);
    timeservice->getTime(&time);
    LONGS_EQUAL(minute, time.minuteOfDay);
    LONGS_EQUAL(day, time.dayOfWeek);
}
