#ifndef EPS_CONTROL_H
#define EPS_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

// Configuration constants
#define SAMPLING_RATE_HZ          1000    // 1kHz sampling rate
#define SAMPLING_PERIOD_MS        1       // 1ms period
#define LOW_SPEED_THRESHOLD       10.0f   // 10 km/h
#define RTC_ANGLE_THRESHOLD       5.0f    // 5 degrees
#define MIN_ASSIST_LIMIT          -50.0f  // Nm
#define MAX_ASSIST_LIMIT          50.0f   // Nm
#define FILTER_ALPHA              0.1f    // Low-pass filter coefficient
#define DAMPING_COEFFICIENT       0.5f    // Damping coefficient
#define INERTIA_COEFFICIENT       0.2f    // Inertia compensation coefficient
#define RTC_COEFFICIENT           0.3f    // Return-to-center coefficient

// Fault codes
#define FAULT_TORQUE_SENSOR       0x01
#define FAULT_ANGLE_SENSOR        0x02
#define FAULT_SPEED_SENSOR        0x03
#define FAULT_MOTOR_OVERCURRENT   0x04
#define FAULT_COMMUNICATION       0x05
#define FAULT_MOTOR_DRIVER        0x06

// Sensor data structure
typedef struct {
    float driver_torque;      // Driver applied torque (Nm)
    float steering_angle;     // Steering angle (degrees)
    float vehicle_speed;      // Vehicle speed (km/h)
    float motor_current;      // Motor current (A)
    float motor_position;     // Motor position (degrees)
} sensor_data_t;

// Filtered data structure
typedef struct {
    float filtered_torque;
    float filtered_angle;
    float filtered_speed;
    float angular_velocity;
    float angular_acceleration;
} filtered_data_t;

// Control parameters
typedef struct {
    float target_assist_torque;
    float motor_current_command;
    bool adas_active;
    float adas_command_torque;
} control_params_t;

// System state
typedef struct {
    bool system_initialized;
    bool fault_detected;
    uint32_t fault_code;
    uint32_t loop_counter;
    float prev_angular_velocity;
    float prev_steering_angle;
} system_state_t;

// Function declarations

/**
 * @brief Initialize the EPS system
 * 
 * Initializes all data structures and sets up the system for operation.
 * Must be called before starting the control loop.
 */
void eps_initialize_system(void);

/**
 * @brief Read sensor inputs
 * 
 * Reads data from torque sensor, steering angle sensor, vehicle speed sensor,
 * and motor feedback sensors. In real implementation, this would involve
 * hardware reads from ADCs or CAN messages.
 */
void eps_read_sensors(void);

/**
 * @brief Filter and process sensor data
 * 
 * Applies low-pass filtering to remove noise and calculates derived values
 * such as angular velocity and acceleration.
 */
void eps_filter_sensor_data(void);

/**
 * @brief Calculate base assist torque
 * 
 * @param driver_torque Driver applied torque in Nm
 * @param vehicle_speed Vehicle speed in km/h
 * @return Base assist torque in Nm
 */
float eps_calculate_base_assist_torque(float driver_torque, float vehicle_speed);

/**
 * @brief Calculate damping component
 * 
 * @param angular_velocity Steering angular velocity in deg/s
 * @return Damping torque component in Nm
 */
float eps_calculate_damping_component(float angular_velocity);

/**
 * @brief Calculate inertia compensation component
 * 
 * @param angular_acceleration Steering angular acceleration in deg/s²
 * @return Inertia compensation torque in Nm
 */
float eps_calculate_inertia_component(float angular_acceleration);

/**
 * @brief Calculate return-to-center component
 * 
 * @param steering_angle Current steering angle in degrees
 * @param vehicle_speed Vehicle speed in km/h
 * @return RTC torque component in Nm
 */
float eps_calculate_rtc_component(float steering_angle, float vehicle_speed);

/**
 * @brief Calculate total assist torque
 * 
 * Combines base assist, damping, inertia compensation, RTC, and ADAS components
 * to calculate the final target assist torque.
 */
void eps_calculate_assist_torque(void);

/**
 * @brief Convert assist torque to motor current command
 * 
 * Converts the calculated assist torque to a motor current command
 * using the motor's torque constant.
 */
void eps_convert_torque_to_motor_command(void);

/**
 * @brief Send motor command to motor driver
 * 
 * Sends the motor current command to the motor driver. In real implementation,
 * this would involve PWM signals or CAN messages.
 */
void eps_send_motor_command(void);

/**
 * @brief Monitor motor feedback
 * 
 * Monitors actual motor current and position feedback and adjusts
 * control parameters based on the difference between commanded and actual values.
 */
void eps_monitor_feedback(void);

/**
 * @brief Perform self-diagnosis checks
 * 
 * Performs various diagnostic checks on sensors, motor, and system health.
 * @return true if no faults detected, false otherwise
 */
bool eps_perform_self_diagnosis(void);

/**
 * @brief Handle fault conditions
 * 
 * @param fault_code The fault code indicating the type of fault
 */
void eps_handle_fault(uint32_t fault_code);

/**
 * @brief Low-pass filter implementation
 * 
 * @param input Current input value
 * @param prev_output Previous filtered output
 * @param alpha Filter coefficient (0-1)
 * @return Filtered output value
 */
float eps_low_pass_filter(float input, float prev_output, float alpha);

/**
 * @brief Clamp value between minimum and maximum
 * 
 * @param value Input value to clamp
 * @param min_val Minimum allowed value
 * @param max_val Maximum allowed value
 * @return Clamped value
 */
float eps_clamp_value(float value, float min_val, float max_val);

/**
 * @brief Main EPS control loop
 * 
 * This is the main control loop that implements the complete EPS algorithm.
 * It should be called at the specified sampling rate (1kHz).
 */
void eps_control_loop(void);

/**
 * @brief Get current sensor data
 * 
 * @return Pointer to current sensor data structure
 */
const sensor_data_t* eps_get_sensor_data(void);

/**
 * @brief Get current control parameters
 * 
 * @return Pointer to current control parameters structure
 */
const control_params_t* eps_get_control_params(void);

/**
 * @brief Get system state
 * 
 * @return Pointer to current system state structure
 */
const system_state_t* eps_get_system_state(void);

/**
 * @brief Set ADAS command
 * 
 * @param active Whether ADAS is active
 * @param command_torque ADAS command torque in Nm
 */
void eps_set_adas_command(bool active, float command_torque);

#endif // EPS_CONTROL_H 