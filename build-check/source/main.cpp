#include <iostream>

int five();

int main(){
    if (5 == five()){
        std::cout << "hello, world" << std::endl;
    }
    return 0;
}
