#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

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

// Global variables
static sensor_data_t sensors;
static filtered_data_t filtered;
static control_params_t control;
static system_state_t system_state;

// Function prototypes
void eps_initialize_system(void);
void eps_read_sensors(void);
void eps_filter_sensor_data(void);
float eps_calculate_base_assist_torque(float driver_torque, float vehicle_speed);
float eps_calculate_damping_component(float angular_velocity);
float eps_calculate_inertia_component(float angular_acceleration);
float eps_calculate_rtc_component(float steering_angle, float vehicle_speed);
void eps_calculate_assist_torque(void);
void eps_convert_torque_to_motor_command(void);
void eps_send_motor_command(void);
void eps_monitor_feedback(void);
bool eps_perform_self_diagnosis(void);
void eps_handle_fault(uint32_t fault_code);
float eps_low_pass_filter(float input, float prev_output, float alpha);
float eps_clamp_value(float value, float min_val, float max_val);

// Getter for sensor data
const sensor_data_t* eps_get_sensor_data(void) {
    return &sensors;
}

// Getter for control parameters
const control_params_t* eps_get_control_params(void) {
    return &control;
}

// Getter for system state
const system_state_t* eps_get_system_state(void) {
    return &system_state;
}

// Lookup table for base assist torque (simplified - in real implementation this would be a 2D table)
float eps_lookup_base_assist(float driver_torque, float vehicle_speed) {
    // Simplified mapping - in real implementation this would be a calibrated lookup table
    float base_assist = driver_torque * 2.0f;  // 2:1 assist ratio
    
    // Speed-dependent scaling
    if (vehicle_speed < 5.0f) {
        base_assist *= 1.5f;  // More assist at very low speeds
    } else if (vehicle_speed < 20.0f) {
        base_assist *= 1.2f;  // Moderate assist at low speeds
    } else if (vehicle_speed > 80.0f) {
        base_assist *= 0.7f;  // Less assist at high speeds
    }
    
    return base_assist;
}

// Initialize the EPS system
void eps_initialize_system(void) {
    memset(&sensors, 0, sizeof(sensors));
    memset(&filtered, 0, sizeof(filtered));
    memset(&control, 0, sizeof(control));
    memset(&system_state, 0, sizeof(system_state));
    
    system_state.system_initialized = true;
    system_state.loop_counter = 0;
    
    printf("EPS System Initialized\n");
}

// Read sensor inputs (simulated - in real implementation these would be hardware reads)
void eps_read_sensors(void) {
    // Simulate sensor readings - in real implementation these would be ADC reads or CAN messages
    // For demonstration, we'll simulate some realistic values
    
    // Simulate driver torque (random walk for demo)
    static float torque_offset = 0.0f;
    torque_offset += (float)(rand() % 100 - 50) / 1000.0f;  // Small random change
    sensors.driver_torque = eps_clamp_value(torque_offset, -20.0f, 20.0f);
    
    // Simulate steering angle (integrate from angular velocity)
    static float angle_offset = 0.0f;
    angle_offset += filtered.angular_velocity * SAMPLING_PERIOD_MS / 1000.0f;
    sensors.steering_angle = angle_offset;
    
    // Simulate vehicle speed (constant for demo)
    sensors.vehicle_speed = 30.0f;  // 30 km/h
    
    // Simulate motor feedback
    sensors.motor_current = control.motor_current_command * 0.95f;  // Simulate motor response
    sensors.motor_position += sensors.motor_current * 0.1f;  // Integrate position
}

// Apply low-pass filtering to sensor data
void eps_filter_sensor_data(void) {
    // Apply low-pass filter to remove noise
    filtered.filtered_torque = eps_low_pass_filter(sensors.driver_torque, 
                                                  filtered.filtered_torque, FILTER_ALPHA);
    filtered.filtered_angle = eps_low_pass_filter(sensors.steering_angle, 
                                                 filtered.filtered_angle, FILTER_ALPHA);
    filtered.filtered_speed = eps_low_pass_filter(sensors.vehicle_speed, 
                                                 filtered.filtered_speed, FILTER_ALPHA);
    
    // Calculate angular velocity (first derivative)
    float delta_angle = filtered.filtered_angle - system_state.prev_steering_angle;
    filtered.angular_velocity = delta_angle / (SAMPLING_PERIOD_MS / 1000.0f);
    
    // Calculate angular acceleration (second derivative)
    float delta_velocity = filtered.angular_velocity - system_state.prev_angular_velocity;
    filtered.angular_acceleration = delta_velocity / (SAMPLING_PERIOD_MS / 1000.0f);
    
    // Store previous values for next iteration
    system_state.prev_steering_angle = filtered.filtered_angle;
    system_state.prev_angular_velocity = filtered.angular_velocity;
}

// Calculate base assist torque using lookup table
float eps_calculate_base_assist_torque(float driver_torque, float vehicle_speed) {
    return eps_lookup_base_assist(driver_torque, vehicle_speed);
}

// Calculate damping component
float eps_calculate_damping_component(float angular_velocity) {
    return -DAMPING_COEFFICIENT * angular_velocity;
}

// Calculate inertia compensation component
float eps_calculate_inertia_component(float angular_acceleration) {
    return -INERTIA_COEFFICIENT * angular_acceleration;
}

// Calculate return-to-center component
float eps_calculate_rtc_component(float steering_angle, float vehicle_speed) {
    if (vehicle_speed < LOW_SPEED_THRESHOLD && fabs(steering_angle) > RTC_ANGLE_THRESHOLD) {
        return -RTC_COEFFICIENT * steering_angle;
    }
    return 0.0f;
}

// Main assist torque calculation
void eps_calculate_assist_torque(void) {
    // Base assist torque
    control.target_assist_torque = eps_calculate_base_assist_torque(
        filtered.filtered_torque, filtered.filtered_speed);
    
    // Add damping component
    control.target_assist_torque += eps_calculate_damping_component(filtered.angular_velocity);
    
    // Add inertia compensation
    control.target_assist_torque += eps_calculate_inertia_component(filtered.angular_acceleration);
    
    // Add return-to-center component
    control.target_assist_torque += eps_calculate_rtc_component(
        filtered.filtered_angle, filtered.filtered_speed);
    
    // ADAS integration (if active)
    if (control.adas_active) {
        control.target_assist_torque += control.adas_command_torque;
    }
    
    // Clamp assist torque within safe limits
    control.target_assist_torque = eps_clamp_value(control.target_assist_torque, 
                                                  MIN_ASSIST_LIMIT, MAX_ASSIST_LIMIT);
}

// Convert assist torque to motor current command
void eps_convert_torque_to_motor_command(void) {
    // Simplified conversion - in real implementation this would use motor characteristics
    // Torque = Kt * Current, where Kt is the motor torque constant
    float motor_torque_constant = 0.1f;  // Nm/A (example value)
    control.motor_current_command = control.target_assist_torque / motor_torque_constant;
    
    // Clamp motor current to safe limits
    control.motor_current_command = eps_clamp_value(control.motor_current_command, -10.0f, 10.0f);
}

// Send motor command to motor driver
void eps_send_motor_command(void) {
    // In real implementation, this would send PWM signals or CAN messages to motor driver
    // For simulation, we just store the command
    printf("Motor Command: %.2f A\n", control.motor_current_command);
}

// Monitor motor feedback and adjust control
void eps_monitor_feedback(void) {
    // In real implementation, this would read motor current and position feedback
    // and adjust control parameters based on the difference between commanded and actual values
    
    // Simple feedback monitoring for demonstration
    float current_error = control.motor_current_command - sensors.motor_current;
    if (fabs(current_error) > 0.5f) {
        printf("Motor current error: %.2f A\n", current_error);
    }
}

// Perform self-diagnosis checks
bool eps_perform_self_diagnosis(void) {
    // Check sensor ranges
    if (fabs(sensors.driver_torque) > 50.0f) {
        eps_handle_fault(0x01);  // Torque sensor fault
        return false;
    }
    
    if (fabs(sensors.steering_angle) > 720.0f) {
        eps_handle_fault(0x02);  // Steering angle sensor fault
        return false;
    }
    
    if (sensors.vehicle_speed < 0.0f || sensors.vehicle_speed > 200.0f) {
        eps_handle_fault(0x03);  // Vehicle speed sensor fault
        return false;
    }
    
    // Check motor current limits
    if (fabs(sensors.motor_current) > 15.0f) {
        eps_handle_fault(0x04);  // Motor overcurrent fault
        return false;
    }
    
    return true;
}

// Handle fault conditions
void eps_handle_fault(uint32_t fault_code) {
    system_state.fault_detected = true;
    system_state.fault_code = fault_code;
    
    printf("EPS Fault Detected: 0x%02X\n", fault_code);
    
    // In real implementation, this would:
    // - Log the fault
    // - Illuminate warning light
    // - Engage failsafe mode
    // - Potentially shut down the system
    
    // For demonstration, we'll reduce assist torque
    control.target_assist_torque *= 0.5f;
}

// Low-pass filter implementation
float eps_low_pass_filter(float input, float prev_output, float alpha) {
    return alpha * input + (1.0f - alpha) * prev_output;
}

// Clamp value between min and max
float eps_clamp_value(float value, float min_val, float max_val) {
    if (value < min_val) return min_val;
    if (value > max_val) return max_val;
    return value;
}

// Main EPS control loop
void eps_control_loop(void) {
    // A. Sensor Data Acquisition
    eps_read_sensors();
    
    // B. Data Processing and Analysis
    eps_filter_sensor_data();
    
    // C. Assist Torque Calculation (Core Logic)
    eps_calculate_assist_torque();
    
    // D. Motor Control
    eps_convert_torque_to_motor_command();
    eps_send_motor_command();
    
    // E. Feedback and Adjustment
    eps_monitor_feedback();
    
    // F. Fault Detection and Management
    if (!eps_perform_self_diagnosis()) {
        // Fault detected - system will continue in reduced mode
        printf("System operating in fault mode\n");
    }
    
    system_state.loop_counter++;
}

#ifndef EPS_UNIT_TEST
int main(void) {
    // Initialize the EPS system
    eps_initialize_system();
    
    printf("Starting EPS Control Loop...\n");
    printf("Press Ctrl+C to stop\n\n");
    
    // Main control loop
    while (1) {
        eps_control_loop();
        
        // Print status every 1000 iterations (1 second at 1kHz)
        if (system_state.loop_counter % 1000 == 0) {
            printf("Loop: %lu, Torque: %.2f Nm, Assist: %.2f Nm, Speed: %.1f km/h\n",
                   system_state.loop_counter,
                   filtered.filtered_torque,
                   control.target_assist_torque,
                   filtered.filtered_speed);
        }
        
        // In real implementation, this would be a precise timer-based delay
        // For simulation, we'll use a simple delay
        // usleep(SAMPLING_PERIOD_MS * 1000);  // Convert to microseconds
    }
    
    return 0;
}
#endif 