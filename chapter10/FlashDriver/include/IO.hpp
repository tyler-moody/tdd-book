#ifndef _IO_hpp
#define _IO_hpp

typedef unsigned int data_t;
typedef unsigned int address_t;

data_t read(address_t address);

void write(address_t address, data_t data);

#endif
