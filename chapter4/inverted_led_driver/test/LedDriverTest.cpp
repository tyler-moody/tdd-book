#include "CppUTest/TestHarness.h"
#include "LedDriver.h"
#include "RuntimeErrorStub.h"

static uint16_t logicLevelsToHardwareLevels(uint16_t reg){
    if (LedDriver_GetLevels() == INVERTED){
        return ~reg;
    }
    return reg;
}

TEST_GROUP(LedDriver){
    uint16_t leds;
    logic_t levels = NORMAL;

    void setup()
    {
        LedDriver_Create(&leds, levels);
    }

    void teardown()
    {
    }
};

TEST_GROUP(LedDriverInverted){
    uint16_t leds;
    logic_t levels = INVERTED;

    void setup(){
        LedDriver_Create(&leds, levels);
    }

    void teardown(){
    }
};

void LedsOffAfterCreate(uint16_t& leds, const logic_t& levels){
    leds = logicLevelsToHardwareLevels(0xffff);
    LedDriver_Create(&leds, levels);
    LONGS_EQUAL(logicLevelsToHardwareLevels(0), leds);
}

TEST(LedDriver, T_LedsOffAfterCreate){
    LedsOffAfterCreate(leds, levels);
}

TEST(LedDriverInverted, T_LedsOffAfterCreate){
    LedsOffAfterCreate(leds, levels);
}

void TurnOnLedOne(const uint16_t& leds){
    LedDriver_TurnOn(1);
    LONGS_EQUAL(logicLevelsToHardwareLevels(1), leds);
}

TEST(LedDriver, T_TurnOnLedOne){
    TurnOnLedOne(leds);
}

TEST(LedDriverInverted, T_TurnOnLedOne){
    TurnOnLedOne(leds);
}

void TurnOffLedOne(const uint16_t& leds){
    LONGS_EQUAL(logicLevelsToHardwareLevels(0), leds);
    LedDriver_TurnOn(1);
    LONGS_EQUAL(logicLevelsToHardwareLevels(1), leds);
    LedDriver_TurnOff(1);
    LONGS_EQUAL(logicLevelsToHardwareLevels(0), leds);
}

TEST(LedDriver, T_TurnOffLedOne){
    TurnOffLedOne(leds);
}

TEST(LedDriverInverted, T_TurnOffLedOne){
    TurnOffLedOne(leds);
}

void TurnOnMultipleLeds(const uint16_t& leds){
    LedDriver_TurnOn(9);
    LedDriver_TurnOn(8);
    LONGS_EQUAL(logicLevelsToHardwareLevels(0x180), leds);
}

TEST(LedDriver, T_TurnOnMultipleLeds){
    TurnOnMultipleLeds(leds);
}

TEST(LedDriverInverted, T_TurnOnMultipleLeds){
    TurnOnMultipleLeds(leds);
}

void AllOn(uint16_t& leds){
    LedDriver_TurnOnAll();
    LONGS_EQUAL(logicLevelsToHardwareLevels(0xffff), leds);
}

TEST(LedDriver, T_AllOn){
    AllOn(leds);
}

TEST(LedDriverInverted, T_AllOn){
    AllOn(leds);
}

void TurnOffAnyLed(const uint16_t& leds){
    LedDriver_TurnOnAll();
    LedDriver_TurnOn(8);
    LedDriver_TurnOff(8);
    LONGS_EQUAL(logicLevelsToHardwareLevels(0xff7f), leds);
}

TEST(LedDriver, T_TurnOffAnyLed){
    TurnOffAnyLed(leds);
}

TEST(LedDriverInverted, T_TurnOffAnyLed){
    TurnOffAnyLed(leds);
}

void LedMemoryNotReadable(uint16_t& leds){
    leds = logicLevelsToHardwareLevels(0xffff);
    LedDriver_TurnOn(8);
    LONGS_EQUAL(logicLevelsToHardwareLevels(0x0080), leds);

    leds = logicLevelsToHardwareLevels(0xffff);
    LedDriver_TurnOff(8);
    LONGS_EQUAL(logicLevelsToHardwareLevels(0x0000), leds);
}

TEST(LedDriver, T_LedMemoryNotReadable){
    LedMemoryNotReadable(leds);
}

TEST(LedDriverInverted, T_LedMemoryNotReadable){
    LedMemoryNotReadable(leds);
}

void UpperAndLowerBounds(const uint16_t& leds){
    LedDriver_TurnOn(1);
    LedDriver_TurnOn(16);
    LONGS_EQUAL(logicLevelsToHardwareLevels(0x8001), leds);
}

TEST(LedDriver, UpperAndLowerBounds){
    UpperAndLowerBounds(leds);
}

TEST(LedDriverInverted, UpperAndLowerBounds){
    UpperAndLowerBounds(leds);
}

void OutOfBoundsTurnOnDoesNoHarm(const uint16_t& leds){
    LedDriver_TurnOn(-1);
    LedDriver_TurnOn(0);
    LedDriver_TurnOn(17);
    LedDriver_TurnOn(3141);
    LONGS_EQUAL(logicLevelsToHardwareLevels(0), leds);
}

TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm){
    OutOfBoundsTurnOnDoesNoHarm(leds);
}

TEST(LedDriverInverted, OutOfBoundsTurnOnDoesNoHarm){
    OutOfBoundsTurnOnDoesNoHarm(leds);
}

void OutOfBoundsTurnOffDoesNoHarm(const uint16_t& leds){
    LedDriver_TurnOnAll();
    LedDriver_TurnOff(-1);
    LedDriver_TurnOff(0);
    LedDriver_TurnOff(17);
    LedDriver_TurnOff(3141);
    LONGS_EQUAL(logicLevelsToHardwareLevels(0xffff), leds);
}

TEST(LedDriver, OutOfBoundTurnOffDoesNoHarm){
    OutOfBoundsTurnOffDoesNoHarm(leds);
}

TEST(LedDriverInverted, OutOfBoundTurnOffDoesNoHarm){
    OutOfBoundsTurnOffDoesNoHarm(leds);
}
void OutOfBoundsProducesRuntimeError(){
    LedDriver_TurnOn(-1);
    STRCMP_EQUAL("LED Driver: out-of-bounds LED",
            RuntimeErrorStub_getLastError());
    LONGS_EQUAL(-1, RuntimeErrorStub_getLastParameter());
}

TEST(LedDriver, OutOfBoundsProducesRuntimeError){
    OutOfBoundsProducesRuntimeError();
}

TEST(LedDriverInverted, OutOfBoundsProducesRuntimeError){
    OutOfBoundsProducesRuntimeError();
}
    
void IsOn(){
    CHECK_FALSE(LedDriver_IsOn(11));
    LedDriver_TurnOn(11);
    CHECK_TRUE(LedDriver_IsOn(11));
}
    
TEST(LedDriver, IsOn){
    IsOn();
}

TEST(LedDriverInverted, IsOn){
    IsOn();
}

void OutOfBoundsLedsAreAlwaysOff(){
    CHECK_TRUE(LedDriver_IsOff(0));
    CHECK_TRUE(LedDriver_IsOff(17));
    CHECK_FALSE(LedDriver_IsOn(0));
    CHECK_FALSE(LedDriver_IsOn(17));
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff){
    OutOfBoundsLedsAreAlwaysOff();
}

TEST(LedDriverInverted, OutOfBoundsLedsAreAlwaysOff){
    OutOfBoundsLedsAreAlwaysOff();
}

void IsOff(){
    int led = 6;
    CHECK_TRUE(LedDriver_IsOff(led));
    LedDriver_TurnOn(led);
    CHECK_FALSE(LedDriver_IsOff(led));
}

TEST(LedDriver, IsOff){
    IsOff();
}

TEST(LedDriverInverted, IsOff){
    IsOff();
}

void TurnOffMultipleLeds(const uint16_t& leds){
    LedDriver_TurnOnAll();
    LedDriver_TurnOff(9);
    LedDriver_TurnOff(8);
    LONGS_EQUAL(logicLevelsToHardwareLevels(0xfe7f), leds);
}

TEST(LedDriver, TurnOffMultipleLeds){
    TurnOffMultipleLeds(leds);
}

TEST(LedDriverInverted, TurnOffMultipleLeds){
    TurnOffMultipleLeds(leds);
}

void AllOff(const uint16_t& leds){
    LedDriver_TurnOnAll();
    LedDriver_TurnOffAll();
    LONGS_EQUAL(logicLevelsToHardwareLevels(0x0), leds);
}

TEST(LedDriver, AllOff){
    AllOff(leds);
}

TEST(LedDriverInverted, AllOff){
    AllOff(leds);
}
