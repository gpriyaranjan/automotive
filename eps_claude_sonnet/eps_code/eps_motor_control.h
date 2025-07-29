/**
 * @file eps_motor_control.h
 * @brief Electronic Power Steering (EPS) Motor Control Module Header
 * @version 1.0
 * @date 2025-07-29
 * 
 * This header file defines the motor control functions and data structures
 * for the EPS system according to the motor control requirements.
 * 
 * Requirements Traceability:
 * - EPS-FR-012 to EPS-FR-016: Motor Control Functions
 * - EPS-IR-050 to EPS-IR-063: Motor Drive Interface Requirements
 * - EPS-ER-026 to EPS-ER-037: Motor Drive Electrical Requirements
 */

#ifndef EPS_MOTOR_CONTROL_H
#define EPS_MOTOR_CONTROL_H

#include "eps_main.h"

/* Motor Control Constants */
#define EPS_MOTOR_MAX_CURRENT_A         50.0f   /* A - EPS-ER-027 */
#define EPS_MOTOR_PEAK_CURRENT_A        100.0f  /* A - EPS-ER-028 */
#define EPS_MOTOR_MAX_VOLTAGE_V         12.0f   /* V - EPS-ER-029 */
#define EPS_MOTOR_PWM_FREQUENCY_HZ      20000   /* Hz - EPS-ER-030 */
#define EPS_MOTOR_MAX_SPEED_RPM         3000    /* RPM - EPS-IR-041 */
#define EPS_MOTOR_POLE_PAIRS            4       /* Motor pole pairs */
#define EPS_MOTOR_TORQUE_CONSTANT       0.1f    /* Nm/A */

/* Motor Control Modes */
typedef enum {
    EPS_MOTOR_MODE_DISABLED = 0,
    EPS_MOTOR_MODE_TORQUE_CONTROL,
    EPS_MOTOR_MODE_SPEED_CONTROL,
    EPS_MOTOR_MODE_POSITION_CONTROL,
    EPS_MOTOR_MODE_FAULT
} eps_motor_control_mode_t;

/* Motor Status */
typedef enum {
    EPS_MOTOR_STATUS_STOPPED = 0,
    EPS_MOTOR_STATUS_RUNNING,
    EPS_MOTOR_STATUS_FAULT,
    EPS_MOTOR_STATUS_OVERTEMP,
    EPS_MOTOR_STATUS_OVERCURRENT
} eps_motor_status_t;

/* Motor Feedback Data */
typedef struct {
    float position_deg;             /* deg - Motor rotor position */
    float velocity_rpm;             /* rpm - Motor speed */
    float current_a[3];             /* A - Three-phase currents */
    float voltage_v[3];             /* V - Three-phase voltages */
    float temperature_c;            /* °C - Motor temperature */
    uint32_t timestamp;             /* ms - Data timestamp */
    bool data_valid;                /* Data validity flag */
} eps_motor_feedback_t;

/* Motor Control Parameters */
typedef struct {
    float kp_torque;                /* Torque control proportional gain */
    float ki_torque;                /* Torque control integral gain */
    float kd_torque;                /* Torque control derivative gain */
    float current_limit_a;          /* A - Current limit */
    float voltage_limit_v;          /* V - Voltage limit */
    float temperature_limit_c;      /* °C - Temperature limit */
    uint16_t pwm_deadtime_ns;       /* ns - PWM deadtime */
} eps_motor_control_params_t;

/* Motor Control State */
typedef struct {
    eps_motor_control_mode_t mode;
    eps_motor_status_t status;
    eps_motor_feedback_t feedback;
    eps_motor_control_params_t params;
    float target_torque;
    float actual_torque;
    uint32_t fault_flags;
    uint32_t last_update_time;
    bool enabled;
} eps_motor_control_state_t;

/* Function Prototypes */

/**
 * @brief Initialize motor control subsystem
 * @return eps_result_t Initialization result
 * 
 * Requirements: EPS-FR-012, EPS-IR-050
 */
eps_result_t eps_motor_control_init(void);

/**
 * @brief Execute motor control command
 * @param command Pointer to motor command structure
 * @return eps_result_t Execution result
 * 
 * Requirements: EPS-FR-013, EPS-PR-014
 */
eps_result_t eps_motor_control_execute(const eps_motor_command_t* command);

/**
 * @brief Disable motor control
 * 
 * Requirements: EPS-SR-050
 */
void eps_motor_control_disable(void);

/**
 * @brief Enable motor control
 * @return eps_result_t Enable result
 */
eps_result_t eps_motor_control_enable(void);

/**
 * @brief Set motor torque limit
 * @param torque_limit_nm Maximum torque limit in Nm
 * @return eps_result_t Result of setting limit
 * 
 * Requirements: EPS-SR-021
 */
eps_result_t eps_motor_control_limit_torque(float torque_limit_nm);

/**
 * @brief Get motor feedback data
 * @param feedback Pointer to feedback data structure
 * @return eps_result_t Result of reading feedback
 * 
 * Requirements: EPS-IR-060, EPS-IR-061
 */
eps_result_t eps_motor_control_get_feedback(eps_motor_feedback_t* feedback);

/**
 * @brief Perform motor control self-test
 * @return eps_result_t Self-test result
 * 
 * Requirements: EPS-DR-081
 */
eps_result_t eps_motor_control_self_test(void);

/**
 * @brief Update motor control parameters
 * @param params Pointer to new parameters
 * @return eps_result_t Update result
 */
eps_result_t eps_motor_control_update_params(const eps_motor_control_params_t* params);

/**
 * @brief Get current motor control state
 * @return const eps_motor_control_state_t* Pointer to current state
 */
const eps_motor_control_state_t* eps_motor_control_get_state(void);

/**
 * @brief Check for motor faults
 * @return uint32_t Fault flags bitmask
 * 
 * Requirements: EPS-ER-034 to EPS-ER-037
 */
uint32_t eps_motor_control_check_faults(void);

/**
 * @brief Clear motor faults
 * @param fault_mask Bitmask of faults to clear
 * @return eps_result_t Clear result
 */
eps_result_t eps_motor_control_clear_faults(uint32_t fault_mask);

/**
 * @brief Calculate motor torque from current
 * @param current_a Motor current in Amperes
 * @return float Motor torque in Nm
 */
float eps_motor_control_current_to_torque(float current_a);

/**
 * @brief Calculate required current for target torque
 * @param torque_nm Target torque in Nm
 * @return float Required current in Amperes
 */
float eps_motor_control_torque_to_current(float torque_nm);

/**
 * @brief Update PWM duty cycles
 * @param duty_cycles Array of 3 duty cycle values (0-1000)
 * @return eps_result_t Update result
 * 
 * Requirements: EPS-IR-051, EPS-IR-052
 */
eps_result_t eps_motor_control_update_pwm(const uint16_t duty_cycles[3]);

/**
 * @brief Perform field-oriented control calculation
 * @param feedback Pointer to motor feedback data
 * @param target_torque Target torque in Nm
 * @param duty_cycles Output PWM duty cycles
 * @return eps_result_t Calculation result
 * 
 * Requirements: EPS-IR-057, EPS-ER-032
 */
eps_result_t eps_motor_control_foc_calculate(const eps_motor_feedback_t* feedback,
                                           float target_torque,
                                           uint16_t duty_cycles[3]);

/* Motor Fault Flags */
#define EPS_MOTOR_FAULT_NONE            0x00000000
#define EPS_MOTOR_FAULT_OVERCURRENT     0x00000001
#define EPS_MOTOR_FAULT_OVERVOLTAGE     0x00000002
#define EPS_MOTOR_FAULT_UNDERVOLTAGE    0x00000004
#define EPS_MOTOR_FAULT_OVERTEMP        0x00000008
#define EPS_MOTOR_FAULT_POSITION_SENSOR 0x00000010
#define EPS_MOTOR_FAULT_CURRENT_SENSOR  0x00000020
#define EPS_MOTOR_FAULT_PWM_FAULT       0x00000040
#define EPS_MOTOR_FAULT_COMMUNICATION   0x00000080
#define EPS_MOTOR_FAULT_STALL           0x00000100
#define EPS_MOTOR_FAULT_OVERSPEED       0x00000200

#endif /* EPS_MOTOR_CONTROL_H */