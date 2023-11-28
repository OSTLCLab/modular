#ifndef SENSOR_H
#define SENSOR_H

namespace modular {

template <typename V>

class Sensor {
    public:
        virtual void measure() {};
        V getValue() {
            return value;
        }
        void addFilter() {};
        virtual void reset() {};

    protected:
        V value;
};

}

#endif