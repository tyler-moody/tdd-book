#include <cstdlib>
#include <cstring>
#include <iostream>
#include "CppUTest/TestHarness.h"
#include "RandomMinute.h"

TEST_GROUP(RandomMinute){
    RandomMinute* randomMinute = nullptr;
    int minute;
    const int bound = 30;

    void setup(){
        randomMinute = new RandomMinute(bound);
        srand(1);
    }

    void teardown(){
        delete randomMinute;
    }

    void AssertMinuteIsInRange(){
        if (minute < -bound || minute > bound){
            std::cout << "bad minute value " << minute << std::endl;
            FAIL("minute out of range");
        }
    }
};

TEST(RandomMinute, GetIsInRange){
    // index 0 -> -30
    // index 1 -> -29
    // ...
    int hit[2*bound+1];
    memset(hit, 0, sizeof(hit));

    for (int i = 0; i < 100*bound; ++i){
        minute = randomMinute->Get();
        AssertMinuteIsInRange();
        hit[minute+bound]+= 1;
    }

    for (int i = 0; i < 2*bound+1; ++i){
        if (hit[i] == 0){
            std::cout << i-bound << " never generated" << std::endl;
            FAIL("bad distribution");
        }
    }
}
