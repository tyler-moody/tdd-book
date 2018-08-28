#include "CppUTestExt/MockSupport.h"
#include "dependency.hpp"

void dependency(int unused){
    mock().actualCall("dependency");
}
