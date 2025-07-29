/**
 * @file ebs_types.h
 * @brief Electronic Braking System - Common Type Definitions
 * @version 1.0
 * @date 2025-07-29
 * @author EBS Development Team
 * 
 * Common type definitions and enumerations for the EBS system
 * 
 * Safety Level: ASIL-D
 * Compliance: ISO 26262, MISRA C:2012
 */

#ifndef EBS_TYPES_H
#define EBS_TYPES_H

#include <stdint.h>
#include <stdbool.h>

/* System State Definitions */
typedef enum {
    EBS_STATE_INIT = 0,
    EBS_STATE_SELF_TEST,
    EBS_STATE_NORMAL,
    EBS_STATE_DEGRADED,
    EBS_STATE_SAFE_MODE,
    EBS_STATE_SHUTDOWN,
    EBS_STATE_ERROR
} ebs_system_state_t;

/* Safety State Definitions */
typedef enum {
    SAFETY_STATE_UNKNOWN = 0,
    SAFETY_STATE_INIT,
    SAFETY_STATE_NORMAL,
    SAFETY_STATE_WARNING,
    SAFETY_STATE_DEGRADED,
    SAFETY_STATE_SAFE,
    SAFETY_STATE_CRITICAL
} ebs_safety_state_t;

/* Safety Fault Types */
typedef enum {
    SAFETY_FAULT_NONE = 0,
    SAFETY_FAULT_SENSOR_FAILURE,
    SAFETY_FAULT_ACTUATOR_FAILURE,
    SAFETY_FAULT_COMMUNICATION_FAILURE,
    SAFETY_FAULT_SELF_TEST_FAILED,
    SAFETY_FAULT_WATCHDOG_TIMEOUT,
    SAFETY_FAULT_MEMORY_CORRUPTION,
    SAFETY_FAULT_CRITICAL,
    SAFETY_FAULT_UNKNOWN_STATE,
    SAFETY_FAULT_SYSTEM_SHUTDOWN
} ebs_safety_fault_t;

/* Wheel Position Definitions */
typedef enum {
    WHEEL_FRONT_LEFT = 0,
    WHEEL_FRONT_RIGHT,
    WHEEL_REAR_LEFT,
    WHEEL_REAR_RIGHT,
    WHEEL_COUNT
} ebs_wheel_position_t;

/* ABS State Definitions */
typedef enum {
    ABS_STATE_INACTIVE = 0,
    ABS_STATE_MONITORING,
    ABS_STATE_ACTIVE,
    ABS_STATE_FAULT
} ebs_abs_state_t;

/* ABS Phase Definitions */
typedef enum {
    ABS_PHASE_NORMAL = 0,
    ABS_PHASE_PRESSURE_REDUCTION,
    ABS_PHASE_PRESSURE_HOLD,
    ABS_PHASE_PRESSURE_INCREASE
} ebs_abs_phase_t;

/* ESC State Definitions */
typedef enum {
    ESC_STATE_INACTIVE = 0,
    ESC_STATE_MONITORING,
    ESC_STATE_ACTIVE_UNDERSTEER,
    ESC_STATE_ACTIVE_OVERSTEER,
    ESC_STATE_FAULT
} ebs_esc_state_t;

/* TCS State Definitions */
typedef enum {
    TCS_STATE_INACTIVE = 0,
    TCS_STATE_MONITORING,
    TCS_STATE_ACTIVE,
    TCS_STATE_FAULT
} ebs_tcs_state_t;

/* Sensor Data Structure */
typedef struct {
    float value;
    uint32_t timestamp;
    bool valid;
    uint8_t quality;
} ebs_sensor_data_t;

/* Wheel Speed Data */
typedef struct {
    ebs_sensor_data_t speed[WHEEL_COUNT];  /* km/h */
    float vehicle_speed;                   /* Estimated vehicle speed */
    bool abs_active[WHEEL_COUNT];          /* ABS active per wheel */
} ebs_wheel_speed_data_t;

/* Pressure Data */
typedef struct {
    ebs_sensor_data_t master_cylinder;     /* Master cylinder pressure */
    ebs_sensor_data_t wheel_pressure[WHEEL_COUNT]; /* Wheel cylinder pressure */
    float target_pressure[WHEEL_COUNT];   /* Target pressure per wheel */
} ebs_pressure_data_t;

/* IMU Data */
typedef struct {
    ebs_sensor_data_t yaw_rate;           /* deg/s */
    ebs_sensor_data_t lateral_accel;      /* m/s² */
    ebs_sensor_data_t longitudinal_accel; /* m/s² */
    float steering_angle;                 /* deg */
} ebs_imu_data_t;

/* Vehicle Dynamics Data */
typedef struct {
    float vehicle_speed;                  /* km/h */
    float wheel_slip[WHEEL_COUNT];        /* Wheel slip ratio */
    float yaw_rate;                       /* deg/s */
    float lateral_acceleration;           /* m/s² */
    float steering_angle;                 /* deg */
    bool vehicle_moving;                  /* Vehicle motion detected */
} ebs_vehicle_dynamics_t;

/* Control Commands */
typedef struct {
    float brake_pressure_cmd[WHEEL_COUNT]; /* Commanded brake pressure */
    float engine_torque_reduction;         /* Engine torque reduction % */
    bool abs_active[WHEEL_COUNT];          /* ABS active per wheel */
    bool esc_active;                       /* ESC active */
    bool tcs_active;                       /* TCS active */
} ebs_control_commands_t;

/* Diagnostic Trouble Code (DTC) */
typedef enum {
    DTC_NO_FAULT = 0x0000,
    
    /* Sensor DTCs */
    DTC_WHEEL_SPEED_SENSOR_FL = 0x1001,
    DTC_WHEEL_SPEED_SENSOR_FR = 0x1002,
    DTC_WHEEL_SPEED_SENSOR_RL = 0x1003,
    DTC_WHEEL_SPEED_SENSOR_RR = 0x1004,
    DTC_PRESSURE_SENSOR_MC = 0x1010,
    DTC_PRESSURE_SENSOR_FL = 0x1011,
    DTC_PRESSURE_SENSOR_FR = 0x1012,
    DTC_PRESSURE_SENSOR_RL = 0x1013,
    DTC_PRESSURE_SENSOR_RR = 0x1014,
    DTC_IMU_SENSOR = 0x1020,
    DTC_STEERING_ANGLE_SENSOR = 0x1021,
    
    /* Actuator DTCs */
    DTC_HYDRAULIC_PUMP = 0x2001,
    DTC_INLET_VALVE_FL = 0x2010,
    DTC_INLET_VALVE_FR = 0x2011,
    DTC_INLET_VALVE_RL = 0x2012,
    DTC_INLET_VALVE_RR = 0x2013,
    DTC_OUTLET_VALVE_FL = 0x2020,
    DTC_OUTLET_VALVE_FR = 0x2021,
    DTC_OUTLET_VALVE_RL = 0x2022,
    DTC_OUTLET_VALVE_RR = 0x2023,
    
    /* System DTCs */
    DTC_SYSTEM_VOLTAGE_LOW = 0x3001,
    DTC_SYSTEM_VOLTAGE_HIGH = 0x3002,
    DTC_SYSTEM_TEMPERATURE_HIGH = 0x3003,
    DTC_CAN_BUS_OFF = 0x3010,
    DTC_CAN_ERROR_PASSIVE = 0x3011,
    
    /* Self-Test DTCs */
    DTC_SENSOR_SELF_TEST_FAILED = 0x4001,
    DTC_ACTUATOR_SELF_TEST_FAILED = 0x4002,
    DTC_COMMUNICATION_SELF_TEST_FAILED = 0x4003,
    DTC_SAFETY_SELF_TEST_FAILED = 0x4004,
    DTC_ALGORITHM_SELF_TEST_FAILED = 0x4005,
    
    /* Safety DTCs */
    DTC_SAFETY_CRITICAL_FAULT = 0x5001,
    DTC_WATCHDOG_TIMEOUT = 0x5002,
    DTC_MEMORY_CORRUPTION = 0x5003,
    DTC_DUAL_CHANNEL_MISMATCH = 0x5004
} ebs_dtc_code_t;

/* DTC Status */
typedef enum {
    DTC_STATUS_INACTIVE = 0x00,
    DTC_STATUS_ACTIVE = 0x01,
    DTC_STATUS_PENDING = 0x02,
    DTC_STATUS_CONFIRMED = 0x04,
    DTC_STATUS_TEST_FAILED = 0x08,
    DTC_STATUS_TEST_NOT_COMPLETED = 0x10
} ebs_dtc_status_t;

/* Diagnostic Event Types */
typedef enum {
    DIAG_EVENT_SYSTEM_START = 0x01,
    DIAG_EVENT_SYSTEM_SHUTDOWN = 0x02,
    DIAG_EVENT_SAFETY_WARNING = 0x10,
    DIAG_EVENT_SAFETY_DEGRADED = 0x11,
    DIAG_EVENT_SAFETY_SAFE_STATE = 0x12,
    DIAG_EVENT_ABS_ACTIVATION = 0x20,
    DIAG_EVENT_ESC_ACTIVATION = 0x21,
    DIAG_EVENT_TCS_ACTIVATION = 0x22,
    DIAG_EVENT_SENSOR_FAULT = 0x30,
    DIAG_EVENT_ACTUATOR_FAULT = 0x31,
    DIAG_EVENT_COMMUNICATION_FAULT = 0x32
} ebs_diag_event_t;

/* Watchdog Types */
typedef enum {
    WATCHDOG_MAIN_TASK = 0,
    WATCHDOG_SAFETY_TASK,
    WATCHDOG_ABS_TASK,
    WATCHDOG_ESC_TASK,
    WATCHDOG_TCS_TASK,
    WATCHDOG_COMMUNICATION_TASK,
    WATCHDOG_DIAGNOSTIC_TASK,
    WATCHDOG_EMERGENCY,
    WATCHDOG_SHUTDOWN,
    WATCHDOG_COUNT
} ebs_watchdog_type_t;

/* CAN Message IDs */
#define CAN_MSG_EBS_STATUS          0x100
#define CAN_MSG_EBS_WHEEL_SPEED     0x101
#define CAN_MSG_ENGINE_TORQUE_REQ   0x102
#define CAN_MSG_ENGINE_STATUS       0x280
#define CAN_MSG_DIAGNOSTIC_REQ      0x7E0
#define CAN_MSG_DIAGNOSTIC_RESP     0x7E8

/* System Constants */
#define EBS_CYCLE_TIME_MS           1U      /* Main cycle time in milliseconds */
#define EBS_MAX_WHEEL_SPEED         300.0f  /* Maximum wheel speed in km/h */
#define EBS_MAX_BRAKE_PRESSURE      250.0f  /* Maximum brake pressure in bar */
#define EBS_MAX_YAW_RATE           300.0f   /* Maximum yaw rate in deg/s */
#define EBS_MAX_LATERAL_ACCEL      20.0f    /* Maximum lateral acceleration in m/s² */

/* Algorithm Parameters */
#define ABS_SLIP_THRESHOLD          0.15f   /* ABS activation slip threshold */
#define ABS_SLIP_TARGET             0.10f   /* ABS target slip ratio */
#define ESC_YAW_RATE_THRESHOLD      5.0f    /* ESC activation threshold in deg/s */
#define TCS_SLIP_THRESHOLD          0.10f   /* TCS activation slip threshold */
#define TCS_SLIP_TARGET             0.05f   /* TCS target slip ratio */

/* Safety Limits */
#define SAFETY_MAX_SENSOR_AGE_MS    100U    /* Maximum sensor data age in ms */
#define SAFETY_MAX_FAULT_COUNT      3U      /* Maximum fault count before safe state */
#define SAFETY_WATCHDOG_TIMEOUT_MS  100U    /* Watchdog timeout in ms */

/* Memory Layout */
#define EBS_FLASH_SIZE              (8U * 1024U * 1024U)  /* 8MB Flash */
#define EBS_RAM_SIZE                (1U * 1024U * 1024U)  /* 1MB RAM */
#define EBS_EEPROM_SIZE             (64U * 1024U)         /* 64KB EEPROM */

/* Function Return Codes */
typedef enum {
    EBS_OK = 0,
    EBS_ERROR,
    EBS_INVALID_PARAM,
    EBS_NOT_INITIALIZED,
    EBS_TIMEOUT,
    EBS_BUSY,
    EBS_FAULT
} ebs_result_t;

/* Function Prototypes */
uint32_t EBS_GetSystemTick(void);

#endif /* EBS_TYPES_H */
