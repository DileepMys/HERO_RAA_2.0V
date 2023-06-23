/* @file FILE NAME */
#ifndef TRIP_TIMER_C
#define TRIP_TIMER_C

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
 *  File name                       : timer_trip.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : COSMIC
 *  Platforms supported             : Platform Independent
 *  Description                     : This file contains implementations of gear_position
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/

#include "Swc_Trip_Timer.h"
#include "Swc_System_Service.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "CanMgr_cfg.h"
#include "rtc.h"
#include "Swc_Nvm_Handler.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
* @brief This macro is used to define the pre condition status of trip timer
* @Unit: NIL 
* @Resolution: NIL
* @Range: bool
* @Applicability: NIL
* @Note:  
*/
#define SWC_CHECK_TRIP_TIMER_PRE_CONDITION TRUE

/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to get software reset command
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NA
 */
uint8_t g_Trip_timer_software_rst_cmd_u8;

/*
 * @brief: This variable is used to store the accumulated trip time
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NA 
 */

uint8_t g_Trip_timer_ACC_u8;
/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

uint8_t g_Delta_trip_u8;


/*
 * @brief: This structure is used to get trip time control structure
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NA
 */
Trip_Timer_Ctrl_St g_Trip_Time_Ctrl_St[TOTAL_TRIP_COUNT];

/*
 * @brief: This variable is used to get CAN engine speed
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NA 
 */
uint32_t  g_CAN_Engine_speed_u32 = 0;

/*
 * @brief: This variable is used to define the button pressed period
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NA 
 */
uint8_t g_Button_Pressed_Period = 0;

/*
 * @brief: This variable is used to get the trip time in minutes
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NA 
 */
uint8_t g_Trip_Time_Min_u8[2];

/*
 * @brief: This variable is used to get the trip time in hours
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NA 
 */
uint8_t g_Trip_Time_Hr_u8[2];

/*
 * @brief: This structure is used to get the displayed trip time
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: NA
 */
uint32_t g_Displayed_Trip_Time[TOTAL_TRIP_COUNT];
/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    This function processes the 
 * @param    Nil
 * @return   uint8_t
 */
uint8_t swc_Get_Sec_From_RTC(void);

/*
 * @brief    This function processes the 
 * @param    p_Trip_Timer_ID
 * @return   Nil
 */
static void Swc_Trip_Timer_Clear_Info(uint8_t p_Trip_Timer_ID);
/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/* To initialize the  function to be called in the main function*/
void Trip_Timer_Init(void)
{
  uint8_t fl_loop_index  = 0;

  /* read trip timer value from NVM */
  for(fl_loop_index =0; fl_loop_index < TRIP_TIMER_MAX; fl_loop_index++)
  {
    Swc_Trip_Timer_NVM_Read(fl_loop_index);

    /* update accumulated trip time */
    g_Trip_Time_Ctrl_St[fl_loop_index].g_Current_Sec_Count = swc_Get_Sec_From_RTC();

  }  

}

/* API is used to re-initialize the init variables with default initial values */ 
void Trip_Timer_DeInit(void)
{
  /* do nothing */
}

/*  API is used to activate the peripherals */
void Trip_Timer_Activate(void)
{
  /* do nothing */
}

/* API is used to Deactivate the peripherals */
void Trip_Timer_DeActivate(void)
{
  /* do nothing */
}

/* API is used to execute the trip timer main system */
void Trip_Timer_MainFunction(void)
{
  bool fl_Trip_Time_Pre_Cond_St = FALSE;
  uint8_t fl_loop_index = 0;

  /* Get pre condition status */
  fl_Trip_Time_Pre_Cond_St = Swc_Check_Trip_Timer_Pre_Condition();

  /* Process if pre condition statisfied */
  if(fl_Trip_Time_Pre_Cond_St == TRUE)
  {

    /* iterate through trip A and trip B */
    for(fl_loop_index =0; fl_loop_index < TRIP_TIMER_MAX; fl_loop_index++)
      {
        /* PROCESS TRIP TIMER */
        Trip_Timer_Function(fl_loop_index);

        if( g_Trip_Time_Ctrl_St[fl_loop_index].g_Invalid_Status_bl == TRUE)
        {
          /* clear invalid status flag if set */
          g_Trip_Time_Ctrl_St[fl_loop_index].g_Invalid_Status_bl = FALSE;

        }
        else
        {
          /* do nothing */
        }

      }     
  }
  else
  {
    /* clear display accumulated time and has to display --- */
    g_Trip_Time_Ctrl_St[TRIP_TIMER_1].g_Invalid_Status_bl = TRUE;

    g_Trip_Time_Ctrl_St[TRIP_TIMER_2].g_Invalid_Status_bl = TRUE;
  }
}

/* API is used to execute the timer function for trip syatem */
void Trip_Timer_Function(uint8_t p_Trip_ID_u8)
{
  /* local variable */
  uint8_t fl_CAN_Read_Result  = 0;





    /* Get Engine RPM from CAN */
    g_CAN_Engine_speed_u32 = TACHOMETER_GET_CALL_BACK_STATE();

    /* Engine is runninng in Normal RPM */
    if((g_CAN_Engine_speed_u32 > MIN_ENGINE_RPM) && (g_CAN_Engine_speed_u32 <= MAX_ENGINE_RPM))
    {
      /* Copy current sec count get from RTC to previous count */
      g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Prev_Sec_Count = g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Current_Sec_Count;

      /* Get current sec from RTC */
      g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Current_Sec_Count = swc_Get_Sec_From_RTC();

      if(g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Prev_Sec_Count > 
         g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Current_Sec_Count)
      {
         /* Delta trip time calculation*/
          g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Delta_Trip_Time = SEC_60 + (g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Current_Sec_Count - 
                                                  g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Prev_Sec_Count);
      }
      else
      {

        g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Delta_Trip_Time = (g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Current_Sec_Count - 
                                                          g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Prev_Sec_Count);
      }


      if(g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Delta_Trip_Time <= MAX_DELTA_TRIP_TIME)
      {
        /* Accumulate Trip time*/
        g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_accumulated_Time = 
                            g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_accumulated_Time +
                            g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Delta_Trip_Time;

      }
      
      if(g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_accumulated_Time > TRIP_TIMER_ACC_MAX)
      {
        g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_accumulated_Time = TRIP_TIMER_ACC_MAX;
      }

    }

        /* displayable time reaches 100hour, then has to roll over */
    if(g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Display_ACCU_Time >= TRIP_TIME_DISP_MAX)
    {

      /* initialize accumulated time */
      g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_accumulated_Time = 0;
    }
    else
    {
      /* convert the accumulated time into displayable time */
      g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_Display_ACCU_Time = (g_Trip_Time_Ctrl_St[p_Trip_ID_u8].g_accumulated_Time) % TRIP_TIME_DISP_MAX;
    }
}


/* API is used to clear trip information on the system */
static void Swc_Trip_Timer_Clear_Info(uint8_t p_Trip_Timer_ID)
{
  g_Trip_Time_Ctrl_St[p_Trip_Timer_ID].g_Display_ACCU_Time = 0;

  /* clear accumulated time */
  g_Trip_Time_Ctrl_St[p_Trip_Timer_ID].g_accumulated_Time = 0;
}

/*Check the Trip timer A & Trip Timer B for reset */
void Swc_Trip_Timer_Reset(TRIP_TRIMER_Lt_Type_En  p_Trip_Timer_ID)
{
    if(p_Trip_Timer_ID == TRIP_TIMER_1)
    {

      Swc_Trip_Timer_Clear_Info(TRIP_TIMER_1);

    }
    else if(p_Trip_Timer_ID == TRIP_TIMER_2)
    {
      Swc_Trip_Timer_Clear_Info(TRIP_TIMER_2);

    }
    else
    {
      /* do nothing */
    }
}

uint8_t swc_Get_Sec_From_RTC(void)
{
  RTC_TIME_STAMP_ST  fl_RTC_Time_Stamp;

  fl_RTC_Time_Stamp = RTC_Time_Display();

  return (fl_RTC_Time_Stamp.second);
}

/* This API is used to write the TRIP information on the NVM */
void Swc_Trip_Timer_NVM_Write(uint8_t fl_loop_index)
{
  bool fl_NVM_Status_bl = TRUE;

  /* Get NVM Status */
  fl_NVM_Status_bl = Swc_Get_NVM_Status();

  if((fl_loop_index < TRIP_TIMER_MAX) && (fl_NVM_Status_bl == FALSE))
  {
    /* write trip timer value in NVM Block */
    NVM_Byte_Write_Allocation((TRIP_TIMER_NVM_BLOCK_ID + fl_loop_index),(uint8_t*)&g_Trip_Time_Ctrl_St[fl_loop_index].g_accumulated_Time);

  }
}

/* API is used to read the written trip infromation from NVM */
void Swc_Trip_Timer_NVM_Read(uint8_t fl_loop_index)
{
   if(fl_loop_index < TRIP_TIMER_MAX)
   {
    /* write trip timer value in NVM Block */
    NVM_Byte_Read_Allocation((TRIP_TIMER_NVM_BLOCK_ID + fl_loop_index),(uint8_t*)&g_Trip_Time_Ctrl_St[fl_loop_index].g_accumulated_Time);

   }
}

/* This API is used to check pre condition state of trip timer such as ignition on off , LVSD/HVSD */
bool Swc_Check_Trip_Timer_Pre_Condition(void)
{
   bool fl_Precondition_Status = FALSE;
   
   uint8_t fl_Ign_Position_u8 = 0;
   uint8_t fl_Gear_LVSD_check_u8;
   uint8_t fl_Gear_HVSD_check_u8;
   uint8_t fl_EEPROM_state_u8 = 0;
   uint8_t fl_CAN_Msg_Timeout_Status = FALSE;
   uint8_t fl_CAN_Bus_State_u8; 
 
  fl_Ign_Position_u8 = Sys_Service_Get_Ignition_State();

  fl_Gear_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

  fl_Gear_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

  /* fl_EEPROM_state_u8 = GET_EEPROM_STATUS();*/
  
    /* Get CAN Bus current status */
    fl_CAN_Bus_State_u8 = GET_CAN_BUS_STATUS();

    fl_CAN_Msg_Timeout_Status =  Swc_Tacho_CAN_Msg_Timeout_Staus();

  if((fl_Ign_Position_u8    == IGN_OFF)  || (fl_Gear_LVSD_check_u8 == 0) ||
      (fl_Gear_HVSD_check_u8 == 0)   ||  (fl_EEPROM_state_u8 == 1) ||
      (fl_CAN_Bus_State_u8 == CAN_BUS_OFF) || (fl_CAN_Msg_Timeout_Status == TRUE))
  {
     fl_Precondition_Status = FALSE;
  }
  else
  {
      fl_Precondition_Status = TRUE;
  }

  return fl_Precondition_Status;
}

/* This API is used to get the trip tier value */
uint32_t  Swc_Trip_Timer_Get_value(uint8_t  p_Trip_Timer_ID)
{
    //return (g_Trip_Time_Ctrl_St[p_Trip_Timer_ID].g_Display_ACCU_Time);
    return (g_Trip_Time_Ctrl_St[p_Trip_Timer_ID].g_accumulated_Time);
}

/* This API is used to get the trip timer time value in hours */
uint8_t Swc_Trip_Timer_Get_Hour_value(uint8_t fl_Trip_Index_u8)
{
	g_Trip_Time_Hr_u8[fl_Trip_Index_u8] =  ((g_Trip_Time_Ctrl_St[fl_Trip_Index_u8].g_Display_ACCU_Time)/3600);

	return g_Trip_Time_Hr_u8[fl_Trip_Index_u8];
}

/* This API is used to get minimum trip timer value */
uint8_t Swc_Trip_Timer_Get_Min_value(uint8_t fl_Trip_Index_u8)
{
	if(g_Trip_Time_Hr_u8[fl_Trip_Index_u8] == 0)
	{
		g_Trip_Time_Min_u8[fl_Trip_Index_u8] =  (g_Trip_Time_Ctrl_St[fl_Trip_Index_u8].g_Display_ACCU_Time)/60;
	}
	else
	{
		g_Trip_Time_Min_u8[fl_Trip_Index_u8] = ((g_Trip_Time_Ctrl_St[fl_Trip_Index_u8].g_Display_ACCU_Time) - (3600*g_Trip_Time_Hr_u8[fl_Trip_Index_u8]))/60;
	}

	return g_Trip_Time_Min_u8[fl_Trip_Index_u8];
}

/* This API is used to get the status of trip timer system */
bool Swc_Get_Trip_Timer_Status(void)
{
  bool fl_Trip_Timer_Status = FALSE;

  if((g_Trip_Time_Ctrl_St[TRIP_TIMER_1].g_Invalid_Status_bl == TRUE) ||
     (g_Trip_Time_Ctrl_St[TRIP_TIMER_2].g_Invalid_Status_bl == TRUE))
      {

        fl_Trip_Timer_Status = FALSE;
      }
      else
      {
        fl_Trip_Timer_Status = TRUE;
      }

  return (fl_Trip_Timer_Status);
}
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0
    REVISION DATE        : 2/19/2021        
    CREATED / REVISED BY : Balsubramaniyan (balasubramaniayan.s@niyatainfoteh.com)       
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! TRIP_TIMER_C */
