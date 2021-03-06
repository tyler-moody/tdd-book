#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "production.hpp"

TEST_GROUP(Production){
    void setup(){
    }

    void teardown(){
        mock().clear();
    }
};

TEST(Production, first){
    mock().expectOneCall("dependency").withParameter("arg", 1);
    production();
    mock().checkExpectations();
}
