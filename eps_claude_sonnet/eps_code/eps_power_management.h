/**
 * @file eps_power_management.h
 * @brief EPS Power Management Module Header
 * @version 1.0
 * @date 2025-07-29
 * 
 * Requirements: EPS-ER-001 to EPS-ER-151 (Electrical and Power Requirements)
 */

#ifndef EPS_POWER_MANAGEMENT_H
#define EPS_POWER_MANAGEMENT_H

#include "eps_main.h"

/* Power Constants */
#define EPS_MAX_CONTINUOUS_POWER_W      150.0f  /* W - EPS-PR-055 */
#define EPS_MAX_PEAK_POWER_W            300.0f  /* W - EPS-PR-056 */
#define EPS_STANDBY_POWER_MW            50.0f   /* mW - EPS-PR-057 */

/* Function Prototypes */
eps_result_t eps_power_management_init(void);
void eps_power_management_sleep(void);
float eps_power_get_consumption(void);

#endif /* EPS_POWER_MANAGEMENT_H */