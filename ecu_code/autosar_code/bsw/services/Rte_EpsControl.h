#ifndef RTE_EPS_CONTROL_H
#define RTE_EPS_CONTROL_H

#include "Std_Types.h"
#include "ComStack_Types.h"

/* AUTOSAR RTE Version Information */
#define RTE_SW_MAJOR_VERSION    4
#define RTE_SW_MINOR_VERSION    4
#define RTE_SW_PATCH_VERSION    0

/* RTE Module ID */
#define RTE_MODULE_ID_EPS_CONTROL    0x1000

/* RTE Service IDs */
#define RTE_SID_EPS_CONTROL_INIT     0x01
#define RTE_SID_EPS_CONTROL_MAIN     0x02
#define RTE_SID_EPS_CONTROL_DEINIT   0x03

/* RTE Error Codes */
#define RTE_EPS_CONTROL_E_OK         0x00
#define RTE_EPS_CONTROL_E_NOT_OK     0x01
#define RTE_EPS_CONTROL_E_TIMEOUT    0x02
#define RTE_EPS_CONTROL_E_LOST_DATA  0x03
#define RTE_EPS_CONTROL_E_INVALID    0x04

/* RTE Interface Definitions */

/* Client-Server Interface: Sensor Data */
typedef struct {
    float driver_torque;           /* Driver applied torque (Nm) */
    float steering_angle;          /* Steering wheel angle (degrees) */
    float vehicle_speed;           /* Vehicle speed (km/h) */
    boolean data_valid;            /* Data validity flag */
    uint32_t timestamp;            /* Data timestamp */
} Rte_SensorData_t;

/* Client-Server Interface: Motor Control */
typedef struct {
    float target_current;          /* Target motor current (A) */
    float actual_current;          /* Actual motor current (A) */
    float motor_voltage;           /* Motor voltage (V) */
    float motor_temperature;       /* Motor temperature (°C) */
    boolean motor_enabled;         /* Motor enable status */
    boolean fault_detected;        /* Motor fault status */
} Rte_MotorData_t;

/* Client-Server Interface: Fault Management */
typedef struct {
    uint8_t fault_count;           /* Number of active faults */
    uint8_t fault_level;           /* Highest fault level */
    boolean system_healthy;        /* System health status */
    boolean safe_mode_active;      /* Safe mode status */
} Rte_FaultData_t;

/* Sender-Receiver Interface: ADAS Integration */
typedef struct {
    boolean adas_active;           /* ADAS system active flag */
    float adas_command_torque;     /* ADAS command torque (Nm) */
    uint8_t adas_mode;             /* ADAS operation mode */
    boolean adas_override;         /* ADAS override flag */
} Rte_AdasData_t;

/* Sender-Receiver Interface: System Status */
typedef struct {
    uint8_t system_state;          /* System state */
    uint8_t control_mode;          /* Control mode */
    boolean eps_enabled;           /* EPS system enabled */
    uint32_t uptime;               /* System uptime */
} Rte_SystemStatus_t;

/* RTE Function Prototypes */

/* Client-Server Interface Functions */

/**
 * @brief Get sensor data from Sensor Interface
 * @param sensor_data Pointer to store sensor data
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
extern Std_ReturnType Rte_Call_SensorInterface_GetSensorData(Rte_SensorData_t* sensor_data);

/**
 * @brief Set motor current command to Motor Control
 * @param target_current Target motor current (A)
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
extern Std_ReturnType Rte_Call_MotorControl_SetTargetCurrent(float target_current);

/**
 * @brief Get motor data from Motor Control
 * @param motor_data Pointer to store motor data
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
extern Std_ReturnType Rte_Call_MotorControl_GetMotorData(Rte_MotorData_t* motor_data);

/**
 * @brief Report fault to Fault Management
 * @param fault_code Fault code
 * @param fault_level Fault level
 * @param description Fault description
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
extern Std_ReturnType Rte_Call_FaultManagement_ReportFault(uint8_t fault_code,
                                                          uint8_t fault_level,
                                                          const char* description);

/**
 * @brief Get fault data from Fault Management
 * @param fault_data Pointer to store fault data
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
extern Std_ReturnType Rte_Call_FaultManagement_GetFaultData(Rte_FaultData_t* fault_data);

/* Sender-Receiver Interface Functions */

/**
 * @brief Write ADAS data
 * @param adas_data ADAS data to write
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
extern Std_ReturnType Rte_Write_AdasData(const Rte_AdasData_t* adas_data);

/**
 * @brief Read ADAS data
 * @param adas_data Pointer to store ADAS data
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
extern Std_ReturnType Rte_Read_AdasData(Rte_AdasData_t* adas_data);

/**
 * @brief Write system status
 * @param system_status System status to write
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
extern Std_ReturnType Rte_Write_SystemStatus(const Rte_SystemStatus_t* system_status);

/**
 * @brief Read system status
 * @param system_status Pointer to store system status
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
extern Std_ReturnType Rte_Read_SystemStatus(Rte_SystemStatus_t* system_status);

/* Mode Management Interface Functions */

/**
 * @brief Switch to normal mode
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
extern Std_ReturnType Rte_Switch_EpsControl_Mode_Normal(void);

/**
 * @brief Switch to safe mode
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
extern Std_ReturnType Rte_Switch_EpsControl_Mode_Safe(void);

/**
 * @brief Switch to fault mode
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
extern Std_ReturnType Rte_Switch_EpsControl_Mode_Fault(void);

/* Timing Service Functions */

/**
 * @brief Get current system time
 * @return uint32_t Current system time in milliseconds
 */
extern uint32_t Rte_GetSystemTime(void);

/**
 * @brief Wait for specified time
 * @param delay_ms Delay time in milliseconds
 */
extern void Rte_Wait(uint32_t delay_ms);

/* Error Handling Functions */

/**
 * @brief Report error to Development Error Tracer (DET)
 * @param module_id Module ID
 * @param instance_id Instance ID
 * @param service_id Service ID
 * @param error_code Error code
 */
extern void Rte_ReportError(uint16_t module_id,
                           uint8_t instance_id,
                           uint8_t service_id,
                           uint8_t error_code);

/**
 * @brief Report runtime error to Development Error Tracer (DET)
 * @param module_id Module ID
 * @param instance_id Instance ID
 * @param service_id Service ID
 * @param error_code Error code
 */
extern void Rte_ReportRuntimeError(uint16_t module_id,
                                  uint8_t instance_id,
                                  uint8_t service_id,
                                  uint8_t error_code);

/* Memory Management Functions */

/**
 * @brief Allocate memory
 * @param size Size of memory to allocate
 * @return void* Pointer to allocated memory, NULL if failed
 */
extern void* Rte_Malloc(uint32_t size);

/**
 * @brief Free allocated memory
 * @param ptr Pointer to memory to free
 */
extern void Rte_Free(void* ptr);

/* Interrupt Management Functions */

/**
 * @brief Disable interrupts
 * @return uint32_t Previous interrupt state
 */
extern uint32_t Rte_DisableInterrupts(void);

/**
 * @brief Enable interrupts
 * @param previous_state Previous interrupt state
 */
extern void Rte_EnableInterrupts(uint32_t previous_state);

/* Watchdog Functions */

/**
 * @brief Trigger watchdog
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
extern Std_ReturnType Rte_TriggerWatchdog(void);

/**
 * @brief Check watchdog status
 * @return boolean - TRUE if watchdog is active, FALSE otherwise
 */
extern boolean Rte_IsWatchdogActive(void);

#endif /* RTE_EPS_CONTROL_H */ 