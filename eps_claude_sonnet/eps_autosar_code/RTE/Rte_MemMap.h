/**
 * @file Rte_MemMap.h
 * @brief AUTOSAR RTE Memory Mapping
 * @version 4.4.0
 * @date 2025-07-29
 * 
 * This file contains the AUTOSAR RTE memory mapping definitions according to
 * AUTOSAR R4.4 specification.
 * 
 * AUTOSAR Module: RTE Memory Mapping
 */

#ifndef RTE_MEMMAP_H
#define RTE_MEMMAP_H

/*******************************************************************************
 * RTE Code Memory Sections
 ******************************************************************************/

#ifdef RTE_START_SEC_CODE
    #undef RTE_START_SEC_CODE
    #define START_SEC_CODE
    #include "MemMap.h"
#endif

#ifdef RTE_STOP_SEC_CODE
    #undef RTE_STOP_SEC_CODE
    #define STOP_SEC_CODE
    #include "MemMap.h"
#endif

/*******************************************************************************
 * RTE Variable Memory Sections
 ******************************************************************************/

#ifdef RTE_START_SEC_VAR_INIT_UNSPECIFIED
    #undef RTE_START_SEC_VAR_INIT_UNSPECIFIED
    #define START_SEC_VAR_INIT_UNSPECIFIED
    #include "MemMap.h"
#endif

#ifdef RTE_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef RTE_STOP_SEC_VAR_INIT_UNSPECIFIED
    #define STOP_SEC_VAR
    #include "MemMap.h"
#endif

#ifdef RTE_START_SEC_VAR_NO_INIT_UNSPECIFIED
    #undef RTE_START_SEC_VAR_NO_INIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
    #include "MemMap.h"
#endif

#ifdef RTE_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
    #undef RTE_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
    #define STOP_SEC_VAR
    #include "MemMap.h"
#endif

/*******************************************************************************
 * RTE Constant Memory Sections
 ******************************************************************************/

#ifdef RTE_START_SEC_CONST_UNSPECIFIED
    #undef RTE_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
    #include "MemMap.h"
#endif

#ifdef RTE_STOP_SEC_CONST_UNSPECIFIED
    #undef RTE_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
    #include "MemMap.h"
#endif

#endif /* RTE_MEMMAP_H */