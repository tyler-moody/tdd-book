#include "CppUTest/TestHarness.h"
#include "Flash.hpp"
#include "MockIO.hpp"

TEST_GROUP(FlashDriver){
    void setup(){
    }

    void teardown(){
    }
};

TEST(FlashDriver, WriteSucceeds_ReadyImmediately){
    const int address = 0x1000;
    const int value = 0xbeef;
    MockIO_Expect_Write(0, 0x40);
    MockIO_Expect_Write(address, value);
    MockIO_Expect_ReadThenReturn(0, 1<<7);
    MockIO_Expect_ReadThenReturn(address, value);

    int result = Flash_Write(address, value);

    LONGS_EQUAL(0, result);
    MockIO_Verify_Complete();
}

// successful operation
// invalid programming voltage
// program error
// attempt to program protected block
// read back fails
// device timeout during write operation
