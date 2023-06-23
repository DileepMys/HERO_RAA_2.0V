/* @file FILE NAME */
#ifndef CMP_TASK_C
#define CMP_TASK_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Name (mail-id)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : 
 *  Version                         : 
 *  Micros supported                : 
 *  Compilers supported             : 
 *  Platforms supported             : 
 *  Description                     : This file consists of definitions of 
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "CanMgr.h"
#include "fsl_flexcan.h"
#include "Cmp_Tasks.h"
#include "Cmp_Init.h"
#include "TTMgr.h"
#include "MIMXRT1172.h"
#include "FreeRTOSConfig.h"
#include "fsl_gpio.h"
#include "task.h"
#include "CanIF.h"
#include "CanTp.h"
#include "CanIF_cfg.h"
#include "TC.h"
#include "rtc.h"
#include "fsl_lpadc.h"
#include "Abs_Telltale.h"
#include "Swc_TT_Fog_Lamp.h"
#include "Swc_System_Service.h"
#include "Swc_Odometer.h"
#include "Swc_Averege_Speed.h"
#include "Fuel_Guage.h"
#include "Button_Manager.h"
#include "Swc_NVM_Handler.h"
#include "Swc_Speedometer.h"
#include "Swc_Tachometer.h"
#include "HMI_Tacho_Rend.h"
#include "Swc_Trip_Timer.h"
#include "Swc_TT_Mil_Tft.h"
#include "Swc_TT_Oil_Pressure.h"
#include "Swc_Service_Remainder.h"
#include "Swc_Voltage_Battery_St.h"
#include "Swc_TFT_Illum.h"
#include "Dio_Handler.h"
#include "CanGateway.h"
#include "Ambient_light_sensor.h"
#include "State_Machine.h"
#include"UDS.h"
#include "UART_DataManager.h"
/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                     
***********************************************************************************************************************/






/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*  
 * @brief: This macro is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
#define Idle_Task_Priority (tskIDLE_PRIORITY)
#define task_PRIORITY_1 (configMAX_PRIORITIES - 4)
#define task_PRIORITY_2 (configMAX_PRIORITIES - 3)
#define task_PRIORITY_3 (configMAX_PRIORITIES - 2)
#define task_PRIORITY_4 (configMAX_PRIORITIES - 1)

unsigned char g_Check_Telltale_status;

flexcan_rx_mb_config_t RxmbConfig;

flexcan_mb_transfer_t CanIF_Rx_GetFrame_Buffer;

extern volatile uint32_t rxQueueNum;

flexcan_mb_transfer_t Rx_ConfigSt;

extern flexcan_frame_t Tx_frame;

// extern flexcan_mb_transfer_t txXfer;

// extern flexcan_mb_transfer_t Can1_Vehicle_rxXfer, Can2_Diag_rxXfer;

extern flexcan_mb_transfer_t Vehicle_Tx_frame, Diag_Tx_frame, Can1_Vehicle_rxXfer, Can2_Diag_rxXfer;

uint8_t g_Set_Tx = 0;

volatile status_t rxStatus = 0;

extern flexcan_frame_t Can1_Vehicle_Rx_frame[CANIF_TOTAL_RX_PDU];

extern flexcan_frame_t Can2_Diag_Rx_frame[CANIF_TOTAL_RX_PDU];






 extern flexcan_handle_t Vehicle_flexcanHandle;

 extern flexcan_handle_t Diag_flexcanHandle;

TickType_t xLastWakeTime;

extern flexcan_rx_mb_config_t mbConfig;

TaskHandle_t Side_Stand_TT_Task_Handler;
TaskHandle_t ABS_TT_Task_Handler;
TaskHandle_t CAN_TP_Task_Handler;
TaskHandle_t CAN_Mgr_Task_Handler;
TaskHandle_t Flex_Vehicle_CAN_Task_Handler;
TaskHandle_t Flex_Diag_CAN_Task_Handler;
TaskHandle_t Sys_Service_Task_Handler;
TaskHandle_t Odo_Task_Handler;
TaskHandle_t MIL_TT_Task_Handler;
TaskHandle_t Speedo_Task_Handler;
TaskHandle_t TT_Mgr_Task_Handler;
TaskHandle_t TFT_Illum_Task_Handler;
TaskHandle_t Fuel_Gauge_Task_Handler;
TaskHandle_t Oil_Pressure_TT_Task_Handler;
TaskHandle_t Service_Remainder_Task_Handler;
TaskHandle_t Gear_Task_Handler;
TaskHandle_t DIO_Task_Handler;
TaskHandle_t Fog_Lamp_TT_Task_Handler;
TaskHandle_t RTC_Task_Handler;
TaskHandle_t AV_Speed_Task_Handler;
TaskHandle_t Batt_Monitor_Task_Handler;
TaskHandle_t Tacho_Task_Handler;
TaskHandle_t TachoHandleTask;
TaskHandle_t Trip_Timer_Task_Handler;
TaskHandle_t Fuel_ADC_Task_Handler;
TaskHandle_t Button_Mgr_Task_Handler;
TaskHandle_t IFE_Task_Handler;
TaskHandle_t AFE_Task_Handler;
TaskHandle_t DTE_Task_Handler;
TaskHandle_t Batt_Volt_Status_Task_Handler;
TaskHandle_t ALS_Task_Handler;

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
void Odometer_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(50);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();
    while(1)
    {
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
		
		ODO_Active();
	
    }
}

void Speedo_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(80);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();
    while(1)
    {
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
		
		Speedometer_Active();
	
    }
}

void TT_Mgr_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(100);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();
    while(1)
    {
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
	
		TT_Mgr_Active();

	
    }
}


void Fuel_Guage_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(100);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

											/* Execution Time */
		Fuel_Guage_MainFunction();					/* 10.5us */

	}
}

void Service_Remainder_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(100);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

											/* Execution Time */
		TT_Service_Remainder_MainFunction();		/* 105us */

	}
}

void Fog_Lamp_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(100);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

											/* Execution Time */

		TT_Fog_Lamp_MainFunction();					/* 10us */
	}
}
void TT_Oil_Pressure_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(100);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

											/* Execution Time */
		TT_Oil_Pressure_MainFunction(); 			/* 30us */
	}
}

void TFT_Illum_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(100);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

											/* Execution Time */
		SWC_TFT_Illum_Mainfunction();
	}
}


void ABS_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(40);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{									
        xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

	    /* Execution time */
		
		Abs_TT_Active();				/* 150us */ 

	}
}

void Gear_Position_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(40);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{									
        xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

	    /* Execution time */
		gear_position_MainFunction();

	}
}
void MIL_TT_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(10);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{									
        xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

	    /* Execution time */
		TT_Mil_Tft_MainFunction();		/* 25us */

	}
}
void Trip_Timer_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(200);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
	
		Trip_Timer_MainFunction();
	}
}

void Trip_Avg_Speed_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(100);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

		Average_Speed_MainFunction();
	}
}

void RTC_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(1000);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
	
		Rtc_MainFunction();

	}
}

void Tacho_Period_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(10);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();
	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
		Tachometer_Active();

	}
}

void GUI_Tacho_Period_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(16);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();
	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
	
		HMI_Tacho_Rend_Mainfunction();
	}
}

void Dio_Handler_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(10);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();
	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

		Dio_Handler_Mainfunction();
	}
}

void Sys_Service(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(100);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
		
		State_Machine_Main_Function();
		System_Service_MainFunction();

	}
}

void Button_Mgr(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(8);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{
	xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
	Button_Mgr_MainFunction();

	}
}

void FlexCan_VehicleRx_Periodic_Task(void *pvparameters)
{

	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(10);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();
    while(1)
    {
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

		CanMgr_RxSignalDispatcher();

		/* UART RUNNABLE - TO MAINTAIN/HANDLE TIMEOUTS */
		UART_DataManager_MainFunction();
    }

}
void IFE_Periodic_Task(void *pvparameters)
{

	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(1000);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

    while(1)
    {
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

		IFE_Active();
		
	}
}

void AFE_Periodic_Task(void *pvparameters)
{

	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(1000);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

    while(1)
    {
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

		AFE_Active();
	}
}

void DTE_Periodic_Task(void *pvparameters)
{

 	TickType_t xLastWakeTime;
  	const TickType_t xFrequency = pdMS_TO_TICKS(100);
  	BaseType_t xWasDelayed;

     // Initialise the xLastWakeTime variable with the current time.
     xLastWakeTime = xTaskGetTickCount ();

    while(1)
    {
 		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

 		DTE_Active();
 	}
}

 void CanTP_Periodic_Task(void *pvparameters)
 {
 	TickType_t xLastWakeTime;
  	const TickType_t xFrequency = pdMS_TO_TICKS(100);
  	BaseType_t xWasDelayed;

     // Initialise the xLastWakeTime variable with the current time.
     xLastWakeTime = xTaskGetTickCount ();
 	while(1)
 	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
 		CanTp_MainFunction();
 		
 	}
 }

void CanMgr_MainFunction_Periodic_Task(void *pvparameters)
{
	static uint8_t network_request_val;
	network_request_val = (WAKEUP_E_OK);

	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(100);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

    while(1)
    {
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
 
		CanMgr_Mainfunction();
		CanMgr_GateWayPeriodicTask();
	}
}

void Side_Stand_Periodic_Task(void *pvparameters)
{

	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(50);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

  while(1)
    {
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
		Side_Stand_TT_Main_Function();
	}
}

void Voltage_Battery_Status_Periodic_Task(void *pvparameters)
 {

 	TickType_t xLastWakeTime;
  	const TickType_t xFrequency = pdMS_TO_TICKS(100);
  	BaseType_t xWasDelayed;

     // Initialise the xLastWakeTime variable with the current time.
     xLastWakeTime = xTaskGetTickCount ();

     while(1)
     {
 		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

 		Voltage_Battery_MainFunction();
 	}
 }


void ALS_100ms_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(100);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

				ALS_Mainfunction();							
	
		
	}
}

void Lvgl_Sys_Tick(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(5);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

		SwTimerCallback();							
		
	}
}

void UDS_10ms_Periodic_Task(void *pvparameters)
{
	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(10);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

	while(1)
	{
		xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );

		UDS_Main();							
		
	}
}

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

void Cmp_Tasks_Create(void)
{

	xTaskCreate(Side_Stand_Periodic_Task, "Side_Stand_Periodic_Task", configMINIMAL_STACK_SIZE+100, NULL, task_PRIORITY_4, &Side_Stand_TT_Task_Handler);

    xTaskCreate(ABS_Periodic_Task, "ABS_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_1, &ABS_TT_Task_Handler);

	xTaskCreate(CanTP_Periodic_Task, "CanTP_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_1, &CAN_TP_Task_Handler);

	xTaskCreate(CanMgr_MainFunction_Periodic_Task, "CanMgr_MainFunction_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_3, &CAN_Mgr_Task_Handler);

    xTaskCreate(FlexCan_VehicleRx_Periodic_Task, "FlexCan_VehicleRx_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_4, &Flex_Vehicle_CAN_Task_Handler);

	xTaskCreate(Sys_Service, "Sys_Service", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_4, &Sys_Service_Task_Handler);

	xTaskCreate(Odometer_Periodic_Task, "Odometer_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_4, &Odo_Task_Handler);

	xTaskCreate(MIL_TT_Periodic_Task, "MIL_TT_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_1, &MIL_TT_Task_Handler);

	xTaskCreate(Speedo_Periodic_Task, "Speedo_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_3, &Speedo_Task_Handler);

	xTaskCreate(TT_Mgr_Periodic_Task, "TT_Mgr_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_4, &TT_Mgr_Task_Handler);

	xTaskCreate(TFT_Illum_Periodic_Task, "TFT_Illum_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_3, &TFT_Illum_Task_Handler);

	xTaskCreate(Fuel_Guage_Periodic_Task, "Fuel_Guage_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_3, &Fuel_Gauge_Task_Handler);

	xTaskCreate(TT_Oil_Pressure_Periodic_Task, "TT_Oil_Pressure_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_3, &Oil_Pressure_TT_Task_Handler);

	xTaskCreate(Service_Remainder_Periodic_Task, "Service_Remainder_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_3, &Service_Remainder_Task_Handler);

	xTaskCreate(Gear_Position_Periodic_Task, "Gear_Position_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_1, &Gear_Task_Handler);

	xTaskCreate(Dio_Handler_Periodic_Task, "Dio_Handler_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_1, &DIO_Task_Handler);

	xTaskCreate(Fog_Lamp_Periodic_Task, "Fog_Lamp_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_3, &Fog_Lamp_TT_Task_Handler);

	xTaskCreate(RTC_Periodic_Task, "RTC_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_2, &RTC_Task_Handler);

	xTaskCreate(Trip_Avg_Speed_Periodic_Task, "Trip_Avg_Speed_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_4, &AV_Speed_Task_Handler);

    xTaskCreate(fsl_System_Service_lpadc_Periodic_Task, "fsl_System_Service_lpadc_Periodic_Task", configMINIMAL_STACK_SIZE+100, NULL, task_PRIORITY_4, &Batt_Monitor_Task_Handler);

    xTaskCreate(Tacho_Period_Task, "Tacho_Period_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_2, &Tacho_Task_Handler);

    xTaskCreate(GUI_Tacho_Period_Task, "GUI_Tacho_Period_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_2, &TachoHandleTask);

   xTaskCreate(Trip_Timer_Periodic_Task, "Trip_Timer_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_2, &Trip_Timer_Task_Handler);

    xTaskCreate(fsl_lpadc_Periodic_Task, "fsl_lpadc_Periodic_Task", configMINIMAL_STACK_SIZE+100, NULL, task_PRIORITY_3, &Fuel_ADC_Task_Handler);

    xTaskCreate(Button_Mgr, "Button_Mgr", configMINIMAL_STACK_SIZE+100, NULL, task_PRIORITY_3, &Button_Mgr_Task_Handler);

    xTaskCreate(IFE_Periodic_Task, "IFE_Periodic_Task", configMINIMAL_STACK_SIZE+100, NULL, task_PRIORITY_4, &IFE_Task_Handler);

    xTaskCreate(AFE_Periodic_Task, "AFE_Periodic_Task", configMINIMAL_STACK_SIZE+100, NULL, task_PRIORITY_1, &AFE_Task_Handler);
   
   xTaskCreate(DTE_Periodic_Task, "DTE_Periodic_Task", configMINIMAL_STACK_SIZE+100, NULL, task_PRIORITY_1, &DTE_Task_Handler);

    xTaskCreate(Voltage_Battery_Status_Periodic_Task, "Voltage_Battery_Status_Periodic_Task", configMINIMAL_STACK_SIZE+100, NULL, task_PRIORITY_1, &Batt_Volt_Status_Task_Handler);

    xTaskCreate(ALS_100ms_Periodic_Task, "ALS_100ms_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_1, &ALS_Task_Handler);

    xTaskCreate(Lvgl_Sys_Tick, "Lvgl_Sys_Tick", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_4, NULL);

    xTaskCreate(UDS_10ms_Periodic_Task, "UDS_10ms_Periodic_Task", configMINIMAL_STACK_SIZE + 100, NULL, task_PRIORITY_4, NULL);

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
    REVISION NUMBER      : Major.Minor.Patch                          
    REVISION DATE        : MONTH/DATE/YEAR        
    CREATED / REVISED BY : NAME (EMAIL-ID)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! CMP_TASK_C */
