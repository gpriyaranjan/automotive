#ifndef SENSOR_INTERFACE_H
#define SENSOR_INTERFACE_H

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "Rte_SensorInterface.h"

/* AUTOSAR Software Component Version Information */
#define SENSOR_INTERFACE_SW_MAJOR_VERSION    1
#define SENSOR_INTERFACE_SW_MINOR_VERSION    0
#define SENSOR_INTERFACE_SW_PATCH_VERSION    0

/* Sensor Interface Constants */
#define SENSOR_SAMPLING_RATE              1000    /* Hz */
#define SENSOR_FILTER_ALPHA               0.9f    /* Low-pass filter coefficient */
#define SENSOR_TIMEOUT_MS                 100     /* Sensor timeout in milliseconds */

/* Sensor Data Structure */
typedef struct {
    float torque_sensor_raw;          /* Raw torque sensor reading (V) */
    float torque_sensor_filtered;     /* Filtered torque sensor reading (V) */
    float torque_sensor_calibrated;   /* Calibrated torque value (Nm) */
    boolean torque_sensor_valid;      /* Torque sensor validity flag */
    
    float angle_sensor_raw;           /* Raw steering angle sensor reading (V) */
    float angle_sensor_filtered;      /* Filtered steering angle sensor reading (V) */
    float angle_sensor_calibrated;    /* Calibrated steering angle (degrees) */
    boolean angle_sensor_valid;       /* Steering angle sensor validity flag */
    
    float speed_sensor_raw;           /* Raw vehicle speed sensor reading (V) */
    float speed_sensor_filtered;      /* Filtered vehicle speed sensor reading (V) */
    float speed_sensor_calibrated;    /* Calibrated vehicle speed (km/h) */
    boolean speed_sensor_valid;       /* Vehicle speed sensor validity flag */
    
    uint32_t last_update_timestamp;   /* Last sensor update timestamp */
    boolean sensors_initialized;      /* Sensor initialization flag */
} SensorData_t;

/* Sensor Calibration Data */
typedef struct {
    float torque_offset;              /* Torque sensor offset (V) */
    float torque_scale;               /* Torque sensor scale factor (Nm/V) */
    float angle_offset;               /* Steering angle sensor offset (V) */
    float angle_scale;                /* Steering angle sensor scale factor (deg/V) */
    float speed_offset;               /* Vehicle speed sensor offset (V) */
    float speed_scale;                /* Vehicle speed sensor scale factor (km/h/V) */
} SensorCalibration_t;

/* Sensor Fault Codes */
typedef enum {
    SENSOR_FAULT_NONE = 0,
    SENSOR_FAULT_TORQUE_SENSOR_OPEN,
    SENSOR_FAULT_TORQUE_SENSOR_SHORT,
    SENSOR_FAULT_TORQUE_SENSOR_OUT_OF_RANGE,
    SENSOR_FAULT_ANGLE_SENSOR_OPEN,
    SENSOR_FAULT_ANGLE_SENSOR_SHORT,
    SENSOR_FAULT_ANGLE_SENSOR_OUT_OF_RANGE,
    SENSOR_FAULT_SPEED_SENSOR_OPEN,
    SENSOR_FAULT_SPEED_SENSOR_SHORT,
    SENSOR_FAULT_SPEED_SENSOR_OUT_OF_RANGE,
    SENSOR_FAULT_COMMUNICATION_ERROR
} SensorFaultCode_t;

/* Function Prototypes */

/**
 * @brief Initialize the Sensor Interface Software Component
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType SensorInterface_Init(void);

/**
 * @brief Main sensor interface function for data acquisition and processing
 * @param sensor_data Pointer to sensor data structure
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType SensorInterface_MainFunction(SensorData_t* sensor_data);

/**
 * @brief Read raw sensor data from hardware
 * @param sensor_data Pointer to sensor data structure
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType SensorInterface_ReadRawSensors(SensorData_t* sensor_data);

/**
 * @brief Apply digital filtering to sensor data
 * @param sensor_data Pointer to sensor data structure
 */
void SensorInterface_ApplyFilters(SensorData_t* sensor_data);

/**
 * @brief Apply calibration to convert raw sensor values to engineering units
 * @param sensor_data Pointer to sensor data structure
 * @param calibration Pointer to calibration data structure
 */
void SensorInterface_ApplyCalibration(SensorData_t* sensor_data, 
                                    const SensorCalibration_t* calibration);

/**
 * @brief Perform sensor validity checks
 * @param sensor_data Pointer to sensor data structure
 * @return Std_ReturnType - E_OK if all sensors valid, E_NOT_OK otherwise
 */
Std_ReturnType SensorInterface_ValidateSensors(SensorData_t* sensor_data);

/**
 * @brief Detect sensor faults
 * @param sensor_data Pointer to sensor data structure
 * @return SensorFaultCode_t - Detected fault code
 */
SensorFaultCode_t SensorInterface_DetectFaults(const SensorData_t* sensor_data);

/**
 * @brief Get sensor calibration data
 * @param calibration Pointer to calibration data structure
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType SensorInterface_GetCalibration(SensorCalibration_t* calibration);

/**
 * @brief Set sensor calibration data
 * @param calibration Pointer to calibration data structure
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType SensorInterface_SetCalibration(const SensorCalibration_t* calibration);

/**
 * @brief Perform sensor self-diagnosis
 * @return Std_ReturnType - E_OK if diagnosis passed, E_NOT_OK otherwise
 */
Std_ReturnType SensorInterface_SelfDiagnosis(void);

/**
 * @brief Deinitialize the Sensor Interface Software Component
 * @return Std_ReturnType - E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType SensorInterface_DeInit(void);

#endif /* SENSOR_INTERFACE_H */ 