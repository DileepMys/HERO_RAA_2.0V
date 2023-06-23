/* @file FILE NAME */
#ifndef TELL_TALE_OIL_PRESSURE_C
#define TELL_TALE_OIL_PRESSURE_C

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
 *  File name                       : Oil Pressure.c
 *  Version                         : V1.0.0
 *  Micros supported                : Mico Independent
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

#include "Swc_TT_Oil_Pressure.h"
#include "hal_stdtypes.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include "Swc_System_Service.h"

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
 * @brief: This variable is used to define the function input of telltale flag oil pressure
 * @Unit:  uint8_t
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NA
 */
uint8_t g_Oil_Pressure_TFT_TT_Functional_Input_flag_u8;


/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/* API shall is used to initialize the init variables with defult values*/
void TT_Oil_Pressure_Init(void)
{
   g_Oil_Pressure_TFT_TT_Functional_Input_flag_u8 = OIL_PRESSURE_TT_TURN_OFF;
}

/* API shall is used to reset the init variables with defult values*/ 
void TT_Oil_Pressure_DeInit(void)
{
      /* do nothing */
  
}

/* API is used to configure the intial variables   */
void TT_Oil_Pressure_Activate (void)
{
   /* do nothing */
}

/* API is used to reset the  intial variables  */
void TT_Oil_Pressure_DeActivate (void)
{
   /* do nothing */
}

/* API is used to configure the main  telltale oil pressure functions   */
void TT_Oil_Pressure_MainFunction(void)
{
   
   uint8_t fl_Oil_Pressure_Hardware_Input_State;


   uint8_t fl_Pre_Condition_state = FALSE;

   fl_Pre_Condition_state = TT_Oil_Pressure_Pre_Condition();

   if(fl_Pre_Condition_state == TRUE)
   {
    fl_Oil_Pressure_Hardware_Input_State = GPIO_PinRead(BOARD_INITPINS_DI_LOW_OIL_PRESSURE_MCU_IN_GPIO, BOARD_INITPINS_DI_LOW_OIL_PRESSURE_MCU_IN_GPIO_PIN);//GET_OIL_PRESSURE_HARDWARE_INPUT_INDICATOR();

     if(fl_Oil_Pressure_Hardware_Input_State == INPUT_HIGH)
     {
        g_Oil_Pressure_TFT_TT_Functional_Input_flag_u8 = OIL_PRESSURE_TT_TURN_OFF;
     }
     else
     {
        g_Oil_Pressure_TFT_TT_Functional_Input_flag_u8 = OIL_PRESSURE_TT_TURN_ON ;
     }
   }
   else 
   {
      g_Oil_Pressure_TFT_TT_Functional_Input_flag_u8  = OIL_PRESSURE_TT_TURN_OFF;
   }

}  
/* configuration shall configure the NVM Functionality   */
uint8_t TT_Oil_Pressure_Pre_Condition(void)
{
   uint8_t fl_Ign_Position_u8 = 0;
   uint8_t fl_Oil_Pressure_LVSD_check_u8;
   uint8_t fl_Oil_Pressure_HVSD_check_u8;
   bool fl_Precondition_Status;
 
  fl_Ign_Position_u8 = Sys_Service_Get_Ignition_State();

  fl_Oil_Pressure_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

  fl_Oil_Pressure_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

  if( (fl_Ign_Position_u8   == IGN_OFF) || 
      (fl_Oil_Pressure_LVSD_check_u8 == 0) ||
      (fl_Oil_Pressure_HVSD_check_u8 == 0) )
  {
     fl_Precondition_Status = FALSE;
  }
  else
  {
      fl_Precondition_Status = TRUE;
  }

  return fl_Precondition_Status;
}

/* API is used to actual value of the telltale oil pressure  */
uint8_t Swc_Oil_Pressure_Get_Value(void)
{
   return g_Oil_Pressure_TFT_TT_Functional_Input_flag_u8;
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
