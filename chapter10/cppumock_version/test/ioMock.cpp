#include "CppUTestExt/MockSupport.h"
#include "IO.hpp"

void write(Address address, Value value){
    mock().actualCall("write").withParameter("address",  address).withParameter("value", value);
}

Value read(Address address){
    return mock().actualCall("read").withParameter("address", address).returnUnsignedIntValue();
}
