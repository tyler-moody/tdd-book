#include "CppUTest/TestHarness.h"
#include "LedDriver.h"
#include "RuntimeErrorStub.h"

TEST_GROUP(LedDriver){
    uint16_t leds;

    void setup()
    {
        LedDriver_Create(&leds);
    }

    void teardown()
    {
    }
};

TEST(LedDriver , LedsOffAfterCreate){
    leds = 0xffff;
    LedDriver_Create(&leds);
    LONGS_EQUAL(0, leds);
}

TEST(LedDriver, TurnOnLedOne){
    LedDriver_TurnOn(1);
    LONGS_EQUAL(1, leds);
}

TEST(LedDriver, TurnOffLedOne){
    LedDriver_TurnOn(1);
    LedDriver_TurnOff(1);
    LONGS_EQUAL(0, leds);
}

TEST(LedDriver, TurnOnMultipleLeds){
    LedDriver_TurnOn(9);
    LedDriver_TurnOn(8);
    LONGS_EQUAL(0x180, leds);
}

TEST(LedDriver, AllOn){
    LedDriver_TurnOnAll();
    LONGS_EQUAL(0xffff, leds);
}

TEST(LedDriver, TurnOffAnyLed){
    LedDriver_TurnOnAll();
    LedDriver_TurnOn(8);
    LedDriver_TurnOff(8);
    LONGS_EQUAL(0xff7f, leds);
}

TEST(LedDriver, LedMemoryNotReadable){
    leds = 0xffff;
    LedDriver_TurnOn(8);
    LONGS_EQUAL(0x0080, leds);

    leds = 0xffff;
    LedDriver_TurnOff(8);
    LONGS_EQUAL(0x0000, leds);
}

TEST(LedDriver, UpperAndLowerBounds){
    LedDriver_TurnOn(1);
    LedDriver_TurnOn(16);
    LONGS_EQUAL(0x8001, leds);
}

TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm){
    LedDriver_TurnOn(-1);
    LedDriver_TurnOn(0);
    LedDriver_TurnOn(17);
    LedDriver_TurnOn(3141);
    LONGS_EQUAL(0, leds);
}

TEST(LedDriver, OutOfBoundTurnOffDoesNoHarm){
    LedDriver_TurnOnAll();
    LedDriver_TurnOff(-1);
    LedDriver_TurnOff(0);
    LedDriver_TurnOff(17);
    LedDriver_TurnOff(3141);
    LONGS_EQUAL(0xffff, leds);
}

TEST(LedDriver, OutOfBoundsProducesRuntimeError){
    LedDriver_TurnOn(-1);
    STRCMP_EQUAL("LED Driver: out-of-bounds LED",
            RuntimeErrorStub_getLastError());
    LONGS_EQUAL(-1, RuntimeErrorStub_getLastParameter());
}
    
TEST(LedDriver, IsOn){
    CHECK_FALSE(LedDriver_IsOn(11));
    LedDriver_TurnOn(11);
    CHECK_TRUE(LedDriver_IsOn(11));
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff){
    CHECK_TRUE(LedDriver_IsOff(0));
    CHECK_TRUE(LedDriver_IsOff(17));
    CHECK_FALSE(LedDriver_IsOn(0));
    CHECK_FALSE(LedDriver_IsOn(17));
}

TEST(LedDriver, IsOff){
    int led = 6;
    CHECK_TRUE(LedDriver_IsOff(led));
    LedDriver_TurnOn(led);
    CHECK_FALSE(LedDriver_IsOff(led));
}

TEST(LedDriver, TurnOffMultipleLeds){
    LedDriver_TurnOnAll();
    LedDriver_TurnOff(9);
    LedDriver_TurnOff(8);
    LONGS_EQUAL(0xfe7f, leds);
}

TEST(LedDriver, AllOff){
    LedDriver_TurnOnAll();
    LedDriver_TurnOffAll();
    LONGS_EQUAL(0x0, leds);
}
