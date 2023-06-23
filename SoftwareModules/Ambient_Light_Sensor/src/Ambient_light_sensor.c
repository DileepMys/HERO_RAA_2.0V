/* @file FILE NAME */
#ifndef AMBIENT_LIGHT_SENSOR_C
#define AMBIENT_LIGHT_SENSOR_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Jeevajothi (jeevajothi@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : Ambientlight_sensor.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : Compiler Independent
 *  Platforms supported             : Platform Independent
 *  Description                     : This file consists of defALS_initialization_send_statusions of luminance value defALS_initialization_send_statusion
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "Ambient_light_sensor.h"
#include "Swc_System_Service.h"
#include "OPT3001_driver.h"
#include "CanMgr_cfg.h"
/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                     
***********************************************************************************************************************/
#include "fsl_lpi2c.h"
#include "fsl_debug_console.h"


/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*
* @brief This macro is used to define Zero luminance value
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/
#define INVALID 0XFFFF
 

/***********************************************************************************************************************
 *                                          G L O B A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to get the lux sample  
 * @Unit:  
 * @Resolution: 0.01
 * @Range: 0-10
 * @Applicability: Samples are taken from I2C sensor  
 */
 uint8_t g_Lux_Samples_u8;  

 /*
 * @brief: This variable is used to find the average lux after the  accumulate 
 * @Unit:  
 * @Resolution: 1
 * @Range: 
 * @Applicability: This variable is used to find the luminance value from average  sample 
 */
 uint16_t g_Lux_Sum_u16; 

  /*
 * @brief: This variable is used to send the ambient data to CAN Tx
 * @Unit:  nil
 * @Resolution: 0
 * @Range: nil
 * @Applicability: NA
 */
static uint8_t g_CAN_Tx_Ambient_data_u8;

   /*
 * @brief: This variable is used to  find the luminance value which is used to check the day/night condition
 * @Resolution: 1
 * @Range: 0-2000
 * @Applicability: Variable is used to determine the day/night mode status
 */
static uint16_t g_Luminance_Value_u16;

  /*
 * @brief: This variable is used to  find the day/night mode status based on the luminance value
 * @Unit:  n/a
 * @Resolution: 
 * @Range: NA
 * @Applicability:  determine the day or night state
 */
 static uint8_t g_Day_night_mode_status_u8;
 
    /*
 * @brief: This variable is used to  update the timer value 
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
 static uint16_t g_update_timer_u16;
 
   /*
 * @brief: This variable is used to  update the ALS initialization status whether its done or not done 
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
 bool g_ALS_initial_sample_done_status_bl;


   /*
 * @brief: This variable is used to get the ignition position status
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */ 
uint8_t g_ALS_Ign_Position_u8;

   /*
 * @brief: This variable is used to get the low voltage state of the ALS system
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
uint8_t g_ALS_LVSD_check_u8;

   /*
 * @brief: This variable is used to get the Voltage voltage state of the ALS system
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
uint8_t g_ALS_HVSD_check_u8;

  /*
 * @brief: This variable is used to debounce the day night mode 
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
uint16_t g_Day_night_Debounce_timer_u16;

 /*
 * @brief:check previous condition states such as ign,LVSD/HVSD from the function if it false it goes off condition 
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
bool g_pre_condition_Status;


/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/

/* Initialize the values for the init variables */
void I2C_Ambient_Sensor_Init(void)
{ 
	/* SET VALUE TO THE DEFAULT VALUE */
	g_Day_night_Debounce_timer_u16 = ALS_UPDATE_TIME_PRIMARY_MS;
	g_ALS_initial_sample_done_status_bl = FALSE;
	g_Luminance_Value_u16 = 0.00;
	g_Day_night_mode_status_u8 = NIGHT;
	g_CAN_Tx_Ambient_data_u8 = NIGHT;
	g_Lux_Samples_u8 = 0;
	g_Lux_Sum_u16 = 0;
}

void I2C_Ambient_Sensor_De_Init(void)
{
        /* do nothing */
}

/* check ambient light precondition to find the luminance value and day/night mode status*/
boolean ALS_Pre_Condition_check(void)
{

	/* check previous condition states such as ign,LVSD/HVSD * from the function if it false it goes off condition */
	bool g_pre_condition_Status = FALSE;



	g_ALS_Ign_Position_u8 = ALS_GET_IGN_POSITION;
	g_ALS_LVSD_check_u8 = ALS_GET_LOW_VOLTAGE_STATE;
	g_ALS_HVSD_check_u8 = ALS_GET_HIGH_VOLTAGE_STATE;

	/* check condition for ignition position and low/high power state of the ALS system */
    if((g_ALS_Ign_Position_u8  == IGN_ON) && \
   	  (g_ALS_LVSD_check_u8 != SYSTEM_SERVICE_NORMAL_VOLTAGE) &&\
	  (	g_ALS_HVSD_check_u8 != SYSTEM_SERVICE_NORMAL_VOLTAGE))

	{
	   /* If the pre condition is true then calculate the luminanca value else returned to off state */
    	g_pre_condition_Status = TRUE;
	}

   return g_pre_condition_Status;
}
/*  function is used to calculate the luminance value from I2C Sensor based on this lux value can find the day/night mode state */
float Sensor_Read_Luminance_value(void)
{	
	float fl_i2c_sensor_value_f = 0;
	 fl_i2c_sensor_value_f =  I2C_Sensor_value_lux_conversion();	
	return fl_i2c_sensor_value_f;
}

void ALS_Mainfunction(void)
{
	/*  function is used to accumulate sample and calculate the luminance value based on the I2C sensor O/P value */
	 ALS_Accumulate_Sample_Process();

	/*  function is used to get day or nighr mode status from the luminance value */
	 ALS_Get_Day_Night_Mode_Info();

	/*  function  is used to provide ambient data information as a parameter to the CAN Tx */
	CanMgr_Write_ambiant_light_data_0x321_s((uint8_t)g_CAN_Tx_Ambient_data_u8);
	
}
void ALS_Accumulate_Sample_Process(void)
{

	 uint16_t fl_Lux_Normalized_Raw_u16 = 0;
	 float fl_Lux_Raw_Input_f = 0;


	 /* check whether the pre condition is true or not,if not it goes to off state */
	g_pre_condition_Status = ALS_Pre_Condition_check();

	if(g_pre_condition_Status == TRUE)
	{
		/* get lux raw input value from I2C sensor */
		fl_Lux_Raw_Input_f = Sensor_Read_Luminance_value();

		/* calculate this float raw input value into whole integer value */
		fl_Lux_Normalized_Raw_u16 = fl_Lux_Raw_Input_f * ALS_RESOLUTION_FACTOR;
		
		if(g_ALS_initial_sample_done_status_bl == TRUE)
		{
			if(g_Lux_Samples_u8 > LUX_AVG_SAMPLE)
			{
				g_Luminance_Value_u16 = ((fl_Lux_Normalized_Raw_u16 + 
										(g_Luminance_Value_u16 * (LUX_AVG_SAMPLE - 1)))/
										LUX_AVG_SAMPLE);
				g_Lux_Samples_u8 = 0;
			}

			else if(g_Lux_Samples_u8 == LUX_AVG_SAMPLE ) 
			{		
				g_Luminance_Value_u16 = g_Lux_Sum_u16 / LUX_AVG_SAMPLE;	
				g_Lux_Sum_u16 = 0;
				g_Lux_Samples_u8++;
			}

			else
			{
				g_Lux_Sum_u16 = g_Lux_Sum_u16 + fl_Lux_Normalized_Raw_u16;

				g_Lux_Samples_u8++;
			}
		}

		else 
		{
			if(g_Lux_Samples_u8 > LUX_AVG_INIT_SAMPLE)
			{
				g_Luminance_Value_u16 = (fl_Lux_Normalized_Raw_u16 +
									(g_Luminance_Value_u16 *(LUX_AVG_INIT_SAMPLE-1)))/
									LUX_AVG_INIT_SAMPLE;
				g_Lux_Sum_u16 = g_Lux_Sum_u16 + fl_Lux_Normalized_Raw_u16;
				g_Lux_Samples_u8 = 0;
			}

			else if(g_Lux_Samples_u8 == LUX_AVG_INIT_SAMPLE)
			{
				g_Luminance_Value_u16 = g_Lux_Sum_u16 / LUX_AVG_INIT_SAMPLE;
				g_Lux_Sum_u16 = 0;
				g_Lux_Samples_u8++;
			}
			
			else
			{
								
				g_Lux_Sum_u16 = g_Lux_Sum_u16 + fl_Lux_Normalized_Raw_u16;

				g_Lux_Samples_u8++;	
			}
		}
	}

}
		
uint8_t ALS_Get_Day_Night_Mode_Info(void)
{
	/* if the condition is true it follow the below condition check else it goes to default night mode */
	if(g_ALS_Ign_Position_u8  == IGN_ON)
	{
		/* if LVSD/HVSD gets condition true check the following condition else it maintain the previous state mode*/
		if((g_ALS_LVSD_check_u8 != SYSTEM_SERVICE_NORMAL_VOLTAGE) &&
			(g_ALS_HVSD_check_u8 != SYSTEM_SERVICE_NORMAL_VOLTAGE))
		{
			if (g_Luminance_Value_u16 != INVALID)
			{
				if(g_Day_night_Debounce_timer_u16 == 0)
				{
					g_ALS_initial_sample_done_status_bl = TRUE;

					g_Day_night_Debounce_timer_u16  = ALS_UPDATE_TIME_SECONDARY_MS;

					if(g_Luminance_Value_u16 < ALS_LUX_NIGHT_THRESHOLD )
					{
						g_Day_night_mode_status_u8 = NIGHT;
					
						g_CAN_Tx_Ambient_data_u8 = NIGHT;
					}
					else if(g_Luminance_Value_u16 > ALS_LUX_DAY_THRESHOLD )
					{
						g_Day_night_mode_status_u8 = DAY;
						g_CAN_Tx_Ambient_data_u8 = DAY;
					}
					else
					{
					/*DO NOTHING */	
					}
					return g_Day_night_mode_status_u8;
				}
				else
				{	
					g_Day_night_Debounce_timer_u16--;
				}
			}
			else
			{
				g_Day_night_mode_status_u8 = NIGHT;
				
				g_CAN_Tx_Ambient_data_u8 = NIGHT;
			}	
		}
		else
		{
			/* To maintain previous state*/				
		}
	}
	else
	{
		g_Day_night_mode_status_u8 = NIGHT;
		
		g_CAN_Tx_Ambient_data_u8 = NIGHT;
	}

}

uint16_t Swc_ALS_Get_Luminance_Value(void)
{
	return (g_Luminance_Value_u16);
}

uint8_t Test_debug_mode = 1;

uint8_t Get_day_night_mode_status(void)
{
	// return Test_debug_mode;
	return (g_Day_night_mode_status_u8);
}


/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : Major.Minor.Patch                          
    REVISION DATE        : MONTH/DATE/YEAR        
    CREATED / REVISED BY : NAME (EMAIL-ID)      
    DESCRIPTION          : ALS_initialization_send_statusial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! FILE NAME */
