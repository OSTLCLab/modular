 #pragma once

#include "Filter.h"
#include <typeinfo> 

namespace modular {

    // Defines the output type of a sensor class
    template <typename VALUE_TYPE, typename SENSOR_READ_TYPE>

    class Sensor {
        public:
            Sensor() {

            };
            virtual void measure() { };
            VALUE_TYPE getValue() {
                return value;
            }

            /* Considerations about filters. In theory we could apply a pipes and filters pattern, here.
             * And maybe sometime in future it will be done. However, in real life I hardly every use more
             * then one filter at a time. So I stick to mantra of this framework and keep it simple.
             */
            bool addFilter(Filter<SENSOR_READ_TYPE, VALUE_TYPE> &f) {
                filter = f;
                return true;
            };

            virtual void reset() {
                // if filter -> resset filters
                // else reset value to 0 by default
                // if value is a struct, reset must be implemented subclass
                //value = VALUE_TYPE(0);
            };

        protected:
            VALUE_TYPE value;
            Filter<SENSOR_READ_TYPE, VALUE_TYPE> filter;
    };
}