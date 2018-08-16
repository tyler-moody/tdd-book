#include "CppUTest/TestHarness.h"
#include "LedDriver.h"

TEST_GROUP(LedDriver)
{
    uint16_t leds;

    void setup()
    {
        leds = 0xffff;
    }

    void teardown()
    {
    }
};

TEST(LedDriver , LedsOffAfterCreate)
{
    LedDriver_Create(&leds);
    LONGS_EQUAL(0, leds);
}

TEST(LedDriver, TurnOnLedOne)
{
    LedDriver_Create(&leds);
    LedDriver_TurnOn(1);
    LONGS_EQUAL(1, leds);
}

TEST(LedDriver, TurnOffLedOne)
{
    LedDriver_Create(&leds);
    LedDriver_TurnOn(1);
    LedDriver_TurnOff(1);
    LONGS_EQUAL(0, leds);
}
