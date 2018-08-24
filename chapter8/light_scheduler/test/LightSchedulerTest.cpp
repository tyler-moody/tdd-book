#include <memory>
#include "CppUTest/TestHarness.h"
#include "LightControllerSpy.hpp"
#include "LightScheduler.hpp"
#include "FakeTimeService.hpp"

TEST_GROUP(LightScheduler){
    LightScheduler* lightScheduler;
    FakeTimeService* timeService;
    LightControllerSpy* lightController;

    void setup(){
        timeService = new FakeTimeService();
        lightController = new LightControllerSpy();
        lightScheduler = new LightScheduler(timeService, lightController);
    }

    void teardown(){
        delete lightScheduler;
        delete lightController;
        delete timeService;
    }
};

TEST(LightScheduler, NoChangeToLightsDuringInitialization){
    LONGS_EQUAL(LightController::UNKNOWN_ID, lightController->getLastId());
    LONGS_EQUAL(LightControllerSpy::LightState::UNKNOWN, lightController->getLastState());
}

TEST(LightScheduler, NoScheduleNothingHappens){
    timeService->setDay(Day::MONDAY);
    timeService->setMinute(100);
    lightScheduler->wakeUp();
    LONGS_EQUAL(LightController::UNKNOWN_ID, lightController->getLastId());
    LONGS_EQUAL(LightControllerSpy::LightState::UNKNOWN, lightController->getLastState());
}

TEST(LightScheduler, ScheduleOnEverydayNotTimeYet){
    lightScheduler->scheduleTurnOn(3, Day::EVERYDAY, 1200);
    timeService->setDay(Day::MONDAY);
    timeService->setMinute(1199);
    lightScheduler->wakeUp();

    LONGS_EQUAL(LightController::UNKNOWN_ID, lightController->getLastId());
    LONGS_EQUAL(LightControllerSpy::LightState::UNKNOWN, lightController->getLastState());
}

TEST(LightScheduler, ScheduleOnEverydayItsTime) {
    lightScheduler->scheduleTurnOn(3, Day::EVERYDAY, 1200);
    timeService->setDay(Day::MONDAY);
    timeService->setMinute(1200);

    lightScheduler->wakeUp();
    
    LONGS_EQUAL(3, lightController->getLastId());
    LONGS_EQUAL(LightControllerSpy::LightState::ON, lightController->getLastState());
}

TEST(LightScheduler, ScheduleOffEverydayItsTime) {
    lightScheduler->scheduleTurnOff(3, Day::EVERYDAY, 1200);
    timeService->setDay(Day::MONDAY);
    timeService->setMinute(1200);
    
    lightScheduler->wakeUp();

    LONGS_EQUAL(3, lightController->getLastId());
    LONGS_EQUAL(LightControllerSpy::LightState::OFF, lightController->getLastState());
}
