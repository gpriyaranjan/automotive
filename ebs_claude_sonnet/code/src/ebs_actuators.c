/**
 * @file ebs_actuators.c
 * @brief Electronic Braking System - Actuator Control Implementation
 * @version 1.0
 * @date 2025-07-29
 * @author EBS Development Team
 * 
 * Actuator control implementation for EBS system
 * 
 * Safety Level: ASIL-D
 * Compliance: ISO 26262, MISRA C:2012
 */

#include "ebs_actuators.h"
#include "ebs_safety.h"
#include "ebs_diagnostics.h"
#include <string.h>
#include <math.h>

/* Static Variables */
static ebs_actuator_manager_t g_actuator_manager;
static bool g_actuators_initialized = false;

/* Static Function Prototypes */
static ebs_result_t Actuators_InitializeHydraulicModulator(void);
static ebs_result_t Actuators_InitializePumpMotor(void);
static ebs_result_t Actuators_InitializeValves(void);
static ebs_result_t Actuators_UpdateHydraulicModulator(void);
static ebs_result_t Actuators_UpdatePumpMotor(void);
static ebs_result_t Actuators_UpdateValves(void);
static bool Actuators_ValidatePressureCommand(ebs_wheel_position_t wheel, float pressure);
static void Actuators_UpdateDiagnostics(void);
static ebs_result_t Actuators_SetValvePosition(ebs_valve_id_t valve_id, float position);
static float Actuators_CalculatePWMDutyCycle(float command);

/**
 * @brief Initialize actuator subsystem
 * @return ebs_result_t Initialization result
 */
ebs_result_t EBS_Actuators_Init(void)
{
    /* Clear actuator manager state */
    memset(&g_actuator_manager, 0, sizeof(g_actuator_manager));
    
    /* Initialize hydraulic modulator */
    if (Actuators_InitializeHydraulicModulator() != EBS_OK) {
        return EBS_ERROR;
    }
    
    /* Initialize pump motor */
    if (Actuators_InitializePumpMotor() != EBS_OK) {
        return EBS_ERROR;
    }
    
    /* Initialize valves */
    if (Actuators_InitializeValves() != EBS_OK) {
        return EBS_ERROR;
    }
    
    /* Initialize actuator manager state */
    g_actuator_manager.system_enabled = true;
    g_actuator_manager.last_update_time = EBS_GetSystemTick();
    g_actuator_manager.update_count = 0;
    
    g_actuators_initialized = true;
    
    return EBS_OK;
}

/**
 * @brief Perform actuator self-test
 * @return bool True if self-test passed
 */
bool EBS_Actuators_SelfTest(void)
{
    if (!g_actuators_initialized) {
        return false;
    }
    
    bool test_passed = true;
    
    /* Test hydraulic modulator */
    ebs_hydraulic_modulator_t* modulator = &g_actuator_manager.hydraulic_modulator;
    if (modulator->max_pressure <= modulator->min_pressure) {
        test_passed = false;
    }
    
    /* Test pump motor */
    ebs_pump_motor_t* pump = &g_actuator_manager.pump_motor;
    if (pump->max_speed <= 0.0f || pump->max_current <= 0.0f) {
        test_passed = false;
    }
    
    /* Test valves */
    for (uint32_t valve = 0; valve < VALVE_COUNT; valve++) {
        ebs_valve_t* valve_ptr = &g_actuator_manager.valves[valve];
        if (valve_ptr->max_flow_rate <= 0.0f) {
            test_passed = false;
        }
    }
    
    /* Test pressure command validation */
    if (!Actuators_ValidatePressureCommand(WHEEL_FRONT_LEFT, 50.0f)) {
        test_passed = false;
    }
    
    /* Test PWM calculation */
    float test_pwm = Actuators_CalculatePWMDutyCycle(0.5f);
    if (test_pwm < 0.0f || test_pwm > 100.0f) {
        test_passed = false;
    }
    
    return test_passed;
}

/**
 * @brief Update all actuators (called every cycle)
 * @return ebs_result_t Update result
 */
ebs_result_t EBS_Actuators_Update(void)
{
    if (!g_actuators_initialized || !g_actuator_manager.system_enabled) {
        return EBS_NOT_INITIALIZED;
    }
    
    ebs_result_t result = EBS_OK;
    
    /* Update hydraulic modulator */
    if (Actuators_UpdateHydraulicModulator() != EBS_OK) {
        result = EBS_ERROR;
    }
    
    /* Update pump motor */
    if (Actuators_UpdatePumpMotor() != EBS_OK) {
        result = EBS_ERROR;
    }
    
    /* Update valves */
    if (Actuators_UpdateValves() != EBS_OK) {
        result = EBS_ERROR;
    }
    
    /* Update diagnostics */
    Actuators_UpdateDiagnostics();
    
    /* Update manager state */
    g_actuator_manager.last_update_time = EBS_GetSystemTick();
    g_actuator_manager.update_count++;
    
    return result;
}

/**
 * @brief Set brake pressure for specific wheel
 * @param wheel Wheel position
 * @param pressure Pressure command (0.0 to 1.0)
 * @return ebs_result_t Set result
 */
ebs_result_t EBS_Actuators_SetPressure(ebs_wheel_position_t wheel, float pressure)
{
    if (!g_actuators_initialized || !ABS_IS_WHEEL_VALID(wheel)) {
        return EBS_INVALID_PARAM;
    }
    
    /* Validate pressure command */
    if (!Actuators_ValidatePressureCommand(wheel, pressure)) {
        return EBS_INVALID_PARAM;
    }
    
    /* Store pressure command */
    g_actuator_manager.pressure_commands[wheel] = pressure;
    g_actuator_manager.command_timestamps[wheel] = EBS_GetSystemTick();
    
    /* Convert pressure command to valve positions */
    ebs_valve_id_t inlet_valve = (ebs_valve_id_t)(VALVE_INLET_FL + wheel);
    ebs_valve_id_t outlet_valve = (ebs_valve_id_t)(VALVE_OUTLET_FL + wheel);
    
    /* Calculate valve positions based on pressure command */
    float inlet_position = pressure;  /* Direct mapping for now */
    float outlet_position = (pressure < 1.0f) ? (1.0f - pressure) : 0.0f;
    
    /* Set valve positions */
    if (Actuators_SetValvePosition(inlet_valve, inlet_position) != EBS_OK) {
        return EBS_ERROR;
    }
    
    if (Actuators_SetValvePosition(outlet_valve, outlet_position) != EBS_OK) {
        return EBS_ERROR;
    }
    
    return EBS_OK;
}

/**
 * @brief Get current brake pressure for wheel
 * @param wheel Wheel position
 * @return float Current pressure (0.0 to 1.0)
 */
float EBS_Actuators_GetPressure(ebs_wheel_position_t wheel)
{
    if (!g_actuators_initialized || !ABS_IS_WHEEL_VALID(wheel)) {
        return 0.0f;
    }
    
    return g_actuator_manager.pressure_commands[wheel];
}

/**
 * @brief Set pump motor speed
 * @param speed Motor speed command (0.0 to 1.0)
 * @return ebs_result_t Set result
 */
ebs_result_t EBS_Actuators_SetPumpSpeed(float speed)
{
    if (!g_actuators_initialized) {
        return EBS_NOT_INITIALIZED;
    }
    
    /* Validate speed command */
    if (speed < 0.0f || speed > 1.0f) {
        return EBS_INVALID_PARAM;
    }
    
    ebs_pump_motor_t* pump = &g_actuator_manager.pump_motor;
    
    /* Store speed command */
    pump->speed_command = speed;
    pump->command_timestamp = EBS_GetSystemTick();
    
    /* Calculate PWM duty cycle */
    pump->pwm_duty_cycle = Actuators_CalculatePWMDutyCycle(speed);
    
    /* Update pump state */
    if (speed > 0.0f) {
        pump->state = PUMP_STATE_RUNNING;
    } else {
        pump->state = PUMP_STATE_STOPPED;
    }
    
    return EBS_OK;
}

/**
 * @brief Get pump motor speed
 * @return float Current pump speed (0.0 to 1.0)
 */
float EBS_Actuators_GetPumpSpeed(void)
{
    if (!g_actuators_initialized) {
        return 0.0f;
    }
    
    return g_actuator_manager.pump_motor.speed_command;
}

/**
 * @brief Check if actuators are operational
 * @return bool True if operational
 */
bool EBS_Actuators_IsOperational(void)
{
    if (!g_actuators_initialized) {
        return false;
    }
    
    /* Check hydraulic modulator */
    if (g_actuator_manager.hydraulic_modulator.fault_detected) {
        return false;
    }
    
    /* Check pump motor */
    if (g_actuator_manager.pump_motor.fault_detected) {
        return false;
    }
    
    /* Check valves */
    for (uint32_t valve = 0; valve < VALVE_COUNT; valve++) {
        if (g_actuator_manager.valves[valve].fault_detected) {
            return false;
        }
    }
    
    return true;
}

/**
 * @brief Get actuator diagnostics
 * @return ebs_actuator_diagnostics_t* Pointer to diagnostics
 */
const ebs_actuator_diagnostics_t* EBS_Actuators_GetDiagnostics(void)
{
    if (!g_actuators_initialized) {
        return NULL;
    }
    
    return &g_actuator_manager.diagnostics;
}

/* Static Function Implementations */

/**
 * @brief Initialize hydraulic modulator
 * @return ebs_result_t Initialization result
 */
static ebs_result_t Actuators_InitializeHydraulicModulator(void)
{
    ebs_hydraulic_modulator_t* modulator = &g_actuator_manager.hydraulic_modulator;
    
    /* Set modulator configuration */
    modulator->min_pressure = HYDRAULIC_MIN_PRESSURE_BAR;
    modulator->max_pressure = HYDRAULIC_MAX_PRESSURE_BAR;
    modulator->response_time_ms = HYDRAULIC_RESPONSE_TIME_MS;
    modulator->enabled = true;
    modulator->fault_detected = false;
    
    /* Initialize current state */
    modulator->current_pressure = 0.0f;
    modulator->target_pressure = 0.0f;
    modulator->pressure_buildup_rate = HYDRAULIC_BUILDUP_RATE_BAR_PER_S;
    modulator->pressure_release_rate = HYDRAULIC_RELEASE_RATE_BAR_PER_S;
    
    return EBS_OK;
}

/**
 * @brief Initialize pump motor
 * @return ebs_result_t Initialization result
 */
static ebs_result_t Actuators_InitializePumpMotor(void)
{
    ebs_pump_motor_t* pump = &g_actuator_manager.pump_motor;
    
    /* Set pump configuration */
    pump->max_speed = PUMP_MAX_SPEED_RPM;
    pump->max_current = PUMP_MAX_CURRENT_A;
    pump->max_pressure = PUMP_MAX_PRESSURE_BAR;
    pump->enabled = true;
    pump->fault_detected = false;
    
    /* Initialize current state */
    pump->state = PUMP_STATE_STOPPED;
    pump->speed_command = 0.0f;
    pump->current_speed = 0.0f;
    pump->current_draw = 0.0f;
    pump->pwm_duty_cycle = 0.0f;
    pump->command_timestamp = EBS_GetSystemTick();
    
    return EBS_OK;
}

/**
 * @brief Initialize valves
 * @return ebs_result_t Initialization result
 */
static ebs_result_t Actuators_InitializeValves(void)
{
    /* Initialize inlet valves */
    for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
        uint32_t inlet_valve_idx = VALVE_INLET_FL + wheel;
        ebs_valve_t* inlet_valve = &g_actuator_manager.valves[inlet_valve_idx];
        
        inlet_valve->type = VALVE_TYPE_INLET;
        inlet_valve->max_flow_rate = VALVE_MAX_FLOW_RATE_L_PER_MIN;
        inlet_valve->response_time_ms = VALVE_RESPONSE_TIME_MS;
        inlet_valve->enabled = true;
        inlet_valve->fault_detected = false;
        inlet_valve->position_command = 0.0f;
        inlet_valve->current_position = 0.0f;
        inlet_valve->pwm_duty_cycle = 0.0f;
        inlet_valve->command_timestamp = EBS_GetSystemTick();
    }
    
    /* Initialize outlet valves */
    for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
        uint32_t outlet_valve_idx = VALVE_OUTLET_FL + wheel;
        ebs_valve_t* outlet_valve = &g_actuator_manager.valves[outlet_valve_idx];
        
        outlet_valve->type = VALVE_TYPE_OUTLET;
        outlet_valve->max_flow_rate = VALVE_MAX_FLOW_RATE_L_PER_MIN;
        outlet_valve->response_time_ms = VALVE_RESPONSE_TIME_MS;
        outlet_valve->enabled = true;
        outlet_valve->fault_detected = false;
        outlet_valve->position_command = 0.0f;
        outlet_valve->current_position = 0.0f;
        outlet_valve->pwm_duty_cycle = 0.0f;
        outlet_valve->command_timestamp = EBS_GetSystemTick();
    }
    
    return EBS_OK;
}

/**
 * @brief Update hydraulic modulator
 * @return ebs_result_t Update result
 */
static ebs_result_t Actuators_UpdateHydraulicModulator(void)
{
    ebs_hydraulic_modulator_t* modulator = &g_actuator_manager.hydraulic_modulator;
    
    if (!modulator->enabled) {
        return EBS_OK;
    }
    
    /* Calculate pressure change rate */
    float pressure_error = modulator->target_pressure - modulator->current_pressure;
    float time_step_s = EBS_CYCLE_TIME_MS / 1000.0f;
    float pressure_change = 0.0f;
    
    if (pressure_error > 0.0f) {
        /* Pressure buildup */
        pressure_change = modulator->pressure_buildup_rate * time_step_s;
        if (pressure_change > pressure_error) {
            pressure_change = pressure_error;
        }
    } else if (pressure_error < 0.0f) {
        /* Pressure release */
        pressure_change = -modulator->pressure_release_rate * time_step_s;
        if (pressure_change < pressure_error) {
            pressure_change = pressure_error;
        }
    }
    
    /* Update current pressure */
    modulator->current_pressure += pressure_change;
    
    /* Clamp to valid range */
    if (modulator->current_pressure < modulator->min_pressure) {
        modulator->current_pressure = modulator->min_pressure;
    } else if (modulator->current_pressure > modulator->max_pressure) {
        modulator->current_pressure = modulator->max_pressure;
    }
    
    /* Check for faults */
    if (fabs(pressure_error) > HYDRAULIC_PRESSURE_ERROR_THRESHOLD) {
        modulator->fault_detected = true;
    } else {
        modulator->fault_detected = false;
    }
    
    return EBS_OK;
}

/**
 * @brief Update pump motor
 * @return ebs_result_t Update result
 */
static ebs_result_t Actuators_UpdatePumpMotor(void)
{
    ebs_pump_motor_t* pump = &g_actuator_manager.pump_motor;
    
    if (!pump->enabled) {
        return EBS_OK;
    }
    
    /* Simulate pump speed response */
    float speed_error = pump->speed_command - pump->current_speed;
    float time_step_s = EBS_CYCLE_TIME_MS / 1000.0f;
    float speed_change = speed_error * PUMP_SPEED_RESPONSE_RATE * time_step_s;
    
    pump->current_speed += speed_change;
    
    /* Clamp to valid range */
    if (pump->current_speed < 0.0f) {
        pump->current_speed = 0.0f;
    } else if (pump->current_speed > 1.0f) {
        pump->current_speed = 1.0f;
    }
    
    /* Simulate current draw */
    pump->current_draw = pump->current_speed * pump->max_current;
    
    /* Check for faults */
    if (pump->current_draw > pump->max_current * 1.1f) {  /* 10% overcurrent tolerance */
        pump->fault_detected = true;
    } else {
        pump->fault_detected = false;
    }
    
    return EBS_OK;
}

/**
 * @brief Update valves
 * @return ebs_result_t Update result
 */
static ebs_result_t Actuators_UpdateValves(void)
{
    for (uint32_t valve = 0; valve < VALVE_COUNT; valve++) {
        ebs_valve_t* valve_ptr = &g_actuator_manager.valves[valve];
        
        if (!valve_ptr->enabled) {
            continue;
        }
        
        /* Simulate valve position response */
        float position_error = valve_ptr->position_command - valve_ptr->current_position;
        float time_step_s = EBS_CYCLE_TIME_MS / 1000.0f;
        float position_change = position_error * VALVE_POSITION_RESPONSE_RATE * time_step_s;
        
        valve_ptr->current_position += position_change;
        
        /* Clamp to valid range */
        if (valve_ptr->current_position < 0.0f) {
            valve_ptr->current_position = 0.0f;
        } else if (valve_ptr->current_position > 1.0f) {
            valve_ptr->current_position = 1.0f;
        }
        
        /* Update PWM duty cycle */
        valve_ptr->pwm_duty_cycle = Actuators_CalculatePWMDutyCycle(valve_ptr->current_position);
        
        /* Check for faults */
        if (fabs(position_error) > VALVE_POSITION_ERROR_THRESHOLD) {
            valve_ptr->fault_detected = true;
        } else {
            valve_ptr->fault_detected = false;
        }
    }
    
    return EBS_OK;
}

/**
 * @brief Validate pressure command
 * @param wheel Wheel position
 * @param pressure Pressure command
 * @return bool True if valid
 */
static bool Actuators_ValidatePressureCommand(ebs_wheel_position_t wheel, float pressure)
{
    if (!ABS_IS_WHEEL_VALID(wheel)) {
        return false;
    }
    
    /* Range check */
    if (pressure < 0.0f || pressure > 1.0f) {
        return false;
    }
    
    /* Rate of change check */
    static float previous_pressures[WHEEL_COUNT] = {0.0f};
    float pressure_change = fabs(pressure - previous_pressures[wheel]);
    float max_change = MAX_PRESSURE_CHANGE_PER_CYCLE;
    
    if (pressure_change > max_change) {
        return false;  /* Pressure changed too rapidly */
    }
    
    previous_pressures[wheel] = pressure;
    
    return true;
}

/**
 * @brief Update actuator diagnostics
 */
static void Actuators_UpdateDiagnostics(void)
{
    ebs_actuator_diagnostics_t* diag = &g_actuator_manager.diagnostics;
    
    /* Check hydraulic modulator fault */
    diag->hydraulic_modulator_fault = g_actuator_manager.hydraulic_modulator.fault_detected;
    
    /* Check pump motor fault */
    diag->pump_motor_fault = g_actuator_manager.pump_motor.fault_detected;
    
    /* Count valve faults */
    diag->valve_faults = 0;
    for (uint32_t valve = 0; valve < VALVE_COUNT; valve++) {
        if (g_actuator_manager.valves[valve].fault_detected) {
            diag->valve_faults++;
        }
    }
    
    /* Update total fault count */
    diag->total_faults = (diag->hydraulic_modulator_fault ? 1 : 0) + 
                        (diag->pump_motor_fault ? 1 : 0) + 
                        diag->valve_faults;
    
    /* Update last update time */
    diag->last_update_time = EBS_GetSystemTick();
}

/**
 * @brief Set valve position
 * @param valve_id Valve identifier
 * @param position Position command (0.0 to 1.0)
 * @return ebs_result_t Set result
 */
static ebs_result_t Actuators_SetValvePosition(ebs_valve_id_t valve_id, float position)
{
    if (valve_id >= VALVE_COUNT) {
        return EBS_INVALID_PARAM;
    }
    
    /* Validate position command */
    if (position < 0.0f || position > 1.0f) {
        return EBS_INVALID_PARAM;
    }
    
    ebs_valve_t* valve = &g_actuator_manager.valves[valve_id];
    
    if (!valve->enabled) {
        return EBS_ERROR;
    }
    
    /* Store position command */
    valve->position_command = position;
    valve->command_timestamp = EBS_GetSystemTick();
    
    return EBS_OK;
}

/**
 * @brief Calculate PWM duty cycle from command
 * @param command Command value (0.0 to 1.0)
 * @return float PWM duty cycle (0.0 to 100.0)
 */
static float Actuators_CalculatePWMDutyCycle(float command)
{
    /* Clamp command to valid range */
    if (command < 0.0f) {
        command = 0.0f;
    } else if (command > 1.0f) {
        command = 1.0f;
    }
    
    /* Convert to PWM duty cycle percentage */
    return command * 100.0f;
}