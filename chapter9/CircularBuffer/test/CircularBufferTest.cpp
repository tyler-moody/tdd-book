#include "CppUTest/TestHarness.h"
#include "CircularBuffer.h"
#include "FormatOutput.h"
#include "FormatOutputSpy.h"
#include <memory>

TEST_GROUP(CircularBufferPrint){
    std::shared_ptr<CircularBuffer> circularBuffer;
    const char* expectedOutput;
    const char* actualOutput;

    void setup(){
        UT_PTR_SET(FormatOutput, FormatOutputSpy);
        FormatOutputSpy_Create(100);
        // grab a pointer to the output buffer
        actualOutput = FormatOutputSpy_GetOutput();
        circularBuffer = std::make_shared<CircularBuffer>(10);
    }

    void teardown(){
        circularBuffer.reset();
        FormatOutputSpy_Destroy();
    }
};

TEST(CircularBufferPrint, PrintEmpty){
    expectedOutput = "Circular buffer content:\n<>\n";

    circularBuffer->Print();

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintAfterOneIsPut){
    expectedOutput = "Circular buffer content:\n<17,>\n";
    circularBuffer->Put(17);

    circularBuffer->Print();

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintNotYetWrappedOrFull){
    expectedOutput = "Circular buffer content:\n<10,20,30,>\n";
    circularBuffer->Put(10);
    circularBuffer->Put(20);
    circularBuffer->Put(30);

    circularBuffer->Print();

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintNotYetWrappedAndIsFull){
    expectedOutput = "Circular buffer content:\n<31,41,59,26,53,>\n";
    circularBuffer = std::make_shared<CircularBuffer>(5);
    circularBuffer->Put(31);
    circularBuffer->Put(41);
    circularBuffer->Put(59);
    circularBuffer->Put(26);
    circularBuffer->Put(53);

    circularBuffer->Print();

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintOldToNewWhenWrappedAndFull){
    expectedOutput = "Circular buffer content:\n<201,202,203,204,999,>\n";
    circularBuffer = std::make_shared<CircularBuffer>(5);
    circularBuffer->Put(200);
    circularBuffer->Put(201);
    circularBuffer->Put(202);
    circularBuffer->Put(203);
    circularBuffer->Put(204);
    LONGS_EQUAL(200, circularBuffer->Get());
    circularBuffer->Put(999);

    circularBuffer->Print();

    STRCMP_EQUAL(expectedOutput, actualOutput);
}
