#ifndef CANTP_TYPES_H
#define CANTP_TYPES_H
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
 *  File name                       : CanTp_Types.h                                                                        
 *  Version                         : V1.0.0                                                                           
 *  Micros supported                : Micro Agnostic (Independant)                                                            
 *  Compilers supported             : XXXX                                                                           
 *  Platforms supported             : XXXX                                                                            
 *  Description                     : This file contains precompile configuration settings for CanIF                                 
 *                                                                                                                     
 *                                                                                                                     
 *  @bug                                                                                                               
 *---------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************
 *                                  I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "sys_common.h"
#include "CanStack_CommonTypes.h"


/***********************************************************************************************************************
 *                             P U B L I C   T Y P E   D E F I N I T I O N S
 ***********************************************************************************************************************/
typedef struct
{
    uint8_t   SeqNum          ;
    uint8_t   Tx_inprogress   ;
    uint8_t   Rx_inprogress   ;
    uint8_t   SendMsg         ;
    uint8_t   Wait4FC         ;
    uint8_t   MsgRcvd         ;
    uint8_t   Rx_Status       ;
    uint8_t   Tx_Status       ;
    uint8_t   FC_Status       ;

}CanTp_StatusType;

typedef struct {
   uint16_t  DataLength;
   uint8_t   *Data;
   }CanTp_SDU;

typedef struct {
   PduIdType PduID;
   uint8_t   Size;
   uint8_t   Data[8];
   }CanTp_PDU;

#if 0
typedef enum
{
    CANTP_RECEIVE_UPPER_ID = 253

}CanTp_RxPduId;

typedef enum
{
    CANTP_TRANSMIT_UPPER_ID = 254

}CanTp_TxPduId;
#endif

typedef void (*ApplCanTpRxIndication_functype) (uint8_t state, uint16_t dataLen);

typedef void (*ApplCanTpTxConfirmation_functype) (uint8_t state);
#if 0
typedef void (*ApplCanTpTxErrorIndication_functype) (uint8_t State);   

typedef void (*ApplCanTpRxErrorIndication_functype) (uint8_t State);
#endif
typedef uint8_t* (*ApplCanTpRxGetBuffer_functype) (uint16_t DataLength);

/**********************************************************************************************************************
                                                R E V I S I O N   H I S T O R Y                                        
***********************************************************************************************************************
**********************************************************************************************************************
     REVISION NUMBER      : V1.0.0
     REVISION DATE        : 26/03/2020                                                                               
     CREATED / REVISED BY : Akshay Bavalatti (akshayb@niyatainfotech.com)                                        
     DESCRIPTION          : Initial version                                                                          
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
#endif


