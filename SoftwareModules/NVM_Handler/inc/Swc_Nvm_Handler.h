/* @file FILE NAME */
#ifndef NVM_HANDLER_H
#define NVM_HANDLER_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Balasubramaniyan (balasubramaniyan.s@niyatainfotech.com)
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
* 
*
*  File name                       : Nvm Handler.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : COSMIC
*  Platforms supported             : Platform Independent
*  Description                     : This file contains Macros, Typdef and Function Declarations for gear_position files
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/

#include "Swc_Nvm_Handler_Cfg.h"

/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/




/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/
/* perform integrity check when it is necessary */
/*#if ( FILE_NAME_H_VERSION != 0x0001 )
    #error "Incorrect version of header file used in filename.h!!!"
#endif*/
/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
/*
* @brief This macro is used to define 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/



/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/



/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/
/*
* @brief    This API is used to Initialize the NVM init variable with default values
* @param    nil
* @return   nil
* @invocation  NA
*/
void NVM_Handler_Init(void);


/*
* @brief    This API is used to reset the NVM init variable with default values
* @param    nil
* @return   nil  
* @invocation NA
*/
void NVM_Handler_Deint(void);

/*
* @brief    This API is used to activate the NVM init variable with default values
* @param    nil
* @return   nil  
* @invocation NA
*/
void NVM_Handler_Activate(void);

/*
* @brief    This API is used to deactivate the NVM init variable with default values
* @param    nil
* @return   nil  
* @invocation NA
*/
void NVM_Handler_DeActivate(void);

/*
* @brief    This API is used to write the data into the NVM
* @param    nil
* @return   nil 
* @invocation NA
*/
uint8_t NVMData_Writesync(uint32_t id,void *data,uint8_t length);

/*
* @brief    This API is used to read the appropriate data in the NVM
* @param    nil
* @return   nil 
* @invocation NA
*/
uint8_t NVMData_Readsync(uint32_t id,void *data,uint8_t length);

/*
* @brief    This API is used to get the non volatile memory status whether its ready do its process 
* @param    nil
* @return   nil 
* @invocation NA
*/
bool Swc_Get_NVM_Status(void);

uint32_t NVM_Write_Frame(uint32_t DstAddress, uint8_t* SrcAddress, uint16_t size);
uint8_t NVM_Byte_Write(uint32_t Address, uint8_t Data);
uint32_t NVM_Read_Frame(uint32_t DstAddress, uint8_t* SrcAddress, uint16_t size);
uint8_t NVM_Byte_Read_Allocation(uint8_t BlockID,uint8_t *Databuff);
uint8_t NVM_Byte_Write_Allocation(uint8_t BlockID,uint8_t *Databuff);
uint8_t NVM_Byte_Read(uint32_t Address, uint8_t* Data);



/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                                                
    REVISION DATE        : 2/19/2021        
    CREATED / REVISED BY : Balasubramaniyan (balasubramaniyan.s@niyatainfotech.com)
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! NVM_HANDLER_H */
