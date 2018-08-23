#include "LightControllerSpy.hpp"

static light_id_t last_id;
static light_state_t last_state;

void LightController_Create(){
    last_id = LIGHT_ID_UNKNOWN;
    last_state = LIGHT_STATE_UNKNOWN;
}

void LightController_Destroy(){
}

void LightController_On(light_id_t id){
    last_id = id;
    last_state = LIGHT_ON;
}

void LightController_Off(light_id_t id){
    last_id = id;
    last_state = LIGHT_OFF;
}

light_id_t LightControllerSpy_GetLastId(){
    return last_id;
}

light_state_t LightControllerSpy_GetLastState(){
    return last_state;
}
