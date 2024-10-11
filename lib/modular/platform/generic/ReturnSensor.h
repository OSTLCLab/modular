/* 
 * Simple Sensor implementation that returns a value that is passed to it.
 * This is useful for testing and debugging purposes.
 */

#pragma once

#include "framework/Sensor.h"

namespace modular::platform::generic {

    template <typename VTYPE>

    class ReturnSensor : public Sensor<VTYPE, float> {
        public:
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