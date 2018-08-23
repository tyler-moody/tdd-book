#ifndef _Controller_h
#define _Controller_h

typedef unsigned int light_id_t;
const light_id_t LIGHT_ID_UNKNOWN = -1;

void LightController_Create();

void LightController_Destroy();

void LightController_On(light_id_t id);

void LightController_Off(light_id_t id);

#endif
