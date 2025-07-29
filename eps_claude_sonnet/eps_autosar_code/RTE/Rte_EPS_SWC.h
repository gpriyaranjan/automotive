/**
 * @file Rte_EPS_SWC.h
 * @brief AUTOSAR RTE Interface for EPS Software Component
 * @version 4.4.0
 * @date 2025-07-29
 * 
 * This file contains the AUTOSAR RTE interface definitions for the
 * Electronic Power Steering (EPS) Software Component according to
 * AUTOSAR R4.4 specification.
 * 
 * AUTOSAR Module: RTE Interface
 * Generated for: EPS_SWC
 */

#ifndef RTE_EPS_SWC_H
#define RTE_EPS_SWC_H

/*******************************************************************************
 * AUTOSAR Includes
 ******************************************************************************/
#include "Rte_Type.h"
#include "EPS_SWC.h"

/*******************************************************************************
 * RTE Version Information
 ******************************************************************************/
#define RTE_EPS_SWC_VENDOR_ID                 (1U)
#define RTE_EPS_SWC_MODULE_ID                 (2U)
#define RTE_EPS_SWC_AR_RELEASE_MAJOR_VERSION  (4U)
#define RTE_EPS_SWC_AR_RELEASE_MINOR_VERSION  (4U)
#define RTE_EPS_SWC_AR_RELEASE_REVISION_VERSION (0U)
#define RTE_EPS_SWC_SW_MAJOR_VERSION          (1U)
#define RTE_EPS_SWC_SW_MINOR_VERSION          (0U)
#define RTE_EPS_SWC_SW_PATCH_VERSION          (0U)

/*******************************************************************************
 * RTE Port Definitions
 ******************************************************************************/

/* Sender-Receiver Ports */
#define RTE_PORT_SensorData                   0U
#define RTE_PORT_MotorCommand                 1U
#define RTE_PORT_SystemState                  2U
#define RTE_PORT_PerformanceData              3U
#define RTE_PORT_ModeRequest                  4U

/* Client-Server Ports */
#define RTE_PORT_PowerManagement              10U
#define RTE_PORT_SafetyManager                11U
#define RTE_PORT_SensorManager                12U
#define RTE_PORT_MotorControl                 13U
#define RTE_PORT_DiagnosticManager            14U

/*******************************************************************************
 * RTE Data Element Definitions
 ******************************************************************************/

/* Data Elements for SensorData Port */
#define RTE_DE_SensorData_SensorData          0U

/* Data Elements for MotorCommand Port */
#define RTE_DE_MotorCommand_MotorCommand      0U

/* Data Elements for SystemState Port */
#define RTE_DE_SystemState_SystemState        0U

/* Data Elements for PerformanceData Port */
#define RTE_DE_PerformanceData_PerformanceData 0U

/* Data Elements for ModeRequest Port */
#define RTE_DE_ModeRequest_ModeRequest        0U

/*******************************************************************************
 * RTE Operation Definitions
 ******************************************************************************/

/* PowerManagement Operations */
#define RTE_OP_PowerManagement_Init           0U
#define RTE_OP_PowerManagement_EnterSleep     1U
#define RTE_OP_PowerManagement_GetConsumption 2U

/* SafetyManager Operations */
#define RTE_OP_SafetyManager_Init             0U
#define RTE_OP_SafetyManager_ResetWatchdog    1U
#define RTE_OP_SafetyManager_MonitorSafety    2U

/* SensorManager Operations */
#define RTE_OP_SensorManager_Init             0U
#define RTE_OP_SensorManager_ValidateData     1U

/* MotorControl Operations */
#define RTE_OP_MotorControl_Init              0U
#define RTE_OP_MotorControl_Disable           1U
#define RTE_OP_MotorControl_DisconnectMotor   2U

/* DiagnosticManager Operations */
#define RTE_OP_DiagnosticManager_SelfTest     0U
#define RTE_OP_DiagnosticManager_SetDTC       1U
#define RTE_OP_DiagnosticManager_GetDTC       2U
#define RTE_OP_DiagnosticManager_UpdateData   3U
#define RTE_OP_DiagnosticManager_SaveData     4U

/*******************************************************************************
 * RTE API Function Prototypes - Sender-Receiver Interface
 ******************************************************************************/

/**
 * @brief Read sensor data from RTE
 * @param data Pointer to sensor data structure
 * @return Std_ReturnType RTE operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_SensorData_SensorData(
    P2VAR(EPS_SensorData_T, AUTOMATIC, RTE_APPL_DATA) data
);

/**
 * @brief Write motor command to RTE
 * @param data Pointer to motor command structure
 * @return Std_ReturnType RTE operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_MotorCommand_MotorCommand(
    P2CONST(EPS_MotorCommand_T, AUTOMATIC, RTE_APPL_DATA) data
);

/**
 * @brief Write system state to RTE
 * @param data Pointer to system state structure
 * @return Std_ReturnType RTE operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_SystemState_SystemState(
    P2CONST(EPS_SystemState_T, AUTOMATIC, RTE_APPL_DATA) data
);

/**
 * @brief Write performance data to RTE
 * @param data Pointer to performance data structure
 * @return Std_ReturnType RTE operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_PerformanceData_PerformanceData(
    P2CONST(EPS_PerformanceData_T, AUTOMATIC, RTE_APPL_DATA) data
);

/**
 * @brief Read mode request from RTE
 * @param mode Pointer to mode request
 * @return Std_ReturnType RTE operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_ModeRequest_ModeRequest(
    P2VAR(EPS_OperatingMode_T, AUTOMATIC, RTE_APPL_DATA) mode
);

/*******************************************************************************
 * RTE API Function Prototypes - Client-Server Interface
 ******************************************************************************/

/**
 * @brief Initialize power management
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_PowerManagement_Init(void);

/**
 * @brief Enter sleep mode
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_PowerManagement_EnterSleep(void);

/**
 * @brief Get power consumption
 * @param consumption Pointer to power consumption value
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_PowerManagement_GetConsumption(
    P2VAR(float32, AUTOMATIC, RTE_APPL_DATA) consumption
);

/**
 * @brief Initialize safety manager
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SafetyManager_Init(void);

/**
 * @brief Reset watchdog timer
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SafetyManager_ResetWatchdog(void);

/**
 * @brief Monitor safety mechanisms
 * @param status Pointer to safety status
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SafetyManager_MonitorSafety(
    P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) status
);

/**
 * @brief Initialize sensor manager
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SensorManager_Init(void);

/**
 * @brief Validate sensor data
 * @param data Pointer to sensor data
 * @return Std_ReturnType Validation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SensorManager_ValidateData(
    P2CONST(EPS_SensorData_T, AUTOMATIC, RTE_APPL_DATA) data
);

/**
 * @brief Initialize motor control
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_MotorControl_Init(void);

/**
 * @brief Disable motor control
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_MotorControl_Disable(void);

/**
 * @brief Disconnect motor for safety
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_MotorControl_DisconnectMotor(void);

/**
 * @brief Perform diagnostic self-test
 * @return Std_ReturnType Test result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_DiagnosticManager_SelfTest(void);

/**
 * @brief Set diagnostic trouble code
 * @param dtcCode DTC code
 * @param dtcStatus DTC status
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_DiagnosticManager_SetDTC(
    VAR(uint16, AUTOMATIC) dtcCode,
    VAR(uint8, AUTOMATIC) dtcStatus
);

/**
 * @brief Get diagnostic trouble code
 * @param dtcCode Pointer to DTC code
 * @param dtcStatus Pointer to DTC status
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_DiagnosticManager_GetDTC(
    P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) dtcCode,
    P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) dtcStatus
);

/**
 * @brief Update diagnostic data
 * @param sensorData Pointer to sensor data
 * @param assistanceParams Pointer to assistance parameters
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_DiagnosticManager_UpdateData(
    P2CONST(EPS_SensorData_T, AUTOMATIC, RTE_APPL_DATA) sensorData,
    P2CONST(EPS_AssistanceParams_T, AUTOMATIC, RTE_APPL_DATA) assistanceParams
);

/**
 * @brief Save diagnostic data
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_DiagnosticManager_SaveData(void);

/*******************************************************************************
 * RTE API Function Prototypes - Mode Management
 ******************************************************************************/

/**
 * @brief Get current operating mode
 * @return Rte_ModeType_EPS_OperatingMode Current mode
 */
FUNC(Rte_ModeType_EPS_OperatingMode, RTE_CODE) Rte_Mode_OperatingMode_currentMode(void);

/**
 * @brief Switch to requested operating mode
 * @param mode Requested mode
 * @return Std_ReturnType Mode switch result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_OperatingMode_currentMode(
    VAR(Rte_ModeType_EPS_OperatingMode, AUTOMATIC) mode
);

/**
 * @brief Get current system status mode
 * @return Rte_ModeType_EPS_SystemStatus Current status
 */
FUNC(Rte_ModeType_EPS_SystemStatus, RTE_CODE) Rte_Mode_SystemStatus_currentStatus(void);

/**
 * @brief Switch to requested system status
 * @param status Requested status
 * @return Std_ReturnType Status switch result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_SystemStatus_currentStatus(
    VAR(Rte_ModeType_EPS_SystemStatus, AUTOMATIC) status
);

/*******************************************************************************
 * RTE API Function Prototypes - Calibration Interface
 ******************************************************************************/

/**
 * @brief Read calibration parameter
 * @param parameterId Parameter ID
 * @param value Pointer to parameter value
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Calibration_ReadParameter(
    VAR(uint16, AUTOMATIC) parameterId,
    P2VAR(float32, AUTOMATIC, RTE_APPL_DATA) value
);

/**
 * @brief Write calibration parameter
 * @param parameterId Parameter ID
 * @param value Parameter value
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Calibration_WriteParameter(
    VAR(uint16, AUTOMATIC) parameterId,
    VAR(float32, AUTOMATIC) value
);

/*******************************************************************************
 * RTE API Function Prototypes - Inter-Runnable Variables
 ******************************************************************************/

/**
 * @brief Read Inter-Runnable Variable
 * @param data Pointer to data
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_IrvRead_SensorData(
    P2VAR(EPS_SensorData_T, AUTOMATIC, RTE_APPL_DATA) data
);

/**
 * @brief Write Inter-Runnable Variable
 * @param data Pointer to data
 * @return Std_ReturnType Operation result
 */
FUNC(Std_ReturnType, RTE_CODE) Rte_IrvWrite_SensorData(
    P2CONST(EPS_SensorData_T, AUTOMATIC, RTE_APPL_DATA) data
);

/*******************************************************************************
 * RTE Memory Sections
 ******************************************************************************/

#define RTE_START_SEC_CODE
#include "Rte_MemMap.h"

/* RTE function implementations will be included here */

#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h"

#endif /* RTE_EPS_SWC_H */