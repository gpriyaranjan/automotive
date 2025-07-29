/**
 * @file eps_main.h
 * @brief Electronic Power Steering (EPS) System Main Header
 * @version 1.0
 * @date 2025-07-29
 * 
 * This header file defines the main EPS system data structures, constants,
 * and function prototypes according to the EPS System Requirements.
 */

#ifndef EPS_MAIN_H
#define EPS_MAIN_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/* System Constants - Based on Performance Requirements */
#define EPS_MAX_ASSISTANCE_TORQUE       8.0f    /* Nm - EPS-PR-002 */
#define EPS_MIN_TORQUE_THRESHOLD        0.1f    /* Nm - EPS-PR-003 */
#define EPS_MAX_RESPONSE_TIME_MS        50      /* ms - EPS-PR-014 */
#define EPS_SYSTEM_CYCLE_TIME_MS        1       /* ms - EPS-PR-019 */
#define EPS_WATCHDOG_TIMEOUT_MS         100     /* ms - EPS-SR-041 */

/* Speed-Sensitive Steering Constants - EPS-PR-040 */
#define EPS_LOW_SPEED_THRESHOLD         10.0f   /* km/h */
#define EPS_HIGH_SPEED_THRESHOLD        100.0f  /* km/h */
#define EPS_MIN_ASSISTANCE_FACTOR       0.3f    /* 30% at high speeds */

/* Control Parameters */
#define EPS_BASE_ASSISTANCE_GAIN        1.5f
#define EPS_RETURN_TO_CENTER_GAIN       0.02f   /* Nm/deg - EPS-PR-034 */
#define EPS_RETURN_TO_CENTER_THRESHOLD  1.0f    /* Nm */
#define EPS_DAMPING_COEFFICIENT         0.05f   /* Nm*s/deg - EPS-PR-037 */
#define EPS_SPEED_RTC_FACTOR            0.01f
#define EPS_SPEED_DAMPING_FACTOR        0.02f

/* Safety Limits */
#define EPS_MAX_ASSISTANCE_RATE         10.0f   /* Nm/s - EPS-FR-005 */
#define EPS_DEGRADED_MAX_TORQUE         4.0f    /* Nm */
#define EPS_OSCILLATION_BUFFER_SIZE     10
#define EPS_TORQUE_CHANGE_THRESHOLD     0.5f    /* Nm */

/* System Result Codes */
typedef enum {
    EPS_SUCCESS = 0,
    EPS_ERROR_NULL_POINTER,
    EPS_ERROR_INVALID_PARAMETER,
    EPS_ERROR_SENSOR_FAULT,
    EPS_ERROR_MOTOR_FAULT,
    EPS_ERROR_COMMUNICATION_FAULT,
    EPS_ERROR_SAFETY_FAULT,
    EPS_ERROR_POWER_FAULT,
    EPS_ERROR_DIRECTION_MISMATCH,
    EPS_ERROR_OSCILLATION_DETECTED,
    EPS_ERROR_TIMEOUT,
    EPS_ERROR_CALIBRATION_FAULT,
    EPS_ERROR_SYSTEM_NOT_READY
} eps_result_t;

/* System Operating Modes - EPS-FR-033 to EPS-FR-042 */
typedef enum {
    EPS_MODE_INIT = 0,
    EPS_MODE_NORMAL,
    EPS_MODE_DEGRADED,
    EPS_MODE_FAIL_SAFE,
    EPS_MODE_SLEEP
} eps_operating_mode_t;

/* System Status */
typedef enum {
    EPS_STATUS_INITIALIZING = 0,
    EPS_STATUS_READY,
    EPS_STATUS_ACTIVE,
    EPS_STATUS_DEGRADED,
    EPS_STATUS_FAULT,
    EPS_STATUS_SLEEP
} eps_system_status_t;

/* Fault Severity Levels */
typedef enum {
    EPS_FAULT_NONE = 0,
    EPS_FAULT_MINOR,
    EPS_FAULT_MAJOR,
    EPS_FAULT_CRITICAL
} eps_fault_severity_t;

/* Sensor Data Structure - EPS-IR-025 to EPS-IR-049 */
typedef struct {
    float driver_torque;            /* Nm - Driver input torque */
    float steering_angle;           /* deg - Steering wheel angle */
    float steering_velocity;        /* deg/s - Steering angular velocity */
    float vehicle_speed;            /* km/h - Vehicle speed */
    float motor_position;           /* deg - Motor rotor position */
    float motor_velocity;           /* rpm - Motor speed */
    float ecu_temperature;          /* °C - ECU temperature */
    float motor_temperature;        /* °C - Motor temperature */
    uint32_t timestamp;             /* ms - Data timestamp */
    bool data_valid;                /* Data validity flag */
} eps_sensor_data_t;

/* Assistance Parameters Structure */
typedef struct {
    float base_assistance;          /* Nm - Base assistance torque */
    float return_to_center;         /* Nm - Return-to-center torque */
    float damping;                  /* Nm - Damping torque */
    float total_assistance;         /* Nm - Total assistance torque */
    float speed_factor;             /* Speed-based scaling factor */
    uint32_t calculation_timestamp; /* ms - Calculation timestamp */
    bool safety_limited;            /* Safety limiting applied flag */
    bool rate_limited;              /* Rate limiting applied flag */
    bool oscillation_detected;      /* Oscillation detection flag */
} eps_assistance_params_t;

/* Motor Command Structure - EPS-IR-050 to EPS-IR-059 */
typedef struct {
    float target_torque;            /* Nm - Target motor torque */
    float current_limit;            /* A - Motor current limit */
    uint16_t pwm_duty_cycle[3];     /* PWM duty cycles for 3 phases */
    bool enable;                    /* Motor enable flag */
    uint32_t command_timestamp;     /* ms - Command timestamp */
} eps_motor_command_t;

/* System State Structure */
typedef struct {
    eps_operating_mode_t operating_mode;
    eps_system_status_t system_status;
    uint32_t system_uptime_ms;
    uint32_t fault_count;
    uint32_t last_fault_time;
    bool manual_steering_available;
    bool assistance_enabled;
} eps_system_state_t;

/* Safety State Structure */
typedef struct {
    bool watchdog_active;
    uint32_t last_watchdog_reset;
    eps_result_t last_fault_code;
    uint32_t fault_count;
    uint32_t last_fault_time;
    bool safety_mechanisms_active;
    bool redundancy_available;
} eps_safety_state_t;

/* Performance Data Structure - EPS-PR-051 */
typedef struct {
    uint32_t last_response_time_ms;
    uint32_t max_response_time_ms;
    float current_power_consumption;
    float max_power_consumption;
    float ecu_temperature;
    float motor_temperature;
    uint32_t system_uptime_ms;
    uint32_t total_steering_cycles;
} eps_performance_data_t;

/* Diagnostic Trouble Codes - EPS-DR-031 */
typedef enum {
    EPS_DTC_NO_FAULT = 0x0000,
    EPS_DTC_TORQUE_SENSOR_FAULT = 0x1001,
    EPS_DTC_ANGLE_SENSOR_FAULT = 0x1002,
    EPS_DTC_MOTOR_FAULT = 0x2001,
    EPS_DTC_POWER_SUPPLY_FAULT = 0x3001,
    EPS_DTC_COMMUNICATION_FAULT = 0x4001,
    EPS_DTC_EXCESSIVE_ASSISTANCE = 0x5001,
    EPS_DTC_DIRECTION_MISMATCH = 0x5002,
    EPS_DTC_OSCILLATION_DETECTED = 0x5003,
    EPS_DTC_SLOW_RESPONSE = 0x6001,
    EPS_DTC_OVERTEMPERATURE = 0x7001
} eps_dtc_code_t;

/* Function Prototypes */

/**
 * @brief Initialize the EPS system
 * @return eps_result_t System initialization result
 */
eps_result_t eps_system_init(void);

/**
 * @brief Main EPS system task - called every 1ms
 * @return eps_result_t Task execution result
 */
eps_result_t eps_system_task(void);

/**
 * @brief System shutdown procedure
 * @return eps_result_t Shutdown result
 */
eps_result_t eps_system_shutdown(void);

/**
 * @brief Get current system state
 * @return const eps_system_state_t* Pointer to current system state
 */
const eps_system_state_t* eps_get_system_state(void);

/**
 * @brief Get current performance data
 * @return const eps_performance_data_t* Pointer to current performance data
 */
const eps_performance_data_t* eps_get_performance_data(void);

/* Internal Function Prototypes */
static eps_result_t eps_calculate_assistance(const eps_sensor_data_t* sensor_data, 
                                           eps_assistance_params_t* assistance_params);
static eps_result_t eps_apply_safety_limits(eps_assistance_params_t* assistance_params);
static void eps_update_performance_data(const eps_sensor_data_t* sensor_data);
static eps_result_t eps_handle_safety_fault(eps_result_t fault_code);
static eps_result_t eps_handle_sensor_fault(eps_result_t fault_code);
static eps_result_t eps_handle_motor_fault(eps_result_t fault_code);
static eps_result_t eps_handle_communication_fault(eps_result_t fault_code);
static eps_result_t eps_handle_calculation_fault(eps_result_t fault_code);
static eps_result_t eps_handle_diagnostic_fault(eps_result_t fault_code);
static eps_result_t eps_system_self_test(void);
static eps_result_t eps_generate_motor_command(const eps_assistance_params_t* assistance_params,
                                             eps_motor_command_t* motor_command);
static bool eps_detect_oscillation(const float* data, uint8_t size);
static eps_fault_severity_t eps_get_fault_severity(eps_result_t fault_code);
static eps_dtc_code_t eps_get_dtc_for_fault(eps_result_t fault_code);

#endif /* EPS_MAIN_H */