#ifndef FAULT_MANAGEMENT_H
#define FAULT_MANAGEMENT_H

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "Rte_FaultManagement.h"
#include "Dem.h"
#include "Det.h"

/* AUTOSAR Software Component Version Information */
#define FAULT_MANAGEMENT_SW_MAJOR_VERSION    1
#define FAULT_MANAGEMENT_SW_MINOR_VERSION    0
#define FAULT_MANAGEMENT_SW_PATCH_VERSION    0

/* Fault Management Constants */
#define FAULT_MAX_ENTRIES                32      /* Maximum number of fault entries */
#define FAULT_HISTORY_SIZE               10      /* Fault history buffer size */
#define FAULT_TIMEOUT_MS                 5000    /* Fault timeout in milliseconds */

/* System Fault Levels */
typedef enum {
    FAULT_LEVEL_NONE = 0,
    FAULT_LEVEL_INFO,                   /* Informational fault */
    FAULT_LEVEL_WARNING,                /* Warning level fault */
    FAULT_LEVEL_ERROR,                  /* Error level fault */
    FAULT_LEVEL_CRITICAL                /* Critical fault - system shutdown */
} FaultLevel_t;

/* System Fault Categories */
typedef enum {
    FAULT_CATEGORY_SENSOR = 0,
    FAULT_CATEGORY_MOTOR,
    FAULT_CATEGORY_COMMUNICATION,
    FAULT_CATEGORY_POWER,
    FAULT_CATEGORY_SOFTWARE,
    FAULT_CATEGORY_HARDWARE,
    FAULT_CATEGORY_CALIBRATION
} FaultCategory_t;

/* System Fault Codes */
typedef enum {
    SYSTEM_FAULT_NONE = 0,
    
    /* Sensor Faults */
    SYSTEM_FAULT_TORQUE_SENSOR_FAILURE,
    SYSTEM_FAULT_ANGLE_SENSOR_FAILURE,
    SYSTEM_FAULT_SPEED_SENSOR_FAILURE,
    SYSTEM_FAULT_SENSOR_CALIBRATION_ERROR,
    
    /* Motor Faults */
    SYSTEM_FAULT_MOTOR_OVERCURRENT,
    SYSTEM_FAULT_MOTOR_OVERTEMPERATURE,
    SYSTEM_FAULT_MOTOR_DRIVER_FAILURE,
    SYSTEM_FAULT_MOTOR_SENSOR_FAILURE,
    
    /* Communication Faults */
    SYSTEM_FAULT_CAN_BUS_ERROR,
    SYSTEM_FAULT_LIN_BUS_ERROR,
    SYSTEM_FAULT_SPI_COMMUNICATION_ERROR,
    SYSTEM_FAULT_I2C_COMMUNICATION_ERROR,
    
    /* Power Faults */
    SYSTEM_FAULT_UNDERVOLTAGE,
    SYSTEM_FAULT_OVERVOLTAGE,
    SYSTEM_FAULT_POWER_SUPPLY_FAILURE,
    SYSTEM_FAULT_BATTERY_LOW,
    
    /* Software Faults */
    SYSTEM_FAULT_SOFTWARE_TIMEOUT,
    SYSTEM_FAULT_MEMORY_ERROR,
    SYSTEM_FAULT_STACK_OVERFLOW,
    SYSTEM_FAULT_WATCHDOG_TIMEOUT,
    
    /* Hardware Faults */
    SYSTEM_FAULT_ECU_TEMPERATURE_HIGH,
    SYSTEM_FAULT_ECU_INTERNAL_ERROR,
    SYSTEM_FAULT_IO_PIN_FAILURE,
    SYSTEM_FAULT_ADC_FAILURE,
    
    /* Calibration Faults */
    SYSTEM_FAULT_CALIBRATION_INVALID,
    SYSTEM_FAULT_CALIBRATION_CORRUPTED,
    SYSTEM_FAULT_CALIBRATION_MISSING
} SystemFaultCode_t;

/* Fault Entry Structure */
typedef struct {
    SystemFaultCode_t fault_code;       /* Fault code */
    FaultLevel_t fault_level;           /* Fault severity level */
    FaultCategory_t fault_category;     /* Fault category */
    uint32_t timestamp;                 /* Fault occurrence timestamp */
    uint32_t occurrence_count;          /* Number of occurrences */
    boolean active;                     /* Fault active flag */
    boolean reported;                   /* Fault reported flag */
    char description[64];               /* Fault description */
} FaultEntry_t;

/* Fault Management Data Structure */
typedef struct {
    FaultEntry_t fault_entries[FAULT_MAX_ENTRIES];  /* Fault entries array */
    uint8_t active_fault_count;                     /* Number of active faults */
    uint8_t total_fault_count;                      /* Total number of faults */
    FaultLevel_t highest_active_level;              /* Highest active fault level */
    boolean system_healthy;                         /* System health status */
    boolean safe_mode_active;                       /* Safe mode active flag */
    uint32_t last_diagnosis_timestamp;              /* Last diagnosis timestamp */
} FaultManagementData_t;

/* Fault Management Configuration */
typedef struct {
    boolean fault_reporting_enabled;    /* Enable fault reporting */
    boolean safe_mode_enabled;          /* Enable safe mode operation */
    uint32_t diagnosis_interval_ms;     /* Diagnosis interval in milliseconds */
    uint32_t fault_timeout_ms;          /* Fault timeout in milliseconds */
    FaultLevel_t safe_mode_threshold;   /* Fault level threshold for safe mode */
} FaultManagementConfig_t;

/* Function Prototypes */

/**
 * @brief Initialize the Fault Management Software Component
 * @param config Pointer to fault management configuration
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType FaultManagement_Init(const FaultManagementConfig_t* config);

/**
 * @brief Main fault management function for system monitoring
 * @param fault_data Pointer to fault management data structure
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType FaultManagement_MainFunction(FaultManagementData_t* fault_data);

/**
 * @brief Report a new fault
 * @param fault_code System fault code
 * @param fault_level Fault severity level
 * @param fault_category Fault category
 * @param description Fault description string
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType FaultManagement_ReportFault(SystemFaultCode_t fault_code,
                                         FaultLevel_t fault_level,
                                         FaultCategory_t fault_category,
                                         const char* description);

/**
 * @brief Clear a specific fault
 * @param fault_code System fault code to clear
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType FaultManagement_ClearFault(SystemFaultCode_t fault_code);

/**
 * @brief Clear all active faults
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType FaultManagement_ClearAllFaults(void);

/**
 * @brief Check if a specific fault is active
 * @param fault_code System fault code to check
 * @return boolean - TRUE if fault is active, FALSE otherwise
 */
boolean FaultManagement_IsFaultActive(SystemFaultCode_t fault_code);

/**
 * @brief Get fault information
 * @param fault_code System fault code
 * @param fault_entry Pointer to store fault information
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType FaultManagement_GetFaultInfo(SystemFaultCode_t fault_code,
                                          FaultEntry_t* fault_entry);

/**
 * @brief Get all active faults
 * @param fault_codes Array to store active fault codes
 * @param max_count Maximum number of fault codes to retrieve
 * @param actual_count Pointer to store actual count
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType FaultManagement_GetActiveFaults(SystemFaultCode_t* fault_codes,
                                             uint8_t max_count,
                                             uint8_t* actual_count);

/**
 * @brief Get system health status
 * @param fault_data Pointer to fault management data structure
 * @return boolean - TRUE if system is healthy, FALSE otherwise
 */
boolean FaultManagement_IsSystemHealthy(const FaultManagementData_t* fault_data);

/**
 * @brief Check if safe mode should be activated
 * @param fault_data Pointer to fault management data structure
 * @return boolean - TRUE if safe mode should be active, FALSE otherwise
 */
boolean FaultManagement_ShouldActivateSafeMode(const FaultManagementData_t* fault_data);

/**
 * @brief Perform system-wide fault diagnosis
 * @param fault_data Pointer to fault management data structure
 * @return Std_ReturnType - E_OK if diagnosis passed, E_NOT_OK otherwise
 */
Std_ReturnType FaultManagement_PerformDiagnosis(FaultManagementData_t* fault_data);

/**
 * @brief Handle fault level escalation
 * @param fault_data Pointer to fault management data structure
 */
void FaultManagement_HandleFaultEscalation(FaultManagementData_t* fault_data);

/**
 * @brief Report faults to Diagnostic Event Manager (DEM)
 * @param fault_data Pointer to fault management data structure
 */
void FaultManagement_ReportToDEM(const FaultManagementData_t* fault_data);

/**
 * @brief Get fault statistics
 * @param total_faults Pointer to store total fault count
 * @param active_faults Pointer to store active fault count
 * @param highest_level Pointer to store highest fault level
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType FaultManagement_GetFaultStatistics(uint8_t* total_faults,
                                                 uint8_t* active_faults,
                                                 FaultLevel_t* highest_level);

/**
 * @brief Set fault management configuration
 * @param config Pointer to fault management configuration
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType FaultManagement_SetConfiguration(const FaultManagementConfig_t* config);

/**
 * @brief Get fault management configuration
 * @param config Pointer to store current configuration
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType FaultManagement_GetConfiguration(FaultManagementConfig_t* config);

/**
 * @brief Reset fault management system
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType FaultManagement_Reset(void);

/**
 * @brief Deinitialize the Fault Management Software Component
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType FaultManagement_DeInit(void);

#endif /* FAULT_MANAGEMENT_H */ 