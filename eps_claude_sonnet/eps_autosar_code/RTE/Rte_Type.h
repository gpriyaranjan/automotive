/**
 * @file Rte_Type.h
 * @brief AUTOSAR RTE Type Definitions
 * @version 4.4.0
 * @date 2025-07-29
 * 
 * This file contains the AUTOSAR RTE type definitions according to
 * AUTOSAR R4.4 specification for the EPS system.
 * 
 * AUTOSAR Module: RTE Types
 * Generated for: EPS System
 */

#ifndef RTE_TYPE_H
#define RTE_TYPE_H

/*******************************************************************************
 * AUTOSAR Includes
 ******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
 * RTE Version Information
 ******************************************************************************/
#define RTE_TYPE_VENDOR_ID                 (1U)
#define RTE_TYPE_MODULE_ID                 (2U)
#define RTE_TYPE_AR_RELEASE_MAJOR_VERSION  (4U)
#define RTE_TYPE_AR_RELEASE_MINOR_VERSION  (4U)
#define RTE_TYPE_AR_RELEASE_REVISION_VERSION (0U)
#define RTE_TYPE_SW_MAJOR_VERSION          (1U)
#define RTE_TYPE_SW_MINOR_VERSION          (0U)
#define RTE_TYPE_SW_PATCH_VERSION          (0U)

/*******************************************************************************
 * RTE Return Values
 ******************************************************************************/
#define RTE_E_OK                    ((Std_ReturnType)0x00U)
#define RTE_E_INVALID               ((Std_ReturnType)0x01U)
#define RTE_E_NO_DATA               ((Std_ReturnType)0x02U)
#define RTE_E_TRANSMIT_ACK          ((Std_ReturnType)0x03U)
#define RTE_E_NEVER_RECEIVED        ((Std_ReturnType)0x04U)
#define RTE_E_UNCONNECTED           ((Std_ReturnType)0x05U)
#define RTE_E_IN_EXCLUSIVE_AREA     ((Std_ReturnType)0x06U)
#define RTE_E_SEG_FAULT             ((Std_ReturnType)0x07U)
#define RTE_E_OUT_OF_RANGE          ((Std_ReturnType)0x08U)
#define RTE_E_SERIALIZATION_ERROR   ((Std_ReturnType)0x09U)
#define RTE_E_HARD_TRANSFORMER_ERROR ((Std_ReturnType)0x0AU)
#define RTE_E_SOFT_TRANSFORMER_ERROR ((Std_ReturnType)0x0BU)
#define RTE_E_LOST_DATA             ((Std_ReturnType)0x40U)
#define RTE_E_MAX_AGE_EXCEEDED      ((Std_ReturnType)0x41U)

/*******************************************************************************
 * RTE Application Error Codes
 ******************************************************************************/
#define RTE_E_TIMEOUT               ((Std_ReturnType)0x80U)
#define RTE_E_LIMIT                 ((Std_ReturnType)0x81U)
#define RTE_E_NO_RESPONSE           ((Std_ReturnType)0x82U)
#define RTE_E_FAULT                 ((Std_ReturnType)0x83U)

/*******************************************************************************
 * RTE Mode Declaration Groups
 ******************************************************************************/

/* EPS Operating Mode Group */
typedef uint8 Rte_ModeType_EPS_OperatingMode;
#define RTE_MODE_EPS_OperatingMode_INIT         ((Rte_ModeType_EPS_OperatingMode)0U)
#define RTE_MODE_EPS_OperatingMode_NORMAL       ((Rte_ModeType_EPS_OperatingMode)1U)
#define RTE_MODE_EPS_OperatingMode_DEGRADED     ((Rte_ModeType_EPS_OperatingMode)2U)
#define RTE_MODE_EPS_OperatingMode_FAIL_SAFE    ((Rte_ModeType_EPS_OperatingMode)3U)
#define RTE_MODE_EPS_OperatingMode_SLEEP        ((Rte_ModeType_EPS_OperatingMode)4U)
#define RTE_TRANSITION_EPS_OperatingMode        ((Rte_ModeType_EPS_OperatingMode)255U)

/* EPS System Status Group */
typedef uint8 Rte_ModeType_EPS_SystemStatus;
#define RTE_MODE_EPS_SystemStatus_INITIALIZING  ((Rte_ModeType_EPS_SystemStatus)0U)
#define RTE_MODE_EPS_SystemStatus_READY         ((Rte_ModeType_EPS_SystemStatus)1U)
#define RTE_MODE_EPS_SystemStatus_ACTIVE        ((Rte_ModeType_EPS_SystemStatus)2U)
#define RTE_MODE_EPS_SystemStatus_DEGRADED      ((Rte_ModeType_EPS_SystemStatus)3U)
#define RTE_MODE_EPS_SystemStatus_FAULT         ((Rte_ModeType_EPS_SystemStatus)4U)
#define RTE_MODE_EPS_SystemStatus_SLEEP         ((Rte_ModeType_EPS_SystemStatus)5U)
#define RTE_TRANSITION_EPS_SystemStatus         ((Rte_ModeType_EPS_SystemStatus)255U)

/*******************************************************************************
 * RTE Primitive Types
 ******************************************************************************/

/* AUTOSAR primitive types already defined in Std_Types.h */

/*******************************************************************************
 * RTE Array Types
 ******************************************************************************/

/* PWM Duty Cycle Array */
typedef uint16 Rte_Array_PwmDutyCycle_3[3];

/* Oscillation Buffer Array */
typedef float32 Rte_Array_OscillationBuffer_10[10];

/*******************************************************************************
 * RTE Enumeration Types
 ******************************************************************************/

/* DTC Status Enumeration */
typedef uint8 Rte_DTC_StatusType;
#define RTE_DTC_STATUS_PASSED           ((Rte_DTC_StatusType)0x00U)
#define RTE_DTC_STATUS_FAILED           ((Rte_DTC_StatusType)0x01U)
#define RTE_DTC_STATUS_PENDING          ((Rte_DTC_StatusType)0x02U)
#define RTE_DTC_STATUS_CONFIRMED        ((Rte_DTC_StatusType)0x03U)

/* Sensor Validation Result */
typedef uint8 Rte_SensorValidationResult;
#define RTE_SENSOR_VALID                ((Rte_SensorValidationResult)0x00U)
#define RTE_SENSOR_INVALID              ((Rte_SensorValidationResult)0x01U)
#define RTE_SENSOR_OUT_OF_RANGE         ((Rte_SensorValidationResult)0x02U)
#define RTE_SENSOR_PLAUSIBILITY_ERROR   ((Rte_SensorValidationResult)0x03U)

/*******************************************************************************
 * RTE Record Types (Complex Data Types)
 ******************************************************************************/

/* Forward declarations for complex types defined in SWC headers */
struct EPS_SensorData_T;
struct EPS_AssistanceParams_T;
struct EPS_MotorCommand_T;
struct EPS_SystemState_T;
struct EPS_PerformanceData_T;

/*******************************************************************************
 * RTE Calibration Parameter Types
 ******************************************************************************/

/* Calibration Parameter Structure */
typedef struct {
    uint16 ParameterId;
    float32 Value;
    float32 MinValue;
    float32 MaxValue;
    boolean IsValid;
} Rte_CalibrationParam_T;

/*******************************************************************************
 * RTE Communication Types
 ******************************************************************************/

/* CAN Message Structure */
typedef struct {
    uint32 MessageId;
    uint8 DataLength;
    uint8 Data[8];
    uint32 Timestamp;
} Rte_CanMessage_T;

/* Diagnostic Message Structure */
typedef struct {
    uint16 ServiceId;
    uint8 SubFunction;
    uint16 DataLength;
    uint8* Data;
} Rte_DiagMessage_T;

/*******************************************************************************
 * RTE Signal Quality Types
 ******************************************************************************/

/* Signal Quality Enumeration */
typedef uint8 Rte_SignalQuality_T;
#define RTE_SIGNAL_QUALITY_GOOD         ((Rte_SignalQuality_T)0x00U)
#define RTE_SIGNAL_QUALITY_DEGRADED     ((Rte_SignalQuality_T)0x01U)
#define RTE_SIGNAL_QUALITY_BAD          ((Rte_SignalQuality_T)0x02U)
#define RTE_SIGNAL_QUALITY_INVALID      ((Rte_SignalQuality_T)0x03U)

/*******************************************************************************
 * RTE Transformation Types
 ******************************************************************************/

/* Transformer Configuration */
typedef struct {
    uint8 TransformerId;
    boolean IsEnabled;
    uint32 BufferSize;
} Rte_TransformerConfig_T;

/*******************************************************************************
 * RTE Memory Sections
 ******************************************************************************/

#define RTE_START_SEC_CODE
#include "Rte_MemMap.h"

/* RTE function prototypes will be included here */

#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h"

#define RTE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Rte_MemMap.h"

/* RTE initialized variables will be included here */

#define RTE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Rte_MemMap.h"

#define RTE_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Rte_MemMap.h"

/* RTE uninitialized variables will be included here */

#define RTE_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Rte_MemMap.h"

#endif /* RTE_TYPE_H */