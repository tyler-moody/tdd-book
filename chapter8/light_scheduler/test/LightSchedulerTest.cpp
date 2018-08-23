#include "CppUTest/TestHarness.h"
#include "LightControllerSpy.hpp"
#include "LightScheduler.hpp"
#include "FakeTimeService.hpp"

TEST_GROUP(LightScheduler){
    FakeTimeService timeservice;

    void setup(){
        LightController_Create();
    }

    void teardown(){
    }
};

TEST(LightScheduler, NoChangeToLightsDuringInitialization){
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, NoScheduleNothingHappens){
    timeservice.setDay(Day::MONDAY);
    timeservice.setMinute(100);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

/*
IGNORE_TEST(LightScheduler, ScheduleOnEverydayNotTimeYet){
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1199);
    LightScheduler_WakeUp();

    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}
*/
