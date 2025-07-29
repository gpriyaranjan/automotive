/**
 * @file ebs_communication.h
 * @brief Electronic Braking System - Communication Module
 */

#ifndef EBS_COMMUNICATION_H
#define EBS_COMMUNICATION_H

#include "ebs_types.h"
#include "ebs_config.h"

ebs_result_t EBS_Communication_Init(void);
bool EBS_Communication_SelfTest(void);
ebs_result_t EBS_Communication_Process(void);
void EBS_Communication_Shutdown(void);

#endif /* EBS_COMMUNICATION_H */