#include "platform/generic/ReturnSensor.h"
#include "filter/StatisticsFilter.h"

using namespace modular;

platform::generic::ReturnSensor<filter::Statistics<float>> sensor;
filter::Statistics<float> reference = {0};

int main() {
    filter::StatisticsFilter<float> filter;
    filter::Statistics<float> reference = {0};
    sensor.addFilter(filter);
    sensor.setSensorValue(1);
    sensor.measure();
    return 0;
}