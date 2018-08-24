#ifndef _TimeService_h
#define _TimeService_h

enum class Day {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY, EVERYDAY, DAY_UNKNOWN};

typedef unsigned int Minute;

const Minute TIME_UNKNOWN = -1;

typedef struct {
    Minute minuteOfDay;
    Day dayOfWeek;
} Time;

class TimeService {
    public:
        virtual void getTime(Time& time) = 0;
        virtual void setPeriodicAlarm() = 0;
    private:
};

#endif
