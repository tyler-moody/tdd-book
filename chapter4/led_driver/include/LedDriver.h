#ifndef _LedDriver_h
#define _LedDriver_h

#include <stdint.h>

void LedDriver_Create(uint16_t *address);

void LedDriver_TurnOn(int ledNumber);

void LedDriver_TurnOnAll();

void LedDriver_TurnOff(int ledNumber);

void LedDriver_TurnOffAll();

bool LedDriver_IsOn(int ledNumber);

bool LedDriver_IsOff(int ledNumber);

#endif
