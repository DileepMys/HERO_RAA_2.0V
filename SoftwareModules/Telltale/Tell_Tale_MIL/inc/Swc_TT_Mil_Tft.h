/* @file FILE NAME */
#ifndef TELL_TALE_MIL_TFT_H
#define TELL_TALE_MIL_TFT_H

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
*  File name                       : Mil.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : COSMIC
*  Platforms supported             : Platform Independent
*  Description                     : This file contains Macros, Typdef and Function Declarations for gear_position files
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

#include "Swc_TT_Mil_Tft_cfg.h"
#include "stdint.h"
/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/



/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This enum is used to define malfunction status of the telltale
 * @param    NA
 * @param    NA
 **/
typedef enum
{
   MIL_SET = 0u,
   MIL_NOT_SET,
   MIL_MAX
}Mil_TFT_List_Type_En;


/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to initialize the initial variables with default values
* @param    Nil
* @return   Nil
* @invocation 
*/
void TT_Mil_Tft_Init(void);


/*
* @brief    This API is used to reset the initial variables with default values
* @param    Nil
* @return   Nil
* @invocation 
*/
void TT_Mil_Tft_DeInit(void);

/*
* @brief    This API is used to activate the initial variables with default values
* @param    Nil
* @return   Nil
* @invocation 
*/
void TT_Mil_Tft_Activate(void);

/*
* @brief    This API is used to deactivate the initial variables with default values
* @param    Nil
* @return   Nil
* @invocation 
*/
void TT_Mil_Tft_DeActivate(void);

/*
* @brief    This API is used to execute tell tale mil function 
* @param    Nil
* @return   Nil
* @invocation 
*/
void TT_Mil_Tft_MainFunction(void);

/*
* @brief    This API is used to get pre condition check such as ignition on/off, LVSD/HVSD 
* @param    Nil
* @return   bool
* @invocation 
*/
bool TT_Mil_Tft_Pre_Condition(void);

/*
* @brief    This API is used to get functional input of tell tall malfunction 
* @param    Nil
* @return   Nil
* @invocation 
*/
uint8_t Swc_Mil_Tft_Get_Value(void);

/*
* @brief    This API is used to get call back for malfunction timer out from CAN mgr 
* @param    Nil
* @return   Nil
* @invocation 
*/
void CanMgr_MIL_Timeout_Callback_0x130(void);

/*
* @brief    This API is used to get timeout flag for malfunction telltale
* @param    Nil
* @return   Nil
* @invocation 
*/
void CanMgr_MIL_Timeout_Flag(void);

/*
* @brief    This API is used to get immediate call back for telltale malfunction
* @param    Nil
* @return   Nil
* @invocation 
*/
void CanMgr_MIL_reception_cbk(void);
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0
    REVISION DATE        : 2/19/2021        
    CREATED / REVISED BY : Balasubramaniyan (balasubramaniyan.s@niyatainfotech.com)
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! TELL_TALE_MIL_TFT_H */
