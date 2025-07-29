/**
 * @file ebs_sensors.h
 * @brief Electronic Braking System - Sensor Interface Module
 */

#ifndef EBS_SENSORS_H
#define EBS_SENSORS_H

#include "ebs_types.h"
#include "ebs_config.h"

ebs_result_t EBS_Sensors_Init(void);
bool EBS_Sensors_SelfTest(void);
ebs_result_t EBS_Sensors_ReadAll(void);
ebs_wheel_speed_data_t* EBS_Sensors_GetWheelSpeedData(void);
ebs_pressure_data_t* EBS_Sensors_GetPressureData(void);
ebs_imu_data_t* EBS_Sensors_GetIMUData(void);

#endif /* EBS_SENSORS_H */
