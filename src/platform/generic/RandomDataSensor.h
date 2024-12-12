#pragma once

#include "framework/Sensor.h"
#include "filter/StatisticsFilter.h"

namespace modular::platform::generic {

class RandomDataSensor : public Sensor<modular::filter::Statistics<float>> {
    public:
        RandomDataSensor(int rangeMin, int rangeMax);
        virtual void measure();
        virtual void reset();
    private:
        int rMin;
        int rMax;
        int count;
};

}