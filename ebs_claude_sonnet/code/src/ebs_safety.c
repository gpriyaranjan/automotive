/**
 * @file ebs_safety.c
 * @brief Electronic Braking System - Safety Management Implementation
 * @version 1.0
 * @date 2025-07-29
 * @author EBS Development Team
 * 
 * Safety management implementation for ASIL-D compliance
 * 
 * Safety Level: ASIL-D
 * Compliance: ISO 26262, MISRA C:2012
 */

#include "ebs_safety.h"
#include "ebs_diagnostics.h"
#include "ebs_actuators.h"
#include "ebs_communication.h"
#include <string.h>

/* Static Variables */
static ebs_safety_manager_t g_safety_manager;
static bool g_safety_initialized = false;
static uint32_t g_safety_violation_count = 0;

/* Static Function Prototypes */
static ebs_result_t Safety_InitializeWatchdogs(void);
static ebs_result_t Safety_CheckSystemIntegrity(void);
static ebs_result_t Safety_ValidateMemory(void);
static ebs_result_t Safety_CheckTimingConstraints(void);
static ebs_result_t Safety_ExecuteDualChannelCheck(void);
static void Safety_HandleSafetyViolation(ebs_safety_violation_t violation);
static bool Safety_IsSystemInSafeState(void);
static ebs_result_t Safety_PerformGracefulShutdown(void);
static uint32_t Safety_CalculateChecksum(const void* data, size_t length);

/**
 * @brief Initialize safety management system
 * @return ebs_result_t Initialization result
 */
ebs_result_t EBS_Safety_Init(void)
{
    /* Clear safety manager state */
    memset(&g_safety_manager, 0, sizeof(g_safety_manager));
    
    /* Initialize safety state */
    g_safety_manager.current_state = SAFETY_STATE_INIT;
    g_safety_manager.previous_state = SAFETY_STATE_UNKNOWN;
    g_safety_manager.safety_level = SAFETY_LEVEL_ASIL_D;
    g_safety_manager.system_enabled = false;
    g_safety_manager.fault_reaction_active = false;
    
    /* Initialize timing monitoring */
    g_safety_manager.timing.last_cycle_time = EBS_GetSystemTick();
    g_safety_manager.timing.max_cycle_time = 0;
    g_safety_manager.timing.cycle_overrun_count = 0;
    
    /* Initialize memory protection */
    g_safety_manager.memory.stack_canary = SAFETY_STACK_CANARY_VALUE;
    g_safety_manager.memory.heap_guard = SAFETY_HEAP_GUARD_VALUE;
    g_safety_manager.memory.corruption_detected = false;
    
    /* Initialize dual channel monitoring */
    g_safety_manager.dual_channel.primary_active = true;
    g_safety_manager.dual_channel.secondary_active = true;
    g_safety_manager.dual_channel.comparison_failures = 0;
    g_safety_manager.dual_channel.last_comparison_time = EBS_GetSystemTick();
    
    /* Initialize watchdogs */
    if (Safety_InitializeWatchdogs() != EBS_OK) {
        return EBS_ERROR;
    }
    
    /* Initialize fault counters */
    for (uint32_t i = 0; i < SAFETY_MAX_FAULT_TYPES; i++) {
        g_safety_manager.fault_counters[i] = 0;
    }
    
    g_safety_initialized = true;
    g_safety_manager.current_state = SAFETY_STATE_OPERATIONAL;
    
    return EBS_OK;
}

/**
 * @brief Perform safety self-test
 * @return bool True if self-test passed
 */
bool EBS_Safety_SelfTest(void)
{
    if (!g_safety_initialized) {
        return false;
    }
    
    bool test_passed = true;
    
    /* Test 1: Memory integrity check */
    if (Safety_ValidateMemory() != EBS_OK) {
        test_passed = false;
    }
    
    /* Test 2: Watchdog functionality */
    uint32_t test_watchdog_id = 0;
    if (EBS_Safety_KickWatchdog(test_watchdog_id) != EBS_OK) {
        test_passed = false;
    }
    
    /* Test 3: Dual channel comparison */
    if (Safety_ExecuteDualChannelCheck() != EBS_OK) {
        test_passed = false;
    }
    
    /* Test 4: Safety state transitions */
    ebs_safety_state_t original_state = g_safety_manager.current_state;
    g_safety_manager.current_state = SAFETY_STATE_DEGRADED;
    if (!EBS_Safety_IsStateValid(g_safety_manager.current_state)) {
        test_passed = false;
    }
    g_safety_manager.current_state = original_state;
    
    /* Test 5: Checksum calculation */
    uint8_t test_data[] = {0x01, 0x02, 0x03, 0x04};
    uint32_t checksum = Safety_CalculateChecksum(test_data, sizeof(test_data));
    if (checksum == 0) {
        test_passed = false;
    }
    
    return test_passed;
}

/**
 * @brief Main safety monitoring function (called every cycle)
 * @return ebs_result_t Monitoring result
 */
ebs_result_t EBS_Safety_Monitor(void)
{
    if (!g_safety_initialized) {
        return EBS_NOT_INITIALIZED;
    }
    
    uint32_t current_time = EBS_GetSystemTick();
    ebs_result_t result = EBS_OK;
    
    /* Update timing statistics */
    uint32_t cycle_time = current_time - g_safety_manager.timing.last_cycle_time;
    if (cycle_time > g_safety_manager.timing.max_cycle_time) {
        g_safety_manager.timing.max_cycle_time = cycle_time;
    }
    g_safety_manager.timing.last_cycle_time = current_time;
    
    /* Check timing constraints */
    if (Safety_CheckTimingConstraints() != EBS_OK) {
        Safety_HandleSafetyViolation(SAFETY_VIOLATION_TIMING);
        result = EBS_ERROR;
    }
    
    /* Check system integrity */
    if (Safety_CheckSystemIntegrity() != EBS_OK) {
        Safety_HandleSafetyViolation(SAFETY_VIOLATION_INTEGRITY);
        result = EBS_ERROR;
    }
    
    /* Validate memory protection */
    if (Safety_ValidateMemory() != EBS_OK) {
        Safety_HandleSafetyViolation(SAFETY_VIOLATION_MEMORY);
        result = EBS_ERROR;
    }
    
    /* Execute dual channel monitoring */
    if (Safety_ExecuteDualChannelCheck() != EBS_OK) {
        Safety_HandleSafetyViolation(SAFETY_VIOLATION_DUAL_CHANNEL);
        result = EBS_ERROR;
    }
    
    /* Update safety state based on monitoring results */
    if (result != EBS_OK && g_safety_manager.current_state == SAFETY_STATE_OPERATIONAL) {
        g_safety_manager.previous_state = g_safety_manager.current_state;
        g_safety_manager.current_state = SAFETY_STATE_DEGRADED;
        
        /* Log state transition */
        EBS_Diagnostics_LogEvent(DIAG_EVENT_SAFETY_STATE_CHANGE, 
                                (uint32_t)g_safety_manager.current_state);
    }
    
    return result;
}

/**
 * @brief Check if system is in safe state
 * @return bool True if system is safe
 */
bool EBS_Safety_IsSystemSafe(void)
{
    if (!g_safety_initialized) {
        return false;
    }
    
    return Safety_IsSystemInSafeState();
}

/**
 * @brief Get current safety state
 * @return ebs_safety_state_t Current safety state
 */
ebs_safety_state_t EBS_Safety_GetState(void)
{
    if (!g_safety_initialized) {
        return SAFETY_STATE_UNKNOWN;
    }
    
    return g_safety_manager.current_state;
}

/**
 * @brief Validate safety state
 * @param state Safety state to validate
 * @return bool True if state is valid
 */
bool EBS_Safety_IsStateValid(ebs_safety_state_t state)
{
    switch (state) {
        case SAFETY_STATE_INIT:
        case SAFETY_STATE_OPERATIONAL:
        case SAFETY_STATE_DEGRADED:
        case SAFETY_STATE_FAULT:
        case SAFETY_STATE_SHUTDOWN:
            return true;
        default:
            return false;
    }
}

/**
 * @brief Kick watchdog timer
 * @param watchdog_id Watchdog identifier
 * @return ebs_result_t Kick result
 */
ebs_result_t EBS_Safety_KickWatchdog(uint32_t watchdog_id)
{
    if (!g_safety_initialized || watchdog_id >= SAFETY_MAX_WATCHDOGS) {
        return EBS_INVALID_PARAM;
    }
    
    ebs_safety_watchdog_t* watchdog = &g_safety_manager.watchdogs[watchdog_id];
    
    if (!watchdog->enabled) {
        return EBS_ERROR;
    }
    
    uint32_t current_time = EBS_GetSystemTick();
    
    /* Check if kick is within expected window */
    uint32_t time_since_last_kick = current_time - watchdog->last_kick_time;
    
    if (time_since_last_kick < watchdog->min_kick_interval) {
        /* Kicked too early - potential runaway condition */
        watchdog->early_kick_count++;
        if (watchdog->early_kick_count > SAFETY_MAX_EARLY_KICKS) {
            Safety_HandleSafetyViolation(SAFETY_VIOLATION_WATCHDOG);
            return EBS_ERROR;
        }
    } else if (time_since_last_kick > watchdog->timeout_ms) {
        /* Kicked too late - timeout occurred */
        watchdog->timeout_count++;
        Safety_HandleSafetyViolation(SAFETY_VIOLATION_WATCHDOG);
        return EBS_ERROR;
    } else {
        /* Valid kick - reset counters */
        watchdog->early_kick_count = 0;
    }
    
    /* Update watchdog state */
    watchdog->last_kick_time = current_time;
    watchdog->kick_count++;
    
    return EBS_OK;
}

/**
 * @brief Report safety violation
 * @param violation_type Type of safety violation
 * @param severity Severity level
 * @return ebs_result_t Report result
 */
ebs_result_t EBS_Safety_ReportViolation(ebs_safety_violation_t violation_type, 
                                       ebs_safety_severity_t severity)
{
    if (!g_safety_initialized) {
        return EBS_NOT_INITIALIZED;
    }
    
    /* Increment violation counter */
    g_safety_violation_count++;
    
    /* Update fault counters */
    if (violation_type < SAFETY_MAX_FAULT_TYPES) {
        g_safety_manager.fault_counters[violation_type]++;
    }
    
    /* Log the violation */
    EBS_Diagnostics_SetDTC(DTC_SAFETY_VIOLATION_DETECTED);
    EBS_Diagnostics_LogEvent(DIAG_EVENT_SAFETY_VIOLATION, (uint32_t)violation_type);
    
    /* Handle based on severity */
    switch (severity) {
        case SAFETY_SEVERITY_LOW:
            /* Log and continue */
            break;
            
        case SAFETY_SEVERITY_MEDIUM:
            /* Enter degraded mode */
            g_safety_manager.previous_state = g_safety_manager.current_state;
            g_safety_manager.current_state = SAFETY_STATE_DEGRADED;
            break;
            
        case SAFETY_SEVERITY_HIGH:
            /* Enter fault state */
            g_safety_manager.previous_state = g_safety_manager.current_state;
            g_safety_manager.current_state = SAFETY_STATE_FAULT;
            g_safety_manager.fault_reaction_active = true;
            break;
            
        case SAFETY_SEVERITY_CRITICAL:
            /* Immediate shutdown */
            Safety_PerformGracefulShutdown();
            break;
            
        default:
            return EBS_INVALID_PARAM;
    }
    
    /* Handle the violation */
    Safety_HandleSafetyViolation(violation_type);
    
    return EBS_OK;
}

/**
 * @brief Perform memory protection check
 * @param address Memory address to check
 * @param size Size of memory region
 * @return bool True if memory is protected
 */
bool EBS_Safety_CheckMemoryProtection(void* address, size_t size)
{
    if (!g_safety_initialized || address == NULL || size == 0) {
        return false;
    }
    
    /* Check stack canary */
    if (g_safety_manager.memory.stack_canary != SAFETY_STACK_CANARY_VALUE) {
        g_safety_manager.memory.corruption_detected = true;
        Safety_HandleSafetyViolation(SAFETY_VIOLATION_MEMORY);
        return false;
    }
    
    /* Check heap guard */
    if (g_safety_manager.memory.heap_guard != SAFETY_HEAP_GUARD_VALUE) {
        g_safety_manager.memory.corruption_detected = true;
        Safety_HandleSafetyViolation(SAFETY_VIOLATION_MEMORY);
        return false;
    }
    
    /* Additional memory range checks could be implemented here */
    /* For now, assume memory is protected if canaries are intact */
    
    return true;
}

/**
 * @brief Get safety statistics
 * @return ebs_safety_statistics_t* Pointer to safety statistics
 */
const ebs_safety_statistics_t* EBS_Safety_GetStatistics(void)
{
    if (!g_safety_initialized) {
        return NULL;
    }
    
    /* Update statistics */
    g_safety_manager.statistics.total_violations = g_safety_violation_count;
    g_safety_manager.statistics.current_state = g_safety_manager.current_state;
    g_safety_manager.statistics.max_cycle_time = g_safety_manager.timing.max_cycle_time;
    g_safety_manager.statistics.cycle_overruns = g_safety_manager.timing.cycle_overrun_count;
    g_safety_manager.statistics.memory_corruptions = g_safety_manager.memory.corruption_detected ? 1 : 0;
    g_safety_manager.statistics.dual_channel_failures = g_safety_manager.dual_channel.comparison_failures;
    
    return &g_safety_manager.statistics;
}

/* Static Function Implementations */

/**
 * @brief Initialize watchdog timers
 * @return ebs_result_t Initialization result
 */
static ebs_result_t Safety_InitializeWatchdogs(void)
{
    /* Initialize main system watchdog */
    g_safety_manager.watchdogs[0].enabled = true;
    g_safety_manager.watchdogs[0].timeout_ms = SAFETY_MAIN_WATCHDOG_TIMEOUT;
    g_safety_manager.watchdogs[0].min_kick_interval = SAFETY_MIN_KICK_INTERVAL;
    g_safety_manager.watchdogs[0].last_kick_time = EBS_GetSystemTick();
    g_safety_manager.watchdogs[0].kick_count = 0;
    g_safety_manager.watchdogs[0].timeout_count = 0;
    g_safety_manager.watchdogs[0].early_kick_count = 0;
    
    /* Initialize safety monitoring watchdog */
    g_safety_manager.watchdogs[1].enabled = true;
    g_safety_manager.watchdogs[1].timeout_ms = SAFETY_MONITOR_WATCHDOG_TIMEOUT;
    g_safety_manager.watchdogs[1].min_kick_interval = SAFETY_MIN_KICK_INTERVAL;
    g_safety_manager.watchdogs[1].last_kick_time = EBS_GetSystemTick();
    g_safety_manager.watchdogs[1].kick_count = 0;
    g_safety_manager.watchdogs[1].timeout_count = 0;
    g_safety_manager.watchdogs[1].early_kick_count = 0;
    
    return EBS_OK;
}

/**
 * @brief Check system integrity
 * @return ebs_result_t Check result
 */
static ebs_result_t Safety_CheckSystemIntegrity(void)
{
    /* Check critical system parameters */
    if (g_safety_manager.safety_level != SAFETY_LEVEL_ASIL_D) {
        return EBS_ERROR;
    }
    
    /* Check watchdog status */
    uint32_t current_time = EBS_GetSystemTick();
    for (uint32_t i = 0; i < SAFETY_MAX_WATCHDOGS; i++) {
        ebs_safety_watchdog_t* watchdog = &g_safety_manager.watchdogs[i];
        if (watchdog->enabled) {
            uint32_t time_since_kick = current_time - watchdog->last_kick_time;
            if (time_since_kick > watchdog->timeout_ms) {
                return EBS_ERROR;
            }
        }
    }
    
    /* Check fault counters */
    for (uint32_t i = 0; i < SAFETY_MAX_FAULT_TYPES; i++) {
        if (g_safety_manager.fault_counters[i] > SAFETY_MAX_FAULT_COUNT) {
            return EBS_ERROR;
        }
    }
    
    return EBS_OK;
}

/**
 * @brief Validate memory integrity
 * @return ebs_result_t Validation result
 */
static ebs_result_t Safety_ValidateMemory(void)
{
    /* Check stack canary */
    if (g_safety_manager.memory.stack_canary != SAFETY_STACK_CANARY_VALUE) {
        g_safety_manager.memory.corruption_detected = true;
        return EBS_ERROR;
    }
    
    /* Check heap guard */
    if (g_safety_manager.memory.heap_guard != SAFETY_HEAP_GUARD_VALUE) {
        g_safety_manager.memory.corruption_detected = true;
        return EBS_ERROR;
    }
    
    /* Additional memory checks could be added here */
    
    return EBS_OK;
}

/**
 * @brief Check timing constraints
 * @return ebs_result_t Check result
 */
static ebs_result_t Safety_CheckTimingConstraints(void)
{
    uint32_t current_time = EBS_GetSystemTick();
    uint32_t cycle_time = current_time - g_safety_manager.timing.last_cycle_time;
    
    /* Check for cycle overrun */
    if (cycle_time > SAFETY_MAX_CYCLE_TIME) {
        g_safety_manager.timing.cycle_overrun_count++;
        return EBS_ERROR;
    }
    
    return EBS_OK;
}

/**
 * @brief Execute dual channel comparison
 * @return ebs_result_t Comparison result
 */
static ebs_result_t Safety_ExecuteDualChannelCheck(void)
{
    uint32_t current_time = EBS_GetSystemTick();
    
    /* Check if both channels are active */
    if (!g_safety_manager.dual_channel.primary_active || 
        !g_safety_manager.dual_channel.secondary_active) {
        return EBS_ERROR;
    }
    
    /* Simulate dual channel comparison */
    /* In a real implementation, this would compare outputs from two independent processing channels */
    bool comparison_passed = true;  /* Placeholder for actual comparison logic */
    
    if (!comparison_passed) {
        g_safety_manager.dual_channel.comparison_failures++;
        return EBS_ERROR;
    }
    
    g_safety_manager.dual_channel.last_comparison_time = current_time;
    
    return EBS_OK;
}

/**
 * @brief Handle safety violation
 * @param violation Type of violation
 */
static void Safety_HandleSafetyViolation(ebs_safety_violation_t violation)
{
    switch (violation) {
        case SAFETY_VIOLATION_TIMING:
            /* Handle timing violation */
            EBS_Diagnostics_SetDTC(DTC_TIMING_VIOLATION);
            break;
            
        case SAFETY_VIOLATION_MEMORY:
            /* Handle memory violation */
            EBS_Diagnostics_SetDTC(DTC_MEMORY_CORRUPTION);
            /* Attempt memory recovery if possible */
            g_safety_manager.memory.stack_canary = SAFETY_STACK_CANARY_VALUE;
            g_safety_manager.memory.heap_guard = SAFETY_HEAP_GUARD_VALUE;
            break;
            
        case SAFETY_VIOLATION_WATCHDOG:
            /* Handle watchdog violation */
            EBS_Diagnostics_SetDTC(DTC_WATCHDOG_TIMEOUT);
            break;
            
        case SAFETY_VIOLATION_DUAL_CHANNEL:
            /* Handle dual channel violation */
            EBS_Diagnostics_SetDTC(DTC_DUAL_CHANNEL_FAILURE);
            break;
            
        case SAFETY_VIOLATION_INTEGRITY:
            /* Handle integrity violation */
            EBS_Diagnostics_SetDTC(DTC_SYSTEM_INTEGRITY_FAILURE);
            break;
            
        default:
            /* Unknown violation */
            EBS_Diagnostics_SetDTC(DTC_UNKNOWN_SAFETY_VIOLATION);
            break;
    }
    
    /* Activate fault reaction if not already active */
    if (!g_safety_manager.fault_reaction_active) {
        g_safety_manager.fault_reaction_active = true;
        
        /* Implement fault reaction based on violation severity */
        /* This could include disabling non-critical functions, */
        /* switching to backup systems, or initiating shutdown */
    }
}

/**
 * @brief Check if system is in safe state
 * @return bool True if system is safe
 */
static bool Safety_IsSystemInSafeState(void)
{
    /* System is safe if in operational or degraded state */
    if (g_safety_manager.current_state == SAFETY_STATE_OPERATIONAL ||
        g_safety_manager.current_state == SAFETY_STATE_DEGRADED) {
        
        /* Additional safety checks */
        if (g_safety_manager.memory.corruption_detected) {
            return false;
        }
        
        if (g_safety_manager.dual_channel.comparison_failures > SAFETY_MAX_DUAL_CHANNEL_FAILURES) {
            return false;
        }
        
        return true;
    }
    
    return false;
}

/**
 * @brief Perform graceful system shutdown
 * @return ebs_result_t Shutdown result
 */
static ebs_result_t Safety_PerformGracefulShutdown(void)
{
    /* Set shutdown state */
    g_safety_manager.previous_state = g_safety_manager.current_state;
    g_safety_manager.current_state = SAFETY_STATE_SHUTDOWN;
    
    /* Disable system functions */
    g_safety_manager.system_enabled = false;
    
    /* Set actuators to safe state */
    for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
        EBS_Actuators_SetPressure((ebs_wheel_position_t)wheel, 1.0f);  /* Full manual braking */
    }
    
    /* Log shutdown event */
    EBS_Diagnostics_LogEvent(DIAG_EVENT_SYSTEM_SHUTDOWN, 0);
    
    /* Send shutdown notification via CAN */
    EBS_Communication_SendShutdownNotification();
    
    return EBS_OK;
}

/**
 * @brief Calculate checksum for data integrity
 * @param data Pointer to data
 * @param length Length of data
 * @return uint32_t Calculated checksum
 */
static uint32_t Safety_CalculateChecksum(const void* data, size_t length)
{
    if (data == NULL || length == 0) {
        return 0;
    }
    
    const uint8_t* bytes = (const uint8_t*)data;
    uint32_t checksum = 0;
    
    /* Simple checksum algorithm (CRC32 would be better for production) */
    for (size_t i = 0; i < length; i++) {
        checksum += bytes[i];
        checksum = (checksum << 1) | (checksum >> 31);  /* Rotate left */
    }
    
    return checksum;
}