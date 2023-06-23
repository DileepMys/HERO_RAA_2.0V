/*********************************************************************************************************************** 
 *    DISCLAIMER                                                                                                        
 *   Copyright (C) 2011, 2016 Niyata Infotech Ptv. Ltd. All rights reserved.                                              
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * @author              Author : Akshay Bavalatti (akshayb@niyatainfotech.com)                                                                         
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N                                           
 *---------------------------------------------------------------------------------------------------------------------
 *  @brief                                                                                                             
 *                                                                                                                     
 *  File name                       : CanIF.c                                                                        
 *  Version                         : V1.0.4
 *  Micros supported                : Micro Agnostic (Independant)                                                            
 *  Compilers supported             : XXXX                                                                           
 *  Platforms supported             : XXXX                                                                            
 *  Description                     : This file contains precompile configuration settings for CanIF                                 
 *                                                                                                                     
 *                                                                                                                     
 *  @bug                                                                                                               
 *---------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *                          I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "CanIF.h"
#include "CanMgr.h"
#include "CanTp.h"
#include "Cmp_Init.h"
#include "fsl_common.h"
#include "CanMgr_cfg.h"
#include "hal_stdtypes.h"
#include "MIMXRT1172.h"
#include "CanGateway.h"
#include "fsl_flexcan.h"
/***********************************************************************************************************************
 *                         M  A   C   R   O
 ***********************************************************************************************************************/

#define WAKEUP_E_OK        E_OK
#define SLEEP_E_OK         E_OK
#define WAKEUP_E_NOT_OK    E_NOT_OK
#define SLEEP_E_NOT_OK     E_NOT_OK
#define SILENT_MODE_OK     E_OK
#define SILENT_MODE_NOT_OK E_NOT_OK 
#define WAKEUP_BY_BUS      E_OK

# define CANIF_FDFLAG           0x4000u

#ifdef CANIF_BASIC_CAN

#define CANIF_CFG_STOPIDX_2_MAPPEDTXBUFFERS(Index)                         (CanIf_CanIfCtrlId2MappedTxBuffersConfig[(Index)].EndIdx_MappedTxBuffersConfig)
#define CANIF_CFG_STARTIDX_2_MAPPEDTXBUFFERS(Index)                        (CanIf_CanIfCtrlId2MappedTxBuffersConfig[(Index)].StartIdx_MappedTxBuffersConfig)
#define CANIF_CFG_MAPPEDTXBUFFERS(Index)                                   (CanIf_MappedTxBuffersConfig[(Index)].MailBoxConfigIdxOfMappedTxBuffersConfig)
#define CanIf_GetTxBufferPrioByCanIdBase(Index)                            (CanIf_TxBufferPrioByCanIdBase.raw[(Index)])
#define CANIF_VAR_TXBUFFERPRIOBYCANID_BUFFERBASE(index, field)             CanIf_GetTxBufferPrioByCanIdBase(index).field 
#define CANIF_CFG_BUFFERBASEIDX_TXBUFFERPRIOBYCANIDBYTEQUEUE(Index)        (CanIf_TxBufferPrioByCanIdByteQueueConfig[(Index)].BaseIdx_TxBufferPrioByCanId)
#define CANIF_CFG_STOPIDX_TXBUFFERPRIOBYCANIDBYTEQUEUE(Index)              (CanIf_TxBufferPrioByCanIdByteQueueConfig[(Index)].EndIdx_TxBufferPrioByCanIdByteQueueMappedTxPdus)
#define CANIF_CFG_QUEUESIZE_TXBUFFERPRIOBYCANIDBYTEQUEUE(Index)            (CanIf_TxBufferPrioByCanIdByteQueueConfig[(Index)].Length_TxBufferPrioByCanIdByteQueueMappedTxPdus)
#define CANIF_CFG_STARTIDX_TXBUFFERPRIOBYCANIDBYTEQUEUE(Index)             (CanIf_TxBufferPrioByCanIdByteQueueConfig[(Index)].StartIdx_TxBufferPrioByCanIdByteQueueMappedTxPdus)
#define CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_MAPPEDTXPDUS(Index)         (CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus[(Index)].TxPduConfigIdxOfTxBufferPrioByCanIdByteQueueMappedTxPdus)
#define CANIF_CFG_TX_QUEUEINDEX(Index)                                     (CanIf_TxPduQueueIndex[(Index)].TxQueueIdxOfTxPduQueueIndex)
#define CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(index, field)                  (CanIf_TxQueue.raw[(index)]).field
#define CanIf_SetTxBufferPrioByCanIdBase(Index, Value)                     CanIf_TxBufferPrioByCanIdBase.raw[(Index)] = (Value)
#define CanIf_SetTxQueue(Index, Value)                                     CanIf_TxQueue.raw[(Index)] = (Value)
#define CanIf_SetTxQueueCounter(index, value)                              (CanIf_GetTxBufferPrioByCanIdBase(index).eQueueCounter = (value))
#define CANIF_CFG_MAILBOX_TXBUFFERIDX(Index)                               (CanIf_MailBoxConfig[(Index)].TxBufferCfgIdxOfMailBoxConfig)
#define CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE(Index)                      (CanIf_MailBoxConfig[(Index)].TxBufferHandlingTypeOfMailBoxConfig)
#define CANIF_CFG_MAILBOX_PDUIDFIRST(Index)                                (CanIf_MailBoxConfig[(Index)].PduIdFirstOfMailBoxConfig)

#endif


#define CANIF_CFG_CTRLMODEINDICATIONFCT                                   (CanIf_CtrlModeIndicationFctPtr)
#define CanIf_GetCtrlMode(Index)                                           (CanIf_CtrlStates.raw [(Index)].CtrlModeOfCtrlStates)
#define CanIf_GetChannelMode(Index)                                        (CanIf_CtrlStates.raw [(Index)].PduModeOfCtrlStates)
#define CANIF_CFG_MAILBOX_CONTROLLER(Index)                                (CanIf_MailBoxConfig[(Index)].CtrlStatesIdxOfMailBoxConfig)
#define CANIF_CFG_MAILBOX_MAILBOXTYPE(Index)                               (CanIf_MailBoxConfig[(Index)].MailBoxTypeOfMailBoxConfig)
#define CANIF_CFG_MAILBOX_PDUIDLAST(Index)                                 (CanIf_MailBoxConfig[(Index)].PduIdLastOfMailBoxConfig)
#define CANIF_CFG_RXINDICATION_FUNCTION(Index)                             (CanIf_RxIndicationFctList[(Index)].RxIndicationFctOfRxIndicationFctList)
#define CANIF_CFG_FUNCTIONLAYOUT_OF_RXINDICATION(Index)                    (CanIf_RxIndicationFctList[(Index)].RxIndicationLayoutOfRxIndicationFctList)
#define CANIF_CFG_RX_DLC(Index)                                            (CanIf_RxPduConfig[(Index)].DlcOfRxPduConfig)
#define CANIF_CFG_RX_RXINDICATION(Index)                                   (CanIf_RxPduConfig[(Index)].RxIndicationFctListIdxOfRxPduConfig)
#define CANIF_CFG_RX_CANID(Index)                                          (CanIf_RxPduConfig[(Index)].RxPduCanIdOfRxPduConfig)
#define CANIF_CFG_RX_MASK(Index)                                           (CanIf_RxPduConfig[(Index)].RxPduMaskOfRxPduConfig)
#define CANIF_CFG_RX_UPPERPDUID(Index)                                     (CanIf_RxPduConfig[(Index)].UpperPduIdOfRxPduConfig)
#define CANIF_CFG_TXCONFIRMATION(Index)                                    (CanIf_TxConfirmationFctList[(Index)])
#define CANIF_CFG_TX_CANID(Index)                                          (CanIf_TxPduConfig[(Index)].CanIdOfTxPduConfig)
#define CANIF_CFG_TX_MASK(Index)                                           (CanIf_TxPduConfig[(Index)].TxPduMaskofTxPduConfig)
#define CANIF_CFG_TX_DLC(Index)                                            (CanIf_TxPduConfig[(Index)].DlcOfTxPduConfig)
#define CANIF_CFG_TX_HTH(Index)                                            (CanIf_TxPduConfig[(Index)].MailBoxConfigIdxOfTxPduConfig)
#define CANIF_CFG_TX_TXCONFIRMATION(Index)                                 (CanIf_TxPduConfig[(Index)].TxConfirmationFctListIdxOfTxPduConfig)
#define CANIF_CFG_TX_UPPERLAYERTXPDUID(Index)                              (CanIf_TxPduConfig[(Index)].UpperLayerTxPduIdOfTxPduConfig)
#define CANIF_CFG_TX_CONTROLLER(Index)                                     (CanIf_TxPduConfig[(Index)].CtrlStatesIdxOfTxPduConfig)


#define CanIf_SetCtrlModeOfCtrlStates(Index, Value)                   CanIf_CtrlStates.raw [(Index)].CtrlModeOfCtrlStates = (Value)
#define CanIf_SetPduModeOfCtrlStates(Index, Value)                    CanIf_CtrlStates.raw [(Index)].PduModeOfCtrlStates = (Value)

#define CanIf_SetChannelMode(index, value)                            CanIf_SetPduModeOfCtrlStates((index), (value))       

#define CanIf_SetCtrlMode(Index, Value)                               CanIf_SetCtrlModeOfCtrlStates(Index, Value)


volatile bool txComplete = false;
volatile bool rxComplete = false;
volatile bool wakenUp    = false;

#define CANIF_CFG_BUSOFFNOTIFICATION(x)                                     CanIf_BusOffNotificationFctPtr(x)
#define CANIF_CFG_TX_UPPERLAYERTXPDUID(Index)                              (CanIf_TxPduConfig[(Index)].UpperLayerTxPduIdOfTxPduConfig)
#define CANIF_CFG_TX_CONTROLLER(Index)                                     (CanIf_TxPduConfig[(Index)].CtrlStatesIdxOfTxPduConfig)
#define CanIf_GetCtrlMode(Index)                                           (CanIf_CtrlStates.raw [(Index)].CtrlModeOfCtrlStates)
#define CanIf_GetChannelMode(Index)                                        (CanIf_CtrlStates.raw [(Index)].PduModeOfCtrlStates)
#define CANIF_CFG_TX_CANID(Index)                                          (CanIf_TxPduConfig[(Index)].CanIdOfTxPduConfig)
#define CANIF_CFG_TX_HTH(Index)                                            (CanIf_TxPduConfig[(Index)].MailBoxConfigIdxOfTxPduConfig)
#define CANIF_CFG_RXINDICATION_FUNCTION(Index)                             (CanIf_RxIndicationFctList[(Index)].RxIndicationFctOfRxIndicationFctList)
#define CANIF_CFG_FUNCTIONLAYOUT_OF_RXINDICATION(Index)                    (CanIf_RxIndicationFctList[(Index)].RxIndicationLayoutOfRxIndicationFctList)


#define CANIF_CFG_RX_DLC(Index)                                            (CanIf_RxPduConfig[(Index)].DlcOfRxPduConfig)
#define CANIF_CFG_RX_RXINDICATION(Index)                                   (CanIf_RxPduConfig[(Index)].RxIndicationFctListIdxOfRxPduConfig)
#define CANIF_CFG_RX_CANID(Index)                                          (CanIf_RxPduConfig[(Index)].RxPduCanIdOfRxPduConfig)
#define CANIF_CFG_RX_MASK(Index)                                           (CanIf_RxPduConfig[(Index)].RxPduMaskOfRxPduConfig)
#define CANIF_CFG_RX_UPPERPDUID(Index)                                     (CanIf_RxPduConfig[(Index)].UpperPduIdOfRxPduConfig)


flexcan_frame_t Can1_Vehicle_Rx_frame[CANIF_TOTAL_RX_PDU];

flexcan_frame_t Can2_Diag_Rx_frame[CANIF_TOTAL_RX_PDU];

 flexcan_handle_t Vehicle_flexcanHandle;

 flexcan_handle_t Diag_flexcanHandle;

volatile flexcan_frame_t Tx_frame;

flexcan_frame_t g_Receive_TxFrame_st;

flexcan_frame_t Tx_GetframeID;

volatile flexcan_mb_transfer_t Vehicle_Tx_frame, Diag_Tx_frame, Can1_Vehicle_rxXfer, Can2_Diag_rxXfer;

 flexcan_mb_transfer_t TxVehicle_Tx_frame;

static NM_STATES l_CanIF_NM_Requested_State_u8[CAN_TOTAL_NUMBER_OF_CHANNELS];

//static CanMgr_ModeType l_CanMgr_Mode[CAN_TOTAL_NUMBER_OF_CHANNELS];

static NM_STATES l_CanIF_NM_Current_State_u8[CAN_TOTAL_NUMBER_OF_CHANNELS ];


extern const CanMailBoxTableDetailsTypeSt CanRXMailBoxTableDetailsSt[CAN_TOTAL_NUMBER_OF_CHANNELS];
extern const CanMailBoxTableDetailsTypeSt CanTXMailBoxTableDetailsSt[CAN_TOTAL_NUMBER_OF_CHANNELS];

/* THIS SHALL HOLD THE NM STOPPED BY DIAG STATUS - THIS IS INDICATION FLAG */
Diag_NetworkControl_Type_St Diag_NetworkControl_St[Max_NM_Msg_types_List] = 
{
     {1, 1},
     {1, 1},
     {1, 1},
     {1, 1},
};

void DiagSetCommControl(Diag_NM_Enable_Mode_Type_En DirectionControl, Diag_NM_COMM_Types_Type_En CommunicationType)
{
     /* LOCAL VARIABLE */

     /* CHECK FOR ACTION IS FOR BOTH THE TYPES */
     if(Network_Management_And_NormalCommunication_Msg == CommunicationType)
     {
          /* CHECK FOR THE DIRECTION CONTROL */
          switch(DirectionControl)
          {
               /* CHECK FOR THE RECVIED CONDITION */
               case ENABLE_RX_AND_ENABLE_TX:
                    Diag_NetworkControl_St[Normal_Communication_Msg].Network_Enable_Rx = 1;
                    Diag_NetworkControl_St[Normal_Communication_Msg].Network_Enable_Tx = 1;

                    Diag_NetworkControl_St[Network_Management_Communication_Msg].Network_Enable_Rx = 1;
                    Diag_NetworkControl_St[Network_Management_Communication_Msg].Network_Enable_Tx = 1;
               break;
               case ENABLE_RX_AND_DISABLE_TX:
                    Diag_NetworkControl_St[Normal_Communication_Msg].Network_Enable_Rx = 1;
                    Diag_NetworkControl_St[Normal_Communication_Msg].Network_Enable_Tx = 0;

                    Diag_NetworkControl_St[Network_Management_Communication_Msg].Network_Enable_Rx = 1;
                    Diag_NetworkControl_St[Network_Management_Communication_Msg].Network_Enable_Tx = 0;
               break;
               case DISABLE_RX_AND_ENABLE_TX:
                    Diag_NetworkControl_St[Normal_Communication_Msg].Network_Enable_Rx = 0;
                    Diag_NetworkControl_St[Normal_Communication_Msg].Network_Enable_Tx = 1;

                    Diag_NetworkControl_St[Network_Management_Communication_Msg].Network_Enable_Rx = 0;
                    Diag_NetworkControl_St[Network_Management_Communication_Msg].Network_Enable_Tx = 1;
               break;
               case DISABLE_RX_AND_DISABLE_TX:
                    Diag_NetworkControl_St[Normal_Communication_Msg].Network_Enable_Rx = 0;
                    Diag_NetworkControl_St[Normal_Communication_Msg].Network_Enable_Tx = 0;

                    Diag_NetworkControl_St[Network_Management_Communication_Msg].Network_Enable_Rx = 0;
                    Diag_NetworkControl_St[Network_Management_Communication_Msg].Network_Enable_Tx = 0;
               break;
               default:
               break;
          }
     }
     else
     {
          /* CHECK FOR THE DIRECTION CONTROL */
          switch(DirectionControl)
          {
               /* CHECK FOR THE RECVIED CONDITION */
               case ENABLE_RX_AND_ENABLE_TX:
                    Diag_NetworkControl_St[CommunicationType].Network_Enable_Rx = 1;
                    Diag_NetworkControl_St[CommunicationType].Network_Enable_Tx = 1;
               break;
               case ENABLE_RX_AND_DISABLE_TX:
                    Diag_NetworkControl_St[CommunicationType].Network_Enable_Rx = 1;
                    Diag_NetworkControl_St[CommunicationType].Network_Enable_Tx = 0;
               break;
               case DISABLE_RX_AND_ENABLE_TX:
                    Diag_NetworkControl_St[CommunicationType].Network_Enable_Rx = 0;
                    Diag_NetworkControl_St[CommunicationType].Network_Enable_Tx = 1;
               break;
               case DISABLE_RX_AND_DISABLE_TX:
                    Diag_NetworkControl_St[CommunicationType].Network_Enable_Rx = 0;
                    Diag_NetworkControl_St[CommunicationType].Network_Enable_Tx = 0;
               break;
               default:
               break;
          }
     }
}

uint8_t DiagGetRXCommControlSts(Diag_NM_COMM_Types_Type_En CommunicationType)
{
     /* LOCAL VARIABLE */

     /* RETURN STATUS */
     return Diag_NetworkControl_St[CommunicationType].Network_Enable_Rx;
}


uint8_t DiagGetTXCommControlSts(Diag_NM_COMM_Types_Type_En CommunicationType)
{
     /* LOCAL VARIABLE */

     /* RETURN STATUS */
     return Diag_NetworkControl_St[CommunicationType].Network_Enable_Tx;
}

static const uint8_t CanIF_ControlMode_State[2][2] =
{
     {
          1, /*CAN_T_STOP,*/
          2, /*CAN_T_START,*/
     },
     {
          1, /*CAN_T_STOP,*/
          2, /*CAN_T_START,*/
     }
};

/*

  CANIF_OFFLINE = 0u,
  CANIF_RX_OFFLINE,
  CANIF_RX_ONLINE,
  CANIF_TX_OFFLINE,
  CANIF_TX_ONLINE,
  CANIF_ONLINE,

*/
static const CanIf_PduModeType CanIF_PduMode_State[6][6] = 
{
     {
          CANIF_OFFLINE,
          CANIF_OFFLINE,
          CANIF_RX_ONLINE,
          CANIF_OFFLINE,
          CANIF_TX_ONLINE,
          CANIF_ONLINE
     },
     {
          CANIF_OFFLINE,
          CANIF_OFFLINE,
          CANIF_OFFLINE,
          CANIF_OFFLINE,
          CANIF_OFFLINE,
          CANIF_OFFLINE
     },
     {
          CANIF_OFFLINE,
          CANIF_OFFLINE,
          CANIF_RX_ONLINE,
          CANIF_RX_ONLINE,
          CANIF_ONLINE,
          CANIF_ONLINE
     },
     {
          CANIF_OFFLINE,
          CANIF_OFFLINE,
          CANIF_OFFLINE,
          CANIF_OFFLINE,
          CANIF_OFFLINE,
          CANIF_OFFLINE
          
     },
     {
          CANIF_OFFLINE,
          CANIF_TX_ONLINE,
          CANIF_ONLINE,
          CANIF_OFFLINE,
          CANIF_TX_ONLINE,
          CANIF_ONLINE
     },
     {
          CANIF_OFFLINE,
          CANIF_TX_ONLINE,
          CANIF_ONLINE,
          CANIF_RX_ONLINE,
          CANIF_ONLINE,
          CANIF_ONLINE
     }     
};



flexcan_frame_t VehicleCanDriverBuffer = {0};
flexcan_frame_t DiagCanDriverBuffer = {0};

/***********************************************************************************************************************
 *                          P R O T O T Y P E    D E C L A R A T I O N
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * NAME:  CanIf_TransmitSubHandleTxResBusy
 ***********************************************************************************************************************/
uint8_t GetMessageUpperID(uint8_t channel, uint8_t MailboxIndex);
Std_ReturnType CanIf_TransmitSubHandleTxResBusy(const Can_PduType* localPduPtr);
#ifdef CANIF_BASIC_CAN
/***********************************************************************************************************************
 * NAME:  CanIf_TxBufferPrioByCanIdQueuePdu
 **********************************************************************************************************************/
void CanIf_TxBufferPrioByCanIdQueuePdu(const Can_PduType* PduInfoPtr);


/**********************************************************************************************************************
| NAME:  CanIf_SetPrioByCanIdTxPduAsQueued
 **********************************************************************************************************************/

Std_ReturnType CanIf_SetPrioByCanIdTxPduAsQueued(PduIdType PduId);

/**********************************************************************************************************************
 * NAME:  CanIf_ClearPrioByCanIdTxPduAsQueued
 **********************************************************************************************************************/

Std_ReturnType CanIf_ClearPrioByCanIdTxPduAsQueued(PduIdType PduId);
#endif
/***********************************************************************************************************************
 * NAME:  CanIf_HlTxConfirmation
 **********************************************************************************************************************/

void CanIf_HlTxConfirmation(PduIdType CanTxPduId);
#ifdef CANIF_BASIC_CAN
/***********************************************************************************************************************
 * NAME:  CanIf_TxQueueTreatment
 **********************************************************************************************************************/

Std_ReturnType CanIf_TxQueueTreatment(uint8_t hth);

/***********************************************************************************************************************
 * NAME:  CanIf_TxQueueTransmit
 **********************************************************************************************************************/

Std_ReturnType CanIf_TxQueueTransmit ( PduIdType PduId);
#endif
/***********************************************************************************************************************
 * NAME:  CanIf_HlIndication
 ***********************************************************************************************************************/

void CanIf_HlIndication(uint8_t  Hrh, PduIdType PduId, const uint8_t* CanSduPtr, uint8_t CanDlc, Can_IdType CanId);
#ifdef CANIF_BASIC_CAN
/***********************************************************************************************************************
 * NAME:  CanIf_ClearQueue
 ***********************************************************************************************************************/

static void CanIf_ClearQueue(uint8_t Channel);
#endif
/***********************************************************************************************************************
 *                          P U B L I C     F U N C T I O N
 ***********************************************************************************************************************/
/*Total number channels added in the structural array */ 
static NM_STATES l_CanIF_NM_Current_State_u8[CAN_TOTAL_NUMBER_OF_CHANNELS ];
static NM_STATES l_CanIF_NM_Requested_State_u8[CAN_TOTAL_NUMBER_OF_CHANNELS];

static uint8_t l_timeout_State_Machine_u8[CAN_TOTAL_NUMBER_OF_CHANNELS];
static uint8_t l_CanIF_Ready_For_Sleep_Status_u8[CAN_TOTAL_NUMBER_OF_CHANNELS];
static uint8_t l_CanIF_Wait_For_Sleep_Preparation_u8[CAN_TOTAL_NUMBER_OF_CHANNELS];




void flexcan_Diag_callback(CAN_Type * base, flexcan_handle_t * handle, status_t status, uint64_t result, void *userData)
{
	/* LOCAL VARIABLE */
	uint8_t Message_Idx = 0;

	switch (status)
	{
		case kStatus_FLEXCAN_RxIdle:
			/* INVOKE CANIF RX INDICATION - RESULT SHALL CONTAIN THE MAILBOX INDEX AND TO SKIP THE ZERO MAILBOX SUBTRACT BY 1 */
			CanIF_RxIndication(base, handle->mbFrameBuf[result], result);
			break;

		case kStatus_FLEXCAN_TxIdle:
			/* CLEAR THE MAILBOX STATE */
			handle->mbState[result] = 0;
			CanMessage_Diag_BusOff_Counter(FALSE);
			Message_Idx = GetMessageUpperID(1, result);
			if(Message_Idx != 0xFF)
			{
				CanIf_HlTxConfirmation(Message_Idx);
			}
			break;

        case kStatus_FLEXCAN_WakeUp:
            wakenUp = true;
            break;

     case kStatus_FLEXCAN_TxBusy:

            break;
        case kStatus_FLEXCAN_ErrorStatus:



      //    CanMessage_Diag_BusOff_Counter(TRUE);
          


            break;
        default:
            break;
    }
}

uint8_t status_value = 0;

void Vehicle_flexcan_callback(CAN_Type * base, flexcan_handle_t * handle, status_t status, uint64_t result, void *userData)
{
    switch (status)
    {
        case kStatus_FLEXCAN_RxIdle:
          /* INVOKE CANIF RX INDICATION - RESULT SHALL CONTAIN THE MAILBOX INDEX AND TO SKIP THE ZERO MAILBOX SUBTRACT BY 1 */
          CanIF_RxIndication(base, handle->mbFrameBuf[result], result);
          break;

        case kStatus_FLEXCAN_TxIdle:
            handle->mbState[result] = 0;
            CanMessage_Vehicle_BusOff_Counter(FALSE);
            break;

        case kStatus_FLEXCAN_WakeUp:
            wakenUp = true;
            break;
        case kStatus_FLEXCAN_ErrorStatus:

          CanMessage_Vehicle_BusOff_Counter(TRUE);
            break;

        default:
               status_value = status;
            break;
    }
}

uint8_t GetMessageUpperID(uint8_t channel, uint8_t MailboxIndex)
{
	/* LOCAL VARIABLE */
	uint8_t fl_loop_u8 = 0;

	/* TRAVERSE TABLE AND FIND THE MESSAGE UPPER INDEX */
	for(fl_loop_u8 = CanTXMailBoxTableDetailsSt[channel].RxTx_TableStartIndex ; fl_loop_u8 < (CanTXMailBoxTableDetailsSt[channel].Size + CanTXMailBoxTableDetailsSt[channel].RxTx_TableStartIndex); fl_loop_u8++)
	{
		/* CHECK FOR THE MAILBOX INDEX */
		if(CanIf_TxPduConfig[fl_loop_u8].MailBoxConfigIdxOfTxPduConfig == MailboxIndex)
		{
			return fl_loop_u8;
		}
	}

	return 0xff;
}

void CanMessage_Vehicle_BusOff_Counter(bool Vehicle_bus_OFF_State)
{

     if(Vehicle_bus_OFF_State == FALSE)
     {

          CANIF_CFG_BUSOFFNOTIFICATION(0);
     }
     else
     {
          Transmit_Vehicle_Error_Count_u16++;
          

          if(Transmit_Vehicle_Error_Count_u16 > 255)
          {

               CANIF_CFG_BUSOFFNOTIFICATION(1);

          }
     }
     
}

void CanMessage_Diag_BusOff_Counter(bool Diag_bus_OFF_State)
{
     if(Diag_bus_OFF_State == FALSE)
     {

          CANIF_CFG_BUSOFFNOTIFICATION(0);
     }
     else
     {
          Transmit_Diag_Error_Count_u16++;

          if(Transmit_Diag_Error_Count_u16 > 255)
          {

          CANIF_CFG_BUSOFFNOTIFICATION(2);

          }
     }
}


/************************************************************************************************************
 * NAME:  CanIF_NetworkRequest
 ************************************************************************************************************
 *  \brief         Request for Network to enter Can to Sleep State or Normal State.
 *  \details       -
 *  \param[in]     fl_CanIF_Network_Request 
 *                 NETWORK_SLEEP - This request the network to go to sleep
 *                 NETWORK_NORMAL - This request the network to get started
 *  \param[in]     ControllerId -ControllerId used to specify the Channel  
 *  \pre           -
 *  \context       ANY
***********************************************************************************************************/
Std_ReturnType CanIF_NetworkRequest(uint8_t Channel,CanIF_Network_Request_Type fl_CanIF_Network_Request)
{

     Std_ReturnType retval = E_NOT_OK;

     switch(fl_CanIF_Network_Request)
     {
          case NETWORK_SLEEP:
               l_CanIF_NM_Requested_State_u8[Channel] = CANIF_NM_STATE_SLEEP_REQUESTED;
               retval = E_OK;
          break;

          case NETWORK_NORMAL:
               l_CanIF_NM_Requested_State_u8[Channel] = CANIF_NM_STATE_NORMAL;
               retval = E_OK;
          break;

          case NETWORK_SILENT:
               l_CanIF_NM_Requested_State_u8[Channel]  = CANIF_NM_STATE_SILENT_REQUESTED;
               retval = E_OK;

          default:
          /* Developmental Error */
          break;

     }

     return retval;

}

/************************************************************************************************************
 * NAME:  Can_NM_State_Machine_MainFunction
 ************************************************************************************************************
 *  \brief         Process the Network Request given by the function CanIF_NetworkRequest.
 *  \details       Request by CanIF_NetworkRequest is processed here. This function has to be configured in
 *                 TIME TASK with the periodicity of ms. All the states in the functions are configured with
 *                 Timeout, if timeout occurs then a callback will be notified to the upper layer on Request
 *                 not processed.
 *  \param[in]     
 *  \pre           CanIf_Init function has to be called.
 *  \context       TIME TASK
***********************************************************************************************************/
void Can_NM_State_Machine_MainFunction(void)
{
    uint8_t Channel;
    static uint8_t network_request_ret_val;
    /*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
    /* call the watch dog alive counter function*/
    CAN_IF_ALIVE_COUNTER();
#endif
      /*This loop is executed according to the total number of channels*/
     for(Channel = 0;Channel < (uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS;Channel++)
     {
     
          /* Check if Controller Mode has initilaized  */ 
          if (CanIf_GetCtrlMode(Channel) == CANIF_CS_UNINIT)
          {

          }
          else
          {
               /* Get the current state of the CANIF module */        
               switch(l_CanIF_NM_Current_State_u8[Channel])
               {

                    case CANIF_NM_STATE_NORMAL:

                         /*Check If the request is for sleep */
                         switch(l_CanIF_NM_Requested_State_u8[Channel])
                         {
                              case CANIF_NM_STATE_SLEEP_REQUESTED:

                                   /* Move to the sleep requested state and clear the timeout value */
                                   l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_SLEEP_REQUESTED;

                                   l_timeout_State_Machine_u8[Channel]= 0;

                              break;
                              case CANIF_NM_STATE_NORMAL:

                                   network_request_ret_val = (WAKEUP_E_OK);

                                   CanMgr_NetworkRequestConfirmation(Channel,&network_request_ret_val);

                              break;

                              case CANIF_NM_STATE_SILENT_REQUESTED:
                                   
                                   l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_SILENT_REQUESTED;

                              break;

                              /* Neglect the request if the requested state is not for sleep */
                              default:
                              /* Developmental Error */
                              break;
                         }

                         /* Clear the Requested State */
                         l_CanIF_NM_Requested_State_u8[Channel] = CANIF_NM_NO_STATE;

                    break;

                    case CANIF_NM_STATE_SLEEP_REQUESTED:
                    {
     #ifdef CANIF_BASIC_CAN                    
                         /* Initialize the local variables */
                         TX_QUEUE_EMPTY_STATUS fl_is_tx_queue_empty_u8;
                         uint8_t fl_search_index_tx_pduid_u8;
                         uint8_t hth;
                         uint32_t txBufferCfgIdx;
                         uint32_t MappedTxPdusIdx;
                         
                         uint32_t TxPduId;
     #endif                    
                         /* Timeout may occur if TX Buffers are not empty or Driver is not accepting the request to put to Sleep */
                         if((l_timeout_State_Machine_u8[Channel] < (uint8_t)CANIF_STATE_MACHINE_TIMEOUT_LIMIT) && (l_CanIF_NM_Requested_State_u8[Channel] != (uint8_t)CANIF_NM_STATE_NORMAL))
                         { 
                                   
                              l_timeout_State_Machine_u8[Channel]++;
     #ifdef CANIF_BASIC_CAN
                              fl_is_tx_queue_empty_u8 = TX_QUEUE_EMPTY;
                              /* Check if there are any messages in queue. If the status of the buffer is set to queue, wait untill all the messages
                              are sent out.  */
                              /* Search all the tx pdu */    
                              for(fl_search_index_tx_pduid_u8 = 0; fl_search_index_tx_pduid_u8 < CANIF_TOTAL_TX_MESSAGES; fl_search_index_tx_pduid_u8++)
                              {
                                   /* Get the mailbox ID */
                                   hth = CANIF_CFG_TX_HTH(fl_search_index_tx_pduid_u8);
                                   
                                   /* Get the Index value of all the tx pdu ids mapped for the above mailbox */
                                   txBufferCfgIdx = CANIF_CFG_MAILBOX_TXBUFFERIDX(hth);
                                   /* Check if Tx-queue is affected (BasicCAN Tx-PDU which has a buffer) */
                                   if ((CanIf_MailBoxConfig[(hth)].TxBufferCfgIdxOfMailBoxConfig) != CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG)
                                   {
                                        /* Fetch the status of the queue for the configured tx pdu   */
                                        for (MappedTxPdusIdx = CANIF_CFG_STARTIDX_TXBUFFERPRIOBYCANIDBYTEQUEUE(txBufferCfgIdx);
                                             MappedTxPdusIdx < CANIF_CFG_STOPIDX_TXBUFFERPRIOBYCANIDBYTEQUEUE(txBufferCfgIdx); 
                                             MappedTxPdusIdx++)
                                        {
                                             TxPduId =  CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_MAPPEDTXPDUS(MappedTxPdusIdx);
                                             if (CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(TxPduId), eQueued) == 1u)
                                             {
                                                  /* If we are here, then some messages are in a queue. Do not move to next state, stay here
                                                  untill all the buffers are empty */
                                                  fl_is_tx_queue_empty_u8 = TX_QUEUE_NOT_EMPTY;
                                             }
                                        }
                                   }
                              }
                              /* Check the status, wheter the tx buffers are empty */
                              if(fl_is_tx_queue_empty_u8 == TX_QUEUE_EMPTY)
                              {
     #endif                    
                                   /* Set the internal PDU mode to OFFLINE, here the CAN Driver will be in normal state but the CANIF layer
                                   will not process tx and rx to the above layer */
                                   (void)CanIf_SetPduMode(Channel,CANIF_OFFLINE);

                                   /* Request the Can Driver for sleep */
                                   if(CanIf_SetControllerMode(Channel,CANIF_CS_STOPPED) == E_OK)
                                   {
                                        /* Initialize the flags used in the state  CANIF_NM_STATE_SLEEP_PREPARE*/
                                        l_CanIF_Ready_For_Sleep_Status_u8[Channel] = (uint8_t)CANIF_SLEEP_STATUS_RESET;

                                        l_timeout_State_Machine_u8[Channel] = 0;

                                        l_CanIF_Wait_For_Sleep_Preparation_u8[Channel] = 0;

                                        /* Move to next state */
                                        l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_SLEEP_PREPARE;

                                   }
     #ifdef CANIF_BASIC_CAN                               
                              }
                              else
                              {
                                   /* Wait untill tx buffer is empty */
                              }
     #endif                         
                         }
                         else
                         {

                              (void)CanIf_SetPduMode(Channel,CANIF_ONLINE);

                              /* If we are here, then either we received a Early wakeup request by the Application */
                              /* OR timeout has occured because either Tx buffer are not empty or CAN Driver is not 
                              accepting request to SLEEP */
                              if(l_CanIF_NM_Requested_State_u8[Channel] == CANIF_NM_STATE_NORMAL)
                              {
                                   /*Early wakeup confirmation*/
                                 network_request_ret_val = (WAKEUP_E_OK);
                              }
                              else
                              {
                                   /*Timeout callback*/
                                 network_request_ret_val = (SLEEP_E_NOT_OK);

                              }

                              CanMgr_NetworkRequestConfirmation(Channel ,&network_request_ret_val);

                              /* Clear the wakeup requested state */
                              l_CanIF_NM_Requested_State_u8[Channel] = CANIF_NM_NO_STATE;

                              /* Put the state back to the normal state */
                              l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_NORMAL;
                         }
                    }

                    break;

                    /* Driver is implemented with the sleep timeout, if driver acknowledges the sleep request as E_OK but driver fails to indicate mode to sleep then driver 
                    will be setting the "Can Driver State" back to NORMAL */
                    case CANIF_NM_STATE_SLEEP_PREPARE:

                    /* Timeout may occur if CAN Driver Accepts the request to put to sleep, but failed to notify the callback on mode indication to Sleep State*/

                    if((l_timeout_State_Machine_u8[Channel] < ((uint8_t)CANIF_STATE_MACHINE_TIMEOUT_LIMIT + (uint8_t)CANIF_WAIT_FOR_SLEEP_TIMEOUT)) )
                    {
                         l_timeout_State_Machine_u8[Channel]++;

                         /* Check if flag is set. If SET then CAN Driver has acknowledge the SLEEP STATE */
                         if(l_CanIF_Ready_For_Sleep_Status_u8[Channel] == (uint8_t)CANIF_SLEEP_STATUS_SET)
                         {
                              l_CanIF_Wait_For_Sleep_Preparation_u8[Channel]++;

                              /* Wait for configured time, just to deduct if any early wakeup by CAN Driver */
                              if(l_CanIF_Wait_For_Sleep_Preparation_u8[Channel] > ((uint8_t)CANIF_WAIT_FOR_SLEEP_TIMEOUT))
                              {
                                   /* No wakeups received , set the transceiver to the STANDBY state */
                                 //  (void)CanTrcv_SetOpMode( Channel, CAN_TRANSCEIVER_SLEEP_MODE );

                                   /* Move the state to sleep */
                                   l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_SLEEP;

                                   if(l_CanIF_NM_Requested_State_u8[Channel] != CANIF_NM_STATE_NORMAL)
                                   {
										/*Callback sleep successfull*/
                                        network_request_ret_val = (SLEEP_E_OK);

                                        CanMgr_NetworkRequestConfirmation(Channel ,&network_request_ret_val);

                                   }

                                   l_timeout_State_Machine_u8[Channel] = 0;
                              }
                              else if(CanIf_GetCtrlMode(Channel) == CANIF_CS_STARTED)
                              {
                                   /* CAN Driver is wakeup, detected early wakeup, put the state back to normal */
                                   l_CanIF_Ready_For_Sleep_Status_u8[Channel] = (uint8_t)CANIF_SLEEP_STATUS_RESET;

                                   (void)CanIf_SetPduMode(Channel,CANIF_ONLINE);

                                   network_request_ret_val = (SLEEP_E_NOT_OK);

                                   CanMgr_NetworkRequestConfirmation(Channel ,&network_request_ret_val);

                                   /* Change the state to the normal state */
                                   l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_NORMAL;

                              }
                              else
                              {
                                   /* Wait for Sleep Preparation */
                              }
                              
                         }

                         /* If callback is received from the CAN Driver, then the flag will be updated to SLEEP State */
                         else if(CanIf_GetCtrlMode(Channel) == CANIF_CS_STOPPED)
                         {
                              /* Set the flag, we need to wait for configured time to check if early wakeup is not detected by CAN Driver */
                              l_CanIF_Ready_For_Sleep_Status_u8[Channel] = (uint8_t)CANIF_SLEEP_STATUS_SET;

                         }
                         else
                         {
                              /* If CanIf_GetCtrlMode is in some other state then wait for timeout */
                         }
                         
                    }
                    else
                    {
                         /* If we are here, then either we received a Early wakeup request by the Application */
                         /* OR timeout has occured because CAN Driver failed to acknowledge the status of Can Driver Stopped */
                         
                         if(l_CanIF_NM_Requested_State_u8[Channel] == CANIF_NM_STATE_NORMAL)
                         {
                            network_request_ret_val = WAKEUP_E_OK;
                         }
                         else
                         {
                              /* Timeout callback */
                              /* Controller Mode is still in Normal state, because no acknowledge is given by driver as SLEEP */
                              network_request_ret_val = SLEEP_E_NOT_OK;
                         }
                         
                         (void)CanIf_SetPduMode(Channel,CANIF_ONLINE);

                         CanMgr_NetworkRequestConfirmation(Channel ,&network_request_ret_val);
                              
                         l_CanIF_NM_Requested_State_u8[Channel] = CANIF_NM_NO_STATE;

                         l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_NORMAL;

                    }

                    break;

                    case CANIF_NM_STATE_SLEEP:

                    /* Get the request by application to wakeup. */
                         switch(l_CanIF_NM_Requested_State_u8[Channel])
                         {
                              case CANIF_NM_STATE_NORMAL:

                              /* Timeout may occur if the repeated request to the driver does not accept to start */
                              if(l_timeout_State_Machine_u8[Channel] < (uint8_t)CANIF_STATE_MACHINE_TIMEOUT_LIMIT )
                              {
                                   l_timeout_State_Machine_u8[Channel]++;

                                   /* request the CAN Driver to Wakeup */
                                   if( E_OK == CanIf_SetControllerMode( Channel, CANIF_CS_STARTED ) )
                                   {
                                        /* Set the transceiver to the normal state */
                                       // (void)CanTrcv_SetOpMode( Channel, CAN_TRANSCEIVER_NORMAL_MODE );

                                        l_CanIF_NM_Requested_State_u8[Channel] = CANIF_NM_NO_STATE;

                                        /* Move to next state */
                                        l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_WAKEUP_REQUESTED;

                                   }
                              }
                              else
                              {
                                   /* timeout occured, be in sleep state */
                                   l_timeout_State_Machine_u8[Channel] = 0;

                                   l_CanIF_NM_Requested_State_u8[Channel] = CANIF_NM_NO_STATE;

                                   /* Callback sleep not successfull*/
                                   network_request_ret_val= WAKEUP_E_NOT_OK;

                                   CanMgr_NetworkRequestConfirmation(Channel ,&network_request_ret_val);
                              
                              }

                              break;

                              case CANIF_NM_STATE_SLEEP_REQUESTED:

                                   /*Callback sleep successfull*/
                                   network_request_ret_val = SLEEP_E_OK;

                                   CanMgr_NetworkRequestConfirmation(Channel ,&network_request_ret_val);

                                   l_CanIF_NM_Requested_State_u8[Channel] = CANIF_NM_NO_STATE;

                              break;

                              case CANIF_NM_STATE_SILENT_REQUESTED:
                                        
                                   l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_SILENT_REQUESTED;
                                                                           
                              default:
                              /* Invalid request */
                              break;
                         }

                         /* Wakeup is detected by the driver,  */
                         if((CanIf_GetCtrlMode(Channel) == CANIF_CS_STARTED) && (l_CanIF_NM_Requested_State_u8[Channel] != CANIF_NM_STATE_NORMAL))
                         {
                              /* Set the Transceiver state to normal */
                           //   (void)CanTrcv_SetOpMode( Channel, CAN_TRANSCEIVER_NORMAL_MODE );

                              (void)CanIf_SetPduMode(Channel,CANIF_ONLINE);

                              network_request_ret_val = WAKEUP_BY_BUS;

                              CanMgr_NetworkRequestConfirmation(Channel ,&network_request_ret_val);

                              /* Move to Wakeup Requested State */   
                              l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_NORMAL;
                         }

                    break;

                    case CANIF_NM_STATE_WAKEUP_REQUESTED:

                    if(l_timeout_State_Machine_u8[Channel] < (uint8_t)CANIF_STATE_MACHINE_TIMEOUT_LIMIT )
                    {
                         l_timeout_State_Machine_u8[Channel]++;

                         /* Wait for CAN Driver Acknowledges stated */
                         if(CanIf_GetCtrlMode(Channel) == CANIF_CS_STARTED)
                         {
                              /* Put the state to normal and set the PDU mode to online state */
                              l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_NORMAL;

                              (void)CanIf_SetPduMode(Channel,CANIF_ONLINE);

                              l_CanIF_NM_Requested_State_u8[Channel] = CANIF_NM_NO_STATE;

                              network_request_ret_val = WAKEUP_E_OK;

                              CanMgr_NetworkRequestConfirmation(Channel ,&network_request_ret_val);
                         }
                    }
                    else
                    {
                         network_request_ret_val = WAKEUP_E_NOT_OK;

                         l_timeout_State_Machine_u8[Channel] =0;

                         CanMgr_NetworkRequestConfirmation(Channel ,&network_request_ret_val);

                         l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_SLEEP;
                    }
                    
                    break;

                    case CANIF_NM_STATE_SILENT_REQUESTED:

                         if( E_OK == CanIf_SetControllerMode( Channel, CANIF_CS_STARTED ) )
                         {
                              /* Set the transceiver to the normal state */
                           //   (void)CanTrcv_SetOpMode( Channel, CAN_TRANSCEIVER_SILENT_MODE );
                              
                              (void)CanIf_SetPduMode(Channel,CANIF_RX_ONLINE);

                              l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_SILENT;

                              l_CanIF_NM_Requested_State_u8[Channel] = CANIF_NM_NO_STATE;

                              network_request_ret_val = SILENT_MODE_OK;
                              
                              CanMgr_NetworkRequestConfirmation(Channel ,&network_request_ret_val);

                         }
                                        

                    break;

                    case CANIF_NM_STATE_SILENT:


                         switch(l_CanIF_NM_Requested_State_u8[Channel])
                         {

                              case CANIF_NM_STATE_NORMAL:

                                   /* Timeout may occur if the repeated request to the driver does not accept to start */
                                   if(l_timeout_State_Machine_u8[Channel] < (uint8_t)CANIF_STATE_MACHINE_TIMEOUT_LIMIT )
                                   {
                                        l_timeout_State_Machine_u8[Channel]++;

                                        /* request the CAN Driver to Wakeup */
                                        if( E_OK == CanIf_SetControllerMode( Channel, CANIF_CS_STARTED ) )
                                        {
                                             /* Set the transceiver to the normal state */
                                         //    (void)CanTrcv_SetOpMode( Channel, CAN_TRANSCEIVER_NORMAL_MODE );

                                             l_CanIF_NM_Requested_State_u8[Channel] = CANIF_NM_NO_STATE;

                                             /* Move to next state */
                                             l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_WAKEUP_REQUESTED;

                                        }
                                   }
                                   else
                                   {
                                        /* timeout occured, be in sleep state */
                                        l_timeout_State_Machine_u8[Channel] = 0;

                                        l_CanIF_NM_Requested_State_u8[Channel] = CANIF_NM_NO_STATE;

                                        /* Callback sleep not successfull*/
                                        network_request_ret_val= WAKEUP_E_NOT_OK;

                                        CanMgr_NetworkRequestConfirmation(Channel ,&network_request_ret_val);
                                   
                                   }

                              break;

                              case CANIF_NM_STATE_SLEEP_REQUESTED:

                                   /* Move to the sleep requested state and clear the timeout value */
                                   l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_SLEEP_REQUESTED;

                                   l_timeout_State_Machine_u8[Channel]= 0;  

                              break;

                              case CANIF_NM_STATE_SILENT_REQUESTED:

                                   network_request_ret_val = SILENT_MODE_OK;
                                   
                                   CanMgr_NetworkRequestConfirmation(Channel ,&network_request_ret_val);

                                   l_CanIF_NM_Requested_State_u8[Channel] = CANIF_NM_NO_STATE;

                              break;

                              default:

                                   /* Do Nothing */
                              break;
                         }


                    break;
                    default:
                         /* Invalid State */
                    break;
               }
          }
     }
}

/************************************************************************************************************
 * NAME:  CanIf_ControllerBusOff
 ************************************************************************************************************
 *  \brief         Busoff notification from CanDriver.
 *  \details       -
 *  \param[in]     -
 *  \pre           -
 *  \context       ANY
***********************************************************************************************************/
void CanIF_ControllerBusOff( uint8_t Channel)
{
          #ifdef CANIF_BASIC_CAN 
               CanIf_ClearQueue(Channel);
          #endif
               (void)CanIf_SetPduMode(Channel, CANIF_OFFLINE);

               CanIf_SetCtrlMode(Channel, CANIF_CS_STOPPED);

               l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_SLEEP;
               
//               if(CANIF_CFG_BUSOFFNOTIFICATION != NULL_PTR)
//               {
//                    CANIF_CFG_BUSOFFNOTIFICATION(Channel);
//               }

}

/************************************************************************************************************
 * NAME:  CanIf_Init
 ************************************************************************************************************
 *  \brief         Initializes the CanIf module.
 *  \details       -
 *  \param[in]     ConfigPtr - Pointer to the CanIf_Config structure.
 *                 If multiple configurations are available, the active configuration can be selected by using
 *                 the related CanIf_Config_<IdentityName> structure.
 *  \pre           The function CanIf_InitMemory() must be called before the function CanIf_Init() is called.
 *                 This function must be called before any other service functionality of CanIf.
 *  \context       TASK
***********************************************************************************************************/
void CanIf_Init(void)
{
     uint8_t Channel;
     uint8_t MailBoxIndex = 0;
      flexcan_rx_mb_config_t FlexCAN_MB_Recieve_St;
      flexcan_mb_transfer_t FlexCAN_Handle_Receive_St;
     CAN_Type* CAN_Channel = NULL;
     uint64_t u64mask = 1;
     /*This loop is executed according to the total number of channels*/
     for(Channel = 0;Channel< (uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS;Channel++)
     {
          #ifdef CANIF_BASIC_CAN          
                    CanIf_ClearQueue(Channel);
          #endif     

          CanIf_SetCtrlMode(Channel, CANIF_CS_STOPPED);

          CanIf_SetChannelMode(Channel, CANIF_OFFLINE);

          l_CanIF_NM_Current_State_u8[Channel] = CANIF_NM_STATE_SLEEP;

          l_CanIF_NM_Requested_State_u8[Channel] = CANIF_NM_NO_STATE;

          l_timeout_State_Machine_u8[Channel] = 0;

          /* CONFIGURE RX MAILBOX */
          for(MailBoxIndex = 0; MailBoxIndex < CanRXMailBoxTableDetailsSt[Channel].Size; MailBoxIndex++)
          {
               /* Setup Rx Message Buffer. */
               FlexCAN_MB_Recieve_St.format = kFLEXCAN_FrameFormatStandard;
               FlexCAN_MB_Recieve_St.type   = kFLEXCAN_FrameTypeData;
               FlexCAN_MB_Recieve_St.id	= FLEXCAN_ID_STD(CanIf_RxPduConfig[(CanRXMailBoxTableDetailsSt[Channel].StartIndex + MailBoxIndex)].RxPduCanIdOfRxPduConfig);
               FlexCAN_Handle_Receive_St.mbIdx = (MailBoxIndex);

               /* CHECK THE CHANNEL BASE ADDRESS AND SET HADNDLE AND CALLBACK */
               if(Channel == 0) /* CHECK FOR IVN CHANNEL OR TESTER CHANNEL */
               {
                    /* SET BUFFER FOR VEHICLE CAN CANNEL */
                    FlexCAN_Handle_Receive_St.frame = &VehicleCanDriverBuffer;
                    /* CONFIG THE MAILBOX - MAILBOX 0 SHALL NOT BE USED */
                    FLEXCAN_SetRxMbConfig(VECHILE_CAN, (MailBoxIndex), &FlexCAN_MB_Recieve_St, true);
                    FLEXCAN_TransferReceiveNonBlocking(VECHILE_CAN, &Vehicle_flexcanHandle, &FlexCAN_Handle_Receive_St);
               }
               else           /* TESTER CHANNEL */
               {
                    /* SET BUFFER FOR THE DIAG CAN CHANNEL */
                    FlexCAN_Handle_Receive_St.frame = &DiagCanDriverBuffer;
                    /* CONFIG THE MAILBOX - MAILBOX 0 SHALL NOT BE USED */
                    FLEXCAN_SetRxMbConfig(DIAG_CAN, (MailBoxIndex), &FlexCAN_MB_Recieve_St, true);
                    FLEXCAN_TransferReceiveNonBlocking(DIAG_CAN, &Diag_flexcanHandle, &FlexCAN_Handle_Receive_St);
               }
          }

          /* CONFIGURE TX MAILBOX */
          for(MailBoxIndex = 0; MailBoxIndex < CanTXMailBoxTableDetailsSt[Channel].Size; MailBoxIndex++)
          {
               /* SET THE MAILBOX INDEX */
               FlexCAN_Handle_Receive_St.mbIdx = (CanTXMailBoxTableDetailsSt[Channel].StartIndex + MailBoxIndex);

               /* CHECK THE CHANNEL BASE ADDRESS AND SET HADNDLE AND CALLBACK */
               if(Channel == 0) /* CHECK FOR IVN CHANNEL OR TESTER CHANNEL */
               {
                    /* SET BUFFER FOR VEHICLE CAN CANNEL */
                    FlexCAN_Handle_Receive_St.frame = &VehicleCanDriverBuffer;
                    /* CONFIG THE MAILBOX - MAILBOX 0 SHALL NOT BE USED */
                    FLEXCAN_SetTxMbConfig(VECHILE_CAN, FlexCAN_Handle_Receive_St.mbIdx, true);
                    FLEXCAN_EnableMbInterrupts(VECHILE_CAN, u64mask << FlexCAN_Handle_Receive_St.mbIdx);
               }
               else           /* TESTER CHANNEL */
               {
                    /* SET BUFFER FOR THE DIAG CAN CHANNEL */
                    FlexCAN_Handle_Receive_St.frame = &DiagCanDriverBuffer;
                    /* CONFIG THE MAILBOX - MAILBOX 0 SHALL NOT BE USED */
                    FLEXCAN_SetTxMbConfig(DIAG_CAN, FlexCAN_Handle_Receive_St.mbIdx, true);
                    FLEXCAN_EnableMbInterrupts(DIAG_CAN, u64mask << FlexCAN_Handle_Receive_St.mbIdx);
               }
          }
     }
}

/************************************************************************************************************
 * NAME:  CanIf_InitMemory()
 ************************************************************************************************************
 *  \brief         Sets the CanIf to the state: uninitialized.
 *  \details       De Initialized the CanIF module.
 *  \param[in]     -
 *  \pre           -
 *  \context       TASK
***********************************************************************************************************/
void CanIf_DeInit(void)
{
    uint8_t Channel;
    /*This loop is executed according to the total number of channels*/
    for(Channel = 0;Channel < (uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS;Channel++)
    {
        CanIf_SetCtrlMode(Channel, CANIF_CS_UNINIT);
      
    } 
}

/************************************************************************************************************
 * NAME:  CanIf_Transmit
 ************************************************************************************************************
 *  \brief               Initiates transmission of a Tx-message.
 *  \details             -
 *  \param[input]        CanTxPduId : Handle of Tx-PDU which shall be transmitted.
 *                       PduInfoPtr : Data of Tx-PDU which shall be transmitted.
 *  \return              E_OK     : The request to transmit a Tx-PDU accepted.
 *                       E_NOT_OK : The request to transmit a Tx-PDU rejected.
 *  \pre           -
 *  \context       ANY
 *  \config        -
***********************************************************************************************************/

Std_ReturnType CanIf_Transmit(PduIdType Mgr_CanTxPduId,const PduInfoType* PduInfoPtr)
{
    Std_ReturnType  retval;
    PduIdType l_Search_Index_CanTxPDU_u16;
    boolean  l_Search_Result_CanTxPDU_u16 = false;
    static Can_PduType     localPdu;
    uint8_t Channel;
    PduIdType CanTxPduId = Mgr_CanTxPduId;
    uint8_t  errorId = (uint8_t)CANIF_NO_ERROR;
    retval = E_NOT_OK;

	Channel = CanIf_TxPduConfig[Mgr_CanTxPduId].CtrlStatesIdxOfTxPduConfig;
	TxVehicle_Tx_frame.mbIdx = CanIf_TxPduConfig[Mgr_CanTxPduId].MailBoxConfigIdxOfTxPduConfig;

     TxVehicle_Tx_frame.frame->id = FLEXCAN_ID_STD(CanIf_TxPduConfig[Mgr_CanTxPduId].CanIdOfTxPduConfig);
     TxVehicle_Tx_frame.frame->length = 8;
     TxVehicle_Tx_frame.frame->type = kFLEXCAN_FrameTypeData;
     TxVehicle_Tx_frame.frame->format = kFLEXCAN_FrameFormatStandard;

     TxVehicle_Tx_frame.frame->dataByte0 = PduInfoPtr->SduDataPtr[0];
     TxVehicle_Tx_frame.frame->dataByte1 = PduInfoPtr->SduDataPtr[1];
     TxVehicle_Tx_frame.frame->dataByte2 = PduInfoPtr->SduDataPtr[2];
     TxVehicle_Tx_frame.frame->dataByte3 = PduInfoPtr->SduDataPtr[3];
     TxVehicle_Tx_frame.frame->dataByte4 = PduInfoPtr->SduDataPtr[4];
     TxVehicle_Tx_frame.frame->dataByte5 = PduInfoPtr->SduDataPtr[5];
     TxVehicle_Tx_frame.frame->dataByte6 = PduInfoPtr->SduDataPtr[6];
     TxVehicle_Tx_frame.frame->dataByte7 = PduInfoPtr->SduDataPtr[7];

     if(CanMgr_TxInfoTable[Mgr_CanTxPduId].channel == 0)
     {
          retval = FLEXCAN_TransferSendNonBlocking(VECHILE_CAN, &Vehicle_flexcanHandle, &TxVehicle_Tx_frame);
     }
     else
     {
          retval = FLEXCAN_TransferSendNonBlocking(DIAG_CAN, &Diag_flexcanHandle, &TxVehicle_Tx_frame);
     }

return retval;
}


/************************************************************************************************************
 * NAME:  CanIf_SetControllerMode
 ************************************************************************************************************
 *  \brief         Requests a mode transition of a CAN channel.
 *  \details       -
 *  \param[in]     ControllerId   : Index of the CAN channel to which API call has to be applied.
 *                 ControllerMode : Mode to which the CAN channel state has to be changed.
 *  \return        E_OK     : The request to change the mode to ControllerMode accepted.
 *                 E_NOT_OK : The request to change the mode to ControllerMode rejected.
 *  \pre           CAN interrupts are not disabled (especially necessary in case of transition to SLEEP)
 *  \context       ANY
***********************************************************************************************************/
Std_ReturnType CanIf_SetControllerMode(uint8_t Channel, CanIf_ControllerModeType ControllerMode)
{
     Std_ReturnType retval;
     uint8_t errorId = (uint8_t)CANIF_NO_ERROR;
     retval = E_NOT_OK;
     uint8_t fl_set_controller_modetype_u8[CAN_TOTAL_NUMBER_OF_CHANNELS];


     if (Channel>= (uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS)
     {      
          errorId = (uint8_t)CANIF_ERROR;
     }
     else if(CanIf_GetCtrlMode(Channel) == CANIF_CS_UNINIT)
     {
          errorId = (uint8_t)CANIF_ERROR;
     }
     else
     {
          if(ControllerMode >= CANIF_CS_UNINIT )
          {
               retval = E_NOT_OK;
          }
          else
          {
               fl_set_controller_modetype_u8[Channel] = CanIF_ControlMode_State[CanIf_GetCtrlMode(Channel)][ControllerMode];

               switch(fl_set_controller_modetype_u8[Channel])
               {
                    case 1:
                        // if (E_OK == (Can_SetControllerMode((uint8_t)Channel, CAN_CS_SLEEP)))
                         {
#ifdef CANIF_BASIC_CAN 
                              if(CanIf_GetCtrlMode(Channel) == CANIF_CS_STARTED)
                              {
                                   
                                   CanIf_ClearQueue(Channel);
                              }
#endif                              
                              retval = E_OK;
                         }
                    break;
                    case 2:
                           //   if (E_OK == (Can_SetControllerMode((uint8_t)Channel, CAN_CS_STARTED)))
                              {
                                   retval = E_OK;
                              }
                    break;

                    default:
                         /* Developmental Error */
                    break;
               }
          }
     }

     if(errorId != (uint8_t)CANIF_NO_ERROR)
     {
          /* Development Error CallBack Function */
     }

     return retval;


}

/************************************************************************************************************
 * NAME:  CanIf_GetControllerMode
 ************************************************************************************************************
 *  \brief         Returns the current mode of a CAN channel.
 *  \details       -
 *  \param[in]     ControllerId      : Index of the CAN channel to which API call has to be applied.
 *                 ControllerModePtr : Pointer to variable where the actual controller mode has to be stored.
 *  \return        E_OK     : Request of controller mode succeeded.
 *                 E_NOT_OK : Request of controller mode failed.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        -
***********************************************************************************************************/
Std_ReturnType CanIf_GetControllerMode(uint8_t Channel, CanIf_ControllerModeType* ControllerModePtr)
{
     Std_ReturnType retval;
     uint8_t errorId = (uint8_t)CANIF_NO_ERROR;
     retval = E_NOT_OK;

     if (Channel >= (uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS)
     {      
          errorId = (uint8_t)CANIF_ERROR;
     }
     else if(CanIf_GetCtrlMode(Channel) == CANIF_CS_UNINIT)
     {
          errorId = (uint8_t)CANIF_ERROR;
     }
    else if (ControllerModePtr == NULL_PTR)
    {
      
      errorId = (uint8_t)CANIF_ERROR;
    }
    else
    {
          *ControllerModePtr = CanIf_GetCtrlMode(Channel);

          retval = E_OK;        
    }

    if (errorId != (uint8_t)CANIF_NO_ERROR)
    {
         /* Development Error CallBack Function */
    }

    return retval;
}

/************************************************************************************************************
 * NAME:  CanIf_SetPduMode
 ************************************************************************************************************
 *  \brief         Sets PDU mode of a CAN channel.
 *  \details       -
 *  \param[in]     ControllerId : Index of the CAN channel to which API call has to be applied.
 *                 PduModeRequest : PDU mode which shall be set.
 *  \return        E_OK     : The PDU mode transition executed.
 *                 E_NOT_OK : The PDU mode transition failed.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        -
***********************************************************************************************************/
Std_ReturnType CanIf_SetPduMode(uint8_t Channel, const CanIf_PduModeType PduModeRequest)
{
     Std_ReturnType retval = E_NOT_OK;
     uint8_t errorId =(uint8_t) CANIF_NO_ERROR;

     if(Channel >= (uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS)
     {
          errorId = (uint8_t)CANIF_ERROR;
     }
     else if (CanIf_GetCtrlMode(Channel) == CANIF_CS_UNINIT)
     {
          errorId = (uint8_t)CANIF_ERROR;
     } 
     else if (PduModeRequest >= CANIF_NO_MODE_PDU_MODE_TYPE_END)
     {
          errorId = (uint8_t)CANIF_ERROR;
     }
     else
     {
          /* Check if  the current controller Mode is NORAMAL to accept the request to change the pdu mode */
          if (CanIf_GetCtrlMode(Channel) == CANIF_CS_STARTED)
          {
               retval = E_OK;
          
               /* Get the requested controller mode */
               switch(PduModeRequest)
               {
                    case CANIF_OFFLINE:
                    case CANIF_TX_OFFLINE:
                    /* Get the current channel mode of the controller */
                         switch(CanIf_GetChannelMode(Channel))
                         {
                              case CANIF_TX_ONLINE:
                              case CANIF_ONLINE:
                                   /* Clear the Queue before transiting to the OFFLINE mode */
#ifdef CANIF_BASIC_CAN                                   
                                   CanIf_ClearQueue(Channel);
#endif                                   
                              break;

                              default:
                              /* No action for other request */
                              break;

                         }

                    break;

                    default:
                    /* No action for other request */
                    break;

               }

               /* Set the channel mode as requested */
               CanIf_SetChannelMode(Channel, CanIF_PduMode_State[CanIf_GetChannelMode(Channel)][PduModeRequest]);
          }
      
     }
     if (errorId != (uint8_t)CANIF_NO_ERROR)
     {
          /* Development Error CallBack Function */
     }   

     return retval;
}

/************************************************************************************************************
 * NAME:  CanIf_GetPduMode
 ***********************************************************************************************************
 *  \brief         Returns the current PDU mode of a CAN channel.
 *  \details       -
 *  \param[in]     ControllerId : Index of the CAN channel to which API call has to be applied.
 *                 PduModePtr   : Pointer to variable where the actual PDU mode has to be stored.
 *  \return        E_OK     : Request of PDU mode succeeded.
 *                 E_NOT_OK : Request of PDU mode failed.
 *  \pre           -
 *  \context       ANY
***********************************************************************************************************/
Std_ReturnType CanIf_GetPduMode(uint8_t Channel, CanIf_PduModeType* PduModePtr)
{
     Std_ReturnType retval = E_NOT_OK;
     uint8_t errorId = (uint8_t)CANIF_NO_ERROR;


     if(Channel >= (uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS)
     {
          errorId =(uint8_t) CANIF_ERROR;
     }
     else if(PduModePtr == NULL_PTR)
     {
         errorId = (uint8_t)CANIF_ERROR; 
     }
     else
     {
          retval = E_OK;

          *PduModePtr = CanIf_GetChannelMode(Channel);
     }

     if(errorId != (uint8_t)CANIF_NO_ERROR)
     {
          /* Development Error CallBack Function */
     }

    return retval;
}

#ifdef CANIF_ALL_API_SUPPORTED

void CanIf_TrcvModeIndication(uint8_t TransceiverId, CanTrcv_TrcvModeType TransceiverMode)
{

}

Std_ReturnType CanIf_SetBaudrate(uint8_t ControllerId, uint16_t BaudRateConfigID)
{
    return E_OK;
}


Std_ReturnType CanIf_ChangeBaudrate(uint8_t ControllerId, const uint16_t Baudrate)
{
    return E_OK;
}

Std_ReturnType CanIf_CheckBaudrate(uint8_t ControllerId, const uint16_t Baudrate)
{
    return E_OK;
}

#endif
/************************************************************************************************************
 * NAME:  
 * CanIf_ControllerModeIndication
 ************************************************************************************************************
 *  \brief         Notifies a mode state transition of a CAN channel.
 *  \details       -
 *  \param[in]     ControllerId: CAN channel where the mode transition happened
 *  \param[in]     ControllerMode: Mode to which the CAN channel transitioned
 *  \pre           -
 *  \context       ANY
 *  \reentrant     TRUE only for different CAN channels (ControllerId)
 *  \synchronous   TRUE
 *  \config        -
***********************************************************************************************************/
void CanIf_ControllerModeIndication(uint8_t Channel, Can_ControllerStateType Controller_Mode)
{

    uint8_t errorId = (uint8_t)CANIF_NO_ERROR;
    CanIf_ControllerModeType CanIF_Controller_Mode = CANIF_CS_UNINIT;
    CanIf_CtrlModeIndicationFctType cbkFct;

    if (Channel >= (uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS)
    {
      errorId = (uint8_t)CANIF_ERROR;
    }
    else if (CanIf_GetCtrlMode(Channel) == CANIF_CS_UNINIT)
    {
      errorId = (uint8_t)CANIF_ERROR;
    }
    else
    {        

          /* Get the requested Controller Mode */
          switch(Controller_Mode)
          {
               case CAN_CS_SLEEP:
               /* Get the current controller Mode */
                    switch(CanIf_GetCtrlMode(Channel))
                    {

                         case CANIF_CS_STARTED:

                              CanIf_SetCtrlMode(Channel, CANIF_CS_STOPPED);

                              CanIF_Controller_Mode = CANIF_CS_STOPPED;

                         break;

                         case CANIF_CS_STOPPED:

                         break;

                         default:
                         /* Error State */
                         break;

                    }
               break;

               case CAN_CS_STARTED:
               /* Get the current controller Mode */
                    switch(CanIf_GetCtrlMode(Channel))
                    {
                         case CANIF_CS_STOPPED:

                              CanIf_SetCtrlMode(Channel, CANIF_CS_STARTED);

                              CanIF_Controller_Mode = CANIF_CS_STARTED;

                         break;

                         case CANIF_CS_STARTED:

                         break;
                       

                         default:
                         /* Error State */
                         break;

                    }
               break;
     

               default:
                    /* Neglect if other state */
               break;                       

          }

          cbkFct = CANIF_CFG_CTRLMODEINDICATIONFCT;

          /* check if the callback function is available  */
          if ((cbkFct != NULL_PTR) && (CanIF_Controller_Mode!= CANIF_CS_UNINIT))
          {
               /* call the callback function */
               cbkFct(Channel, CanIF_Controller_Mode);
          }


    }

    if (errorId !=(uint8_t) CANIF_NO_ERROR)
    {
         /* Development Error CallBack Function */
    }

}

/***********************************************************************************************************************
* NAME:  CanIf_TxConfirmation
 ***********************************************************************************************************************
 *  \brief       Confirmation for successful transmission.
 *  \details     -
 *  \param[in]   CanTxPduId: Internal ID of successful transmitted PDU.
 *  \pre         -
 *  \context     ISR
 **********************************************************************************************************************/

void CanIf_TxConfirmation(PduIdType CanTxPduId)
{
    uint8_t errorId = (uint8_t)CANIF_NO_ERROR;    

    /* Check if parameter CanTxPduId is valid */
    if (CanTxPduId >=  (uint8_t)CANIF_CFG_MAX_TXPDUS)
    {      
      errorId = (uint8_t)CANIF_ERROR;
    }
    /* Check if corresponding CAN channel is initialized */
    else if (CanIf_GetCtrlMode(CANIF_CFG_TX_CONTROLLER(CanTxPduId)) == CANIF_CS_UNINIT )
    {
      errorId = (uint8_t)CANIF_ERROR;
    }
    else
    {
        if (CanIf_GetCtrlMode(CANIF_CFG_TX_CONTROLLER(CanTxPduId)) == CANIF_CS_STARTED)
        {
            if ( (CanIf_GetChannelMode(CANIF_CFG_TX_CONTROLLER(CanTxPduId)) == CANIF_ONLINE) ||
               (CanIf_GetChannelMode(CANIF_CFG_TX_CONTROLLER(CanTxPduId)) == CANIF_TX_ONLINE))
            {
#ifdef CANIF_BASIC_CAN                 
                uint32_t hth;
                hth = CANIF_CFG_TX_HTH(CanTxPduId);
                
                /* Check if Tx-queue is affected (BasicCAN Tx-PDU which has a buffer) */
                if ((CanIf_MailBoxConfig[(hth)].TxBufferCfgIdxOfMailBoxConfig) != CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG)  
                {

                    /* parameter hth out of CanTxPduId */
                    (void)CanIf_TxQueueTreatment((uint8_t)hth);

                }
#endif
                /*  Inform upper layer about transmitted PDU */
                CanIf_HlTxConfirmation(CanTxPduId);

            }
       }
    }

    if (errorId != (uint8_t)CANIF_NO_ERROR)
    {
         /* Development Error CallBack Function */
    }

}

void CanIF_RxIndication(CAN_Type *base, flexcan_frame_t *CanIF_RxFrame, uint8_t result)
{
     /* LOCAL VARIABLES */
     uint8_t fl_PDUIdx = 0;
     CanIf_AdvancedRxIndicationFctType rxIndicationFct ;
     static uint8_t network_request_val;
     uint8_t FunctionPtrIndex = 0;
     PduInfoType fl_GetBuffer;
     uint8_t CanId = 0;
     uint8_t fl_data_u8[8] = {0};
     uint8_t fl_NM_NetworkCommMsgEnable_u8 = 0;
     uint8_t fl_Normal_Communication_Msg_Enable_u8 = 0;

     /* CONVERT DRIVER DATE TO PDU FORMAT */
	fl_data_u8[0] = CanIF_RxFrame->dataByte0;
	fl_data_u8[1] = CanIF_RxFrame->dataByte1;
	fl_data_u8[2] = CanIF_RxFrame->dataByte2;
	fl_data_u8[3] = CanIF_RxFrame->dataByte3;
	fl_data_u8[4] = CanIF_RxFrame->dataByte4;
	fl_data_u8[5] = CanIF_RxFrame->dataByte5;
	fl_data_u8[6] = CanIF_RxFrame->dataByte6;
	fl_data_u8[7] = CanIF_RxFrame->dataByte7;

     /* FILL THE PDU DATA */
     fl_GetBuffer.SduLength = CanIF_RxFrame->length;
	fl_GetBuffer.SduDataPtr = &fl_data_u8[0];

	network_request_val = (WAKEUP_E_OK);

     /* CHECK FOR THE CAN BASE */
     if(base == VECHILE_CAN)
     {
          /* SET THE RESULT AS PDU INDEX */
          fl_PDUIdx = result;
          /* SET CanID FOR NETWORK MESSAGE */
          CanId = 0;
     }
     else
     {
          /* SET CHANNEL 2 OFFSET FROM THE MAILBOX INDEX */
          fl_PDUIdx = (result + 12);
          /* SET CanID FOR NETWORK MESSAGE */
          CanId = 1;
     }

     /* GET FUNCTION POINTER INDEX */
	FunctionPtrIndex = CANIF_CFG_RX_RXINDICATION(fl_PDUIdx);

     /* CHECK FOR THE TYPE OF FUNCTION */
     if (CANIF_CFG_FUNCTIONLAYOUT_OF_RXINDICATION(FunctionPtrIndex) == CanIf_AdvancedRxIndicationLayout)
     {
          /* CHECK FOR THE NM STATUS ENABLED */
          if(DiagGetRXCommControlSts(Normal_Communication_Msg) == 1)
          {
               /* GET THE FUNCTION ADDRESS */
               rxIndicationFct = CANIF_CFG_RXINDICATION_FUNCTION(FunctionPtrIndex).eAdvancedRxIndicationType;

               /* CHECK FOR THE VALID POINTER MAPPED */
               if (rxIndicationFct != NULL_PTR)
               {
                    rxIndicationFct(CANIF_CFG_RX_UPPERPDUID(fl_PDUIdx), (const PduInfoType*) &fl_GetBuffer);
               }
          }
     }
     else if (CANIF_CFG_FUNCTIONLAYOUT_OF_RXINDICATION(FunctionPtrIndex) == CanIf_TpRxIndicationLayout)
     {
          /* GET THE FUNCTION ADDRESS */
          rxIndicationFct = CANIF_CFG_RXINDICATION_FUNCTION(FunctionPtrIndex).eTpRxIndicationType;

          /* CHECK FOR THE VALID POINTER MAPPED */
          if (rxIndicationFct != NULL_PTR)
          {
               rxIndicationFct(CANIF_CFG_RX_UPPERPDUID(fl_PDUIdx), (const PduInfoType*) &fl_GetBuffer);
          }
     }
     else if (CANIF_CFG_FUNCTIONLAYOUT_OF_RXINDICATION(FunctionPtrIndex) == CanIf_NmRxIndicationLayout)
     {
          /* CHECK FOR THE NM STATUS ENABLED */
          if(DiagGetRXCommControlSts(Network_Management_Communication_Msg) == 1)
          {
               /*  CanIf_NmOsekRxIndicationLayout API */
               CanIf_NmRxIndicationFctType rxIndicationFct ;

               /* GET THE FUNCTION PTR */
               rxIndicationFct = CANIF_CFG_RXINDICATION_FUNCTION(FunctionPtrIndex).eNmRxIndicationType;

               /* CHECK FOR THE VALID FUNCTION */
               if (rxIndicationFct != NULL_PTR)
               {
                    rxIndicationFct(CANIF_CFG_RX_UPPERPDUID(fl_PDUIdx), (const uint8_t*) &fl_data_u8[0], CanId);
               }
          }
     }
     else{}
}

/***********************************************************************************************************************
 *                          P R I V A T E     F U N C T I O N
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * NAME:  CanIf_HlIndication
 ***********************************************************************************************************************
 *  \brief          Reports a received message to upper layer.
 *  \details        Additionally it handles: wake-up validation state, DLC check, meta data. Called out of CanIf_RxIndication().
 *  \param[input]   Hrh: hardware receive handle. Parameter must be smaller than CANIF_CFG_MAX_MAILBOXES.
 *  \param[input]   PduId: Internal Rx-PDU ID. Parameter must be smaller than CANIF_CFG_MAX_RXPDUS.
 *  \param[input]   CanSduPtr: pointer to Rx-data
 *  \param[input]   CanDlc: length of Rx-data
 *  \param[input]   CanId: CAN identifier (optional, depending on configuration)
 *  \context        ANY
 *  \config      
 **********************************************************************************************************************/
void CanIf_HlIndication(uint8_t  Hrh, PduIdType PduId, const uint8_t* CanSduPtr, uint8_t CanDlc, Can_IdType CanId)
{
     /* ----- Local Variables ---------------------------------------------- */
     uint8_t errorId = (uint8_t)CANIF_NO_ERROR;
     uint8_t Channel;
     uint8_t index; 
     CanIf_AdvancedRxIndicationFctType rxIndicationFct;
     static PduInfoType pduinfo;

     /* Determine the channel from Hrh */
     Channel = CANIF_CFG_MAILBOX_CONTROLLER(Hrh);

     if (Channel >= (uint8_t)CAN_TOTAL_NUMBER_OF_CHANNELS)
     {
          errorId = (uint8_t)CANIF_ERROR;
     }
     else if (CanIf_GetCtrlMode(Channel) == CANIF_CS_UNINIT)
     {
          
          errorId =(uint8_t)CANIF_ERROR;
     }
     else
     {
          if (CanIf_GetCtrlMode(Channel) == CANIF_CS_STARTED)
          {
               if ( (CanIf_GetChannelMode(Channel) == CANIF_ONLINE) ||
                    (CanIf_GetChannelMode(Channel) == CANIF_RX_ONLINE))
               {
                    if (CanDlc < (uint8_t)(CANIF_CFG_RX_DLC(PduId) ) )
                    {

                         errorId = (uint8_t)CANIF_ERROR;
                    }
                    else if( CANIF_CFG_RX_RXINDICATION(PduId) >=  (uint8_t)CANIF_CFG_MAX_RXINDICATIONS )
                    {
                         errorId = (uint8_t)CANIF_ERROR;
                    } 
                    else
                    {
                         
                         index = CANIF_CFG_RX_RXINDICATION(PduId);

                         if (CANIF_CFG_FUNCTIONLAYOUT_OF_RXINDICATION(index) == CanIf_NmRxIndicationLayout)
                         {
                              /*  CanIf_NmOsekRxIndicationLayout API */
                              CanIf_NmRxIndicationFctType rxIndicationFct;

                              rxIndicationFct = CANIF_CFG_RXINDICATION_FUNCTION(index).eNmRxIndicationType;

                              if (rxIndicationFct != NULL_PTR)
                              {
                                   rxIndicationFct(CANIF_CFG_RX_UPPERPDUID(PduId), (const uint8_t*) CanSduPtr, CanId);
                              }


                         }

                         if (CANIF_CFG_FUNCTIONLAYOUT_OF_RXINDICATION(index) == CanIf_AdvancedRxIndicationLayout)  
                         {
                              /* const to non-const cast is not avoidable */
                              pduinfo.SduDataPtr = (const uint8_t*) CanSduPtr;

                              /* Currently received DLC value is passed to upper layer */
                              pduinfo.SduLength = CanDlc;

                              rxIndicationFct = CANIF_CFG_RXINDICATION_FUNCTION(index).eAdvancedRxIndicationType;

                              if (rxIndicationFct != NULL_PTR)
                              {

                                   rxIndicationFct(CANIF_CFG_RX_UPPERPDUID(PduId), (const PduInfoType*) &pduinfo);  
                              }
                         }

                    }
                    

               }

          }         
     }

     if (errorId != (uint8_t)CANIF_NO_ERROR)
     {
          /* Development Error CallBack Function */
     }
       
}

/***********************************************************************************************************************
 * NAME:  CanIf_HlTxConfirmation
 **********************************************************************************************************************
 *  \brief       Reports the confirmation for a successful transmission.
 *  \details     Called out of CanIf_TxConfirmation(), CanIf_Transmit().
 *  \param[in]   CanTxPduId: Internal Tx-PDU ID. Parameter must be smaller than CANIF_CFG_MAX_TXPDUS.
 *  \pre         -
 *  \context     ANY
 **********************************************************************************************************************/

void CanIf_HlTxConfirmation(PduIdType CanTxPduId)
{
     
     uint8_t index;
     PduIdType upperLayerTxPduId;
     CanIf_TxConfirmationFctType txConfirmationFct;
    
     /*  Get the Tx-confirmation function */
     index = CANIF_CFG_TX_TXCONFIRMATION(CanTxPduId);

     /*  Convert the CanIf internal TxPduId to the upper layer one */
     upperLayerTxPduId = CANIF_CFG_TX_UPPERLAYERTXPDUID(CanTxPduId);

     txConfirmationFct = CANIF_CFG_TXCONFIRMATION(index);

     if (txConfirmationFct != NULL_PTR)
     {
       /*  If configured, call the Tx-confirmation function */
         txConfirmationFct(upperLayerTxPduId, E_OK);     
     }


}

/***********************************************************************************************************************
 * NAME:  CanIf_TransmitSubHandleTxResBusy
 ***********************************************************************************************************************
 *  \brief       Handles the Tx-queue.
 *  \details     Called out of CanIf_Transmit().
 *  \param[in]   localPduPtr: Pointer to PDU data.
 *  \return      E_OK: PDU was successfully buffered.
 *               E_NOT_OK: PDU could not be buffered.
 *  \pre         Due to write access to Tx-buffer this API must be called protected with critical area!
 *  \context     ANY
 **********************************************************************************************************************/

Std_ReturnType CanIf_TransmitSubHandleTxResBusy(const Can_PduType* localPduPtr)
{
     Std_ReturnType retval = E_NOT_OK; 
    
     uint32_t hth;
     uint8_t errorId = (uint8_t)CANIF_NO_ERROR;   

     hth = CANIF_CFG_TX_HTH(localPduPtr->swPduHandle);

     if ((CanIf_MailBoxConfig[(hth)].TxBufferCfgIdxOfMailBoxConfig) != (uint8_t)CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG)
     {

          if ((localPduPtr->sdu == NULL_PTR) && (localPduPtr->length != (uint8_t)0U))
          {
               errorId = (uint8_t)CANIF_ERROR;
          }
          else
          {

#ifdef CANIF_BASIC_CAN

               switch (CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE(hth))
               {
                    case CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID:
            
                         if(localPduPtr->length <= CANIF_STATIC_BUFFER_SIZE)
                         {
                              /* Queue information */
                              CanIf_TxBufferPrioByCanIdQueuePdu(localPduPtr); 
 
                              /*  Set queue flag for current PDU and return E_OK */
                              (void)CanIf_SetPrioByCanIdTxPduAsQueued(localPduPtr->swPduHandle);
                              retval = E_OK;
                         }
                         else
                         {
                              errorId = (uint8_t)CANIF_ERROR;

                              retval = E_NOT_OK;
                         }

                    break;

                    default:
                    /* Other Buffer handling method are not supported */
                    break;
                         
         
               }

#endif 
          }          
     }
     else
     {
          retval = E_NOT_OK;
     }
    

     if (errorId != (uint8_t)CANIF_NO_ERROR)
     {
        /* Development Error CallBack Function */
     }



     return retval;
  
}
#ifdef CANIF_BASIC_CAN
/***********************************************************************************************************************
 * NAME:  CanIf_TxBufferPrioByCanIdQueuePdu
 ***********************************************************************************************************************
 *  \brief       Stores a PDU within the Tx-buffer of type: PRIO_BY_CANID
 *  \details     Called out of CanIf_TransmitSubHandleTxResBusy().
 *  \param[in]   PduInfoPtr:  Contains length, PduId and datapointer.
 *  \pre         Must be called within entered CANIF_EXCLUSIVE_AREA_1 or CANIF_EXCLUSIVE_AREA_4
 *  \context     ANY
 **********************************************************************************************************************/ 

void CanIf_TxBufferPrioByCanIdQueuePdu(const Can_PduType* PduInfoPtr)
{
     uint32_t queueindex;
     queueindex = CANIF_CFG_TX_QUEUEINDEX(PduInfoPtr->swPduHandle); 
  
     CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(queueindex, eQueueParams.eBaseParams.eSduLength) = PduInfoPtr->length; 

     memcpy(CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(queueindex, eQueueParams.eSdu), PduInfoPtr->sdu, PduInfoPtr->length); 


}

/**********************************************************************************************************************
| NAME:  CanIf_SetPrioByCanIdTxPduAsQueued
 **********************************************************************************************************************
 *  \brief       Sets the flag "is buffered".
 *  \details     This API sets the flag of the corresponding TxPdu and returns if it was set before.
 *               Called out of CanIf_TransmitSubHandleTxResBusy()
 *  \param[in]   PduId: Internal Tx-PDU ID for which the "is buffered" flag is set. Parameter must be smaller than CANIF_CFG_MAX_TXPDUS.
 *  \return      E_OK: PduId was not already buffered.
 *               E_NOT_OK: PduId was already buffered.
 *  \pre         Check if a PrioByCanId transmit buffer is assigned to the TxPdu.
 *  \context     ANY
 **********************************************************************************************************************/

Std_ReturnType CanIf_SetPrioByCanIdTxPduAsQueued(PduIdType PduId)
{

  uint16_t txBufferCfgIdx;
  Std_ReturnType retval = E_NOT_OK;
  txBufferCfgIdx = CANIF_CFG_MAILBOX_TXBUFFERIDX(CANIF_CFG_TX_HTH(PduId));

  if (CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(PduId), eQueued) == 0u)
  {
    /* If not already set do it now and increment counter */
    CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(PduId), eQueued) = 1u; 

    ++CanIf_GetTxBufferPrioByCanIdBase(CANIF_CFG_BUFFERBASEIDX_TXBUFFERPRIOBYCANIDBYTEQUEUE(txBufferCfgIdx)).eQueueCounter;

    retval = E_OK;
  }

  return retval; 
}

/**********************************************************************************************************************
 * NAME:  CanIf_ClearPrioByCanIdTxPduAsQueued
 **********************************************************************************************************************
 *  \brief       Resets the flag "is buffered".
 *  \details     This API resets the flag of the corresponding TxPdu and returns if it was reset before.
 *               Called out of CanIf_Transmit(), CanIf_TxQueueTransmit(). 
 *  \param[in]   PduId: Internal Tx-PDU ID for which the "is buffered" flag is reset. Parameter must be smaller than CANIF_CFG_MAX_TXPDUS.
 *  \return      E_OK: PduId was not already buffered.
 *               E_NOT_OK: PduId was already buffered.
 *  \pre         Check if a PrioByCanId transmit buffer is assigned to the TxPdu.
 *  \context     ANY
 **********************************************************************************************************************/

Std_ReturnType CanIf_ClearPrioByCanIdTxPduAsQueued(PduIdType PduId)
{
     uint32_t txBufferCfgIdx;
     Std_ReturnType retval = E_NOT_OK;
     txBufferCfgIdx = CANIF_CFG_MAILBOX_TXBUFFERIDX(CANIF_CFG_TX_HTH(PduId));

       /* Is flag set for given PduId ?*/
     if (CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(PduId), eQueued) == 1u)
     {
       /* If set clear it and decrement counter */
       CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(PduId), eQueued) = 0u; 
       --CanIf_GetTxBufferPrioByCanIdBase(CANIF_CFG_BUFFERBASEIDX_TXBUFFERPRIOBYCANIDBYTEQUEUE(txBufferCfgIdx)).eQueueCounter;
       retval = E_OK;
     }

     return retval;

}

/***********************************************************************************************************************
 * NAME:  CanIf_TxQueueTreatment
 **********************************************************************************************************************
 * \brief       Checks if queued PDUs have to be transmitted.
 *  \details     Called out of CanIf_TxConfirmation().
 *  \param[in]   hth: Index of the hardware transmit handle. Parameter must be smaller than CANIF_CFG_MAX_MAILBOXES.
 *  \return      E_OK: Any Tx-PDU transmitted.
 *               E_NOT_OK: No Tx-PDU transmitted.
 *  \pre         Must be called with entered critical section in order to secure the Tx-queue.
 *               Must only be called for "hth" to which any Tx-buffer is mapped.        
 *  \context     ANY
 **********************************************************************************************************************/

Std_ReturnType CanIf_TxQueueTreatment(uint8_t hth)
{
    uint32_t idx2MappedTxPdus;

    uint32_t txBufferPrioByCanIdBaseIdx;
    Std_ReturnType retval;
    uint32_t txBufferCfgIdx;

    retval = E_NOT_OK;

    txBufferCfgIdx = CANIF_CFG_MAILBOX_TXBUFFERIDX(hth);

    switch (CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE(hth))
    {
          case CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID:
               /* PRIO_BY_CANID: BYTE_QUEUE handling: */
               txBufferPrioByCanIdBaseIdx = CANIF_CFG_BUFFERBASEIDX_TXBUFFERPRIOBYCANIDBYTEQUEUE(txBufferCfgIdx);
       
               /*  Anything buffered? */
               if (CanIf_GetTxBufferPrioByCanIdBase(txBufferPrioByCanIdBaseIdx).eQueueCounter != 0u)
               {
                    /*  Compute the next buffered PDU ID with the highest priority */  
                    for (idx2MappedTxPdus = (uint32_t)((uint32_t)(CANIF_CFG_STOPIDX_TXBUFFERPRIOBYCANIDBYTEQUEUE(txBufferCfgIdx)) - 1U); 
                         idx2MappedTxPdus >= (uint32_t)CANIF_CFG_STARTIDX_TXBUFFERPRIOBYCANIDBYTEQUEUE(txBufferCfgIdx); 
                         idx2MappedTxPdus--)       
                    {
                         uint32_t TxPduId;
                         TxPduId = CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_MAPPEDTXPDUS(idx2MappedTxPdus);
          
                         if (CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(TxPduId), eQueued) != 0u)
                         {
                              /* Send and remove from queue */
                              /*  Call CanIf_TxQueueTransmit() for the corresponding TxPdu ID */
                              retval = CanIf_TxQueueTransmit((PduIdType)TxPduId);
                              break;
                         }
                     }

               }
 
          break;

          default:
          /* Other Buffer handling method are not supported */
          break;
    }

    return retval;

}

/***********************************************************************************************************************
 * NAME:  CanIf_TxQueueTransmit
 **********************************************************************************************************************
 *  \brief       Transmits a Tx-PDU and removes it from the Tx-queue.
 *  \details     Called out of CanIf_TxQueueTreatment().
 *  \param[in]   PduId: Internal Tx-PDU ID. Parameter must be smaller than CANIF_CFG_MAX_TXPDUS. 
 *  \return      E_OK: Can_Write returned with E_OK or BUSY.
 *               E_NOT_OK: Can_Write returned with E_NOT_OK.
 *  \pre         Must be called with entered critical section in order to secure Tx-queue.
 *  \context     ANY
 **********************************************************************************************************************/
Std_ReturnType CanIf_TxQueueTransmit ( PduIdType PduId)
{
  static Can_PduType localPdu;
  Can_ReturnType txResult;
  Std_ReturnType retval;
  uint32_t hth;
  
  uint8_t errorId = (uint8_t)CANIF_NO_ERROR;

  retval = E_NOT_OK;

  if (PduId >= CANIF_CFG_MAX_TXPDUS)
  {
    
    errorId = (uint8_t)CANIF_ERROR;
  }
  else
  {
      hth = CANIF_CFG_TX_HTH(PduId);

      switch (CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE(hth))
      {
          case CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID:

            (localPdu).id = CANIF_CFG_TX_CANID(PduId);
            (localPdu).length = (uint8_t)CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(PduId), eQueueParams.eBaseParams.eSduLength);

            (localPdu).sdu = CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(PduId), eQueueParams.eSdu);

            (localPdu).swPduHandle = (PduId);
          break;

          default:
          /* Other Buffer handling method are not supported */
          break;
      }

      txResult = Can_Write((uint8_t)(hth + 1U), &localPdu); 

      if (txResult == CAN_OK)  
      {
        switch (CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE(hth))
        {
            case CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID:

                (void)CanIf_ClearPrioByCanIdTxPduAsQueued(PduId);

            break;

            default:
            /* Other Buffer handling method are not supported */
            break;

        }

        retval = E_OK;
      }
      else if(txResult == CAN_BUSY)
      {
        /* also ok due to confirmation queue handling may be interrupted by CanIf_Transmit() or just a cancel request */
        retval = E_OK; 
      }
      else
      {
           /* code */
      }
      


  }

  if (errorId != (uint8_t)CANIF_NO_ERROR)
  {
    /* Development Error CallBack Function */
  }

  return retval;

}


/***********************************************************************************************************************
 * NAME:  CanIf_ClearQueue
 ***********************************************************************************************************************
 * \brief       Initializes and resets the Tx-queue.
 *  \details     This API initializes the Tx-queue for CAN channel given by CANIF_CHANNEL_CANTYPE_ONLY. 
 *               Called out of CanIf_SetControllerMode(), CanIf_ControllerBusOff(), CanIf_SetPduMode(), CanIf_Init().
 *  \param[in]   CANIF_CHANNEL_CANTYPE_ONLY: Index of CAN channel. Parameter must be smaller than CANIF_CFG_MAX_CONTROLLER.
 *  \pre         Check if parameter is in range from 0 to CANIF_CFG_MAX_CONTROLLER-1.
 *  \context     ANY
 **********************************************************************************************************************/

static void CanIf_ClearQueue(uint8_t Channel)
{
  uint32_t idx2MappedTxBufferCfg;
  uint32_t hth;
  uint32_t txBufferBaseIdx;
  uint32_t MappedTxPdusIdx;
  uint32_t TxPduId;


  for(idx2MappedTxBufferCfg = CANIF_CFG_STARTIDX_2_MAPPEDTXBUFFERS(Channel);
      idx2MappedTxBufferCfg < CANIF_CFG_STOPIDX_2_MAPPEDTXBUFFERS(Channel);
      idx2MappedTxBufferCfg++ ) 
  {
    uint32_t txBufferCfgIdx;
    hth = CANIF_CFG_MAPPEDTXBUFFERS(idx2MappedTxBufferCfg); /* hth to access CanIf_MailBoxConfig[] */
    txBufferCfgIdx = CANIF_CFG_MAILBOX_TXBUFFERIDX(hth);
    /*  Clear the Tx-buffer dependent on it's Tx-buffer handling type */
    switch (CanIf_MailBoxConfig[hth].TxBufferHandlingTypeOfMailBoxConfig)
    {
        case CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID:
                /* Clearing of PRIO_BY_CANID: BYTE_QUEUE */

        for (MappedTxPdusIdx = CANIF_CFG_STARTIDX_TXBUFFERPRIOBYCANIDBYTEQUEUE(txBufferCfgIdx);
             MappedTxPdusIdx < CANIF_CFG_STOPIDX_TXBUFFERPRIOBYCANIDBYTEQUEUE(txBufferCfgIdx); 
             MappedTxPdusIdx++)
        {
          TxPduId =  CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_MAPPEDTXPDUS(MappedTxPdusIdx);
          CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(TxPduId), eQueued) = 0;
        }
        txBufferBaseIdx = CANIF_CFG_BUFFERBASEIDX_TXBUFFERPRIOBYCANIDBYTEQUEUE(txBufferCfgIdx);


        /*  Set QueueCounter to 0 */
        CanIf_SetTxQueueCounter(txBufferBaseIdx, 0);
        break;

        default:  
        /* Other Buffer handling method are not supported */
        break;

    }    
  }
}
#endif
/**********************************************************************************************************************
                                                R E V I S I O N   H I S T O R Y                                        
***********************************************************************************************************************
**********************************************************************************************************************
     REVISION NUMBER      : V1.0.4
     REVISION DATE        : 15/11/2021
     CREATED / REVISED BY : Rajasekar T(rajasekar@niyatainfotech.com)
     DESCRIPTION          : Implementent Functional Safety Features
-------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.0.3
     REVISION DATE        : 28/08/2021
     CREATED / REVISED BY : Rajasekar T(rajasekar@niyatainfotech.com)
     DESCRIPTION          : Silent Mode (Listen only mode) Feature code is integrated(Taken from SPT Branch).
-------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.0.2                                                                                   
     REVISION DATE        : 28/07/2020
     CREATED / REVISED BY : Prabhu R (prabhu.r@niyatainfotech.com)
     DESCRIPTION          : Added the Multi-Channel Configuration
---------------------------------------------------------------------------------------------------------------------
**********************************************************************************************************************
     REVISION NUMBER      : V1.0.1                                                                                   
     REVISION DATE        : 05/03/2020
     CREATED / REVISED BY : Akshay Bavalatti (akshayb@niyatainfotech.com)
     DESCRIPTION          : Compiler Warning and MISRA fix
---------------------------------------------------------------------------------------------------------------------
**********************************************************************************************************************
     REVISION NUMBER      : V1.0.0
     REVISION DATE        : 13/01/2020                                                                               
     CREATED / REVISED BY : Akshay Bavalatti (akshayb@niyatainfotech.com)                                        
     DESCRIPTION          : Initial version                                                                          
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
