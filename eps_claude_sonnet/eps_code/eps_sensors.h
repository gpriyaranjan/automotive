/**
 * @file eps_sensors.h
 * @brief Electronic Power Steering (EPS) Sensors Module Header
 * @version 1.0
 * @date 2025-07-29
 * 
 * Requirements Traceability:
 * - EPS-IR-025 to EPS-IR-049: Sensor Interface Requirements
 * - EPS-FR-007 to EPS-FR-011: Torque Sensing Functions
 */

#ifndef EPS_SENSORS_H
#define EPS_SENSORS_H

#include "eps_main.h"

/* Sensor Constants */
#define EPS_TORQUE_SENSOR_RANGE_NM      10.0f   /* ±10 Nm - EPS-PR-009 */
#define EPS_TORQUE_SENSOR_ACCURACY      0.02f   /* 2% - EPS-PR-010 */
#define EPS_ANGLE_SENSOR_RANGE_DEG      720.0f  /* ±720° - EPS-PR-047 */
#define EPS_ANGLE_SENSOR_ACCURACY       1.0f    /* ±1° - EPS-PR-048 */
#define EPS_SENSOR_SAMPLE_RATE_HZ       1000    /* Hz - EPS-IR-028 */

/* Sensor Types */
typedef enum {
    EPS_SENSOR_TORQUE_PRIMARY = 0,
    EPS_SENSOR_TORQUE_SECONDARY,
    EPS_SENSOR_STEERING_ANGLE,
    EPS_SENSOR_MOTOR_POSITION,
    EPS_SENSOR_TEMPERATURE_ECU,
    EPS_SENSOR_TEMPERATURE_MOTOR,
    EPS_SENSOR_COUNT
} eps_sensor_type_t;

/* Sensor Status */
typedef enum {
    EPS_SENSOR_STATUS_OK = 0,
    EPS_SENSOR_STATUS_FAULT,
    EPS_SENSOR_STATUS_OUT_OF_RANGE,
    EPS_SENSOR_STATUS_DISCONNECTED,
    EPS_SENSOR_STATUS_NOISY
} eps_sensor_status_t;

/* Individual Sensor Data */
typedef struct {
    float raw_value;
    float calibrated_value;
    eps_sensor_status_t status;
    uint32_t timestamp;
    bool valid;
} eps_sensor_reading_t;

/* Function Prototypes */
eps_result_t eps_sensors_init(void);
eps_result_t eps_sensors_read_all(eps_sensor_data_t* sensor_data);
eps_result_t eps_sensors_validate_data(const eps_sensor_data_t* sensor_data);
eps_result_t eps_sensors_self_test(void);
eps_result_t eps_sensors_calibrate(eps_sensor_type_t sensor_type);
eps_sensor_reading_t eps_sensors_read_single(eps_sensor_type_t sensor_type);

#endif /* EPS_SENSORS_H */