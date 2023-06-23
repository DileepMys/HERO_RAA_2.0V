/* @file UDSAPP_C */
#ifndef UDSAPP_C
#define UDSAPP_C
/*********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2011, 2016 Niyata Infotech Ptv. Ltd. All rights reserved.                                           
*********************************************************************************************************************/

/*********************************************************************************************************************
* @author              Author : Sharmili N (sharmili@niyatainfotech.com)
*********************************************************************************************************************/

/*********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                       
**--------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : UdsApp.c
*  Version                         : V1.3.2
*  Micros supported                : xxxx 
*  Compilers supported             : xxxx 
*  Platforms supported             : xxxx
*  Description                     : This file contains the APIs of diagnostic application layer
*  @bug                         
--------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/********************************************************************************************************************/

/*********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                             
*********************************************************************************************************************/
#include "UdsApp.h"
#include "UDS_Cfg.h"
#include "UdsApp_SecAcc.h"
#include "UdsApp_Cfg.h"
#include "UdsApp_Support.h"
#include "Uds_Types.h"
#include "Swc_Speedometer.h"
#include "Cmp_Init.h"
#if((UDS_CLEAR_DTC_SID_0x14_FEATURE == STD_ON) || (UDS_READ_DTC_SID_0x19_FEATURE == STD_ON) || (UDS_CONTROL_DTC_SID_0x85_FEATURE == STD_ON))
#include "Uds_Dtc.h"
#include "Uds_DtcApp.h"
#endif

/*********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                               
*********************************************************************************************************************/
/*********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                   
*********************************************************************************************************************/

/*********************************************************************************************************************
*                                          M A C R O   D E F I N I T I O N S                                          
*********************************************************************************************************************/
/*
* @brief: This macro is used to define request download state as inactive
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define REQUEST_DOWNLOAD_INACTIVE           (UDS_UINT8)0

/*
* @brief: This macro is used to define request download state as active
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define REQUEST_DOWNLOAD_ACTIVE             (UDS_UINT8)1



/*
* @brief: This macro is used to define request upload state as inactive
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define REQUEST_UPLOAD_INACTIVE           (UDS_UINT8)0

/*
* @brief: This macro is used to define request download state as active
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define REQUEST_UPLOAD_ACTIVE             (UDS_UINT8)1

/*
* @brief: This macro is used to define Transfer Exit state
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define TRANSFER_EXIT_STATE                 (UDS_UINT8)2
/*********************************************************************************************************************
*                                          P R I V A T E   D E C L A R A T I O N S                                    
*********************************************************************************************************************/
/*
* @brief: This variable is used to hold the current session value
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 to 4
  @Applicability: YES
*/
static UDS_UINT8 l_current_session_u8;

/*
* @brief: This variable is used to define the ECU reset status flag
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: YES
*/
static UDS_UINT8 l_reset_pending_u8;

/*
* @brief: This variable is used to define the power shut down status flag
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: YES
*/
static UDS_UINT8 l_power_shutdown_enable_u8;

/*
* @brief: This variable is used to define the power shut down status flag
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: YES
*/
static UDS_UINT8 l_power_shutdown_disable_u8;

/*
* @brief: This variable is used to define the security access status
  @Unit:  N/A
  @Resolution: N/A
  @Range: 1 or 0
  @Applicability: YES
*/
static UDS_UINT8 l_security_access_status_u8;

/*
* @brief: This variable is used to define the seed request sequence flag
  @Unit:  N/A
  @Resolution: N/A
  @Range: 0 to 1
  @Applicability: YES
*/
static UDS_UINT8 l_SeedRequest_Sequence_Flag_u8;

/*
* @brief: This variable is used to maintain the invalid key attempt counts
  @Unit:  N/A
  @Resolution: N/A
  @Range: 0 to FFFF
  @Applicability: YES
*/
static UDS_UINT8 l_InvalidKey_Attempt_Counter_u8;

/*
* @brief: This variable is used to maintain the ECU reset sub-function
  @Unit:  N/A
  @Resolution: N/A
  @Range: 0 to FFFF
  @Applicability: YES
*/
static UDS_UINT8 l_ECUReset_Subfunction_u8;

/**
 * @brief    This structure is used to maintain data related to 0x34 , 0x36 & 0x37 services
 * @param    Download_address - Memory address where the data has to be flashed
 * @param    Download_length  - To length of data that has to be downloaded
 * @param    Downloaded_length  - Total length that has been downloaded
 * @param    blocksequence_counter  - Used to hold block sequence number from 0x36 service
 * @param    Download_state  - Used to mention the state of download request
 **/
typedef struct
{
    UDS_UINT32 Download_address;
    UDS_UINT32 Download_length;
    UDS_UINT32 Downloaded_length;
    UDS_UINT8 blocksequence_counter;
    UDS_UINT8 Download_state;
    UDS_UINT8 Upload_state;
}RequestDownload_Upload_t;

/*
* @brief: This structure is used to maintain data related to 0x34 , 0x36 & 0x37 services
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
static RequestDownload_Upload_t l_RequestDownload;

extern uint32_t g_ECUGeneratedKey_u8 ;

bool g_UDS_pre_condition_status;
UDS_UINT8 FLASH_DATA[4] = {0xAB, 0xCD, 0xEF, 0x01};

/**********************************************************************************************************************
                                P R I V A T E    F U N C T I O N S    D E C L A R A T I O N                        
**********************************************************************************************************************/
/*
* @brief    This function is used to initialize global variable related to
*           RequestDownload service            
* @param    None 
* @return   None
*/
void UdsApp_DownloadRequestInit(void);

/*
* @brief    This function is used to get NRC for the application error code
* @param    App_Error_Code
* @return   NRC
*/
UDS_UINT8 UdsAppGetNRC(UDS_UINT8 App_Error_Code);

/*********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N S                     
*********************************************************************************************************************/

uint8_t GetCurrentSession(void)
{
    return l_current_session_u8;
}

/*
* @brief    This function is used to initialize the UDS application layer
* @param    None 
* @return   None
*/
void UdsApp_Init(void)
{
    /*initialize the current session as defualt session*/
    l_current_session_u8 = UDS_DEFAULT_SESS;

    /*clear reset pending flag*/
    l_reset_pending_u8 = UDS_FALSE;

    /*clear power shut down flag */
    l_power_shutdown_enable_u8 = UDS_FALSE;
    l_power_shutdown_disable_u8 = UDS_FALSE;

    /*set security status as locked state*/
    l_security_access_status_u8 = UDS_SECURITY_LOCKED_STATE;
}

#if(UDS_DIAG_SESS_CTRL_SID_0x10_FEATURE == STD_ON)
/*
* @brief    This service is used to starts the requested diagnostic session as per the sub function (0x10)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/


void UdsApp_DiagnosticSessionControl(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    uint32_t ControlRegister = 0;
    UDS_UINT8 fl_session_u8 = UDS_DEFAULT_SESSION;
    UDS_UINT8 fl_status_u8;
    static UDS_UINT8 fl_response_buffer_u8[BUFF_INDEX_SEVEN];
    UDS_UINT8 fl_CurrentRequestType_u8;
    UDS_UINT8 fl_ReqSession_u8;
            
    /*check valid length of diagnostice request*/
    if(fl_datalength_u16 == (UDS_UINT16)UDS_DIAGNOSTIC_SESSION_CONTROL_REQUEST_LENGTH)
    {
        /* removing the supressed positive response bit from the diagnostic session request*/
        fl_session_u8 = (fl_pdiagdata_u8[BUFF_INDEX_ZERO]& UDS_RESPONSE_SUPPRESS_MASK);

        /* CHECK FOR THE VALID SESSION */
        if((fl_pdiagdata_u8[BUFF_INDEX_ZERO] == UDS_DEFAULT_SESSION) || (fl_pdiagdata_u8[BUFF_INDEX_ZERO] == UDS_PROGRAMMING_SESSION) ||
         (fl_pdiagdata_u8[BUFF_INDEX_ZERO] == UDS_EXTENDED_DIAGNOSTIC_SESSION) || (fl_pdiagdata_u8[BUFF_INDEX_ZERO] == UDS_VISTEON_SESSION))
        {
            /* check whether the vehicle speed is zero or not */
            if(UDS_VEHICLE_SPEED() == 0)
            {
                /*Check whether the request is for transition from Default to Non-Default session*/
                // if (l_current_session_u8 == UDS_DEFAULT_SESS)
                // {              
                    /*Requested Session is Default session*/
                    switch(fl_session_u8)
                    {
                        case UDS_DEFAULT_SESSION:
                        {                            
                            if(fl_session_u8 == UDS_DEFAULT_SESSION)
                            {
                                /*Check for incorrect conditions flag status*/
                                if(UDSAPP_DEFAULT_SESS_CNC_CHECK_SID_10_SF_01 == UDS_FALSE)
                                {
                                    /*update current session as default session*/
                                    fl_ReqSession_u8 = UDS_DEFAULT_SESS;
                                    l_current_session_u8 = UDS_DEFAULT_SESS;
                                    UDS_Update_Current_Session(fl_ReqSession_u8);
                                    UdsApp_SecurityLock();
                                    /*set valid request*/
                                    fl_status_u8 = UDS_NO_ERROR;
                                }
                                else
                                {
                                    /* do nothing */
                                }
                            }
                            break;
                        }

                        case UDS_PROGRAMMING_SESSION:
                        {
                            if(l_current_session_u8 == UDS_DEFAULT_SESS || l_current_session_u8 == UDS_EXTND_SESS || l_current_session_u8 == UDS_PROG_SESS)
                            {
                                /*Check whether Positive Response Suppression Bit is Set*/
                                if ((UDS_UINT8)UDS_FALSE != UDS_INSPECT_POS_RSP_SUPPRESSED(fl_pdiagdata_u8))
                                {
                                    /*Restart S3 session timer on switching to a non-default session*/
                                    UDS_StartS3Timer();
                                }
                                    if(fl_session_u8 == UDS_PROGRAMMING_SESSION)
                                    {
                                        /*Check for incorrect conditions flag status*/
                                        if(UDSAPP_PROG_SESS_CNC_CHECK_SID_10_SF_02 == UDS_FALSE)
                                        {
                                            /*update current session as programming session*/
                                            fl_ReqSession_u8 = UDS_PROG_SESS;
                                            l_current_session_u8 = UDS_PROG_SESS;
                                            UDS_Update_Current_Session(fl_ReqSession_u8);
                                            UdsApp_SecurityLock();
                                            NVM_Byte_Write_Allocation(BOOT_FLAG,&FLASH_DATA[0]);
                                            UDS_SendRCRRP();
                                            //Application_SoftECU_Reset();
                                            //AppToBootJmp();
                                            //NVMData_Readsync(30,FLASH_DATA,1);
                                            /*set valid request*/
                                            fl_status_u8 = UDS_NO_ERROR;
                                        }
                                        else
                                        {
                                        /* do nothing */                    
                                        }
                                    }
                            }
                            else
                            {
                                fl_status_u8 = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                            }
                            break;
                        }

                        /*Check Requested Session is Non-Default session*/
                        case UDS_EXTENDED_DIAGNOSTIC_SESSION:
                        {
                            if(l_current_session_u8 == UDS_DEFAULT_SESS || l_current_session_u8 == UDS_EXTND_SESS)
                            {
                                /*Check whether Positive Response Suppression Bit is Set*/
                                if ((UDS_UINT8)UDS_FALSE != UDS_INSPECT_POS_RSP_SUPPRESSED(fl_pdiagdata_u8))
                                {
                                /*Restart S3 session timer on switching to a non-default session*/
                                UDS_StartS3Timer();
                                }
                                if(fl_session_u8 == UDS_EXTENDED_DIAGNOSTIC_SESSION)
                                {
                                    /*Check for incorrect conditions flag status*/
                                    if(UDSAPP_EXTENDED_SESS_CNC_CHECK_SID_10_SF_03 == UDS_FALSE)
                                    {
                                    /*update current session as extended diagnostic session*/
                                    fl_ReqSession_u8 = UDS_EXTND_SESS;
                                    l_current_session_u8 = UDS_EXTND_SESS;
                                    UDS_Update_Current_Session(fl_ReqSession_u8);
                                    UdsApp_SecurityLock();
                                    /*set valid request*/
                                    fl_status_u8 = UDS_NO_ERROR;
                                    }
                                    else
                                    {
                                    /* do nothing */

                                    }
                                }
                            }
                            else
                            {
                                fl_status_u8 = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                            }
                            break;
                        }

                        /*Check Requested Session is Non-Default session*/
                        case UDS_VISTEON_SESSION:
                        {
                            if(l_current_session_u8 == UDS_EXTND_SESS || l_current_session_u8 == UDS_VISTEON_SYS_DIAG_SESS)
                            {
                                /*Check whether Positive Response Suppression Bit is Set*/
                                if ((UDS_UINT8)UDS_FALSE != UDS_INSPECT_POS_RSP_SUPPRESSED(fl_pdiagdata_u8))
                                {
                                    /*Restart S3 session timer on switching to a non-default session*/
                                    UDS_StartS3Timer();
       
                                }
                                if(fl_session_u8 == UDS_VISTEON_SESSION)
                                {
                                    /*Check for incorrect conditions flag status*/
                                    if(UDSAPP_VISTEON_SESS_CTRL_CNC_CHECK_SID_10_SF_60 == UDS_FALSE)
                                    {
                                    /*update current session as safety system diagnostic session*/
                                    fl_ReqSession_u8 = UDS_VISTEON_SYS_DIAG_SESS;
                                    l_current_session_u8 = UDS_VISTEON_SYS_DIAG_SESS;
                                    UDS_Update_Current_Session(fl_ReqSession_u8);
                                    UdsApp_SecurityLock();
                                    /*set valid request*/
                                    fl_status_u8 = UDS_NO_ERROR;
                                    }
                                    else
                                    {
                                    /* do nothing */                    
                                    }
                                }
                            }
                            else
                            {
                                fl_status_u8 = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
                            }
                            break;
                        }

                        default:
                        {
                            /*Do nothing*/
                            break;
                        }
                    }             
                        
                //} 
        
                // if(fl_session_u8 == UDS_DEFAULT_SESSION)
                // {
                //     /*Check for incorrect conditions flag status*/
                //     if(UDSAPP_DEFAULT_SESS_CNC_CHECK_SID_10_SF_01 == UDS_FALSE)
                //     {
                //         /*update current session as default session*/
                //         fl_ReqSession_u8 = UDS_DEFAULT_SESS;
                //         l_current_session_u8 = UDS_DEFAULT_SESS;
                //         UDS_Update_Current_Session(fl_ReqSession_u8);
                //         UdsApp_SecurityLock();
                //         /*set valid request*/
                //         fl_status_u8 = UDS_NO_ERROR;
                //     }
                //     else
                //     {
                //         /* do nothing */
                //     }
                // }
                // else if(fl_session_u8 == UDS_PROGRAMMING_SESSION)
                // {
                //     /*Check for incorrect conditions flag status*/
                //     if(UDSAPP_PROG_SESS_CNC_CHECK_SID_10_SF_02 == UDS_FALSE)
                //     {
                //         /*update current session as programming session*/
                //         fl_ReqSession_u8 = UDS_PROG_SESS;
                //         l_current_session_u8 = UDS_PROG_SESS;
                //         UDS_Update_Current_Session(fl_ReqSession_u8);
                //         UdsApp_SecurityLock();                       
                //         /*set valid request*/
                //         fl_status_u8 = UDS_NO_ERROR;
                //     }
                //    else
                //     {
                //         /* do nothing */                    
                //     }
                // }    
                // else if(fl_session_u8 == UDS_EXTENDED_DIAGNOSTIC_SESSION)
                // {
                //     /*Check for incorrect conditions flag status*/
                //     if(UDSAPP_EXTENDED_SESS_CNC_CHECK_SID_10_SF_03 == UDS_FALSE)
                //     {
                //         /*update current session as extended diagnostic session*/
                //         fl_ReqSession_u8 = UDS_EXTND_SESS;
                //         l_current_session_u8 = UDS_EXTND_SESS;
                //         UDS_Update_Current_Session(fl_ReqSession_u8);
                //         UdsApp_SecurityLock();
                //         /*set valid request*/
                //         fl_status_u8 = UDS_NO_ERROR;
                //     }
                //     else
                //     {
                //         /* do nothing */
                    
                //     }
                // }
                // else if(fl_session_u8 == UDS_VISTEON_SESSION)
                // {
                //     /*Check for incorrect conditions flag status*/
                //     if(UDSAPP_VISTEON_SESS_CTRL_CNC_CHECK_SID_10_SF_60 == UDS_FALSE)
                //     {
                //         /*update current session as safety system diagnostic session*/
                //         fl_ReqSession_u8 = UDS_VISTEON_SYS_DIAG_SESS;
                //         l_current_session_u8 = UDS_VISTEON_SYS_DIAG_SESS;
                //         UDS_Update_Current_Session(fl_ReqSession_u8);
                //         UdsApp_SecurityLock();
                //         /*set valid request*/
                //         fl_status_u8 = UDS_NO_ERROR;
                //     }
                //     else
                //     {
                //         /* do nothing */                    
                //     }
                // }
                //  else
                // {
                //     /* do nothing */                   
    
                // }
            }
            else
            {
                /*Send NRC since conditions to proceed are incorrect*/
                fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;
            }
        }
        else
        {
            /*send negative response code as sub function not supported*/
            fl_status_u8 = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
        }
    }
    else
    {
        /*send negative response code as invalid format*/
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }

    /*send negative response if request is not valid*/
    if(fl_status_u8 != UDS_NO_ERROR)
    {
        UDS_SendNegativeResponse(fl_status_u8, UDS_DIAG_SESSION_CONTROL_SID);
    }
    else
    {
        if ((UDS_UINT8)UDS_ZERO == UDS_INSPECT_POS_RSP_SUPPRESSED(fl_pdiagdata_u8))
        {
            /*positive response for diagnostic session request*/
            fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_DIAG_SESSION_CONTROL_POSITIVE_RESP;
            fl_response_buffer_u8[BUFF_INDEX_ONE] = fl_session_u8;
            fl_response_buffer_u8[BUFF_INDEX_TWO] = (uint8_t)(UDS_P2_TIMER_MAXCNT >> UDS_SHIFT_EIGHT);
            fl_response_buffer_u8[BUFF_INDEX_THREE] = (uint8_t)(UDS_P2_TIMER_MAXCNT & 0xffu);
            fl_response_buffer_u8[BUFF_INDEX_FOUR] = (uint8_t)(UDS_P2STAR_TIMER_MAXCNT >> UDS_SHIFT_EIGHT);
            fl_response_buffer_u8[BUFF_INDEX_FIVE] = (uint8_t)(UDS_P2STAR_TIMER_MAXCNT & 0xffu);

            /*send positive response if request is valid*/
           UDS_SendPositiveResponse(fl_response_buffer_u8, LENGTH_SIX);
        }
        else
        {
            fl_CurrentRequestType_u8 = UDS_GetCurrentRequestType();
            /*suppress response for a request*/
            UDS_SuppressPosResponse(fl_CurrentRequestType_u8);
        }
    }
}
#endif

#if(UDS_ECU_RESET_SID_0x11_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the ECU Reset request (0x11)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_EcuReset(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{

    UDS_UINT8 fl_status_u8;
    UDS_UINT8 fl_subfunc_u8 = UDS_INIT;
    static UDS_UINT8 fl_response_buffer_u8[BUFF_INDEX_FIVE];
    UDS_UINT8 fl_CurrentRequestType_u8;

    /*initialize the status of ECU reset request*/
    fl_status_u8 = UDS_NO_ERROR;

    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
    if((NULL == fl_pdiagdata_u8) || (fl_datalength_u16 != (UDS_UINT16)UDS_ECU_RESET_REQUEST_LENGTH))
    {
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }
    else
    {
        /* removing the supressed positive response bit from the ECU reset request*/
        fl_subfunc_u8 = (fl_pdiagdata_u8[BUFF_INDEX_ZERO]& UDS_RESPONSE_SUPPRESS_MASK);

        /*Storing the Request reset type to handle in the post handler*/
        l_ECUReset_Subfunction_u8 = fl_subfunc_u8;

         /* CHECK FOR THE VALID SESSION */
        if((fl_pdiagdata_u8[BUFF_INDEX_ZERO] == UDS_HARD_RESET) || (fl_pdiagdata_u8[BUFF_INDEX_ZERO] == UDS_KEY_OFF_ON_RESET) ||
           (fl_pdiagdata_u8[BUFF_INDEX_ZERO] == UDS_SOFT_RESET))
        {
            #if(SECURITY_ACCESS_FEATURE_SID_0x11 == STD_ON)
            /*Check whether Security Acccess is available to Proceed the service*/
            if(l_security_access_status_u8 == UDS_SECURITY_UNLOCKED_STATE)
            {
             #endif
                /* check whether the vehicle speed is zero or not */
                if(UDS_VEHICLE_SPEED() == 0)
                {
                        if(fl_subfunc_u8 == UDS_HARD_RESET)
                        {          
                            /*Check for incorrect conditions flag status*/
                            if(UDSAPP_HARD_ECU_RESET_CNC_CHECK_SID_11_SF_01  == UDS_FALSE)
                            {
                                /* ECU reset shall happen after sent the positive response */
                                l_reset_pending_u8 = UDS_TRUE;

                                /*clear ECU shut down flag*/
                                l_power_shutdown_enable_u8 = UDS_FALSE;
                                l_power_shutdown_disable_u8 = UDS_FALSE;
                            }
                            else
                            {
                                /* do nothing */
                            }
                        }
                        else if(fl_subfunc_u8 == UDS_KEY_OFF_ON_RESET)
                        {
                            /*Check for incorrect conditions flag status*/
                            if(UDSAPP_KEYOFF_ECU_RESET_CNC_CHECK_SID_11_SF_02  == UDS_FALSE)
                            {
                                /* ECU reset shall happen after sent the positive response */
                                l_reset_pending_u8 = UDS_TRUE;

                                /*clear ECU shut down flag*/
                                l_power_shutdown_enable_u8 = UDS_FALSE;
                                l_power_shutdown_disable_u8 = UDS_FALSE;
                            }
                            else
                            {
                                 /* do nothing */
                            }
                        }
                        else if(fl_subfunc_u8 == UDS_SOFT_RESET)
                        {
                            /*Check for incorrect conditions flag status*/
                            if(UDSAPP_SOFT_ECU_RESET_CNC_CHECK_SID_11_SF_03 == UDS_FALSE)
                            {
                                /* ECU reset shall happen after sent the positive response */
                                l_reset_pending_u8 = UDS_TRUE;

                                /*clear ECU shut down flag*/
                                l_power_shutdown_enable_u8 = UDS_FALSE;
                                l_power_shutdown_disable_u8 = UDS_FALSE;
                            }
                            else
                            {
                                /* do nothing */
                            }
                        }                                       
                       
                    #if(SECURITY_ACCESS_FEATURE_SID_0x11 == STD_ON)
                }
                else
                {
                    /*Send NRC if vehicle speed is not zero*/
                    fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;
                }
            }
            else
            {
                /*Send negative response code as Security Access Denied*/
                fl_status_u8 = UDS_NRC_SECURITY_ACCESS_DENIED;
            }
                    #endif
        }
        else
        {
            /*Send NRC since conditions to proceed are incorrect*/
            fl_status_u8 = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
        }
        
    }

    /*send negative response if request is not valid*/
    if(fl_status_u8 != UDS_NO_ERROR)
    {
        UDS_SendNegativeResponse(fl_status_u8, UDS_ECU_RESET_SID);
    }
    else
    {
        if((UDS_UINT8)UDS_FALSE == UDS_INSPECT_POS_RSP_SUPPRESSED(fl_pdiagdata_u8))
        {
            if(fl_subfunc_u8 == UDS_ENABLE_RAPID_POWER_SHUTDOWN)
            {
                /*positive response for ECU reset request*/
                fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_ECU_RESET_POSITIVE_RESP;
                fl_response_buffer_u8[BUFF_INDEX_ONE] = fl_subfunc_u8;
                fl_response_buffer_u8[BUFF_INDEX_TWO] = ECU_RST_POWERDOWNTIME;
                UDS_SendPositiveResponse(fl_response_buffer_u8, LENGTH_THREE);
            }
            else
            {
                /*positive response for ECU reset request*/
                fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_ECU_RESET_POSITIVE_RESP;
                fl_response_buffer_u8[BUFF_INDEX_ONE] = fl_subfunc_u8;
                UDS_SendPositiveResponse(fl_response_buffer_u8, LENGTH_TWO);
            }   
        }
        else
        {
            fl_CurrentRequestType_u8 = UDS_GetCurrentRequestType();
            /*suppress response for a request*/
            UDS_SuppressPosResponse(fl_CurrentRequestType_u8);
        }
    }
 
}
#endif

#if(UDS_CLEAR_DTC_SID_0x14_FEATURE == STD_ON)
/*
* @brief    This service is used to clear diagnostic information in one or multiple memory (0x14)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_ClearDiagnosticInformation(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8 = UDS_NO_ERROR;
    UDS_UINT32 fl_GroupOfDTC_u32 = 0u;
    static UDS_UINT8 fl_response_u8 = UDS_CLEAR_DIAG_INFO_POSITIVE_RESP;
    Clear_Dtc_ErrorCode fl_ClearStatus = DTC_NO_ERROR;
    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
    if ((NULL == fl_pdiagdata_u8) || (fl_datalength_u16 < (UDS_UINT16)UDS_CLEAR_DTC_INFO_REQUEST_LENGTH))
    {
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }
    else
    {
        /*Verification of Conditions Correct to proceed Clearing DTC Information*/
        if(UDSAPP_CLEAR_DIAG_INFO_CNC_CHECK_SID_14 == UDS_FALSE)
        {
            /*Read the DTC group to be cleared*/
            fl_GroupOfDTC_u32 |= ( ((UDS_UINT32)fl_pdiagdata_u8[0] << UDS_SHIFT_SIXTEEN ) | \
                                 ( (UDS_UINT32)fl_pdiagdata_u8[1] << UDS_SHIFT_EIGHT ) | \
                                 ( (UDS_UINT32)fl_pdiagdata_u8[2]) );

            /*Status retriving after Clear operation execution*/
            fl_ClearStatus = Uds_Dtc_Clear_Diagnostics_Info(fl_GroupOfDTC_u32);

            /*Process the Clear status based on the Error code returned by Dtc Layer*/
            switch(fl_ClearStatus)
            {
                case DTC_NO_ERROR:
                        /*Set status as no error since DTCs requested are cleared successfully*/
                        fl_status_u8 = UDS_NO_ERROR;
                        break;
                case DTC_GRP_NOT_FOUND:
                        /*Trigger NRC 0x31, Since Requested DTC to be cleared not supported*/
                        fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
                        break;
                case DTC_NOT_CLEARABLE:
                        /*Trigger NRC 0x72, Since ECU has detected an error while clearing the data*/
                        fl_status_u8 = UDS_NRC_GENERAL_PROGRAMMING_FAILURE;
                        break;
                default:
                        /*Do nothing*/
                        break;
            }
        }
        else
        {
            /*Trigger NRC 0x22 since conditions to proceed Clearing Diagnostics is not satisfied*/
            fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;
        }
    }
    /*send negative response if request is not valid*/
    if (fl_status_u8 != UDS_NO_ERROR)
    {
        UDS_SendNegativeResponse(fl_status_u8, UDS_CLEAR_DIAG_INFO_SID);
    }
    else
    {
        /*send positive response if request is valid*/
        UDS_SendPositiveResponse(&fl_response_u8, LENGTH_ONE);
    }
}
#endif 

#if(UDS_READ_DTC_SID_0x19_FEATURE == STD_ON)
/*
* @brief    This service is used to read the status of resident Diagnostic Trouble Code (DTC) information (0x19)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_ReadDTCInformation(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8;
    UDS_UINT8 fl_subfunc_u8;
    static UDS_UINT8 fl_resp_buff_len_u8 = UDS_INIT;
    static UDS_UINT8 fl_resp_buff_u8[RESPONSE_LENGTH_MAX];
    UDS_UINT8 fl_CurrentRequestType_u8;
    

    /* invalid format or length check */
    if((NULL == fl_pdiagdata_u8) || (fl_datalength_u16 < LENGTH_ONE))
    {
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }
    else
    {
        /*get sub function for read DTC information request*/
        fl_subfunc_u8 = (fl_pdiagdata_u8[BUFF_INDEX_ZERO]& UDS_RESPONSE_SUPPRESS_MASK);

        /*Clearing the static buffer before writing with data*/
        memset(&fl_resp_buff_u8, 0u, sizeof(fl_resp_buff_u8));

        /*Clearing static variable before writing with data*/
        memset(&fl_resp_buff_len_u8, 0u, sizeof(fl_resp_buff_len_u8));

        /*Sub-function*/
        switch(fl_subfunc_u8)
        {
            case UDS_REPORT_NUMBER_OF_DTC_BY_STATUS_MASK:

                if(fl_datalength_u16 == UDS_REPORT_NUMBER_OF_DTC_BY_STATUS_MASK_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_DTC_BY_STATUS_MASK:

                if(fl_datalength_u16 == UDS_REPORT_DTC_BY_STATUS_MASK_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_DTC_SNAPSHOT_IDENTIFICATION:

                if(fl_datalength_u16 == UDS_REPORT_DTC_SNAPSHOT_IDENTIFICATION_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER:

                if(fl_datalength_u16 == UDS_REPORT_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_DTC_STORED_DATA_BY_RECORD_NUMBER:

                if(fl_datalength_u16 == UDS_REPORT_DTC_STORED_DATA_BY_RECORD_NUMBER_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_DTC_EXT_DATA_RECORD_BY_DTC_NUMBER:

                if(fl_datalength_u16 == UDS_REPORT_DTC_EXT_DATA_RECORD_BY_DTC_NUMBER_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_NUMBER_OF_DTC_BY_SEVERITY_MASK_RECORD:

                if(fl_datalength_u16 == UDS_REPORT_NUMBER_OF_DTC_BY_SEVERITY_MASK_RECORD_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_DTC_BY_SEVERITY_MASK:

                if(fl_datalength_u16 == UDS_REPORT_DTC_BY_SEVERITY_MASK_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_SEVERITY_INFORMATION_OF_DTC:

                if(fl_datalength_u16 == UDS_REPORT_SEVERITY_INFORMATION_OF_DTC_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_MIRROR_MEMORY_DTC_EXT_DATA_RECORD_BY_DTC_NUMBER:

                if(fl_datalength_u16 == UDS_REPORT_MIRROR_MEMORY_DTC_EXT_DATA_RECORD_BY_DTC_NUMBER_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_SUPPORTED_DTC:

                if(fl_datalength_u16 == UDS_REPORT_SUPPORTED_DTC_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_FIRST_TEST_FAILED_DTC:

                if(fl_datalength_u16 == UDS_REPORT_FIRST_TEST_FAILED_DTC_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_FIRST_CONFIRMED_DTC:

                if(fl_datalength_u16 == UDS_REPORT_FIRST_CONFIRMED_DTC_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_MOST_RECENT_TEST_FAILED_DTC:

                if(fl_datalength_u16 == UDS_REPORT_MOST_RECENT_TEST_FAILED_DTC_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_MOST_RECENT_CONFIRMED_DTC:

                if(fl_datalength_u16 == UDS_REPORT_MOST_RECENT_CONFIRMED_DTC_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_MIRROR_MEMORY_DTC_BY_STATUS_MASK:

                if(fl_datalength_u16 == UDS_REPORT_MIRROR_MEMORY_DTC_BY_STATUS_MASK_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_NUMBER_OF_MIRROR_MEMORY_DTC_BY_STATUS_MASK:

                if(fl_datalength_u16 == UDS_REPORT_NUMBER_OF_MIRROR_MEMORY_DTC_BY_STATUS_MASK_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_NUMBER_OF_EMISSIONS_OBD_DTC_BY_STATUS_MASK:

                if(fl_datalength_u16 == UDS_REPORT_NUMBER_OF_EMISSIONS_OBD_DTC_BY_STATUS_MASK_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_EMISSIONS_OBD_DTC_BY_STATUS_MASK:

                if(fl_datalength_u16 == UDS_REPORT_EMISSIONS_OBD_DTC_BY_STATUS_MASK_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_DTC_FAULT_DETECTION_COUNTER:

                if(fl_datalength_u16 == UDS_REPORT_DTC_FAULT_DETECTION_COUNTER_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_DTC_WITH_PERMANENT_STATUS:

                if(fl_datalength_u16 == UDS_REPORT_DTC_WITH_PERMANENT_STATUS_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_DTC_EXT_DATA_RECORD_BY_RECORD_NUMBER:

                if(fl_datalength_u16 == UDS_REPORT_DTC_EXT_DATA_RECORD_BY_RECORD_NUMBER_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_USER_DEF_MEMORY_DTC_BY_STATUS_MASK:

                if(fl_datalength_u16 == UDS_REPORT_USER_DEF_MEMORY_DTC_BY_STATUS_MASK_LENGTH)
                {   
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_USER_DEF_MEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER:

                if(fl_datalength_u16 == UDS_REPORT_USER_DEF_MEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_USER_DEF_MEMORY_DTC_EXT_DATA_RECORD_BY_DTC_NUMBER:

                if(fl_datalength_u16 == UDS_REPORT_USER_DEF_MEMORY_DTC_EXT_DATA_RECORD_BY_DTC_NUMBER_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_WWH_OBD_DTC_BY_MASK_RECORD:

                if(fl_datalength_u16 == UDS_REPORT_WWH_OBD_DTC_BY_MASK_RECORD_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;

            case UDS_REPORT_WWHOBD_DTC_WITH_PERMANENT_STATUS:

                if(fl_datalength_u16 == UDS_REPORT_WWHOBD_DTC_WITH_PERMANENT_STATUS_LENGTH)
                {
                    /*Read DTC information from Dtc Manager*/
                    Uds_Dtc_ReadDtc_Info(&fl_pdiagdata_u8[0], &fl_resp_buff_u8[2], &fl_resp_buff_len_u8);
                    fl_status_u8 = UDS_NO_ERROR;
                }
                else
                {
                    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
            break;
                
            default:

                /*set negative response code as sub function not supported for read DTC information request*/
                fl_status_u8 = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
            break;   
        }
    }

    /*Check for positive response or negative response transmission based on the status*/
    if(fl_status_u8 != UDS_NO_ERROR)
    {
        /*Transmit the response*/
        UDS_SendNegativeResponse(fl_status_u8, UDS_READ_DTCINFO_SID);
    }
    else
    {
        if ((UDS_UINT8)UDS_ZERO == UDS_INSPECT_POS_RSP_SUPPRESSED(fl_pdiagdata_u8))
        {
            fl_resp_buff_u8[BUFF_INDEX_ZERO] = UDS_READ_DTCINFO_POSITIVE_RESP;
            fl_resp_buff_u8[BUFF_INDEX_ONE] = fl_subfunc_u8;
            fl_resp_buff_len_u8 += LENGTH_TWO;
            /*Transmit the response*/
            UDS_SendPositiveResponse(fl_resp_buff_u8, fl_resp_buff_len_u8);
        }
        else
        {
            fl_CurrentRequestType_u8 = UDS_GetCurrentRequestType();
            /*suppress response for a request*/
            UDS_SuppressPosResponse(fl_CurrentRequestType_u8);
        }
    }
}
#endif

#if(UDS_READ_DID_SID_0x22_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the UDS Read DID request (0x22)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_ReadDataByIdentifier(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8;
    UDS_UINT16 fl_subfunc_u16;
    UDS_UINT8 fl_subfunc_matched_u8 = UDS_FALSE;
    static UDS_UINT8 fl_response_buffer_u8[RESPONSE_LENGTH_MAX] = {UDS_INIT};
    UDS_UINT8 fl_DID_Byte1_Index = UDS_INIT;
    UDS_UINT8 fl_DID_Byte2_Index = LENGTH_ONE;
    UDS_UINT8 fl_Index_DID_Received_u8;
    UDS_UINT8 fl_Index_DID_Supported_u8;
    static UDS_UINT8 fl_NumOfDIDReceived_u8;
    UDS_UINT16 fl_resp_buff_index_u16 = LENGTH_ONE;
	UDS_UINT8 fl_readstatus_u8 = E_NOT_OK;
    
    /*Get request type to fetch the length from corresponding buffer of Core layer*/
    UDS_UINT8 fl_CurrentReq_Type_u8 = UDS_GetCurrentRequestType();

    /*With the request type data - Get the request length to process whether multiple DIDs requested*/
    UDS_UINT32 fl_BufferLength_u32 = UDS_GetBufferLength(fl_CurrentReq_Type_u8);

    /*Based on length - Calculate the number of DIDs requested to be read*/
    fl_NumOfDIDReceived_u8 = (UDS_UINT8)(((fl_BufferLength_u32)-LENGTH_ONE) / LENGTH_TWO);

    /*Initialize the positive response length with minimum index value based on number of DIDs*/
    UDS_UINT16 fl_response_length_u16 = (UDS_UINT16)( LENGTH_ONE + (fl_NumOfDIDReceived_u8 * LENGTH_TWO));
    
    /*initialize the status of read DID*/
    fl_status_u8 = UDS_NO_ERROR;

    /*Check for valid length */
    if((NULL == fl_pdiagdata_u8) || (fl_datalength_u16 < LENGTH_TWO))
    {
        /*send negative response code as invalid format for the read DID request*/
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }
    else
    {
        #if(SECURITY_ACCESS_FEATURE_SID_0x22 == STD_ON)
        /*Check whether Security Acccess is available to Proceed the service*/
        if(l_security_access_status_u8 == UDS_SECURITY_UNLOCKED_STATE)
        {
        #endif
                /*Iterate upto total number of DID rrequests received*/
                for(fl_Index_DID_Received_u8 = UDS_ZERO; fl_Index_DID_Received_u8 < fl_NumOfDIDReceived_u8; fl_Index_DID_Received_u8++)
                {
                    /* Get the requested DID */
                    fl_subfunc_u16 = (((UDS_UINT16)fl_pdiagdata_u8[fl_DID_Byte1_Index] << UDS_SHIFT_EIGHT) |
                                      (UDS_UINT16)fl_pdiagdata_u8[fl_DID_Byte2_Index]);

                    /*Index to extract data ID from the pointer received*/
                    fl_DID_Byte1_Index = fl_DID_Byte2_Index + LENGTH_ONE;
                    fl_DID_Byte2_Index = fl_DID_Byte2_Index + LENGTH_TWO;

                    /*Iterate upto total nummber of DID supported as per the DID configuration table*/
                    for(fl_Index_DID_Supported_u8 = UDS_ZERO; fl_Index_DID_Supported_u8 < TOTAL_READ_DID_SUPPORTED; fl_Index_DID_Supported_u8++)
                    {
                        /*Check if received DID is supported with reference to the configurations of total DID list*/
                        if(g_ReadDIDInfo_List_st[fl_Index_DID_Supported_u8].DID == fl_subfunc_u16)
                        {
                            fl_response_buffer_u8[fl_resp_buff_index_u16] = (UDS_UINT8)(fl_subfunc_u16 >> UDS_SHIFT_EIGHT);
                            fl_resp_buff_index_u16 += LENGTH_ONE;

                            fl_response_buffer_u8[fl_resp_buff_index_u16] = (UDS_UINT8)fl_subfunc_u16;
                            fl_resp_buff_index_u16 += LENGTH_ONE;

                            fl_subfunc_matched_u8 = UDS_TRUE;

                            /*Calculate the response length for each DID received*/
                            fl_response_length_u16 += g_ReadDIDInfo_List_st[fl_Index_DID_Supported_u8].DID_size;

                            /*Check whether response lenggth exceeds maximum value supported by the TP*/
                            if(fl_response_length_u16 < RESPONSE_LENGTH_MAX)
                            {
                                /*Read for 1st DID*/
                                if(fl_Index_DID_Received_u8 == UDS_ZERO)
                                {
                                    /*Read data from NVM for the received DID*/
                                    fl_readstatus_u8 = UDSAPP_READ_DID_SUPPORT(g_ReadDIDInfo_List_st[fl_Index_DID_Supported_u8].DID, &fl_response_buffer_u8[fl_resp_buff_index_u16], \
                                                              g_ReadDIDInfo_List_st[fl_Index_DID_Supported_u8].DID_size);
                                    if(fl_readstatus_u8 != E_NOT_OK)
                                    {
                                        /*Data read successfully*/
                                        fl_status_u8 = UDS_NO_ERROR;
                                    }
                                    else
                                    {
                                        /*Unable to read data successfully since Conditions not correct*/
                                        fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;
                                    }
                                }
                                /*Proceed reading if more than 1 DID requested*/
                                else
                                {
                                    /*Read from Memory*/
                                    fl_readstatus_u8 = UDSAPP_READ_DID_SUPPORT(g_ReadDIDInfo_List_st[fl_Index_DID_Supported_u8].DID, &fl_response_buffer_u8[fl_resp_buff_index_u16], \
                                                              g_ReadDIDInfo_List_st[fl_Index_DID_Supported_u8].DID_size);
                                                              
                                    /*Verification whether Read status successful/ unsuccessful*/
                                    if(fl_readstatus_u8 != E_NOT_OK)
                                    {
                                        /*Data read successfully*/
                                        fl_status_u8 = UDS_NO_ERROR;
                                        fl_resp_buff_index_u16 += g_ReadDIDInfo_List_st[fl_Index_DID_Supported_u8].DID_size;
                                    }
                                    else
                                    {
                                        /*Unable to read data successfully since Conditions not correct*/
                                        fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;
                                    }
                                } 
                            }
                            else
                            {
                                /*Trigger NRC 0x22 since reponse length calculated is too long*/
                                fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;
                            } 
                        }
                    }
                    if(fl_subfunc_matched_u8 != UDS_TRUE)
                    {
                        /*No matching DID from the configurations, Trigger NRC 0x31 Request Out of Range*/
                        fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
                        fl_Index_DID_Received_u8 = fl_NumOfDIDReceived_u8;
                    }
                }
        #if(SECURITY_ACCESS_FEATURE_SID_0x22 == STD_ON)
        }
        else
        {
            /*Set NRC for no secuirty access available to perform this request*/
            fl_status_u8 = UDS_NRC_SECURITY_ACCESS_DENIED;
        }
        #endif
    }

    /*send negative response if request is not valid*/
    if(fl_status_u8 != UDS_NO_ERROR)
    {
        UDS_SendNegativeResponse(fl_status_u8, UDS_READ_DATABYID_SID);
    }
    else
    {
        /*response for read DID request*/
        fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_READ_DATABYID_POSITIVE_RESP;

        /*send positive response if request is valid*/
        UDS_SendPositiveResponse(fl_response_buffer_u8, fl_response_length_u16);
    }
}
#endif 

#if(UDS_WRITE_DID_SID_0x2E_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the UDS Write DID request (0x2E) 
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None 
*/
void UdsApp_WriteDataByIdentifier(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8;
    UDS_UINT16 fl_subfunc_u16;
    static UDS_UINT8 fl_response_buffer_u8[BUFF_INDEX_FIVE];
    UDS_UINT8 fl_Index_DID_Supported_u8;
    UDS_UINT8 fl_subfunc_matched = UDS_FALSE;
    UDS_UINT8 fl_datalength_matched_u8 = UDS_FALSE;
    /*Flag to return the callback status*/
    Std_ReturnType fl_WriteDID_Status_u8 = 0u;

    /*initialize the status of write DID*/
    fl_status_u8 = UDS_NO_ERROR;

  
           
                /* Get the requested DID */
                fl_subfunc_u16 = (((UDS_UINT16)fl_pdiagdata_u8[UDS_DID_OFFSET] << UDS_SHIFT_EIGHT) |
                                 (UDS_UINT16)fl_pdiagdata_u8[UDS_DID_OFFSET + LENGTH_ONE]);
                /*Iterate the whole configuration table to match the  DID*/
                for(fl_Index_DID_Supported_u8 = UDS_ZERO; fl_Index_DID_Supported_u8 < TOTAL_WRITE_DID_SUPPORTED; fl_Index_DID_Supported_u8++)
                {
                    /*Verification for matching DID in configuration table of Write DID service*/
                    if(g_WriteDIDInfo_List_st[fl_Index_DID_Supported_u8].DID ==  fl_subfunc_u16)
                    {
                           /*Check for valid length */
                        if(((fl_datalength_u16-LENGTH_TWO) != g_WriteDIDInfo_List_st[fl_Index_DID_Supported_u8].DID_size))
                        {   
                            /*send negative response code as invalid format for the read DID request*/
                            fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                        }
                        else
                        {
                            /*check vehicle speed whether it is zero or not */
                            if(UDSAPP_WRITE_DID_CNC_CHECK_SID_2E() == UDS_ZERO)
                            {
                                /*Check whether security is in unlocked state to proceed*/
                                if(l_security_access_status_u8 == UDS_SECURITY_UNLOCKED_STATE)
                                {
                                    /*Set the sub-function matched table*/
                                    fl_subfunc_matched = UDS_TRUE;
                                 
                                        fl_WriteDID_Status_u8 = UDSAPP_WRITE_DID_SUPPORT(fl_subfunc_u16, &fl_pdiagdata_u8[BUFF_INDEX_TWO], \
                                                                g_WriteDIDInfo_List_st[fl_Index_DID_Supported_u8].DID_size);

                                        if(E_OK == fl_WriteDID_Status_u8)
                                        {
                                            /*Do nothing*/
                                            fl_status_u8 = UDS_NO_ERROR;
                                        }
                                        else
                                        {
                                            /*Write operation unsuccessful, Trigger NRC 0x72*/
                                            fl_status_u8 = UDS_NRC_GENERAL_PROGRAMMING_FAILURE;
                                        }
                                    
                                }
                                else
                                {
                                    /*Set NRC for no security access available to perform this request*/
                                    fl_status_u8 = UDS_NRC_SECURITY_ACCESS_DENIED;
                                }
                            }
                            else
                            {
                                /* Trigger NRC 0x22 when vehicle speed is not zero */
                                fl_status_u8 =   UDS_NRC_CONDITIONS_NOT_CORRECT; 
                            }
                        } 
                            // if(g_WriteDIDInfo_List_st[fl_Index_DID_Supported_u8].DID ==  fl_subfunc_u16)
                            // {
                            //     if(fl_datalength_matched_u8 !=  UDS_TRUE)
                            //     {
                            //         /*Trigger NRC 0x13 since DID didn't match*/
                            //         fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;

                            //     }
                            // }
                            /*Check for DID match*/
                            // if(fl_subfunc_matched !=  UDS_TRUE)
                            break;
                    }
                    else
                    {
                        /*Trigger NRC 0x31 since DID didn't match*/
                        fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
                    }

                }
                

               
            


    /*send negative response if request is not valid*/
    if(fl_status_u8 != UDS_NO_ERROR)
    {
        UDS_SendNegativeResponse(fl_status_u8, UDS_WRITE_DID_SID);
    }
    else
    {
        /*response for write DID request*/
        fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_WRITE_DID_POSITIVE_RESP;
        fl_response_buffer_u8[BUFF_INDEX_ONE] = fl_pdiagdata_u8[BUFF_INDEX_ZERO];
        fl_response_buffer_u8[BUFF_INDEX_TWO] = fl_pdiagdata_u8[BUFF_INDEX_ONE];

        /*send positive response if request is valid*/
        UDS_SendPositiveResponse(fl_response_buffer_u8, 3);
    }
}
#endif 

#if(UDS_SECURITY_ACCESS_SID_0x27_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the UDS Security Access request (0x27)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_SecurityAccess(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    /*Initializing all local variables*/
    UDS_UINT8 fl_index_u8;
    UDS_UINT8 fl_ClientGeneratedKey_u8[BUFF_INDEX_FOUR];
    UDS_UINT8 fl_ECUGeneratedKey_u8[BUFF_INDEX_THREE];
    UDS_UINT8 fl_resp_length_u8 = UDS_INIT;
    UDS_UINT8 fl_status_u8;
    UDS_UINT8 fl_subfunc_u8 = UDS_INIT;
    static UDS_UINT8 fl_response_buffer_u8[BUFF_INDEX_SIX];
    UDS_UINT8 fl_CurrentRequestType_u8;

    /*Client ID verification feature enabled*/
    #if(SECURITY_ACCESS_DATA_RECORD_VERIFICATION == STD_ON)
    UDS_UINT8 fl_DataRecord_Index_u8;
    UDS_UINT32 fl_SecurityAccDataRecord_u32 = 0U;
    UDS_UINT8 fl_ShiftPositionLogic_u8;
    #endif 

        /*get the sub function of security access request*/
        fl_subfunc_u8 = (fl_pdiagdata_u8[BUFF_INDEX_ZERO]& UDS_RESPONSE_SUPPRESS_MASK);
      
        switch(fl_subfunc_u8)
        {
            /*Seed Request received*/
            case UDS_REQUEST_SEED:
            {
                /* Check for valid length */
                if((fl_datalength_u16 == UDS_SECURITY_ACCESS_SEED_LENGTH))
                {                                  
                    /*Verification of whether Security Access feature is already Unlocked*/
                    if(l_security_access_status_u8 != UDS_SECURITY_UNLOCKED_STATE)
                    {
                        if(UDS_Get_DelayTimer_Value() == UDS_FALSE)
                        {
                            #if(SECURITY_ACCESS_DATA_RECORD_VERIFICATION == STD_ON)
                            if(fl_datalength_u16 == (UDS_UINT16)UDS_SECURITY_ACCESS_SEED_LENGTH)
                            #else
                            /*Do nothing*/
                            #endif 
                            {   
                                if(UDS_VEHICLE_SPEED() == UDS_ZERO)
                                {
                                    #if(SECURITY_ACCESS_DATA_RECORD_VERIFICATION == STD_ON)
                                    /*Since SecurityAccess Data Record is received in request, process to compare the received 
                                    data record with Server's Static Data Record for verification*/
                                    for(fl_DataRecord_Index_u8 = UDS_ONE; fl_DataRecord_Index_u8 <= (fl_datalength_u16 - LENGTH_ONE); \
                                        fl_DataRecord_Index_u8++)
                                    {
                                        /*Data record could be of any length(Vehicle-Manufacturer specific), so logically preparing the shift positions*/
                                        fl_ShiftPositionLogic_u8 = (UDS_SHIFT_EIGHT * (fl_datalength_u16 - (fl_DataRecord_Index_u8 + LENGTH_ONE)));
                                        /*Variable update with Data record received from client for verification purpose*/
                                        fl_SecurityAccDataRecord_u32 |= fl_pdiagdata_u8[fl_DataRecord_Index_u8] << fl_ShiftPositionLogic_u8;
                                    }
                                        /*Verification of Client using SecurityAccessDataRecord*/
                                        /*Proceed only if Client Identification received matches with the client ID that the server is aware*/
                                    if(fl_SecurityAccDataRecord_u32 == UDS_SECURITY_ACC_DATA_RECORD)
                                    { 
                                    #endif
                                        /*Verification of Conditions satisfied to proceed sending the Seed*/
                                        if(UDSAPP_SEEDREQ_CNC_CHECK_SID_27_SF_01 == UDS_FALSE)
                                        {                                       

                                            /*Store the seed value into the response buffer*/
                                            UdsApp_SecurityAccess_SeedGeneration(&fl_response_buffer_u8[BUFF_INDEX_TWO]);

                                            fl_resp_length_u8 = LENGTH_SIX;

                                            /*set the status as no error if seed request as valid*/
                                            fl_status_u8 = UDS_NO_ERROR;
                                            l_SeedRequest_Sequence_Flag_u8 = UDS_TRUE;
                                        }
                                        else
                                        {
                                                /* do nothing */
                                        }

                                    #if(SECURITY_ACCESS_DATA_RECORD_VERIFICATION == STD_ON)
                                    }
                                    else
                                    {
                                        /*Trigger NRC 0x31 since SecurityAccessDataRecord received from client contains invalid data*/
                                        /*Client ID doesn't match with ID that the server is aware*/
                                        fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
                                    }
                                    #endif
                                }
                                else
                                {
                                    /*Trigger NRC 0x22 since vehicle speed is not zero*/
                                    fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;  
                                }    
                           

                            }                                
                            #if(SECURITY_ACCESS_DATA_RECORD_VERIFICATION == STD_ON)
                            else
                            {
                                /*send negative response code as invalid format for security access seed request*/
                                fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;  
                            }
                            #endif
                        }
                        else
                        {
                            /*Trigger NRC that Delay timer has not expired*/
                            fl_status_u8 = UDS_NRC_REQUIRED_TIME_DELAY_NOT_EXPIRED;
                        }
                    }
                    else
                    {
                        /*Send response with Seed Bytes as all zeroes indicating Security is already in Unlocked state*/
                        fl_response_buffer_u8[BUFF_INDEX_TWO] = 0x00u;
                        fl_response_buffer_u8[BUFF_INDEX_THREE] = 0x00u;
                        fl_response_buffer_u8[BUFF_INDEX_FOUR] = 0x00u;
                        fl_resp_length_u8 = LENGTH_SIX;

                        /*set the status as no error if seed request as valid*/
                        fl_status_u8 = UDS_NO_ERROR;
                    }
                }
                else
                {
                        /*send negative response code as invalid format for the write DID request*/
                        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                    
                }

                break;     
            }
            /* Security key validation request received */
            case UDS_SEND_KEY:
            {
                /* Check for valid length */
                if((fl_datalength_u16 == ((UDS_UINT16)UDS_SECURITY_ACCESS_KEY_LEN)))
                {
                    /*Check if Send Key request is received after Seed Request subfunction*/
                    if(l_SeedRequest_Sequence_Flag_u8 != UDS_FALSE)
                    {
                        if(UDS_VEHICLE_SPEED() == UDS_ZERO)
                        { 
                            /*Verification of Conditions satisfied to proceed sending the Seed*/
                            if(UDSAPP_SENDKEY_CNC_CHECK_SID_27_SF_02 == UDS_FALSE)
                            {
                                /* store the tool generated security key to validate */
                                for(fl_index_u8 = BUFF_INDEX_ZERO; fl_index_u8<((UDS_UINT8)UDS_SECURITY_ACCESS_KEY_LEN); fl_index_u8++)
                                {
                                    fl_ClientGeneratedKey_u8[fl_index_u8]=fl_pdiagdata_u8[fl_index_u8+1u];
                                }

                                    /* validate the tool generated and ecu generated security key*/
                                if( (fl_ClientGeneratedKey_u8[BUFF_INDEX_ZERO] == ((g_ECUGeneratedKey_u8 >>24) & 0xff)) && \
                                    (fl_ClientGeneratedKey_u8[BUFF_INDEX_ONE] == ((g_ECUGeneratedKey_u8 >> 16)&0xff) )&& \
                                    (fl_ClientGeneratedKey_u8[BUFF_INDEX_TWO] == ((g_ECUGeneratedKey_u8 >> 8)&0xff) ) &&\
                                    (fl_ClientGeneratedKey_u8[BUFF_INDEX_THREE] == ((g_ECUGeneratedKey_u8 )&0xff) ) )
                                {
                                    /*set the status as no error if key validation request has been verified successfully*/
                                    fl_status_u8 = UDS_NO_ERROR;

                                    /*set security status as un locked state*/
                                    l_security_access_status_u8 = UDS_SECURITY_UNLOCKED_STATE;

                                    fl_resp_length_u8 = LENGTH_TWO;
                                }
                                else
                                {
                                    /*Increment the invalid key counter  to  keep a track of the attempts*/
                                    l_InvalidKey_Attempt_Counter_u8 += UDS_ONE;

                                    /*Check if exceeded numbber of invalid key attempts*/
                                    if(l_InvalidKey_Attempt_Counter_u8 > INVALID_KEY_MAXIMUM_ATTEMPTS)
                                    {
                                        /*Restart the Delay timer on Exceeded attempts of invalid key before sending NRC 0x36*/
                                        UDS_Start_DelayTimer();

                                        /*Trigger NRC 0x36 for exceeded invalid key attempts*/
                                        fl_status_u8 = UDS_NRC_EXCEEDED_NUMBER_ATTEMPTS;

                                        /*set security status as locked state*/
                                        l_security_access_status_u8 = UDS_SECURITY_LOCKED_STATE;

                                        /*Clear the Counter flag*/
                                        l_InvalidKey_Attempt_Counter_u8 = UDS_INIT;
                                    }
                                    else
                                    {
                                        /*send negative response code as security access denied*/
                                        fl_status_u8 = UDS_NRC_INVALID_KEY;

                                        /*set security status as locked state*/
                                        l_security_access_status_u8 = UDS_SECURITY_LOCKED_STATE;
                                    }
                                }
                            }
                            else
                            {
                                /*Trigger NRC 0x22 since conditions to pproceed Seed Request not satisfied*/
                                fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;
                            }

                        }
                        else
                        {
                            /*send negative response code as vehicle speed is not Zero*/
                            fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT; 
                        }
                        
                    }
                    else
                    {
                        /*Send NRC since SEND KEY request received before SEED REQUEST*/
                        fl_status_u8 = UDS_NRC_REQUEST_SEQUENCE_ERROR;
                    }
                }
                else
                {
                    /*send negative response code as invalid format for the write DID request*/
                    fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }    
                break;
            }

            default:
            {
                /*Send NRC 0x12 since invalid subfunction has been received*/
                fl_status_u8 = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
                break;
            }
        }
       

    /*send negative response if request is not valid*/
    if(fl_status_u8 != UDS_NO_ERROR)
    {
        UDS_SendNegativeResponse(fl_status_u8, UDS_SECURITY_ACCESS_SID);
    }
    else
    {
        if ((UDS_UINT8)UDS_ZERO == UDS_INSPECT_POS_RSP_SUPPRESSED(fl_pdiagdata_u8))
        {
            /*response for security access request*/

            fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_SECURITY_ACCESS_POSITIVE_RESP;

            fl_response_buffer_u8[BUFF_INDEX_ONE] = fl_subfunc_u8;

            /*send positive response if request is valid*/
            UDS_SendPositiveResponse(fl_response_buffer_u8, fl_resp_length_u8);
        }
        else
        {
            fl_CurrentRequestType_u8 = UDS_GetCurrentRequestType();
            /*suppress response for a request*/
            UDS_SuppressPosResponse(fl_CurrentRequestType_u8);
        }
    }
}
#endif 

#if(UDS_COMMUNICATION_CTRL_SID_0x28_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the UDS Communication Control request (0x27)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_CommunicationControl(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8 = UDS_INIT;
    UDS_UINT8 fl_sub_func_u8 = UDS_INIT;
    UDS_UINT16 fl_identifier_u16;
    UDS_UINT8 fl_resp_length_u8 = UDS_INIT;
    UDS_UINT8 UDS_COMMUNICATION_TYPE;
    UDS_UINT8 UDS_NORMAL_COMMUNICATION = 0x01;
    UDS_UINT8 UDS_NETWORK_COMMUNICATION = 0x02;
    UDS_UINT8 UDS_NORMAL_AND_NETWORK_COMMUNICATION = 0x03;
    static UDS_UINT8 fl_response_buffer_u8[RESPONSE_LENGTH_MAX];


    /* Trigger NRC 0x13 since invalid data length received in the request message*/
    if(fl_datalength_u16 == (UDS_UINT16)UDS_COMMU_CONTROL_BY_ID_REQUEST_LENGTH)
    {
        /* removing the suppressed positive response bit from the communication control session request*/
        fl_sub_func_u8 = (fl_pdiagdata_u8[BUFF_INDEX_ZERO]& UDS_RESPONSE_SUPPRESS_MASK);
           
        switch(fl_sub_func_u8)
        {            
            case UDS_ENABLE_RX_TX:
            case UDS_ENABLE_RX_DISABLE_TX:
            case UDS_DISABLE_RX_ENABLE_TX:
            case UDS_DISABLE_RX_TX:
                if(fl_pdiagdata_u8[BUFF_INDEX_ONE] == UDS_NORMAL_COMMUNICATION || 
                    fl_pdiagdata_u8[BUFF_INDEX_ONE] == UDS_NORMAL_AND_NETWORK_COMMUNICATION || 
                    fl_pdiagdata_u8[BUFF_INDEX_ONE] == UDS_NETWORK_COMMUNICATION)
                {
                    /*check vehicle speed is zero or not*/
                    if(UDS_VEHICLE_SPEED() == UDS_ZERO)
                    {
                        /*set status as no error if valid request*/
                        fl_status_u8 = UDS_NO_ERROR;
                    }
                    else
                    {   /* If vehicle speed is not zero then trigger the 0x22 NRC */
                        fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;   
                    }
                }
                else
                {   /* comunication type is not valid then trigger the 0x31 NRC */
                    fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;    
                }
            break;
            default:
                /*set negative response code as sub function not supported for communication control request*/
                fl_status_u8 = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
            break;        
        }
    }
    else
    {
      /*send negative response code as invalid format for the write DID request*/
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;  
    }    

    /*send negative response if request is not valid*/
    if(fl_status_u8 != UDS_NO_ERROR)
    {
        UDS_SendNegativeResponse(fl_status_u8, UDS_COMMUNICATION_CONTROL_SID);
    }
    else
    {
        /* INTIMATE NETWORK MANAGER TO TAKE ACTION */
        UDS_COMMUNICATION_CONTROL_ACTION(fl_sub_func_u8, (fl_pdiagdata_u8[BUFF_INDEX_ONE] & 0x0F));

        /*response for read IO control by Identifier request*/
        fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_COMMU_CTRL_BYID_POSITIVE_RESP;
        fl_response_buffer_u8[BUFF_INDEX_ONE] = fl_pdiagdata_u8[BUFF_INDEX_ZERO];
        fl_response_buffer_u8[BUFF_INDEX_TWO] = fl_pdiagdata_u8[BUFF_INDEX_ONE];
        fl_response_buffer_u8[BUFF_INDEX_THREE] = fl_sub_func_u8;

        /*send positive response if request is valid*/
        UDS_SendPositiveResponse(fl_response_buffer_u8, LENGTH_FIVE);
    }
}
#endif

#if(UDS_IO_CTRL_BY_ID_SID_0x2F_FEATURE == STD_OFF)
/*
* @brief    This service is used to substitute a value for an input signal, 
*           and/or force control to a value for an output signal (0x2F)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_InputOutputControlByIdentifier(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8;
    UDS_UINT8 fl_sub_func_u8 = UDS_INIT;
    static UDS_UINT8 fl_response_buffer_u8[BUFF_INDEX_FIVE];
    UDS_UINT8 fl_Index_DID_Supported_u8;
    UDS_UINT16 fl_DID_u16;
    UDS_UINT8 fl_DID_matched_u8;

    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
    if ((NULL == fl_pdiagdata_u8) || (fl_datalength_u16 != (UDS_UINT16)UDS_IO_CONTROL_BY_ID_REQUEST_LENGTH))
    {
            fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }
    else
    {
        if (l_security_access_status_u8 == UDS_SECURITY_UNLOCKED_STATE)
        {
            /*Verification of Conditions to be satisfied in proceeding with this service request*/
            if(UDSAPP_IO_CONTROLBYID_CNC_CHECK_SID_2F == UDS_FALSE)
            {            
                /*get sub function of I/O control by identifier*/
                fl_sub_func_u8 = fl_pdiagdata_u8[BUFF_INDEX_TWO];
                fl_DID_u16 = (((UDS_UINT16)fl_pdiagdata_u8[BUFF_INDEX_ZERO] << UDS_SHIFT_EIGHT) | \
                               (UDS_UINT16)fl_pdiagdata_u8[BUFF_INDEX_ONE]);
                for(fl_Index_DID_Supported_u8 = UDS_ZERO; fl_Index_DID_Supported_u8 < TOTAL_IO_DID_SUPPORTED; fl_Index_DID_Supported_u8++)
                {
                   if(g_IO_DIDInfo_List_st[fl_Index_DID_Supported_u8].DID ==  fl_DID_u16)
                   {
                       /*Set the flag for DID match*/
                       fl_DID_matched_u8 = UDS_TRUE;
                        switch(fl_sub_func_u8)
                        {
                            case UDS_RETURN_CONTROL_TO_ECU:
                                APP_RETURN_TO_ECU_IOCTRL(fl_DID_u16);
                                /*set status as no error if valid request*/
                                fl_status_u8 = UDS_NO_ERROR;
                                break;

                            case UDS_RESET_TO_DEFAULT:
                                APP_RESET_TO_DEFAULT_IOCTRL(fl_DID_u16);
                                /*set status as no error if valid request*/
                                fl_status_u8 = UDS_NO_ERROR;
                                break;

                            case UDS_FREEZE_CURRENT_STATE:
                                APP_FREEZE_CURRENT_STATE_IOCTRL(fl_DID_u16);
                                /*set status as no error if valid request*/
                                fl_status_u8 = UDS_NO_ERROR;
                                break;

                            case UDS_SHORT_TERM_ADJUSTMENT:
                                APP_SHORT_ADJUSMNT_IOCTRL(fl_DID_u16,&fl_pdiagdata_u8[THREE]);
                                /*set status as no error if valid request*/
                                fl_status_u8 = UDS_NO_ERROR;
                                break;

                            default:
                                /*set negative response code as sub function not supported for control DTC setting request*/
                                fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
                                break;
                        }
                   }
                }
                /*Check whether matching DID was found to control the I/O*/
                if(fl_DID_matched_u8 != TRUE)
                {
                    /*Trigger NRC 0x31, since DID match condition not satisfied*/
                    fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
                }
            }
            else
            {
                /*Trigger NRC 0x22 since conditions not satisfied to proceed this service request*/
                fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;
            }
            
        }
        else
        {
            /*Security in locked state, trigger NRC 0x33 for Security Access Denial*/
            fl_status_u8 = UDS_NRC_SECURITY_ACCESS_DENIED;
        }
    }

    /*send negative response if request is not valid*/
    if(fl_status_u8 != UDS_NO_ERROR)
    {
        UDS_SendNegativeResponse(fl_status_u8, UDS_IO_CTRL_BYID_SID);
    }
    else
    {
        /*response for read IO control by Identifier request*/
        fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_IO_CTRL_BYID_POSITIVE_RESP;
        fl_response_buffer_u8[BUFF_INDEX_ONE] = fl_pdiagdata_u8[BUFF_INDEX_ZERO];
        fl_response_buffer_u8[BUFF_INDEX_TWO] = fl_pdiagdata_u8[BUFF_INDEX_ONE];
        fl_response_buffer_u8[BUFF_INDEX_THREE] = fl_sub_func_u8;

        /*send positive response if request is valid*/
        UDS_SendPositiveResponse(fl_response_buffer_u8, LENGTH_FIVE);
    }
}
#endif 

#if(UDS_ROUTINE_CTRL_SID_0x31_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the UDS Routine Control request (0x31)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_RoutineControl(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8 = UDS_INIT;
    UDS_UINT8 fl_sub_func_u8 = UDS_INIT;
    UDS_UINT16 fl_identifier_u16;
    UDS_UINT8 fl_resp_length_u8 = UDS_INIT;
    static UDS_UINT8 fl_response_buffer_u8[RESPONSE_LENGTH_MAX];
    UDS_UINT8 fl_Routine_Index_u8;
    UDS_UINT8 fl_RoutineStatus_u8;
    UDS_UINT8 fl_RID_match_status_u8 = UDS_FALSE;
    UDS_UINT8 fl_GetResult_RespLength_u8 = UDS_INIT;
    UDS_UINT8 fl_CurrentRequestType_u8;    

    /* Check for invalid format */
    if( (NULL == fl_pdiagdata_u8) || ((fl_datalength_u16 < (UDS_UINT16)LENGTH_THREE)) )
    {
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }

    else
    {
        g_UDS_pre_condition_status = RoutineControl_Pre_Condition_check();

        if(g_UDS_pre_condition_status == UDS_TRUE)
        {
                /*get the routine identifier of routine control request*/
                fl_identifier_u16 = (((UDS_UINT16)fl_pdiagdata_u8[UDS_ROUTINE_OFFSET] << UDS_SHIFT_EIGHT) |
                                    (UDS_UINT16)fl_pdiagdata_u8[UDS_ROUTINE_OFFSET + LENGTH_ONE]);

                for(fl_Routine_Index_u8 = UDS_ZERO; fl_Routine_Index_u8 < MAX_NO_OF_ROUTINE; fl_Routine_Index_u8++)
                {
                    /*Verification for matching DID in configuration table of Write DID service*/
                    if(g_Routine_List_st[fl_Routine_Index_u8].RID ==  fl_identifier_u16)
                    {
                        /*get Security status*/
                        if( l_security_access_status_u8 ==UDS_SECURITY_UNLOCKED_STATE)
                        {
                            /*get the sub function of routine control request*/
                            fl_sub_func_u8 = (fl_pdiagdata_u8[BUFF_INDEX_ZERO]& UDS_RESPONSE_SUPPRESS_MASK);

                                        switch(fl_sub_func_u8)
                                        {
                                            /*check routine sub function as start routine*/
                                            case UDS_START_ROUTINE:

                                                // /*Start iterating for RID match*/
                                                // for(fl_Routine_Index_u8 = UDS_ZERO; fl_Routine_Index_u8 < MAX_NO_OF_ROUTINE; fl_Routine_Index_u8++)
                                                // {
                                                //     /*Check whether received RID is supported*/
                                                    // if(fl_identifier_u16 == g_Routine_List_st[fl_Routine_Index_u8].RID)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
                                                    // {
                                                        #if(ROUTINE_CTRL_OPTION_RECORD_FEATURE == STD_ON)
                                                        /*Check whether the received Routine Control Option record matches with the server data*/
                                                        if(UDS_TRUE == Application_Check_Routine_Ctrl_Option_Record_Match(&fl_pdiagdata_u8[LENGTH_THREE], g_Routine_List_st[fl_Routine_Index_u8].RID ,(fl_datalength_u16 - LENGTH_THREE)))
                                                        {
                                                        #endif
                                                            /*Set this flag to indicate that Routine ID has been matched*/
                                                            fl_RID_match_status_u8 = UDS_TRUE;

                                                            /*Verification of Conditions satisfied to proceed starting the routine requested*/
                                                            if(UDSAPP_STARTROUTINE_CNC_CHECK_SID_31_SF_01 == UDS_FALSE)
                                                            {
                                                                #if(ROUTINE_RESTART_FEATURE != STD_ON)
                                                                /*Check whether the Routine ID requested has been started already to avoid restarting of same routine*/
                                                                if(g_Routine_List_st[fl_Routine_Index_u8].RoutineState != UDS_ROUTINE_STARTED)
                                                                {
                                                                #endif
                                                                    if(Application_StartRoutine_Handler != NULL)
                                                                    {
                                                                        /*Execute the routine handler configured*/
                                                                        fl_RoutineStatus_u8 = Application_StartRoutine_Handler(g_Routine_List_st[fl_Routine_Index_u8].RID);
                                                                        /*Check whether routine handling was successful*/
                                                                        if(fl_RoutineStatus_u8 == UDS_TRUE)
                                                                        {
                                                                            fl_status_u8 = UDS_NO_ERROR;

                                                                            fl_resp_length_u8 = LENGTH_FOUR;

                                                                            /*Update the Routine state that it has been started*/
                                                                            g_Routine_List_st[fl_Routine_Index_u8].RoutineState = UDS_ROUTINE_STARTED;
                                                                        }
                                                                        else
                                                                        {
                                                                            /*Trigger NRC 0x72 since routine handling not done due to internal errors*/
                                                                            fl_status_u8 = UDS_NRC_GENERAL_PROGRAMMING_FAILURE;
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        /*Trigger NRC 0x72 since routine handling not done due to internal errors*/
                                                                        fl_status_u8 = UDS_NRC_GENERAL_PROGRAMMING_FAILURE;
                                                                    }
                                                                #if(ROUTINE_RESTART_FEATURE != STD_ON)
                                                                }
                                                                else
                                                                {
                                                                    /*Trigger NRC 0x24 since Start requested for a Routine that has been started already*/
                                                                    fl_status_u8 = UDS_NRC_REQUEST_SEQUENCE_ERROR;
                                                                }
                                                                #endif
                                                            }
                                                            else
                                                            {
                                                                /*Trigger NRC 0x22 since conditions in proceeding to start a routine not satisfied*/
                                                                fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;
                                                            }
                                                            #if(ROUTINE_CTRL_OPTION_RECORD_FEATURE == STD_ON)
                                                        }
                                                        else
                                                        {
                                                            /*Trigger NRC 0x31 since Request Out of Range due to Control Option Record Mismatch*/
                                                            fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
                                                        }
                                                        #endif    
                                                    //}
                                                // }
                                                // if(fl_RID_match_status_u8 != UDS_TRUE)
                                                // {
                                                //     /*send the negative response code as requested routine identifier is not supported*/
                                                //     fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
                                                // }
                                                fl_status_u8 = UDS_NO_ERROR;
                                                break;
                                            case UDS_STOP_ROUTINE:
                                            
                                                // /*Start iterating for RID match*/
                                                // for(fl_Routine_Index_u8 = UDS_ZERO; fl_Routine_Index_u8 < MAX_NO_OF_ROUTINE; fl_Routine_Index_u8++)
                                                // {
                                                //     /*Check whether received RID is supported*/
                                                //     if(fl_identifier_u16 == g_Routine_List_st[fl_Routine_Index_u8].RID)
                                                //     {
                                                        #if(ROUTINE_CTRL_OPTION_RECORD_FEATURE == STD_ON)
                                                        /*Check whether the received Routine Control Option record matches with the server data*/
                                                        if(UDS_TRUE == Application_Check_Routine_Ctrl_Option_Record_Match(&fl_pdiagdata_u8[LENGTH_THREE], \
                                                                    g_Routine_List_st[fl_Routine_Index_u8].RID ,(fl_datalength_u16 - LENGTH_THREE)))
                                                        {
                                                        #endif
                                                            /*Set this flag to indicate that Routine ID has been matched*/
                                                            fl_RID_match_status_u8 = UDS_TRUE;
                                                            /*Verification of Conditions satisfied to proceed starting the routine requested*/
                                                            if(UDSAPP_STOPROUTINE_CNC_CHECK_SID_31_SF_02 == UDS_FALSE)
                                                            {
                                                                /*Check whether the Routine ID requested has been started already to stop the routine*/
                                                                if( g_Routine_List_st[fl_Routine_Index_u8].RoutineState == UDS_ROUTINE_STARTED)
                                                                {
                                                                    if(Application_StopRoutine_Handler != NULL)
                                                                    {
                                                                        /*Execute the routine handler configured*/
                                                                        fl_RoutineStatus_u8 = Application_StopRoutine_Handler(g_Routine_List_st[fl_Routine_Index_u8].RID);
                                                                        /*Check whether routine handling was successful*/
                                                                        if(fl_RoutineStatus_u8 == UDS_TRUE)
                                                                        {
                                                                            fl_status_u8 = UDS_NO_ERROR;

                                                                            fl_resp_length_u8 = LENGTH_FOUR;

                                                                            /*Update the Routine state that it has been stopped*/
                                                                            g_Routine_List_st[fl_Routine_Index_u8].RoutineState = UDS_ROUTINE_STOPPED;
                                                                        }
                                                                        else
                                                                        {
                                                                            /*Trigger NRC 0x72 since routine handling not done due to internal errors*/
                                                                            fl_status_u8 = UDS_NRC_GENERAL_PROGRAMMING_FAILURE;
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        /*Trigger NRC 0x72 since routine handling not done due to internal errors*/
                                                                        fl_status_u8 = UDS_NRC_GENERAL_PROGRAMMING_FAILURE;
                                                                    }
                                                                    
                                                                }
                                                                else
                                                                {
                                                                    /*Trigger NRC 0x24 since Stop requested for a Routine that has not been started at all*/
                                                                    fl_status_u8 = UDS_NRC_REQUEST_SEQUENCE_ERROR;
                                                                }

                                                            }
                                                            else
                                                            {
                                                                /*Trigger NRC 0x22 since conditions in proceeding to start a routine not satisfied*/
                                                                fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;
                                                            }
                                                        #if(ROUTINE_CTRL_OPTION_RECORD_FEATURE == STD_ON)
                                                        }
                                                        else
                                                        {
                                                            /*Trigger NRC 0x31 since Request Out of Range due to Control Option Record Mismatch*/
                                                            fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
                                                        }
                                                        #endif
                                                //     }
                                                // }
                                                // if(fl_RID_match_status_u8 != UDS_TRUE)
                                                // {
                                                //     /*send the negative response code as requested routine identifier is not supported*/
                                                //     fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
                                                // }
                                                fl_status_u8 = UDS_NO_ERROR;
                                                break;
                                                    

                                        
                                            case UDS_REQUEST_ROUTINE_RESULTS:
                                            
                                            // /*Start iterating for RID match*/
                                            //     for(fl_Routine_Index_u8 = UDS_ZERO; fl_Routine_Index_u8 < MAX_NO_OF_ROUTINE; fl_Routine_Index_u8++)
                                            //     {
                                            //         /*Check whether received RID is supported*/
                                            //         if(fl_identifier_u16 == g_Routine_List_st[fl_Routine_Index_u8].RID)
                                            //         {
                                                        /*Set this flag to indicate that Routine ID has been matched*/
                                                        fl_RID_match_status_u8 = UDS_TRUE;
                                                        if(UDSAPP_GETROUTINERESULT_CNC_CHECK_SID_31_SF_03 == UDS_FALSE)
                                                        {
                                                            /*Check whether the Routine ID requested has been completed already to get the results*/
                                                            if( g_Routine_List_st[fl_Routine_Index_u8].RoutineState == UDS_ROUTINE_STOPPED)
                                                            {
                                                                if(Application_GetResultRoutine_Handler != NULL)
                                                                {
                                                                    /*Execute the routine handler configured*/
                                        							fl_RoutineStatus_u8 = Application_GetResultRoutine_Handler(fl_Routine_Index_u8, &fl_response_buffer_u8[BUFF_INDEX_FOUR], &fl_GetResult_RespLength_u8);

                                                                    /*Check whether routine handling was successful*/
                                                                    if(fl_RoutineStatus_u8 == UDS_TRUE)
                                                                    {
                                                                        fl_status_u8 = UDS_NO_ERROR;

                                                                        fl_resp_length_u8 = LENGTH_FOUR + fl_GetResult_RespLength_u8;
                                                                    }
                                                                    else
                                                                    {
                                                                        /*Trigger NRC 0x72 since routine handling not done due to internal errors*/
                                                                        fl_status_u8 = UDS_NRC_GENERAL_PROGRAMMING_FAILURE;
                                                                    }
                                                                }
                                                                else
                                                                {
                                                                    /*Trigger NRC 0x72 since routine handling not done due to internal errors*/
                                                                    fl_status_u8 = UDS_NRC_GENERAL_PROGRAMMING_FAILURE;
                                                                }
                                                            }   
                                                            else
                                                            {
                                                                /*Trigger NRC 0x24 since results requested for a Routine that has not been started at all*/
                                                                fl_status_u8 = UDS_NRC_REQUEST_SEQUENCE_ERROR;
                                                            }
                                                            
                                                        }
                                                        else
                                                        {
                                                            /*Trigger NRC 0x22 since conditions in proceeding to start a routine not satisfied*/
                                                            fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;
                                                        }
                                                //     }
                                                // }
                                                // if(fl_RID_match_status_u8 != UDS_TRUE)
                                                // {
                                                //     /*send the negative response code as requested routine identifier is not supported*/
                                                //     fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
                                                // }
                                                fl_status_u8 = UDS_NO_ERROR;
                                                break;
                                        
                                            default:
                                            {
                                                /*set negative response code as requested sub function not supported in routine control*/
                                                fl_status_u8 = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
                                                break;
                                            }
                                        
                                        }
                        }
                        else
                        {
                        fl_status_u8 = UDS_NRC_SECURITY_ACCESS_DENIED;
                        }
                    }
                    else
                    {
                        /*send the negative response code as requested routine identifier is not supported*/
                        fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;  
                    }
            }
     
        }
        else
        {
        /* if pre condition is failed then triger the NRC 0x22 */
        fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT; 
        }
    }
                    /*send negative response if request is not valid*/
                    if (fl_status_u8 != UDS_NO_ERROR)
                    {
                        UDS_SendNegativeResponse(fl_status_u8, UDS_ROUTINE_CTRL_SID);
                    }
                    else
                    {
                #if(UDSAPP_ROUTINE_CTRL_ASYNC_RESPONSE_SID_31)
                        /*Add the RID's for which ASYNC response is required*/
                        if(fl_identifier_u16 == (UDS_UINT16)0xff00)
                        {
                            UDS_SendRCRRP();
                        }
                        else
                #endif
                        {
                            if ((UDS_UINT8)UDS_ZERO == UDS_INSPECT_POS_RSP_SUPPRESSED(fl_pdiagdata_u8))
                            {
                                /*response for routine control request*/
                                fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_ROUTINE_CTRL_POSITIVE_RESP;
                                fl_response_buffer_u8[BUFF_INDEX_ONE] = fl_sub_func_u8;
                                fl_response_buffer_u8[BUFF_INDEX_TWO] = (fl_identifier_u16 >> UDS_SHIFT_EIGHT);
                                fl_response_buffer_u8[BUFF_INDEX_THREE] = fl_identifier_u16;

                                /*send positive response if request is valid*/
                                UDS_SendPositiveResponse(fl_response_buffer_u8, fl_resp_length_u8);
                            }
                            else
                            {
                                fl_CurrentRequestType_u8 = UDS_GetCurrentRequestType();
                                /*suppress response for a request*/
                                UDS_SuppressPosResponse(fl_CurrentRequestType_u8);
                            }
                        }
                    }

}
#endif 

#if(UDS_DWNLD_REQ_SID_0x34_FEATURE == STD_ON)
/*
* @brief    This service routine is used to downloading the data to FLash/NVM (0x34)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_RequestDownload(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8 = UDS_NO_ERROR;
    UDS_UINT8 fl_dataformat_identifier_u8;
    UDS_UINT8 fl_memoryaddress_length_u8;
    UDS_UINT8 fl_memorysize_length_u8;
    UDS_UINT32 fl_memoryaddress_u32 = (UDS_UINT32)UDS_INIT;
    UDS_UINT32 fl_memorysize_u32 = (UDS_UINT32) UDS_INIT;
    UDS_UINT8 fl_loopindex_u8;

    /*Minimum length validity check */
    if((fl_pdiagdata_u8 == NULL) || (fl_datalength_u16 < LENGTH_FIVE))
    {
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }
    /*Proceed further for both positive and negative use case*/
    else
    {

        /*Extracting memory address length and memory size length from
            * addressAndLengthFormatIdentifier high nibble specifies memory size length
            * and low nibble specifies memory address length*/

        UdsApp_DownloadRequestInit();

        fl_memoryaddress_length_u8 = (fl_pdiagdata_u8[1] & (UDS_UINT8)(0x0F));

        fl_memorysize_length_u8 = (UDS_UINT8)(((UDS_UINT8)(fl_pdiagdata_u8[1] >> 4)) & (UDS_UINT8)(0x0F));

        if((fl_memoryaddress_length_u8 > LENGTH_FOUR) || (fl_memorysize_length_u8 > LENGTH_FOUR))
        {
            /*Trigger NRC 31 as addressAndLengthFormatIdentifier is invalid*/
            fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
        }
        else
        {
            /*Request download service shall be processed only if security is unlocked*/
            if( UDS_SECURITY_LOCKED_STATE != l_security_access_status_u8)
            {
                for(fl_loopindex_u8 = (UDS_UINT8)1; fl_loopindex_u8 <= (fl_memoryaddress_length_u8 + fl_memorysize_length_u8); fl_loopindex_u8++)
                {
                    /*Append the received data for fl_memoryaddress_length_u8 to generate memory address*/
                    if(fl_loopindex_u8 <= fl_memoryaddress_length_u8 )
                    {
                        fl_memoryaddress_u32 |= (UDS_UINT32)fl_pdiagdata_u8[fl_loopindex_u8 + LENGTH_ONE] << \
                                (UDS_UINT8)((UDS_SHIFT_EIGHT)*(fl_memoryaddress_length_u8 - fl_loopindex_u8));
                    }
                    /* Append the received data for fl_memorysize_length_u8 to generate memory size */
                    else
                    {
                        fl_memorysize_u32 |= (UDS_UINT32)fl_pdiagdata_u8[fl_loopindex_u8 + LENGTH_ONE] << \
                                (UDS_UINT8)((UDS_SHIFT_EIGHT)*((UDS_UINT8)(fl_memorysize_length_u8 + fl_memoryaddress_length_u8) - fl_loopindex_u8));
                    }
                }

                /* Received download address*/
                l_RequestDownload.Download_address = fl_memoryaddress_u32;
                
                /* Total length to be downloaded*/
                l_RequestDownload.Download_length = fl_memorysize_u32;
            }
            
            else
            {
                /*Security is not unlocked NRC 0x33 should be triggered*/
                fl_status_u8 = UDS_NRC_SECURITY_ACCESS_DENIED;
            }
        }
    }
    if(fl_status_u8 == UDS_NO_ERROR)
    {
        fl_dataformat_identifier_u8 = fl_pdiagdata_u8[0];
        APP_REQUEST_DOWNLOAD_CBK(fl_memoryaddress_u32, fl_memorysize_u32, fl_dataformat_identifier_u8);
        /*CALLBACK function to be invoked*/
    }
    else
    {        
        /*Send negative response*/        
        UDS_SendNegativeResponse(fl_status_u8, UDS_DWNLD_REQUEST_SID);
    }
}
#endif 

#if(UDS_UPLD_REQ_SID_0x35_FEATURE == STD_ON)
/*
* @brief    This service routine is used to uploading the data from Server to Client(0x35)
* @param    fl_pdiagdata_u8   - Data associated with the request
* @param    fl_datalength_u16  - Length of the data
* @return   None
*/
void UdsApp_RequestUpload(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8 = UDS_NO_ERROR;
    UDS_UINT8 fl_length_memoryaddress_u8;
    UDS_UINT8 fl_length_memorysize_u8;
    UDS_UINT32 fl_memoryaddress_u32 = (UDS_UINT32)UDS_INIT;
    UDS_UINT32 fl_memorysize_u32 = (UDS_UINT32)UDS_INIT;
    UDS_UINT8 fl_loopindex_u8;

    /*Minimum length validity check */
    if((fl_pdiagdata_u8 == NULL) || (fl_datalength_u16 < LENGTH_FOUR))
    {
      fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }
    else
    {
        /*Request download service shall be processed only if security is unlocked*/
        if( UDS_SECURITY_LOCKED_STATE != l_security_access_status_u8)
        {
            /*Acquiring memory address length by masking bits 0 to 3*/
            fl_length_memoryaddress_u8 = (fl_pdiagdata_u8[BUFF_INDEX_ZERO] & 0x0Fu);

            /*Acquiring memory address length by masking bits 4 to 7 & shifting to get value according to low nibble*/
            fl_length_memorysize_u8 = ((fl_pdiagdata_u8[BUFF_INDEX_ZERO] & 0xF0u) >> UDS_SHIFT_FOUR);

            for(fl_loopindex_u8 = (UDS_UINT8)1; fl_loopindex_u8 <= (fl_length_memoryaddress_u8 + fl_length_memorysize_u8); fl_loopindex_u8++)
            {
                /*Append the received data for fl_memoryaddress_length_u8 to generate memory address*/
                if(fl_loopindex_u8 <= fl_length_memoryaddress_u8 )
                {
                    fl_memoryaddress_u32 |= (UDS_UINT32)fl_pdiagdata_u8[fl_loopindex_u8 + LENGTH_ONE] << \
                            (UDS_UINT8)((UDS_SHIFT_EIGHT)*(fl_length_memoryaddress_u8 - fl_loopindex_u8));
                }
                /*Append the received data for fl_memorysize_length_u8 to generate memory size*/
                else
                {
                    fl_memorysize_u32 |= (UDS_UINT32)fl_pdiagdata_u8[fl_loopindex_u8 + LENGTH_ONE] << \
                            (UDS_UINT8)((UDS_SHIFT_EIGHT)*((UDS_UINT8)(fl_length_memorysize_u8 + fl_length_memoryaddress_u8) - fl_loopindex_u8));
                }
            }
                /*Note: Validity check for Memory address & Memory size requested by the client to be done
                        To be added as per Vehicle-Manufacturer Micro details*/
                /*The variable fl_status_u8 to be updated with UDS_NO_ERROR or NRC's respectively at the end of this else-case*/

        }
        else
        {
           /*Security is not unlocked NRC 0x33 should be triggered*/
           fl_status_u8 = UDS_NRC_SECURITY_ACCESS_DENIED;
        }
    }

    if(fl_status_u8 != UDS_NO_ERROR)
    {
        /*Send negative response*/
        UDS_SendNegativeResponse(fl_status_u8, UDS_UPLOAD_REQUEST_SID);
    }
    else
    {
        /*Application callback function*/
        APP_REQUEST_UPLOAD_CBK(fl_memoryaddress_u32, fl_memorysize_u32, fl_dataformat_identifier_u8);
    }
}
#endif 

#if(UDS_TRNSFR_DATA_SID_0x36_FEATURE == STD_ON)
/*
* @brief    This service routine is used to Transfer the data to FLash/NVM. (0x36)
* @param    fl_pdiagdata_u8    - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_TransferData(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8 = UDS_NO_ERROR;
    UDS_UINT8 fl_voltage_status_u8;

    /*Minimum length validity check */
    if((fl_pdiagdata_u8 == NULL) || (fl_datalength_u16 < LENGTH_TWO))
    {
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }
    else
    {
        /*Check if request download or request upload service has been given prior to transfer data*/
        if((l_RequestDownload.Download_state != REQUEST_DOWNLOAD_INACTIVE) || (l_RequestDownload.Upload_state != REQUEST_UPLOAD_INACTIVE))
        {

            /*Check if block sequence counter has been incremented or same block sequence counter has been received*/
            if((l_RequestDownload.blocksequence_counter == fl_pdiagdata_u8[UDS_ZERO]) || \
                    ((l_RequestDownload.blocksequence_counter + (UDS_UINT8)1) == fl_pdiagdata_u8[UDS_ZERO]))
            {
                if((l_RequestDownload.blocksequence_counter + (UDS_UINT8)1) == fl_pdiagdata_u8[UDS_ZERO])
                {
                    /* Total length that has been received and flashed*/
                    l_RequestDownload.Downloaded_length += (UDS_UINT32)((UDS_UINT32)fl_datalength_u16 - (UDS_UINT32)1);

                    /*Move into transfer exit state when the requested total length has been flashed */    
                    if(l_RequestDownload.Downloaded_length == l_RequestDownload.Download_length)
                    {
                        l_RequestDownload.Download_state = TRANSFER_EXIT_STATE;

                        l_RequestDownload.Upload_state = TRANSFER_EXIT_STATE;
                    }
                    else if(l_RequestDownload.Downloaded_length > l_RequestDownload.Download_length)
                    {
                        fl_status_u8 = UDS_NRC_TRANSFER_DATA_SUSPENDED;
                    }
                    else
                    {
                        /*Do Nothing*/
                    }
                }
                /*Update block sequence counter with the received value*/
                l_RequestDownload.blocksequence_counter = fl_pdiagdata_u8[0];

                /*Reload the block sequence counter if maximum value of 255 has been reached*/
                if(l_RequestDownload.blocksequence_counter == (UDS_UINT8)0xFF)
                {
                    l_RequestDownload.blocksequence_counter = (UDS_UINT8)UDS_ZERO;
                }
                else
                {
                    /*Do Nothing*/
                }

                /*Get voltage status from application*/
                fl_voltage_status_u8 = UDSAPP_GET_VOLTAGE_STATUS();

                /*Check if the voltage is suitable for flashing*/
                if(fl_voltage_status_u8 == LOW_VOLTAGE)
                {
                    fl_status_u8 = UDS_NRC_VOLTAGE_TOO_LOW;
                }

                /*Check if the voltage is suitable for flashing*/
                else if(fl_voltage_status_u8 == HIGH_VOLTAGE)
                {
                    fl_status_u8 = UDS_NRC_VOLTAGE_TOO_HIGH;
                }
                else
                {
                    /*Do Nothing*/
                }
            }
            else
            {
                /* Wrong block sequence counter value */
                fl_status_u8 = UDS_NRC_WRONG_BLOCK_SEQ_COUNTER;
            }
        }
        else
        {
            /*Request sequence error*/
            fl_status_u8 = UDS_NRC_REQUEST_SEQUENCE_ERROR;
        }
    }
    if(fl_status_u8 == UDS_NO_ERROR)
    {
        UDS_SendRCRRP();
        /*Give callback to application layer*/
        APP_TRANSFER_DATA_CBK(l_RequestDownload.blocksequence_counter, &fl_pdiagdata_u8[1], (UDS_UINT16)(fl_datalength_u16 - (UDS_UINT16)1));
    }
    else
    {
          /*This function initializes all the global variable related to this service*/
        UdsApp_DownloadRequestInit();
        
        /*Send negative response*/
        UDS_SendNegativeResponse(fl_status_u8, UDS_TRNSFR_DATA_SID);
    }
}
#endif 

#if(UDS_TRNSFR_EXIT_SID_0x37_FEATURE == STD_ON)
/*
* @brief    This service routine is used to Exit the data transfer (0x37)
* @param    fl_pdiagdata_u8    - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_RequestTransferExit(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8 = UDS_NO_ERROR;

    /*Minimum length validity check */
    if((fl_pdiagdata_u8 == NULL) || (TRANSFER_EXIT_MIN_DLC < fl_datalength_u16))
    {
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }
    else
    {
        if((l_RequestDownload.Download_state != TRANSFER_EXIT_STATE) || (l_RequestDownload.Upload_state != TRANSFER_EXIT_STATE))
        {
            fl_status_u8 = UDS_NRC_REQUEST_SEQUENCE_ERROR;
        }
    }
    if(fl_status_u8 == UDS_NO_ERROR)
    {
        if(fl_datalength_u16 == (UDS_UINT16)UDS_ZERO)
        {
            /*Call application callback function with NULL Pointer if required */
            APP_TRANSFER_EXIT_CBK(NULL);
        }
        else
        {
            /*Application callback function*/
            APP_TRANSFER_EXIT_CBK(fl_pdiagdata_u8);
        }
    }
    else
    {
        /*This function initializes all the global variable related to this service*/
        UdsApp_DownloadRequestInit();
                
        /*Send negative response*/
        UDS_SendNegativeResponse(fl_status_u8, UDS_REQ_TRNSFR_EXIT_SID);
    }
}
#endif 

#if(UDS_TRNSFR_FILE_SID_0x38_FEATURE == STD_ON)
/*
* @brief    This service routine is used to Transfer the File from Server to Client (or) Vice-Versa. (0x38)
* @param    fl_pdiagdata_u8   - Data associated with the request
* @param    fl_datalength_u16  - Length of the data
* @return   None
*/
void UdsApp_RequestFileTransfer(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8 = UDS_NO_ERROR;
    UDS_UINT8 fl_ModeOfOperation_u8;
    UDS_UINT16 fl_FilePathNameLength_u16;

    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
    if((NULL == fl_pdiagdata_u8) || (fl_datalength_u16 < LENGTH_FOUR))
    {
        /*Trigger NRC 0x13 since invalid length*/
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }
    else
    {
        /*Request download service shall be processed only if security is unlocked*/
        if( UDS_SECURITY_LOCKED_STATE != l_security_access_status_u8)
        {
            /*Acquiring Mode Of Operation data value form the Request message buffer*/
            fl_ModeOfOperation_u8 = fl_pdiagdata_u8[BUFF_INDEX_ZERO];

            fl_FilePathNameLength_u16 = (UDS_UINT16)(((UDS_UINT16)fl_pdiagdata_u8[BUFF_INDEX_ONE] << (UDS_UINT8)UDS_SHIFT_EIGHT) |
                                          (UDS_UINT16)fl_pdiagdata_u8[BUFF_INDEX_TWO]);
            switch(fl_ModeOfOperation_u8)
            {
                case UDS_TRANSFER_ADD_FILE:
                    /*Note: FilPathAndName parameter to be calculated using the variable fl_FilePathNameLength_u16*/
                    /*The variable fl_status_u8 to be updated with UDS_NO_ERROR or NRC's respectively at the end of this switch-case*/
                    /*Vehicle manufacturer specific code to be implemented further*/
                    break;

                case UDS_TRANSFER_DELETE_FILE:
                    /*Note: FilPathAndName parameter to be calculated using the variable fl_FilePathNameLength_u16*/
                    /*The variable fl_status_u8 to be updated with UDS_NO_ERROR or NRC's respectively at the end of this switch-case*/
                    /*Vehicle manufacturer specific code to be implemented further*/
                    break;

                case UDS_TRANSFER_REPLACE_FILE:
                    /*Note: FilPathAndName parameter to be calculated using the variable fl_FilePathNameLength_u16*/
                    /*The variable fl_status_u8 to be updated with UDS_NO_ERROR or NRC's respectively at the end of this switch-case*/
                    /*Vehicle manufacturer specific code to be implemented further*/
                    break;

                case UDS_TRANSFER_READ_FILE:
                    /*Note: FilPathAndName parameter to be calculated using the variable fl_FilePathNameLength_u16*/
                    /*The variable fl_status_u8 to be updated with UDS_NO_ERROR or NRC's respectively at the end of this switch-case*/
                    /*Vehicle manufacturer specific code to be implemented further*/
                    break;

                case UDS_TRANSFER_READ_DIR_FILE:
                    /*Note: FilPathAndName parameter to be calculated using the variable fl_FilePathNameLength_u16*/
                    /*The variable fl_status_u8 to be updated with UDS_NO_ERROR or NRC's respectively at the end of this switch-case*/
                    /*Vehicle manufacturer specific code to be implemented further*/
                    break;

                default:
                    /*Trigger NRC 0x31 since Mode Of Operation value requested is out of Range*/
                    fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
                    break;
            }
        }
        else
        {
          /*Security is not unlocked NRC 0x33 should be triggered*/
          fl_status_u8 = UDS_NRC_SECURITY_ACCESS_DENIED;
        }
    }
    /*Check whether any NRCs received*/
    if(fl_status_u8 != UDS_NO_ERROR)
    {
        /*Send the NRC Triggered*/
        UDS_SendNegativeResponse(fl_status_u8, UDS_REQ_TRNSFR_FILE_SID);
    }
    else
    {
        /*Application call-back function*/
    }
}
#endif 

#if(UDS_TESTER_PRESENT_SID_0x3E_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the Tester present request (0x3E)
* @param    fl_pdiagdata_u8    - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_TesterPresent(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8;
    static UDS_UINT8 fl_response_buffer_u8[BUFF_INDEX_THREE];
    UDS_UINT8 fl_CurrentRequestType_u8;
    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
    if((NULL == fl_pdiagdata_u8) || (fl_datalength_u16 != (UDS_UINT16)UDS_TESTER_PRESENT_REQUEST_LENGTH))
    {
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }
    else
    {
        if(UDS_ZERO_SUB_FUNCTION == (fl_pdiagdata_u8[BUFF_INDEX_ZERO]& UDS_RESPONSE_SUPPRESS_MASK))
        {
            /*Restart S3 session timer */
            UDS_StartS3Timer();
            
            /*set status as no error if tester present request as valid*/
            fl_status_u8 = UDS_NO_ERROR;
        }
        else
        {
            /*Send NRC as subfunction Not supported for Tester Present Service*/
            fl_status_u8 = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
        }
        
    }
    
    /*send negative response if request is not valid*/
    if(fl_status_u8 != UDS_NO_ERROR)
    {
        UDS_SendNegativeResponse(fl_status_u8, UDS_TESTER_PRESENT_SID);
    }
    else
    {
        if ((UDS_UINT8)UDS_ZERO == UDS_INSPECT_POS_RSP_SUPPRESSED(fl_pdiagdata_u8))
        {
            /*response for tester present request*/
            fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_TESTER_PRESENT_POSITIVE_RESP;
            fl_response_buffer_u8[BUFF_INDEX_ONE] = fl_pdiagdata_u8[BUFF_INDEX_ZERO];

            /*send positive response if request is valid*/
            UDS_SendPositiveResponse(fl_response_buffer_u8, LENGTH_TWO);
        }
        else
        {
            fl_CurrentRequestType_u8 = UDS_GetCurrentRequestType();
            /*suppress response for a request*/
            UDS_SuppressPosResponse(fl_CurrentRequestType_u8);
        }
    }
}
#endif 

#if(UDS_CONTROL_DTC_SID_0x85_FEATURE == STD_ON)
/*
* @brief    Service for controlling DTC monitoring and setting. (0x85)
* @param    fl_pdiagdata_u8    - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_ControlDTCSetting(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8;
    UDS_UINT8 fl_subfunc_u8 = UDS_INIT;
    static UDS_UINT8 fl_response_buffer_u8[BUFF_INDEX_THREE];
    UDS_UINT8 fl_CurrentRequestType_u8;
    
    /* Trigger NRC 0x13 since invalid data length received in the request messag*/
    if((NULL == fl_pdiagdata_u8) || (fl_datalength_u16 != (UDS_UINT16)UDS_CONTROL_DTC_SETTING_REQUEST_LENGTH))
    {
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }
    else
    {
        /* removing the supressed positive response bit from the control DTC setting request*/
        fl_subfunc_u8 = (fl_pdiagdata_u8[BUFF_INDEX_ZERO]& UDS_RESPONSE_SUPPRESS_MASK);
        if (UDSAPP_CONTROL_DTC_CNC_CHECK_SID_85 == UDS_FALSE)
        {
            switch(fl_subfunc_u8)
            {
                case UDS_DTC_ON:
                                /*Enable the DTC Monitoring Setting*/
                                Uds_DtcApp_Enable_DTC_Logging_0x85();

                                /*set status as no error if valid request*/
                                fl_status_u8 = UDS_NO_ERROR;
                                break;

                case UDS_DTC_OFF:
                                /*Disable the DTC Monitoring Setting Status*/
                                Uds_DtcApp_Disable_DTC_Logging_0x85();

                                /*set status as no error if valid request*/
                                fl_status_u8 = UDS_NO_ERROR;
                                break;

                default:
                    /*Trigger NRC 0x12, since sub function not supported for control DTC setting request*/
                    fl_status_u8 = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
                    break;
            }
        }
        else
        {
            /*Trigger NRC 0x12, since conditions not correct for control DTC setting request*/
           fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;
        } 
    }

    /*send negative response if request is not valid*/
    if(fl_status_u8 != UDS_NO_ERROR)
    {
        UDS_SendNegativeResponse(fl_status_u8, UDS_CTRL_DTC_STTNG_SID);
    }
    else
    {
        if ((UDS_UINT8)UDS_ZERO == UDS_INSPECT_POS_RSP_SUPPRESSED(fl_pdiagdata_u8))
        {
            /*response for control DTC setting*/
            fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_CTRL_DTC_STTNG_POSITIVE_RESP;
            fl_response_buffer_u8[BUFF_INDEX_ONE] = fl_subfunc_u8;

            /*send positive response if request is valid*/
            UDS_SendPositiveResponse(fl_response_buffer_u8, LENGTH_THREE);
        }
        else
        {
            fl_CurrentRequestType_u8 = UDS_GetCurrentRequestType();
            /*suppress response for a request*/
            UDS_SuppressPosResponse(fl_CurrentRequestType_u8);
        }
    }
}
#endif

#if(UDS_SECURED_DATA_TRNSMSN_SID_0x84_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the Secured Data Transmission service (0x84)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_SecuredDataTransmission(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8 = UDS_NO_ERROR;
    static UDS_UINT8 fl_response_buffer_u8[LENGTH_ONE + MAX_DATA_RESP_RECORD_LENGTH_IN_BYTES];
    UDS_UINT16 fl_resplen_u16 = LENGTH_ONE;

    /*Minimum length validity check */
    if((fl_pdiagdata_u8 == NULL) || (fl_datalength_u16 < LENGTH_ONE))
    {
        /*Trigger NRC 0x13 since invalid length*/
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }
    /*Request proceeded with further checks as per positive response sequence*/
    else
    {
        /*Vehicle-Manufacturer specific implementations to be done*/
        /*Note: 1. "fl_status_u8" variable to be updated at the end of this else-case as UDS_NO_ERROR 
                    for positive response (or) NRC value as per the internal operation failure.
                2. "fl_response_buffer_u8" variable to be appended with "securityDataResponseRecord" 
                    in case of positive response.
                3. "fl_resplen_u16" variable to be updated .*/
    }

    /*Request proceedings status check to trigger response accrodingly*/
    if(fl_status_u8 != UDS_NO_ERROR)
    {
        /*Send negative response captured since status is updated with NRC*/
        UDS_SendNegativeResponse(fl_status_u8, UDS_SECURED_DATA_TRANSMISSION_SID);
    }
    else
    {
        /*Appending the Positive response value corresponding  to the SID in response buffer*/
        fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_SECURE_DATA_TRANSMSN_POSITIVE_RESP;

        /*Send positive response to the client*/
        UDS_SendPositiveResponse(fl_response_buffer_u8, fl_resplen_u16);
    }
}
#endif 

#if(UDS_RSP_ON_EVNT_SID_0x86_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the Response On Event service request (0x86)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_ResponseOnEvent(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8;
    UDS_UINT8 fl_subfunction_u8;
    UDS_UINT8 fl_storagebit_val_u8;
    UDS_UINT8 fl_storagestate_u8;
    static UDS_UINT8 fl_response_buffer_u8[MAX_BUFFER_LENGTH_IN_BYTES_SID_0X86];
    UDS_UINT16 fl_resplen_u16 = LENGTH_TWO;

    /*Minimum length validity check */
    if((fl_pdiagdata_u8 == NULL) || (fl_datalength_u16 < LENGTH_ONE))
    {
        /*Trigger NRC 0x13 since invalid length*/
        fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
    }
    /*Request proceeded with further checks as per positive response sequence*/
    else
    {
        /*Acquiring the subfunction value by masking bits 0 to 5*/
        fl_subfunction_u8 = (fl_pdiagdata_u8[BUFF_INDEX_ZERO] & 0x3Fu);

        /*Acquiring storage state bit's value by masking 6th bit*/
        fl_storagebit_val_u8 = ((fl_pdiagdata_u8[BUFF_INDEX_ZERO] & 0x40u) >> UDS_SHIFT_SIX);

        /*Check to decide the storage state based on 6th bit value of the sub-function*/
        if(fl_storagebit_val_u8 != UDS_ZERO)
        {
            /*Since 6th bit is "1", StorageState defined as to be Stored*/
            fl_storagestate_u8 = UDS_STORE_EVENT;
        }
        else
        {
            /*Since 6th bit is  "0", StorageState defined as NotToBeStored*/
            fl_storagestate_u8 = UDS_DO_NOT_STORE_EVENT;
        }
        
        switch(fl_subfunction_u8)
        {
            case UDS_STOP_RSP_ON_EVENT:
            /*Vehicle-Manufacturer specific implementations to be done*/
            /*Note: 1. "fl_status_u8" variable to be updated at the end of this else-case as UDS_NO_ERROR 
                    for positive response (or) NRC value as per the internal operation failure.
                    2. "fl_response_buffer_u8" variable to be appended with  positive response details.
                    3. "fl_resplen_u16" variable to be updated accordingly*/
            break;

            case UDS_ON_DTC_STATUS_CHANGE:
            /*Vehicle-Manufacturer specific implementations to be done*/
            /*Note: 1. "fl_status_u8" variable to be updated at the end of this else-case as UDS_NO_ERROR 
                    for positive response (or) NRC value as per the internal operation failure.
                    2. "fl_response_buffer_u8" variable to be appended with  positive response details.
                    3. "fl_resplen_u16" variable to be updated accordingly*/
            break;

            case UDS_ON_TIMER_INTERRUPT:
            /*Vehicle-Manufacturer specific implementations to be done*/
            /*Note: 1. "fl_status_u8" variable to be updated at the end of this else-case as UDS_NO_ERROR 
                    for positive response (or) NRC value as per the internal operation failure.
                    2. "fl_response_buffer_u8" variable to be appended with  positive response details.
                    3. "fl_resplen_u16" variable to be updated accordingly*/
            break;

            case UDS_ON_CHANGE_OF_DATA_IDENTIFIER:
            /*Vehicle-Manufacturer specific implementations to be done*/
            /*Note: 1. "fl_status_u8" variable to be updated at the end of this else-case as UDS_NO_ERROR 
                    for positive response (or) NRC value as per the internal operation failure.
                    2. "fl_response_buffer_u8" variable to be appended with  positive response details.
                    3. "fl_resplen_u16" variable to be updated accordingly*/
            break;

            case UDS_REPORT_ACTIVATED_EVENTS:
            /*Vehicle-Manufacturer specific implementations to be done*/
            /*Note: 1. "fl_status_u8" variable to be updated at the end of this else-case as UDS_NO_ERROR 
                    for positive response (or) NRC value as per the internal operation failure.
                    2. "fl_response_buffer_u8" variable to be appended with  positive response details.
                    3. "fl_resplen_u16" variable to be updated accordingly*/
            break;

            case UDS_START_RSP_ON_EVENT:
            /*Vehicle-Manufacturer specific implementations to be done*/
            /*Note: 1. "fl_status_u8" variable to be updated at the end of this else-case as UDS_NO_ERROR 
                    for positive response (or) NRC value as per the internal operation failure.
                    2. "fl_response_buffer_u8" variable to be appended with  positive response details.
                    3. "fl_resplen_u16" variable to be updated accordingly*/
            break;

            case UDS_CLEAR_RSP_ON_EVENT:
            /*Vehicle-Manufacturer specific implementations to be done*/
            /*Note: 1. "fl_status_u8" variable to be updated at the end of this else-case as UDS_NO_ERROR 
                    for positive response (or) NRC value as per the internal operation failure.
                    2. "fl_response_buffer_u8" variable to be appended with  positive response details.
                    3. "fl_resplen_u16" variable to be updated accordingly*/
            break;

            case UDS_ON_COMPARISON_OF_VALUES:
            /*Vehicle-Manufacturer specific implementations to be done*/
            /*Note: 1. "fl_status_u8" variable to be updated at the end of this else-case as UDS_NO_ERROR
                        for positive response (or) NRC value as per the internal operation failure.
                    2. "fl_response_buffer_u8" variable to be appended with  positive response details.
                    3. "fl_resplen_u16" variable to be updated accordingly*/
            break;

            default:
                /*Trigger NRC 0x12 since sub-function invalid & not supported by Server*/
                fl_status_u8 = UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
            break;
        }        
    }

    /*Request proceedings status check to trigger response accrodingly*/
    if(fl_status_u8 != UDS_NO_ERROR)
    {
        /*Send negative response captured since status is updated with NRC*/
        UDS_SendNegativeResponse(fl_status_u8, UDS_RESPONSE_ON_EVNT_SID);
    }
    else
    {
        /*Appending the Positive response value corresponding  to the SID in response buffer*/
        fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_RESP_ON_EVENT_POSITIVE_RESP;
        fl_response_buffer_u8[BUFF_INDEX_ONE] = fl_pdiagdata_u8[BUFF_INDEX_ZERO];

        /*Send positive response to the client*/
        UDS_SendPositiveResponse(fl_response_buffer_u8, fl_resplen_u16);
    }
}
#endif 

#if(UDS_READ_MEM_BY_ADDRSS_SID_0x23_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the Read Memory By Address service request (0x23)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_ReadMemoryByAddress(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8;
    static UDS_UINT8 fl_response_buffer_u8[RESPONSE_LENGTH_MAX];
    UDS_UINT16 fl_resplen_u16 = LENGTH_ONE;
    UDS_UINT8 fl_length_memorysize_u8;
    UDS_UINT8 fl_length_memoryaddress_u8;
    UDS_UINT8 fl_memory_address_index_u8;
    UDS_UINT8 fl_AddressShiftPositionLogic_u8;
    UDS_UINT32 fl_memoryaddress_u32 = (UDS_UINT32)(UDS_INIT);
    UDS_UINT32 fl_StartAddress_u32;
    UDS_UINT32 fl_EndAddress_u32;
    UDS_UINT8 fl_memorysize_index_u8;
    UDS_UINT8 fl_SizeShiftPositionLogic_u8;
    UDS_UINT32 fl_memorysize_u32 = (UDS_UINT32)(UDS_INIT);

 /* check the vehicle speed is zero or not */
    if(UDS_VEHICLE_SPEED() == UDS_ZERO)
    {     
        /*Acquiring memory address length by masking bits 0 to 3*/
        fl_length_memoryaddress_u8 = (fl_pdiagdata_u8[BUFF_INDEX_ZERO] & 0x0Fu);

        /*Acquiring memory address length by masking bits 4 to 7 & shifting to get value according to low nibble*/
        fl_length_memorysize_u8 = ((fl_pdiagdata_u8[BUFF_INDEX_ZERO] & 0xF0u) >> UDS_SHIFT_FOUR);

        /*Iteration for memory address acquisition*/
        for(fl_memory_address_index_u8 = 1u; \
            fl_memory_address_index_u8 <= fl_length_memoryaddress_u8; \
            fl_memory_address_index_u8++)
        {
            /*Address could be of any length(Vehicle-Manufacturer specific), so logically preparing the shift positions*/
            fl_AddressShiftPositionLogic_u8 = (UDS_SHIFT_EIGHT * (fl_length_memoryaddress_u8 - \
                                                (fl_memory_address_index_u8 )));
            /*Variable update with memory address received from client request*/
            fl_memoryaddress_u32 |= (UDS_UINT32)(((UDS_UINT32)fl_pdiagdata_u8[fl_memory_address_index_u8]) << fl_AddressShiftPositionLogic_u8);
        }

        /*Iteration for memory size acquisition*/
        for(fl_memorysize_index_u8 = fl_memory_address_index_u8; \
            fl_memorysize_index_u8 < (fl_memory_address_index_u8 + fl_length_memorysize_u8); \
            fl_memorysize_index_u8++)
        {
            /*Size could be of any length(Vehicle-Manufacturer specific), so logically preparing the shift positions*/
            fl_SizeShiftPositionLogic_u8 = (UDS_SHIFT_EIGHT * (fl_length_memorysize_u8 - \
                                            (fl_memorysize_index_u8 - fl_length_memoryaddress_u8)));
            /*Variable update with memory size received from client request*/
            fl_memorysize_u32 |= (UDS_UINT32)(((UDS_UINT32)fl_pdiagdata_u8[fl_memorysize_index_u8]) << fl_SizeShiftPositionLogic_u8);
        }

        /*Start address acquisition*/
        fl_StartAddress_u32 = fl_memoryaddress_u32;

        /*End address determination by making use of MemorySize*/
        fl_EndAddress_u32 = (fl_memoryaddress_u32 + fl_memorysize_u32 - LENGTH_ONE);

        /*Validity check for Memory address & Memory size requested by the client*/
        /*Note: Restricted memory area check for Request Out of Range not Done, since it is Vehicle-Manufacturer specific.
                To be added as per Vehicle-Manufacturer Micro details*/
        if((fl_StartAddress_u32 >= USER_MICRO_START_ADDRESS)  && \
        (fl_StartAddress_u32 <= USER_MICRO_END_ADDRESS) && \
        (fl_EndAddress_u32 <= USER_MICRO_END_ADDRESS) && \
        (fl_memorysize_u32 != 0u) && \
        (fl_memorysize_u32 < USER_MICRO_MEMORY_SIZE))
        {
                /*Check whether security is in unlocked state to proceed with the request*/
            if(l_security_access_status_u8 == UDS_SECURITY_UNLOCKED_STATE)
            {
                /*Minimum length validity check */
                if((fl_pdiagdata_u8 == NULL) || (fl_datalength_u16 < LENGTH_THREE))
                {
                /*Trigger NRC 0x13 since invalid length*/
                fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                }
                /*Request proceeded with further checks as per positive response sequence*/
                else
                {
                    if(UDSAPP_READ_MEM_BY_ADDRESS_CNC_CHECK_SID_23 == UDS_FALSE)
                    {
                        (void)UDSAPP_READ_MEM_SUPPORT(  fl_memoryaddress_u32, &fl_response_buffer_u8[BUFF_INDEX_ONE], fl_memorysize_u32);
                        /*Vehicle-Manufacturer specific implementations to be done*/
                        /*Note: 1. "fl_status_u8" variable to be updated at the end as UDS_NO_ERROR 
                                for positive response (or) NRC value as per the internal operation failure.
                            2. "fl_response_buffer_u8" variable to be appended with "dataRecord" that is read by memory address 
                                in case of positive response.
                            3. "fl_resplen_u16" variable to be updated*/
                        fl_status_u8 = UDS_NO_ERROR;
                        fl_resplen_u16 = (UDS_UINT16)(fl_resplen_u16 + (UDS_UINT16)fl_memorysize_u32);
                    }
                    else
                    {
                        /*Trigger NRC 0x22 since conditions not correct to proceed reading memory by address*/
                        fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;
                    }
                }
            }
            else
            {
                /*Trigger NRC 0x33 since Security access is in Locked state*/
                fl_status_u8 = UDS_NRC_SECURITY_ACCESS_DENIED;
            }
        }
        else
        {
            /*Trigger NRC 0x31 since memory address or memory size is invalid*/
            fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
        }   
        
            /*Request proceedings status check to trigger response accordingly*/
            if(fl_status_u8 != UDS_NO_ERROR)
            {
                /*Send negative response captured since status is updated with NRC*/
                UDS_SendNegativeResponse(fl_status_u8, UDS_READ_MEM_BY_ID_SID);
            }
            else
            {
                /*Appending the Positive response value corresponding  to the SID in response buffer*/
                fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_READ_MEM_BY_ADDRESS_POSITIVE_RESP;

                /*Send positive response to the client*/
                UDS_SendPositiveResponse(fl_response_buffer_u8, fl_resplen_u16);
            }

    }
    else
    {
        /* if vehicle speed is not zero then trigger 0X22 NRC */
        fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT; 
    }
}
#endif 

#if(UDS_WRITE_MEM_BY_ADDRSS_SID_0x3D_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the Write Memory By Address service request (0x3D)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_WriteMemoryByAddress(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16)
{
    UDS_UINT8 fl_status_u8;
    static UDS_UINT8 fl_response_buffer_u8[RESPONSE_LENGTH_MAX];
    UDS_UINT16 fl_resplen_u16 = LENGTH_ONE;
    UDS_UINT8 fl_length_memorysize_u8 = UDS_INIT;
    UDS_UINT8 fl_length_memoryaddress_u8 = UDS_INIT;
    UDS_UINT8 fl_memory_address_index_u8;
    UDS_UINT8 fl_AddressShiftPositionLogic_u8;
    UDS_UINT32 fl_memoryaddress_u32 =  (UDS_UINT32)(UDS_INIT);
    UDS_UINT32 fl_StartAddress_u32;
    UDS_UINT32 fl_EndAddress_u32;
    UDS_UINT8 fl_memorysize_index_u8;
    UDS_UINT8 fl_SizeShiftPositionLogic_u8;
    UDS_UINT32 fl_memorysize_u32 =  (UDS_UINT32)(UDS_INIT);
    UDS_UINT8 fl_write_status_u8 = UDS_FALSE;
    UDS_UINT8 fl_flash_write_status_u8 = UDS_FALSE;
    UDS_UINT8 fl_datarecord_index_u8 = UDS_INIT;
    UDS_UINT8 fl_index_u8;

    /* check the vehicle speed is zero or not */
    if(UDS_VEHICLE_SPEED() == UDS_ZERO)
    {
        /*Acquiring memory address length by masking bits 0 to 3*/
        fl_length_memoryaddress_u8 = (fl_pdiagdata_u8[BUFF_INDEX_ZERO] & 0x0Fu);

        /*Acquiring memory address length by masking bits 4 to 7 & shifting to get value according to low nibble*/
        fl_length_memorysize_u8 = ((fl_pdiagdata_u8[BUFF_INDEX_ZERO] & 0xF0u) >> UDS_SHIFT_FOUR);

        /*Iteration for memory address acquisition*/
        for(fl_memory_address_index_u8 = 1u; \
            fl_memory_address_index_u8 <= fl_length_memoryaddress_u8; \
            fl_memory_address_index_u8++)
        {
            /*Address could be of any length(Vehicle-Manufacturer specific), so logically preparing the shift positions*/
            fl_AddressShiftPositionLogic_u8 = (UDS_SHIFT_EIGHT * (fl_length_memoryaddress_u8 - \
                                                (fl_memory_address_index_u8 )));

            /*Variable update with memory address received from client request*/
            fl_memoryaddress_u32 |= (UDS_UINT32)(((UDS_UINT32)fl_pdiagdata_u8[fl_memory_address_index_u8]) << fl_AddressShiftPositionLogic_u8);
        }

        /*Iteration for memory size acquisition*/
        for(fl_memorysize_index_u8 = fl_memory_address_index_u8; \
            fl_memorysize_index_u8 < (fl_memory_address_index_u8 + fl_length_memorysize_u8); \
            fl_memorysize_index_u8++)
        {
            /*Size could be of any length(Vehicle-Manufacturer specific), so logically preparing the shift positions*/
            fl_SizeShiftPositionLogic_u8 = (UDS_SHIFT_EIGHT * (fl_length_memorysize_u8 - \
                                            (fl_memorysize_index_u8 - fl_length_memoryaddress_u8)));

            /*Variable update with memory size received from client request*/
            fl_memorysize_u32 |= (UDS_UINT32)(((UDS_UINT32)fl_pdiagdata_u8[fl_memorysize_index_u8]) << fl_SizeShiftPositionLogic_u8);
        }

            /*Start address acquisition*/
            fl_StartAddress_u32 = fl_memoryaddress_u32;

            /*End address determination by making use of MemorySize*/
            fl_EndAddress_u32 = (fl_memoryaddress_u32 + fl_memorysize_u32 - LENGTH_ONE);

            /*Acquiring data record index in the request frame*/
            fl_datarecord_index_u8 = fl_length_memoryaddress_u8 + fl_length_memorysize_u8 + LENGTH_ONE;

            /*Validity check for Memory address & Memory size requested by the client*/
            /*Note: Restricted memory area check for Request Out of Range not Done, since it is Vehicle-Manufacturer specific.
                    To be added as per Vehicle-Manufacturer Micro details*/
            if((fl_StartAddress_u32 >= USER_MICRO_START_ADDRESS)  && \
                (fl_StartAddress_u32 <= USER_MICRO_END_ADDRESS) && \
                (fl_EndAddress_u32 <= USER_MICRO_END_ADDRESS) && \
                (fl_memorysize_u32 != 0u) && \
                (fl_memorysize_u32 < USER_MICRO_MEMORY_SIZE))
            {
                /*Check whether conditions correct in proceeding with execution of the service request*/
                if(UDSAPP_WRITE_MEM_BY_ADDRESS_CNC_CHECK_SID_3D == UDS_FALSE)
                {
                        /*Check whether security is in unlocked state to proceed with the request*/
                    if(l_security_access_status_u8 == UDS_SECURITY_UNLOCKED_STATE)
                    {
                            /*Minimum length validity check */
                        if((fl_pdiagdata_u8 == NULL) || (fl_datalength_u16 < LENGTH_THREE))
                        {
                            /*Trigger NRC 0x13 since invalid length*/
                            fl_status_u8 = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
                        }
                        /*Request proceeded with further checks as per positive response sequence*/
                        else
                        {
                            /*Write Memory operation done*/
                            fl_write_status_u8 = UDSAPP_WRITE_MEM_SUPPORT(fl_memoryaddress_u32, &fl_pdiagdata_u8[fl_datarecord_index_u8], fl_memorysize_u32);

                            /*Check whether Write memory by address was completed successfully*/
                            if(fl_write_status_u8 == UDS_TRUE)
                            {
                                /*Update status as NO ERROR since write operation done succesfully*/
                                fl_status_u8 = UDS_NO_ERROR;   
                            }
                            else
                            {
                                /*Trigger NRC 0x72 since Write operation was not done due to general programming failure*/
                                fl_status_u8 = UDS_NRC_GENERAL_PROGRAMMING_FAILURE;
                            }
                        }

                    }
                    else
                    {
                    /*Trigger NRC 0x33 since Security access is in Locked state*/
                    fl_status_u8 = UDS_NRC_SECURITY_ACCESS_DENIED;
                    }
             
                }
                else
                {
                    /*Trigger NRC 0x31 since memory address or memory size is invalid*/
                    fl_status_u8 = UDS_NRC_REQUEST_OUT_OF_RANGE;
                }
            }         
                else
                {
                /* if vehicle speed is not zero then trigger 0X22 NRC */
                fl_status_u8 = UDS_NRC_CONDITIONS_NOT_CORRECT;  
                }
    }



    /*Request proceedings status check to trigger response accrodingly*/
    if(fl_status_u8 != UDS_NO_ERROR)
    {
        /*Send negative response captured since status is updated with NRC*/
        UDS_SendNegativeResponse(fl_status_u8, UDS_WRITE_MEM_BY_ID_SID);
    }
    else
    {
        /*Appending the Positive response value corresponding  to the SID in response buffer*/
        fl_response_buffer_u8[BUFF_INDEX_ZERO] = UDS_WRITE_MEM_BY_ADDRESS_POSITIVE_RESP;

        /*Positive response buffer filled with addressAndLengthFormatIdentifier*/
        fl_response_buffer_u8[BUFF_INDEX_ONE] = fl_pdiagdata_u8[BUFF_INDEX_ZERO];

        /*Appending response buffer with memory address & memory size as received in request frame*/
        for(fl_index_u8 = BUFF_INDEX_TWO; fl_index_u8 <= (fl_datarecord_index_u8); fl_index_u8++)
        {
            fl_response_buffer_u8[fl_index_u8] = fl_pdiagdata_u8[fl_index_u8 - LENGTH_ONE];
        }

        /*Response length value set to send to the client*/
        fl_resplen_u16 = (UDS_UINT16)(fl_resplen_u16 + ((UDS_UINT16)fl_length_memoryaddress_u8) + \
                                      fl_length_memorysize_u8 + ((UDS_UINT8)LENGTH_ONE));
        
        /*Send positive response to the client*/
        UDS_SendPositiveResponse(fl_response_buffer_u8, fl_resplen_u16);
    }
}
#endif 

/*
* @brief    This function is used to send asynchronous response
* @param    ErrorStaus - Error code from application
* @param    Dataptr -  reference pointer for the data to be transmitted
* @param    length - total length
* @return   None
*/
void UdsApp_Send_Async_Response(UDS_UINT8 ErrorStaus, const UDS_UINT8* Dataptr, UDS_UINT16 length)
{
    UDS_UINT8 fl_status_u8 = UDS_NO_ERROR;
    static UDS_UINT8 fl_response_buffer_u8[RESPONSE_LENGTH_MAX];
    UDS_UINT8 fl_current_sid_u8 = 0;
    UDS_UINT16 fl_resplen_u16 = (UDS_UINT16)0;
    UDS_UINT16 fl_loop_index_u16;
    const UDS_UINT8* fl_physical_buffer_u8;

    /*Get Physical buffer*/
    fl_physical_buffer_u8 = UDS_PhysicalGetBuffer(UDS_PRIMARYBUFF_LENGTHMAX);

    /*Current service that has been requested*/
    fl_current_sid_u8 = fl_physical_buffer_u8[0];

    /*If No Error from application proceed for positive response*/
    if(ErrorStaus == UDS_NO_ERROR)
    {
        switch(fl_current_sid_u8)
        {
            case UDS_ROUTINE_CTRL_SID:

            /*Updating the response buffer to be transmitted*/
            fl_response_buffer_u8[UDS_ZERO] = UDS_ROUTINE_CTRL_POSITIVE_RESP;
            fl_response_buffer_u8[UDS_ONE]  = fl_physical_buffer_u8[1] ;
            fl_resplen_u16 = (UDS_UINT16)UDS_TWO;
            break;

            case UDS_DWNLD_REQUEST_SID:

                /*Updating the response buffer to be transmitted*/
                fl_response_buffer_u8[UDS_ZERO] = UDS_DWNLD_REQUEST_POSITIVE_RESP;
                fl_response_buffer_u8[UDS_ONE] |= (UDS_UINT8)((UDS_UINT8)0xF0)&((UDS_UINT8)length << (UDS_UINT8)4) ;

                for(fl_loop_index_u16 = UDS_TWO; fl_loop_index_u16 < (UDS_UINT16)(length + (UDS_UINT16)UDS_TWO); fl_loop_index_u16++)
                {
                    fl_response_buffer_u8[fl_loop_index_u16] = *Dataptr;
                    Dataptr++;
                }
                fl_resplen_u16 = (UDS_UINT16)(length + (UDS_UINT16)UDS_TWO);

                /*Request download has been received*/
                l_RequestDownload.Download_state = REQUEST_DOWNLOAD_ACTIVE;

                break;

            case UDS_UPLOAD_REQUEST_SID:

                /*Updating the response buffer to be transmitted*/
                fl_response_buffer_u8[UDS_ZERO] = UDS_UPLOAD_REQUEST_POSITIVE_RESP;
                fl_response_buffer_u8[UDS_ONE] |= (UDS_UINT8)((UDS_UINT8)0xF0)&((UDS_UINT8)length << (UDS_UINT8)4) ;

                for(fl_loop_index_u16 = UDS_TWO; fl_loop_index_u16 < (UDS_UINT16)(length + (UDS_UINT16)UDS_TWO); fl_loop_index_u16++)
                {
                  fl_response_buffer_u8[fl_loop_index_u16] = *Dataptr;
                  Dataptr++;
                }
               fl_resplen_u16 = (UDS_UINT16)(length + (UDS_UINT16)UDS_TWO);

               break;

            case UDS_TRNSFR_DATA_SID:

                /*Updating the response buffer to be transmitted*/
                fl_response_buffer_u8[UDS_ZERO] = UDS_TRNSFR_DATA_POSITIVE_RESP;
                fl_response_buffer_u8[UDS_ONE] = fl_physical_buffer_u8[UDS_ONE];
                fl_resplen_u16 = (UDS_UINT16)UDS_TWO;

                /*When request upload is active*/
                if(Dataptr != NULL)
                {
                    /*Updating the response buffer with the data form application layer*/
                    for(fl_loop_index_u16 = UDS_ZERO; fl_loop_index_u16 < length; fl_loop_index_u16++)
                    {
                        fl_response_buffer_u8[fl_loop_index_u16 + (UDS_UINT16)2] = Dataptr[fl_loop_index_u16];
                    }
                    
                    fl_resplen_u16 += (UDS_UINT16)length;
                    
                }                
                break;

            case UDS_REQ_TRNSFR_EXIT_SID:

                /*Updating the response buffer to be transmitted*/
                fl_response_buffer_u8[UDS_ZERO] = UDS_REQ_TRNSFR_EXIT_POSITIVE_RESP;
                fl_resplen_u16 = (UDS_UINT16)1;

                if(Dataptr != NULL)
                {
                    for(fl_loop_index_u16 = UDS_ZERO; fl_loop_index_u16 < length; fl_loop_index_u16++)
                    {
                        fl_response_buffer_u8[fl_loop_index_u16 + (UDS_UINT16)1] = Dataptr[fl_loop_index_u16];
                    }
                    
                    fl_resplen_u16 += (UDS_UINT16)length;  
                }
                else
                {
                    /* Do Nothing */
                }
                break;

            default:

                /*Do Nothing*/
                break;
        }
        /*Send positive response to the client*/
        UDS_SendPositiveResponse(&fl_response_buffer_u8[0], fl_resplen_u16);
    }
    else
    {
        if((fl_current_sid_u8 == UDS_DWNLD_REQUEST_SID) || (fl_current_sid_u8 == UDS_TRNSFR_DATA_SID) || (fl_current_sid_u8 == UDS_REQ_TRNSFR_EXIT_SID))
        {
            UdsApp_DownloadRequestInit();
        }

        /*Get NRC for the application error code*/
        fl_status_u8 = UdsAppGetNRC(ErrorStaus);

        /*Send negative response captured since status is updated with NRC*/
        UDS_SendNegativeResponse(fl_status_u8, fl_current_sid_u8);
    }

}

#if(UDS_ECU_RESET_SID_0x11_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the ECU reset / power shut down after sending the response
* @param    None
* @return   None
*/
void UdsApp_EcuResetHandler(void)
{
    switch(l_ECUReset_Subfunction_u8)
    {
        case UDS_HARD_RESET:
        {
            /*ECU reset happen if valid request*/
            if(l_reset_pending_u8 == UDS_TRUE)
            {
                /*clear ECU reset flag*/
                l_reset_pending_u8 = UDS_FALSE;

                /*clear ECU shut down flag*/
                l_power_shutdown_enable_u8 = UDS_FALSE;
                l_power_shutdown_disable_u8 = UDS_FALSE;
                /*Ecu perform reset*/
                Application_HardECU_Reset();
            }
            else
            {
                /* do nothing */
            }
            break;
        }
        case UDS_KEY_OFF_ON_RESET:
        {
            /*ECU reset happen if valid request*/
            if(l_reset_pending_u8 == UDS_TRUE)
            {
                /*clear ECU reset flag*/
                l_reset_pending_u8 = UDS_FALSE;

                /*clear ECU shut down flag*/
                l_power_shutdown_enable_u8 = UDS_FALSE;
                l_power_shutdown_disable_u8 = UDS_FALSE;
                /*Ecu perform reset*/
                Application_KeyOffECU_Reset();
            }
            else
            {
                /* do nothing */
            }
            break;
        }
        case UDS_SOFT_RESET:
        {
            /*ECU reset happen if valid request*/
            if(l_reset_pending_u8 == UDS_TRUE)
            {
                /*clear ECU reset flag*/
                l_reset_pending_u8 = UDS_FALSE;

                /*clear ECU shut down flag*/
                l_power_shutdown_enable_u8 = UDS_FALSE;
                l_power_shutdown_disable_u8 = UDS_FALSE;
                /*Ecu perform reset*/
                Application_SoftECU_Reset();
            }
            else
            {
                /* do nothing */
            }
            break;
        }
        
        default :
        /*MISRA recommendation*/
        /*Do nothing*/
        break;
    } 
}
#endif 

/*
* @brief    This function is used to relock security whenever required
* @param    None
* @return   None
*/
void UdsApp_SecurityLock(void)
{
    l_security_access_status_u8 = UDS_SECURITY_LOCKED_STATE;
}

/**********************************************************************************************************************
                                P R I V A T E     F U N C T I O N S    D E F I N A T I O N S                             
***********************************************************************************************************************/

/*
* @brief    This function is used to initialize global variable related to
*           RequestDownload service            
* @param    None 
* @return   None
*/
void UdsApp_DownloadRequestInit(void)
{
    /*Clear all the variables to default value*/
    l_RequestDownload.blocksequence_counter = (UDS_UINT8)UDS_ZERO;
    l_RequestDownload.Download_address = (UDS_UINT32)UDS_ZERO;
    l_RequestDownload.Download_length = (UDS_UINT32)UDS_ZERO;
    l_RequestDownload.Download_state = REQUEST_DOWNLOAD_INACTIVE;
    l_RequestDownload.Downloaded_length = (UDS_UINT32)UDS_ZERO;
    l_RequestDownload.Upload_state = REQUEST_UPLOAD_INACTIVE;

}

/*
* @brief    This function is used to get NRC for the application error code
* @param    App_Error_Code
* @return   NRC
*/
UDS_UINT8 UdsAppGetNRC(UDS_UINT8 App_Error_Code)
{
    UDS_UINT8 fl_loop_index_u8;
    UDS_UINT8 fl_match_found_u8 = (UDS_UINT8)UDS_INIT;
    UDS_UINT8 fl_NRC_u8 = UDS_NRC_GENERAL_REJECT;

    /*This loop is to identify NRC for the application error code*/
    for(fl_loop_index_u8 = (UDS_UINT8)0; ((fl_loop_index_u8 < MAX_NOS_OF_APPLICATION_ERROR_CODE) && \
                                                (fl_match_found_u8 == (UDS_UINT8)UDS_INIT)); fl_loop_index_u8++)
    {
        if(App_Error_Code == l_Error_Code_list_st[fl_loop_index_u8].Application_ErrorCode)
        {
            /*Update this varibale as NRC as been identified*/
            fl_match_found_u8 = (UDS_UINT8)1;
            
            /*Copy the actual NRC to be returned*/
            fl_NRC_u8 = l_Error_Code_list_st[fl_loop_index_u8].UDS_NRC;
        }
    }
    return fl_NRC_u8;
}

/**********************************************************************************************************************/
/*                                              E N D   O F   S O F T W A R E                                         */
/**********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/**********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y                                       
 **********************************************************************************************************************/
/**********************************************************************************************************************
    REVISION NUMBER      : V1.3.2
    REVISION DATE        : 10-August-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Shared ROM - Write DID execution extended through UdsApp_Support file
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.3.1
    REVISION DATE        : 31-July-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Read DID service - CNC NRC managed as per Nvm's behaviour
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.3.0
    REVISION DATE        : 06-July-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Static Analysis done
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.2.0
    REVISION DATE        : 02-July-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Service implementation done & below Defects fixed:
                           1. Bootloader services implementation
                           2. Defect fix - Security access minimal length check & Read DID for both PA and FA
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.1.0
    REVISION DATE        : 27-May-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Comments updated & below Defects fixed:
                           1. Read DID Service - Wrong DID value appended in  response message.
                           2. Conditional compilation of Security Access feature for Read DID & ECU Reset Service done.
                           3. Non-Bootloader services (0x84, 0x86, 0x23, 0x3D) definitions implemented
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.9
    REVISION DATE        : 15-May-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Comments updated & below Defects fixed:
                           1. Pending implementations done as per ISO - 14229 for existing 11 services.
                           2. I/OControl Service - Removed wrongly appended NRC instead of 0x31 NRC.
                           3. ReadDataByIdentifier - Wrong DID value sent to client due to bit wise | operation.
                              Removed Set & assigned completely.
                           4. Write Data By Identifier - Reception of NRC 0x13 inappropriately due to data length check 
                              even  when SID not matched before the For-Loop is terminated.
                           5. Removed Read  DTC Service implementations & provided only skeleton to be implemented as 
                              per Vehicle-Manufacturer specifications.
                           6. Routine Control service - Modified Routine Handler functions implementation.
                           7. Security Relock done after transition from one Non-Default session to another 
                              Non-Default session.
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.8
    REVISION DATE        : 16-Apr-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Comments updated & below Defects fixed:
                           1. Security Relock on transition from Default to Non-Default session (0x27)
                           2. Current session update to Core Layer on session transition (0x10)
                           3. Removed extra data byte in Tester Present Response frame (0x3E)
                           4. Minimal length check for Write DID & Read DID request frames (0x22 & 0x2E)
                           5. Recheck of session supported in Security access removed since code found to be 
                              redundant (0x27)
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.7
    REVISION DATE        : 04-Apr-2020                                  
    CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)   
    DESCRIPTION          : Static Analysis Fixes done                                 
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.6
    REVISION DATE        : 02-Apr-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Bug fixing while testing  
------------------------------------------------------------------------------------------------------------------------                               
    REVISION NUMBER      : V1.0.5
    REVISION DATE        : 31-Mar-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Peer Review Comments Fixed                                 
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.4
    REVISION DATE        : 30-Mar-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Peer Review Comments Fixed                                 
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.3
    REVISION DATE        : 27-Mar-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Peer Review Comments Fixed                                 
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.2
    REVISION DATE        : 26-Mar-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Pending NRC implementations & Security Access logic with Algorithm done
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.1                                                           
    REVISION DATE        : 20-Mar-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Code Fixed after initial High Level testing                                 
------------------------------------------------------------------------------------------------------------------------
 *    REVISION NUMBER      : V1.0.0                                                                                   
 *    REVISION DATE        : 18/02/2020                                                                               
 *    CREATED / REVISED BY : Prasanth Selvam (prasanth.s@niyatainfotech.com)                                        
 *    DESCRIPTION          : Initial version                                                                          
 *--------------------------------------------------------------------------------------------------------------------
 **********************************************************************************************************************/
#endif /* ! UDSAPP_C */
