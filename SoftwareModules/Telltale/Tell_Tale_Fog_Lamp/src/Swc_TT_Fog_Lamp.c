/* @file FILE NAME */
#ifndef TELL_TALE_FOG_LAMP_C
#define TELL_TALE_FOG_LAMP_C

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
 *  File name                       : Fog_Lamp.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : COSMIC
 *  Platforms supported             : Platform Independent
 *  Description                     : This file contains implementations of gear_position
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/

#include "Swc_TT_Fog_Lamp.h"
#include "Swc_System_Service.h"
#include "board.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "Swc_TT_Mil_Tft.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/



/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to get fog lamp tell tall flag
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NA
 */
uint8_t g_Fog_Lamp_Tell_Tale_flag_u8;

/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/* To initialize the  function to be called in the main function*/
void TT_Fog_Lamp_Init(void)
{
  g_Fog_Lamp_Tell_Tale_flag_u8 = TURN_OFF;
}
 
void TT_Fog_Lamp_DeInit(void)
{
         /* do nothing */  
}

/* This function processes to initialize the peripherals */
void TT_Fog_Lamp_Activate(void)
{
   /* do nothing */
}

/* This function processes to Deinitialize the peripherals */
void TT_Fog_Lamp_DeActivate(void)
{
   /* do nothing */
}

/* This API processes the foglamp telltale process  */
void TT_Fog_Lamp_MainFunction(void)
{
   
   uint8_t fl_Fog_Lamp_Hardware_Input_State = 0;

   uint8_t fl_Pre_Condition_state = FALSE;

   fl_Pre_Condition_state = TT_Fog_Lamp_Pre_Condition();

   if(fl_Pre_Condition_state == TRUE)
   {
    fl_Fog_Lamp_Hardware_Input_State = GPIO_PinRead(BOARD_INITPINS_FOG_LAMP_GPIO, BOARD_INITPINS_FOG_LAMP_GPIO_PIN);

      if(fl_Fog_Lamp_Hardware_Input_State == INPUT_LOW)
      {
         g_Fog_Lamp_Tell_Tale_flag_u8 = TURN_ON;
      }
      else
      {
    	  g_Fog_Lamp_Tell_Tale_flag_u8 = TURN_OFF;
      }
   }
   else
   {
       g_Fog_Lamp_Tell_Tale_flag_u8 = TURN_OFF;
   }
}

/* API is used to check the pre condition status such as ignition on/off, LVSD/HVSD  */   
bool TT_Fog_Lamp_Pre_Condition(void)
{
   uint8_t fl_Ign_Position_u8 = 0;
   uint8_t fl_Fog_LVSD_check_u8;
   uint8_t fl_Fog_HVSD_check_u8;
   uint8_t fl_Precondition_Status;
 
   fl_Ign_Position_u8 = Sys_Service_Get_Ignition_State();

   fl_Fog_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

   fl_Fog_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

  if((fl_Ign_Position_u8 == IGN_OFF)  || (fl_Fog_LVSD_check_u8 == 0) ||
      (fl_Fog_HVSD_check_u8 == 0))
  {
     fl_Precondition_Status = FALSE;
  }
  else
  {
      fl_Precondition_Status = TRUE;
  }

  return fl_Precondition_Status;
}


/* API is used to get the value for foglamp telltale unit */
uint8_t Swc_Fog_LAmp_Get_Value(void)
{
   return g_Fog_Lamp_Tell_Tale_flag_u8;
}





/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0
    REVISION DATE        : 2/19/2021        
    CREATED / REVISED BY : Balsubramaniyan (balasubramaniayan.s@niyatainfoteh.com)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! ADC_C*/
