#ifndef _Flash_hpp
#define _Flash_hpp

#include "IO.hpp"

typedef enum { SUCCESS=0, FAILURE=-1, FAILURE_VPP, FAILURE_PROGRAM, FAILURE_PROTECTEDBLOCK, FAILURE_TIMEOUT } Status;

Status Flash_Write(Address offset, Value data);

const Address commandRegister = 0x0;
const Address statusRegister = 0x0;

 const Value WRITE_DONE = 0x80;
const Value VPP_ERROR = 0x08;
const Value PROGRAM_ERROR = 0x10;
const Value PROTECTEDBLOCK_ERROR = 0x02;
const Value WRITE_OK = 0x80;
const Value programMode = 0x40;

#endif
