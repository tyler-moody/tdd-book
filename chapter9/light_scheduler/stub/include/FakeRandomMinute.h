#include "RandomMinute.h"

class FakeRandomMinute: public RandomMinute {
    public:
        FakeRandomMinute(unsigned int bound);
        ~FakeRandomMinute();
        int Get();

        void SetFirstAndIncrement(int first, int increment);
    private:
        int first;
        int increment;
};
