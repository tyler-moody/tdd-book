#include "CppUTest/TestHarness.h"
#include "LedDriver.h"

TEST_GROUP(LedDriver)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(LedDriver , LedsOffAfterCreate)
{
    uint16_t leds = 0xffff;
    LedDriver_Create(&leds);
    LONGS_EQUAL(0, leds);
}
