#ifndef _LightControllerSpy_h
#define _LightControllerSpy_h

#include "LightController.hpp"

class LightControllerSpy final: public LightController {
    public:
        enum class LightState {UNKNOWN=-1, OFF=0, ON = 1};

        LightControllerSpy();
        void On(Id id) final;
        void Off(Id id) final;

        Id getLastId();
        LightState getLastState();

    private:
        Id lastId;
        LightState lastState;
};

#endif
