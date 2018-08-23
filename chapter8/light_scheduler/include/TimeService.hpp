#ifndef _TimeService_h
#define _TimeService_h

typedef enum {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY, EVERYDAY, DAY_UNKNOWN} day_t;

const unsigned int TIME_UNKNOWN = -1;

typedef struct {
    unsigned int minuteOfDay;
    day_t dayOfWeek;
} Time;

void TimeService_GetTime(Time* time);

void TimeService_SetPeriodicAlarm();

#endif
