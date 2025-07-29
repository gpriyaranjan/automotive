/**
 * @file ebs_abs.h
 * @brief Electronic Braking System - Anti-lock Braking System Module
 * @version 1.0
 * @date 2025-07-29
 * @author EBS Development Team
 * 
 * ABS control algorithm and functions
 * 
 * Safety Level: ASIL-D
 * Compliance: ISO 26262, UN-ECE R13-H
 */

#ifndef EBS_ABS_H
#define EBS_ABS_H

#include "ebs_types.h"
#include "ebs_config.h"

/* ABS Function Prototypes */

/**
 * @brief Initialize ABS system
 * @return ebs_result_t Initialization result
 */
ebs_result_t EBS_ABS_Init(void);

/**
 * @brief Perform ABS self-test
 * @return bool True if self-test passed
 */
bool EBS_ABS_SelfTest(void);

/**
 * @brief Main ABS control function (called every 1ms)
 * @return ebs_result_t Control result
 */
ebs_result_t EBS_ABS_Control(void);

/**
 * @brief Get ABS state for specific wheel
 * @param wheel Wheel position
 * @return ebs_abs_state_t ABS state
 */
ebs_abs_state_t EBS_ABS_GetState(ebs_wheel_position_t wheel);

/**
 * @brief Check if ABS is active on any wheel
 * @return bool True if ABS is active
 */
bool EBS_ABS_IsActive(void);

/**
 * @brief Get ABS activation count for wheel
 * @param wheel Wheel position
 * @return uint32_t Activation count
 */
uint32_t EBS_ABS_GetActivationCount(ebs_wheel_position_t wheel);

/**
 * @brief Calculate wheel slip ratio
 * @param wheel_speed Wheel speed in km/h
 * @param vehicle_speed Vehicle speed in km/h
 * @return float Slip ratio (0.0 to 1.0)
 */
float EBS_ABS_CalculateSlipRatio(float wheel_speed, float vehicle_speed);

/**
 * @brief Calculate vehicle reference speed
 * @param wheel_speeds Array of wheel speeds
 * @return float Estimated vehicle speed in km/h
 */
float EBS_ABS_CalculateVehicleSpeed(const float* wheel_speeds);

/**
 * @brief ABS pressure modulation control
 * @param wheel Wheel position
 * @param slip_ratio Current slip ratio
 * @param target_slip Target slip ratio
 * @return float Pressure command (0.0 to 1.0)
 */
float EBS_ABS_PressureModulation(ebs_wheel_position_t wheel, float slip_ratio, float target_slip);

/**
 * @brief Update ABS state machine for wheel
 * @param wheel Wheel position
 * @param slip_ratio Current slip ratio
 * @param wheel_acceleration Wheel acceleration
 * @return ebs_result_t Update result
 */
ebs_result_t EBS_ABS_UpdateStateMachine(ebs_wheel_position_t wheel, float slip_ratio, 
                                        float wheel_acceleration);

/**
 * @brief Get ABS performance statistics
 * @param wheel Wheel position
 * @param stats Pointer to statistics structure
 * @return ebs_result_t Operation result
 */
ebs_result_t EBS_ABS_GetStatistics(ebs_wheel_position_t wheel, void* stats);

/**
 * @brief Reset ABS system
 * @return ebs_result_t Reset result
 */
ebs_result_t EBS_ABS_Reset(void);

/**
 * @brief Enable/disable ABS function
 * @param enable True to enable, false to disable
 * @return ebs_result_t Operation result
 */
ebs_result_t EBS_ABS_Enable(bool enable);

/**
 * @brief Check ABS system health
 * @return bool True if system is healthy
 */
bool EBS_ABS_HealthCheck(void);

/* ABS Algorithm Parameters */
#define ABS_SLIP_THRESHOLD_DEFAULT      0.15f   /* Default slip threshold */
#define ABS_SLIP_TARGET_DEFAULT         0.10f   /* Default target slip */
#define ABS_RECOVERY_THRESHOLD          2.0f    /* Wheel acceleration recovery threshold (m/s²) */
#define ABS_PRESSURE_REDUCTION_RATE     0.8f    /* Pressure reduction factor */
#define ABS_PRESSURE_INCREASE_RATE      1.1f    /* Pressure increase factor */
#define ABS_MIN_VEHICLE_SPEED           5.0f    /* Minimum speed for ABS activation (km/h) */
#define ABS_MAX_CYCLE_FREQUENCY         20.0f   /* Maximum ABS cycle frequency (Hz) */
#define ABS_MIN_CYCLE_FREQUENCY         4.0f    /* Minimum ABS cycle frequency (Hz) */

/* ABS Calibration Structure */
typedef struct {
    float slip_threshold[WHEEL_COUNT];      /* Slip threshold per wheel */
    float slip_target[WHEEL_COUNT];         /* Target slip per wheel */
    float pressure_reduction_rate[WHEEL_COUNT]; /* Pressure reduction rate per wheel */
    float pressure_increase_rate[WHEEL_COUNT];  /* Pressure increase rate per wheel */
    float min_activation_speed;             /* Minimum speed for activation */
    bool enable_per_wheel[WHEEL_COUNT];     /* Enable flag per wheel */
} ebs_abs_calibration_t;

/* ABS Statistics Structure */
typedef struct {
    uint32_t activation_count;              /* Number of activations */
    uint32_t total_active_time_ms;          /* Total active time in ms */
    float max_slip_ratio;                   /* Maximum slip ratio recorded */
    float avg_cycle_frequency;              /* Average cycle frequency */
    uint32_t fault_count;                   /* Number of faults */
    uint32_t last_activation_time;          /* Timestamp of last activation */
} ebs_abs_statistics_t;

/* ABS Internal State Structure */
typedef struct {
    ebs_abs_state_t state;                  /* Current ABS state */
    ebs_abs_phase_t phase;                  /* Current ABS phase */
    float slip_ratio;                       /* Current slip ratio */
    float pressure_command;                 /* Current pressure command */
    uint32_t activation_time;               /* Activation timestamp */
    uint32_t phase_time;                    /* Phase timestamp */
    float previous_wheel_speed;             /* Previous wheel speed */
    float wheel_acceleration;               /* Calculated wheel acceleration */
    bool fault_detected;                    /* Fault flag */
} ebs_abs_wheel_state_t;

/* ABS System State Structure */
typedef struct {
    ebs_abs_wheel_state_t wheel_state[WHEEL_COUNT]; /* Per-wheel state */
    float vehicle_speed;                    /* Estimated vehicle speed */
    bool system_enabled;                    /* System enable flag */
    bool any_wheel_active;                  /* Any wheel ABS active */
    uint32_t system_activation_count;       /* Total system activations */
    ebs_abs_calibration_t calibration;     /* Calibration parameters */
    ebs_abs_statistics_t statistics[WHEEL_COUNT]; /* Per-wheel statistics */
} ebs_abs_system_state_t;

/* ABS Macros */
#define ABS_IS_WHEEL_VALID(wheel) ((wheel) < WHEEL_COUNT)
#define ABS_IS_SLIP_EXCESSIVE(slip) ((slip) > EBS_ABS_SLIP_THRESHOLD)
#define ABS_IS_SPEED_SUFFICIENT(speed) ((speed) > ABS_MIN_VEHICLE_SPEED)

/* ABS Function-like Macros */
#define ABS_CALCULATE_SLIP(wheel_speed, vehicle_speed) \
    (((vehicle_speed) > 1.0f) ? (((vehicle_speed) - (wheel_speed)) / (vehicle_speed)) : 0.0f)

#define ABS_LIMIT_PRESSURE_COMMAND(cmd) \
    EBS_CLAMP((cmd), 0.0f, 1.0f)

#define ABS_IS_WHEEL_LOCKED(slip) \
    ((slip) > 0.9f)

#define ABS_IS_WHEEL_RECOVERING(accel) \
    ((accel) > ABS_RECOVERY_THRESHOLD)

#endif /* EBS_ABS_H */
