/* @file UDS_DTC_CFG_C */
#ifndef UDS_DTC_CFG_C
#define UDS_DTC_CFG_C

/***********************************************************************************************************************
*   DISCLAIMER
*   Copyright © 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
*
*  File name                       : Uds_Dtc_Cfg.c
*  Generation Time                 : 18-10-2022 16:41:17
*  Tool Version                    : UDS_Configurator  2.2.1.0
*  Description                     : This header file contains the configuration definitions of Uds_Dtc Core Layer
*  @bug                            : N/A
*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                            
***********************************************************************************************************************/
#include "Uds_Dtc_Cfg.h"
#include "Uds_Dtc_Types.h"
#include "hal_stdtypes.h"
//#include "Sample_APP.h"
/***********************************************************************************************************************
*                             C O N F I G U R A T I O N    C O N S T A N T S   D E F I N I T I O N                          
***********************************************************************************************************************/
/*
 * @brief    This structure is used to define the configurable functional structure's type
 * @param    l_Dtc_Index_u8     - DTC index as per configuration
 * @param    l_DTCGroup_u32     - DTC Group Value (3byte)
 * @param    l_BlockID_u16       - Nvm Block ID
 * @param    FunctionHandler    - Function Handler for executing
 * @param    l_WarningIndicator_Feature_bool - Warning Indicator Feature enable/disable
 * 
 * Example:
 * extern const Uds_Dtc_Functional_Struct Uds_Dtc_Process_TableConfig[UDS_DTC_MAX_CFG] = {
    {
        (uint8_t)0,
        (uint32_t)0x101010,
        (uint16_t)9,
        NULL,
        (boolean)FALSE
    },
    {
        (uint8_t)0,
        (uint32_t)0x202020,
        (uint16_t)10,
        NULL,
        (boolean)FALSE
    }
    };
 **/
 const Uds_Dtc_Functional_Struct Uds_Dtc_Process_TableConfig[UDS_DTC_MAX_CFG] = {
    {
        (uint8_t)0,
        (uint32_t)0x101010,
        (uint16_t)9,
        NULL,
        (bool)FALSE
    },
    {
        (uint8_t)0,
        (uint32_t)0x202020,
        (uint16_t)10,
		NULL,
        (bool)FALSE
    },
    {
        (uint8_t)0,
        (uint32_t)0X303030,
        (uint16_t)11,
		NULL,
        (bool)FALSE
    }
};
/***********************************************************************************************************************
*                           C O N F I G U R A T I O N    V A R I A B L E S    D E F I N I T I O N                                            
***********************************************************************************************************************/
/*
* @brief This variable is used to configure the 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/

/*********************************************************************************************************************
*                         C O N F I G U R A T I O N     F U N C T I O N    D E F I N I T I O N S                      
*********************************************************************************************************************/
/*
* @brief    This function is used to 
* @param    
* @return 
* @note:  
*/

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* ! UDS_DTC_CFG_C */
