#ifndef CANIF_CFG_H
#define CANIF_CFG_H
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
*  File name                       : CanIF_cfg.h                                                                         
*  Version                         : v4.3.20   
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
/* ====================================================================================================================
*                          I N C L U D E   F I L E S
* ===================================================================================================================*/

#include "CanIF_Types.h"
#include "CanIF_cbk.h"
#include "CanMgr_cfg.h"
//#include "CAN_Driver_cfg.h"
/* ====================================================================================================================
 *                          C O N F I G U R A T I O N
* ===================================================================================================================*/


#define NOT_AUTOSAR_IMPLEMENTATION

#define CANIF_TOTAL_TX_BUFFER_MESSAGE    0U

#define CANIF_TOTAL_NUM_OF_MAILBOX_CONIGURED_TO_STORE_TX_BUFFERS 0U

#define CANIF_TOTAL_RX_PDU                    18U

#define CANIF_TOTAL_TX_MESSAGES          10U

#define CANIF_TOTAL_RX_INIDICATION_FUNC   5U

#define CANIF_TOTAL_NUM_OF_MAIL_BOX           128U

#define CANIF_CFG_RX_MAXVALIDRXDLC       64U

#define CANIF_CFG_MAX_MAILBOXES          128U

#define CANIF_CFG_MAX_TXPDUS  CANIF_TOTAL_TX_MESSAGES

#define CANIF_CFG_MAX_RXPDUS            CANIF_TOTAL_RX_PDU

#define CANIF_CFG_MAX_RXINDICATIONS     CANIF_TOTAL_RX_INIDICATION_FUNC


#define CANIF_TOTAL_TX_CONFIRMATION_FUNC_LIST 5U

#define CANIF_STATE_MACHINE_ERROR_COUNTER_LIMIT  5U

#define CANIF_STATE_MACHINE_TIMEOUT_LIMIT        5U

#define CANIF_WAIT_FOR_SLEEP_TIMEOUT    10U

#ifdef CANIF_BASIC_CAN
typedef union CanIf_TxQueueUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  CanIf_TxPrioByCanIdByteQueueType raw[CANIF_TOTAL_TX_BUFFER_MESSAGE];
} CanIf_TxQueueUType;
#endif

typedef union CanIf_CtrlStatesUTag
{
  CanIf_CtrlStatesType raw[CAN_TOTAL_NUMBER_OF_CHANNELS];
} CanIf_CtrlStatesUType;

#ifdef CANIF_BASIC_CAN
/**   \brief  type to access CanIf_TxBufferPrioByCanIdBase in an index and symbol based style. */
typedef union CanIf_TxBufferPrioByCanIdBaseUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  CanIf_TxBufferPrioByCanIdBaseType raw[CANIF_TOTAL_NUM_OF_MAILBOX_CONIGURED_TO_STORE_TX_BUFFERS];
} CanIf_TxBufferPrioByCanIdBaseUType;
#endif

/**********************************************************************************************************************
  CanIf_BusOffNotificationFctPtr
**********************************************************************************************************************/

/**
 * 
 */ 
extern const CanIf_BusOffNotificationFctType CanIf_BusOffNotificationFctPtr;

#ifdef CANIF_BASIC_CAN
/**********************************************************************************************************************
 CanIf_CanIfCtrlId2MappedTxBuffersConfig
**********************************************************************************************************************/
/** 
 \var    CanIf_CanIfCtrlId2MappedTxBuffersConfig
 \brief  CAN controller configuration - mapped Tx-buffer(s).
 \details
Element                          Description
MappedTxBuffersConfigEndIdx      the end index of the 1:n relation pointing to CanIf_MappedTxBuffersConfig
MappedTxBuffersConfigStartIdx    the start index of the 1:n relation pointing to CanIf_MappedTxBuffersConfig
*/ 
extern const CanIf_CanIfCtrlId2MappedTxBuffersConfigType CanIf_CanIfCtrlId2MappedTxBuffersConfig[CAN_TOTAL_NUMBER_OF_CHANNELS];
#endif
/**********************************************************************************************************************
  CanIf_CtrlModeIndicationFctPtr
**********************************************************************************************************************/

extern const CanIf_CtrlModeIndicationFctType CanIf_CtrlModeIndicationFctPtr;

/**********************************************************************************************************************
 CanIf_MailBoxConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_MailBoxConfig
 \brief  Mailbox table.
\details
Element                 Description
CtrlStatesIdx           the index of the 1:1 relation pointing to CanIf_CtrlStates
PduIdFirst              "First" PDU mapped to mailbox.
PduIdLast               "Last" PDU mapped to mailbox.
TxBufferCfgIdx          the index of the 0:1 relation pointing to CanIf_TxBufferPrioByCanIdByteQueueConfig
TxBufferHandlingType
MailBoxType             Type of mailbox: Rx-/Tx- BasicCAN/FullCAN/unused.
*/ 
extern const CanIf_MailBoxConfigType CanIf_MailBoxConfig[CANIF_TOTAL_NUM_OF_MAIL_BOX];

#ifdef CANIF_BASIC_CAN
/**********************************************************************************************************************
 CanIf_MappedTxBuffersConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_MappedTxBuffersConfig
\brief  Mapped Tx-buffer(s)
\details
Element             Description
MailBoxConfigIdx    the index of the 1:1 relation pointing to CanIf_MailBoxConfig
*/ 
extern const CanIf_MappedTxBuffersConfigType CanIf_MappedTxBuffersConfig[CANIF_TOTAL_NUM_OF_MAILBOX_CONIGURED_TO_STORE_TX_BUFFERS];
#endif
/**********************************************************************************************************************
 CanIf_RxIndicationFctList
**********************************************************************************************************************/
/** 
  \var    CanIf_RxIndicationFctList
 \brief  Rx indication functions table.
\details
Element               Description
RxIndicationFct       Rx indication function.
RxIndicationLayout    Layout of Rx indication function.
*/
extern const CanIf_RxIndicationFctListType CanIf_RxIndicationFctList[CANIF_TOTAL_RX_INIDICATION_FUNC];

/**********************************************************************************************************************
  CanIf_RxPduConfig
**********************************************************************************************************************/
/** 
 \var    CanIf_RxPduConfig
 \brief  Rx-PDU configuration table.
 \details
 Element                   Description
 RxPduCanId                Rx-PDU: CAN identifier.
 RxPduMask                 Rx-PDU: CAN identifier mask.
 UpperPduId                PDU ID defined by upper layer.
Dlc                       Data length code.
 RxIndicationFctListIdx    the index of the 1:1 relation pointing to CanIf_RxIndicationFctList
*/ 
extern const CanIf_RxPduConfigType CanIf_RxPduConfig[CANIF_TOTAL_RX_PDU];


#ifdef CANIF_BASIC_CAN
/**********************************************************************************************************************
  CanIf_TxBufferPrioByCanIdByteQueueConfig
**********************************************************************************************************************/
/** 
 \var    CanIf_TxBufferPrioByCanIdByteQueueConfig
 \brief  Tx-buffer: PRIO_BY_CANID as BYTE_QUEUE
 \details
 Element      Description
TxBufferPrioByCanIdBaseIdx                          the index of the 1:1 relation pointing to CanIf_TxBufferPrioByCanIdBase
TxBufferPrioByCanIdByteQueueMappedTxPdusEndIdx      the end index of the 1:n relation pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
 TxBufferPrioByCanIdByteQueueMappedTxPdusLength      the number of relations pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
TxBufferPrioByCanIdByteQueueMappedTxPdusStartIdx    the start index of the 1:n relation pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
*/

extern const CanIf_TxBufferPrioByCanIdByteQueueConfigType CanIf_TxBufferPrioByCanIdByteQueueConfig[CANIF_TOTAL_NUM_OF_MAILBOX_CONIGURED_TO_STORE_TX_BUFFERS];

/**********************************************************************************************************************
 CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
**********************************************************************************************************************/
/** 
 \var    CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
\brief  Tx-buffer: PRIO_BY_CANID as BYTE_QUEUE: Mapped Tx-PDUs
 \details
 Element           Description
TxPduConfigIdx    the index of the 1:1 relation pointing to CanIf_TxPduConfig
*/ 

extern const CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdusType CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus[CANIF_TOTAL_TX_BUFFER_MESSAGE];
#endif

/**********************************************************************************************************************
 CanIf_TxConfirmationFctList
**********************************************************************************************************************/
/** 
  \var    CanIf_TxConfirmationFctList
 \brief  Tx confirmation functions table.
*/ 
extern const CanIf_TxConfirmationFctType CanIf_TxConfirmationFctList[CANIF_TOTAL_TX_CONFIRMATION_FUNC_LIST];

/**********************************************************************************************************************
 CanIf_TxPduConfig
**********************************************************************************************************************/
/** 
 \var    CanIf_TxPduConfig
 \brief  Tx-PDUs - configuration.
 \details
 Element                     Description
CanId                       CAN identifier (16bit / 32bit).
UpperLayerTxPduId           Upper layer handle ID (8bit / 16bit).
CtrlStatesIdx               the index of the 1:1 relation pointing to CanIf_CtrlStates
Dlc                         Data length code.
MailBoxConfigIdx            the index of the 1:1 relation pointing to CanIf_MailBoxConfig
TxConfirmationFctListIdx    the index of the 1:1 relation pointing to CanIf_TxConfirmationFctList
*/ 
extern const CanIf_TxPduConfigType CanIf_TxPduConfig[CANIF_TOTAL_TX_MESSAGES];

#ifdef CANIF_BASIC_CAN
/**********************************************************************************************************************
 CanIf_TxPduQueueIndex
**********************************************************************************************************************/
/** 
 \var    CanIf_TxPduQueueIndex
 \brief  Indirection table: Tx-PDU handle ID to corresponding Tx buffer handle ID. NOTE: Only BasicCAN Tx-PDUs have a valid indirection into the Tx buffer.
 \details
 Element       Description
TxQueueIdx    the index of the 0:1 relation pointing to CanIf_TxQueue
*/ 
extern const CanIf_TxPduQueueIndexType CanIf_TxPduQueueIndex[CANIF_TOTAL_TX_MESSAGES];
#endif
/**********************************************************************************************************************
  CanIf_CtrlStates
**********************************************************************************************************************/
/** 
 \var    CanIf_CtrlStates
 \details
 Element     Description
CtrlMode    Controller mode.
PduMode     PDU mode state.
*/ 
extern CanIf_CtrlStatesUType CanIf_CtrlStates;

#ifdef CANIF_BASIC_CAN
/**********************************************************************************************************************
 CanIf_TxBufferPrioByCanIdBase
**********************************************************************************************************************/
/** 
  \var    CanIf_TxBufferPrioByCanIdBase
 \brief  Variable declaration - Tx-buffer: PRIO_BY_CANID as byte/bit-queue. Stores at least the QueueCounter.
*/
extern CanIf_TxBufferPrioByCanIdBaseUType CanIf_TxBufferPrioByCanIdBase;

/**********************************************************************************************************************
  CanIf_TxQueue
**********************************************************************************************************************/
/** 
 \var    CanIf_TxQueue
 \brief  Variable declaration - Tx byte queue.
*/
extern CanIf_TxQueueUType CanIf_TxQueue;
#endif
#endif



/**********************************************************************************************************************
                                                  R E V I S I O N   H I S T O R Y             
************************************************************************************************************************/
/**********************************************************************************************************************
  REVISION NUMBER      : V1.0.0                                                                                   
  REVISION DATE        : 13/01/2020                                                                               
  CREATED / REVISED BY : Akshay Bavalatti (akshayb@niyatainfotech.com)                                        
  DESCRIPTION          : Initial Version                                                                       
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
