#include "FakeTimeService.hpp"

static const unsigned int default_period = -1;
void default_callback(void){
    while(1){};
}

FakeTimeService::FakeTimeService() : 
    minute(TIME_UNKNOWN),
    day(Day::DAY_UNKNOWN),
    callback(std::bind(default_callback)),
    period(default_period){
}

void FakeTimeService::getTime(Time& t){
    t.minuteOfDay = minute;
    t.dayOfWeek = day;
}

void FakeTimeService::setPeriodicAlarm(unsigned int p, std::function<void(void)> cb){
    period = p;
    callback = cb;
}

void FakeTimeService::cancelPeriodicAlarm(callback_t callback){
    period = default_period;
    callback = std::bind(default_callback);
}

void FakeTimeService::setMinute(Minute m){
    minute = m;
}

void FakeTimeService::setDay(Day d){
    day = d;
}

TimeService::callback_t FakeTimeService::getAlarmCallback(){
    return callback;
}

unsigned int FakeTimeService::getAlarmPeriod(){
    return period;
}
