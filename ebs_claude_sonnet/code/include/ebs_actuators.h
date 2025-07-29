/**
 * @file ebs_actuators.h
 * @brief Electronic Braking System - Actuator Control Module
 */

#ifndef EBS_ACTUATORS_H
#define EBS_ACTUATORS_H

#include "ebs_types.h"
#include "ebs_config.h"

ebs_result_t EBS_Actuators_Init(void);
bool EBS_Actuators_SelfTest(void);
ebs_result_t EBS_Actuators_Update(void);
ebs_result_t EBS_Actuators_SetPressure(ebs_wheel_position_t wheel, float pressure);
void EBS_Actuators_Shutdown(void);
void EBS_Actuators_EmergencyStop(void);

#endif /* EBS_ACTUATORS_H */
