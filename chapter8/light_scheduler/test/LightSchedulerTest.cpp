#include <iostream>
#include <memory>
#include <typeinfo>
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
}

TEST(LightScheduler, ScheduleTuesdayButItsMonday){
    lightScheduler->scheduleEvent(3, Day::TUESDAY, 1200, Event::TURN_ON);
    setTimeTo(Day::MONDAY, 1200);

    lightScheduler->wakeUp();

    checkLightState(LightController::UNKNOWN_ID, LightControllerSpy::LightState::UNKNOWN);
}

TEST(LightScheduler, ScheduleTuesdayAndItsTuesday){
    lightScheduler->scheduleEvent(3, Day::TUESDAY, 1200, Event::TURN_ON);
    setTimeTo(Day::TUESDAY, 1200);

    lightScheduler->wakeUp();

    checkLightState(3, LightControllerSpy::LightState::ON);
}

TEST(LightScheduler, ScheduleWeekendItsFriday){
    lightScheduler->scheduleEvent(4, Day::WEEKEND, 1300, Event::TURN_OFF);
    setTimeTo(Day::FRIDAY, 1300);

    lightScheduler->wakeUp();

    checkLightState(LightController::UNKNOWN_ID, LightControllerSpy::LightState::UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekendItsSaturday){
    lightScheduler->scheduleEvent(4, Day::WEEKEND, 1300, Event::TURN_OFF);
    setTimeTo(Day::SATURDAY, 1300);

    lightScheduler->wakeUp();

    checkLightState(4, LightControllerSpy::LightState::OFF);
}

TEST(LightScheduler, ScheduleWeekendItsSunday){
    lightScheduler->scheduleEvent(5, Day::WEEKEND, 1300, Event::TURN_OFF);
    setTimeTo(Day::SUNDAY, 1300);

    lightScheduler->wakeUp();

    checkLightState(5, LightControllerSpy::LightState::OFF);
}

TEST(LightScheduler, ScheduleWeekendItsMonday){
    lightScheduler->scheduleEvent(6, Day::WEEKEND, 1300, Event::TURN_OFF);
    setTimeTo(Day::MONDAY, 1300);

    lightScheduler->wakeUp();

    checkLightState(LightController::UNKNOWN_ID, LightControllerSpy::LightState::UNKNOWN);
}

///////////////////////////////////////////////////////////////////////////////

TEST_GROUP(LightSchedulerInitAndCleanup){
    LightScheduler* lightScheduler;
    FakeTimeService* timeService;
    LightControllerSpy* lightController;

    void setup(){
        lightController = new LightControllerSpy();
        timeService = new FakeTimeService();
        lightScheduler = new LightScheduler(timeService, lightController);
    }

    void teardown(){
        delete lightScheduler;
        delete timeService;
        delete lightController;
    }
};

TEST(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm){
    // callback unchecked - std::function is not a comparable type
    LONGS_EQUAL(60, timeService->getAlarmPeriod());
}
