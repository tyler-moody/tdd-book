#include "CppUTest/TestHarness.h"
#include "LedDriver.h"

TEST_GROUP(LedDriver)
{
    uint16_t leds;

    void setup()
    {
        LedDriver_Create(&leds);
    }

    void teardown()
    {
    }
};

TEST(LedDriver , LedsOffAfterCreate)
{
    leds = 0xffff;
    LedDriver_Create(&leds);
    LONGS_EQUAL(0, leds);
}

TEST(LedDriver, TurnOnLedOne)
{
    LedDriver_TurnOn(1);
    LONGS_EQUAL(1, leds);
}

TEST(LedDriver, TurnOffLedOne)
{
    LedDriver_TurnOn(1);
    LedDriver_TurnOff(1);
    LONGS_EQUAL(0, leds);
}
