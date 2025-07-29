/**
 * @file ebs_abs.c
 * @brief Electronic Braking System - Anti-lock Braking System Implementation
 * @version 1.0
 * @date 2025-07-29
 * @author EBS Development Team
 * 
 * ABS control algorithm implementation based on specifications
 * 
 * Safety Level: ASIL-D
 * Compliance: ISO 26262, UN-ECE R13-H, MISRA C:2012
 */

#include "ebs_abs.h"
#include "ebs_safety.h"
#include "ebs_sensors.h"
#include "ebs_actuators.h"
#include "ebs_diagnostics.h"
#include <math.h>
#include <string.h>

/* Static Variables */
static ebs_abs_system_state_t g_abs_system;
static bool g_abs_initialized = false;

/* Static Function Prototypes */
static ebs_result_t ABS_InitializeCalibration(void);
static ebs_result_t ABS_UpdateWheelState(ebs_wheel_position_t wheel);
static float ABS_CalculateWheelAcceleration(ebs_wheel_position_t wheel, float current_speed);
static ebs_result_t ABS_ExecuteStateMachine(ebs_wheel_position_t wheel);
static float ABS_CalculatePressureCommand(ebs_wheel_position_t wheel);
static bool ABS_ValidateInputs(void);
static void ABS_UpdateStatistics(ebs_wheel_position_t wheel);

/**
 * @brief Initialize ABS system
 * @return ebs_result_t Initialization result
 */
ebs_result_t EBS_ABS_Init(void)
{
    /* Clear system state */
    memset(&g_abs_system, 0, sizeof(g_abs_system));
    
    /* Initialize calibration parameters */
    if (ABS_InitializeCalibration() != EBS_OK) {
        EBS_Diagnostics_SetDTC(DTC_ALGORITHM_SELF_TEST_FAILED);
        return EBS_ERROR;
    }
    
    /* Initialize wheel states */
    for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
        g_abs_system.wheel_state[wheel].state = ABS_STATE_INACTIVE;
        g_abs_system.wheel_state[wheel].phase = ABS_PHASE_NORMAL;
        g_abs_system.wheel_state[wheel].slip_ratio = 0.0f;
        g_abs_system.wheel_state[wheel].pressure_command = 0.0f;
        g_abs_system.wheel_state[wheel].previous_wheel_speed = 0.0f;
        g_abs_system.wheel_state[wheel].wheel_acceleration = 0.0f;
        g_abs_system.wheel_state[wheel].fault_detected = false;
    }
    
    /* Initialize system parameters */
    g_abs_system.vehicle_speed = 0.0f;
    g_abs_system.system_enabled = true;
    g_abs_system.any_wheel_active = false;
    g_abs_system.system_activation_count = 0;
    
    g_abs_initialized = true;
    
    return EBS_OK;
}

/**
 * @brief Perform ABS self-test
 * @return bool True if self-test passed
 */
bool EBS_ABS_SelfTest(void)
{
    if (!g_abs_initialized) {
        return false;
    }
    
    /* Test calibration parameters */
    for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
        if (g_abs_system.calibration.slip_threshold[wheel] <= 0.0f ||
            g_abs_system.calibration.slip_threshold[wheel] > 1.0f) {
            return false;
        }
        
        if (g_abs_system.calibration.slip_target[wheel] <= 0.0f ||
            g_abs_system.calibration.slip_target[wheel] >= 
            g_abs_system.calibration.slip_threshold[wheel]) {
            return false;
        }
    }
    
    /* Test algorithm functions with known inputs */
    float test_slip = EBS_ABS_CalculateSlipRatio(40.0f, 50.0f);
    if (fabs(test_slip - 0.2f) > 0.001f) {
        return false;
    }
    
    float test_speeds[WHEEL_COUNT] = {50.0f, 50.0f, 50.0f, 50.0f};
    float test_vehicle_speed = EBS_ABS_CalculateVehicleSpeed(test_speeds);
    if (fabs(test_vehicle_speed - 50.0f) > 0.1f) {
        return false;
    }
    
    return true;
}

/**
 * @brief Main ABS control function (called every 1ms)
 * @return ebs_result_t Control result
 */
ebs_result_t EBS_ABS_Control(void)
{
    if (!g_abs_initialized || !g_abs_system.system_enabled) {
        return EBS_NOT_INITIALIZED;
    }
    
    /* Validate inputs */
    if (!ABS_ValidateInputs()) {
        EBS_Diagnostics_SetDTC(DTC_SENSOR_SELF_TEST_FAILED);
        return EBS_ERROR;
    }
    
    /* Get sensor data */
    ebs_wheel_speed_data_t* wheel_data = EBS_Sensors_GetWheelSpeedData();
    if (wheel_data == NULL) {
        return EBS_ERROR;
    }
    
    /* Calculate vehicle reference speed */
    float wheel_speeds[WHEEL_COUNT];
    for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
        wheel_speeds[wheel] = wheel_data->speed[wheel].value;
    }
    g_abs_system.vehicle_speed = EBS_ABS_CalculateVehicleSpeed(wheel_speeds);
    
    /* Reset system active flag */
    g_abs_system.any_wheel_active = false;
    
    /* Process each wheel */
    for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
        if (g_abs_system.calibration.enable_per_wheel[wheel]) {
            /* Update wheel state */
            if (ABS_UpdateWheelState((ebs_wheel_position_t)wheel) != EBS_OK) {
                continue;
            }
            
            /* Execute state machine */
            if (ABS_ExecuteStateMachine((ebs_wheel_position_t)wheel) != EBS_OK) {
                continue;
            }
            
            /* Update statistics */
            ABS_UpdateStatistics((ebs_wheel_position_t)wheel);
            
            /* Check if any wheel is active */
            if (g_abs_system.wheel_state[wheel].state == ABS_STATE_ACTIVE) {
                g_abs_system.any_wheel_active = true;
            }
        }
    }
    
    return EBS_OK;
}

/**
 * @brief Calculate wheel slip ratio
 * @param wheel_speed Wheel speed in km/h
 * @param vehicle_speed Vehicle speed in km/h
 * @return float Slip ratio (0.0 to 1.0)
 */
float EBS_ABS_CalculateSlipRatio(float wheel_speed, float vehicle_speed)
{
    /* Safety validation */
    if (vehicle_speed < 1.0f) {
        return 0.0f;  /* No slip at very low speeds */
    }
    
    if (wheel_speed < 0.0f || vehicle_speed < 0.0f) {
        return 0.0f;  /* Invalid speeds */
    }
    
    /* Calculate slip ratio: (Vvehicle - Vwheel) / Vvehicle */
    float slip_ratio = (vehicle_speed - wheel_speed) / vehicle_speed;
    
    /* Clamp to valid range [0.0, 1.0] */
    if (slip_ratio < 0.0f) {
        slip_ratio = 0.0f;
    } else if (slip_ratio > 1.0f) {
        slip_ratio = 1.0f;
    }
    
    return slip_ratio;
}

/**
 * @brief Calculate vehicle reference speed
 * @param wheel_speeds Array of wheel speeds
 * @return float Estimated vehicle speed in km/h
 */
float EBS_ABS_CalculateVehicleSpeed(const float* wheel_speeds)
{
    if (wheel_speeds == NULL) {
        return 0.0f;
    }
    
    /* Use the highest wheel speed as reference (non-braking wheel) */
    float max_speed = 0.0f;
    uint32_t valid_wheels = 0;
    float speed_sum = 0.0f;
    
    for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
        if (wheel_speeds[wheel] >= 0.0f && wheel_speeds[wheel] <= EBS_MAX_WHEEL_SPEED) {
            if (wheel_speeds[wheel] > max_speed) {
                max_speed = wheel_speeds[wheel];
            }
            speed_sum += wheel_speeds[wheel];
            valid_wheels++;
        }
    }
    
    /* If no valid wheels, return 0 */
    if (valid_wheels == 0) {
        return 0.0f;
    }
    
    /* Use average of highest speed and mean speed for better accuracy */
    float mean_speed = speed_sum / valid_wheels;
    float vehicle_speed = (max_speed + mean_speed) / 2.0f;
    
    /* Apply low-pass filter for smoothing */
    static float filtered_speed = 0.0f;
    const float filter_alpha = 0.1f;
    filtered_speed = filter_alpha * vehicle_speed + (1.0f - filter_alpha) * filtered_speed;
    
    return filtered_speed;
}

/**
 * @brief ABS pressure modulation control
 * @param wheel Wheel position
 * @param slip_ratio Current slip ratio
 * @param target_slip Target slip ratio
 * @return float Pressure command (0.0 to 1.0)
 */
float EBS_ABS_PressureModulation(ebs_wheel_position_t wheel, float slip_ratio, float target_slip)
{
    if (!ABS_IS_WHEEL_VALID(wheel)) {
        return 0.0f;
    }
    
    ebs_abs_wheel_state_t* wheel_state = &g_abs_system.wheel_state[wheel];
    ebs_abs_calibration_t* cal = &g_abs_system.calibration;
    
    float pressure_cmd = wheel_state->pressure_command;
    
    switch (wheel_state->phase) {
        case ABS_PHASE_PRESSURE_REDUCTION:
            /* Reduce pressure to decrease slip */
            pressure_cmd *= cal->pressure_reduction_rate[wheel];
            
            /* Check for wheel recovery */
            if (wheel_state->wheel_acceleration > ABS_RECOVERY_THRESHOLD) {
                wheel_state->phase = ABS_PHASE_PRESSURE_HOLD;
                wheel_state->phase_time = EBS_GetSystemTick();
            }
            break;
            
        case ABS_PHASE_PRESSURE_HOLD:
            /* Hold current pressure */
            /* Check if slip is acceptable */
            if (slip_ratio < target_slip) {
                wheel_state->phase = ABS_PHASE_PRESSURE_INCREASE;
                wheel_state->phase_time = EBS_GetSystemTick();
            } else if (slip_ratio > cal->slip_threshold[wheel]) {
                wheel_state->phase = ABS_PHASE_PRESSURE_REDUCTION;
                wheel_state->phase_time = EBS_GetSystemTick();
            }
            break;
            
        case ABS_PHASE_PRESSURE_INCREASE:
            /* Gradually increase pressure */
            pressure_cmd *= cal->pressure_increase_rate[wheel];
            
            /* Check for slip increase */
            if (slip_ratio > cal->slip_threshold[wheel]) {
                wheel_state->phase = ABS_PHASE_PRESSURE_REDUCTION;
                wheel_state->phase_time = EBS_GetSystemTick();
            }
            break;
            
        default:
            /* Normal braking - use master cylinder pressure */
            pressure_cmd = 1.0f;  /* Full pressure */
            break;
    }
    
    /* Limit pressure command */
    pressure_cmd = ABS_LIMIT_PRESSURE_COMMAND(pressure_cmd);
    
    return pressure_cmd;
}

/**
 * @brief Get ABS state for specific wheel
 * @param wheel Wheel position
 * @return ebs_abs_state_t ABS state
 */
ebs_abs_state_t EBS_ABS_GetState(ebs_wheel_position_t wheel)
{
    if (!ABS_IS_WHEEL_VALID(wheel) || !g_abs_initialized) {
        return ABS_STATE_FAULT;
    }
    
    return g_abs_system.wheel_state[wheel].state;
}

/**
 * @brief Check if ABS is active on any wheel
 * @return bool True if ABS is active
 */
bool EBS_ABS_IsActive(void)
{
    if (!g_abs_initialized) {
        return false;
    }
    
    return g_abs_system.any_wheel_active;
}

/**
 * @brief Get ABS activation count for wheel
 * @param wheel Wheel position
 * @return uint32_t Activation count
 */
uint32_t EBS_ABS_GetActivationCount(ebs_wheel_position_t wheel)
{
    if (!ABS_IS_WHEEL_VALID(wheel) || !g_abs_initialized) {
        return 0;
    }
    
    return g_abs_system.statistics[wheel].activation_count;
}

/* Static Function Implementations */

/**
 * @brief Initialize calibration parameters
 * @return ebs_result_t Initialization result
 */
static ebs_result_t ABS_InitializeCalibration(void)
{
    ebs_abs_calibration_t* cal = &g_abs_system.calibration;
    
    /* Set default calibration values */
    for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
        cal->slip_threshold[wheel] = ABS_SLIP_THRESHOLD_DEFAULT;
        cal->slip_target[wheel] = ABS_SLIP_TARGET_DEFAULT;
        cal->pressure_reduction_rate[wheel] = ABS_PRESSURE_REDUCTION_RATE;
        cal->pressure_increase_rate[wheel] = ABS_PRESSURE_INCREASE_RATE;
        cal->enable_per_wheel[wheel] = true;
    }
    
    cal->min_activation_speed = ABS_MIN_VEHICLE_SPEED;
    
    return EBS_OK;
}

/**
 * @brief Update wheel state with current sensor data
 * @param wheel Wheel position
 * @return ebs_result_t Update result
 */
static ebs_result_t ABS_UpdateWheelState(ebs_wheel_position_t wheel)
{
    if (!ABS_IS_WHEEL_VALID(wheel)) {
        return EBS_INVALID_PARAM;
    }
    
    ebs_abs_wheel_state_t* wheel_state = &g_abs_system.wheel_state[wheel];
    ebs_wheel_speed_data_t* wheel_data = EBS_Sensors_GetWheelSpeedData();
    
    if (wheel_data == NULL || !wheel_data->speed[wheel].valid) {
        wheel_state->fault_detected = true;
        return EBS_ERROR;
    }
    
    /* Get current wheel speed */
    float current_speed = wheel_data->speed[wheel].value;
    
    /* Calculate wheel acceleration */
    wheel_state->wheel_acceleration = ABS_CalculateWheelAcceleration(wheel, current_speed);
    
    /* Calculate slip ratio */
    wheel_state->slip_ratio = EBS_ABS_CalculateSlipRatio(current_speed, g_abs_system.vehicle_speed);
    
    /* Update previous speed for next cycle */
    wheel_state->previous_wheel_speed = current_speed;
    
    return EBS_OK;
}

/**
 * @brief Calculate wheel acceleration
 * @param wheel Wheel position
 * @param current_speed Current wheel speed
 * @return float Wheel acceleration in m/s²
 */
static float ABS_CalculateWheelAcceleration(ebs_wheel_position_t wheel, float current_speed)
{
    if (!ABS_IS_WHEEL_VALID(wheel)) {
        return 0.0f;
    }
    
    ebs_abs_wheel_state_t* wheel_state = &g_abs_system.wheel_state[wheel];
    
    /* Convert km/h to m/s and calculate acceleration */
    float current_speed_ms = current_speed / 3.6f;
    float previous_speed_ms = wheel_state->previous_wheel_speed / 3.6f;
    float dt = EBS_CYCLE_TIME_MS / 1000.0f;  /* Convert ms to seconds */
    
    if (dt <= 0.0f) {
        return 0.0f;
    }
    
    float acceleration = (current_speed_ms - previous_speed_ms) / dt;
    
    /* Apply low-pass filter to reduce noise */
    static float filtered_accel[WHEEL_COUNT] = {0.0f};
    const float filter_alpha = 0.2f;
    filtered_accel[wheel] = filter_alpha * acceleration + (1.0f - filter_alpha) * filtered_accel[wheel];
    
    return filtered_accel[wheel];
}

/**
 * @brief Execute ABS state machine for wheel
 * @param wheel Wheel position
 * @return ebs_result_t Execution result
 */
static ebs_result_t ABS_ExecuteStateMachine(ebs_wheel_position_t wheel)
{
    if (!ABS_IS_WHEEL_VALID(wheel)) {
        return EBS_INVALID_PARAM;
    }
    
    ebs_abs_wheel_state_t* wheel_state = &g_abs_system.wheel_state[wheel];
    ebs_abs_calibration_t* cal = &g_abs_system.calibration;
    
    ebs_abs_state_t previous_state = wheel_state->state;
    
    switch (wheel_state->state) {
        case ABS_STATE_INACTIVE:
            /* Check for activation conditions */
            if (g_abs_system.vehicle_speed > cal->min_activation_speed &&
                wheel_state->slip_ratio > cal->slip_threshold[wheel] &&
                !wheel_state->fault_detected) {
                
                wheel_state->state = ABS_STATE_ACTIVE;
                wheel_state->phase = ABS_PHASE_PRESSURE_REDUCTION;
                wheel_state->activation_time = EBS_GetSystemTick();
                wheel_state->phase_time = EBS_GetSystemTick();
                
                /* Log activation event */
                EBS_Diagnostics_LogEvent(DIAG_EVENT_ABS_ACTIVATION, wheel);
            }
            break;
            
        case ABS_STATE_MONITORING:
            /* Monitor for re-activation */
            if (wheel_state->slip_ratio > cal->slip_threshold[wheel]) {
                wheel_state->state = ABS_STATE_ACTIVE;
                wheel_state->phase = ABS_PHASE_PRESSURE_REDUCTION;
                wheel_state->phase_time = EBS_GetSystemTick();
            } else if (g_abs_system.vehicle_speed < cal->min_activation_speed) {
                wheel_state->state = ABS_STATE_INACTIVE;
            }
            break;
            
        case ABS_STATE_ACTIVE:
            /* Calculate pressure command */
            wheel_state->pressure_command = ABS_CalculatePressureCommand(wheel);
            
            /* Apply pressure command to actuator */
            EBS_Actuators_SetPressure(wheel, wheel_state->pressure_command);
            
            /* Check for deactivation conditions */
            if (wheel_state->slip_ratio < cal->slip_target[wheel] &&
                wheel_state->wheel_acceleration > -1.0f) {  /* Not decelerating rapidly */
                wheel_state->state = ABS_STATE_MONITORING;
                wheel_state->phase = ABS_PHASE_NORMAL;
            }
            
            /* Check for fault conditions */
            if (wheel_state->fault_detected) {
                wheel_state->state = ABS_STATE_FAULT;
            }
            break;
            
        case ABS_STATE_FAULT:
            /* Fault state - disable ABS for this wheel */
            wheel_state->pressure_command = 1.0f;  /* Full pressure (manual braking) */
            EBS_Actuators_SetPressure(wheel, wheel_state->pressure_command);
            
            /* Check if fault is cleared */
            if (!wheel_state->fault_detected) {
                wheel_state->state = ABS_STATE_INACTIVE;
            }
            break;
            
        default:
            /* Invalid state - go to fault */
            wheel_state->state = ABS_STATE_FAULT;
            break;
    }
    
    /* Update activation count on state transition */
    if (previous_state != ABS_STATE_ACTIVE && wheel_state->state == ABS_STATE_ACTIVE) {
        g_abs_system.statistics[wheel].activation_count++;
        g_abs_system.system_activation_count++;
    }
    
    return EBS_OK;
}

/**
 * @brief Calculate pressure command for wheel
 * @param wheel Wheel position
 * @return float Pressure command
 */
static float ABS_CalculatePressureCommand(ebs_wheel_position_t wheel)
{
    if (!ABS_IS_WHEEL_VALID(wheel)) {
        return 1.0f;  /* Full pressure as safe default */
    }
    
    ebs_abs_wheel_state_t* wheel_state = &g_abs_system.wheel_state[wheel];
    ebs_abs_calibration_t* cal = &g_abs_system.calibration;
    
    return EBS_ABS_PressureModulation(wheel, wheel_state->slip_ratio, cal->slip_target[wheel]);
}

/**
 * @brief Validate ABS inputs
 * @return bool True if inputs are valid
 */
static bool ABS_ValidateInputs(void)
{
    ebs_wheel_speed_data_t* wheel_data = EBS_Sensors_GetWheelSpeedData();
    if (wheel_data == NULL) {
        return false;
    }
    
    /* Check wheel speed data validity */
    for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
        if (!wheel_data->speed[wheel].valid) {
            g_abs_system.wheel_state[wheel].fault_detected = true;
        } else {
            /* Range check */
            float speed = wheel_data->speed[wheel].value;
            if (speed < 0.0f || speed > EBS_MAX_WHEEL_SPEED) {
                g_abs_system.wheel_state[wheel].fault_detected = true;
            } else {
                g_abs_system.wheel_state[wheel].fault_detected = false;
            }
        }
    }
    
    return true;
}

/**
 * @brief Update ABS statistics
 * @param wheel Wheel position
 */
static void ABS_UpdateStatistics(ebs_wheel_position_t wheel)
{
    if (!ABS_IS_WHEEL_VALID(wheel)) {
        return;
    }
    
    ebs_abs_statistics_t* stats = &g_abs_system.statistics[wheel];
    ebs_abs_wheel_state_t* wheel_state = &g_abs_system.wheel_state[wheel];
    
    /* Update maximum slip ratio */
    if (wheel_state->slip_ratio > stats->max_slip_ratio) {
        stats->max_slip_ratio = wheel_state->slip_ratio;
    }
    
    /* Update active time */
    if (wheel_state->state == ABS_STATE_ACTIVE) {
        stats->total_active_time_ms += EBS_CYCLE_TIME_MS;
        stats->last_activation_time = EBS_GetSystemTick();
    }
    
    /* Update fault count */
    if (wheel_state->fault_detected) {
        stats->fault_count++;
    }
}

/* External function implementations for missing functions */
uint32_t EBS_GetSystemTick(void)
{
    static uint32_t tick_counter = 0;
    return ++tick_counter;
}
