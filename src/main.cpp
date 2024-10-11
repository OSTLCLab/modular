#include "platform/generic/ReturnSensor.h"
#include "filter/StatisticsFilter.h"

using namespace modular;

platform::generic::ReturnSensor<filter::Statistics<float>> sensor;

int main() {
    filter::StatisticsFilter<float> filter;
    sensor.addFilter(filter);
    sensor.setSensorValue(1);
    sensor.measure();
    return 0;
}