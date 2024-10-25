 #pragma once

#include "Filter.h"
#include "TimeManager.h"

namespace modular {

    /* 
     * Defines the output type of a sensor class
     * CONSIDERATION: VALUE_TYPE must have a proper initializer and the reset function
     * will reinitialize with {0} a more appropriate way would be to 
     * Define an abstract VALUE_TYPE Class that forces a virtual reset method.
     */


    template <typename VALUE_TYPE, typename SENSOR_READ_TYPE>

    class Sensor {
        public:            
            virtual void measure() {
                SENSOR_READ_TYPE sensorValue = readSensor();
                if (hasFilter) {
                    value = filter->filter(value, sensorValue);
                } else {
                    value = VALUE_TYPE(sensorValue);
                }
            };

            VALUE_TYPE getValue() {
                return value;
            }

            /* Considerations about filters. In theory we could apply a pipes and filters pattern, here.
             * And maybe sometime in future it will be done. However, in real life I hardly every use more
             * then one filter at a time. So I stick to mantra of this framework and keep it simple.
             */
            bool setFilter(Filter<SENSOR_READ_TYPE, VALUE_TYPE> &f) {
                // we could compare the type of the filter with the type of the sensor here
                filter = &f;
                hasFilter = true;
                return true;
            };

            void reset() {
                value = VALUE_TYPE(0);
            };

        protected:
            virtual SENSOR_READ_TYPE readSensor() {
                return SENSOR_READ_TYPE(0);
            };
            VALUE_TYPE value{0};
            Filter<SENSOR_READ_TYPE, VALUE_TYPE> *filter;
            bool hasFilter = false;

    };
}