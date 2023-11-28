#ifndef RANDOMDATASENSOR_H
#define RANDOMDATASENSOR_H

#include "framework/Sensor.h"
#include "framework/DataStrctures.h"

namespace modular::devices::generic {

class RandomDataSensor : public Sensor<MinMaxAvg<int>> {
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

#endif