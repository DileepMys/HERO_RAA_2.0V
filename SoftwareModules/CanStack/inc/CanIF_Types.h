#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H
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
 *  File name                       : CanIF_Types.h                                                                         
 *  Version                         : V1.0.0                                                                           
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
#include "sys_common.h"
#include "CanStack_CommonTypes.h"

/*          M   A   C   R   O       */

#define CANIF_NO_ERROR          0U
#define CANIF_ERROR          1U

#define CANIF_SLEEP_STATUS_SET 1U
#define CANIF_SLEEP_STATUS_RESET 0U

#define CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG                        255U
#define CANIF_NO_TXQUEUEIDXOFTXPDUQUEUEINDEX                          255U

#define CanIf_TxPduHnd_INVALID                             0xFFU
#define CanIf_RxPduHnd_INVALID                             0xFFU

#define CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID                                                             1U
#define CANIF_TXBUFFER_HANDLINGTYPE_NONE                                                                    3U


/* hard coded array size */
#define CANIF_STATIC_BUFFER_SIZE              8u


typedef uint8_t PduLengthType; 


/*          E  N  U  M        */

typedef enum 
{
  CANIF_CS_STOPPED = 0,
  CANIF_CS_STARTED,
   CANIF_CS_UNINIT
} CanIf_ControllerModeType;

typedef enum 
{
  CANIF_OFFLINE = 0u,
  CANIF_RX_OFFLINE,
  CANIF_RX_ONLINE,
  CANIF_TX_OFFLINE,
  CANIF_TX_ONLINE,
  CANIF_ONLINE,
  CANIF_NO_MODE_PDU_MODE_TYPE_END 
} CanIf_PduModeType;

typedef enum
{
  CANIF_RxBasicCANMailbox = 0u,
  CANIF_RxFullCANMailbox,
  CANIF_TxBasicCANMailbox,
  CANIF_TxFullCANMailbox,
  CANIF_UnusedCANMailbox
} CanIf_MailBoxTypeType;

typedef enum
{
  CanIf_SimpleRxIndicationLayout = 0u,
  CanIf_AdvancedRxIndicationLayout,
  CanIf_NmRxIndicationLayout,
  CanIf_TpRxIndicationLayout,
} CanIf_RxIndicationLayoutType;


typedef struct
{
  const uint8_t* SduDataPtr;
  PduLengthType SduLength;
} PduInfoType;

typedef enum
{
     NETWORK_SLEEP  = 0,
     NETWORK_NORMAL = 1,
     NETWORK_SILENT = 2,
}CanIF_Network_Request_Type;


/*            F  U  N   C   T   I   O   N              P   T   R*/


typedef void (* CanIf_BusOffNotificationFctType) (uint8_t channel);

typedef void (* CanIf_CtrlModeIndicationFctType) (uint8_t ControllerId, CanIf_ControllerModeType ControllerMode);

typedef void (*CanIf_TxConfirmationFctType) (PduIdType CanTxPduId, Std_ReturnType Result);

typedef void (* CanIf_SimpleRxIndicationFctType) (PduIdType CanRxPduId, const uint8_t*  CanSduPtr);

typedef void (* CanIf_AdvancedRxIndicationFctType) (PduIdType CanRxPduId, const PduInfoType* PduInfoPtr);

typedef void (* CanIf_TpRxIndicationFctType) (PduIdType CanRxPduId, const PduInfoType* PduInfoPtr);

typedef void (* CanIf_NmRxIndicationFctType) (PduIdType CanRxPduId, const uint8_t* CanSduPtr, Can_IdType CanId);


/*          S  T  R  U  C  T        */

typedef struct sCanIf_PCConfigType
{
  uint8_t CanIf_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} CanIf_PCConfigType;

typedef CanIf_PCConfigType CanIf_ConfigType;

typedef struct sCanIf_CanIfCtrlId2MappedTxBuffersConfigType
{
  uint16_t EndIdx_MappedTxBuffersConfig;  /**< the end index of the 1:n relation pointing to CanIf_MappedTxBuffersConfig */
  uint16_t StartIdx_MappedTxBuffersConfig;  /**< the start index of the 1:n relation pointing to CanIf_MappedTxBuffersConfig */
} CanIf_CanIfCtrlId2MappedTxBuffersConfigType;

/**   \brief  type used in CanIf_MailBoxConfig */
typedef struct sCanIf_MailBoxConfigType
{
  uint8_t CtrlStatesIdxOfMailBoxConfig;  /**< the index of the 1:1 relation pointing to CanIf_CtrlStates */
  PduIdType PduIdFirstOfMailBoxConfig;  /**< "First" PDU mapped to mailbox. */
  PduIdType PduIdLastOfMailBoxConfig;  /**< "Last" PDU mapped to mailbox. */
  uint16_t TxBufferCfgIdxOfMailBoxConfig;  /**< the index of the 0:1 relation pointing to CanIf_TxBufferPrioByCanIdByteQueueConfig */
  uint8_t TxBufferHandlingTypeOfMailBoxConfig;
  CanIf_MailBoxTypeType MailBoxTypeOfMailBoxConfig;  /**< Type of mailbox: Rx-/Tx- BasicCAN/FullCAN/unused. */
} CanIf_MailBoxConfigType;

/**   \brief  type used in CanIf_MappedTxBuffersConfig */
typedef struct sCanIf_MappedTxBuffersConfigType
{
  uint8_t MailBoxConfigIdxOfMappedTxBuffersConfig;  /**< the index of the 1:1 relation pointing to CanIf_MailBoxConfig */
} CanIf_MappedTxBuffersConfigType;


typedef union
{ 
  CanIf_AdvancedRxIndicationFctType   eAdvancedRxIndicationType;
  CanIf_SimpleRxIndicationFctType     eSimpleRxIndicationType;
  CanIf_NmRxIndicationFctType         eNmRxIndicationType;
  CanIf_TpRxIndicationFctType         eTpRxIndicationType;
} CanIf_RxIndicationFctType;

typedef struct sCanIf_RxIndicationFctListType
{
  CanIf_RxIndicationFctType RxIndicationFctOfRxIndicationFctList;  /**< Rx indication function. */
  CanIf_RxIndicationLayoutType RxIndicationLayoutOfRxIndicationFctList;  /**< Layout of Rx indication function. */
} CanIf_RxIndicationFctListType;



/**   \brief  type used in CanIf_RxPduConfig */
typedef struct sCanIf_RxPduConfigType
{
  uint16_t RxPduCanIdOfRxPduConfig;  /**< Rx-PDU: CAN identifier. */
  uint16_t RxPduMaskOfRxPduConfig;  /**< Rx-PDU: CAN identifier mask. */
  PduIdType UpperPduIdOfRxPduConfig;  /**< PDU ID defined by upper layer. */
  uint8_t DlcOfRxPduConfig;  /**< Data length code. */
  uint8_t RxIndicationFctListIdxOfRxPduConfig;  /**< the index of the 1:1 relation pointing to CanIf_RxIndicationFctList */
} CanIf_RxPduConfigType;

typedef struct sCanIf_TxBufferPrioByCanIdByteQueueConfigType
{
  uint16_t BaseIdx_TxBufferPrioByCanId;  /**< the index of the 1:1 relation pointing to CanIf_TxBufferPrioByCanIdBase */
  uint16_t EndIdx_TxBufferPrioByCanIdByteQueueMappedTxPdus;  /**< the end index of the 1:n relation pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus */
  uint16_t Length_TxBufferPrioByCanIdByteQueueMappedTxPdus;  /**< the number of relations pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus */
  uint16_t StartIdx_TxBufferPrioByCanIdByteQueueMappedTxPdus;  /**< the start index of the 1:n relation pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus */
} CanIf_TxBufferPrioByCanIdByteQueueConfigType;

/**   \brief  type used in CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus */
typedef struct sCanIf_TxBufferPrioByCanIdByteQueueMappedTxPdusType
{
  uint16_t TxPduConfigIdxOfTxBufferPrioByCanIdByteQueueMappedTxPdus;  /**< the index of the 1:1 relation pointing to CanIf_TxPduConfig */
} CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdusType;

typedef struct sCanIf_TxPduConfigType
{
  uint16_t CanIdOfTxPduConfig;  /**< CAN identifier (16bit / 32bit). */
  uint16_t TxPduMaskofTxPduConfig;
  PduIdType UpperLayerTxPduIdOfTxPduConfig;  /**< Upper layer handle ID (8bit / 16bit). */
  uint8_t CtrlStatesIdxOfTxPduConfig;  /**< the index of the 1:1 relation pointing to CanIf_CtrlStates */
  uint8_t DlcOfTxPduConfig;  /**< Data length code. */
  uint8_t MailBoxConfigIdxOfTxPduConfig;  /**< the index of the 1:1 relation pointing to CanIf_MailBoxConfig */
  uint8_t TxConfirmationFctListIdxOfTxPduConfig;  /**< the index of the 1:1 relation pointing to CanIf_TxConfirmationFctList */
} CanIf_TxPduConfigType;

/**   \brief  type used in CanIf_TxPduQueueIndex */
typedef struct sCanIf_TxPduQueueIndexType
{
  uint16_t TxQueueIdxOfTxPduQueueIndex;  /**< the index of the 0:1 relation pointing to CanIf_TxQueue */
} CanIf_TxPduQueueIndexType;

typedef struct sCanIf_CtrlStatesType
{
  CanIf_ControllerModeType CtrlModeOfCtrlStates;  /**< Controller mode. */
  CanIf_PduModeType PduModeOfCtrlStates;  /**< PDU mode state. */
} CanIf_CtrlStatesType;



/* This type is to be instantiated one per each "CanIfBufferCfg" with "CanIfTxBufferHandlingType == PRIO_BY_CANID" and BYTE_QUEUE is configured */
typedef struct sCanIf_TxBufferPrioByCanIdBaseType
{
  uint8_t  eQueueCounter; /* How many elements are queued within the Tx-buffer. */
} CanIf_TxBufferPrioByCanIdBaseType;



typedef struct sCanIf_TxQueueBaseType
{
  uint8_t         eSduLength; /* uint8: Is sufficient: 8-64 bytes */
} CanIf_TxQueueBaseType;

typedef struct sCanIf_TxQueueBaseWithDataType
{

  uint8_t                   eSdu[CANIF_STATIC_BUFFER_SIZE]; /* const 64 bit     */

  CanIf_TxQueueBaseType eBaseParams;                    /* CanId, SduLength */
} CanIf_TxQueueBaseWithDataType;

typedef struct sCanIf_TxPrioByCanIdByteQueueType
{
  CanIf_TxQueueBaseWithDataType eQueueParams; /* CanId, SduLength, Sdu */
  uint8_t                         eQueued;      /* Validity flag: 0: invalid, 1: valid */
} CanIf_TxPrioByCanIdByteQueueType;

typedef struct sCanIf_RxSearchParamsType
{
  Can_IdType    eCanId;
  PduIdType     eRxPduId;
  PduIdType     eRxPduIdMatch;
  uint8_t eHrh;
  boolean       eContinueSearch;
} CanIf_RxSearchParamsType;

typedef enum
{
     CANIF_NM_STATE_NORMAL = 1,
     CANIF_NM_STATE_SLEEP_REQUESTED,
     CANIF_NM_STATE_SLEEP_PREPARE ,
     CANIF_NM_STATE_SLEEP ,
     CANIF_NM_STATE_WAKEUP_REQUESTED,
     CANIF_NM_STATE_SILENT_REQUESTED,
     CANIF_NM_STATE_SILENT,
     CANIF_NM_NO_STATE
}NM_STATES;

typedef enum
{
     TX_QUEUE_EMPTY = 0,
     TX_QUEUE_NOT_EMPTY
}TX_QUEUE_EMPTY_STATUS;

#endif

/**********************************************************************************************************************
                                                R E V I S I O N   H I S T O R Y                                        
***********************************************************************************************************************
*********************************************************************************************************************************************************************************************************************************************
     REVISION NUMBER      : V1.0.2
     REVISION DATE        : 28/08/2021
     CREATED / REVISED BY : Rajasekar T(rajasekar@niyatainfotech.com)
     DESCRIPTION          : Silent Mode (Listen only mode) Feature code is integrated(Taken from SPT Branch).
-------------------------------------------------------------------------------------
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



