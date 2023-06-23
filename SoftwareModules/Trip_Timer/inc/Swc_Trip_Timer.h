/* @file FILE NAME */
#ifndef TRIP_TIMER_H
#define TRIP_TIMER_H

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
*  File name                       : Trip_Timer.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : COSMIC
*  Platforms supported             : Platform independent
*  Description                     : This file contains Macros, Typdef and Function Declarations for gear_position files
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/

#include "Swc_Trip_Timer_Cfg.h"
#include "stdint.h"
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

/*
* @brief This enum is used to define for maximum number of Trip timer 
* @Unit:  NA
* @Resolution: NA
* @Range: NA
* @Applicability: NA
* @Note:  
*/
typedef enum
{
   TRIP_TIMER_1 = 0,
   TRIP_TIMER_2,
   TRIP_TIMER_MAX
}TRIP_TRIMER_Lt_Type_En;

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This structure is used to define for Trip timer
 * @param    
 * @param    
 **/
typedef struct 
{
    uint8_t Ret_Triger_Setting;
    uint8_t SW_Ret_Cmd;
    uint32_t g_accumulated_Time;
    uint8_t g_Prev_Sec_Count;
    uint8_t g_Current_Sec_Count;
    uint8_t g_Delta_Trip_Time;  
    uint32_t g_Display_ACCU_Time;
    bool g_Invalid_Status_bl;
}Trip_Timer_Ctrl_St;

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to initialize the  function to be called in the main function
* @param    NA
* @return   NA
* @invocation  This function is invoked by OS
*/
void Trip_Timer_Init(void);

/*
* @brief    This API is used to re-initialize the init variables with default initial values 
* @param    NA
* @return   NA
* @invocation  This function is invoked by OS
*/
void Trip_Timer_DeInit(void);

/*
* @brief    This API is used to activate the peripherals 
* @param    NA
* @return   NA
* @invocation  This function is invoked by OS
*/
void Trip_Timer_Activate(void);

/*
* @brief    This API is used to Deactivate the peripherals 
* @param    NA
* @return   NA
* @invocation This function is invoked by OS
*/
void Trip_Timer_DeActivate(void);


/*
* @brief    This API is used to execute the trip timer main system 
* @param    NA
* @return   NA
* @invocation This function is invoked by OS
*/
void Trip_Timer_MainFunction(void);

/*
* @brief    This API is used to execute the timer function for trip system 
* @param    NA
* @return   NA
* @invocation   This function is invoked by OS
*/

void Trip_Timer_Function(uint8_t p_Trip_ID_u8);

/*
* @brief    This API is used to Trip timer A & Trip Timer B for reset 
* @param    NA
* @return   NA
* @invocation This function is invoked by OS
*/

void Swc_Trip_Timer_Reset(TRIP_TRIMER_Lt_Type_En  p_Trip_Timer_ID);


/*
* @brief    This API is used to get the trip timer value 
* @param    NA
* @return   NA
* @invocation This function is invoked by OS
*/

uint32_t  Swc_Trip_Timer_Get_value(uint8_t  p_Trip_Timer_ID);

/*
* @brief    This API is used to check pre condition state of trip timer such as ignition on off , LVSD/HVSD 
* @param    NA
* @return   bool 
* @invocation  This function is invoked by OS
*/
bool Swc_Check_Trip_Timer_Pre_Condition(void);
void Swc_Trip_Time_Handler(void);

/*
* @brief    This API is used to write the TRIP information on the NVM 
* @param    NA
* @return   NA
* @invocation This function is invoked by OS
*/
void Swc_Trip_Timer_NVM_Write(uint8_t fl_loop_index);

/*
* @brief    This API is used to read the written trip infromation from NVM 
* @param    NA
* @return   NA
* @invocation This function is invoked by OS
*/
void Swc_Trip_Timer_NVM_Read(uint8_t fl_loop_index);

void Swc_Trip_Time_User_Reset(void);

/*
* @brief    This API is used to get the trip timer time value in hours 
* @param    NA
* @return   NA
* @invocation This function is invoked by OS
*/
uint8_t Swc_Trip_Timer_Get_Hour_value(uint8_t fl_Trip_Index_u8);

/*
* @brief    This API is used to get minimum trip timer value 
* @param    NA
* @return   NA
* @invocation This function is invoked by OS
*/
uint8_t Swc_Trip_Timer_Get_Min_value(uint8_t fl_Trip_Index_u8);

/*
* @brief    This API is used to get the status of trip timer system 
* @param    NA
* @return   NA
* @invocation This function is invoked by OS
*/
bool Swc_Get_Trip_Timer_Status(void);
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
#endif /* ! TRIP_TIMER_H */
