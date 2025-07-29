/**
 * @file ebs_sensors.c
 * @brief Electronic Braking System - Sensor Interface Implementation
 * @version 1.0
 * @date 2025-07-29
 * @author EBS Development Team
 * 
 * Sensor interface implementation for EBS system
 * 
 * Safety Level: ASIL-D
 * Compliance: ISO 26262, MISRA C:2012
 */

#include "ebs_sensors.h"
#include "ebs_safety.h"
#include "ebs_diagnostics.h"
#include <string.h>
#include <math.h>

/* Static Variables */
static ebs_sensor_manager_t g_sensor_manager;
static bool g_sensors_initialized = false;

/* Static Function Prototypes */
static ebs_result_t Sensors_InitializeWheelSpeed(void);
static ebs_result_t Sensors_InitializePressure(void);
static ebs_result_t Sensors_InitializeIMU(void);
static ebs_result_t Sensors_InitializeSteeringAngle(void);
static ebs_result_t Sensors_ReadWheelSpeedSensors(void);
static ebs_result_t Sensors_ReadPressureSensors(void);
static ebs_result_t Sensors_ReadIMUSensors(void);
static ebs_result_t Sensors_ReadSteeringAngleSensor(void);
static bool Sensors_ValidateWheelSpeed(uint32_t wheel, float speed);
static bool Sensors_ValidatePressure(uint32_t sensor, float pressure);
static bool Sensors_ValidateIMUData(const ebs_imu_data_t* imu_data);
static bool Sensors_ValidateSteeringAngle(float angle);
static void Sensors_UpdateDiagnostics(void);
static float Sensors_ApplyCalibration(float raw_value, const ebs_sensor_calibration_t* cal);

/**
 * @brief Initialize sensor subsystem
 * @return ebs_result_t Initialization result
 */
ebs_result_t EBS_Sensors_Init(void)
{
    /* Clear sensor manager state */
    memset(&g_sensor_manager, 0, sizeof(g_sensor_manager));
    
    /* Initialize wheel speed sensors */
    if (Sensors_InitializeWheelSpeed() != EBS_OK) {
        return EBS_ERROR;
    }
    
    /* Initialize pressure sensors */
    if (Sensors_InitializePressure() != EBS_OK) {
        return EBS_ERROR;
    }
    
    /* Initialize IMU sensor */
    if (Sensors_InitializeIMU() != EBS_OK) {
        return EBS_ERROR;
    }
    
    /* Initialize steering angle sensor */
    if (Sensors_InitializeSteeringAngle() != EBS_OK) {
        return EBS_ERROR;
    }
    
    /* Initialize sensor manager state */
    g_sensor_manager.system_enabled = true;
    g_sensor_manager.last_update_time = EBS_GetSystemTick();
    g_sensor_manager.update_count = 0;
    
    g_sensors_initialized = true;
    
    return EBS_OK;
}

/**
 * @brief Perform sensor self-test
 * @return bool True if self-test passed
 */
bool EBS_Sensors_SelfTest(void)
{
    if (!g_sensors_initialized) {
        return false;
    }
    
    bool test_passed = true;
    
    /* Test wheel speed sensors */
    for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
        ebs_wheel_speed_sensor_t* sensor = &g_sensor_manager.wheel_speed.sensors[wheel];
        
        /* Check sensor configuration */
        if (sensor->pulses_per_revolution == 0 || sensor->wheel_circumference <= 0.0f) {
            test_passed = false;
        }
        
        /* Test sensor communication */
        sensor->raw_pulse_count = 100;  /* Simulate test pulse count */
        float test_speed = (sensor->raw_pulse_count * sensor->wheel_circumference * 3.6f) / 
                          (sensor->pulses_per_revolution * (EBS_CYCLE_TIME_MS / 1000.0f));
        
        if (test_speed <= 0.0f || test_speed > EBS_MAX_WHEEL_SPEED) {
            test_passed = false;
        }
    }
    
    /* Test pressure sensors */
    for (uint32_t sensor = 0; sensor < PRESSURE_SENSOR_COUNT; sensor++) {
        ebs_pressure_sensor_t* press_sensor = &g_sensor_manager.pressure.sensors[sensor];
        
        /* Check sensor range */
        if (press_sensor->max_pressure <= press_sensor->min_pressure) {
            test_passed = false;
        }
    }
    
    /* Test IMU sensor */
    ebs_imu_sensor_t* imu = &g_sensor_manager.imu.sensor;
    if (imu->accelerometer_range <= 0.0f || imu->gyroscope_range <= 0.0f) {
        test_passed = false;
    }
    
    /* Test steering angle sensor */
    ebs_steering_angle_sensor_t* steering = &g_sensor_manager.steering_angle.sensor;
    if (steering->max_angle <= steering->min_angle) {
        test_passed = false;
    }
    
    return test_passed;
}

/**
 * @brief Update all sensors (called every cycle)
 * @return ebs_result_t Update result
 */
ebs_result_t EBS_Sensors_Update(void)
{
    if (!g_sensors_initialized || !g_sensor_manager.system_enabled) {
        return EBS_NOT_INITIALIZED;
    }
    
    ebs_result_t result = EBS_OK;
    
    /* Read wheel speed sensors */
    if (Sensors_ReadWheelSpeedSensors() != EBS_OK) {
        result = EBS_ERROR;
    }
    
    /* Read pressure sensors */
    if (Sensors_ReadPressureSensors() != EBS_OK) {
        result = EBS_ERROR;
    }
    
    /* Read IMU sensor */
    if (Sensors_ReadIMUSensors() != EBS_OK) {
        result = EBS_ERROR;
    }
    
    /* Read steering angle sensor */
    if (Sensors_ReadSteeringAngleSensor() != EBS_OK) {
        result = EBS_ERROR;
    }
    
    /* Update diagnostics */
    Sensors_UpdateDiagnostics();
    
    /* Update manager state */
    g_sensor_manager.last_update_time = EBS_GetSystemTick();
    g_sensor_manager.update_count++;
    
    return result;
}

/**
 * @brief Get wheel speed data
 * @return ebs_wheel_speed_data_t* Pointer to wheel speed data
 */
ebs_wheel_speed_data_t* EBS_Sensors_GetWheelSpeedData(void)
{
    if (!g_sensors_initialized) {
        return NULL;
    }
    
    return &g_sensor_manager.wheel_speed.data;
}

/**
 * @brief Get pressure sensor data
 * @return ebs_pressure_data_t* Pointer to pressure data
 */
ebs_pressure_data_t* EBS_Sensors_GetPressureData(void)
{
    if (!g_sensors_initialized) {
        return NULL;
    }
    
    return &g_sensor_manager.pressure.data;
}

/**
 * @brief Get IMU sensor data
 * @return ebs_imu_data_t* Pointer to IMU data
 */
ebs_imu_data_t* EBS_Sensors_GetIMUData(void)
{
    if (!g_sensors_initialized) {
        return NULL;
    }
    
    return &g_sensor_manager.imu.data;
}

/**
 * @brief Get steering angle data
 * @return ebs_steering_angle_data_t* Pointer to steering angle data
 */
ebs_steering_angle_data_t* EBS_Sensors_GetSteeringAngleData(void)
{
    if (!g_sensors_initialized) {
        return NULL;
    }
    
    return &g_sensor_manager.steering_angle.data;
}

/**
 * @brief Check if sensor data is valid
 * @param sensor_type Type of sensor to check
 * @return bool True if sensor data is valid
 */
bool EBS_Sensors_IsDataValid(ebs_sensor_type_t sensor_type)
{
    if (!g_sensors_initialized) {
        return false;
    }
    
    switch (sensor_type) {
        case SENSOR_TYPE_WHEEL_SPEED:
            for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
                if (!g_sensor_manager.wheel_speed.data.speed[wheel].valid) {
                    return false;
                }
            }
            return true;
            
        case SENSOR_TYPE_PRESSURE:
            for (uint32_t sensor = 0; sensor < PRESSURE_SENSOR_COUNT; sensor++) {
                if (!g_sensor_manager.pressure.data.pressure[sensor].valid) {
                    return false;
                }
            }
            return true;
            
        case SENSOR_TYPE_IMU:
            return g_sensor_manager.imu.data.valid;
            
        case SENSOR_TYPE_STEERING_ANGLE:
            return g_sensor_manager.steering_angle.data.valid;
            
        default:
            return false;
    }
}

/**
 * @brief Get sensor diagnostics
 * @return ebs_sensor_diagnostics_t* Pointer to sensor diagnostics
 */
const ebs_sensor_diagnostics_t* EBS_Sensors_GetDiagnostics(void)
{
    if (!g_sensors_initialized) {
        return NULL;
    }
    
    return &g_sensor_manager.diagnostics;
}

/* Static Function Implementations */

/**
 * @brief Initialize wheel speed sensors
 * @return ebs_result_t Initialization result
 */
static ebs_result_t Sensors_InitializeWheelSpeed(void)
{
    ebs_wheel_speed_manager_t* ws_mgr = &g_sensor_manager.wheel_speed;
    
    /* Initialize each wheel speed sensor */
    for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
        ebs_wheel_speed_sensor_t* sensor = &ws_mgr->sensors[wheel];
        
        /* Set sensor configuration */
        sensor->pulses_per_revolution = WHEEL_SPEED_PULSES_PER_REV;
        sensor->wheel_circumference = WHEEL_CIRCUMFERENCE_M;
        sensor->enabled = true;
        sensor->fault_detected = false;
        sensor->raw_pulse_count = 0;
        sensor->previous_pulse_count = 0;
        sensor->pulse_time_us = 0;
        
        /* Set calibration parameters */
        sensor->calibration.offset = 0.0f;
        sensor->calibration.scale = 1.0f;
        sensor->calibration.min_value = 0.0f;
        sensor->calibration.max_value = EBS_MAX_WHEEL_SPEED;
        
        /* Initialize data */
        ws_mgr->data.speed[wheel].value = 0.0f;
        ws_mgr->data.speed[wheel].valid = false;
        ws_mgr->data.speed[wheel].timestamp = EBS_GetSystemTick();
    }
    
    ws_mgr->data.timestamp = EBS_GetSystemTick();
    
    return EBS_OK;
}

/**
 * @brief Initialize pressure sensors
 * @return ebs_result_t Initialization result
 */
static ebs_result_t Sensors_InitializePressure(void)
{
    ebs_pressure_manager_t* press_mgr = &g_sensor_manager.pressure;
    
    /* Initialize each pressure sensor */
    for (uint32_t sensor = 0; sensor < PRESSURE_SENSOR_COUNT; sensor++) {
        ebs_pressure_sensor_t* press_sensor = &press_mgr->sensors[sensor];
        
        /* Set sensor configuration */
        press_sensor->min_pressure = PRESSURE_SENSOR_MIN_BAR;
        press_sensor->max_pressure = PRESSURE_SENSOR_MAX_BAR;
        press_sensor->enabled = true;
        press_sensor->fault_detected = false;
        press_sensor->raw_adc_value = 0;
        
        /* Set calibration parameters */
        press_sensor->calibration.offset = 0.0f;
        press_sensor->calibration.scale = (PRESSURE_SENSOR_MAX_BAR - PRESSURE_SENSOR_MIN_BAR) / 4095.0f;  /* 12-bit ADC */
        press_sensor->calibration.min_value = PRESSURE_SENSOR_MIN_BAR;
        press_sensor->calibration.max_value = PRESSURE_SENSOR_MAX_BAR;
        
        /* Initialize data */
        press_mgr->data.pressure[sensor].value = 0.0f;
        press_mgr->data.pressure[sensor].valid = false;
        press_mgr->data.pressure[sensor].timestamp = EBS_GetSystemTick();
    }
    
    press_mgr->data.timestamp = EBS_GetSystemTick();
    
    return EBS_OK;
}

/**
 * @brief Initialize IMU sensor
 * @return ebs_result_t Initialization result
 */
static ebs_result_t Sensors_InitializeIMU(void)
{
    ebs_imu_manager_t* imu_mgr = &g_sensor_manager.imu;
    ebs_imu_sensor_t* imu_sensor = &imu_mgr->sensor;
    
    /* Set sensor configuration */
    imu_sensor->accelerometer_range = IMU_ACCEL_RANGE_G;
    imu_sensor->gyroscope_range = IMU_GYRO_RANGE_DPS;
    imu_sensor->sample_rate_hz = IMU_SAMPLE_RATE_HZ;
    imu_sensor->enabled = true;
    imu_sensor->fault_detected = false;
    
    /* Set calibration parameters */
    imu_sensor->accel_calibration.offset = 0.0f;
    imu_sensor->accel_calibration.scale = 1.0f;
    imu_sensor->accel_calibration.min_value = -IMU_ACCEL_RANGE_G;
    imu_sensor->accel_calibration.max_value = IMU_ACCEL_RANGE_G;
    
    imu_sensor->gyro_calibration.offset = 0.0f;
    imu_sensor->gyro_calibration.scale = 1.0f;
    imu_sensor->gyro_calibration.min_value = -IMU_GYRO_RANGE_DPS;
    imu_sensor->gyro_calibration.max_value = IMU_GYRO_RANGE_DPS;
    
    /* Initialize data */
    memset(&imu_mgr->data, 0, sizeof(imu_mgr->data));
    imu_mgr->data.valid = false;
    imu_mgr->data.timestamp = EBS_GetSystemTick();
    
    return EBS_OK;
}

/**
 * @brief Initialize steering angle sensor
 * @return ebs_result_t Initialization result
 */
static ebs_result_t Sensors_InitializeSteeringAngle(void)
{
    ebs_steering_angle_manager_t* sa_mgr = &g_sensor_manager.steering_angle;
    ebs_steering_angle_sensor_t* sa_sensor = &sa_mgr->sensor;
    
    /* Set sensor configuration */
    sa_sensor->min_angle = STEERING_ANGLE_MIN_DEG;
    sa_sensor->max_angle = STEERING_ANGLE_MAX_DEG;
    sa_sensor->resolution = STEERING_ANGLE_RESOLUTION_DEG;
    sa_sensor->enabled = true;
    sa_sensor->fault_detected = false;
    sa_sensor->raw_adc_value = 0;
    
    /* Set calibration parameters */
    sa_sensor->calibration.offset = 0.0f;
    sa_sensor->calibration.scale = (STEERING_ANGLE_MAX_DEG - STEERING_ANGLE_MIN_DEG) / 4095.0f;  /* 12-bit ADC */
    sa_sensor->calibration.min_value = STEERING_ANGLE_MIN_DEG;
    sa_sensor->calibration.max_value = STEERING_ANGLE_MAX_DEG;
    
    /* Initialize data */
    sa_mgr->data.angle = 0.0f;
    sa_mgr->data.angular_velocity = 0.0f;
    sa_mgr->data.valid = false;
    sa_mgr->data.timestamp = EBS_GetSystemTick();
    
    return EBS_OK;
}

/**
 * @brief Read wheel speed sensors
 * @return ebs_result_t Read result
 */
static ebs_result_t Sensors_ReadWheelSpeedSensors(void)
{
    ebs_wheel_speed_manager_t* ws_mgr = &g_sensor_manager.wheel_speed;
    uint32_t current_time = EBS_GetSystemTick();
    
    for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
        ebs_wheel_speed_sensor_t* sensor = &ws_mgr->sensors[wheel];
        
        if (!sensor->enabled) {
            ws_mgr->data.speed[wheel].valid = false;
            continue;
        }
        
        /* Simulate reading pulse count from hardware */
        /* In real implementation, this would read from hardware registers */
        static uint32_t simulated_pulse_count[WHEEL_COUNT] = {0};
        simulated_pulse_count[wheel] += 10;  /* Simulate 10 pulses per cycle */
        sensor->raw_pulse_count = simulated_pulse_count[wheel];
        
        /* Calculate speed from pulse count */
        uint32_t pulse_diff = sensor->raw_pulse_count - sensor->previous_pulse_count;
        float time_diff_s = EBS_CYCLE_TIME_MS / 1000.0f;
        
        if (time_diff_s > 0.0f && pulse_diff > 0) {
            /* Speed = (pulses * circumference * 3.6) / (pulses_per_rev * time_in_seconds) */
            float raw_speed = (pulse_diff * sensor->wheel_circumference * 3.6f) / 
                             (sensor->pulses_per_revolution * time_diff_s);
            
            /* Apply calibration */
            float calibrated_speed = Sensors_ApplyCalibration(raw_speed, &sensor->calibration);
            
            /* Validate speed */
            if (Sensors_ValidateWheelSpeed(wheel, calibrated_speed)) {
                ws_mgr->data.speed[wheel].value = calibrated_speed;
                ws_mgr->data.speed[wheel].valid = true;
                sensor->fault_detected = false;
            } else {
                ws_mgr->data.speed[wheel].valid = false;
                sensor->fault_detected = true;
            }
        } else {
            /* No movement detected */
            ws_mgr->data.speed[wheel].value = 0.0f;
            ws_mgr->data.speed[wheel].valid = true;
            sensor->fault_detected = false;
        }
        
        ws_mgr->data.speed[wheel].timestamp = current_time;
        sensor->previous_pulse_count = sensor->raw_pulse_count;
    }
    
    ws_mgr->data.timestamp = current_time;
    
    return EBS_OK;
}

/**
 * @brief Read pressure sensors
 * @return ebs_result_t Read result
 */
static ebs_result_t Sensors_ReadPressureSensors(void)
{
    ebs_pressure_manager_t* press_mgr = &g_sensor_manager.pressure;
    uint32_t current_time = EBS_GetSystemTick();
    
    for (uint32_t sensor = 0; sensor < PRESSURE_SENSOR_COUNT; sensor++) {
        ebs_pressure_sensor_t* press_sensor = &press_mgr->sensors[sensor];
        
        if (!press_sensor->enabled) {
            press_mgr->data.pressure[sensor].valid = false;
            continue;
        }
        
        /* Simulate reading ADC value from hardware */
        /* In real implementation, this would read from ADC */
        static uint16_t simulated_adc[PRESSURE_SENSOR_COUNT] = {2048, 2048, 2048, 2048};  /* Mid-range values */
        press_sensor->raw_adc_value = simulated_adc[sensor];
        
        /* Convert ADC value to pressure */
        float raw_pressure = Sensors_ApplyCalibration((float)press_sensor->raw_adc_value, 
                                                     &press_sensor->calibration);
        
        /* Validate pressure */
        if (Sensors_ValidatePressure(sensor, raw_pressure)) {
            press_mgr->data.pressure[sensor].value = raw_pressure;
            press_mgr->data.pressure[sensor].valid = true;
            press_sensor->fault_detected = false;
        } else {
            press_mgr->data.pressure[sensor].valid = false;
            press_sensor->fault_detected = true;
        }
        
        press_mgr->data.pressure[sensor].timestamp = current_time;
    }
    
    press_mgr->data.timestamp = current_time;
    
    return EBS_OK;
}

/**
 * @brief Read IMU sensor
 * @return ebs_result_t Read result
 */
static ebs_result_t Sensors_ReadIMUSensors(void)
{
    ebs_imu_manager_t* imu_mgr = &g_sensor_manager.imu;
    ebs_imu_sensor_t* imu_sensor = &imu_mgr->sensor;
    uint32_t current_time = EBS_GetSystemTick();
    
    if (!imu_sensor->enabled) {
        imu_mgr->data.valid = false;
        return EBS_OK;
    }
    
    /* Simulate reading IMU data from hardware */
    /* In real implementation, this would read from IMU via SPI/I2C */
    
    /* Simulate accelerometer data (in g) */
    imu_mgr->data.acceleration.x = 0.0f;  /* Longitudinal acceleration */
    imu_mgr->data.acceleration.y = 0.0f;  /* Lateral acceleration */
    imu_mgr->data.acceleration.z = 1.0f;  /* Vertical acceleration (gravity) */
    
    /* Simulate gyroscope data (in deg/s) */
    imu_mgr->data.angular_velocity.x = 0.0f;  /* Roll rate */
    imu_mgr->data.angular_velocity.y = 0.0f;  /* Pitch rate */
    imu_mgr->data.angular_velocity.z = 0.0f;  /* Yaw rate */
    
    /* Apply calibration */
    imu_mgr->data.acceleration.x = Sensors_ApplyCalibration(imu_mgr->data.acceleration.x, 
                                                           &imu_sensor->accel_calibration);
    imu_mgr->data.acceleration.y = Sensors_ApplyCalibration(imu_mgr->data.acceleration.y, 
                                                           &imu_sensor->accel_calibration);
    imu_mgr->data.acceleration.z = Sensors_ApplyCalibration(imu_mgr->data.acceleration.z, 
                                                           &imu_sensor->accel_calibration);
    
    imu_mgr->data.angular_velocity.x = Sensors_ApplyCalibration(imu_mgr->data.angular_velocity.x, 
                                                               &imu_sensor->gyro_calibration);
    imu_mgr->data.angular_velocity.y = Sensors_ApplyCalibration(imu_mgr->data.angular_velocity.y, 
                                                               &imu_sensor->gyro_calibration);
    imu_mgr->data.angular_velocity.z = Sensors_ApplyCalibration(imu_mgr->data.angular_velocity.z, 
                                                               &imu_sensor->gyro_calibration);
    
    /* Validate IMU data */
    if (Sensors_ValidateIMUData(&imu_mgr->data)) {
        imu_mgr->data.valid = true;
        imu_sensor->fault_detected = false;
    } else {
        imu_mgr->data.valid = false;
        imu_sensor->fault_detected = true;
    }
    
    imu_mgr->data.timestamp = current_time;
    
    return EBS_OK;
}

/**
 * @brief Read steering angle sensor
 * @return ebs_result_t Read result
 */
static ebs_result_t Sensors_ReadSteeringAngleSensor(void)
{
    ebs_steering_angle_manager_t* sa_mgr = &g_sensor_manager.steering_angle;
    ebs_steering_angle_sensor_t* sa_sensor = &sa_mgr->sensor;
    uint32_t current_time = EBS_GetSystemTick();
    
    if (!sa_sensor->enabled) {
        sa_mgr->data.valid = false;
        return EBS_OK;
    }
    
    /* Simulate reading ADC value from hardware */
    /* In real implementation, this would read from ADC */
    static uint16_t simulated_steering_adc = 2048;  /* Mid-range (straight ahead) */
    sa_sensor->raw_adc_value = simulated_steering_adc;
    
    /* Convert ADC value to angle */
    float raw_angle = Sensors_ApplyCalibration((float)sa_sensor->raw_adc_value, 
                                              &sa_sensor->calibration);
    
    /* Calculate angular velocity */
    static float previous_angle = 0.0f;
    float time_diff_s = EBS_CYCLE_TIME_MS / 1000.0f;
    float angular_velocity = 0.0f;
    
    if (time_diff_s > 0.0f) {
        angular_velocity = (raw_angle - previous_angle) / time_diff_s;
    }
    
    /* Validate steering angle */
    if (Sensors_ValidateSteeringAngle(raw_angle)) {
        sa_mgr->data.angle = raw_angle;
        sa_mgr->data.angular_velocity = angular_velocity;
        sa_mgr->data.valid = true;
        sa_sensor->fault_detected = false;
    } else {
        sa_mgr->data.valid = false;
        sa_sensor->fault_detected = true;
    }
    
    sa_mgr->data.timestamp = current_time;
    previous_angle = raw_angle;
    
    return EBS_OK;
}

/**
 * @brief Validate wheel speed reading
 * @param wheel Wheel index
 * @param speed Speed value to validate
 * @return bool True if valid
 */
static bool Sensors_ValidateWheelSpeed(uint32_t wheel, float speed)
{
    if (wheel >= WHEEL_COUNT) {
        return false;
    }
    
    /* Range check */
    if (speed < 0.0f || speed > EBS_MAX_WHEEL_SPEED) {
        return false;
    }
    
    /* Rate of change check */
    static float previous_speeds[WHEEL_COUNT] = {0.0f};
    float speed_change = fabs(speed - previous_speeds[wheel]);
    float max_change = MAX_WHEEL_SPEED_CHANGE_PER_CYCLE;
    
    if (speed_change > max_change) {
        return false;  /* Speed changed too rapidly */
    }
    
    previous_speeds[wheel] = speed;
    
    return true;
}

/**
 * @brief Validate pressure reading
 * @param sensor Sensor index
 * @param pressure Pressure value to validate
 * @return bool True if valid
 */
static bool Sensors_ValidatePressure(uint32_t sensor, float pressure)
{
    if (sensor >= PRESSURE_SENSOR_COUNT) {
        return false;
    }
    
    /* Range check */
    if (pressure < PRESSURE_SENSOR_MIN_BAR || pressure > PRESSURE_SENSOR_MAX_BAR) {
        return false;
    }
    
    return true;
}

/**
 * @brief Validate IMU data
 * @param imu_data IMU data to validate
 * @return bool True if valid
 */
static bool Sensors_ValidateIMUData(const ebs_imu_data_t* imu_data)
{
    if (imu_data == NULL) {
        return false;
    }
    
    /* Check acceleration ranges */
    if (fabs(imu_data->acceleration.x) > IMU_ACCEL_RANGE_G ||
        fabs(imu_data->acceleration.y) > IMU_ACCEL_RANGE_G ||
        fabs(imu_data->acceleration.z) > IMU_ACCEL_RANGE_G) {
        return false;
    }
    
    /* Check angular velocity ranges */
    if (fabs(imu_data->angular_velocity.x) > IMU_GYRO_RANGE_DPS ||
        fabs(imu_data->angular_velocity.y) > IMU_GYRO_RANGE_DPS ||
        fabs(imu_data->angular_velocity.z) > IMU_GYRO_RANGE_DPS) {
        return false;
    }
    
    return true;
}

/**
 * @brief Validate steering angle reading
 * @param angle Steering angle to validate
 * @return bool True if valid
 */
static bool Sensors_ValidateSteeringAngle(float angle)
{
    /* Range check */
    if (angle < STEERING_ANGLE_MIN_DEG || angle > STEERING_ANGLE_MAX_DEG) {
        return false;
    }
    
    return true;
}

/**
 * @brief Update sensor diagnostics
 */
static void Sensors_UpdateDiagnostics(void)
{
    ebs_sensor_diagnostics_t* diag = &g_sensor_manager.diagnostics;
    
    /* Count wheel speed sensor faults */
    diag->wheel_speed_faults = 0;
    for (uint32_t wheel = 0; wheel < WHEEL_COUNT; wheel++) {
        if (g_sensor_manager.wheel_speed.sensors[wheel].fault_detected) {
            diag->wheel_speed_faults++;
        }
    }
    
    /* Count pressure sensor faults */
    diag->pressure_sensor_faults = 0;
    for (uint32_t sensor = 0; sensor < PRESSURE_SENSOR_COUNT; sensor++) {
        if (g_sensor_manager.pressure.sensors[sensor].fault_detected) {
            diag->pressure_sensor_faults++;
        }
    }
    
    /* Check IMU sensor fault */
diag->imu_fault = g_sensor_manager.imu.sensor.fault_detected;
    
    /* Check steering angle sensor fault */
    diag->steering_angle_fault = g_sensor_manager.steering_angle.sensor.fault_detected;
    
    /* Update total fault count */
    diag->total_faults = diag->wheel_speed_faults + diag->pressure_sensor_faults + 
                        (diag->imu_fault ? 1 : 0) + (diag->steering_angle_fault ? 1 : 0);
    
    /* Update last update time */
    diag->last_update_time = EBS_GetSystemTick();
}

/**
 * @brief Apply calibration to sensor reading
 * @param raw_value Raw sensor value
 * @param cal Calibration parameters
 * @return float Calibrated value
 */
static float Sensors_ApplyCalibration(float raw_value, const ebs_sensor_calibration_t* cal)
{
    if (cal == NULL) {
        return raw_value;
    }
    
    /* Apply offset and scale */
    float calibrated_value = (raw_value + cal->offset) * cal->scale;
    
    /* Clamp to valid range */
    if (calibrated_value < cal->min_value) {
        calibrated_value = cal->min_value;
    } else if (calibrated_value > cal->max_value) {
        calibrated_value = cal->max_value;
    }
    
    return calibrated_value;
}