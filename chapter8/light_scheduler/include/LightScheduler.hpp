#ifndef _LightScheduler_h
#define _LightScheduler_h

#include "LightController.hpp"
#include "TimeService.hpp"

class LightScheduler {
    public:
        LightScheduler(TimeService* ts, LightController* lc);

        void scheduleTurnOn(LightController::Id light_id, Day day, Minute minute);

        void scheduleTurnOff(LightController::Id light_id, Day day, Minute minute);

        void removeSchedule();

        void wakeUp();


    private:
        TimeService* timeService;
        LightController* lightController;

        enum class Event {TURN_ON, TURN_OFF};
        typedef struct {
            unsigned int id;
            Minute minuteOfDay;
            Event event;
        } ScheduledLightEvent;

        ScheduledLightEvent scheduledEvent;
};

#endif
