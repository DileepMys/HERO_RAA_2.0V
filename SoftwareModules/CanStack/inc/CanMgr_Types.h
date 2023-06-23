
#ifndef CANMGR_TYPES_H_
#define CANMGR_TYPES_H_
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
 *  File name                       : CanMgr_Types.h
 *  Version                         : V1.1.0
 *  Micros supported                : Micro Agnostic (Independent)
 *  Compilers supported             : XXXXX
 *  Platforms supported             : XXXXX
 *  Description                     : This file contains type declaration required for CanMgr
 *                                                                                                                    
 *                                                                                                                    
 *  @bug                                                                                                              
 *--------------------------------------------------------------------------------------------------------------------*/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *                                          I N C L U D E   F I L E S                                    
 ***********************************************************************************************************************/

#include "stdint.h"
#include "stdio.h"

/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S                                          
 ***********************************************************************************************************************/
#define CANMGR_TRUE     (uint8_t)0x01
#define CANMGR_FALSE    (uint8_t)0x00
#define CANMGR_GATEWAY  (uint8_t)0x55

/*
* @brief: This Macro is used to indicates that the message
  @brief: has been received successfully
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define MSG_RECEIVED (uint8_t)0x01

/*
* @brief: This Macro is used to indicates that the message
  @brief: is missing and reception timeout time is elapsed
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define MSG_MISSING (uint8_t)0x02

/*
* @brief: This Macro is used to indicates that the message
  @brief: has been never received (not even once).
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define MSG_NEVER_RECEIVED (uint8_t)0x03

/*
* @brief: This Macro is used to indicates that the message has been received with checksum error & has been confirmed
*         based on the de-bounce.
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define RX_CRC_ERROR_CONFIRMED    (uint8_t)0x04

/*
* @brief: This Macro is used to indicates that the message has been received with alive counter error & has been confirmed
*         based on the de-bounce.
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define RX_ALIVE_CNTR_ERROR_CONFIRMED    (uint8_t)0x05
/*********************************************************************************************************************** 
 *                                          T Y P E   D E F I N I T I O N S                                            *
 ***********************************************************************************************************************/
typedef enum
{
    CAN_MGR_INIT =(0x00u),
    CAN_MGR_UNINIT
}CanMgr_StatusType;

typedef unsigned int CanMgr_SignalIdType;

typedef enum
{
   CYCLIC          = (uint8_t)0x00,
   ONCHANGE        = (uint8_t)0x01,
   ONWRITE         = (uint8_t)0x02,
   IFACTIVE        = (uint8_t)0x03,
   ONCHANGE_REP    = (uint8_t)0x04,
   ONWRITE_REP     = (uint8_t)0x05,
   IFACTIVE_REP    = (uint8_t)0x06,
   CYCLIC_ONCHANGE = (uint8_t)0x07,
   CYCLIC_ONWRITE  = (uint8_t)0x08,
   CYCLIC_IFACTIVE = (uint8_t)0x09,
   EVENT_SIGNAL    = (uint8_t)0x0A,
   SIGNAL_TYPE_MAX
}CanMgr_Signal_Type_En;

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                          
***********************************************************************************************************************/
#ifdef __cplusplus
}
#endif
/**********************************************************************************************************************
 *                                                R E V I S I O N   H I S T O R Y             
***********************************************************************************************************************
     REVISION NUMBER      : V1.7.6
     REVISION DATE        : 11/08/2020
     CREATED / REVISED BY : Sharmili N(sharmili@niyatainfotech.com)
     DESCRIPTION          : Additional Tx methods implemented
-------------------------------------------------------------------------------------
**********************************************************************************************************************
     REVISION NUMBER      : V1.1.0                                                                                   
     REVISION DATE        : 30/05/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : Misra Fix                                                                            
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.0.0                                                                                   
     REVISION DATE        : 30/01/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : Initial Version                                                                            
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
#endif /* CANMGR_TYPES_H_ */
