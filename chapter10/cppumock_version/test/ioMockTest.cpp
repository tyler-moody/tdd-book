#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "IO.hpp"

TEST_GROUP(IOMock){
    void setup(){
    }

    void teardown(){
        mock().clear();
    }
};

TEST(IOMock, read){
    Address address = 5;
    Value expected = 7;
    mock().expectOneCall("read").withParameter("address", address).andReturnValue(expected);
    Value observed = read(address);
    LONGS_EQUAL(expected, observed);
    mock().checkExpectations();
}

TEST(IOMock, write){
    Address address = 5;
    Value value = 7;
    mock().expectOneCall("write").withParameter("address", address).withParameter("value", value);
    write(address, value);
    mock().checkExpectations();
}
