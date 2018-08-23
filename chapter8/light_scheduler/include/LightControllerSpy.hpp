#ifndef _LightControllerSpy_h
#define _LightControllerSpy_h

#include "LightController.hpp"

light_id_t LightControllerSpy_GetLastId();

typedef enum {LIGHT_STATE_UNKNOWN, LIGHT_ON, LIGHT_OFF} light_state_t;

light_state_t LightControllerSpy_GetLastState();

#endif
