#ifndef _CircularBuffer_h
#define _CircularBuffer_h

#include "FormatOutput.h"
#include <cstring>
#include <vector>

class CircularBuffer {
    public:
        CircularBuffer(size_t cap) :
            contents(nullptr),
            capacity(cap+1),
            front(0),
            back(0) {
            contents = new int[capacity];
            memset(contents, 0, capacity*sizeof(int));
        }

        ~CircularBuffer(){
            delete[] contents;
        }

        /*
        bool IsEmpty(){
            return front == back;
        }

        bool IsFull(){
            return (front == 0 && back == capacity-1) ||
                (back + 1 == front);
        }
        */

        void Put(int n){
            contents[back] = n;
            back = (back+1)%capacity;
        }

        int Get(){
            int r = contents[front];
            front = (front+1)%capacity;
            return r;
        }

        void Print() {
            FormatOutput("Circular buffer content:\n<");
            size_t it = front;
            while (it != back){
                FormatOutput("%d", contents[it]);
                if ( ((it+1)%capacity) != (back)){
                    FormatOutput(", ");
                }
                it = (it+1)%capacity;
            }
            FormatOutput(">\n");
        }
        
    private:
        int* contents;
        size_t capacity;
        size_t front;
        size_t back;
};


#endif
