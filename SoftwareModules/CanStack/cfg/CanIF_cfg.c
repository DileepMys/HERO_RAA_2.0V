#ifndef CANIF_CFG_C
#define CANIF_CFG_C
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
 *  File name                       : CanIF_cfg.c                                                                         
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
/***********************************************************************************************************************
 *                          I N C L U D E   F I L E S
 ***********************************************************************************************************************/

#include "CanIF_cfg.h"
#include "CanMgr.h"
#include "CanTp.h"
#include "CanGateway.h"
#include "CanIF.h"
/***********************************************************************************************************************
 *                          C O N F I G U R A T I O N
***********************************************************************************************************************/

/**********************************************************************************************************************
  CanIf_BusOffNotificationFctPtr
**********************************************************************************************************************/
/**
 * 
 */ 
const CanIf_BusOffNotificationFctType CanIf_BusOffNotificationFctPtr = &CanMgr_BusoffIndication ;

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
const CanIf_CanIfCtrlId2MappedTxBuffersConfigType CanIf_CanIfCtrlId2MappedTxBuffersConfig[CANIF_CFG_MAX_CONTROLLER] = {
  /* Index                               MappedTxBuffersConfigEndIdx              MappedTxBuffersConfigStartIdx */        
 { /*0*/                                           0U ,                                                0U  }                                                       
};

#endif
/**********************************************************************************************************************
 CanIf_CtrlModeIndicationFctPtr
**********************************************************************************************************************/
const CanIf_CtrlModeIndicationFctType CanIf_CtrlModeIndicationFctPtr = NULL;
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
const CanIf_MailBoxConfigType CanIf_MailBoxConfig[CANIF_TOTAL_NUM_OF_MAIL_BOX] = {
   /* Index			CtrlStatesIdx			PduIdLast							PduIdFirst									TxBufferCfgIdx																		TxBufferHandlingType												MailBoxType      */         
  {  /*0 */					0U ,						0U  /*TxPduID*/ ,			0U  /*TxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG, 		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_TxFullCANMailbox  },
  {  /*1 */					0U,							0U  /*TxPduID*/ ,			0U  /*TxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_TxFullCANMailbox  },
  {  /*2 */					0U,							0U  /*TxPduID*/ ,			0U  /*TxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_TxFullCANMailbox  },
  {  /*3 */					0U,							0U  /*TxPduID*/ ,			0U  /*TxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_TxFullCANMailbox  },
  {  /*4 */					0U,							0U  /*TxPduID*/ ,			0U  /*TxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_TxFullCANMailbox  },
  {  /*5 */					0U,							0U  /*RxPduID*/ ,			0U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*6 */					0U,							1U  /*RxPduID*/ ,			1U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*7 */					0U,							2U  /*RxPduID*/ ,			2U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*8 */					0U,							3U  /*RxPduID*/ ,			3U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*9 */					0U,							4U  /*RxPduID*/ ,			4U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*10*/					0U,							5U  /*RxPduID*/ ,			5U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*11*/					0U,							6U  /*RxPduID*/ ,			6U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*12*/					0U,							7U  /*RxPduID*/ ,			7U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*13*/					0U,							8U  /*RxPduID*/ ,			8U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*14*/					0U,							9U  /*RxPduID*/ ,			9U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*15*/					0U,							10U  /*RxPduID*/ ,			10U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*16*/					0U,							11U  /*RxPduID*/ ,			11U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*17*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*18*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*19*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*20*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*21*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*22*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*23*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*24*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*25*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*26*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*27*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*28*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*29*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*30*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*31*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*32*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*33*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*34*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*35*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*36*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*37*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*38*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*39*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*40*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*41*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*42*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*43*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*44*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*45*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*46*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*47*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*48*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*49*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*50*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*51*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*52*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*53*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*54*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*55*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*56*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*57*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*58*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*59*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*60*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*61*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*62*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*63*/					0U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
   /* Index			CtrlStatesIdx			PduIdLast							PduIdFirst									TxBufferCfgIdx																		TxBufferHandlingType												MailBoxType      */         
  {  /*64 */					1U ,						0U  /*TxPduID*/ ,			0U  /*TxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG, 		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_TxFullCANMailbox  },
  {  /*65 */					1U,							0U  /*TxPduID*/ ,			0U  /*TxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_TxFullCANMailbox  },
  {  /*66 */					1U,							0U  /*TxPduID*/ ,			0U  /*TxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_TxFullCANMailbox  },
  {  /*67 */					1U,							0U  /*TxPduID*/ ,			0U  /*TxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_TxFullCANMailbox  },
  {  /*68 */					1U,							0U  /*TxPduID*/ ,			0U  /*TxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_TxFullCANMailbox  },
  {  /*69 */					1U,							12U  /*RxPduID*/ ,			12U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*70 */					1U,							13U  /*RxPduID*/ ,			13U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*71 */					1U,							14U  /*RxPduID*/ ,			14U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*72 */					1U,							15U  /*RxPduID*/ ,			15U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*73 */					1U,							16U  /*RxPduID*/ ,			16U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*74*/					1U,							17U  /*RxPduID*/ ,			17U  /*RxPduID */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_RxFullCANMailbox  },
  {  /*75*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*76*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*77*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*78*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*79*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*80*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*81*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*82*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*83*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*84*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*85*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*86*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*87*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*88*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*89*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*90*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*91*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*92*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*93*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*94*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*95*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*96*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*97*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*98*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*99*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*100*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*101*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*102*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*103*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*104*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*105*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*106*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*107*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*108*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*109*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*110*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*111*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*112*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*113*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*114*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*115*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*116*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*117*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*118*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*119*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*120*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*121*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*122*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*123*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*124*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*125*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*126*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  },
  {  /*127*/					1U,							0U  /*Unused*/ ,			0U  /*Unused */ ,			CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG,		CANIF_TXBUFFER_HANDLINGTYPE_NONE, 					CANIF_UnusedCANMailbox  }
};


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
const CanIf_MappedTxBuffersConfigType CanIf_MappedTxBuffersConfig[CANIF_TOTAL_NUM_OF_MAILBOX_CONIGURED_TO_STORE_TX_BUFFERS] = {
      /* Index    MailBoxConfigIdx */     

};
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
const CanIf_RxIndicationFctListType CanIf_RxIndicationFctList[CANIF_TOTAL_RX_INIDICATION_FUNC] = {
  /* Index                RxIndicationFct                                                RxIndicationLayout   */       
{ /*   0 */       { (CanIf_AdvancedRxIndicationFctType)&CanMgr_RxIndication }  ,  CanIf_AdvancedRxIndicationLayout    },
{ /*   1 */       { (CanIf_AdvancedRxIndicationFctType)&Gateway_Request_Rx }   ,  CanIf_NmRxIndicationLayout          },
{ /*   2 */       { (CanIf_AdvancedRxIndicationFctType)&CanTp_RxIndication}    ,  CanIf_TpRxIndicationLayout          },  
{ /*   3 */       { NULL_PTR }                                                 ,  CanIf_AdvancedRxIndicationLayout    },  
{ /*   4 */       { NULL_PTR }                                                 ,  CanIf_AdvancedRxIndicationLayout    }   
};
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
const CanIf_RxPduConfigType CanIf_RxPduConfig[CANIF_TOTAL_RX_PDU] = {

  /*		Index			RxPduCanId					RxPduMask					UpperPduId										              Dlc					 RxIndicationFctListIdx     */           
{/*		0*/					0x130U,					  0x7FFU,					 (PduIdType)ECM_ENGINE_PARAMETER_0X130,					8U,							 0U  } ,
{/*		1*/					0x131U,					  0x7FFU,					 (PduIdType)ECM_SENSOR_PARAMETER_0X131,					8U,							 0U  },
{/*		2*/					0x135U,					  0x7FFU,					 (PduIdType)ECM_ADDITIONAL_INFO_0X135,					8U,							 0U  },
{/*		3*/					0x142U,					  0x7FFU,					 (PduIdType)ABS_TRQ_REQ_0X142,					        8U,							 1U  },
{/*		4*/					0x205U,					  0x7FFU,					 (PduIdType)ABS_STATUS_0X205,					          8U,							 0U  },
{/*		5*/					0x206U,					  0x7FFU,					 (PduIdType)ABS_VEHICLE_SPEED_0X206,					  8U,							 0U  },
{/*		6*/					0x629U,					  0x7FFU,					 (PduIdType)DIAG_ANS_ABS_0X629,					        8U,							 1U  },
{/*		7*/					0x632U,					  0x7FFU,					 (PduIdType)REQ_DIAG_ANS_IC_0X632,					    8U,							 1U  },
{/*		8*/					0x641U,					  0x7FFU,					 (PduIdType)DIAG_ANSW_TCU_0X641,					      8U,							 1U  },
{/*		9*/					0x642U,					  0x7FFU,					 (PduIdType)DIAG_ANS_IC_0X642,					        8U,							 2U  },
{/*		10*/				0x644U,					  0x7FFU,					 (PduIdType)DIAG_ANS_BCM_0X644,					        8U,							 1U  },
{/*		11*/				0x7e8U,					  0x7FFU,					 (PduIdType)DIAG_ANS_ECM_0X7E8,					        8U,							 1U  }
  /*		Index			RxPduCanId					RxPduMask					UpperPduId										Dlc					 RxIndicationFctListIdx     */           
,
{/*		12*/					0x631U,					  0x7FFU,					 (PduIdType)REQ_DIAG_ANSW_TCU_0X631,					8U,							 1U  },
{/*		13*/					0x632U,					  0x7FFU,					 (PduIdType)REQ_DIAG_ANSW_IC_0X632,					  8U,							 2U  },
{/*		14*/					0x6f0U,					  0x7FFU,					 (PduIdType)REQ_DIAG_ANSW_ABS_0X6F0,					8U,							 1U  },
{/*		15*/					0x6f1U,					  0x7FFU,					 (PduIdType)REQ_DIAG_ANSW_BCM_0X6F1,					8U,							 1U  },
{/*		16*/					0x7dfU,					  0x7FFU,					 (PduIdType)FUNCTIONAL_DIAG_REQUEST_0X7DF,		8U,							 1U  },
{/*		17*/					0x7e0U,					  0x7FFU,					 (PduIdType)REQ_DIAG_ANSW_ECM_0X7E0,					8U,							 1U  }};


#ifdef CANIF_BASIC_CAN
/**********************************************************************************************************************
   CanIf_TxBufferPrioByCanIdByteQueueConfig
**********************************************************************************************************************/
/** 
  \var    CanIf_TxBufferPrioByCanIdByteQueueConfig
  \brief  Tx-buffer: PRIO_BY_CANID as BYTE_QUEUE
  \details
  Element                                             Description
  TxBufferPrioByCanIdBaseIdx                          the index of the 1:1 relation pointing to CanIf_TxBufferPrioByCanIdBase
  TxBufferPrioByCanIdByteQueueMappedTxPdusEndIdx      the end index of the 1:n relation pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
  TxBufferPrioByCanIdByteQueueMappedTxPdusLength      the number of relations pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
  TxBufferPrioByCanIdByteQueueMappedTxPdusStartIdx    the start index of the 1:n relation pointing to CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus
*/

const CanIf_TxBufferPrioByCanIdByteQueueConfigType CanIf_TxBufferPrioByCanIdByteQueueConfig[CANIF_TOTAL_NUM_OF_MAILBOX_CONIGURED_TO_STORE_TX_BUFFERS] = {
  /* Index    TxBufferPrioByCanIdBaseIdx       TxBufferPrioByCanIdByteQueueMappedTxPdusEndIdx    TxBufferPrioByCanIdByteQueueMappedTxPdusLength    TxBufferPrioByCanIdByteQueueMappedTxPdusStartIdx  */ 

};

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

const CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdusType CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus[CANIF_TOTAL_TX_BUFFER_MESSAGE] = {
  /* Index    TxPduConfigIdx */

};

#endif
/**********************************************************************************************************************
  CanIf_TxConfirmationFctList
**********************************************************************************************************************/
/** 
  \var    CanIf_TxConfirmationFctList
  \brief  Tx confirmation functions table.
*/ 
const CanIf_TxConfirmationFctType CanIf_TxConfirmationFctList[CANIF_TOTAL_TX_CONFIRMATION_FUNC_LIST] = {
  /* Index     TxConfirmationFctList    Referable Keys */ 
  /*     0 */ NULL_PTR,
  /*     1 */ (CanIf_TxConfirmationFctType)&CanTp_TxConfirmation ,
  /*     2 */ NULL_PTR,
  /*     3 */ (CanIf_TxConfirmationFctType)&CanMgr_TxConfirmation,
  /*     4 */ NULL_PTR
};

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
const CanIf_TxPduConfigType CanIf_TxPduConfig[CANIF_TOTAL_TX_MESSAGES] = {

  /*		Index				CanId								TxPduMask								UpperLayerTxPduId								        CtrlStatesIdx				Dlc		tMailBoxConfigIdx		TxConfirmationFctListIdx    */
{		/*		0*/				0x321U,								0x7FFU,								(PduIdType)IC_INFO_MSG_0X321,								0U,							8U,				12U,										3U										} ,
{		/*		1*/				0x631U,								0x7FFU,								(PduIdType)REQ_DIAGN_ANS_TCU_0X631,					0U,							8U,				13U,										3U										} ,
{		/*		2*/				0x6f0U,								0x7FFU,								(PduIdType)REQ_DIAGN_ANS_ABS_0X6F0,					0U,							8U,				14U,										3U										} ,
{		/*		3*/				0x6f1U,								0x7FFU,								(PduIdType)REQ_DIAGN_ANS_BCM_0X6F1,					0U,							8U,				15U,										3U										} ,
{		/*		4*/				0x7e0U,								0x7FFU,								(PduIdType)REQ_DIAGN_ANS_ECM_0X7E0,					0U,							8U,				16U,										3U										} 
  /*		Index				CanId								TxPduMask								UpperLayerTxPduId								          CtrlStatesIdx				Dlc		tMailBoxConfigIdx		TxConfirmationFctListIdx    */
,
{		/*		5*/				0x629U,								0x7FFU,								(PduIdType)DIAG_ANSW_ABS_0X629,								1U,							8U,				6U,										3U										} ,
{		/*		6*/				0x641U,								0x7FFU,								(PduIdType)DIA_ANSW_TCU_0X641,								1U,							8U,				7U,										3U										} ,
{		/*		7*/				0x642U,								0x7FFU,								(PduIdType)DIAG_ANSW_IC_0X642,								1U,							8U,				8U,										1U										} ,
{		/*		8*/				0x644U,								0x7FFU,								(PduIdType)DIAG_ANSW_BCM_0X644,								1U,							8U,				9U,										3U										} ,
{		/*		9*/				0x7e8U,								0x7FFU,								(PduIdType)DIAG_ANSW_ECM_0X7E8,								1U,							8U,				10U,										3U										} 
};
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
const CanIf_TxPduQueueIndexType CanIf_TxPduQueueIndex[CANIF_TOTAL_TX_MESSAGES] = {
  /* Index    TxQueueIdx                              */      

{/*     0 */      CANIF_NO_TXQUEUEIDXOFTXPDUQUEUEINDEX     },
{/*     1 */      CANIF_NO_TXQUEUEIDXOFTXPDUQUEUEINDEX     } ,
{/*     2 */      CANIF_NO_TXQUEUEIDXOFTXPDUQUEUEINDEX     } ,
{/*     3 */      CANIF_NO_TXQUEUEIDXOFTXPDUQUEUEINDEX     } ,
{/*     4 */      CANIF_NO_TXQUEUEIDXOFTXPDUQUEUEINDEX     } 
,
{/*     64 */      CANIF_NO_TXQUEUEIDXOFTXPDUQUEUEINDEX     } ,
{/*     65 */      CANIF_NO_TXQUEUEIDXOFTXPDUQUEUEINDEX     } ,
{/*     66 */      CANIF_NO_TXQUEUEIDXOFTXPDUQUEUEINDEX     } ,
{/*     67 */      CANIF_NO_TXQUEUEIDXOFTXPDUQUEUEINDEX     } ,
{/*     68 */      CANIF_NO_TXQUEUEIDXOFTXPDUQUEUEINDEX     } };

#endif

const CanMailBoxTableDetailsTypeSt CanRXMailBoxTableDetailsSt[CAN_TOTAL_NUMBER_OF_CHANNELS] =
{
  {0, 12, 0},
  {12, 6, 12}
};

const CanMailBoxTableDetailsTypeSt CanTXMailBoxTableDetailsSt[CAN_TOTAL_NUMBER_OF_CHANNELS] =
{
  {12, 5, 0},
  {6, 5, 5}
};


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
CanIf_CtrlStatesUType CanIf_CtrlStates;  

#ifdef CANIF_BASIC_CAN
/**********************************************************************************************************************
  CanIf_TxBufferPrioByCanIdBase
**********************************************************************************************************************/
/** 
  \var    CanIf_TxBufferPrioByCanIdBase
  \brief  Variable declaration - Tx-buffer: PRIO_BY_CANID as byte/bit-queue. Stores at least the QueueCounter.
*/

CanIf_TxBufferPrioByCanIdBaseUType CanIf_TxBufferPrioByCanIdBase;  

/**********************************************************************************************************************
  CanIf_TxQueue
**********************************************************************************************************************/
/** 
  \var    CanIf_TxQueue
  \brief  Variable declaration - Tx byte queue.
*/
CanIf_TxQueueUType CanIf_TxQueue;  

#endif

#endif

/**********************************************************************************************************************
                                          R E V I S I O N   H I S T O R Y                                        
***********************************************************************************************************************
***********************************************************************************************************************




***********************************************************************************************************************/

