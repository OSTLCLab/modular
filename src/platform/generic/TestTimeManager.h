
#pragma once

#include "framework/TimeManager.h"


namespace modular::platform::generic {

    class TestTimeManager : public TimeManager<int> {
        public:
            virtual int getTimeStamp() override {
                return 1;
            };
    };

}