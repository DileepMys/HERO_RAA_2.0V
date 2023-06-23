
#ifndef CANMGR_C_
#define CANMGR_C_
/**********************************************************************************************************************
 *   DISCLAIMER                                                                                                       
 *   Copyright (C) 2011, 2016 Niyata Infotech Ptv. Ltd. All rights reserved.                                             
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * @author              Author : Mahendran L (mahendranl@niyatainfotech.com)                                                                      
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *                                               F I L E  D E S C R I P T I O N                                      
 *--------------------------------------------------------------------------------------------------------------------
 *  @brief                                                                                                            
 *                                                                                                                    
 *  File name                       : CanMgr.c
 *  Version                         : V1.8.0
 *  Micros supported                : Micro Agnostic (Independent)
 *  Compilers supported             : XXXXX
 *  Platforms supported             : XXXXX
 *  Description                     : This file contains functions definitions of CanMgr
 *                                                                                                                    
 *                                                                                                                    
 *  @bug                                                                                                              
 *--------------------------------------------------------------------------------------------------------------------*/
/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *                                          I N C L U D E    F I L E S                                    
 ***********************************************************************************************************************/
#include "CanMgr.h"
#include "CanTp.h"
#include "CanTp_cfg.h"
#include "CanIF.h"
#include "TTMgr_Cfg.h"
#include "pin_mux.h"
#include "Cmp_Init.h"
#include "CanMgr_cfg.h"
#if(CHECKSUM_FEATURE_GLOBAL == STD_ON)
#include "Crc.h"
#endif
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S                                          
 ***********************************************************************************************************************/
/*
* @brief: This Macro defines the max length of the CAN Message
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define MAX_DLC_LENGTH (uint8_t)0x08


/*
* @brief: This Macro defines the mask value of 1st nibble of a byte
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define FRST_NIBBLE_MSK_VAL     (uint8_t)0x0F

/*
* @brief: This Macro defines the mask value of 2nd nibble of a byte
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define SCND_NIBBLE_MSK_VAL     (uint8_t)0xF0

/*
* @brief: This Macro defines length in one byte
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define LNGTH_ONE               (uint32_t)0x01


typedef enum
{
   TRAVERSE_FOR_SIGNAL_START = 0,
   TRAVERSE_FOR_THE_SIGNAL_END,
   MAX_SIGNAL_STATE
}CanMgr_Signal_Traverse_State_Type_En;


/*
* @brief: This variable is holds the bus off detected return status.
  @Unit:  N/A
  @Resolution: 1
  @Range: 0 - 4096
  @Applicability: YES
*/
uint8_t g_Bus_off_detected;




uint8_t g_Alive_Counter_data_u8;
/***********************************************************************************************************************/

/**********************************************************************************************************************
 *                             S T A T I C    V A R I A B L E S  D E F I N A T I O N S                                                      
 **********************************************************************************************************************/
/*
* @brief: This variable holds the status of CanMgr.
  @Unit:  N/A
  @Resolution: N/A
  @Range: CanMgr_StatusType
  @Applicability: YES
*/
static CanMgr_StatusType l_CanMgr_Status[CAN_TOTAL_NUMBER_OF_CHANNELS];

/*
* @brief: This variable holds the current mode of CanMgr.
  @Unit:  N/A
  @Resolution: N/A
  @Range: CanMgr_ModeType
  @Applicability: YES
*/
static CanMgr_ModeType l_CanMgr_Mode[CAN_TOTAL_NUMBER_OF_CHANNELS];

/*
* @brief: This variable holds the requested mode of CanMgr.
  @Unit:  N/A
  @Resolution: N/A
  @Range: CanMgr_ModeType
  @Applicability: YES
*/
static CanMgr_ModeType l_Requested_CanMgr_Mode[CAN_TOTAL_NUMBER_OF_CHANNELS];

/*
* @brief: This variable holds the CanTp message size.
  @Unit:  N/A
  @Resolution: N/A
  @Range: 0 - 4096
  @Applicability: YES
*/
static uint16_t l_CanMgr_CanTp_DataSize_u16;

/*
* @brief: This variable is reference to store the received message in the desired location.
  @Unit:  N/A
  @Resolution: N/A
  @Range: uint8_t pointer
  @Applicability: YES
*/
static uint8_t *l_CanTp_RxDataPtr;

CAN_Type * base;

CAN_Type * Get_base;

uint8_t Get_Can_base;

uint16_t Transmit_Diag_Error_Count_u16;

uint16_t Transmit_Vehicle_Error_Count_u16;
CanMgr_TxDataBuffer_t l_TxDataBuffer[CANMGR_MAX_NO_OF_TX_MSGS];
CanMgr_RxDataBuffer_t l_RxDataBuffer[CANMGR_MAX_NO_OF_RX_MSGS] ={{0xFF}, 0, 0, 0};

#if ((CANMGR_MESSAGE_MISSING_CALLBACK == STD_ON) || (CANMGR_ON_CHANGE_RECEPTION_CALLBACK == STD_ON))
/*
* @brief: This variable is holds the value of received signals.
  @Unit:  N/A
  @Resolution: N/A
  @Range: uint8_t pointer
  @Applicability: YES
*/
static float64 l_Rx_Signal_Data[MAX_RX_SIGNALS];
#endif
/*
* @brief: This variable is holds the PDU ID of RX CAN TP RX Message.
  @Unit:  N/A
  @Resolution: 1
  @Range: 0 - 4096
  @Applicability: YES
*/
static PduIdType l_CanMgr_CanTp_RxPduID;
/**********************************************************************************************************************
                                P R I V A T E    F U N C T I O N S    D E C L A R A T I O N                        
**********************************************************************************************************************/
/*
 * @Brief : This function copies the data to the global buffer
 * @param : SignalId 
 *          SignalDataPtr - pointer to the data to be
 *          length - length of the signal
 * @return: None
 */
static void CanMgr_DataBufferProcessing(CanMgr_SignalIdType SignalId, const uint8_t *SignalDataPtr, uint8_t length);

/*
 * @Brief : This function initializes data with Init value
 * @param : pointer to the data
 * @return: None
 */
static void CanMgr_InitMemory(const uint8_t *data);

/*
 * @Brief : This function initializes data with Init value
 * @param : pointer to the data
 * @return: None
 */
static void CanMgr_ClearDataBuffer(uint8_t *dataptr, uint8_t length);

#if (CANMGR_PERIODIC_MESSAGE_TRANSMISSION == STD_ON)
/*
 * @breif : This function is a period task and process the signals
 * @param : channel - CAN channel number
 * @return: None
 */
static void CanMgr_MainfunctionTx(uint8_t channel);
#endif

#if (CANMGR_MESSAGE_MISSING_CALLBACK == STD_ON)
/*
 * @breif : This function is a period task that monitors Rx messages
 * @param : channel - CAN channel number
 * @return: None
 */
static void CanMgr_MainfunctionRx(uint8_t channel);
#endif
/*
 * @breif : This service is used to get Checksum and Alive Counter Features details. 
 * @param : index - Message Index
 * @return: None
 */

static void CanMgr_Checksum_AliveCounter(uint8_t index);
/**********************************************************************************************************************
                                P U B L I C     F U N C T I O N S    D E F I N A T I O N S                             
***********************************************************************************************************************/

/*
 * @breif : This function initializes CanMgr
 * @param : None
 * @return: None
 */
void CanMgr_Init(void)
{
    uint16_t fl_TxDatabuffer_index_u16;
    uint16_t fl_RxDatabuffer_index_u16;
    uint8_t fl_index_u8;
    CanMgr_Signal_Traverse_State_Type_En fl_SignalGroupState_u8 = TRAVERSE_FOR_SIGNAL_START;
    uint16_t fl_Signal_Index_u16 = 0u;

    /*Initialize all the transmission_status as CANMGR_TX_STATUS_IDLE*/
    for (fl_TxDatabuffer_index_u16 = (uint16_t)0u; fl_TxDatabuffer_index_u16 < (uint16_t)CANMGR_MAX_NO_OF_TX_MSGS; fl_TxDatabuffer_index_u16++)
    {
        CanMgr_ClearDataBuffer(&l_TxDataBuffer[fl_TxDatabuffer_index_u16].data[0], MAX_DLC_LENGTH);
        l_TxDataBuffer[fl_TxDatabuffer_index_u16].transmission_status = CANMGR_TX_STATUS_IDLE;

        /*Initialize repetition counter */
        l_TxDataBuffer[fl_TxDatabuffer_index_u16].RepetitionCounter = (uint8_t)0;

        #if(ALIVE_COUNTER_FEATURE_GLOBAL == STD_ON)
        /*Initialize the alive counter variable*/
        l_TxDataBuffer[fl_TxDatabuffer_index_u16].Alive_Counter = (uint8_t)0xFF;
        #endif
         /* CHECK ALL THE SIGNALS CONFIGURED WHICH BELONGS TO THE MESSAGE INDEX REQUESTED */
         for(fl_Signal_Index_u16 = (uint16_t)0u; fl_Signal_Index_u16 < (uint16_t)MAX_TX_SIGNALS; fl_Signal_Index_u16++)
         {
            /* CHECK MESSAGE INDEX MATCHES THE MESSAGE LOOP INDEX */
            if(fl_TxDatabuffer_index_u16 == CanMgr_TxSignalInfoTable_t[fl_Signal_Index_u16].Message_Index)
            {
               /* CHECK FOR SIGNAL START INDEX */
               if(fl_SignalGroupState_u8 == TRAVERSE_FOR_SIGNAL_START)
               {
                  /* STORE THE START OF SIGNAL INDEX */
                  l_TxDataBuffer[fl_TxDatabuffer_index_u16].SignalStartIndex = fl_Signal_Index_u16;
                  /* INCREMENT THE SIGNAL VALUE AND THIS VARIBALE SHALL BE CONTINUE INCREMENT IN THE NEXT STATE */
                  ++l_TxDataBuffer[fl_TxDatabuffer_index_u16].NoOfSignals;
                  /* CHANGE THE STATE TO TRAVERSE THE NO OF LOOP */
                  fl_SignalGroupState_u8 = TRAVERSE_FOR_THE_SIGNAL_END;
               }
               else
               {
                  /* IF THE SIGNAL BELONGS TO THIS MESSAGE THIS THEN NO OF SIGNAL VALUE WILL BE INCREMENTED WITH 1 */
                  ++l_TxDataBuffer[fl_TxDatabuffer_index_u16].NoOfSignals;
               }
            }
         }
         /* CHANGE THE STATE FOR THE NEXT MESSAGE ITTERATION */
         fl_SignalGroupState_u8 = TRAVERSE_FOR_SIGNAL_START;
      }
    /*Initialize all the reception_status as MSG_NEVER_RECEIVED*/
    for (fl_RxDatabuffer_index_u16 = (uint16_t)0u; fl_RxDatabuffer_index_u16 < (uint16_t)CANMGR_MAX_NO_OF_RX_MSGS; fl_RxDatabuffer_index_u16++)
    {
        CanMgr_ClearDataBuffer(&l_RxDataBuffer[fl_RxDatabuffer_index_u16].data[0], MAX_DLC_LENGTH);
        l_RxDataBuffer[fl_RxDatabuffer_index_u16].reception_status = MSG_NEVER_RECEIVED;
        l_RxDataBuffer[fl_RxDatabuffer_index_u16].Reception_TimeoutCbk_required = (uint8_t)CANMGR_TRUE;

        #if(CHECKSUM_FEATURE_GLOBAL == STD_ON)
        /*Reset the CRC Error Debounce Counter value to 0 which will be incremented in the Rx indication*/
        l_RxDataBuffer[fl_RxDatabuffer_index_u16].CRC_Error_debounce_Counter = (uint8_t)0;

        /*Reload the CRC Error Recovery Debounce DOWN Counter value with the configured maximum value*/
        l_RxDataBuffer[fl_RxDatabuffer_index_u16].CRC_Error_Recovery_Debounce_Counter = \
        CanMgr_RxInfoTable[fl_RxDatabuffer_index_u16].checksum_error_recovery_counter;
        #endif

        #if(ALIVE_COUNTER_FEATURE_GLOBAL == STD_ON)
        /*Initialize the alive counter variable*/
        l_RxDataBuffer[fl_RxDatabuffer_index_u16].Alive_Cntr_Value = (uint8_t)0xFF; 

        /*Reset the Alive counter's Error Debounce Counter value to 0 which will be incremented in the Rx indication*/
        l_RxDataBuffer[fl_RxDatabuffer_index_u16].Alive_Cntr_Error_Debounce_Counter = (uint8_t)0;

        /*Reload the Alive counter's Error Recovery Debounce DOWN Counter value with the configured maximum value*/
        l_RxDataBuffer[fl_RxDatabuffer_index_u16].Alive_Cntr_Error_Recovery_Debounce_Counter = \
        CanMgr_RxInfoTable[fl_RxDatabuffer_index_u16].alive_error_recovery_counter;
        #endif
    }
    /*Initialize all channels*/
    for (fl_index_u8 = 0; fl_index_u8 < (uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS; fl_index_u8++)
    {
        l_CanMgr_Status[fl_index_u8] = CAN_MGR_INIT;
        /*Initializes all the message data with default values*/
        CanMgr_cfgInit();
        /*Initializes all the message data with default values*/
        CanMgr_InitMemory(INIT_DATA_VALUE);
        l_CanMgr_Mode[fl_index_u8] = CANMGR_FULL_COMMUNICATION;
        l_Requested_CanMgr_Mode[fl_index_u8] = CANMGR_IDLE;
    }
}

/*
 * @breif : This function Deinitializes CanMgr Channel specific
 * @param : p_Channel_u8 - CHANNEL INDEX SHALL BE PASSED HERE
 * @return: None
 */
uint8_t CanMgr_Channel_DeInit(uint8_t p_Channel_u8)
{
   /* LOCAL VARIABLES */
    uint16_t fl_TxDatabuffer_index_u16;
    uint16_t fl_RxDatabuffer_index_u16;
    uint8_t fl_Ret_u8 = E_OK;

   /* CHECK FOR VALID CHANNEL */
   if(p_Channel_u8 < (uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS)
   {
      /*Initialize all the transmission_status as CANMGR_TX_STATUS_IDLE */
      for (fl_TxDatabuffer_index_u16 = (uint16_t)0u; fl_TxDatabuffer_index_u16 < (uint16_t)CANMGR_MAX_NO_OF_TX_MSGS; fl_TxDatabuffer_index_u16++)
      {
         /* CHECK FOR THE CHANNEL MATCH IN ALL THE TX MESSAGES */
         if(CanMgr_TxInfoTable[fl_TxDatabuffer_index_u16].channel == p_Channel_u8)
         {
            /* CLEAR DATA IN THE BUFFER */
            CanMgr_ClearDataBuffer(&l_TxDataBuffer[fl_TxDatabuffer_index_u16].data[0], MAX_DLC_LENGTH);

            /* SET TRANSMISSION STATUS */
            l_TxDataBuffer[fl_TxDatabuffer_index_u16].transmission_status = CANMGR_TX_STATUS_IDLE;
         }
      }

      /*Initialize all the reception_status as MSG_NEVER_RECEIVED for the requested channel*/
      for (fl_RxDatabuffer_index_u16 = (uint16_t)0u; fl_RxDatabuffer_index_u16 < (uint16_t)CANMGR_MAX_NO_OF_RX_MSGS; fl_RxDatabuffer_index_u16++)
      {
         /* CHECK FOR THE CHANNEL MATCH - User_idx OBJECT REFERING THE CHANNEL */
         if(CanMgr_RxInfoTable[fl_RxDatabuffer_index_u16].User_idx == p_Channel_u8)
         {
            /* CLEAR MESSAGE BUFFER */
            CanMgr_ClearDataBuffer(&l_RxDataBuffer[fl_RxDatabuffer_index_u16].data[0], MAX_DLC_LENGTH);
            l_RxDataBuffer[fl_RxDatabuffer_index_u16].reception_status = MSG_NEVER_RECEIVED;
            l_RxDataBuffer[fl_RxDatabuffer_index_u16].Reception_TimeoutCbk_required = CANMGR_TRUE;
         }
      }
   }
   else
   {
      /* RETURN NOT OK - INVALID CHANNEL */
      fl_Ret_u8 = E_NOT_OK;
   }

   /* RETURN STATUS */
   return fl_Ret_u8;
}

/*
 * @breif : This function Deinitializes CanMgr
 * @param : None
 * @return: None
 */
void CanMgr_DeInit(void)
{
    uint16_t fl_TxDatabuffer_index_u16;
    uint16_t fl_RxDatabuffer_index_u16;
    uint8_t fl_index_u8;

    /*Initialize all the transmission_status as CANMGR_TX_STATUS_IDLE */
    for (fl_TxDatabuffer_index_u16 = (uint16_t)0u; fl_TxDatabuffer_index_u16 < (uint16_t)CANMGR_MAX_NO_OF_TX_MSGS; fl_TxDatabuffer_index_u16++)
    {
        CanMgr_ClearDataBuffer(&l_TxDataBuffer[fl_TxDatabuffer_index_u16].data[0], MAX_DLC_LENGTH);
        l_TxDataBuffer[fl_TxDatabuffer_index_u16].transmission_status = CANMGR_TX_STATUS_IDLE;
    }
    /*Initialize all the reception_status as MSG_NEVER_RECEIVED*/
    for (fl_RxDatabuffer_index_u16 = (uint16_t)0u; fl_RxDatabuffer_index_u16 < (uint16_t)CANMGR_MAX_NO_OF_RX_MSGS; fl_RxDatabuffer_index_u16++)
    {
        CanMgr_ClearDataBuffer(&l_RxDataBuffer[fl_RxDatabuffer_index_u16].data[0], MAX_DLC_LENGTH);
        l_RxDataBuffer[fl_RxDatabuffer_index_u16].reception_status = MSG_NEVER_RECEIVED;
        l_RxDataBuffer[fl_RxDatabuffer_index_u16].Reception_TimeoutCbk_required = CANMGR_TRUE;
    }
    /*De-Initialize all channels*/
    for (fl_index_u8 = 0; fl_index_u8 < (uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS; fl_index_u8++)
    {
        l_CanMgr_Status[fl_index_u8] = CAN_MGR_UNINIT;
    }
}

/*
 * @breif : This function returns CanMgr status [Initialized or Deinitialized]
 * @param : channel - CAN channel number
 * @return: CanMgr Status
 */
CanMgr_StatusType CanMgr_GetStatus(uint8_t channel)
{
    return (CanMgr_StatusType)l_CanMgr_Status[channel];
}

/*
 * @breif : This function is a period task and process the signals
 * @param : None
 * @return: None
 */
void CanMgr_Mainfunction(void)
{
	uint8_t fl_index_u8;
    /*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON

/* call the watch dog alive counter function*/
         CAN_MGR_ALIVE_COUNTER();
#endif

    /*Channel-wise iteration*/
    for (fl_index_u8 = 0; fl_index_u8 < (uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS; fl_index_u8++)
    {
        switch (l_CanMgr_Mode[fl_index_u8])
        {
        case CANMGR_FULL_COMMUNICATION_REQUESTED:
            /*Wait in this state until callback from for Netword request is received*/
            break;

        case CANMGR_FULL_COMMUNICATION:
#if (CANMGR_PERIODIC_MESSAGE_TRANSMISSION == STD_ON)
            /*Process all TX and RX messages*/
            CanMgr_MainfunctionTx(fl_index_u8);
#endif
#if (CANMGR_MESSAGE_MISSING_CALLBACK == STD_ON)
            CanMgr_MainfunctionRx(fl_index_u8);
#endif
            break;

        case CANMGR_NO_COMMUNICATION_REQUESTED:
            /*Sleep request has been received , process TX message once*/
#if (CANMGR_PERIODIC_MESSAGE_TRANSMISSION == STD_ON)
            CanMgr_MainfunctionTx(fl_index_u8);
#endif
            l_CanMgr_Mode[fl_index_u8] = CANMGR_NO_COMMUNICATION_PREPARE;
            break;

        case CANMGR_NO_COMMUNICATION_PREPARE:
            /*Request Network Sleep to CanIf*/
            if (CanIF_NetworkRequest(fl_index_u8, NETWORK_SLEEP) == E_OK)
            {
                l_CanMgr_Mode[fl_index_u8] = CANMGR_NO_COMMUNICATION;
            }
            else
            {
                l_CanMgr_Mode[fl_index_u8] = CANMGR_NO_COMMUNICATION_PREPARE;
            }
            break;

        case CANMGR_NO_COMMUNICATION:
            /*Deinitialize the RX and TX buffers*/

            /* INSTEAD OF CALLING WHOLE CHANNEL DEINIT - THIS SHALL BE USED TO DEINIT A CHANNEL'S SEPARTLY */
            (void)CanMgr_Channel_DeInit(fl_index_u8);

            /* MOVE THE STATE OF CAN CHANNEL TO IDLE */
            l_CanMgr_Mode[fl_index_u8] = CANMGR_IDLE;
            break;

        case CANMGR_SILENT_COMM_REQUESTED:

            /* Do Nothing, Wait here untill network reqeust confirmation
               is received */
            /* If Required action can be performed */
            break;

        case CANMGR_SILENT_COMMUNICATION:
            
            /* Do Nothing */
            /* If Required action can be performed */
            break;

        case CANMGR_IDLE:
            /*Do Nothing*/
            break;

        default:
            /*Do Nothing*/
            break;
        }
    }

}

/*
 * @breif : The service CanMgr_SendSignal updates the signal object identified by SignalId with
 *          the signal referenced by the SignalDataPtr parameter.
 * @param : SignalId : Id of signal to be sent
 *          SignalDataPtr : Reference to the signal data to be transmitted.
 * @return: E_OK: service has been accepted
 *          E_NOT_OK: Invalid SignalId
 */
uint8_t CanMgr_SendSignal(Tx_Msg_Id SignalId, const uint8_t *SignalDataPtr)
{
    /* LOCAL VARIBALES */
    uint8_t fl_ret_u8 = E_NOT_OK;
    uint8_t fl_index_u8 = 0u;
    uint16_t fl_SignalId_u16 = (uint16_t)SignalId;
    uint16_t fl_Signal_Index_u16 = (uint16_t)0u;
    uint8_t fl_signalindex_u8 = 0u;

    if (CANMGR_MAX_NO_OF_TX_MSGS <= SignalId)
    {
        fl_ret_u8 = E_NOT_OK;
    }
    else if (SignalDataPtr == NULL)
    {
        fl_ret_u8 = E_NOT_OK;
    }
    else
    {
        /*Channel-wise iteration*/
        for (fl_index_u8 = 0; fl_index_u8 < (uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS; fl_index_u8++)
        {
            /*Identify current channel*/
            if (CanMgr_TxInfoTable[SignalId].channel == fl_index_u8)
            {
                /* CHECK ALL THE SIGNALS CONFIGURED WHICH BELONGS TO THE MESSAGE INDEX REQUESTED */
                for(fl_Signal_Index_u16 = (uint16_t)0u; fl_Signal_Index_u16 < (uint16_t)MAX_TX_SIGNALS; fl_Signal_Index_u16++)
                {
                    /* CHECK FOR THE MATCH OF MESSAGE INDEX WITH THE SIGNAL CONFIGURED */
                    if((uint8_t)SignalId == CanMgr_TxSignalInfoTable_t[fl_Signal_Index_u16].Message_Index)
                    {
                         /* Here we have focus on ONCHANGE,ONWRITE details*/
                        switch((CanMgr_Signal_Type_En)CanMgr_TxSignalInfoTable_t[fl_Signal_Index_u16].Signal_SendType)
                        {   
                            /*If Frame Type is ONCHANGE or CYCLIC_ONCHANGE or ONCHANGE_REP send the Transmit indication to IF layer*/
                            case ONCHANGE         :
                            case CYCLIC_ONCHANGE  :
                                 /*Iteration loop to check whether at least one byte on the message frame has a data change*/
                                 for(fl_signalindex_u8 = (uint8_t)0u; fl_signalindex_u8 < (uint8_t)8u; fl_signalindex_u8++)
                                 {
                                    /*Check whether there is a data change by comparing the previous message frame and current frame*/
                                    if(SignalDataPtr[fl_signalindex_u8] != l_TxDataBuffer[fl_SignalId_u16].data[fl_signalindex_u8])
                                    {
                                        /* CHECK FOR THE COMMUNICATION CONTROL - SETTINGS */
                                        if(DiagGetTXCommControlSts(Normal_Communication_Msg) == 1)
                                        {
                                            /* PLACE REQUEST TO SEND THE MESSAGE FRAME */
                                            CanMgr_Send_Message(SignalId);
                                        }

                                       /* BREAK THE LOOP ONCE THERE CHANGE IN THE DATA FOUND */
                                       break;
                                    }
                                 }
                              break;
                            case ONCHANGE_REP     :
                                 /*Iteration loop to check whether at least one byte on the message frame has a data change*/
                                 for(fl_signalindex_u8 = (uint8_t)0u; fl_signalindex_u8 < (uint8_t)8u; fl_signalindex_u8++)
                                 {
                                    /*Check whether there is a data change by comparing the previous message frame and current frame*/
                                    if(SignalDataPtr[fl_signalindex_u8] != l_TxDataBuffer[fl_SignalId_u16].data[fl_signalindex_u8])
                                    {
                                       /* SET THE TRANSMISSION REQUEST FLAG */
                                       l_TxDataBuffer[fl_SignalId_u16].Transmission_Requested = 1U;

                                       /* CLEAR THE REPETATION COUNTER */
                                       l_TxDataBuffer[fl_SignalId_u16].RepetitionCounter = 0U;

                                       /* BREAK THE LOOP ONCE THERE CHANGE IN THE DATA FOUND */
                                       break;
                                    }
                                 }
                            break;
                            /*If Frame Type is ONWRITE or CYCLIC_ONWRITE send the Transmit indication to IF layer*/
                            case ONWRITE          :
                            case CYCLIC_ONWRITE   :
                                /* CHECK FOR THE COMMUNICATION CONTROL - SETTINGS */
                                if(DiagGetTXCommControlSts(Normal_Communication_Msg) == 1)
                                {
                                    /* PLACE REQUEST TO SEND THE MESSAGE FRAME */
                                    CanMgr_Send_Message(SignalId);
                                }
                              break;
                            case ONWRITE_REP:
                                 /* SET THE TRANSMISSION REQUEST FLAG */
                                 l_TxDataBuffer[fl_SignalId_u16].Transmission_Requested = 1U;

                                 /* CLEAR THE REPETATION COUNTER */
                                 l_TxDataBuffer[fl_SignalId_u16].RepetitionCounter = 0U;
                            break;
                            default   :
                            /*Do nothing */
                            break;
                        }
                    }
                    else
                       { 
                        /*Do nothing*/
                       }
                }

                /*Store Data in global buffer*/
                CanMgr_DataBufferProcessing((CanMgr_SignalIdType)fl_SignalId_u16, SignalDataPtr, (uint8_t)CanMgr_TxInfoTable[fl_SignalId_u16].length);

                fl_ret_u8 = E_OK;
            }
        }
    }
    return fl_ret_u8;
}

/*
 * @breif : The service CanMgr_SendSignal updates the signal object identified by SignalId with
 *          the signal referenced by the SignalDataPtr parameter.
 * @param : SignalId : Id of signal to be sent
 *          SignalDataPtr : Reference to the location where the received signal data shall be stored.
 * @return: E_OK: service has been accepted
 *          E_NOT_OK: Invalid SignalId
 */
uint8_t CanMgr_ReceiveSignal(Rx_Msg_Id SignalId, uint8_t *SignalDataPtr)
{
    uint8_t fl_ret_u8 = E_NOT_OK;
    uint8_t *fl_data_u8 = SignalDataPtr;
    uint16_t fl_index_u16;
    uint16_t fl_SignalId_u16 = (uint16_t)SignalId;
    uint8_t fl_index_u8;

    if (CANMGR_MAX_NO_OF_RX_MSGS <= SignalId)
    {
        fl_ret_u8 = E_NOT_OK;
    }
    else if (SignalDataPtr == NULL)
    {
        fl_ret_u8 = E_NOT_OK;
    }
    else
    {
        /*Channel-wise iteration*/
        for (fl_index_u8 = 0; fl_index_u8 <(uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS; fl_index_u8++)
        {
            /*Identify current channel*/
            if (CanMgr_RxInfoTable[SignalId].User_idx == fl_index_u8)
            {
                for (fl_index_u16 = 0; fl_index_u16 < (uint16_t)CanMgr_RxInfoTable[fl_SignalId_u16].length; fl_index_u16++)
                {
                    /* Copy the received data into the destination buffer*/
                    *fl_data_u8 = l_RxDataBuffer[fl_SignalId_u16].data[fl_index_u16];

                    /* Incrementing the pointer */
                    fl_data_u8++;
                }
                /* Update the receptions status to the return variable */
                fl_ret_u8 = l_RxDataBuffer[fl_SignalId_u16].reception_status;
            }
        }
    }
    return fl_ret_u8;
}

#if (CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : This function shall be used to transmit TP messages.
 * @param : SignalId : Id of signal to get the channel number
 * @param : MsgPtr - Reference to the signal data to be transmitted.
 *          Lenght - Lenght of the message to be transmitted.    
 * @return: E_OK / E_NOT_OK
 */
Std_ReturnType CanMgr_CanTp_Transmit(Tx_Msg_Id SignalId, uint8_t *fl_Msgptr, uint16_t length)
{
    Std_ReturnType fl_RetVal = E_OK;
    CanMgr_ModeType fl_CanMgr_Mode[CAN_TOTAL_NUMBER_OF_CHANNELS];
    uint8_t fl_channel_u8;

    /*Get the corresponding channel number for Signal ID*/
    fl_channel_u8 = CanMgr_TxInfoTable[SignalId].channel;
    /*Get the Current network mode*/
    fl_CanMgr_Mode[fl_channel_u8] = CanMgr_GetNetWorkMode(fl_channel_u8);

    /*Checks the network is in FULL COMM*/
    if (fl_CanMgr_Mode[fl_channel_u8] == CANMGR_FULL_COMMUNICATION)
    {
        if (fl_Msgptr != NULL)
        {
            /*Invoking TP layer for message transmission*/
            fl_RetVal = CanTp_Transmit(fl_Msgptr, length);
        }
        else
        {
            /*NULL pointer has been passed*/
            fl_RetVal = E_NOT_OK;
        }
    }
    else
    {
        /*CAN STACK is not in FULL COMM Mode Transmission cannot happen*/
        fl_RetVal = E_NOT_OK;
    }

    return fl_RetVal;
}
#endif

#if (CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : This function is used to get the CANTP transmit status.
 * @param : NONE
 * @return: Transmission in progress or completed
 */
uint8_t CanMgr_CanTp_Get_Transmit_Status(void)
{
    return CanTp_Get_Transmit_Status();
}
#endif

#if (CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : This function shall be used to cancel the ongoing TP transmission.
 * @param : NONE
 * @return: E_OK : Service is accepted
 *          E_NOT_OK Service is not accepted
 */
Std_ReturnType CanMgr_CanTp_CancelTransmit(void)
{
    return CanTp_CancelTransmit();
}
#endif

#if (CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : This function shall be used to cancel the ongoing TP reception.
 * @param : NONE
 * @return: E_OK : Service is accepted
 *          E_NOT_OK Service is not accepted
 */
Std_ReturnType CanMgr_CanTp_CancelReception(void)
{
    return CanTp_CancelReception();
}
#endif

/*
 * @breif : This function copies the data to the global buffer
 * @param : SignalId PDU Id of the transmitted signal
 * @return: Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED )
 */
uint8_t CanMgr_GetTransmissionStatus(Tx_Msg_Id SignalId)
{
    uint8_t fl_Tx_status_u8;
    uint16_t fl_index_u16 = (uint16_t)SignalId;

    /* Updating the TP transmission status to the return variable */
    fl_Tx_status_u8 = (uint8_t)l_TxDataBuffer[fl_index_u16].transmission_status;

    return fl_Tx_status_u8;
}

/*
 * @breif : The lower layer communication interface module confirms the transmission of a PDU,
 *          or the failure to transmit a PDU..
 * @param : TxPduId : Id of the signal that has been transmitted
 *          result  : E_OK: The PDU was transmitted.
 *                    E_NOT_OK: Transmission of the PDU failed.
 * @return: None
 */
void CanMgr_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    if (result != E_NOT_OK)
    {
        /*Update transmission status as TRANSMISSION_SUCCESS*/
        l_TxDataBuffer[TxPduId].transmission_status = CANMGR_TX_STATUS_SUCCESSFUL;
        l_TxDataBuffer[TxPduId].counter = (uint16_t)0;
    }
    else
    {
        /*Update transmission status as TRANSMISSION_FAILED*/
        l_TxDataBuffer[TxPduId].transmission_status = CANMGR_TX_STATUS_FAILED;
    }
}

/*
 * @breif : The lower layer communication interface module confirms the transmission of a PDU,
 *          or the failure to transmit a PDU..
 * @param : RxPduId : ID of the received PDU
 *          PduInfoPtr : Contains the length (SduLength) of the received PDU, a pointer to a
 *           buffer (SduDataPtr) containing the PDU, and the MetaData related to this PDU
 * @return: None
 */
void CanMgr_RxIndication(uint8_t RxPduId, const PduInfoType *PduInfoPtr)
{
    const uint8_t *fl_data_u8;
    uint8_t fl_index_u8;
    uint8_t fl_CRC_data_u8;
    
    uint8_t fl_loop_Idx;
    uint8_t fl_data_Buffer[8];

    uint8_t fl_Received_crc;
    uint8_t fl_Received_Alive_cntr;
    uint8_t  fl_Loop_var;
    uint16_t CAN_ID=0X131;


    fl_data_u8 = PduInfoPtr->SduDataPtr;
    boolean fl_Checksum_Matched_bool = (boolean)1;
   
   

 if (PduInfoPtr != NULL)
    {
        #if(CHECKSUM_FEATURE_GLOBAL == STD_ON)

        /*Check whether Checksum feature has been enabled for that particular ID*/
        if(CanMgr_RxInfoTable[RxPduId].checksum_enable == ((uint8_t)STD_ON))
        {

             /*Copy all the data to the local buffer in order to  clear only required bytes */
          
           for( fl_Loop_var=0;fl_Loop_var<8;fl_Loop_var++)
           {
               fl_data_Buffer[fl_Loop_var] = fl_data_u8[fl_Loop_var];
           }
     
          

        /* get CRC value from data Buffer  */
        fl_Received_crc = fl_data_Buffer[CanMgr_RxInfoTable[RxPduId].checksum_byte_pos];
        

        /*To Clear CRC byte*/
          fl_data_Buffer[CanMgr_RxInfoTable[RxPduId].checksum_byte_pos]=0;
       
          /*calculate CRC Value for received data*/

            uint8_t fl_calculated_checksum_u8 = (uint8_t)0;
            fl_calculated_checksum_u8 = Crc_CalculateCRC8(CanIf_RxPduConfig[RxPduId].RxPduCanIdOfRxPduConfig, &fl_data_Buffer[0], \
                                        (uint32_t)((uint32_t)CanMgr_RxInfoTable[RxPduId].length));

            /*Validation of the received checksum with the Rx calculated checksum*/
            if(fl_calculated_checksum_u8 == fl_Received_crc)
            {
                /*Received Checksum is valid & no data corruption*/
                fl_Checksum_Matched_bool = (boolean)1;

                /*Check whether a valid checksum has been received after Checksum error confirmation*/
                if(l_RxDataBuffer[RxPduId].CRC_Error_debounce_Counter == CanMgr_RxInfoTable[RxPduId].checksum_debounce_counter)
                {
                    /*Check whether error recovery counter has been made use of to start recovering based on debounce count*/
                    if(CanMgr_RxInfoTable[RxPduId].checksum_error_recovery_counter != (uint8_t)0)
                    {
                        /*Since error has been confirmed and not recovered, 
                        decrement the error recovery down counter*/
                        if(l_RxDataBuffer[RxPduId].CRC_Error_Recovery_Debounce_Counter != ((uint8_t)0))
                        {
                            l_RxDataBuffer[RxPduId].CRC_Error_Recovery_Debounce_Counter--;  
                            if(l_RxDataBuffer[RxPduId].CRC_Error_Recovery_Debounce_Counter == ((uint8_t)0))
                            {
                                /*Valid data received*/
                                l_RxDataBuffer[RxPduId].reception_status = MSG_RECEIVED;

                                /*Reset the error confirmation de-bounce counter to 0 since error recovery has happened*/
                                l_RxDataBuffer[RxPduId].CRC_Error_debounce_Counter = (uint8_t)0;

                                /*Reset the Error recovery de-bounce counter with initial value since it has been elapsed*/
                                l_RxDataBuffer[RxPduId].CRC_Error_Recovery_Debounce_Counter = \
                                CanMgr_RxInfoTable[RxPduId].checksum_error_recovery_counter;

                                /*Error Recovery callback to the application*/
                                CHECKSUM_ERROR_RECOVERY_CALLBACK(RxPduId, CanMgr_RxInfoTable[RxPduId].User_idx);
                            }
                        }
                    }
                    /*Error recovery not based on debounce counter. Recover from error immediately after receiving a valid value*/
                    else
                    {
                        /*Valid data received*/
                        l_RxDataBuffer[RxPduId].reception_status = MSG_RECEIVED;

                        /*Reset the error confirmation de-bounce counter to 0 since error recovery has happened*/
                        l_RxDataBuffer[RxPduId].CRC_Error_debounce_Counter = (uint8_t)0;

                        /*Error Recovery callback to the application*/
                        CHECKSUM_ERROR_RECOVERY_CALLBACK(RxPduId, CanMgr_RxInfoTable[RxPduId].User_idx);
                    }
                }
                /*Received valid checksum that doesn't have a history of error - recovery counter elapsed*/
                else 
                {
                    /*Valid data received*/
                    l_RxDataBuffer[RxPduId].reception_status = MSG_RECEIVED;
                }
            }
            else /*Checksum error*/
            {
                /*Reset all flags and counters*/
                fl_Checksum_Matched_bool = (boolean)0;

                CanMgr_RxInfoTable[RxPduId].timeout_counter = (uint16_t)0u;

                l_RxDataBuffer[RxPduId].Reception_TimeoutCbk_required = CANMGR_FALSE;

                /*Check whether CRC error is still debouncing and yet to be confirmed*/
                if(l_RxDataBuffer[RxPduId].CRC_Error_debounce_Counter != CanMgr_RxInfoTable[RxPduId].checksum_debounce_counter)
                {
                    /*Increment the Error Debounce Counter - until the error is confirmed*/
                    l_RxDataBuffer[RxPduId].CRC_Error_debounce_Counter++;

                    /*Check whether the Checksum Error Debounce counter has elapsed*/
                    if(l_RxDataBuffer[RxPduId].CRC_Error_debounce_Counter == \
                       CanMgr_RxInfoTable[RxPduId].checksum_debounce_counter)
                    {
                        /*CRC error confirmed based on debounce counter*/
                        l_RxDataBuffer[RxPduId].reception_status = RX_CRC_ERROR_CONFIRMED;

                        /*Checksum error confirmed since the Debounce count has reached - Call back to application*/
                        CHECKSUM_ERROR_CALLBACK(RxPduId, CanMgr_RxInfoTable[RxPduId].User_idx);
                    }
                }
                /*Error has been confirmed already and still active- just update the reception status*/
                else
                {
                    l_RxDataBuffer[RxPduId].reception_status = RX_CRC_ERROR_CONFIRMED;
                }
            }
        }
        else /*Checksum not enabled for this signal Id*/
        {
            /*Valid data received*/
            l_RxDataBuffer[RxPduId].reception_status = MSG_RECEIVED;      
        }
        #endif
        
        #if(ALIVE_COUNTER_FEATURE_GLOBAL == STD_ON)

            /*Check whether Alive Counter feature has been enabled for that particular ID
              & Checksum is valid. If checksum invalid - all data byets are considered as invalid. 
              hence no need to verify alive counter*/
            if((CanMgr_RxInfoTable[RxPduId].alive_counter_enable == (uint8_t)STD_ON) && (fl_Checksum_Matched_bool == (boolean)1))
            {
               /* get Alive Counter value from data Buffer  */
               fl_Received_Alive_cntr = fl_data_Buffer[CanMgr_RxInfoTable[RxPduId].alive_counter_byte_Pos];
              
              /*get the alive counter bit position in the byte - check dbc for reference*/
            fl_Received_Alive_cntr= fl_Received_Alive_cntr>>CanMgr_RxInfoTable[RxPduId].alive_counter_bit_pos;

           
        
           /*Check whether previously received alive counter and currently received alive counter value matches*/
                if(l_RxDataBuffer[RxPduId].Alive_Cntr_Value == fl_Received_Alive_cntr)
                {/*Repeated invalid alive counter - consider this usecase for Alive counter error debounce*/

                    /*Check whether the debounce is happening for the error to be confirmed*/
                    if(l_RxDataBuffer[RxPduId].Alive_Cntr_Error_Debounce_Counter != \
                        CanMgr_RxInfoTable[RxPduId].alive_debounce_counter)
                    {
                        /*If YES, increment the error debounce counter*/
                        l_RxDataBuffer[RxPduId].Alive_Cntr_Error_Debounce_Counter++;

                        /*Check whether the counter has elapsed with maximum value upon incrementing in this iteration*/
                        if(l_RxDataBuffer[RxPduId].Alive_Cntr_Error_Debounce_Counter == \
                           CanMgr_RxInfoTable[RxPduId].alive_debounce_counter)
                        {
                            /*Set status as error confirmed & give a call back*/
                            l_RxDataBuffer[RxPduId].reception_status = RX_ALIVE_CNTR_ERROR_CONFIRMED;

                            /*Store the reception status with error confirmed status and give a call back to application*/
                            ALIVE_COUNTER_ERROR_CALLBACK(RxPduId, CanMgr_RxInfoTable[RxPduId].User_idx);
                        }
                    }
                    /*Error has been confirmed already in previous iteration*/
                    else
                    {
                        l_RxDataBuffer[RxPduId].reception_status = RX_ALIVE_CNTR_ERROR_CONFIRMED;                           
                    }
                }
                /*ELSE, Received valid alive counter value and not repeated alive counter*/
                else
                {
                    /*Store the currently received alive counter value from the data frame for next iteration verification*/
                    l_RxDataBuffer[RxPduId].Alive_Cntr_Value = fl_Received_Alive_cntr;

                    /*Check whether a valid alive counter value has been received after an error has been confirmed 
                      for this particular Msg Id*/
                    if(l_RxDataBuffer[RxPduId].Alive_Cntr_Error_Debounce_Counter == \
                       CanMgr_RxInfoTable[RxPduId].alive_debounce_counter)
                    {
                        /*Check whether error recovery counter has been made use of to start recovering based on debounce count*/
                        if(CanMgr_RxInfoTable[RxPduId].alive_error_recovery_counter != (uint8_t)0)
                        {
                            /*If YES, Valid counter value means that Error recovery is happening*/
                            if(l_RxDataBuffer[RxPduId].Alive_Cntr_Error_Recovery_Debounce_Counter != (uint8_t)0)
                            {
                                /*Keep decrementing the error recovery debounce counter until it elapses to zero*/
                                l_RxDataBuffer[RxPduId].Alive_Cntr_Error_Recovery_Debounce_Counter--;

                                if(l_RxDataBuffer[RxPduId].Alive_Cntr_Error_Recovery_Debounce_Counter == (uint8_t)0)
                                {
                                    /*Recovered completely from the error. Set the status & give recovery call-back to application*/
                                    l_RxDataBuffer[RxPduId].reception_status = MSG_RECEIVED;
                                    ALIVE_COUNTER_ERROR_RECOVERY_CALLBACK(RxPduId, CanMgr_RxInfoTable[RxPduId].User_idx);

                                    /*Reset the error confirmation counter to zero since error has been recovered*/
                                    l_RxDataBuffer[RxPduId].Alive_Cntr_Error_Debounce_Counter = (uint8_t)0;

                                    /*Reset the Alive counter's error recovery counter to initial value since it has been completely recovered*/
                                    l_RxDataBuffer[RxPduId].Alive_Cntr_Error_Recovery_Debounce_Counter = \
                                    CanMgr_RxInfoTable[RxPduId].alive_error_recovery_counter;
                                }
                            }
                        }
                        /*Error recovery debounce counter not used. Recover from error immediately after receiving a vslid value*/
                        else
                        {
                            /*Recovered completely from the error. Set the status & give recovery call-back to application*/
                            l_RxDataBuffer[RxPduId].reception_status = MSG_RECEIVED;
                            
                            /*Reset the error confirmation counter to zero since error has been recovered*/
                            l_RxDataBuffer[RxPduId].Alive_Cntr_Error_Debounce_Counter = (uint8_t)0;

                            ALIVE_COUNTER_ERROR_RECOVERY_CALLBACK(RxPduId, CanMgr_RxInfoTable[RxPduId].User_idx);
                        }
                    }
                    else
                    {
                        /*Do nothing*/
                    }
                }
            }
            else
            {
                /*Do nothing - since Alive counter feature hasn't been enabled for this Msg Id 
                                        OR
                               Checksum error has occurred. Hence no need to verify alive counter.
                               All data bytes are corrupted*/
            }
        #endif

        #if((CHECKSUM_FEATURE_GLOBAL == STD_ON) || (ALIVE_COUNTER_FEATURE_GLOBAL == STD_ON))
        /*Update the data buffer with received data if the status is set*/
        if(l_RxDataBuffer[RxPduId].reception_status == MSG_RECEIVED)
        {
            for (fl_index_u8 = 0; fl_index_u8 < PduInfoPtr->SduLength; fl_index_u8++)
            {
                if (l_RxDataBuffer[RxPduId].data[fl_index_u8] != *fl_data_u8)
                {
                    l_RxDataBuffer[RxPduId].data[fl_index_u8] = *fl_data_u8;
                    /* update on change variable to true*/
                    l_RxDataBuffer[RxPduId].data_change = CANMGR_TRUE;
                }
                else
                {
                    /*Do Nothing*/
                }
                fl_data_u8++;
            }
            CanMgr_RxInfoTable[RxPduId].timeout_counter = (uint16_t)0;
            l_RxDataBuffer[RxPduId].Reception_TimeoutCbk_required = CANMGR_TRUE; 
        }
        #else /*Else, CHECKSUM & ALIVE COUNTER features disabled.*/
        for (fl_index_u8 = 0; fl_index_u8 < PduInfoPtr->SduLength; fl_index_u8++)
        {
            if (l_RxDataBuffer[RxPduId].data[fl_index_u8] != *fl_data_u8)
            {
                l_RxDataBuffer[RxPduId].data[fl_index_u8] = *fl_data_u8;
                /* update on change variable to true*/
                l_RxDataBuffer[RxPduId].data_change = CANMGR_TRUE;
            }
            else
            {
                /*Do Nothing*/
            }
            fl_data_u8++;
        }
        CanMgr_RxInfoTable[RxPduId].timeout_counter = (uint16_t)0u;
        l_RxDataBuffer[RxPduId].reception_status = MSG_RECEIVED;
        l_RxDataBuffer[RxPduId].Reception_TimeoutCbk_required = CANMGR_TRUE;
        //CanMgr_RxSignalDispatcher();

        #endif
    }
    else
    {
        /*Do Nothing*/
    }
}

#if (CANMGR_ON_CHANGE_RECEPTION_CALLBACK == STD_ON)
/*
 * @breif : This function is a Round Robin and process the received data and gives a callback when there is a change in
 *          received data
 * @param : None
 * @return: None
 */
void CanMgr_RxSignalDispatcher(void)
{
    uint16_t fl_index_1_u16;
    uint16_t fl_index_2_u16;
    static float64 fl_data_f64;
    uint8_t fl_index_u8;

    /*Channel-wise iteration*/
    for (fl_index_u8 = 0; fl_index_u8 <(uint8_t) CAN_TOTAL_NUMBER_OF_CHANNELS; fl_index_u8++)
    {
        /*Check for change in received data only when CAN MGR is in full communication mode*/
        if (l_CanMgr_Mode[fl_index_u8] == CANMGR_FULL_COMMUNICATION)
        {

            for (fl_index_1_u16 = 0; fl_index_1_u16 < (uint16_t)CANMGR_MAX_NO_OF_RX_MSGS; fl_index_1_u16++)
            {
                /*Change is received data is true*/
                if (l_RxDataBuffer[fl_index_1_u16].data_change == CANMGR_TRUE) 
                {
                    for (fl_index_2_u16 = 0; fl_index_2_u16 < (uint16_t)MAX_RX_SIGNALS; fl_index_2_u16++)
                    {
                        /*Checks if the signal belongs to the received message*/
                        if (Rx_Dispatcher[fl_index_2_u16].Message_Index == fl_index_1_u16)
                        {
                            (void)Rx_Dispatcher[fl_index_2_u16].Message_funcptr(&fl_data_f64);
                            /*Checks if there is any change in the received siganl*/
                            //if (fl_data_f64 != l_Rx_Signal_Data[fl_index_2_u16])
                            {
                                l_Rx_Signal_Data[fl_index_2_u16] = fl_data_f64;
                                if (RxCbk_SignalIndication_Table[fl_index_2_u16].Rx_SignalIndication_cbkFuncPtr != NULL)
                                {
                                    /*Give callback*/
                                    RxCbk_SignalIndication_Table[fl_index_2_u16].Rx_SignalIndication_cbkFuncPtr();
                                    l_RxDataBuffer[fl_index_1_u16].data_change = CANMGR_FALSE;
                                }
                                else
                                {
                                    l_RxDataBuffer[fl_index_1_u16].data_change = CANMGR_FALSE;
                                    /*No Callback function is configured*/
                                }
                            }
                            // else
                            // {
                            //     l_RxDataBuffer[fl_index_1_u16].data_change = CANMGR_FALSE;
                            //     /*No Change in the received data*/
                            // }
                        }
                        else
                        {
                            /*This is not the expected messgae index*/
                        }
                    }
                }
                else
                {
                    /*No Change in the received data*/
                }
            }
        }
        /*CAN Mgr not in Full-Comm mode*/
        else
        {
            /* Do Nothing */
        }
    }
}
#endif

/*
 * @breif : This function is used to put the CAN into sleep/Normal
 * @param	channel - CAN channel number
 * @param : State (CANMGR_FULL_COMM / CANMGR_NO_COMM)
 *          CANMGR_NO_COMM - Puts CAN into sleep    
 * @return: E_OK / E_NOT_OK
 */
Std_ReturnType CanMgr_SetNetworkMode(uint8_t channel, CanMgr_ModeType NetworkMode)
{
    uint8_t ret;
    CanMgr_ModeType Current_NetworkMode[CAN_TOTAL_NUMBER_OF_CHANNELS];

    /*Get current CanMgr mode for requested channel*/
    Current_NetworkMode[channel] = CanMgr_GetNetWorkMode(channel);

    /*Store the requested mode for requested channel*/
    l_Requested_CanMgr_Mode[channel] = NetworkMode;

    switch(Current_NetworkMode[channel])
    {
        case CANMGR_FULL_COMMUNICATION:

            if(l_Requested_CanMgr_Mode[channel] == CANMGR_FULL_COMMUNICATION)
            {
                /* Current mode and requested mode is same so no network change is required */                
                ret = E_OK;
            }
            else if(l_Requested_CanMgr_Mode[channel] == CANMGR_SILENT_COMMUNICATION)
            {

                /* Full Comm to Silent Comm Network change is requested */
                /* Changing the internal state machine state to Silent comm requested */
                if(CanIF_NetworkRequest(channel, NETWORK_SILENT) == E_OK)
                {
                    l_CanMgr_Mode[channel] = CANMGR_SILENT_COMM_REQUESTED;
                    ret = E_OK;
                }
                else
                {
                    /* Network request is not accepted by IF layer */
                    l_CanMgr_Mode[channel] = CANMGR_IDLE;
                    ret = E_NOT_OK;
                }
                
                ret = E_OK;
            }
            else if(l_Requested_CanMgr_Mode[channel] == CANMGR_NO_COMMUNICATION_REQUESTED)
            {
                /* Full Comm to No Comm Network change is requested */
                /* Changing the internal state machine state to No comm requested */

                if (CanIF_NetworkRequest(channel, NETWORK_SLEEP) == E_OK)
                {
                    l_CanMgr_Mode[channel] = CANMGR_NO_COMMUNICATION_REQUESTED;
                    ret = E_OK;
                }
                else
                {
                    l_CanMgr_Mode[channel] = CANMGR_IDLE;
                    ret = E_NOT_OK;
                }

            }
            else
            {
                /* Invalid Network Change request */
                ret = E_NOT_OK;
            }
        break;

        case CANMGR_NO_COMMUNICATION:

            if(l_Requested_CanMgr_Mode[channel] == CANMGR_FULL_COMMUNICATION)
            {
                
                /* No Comm to Full Comm Network Change is requested */
                /* Requesting the CanIF to put the canstack into Full Comm */
                if(E_OK == CanIF_NetworkRequest(channel, NETWORK_NORMAL))
                {
                    ret = E_OK;
                    /* Changing the internal state machine state to Full comm requested */
                    l_CanMgr_Mode[channel] = CANMGR_FULL_COMMUNICATION_REQUESTED;
                }
                else
                {
                    /* Network request is not accepted by IF layer */
                    ret = E_NOT_OK;
                    l_CanMgr_Mode[channel] = CANMGR_IDLE;
                }
                
            }
            else if(l_Requested_CanMgr_Mode[channel] == CANMGR_SILENT_COMMUNICATION)
            {                

                /* No Comm to Silent Comm Network Change is requested */
                /* Changing the internal state machine state to Silent comm requested*/
            	
                if(CanIF_NetworkRequest(channel, NETWORK_SILENT) == E_OK)
                {
                    l_CanMgr_Mode[channel] = CANMGR_SILENT_COMM_REQUESTED;
                    ret = E_OK;
                }
                else
                {
                    /* Network request is not accepted by IF layer */
                    l_CanMgr_Mode[channel] = CANMGR_IDLE;
                    ret = E_NOT_OK;
                }

                ret = E_OK;
            }
            else if(l_Requested_CanMgr_Mode[channel] == CANMGR_NO_COMMUNICATION_REQUESTED)
            {                                
                /* Current mode and requested mode is same so no network change is required */     
                ret = E_OK;
            }
            else
            {
                ret = E_NOT_OK;
            }        

        break;

        case CANMGR_SILENT_COMMUNICATION:

            if(l_Requested_CanMgr_Mode[channel] == CANMGR_FULL_COMMUNICATION)
            {
                /* Silent Comm to Full Comm Network change is requested */
                /* Requesting the CanIF to put the canstack into Full Comm */
                if(E_OK == CanIF_NetworkRequest(channel, NETWORK_NORMAL))
                {
                    ret = E_OK;
                    /* Changing the internal state machine state to Full comm requested */
                    l_CanMgr_Mode[channel] = CANMGR_FULL_COMMUNICATION_REQUESTED;
                }
                else
                {
                    /* Network request is not accepted by IF layer */
                    ret = E_NOT_OK;
                    l_CanMgr_Mode[channel] = CANMGR_IDLE;
                }
            }
            else if(l_Requested_CanMgr_Mode[channel] == CANMGR_SILENT_COMMUNICATION)
            {
                /* Current mode and requested mode is same so no network change is required */                                
                ret = E_OK;
            }
            else if(l_Requested_CanMgr_Mode[channel] == CANMGR_NO_COMMUNICATION_REQUESTED)
            {                
                /* Silent Comm to No Comm Network change is requested */
                /* Changing the internal state machine state to No Comm requested */
                if (CanIF_NetworkRequest(channel, NETWORK_SLEEP) == E_OK)
                {
                    l_CanMgr_Mode[channel] = CANMGR_NO_COMMUNICATION_REQUESTED;
                    ret = E_OK;
                }
                else
                {
                    l_CanMgr_Mode[channel] = CANMGR_IDLE;
                    ret = E_NOT_OK;
                }
            }
            else
            {
                ret = E_NOT_OK;
            }        

        break;

        case CANMGR_FULL_COMMUNICATION_REQUESTED:

        /* New Request is received while the previous request is in process 
           Try again after receiving network request confirmation cbk */

        ret = E_NOT_OK;

        break;

        case CANMGR_NO_COMMUNICATION_REQUESTED:

        /* New Request is received while the previous request is in process 
           Try again after receiving network request confirmation cbk */

        ret = E_NOT_OK;

        break;

        case CANMGR_NO_COMMUNICATION_PREPARE:

        /* New Request is received while the previous request is in process 
           Try again after receiving network request confirmation cbk */

        ret = E_NOT_OK;

        break;

        case CANMGR_SILENT_COMM_REQUESTED:

        /* New Request is received while the previous request is in process 
           Try again after receiving network request confirmation cbk */

        ret = E_NOT_OK;

        break;

        case CANMGR_IDLE:
            
            if(l_Requested_CanMgr_Mode[channel] == CANMGR_FULL_COMMUNICATION)
            {
                /* Full Comm  Mode is requested */
                /* Requesting the CanIF to put the canstack into Full Comm */
                if(E_OK == CanIF_NetworkRequest(channel, NETWORK_NORMAL))
                {
                    ret = E_OK;
                    /* Changing the internal state machine state to Full comm requested */
                    l_CanMgr_Mode[channel] = CANMGR_FULL_COMMUNICATION_REQUESTED;
                }
                else
                {
                    /* Network request is not accepted by IF layer */
                    ret = E_NOT_OK;
                    l_CanMgr_Mode[channel] = CANMGR_IDLE;
                }
            }
            else if(l_Requested_CanMgr_Mode[channel] == CANMGR_SILENT_COMMUNICATION)
            {

                /* Silent Comm  Mode is requested */                
                /* Changing the internal state machine state to Silent Comm Requested */
                if(CanIF_NetworkRequest(channel, NETWORK_SILENT) == E_OK)
                {
                    l_CanMgr_Mode[channel] = CANMGR_SILENT_COMM_REQUESTED;
                    ret = E_OK;
                }
                else
                {
                    /* Network request is not accepted by IF layer */
                    l_CanMgr_Mode[channel] = CANMGR_IDLE;
                    ret = E_NOT_OK;
                }
            }
            else if(l_Requested_CanMgr_Mode[channel] == CANMGR_NO_COMMUNICATION_REQUESTED)
            {
                /* No Comm  Mode is requested */ 
                /* Changing the internal state machine state to No Comm Requested */
                if (CanIF_NetworkRequest(channel, NETWORK_SLEEP) == E_OK)
                {
                    l_CanMgr_Mode[channel] = CANMGR_NO_COMMUNICATION_REQUESTED;
                    ret = E_OK;
                }
                else
                {
                    l_CanMgr_Mode[channel] = CANMGR_IDLE;
                    ret = E_NOT_OK;
                }
            }
            else
            {
                /* Invalid State */
                ret = E_NOT_OK;
            }

        break;

        default:

        /* Invalid State */
        ret = E_NOT_OK;

        break;
    }

    return ret;
}

/*
 * @breif : This function returns the state of CAN 
 * @param : channel - CAN channel number
 * @return: State -(CANMGR_FULL_COMM / CANMGR_NO_COMM)
 */
CanMgr_ModeType CanMgr_GetNetWorkMode(uint8_t channel)
{
    return l_CanMgr_Mode[channel];
}

/*
 * @breif : Callback function will be invoked by IF layer.
 * @param	channel - CAN channel number
 * @param : Result - contains the Network request result.
 * @return: None
 */
void CanMgr_NetworkRequestConfirmation(uint8_t channel, const uint8_t *Result)
{
    uint8_t NetworRequest_Result = *Result;
    CanMgr_ModeType CurrentNetworkMode = CanMgr_GetNetWorkMode(channel);

    /* If network request confirmation is received when CanMgr requested mode
        is IDLE then it is Remote Wakeup as no request is received from the
        Application */
    if ((l_Requested_CanMgr_Mode[channel] == CANMGR_IDLE) && (NetworRequest_Result == E_OK))
    {
#if (CANMGR_WAKEUP_INDICATION == STD_ON)
        CanMgr_WakeUpIndication(channel);
#endif
    }
    else
    {
        /* Switch to Can Mgr Current Mode */
        switch (CurrentNetworkMode)
        {
        case CANMGR_FULL_COMMUNICATION_REQUESTED:

            switch (NetworRequest_Result)
            {
                case E_OK:

                    /* Network request Change is successfull, Changing the mode
                       to FULL COMM */    
                    l_CanMgr_Mode[channel] = CANMGR_FULL_COMMUNICATION;

                    /* Clearing the requestd CanMgr Mode */
                    l_Requested_CanMgr_Mode[channel] = CANMGR_IDLE;

                    break;

                case E_NOT_OK:

                    /* Network request is not successfull */
                    /* Moving both CanMgr Mode and requested CanMgr mode to CANMGR IDLE */
                    l_CanMgr_Mode[channel] = CANMGR_IDLE;

                    l_Requested_CanMgr_Mode[channel] = CANMGR_IDLE;            

                    break;

            default:
                /*Do Nothing*/
                break;
            }

            break;
        case CANMGR_NO_COMMUNICATION:

            /* Do Nothing */

            break;
        case CANMGR_NO_COMMUNICATION_PREPARE:

            switch (NetworRequest_Result)
            {
                case E_OK:

                    /* Network request Change is successfull*/
                    l_CanMgr_Mode[channel] = CANMGR_NO_COMMUNICATION;

                    l_Requested_CanMgr_Mode[channel] = CANMGR_IDLE;
                    /*Do Nothing*/
    
                    break;
                case E_NOT_OK:

                    /* Network request is not successfull */
                    /* Moving both CanMgr Mode and requested CanMgr mode to CANMGR IDLE */

                    l_CanMgr_Mode[channel] = CANMGR_IDLE;

                    l_Requested_CanMgr_Mode[channel] = CANMGR_IDLE;

                    break;
                default:
                    /*Do Nothing*/
                    break;
            }

            break;
        case CANMGR_FULL_COMMUNICATION:
        
            /*Do Nothing*/
            break;
        case CANMGR_NO_COMMUNICATION_REQUESTED:
            /*Do Nothing*/
            break;
        case CANMGR_SILENT_COMM_REQUESTED:

            switch (NetworRequest_Result)
            {
                case E_OK:

                    if (l_Requested_CanMgr_Mode[channel] == CANMGR_SILENT_COMMUNICATION)
                    {
                        /* NetWork Request change is successful */
                        l_CanMgr_Mode[channel] = CANMGR_SILENT_COMMUNICATION;

                        l_Requested_CanMgr_Mode[channel] = CANMGR_IDLE;
                    }
                    else
                    {
                        /*Invalid Mode */
                        /* Network request is not successfull */
                        /* Moving both CanMgr Mode and requested CanMgr mode to CANMGR IDLE */
                        l_CanMgr_Mode[channel] = CANMGR_IDLE;

                        l_Requested_CanMgr_Mode[channel] = CANMGR_IDLE;                    
                    }
                    
                    break;
                case E_NOT_OK:

                    /* Network request is not successfull */
                    /* Moving both CanMgr Mode and requested CanMgr mode to CANMGR IDLE */

                    l_CanMgr_Mode[channel] = CANMGR_IDLE;

                    l_Requested_CanMgr_Mode[channel] = CANMGR_IDLE;

                    break;
                default:
                    /*Do Nothing*/
                    break;
            }

            break;
        case CANMGR_SILENT_COMMUNICATION:
            /*Do Nothing*/
            break;                            
        case CANMGR_IDLE:
            /*Do Nothing*/
            break;
        default:
            /*Do Nothing*/
            break;
        }

        if(APPLICATION_NETWORK_REQUEST_CBK_FUNC(channel,NetworRequest_Result) != NULL)
        {
            /* Network request confirmation CBK to application */
            APPLICATION_NETWORK_REQUEST_CBK_FUNC(channel,NetworRequest_Result);
        }

    }
}

#if (CANMGR_WAKEUP_INDICATION == STD_ON)
/*
 * @breif : Callback function will be invoked by IF layer when wakeup happens 
 * @param	channel - CAN channel number
 * @return: NONE
 */
void CanMgr_WakeUpIndication(uint8_t channel)
{
    CanMgr_Init();

    /*TO DO if required change the state of CAN_MGR.*/
    l_CanMgr_Mode[channel] = CANMGR_FULL_COMMUNICATION;

    /*Wakeup indication callback function*/
    APPLICATION_WAKEUP_CBK(channel);
}
#endif

/*
 * @breif : Callback function will be invoked by IF layer when busoff happens 
 * @param	channel - CAN channel number
 * @return: NONE
 */
void CanMgr_BusoffIndication(uint8_t channel)
{
    if(channel == 1)
    {
        /*Bus off has been detected */
        l_CanMgr_Mode[channel] = CANMGR_IDLE;
        
        
        /*Calling application callback fucntion to inform about bus off*/
        APPLICATION_BUSOFF_INDICATION(0);
      
    }
}

/*
 * @breif : Callback function will be invoked by IF layer when Errors happens
 * @param	channel - CAN channel number
 *          Error_Value- Error register value
 * @return: NONE
 */
void CanMgr_Error_State_Indication(uint32_t Channel,uint32_t Error_Value)
{
    /* CHECK FOR VALID  */
    if(APPLICATION_ERRORSTATE_INDICATION(Channel, Error_Value) != NULL)
    {
        /* Error Service Call back Function */
        APPLICATION_ERRORSTATE_INDICATION(Channel, Error_Value);
    }
}
/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON

/**
     * @brief    This function is used to get the Driver Watch dog Alive counter.
     * @param    None
     * @return   None
     * @note This function is called in Watch dog alive counter
     */
void CAN_DRV_INFORM_ALIVE_STATUS (void)
{
    /*Increment the counter value*/
      g_Drv_counter_u8++;
}
#endif
/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
/**
     * @brief    This function is used to get the IF Watch dog Alive counter.
     * @param   counter- get driver counter value
     * @return   None
     * @note This function is called in Watch dog alive counter
     */
void CAN_IF_INFORM_ALIVE_STATUS(void)
{
   /*Increment the counter value*/
    g_If_counter_u8++;    
}
#endif
/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
/**
     * @brief    This function is used to get the Manager Watch dog Alive counter.
     * @param   counter- get driver counter value
     * @return   None
     * @note This function is called in Watch dog alive counter
     */
void CAN_MGR_INFORM_ALIVE_STATUS(void)
{ 
   /*Increment the counter value*/
     g_Mgr_counter_u8++;  
}
#endif
/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
/**
     * @brief    This function is used to get the TP Watch dog Alive counter.
     * @param   counter- get driver counter value
     * @return   None
     * @note This function is called in Watch dog alive counter
     */
void CAN_TP_INFORM_ALIVE_STATUS(void)
{
    /*Increment the counter value*/
     g_Tp_counter_u8++;   
}
#endif
/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
/**
     * @brief    This function is used to get the status Watch dog Alive counter.
     * @param    None
     * @return   None
     * @note This function is called in Watch dog alive counter
     */
void CANMGR_Alive_Counter_Mainfunction(void)
{
    /*Check the all main functionvalue equal or not to timer value*/
    if(( MAX_DRV_CALL==g_Drv_counter_u8) &&(MAX_IF_CALL==g_If_counter_u8)&&(MAX_MGR_CALL==g_Mgr_counter_u8)&&(MAX_TP_CALL==g_Tp_counter_u8) )
    {
            /*reset the counter value*/
            g_Drv_counter_u8 =0;
            g_If_counter_u8 = 0;
            g_Mgr_counter_u8 = 0;
            g_Tp_counter_u8 = 0;

            /* CHECK FOR VALID FUNCTION */
            if(CAN_CONTROL_FLOW_STATUS() != NULL)
            {
                /*call the control flow status function*/
                CAN_CONTROL_FLOW_STATUS((uint8_t)CAN_CONTROL_FLOW_SUCCESS);
            }
    }
}
#endif
#if (CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : The lower layer communication interface module confirms the transmission of a message,
 *          or the failure to transmit a message..
 * @param : result  : E_OK: The message was transmitted.
 *                    E_NOT_OK: Transmission of the message failed.
 * @return: None
 */
void CanMgr_CanTp_Tx_Confirmation(Std_ReturnType TransmissionResult)
{
    /*Invoke Application callback function*/
    if (ApplCanTpTxConfirmation != NULL)
    {
        ApplCanTpTxConfirmation(TransmissionResult);
    }
}
#endif

#if (CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : The lower layer communication interface module indicates the upper layer on
 *          message reception
 * @param : result  : E_OK: The message was transmitted.
 *                    E_NOT_OK: Transmission of the message failed.
 * @return: None
 */
void CanMgr_CanTp_RxIndication(Std_ReturnType Result)
{
    /*The message was received successfully*/

    if (l_CanMgr_CanTp_RxPduID == (PduIdType)CANTP_RECEIVE_PHYS_PDU_ID_IC)
    {
        if (Appl_Phys_CanTpRxIndication != NULL)
        {
            if (Result == E_OK)
            {
                /*Invoking application callback function wiht result and received data length*/
                Appl_Phys_CanTpRxIndication(Result, l_CanMgr_CanTp_DataSize_u16);
            }
            else
            {
                /*Invoking application callback function wiht result as E_NO_OK and received data length as 0*/
                Appl_Phys_CanTpRxIndication(Result, 0x00);
            }
        }
        else
        {
            /*Do Nothing*/
        }
    }
    else if (l_CanMgr_CanTp_RxPduID == (PduIdType)CANTP_RECEIVE_PHYS_PDU_ID_IC)
    {
        if (Appl_Func_CanTpRxIndication != NULL)
        {
            if (Result == E_OK)
            {
                /*Invoking application callback function with result and received data length*/
                Appl_Func_CanTpRxIndication(Result, l_CanMgr_CanTp_DataSize_u16);
            }
            else
            {
                /*Invoking application callback function wiht result as E_NO_OK and received data length as 0*/
                Appl_Func_CanTpRxIndication(Result, 0x00);
            }
        }
        else
        {
            /*Do Nothing*/
        }
    }
    else
    {
        /*Do Nothing*/
    }
}
#endif

#if (CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : This service shall be used by TP layer to get the reference of application data buffer
 *          to store the data on message reception.
 * @param : PduId: SiganlID
 *          PduIdLength : Total lenght of the message
 * @return: E_OK : Service accepted
 *          E_NOT_OK : Conditions not met.    
 */
Std_ReturnType CanMgr_CanTpStartOfReception(PduIdType PduId, uint16_t PduIdLength)
{
    Std_ReturnType RetValue;

    /*For future purpose*/
    (void)PduId;
    /*Clear the data length on TP message reception*/
    l_CanMgr_CanTp_DataSize_u16 = 0;

    l_CanMgr_CanTp_RxPduID = PduId;

    if (PduId == (PduIdType)CANTP_RECEIVE_PHYS_PDU_ID_IC)
    {
        if (Appl_Phys_CanTpRxGetBuffer != NULL)
        {
            /*Get the application data reference to store the incoming data*/
            l_CanTp_RxDataPtr = (uint8_t *)Appl_Phys_CanTpRxGetBuffer(PduIdLength);

            if (l_CanTp_RxDataPtr != NULL)
            {
                RetValue = E_OK;
            }
            else
            {
                /*NULL data pointer*/
                RetValue = E_NOT_OK;
            }
        }
        else
        {
            /*NULL data pointer*/
            RetValue = E_NOT_OK;
        }
    }
    else if (PduId == (PduIdType)CANTP_RECEIVE_FUNC_PDU_ID)
    {
        if (Appl_Func_CanTpRxGetBuffer != NULL)
        {
            /*Get the application data reference to store the incoming data*/
            l_CanTp_RxDataPtr = (uint8_t *)Appl_Func_CanTpRxGetBuffer(PduIdLength);

            if (l_CanTp_RxDataPtr != NULL)
            {
                RetValue = E_OK;
            }
            else
            {
                /*NULL data pointer*/
                RetValue = E_NOT_OK;
            }
        }
        else
        {
            /*NULL data pointer*/
            RetValue = E_NOT_OK;
        }
    }
    else
    {
        /*NULL function pointer ,  no application function is mapped*/
        RetValue = E_NOT_OK;
    }

    return RetValue;
}
#endif

#if (CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : This service shall be used by TP layer to update the received 
 *          data.
 * @param : MsgPtr: refernce to the received data
 *          size_u8 : Size of received data
 * @return: None
 *           
 */
void CanMgr_CanTpRxInProgress(const uint8_t *MsgPtr, uint8_t size_u8)
{
    uint8_t fl_index_u8;
    /*Check is passed reference data pointer is NULL or not*/
    if (MsgPtr != NULL)
    {
        /*This loop copies the received data into application data buffer*/
        for (fl_index_u8 = 0; fl_index_u8 < size_u8; fl_index_u8++)
        {
            l_CanTp_RxDataPtr[l_CanMgr_CanTp_DataSize_u16] = *MsgPtr;
            MsgPtr++;
            l_CanMgr_CanTp_DataSize_u16++;
        }
    }
    else
    {
        /*NULL Pointer has been passed*/
        /*Do Nothing*/
    }
}
#endif

/**********************************************************************************************************************
                                P R I V A T E     F U N C T I O N S    D E F I N A T I O N S                             
***********************************************************************************************************************/
/*
 * @breif : This function copies the data to the global buffer
 * @param : SignalId 
 *          SignalDataPtr - pointer to the data to be
 *          length - length of the signal
 * @return: None
 */
static void CanMgr_DataBufferProcessing(CanMgr_SignalIdType SignalId, const uint8_t *SignalDataPtr, uint8_t length)
{
    uint8_t fl_index;
    const uint8_t *dataPtr = SignalDataPtr;

    /* Null Pointer Check */
    if (dataPtr != NULL)
    {
        /* Iterating the loop based on the message length*/
        for (fl_index = ((uint8_t)0); fl_index < length; fl_index++)
        {
            /* Copy the data into CanMgr buffer */
            l_TxDataBuffer[SignalId].data[fl_index] = *dataPtr;
            
            /* Incrementing the pointer */
            dataPtr++;
        }
    }
}

/*
 * @breif : This function initializes data with Init value
 * @param : pointer to the data
 * @return: None
 */
static void CanMgr_InitMemory(const uint8_t *data)
{
    uint16_t fl_index_1_u8;
    uint8_t fl_index_2_u8;
    const uint8_t *fl_data = data;

    /* Null Pointer Check */
    if (fl_data != NULL)
    {
        /* Iterating the loop for maximum number of Tx Messages */
        for (fl_index_1_u8 = 0; fl_index_1_u8 < (uint16_t)CANMGR_MAX_NO_OF_TX_MSGS; fl_index_1_u8++)
        {
             /* Iterating the loop based on the message length*/
            for (fl_index_2_u8 = 0; fl_index_2_u8 < (uint8_t)CanMgr_TxInfoTable[fl_index_1_u8].length; fl_index_2_u8++)
            {
                /* Updating the siganl init values data into canmgr buffer */
                l_TxDataBuffer[fl_index_1_u8].data[fl_index_2_u8] = *fl_data;
                
                /* Incrementing the pointer */
                fl_data++;
            }
        }
    }
    else
    {
        /*Do Nothing*/
    }
}

/*
 * @Brief : This function initializes data with Init value
 * @param : pointer to the data
 * @return: None
 */
static void CanMgr_ClearDataBuffer(uint8_t *dataptr, uint8_t length)
{
    uint8_t fl_index;
    uint8_t *fl_dataPtr = (uint8_t *)dataptr;
    
    /* Null Pointer Check*/
    if (fl_dataPtr != NULL)
    {
        /* Iterate the loop based on the length*/
        for (fl_index = 0; fl_index < length; fl_index++)
        {
            /* Clear the buffer (Filling it with Zeros */
            *fl_dataPtr = (uint8_t)0xFFu;
            
            /* Incrementing the pointer*/
            fl_dataPtr++;
        }
    }
    else
    {
        /*Do Nothing*/
    }
}
/*
 * @breif : This service is used to get Checksum and Alive Counter Features details. 
 * @param : index - Message Index
 * @return: None
 */
static void CanMgr_Checksum_AliveCounter(uint8_t index)
{
    #if(ALIVE_COUNTER_FEATURE_GLOBAL == STD_ON)
    if(CanMgr_TxInfoTable[index].alive_counter_enable == (uint8_t)STD_ON)
    {

        /*Check whether the alive counter has been initialized and not sent any msgs for this Id previously*/
        if(l_TxDataBuffer[index].Alive_Counter == (uint8_t)0xFF)
        {
            /*Load the alive counter with the minimum value as per the configurations*/
            l_TxDataBuffer[index].Alive_Counter = CanMgr_TxInfoTable[index].alive_counter_rollback_min_val;
        }
        /*Check whether the alive counter has reached maximum value*/
        else if(l_TxDataBuffer[index].Alive_Counter == CanMgr_TxInfoTable[index].alive_counter_rollback_max_val)
        {
            /*If yes, roll back the counter to its minimum value as per the configurations*/
            l_TxDataBuffer[index].Alive_Counter = CanMgr_TxInfoTable[index].alive_counter_rollback_min_val;
        }
        /*Alive counter has starting running and some where in between minimum and maximum value*/
        else
        {
            /*Yet to reach maximum value, hence increment the counter*/
            l_TxDataBuffer[index].Alive_Counter++;
        }

        /*Mask the second nibble of 1st index*/
        l_TxDataBuffer[index].data[1] = (l_TxDataBuffer[index].data[1] & SCND_NIBBLE_MSK_VAL);

        /*Set the Alive counter's value to the 1st nibble of 1st data index (as per Frame format)*/
        l_TxDataBuffer[index].data[1] |= l_TxDataBuffer[index].Alive_Counter;

    }
    else
    {
        /*Do nothing since alive counter feature isn't enabled for this Id in this system*/
    }
    #endif

    #if (CHECKSUM_FEATURE_GLOBAL == STD_ON)

    /*Check whether Checksum feature has been enabled for this Id in the system*/
    if((CanMgr_TxInfoTable[index].checksum_enable == (uint8_t)STD_ON))
    { 
        /*Checksum feature enabled for this Id, hence calculate checksum for the given data pointer*/
        uint8_t fl_calculated_checksum_u8 = (uint8_t)0;
        fl_calculated_checksum_u8 = Crc_CalculateCRC8(CanIf_TxPduConfig[index].CanIdOfTxPduConfig,&l_TxDataBuffer[index].data[1], \
                                                    (uint32_t)((uint32_t)CanMgr_TxInfoTable[index].length - LNGTH_ONE));

        l_TxDataBuffer[index].data[0] = fl_calculated_checksum_u8;
    }
    else /*Checksum feature not enabled for this Id in the system*/

    {
        /*Do nothing*/
    }
    #else /* Else, CHECKSUM_FEATURE_GLOBAL is DISABLED. This system doesn't have checksum feature*/
                        /*Do nothing*/
    #endif
}

#if (CANMGR_PERIODIC_MESSAGE_TRANSMISSION == STD_ON)
/*
 * @breif : This function is a period task and process the signals
 * @param	channel - CAN channel number
 * @return: None
 */
static void CanMgr_MainfunctionTx(uint8_t channel)
{
   uint16_t fl_index = 0;
   uint16_t fl_Signal_Index_u16 = (uint16_t)0u;
   uint16_t fl_NoOfSignals_NeedToCheck_u16 = 0u;
   boolean fl_Is_Msg_Tx_Required_Bool = (boolean)FALSE;

   for (fl_index = 0u; fl_index < (uint16_t)CANMGR_MAX_NO_OF_TX_MSGS; fl_index++)
   {
      /*Identify the channel to be Txed*/
      if ((CanMgr_TxInfoTable[fl_index].channel) == channel)
      {
         /*Transmission status check shall be performed irrespective of the message type*/
         /* Previous transmission was successful moving this the status to IDLE */
         if(l_TxDataBuffer[fl_index].transmission_status == CANMGR_TX_STATUS_SUCCESSFUL)
         {
            l_TxDataBuffer[fl_index].transmission_status = CANMGR_TX_STATUS_IDLE;
         }

         /* Since there is no TX confirmation for 10ms moving the TX status to IDLE
         or
         Pervious tranmssion request has been failed moving the transmission status to IDLE */
         else if((l_TxDataBuffer[fl_index].transmission_status == CANMGR_TX_STATUS_IN_MAILBOX) || (l_TxDataBuffer[fl_index].transmission_status == CANMGR_TX_STATUS_FAILED))
         {
               l_TxDataBuffer[fl_index].transmission_status = CANMGR_TX_STATUS_IDLE;
               
               /*Resetting the counter to zero since pervious transmission is failed or tx confirmation is not received*/
               l_TxDataBuffer[fl_index].counter = (uint16_t)0;
         }
         else
         {
               /*Do Nothing*/
         }

         /*Increment the counter*/
         l_TxDataBuffer[fl_index].counter = l_TxDataBuffer[fl_index].counter + CANMGR_MAINFUNCTION_PERIOD;

         fl_NoOfSignals_NeedToCheck_u16 = (l_TxDataBuffer[fl_index].NoOfSignals + l_TxDataBuffer[fl_index].SignalStartIndex);

         /* CHECK ALL THE SIGNALS CONFIGURED WHICH BELONGS TO THE MESSAGE INDEX REQUESTED */
         for(fl_Signal_Index_u16 = l_TxDataBuffer[fl_index].SignalStartIndex; fl_Signal_Index_u16 <= fl_NoOfSignals_NeedToCheck_u16; fl_Signal_Index_u16++)
         {
            /* CHECK FOR THE MATCH OF MESSAGE INDEX WITH THE SIGNAL CONFIGURED */
            if(fl_index == CanMgr_TxSignalInfoTable_t[fl_Signal_Index_u16].Message_Index)
            {
               /* Here we have focus on Cyclic,IfActive,IfActive/Onchange/Onwrite with Repition details*/
               switch((CanMgr_Signal_Type_En)CanMgr_TxSignalInfoTable_t[fl_Signal_Index_u16].Signal_SendType)
               {
                  case EVENT_SIGNAL:
                    /* CHECK FOR THE TRANSMISSION REQUESTED FOR THIS MESSAGE */
                    if(l_TxDataBuffer[fl_index].Transmission_Requested == TRUE)
                    {
                        /* SET TRANSMISSION FLAG */
                        fl_Is_Msg_Tx_Required_Bool = TRUE;
                        l_TxDataBuffer[fl_index].Transmission_Requested = FALSE;
                    }
                  break;
                  /* Check the frame type of message - CYCLIC, CYCLIC_ONWRITE, CYCLIC_ONCHANGE*/
                  case CYCLIC          :
                  case CYCLIC_ONWRITE  :
                  case CYCLIC_ONCHANGE :
                     /* Check whether message periodicity has occurred */
                     if ((l_TxDataBuffer[fl_index].counter >= (uint16_t)CanMgr_TxInfoTable[fl_index].period))
                     {
                        /* SET TRANSMIT FLAG */
                        fl_Is_Msg_Tx_Required_Bool = TRUE;
                        l_TxDataBuffer[fl_index].counter = 0;
                     }
                  break;
                  /* Check the frame type of message - ONCHANGE_REP, ONWRITE_REP*/     
                  case ONCHANGE_REP    :
                  case ONWRITE_REP     :
                     /* CHECK FOR THE TRANSMISSION REQUESTED FOR THIS MESSAGE */
                     if(l_TxDataBuffer[fl_index].Transmission_Requested == TRUE)
                     {
                        /* Check whether message fast cycle periodicity has occurred */
                        if((l_TxDataBuffer[fl_index].counter >= (uint16_t)CanMgr_TxInfoTable[fl_index].FastPeriodTime))
                        {
                           /* CHECK REPETATION COUNT ACHIEVED */
                           if(l_TxDataBuffer[fl_index].RepetitionCounter < CanMgr_TxInfoTable[fl_index].Msg_NumberOfRepetition)
                           {
                              /* SET TRANSMIT FLAG */
                              fl_Is_Msg_Tx_Required_Bool = TRUE;

                              /*Increment the Counter to its maximum value one by one upon each iteration*/
                              l_TxDataBuffer[fl_index].RepetitionCounter++;
                           }
                           else /* COMES HERE ONCE THE REPETATION COUNTER REACHES MAXIMUM COUNTER */
                           {
                              /* CLEAR THE TRANSMISSION FLAG */
                              l_TxDataBuffer[fl_index].Transmission_Requested = FALSE;

                              /* CLEAR THE REPEATAION COUNTER */
                              l_TxDataBuffer[fl_index].RepetitionCounter = 0U;
                           }
                        }
                     }
                  break;
                  /*Message Type - IfActive / Cyclic IfActive*/
                  case IFACTIVE        :
                     /*Check the status of the signal whether it is active/inactive*/
                     if(CanMgr_TxSignalInfoTable_t[fl_Signal_Index_u16].SignalIfActiveFlag == TRUE)
                     {
                        /* Check whether message fast cycle periodicity has occurred */
                        if((l_TxDataBuffer[fl_index].counter >= (uint16_t)CanMgr_TxInfoTable[fl_index].FastPeriodTime))
                        {
                           /* SET TRANSMISSION FLAG */
                           fl_Is_Msg_Tx_Required_Bool = TRUE;
                        }
                     }
                  break;
                  case CYCLIC_IFACTIVE :
                     /*Check the status of the signal whether it is active/inactive*/
                     if(CanMgr_TxSignalInfoTable_t[fl_Signal_Index_u16].SignalIfActiveFlag == TRUE)
                     {
                        /* Check whether message fast cycle periodicity has occurred */
                        if((l_TxDataBuffer[fl_index].counter >= (uint16_t)CanMgr_TxInfoTable[fl_index].FastPeriodTime))
                        {
                           /* SET TRANSMISSION FLAG */
                           fl_Is_Msg_Tx_Required_Bool = TRUE;
                        }
                     }
                     else
                     {
                        /* Check whether message cycle periodicity has occurred */
                        if((l_TxDataBuffer[fl_index].counter >= (uint16_t)CanMgr_TxInfoTable[fl_index].period))
                        {
                           /* SET TRANSMISSION FLAG */
                           fl_Is_Msg_Tx_Required_Bool = TRUE;
                        }
                     }
                  break;
                  default:
                  break;
               }

               /* CHECK FOR THE MESSAGE TRANSMIT FLAG RISED */
               if(fl_Is_Msg_Tx_Required_Bool == TRUE)
               {
                  /* CLEAR THE FLAG FOR THE NEXT MESSAGE CHECK */
                  fl_Is_Msg_Tx_Required_Bool = FALSE;

                  if(DiagGetTXCommControlSts(Normal_Communication_Msg) == 1)
                  {
                    /* PLACE REQUEST TO SEND THE MESSAGE FRAME */
                    CanMgr_Send_Message(fl_index);
                  }

                  /* BREAK THE LOOP - ONCE MESSAGE SEND (SIGNAL LOOP SHALL BE BREAKED - THIS WILL SKIP THE SEARCHING OF NEXT SIGNAL IN THIS MESSAGE)*/
                  break;
               }
            }
         }/* END OF SIGNAL PARSING IN A MESSAGE */
      }/* END OF NUMBER OF CAN CHANNEL PARSING */
   }/* END OF MESSAGE PARSING IN THE TOTAL MESSAGE LIST */
}
#endif


/*
 * @breif : This function shall be used to pre-job before send.
 * @param	p_Message_Index_u16 - Message list enumuration index shall be given as parameter.
 * @return: None
 */
void CanMgr_Send_Message(uint16_t p_Message_Index_u16)
{
   /* LOCAL VARIABLE */
   static PduInfoType TxPduInfoPtr;

   /* SET THE TRANSMISSION FLAG STATUS  - REQUESTED */
   l_TxDataBuffer[p_Message_Index_u16].transmission_status = CANMGR_TX_STATUS_REQUESTED;

   /* CHECKSUM AND ALIVE COUNTER CALCULATION */
   CanMgr_Checksum_AliveCounter(p_Message_Index_u16);

   /* SET THE LENGTH OF THE MESSAGE */
   TxPduInfoPtr.SduLength = (uint16_t)CanMgr_TxInfoTable[p_Message_Index_u16].length;

   /*Load the Sdu data pointer with data*/
   TxPduInfoPtr.SduDataPtr = &l_TxDataBuffer[p_Message_Index_u16].data[0];

   /*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
   /*call local buffer*/
   CAN_Get_buffer(&TxPduInfoPtr);
#endif
   /* CHECK FOR THE SUCCESSFULL MESSAGE REQUEST PLACED */
   if((Std_ReturnType)E_OK == CanIf_Transmit(p_Message_Index_u16, &TxPduInfoPtr))
   {
      /*Transmission request has been accepted, so moving the status to CANMGR_TX_STATUS_IN_MAILBOX*/
      l_TxDataBuffer[p_Message_Index_u16].transmission_status = CANMGR_TX_STATUS_IN_MAILBOX;
   }
   else
   {
      /*Transmission request is not accepted, so moving the status to CANMGR_TX_STATUS_FAILED*/
      l_TxDataBuffer[p_Message_Index_u16].transmission_status = CANMGR_TX_STATUS_FAILED;
   }
}



#if (CANMGR_MESSAGE_MISSING_CALLBACK == STD_ON)
/*
 * @breif : This function is a period task that monitors Rx messages
 * @param	channel - CAN channel number
 * @return: None
 */
static void CanMgr_MainfunctionRx(uint8_t channel)
{
    uint16_t fl_index;
    uint16_t fl_index_u16;

    for (fl_index = 0; fl_index < (uint16_t)CANMGR_MAX_NO_OF_RX_MSGS; fl_index++)
    {
        /*Identification of the channel to be Rxed */
        if ((CanMgr_RxInfoTable[fl_index].User_idx) == channel)
        {
            /*Increment the counter*/
            CanMgr_RxInfoTable[fl_index].timeout_counter = CanMgr_RxInfoTable[fl_index].timeout_counter + 1;
            /*Check for message timeout*/
        
           if (CanMgr_RxInfoTable[fl_index].timeout <= CanMgr_RxInfoTable[fl_index].timeout_counter)
            { /*Timeout happened*/
                if (l_RxDataBuffer[fl_index].Reception_TimeoutCbk_required == CANMGR_TRUE)
                {
                    l_RxDataBuffer[fl_index].Reception_TimeoutCbk_required = CANMGR_FALSE;

                    for (fl_index_u16 = 0; fl_index_u16 < (uint16_t)MAX_RX_SIGNALS; fl_index_u16++)
                    {
                        /*Finding the signals belonging to that message*/
                        if (Rx_ReceptionTimeoutCbk_Table[fl_index_u16].Message_Index == fl_index)
                        {
                            if (Rx_ReceptionTimeoutCbk_Table[fl_index_u16].RxSignal_ReceptionTimeout_cbkFuncPtr != NULL)
                            {
                                /*Update the Rx data buffer using safe values since Rx timeout error has been confirmed*/
                                memcpy(&l_RxDataBuffer[fl_index].data[0], \
                                       &CanMgr_RxInfoTable[fl_index].msg_default_safe_value, \
                                       8);
                                       //
                                /*Invoking Timeout callback function*/
                                Rx_ReceptionTimeoutCbk_Table[fl_index_u16].RxSignal_ReceptionTimeout_cbkFuncPtr();
                            }
                            /*Clearing the signal data when signal is missing*/
                            l_Rx_Signal_Data[fl_index_u16] = (float64)(0);
                        }
                    }

                    //
                }
                else
                {
                    /*Do Nothing*/
                }

                if(l_RxDataBuffer[fl_index].reception_status != MSG_NEVER_RECEIVED )
                {
                    l_RxDataBuffer[fl_index].reception_status = MSG_MISSING;
                    /*Clearing the message data as timeout happened*/
                    CanMgr_ClearDataBuffer(&l_RxDataBuffer[fl_index].data[0], MAX_DLC_LENGTH);
                }
                else
                {
                    /*Do Nothing*/
                }
            }
            else
            {
                /*Do Nothing*/
            }
        }
    }
}
#endif

/*
 * @breif : This function is used for can bus off indication
 * @param	channel - CAN channel number
 * @return: None
 */
void App_Can_bus_off_indication(uint8_t BusOff)
{
    uint8_t BusOff_Status_u8;

    BusOff_Status_u8 = BusOff;

    switch (BusOff_Status_u8)
    {
    case VEHICLE_BUS_OFF_DETECTED:
       g_Bus_off_detected = 1;
        break;
    
    case DIAG_BUS_OFF_DETECTED:
        g_Bus_off_detected = 2;
        break;
    case BUSOFF_NOT_DETECTED:
        g_Bus_off_detected = 0;
    default:
    
        break;
    }


}

void clear_Can1_Busoff(void)
{
    if(g_Bus_off_detected == 1)
    {
        g_Bus_off_detected = 0;
    }
}

void clear_Can2_Busoff(void)
{
    if(g_Bus_off_detected == 2)
    {
        g_Bus_off_detected = 0;
    }
}

/*
 * @breif : This function is used for bus off indication
 * @param	void
 * @return: g_Bus_off_detected
 */
uint8_t App_Can_bus_off_Get_indication(void)
{
    return g_Bus_off_detected;
}

void Can_Bus_WakeUp_Notification(uint8_t channel)
{
   uint8_t Wake_ack = 1;
}


/**********************************************************************************************************************
 *                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/
#ifdef __cplusplus
}
#endif
/**********************************************************************************************************************
 *                                                R E V I S I O N   H I S T O R Y             
***********************************************************************************************************************
     REVISION NUMBER      : V1.8.0
     REVISION DATE        : 29/12/2021
     CREATED / REVISED BY : Karthikeyan vijayan(v.karthikeyan@niyatainfotech.com)
     DESCRIPTION          : Implementent Functional Safety Features
-------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.7.9
     REVISION DATE        : 15/11/2021
     CREATED / REVISED BY : Rajasekar T(rajasekar@niyatainfotech.com)
     DESCRIPTION          : Implementent Functional Safety Features
-------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.7.8
     REVISION DATE        : 28/08/2021
     CREATED / REVISED BY : Rajasekar T(rajasekar@niyatainfotech.com)
     DESCRIPTION          : Silent Mode (Listen only mode) Feature code is integrated(Taken from SPT Branch).
-------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.7.7
     REVISION DATE        : 25/08/2020
     CREATED / REVISED BY : Rajasekar T(rajasekar@niyatainfotech.com)
     DESCRIPTION          : Tx methods features implemented for Signal based.
-------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.7.6
     REVISION DATE        : 11/08/2020
     CREATED / REVISED BY : Sharmili N(sharmili@niyatainfotech.com)
     DESCRIPTION          : Additional Tx methods implemented
-------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.7.5
     REVISION DATE        : 18/03/2020
     CREATED / REVISED BY : Sharmili N(sharmili@niyatainfotech.com)
     DESCRIPTION          : Checksum and Alive counter - Static analysis & defect fixed
-------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.7.4
     REVISION DATE        : 08/03/2020
     CREATED / REVISED BY : Sharmili N(sharmili@niyatainfotech.com)
     DESCRIPTION          : Checksum and Alive counter - code optimized
-------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.7.3
     REVISION DATE        : 28/09/2020
     CREATED / REVISED BY : Sharmili N(sharmili@niyatainfotech.com)
     DESCRIPTION          : Checksum and Alive counter - internal PR comments addressed
-------------------------------------------------------------------------------------
**********************************************************************************************************************
     REVISION NUMBER      : V1.7.2
     REVISION DATE        : 28/09/2020
     CREATED / REVISED BY : Sharmili N(sharmili@niyatainfotech.com)
     DESCRIPTION          : Checksum and Alive counter features implemented
-------------------------------------------------------------------------------------
**********************************************************************************************************************
     REVISION NUMBER      : V1.0.3
     REVISION DATE        : 30/09/2020
     CREATED / REVISED BY : prabhu R(prabhu.r@niyatainfotech.com)
     DESCRIPTION          : All states(IDEL,REQUESTED MAILBOX,SUCCESSFUL,FAILED,)are updated in ( init ,CanMgr_SendSignal,CanMgr_Mainfunctiontx )functions.
-------------------------------------------------------------------------------------
**********************************************************************************************************************
     REVISION NUMBER      : V1.0.3
     REVISION DATE        : 28/09/2020
     CREATED / REVISED BY : prabhu R(prabhu.r@niyatainfotech.com)
     DESCRIPTION          : Updated the TX status for can timing issue Defect fix in Multi-Channel can stack
-------------------------------------------------------------------------------------
**********************************************************************************************************************
     REVISION NUMBER      : V1.7.1                                                                                   
     REVISION DATE        : 28/07/2020                                                                               
     CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)                                        
     DESCRIPTION          : Bootloader Conditional compilation added.
                            Comments added and configurations mapped.                                                                            
---------------------------------------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.7.0                                                                                   
     REVISION DATE        : 28/07/2020                                                                               
     CREATED / REVISED BY : Bakyaraj (bakyaraj@niyatainfotech.com)                                        
     DESCRIPTION          : Multi - Channel support implemented.                                                                            
---------------------------------------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.6.0                                                                                   
     REVISION DATE        : 30/05/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : MISRA fix                                                                             
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.5.0
     REVISION DATE        : 14/05/2020                                                                               
     CREATED / REVISED BY : Pavithra R(Pavithra.r@niyatainfotech.com)                                        
     DESCRIPTION          : Physical and functional condition been added in CanstartofReceiption and CanMgr_CanTp_RxIndication                                                                        
---------------------------------------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.4.0                                                                                   
     REVISION DATE        : 06/04/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : CAN TP functions MISRA FIX                                                                          
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.3.0                                                                                   
     REVISION DATE        : 01/04/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : CAN TP functions implemented                                                                           
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.2.0                                                                                   
     REVISION DATE        : 14/03/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : MISRA fix                                                                             
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.1.0                                                                                   
     REVISION DATE        : 20/02/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : Implemented: RX callback only when there is change in received data
                                         Reception timeout callback (Never received and Missing)                                                                             
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.0.1                                                                                   
     REVISION DATE        : 13/02/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : Implemented set network mode and netwoek request confirmation                                                                          
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.0.0                                                                                   
     REVISION DATE        : 30/01/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : Initial version                                                                          
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
#endif /* CANMGR_C_*/
