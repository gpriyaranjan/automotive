/**
 * @file eps_main.c
 * @brief Electronic Power Steering (EPS) System Main Implementation
 * @version 1.0
 * @date 2025-07-29
 * 
 * This file implements the main EPS system functionality according to the
 * requirements specified in the EPS System Requirements Document.
 * 
 * Requirements Traceability:
 * - EPS-FR-001 to EPS-FR-105: Functional Requirements
 * - EPS-SR-001 to EPS-SR-098: Safety Requirements
 * - EPS-PR-001 to EPS-PR-128: Performance Requirements
 */

#include "eps_main.h"
#include "eps_safety.h"
#include "eps_motor_control.h"
#include "eps_sensors.h"
#include "eps_communication.h"
#include "eps_diagnostics.h"
#include "eps_power_management.h"

/* Global system state */
static eps_system_state_t g_eps_system_state;
static eps_safety_state_t g_eps_safety_state;
static eps_performance_data_t g_eps_performance_data;

/* System timing */
static uint32_t g_system_tick_counter = 0;
static uint32_t g_last_watchdog_reset = 0;

/**
 * @brief Initialize the EPS system
 * @return eps_result_t System initialization result
 * 
 * Requirements: EPS-FR-033, EPS-SR-084, EPS-PR-014
 */
eps_result_t eps_system_init(void)
{
    eps_result_t result = EPS_SUCCESS;
    
    /* Initialize system state */
    memset(&g_eps_system_state, 0, sizeof(eps_system_state_t));
    memset(&g_eps_safety_state, 0, sizeof(eps_safety_state_t));
    memset(&g_eps_performance_data, 0, sizeof(eps_performance_data_t));
    
    g_eps_system_state.operating_mode = EPS_MODE_INIT;
    g_eps_system_state.system_status = EPS_STATUS_INITIALIZING;
    
    /* Initialize power management - EPS-ER-022 */
    result = eps_power_management_init();
    if (result != EPS_SUCCESS) {
        g_eps_system_state.system_status = EPS_STATUS_FAULT;
        return result;
    }
    
    /* Initialize safety subsystem - EPS-SR-084 */
    result = eps_safety_init(&g_eps_safety_state);
    if (result != EPS_SUCCESS) {
        g_eps_system_state.system_status = EPS_STATUS_FAULT;
        return result;
    }
    
    /* Initialize sensors - EPS-FR-007, EPS-IR-025 */
    result = eps_sensors_init();
    if (result != EPS_SUCCESS) {
        g_eps_system_state.system_status = EPS_STATUS_FAULT;
        return result;
    }
    
    /* Initialize motor control - EPS-FR-012, EPS-IR-050 */
    result = eps_motor_control_init();
    if (result != EPS_SUCCESS) {
        g_eps_system_state.system_status = EPS_STATUS_FAULT;
        return result;
    }
    
    /* Initialize communication - EPS-IR-001, EPS-IR-045 */
    result = eps_communication_init();
    if (result != EPS_SUCCESS) {
        g_eps_system_state.system_status = EPS_STATUS_FAULT;
        return result;
    }
    
    /* Initialize diagnostics - EPS-DR-001, EPS-DR-031 */
    result = eps_diagnostics_init();
    if (result != EPS_SUCCESS) {
        g_eps_system_state.system_status = EPS_STATUS_FAULT;
        return result;
    }
    
    /* Perform initial self-test - EPS-DR-002 */
    result = eps_system_self_test();
    if (result != EPS_SUCCESS) {
        g_eps_system_state.system_status = EPS_STATUS_FAULT;
        return result;
    }
    
    /* System initialization complete */
    g_eps_system_state.operating_mode = EPS_MODE_NORMAL;
    g_eps_system_state.system_status = EPS_STATUS_READY;
    g_system_tick_counter = 0;
    
    return EPS_SUCCESS;
}

/**
 * @brief Main EPS system task - called every 1ms
 * @return eps_result_t Task execution result
 * 
 * Requirements: EPS-FR-019, EPS-PR-014, EPS-SR-041
 */
eps_result_t eps_system_task(void)
{
    eps_result_t result = EPS_SUCCESS;
    eps_sensor_data_t sensor_data;
    eps_motor_command_t motor_command;
    eps_assistance_params_t assistance_params;
    
    /* Increment system tick counter */
    g_system_tick_counter++;
    
    /* Watchdog reset - EPS-SR-041 */
    if ((g_system_tick_counter - g_last_watchdog_reset) >= EPS_WATCHDOG_TIMEOUT_MS) {
        eps_safety_reset_watchdog();
        g_last_watchdog_reset = g_system_tick_counter;
    }
    
    /* Safety monitoring - EPS-SR-047, EPS-DR-003 */
    result = eps_safety_monitor(&g_eps_safety_state);
    if (result != EPS_SUCCESS) {
        return eps_handle_safety_fault(result);
    }
    
    /* Read sensor data - EPS-FR-007, EPS-IR-028 */
    result = eps_sensors_read_all(&sensor_data);
    if (result != EPS_SUCCESS) {
        return eps_handle_sensor_fault(result);
    }
    
    /* Validate sensor data - EPS-SR-019, EPS-DR-011 */
    result = eps_sensors_validate_data(&sensor_data);
    if (result != EPS_SUCCESS) {
        return eps_handle_sensor_fault(result);
    }
    
    /* Update performance data - EPS-PR-051 */
    eps_update_performance_data(&sensor_data);
    
    /* Calculate steering assistance - EPS-FR-002, EPS-FR-017 */
    result = eps_calculate_assistance(&sensor_data, &assistance_params);
    if (result != EPS_SUCCESS) {
        return eps_handle_calculation_fault(result);
    }
    
    /* Apply safety limits - EPS-SR-021, EPS-SR-005 */
    result = eps_apply_safety_limits(&assistance_params);
    if (result != EPS_SUCCESS) {
        return eps_handle_safety_fault(result);
    }
    
    /* Generate motor command - EPS-FR-012, EPS-IR-055 */
    result = eps_generate_motor_command(&assistance_params, &motor_command);
    if (result != EPS_SUCCESS) {
        return eps_handle_motor_fault(result);
    }
    
    /* Execute motor control - EPS-FR-013, EPS-PR-014 */
    result = eps_motor_control_execute(&motor_command);
    if (result != EPS_SUCCESS) {
        return eps_handle_motor_fault(result);
    }
    
    /* Update communication - EPS-IR-006, EPS-IR-007 */
    result = eps_communication_update(&sensor_data, &assistance_params);
    if (result != EPS_SUCCESS) {
        return eps_handle_communication_fault(result);
    }
    
    /* Update diagnostics - EPS-DR-089, EPS-DR-093 */
    result = eps_diagnostics_update(&sensor_data, &assistance_params);
    if (result != EPS_SUCCESS) {
        return eps_handle_diagnostic_fault(result);
    }
    
    return EPS_SUCCESS;
}

/**
 * @brief Calculate steering assistance based on inputs
 * @param sensor_data Pointer to sensor data structure
 * @param assistance_params Pointer to assistance parameters output
 * @return eps_result_t Calculation result
 * 
 * Requirements: EPS-FR-002, EPS-FR-017, EPS-PR-040
 */
static eps_result_t eps_calculate_assistance(const eps_sensor_data_t* sensor_data, 
                                           eps_assistance_params_t* assistance_params)
{
    if (!sensor_data || !assistance_params) {
        return EPS_ERROR_NULL_POINTER;
    }
    
    float base_assistance = 0.0f;
    float speed_factor = 1.0f;
    float return_to_center_torque = 0.0f;
    float damping_torque = 0.0f;
    
    /* Base assistance calculation - EPS-FR-002 */
    if (fabs(sensor_data->driver_torque) > EPS_MIN_TORQUE_THRESHOLD) {
        base_assistance = sensor_data->driver_torque * EPS_BASE_ASSISTANCE_GAIN;
        
        /* Apply torque direction check - EPS-FR-003, EPS-SR-018 */
        if ((sensor_data->driver_torque > 0 && base_assistance < 0) ||
            (sensor_data->driver_torque < 0 && base_assistance > 0)) {
            /* Direction mismatch detected - safety fault */
            eps_diagnostics_set_dtc(EPS_DTC_DIRECTION_MISMATCH);
            return EPS_ERROR_DIRECTION_MISMATCH;
        }
    }
    
    /* Speed-sensitive assistance - EPS-FR-017, EPS-PR-040 */
    if (sensor_data->vehicle_speed <= EPS_LOW_SPEED_THRESHOLD) {
        speed_factor = 1.0f; /* Maximum assistance at low speeds */
    } else if (sensor_data->vehicle_speed >= EPS_HIGH_SPEED_THRESHOLD) {
        speed_factor = EPS_MIN_ASSISTANCE_FACTOR; /* Minimum assistance at high speeds */
    } else {
        /* Linear interpolation between low and high speed thresholds */
        float speed_range = EPS_HIGH_SPEED_THRESHOLD - EPS_LOW_SPEED_THRESHOLD;
        float speed_offset = sensor_data->vehicle_speed - EPS_LOW_SPEED_THRESHOLD;
        speed_factor = 1.0f - (speed_offset / speed_range) * (1.0f - EPS_MIN_ASSISTANCE_FACTOR);
    }
    
    /* Return-to-center assistance - EPS-FR-023, EPS-PR-034 */
    if (fabs(sensor_data->driver_torque) < EPS_RETURN_TO_CENTER_THRESHOLD) {
        return_to_center_torque = -sensor_data->steering_angle * EPS_RETURN_TO_CENTER_GAIN;
        
        /* Speed-based return-to-center adjustment - EPS-FR-025 */
        return_to_center_torque *= (1.0f + sensor_data->vehicle_speed * EPS_SPEED_RTC_FACTOR);
    }
    
    /* Damping calculation - EPS-FR-029, EPS-PR-037 */
    damping_torque = -sensor_data->steering_velocity * EPS_DAMPING_COEFFICIENT;
    
    /* Speed-based damping adjustment - EPS-FR-031 */
    damping_torque *= (1.0f + sensor_data->vehicle_speed * EPS_SPEED_DAMPING_FACTOR);
    
    /* Combine all assistance components */
    assistance_params->base_assistance = base_assistance * speed_factor;
    assistance_params->return_to_center = return_to_center_torque;
    assistance_params->damping = damping_torque;
    assistance_params->total_assistance = assistance_params->base_assistance + 
                                        assistance_params->return_to_center + 
                                        assistance_params->damping;
    
    /* Store calculation metadata */
    assistance_params->speed_factor = speed_factor;
    assistance_params->calculation_timestamp = g_system_tick_counter;
    
    return EPS_SUCCESS;
}

/**
 * @brief Apply safety limits to assistance parameters
 * @param assistance_params Pointer to assistance parameters
 * @return eps_result_t Safety check result
 * 
 * Requirements: EPS-SR-021, EPS-SR-005, EPS-PR-004
 */
static eps_result_t eps_apply_safety_limits(eps_assistance_params_t* assistance_params)
{
    if (!assistance_params) {
        return EPS_ERROR_NULL_POINTER;
    }
    
    /* Check for excessive assistance - EPS-SR-021 */
    if (fabs(assistance_params->total_assistance) > EPS_MAX_ASSISTANCE_TORQUE) {
        eps_diagnostics_set_dtc(EPS_DTC_EXCESSIVE_ASSISTANCE);
        
        /* Limit assistance to maximum allowed - EPS-FR-004 */
        if (assistance_params->total_assistance > 0) {
            assistance_params->total_assistance = EPS_MAX_ASSISTANCE_TORQUE;
        } else {
            assistance_params->total_assistance = -EPS_MAX_ASSISTANCE_TORQUE;
        }
        
        assistance_params->safety_limited = true;
    }
    
    /* Check for oscillation detection - EPS-SR-006 */
    static float previous_assistance[EPS_OSCILLATION_BUFFER_SIZE] = {0};
    static uint8_t buffer_index = 0;
    
    previous_assistance[buffer_index] = assistance_params->total_assistance;
    buffer_index = (buffer_index + 1) % EPS_OSCILLATION_BUFFER_SIZE;
    
    if (eps_detect_oscillation(previous_assistance, EPS_OSCILLATION_BUFFER_SIZE)) {
        eps_diagnostics_set_dtc(EPS_DTC_OSCILLATION_DETECTED);
        assistance_params->total_assistance = 0.0f; /* Disable assistance */
        assistance_params->oscillation_detected = true;
        return EPS_ERROR_OSCILLATION_DETECTED;
    }
    
    /* Rate limiting - EPS-FR-005 */
    static float previous_assistance_value = 0.0f;
    float assistance_rate = assistance_params->total_assistance - previous_assistance_value;
    
    if (fabs(assistance_rate) > EPS_MAX_ASSISTANCE_RATE) {
        if (assistance_rate > 0) {
            assistance_params->total_assistance = previous_assistance_value + EPS_MAX_ASSISTANCE_RATE;
        } else {
            assistance_params->total_assistance = previous_assistance_value - EPS_MAX_ASSISTANCE_RATE;
        }
        assistance_params->rate_limited = true;
    }
    
    previous_assistance_value = assistance_params->total_assistance;
    
    return EPS_SUCCESS;
}

/**
 * @brief Update system performance data
 * @param sensor_data Pointer to current sensor data
 * 
 * Requirements: EPS-PR-051, EPS-DR-093
 */
static void eps_update_performance_data(const eps_sensor_data_t* sensor_data)
{
    if (!sensor_data) {
        return;
    }
    
    /* Update response time measurement - EPS-PR-014 */
    static uint32_t last_torque_change_time = 0;
    static float last_driver_torque = 0.0f;
    
    if (fabs(sensor_data->driver_torque - last_driver_torque) > EPS_TORQUE_CHANGE_THRESHOLD) {
        if (last_torque_change_time > 0) {
            uint32_t response_time = g_system_tick_counter - last_torque_change_time;
            g_eps_performance_data.last_response_time_ms = response_time;
            
            /* Update response time statistics */
            if (response_time > g_eps_performance_data.max_response_time_ms) {
                g_eps_performance_data.max_response_time_ms = response_time;
            }
            
            /* Check response time requirement - EPS-PR-014 */
            if (response_time > EPS_MAX_RESPONSE_TIME_MS) {
                eps_diagnostics_set_dtc(EPS_DTC_SLOW_RESPONSE);
            }
        }
        last_torque_change_time = g_system_tick_counter;
        last_driver_torque = sensor_data->driver_torque;
    }
    
    /* Update power consumption data - EPS-PR-055 */
    g_eps_performance_data.current_power_consumption = eps_power_get_consumption();
    
    /* Update temperature data - EPS-EDR-087 */
    g_eps_performance_data.ecu_temperature = sensor_data->ecu_temperature;
    g_eps_performance_data.motor_temperature = sensor_data->motor_temperature;
    
    /* Update system uptime */
    g_eps_performance_data.system_uptime_ms = g_system_tick_counter;
}

/**
 * @brief Handle safety fault conditions
 * @param fault_code Fault code indicating the type of safety fault
 * @return eps_result_t Fault handling result
 * 
 * Requirements: EPS-SR-050, EPS-SR-051, EPS-SR-052
 */
static eps_result_t eps_handle_safety_fault(eps_result_t fault_code)
{
    /* Determine fault severity and required response */
    eps_fault_severity_t severity = eps_get_fault_severity(fault_code);
    
    switch (severity) {
        case EPS_FAULT_CRITICAL:
            /* Critical fault - immediate safe state - EPS-SR-050 */
            g_eps_system_state.operating_mode = EPS_MODE_FAIL_SAFE;
            eps_motor_control_disable();
            eps_diagnostics_set_dtc(eps_get_dtc_for_fault(fault_code));
            break;
            
        case EPS_FAULT_MAJOR:
            /* Major fault - degraded operation - EPS-SR-036 */
            g_eps_system_state.operating_mode = EPS_MODE_DEGRADED;
            eps_motor_control_limit_torque(EPS_DEGRADED_MAX_TORQUE);
            eps_diagnostics_set_dtc(eps_get_dtc_for_fault(fault_code));
            break;
            
        case EPS_FAULT_MINOR:
            /* Minor fault - continue with monitoring */
            eps_diagnostics_set_dtc(eps_get_dtc_for_fault(fault_code));
            break;
            
        default:
            break;
    }
    
    /* Update safety state */
    g_eps_safety_state.last_fault_code = fault_code;
    g_eps_safety_state.fault_count++;
    g_eps_safety_state.last_fault_time = g_system_tick_counter;
    
    return fault_code;
}

/**
 * @brief Perform system self-test
 * @return eps_result_t Self-test result
 * 
 * Requirements: EPS-DR-002, EPS-SR-047
 */
static eps_result_t eps_system_self_test(void)
{
    eps_result_t result = EPS_SUCCESS;
    
    /* Test sensor functionality */
    result = eps_sensors_self_test();
    if (result != EPS_SUCCESS) {
        return result;
    }
    
    /* Test motor control functionality */
    result = eps_motor_control_self_test();
    if (result != EPS_SUCCESS) {
        return result;
    }
    
    /* Test communication functionality */
    result = eps_communication_self_test();
    if (result != EPS_SUCCESS) {
        return result;
    }
    
    /* Test safety mechanisms */
    result = eps_safety_self_test();
    if (result != EPS_SUCCESS) {
        return result;
    }
    
    /* Test diagnostic functionality */
    result = eps_diagnostics_self_test();
    if (result != EPS_SUCCESS) {
        return result;
    }
    
    return EPS_SUCCESS;
}

/**
 * @brief Get current system state
 * @return eps_system_state_t* Pointer to current system state
 */
const eps_system_state_t* eps_get_system_state(void)
{
    return &g_eps_system_state;
}

/**
 * @brief Get current performance data
 * @return eps_performance_data_t* Pointer to current performance data
 */
const eps_performance_data_t* eps_get_performance_data(void)
{
    return &g_eps_performance_data;
}

/**
 * @brief System shutdown procedure
 * @return eps_result_t Shutdown result
 * 
 * Requirements: EPS-FR-042, EPS-ER-043
 */
eps_result_t eps_system_shutdown(void)
{
    /* Disable motor control */
    eps_motor_control_disable();
    
    /* Save diagnostic data */
    eps_diagnostics_save_data();
    
    /* Enter sleep mode */
    g_eps_system_state.operating_mode = EPS_MODE_SLEEP;
    g_eps_system_state.system_status = EPS_STATUS_SLEEP;
    
    /* Power down non-essential systems */
    eps_power_management_sleep();
    
    return EPS_SUCCESS;
}