#include "platform/generic/ReturnSensor.h"
#include "filter/StatisticsFilter.h"
#include <unity.h>

using namespace modular;

platform::generic::ReturnSensor<filter::Statistics<float>> sensor;
filter::Statistics<float> reference = {0};

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

// test the sensor get function 
void test_sensor_measure(void) {
    sensor.setSensorValue(5);
    sensor.measure();
    TEST_ASSERT_EQUAL(5, sensor.getValue().last);
}

void test_sensor_reset(void) {
    sensor.setSensorValue(5);
    sensor.measure();
    sensor.reset();
    TEST_ASSERT_EQUAL(0, sensor.getValue().last);
}

void test_sensor_filter(void) {
    filter::StatisticsFilter<float> filter;
    filter::Statistics<float> reference = {0};
    TEST_ASSERT_EQUAL(true, sensor.addFilter(filter));
    sensor.setSensorValue(1);
    sensor.measure();
    sensor.setSensorValue(2);
    sensor.measure();
    sensor.setSensorValue(3);
    sensor.measure();
    TEST_ASSERT_EQUAL(1, sensor.getValue().min);
    TEST_ASSERT_EQUAL(3, sensor.getValue().max);
    TEST_ASSERT_EQUAL(2, sensor.getValue().avg);
}

// Test Statistics filter   sensor.setSensorValue(5);

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_sensor_measure);
    RUN_TEST(test_sensor_reset);
    RUN_TEST(test_sensor_filter);
    UNITY_END();
    return 0;
}