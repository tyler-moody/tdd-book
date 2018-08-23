#include <memory>
#include "CppUTest/TestHarness.h"
#include "LightControllerSpy.hpp"
#include "LightScheduler.hpp"
#include "FakeTimeService.hpp"

TEST_GROUP(LightScheduler){
    std::unique_ptr<FakeTimeService> timeservice;
    std::unique_ptr<LightControllerSpy> lightController;

    void setup(){
        timeservice.reset(new FakeTimeService()); 
        lightController.reset(new LightControllerSpy());
    }

    void teardown(){
    }
};

TEST(LightScheduler, NoChangeToLightsDuringInitialization){
    LONGS_EQUAL(LightController::UNKNOWN_ID, lightController->getLastId());
    LONGS_EQUAL(LightControllerSpy::LightState::UNKNOWN, lightController->getLastState());
}

TEST(LightScheduler, NoScheduleNothingHappens){
    timeservice->setDay(Day::MONDAY);
    timeservice->setMinute(100);
    LightScheduler_WakeUp();
    LONGS_EQUAL(LightController::UNKNOWN_ID, lightController->getLastId());
    LONGS_EQUAL(LightControllerSpy::LightState::UNKNOWN, lightController->getLastState());
}

/*
IGNORE_TEST(LightScheduler, ScheduleOnEverydayNotTimeYet){
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1199);
    LightScheduler_WakeUp();

    LONGS_EQUAL(LightController::UNKNOWN_ID, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LightControllerSpy::LightState::UNKNOWN, LightControllerSpy_GetLastState());
}
*/
