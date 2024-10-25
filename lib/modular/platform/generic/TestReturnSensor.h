/* 
 * Simple Sensor implementation that returns a value that is passed to it.
 * This is useful for testing and debugging purposes.
 */

#pragma once

#include "framework/Sensor.h"
#include "filter/StatisticsFilter.h"
#include "TestTimeManager.h"

namespace modular::platform::generic {

    class TestReturnSensor : public Sensor<filter::Statistics<float>, float> {
        public:
            void setSensorValue(float val) {
                sensorValue = val;
            };

        protected:
            virtual float readSensor() override {
                value.timestamp = 1;
                return sensorValue;
            };
        private:
            float sensorValue;
    };

}