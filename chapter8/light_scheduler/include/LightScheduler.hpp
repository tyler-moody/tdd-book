#ifndef _LightScheduler_h
#define _LightScheduler_h

#include "LightController.hpp"
#include "TimeService.hpp"

enum class Event {TURN_ON, TURN_OFF};

class LightScheduler {
    public:
        LightScheduler(TimeService* ts, LightController* lc);
        ~LightScheduler();

        void scheduleEvent(LightController::Id light_id, Day day, Minute minute, Event event);

        void removeSchedule();

        void wakeUp();


    private:
        TimeService* timeService;
        LightController* lightController;

        typedef struct {
            unsigned int id;
            Minute minuteOfDay;
            Day day;
            Event event;
        } ScheduledLightEvent;

        ScheduledLightEvent scheduledEvent;

        void processEventDueNow(const Time& time, const ScheduledLightEvent& lightEvent);

        void operateLight(const ScheduledLightEvent& lightEvent);
};

#endif
