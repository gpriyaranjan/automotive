/**
 * @file eps_communication.h
 * @brief EPS Communication Module Header
 * @version 1.0
 * @date 2025-07-29
 * 
 * Requirements: EPS-IR-001 to EPS-IR-024 (CAN/LIN Communication)
 */

#ifndef EPS_COMMUNICATION_H
#define EPS_COMMUNICATION_H

#include "eps_main.h"

/* CAN Message IDs */
#define EPS_CAN_MSG_STEERING_ANGLE      0x101
#define EPS_CAN_MSG_SYSTEM_STATUS       0x102
#define EPS_CAN_MSG_ASSISTANCE_TORQUE   0x103
#define EPS_CAN_MSG_VEHICLE_SPEED       0x201

/* Function Prototypes */
eps_result_t eps_communication_init(void);
eps_result_t eps_communication_update(const eps_sensor_data_t* sensor_data, 
                                     const eps_assistance_params_t* assistance_params);
eps_result_t eps_communication_self_test(void);

#endif /* EPS_COMMUNICATION_H */