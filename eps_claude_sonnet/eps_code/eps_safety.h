/**
 * @file eps_safety.h
 * @brief Electronic Power Steering (EPS) Safety Module Header
 * @version 1.0
 * @date 2025-07-29
 * 
 * This header file defines the safety-related functions and data structures
 * for the EPS system according to ISO 26262 functional safety requirements.
 * 
 * Requirements Traceability:
 * - EPS-SR-001 to EPS-SR-098: Safety Requirements
 * - ISO 26262 ASIL A-D compliance
 */

#ifndef EPS_SAFETY_H
#define EPS_SAFETY_H

#include "eps_main.h"

/* Safety Constants */
#define EPS_SAFETY_WATCHDOG_TIMEOUT_MS      100     /* ms - EPS-SR-041 */
#define EPS_SAFETY_FAULT_TOLERANCE_TIME_MS  100     /* ms - EPS-SR-050 */
#define EPS_SAFETY_MAX_FAULT_COUNT          10      /* Maximum faults before shutdown */
#define EPS_SAFETY_DIAGNOSTIC_COVERAGE      95      /* % - EPS-SR-048 */

/* Safety Mechanism Types */
typedef enum {
    EPS_SAFETY_MECH_WATCHDOG = 0,
    EPS_SAFETY_MECH_DUAL_CHANNEL,
    EPS_SAFETY_MECH_RANGE_CHECK,
    EPS_SAFETY_MECH_PLAUSIBILITY_CHECK,
    EPS_SAFETY_MECH_CROSS_CHECK,
    EPS_SAFETY_MECH_TIMEOUT_MONITOR,
    EPS_SAFETY_MECH_COUNT
} eps_safety_mechanism_t;

/* Safety Mechanism Status */
typedef struct {
    bool active;
    bool functional;
    uint32_t last_test_time;
    uint32_t fault_count;
    eps_result_t last_result;
} eps_safety_mechanism_status_t;

/* Safety Monitor Data */
typedef struct {
    eps_safety_mechanism_status_t mechanisms[EPS_SAFETY_MECH_COUNT];
    uint32_t total_fault_count;
    uint32_t last_safety_check_time;
    bool safety_state_valid;
    bool manual_steering_available;
} eps_safety_monitor_t;

/* Function Prototypes */

/**
 * @brief Initialize safety subsystem
 * @param safety_state Pointer to safety state structure
 * @return eps_result_t Initialization result
 * 
 * Requirements: EPS-SR-084
 */
eps_result_t eps_safety_init(eps_safety_state_t* safety_state);

/**
 * @brief Monitor system safety
 * @param safety_state Pointer to safety state structure
 * @return eps_result_t Monitoring result
 * 
 * Requirements: EPS-SR-047, EPS-DR-003
 */
eps_result_t eps_safety_monitor(eps_safety_state_t* safety_state);

/**
 * @brief Reset watchdog timer
 * 
 * Requirements: EPS-SR-041
 */
void eps_safety_reset_watchdog(void);

/**
 * @brief Perform safety self-test
 * @return eps_result_t Self-test result
 * 
 * Requirements: EPS-SR-047
 */
eps_result_t eps_safety_self_test(void);

/**
 * @brief Check dual-channel sensor data
 * @param channel1_data Primary channel data
 * @param channel2_data Secondary channel data
 * @param tolerance Acceptable tolerance between channels
 * @return eps_result_t Cross-check result
 * 
 * Requirements: EPS-SR-029, EPS-SR-031
 */
eps_result_t eps_safety_dual_channel_check(float channel1_data, 
                                          float channel2_data, 
                                          float tolerance);

/**
 * @brief Validate sensor range
 * @param sensor_value Sensor value to check
 * @param min_value Minimum valid value
 * @param max_value Maximum valid value
 * @return eps_result_t Range check result
 * 
 * Requirements: EPS-SR-044, EPS-SR-045
 */
eps_result_t eps_safety_range_check(float sensor_value, 
                                   float min_value, 
                                   float max_value);

/**
 * @brief Check plausibility of sensor data
 * @param current_value Current sensor value
 * @param previous_value Previous sensor value
 * @param max_rate Maximum allowed rate of change
 * @param delta_time Time difference in ms
 * @return eps_result_t Plausibility check result
 * 
 * Requirements: EPS-SR-042
 */
eps_result_t eps_safety_plausibility_check(float current_value,
                                          float previous_value,
                                          float max_rate,
                                          uint32_t delta_time);

/**
 * @brief Monitor timeout conditions
 * @param last_update_time Time of last update
 * @param current_time Current time
 * @param timeout_ms Timeout threshold in ms
 * @return eps_result_t Timeout check result
 * 
 * Requirements: EPS-SR-041
 */
eps_result_t eps_safety_timeout_check(uint32_t last_update_time,
                                     uint32_t current_time,
                                     uint32_t timeout_ms);

/**
 * @brief Transition to safe state
 * @param fault_code Fault code triggering safe state
 * @return eps_result_t Safe state transition result
 * 
 * Requirements: EPS-SR-050, EPS-SR-051
 */
eps_result_t eps_safety_enter_safe_state(eps_result_t fault_code);

/**
 * @brief Check if manual steering is available
 * @return bool True if manual steering is available
 * 
 * Requirements: EPS-SR-010, EPS-SR-051
 */
bool eps_safety_manual_steering_available(void);

/**
 * @brief Get safety mechanism status
 * @param mechanism Safety mechanism type
 * @return eps_safety_mechanism_status_t* Pointer to mechanism status
 */
const eps_safety_mechanism_status_t* eps_safety_get_mechanism_status(eps_safety_mechanism_t mechanism);

/**
 * @brief Calculate diagnostic coverage
 * @return float Diagnostic coverage percentage
 * 
 * Requirements: EPS-SR-048
 */
float eps_safety_get_diagnostic_coverage(void);

/**
 * @brief Test safety mechanism
 * @param mechanism Safety mechanism to test
 * @return eps_result_t Test result
 */
eps_result_t eps_safety_test_mechanism(eps_safety_mechanism_t mechanism);

#endif /* EPS_SAFETY_H */