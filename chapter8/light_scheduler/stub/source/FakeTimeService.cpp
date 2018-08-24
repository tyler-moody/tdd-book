#include "FakeTimeService.hpp"

FakeTimeService::FakeTimeService() : 
    minute(TIME_UNKNOWN),
    day(Day::DAY_UNKNOWN) {
}

void FakeTimeService::getTime(Time& t){
    t.minuteOfDay = minute;
    t.dayOfWeek = day;
}

void FakeTimeService::setPeriodicAlarm(){
}

void FakeTimeService::setMinute(Minute m){
    minute = m;
}

void FakeTimeService::setDay(Day d){
    day = d;
}
