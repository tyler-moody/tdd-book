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

    void setTimeTo(Day day, Minute minute){
        timeService->setDay(day);
        timeService->setMinute(minute);
    }

    void checkLightState(LightController::Id id, LightControllerSpy::LightState level){
        LONGS_EQUAL(id, lightController->getLastId());
        LONGS_EQUAL(level, lightController->getLastState());
    }
};


TEST(LightScheduler, NoChangeToLightsDuringInitialization){
    checkLightState(LightController::UNKNOWN_ID, LightControllerSpy::LightState::UNKNOWN);
}

TEST(LightScheduler, NoScheduleNothingHappens){
    setTimeTo(Day::MONDAY, 100);

    lightScheduler->wakeUp();

    checkLightState(LightController::UNKNOWN_ID, LightControllerSpy::LightState::UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayNotTimeYet){
    lightScheduler->scheduleEvent(3, Day::EVERYDAY, 1200, Event::TURN_ON);
    setTimeTo(Day::MONDAY, 1199);

    lightScheduler->wakeUp();

    checkLightState(LightController::UNKNOWN_ID, LightControllerSpy::LightState::UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayItsTime) {
    lightScheduler->scheduleEvent(3, Day::EVERYDAY, 1200, Event::TURN_ON);
    setTimeTo(Day::MONDAY, 1200);

    lightScheduler->wakeUp();
    
    checkLightState(3, LightControllerSpy::LightState::ON);
}

TEST(LightScheduler, ScheduleOffEverydayItsTime) {
    lightScheduler->scheduleEvent(3, Day::EVERYDAY, 1200, Event::TURN_OFF);
    setTimeTo(Day::MONDAY, 1200);
    
    lightScheduler->wakeUp();

    checkLightState(3, LightControllerSpy::LightState::OFF);
    LONGS_EQUAL(3, lightController->getLastId());
    LONGS_EQUAL(LightControllerSpy::LightState::OFF, lightController->getLastState());
}
