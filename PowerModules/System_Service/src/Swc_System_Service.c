/* @file FILE NAME */
#ifndef SYSTEM_SERVICE_C
#define SYSTEM_SERVICE_C

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
 *  File name                       : System service.c
 *  Version                         : V1.0.3
 *  Micros supported                : 
 *  Compilers supported             :
 *  Platforms supported             : 
 *  Description                     : This file contains implementations of System services

 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/

#include "Fuel_Guage.h"
#include "TC.h"
#include "Swc_Odometer.h"
#include "Swc_Service_Remainder.h"
#include "stdint.h"
#include "Cmp_Init.h"
#include "fsl_gpio.h"
#include "fsl_flexcan.h"
#include "Cmp_Tasks.h"
#include "fsl_lpadc.h"
#include "I2C_Handler.h"
#include "clock_config.h"
#include "Swc_System_Service.h"
#include "Swc_Trip_Timer.h"
#include "task.h"
#include "Swc_TFT_Illum.h"
#include "fsl_pwm.h"
#include "core_cm7.h"
#include "fsl_lpi2c.h"
#include "fsl_wdog.h"
#include "Dio_Handler.h"
#include "fsl_elcdif.h"
#include "Interpolation.h"
#include "lvgl_app.h"
#include "HMI_GUI_Interface.h"
#include "UdsApp.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/
#define DEMO_LPADC_USER_CMDID   2U /* CMD1 */
#define DEMO_LPADC_VREF_SOURCE  kLPADC_ReferenceVoltageAlt1

#define POWER_LPADC_USER_CHANNEL 2U

/*
* @brief: This macro is used to configure value which will be stored in SNVS LP GPR register to differentiate cold and warm init
 * @Unit:  uint32_t
 * @Resolution: 1
 * @Range: 0x0000 - 0xFFFF
 * @Applicability:  Used in sleep entry and cold init detection 
*/
#define SNVS_LP_GPR_VALUE 0xAA22
#define  VOLTAGE_HYSTERSIS_LOW    0

#define  VOLTAGE_HYSTERSIS_HIGH    0

/* Low voltage entry condition i.e., 7.5v */
#define VOLTAGE_BATT_LOW_THRSHOLD  241

/* low voltage recovery voltage 8v */
#define VOLTAGE_BATT_LOW_RECOVERY  259

/* High voltage recovery voltage 16.5v */
#define VOLTAGE_BATT_HIGH_THRSHOLD  568

/* High voltage recovery voltage 16v */
#define VOLTAGE_BATT_HIGH_RECOVERY  550

/*
* @brief: This variable is used to configure 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:
*/

/*#define SWC_SYSTEM_SERVICE_GET_VBATT()        NULL*/


#define ADC_VALUES_IDEX                     25

/*
* @brief: This variable is used to configure OFFSET value to added to raw battery voltage value
* @Unit:  
* @Resolution: 0.1v
* @Range: 
* @Applicability: 
* @Note:
*/
#define BATTERY_VOLTAGE_OFFSET        0


/*
* @brief: This variable is used to configure sleep entry counter value to enter into SNVS
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:
*/
#define SLEEP_ENTRY_TIMER       15

/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/


uint16_t BATTERY_ADC_RAW[ADC_VALUES_IDEX] 	 = {187,205,223,241,259,277,296,314,332,350,368,386,405,423,441,459,477,495,513,532,550,568,589,604,622};

uint16_t BATTERY_ADC_ACTUAL[ADC_VALUES_IDEX] = {180,200,215,233,250,268,285,304,321,338,355,373,390,407,423,441,461,479,495,513,530,548,564,580,622};

const uint16_t MCU_Volt_To_Batt_Volt_Map_Table[ADC_VALUES_IDEX + 1][2] = 
{
  /* mcu volt(0.001v)   battery volt (0.001v)*/
  {		328	,	 1094},
  {		328	,	 6000},
  {		360	,	 6500},
  {		392	,	 7000},
  {		424	,	 7500},
  {		456	,	 8000},
  {		488	,	 8500},
  {		519	,	 9000},
  {		552	,	 9500},
  {		583	,	10000},
  {		615	,	10500},
  {		647	,	11000},
  {		679	,	11500},
  {		711	,	12000},
  {		743	,	12500},
  {		775	,	13000},
  {		809	,	13500},
  {		839	,	14000},
  {		871	,	14500},
  {		903	,	15000},
  {		935	,	15500},
  {		966	,	16000},
  {		998	,	16500},
  {		1030	,	17000},
  {		1062	,	17500},
  {		1094	,	18000}

};

/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

uint8_t g_Read_IGN_St;

/*
 * @brief    This typedef enum is used to define for Voltage variation
 * @param    
 * @param
 **/

System_Service_State_Type_En g_System_Service_State_u8;

/*
 * @brief: This variable is used to LVSD
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */


uint8_t g_Low_Vge_Shutdown_Flag_u8;

/*
 * @brief: This variable is used to HVSD
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

uint8_t g_High_Vge_Shutdown_Flag_u8;

/*
 * @brief: This variable is used to Low Threshold
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

const uint8_t  g_Voltage_Batt_Low_Thrsh_u8;

/*
 * @brief: This variable is used to High Threshold
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

const uint8_t g_Voltage_Hystersis_Low_u8;

/*
 * @brief: This variable is used to Battery High Threshold
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

const uint8_t g_Voltage_Batt_High_Thrsh_u8;

/*
 * @brief: This variable is used to g_Sys_Service_ignition_status_u8
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

uint8_t  g_Sys_Service_ignition_status_u8;

/*
 * @brief: This variable is used to read value in snvs general purpose register
 * @Unit:  uint32_t
 * @Resolution: 1
 * @Range: 0x0000 - 0xFFFF
 * @Applicability: 
 */
uint32_t g_Data_In_SNVS_GPR_u32;

uint8_t g_Read_IGN_St;

uint8_t g_Ign_LCD_OFF = 2;

uint8_t g_Do_Bklt_En_u8 = 2;

uint8_t g_Do_TFT_En_u8 = 2;

uint8_t g_Do_Can_En_u8 = 2;

uint8_t g_Do_5v_En_u8 = 2;

uint8_t g_Do_Switch_Batt_En_u8 = 2;

uint8_t g_SBatt_ctrl_Mcuout_u8 = 2;

uint8_t g_Illum_Pwm_En_u8 = 2;

uint8_t g_Batt1_MainFiltered_Sw_En_u8 = 2;

gpio_pin_config_t s_batt_filter_st;

uint32_t g_Sys_Service_ADCResult_u32;
uint32_t g_Sys_Service_ADCResult_Prev_u32;
uint32_t g_Sys_Service_ADCResult_Crnt_u32;

uint32_t g_Sys_Service_Voltage_u32;

uint32_t g_BATT_ADC_Val_u32;

uint8_t g_Sys_Service_Status;

static uint16_t g_HV_ADC_Sample_Index_u16_ch1;

static uint8_t g_LowFuel_Status = 0;
static uint32_t g_FuelSensorVoltage_u32 = 0u;
static uint32_t g_FuelSensorADCResult_u32 = 0u;

static uint16_t g_HV_ADC_Sample_u16_ch1[10] = {0,0,0,0,0,0,0,0,0,0};

static const uint32_t g_LpadcFullRange   = 4096U;
static const uint32_t g_LpadcResultShift = 3U;

uint8_t g_Is_Ignition_OFF_to_ON_u8;

uint32_t g_ActualVoltage_u32;

uint32_t g_Batt_Voltage_u32;

bool g_Sys_Ready_Status_bl;

bool g_Sys_BootUp_Compl_st;

Hero_RAAA_System_State_en g_System_Current_State_en;

const TickType_t xDelay = 100 / portTICK_PERIOD_MS;
const TickType_t x_200ms_Delay = 200 / portTICK_PERIOD_MS;
uint32_t regPrimask;

bool Sys_Reset_Flag;

uint8_t g_debug_var = 1;

bool g_Normal_To_Sleep_Trans_Status_bl = FALSE;

uint8_t g_Sleep_Entry_Counter;

uint8_t g_Current_IGN_St_u8;

uint8_t g_Previous_IGN_State_u8;

bool g_Sleep_NVM_Completion_Status;

extern bool g_Animation_Comp_Status;

extern uint32_t g_CurrentScreen_U32;

bool g_LVGL_Suspend_BL = FALSE;

lv_disp_drv_t *disp;

SLEEP_NVM_WRITE_CBK_ST SLEEP_NVM_WRITE_CBK_CFG[6] = 
{
	{&Swc_Odo_CM_NVM_Write},
	{&Swc_TripA_Timer_NVM_Write},
	{&Swc_TripB_Timer_NVM_Write},
	{&Swc_AFE_Writesync},
	{&Swc_DTE_Writesync},
	{&Fuel_Gauge_NVM_Write}
};

bool g_Initial_ADC_Sampling_Is_Done ;
/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    This function processes the 
 * @param    
 * @return   
 */
static void Sys_Service_Process_Ready_Status(void);

static void Sys_Service_Illum_control(uint8_t pwm_duty);
/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/* To initialize the ADC function to be called in the main function*/
void System_Service_Init(void)
{

   g_Read_IGN_St = IGN_OFF;

   g_Is_Ignition_OFF_to_ON_u8 = FALSE;

    g_Low_Vge_Shutdown_Flag_u8 = SYSTEM_SERVICE_SET;

	/* INIT ADC STATE */
   g_System_Service_State_u8 = SYSTEM_SERVICE_NORMAL_VOLTAGE;

    g_High_Vge_Shutdown_Flag_u8 = SYSTEM_SERVICE_SET;

	g_Sys_Ready_Status_bl = FALSE;

	g_Sys_BootUp_Compl_st = FALSE;

	g_System_Current_State_en = RAAA_SYSTEM_IN_NORMAL;

	Sys_Reset_Flag = FALSE;

	g_Sleep_Entry_Counter = 0;

	g_Current_IGN_St_u8 = 0;

	g_Previous_IGN_State_u8 = 0;

	/* initialize sleep nvm status as false */
	g_Sleep_NVM_Completion_Status = FALSE;

	g_Initial_ADC_Sampling_Is_Done = FALSE;

}
 
void System_Service_Deint(void)
{

}

void System_Service_MainFunction(void)
{
		bool fl_Comp_Status = FALSE;
   Sys_Service_Process_Ignition_State();

	if(g_System_Current_State_en == RAAA_SYSTEM_IN_NORMAL)
	{
		Sys_Service_Process_Ready_Status();
	}

 /* pre conditon check */
 switch(g_System_Service_State_u8)
	{
		 /*Voltage check for System Service*/
    case SYSTEM_SERVICE_NORMAL_VOLTAGE:

        g_Low_Vge_Shutdown_Flag_u8 = SYSTEM_SERVICE_NOT_SET;

        g_High_Vge_Shutdown_Flag_u8 = SYSTEM_SERVICE_NOT_SET;
		 
		/* Check LVGL Task is Suspend & Resume the LVGL Task*/

		if (g_LVGL_Suspend_BL == TRUE)
		{			
			Lvgl_task_Resume();
			g_LVGL_Suspend_BL = FALSE;
		}
		else
		{
			/* Do Nothing */
		}
		
		TFT_Backlight_Enable();

        if((g_Sys_Service_ADCResult_u32) < (VOLTAGE_BATT_LOW_THRSHOLD - VOLTAGE_HYSTERSIS_LOW))
        {
           g_Low_Vge_Shutdown_Flag_u8 = SYSTEM_SERVICE_SET;

            g_System_Service_State_u8 = SYSTEM_SERVICE_LOW_VOLTAGE;
        } 
         else if((g_Sys_Service_ADCResult_u32) > (VOLTAGE_BATT_HIGH_THRSHOLD + VOLTAGE_HYSTERSIS_HIGH))
        {
          g_High_Vge_Shutdown_Flag_u8 = SYSTEM_SERVICE_SET;

           g_System_Service_State_u8 = SYSTEM_SERVICE_HIGH_VOLTAGE;
        }
		else
		{
			/*do nothing*/
		}

    break;

    case SYSTEM_SERVICE_HIGH_VOLTAGE:

		if((g_Sys_Service_ADCResult_u32) <= VOLTAGE_BATT_HIGH_RECOVERY)
		{
			g_High_Vge_Shutdown_Flag_u8 = SYSTEM_SERVICE_NOT_SET;

			g_System_Service_State_u8 = SYSTEM_SERVICE_NORMAL_VOLTAGE;

		}
		else
		{

			if(g_Initial_ADC_Sampling_Is_Done == TRUE)
			{
				if (g_LVGL_Suspend_BL == FALSE)
				{
					SuspendLVGL_ClearBuffer();
				}
				else
				{
					/* Do Nothing */
				}
				TFT_Backlight_Disable();

			}

		}
	
    break;

    case SYSTEM_SERVICE_LOW_VOLTAGE:

        if((g_Sys_Service_ADCResult_u32) >= VOLTAGE_BATT_LOW_RECOVERY)
        {
           g_Low_Vge_Shutdown_Flag_u8 = SYSTEM_SERVICE_NOT_SET;

           g_System_Service_State_u8 = SYSTEM_SERVICE_NORMAL_VOLTAGE;
		
        }
		else
		{
			if(g_Initial_ADC_Sampling_Is_Done == TRUE)
			{
				if (g_LVGL_Suspend_BL == FALSE)
				{
					SuspendLVGL_ClearBuffer();
				}
				else
				{
					/* Do Nothing */
				}
				TFT_Backlight_Disable();

			}

		} 

    break;

    default :
      /*Do Nothing */
    break;
	}
    WDOG_Refresh(WDOG1);
}



void fsl_System_Service_lpadc_Periodic_Task(void *pvparameters)
{
	lpadc_config_t mLpadcConfigStruct_ss;
	lpadc_conv_trigger_config_t mLpadcTriggerConfigStruct_ss;
	lpadc_conv_command_config_t mLpadcCommandConfigStruct_ss;
	lpadc_conv_result_t mLpadcResultConfigStruct_ss;
	uint32_t fl_Actual_Converter_Value_U32 = 0;
	uint32_t fl_Averaged_Converter_Value_U32 = 0;
	uint32_t fl_Avg_Delta_Hyst_u32 = 0;
	uint32_t fl_Batt_Volt_Interpolated_value_u32 = 0;
	uint32_t fl_Batt_Volt_u32 = 0;


	TickType_t xLastWakeTime;
 	TickType_t xFrequency = pdMS_TO_TICKS(25);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();



	LPADC_GetDefaultConvCommandConfig(&mLpadcCommandConfigStruct_ss);

	mLpadcCommandConfigStruct_ss.channelNumber = POWER_LPADC_USER_CHANNEL;


	mLpadcCommandConfigStruct_ss.sampleChannelMode = kLPADC_SampleChannelSingleEndSideA;


	LPADC_SetConvCommandConfig(DEMO_LPADC_BASE, DEMO_LPADC_USER_CMDID, &mLpadcCommandConfigStruct_ss);
	LPADC_GetDefaultConvTriggerConfig(&mLpadcTriggerConfigStruct_ss);

	mLpadcTriggerConfigStruct_ss.targetCommandId       = DEMO_LPADC_USER_CMDID;

	mLpadcTriggerConfigStruct_ss.enableHardwareTrigger = false;
	LPADC_SetConvTriggerConfig(DEMO_LPADC_BASE, 1U, &mLpadcTriggerConfigStruct_ss);
	

	       
	      


	while (1)
	    {
			xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
			
	        //GETCHAR();
	        LPADC_DoSoftwareTrigger(DEMO_LPADC_BASE, 1<<1); /* 1U is trigger1 mask. */
	        while (!LPADC_GetConvResult(DEMO_LPADC_BASE, &mLpadcResultConfigStruct_ss));

			fl_Actual_Converter_Value_U32 = ((mLpadcResultConfigStruct_ss.convValue) >> g_LpadcResultShift);


	        /* Moving Average calculation for Digital Data for channel 0 */
	                 if (g_HV_ADC_Sample_Index_u16_ch1 < 10)
	                 {
						/* battery voltage adc initial sampling is in progress*/
						g_Initial_ADC_Sampling_Is_Done = FALSE;

	                	 g_HV_ADC_Sample_Index_u16_ch1++;
	                     g_HV_ADC_Sample_u16_ch1[g_HV_ADC_Sample_Index_u16_ch1] = (uint16_t)fl_Actual_Converter_Value_U32;
	                 }
	                 else
	                 {
						/* battery voltage adc initial sampling is done*/
						g_Initial_ADC_Sampling_Is_Done = TRUE;

	                	 /* Move the data for every sample */
	                     g_HV_ADC_Sample_u16_ch1[0] = g_HV_ADC_Sample_u16_ch1[1];
	                     g_HV_ADC_Sample_u16_ch1[1] = g_HV_ADC_Sample_u16_ch1[2];
	                     g_HV_ADC_Sample_u16_ch1[2] = g_HV_ADC_Sample_u16_ch1[3];
	                     g_HV_ADC_Sample_u16_ch1[3] = g_HV_ADC_Sample_u16_ch1[4];
	                     g_HV_ADC_Sample_u16_ch1[4] = g_HV_ADC_Sample_u16_ch1[5];
	                     g_HV_ADC_Sample_u16_ch1[5] = g_HV_ADC_Sample_u16_ch1[6];
	                     g_HV_ADC_Sample_u16_ch1[6] = g_HV_ADC_Sample_u16_ch1[7];
	                     g_HV_ADC_Sample_u16_ch1[7] = g_HV_ADC_Sample_u16_ch1[8];
	                     g_HV_ADC_Sample_u16_ch1[8] = g_HV_ADC_Sample_u16_ch1[9];
	                     g_HV_ADC_Sample_u16_ch1[9] =  (uint16_t)fl_Actual_Converter_Value_U32;
	                 }
	   /* Once welcome animation is completed, then change the task periodicity to 100ms */
				if( HMI_Get_Welcome_Animation_Status() == WELCOME_ANIMATION_COMPLETED)
				{
					xFrequency = pdMS_TO_TICKS(100);
				}
				else
				{
                  /*do nothing*/
				}

	        fl_Averaged_Converter_Value_U32 = (g_HV_ADC_Sample_u16_ch1[0] +
	                                                 g_HV_ADC_Sample_u16_ch1[1] +
	                                                 g_HV_ADC_Sample_u16_ch1[2] +
	                                                 g_HV_ADC_Sample_u16_ch1[3] +
	                                                 g_HV_ADC_Sample_u16_ch1[4] +
	                                                 g_HV_ADC_Sample_u16_ch1[5] +
	                                                 g_HV_ADC_Sample_u16_ch1[6] +
	                                                 g_HV_ADC_Sample_u16_ch1[7] +
	                                                 g_HV_ADC_Sample_u16_ch1[8] +
	                                                 g_HV_ADC_Sample_u16_ch1[9] ) / 10;

			g_Sys_Service_ADCResult_u32 = (fl_Averaged_Converter_Value_U32 / 4);

			Get_Adc_Status();
	    
		   g_ActualVoltage_u32 = (g_Sys_Service_ADCResult_u32 * 18 * 1000) / 10230;

		   /* linear interpolation MCU Volt vs Battery volt*/
		   fl_Batt_Volt_Interpolated_value_u32 = LinearInterpolateWord((uint16_t*)&MCU_Volt_To_Batt_Volt_Map_Table[0][0],g_ActualVoltage_u32);

		   /* convert to 0.1v resolution*/
		   fl_Batt_Volt_u32 = fl_Batt_Volt_Interpolated_value_u32 / 100;

		   /* Add offset*/
		   g_Batt_Voltage_u32 = fl_Batt_Volt_u32 + BATTERY_VOLTAGE_OFFSET;
	    
	    }
}

void Get_Adc_Status(void)
{

	uint8_t fl_loop_index_u8;

	uint32_t fl_Actual_ADC_First_Row_u32;

	uint32_t fl_Actual_ADC_Second_Row_u32;

	uint32_t fl_Indicated_ADC_First_Row_u32;
	uint32_t fl_Indicated_ADC_Second_Row_u32;

	uint32_t fl_Actual_ADC_Delta_u32;
	uint32_t fl_Indicated_ADC_Delta_u32;

	/*selection process KMPH or MPH*/


	/* Table Boundary Verification */
	if (g_Sys_Service_ADCResult_u32 <= BATTERY_ADC_ACTUAL[0])
	{
		g_Sys_Service_ADCResult_u32 = BATTERY_ADC_RAW[0];

	}
	else if (g_Sys_Service_ADCResult_u32 >= BATTERY_ADC_ACTUAL[24])
	{
		g_Sys_Service_ADCResult_u32 = BATTERY_ADC_RAW[24];

	}
	else
	{

		for (fl_loop_index_u8 = 0; fl_loop_index_u8 < ADC_VALUES_IDEX; fl_loop_index_u8++)
		{
			fl_Actual_ADC_First_Row_u32 = BATTERY_ADC_ACTUAL[fl_loop_index_u8];
			fl_Actual_ADC_Second_Row_u32 = BATTERY_ADC_ACTUAL[fl_loop_index_u8 + 1];

			fl_Indicated_ADC_First_Row_u32 = BATTERY_ADC_RAW[fl_loop_index_u8];
			fl_Indicated_ADC_Second_Row_u32 = BATTERY_ADC_RAW[fl_loop_index_u8 + 1];

			if(g_Sys_Service_ADCResult_u32 == BATTERY_ADC_ACTUAL[fl_loop_index_u8])
			{
				g_Sys_Service_ADCResult_u32 = BATTERY_ADC_RAW[fl_loop_index_u8];

				break;
			}				  
			/* Linear Interpolation */
			else if ( (g_Sys_Service_ADCResult_u32 > fl_Actual_ADC_First_Row_u32) &&
			(g_Sys_Service_ADCResult_u32 < fl_Actual_ADC_Second_Row_u32) )
			{
				fl_Actual_ADC_Delta_u32 = fl_Actual_ADC_Second_Row_u32 - fl_Actual_ADC_First_Row_u32;
				fl_Indicated_ADC_Delta_u32 = fl_Indicated_ADC_Second_Row_u32 - fl_Indicated_ADC_First_Row_u32;

				g_Sys_Service_ADCResult_u32 = fl_Indicated_ADC_First_Row_u32 + ((float)(g_Sys_Service_ADCResult_u32 - fl_Actual_ADC_First_Row_u32)
														 / (float)fl_Actual_ADC_Delta_u32) * fl_Indicated_ADC_Delta_u32;

				break;
			}
			else
			{

			}

		}


	}

}

static void Sys_Service_Process_Ready_Status(void)
{

	if(Fuel_Gauge_Ready_Status() != FALSE)
	{

		g_Sys_Ready_Status_bl = TRUE;

		if(g_Sys_BootUp_Compl_st == FALSE)
		{

			g_Sys_BootUp_Compl_st = TRUE;

		}
	}
	else
	{
		g_Sys_Ready_Status_bl = FALSE;

		g_Sys_BootUp_Compl_st = FALSE;

	}

}

/*check High voltage flag */
uint8_t Sys_Service_Get_High_Voltage_State(void)
{

  return g_High_Vge_Shutdown_Flag_u8;
}



/*check Low voltage flag */
uint8_t Sys_Service_Get_Low_Voltage_State(void)
{

  return g_Low_Vge_Shutdown_Flag_u8;
}

/*Check Ignition state*/
uint8_t Sys_Service_Get_Ignition_State(void)
{
  
   return g_Sys_Service_ignition_status_u8;
    
}

bool Sys_Get_Ready_Status(void)
{
	return (g_Sys_Ready_Status_bl);
}


void Sys_Service_Process_Ignition_State(void)
{
  uint8_t i = 0;
  uint8_t fl_IGN_Status_u8 ;
  uint8_t fl_Current_pwm_Duty_u8;
  uint8_t fl_loop_Idx;

  g_Current_IGN_St_u8 = Dio_Handler_Read_Pin_Status();

  switch(g_System_Current_State_en)
  {
	case RAAA_SYSTEM_IN_NORMAL:

			if(g_Current_IGN_St_u8 == IGN_ON)
			{
				g_Sys_Service_ignition_status_u8 = IGN_ON;		

				g_Is_Ignition_OFF_to_ON_u8 = TRUE;
				
			} 
			else
			{
				/* Change state to limited mode */
				g_System_Current_State_en = RAAA_SYSTEM_IN_LIMITED_MODE;

				/* Preserve the IGN status */
				g_Previous_IGN_State_u8 = g_Current_IGN_St_u8;
				
				/* Suspend the LVGL Task & Clear the LCD Buffer*/
				Lvgl_Task_Suspend();
				LCDIF_ClearAndUpdateLCDBuffer();

				Sys_Service_Illum_control(0u);

				g_Sys_Service_ignition_status_u8 = IGN_OFF;

				g_Sys_Ready_Status_bl = FALSE;

				/* Write has to happen only on IGN OFF TO ON*/
				if(g_Is_Ignition_OFF_to_ON_u8 == TRUE)
				{
					/* Write value in GPR to detect IGN / BATTERY CYCLE Difference*/
					SNVS_LP_GPR_Write();
				}

			}

			break;

	case RAAA_SYSTEM_IN_LIMITED_MODE:

			for(fl_loop_Idx = 0; fl_loop_Idx < 6; fl_loop_Idx++)
			{
				/* Do NVM Write */
				SLEEP_NVM_WRITE_CBK_CFG[fl_loop_Idx].NVM_WRITE_CBK();

				/* set NVM Write completion flag */
				g_Sleep_NVM_Completion_Status = TRUE;

			}

			if(g_Sleep_NVM_Completion_Status == TRUE)
			{
				/* initialize sleep entry counter */
				g_Sleep_Entry_Counter = SLEEP_ENTRY_TIMER;

				/* Change state to prepare sleep to enter into SNVS mode */
				g_System_Current_State_en = RAAA_SYSTEM_PREPARE_SLEEP;

			}
			else
			{
				/* DO NOTHING*/
			}
			break;		

	case RAAA_SYSTEM_PREPARE_SLEEP:	

			/* read ign pin status */
			g_Current_IGN_St_u8 = Dio_Handler_Read_Pin_Status();

			if(g_Current_IGN_St_u8 == IGN_OFF)
			{
				/* Decrement sleep entry counter */
				if (g_Sleep_Entry_Counter >= 0)
				{
					g_Sleep_Entry_Counter --;
				}
			}
			else
			{
				/* early wakeup observed */

				/* Enter into normal mode */
				g_System_Current_State_en = RAAA_SYSTEM_IN_NORMAL;	

				g_Previous_IGN_State_u8 = IGN_ON;

				/* enbale TFT with default pwm */
				Sys_Service_Illum_control(0u);

				/* welcome animation */
				HMI_Early_Wake_Up_Animation_Control();

				g_Sleep_Entry_Counter = 0;

				g_Sleep_NVM_Completion_Status = FALSE;

			}

			/* SLEEP ENTRY COUNTER EXPIRED, ENTER INTO SNVS MODE */
			if((g_Sleep_Entry_Counter == 0) && (g_Current_IGN_St_u8 == IGN_OFF))
			{
			    /* change state to sleep entry */
			   	g_System_Current_State_en = RAAA_SYSTEM_IN_SLEEP_ENTRY;

			}
			else
			{
				/* DO NOTHING */
			}

			break;	

	case RAAA_SYSTEM_IN_SLEEP_ENTRY:

			fl_IGN_Status_u8 = GPIO_PinRead(BOARD_INITPINS_DI_IGN_MCU_IN_GPIO,BOARD_INITPINS_DI_IGN_MCU_IN_GPIO_PIN);

			if(fl_IGN_Status_u8 == IGN_OFF)
			{

				GPIO_PinInit(BOARD_INITPINS_DI_IGN_MCU_IN_GPIO, BOARD_INITPINS_DI_IGN_MCU_IN_GPIO_PIN,  &s_batt_filter_st);

				GPIO_PinSetInterruptConfig(BOARD_INITPINS_DI_IGN_MCU_IN_GPIO,BOARD_INITPINS_DI_IGN_MCU_IN_GPIO_PIN, kGPIO_IntLowLevel);
				
				PowerDown_Sequence();

				GPIO13->IMR |= 1;

				SNVS->LPCR |= SNVS_LPCR_TOP_MASK;


			}
			else
			{
				/* enbale TFT with default pwm */
				Sys_Service_Illum_control(0u);

				/* welcome animation */
				HMI_Early_Wake_Up_Animation_Control();

				/* Enter into normal mode */
				g_System_Current_State_en = RAAA_SYSTEM_IN_NORMAL;	

				g_Previous_IGN_State_u8 = IGN_ON;

				g_Sys_Ready_Status_bl = FALSE;

				g_Sleep_Entry_Counter = 0;

			}


			break;

	default:
			/* Enter into normal mode */
			g_System_Current_State_en = RAAA_SYSTEM_IN_NORMAL;	

			break;	

    }
}

void Swc_TripA_Timer_NVM_Write(void)
{
	/* TRIPA TIME NVM WRITE */
	Swc_Trip_Timer_NVM_Write(0);
}

void Swc_TripB_Timer_NVM_Write(void)
{
	/* TRIPB TIME NVM WRITE */
	Swc_Trip_Timer_NVM_Write(1);
}

static void Sys_Service_Illum_control(uint8_t pwm_duty)
{
	/* update current duty cycle value in PWM Driver */
	PWM_UpdatePwmDutycycle(PWM1,kPWM_Module_0,kPWM_PwmA,kPWM_SignedCenterAligned,pwm_duty);

    /* Load PWM Register */
	PWM_SetPwmLdok(PWM1, (kPWM_Control_Module_0), true);

}

void Enter_Critic_Section(void)
{
	/* Block Global interrupts , Enter into critical section */
    regPrimask = DisableGlobalIRQ();
}

void Exit_Critic_Section(void)
{
	/* Enable global interrupts , exit critical section */
	EnableGlobalIRQ(regPrimask);
}

uint8_t Sys_Service_Ign_Off_To_ON_Status(void)
{
	return (g_Is_Ignition_OFF_to_ON_u8);
}

void Sys_Service_Shutdown_Process(void)
{
	/* DO_TFT_BKLT_EN */

	if (g_Do_Bklt_En_u8 == 0)
	{
		/* Do Nothing */
	}
	else if(g_Do_Bklt_En_u8 == 1)
	{

		GPIO_PinWrite(BOARD_INITPINS_bklt_GPIO, BOARD_INITPINS_bklt_GPIO_PIN, 1);
	}
	else if(g_Do_Bklt_En_u8 == 2)
	{

		GPIO_PinWrite(BOARD_INITPINS_bklt_GPIO, BOARD_INITPINS_bklt_GPIO_PIN, 0);
	}




	if(g_Illum_Pwm_En_u8 == 0)
	{
		/* Do Nothing */
	}
	else if(g_Illum_Pwm_En_u8 == 1)
	{

//		GPIO_PinWrite(BOARD_INITPINS_illum_GPIO, BOARD_INITPINS_illum_GPIO_PIN, 1);
	}
	else if(g_Illum_Pwm_En_u8 == 2)
	{

//		GPIO_PinWrite(BOARD_INITPINS_illum_GPIO, BOARD_INITPINS_illum_GPIO_PIN, 0);
	}



	/* TFT_3.3V_EN */

	if (g_Do_TFT_En_u8 == 0)
	{
		/* Do Nothing */
	}
	else if(g_Do_TFT_En_u8 == 1)
	{

		GPIO_PinWrite(BOARD_INITPINS_tft_3v3_GPIO, BOARD_INITPINS_tft_3v3_GPIO_PIN, 1);
	}
	else if(g_Do_TFT_En_u8 == 2)
	{

		GPIO_PinWrite(BOARD_INITPINS_tft_3v3_GPIO, BOARD_INITPINS_tft_3v3_GPIO_PIN, 0);
	}



	/* 5V_SW_EN */

	if(g_Do_5v_En_u8 == 0)
	{

	}
	else if(g_Do_5v_En_u8 == 1)
	{

		GPIO_PinWrite(BOARD_INITPINS_en_5v_GPIO, BOARD_INITPINS_en_5v_GPIO_PIN, 1);
	}

	else if(g_Do_5v_En_u8 == 2)
	{

		GPIO_PinWrite(BOARD_INITPINS_en_5v_GPIO, BOARD_INITPINS_en_5v_GPIO_PIN, 0);
	}



	/* DO_CAN_VEH_STB */

	if(g_Do_Can_En_u8 == 0)
	{
		/* Do Nothing */
	}
	else if(g_Do_Can_En_u8 == 1)
	{

		GPIO_PinWrite(BOARD_INITPINS_CAN_STB_GPIO, BOARD_INITPINS_CAN_STB_GPIO_PIN, 1);
	}
	else if(g_Do_Can_En_u8 == 2)
	{

		GPIO_PinWrite(BOARD_INITPINS_CAN_STB_GPIO, BOARD_INITPINS_CAN_STB_GPIO_PIN, 0);
	}



	/* DO_SWITCHED_BATT_EN */

	if(g_Do_Switch_Batt_En_u8 == 0)
	{

	}
	else if(g_Do_Switch_Batt_En_u8 == 1)
	{

		GPIO_PinWrite(BOARD_INITPINS_batt_en_GPIO, BOARD_INITPINS_batt_en_GPIO_PIN, 1);
	}
	else if(g_Do_Switch_Batt_En_u8 == 2)
	{

		GPIO_PinWrite(BOARD_INITPINS_batt_en_GPIO, BOARD_INITPINS_batt_en_GPIO_PIN, 0);
	}


	/* P_BATT1_MAIN_FILTERED_SW_EN */

	if(g_Batt1_MainFiltered_Sw_En_u8 == 0)
	{

	}
	else if(g_Batt1_MainFiltered_Sw_En_u8 == 1)
	{

		GPIO_PinWrite(BOARD_INITPINS_FUEL_SBATT_CTRL_MCUOUT_GPIO, BOARD_INITPINS_FUEL_SBATT_CTRL_MCUOUT_GPIO_PIN, 1);
	}
	else if(g_Batt1_MainFiltered_Sw_En_u8 == 2)
	{

		GPIO_PinWrite(BOARD_INITPINS_FUEL_SBATT_CTRL_MCUOUT_GPIO, BOARD_INITPINS_FUEL_SBATT_CTRL_MCUOUT_GPIO_PIN, 0);
	}




	/* FUEL_SBATT_CTRL_MCUOUT */

	if(g_SBatt_ctrl_Mcuout_u8 == 0)
	{
		/* Do Nothing */
	}
	else if(g_SBatt_ctrl_Mcuout_u8 == 1)
	{

		GPIO_PinWrite(BOARD_INITPINS_FUEL_SBATT_CTRL_MCUOUT_GPIO, BOARD_INITPINS_FUEL_SBATT_CTRL_MCUOUT_GPIO_PIN, 1);
	}
	else if(g_SBatt_ctrl_Mcuout_u8 == 2)
	{

		GPIO_PinWrite(BOARD_INITPINS_FUEL_SBATT_CTRL_MCUOUT_GPIO, BOARD_INITPINS_FUEL_SBATT_CTRL_MCUOUT_GPIO_PIN, 0);
	}

	/* Shutdown CAN Peripheral */
	//FLEXCAN_Deinit(CAN_Channel_Base);
	FLEXCAN_Deinit(VECHILE_CAN);
	FLEXCAN_Deinit(DIAG_CAN);

	/* Shutdown ADC Peripheral */
	//void LPADC_Deinit(ADC_Type *base);
	LPADC_Deinit(DEMO_LPADC_BASE);

	/* Shutdown LCD Peripheral */
	ELCDIF_Deinit(LCDIF);

	/* Kill I2C Peripheral */
	LPI2C_MasterDeinit(EXAMPLE_LPI2C_MASTER_BASEADDR);
}


void Sys_Service_WakeUp_Process(void)
{
		/* do nothing */
}

uint32_t Sys_Service_Voltage_Batt_Get_Status(void)
{
	return g_Batt_Voltage_u32;
}

void SNVS_LP_GPR_Write(void)
{
   /* WRITE DATA INTO GENERAL PURPOSE REGISTER OF SNVS*/
   SNVS->LPGPR[0] = SNVS_LP_GPR_VALUE;
}

void SNVS_LP_GPR_Read(void)
{
	/* READ DATA INTO GENERAL PURPOSE REGISTER OF SNVS*/
	g_Data_In_SNVS_GPR_u32 = SNVS->LPGPR[0];
}

bool System_Service_Is_Battery_Cycle_Detected(void)
{
	bool fl_Return_Status = FALSE;

	/* read value in SNVS General purpose register*/
	SNVS_LP_GPR_Read();

	/* value in SNVS LP GPR0 is zero , cold init detected. 
	 * because upon battery cycle, value will errased , upon IGN Cycle , it retains value*/
	if(g_Data_In_SNVS_GPR_u32 == SNVS_LP_GPR_VALUE)
	{
		/* IGN Cycle detected*/
		fl_Return_Status = FALSE;
	}
	else
	{
		/* battery cycle detected*/
		fl_Return_Status = TRUE;
	}

	return (fl_Return_Status);
}

void AppToBootJmp( void)
 {
	 /* LOCAL VARIABLE */
    uint32_t ControlRegister = 0;
	uint8_t CrntSession = GetCurrentSession();
	
	if(CrntSession == UDS_PROG_SESS)
	{
		Sys_Service_Shutdown_Process();
		SCB->VTOR = 0x30002000; // REMAPPING VECTOR TABLE
		
		/* CLEAR ACTIVE STACK POINTER BIT - REFER CONTROL REGISTER IN TRM */
		ControlRegister = __get_CONTROL(); 

		/* clear the control bit **/
		ControlRegister &= !(1 << 1);

		/*  */
		__set_CONTROL(ControlRegister);

		__asm("LDR r1, = 0x30002000");
		__asm("LDR sp, [r1]");
		__asm("LDR r3,[r1,#4]");
		__asm("BLX r3");
	}
 }


void SuspendLVGL_ClearBuffer(void)
{
	/* Check Welcome Animation Status & Enable the Black Image & Suspend the LVGL Task */
	if (g_Animation_Comp_Status == TRUE)
	{					
		Lvgl_Task_Suspend();
		LCDIF_ClearAndUpdateLCDBuffer();
		g_LVGL_Suspend_BL = TRUE;
	}
	else
	{
		/* Do Nothing */
	}

}


uint8_t SysService_Get_BatteryVoltageSts(void)
{
	/* RETURN BATTERY STATUS */
	return g_System_Service_State_u8;
}



/*
* @brief    This API is used to process core expection states
* @param    NONE
* @return   NONE
* @invocation invoked by exception handler supported by Micro
*/
void Core_Exception_Handler(void)
{
	#if(ENABLE_SOFT_RESET_IN_EXCEPTION_STATE == STD_ON)
		/* System reset shall be enabled in released software in exception states*/
        NVIC_SystemReset();
    #else    
        while(1) {}
    #endif 
}

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : v1.0.3                         
    REVISION DATE        : 01/23/2023      
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfoteh.com)       
    DESCRIPTION          : Core exception handler API implemented         
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : v1.0.2                         
    REVISION DATE        : 11/09/2022      
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfoteh.com)       
    DESCRIPTION          : SNVS LP GPR write and read functionality added for cold and warm init detection           
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : v1.0.0                         
    REVISION DATE        : 04/12/2022       
    CREATED / REVISED BY : Balsubramaniyan (balasubramaniayan.s@niyatainfoteh.com)       
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! ADC_C*/
