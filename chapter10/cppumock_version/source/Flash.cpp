#include "Flash.hpp"
#include "IO.hpp"

Status Flash_Write(Address offset, Value data){
    write(commandRegister, programMode);
    write(offset, data);

    const unsigned int TIMEOUT_TRIES = 8;
    unsigned int numReads = 0;
    Value status = 0;
    while ((status & WRITE_DONE) == 0 && (numReads < TIMEOUT_TRIES)){
        status = read(statusRegister);
        ++numReads;
    } 

    if (status == (WRITE_DONE | WRITE_OK)){
        if (data == read(offset)){
            return SUCCESS;
        }
    }
    else {
        if ((status & WRITE_DONE) != WRITE_DONE){
            return FAILURE_TIMEOUT;
        }
        if (status & VPP_ERROR){
            return FAILURE_VPP;
        }
        if (status & PROGRAM_ERROR){
            return FAILURE_PROGRAM;
        }
        if (status & PROTECTEDBLOCK_ERROR){
            return FAILURE_PROTECTEDBLOCK;
        }
    }
    return FAILURE;
}
