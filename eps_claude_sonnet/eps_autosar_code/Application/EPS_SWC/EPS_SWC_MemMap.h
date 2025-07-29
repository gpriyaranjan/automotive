/**
 * @file EPS_SWC_MemMap.h
 * @brief AUTOSAR Memory Mapping for EPS Software Component
 * @version 4.4.0
 * @date 2025-07-29
 * 
 * This file contains the AUTOSAR memory mapping definitions for the
 * Electronic Power Steering (EPS) Software Component according to
 * AUTOSAR R4.4 specification.
 * 
 * AUTOSAR Module: Memory Mapping
 * Component: EPS_SWC
 */

#ifndef EPS_SWC_MEMMAP_H
#define EPS_SWC_MEMMAP_H

/*******************************************************************************
 * Memory Mapping Definitions
 ******************************************************************************/

/* Code Memory Sections */
#ifdef EPS_SWC_START_SEC_CODE
    #undef EPS_SWC_START_SEC_CODE
    #define START_SEC_CODE
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_CODE
    #undef EPS_SWC_STOP_SEC_CODE
    #define STOP_SEC_CODE
    #include "MemMap.h"
#endif

/* Initialized Variable Memory Sections */
#ifdef EPS_SWC_START_SEC_VAR_INIT_8
    #undef EPS_SWC_START_SEC_VAR_INIT_8
    #define START_SEC_VAR_INIT_8BIT
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_VAR_INIT_8
    #undef EPS_SWC_STOP_SEC_VAR_INIT_8
    #define STOP_SEC_VAR
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_START_SEC_VAR_INIT_16
    #undef EPS_SWC_START_SEC_VAR_INIT_16
    #define START_SEC_VAR_INIT_16BIT
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_VAR_INIT_16
    #undef EPS_SWC_STOP_SEC_VAR_INIT_16
    #define STOP_SEC_VAR
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_START_SEC_VAR_INIT_32
    #undef EPS_SWC_START_SEC_VAR_INIT_32
    #define START_SEC_VAR_INIT_32BIT
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_VAR_INIT_32
    #undef EPS_SWC_STOP_SEC_VAR_INIT_32
    #define STOP_SEC_VAR
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_START_SEC_VAR_INIT_UNSPECIFIED
    #undef EPS_SWC_START_SEC_VAR_INIT_UNSPECIFIED
    #define START_SEC_VAR_INIT_UNSPECIFIED
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef EPS_SWC_STOP_SEC_VAR_INIT_UNSPECIFIED
    #define STOP_SEC_VAR
    #include "MemMap.h"
#endif

/* Uninitialized Variable Memory Sections */
#ifdef EPS_SWC_START_SEC_VAR_NO_INIT_8
    #undef EPS_SWC_START_SEC_VAR_NO_INIT_8
    #define START_SEC_VAR_NOINIT_8BIT
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_VAR_NO_INIT_8
    #undef EPS_SWC_STOP_SEC_VAR_NO_INIT_8
    #define STOP_SEC_VAR
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_START_SEC_VAR_NO_INIT_16
    #undef EPS_SWC_START_SEC_VAR_NO_INIT_16
    #define START_SEC_VAR_NOINIT_16BIT
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_VAR_NO_INIT_16
    #undef EPS_SWC_STOP_SEC_VAR_NO_INIT_16
    #define STOP_SEC_VAR
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_START_SEC_VAR_NO_INIT_32
    #undef EPS_SWC_START_SEC_VAR_NO_INIT_32
    #define START_SEC_VAR_NOINIT_32BIT
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_VAR_NO_INIT_32
    #undef EPS_SWC_STOP_SEC_VAR_NO_INIT_32
    #define STOP_SEC_VAR
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_START_SEC_VAR_NO_INIT_UNSPECIFIED
    #undef EPS_SWC_START_SEC_VAR_NO_INIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
    #undef EPS_SWC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
    #define STOP_SEC_VAR
    #include "MemMap.h"
#endif

/* Constant Memory Sections */
#ifdef EPS_SWC_START_SEC_CONST_8
    #undef EPS_SWC_START_SEC_CONST_8
    #define START_SEC_CONST_8BIT
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_CONST_8
    #undef EPS_SWC_STOP_SEC_CONST_8
    #define STOP_SEC_CONST
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_START_SEC_CONST_16
    #undef EPS_SWC_START_SEC_CONST_16
    #define START_SEC_CONST_16BIT
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_CONST_16
    #undef EPS_SWC_STOP_SEC_CONST_16
    #define STOP_SEC_CONST
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_START_SEC_CONST_32
    #undef EPS_SWC_START_SEC_CONST_32
    #define START_SEC_CONST_32BIT
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_CONST_32
    #undef EPS_SWC_STOP_SEC_CONST_32
    #define STOP_SEC_CONST
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_START_SEC_CONST_UNSPECIFIED
    #undef EPS_SWC_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_CONST_UNSPECIFIED
    #undef EPS_SWC_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
    #include "MemMap.h"
#endif

/* Calibration Memory Sections */
#ifdef EPS_SWC_START_SEC_CALIB_8
    #undef EPS_SWC_START_SEC_CALIB_8
    #define START_SEC_CONST_8BIT
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_CALIB_8
    #undef EPS_SWC_STOP_SEC_CALIB_8
    #define STOP_SEC_CONST
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_START_SEC_CALIB_16
    #undef EPS_SWC_START_SEC_CALIB_16
    #define START_SEC_CONST_16BIT
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_CALIB_16
    #undef EPS_SWC_STOP_SEC_CALIB_16
    #define STOP_SEC_CONST
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_START_SEC_CALIB_32
    #undef EPS_SWC_START_SEC_CALIB_32
    #define START_SEC_CONST_32BIT
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_CALIB_32
    #undef EPS_SWC_STOP_SEC_CALIB_32
    #define STOP_SEC_CONST
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_START_SEC_CALIB_UNSPECIFIED
    #undef EPS_SWC_START_SEC_CALIB_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
    #include "MemMap.h"
#endif

#ifdef EPS_SWC_STOP_SEC_CALIB_UNSPECIFIED
    #undef EPS_SWC_STOP_SEC_CALIB_UNSPECIFIED
    #define STOP_SEC_CONST
    #include "MemMap.h"
#endif

#endif /* EPS_SWC_MEMMAP_H */