#include "LightScheduler.hpp"

LightScheduler::LightScheduler(TimeService* ts, LightController* lc) :
    timeService(ts),
    lightController(lc) {
    scheduledEvent.id = LightController::UNUSED_ID;
}

void LightScheduler::wakeUp() {
    Time time;
    timeService->getTime(time);

    if (scheduledEvent.id == LightController::UNUSED_ID){
        return;
    } if (scheduledEvent.minuteOfDay != time.minuteOfDay){
        return;
    }

    if (scheduledEvent.event == Event::TURN_ON){
        lightController->On(scheduledEvent.id);
    } else if (scheduledEvent.event == Event::TURN_OFF){
        lightController->Off(scheduledEvent.id);
    }
}

void LightScheduler::scheduleTurnOn(LightController::Id light_id, Day day, Minute minute) {
    scheduledEvent.id = light_id;
    scheduledEvent.minuteOfDay = minute;
    scheduledEvent.event = Event::TURN_ON;
}

void LightScheduler::scheduleTurnOff(LightController::Id light_id, Day day, Minute minute) {
    scheduledEvent.id = light_id;
    scheduledEvent.minuteOfDay = minute;
    scheduledEvent.event = Event::TURN_OFF;
}
