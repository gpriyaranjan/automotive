/**
 * @file ebs_diagnostics.c
 * @brief Electronic Braking System - Diagnostics Implementation
 * @version 1.0
 * @date 2025-07-29
 * @author EBS Development Team
 * 
 * Diagnostics and fault management implementation for EBS system
 * 
 * Safety Level: ASIL-D
 * Compliance: ISO 26262, MISRA C:2012
 */

#include "ebs_diagnostics.h"
#include "ebs_safety.h"
#include "ebs_communication.h"
#include <string.h>

/* Static Variables */
static ebs_diagnostics_manager_t g_diagnostics_manager;
static bool g_diagnostics_initialized = false;

/* Static Function Prototypes */
static ebs_result_t Diagnostics_InitializeDTCTable(void);
static ebs_result_t Diagnostics_InitializeEventLog(void);
static bool Diagnostics_ValidateDTC(ebs_dtc_code_t dtc_code);
static ebs_result_t Diagnostics_StoreDTC(ebs_dtc_code_t dtc_code);
static ebs_result_t Diagnostics_StoreEvent(ebs_diagnostic_event_t event_type, uint32_t data);
static void Diagnostics_UpdateStatistics(void);
static ebs_result_t Diagnostics_ProcessPendingDTCs(void);

/**
 * @brief Initialize diagnostics subsystem
 * @return ebs_result_t Initialization result
 */
ebs_result_t EBS_Diagnostics_Init(void)
{
    /* Clear diagnostics manager state */
    memset(&g_diagnostics_manager, 0, sizeof(g_diagnostics_manager));
    
    /* Initialize DTC table */
    if (Diagnostics_InitializeDTCTable() != EBS_OK) {
        return EBS_ERROR;
    }
    
    /* Initialize event log */
    if (Diagnostics_InitializeEventLog() != EBS_OK) {
        return EBS_ERROR;
    }
    
    /* Initialize diagnostics manager state */
    g_diagnostics_manager.system_enabled = true;
    g_diagnostics_manager.last_update_time = EBS_GetSystemTick();
    g_diagnostics_manager.update_count = 0;
    g_diagnostics_manager.total_dtc_count = 0;
    g_diagnostics_manager.active_dtc_count = 0;
    
    g_diagnostics_initialized = true;
    
    return EBS_OK;
}

/**
 * @brief Perform diagnostics self-test
 * @return bool True if self-test passed
 */
bool EBS_Diagnostics_SelfTest(void)
{
    if (!g_diagnostics_initialized) {
        return false;
    }
    
    bool test_passed = true;
    
    /* Test DTC validation */
    if (!Diagnostics_ValidateDTC(DTC_SENSOR_SELF_TEST_FAILED)) {
        test_passed = false;
    }
    
    /* Test DTC storage */
    ebs_dtc_code_t test_dtc = DTC_ALGORITHM_SELF_TEST_FAILED;
    if (Diagnostics_StoreDTC(test_dtc) != EBS_OK) {
        test_passed = false;
    }
    
    /* Test event logging */
    if (Diagnostics_StoreEvent(DIAG_EVENT_SYSTEM_STARTUP, 0) != EBS_OK) {
        test_passed = false;
    }
    
    /* Clear test DTC */
    EBS_Diagnostics_ClearDTC(test_dtc);
    
    return test_passed;
}

/**
 * @brief Update diagnostics (called every cycle)
 * @return ebs_result_t Update result
 */
ebs_result_t EBS_Diagnostics_Update(void)
{
    if (!g_diagnostics_initialized || !g_diagnostics_manager.system_enabled) {
        return EBS_NOT_INITIALIZED;
    }
    
    /* Process pending DTCs */
    Diagnostics_ProcessPendingDTCs();
    
    /* Update statistics */
    Diagnostics_UpdateStatistics();
    
    /* Update manager state */
    g_diagnostics_manager.last_update_time = EBS_GetSystemTick();
    g_diagnostics_manager.update_count++;
    
    return EBS_OK;
}

/**
 * @brief Set diagnostic trouble code
 * @param dtc_code DTC code to set
 * @return ebs_result_t Set result
 */
ebs_result_t EBS_Diagnostics_SetDTC(ebs_dtc_code_t dtc_code)
{
    if (!g_diagnostics_initialized) {
        return EBS_NOT_INITIALIZED;
    }
    
    /* Validate DTC code */
    if (!Diagnostics_ValidateDTC(dtc_code)) {
        return EBS_INVALID_PARAM;
    }
    
    /* Store DTC */
    return Diagnostics_StoreDTC(dtc_code);
}

/**
 * @brief Clear diagnostic trouble code
 * @param dtc_code DTC code to clear
 * @return ebs_result_t Clear result
 */
ebs_result_t EBS_Diagnostics_ClearDTC(ebs_dtc_code_t dtc_code)
{
    if (!g_diagnostics_initialized) {
        return EBS_NOT_INITIALIZED;
    }
    
    /* Find DTC in table */
    for (uint32_t i = 0; i < DIAGNOSTICS_MAX_DTC_COUNT; i++) {
        ebs_dtc_entry_t* entry = &g_diagnostics_manager.dtc_table[i];
        
        if (entry->dtc_code == dtc_code && entry->active) {
            /* Clear DTC */
            entry->active = false;
            entry->cleared_timestamp = EBS_GetSystemTick();
            entry->clear_count++;
            
            /* Update active count */
            if (g_diagnostics_manager.active_dtc_count > 0) {
                g_diagnostics_manager.active_dtc_count--;
            }
            
            /* Log event */
            EBS_Diagnostics_LogEvent(DIAG_EVENT_DTC_CLEARED, (uint32_t)dtc_code);
            
            return EBS_OK;
        }
    }
    
    return EBS_NOT_FOUND;
}

/**
 * @brief Check if DTC is active
 * @param dtc_code DTC code to check
 * @return bool True if DTC is active
 */
bool EBS_Diagnostics_IsDTCActive(ebs_dtc_code_t dtc_code)
{
    if (!g_diagnostics_initialized) {
        return false;
    }
    
    /* Search for DTC in table */
    for (uint32_t i = 0; i < DIAGNOSTICS_MAX_DTC_COUNT; i++) {
        ebs_dtc_entry_t* entry = &g_diagnostics_manager.dtc_table[i];
        
        if (entry->dtc_code == dtc_code && entry->active) {
            return true;
        }
    }
    
    return false;
}

/**
 * @brief Get active DTC count
 * @return uint32_t Number of active DTCs
 */
uint32_t EBS_Diagnostics_GetActiveDTCCount(void)
{
    if (!g_diagnostics_initialized) {
        return 0;
    }
    
    return g_diagnostics_manager.active_dtc_count;
}

/**
 * @brief Log diagnostic event
 * @param event_type Type of event
 * @param data Event data
 * @return ebs_result_t Log result
 */
ebs_result_t EBS_Diagnostics_LogEvent(ebs_diagnostic_event_t event_type, uint32_t data)
{
    if (!g_diagnostics_initialized) {
        return EBS_NOT_INITIALIZED;
    }
    
    return Diagnostics_StoreEvent(event_type, data);
}

/**
 * @brief Get diagnostic statistics
 * @return ebs_diagnostic_statistics_t* Pointer to statistics
 */
const ebs_diagnostic_statistics_t* EBS_Diagnostics_GetStatistics(void)
{
    if (!g_diagnostics_initialized) {
        return NULL;
    }
    
    return &g_diagnostics_manager.statistics;
}

/**
 * @brief Get DTC table
 * @return ebs_dtc_entry_t* Pointer to DTC table
 */
const ebs_dtc_entry_t* EBS_Diagnostics_GetDTCTable(void)
{
    if (!g_diagnostics_initialized) {
        return NULL;
    }
    
    return g_diagnostics_manager.dtc_table;
}

/**
 * @brief Get event log
 * @return ebs_diagnostic_event_entry_t* Pointer to event log
 */
const ebs_diagnostic_event_entry_t* EBS_Diagnostics_GetEventLog(void)
{
    if (!g_diagnostics_initialized) {
        return NULL;
    }
    
    return g_diagnostics_manager.event_log;
}

/* Static Function Implementations */

/**
 * @brief Initialize DTC table
 * @return ebs_result_t Initialization result
 */
static ebs_result_t Diagnostics_InitializeDTCTable(void)
{
    /* Clear DTC table */
    memset(g_diagnostics_manager.dtc_table, 0, 
           sizeof(g_diagnostics_manager.dtc_table));
    
    /* Initialize each entry */
    for (uint32_t i = 0; i < DIAGNOSTICS_MAX_DTC_COUNT; i++) {
        ebs_dtc_entry_t* entry = &g_diagnostics_manager.dtc_table[i];
        
        entry->dtc_code = DTC_NO_FAULT;
        entry->active = false;
        entry->pending = false;
        entry->confirmed = false;
        entry->first_occurrence_timestamp = 0;
        entry->last_occurrence_timestamp = 0;
        entry->cleared_timestamp = 0;
        entry->occurrence_count = 0;
        entry->clear_count = 0;
    }
    
    return EBS_OK;
}

/**
 * @brief Initialize event log
 * @return ebs_result_t Initialization result
 */
static ebs_result_t Diagnostics_InitializeEventLog(void)
{
    /* Clear event log */
    memset(g_diagnostics_manager.event_log, 0, 
           sizeof(g_diagnostics_manager.event_log));
    
    g_diagnostics_manager.event_log_index = 0;
    g_diagnostics_manager.event_log_count = 0;
    
    return EBS_OK;
}

/**
 * @brief Validate DTC code
 * @param dtc_code DTC code to validate
 * @return bool True if valid
 */
static bool Diagnostics_ValidateDTC(ebs_dtc_code_t dtc_code)
{
    /* Check if DTC code is in valid range */
    if (dtc_code >= DTC_NO_FAULT && dtc_code < DTC_MAX_CODE) {
        return true;
    }
    
    return false;
}

/**
 * @brief Store DTC in table
 * @param dtc_code DTC code to store
 * @return ebs_result_t Store result
 */
static ebs_result_t Diagnostics_StoreDTC(ebs_dtc_code_t dtc_code)
{
    uint32_t current_time = EBS_GetSystemTick();
    
    /* Check if DTC already exists */
    for (uint32_t i = 0; i < DIAGNOSTICS_MAX_DTC_COUNT; i++) {
        ebs_dtc_entry_t* entry = &g_diagnostics_manager.dtc_table[i];
        
        if (entry->dtc_code == dtc_code) {
            /* Update existing entry */
            if (!entry->active) {
                entry->active = true;
                g_diagnostics_manager.active_dtc_count++;
            }
            
            entry->last_occurrence_timestamp = current_time;
            entry->occurrence_count++;
            
            /* Mark as confirmed after multiple occurrences */
            if (entry->occurrence_count >= DIAGNOSTICS_CONFIRMATION_THRESHOLD) {
                entry->confirmed = true;
            }
            
            return EBS_OK;
        }
    }
    
    /* Find empty slot for new DTC */
    for (uint32_t i = 0; i < DIAGNOSTICS_MAX_DTC_COUNT; i++) {
        ebs_dtc_entry_t* entry = &g_diagnostics_manager.dtc_table[i];
        
        if (entry->dtc_code == DTC_NO_FAULT) {
            /* Store new DTC */
            entry->dtc_code = dtc_code;
            entry->active = true;
            entry->pending = true;
            entry->confirmed = false;
            entry->first_occurrence_timestamp = current_time;
            entry->last_occurrence_timestamp = current_time;
            entry->occurrence_count = 1;
            entry->clear_count = 0;
            
            /* Update counters */
            g_diagnostics_manager.active_dtc_count++;
            g_diagnostics_manager.total_dtc_count++;
            
            /* Log event */
            EBS_Diagnostics_LogEvent(DIAG_EVENT_DTC_SET, (uint32_t)dtc_code);
            
            return EBS_OK;
        }
    }
    
    /* DTC table is full */
    return EBS_BUFFER_FULL;
}

/**
 * @brief Store event in log
 * @param event_type Event type
 * @param data Event data
 * @return ebs_result_t Store result
 */
static ebs_result_t Diagnostics_StoreEvent(ebs_diagnostic_event_t event_type, uint32_t data)
{
    uint32_t current_time = EBS_GetSystemTick();
    uint32_t index = g_diagnostics_manager.event_log_index;
    
    /* Store event in circular buffer */
    ebs_diagnostic_event_entry_t* entry = &g_diagnostics_manager.event_log[index];
    
    entry->event_type = event_type;
    entry->data = data;
    entry->timestamp = current_time;
    
    /* Update index and count */
    g_diagnostics_manager.event_log_index = (index + 1) % DIAGNOSTICS_MAX_EVENT_COUNT;
    
    if (g_diagnostics_manager.event_log_count < DIAGNOSTICS_MAX_EVENT_COUNT) {
        g_diagnostics_manager.event_log_count++;
    }
    
    return EBS_OK;
}

/**
 * @brief Update diagnostic statistics
 */
static void Diagnostics_UpdateStatistics(void)
{
    ebs_diagnostic_statistics_t* stats = &g_diagnostics_manager.statistics;
    
    /* Update basic counters */
    stats->total_dtc_count = g_diagnostics_manager.total_dtc_count;
    stats->active_dtc_count = g_diagnostics_manager.active_dtc_count;
    stats->event_log_count = g_diagnostics_manager.event_log_count;
    
    /* Count confirmed DTCs */
    stats->confirmed_dtc_count = 0;
    for (uint32_t i = 0; i < DIAGNOSTICS_MAX_DTC_COUNT; i++) {
        ebs_dtc_entry_t* entry = &g_diagnostics_manager.dtc_table[i];
        if (entry->confirmed) {
            stats->confirmed_dtc_count++;
        }
    }
    
    /* Update last update time */
    stats->last_update_time = EBS_GetSystemTick();
}

/**
 * @brief Process pending DTCs
 * @return ebs_result_t Process result
 */
static ebs_result_t Diagnostics_ProcessPendingDTCs(void)
{
    uint32_t current_time = EBS_GetSystemTick();
    
    for (uint32_t i = 0; i < DIAGNOSTICS_MAX_DTC_COUNT; i++) {
        ebs_dtc_entry_t* entry = &g_diagnostics_manager.dtc_table[i];
        
        if (entry->pending && entry->active) {
            /* Check if DTC should be confirmed */
            uint32_t time_since_first = current_time - entry->first_occurrence_timestamp;
            
            if (time_since_first >= DIAGNOSTICS_CONFIRMATION_TIME_MS ||
                entry->occurrence_count >= DIAGNOSTICS_CONFIRMATION_THRESHOLD) {
                
                entry->confirmed = true;
                entry->pending = false;
                
                /* Log confirmation event */
                EBS_Diagnostics_LogEvent(DIAG_EVENT_DTC_CONFIRMED, (uint32_t)entry->dtc_code);
                
                /* Send CAN message for confirmed DTC */
                EBS_Communication_SendDTCNotification(entry->dtc_code, true);
            }
        }
    }
    
    return EBS_OK;
}

/* Stub implementations for missing functions */
ebs_result_t EBS_Communication_SendDTCNotification(ebs_dtc_code_t dtc_code, bool confirmed)
{
    /* Placeholder implementation */
    (void)dtc_code;
    (void)confirmed;
    return EBS_OK;
}

ebs_result_t EBS_Communication_SendShutdownNotification(void)
{
    /* Placeholder implementation */
    return EBS_OK;
}