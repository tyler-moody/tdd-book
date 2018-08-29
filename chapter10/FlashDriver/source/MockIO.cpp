#include "MockIO.hpp"
#include "IO.hpp"
#include "CppUTest/TestHarness_c.h"

enum operation {FLASH_WRITE, FLASH_READ, NoExpectedValue};

typedef struct Expectation {
    int kind;
    address_t address;
    data_t value;
} Expectation;

static Expectation* expectations = nullptr;
static size_t setExpectationCount = 0;
static size_t getExpectationCount = 0;
static size_t maxExpectationCount = 0;
static bool failureAlreadyReported = false;

static Expectation expected;
static Expectation actual;

static const char* report_expect_write_was_read = "expected IO_Write but was IO_Read";
static const char* report_expect_read_was_write = "expected IO_Read but was IO_Write";
static const char* report_read_wrong_address = "expected IO_Read but was IO_Write";
static const char* report_write_does_not_match = "expected write args with other args";
static const char* report_too_many_write_expectations = "write: too many expectations";
static const char* report_too_many_read_expectations = "read: too many expectations";
static const char* report_not_initialized = "not initialized";
static const char* report_write_but_out_of_expectations = "write but out of expectations";
static const char* report_read_but_out_of_expectations = "read but out of expectations";
static const char* report_no_more_expectations = "no more expectations";
static const char* report_expectation_number = "expectation number";

static void fail(const char* message){
    failureAlreadyReported = true;
    FAIL_TEXT_C(message);
}

static void failWhenNotInitialized(){
    if (expectations == nullptr){
        fail(report_not_initialized);
    }
}

static void failWhenNoRoomForExpectations(const char* msg){
    failWhenNotInitialized();
    if (setExpectationCount >= maxExpectationCount){
        fail(msg);
    }
}

static void failWhenNoUnusedExpectations(const char* msg){
    if (getExpectationCount >= setExpectationCount){
        fail(msg);
    }
}

static void failExpectation(const char* msg){
    fail(msg);
}

static void failWhenNotAllExpectationsUsed(){
    if (getExpectationCount == setExpectationCount){
        return;
    }
    fail("not all expectations used");
}

static void failWhen(int condition, const char* msg){
    if (condition){
        failExpectation(msg);
    }
}

static int expectationIsNot(int kind){
    return kind != expectations[getExpectationCount].kind;
}

static int expectedAddressIsNot(address_t address){
    return expected.address != address;
}

static int expectedDataIsNot(data_t data){
    return expected.value != data;
}

static void setExpectedAndActual(address_t address, data_t data){
    expected.address = expectations[getExpectationCount].address;
    expected.value = expectations[getExpectationCount].value;
    actual.address = address;
    actual.value = data;
}

static void recordExpectation(int kind, address_t address, data_t data){
    expectations[setExpectationCount].kind = kind;
    expectations[setExpectationCount].address = address;
    expectations[setExpectationCount].value = data;
    ++setExpectationCount;
}

void MockIO_Create(size_t maxExpectations){
    expectations = new Expectation[maxExpectations];
    setExpectationCount = 0;
    getExpectationCount = 0;
    maxExpectationCount = maxExpectations;
    failureAlreadyReported = false;
}

void MockIO_Destroy(){
    if (expectations){
        delete[] expectations;
        expectations = nullptr;
    }
}

void MockIO_Expect_Write(address_t address, data_t data){
    failWhenNoRoomForExpectations(report_too_many_write_expectations);
    recordExpectation(FLASH_WRITE, address, data);
}

void MockIO_Expect_ReadThenReturn(address_t address, data_t value){
    failWhenNoRoomForExpectations(report_too_many_read_expectations);
    recordExpectation(FLASH_READ, address, value);
}

void MockIO_Verify_Complete(){
    if (failureAlreadyReported){
        return;
    }
    failWhenNotAllExpectationsUsed();
}

void IO_Write(address_t address, data_t data){
    setExpectedAndActual(address, data);
    failWhenNotInitialized();
    failWhenNoUnusedExpectations(report_write_but_out_of_expectations);
    failWhen(expectationIsNot(FLASH_WRITE), report_expect_read_was_write);
    failWhen(expectedAddressIsNot(address), report_write_does_not_match);
    failWhen(expectedDataIsNot(data), report_write_does_not_match);
    ++getExpectationCount;
}

data_t IORead(address_t address){
    setExpectedAndActual(address, NoExpectedValue);
    failWhenNotInitialized();
    failWhenNoUnusedExpectations(report_read_but_out_of_expectations);
    failWhen(expectationIsNot(FLASH_READ), report_expect_write_was_read);
    failWhen(expectedAddressIsNot(address), report_read_wrong_address);

    data_t r = expectations[getExpectationCount].value;
    ++getExpectationCount;
    return r;
}
