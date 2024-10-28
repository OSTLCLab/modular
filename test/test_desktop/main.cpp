#include "platform/generic/TestReturnSensor.h"
#include "platform/generic/TestReturnTimeSensor.h"
#include "platform/generic/TestTimeManager.h"
#include "filter/StatisticsFilter.h"
#include "framework/Fsm.h"

#include <unity.h>

namespace platform = modular::platform::generic;

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

// State machine variables
// Define Events
#define FLIP_LIGHT_SWITCH 1

// Define State and transition functions
void on_light_on_enter();
void on_light_on_exit();
void on_light_off_enter();
void on_light_off_exit();
void on_trans_light_on_light_off();
void on_trans_light_off_light_on();

// Define States
State state_light_on (&on_light_on_enter,  NULL, &on_light_on_exit);
State state_light_off(&on_light_off_enter, NULL, &on_light_off_exit);
Fsm fsm(&state_light_off);

int fsm_step = 0;

void on_light_on_enter() {
    fsm_step++;
}

void on_light_on_exit() {
    fsm_step++;
}

void on_light_off_enter() {
    fsm_step++;
}

void on_light_off_exit() {
    fsm_step++;
}

void test_fsm() {
    fsm.run_machine();              // enter light off
    fsm.trigger(FLIP_LIGHT_SWITCH); // exit light off, enter light on
    TEST_ASSERT_EQUAL(3, fsm_step); 
    TEST_ASSERT_EQUAL(&state_light_on, fsm.getCurrentState());
    fsm.trigger(FLIP_LIGHT_SWITCH);
    TEST_ASSERT_EQUAL(5, fsm_step); // exit light off, enter light on
    TEST_ASSERT_EQUAL(&state_light_off, fsm.getCurrentState());
}

void setUp(void) {
    fsm.add_transition(&state_light_on,  &state_light_off, FLIP_LIGHT_SWITCH, NULL);
    fsm.add_transition(&state_light_off, &state_light_on,  FLIP_LIGHT_SWITCH, NULL);
}

void tearDown(void) {
    // clean stuff up here
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_sensor_measure);
    RUN_TEST(test_sensor_reset);
    RUN_TEST(test_sensor_filter);
    RUN_TEST(test_time_manager);
    RUN_TEST(test_fsm);
    UNITY_END();
    return 0;
}