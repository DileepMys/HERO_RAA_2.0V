/* @file UDS_CFG_H */
#ifndef UDS_CFG_H
#define UDS_CFG_H

/***********************************************************************************************************************
*   DISCLAIMER
*   Copyright © 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : UDS_Cfg.h
*  Generation Time                 : 18-10-2022 16:41:17
*  Tool Version                    : UDS_Configurator  2.2.1.0
*  Description                     : This file contains the configuration elements of UDS Core Layer
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
#include "UDS.h"
#include "CanMgr.h"
//#include "Oem_Dwnld_Mgr.h"
/***********************************************************************************************************************
*                                    CONFIGURATION MACROS                      
***********************************************************************************************************************/
/*
* @brief: This macro is used to configure the P2 timer maximum count to be maintained in milliseconds
  @Unit:  milliseconds
  @Resolution: 1
  @Range: 0 to 0xFF
  @Applicability: YES
  @Note: This value has to be divisible by Main Function's Periodicity
  Example: Mainfunction Periodicity -> y = 1ms
           P2 Timer Value -> x = 50ms
           Then, UDS_P2_TIMER_MAXCNT = (x / y) = 50/1 = 50 TO BE CONFIGURED IN BELOW MACRO.
*/
#define UDS_P2_TIMER_MAXCNT                     5000u

/*
* @brief: This macro is used to configure the S3 timer maximum count to be maintained in milliseconds
  @Unit:  milliseconds
  @Resolution: 1
  @Range: 0 to 0xFF
  @Applicability: YES
  @Note: This value has to be divisible by Main Function's Periodicity
  Example: Mainfunction Periodicity -> y = 1ms
           S3 Timer Value -> x = 5000ms
           Then, UDS_S3_TIMER_MAXCNT = (x / y) = 5000/1 = 5000 TO BE CONFIGURED IN BELOW MACRO.
*/
#define UDS_S3_TIMER_MAXCNT                     4000u

/*
* @brief: This macro is used to configure the P4 timer maximum count to be maintained in milliseconds
  @Unit:  milliseconds
  @Resolution: 1
  @Range: 0 to 0xFF
  @Applicability: YES
  @Note: This value has to be divisible by Main Function's Periodicity
  Example: Mainfunction Periodicity -> y = 1ms
           P4 Timer Value -> x = 50ms
           Then, UDS_P4_TIMER_MAXCNT = (x / y) = 50/1 = 50 TO BE CONFIGURED IN BELOW MACRO.
*/
#define UDS_P4_TIMER_MAXCNT                     50u

/*
* @brief: This macro is used to configure the RCRRP timer maximum count to be maintained in milliseconds
  @Unit:  milliseconds
  @Resolution: 1
  @Range: 0 to 0xFFFF
  @Applicability: YES
  @Note: This value has to be divisible by Main Function's Periodicity
  Example: Mainfunction Periodicity -> y = 1ms
           P2* Timer Value -> x = 5000ms
           Then, UDS_P2STAR_TIMER_MAXCNT = (x / y) = 5000/1 = 5000 TO BE CONFIGURED IN BELOW MACRO.
*/
#define UDS_P2STAR_TIMER_MAXCNT                  5000u

/*
* @brief: This macro is used to configure the size of the Physical Request Data Buffer
  @Unit:  N/A
  @Resolution: 1
  @Range: 0 to 0xFFF
  @Applicability: YES
*/
#define UDS_PRIMARYBUFF_LENGTHMAX           4095u

/*
* @brief: This macro is used to configure the size of the Functional Request Data Buffer
  @Unit:  N/A
  @Resolution: 1
  @Range: 0 to 0xFF
  @Applicability: YES
*/
#define UDS_SECONDARYBUFF_LENGTHMAX         20u

/*
* @brief: This macro is used to configure the MAXIMUM Delay Timer Maximum count
  @Unit:  milliseconds
  @Resolution: 1
  @Range: 0 to 0xFFFF
  @Applicability: YES
  @Note: This value has to be divisible by Main Function's Periodicity
  Example: Mainfunction Periodicity -> y = 1ms
           Delay Timer Value -> x = 2000ms
           Then, UDS_DELAY_TIMER_MAXCNT = (x / y) = 2000/1 = 2000 TO BE CONFIGURED IN BELOW MACRO.
*/
#define UDS_DELAY_TIMER_MAXCNT                 2000u

/*
* @brief: This macro is used to configure the CAN API to tx the response from server to client
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define UDS_TX_RESPONSE(X , Y)                CanMgr_CanTp_Transmit(0, X , Y)

/*
* @brief: This macro is used to configure the P2 timeout consequential actions as per the manufacturer
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define UDS_P2_TIMEOUT_ACTION_USER()          

/*
* @brief: This macro is used to configure the P2* timeout consequential actions as per the manufacturer
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define UDS_P2STAR_TIMEOUT_ACTION_USER()      

/*
* @brief: This macro is used to configure the S3 timeout consequential actions as per the manufacturer
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define UDS_S3_TIMEOUT_ACTION_USER()    		0//Oem_DwldMgr_PerformSystemReset()

/*
* @brief: This macro is used to configure the P4 timeout consequential actions as per the manufacturer
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define UDS_P4_TIMEOUT_ACTION_USER()          

/*
* @brief: This macro is used to configure the number of RCRRPs that could be sent maximum for a request
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define UDS_RCRRP_MAX_COUNT           (uint8_t)100

/*
* @brief: This macro is used to configure the total number of services supported by the Server to executee the 
          Cfg table g_UDS_ServiceInfoTable_st in UDS_Cfg.c file.
  @param: None
  @Unit:  N/A
  @Resolution: 1
  @Range: 1 - 26(Based on number of services enabled)
  @Applicability: YES
*/
#define MAX_NO_OF_SRV                    18U

/***********************************************************************************************************************
*                                OPTIONAL FEATURE ENABLING CONDITIONAL COMPILATION
***********************************************************************************************************************/

/*
* @brief: This macro is used to enable the Bootloader related implementation
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: STD_OFF(Disable) / STD_ON(Enable)
  @Applicability: To be in Enabled state only if UDS layer is used in Bootloader
*/
#define UDS_BOOTLOADER_MODE_ENABLED           STD_OFF

/*
 * @brief: The following macros describes whether the following service is
 *         required or not required.
 *         STD_ON : The service shall be enabled
 *         STD_OFF: The service shall be disabled
 * @Unit:  N/A
 * @Resolution: N/A
 * */
#define UDS_DIAG_SESS_CTRL_SID_0x10_FEATURE       STD_ON
#define UDS_ECU_RESET_SID_0x11_FEATURE            STD_ON
#define UDS_CLEAR_DTC_SID_0x14_FEATURE            STD_OFF
#define UDS_READ_DTC_SID_0x19_FEATURE             STD_OFF
#define UDS_READ_DID_SID_0x22_FEATURE             STD_ON
#define UDS_READ_MEM_BY_ADDRSS_SID_0x23_FEATURE   STD_ON
#define UDS_SECURITY_ACCESS_SID_0x27_FEATURE      STD_ON
#define UDS_WRITE_DID_SID_0x2E_FEATURE            STD_ON
#define UDS_IO_CTRL_BY_ID_SID_0x2F_FEATURE        STD_ON
#define UDS_ROUTINE_CTRL_SID_0x31_FEATURE         STD_ON
#define UDS_DWNLD_REQ_SID_0x34_FEATURE            STD_ON
#define UDS_UPLD_REQ_SID_0x35_FEATURE             STD_OFF
#define UDS_TRNSFR_DATA_SID_0x36_FEATURE          STD_ON
#define UDS_TRNSFR_EXIT_SID_0x37_FEATURE          STD_ON
#define UDS_TRNSFR_FILE_SID_0x38_FEATURE          STD_ON
#define UDS_WRITE_MEM_BY_ADDRSS_SID_0x3D_FEATURE  STD_ON
#define UDS_TESTER_PRESENT_SID_0x3E_FEATURE       STD_ON
#define UDS_SECURED_DATA_TRNSMSN_SID_0x84_FEATURE STD_ON
#define UDS_CONTROL_DTC_SID_0x85_FEATURE          STD_OFF
#define UDS_RSP_ON_EVNT_SID_0x86_FEATURE          STD_ON
#define UDS_COMMUNICATION_CTRL_SID_0x28_FEATURE   STD_ON

/***********************************************************************************************************************
*                                    CONFIGURATION CONSTANTS                      
***********************************************************************************************************************/
/*
* @brief: This variable is used to maintain the Service Information Table configured
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
extern const UDS_ServiceInfo_st g_UDS_ServiceInfoTable_st[MAX_NO_OF_SRV] ;

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* ! UDS_CFG_H */

