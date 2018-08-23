#ifndef _FakeTimeService_h
#define _FakeTimeService_h

#include "TimeService.hpp"

void FakeTimeService_Reset();

void FakeTimeService_SetDay(day_t day);

void FakeTimeService_SetMinute(unsigned int minute);

#endif
