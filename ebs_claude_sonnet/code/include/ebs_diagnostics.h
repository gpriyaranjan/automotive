/**
 * @file ebs_diagnostics.h
 * @brief Electronic Braking System - Diagnostics Module
 */

#ifndef EBS_DIAGNOSTICS_H
#define EBS_DIAGNOSTICS_H

#include "ebs_types.h"
#include "ebs_config.h"

ebs_result_t EBS_Diagnostics_Init(void);
ebs_result_t EBS_Diagnostics_Process(void);
void EBS_Diagnostics_Shutdown(void);
ebs_result_t EBS_Diagnostics_SetDTC(ebs_dtc_code_t dtc);
ebs_result_t EBS_Diagnostics_LogEvent(ebs_diag_event_t event, uint32_t data);

#endif /* EBS_DIAGNOSTICS_H */
