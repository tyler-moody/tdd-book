#ifndef _LightScheduler_h
#define _LightScheduler_h

#include "LightController.hpp"
#include "TimeService.hpp"

void LightScheduler_ScheduleTurnOn(light_id_t light_id, Day day, Minute minute);

void LightScheduler_RemoveSchedule();

void LightScheduler_WakeUp();

#endif
