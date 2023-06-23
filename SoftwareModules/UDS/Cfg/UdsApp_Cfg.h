/* @file UDSAPP_CFG_H */
#ifndef UDSAPP_CFG_H
#define UDSAPP_CFG_H

/***********************************************************************************************************************
*   DISCLAIMER
*   Copyright © 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : UdsApp_Cfg.h
*  Generation Time                 : 18-10-2022 16:41:17
*  Tool Version                    : UDS_Configurator  2.2.1.0
*  Description                     : This file contains the configuration elements of UDS Application Layer
*  @bug                            : N/A                       
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

#include "string.h"
#include "Uds_Types.h"
#include "UDS_Cfg.h"
#include "Swc_NVM_Handler.h"
#include "UDS.h"
#if(UDS_BOOTLOADER_MODE_ENABLED != STD_ON)
/*Inclusion of Nvm Manager Header file*/
#endif
/***********************************************************************************************************************
*                                CONFIGURATION MACRO VALUES
***********************************************************************************************************************/

#define UDS_VEHICLE_SPEED()                 Get_display_Speed()



/******************************** DIAGNOSTIC SESSION CONTROL - 0x10 ***************************************************/
#if(UDS_DIAG_SESS_CTRL_SID_0x10_FEATURE == STD_ON)
/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in Diagnostic Session Control[0x10] Service's Subfunction - Default [0x01]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x10 (Diagnostic Session Control)
*/
#define UDSAPP_DEFAULT_SESS_CNC_CHECK_SID_10_SF_01                              0

/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in Diagnostic Session Control[0x10] Service's Subfunction - Programming [0x02]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x10 (Diagnostic Session Control)
*/
#define UDSAPP_PROG_SESS_CNC_CHECK_SID_10_SF_02                                 0

/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in Diagnostic Session Control[0x10] Service's Subfunction - Extended [0x03]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x10 (Diagnostic Session Control)
*/
#define UDSAPP_EXTENDED_SESS_CNC_CHECK_SID_10_SF_03                             0

/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in Diagnostic Session Control[0x10] Service's Subfunction - Safety Session [0x04]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x10 (Diagnostic Session Control)
*/
#define UDSAPP_SAFETY_SESS_CTRL_CNC_CHECK_SID_10_SF_04                          0

#define UDSAPP_VISTEON_SESS_CTRL_CNC_CHECK_SID_10_SF_60                          0
#endif
/********************************************************************************************************************/

/*********************************************** ECU RESET - 0x11 ***************************************************/
#if(UDS_ECU_RESET_SID_0x11_FEATURE == STD_ON)
/*
* @brief: This macro is used to enable the Client ID verification feature
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: STD_OFF(Disable) / STD_ON(Enable)
  @Applicability: To be in Enabled state only if SecurityAccess (0x27) service has the client ID verification feature
*/
#define SECURITY_ACCESS_DATA_RECORD_VERIFICATION     STD_OFF

/*
* @brief: This macro is used to enable the Security Access feature for ECU Reset service (0x11)
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: STD_OFF(Disable) / STD_ON(Enable)
  @Applicability: To be in Enabled state only if ECU Reset (0x11) service requires Secured access feature
*/
#define SECURITY_ACCESS_FEATURE_SID_0x11           STD_ON

/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in ECU Reset[0x11] Service's Subfunction - Hard Reset [0x01]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x11 (ECU Reset)
*/
#define UDSAPP_HARD_ECU_RESET_CNC_CHECK_SID_11_SF_01          0

/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in ECU Reset[0x11] Service's Subfunction - Key off Reset [0x02]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x11 (ECU Reset)
*/
#define UDSAPP_KEYOFF_ECU_RESET_CNC_CHECK_SID_11_SF_02                          0

/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in ECU Reset[0x11] Service's Subfunction - Soft Reset [0x03]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x11 (ECU Reset)
*/
#define UDSAPP_SOFT_ECU_RESET_CNC_CHECK_SID_11_SF_03                            0

/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in ECU Reset[0x11] Service's Subfunction - Enable Rapid Power ShutDown[0x04]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x11 (ECU Reset)
*/
#define UDSAPP_ENBLE_RAPID_PWR_SHUTDWN_CNC_CHECK_SID_11_SF_04                   0

/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in ECU Reset[0x11] Service's Subfunction - Disable Rapid Power ShutDown[0x05]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x11 (ECU Reset)
*/
#define UDSAPP_DISABLE_RAPID_PWR_SHUTDWN_CNC_CHECK_SID_11_SF_05                 0

/*
* @brief: This macro is used to configure the PowerDownTime
  @Unit:  seconds
  @Resolution: 1
  @Range: 0 to 254
  @Applicability: Service ID - 0x11 (ECU Reset)
*/
#define ECU_RST_POWERDOWNTIME                0x00U
#endif
/************************************************************************************************************************/

/*************************************** CLEAR DIAGNOSTIC INFO - 0x14 ***************************************************/
#if(UDS_CLEAR_DTC_SID_0x14_FEATURE == STD_ON)
/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in Clear Diagnostic Information Service[0x14]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x14 (Clear Diagnostics Info)
*/
#define UDSAPP_CLEAR_DIAG_INFO_CNC_CHECK_SID_14                 0

/*
* @brief: This macro is used to configure the DTC group to be cleared by the user
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: Service ID - 0x14 (Clear Diagnostics Info)
*/
#define UDSAPP_CLEAR_DTC_GROUP 0x00010101u
#endif
/************************************************************************************************************************/

/**************************************** READ DATA BY IDENTIFIER - 0x22 *************************************************/
#if(UDS_READ_DID_SID_0x22_FEATURE == STD_ON)
/*
* @brief          : This macros defines the Read data API for Service 0x22 to be configured
* @unit           : N/A
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : Service ID - 0x22 (Read DID)
*/
#define UDSAPP_READ_DID_SUPPORT(a,b,c)      UdsApp_Support_Read_Data(a, b, c)

/*
* @brief: This macro is used to enable the Security Access feature for Read Data by Identifier service (0x22)
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: STD_OFF(Disable) / STD_ON(Enable)
  @Applicability: To be in Enabled state only if Read Data by Identifier (0x22) service requires Secured access feature
*/
#define SECURITY_ACCESS_FEATURE_SID_0x22           STD_ON

/*
* @brief: This macro is used to configure the Total number of DID services supported
  @Unit:  N/A
  @Resolution: 1
  @Range: 0 to 254
  @Applicability: Service ID - 0x22 (Read DID)
*/
#define TOTAL_READ_DID_SUPPORTED                16u
#endif
/************************************************************************************************************************/

/**************************************** READ MEMORY BY ADDRESS - 0x23 ***********************************************/
#if(UDS_READ_MEM_BY_ADDRSS_SID_0x23_FEATURE == STD_ON)
/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in Read  Memory By Identifier Service[0x23]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x23 (Read Memory By Address)
*/
#define UDSAPP_READ_MEM_BY_ADDRESS_CNC_CHECK_SID_23                0

/*
* @brief          : This macros defines the Read data API for Service 0x23 to be configured
* @unit           : N/A
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : Service ID - 0x23 (Read Memory By Address)
*/
#define UDSAPP_READ_MEM_SUPPORT(a, b, c)                    UDSAPP_READ_BY_ADDRESS(a, b, c)

/*
* @brief: This macro is used to configure the start address of Micro's memory which is used in Read Data by Memory Service (0x23, 0x3D)
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: Micro-Specific
  @Applicability: Service ID - 0x23  (ReadMemoryByAddress) & Service ID - 0x3D  (WriteMemoryByAddress)
*/
#define USER_MICRO_START_ADDRESS    0x20000000

#define USER_NOR_MICRO_START_ADDRESS    0x30000000

/*
* @brief: This macro is used to configure the end address of Micro's memory which is used in Read Data by Memory Service (0x23, 0x3D)
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: Micro-Specific
  @Applicability: Service ID - 0x23  (ReadMemoryByAddress) & Service ID - 0x3D  (WriteMemoryByAddress)
*/
#define USER_MICRO_END_ADDRESS      0x20040000

#define USER_NOR_MICRO_END_ADDRESS      0x32000000

/*
* @brief: This macro is used to configure the size of Micro's memory which is used in Read Data by Memory Service (0x23, 0x3D)
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: Micro-Specific
  @Applicability: Service ID - 0x23  (ReadMemoryByAddress) & Service ID - 0x3D  (WriteMemoryByAddress)
*/
#define USER_MICRO_MEMORY_SIZE      0x40000

#define USER_NOR_MICRO_MEMORY_SIZE      0x200000
#endif
/************************************************************************************************************************/

/*************************************************** SECURITY ACCESS - 0x27 *********************************************/
#if(UDS_SECURITY_ACCESS_SID_0x27_FEATURE == STD_ON)
/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in Security Access[0x27] Service's - Subfunction SeedReq [0x01]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x27 (Security Access)
*/
#define UDSAPP_SEEDREQ_CNC_CHECK_SID_27_SF_01                   0 

/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in Security Access[0x27] Service's - Subfunction SeedReq [0x01]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x27 (Security Access)
*/
#define UDSAPP_SENDKEY_CNC_CHECK_SID_27_SF_02                   0

/*
* @brief: This macro is used to configure the Total number of Invalid Key Attampts for Security Access
  @Unit:  N/A
  @Resolution: 1
  @Range: 0 to 254
  @Applicability: Service ID - 0x27 (Security Access)
  */
#define INVALID_KEY_MAXIMUM_ATTEMPTS                            2u
#endif
/************************************************************************************************************************/

/******************************************* WRITE DATA BY IDENTIFIER - 0x2E ********************************************/
#if(UDS_WRITE_DID_SID_0x2E_FEATURE == STD_ON)
/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in Write Data By Identifier Service[0x2E]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x2E (Write DID)
*/
#define UDSAPP_WRITE_DID_CNC_CHECK_SID_2E()                      UDS_VEHICLE_SPEED()

/*
* @brief          : This macros defines the Read data API for Service 0x22 to be configured
* @unit           : N/A
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : Service ID - 0x2E (Write DID)
*/
#define UDSAPP_WRITE_DID_SUPPORT(a,b,c)      UdsApp_Support_Write_Data(a, b, c)

/*
* @brief: This macro is used to configure the Total number of DID services supported
  @Unit:  N/A
  @Resolution: 1
  @Range: 0 to 254
  @Applicability: Service ID - 0x2E (Write DID)
*/
#define TOTAL_WRITE_DID_SUPPORTED                11u
#endif
/************************************************************************************************************************/

/****************************************** INPUT/OUTPUT CONTROL BY IDENTIFIER - 0x2F ***********************************/
#if(UDS_IO_CTRL_BY_ID_SID_0x2F_FEATURE == STD_ON)
/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in I/O Control By Identifer Service[0x2F]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x2F (Input Output Control By Identifier)
*/
#define UDSAPP_IO_CONTROLBYID_CNC_CHECK_SID_2F                    0

/*
* @brief          : This macros defines the return to ECU API to be configured for 0x2F service Subfunction 0x00
* @unit           : N/A
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : Service ID - 0x2F (Input Output Control By Identifier)
*/
#define APP_RETURN_TO_ECU_IOCTRL(a)                                          NULL

/*
* @brief          : This macros defines the reset to default API to be configured for 0x2F service Subfunction 0x01
* @unit           : N/A
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : Service ID - 0x2F (Input Output Control By Identifier)
*/
#define APP_RESET_TO_DEFAULT_IOCTRL(a)                                       NULL

/*
* @brief          : This macros defines the freeze current state API to be configured for 0x2F service Subfunction 0x02
* @unit           : N/A
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : Service ID - 0x2F (Input Output Control By Identifier)
*/
#define APP_FREEZE_CURRENT_STATE_IOCTRL(a)                                 NULL

/*
* @brief          : This macros defines the return to ECU API to be configured for 0x2F service Subfunction 0x03
* @unit           : N/A
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : Service ID - 0x2F (Input Output Control By Identifier)
*/
#define APP_SHORT_ADJUSMNT_IOCTRL(a,b)                 UDS_IO_DID_SHORTTERM_ADJUSTMENT(a,b)

#define  TOTAL_IO_DID_SUPPORTED          3                        
#endif
/************************************************************************************************************************/

/********************************************* ROUTINE CONTROL - 0x31 ***************************************************/
#if(UDS_ROUTINE_CTRL_SID_0x31_FEATURE == STD_ON)
/*
* @brief: This macro is used to enable the Routine Restart feature
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: STD_OFF(Disable) / STD_ON(Enable)
  @Applicability: To be in Enabled state only if RoutineControl (0x31) service supports Routine RESTART feature
*/
#define ROUTINE_RESTART_FEATURE                      STD_OFF

/*
* @brief: This macro is used to enable the Routine Control Option Record feature
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: STD_OFF(Disable) / STD_ON(Enable)
  @Applicability: To be in Enabled state only if RoutineControl (0x31) service supports Routine RESTART feature
*/
#define ROUTINE_CTRL_OPTION_RECORD_FEATURE           STD_ON

/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in Routine Control[0x31] Service's subfunction - StartRoutine [0x01]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x31 (Routine Control)
*/
#define UDSAPP_STARTROUTINE_CNC_CHECK_SID_31_SF_01              0

/*
* @brief: This macro is used to enable or disable async response for SID 31
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x31 (Routine Control)
*/
#define UDSAPP_ROUTINE_CTRL_ASYNC_RESPONSE_SID_31               STD_ON
/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in Routine Control[0x31] Service's subfunction - StopRoutine [0x02]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x31 (Routine Control)
*/
#define UDSAPP_STOPROUTINE_CNC_CHECK_SID_31_SF_02                0

/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in Routine Control[0x31] Service's subfunction - GetRoutineResults [0x03]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x31 (Routine Control)
*/
#define UDSAPP_GETROUTINERESULT_CNC_CHECK_SID_31_SF_03           0

/*
* @brief: This macro is to mention application that erase request (RID 0xff00) has been received
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: Service ID - 0x31 (Routine Control)
*/
#define UDS_APP_OEM_ERASE_REQUEST(x,y)                          0

/*
* @brief: This macro is used to configure the Total number of routines supported
  @Unit:  N/A
  @Resolution: 1
  @Range: 0 to 254
  @Applicability: Service ID - 0x31 (Routine Control)
*/
#define MAX_NO_OF_ROUTINE                         4u
#endif
/************************************************************************************************************************/

/********************************************** REQUEST DOWNLOAD - 0x34 *************************************************/
#if(UDS_DWNLD_REQ_SID_0x34_FEATURE == STD_ON)
/*
* @brief: This macro is to mention application that request download service has been received
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: Service ID - 0x34 (Download Request)
*/
#define APP_REQUEST_DOWNLOAD_CBK(x, y, z)                                  //Oem_DwldMgr_Download_Request()
#endif
/************************************************************************************************************************/

/************************************************* REQUEST UPLOAD - 0x34 ************************************************/
#if(UDS_UPLD_REQ_SID_0x35_FEATURE == STD_ON)
/*
* @brief: This macro is to indicate application that upload request has been received
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: Service ID - 0x35 (Upload Request)
*/
#define APP_REQUEST_UPLOAD_CBK(x, y, z)
#endif
/***********************************************************************************************************************/

/************************************************** TRANSFER DATA - 0x36 ***********************************************/
#if(UDS_TRNSFR_DATA_SID_0x36_FEATURE == STD_ON)
/*
* @brief: This macro is to mention application that request download service has been received
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: Service ID - 0x36 (UdsApp_TransferData)
*/
#define APP_TRANSFER_DATA_CBK(x, y,z)                           //Oem_DwldMgr_Transfer_data_Request()

/*
* @brief: This macro is used to get voltage status from application
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: Service ID - 0x36 (UdsApp_TransferData)
*/
#define UDSAPP_GET_VOLTAGE_STATUS()                             UDS_VOLTAGE_STATUS()

/*
* @brief: This macro is used to specify low voltage status
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: Service ID - 0x36 (UdsApp_TransferData)
*/
#define LOW_VOLTAGE                           1u

/*
* @brief:  This macro is used to specify high voltage status
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: Service ID - 0x36 (UdsApp_TransferData)
*/
#define HIGH_VOLTAGE                          2u

/*
* @brief: This macro is to mention normal voltage status
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: Service ID - 0x36 (UdsApp_TransferData)
*/
#define NORMAL_VOLTAGE                        3u
#endif
/************************************************************************************************************************/

/**************************************************** TRANSFER EXIT - 0x37 **********************************************/
#if(UDS_TRNSFR_EXIT_SID_0x37_FEATURE == STD_ON)
/*
* @brief: This macro is used indicate application that transfer exit service has been received
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: Service ID - 0x37 (TransferExit)
*/
#define APP_TRANSFER_EXIT_CBK(x)                        //Oem_DwldMgr_Transfer_Exit_Process()

/*
* @brief: This macro is used to mention the min dlc in service (0x37)
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: Service ID - 0x37 (TransferExit)
*/
#define TRANSFER_EXIT_MIN_DLC                 0
#endif
/************************************************************************************************************************/

/*************************************************** WRITE MEMORY BY ADDRESS - 0x3D ************************************/
#if(UDS_WRITE_MEM_BY_ADDRSS_SID_0x3D_FEATURE == STD_ON)
/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in Write Memory By Identifier Service[0x3D]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x3D (Write Memory By Address)
*/
#define UDSAPP_WRITE_MEM_BY_ADDRESS_CNC_CHECK_SID_3D                0

/*
* @brief          : This macros defines the Write memory API for Service 0x3D to be configured
* @unit           : N/A
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : Service ID - 0x3D (Write Memory By Address)
*/
#define UDSAPP_WRITE_MEM_SUPPORT(a, b, c)             UDSAPP_WRITE_BY_ADDRESS(a,b,c)

//#define UDSAPP_FLASH_MEM_SUPPORT(a, b, c)             UDSAPP_FLASH_WRITE_BY_ADDRESS(a,b,c)
#endif
/************************************************************************************************************************/

/************************************************** SECURED DATA TRANSMISSION - 0x84 ************************************/
#if(UDS_SECURED_DATA_TRNSMSN_SID_0x84_FEATURE == STD_ON)
/*
* @brief: This macro is used to configure the number of bytes the securityDataResponseRecord to calculate the
          response buffer length accordingly by the UdsApp layer for 0x84 service.
  @Unit:  N/A
  @Resolution: 1
  @Range: 0 to 254
  @Applicability: Service ID - 0x84 (Secured Data Transmission)
*/
#define MAX_DATA_RESP_RECORD_LENGTH_IN_BYTES                             0u

/*
* @brief: This macro is used to configure the length of array holding response data of the securityDataResponseRecord
          response buffer length accordingly by the UdsApp layer for 0x84 service.
  @Unit:  N/A
  @Resolution: 1
  @Range: 0 to 254
  @Applicability: Service ID - 0x84 (Secured Data Transmission)
*/
#define MAX_BUFFER_LENGTH_IN_BYTES_SID_0X86                             1u
#endif
/************************************************************************************************************************/

/*************************************************** CONTROL DTC SETTING - 0x85 *****************************************/
#if(UDS_CONTROL_DTC_SID_0x85_FEATURE == STD_ON)
/*
* @brief: This macro is used to configure the appropriate flag variable to be checked for NRC 0x22
          in Control DTC Setting Service[0x85]
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: Service ID - 0x85 (Control DTC)
*/
#define UDSAPP_CONTROL_DTC_CNC_CHECK_SID_85                       Condition_not_correct_Stub()
#endif
/************************************************************************************************************************/
#if(UDS_BOOTLOADER_MODE_ENABLED == STD_OFF)
/*
* @brief          : This macros defines the Read NVM API to be configured
* @unit           : N/A
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : To Read data from Nvm using Sync operation
*/
#define UDSAPP_READ_NVM(x,y)                            NVM_Byte_Read_Allocation(x,y)

/*
* @brief          : This macros defines the Write NVM API to be configured
* @unit           : N/A
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : To Write data to Nvm using Sync operation
*/
#define UDSAPP_WRITE_NVM(x, y)                            NVM_Byte_Write_Allocation(x,y)
#endif

/*
* @brief: This macro is to mention application that request download service has been received
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if async response is being used
*/
#define MAX_NOS_OF_APPLICATION_ERROR_CODE       (UDS_UINT8)5

/*
* @brief: This macro is used to configure the DID response length according to the TP
  @Unit:  N/A
  @Resolution: 1
  @Range: 0 to FFF (TP max)
  @Applicability: YES
*/
#define RESPONSE_LENGTH_MAX        4096u


#define PROGRAMING_DATE_DID                                        (UDS_UINT16)0xF199
#define FINGERPRINT_DATA_DID                                       (UDS_UINT16)0xF183
#define BOOTLOADER_VERSION_DID                                     (UDS_UINT16)0xF180
#define PROGRAMMING_ATTEMPT_COUNTER_DID                            (UDS_UINT16)0xFDA0
#define PROGRAMMING_SUCCESS_COUNTER_DID                            (UDS_UINT16)0xFDA1



/*ROM shared Data*/
#define BMS_SW_PART_NUMBER   (UDS_UINT16)0xF181
#define DCDC_SW_PART_NUMBER  (UDS_UINT16)0xF182




/***********************************************************************************************************************
*                                    CONFIGURATION VARIABLES                      
***********************************************************************************************************************/
#if(UDS_ROUTINE_CTRL_SID_0x31_FEATURE == STD_ON)
/********************************************* ROUTINE CONTROL - 0x31 ***************************************************/
/* 
 * @brief This variable is used to configure the Start Routine Function Handler
 * @param    Routine Identifier RID
 * @return   Routine execution status (UDS_TRUE - successful, UDS_FALSE - unsuccessful)
 * @applicability: Service ID - 0x31 (Routine Control)  
   eg: StartStopRoutineHandler_type Application_StartRoutine_Handler = Start_RoutineHandler();*
**/
extern StartStopRoutineHandler_type Application_StartRoutine_Handler;

/* 
 * @brief This variable is used to configure the Start Routine Function Handler 
 * @param    Routine Identifier RID
 * @return   Routine execution status (UDS_TRUE - successful, UDS_FALSE - unsuccessful)
 * @applicability: Service ID - 0x31 (Routine Control)  
   eg: StartStopRoutineHandler_type Application_StopRoutine_Handler = Stop_RoutineHandler(); 
**/
extern StartStopRoutineHandler_type Application_StopRoutine_Handler;

/* 
 * @brief This variable is used to configure the Start Routine Function Handler
 * @param    RID - Routine Identifier
 * @param    RespDataBuff - Pointer to update the response buffer with routine results
 * @param    DataLen - Pointer to update the length  of the buffer after updating with Routine results
 * @return   Routine execution status (UDS_TRUE - successful, UDS_FALSE - unsuccessful)
 * @applicability: Service ID - 0x31 (Routine Control)  
   eg: GetResultRoutineHandler_type Application_GetResultRoutine_Handler = GetResult_RoutineHandler(); 
**/
extern GetResultRoutineHandler_type Application_GetResultRoutine_Handler;

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/
/*
* @brief    This API is used to configure the Application check routine control option  record
* @param    pdiagdata - Diagnostic request frame received from the client
* @param    datalength - Data length of the Routine Control record
* @return   EcuReset Condition Status
* @applicability: Service ID - 0x31 (Routine Control)
**/
UDS_UINT8 Application_Check_Routine_Ctrl_Option_Record_Match(const UDS_UINT8 *pdiagdata, UDS_UINT16 RID, UDS_UINT8 datalength);
#endif
/*****************************************************************************************************************************/

/**************************************************** ECU RESET - 0x11 *******************************************************/
#if(UDS_ECU_RESET_SID_0x11_FEATURE == STD_ON)
/*
* @brief    This API is used to configure the Hard ECU reset
* @param    None
* @return   EcuReset Condition Status
* @applicability: Service ID - 0x11 (ECU reset)
**/
void Application_HardECU_Reset(void);

/*
* @brief    This service is used to configure the ECU Soft reset
* @param    None
* @return   None
* @applicability: Service ID - 0x11 (ECU reset)
**/
void Application_SoftECU_Reset(void);

/*
* @brief    This service is used to configure the KeyOff reset
* @param    None
* @return   None
* @applicability: Service ID - 0x11 (ECU reset)
**/
void Application_KeyOffECU_Reset(void);

/*
* @brief    This service is used to configure the ECU reset
* @param    None
* @return   None
* @applicability: Service ID - 0x11 (ECU reset)
**/
void Application_Enable_RapidPwr_ShutDwn_ECU_Reset(void);

/*
* @brief    This service is used to configure the ECU reset
* @param    None
* @return   None
* @applicability: Service ID - 0x11 (ECU reset)
**/
void Application_Disable_RapidPwr_ShutDwn_ECU_Reset(void);
#endif
/***********************************************************************************************************************/

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* ! UDSAPP_CFG_H */
