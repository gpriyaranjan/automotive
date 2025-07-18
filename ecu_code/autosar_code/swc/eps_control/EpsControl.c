#include "EpsControl.h"
#include "Rte_EpsControl.h"
#include "Det.h"
#include "Dem.h"
#include "SchM_EpsControl.h"

/* Private Constants */
#define EPS_ASSIST_MAP_SIZE_X    10  /* Driver torque points */
#define EPS_ASSIST_MAP_SIZE_Y    8   /* Vehicle speed points */

/* Private Variables */
static EpsControlData_t eps_control_data;
static float previous_steering_angle = 0.0f;
static uint32_t system_ticks = 0;

/* Assist Torque Lookup Table (Base assist mapping) */
static const float assist_torque_map[EPS_ASSIST_MAP_SIZE_X][EPS_ASSIST_MAP_SIZE_Y] = {
    /* Speed: 0, 10, 20, 30, 40, 50, 60, 70 km/h */
    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},  /* 0 Nm driver torque */
    {2.0f, 1.8f, 1.5f, 1.2f, 1.0f, 0.8f, 0.6f, 0.4f},  /* 1 Nm driver torque */
    {4.0f, 3.6f, 3.0f, 2.4f, 2.0f, 1.6f, 1.2f, 0.8f},  /* 2 Nm driver torque */
    {6.0f, 5.4f, 4.5f, 3.6f, 3.0f, 2.4f, 1.8f, 1.2f},  /* 3 Nm driver torque */
    {8.0f, 7.2f, 6.0f, 4.8f, 4.0f, 3.2f, 2.4f, 1.6f},  /* 4 Nm driver torque */
    {10.0f, 9.0f, 7.5f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f}, /* 5 Nm driver torque */
    {12.0f, 10.8f, 9.0f, 7.2f, 6.0f, 4.8f, 3.6f, 2.4f}, /* 6 Nm driver torque */
    {14.0f, 12.6f, 10.5f, 8.4f, 7.0f, 5.6f, 4.2f, 2.8f}, /* 7 Nm driver torque */
    {16.0f, 14.4f, 12.0f, 9.6f, 8.0f, 6.4f, 4.8f, 3.2f}, /* 8 Nm driver torque */
    {18.0f, 16.2f, 13.5f, 10.8f, 9.0f, 7.2f, 5.4f, 3.6f} /* 9 Nm driver torque */
};

/* Private Function Prototypes */
static float EpsControl_LookupAssistTorque(float driver_torque, float vehicle_speed);
static float EpsControl_Interpolate2D(float x, float y, const float map[EPS_ASSIST_MAP_SIZE_X][EPS_ASSIST_MAP_SIZE_Y]);
static void EpsControl_UpdateSteeringVelocity(void);
static void EpsControl_ApplyLimits(float* assist_torque);

/* Function Implementations */

Std_ReturnType EpsControl_Init(void)
{
    Std_ReturnType result = E_OK;
    
    /* Initialize control data structure */
    memset(&eps_control_data, 0, sizeof(EpsControlData_t));
    eps_control_data.system_state = EPS_STATE_INIT;
    eps_control_data.fault_code = EPS_FAULT_NONE;
    
    /* Initialize previous values */
    previous_steering_angle = 0.0f;
    system_ticks = 0;
    
    /* Report initialization to DET if configured */
    #ifdef DET_ENABLED
    Det_ReportError(EPS_CONTROL_MODULE_ID, 0, EPS_CONTROL_INIT_SID, DET_EPS_CONTROL_INIT_OK);
    #endif
    
    /* Transition to normal state */
    eps_control_data.system_state = EPS_STATE_NORMAL;
    
    return result;
}

Std_ReturnType EpsControl_MainFunction(EpsControlData_t* control_data)
{
    Std_ReturnType result = E_OK;
    
    if (control_data == NULL) {
        return E_NOT_OK;
    }
    
    /* Update system tick counter */
    system_ticks++;
    
    /* Update steering angular velocity */
    EpsControl_UpdateSteeringVelocity();
    
    /* Perform fault detection */
    if (EpsControl_FaultDetection(control_data) != E_OK) {
        /* Fault detected - handle in state management */
    }
    
    /* Handle system state transitions */
    EpsControl_StateManagement(control_data);
    
    /* Execute control algorithm based on system state */
    switch (control_data->system_state) {
        case EPS_STATE_NORMAL:
            /* Calculate assist torque */
            control_data->target_assist_torque = EpsControl_CalculateAssistTorque(
                control_data->driver_torque,
                control_data->vehicle_speed,
                control_data->steering_angle,
                control_data->steering_angular_velocity
            );
            
            /* Convert to motor current command */
            control_data->motor_current_command = EpsControl_ConvertTorqueToCurrent(
                control_data->target_assist_torque
            );
            break;
            
        case EPS_STATE_FAULT:
        case EPS_STATE_SAFE_MODE:
            /* Reduced assist or no assist based on fault type */
            control_data->target_assist_torque = 0.0f;
            control_data->motor_current_command = 0.0f;
            break;
            
        case EPS_STATE_INIT:
        default:
            /* No action in init state */
            break;
    }
    
    /* Update previous steering angle for next iteration */
    previous_steering_angle = control_data->steering_angle;
    
    return result;
}

float EpsControl_CalculateAssistTorque(float driver_torque, 
                                     float vehicle_speed,
                                     float steering_angle,
                                     float steering_angular_velocity)
{
    float assist_torque = 0.0f;
    
    /* Step 1: Base assist mapping */
    assist_torque = EpsControl_LookupAssistTorque(driver_torque, vehicle_speed);
    
    /* Step 2: Add damping component */
    assist_torque += EpsControl_CalculateDampingComponent(steering_angular_velocity);
    
    /* Step 3: Add return-to-center component */
    assist_torque += EpsControl_CalculateRTCComponent(steering_angle, vehicle_speed);
    
    /* Step 4: Apply ADAS override if active */
    if (eps_control_data.adas_active) {
        assist_torque = eps_control_data.adas_command_torque;
    }
    
    /* Step 5: Apply limits */
    EpsControl_ApplyLimits(&assist_torque);
    
    return assist_torque;
}

float EpsControl_CalculateRTCComponent(float steering_angle, float vehicle_speed)
{
    float rtc_component = 0.0f;
    
    /* Apply return-to-center logic only at low speeds */
    if (vehicle_speed < EPS_LOW_SPEED_THRESHOLD && 
        fabs(steering_angle) > EPS_RTC_ANGLE_THRESHOLD) {
        
        /* RTC torque proportional to steering angle and inversely proportional to speed */
        float speed_factor = 1.0f - (vehicle_speed / EPS_LOW_SPEED_THRESHOLD);
        rtc_component = -0.5f * steering_angle * speed_factor;
        
        /* Limit RTC component */
        if (rtc_component > 5.0f) rtc_component = 5.0f;
        if (rtc_component < -5.0f) rtc_component = -5.0f;
    }
    
    return rtc_component;
}

float EpsControl_CalculateDampingComponent(float steering_angular_velocity)
{
    float damping_component = 0.0f;
    
    /* Damping proportional to steering angular velocity */
    /* Negative sign to oppose rapid steering movements */
    damping_component = -0.1f * steering_angular_velocity;
    
    /* Limit damping component */
    if (damping_component > 3.0f) damping_component = 3.0f;
    if (damping_component < -3.0f) damping_component = -3.0f;
    
    return damping_component;
}

float EpsControl_ConvertTorqueToCurrent(float assist_torque)
{
    float motor_current = 0.0f;
    
    /* Simple linear conversion from torque to current */
    /* This would be calibrated based on motor characteristics */
    motor_current = assist_torque * 2.0f; /* 2 A per Nm (example) */
    
    /* Apply current limits */
    if (motor_current > 100.0f) motor_current = 100.0f;
    if (motor_current < -100.0f) motor_current = -100.0f;
    
    return motor_current;
}

Std_ReturnType EpsControl_FaultDetection(EpsControlData_t* control_data)
{
    Std_ReturnType result = E_OK;
    
    /* Check sensor validity */
    if (control_data->driver_torque < -20.0f || control_data->driver_torque > 20.0f) {
        control_data->fault_code = EPS_FAULT_TORQUE_SENSOR;
        result = E_NOT_OK;
    }
    
    if (control_data->steering_angle < -720.0f || control_data->steering_angle > 720.0f) {
        control_data->fault_code = EPS_FAULT_ANGLE_SENSOR;
        result = E_NOT_OK;
    }
    
    if (control_data->vehicle_speed < 0.0f || control_data->vehicle_speed > 300.0f) {
        control_data->fault_code = EPS_FAULT_SPEED_SENSOR;
        result = E_NOT_OK;
    }
    
    /* Check motor current limits (would be implemented with actual motor feedback) */
    if (fabs(control_data->motor_current_command) > 100.0f) {
        control_data->fault_code = EPS_FAULT_MOTOR_OVERCURRENT;
        result = E_NOT_OK;
    }
    
    /* Report faults to DEM if configured */
    #ifdef DEM_ENABLED
    if (result != E_OK) {
        Dem_SetEventStatus(EPS_FAULT_EVENT_ID, DEM_EVENT_STATUS_FAILED);
    }
    #endif
    
    return result;
}

void EpsControl_StateManagement(EpsControlData_t* control_data)
{
    EpsSystemState_t previous_state = control_data->system_state;
    
    /* State transition logic */
    switch (control_data->system_state) {
        case EPS_STATE_INIT:
            /* Transition to normal after initialization */
            control_data->system_state = EPS_STATE_NORMAL;
            break;
            
        case EPS_STATE_NORMAL:
            /* Check for faults */
            if (control_data->fault_code != EPS_FAULT_NONE) {
                control_data->system_state = EPS_STATE_FAULT;
            }
            break;
            
        case EPS_STATE_FAULT:
            /* Check if fault is cleared */
            if (control_data->fault_code == EPS_FAULT_NONE) {
                control_data->system_state = EPS_STATE_NORMAL;
            } else {
                /* Transition to safe mode for critical faults */
                if (control_data->fault_code == EPS_FAULT_MOTOR_OVERCURRENT ||
                    control_data->fault_code == EPS_FAULT_ECU_INTERNAL_ERROR) {
                    control_data->system_state = EPS_STATE_SAFE_MODE;
                }
            }
            break;
            
        case EPS_STATE_SAFE_MODE:
            /* Safe mode requires manual reset or fault clearance */
            break;
    }
    
    /* Report state change if configured */
    if (previous_state != control_data->system_state) {
        #ifdef DET_ENABLED
        Det_ReportError(EPS_CONTROL_MODULE_ID, 0, EPS_CONTROL_STATE_CHANGE_SID, 
                       (uint16_t)control_data->system_state);
        #endif
    }
}

Std_ReturnType EpsControl_DeInit(void)
{
    Std_ReturnType result = E_OK;
    
    /* Reset control data */
    memset(&eps_control_data, 0, sizeof(EpsControlData_t));
    eps_control_data.system_state = EPS_STATE_INIT;
    
    return result;
}

/* Private Function Implementations */

static float EpsControl_LookupAssistTorque(float driver_torque, float vehicle_speed)
{
    /* Use 2D interpolation to get assist torque from lookup table */
    return EpsControl_Interpolate2D(driver_torque, vehicle_speed, assist_torque_map);
}

static float EpsControl_Interpolate2D(float x, float y, const float map[EPS_ASSIST_MAP_SIZE_X][EPS_ASSIST_MAP_SIZE_Y])
{
    /* Simple bilinear interpolation implementation */
    /* This is a simplified version - in practice, more sophisticated interpolation would be used */
    
    /* Clamp inputs to valid range */
    if (x < 0.0f) x = 0.0f;
    if (x > 9.0f) x = 9.0f;
    if (y < 0.0f) y = 0.0f;
    if (y > 70.0f) y = 70.0f;
    
    /* Find grid indices */
    int x_idx = (int)x;
    int y_idx = (int)(y / 10.0f);
    
    if (x_idx >= EPS_ASSIST_MAP_SIZE_X - 1) x_idx = EPS_ASSIST_MAP_SIZE_X - 2;
    if (y_idx >= EPS_ASSIST_MAP_SIZE_Y - 1) y_idx = EPS_ASSIST_MAP_SIZE_Y - 2;
    
    /* Get interpolation weights */
    float x_weight = x - x_idx;
    float y_weight = (y - y_idx * 10.0f) / 10.0f;
    
    /* Bilinear interpolation */
    float c00 = map[x_idx][y_idx];
    float c01 = map[x_idx][y_idx + 1];
    float c10 = map[x_idx + 1][y_idx];
    float c11 = map[x_idx + 1][y_idx + 1];
    
    float result = c00 * (1.0f - x_weight) * (1.0f - y_weight) +
                   c01 * (1.0f - x_weight) * y_weight +
                   c10 * x_weight * (1.0f - y_weight) +
                   c11 * x_weight * y_weight;
    
    return result;
}

static void EpsControl_UpdateSteeringVelocity(void)
{
    /* Calculate steering angular velocity from angle difference */
    float angle_diff = eps_control_data.steering_angle - previous_steering_angle;
    
    /* Convert to angular velocity (deg/s) assuming 1ms sampling rate */
    eps_control_data.steering_angular_velocity = angle_diff * 1000.0f;
    
    /* Apply low-pass filter to reduce noise */
    eps_control_data.steering_angular_velocity *= 0.9f;
}

static void EpsControl_ApplyLimits(float* assist_torque)
{
    if (assist_torque != NULL) {
        if (*assist_torque > EPS_MAX_ASSIST_TORQUE) {
            *assist_torque = EPS_MAX_ASSIST_TORQUE;
        }
        if (*assist_torque < EPS_MIN_ASSIST_TORQUE) {
            *assist_torque = EPS_MIN_ASSIST_TORQUE;
        }
    }
} 