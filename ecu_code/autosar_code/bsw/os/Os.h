#ifndef OS_H
#define OS_H

#include "Std_Types.h"
#include "Os_Cfg.h"

/* AUTOSAR OS Version Information */
#define OS_SW_MAJOR_VERSION    4
#define OS_SW_MINOR_VERSION    4
#define OS_SW_PATCH_VERSION    0

/* OS Module ID */
#define OS_MODULE_ID           0x2000

/* OS Service IDs */
#define OS_SID_STARTOS        0x01
#define OS_SID_SHUTDOWNOS     0x02
#define OS_SID_ACTIVATETASK   0x03
#define OS_SID_TERMINATETASK  0x04
#define OS_SID_SCHEDULE       0x05
#define OS_SID_GETTASKID      0x06
#define OS_SID_GETTASKSTATE   0x07
#define OS_SID_DISABLEALLINTERRUPTS 0x08
#define OS_SID_ENABLEALLINTERRUPTS  0x09
#define OS_SID_SUSPENDALLINTERRUPTS 0x0A
#define OS_SID_RESUMEALLINTERRUPTS  0x0B
#define OS_SID_SUSPENDOSINTERRUPTS  0x0C
#define OS_SID_RESUMEOSINTERRUPTS   0x0D
#define OS_SID_GETISRID       0x0E
#define OS_SID_GETRESOURCE    0x0F
#define OS_SID_RELEASERESOURCE 0x10
#define OS_SID_SETEVENT       0x11
#define OS_SID_CLEAREVENT     0x12
#define OS_SID_GETEVENT       0x13
#define OS_SID_WAITEVENT      0x14
#define OS_SID_GETALARMBASE   0x15
#define OS_SID_GETALARM       0x16
#define OS_SID_SETRELALARM    0x17
#define OS_SID_SETABSALARM    0x18
#define OS_SID_CANCELALARM    0x19
#define OS_SID_GETACTIVEAPPLICATIONMODE 0x1A
#define OS_SID_SHUTDOWNOS     0x1B
#define OS_SID_STARTOS        0x1C

/* OS Error Codes */
#define OS_E_OK               0x00
#define OS_E_OS_ID            0x01
#define OS_E_OS_LIMIT         0x02
#define OS_E_OS_NOFUNC        0x03
#define OS_E_OS_RESOURCE      0x04
#define OS_E_OS_TIMEOUT       0x05
#define OS_E_OS_STATE         0x06
#define OS_E_OS_VALUE         0x07

/* Task States */
typedef enum {
    OS_TASK_SUSPENDED = 0,
    OS_TASK_READY,
    OS_TASK_RUNNING,
    OS_TASK_WAITING
} OsTaskState_t;

/* Task Priorities */
#define OS_TASK_PRIORITY_LOWEST    0
#define OS_TASK_PRIORITY_LOW       1
#define OS_TASK_PRIORITY_NORMAL    2
#define OS_TASK_PRIORITY_HIGH      3
#define OS_TASK_PRIORITY_HIGHEST   4

/* Task IDs for EPS System */
typedef enum {
    OS_TASK_ID_INVALID = 0,
    OS_TASK_ID_EPS_CONTROL,          /* Main EPS control task */
    OS_TASK_ID_SENSOR_INTERFACE,     /* Sensor data acquisition task */
    OS_TASK_ID_MOTOR_CONTROL,        /* Motor control task */
    OS_TASK_ID_FAULT_MANAGEMENT,     /* Fault management task */
    OS_TASK_ID_COMMUNICATION,        /* Communication task */
    OS_TASK_ID_WATCHDOG,             /* Watchdog task */
    OS_TASK_ID_IDLE,                 /* Idle task */
    OS_TASK_ID_MAX
} OsTaskId_t;

/* ISR IDs for EPS System */
typedef enum {
    OS_ISR_ID_INVALID = 0,
    OS_ISR_ID_TIMER_1MS,             /* 1ms timer interrupt */
    OS_ISR_ID_CAN_RX,                /* CAN receive interrupt */
    OS_ISR_ID_ADC_COMPLETE,          /* ADC conversion complete */
    OS_ISR_ID_MOTOR_FAULT,           /* Motor fault interrupt */
    OS_ISR_ID_WATCHDOG_TIMEOUT,      /* Watchdog timeout interrupt */
    OS_ISR_ID_MAX
} OsIsrId_t;

/* Resource IDs for EPS System */
typedef enum {
    OS_RESOURCE_ID_INVALID = 0,
    OS_RESOURCE_ID_SENSOR_DATA,      /* Sensor data access resource */
    OS_RESOURCE_ID_MOTOR_CONTROL,    /* Motor control resource */
    OS_RESOURCE_ID_FAULT_MANAGEMENT, /* Fault management resource */
    OS_RESOURCE_ID_COMMUNICATION,    /* Communication resource */
    OS_RESOURCE_ID_MAX
} OsResourceId_t;

/* Event IDs for EPS System */
typedef enum {
    OS_EVENT_ID_INVALID = 0,
    OS_EVENT_ID_SENSOR_DATA_READY,   /* Sensor data ready event */
    OS_EVENT_ID_MOTOR_COMMAND_READY, /* Motor command ready event */
    OS_EVENT_ID_FAULT_DETECTED,      /* Fault detected event */
    OS_EVENT_ID_COMMUNICATION_RX,    /* Communication receive event */
    OS_EVENT_ID_WATCHDOG_TRIGGER,    /* Watchdog trigger event */
    OS_EVENT_ID_MAX
} OsEventId_t;

/* Alarm IDs for EPS System */
typedef enum {
    OS_ALARM_ID_INVALID = 0,
    OS_ALARM_ID_EPS_CONTROL_PERIODIC,    /* EPS control periodic alarm */
    OS_ALARM_ID_SENSOR_ACQUISITION,      /* Sensor acquisition alarm */
    OS_ALARM_ID_MOTOR_CONTROL_PERIODIC,  /* Motor control periodic alarm */
    OS_ALARM_ID_FAULT_DIAGNOSIS,         /* Fault diagnosis alarm */
    OS_ALARM_ID_WATCHDOG_PERIODIC,       /* Watchdog periodic alarm */
    OS_ALARM_ID_MAX
} OsAlarmId_t;

/* Application Mode IDs */
typedef enum {
    OS_APPLICATION_MODE_INVALID = 0,
    OS_APPLICATION_MODE_NORMAL,      /* Normal operation mode */
    OS_APPLICATION_MODE_SAFE,        /* Safe mode */
    OS_APPLICATION_MODE_FAULT,       /* Fault mode */
    OS_APPLICATION_MODE_CALIBRATION, /* Calibration mode */
    OS_APPLICATION_MODE_MAX
} OsApplicationMode_t;

/* OS Configuration Structure */
typedef struct {
    uint8_t task_count;              /* Number of tasks */
    uint8_t isr_count;               /* Number of ISRs */
    uint8_t resource_count;          /* Number of resources */
    uint8_t event_count;             /* Number of events */
    uint8_t alarm_count;             /* Number of alarms */
    uint8_t application_mode_count;  /* Number of application modes */
    uint32_t system_tick_period_ms;  /* System tick period in milliseconds */
} OsConfig_t;

/* Task Configuration Structure */
typedef struct {
    OsTaskId_t task_id;              /* Task ID */
    uint8_t priority;                /* Task priority */
    uint32_t stack_size;             /* Stack size in bytes */
    uint32_t activation_count;       /* Number of activations */
    boolean auto_start;              /* Auto-start flag */
    OsApplicationMode_t app_mode;    /* Application mode */
    void (*task_function)(void);     /* Task function pointer */
} OsTaskConfig_t;

/* ISR Configuration Structure */
typedef struct {
    OsIsrId_t isr_id;                /* ISR ID */
    uint8_t priority;                /* ISR priority */
    void (*isr_function)(void);      /* ISR function pointer */
} OsIsrConfig_t;

/* Resource Configuration Structure */
typedef struct {
    OsResourceId_t resource_id;      /* Resource ID */
    uint8_t ceiling_priority;        /* Ceiling priority */
} OsResourceConfig_t;

/* Event Configuration Structure */
typedef struct {
    OsEventId_t event_id;            /* Event ID */
    OsTaskId_t task_id;              /* Associated task ID */
} OsEventConfig_t;

/* Alarm Configuration Structure */
typedef struct {
    OsAlarmId_t alarm_id;            /* Alarm ID */
    uint32_t period_ms;              /* Alarm period in milliseconds */
    OsEventId_t event_id;            /* Associated event ID */
    boolean auto_start;              /* Auto-start flag */
} OsAlarmConfig_t;

/* Function Prototypes */

/* OS Management Functions */

/**
 * @brief Start the AUTOSAR Operating System
 * @param app_mode Application mode to start
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType StartOS(OsApplicationModeType app_mode);

/**
 * @brief Shutdown the AUTOSAR Operating System
 * @param error_code Error code for shutdown
 */
void ShutdownOS(StatusType error_code);

/**
 * @brief Get the current application mode
 * @return OsApplicationModeType Current application mode
 */
OsApplicationModeType GetActiveApplicationMode(void);

/* Task Management Functions */

/**
 * @brief Activate a task
 * @param task_id Task ID to activate
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType ActivateTask(TaskType task_id);

/**
 * @brief Terminate the calling task
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType TerminateTask(void);

/**
 * @brief Chain a task (terminate current and activate another)
 * @param task_id Task ID to chain to
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType ChainTask(TaskType task_id);

/**
 * @brief Schedule the system
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType Schedule(void);

/**
 * @brief Get the ID of the currently running task
 * @return TaskType Current task ID
 */
TaskType GetTaskID(void);

/**
 * @brief Get the state of a task
 * @param task_id Task ID
 * @param state Pointer to store task state
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType GetTaskState(TaskType task_id, TaskStateRefType state);

/* Interrupt Management Functions */

/**
 * @brief Disable all interrupts
 * @return ISRType Previous interrupt state
 */
ISRType DisableAllInterrupts(void);

/**
 * @brief Enable all interrupts
 * @param previous_state Previous interrupt state
 */
void EnableAllInterrupts(ISRType previous_state);

/**
 * @brief Suspend all interrupts
 * @return ISRType Previous interrupt state
 */
ISRType SuspendAllInterrupts(void);

/**
 * @brief Resume all interrupts
 * @param previous_state Previous interrupt state
 */
void ResumeAllInterrupts(ISRType previous_state);

/**
 * @brief Suspend OS interrupts
 * @return ISRType Previous interrupt state
 */
ISRType SuspendOSInterrupts(void);

/**
 * @brief Resume OS interrupts
 * @param previous_state Previous interrupt state
 */
void ResumeOSInterrupts(ISRType previous_state);

/**
 * @brief Get the ID of the currently running ISR
 * @return ISRType Current ISR ID
 */
ISRType GetISRID(void);

/* Resource Management Functions */

/**
 * @brief Get a resource
 * @param resource_id Resource ID
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType GetResource(ResourceType resource_id);

/**
 * @brief Release a resource
 * @param resource_id Resource ID
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType ReleaseResource(ResourceType resource_id);

/* Event Management Functions */

/**
 * @brief Set an event for a task
 * @param task_id Task ID
 * @param event_mask Event mask
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType SetEvent(TaskType task_id, EventMaskType event_mask);

/**
 * @brief Clear an event for the calling task
 * @param event_mask Event mask to clear
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType ClearEvent(EventMaskType event_mask);

/**
 * @brief Get the event mask of the calling task
 * @return EventMaskType Current event mask
 */
EventMaskType GetEvent(TaskType task_id);

/**
 * @brief Wait for an event
 * @param event_mask Event mask to wait for
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType WaitEvent(EventMaskType event_mask);

/* Alarm Management Functions */

/**
 * @brief Get alarm base information
 * @param alarm_id Alarm ID
 * @param info Pointer to store alarm base information
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType GetAlarmBase(AlarmType alarm_id, AlarmBaseRefType info);

/**
 * @brief Get alarm information
 * @param alarm_id Alarm ID
 * @param info Pointer to store alarm information
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType GetAlarm(AlarmType alarm_id, TickRefType tick);

/**
 * @brief Set a relative alarm
 * @param alarm_id Alarm ID
 * @param increment Alarm increment
 * @param cycle Alarm cycle
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType SetRelAlarm(AlarmType alarm_id, TickType increment, TickType cycle);

/**
 * @brief Set an absolute alarm
 * @param alarm_id Alarm ID
 * @param start Alarm start time
 * @param cycle Alarm cycle
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType SetAbsAlarm(AlarmType alarm_id, TickType start, TickType cycle);

/**
 * @brief Cancel an alarm
 * @param alarm_id Alarm ID
 * @return Status - E_OK if successful, E_NOT_OK otherwise
 */
StatusType CancelAlarm(AlarmType alarm_id);

/* EPS System Specific Task Functions */

/**
 * @brief EPS Control Task Function
 */
void EpsControlTask(void);

/**
 * @brief Sensor Interface Task Function
 */
void SensorInterfaceTask(void);

/**
 * @brief Motor Control Task Function
 */
void MotorControlTask(void);

/**
 * @brief Fault Management Task Function
 */
void FaultManagementTask(void);

/**
 * @brief Communication Task Function
 */
void CommunicationTask(void);

/**
 * @brief Watchdog Task Function
 */
void WatchdogTask(void);

/**
 * @brief Idle Task Function
 */
void IdleTask(void);

#endif /* OS_H */ 