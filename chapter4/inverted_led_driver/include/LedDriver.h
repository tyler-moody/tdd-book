#ifndef _LedDriver_h
#define _LedDriver_h

#include <stdint.h>

typedef enum {NORMAL, INVERTED} logic_t;

void LedDriver_Create(uint16_t *address, logic_t levels);

logic_t LedDriver_GetLevels();

void LedDriver_TurnOn(int ledNumber);

void LedDriver_TurnOnAll();

void LedDriver_TurnOff(int ledNumber);

void LedDriver_TurnOffAll();

bool LedDriver_IsOn(int ledNumber);

bool LedDriver_IsOff(int ledNumber);

#endif
