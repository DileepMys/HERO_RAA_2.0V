/* @file FILE NAME */
#ifndef TELL_TALE_MIL_TFT_C
#define TELL_TALE_MIL_TFT_C

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
 *  File name                       : Mil.c
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
#include "stdbool.h"
#include "Swc_TT_Mil_Tft.h"
#include "hal_stdtypes.h"
#include "Swc_System_Service.h"
#include "CanMgr.h"
#include "Abs_Telltale.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to get  position indication display
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NA
 */
uint8_t g_MIL_Pos_Ind_Display;

/*
 * @brief: This variable is used to get tell tale missing status
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NA
 */
bool g_MIL_TElltale_Missing_Status_bool;
/*
 * @brief: This variable is used to get CAN signal value
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NA
 */
float64 g_MIL_CanSignal_Value_f64;
/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*
 * @brief: This variable is used to get input flag of mileage tell tale
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
uint8_t Mil_Tft_TT_Functional_Input_flag;
/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
uint8_t g_Mil_Tft_TT_Functional_Input;

/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
float64 g_MIL_CanSignal_Value_f64;

/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
float64 g_MIL_Can_Value_f64;

/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
uint8_t g_Precondition_Status;

/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/* To initialize the  function to be called in the main function*/
void TT_Mil_Tft_Init(void)
{
	g_MIL_TElltale_Missing_Status_bool = TRUE;
   
	g_Mil_Tft_TT_Functional_Input = TURN_OFF;
}

/* This API is used to reset the initial variables with default values */
void TT_Mil_Tft_DeInit(void)
{
	g_MIL_Pos_Ind_Display = 0;

	g_Mil_Tft_TT_Functional_Input = TURN_OFF;
  
}

/* API is used to activate the initial variables with default values */
void TT_Mil_Tft_Activate(void)
{
   /* do nothing */
}

/* API is used to deactivate the initial variables with default values*/
void TT_Mil_Tft_DeActivate(void)
{
   /* do nothing */
}

/* API is used to execute tell tale mil function  */
void TT_Mil_Tft_MainFunction(void)
{
   uint8_t fl_CAN_Time_status_u8;
   uint8_t fl_CAN_Bus_State_u8;
   uint8_t fl_CAN_Mil_Status_u8;

   uint8_t fl_Fog_Lamp_Hardware_Input_State = 0;

   uint8_t fl_Pre_Condition_state = FALSE;

   fl_Pre_Condition_state = TT_Mil_Tft_Pre_Condition();

   if(g_Precondition_Status == TRUE)
   {

       /* Get CAN Bus current status */
      fl_CAN_Bus_State_u8 = App_Can_bus_off_Get_indication();

      if(fl_CAN_Bus_State_u8 != CAN_BUS_ON)
      {
    	  g_Mil_Tft_TT_Functional_Input = TURN_ON;
      }
      else if(FALSE != g_MIL_TElltale_Missing_Status_bool)
      {
    	  g_Mil_Tft_TT_Functional_Input = TURN_ON;

        /* Message received */
      //  g_MIL_TElltale_Missing_Status_bool = FALSE;
      }
      else
      {

     CanMgr_Read_mil_0x130_s(&g_MIL_Can_Value_f64);

         if(g_MIL_Can_Value_f64 == MIL_ENGINE_CHECK )
         {
         g_Mil_Tft_TT_Functional_Input = TURN_ON;
         }
         else  if((g_MIL_Can_Value_f64 == 0) || (g_MIL_Can_Value_f64 == 2) || (g_MIL_Can_Value_f64 == 3))
         {
         g_Mil_Tft_TT_Functional_Input = TURN_OFF;
         }

      }

   }
   else
   {
      g_Mil_Tft_TT_Functional_Input = TURN_OFF;
   }
}

/* Tell tale MIL pre condition check */
bool TT_Mil_Tft_Pre_Condition(void)
{
   uint8_t fl_Ign_Position_u8;

   uint8_t fl_Mil_LVSD_check_u8;

   uint8_t fl_Mil_HVSD_check_u8;

   uint8_t fl_Precondition_Status;
 
   fl_Ign_Position_u8 = Sys_Service_Get_Ignition_State();

   fl_Mil_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

   fl_Mil_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

  if((fl_Ign_Position_u8 == IGN_OFF)  || (fl_Mil_LVSD_check_u8 == 0) ||
      (fl_Mil_HVSD_check_u8 == 0))
  {
     g_Precondition_Status = FALSE;
  }
  else
  {
      g_Precondition_Status = TRUE;
  }

  return g_Precondition_Status;
}

/* This API is used to get functional input of tell tall malfunction */
uint8_t Swc_Mil_Tft_Get_Value(void)
{

	return g_Mil_Tft_TT_Functional_Input;
}

/* this API is used to get call back for malfunction timer out from CAN mgr */
void CanMgr_MIL_Timeout_Callback_0x130(void)
{
	
   CanMgr_MIL_Timeout_Flag();
}

/* API is used to get timeout flag for malfunction telltale */
void CanMgr_MIL_Timeout_Flag(void)
{
	g_MIL_TElltale_Missing_Status_bool = TRUE;
}

/* API is used to get immediate call back for telltale malfunction */
void CanMgr_MIL_reception_cbk(void)
{

	g_MIL_TElltale_Missing_Status_bool = FALSE;
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
#endif /* ! TELL_TALE_MIL_TFT_C*/
