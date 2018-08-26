#include "FakeRandomMinute.h"

FakeRandomMinute::FakeRandomMinute(unsigned int b) : 
    RandomMinute(b),
    first(0),
    increment(0){
}

FakeRandomMinute::~FakeRandomMinute(){
}

int FakeRandomMinute::Get(){
    static int num_calls = 0;
    int n = first + num_calls*increment;
    num_calls += 1;
    return n;
}

void FakeRandomMinute::SetFirstAndIncrement(int first, int increment){
    this->first = first;
    this->increment = increment;
}
