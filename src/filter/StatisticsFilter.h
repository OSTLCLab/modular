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
        T current = T(0);
        float m2 = 0;
        float var = 0;
        long long timestamp = 0;
    };

    template <typename ST>

    class StatisticsFilter : public modular::Filter<ST, Statistics<ST>> {
        public:
            virtual Statistics<ST> filter(Statistics<ST> &val, ST newValue) override {
                if (count == 0) {
                    val.min = newValue;
                    val.max = newValue;
                    val.avg = newValue;
                    val.current = newValue;
                    val.m2 = 0;
                    val.var = 0;
                } else {
                    val.min = std::min(val.min, newValue);
                    val.max = std::max(val.max, newValue);
                    float delta = newValue - val.avg;
                    val.avg += delta / (count + 1);
                    float delta2 = newValue - val.avg;
                    val.m2 += delta * delta2;
                    val.var = val.m2 / (count + 1);   
                    val.current = newValue;
                }
                count++;
                return val;     
            };

            int getNumberOfMeasurements() { 
                return count;
            }

        private:
            int count = 0;
    };

    class StatFloatFilterSensor : public modular::Sensor<Statistics<float>> {
        public:
            virtual void measure() override {
                value  = f.filter(value, readSensorFloat());
            }

        protected:
            virtual float readSensorFloat() {
                return 0;
            }

        private:
            StatisticsFilter<float> f;
    };  

}