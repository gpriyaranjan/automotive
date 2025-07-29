/**
 * @file ebs_esc.h
 * @brief Electronic Braking System - Electronic Stability Control Module
 * @version 1.0
 * @date 2025-07-29
 * @author EBS Development Team
 * 
 * ESC control algorithm and functions
 * 
 * Safety Level: ASIL-D
 * Compliance: ISO 26262, UN-ECE R13-H
 */

#ifndef EBS_ESC_H
#define EBS_ESC_H

#include "ebs_types.h"
#include "ebs_config.h"

/* ESC Function Prototypes */
ebs_result_t EBS_ESC_Init(void);
bool EBS_ESC_SelfTest(void);
ebs_result_t EBS_ESC_Control(void);
ebs_esc_state_t EBS_ESC_GetState(void);
bool EBS_ESC_IsActive(void);
float EBS_ESC_CalculateReferenceYawRate(float vehicle_speed, float steering_angle);
ebs_result_t EBS_ESC_Enable(bool enable);
bool EBS_ESC_HealthCheck(void);

#endif /* EBS_ESC_H */