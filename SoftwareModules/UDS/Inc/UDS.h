/* @file UDS_H */
#ifndef UDS_H
#define UDS_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2011, 2016 Niyata Infotech Ptv. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Sharmili N (sharmili@niyatainfotech.com)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : UDS.h
*  Version                         : V1.0.7
*  Micros supported                : Micro Agnostic (Independant)  
*  Compilers supported             : XXXXX 
*  Platforms supported             : XXXXX                         
*  Description                     : This header file contains the APIs of UDS Core Layer
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include <stddef.h>
#include "Uds_Types.h"
#include "hal_stdtypes.h"
/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
/*
* @brief This macro is used to define Reset values of timers
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define UDS_TIMER_RESET_VALUE         0x00u

/*
* @brief This macro is used to define No error status
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define UDS_NOERROR               0x00u

/*
* @brief This macro is used to define init value of any variable
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define UDS_INIT                  0x00u

/*
* @brief This macro is used to define zero value for any variable
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define UDS_ZERO                  0u

/*
* @brief This macro is used to define NRC length
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define NEGATIVE_RESP_LENGTH      0x01u

/*
* @brief This macro is used to define NR ID
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define UDS_NEG_RESP_ID       0x7Fu

/*
* @brief This macro is used to define physical request indication value
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define UDS_PHYSICAL_REQ      (UDS_UINT8)(0x01u)

/*
* @brief This macro is used to define functional request indication value
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define UDS_FUNCTIONAL_REQ    (UDS_UINT8)(0x02u)
/*
* @brief This macro is used to define number of maximum request indication value
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define UDS_NUMREQ            (UDS_UINT8)(0x02u)

/*
* @brief This macro is used to define no service ID
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define UDS_NO_SERVICE_REQ    (UDS_UINT8)(0xFFu)

/*
* @brief This macro is used to define Invalid SID
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define UDS_INVALID_SID       (UDS_UINT8)(0xFFu)

/*  
* @brief: This macro is used to indicate the counter value as zero
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define UDS_COUNTER_ZERO             0u

/*  
* @brief: This macro is used to indicate the zeroth index of a buffer
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define BUFF_INDEX_ZERO              0u

/*  
* @brief: This macro is used to indicate the first index of a buffer
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define BUFF_INDEX_ONE               1u

/*  
* @brief: This macro is used to indicate the second index of a buffer
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define BUFF_INDEX_TWO               2u

/*  
* @brief: This macro is used to indicate the third index of a buffer
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define BUFF_INDEX_THREE             3u

/*  
* @brief: This macro is used to indicate the fourth index of a buffer
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define BUFF_INDEX_FOUR              4u

/*  
* @brief: This macro is used to indicate the fifth index of a buffer
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define BUFF_INDEX_FIVE              5u

/*  
* @brief: This macro is used to indicate the sixth index of a buffer
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define BUFF_INDEX_SIX               6U

/*  
* @brief: This macro is used to indicate the seventh index of a buffer
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define BUFF_INDEX_SEVEN             7u

/*  
* @brief: This macro is used to indicate the eighth index of a buffer
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define BUFF_INDEX_EIGHT             8u

/*  
* @brief: This macro is used to indicate the ninth index of a buffer
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define BUFF_INDEX_NINE             9u

/*  
* @brief: This macro is used to indicate VALUE ONE
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define UDS_ONE                         0x01u

/*  
* @brief: This macro is used to indicate VALUE TWO
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define UDS_TWO                         0x02u

/*  
* @brief: This macro is used to indicate EIGHT BIT SHIFT VALUE
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define UDS_SHIFT_EIGHT                  8u

/*  
* @brief: This macro is used to indicate SIXTEEN BIT SHIFT VALUE
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define UDS_SHIFT_SIXTEEN                16u

/*  
* @brief: This macro is used to indicate TWENTY FOUR BIT SHIFT VALUE
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define UDS_SHIFT_TWENTYFOUR             24u

/*  
* @brief: This macro is used to indicate TWENTY FOUR BIT SHIFT VALUE
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define UDS_SHIFT_SEVEN             7u

/*  
* @brief: This macro is used to indicate TWENTY FOUR BIT SHIFT VALUE
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define UDS_SHIFT_SIX             6U

/*  
* @brief: This macro is used to indicate TWENTY FOUR BIT SHIFT VALUE
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define UDS_SHIFT_FIVE             5U

/*  
* @brief: This macro is used to indicate TWENTY FOUR BIT SHIFT VALUE
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define UDS_SHIFT_FOUR             4U

/*  
* @brief: This macro is used to indicate TWENTY FOUR BIT SHIFT VALUE
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define UDS_SHIFT_THREE             3u

/*  
* @brief: This macro is used to indicate TWENTY FOUR BIT SHIFT VALUE
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define UDS_SHIFT_TWO             2U

/*  
* @brief: This macro is used to indicate TWENTY FOUR BIT SHIFT VALUE
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
*/
#define UDS_SHIFT_ONE             1u
/***********************************************************************************************************************
*                                         U D S  S E R V I C E   I D E N T I F I E R S                                       
***********************************************************************************************************************/

/*
* @brief This macro is used to define Service ID of Diagnostic Session
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if DiagSessionControl service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_DIAG_SESSION_CONTROL_SID          0x10u

/*
* @brief This macro is used to define Service ID of ECU Reset
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ECUReset service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_ECU_RESET_SID                     0x11u

/*  
* @brief: This macro is used to define Service ID of ClearDiagInfo
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ClearDiagInfo service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_CLEAR_DIAG_INFO_SID               0x14u

/*  
* @brief: This macro is used to define Service ID of ReadDTCInfo
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ReadDTCInfo service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_READ_DTCINFO_SID                  0x19u

/*  
* @brief: This macro is used to define Service ID of ReadDID
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ReadDID service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_READ_DATABYID_SID                 0x22u

/*  
* @brief: This macro is used to define Service ID of SecurityAccess
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if SecurityAccess service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_SECURITY_ACCESS_SID               0x27u

#define UDS_COMMUNICATION_CONTROL_SID         0x28u

/*  
* @brief: This macro is used to define Service ID of WriteDID
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if WriteDID service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_WRITE_DID_SID                     0x2Eu

/*  
* @brief: This macro is used to define Service ID of IOControlByIdentifier
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if IOControlByIdentifier service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_IO_CTRL_BYID_SID                  0x2Fu

/*  
* @brief: This macro is used to define Service ID of RoutineCtrl
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if RoutineCtrl service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_ROUTINE_CTRL_SID                  0x31u

/*  
* @brief: This macro is used to define Service ID of DownloadRequest
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if DownloadRequest service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_DWNLD_REQUEST_SID                 0x34u

/*  
* @brief: This macro is used to define Service ID of UploadRequest
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if UploadRequest service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_UPLOAD_REQUEST_SID                 0x35u

/*
* @brief: This macro is used to define Service ID of TransferData
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if TransferData service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_TRNSFR_DATA_SID                   0x36u

/*  
* @brief: This macro is used to define Service ID of RequestTransferExit
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if RequestTransferExit service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_REQ_TRNSFR_EXIT_SID               0x37u

/*  
* @brief: This macro is used to define Service ID of RequestFileTransfer
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if RequestFileTransfer Service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_REQ_TRNSFR_FILE_SID               0x38u

/*
* @brief: This macro is used to define Service ID of TesterPresent
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if TesterPresent service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_TESTER_PRESENT_SID                0x3Eu

/*  
* @brief: This macro is used to define Service ID of ControlDTCSetting
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ControlDTCSetting service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_CTRL_DTC_STTNG_SID                0X85u

/*  
* @brief: This macro is used to define Service ID of Secured Data Transmission
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if SecuredDataTransmission service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_SECURED_DATA_TRANSMISSION_SID                0X84u

/*  
* @brief: This macro is used to define Service ID of ResponseOnEvent
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ResponseOnEvent service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_RESPONSE_ON_EVNT_SID                0X86u
/*  
* @brief: This macro is used to define Service ID of ReadMemoryByIdentifier
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if ReadMemoryByAddress service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_READ_MEM_BY_ID_SID                0X23u

/*  
* @brief: This macro is used to define Service ID of WriteMemoryByIdentifier
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if WriteMemoryByAddress service enabled
  @Note:  Do not modify this macro value or name
*/
#define UDS_WRITE_MEM_BY_ID_SID                0X3Du

/*
* @brief: This macro is used to Get the Delay Timer's current value 
  @Unit:  milliseconds
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES 
  @Note:  Do not modify this macro value or name
*/
#define UDS_GET_DELAYTIMER_CNT()                    l_DelayTimer_Count_u32

/*  
* @brief: This macro is used to mention that no session check is required for a service request execution
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES 
  @Note:  Do not modify this macro value or name
*/
#define UDS_NO_SESSION_CHECK                                     0u

/*  
* @brief: This macro is used to mention the default session 
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES 
  @Note:  Do not modify this macro value or name
*/
#define UDS_DEFAULT_SESS                                         8u

/*  
* @brief: This macro is used to mention the programming session
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES 
  @Note:  Do not modify this macro value or name
*/
#define UDS_PROG_SESS                                            4u

/*  
* @brief: This macro is used to mention the extended session
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES 
  @Note:  Do not modify this macro value or name
*/
#define UDS_EXTND_SESS                                           2u

/*  
* @brief: This macro is used to mention the safety system diagnostic session
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES 
  @Note:  Do not modify this macro value or name
*/
#define UDS_SAFETY_SYS_DIAG_SESS                                 1u

/*  
* @brief: This macro is used to mention the visteon diagnostic session
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES 
  @Note:  Do not modify this macro value or name
*/
#define UDS_VISTEON_SYS_DIAG_SESS                                 6u

/*  
* @brief: This macro is used to define Length One
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define LENGTH_ONE                                      0x01u

/*  
* @brief: This macro is used to define Length Two
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define LENGTH_TWO                                      0x02u

/*  
* @brief: This macro is used to define Length Three
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define LENGTH_THREE                                    0x03u

/*  
* @brief: This macro is used to define Length Four
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define LENGTH_FOUR                                     0x04u

/*  
* @brief: This macro is used to define Length Five
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define LENGTH_FIVE                                     0x05u

/*  
* @brief: This macro is used to define Length Six
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define LENGTH_SIX                                      0x06u

/*  
* @brief: This macro is used to define Length Seven
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define LENGTH_SEVEN                                    0x07u

/*  
* @brief: This macro is used to define Length Eight
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define LENGTH_EIGHT                                    0x08u

/***********************************************************************************************************************
*                               S U B F U N C T I O N S   M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
/*
* @brief          : The below set of macros define the sub-functions of Diagnostic Session Control Service(0x10)
* @unit           : UINT8
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_DEFAULT_SESSION                                                 (UDS_UINT8)(0x01U)
#define UDS_PROGRAMMING_SESSION                                             (UDS_UINT8)(0x02U)
#define UDS_EXTENDED_DIAGNOSTIC_SESSION                                     (UDS_UINT8)(0x03U)
#define UDS_SAFETY_SYSTEM_DIAGNOSTIC_SESSION                                (UDS_UINT8)(0x04U)
#define UDS_VISTEON_SESSION                                                 (UDS_UINT8)(0x60U)  

/*
* @brief          : The below set of macros define the sub-functions of ECU Reset Service(0x11)
* @unit           : UINT8
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_HARD_RESET                                                      (UDS_UINT8)(0x01U)
#define UDS_KEY_OFF_ON_RESET                                                (UDS_UINT8)(0x02U)
#define UDS_SOFT_RESET                                                      (UDS_UINT8)(0x03U)
#define UDS_ENABLE_RAPID_POWER_SHUTDOWN                                     (UDS_UINT8)(0x04U)
#define UDS_DISABLE_RAPID_POWER_SHUTDOWN                                    (UDS_UINT8)(0x05U)

/*
* @brief          : The below set of macros define the sub-function's status of resident Diagnostic 
                    Trouble Code (DTC) Information (0x19)
* @unit           : UINT8
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_REPORT_NUMBER_OF_DTC_BY_STATUS_MASK                             (UDS_UINT8)(0x01U)
#define UDS_REPORT_DTC_BY_STATUS_MASK                                       (UDS_UINT8)(0x02U)
#define UDS_REPORT_DTC_SNAPSHOT_IDENTIFICATION                              (UDS_UINT8)(0x03U)
#define UDS_REPORT_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER                        (UDS_UINT8)(0x04U)
#define UDS_REPORT_DTC_STORED_DATA_BY_RECORD_NUMBER                         (UDS_UINT8)(0x05U)
#define UDS_REPORT_DTC_EXT_DATA_RECORD_BY_DTC_NUMBER                        (UDS_UINT8)(0x06U)
#define UDS_REPORT_NUMBER_OF_DTC_BY_SEVERITY_MASK_RECORD                    (UDS_UINT8)(0x07U)
#define UDS_REPORT_DTC_BY_SEVERITY_MASK                                     (UDS_UINT8)(0x08U)
#define UDS_REPORT_SEVERITY_INFORMATION_OF_DTC                              (UDS_UINT8)(0x09U)
#define UDS_REPORT_MIRROR_MEMORY_DTC_EXT_DATA_RECORD_BY_DTC_NUMBER          (UDS_UINT8)(0x10U)
#define UDS_REPORT_SUPPORTED_DTC                                            (UDS_UINT8)(0x0AU)
#define UDS_REPORT_FIRST_TEST_FAILED_DTC                                    (UDS_UINT8)(0x0BU)
#define UDS_REPORT_FIRST_CONFIRMED_DTC                                      (UDS_UINT8)(0x0CU)
#define UDS_REPORT_MOST_RECENT_TEST_FAILED_DTC                              (UDS_UINT8)(0x0DU)
#define UDS_REPORT_MOST_RECENT_CONFIRMED_DTC                                (UDS_UINT8)(0x0EU)
#define UDS_REPORT_MIRROR_MEMORY_DTC_BY_STATUS_MASK                         (UDS_UINT8)(0x0FU)
#define UDS_REPORT_NUMBER_OF_MIRROR_MEMORY_DTC_BY_STATUS_MASK               (UDS_UINT8)(0x11U)
#define UDS_REPORT_NUMBER_OF_EMISSIONS_OBD_DTC_BY_STATUS_MASK               (UDS_UINT8)(0x12U)
#define UDS_REPORT_EMISSIONS_OBD_DTC_BY_STATUS_MASK                         (UDS_UINT8)(0x13U)
#define UDS_REPORT_DTC_FAULT_DETECTION_COUNTER                              (UDS_UINT8)(0x14U)
#define UDS_REPORT_DTC_WITH_PERMANENT_STATUS                                (UDS_UINT8)(0x15U)
#define UDS_REPORT_DTC_EXT_DATA_RECORD_BY_RECORD_NUMBER                     (UDS_UINT8)(0x16U)
#define UDS_REPORT_USER_DEF_MEMORY_DTC_BY_STATUS_MASK                       (UDS_UINT8)(0x17U)
#define UDS_REPORT_USER_DEF_MEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER        (UDS_UINT8)(0x18U)
#define UDS_REPORT_USER_DEF_MEMORY_DTC_EXT_DATA_RECORD_BY_DTC_NUMBER        (UDS_UINT8)(0x19U)
#define UDS_REPORT_WWH_OBD_DTC_BY_MASK_RECORD                               (UDS_UINT8)(0x42U)
#define UDS_REPORT_WWHOBD_DTC_WITH_PERMANENT_STATUS                         (UDS_UINT8)(0x55U)

/*
* @brief          : The below set of macros define the sub-function of Security Access Service(0x27)
* @unit           : UINT8
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_REQUEST_SEED                                                    (UDS_UINT8)(0x01U)
#define UDS_SEND_KEY                                                        (UDS_UINT8)(0x02U)


/*
* @brief          : The below set of macros define the sub-function of Communication Control Service(0x28)
* @unit           : UINT8
* @resolution     : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_ENABLE_RX_TX                                                    (UDS_UINT8)(0x00U)
#define UDS_ENABLE_RX_DISABLE_TX                                            (UDS_UINT8)(0x01U)
#define UDS_DISABLE_RX_ENABLE_TX                                            (UDS_UINT8)(0x02U)
#define UDS_DISABLE_RX_TX                                                   (UDS_UINT8)(0x03U)



/*
* @brief          : The below set of macros define the sub-function of Input Output Control by 
                    Identifier Service(0x2F)
* @unit           : UINT8
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_RETURN_CONTROL_TO_ECU                                           (UDS_UINT8)(0x00U)
#define UDS_RESET_TO_DEFAULT                                                (UDS_UINT8)(0x01U)
#define UDS_FREEZE_CURRENT_STATE                                            (UDS_UINT8)(0x02U)
#define UDS_SHORT_TERM_ADJUSTMENT                                           (UDS_UINT8)(0x03U)

/*
* @brief          : The below set of macros define the sub-functions of Routine Control Service(0x31)
* @unit           : UINT8
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_START_ROUTINE                                                   (UDS_UINT8)(0x01U)
#define UDS_STOP_ROUTINE                                                    (UDS_UINT8)(0x02U)
#define UDS_REQUEST_ROUTINE_RESULTS                                         (UDS_UINT8)(0x03U)

/*
* @brief          : This macro defines the sub-functions of Tester Present Service (0x3E)
* @unit           : UINT8
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_ZERO_SUB_FUNCTION                                               (UDS_UINT8)(0x00U)

/*
* @brief          : The below set of macros define the sub-functions of ControlDTCSetting Service (0x85)
* @unit           : UINT8
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_DTC_ON                                                          (UDS_UINT8)(0x01U)
#define UDS_DTC_OFF                                                         (UDS_UINT8)(0x02U)

/*
* @brief          : The below set of macros define the eventType sub-functions of ResponseOnEvent Service (0x86)
* @unit           : UINT8
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_STOP_RSP_ON_EVENT                                              (UDS_UINT8)0x00U           
#define UDS_ON_DTC_STATUS_CHANGE                                           (UDS_UINT8)0x01U            
#define UDS_ON_TIMER_INTERRUPT                                             (UDS_UINT8)0x02U
#define UDS_ON_CHANGE_OF_DATA_IDENTIFIER                                   (UDS_UINT8)0x03U
#define UDS_REPORT_ACTIVATED_EVENTS                                        (UDS_UINT8)0x04U
#define UDS_START_RSP_ON_EVENT                                             (UDS_UINT8)0x05U
#define UDS_CLEAR_RSP_ON_EVENT                                             (UDS_UINT8)0x06U
#define UDS_ON_COMPARISON_OF_VALUES                                        (UDS_UINT8)0x07U

/*
* @brief          : The below set of macros define the ModeOfOperation for Upload Request Service (0x35)
* @unit           : UINT8
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_TRANSFER_ADD_FILE                                               (UDS_UINT8)0x01U
#define UDS_TRANSFER_DELETE_FILE                                            (UDS_UINT8)0x02U
#define UDS_TRANSFER_REPLACE_FILE                                           (UDS_UINT8)0x03U
#define UDS_TRANSFER_READ_FILE                                              (UDS_UINT8)0x04U
#define UDS_TRANSFER_READ_DIR_FILE                                          (UDS_UINT8)0x05U

/*
* @brief          : The below set of macros define the storageState sub-functions of ResponseOnEvent Service (0x86)
* @unit           : UINT8
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_DO_NOT_STORE_EVENT                                              (UDS_UINT8)0x00U           
#define UDS_STORE_EVENT                                                     (UDS_UINT8)0x01U            

/*
* @brief          : The below set of macros define the negative response code for UDS request. 
* @unit           : UINT8
* @resolution   : N/A
* @range          : N/A
* @validity check : N/A
* @required       : YES
*/
#define UDS_NO_ERROR                                                        (UDS_UINT8)(0x00)
#define UDS_NRC_GENERAL_REJECT                                              (UDS_UINT8)(0x10)
#define UDS_NRC_SERVICE_NOT_SUPPORTED                                       (UDS_UINT8)(0x11)
#define UDS_NRC_SUBFUNCTION_NOT_SUPPORTED                                   (UDS_UINT8)(0x12)
#define UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH                                (UDS_UINT8)(0x13)
#define UDS_NRC_RESPONSE_TOO_LONG                                           (UDS_UINT8)(0x14)
#define UDS_NRC_BUSY_REPEAT_REQUEST                                         (UDS_UINT8)(0x21)
#define UDS_NRC_CONDITIONS_NOT_CORRECT                                      (UDS_UINT8)(0x22)
#define UDS_NRC_ROUTINE_NOT_COMPLETED                                       (UDS_UINT8)(0x23)
#define UDS_NRC_REQUEST_SEQUENCE_ERROR                                      (UDS_UINT8)(0x24)
#define UDS_NRC_REQUEST_OUT_OF_RANGE                                        (UDS_UINT8)(0x31)
#define UDS_NRC_SECURITY_ACCESS_DENIED                                      (UDS_UINT8)(0x33)
#define UDS_NRC_INVALID_KEY                                                 (UDS_UINT8)(0x35)
#define UDS_NRC_EXCEEDED_NUMBER_ATTEMPTS                                    (UDS_UINT8)(0x36)
#define UDS_NRC_REQUIRED_TIME_DELAY_NOT_EXPIRED                             (UDS_UINT8)(0x37)
#define UDS_NRC_UPLOAD_DOWNLOAD_NOT_ACCEPTED                                (UDS_UINT8)(0x70)
#define UDS_NRC_TRANSFER_DATA_SUSPENDED                                     (UDS_UINT8)(0x71)
#define UDS_NRC_GENERAL_PROGRAMMING_FAILURE                                 (UDS_UINT8)(0x72)
#define UDS_NRC_WRONG_BLOCK_SEQ_COUNTER                                     (UDS_UINT8)(0x73)
#define UDS_NRC_REQUEST_CORRECTLY_RECEIVED_RESPONSE_PENDING                 (UDS_UINT8)(0x78)
#define UDS_NRC_SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION                 (UDS_UINT8)(0x7E)
#define UDS_NRC_SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION                     (UDS_UINT8)(0x7F)
#define UDS_NRC_VOLTAGE_TOO_HIGH                                            (UDS_UINT8)(0x92)
#define UDS_NRC_VOLTAGE_TOO_LOW                                             (UDS_UINT8)(0x93)

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef is used as Pointer to the post handler to be called after confirmation of 
 *           request transmission
 * @param    NULL
 **/
typedef void  (*Uds_PostHandler_t ) (void);

/*
 * @brief    This typedef is used to handle the main function pointers of requested UDS Service 
 * @param    DiagData - Buffer Pointer to the Diagnostic Data Received
 * @param    RespLen  - Length of the Response to be sent 
 **/
typedef void  (*Uds_MainFuncHandler_t ) (const UDS_UINT8 *DiagData, UDS_UINT16 RespLen);

/*
 * @brief    This structure is used as Function Handlers for services
 * @param    MainFuncHandler - Pointer to the main function handler for the requested service
 * @param    PostFuncHandler  - Pointer to the post handler to be called after confirmation of request transmission 
 **/
typedef struct
{
    Uds_MainFuncHandler_t   MainFuncHandler;
    Uds_PostHandler_t PostFuncHandler;
} UDS_FuncHandler_st;

/*
 * @brief    This structure is used to maintain the corresponding information required to handle each services
 * @param    RequestSID         - Requested Service ID
 * @param    SupportedSession   - Session in which the Service ID is supported
 *                                (@DiagSession_TypeDef -UDS_DEFAULT_SESS/UDS_PROG_SESS/UDS_EXTND_SESS/UDS_SAFETY_SYS_DIAG_SESS)
 * @param    ResponseSupport    - Flag to check whether Response to be sent
 * @param    RequestTypeSupported - Supported for Physical or Functional or Both (UDS_PHYSICAL_REQ, UDS_FUNCTIONAL_REQ)
 * @param    FuncHandler        - Function handler for the corresponding service ID
 **/
typedef struct
{
    UDS_UINT8 RequestSID;
    UDS_UINT8 SupportedSession;
    UDS_UINT8 ResponseSupport;
    UDS_UINT8 RequestTypeSupported;
    UDS_FuncHandler_st FuncHandler;
} UDS_ServiceInfo_st;


/*
 * @brief    This structure is used to maintain the Buffer controlling each service behaviour   
 * @param    CurrentSrvIdx  - Service ID index of the current request
 * @param    MakeResponse   - Flag to start the response framing
 * @param    Response_Txed  - Flag to indicate the confirmation of response txed 
 * @param    Tx_Ready       - Flag to start transmission, by calling TP
 * @param    Ind_Flag       - Flag to indicate new request received
 **/
typedef struct
{
    UDS_UINT8 CurrentSrvIdx;
    UDS_UINT8 MakeResponse;
    UDS_UINT8 Confirmation_Txed;
    UDS_UINT8 Tx_Ready;
    UDS_UINT8 Ind_Flag;
} UDS_BufferCtrl_st;



/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API will initialiaze the UDS Layer variables & session status
* @param    None
* @return   None
*/
void UDS_Init(void);

/*
* @brief    This API is used to handle the incoming Diagnostic requests with 
            Timing Parameters monitored internally
* @param    None
* @return   None
* @Note     This API should be executed periodically as a Time Task to catch all the incoming requests
*/
void UDS_Main(void);

/*
* @brief    This function processes the Negative response to be sent by the core layer
* @param    ErrorNRC - Error Code to be sent as Negative Response
* @param    ServiceID - Service Identifier for which the NRC is to be transmitted
* @return   NULL
*/
void UDS_SendNegativeResponse(UDS_UINT8 ErrorNRC, UDS_UINT8 ServiceID);

/*
* @brief    This function processes the Positive response to be sent by the core layer
* @param    DataBuffer - Data buffer carrying the response to be sent
* @param    RespLen - Length of the response to be sent(0 TO 0xFF)
* @return   NULL
*/
void UDS_SendPositiveResponse(UDS_UINT8 *DataBuffer, UDS_UINT16 RespLen);



/*
* @brief    This function indicates the core layer to start S3 timer
* @param    NULL
* @return   NULL
*/
void UDS_StartS3Timer(void);

/*
* @brief    This function is used to indicate the reception of physical request 
* @param    Result - TP layer message Rx status 
* @param    DataLen - Length of the data
* @return   NULL
*/
void UDS_PhysicalReq_Indication(uint8_t Result, UDS_UINT16 DataLen);

/*
* @brief    This function is used to indicate the reception of functional request
* @param    Result - TP layer message Rx status
* @param    DataLen - Length of the data
* @return   NULL
*/
void UDS_FunctionalReq_Indication(uint8_t Result,UDS_UINT16 DataLen);

/*
* @brief    This function is used to get the functional reception buffer from
* @param    DataLen - Length of the data
* @return   UDS_UINT8* - Address Diagnostic Buffer for receiving data from TP layer
*/
UDS_UINT8* UDS_FunctionalGetBuffer(UDS_UINT16 DataLen);

/*
* @brief    This function is used to get the physical reception buffer
* @param    DataLen - Length of the data
* @return   UDS_UINT8* - Address Diagnostic Buffer for receiving data from TP layer
*/
UDS_UINT8* UDS_PhysicalGetBuffer(UDS_UINT16 DataLen);

/*
* @brief    This service is used to Suppress Response activity
 * @param    BuffIndex - Index of the buffer to get the current request type
 * @return   NULL
 */
void UDS_SuppressPosResponse(UDS_UINT8 BuffIndex);

/*
* @brief    This function is used to get the current request type  
* @param    NULL
* @return   uint8_t - CurrentRequestType
*/
UDS_UINT8 UDS_GetCurrentRequestType(void);

/*
 * @brief    This function is used to get the buffer length of current request
 * @param    fl_RequestType_u8 - Physical/ Functional
 * @return   uint32_t - DLC of the request received
 */
UDS_UINT32 UDS_GetBufferLength(uint8_t fl_RequestType_u8);

/*
* @brief    This function is used to get the delay timer current value  
* @param    NULL
* @return   uint32_t - CurrentTimerValue
*/
UDS_UINT32 UDS_Get_DelayTimer_Value(void);

/*
* @brief    This function is used to start the delay timer 
* @param    NULL
* @return   NULL
*/
void UDS_Start_DelayTimer(void);

/*
* @brief    This function is used to get the current session of the server
* @param    NULL
* @return   uint8_t - Current session value
*/
UDS_UINT8 UDS_Get_Current_Session(void);

/*
* @brief    This function is used to get the current session of the server
* @param    fl_current_sess_u8 - Current session value
* @return   NULL
*/
void UDS_Update_Current_Session(UDS_UINT8 fl_current_sess_u8);

/*
 * @brief    This function is used to send the NRC for RequestCorrectlyReceivedResponsePending
 * @param    NULL
 * @return   NULL
 */
void UDS_SendRCRRP(void);


#define UDS_GET_IGN_POSITION()                                                Sys_Service_Get_Ignition_State();
#define UDS_GET_LOW_VOLTAGE_STATE()                                           Sys_Service_Get_Low_Voltage_State();
#define UDS_GET_HIGH_VOLTAGE_STATE()                                          Sys_Service_Get_High_Voltage_State();


void UDS_ROUTINE_HANDLER (void);
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
**********************************************************************************************************************
    REVISION NUMBER      : V1.0.7
    REVISION DATE        : 10-Aug-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Code alignment  done
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.6
    REVISION DATE        : 02-July-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Service implementation done & below Defects fixed:
                           1. Renamed UDS_GetPrimaryBufferLength as UDS_GetBufferLength to accommodate any type of
                           addressing's length
						   2. Moved Send_RCRRP to header to accomodate for Bootloader implementation
-----------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.5
    REVISION DATE        : 27-May-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : 1.  Header macros added for new services 0x84, 0x86, 0x23, 0x3D.
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.4
    REVISION DATE        : 16-Apr-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Defects Fixed & comments updated
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
    REVISION NUMBER      : V1.0.0                                                
    REVISION DATE        : 11-Feb-2020                              
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! UDS_H */
