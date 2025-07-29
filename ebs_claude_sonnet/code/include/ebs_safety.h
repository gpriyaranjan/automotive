/**
 * @file ebs_safety.h
 * @brief Electronic Braking System - Safety Management Module
 * @version 1.0
 * @date 2025-07-29
 * @author EBS Development Team
 * 
 * Safety management and monitoring functions for ASIL-D compliance
 * 
 * Safety Level: ASIL-D
 * Compliance: ISO 26262, MISRA C:2012
 */

#ifndef EBS_SAFETY_H
#define EBS_SAFETY_H

#include "ebs_types.h"
#include "ebs_config.h"

/* Safety Function Prototypes */

/**
 * @brief Initialize safety management system
 * @return ebs_result_t Initialization result
 */
ebs_result_t EBS_Safety_Init(void);

/**
 * @brief Perform safety self-test
 * @return bool True if self-test passed, false otherwise
 */
bool EBS_Safety_SelfTest(void);

/**
 * @brief Get current safety state
 * @return ebs_safety_state_t Current safety state
 */
ebs_safety_state_t EBS_Safety_GetState(void);

/**
 * @brief Enter safe state with specified fault
 * @param fault Safety fault that triggered safe state
 * @return ebs_result_t Operation result
 */
ebs_result_t EBS_Safety_EnterSafeState(ebs_safety_fault_t fault);

/**
 * @brief Monitor system health
 * @return ebs_result_t Monitoring result
 */
ebs_result_t EBS_Safety_MonitorSystemHealth(void);

/**
 * @brief Check if critical fault is present
 * @return bool True if critical fault detected
 */
bool EBS_Safety_HasCriticalFault(void);

/**
 * @brief Emergency stop function (called from interrupt)
 * @return void
 */
void EBS_Safety_EmergencyStop(void);

/**
 * @brief Validate sensor data
 * @param sensor_data Pointer to sensor data structure
 * @return bool True if data is valid, false otherwise
 */
bool EBS_Safety_ValidateSensorData(const ebs_sensor_data_t* sensor_data);

/**
 * @brief Perform dual-channel comparison
 * @param channel_a Channel A data
 * @param channel_b Channel B data
 * @param tolerance Comparison tolerance
 * @return bool True if channels agree within tolerance
 */
bool EBS_Safety_DualChannelCompare(float channel_a, float channel_b, float tolerance);

/**
 * @brief Calculate CRC for data integrity
 * @param data Pointer to data buffer
 * @param length Data length in bytes
 * @return uint32_t Calculated CRC value
 */
uint32_t EBS_Safety_CalculateCRC(const uint8_t* data, uint32_t length);

/**
 * @brief Verify CRC for data integrity
 * @param data Pointer to data buffer
 * @param length Data length in bytes
 * @param expected_crc Expected CRC value
 * @return bool True if CRC matches
 */
bool EBS_Safety_VerifyCRC(const uint8_t* data, uint32_t length, uint32_t expected_crc);

/**
 * @brief Memory protection check
 * @return bool True if memory is intact
 */
bool EBS_Safety_MemoryProtectionCheck(void);

/**
 * @brief Range validation for sensor values
 * @param value Sensor value to validate
 * @param min_value Minimum valid value
 * @param max_value Maximum valid value
 * @return bool True if value is within range
 */
bool EBS_Safety_RangeCheck(float value, float min_value, float max_value);

/**
 * @brief Plausibility check for sensor values
 * @param current_value Current sensor value
 * @param previous_value Previous sensor value
 * @param max_rate Maximum rate of change
 * @param delta_time Time difference in ms
 * @return bool True if rate of change is plausible
 */
bool EBS_Safety_PlausibilityCheck(float current_value, float previous_value, 
                                  float max_rate, uint32_t delta_time);

/**
 * @brief Cross-channel validation
 * @param primary_value Primary channel value
 * @param secondary_value Secondary channel value
 * @param tolerance Acceptable difference
 * @return bool True if channels are consistent
 */
bool EBS_Safety_CrossChannelValidation(float primary_value, float secondary_value, 
                                       float tolerance);

/**
 * @brief Temporal validation (stuck sensor detection)
 * @param value Current sensor value
 * @param previous_values Array of previous values
 * @param count Number of previous values
 * @param resolution Sensor resolution
 * @return bool True if sensor is not stuck
 */
bool EBS_Safety_TemporalValidation(float value, const float* previous_values, 
                                   uint32_t count, float resolution);

/**
 * @brief Safety state machine update
 * @return ebs_result_t Update result
 */
ebs_result_t EBS_Safety_StateMachineUpdate(void);

/**
 * @brief Get safety fault history
 * @param fault_buffer Buffer to store fault history
 * @param buffer_size Size of fault buffer
 * @return uint32_t Number of faults returned
 */
uint32_t EBS_Safety_GetFaultHistory(ebs_safety_fault_t* fault_buffer, uint32_t buffer_size);

/**
 * @brief Clear safety fault
 * @param fault Fault to clear
 * @return ebs_result_t Clear result
 */
ebs_result_t EBS_Safety_ClearFault(ebs_safety_fault_t fault);

/**
 * @brief Get safety statistics
 * @param stats Pointer to statistics structure
 * @return ebs_result_t Operation result
 */
ebs_result_t EBS_Safety_GetStatistics(void* stats);

/* Safety Constants */
#define SAFETY_CRC_POLYNOMIAL       0x04C11DB7U  /* CRC-32 polynomial */
#define SAFETY_DUAL_CHANNEL_TOL     0.05f        /* 5% tolerance for dual-channel */
#define SAFETY_SENSOR_TIMEOUT_MS    100U         /* Sensor data timeout */
#define SAFETY_MAX_FAULT_COUNT      3U           /* Maximum faults before safe state */
#define SAFETY_MEMORY_PATTERN       0xA5A5A5A5U  /* Memory test pattern */

/* Safety Macros */
#define SAFETY_ASSERT(expr) \
    do { \
        if (!(expr)) { \
            EBS_Safety_EnterSafeState(SAFETY_FAULT_CRITICAL); \
        } \
    } while(0)

#define SAFETY_VALIDATE_POINTER(ptr) \
    do { \
        if ((ptr) == NULL) { \
            EBS_Safety_EnterSafeState(SAFETY_FAULT_CRITICAL); \
            return EBS_INVALID_PARAM; \
        } \
    } while(0)

#define SAFETY_VALIDATE_RANGE(val, min, max) \
    do { \
        if (!EBS_Safety_RangeCheck((val), (min), (max))) { \
            EBS_Safety_EnterSafeState(SAFETY_FAULT_SENSOR_FAILURE); \
            return EBS_ERROR; \
        } \
    } while(0)

#endif /* EBS_SAFETY_H */
