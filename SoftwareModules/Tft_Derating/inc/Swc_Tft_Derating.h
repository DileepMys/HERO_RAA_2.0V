/* @file FILE NAME */
#ifndef TFT_DERATING_H
#define TFT_DERATING_H

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
*  File name                       : SWC_Tft_Derating.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : J Link
*  Platforms supported             : Platform Independent
*  Description                     : This file contains Macros, Typdef and Function Declarations
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/

#include "Swc_Tft_Derating_Cfg.h"
#include "stdbool.h"
#include "hal_stdtypes.h"

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

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used To initialize the  function to be called in the main function 
* @param    Nil
* @return   Nil
* @invocation 
*/
void Tft_Derating_Init(void);


/*
* @brief    This API is used To reset the  function to be called in the main function 
* @param    Nil
* @return   Nil
* @invocation 
*/
void Tft_Derating_DeInit(void);


/*
* @brief    This API is used To activate the  peripherals
* @param    Nil
* @return   Nil
* @invocation 
*/
void Tft_Derating_Active(void);


/*
* @brief    This API is used To reset the peripherals of the system
* @param    Nil
* @return   Nil
* @invocation 
*/
void Tft_Derating_DeActive(void);

/*
* @brief    This API is used To execute the all system function 
* @param    Nil
* @return   Nil
* @invocation 
*/
void Tft_Derating_MainFunction(void);

/*
* @brief    This API is used To check the all pre condition elements such as ign on/off LVSD/HVSD
* @param    Nil
* @return   bool
* @invocation 
*/
bool Tft_Derating_Pre_Condition(void);

/*
* @brief    This API is used To get duty cycle value for TFT derating
* @param    fl_TFT_Temperature_value_u16
* @return   uint16_t
* @invocation 
*/
uint16_t Tft_Derating_Get_Duty_Cycle(uint16_t fl_TFT_Temperature_value_u16);

/*
* @brief    This API is used To map the ADS and temperature
* @param    fl_TFT_Temperature_value_u16,data_from_table_u16,fl_table_size_u16
* @return   uint16_t
* @invocation 
*/
uint16_t TFT_Derating_ADC_VS_Temperature_Mapping(uint16_t *ADC_Vs_Temperature_data_u16, uint16_t data_from_table_u16, uint16_t fl_table_size_u16 );

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                                               
    REVISION DATE        : MONTH/DATE/YEAR                              
    CREATED / REVISED BY : Balasubramaniyan (balasubramaniyan.s@niyatainfotech.com)
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! TFT_DERATING_H */
