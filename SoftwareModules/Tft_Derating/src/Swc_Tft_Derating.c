/* @file FILE NAME */
#ifndef TFT_DERATING_C
#define TFT_DERATING_C

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
 *  File name                       : SWC_Tft_Derating.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent 
 *  Compilers supported             : J Link
 *  Platforms supported             : Platform Independent
 *  Description                     : This file contains implementations of TFT derating

 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/

#include "Swc_Tft_Derating.h"
#include "fsl_gpio.h"
#include "Cmp_Tasks.h"
#include "stdint.h"
#include "Interpolation.h"

/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
* @brief: This macro is used to Get the Demanded DC% from the Illumination Processing Unit
* @Unit:  DUTY CYCLE %
* @Resolution: 1 %
* @Range: 1 to 100 %
* @Applicability: Yes
* @Note: 50% is assumed, since Illumination Processing Unit is not ready as on today (9-June-2022)
*/
#define TFT_GET_ILLUMINATION_DUTY_CYCLE				 (50)

/*
* @brief: This macro is used to configure the Minimum Allowed Duty Cycle in the system 
* @Unit:  DUTY CYCLE %
* @Resolution: 1 %
* @Range: 1 to TFT_DERATING_MAX_DUTY_CYCLE-1 %
* @Applicability: Yes
* @Note:  
*/
#define TFT_MIN_DUTY_CYCLE                       (30)

/*
* @brief: This macro is used to configure the Maximum Allowed Duty Cycle in the system 
* @Unit:  DUTY CYCLE %
* @Resolution: 1 %
* @Range: 1 to 100 %
* @Applicability: Yes
* @Note:  
*/
#define TFT_DERATING_MAX_DUTY_CYCLE             (100u)

/*
* @brief: This macro is used to configure the FREQUENCY in the system 
* @Unit: HZ
* @Resolution: 1
* @Range: 200 to TBD
* @Applicability: Yes
* @Note:  
*/
#define TFT_DERATING_DEFAULT_FREQUENCY          (200u)

/*
* @brief: This macro is used to configure the Step Value of Computed Temperature 
* @Unit:  Degree C
* @Resolution: 1
* @Range: 1
* @Applicability: Yes
* @Note: 
*/
#define TFT_TEMPERATURE_GAIN                      (1)


/*
* @brief: This macro is used to configure the row size of the table 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: Yes
* @Note: 
*/
#define ROW_SIZE                      4

/*
* @brief: This macro is used to configure the table is ascending or descending
* @Unit:  
* @Resolution: 
* @Range: 0 or 1 ; 0 - Ascending, 1- Descending
* @Applicability: Yes
* @Note: 
*/
#define TABLE_CONFIG                     1

/*
* @brief: This macro is used to configure the Table [Computed ADC Vs Termperature %]
* @Unit:  
*                  Column 1 is in ADC
*                  Column 2 is in Temperature
* @Resolution: 1
* @Range:
*                  Column 1 is between 0 & 4000
*                  Column 2 is between 0 & 100
* @Applicability: Yes
* @Note: 
*/
#define ADC_VS_TEMPERATURE   		{   3020,                        0    },\
									{   667,                        75    },\
									{   591,                        80    },\
									{   524,                        85    }


/*
* @brief: This macro is used to configure the Table [Computed ADC Vs Termperature %]
* @Unit:  
*                  Column 1 is in ADC
*                  Column 2 is in Temperature
* @Resolution: 1
* @Range:
*                  Column 1 is between 0 & 4000
*                  Column 2 is between 0 & 100
* @Applicability: Yes
* @Note: 
*/
#define TEMP_VS_DUTY                	{   0,                         100    },\
										{   75,                        100    },\
										{   80,                        60    },\
										{   85,                        30    }


/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*
 * @brief: This variable is used to preserve the Pre-Condition
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: TRUE/FALSE
 * @Applicability: Yes
 */
boolean g_Precondition_Status_bool;

/*
 * @brief: This variable is used to get the Demanded Duty Cycle from Illumination Processing
 * @Unit:  Duty Cycle %
 * @Resolution: 1
 * @Range: 0 to 100
 * @Applicability: Yes
 */
uint8_t g_Demanded_DutyCycle_u8;

/*
 * @brief: This variable is used to get the Backlight TFT temperature 
 * @Unit:  COUNT
 * @Resolution: 1
 * @Range: 1 to 1024 (8 bit ADC)
 * @Applicability: Yes
 */
uint16_t g_BKLT_Temperature_Celcius_ADC_u16;

/*
 * @brief: This variable is used to preserve the computed PWM Duty Cycle
 * @Unit:  DC %
 * @Resolution: 1
 * @Range: 1 TO 100
 * @Applicability: Yes
 */
uint8_t g_Recommended_Pwm_DutyCycle_u8;

/*
 * @brief: This variable is used to preserve the Ouptut PWM Duty Cycle
 * @Unit:  DC %
 * @Resolution: 1
 * @Range: 1 TO 100
 * @Applicability: Yes
 */
uint8_t g_PWM_Output_Duty_Cycle_u8;

/*
 * @brief: This variable is used to preserve the Output PWM Frequency
 * @Unit:  Hz
 * @Resolution: 1
 * @Range: 1 to 2000
 * @Applicability: Yes
 */
uint16_t g_PWM_Output_Frequency_u16;

/*
 * @brief: This variable is used to preserve the duty cycle
 * @Unit:  %
 * @Resolution: 
 * @Range: 0 to 100
 * @Applicability: Yes
 */
uint16_t g_Tft_Duty_u32;

/*
 * @brief: This variable is used to preserve the temperature value
 * @Unit:  degree
 * @Resolution: 
 * @Range: 0 to 85
 * @Applicability: Yes
 */
uint16_t g_Tft_Value_Celcius_u32;

/*
 * @brief: This variable is used to preserve the temperature value from ADC vs temperature mapping table
 * @Unit:  degree
 * @Resolution: 
 * @Range: 0 to 85
 * @Applicability: Yes
 */
uint16_t g_Get_Mapp_Value_u16;

/*
 * @brief: This variable is used to preserve the recommended temperature
 * @Unit:  degree
 * @Resolution: 
 * @Range: 0 to 85
 * @Applicability: Yes
 */
uint16_t g_Recommended_Pwm_u16;

/*
 * @brief: This variable is used to preserve the recommended temperature
 * @Unit:  degree
 * @Resolution: 
 * @Range: 0 to 85
 * @Applicability: Yes
 */
uint16_t g_Recommended_Temp_u16;

/*
 * @brief: This variable is used to preserve the temperature
 * @Unit:  degree
 * @Resolution: 
 * @Range: 0 to 85
 * @Applicability: Yes
 */
static uint16_t ADC_Vs_Temperature_u16[4][2] = {ADC_VS_TEMPERATURE};

/*
 * @brief: This variable is used to preserve the recommended Duty
 * @Unit:  degree
 * @Resolution: 
 * @Range: 0 to 85
 * @Applicability: Yes
 */
static uint16_t TFT_Temperature_Vs_DutyCycle_u16[4][2] = {TEMP_VS_DUTY};

/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    This function processes the 
 * @param    
 * @return   
 */

/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/

/* To initialize the  function to be called in the main function*/
void Tft_Derating_Init(void)
{
  g_Precondition_Status_bool = FALSE;

  g_Demanded_DutyCycle_u8 = 0;

  g_BKLT_Temperature_Celcius_ADC_u16 = 0;

  g_Recommended_Pwm_DutyCycle_u8 = 0;
  
  g_PWM_Output_Duty_Cycle_u8 = 50;
  
  g_PWM_Output_Frequency_u16 = TFT_DERATING_DEFAULT_FREQUENCY;
}
 
/* API is used To reset the  function to be called in the main function */
void Tft_Derating_DeInit(void)
{
      /* do nothing */  
}

/* API is used To activate the  peripherals*/
void Tft_Derating_Active(void)
{
    /* do nothing */    
}

/* API is used To reset the peripherals of the system */
void Tft_Derating_DeActive(void)
{
    /* do nothing */    
}

/*Voltage Battery */
void Tft_Derating_MainFunction(void)
{
   bool fl_Tft_Derating_Pre_Condition_state = FALSE;

   uint16_t fl_TFT_Illumination_Duty_16;

   uint32_t fl_Tft_Temp_New_u32;

   uint32_t fl_Tft_Temp_u32;

   fl_TFT_Illumination_Duty_16 = TFT_GET_ILLUMINATION_DUTY_CYCLE;

   fl_Tft_Derating_Pre_Condition_state = Tft_Derating_Pre_Condition();

   if(fl_Tft_Derating_Pre_Condition_state == TRUE)
   {
	   //fl_Tft_Temp_New_u32 = Al_BKLT_TEMP_MONITOR();

      if(fl_Tft_Temp_New_u32 > fl_Tft_Temp_u32)
      {
        // fl_Tft_Temp_u32 = fl_Tft_Temp_u32 + GAIN;

         g_Recommended_Temp_u16 = TFT_Derating_ADC_VS_Temperature_Mapping(&ADC_Vs_Temperature_u16[0][0], fl_Tft_Temp_u32, ROW_SIZE);

         g_Recommended_Pwm_u16 = TFT_GET_ILLUMINATION_DUTY_CYCLE;
      }
      else
      {
         if(fl_Tft_Temp_New_u32 < fl_Tft_Temp_u32)
         {
      //   fl_Tft_Temp_u32 = fl_Tft_Temp_u32 - GAIN;
         g_Recommended_Pwm_u16 = TFT_GET_ILLUMINATION_DUTY_CYCLE;
         }
         else
         {
           g_Recommended_Pwm_u16 = TFT_GET_ILLUMINATION_DUTY_CYCLE;
         }
      }
   }
   else
   {
      /* do nothing */
   } 

} 

/* API is used To check the all pre condition elements such as ign on/off LVSD/HVSD */
bool Tft_Derating_Pre_Condition(void)
{
   bool fl_Precondition_Status = FALSE;

   uint8_t fl_Ign_Position_u8;
   uint8_t fl_Tft_Derating_LVSD_check_u8;
   uint8_t fl_Tft_Derating_HVSD_check_u8;
   uint16_t fl_Al_Blink_Temp_Mon_u8;
   
   //fl_Al_Blink_Temp_Mon_u8 = AL_BKLT();

   fl_Ign_Position_u8 = Sys_Service_Get_Ignition_State();

   fl_Tft_Derating_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

   fl_Tft_Derating_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

  if((fl_Ign_Position_u8 == IGN_OFF)  || (fl_Tft_Derating_LVSD_check_u8 == 0) ||
      (fl_Tft_Derating_HVSD_check_u8 == 0) || (fl_Al_Blink_Temp_Mon_u8 == 0))
  {
	  g_Precondition_Status_bool = FALSE;
  }
  else
  {
	  g_Precondition_Status_bool = TRUE;
  }

  return g_Precondition_Status_bool;
}

/* API is used To get duty cycle value for TFT derating*/
uint16_t Tft_Derating_Get_Duty_Cycle(uint16_t fl_TFT_Temperature_value_u16)
{
   g_Tft_Value_Celcius_u32 = fl_TFT_Temperature_value_u16;

   if (g_Tft_Value_Celcius_u32 >= 0 && g_Tft_Value_Celcius_u32 <= 75)
   {
      /*TFT Derating will be depends upon the ambient sensor*/
      /*g_Tft_Duty_u32 = 100;*/
      g_Tft_Duty_u32 = TFT_GET_ILLUMINATION_DUTY_CYCLE;

   }
   else if (g_Tft_Value_Celcius_u32 > 75)
   {
      g_Tft_Duty_u32 = Interpolation_Handler(g_Tft_Value_Celcius_u32, &TFT_Temperature_Vs_DutyCycle_u16[0][0], ROW_SIZE,TABLE_CONFIG);

   }
   else
   {
      /* do nothing */
   }
   return g_Tft_Duty_u32; 
}

/* API is used To map the ADS and temperature */
uint16_t TFT_Derating_ADC_VS_Temperature_Mapping(uint16_t *ADC_Vs_Temperature_data_u16, uint16_t data_from_table_u16, uint16_t fl_table_size_u16 )
{
   uint8_t fl_index_u8;
	for(fl_index_u8 = 0; fl_index_u8 < fl_table_size_u16; fl_index_u8++)
    {
        if(data_from_table_u16 == *ADC_Vs_Temperature_data_u16)
        {
           g_Get_Mapp_Value_u16 =  *(++ADC_Vs_Temperature_data_u16);
           break;
        }

        else
        {
            g_Get_Mapp_Value_u16 = *ADC_Vs_Temperature_data_u16 + 2u;
        }
    }
	return g_Get_Mapp_Value_u16;
}
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0
    REVISION DATE        : MONTH/DATE/YEAR        
    CREATED / REVISED BY : Balsubramaniyan (balasubramaniayan.s@niyatainfoteh.com)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! SWS_TFT_DERATING_C*/
