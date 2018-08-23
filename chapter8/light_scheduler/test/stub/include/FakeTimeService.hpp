#ifndef _FakeTimeService_h
#define _FakeTimeService_h

#include "TimeService.hpp"

class FakeTimeService: public TimeService {
    public:
        void getTime(Time* t);
        void setPeriodicAlarm();
        void reset();
        void setDay(Day d);
        void setMinute(Minute m);
    private:

};

#endif
