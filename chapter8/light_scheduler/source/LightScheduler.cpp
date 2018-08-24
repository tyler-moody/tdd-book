#include "LightScheduler.hpp"

LightScheduler::LightScheduler(TimeService* ts, LightController* lc) :
    timeService(ts),
    lightController(lc) {
    scheduledEvent.id = LightController::UNUSED_ID;
}

void LightScheduler::processEventDueNow(const Time& time, const ScheduledLightEvent& lightEvent){
    if (lightEvent.id == LightController::UNUSED_ID){
        return;
    } 
    if (lightEvent.minuteOfDay != time.minuteOfDay){
        return;
    }

    operateLight(lightEvent);
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
    scheduledEvent.event = event;
}
