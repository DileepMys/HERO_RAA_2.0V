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
 *  File name                       : CanTp.c                                                                        
 *  Version                         : V1.1.1
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
 *                                  I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "CanMgr.h"
#include "CanIF.h"
#include "CanTp.h"

#define CANTP_Tx_CF_Timecnt           (uint16_t)(CANTP_TX_CF_TIME_INMSEC          / CANTP_PERIODICITY)
#define CANTP_Wait_FC_Timecnt         (uint16_t)(CANTP_WAIT_FC_TIME_INMSEC        / CANTP_PERIODICITY)
#define CANTP_Wait_CF_Timecnt         (uint16_t)(CANTP_WAIT_CF_TIME_INMSEC        / CANTP_PERIODICITY)
#define CANTP_Wait_TXConf_Timecnt     (uint16_t)(CANTP_TX_WAIT_CONF_TIME_INMSEC   / CANTP_PERIODICITY)


/***********************************************************************************************************************
 *                                          M A C R O
 ***********************************************************************************************************************/
#define CANTP_LASTMSG_SF           ((uint8_t)0x00 == (l_CanTp_TxMsg_st.Data[0] & (uint8_t)0xF0 ))
#define CANTP_LASTMSG_FF           ((uint8_t)0x10 == (l_CanTp_TxMsg_st.Data[0] & (uint8_t)0xF0 ))
#define CANTP_LASTMSG_CF           ((uint8_t)0x20 == (l_CanTp_TxMsg_st.Data[0] & (uint8_t)0xF0 ))
#define CANTP_LASTMSG_FC           ((uint8_t)0x30 == (l_CanTp_TxMsg_st.Data[0] & (uint8_t)0xF0 ))

#define CANTP_FCCTS                ((uint8_t)0x30 == l_CanTp_RxMsg_st.Data[0])
#define CANTP_FCWAIT               ((uint8_t)0x31 == l_CanTp_RxMsg_st.Data[0])
#define CANTP_FCOVERFLOW           ((uint8_t)0x32 == l_CanTp_RxMsg_st.Data[0])

#define CANTP_MSGRCVD_SF           ((uint8_t)0x00 == (l_CanTp_RxMsg_st.Data[0] & (uint8_t)0xF0 ))
#define CANTP_MSGRCVD_FF           ((uint8_t)0x10 == (l_CanTp_RxMsg_st.Data[0] & (uint8_t)0xF0 ))
#define CANTP_MSGRCVD_CF           ((uint8_t)0x20 == (l_CanTp_RxMsg_st.Data[0] & (uint8_t)0xF0 ))
#define CANTP_MSGRCVD_FC           ((uint8_t)0x30 == (l_CanTp_RxMsg_st.Data[0] & (uint8_t)0xF0 ))

#define CANTP_TX_IN_PROGRESS       (l_CanTp_status_st.Tx_inprogress  !=  (uint8_t)(0))
#define CANTP_SET_TXINPROGRESS     (l_CanTp_status_st.Tx_inprogress   =  (uint8_t)(1))
#define CANTP_CLEAR_TXINPROGRESS   (l_CanTp_status_st.Tx_inprogress   =  (uint8_t)(0))

#define CANTP_RX_IN_PROGRESS       (l_CanTp_status_st.Rx_inprogress  !=  (uint8_t)(0))
#define CANTP_SET_RXINPROGRESS     (l_CanTp_status_st.Rx_inprogress   =  (uint8_t)(1)) 
#define CANTP_CLEAR_RXINPROGRESS   (l_CanTp_status_st.Rx_inprogress   =  (uint8_t)(0))
 
#define CANTP_MSGRCVD              (l_CanTp_status_st.MsgRcvd        !=  (uint8_t)(0))
#define CANTP_SET_MSGRCVD          (l_CanTp_status_st.MsgRcvd         =  (uint8_t)(1)) 
#define CANTP_CLEAR_MSGRCVD        (l_CanTp_status_st.MsgRcvd         =  (uint8_t)(0))

#define CANTP_SENDMSG              (l_CanTp_status_st.SendMsg        !=  (uint8_t)(0))
#define CANTP_SET_SENDMSG          (l_CanTp_status_st.SendMsg         =  (uint8_t)(1)) 
#define CANTP_CLEAR_SENDMSG        (l_CanTp_status_st.SendMsg         =  (uint8_t)(0))
 

#define CANTP_INC_SEQNUM           (l_CanTp_status_st.SeqNum++)
#define CANTP_INIT_SEQNUM          (l_CanTp_status_st.SeqNum          = (uint8_t)1U)
#define CANTP_CLEAR_SEQNUM         (l_CanTp_status_st.SeqNum          = (uint8_t)0U)

#define CANTP_SET_FC_CTS           (l_CanTp_status_st.FC_Status =       (uint8_t)0)
#define CANTP_SET_FC_WAIT          (l_CanTp_status_st.FC_Status =       (uint8_t)1)
#define CANTP_SET_FC_OF            (l_CanTp_status_st.FC_Status =       (uint8_t)2)
#define CANTP_FC_CTS               (l_CanTp_status_st.FC_Status ==      (uint8_t)0)
#define CANTP_FC_WAIT              (l_CanTp_status_st.FC_Status ==      (uint8_t)1)
#define CANTP_FC_OVERFLOW          (l_CanTp_status_st.FC_Status ==      (uint8_t)2)
#define CANTP_FC_STATUS            (l_CanTp_status_st.FC_Status)

#define CANTP_SET_RX_COMPLETE      (l_CanTp_status_st.Rx_Status  =      (uint8_t)1)
#define CANTP_SET_RX_ERROR         (l_CanTp_status_st.Rx_Status  =      (uint8_t)2)
#define CANTP_CLEAR_RX_COMPLETE    (l_CanTp_status_st.Rx_Status  =      (uint8_t)0)
#define CANTP_CLEAR_RX_ERROR       (l_CanTp_status_st.Rx_Status  =      (uint8_t)0)
#define CANTP_RX_STATUS_COMPLETE   (l_CanTp_status_st.Rx_Status  ==     (uint8_t)1)
#define CANTP_RX_STATUS_ERROR      (l_CanTp_status_st.Rx_Status  ==     (uint8_t)2)

#define CANTP_SET_TX_COMPLETE      (l_CanTp_status_st.Tx_Status  =      (uint8_t)1)
#define CANTP_SET_TX_ERROR         (l_CanTp_status_st.Tx_Status  =      (uint8_t)2)
#define CANTP_CLEAR_TX_COMPLETE    (l_CanTp_status_st.Tx_Status  =      (uint8_t)0)
#define CANTP_CLEAR_TX_ERROR       (l_CanTp_status_st.Tx_Status  =      (uint8_t)0)
#define CANTP_TX_STATUS_COMPLETE   (l_CanTp_status_st.Tx_Status  ==     (uint8_t)1)
#define CANTP_TX_STATUS_ERROR      (l_CanTp_status_st.Tx_Status  ==     (uint8_t)2)


#define CANTP_WAIT4FC              (l_CanTp_status_st.Wait4FC        !=  (uint8_t)(0))
#define CANTP_SET_WAIT4FC          (l_CanTp_status_st.Wait4FC         =  (uint8_t)(1)) 
#define CANTP_CLEAR_WAIT4FC        (l_CanTp_status_st.Wait4FC         =  (uint8_t)(0))

#define CANTP_START_TX_CF_TIMER      (l_CanTp_Timer_u16 = CANTP_Tx_CF_Timecnt)
#define CANTP_START_RX_FC_TIMER      (l_CanTp_Timer_u16 = CANTP_Wait_FC_Timecnt)
#define CANTP_START_RX_CF_TIMER      (l_CanTp_Timer_u16 = CANTP_Wait_CF_Timecnt)
#define CANTP_START_TX_CONF_TIMER    (l_CanTp_Timer_u16 = CANTP_Wait_TXConf_Timecnt)

#define CANTP_STOP_TIMER          (l_CanTp_Timer_u16  =  (uint16_t)0)
#define CANTP_TIMER_XPIRED        (l_CanTp_Timer_u16  == (uint16_t)0)

#define CANTP_SINGLEFRAME_LENGTH   0x07u
/***********************************************************************************************************************
 *                                    L O C A L     V A R I A B L E S
 ***********************************************************************************************************************/
static uint16_t             l_CanTp_Timer_u16;
static CanTp_PDU            l_CanTp_TxMsg_st;
static CanTp_PDU            l_CanTp_RxMsg_st;
static uint8_t              l_CanTp_BlockSize_u8;
static uint8_t              l_CanTp_STmin_u8;
static uint8_t              l_CanTp_STminCntr_u8;
static uint8_t              l_CanTp_TxCFConfirm_u8;
static uint8_t              l_CanTp_FCwaitCntr_u8;
static CanTp_StatusType     l_CanTp_status_st;
static uint16_t             l_CanTp_DataCounter_u16;
static CanTp_SDU            l_CanTp_TxRx_st;
static CanTp_SDU*           l_CanTp_TxRxMsgptr = &l_CanTp_TxRx_st;
static uint8_t              l_CanTp_Config_BlockSize_u8;



static uint8_t l_CanTp_Padding_u8[8] = { CANTP_UNUSED_BYTE_VALUE,CANTP_UNUSED_BYTE_VALUE,CANTP_UNUSED_BYTE_VALUE,CANTP_UNUSED_BYTE_VALUE,CANTP_UNUSED_BYTE_VALUE,CANTP_UNUSED_BYTE_VALUE,CANTP_UNUSED_BYTE_VALUE,CANTP_UNUSED_BYTE_VALUE};
/***********************************************************************************************************************
 *                              P R O T O T Y P E    D E C L A R A T I O N
 ***********************************************************************************************************************/
static void CanTp_Wait4FC(void);

static void CanTp_TransmitCF(void);

static void CanTp_Receive(void);

static void CanTp_Memcpy(const uint8_t *fl_src_p_u8, uint8_t *fl_dst_p_u8, uint8_t fl_size_p_u8);

static void CanTp_SendFC(void);

static void CanTp_TransmitCFafterFC(void);

/***********************************************************************************************************************
 *                                    P U B L I C     F U N C T I O N
 ***********************************************************************************************************************/

/************************************************************************************************************
 * NAME:  CanTp_Init
 ************************************************************************************************************
 *  \brief         Intializes the global variable of TP layer .
 *  \details       -
 *  \param[in]     -
 *  \return        -
 *  \pre           -
 *  \context       ANY
***********************************************************************************************************/

void CanTp_Init(void)
{
   l_CanTp_Timer_u16      = (uint16_t)0;
   l_CanTp_BlockSize_u8   = (uint8_t)0;
   l_CanTp_STmin_u8       = (uint8_t)0;
   CANTP_CLEAR_TXINPROGRESS;
   CANTP_CLEAR_RXINPROGRESS;
   CANTP_CLEAR_SENDMSG;
   CANTP_CLEAR_MSGRCVD;
   l_CanTp_TxRxMsgptr = &l_CanTp_TxRx_st;
   l_CanTp_TxCFConfirm_u8 = (uint8_t)0;
   CANTP_CLEAR_WAIT4FC;

}

/************************************************************************************************************
 * NAME:  CanTp_MainFunction
 ************************************************************************************************************
 *  \brief         This is a Periodic Function, it manages the timeout
 *  \details       -
 *  \param[in]     -
 *  \return        -
 *  \pre           - CanTp_Init has to be called before invocation of this function
 *  \context       Time Task
***********************************************************************************************************/
void CanTp_MainFunction(void)
{
    Std_ReturnType ret;
    /*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
    /* call the watch dog alive counter function*/
    CAN_TP_ALIVE_COUNTER();
#endif
    if((uint16_t)0 != l_CanTp_Timer_u16)
    {
        l_CanTp_Timer_u16--;
    }
    else
    {
        /* l_CanTp_Timer_u16 value 0 */
    }

    if(CANTP_TX_IN_PROGRESS)
    {
        if(CANTP_TIMER_XPIRED)
        {
            CanMgr_CanTp_Tx_Confirmation(E_NOT_OK);
            CANTP_CLEAR_TXINPROGRESS;
            CANTP_CLEAR_SENDMSG;
            CANTP_CLEAR_MSGRCVD;
            CANTP_CLEAR_WAIT4FC;
        }
        else
        {
			if(CANTP_LASTMSG_FF || CANTP_LASTMSG_CF)
			{
				if(CANTP_WAIT4FC)
				{
					CanTp_Wait4FC();
				}
				else
				{
					CanTp_TransmitCF();
				}
			}
		}

    }
    else if(CANTP_RX_STATUS_COMPLETE)
    {
        CANTP_CLEAR_RX_COMPLETE;
        CanMgr_CanTp_RxIndication(E_OK);
    }
    else if(CANTP_RX_IN_PROGRESS)
    {
        if(CANTP_TIMER_XPIRED)
        {
            CanMgr_CanTp_RxIndication( E_NOT_OK);
            CANTP_CLEAR_RXINPROGRESS;
            CANTP_CLEAR_SENDMSG;
            CANTP_CLEAR_MSGRCVD;
        }
        else
        {
            /* Timer Not Expired */

        }
    }
    else
    {
        /* IDLE status */
    }

    if(CANTP_SENDMSG)
    {
        static PduInfoType fl_local_sdu_data_ptr;
        fl_local_sdu_data_ptr.SduDataPtr = &l_CanTp_TxMsg_st.Data[0];
        fl_local_sdu_data_ptr.SduLength  = 8;
/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS == STD_ON
         /*call local buffer*/
         CAN_Get_buffer(&fl_local_sdu_data_ptr);
#endif
        ret = CanIf_Transmit((PduIdType)CANTP_TRANSMIT_PDU_ID_4, &fl_local_sdu_data_ptr);

        if( E_OK == ret)
        {
            CANTP_CLEAR_SENDMSG;
        }
        else
        {
            /* Transmit service not accepted */
        }
    }
    else
    {
        /* No Transmition request */
    }
}

/************************************************************************************************************
 * NAME:  CanTp_RxIndication
 ************************************************************************************************************
 *  \brief         Indication about a received CAN message
 *  \details       This functions looks for if received CAN message matches one of the configured ones. If yes then the configured upper layer is notified.
 *  \param[in]     RxPduId: Pdu ID of the message received
 *  \param[in]     CanSduPtr: Pointer to data of received message
 *  \return        -
 *  \context       ISR
***********************************************************************************************************/
void CanTp_RxIndication( uint8_t RxPduId, const PduInfoType* PduInfoPtr)
{

    if( (PduInfoPtr != NULL) && ((RxPduId == (uint8_t)CANTP_RECEIVE_PHYS_PDU_ID_ABS) || 
                                 (RxPduId == (uint8_t)CANTP_RECEIVE_PHYS_PDU_ID_BCM) ||
                                 (RxPduId == (uint8_t)CANTP_RECEIVE_PHYS_PDU_ID_ECM) ||
                                 (RxPduId == (uint8_t)CANTP_RECEIVE_PHYS_PDU_ID_IC) ||
                                 (RxPduId == (uint8_t)CANTP_RECEIVE_PHYS_PDU_ID_TCU) ||
                                 (RxPduId == (uint8_t)CANTP_RECEIVE_FUNC_PDU_ID)))
    {
        l_CanTp_RxMsg_st.PduID = (PduIdType)RxPduId;
        l_CanTp_RxMsg_st.Size  = (uint8_t)PduInfoPtr->SduLength;
        CanTp_Memcpy(PduInfoPtr->SduDataPtr, &(l_CanTp_RxMsg_st.Data[0]), l_CanTp_RxMsg_st.Size);

        CANTP_SET_MSGRCVD;

        CanTp_Receive();
    }


}

/************************************************************************************************************
 * NAME:  CanTp_SetFC_Overflow
 ************************************************************************************************************
 *  \brief         Set the FS bits in the Flow Control  .
 *  \details       Flow Status bit is updated with 1 in the Flow Control
 *  \param[in]     -
 *  \return        -
 *  \pre           -
 *  \context       ANY
***********************************************************************************************************/
void CanTp_SetFC_Overflow(void)
{
    CANTP_SET_FC_OF;
}

/************************************************************************************************************
 * NAME:  CanTp_Transmit
 ************************************************************************************************************
 *  \brief               Initiates transmission of a Tx-message.
 *  \details             -
 *  \param[input]        length : Length to be transmitted
 *                       fl_Msgptr  : Data of Tx-PDU which shall be transmitted.
 *  \return              E_OK     : The request to transmit a Tx-PDU accepted.
 *                       E_NOT_OK : The request to transmit a Tx-PDU rejected.
 *  \pre           -
 *  \context       ANY
 *  \config        -
***********************************************************************************************************/
Std_ReturnType CanTp_Transmit(uint8_t * fl_Msgptr, uint16_t length)
{
	Std_ReturnType retStatus;
	uint8_t fl_CanTp_byte_location_u8;
    static PduInfoType fl_local_sdu_data_ptr;

	retStatus = E_NOT_OK;

    if((fl_Msgptr != NULL))
    {

	    if((!CANTP_TX_IN_PROGRESS) && (!CANTP_RX_IN_PROGRESS) && (length != (uint16_t)0))
	    {
	    	l_CanTp_TxRxMsgptr->Data    =  fl_Msgptr;
	    	l_CanTp_TxRxMsgptr->DataLength = length;
	    	
            l_CanTp_TxMsg_st.PduID   =  (PduIdType)CANTP_TRANSMIT_PDU_ID_4;
	    	l_CanTp_TxMsg_st.Size    =  (uint8_t)8;

	    	if((uint16_t)CANTP_SINGLEFRAME_LENGTH >= l_CanTp_TxRxMsgptr->DataLength)
	    	{
	    		l_CanTp_TxMsg_st.Data[0] =  (uint8_t)l_CanTp_TxRxMsgptr->DataLength;

	    		CanTp_Memcpy(l_CanTp_TxRxMsgptr->Data,&(l_CanTp_TxMsg_st.Data[1]),(uint8_t)l_CanTp_TxRxMsgptr->DataLength);

	    		if((uint16_t)CANTP_SINGLEFRAME_LENGTH > l_CanTp_TxRxMsgptr->DataLength )
	    		{
	    			l_CanTp_TxRxMsgptr->DataLength = ((uint16_t)CANTP_SINGLEFRAME_LENGTH - l_CanTp_TxRxMsgptr->DataLength);

	    			fl_CanTp_byte_location_u8 = (uint8_t)((uint8_t)CANTP_SINGLEFRAME_LENGTH - (uint8_t)l_CanTp_TxRxMsgptr->DataLength + (uint16_t)1);

	    			CanTp_Memcpy(&l_CanTp_Padding_u8[0], &(l_CanTp_TxMsg_st.Data[fl_CanTp_byte_location_u8]) , (uint8_t)l_CanTp_TxRxMsgptr->DataLength);
	    		}

	    		l_CanTp_TxRxMsgptr->DataLength = (uint16_t)0;

	    		l_CanTp_DataCounter_u16      =  (uint16_t)0;
	    	}
	    	else
	    	{
	    		CanTp_Memcpy(&(l_CanTp_TxRxMsgptr->Data[0]),&(l_CanTp_TxMsg_st.Data[2]), (uint8_t)6 );

	    		l_CanTp_TxMsg_st.Data[0]    =  (uint8_t)((uint8_t)0x10 + (uint8_t)(l_CanTp_TxRxMsgptr->DataLength >> (uint8_t)8));

	    		l_CanTp_TxMsg_st.Data[1]    =  (uint8_t) (l_CanTp_TxRxMsgptr->DataLength);

	    		l_CanTp_TxRxMsgptr->DataLength   -= (uint16_t)6;

	    		l_CanTp_DataCounter_u16         = (uint16_t)6;

	    		CANTP_INIT_SEQNUM;
	    		CANTP_SET_WAIT4FC;
	    	}

	    	CANTP_SET_TXINPROGRESS;
        
            fl_local_sdu_data_ptr.SduDataPtr = &l_CanTp_TxMsg_st.Data[0];
            fl_local_sdu_data_ptr.SduLength  = (uint8_t)8;
            /*Check the functional safety macro enable or Disable*/

#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS == STD_ON
                     /*call local buffer*/
                    CAN_Get_buffer(&fl_local_sdu_data_ptr);
#endif
            retStatus = CanIf_Transmit((PduIdType)CANTP_TRANSMIT_PDU_ID_4, &fl_local_sdu_data_ptr);

	    	if((uint8_t) E_OK == retStatus)
	    	{
	    		CANTP_CLEAR_SENDMSG;

	    	}
	    	else
	    	{
                /* Transmit service not accepted */
            }

	    	CANTP_START_TX_CONF_TIMER;
	    	
	    }
	    else
	    {
           /* Transmit service not accepted */
	    }
    }


	return(retStatus);
}

/************************************************************************************************************
 * NAME:  CanTp_CancelTransmit
 ************************************************************************************************************
 *  \brief               Cancel the transmission of a Tx-message.
 *  \details             -
 *  \param[input]        -
 *  \return              E_OK     : The request to Cancel transmit of Tx-PDU accepted.
 *                       E_NOT_OK : The request to Cancel transmit of Tx-PDU rejected.
 *  \pre           -
 *  \context       ANY
 *  \config        -
***********************************************************************************************************/
Std_ReturnType CanTp_CancelTransmit(void)
{
    Std_ReturnType retval = E_NOT_OK;

    if((CANTP_TX_IN_PROGRESS) && (!CANTP_RX_IN_PROGRESS) && (l_CanTp_TxRxMsgptr->DataLength > (uint16_t)7))
    {
        CANTP_CLEAR_TXINPROGRESS;
        CANTP_CLEAR_SENDMSG;
        CANTP_CLEAR_MSGRCVD;
        l_CanTp_TxCFConfirm_u8 = (uint8_t)0;
        l_CanTp_TxRxMsgptr->DataLength = (uint16_t)0;
		l_CanTp_DataCounter_u16      =  (uint16_t)0;
        CANTP_CLEAR_WAIT4FC;

        retval = E_OK;
    }
    return retval;
}

/************************************************************************************************************
 * NAME:  CanTp_CancelReception
 ************************************************************************************************************
 *  \brief               Cancel the Reception of a Rx-message.
 *  \details             -
 *  \param[input]        -
 *  \return              E_OK     : The request to Cancel Reception of Rx-PDU accepted.
 *                       E_NOT_OK : The request to Cancel Reception of Rx-PDU rejected.
 *  \pre           -
 *  \context       ANY
 *  \config        -
***********************************************************************************************************/
Std_ReturnType CanTp_CancelReception(void)
{
    Std_ReturnType retval = E_NOT_OK;
    if((!CANTP_TX_IN_PROGRESS) && (CANTP_RX_IN_PROGRESS) && (l_CanTp_DataCounter_u16 > (uint16_t)7))
    {
        CANTP_CLEAR_RXINPROGRESS;
        CANTP_CLEAR_SENDMSG;
        CANTP_CLEAR_MSGRCVD;

        retval = E_OK;
    }

    return retval;
}
/***********************************************************************************************************************
* NAME:  CanTp_TxConfirmation
 ***********************************************************************************************************************
 *  \brief       Confirmation for successful transmission.
 *  \details     -
 *  \param[in]   CanTxPduId: Internal ID of successful transmitted PDU.
 *  \pre         -
 *  \context     ISR
 **********************************************************************************************************************/
void CanTp_TxConfirmation(PduIdType PduId, Std_ReturnType result)
{

    if (   (PduId == (PduIdType)CANTP_TRANSMIT_PDU_ID_4) && 
           (result == E_OK) )
    {

        if(CANTP_LASTMSG_SF)
        {

            CANTP_CLEAR_TXINPROGRESS;
            CANTP_SET_TX_COMPLETE;
            CANTP_STOP_TIMER;

        }
        else if(CANTP_LASTMSG_FF)
        {
            CANTP_START_RX_FC_TIMER;
        }
        else if(CANTP_LASTMSG_CF)
        {
	    	l_CanTp_TxCFConfirm_u8 = (uint8_t)1;

            if(CANTP_WAIT4FC)
            {
                CANTP_START_RX_FC_TIMER;
            }
            else
            {
                 l_CanTp_STminCntr_u8 = (uint8_t)((l_CanTp_STmin_u8 / (uint8_t)CANTP_PERIODICITY) + (uint8_t)2);

                 CANTP_START_TX_CF_TIMER;
	    		 
            }
        }
        else if(CANTP_LASTMSG_FC)
        {
            CANTP_START_RX_CF_TIMER;
        }
        else
        {
            /* Improper frame received */
        }

        if(CANTP_TX_STATUS_COMPLETE)
        {
            CANTP_CLEAR_TX_COMPLETE;
            CanMgr_CanTp_Tx_Confirmation( E_OK);
        }

    }
}
/***********************************************************************************************************************
 *                                  P R I V A T E     F U N C T I O N
 ***********************************************************************************************************************/

/************************************************************************************************************
 * NAME:  CanTp_Receive
 ************************************************************************************************************
 *  \brief         This function validates the received message and performs the necessary action based 
 *                 on the received message.
 *  \details       
 *  \param[in]     -
 *  \return        -
 *  \pre           - 
 *  \context       ANY
***********************************************************************************************************/
static void CanTp_Receive(void)
{
    uint8_t ret;
	uint8_t fl_SF_DataLength_u8;

    if(CANTP_MSGRCVD_SF)
    {
        if(CANTP_RX_IN_PROGRESS)
        {
        
            CanMgr_CanTp_RxIndication( E_NOT_OK);
        
            CANTP_CLEAR_RXINPROGRESS;
        }
        else
        {
            /* CanTp is in the state of accepting RX messages */
		}

		fl_SF_DataLength_u8 = (uint8_t)(l_CanTp_RxMsg_st.Data[0] & (uint8_t)0x0F);

		if(l_CanTp_RxMsg_st.Size > fl_SF_DataLength_u8)
		{
			ret = CanMgr_CanTpStartOfReception(l_CanTp_RxMsg_st.PduID, l_CanTp_RxMsg_st.Data[0]);

			if ( ret ==  E_OK)
			{
				 CanMgr_CanTpRxInProgress(&l_CanTp_RxMsg_st.Data[1],l_CanTp_RxMsg_st.Data[0]);
				
                 CANTP_SET_RX_COMPLETE;

			}
			else
			{
				 CANTP_CLEAR_RXINPROGRESS;
			}

		}
		else
		{
            /* Data Length specified in the TP frame is more than the DLC */
        }

    }


    else if(CANTP_MSGRCVD_FF)
    {
        if(CANTP_RX_IN_PROGRESS)
        {
            CanMgr_CanTp_RxIndication( E_NOT_OK);

            CANTP_CLEAR_RXINPROGRESS;
        }
        else
        {
            /* CanTp is in the state of accepting RX messages */
		}



		l_CanTp_DataCounter_u16 = (uint16_t)(l_CanTp_RxMsg_st.Data[0] & (uint8_t)0x0FU);

		l_CanTp_DataCounter_u16 <<= (uint8_t)8;

		l_CanTp_DataCounter_u16 += (uint16_t)l_CanTp_RxMsg_st.Data[1];

		if((l_CanTp_DataCounter_u16 >= (uint16_t)8) && (l_CanTp_RxMsg_st.Size == (uint8_t)8))
		{
			ret = CanMgr_CanTpStartOfReception(l_CanTp_RxMsg_st.PduID, l_CanTp_DataCounter_u16);
			
            if ( ret ==  E_OK)
			{
				CANTP_SET_FC_CTS;
			
            	CanMgr_CanTpRxInProgress(&l_CanTp_RxMsg_st.Data[2], (uint8_t)6);
		
        		l_CanTp_BlockSize_u8 = (uint8_t)1;
		
        		CanTp_SendFC();
		
        		l_CanTp_DataCounter_u16 -= (uint16_t)6;
		
        		CANTP_CLEAR_SEQNUM;

				CANTP_SET_RXINPROGRESS;
			}
			else
			{

				if(CANTP_FC_OVERFLOW)
				{

					l_CanTp_BlockSize_u8 = (uint8_t)1;
					
                    CANTP_SET_FC_OF;
				
                	CanTp_SendFC();
				
                }
				CANTP_CLEAR_RXINPROGRESS;
			}
		}
		else
		{
            /* Length of Data to be received is less than 8 bytes or the size of the DLC of message received is less than 8 */
		}


    }

    else if(CANTP_MSGRCVD_CF)
    {

		if(CANTP_RX_IN_PROGRESS)
		{

			
            if(l_CanTp_status_st.SeqNum == (uint8_t)0x0F)
            {
                l_CanTp_status_st.SeqNum = (uint8_t)0x00;
            }
            else
            {
                CANTP_INC_SEQNUM;
            }
            

    
            if((uint16_t)7 >= l_CanTp_DataCounter_u16)
			{

				if(l_CanTp_status_st.SeqNum == (uint8_t)(l_CanTp_RxMsg_st.Data[0] & (uint8_t)0x0F))
				{
                    
					CanMgr_CanTpRxInProgress(&l_CanTp_RxMsg_st.Data[1], (uint8_t)l_CanTp_DataCounter_u16);

                    l_CanTp_DataCounter_u16 = (uint16_t)0;
						
                    CANTP_CLEAR_RXINPROGRESS;
						
                    CANTP_SET_RX_COMPLETE;
				}
				else
				{
				   CanMgr_CanTp_RxIndication( E_NOT_OK);
					
                   CANTP_CLEAR_RXINPROGRESS;
				}
			}
			else
            {
			    if((uint8_t)8 == l_CanTp_RxMsg_st.Size)
			    {
				  
                    if(l_CanTp_status_st.SeqNum == (uint8_t)(l_CanTp_RxMsg_st.Data[0] & (uint8_t)0x0F))
				    {
					  
                        CanMgr_CanTpRxInProgress(&l_CanTp_RxMsg_st.Data[1], (uint8_t)7);

                        CANTP_SET_FC_CTS;

                        CanTp_SendFC();

                        l_CanTp_DataCounter_u16 -= (uint16_t)7;
				    }
				    else
				    {
				
                	     CanMgr_CanTp_RxIndication( E_NOT_OK);
			
                	     CANTP_CLEAR_RXINPROGRESS;
				    }
			    }
                else
                {
				
                	CanMgr_CanTp_RxIndication( E_NOT_OK);
				
                	CANTP_CLEAR_RXINPROGRESS;
                }
                

		    }     

        }
        else
        {
           /* CanTp RX status is cleared, FF and FC has to be received */
        }
    }
        
    else if( (CANTP_WAIT4FC) && (CANTP_MSGRCVD_FC) )
    {
        if(l_CanTp_RxMsg_st.Size >= (uint8_t)3)
        {
        	CanTp_Wait4FC();
        }
    }

    else
    {
        /* Not a valid receive frame */
    }
    CANTP_CLEAR_MSGRCVD;

}
/************************************************************************************************************
 * NAME:  CanTp_Memcpy
 ************************************************************************************************************
 *  \brief         Copies the n bytes pointed by source to destination address. 
 *  \details       -
 *  \param[in]     fl_src_p_u8 - Pointer to the memory location where the contents are copied from.
 *  \param[in]     fl_dst_p_u8 - Pointer to the memory location where the contents are copied to
 *  \param[in]     fl_size_p_u8 - Number of bytes to copy from src to dest.
 *  \return        -
 *  \pre           -
 *  \context       ANY
***********************************************************************************************************/
static void CanTp_Memcpy(const uint8_t *fl_src_p_u8, uint8_t *fl_dst_p_u8, uint8_t fl_size_p_u8)
{
    uint8_t fl_size_u8 = fl_size_p_u8;
    const uint8_t *fl_src_u8 = fl_src_p_u8;
    uint8_t *fl_dst_u8 = fl_dst_p_u8;

    for( ; fl_size_u8 > (uint8_t)0 ; fl_size_u8--)
    {
        *fl_dst_u8 = *fl_src_u8;
        fl_dst_u8++;
        fl_src_u8++;
    }
}

/************************************************************************************************************
 * NAME:  CanTp_Wait4FC
 ************************************************************************************************************
 *  \brief         This function validates the received message is for Flow Control and perform the action
 *                 after validating the bits Flow Status (FS), Block Size (BS), Seperation Time (STmin)
 *  \details       00 – 7F SeparationTime (STmin) range: 0 ms – 127 ms
 *		           The units of STmin in the range 00 hex – 7F hex are absolute milliseconds (ms).
 *  	           80 – F0 Reserved
 *  	           This range of values is reserved by this part of ISO 15765.
 *  	           F1 – F9 SeparationTime (STmin) range: 100 μs – 900 μs
 *  	           The units of STmin in the range F1 hex – F9 hex are even 100 microseconds (μs), where parameter
 *  	           value F1 hex represents 100 μs and parameter value F9 hex represents 900 μs.
 *  	           FA – FF Reserved
 *  	           This range of values is reserved by this part of ISO 15765. 
 *  \param[in]     -
 *  \return        -
 *  \pre           - 
 *  \context       ANY
***********************************************************************************************************/
static void CanTp_Wait4FC(void)
{

    if(CANTP_WAIT4FC && CANTP_MSGRCVD)
    {
        if(CANTP_FCCTS)
        {
			CANTP_CLEAR_WAIT4FC;

            l_CanTp_FCwaitCntr_u8 = (uint8_t)0;
            
            l_CanTp_BlockSize_u8 = l_CanTp_RxMsg_st.Data[1];
            
            l_CanTp_STmin_u8     = l_CanTp_RxMsg_st.Data[2];

            /* refer the section \details  */
			if(l_CanTp_STmin_u8 > (uint8_t)0x7F)
			{
				l_CanTp_STmin_u8 = (uint8_t)0x7F;
			}
			
			l_CanTp_STminCntr_u8 = (uint8_t)0;

            CanTp_TransmitCFafterFC();            
        }
        else if(CANTP_FCWAIT)
        {

            l_CanTp_FCwaitCntr_u8++;
            
            if((uint8_t)CANTP_MAX_WAIT_CNT >= l_CanTp_FCwaitCntr_u8)
            {
                CANTP_START_RX_FC_TIMER;
            }
            else
            {
                l_CanTp_FCwaitCntr_u8 = (uint8_t)0;

                CanMgr_CanTp_Tx_Confirmation( E_NOT_OK);
                
                CANTP_CLEAR_TXINPROGRESS;
            }
        }
        else if(CANTP_FCOVERFLOW)
        {
                CanMgr_CanTp_Tx_Confirmation( E_NOT_OK);
            
                CANTP_CLEAR_TXINPROGRESS;
            
                CANTP_CLEAR_WAIT4FC;
        }
        else
        {
            if(CANTP_TIMER_XPIRED)
            {
            
                CanMgr_CanTp_Tx_Confirmation( E_NOT_OK);
            
                CANTP_CLEAR_TXINPROGRESS;
            
                CANTP_CLEAR_WAIT4FC;
            }
            else
            {
                /* Timer Not Expired */
            }
        }
        CANTP_CLEAR_MSGRCVD;
    }
    else
    {
        if(CANTP_TIMER_XPIRED)
        {
            CanMgr_CanTp_Tx_Confirmation( E_NOT_OK);
        
            CANTP_CLEAR_TXINPROGRESS;
        
            CANTP_CLEAR_WAIT4FC;
        
            CANTP_CLEAR_MSGRCVD;
        }
        else
        {
               /* Timer Not Expired */
        }
    }

}

/************************************************************************************************************
 * NAME:  CanTp_TransmitCF
 ************************************************************************************************************
 *  \brief         This function transmits the Consecutive Frame when the STmin Counter values reaches 0
 *  \details       -
 *  \param[in]     -
 *  \return        -
 *  \pre           -
 *  \context       ANY
***********************************************************************************************************/
static void CanTp_TransmitCF(void)
{

	if((uint8_t)0 != l_CanTp_STminCntr_u8)
    {
        l_CanTp_STminCntr_u8--;
    }
    else
    {
        /* l_CanTp_STminCntr_u8 value 0 */
    }

    if(((uint8_t)0 == l_CanTp_STminCntr_u8) && ((uint8_t)1 == l_CanTp_TxCFConfirm_u8))
    {
        CanTp_TransmitCFafterFC();
    }
    else
    {
        /* wait for  l_CanTp_STminCntr_u8 value 0 or CF transmition not confirmed */
    }

}

/************************************************************************************************************
 * NAME:  CanTp_TransmitCFafterFC
 ************************************************************************************************************
 *  \brief         This function transmits the Consecutive Frame.
 *  \details       -
 *  \param[in]     -
 *  \return        -
 *  \pre           This function has to be called only after Flow Control is received atleast once.
 *  \context       ANY
***********************************************************************************************************/
static void CanTp_TransmitCFafterFC(void)
{
    uint8_t fl_CanTp_byte_location_u8;
    Std_ReturnType retStatus;
    static PduInfoType fl_local_sdu_data_ptr;

	l_CanTp_TxMsg_st.Data[0] =  (uint8_t)((uint8_t)0x20 + l_CanTp_status_st.SeqNum);
    
    if((uint16_t)7 >= l_CanTp_TxRxMsgptr->DataLength)
    {
        l_CanTp_TxMsg_st.Size    =  (uint8_t)8;
        
        CanTp_Memcpy(&(l_CanTp_TxRxMsgptr->Data[l_CanTp_DataCounter_u16]),&(l_CanTp_TxMsg_st.Data[1]),(uint8_t)l_CanTp_TxRxMsgptr->DataLength);
        
        if((uint16_t)7U > l_CanTp_TxRxMsgptr->DataLength )
        {
          	l_CanTp_TxRxMsgptr->DataLength = (uint16_t)((uint16_t)CANTP_SINGLEFRAME_LENGTH - l_CanTp_TxRxMsgptr->DataLength);
        
           	fl_CanTp_byte_location_u8 = (uint8_t)((uint8_t)CANTP_SINGLEFRAME_LENGTH - (uint8_t)(l_CanTp_TxRxMsgptr->DataLength - (uint16_t)1u));
        
           	CanTp_Memcpy(&l_CanTp_Padding_u8[0], &(l_CanTp_TxMsg_st.Data[fl_CanTp_byte_location_u8]) , (uint8_t)l_CanTp_TxRxMsgptr->DataLength);
        }

        l_CanTp_TxRxMsgptr->DataLength = (uint16_t)0;
        
        CANTP_CLEAR_TXINPROGRESS;
        
        CANTP_CLEAR_MSGRCVD;
        
        CANTP_SET_TX_COMPLETE;
    }
    else
    {
        l_CanTp_TxMsg_st.Size    =  (uint8_t)8;
    
        CanTp_Memcpy(&(l_CanTp_TxRxMsgptr->Data[l_CanTp_DataCounter_u16]),&(l_CanTp_TxMsg_st.Data[1]),(uint8_t)7);
    
        l_CanTp_TxRxMsgptr->DataLength   -= (uint16_t)7;
        l_CanTp_DataCounter_u16         += (uint16_t)7;
    
        if(l_CanTp_status_st.SeqNum == (uint8_t)0x0F)
        {
            l_CanTp_status_st.SeqNum = (uint8_t)0x00;
        }
        else
        {
            CANTP_INC_SEQNUM;
        }       
    }

    l_CanTp_TxCFConfirm_u8 = (uint8_t)0;
    
            
    fl_local_sdu_data_ptr.SduDataPtr = &l_CanTp_TxMsg_st.Data[0];
    fl_local_sdu_data_ptr.SduLength  = (uint8_t)8;
    #if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS == STD_ON
                     /*call local buffer*/
                    CAN_Get_buffer(&fl_local_sdu_data_ptr);
    #endif
    retStatus = CanIf_Transmit((PduIdType)CANTP_TRANSMIT_PDU_ID_4, &fl_local_sdu_data_ptr);
    
    if((uint8_t) E_OK == retStatus)
    {
        CANTP_CLEAR_SENDMSG;
    }
    else
    {
        /* Transmit service not accepted */
    }

    CANTP_START_TX_CONF_TIMER;

    if(((uint8_t)0 != l_CanTp_BlockSize_u8) && (CANTP_TX_IN_PROGRESS))
    {
        l_CanTp_BlockSize_u8--;

        if((uint8_t)0 == l_CanTp_BlockSize_u8)
        {
            CANTP_SET_WAIT4FC;
        }
        else
        {
            /* l_CanTp_BlockSize_u8 value not 0 */
        }
    }
    else
    {
        /* l_CanTp_BlockSize_u8 value 0 or CanTp is not in Tx State*/
    }
    
}

/************************************************************************************************************
 * NAME:  CanTp_SendFC
 ************************************************************************************************************
 *  \brief         This function transmits the Flow Control Frame.
 *  \details       -
 *  \param[in]     -
 *  \return        -
 *  \pre           -
 *  \context       ANY
***********************************************************************************************************/
static void CanTp_SendFC(void)
{
    uint8_t ret;

    static PduInfoType fl_local_sdu_data_ptr;

    if((uint8_t)0 != l_CanTp_BlockSize_u8)
    {
        l_CanTp_BlockSize_u8--;
        
        if((uint8_t)0 == l_CanTp_BlockSize_u8)
        {

			l_CanTp_TxMsg_st.PduID    = (PduIdType)(CANTP_TRANSMIT_PDU_ID_4);
            l_CanTp_TxMsg_st.Size     = (uint8_t)0x08;
            l_CanTp_TxMsg_st.Data[0]  = (uint8_t)((uint8_t)0x30U | (CANTP_FC_STATUS));
            l_CanTp_TxMsg_st.Data[1]  = l_CanTp_Config_BlockSize_u8;
            l_CanTp_TxMsg_st.Data[2]  = (uint8_t)CANTP_STMIN;
            l_CanTp_BlockSize_u8      = l_CanTp_Config_BlockSize_u8;
						
            CanTp_Memcpy(&l_CanTp_Padding_u8[0], &(l_CanTp_TxMsg_st.Data[3]) , (uint8_t)5 );
                   
            
            fl_local_sdu_data_ptr.SduDataPtr = &l_CanTp_TxMsg_st.Data[0];
            fl_local_sdu_data_ptr.SduLength  = (uint8_t)8;
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS == STD_ON
                     /*call local buffer*/
                    CAN_Get_buffer(&fl_local_sdu_data_ptr);
#endif
            ret = CanIf_Transmit((PduIdType)CANTP_TRANSMIT_PDU_ID_4, &fl_local_sdu_data_ptr);
            
            
            if( E_OK == ret)
            {
                CANTP_CLEAR_SENDMSG;
            }
            else
            {
                 /* Transmit service not accepted */
            }

            CANTP_START_TX_CONF_TIMER;
        
        }
        else
        {
            /* l_CanTp_BlockSize_u8 value not 0 */
            
        }
    }
    else
    {
        CANTP_START_RX_CF_TIMER;
    }
}

/************************************************************************************************************
 * NAME:  CanTp_SendFC
 ************************************************************************************************************
 *  \brief         This function returns the transmission status
 *  \details       -
 *  \param[in]     -
 *  \return        -
 *  \pre           -
 *  \context       ANY
***********************************************************************************************************/
uint8_t CanTp_Get_Transmit_Status(void)
{
    return l_CanTp_status_st.Tx_inprogress;
}

/************************************************************************************************************
 * NAME:  CanTp_Rx_GetStatus
 ************************************************************************************************************
 *  \brief         This function indicates the Rx Status of TP when called.
 *  \details       -
 *  \param[in]     -
 *  \return        Status of the Receiving TP PDU
 *  \pre           -
 *  \context       ANY
***********************************************************************************************************/
uint8_t CanTp_Rx_GetStatus(void)
{
    return((uint8_t)l_CanTp_status_st.Rx_Status);
}

/************************************************************************************************************
 * NAME:  CanTp_Set_TPBlockSize
 ************************************************************************************************************
 *  \brief         This function will set the BS bits in the Flow Control
 *  \details       -
 *  \param[in]     fl_BlockSize_u8: Size of the block to be set in Flow Control
 *  \return        -
 *  \pre           -
 *  \context       ANY
***********************************************************************************************************/
void CanTp_Set_TPBlockSize(uint8_t fl_BlockSize_u8)
{
    l_CanTp_Config_BlockSize_u8 = fl_BlockSize_u8;
}



/***********************************************************************************************************************
 *                                     E N D   O F   S O F T W A R E                                          
***********************************************************************************************************************/
#ifdef __cplusplus
}
#endif
/**********************************************************************************************************************
                                                R E V I S I O N   H I S T O R Y                                        
***********************************************************************************************************************
**********************************************************************************************************************
     REVISION NUMBER      : V1.1.1
     REVISION DATE        : 15/11/2021
     CREATED / REVISED BY : Rajasekar T(rajasekar@niyatainfotech.com)
     DESCRIPTION          : Implementent Functional Safety Features
-------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.1.0
     REVISION DATE        : 30/05/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : MISRA Warnings Fix                                                                          
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.0.0
     REVISION DATE        : 26/03/2020                                                                               
     CREATED / REVISED BY : Akshay Bavalatti (akshayb@niyatainfotech.com)                                        
     DESCRIPTION          : Initial version                                                                          
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
