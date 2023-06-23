/* @file DIO_HANLDER_H */
#ifndef DIO_HANLDER_H
#define DIO_HANLDER_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : palani kumar (palanikumar@niyatainfotech.com) 
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
* 
*
*  File name                       : Dio handler.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : J link
*  Platforms supported             : Platform Independent
*  Description                     : This file contains Macros, Typdef and Function Declarations for gear_position files
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include "Dio_Handler_cfg.h"
#include "Cmp_Init.h"
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

/*
 * @brief    This typedef is used to define the number of DIO pin handler states
 * @param    NA
 * @return   NA
 */
typedef enum
{
    DIO_CHECK_PIN_STATUS = 0,
    DIO_PIN_HIGH_DETECTION,
    DIO_PIN_LOW_DETECTION,
    DIO_PROCESS_DEBOUNCE_STATE,
    DIO_PIN_HIGH_CONFIRMATION,
    DIO_PIN_LOW_CONFIRMATION

}DIO_PIN_HANDLER_STATE_EN;

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to initialize the variables with default values
* @param    Nil
* @return   nil
* @invocation  nil
*/
void Dio_Handler_Init(void);

/*
* @brief    This API is used to activate  the initial peripheral variables
* @param    Nil
* @return   Nil
* @invocation nil
*/
void Dio_Handler_Activate(void);

/*
* @brief    This API is used to reset the peripheral variables
* @param    Nil
* @return   Nil
* @invocation nil
*/
void Dio_Handler_Deactivate(void);

/*
* @brief    This API is used to excute all sub function 
* @param    Nil
* @return   nil
* @invocation  nil
*/
void Dio_Handler_Mainfunction(void);

/*
* @brief    This API is used to read the pin status of the Dio handler
* @param    Nil
* @return   Nil
* @invocation  nil
*/
uint8_t Dio_Handler_Read_Pin_Status(void);


/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                                                
    REVISION DATE        : 2/19/2021 
    CREATED / REVISED BY : palani kumar (palanikumar@niyatainfotech.com) 
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! DIO_HANLDER_H */
