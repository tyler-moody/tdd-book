#ifndef _Controller_h
#define _Controller_h

class LightController {
    public:
        typedef unsigned int Id;
        static const Id UNKNOWN_ID = -1;

        virtual void On(Id id) = 0;
        virtual void Off(Id id) = 0;
    private:
};

#endif
