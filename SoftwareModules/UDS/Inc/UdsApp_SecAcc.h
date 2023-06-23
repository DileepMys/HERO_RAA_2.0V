/* @file UDSAPP_SECACC_H */
#ifndef UDSAPP_SECACC_H
#define UDSAPP_SECACC_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2011, 2016 Niyata Infotech Ptv. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Sharmili N (sharmili@niyatainfotech.com)                                                                      
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : UdsApp_SecAcc.h
*  Version                         : V1.0.1
*  Micros supported                : Micro Agnostic (Independent)
*  Compilers supported             : XXXXX
*  Platforms supported             : XXXXX
*  Description                     : This file consists of declaration of Security Access Key Generation algorithm 
                                     process
*  @bug                          
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include "Uds_Types.h"
/*********************************************************************************************************************
*                                          M A C R O   D E F I N I T I O N S                                          
*********************************************************************************************************************/
/*
* @brief          : The below macros defines the 3 byte constant Key value of Security Access
* @unit           : N/A
* @resolutution   : N/A
* @range          : N/A
* @validity check : N/A
* @note           : MSB first
* @required       : YES
*/
// #define UDS_SERVER_KEY_BYTE1 Calculated_Key[BUFF_INDEX_ZERO]
// #define UDS_SERVER_KEY_BYTE2 Calculated_Key[BUFF_INDEX_ONE]
// #define UDS_SERVER_KEY_BYTE3 Calculated_Key[BUFF_INDEX_TWO]

#if(SECURITY_ACCESS_DATA_RECORD_VERIFICATION == STD_ON)
/*
* @brief          : The below macros defines the securityAccessDataRecord - identification of client for verification
* @unit           : N/A
* @resolutution   : N/A
* @range          : N/A
* @validity check : N/A
* @note           : Could be of any number of Bytes since it is completely Vehicle-Manufacturer Specific
* @required       : YES
*/
#define UDS_SECURITY_ACC_DATA_RECORD  0x4943u
#endif 
/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This function is used to generate the Secure Seed with the existing known values of Key, C1 & C2
* @param    NULL
* @return   UINT32 - GeneratedKey
*/
//void UdsApp_SecurityAccess_SeedGeneration(UDS_UINT8 *DataBuffer);

void UdsApp_SecurityAccess_SeedGeneration(uint8_t *buffer);

uint32 rtiGetCounter(uint32 counter);
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
***********************************************************************************************************************
    REVISION NUMBER      : V1.0.1
    REVISION DATE        : 30-Mar-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Peer Review Comments Fixed                                 
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.0                                                           
    REVISION DATE        : 27-Mar-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Initial Version                              
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! UDSAPP_SECACC_H */
