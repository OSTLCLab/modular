 #pragma once

#include "Sensor.h"
#include "TimeManager.h"
#include <type_traits>

namespace modular {

    /* 
     * Defines an interface for Sensors that have a timestamp. 
     * If the VALUE_TYPE is a struct, and has an attribute called a "timestamp" field,
     * then the timestamp will be set automatically.
     * If not, the timestamp will be ignored and must be set manually in the implementation (e.g. by
     * overriding the measure method)
     */

    // A utility struct to implement SFINAE pattern
   
    template<typename T, typename = void>
    struct HasTimestamp : std::false_type {};

    template<typename T>
    struct HasTimestamp<T, std::void_t<decltype(std::declval<T>().timestamp)>> : std::true_type {};

    template <typename VALUE_TYPE, typename SENSOR_READ_TYPE, typename TIME_TYPE>

    class TimeSensor : public Sensor<VALUE_TYPE, SENSOR_READ_TYPE> {
        public:
            TimeSensor(TimeManager<TIME_TYPE> &timeManager) : timeManager(timeManager) {
            };
            
            virtual void measure() override {
                Sensor<VALUE_TYPE, SENSOR_READ_TYPE>::measure();
                if (HasTimestamp<VALUE_TYPE>::value) {
                    this->value.timestamp = timeManager.getTimeStamp();
                }
            };

        protected:
            TimeManager<TIME_TYPE> &timeManager;
    };
}