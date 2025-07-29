/**
 * @file Platform_Types.h
 * @brief AUTOSAR Platform Types Definition
 * @version 4.4.0
 * @date 2025-07-29
 * 
 * This file contains the AUTOSAR platform-specific type definitions according to
 * AUTOSAR R4.4 specification for ARM Cortex-M4 platform.
 * 
 * AUTOSAR Module: Platform Types
 * Module ID: 199
 * Vendor ID: 1
 */

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*******************************************************************************
 * Version Information
 ******************************************************************************/
#define PLATFORM_VENDOR_ID                 (1U)
#define PLATFORM_MODULE_ID                 (199U)
#define PLATFORM_AR_RELEASE_MAJOR_VERSION  (4U)
#define PLATFORM_AR_RELEASE_MINOR_VERSION  (4U)
#define PLATFORM_AR_RELEASE_REVISION_VERSION (0U)
#define PLATFORM_SW_MAJOR_VERSION          (1U)
#define PLATFORM_SW_MINOR_VERSION          (0U)
#define PLATFORM_SW_PATCH_VERSION          (0U)

/*******************************************************************************
 * CPU Type and Endianness
 ******************************************************************************/
#define CPU_TYPE_8              8U
#define CPU_TYPE_16             16U
#define CPU_TYPE_32             32U
#define CPU_TYPE_64             64U

#define MSB_FIRST               0U    /* Big endian bit ordering */
#define LSB_FIRST               1U    /* Little endian bit ordering */

#define HIGH_BYTE_FIRST         0U    /* Big endian byte ordering */
#define LOW_BYTE_FIRST          1U    /* Little endian byte ordering */

/*******************************************************************************
 * Platform Configuration for ARM Cortex-M4
 ******************************************************************************/
#define CPU_TYPE                CPU_TYPE_32
#define CPU_BIT_ORDER           LSB_FIRST
#define CPU_BYTE_ORDER          LOW_BYTE_FIRST

/*******************************************************************************
 * AUTOSAR Integer Data Types
 ******************************************************************************/
typedef unsigned char           boolean;

typedef signed char             sint8;
typedef unsigned char           uint8;
typedef signed short            sint16;
typedef unsigned short          uint16;
typedef signed long             sint32;
typedef unsigned long           uint32;
typedef signed long long        sint64;
typedef unsigned long long      uint64;

typedef signed char             sint8_least;
typedef unsigned char           uint8_least;
typedef signed short            sint16_least;
typedef unsigned short          uint16_least;
typedef signed long             sint32_least;
typedef unsigned long           uint32_least;

/*******************************************************************************
 * AUTOSAR Floating Point Data Types
 ******************************************************************************/
typedef float                   float32;
typedef double                  float64;

/*******************************************************************************
 * AUTOSAR Boolean Values
 ******************************************************************************/
#ifndef TRUE
#define TRUE                    ((boolean)1U)
#endif

#ifndef FALSE
#define FALSE                   ((boolean)0U)
#endif

/*******************************************************************************
 * AUTOSAR Optimized Integer Data Types
 ******************************************************************************/
typedef signed long             sint8_fast;
typedef unsigned long           uint8_fast;
typedef signed long             sint16_fast;
typedef unsigned long           uint16_fast;
typedef signed long             sint32_fast;
typedef unsigned long           uint32_fast;

/*******************************************************************************
 * AUTOSAR Pointer Types
 ******************************************************************************/
typedef void*                   VoidPtr;
typedef const void*             ConstVoidPtr;

/*******************************************************************************
 * AUTOSAR Size Types
 ******************************************************************************/
typedef unsigned long           PtrDiffType;
typedef unsigned long           PtrToIntType;
typedef unsigned long           IntToPtr;

/*******************************************************************************
 * Platform-Specific Definitions
 ******************************************************************************/
#define PLATFORM_SUPPORT_SINT64_UINT64     STD_ON
#define PLATFORM_SUPPORT_FLOAT             STD_ON
#define PLATFORM_SUPPORT_DOUBLE            STD_ON

/*******************************************************************************
 * Memory Alignment
 ******************************************************************************/
#define PLATFORM_ALIGNMENT_8BIT            1U
#define PLATFORM_ALIGNMENT_16BIT           2U
#define PLATFORM_ALIGNMENT_32BIT           4U
#define PLATFORM_ALIGNMENT_64BIT           8U

/*******************************************************************************
 * Register Width
 ******************************************************************************/
#define PLATFORM_REGISTER_WIDTH            32U

/*******************************************************************************
 * Atomic Operations Support
 ******************************************************************************/
#define PLATFORM_SUPPORT_ATOMIC_8BIT       STD_ON
#define PLATFORM_SUPPORT_ATOMIC_16BIT      STD_ON
#define PLATFORM_SUPPORT_ATOMIC_32BIT      STD_ON
#define PLATFORM_SUPPORT_ATOMIC_64BIT      STD_OFF

#endif /* PLATFORM_TYPES_H */