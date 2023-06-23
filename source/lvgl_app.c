/*
 * lvgl_app.c
 *
 *  Created on: 23-Mar-2022
 *      Author: Admin
 */
#include <gen/events_init.h>
#include <gen/gui_guider.h>
#include "peripherals.h"

#include "../lvgl/lvgl.h"

#include "lvgl_app.h"

#include "custom.h"
#include "fsl_gpio.h"

/* APPLCIATION - INCLUDE */
#include "Swc_Speedometer.h"
#include "Swc_TT_Mil_Tft.h"
#include "Abs_Telltale.h"
#include "Cmp_Tasks.h"
#include "Swc_TT_Oil_Pressure.h"
#include "Swc_Odometer.h"
#include "I2C_Handler.h"
#include "Fuel_Guage.h"
#include "Swc_Tachometer.h"
#include "HMI_Tacho_Rend.h"
#include "fsl_snvs_lp.h"
#include "SWC_Gear_position.h"
#include "rtc.h"
#include "Swc_Trip_Timer.h"
#include "Swc_Trip_Timer_cfg.h"
#include "Swc_Averege_Speed.h"
#include "Swc_TT_Fog_Lamp.h"
#include "Swc_Service_Remainder.h"
#include "Swc_Speedometer.h"
#include "TC.h"
#include "Button_Manager_Cfg.h"
#include "HMI_Main_Screen.h"
#include "HMI_Setting_Screen.h"
#include "fuel03.h"
#include "UART_DataManager.h"
#include "Ambient_light_sensor.h"
#include "Ambient_light_sensor_Cfg.h"
#include "HMI_Setting_Screen.h"
#include "Swc_System_Service.h"
#include "pin_mux.h"
#include "board.h"
#include "HMI_TripA.h"
#include "HMI_TripInfo.h"
#include "HMI_Clock.h"
#include "HMI_Phone.h"
#include "Cmp_Init.h"
#include "rtc.h"
#include "Swc_System_Service.h"
#include "gui_guider.h"

/* To hold the state of HMI Presentation Layer */
uint8_t g_HMI_Screen_PST_State_u8 = HMI_PST_WELCOME_SCREEN;

uint8_t g_previous_fl_Fault_St_u8 = 0;
uint8_t g_Performance_checking_flag_u8 = TRUE;

uint8_t g_image_index = 1;

uint8_t fl_Trip_Ret_Btn_St = 0;

uint16_t g_ISpeedo_Value_u16 = 0;

uint16_t g_Previous_ISpeedo_Value_u16 = 0;

uint8_t fl_Get_Current_Time_Foramt_Lvgl_App;

uint8_t g_Previous_FoglampValue_U8 = 0xFF;
uint8_t g_Previous_EngineTTValue_U8 = 0xFF;
uint8_t g_Previous_OilTTValue_U8 = 0xFF;

/* Varibale to hold current status of Welcome animation*/
HMI_WELCOME_ANIMATION_ST_EN g_Welcome_Animation_Status_en = WELCOME_ANIMATION_NOT_STARTED;

bool g_Animation_Comp_Status = FALSE;

uint8_t g_check_Welcome_status = 0;
uint32_t g_Previous_ODOValue_u32 = 0;

uint8_t animation = 0;
uint8_t g_Fuel_Bar_count_u8;
uint8_t g_Prev_Fuel_Bar_Level;
static uint8_t g_Fuel_Img_Index = 0;

uint8_t g_Service_TT_Status;

uint8_t g_Previous_Service_TT_Status = 0xFF;

bool g_ABS_TT_ON_Status;

static lv_disp_draw_buf_t draw_buf;
// static lv_color_t buf1[APP_IMG_WIDTH * APP_IMG_HEIGHT / 10];
static lv_disp_drv_t disp_drv;		  /*Descriptor of a display driver*/
static lv_disp_drv_t *disp_drv_Flush; /*Descriptor of a display driver*/

static lv_style_t screen_Set_Min;

static lv_style_t screen_Set_Hour;
// static Welcome_Counter  = 0;

uint8_t frameBufferIndex = 0;

// UART_DATA_MGR_PACKETS_TYPE_ST g_Get_Screen_Data_st;
static volatile bool s_frameDone = false;

GEAR_POS_LIST_EN g_Gear_Position_Display;
GEAR_SHIFT_ADVISORY_LIST_EN g_Gear_shift_advisory_u8;

extern const lv_img_dsc_t _Batt_1_3x8;

#define g_RTC_SNVS_Base_Add ((SNVS_Type *)0x40C90000)
#define DAY_MODE 1

RTC_TIME_STAMP_ST g_display_datetime = {0};

g_RTC_DATE_TIME_ST g_Date_Time_St;

uint8_t g_NVM_Busy_u8;
uint8_t g_set_counter;
lv_ui guider_ui;
static lv_style_t Opacity_Num;

TickType_t xDelay_HMI = 100 / portTICK_PERIOD_MS;

uint16_t g_Speedo_Intermediate_Value_u16 = 0;
static uint8_t g_check_status_clock_setting_u8 = 0;
uint8_t g_Trip_Odometer_Value_u8 = 0;
uint32_t g_Flash_TT_Status_u8 = 0;
uint8_t g_Is_Direction_Clockwise_u8 = 0;
uint8_t g_Fuel_Bar_In_Display_u8;
uint8_t g_Previous_Fuel_Bar_In_Display_u8 = 0;

bool g_Fuel_Inital_Update_bl;

uint16_t g_FuelTTFlash_u16 = 0;
uint8_t g_EEPROM_Ret_Timer = 0;
uint16_t g_Trip_Reset_Timer_u16 = 0;
uint8_t g_LowFuel_TT_ON_Status_u8 = 0;

uint8_t g_Fuel_Guague_Init = 1;

uint8_t g_EEPROM_Reset_Timer_u8 = 0;

uint8_t g_label_Change_Counter_u8;
static uint8_t g_Preveious_Ambient_Sense_Val_u8 = 0;
static uint8_t g_Current_Ambient_Sense_Val_u8 = 0;
g_Tacho_image g_tacho_img_table[202] = {TACHO_IMAGE_TABLE};
g_fuel_image g_fuel_img_table[67] = {FUEL_IMAGE_TABLE};

// static g_Nav_image g_Nav_img_table[10]={NAVIGATION_IMAGE_TABLE};

uint32_t g_current_tacho_index_u8 = 0;
uint8_t tacho_counter_u8 = 0;

uint8_t g_clock_check_set = 0;
uint8_t g_HMI_clock_format_u8 = 0;
uint8_t g_HMI_AM_PM_u8 = 0;

uint8_t g_Fuel_Open_Short_Flash_u8;

uint8_t g_hour_counter_u8 = 0;
uint8_t g_min_counter_u8 = 0;

bool g_Flash_Status_bl;
bool g_Previous_Flash_bl = FALSE;

uint8_t g_Fuel_Short_Flash_u8;

uint8_t g_Get_Navigation_Connect_Status = BLUETOOTH_ON;

/* HANDLE BAR BUTTON VARIABLE */
static uint8_t g_Handle_Bar_Btn_Status_u8[TOTAL_BUTTON] = {0};

uint8_t g_Service_Remainder_Blink_Count_u8;

uint16_t g_Min_RPM_ValPer_Img;
uint8_t variable = 2;

uint8_t HMI_FUEL_BAR_Image_Cfg[8] = {0, 10, 20, 30, 37, 48, 55, 66};

extern bool g_ghostimage_status;

lv_obj_t *img = NULL;

void GUI_Screen_Handler(void)
{

	switch (g_HMI_Screen_PST_State_u8)
	{
	case HMI_PST_IDLE:
		/* do nothing*/
		break;

	case HMI_PST_WELCOME_SCREEN:

		if (Sys_Service_Get_Ignition_State() == IGN_ON)
		{
			/* Once animation completed , trigger a event to navigate to main screen*/
			if (g_Welcome_Animation_Status_en == WELCOME_ANIMATION_COMPLETED)
			{
				/* Event trigger*/
				/* Change state to home screen*/
				g_HMI_Screen_PST_State_u8 = HMI_PST_HOME_SCREEN;

				/* Trigger event for screen transition from Welcome animation to main screen*/
				Set_Event(0);
			}
			else
			{
				HMI_Welcome_animation();
			}
		}
		break;

	case HMI_PST_HOME_SCREEN:
		/* Handle HMI Screen transitions and button handling */
		GUI_mainFunction();
		break;

	default:

		g_HMI_Screen_PST_State_u8 = HMI_PST_WELCOME_SCREEN;
		break;
	}

	/* clear button events */
	Clear_Btn_Events();
}

void HMI_Welcome_animation(void)
{
	if (g_image_index == 0)
	{
		img = NULL;
	}

	if (g_image_index == 1)
	{

		if (img == NULL)
		{
			img = lv_gif_create(lv_scr_act());
			lv_gif_set_src(img, &HeroRAAA_84);
			lv_obj_align(img, LV_ALIGN_DEFAULT, 0, 0);
		}
		else
		{
			lv_gif_restart(img);
		}

		/* Welcome Animation started*/
		g_Welcome_Animation_Status_en = WELCOME_ANIMATION_STARTED;
	}

	if (g_image_index <= 70)
	{
		/* Welcome Animation inprogress*/
		g_Welcome_Animation_Status_en = WELCOME_ANIMATION_INPROGRESS;

		g_image_index++;
	}
	else
	{
		if (img != NULL)
		{
			lv_obj_clean(img);
			lv_obj_del(img);
		}
		img = NULL;

		g_image_index = 0;
		g_Welcome_Animation_Status_en = WELCOME_ANIMATION_COMPLETED;

		g_Animation_Comp_Status = TRUE;
	}
}

void HMI_Animation_To_Main_Screen_Event_Trigger(void)
{
	if (img != NULL)
	{
		lv_obj_clean(img);
		lv_obj_del(img);
	}
	img = NULL;

	g_image_index = 0;
	g_Welcome_Animation_Status_en = WELCOME_ANIMATION_COMPLETED;

	g_Animation_Comp_Status = TRUE;

	/* Change state to home screen*/
	g_HMI_Screen_PST_State_u8 = HMI_PST_HOME_SCREEN;

	/* Trigger event for screen transition from Welcome animation to main screen*/
	Set_Event(0);

	/* Load Main screen*/
	GUI_mainFunction();
}

signed int Fuel_Pos[2] = {41, 226};

void GUI_Telltale_Handler(void)
{

	uint8_t fl_FogLamp_TT_ON_Status_u8;
	uint8_t fl_EngineFault_TT_ON_Status_u8;
	uint8_t fl_OilPressure_TT_ON_Status_u8;
	uint8_t fl_TractionControl_TT_ON_Status_u8;
	FUEL_LFW_TT_ST_EN fl_Low_Fuel_Warning_Status;

	fl_FogLamp_TT_ON_Status_u8 = Swc_Fog_LAmp_Get_Value();
	fl_EngineFault_TT_ON_Status_u8 = Swc_Mil_Tft_Get_Value();
	fl_OilPressure_TT_ON_Status_u8 = Swc_Oil_Pressure_Get_Value();

	fl_TractionControl_TT_ON_Status_u8 = 0;

	fl_Low_Fuel_Warning_Status = Fuel_Guage_Get_Low_Fuel_Status();

	/* Low Fuel Warning Indicator */
	if (fl_Low_Fuel_Warning_Status == LOW_FUEL_TT_ON)
	{

		if (g_Flash_Status_bl == TRUE & g_Previous_Flash_bl == FALSE)
		{
			lv_img_set_src(guider_ui.screen_Fuelbar0, &img_night_fuel_fill_09_orange);
			lv_obj_set_size(guider_ui.screen_Fuelbar0, 88, 40);
			lv_obj_set_pos(guider_ui.screen_Fuelbar0, 41, 265);
			g_Previous_Flash_bl = TRUE;
		}
		else if (g_Flash_Status_bl == FALSE & g_Previous_Flash_bl == TRUE)
		{
			lv_img_set_src(guider_ui.screen_Fuelbar0, &img_fuel_grey_bg_orange_icon);
			lv_obj_set_size(guider_ui.screen_Fuelbar0, 158, 43);
			lv_obj_set_pos(guider_ui.screen_Fuelbar0, 41, 265);
			g_Previous_Flash_bl = FALSE;
		}
	}
	else
	{
		/* Do Nothing*/
	}

	/* High Beam Indicator */
	if (g_Previous_FoglampValue_U8 != fl_FogLamp_TT_ON_Status_u8)
	{
		if (0 == fl_FogLamp_TT_ON_Status_u8)
		{
			/*  Flush the Green Icon, which is assigned for Button Pressed */
			lv_imgbtn_set_state(guider_ui.screen_FogLampTT, 0);
		}
		else
		{
			/*  Flush the White Icon, which is assigned for Button Released */
			lv_imgbtn_set_state(guider_ui.screen_FogLampTT, 1);
		}
		g_Previous_FoglampValue_U8 = fl_FogLamp_TT_ON_Status_u8;
	}
	else
	{
		/* No Changes Done Here */
	}

	/* Engine Indicator */
	if (g_Previous_EngineTTValue_U8 != fl_EngineFault_TT_ON_Status_u8)
	{
		if (0 != fl_EngineFault_TT_ON_Status_u8)
		{
			/*  Flush the Green Icon, which is assigned for Button Pressed */
			lv_imgbtn_set_state(guider_ui.screen_imgEngineTT, 0);
		}
		else
		{
			/*  Flush the White Icon, which is assigned for Button Released */
			lv_imgbtn_set_state(guider_ui.screen_imgEngineTT, 1);
		}
		g_Previous_EngineTTValue_U8 = fl_EngineFault_TT_ON_Status_u8;
	}
	else
	{
		/* No Changes Done Here */
	}

	/* Oil Pressure Warning Indicator */
	if (g_Previous_OilTTValue_U8 != fl_OilPressure_TT_ON_Status_u8)
	{
		if (0 != fl_OilPressure_TT_ON_Status_u8)
		{
			/*  Flush the Green Icon, which is assigned for Button Pressed */
			lv_imgbtn_set_state(guider_ui.screen_imgOilTelltale, 0);

		}
		else
		{
			/*  Flush the White Icon, which is assigned for Button Released */
			lv_imgbtn_set_state(guider_ui.screen_imgOilTelltale, 1);
		}
		g_Previous_OilTTValue_U8 = fl_OilPressure_TT_ON_Status_u8;
	}
	else
	{
		/* No Changes Done Here */
	}

	/* service remainder TT */
	if( g_Service_TT_Status != g_Previous_Service_TT_Status)
	{

		if (g_Service_TT_Status == (uint8_t)TRUE)
		{
			lv_obj_clear_flag(guider_ui.screen_Service_Due, LV_OBJ_FLAG_HIDDEN);
			lv_obj_move_foreground(guider_ui.screen_Service_Due);
			g_Previous_Service_TT_Status = (uint8_t)TRUE;
		}
		else if (g_Service_TT_Status == (uint8_t)FALSE)
		{
			lv_obj_add_flag(guider_ui.screen_Service_Due, LV_OBJ_FLAG_HIDDEN);
			lv_obj_move_foreground(guider_ui.screen_Service_Due);
			g_Previous_Service_TT_Status = (uint8_t)FALSE;
		}
		else
		{
			/* No valid state*/
		}
	}
	else
	{
		/* No Changes Done Here */
	}
}

void Telltale_Previous_Entry(void)
{
	g_Previous_FoglampValue_U8 = 0xFF;
	g_Previous_EngineTTValue_U8 = 0xFF;
	g_Previous_OilTTValue_U8 = 0xFF;
	g_Previous_Service_TT_Status = 0xFF;
	g_Previous_Flash_bl = FALSE;

}

void ABS_TT_Set_ON(void)
{
	g_ABS_TT_ON_Status = TRUE;
}

void ABS_TT_Set_OFF(void)
{
	g_ABS_TT_ON_Status = FALSE;
}

uint8_t HMI_Setting_Screen_Navigation(void)
{
	uint8_t fl_result_u8 = 0;
	uint16_t fl_Speedo_Value_u16 = 0;

	/* Get vehicle speed */
	fl_Speedo_Value_u16 = Get_display_Speed();

	/* displayed vehicle speed should be less than 10kms */
	if (fl_Speedo_Value_u16 < HMI_USM_ALLOWED_VEHICLE_SPEED)
	{
		fl_result_u8 = 0;
	}
	else
	{
		fl_result_u8 = 1;
	}

	return (fl_result_u8);
}

void GUI_Setting_Screen_Telltale_Handler(void)
{

	uint8_t fl_FogLamp_TT_ON_Status_u8;
	uint8_t fl_EngineFault_TT_ON_Status_u8;
	uint8_t fl_OilPressure_TT_ON_Status_u8;
	uint8_t fl_TractionControl_TT_ON_Status_u8;
	uint8_t fl_Service_Remainder_TT_Status_u8;

	fl_FogLamp_TT_ON_Status_u8 = Swc_Fog_LAmp_Get_Value();
	fl_EngineFault_TT_ON_Status_u8 = Swc_Mil_Tft_Get_Value();
	fl_OilPressure_TT_ON_Status_u8 = Swc_Oil_Pressure_Get_Value();

	/* Get service remainder telltale status */
	fl_Service_Remainder_TT_Status_u8 = Swc_Service_Remainder_Get_TT_Status();

	fl_TractionControl_TT_ON_Status_u8 = 0;

	/* Low Fuel Warning Indicator */
	if (0 != g_LowFuel_TT_ON_Status_u8)
	{
		/*  Flush the Orange Icon, which is assigned for Button Pressed */

		g_FuelTTFlash_u16++;
		if (g_FuelTTFlash_u16 == 5)
		{
		}
		else if (g_FuelTTFlash_u16 == 10)
		{
			g_FuelTTFlash_u16 = 0;
		}
	}
	else
	{
		/*  Flush the White Icon, which is assigned for Button Pressed */
		// lv_imgbtn_set_state(guider_ui.Setting_Screen_FuelWarning, 1);
	}

	/* High Beam Indicator */
	if (0 == fl_FogLamp_TT_ON_Status_u8)
	{
		/*  Flush the Green Icon, which is assigned for Button Pressed */
		lv_imgbtn_set_state(guider_ui.Setting_Screen_FogLampTT, 1);
	}
	else
	{
		/*  Flush the White Icon, which is assigned for Button Released */
		lv_imgbtn_set_state(guider_ui.Setting_Screen_FogLampTT, 0);
	}

	/* Engine Indicator */
	if (0 != fl_EngineFault_TT_ON_Status_u8)
	{
		/*  Flush the Green Icon, which is assigned for Button Pressed */
		lv_imgbtn_set_state(guider_ui.Setting_Screen_imgEngineTT, 0);
	}
	else
	{
		/*  Flush the White Icon, which is assigned for Button Released */
		lv_imgbtn_set_state(guider_ui.Setting_Screen_imgEngineTT, 1);
	}

	/* Oil Pressure Warning Indicator */
	if (0 != fl_OilPressure_TT_ON_Status_u8)
	{
		/*  Flush the Green Icon, which is assigned for Button Pressed */
		lv_imgbtn_set_state(guider_ui.Setting_Screen_imgOilTelltale, 0);
		set_obj_opa(guider_ui.Setting_Screen_imgOilTelltale, 255);
	}
	else
	{
		/*  Flush the White Icon, which is assigned for Button Released */
		lv_imgbtn_set_state(guider_ui.Setting_Screen_imgOilTelltale, 1);
	}

}

void HMI_Set_Service_TT_ON(void)
{
	g_Service_TT_Status = (uint8_t)TRUE;
}

void HMI_Set_Service_TT_OFF(void)
{
	g_Service_TT_Status = (uint8_t)FALSE;
}

uint8_t get_NVM_Status(void)
{
	return g_NVM_Busy_u8;
}

void Set_NVM_Status(void)
{
	g_NVM_Busy_u8 = 1;
}

void Clear_NVM_Status(void)
{
	g_NVM_Busy_u8 = 0;
}

bool Lvgl_Get_Active_Screen(void)
{
	lv_obj_t *active_Scr;
	bool fl_Ret_Status = FALSE;

	active_Scr = lv_scr_act();

	if (active_Scr == guider_ui.screen)
	{
		fl_Ret_Status = TRUE;
	}

	return (fl_Ret_Status);
}

uint32_t g_HomeScreen_Flag = 0;

void GUiTachoHandler(void)
{
	if (g_HomeScreen_Flag == 1)
	{
		g_current_tacho_index_u8 = HMI_Tacho_Rend_Get_Img_Index();
		/* Animation Image */
		// set_obj_opa(guider_ui.screen_TachoBar0_1, 255);
		lv_img_set_src(guider_ui.screen_TachoBar0_1, g_tacho_img_table[g_current_tacho_index_u8].g_tacho_img);
		lv_obj_set_pos(guider_ui.screen_TachoBar0_1, g_tacho_img_table[g_current_tacho_index_u8].Feature_text_X, g_tacho_img_table[g_current_tacho_index_u8].Feature_text_Y);
		lv_obj_set_size(guider_ui.screen_TachoBar0_1, g_tacho_img_table[g_current_tacho_index_u8].Feature_text_W, g_tacho_img_table[g_current_tacho_index_u8].Feature_text_H);
	}
}

void GUI_Fuelmeter_Handler(void)
{

	uint8_t fl_Fault_St_u8;
	uint8_t fl_Fuel_Bar_In_Display_u8;
	uint8_t fl_fuel03_Init_Finished_bl;

	fl_Fault_St_u8 = Swc_Fuel_Gauge_Get_Fault_Status();

	fl_Fuel_Bar_In_Display_u8 = Fuel_Guage_Get_Current_Bar_Level();

	/* Get fuel03 package init finished status */
	fl_fuel03_Init_Finished_bl = fuel03_init_finished();
	lv_obj_set_pos(guider_ui.screen_Fuelbar0, 41, 265);
	if (fl_fuel03_Init_Finished_bl == TRUE)
	{
		if ((g_previous_fl_Fault_St_u8 != fl_Fault_St_u8) || (g_Fuel_Bar_In_Display_u8 != fl_Fuel_Bar_In_Display_u8) || (g_Performance_checking_flag_u8 == TRUE))
		{
			g_previous_fl_Fault_St_u8 = fl_Fault_St_u8;
			g_Fuel_Bar_In_Display_u8 = fl_Fuel_Bar_In_Display_u8;

			if (g_Fuel_Inital_Update_bl == FALSE)
			{
				/* Update current fuel bar - image index to show directly*/
				HMI_Fuel_Gauge_Initial_Update();

				g_Fuel_Inital_Update_bl = TRUE;
			}
			/* No Bar Blinkning */
			if (g_previous_fl_Fault_St_u8 == FUEL03_STATUS_OPEN)
			{

				if ((g_Flash_Status_bl == TRUE) && (g_Previous_Flash_bl == FALSE))
				{
					lv_img_set_src(guider_ui.screen_Fuelbar0, &new_fuel_8);
					lv_obj_clear_flag(guider_ui.screen_E_F_Img, LV_OBJ_FLAG_HIDDEN);
					lv_obj_clear_flag(guider_ui.screen_F_Img, LV_OBJ_FLAG_HIDDEN);
					lv_obj_set_size(guider_ui.screen_Fuelbar0, 158, 43);
					g_Previous_Flash_bl = TRUE;
				}
				else if ((g_Flash_Status_bl == FALSE) && (g_Previous_Flash_bl == TRUE))
				{

					lv_img_set_src(guider_ui.screen_Fuelbar0, &img_fuel_grey_bg_white_icon);
					lv_obj_add_flag(guider_ui.screen_E_F_Img, LV_OBJ_FLAG_HIDDEN);
					lv_obj_add_flag(guider_ui.screen_F_Img, LV_OBJ_FLAG_HIDDEN);
					lv_obj_set_size(guider_ui.screen_Fuelbar0, 158, 43);
					g_Previous_Flash_bl = FALSE;
				}
			}
			else if (g_previous_fl_Fault_St_u8 == FUEL03_STATUS_SHORT)
			{
				g_Fuel_Short_Flash_u8++;

				if ((g_Flash_Status_bl == TRUE) && (g_Previous_Flash_bl == FALSE))
				{
					lv_obj_clear_flag(guider_ui.screen_E_F_Img, LV_OBJ_FLAG_HIDDEN);
					lv_obj_clear_flag(guider_ui.screen_F_Img, LV_OBJ_FLAG_HIDDEN);
					g_Previous_Flash_bl = TRUE;
				}
				else if ((g_Flash_Status_bl == FALSE) && (g_Previous_Flash_bl == TRUE))
				{
					g_Fuel_Short_Flash_u8 = 0;
					lv_obj_add_flag(guider_ui.screen_E_F_Img, LV_OBJ_FLAG_HIDDEN);
					lv_obj_add_flag(guider_ui.screen_F_Img, LV_OBJ_FLAG_HIDDEN);
					g_Previous_Flash_bl = FALSE;
				}

				lv_img_set_src(guider_ui.screen_Fuelbar0, &new_fuel_8);
				lv_obj_set_size(guider_ui.screen_Fuelbar0, 158, 43);
			}

			else if (g_previous_fl_Fault_St_u8 == FUEL03_STATUS_NO_OPEN_SHORT)
			{
				if (g_Previous_Fuel_Bar_In_Display_u8 != g_Fuel_Bar_In_Display_u8)
				{
					if ((g_Fuel_Bar_In_Display_u8 <= 7) && (g_Fuel_Bar_In_Display_u8 > 0))
					{
						GUI_Fuel_Gauge_Handler(g_Fuel_Bar_In_Display_u8);
					}

					/* E AND F CAHPLET FOR FUEL GAUGE*/
					lv_obj_clear_flag(guider_ui.screen_E_F_Img, LV_OBJ_FLAG_HIDDEN);
					lv_obj_clear_flag(guider_ui.screen_F_Img, LV_OBJ_FLAG_HIDDEN);
					g_Previous_Fuel_Bar_In_Display_u8 = g_Fuel_Bar_In_Display_u8;
				}
				else
				{
					/* Do Nothing */
				}
			}
			else
			{
				/*do nothing*/
			}
		}
	}
	else
	{
		g_LowFuel_TT_ON_Status_u8 = 0;

		lv_img_set_src(guider_ui.screen_Fuelbar0, &fuel_0_orange);
		lv_obj_clear_flag(guider_ui.screen_E_F_Img, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_F_Img, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_size(guider_ui.screen_Fuelbar0, 158, 43);
	}
}

void GUI_Fuel_Gauge_Handler(uint8_t Current_Bar_Level)
{
	uint8_t fl_Img_Index = HMI_FUEL_BAR_Image_Cfg[Current_Bar_Level];

	/* Fuel bar image index for current bar level*/
	g_Fuel_Img_Index = fl_Img_Index;

	/* Lvgl image flush invocation */
	lv_img_set_src(guider_ui.screen_Fuelbar0, g_fuel_img_table[g_Fuel_Img_Index].g_fuel_img);
	lv_obj_set_pos(guider_ui.screen_Fuelbar0, g_fuel_img_table[g_Fuel_Img_Index].Feature_fuel_text_X, g_fuel_img_table[g_Fuel_Img_Index].Feature_fuel_text_Y);
	lv_obj_set_size(guider_ui.screen_Fuelbar0, g_fuel_img_table[g_Fuel_Img_Index].Feature_fuel_text_W, g_fuel_img_table[g_Fuel_Img_Index].Feature_fuel_text_H);
}

void HMI_Fuel_Gauge_Initial_Update(void)
{
	uint8_t fl_Fuel_Bar_Level_u8;

	if (g_Fuel_Bar_In_Display_u8 == 0)
	{
		/* LFW State */
		g_Fuel_Img_Index = HMI_FUEL_BAR_Image_Cfg[(g_Fuel_Bar_In_Display_u8 + 1)];
	}
	else
	{
		/* Upon IGN Cycle, Fuel bar has to update immediately rather than step wise*/
		g_Fuel_Img_Index = HMI_FUEL_BAR_Image_Cfg[g_Fuel_Bar_In_Display_u8];
	}
}

void HMI_Set_FUEL_FLASH_ON(void)
{
	g_Flash_Status_bl = TRUE;
}

void HMI_Set_FUEL_FLASH_OFF(void)
{
	g_Flash_Status_bl = FALSE;
}

void eLCDIF_IRQHandler(void)
{
	uint32_t intStatus;

	intStatus = ELCDIF_GetInterruptStatus(LCDIF);

	ELCDIF_ClearInterruptStatus(LCDIF, intStatus);

	if (intStatus & kELCDIF_CurFrameDone)
	{
		if (s_frameDone == true)
		{
			lv_disp_flush_ready(disp_drv_Flush); /* Indicate you are ready with the flushing*/

			/* clear status as display flushing is done*/
			s_frameDone = false;
		}
	}
	SDK_ISR_EXIT_BARRIER;
}

//__attribute__ ((used, section("lvglbuffer")))
__attribute__((section("lvglbuffer,\"aw\",%nobits @")))
uint16_t LVGL_Buffer[1][240 * 320];
void lvgl_app_int(void)
{
	// LVGL INIT

#if LV_USE_GPU_NXP_VG_LITE
#include "lvgl/src/draw/nxp_vglite/lv_vglite_utils.h"
#endif

#if LV_USE_GPU_NXP_VG_LITE
	VG_LITE_COND_STOP(vg_lite_init(64, 64) != VG_LITE_SUCCESS, "VGLite init failed.");
#endif

	lv_init();
	lv_disp_draw_buf_init(&draw_buf, LVGL_Buffer[0], NULL,
						  LCDIF_PANEL_WIDTH * LCDIF_PANEL_HEIGHT); /*Initialize the display buffer.*/
	lv_disp_drv_init(&disp_drv);								   /*Basic initialization*/
	disp_drv.flush_cb = my_disp_flush;							   /*Set your driver function*/
	disp_drv.draw_buf = &draw_buf;								   /*Assign the buffer to the display*/
	disp_drv.hor_res = LCDIF_PANEL_WIDTH;						   /*Set the horizontal resolution of the display*/
	disp_drv.ver_res = LCDIF_PANEL_HEIGHT;						   /*Set the vertical resolution of the display*/
	disp_drv.full_refresh = 1;

	lv_disp_drv_register(&disp_drv); /*Finally register the driver*/
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
	int32_t x, y;
	/*It's a very slow but simple implementation.
	 *`set_pixel` needs to be written by you to a set pixel on the screen*/
	frameBufferIndex ^= 1U;
	for (y = area->y1; y <= area->y2; y++)
	{
		for (x = area->x1; x <= area->x2; x++)
		{
			// set_pixel(x, y, *color_p);
			LCDIF_Buffer[0][y][x] = (uint16_t)color_p->full;
			color_p++;
		}
	}


	/* Buffer copy from LVGL buffer to LCDIF buffer is done */
	s_frameDone = TRUE;

	ELCDIF_SetNextBufferAddr(LCDIF,
							 (uint32_t)LCDIF_Buffer[0]);

	/* copy display driver to global structure*/
	disp_drv_Flush = disp;
}

void FuelValueEntry(void)
{
	g_Previous_Fuel_Bar_In_Display_u8 = 0xFF;
}

void SwTimerCallback(void)
{

	lv_tick_inc(5);
}

/*!
 * @brief Initialization of TFT Buffers
 */
void TFT_Buffers_Init(void)
{
	/* Initializes Lvgl buffer to zero */
	memset(&LVGL_Buffer[0], 0x00, (LCDIF_PANEL_WIDTH * LCDIF_PANEL_HEIGHT * 2));

	/* Initializes LCDIF buffer to zero */
	memset(&LCDIF_Buffer[0], 0x00, (LCDIF_PANEL_WIDTH * LCDIF_PANEL_HEIGHT * 2));
}

void LCDIF_ClearAndUpdateLCDBuffer(void)
{
	/* Initializes LCDIF buffer to zero */
	memset(&LCDIF_Buffer[0], 0x00, (LCDIF_PANEL_WIDTH * LCDIF_PANEL_HEIGHT * 2));
}

void lvgl_task(void *pvParameters)
{
	bool fl_Sys_Ready_St_bl = FALSE;
	const TickType_t xDelay = 100 / portTICK_PERIOD_MS;
	Lvgl_Display_Init();
	
	while (1)
	{

		if((Sys_Service_Get_Ignition_State() ==IGN_ON) &&
		  (Sys_Service_Get_High_Voltage_State() == SYSTEM_SERVICE_NOT_SET) &&
		  (Sys_Service_Get_Low_Voltage_State() == SYSTEM_SERVICE_NOT_SET))
		{
			/* New update will happpen after completing previous frame rendering and flushing to the display*/
			if (s_frameDone == false)
			{
				/* handling the screen transition and its HMI things */
				GUI_Screen_Handler();
				frameBufferIndex ^= 1U;

				/* content from lvgl buffer is copied to LCDBuffer*/
				lv_timer_handler();
				
			}
		}
		else
		{
			/* if interruption occures due to LVSD,HVSD when animation screen is loading ,
			 * Animation will be skipped , move to main screen Upon recovery from Abnormal state*/
			if (g_Welcome_Animation_Status_en == WELCOME_ANIMATION_INPROGRESS)
			{
				/* Trigger Event*/
				HMI_Animation_To_Main_Screen_Event_Trigger();
			}
			else
			{
				/* do nothing*/
			}
		}
		
		vTaskDelay(5);
	}
}

void HMI_Early_Wake_Up_Animation_Control(void)
{

	Enter_Critic_Section();

	NVIC_SystemReset();
}

void Lvgl_Display_Init(void)
{
	setup_ui(&guider_ui);
	events_init(&guider_ui);
	custom_init(&guider_ui);
}

void screen_busy(void)
{
	s_frameDone = false;
	/* Wait for previous frame complete. */
	while (!s_frameDone)
	{
	}
}

/*!
 * @brief Stack overflow hook.
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
	(void)pcTaskName;
	(void)xTask;

	for (;;)
		;
}

void Handle_Bar_Set_Btn_CBK(uint8_t Button_Status)
{

	/*Check if  Button pressed (with 200 ms)*/
	if (1u == Button_Status)
	{

		g_Handle_Bar_Btn_Status_u8[HANDLER_BAR_SET_BUTTON] = BUTTON_SHORT_PRESSED;
	}
	else if (2u == Button_Status)
	{
		/* Button pressed for 2sec */
		g_Handle_Bar_Btn_Status_u8[HANDLER_BAR_SET_BUTTON] = BUTTON_LONG_PRESSED;
	}
}

void Handle_Bar_Up_Btn_CBK(uint8_t Button_Status)
{

	/*Check if  Button pressed (with 200 ms)*/
	if (1u == Button_Status)
	{

		g_Handle_Bar_Btn_Status_u8[HANDLER_BAR_UP_BUTTON] = BUTTON_SHORT_PRESSED;
	}
	else if (2u == Button_Status)
	{
		/* Button pressed for 2sec */
		g_Handle_Bar_Btn_Status_u8[HANDLER_BAR_UP_BUTTON] = BUTTON_LONG_PRESSED;
	}
	else if (3u == Button_Status)
	{
		/* Button long press and hold */
		g_Handle_Bar_Btn_Status_u8[HANDLER_BAR_UP_BUTTON] = BUTTON_LONG_PRESS_AND_HOLD;
	}
}

void Handle_Bar_Down_Btn_CBK(uint8_t Button_Status)
{
	/*Check if  Button pressed (with 200 ms)*/
	if (1u == Button_Status)
	{
		g_Handle_Bar_Btn_Status_u8[HANDLER_BAR_DOWN_BUTTON] = BUTTON_SHORT_PRESSED;
	}
	else if (2u == Button_Status)
	{
		/* Button pressed for 2sec */
		g_Handle_Bar_Btn_Status_u8[HANDLER_BAR_DOWN_BUTTON] = BUTTON_LONG_PRESSED;
	}
	else if (3u == Button_Status)
	{
		/* Button long press and hold */
		g_Handle_Bar_Btn_Status_u8[HANDLER_BAR_DOWN_BUTTON] = BUTTON_LONG_PRESS_AND_HOLD;
	}
}

void Handle_Bar_Return_Btn_CBK(uint8_t Button_Status)
{
	/*Check if  Button pressed (with 200 ms)*/
	if (1u == Button_Status)
	{
		g_Handle_Bar_Btn_Status_u8[HANDLER_BAR_RETURN_BUTTON] = BUTTON_SHORT_PRESSED;
	}
	else if (2u == Button_Status)
	{
		/* Button pressed for 2sec */
		g_Handle_Bar_Btn_Status_u8[HANDLER_BAR_RETURN_BUTTON] = BUTTON_LONG_PRESSED;
	}
}

uint8_t HMI_Get_Handle_Bar_Btn_Status(BM_List_Index_Type_En p_Button_ID)
{
	uint8_t fl_result_u8 = 0;

	if (p_Button_ID < MAX_BUTTON_LIST)
	{
		fl_result_u8 = (g_Handle_Bar_Btn_Status_u8[p_Button_ID]);
	}
	else
	{
		fl_result_u8 = 0xFF;
	}

	/* return handle bar button status */
	return (fl_result_u8);
}

static void Clear_Btn_Events(void)
{
	uint8_t fl_loop_Idx = 0;

	for (fl_loop_Idx = 0; fl_loop_Idx < TOTAL_BUTTON; fl_loop_Idx++)
	{
		/* Clear All button status */
		g_Handle_Bar_Btn_Status_u8[fl_loop_Idx] = BUTTON_RELEASED;
	}
}

void GUI_Main_Screen_Entry(void)
{

	lv_obj_clear_flag(guider_ui.screen_imgKmph, LV_OBJ_FLAG_HIDDEN);

	/* Pos For No Image in Trip Home Screen Circle*/
	lv_obj_move_background(guider_ui.screen_Fuel_low_mMarker);
	

	lv_obj_set_pos(guider_ui.screen_con_odo_val, 37, 96);
	lv_obj_set_size(guider_ui.screen_con_odo_val, 69, 19);
	lv_img_set_src(guider_ui.screen_conkm, &txt_night_odo_unit);
	lv_obj_set_pos(guider_ui.screen_conkm, 109, 103);
	lv_obj_set_size(guider_ui.screen_conkm, 20, 15);

	static uint8_t x = 1;
	static uint8_t y = 103;
	lv_obj_set_pos(guider_ui.screen_Codo, x, y);
	lv_obj_set_size(guider_ui.screen_Codo, 27, 14);
	lv_img_set_src(guider_ui.screen_Sub_Con, &_Layer_0_9x9);

	fl_Get_Current_Time_Foramt_Lvgl_App = GUI_Get_Time_Format();

	if (fl_Get_Current_Time_Foramt_Lvgl_App == CLOCK_12HR_FORMAT)
	{
		GUI_Main12hr_position();
	}
	else
	{
		GUI_Main24hr_position();
	}

	lv_obj_set_style_text_color(guider_ui.screen_con_odo_val, lv_color_night_orange(), 0);
	set_obj_opa_S(guider_ui.screen_con_odo_val, 0);
}

void Odo_MainScreen_Entry(void)
{
	g_Previous_ODOValue_u32 = 0;
}

void GUI_Main_Screen_Day(void)
{
	uint32_t fl_ODOValue_u32 = Swc_Get_Display_ODO_Value();
	uint32_t fl_Unit_Selection_u32 = Distance_fn();
	uint8_t var = 0;

	if (g_Previous_ODOValue_u32 != fl_ODOValue_u32)
	{

		if (fl_ODOValue_u32 == ODO_INVALID_STATE)
		{
			lv_label_set_text(guider_ui.screen_main_odo_lbl, "------");
		}
		else
		{
			lv_label_set_text_fmt(guider_ui.screen_main_odo_lbl, "%d", fl_ODOValue_u32);
		}

		g_Previous_ODOValue_u32 = fl_ODOValue_u32;
	}
	else
	{
		/* Do Nothing */
	}
}

void GUI_Main_Screen(void)
{

	uint32_t fl_ODOValue_u32 = Swc_Get_Display_ODO_Value();
	uint32_t fl_Unit_Selection_u32 = Distance_fn();
	uint8_t var = 0;

	if (g_Previous_ODOValue_u32 != fl_ODOValue_u32)
	{

		if (fl_ODOValue_u32 == ODO_INVALID_STATE)
		{
			lv_label_set_text(guider_ui.screen_con_odo_val, "------");
		}
		else
		{
			lv_label_set_text_fmt(guider_ui.screen_con_odo_val, "%d", fl_ODOValue_u32);
		}

		g_Previous_ODOValue_u32 = fl_ODOValue_u32;
	}
	else
	{
		/* Do Nothing */
	}
}

void HMI_TRIP_Timer_SW_Reset_Cmd(uint8_t p_Trip_ID)
{
	/* inform trip odo to reset */
	ODO_TripSwitch_Reset(p_Trip_ID);

	/* inform trip timer to reset */
	Swc_Trip_Timer_Reset(p_Trip_ID);

	/* Inform average speed to reset*/
	Swc_Average_Speed_Reset(p_Trip_ID);

	/* Inform AFE to reset */
	Swc_AFE_SW_Reset(p_Trip_ID);
}

static void HMI_Setting_Screen_Change(void)
{

	lv_obj_del(lv_scr_act());

	setup_scr_Setting_Screen(&guider_ui);

	lv_scr_load(guider_ui.Setting_Screen);
	events_init(&guider_ui);
	custom_init(&guider_ui);
}

void RTC_Set_User_Selected_Date(uint8_t p_day_u8, uint8_t p_month_u8, uint16_t p_year_u16)
{
	/* Get current time from RTC To avoid exception for wrong value*/
	Get_Date_Time(&g_Date_Time_St);

	g_display_datetime.day = p_day_u8;
	g_display_datetime.month = p_month_u8;
	g_display_datetime.year = p_year_u16;
	g_display_datetime.hour = g_Date_Time_St.hour;
	g_display_datetime.minute = g_Date_Time_St.minute;
	g_display_datetime.second = 00;

	RTC_Set_Date_time(g_RTC_SNVS_Base_Add, &g_display_datetime);
}

void Get_Date_Time(g_RTC_DATE_TIME_ST *p_Date_Time_st)
{
	/* Get data from RTC */
	g_display_datetime = RTC_Time_Display();

	p_Date_Time_st->hour = g_display_datetime.hour;

	p_Date_Time_st->minute = g_display_datetime.minute;

	p_Date_Time_st->day = g_display_datetime.day;

	p_Date_Time_st->month = g_display_datetime.month;

	p_Date_Time_st->year = g_display_datetime.year;
}

void RTC_Set_User_Selected_Time(uint8_t p_Hour_u8, uint8_t p_Min_u8)
{
	uint8_t fl_Time_Format_u8 = GUI_Get_Time_Format();
	uint8_t fl_Time_Meridian = GUI_am_pm_Setting();

	/* Get current Date */
	Get_Date_Time(&g_Date_Time_St);

	if ((fl_Time_Meridian == 2) && (fl_Time_Format_u8 == CLOCK_12HR_FORMAT) && (p_Hour_u8 != 12))
	{
		/* Covert time in PM to 24hrs format except 12:00 PM*/
		p_Hour_u8 = p_Hour_u8 + 12;
	}
	else if ((p_Hour_u8 == 12) && (fl_Time_Meridian == 1) && (fl_Time_Format_u8 == CLOCK_12HR_FORMAT))
	{
		/* 12:00 AM has to be stored as 00:00 */
		p_Hour_u8 = 0;
	}

	g_display_datetime.day = g_Date_Time_St.day;
	g_display_datetime.month = g_Date_Time_St.month;
	g_display_datetime.year = g_Date_Time_St.year;
	g_display_datetime.hour = p_Hour_u8;
	g_display_datetime.minute = p_Min_u8;
	g_display_datetime.second = 00;
	RTC_Set_Date_time(g_RTC_SNVS_Base_Add, &g_display_datetime);
}

void Lvgl_Screen_Change_Req_Process(SCREEN_TRANSITON_EN p_screen_en)
{
	if (p_screen_en == SETTING_SCREEN_TO_MAIN_SCREEN)
	{

		HMI_CLK_NVM_check();

		HMI_Main_Screen_Cold_Init();

		/* change current screen to main screen */
		g_HMI_Screen_PST_State_u8 = HMI_PST_HOME_SCREEN;
		// g_HMI_Screen_PST_State_u8 = HMI_BLOCK_STATE;
	}
	else if (p_screen_en == MAIN_SCREEN_TO_SETTING_SCREEN)
	{

		/* change current screen state to setting screen*/
		g_HMI_Screen_PST_State_u8 = HMI_PST_SETTING_SCREEN;
	}
	else if (p_screen_en == SETTING_SCREEN_TO_INTERMEDIATE_SCREEN)
	{

		lv_obj_del(lv_scr_act());

		Idle_Main_Screen(&guider_ui);

		lv_scr_load(guider_ui.screen);
		events_init(&guider_ui);
		custom_init(&guider_ui);

		/* Initialize Main screen */
		HMI_Intermediate_Screen_Cold_Init();

		HMI_Load_Intermediate_Screen();

		/* change current screen to main screen */
		g_HMI_Screen_PST_State_u8 = HMI_PST_HOME_SCREEN;
	}
	else if (p_screen_en == INTERMEDIATE_SCREEN_TO_SETTING_SCREEN)
	{

		lv_obj_del(lv_scr_act());

		Idle_Setting_Screen(&guider_ui);

		lv_scr_load(guider_ui.Setting_Screen);
		events_init(&guider_ui);
		custom_init(&guider_ui);

		/* change current screen state to setting screen*/
		g_HMI_Screen_PST_State_u8 = HMI_PST_SETTING_SCREEN;
	}
}

extern uint8_t setting_debug;
extern bool g_Main_To_Other_Screen_Change_Req_Status;

void HomeScreenExit(void)
{
	lv_obj_del(lv_scr_act());
	Idle_Setting_Screen(&guider_ui);
	g_HMI_Screen_PST_State_u8 = HMI_BLOCK_STATE;
}

void SettingScreenEntry(void)
{
	lv_scr_load(guider_ui.Setting_Screen);
	events_init(&guider_ui);
	custom_init(&guider_ui);
	GUI_Setting_mainscr_night_entry();
	g_HMI_Screen_PST_State_u8 = HMI_BLOCK_STATE;
	lv_obj_add_flag(guider_ui.Setting_Screen_setting_trip_day_container, LV_OBJ_FLAG_HIDDEN);
}

void memp(char *s)
{

	lv_mem_monitor_t mon;
	lv_mem_monitor(&mon);
}

void hmi_reset(void)
{
}

void GUI_Service_remainder_Position_Text(void)
{
}

void set_obj_opa(lv_obj_t *text, uint8_t value)
{

	lv_style_value_t v = {
		.num = (int32_t)value};
	lv_obj_set_local_style_prop(text, LV_STYLE_IMG_OPA, v, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void set_obj_opa_S(lv_obj_t *text_S, uint8_t value_S)
{
	lv_style_value_t v = {
		.num = (int32_t)value_S};
	lv_obj_set_local_style_prop(text_S, LV_STYLE_BG_OPA, v, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void Intermediate_Speedo_Entry(void)
{

	g_Previous_ISpeedo_Value_u16 = 0;
}

void GUI_Intermediate_Speedometer_Handler(void)
{

	uint8_t DigitI_Value_1_u8 = 0;
	uint8_t DigitI_Value_2_u8 = 0;
	uint8_t DigitI_Value_3_u8 = 0;

	g_ISpeedo_Value_u16 = Get_display_Speed();

	if (g_Previous_ISpeedo_Value_u16 != g_ISpeedo_Value_u16)
	{

		lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP0_24x47);
		lv_obj_set_style_img_opa(guider_ui.screen_trip_spedo_s1, 255, 0);
		lv_obj_set_style_img_recolor(guider_ui.screen_trip_spedo_s1, lv_color_white(), 0);

		DigitI_Value_1_u8 = (g_ISpeedo_Value_u16) % 10;
		DigitI_Value_2_u8 = (((g_ISpeedo_Value_u16)-DigitI_Value_1_u8) % 100) / 10;
		DigitI_Value_3_u8 = (((g_ISpeedo_Value_u16) - (DigitI_Value_2_u8 * 10)) % 1000) / 100;

		if (g_ISpeedo_Value_u16 >= SPEED_MAX)
		{
			lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP9_24x47);
			lv_obj_set_style_img_opa(guider_ui.screen_trip_spedo_s1, 255, 0);
			lv_obj_set_style_img_recolor(guider_ui.screen_trip_spedo_s1, lv_color_white(), 0);

			lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP9_24x47);
			lv_obj_set_style_img_opa(guider_ui.screen_trip_spedo_s2, 255, 0);
			lv_obj_set_style_img_recolor(guider_ui.screen_trip_spedo_s2, lv_color_white(), 0);

			lv_img_set_src(guider_ui.screen_trip_spedo_s3, &_ISP1_24x47);
			lv_obj_set_style_img_opa(guider_ui.screen_trip_spedo_s3, 255, 0);
			lv_obj_set_style_img_recolor(guider_ui.screen_trip_spedo_s3, lv_color_white(), 0);

			set_obj_opa(guider_ui.screen_trip_spedo_s3, 255);
			set_obj_opa(guider_ui.screen_trip_spedo_s2, 255);
			set_obj_opa(guider_ui.screen_trip_spedo_s1, 255);

			lv_img_set_src(guider_ui.screen_imgKmph, &_txt_night_speed_unit_33x19);
			set_obj_opa(guider_ui.screen_imgKmph, 255);
		}
		else
		{
			if ((g_ISpeedo_Value_u16 >= 0) && (g_ISpeedo_Value_u16 < 10))
			{

				lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_trip_spedo_s1, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_trip_spedo_s1, lv_color_white(), 0);

				lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_trip_spedo_s2, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_trip_spedo_s2, lv_color_Intermediate_Grey(), 0);
				set_obj_opa(guider_ui.screen_trip_spedo_s2, 50);

				lv_img_set_src(guider_ui.screen_trip_spedo_s3, &_ISP0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_trip_spedo_s3, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_trip_spedo_s3, lv_color_Intermediate_Grey(), 0);
				set_obj_opa(guider_ui.screen_trip_spedo_s3, 50);

				lv_img_set_src(guider_ui.screen_imgKmph, &_txt_night_speed_unit_33x19);
				set_obj_opa(guider_ui.screen_imgKmph, 255);
			}
			else if ((g_ISpeedo_Value_u16 >= 10) && (g_ISpeedo_Value_u16 < 100))
			{
				lv_img_set_src(guider_ui.screen_trip_spedo_s3, &_ISP0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_trip_spedo_s3, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_trip_spedo_s3, lv_color_Intermediate_Grey(), 0);
				set_obj_opa(guider_ui.screen_trip_spedo_s3, 50);

				lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_trip_spedo_s2, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_trip_spedo_s2, lv_color_white(), 0);

				lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_trip_spedo_s1, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_trip_spedo_s1, lv_color_white(), 0);

				if ((DigitI_Value_2_u8 >= 0) && (DigitI_Value_2_u8 <= 9))
				{

					Speed_DigitI(DigitI_Value_2_u8, 1);
				}
				else
				{
				}
			}
			else if ((g_ISpeedo_Value_u16 >= 100) && (g_ISpeedo_Value_u16 < 1000))
			{
				lv_img_set_src(guider_ui.screen_trip_spedo_s3, &_ISP0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_trip_spedo_s1, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_trip_spedo_s1, lv_color_white(), 0);

				lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_trip_spedo_s2, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_trip_spedo_s2, lv_color_white(), 0);

				lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_trip_spedo_s3, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_trip_spedo_s3, lv_color_white(), 0);

				if ((DigitI_Value_3_u8 >= 0) && (DigitI_Value_3_u8 <= 9))
				{

					Speed_DigitI(DigitI_Value_3_u8, 2);
				}
				if ((DigitI_Value_2_u8 >= 0) && (DigitI_Value_2_u8 <= 9))
				{

					Speed_DigitI(DigitI_Value_2_u8, 1);
				}
			}
			else
			{
			}

			if (DigitI_Value_1_u8 == 0)
			{
				lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP0_24x47);
				set_obj_opa(guider_ui.screen_trip_spedo_s1, 255);

				lv_img_set_src(guider_ui.screen_imgKmph, &_txt_night_speed_unit_33x19);
				set_obj_opa(guider_ui.screen_imgKmph, 255);
			}
			else if (DigitI_Value_1_u8 == 1)
			{
				lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP1_24x47);
				set_obj_opa(guider_ui.screen_trip_spedo_s1, 255);
			}
			else if (DigitI_Value_1_u8 == 2)
			{
				lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP2_24x47);
				set_obj_opa(guider_ui.screen_trip_spedo_s1, 255);
			}
			else if (DigitI_Value_1_u8 == 3)
			{
				lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP3_24x47);
				set_obj_opa(guider_ui.screen_trip_spedo_s1, 255);
			}
			else if (DigitI_Value_1_u8 == 4)
			{
				lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP4_24x47);
				set_obj_opa(guider_ui.screen_trip_spedo_s1, 255);
			}
			else if (DigitI_Value_1_u8 == 5)
			{
				lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP5_24x47);
				set_obj_opa(guider_ui.screen_trip_spedo_s1, 255);
			}
			else if (DigitI_Value_1_u8 == 6)
			{
				lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP6_24x47);
				set_obj_opa(guider_ui.screen_trip_spedo_s1, 255);
			}
			else if (DigitI_Value_1_u8 == 7)
			{
				lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP7_24x47);
				set_obj_opa(guider_ui.screen_trip_spedo_s1, 255);
			}
			else if (DigitI_Value_1_u8 == 8)
			{
				lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP8_24x47);
				set_obj_opa(guider_ui.screen_trip_spedo_s1, 255);
			}
			else if (DigitI_Value_1_u8 == 9)
			{
				lv_img_set_src(guider_ui.screen_trip_spedo_s1, &_ISP9_24x47);
				set_obj_opa(guider_ui.screen_trip_spedo_s1, 255);
			}
		}
		g_Previous_ISpeedo_Value_u16 = g_ISpeedo_Value_u16;
	}
	else
	{
		/* Do Nothing */
	}
}

void Speed_DigitI(uint8_t fl_no_IDigit_u8, uint8_t DigitIn_Selection)
{
	switch (fl_no_IDigit_u8)
	{
	case 0:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP0_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s3, &_ISP0_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s3, 255);
		}
		else
		{
			/*do nothing*/
		}
		break;
	case 1:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP1_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			/*need to check*/

			lv_img_set_src(guider_ui.screen_trip_spedo_s3, &_ISP1_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s3, 255);
		}
		else
		{
			/*do nothing*/
		}
		break;

	case 2:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP2_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP2_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s2, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 3:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP3_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP3_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s2, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 4:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP4_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s3, &_ISP4_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s3, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 5:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP5_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s3, &_ISP5_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s3, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 6:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP6_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s3, &_ISP6_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s3, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 7:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP7_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s3, &_ISP7_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s3, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 8:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP8_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s3, &_ISP8_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s3, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 9:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP9_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_trip_spedo_s2, &_ISP9_24x47);
			set_obj_opa(guider_ui.screen_trip_spedo_s2, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;
	}
}

void GUI_Intermediate_Speedometer_Handler_Day(void)
{
	uint8_t DigitI_Value_1_u8 = 0;
	uint8_t DigitI_Value_2_u8 = 0;
	uint8_t DigitI_Value_3_u8 = 0;

	g_ISpeedo_Value_u16 = Get_display_Speed();

	if (g_Previous_ISpeedo_Value_u16 != g_ISpeedo_Value_u16)
	{

		DigitI_Value_1_u8 = (g_ISpeedo_Value_u16) % 10;
		DigitI_Value_2_u8 = (((g_ISpeedo_Value_u16)-DigitI_Value_1_u8) % 100) / 10;
		DigitI_Value_3_u8 = (((g_ISpeedo_Value_u16) - (DigitI_Value_2_u8 * 10)) % 1000) / 100;

		if (g_ISpeedo_Value_u16 >= SPEED_MAX)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc1, &black9_24x47);
			lv_obj_set_style_img_opa(guider_ui.screen_day_in_sc1, 255, 0);
			lv_obj_set_style_img_recolor(guider_ui.screen_day_in_sc1, lv_color_black(), 0);

			lv_img_set_src(guider_ui.screen_day_in_sc2, &black9_24x47);
			lv_obj_set_style_img_opa(guider_ui.screen_day_in_sc2, 255, 0);
			lv_obj_set_style_img_recolor(guider_ui.screen_day_in_sc2, lv_color_black(), 0);

			lv_img_set_src(guider_ui.screen_day_in_sc3, &black1_24x47);
			lv_obj_set_style_img_opa(guider_ui.screen_day_in_sc3, 255, 0);
			lv_obj_set_style_img_recolor(guider_ui.screen_day_in_sc3, lv_color_black(), 0);
		}
		else
		{
			if ((g_ISpeedo_Value_u16 >= 0) && (g_ISpeedo_Value_u16 < 10))
			{

				lv_img_set_src(guider_ui.screen_day_in_sc1, &black0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_day_in_sc1, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_day_in_sc1, lv_color_black(), 0);

				lv_img_set_src(guider_ui.screen_day_in_sc2, &black0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_day_in_sc2, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_day_in_sc2, lv_color_Day_Grey(), 0);
				set_obj_opa(guider_ui.screen_day_in_sc2, 50);

				lv_img_set_src(guider_ui.screen_day_in_sc3, &black0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_day_in_sc3, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_day_in_sc3, lv_color_Day_Grey(), 0);
				set_obj_opa(guider_ui.screen_day_in_sc3, 50);
			}
			else if ((g_ISpeedo_Value_u16 >= 10) && (g_ISpeedo_Value_u16 < 100))
			{

				lv_img_set_src(guider_ui.screen_day_in_sc3, &black0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_day_in_sc3, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_day_in_sc3, lv_color_black(), 0);
				set_obj_opa(guider_ui.screen_day_in_sc3, 50);

				lv_img_set_src(guider_ui.screen_day_in_sc2, &black0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_day_in_sc2, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_day_in_sc2, lv_color_black(), 0);

				lv_img_set_src(guider_ui.screen_day_in_sc1, &black0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_day_in_sc1, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_day_in_sc1, lv_color_black(), 0);

				if ((DigitI_Value_2_u8 >= 0) && (DigitI_Value_2_u8 <= 9))
				{

					Speed_DigitI_Day(DigitI_Value_2_u8, 1);
				}
				else
				{
				}
			}
			else if ((g_ISpeedo_Value_u16 >= 100) && (g_ISpeedo_Value_u16 < 1000))
			{

				lv_img_set_src(guider_ui.screen_day_in_sc3, &black0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_day_in_sc3, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_day_in_sc3, lv_color_black(), 0);

				lv_img_set_src(guider_ui.screen_day_in_sc2, &black0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_day_in_sc2, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_day_in_sc2, lv_color_black(), 0);

				lv_img_set_src(guider_ui.screen_day_in_sc1, &black0_24x47);
				lv_obj_set_style_img_opa(guider_ui.screen_day_in_sc1, 255, 0);
				lv_obj_set_style_img_recolor(guider_ui.screen_day_in_sc1, lv_color_black(), 0);

				if ((DigitI_Value_3_u8 >= 0) && (DigitI_Value_3_u8 <= 9))
				{

					Speed_DigitI_Day(DigitI_Value_3_u8, 2);
				}
				if ((DigitI_Value_2_u8 >= 0) && (DigitI_Value_2_u8 <= 9))
				{

					Speed_DigitI_Day(DigitI_Value_2_u8, 1);
				}
			}
			else
			{
			}

			if (DigitI_Value_1_u8 == 0)
			{
			}
			else if (DigitI_Value_1_u8 == 1)
			{

				lv_img_set_src(guider_ui.screen_day_in_sc1, &black1_24x47);
				set_obj_opa(guider_ui.screen_day_in_sc1, 255);
			}
			else if (DigitI_Value_1_u8 == 2)
			{

				lv_img_set_src(guider_ui.screen_day_in_sc1, &black2_24x47);
				set_obj_opa(guider_ui.screen_day_in_sc1, 255);
			}
			else if (DigitI_Value_1_u8 == 3)
			{

				lv_img_set_src(guider_ui.screen_day_in_sc1, &black3_24x47);
				set_obj_opa(guider_ui.screen_day_in_sc1, 255);
			}
			else if (DigitI_Value_1_u8 == 4)
			{

				lv_img_set_src(guider_ui.screen_day_in_sc1, &black4_24x47);
				set_obj_opa(guider_ui.screen_day_in_sc1, 255);
			}
			else if (DigitI_Value_1_u8 == 5)
			{

				lv_img_set_src(guider_ui.screen_day_in_sc1, &black5_24x47);
				set_obj_opa(guider_ui.screen_day_in_sc1, 255);
			}
			else if (DigitI_Value_1_u8 == 6)
			{

				lv_img_set_src(guider_ui.screen_day_in_sc1, &black6_24x47);
				set_obj_opa(guider_ui.screen_day_in_sc1, 255);
			}
			else if (DigitI_Value_1_u8 == 7)
			{
				lv_img_set_src(guider_ui.screen_day_in_sc1, &black7_24x47);
				set_obj_opa(guider_ui.screen_day_in_sc1, 255);
			}
			else if (DigitI_Value_1_u8 == 8)
			{

				lv_img_set_src(guider_ui.screen_day_in_sc1, &black8_24x47);
				set_obj_opa(guider_ui.screen_day_in_sc1, 255);
			}
			else if (DigitI_Value_1_u8 == 9)
			{

				lv_img_set_src(guider_ui.screen_day_in_sc1, &black9_24x47);
				set_obj_opa(guider_ui.screen_day_in_sc1, 255);
			}
		}

		g_Previous_ISpeedo_Value_u16 = g_ISpeedo_Value_u16;
	}
	else
	{
		/* Do Nothing */
	}
}

void Speed_DigitI_Day(uint8_t fl_no_IDigit_u8, uint8_t DigitIn_Selection)
{
	switch (fl_no_IDigit_u8)
	{
	case 0:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc2, &black0_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc3, &black0_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc3, 255);
		}
		else
		{
			/*do nothing*/
		}
		break;
	case 1:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc2, &black1_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			/*need to check*/

			lv_img_set_src(guider_ui.screen_day_in_sc3, &black1_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc3, 255);
		}
		else
		{
			/*do nothing*/
		}
		break;

	case 2:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc2, &black2_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc3, &black2_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc3, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 3:
		if (DigitIn_Selection == 1)
		{
			lv_img_set_src(guider_ui.screen_day_in_sc2, &black3_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc3, &black3_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc3, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 4:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc2, &black4_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc3, &black4_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc3, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 5:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc2, &black5_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc3, &black5_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc3, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 6:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc2, &black6_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc2, 255);
		}
		else if (DigitIn_Selection == 2)
		{
			lv_img_set_src(guider_ui.screen_day_in_sc3, &black6_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc3, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 7:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc2, &black7_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc3, &black7_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc3, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 8:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc2, &black8_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc3, &black8_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc3, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 9:
		if (DigitIn_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc2, &black9_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc2, 255);
		}
		else if (DigitIn_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_day_in_sc2, &black9_24x47);
			set_obj_opa(guider_ui.screen_day_in_sc2, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;
	}
}

/* FUNCTION USED TO GET CURRENT STATUS OF WELCOME ANIMATION */
HMI_WELCOME_ANIMATION_ST_EN HMI_Get_Welcome_Animation_Status(void)
{
	/* return animation status*/
	return (g_Welcome_Animation_Status_en);
}
