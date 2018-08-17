#include "LedDriver.h"

static uint16_t *address;
static uint16_t ledImage;

enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};

static void updateHardware(){
    *address = ledImage;
}

void LedDriver_Create(uint16_t *addr){
    address = addr;
    ledImage = ALL_LEDS_OFF;
    updateHardware();
}

static uint16_t convertLedNumberToBit(int ledNumber){
    return 1 << (ledNumber-1);
}

void LedDriver_TurnOn(int ledNumber){
    if (ledNumber <= 16 && ledNumber >= 1){
        ledImage = ledImage | convertLedNumberToBit(ledNumber);
        updateHardware();
    }
}

void LedDriver_TurnOff(int ledNumber){
    if (ledNumber <= 16 && ledNumber >= 1){
        ledImage = *address & ~(convertLedNumberToBit(ledNumber));
        updateHardware();
    }
}

void LedDriver_TurnOnAll(){
    ledImage = ALL_LEDS_ON;
    updateHardware();
}

