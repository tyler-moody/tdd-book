#ifndef _TimeService_h
#define _TimeService_h

#include <functional>

enum class Day {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY, EVERYDAY, WEEKDAY, WEEKEND, DAY_UNKNOWN};

typedef unsigned int Minute;

const Minute TIME_UNKNOWN = -1;

typedef struct {
    Minute minuteOfDay;
    Day dayOfWeek;
} Time;

class TimeService {
    public:
        typedef std::function<void(void)> callback_t;
        virtual void getTime(Time& time) = 0;
        virtual void setPeriodicAlarm(unsigned int period, callback_t callback) = 0;
        virtual void cancelPeriodicAlarm(callback_t callback) = 0;
    private:
};

#endif
