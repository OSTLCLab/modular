#ifndef STATISTICSFILTER_H
#define STATISTICSFILTER_H

#include <framework/Sensor.h>

namespace modular::filter {

    template <typename T>

    struct Statistics {
        T min {0};
        T max {0};
        T avg {0};
        T last {0};
        T m2 {0};
        T var {0};
    };

    template <typename ST>

    class StatisticsFilter  {
        public:
            StatisticsFilter() {};
            Statistics<ST> filter(Statistics<ST> val, float newValue) {
                val.last = newValue;
                val.min = min(val.min, newValue);
                val.max = max(val.max, newValue);
                count++;
                float delta = newValue - val.avg;
                val.avg += delta / count;
                float delta2 = newValue - val.avg;
                val.m2 += delta * delta2;
                val.var = val.m2 / count;   
                return val;     
            };

            void reset(Statistics<ST>* val) {
                val->min = 0;
                val->max = 0;
                val->avg = 0;
                val->last = 0;
                val->m2 = 0;
                val->var = 0;
                count = 0;
            };

            int getNumberOfMeasurements() { 
                return count;
            }

        private:
            int count;
    };

}
#endif