/**
 * @file eps_diagnostics.h
 * @brief EPS Diagnostics Module Header
 * @version 1.0
 * @date 2025-07-29
 * 
 * Requirements: EPS-DR-001 to EPS-DR-143 (Diagnostic Requirements)
 */

#ifndef EPS_DIAGNOSTICS_H
#define EPS_DIAGNOSTICS_H

#include "eps_main.h"

/* Function Prototypes */
eps_result_t eps_diagnostics_init(void);
eps_result_t eps_diagnostics_update(const eps_sensor_data_t* sensor_data, 
                                   const eps_assistance_params_t* assistance_params);
eps_result_t eps_diagnostics_self_test(void);
void eps_diagnostics_set_dtc(eps_dtc_code_t dtc_code);
void eps_diagnostics_save_data(void);

#endif /* EPS_DIAGNOSTICS_H */