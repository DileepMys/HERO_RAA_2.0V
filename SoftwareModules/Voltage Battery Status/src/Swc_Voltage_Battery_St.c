/* @file FILE NAME */
#ifndef VOLTAGE_BATTERY_STATUS_C
#define VOLTAGE_BATTERY_STATUS_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Balasubramaniyan (balasubramaniyan.s@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : Voltage_Battery.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : J-link
 *  Platforms supported             : Platform Independent
 *  Description                     : This file contains implementations of gear_position

 *  @bug
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/

#include "Swc_Voltage_Battery_St.h"
#include "fsl_gpio.h"
#include "Cmp_Tasks.h"
#include "Swc_System_Service.h"
#include "stdint.h"

/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*  
 * @brief: This macro is add offset to actual calculated batter voltage
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

#define BATT_OFFSET            0



/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/


/*
 * @brief: This variable is used to get the pre condition status 
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NIL
 */
static uint8_t g_Precondition_Status;

/*
 * @brief: This variable is used to get the average battery voltage unit
 * @Unit:  volt
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NIL
 */
 uint32_t g_Avereage_Battery_Voltage_Input;

/*
 * @brief: This variable is used to get the ABV value
 * @Unit:  volt
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NIL
 */
 uint32_t g_ABV_Get_Value_u32;

/*
 * @brief: This variable is used to get the ABV value
 * @Unit:  volt
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NIL
 */
 uint32_t g_Voltage_Battery_Get_Value_u32;


/*
 * @brief: This variable is used to store the number of samples
 * @Unit:  NIL
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NIL
 */
 uint32_t g_No_Of_Samples;


/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/* To initialize the  function to be called in the main function*/
void Voltage_Battery_Init(void)
{
  g_ABV_Get_Value_u32 = 0;
}
 
void Voltage_Battery_DeInit(void)
{

  
}

/*Voltage Battery */
void Voltage_Battery_MainFunction(void)
{
   bool fl_Vol_Batt_Pre_Condition_state = FALSE;

   uint32_t fl_Battery_Vol_status_u32;

   fl_Vol_Batt_Pre_Condition_state = Voltage_Battery_Pre_Condition();

   if(fl_Vol_Batt_Pre_Condition_state == TRUE)
   {
	   fl_Battery_Vol_status_u32 = Sys_Service_Voltage_Batt_Get_Status();

	   fl_Battery_Vol_status_u32 = fl_Battery_Vol_status_u32 + BATT_OFFSET;

      if(g_No_Of_Samples <= 9)
      {
         g_Avereage_Battery_Voltage_Input = g_Avereage_Battery_Voltage_Input + fl_Battery_Vol_status_u32;
         g_No_Of_Samples = g_No_Of_Samples + 1;
      }
      else
      {
         g_No_Of_Samples = 0;

         g_Avereage_Battery_Voltage_Input = g_Avereage_Battery_Voltage_Input / 10;

         g_ABV_Get_Value_u32 = g_Avereage_Battery_Voltage_Input;

         // g_ABV_Get_Value_u32 = g_ABV_Get_Value_u32;

         g_Avereage_Battery_Voltage_Input = 0;
      }
   } 
       //g_ABV_Get_Value_u32= g_Avereage_Battery_Voltage_Input;
} 
bool Voltage_Battery_Pre_Condition(void)
{
   bool fl_Precondition_Status = FALSE;

   uint8_t fl_Ign_Position_u8;
   uint8_t fl_Voltage_Battery_LVSD_check_u8;
   uint8_t fl_Voltage_Battery_HVSD_check_u8;

   fl_Ign_Position_u8 = Sys_Service_Get_Ignition_State();

   fl_Voltage_Battery_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

   fl_Voltage_Battery_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

  if((fl_Ign_Position_u8 == IGN_OFF)  || (fl_Voltage_Battery_LVSD_check_u8 == 0) ||
      (fl_Voltage_Battery_HVSD_check_u8 == 0))
  {
     g_Precondition_Status = FALSE;
  }
  else
  {
      g_Precondition_Status = TRUE;
  }

  return g_Precondition_Status;
}


uint32_t Voltage_Battery_Get_Value(void)
{
   return g_ABV_Get_Value_u32;
}





/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : Major.Minor.Patch                          
    REVISION DATE        : MONTH/DATE/YEAR        
    CREATED / REVISED BY : Balsubramaniyan (balasubramaniayan.s@niyatainfoteh.com)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! ADC_C*/
