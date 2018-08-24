#ifndef _FakeTimeService_h
#define _FakeTimeService_h

#include "TimeService.hpp"

class FakeTimeService final: public TimeService {
    public:
        FakeTimeService();
        void getTime(Time& t);
        void setPeriodicAlarm();
        void setDay(Day d);
        void setMinute(Minute m);
    private:
        Minute minute;
        Day day;
};

#endif
