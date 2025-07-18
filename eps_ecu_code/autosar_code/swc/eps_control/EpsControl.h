#ifndef EPS_CONTROL_H
#define EPS_CONTROL_H

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "Rte_EpsControl.h"

/* AUTOSAR Software Component Version Information */
#define EPS_CONTROL_SW_MAJOR_VERSION    1
#define EPS_CONTROL_SW_MINOR_VERSION    0
#define EPS_CONTROL_SW_PATCH_VERSION    0

/* EPS Control Constants */
#define EPS_MAX_ASSIST_TORQUE          50.0f   /* Nm */
#define EPS_MIN_ASSIST_TORQUE          -50.0f  /* Nm */
#define EPS_LOW_SPEED_THRESHOLD        20.0f   /* km/h */
#define EPS_RTC_ANGLE_THRESHOLD        5.0f    /* degrees */
#define EPS_SAMPLING_RATE              1000    /* Hz */

/* EPS System States */
typedef enum {
    EPS_STATE_INIT = 0,
    EPS_STATE_NORMAL,
    EPS_STATE_FAULT,
    EPS_STATE_SAFE_MODE
} EpsSystemState_t;

/* EPS Fault Codes */
typedef enum {
    EPS_FAULT_NONE = 0,
    EPS_FAULT_TORQUE_SENSOR,
    EPS_FAULT_ANGLE_SENSOR,
    EPS_FAULT_SPEED_SENSOR,
    EPS_FAULT_MOTOR_OVERCURRENT,
    EPS_FAULT_MOTOR_OVERTEMP,
    EPS_FAULT_COMMUNICATION_ERROR,
    EPS_FAULT_ECU_INTERNAL_ERROR
} EpsFaultCode_t;

/* EPS Control Data Structure */
typedef struct {
    float driver_torque;           /* Driver applied torque (Nm) */
    float steering_angle;          /* Steering wheel angle (degrees) */
    float vehicle_speed;           /* Vehicle speed (km/h) */
    float steering_angular_velocity; /* Steering angular velocity (deg/s) */
    float target_assist_torque;    /* Calculated assist torque (Nm) */
    float motor_current_command;   /* Motor current command (A) */
    EpsSystemState_t system_state; /* Current system state */
    EpsFaultCode_t fault_code;     /* Current fault code */
    boolean adas_active;           /* ADAS system active flag */
    float adas_command_torque;     /* ADAS command torque (Nm) */
} EpsControlData_t;

/* Function Prototypes */

/**
 * @brief Initialize the EPS Control Software Component
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType EpsControl_Init(void);

/**
 * @brief Main EPS control algorithm execution
 * @param control_data Pointer to EPS control data structure
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType EpsControl_MainFunction(EpsControlData_t* control_data);

/**
 * @brief Calculate assist torque based on sensor inputs
 * @param driver_torque Driver applied torque (Nm)
 * @param vehicle_speed Vehicle speed (km/h)
 * @param steering_angle Steering wheel angle (degrees)
 * @param steering_angular_velocity Steering angular velocity (deg/s)
 * @return float Calculated assist torque (Nm)
 */
float EpsControl_CalculateAssistTorque(float driver_torque, 
                                     float vehicle_speed,
                                     float steering_angle,
                                     float steering_angular_velocity);

/**
 * @brief Apply return-to-center logic
 * @param steering_angle Current steering angle (degrees)
 * @param vehicle_speed Current vehicle speed (km/h)
 * @return float RTC assist torque component (Nm)
 */
float EpsControl_CalculateRTCComponent(float steering_angle, float vehicle_speed);

/**
 * @brief Apply damping control
 * @param steering_angular_velocity Steering angular velocity (deg/s)
 * @return float Damping torque component (Nm)
 */
float EpsControl_CalculateDampingComponent(float steering_angular_velocity);

/**
 * @brief Convert assist torque to motor current command
 * @param assist_torque Target assist torque (Nm)
 * @return float Motor current command (A)
 */
float EpsControl_ConvertTorqueToCurrent(float assist_torque);

/**
 * @brief Perform fault detection and management
 * @param control_data Pointer to EPS control data structure
 * @return Std_ReturnType - E_OK if no faults, E_NOT_OK if faults detected
 */
Std_ReturnType EpsControl_FaultDetection(EpsControlData_t* control_data);

/**
 * @brief Handle system state transitions
 * @param control_data Pointer to EPS control data structure
 */
void EpsControl_StateManagement(EpsControlData_t* control_data);

/**
 * @brief Deinitialize the EPS Control Software Component
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType EpsControl_DeInit(void);

#endif /* EPS_CONTROL_H */ 