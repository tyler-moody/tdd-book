#include <iostream>
#include <memory>
#include <typeinfo>
#include "CppUTest/TestHarness.h"
#include "LightControllerSpy.hpp"
#include "LightScheduler.hpp"
#include "FakeTimeService.hpp"
#include "FakeRandomMinute.h"

TEST_GROUP(LightScheduler){
    FakeTimeService* timeService;
    LightControllerSpy* lightController;
    RandomMinute* randomMinute;
    LightScheduler* lightScheduler;

    void setup(){
        timeService = new FakeTimeService();
        lightController = new LightControllerSpy();
        randomMinute = new RandomMinute(30);
        lightScheduler = new LightScheduler(timeService, lightController, randomMinute);
    }

    void teardown(){
        delete lightScheduler;
        delete lightController;
        delete timeService;
        delete randomMinute;
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

TEST_GROUP(LightSchedulerRandomize){
    FakeTimeService* timeService = nullptr;
    LightControllerSpy* lightController = nullptr;
    LightScheduler* lightScheduler = nullptr;
    FakeRandomMinute* randomMinute = nullptr;

    void setup(){
        timeService = new FakeTimeService();
        lightController = new LightControllerSpy();
        randomMinute = new FakeRandomMinute(30);
        lightScheduler = new LightScheduler(timeService, lightController, randomMinute);
    }

    void teardown(){
        delete lightScheduler;
        delete randomMinute;
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

TEST(LightSchedulerRandomize, TurnsOnEarly){
    randomMinute->SetFirstAndIncrement(-10, 5);
    lightScheduler->scheduleEvent(4, Day::EVERYDAY, 600, Event::TURN_ON);
    lightScheduler->randomize(4, Day::EVERYDAY, 600);
    setTimeTo(Day::MONDAY, 600-10);
    lightScheduler->wakeUp();
    checkLightState(4, LightControllerSpy::LightState::ON);
}
