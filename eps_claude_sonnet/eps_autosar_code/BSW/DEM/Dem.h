/**
 * @file Dem.h
 * @brief AUTOSAR Diagnostic Event Manager Header
 * @version 4.4.0
 * @date 2025-07-29
 * 
 * This file contains the AUTOSAR Diagnostic Event Manager (DEM) interface
 * definitions according to AUTOSAR R4.4 specification for the EPS system.
 * 
 * AUTOSAR Module: DEM
 * Module ID: 54
 * Vendor ID: 1
 */

#ifndef DEM_H
#define DEM_H

/*******************************************************************************
 * AUTOSAR Includes
 ******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
 * Version Information
 ******************************************************************************/
#define DEM_VENDOR_ID                 (1U)
#define DEM_MODULE_ID                 (54U)
#define DEM_AR_RELEASE_MAJOR_VERSION  (4U)
#define DEM_AR_RELEASE_MINOR_VERSION  (4U)
#define DEM_AR_RELEASE_REVISION_VERSION (0U)
#define DEM_SW_MAJOR_VERSION          (1U)
#define DEM_SW_MINOR_VERSION          (0U)
#define DEM_SW_PATCH_VERSION          (0U)

/*******************************************************************************
 * DEM Configuration Parameters
 ******************************************************************************/
#define DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY     (50U)
#define DEM_MAX_NUMBER_EVENT_ENTRY_SECONDARY   (20U)
#define DEM_MAX_NUMBER_EVENT_ENTRY_MIRROR      (10U)
#define DEM_MAX_NUMBER_EVENT_ENTRY_PERMANENT   (10U)

/*******************************************************************************
 * DEM Event ID Definitions
 ******************************************************************************/
typedef uint16 Dem_EventIdType;

/* EPS System Event IDs */
#define DEM_EVENT_EPS_TORQUE_SENSOR_FAULT       ((Dem_EventIdType)0x1001U)
#define DEM_EVENT_EPS_ANGLE_SENSOR_FAULT        ((Dem_EventIdType)0x1002U)
#define DEM_EVENT_EPS_MOTOR_FAULT               ((Dem_EventIdType)0x2001U)
#define DEM_EVENT_EPS_POWER_SUPPLY_FAULT        ((Dem_EventIdType)0x3001U)
#define DEM_EVENT_EPS_COMMUNICATION_FAULT       ((Dem_EventIdType)0x4001U)
#define DEM_EVENT_EPS_EXCESSIVE_ASSISTANCE      ((Dem_EventIdType)0x5001U)
#define DEM_EVENT_EPS_DIRECTION_MISMATCH        ((Dem_EventIdType)0x5002U)
#define DEM_EVENT_EPS_OSCILLATION_DETECTED      ((Dem_EventIdType)0x5003U)
#define DEM_EVENT_EPS_SLOW_RESPONSE             ((Dem_EventIdType)0x6001U)
#define DEM_EVENT_EPS_OVERTEMPERATURE           ((Dem_EventIdType)0x7001U)

/*******************************************************************************
 * DEM Event Status Definitions
 ******************************************************************************/
typedef uint8 Dem_EventStatusType;

#define DEM_EVENT_STATUS_PASSED                 ((Dem_EventStatusType)0x00U)
#define DEM_EVENT_STATUS_FAILED                 ((Dem_EventStatusType)0x01U)
#define DEM_EVENT_STATUS_PREPASSED              ((Dem_EventStatusType)0x02U)
#define DEM_EVENT_STATUS_PREFAILED             ((Dem_EventStatusType)0x03U)

/*******************************************************************************
 * DEM UDS Status Byte Definitions
 ******************************************************************************/
typedef uint8 Dem_UdsStatusByteType;

#define DEM_UDS_STATUS_TF                      ((Dem_UdsStatusByteType)0x01U)  /* Test Failed */
#define DEM_UDS_STATUS_TFTOC                   ((Dem_UdsStatusByteType)0x02U)  /* Test Failed This Operation Cycle */
#define DEM_UDS_STATUS_PDTC                    ((Dem_UdsStatusByteType)0x04U)  /* Pending DTC */
#define DEM_UDS_STATUS_CDTC                    ((Dem_UdsStatusByteType)0x08U)  /* Confirmed DTC */
#define DEM_UDS_STATUS_TNCSLC                  ((Dem_UdsStatusByteType)0x10U)  /* Test Not Completed Since Last Clear */
#define DEM_UDS_STATUS_TFSLC                   ((Dem_UdsStatusByteType)0x20U)  /* Test Failed Since Last Clear */
#define DEM_UDS_STATUS_TNCTOC                  ((Dem_UdsStatusByteType)0x40U)  /* Test Not Completed This Operation Cycle */
#define DEM_UDS_STATUS_WIR                     ((Dem_UdsStatusByteType)0x80U)  /* Warning Indicator Requested */

/*******************************************************************************
 * DEM Operation Cycle Definitions
 ******************************************************************************/
typedef uint8 Dem_OperationCycleIdType;

#define DEM_OPCYC_POWER                         ((Dem_OperationCycleIdType)0x00U)
#define DEM_OPCYC_IGNITION                      ((Dem_OperationCycleIdType)0x01U)
#define DEM_OPCYC_WARMUP                        ((Dem_OperationCycleIdType)0x02U)

typedef uint8 Dem_OperationCycleStateType;

#define DEM_CYCLE_STATE_START                   ((Dem_OperationCycleStateType)0x00U)
#define DEM_CYCLE_STATE_END                     ((Dem_OperationCycleStateType)0x01U)

/*******************************************************************************
 * DEM Debouncing Definitions
 ******************************************************************************/
typedef sint8 Dem_DebounceCounterBasedClassType;

#define DEM_DEBOUNCE_COUNTER_BASED_CLASS_1      ((Dem_DebounceCounterBasedClassType)1)
#define DEM_DEBOUNCE_COUNTER_BASED_CLASS_2      ((Dem_DebounceCounterBasedClassType)2)
#define DEM_DEBOUNCE_COUNTER_BASED_CLASS_3      ((Dem_DebounceCounterBasedClassType)3)

/*******************************************************************************
 * DEM Severity Definitions
 ******************************************************************************/
typedef uint8 Dem_DTCSeverityType;

#define DEM_SEVERITY_NO_SEVERITY                ((Dem_DTCSeverityType)0x00U)
#define DEM_SEVERITY_WWHOBD_CLASS_NO_CLASS      ((Dem_DTCSeverityType)0x01U)
#define DEM_SEVERITY_WWHOBD_CLASS_A             ((Dem_DTCSeverityType)0x02U)
#define DEM_SEVERITY_WWHOBD_CLASS_B1            ((Dem_DTCSeverityType)0x04U)
#define DEM_SEVERITY_WWHOBD_CLASS_B2            ((Dem_DTCSeverityType)0x08U)
#define DEM_SEVERITY_WWHOBD_CLASS_C             ((Dem_DTCSeverityType)0x10U)
#define DEM_SEVERITY_MAINTENANCE_ONLY           ((Dem_DTCSeverityType)0x20U)
#define DEM_SEVERITY_CHECK_AT_NEXT_HALT         ((Dem_DTCSeverityType)0x40U)
#define DEM_SEVERITY_CHECK_IMMEDIATELY          ((Dem_DTCSeverityType)0x80U)

/*******************************************************************************
 * DEM API Function Prototypes
 ******************************************************************************/

/**
 * @brief Initialize the Diagnostic Event Manager
 * @param ConfigPtr Pointer to configuration structure
 * 
 * Requirements: EPS-DR-001
 */
FUNC(void, DEM_CODE) Dem_Init(
    P2CONST(void, AUTOMATIC, DEM_APPL_CONST) ConfigPtr
);

/**
 * @brief Shutdown the Diagnostic Event Manager
 * 
 * Requirements: EPS-DR-002
 */
FUNC(void, DEM_CODE) Dem_Shutdown(void);

/**
 * @brief Report an event status to DEM
 * @param EventId Event identifier
 * @param EventStatus Event status (PASSED/FAILED/PREPASSED/PREFAILED)
 * @return Std_ReturnType Operation result
 * 
 * Requirements: EPS-DR-031, EPS-SR-047
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(
    VAR(Dem_EventIdType, AUTOMATIC) EventId,
    VAR(Dem_EventStatusType, AUTOMATIC) EventStatus
);

/**
 * @brief Reset event status to initial state
 * @param EventId Event identifier
 * @return Std_ReturnType Operation result
 * 
 * Requirements: EPS-DR-032
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_ResetEventStatus(
    VAR(Dem_EventIdType, AUTOMATIC) EventId
);

/**
 * @brief Get current event status
 * @param EventId Event identifier
 * @param EventStatusExtended Pointer to extended event status
 * @return Std_ReturnType Operation result
 * 
 * Requirements: EPS-DR-033
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventStatus(
    VAR(Dem_EventIdType, AUTOMATIC) EventId,
    P2VAR(Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA) EventStatusExtended
);

/**
 * @brief Get event failed status
 * @param EventId Event identifier
 * @param EventFailed Pointer to event failed status
 * @return Std_ReturnType Operation result
 * 
 * Requirements: EPS-DR-034
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventFailed(
    VAR(Dem_EventIdType, AUTOMATIC) EventId,
    P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) EventFailed
);

/**
 * @brief Get event tested status
 * @param EventId Event identifier
 * @param EventTested Pointer to event tested status
 * @return Std_ReturnType Operation result
 * 
 * Requirements: EPS-DR-035
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventTested(
    VAR(Dem_EventIdType, AUTOMATIC) EventId,
    P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) EventTested
);

/**
 * @brief Set operation cycle state
 * @param OperationCycleId Operation cycle identifier
 * @param CycleState Cycle state (START/END)
 * @return Std_ReturnType Operation result
 * 
 * Requirements: EPS-DR-036
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_SetOperationCycleState(
    VAR(Dem_OperationCycleIdType, AUTOMATIC) OperationCycleId,
    VAR(Dem_OperationCycleStateType, AUTOMATIC) CycleState
);

/**
 * @brief Get DTC of an event
 * @param EventId Event identifier
 * @param DTCFormat DTC format
 * @param DTCOfEvent Pointer to DTC value
 * @return Std_ReturnType Operation result
 * 
 * Requirements: EPS-DR-037
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCOfEvent(
    VAR(Dem_EventIdType, AUTOMATIC) EventId,
    VAR(uint8, AUTOMATIC) DTCFormat,
    P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA) DTCOfEvent
);

/**
 * @brief Clear DTC information
 * @param DTC DTC value
 * @param DTCFormat DTC format
 * @param DTCOrigin DTC origin
 * @return Std_ReturnType Operation result
 * 
 * Requirements: EPS-DR-038
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC(
    VAR(uint32, AUTOMATIC) DTC,
    VAR(uint8, AUTOMATIC) DTCFormat,
    VAR(uint8, AUTOMATIC) DTCOrigin
);

/**
 * @brief Main function for DEM processing
 * 
 * Requirements: EPS-DR-089
 */
FUNC(void, DEM_CODE) Dem_MainFunction(void);

/*******************************************************************************
 * DEM Configuration Structure
 ******************************************************************************/
typedef struct {
    Dem_EventIdType EventId;
    uint32 DTC;
    Dem_DTCSeverityType Severity;
    boolean ImmediateStorage;
    uint8 DebounceCounterFailedThreshold;
    uint8 DebounceCounterPassedThreshold;
} Dem_EventParameterType;

typedef struct {
    uint16 NumberOfEvents;
    P2CONST(Dem_EventParameterType, AUTOMATIC, DEM_CONST) EventParameters;
} Dem_ConfigType;

/*******************************************************************************
 * DEM Memory Sections
 ******************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"

/* DEM function implementations will be included here */

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

/* DEM initialized variables will be included here */

#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

/* DEM uninitialized variables will be included here */

#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#define DEM_START_SEC_CONST_UNSPECIFIED
#include "Dem_MemMap.h"

/* DEM constants will be included here */

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "Dem_MemMap.h"

#endif /* DEM_H */