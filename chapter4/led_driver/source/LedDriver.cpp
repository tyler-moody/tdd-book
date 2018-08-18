#include "LedDriver.h"
#include "RuntimeError.h"

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

enum {FIRST_LED = 1, LAST_LED = 16};
static bool LedIsOutOfBounds(int ledNumber){
    return ledNumber < FIRST_LED || ledNumber > LAST_LED;
}

static void setLedImageBit(int ledNumber){
    ledImage = ledImage | convertLedNumberToBit(ledNumber);
}

void LedDriver_TurnOn(int ledNumber){
    if (LedIsOutOfBounds(ledNumber)){
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
    } else {
        setLedImageBit(ledNumber);
        updateHardware();
    }
}

static void clearLedImageBit(int ledNumber){
    ledImage = ledImage & ~(convertLedNumberToBit(ledNumber));
}

void LedDriver_TurnOff(int ledNumber){
    if (LedIsOutOfBounds(ledNumber)){
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
    } else {
        clearLedImageBit(ledNumber);
        updateHardware();
    }
}

void LedDriver_TurnOnAll(){
    ledImage = ALL_LEDS_ON;
    updateHardware();
}

bool LedDriver_IsOn(int ledNumber){
    if (LedIsOutOfBounds(ledNumber)){
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
        return false;
    } else {
        return ledImage & convertLedNumberToBit(ledNumber);
    }
}

bool LedDriver_IsOff(int ledNumber){
    return !LedDriver_IsOn(ledNumber);;
}

void LedDriver_TurnOffAll(){
    ledImage = ALL_LEDS_OFF;
    updateHardware();
}
