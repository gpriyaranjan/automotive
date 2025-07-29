/**
 * @file ebs_watchdog.h
 * @brief Electronic Braking System - Watchdog Module
 */

#ifndef EBS_WATCHDOG_H
#define EBS_WATCHDOG_H

#include "ebs_types.h"
#include "ebs_config.h"

ebs_result_t EBS_Watchdog_Init(void);
ebs_result_t EBS_Watchdog_Refresh(ebs_watchdog_type_t watchdog_type);

/* HAL Functions */
ebs_result_t EBS_HAL_Init(void);

#endif /* EBS_WATCHDOG_H */