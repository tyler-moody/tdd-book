#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Flash.hpp"

TEST_GROUP(Flash){
    void setup(){
    }

    void teardown(){
        mock().clear();
    }

    void fake_response(size_t stall_cycles, unsigned int return_value){
        for (unsigned int i = 0; i < stall_cycles; ++i){
            mock().expectOneCall("read").withParameter("address", statusRegister).andReturnValue(0);
        }
        mock().expectOneCall("read").withParameter("address", statusRegister).andReturnValue(WRITE_DONE | return_value);
    }
};

TEST(Flash, WriteSucceedsImmediately){
    Address address = 5;
    Value value = 7;
    mock().expectOneCall("write").withParameter("address", commandRegister).withParameter("value", programMode);
    mock().expectOneCall("write").withParameter("address", address).withParameter("value", value);
    mock().expectOneCall("read").withParameter("address", statusRegister).andReturnValue(WRITE_DONE);
    mock().expectOneCall("read").withParameter("address", address).andReturnValue(value);

    LONGS_EQUAL(SUCCESS, Flash_Write(5,7));
    mock().checkExpectations();
}

TEST(Flash, WriteSucceedsEventually){
    Address address = 5;
    Value value = 7;
    mock().expectOneCall("write").withParameter("address", commandRegister).withParameter("value", programMode);
    mock().expectOneCall("write").withParameter("address", address).withParameter("value", value);

    fake_response(3, WRITE_OK);
    mock().expectOneCall("read").withParameter("address", address).andReturnValue(value);

    LONGS_EQUAL(SUCCESS, Flash_Write(5,7));
    mock().checkExpectations();
}

TEST(Flash, WriteFailsVpp){
    Address address = 5;
    Value value = 7;
    mock().expectOneCall("write").withParameter("address", commandRegister).withParameter("value", programMode);
    mock().expectOneCall("write").withParameter("address", address).withParameter("value", value);
    fake_response(3, VPP_ERROR);

    LONGS_EQUAL(FAILURE_VPP, Flash_Write(5,7));

    mock().checkExpectations();
}

TEST(Flash, WriteFailsProgram){
    Address address = 5;
    Value value = 7;
    mock().expectOneCall("write").withParameter("address", commandRegister).withParameter("value", programMode);
    mock().expectOneCall("write").withParameter("address", address).withParameter("value", value);
    fake_response(3, PROGRAM_ERROR);

    LONGS_EQUAL(FAILURE_PROGRAM, Flash_Write(5,7));

    mock().checkExpectations();
}

TEST(Flash, WriteFailsProtectedBlock){
    Address address = 5;
    Value value = 7;
    mock().expectOneCall("write").withParameter("address", commandRegister).withParameter("value", programMode);
    mock().expectOneCall("write").withParameter("address", address).withParameter("value", value);
    fake_response(3, PROTECTEDBLOCK_ERROR);

    LONGS_EQUAL(FAILURE_PROTECTEDBLOCK, Flash_Write(5,7));

    mock().checkExpectations();
}

IGNORE_TEST(Flash, WriteFailsTimeout){
    Address address = 5;
    Value value = 7;
    mock().expectOneCall("write").withParameter("address", commandRegister).withParameter("value", programMode);
    mock().expectOneCall("write").withParameter("address", address).withParameter("value", value);
    fake_response(8, 0);

    LONGS_EQUAL(FAILURE_TIMEOUT, Flash_Write(5,7));

    mock().checkExpectations();
}
