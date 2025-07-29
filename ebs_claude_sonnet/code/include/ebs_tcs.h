/**
 * @file ebs_tcs.h
 * @brief Electronic Braking System - Traction Control System Module
 */

#ifndef EBS_TCS_H
#define EBS_TCS_H

#include "ebs_types.h"
#include "ebs_config.h"

ebs_result_t EBS_TCS_Init(void);
bool EBS_TCS_SelfTest(void);
ebs_result_t EBS_TCS_Control(void);
ebs_tcs_state_t EBS_TCS_GetState(void);
bool EBS_TCS_IsActive(void);

#endif /* EBS_TCS_H */