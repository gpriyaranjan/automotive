/**
 * @file EPS_SWC.h
 * @brief AUTOSAR Software Component Header for Electronic Power Steering
 * @version 1.0
 * @date 2025-07-29
 * 
 * This file defines the AUTOSAR Software Component interface for the
 * Electronic Power Steering (EPS) system according to AUTOSAR R4.4 standards.
 * 
 * AUTOSAR SWC: EPS_SWC
 * Component Type: Application Software Component
 * ASIL Level: ASIL D (decomposed)
 * 
 * Requirements Traceability:
 * - EPS-FR-100: AUTOSAR architecture compliance
 * - EPS-SR-038: Software partitioning
 * - EPS-SR-040: Diverse software channels
 */

#ifndef EPS_SWC_H
#define EPS_SWC_H

/*******************************************************************************
 * AUTOSAR Standard Types
 ******************************************************************************/
#include "Std_Types.h"
#include "Rte_Type.h"

/*******************************************************************************
 * AUTOSAR Component Specific Types
 ******************************************************************************/

/* EPS System Operating Modes - AUTOSAR Enumeration */
typedef uint8 EPS_OperatingMode_T;
#define EPS_MODE_INIT           ((EPS_OperatingMode_T)0U)
#define EPS_MODE_NORMAL         ((EPS_OperatingMode_T)1U)
#define EPS_MODE_DEGRADED       ((EPS_OperatingMode_T)2U)
#define EPS_MODE_FAIL_SAFE      ((EPS_OperatingMode_T)3U)
#define EPS_MODE_SLEEP          ((EPS_OperatingMode_T)4U)

/* EPS System Status - AUTOSAR Enumeration */
typedef uint8 EPS_SystemStatus_T;
#define EPS_STATUS_INITIALIZING ((EPS_SystemStatus_T)0U)
#define EPS_STATUS_READY        ((EPS_SystemStatus_T)1U)
#define EPS_STATUS_ACTIVE       ((EPS_SystemStatus_T)2U)
#define EPS_STATUS_DEGRADED     ((EPS_SystemStatus_T)3U)
#define EPS_STATUS_FAULT        ((EPS_SystemStatus_T)4U)
#define EPS_STATUS_SLEEP        ((EPS_SystemStatus_T)5U)

/* EPS Sensor Data Structure - AUTOSAR Complex Type */
typedef struct {
    float32 DriverTorque_Nm;        /* Driver input torque [Nm] */
    float32 SteeringAngle_Deg;      /* Steering wheel angle [deg] */
    float32 SteeringVelocity_DegS;  /* Steering angular velocity [deg/s] */
    float32 VehicleSpeed_KmH;       /* Vehicle speed [km/h] */
    float32 MotorPosition_Deg;      /* Motor rotor position [deg] */
    float32 MotorVelocity_Rpm;      /* Motor speed [rpm] */
    float32 EcuTemperature_DegC;    /* ECU temperature [°C] */
    float32 MotorTemperature_DegC;  /* Motor temperature [°C] */
    uint32 Timestamp_Ms;            /* Data timestamp [ms] */
    boolean DataValid;              /* Data validity flag */
} EPS_SensorData_T;

/* EPS Assistance Parameters - AUTOSAR Complex Type */
typedef struct {
    float32 BaseAssistance_Nm;      /* Base assistance torque [Nm] */
    float32 ReturnToCenter_Nm;      /* Return-to-center torque [Nm] */
    float32 Damping_Nm;             /* Damping torque [Nm] */
    float32 TotalAssistance_Nm;     /* Total assistance torque [Nm] */
    float32 SpeedFactor;            /* Speed-based scaling factor */
    uint32 CalculationTimestamp_Ms; /* Calculation timestamp [ms] */
    boolean SafetyLimited;          /* Safety limiting applied flag */
    boolean RateLimited;            /* Rate limiting applied flag */
    boolean OscillationDetected;    /* Oscillation detection flag */
} EPS_AssistanceParams_T;

/* EPS Motor Command - AUTOSAR Complex Type */
typedef struct {
    float32 TargetTorque_Nm;        /* Target motor torque [Nm] */
    float32 CurrentLimit_A;         /* Motor current limit [A] */
    uint16 PwmDutyCycle_U[3];       /* PWM duty cycles for 3 phases */
    boolean Enable;                 /* Motor enable flag */
    uint32 CommandTimestamp_Ms;     /* Command timestamp [ms] */
} EPS_MotorCommand_T;

/* EPS System State - AUTOSAR Complex Type */
typedef struct {
    EPS_OperatingMode_T OperatingMode;
    EPS_SystemStatus_T SystemStatus;
    uint32 SystemUptime_Ms;
    uint32 FaultCount;
    uint32 LastFaultTime_Ms;
    boolean ManualSteeringAvailable;
    boolean AssistanceEnabled;
} EPS_SystemState_T;

/* EPS Performance Data - AUTOSAR Complex Type */
typedef struct {
    uint32 LastResponseTime_Ms;
    uint32 MaxResponseTime_Ms;
    float32 CurrentPowerConsumption_W;
    float32 MaxPowerConsumption_W;
    float32 EcuTemperature_DegC;
    float32 MotorTemperature_DegC;
    uint32 SystemUptime_Ms;
    uint32 TotalSteeringCycles;
} EPS_PerformanceData_T;

/*******************************************************************************
 * AUTOSAR Port Interface Definitions
 ******************************************************************************/

/* Sender-Receiver Interface: EPS_SensorData_IF */
typedef struct {
    EPS_SensorData_T SensorData;
} EPS_SensorData_IF_T;

/* Sender-Receiver Interface: EPS_MotorCommand_IF */
typedef struct {
    EPS_MotorCommand_T MotorCommand;
} EPS_MotorCommand_IF_T;

/* Sender-Receiver Interface: EPS_SystemState_IF */
typedef struct {
    EPS_SystemState_T SystemState;
} EPS_SystemState_IF_T;

/* Client-Server Interface: EPS_Calibration_IF */
typedef struct {
    Std_ReturnType (*ReadCalibrationData)(uint16 ParameterId, float32* Value);
    Std_ReturnType (*WriteCalibrationData)(uint16 ParameterId, float32 Value);
    Std_ReturnType (*ResetToDefault)(void);
} EPS_Calibration_IF_T;

/* Client-Server Interface: EPS_Diagnostics_IF */
typedef struct {
    Std_ReturnType (*GetDTC)(uint16* DtcCode, uint8* DtcStatus);
    Std_ReturnType (*ClearDTC)(uint16 DtcCode);
    Std_ReturnType (*GetSystemInfo)(EPS_SystemState_T* SystemState);
    Std_ReturnType (*PerformSelfTest)(uint8* TestResult);
} EPS_Diagnostics_IF_T;

/*******************************************************************************
 * AUTOSAR Runnable Entity Prototypes
 ******************************************************************************/

/**
 * @brief EPS System Initialization Runnable
 * @details AUTOSAR Runnable Entity executed during system initialization
 * 
 * Trigger: Init Event
 * Period: Single execution
 * WCET: 50ms
 * 
 * Requirements: EPS-FR-033, EPS-SR-084
 */
FUNC(void, EPS_SWC_CODE) EPS_Init_Runnable(void);

/**
 * @brief EPS Main Cyclic Task Runnable
 * @details AUTOSAR Runnable Entity for main EPS control loop
 * 
 * Trigger: Timing Event
 * Period: 1ms
 * WCET: 0.8ms
 * 
 * Requirements: EPS-FR-019, EPS-PR-014, EPS-SR-041
 */
FUNC(void, EPS_SWC_CODE) EPS_MainTask_Runnable(void);

/**
 * @brief EPS Safety Monitor Runnable
 * @details AUTOSAR Runnable Entity for safety monitoring
 * 
 * Trigger: Timing Event
 * Period: 10ms
 * WCET: 2ms
 * 
 * Requirements: EPS-SR-047, EPS-DR-003
 */
FUNC(void, EPS_SWC_CODE) EPS_SafetyMonitor_Runnable(void);

/**
 * @brief EPS Diagnostic Task Runnable
 * @details AUTOSAR Runnable Entity for diagnostic functions
 * 
 * Trigger: Timing Event
 * Period: 100ms
 * WCET: 5ms
 * 
 * Requirements: EPS-DR-089, EPS-DR-093
 */
FUNC(void, EPS_SWC_CODE) EPS_DiagnosticTask_Runnable(void);

/**
 * @brief EPS Mode Request Handler Runnable
 * @details AUTOSAR Runnable Entity for mode change requests
 * 
 * Trigger: Data Received Event
 * Period: Event-driven
 * WCET: 1ms
 * 
 * Requirements: EPS-FR-033 to EPS-FR-042
 */
FUNC(void, EPS_SWC_CODE) EPS_ModeRequest_Runnable(void);

/**
 * @brief EPS Shutdown Runnable
 * @details AUTOSAR Runnable Entity for system shutdown
 * 
 * Trigger: Shutdown Event
 * Period: Single execution
 * WCET: 10ms
 * 
 * Requirements: EPS-FR-042, EPS-ER-043
 */
FUNC(void, EPS_SWC_CODE) EPS_Shutdown_Runnable(void);

/*******************************************************************************
 * AUTOSAR Inter-Runnable Variable Definitions
 ******************************************************************************/

/* Inter-Runnable Variables for data sharing between runnables */
extern VAR(EPS_SensorData_T, EPS_SWC_VAR) EPS_IRV_SensorData;
extern VAR(EPS_AssistanceParams_T, EPS_SWC_VAR) EPS_IRV_AssistanceParams;
extern VAR(EPS_MotorCommand_T, EPS_SWC_VAR) EPS_IRV_MotorCommand;
extern VAR(EPS_SystemState_T, EPS_SWC_VAR) EPS_IRV_SystemState;

/*******************************************************************************
 * AUTOSAR Memory Sections
 ******************************************************************************/

#define EPS_SWC_START_SEC_CODE
#include "EPS_SWC_MemMap.h"

/* Function prototypes will be included here */

#define EPS_SWC_STOP_SEC_CODE
#include "EPS_SWC_MemMap.h"

#define EPS_SWC_START_SEC_VAR_INIT_UNSPECIFIED
#include "EPS_SWC_MemMap.h"

/* Initialized variables will be included here */

#define EPS_SWC_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "EPS_SWC_MemMap.h"

#define EPS_SWC_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "EPS_SWC_MemMap.h"

/* Uninitialized variables will be included here */

#define EPS_SWC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "EPS_SWC_MemMap.h"

#endif /* EPS_SWC_H */