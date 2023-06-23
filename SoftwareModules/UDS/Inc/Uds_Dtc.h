/* @file UDS_DTC_H */
#ifndef UDS_DTC_H
#define UDS_DTC_H

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
*  File name                       : Uds_Dtc.h
*  Version                         : V1.0.1
*  Micros supported                : Micro Agnostic (Independent)
*  Compilers supported             : XXXXX
*  Platforms supported             : XXXXX 
*  Description                     : This header file contains the declarations of Uds_Dtc Core Layer
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
#include <stdint.h>
#include "Uds_Dtc_Cfg.h"
/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
/**
* @brief This macro is used to define the All DTC Group Value
* @Unit: N/A
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define ALL_DTC_GRP             0xFFFFFFu

/**
* @brief This macro is used to define Nvm Block's size for each DTC
* @Unit: N/A
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define DTC_NVM_BLOCK_LNGTH             (uint8_t)27

/**
* @brief This macro is used to define DTC ISO 14229-1 format identifer
* @Unit: N/A
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define UDS_DTC_ISO_14229_1_DTC_FORMAT             (uint8_t)0x01

/**
* @brief This macro is used to define the 0th Status bit - testFailed
* @Unit: N/A
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define UDS_DTC_STATUS_BIT_TF_0TH               (uint8_t)(0x01)

/**
* @brief This macro is used to define the 1st Status bit - testFailedThisOperationCycle
* @Unit: N/A
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define UDS_DTC_STATUS_BIT_TFTOC_1ST            (uint8_t)(0x02)

/**
* @brief This macro is used to define the 2nd Status bit - pendingDTC
* @Unit: N/A
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define UDS_DTC_STATUS_BIT_PDTC_2ND             (uint8_t)(0x04)

/**
* @brief This macro is used to define the 3rd Status bit - confirmedDTC
* @Unit: N/A
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define UDS_DTC_STATUS_BIT_CDTC_3RD             (uint8_t)(0x08)

/**
* @brief This macro is used to define the 4th Status bit - testNotCompletedSinceLastClear
* @Unit: N/A
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define UDS_DTC_STATUS_BIT_TNCSLC_4TH           (uint8_t)(0x10)

/**
* @brief This macro is used to define the 5th Status bit - testFailedSinceLastClear
* @Unit: N/A
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define UDS_DTC_STATUS_BIT_TFSLC_5TH            (uint8_t)(0x20)

/**
* @brief This macro is used to define the 6th Status bit - testNotCompletedThisOperationCycle
* @Unit: N/A
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define UDS_DTC_STATUS_BIT_TNCTOC_6TH           (uint8_t)(0x40)

/**
* @brief This macro is used to define the 7th Status bit - warningIndicatorRequested
* @Unit: N/A
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define UDS_DTC_STATUS_BIT_WIR_7TH              (uint8_t)(0x80)

/**
* @brief This macro is used to increment the counters and buffer index by ONE as resolution
* @Unit: N/A
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define UDS_DTC_INCREMENT_BY_ONE                    (uint8_t)1

/**
* @brief This macro is used to clear or assign DTC related data with Zero as its value
* @Unit: N/A
* @Resolution: N/A 
* @Range: N/A
* @Applicability: YES
* @Note: Do not modify this macro value
*/
#define UDS_DTC_ZERO                                (uint8_t)0
/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/
/*
 * @brief    This typedef enum is used to define the confirmedDTC bit's confirmation stages
 * @param    UDS_DTC_INITIAL_MONITOR - Monitoring initally for FDC threshold
 * @param    UDS_DTC_AGING_MONITOR - Monitoring the Aging of confirmedDTC
 **/
typedef enum
{
    UDS_DTC_INITIAL_MONITOR = (uint8_t)0,
    UDS_DTC_AGING_MONITOR,
}Uds_Dtc_ConfirmedMonitor;

/*
 * @brief    This typedef enum is used to define the error codes of Clearing DTC
 * @param    DTC_NO_ERROR - No error occurred while clearing DTC
 * @param    DTC_GRP_NOT_FOUND - The requested Group of DTC is not found in server
 * @param    DTC_NOT_CLEARABLE - Due to internal error, DTC not cleared
 **/
typedef enum
{
    DTC_NO_ERROR = (uint8_t)0, 
    DTC_GRP_NOT_FOUND,
    DTC_NOT_CLEARABLE
}Clear_Dtc_ErrorCode;



/*
 * @brief    This structure is used to define the configurable functional structure's type
 * @param    l_Uds_Dtc_StatusByte_u8        - Status byte of DTC
 * @param    l_confirmStage              - confirmation stage of reported DTC
 * @param    l_operationCycleCounter_u8     - Operation Cycle Counter value
 * @param    l_Dtc_Aging_DownCounter_u8     - Aging Down Counter value
 * @param    l_Dtc_FaultDetectionCounter_u8 - Fault Detection Counter
 * @param    l_lastOperationCycle_u8        - Last Operation Cycle Value
 * @param    l_currentOperationCycle_u8     - Current Operation Cycle Value
 * @param    l_Uds_Dtc_Local_SS_u8             - Local Snapshot Data Record
 * @param    l_Uds_Dtc_Global_SS_u8            - Global Snapshot Data Record
 * @param    l_Uds_MC_u8                    - Monitoring Cycle value
 **/
typedef struct 
{
    uint8_t l_Uds_Dtc_StatusByte_u8;
    Uds_Dtc_ConfirmedMonitor l_confirmStage;
    uint8_t l_operationCycleCounter_u8;
    uint8_t l_Dtc_Aging_DownCounter_u8;
    uint8_t l_Dtc_FaultDetectionCounter_u8;
    uint8_t l_lastOperationCycle_u8;
    uint8_t l_currentOperationCycle_u8;
    uint8_t l_Uds_Dtc_Local_SS_u8[UDS_DTC_LOCAL_SS_SIZE];
    uint8_t l_Uds_Dtc_Global_SS_u8[UDS_DTC_GLOBAL_SS_SIZE];
}Uds_Dtc_Record_Struct;

/***********************************************************************************************************************
*                            E X T E R N A L   V A R I A B L E S    D E C L A R A T I O N                  
***********************************************************************************************************************/
/*
 * @brief: This variable is used to store the DTC record details
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: YES 
 */
extern Uds_Dtc_Record_Struct g_Uds_Dtc_NvmRecord_St[UDS_DTC_MAX_CFG];

/*
 * @brief: This variable is used to store the Firsst Power Up status details in Nvm
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: YES 
 */
extern uint8_t g_Uds_Dtc_FirstPowerUp_NvmByte_u8;  
/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to initialize DTC core layer
* @param    NULL
* @return   NULL
*/
void Uds_Dtc_Init(void);

/*
* @brief    This API is used to deinitialize the DTC core layer
* @param    
* @return   
*/
void Uds_Dtc_DeInit(void);

/*
* @brief    This API is used to execute the periodic execution of status bit checks and updates for each DTC
* @param    NULL
* @return   NULL
*/
void Uds_Dtc_MainFunction(void);

/*
* @brief    This API is used to Clear the Diagnostic information when requested by the Client through service 0x14
* @param    fl_DTCVal_u32 - 3 byte value of DTC Group
* @return   Clear_Dtc_ErrorCode - Error codes based on the execution of Clearing DTC information
            DTC_NO_ERROR - No error occurred while clearing DTC
            DTC_GRP_NOT_FOUND - The requested Group of DTC is not found in server
            DTC_NOT_CLEARABLE - Due to internal error, DTC not cleared
*/
Clear_Dtc_ErrorCode Uds_Dtc_Clear_Diagnostics_Info(uint32_t fl_DTCVal_u32);

/*
* @brief    This API is used to Read the Diagnostic information when requested by the Client through service 0x19
* @param    fl_pdiagdata_u8 - Data associated with the 0x19 request 
* @param    fl_DataPtr_u8 - Pointer to return with updated data read from DTC layer to UdsApp layer
* @param    fl_DLC_u8 - Length of the Data returned through pointer above
* @return   NULL
*/
void Uds_Dtc_ReadDtc_Info(const uint8_t* fl_pdiagdata_u8, uint8_t* fl_DataPtr_u8, uint8_t* fl_DLC_u8);

/*
 * @brief    This function copies data from NvM to local buffer
 * @param    fl_dtcindex_u8 - Index of the DTC information table
 * @return   NULL
 */
void Uds_Dtc_ReadMirrorData(uint8_t fl_DTCindex_u8);

/*
 * @brief    This API sets the operation cycle status as per the status changed
 * @param    OCStatus - Status of the OC (UDS_DTC_OPERATION_CYCLE_RUN_CONDITION/ UDS_DTC_OPERATION_CYCLE_STOP_CONDITION)
 * @return   NULL
 * @note     This API has to be called by the Dtc App layer under operation cycle maintainance operation
 */
void Uds_Dtc_Set_OperationCycle(uint8_t OCStatus);

/*
* @brief    This API is used to Initialize an operation cycle related elements
* @param    
* @return   
*/
void Uds_Dtc_OperationCycle_Init(void);

/*
 * @brief    This API sets the FDC when a test is failed
 * @param    fl_dtcindex_u8 - DTC index value
 * @param    fl_FDCIncrmntResolution_u8 - Resolution to the increment value of FDC
 * @return   NULL
 */
void Uds_Dtc_Increment_FDC(uint8_t fl_dtcindex_u8, uint8_t fl_FDCIncrmntResolution_u8);

/*
 * @brief    This API decrements aging down counter when an OC completes with 3rd bit set
 * @param    fl_dtcindex_u8 - DTC index value
 * @param    fl_AgingDcrmntResolution_u8 - Resolution to the decrement value of Aging Counter
 * @return   NULL
 */
void Uds_Dtc_Decrement_AgingCounter(uint8_t fl_dtcindex_u8, uint8_t fl_AgingDcrmntResolution_u8);

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
***********************************************************************************************************************
    REVISION NUMBER      : V1.0.1
    REVISION DATE        : 22-July-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : g_Uds_Dtc_NvmRecord_St variable array size mapped with maximum  DTC configured MACRO.
                           Uds_Dtc_Record_Struct structure mapped with array variables size with configurable macro.
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.0                                                           
    REVISION DATE        : 26-June-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! UDS_DTC_H */
