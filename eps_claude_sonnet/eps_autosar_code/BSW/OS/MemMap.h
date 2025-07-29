/**
 * @file MemMap.h
 * @brief AUTOSAR Memory Mapping Base File
 * @version 4.4.0
 * @date 2025-07-29
 * 
 * This file contains the base AUTOSAR memory mapping definitions according to
 * AUTOSAR R4.4 specification for ARM Cortex-M4 platform.
 * 
 * AUTOSAR Module: Memory Mapping
 * Platform: ARM Cortex-M4
 */

#ifndef MEMMAP_H
#define MEMMAP_H

/*******************************************************************************
 * Memory Mapping Configuration
 ******************************************************************************/

/* Code Memory Sections */
#ifdef START_SEC_CODE
    #undef START_SEC_CODE
    #pragma section code "CODE"
#endif

#ifdef STOP_SEC_CODE
    #undef STOP_SEC_CODE
    #pragma section code restore
#endif

/* Fast Code Memory Sections */
#ifdef START_SEC_CODE_FAST
    #undef START_SEC_CODE_FAST
    #pragma section code "CODE_FAST"
#endif

#ifdef STOP_SEC_CODE_FAST
    #undef STOP_SEC_CODE_FAST
    #pragma section code restore
#endif

/* Slow Code Memory Sections */
#ifdef START_SEC_CODE_SLOW
    #undef START_SEC_CODE_SLOW
    #pragma section code "CODE_SLOW"
#endif

#ifdef STOP_SEC_CODE_SLOW
    #undef STOP_SEC_CODE_SLOW
    #pragma section code restore
#endif

/* Initialized Variable Memory Sections */
#ifdef START_SEC_VAR_INIT_8BIT
    #undef START_SEC_VAR_INIT_8BIT
    #pragma section data "VAR_INIT_8"
#endif

#ifdef START_SEC_VAR_INIT_16BIT
    #undef START_SEC_VAR_INIT_16BIT
    #pragma section data "VAR_INIT_16"
#endif

#ifdef START_SEC_VAR_INIT_32BIT
    #undef START_SEC_VAR_INIT_32BIT
    #pragma section data "VAR_INIT_32"
#endif

#ifdef START_SEC_VAR_INIT_UNSPECIFIED
    #undef START_SEC_VAR_INIT_UNSPECIFIED
    #pragma section data "VAR_INIT"
#endif

/* Uninitialized Variable Memory Sections */
#ifdef START_SEC_VAR_NOINIT_8BIT
    #undef START_SEC_VAR_NOINIT_8BIT
    #pragma section bss "VAR_NOINIT_8"
#endif

#ifdef START_SEC_VAR_NOINIT_16BIT
    #undef START_SEC_VAR_NOINIT_16BIT
    #pragma section bss "VAR_NOINIT_16"
#endif

#ifdef START_SEC_VAR_NOINIT_32BIT
    #undef START_SEC_VAR_NOINIT_32BIT
    #pragma section bss "VAR_NOINIT_32"
#endif

#ifdef START_SEC_VAR_NOINIT_UNSPECIFIED
    #undef START_SEC_VAR_NOINIT_UNSPECIFIED
    #pragma section bss "VAR_NOINIT"
#endif

/* Fast Variable Memory Sections */
#ifdef START_SEC_VAR_FAST_INIT_8BIT
    #undef START_SEC_VAR_FAST_INIT_8BIT
    #pragma section data "VAR_FAST_INIT_8"
#endif

#ifdef START_SEC_VAR_FAST_INIT_16BIT
    #undef START_SEC_VAR_FAST_INIT_16BIT
    #pragma section data "VAR_FAST_INIT_16"
#endif

#ifdef START_SEC_VAR_FAST_INIT_32BIT
    #undef START_SEC_VAR_FAST_INIT_32BIT
    #pragma section data "VAR_FAST_INIT_32"
#endif

#ifdef START_SEC_VAR_FAST_INIT_UNSPECIFIED
    #undef START_SEC_VAR_FAST_INIT_UNSPECIFIED
    #pragma section data "VAR_FAST_INIT"
#endif

#ifdef START_SEC_VAR_FAST_NOINIT_8BIT
    #undef START_SEC_VAR_FAST_NOINIT_8BIT
    #pragma section bss "VAR_FAST_NOINIT_8"
#endif

#ifdef START_SEC_VAR_FAST_NOINIT_16BIT
    #undef START_SEC_VAR_FAST_NOINIT_16BIT
    #pragma section bss "VAR_FAST_NOINIT_16"
#endif

#ifdef START_SEC_VAR_FAST_NOINIT_32BIT
    #undef START_SEC_VAR_FAST_NOINIT_32BIT
    #pragma section bss "VAR_FAST_NOINIT_32"
#endif

#ifdef START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #undef START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #pragma section bss "VAR_FAST_NOINIT"
#endif

/* Constant Memory Sections */
#ifdef START_SEC_CONST_8BIT
    #undef START_SEC_CONST_8BIT
    #pragma section const "CONST_8"
#endif

#ifdef START_SEC_CONST_16BIT
    #undef START_SEC_CONST_16BIT
    #pragma section const "CONST_16"
#endif

#ifdef START_SEC_CONST_32BIT
    #undef START_SEC_CONST_32BIT
    #pragma section const "CONST_32"
#endif

#ifdef START_SEC_CONST_UNSPECIFIED
    #undef START_SEC_CONST_UNSPECIFIED
    #pragma section const "CONST"
#endif

/* Fast Constant Memory Sections */
#ifdef START_SEC_CONST_FAST_8BIT
    #undef START_SEC_CONST_FAST_8BIT
    #pragma section const "CONST_FAST_8"
#endif

#ifdef START_SEC_CONST_FAST_16BIT
    #undef START_SEC_CONST_FAST_16BIT
    #pragma section const "CONST_FAST_16"
#endif

#ifdef START_SEC_CONST_FAST_32BIT
    #undef START_SEC_CONST_FAST_32BIT
    #pragma section const "CONST_FAST_32"
#endif

#ifdef START_SEC_CONST_FAST_UNSPECIFIED
    #undef START_SEC_CONST_FAST_UNSPECIFIED
    #pragma section const "CONST_FAST"
#endif

/* Calibration Memory Sections */
#ifdef START_SEC_CALIB_8BIT
    #undef START_SEC_CALIB_8BIT
    #pragma section const "CALIB_8"
#endif

#ifdef START_SEC_CALIB_16BIT
    #undef START_SEC_CALIB_16BIT
    #pragma section const "CALIB_16"
#endif

#ifdef START_SEC_CALIB_32BIT
    #undef START_SEC_CALIB_32BIT
    #pragma section const "CALIB_32"
#endif

#ifdef START_SEC_CALIB_UNSPECIFIED
    #undef START_SEC_CALIB_UNSPECIFIED
    #pragma section const "CALIB"
#endif

/* Configuration Data Memory Sections */
#ifdef START_SEC_CONFIG_DATA_8BIT
    #undef START_SEC_CONFIG_DATA_8BIT
    #pragma section const "CONFIG_DATA_8"
#endif

#ifdef START_SEC_CONFIG_DATA_16BIT
    #undef START_SEC_CONFIG_DATA_16BIT
    #pragma section const "CONFIG_DATA_16"
#endif

#ifdef START_SEC_CONFIG_DATA_32BIT
    #undef START_SEC_CONFIG_DATA_32BIT
    #pragma section const "CONFIG_DATA_32"
#endif

#ifdef START_SEC_CONFIG_DATA_UNSPECIFIED
    #undef START_SEC_CONFIG_DATA_UNSPECIFIED
    #pragma section const "CONFIG_DATA"
#endif

/* Stop Sections */
#ifdef STOP_SEC_VAR
    #undef STOP_SEC_VAR
    #pragma section data restore
    #pragma section bss restore
#endif

#ifdef STOP_SEC_CONST
    #undef STOP_SEC_CONST
    #pragma section const restore
#endif

/* Application Data Memory Sections */
#ifdef START_SEC_APPL_CODE
    #undef START_SEC_APPL_CODE
    #pragma section code "APPL_CODE"
#endif

#ifdef STOP_SEC_APPL_CODE
    #undef STOP_SEC_APPL_CODE
    #pragma section code restore
#endif

#ifdef START_SEC_APPL_DATA
    #undef START_SEC_APPL_DATA
    #pragma section data "APPL_DATA"
#endif

#ifdef STOP_SEC_APPL_DATA
    #undef STOP_SEC_APPL_DATA
    #pragma section data restore
#endif

/* Shared Memory Sections */
#ifdef START_SEC_SHARED_DATA
    #undef START_SEC_SHARED_DATA
    #pragma section data "SHARED_DATA"
#endif

#ifdef STOP_SEC_SHARED_DATA
    #undef STOP_SEC_SHARED_DATA
    #pragma section data restore
#endif

#endif /* MEMMAP_H */