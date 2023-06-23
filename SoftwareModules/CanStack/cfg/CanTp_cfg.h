#ifndef CANTP_CFG_H
#define CANTP_CFG_H
/*********************************************************************************************************************** 
 *    DISCLAIMER                                                                                                        
 *   Copyright (C) 2011, 2016 Niyata Infotech Ptv. Ltd. All rights reserved.                                              
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * @author              Author : Mahendran L (mahendranl@niyatainfotech.com)                                                                       
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N                                           
 *---------------------------------------------------------------------------------------------------------------------
 *  @brief                                                                                                             
 *                                                                                                                     
 *  File name                       : CanTp_cfg.h                                                                        
 *  Version                         : Currentversion                                                                           
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
#include "CanTp_Types.h"
#include "CanMgr_cfg.h"

/***********************************************************************************************************************
 *                                          M A C R O   C O N F I G U R A T I O N
 ***********************************************************************************************************************/

/**********************************************************************************************************************
  CANTP_PERIODICITY
**********************************************************************************************************************/
/** 
 *  \brief  This parameter specifies the TP periodic task schedule time
 *          in msec.This parameter defines the STmin for all TP channel
 *  \Template:        CANTP_PERIODICITY          (5u)
 */

#define CANTP_PERIODICITY   (2u)

#define CANTP_TX_MESSAGE_CONFIGURED  STD_ON
#define CANTP_RX_MESSAGE_CONFIGURED  STD_ON


#if ((CANTP_TX_MESSAGE_CONFIGURED == STD_ON) && (CANTP_RX_MESSAGE_CONFIGURED == STD_ON))
/**********************************************************************************************************************
  CANTP_RECEIVE_PDU_ID
**********************************************************************************************************************/
/** 
 *  \brief:  CanIf Rx PduID mapped to the mailbox
 *  \Templates:        CANTP_RECEIVE_PDU_ID        CANTP_RECEIVE_UPPER_ID
 */
#define CANTP_RECEIVE_PHYS_PDU_ID_ABS   REQ_DIAG_ANSW_ABS_0X6F0

#define CANTP_RECEIVE_PHYS_PDU_ID_BCM   REQ_DIAG_ANSW_BCM_0X6F1

#define CANTP_RECEIVE_PHYS_PDU_ID_ECM   REQ_DIAG_ANSW_ECM_0X7E0

#define CANTP_RECEIVE_PHYS_PDU_ID_IC   REQ_DIAG_ANSW_IC_0X632

#define CANTP_RECEIVE_PHYS_PDU_ID_TCU   REQ_DIAG_ANSW_TCU_0X631

/***
*   if functional addressing is not used then configure as
*    CANTP_RECEIVE_FUNC_PDU_ID      0xFFFF
***/
#define CANTP_RECEIVE_FUNC_PDU_ID   FUNCTIONAL_DIAG_REQUEST_0X7DF

/**********************************************************************************************************************
  CANTP_TRANSMIT_PDU_ID
**********************************************************************************************************************/
/** 
 *  \brief:  CanIf Tx PduID mapped to the mailbox
 *  \Templates:        CANTP_TRANSMIT_PDU_ID        CANTP_TRANSMIT_UPPER_ID)
 */
#define CANTP_TRANSMIT_PDU_ID_1   DIAG_ANSW_TCU_0X641

#define CANTP_TRANSMIT_PDU_ID_2   DIAG_ANS_ABS_0X629

#define CANTP_TRANSMIT_PDU_ID_3   DIAG_ANS_BCM_0X644

#define CANTP_TRANSMIT_PDU_ID_4   7//(0x642U)

#define CANTP_TRANSMIT_PDU_ID_5   DIAG_ANS_IC_0X642

#else
     
     #define CANTP_RECEIVE_PHYS_PDU_ID			          0xFFFFU

     #define CANTP_RECEIVE_FUNC_PDU_ID                0xFFFFU
     
     #define CANTP_TRANSMIT_PDU_ID    		            0xFFFFU
     
#endif


/**********************************************************************************************************************
  CANTP_TX_WAIT_CONF_TIME_INMSEC
**********************************************************************************************************************/
/** 
 *  \brief:  Time out value for waiting for Confirmation to Txed message
 *  \Templates:        CANTP_TX_WAIT_CONF_TIME_INMSEC        (70u)
 */
#define CANTP_TX_WAIT_CONF_TIME_INMSEC   (1000u)


/**********************************************************************************************************************
  CANTP_TX_CF_TIME_INMSEC
**********************************************************************************************************************/
/** 
 *  \brief:  Time out value for transmit Consecutive Frame time Count
 *           value for all the TP channels
 *           This list should hold the Consecutive frame wait count
 *           parameter of all the channels in the order of Connections
 *  \Templates:        CANTP_TX_CF_TIME_INMSEC        (70u)
 */   
#define CANTP_TX_CF_TIME_INMSEC   (1000u)

/**********************************************************************************************************************
  CANTP_WAIT_FC_TIME_INMSEC
**********************************************************************************************************************/
/** 
 *  \brief  Time out value for waiting for FLow Control Frame 
 *  \Templates:        CANTP_WAIT_FC_TIME_INMSEC        (150u)
 */
#define CANTP_WAIT_FC_TIME_INMSEC   (1000u)

/**********************************************************************************************************************
  CANTP_WAIT_CF_TIME_INMSEC
**********************************************************************************************************************/
/** 
 *  \brief  Time out value for waiting for Consecutive Frame 
 *  \Templates:        CANTP_WAIT_CF_TIME_INMSEC        (150u)
 */
#define CANTP_WAIT_CF_TIME_INMSEC   (1000u)


/**********************************************************************************************************************
  CANTP_MAX_WAIT_CNT
**********************************************************************************************************************/
/** 
 *  \brief  This paramter specifies the Number of successive 
 *          FC with Wait Status accepted during data transfer.
 *  \Templates:        CANTP_MAX_WAIT_CNT        (2u)
 */
#define CANTP_MAX_WAIT_CNT   (2u)

/**********************************************************************************************************************
  CANTP_STMIN
**********************************************************************************************************************/
/** 
 *  \brief  The STmin of TP frame during Reception.
 *          Block size zero mentions no BS used by TP
 *  \Templates:        CANTP_STMIN        (0x00u)
 */
#define CANTP_STMIN   (2u)

/**********************************************************************************************************************
  CANTP_UNUSED_BYTE_VALUE
**********************************************************************************************************************/
/** 
 *  \brief  This parameter specifies the unused data byte values
 *  \Templates:        CANTP_UNUSED_BYTE_VALUE        (0x0u)
 */   
#define CANTP_UNUSED_BYTE_VALUE   (0u)


extern ApplCanTpRxIndication_functype Appl_Func_CanTpRxIndication;

extern ApplCanTpRxIndication_functype Appl_Phys_CanTpRxIndication;

extern ApplCanTpTxConfirmation_functype ApplCanTpTxConfirmation;
#if 0
extern ApplCanTpTxErrorIndication_functype ApplCanTpTxErrorIndication;

extern ApplCanTpRxErrorIndication_functype ApplCanTpRxErrorIndication;
#endif
extern ApplCanTpRxGetBuffer_functype Appl_Func_CanTpRxGetBuffer;

extern ApplCanTpRxGetBuffer_functype Appl_Phys_CanTpRxGetBuffer;


/***********************************************************************************************************************
 *                     P U B L I C     F U N C T I O N    D E C L A R A T I O N
 ***********************************************************************************************************************/


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
     REVISION NUMBER      : V1.0.0
     REVISION DATE        : 26/03/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : Initial version                                                                          
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
#endif




