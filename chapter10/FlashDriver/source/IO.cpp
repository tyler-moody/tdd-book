#include "IO.hpp"

data_t read(address_t address){
    data_t* p = 0;
    return *(p + address);
}

void write(address_t address, data_t data){
    data_t* p = 0;
    *(p + address) = data;
}
