#pragma once

#include "framework/Sensor.h"
#include "filter/StatisticsFilter.h"

namespace modular::platform::generic {

class RandomDataSensor : public Sensor<modular::filter::Statistics<float>, float> {
    public:
        RandomDataSensor(int rangeMin, int rangeMax);
        void measure();
        void reset();
    private:
        int rMin;
        int rMax;
        int count;
};

}