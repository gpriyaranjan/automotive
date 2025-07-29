/**
 * @file ebs_main.c
 * @brief Electronic Braking System - Main Application Entry Point
 * @version 1.0
 * @date 2025-07-29
 * @author EBS Development Team
 * 
 * Main application file for the Electronic Braking System (EBS)
 * Implements the primary control loop and system initialization
 * 
 * Safety Level: ASIL-D
 * Compliance: ISO 26262, UN-ECE R13-H
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "ebs_config.h"
#include "ebs_types.h"
#include "ebs_safety.h"
#include "ebs_abs.h"
#include "ebs_esc.h"
#include "ebs_tcs.h"
#include "ebs_sensors.h"
#include "ebs_actuators.h"
#include "ebs_communication.h"
#include "ebs_diagnostics.h"
#include "ebs_watchdog.h"

/* Global system state */
static ebs_system_state_t g_system_state = EBS_STATE_INIT;
static ebs_safety_state_t g_safety_state = SAFETY_STATE_UNKNOWN;
static uint32_t g_system_tick_counter = 0;

/* Function prototypes */
static void EBS_SystemInit(void);
static void EBS_MainControlLoop(void);
static void EBS_SafetyMonitoring(void);
static void EBS_SystemShutdown(void);
static bool EBS_SelfTest(void);

/**
 * @brief Main application entry point
 * @return int Application exit code (should never return in normal operation)
 */
int main(void)
{
    /* Initialize system */
    EBS_SystemInit();
    
    /* Perform self-test */
    if (!EBS_SelfTest()) {
        /* Self-test failed - enter safe state */
        EBS_Safety_EnterSafeState(SAFETY_FAULT_SELF_TEST_FAILED);
        g_system_state = EBS_STATE_SAFE_MODE;
    } else {
        /* Self-test passed - enter normal operation */
        g_system_state = EBS_STATE_NORMAL;
    }
    
    /* Main control loop */
    while (1) {
        /* Refresh watchdog */
        EBS_Watchdog_Refresh(WATCHDOG_MAIN_TASK);
        
        /* Safety monitoring (highest priority) */
        EBS_SafetyMonitoring();
        
        /* Main control loop */
        if (g_system_state == EBS_STATE_NORMAL) {
            EBS_MainControlLoop();
        }
        
        /* Increment system tick counter */
        g_system_tick_counter++;
        
        /* Wait for next cycle (1ms) */
        EBS_Delay_Ms(1);
    }
    
    /* Should never reach here */
    EBS_SystemShutdown();
    return 0;
}

/**
 * @brief Initialize EBS system components
 */
static void EBS_SystemInit(void)
{
    /* Initialize hardware abstraction layer */
    EBS_HAL_Init();
    
    /* Initialize watchdog system */
    EBS_Watchdog_Init();
    
    /* Initialize safety monitoring */
    EBS_Safety_Init();
    
    /* Initialize sensor interfaces */
    EBS_Sensors_Init();
    
    /* Initialize actuator interfaces */
    EBS_Actuators_Init();
    
    /* Initialize communication interfaces */
    EBS_Communication_Init();
    
    /* Initialize control algorithms */
    EBS_ABS_Init();
    EBS_ESC_Init();
    EBS_TCS_Init();
    
    /* Initialize diagnostics */
    EBS_Diagnostics_Init();
    
    /* Set initial system state */
    g_system_state = EBS_STATE_INIT;
    g_safety_state = SAFETY_STATE_INIT;
}

/**
 * @brief Main control loop - executes every 1ms
 */
static void EBS_MainControlLoop(void)
{
    static uint32_t abs_counter = 0;
    static uint32_t esc_counter = 0;
    static uint32_t tcs_counter = 0;
    static uint32_t comm_counter = 0;
    static uint32_t diag_counter = 0;
    
    /* Read sensor data (every cycle - 1ms) */
    EBS_Sensors_ReadAll();
    
    /* ABS control (every cycle - 1ms) */
    EBS_ABS_Control();
    
    /* ESC control (every 5ms) */
    if (++esc_counter >= 5) {
        esc_counter = 0;
        EBS_ESC_Control();
    }
    
    /* TCS control (every 10ms) */
    if (++tcs_counter >= 10) {
        tcs_counter = 0;
        EBS_TCS_Control();
    }
    
    /* Update actuators (every cycle - 1ms) */
    EBS_Actuators_Update();
    
    /* Communication tasks (every 10ms) */
    if (++comm_counter >= 10) {
        comm_counter = 0;
        EBS_Communication_Process();
    }
    
    /* Diagnostic tasks (every 100ms) */
    if (++diag_counter >= 100) {
        diag_counter = 0;
        EBS_Diagnostics_Process();
    }
}

/**
 * @brief Safety monitoring - executes every cycle
 */
static void EBS_SafetyMonitoring(void)
{
    /* Check safety state */
    g_safety_state = EBS_Safety_GetState();
    
    /* Handle safety state transitions */
    switch (g_safety_state) {
        case SAFETY_STATE_NORMAL:
            /* Normal operation - no action required */
            break;
            
        case SAFETY_STATE_WARNING:
            /* Warning state - log event and continue */
            EBS_Diagnostics_LogEvent(DIAG_EVENT_SAFETY_WARNING, 0);
            break;
            
        case SAFETY_STATE_DEGRADED:
            /* Degraded state - reduce functionality */
            g_system_state = EBS_STATE_DEGRADED;
            EBS_Diagnostics_LogEvent(DIAG_EVENT_SAFETY_DEGRADED, 0);
            break;
            
        case SAFETY_STATE_SAFE:
            /* Safe state - minimal functionality only */
            g_system_state = EBS_STATE_SAFE_MODE;
            EBS_Diagnostics_LogEvent(DIAG_EVENT_SAFETY_SAFE_STATE, 0);
            break;
            
        default:
            /* Unknown state - enter safe mode */
            EBS_Safety_EnterSafeState(SAFETY_FAULT_UNKNOWN_STATE);
            g_system_state = EBS_STATE_SAFE_MODE;
            break;
    }
    
    /* Monitor system health */
    EBS_Safety_MonitorSystemHealth();
    
    /* Check for critical faults */
    if (EBS_Safety_HasCriticalFault()) {
        /* Critical fault detected - immediate safe state */
        EBS_Safety_EnterSafeState(SAFETY_FAULT_CRITICAL);
        g_system_state = EBS_STATE_SAFE_MODE;
    }
}

/**
 * @brief Perform system self-test
 * @return bool True if self-test passed, false otherwise
 */
static bool EBS_SelfTest(void)
{
    bool test_result = true;
    
    /* Test sensor interfaces */
    if (!EBS_Sensors_SelfTest()) {
        EBS_Diagnostics_SetDTC(DTC_SENSOR_SELF_TEST_FAILED);
        test_result = false;
    }
    
    /* Test actuator interfaces */
    if (!EBS_Actuators_SelfTest()) {
        EBS_Diagnostics_SetDTC(DTC_ACTUATOR_SELF_TEST_FAILED);
        test_result = false;
    }
    
    /* Test communication interfaces */
    if (!EBS_Communication_SelfTest()) {
        EBS_Diagnostics_SetDTC(DTC_COMMUNICATION_SELF_TEST_FAILED);
        test_result = false;
    }
    
    /* Test safety systems */
    if (!EBS_Safety_SelfTest()) {
        EBS_Diagnostics_SetDTC(DTC_SAFETY_SELF_TEST_FAILED);
        test_result = false;
    }
    
    /* Test control algorithms */
    if (!EBS_ABS_SelfTest() || !EBS_ESC_SelfTest() || !EBS_TCS_SelfTest()) {
        EBS_Diagnostics_SetDTC(DTC_ALGORITHM_SELF_TEST_FAILED);
        test_result = false;
    }
    
    return test_result;
}

/**
 * @brief System shutdown procedure
 */
static void EBS_SystemShutdown(void)
{
    /* Enter safe state */
    EBS_Safety_EnterSafeState(SAFETY_FAULT_SYSTEM_SHUTDOWN);
    
    /* Shutdown actuators */
    EBS_Actuators_Shutdown();
    
    /* Shutdown communication */
    EBS_Communication_Shutdown();
    
    /* Log shutdown event */
    EBS_Diagnostics_LogEvent(DIAG_EVENT_SYSTEM_SHUTDOWN, g_system_tick_counter);
    
    /* Shutdown diagnostics */
    EBS_Diagnostics_Shutdown();
    
    /* Final watchdog refresh */
    EBS_Watchdog_Refresh(WATCHDOG_SHUTDOWN);
}

/**
 * @brief Get current system state
 * @return ebs_system_state_t Current system state
 */
ebs_system_state_t EBS_GetSystemState(void)
{
    return g_system_state;
}

/**
 * @brief Get system tick counter
 * @return uint32_t Current tick counter value
 */
uint32_t EBS_GetSystemTick(void)
{
    return g_system_tick_counter;
}

/**
 * @brief Emergency shutdown handler
 * Called from interrupt context for immediate shutdown
 */
void EBS_EmergencyShutdown(void)
{
    /* Disable all interrupts */
    __disable_irq();
    
    /* Immediate safe state activation */
    EBS_Safety_EmergencyStop();
    
    /* Shutdown all actuators immediately */
    EBS_Actuators_EmergencyStop();
    
    /* Infinite loop - system requires reset */
    while (1) {
        /* Keep watchdog alive to prevent reset during emergency */
        EBS_Watchdog_Refresh(WATCHDOG_EMERGENCY);
        EBS_Delay_Ms(10);
    }
}