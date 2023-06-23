/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* Standard includes. */
#include <assert.h>
#include <stdio.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "peripherals.h"
#include "clock_config.h"
#include "board.h"
#include "lvgl_app.h"
#include "display_test.h"
#include "State_Machine.h"
#include "State_Machine_cfg.h"
#include "Cmp_Init.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define ENABLE_OS

#define APP_IMG_HEIGHT LCDIF_PANEL_HEIGHT
#define APP_IMG_WIDTH LCDIF_PANEL_WIDTH

/* The software timer period. */
#define SW_TIMER_PERIOD_MS (10 / portTICK_PERIOD_MS)

TaskHandle_t Lvgl_Task_Handle;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main(void) {
	bool fl_Cold_Init_Detection_Status_bl = FALSE;
	TimerHandle_t SwTimerHandle = NULL;
	TaskHandle_t lvglTaskHandle = NULL;

	/* Init board hardware. */
	HardWare_Init(); 

	fl_Cold_Init_Detection_Status_bl = System_Service_Is_Battery_Cycle_Detected();

	/* Init Application Module */
	Application_Init();

	/* COLD INIT DETECTED*/
	if(fl_Cold_Init_Detection_Status_bl == TRUE)
	{
		/* perform cold init*/
		Application_Cold_Init();
	}
	else
	{
		/* perform warm init*/
		Application_Warm_Init();

	}

#ifdef ENABLE_OS


	/* CREATE DISPLAY RELATED TASK */
	if (xTaskCreate(lvgl_task, "LVGL_task", configMINIMAL_STACK_SIZE + 1024,
			NULL, lvgl_task_PRIORITY, &Lvgl_Task_Handle) !=
	pdPASS) {
		
		//while (1);
	}

	/* CREATE APPLICATION TASK */
	Cmp_Tasks_Create();

	/* Start scheduling. */
	vTaskStartScheduler();
	for (;;);
}
#else
	//CBAR(LCDIF_Buffer[0]);
	APP_FillFrameBuffer(LCDIF_Buffer[frameBufferIndex]);
	while(1)
	{
		frameBufferIndex ^= 1U;
		//CBAR(LCDIF_Buffer[frameBufferIndex]);
		APP_FillFrameBuffer(LCDIF_Buffer[frameBufferIndex]);

		ELCDIF_SetNextBufferAddr(LCDIF,
		(uint32_t) LCDIF_Buffer[frameBufferIndex]);

		screen_busy();
	}
}

#endif

void Lvgl_task_Resume(void)
{
	
	vTaskResume(Lvgl_Task_Handle);
}

void Lvgl_Task_Suspend(void)
{
	vTaskSuspend(Lvgl_Task_Handle);
}
/*!
 * @brief Malloc failed hook.
 */
void vApplicationMallocFailedHook(void)
{
    for (;;)
        ;
}
