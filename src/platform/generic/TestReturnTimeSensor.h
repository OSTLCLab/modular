/* 
 * Simple Sensor implementation that returns a value that is passed to it.
 * This is useful for testing and debugging purposes.
 */

#pragma once

#include "framework/TimeSensor.h"
#include "filter/StatisticsFilter.h"

namespace modular::platform::generic {

    struct TimeValue {
        TimeValue(float val) : value{val}, timestamp{0} {};
        float value;
        int timestamp;
    };

    class TestReturnTimeSensor : public TimeSensor<TimeValue, float, int> {
        public:
            TestReturnTimeSensor(TestTimeManager &tm) : TimeSensor<TimeValue, float, int>(tm) {

            }
            void setSensorValue(float val) {
                sensorValue = val;
            };

        protected:
            virtual float readSensor() override {
                return sensorValue;
            };
        private:
            float sensorValue;
    };

}