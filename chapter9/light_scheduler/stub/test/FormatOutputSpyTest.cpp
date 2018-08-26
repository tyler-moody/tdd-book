#include "CppUTest/TestHarness.h"
#include "FormatOutput.h"
#include "FormatOutputSpy.h"

TEST_GROUP(FormatOutputSpy){

    void setup(){
        UT_PTR_SET(FormatOutput, FormatOutputSpy);
    }
    
    void teardown(){
        FormatOutputSpy_Destroy();
    }
};

TEST(FormatOutputSpy, HelloWorld){
    FormatOutputSpy_Create(20);
    const char* str = "hello, world\n";
    FormatOutput(str);
    STRCMP_EQUAL(str, FormatOutputSpy_GetOutput());

}

TEST(FormatOutputSpy, LimitTheOutputBufferSize){
    FormatOutputSpy_Create(4);
    FormatOutput("hello, world\n");
    STRCMP_EQUAL("hell", FormatOutputSpy_GetOutput());
}

TEST(FormatOutputSpy, PrintMultipleTimes){
    FormatOutputSpy_Create(25);
    FormatOutput("hello");
    FormatOutput(", world\n");
    STRCMP_EQUAL("hello, world\n", FormatOutputSpy_GetOutput());
}

TEST(FormatOutputSpy, PrintMultipleOutputsPastFull){
    FormatOutputSpy_Create(12);
    FormatOutput("12345");
    FormatOutput("67890");
    FormatOutput("ABCDE");
    STRCMP_EQUAL("1234567890AB", FormatOutputSpy_GetOutput());
}
