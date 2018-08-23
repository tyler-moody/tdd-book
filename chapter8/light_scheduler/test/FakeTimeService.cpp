#include "FakeTimeService.hpp"

static unsigned int _minute = TIME_UNKNOWN;
static day_t _day = DAY_UNKNOWN;

void TimeService_GetTime(Time* time){
    time->minuteOfDay = _minute;
    time->dayOfWeek = _day;
}

void FakeTimeService_Reset(){
    _minute = TIME_UNKNOWN;
    _day = DAY_UNKNOWN;
}

void FakeTimeService_SetMinute(unsigned int minute){
    _minute = minute;
}

void FakeTimeService_SetDay(day_t day){
    _day = day;
}
