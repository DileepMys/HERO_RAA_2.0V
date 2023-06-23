/* @file FILE NAME */
#ifndef TELL_TALE_SEVICE_REMAINDER_H
#define TELL_TALE_SEVICE_REMAINDER_H

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
*  File name                       : Service_Remainder.h
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

#include "stdbool.h"
#include "stdint.h"
#include "Swc_Service_Remainder_cfg.h"
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
* @brief This enum is used to define for service reminder status whether its set or not set 
* @Unit:  Nil
* @Resolution: Nil
* @Range: Nil
* @Applicability: Nil
* @Note:  
*/

typedef enum
{
   SET = 0u,
   NOT_SET,
}Service_Reminder_List_Type_En;


/*
* @brief This enum is used to define  for Service Icon blink status
* @Unit:  Nil
* @Resolution: NIl
* @Range: Nil 
* @Applicability: Nil
* @Note:  
*/

typedef enum
{
	OFF,
    ON,
    Blink
}SERVICE_List_Type_En;


/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/
/*
 * @brief    This Function is used to initialize the gear position init variable with defualt values 
 * @param    N/A
 * @return   NIL
 **/
void TT_Service_Remainder_Init(void);

/*
 * @brief    This Function is used to reset the gear position init variable 
 * @param    N/A
 * @return   NIL
 **/
void TT_Service_Remainder_DeInit(void);

/*
 * @brief    This Function is used to initialize the gear position peripherals
 * @param    N/A
 * @return   NIL
 **/
void TT_Service_Remainder_Activate(void);

/*
 * @brief    This Function is used to reset the gear position peripherals
 * @param    N/A
 * @param    NIL
 **/
void TT_Service_Remainder_DeActivate(void);

/*
 * @brief    This Function is used to execute the service reminder main functions 
 * @param    N/A
 * @return   NIL
 **/
void TT_Service_Remainder_MainFunction(void);


/*
 * @brief    This API is used to reset all the element of service remainder function
 * @param    Nil
 * @return   Nil 
 **/
void Service_Remainder_Reset_Logic(void);

/*
 * @brief    This API is used to get Tell Tale staus for service remainder
 * @param    Nil
 * @return   Nil 
 **/

uint8_t Swc_Service_Remainder_Get_TT_Status(void);

/*
 * @brief    This API is used to check the pre condition such as ignition position ,LVSD/HVSD state
 * @param    NIL
 * @return   bool 
 **/
bool TT_Service_Remainder_Pre_Condition(void);

/*
 * @brief    This structure is used to  write the service reminder data information in NVM
 * @param    Nil
 * @return   Nil 
 **/
void swc_Service_Remainder_Data_NVM_Write(void);

/*
 * @brief    This API is used to read the service remainder data from NVM 
 * @param    Nil
 * @return   Nil 
 **/
void swc_Service_Remainder_Data_NVM_Read (void);

/*
 * @brief    This API is used to define the service reminder reset button status
 * @param    nil
 * @return   nil 
 **/
void Swc_Service_Remainder_Reset_Button_Sense(void);

/*
 * @brief    This API is used to get due distance for service reminder
 * @param    nil
 * @return   nil 
 **/
uint16_t Swc_Service_Remainder_Get_Due_Distance(void);

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to 
* @param    
* @return  
* @invocation 
*/

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
#endif /* ! TELL_TALE_SEVICE_REMAINDER_H */
