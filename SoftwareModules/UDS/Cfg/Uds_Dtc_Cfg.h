/* @file FILE NAME */
#ifndef UDS_DTC_CFG_H
#define UDS_DTC_CFG_H

/***********************************************************************************************************************
*   DISCLAIMER
*   Copyright © 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : Uds_Dtc_Cfg.h
*  Generation Time                 : 18-10-2022 16:41:17
*  Tool Version                    : UDS_Configurator  2.2.1.0
*  Description                     : This header file contains the configuration declarations of Uds_Dtc Core Layer
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
#include "Uds_Dtc_Types.h"
/***********************************************************************************************************************
*                                    C O N F I G U R A T I O N     M A C R O S                      
***********************************************************************************************************************/
/*
* @brief: This macro is used to configure the maximum DTCs supported by the Server
* @Unit:  N/A
* @Resolution: 1 
* @Range: 1 - 255
* @Applicability: Yes 
* @Note: Size of this array variable UDs_Dtc_Process_TableConfig is dependent on this macro.
*/
#define UDS_DTC_MAX_CFG             (uint8_t)3

/*
* @brief This macro is used to define the Operation cycle's ON condition
* @Unit:  N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: Mandatory
* @Note:  Operation Cycle's start conditions are to be defined by Vehicle Manufacturer
*/
#define UDS_DTC_OPERATION_CYCLE_RUN_CONDITION  (uint8_t)0

/*
* @brief This macro is used to define the Operation cycle's OFF condition
* @Unit:  N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: Mandatory
* @Note:  Operation Cycle's stop conditions are to be defined by Vehicle Manufacturer
*/
#define UDS_DTC_OPERATION_CYCLE_STOP_CONDITION  (uint8_t)1

/*
* @brief This macro is used to configure the Aging Counter's maximum threshold value for this Server
* @Unit: N/A 
* @Resolution: User-Specific 
* @Range: 0-255
* @Applicability: YES 
* @Note:  N/A
*/
#define UDS_DTC_AGING_COUNTER_THRESHOLD_VALUE         (uint8_t)3

/*
* @brief This macro is used to configure the Fault Detection Counter's maximum threshold value for this Server 
* @Unit: N/A 
* @Resolution: User-Specific
* @Range: 0-255
* @Applicability: YES 
* @Note: N/A
*/
#define UDS_DTC_FDC_THRESHOLD_VALUE  (uint8_t)251

/*
* @brief This macro is used to Enable/Disable the DTC Setting ON and OFF feature based on the application
* @Unit: N/A 
* @Resolution: N/A 
* @Range: STD_ON (Enable)/ STD_OFF (Disable)
* @Applicability: If 0x85 service is made use, this feature should be enabled
* @Note: N/A 
*/
#define UDS_DTC_SETTING_LOCK_FEATURE        STD_OFF

/*
* @brief This macro is used to specify the size of a Local Snapshot record
* @Unit: Byte 
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: N/A 
*/
#define UDS_DTC_LOCAL_SS_SIZE           (uint8_t)19

/*
* @brief This macro is used to specify the size of a Global Snapshot record
* @Unit: Byte 
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: N/A 
*/
#define UDS_DTC_GLOBAL_SS_SIZE           (uint8_t)10

/*
* @brief This macro is used to specify the Status bits availability for the Server
* @Unit: N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: YES
* @Note: N/A
*/
#define UDS_DTC_STATUS_AVAILABILITY_MASK        (uint8_t)0xFF

/*
* @brief This macro is used to map the Nvm Read operation
* @Unit: N/A 
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: N/A 
*/
#define UDS_DTC_READ_NVM(a, b, c, d)            0    

/*
* @brief This macro is used to map the Nvm write operation
* @Unit: N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: YES
* @Note: N/A
*/
#define UDS_DTC_WRITE_NVM(a, b)                 0         

/*
* @brief This macro is used to map the Nvm Manager Status Getter function
* @Unit: N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: YES
* @Note: N/A
*/
#define UDS_DTC_GET_NVM_MGR_STATUS(a)   Nvm_Mgr_GetStatus(a)

/*
* @brief This macro is used to map the Nvm Manager's Idle state value
* @Unit: N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: YES
* @Note: N/A
*/
#define UDS_DTC_NVM_MGR_IDLE           NVM_MGR_SM_STATE_IDLE

/*
* @brief This macro is used to map the Nvm write operation
* @Unit: N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: YES
* @Note: N/A
*/
#define UDS_DTC_FIRST_POWERUP_BLOCK_ID      (uint16_t)12
/***********************************************************************************************************************
*                             C O N F I G U R A T I O N    C O N S T A N T S    D E C L A R A T I O N                       
***********************************************************************************************************************/
/*
* @brief: This variable is used to configure the DTC Process Table
* @Unit:  N/A
* @Resolution: N/A 
* @Range: N/A
* @Applicability: Yes
* @Note: This is a mandatory configuration to execute the Main function of Uds_Dtc core layer 
*/
extern const Uds_Dtc_Functional_Struct Uds_Dtc_Process_TableConfig[UDS_DTC_MAX_CFG];


/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* ! UDS_DTC_CFG_H */
