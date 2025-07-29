/**
 * @file EPS_SWC.c
 * @brief AUTOSAR Software Component Implementation for Electronic Power Steering
 * @version 1.0
 * @date 2025-07-29
 * 
 * This file implements the AUTOSAR Software Component for the
 * Electronic Power Steering (EPS) system according to AUTOSAR R4.4 standards.
 * 
 * AUTOSAR SWC: EPS_SWC
 * Component Type: Application Software Component
 * ASIL Level: ASIL D (decomposed)
 * 
 * Requirements Traceability:
 * - EPS-FR-001 to EPS-FR-105: Functional Requirements
 * - EPS-SR-001 to EPS-SR-098: Safety Requirements
 * - EPS-PR-001 to EPS-PR-128: Performance Requirements
 */

/*******************************************************************************
 * AUTOSAR Includes
 ******************************************************************************/
#include "EPS_SWC.h"
#include "Rte_EPS_SWC.h"

/*******************************************************************************
 * Local Constants
 ******************************************************************************/

/* System Constants - Based on Performance Requirements */
#define EPS_MAX_ASSISTANCE_TORQUE_NM        (8.0F)    /* Nm - EPS-PR-002 */
#define EPS_MIN_TORQUE_THRESHOLD_NM         (0.1F)    /* Nm - EPS-PR-003 */
#define EPS_MAX_RESPONSE_TIME_MS            (50U)     /* ms - EPS-PR-014 */
#define EPS_SYSTEM_CYCLE_TIME_MS            (1U)      /* ms - EPS-PR-019 */
#define EPS_WATCHDOG_TIMEOUT_MS             (100U)    /* ms - EPS-SR-041 */

/* Speed-Sensitive Steering Constants - EPS-PR-040 */
#define EPS_LOW_SPEED_THRESHOLD_KMH         (10.0F)   /* km/h */
#define EPS_HIGH_SPEED_THRESHOLD_KMH        (100.0F)  /* km/h */
#define EPS_MIN_ASSISTANCE_FACTOR           (0.3F)    /* 30% at high speeds */

/* Control Parameters */
#define EPS_BASE_ASSISTANCE_GAIN            (1.5F)
#define EPS_RETURN_TO_CENTER_GAIN           (0.02F)   /* Nm/deg - EPS-PR-034 */
#define EPS_RETURN_TO_CENTER_THRESHOLD_NM   (1.0F)    /* Nm */
#define EPS_DAMPING_COEFFICIENT             (0.05F)   /* Nm*s/deg - EPS-PR-037 */
#define EPS_SPEED_RTC_FACTOR                (0.01F)
#define EPS_SPEED_DAMPING_FACTOR            (0.02F)

/* Safety Limits */
#define EPS_MAX_ASSISTANCE_RATE_NMS         (10.0F)   /* Nm/s - EPS-FR-005 */
#define EPS_DEGRADED_MAX_TORQUE_NM          (4.0F)    /* Nm */
#define EPS_OSCILLATION_BUFFER_SIZE         (10U)
#define EPS_TORQUE_CHANGE_THRESHOLD_NM      (0.5F)    /* Nm */

/*******************************************************************************
 * AUTOSAR Memory Sections
 ******************************************************************************/

#define EPS_SWC_START_SEC_VAR_INIT_UNSPECIFIED
#include "EPS_SWC_MemMap.h"

/* Global system state variables */
static VAR(EPS_SystemState_T, EPS_SWC_VAR) EPS_SystemState = {
    .OperatingMode = EPS_MODE_INIT,
    .SystemStatus = EPS_STATUS_INITIALIZING,
    .SystemUptime_Ms = 0U,
    .FaultCount = 0U,
    .LastFaultTime_Ms = 0U,
    .ManualSteeringAvailable = TRUE,
    .AssistanceEnabled = FALSE
};

static VAR(EPS_PerformanceData_T, EPS_SWC_VAR) EPS_PerformanceData = {
    .LastResponseTime_Ms = 0U,
    .MaxResponseTime_Ms = 0U,
    .CurrentPowerConsumption_W = 0.0F,
    .MaxPowerConsumption_W = 0.0F,
    .EcuTemperature_DegC = 25.0F,
    .MotorTemperature_DegC = 25.0F,
    .SystemUptime_Ms = 0U,
    .TotalSteeringCycles = 0U
};

#define EPS_SWC_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "EPS_SWC_MemMap.h"

#define EPS_SWC_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "EPS_SWC_MemMap.h"

/* Inter-Runnable Variables */
VAR(EPS_SensorData_T, EPS_SWC_VAR) EPS_IRV_SensorData;
VAR(EPS_AssistanceParams_T, EPS_SWC_VAR) EPS_IRV_AssistanceParams;
VAR(EPS_MotorCommand_T, EPS_SWC_VAR) EPS_IRV_MotorCommand;
VAR(EPS_SystemState_T, EPS_SWC_VAR) EPS_IRV_SystemState;

/* Local variables */
static VAR(uint32, EPS_SWC_VAR) EPS_SystemTickCounter;
static VAR(uint32, EPS_SWC_VAR) EPS_LastWatchdogReset;

#define EPS_SWC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "EPS_SWC_MemMap.h"

/*******************************************************************************
 * Local Function Prototypes
 ******************************************************************************/

#define EPS_SWC_START_SEC_CODE
#include "EPS_SWC_MemMap.h"

static FUNC(Std_ReturnType, EPS_SWC_CODE) EPS_CalculateAssistance(
    P2CONST(EPS_SensorData_T, AUTOMATIC, EPS_SWC_APPL_CONST) SensorData,
    P2VAR(EPS_AssistanceParams_T, AUTOMATIC, EPS_SWC_APPL_VAR) AssistanceParams
);

static FUNC(Std_ReturnType, EPS_SWC_CODE) EPS_ApplySafetyLimits(
    P2VAR(EPS_AssistanceParams_T, AUTOMATIC, EPS_SWC_APPL_VAR) AssistanceParams
);

static FUNC(void, EPS_SWC_CODE) EPS_UpdatePerformanceData(
    P2CONST(EPS_SensorData_T, AUTOMATIC, EPS_SWC_APPL_CONST) SensorData
);

static FUNC(Std_ReturnType, EPS_SWC_CODE) EPS_GenerateMotorCommand(
    P2CONST(EPS_AssistanceParams_T, AUTOMATIC, EPS_SWC_APPL_CONST) AssistanceParams,
    P2VAR(EPS_MotorCommand_T, AUTOMATIC, EPS_SWC_APPL_VAR) MotorCommand
);

static FUNC(boolean, EPS_SWC_CODE) EPS_DetectOscillation(
    P2CONST(float32, AUTOMATIC, EPS_SWC_APPL_CONST) Data,
    VAR(uint8, AUTOMATIC) Size
);

/*******************************************************************************
 * AUTOSAR Runnable Entity Implementations
 ******************************************************************************/

/**
 * @brief EPS System Initialization Runnable
 * @details AUTOSAR Runnable Entity executed during system initialization
 * 
 * Requirements: EPS-FR-033, EPS-SR-084, EPS-PR-014
 */
FUNC(void, EPS_SWC_CODE) EPS_Init_Runnable(void)
{
    Std_ReturnType retVal = E_OK;
    
    /* Initialize system state */
    EPS_SystemState.OperatingMode = EPS_MODE_INIT;
    EPS_SystemState.SystemStatus = EPS_STATUS_INITIALIZING;
    EPS_SystemState.SystemUptime_Ms = 0U;
    EPS_SystemState.FaultCount = 0U;
    EPS_SystemState.LastFaultTime_Ms = 0U;
    EPS_SystemState.ManualSteeringAvailable = TRUE;
    EPS_SystemState.AssistanceEnabled = FALSE;
    
    /* Initialize Inter-Runnable Variables */
    (void)memset(&EPS_IRV_SensorData, 0, sizeof(EPS_SensorData_T));
    (void)memset(&EPS_IRV_AssistanceParams, 0, sizeof(EPS_AssistanceParams_T));
    (void)memset(&EPS_IRV_MotorCommand, 0, sizeof(EPS_MotorCommand_T));
    
    /* Initialize system counters */
    EPS_SystemTickCounter = 0U;
    EPS_LastWatchdogReset = 0U;
    
    /* Initialize power management through RTE */
    retVal = Rte_Call_PowerManagement_Init();
    if (retVal != RTE_E_OK)
    {
        EPS_SystemState.SystemStatus = EPS_STATUS_FAULT;
        EPS_SystemState.FaultCount++;
        return;
    }
    
    /* Initialize safety subsystem through RTE */
    retVal = Rte_Call_SafetyManager_Init();
    if (retVal != RTE_E_OK)
    {
        EPS_SystemState.SystemStatus = EPS_STATUS_FAULT;
        EPS_SystemState.FaultCount++;
        return;
    }
    
    /* Initialize sensors through RTE */
    retVal = Rte_Call_SensorManager_Init();
    if (retVal != RTE_E_OK)
    {
        EPS_SystemState.SystemStatus = EPS_STATUS_FAULT;
        EPS_SystemState.FaultCount++;
        return;
    }
    
    /* Initialize motor control through RTE */
    retVal = Rte_Call_MotorControl_Init();
    if (retVal != RTE_E_OK)
    {
        EPS_SystemState.SystemStatus = EPS_STATUS_FAULT;
        EPS_SystemState.FaultCount++;
        return;
    }
    
    /* Perform initial self-test */
    retVal = Rte_Call_DiagnosticManager_SelfTest();
    if (retVal != RTE_E_OK)
    {
        EPS_SystemState.SystemStatus = EPS_STATUS_FAULT;
        EPS_SystemState.FaultCount++;
        return;
    }
    
    /* System initialization complete */
    EPS_SystemState.OperatingMode = EPS_MODE_NORMAL;
    EPS_SystemState.SystemStatus = EPS_STATUS_READY;
    EPS_SystemState.AssistanceEnabled = TRUE;
    
    /* Copy to Inter-Runnable Variable */
    EPS_IRV_SystemState = EPS_SystemState;
    
    /* Send system state through RTE */
    (void)Rte_Write_SystemState_SystemState(&EPS_SystemState);
}

/**
 * @brief EPS Main Cyclic Task Runnable
 * @details AUTOSAR Runnable Entity for main EPS control loop
 * 
 * Requirements: EPS-FR-019, EPS-PR-014, EPS-SR-041
 */
FUNC(void, EPS_SWC_CODE) EPS_MainTask_Runnable(void)
{
    Std_ReturnType retVal = E_OK;
    EPS_SensorData_T sensorData;
    EPS_AssistanceParams_T assistanceParams;
    EPS_MotorCommand_T motorCommand;
    
    /* Increment system tick counter */
    EPS_SystemTickCounter++;
    EPS_SystemState.SystemUptime_Ms = EPS_SystemTickCounter;
    
    /* Watchdog reset - EPS-SR-041 */
    if ((EPS_SystemTickCounter - EPS_LastWatchdogReset) >= EPS_WATCHDOG_TIMEOUT_MS)
    {
        (void)Rte_Call_SafetyManager_ResetWatchdog();
        EPS_LastWatchdogReset = EPS_SystemTickCounter;
    }
    
    /* Read sensor data through RTE - EPS-FR-007, EPS-IR-028 */
    retVal = Rte_Read_SensorData_SensorData(&sensorData);
    if (retVal != RTE_E_OK)
    {
        /* Handle sensor fault */
        EPS_SystemState.SystemStatus = EPS_STATUS_FAULT;
        EPS_SystemState.FaultCount++;
        return;
    }
    
    /* Store in Inter-Runnable Variable */
    EPS_IRV_SensorData = sensorData;
    
    /* Validate sensor data - EPS-SR-019, EPS-DR-011 */
    retVal = Rte_Call_SensorManager_ValidateData(&sensorData);
    if (retVal != RTE_E_OK)
    {
        /* Handle sensor validation fault */
        EPS_SystemState.SystemStatus = EPS_STATUS_DEGRADED;
        EPS_SystemState.FaultCount++;
        return;
    }
    
    /* Update performance data - EPS-PR-051 */
    EPS_UpdatePerformanceData(&sensorData);
    
    /* Calculate steering assistance - EPS-FR-002, EPS-FR-017 */
    retVal = EPS_CalculateAssistance(&sensorData, &assistanceParams);
    if (retVal != E_OK)
    {
        /* Handle calculation fault */
        assistanceParams.TotalAssistance_Nm = 0.0F;
        assistanceParams.SafetyLimited = TRUE;
    }
    
    /* Apply safety limits - EPS-SR-021, EPS-SR-005 */
    retVal = EPS_ApplySafetyLimits(&assistanceParams);
    if (retVal != E_OK)
    {
        /* Safety limits applied - continue with limited assistance */
        EPS_SystemState.SystemStatus = EPS_STATUS_DEGRADED;
    }
    
    /* Store in Inter-Runnable Variable */
    EPS_IRV_AssistanceParams = assistanceParams;
    
    /* Generate motor command - EPS-FR-012, EPS-IR-055 */
    retVal = EPS_GenerateMotorCommand(&assistanceParams, &motorCommand);
    if (retVal != E_OK)
    {
        /* Handle motor command generation fault */
        motorCommand.TargetTorque_Nm = 0.0F;
        motorCommand.Enable = FALSE;
    }
    
    /* Store in Inter-Runnable Variable */
    EPS_IRV_MotorCommand = motorCommand;
    
    /* Send motor command through RTE - EPS-FR-013, EPS-PR-014 */
    (void)Rte_Write_MotorCommand_MotorCommand(&motorCommand);
    
    /* Update system state */
    if (EPS_SystemState.SystemStatus != EPS_STATUS_FAULT)
    {
        EPS_SystemState.SystemStatus = EPS_STATUS_ACTIVE;
    }
    
    /* Copy to Inter-Runnable Variable */
    EPS_IRV_SystemState = EPS_SystemState;
    
    /* Send system state through RTE */
    (void)Rte_Write_SystemState_SystemState(&EPS_SystemState);
}

/**
 * @brief EPS Safety Monitor Runnable
 * @details AUTOSAR Runnable Entity for safety monitoring
 * 
 * Requirements: EPS-SR-047, EPS-DR-003
 */
FUNC(void, EPS_SWC_CODE) EPS_SafetyMonitor_Runnable(void)
{
    Std_ReturnType retVal = E_OK;
    uint8 safetyStatus = 0U;
    
    /* Monitor safety mechanisms through RTE */
    retVal = Rte_Call_SafetyManager_MonitorSafety(&safetyStatus);
    if (retVal != RTE_E_OK)
    {
        /* Safety monitoring fault detected */
        EPS_SystemState.OperatingMode = EPS_MODE_FAIL_SAFE;
        EPS_SystemState.SystemStatus = EPS_STATUS_FAULT;
        EPS_SystemState.FaultCount++;
        EPS_SystemState.LastFaultTime_Ms = EPS_SystemTickCounter;
        
        /* Disable motor assistance */
        EPS_SystemState.AssistanceEnabled = FALSE;
        
        /* Send fault notification through RTE */
        (void)Rte_Call_DiagnosticManager_SetDTC(0x5001U, 0x01U); /* Safety fault DTC */
    }
    
    /* Check for critical faults that require immediate safe state */
    if (safetyStatus & 0x80U) /* Critical fault bit */
    {
        EPS_SystemState.OperatingMode = EPS_MODE_FAIL_SAFE;
        EPS_SystemState.AssistanceEnabled = FALSE;
        
        /* Ensure manual steering is available */
        (void)Rte_Call_MotorControl_DisconnectMotor();
    }
    
    /* Update system state */
    EPS_IRV_SystemState = EPS_SystemState;
    (void)Rte_Write_SystemState_SystemState(&EPS_SystemState);
}

/**
 * @brief EPS Diagnostic Task Runnable
 * @details AUTOSAR Runnable Entity for diagnostic functions
 * 
 * Requirements: EPS-DR-089, EPS-DR-093
 */
FUNC(void, EPS_SWC_CODE) EPS_DiagnosticTask_Runnable(void)
{
    Std_ReturnType retVal = E_OK;
    
    /* Update diagnostic data through RTE */
    retVal = Rte_Call_DiagnosticManager_UpdateData(&EPS_IRV_SensorData, &EPS_IRV_AssistanceParams);
    if (retVal != RTE_E_OK)
    {
        /* Diagnostic update failed - non-critical */
    }
    
    /* Send performance data through RTE */
    (void)Rte_Write_PerformanceData_PerformanceData(&EPS_PerformanceData);
    
    /* Check for diagnostic trouble codes */
    uint16 dtcCode = 0U;
    uint8 dtcStatus = 0U;
    
    retVal = Rte_Call_DiagnosticManager_GetDTC(&dtcCode, &dtcStatus);
    if ((retVal == RTE_E_OK) && (dtcCode != 0U))
    {
        /* DTC present - update fault count */
        EPS_SystemState.FaultCount++;
        EPS_SystemState.LastFaultTime_Ms = EPS_SystemTickCounter;
    }
}

/**
 * @brief EPS Mode Request Handler Runnable
 * @details AUTOSAR Runnable Entity for mode change requests
 * 
 * Requirements: EPS-FR-033 to EPS-FR-042
 */
FUNC(void, EPS_SWC_CODE) EPS_ModeRequest_Runnable(void)
{
    Std_ReturnType retVal = E_OK;
    EPS_OperatingMode_T requestedMode = EPS_MODE_INIT;
    
    /* Read mode request through RTE */
    retVal = Rte_Read_ModeRequest_ModeRequest(&requestedMode);
    if (retVal != RTE_E_OK)
    {
        return; /* No mode request available */
    }
    
    /* Process mode change request */
    switch (requestedMode)
    {
        case EPS_MODE_NORMAL:
            if (EPS_SystemState.OperatingMode != EPS_MODE_FAIL_SAFE)
            {
                EPS_SystemState.OperatingMode = EPS_MODE_NORMAL;
                EPS_SystemState.SystemStatus = EPS_STATUS_ACTIVE;
                EPS_SystemState.AssistanceEnabled = TRUE;
            }
            break;
            
        case EPS_MODE_DEGRADED:
            EPS_SystemState.OperatingMode = EPS_MODE_DEGRADED;
            EPS_SystemState.SystemStatus = EPS_STATUS_DEGRADED;
            EPS_SystemState.AssistanceEnabled = TRUE; /* Limited assistance */
            break;
            
        case EPS_MODE_FAIL_SAFE:
            EPS_SystemState.OperatingMode = EPS_MODE_FAIL_SAFE;
            EPS_SystemState.SystemStatus = EPS_STATUS_FAULT;
            EPS_SystemState.AssistanceEnabled = FALSE;
            (void)Rte_Call_MotorControl_DisconnectMotor();
            break;
            
        case EPS_MODE_SLEEP:
            EPS_SystemState.OperatingMode = EPS_MODE_SLEEP;
            EPS_SystemState.SystemStatus = EPS_STATUS_SLEEP;
            EPS_SystemState.AssistanceEnabled = FALSE;
            (void)Rte_Call_PowerManagement_EnterSleep();
            break;
            
        default:
            /* Invalid mode request - ignore */
            break;
    }
    
    /* Update Inter-Runnable Variable and send through RTE */
    EPS_IRV_SystemState = EPS_SystemState;
    (void)Rte_Write_SystemState_SystemState(&EPS_SystemState);
}

/**
 * @brief EPS Shutdown Runnable
 * @details AUTOSAR Runnable Entity for system shutdown
 * 
 * Requirements: EPS-FR-042, EPS-ER-043
 */
FUNC(void, EPS_SWC_CODE) EPS_Shutdown_Runnable(void)
{
    /* Disable motor control */
    (void)Rte_Call_MotorControl_Disable();
    
    /* Save diagnostic data */
    (void)Rte_Call_DiagnosticManager_SaveData();
    
    /* Enter sleep mode */
    EPS_SystemState.OperatingMode = EPS_MODE_SLEEP;
    EPS_SystemState.SystemStatus = EPS_STATUS_SLEEP;
    EPS_SystemState.AssistanceEnabled = FALSE;
    
    /* Power down non-essential systems */
    (void)Rte_Call_PowerManagement_EnterSleep();
    
    /* Update system state */
    EPS_IRV_SystemState = EPS_SystemState;
    (void)Rte_Write_SystemState_SystemState(&EPS_SystemState);
}

/*******************************************************************************
 * Local Function Implementations
 ******************************************************************************/

/**
 * @brief Calculate steering assistance based on inputs
 * @param SensorData Pointer to sensor data structure
 * @param AssistanceParams Pointer to assistance parameters output
 * @return Std_ReturnType Calculation result
 * 
 * Requirements: EPS-FR-002, EPS-FR-017, EPS-PR-040
 */
static FUNC(Std_ReturnType, EPS_SWC_CODE) EPS_CalculateAssistance(
    P2CONST(EPS_SensorData_T, AUTOMATIC, EPS_SWC_APPL_CONST) SensorData,
    P2VAR(EPS_AssistanceParams_T, AUTOMATIC, EPS_SWC_APPL_VAR) AssistanceParams
)
{
    float32 baseAssistance = 0.0F;
    float32 speedFactor = 1.0F;
    float32 returnToCenterTorque = 0.0F;
    float32 dampingTorque = 0.0F;
    
    if ((SensorData == NULL_PTR) || (AssistanceParams == NULL_PTR))
    {
        return E_NOT_OK;
    }
    
    /* Base assistance calculation - EPS-FR-002 */
    if (fabsf(SensorData->DriverTorque_Nm) > EPS_MIN_TORQUE_THRESHOLD_NM)
    {
        baseAssistance = SensorData->DriverTorque_Nm * EPS_BASE_ASSISTANCE_GAIN;
        
        /* Apply torque direction check - EPS-FR-003, EPS-SR-018 */
        if (((SensorData->DriverTorque_Nm > 0.0F) && (baseAssistance < 0.0F)) ||
            ((SensorData->DriverTorque_Nm < 0.0F) && (baseAssistance > 0.0F)))
        {
            /* Direction mismatch detected - safety fault */
            (void)Rte_Call_DiagnosticManager_SetDTC(0x5002U, 0x01U); /* Direction mismatch DTC */
            return E_NOT_OK;
        }
    }
    
    /* Speed-sensitive assistance - EPS-FR-017, EPS-PR-040 */
    if (SensorData->VehicleSpeed_KmH <= EPS_LOW_SPEED_THRESHOLD_KMH)
    {
        speedFactor = 1.0F; /* Maximum assistance at low speeds */
    }
    else if (SensorData->VehicleSpeed_KmH >= EPS_HIGH_SPEED_THRESHOLD_KMH)
    {
        speedFactor = EPS_MIN_ASSISTANCE_FACTOR; /* Minimum assistance at high speeds */
    }
    else
    {
        /* Linear interpolation between low and high speed thresholds */
        float32 speedRange = EPS_HIGH_SPEED_THRESHOLD_KMH - EPS_LOW_SPEED_THRESHOLD_KMH;
        float32 speedOffset = SensorData->VehicleSpeed_KmH - EPS_LOW_SPEED_THRESHOLD_KMH;
        speedFactor = 1.0F - (speedOffset / speedRange) * (1.0F - EPS_MIN_ASSISTANCE_FACTOR);
    }
    
    /* Return-to-center assistance - EPS-FR-023, EPS-PR-034 */
    if (fabsf(SensorData->DriverTorque_Nm) < EPS_RETURN_TO_CENTER_THRESHOLD_NM)
    {
        returnToCenterTorque = -SensorData->SteeringAngle_Deg * EPS_RETURN_TO_CENTER_GAIN;
        
        /* Speed-based return-to-center adjustment - EPS-FR-025 */
        returnToCenterTorque *= (1.0F + SensorData->VehicleSpeed_KmH * EPS_SPEED_RTC_FACTOR);
    }
    
    /* Damping calculation - EPS-FR-029, EPS-PR-037 */
    dampingTorque = -SensorData->SteeringVelocity_DegS * EPS_DAMPING_COEFFICIENT;
    
    /* Speed-based damping adjustment - EPS-FR-031 */
    dampingTorque *= (1.0F + SensorData->VehicleSpeed_KmH * EPS_SPEED_DAMPING_FACTOR);
    
    /* Combine all assistance components */
    AssistanceParams->BaseAssistance_Nm = baseAssistance * speedFactor;
    AssistanceParams->ReturnToCenter_Nm = returnToCenterTorque;
    AssistanceParams->Damping_Nm = dampingTorque;
    AssistanceParams->TotalAssistance_Nm = AssistanceParams->BaseAssistance_Nm + 
                                          AssistanceParams->ReturnToCenter_Nm + 
                                          AssistanceParams->Damping_Nm;
    
    /* Store calculation metadata */
    AssistanceParams->SpeedFactor = speedFactor;
    AssistanceParams->CalculationTimestamp_Ms = EPS_SystemTickCounter;
    AssistanceParams->SafetyLimited = FALSE;
    AssistanceParams->RateLimited = FALSE;
    AssistanceParams->OscillationDetected = FALSE;
    
    return E_OK;
}

/**
 * @brief Apply safety limits to assistance parameters
 * @param AssistanceParams Pointer to assistance parameters
 * @return Std_ReturnType Safety check result
 * 
 * Requirements: EPS-SR-021, EPS-SR-005, EPS-PR-004
 */
static FUNC(Std_ReturnType, EPS_SWC_CODE) EPS_ApplySafetyLimits(
    P2VAR(EPS_AssistanceParams_T, AUTOMATIC, EPS_SWC_APPL_VAR) AssistanceParams
)
{
    Std_ReturnType retVal = E_OK;
    
    if (AssistanceParams == NULL_PTR)
    {
        return E_NOT_OK;
    }
    
    /* Check for excessive assistance - EPS-SR-021 */
    if (fabsf(AssistanceParams->TotalAssistance_Nm) > EPS_MAX_ASSISTANCE_TORQUE_NM)
    {
        (void)Rte_Call_DiagnosticManager_SetDTC(0x5001U, 0x01U); /* Excessive assistance DTC */
        
        /* Limit assistance to maximum allowed - EPS-FR-004 */
        if (AssistanceParams->TotalAssistance_Nm > 0.0F)
        {
            AssistanceParams->TotalAssistance_Nm = EPS_MAX_ASSISTANCE_TORQUE_NM;
        }
        else
        {
            AssistanceParams->TotalAssistance_Nm = -EPS_MAX_ASSISTANCE_TORQUE_NM;
        }
        
        AssistanceParams->SafetyLimited = TRUE;
        retVal = E_NOT_OK;
    }
    
    /* Check for oscillation detection - EPS-SR-006 */
    static float32 previousAssistance[EPS_OSCILLATION_BUFFER_SIZE] = {0.0F};
    static uint8 bufferIndex = 0U;
    
    previousAssistance[bufferIndex] = AssistanceParams->TotalAssistance_Nm;
    bufferIndex = (bufferIndex + 1U) % EPS_OSCILLATION_BUFFER_SIZE;
    
    if (EPS_DetectOscillation(previousAssistance, EPS_OSCILLATION_BUFFER_SIZE) == TRUE)
    {
        (void)Rte_Call_DiagnosticManager_SetDTC(0x5003U, 0x01U); /* Oscillation detected DTC */
        AssistanceParams->TotalAssistance_Nm = 0.0F; /* Disable assistance */
        AssistanceParams->OscillationDetected = TRUE;
        retVal = E_NOT_OK;
    }
    
    /* Rate limiting - EPS-FR-005 */
    static float32 previousAssistanceValue = 0.0F;
    float32 assistanceRate = AssistanceParams->TotalAssistance_Nm - previousAssistanceValue;
    
    if (fabsf(assistanceRate) > EPS_MAX_ASSISTANCE_RATE_NMS)
    {
        if (assistanceRate > 0.0F)
        {
            AssistanceParams->TotalAssistance_Nm = previousAssistanceValue + EPS_MAX_ASSISTANCE_RATE_NMS;
        }
        else
        {
            AssistanceParams->TotalAssistance_Nm = previousAssistanceValue - EPS_MAX_ASSISTANCE_RATE_NMS;
        }
        AssistanceParams->RateLimited = TRUE;
    }
    
    previousAssistanceValue = AssistanceParams->TotalAssistance_Nm;
    
    return retVal;
}

/**
 * @brief Update system performance data
 * @param SensorData Pointer to current sensor data
 *
 * Requirements: EPS-PR-051, EPS-DR-093
 */
static FUNC(void, EPS_SWC_CODE) EPS_UpdatePerformanceData(
    P2CONST(EPS_SensorData_T, AUTOMATIC, EPS_SWC_APPL_CONST) SensorData
)
{
    if (SensorData == NULL_PTR)
    {
        return;
    }
    
    /* Update response time measurement - EPS-PR-014 */
    static uint32 lastTorqueChangeTime = 0U;
    static float32 lastDriverTorque = 0.0F;
    
    if (fabsf(SensorData->DriverTorque_Nm - lastDriverTorque) > EPS_TORQUE_CHANGE_THRESHOLD_NM)
    {
        if (lastTorqueChangeTime > 0U)
        {
            uint32 responseTime = EPS_SystemTickCounter - lastTorqueChangeTime;
            EPS_PerformanceData.LastResponseTime_Ms = responseTime;
            
            /* Update response time statistics */
            if (responseTime > EPS_PerformanceData.MaxResponseTime_Ms)
            {
                EPS_PerformanceData.MaxResponseTime_Ms = responseTime;
            }
            
            /* Check response time requirement - EPS-PR-014 */
            if (responseTime > EPS_MAX_RESPONSE_TIME_MS)
            {
                (void)Rte_Call_DiagnosticManager_SetDTC(0x6001U, 0x01U); /* Slow response DTC */
            }
        }
        lastTorqueChangeTime = EPS_SystemTickCounter;
        lastDriverTorque = SensorData->DriverTorque_Nm;
    }
    
    /* Update power consumption data - EPS-PR-055 */
    (void)Rte_Call_PowerManagement_GetConsumption(&EPS_PerformanceData.CurrentPowerConsumption_W);
    
    /* Update temperature data - EPS-EDR-087 */
    EPS_PerformanceData.EcuTemperature_DegC = SensorData->EcuTemperature_DegC;
    EPS_PerformanceData.MotorTemperature_DegC = SensorData->MotorTemperature_DegC;
    
    /* Update system uptime */
    EPS_PerformanceData.SystemUptime_Ms = EPS_SystemTickCounter;
}

/**
 * @brief Generate motor command from assistance parameters
 * @param AssistanceParams Pointer to assistance parameters
 * @param MotorCommand Pointer to motor command output
 * @return Std_ReturnType Generation result
 *
 * Requirements: EPS-FR-012, EPS-IR-055
 */
static FUNC(Std_ReturnType, EPS_SWC_CODE) EPS_GenerateMotorCommand(
    P2CONST(EPS_AssistanceParams_T, AUTOMATIC, EPS_SWC_APPL_CONST) AssistanceParams,
    P2VAR(EPS_MotorCommand_T, AUTOMATIC, EPS_SWC_APPL_VAR) MotorCommand
)
{
    if ((AssistanceParams == NULL_PTR) || (MotorCommand == NULL_PTR))
    {
        return E_NOT_OK;
    }
    
    /* Set target torque */
    MotorCommand->TargetTorque_Nm = AssistanceParams->TotalAssistance_Nm;
    
    /* Set current limit based on operating mode */
    if (EPS_SystemState.OperatingMode == EPS_MODE_DEGRADED)
    {
        MotorCommand->CurrentLimit_A = 20.0F; /* Reduced current limit */
    }
    else
    {
        MotorCommand->CurrentLimit_A = 40.0F; /* Normal current limit */
    }
    
    /* Enable motor if assistance is enabled and system is ready */
    MotorCommand->Enable = (EPS_SystemState.AssistanceEnabled == TRUE) &&
                          (EPS_SystemState.SystemStatus != EPS_STATUS_FAULT);
    
    /* Set timestamp */
    MotorCommand->CommandTimestamp_Ms = EPS_SystemTickCounter;
    
    /* PWM duty cycles will be calculated by motor control BSW */
    MotorCommand->PwmDutyCycle_U[0] = 0U;
    MotorCommand->PwmDutyCycle_U[1] = 0U;
    MotorCommand->PwmDutyCycle_U[2] = 0U;
    
    return E_OK;
}

/**
 * @brief Detect oscillation in assistance data
 * @param Data Pointer to data array
 * @param Size Size of data array
 * @return boolean TRUE if oscillation detected
 *
 * Requirements: EPS-SR-006
 */
static FUNC(boolean, EPS_SWC_CODE) EPS_DetectOscillation(
    P2CONST(float32, AUTOMATIC, EPS_SWC_APPL_CONST) Data,
    VAR(uint8, AUTOMATIC) Size
)
{
    uint8 i;
    uint8 signChanges = 0U;
    float32 maxAmplitude = 0.0F;
    
    if ((Data == NULL_PTR) || (Size < 3U))
    {
        return FALSE;
    }
    
    /* Count sign changes and find maximum amplitude */
    for (i = 1U; i < Size; i++)
    {
        if (((Data[i-1U] > 0.0F) && (Data[i] < 0.0F)) ||
            ((Data[i-1U] < 0.0F) && (Data[i] > 0.0F)))
        {
            signChanges++;
        }
        
        if (fabsf(Data[i]) > maxAmplitude)
        {
            maxAmplitude = fabsf(Data[i]);
        }
    }
    
    /* Oscillation detected if:
     * - More than 4 sign changes in buffer (frequency > 0.5Hz at 1ms cycle)
     * - Amplitude > 2Nm
     */
    if ((signChanges > 4U) && (maxAmplitude > 2.0F))
    {
        return TRUE;
    }
    
    return FALSE;
}

#define EPS_SWC_STOP_SEC_CODE
#include "EPS_SWC_MemMap.h"