#ifndef _IO_hpp
#define _IO_hpp

typedef unsigned int Address;
typedef unsigned int Value;

void write(Address address, Value value);

Value read(Address address);

#endif
