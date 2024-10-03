#pragma once

#include <framework/Sensor.h>
#include <framework/Filter.h>
#include <algorithm>

namespace modular::filter {

    template <typename T>

    struct Statistics {
        T min = T(0);
        T max = T(0);
        T avg = T(0);
        T last = T(0);
        float m2 = 0;
        float var = 0;
    };

    template <typename ST>

    class StatisticsFilter : public modular::Filter<ST, Statistics<ST>> {
        public:
            virtual Statistics<ST> filter(Statistics<ST> &val, ST newValue) {
                val.min = std::min(val.min, newValue);
                val.max = std::max(val.max, newValue);
                float delta = newValue - val.avg;
                val.avg += delta / (count + 1);
                float delta2 = newValue - val.avg;
                val.m2 += delta * delta2;
                val.var = val.m2 / (count + 1);   
                val.last = newValue;
                count++;
                return val;     
            };

            virtual void reset(Statistics<ST> &val) {
                val.min = 0;
                val.max = 0;
                val.avg = 0;
                val.last = 0;
                val.m2 = 0;
                val.var = 0;
                count = 0;
            };

            int getNumberOfMeasurements() { 
                return count;
            }

        private:
            int count = 0;
    };

}