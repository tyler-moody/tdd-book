#include "LightScheduler.hpp"

LightScheduler::LightScheduler(TimeService* ts, LightController* lc) :
    timeService(ts),
    lightController(lc) {
    scheduledEvent.id = LightController::UNUSED_ID;

    timeService->setPeriodicAlarm(60, std::bind(&LightScheduler::wakeUp, this));
}

LightScheduler::~LightScheduler(){
    timeService->cancelPeriodicAlarm(std::bind(&LightScheduler::wakeUp, this));
}

void LightScheduler::processEventDueNow(const Time& now, const ScheduledLightEvent& lightEvent){
    if (lightEvent.id == LightController::UNUSED_ID){
        return;
    } 
    if (lightEvent.minuteOfDay != now.minuteOfDay){
        return;
    }

    if ((lightEvent.day == Day::EVERYDAY) ||
            (lightEvent.day == now.dayOfWeek) ||
            (lightEvent.day == Day::WEEKEND && now.dayOfWeek == Day::SATURDAY) ||
            (lightEvent.day == Day::WEEKEND && now.dayOfWeek == Day::SUNDAY)
       ){
        operateLight(lightEvent);
    }
}

void LightScheduler::operateLight(const ScheduledLightEvent& lightEvent){
    if (lightEvent.event == Event::TURN_ON){
        lightController->On(lightEvent.id);
    } else if (lightEvent.event == Event::TURN_OFF){
        lightController->Off(lightEvent.id);
    }
}

void LightScheduler::wakeUp() {
    Time time;
    timeService->getTime(time);

    processEventDueNow(time, scheduledEvent);
}

void LightScheduler::scheduleEvent(LightController::Id light_id, Day day, Minute minute, Event event) {
    scheduledEvent.id = light_id;
    scheduledEvent.minuteOfDay = minute;
    scheduledEvent.day = day;
    scheduledEvent.event = event;
}
