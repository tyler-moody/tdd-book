#include "CppUTest/TestHarness.h"

int five();

TEST_GROUP(Five)
{
};

TEST(Five, eq)
{
    LONGS_EQUAL(5, five());
}
