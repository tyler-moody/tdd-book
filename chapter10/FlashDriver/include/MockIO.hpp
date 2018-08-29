#ifndef _MockIO_hpp
#define _MockIO_hpp

#include <cstddef>
#include "IO.hpp"

void MockIO_Create(size_t maxExpectations);
void MockIO_Destroy();

void MockIO_Expect_Write(address_t address, data_t data);
void MockIO_Expect_ReadThenReturn(address_t address, data_t value);
void MockIO_Verify_Complete();

#endif
