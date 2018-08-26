#include "LightControllerSpy.hpp"

LightControllerSpy::LightControllerSpy() :
    lastId(UNKNOWN_ID),
    lastState(LightState::UNKNOWN)
{
}

void LightControllerSpy::On(Id id){
    lastId = id;
    lastState = LightState::ON;
}

void LightControllerSpy::Off(Id id){
    lastId =  id;
    lastState = LightState::OFF;
}

LightController::Id LightControllerSpy::getLastId(){
    return lastId;
}

LightControllerSpy::LightState LightControllerSpy::getLastState(){
    return lastState;
}
