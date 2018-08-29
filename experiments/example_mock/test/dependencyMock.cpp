#include "CppUTestExt/MockSupport.h"
#include "dependency.hpp"

void dependency(int arg){
    mock().actualCall("dependency").withParameter("arg", arg);
}
