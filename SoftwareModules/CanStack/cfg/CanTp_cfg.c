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
 *  File name                       : CanTp_cfg.c                                                                        
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
#include "CanTp_cfg.h"
//#include "Sample_APP.h"
#include "UDS.h"
/***********************************************************************************************************************
 *                     C O N F I G U R A T I O N
 ***********************************************************************************************************************/

/**********************************************************************************************************************
  ApplCanTpRxIndication
**********************************************************************************************************************/
/** 
 *  \var    ApplCanTpRxIndication
 *  \brief  Rx Indication Function - Application function pointed to this configuration will be updated with argument of type
 *          Std_RetrunType i.e E_OK or E_NOT_OK. and length of the Message Received.
 *          E_OK - on Reception is successful.
 *          E_NOT_OK - on Reception is not successful. 
 *          DataLength  - Received Data Length will be zero if E_NOT_OK 
 *                       or Received Data Length will be number of bytes received if E_OK 
 * 
 */

ApplCanTpRxIndication_functype Appl_Func_CanTpRxIndication  = UDS_FunctionalReq_Indication;

ApplCanTpRxIndication_functype Appl_Phys_CanTpRxIndication  = UDS_PhysicalReq_Indication;
/**********************************************************************************************************************
  ApplCanTpTxConfirmation
**********************************************************************************************************************/
/** 
 *  \var    ApplCanTpTxConfirmation
 *  \brief  Tx Confirmation Function - Application function pointed to this configuration will be updated with argument of type
 *          Std_RetrunType i.e E_OK or E_NOT_OK.
 *          E_OK - on Transmition is successful.
 *          E_NOT_OK - on Transmition is not successful.         
 */
ApplCanTpTxConfirmation_functype ApplCanTpTxConfirmation  = NULL;

#if 0
ApplCanTpTxErrorIndication_functype ApplCanTpTxErrorIndication;

ApplCanTpRxErrorIndication_functype ApplCanTpRxErrorIndication;
#endif

/**********************************************************************************************************************
  ApplCanTpRxGetBuffer
**********************************************************************************************************************/
/** 
 *  \var    ApplCanTpRxGetBuffer
 *  \brief  Application function pointed to this configuration shall return the address of RX buffer 
 *          that need to be updated up on TP message received.
 */

ApplCanTpRxGetBuffer_functype Appl_Phys_CanTpRxGetBuffer  = UDS_PhysicalGetBuffer;

ApplCanTpRxGetBuffer_functype Appl_Func_CanTpRxGetBuffer  = UDS_FunctionalGetBuffer;

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
