 #pragma once

#include "Filter.h"
#include <typeinfo> 

namespace modular {

    // Defines the output type of a sensor class
    template <typename VALUE_TYPE, typename SENSOR_READ_TYPE>

    class Sensor {
        public:
            Sensor() {};
            
            void measure() {
                SENSOR_READ_TYPE sensorValue = readSensor();
                if (hasFilter) {
                    value = filter->filter(value, sensorValue);
                } else {
                    value = VALUE_TYPE{sensorValue};
                }
            };

            VALUE_TYPE getValue() {
                return value;
            }

            /* Considerations about filters. In theory we could apply a pipes and filters pattern, here.
             * And maybe sometime in future it will be done. However, in real life I hardly every use more
             * then one filter at a time. So I stick to mantra of this framework and keep it simple.
             */
            bool addFilter(Filter<SENSOR_READ_TYPE, VALUE_TYPE> &f) {
                filter = &f;
                hasFilter = true;
                return true;
            };

            void reset() {
                if (hasFilter) {
                    this->filter->reset(this->value);
                } else {
                    value = VALUE_TYPE{0};
                }
            };

        protected:
            virtual SENSOR_READ_TYPE readSensor() {
                return SENSOR_READ_TYPE(0);
            };
            VALUE_TYPE value;
            Filter<SENSOR_READ_TYPE, VALUE_TYPE>* filter;
        private:
            bool hasFilter = false;
    };
}