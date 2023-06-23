/* @file UDSAPP_SUPPORT_H */
#ifndef UDSAPP_SUPPORT_H
#define UDSAPP_SUPPORT_H

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
*  File name                       : UdsApp_Support.h
*  Version                         : V1.0.1
*  Micros supported                : Micro Agnostic (Independent)
*  Compilers supported             : XXXXX
*  Platforms supported             : XXXXX
*  Description                     : This file contains the declarations of Extended support APIs required for UdsApp
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
#include "hal_stdtypes.h"
#include "CanIF.h"
/*********************************************************************************************************************
*                                          M A C R O   D E F I N I T I O N S                                          
*********************************************************************************************************************/
/**
 * @brief    This structure is used to maintain the corresponding information required to handle DID services to read
 * @param    DID         - Requested Data ID
 * @param    Block_Id    - Block ID in  NvM 
 **/
typedef struct
{
    UDS_UINT16 DID;
    UDS_UINT16 Block_Id; 
    //UDS_UINT16 (*funptr)void;
}UdsApp_Support_Nvm_st;

/**
 * @brief    This structure is used to maintain the corresponding information required to handle DID services 
 *           to read/write data from ROM
 * @param    DID             - Requested Data ID
 * @param    StartAddress    - Start address of the sector 
 **/
typedef struct
{
    UDS_UINT16 DID;
    UDS_UINT8* StartAddress; 
}UdsApp_Support_ROM_st;


/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This function is used to handle the Read DID service's reading operation from NVM/RAM/ROM
* @param    Data_Identifier - Identifier to analyze which data to be read from where
* @param    DataBuffer      - Data pointer to store the data read
* @param    DataSize        - Size of the Data to be read
* @return   UDS_UINT8 - E_OK: Write completed successfully
                        E_NOT_OK: Write not eexecuted successfully
*/
UDS_UINT8 UdsApp_Support_Read_Data(UDS_UINT16 Data_Identifier, UDS_UINT8 *DataBuffer, UDS_UINT16 DataSize);

/*
* @brief    This function is used to handle the Write DID service's write operation from NVM/RAM/ROM
* @param    Data_Identifier - Identifier to analyze which data to be read from where
* @param    DataBuffer      - Data pointer to store the data read
* @param    DataSize        - Size of the Data to be read
* @return   UDS_UINT8 - E_OK: Write completed successfully
                        E_NOT_OK: Write not eexecuted successfully
*/
UDS_UINT8 UdsApp_Support_Write_Data(UDS_UINT16 Data_Identifier, const UDS_UINT8 *DataBuffer, UDS_UINT16 DataSize);

UDS_UINT8 UDSAPP_WRITE_BY_ADDRESS( UDS_UINT32 Data_Address,const UDS_UINT8 *pdiagdata, UDS_UINT32 DataSize);
UDS_UINT8 UDSAPP_READ_BY_ADDRESS( UDS_UINT32 Data_Address, UDS_UINT8 *pdiagdata, UDS_UINT16 DataSize);

/*Sample Code - Skeleton for Future implementation Purpose*/

/**
 * @brief    This sample function is used to show the implementation skeleton for start routine handler 
 * @param    Routine Identifier RID
 * @return   Routine execution status (UDS_TRUE - successfull, UDS_FALSE - unsuccessful)
 **/
UDS_UINT8 Sample_Routine_Start(UDS_UINT16 RID);

/**
 * @brief    This sample function is used to show the implementation skeleton for stop routine handler 
 * @param    Routine Identifier RID
 * @return   Routine execution status (UDS_TRUE - successfull, UDS_FALSE - unsuccessful)
 **/
UDS_UINT8 Sample_Routine_Stop(UDS_UINT16 RID);

/**
 * @brief    This sample function is used to show the implementation skeleton for get results routine handler
 * @param    RID - Routine Identifier
 * @param    RespDataBuff - Pointer to update the response buffer with routine results
 * @param    DataLen - Pointer to update the length  of the buffer after updating with Routine results
 * @return   Routine execution status (UDS_TRUE - successfull, UDS_FALSE - unsuccessful)
 **/
UDS_UINT8 Sample_Routine_Result(UDS_UINT16 RID, UDS_UINT8 *RespDataBuff, UDS_UINT8 *DataLen);

boolean RoutineControl_Pre_Condition_check(void);
UDS_UINT8 UDS_VOLTAGE_STATUS(void);

uint8_t UDS_EXTERNAL_EEPROM_MEMORY_READ_BLKID(void);
uint8_t UDS_NVM_CHECKSUM(void);
uint8_t UDS_HYPERFLASH_MEMORY_CHECKSUM(void);
uint8_t UDS_ANALOG_INPUT_CHECK(void);
uint8_t UDS_BLE_STATUS_READ(void);
uint8_t UDS_PROGRAM_ALL_NVM(void);
uint8_t UDS_PROGRAM_PRECONDITION_CHECK_RESULT(void);
uint8_t UDS_PROGRAM_PRECONDITION_CHECK(void);

uint8_t UDS_NVM_CHECKSUM_RESULT(void);
//uint8_t UDS_Comm_Cntrl_Action(uint8_t Action, uint8_t CommType);

#define UDS_COMMUNICATION_CONTROL_ACTION(ACTION, COMM_TYPE)                             DiagSetCommControl(ACTION, COMM_TYPE)



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
    REVISION DATE        : 30-July-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Write DID service extension provided for ROM & NVM
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.0                                                           
    REVISION DATE        : 16-Apr-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Initial Version                              
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! UDSAPP_SUPPORT_H */
