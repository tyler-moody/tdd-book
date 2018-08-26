#ifndef _RandomMinute_h
#define _RandomMinute_h

class RandomMinute {
    public:
        RandomMinute(unsigned int bound);
        virtual ~RandomMinute();
        virtual int Get();
    private:
        unsigned int bound;

};

#endif
