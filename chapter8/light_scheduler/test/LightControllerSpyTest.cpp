#include "CppUTest/TestHarness.h"
#include "LightControllerSpy.hpp"

TEST_GROUP(LightControllerSpy){
    void setup(){
        LightController_Create();
    }

    void teardown(){
        LightController_Destroy();
    }
};

TEST(LightControllerSpy, Create){
    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightControllerSpy, RememberTheLastLightIdControlled){
    LightController_On(10);
    LONGS_EQUAL(10, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());

    LightController_Off(5);
    LONGS_EQUAL(5, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_OFF, LightControllerSpy_GetLastState());
}
