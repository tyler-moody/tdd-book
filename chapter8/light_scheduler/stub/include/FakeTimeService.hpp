#ifndef _FakeTimeService_h
#define _FakeTimeService_h

#include "TimeService.hpp"

class FakeTimeService final: public TimeService {
    public:
        FakeTimeService();
        void getTime(Time& t);
        void setPeriodicAlarm(unsigned int period, callback_t callback);
        void cancelPeriodicAlarm(callback_t callback);
        void setDay(Day d);
        void setMinute(Minute m);
        TimeService::callback_t getAlarmCallback();
        unsigned int getAlarmPeriod();
    private:
        Minute minute;
        Day day;
        callback_t callback;
        unsigned int period;
};

#endif
