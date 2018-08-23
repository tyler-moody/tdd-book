#ifndef _LightControllerSpy_h
#define _LightControllerSpy_h

#include "LightController.hpp"

class LightControllerSpy : public LightController {
    public:
        enum class LightState {UNKNOWN=-1, OFF=0, ON = 1};

        LightControllerSpy();
        void On(Id id);
        void Off(Id id);

        Id getLastId();
        LightState getLastState();

    private:
        Id lastId;
        LightState lastState;
};

#endif
