#include "platform/generic/TestReturnSensor.h"
#include "platform/generic/TestReturnTimeSensor.h"
#include "platform/generic/TestTimeManager.h"

#include "filter/StatisticsFilter.h"
#include <unity.h>

namespace platform = modular::platform::generic;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

// test the sensor get function 
void test_sensor_measure(void) {
    platform::TestReturnSensor sensor;
    sensor.setSensorValue(5);
    sensor.measure();
    TEST_ASSERT_EQUAL(5, sensor.getValue().current);
}

void test_sensor_reset(void) {
    platform::TestReturnSensor sensor;
    sensor.setSensorValue(5);
    sensor.measure();
    sensor.reset();
    TEST_ASSERT_EQUAL(0, sensor.getValue().current);
}

void test_sensor_filter(void) {
    platform::TestReturnSensor sensor;
    modular::filter::StatisticsFilter<float> filter;
    TEST_ASSERT_EQUAL(true, sensor.setFilter(filter));
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

void test_time_manager(void) {
    platform::TestTimeManager t{};
    platform::TestReturnTimeSensor sensor{t};
    sensor.setSensorValue(5);
    sensor.measure();
    platform::TimeValue v = sensor.getValue();
    TEST_ASSERT_EQUAL(1, v.timestamp);
}   

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_sensor_measure);
    RUN_TEST(test_sensor_reset);
    RUN_TEST(test_sensor_filter);
    RUN_TEST(test_time_manager);
    UNITY_END();
    return 0;
}