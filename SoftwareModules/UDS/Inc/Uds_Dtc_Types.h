/* @file UDS_DTC_TYPES_H */
#ifndef UDS_DTC_TYPES_H_
#define UDS_DTC_TYPES_H_

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Sharmili N (sharmili@niyatainfotech.com)                                                                     
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : Uds_Dtc_Types.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Agnostic (Independent)
*  Compilers supported             : XXXXX
*  Platforms supported             : XXXXX 
*  Description                     : This header file contains the Type defintions of Uds_Dtc 
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/
#include "hal_stdtypes.h"
/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/


/**
* @brief This macro is used to define the DTC setting ON status
* @Unit: N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define DTC_SETTING_ON          (uint8_t)0x01

/**
* @brief This macro is used to define the DTC setting OFF status
* @Unit: N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define DTC_SETTING_OFF         (uint8_t)0x02



/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef enum is used to define the DTC monitoring cycle status
 * @param    UDS_DTC_NOT_USED - DTC not used in current Server Version
 * @param    UDS_DTC_ERROR_OCCURRED - Test Failed, Error occurred
 * @param    UDS_DTC_ERROR_NOT_OCCURRED - Test Passed, No Error occurred
 **/
typedef enum
{
    UDS_DTC_NOT_USED = (uint8_t)0,
    UDS_DTC_ERROR_OCCURRED,
    UDS_DTC_ERROR_NOT_OCCURRED
}Uds_Dtc_Error_Status;

/**
 * @brief    This typedef is used as Pointer to the function process handler to be called for DTC error monitoring
 * @param    NULL
 **/
typedef Uds_Dtc_Error_Status (*Uds_Dtc_FunctionalProcess) (void);

/*
 * @brief    This structure is used to define the configurable functional structure's type
 * @param    l_Dtc_Index_u8     - DTC index as per configuration
 * @param    l_DTCGroup_u32     - DTC Group Value (3byte)
 * @param    l_BlockID_u16       - Nvm Block ID
 * @param    FunctionHandler    - Function Handler for executing
 * @param    l_WarningIndicator_Feature_bool - Warning Indicator Feature enable/disable
 **/
typedef struct
{
    uint8_t l_Dtc_Index_u8;
    uint32_t l_DTCGroup_u32;
    uint8_t l_BlockID_u16;
    Uds_Dtc_FunctionalProcess FunctionHandler;
    boolean l_WarningIndicator_Feature_bool;
}Uds_Dtc_Functional_Struct;

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                                                           
    REVISION DATE        : 26-June-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! UDS_DTC_TYPES_H_ */
