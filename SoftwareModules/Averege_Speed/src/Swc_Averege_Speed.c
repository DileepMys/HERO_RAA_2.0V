/* @file AVERAGE_SPEED_C */
#ifndef AVERAGE_SPEED_C
#define AVERAGE_SPEED_C

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
 *  File name                       : Average Speed.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : J-Link
 *  Platforms supported             : Platform Independent
 *  Description                     : This file contains implementations of gear_position

 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "Swc_Averege_Speed.h"
#include "Swc_Trip_Timer.h"
#include "Swc_Odometer.h"
#include "Swc_Service_Remainder.h"
#include "Swc_Speedometer.h"
#include "TC.h"
#include <stdlib.h>
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This structure variable is having the information about speed and gear detail information
 * @Unit:  NIL
 * @Resolution: NIL
 * @Range: NIL
 * @Applicability: Odo meter implementation
 */
Avereage_Speed_Ctrl_St g_Average_Speed_Ctrl_St[TOTAL_TRIP_COUNT];
/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/


/*
 * @brief: This variable is used to store the number of Kilo meter 
 * @Unit:  Kilometer
 * @Resolution: 1Km
 * @Range: 0-199
 * @Applicability: Nil 
 */
uint32_t g_TripOdo_Km_u32[TOTAL_TRIP_COUNT];

/*
 * @brief: This variable is used to store the number of distance accumulated 
 * @Unit:  Kilometer
 * @Resolution: 1Km
 * @Range: 0-199
 * @Applicability: Nil 
 */
uint64_t g_TripOdo_Dist_ACCU_u64[TOTAL_TRIP_COUNT];

/*
 * @brief: This variable is used to store the number of distance accumulated 
 * @Unit:  Kilometer
 * @Resolution: 1Km
 * @Range: 0-199
 * @Applicability: Nil 
 */
uint32_t g_TripOdo_Dist_N_u32[TOTAL_TRIP_COUNT];

/*
 * @brief: This variable is used to store the total trip count value
 * @Unit:  Kilometer
 * @Resolution: 1Km
 * @Range: 0-199
 * @Applicability: Nil 
 */
uint32_t g_TripOdo_delta_u32[TOTAL_TRIP_COUNT];

/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    
 * @param    
 * @return   
 */



static uint16_t g_Speed_Input_u16;

/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/* To initialize the  function to be called in the main function*/
void Average_Speed_Init(void)
{
   for(uint8_t index = 0; index < TOTAL_TRIP_COUNT; index++)
   {
      g_TripOdo_Km_u32[index] = 0;

      g_Average_Speed_Ctrl_St[index].display_update_time = 0;
       
      g_TripOdo_Dist_ACCU_u64[index] =  TripOdo_Acc_value(index);

      g_TripOdo_Dist_N_u32[index] = IFE_ODO_value();

       g_Average_Speed_Ctrl_St[index].g_Displayed_Trip_Average_Speed = 0;
   }
}
/*  API is used to reset the initital value of the variable*/ 
void Average_Speed_Deinit(void)
{
   /* do nothing */
}

/* API is used to activate the peripherals */
void Average_Speed_Activate(void)
{
   /* do nothing */
}

/* API is used to deactivate the peripherals */
void Average_Speed_Deactivate(void)
{
    /* do nothing */
}

/* API is used to get current status of average speed range */
void Average_Speed_MainFunction(void)
{

   bool fl_Average_Speed_Pre_Cond_St = FALSE;
   uint8_t fl_loop_index = 0;

  /* Get pre condition status */
  fl_Average_Speed_Pre_Cond_St = Swc_Check_Average_Speed_Pre_Condition();

  /* Process if pre condition statisfied */
  if(fl_Average_Speed_Pre_Cond_St == TRUE)
  {
    /* iterate through trip A and trip B */
    for(fl_loop_index =0; fl_loop_index < AVERAGE_SPEED_MAX; fl_loop_index++)
      {
        Average_Speed_Function(fl_loop_index);

        if(g_Average_Speed_Ctrl_St[fl_loop_index].Pre_Cond_Status == TRUE)
        {
            g_Average_Speed_Ctrl_St[fl_loop_index].Pre_Cond_Status = FALSE;
         
        }

      }     
      
  }
  else
  {
     g_Average_Speed_Ctrl_St[0].g_Displayed_Trip_Average_Speed = 0;
     g_Average_Speed_Ctrl_St[1].g_Displayed_Trip_Average_Speed = 0;
     g_Average_Speed_Ctrl_St[0].Pre_Cond_Status = TRUE;
     g_Average_Speed_Ctrl_St[1].Pre_Cond_Status = TRUE;
  }

}
/* This API is used to get average speed of the system  */
void Average_Speed_Function(uint8_t p_Average_Speed_ID_u8)
{
  /* local variable */
  uint64_t fl_Trip_Timer_KM;
  uint32_t fl_Timer_Trip_Acc;
  uint16_t fl_average_speed_u16;
  float64 fl_get_input_speed_f64;
  uint16_t fl_delta_u16 = 0;
  uint32_t fl_sample_average_speed = 0;

  /* hard reset set */
   if(g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Average_Speed_Ret_Triger_Setting == 1)
   {
      g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Average_Speed_Ret_Triger_Setting = 0;
      g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Average_Speed_KM = 0;
   } 
   else
   {
      if( g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Average_Speed__SW_Ret_Cmd == 1)
      {
         g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Average_Speed__SW_Ret_Cmd = 0;
         g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Average_Speed_KM = 0;
      }
      else
      {
         /*Get Trip Timer function*/
         fl_Timer_Trip_Acc = Swc_Trip_Timer_Get_value(p_Average_Speed_ID_u8);
         
         /* Get Trip Odo distance value */
         fl_Trip_Timer_KM = AVS_TRIP_ODO_CM(p_Average_Speed_ID_u8);

         fl_Trip_Timer_KM = fl_Trip_Timer_KM;

         

         if(fl_Timer_Trip_Acc != 0)
         {
            Swc_Sampling_Trip_Odo_Time(fl_Trip_Timer_KM, fl_Timer_Trip_Acc, p_Average_Speed_ID_u8);

            if(fl_Trip_Timer_KM > INIT_DIST)
            {
               /*Check KMph or Mph Selection*/
               if(AVERAGE_SPEED_KMPH == AVERAGE_SPEED_UNIT_SELECTION)
               {
                  g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Displayed_Avg_Speed_Unit = AVERAGE_SPEED_KMPH;
                                 
                  fl_average_speed_u16 = round_int(g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Average_Speed_KM, 10);
                  
                  fl_average_speed_u16 = hysteresis_int(fl_average_speed_u16, g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Displayed_Trip_Average_Speed*100, 100);
                  
                  if(g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].display_update_time == 0)
                  {
                     g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Displayed_Trip_Average_Speed = fl_average_speed_u16 / 100;

                     g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].display_update_time = 100;
                  }
                  else
                  {
                     g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].display_update_time--;
                  }
                  

               }
               else
               {
                  g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Displayed_Avg_Speed_Unit = AVERAGE_SPEED_MPH;

                  /*Need to add MPG*/
               }

               if(g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Displayed_Trip_Average_Speed > SPEED_MAX)
               {

                  g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Displayed_Trip_Average_Speed = SPEED_MAX;

               }
            }  
            else
            {   
               g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Displayed_Trip_Average_Speed = 0;
      
            }
         }
      }   
   }
}

void Swc_Sampling_Trip_Odo_Time(uint64_t get_odo, uint32_t get_time, uint8_t Trip_id)
{
   uint32_t Add_sample_Average = 0;

   uint32_t fl_sampling_value_u32 = 0;

   if(get_odo > 0xFFFFFFFFFF)
   {
      get_odo = get_odo / 2;

      get_time = get_time / 2;
   }
   else if(get_time > TRIP_TIME_DISP_MAX)
   {
      get_odo = get_odo / 2;

      get_time = get_time / 2;      
   }
   else if(get_time != 0)
   {
      fl_sampling_value_u32 = get_odo / get_time;
   }
   else
   {
      /*Do nothing*/
   }

   g_Average_Speed_Ctrl_St[Trip_id].g_Average_Speed_KM = (fl_sampling_value_u32 * 36)/10;
}

/* API is used to get current status of average speed  */
bool Swc_Check_Average_Speed_Pre_Condition(void)
{

   uint8_t fl_Gear_LVSD_check_u8;
   uint8_t fl_Gear_HVSD_check_u8;
   bool fl_EEPROM_state_u8 = FALSE;
   bool fl_Precondition_Status = FALSE;
   
   uint8_t fl_Ign_Position_u8 = 0;
 
  fl_Ign_Position_u8 = Sys_Service_Get_Ignition_State();

  fl_Gear_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

  fl_Gear_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

  fl_EEPROM_state_u8 = Swc_Get_ODO_NVM_Error_Status();
  
   /* Get pre-Condition status */
   if( (fl_Ign_Position_u8 == IGN_OFF)  || (fl_Gear_LVSD_check_u8 == SET) || 
      (fl_Gear_HVSD_check_u8 == SET) || (fl_EEPROM_state_u8 == TRUE)) 
   {
      fl_Precondition_Status = FALSE;
   }
   else
   {
      fl_Precondition_Status = TRUE;
   }

   return (fl_Precondition_Status);

}

/*Check the Trip timer Acc 1 & Trip Timer Acc 2 for reset */
void Swc_Average_Speed_Reset(Trip_Timer_Acc_Lt_Type_En  p_Average_Speed_ID)
{
   if(p_Average_Speed_ID == TRIP_TIME_ACC_1)
   {
      g_Average_Speed_Ctrl_St[p_Average_Speed_ID].g_Displayed_Trip_Average_Speed = 0;
      g_TripOdo_Dist_ACCU_u64[p_Average_Speed_ID] = 0;
      g_Average_Speed_Ctrl_St[p_Average_Speed_ID].display_update_time = 0;
      g_Average_Speed_Ctrl_St[p_Average_Speed_ID].sample_counter = 0;
   }
   else if(p_Average_Speed_ID == TRIP_TIME_ACC_2)
   {
      g_Average_Speed_Ctrl_St[p_Average_Speed_ID].g_Displayed_Trip_Average_Speed = 0;
      g_TripOdo_Dist_ACCU_u64[p_Average_Speed_ID] = 0;
      g_Average_Speed_Ctrl_St[p_Average_Speed_ID].display_update_time = 0;
      g_Average_Speed_Ctrl_St[p_Average_Speed_ID].sample_counter = 0;
   }
   else
   {
      /* do nothing */
   }
}

/* API is used to get current status of average speed  */
uint16_t Swc_Avereage_Speed_Get_value(uint8_t p_Average_Speed_ID_u8)
{
   return g_Average_Speed_Ctrl_St[p_Average_Speed_ID_u8].g_Displayed_Trip_Average_Speed;
}

/* API is used to get current status of average speed  */
bool Swc_Average_Speed_Get_Status(void)
{
   bool fl_Ret_Status_bl;
   
   if((g_Average_Speed_Ctrl_St[0].Pre_Cond_Status != FALSE) || 
      (g_Average_Speed_Ctrl_St[1].Pre_Cond_Status != FALSE))
      {
         fl_Ret_Status_bl = FALSE;
      }
      else
      {
         fl_Ret_Status_bl = TRUE;
      }
}

/* API is used to get current status of average speed  */
uint32_t round_int(uint32_t actual_input, uint32_t resolution)
{
   uint32_t modulus_int = 0;

   uint32_t div_int = 0;

   uint32_t processed_input = 0;
   
   modulus_int = actual_input % resolution;
   
   div_int = actual_input / resolution;

   if(modulus_int >= (resolution / 2))
   {
      processed_input = div_int * resolution + resolution;
   }
   else
   {
      processed_input = div_int * resolution;
   }

   return processed_input;
}

/* API is used to get current status of average speed  */
uint32_t hysteresis_int(uint32_t actual_input, uint32_t previous_input, uint16_t hysteresis)
{
   uint32_t delta = 0;

   delta = abs(actual_input - previous_input);

   if(delta >= hysteresis)
   {
      return actual_input;
   }
   else
   {
      return previous_input;
   }
}

/* API is used to get current status of average speed  */
uint64_t AVS_TRIP_ODO_CM(uint8_t trip_id)
{
   /*To store the Trip km value*/
	g_TripOdo_Km_u32[trip_id] = GET_ODO_VALUE();
	
   /*Check the current and Previous Odo value*/
	if(g_TripOdo_Dist_N_u32[trip_id] > g_TripOdo_Km_u32[trip_id])
	{
		/*Hold the ODO value*/
	   g_TripOdo_delta_u32[trip_id] = (g_TripOdo_Km_u32[trip_id] + 10000) - g_TripOdo_Dist_N_u32[trip_id];
	}
	else
	{
		/*Hold the ODO value*/
		g_TripOdo_delta_u32[trip_id] = g_TripOdo_Km_u32[trip_id] - g_TripOdo_Dist_N_u32[trip_id];
	}

	g_TripOdo_Dist_ACCU_u64[trip_id] = g_TripOdo_Dist_ACCU_u64[trip_id] + g_TripOdo_delta_u32[trip_id];

   /*Store the current odo value*/
	g_TripOdo_Dist_N_u32[trip_id] = g_TripOdo_Km_u32[trip_id];

   return g_TripOdo_Dist_ACCU_u64[trip_id];
}

/* API is used to get current status of average speed  */
uint64_t AVS_Accu_Value(uint8_t trip_id)
{
   return g_TripOdo_Dist_ACCU_u64[trip_id];
}

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
***********************************************************************************************************************
    REVISION NUMBER      : v1..0.1                          
    REVISION DATE        : 05/10/2022         
    CREATED / REVISED BY : palani kumar (palanikumar@niyatainfoteh.com)      
    DESCRIPTION          : Updated average speed calculation against SRD V1.1            
------------------------------------------------------------------------------------------------------------------------  
    REVISION NUMBER      :  v1.0.0                            
    REVISION DATE        : 04/12/2022        
    CREATED / REVISED BY : Balsubramaniyan (balasubramaniayan.s@niyatainfoteh.com)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! AVERAGE_SPEED_C */
