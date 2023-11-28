#ifndef VOLTAGESENSOR_H
#define VOLTAGESENSOR_H

#include "framework/Sensor.h"
#include "framework/DataStrctures.h"

namespace modular::devices::arduino {

class VoltageSensor : public Sensor<MinMaxAvg<float>> {
    public:
        VoltageSensor(int pinVoltage, float referenceVoltage);
        void measure();
        void reset();
    private:
        int pinVoltage;
        float referenceVoltage;
        int count;
};

}

#endif