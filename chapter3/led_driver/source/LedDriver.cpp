#include "LedDriver.h"

static uint16_t *address;
void LedDriver_Create(uint16_t *addr){
    address = addr;
    *address = 0;
}

void LedDriver_TurnOn(int ledNumber){
    *address = 1;
}

void LedDriver_TurnOff(int ledNumber){
    *address = 0;
}
