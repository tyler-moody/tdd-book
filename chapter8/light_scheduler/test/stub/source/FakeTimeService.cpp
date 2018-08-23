#include "FakeTimeService.hpp"

static Minute minute = TIME_UNKNOWN;
static Day day = Day::DAY_UNKNOWN;

void FakeTimeService::getTime(Time* time){
    time->minuteOfDay = minute;
    time->dayOfWeek = day;
}

void FakeTimeService::setPeriodicAlarm(){
}

void FakeTimeService::reset(){
    minute = TIME_UNKNOWN;
    day = Day::DAY_UNKNOWN;
}

void FakeTimeService::setMinute(Minute m){
    minute = m;
}

void FakeTimeService::setDay(Day d){
    day = d;
}
