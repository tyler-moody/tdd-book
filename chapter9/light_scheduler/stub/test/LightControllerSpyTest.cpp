#include <memory>
#include "CppUTest/TestHarness.h"
#include "LightControllerSpy.hpp"

TEST_GROUP(LightControllerSpy){
    std::unique_ptr<LightControllerSpy> lightController;

    void setup(){
        lightController.reset(new LightControllerSpy());
    }

    void teardown(){
    }
};

TEST(LightControllerSpy, Create){
    LONGS_EQUAL(LightController::UNKNOWN_ID, lightController->getLastId());
    LONGS_EQUAL(LightControllerSpy::LightState::UNKNOWN, lightController->getLastState());
}

TEST(LightControllerSpy, RememberTheLastLightIdControlled){
    lightController->On(10);
    LONGS_EQUAL(10, lightController->getLastId());
    LONGS_EQUAL(LightControllerSpy::LightState::ON, lightController->getLastState());

    lightController->Off(5);
    LONGS_EQUAL(5, lightController->getLastId());
    LONGS_EQUAL(LightControllerSpy::LightState::OFF, lightController->getLastState());
}
