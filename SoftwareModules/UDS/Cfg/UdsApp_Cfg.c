/* @file UDSAPP_CFG_C */
#ifndef UDSAPP_CFG_C
#define UDSAPP_CFG_C

/***********************************************************************************************************************
*   DISCLAIMER
*   Copyright © 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/**********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : UdsApp_Cfg.c
*  Generation Time                 : 18-10-2022 16:41:17
*  Tool Version                    : UDS_Configurator  2.2.1.0
*  Description                     : This file contains the configuration elements of UDS App Layer
*  @bug                            : N/A
*--------------------------------------------------------------------------------------------------------------------*/

/*********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*********************************************************************************************************************/

/**********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                            
***********************************************************************************************************************/
#include "UdsApp.h"
#include "UdsApp_Support.h"
#include "Uds.h"
/**********************************************************************************************************************
*                                          C O N F I G U R A T I O N  V A R I A B L E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/**************************************** READ DATA BY IDENTIFIER - 0x22 *************************************************/
#if(UDS_READ_DID_SID_0x22_FEATURE == STD_ON)
/*Eraase request RID*/
#define ERASE_REQUEST_RID           (UDS_UINT16)0XFF


/*
* @brief This variable is used to define the DID information list to read
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: Service ID - 0x22 (Read DID)
  @Note:  Do not modify this macro value or name
  @param: 1. DID - Data Identifier 
          2. DIDSize - Size of the DID in NVM block */
const UdsApp_Read_DID_st g_ReadDIDInfo_List_st[TOTAL_READ_DID_SUPPORTED]  = { \
{                              \
        PROGRAMING_DATE_DID,         \
        4u
    },                             \
    {                              \
        FINGERPRINT_DATA_DID,         \
        22u
    },                                  \
    {                              \
        PROGRAMMING_ATTEMPT_COUNTER_DID,\
        2u 
    },
    {                              \
        PROGRAMMING_SUCCESS_COUNTER_DID,\
        2u 
    },
    {                              \
        BOOTLOADER_VERSION_DID,\
        24u 
    }
};
#endif
/**************************************************************************************************************************/

/**************************************** WRITE DATA BY IDENTIFIER - 0x2E *************************************************/
#if(UDS_WRITE_DID_SID_0x2E_FEATURE == STD_ON)
/*
* @brief This variable is used to define the DID information list to write
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: Service ID - 0x2E (Write DID)
  @Note:  Do not modify this macro value or name
  @param: 1. DID - Data Identifier 
          2. DIDSize - Size of the DID in NVM block 
    Example:
    const UdsApp_Write_DID_st g_WriteDIDInfo_List_st[TOTAL_WRITE_DID_SUPPORTED]  = { \
         {                              \
             BMS_HW_PART_NUMBER,         \
             24u
         },                             \
         {                              \
             DCDC_HW_PART_NUMBER,         \
             24u
         },                             \
        };

*/
const UdsApp_Write_DID_st g_WriteDIDInfo_List_st[TOTAL_WRITE_DID_SUPPORTED]  = { \
    {                              \
        PROGRAMING_DATE_DID,         \
        4u
    },                             \
	 {                             \
        FINGERPRINT_DATA_DID,         \
        22u
	 },
    {                              \
        PROGRAMMING_ATTEMPT_COUNTER_DID,\
        2u 
    },
    {                              \
        PROGRAMMING_SUCCESS_COUNTER_DID,\
        2u 
    },
    {                              \
        BOOTLOADER_VERSION_DID,\
        24u 
    }

};
#endif
/***************************************************************************************************************************/

/********************************************* ROUTINE CONTROL - 0x31 ***************************************************/
#if(UDS_ROUTINE_CTRL_SID_0x31_FEATURE == STD_ON)
/*
* @brief This variable is used to define the Routine information list
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if RoutineControl service enabled
  @Note:  Do not modify this macro value or name
  @param    1. RID         - Requested routine ID
            2. RoutineState - Variable whiich specifies whether the Routine has been Uninitialized/Completed,
                              Started or Stopped */
UdsApp_Routine_Identifier_st g_Routine_List_st[MAX_NO_OF_ROUTINE] = { \

    {
    0XFF00 ,					\
    UDS_ROUTINE_UNINIT,
    NULL,
	NULL
  },
    {
    0X0202 ,					\
    UDS_ROUTINE_UNINIT,
    NULL,
	NULL
  },
    {
		0X0203 ,					\
		UDS_ROUTINE_UNINIT,
		&UDS_PROGRAM_PRECONDITION_CHECK,
		&UDS_PROGRAM_PRECONDITION_CHECK_RESULT
  },
    {
    0XFF01 ,					\
    UDS_ROUTINE_UNINIT,
    NULL,
	NULL
  }

};

/* 
 * @brief This variable is used to configure the Start Routine Function Handler
 * @param    Routine Identifier RID
 * @return   Routine execution status (UDS_TRUE - successful, UDS_FALSE - unsuccessful)
 * @applicability: Service ID - 0x31 (Routine Control)  
   eg: StartStopRoutineHandler_type Application_StartRoutine_Handler = Start_RoutineHandler();*
**/
StartStopRoutineHandler_type Application_StartRoutine_Handler = Sample_Routine_Start;

/* 
 * @brief This variable is used to configure the Start Routine Function Handler 
 * @param    Routine Identifier RID
 * @return   Routine execution status (UDS_TRUE - successful, UDS_FALSE - unsuccessful)
 * @applicability: Service ID - 0x31 (Routine Control)  
   eg: StartStopRoutineHandler_type Application_StopRoutine_Handler = Stop_RoutineHandler(); 
**/
StartStopRoutineHandler_type Application_StopRoutine_Handler = Sample_Routine_Stop;

/* 
 * @brief This variable is used to configure the Start Routine Function Handler
 * @param    RID - Routine Identifier
 * @param    RespDataBuff - Pointer to update the response buffer with routine results
 * @param    DataLen - Pointer to update the length  of the buffer after updating with Routine results
 * @return   Routine execution status (UDS_TRUE - successful, UDS_FALSE - unsuccessful)
 * @applicability: Service ID - 0x31 (Routine Control)  
   eg: GetResultRoutineHandler_type Application_GetResultRoutine_Handler = GetResult_RoutineHandler(); 
**/
GetResultRoutineHandler_type Application_GetResultRoutine_Handler = Sample_Routine_Result;
#endif
/*******************************************************************************************************************/

/*
 * @brief    This structure is used to map application error codes with UDS ISO NRC
 * @param    Application_ErrorCode - Error code from application which is equivalent to NRC
 * @param    UDS_NRC    - NRC (Negative response code)
 * Example:
 * const UdsApp_Error_Code_st l_Error_Code_list_st[MAX_NOS_OF_APPLICATION_ERROR_CODE] = {
  {
   (UDS_UINT8)0x01,                       \
   UDS_NRC_GENERAL_PROGRAMMING_FAILURE,        \
  },
  {
   (UDS_UINT8)0x03,                       \
   UDS_NRC_REQUEST_OUT_OF_RANGE,          \
  },
};
 **/
const UdsApp_Error_Code_st l_Error_Code_list_st[MAX_NOS_OF_APPLICATION_ERROR_CODE] = {
  {
   (UDS_UINT8)0x01,                       \
   UDS_NRC_GENERAL_PROGRAMMING_FAILURE,        \
  },
  {
   (UDS_UINT8)0x03,                       \
   UDS_NRC_REQUEST_OUT_OF_RANGE,          \
  },
  {
   (UDS_UINT8)0x05,
   UDS_NRC_UPLOAD_DOWNLOAD_NOT_ACCEPTED
  },
  {
   (UDS_UINT8)0x06,
   UDS_NRC_REQUEST_OUT_OF_RANGE
  },
  {
   (UDS_UINT8)0x04,                       \
   UDS_NRC_GENERAL_PROGRAMMING_FAILURE,        \
  }


};

/**************************************** INPUTOUTPUTCONTROLBYIDENTIFIER - 0x2F *************************************************/
#if(UDS_IO_CTRL_BY_ID_SID_0x2F_FEATURE == STD_OFF)

/*
* @brief This variable is used to define the DID information list to I/O control identifier
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: Service ID - 0x2F (I/O DID)
  @Note:  Do not modify this macro value or name
  @param: 1. DID - Data Identifier 
          2. DIDSize - Size of the DID in NVM block */
const UdsApp_IO_CONTROL_IDENTIFIER_DID_st g_IO_DIDInfo_List_st[TOTAL_IO_DID_SUPPORTED]  = { \
    {                              \
        TELLTALES_CONTROL,         \
        0X0Au,
    }
 

};
#endif

/********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N S                     
*********************************************************************************************************************/
/*********************************************** ECU RESET - 0x11 ***************************************************/
#if(UDS_ECU_RESET_SID_0x11_FEATURE == STD_ON)
/*
* @brief    This service is used to configure the ECU Hard reset
* @param    None
* @return   None
**/
void Application_HardECU_Reset(void)
{
    /*To be configured by the Integrator with corresponding API*/

}

/*
* @brief    This service is used to configure the ECU Soft reset
* @param    None
* @return   None
**/
void Application_SoftECU_Reset(void)
{
    /*To be configured by the Integrator with corresponding API*/
    NVIC_SystemReset();   
}

/*
* @brief    This service is used to configure the KeyOff reset
* @param    None
* @return   None
**/
void Application_KeyOffECU_Reset(void)
{
    /*To be configured by the Integrator with corresponding API*/

}

#endif
/*********************************************************************************************************************/

/**********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* ! UDSAPP_CFG_C */
