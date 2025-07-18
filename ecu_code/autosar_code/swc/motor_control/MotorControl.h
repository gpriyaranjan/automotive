#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "Rte_MotorControl.h"

/* AUTOSAR Software Component Version Information */
#define MOTOR_CONTROL_SW_MAJOR_VERSION    1
#define MOTOR_CONTROL_SW_MINOR_VERSION    0
#define MOTOR_CONTROL_SW_PATCH_VERSION    0

/* Motor Control Constants */
#define MOTOR_MAX_CURRENT                100.0f  /* Maximum motor current (A) */
#define MOTOR_MIN_CURRENT                -100.0f /* Minimum motor current (A) */
#define MOTOR_MAX_VOLTAGE                48.0f   /* Maximum motor voltage (V) */
#define MOTOR_MIN_VOLTAGE                -48.0f  /* Minimum motor voltage (V) */
#define MOTOR_PWM_FREQUENCY              20000   /* PWM frequency (Hz) */
#define MOTOR_CONTROL_RATE               1000    /* Control loop rate (Hz) */

/* PID Controller Constants */
#define MOTOR_PID_KP                     2.0f    /* Proportional gain */
#define MOTOR_PID_KI                     0.1f    /* Integral gain */
#define MOTOR_PID_KD                     0.05f   /* Derivative gain */
#define MOTOR_PID_INTEGRAL_LIMIT         50.0f   /* Integral windup limit */

/* Motor Control Data Structure */
typedef struct {
    float target_current;               /* Target motor current (A) */
    float actual_current;               /* Actual motor current (A) */
    float current_error;                /* Current error (A) */
    float motor_voltage;                /* Motor voltage command (V) */
    float motor_speed;                  /* Motor speed (rpm) */
    float motor_torque;                 /* Motor torque (Nm) */
    float motor_temperature;            /* Motor temperature (°C) */
    
    /* PID Controller State */
    float pid_integral;                 /* PID integral term */
    float pid_derivative;               /* PID derivative term */
    float pid_previous_error;           /* Previous error for derivative calculation */
    
    /* Control Flags */
    boolean motor_enabled;              /* Motor enable flag */
    boolean current_control_active;     /* Current control active flag */
    boolean fault_detected;             /* Motor fault flag */
    
    /* Timing */
    uint32_t last_control_timestamp;    /* Last control update timestamp */
    uint32_t control_period_ms;         /* Control period in milliseconds */
} MotorControlData_t;

/* Motor Control States */
typedef enum {
    MOTOR_STATE_INIT = 0,
    MOTOR_STATE_DISABLED,
    MOTOR_STATE_ENABLED,
    MOTOR_STATE_FAULT,
    MOTOR_STATE_EMERGENCY_STOP
} MotorControlState_t;

/* Motor Fault Codes */
typedef enum {
    MOTOR_FAULT_NONE = 0,
    MOTOR_FAULT_OVERCURRENT,
    MOTOR_FAULT_OVERVOLTAGE,
    MOTOR_FAULT_OVERTEMPERATURE,
    MOTOR_FAULT_UNDERVOLTAGE,
    MOTOR_FAULT_COMMUNICATION_ERROR,
    MOTOR_FAULT_HARDWARE_ERROR,
    MOTOR_FAULT_SENSOR_ERROR
} MotorFaultCode_t;

/* Motor Control Configuration */
typedef struct {
    float max_current_limit;            /* Maximum current limit (A) */
    float max_voltage_limit;            /* Maximum voltage limit (V) */
    float max_temperature_limit;        /* Maximum temperature limit (°C) */
    float pid_kp;                       /* PID proportional gain */
    float pid_ki;                       /* PID integral gain */
    float pid_kd;                       /* PID derivative gain */
    uint32_t control_rate_hz;           /* Control loop rate (Hz) */
} MotorControlConfig_t;

/* Function Prototypes */

/**
 * @brief Initialize the Motor Control Software Component
 * @param config Pointer to motor control configuration
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType MotorControl_Init(const MotorControlConfig_t* config);

/**
 * @brief Main motor control function for current regulation
 * @param motor_data Pointer to motor control data structure
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType MotorControl_MainFunction(MotorControlData_t* motor_data);

/**
 * @brief Set target motor current
 * @param target_current Target current in amperes
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType MotorControl_SetTargetCurrent(float target_current);

/**
 * @brief Get actual motor current
 * @param actual_current Pointer to store actual current
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType MotorControl_GetActualCurrent(float* actual_current);

/**
 * @brief Enable motor control
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType MotorControl_Enable(void);

/**
 * @brief Disable motor control
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType MotorControl_Disable(void);

/**
 * @brief Execute PID current control algorithm
 * @param motor_data Pointer to motor control data structure
 * @return float Calculated voltage command (V)
 */
float MotorControl_ExecutePIDControl(MotorControlData_t* motor_data);

/**
 * @brief Apply voltage command to motor
 * @param voltage_command Voltage command in volts
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType MotorControl_ApplyVoltageCommand(float voltage_command);

/**
 * @brief Read motor feedback sensors
 * @param motor_data Pointer to motor control data structure
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType MotorControl_ReadFeedbackSensors(MotorControlData_t* motor_data);

/**
 * @brief Perform motor fault detection
 * @param motor_data Pointer to motor control data structure
 * @return MotorFaultCode_t - Detected fault code
 */
MotorFaultCode_t MotorControl_DetectFaults(const MotorControlData_t* motor_data);

/**
 * @brief Handle motor fault conditions
 * @param motor_data Pointer to motor control data structure
 * @param fault_code Detected fault code
 */
void MotorControl_HandleFault(MotorControlData_t* motor_data, MotorFaultCode_t fault_code);

/**
 * @brief Reset motor control system
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType MotorControl_Reset(void);

/**
 * @brief Get motor control state
 * @param state Pointer to store current state
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType MotorControl_GetState(MotorControlState_t* state);

/**
 * @brief Set motor control configuration
 * @param config Pointer to motor control configuration
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType MotorControl_SetConfiguration(const MotorControlConfig_t* config);

/**
 * @brief Get motor control configuration
 * @param config Pointer to store current configuration
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType MotorControl_GetConfiguration(MotorControlConfig_t* config);

/**
 * @brief Perform motor self-diagnosis
 * @return Std_ReturnType - E_OK if diagnosis passed, E_NOT_OK otherwise
 */
Std_ReturnType MotorControl_SelfDiagnosis(void);

/**
 * @brief Deinitialize the Motor Control Software Component
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType MotorControl_DeInit(void);

#endif /* MOTOR_CONTROL_H */ 