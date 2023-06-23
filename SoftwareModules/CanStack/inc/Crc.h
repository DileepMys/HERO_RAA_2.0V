#ifndef CRC_H
#define CRC_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Sharmili N (sharmili@niyatainfotech.com)                                                                        
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : Crc.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Agnostic (Independent)
*  Compilers supported             : XXXXX
*  Platforms supported             : XXXXX
*  Description                     : This header file contains the declarations of CRC
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/
/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include <stdint.h>
#include <stddef.h>

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/
/*
 * @brief    This service initializes CRC layer
 * @param    NULL
 * @return   NULL
 * @note     To be made use if Hash table calculation is used
 */
void Crc_Init(void);

/*
 * @brief    This service makes a CRC8 calculation on Crc_Length data bytes, with SAE J1850 parameters
 * @param    CAN ID - message ID of data to be calculated 
 * @param    Pointer to start address of data block to be calculated.
 * @param    Length of data block to be calculated in bytes.
 * @param    Start value when the algorithm starts.
 * @param    TRUE: First call in a sequence or individual CRC calculation; start from initial value, ignore Crc_StartValue8. 
             FALSE: Subsequent call in a call sequence; Crc_StartValue8 is interpreted to be the return value of previous function call.
 * @return   uint8_t - 8 bit result of CRC calculation.
 */
uint8_t Crc_CalculateCRC8(uint16_t CAN_ID , const uint8_t* Crc_DataPtr, uint32_t Crc_Length);

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
***********************************************************************************************************************
    REVISION NUMBER      : V1.0.1
    REVISION DATE        : 5-Mar-2021
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Crc_Init function declared. New API.
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.0                                                
    REVISION DATE        : 24-Feb-2021                              
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)  
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* CRC_H */
