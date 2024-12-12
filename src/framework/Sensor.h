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


    template <typename VALUE_TYPE>

    class Sensor {
        public:            
            virtual void measure() {
                value = readSensor();
            };

            VALUE_TYPE getValue() {
                return value;
            }

            /* Considerations about filters. In theory we could apply a pipes and filters pattern, here.
             * And maybe sometime in future it will be done. However, in real life I hardly every use more
             * then one filter at a time and abstracting filter chains is a bit overkill.
             * This framework, for  now, offers filters, but they must be implemented in the sensor implementation class.
             */


            virtual void reset() {
                value = VALUE_TYPE {};
            };

        protected:
            virtual VALUE_TYPE readSensor() {
                return VALUE_TYPE {};
            };
            VALUE_TYPE value = VALUE_TYPE {};
    };
}