#include <cstdlib>
#include "RandomMinute.h"

RandomMinute::RandomMinute(unsigned int b) : 
    bound(b){
}

RandomMinute::~RandomMinute(){
}

int RandomMinute::Get(){
    int r = rand() % (2*bound+1);
    r -= bound;
    return r;
}
