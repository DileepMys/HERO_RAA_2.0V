/* @file FILE NAME */
#ifndef UDS_DTC_C
#define UDS_DTC_C

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
 *  File name                       : Uds_Dtc.c
 *  Version                         : V1.0.6
 *  Micros supported                : Micro Agnostic (Independent)
 *  Compilers supported             : XXXXX
 *  Platforms supported             : XXXXX 
 *  Description                     : This file contains the definitions of Uds_Dtc Core Layer
 *  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "UDS_Cfg.h"
#if((UDS_CLEAR_DTC_SID_0x14_FEATURE == STD_ON) || (UDS_READ_DTC_SID_0x19_FEATURE == STD_ON) || (UDS_CONTROL_DTC_SID_0x85_FEATURE == STD_ON))
#include "Uds_DtcApp.h"
#include "Uds_Dtc.h"
#include "hal_stdtypes.h"
#include "Uds_Types.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*  
 * @brief: This macro is used to set a bit of Status Byte
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: YES
 * @Param: operand - Operand byte value
 * @Param: bit_mask - Masked value of Bit to be set
 */
#define DTC_SETBIT( operand, bit_mask )         ((operand) |= (bit_mask))

/*  
 * @brief: This macro is used to clear a bit of Status byte
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: YES
 * @Param: operand - Operand byte value
 * @Param: bit_mask - Masked value of Bit to be clear
 */
#define DTC_CLEARBIT( operand, bit_mask )       ((operand) &= (~(bit_mask)))

/*  
 * @brief: This macro is used to check the DTC Status bits' Availability
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: YES
 * @Param: operand - Operand byte value
 * @Param: bit_mask - Masked value of Bit to be clear
 */
#define DTC_TESTBIT( operand, bit_mask )        (((operand) & (bit_mask)) != ((bit_mask) - (bit_mask)))

/*  
 * @brief: This macro is used to clear a bit of Status byte
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: To be used only inside Main function
 * @Param: operand - Operand byte value
 * @Param: bit_mask - Masked value of Bit to be clear
 */
#define UDS_SUPPRESS_BITMASK            (uint8_t)0x7F

/*  
 * @brief: This macro is used to chECk whether First Power Up has been done by filling with known value
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: N/A
 */
#define UDS_DTC_FIRST_PWR_UP_DONE       (uint8_t)0x55

/*  
 * @brief: This macro is used to set a flag  as high
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: N/A
 */
#define UDS_DTC_SET_FLAG       (uint8_t)0x01

/*  
 * @brief: This macro is used to clear a flag  as low
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: N/A

 */
#define UDS_DTC_CLEAR_FLAG       (uint8_t)0x00
/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to store the DTC record details as in Nvm
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: YES 
 */
Uds_Dtc_Record_Struct g_Uds_Dtc_NvmRecord_St[UDS_DTC_MAX_CFG];

/*
 * @brief: This variable is used to store the Firsst Power Up status details in Nvm
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: YES 
 */
uint8_t g_Uds_Dtc_FirstPowerUp_NvmByte_u8;    
/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*
 * @brief: This variable is used to locally read and store the Nvm Data
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: YES 
 */
static Uds_Dtc_Record_Struct l_Uds_Dtc_MirrorNvmRecord_St;

/*
 * @brief: This variable is used to locally modify the First Power Up status details in Nvm
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: YES 
 */
static uint8_t l_Uds_Dtc_FirstPowerUp_NvmMirrorByte_u8; 

/*
 * @brief: This variable is used to maintain  the Write pending status of each DTC index in Nvm
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 or 1
 * @Applicability: YES 
 */
static uint8_t l_Uds_Dtc_WritePending_Flag_u8[UDS_DTC_MAX_CFG];

/*
 * @brief: This variable is used to maintain  the Write pending status of 1st power-up byte in Nvm
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 1 or 0
 * @Applicability: YES 
 */
static uint8_t l_Uds_Dtc_FirstPwrUp_WritePending_Flag_u8;

/*
 * @brief: This variable is used to maintain  the Write pending data of each DTC index that are to be written in Nvm
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: YES 
 */
static Uds_Dtc_Record_Struct l_Uds_Dtc_WritePending_Data_u8[UDS_DTC_MAX_CFG];

/*
 * @brief: This variable is used to maintain  the Write pending completion status 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 1 or 0
 * @Applicability: YES 
 */
static uint8_t l_Uds_Dtc_ReadWritePending_CompletedFlag_u8 = UDS_DTC_CLEAR_FLAG;
/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    This function processes the Error logging after the 3rd bit Confirmed DTC bit is set
 * @param    fl_ErrorDataPtr_u8 - Data pointer with Error data ( Snapshot/ Stored/ Extended Data)
 * @param    fl_DLC_u8 - Length of the Data record received through pointer
 * @return   
 */
static void Uds_Dtc_SetError(uint8_t *fl_ErrorDataPtr_u8, uint8_t fl_DLC_u8);

/*
 * @brief    This function processes the Write to Nvm operation by queuing based on Nvm's status
 * @param    fl_BlockID_u16 - Nvm Block ID
 * @param    fl_loopindex_u8 - Index to iterate the data correspondingly
 * @return   NULL
 */
static void Uds_DtcData_WriteNvm(uint16_t fl_BlockID_u16, uint8_t fl_loopindex_u8);
/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
* @brief    This API is used to initialize DTC core layer
* @param    NULL
* @return   NULL
*/
void Uds_Dtc_Init(void)
{
    uint8_t fl_loopindex_u8;
    uint16_t fl_BlockID_u16 = UDS_DTC_ZERO;
    uint8_t fl_FirstPwrUp_Val_u8 = UDS_DTC_ZERO;
    
    (void)UDS_DTC_READ_NVM(UDS_DTC_FIRST_POWERUP_BLOCK_ID, 0, &fl_FirstPwrUp_Val_u8, 1u);

    if(fl_FirstPwrUp_Val_u8 != UDS_DTC_FIRST_PWR_UP_DONE)
    {
        for(fl_loopindex_u8 = UDS_DTC_ZERO; fl_loopindex_u8 < UDS_DTC_MAX_CFG; fl_loopindex_u8++)
        {
            /*Fetch Block ID information from cfg table for the particular DTC*/
            fl_BlockID_u16 =  Uds_Dtc_Process_TableConfig[fl_loopindex_u8].l_BlockID_u16;

            /*Operation Cycle Initialization*/
            Uds_Dtc_OperationCycle_Init();

            /*Check for the status bit availability to set the bit accordingly*/
            if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TNCSLC_4TH))
            {
                /*Initialize status byte */
                l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8 = UDS_DTC_ZERO;

                /*Set the Status byte with 4th bit - testNotCompletedSinceLastClear*/
                DTC_SETBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TNCSLC_4TH);
            }

            /*Check for the status bit availability to set the bit accordingly*/
            if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TNCTOC_6TH))
            {
                if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TNCSLC_4TH))
                {
                    /*Initialize status byte with 6th bit - testNotCompletedThisOperationCycle along 4th bit - testNotCompletedSinceLastClear*/
                    DTC_SETBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TNCTOC_6TH);
                }
                else
                {
                    /*Initialize status byte */
                    l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8 = UDS_DTC_ZERO;

                    /*Set the Status byte with 6th bit - testNotCompletedThisOperationCycle*/
                    DTC_SETBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TNCTOC_6TH);
                } 
            }
        /*Write DTC structure to NvM for a block*/
        Uds_DtcData_WriteNvm(fl_BlockID_u16, fl_loopindex_u8);
        }

        /*Change the status in the variable to store in Nvm that First Power Up Done */
        l_Uds_Dtc_FirstPowerUp_NvmMirrorByte_u8 = UDS_DTC_FIRST_PWR_UP_DONE;

        /*Write the 1st Power up detection to Nvm only if state in IDLE*/
        if (UDS_DTC_NVM_MGR_IDLE == UDS_DTC_GET_NVM_MGR_STATUS(UDS_DTC_FIRST_POWERUP_BLOCK_ID))
        {
            /*Push the Data to Nvm*/
            UDS_DTC_WRITE_NVM(UDS_DTC_FIRST_POWERUP_BLOCK_ID, (uint8_t*)&l_Uds_Dtc_FirstPowerUp_NvmMirrorByte_u8);

            /*Clear the corresponding pending flag for write*/
            l_Uds_Dtc_FirstPwrUp_WritePending_Flag_u8 = UDS_DTC_CLEAR_FLAG;

        }
        else
        {
            /*Do not clear the flag, since it will be written in next iteration*/
            l_Uds_Dtc_FirstPwrUp_WritePending_Flag_u8 = UDS_DTC_SET_FLAG;
        }
    }
    /*If 1st Power-Up already done*/
    else if(fl_FirstPwrUp_Val_u8 == UDS_DTC_FIRST_PWR_UP_DONE)
    {
        for(fl_loopindex_u8 = UDS_DTC_ZERO; fl_loopindex_u8 < UDS_DTC_LOCAL_SS_SIZE; fl_loopindex_u8++)
        {
            /*Operation Cycle Initialization*/
            Uds_Dtc_OperationCycle_Init();
        }
    }
    else
    {
        /*Do nothing*/
    }    
}

/*
 * @brief    This function processes the Write to Nvm operation by queuing based on Nvm's status
 * @param    fl_BlockID_u16 - Nvm Block ID
 * @param    fl_loopindex_u8 - Index to iterate the data correspondingly
 * @return   NULL
 */
static void Uds_DtcData_WriteNvm(uint16_t fl_BlockID_u16, uint8_t fl_loopindex_u8)
{
    uint8_t fl_PendingIndex_u8 = UDS_DTC_ZERO;

    if (UDS_DTC_NVM_MGR_IDLE == UDS_DTC_GET_NVM_MGR_STATUS(fl_BlockID_u16))
    {
        /*Push the update data buffer to Nvm*/
        (void)UDS_DTC_WRITE_NVM(fl_BlockID_u16, (uint8_t*)&l_Uds_Dtc_MirrorNvmRecord_St);

        /*Since write to nvm is done, clear the Flag*/
        l_Uds_Dtc_WritePending_Flag_u8[fl_loopindex_u8] = UDS_DTC_ZERO;

        /*Copy and store the Nvm data to a local buffer*/
        l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_Uds_Dtc_StatusByte_u8    = UDS_DTC_ZERO;

        /*Initialze the montoring status*/
        l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_confirmStage             = UDS_DTC_INITIAL_MONITOR;

        /*Operation Cycle Counter clearance */
        l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_operationCycleCounter_u8 = UDS_DTC_ZERO;

        /*Initialize the Aging counter with Threshold value since it is a Down Counter*/
        l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_Dtc_Aging_DownCounter_u8 = UDS_DTC_ZERO;

        /*Clearing FDC*/
        l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_Dtc_FaultDetectionCounter_u8  = UDS_DTC_ZERO;

        /*Clear Last OC data*/
        l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_lastOperationCycle_u8 = UDS_DTC_ZERO;

        /*Clear current OC data*/
        l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_currentOperationCycle_u8 = UDS_DTC_ZERO;

        /*Local Snapshot record Clearance*/
        for(fl_PendingIndex_u8 = UDS_DTC_ZERO; fl_PendingIndex_u8 < UDS_DTC_LOCAL_SS_SIZE; fl_PendingIndex_u8++)
        {
            l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_Uds_Dtc_Local_SS_u8[fl_PendingIndex_u8]  = UDS_DTC_ZERO;
        }

        /*Global Snapshot record Clearance*/
        for(fl_PendingIndex_u8 = UDS_DTC_ZERO; fl_PendingIndex_u8 < UDS_DTC_GLOBAL_SS_SIZE; fl_PendingIndex_u8++)
        {
            l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_Uds_Dtc_Global_SS_u8[fl_PendingIndex_u8] = UDS_DTC_ZERO;
        }
    }
    else
    {
        /*Set the flag to write to nvm later*/
        l_Uds_Dtc_WritePending_Flag_u8[fl_loopindex_u8] = UDS_DTC_SET_FLAG;

        /*Copy and store the Nvm data to a local buffer*/
        l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_Uds_Dtc_StatusByte_u8    = l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8;

        /*Backup the monitoring status*/
        l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_confirmStage             = l_Uds_Dtc_MirrorNvmRecord_St.l_confirmStage;

        /*Aging counter backup*/
        l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_Dtc_Aging_DownCounter_u8 = l_Uds_Dtc_MirrorNvmRecord_St.l_Dtc_Aging_DownCounter_u8;

        /*Backup FDC*/
        l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_Dtc_FaultDetectionCounter_u8  = l_Uds_Dtc_MirrorNvmRecord_St.l_Dtc_FaultDetectionCounter_u8;

        /*Operation Cycle Counter update */
        l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_operationCycleCounter_u8 = l_Uds_Dtc_MirrorNvmRecord_St.l_operationCycleCounter_u8;

        /*Last operation cycle backup*/
        l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_lastOperationCycle_u8 = l_Uds_Dtc_MirrorNvmRecord_St.l_lastOperationCycle_u8;

        /*Current operation cycle backup*/
        l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_currentOperationCycle_u8 = l_Uds_Dtc_MirrorNvmRecord_St.l_currentOperationCycle_u8;

        /*Local Snapshot record backup*/
        for(fl_PendingIndex_u8 = UDS_DTC_ZERO; fl_PendingIndex_u8 < UDS_DTC_LOCAL_SS_SIZE; fl_PendingIndex_u8++)
        {
            l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_Uds_Dtc_Local_SS_u8[fl_PendingIndex_u8] = \
            l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_Local_SS_u8[fl_PendingIndex_u8];
        }

        /*Global Snapshot record backup*/
        for(fl_PendingIndex_u8 = UDS_DTC_ZERO; fl_PendingIndex_u8 < UDS_DTC_GLOBAL_SS_SIZE; fl_PendingIndex_u8++)
        {
            l_Uds_Dtc_WritePending_Data_u8[fl_loopindex_u8].l_Uds_Dtc_Global_SS_u8[fl_PendingIndex_u8] = \
            l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_Global_SS_u8[fl_PendingIndex_u8];
        }
    }
}

/*
* @brief    This API is used to deinitialize the DTC core layer
* @param    
* @return   
*/
void Uds_Dtc_DeInit(void)
{

}

/*
* @brief    This API is used to execute the periodic execution of status bit checks and updates for each DTC
* @param    NULL
* @return   NULL
* @note     To be mapped in the Time task
*/
void Uds_Dtc_MainFunction(void)
{
    uint8_t fl_loopindex_u8 = UDS_DTC_ZERO;
    #if(UDS_DTC_SETTING_LOCK_FEATURE == STD_ON)
    uint8_t fl_DTC_SettingStatus_u8 = UDS_DTC_ZERO;
    #endif
    static uint8_t fl_DataBuffer_u8[UDS_DTC_LOCAL_SS_SIZE + UDS_DTC_GLOBAL_SS_SIZE] = { UDS_DTC_ZERO, UDS_DTC_ZERO, UDS_DTC_ZERO, UDS_DTC_ZERO, UDS_DTC_ZERO, \
                                     UDS_DTC_ZERO, UDS_DTC_ZERO, UDS_DTC_ZERO, UDS_DTC_ZERO, UDS_DTC_ZERO, \
                                     UDS_DTC_ZERO, UDS_DTC_ZERO, UDS_DTC_ZERO, UDS_DTC_ZERO, UDS_DTC_ZERO, \
                                     UDS_DTC_ZERO, UDS_DTC_ZERO, UDS_DTC_ZERO, UDS_DTC_ZERO, UDS_DTC_ZERO};
    static uint8_t fl_DLC_u8 = UDS_DTC_ZERO;
    uint8_t fl_BlockID_u16 = UDS_DTC_ZERO;
    uint8_t fl_SSindex_u8 = UDS_DTC_ZERO;
    Uds_Dtc_Error_Status fl_ErrorStatus = UDS_DTC_ERROR_NOT_OCCURRED;
    uint8_t fl_WritePendingIndex_u8 = UDS_DTC_ZERO;

    if(UDS_DTC_NVM_MGR_IDLE == UDS_DTC_GET_NVM_MGR_STATUS(UDS_DTC_FIRST_POWERUP_BLOCK_ID))
    {
        /*Check whether NVMMgr is in IDLE state to Write*/
        if(l_Uds_Dtc_FirstPwrUp_WritePending_Flag_u8 == UDS_DTC_SET_FLAG)
        {
            /*Write to the Nvm*/
            (void)UDS_DTC_WRITE_NVM(UDS_DTC_FIRST_POWERUP_BLOCK_ID, (uint8_t*)&l_Uds_Dtc_FirstPowerUp_NvmMirrorByte_u8);
            /*Clear Pending write flag for 1st powerup*/
            l_Uds_Dtc_FirstPwrUp_WritePending_Flag_u8 = UDS_DTC_ZERO;
        }
    }

    /*Iteration for Write pending*/
    for(fl_WritePendingIndex_u8 = UDS_DTC_ZERO; fl_WritePendingIndex_u8 < UDS_DTC_MAX_CFG; fl_WritePendingIndex_u8++)
    {
        /*Check whether Nvm mgr is in idle state to write*/
        if(UDS_DTC_NVM_MGR_IDLE == UDS_DTC_GET_NVM_MGR_STATUS(Uds_Dtc_Process_TableConfig[fl_WritePendingIndex_u8].l_BlockID_u16))
        {
            /*Iteration for Pending flag to be written*/
            if((l_Uds_Dtc_WritePending_Flag_u8[fl_WritePendingIndex_u8] == UDS_DTC_SET_FLAG))
            {
                /*Write if pending data is there to be written*/
                (void)UDS_DTC_WRITE_NVM(Uds_Dtc_Process_TableConfig[fl_WritePendingIndex_u8].l_BlockID_u16,  \
                (uint8_t*)&l_Uds_Dtc_WritePending_Data_u8[fl_WritePendingIndex_u8]);

                /*Clear the flag */
                l_Uds_Dtc_WritePending_Flag_u8[fl_WritePendingIndex_u8] = UDS_DTC_CLEAR_FLAG;
            }
            else
            {
                /*Do nothing*/
            }
        }
    }
    /*Prepare the flag for new iteration execution*/
    l_Uds_Dtc_ReadWritePending_CompletedFlag_u8 = UDS_DTC_SET_FLAG;

    /*Iterate whether any pending write is there to be executed*/
    for(fl_WritePendingIndex_u8 = UDS_DTC_ZERO; ((fl_WritePendingIndex_u8 < UDS_DTC_MAX_CFG) && (l_Uds_Dtc_ReadWritePending_CompletedFlag_u8 == 1u)); fl_WritePendingIndex_u8++)
    {
        /*Flag status to be checked for writing to Nvm*/
        if((l_Uds_Dtc_WritePending_Flag_u8[fl_WritePendingIndex_u8] == UDS_DTC_ZERO))
        {
            /*Check whether all read-back for data that has been written is completed*/
            if(UDS_DTC_NVM_MGR_IDLE == UDS_DTC_GET_NVM_MGR_STATUS(Uds_Dtc_Process_TableConfig[fl_WritePendingIndex_u8].l_BlockID_u16))
            {
                /*No pending data to be written/ read - Hence set the completion flag*/
                l_Uds_Dtc_ReadWritePending_CompletedFlag_u8 = UDS_DTC_SET_FLAG;
            }
            else
            {
               /*Pending Data to be written/ read - Clear the flag*/
               l_Uds_Dtc_ReadWritePending_CompletedFlag_u8 = UDS_DTC_CLEAR_FLAG;
            }

        }
        else
        {
            /*Pending Data to be written/ read - Clear the flag*/
            l_Uds_Dtc_ReadWritePending_CompletedFlag_u8 = UDS_DTC_CLEAR_FLAG;
        }
    }
    /*All pending read and write activities executed*/
    if(l_Uds_Dtc_ReadWritePending_CompletedFlag_u8 == UDS_DTC_SET_FLAG)
    {
        #if(UDS_DTC_SETTING_LOCK_FEATURE == STD_ON)
        /*Get the current DTC setting status*/
        fl_DTC_SettingStatus_u8 = Uds_DtcApp_Get_MonitoringStatus();
        /*Check whether monitoring is allowed currently*/
        if(fl_DTC_SettingStatus_u8 == DTC_SETTING_ON)
        {
        #endif
            /*Execute the DTCs according the Process table sequentially*/
            for(fl_loopindex_u8 = UDS_DTC_ZERO; fl_loopindex_u8 < UDS_DTC_MAX_CFG; fl_loopindex_u8++)
            {
                /*Fetch Block ID information from cfg table for the particular DTC*/
                fl_BlockID_u16 =  Uds_Dtc_Process_TableConfig[fl_loopindex_u8].l_BlockID_u16;

                /*Proceed if the current operation cycle is in a Runnable condition*/
                if(UDS_DTC_OPERATION_CYCLE_RUN_CONDITION == g_Uds_Dtc_NvmRecord_St[fl_loopindex_u8].l_currentOperationCycle_u8)
                {
                    /*Check whether previous operation cycle and current operation cycle are same */
                    if(g_Uds_Dtc_NvmRecord_St[fl_loopindex_u8].l_lastOperationCycle_u8 == \
                       g_Uds_Dtc_NvmRecord_St[fl_loopindex_u8].l_currentOperationCycle_u8)
                    {
                        /*Fetch the Error status for current monitoring cycle*/
                        fl_ErrorStatus = Uds_Dtc_Process_TableConfig[fl_loopindex_u8].FunctionHandler();

                        /*Read the DTC existing data from NvM*/
                        Uds_Dtc_ReadMirrorData(fl_loopindex_u8);

                        switch (fl_ErrorStatus)
                        {
                        /*Error has been occurred in current monitoring cycle*/
                        case UDS_DTC_ERROR_OCCURRED:

                                /*Check for the status bit availability to set the bit accordingly*/
                                if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TF_0TH))
                                {
                                    /*Set 0th bit - testFailed*/
                                    DTC_SETBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TF_0TH);
                                }

                                /*Check for the status bit availability to set the bit accordingly*/
                                if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TFTOC_1ST))
                                {
                                    /*Set 1st bit - testFailedthisOperationCycle*/
                                    DTC_SETBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TFTOC_1ST);
                                }

                                /*Check for the status bit availability to set the bit accordingly*/
                                if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TFSLC_5TH))
                                {
                                    /*Set 5th bit - testFailedSinceLastClear */
                                    DTC_SETBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TFSLC_5TH);
                                }

                                /*Check for the status bit availability to set the bit accordingly*/
                                if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TNCSLC_4TH))
                                {
                                    /*Clear 4th bit - testNotCompletedSinceLastClear */
                                    DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TNCSLC_4TH);
                                }

                                /*Check for the status bit availability to set the bit accordingly*/
                                if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TNCTOC_6TH))
                                {
                                    /*Clear 6th bit - testNotCompletedThisOperationCycle */
                                    DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TNCTOC_6TH);
                                }

                                /*Reset the Aging Counter Value*/
                                l_Uds_Dtc_MirrorNvmRecord_St.l_Dtc_Aging_DownCounter_u8 = UDS_DTC_AGING_COUNTER_THRESHOLD_VALUE;

                                /*Check whether the FDC has reached the threshold value*/
                                if(g_Uds_Dtc_NvmRecord_St[fl_loopindex_u8].l_Dtc_FaultDetectionCounter_u8 >= \
                                                                        UDS_DTC_FDC_THRESHOLD_VALUE)
                                {
                                    /*Check for the status bit availability to set the bit accordingly*/
                                    if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_CDTC_3RD))
                                    {
                                        /*Set 3rd bit confirmedDTC*/
                                        DTC_SETBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_CDTC_3RD);
                                    }

                                    /*Set the Confirmation stage for 3rd bit reached Aging monitor level*/
                                    l_Uds_Dtc_MirrorNvmRecord_St.l_confirmStage = UDS_DTC_AGING_MONITOR;

                                    /*Get the Snapshot Data record since FDC has matured*/
                                    Uds_DtcApp_Get_Record_Info(fl_loopindex_u8, &fl_DataBuffer_u8[0], &fl_DLC_u8);

                                    /*Push the record details to NvM upon error confirmation*/
                                    Uds_Dtc_SetError(&fl_DataBuffer_u8[0], fl_DLC_u8);

                                    /*Check whether Warning indicator exists for this DTC*/
                                    if((Uds_Dtc_Process_TableConfig[fl_loopindex_u8].l_WarningIndicator_Feature_bool == ((boolean)TRUE)))
                                    {
                                        /*Check whether Warning indicator Criteria Satisfied for the particular DTC*/
                                        if(Uds_DtcApp_WarningIndicator_Status(fl_loopindex_u8) == E_OK)
                                        {
                                            /*Check for the status bit availability to set the bit accordingly*/
                                            if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_WIR_7TH))
                                            {
                                                /*Set 7th bit - warningIndicatorRequested */
                                                DTC_SETBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_WIR_7TH);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        /*Do nothing*/
                                    }
                                }
                                Uds_DtcData_WriteNvm(fl_BlockID_u16, fl_loopindex_u8);
                                break;

                        case UDS_DTC_ERROR_NOT_OCCURRED:

                                /*Check for the status bit availability to set the bit accordingly*/
                                if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TF_0TH))
                                {
                                    /*Clear 0th bit - testFailed*/
                                    DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TF_0TH);
                                }

                                /*Check for the status bit availability to set the bit accordingly*/
                                if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TNCSLC_4TH))
                                {
                                    /*Clear 4th bit - testNotCompletedSinceLastClear*/
                                    DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TNCSLC_4TH);
                                }

                                /*Check for the status bit availability to set the bit accordingly*/
                                if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TNCTOC_6TH))
                                {
                                    /*Clear 6th bit - testNotCompletedThisOperationCycle */
                                    DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TNCTOC_6TH);
                                }

                                /*Check for the status bit availability to set the bit accordingly*/
                                if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_CDTC_3RD))
                                {
                                    /*Check whether 3rd bit - confirmedDTC has been set*/
                                    if(DTC_TESTBIT(g_Uds_Dtc_NvmRecord_St[fl_loopindex_u8].l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_CDTC_3RD))
                                    {
                                        /*Check whether Aging counter has expired*/
                                        if(g_Uds_Dtc_NvmRecord_St[fl_loopindex_u8].l_Dtc_Aging_DownCounter_u8 == UDS_DTC_ZERO)
                                        {
                                            /*Check for the status bit availability to set the bit accordingly*/
                                            if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_CDTC_3RD))
                                            {
                                                /*Since Aging counter has expired, Clear 3rd bit - confirmedDTC */
                                                DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_CDTC_3RD);
                                            }

                                            /*Check for the status bit availability to set the bit accordingly*/
                                            if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TFSLC_5TH))
                                            {
                                                /*Since Aging counter has expired, Clear 5th bit- testFailedSinceLastClear */
                                                DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TFSLC_5TH);
                                            }

                                            /*Set the DTC's confirmation stage as Initial since data has been cleared*/
                                            l_Uds_Dtc_MirrorNvmRecord_St.l_confirmStage = UDS_DTC_INITIAL_MONITOR;

                                            /*Since Aging counter has expired, Clearing the data relevant to current DTC*/
                                            for(fl_SSindex_u8 = UDS_DTC_ZERO; fl_SSindex_u8 < UDS_DTC_LOCAL_SS_SIZE; fl_SSindex_u8++)
                                            {
                                                l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_Local_SS_u8[fl_SSindex_u8]  = UDS_DTC_ZERO;
                                            }

                                            for(fl_SSindex_u8 = UDS_DTC_ZERO; fl_SSindex_u8 < UDS_DTC_GLOBAL_SS_SIZE; fl_SSindex_u8++)
                                            {
                                                l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_Global_SS_u8[fl_SSindex_u8] = UDS_DTC_ZERO;
                                            }
                                        }
                                    }
                                }
                                Uds_DtcData_WriteNvm(fl_BlockID_u16, fl_loopindex_u8);
                                break;

                        case UDS_DTC_NOT_USED:
                                /*Future implementation*/
                                break;

                        default:
                            /*Do nothing*/
                            break;
                        }
                    }

                    /*Operation cycle and current operation cycle are not same */
                    else
                    {
                        /*Do nothing*/
                    }
                }
                /*Current operation cycle is not in Runnable condition*/
                else
                {
                    /*Do nothing*/
                }
            }

        #if(UDS_DTC_SETTING_LOCK_FEATURE == STD_ON)
        }
        else
        {
            /*Do nothing*/
        }
        #endif
    }
    /*Write to Nvm is pending, do not proceed with DTC iteration*/
    else
    {
        /*Do nothing*/
    }
}

/*
 * @brief    This function processes the Error logging after the 3rd bit Confirmed DTC bit is set
 * @param    fl_ErrorDataPtr_u8 - Data pointer with Error data ( Snapshot/ Stored/ Extended Data)
 * @param    fl_DLC_u8 - Length of the Data record received through pointer
 * @return   
 */
static void Uds_Dtc_SetError(uint8_t *fl_ErrorDataPtr_u8, uint8_t fl_DLC_u8)
{
    uint8_t fl_loopindex_u8;
    uint8_t fl_LSS_index_u8 = UDS_DTC_ZERO;
    uint8_t fl_GSS_index_u8 = UDS_DTC_ZERO;

    /*Fill up the local buffer with LSS data record from application to write in NvM*/
    for(fl_loopindex_u8 = UDS_DTC_ZERO; fl_loopindex_u8 < UDS_DTC_LOCAL_SS_SIZE; fl_loopindex_u8++) 
    {
        l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_Local_SS_u8[fl_LSS_index_u8]  = fl_ErrorDataPtr_u8[fl_loopindex_u8];
        fl_LSS_index_u8 += UDS_DTC_INCREMENT_BY_ONE;
    }  

    /*Fill up the local buffer with GSS data record from application to write in NvM*/
    for(fl_loopindex_u8 = UDS_DTC_LOCAL_SS_SIZE; fl_loopindex_u8 < (UDS_DTC_LOCAL_SS_SIZE + UDS_DTC_GLOBAL_SS_SIZE); fl_loopindex_u8++)
    {     
        l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_Global_SS_u8[fl_GSS_index_u8] = fl_ErrorDataPtr_u8[fl_loopindex_u8];
        fl_GSS_index_u8 += UDS_DTC_INCREMENT_BY_ONE;
    }  
}

/*
* @brief    This API is used to Clear the Diagnostic information when requested by the Client through service 0x14
* @param    fl_DTCVal_u32 - 3 byte value of DTC Group
* @return   Clear_Dtc_ErrorCode - Error codes based on the execution of Clearing DTC information
            DTC_NO_ERROR - No error occurred while clearing DTC
            DTC_GRP_NOT_FOUND - The requested Group of DTC is not found in server
            DTC_NOT_CLEARABLE - Due to internal error, DTC not cleared
*/
Clear_Dtc_ErrorCode Uds_Dtc_Clear_Diagnostics_Info(uint32_t fl_DTCVal_u32)
{
    uint8_t fl_loopindex_u8 = UDS_DTC_ZERO;
    boolean fl_DTCMatched_Flag_bool = ((boolean)FALSE);
    uint16_t fl_BlockID_u16 = (uint16_t)0;
    Clear_Dtc_ErrorCode fl_ErrorCode = DTC_NO_ERROR;
    uint8_t fl_ClearStatus_u8 = E_OK;
    uint8_t fl_LSS_index_u8 = UDS_DTC_ZERO;
    uint8_t fl_GSS_index_u8 = UDS_DTC_ZERO;

    /*Check whether Clear request received for any specific DTC group or all DTCs*/
    if(fl_DTCVal_u32 != ALL_DTC_GRP)
    {
        /*Iteration to find matching DTC based on the maximum  number of DTCs available in server*/
        for(fl_loopindex_u8 = UDS_DTC_ZERO; \
           ((fl_loopindex_u8 < UDS_DTC_MAX_CFG) && (fl_DTCMatched_Flag_bool != ((boolean)TRUE))); \
           fl_loopindex_u8++)
        {
            /*Check whether received DTC value matches with server supported DTC*/
            if(fl_DTCVal_u32 == Uds_Dtc_Process_TableConfig[fl_loopindex_u8].l_DTCGroup_u32)
            {
                /*Fetch Block ID information from cfg table since the DTC value matched*/
                fl_BlockID_u16 =  Uds_Dtc_Process_TableConfig[fl_loopindex_u8].l_BlockID_u16;

                /*Set the DTC match flag to proceed clearing*/
                fl_DTCMatched_Flag_bool = ((boolean)TRUE);
            }
        }

        /*Proceed clearing the corresponding DTC relevant data if the DTC has matched*/
        if(fl_DTCMatched_Flag_bool == ((boolean)TRUE))
        {

            /*Copy and store the Nvm data to a local buffer*/
            l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8    = UDS_DTC_ZERO;

            if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TNCSLC_4TH))
            {
                /*Initialize (set) 4th bit of Status Byte - testNotCompletedSinceLastClear*/
                DTC_SETBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TNCSLC_4TH);
            }

            if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TNCTOC_6TH))
            {
                /*Initialize (set) 6th bit of Status Byte - testNotCompletedThisOperationCycle*/
                DTC_SETBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TNCTOC_6TH);
            }

            /*Initialze the montoring status*/
            l_Uds_Dtc_MirrorNvmRecord_St.l_confirmStage             = UDS_DTC_INITIAL_MONITOR;

            /*Initialize the Aging counter with Threshold value since it is a Down Counter*/
            l_Uds_Dtc_MirrorNvmRecord_St.l_Dtc_Aging_DownCounter_u8 = UDS_DTC_AGING_COUNTER_THRESHOLD_VALUE;

            /*Clearing FDC*/
            l_Uds_Dtc_MirrorNvmRecord_St.l_Dtc_FaultDetectionCounter_u8  = UDS_DTC_ZERO;

            /*Local Snapshot record Clearance*/
            for(fl_loopindex_u8 = UDS_DTC_ZERO; fl_loopindex_u8 < UDS_DTC_LOCAL_SS_SIZE; fl_loopindex_u8++) 
            {
                l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_Local_SS_u8[fl_loopindex_u8]  = UDS_DTC_ZERO;
            }
            
            /*Global Snapshot record Clearance*/
            for(fl_loopindex_u8 = UDS_DTC_ZERO; fl_loopindex_u8 < UDS_DTC_GLOBAL_SS_SIZE; fl_loopindex_u8++) 
            {      
                l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_Global_SS_u8[fl_loopindex_u8] = UDS_DTC_ZERO;
            }

            /*Execute Clearance of DTC information in that block*/
             fl_ClearStatus_u8 = UDS_DTC_WRITE_NVM(fl_BlockID_u16, (uint8_t*)&l_Uds_Dtc_MirrorNvmRecord_St);

            /*Check whether DTC clearance done successfully*/
            if(fl_ClearStatus_u8 == E_OK)
            {
                /*Set as NO ERROR since DTC cleared successfully*/
                fl_ErrorCode = DTC_NO_ERROR; 
            }
            else
            {
                /*Capture Error Code as NOT CLEARABLE*/
                fl_ErrorCode = DTC_NOT_CLEARABLE;
            }   
        }
        /*Requested DTC value not matched for clearance*/
        else
        {
            /*Capture Error Code as Requested DTC NOT FOUND*/
            fl_ErrorCode = DTC_GRP_NOT_FOUND;
        }
    }
    /*Request received to clear all DTCs relevant data*/
    else
    {
        /*Iteration to DTC one by one based on the maximum  number of DTCs available in server*/
        for(fl_loopindex_u8 = UDS_DTC_ZERO; \
           ((fl_loopindex_u8 < UDS_DTC_MAX_CFG) && (fl_ClearStatus_u8 != E_NOT_OK)); \
           fl_loopindex_u8++)
        {
            /*Copy and store the Nvm data to a local buffer*/
            l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8    = UDS_DTC_ZERO;

            if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TNCSLC_4TH))
            {
                /*Initialize (set) 4th bit of Status Byte - testNotCompletedSinceLastClear*/
                DTC_SETBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TNCSLC_4TH);
            }

            if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TNCTOC_6TH))
            {
                /*Initialize (set) 6th bit of Status Byte - testNotCompletedThisOperationCycle*/
                DTC_SETBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TNCTOC_6TH);
            }

            /*Initialize the monitoring status*/
            l_Uds_Dtc_MirrorNvmRecord_St.l_confirmStage             = UDS_DTC_INITIAL_MONITOR;

            /*Initialize the Aging counter with Threshold value since it is a Down Counter*/
            l_Uds_Dtc_MirrorNvmRecord_St.l_Dtc_Aging_DownCounter_u8 = UDS_DTC_AGING_COUNTER_THRESHOLD_VALUE;

            /*Clearing FDC*/
            l_Uds_Dtc_MirrorNvmRecord_St.l_Dtc_FaultDetectionCounter_u8  = UDS_DTC_ZERO;

            /*Local Snapshot record Clearance*/
            for(fl_LSS_index_u8 = UDS_DTC_ZERO; fl_LSS_index_u8 < UDS_DTC_LOCAL_SS_SIZE; fl_LSS_index_u8++) 
            {
                l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_Local_SS_u8[fl_LSS_index_u8]  = UDS_DTC_ZERO;
            }

            /*Global Snapshot record Clearance*/
            for(fl_GSS_index_u8 = UDS_DTC_ZERO; fl_GSS_index_u8 < UDS_DTC_GLOBAL_SS_SIZE; fl_GSS_index_u8++) 
            {      
                l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_Global_SS_u8[fl_GSS_index_u8] = UDS_DTC_ZERO;
            }
            /*Fetch Block ID information from cfg table since the DTC value matched*/
            fl_BlockID_u16 =  Uds_Dtc_Process_TableConfig[fl_loopindex_u8].l_BlockID_u16;

            /*Execute Clearance of DTC information in that block*/
             fl_ClearStatus_u8 = UDS_DTC_WRITE_NVM(fl_BlockID_u16, (uint8_t*)&l_Uds_Dtc_MirrorNvmRecord_St);
        }
        /*Check whether DTC clearance done successfully*/
        if(fl_ClearStatus_u8 == E_OK)
        {
            /*Set as NO ERROR since DTC cleared successfully*/
            fl_ErrorCode = DTC_NO_ERROR; 
        }
        /*DTC clearance not successful*/
        else
        {
            /*Capture Error Code as NOT CLEARABLE*/
            fl_ErrorCode = DTC_NOT_CLEARABLE;
        }
    }    
    /*Return the Error code*/
    return fl_ErrorCode; 
}

/*
* @brief    This API is used to Read the Diagnostic information when requested by the Client through service 0x19
* @param    fl_pdiagdata_u8 - Data associated with the 0x19 request 
* @param    fl_DataPtr_u8 - Pointer to return with updated data read from DTC layer to UdsApp layer
* @param    fl_DLC_u8 - Length of the Data returned through pointer above
* @return   NULL
*/
void Uds_Dtc_ReadDtc_Info(const uint8_t* fl_pdiagdata_u8, uint8_t* fl_DataPtr_u8, uint8_t* fl_DLC_u8)
{
    uint8_t fl_Total_DTCUsed_u16 = (uint16_t)0;
    uint8_t fl_loopindex_u8 = UDS_DTC_ZERO;
    uint32_t fl_DTCGroup_u32 = (uint32_t)0;
    uint8_t fl_RespIndex_u8 = UDS_DTC_ZERO;
    uint8_t fl_subfunction_u8 = (fl_pdiagdata_u8[0] & UDS_SUPPRESS_BITMASK);
    uint8_t fl_DTCStatusMask_u8 = UDS_DTC_ZERO;
    
    /* Sub-function - 0x01 - UDS_REPORT_NUMBER_OF_DTC_BY_STATUS_MASK*/
    if(fl_subfunction_u8 == (uint8_t)0x01)
    {
        /*Receive the requested Status Mask Value*/
        fl_DTCStatusMask_u8 = fl_pdiagdata_u8[1];

        /*Iteration to check DTC reported status that is supported by server*/
        for(fl_loopindex_u8 = UDS_DTC_ZERO; fl_loopindex_u8 < UDS_DTC_MAX_CFG; fl_loopindex_u8++)
        {
            /*Check whether any DTC has been reported*/
            if((g_Uds_Dtc_NvmRecord_St[fl_loopindex_u8].l_Uds_Dtc_StatusByte_u8 & \
                                                     fl_DTCStatusMask_u8) == fl_DTCStatusMask_u8)
            {
                /*Increment the DTC reported counter*/
                fl_Total_DTCUsed_u16 += UDS_DTC_INCREMENT_BY_ONE;
            }
        }   
        /*Report back the Response buffer with  Status Availability mask*/
        fl_DataPtr_u8[0] = UDS_DTC_STATUS_AVAILABILITY_MASK;

        /*Report back the Response buffer with  DTC format folowed*/
        fl_DataPtr_u8[1] = UDS_DTC_ISO_14229_1_DTC_FORMAT;

        /*MSB of Total DTCs used*/
        fl_DataPtr_u8[2] = (uint8_t) (fl_Total_DTCUsed_u16 >> (uint8_t)8);

        /*LSB of Total DTCs used*/
        fl_DataPtr_u8[3] = (uint8_t) (fl_Total_DTCUsed_u16);

        /*Pass the length of pointer passed on*/
        *fl_DLC_u8 = (uint8_t)4;
    }   
    /* Sub-function - 0x02 - UDS_REPORT_DTC_BY_STATUS_MASK*/
    else if(fl_subfunction_u8 == (uint8_t)0x02)
    {
        /*Receive the requested Status Mask Value*/
        fl_DTCStatusMask_u8 = fl_pdiagdata_u8[1];

        /*Report the Status availability mask*/
        fl_DataPtr_u8[fl_RespIndex_u8] = UDS_DTC_STATUS_AVAILABILITY_MASK;

        /*Iteration to check DTC reported status that is supported by server*/
        for(fl_loopindex_u8 = UDS_DTC_ZERO; \
        ((fl_loopindex_u8 < UDS_DTC_MAX_CFG)); \
        fl_loopindex_u8++)
        {
            /*Check whether any DTC has been reported*/
            if((g_Uds_Dtc_NvmRecord_St[fl_loopindex_u8].l_Uds_Dtc_StatusByte_u8 & \
                                                     fl_DTCStatusMask_u8) == fl_DTCStatusMask_u8)
            {
                /*Fetch the corresponding DTC group value for whom DTC has been reported*/
                fl_DTCGroup_u32 =  Uds_Dtc_Process_TableConfig[fl_loopindex_u8 ].l_DTCGroup_u32;

                /*Store the DTC value High byte in response buffer*/
                fl_RespIndex_u8 += UDS_DTC_INCREMENT_BY_ONE;
                fl_DataPtr_u8[fl_RespIndex_u8] = (uint8_t) (fl_DTCGroup_u32 >> (uint8_t)16);

                /*Store the DTC value Middle byte in response buffer*/
                fl_RespIndex_u8 += UDS_DTC_INCREMENT_BY_ONE;
                fl_DataPtr_u8[fl_RespIndex_u8] = (uint8_t) (fl_DTCGroup_u32 >> (uint8_t)8);

                /*Store the DTC value Low byte in response buffer*/
                fl_RespIndex_u8 += UDS_DTC_INCREMENT_BY_ONE;
                fl_DataPtr_u8[fl_RespIndex_u8] = (uint8_t) (fl_DTCGroup_u32);

                /*Store the Status byte value of corresponding DTC in response buffer*/
                fl_RespIndex_u8 += UDS_DTC_INCREMENT_BY_ONE;
                fl_DataPtr_u8[fl_RespIndex_u8] = g_Uds_Dtc_NvmRecord_St[fl_loopindex_u8].l_Uds_Dtc_StatusByte_u8;
            }
        }    
        /*Pass the length of pointer passed on*/
        *fl_DLC_u8 = (fl_RespIndex_u8 + UDS_DTC_INCREMENT_BY_ONE);
    }   
    /* Sub-function - 0x0A - UDS_REPORT_SUPPORTED_DTC*/
    else if(fl_subfunction_u8 == (uint8_t)0x0A)
    {
        /*Report the Status availability mask*/
        fl_DataPtr_u8[fl_RespIndex_u8] = UDS_DTC_STATUS_AVAILABILITY_MASK;
        /*Iteration to check DTC reported status that is supported by server*/
        for(fl_loopindex_u8 = UDS_DTC_ZERO; \
            fl_loopindex_u8 < UDS_DTC_MAX_CFG; \
            fl_loopindex_u8++)
        {
            /*Fetch the corresponding DTC group value for whom DTC has been reported*/
            fl_DTCGroup_u32 =  Uds_Dtc_Process_TableConfig[fl_loopindex_u8].l_DTCGroup_u32; 

            /*Store the DTC value High byte in response buffer*/
            fl_RespIndex_u8 += UDS_DTC_INCREMENT_BY_ONE;
            fl_DataPtr_u8[fl_RespIndex_u8] = (uint8_t) (fl_DTCGroup_u32 >> (uint8_t)16);

            /*Store the DTC value Middle byte in response buffer*/
            fl_RespIndex_u8 += UDS_DTC_INCREMENT_BY_ONE;
            fl_DataPtr_u8[fl_RespIndex_u8] = (uint8_t) (fl_DTCGroup_u32 >> (uint8_t)8);

            /*Store the DTC value Low byte in response buffer*/
            fl_RespIndex_u8 += UDS_DTC_INCREMENT_BY_ONE;
            fl_DataPtr_u8[fl_RespIndex_u8] = (uint8_t) (fl_DTCGroup_u32);

            /*Store the Status byte value of current DTC in iteration to the resposne buffer*/
            fl_RespIndex_u8 += UDS_DTC_INCREMENT_BY_ONE;
            fl_DataPtr_u8[fl_RespIndex_u8] = g_Uds_Dtc_NvmRecord_St[fl_loopindex_u8].l_Uds_Dtc_StatusByte_u8;
        }
        /*Pass the length of pointer passed on*/
        *fl_DLC_u8 = fl_RespIndex_u8 + UDS_DTC_INCREMENT_BY_ONE;
    }   
    
    /*For other Sub-functions - Fetch information from Dtc App layer*/
    else
    {
        Uds_DtcApp_ReadDtc_Info(fl_pdiagdata_u8, fl_DataPtr_u8, fl_DLC_u8);
    }
}

/*
 * @brief    This function copies data from NvM to local buffer
 * @param    fl_dtcindex_u8 - Index of the DTC information table
 * @return   NULL
 */
void Uds_Dtc_ReadMirrorData(uint8_t fl_DTCindex_u8)
{
    uint8_t fl_loopindex_u8  = UDS_DTC_ZERO;

    /*Copy and store the Nvm data to a local buffer*/
    l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8         = g_Uds_Dtc_NvmRecord_St[fl_DTCindex_u8].l_Uds_Dtc_StatusByte_u8;
    l_Uds_Dtc_MirrorNvmRecord_St.l_confirmStage                  = g_Uds_Dtc_NvmRecord_St[fl_DTCindex_u8].l_confirmStage;
    l_Uds_Dtc_MirrorNvmRecord_St.l_operationCycleCounter_u8      = g_Uds_Dtc_NvmRecord_St[fl_DTCindex_u8].l_operationCycleCounter_u8;
    l_Uds_Dtc_MirrorNvmRecord_St.l_Dtc_Aging_DownCounter_u8      = g_Uds_Dtc_NvmRecord_St[fl_DTCindex_u8].l_Dtc_Aging_DownCounter_u8;
    l_Uds_Dtc_MirrorNvmRecord_St.l_Dtc_FaultDetectionCounter_u8  = g_Uds_Dtc_NvmRecord_St[fl_DTCindex_u8].l_Dtc_FaultDetectionCounter_u8;
    l_Uds_Dtc_MirrorNvmRecord_St.l_lastOperationCycle_u8         = g_Uds_Dtc_NvmRecord_St[fl_DTCindex_u8].l_lastOperationCycle_u8;
    l_Uds_Dtc_MirrorNvmRecord_St.l_currentOperationCycle_u8      = g_Uds_Dtc_NvmRecord_St[fl_DTCindex_u8].l_currentOperationCycle_u8;
    
    /*Copy and store Local Snapshot information based on its bytes size*/
    for(fl_loopindex_u8 = UDS_DTC_ZERO; fl_loopindex_u8 < UDS_DTC_LOCAL_SS_SIZE; fl_loopindex_u8++) 
    {
        l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_Local_SS_u8[fl_loopindex_u8]  = \
        g_Uds_Dtc_NvmRecord_St[fl_DTCindex_u8].l_Uds_Dtc_Local_SS_u8[fl_loopindex_u8];        
    }  

    /*Copy and store Global Snapshot information based on its bytes size*/
    for(fl_loopindex_u8 = UDS_DTC_ZERO; fl_loopindex_u8 < UDS_DTC_GLOBAL_SS_SIZE; fl_loopindex_u8++) 
    {
        l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_Global_SS_u8[fl_loopindex_u8] = \
        g_Uds_Dtc_NvmRecord_St[fl_DTCindex_u8].l_Uds_Dtc_Global_SS_u8[fl_loopindex_u8];
    }         
}

/*
 * @brief    This API sets the operation cycle status as per the status changed
 * @param    OCStatus - Status of the OC (UDS_DTC_OPERATION_CYCLE_RUN_CONDITION/ UDS_DTC_OPERATION_CYCLE_STOP_CONDITION)
 * @return   NULL
 * @note     This API has to be called by the Dtc App layer under operation cycle maintainance (Curent OC != Last OC)
 */
void Uds_Dtc_Set_OperationCycle(uint8_t OCStatus)
{
    uint8_t fl_loopindex_u8 = UDS_DTC_ZERO;
    uint16_t fl_BlockID_u16 = (uint16_t)0;

    /*Set the Operation Cycle value for all DTCs*/
    for(fl_loopindex_u8 = UDS_DTC_ZERO; fl_loopindex_u8 < UDS_DTC_MAX_CFG; fl_loopindex_u8++)
    {

        /*Fetch Block ID information from cfg table with the loop index as reference*/
        fl_BlockID_u16 = Uds_Dtc_Process_TableConfig[fl_loopindex_u8].l_BlockID_u16;

        /*Read the Data from NvM for this DTC index*/
        Uds_Dtc_ReadMirrorData(fl_loopindex_u8);

        /*Check whether an operation cycle has been completed */
        if((OCStatus == UDS_DTC_OPERATION_CYCLE_STOP_CONDITION) && \
           (g_Uds_Dtc_NvmRecord_St[fl_loopindex_u8].l_currentOperationCycle_u8 == UDS_DTC_OPERATION_CYCLE_RUN_CONDITION))
        {

            /*Increment the operation counter since one cycle has been completed*/
            l_Uds_Dtc_MirrorNvmRecord_St.l_operationCycleCounter_u8 = g_Uds_Dtc_NvmRecord_St[fl_loopindex_u8].l_operationCycleCounter_u8 + UDS_DTC_INCREMENT_BY_ONE;

            /*Check for the status bit availability to set the bit accordingly*/
            if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TF_0TH))
            {
                /*Clear the 0th bit - testFailed */
                DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TF_0TH);
            }

            /*Check for the status bit availability to set the bit accordingly*/
            if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TFTOC_1ST))
            {
                /*Clear the 1st bit - testFailedThisOperationCycle */
                DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TFTOC_1ST);
            }

            /*Check if 1st & 6th bits are not TRUE - testNotCompletedThisOperationCycle & testFailedThisOperationCycle*/
            /*0x42 is the bitmask value of 1st & 6th bits*/
            if((g_Uds_Dtc_NvmRecord_St[fl_loopindex_u8].l_Uds_Dtc_StatusByte_u8 & (UDS_DTC_STATUS_BIT_TFTOC_1ST + UDS_DTC_STATUS_BIT_TNCTOC_6TH)) == UDS_DTC_ZERO)
            {
                /*Check for the status bit availability to set the bit accordingly*/
                if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_PDTC_2ND))
                {
                    /*Clear 2nd bit pendingDTC */
                    DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_PDTC_2ND);
                }
            }

            /*Check for the status bit availability to set the bit accordingly*/
            if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TNCTOC_6TH))
            {
                /*Set the 6th bit - testNotCompletedThisOperationCycle */
                DTC_SETBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TNCTOC_6TH);
            }
        }

        /*Assign the new status change in operation cycle*/
        l_Uds_Dtc_MirrorNvmRecord_St.l_currentOperationCycle_u8 = OCStatus;

        /*Preserve the current operation to last operation*/
        l_Uds_Dtc_MirrorNvmRecord_St.l_lastOperationCycle_u8 = l_Uds_Dtc_MirrorNvmRecord_St.l_currentOperationCycle_u8;

        /*Write DTC struct data by queuing */
        Uds_DtcData_WriteNvm(fl_BlockID_u16, fl_loopindex_u8);
    }
}

/*
* @brief    This API is used to Initialize an operation cycle related elements
* @param    NULL
* @return   NULL
*/
void Uds_Dtc_OperationCycle_Init(void)
{
    uint8_t fl_loopindex_u8 = UDS_DTC_ZERO;

    for(fl_loopindex_u8 = UDS_DTC_ZERO; fl_loopindex_u8 < UDS_DTC_MAX_CFG; fl_loopindex_u8++)
    {
        /*Check for the status bit availability to set the bit accordingly*/
        if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TF_0TH))
        {
            /*Clear the 0th bit - testFailed */
            DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TF_0TH);
        }

        /*Check for the status bit availability to set the bit accordingly*/
        if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TFTOC_1ST))
        {
            /*Clear the 1st bit - testFailedThisOperationCycle */
            DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TFTOC_1ST);
        }

        /*Check for the status bit availability to set the bit accordingly*/
        if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_PDTC_2ND))
        {
            /*Clear the 2nd bit - pendingDTC */
            DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_PDTC_2ND);
        }

        /*Check for the status bit availability to set the bit accordingly*/
        if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TFSLC_5TH))
        {
            /*Clear the 5th bit - testFailedSinceLastClear */
            DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TFSLC_5TH);
        }

        /*Check for the status bit availability to set the bit accordingly*/
        if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_TNCTOC_6TH))
        {
            /*Set the 6th bit - testNotCompletedThisOperationCycle */
            DTC_SETBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_TNCTOC_6TH);
        }

        /*Check for the status bit availability to set the bit accordingly*/
        if(DTC_TESTBIT(UDS_DTC_STATUS_AVAILABILITY_MASK, UDS_DTC_STATUS_BIT_WIR_7TH))
        {
            /*Clear the 7th bit - warningIndicatorRequested */
            DTC_CLEARBIT(l_Uds_Dtc_MirrorNvmRecord_St.l_Uds_Dtc_StatusByte_u8, UDS_DTC_STATUS_BIT_WIR_7TH);
        }

        l_Uds_Dtc_MirrorNvmRecord_St.l_confirmStage = UDS_DTC_INITIAL_MONITOR;
        l_Uds_Dtc_MirrorNvmRecord_St.l_lastOperationCycle_u8    = UDS_DTC_OPERATION_CYCLE_RUN_CONDITION;
        l_Uds_Dtc_MirrorNvmRecord_St.l_currentOperationCycle_u8 = UDS_DTC_OPERATION_CYCLE_STOP_CONDITION;
        /*Write Nvm Data by queuing*/
        Uds_DtcData_WriteNvm(Uds_Dtc_Process_TableConfig[fl_loopindex_u8].l_BlockID_u16, fl_loopindex_u8);
    }
}

/*
 * @brief    This API sets the FDC when a test is failed
 * @param    fl_dtcindex_u8 - DTC index value
 * @param    fl_FDCIncrmntResolution_u8 - Resolution to the increment value of FDC
 * @return   NULL
 */
void Uds_Dtc_Increment_FDC(uint8_t fl_dtcindex_u8, uint8_t fl_FDCIncrmntResolution_u8)
{
    /*Increment FDC as per resolution value*/
     l_Uds_Dtc_MirrorNvmRecord_St.l_Dtc_FaultDetectionCounter_u8 = g_Uds_Dtc_NvmRecord_St[fl_dtcindex_u8].l_Dtc_FaultDetectionCounter_u8 + fl_FDCIncrmntResolution_u8;
}

/*
 * @brief    This API decrements aging down counter when an OC completes with 3rd bit set
 * @param    fl_dtcindex_u8 - DTC index value
 * @param    fl_AgingDcrmntResolution_u8 - Resolution to the decrement value of Aging Counter
 * @return   NULL
 */
void Uds_Dtc_Decrement_AgingCounter(uint8_t fl_dtcindex_u8, uint8_t fl_AgingDcrmntResolution_u8)
{
    /*Decrement the aging counter if the counter has not matured already*/
    if(l_Uds_Dtc_MirrorNvmRecord_St.l_Dtc_Aging_DownCounter_u8 != UDS_DTC_ZERO)
    {
        /*Decrement Aging counter*/
        l_Uds_Dtc_MirrorNvmRecord_St.l_Dtc_Aging_DownCounter_u8 = g_Uds_Dtc_NvmRecord_St[fl_dtcindex_u8].l_Dtc_Aging_DownCounter_u8 - fl_AgingDcrmntResolution_u8;
    }
}

#endif
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.6                                                           
    REVISION DATE        : 25-August-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Conditional compilations provided                          
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.5                                                           
    REVISION DATE        : 08-August-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Compiler warnings fixed, macros given instead of magic numbers, comments updated                          
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.4
    REVISION DATE        : 22-July-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Below Internal Defects fixed:
                           1. Operation Cycle Counter update fixed - Uds_Dtc_Set_OperationCycle API. (#919)
                           2. Last DTC configured not updated - Read Pending status check in Uds_Dtc_MainFunction. (#913)
                           3. Aging Counter Decrementation to be taken care by application along with FDC.
                              Removed the implementation in Uds_Dtc_Set_OperationCycle.
                           4. Static Analysis completed.
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.3
    REVISION DATE        : 11-July-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Write Nvm done by queuing method.                                
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.2                                                           
    REVISION DATE        : 09-July-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : External Peer Review Comments fixed                               
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.1                                                           
    REVISION DATE        : 03-July-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Internal Peer Review Comments fixed  & Static Analysis done.                                
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.0                                                           
    REVISION DATE        : 26-June-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! UDS_DTC_C */
