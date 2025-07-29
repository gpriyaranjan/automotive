/**
 * @file Std_Types.h
 * @brief AUTOSAR Standard Types Definition
 * @version 4.4.0
 * @date 2025-07-29
 * 
 * This file contains the AUTOSAR standard type definitions according to
 * AUTOSAR R4.4 specification.
 * 
 * AUTOSAR Module: Standard Types
 * Module ID: 197
 * Vendor ID: 1
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

/*******************************************************************************
 * Version Information
 ******************************************************************************/
#define STD_TYPES_VENDOR_ID                 (1U)
#define STD_TYPES_MODULE_ID                 (197U)
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION  (4U)
#define STD_TYPES_AR_RELEASE_MINOR_VERSION  (4U)
#define STD_TYPES_AR_RELEASE_REVISION_VERSION (0U)
#define STD_TYPES_SW_MAJOR_VERSION          (1U)
#define STD_TYPES_SW_MINOR_VERSION          (0U)
#define STD_TYPES_SW_PATCH_VERSION          (0U)

/*******************************************************************************
 * Platform Types Include
 ******************************************************************************/
#include "Platform_Types.h"

/*******************************************************************************
 * AUTOSAR Standard Return Type
 ******************************************************************************/
typedef uint8 Std_ReturnType;

#define E_OK                    ((Std_ReturnType)0x00U)
#define E_NOT_OK                ((Std_ReturnType)0x01U)

/*******************************************************************************
 * AUTOSAR Standard Version Info Type
 ******************************************************************************/
typedef struct {
    uint16 vendorID;
    uint16 moduleID;
    uint8 sw_major_version;
    uint8 sw_minor_version;
    uint8 sw_patch_version;
} Std_VersionInfoType;

/*******************************************************************************
 * AUTOSAR Standard Transformation Types
 ******************************************************************************/
typedef uint8 Std_TransformerErrorCode;

#define STD_TRANSFORMER_UNSPECIFIED        ((Std_TransformerErrorCode)0x00U)
#define STD_TRANSFORMER_SERIALIZER_ERROR   ((Std_TransformerErrorCode)0x01U)
#define STD_TRANSFORMER_SAFETY_ERROR       ((Std_TransformerErrorCode)0x02U)
#define STD_TRANSFORMER_CUSTOM_ERROR       ((Std_TransformerErrorCode)0x03U)

typedef uint8 Std_MessageTypeType;
typedef uint32 Std_MessageLengthType;
typedef uint8 Std_MessageResultType;

#define STD_MESSAGETYPE_REQUEST             ((Std_MessageTypeType)0x00U)
#define STD_MESSAGETYPE_RESPONSE            ((Std_MessageTypeType)0x01U)

#define STD_MESSAGERESULT_OK                ((Std_MessageResultType)0x00U)
#define STD_MESSAGERESULT_ERROR             ((Std_MessageResultType)0x01U)

/*******************************************************************************
 * AUTOSAR Standard Macros
 ******************************************************************************/
#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
#define E_OK                    0x00U
typedef unsigned char StatusType; /* OSEK compliance */
#endif

#define STD_HIGH                0x01U   /* Physical state 5V or 3.3V */
#define STD_LOW                 0x00U   /* Physical state 0V */

#define STD_ACTIVE              0x01U   /* Logical state active */
#define STD_IDLE                0x00U   /* Logical state idle */

#define STD_ON                  0x01U
#define STD_OFF                 0x00U

/*******************************************************************************
 * AUTOSAR Memory Classes
 ******************************************************************************/
#define AUTOMATIC
#define STATIC                  static
#define NULL_PTR                ((void*)0)

/*******************************************************************************
 * AUTOSAR Function Macros
 ******************************************************************************/
#define FUNC(rettype, memclass) rettype
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype*
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype*
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype* const
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype* const
#define P2FUNC(rettype, ptrclass, fctname) rettype (*fctname)
#define CONST(consttype, memclass) const consttype
#define VAR(vartype, memclass) vartype

/*******************************************************************************
 * AUTOSAR Memory Classes for Variables
 ******************************************************************************/
#define TYPEDEF

/*******************************************************************************
 * AUTOSAR Compiler Abstraction
 ******************************************************************************/
#define INLINE                  inline
#define LOCAL_INLINE            static inline

#endif /* STD_TYPES_H */