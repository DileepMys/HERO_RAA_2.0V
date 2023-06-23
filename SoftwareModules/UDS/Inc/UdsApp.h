/* @file UDSAPP_H */
#ifndef UDSAPP_H
#define UDSAPP_H
/*******************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2011, 2016 Niyata Infotech Ptv. Ltd. All rights reserved.                                           
*********************************************************************************************************************/

/*******************************************************************************************************************
* @author              Author : Sharmili N (sharmili@niyatainfotech.com)
*********************************************************************************************************************/

/*******************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                       
**--------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : UdsApp.h
*  Version                         : V1.0.7
*  Micros supported                : Micro Agnostic (Independant)  
*  Compilers supported             : xxxx 
*  Platforms supported             : xxxx
*  Description                     : This file contains the APIs of diagnostic application layer
*  @bug                         
--------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************************************************/

/*******************************************************************************************************************
*                                               I N C L U D E   F I L E S                                             
*********************************************************************************************************************/
#include "Uds_Types.h"
#include "hal_stdtypes.h"
#include "UdsApp_Cfg.h"
#include "UDS_Cfg.h"
#include "Swc_System_Service.h"
/*******************************************************************************************************************
*                                          M A C R O   D E F I N I T I O N S                                          
*********************************************************************************************************************/
/*
* @brief          : This macro is used to supress the response data.
* @unit           : UINT8
* @resolution     : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_RESPONSE_SUPPRESS_MASK                                          (UDS_UINT8)(0x7F) 

/*
* @brief          : The below macros are used to check the length of dignostic request.
* @unit           : UINT8
* @resolution     : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_DIAGNOSTIC_SESSION_CONTROL_REQUEST_LENGTH                       (UDS_UINT8)(0x01)
#define UDS_ECU_RESET_REQUEST_LENGTH                                        (UDS_UINT8)(0x01)
#define UDS_DOWNLOAD_REQUEST_LENGTH                                         (UDS_UINT8)(0x0A)
#define UDS_TRANSFER_EXIT_REQUEST_LENGTH                                    (UDS_UINT8)(0x00)
#define UDS_TESTER_PRESENT_REQUEST_LENGTH                                   (UDS_UINT8)(0x01)
#define UDS_READ_DTC_INFO_REQUEST_LENGTH                                    (UDS_UINT8)(0x02)
#define UDS_CONTROL_DTC_SETTING_REQUEST_LENGTH                              (UDS_UINT8)(0x01)
#define UDS_CLEAR_DTC_INFO_REQUEST_LENGTH                                   (UDS_UINT8)(0x03)
#define UDS_IO_CONTROL_BY_ID_REQUEST_LENGTH                                 (UDS_UINT8)(0x09)
#define UDS_COMMU_CONTROL_BY_ID_REQUEST_LENGTH                              (UDS_UINT8)(0x02)

/*
* @brief          : This macro defines the Positive response suppression 
* @unit           : UINT8
* @resolution     : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_INSPECT_POS_RSP_SUPPRESSED(x)   ((UDS_UINT8)(x[0] & \
                                            (UDS_UINT8)(~(UDS_UINT8)UDS_RESPONSE_SUPPRESS_MASK)))

/*
* @brief          : This macro defines the offset of DID
* @unit           : UINT8
* @resolution     : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_DID_OFFSET                                                      (UDS_UINT8)(0x00)

/*
* @brief          : This macro defines the offset of routine control
* @unit           : UINT8
* @resolution     : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_ROUTINE_OFFSET                                                  (UDS_UINT8)(0x01)

/*
* @brief          : These macros are set and check the status of security (service 0x27)
* @unit           : UINT8
* @resolution     : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_SECURITY_LOCKED_STATE                                           (UDS_UINT8)(0x00)
#define UDS_SECURITY_UNLOCKED_STATE                                         (UDS_UINT8)(0x01)

/*
* @brief          : These macros are used to validate the download request
* @unit           : UINT8
* @resolution     : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_APP_STARTING_ADDRESS                                            (UDS_UINT32)(0x00001000)
#define UDS_APP_ENDING_ADDRESS                                              (UDS_UINT8)(0x00000FFFF)

/*
* @brief          : This macro defines the data format identifier of download request
* @unit           : UINT8
* @resolution     : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_DOWNLOAD_REQUEST_NO_ENCRYPTION                                  (UDS_UINT8)(0x00)

/*
* @brief          : This macro defines the max buffer length request to tool
* @unit           : UINT8
* @resolution     : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_DOWNLOAD_REQUEST_MAX_BUFF_LENGTH                                (UDS_UINT16)(0x0101)

/*
* @brief          : These macros are used to set and check the status of download process
* @unit           : UINT8
* @resolution     : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_DOWNLOAD_REQUEST_NOT_COMPLETED                                  (UDS_UINT8)(0x00)
#define UDS_DOWNLOAD_REQUEST_COMPLETED                                      (UDS_UINT8)(0x01)
#define UDS_TRANSFER_DATA_COMPLETED                                         (UDS_UINT8)(0x02)

/*
* @brief          : The below macros defines the length of read DTC information request
* @unit           : UINT8
* @resolution     : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_REPORT_NUMBER_OF_DTC_BY_STATUS_MASK_LENGTH                      (UDS_UINT8)(0x02U)
#define UDS_REPORT_DTC_BY_STATUS_MASK_LENGTH                                (UDS_UINT8)(0x02U)
#define UDS_REPORT_DTC_SNAPSHOT_IDENTIFICATION_LENGTH                       (UDS_UINT8)(0x01U)
#define UDS_REPORT_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER_LENGTH                 (UDS_UINT8)(0x05U)
#define UDS_REPORT_DTC_STORED_DATA_BY_RECORD_NUMBER_LENGTH                  (UDS_UINT8)(0x02U)
#define UDS_REPORT_DTC_EXT_DATA_RECORD_BY_DTC_NUMBER_LENGTH                 (UDS_UINT8)(0x05U)
#define UDS_REPORT_NUMBER_OF_DTC_BY_SEVERITY_MASK_RECORD_LENGTH             (UDS_UINT8)(0x03U)
#define UDS_REPORT_DTC_BY_SEVERITY_MASK_LENGTH                              (UDS_UINT8)(0x03U)
#define UDS_REPORT_SEVERITY_INFORMATION_OF_DTC_LENGTH                       (UDS_UINT8)(0x04U)
#define UDS_REPORT_SUPPORTED_DTC_LENGTH                                     (UDS_UINT8)(0x01U)
#define UDS_REPORT_FIRST_TEST_FAILED_DTC_LENGTH                             (UDS_UINT8)(0x01U)
#define UDS_REPORT_FIRST_CONFIRMED_DTC_LENGTH                               (UDS_UINT8)(0x01U)
#define UDS_REPORT_MOST_RECENT_TEST_FAILED_DTC_LENGTH                       (UDS_UINT8)(0x01U)
#define UDS_REPORT_MOST_RECENT_CONFIRMED_DTC_LENGTH                         (UDS_UINT8)(0x01U)
#define UDS_REPORT_MIRROR_MEMORY_DTC_BY_STATUS_MASK_LENGTH                  (UDS_UINT8)(0x02U)
#define UDS_REPORT_MIRROR_MEMORY_DTC_EXT_DATA_RECORD_BY_DTC_NUMBER_LENGTH   (UDS_UINT8)(0x05U)
#define UDS_REPORT_NUMBER_OF_MIRROR_MEMORY_DTC_BY_STATUS_MASK_LENGTH        (UDS_UINT8)(0x02U)
#define UDS_REPORT_NUMBER_OF_EMISSIONS_OBD_DTC_BY_STATUS_MASK_LENGTH        (UDS_UINT8)(0x02U)
#define UDS_REPORT_EMISSIONS_OBD_DTC_BY_STATUS_MASK_LENGTH                  (UDS_UINT8)(0x02U)
#define UDS_REPORT_DTC_FAULT_DETECTION_COUNTER_LENGTH                       (UDS_UINT8)(0x01U)
#define UDS_REPORT_DTC_WITH_PERMANENT_STATUS_LENGTH                         (UDS_UINT8)(0x01U)
#define UDS_REPORT_DTC_EXT_DATA_RECORD_BY_RECORD_NUMBER_LENGTH              (UDS_UINT8)(0x02U)
#define UDS_REPORT_USER_DEF_MEMORY_DTC_BY_STATUS_MASK_LENGTH                (UDS_UINT8)(0x03U)
#define UDS_REPORT_USER_DEF_MEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER_LENGTH (UDS_UINT8)(0x06U)
#define UDS_REPORT_USER_DEF_MEMORY_DTC_EXT_DATA_RECORD_BY_DTC_NUMBER_LENGTH (UDS_UINT8)(0x06U)
#define UDS_REPORT_WWH_OBD_DTC_BY_MASK_RECORD_LENGTH                        (UDS_UINT8)(0x04U)
#define UDS_REPORT_WWHOBD_DTC_WITH_PERMANENT_STATUS_LENGTH                  (UDS_UINT8)(0x02U)
/*
* @brief          : The below macros defines the length of security seed
* @unit           : UINT8
* @resolution     : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_SECURITY_ACCESS_SEED_LENGTH                                     (UDS_UINT8)(0x01)
#define UDS_SECURITY_ACCESS_KEY_LEN                                         (UDS_UINT8)(0x05)

/*
* @brief          : The below macros defines the routine identifiers
* @unit           : UINT8
* @resolution     : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_ROUTINE_IDENTIFIER                                              (UDS_UINT16)(0x0123)



/*******************************************************************************************************************
*                               POSITIVE RESPONSE VALUE FOR EACH SERVICE                                            
*********************************************************************************************************************/

/*
* @brief This macro is used to define Positive response of Diagnostic Session
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if DiagSessionControl service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_DIAG_SESSION_CONTROL_POSITIVE_RESP          0x50u

/*
* @brief This macro is used to define Positive response of ECU Reset
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ECUReset service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_ECU_RESET_POSITIVE_RESP                      0x51u

/*  
* @brief: This macro is used to define Positive response of ClearDiagInfo
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ClearDiagInfo service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_CLEAR_DIAG_INFO_POSITIVE_RESP                0x54u

/*  
* @brief: This macro is used to define Positive response of ReadDTCInfo
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ReadDTCInfo service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_READ_DTCINFO_POSITIVE_RESP                   0x59u

/*  
* @brief: This macro is used to define Positive response of ReadDID
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ReadDID service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_READ_DATABYID_POSITIVE_RESP                  0x62u

/*  
* @brief: This macro is used to define Positive response of SecurityAccess
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if SecurityAccess service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_SECURITY_ACCESS_POSITIVE_RESP                0x67u

#define UDS_COMMU_CTRL_BYID_POSITIVE_RESP                0x68u

/*  
* @brief: This macro is used to define Positive response of WriteDID
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if WriteDID service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_WRITE_DID_POSITIVE_RESP                      0x6Eu

/*  
* @brief: This macro is used to define Positive response of IOControlByIdentifier
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if IOControlByIdentifier service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_IO_CTRL_BYID_POSITIVE_RESP                   0x6Fu

/*  
* @brief: This macro is used to define Positive response of RoutineCtrl
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if RoutineCtrl service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_ROUTINE_CTRL_POSITIVE_RESP                  0x71u

/*  
* @brief: This macro is used to define Positive response of DownloadRequest
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if DownloadRequest service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_DWNLD_REQUEST_POSITIVE_RESP                  0x74u

/*  
* @brief: This macro is used to define Positive response of UploadRequest
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if UploadRequest service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_UPLOAD_REQUEST_POSITIVE_RESP                  0x75u

/*
* @brief: This macro is used to define Positive response of TransferData
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if TransferData service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_TRNSFR_DATA_POSITIVE_RESP                   0x76u

/*  
* @brief: This macro is used to define Positive response of RequestTransferExit
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if RequestTransferExit service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_REQ_TRNSFR_EXIT_POSITIVE_RESP                0x77u

/*  
* @brief: This macro is used to define Positive response of TesterPresent
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if TesterPresent service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_TESTER_PRESENT_POSITIVE_RESP                0x7Eu

/*  
* @brief: This macro is used to define Positive response of ControlDTCSetting
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ControlDTCSetting service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_CTRL_DTC_STTNG_POSITIVE_RESP                 0XC5u

/*  
* @brief: This macro is used to define Positive response of SecuredDataTransmission
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ControlDTCSetting service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_SECURE_DATA_TRANSMSN_POSITIVE_RESP                 0XC4u

/*  
* @brief: This macro is used to define Positive response of SecuredDataTransmission
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ControlDTCSetting service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_RESP_ON_EVENT_POSITIVE_RESP                 0XC6u

/*  
* @brief: This macro is used to define Positive response of ReadMemoryByIdentifier
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ControlDTCSetting service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_READ_MEM_BY_ADDRESS_POSITIVE_RESP                 0X63u

/*  
* @brief: This macro is used to define Positive response of WriteMemoryByIdentifier
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ControlDTCSetting service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_WRITE_MEM_BY_ADDRESS_POSITIVE_RESP                 0X7Du

/*  
* @brief: This macro is used to define Format identifier according to ISO 14229-1
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define UDS_ISO_FORMAT_IDENTIFIER                       0x01u

/*  
* @brief: This macro is used to define that the Chosen Routine hasn't been Initialized at all
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define UDS_ROUTINE_UNINIT                   0u

/*  
* @brief: This macro is used to define that the Chosen Routine has been Initialized or started
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define UDS_ROUTINE_STARTED                           1u

/*  
* @brief: This macro is used to define that the chosen Routine has been Completed/ Stopped
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define UDS_ROUTINE_STOPPED                           2u

/*******************************************************************************************************************
*                                          P R I V A T E   D E C L A R A T I O N S                                    
*********************************************************************************************************************/
/*
 * @brief    This structure is used to maintain the corresponding information required to handle DID services to read
 * @param    DID         - Requested Data ID
 * @param    DID_size    - Size of the DID 
 **/
typedef struct
{
    UDS_UINT16 DID;
    UDS_UINT16 DID_size; 
}UdsApp_Read_DID_st;

/*
 * @brief    This structure is used to maintain the corresponding information required to handle DID services to write 
 * @param    DID         - Requested Data ID
 * @param    DID_size    - Size of the DID 
 **/
typedef struct
{
    UDS_UINT16 DID;
    UDS_UINT16 DID_size; 
}UdsApp_Write_DID_st;

/*
 * @brief    This structure is used to maintain the corresponding information required to handle Routine control
 * @param    RID         - Requested routine ID
 * @param    RoutineHandler    - Pointer to execute the routine
 * @param    RoutineState - Variable whiich specifies whether the Routine has been Uninitialized/Completed, 
 *                          Started or Stopped
 **/
typedef struct 
{
  UDS_UINT16 RID;
  UDS_UINT8 RoutineState;
  /*functionpointer-pointtofunction*/
  uint8_t(*start_fnptr)(void);
  uint8_t(*result_fnptr)(void);
}UdsApp_Routine_Identifier_st;

/*
 * @brief    This structure is used to maintain the corresponding information required to handle Read DTC services
 * @param    DTC         - Diagnostic Trouble Code
 * @param    DTC_Size    - Size of the DTC
 * @param    Block_Id    - Block ID in NvM
 **/
typedef struct
{
    UDS_UINT32 DTC;
    UDS_UINT8 DTC_Size;
    UDS_UINT8 Block_Id;
}DTC_Table_t;

/*
 * @brief    This structure is used to map application error codes with UDS ISO NRC
 * @param    Application_ErrorCode - Error code from application
 * @param    UDS_NRC    - NRC (Negative response code)
 **/
typedef struct
{
    UDS_UINT8 Application_ErrorCode;
    UDS_UINT8 UDS_NRC;
}UdsApp_Error_Code_st;


typedef struct
{
   UDS_UINT8 DID;
   UDS_UINT8 DID_SIZE;
}UdsApp_IO_CONTROL_IDENTIFIER_DID_st;

/*
 * @brief    This structure is used to map application error codes with UDS ISO NRC
 * @param    Application_ErrorCode - Error code from application which is equivalent to NRC
 * @param    UDS_NRC    - NRC (Negative response code)
 **/
const extern UdsApp_Error_Code_st l_Error_Code_list_st[MAX_NOS_OF_APPLICATION_ERROR_CODE];

/*
* @brief This variable is used to define the DID information list to read
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ReadDataByIdentifier service enabled
  @Note:  Do not modify this macro value or name
  @param: 1. DID - Data Identifier 
          2. DIDSize - Size of the DID in NVM block */
const extern UdsApp_Read_DID_st g_ReadDIDInfo_List_st[TOTAL_READ_DID_SUPPORTED];

/*
* @brief This variable is used to define the DID information list to write
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if WriteDataByIdentifier service enabled
  @Note:  Do not modify this macro value or name
  @param: 1. DID - Data Identifier 
          2. DIDSize - Size of the DID in NVM block
          3. Block_Id - Block ID in NvM */
const extern UdsApp_Write_DID_st g_WriteDIDInfo_List_st[TOTAL_WRITE_DID_SUPPORTED];

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
extern UdsApp_Routine_Identifier_st g_Routine_List_st[MAX_NO_OF_ROUTINE];

/*
* @brief This variable is used to define the I/O Control Identifier information list
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if RoutineControl service enabled
  @Note:  Do not modify this macro value or name
  @param    1. DID         - Requested routine ID
            2. DID_SIZE    - Variable whiich specifies whether the Routine has been Uninitialized/Completed, 
                              Started or Stopped */
extern const UdsApp_IO_CONTROL_IDENTIFIER_DID_st g_IO_DIDInfo_List_st[TOTAL_IO_DID_SUPPORTED];
/*******************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N S                     
*********************************************************************************************************************/
uint8_t GetCurrentSession(void);
/*
* @brief    This function is used to initialize the UDS Manager
* @param    None 
* @return   None
*/
void UdsApp_Init(void);

#if(UDS_DIAG_SESS_CTRL_SID_0x10_FEATURE == STD_ON)

/*
* @brief    This service is used to starts the requested diagnostic session as per the sub function (0x10)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_DiagnosticSessionControl(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_ECU_RESET_SID_0x11_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the ECU Reset request (0x11)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_EcuReset(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_CLEAR_DTC_SID_0x14_FEATURE == STD_ON)
/*
* @brief    This service is used to clear diagnostic information in one or multiple memory (0x14)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_ClearDiagnosticInformation(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_READ_DTC_SID_0x19_FEATURE == STD_ON)
/*
* @brief    This service is used to read the status of resident Diagnostic Trouble Code (DTC) information (0x19)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_ReadDTCInformation(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_READ_DID_SID_0x22_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the UDS Read DID request (0x22)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_ReadDataByIdentifier(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_WRITE_DID_SID_0x2E_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the UDS Write DID request (0x2E)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_WriteDataByIdentifier(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_SECURITY_ACCESS_SID_0x27_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the UDS Security Access request (0x27)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_SecurityAccess(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_COMMUNICATION_CTRL_SID_0x28_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the UDS Communication Control request (0x27)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_CommunicationControl(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);

#endif

#if(UDS_IO_CTRL_BY_ID_SID_0x2F_FEATURE == STD_OFF)
/*
* @brief    This service is used to substitute a value for an input signal, 
*           and/or force control to a value for an output signal (0x2F)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_InputOutputControlByIdentifier(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_ROUTINE_CTRL_SID_0x31_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the UDS Routine Control request (0x31)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_RoutineControl(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_DWNLD_REQ_SID_0x34_FEATURE == STD_ON)
/*
* @brief    This service routine is used to downloading the data to FLash/NVM (0x34)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_RequestDownload(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_UPLD_REQ_SID_0x35_FEATURE == STD_ON)
/*
* @brief    This service routine is used to uploading the data from Server to Client(0x35)
* @param    fl_pdiagdata_u8   - Data associated with the request
* @param    fl_datalength_u16  - Length of the data
* @return   None
*/
void UdsApp_RequestUpload(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_TRNSFR_DATA_SID_0x36_FEATURE == STD_ON)
/*
* @brief    This service routine is used to Transfer the data to FLash/NVM. (0x36)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_TransferData(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_TRNSFR_EXIT_SID_0x37_FEATURE == STD_ON)
/*
* @brief    This service routine is used to Exit the data transfer (0x37)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_RequestTransferExit(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_TRNSFR_EXIT_SID_0x37_FEATURE == STD_ON)
/*
* @brief    This service routine is used to Transfer the File from Server to Client (or) Vice-Versa. (0x38)
* @param    fl_pdiagdata_u8   - Data associated with the request
* @param    fl_datalength_u16  - Length of the data
* @return   None
*/
void UdsApp_RequestFileTransfer(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_TESTER_PRESENT_SID_0x3E_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the Tester present request (0x3E)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_TesterPresent(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_CONTROL_DTC_SID_0x85_FEATURE == STD_ON)
/*
* @brief    This service is used to enable or disable DTC setting (0x85)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_ControlDTCSetting(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_SECURED_DATA_TRNSMSN_SID_0x84_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the Secured Data Transmission service (0x84)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_SecuredDataTransmission(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_RSP_ON_EVNT_SID_0x86_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the Response On Event service request (0x86)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_ResponseOnEvent(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_READ_MEM_BY_ADDRSS_SID_0x23_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the Read Memory By Address service request (0x23)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_ReadMemoryByAddress(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_WRITE_MEM_BY_ADDRSS_SID_0x3D_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the Write Memory By Address service request (0x3D)
* @param    fl_pdiagdata_u8   - Data associated with the request 
* @param    fl_datalength_u16  - Length of the data 
* @return   None
*/
void UdsApp_WriteMemoryByAddress(const UDS_UINT8 *fl_pdiagdata_u8, UDS_UINT16 fl_datalength_u16);
#endif

#if(UDS_ECU_RESET_SID_0x11_FEATURE == STD_ON)
/*
* @brief    This service is used to handle the ECU reset / power shut down after sending the response
* @param    None
* @return   None
*/
void UdsApp_EcuResetHandler(void);
#endif

/*
* @brief    This function is used to relock security whenever required
* @param    None
* @return   None
*/
void UdsApp_SecurityLock(void);

/*
* @brief    This function is used to send asynchronous response
* @param    ErrorStaus - Error code from application
* @param    Dataptr -  reference pointer for the data to be transmitted
* @param    length - total length
* @return   None
*/
void UdsApp_Send_Async_Response(UDS_UINT8 ErrorStaus, const UDS_UINT8* Dataptr, UDS_UINT16 length);





/********************************************************************************************************************/
/*                                              E N D   O F   S O F T W A R E                                         */
/********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y                                       
 **********************************************************************************************************************/
/********************************************************************************************************************
    REVISION NUMBER      : V1.0.7
    REVISION DATE        : 30-July-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Pre-Processing compilation macros provided for each service enabling.
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.6
    REVISION DATE        : 27-May-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : API declaration done for new services 0x84, 0x86, 0x23, 0x3D.
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.5
    REVISION DATE        : 16-Apr-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Comments updated & UdsApp_SecurityLock API added for defect #.
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.5
    REVISION DATE        : 04-Apr-2020                                  
    CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)   
    DESCRIPTION          : Static Analysis Fixes done                                 
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.4
    REVISION DATE        : 31-Mar-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Peer Review Comments Fixed                                 
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.3
    REVISION DATE        : 30-Mar-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Peer Review Comments Fixed                                 
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.2                                                           
    REVISION DATE        : 27-Mar-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Peer Review Comments Fixed                                 
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
#endif /* ! UDSAPP_H */
