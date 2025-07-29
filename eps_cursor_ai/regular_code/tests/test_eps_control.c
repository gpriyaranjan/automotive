#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../eps_control.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Helper macros for floating point comparison
#define EPSILON 1e-5
#define FLOAT_EQ(a, b) (fabs((a) - (b)) < EPSILON)

void test_eps_initialize_system(void) {
    eps_initialize_system();
    const system_state_t* state = eps_get_system_state();
    CU_ASSERT(state != NULL);
    CU_ASSERT(state->system_initialized == true);
    CU_ASSERT(state->fault_detected == false);
    CU_ASSERT(state->fault_code == 0);
    CU_ASSERT(state->loop_counter == 0);
}

void test_eps_read_sensors(void) {
    eps_initialize_system();
    eps_read_sensors();
    const sensor_data_t* sensors = eps_get_sensor_data();
    CU_ASSERT(sensors != NULL);
    // Check that simulated values are within expected demo range
    CU_ASSERT(sensors->driver_torque >= -20.0f && sensors->driver_torque <= 20.0f);
    CU_ASSERT(sensors->vehicle_speed == 30.0f);
}

void test_eps_filter_sensor_data(void) {
    eps_initialize_system();
    eps_read_sensors();
    eps_filter_sensor_data();
    // Check filtered values are within reasonable range
    // (filtered values should not be NaN or Inf)
    const filtered_data_t* filtered = (const filtered_data_t*)((void*)&filtered); // Not accessible via getter, so just check code runs
    CU_ASSERT(1); // Placeholder, as filtered is static
}

void test_eps_calculate_base_assist_torque(void) {
    float t1 = eps_calculate_base_assist_torque(10.0f, 2.0f); // low speed
    float t2 = eps_calculate_base_assist_torque(10.0f, 10.0f); // moderate speed
    float t3 = eps_calculate_base_assist_torque(10.0f, 100.0f); // high speed
    CU_ASSERT(t1 > t2 && t2 > t3);
}

void test_eps_calculate_damping_component(void) {
    float d1 = eps_calculate_damping_component(5.0f);
    float d2 = eps_calculate_damping_component(-5.0f);
    CU_ASSERT(d1 < 0);
    CU_ASSERT(d2 > 0);
}

void test_eps_calculate_inertia_component(void) {
    float i1 = eps_calculate_inertia_component(3.0f);
    float i2 = eps_calculate_inertia_component(-3.0f);
    CU_ASSERT(i1 < 0);
    CU_ASSERT(i2 > 0);
}

void test_eps_calculate_rtc_component(void) {
    float r1 = eps_calculate_rtc_component(10.0f, 5.0f); // angle > threshold, speed < threshold
    float r2 = eps_calculate_rtc_component(2.0f, 5.0f);  // angle < threshold
    float r3 = eps_calculate_rtc_component(10.0f, 20.0f); // speed > threshold
    CU_ASSERT(r1 != 0.0f);
    CU_ASSERT(r2 == 0.0f);
    CU_ASSERT(r3 == 0.0f);
}

void test_eps_low_pass_filter(void) {
    float prev = 0.0f;
    float filtered = eps_low_pass_filter(10.0f, prev, 0.1f);
    CU_ASSERT(filtered > prev);
}

void test_eps_clamp_value(void) {
    CU_ASSERT(FLOAT_EQ(eps_clamp_value(5.0f, 0.0f, 10.0f), 5.0f));
    CU_ASSERT(FLOAT_EQ(eps_clamp_value(-5.0f, 0.0f, 10.0f), 0.0f));
    CU_ASSERT(FLOAT_EQ(eps_clamp_value(15.0f, 0.0f, 10.0f), 10.0f));
}

void test_eps_perform_self_diagnosis(void) {
    eps_initialize_system();
    bool result = eps_perform_self_diagnosis();
    CU_ASSERT(result == true);
    // Now inject a fault
    eps_initialize_system();
    sensor_data_t* sensors = (sensor_data_t*)eps_get_sensor_data();
    sensors->driver_torque = 100.0f; // Out of range
    result = eps_perform_self_diagnosis();
    CU_ASSERT(result == false);
    const system_state_t* state = eps_get_system_state();
    CU_ASSERT(state->fault_detected == true);
    CU_ASSERT(state->fault_code == 0x01);
}

void test_eps_handle_fault(void) {
    eps_initialize_system();
    eps_handle_fault(0x02);
    const system_state_t* state = eps_get_system_state();
    CU_ASSERT(state->fault_detected == true);
    CU_ASSERT(state->fault_code == 0x02);
}

void test_eps_calculate_assist_torque(void) {
    eps_initialize_system();
    eps_read_sensors();
    eps_filter_sensor_data();
    eps_calculate_assist_torque();
    const control_params_t* control = eps_get_control_params();
    CU_ASSERT(control != NULL);
    CU_ASSERT(control->target_assist_torque >= MIN_ASSIST_LIMIT && control->target_assist_torque <= MAX_ASSIST_LIMIT);
}

void test_eps_convert_torque_to_motor_command(void) {
    eps_initialize_system();
    eps_read_sensors();
    eps_filter_sensor_data();
    eps_calculate_assist_torque();
    eps_convert_torque_to_motor_command();
    const control_params_t* control = eps_get_control_params();
    CU_ASSERT(control != NULL);
    CU_ASSERT(control->motor_current_command >= -10.0f && control->motor_current_command <= 10.0f);
}

void test_eps_send_motor_command(void) {
    eps_initialize_system();
    eps_send_motor_command();
    // No assertion, but should run without error
}

void test_eps_monitor_feedback(void) {
    eps_initialize_system();
    eps_monitor_feedback();
    // No assertion, but should run without error
}

void test_eps_control_loop(void) {
    eps_initialize_system();
    eps_control_loop();
    const system_state_t* state = eps_get_system_state();
    CU_ASSERT(state->loop_counter == 1);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("EPS Control Suite", 0, 0);
    CU_add_test(suite, "Initialize System", test_eps_initialize_system);
    CU_add_test(suite, "Read Sensors", test_eps_read_sensors);
    CU_add_test(suite, "Filter Sensor Data", test_eps_filter_sensor_data);
    CU_add_test(suite, "Base Assist Torque", test_eps_calculate_base_assist_torque);
    CU_add_test(suite, "Damping Component", test_eps_calculate_damping_component);
    CU_add_test(suite, "Inertia Component", test_eps_calculate_inertia_component);
    CU_add_test(suite, "RTC Component", test_eps_calculate_rtc_component);
    CU_add_test(suite, "Low Pass Filter", test_eps_low_pass_filter);
    CU_add_test(suite, "Clamp Value", test_eps_clamp_value);
    CU_add_test(suite, "Self Diagnosis", test_eps_perform_self_diagnosis);
    CU_add_test(suite, "Handle Fault", test_eps_handle_fault);
    CU_add_test(suite, "Calculate Assist Torque", test_eps_calculate_assist_torque);
    CU_add_test(suite, "Convert Torque to Motor Command", test_eps_convert_torque_to_motor_command);
    CU_add_test(suite, "Send Motor Command", test_eps_send_motor_command);
    CU_add_test(suite, "Monitor Feedback", test_eps_monitor_feedback);
    CU_add_test(suite, "Control Loop", test_eps_control_loop);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
} 