/* @file FILE NAME */
#ifndef HMI_SETTING_SCREEN_C
#define HMI_SETTING_SCREEN_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Palani kumar  ( palanikumar@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  Version                         : v1.0.0
 *  Micros supported                :
 *  Compilers supported             :
 *  Platforms supported             :
 *  Description                     : This file consists of button processing and HMI related elements
 *                                    for Setting screen
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "HMI_Setting_Screen.h"
#include "lvgl_app.h"
#include "Button_Manager_Cfg.h"
#include "gui_guider.h"
#include "Swc_Voltage_Battery_St.h"
#include "TC.h"
#include "Swc_TFT_Illum.h"
#include "Fuel_Guage.h"
#include "fsl_lpuart.h"
#include "Ambient_light_sensor_Cfg.h"
#include "BLE_music_module.h"
#include "rtc.h"
#include "HMI_Main_Screen.h"
#include "HMI_Clock.h"
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

	uint8_t setting_white_scr = 0;

#define DAY_MODE 1

	/***********************************************************************************************************************
	 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
	 ***********************************************************************************************************************/
	/*
	 * @brief: This variable is used to store current presentation screen of setting screen
	 * @Unit:
	 * @Resolution:
	 * @Range:
	 * @Applicability:
	 */
	HMI_SETTING_PST_SCREENS_EN g_Setting_PST_State_en;

	HMI_SETTING_PST_SCREENS_EN g_HMI_Setting_Last_Intermediate_Screen_u8;

	/* variable used to select setting sub screen based on user selection */
	uint8_t g_Setting_Sub_Screen_Sel_Cnt_U8 = 1;
	uint8_t g_Setting_Music_Selection_U8 = 1;
	uint8_t g_Bike_Sub_Screen_Sel_Cnt_U8 = 1;
	uint8_t g_Bike_Trip_sel_cnt_u8[2] = {1, 1};
	uint8_t g_Display_Sub_Screen_sel_cnt_u8 = 1;
	uint8_t g_Display_brightness_sel_cnt_u8 = 1;
	uint8_t g_Display_Clock_sel_cnt_u8 = 1;
	uint8_t g_UnitsSelection_Cnt_u8 = 1;
	uint8_t g_DistanceSelection_Cnt_u8 = 1;
	uint8_t g_Display_About_Sel_Cnt_u8 = 1;
	uint8_t g_Display_Audio_Sel_Cnt_u8 = 1;
	uint8_t g_Fuel_Consum_Selection_Cnt_u8 = 2;
	uint8_t g_User_Sel_Distance_Unit = 0;
	uint8_t g_User_Sel_Connectivity_Unit = 1;
	uint8_t g_User_Sel_TC_Unit = 2;

	uint8_t g_User_Brightness_Level_u8;
	uint8_t g_User_Music_Select_Level_U8;
	uint8_t g_Clock_Format_Selection_Cmd;

	// uint8_t g_BLE_Connectivity_Status_u8 = 0;
	uint8_t g_display_time_hr = 0;
    uint8_t g_display_time_min = 0;
	uint8_t g_display_am_pm_u8 = 0;
	uint8_t g_Ble_Music_u8 = 0;
    
	uint8_t g_Hour_Min_Meridian_Sel_Cnt = 0;
	/* User Date Setting variables */
	 uint8_t g_Day_Month_Year_Sel_Cnt = 0;
	uint8_t g_BLE_Status_u8 = BLUETOOTH_OFF;
	uint8_t g_Music_Status_u8 = 0;
	uint8_t g_Menu_Status_u8 = MENU_ON;
	uint8_t g_Fuel_Status_u8 = KmperL;
	uint8_t g_BLE_Selection_Status_u8 = 1;
	uint8_t g_Display_Menu_Setting_Status = 1;
    uint8_t g_Display_Date_Day_Timer_u8 = 1;
	uint8_t g_Display_Date_Arrow_status;
	uint8_t g_Display_Month_Arrow_status;
	uint8_t g_Display_Year_Arrow_status;

	uint8_t g_Display_hr_Arrow_status;
	uint8_t g_Display_min_Arrow_status;
	uint8_t g_Display_ampm_Arrow_status;
    uint8_t g_Display_Month_Timer_u8 = 1;
    uint16_t g_Display_Year_Timer_u16 = 2022;
	bool g_User_Date_Selection_Confirm_Cmd = FALSE;
	bool g_User_Clock_Selection_Confirm_Cmd = FALSE;
	uint8_t NVM_Setting_Write_request;

	 RTC_TIME_STAMP_ST g_Crnt_TimeSt;

	 //g_RTC_DATE_TIME_ST g_Crnt_TimeSt;

	extern g_RTC_DATE_TIME_ST g_Current_Date_St;

	uint8_t g_Handle_Bar_Btn_Status_u8[MAX_BUTTON_LIST];

	uint8_t g_flag = 0;
	uint8_t g_Blutooth_Selection_Cnt_u8 = 1;

	bool g_Setting_Screen_To_Other_Screen_Change_Req_Status;

	uint8_t g_NVM_Menu_Selection_Data_u8;

	/* Non-leap year days per month*/
	uint8_t Days_In_Month[12][2] = {
		{1, 31},
		{2, 28},
		{3, 31},
		{4, 30},
		{5, 31},
		{6, 30},
		{7, 31},
		{8, 31},
		{9, 30},
		{10, 31},
		{11, 30},
		{12, 31},
	};
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





	/***********************************************************************************************************************
	 *                                          F U N C T I O N     D E F I N I T I O N S
	 ***********************************************************************************************************************/
	void HMI_Setting_Screen_Warm_Init(void)
	{
		uint8_t fl_Setting_Screen_NVM_Data[6];

		g_Setting_PST_State_en = HMI_PST_SETTING_MAIN_SCREEN;

		g_HMI_Setting_Last_Intermediate_Screen_u8 = HMI_PST_SETTING_MAIN_SCREEN;
		g_Setting_Screen_To_Other_Screen_Change_Req_Status = FALSE;

		g_User_Brightness_Level_u8 = LOW_BRIGHTNESS;

		
		NVM_Byte_Read_Allocation(NVM_SETTING_SCREEN_NVM_DATA,&fl_Setting_Screen_NVM_Data[0]);

		g_NVM_Menu_Selection_Data_u8 = fl_Setting_Screen_NVM_Data[0];

		g_Clock_Format_Selection_Cmd = fl_Setting_Screen_NVM_Data[1];

		g_User_Brightness_Level_u8 = fl_Setting_Screen_NVM_Data[2];

		g_User_Sel_TC_Unit = fl_Setting_Screen_NVM_Data[3];

		g_BLE_Status_u8 = fl_Setting_Screen_NVM_Data[4];

		g_User_Music_Select_Level_U8 = fl_Setting_Screen_NVM_Data[5];

		/*Send Bluetooth*/
		if (g_BLE_Status_u8 == BLUETOOTH_ON)
		{
			GPIO_PinWrite(GPIO9, 16, 1);
		}
		else
		{
			GPIO_PinWrite(GPIO9, 16, 0);
		}

			/* As on 17/10/2022,  eeprom flash is not implemented, nvm may have default value. 
			so it assign to kmperl*/
			if(g_User_Sel_TC_Unit == 0)
			{
				g_User_Sel_TC_Unit = KmperL;
			}
	}

	void HMI_Setting_Screen_Cold_Init(void)
	{
		uint8_t fl_Setting_Screen_NVM_Data[6];

		g_Setting_PST_State_en = HMI_PST_SETTING_MAIN_SCREEN;

		g_HMI_Setting_Last_Intermediate_Screen_u8 = HMI_PST_SETTING_MAIN_SCREEN;
		g_Setting_Screen_To_Other_Screen_Change_Req_Status = FALSE;

		g_User_Brightness_Level_u8 = LOW_BRIGHTNESS;


		NVM_Byte_Read_Allocation(NVM_SETTING_SCREEN_NVM_DATA,&fl_Setting_Screen_NVM_Data[0]);

		g_NVM_Menu_Selection_Data_u8 = fl_Setting_Screen_NVM_Data[0];

		g_Clock_Format_Selection_Cmd = fl_Setting_Screen_NVM_Data[1];

		g_User_Brightness_Level_u8 = fl_Setting_Screen_NVM_Data[2];

		g_User_Sel_TC_Unit = fl_Setting_Screen_NVM_Data[3];

		g_BLE_Status_u8 = fl_Setting_Screen_NVM_Data[4];

		g_User_Music_Select_Level_U8 = fl_Setting_Screen_NVM_Data[5];

		/* Upon cold init clock format initialized in 12hr format*/
		g_Clock_Format_Selection_Cmd = CLOCK_12HR_FORMAT;

		NVM_Write_RTC_Time_Format();

		/*Send Bluetooth*/
		if (g_BLE_Status_u8 == BLUETOOTH_ON)
		{
			GPIO_PinWrite(GPIO9, 16, 1);
		}
		else
		{
			GPIO_PinWrite(GPIO9, 16, 0);
		}

	}



void GUI_Setting_mainscr_night_entry(void)
{
	lv_obj_clear_flag(guider_ui.Setting_Screen_setting_main_container,LV_OBJ_FLAG_HIDDEN);

	SettingConnectScrnEntry();
}

void GUI_Setting_mainscr_night_exit(void)
{
	lv_obj_add_flag(guider_ui.Setting_Screen_setting_main_container,LV_OBJ_FLAG_HIDDEN);
}

void GUI_NightEntry_Base(void)
{
	lv_obj_clear_flag(guider_ui.screen_Clock_Am, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Gear_Symbol, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Gear_Position_Number, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_gear_N_img_night, LV_OBJ_FLAG_HIDDEN);
}


void SettingConnectScrnEntry(void)
{
	lv_label_set_text(guider_ui.Setting_Screen_main_night_L1,"ABOUT");
	lv_label_set_text(guider_ui.Setting_Screen_main_night_L2,"");
	lv_label_set_text(guider_ui.Setting_Screen_main_night_L3,"BIKE");			
}




	void HMI_CLK_NVM_check(void)
	{

		NVM_Write_RTC_Time_Format();
	}


	void HMI_Load_Setting_Screen(void)
	{
		hmi_reset();
		/* screen change */

		lv_obj_del(lv_scr_act());

		setup_scr_Setting_Screen(&guider_ui);
		lv_scr_load(guider_ui.Setting_Screen);

	}

	void Idle_Setting_Screen(lv_ui *ui)
	{
		// Write codes Setting_Screen
		// Write codes Setting_Screen
		ui->Setting_Screen = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_main_default
	static lv_style_t style_setting_screen_main_main_default;
	lv_style_reset(&style_setting_screen_main_main_default);
	lv_style_set_bg_color(&style_setting_screen_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_setting_screen_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen, &style_setting_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_skin
	ui->Setting_Screen_skin = lv_img_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_skin, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_skin, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_skin_main_main_default
	static lv_style_t style_setting_screen_skin_main_main_default;
	lv_style_reset(&style_setting_screen_skin_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_skin_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_skin_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_skin_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_skin, &style_setting_screen_skin_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_skin, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_skin,&_Hero_RAAA_Outer_Ring_240x320);
	lv_img_set_pivot(ui->Setting_Screen_skin, 0,0);
	lv_img_set_angle(ui->Setting_Screen_skin, 0);

	//Write codes Setting_Screen_D_Cir
	ui->Setting_Screen_D_Cir = lv_img_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_D_Cir, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_D_Cir, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_d_cir_main_main_default
	static lv_style_t style_setting_screen_d_cir_main_main_default;
	lv_style_reset(&style_setting_screen_d_cir_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_d_cir_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_d_cir_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_d_cir_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_D_Cir, &style_setting_screen_d_cir_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_D_Cir, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_D_Cir,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_D_Cir, 0,0);
	lv_img_set_angle(ui->Setting_Screen_D_Cir, 0);

	//Write codes Setting_Screen_FogLampTT
	ui->Setting_Screen_FogLampTT = lv_imgbtn_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_FogLampTT, 10, 11);
	lv_obj_set_size(ui->Setting_Screen_FogLampTT, 24, 21);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_foglamptt_main_main_default
	static lv_style_t style_setting_screen_foglamptt_main_main_default;
	lv_style_reset(&style_setting_screen_foglamptt_main_main_default);
	lv_style_set_text_color(&style_setting_screen_foglamptt_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_setting_screen_foglamptt_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_foglamptt_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_foglamptt_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_FogLampTT, &style_setting_screen_foglamptt_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_setting_screen_foglamptt_main_main_pressed
	static lv_style_t style_setting_screen_foglamptt_main_main_pressed;
	lv_style_reset(&style_setting_screen_foglamptt_main_main_pressed);
	lv_style_set_text_color(&style_setting_screen_foglamptt_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_setting_screen_foglamptt_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_setting_screen_foglamptt_main_main_pressed, 0);
	lv_obj_add_style(ui->Setting_Screen_FogLampTT, &style_setting_screen_foglamptt_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_setting_screen_foglamptt_main_main_checked
	static lv_style_t style_setting_screen_foglamptt_main_main_checked;
	lv_style_reset(&style_setting_screen_foglamptt_main_main_checked);
	lv_style_set_text_color(&style_setting_screen_foglamptt_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_setting_screen_foglamptt_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_setting_screen_foglamptt_main_main_checked, 0);
	lv_obj_add_style(ui->Setting_Screen_FogLampTT, &style_setting_screen_foglamptt_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->Setting_Screen_FogLampTT, LV_IMGBTN_STATE_RELEASED, NULL, &new_header_fog_telltale, NULL);
	lv_imgbtn_set_src(ui->Setting_Screen_FogLampTT, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_24x20, NULL);
	lv_obj_add_flag(ui->Setting_Screen_FogLampTT, LV_OBJ_FLAG_CHECKABLE);

	//Write codes Setting_Screen_imgEngineTT
	ui->Setting_Screen_imgEngineTT = lv_imgbtn_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_imgEngineTT, 204, 12);
	lv_obj_set_size(ui->Setting_Screen_imgEngineTT, 26, 18);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_imgenginett_main_main_default
	static lv_style_t style_setting_screen_imgenginett_main_main_default;
	lv_style_reset(&style_setting_screen_imgenginett_main_main_default);
	lv_style_set_text_color(&style_setting_screen_imgenginett_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_setting_screen_imgenginett_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_imgenginett_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_imgenginett_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_imgEngineTT, &style_setting_screen_imgenginett_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_setting_screen_imgenginett_main_main_pressed
	static lv_style_t style_setting_screen_imgenginett_main_main_pressed;
	lv_style_reset(&style_setting_screen_imgenginett_main_main_pressed);
	lv_style_set_text_color(&style_setting_screen_imgenginett_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_setting_screen_imgenginett_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_setting_screen_imgenginett_main_main_pressed, 0);
	lv_obj_add_style(ui->Setting_Screen_imgEngineTT, &style_setting_screen_imgenginett_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_setting_screen_imgenginett_main_main_checked
	static lv_style_t style_setting_screen_imgenginett_main_main_checked;
	lv_style_reset(&style_setting_screen_imgenginett_main_main_checked);
	lv_style_set_text_color(&style_setting_screen_imgenginett_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_setting_screen_imgenginett_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_setting_screen_imgenginett_main_main_checked, 0);
	lv_obj_add_style(ui->Setting_Screen_imgEngineTT, &style_setting_screen_imgenginett_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->Setting_Screen_imgEngineTT, LV_IMGBTN_STATE_RELEASED, NULL, &new_engine_telltale, NULL);
	lv_imgbtn_set_src(ui->Setting_Screen_imgEngineTT, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_25x17, NULL);
	lv_obj_add_flag(ui->Setting_Screen_imgEngineTT, LV_OBJ_FLAG_CHECKABLE);

	//Write codes Setting_Screen_imgOilTelltale
	ui->Setting_Screen_imgOilTelltale = lv_imgbtn_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_imgOilTelltale, 4, 290);
	lv_obj_set_size(ui->Setting_Screen_imgOilTelltale, 34, 14);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_imgoiltelltale_main_main_default
	static lv_style_t style_setting_screen_imgoiltelltale_main_main_default;
	lv_style_reset(&style_setting_screen_imgoiltelltale_main_main_default);
	lv_style_set_text_color(&style_setting_screen_imgoiltelltale_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_setting_screen_imgoiltelltale_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_imgoiltelltale_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_imgoiltelltale_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_imgOilTelltale, &style_setting_screen_imgoiltelltale_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_setting_screen_imgoiltelltale_main_main_pressed
	static lv_style_t style_setting_screen_imgoiltelltale_main_main_pressed;
	lv_style_reset(&style_setting_screen_imgoiltelltale_main_main_pressed);
	lv_style_set_text_color(&style_setting_screen_imgoiltelltale_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_setting_screen_imgoiltelltale_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_setting_screen_imgoiltelltale_main_main_pressed, 0);
	lv_obj_add_style(ui->Setting_Screen_imgOilTelltale, &style_setting_screen_imgoiltelltale_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_setting_screen_imgoiltelltale_main_main_checked
	static lv_style_t style_setting_screen_imgoiltelltale_main_main_checked;
	lv_style_reset(&style_setting_screen_imgoiltelltale_main_main_checked);
	lv_style_set_text_color(&style_setting_screen_imgoiltelltale_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_setting_screen_imgoiltelltale_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_setting_screen_imgoiltelltale_main_main_checked, 0);
	lv_obj_add_style(ui->Setting_Screen_imgOilTelltale, &style_setting_screen_imgoiltelltale_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->Setting_Screen_imgOilTelltale, LV_IMGBTN_STATE_RELEASED, NULL, &new_oil_telltale, NULL);
	lv_imgbtn_set_src(ui->Setting_Screen_imgOilTelltale, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_32x13, NULL);
	lv_obj_add_flag(ui->Setting_Screen_imgOilTelltale, LV_OBJ_FLAG_CHECKABLE);

	//Write codes Setting_Screen_Clock_hour
	ui->Setting_Screen_Clock_hour = lv_label_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_Clock_hour, 75, 285);
	lv_obj_set_size(ui->Setting_Screen_Clock_hour, 21, 15);
	lv_label_set_text(ui->Setting_Screen_Clock_hour, "24");
	lv_label_set_long_mode(ui->Setting_Screen_Clock_hour, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->Setting_Screen_Clock_hour, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_clock_hour_main_main_default
	static lv_style_t style_setting_screen_clock_hour_main_main_default;
	lv_style_reset(&style_setting_screen_clock_hour_main_main_default);
	lv_style_set_radius(&style_setting_screen_clock_hour_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_clock_hour_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_clock_hour_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_clock_hour_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_clock_hour_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_clock_hour_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_clock_hour_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_clock_hour_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_Clock_hour, &style_setting_screen_clock_hour_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_Clock_min
	ui->Setting_Screen_Clock_min = lv_label_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_Clock_min, 107, 285);
	lv_obj_set_size(ui->Setting_Screen_Clock_min, 20, 15);
	lv_label_set_text(ui->Setting_Screen_Clock_min, "60");
	lv_label_set_long_mode(ui->Setting_Screen_Clock_min, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->Setting_Screen_Clock_min, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_clock_min_main_main_default
	static lv_style_t style_setting_screen_clock_min_main_main_default;
	lv_style_reset(&style_setting_screen_clock_min_main_main_default);
	lv_style_set_radius(&style_setting_screen_clock_min_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_clock_min_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_clock_min_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_clock_min_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_clock_min_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_clock_min_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_clock_min_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_clock_min_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_Clock_min, &style_setting_screen_clock_min_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_Clock_Colan
	ui->Setting_Screen_Clock_Colan = lv_label_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_Clock_Colan, 94, 285);
	lv_obj_set_size(ui->Setting_Screen_Clock_Colan, 15, 15);
	lv_label_set_text(ui->Setting_Screen_Clock_Colan, ":");
	lv_label_set_long_mode(ui->Setting_Screen_Clock_Colan, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->Setting_Screen_Clock_Colan, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_clock_colan_main_main_default
	static lv_style_t style_setting_screen_clock_colan_main_main_default;
	lv_style_reset(&style_setting_screen_clock_colan_main_main_default);
	lv_style_set_radius(&style_setting_screen_clock_colan_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_clock_colan_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_clock_colan_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_clock_colan_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_clock_colan_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_clock_colan_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_clock_colan_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_clock_colan_main_main_default, 2);
	lv_style_set_pad_left(&style_setting_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_clock_colan_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_Clock_Colan, &style_setting_screen_clock_colan_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_Clock_AM
	ui->Setting_Screen_Clock_AM = lv_label_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_Clock_AM, 130, 285);
	lv_obj_set_size(ui->Setting_Screen_Clock_AM, 28, 13);
	lv_label_set_text(ui->Setting_Screen_Clock_AM, "AM");
	lv_label_set_long_mode(ui->Setting_Screen_Clock_AM, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->Setting_Screen_Clock_AM, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_clock_am_main_main_default
	static lv_style_t style_setting_screen_clock_am_main_main_default;
	lv_style_reset(&style_setting_screen_clock_am_main_main_default);
	lv_style_set_radius(&style_setting_screen_clock_am_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_clock_am_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_clock_am_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_clock_am_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_clock_am_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_clock_am_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_clock_am_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_clock_am_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_Clock_AM, &style_setting_screen_clock_am_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_label
	ui->Setting_Screen_display_label = lv_label_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_display_label, 0, 22);
	lv_obj_set_size(ui->Setting_Screen_display_label, 240, 17);
	lv_label_set_text(ui->Setting_Screen_display_label, "DATE AND TIME");
	lv_label_set_long_mode(ui->Setting_Screen_display_label, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_display_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_label_main_main_default
	static lv_style_t style_setting_screen_display_label_main_main_default;
	lv_style_reset(&style_setting_screen_display_label_main_main_default);
	lv_style_set_radius(&style_setting_screen_display_label_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_display_label_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_display_label_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_display_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_display_label_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_display_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_display_label_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_setting_screen_display_label_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_display_label_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_display_label_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_display_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_display_label_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_display_label, &style_setting_screen_display_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	

	//Write codes Setting_Screen_setting_main_container
	ui->Setting_Screen_setting_main_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_main_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_main_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_main_container_main_main_default
	static lv_style_t style_setting_screen_setting_main_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_main_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_main_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_main_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_main_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_main_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_main_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_main_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_main_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_main_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_main_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_main_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_main_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_main_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_main_container, &style_setting_screen_setting_main_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_side_night_img
	ui->Setting_Screen_main_side_night_img = lv_img_create(ui->Setting_Screen_setting_main_container);
	lv_obj_set_pos(ui->Setting_Screen_main_side_night_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_main_side_night_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_side_night_img_main_main_default
	static lv_style_t style_setting_screen_main_side_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_side_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_side_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_side_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_side_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_side_night_img, &style_setting_screen_main_side_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_sub_button_night_img
	ui->Setting_Screen_main_sub_button_night_img = lv_img_create(ui->Setting_Screen_setting_main_container);
	lv_obj_set_pos(ui->Setting_Screen_main_sub_button_night_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_main_sub_button_night_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_sub_button_night_img_main_main_default
	static lv_style_t style_setting_screen_main_sub_button_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_sub_button_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_sub_button_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_sub_button_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_sub_button_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_sub_button_night_img, &style_setting_screen_main_sub_button_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_main_sub_button_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_main_sub_button_night_img,&subbtn_night_24x24);
	lv_img_set_pivot(ui->Setting_Screen_main_sub_button_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_main_sub_button_night_img, 0);

	//Write codes Setting_Screen_main_up_arrow_night_img
	ui->Setting_Screen_main_up_arrow_night_img = lv_img_create(ui->Setting_Screen_setting_main_container);
	lv_obj_set_pos(ui->Setting_Screen_main_up_arrow_night_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_main_up_arrow_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_up_arrow_night_img_main_main_default
	static lv_style_t style_setting_screen_main_up_arrow_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_up_arrow_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_up_arrow_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_up_arrow_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_up_arrow_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_up_arrow_night_img, &style_setting_screen_main_up_arrow_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_main_up_arrow_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_main_up_arrow_night_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_main_up_arrow_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_main_up_arrow_night_img, 0);

	//Write codes Setting_Screen_main_down_arr_night_img
	ui->Setting_Screen_main_down_arr_night_img = lv_img_create(ui->Setting_Screen_setting_main_container);
	lv_obj_set_pos(ui->Setting_Screen_main_down_arr_night_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_main_down_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_down_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_main_down_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_down_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_down_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_down_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_down_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_down_arr_night_img, &style_setting_screen_main_down_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_main_down_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_main_down_arr_night_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_main_down_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_main_down_arr_night_img, 0);

	//Write codes Setting_Screen_main_night_L1
	ui->Setting_Screen_main_night_L1 = lv_label_create(ui->Setting_Screen_setting_main_container);
	lv_obj_set_pos(ui->Setting_Screen_main_night_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_main_night_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_main_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_main_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_main_night_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_night_l1_main_main_default
	static lv_style_t style_setting_screen_main_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_main_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_main_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_main_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_main_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_main_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_main_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_main_night_l1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_main_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_main_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_main_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_main_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_main_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_main_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_main_night_L1, &style_setting_screen_main_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_night_L2
	ui->Setting_Screen_main_night_L2 = lv_label_create(ui->Setting_Screen_setting_main_container);
	lv_obj_set_pos(ui->Setting_Screen_main_night_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_main_night_L2, 240, 18);
	lv_label_set_text(ui->Setting_Screen_main_night_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_main_night_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_main_night_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_night_l2_main_main_default
	static lv_style_t style_setting_screen_main_night_l2_main_main_default;
	lv_style_reset(&style_setting_screen_main_night_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_main_night_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_main_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_main_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_main_night_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_main_night_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_main_night_l2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_main_night_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_main_night_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_main_night_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_main_night_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_main_night_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_main_night_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_main_night_L2, &style_setting_screen_main_night_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_night_L3
	ui->Setting_Screen_main_night_L3 = lv_label_create(ui->Setting_Screen_setting_main_container);
	lv_obj_set_pos(ui->Setting_Screen_main_night_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_main_night_L3, 240, 18);
	lv_label_set_text(ui->Setting_Screen_main_night_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_main_night_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_main_night_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_night_l3_main_main_default
	static lv_style_t style_setting_screen_main_night_l3_main_main_default;
	lv_style_reset(&style_setting_screen_main_night_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_main_night_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_main_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_main_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_main_night_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_main_night_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_main_night_l3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_main_night_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_main_night_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_main_night_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_main_night_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_main_night_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_main_night_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_main_night_L3, &style_setting_screen_main_night_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_main_day_container
	ui->Setting_Screen_setting_main_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_main_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_main_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_main_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_main_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_main_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_main_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_main_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_main_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_main_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_main_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_main_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_main_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_main_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_main_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_main_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_main_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_main_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_main_day_container, &style_setting_screen_setting_main_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_day_circle_img
	ui->Setting_Screen_main_day_circle_img = lv_img_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_main_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_main_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_day_circle_img, &style_setting_screen_main_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_main_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_main_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_main_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_main_day_circle_img, 0);

	//Write codes Setting_Screen_main_side_day_img
	ui->Setting_Screen_main_side_day_img = lv_img_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_side_day_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_main_side_day_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_side_day_img_main_main_default
	static lv_style_t style_setting_screen_main_side_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_side_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_side_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_side_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_side_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_side_day_img, &style_setting_screen_main_side_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_sub_button_day_img
	ui->Setting_Screen_main_sub_button_day_img = lv_img_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_sub_button_day_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_main_sub_button_day_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_sub_button_day_img_main_main_default
	static lv_style_t style_setting_screen_main_sub_button_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_sub_button_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_sub_button_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_sub_button_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_sub_button_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_sub_button_day_img, &style_setting_screen_main_sub_button_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_main_sub_button_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_main_sub_button_day_img,&subbtn_day_24x24);
	lv_img_set_pivot(ui->Setting_Screen_main_sub_button_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_main_sub_button_day_img, 0);

	//Write codes Setting_Screen_main_up_night_day_img
	ui->Setting_Screen_main_up_night_day_img = lv_img_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_up_night_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_main_up_night_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_up_night_day_img_main_main_default
	static lv_style_t style_setting_screen_main_up_night_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_up_night_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_up_night_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_up_night_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_up_night_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_up_night_day_img, &style_setting_screen_main_up_night_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_main_up_night_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_main_up_night_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_main_up_night_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_main_up_night_day_img, 0);

	//Write codes Setting_Screen_main_down_arr_day_img
	ui->Setting_Screen_main_down_arr_day_img = lv_img_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_down_arr_day_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_main_down_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_down_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_main_down_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_down_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_down_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_down_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_down_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_down_arr_day_img, &style_setting_screen_main_down_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_main_down_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_main_down_arr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_main_down_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_main_down_arr_day_img, 0);

	//Write codes Setting_Screen_main_day_L1
	ui->Setting_Screen_main_day_L1 = lv_label_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_day_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_main_day_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_main_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_main_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_main_day_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_day_l1_main_main_default
	static lv_style_t style_setting_screen_main_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_main_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_main_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_main_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_main_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_main_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_main_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_main_day_l1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_main_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_main_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_main_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_main_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_main_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_main_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_main_day_L1, &style_setting_screen_main_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_day_L2
	ui->Setting_Screen_main_day_L2 = lv_label_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_day_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_main_day_L2, 240, 18);
	lv_label_set_text(ui->Setting_Screen_main_day_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_main_day_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_main_day_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_day_l2_main_main_default
	static lv_style_t style_setting_screen_main_day_l2_main_main_default;
	lv_style_reset(&style_setting_screen_main_day_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_main_day_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_main_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_main_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_main_day_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_main_day_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_main_day_l2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_main_day_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_main_day_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_main_day_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_main_day_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_main_day_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_main_day_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_main_day_L2, &style_setting_screen_main_day_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_day_L3
	ui->Setting_Screen_main_day_L3 = lv_label_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_day_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_main_day_L3, 240, 18);
	lv_label_set_text(ui->Setting_Screen_main_day_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_main_day_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_main_day_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_day_l3_main_main_default
	static lv_style_t style_setting_screen_main_day_l3_main_main_default;
	lv_style_reset(&style_setting_screen_main_day_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_main_day_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_main_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_main_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_main_day_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_main_day_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_main_day_l3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_main_day_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_main_day_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_main_day_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_main_day_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_main_day_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_main_day_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_main_day_L3, &style_setting_screen_main_day_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes Setting_Screen_setting_bike_night_container
	ui->Setting_Screen_setting_bike_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_bike_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_bike_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_bike_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_bike_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_bike_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_bike_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_bike_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_bike_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_bike_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_bike_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_bike_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_bike_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_bike_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_bike_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_bike_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_bike_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_bike_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_bike_night_container, &style_setting_screen_setting_bike_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_side_night_img
	ui->Setting_Screen_bike_side_night_img = lv_img_create(ui->Setting_Screen_setting_bike_night_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_side_night_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_bike_side_night_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_side_night_img_main_main_default
	static lv_style_t style_setting_screen_bike_side_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_side_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_side_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_side_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_side_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_side_night_img, &style_setting_screen_bike_side_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_sub_button_night_img
	ui->Setting_Screen_bike_sub_button_night_img = lv_img_create(ui->Setting_Screen_setting_bike_night_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_sub_button_night_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_bike_sub_button_night_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_sub_button_night_img_main_main_default
	static lv_style_t style_setting_screen_bike_sub_button_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_sub_button_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_sub_button_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_sub_button_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_sub_button_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_sub_button_night_img, &style_setting_screen_bike_sub_button_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_bike_sub_button_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_bike_sub_button_night_img,&subbtn_night_24x24);
	lv_img_set_pivot(ui->Setting_Screen_bike_sub_button_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_bike_sub_button_night_img, 0);

	//Write codes Setting_Screen_bike_up_arrow_night_img
	ui->Setting_Screen_bike_up_arrow_night_img = lv_img_create(ui->Setting_Screen_setting_bike_night_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_up_arrow_night_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_bike_up_arrow_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_up_arrow_night_img_main_main_default
	static lv_style_t style_setting_screen_bike_up_arrow_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_up_arrow_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_up_arrow_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_up_arrow_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_up_arrow_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_up_arrow_night_img, &style_setting_screen_bike_up_arrow_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_bike_up_arrow_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_bike_up_arrow_night_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_bike_up_arrow_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_bike_up_arrow_night_img, 0);

	//Write codes Setting_Screen_bike_down_arrow_night_img
	ui->Setting_Screen_bike_down_arrow_night_img = lv_img_create(ui->Setting_Screen_setting_bike_night_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_down_arrow_night_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_bike_down_arrow_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_down_arrow_night_img_main_main_default
	static lv_style_t style_setting_screen_bike_down_arrow_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_down_arrow_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_down_arrow_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_down_arrow_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_down_arrow_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_down_arrow_night_img, &style_setting_screen_bike_down_arrow_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_bike_down_arrow_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_bike_down_arrow_night_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_bike_down_arrow_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_bike_down_arrow_night_img, 0);

	//Write codes Setting_Screen_bike_night_L1
	ui->Setting_Screen_bike_night_L1 = lv_label_create(ui->Setting_Screen_setting_bike_night_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_night_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_bike_night_L1, 240, 26);
	lv_label_set_text(ui->Setting_Screen_bike_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_bike_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_bike_night_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_night_l1_main_main_default
	static lv_style_t style_setting_screen_bike_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_bike_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_bike_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_bike_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_bike_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_bike_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_bike_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_bike_night_l1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_bike_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_bike_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_bike_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_bike_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_bike_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_bike_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_bike_night_L1, &style_setting_screen_bike_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_night_L2
	ui->Setting_Screen_bike_night_L2 = lv_label_create(ui->Setting_Screen_setting_bike_night_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_night_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_bike_night_L2, 240, 26);
	lv_label_set_text(ui->Setting_Screen_bike_night_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_bike_night_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_bike_night_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_night_l2_main_main_default
	static lv_style_t style_setting_screen_bike_night_l2_main_main_default;
	lv_style_reset(&style_setting_screen_bike_night_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_bike_night_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_bike_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_bike_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_bike_night_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_bike_night_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_bike_night_l2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_bike_night_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_bike_night_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_bike_night_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_bike_night_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_bike_night_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_bike_night_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_bike_night_L2, &style_setting_screen_bike_night_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_night_L3
	ui->Setting_Screen_bike_night_L3 = lv_label_create(ui->Setting_Screen_setting_bike_night_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_night_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_bike_night_L3, 240, 26);
	lv_label_set_text(ui->Setting_Screen_bike_night_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_bike_night_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_bike_night_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_night_l3_main_main_default
	static lv_style_t style_setting_screen_bike_night_l3_main_main_default;
	lv_style_reset(&style_setting_screen_bike_night_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_bike_night_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_bike_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_bike_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_bike_night_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_bike_night_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_bike_night_l3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_bike_night_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_bike_night_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_bike_night_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_bike_night_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_bike_night_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_bike_night_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_bike_night_L3, &style_setting_screen_bike_night_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_bike_day_container
	ui->Setting_Screen_setting_bike_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_bike_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_bike_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_bike_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_bike_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_bike_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_bike_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_bike_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_bike_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_bike_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_bike_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_bike_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_bike_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_bike_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_bike_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_bike_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_bike_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_bike_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_bike_day_container, &style_setting_screen_setting_bike_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_day_circle_img
	ui->Setting_Screen_bike_day_circle_img = lv_img_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_bike_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_bike_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_day_circle_img, &style_setting_screen_bike_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_bike_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_bike_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_bike_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_bike_day_circle_img, 0);

	//Write codes Setting_Screen_bike_side_day_img
	ui->Setting_Screen_bike_side_day_img = lv_img_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_side_day_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_bike_side_day_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_side_day_img_main_main_default
	static lv_style_t style_setting_screen_bike_side_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_side_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_side_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_side_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_side_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_side_day_img, &style_setting_screen_bike_side_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_sub_button_img
	ui->Setting_Screen_bike_sub_button_img = lv_img_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_sub_button_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_bike_sub_button_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_sub_button_img_main_main_default
	static lv_style_t style_setting_screen_bike_sub_button_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_sub_button_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_sub_button_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_sub_button_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_sub_button_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_sub_button_img, &style_setting_screen_bike_sub_button_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_bike_sub_button_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_bike_sub_button_img,&subbtn_day_24x24);
	lv_img_set_pivot(ui->Setting_Screen_bike_sub_button_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_bike_sub_button_img, 0);

	//Write codes Setting_Screen_bike_up_arr_day_img
	ui->Setting_Screen_bike_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_up_arr_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_bike_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_bike_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_up_arr_day_img, &style_setting_screen_bike_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_bike_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_bike_up_arr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_bike_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_bike_up_arr_day_img, 0);

	//Write codes Setting_Screen_bike_down_arr_day_img
	ui->Setting_Screen_bike_down_arr_day_img = lv_img_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_down_arr_day_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_bike_down_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_down_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_bike_down_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_down_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_down_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_down_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_down_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_down_arr_day_img, &style_setting_screen_bike_down_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_bike_down_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_bike_down_arr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_bike_down_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_bike_down_arr_day_img, 0);

	//Write codes Setting_Screen_bike_day_L1
	ui->Setting_Screen_bike_day_L1 = lv_label_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_day_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_bike_day_L1, 240, 26);
	lv_label_set_text(ui->Setting_Screen_bike_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_bike_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_bike_day_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_day_l1_main_main_default
	static lv_style_t style_setting_screen_bike_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_bike_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_bike_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_bike_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_bike_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_bike_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_bike_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_bike_day_l1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_bike_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_bike_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_bike_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_bike_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_bike_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_bike_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_bike_day_L1, &style_setting_screen_bike_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_day_L2
	ui->Setting_Screen_bike_day_L2 = lv_label_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_day_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_bike_day_L2, 240, 26);
	lv_label_set_text(ui->Setting_Screen_bike_day_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_bike_day_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_bike_day_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_day_l2_main_main_default
	static lv_style_t style_setting_screen_bike_day_l2_main_main_default;
	lv_style_reset(&style_setting_screen_bike_day_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_bike_day_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_bike_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_bike_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_bike_day_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_bike_day_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_bike_day_l2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_bike_day_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_bike_day_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_bike_day_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_bike_day_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_bike_day_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_bike_day_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_bike_day_L2, &style_setting_screen_bike_day_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_day_L3
	ui->Setting_Screen_bike_day_L3 = lv_label_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_day_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_bike_day_L3, 240, 26);
	lv_label_set_text(ui->Setting_Screen_bike_day_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_bike_day_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_bike_day_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_day_l3_main_main_default
	static lv_style_t style_setting_screen_bike_day_l3_main_main_default;
	lv_style_reset(&style_setting_screen_bike_day_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_bike_day_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_bike_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_bike_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_bike_day_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_bike_day_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_bike_day_l3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_bike_day_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_bike_day_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_bike_day_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_bike_day_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_bike_day_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_bike_day_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_bike_day_L3, &style_setting_screen_bike_day_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_about_night_container
	ui->Setting_Screen_setting_about_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_about_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_about_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_about_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_about_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_about_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_about_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_about_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_about_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_about_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_about_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_about_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_about_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_about_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_about_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_about_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_about_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_about_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_about_night_container, &style_setting_screen_setting_about_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_side_night_img
	ui->Setting_Screen_about_side_night_img = lv_img_create(ui->Setting_Screen_setting_about_night_container);
	lv_obj_set_pos(ui->Setting_Screen_about_side_night_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_about_side_night_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_side_night_img_main_main_default
	static lv_style_t style_setting_screen_about_side_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_side_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_side_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_side_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_side_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_side_night_img, &style_setting_screen_about_side_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_sub_button_night_img
	ui->Setting_Screen_about_sub_button_night_img = lv_img_create(ui->Setting_Screen_setting_about_night_container);
	lv_obj_set_pos(ui->Setting_Screen_about_sub_button_night_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_about_sub_button_night_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_sub_button_night_img_main_main_default
	static lv_style_t style_setting_screen_about_sub_button_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_sub_button_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_sub_button_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_sub_button_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_sub_button_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_sub_button_night_img, &style_setting_screen_about_sub_button_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_about_sub_button_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_about_sub_button_night_img,&subbtn_night_24x24);
	lv_img_set_pivot(ui->Setting_Screen_about_sub_button_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_about_sub_button_night_img, 0);

	//Write codes Setting_Screen_about_up_arr_night_img
	ui->Setting_Screen_about_up_arr_night_img = lv_img_create(ui->Setting_Screen_setting_about_night_container);
	lv_obj_set_pos(ui->Setting_Screen_about_up_arr_night_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_about_up_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_up_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_about_up_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_up_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_up_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_up_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_up_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_up_arr_night_img, &style_setting_screen_about_up_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_about_up_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_about_up_arr_night_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_about_up_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_about_up_arr_night_img, 0);

	//Write codes Setting_Screen_about_down_arr_night_img
	ui->Setting_Screen_about_down_arr_night_img = lv_img_create(ui->Setting_Screen_setting_about_night_container);
	lv_obj_set_pos(ui->Setting_Screen_about_down_arr_night_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_about_down_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_down_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_about_down_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_down_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_down_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_down_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_down_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_down_arr_night_img, &style_setting_screen_about_down_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_about_down_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_about_down_arr_night_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_about_down_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_about_down_arr_night_img, 0);

	//Write codes Setting_Screen_about_night_L1
	ui->Setting_Screen_about_night_L1 = lv_label_create(ui->Setting_Screen_setting_about_night_container);
	lv_obj_set_pos(ui->Setting_Screen_about_night_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_about_night_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_about_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_about_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_about_night_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_night_l1_main_main_default
	static lv_style_t style_setting_screen_about_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_about_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_about_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_about_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_about_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_about_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_about_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_about_night_l1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_about_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_about_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_about_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_about_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_about_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_about_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_about_night_L1, &style_setting_screen_about_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_night_L2
	ui->Setting_Screen_about_night_L2 = lv_label_create(ui->Setting_Screen_setting_about_night_container);
	lv_obj_set_pos(ui->Setting_Screen_about_night_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_about_night_L2, 240, 18);
	lv_label_set_text(ui->Setting_Screen_about_night_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_about_night_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_about_night_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_night_l2_main_main_default
	static lv_style_t style_setting_screen_about_night_l2_main_main_default;
	lv_style_reset(&style_setting_screen_about_night_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_about_night_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_about_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_about_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_about_night_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_about_night_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_about_night_l2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_about_night_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_about_night_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_about_night_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_about_night_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_about_night_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_about_night_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_about_night_L2, &style_setting_screen_about_night_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_night_L3
	ui->Setting_Screen_about_night_L3 = lv_label_create(ui->Setting_Screen_setting_about_night_container);
	lv_obj_set_pos(ui->Setting_Screen_about_night_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_about_night_L3, 240, 18);
	lv_label_set_text(ui->Setting_Screen_about_night_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_about_night_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_about_night_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_night_l3_main_main_default
	static lv_style_t style_setting_screen_about_night_l3_main_main_default;
	lv_style_reset(&style_setting_screen_about_night_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_about_night_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_about_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_about_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_about_night_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_about_night_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_about_night_l3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_about_night_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_about_night_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_about_night_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_about_night_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_about_night_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_about_night_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_about_night_L3, &style_setting_screen_about_night_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_about_day_container
	ui->Setting_Screen_setting_about_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_about_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_about_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_about_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_about_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_about_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_about_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_about_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_about_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_about_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_about_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_about_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_about_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_about_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_about_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_about_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_about_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_about_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_about_day_container, &style_setting_screen_setting_about_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_day_circle_img
	ui->Setting_Screen_about_day_circle_img = lv_img_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_about_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_about_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_day_circle_img, &style_setting_screen_about_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_about_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_about_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_about_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_about_day_circle_img, 0);

	//Write codes Setting_Screen_about_side_day_img
	ui->Setting_Screen_about_side_day_img = lv_img_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_side_day_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_about_side_day_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_side_day_img_main_main_default
	static lv_style_t style_setting_screen_about_side_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_side_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_side_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_side_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_side_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_side_day_img, &style_setting_screen_about_side_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_sub_button_day_img
	ui->Setting_Screen_about_sub_button_day_img = lv_img_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_sub_button_day_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_about_sub_button_day_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_sub_button_day_img_main_main_default
	static lv_style_t style_setting_screen_about_sub_button_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_sub_button_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_sub_button_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_sub_button_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_sub_button_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_sub_button_day_img, &style_setting_screen_about_sub_button_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_about_sub_button_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_about_sub_button_day_img,&subbtn_day_24x24);
	lv_img_set_pivot(ui->Setting_Screen_about_sub_button_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_about_sub_button_day_img, 0);

	//Write codes Setting_Screen_about_up_arr_day_img
	ui->Setting_Screen_about_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_up_arr_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_about_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_about_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_up_arr_day_img, &style_setting_screen_about_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_about_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_about_up_arr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_about_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_about_up_arr_day_img, 0);

	//Write codes Setting_Screen_about_down_arr_day_img
	ui->Setting_Screen_about_down_arr_day_img = lv_img_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_down_arr_day_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_about_down_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_down_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_about_down_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_down_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_down_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_down_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_down_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_down_arr_day_img, &style_setting_screen_about_down_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_about_down_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_about_down_arr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_about_down_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_about_down_arr_day_img, 0);

	//Write codes Setting_Screen_about_day_L1
	ui->Setting_Screen_about_day_L1 = lv_label_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_day_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_about_day_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_about_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_about_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_about_day_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_day_l1_main_main_default
	static lv_style_t style_setting_screen_about_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_about_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_about_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_about_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_about_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_about_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_about_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_about_day_l1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_about_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_about_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_about_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_about_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_about_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_about_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_about_day_L1, &style_setting_screen_about_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_day_L2
	ui->Setting_Screen_about_day_L2 = lv_label_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_day_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_about_day_L2, 240, 18);
	lv_label_set_text(ui->Setting_Screen_about_day_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_about_day_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_about_day_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_day_l2_main_main_default
	static lv_style_t style_setting_screen_about_day_l2_main_main_default;
	lv_style_reset(&style_setting_screen_about_day_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_about_day_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_about_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_about_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_about_day_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_about_day_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_about_day_l2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_about_day_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_about_day_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_about_day_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_about_day_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_about_day_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_about_day_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_about_day_L2, &style_setting_screen_about_day_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_day_L3
	ui->Setting_Screen_about_day_L3 = lv_label_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_day_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_about_day_L3, 240, 18);
	lv_label_set_text(ui->Setting_Screen_about_day_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_about_day_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_about_day_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_day_l3_main_main_default
	static lv_style_t style_setting_screen_about_day_l3_main_main_default;
	lv_style_reset(&style_setting_screen_about_day_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_about_day_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_about_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_about_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_about_day_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_about_day_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_about_day_l3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_about_day_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_about_day_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_about_day_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_about_day_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_about_day_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_about_day_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_about_day_L3, &style_setting_screen_about_day_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes Setting_Screen_setting_display_night_container
	ui->Setting_Screen_setting_display_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_display_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_display_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_display_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_display_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_display_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_display_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_display_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_display_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_display_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_display_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_display_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_display_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_display_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_display_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_display_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_display_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_display_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_display_night_container, &style_setting_screen_setting_display_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_side_night_img
	ui->Setting_Screen_display_side_night_img = lv_img_create(ui->Setting_Screen_setting_display_night_container);
	lv_obj_set_pos(ui->Setting_Screen_display_side_night_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_display_side_night_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_side_night_img_main_main_default
	static lv_style_t style_setting_screen_display_side_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_side_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_side_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_side_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_side_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_side_night_img, &style_setting_screen_display_side_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_sub_button_night_img
	ui->Setting_Screen_display_sub_button_night_img = lv_img_create(ui->Setting_Screen_setting_display_night_container);
	lv_obj_set_pos(ui->Setting_Screen_display_sub_button_night_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_display_sub_button_night_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_sub_button_night_img_main_main_default
	static lv_style_t style_setting_screen_display_sub_button_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_sub_button_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_sub_button_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_sub_button_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_sub_button_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_sub_button_night_img, &style_setting_screen_display_sub_button_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_display_sub_button_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_display_sub_button_night_img,&subbtn_night_24x24);
	lv_img_set_pivot(ui->Setting_Screen_display_sub_button_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_display_sub_button_night_img, 0);

	//Write codes Setting_Screen_display_up_arr_night_img
	ui->Setting_Screen_display_up_arr_night_img = lv_img_create(ui->Setting_Screen_setting_display_night_container);
	lv_obj_set_pos(ui->Setting_Screen_display_up_arr_night_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_display_up_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_up_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_display_up_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_up_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_up_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_up_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_up_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_up_arr_night_img, &style_setting_screen_display_up_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_display_up_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_display_up_arr_night_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_display_up_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_display_up_arr_night_img, 0);

	//Write codes Setting_Screen_display_down_arr_night_img
	ui->Setting_Screen_display_down_arr_night_img = lv_img_create(ui->Setting_Screen_setting_display_night_container);
	lv_obj_set_pos(ui->Setting_Screen_display_down_arr_night_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_display_down_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_down_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_display_down_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_down_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_down_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_down_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_down_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_down_arr_night_img, &style_setting_screen_display_down_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_display_down_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_display_down_arr_night_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_display_down_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_display_down_arr_night_img, 0);

	//Write codes Setting_Screen_display_night_L1
	ui->Setting_Screen_display_night_L1 = lv_label_create(ui->Setting_Screen_setting_display_night_container);
	lv_obj_set_pos(ui->Setting_Screen_display_night_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_display_night_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_display_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_display_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_display_night_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_night_l1_main_main_default
	static lv_style_t style_setting_screen_display_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_display_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_display_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_display_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_display_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_display_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_display_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_display_night_l1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_display_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_display_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_display_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_display_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_display_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_display_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_display_night_L1, &style_setting_screen_display_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_night_L2
	ui->Setting_Screen_display_night_L2 = lv_label_create(ui->Setting_Screen_setting_display_night_container);
	lv_obj_set_pos(ui->Setting_Screen_display_night_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_display_night_L2, 240, 18);
	lv_label_set_text(ui->Setting_Screen_display_night_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_display_night_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_display_night_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_night_l2_main_main_default
	static lv_style_t style_setting_screen_display_night_l2_main_main_default;
	lv_style_reset(&style_setting_screen_display_night_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_display_night_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_display_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_display_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_display_night_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_display_night_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_display_night_l2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_display_night_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_display_night_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_display_night_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_display_night_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_display_night_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_display_night_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_display_night_L2, &style_setting_screen_display_night_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_night_L3
	ui->Setting_Screen_display_night_L3 = lv_label_create(ui->Setting_Screen_setting_display_night_container);
	lv_obj_set_pos(ui->Setting_Screen_display_night_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_display_night_L3, 240, 18);
	lv_label_set_text(ui->Setting_Screen_display_night_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_display_night_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_display_night_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_night_l3_main_main_default
	static lv_style_t style_setting_screen_display_night_l3_main_main_default;
	lv_style_reset(&style_setting_screen_display_night_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_display_night_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_display_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_display_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_display_night_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_display_night_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_display_night_l3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_display_night_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_display_night_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_display_night_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_display_night_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_display_night_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_display_night_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_display_night_L3, &style_setting_screen_display_night_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_display_day_container
	ui->Setting_Screen_setting_display_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_display_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_display_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_display_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_display_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_display_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_display_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_display_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_display_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_display_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_display_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_display_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_display_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_display_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_display_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_display_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_display_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_display_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_display_day_container, &style_setting_screen_setting_display_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_day_circle_img
	ui->Setting_Screen_display_day_circle_img = lv_img_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_display_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_display_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_day_circle_img, &style_setting_screen_display_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_display_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_display_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_display_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_display_day_circle_img, 0);

	//Write codes Setting_Screen_display_side_day_img
	ui->Setting_Screen_display_side_day_img = lv_img_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_side_day_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_display_side_day_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_side_day_img_main_main_default
	static lv_style_t style_setting_screen_display_side_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_side_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_side_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_side_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_side_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_side_day_img, &style_setting_screen_display_side_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_sub_button_day_img
	ui->Setting_Screen_display_sub_button_day_img = lv_img_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_sub_button_day_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_display_sub_button_day_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_sub_button_day_img_main_main_default
	static lv_style_t style_setting_screen_display_sub_button_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_sub_button_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_sub_button_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_sub_button_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_sub_button_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_sub_button_day_img, &style_setting_screen_display_sub_button_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_display_sub_button_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_display_sub_button_day_img,&subbtn_day_24x24);
	lv_img_set_pivot(ui->Setting_Screen_display_sub_button_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_display_sub_button_day_img, 0);

	//Write codes Setting_Screen_display_up_arr_day_img
	ui->Setting_Screen_display_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_up_arr_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_display_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_display_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_up_arr_day_img, &style_setting_screen_display_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_display_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_display_up_arr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_display_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_display_up_arr_day_img, 0);

	//Write codes Setting_Screen_display_down_arr_day_img
	ui->Setting_Screen_display_down_arr_day_img = lv_img_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_down_arr_day_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_display_down_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_down_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_display_down_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_down_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_down_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_down_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_down_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_down_arr_day_img, &style_setting_screen_display_down_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_display_down_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_display_down_arr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_display_down_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_display_down_arr_day_img, 0);

	//Write codes Setting_Screen_display_day_L1
	ui->Setting_Screen_display_day_L1 = lv_label_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_day_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_display_day_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_display_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_display_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_display_day_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_day_l1_main_main_default
	static lv_style_t style_setting_screen_display_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_display_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_display_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_display_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_display_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_display_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_display_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_display_day_l1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_display_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_display_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_display_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_display_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_display_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_display_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_display_day_L1, &style_setting_screen_display_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_day_L2
	ui->Setting_Screen_display_day_L2 = lv_label_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_day_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_display_day_L2, 240, 18);
	lv_label_set_text(ui->Setting_Screen_display_day_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_display_day_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_display_day_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_day_l2_main_main_default
	static lv_style_t style_setting_screen_display_day_l2_main_main_default;
	lv_style_reset(&style_setting_screen_display_day_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_display_day_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_display_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_display_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_display_day_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_display_day_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_display_day_l2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_display_day_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_display_day_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_display_day_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_display_day_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_display_day_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_display_day_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_display_day_L2, &style_setting_screen_display_day_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_day_L3
	ui->Setting_Screen_display_day_L3 = lv_label_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_day_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_display_day_L3, 240, 18);
	lv_label_set_text(ui->Setting_Screen_display_day_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_display_day_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_display_day_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_day_l3_main_main_default
	static lv_style_t style_setting_screen_display_day_l3_main_main_default;
	lv_style_reset(&style_setting_screen_display_day_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_display_day_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_display_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_display_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_display_day_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_display_day_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_display_day_l3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_display_day_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_display_day_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_display_day_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_display_day_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_display_day_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_display_day_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_display_day_L3, &style_setting_screen_display_day_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes Setting_Screen_setting_connect_night_container
	ui->Setting_Screen_setting_connect_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_connect_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_connect_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_connect_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_connect_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_connect_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_connect_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_connect_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_connect_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_connect_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_connect_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_connect_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_connect_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_connect_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_connect_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_connect_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_connect_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_connect_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_connect_night_container, &style_setting_screen_setting_connect_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_connnect_side_night_img
	ui->Setting_Screen_connnect_side_night_img = lv_img_create(ui->Setting_Screen_setting_connect_night_container);
	lv_obj_set_pos(ui->Setting_Screen_connnect_side_night_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_connnect_side_night_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connnect_side_night_img_main_main_default
	static lv_style_t style_setting_screen_connnect_side_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_connnect_side_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connnect_side_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connnect_side_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connnect_side_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connnect_side_night_img, &style_setting_screen_connnect_side_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_connect_sub_button_night_img
	ui->Setting_Screen_connect_sub_button_night_img = lv_img_create(ui->Setting_Screen_setting_connect_night_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_sub_button_night_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_connect_sub_button_night_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_sub_button_night_img_main_main_default
	static lv_style_t style_setting_screen_connect_sub_button_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_sub_button_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_sub_button_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_sub_button_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_sub_button_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_sub_button_night_img, &style_setting_screen_connect_sub_button_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_sub_button_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_sub_button_night_img,&subbtn_night_24x24);
	lv_img_set_pivot(ui->Setting_Screen_connect_sub_button_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_sub_button_night_img, 0);

	//Write codes Setting_Screen_connect_switch_btn_night_img
	ui->Setting_Screen_connect_switch_btn_night_img = lv_img_create(ui->Setting_Screen_setting_connect_night_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_switch_btn_night_img, 179, 147);
	lv_obj_set_size(ui->Setting_Screen_connect_switch_btn_night_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_switch_btn_night_img_main_main_default
	static lv_style_t style_setting_screen_connect_switch_btn_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_switch_btn_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_switch_btn_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_switch_btn_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_switch_btn_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_switch_btn_night_img, &style_setting_screen_connect_switch_btn_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_switch_btn_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_switch_btn_night_img,&_btn_1_29x20);
	lv_img_set_pivot(ui->Setting_Screen_connect_switch_btn_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_switch_btn_night_img, 0);

	//Write codes Setting_Screen_connect_up_arr_night_img
	ui->Setting_Screen_connect_up_arr_night_img = lv_img_create(ui->Setting_Screen_setting_connect_night_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_up_arr_night_img, 110, 105);
	lv_obj_set_size(ui->Setting_Screen_connect_up_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_up_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_connect_up_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_up_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_up_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_up_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_up_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_up_arr_night_img, &style_setting_screen_connect_up_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_up_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_up_arr_night_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_connect_up_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_up_arr_night_img, 0);

	//Write codes Setting_Screen_connect_down_arr_night_img
	ui->Setting_Screen_connect_down_arr_night_img = lv_img_create(ui->Setting_Screen_setting_connect_night_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_down_arr_night_img, 110, 198);
	lv_obj_set_size(ui->Setting_Screen_connect_down_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_down_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_connect_down_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_down_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_down_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_down_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_down_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_down_arr_night_img, &style_setting_screen_connect_down_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_down_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_down_arr_night_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_connect_down_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_down_arr_night_img, 0);

	//Write codes Setting_Screen_connect_night_L1
	ui->Setting_Screen_connect_night_L1 = lv_label_create(ui->Setting_Screen_setting_connect_night_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_night_L1, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_connect_night_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_connect_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_connect_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_connect_night_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_night_l1_main_main_default
	static lv_style_t style_setting_screen_connect_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_connect_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_connect_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_connect_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_connect_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_connect_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_connect_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_connect_night_l1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_connect_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_connect_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_connect_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_connect_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_connect_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_connect_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_connect_night_L1, &style_setting_screen_connect_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_connect_day_container
	ui->Setting_Screen_setting_connect_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_connect_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_connect_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_connect_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_connect_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_connect_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_connect_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_connect_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_connect_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_connect_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_connect_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_connect_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_connect_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_connect_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_connect_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_connect_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_connect_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_connect_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_connect_day_container, &style_setting_screen_setting_connect_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_connect_day_circle_img
	ui->Setting_Screen_connect_day_circle_img = lv_img_create(ui->Setting_Screen_setting_connect_day_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_connect_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_connect_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_day_circle_img, &style_setting_screen_connect_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_connect_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_day_circle_img, 0);

	//Write codes Setting_Screen_connect_side_day_img
	ui->Setting_Screen_connect_side_day_img = lv_img_create(ui->Setting_Screen_setting_connect_day_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_side_day_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_connect_side_day_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_side_day_img_main_main_default
	static lv_style_t style_setting_screen_connect_side_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_side_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_side_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_side_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_side_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_side_day_img, &style_setting_screen_connect_side_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_connect_sub_button_day_img
	ui->Setting_Screen_connect_sub_button_day_img = lv_img_create(ui->Setting_Screen_setting_connect_day_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_sub_button_day_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_connect_sub_button_day_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_sub_button_day_img_main_main_default
	static lv_style_t style_setting_screen_connect_sub_button_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_sub_button_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_sub_button_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_sub_button_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_sub_button_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_sub_button_day_img, &style_setting_screen_connect_sub_button_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_sub_button_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_sub_button_day_img,&subbtn_day_24x24);
	lv_img_set_pivot(ui->Setting_Screen_connect_sub_button_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_sub_button_day_img, 0);

	//Write codes Setting_Screen_connect_switch_btn_day_img
	ui->Setting_Screen_connect_switch_btn_day_img = lv_img_create(ui->Setting_Screen_setting_connect_day_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_switch_btn_day_img, 179, 147);
	lv_obj_set_size(ui->Setting_Screen_connect_switch_btn_day_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_switch_btn_day_img_main_main_default
	static lv_style_t style_setting_screen_connect_switch_btn_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_switch_btn_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_switch_btn_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_switch_btn_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_switch_btn_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_switch_btn_day_img, &style_setting_screen_connect_switch_btn_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_switch_btn_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_switch_btn_day_img,&_day_toogle_on_29x20);
	lv_img_set_pivot(ui->Setting_Screen_connect_switch_btn_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_switch_btn_day_img, 0);

	//Write codes Setting_Screen_connect_up_arr_day_img
	ui->Setting_Screen_connect_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_connect_day_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_up_arr_day_img, 110, 105);
	lv_obj_set_size(ui->Setting_Screen_connect_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_connect_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_up_arr_day_img, &style_setting_screen_connect_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_up_arr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_connect_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_up_arr_day_img, 0);

	//Write codes Setting_Screen_connect_dow_arr_day_img
	ui->Setting_Screen_connect_dow_arr_day_img = lv_img_create(ui->Setting_Screen_setting_connect_day_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_dow_arr_day_img, 110, 198);
	lv_obj_set_size(ui->Setting_Screen_connect_dow_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_dow_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_connect_dow_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_dow_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_dow_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_dow_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_dow_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_dow_arr_day_img, &style_setting_screen_connect_dow_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_dow_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_dow_arr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_connect_dow_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_dow_arr_day_img, 0);

	//Write codes Setting_Screen_connect_day_L1
	ui->Setting_Screen_connect_day_L1 = lv_label_create(ui->Setting_Screen_setting_connect_day_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_day_L1, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_connect_day_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_connect_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_connect_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_connect_day_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_day_l1_main_main_default
	static lv_style_t style_setting_screen_connect_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_connect_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_connect_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_connect_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_connect_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_connect_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_connect_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_connect_day_l1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_connect_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_connect_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_connect_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_connect_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_connect_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_connect_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_connect_day_L1, &style_setting_screen_connect_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_music_night_container
	ui->Setting_Screen_setting_music_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_music_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_music_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_music_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_music_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_music_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_music_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_music_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_music_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_music_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_music_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_music_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_music_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_music_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_music_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_music_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_music_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_music_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_music_night_container, &style_setting_screen_setting_music_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_music_sel_btn1_img
	ui->Setting_Screen_music_sel_btn1_img = lv_img_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_sel_btn1_img, 176, 101);
	lv_obj_set_size(ui->Setting_Screen_music_sel_btn1_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_sel_btn1_img_main_main_default
	static lv_style_t style_setting_screen_music_sel_btn1_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_sel_btn1_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_sel_btn1_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_sel_btn1_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_sel_btn1_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_sel_btn1_img, &style_setting_screen_music_sel_btn1_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_sel_btn1_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_sel_btn1_img,&_radiobtn_night_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_music_sel_btn1_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_sel_btn1_img, 0);

	//Write codes Setting_Screen_music_sel_btn2_img
	ui->Setting_Screen_music_sel_btn2_img = lv_img_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_sel_btn2_img, 176, 150);
	lv_obj_set_size(ui->Setting_Screen_music_sel_btn2_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_sel_btn2_img_main_main_default
	static lv_style_t style_setting_screen_music_sel_btn2_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_sel_btn2_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_sel_btn2_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_sel_btn2_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_sel_btn2_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_sel_btn2_img, &style_setting_screen_music_sel_btn2_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_sel_btn2_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_sel_btn2_img,&_radiobtn_night_Checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_music_sel_btn2_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_sel_btn2_img, 0);

	//Write codes Setting_Screen_music_sel_btn3_img
	ui->Setting_Screen_music_sel_btn3_img = lv_img_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_sel_btn3_img, 176, 198);
	lv_obj_set_size(ui->Setting_Screen_music_sel_btn3_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_sel_btn3_img_main_main_default
	static lv_style_t style_setting_screen_music_sel_btn3_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_sel_btn3_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_sel_btn3_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_sel_btn3_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_sel_btn3_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_sel_btn3_img, &style_setting_screen_music_sel_btn3_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_sel_btn3_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_sel_btn3_img,&_radiobtn_night_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_music_sel_btn3_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_sel_btn3_img, 0);

	//Write codes Setting_Screen_music_up_arr_night_img
	ui->Setting_Screen_music_up_arr_night_img = lv_img_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_up_arr_night_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_music_up_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_up_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_music_up_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_up_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_up_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_up_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_up_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_up_arr_night_img, &style_setting_screen_music_up_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_up_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_up_arr_night_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_music_up_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_up_arr_night_img, 0);

	//Write codes Setting_Screen_music_down_arr_night_img
	ui->Setting_Screen_music_down_arr_night_img = lv_img_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_down_arr_night_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_music_down_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_down_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_music_down_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_down_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_down_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_down_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_down_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_down_arr_night_img, &style_setting_screen_music_down_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_down_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_down_arr_night_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_music_down_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_down_arr_night_img, 0);

	//Write codes Setting_Screen_music_night_L1
	ui->Setting_Screen_music_night_L1 = lv_label_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_night_L1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_music_night_L1, 100, 18);
	lv_label_set_text(ui->Setting_Screen_music_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_music_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_music_night_L1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_night_l1_main_main_default
	static lv_style_t style_setting_screen_music_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_music_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_music_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_music_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_music_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_music_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_music_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_music_night_l1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_music_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_music_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_music_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_music_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_music_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_music_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_music_night_L1, &style_setting_screen_music_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_music_night_L2
	ui->Setting_Screen_music_night_L2 = lv_label_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_night_L2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_music_night_L2, 100, 18);
	lv_label_set_text(ui->Setting_Screen_music_night_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_music_night_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_music_night_L2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_night_l2_main_main_default
	static lv_style_t style_setting_screen_music_night_l2_main_main_default;
	lv_style_reset(&style_setting_screen_music_night_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_music_night_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_music_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_music_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_music_night_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_music_night_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_music_night_l2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_music_night_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_music_night_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_music_night_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_music_night_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_music_night_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_music_night_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_music_night_L2, &style_setting_screen_music_night_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_music_night_L3
	ui->Setting_Screen_music_night_L3 = lv_label_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_night_L3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_music_night_L3, 100, 18);
	lv_label_set_text(ui->Setting_Screen_music_night_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_music_night_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_music_night_L3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_night_l3_main_main_default
	static lv_style_t style_setting_screen_music_night_l3_main_main_default;
	lv_style_reset(&style_setting_screen_music_night_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_music_night_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_music_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_music_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_music_night_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_music_night_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_music_night_l3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_music_night_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_music_night_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_music_night_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_music_night_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_music_night_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_music_night_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_music_night_L3, &style_setting_screen_music_night_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_music_day_container
	ui->Setting_Screen_setting_music_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_music_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_music_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_music_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_music_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_music_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_music_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_music_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_music_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_music_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_music_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_music_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_music_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_music_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_music_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_music_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_music_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_music_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_music_day_container, &style_setting_screen_setting_music_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_music_day_cicrcle_img
	ui->Setting_Screen_music_day_cicrcle_img = lv_img_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_day_cicrcle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_music_day_cicrcle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_day_cicrcle_img_main_main_default
	static lv_style_t style_setting_screen_music_day_cicrcle_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_day_cicrcle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_day_cicrcle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_day_cicrcle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_day_cicrcle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_day_cicrcle_img, &style_setting_screen_music_day_cicrcle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_day_cicrcle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_day_cicrcle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_music_day_cicrcle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_day_cicrcle_img, 0);

	//Write codes Setting_Screen_music_sel_day_btn1_img
	ui->Setting_Screen_music_sel_day_btn1_img = lv_img_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_sel_day_btn1_img, 176, 101);
	lv_obj_set_size(ui->Setting_Screen_music_sel_day_btn1_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_sel_day_btn1_img_main_main_default
	static lv_style_t style_setting_screen_music_sel_day_btn1_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_sel_day_btn1_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_sel_day_btn1_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_sel_day_btn1_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_sel_day_btn1_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_sel_day_btn1_img, &style_setting_screen_music_sel_day_btn1_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_sel_day_btn1_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_sel_day_btn1_img,&_radiobtn_day_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_music_sel_day_btn1_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_sel_day_btn1_img, 0);

	//Write codes Setting_Screen_music_sel_day_btn2_img
	ui->Setting_Screen_music_sel_day_btn2_img = lv_img_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_sel_day_btn2_img, 176, 150);
	lv_obj_set_size(ui->Setting_Screen_music_sel_day_btn2_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_sel_day_btn2_img_main_main_default
	static lv_style_t style_setting_screen_music_sel_day_btn2_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_sel_day_btn2_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_sel_day_btn2_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_sel_day_btn2_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_sel_day_btn2_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_sel_day_btn2_img, &style_setting_screen_music_sel_day_btn2_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_sel_day_btn2_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_sel_day_btn2_img,&_radiobtn_day_checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_music_sel_day_btn2_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_sel_day_btn2_img, 0);

	//Write codes Setting_Screen_music_sel_day_btn3_img
	ui->Setting_Screen_music_sel_day_btn3_img = lv_img_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_sel_day_btn3_img, 176, 198);
	lv_obj_set_size(ui->Setting_Screen_music_sel_day_btn3_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_sel_day_btn3_img_main_main_default
	static lv_style_t style_setting_screen_music_sel_day_btn3_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_sel_day_btn3_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_sel_day_btn3_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_sel_day_btn3_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_sel_day_btn3_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_sel_day_btn3_img, &style_setting_screen_music_sel_day_btn3_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_sel_day_btn3_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_sel_day_btn3_img,&_radiobtn_day_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_music_sel_day_btn3_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_sel_day_btn3_img, 0);

	//Write codes Setting_Screen_music_up_arr_day_img
	ui->Setting_Screen_music_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_up_arr_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_music_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_music_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_up_arr_day_img, &style_setting_screen_music_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_up_arr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_music_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_up_arr_day_img, 0);

	//Write codes Setting_Screen_music_night_arr_day_img
	ui->Setting_Screen_music_night_arr_day_img = lv_img_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_night_arr_day_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_music_night_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_night_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_music_night_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_night_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_night_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_night_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_night_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_night_arr_day_img, &style_setting_screen_music_night_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_night_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_night_arr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_music_night_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_night_arr_day_img, 0);

	//Write codes Setting_Screen_music_day_L1
	ui->Setting_Screen_music_day_L1 = lv_label_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_day_L1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_music_day_L1, 100, 18);
	lv_label_set_text(ui->Setting_Screen_music_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_music_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_music_day_L1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_day_l1_main_main_default
	static lv_style_t style_setting_screen_music_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_music_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_music_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_music_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_music_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_music_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_music_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_music_day_l1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_music_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_music_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_music_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_music_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_music_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_music_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_music_day_L1, &style_setting_screen_music_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_music_day_L2
	ui->Setting_Screen_music_day_L2 = lv_label_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_day_L2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_music_day_L2, 100, 18);
	lv_label_set_text(ui->Setting_Screen_music_day_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_music_day_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_music_day_L2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_day_l2_main_main_default
	static lv_style_t style_setting_screen_music_day_l2_main_main_default;
	lv_style_reset(&style_setting_screen_music_day_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_music_day_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_music_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_music_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_music_day_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_music_day_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_music_day_l2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_music_day_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_music_day_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_music_day_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_music_day_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_music_day_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_music_day_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_music_day_L2, &style_setting_screen_music_day_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_music_day_L3
	ui->Setting_Screen_music_day_L3 = lv_label_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_day_L3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_music_day_L3, 100, 18);
	lv_label_set_text(ui->Setting_Screen_music_day_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_music_day_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_music_day_L3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_day_l3_main_main_default
	static lv_style_t style_setting_screen_music_day_l3_main_main_default;
	lv_style_reset(&style_setting_screen_music_day_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_music_day_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_music_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_music_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_music_day_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_music_day_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_music_day_l3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_music_day_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_music_day_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_music_day_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_music_day_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_music_day_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_music_day_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_music_day_L3, &style_setting_screen_music_day_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes Setting_Screen_setting_brightness_night_contain
	ui->Setting_Screen_setting_brightness_night_contain = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_brightness_night_contain, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_brightness_night_contain, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_brightness_night_contain_main_main_default
	static lv_style_t style_setting_screen_setting_brightness_night_contain_main_main_default;
	lv_style_reset(&style_setting_screen_setting_brightness_night_contain_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_brightness_night_contain_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_brightness_night_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_brightness_night_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_brightness_night_contain_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_brightness_night_contain_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_brightness_night_contain_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_brightness_night_contain_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_brightness_night_contain_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_brightness_night_contain_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_brightness_night_contain_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_brightness_night_contain_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_brightness_night_contain_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_brightness_night_contain, &style_setting_screen_setting_brightness_night_contain_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_brightness_sel_btn1_img
	ui->Setting_Screen_brightness_sel_btn1_img = lv_img_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_sel_btn1_img, 176, 103);
	lv_obj_set_size(ui->Setting_Screen_brightness_sel_btn1_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_sel_btn1_img_main_main_default
	static lv_style_t style_setting_screen_brightness_sel_btn1_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_sel_btn1_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_sel_btn1_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_sel_btn1_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_sel_btn1_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_sel_btn1_img, &style_setting_screen_brightness_sel_btn1_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_sel_btn1_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_sel_btn1_img,&_radiobtn_night_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_brightness_sel_btn1_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_sel_btn1_img, 0);

	//Write codes Setting_Screen_brightness_sel_btn2_img
	ui->Setting_Screen_brightness_sel_btn2_img = lv_img_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_sel_btn2_img, 176, 150);
	lv_obj_set_size(ui->Setting_Screen_brightness_sel_btn2_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_sel_btn2_img_main_main_default
	static lv_style_t style_setting_screen_brightness_sel_btn2_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_sel_btn2_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_sel_btn2_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_sel_btn2_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_sel_btn2_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_sel_btn2_img, &style_setting_screen_brightness_sel_btn2_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_sel_btn2_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_sel_btn2_img,&_radiobtn_night_Checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_brightness_sel_btn2_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_sel_btn2_img, 0);

	//Write codes Setting_Screen_brightness_sel_btn3_img
	ui->Setting_Screen_brightness_sel_btn3_img = lv_img_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_sel_btn3_img, 176, 198);
	lv_obj_set_size(ui->Setting_Screen_brightness_sel_btn3_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_sel_btn3_img_main_main_default
	static lv_style_t style_setting_screen_brightness_sel_btn3_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_sel_btn3_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_sel_btn3_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_sel_btn3_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_sel_btn3_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_sel_btn3_img, &style_setting_screen_brightness_sel_btn3_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_sel_btn3_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_sel_btn3_img,&_radiobtn_night_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_brightness_sel_btn3_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_sel_btn3_img, 0);

	//Write codes Setting_Screen_brightness_up_arr_night_img
	ui->Setting_Screen_brightness_up_arr_night_img = lv_img_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_up_arr_night_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_brightness_up_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_up_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_brightness_up_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_up_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_up_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_up_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_up_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_up_arr_night_img, &style_setting_screen_brightness_up_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_up_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_up_arr_night_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_brightness_up_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_up_arr_night_img, 0);

	//Write codes Setting_Screen_brightness_down_arr_night_img
	ui->Setting_Screen_brightness_down_arr_night_img = lv_img_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_down_arr_night_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_brightness_down_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_down_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_brightness_down_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_down_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_down_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_down_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_down_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_down_arr_night_img, &style_setting_screen_brightness_down_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_down_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_down_arr_night_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_brightness_down_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_down_arr_night_img, 0);

	//Write codes Setting_Screen_brightness_night_L1
	ui->Setting_Screen_brightness_night_L1 = lv_label_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_night_L1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_brightness_night_L1, 100, 18);
	lv_label_set_text(ui->Setting_Screen_brightness_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_brightness_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_brightness_night_L1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_night_l1_main_main_default
	static lv_style_t style_setting_screen_brightness_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_brightness_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_brightness_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_brightness_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_brightness_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_brightness_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_brightness_night_l1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_brightness_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_brightness_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_brightness_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_brightness_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_brightness_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_brightness_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_brightness_night_L1, &style_setting_screen_brightness_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_brightness_night_L2
	ui->Setting_Screen_brightness_night_L2 = lv_label_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_night_L2, 50, 148);
	lv_obj_set_size(ui->Setting_Screen_brightness_night_L2, 100, 18);
	lv_label_set_text(ui->Setting_Screen_brightness_night_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_brightness_night_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_brightness_night_L2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_night_l2_main_main_default
	static lv_style_t style_setting_screen_brightness_night_l2_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_night_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_brightness_night_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_brightness_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_brightness_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_brightness_night_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_brightness_night_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_brightness_night_l2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_brightness_night_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_brightness_night_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_brightness_night_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_brightness_night_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_brightness_night_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_brightness_night_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_brightness_night_L2, &style_setting_screen_brightness_night_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_brightness_night_L3
	ui->Setting_Screen_brightness_night_L3 = lv_label_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_night_L3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_brightness_night_L3, 100, 18);
	lv_label_set_text(ui->Setting_Screen_brightness_night_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_brightness_night_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_brightness_night_L3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_night_l3_main_main_default
	static lv_style_t style_setting_screen_brightness_night_l3_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_night_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_brightness_night_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_brightness_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_brightness_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_brightness_night_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_brightness_night_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_brightness_night_l3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_brightness_night_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_brightness_night_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_brightness_night_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_brightness_night_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_brightness_night_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_brightness_night_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_brightness_night_L3, &style_setting_screen_brightness_night_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_brightness_day_contain
	ui->Setting_Screen_setting_brightness_day_contain = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_brightness_day_contain, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_brightness_day_contain, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_brightness_day_contain_main_main_default
	static lv_style_t style_setting_screen_setting_brightness_day_contain_main_main_default;
	lv_style_reset(&style_setting_screen_setting_brightness_day_contain_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_brightness_day_contain_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_brightness_day_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_brightness_day_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_brightness_day_contain_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_brightness_day_contain_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_brightness_day_contain_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_brightness_day_contain_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_brightness_day_contain_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_brightness_day_contain_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_brightness_day_contain_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_brightness_day_contain_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_brightness_day_contain_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_brightness_day_contain, &style_setting_screen_setting_brightness_day_contain_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_day_circle_img
	ui->Setting_Screen_setting_day_circle_img = lv_img_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_setting_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_setting_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_setting_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_setting_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_setting_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_setting_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_setting_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_setting_day_circle_img, &style_setting_screen_setting_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_setting_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_setting_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_setting_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_setting_day_circle_img, 0);

	//Write codes Setting_Screen_brightness_sel_day_btn1_img
	ui->Setting_Screen_brightness_sel_day_btn1_img = lv_img_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_sel_day_btn1_img, 176, 103);
	lv_obj_set_size(ui->Setting_Screen_brightness_sel_day_btn1_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_sel_day_btn1_img_main_main_default
	static lv_style_t style_setting_screen_brightness_sel_day_btn1_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_sel_day_btn1_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_sel_day_btn1_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_sel_day_btn1_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_sel_day_btn1_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_sel_day_btn1_img, &style_setting_screen_brightness_sel_day_btn1_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_sel_day_btn1_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_sel_day_btn1_img,&_radiobtn_day_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_brightness_sel_day_btn1_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_sel_day_btn1_img, 0);

	//Write codes Setting_Screen_brightness_sel_day_btn2_img
	ui->Setting_Screen_brightness_sel_day_btn2_img = lv_img_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_sel_day_btn2_img, 176, 150);
	lv_obj_set_size(ui->Setting_Screen_brightness_sel_day_btn2_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_sel_day_btn2_img_main_main_default
	static lv_style_t style_setting_screen_brightness_sel_day_btn2_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_sel_day_btn2_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_sel_day_btn2_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_sel_day_btn2_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_sel_day_btn2_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_sel_day_btn2_img, &style_setting_screen_brightness_sel_day_btn2_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_sel_day_btn2_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_sel_day_btn2_img,&_radiobtn_day_checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_brightness_sel_day_btn2_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_sel_day_btn2_img, 0);

	//Write codes Setting_Screen_brightness_sel_day_btn3_img
	ui->Setting_Screen_brightness_sel_day_btn3_img = lv_img_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_sel_day_btn3_img, 176, 198);
	lv_obj_set_size(ui->Setting_Screen_brightness_sel_day_btn3_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_sel_day_btn3_img_main_main_default
	static lv_style_t style_setting_screen_brightness_sel_day_btn3_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_sel_day_btn3_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_sel_day_btn3_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_sel_day_btn3_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_sel_day_btn3_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_sel_day_btn3_img, &style_setting_screen_brightness_sel_day_btn3_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_sel_day_btn3_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_sel_day_btn3_img,&_radiobtn_day_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_brightness_sel_day_btn3_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_sel_day_btn3_img, 0);

	//Write codes Setting_Screen_brightness_up_arr_day_img
	ui->Setting_Screen_brightness_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_up_arr_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_brightness_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_brightness_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_up_arr_day_img, &style_setting_screen_brightness_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_up_arr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_brightness_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_up_arr_day_img, 0);

	//Write codes Setting_Screen_brightness_down_arr_day_img
	ui->Setting_Screen_brightness_down_arr_day_img = lv_img_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_down_arr_day_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_brightness_down_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_down_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_brightness_down_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_down_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_down_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_down_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_down_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_down_arr_day_img, &style_setting_screen_brightness_down_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_down_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_down_arr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_brightness_down_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_down_arr_day_img, 0);

	//Write codes Setting_Screen_brightness_day_L1
	ui->Setting_Screen_brightness_day_L1 = lv_label_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_day_L1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_brightness_day_L1, 110, 18);
	lv_label_set_text(ui->Setting_Screen_brightness_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_brightness_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_brightness_day_L1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_day_l1_main_main_default
	static lv_style_t style_setting_screen_brightness_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_brightness_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_brightness_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_brightness_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_brightness_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_brightness_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_brightness_day_l1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_brightness_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_brightness_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_brightness_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_brightness_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_brightness_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_brightness_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_brightness_day_L1, &style_setting_screen_brightness_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_brightness_day_L2
	ui->Setting_Screen_brightness_day_L2 = lv_label_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_day_L2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_brightness_day_L2, 110, 18);
	lv_label_set_text(ui->Setting_Screen_brightness_day_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_brightness_day_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_brightness_day_L2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_day_l2_main_main_default
	static lv_style_t style_setting_screen_brightness_day_l2_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_day_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_brightness_day_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_brightness_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_brightness_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_brightness_day_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_brightness_day_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_brightness_day_l2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_brightness_day_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_brightness_day_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_brightness_day_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_brightness_day_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_brightness_day_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_brightness_day_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_brightness_day_L2, &style_setting_screen_brightness_day_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_brightness_day_L3
	ui->Setting_Screen_brightness_day_L3 = lv_label_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_day_L3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_brightness_day_L3, 110, 18);
	lv_label_set_text(ui->Setting_Screen_brightness_day_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_brightness_day_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_brightness_day_L3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_day_l3_main_main_default
	static lv_style_t style_setting_screen_brightness_day_l3_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_day_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_brightness_day_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_brightness_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_brightness_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_brightness_day_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_brightness_day_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_brightness_day_l3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_brightness_day_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_brightness_day_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_brightness_day_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_brightness_day_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_brightness_day_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_brightness_day_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_brightness_day_L3, &style_setting_screen_brightness_day_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_menu_night_contain
	ui->Setting_Screen_setting_menu_night_contain = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_menu_night_contain, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_menu_night_contain, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_menu_night_contain_main_main_default
	static lv_style_t style_setting_screen_setting_menu_night_contain_main_main_default;
	lv_style_reset(&style_setting_screen_setting_menu_night_contain_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_menu_night_contain_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_menu_night_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_menu_night_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_menu_night_contain_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_menu_night_contain_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_menu_night_contain_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_menu_night_contain_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_menu_night_contain_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_menu_night_contain_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_menu_night_contain_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_menu_night_contain_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_menu_night_contain_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_menu_night_contain, &style_setting_screen_setting_menu_night_contain_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_menu_sel_btn1_img
	ui->Setting_Screen_menu_sel_btn1_img = lv_img_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_sel_btn1_img, 178, 101);
	lv_obj_set_size(ui->Setting_Screen_menu_sel_btn1_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_sel_btn1_img_main_main_default
	static lv_style_t style_setting_screen_menu_sel_btn1_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_sel_btn1_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_sel_btn1_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_sel_btn1_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_sel_btn1_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_sel_btn1_img, &style_setting_screen_menu_sel_btn1_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_sel_btn1_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_sel_btn1_img,&_radiobtn_night_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_menu_sel_btn1_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_sel_btn1_img, 0);

	//Write codes Setting_Screen_menu_sel_btn2_img
	ui->Setting_Screen_menu_sel_btn2_img = lv_img_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_sel_btn2_img, 178, 149);
	lv_obj_set_size(ui->Setting_Screen_menu_sel_btn2_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_sel_btn2_img_main_main_default
	static lv_style_t style_setting_screen_menu_sel_btn2_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_sel_btn2_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_sel_btn2_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_sel_btn2_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_sel_btn2_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_sel_btn2_img, &style_setting_screen_menu_sel_btn2_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_sel_btn2_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_sel_btn2_img,&_radiobtn_night_Checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_menu_sel_btn2_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_sel_btn2_img, 0);

	//Write codes Setting_Screen_menu_sel_btn3_img
	ui->Setting_Screen_menu_sel_btn3_img = lv_img_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_sel_btn3_img, 178, 198);
	lv_obj_set_size(ui->Setting_Screen_menu_sel_btn3_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_sel_btn3_img_main_main_default
	static lv_style_t style_setting_screen_menu_sel_btn3_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_sel_btn3_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_sel_btn3_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_sel_btn3_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_sel_btn3_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_sel_btn3_img, &style_setting_screen_menu_sel_btn3_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_sel_btn3_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_sel_btn3_img,&_radiobtn_night_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_menu_sel_btn3_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_sel_btn3_img, 0);

	//Write codes Setting_Screen_menu_up_arr_day_img
	ui->Setting_Screen_menu_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_up_arr_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_menu_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_menu_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_up_arr_day_img, &style_setting_screen_menu_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_up_arr_day_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_menu_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_up_arr_day_img, 0);

	//Write codes Setting_Screen_menu_down_arr_day_img
	ui->Setting_Screen_menu_down_arr_day_img = lv_img_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_down_arr_day_img, 110, 258);
	lv_obj_set_size(ui->Setting_Screen_menu_down_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_down_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_menu_down_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_down_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_down_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_down_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_down_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_down_arr_day_img, &style_setting_screen_menu_down_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_down_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_down_arr_day_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_menu_down_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_down_arr_day_img, 0);

	//Write codes Setting_Screen_menu_night_L1
	ui->Setting_Screen_menu_night_L1 = lv_label_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_night_L1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_menu_night_L1, 130, 18);
	lv_label_set_text(ui->Setting_Screen_menu_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_menu_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_menu_night_L1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_night_l1_main_main_default
	static lv_style_t style_setting_screen_menu_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_menu_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_menu_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_menu_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_menu_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_menu_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_menu_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_menu_night_l1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_menu_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_menu_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_menu_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_menu_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_menu_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_menu_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_menu_night_L1, &style_setting_screen_menu_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_menu_night_L2
	ui->Setting_Screen_menu_night_L2 = lv_label_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_night_L2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_menu_night_L2, 130, 18);
	lv_label_set_text(ui->Setting_Screen_menu_night_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_menu_night_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_menu_night_L2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_night_l2_main_main_default
	static lv_style_t style_setting_screen_menu_night_l2_main_main_default;
	lv_style_reset(&style_setting_screen_menu_night_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_menu_night_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_menu_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_menu_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_menu_night_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_menu_night_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_menu_night_l2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_menu_night_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_menu_night_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_menu_night_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_menu_night_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_menu_night_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_menu_night_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_menu_night_L2, &style_setting_screen_menu_night_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_menu_night_L3
	ui->Setting_Screen_menu_night_L3 = lv_label_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_night_L3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_menu_night_L3, 130, 18);
	lv_label_set_text(ui->Setting_Screen_menu_night_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_menu_night_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_menu_night_L3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_night_l3_main_main_default
	static lv_style_t style_setting_screen_menu_night_l3_main_main_default;
	lv_style_reset(&style_setting_screen_menu_night_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_menu_night_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_menu_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_menu_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_menu_night_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_menu_night_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_menu_night_l3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_menu_night_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_menu_night_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_menu_night_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_menu_night_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_menu_night_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_menu_night_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_menu_night_L3, &style_setting_screen_menu_night_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_menu_day_contain
	ui->Setting_Screen_setting_menu_day_contain = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_menu_day_contain, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_menu_day_contain, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_menu_day_contain_main_main_default
	static lv_style_t style_setting_screen_setting_menu_day_contain_main_main_default;
	lv_style_reset(&style_setting_screen_setting_menu_day_contain_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_menu_day_contain_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_menu_day_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_menu_day_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_menu_day_contain_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_menu_day_contain_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_menu_day_contain_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_menu_day_contain_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_menu_day_contain_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_menu_day_contain_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_menu_day_contain_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_menu_day_contain_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_menu_day_contain_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_menu_day_contain, &style_setting_screen_setting_menu_day_contain_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_menu_day_circle_img
	ui->Setting_Screen_menu_day_circle_img = lv_img_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_menu_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_menu_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_day_circle_img, &style_setting_screen_menu_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_menu_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_day_circle_img, 0);

	//Write codes Setting_Screen_menu_sel_day_btn1_img
	ui->Setting_Screen_menu_sel_day_btn1_img = lv_img_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_sel_day_btn1_img, 176, 101);
	lv_obj_set_size(ui->Setting_Screen_menu_sel_day_btn1_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_sel_day_btn1_img_main_main_default
	static lv_style_t style_setting_screen_menu_sel_day_btn1_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_sel_day_btn1_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_sel_day_btn1_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_sel_day_btn1_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_sel_day_btn1_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_sel_day_btn1_img, &style_setting_screen_menu_sel_day_btn1_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_sel_day_btn1_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_sel_day_btn1_img,&_radiobtn_day_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_menu_sel_day_btn1_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_sel_day_btn1_img, 0);

	//Write codes Setting_Screen_menu_sel_day_btn2_img
	ui->Setting_Screen_menu_sel_day_btn2_img = lv_img_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_sel_day_btn2_img, 176, 150);
	lv_obj_set_size(ui->Setting_Screen_menu_sel_day_btn2_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_sel_day_btn2_img_main_main_default
	static lv_style_t style_setting_screen_menu_sel_day_btn2_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_sel_day_btn2_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_sel_day_btn2_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_sel_day_btn2_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_sel_day_btn2_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_sel_day_btn2_img, &style_setting_screen_menu_sel_day_btn2_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_sel_day_btn2_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_sel_day_btn2_img,&_radiobtn_day_checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_menu_sel_day_btn2_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_sel_day_btn2_img, 0);

	//Write codes Setting_Screen_menu_sel_day_btn3_img
	ui->Setting_Screen_menu_sel_day_btn3_img = lv_img_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_sel_day_btn3_img, 176, 198);
	lv_obj_set_size(ui->Setting_Screen_menu_sel_day_btn3_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_sel_day_btn3_img_main_main_default
	static lv_style_t style_setting_screen_menu_sel_day_btn3_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_sel_day_btn3_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_sel_day_btn3_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_sel_day_btn3_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_sel_day_btn3_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_sel_day_btn3_img, &style_setting_screen_menu_sel_day_btn3_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_sel_day_btn3_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_sel_day_btn3_img,&_radiobtn_day_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_menu_sel_day_btn3_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_sel_day_btn3_img, 0);

	//Write codes Setting_Screen_menu_up_darr_day_img
	ui->Setting_Screen_menu_up_darr_day_img = lv_img_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_up_darr_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_menu_up_darr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_up_darr_day_img_main_main_default
	static lv_style_t style_setting_screen_menu_up_darr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_up_darr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_up_darr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_up_darr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_up_darr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_up_darr_day_img, &style_setting_screen_menu_up_darr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_up_darr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_up_darr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_menu_up_darr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_up_darr_day_img, 0);

	//Write codes Setting_Screen_menu_down_darr_day_img
	ui->Setting_Screen_menu_down_darr_day_img = lv_img_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_down_darr_day_img, 110, 245);
	lv_obj_set_size(ui->Setting_Screen_menu_down_darr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_down_darr_day_img_main_main_default
	static lv_style_t style_setting_screen_menu_down_darr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_down_darr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_down_darr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_down_darr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_down_darr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_down_darr_day_img, &style_setting_screen_menu_down_darr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_down_darr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_down_darr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_menu_down_darr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_down_darr_day_img, 0);

	//Write codes Setting_Screen_menu_day_L1
	ui->Setting_Screen_menu_day_L1 = lv_label_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_day_L1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_menu_day_L1, 130, 18);
	lv_label_set_text(ui->Setting_Screen_menu_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_menu_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_menu_day_L1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_day_l1_main_main_default
	static lv_style_t style_setting_screen_menu_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_menu_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_menu_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_menu_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_menu_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_menu_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_menu_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_menu_day_l1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_menu_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_menu_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_menu_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_menu_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_menu_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_menu_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_menu_day_L1, &style_setting_screen_menu_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_menu_day_L2
	ui->Setting_Screen_menu_day_L2 = lv_label_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_day_L2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_menu_day_L2, 130, 18);
	lv_label_set_text(ui->Setting_Screen_menu_day_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_menu_day_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_menu_day_L2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_day_l2_main_main_default
	static lv_style_t style_setting_screen_menu_day_l2_main_main_default;
	lv_style_reset(&style_setting_screen_menu_day_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_menu_day_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_menu_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_menu_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_menu_day_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_menu_day_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_menu_day_l2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_menu_day_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_menu_day_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_menu_day_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_menu_day_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_menu_day_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_menu_day_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_menu_day_L2, &style_setting_screen_menu_day_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_menu_day_L3
	ui->Setting_Screen_menu_day_L3 = lv_label_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_day_L3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_menu_day_L3, 130, 18);
	lv_label_set_text(ui->Setting_Screen_menu_day_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_menu_day_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_menu_day_L3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_day_l3_main_main_default
	static lv_style_t style_setting_screen_menu_day_l3_main_main_default;
	lv_style_reset(&style_setting_screen_menu_day_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_menu_day_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_menu_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_menu_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_menu_day_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_menu_day_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_menu_day_l3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_menu_day_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_menu_day_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_menu_day_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_menu_day_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_menu_day_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_menu_day_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_menu_day_L3, &style_setting_screen_menu_day_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes Setting_Screen_seting_date_time_container
	ui->Setting_Screen_seting_date_time_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_seting_date_time_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_seting_date_time_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_seting_date_time_container_main_main_default
	static lv_style_t style_setting_screen_seting_date_time_container_main_main_default;
	lv_style_reset(&style_setting_screen_seting_date_time_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_seting_date_time_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_seting_date_time_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_seting_date_time_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_seting_date_time_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_seting_date_time_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_seting_date_time_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_seting_date_time_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_seting_date_time_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_seting_date_time_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_seting_date_time_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_seting_date_time_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_seting_date_time_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_seting_date_time_container, &style_setting_screen_seting_date_time_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_data_time_night_icon_img
	ui->Setting_Screen_data_time_night_icon_img = lv_img_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_night_icon_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_data_time_night_icon_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_night_icon_img_main_main_default
	static lv_style_t style_setting_screen_data_time_night_icon_img_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_night_icon_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_night_icon_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_night_icon_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_night_icon_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_night_icon_img, &style_setting_screen_data_time_night_icon_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_data_time_night_sub_button_img
	ui->Setting_Screen_data_time_night_sub_button_img = lv_img_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_night_sub_button_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_data_time_night_sub_button_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_night_sub_button_img_main_main_default
	static lv_style_t style_setting_screen_data_time_night_sub_button_img_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_night_sub_button_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_night_sub_button_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_night_sub_button_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_night_sub_button_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_night_sub_button_img, &style_setting_screen_data_time_night_sub_button_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_data_time_night_sub_button_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_data_time_night_sub_button_img,&subbtn_night_24x24);
	lv_img_set_pivot(ui->Setting_Screen_data_time_night_sub_button_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_data_time_night_sub_button_img, 0);

	//Write codes Setting_Screen_data_time_night_toggl_btn
	ui->Setting_Screen_data_time_night_toggl_btn = lv_img_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_night_toggl_btn, 179, 230);
	lv_obj_set_size(ui->Setting_Screen_data_time_night_toggl_btn, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_night_toggl_btn_main_main_default
	static lv_style_t style_setting_screen_data_time_night_toggl_btn_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_night_toggl_btn_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_night_toggl_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_night_toggl_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_night_toggl_btn_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_night_toggl_btn, &style_setting_screen_data_time_night_toggl_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_data_time_night_toggl_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_data_time_night_toggl_btn,&_day_toogle_on_29x20);
	lv_img_set_pivot(ui->Setting_Screen_data_time_night_toggl_btn, 0,0);
	lv_img_set_angle(ui->Setting_Screen_data_time_night_toggl_btn, 0);

	//Write codes Setting_Screen_data_time_up_arr_nigh_button_img
	ui->Setting_Screen_data_time_up_arr_nigh_button_img = lv_img_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_up_arr_nigh_button_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_data_time_up_arr_nigh_button_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_up_arr_nigh_button_img_main_main_default
	static lv_style_t style_setting_screen_data_time_up_arr_nigh_button_img_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_up_arr_nigh_button_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_up_arr_nigh_button_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_up_arr_nigh_button_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_up_arr_nigh_button_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_up_arr_nigh_button_img, &style_setting_screen_data_time_up_arr_nigh_button_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_data_time_up_arr_nigh_button_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_data_time_up_arr_nigh_button_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_data_time_up_arr_nigh_button_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_data_time_up_arr_nigh_button_img, 0);

	//Write codes Setting_Screen_data_time_do_arr_nigh_button_img
	ui->Setting_Screen_data_time_do_arr_nigh_button_img = lv_img_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_do_arr_nigh_button_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_data_time_do_arr_nigh_button_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_do_arr_nigh_button_img_main_main_default
	static lv_style_t style_setting_screen_data_time_do_arr_nigh_button_img_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_do_arr_nigh_button_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_do_arr_nigh_button_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_do_arr_nigh_button_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_do_arr_nigh_button_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_do_arr_nigh_button_img, &style_setting_screen_data_time_do_arr_nigh_button_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_data_time_do_arr_nigh_button_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_data_time_do_arr_nigh_button_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_data_time_do_arr_nigh_button_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_data_time_do_arr_nigh_button_img, 0);

	//Write codes Setting_Screen_data_time_do_arr_nigh_LB1
	ui->Setting_Screen_data_time_do_arr_nigh_LB1 = lv_label_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_do_arr_nigh_LB1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_data_time_do_arr_nigh_LB1, 126, 18);
	lv_label_set_text(ui->Setting_Screen_data_time_do_arr_nigh_LB1, "");
	lv_label_set_long_mode(ui->Setting_Screen_data_time_do_arr_nigh_LB1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_data_time_do_arr_nigh_LB1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default
	static lv_style_t style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default);
	lv_style_set_radius(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_data_time_do_arr_nigh_LB1, &style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_data_time_do_arr_nigh_LB2
	ui->Setting_Screen_data_time_do_arr_nigh_LB2 = lv_label_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_do_arr_nigh_LB2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_data_time_do_arr_nigh_LB2, 126, 18);
	lv_label_set_text(ui->Setting_Screen_data_time_do_arr_nigh_LB2, "");
	lv_label_set_long_mode(ui->Setting_Screen_data_time_do_arr_nigh_LB2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_data_time_do_arr_nigh_LB2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default
	static lv_style_t style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default);
	lv_style_set_radius(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_data_time_do_arr_nigh_LB2, &style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_data_time_do_arr_nigh_LB3
	ui->Setting_Screen_data_time_do_arr_nigh_LB3 = lv_label_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_do_arr_nigh_LB3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_data_time_do_arr_nigh_LB3, 126, 18);
	lv_label_set_text(ui->Setting_Screen_data_time_do_arr_nigh_LB3, "");
	lv_label_set_long_mode(ui->Setting_Screen_data_time_do_arr_nigh_LB3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_data_time_do_arr_nigh_LB3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default
	static lv_style_t style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default);
	lv_style_set_radius(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_data_time_do_arr_nigh_LB3, &style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_seting_date_time_day_container
	ui->Setting_Screen_seting_date_time_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_seting_date_time_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_seting_date_time_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_seting_date_time_day_container_main_main_default
	static lv_style_t style_setting_screen_seting_date_time_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_seting_date_time_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_seting_date_time_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_seting_date_time_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_seting_date_time_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_seting_date_time_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_seting_date_time_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_seting_date_time_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_seting_date_time_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_seting_date_time_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_seting_date_time_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_seting_date_time_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_seting_date_time_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_seting_date_time_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_seting_date_time_day_container, &style_setting_screen_seting_date_time_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_day_circle_img
	ui->Setting_Screen_date_day_circle_img = lv_img_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_date_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_date_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_circle_img, &style_setting_screen_date_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_date_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_circle_img, 0);

	//Write codes Setting_Screen_date_side_day_img
	ui->Setting_Screen_date_side_day_img = lv_img_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_date_side_day_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_date_side_day_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_side_day_img_main_main_default
	static lv_style_t style_setting_screen_date_side_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_date_side_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_side_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_side_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_side_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_side_day_img, &style_setting_screen_date_side_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_sub_btn_day_img
	ui->Setting_Screen_date_sub_btn_day_img = lv_img_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_date_sub_btn_day_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_date_sub_btn_day_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_sub_btn_day_img_main_main_default
	static lv_style_t style_setting_screen_date_sub_btn_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_date_sub_btn_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_sub_btn_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_sub_btn_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_sub_btn_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_sub_btn_day_img, &style_setting_screen_date_sub_btn_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_sub_btn_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_sub_btn_day_img,&subbtn_day_24x24);
	lv_img_set_pivot(ui->Setting_Screen_date_sub_btn_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_sub_btn_day_img, 0);

	//Write codes Setting_Screen_data_time_day_toggl_btn
	ui->Setting_Screen_data_time_day_toggl_btn = lv_img_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_day_toggl_btn, 149, 170);
	lv_obj_set_size(ui->Setting_Screen_data_time_day_toggl_btn, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_day_toggl_btn_main_main_default
	static lv_style_t style_setting_screen_data_time_day_toggl_btn_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_day_toggl_btn_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_day_toggl_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_day_toggl_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_day_toggl_btn_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_day_toggl_btn, &style_setting_screen_data_time_day_toggl_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_data_time_day_toggl_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_data_time_day_toggl_btn,&_day_toogle_on_29x20);
	lv_img_set_pivot(ui->Setting_Screen_data_time_day_toggl_btn, 0,0);
	lv_img_set_angle(ui->Setting_Screen_data_time_day_toggl_btn, 0);

	//Write codes Setting_Screen_data_time_up_arr_day_button_img
	ui->Setting_Screen_data_time_up_arr_day_button_img = lv_img_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_up_arr_day_button_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_data_time_up_arr_day_button_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_up_arr_day_button_img_main_main_default
	static lv_style_t style_setting_screen_data_time_up_arr_day_button_img_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_up_arr_day_button_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_up_arr_day_button_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_up_arr_day_button_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_up_arr_day_button_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_up_arr_day_button_img, &style_setting_screen_data_time_up_arr_day_button_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_data_time_up_arr_day_button_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_data_time_up_arr_day_button_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_data_time_up_arr_day_button_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_data_time_up_arr_day_button_img, 0);

	//Write codes Setting_Screen_data_time_dow_arr_day_button_img
	ui->Setting_Screen_data_time_dow_arr_day_button_img = lv_img_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_dow_arr_day_button_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_data_time_dow_arr_day_button_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_dow_arr_day_button_img_main_main_default
	static lv_style_t style_setting_screen_data_time_dow_arr_day_button_img_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_dow_arr_day_button_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_dow_arr_day_button_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_dow_arr_day_button_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_dow_arr_day_button_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_dow_arr_day_button_img, &style_setting_screen_data_time_dow_arr_day_button_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_data_time_dow_arr_day_button_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_data_time_dow_arr_day_button_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_data_time_dow_arr_day_button_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_data_time_dow_arr_day_button_img, 0);

	//Write codes Setting_Screen_data_time_do_arr_day_LB1
	ui->Setting_Screen_data_time_do_arr_day_LB1 = lv_label_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_do_arr_day_LB1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_data_time_do_arr_day_LB1, 126, 18);
	lv_label_set_text(ui->Setting_Screen_data_time_do_arr_day_LB1, "");
	lv_label_set_long_mode(ui->Setting_Screen_data_time_do_arr_day_LB1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_data_time_do_arr_day_LB1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_do_arr_day_lb1_main_main_default
	static lv_style_t style_setting_screen_data_time_do_arr_day_lb1_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default);
	lv_style_set_radius(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_data_time_do_arr_day_LB1, &style_setting_screen_data_time_do_arr_day_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_data_time_do_arr_day_LB2
	ui->Setting_Screen_data_time_do_arr_day_LB2 = lv_label_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_do_arr_day_LB2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_data_time_do_arr_day_LB2, 126, 18);
	lv_label_set_text(ui->Setting_Screen_data_time_do_arr_day_LB2, "");
	lv_label_set_long_mode(ui->Setting_Screen_data_time_do_arr_day_LB2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_data_time_do_arr_day_LB2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_do_arr_day_lb2_main_main_default
	static lv_style_t style_setting_screen_data_time_do_arr_day_lb2_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default);
	lv_style_set_radius(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_data_time_do_arr_day_LB2, &style_setting_screen_data_time_do_arr_day_lb2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_data_time_do_arr_day_LB3
	ui->Setting_Screen_data_time_do_arr_day_LB3 = lv_label_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_do_arr_day_LB3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_data_time_do_arr_day_LB3, 126, 18);
	lv_label_set_text(ui->Setting_Screen_data_time_do_arr_day_LB3, "");
	lv_label_set_long_mode(ui->Setting_Screen_data_time_do_arr_day_LB3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_data_time_do_arr_day_LB3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_do_arr_day_lb3_main_main_default
	static lv_style_t style_setting_screen_data_time_do_arr_day_lb3_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default);
	lv_style_set_radius(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_data_time_do_arr_day_LB3, &style_setting_screen_data_time_do_arr_day_lb3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes Setting_Screen_setting_unit_night_container
	ui->Setting_Screen_setting_unit_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_unit_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_unit_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_unit_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_unit_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_unit_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_unit_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_unit_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_unit_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_unit_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_unit_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_unit_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_unit_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_unit_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_unit_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_unit_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_unit_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_unit_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_unit_night_container, &style_setting_screen_setting_unit_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_unit_night_icon_img
	ui->Setting_Screen_unit_night_icon_img = lv_img_create(ui->Setting_Screen_setting_unit_night_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_night_icon_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_unit_night_icon_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_night_icon_img_main_main_default
	static lv_style_t style_setting_screen_unit_night_icon_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_night_icon_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_night_icon_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_night_icon_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_night_icon_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_night_icon_img, &style_setting_screen_unit_night_icon_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_unit_night_sub_btn_img
	ui->Setting_Screen_unit_night_sub_btn_img = lv_img_create(ui->Setting_Screen_setting_unit_night_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_night_sub_btn_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_unit_night_sub_btn_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_night_sub_btn_img_main_main_default
	static lv_style_t style_setting_screen_unit_night_sub_btn_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_night_sub_btn_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_night_sub_btn_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_night_sub_btn_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_night_sub_btn_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_night_sub_btn_img, &style_setting_screen_unit_night_sub_btn_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_unit_night_sub_btn_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_unit_night_sub_btn_img,&subbtn_night_24x24);
	lv_img_set_pivot(ui->Setting_Screen_unit_night_sub_btn_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_unit_night_sub_btn_img, 0);

	//Write codes Setting_Screen_unit_night_up_arr_img
	ui->Setting_Screen_unit_night_up_arr_img = lv_img_create(ui->Setting_Screen_setting_unit_night_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_night_up_arr_img, 110, 105);
	lv_obj_set_size(ui->Setting_Screen_unit_night_up_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_night_up_arr_img_main_main_default
	static lv_style_t style_setting_screen_unit_night_up_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_night_up_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_night_up_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_night_up_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_night_up_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_night_up_arr_img, &style_setting_screen_unit_night_up_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_unit_night_up_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_unit_night_up_arr_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_unit_night_up_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_unit_night_up_arr_img, 0);

	//Write codes Setting_Screen_unit_night_down_arr_img
	ui->Setting_Screen_unit_night_down_arr_img = lv_img_create(ui->Setting_Screen_setting_unit_night_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_night_down_arr_img, 110, 198);
	lv_obj_set_size(ui->Setting_Screen_unit_night_down_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_night_down_arr_img_main_main_default
	static lv_style_t style_setting_screen_unit_night_down_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_night_down_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_night_down_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_night_down_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_night_down_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_night_down_arr_img, &style_setting_screen_unit_night_down_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_unit_night_down_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_unit_night_down_arr_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_unit_night_down_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_unit_night_down_arr_img, 0);

	//Write codes Setting_Screen_unit_night_Lb1
	ui->Setting_Screen_unit_night_Lb1 = lv_label_create(ui->Setting_Screen_setting_unit_night_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_night_Lb1, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_unit_night_Lb1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_unit_night_Lb1, "");
	lv_label_set_long_mode(ui->Setting_Screen_unit_night_Lb1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_unit_night_Lb1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_night_lb1_main_main_default
	static lv_style_t style_setting_screen_unit_night_lb1_main_main_default;
	lv_style_reset(&style_setting_screen_unit_night_lb1_main_main_default);
	lv_style_set_radius(&style_setting_screen_unit_night_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_unit_night_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_unit_night_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_unit_night_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_unit_night_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_unit_night_lb1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_unit_night_lb1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_unit_night_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_unit_night_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_unit_night_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_unit_night_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_unit_night_lb1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_unit_night_Lb1, &style_setting_screen_unit_night_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_unit_day_container
	ui->Setting_Screen_setting_unit_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_unit_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_unit_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_unit_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_unit_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_unit_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_unit_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_unit_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_unit_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_unit_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_unit_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_unit_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_unit_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_unit_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_unit_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_unit_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_unit_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_unit_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_unit_day_container, &style_setting_screen_setting_unit_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_unit_day_circle_img
	ui->Setting_Screen_unit_day_circle_img = lv_img_create(ui->Setting_Screen_setting_unit_day_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_unit_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_unit_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_day_circle_img, &style_setting_screen_unit_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_unit_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_unit_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_unit_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_unit_day_circle_img, 0);

	//Write codes Setting_Screen_unit_day_icon_img
	ui->Setting_Screen_unit_day_icon_img = lv_img_create(ui->Setting_Screen_setting_unit_day_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_day_icon_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_unit_day_icon_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_day_icon_img_main_main_default
	static lv_style_t style_setting_screen_unit_day_icon_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_day_icon_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_day_icon_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_day_icon_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_day_icon_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_day_icon_img, &style_setting_screen_unit_day_icon_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_unit_day_sub_btn_img
	ui->Setting_Screen_unit_day_sub_btn_img = lv_img_create(ui->Setting_Screen_setting_unit_day_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_day_sub_btn_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_unit_day_sub_btn_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_day_sub_btn_img_main_main_default
	static lv_style_t style_setting_screen_unit_day_sub_btn_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_day_sub_btn_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_day_sub_btn_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_day_sub_btn_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_day_sub_btn_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_day_sub_btn_img, &style_setting_screen_unit_day_sub_btn_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_unit_day_sub_btn_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_unit_day_sub_btn_img,&subbtn_day_24x24);
	lv_img_set_pivot(ui->Setting_Screen_unit_day_sub_btn_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_unit_day_sub_btn_img, 0);

	//Write codes Setting_Screen_unit_day_up_arr_img
	ui->Setting_Screen_unit_day_up_arr_img = lv_img_create(ui->Setting_Screen_setting_unit_day_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_day_up_arr_img, 110, 105);
	lv_obj_set_size(ui->Setting_Screen_unit_day_up_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_day_up_arr_img_main_main_default
	static lv_style_t style_setting_screen_unit_day_up_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_day_up_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_day_up_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_day_up_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_day_up_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_day_up_arr_img, &style_setting_screen_unit_day_up_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_unit_day_up_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_unit_day_up_arr_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_unit_day_up_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_unit_day_up_arr_img, 0);

	//Write codes Setting_Screen_unit_day_night_arr_img
	ui->Setting_Screen_unit_day_night_arr_img = lv_img_create(ui->Setting_Screen_setting_unit_day_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_day_night_arr_img, 110, 198);
	lv_obj_set_size(ui->Setting_Screen_unit_day_night_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_day_night_arr_img_main_main_default
	static lv_style_t style_setting_screen_unit_day_night_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_day_night_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_day_night_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_day_night_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_day_night_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_day_night_arr_img, &style_setting_screen_unit_day_night_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_unit_day_night_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_unit_day_night_arr_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_unit_day_night_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_unit_day_night_arr_img, 0);

	//Write codes Setting_Screen_unit_day_lb1
	ui->Setting_Screen_unit_day_lb1 = lv_label_create(ui->Setting_Screen_setting_unit_day_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_day_lb1, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_unit_day_lb1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_unit_day_lb1, "");
	lv_label_set_long_mode(ui->Setting_Screen_unit_day_lb1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_unit_day_lb1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_day_lb1_main_main_default
	static lv_style_t style_setting_screen_unit_day_lb1_main_main_default;
	lv_style_reset(&style_setting_screen_unit_day_lb1_main_main_default);
	lv_style_set_radius(&style_setting_screen_unit_day_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_unit_day_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_unit_day_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_unit_day_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_unit_day_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_unit_day_lb1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_unit_day_lb1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_unit_day_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_unit_day_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_unit_day_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_unit_day_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_unit_day_lb1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_unit_day_lb1, &style_setting_screen_unit_day_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_units_sub_container
	ui->Setting_Screen_setting_units_sub_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_units_sub_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_units_sub_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_units_sub_container_main_main_default
	static lv_style_t style_setting_screen_setting_units_sub_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_units_sub_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_units_sub_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_units_sub_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_units_sub_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_units_sub_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_units_sub_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_units_sub_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_units_sub_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_units_sub_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_units_sub_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_units_sub_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_units_sub_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_units_sub_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_units_sub_container, &style_setting_screen_setting_units_sub_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_units_check_btn_img
	ui->Setting_Screen_units_check_btn_img = lv_img_create(ui->Setting_Screen_setting_units_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_check_btn_img, 168, 117);
	lv_obj_set_size(ui->Setting_Screen_units_check_btn_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_check_btn_img_main_main_default
	static lv_style_t style_setting_screen_units_check_btn_img_main_main_default;
	lv_style_reset(&style_setting_screen_units_check_btn_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_units_check_btn_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_units_check_btn_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_units_check_btn_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_units_check_btn_img, &style_setting_screen_units_check_btn_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_units_check_btn_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_units_check_btn_img,&_radiobtn_night_Checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_units_check_btn_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_units_check_btn_img, 0);

	//Write codes Setting_Screen_units_sub_up_arr_img
	ui->Setting_Screen_units_sub_up_arr_img = lv_img_create(ui->Setting_Screen_setting_units_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_sub_up_arr_img, 110, 115);
	lv_obj_set_size(ui->Setting_Screen_units_sub_up_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_sub_up_arr_img_main_main_default
	static lv_style_t style_setting_screen_units_sub_up_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_units_sub_up_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_units_sub_up_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_units_sub_up_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_units_sub_up_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_units_sub_up_arr_img, &style_setting_screen_units_sub_up_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_units_sub_up_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_units_sub_up_arr_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_units_sub_up_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_units_sub_up_arr_img, 0);

	//Write codes Setting_Screen_units_sub_down_arr_img
	ui->Setting_Screen_units_sub_down_arr_img = lv_img_create(ui->Setting_Screen_setting_units_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_sub_down_arr_img, 110, 198);
	lv_obj_set_size(ui->Setting_Screen_units_sub_down_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_sub_down_arr_img_main_main_default
	static lv_style_t style_setting_screen_units_sub_down_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_units_sub_down_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_units_sub_down_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_units_sub_down_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_units_sub_down_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_units_sub_down_arr_img, &style_setting_screen_units_sub_down_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_units_sub_down_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_units_sub_down_arr_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_units_sub_down_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_units_sub_down_arr_img, 0);

	//Write codes Setting_Screen_units_sub_lbl
	ui->Setting_Screen_units_sub_lbl = lv_label_create(ui->Setting_Screen_setting_units_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_sub_lbl, 51, 148);
	lv_obj_set_size(ui->Setting_Screen_units_sub_lbl, 126, 18);
	lv_label_set_text(ui->Setting_Screen_units_sub_lbl, "L/100 km");
	lv_label_set_long_mode(ui->Setting_Screen_units_sub_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_units_sub_lbl, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_sub_lbl_main_main_default
	static lv_style_t style_setting_screen_units_sub_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_units_sub_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_units_sub_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_units_sub_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_units_sub_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_units_sub_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_units_sub_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_units_sub_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_units_sub_lbl_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_units_sub_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_units_sub_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_units_sub_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_units_sub_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_units_sub_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_units_sub_lbl, &style_setting_screen_units_sub_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_units_day_sub_container
	ui->Setting_Screen_setting_units_day_sub_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_units_day_sub_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_units_day_sub_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_units_day_sub_container_main_main_default
	static lv_style_t style_setting_screen_setting_units_day_sub_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_units_day_sub_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_units_day_sub_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_units_day_sub_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_units_day_sub_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_units_day_sub_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_units_day_sub_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_units_day_sub_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_units_day_sub_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_units_day_sub_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_units_day_sub_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_units_day_sub_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_units_day_sub_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_units_day_sub_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_units_day_sub_container, &style_setting_screen_setting_units_day_sub_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_units_day_circle_img
	ui->Setting_Screen_units_day_circle_img = lv_img_create(ui->Setting_Screen_setting_units_day_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_units_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_units_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_units_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_units_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_units_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_units_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_units_day_circle_img, &style_setting_screen_units_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_units_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_units_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_units_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_units_day_circle_img, 0);

	//Write codes Setting_Screen_units_check_day_btn_img
	ui->Setting_Screen_units_check_day_btn_img = lv_img_create(ui->Setting_Screen_setting_units_day_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_check_day_btn_img, 196, 145);
	lv_obj_set_size(ui->Setting_Screen_units_check_day_btn_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_check_day_btn_img_main_main_default
	static lv_style_t style_setting_screen_units_check_day_btn_img_main_main_default;
	lv_style_reset(&style_setting_screen_units_check_day_btn_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_units_check_day_btn_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_units_check_day_btn_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_units_check_day_btn_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_units_check_day_btn_img, &style_setting_screen_units_check_day_btn_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_units_check_day_btn_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_units_check_day_btn_img,&_radiobtn_day_checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_units_check_day_btn_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_units_check_day_btn_img, 0);

	//Write codes Setting_Screen_units_up_arr_day_img
	ui->Setting_Screen_units_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_units_day_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_up_arr_day_img, 110, 115);
	lv_obj_set_size(ui->Setting_Screen_units_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_units_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_units_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_units_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_units_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_units_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_units_up_arr_day_img, &style_setting_screen_units_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_units_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_units_up_arr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_units_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_units_up_arr_day_img, 0);

	//Write codes Setting_Screen_units_up_arr_night_img
	ui->Setting_Screen_units_up_arr_night_img = lv_img_create(ui->Setting_Screen_setting_units_day_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_up_arr_night_img, 110, 198);
	lv_obj_set_size(ui->Setting_Screen_units_up_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_up_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_units_up_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_units_up_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_units_up_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_units_up_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_units_up_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_units_up_arr_night_img, &style_setting_screen_units_up_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_units_up_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_units_up_arr_night_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_units_up_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_units_up_arr_night_img, 0);

	//Write codes Setting_Screen_units_day_lbl1
	ui->Setting_Screen_units_day_lbl1 = lv_label_create(ui->Setting_Screen_setting_units_day_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_day_lbl1, 51, 148);
	lv_obj_set_size(ui->Setting_Screen_units_day_lbl1, 126, 18);
	lv_label_set_text(ui->Setting_Screen_units_day_lbl1, "L/100 km");
	lv_label_set_long_mode(ui->Setting_Screen_units_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_units_day_lbl1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_day_lbl1_main_main_default
	static lv_style_t style_setting_screen_units_day_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_units_day_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_units_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_units_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_units_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_units_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_units_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_units_day_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_units_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_units_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_units_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_units_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_units_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_units_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_units_day_lbl1, &style_setting_screen_units_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	
	//Write codes Setting_Screen_setting_about_inf_container
	ui->Setting_Screen_setting_about_inf_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_about_inf_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_about_inf_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_about_inf_container_main_main_default
	static lv_style_t style_setting_screen_setting_about_inf_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_about_inf_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_about_inf_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_about_inf_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_about_inf_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_about_inf_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_about_inf_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_about_inf_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_about_inf_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_about_inf_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_about_inf_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_about_inf_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_about_inf_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_about_inf_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_about_inf_container, &style_setting_screen_setting_about_inf_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_aboutinf_lb1
	ui->Setting_Screen_aboutinf_lb1 = lv_label_create(ui->Setting_Screen_setting_about_inf_container);
	lv_obj_set_pos(ui->Setting_Screen_aboutinf_lb1, 61, 148);
	lv_obj_set_size(ui->Setting_Screen_aboutinf_lb1, 126, 18);
	lv_label_set_text(ui->Setting_Screen_aboutinf_lb1, "");
	lv_label_set_long_mode(ui->Setting_Screen_aboutinf_lb1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_aboutinf_lb1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_aboutinf_lb1_main_main_default
	static lv_style_t style_setting_screen_aboutinf_lb1_main_main_default;
	lv_style_reset(&style_setting_screen_aboutinf_lb1_main_main_default);
	lv_style_set_radius(&style_setting_screen_aboutinf_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_aboutinf_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_aboutinf_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_aboutinf_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_aboutinf_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_aboutinf_lb1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_aboutinf_lb1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_aboutinf_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_aboutinf_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_aboutinf_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_aboutinf_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_aboutinf_lb1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_aboutinf_lb1, &style_setting_screen_aboutinf_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_about_inf_nigh_container
	ui->Setting_Screen_setting_about_inf_nigh_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_about_inf_nigh_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_about_inf_nigh_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_about_inf_nigh_container_main_main_default
	static lv_style_t style_setting_screen_setting_about_inf_nigh_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_about_inf_nigh_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_about_inf_nigh_container, &style_setting_screen_setting_about_inf_nigh_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_aboout_day_cir_img
	ui->Setting_Screen_aboout_day_cir_img = lv_img_create(ui->Setting_Screen_setting_about_inf_nigh_container);
	lv_obj_set_pos(ui->Setting_Screen_aboout_day_cir_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_aboout_day_cir_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_aboout_day_cir_img_main_main_default
	static lv_style_t style_setting_screen_aboout_day_cir_img_main_main_default;
	lv_style_reset(&style_setting_screen_aboout_day_cir_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_aboout_day_cir_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_aboout_day_cir_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_aboout_day_cir_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_aboout_day_cir_img, &style_setting_screen_aboout_day_cir_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_aboout_day_cir_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_aboout_day_cir_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_aboout_day_cir_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_aboout_day_cir_img, 0);

	//Write codes Setting_Screen_aboutinf_nnight_lbl1
	ui->Setting_Screen_aboutinf_nnight_lbl1 = lv_label_create(ui->Setting_Screen_setting_about_inf_nigh_container);
	lv_obj_set_pos(ui->Setting_Screen_aboutinf_nnight_lbl1, 61, 148);
	lv_obj_set_size(ui->Setting_Screen_aboutinf_nnight_lbl1, 126, 18);
	lv_label_set_text(ui->Setting_Screen_aboutinf_nnight_lbl1, "");
	lv_label_set_long_mode(ui->Setting_Screen_aboutinf_nnight_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_aboutinf_nnight_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_aboutinf_nnight_lbl1_main_main_default
	static lv_style_t style_setting_screen_aboutinf_nnight_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_aboutinf_nnight_lbl1, &style_setting_screen_aboutinf_nnight_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_date_set_container
	ui->Setting_Screen_setting_date_set_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_date_set_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_date_set_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_date_set_container_main_main_default
	static lv_style_t style_setting_screen_setting_date_set_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_date_set_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_date_set_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_date_set_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_date_set_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_date_set_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_date_set_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_date_set_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_date_set_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_date_set_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_date_set_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_date_set_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_date_set_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_date_set_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_date_set_container, &style_setting_screen_setting_date_set_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_night_up_arr_1
	ui->Setting_Screen_date_night_up_arr_1 = lv_img_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_up_arr_1, 60, 133);
	lv_obj_set_size(ui->Setting_Screen_date_night_up_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_up_arr_1_main_main_default
	static lv_style_t style_setting_screen_date_night_up_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_up_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_night_up_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_night_up_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_night_up_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_night_up_arr_1, &style_setting_screen_date_night_up_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_night_up_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_night_up_arr_1,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_night_up_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_night_up_arr_1, 0);

	//Write codes Setting_Screen_date_night_up_arr_2
	ui->Setting_Screen_date_night_up_arr_2 = lv_img_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_up_arr_2, 109, 133);
	lv_obj_set_size(ui->Setting_Screen_date_night_up_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_up_arr_2_main_main_default
	static lv_style_t style_setting_screen_date_night_up_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_up_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_night_up_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_night_up_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_night_up_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_night_up_arr_2, &style_setting_screen_date_night_up_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_night_up_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_night_up_arr_2,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_night_up_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_night_up_arr_2, 0);

	//Write codes Setting_Screen_date_night_up_arr_3
	ui->Setting_Screen_date_night_up_arr_3 = lv_img_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_up_arr_3, 159, 133);
	lv_obj_set_size(ui->Setting_Screen_date_night_up_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_up_arr_3_main_main_default
	static lv_style_t style_setting_screen_date_night_up_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_up_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_night_up_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_night_up_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_night_up_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_night_up_arr_3, &style_setting_screen_date_night_up_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_night_up_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_night_up_arr_3,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_night_up_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_night_up_arr_3, 0);

	//Write codes Setting_Screen_date_night_down_arr_1
	ui->Setting_Screen_date_night_down_arr_1 = lv_img_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_down_arr_1, 60, 177);
	lv_obj_set_size(ui->Setting_Screen_date_night_down_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_down_arr_1_main_main_default
	static lv_style_t style_setting_screen_date_night_down_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_down_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_night_down_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_night_down_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_night_down_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_night_down_arr_1, &style_setting_screen_date_night_down_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_night_down_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_night_down_arr_1,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_night_down_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_night_down_arr_1, 0);

	//Write codes Setting_Screen_date_night_down_arr_2
	ui->Setting_Screen_date_night_down_arr_2 = lv_img_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_down_arr_2, 109, 177);
	lv_obj_set_size(ui->Setting_Screen_date_night_down_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_down_arr_2_main_main_default
	static lv_style_t style_setting_screen_date_night_down_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_down_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_night_down_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_night_down_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_night_down_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_night_down_arr_2, &style_setting_screen_date_night_down_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_night_down_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_night_down_arr_2,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_night_down_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_night_down_arr_2, 0);

	//Write codes Setting_Screen_date_night_down_arr_3
	ui->Setting_Screen_date_night_down_arr_3 = lv_img_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_down_arr_3, 159, 177);
	lv_obj_set_size(ui->Setting_Screen_date_night_down_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_down_arr_3_main_main_default
	static lv_style_t style_setting_screen_date_night_down_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_down_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_night_down_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_night_down_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_night_down_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_night_down_arr_3, &style_setting_screen_date_night_down_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_night_down_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_night_down_arr_3,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_night_down_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_night_down_arr_3, 0);

	//Write codes Setting_Screen_date_night_lbl1
	ui->Setting_Screen_date_night_lbl1 = lv_label_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_lbl1, 59, 148);
	lv_obj_set_size(ui->Setting_Screen_date_night_lbl1, 21, 18);
	lv_label_set_text(ui->Setting_Screen_date_night_lbl1, "99");
	lv_label_set_long_mode(ui->Setting_Screen_date_night_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_night_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_lbl1_main_main_default
	static lv_style_t style_setting_screen_date_night_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_night_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_night_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_night_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_night_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_night_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_night_lbl1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_date_night_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_date_night_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_night_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_night_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_night_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_night_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_night_lbl1, &style_setting_screen_date_night_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_night_lbl2
	ui->Setting_Screen_date_night_lbl2 = lv_label_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_lbl2, 109, 148);
	lv_obj_set_size(ui->Setting_Screen_date_night_lbl2, 21, 18);
	lv_label_set_text(ui->Setting_Screen_date_night_lbl2, "99");
	lv_label_set_long_mode(ui->Setting_Screen_date_night_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_night_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_lbl2_main_main_default
	static lv_style_t style_setting_screen_date_night_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_night_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_night_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_night_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_night_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_night_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_night_lbl2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_date_night_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_date_night_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_night_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_night_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_night_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_night_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_night_lbl2, &style_setting_screen_date_night_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_night_lbl3
	ui->Setting_Screen_date_night_lbl3 = lv_label_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_lbl3, 148, 148);
	lv_obj_set_size(ui->Setting_Screen_date_night_lbl3, 43, 18);
	lv_label_set_text(ui->Setting_Screen_date_night_lbl3, "9999");
	lv_label_set_long_mode(ui->Setting_Screen_date_night_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_night_lbl3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_lbl3_main_main_default
	static lv_style_t style_setting_screen_date_night_lbl3_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_lbl3_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_night_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_night_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_night_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_night_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_night_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_night_lbl3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_date_night_lbl3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_date_night_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_night_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_night_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_night_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_night_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_night_lbl3, &style_setting_screen_date_night_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_hold_lbl
	ui->Setting_Screen_date_hold_lbl = lv_label_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_hold_lbl, 68, 231);
	lv_obj_set_size(ui->Setting_Screen_date_hold_lbl, 27, 13);
	lv_label_set_text(ui->Setting_Screen_date_hold_lbl, "Hold");
	lv_label_set_long_mode(ui->Setting_Screen_date_hold_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_hold_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_hold_lbl_main_main_default
	static lv_style_t style_setting_screen_date_hold_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_date_hold_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_hold_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_hold_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_hold_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_hold_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_date_hold_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_date_hold_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_hold_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_hold_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_hold_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_hold_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_hold_lbl, &style_setting_screen_date_hold_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_toset_lbl
	ui->Setting_Screen_date_toset_lbl = lv_label_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_toset_lbl, 127, 232);
	lv_obj_set_size(ui->Setting_Screen_date_toset_lbl, 37, 14);
	lv_label_set_text(ui->Setting_Screen_date_toset_lbl, "toSET");
	lv_label_set_long_mode(ui->Setting_Screen_date_toset_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_toset_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write codes Setting_Screen_date_toset_lbl_1
	ui->Setting_Screen_date_toset_lbl_1 = lv_label_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_toset_lbl_1, 127, 232);
	lv_obj_set_size(ui->Setting_Screen_date_toset_lbl_1, 47, 12);
	lv_label_set_text(ui->Setting_Screen_date_toset_lbl_1, "SET");
	lv_label_set_long_mode(ui->Setting_Screen_date_toset_lbl_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_toset_lbl_1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_toset_lbl_main_main_default
	static lv_style_t style_setting_screen_date_toset_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_date_toset_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_toset_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_toset_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_toset_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_toset_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_date_toset_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_date_toset_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_toset_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_toset_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_toset_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_toset_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_toset_lbl, &style_setting_screen_date_toset_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_sub_btn_img
	ui->Setting_Screen_date_sub_btn_img = lv_img_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_sub_btn_img, 73, 228);
	lv_obj_set_size(ui->Setting_Screen_date_sub_btn_img, 95, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_sub_btn_img_main_main_default
	static lv_style_t style_setting_screen_date_sub_btn_img_main_main_default;
	lv_style_reset(&style_setting_screen_date_sub_btn_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_sub_btn_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_sub_btn_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_sub_btn_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_sub_btn_img, &style_setting_screen_date_sub_btn_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_sub_btn_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_sub_btn_img,&hold_set_day);
	lv_img_set_pivot(ui->Setting_Screen_date_sub_btn_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_sub_btn_img, 0);

	//Write codes Setting_Screen_setting_date_set_night_container
	ui->Setting_Screen_setting_date_set_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_date_set_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_date_set_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_date_set_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_date_set_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_date_set_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_date_set_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_date_set_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_date_set_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_date_set_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_date_set_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_date_set_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_date_set_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_date_set_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_date_set_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_date_set_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_date_set_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_date_set_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_date_set_night_container, &style_setting_screen_setting_date_set_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_day_cir_img
	ui->Setting_Screen_date_day_cir_img = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_cir_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_date_day_cir_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_cir_img_main_main_default
	static lv_style_t style_setting_screen_date_day_cir_img_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_cir_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_cir_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_cir_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_cir_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_cir_img, &style_setting_screen_date_day_cir_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_cir_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_cir_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_date_day_cir_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_cir_img, 0);

	//Write codes Setting_Screen_date_day_up_arr_1
	ui->Setting_Screen_date_day_up_arr_1 = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_up_arr_1, 60, 133);
	lv_obj_set_size(ui->Setting_Screen_date_day_up_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_up_arr_1_main_main_default
	static lv_style_t style_setting_screen_date_day_up_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_up_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_up_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_up_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_up_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_up_arr_1, &style_setting_screen_date_day_up_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_up_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_up_arr_1,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_day_up_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_up_arr_1, 0);

	//Write codes Setting_Screen_date_day_up_arr_2
	ui->Setting_Screen_date_day_up_arr_2 = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_up_arr_2, 109, 133);
	lv_obj_set_size(ui->Setting_Screen_date_day_up_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_up_arr_2_main_main_default
	static lv_style_t style_setting_screen_date_day_up_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_up_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_up_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_up_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_up_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_up_arr_2, &style_setting_screen_date_day_up_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_up_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_up_arr_2,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_day_up_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_up_arr_2, 0);

	//Write codes Setting_Screen_date_day_up_arr_3
	ui->Setting_Screen_date_day_up_arr_3 = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_up_arr_3, 159, 133);
	lv_obj_set_size(ui->Setting_Screen_date_day_up_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_up_arr_3_main_main_default
	static lv_style_t style_setting_screen_date_day_up_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_up_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_up_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_up_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_up_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_up_arr_3, &style_setting_screen_date_day_up_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_up_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_up_arr_3,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_day_up_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_up_arr_3, 0);

	//Write codes Setting_Screen_date_day_down_arr_1
	ui->Setting_Screen_date_day_down_arr_1 = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_down_arr_1, 60, 177);
	lv_obj_set_size(ui->Setting_Screen_date_day_down_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_down_arr_1_main_main_default
	static lv_style_t style_setting_screen_date_day_down_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_down_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_down_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_down_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_down_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_down_arr_1, &style_setting_screen_date_day_down_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_down_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_down_arr_1,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_day_down_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_down_arr_1, 0);

	//Write codes Setting_Screen_date_day_down_arr_2
	ui->Setting_Screen_date_day_down_arr_2 = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_down_arr_2, 109, 179);
	lv_obj_set_size(ui->Setting_Screen_date_day_down_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_down_arr_2_main_main_default
	static lv_style_t style_setting_screen_date_day_down_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_down_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_down_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_down_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_down_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_down_arr_2, &style_setting_screen_date_day_down_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_down_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_down_arr_2,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_day_down_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_down_arr_2, 0);

	//Write codes Setting_Screen_date_day_down_arr_3
	ui->Setting_Screen_date_day_down_arr_3 = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_down_arr_3, 159, 177);
	lv_obj_set_size(ui->Setting_Screen_date_day_down_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_down_arr_3_main_main_default
	static lv_style_t style_setting_screen_date_day_down_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_down_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_down_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_down_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_down_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_down_arr_3, &style_setting_screen_date_day_down_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_down_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_down_arr_3,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_day_down_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_down_arr_3, 0);

	//Write codes Setting_Screen_date_day_lbl1
	ui->Setting_Screen_date_day_lbl1 = lv_label_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_lbl1, 59, 148);
	lv_obj_set_size(ui->Setting_Screen_date_day_lbl1, 21, 18);
	lv_label_set_text(ui->Setting_Screen_date_day_lbl1, "99");
	lv_label_set_long_mode(ui->Setting_Screen_date_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_lbl1_main_main_default
	static lv_style_t style_setting_screen_date_day_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_day_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_date_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_date_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_day_lbl1, &style_setting_screen_date_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_day_lbl2
	ui->Setting_Screen_date_day_lbl2 = lv_label_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_lbl2, 109, 148);
	lv_obj_set_size(ui->Setting_Screen_date_day_lbl2, 21, 18);
	lv_label_set_text(ui->Setting_Screen_date_day_lbl2, "99");
	lv_label_set_long_mode(ui->Setting_Screen_date_day_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_day_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_lbl2_main_main_default
	static lv_style_t style_setting_screen_date_day_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_day_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_day_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_day_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_day_lbl2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_date_day_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_date_day_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_day_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_day_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_day_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_day_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_day_lbl2, &style_setting_screen_date_day_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_day_lbl3
	ui->Setting_Screen_date_day_lbl3 = lv_label_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_lbl3, 148, 148);
	lv_obj_set_size(ui->Setting_Screen_date_day_lbl3, 43, 18);
	lv_label_set_text(ui->Setting_Screen_date_day_lbl3, "9999");
	lv_label_set_long_mode(ui->Setting_Screen_date_day_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_day_lbl3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_lbl3_main_main_default
	static lv_style_t style_setting_screen_date_day_lbl3_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_lbl3_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_day_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_day_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_day_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_day_lbl3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_date_day_lbl3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_date_day_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_day_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_day_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_day_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_day_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_day_lbl3, &style_setting_screen_date_day_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_day_hold_lbl
	ui->Setting_Screen_date_day_hold_lbl = lv_label_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_hold_lbl, 68, 230);
	lv_obj_set_size(ui->Setting_Screen_date_day_hold_lbl, 27, 13);
	lv_label_set_text(ui->Setting_Screen_date_day_hold_lbl, "");
	lv_label_set_long_mode(ui->Setting_Screen_date_day_hold_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_day_hold_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_hold_lbl_main_main_default
	static lv_style_t style_setting_screen_date_day_hold_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_hold_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_day_hold_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_day_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_day_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_day_hold_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_day_hold_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_day_hold_lbl_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_date_day_hold_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_date_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_day_hold_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_day_hold_lbl, &style_setting_screen_date_day_hold_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_day_toset_lbl
	ui->Setting_Screen_date_day_toset_lbl = lv_label_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_toset_lbl, 127, 230);
	lv_obj_set_size(ui->Setting_Screen_date_day_toset_lbl, 37, 14);
	lv_label_set_text(ui->Setting_Screen_date_day_toset_lbl, "");
	lv_label_set_long_mode(ui->Setting_Screen_date_day_toset_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_day_toset_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_toset_lbl_main_main_default
	static lv_style_t style_setting_screen_date_day_toset_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_toset_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_day_toset_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_day_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_day_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_day_toset_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_day_toset_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_day_toset_lbl_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_date_day_toset_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_date_day_toset_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_day_toset_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_day_toset_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_day_toset_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_day_toset_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_day_toset_lbl, &style_setting_screen_date_day_toset_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_day_subbutn_img
	ui->Setting_Screen_date_day_subbutn_img = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_subbutn_img, 72, 228);
	lv_obj_set_size(ui->Setting_Screen_date_day_subbutn_img, 96, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_subbutn_img_main_main_default
	static lv_style_t style_setting_screen_date_day_subbutn_img_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_subbutn_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_subbutn_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_subbutn_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_subbutn_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_subbutn_img, &style_setting_screen_date_day_subbutn_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_subbutn_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_subbutn_img,&hold_set_day);
	lv_img_set_pivot(ui->Setting_Screen_date_day_subbutn_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_subbutn_img, 0);

	//Write codes Setting_Screen_setting_time_set_container
	ui->Setting_Screen_setting_time_set_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_time_set_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_time_set_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_time_set_container_main_main_default
	static lv_style_t style_setting_screen_setting_time_set_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_time_set_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_time_set_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_time_set_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_time_set_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_time_set_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_time_set_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_time_set_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_time_set_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_time_set_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_time_set_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_time_set_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_time_set_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_time_set_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_time_set_container, &style_setting_screen_setting_time_set_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_night_up_arr_1
	ui->Setting_Screen_time_night_up_arr_1 = lv_img_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_up_arr_1, 60, 133);
	lv_obj_set_size(ui->Setting_Screen_time_night_up_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_up_arr_1_main_main_default
	static lv_style_t style_setting_screen_time_night_up_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_up_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_night_up_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_night_up_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_night_up_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_night_up_arr_1, &style_setting_screen_time_night_up_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_night_up_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_night_up_arr_1,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_night_up_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_night_up_arr_1, 0);

	//Write codes Setting_Screen_time_night_up_arr_2
	ui->Setting_Screen_time_night_up_arr_2 = lv_img_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_up_arr_2, 109, 133);
	lv_obj_set_size(ui->Setting_Screen_time_night_up_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_up_arr_2_main_main_default
	static lv_style_t style_setting_screen_time_night_up_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_up_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_night_up_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_night_up_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_night_up_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_night_up_arr_2, &style_setting_screen_time_night_up_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_night_up_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_night_up_arr_2,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_night_up_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_night_up_arr_2, 0);

	//Write codes Setting_Screen_time_night_up_arr_3
	ui->Setting_Screen_time_night_up_arr_3 = lv_img_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_up_arr_3, 159, 133);
	lv_obj_set_size(ui->Setting_Screen_time_night_up_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_up_arr_3_main_main_default
	static lv_style_t style_setting_screen_time_night_up_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_up_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_night_up_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_night_up_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_night_up_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_night_up_arr_3, &style_setting_screen_time_night_up_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_night_up_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_night_up_arr_3,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_night_up_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_night_up_arr_3, 0);

	//Write codes Setting_Screen_time_night_down_arr_1
	ui->Setting_Screen_time_night_down_arr_1 = lv_img_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_down_arr_1, 60, 177);
	lv_obj_set_size(ui->Setting_Screen_time_night_down_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_down_arr_1_main_main_default
	static lv_style_t style_setting_screen_time_night_down_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_down_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_night_down_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_night_down_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_night_down_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_night_down_arr_1, &style_setting_screen_time_night_down_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_night_down_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_night_down_arr_1,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_night_down_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_night_down_arr_1, 0);

	//Write codes Setting_Screen_time_night_down_arr_2
	ui->Setting_Screen_time_night_down_arr_2 = lv_img_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_down_arr_2, 109, 177);
	lv_obj_set_size(ui->Setting_Screen_time_night_down_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_down_arr_2_main_main_default
	static lv_style_t style_setting_screen_time_night_down_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_down_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_night_down_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_night_down_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_night_down_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_night_down_arr_2, &style_setting_screen_time_night_down_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_night_down_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_night_down_arr_2,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_night_down_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_night_down_arr_2, 0);

	//Write codes Setting_Screen_time_night_down_arr_3
	ui->Setting_Screen_time_night_down_arr_3 = lv_img_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_down_arr_3, 159, 177);
	lv_obj_set_size(ui->Setting_Screen_time_night_down_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_down_arr_3_main_main_default
	static lv_style_t style_setting_screen_time_night_down_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_down_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_night_down_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_night_down_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_night_down_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_night_down_arr_3, &style_setting_screen_time_night_down_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_night_down_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_night_down_arr_3,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_night_down_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_night_down_arr_3, 0);

	//Write codes Setting_Screen_time_night_lbl1
	ui->Setting_Screen_time_night_lbl1 = lv_label_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_lbl1, 59, 148);
	lv_obj_set_size(ui->Setting_Screen_time_night_lbl1, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_night_lbl1, "00");
	lv_label_set_long_mode(ui->Setting_Screen_time_night_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_night_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_lbl1_main_main_default
	static lv_style_t style_setting_screen_time_night_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_night_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_night_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_night_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_night_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_night_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_night_lbl1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_night_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_night_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_night_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_night_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_night_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_night_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_night_lbl1, &style_setting_screen_time_night_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_night_lbl2
	ui->Setting_Screen_time_night_lbl2 = lv_label_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_lbl2, 109, 148);
	lv_obj_set_size(ui->Setting_Screen_time_night_lbl2, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_night_lbl2, "12");
	lv_label_set_long_mode(ui->Setting_Screen_time_night_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_night_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_lbl2_main_main_default
	static lv_style_t style_setting_screen_time_night_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_night_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_night_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_night_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_night_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_night_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_night_lbl2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_night_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_night_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_night_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_night_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_night_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_night_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_night_lbl2, &style_setting_screen_time_night_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_night_lbl3
	ui->Setting_Screen_time_night_lbl3 = lv_label_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_lbl3, 148, 148);
	lv_obj_set_size(ui->Setting_Screen_time_night_lbl3, 43, 18);
	lv_label_set_text(ui->Setting_Screen_time_night_lbl3, "AM");
	lv_label_set_long_mode(ui->Setting_Screen_time_night_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_night_lbl3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_lbl3_main_main_default
	static lv_style_t style_setting_screen_time_night_lbl3_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_lbl3_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_night_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_night_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_night_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_night_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_night_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_night_lbl3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_night_lbl3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_night_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_night_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_night_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_night_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_night_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_night_lbl3, &style_setting_screen_time_night_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_night_hold_lbl
	ui->Setting_Screen_time_night_hold_lbl = lv_label_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_hold_lbl, 68, 231);
	lv_obj_set_size(ui->Setting_Screen_time_night_hold_lbl, 27, 13);
	lv_label_set_text(ui->Setting_Screen_time_night_hold_lbl, "");
	lv_label_set_long_mode(ui->Setting_Screen_time_night_hold_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_night_hold_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_hold_lbl_main_main_default
	static lv_style_t style_setting_screen_time_night_hold_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_hold_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_night_hold_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_night_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_night_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_night_hold_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_night_hold_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_night_hold_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_night_hold_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_night_hold_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_night_hold_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_night_hold_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_night_hold_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_night_hold_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_night_hold_lbl, &style_setting_screen_time_night_hold_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_night_toset_lbl
	ui->Setting_Screen_time_night_toset_lbl = lv_label_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_toset_lbl, 127, 230);
	lv_obj_set_size(ui->Setting_Screen_time_night_toset_lbl, 37, 14);
	lv_label_set_text(ui->Setting_Screen_time_night_toset_lbl, "");
	lv_label_set_long_mode(ui->Setting_Screen_time_night_toset_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_night_toset_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_toset_lbl_main_main_default
	static lv_style_t style_setting_screen_time_night_toset_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_toset_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_night_toset_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_night_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_night_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_night_toset_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_night_toset_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_night_toset_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_night_toset_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_night_toset_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_night_toset_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_night_toset_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_night_toset_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_night_toset_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_night_toset_lbl, &style_setting_screen_time_night_toset_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_night_sub_btn
	ui->Setting_Screen_time_night_sub_btn = lv_img_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_sub_btn, 73, 228);
	lv_obj_set_size(ui->Setting_Screen_time_night_sub_btn, 95, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_sub_btn_main_main_default
	static lv_style_t style_setting_screen_time_night_sub_btn_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_sub_btn_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_night_sub_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_night_sub_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_night_sub_btn_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_night_sub_btn, &style_setting_screen_time_night_sub_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_night_sub_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_night_sub_btn,&hold_to_set_night);
	lv_img_set_pivot(ui->Setting_Screen_time_night_sub_btn, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_night_sub_btn, 0);

	//Write codes Setting_Screen_setting_time_set_night_container
	ui->Setting_Screen_setting_time_set_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_time_set_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_time_set_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_time_set_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_time_set_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_time_set_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_time_set_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_time_set_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_time_set_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_time_set_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_time_set_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_time_set_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_time_set_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_time_set_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_time_set_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_time_set_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_time_set_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_time_set_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_time_set_night_container, &style_setting_screen_setting_time_set_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_day_cir_img
	ui->Setting_Screen_time_day_cir_img = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_cir_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_time_day_cir_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_cir_img_main_main_default
	static lv_style_t style_setting_screen_time_day_cir_img_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_cir_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_cir_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_cir_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_cir_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_cir_img, &style_setting_screen_time_day_cir_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_cir_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_cir_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_time_day_cir_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_cir_img, 0);

	//Write codes Setting_Screen_time_day_up_arr_1
	ui->Setting_Screen_time_day_up_arr_1 = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_up_arr_1, 60, 133);
	lv_obj_set_size(ui->Setting_Screen_time_day_up_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_up_arr_1_main_main_default
	static lv_style_t style_setting_screen_time_day_up_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_up_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_up_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_up_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_up_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_up_arr_1, &style_setting_screen_time_day_up_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_up_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_up_arr_1,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_day_up_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_up_arr_1, 0);

	//Write codes Setting_Screen_time_day_up_arr_2
	ui->Setting_Screen_time_day_up_arr_2 = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_up_arr_2, 109, 133);
	lv_obj_set_size(ui->Setting_Screen_time_day_up_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_up_arr_2_main_main_default
	static lv_style_t style_setting_screen_time_day_up_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_up_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_up_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_up_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_up_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_up_arr_2, &style_setting_screen_time_day_up_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_up_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_up_arr_2,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_day_up_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_up_arr_2, 0);

	//Write codes Setting_Screen_time_day_up_arr_3
	ui->Setting_Screen_time_day_up_arr_3 = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_up_arr_3, 159, 133);
	lv_obj_set_size(ui->Setting_Screen_time_day_up_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_up_arr_3_main_main_default
	static lv_style_t style_setting_screen_time_day_up_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_up_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_up_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_up_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_up_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_up_arr_3, &style_setting_screen_time_day_up_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_up_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_up_arr_3,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_day_up_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_up_arr_3, 0);

	//Write codes Setting_Screen_time_day_down_arr_1
	ui->Setting_Screen_time_day_down_arr_1 = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_down_arr_1, 60, 177);
	lv_obj_set_size(ui->Setting_Screen_time_day_down_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_down_arr_1_main_main_default
	static lv_style_t style_setting_screen_time_day_down_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_down_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_down_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_down_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_down_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_down_arr_1, &style_setting_screen_time_day_down_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_down_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_down_arr_1,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_day_down_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_down_arr_1, 0);

	//Write codes Setting_Screen_time_day_down_arr_2
	ui->Setting_Screen_time_day_down_arr_2 = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_down_arr_2, 109, 177);
	lv_obj_set_size(ui->Setting_Screen_time_day_down_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_down_arr_2_main_main_default
	static lv_style_t style_setting_screen_time_day_down_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_down_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_down_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_down_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_down_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_down_arr_2, &style_setting_screen_time_day_down_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_down_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_down_arr_2,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_day_down_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_down_arr_2, 0);

	//Write codes Setting_Screen_time_day_down_arr_3
	ui->Setting_Screen_time_day_down_arr_3 = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_down_arr_3, 159, 177);
	lv_obj_set_size(ui->Setting_Screen_time_day_down_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_down_arr_3_main_main_default
	static lv_style_t style_setting_screen_time_day_down_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_down_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_down_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_down_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_down_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_down_arr_3, &style_setting_screen_time_day_down_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_down_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_down_arr_3,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_day_down_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_down_arr_3, 0);

	//Write codes Setting_Screen_time_day_lbl1
	ui->Setting_Screen_time_day_lbl1 = lv_label_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_lbl1, 59, 148);
	lv_obj_set_size(ui->Setting_Screen_time_day_lbl1, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_day_lbl1, "99");
	lv_label_set_long_mode(ui->Setting_Screen_time_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_lbl1_main_main_default
	static lv_style_t style_setting_screen_time_day_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_day_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_day_lbl1, &style_setting_screen_time_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_day_lbl2
	ui->Setting_Screen_time_day_lbl2 = lv_label_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_lbl2, 109, 148);
	lv_obj_set_size(ui->Setting_Screen_time_day_lbl2, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_day_lbl2, "99");
	lv_label_set_long_mode(ui->Setting_Screen_time_day_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_day_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_lbl2_main_main_default
	static lv_style_t style_setting_screen_time_day_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_day_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_day_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_day_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_day_lbl2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_day_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_day_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_day_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_day_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_day_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_day_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_day_lbl2, &style_setting_screen_time_day_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_day_lbl3
	ui->Setting_Screen_time_day_lbl3 = lv_label_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_lbl3, 148, 148);
	lv_obj_set_size(ui->Setting_Screen_time_day_lbl3, 43, 18);
	lv_label_set_text(ui->Setting_Screen_time_day_lbl3, "AM");
	lv_label_set_long_mode(ui->Setting_Screen_time_day_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_day_lbl3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_lbl3_main_main_default
	static lv_style_t style_setting_screen_time_day_lbl3_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_lbl3_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_day_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_day_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_day_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_day_lbl3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_day_lbl3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_day_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_day_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_day_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_day_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_day_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_day_lbl3, &style_setting_screen_time_day_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_day_Hold_lbl1
	ui->Setting_Screen_time_day_Hold_lbl1 = lv_label_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_Hold_lbl1, 68, 231);
	lv_obj_set_size(ui->Setting_Screen_time_day_Hold_lbl1, 27, 13);
	lv_label_set_text(ui->Setting_Screen_time_day_Hold_lbl1, "");
	lv_label_set_long_mode(ui->Setting_Screen_time_day_Hold_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_day_Hold_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_hold_lbl1_main_main_default
	static lv_style_t style_setting_screen_time_day_hold_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_hold_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_day_hold_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_day_hold_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_day_hold_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_day_hold_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_day_hold_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_day_hold_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_day_hold_lbl1_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_day_hold_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_day_hold_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_day_hold_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_day_hold_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_day_hold_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_day_Hold_lbl1, &style_setting_screen_time_day_hold_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_day_Hold_lbl2
	ui->Setting_Screen_time_day_Hold_lbl2 = lv_label_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_Hold_lbl2, 127, 231);
	lv_obj_set_size(ui->Setting_Screen_time_day_Hold_lbl2, 37, 14);
	lv_label_set_text(ui->Setting_Screen_time_day_Hold_lbl2, "");
	lv_label_set_long_mode(ui->Setting_Screen_time_day_Hold_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_day_Hold_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_hold_lbl2_main_main_default
	static lv_style_t style_setting_screen_time_day_hold_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_hold_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_day_hold_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_day_hold_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_day_hold_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_day_hold_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_day_hold_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_day_hold_lbl2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_day_hold_lbl2_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_day_hold_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_day_hold_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_day_hold_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_day_hold_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_day_hold_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_day_Hold_lbl2, &style_setting_screen_time_day_hold_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_day_sub_btn
	ui->Setting_Screen_time_day_sub_btn = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_sub_btn, 72, 228);
	lv_obj_set_size(ui->Setting_Screen_time_day_sub_btn, 96, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_sub_btn_main_main_default
	static lv_style_t style_setting_screen_time_day_sub_btn_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_sub_btn_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_sub_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_sub_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_sub_btn_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_sub_btn, &style_setting_screen_time_day_sub_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_sub_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_sub_btn,&hold_set_day);
	lv_img_set_pivot(ui->Setting_Screen_time_day_sub_btn, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_sub_btn, 0);

	//Write codes Setting_Screen_setting_time_12_container
	ui->Setting_Screen_setting_time_12_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_time_12_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_time_12_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_time_12_container_main_main_default
	static lv_style_t style_setting_screen_setting_time_12_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_time_12_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_time_12_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_time_12_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_time_12_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_time_12_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_time_12_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_time_12_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_time_12_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_time_12_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_time_12_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_time_12_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_time_12_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_time_12_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_time_12_container, &style_setting_screen_setting_time_12_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_up_arr_1
	ui->Setting_Screen_time_12_up_arr_1 = lv_img_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_up_arr_1, 86, 120);
	lv_obj_set_size(ui->Setting_Screen_time_12_up_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_up_arr_1_main_main_default
	static lv_style_t style_setting_screen_time_12_up_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_up_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_up_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_up_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_up_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_up_arr_1, &style_setting_screen_time_12_up_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_up_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_up_arr_1,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_up_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_up_arr_1, 0);

	//Write codes Setting_Screen_time_12_up_arr_2
	ui->Setting_Screen_time_12_up_arr_2 = lv_img_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_up_arr_2, 134, 120);
	lv_obj_set_size(ui->Setting_Screen_time_12_up_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_up_arr_2_main_main_default
	static lv_style_t style_setting_screen_time_12_up_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_up_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_up_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_up_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_up_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_up_arr_2, &style_setting_screen_time_12_up_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_up_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_up_arr_2,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_up_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_up_arr_2, 0);

	//Write codes Setting_Screen_time_12_down_arr_1
	ui->Setting_Screen_time_12_down_arr_1 = lv_img_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_down_arr_1, 86, 190);
	lv_obj_set_size(ui->Setting_Screen_time_12_down_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_down_arr_1_main_main_default
	static lv_style_t style_setting_screen_time_12_down_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_down_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_down_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_down_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_down_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_down_arr_1, &style_setting_screen_time_12_down_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_down_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_down_arr_1,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_down_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_down_arr_1, 0);

	//Write codes Setting_Screen_time_12_down_arr_2
	ui->Setting_Screen_time_12_down_arr_2 = lv_img_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_down_arr_2, 134, 190);
	lv_obj_set_size(ui->Setting_Screen_time_12_down_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_down_arr_2_main_main_default
	static lv_style_t style_setting_screen_time_12_down_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_down_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_down_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_down_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_down_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_down_arr_2, &style_setting_screen_time_12_down_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_down_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_down_arr_2,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_down_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_down_arr_2, 0);

	//Write codes Setting_Screen_time_12_lbl_1
	ui->Setting_Screen_time_12_lbl_1 = lv_label_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_lbl_1, 85, 148);
	lv_obj_set_size(ui->Setting_Screen_time_12_lbl_1, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_12_lbl_1, "99");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_lbl_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_lbl_1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_lbl_1_main_main_default
	static lv_style_t style_setting_screen_time_12_lbl_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_lbl_1_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_lbl_1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_lbl_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_lbl_1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_lbl_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_12_lbl_1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_lbl_1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_lbl_1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_lbl_1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_lbl_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_lbl_1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_lbl_1, &style_setting_screen_time_12_lbl_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_lbl_2
	ui->Setting_Screen_time_12_lbl_2 = lv_label_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_lbl_2, 134, 148);
	lv_obj_set_size(ui->Setting_Screen_time_12_lbl_2, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_12_lbl_2, "99");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_lbl_2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_lbl_2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_lbl_2_main_main_default
	static lv_style_t style_setting_screen_time_12_lbl_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_lbl_2_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_lbl_2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_lbl_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_lbl_2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_lbl_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_12_lbl_2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_lbl_2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_lbl_2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_lbl_2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_lbl_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_lbl_2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_lbl_2, &style_setting_screen_time_12_lbl_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_hold_lbl
	ui->Setting_Screen_time_12_hold_lbl = lv_label_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_hold_lbl, 68, 231);
	lv_obj_set_size(ui->Setting_Screen_time_12_hold_lbl, 27, 13);
	lv_label_set_text(ui->Setting_Screen_time_12_hold_lbl, "Hold");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_hold_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_hold_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_hold_lbl_main_main_default
	static lv_style_t style_setting_screen_time_12_hold_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_hold_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_hold_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_hold_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_hold_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_hold_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_12_hold_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_hold_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_hold_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_hold_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_hold_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_hold_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_hold_lbl, &style_setting_screen_time_12_hold_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_toset_lbl
	ui->Setting_Screen_time_12_toset_lbl = lv_label_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_toset_lbl, 127, 232);
	lv_obj_set_size(ui->Setting_Screen_time_12_toset_lbl, 37, 14);
	lv_label_set_text(ui->Setting_Screen_time_12_toset_lbl, "toSET");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_toset_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_toset_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_toset_lbl_main_main_default
	static lv_style_t style_setting_screen_time_12_toset_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_toset_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_toset_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_toset_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_toset_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_toset_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_12_toset_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_toset_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_toset_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_toset_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_toset_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_toset_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_toset_lbl, &style_setting_screen_time_12_toset_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_sub_btn_lbl
	ui->Setting_Screen_time_12_sub_btn_lbl = lv_img_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_sub_btn_lbl, 101, 225);
	lv_obj_set_size(ui->Setting_Screen_time_12_sub_btn_lbl, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_sub_btn_lbl_main_main_default
	static lv_style_t style_setting_screen_time_12_sub_btn_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_sub_btn_lbl_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_sub_btn_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_sub_btn_lbl_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_sub_btn_lbl_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_sub_btn_lbl, &style_setting_screen_time_12_sub_btn_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_sub_btn_lbl, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_sub_btn_lbl,&_img_night_menu_btn_20x20);
	lv_img_set_pivot(ui->Setting_Screen_time_12_sub_btn_lbl, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_sub_btn_lbl, 0);

	//Write codes Setting_Screen_setting_time_12_day_container
	ui->Setting_Screen_setting_time_12_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_time_12_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_time_12_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_time_12_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_time_12_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_time_12_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_time_12_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_time_12_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_time_12_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_time_12_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_time_12_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_time_12_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_time_12_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_time_12_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_time_12_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_time_12_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_time_12_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_time_12_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_time_12_day_container, &style_setting_screen_setting_time_12_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_day_circle
	ui->Setting_Screen_time_12_day_circle = lv_img_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_day_circle, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_time_12_day_circle, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_day_circle_main_main_default
	static lv_style_t style_setting_screen_time_12_day_circle_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_day_circle_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_day_circle_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_day_circle_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_day_circle_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_day_circle, &style_setting_screen_time_12_day_circle_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_day_circle, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_day_circle,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_time_12_day_circle, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_day_circle, 0);

	//Write codes Setting_Screen_time_12_up_arr_day_1
	ui->Setting_Screen_time_12_up_arr_day_1 = lv_img_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_up_arr_day_1, 86, 120);
	lv_obj_set_size(ui->Setting_Screen_time_12_up_arr_day_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_up_arr_day_1_main_main_default
	static lv_style_t style_setting_screen_time_12_up_arr_day_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_up_arr_day_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_up_arr_day_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_up_arr_day_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_up_arr_day_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_up_arr_day_1, &style_setting_screen_time_12_up_arr_day_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_up_arr_day_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_up_arr_day_1,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_up_arr_day_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_up_arr_day_1, 0);

	//Write codes Setting_Screen_time_12_up_arr_day_2
	ui->Setting_Screen_time_12_up_arr_day_2 = lv_img_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_up_arr_day_2, 134, 120);
	lv_obj_set_size(ui->Setting_Screen_time_12_up_arr_day_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_up_arr_day_2_main_main_default
	static lv_style_t style_setting_screen_time_12_up_arr_day_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_up_arr_day_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_up_arr_day_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_up_arr_day_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_up_arr_day_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_up_arr_day_2, &style_setting_screen_time_12_up_arr_day_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_up_arr_day_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_up_arr_day_2,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_up_arr_day_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_up_arr_day_2, 0);

	//Write codes Setting_Screen_time_12_down_arr_day_1
	ui->Setting_Screen_time_12_down_arr_day_1 = lv_img_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_down_arr_day_1, 86, 190);
	lv_obj_set_size(ui->Setting_Screen_time_12_down_arr_day_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_down_arr_day_1_main_main_default
	static lv_style_t style_setting_screen_time_12_down_arr_day_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_down_arr_day_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_down_arr_day_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_down_arr_day_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_down_arr_day_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_down_arr_day_1, &style_setting_screen_time_12_down_arr_day_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_down_arr_day_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_down_arr_day_1,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_down_arr_day_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_down_arr_day_1, 0);

	//Write codes Setting_Screen_time_12_down_arr_day_2
	ui->Setting_Screen_time_12_down_arr_day_2 = lv_img_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_down_arr_day_2, 134, 190);
	lv_obj_set_size(ui->Setting_Screen_time_12_down_arr_day_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_down_arr_day_2_main_main_default
	static lv_style_t style_setting_screen_time_12_down_arr_day_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_down_arr_day_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_down_arr_day_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_down_arr_day_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_down_arr_day_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_down_arr_day_2, &style_setting_screen_time_12_down_arr_day_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_down_arr_day_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_down_arr_day_2,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_down_arr_day_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_down_arr_day_2, 0);

	//Write codes Setting_Screen_time_12_day_lbl1
	ui->Setting_Screen_time_12_day_lbl1 = lv_label_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_day_lbl1, 85, 148);
	lv_obj_set_size(ui->Setting_Screen_time_12_day_lbl1, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_12_day_lbl1, "99");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_day_lbl1_main_main_default
	static lv_style_t style_setting_screen_time_12_day_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_day_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_day_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_12_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_day_lbl1, &style_setting_screen_time_12_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_day_lbl2
	ui->Setting_Screen_time_12_day_lbl2 = lv_label_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_day_lbl2, 139, 148);
	lv_obj_set_size(ui->Setting_Screen_time_12_day_lbl2, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_12_day_lbl2, "99");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_day_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_day_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_day_lbl2_main_main_default
	static lv_style_t style_setting_screen_time_12_day_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_day_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_day_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_day_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_day_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_day_lbl2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_12_day_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_day_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_day_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_day_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_day_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_day_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_day_lbl2, &style_setting_screen_time_12_day_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_day_hold_lbl
	ui->Setting_Screen_time_12_day_hold_lbl = lv_label_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_day_hold_lbl, 62, 231);
	lv_obj_set_size(ui->Setting_Screen_time_12_day_hold_lbl, 27, 13);
	lv_label_set_text(ui->Setting_Screen_time_12_day_hold_lbl, "Hold");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_day_hold_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_day_hold_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_day_hold_lbl_main_main_default
	static lv_style_t style_setting_screen_time_12_day_hold_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_day_hold_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_day_hold_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_day_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_day_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_day_hold_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_day_hold_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_day_hold_lbl_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_12_day_hold_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_day_hold_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_day_hold_lbl, &style_setting_screen_time_12_day_hold_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_day_sub_btn
	ui->Setting_Screen_time_12_day_sub_btn = lv_label_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_day_sub_btn, 127, 232);
	lv_obj_set_size(ui->Setting_Screen_time_12_day_sub_btn, 37, 14);
	lv_label_set_text(ui->Setting_Screen_time_12_day_sub_btn, "toSET");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_day_sub_btn, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_day_sub_btn, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_day_sub_btn_main_main_default
	static lv_style_t style_setting_screen_time_12_day_sub_btn_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_day_sub_btn_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_day_sub_btn_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_day_sub_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_day_sub_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_day_sub_btn_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_day_sub_btn_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_day_sub_btn_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_12_day_sub_btn_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_day_sub_btn_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_day_sub_btn_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_day_sub_btn_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_day_sub_btn_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_day_sub_btn_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_day_sub_btn, &style_setting_screen_time_12_day_sub_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_day_toset_lbl
	ui->Setting_Screen_time_12_day_toset_lbl = lv_img_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_day_toset_lbl, 101, 225);
	lv_obj_set_size(ui->Setting_Screen_time_12_day_toset_lbl, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_day_toset_lbl_main_main_default
	static lv_style_t style_setting_screen_time_12_day_toset_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_day_toset_lbl_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_day_toset_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_day_toset_lbl_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_day_toset_lbl_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_day_toset_lbl, &style_setting_screen_time_12_day_toset_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_day_toset_lbl, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_day_toset_lbl,&_day_sub_btn_20x20);
	lv_img_set_pivot(ui->Setting_Screen_time_12_day_toset_lbl, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_day_toset_lbl, 0);

	//Write codes Setting_Screen_setting_battery_container
	ui->Setting_Screen_setting_battery_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_battery_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_battery_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_battery_container_main_main_default
	static lv_style_t style_setting_screen_setting_battery_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_battery_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_battery_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_battery_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_battery_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_battery_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_battery_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_battery_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_battery_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_battery_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_battery_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_battery_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_battery_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_battery_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_battery_container, &style_setting_screen_setting_battery_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_battery_img
	ui->Setting_Screen_battery_img = lv_img_create(ui->Setting_Screen_setting_battery_container);
	lv_obj_set_pos(ui->Setting_Screen_battery_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_battery_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_battery_img_main_main_default
	static lv_style_t style_setting_screen_battery_img_main_main_default;
	lv_style_reset(&style_setting_screen_battery_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_battery_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_battery_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_battery_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_battery_img, &style_setting_screen_battery_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_battery_lbl1
	ui->Setting_Screen_battery_lbl1 = lv_label_create(ui->Setting_Screen_setting_battery_container);
	lv_obj_set_pos(ui->Setting_Screen_battery_lbl1, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_battery_lbl1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_battery_lbl1, "");
	lv_label_set_long_mode(ui->Setting_Screen_battery_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_battery_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_battery_lbl1_main_main_default
	static lv_style_t style_setting_screen_battery_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_battery_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_battery_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_battery_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_battery_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_battery_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_battery_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_battery_lbl1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_battery_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_battery_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_battery_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_battery_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_battery_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_battery_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_battery_lbl1, &style_setting_screen_battery_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_battery_day_container
	ui->Setting_Screen_setting_battery_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_battery_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_battery_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_battery_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_battery_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_battery_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_battery_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_battery_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_battery_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_battery_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_battery_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_battery_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_battery_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_battery_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_battery_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_battery_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_battery_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_battery_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_battery_day_container, &style_setting_screen_setting_battery_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_battery_day_im
	ui->Setting_Screen_battery_day_im = lv_img_create(ui->Setting_Screen_setting_battery_day_container);
	lv_obj_set_pos(ui->Setting_Screen_battery_day_im, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_battery_day_im, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_battery_day_im_main_main_default
	static lv_style_t style_setting_screen_battery_day_im_main_main_default;
	lv_style_reset(&style_setting_screen_battery_day_im_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_battery_day_im_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_battery_day_im_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_battery_day_im_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_battery_day_im, &style_setting_screen_battery_day_im_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_battery_day_im, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_battery_day_im,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_battery_day_im, 0,0);
	lv_img_set_angle(ui->Setting_Screen_battery_day_im, 0);

	//Write codes Setting_Screen_battery_day_img
	ui->Setting_Screen_battery_day_img = lv_img_create(ui->Setting_Screen_setting_battery_day_container);
	lv_obj_set_pos(ui->Setting_Screen_battery_day_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_battery_day_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_battery_day_img_main_main_default
	static lv_style_t style_setting_screen_battery_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_battery_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_battery_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_battery_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_battery_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_battery_day_img, &style_setting_screen_battery_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_battery_day_lbl1
	ui->Setting_Screen_battery_day_lbl1 = lv_label_create(ui->Setting_Screen_setting_battery_day_container);
	lv_obj_set_pos(ui->Setting_Screen_battery_day_lbl1, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_battery_day_lbl1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_battery_day_lbl1, "");
	lv_label_set_long_mode(ui->Setting_Screen_battery_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_battery_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_battery_day_lbl1_main_main_default
	static lv_style_t style_setting_screen_battery_day_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_battery_day_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_battery_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_battery_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_battery_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_battery_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_battery_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_battery_day_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_battery_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_battery_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_battery_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_battery_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_battery_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_battery_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_battery_day_lbl1, &style_setting_screen_battery_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_trip_container
	ui->Setting_Screen_setting_trip_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_trip_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_trip_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_trip_container_main_main_default
	static lv_style_t style_setting_screen_setting_trip_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_trip_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_trip_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_trip_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_trip_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_trip_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_trip_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_trip_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_trip_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_trip_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_trip_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_trip_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_trip_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_trip_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_trip_container, &style_setting_screen_setting_trip_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_up_arr_img
	ui->Setting_Screen_trip_up_arr_img = lv_img_create(ui->Setting_Screen_setting_trip_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_up_arr_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_trip_up_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_up_arr_img_main_main_default
	static lv_style_t style_setting_screen_trip_up_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_trip_up_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_trip_up_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_trip_up_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_trip_up_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_trip_up_arr_img, &style_setting_screen_trip_up_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_trip_up_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_trip_up_arr_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_trip_up_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_trip_up_arr_img, 0);

	//Write codes Setting_Screen_trip_down_arr_img
	ui->Setting_Screen_trip_down_arr_img = lv_img_create(ui->Setting_Screen_setting_trip_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_down_arr_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_trip_down_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_down_arr_img_main_main_default
	static lv_style_t style_setting_screen_trip_down_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_trip_down_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_trip_down_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_trip_down_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_trip_down_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_trip_down_arr_img, &style_setting_screen_trip_down_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_trip_down_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_trip_down_arr_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_trip_down_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_trip_down_arr_img, 0);

	//Write codes Setting_Screen_trip_lbl1
	ui->Setting_Screen_trip_lbl1 = lv_label_create(ui->Setting_Screen_setting_trip_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_lbl1, 20, 97);
	lv_obj_set_size(ui->Setting_Screen_trip_lbl1, 200, 26);
	lv_label_set_text(ui->Setting_Screen_trip_lbl1, "Av Speed 999 L/100km");
	lv_label_set_long_mode(ui->Setting_Screen_trip_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_trip_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_lbl1_main_main_default
	static lv_style_t style_setting_screen_trip_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_trip_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_trip_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_trip_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_trip_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_trip_lbl1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_trip_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_trip_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_trip_lbl1, &style_setting_screen_trip_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_lbl2
	ui->Setting_Screen_trip_lbl2 = lv_label_create(ui->Setting_Screen_setting_trip_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_lbl2, 20, 145);
	lv_obj_set_size(ui->Setting_Screen_trip_lbl2, 200, 26);
	lv_label_set_text(ui->Setting_Screen_trip_lbl2, "Av Speed 999 L/100km");
	lv_label_set_long_mode(ui->Setting_Screen_trip_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_trip_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_lbl2_main_main_default
	static lv_style_t style_setting_screen_trip_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_trip_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_trip_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_trip_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_trip_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_trip_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_trip_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_trip_lbl2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_trip_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_trip_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_trip_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_trip_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_trip_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_trip_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_trip_lbl2, &style_setting_screen_trip_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_lbl3
	ui->Setting_Screen_trip_lbl3 = lv_label_create(ui->Setting_Screen_setting_trip_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_lbl3, 20, 193);
	lv_obj_set_size(ui->Setting_Screen_trip_lbl3, 200, 26);
	lv_label_set_text(ui->Setting_Screen_trip_lbl3, "Hold           to   Set");
	lv_label_set_long_mode(ui->Setting_Screen_trip_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_trip_lbl3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_lbl3_main_main_default
	static lv_style_t style_setting_screen_trip_lbl3_main_main_default;
	lv_style_reset(&style_setting_screen_trip_lbl3_main_main_default);
	lv_style_set_radius(&style_setting_screen_trip_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_trip_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_trip_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_trip_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_trip_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_trip_lbl3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_trip_lbl3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_trip_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_trip_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_trip_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_trip_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_trip_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_trip_lbl3, &style_setting_screen_trip_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_hold_btn
	ui->Setting_Screen_trip_hold_btn = lv_img_create(ui->Setting_Screen_setting_trip_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_hold_btn, 90, 118);
	lv_obj_set_size(ui->Setting_Screen_trip_hold_btn, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_hold_btn_main_main_default
	static lv_style_t style_setting_screen_trip_hold_btn_main_main_default;
	lv_style_reset(&style_setting_screen_trip_hold_btn_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_trip_hold_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_trip_hold_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_trip_hold_btn_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_trip_hold_btn, &style_setting_screen_trip_hold_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_trip_hold_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_trip_hold_btn,&_img_night_menu_btn_20x20);
	lv_img_set_pivot(ui->Setting_Screen_trip_hold_btn, 0,0);
	lv_img_set_angle(ui->Setting_Screen_trip_hold_btn, 0);

	//Write codes Setting_Screen_setting_trip_day_container
	ui->Setting_Screen_setting_trip_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_trip_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_trip_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_trip_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_trip_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_trip_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_trip_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_trip_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_trip_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_trip_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_trip_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_trip_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_trip_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_trip_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_trip_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_trip_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_trip_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_trip_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_trip_day_container, &style_setting_screen_setting_trip_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_day_circle
	ui->Setting_Screen_trip_day_circle = lv_img_create(ui->Setting_Screen_setting_trip_day_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_day_circle, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_trip_day_circle, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_day_circle_main_main_default
	static lv_style_t style_setting_screen_trip_day_circle_main_main_default;
	lv_style_reset(&style_setting_screen_trip_day_circle_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_trip_day_circle_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_trip_day_circle_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_trip_day_circle_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_trip_day_circle, &style_setting_screen_trip_day_circle_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_trip_day_circle, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_trip_day_circle,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_trip_day_circle, 0,0);
	lv_img_set_angle(ui->Setting_Screen_trip_day_circle, 0);

	//Write codes Setting_Screen_trip_day_up_arr
	ui->Setting_Screen_trip_day_up_arr = lv_img_create(ui->Setting_Screen_setting_trip_day_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_day_up_arr, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_trip_day_up_arr, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_day_up_arr_main_main_default
	static lv_style_t style_setting_screen_trip_day_up_arr_main_main_default;
	lv_style_reset(&style_setting_screen_trip_day_up_arr_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_trip_day_up_arr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_trip_day_up_arr_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_trip_day_up_arr_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_trip_day_up_arr, &style_setting_screen_trip_day_up_arr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_trip_day_up_arr, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_trip_day_up_arr,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_trip_day_up_arr, 0,0);
	lv_img_set_angle(ui->Setting_Screen_trip_day_up_arr, 0);

	//Write codes Setting_Screen_trip_day_down_arr
	ui->Setting_Screen_trip_day_down_arr = lv_img_create(ui->Setting_Screen_setting_trip_day_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_day_down_arr, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_trip_day_down_arr, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_day_down_arr_main_main_default
	static lv_style_t style_setting_screen_trip_day_down_arr_main_main_default;
	lv_style_reset(&style_setting_screen_trip_day_down_arr_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_trip_day_down_arr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_trip_day_down_arr_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_trip_day_down_arr_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_trip_day_down_arr, &style_setting_screen_trip_day_down_arr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_trip_day_down_arr, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_trip_day_down_arr,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_trip_day_down_arr, 0,0);
	lv_img_set_angle(ui->Setting_Screen_trip_day_down_arr, 0);

	//Write codes Setting_Screen_trip_day_lbl1
	ui->Setting_Screen_trip_day_lbl1 = lv_label_create(ui->Setting_Screen_setting_trip_day_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_day_lbl1, 20, 97);
	lv_obj_set_size(ui->Setting_Screen_trip_day_lbl1, 200, 26);
	lv_label_set_text(ui->Setting_Screen_trip_day_lbl1, "Av Speed 999 L/100km");
	lv_label_set_long_mode(ui->Setting_Screen_trip_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_trip_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_day_lbl1_main_main_default
	static lv_style_t style_setting_screen_trip_day_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_trip_day_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_trip_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_trip_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_trip_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_trip_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_trip_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_trip_day_lbl1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_trip_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_trip_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_trip_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_trip_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_trip_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_trip_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_trip_day_lbl1, &style_setting_screen_trip_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_day_lbl2
	ui->Setting_Screen_trip_day_lbl2 = lv_label_create(ui->Setting_Screen_setting_trip_day_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_day_lbl2, 20, 145);
	lv_obj_set_size(ui->Setting_Screen_trip_day_lbl2, 200, 26);
	lv_label_set_text(ui->Setting_Screen_trip_day_lbl2, "Av Speed 999 L/100km");
	lv_label_set_long_mode(ui->Setting_Screen_trip_day_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_trip_day_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_day_lbl2_main_main_default
	static lv_style_t style_setting_screen_trip_day_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_trip_day_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_trip_day_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_trip_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_trip_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_trip_day_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_trip_day_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_trip_day_lbl2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_trip_day_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_trip_day_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_trip_day_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_trip_day_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_trip_day_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_trip_day_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_trip_day_lbl2, &style_setting_screen_trip_day_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_day_lbl3
	ui->Setting_Screen_trip_day_lbl3 = lv_label_create(ui->Setting_Screen_setting_trip_day_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_day_lbl3, 20, 193);
	lv_obj_set_size(ui->Setting_Screen_trip_day_lbl3, 200, 26);
	lv_label_set_text(ui->Setting_Screen_trip_day_lbl3, "Hold           to   Set");
	lv_label_set_long_mode(ui->Setting_Screen_trip_day_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_trip_day_lbl3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_day_lbl3_main_main_default
	static lv_style_t style_setting_screen_trip_day_lbl3_main_main_default;
	lv_style_reset(&style_setting_screen_trip_day_lbl3_main_main_default);
	lv_style_set_radius(&style_setting_screen_trip_day_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_trip_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_trip_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_trip_day_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_trip_day_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_trip_day_lbl3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_trip_day_lbl3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_trip_day_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_trip_day_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_trip_day_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_trip_day_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_trip_day_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_trip_day_lbl3, &style_setting_screen_trip_day_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_day_hold
	ui->Setting_Screen_trip_day_hold = lv_img_create(ui->Setting_Screen_setting_trip_day_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_day_hold, 90, 118);
	lv_obj_set_size(ui->Setting_Screen_trip_day_hold, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_day_hold_main_main_default
	static lv_style_t style_setting_screen_trip_day_hold_main_main_default;
	lv_style_reset(&style_setting_screen_trip_day_hold_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_trip_day_hold_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_trip_day_hold_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_trip_day_hold_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_trip_day_hold, &style_setting_screen_trip_day_hold_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_trip_day_hold, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_trip_day_hold,&_day_sub_btn_20x20);
	lv_img_set_pivot(ui->Setting_Screen_trip_day_hold, 0,0);
	lv_img_set_angle(ui->Setting_Screen_trip_day_hold, 0);

	//Write codes Setting_Screen_setting_disc_night_container
	ui->Setting_Screen_setting_disc_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_disc_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_disc_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_disc_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_disc_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_disc_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_disc_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_disc_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_disc_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_disc_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_disc_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_disc_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_disc_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_disc_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_disc_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_disc_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_disc_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_disc_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_disc_night_container, &style_setting_screen_setting_disc_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_disc_up_arr_img
	ui->Setting_Screen_disc_up_arr_img = lv_img_create(ui->Setting_Screen_setting_disc_night_container);
	lv_obj_set_pos(ui->Setting_Screen_disc_up_arr_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_disc_up_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_disc_up_arr_img_main_main_default
	static lv_style_t style_setting_screen_disc_up_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_disc_up_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_disc_up_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_disc_up_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_disc_up_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_disc_up_arr_img, &style_setting_screen_disc_up_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_disc_up_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_disc_up_arr_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_disc_up_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_disc_up_arr_img, 0);

	//Write codes Setting_Screen_disc_up_down_img
	ui->Setting_Screen_disc_up_down_img = lv_img_create(ui->Setting_Screen_setting_disc_night_container);
	lv_obj_set_pos(ui->Setting_Screen_disc_up_down_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_disc_up_down_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_disc_up_down_img_main_main_default
	static lv_style_t style_setting_screen_disc_up_down_img_main_main_default;
	lv_style_reset(&style_setting_screen_disc_up_down_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_disc_up_down_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_disc_up_down_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_disc_up_down_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_disc_up_down_img, &style_setting_screen_disc_up_down_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_disc_up_down_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_disc_up_down_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_disc_up_down_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_disc_up_down_img, 0);

	//Write codes Setting_Screen_dis_night_lb1
	ui->Setting_Screen_dis_night_lb1 = lv_label_create(ui->Setting_Screen_setting_disc_night_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_night_lb1, 25, 98);
	lv_obj_set_size(ui->Setting_Screen_dis_night_lb1, 190, 20);
	lv_label_set_text(ui->Setting_Screen_dis_night_lb1, "");
	lv_label_set_long_mode(ui->Setting_Screen_dis_night_lb1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_dis_night_lb1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_night_lb1_main_main_default
	static lv_style_t style_setting_screen_dis_night_lb1_main_main_default;
	lv_style_reset(&style_setting_screen_dis_night_lb1_main_main_default);
	lv_style_set_radius(&style_setting_screen_dis_night_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_dis_night_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_dis_night_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_dis_night_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_dis_night_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_dis_night_lb1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_dis_night_lb1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_dis_night_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_dis_night_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_dis_night_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_dis_night_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_dis_night_lb1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_dis_night_lb1, &style_setting_screen_dis_night_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_dis_night_lb2
	ui->Setting_Screen_dis_night_lb2 = lv_label_create(ui->Setting_Screen_setting_disc_night_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_night_lb2, 25, 146);
	lv_obj_set_size(ui->Setting_Screen_dis_night_lb2, 190, 20);
	lv_label_set_text(ui->Setting_Screen_dis_night_lb2, "");
	lv_label_set_long_mode(ui->Setting_Screen_dis_night_lb2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_dis_night_lb2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_night_lb2_main_main_default
	static lv_style_t style_setting_screen_dis_night_lb2_main_main_default;
	lv_style_reset(&style_setting_screen_dis_night_lb2_main_main_default);
	lv_style_set_radius(&style_setting_screen_dis_night_lb2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_dis_night_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_dis_night_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_dis_night_lb2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_dis_night_lb2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_dis_night_lb2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_dis_night_lb2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_dis_night_lb2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_dis_night_lb2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_dis_night_lb2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_dis_night_lb2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_dis_night_lb2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_dis_night_lb2, &style_setting_screen_dis_night_lb2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_dis_night_lb3
	ui->Setting_Screen_dis_night_lb3 = lv_label_create(ui->Setting_Screen_setting_disc_night_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_night_lb3, 25, 194);
	lv_obj_set_size(ui->Setting_Screen_dis_night_lb3, 190, 20);
	lv_label_set_text(ui->Setting_Screen_dis_night_lb3, "");
	lv_label_set_long_mode(ui->Setting_Screen_dis_night_lb3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_dis_night_lb3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_night_lb3_main_main_default
	static lv_style_t style_setting_screen_dis_night_lb3_main_main_default;
	lv_style_reset(&style_setting_screen_dis_night_lb3_main_main_default);
	lv_style_set_radius(&style_setting_screen_dis_night_lb3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_dis_night_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_dis_night_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_dis_night_lb3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_dis_night_lb3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_dis_night_lb3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_dis_night_lb3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_dis_night_lb3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_dis_night_lb3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_dis_night_lb3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_dis_night_lb3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_dis_night_lb3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_dis_night_lb3, &style_setting_screen_dis_night_lb3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_disc_day_container
	ui->Setting_Screen_setting_disc_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_disc_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_disc_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_disc_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_disc_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_disc_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_disc_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_disc_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_disc_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_disc_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_disc_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_disc_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_disc_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_disc_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_disc_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_disc_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_disc_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_disc_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_disc_day_container, &style_setting_screen_setting_disc_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_disc_day_base_img
	ui->Setting_Screen_disc_day_base_img = lv_img_create(ui->Setting_Screen_setting_disc_day_container);
	lv_obj_set_pos(ui->Setting_Screen_disc_day_base_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_disc_day_base_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_disc_day_base_img_main_main_default
	static lv_style_t style_setting_screen_disc_day_base_img_main_main_default;
	lv_style_reset(&style_setting_screen_disc_day_base_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_disc_day_base_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_disc_day_base_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_disc_day_base_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_disc_day_base_img, &style_setting_screen_disc_day_base_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_disc_day_base_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_disc_day_base_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_disc_day_base_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_disc_day_base_img, 0);

	//Write codes Setting_Screen_dis_day_up_arr_img
	ui->Setting_Screen_dis_day_up_arr_img = lv_img_create(ui->Setting_Screen_setting_disc_day_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_day_up_arr_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_dis_day_up_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_day_up_arr_img_main_main_default
	static lv_style_t style_setting_screen_dis_day_up_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_dis_day_up_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_dis_day_up_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_dis_day_up_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_dis_day_up_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_dis_day_up_arr_img, &style_setting_screen_dis_day_up_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_dis_day_up_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_dis_day_up_arr_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_dis_day_up_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_dis_day_up_arr_img, 0);

	//Write codes Setting_Screen_dis_day_down_arr_img
	ui->Setting_Screen_dis_day_down_arr_img = lv_img_create(ui->Setting_Screen_setting_disc_day_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_day_down_arr_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_dis_day_down_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_day_down_arr_img_main_main_default
	static lv_style_t style_setting_screen_dis_day_down_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_dis_day_down_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_dis_day_down_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_dis_day_down_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_dis_day_down_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_dis_day_down_arr_img, &style_setting_screen_dis_day_down_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_dis_day_down_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_dis_day_down_arr_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_dis_day_down_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_dis_day_down_arr_img, 0);

	//Write codes Setting_Screen_dis_day_lb1
	ui->Setting_Screen_dis_day_lb1 = lv_label_create(ui->Setting_Screen_setting_disc_day_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_day_lb1, 25, 98);
	lv_obj_set_size(ui->Setting_Screen_dis_day_lb1, 190, 20);
	lv_label_set_text(ui->Setting_Screen_dis_day_lb1, "");
	lv_label_set_long_mode(ui->Setting_Screen_dis_day_lb1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_dis_day_lb1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_day_lb1_main_main_default
	static lv_style_t style_setting_screen_dis_day_lb1_main_main_default;
	lv_style_reset(&style_setting_screen_dis_day_lb1_main_main_default);
	lv_style_set_radius(&style_setting_screen_dis_day_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_dis_day_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_dis_day_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_dis_day_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_dis_day_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_dis_day_lb1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_dis_day_lb1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_dis_day_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_dis_day_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_dis_day_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_dis_day_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_dis_day_lb1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_dis_day_lb1, &style_setting_screen_dis_day_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_dis_day_lb2
	ui->Setting_Screen_dis_day_lb2 = lv_label_create(ui->Setting_Screen_setting_disc_day_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_day_lb2, 25, 146);
	lv_obj_set_size(ui->Setting_Screen_dis_day_lb2, 190, 20);
	lv_label_set_text(ui->Setting_Screen_dis_day_lb2, "");
	lv_label_set_long_mode(ui->Setting_Screen_dis_day_lb2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_dis_day_lb2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_day_lb2_main_main_default
	static lv_style_t style_setting_screen_dis_day_lb2_main_main_default;
	lv_style_reset(&style_setting_screen_dis_day_lb2_main_main_default);
	lv_style_set_radius(&style_setting_screen_dis_day_lb2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_dis_day_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_dis_day_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_dis_day_lb2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_dis_day_lb2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_dis_day_lb2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_dis_day_lb2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_dis_day_lb2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_dis_day_lb2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_dis_day_lb2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_dis_day_lb2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_dis_day_lb2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_dis_day_lb2, &style_setting_screen_dis_day_lb2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_dis_day_lb3
	ui->Setting_Screen_dis_day_lb3 = lv_label_create(ui->Setting_Screen_setting_disc_day_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_day_lb3, 25, 194);
	lv_obj_set_size(ui->Setting_Screen_dis_day_lb3, 190, 20);
	lv_label_set_text(ui->Setting_Screen_dis_day_lb3, "");
	lv_label_set_long_mode(ui->Setting_Screen_dis_day_lb3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_dis_day_lb3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_day_lb3_main_main_default
	static lv_style_t style_setting_screen_dis_day_lb3_main_main_default;
	lv_style_reset(&style_setting_screen_dis_day_lb3_main_main_default);
	lv_style_set_radius(&style_setting_screen_dis_day_lb3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_dis_day_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_dis_day_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_dis_day_lb3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_dis_day_lb3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_dis_day_lb3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_dis_day_lb3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_dis_day_lb3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_dis_day_lb3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_dis_day_lb3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_dis_day_lb3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_dis_day_lb3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_dis_day_lb3, &style_setting_screen_dis_day_lb3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_Setting_disclaimer_night_new
	ui->Setting_Screen_Setting_disclaimer_night_new = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_Setting_disclaimer_night_new, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_Setting_disclaimer_night_new, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_disclaimer_night_new_main_main_default
	static lv_style_t style_setting_screen_setting_disclaimer_night_new_main_main_default;
	lv_style_reset(&style_setting_screen_setting_disclaimer_night_new_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_disclaimer_night_new_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_disclaimer_night_new_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_disclaimer_night_new_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_disclaimer_night_new_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_Setting_disclaimer_night_new, &style_setting_screen_setting_disclaimer_night_new_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_dis_msg_night_img
	ui->Setting_Screen_dis_msg_night_img = lv_img_create(ui->Setting_Screen_Setting_disclaimer_night_new);
	lv_obj_set_pos(ui->Setting_Screen_dis_msg_night_img, 24, 89);
	lv_obj_set_size(ui->Setting_Screen_dis_msg_night_img, 192, 134);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_msg_night_img_main_main_default
	static lv_style_t style_setting_screen_dis_msg_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_dis_msg_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_dis_msg_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_dis_msg_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_dis_msg_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_dis_msg_night_img, &style_setting_screen_dis_msg_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->Setting_Screen_dis_msg_night_img,&dis_night);

	//Write codes Setting_Screen_Setting_disclaimer_day_new
	ui->Setting_Screen_Setting_disclaimer_day_new = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_Setting_disclaimer_day_new, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_Setting_disclaimer_day_new, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_disclaimer_day_new_main_main_default
	static lv_style_t style_setting_screen_setting_disclaimer_day_new_main_main_default;
	lv_style_reset(&style_setting_screen_setting_disclaimer_day_new_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_disclaimer_day_new_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_disclaimer_day_new_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_disclaimer_day_new_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_disclaimer_day_new_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_Setting_disclaimer_day_new, &style_setting_screen_setting_disclaimer_day_new_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_dis_day_whitebaseimg
	ui->Setting_Screen_dis_day_whitebaseimg = lv_img_create(ui->Setting_Screen_Setting_disclaimer_day_new);
	lv_obj_set_pos(ui->Setting_Screen_dis_day_whitebaseimg, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_dis_day_whitebaseimg, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_day_whitebaseimg_main_main_default
	static lv_style_t style_setting_screen_dis_day_whitebaseimg_main_main_default;
	lv_style_reset(&style_setting_screen_dis_day_whitebaseimg_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_dis_day_whitebaseimg_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_dis_day_whitebaseimg_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_dis_day_whitebaseimg_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_dis_day_whitebaseimg, &style_setting_screen_dis_day_whitebaseimg_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_dis_day_whitebaseimg, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_dis_day_whitebaseimg,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_dis_day_whitebaseimg, 0,0);
	lv_img_set_angle(ui->Setting_Screen_dis_day_whitebaseimg, 0);

	//Write codes Setting_Screen_dis_msg_day_img
	ui->Setting_Screen_dis_msg_day_img = lv_img_create(ui->Setting_Screen_Setting_disclaimer_day_new);
	lv_obj_set_pos(ui->Setting_Screen_dis_msg_day_img, 24, 89);
	lv_obj_set_size(ui->Setting_Screen_dis_msg_day_img, 192, 134);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_msg_day_img_main_main_default
	static lv_style_t style_setting_screen_dis_msg_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_dis_msg_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_dis_msg_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_dis_msg_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_dis_msg_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_dis_msg_day_img, &style_setting_screen_dis_msg_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_dis_msg_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_dis_msg_day_img,&dis_day);
	lv_img_set_pivot(ui->Setting_Screen_dis_msg_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_dis_msg_day_img, 0);



	//Write codes Setting_Screen_setting_ghost_images
	ui->Setting_Screen_setting_ghost_images = lv_img_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_ghost_images, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_ghost_images, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_ghost_images_main_main_default
	static lv_style_t style_setting_screen_setting_ghost_images_main_main_default;
	lv_style_reset(&style_setting_screen_setting_ghost_images_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_setting_ghost_images_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_setting_ghost_images_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_setting_ghost_images_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_ghost_images, &style_setting_screen_setting_ghost_images_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_setting_ghost_images, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_setting_ghost_images,&_1_240x320);
	lv_img_set_pivot(ui->Setting_Screen_setting_ghost_images, 0,0);
	lv_img_set_angle(ui->Setting_Screen_setting_ghost_images, 0);
	}

	uint8_t Fuel_Consumption_fn(void)
	{
		return (g_User_Sel_TC_Unit);
	}

	uint8_t Distance_fn(void)
	{
		return (g_User_Sel_Distance_Unit);
	}

	uint8_t GUI_am_pm_Setting(void)
	{
		return (g_display_am_pm_u8);
	}

	uint8_t GUI_Get_Time_Format(void)
	{
		return (g_Clock_Format_Selection_Cmd);
	}

	void NVM_Write_RTC_Time_Format(void)
	{
		uint8_t fl_setting_Screen_NVM_Data[6];

		fl_setting_Screen_NVM_Data[0] = g_NVM_Menu_Selection_Data_u8;

		fl_setting_Screen_NVM_Data[1] = g_Clock_Format_Selection_Cmd;

		fl_setting_Screen_NVM_Data[2] = g_User_Brightness_Level_u8;

		fl_setting_Screen_NVM_Data[3] = g_User_Sel_TC_Unit;

		fl_setting_Screen_NVM_Data[4] = g_BLE_Status_u8;

		fl_setting_Screen_NVM_Data[5] = g_User_Music_Select_Level_U8;

		NVM_Byte_Write_Allocation(NVM_SETTING_SCREEN_NVM_DATA,&fl_setting_Screen_NVM_Data[0]);
		
	}

	uint8_t NVM_Read_RTC_Time_Format(void)
	{
		uint8_t fl_Clock_format_u8;

		NVM_Byte_Read_Allocation(NVM_SETTING_SCREEN_NVM_DATA,&fl_Clock_format_u8);

		return (fl_Clock_format_u8);
	}

	uint8_t HMI_Setting_Screen_Get_Brightness_Level(void)
	{

		return (g_User_Brightness_Level_u8);
	}

	uint8_t GUI_BLE_Enable_Status(void)
	{
		return g_BLE_Status_u8;
	}

	uint8_t HMI_Menu_Setting_Get_NVM_Data(void)
	{
		return (g_NVM_Menu_Selection_Data_u8);
	}
	

/*  Time & Date Setting */

void GUI_Up_Button_Press_Set_time(void)
{
	if (g_Hour_Min_Meridian_Sel_Cnt == 0)
	{
		g_display_time_hr = g_display_time_hr + 1;

		/* check for hour value violation */
		if ((g_Clock_Format_Selection_Cmd == CLOCK_12HR_FORMAT) && (g_display_time_hr > 12))
		{
			g_display_time_hr = 1;
		}
		else if (g_Clock_Format_Selection_Cmd == CLOCK_24HR_FORMAT)
		{
			g_display_time_hr = (g_display_time_hr % 24);
		}
	}
	else if (g_Hour_Min_Meridian_Sel_Cnt == 1)
	{
		g_display_time_min = g_display_time_min + 1;

		/* check for minute value violation */
		g_display_time_min = g_display_time_min % 60;
	}
	else if (g_Hour_Min_Meridian_Sel_Cnt == 2)
		{
			/*check 12 or 24 hours*/
			if (g_Clock_Format_Selection_Cmd == CLOCK_12HR_FORMAT)
			{
				if (g_display_am_pm_u8 == 1)
				{
					g_display_am_pm_u8 = 2;
				}
				else
				{
					g_display_am_pm_u8 = 1;
				}
			}
			else
			{
				/*do nothing*/
				g_display_am_pm_u8 = 3;
			}
		}
		else
		{
			/*Do nothing*/
		}
}


uint8_t GUI_Up_Button_Hr_Set_time(void)
{
	g_Display_hr_Arrow_status = 1;
	g_display_time_hr = g_display_time_hr + 1;

	/* check for hour value violation */
	if ((g_Clock_Format_Selection_Cmd == CLOCK_12HR_FORMAT) && (g_display_time_hr > 12))
	{
		g_display_time_hr = 1;
	}
	else if (g_Clock_Format_Selection_Cmd == CLOCK_24HR_FORMAT)
	{
		g_display_time_hr = (g_display_time_hr % 24);
	}
	else{}
	return 0;
}


uint8_t GUI_Up_Button_Min_Set_time(void)
{
	g_Display_min_Arrow_status = 1;
	g_display_time_min = g_display_time_min + 1;
	/* check for minute value violation */
	g_display_time_min = g_display_time_min % 60;
	return 0;
}


uint8_t GUI_Down_Button_Min_Set_time(void)
{
	g_Display_min_Arrow_status = 2;
	if (g_display_time_min >= 1)
	{
		g_display_time_min = g_display_time_min - 1;
	}
	else if (g_display_time_min <= 0)
	{
		g_display_time_min = 59;
	}
	return 0;
}



uint8_t GUI_Down_Button_Hr_Set_time(void)
{
	g_Display_hr_Arrow_status = 2;
	if (g_Clock_Format_Selection_Cmd == CLOCK_24HR_FORMAT)
	{
		/* To avoid negative value of hour , roll over has to be done ,
		when try to decrease hour value from 0, it will display 23*/
		if (g_display_time_hr <= 0)
		{
			g_display_time_hr = 23;
		}
		else
		{
			g_display_time_hr = g_display_time_hr - 1;
		}
	}
	else
	{
		/* FOR 12HR format */
		if(g_display_time_hr == 0)
		{
			g_display_time_hr = 12;	
		}
		else
		{
			g_display_time_hr = g_display_time_hr - 1;

			if (g_display_time_hr <= 0)
			{
				g_display_time_hr = 12;
			}
		}
	}

	return 0;
}


uint8_t GUI_UP_Button_Merdian_Set_time(void)
{
	g_Display_ampm_Arrow_status = 1;
	/*check 12 or 24 hours*/
	if (g_Clock_Format_Selection_Cmd == CLOCK_12HR_FORMAT)
	{
		if (g_display_am_pm_u8 == 1)
		{
			g_display_am_pm_u8 = 2;
		}
		else
		{
			g_display_am_pm_u8 = 1;
		}
	}
	else
	{
		/*do nothing*/
		g_display_am_pm_u8 = 3;
	}
	return 0;
}


uint8_t GUI_Down_Button_Merdian_Set_time(void)
{
	g_Display_ampm_Arrow_status = 2;
	/*check 12 or 24 hours*/
	if (g_Clock_Format_Selection_Cmd == CLOCK_12HR_FORMAT)
	{
		if (g_display_am_pm_u8 == 1)
		{
			g_display_am_pm_u8 = 2;
		}
		else
		{
			g_display_am_pm_u8 = 1;
		}
	}
	else
	{
		/*do nothing*/
		g_display_am_pm_u8 = 3;
	}
	return 0;
}



void GUI_Down_Button_Press_Set_time(void)
{
	if (g_Hour_Min_Meridian_Sel_Cnt == 0)
	{
		if (g_Clock_Format_Selection_Cmd == CLOCK_24HR_FORMAT)
		{
		/* To avoid negative value of hour , roll over has to be done ,
		when try to decrease hour value from 0, it will display 23*/
		if (g_display_time_hr <= 0)
		{
			g_display_time_hr = 23;
		}
		else
		{
			g_display_time_hr = g_display_time_hr - 1;
		}
		}
		else
		{
			/* FOR 12HR format */
			g_display_time_hr = g_display_time_hr - 1;

			if (g_display_time_hr <= 0)
			{
				g_display_time_hr = 12;
			}
		}
	}

	else if (g_Hour_Min_Meridian_Sel_Cnt == 1)
	{
		if (g_display_time_min >= 1)
		{
			g_display_time_min = g_display_time_min - 1;
		}
		else if (g_display_time_min <= 0)
		{
			g_display_time_min = 59;
		}
	}

	else if (g_Hour_Min_Meridian_Sel_Cnt == 2)
	{
		/*check 12 or 24 hours*/
		if (g_Clock_Format_Selection_Cmd == CLOCK_12HR_FORMAT)
		{
			if (g_display_am_pm_u8 == 1)
			{
				g_display_am_pm_u8 = 2;
			}
			else
			{
				g_display_am_pm_u8 = 1;
			}
		}
		else
		{
			/*do nothing*/
			g_display_am_pm_u8 = 3;
		}
	}
}

uint8_t GUI_Up_Button_Date_Setting(void)
{
	g_Display_Date_Arrow_status = 1;
	g_Display_Date_Day_Timer_u8 = g_Display_Date_Day_Timer_u8 + 1;
	GUI_Leap_year_check_And_Month_end_St();

	return 0;
}

uint8_t GUI_Up_Button_Month_Setting(void)
{
	g_Display_Month_Arrow_status = 1;
	g_Display_Month_Timer_u8 = g_Display_Month_Timer_u8 + 1;

	/* check for month value violaton */
	if (g_Display_Month_Timer_u8 > 12)
	{
		g_Display_Month_Timer_u8 = 1;
	}

	/* Day will be changed to valid if needed */
	HMI_Change_Valid_Day_based_On_Month_Year_Setting();
	return 0;
}

uint8_t GUI_Up_Button_year_Setting(void)
{
	g_Display_Year_Arrow_status = 1;
	g_Display_Year_Timer_u16 = g_Display_Year_Timer_u16 + 1;

	if (g_Display_Year_Timer_u16 > MAX_DISPLAYABLE_YEAR)
	{
		g_Display_Year_Timer_u16 = MAX_DISPLAYABLE_YEAR;
	}

	/* Day will be changed to valid if needed */
	HMI_Change_Valid_Day_based_On_Month_Year_Setting();

	return 0;
}


uint8_t GUI_Down_button_Date_Setting(void)
{
	g_Display_Date_Arrow_status = 2;
	g_Display_Date_Day_Timer_u8 = g_Display_Date_Day_Timer_u8 - 1;
	GUI_Leap_year_check_And_Month_end_St();
	return 0;
}


uint8_t  GUI_Down_Button_Month_setting(void)
{
	g_Display_Month_Arrow_status = 2;
	if (g_Display_Month_Timer_u8 > 1)
	{
		g_Display_Month_Timer_u8 = g_Display_Month_Timer_u8 - 1;
	}
	else
	{
		g_Display_Month_Timer_u8 = 12;
	}

	/* Day will be changed to valid if needed */
	HMI_Change_Valid_Day_based_On_Month_Year_Setting();

	return 0;
}

uint8_t GUI_Down_Button_Year_setting(void)
{
	g_Display_Year_Arrow_status = 2;
	g_Display_Year_Timer_u16 = g_Display_Year_Timer_u16 - 1;

	/* check year value violation  Year ranges from 2022 to 2050*/
	if (g_Display_Year_Timer_u16 < MIN_DISPLAYABLE_YEAR)
	{
		g_Display_Year_Timer_u16 = MIN_DISPLAYABLE_YEAR;
	}

	/* Day will be changed to valid if needed */
	HMI_Change_Valid_Day_based_On_Month_Year_Setting();

	return 0;
}



void Display_hr_Time_Setting_Day_During(void)
{


	if(g_Display_hr_Arrow_status == 1)
	{
		lv_img_set_src(guider_ui.Setting_Screen_time_day_up_arr_1,&day_up_btn_pressed);
		lv_img_set_src(guider_ui.Setting_Screen_time_day_down_arr_1,&_day_down_arrow_20x11);

		g_Display_hr_Arrow_status = 0;
	}
	else if(g_Display_hr_Arrow_status == 2)
	{
		lv_img_set_src(guider_ui.Setting_Screen_time_day_up_arr_1,&_day_up_arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_time_day_down_arr_1,&day_down_btn_pressed);
		g_Display_hr_Arrow_status = 0;
	}
	else
	{
		lv_img_set_src(guider_ui.Setting_Screen_time_day_up_arr_1,&_day_up_arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_time_day_down_arr_1,&_day_down_arrow_20x11);
		g_Display_hr_Arrow_status = 0;
	}

	if(g_display_time_hr <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl1, "0%d", g_display_time_hr);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl1, "%d", g_display_time_hr);
	}

	if(g_display_time_min <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl2, "0%d", g_display_time_min);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl2, "%d", g_display_time_min);
	}
   
   
	
        if (g_display_am_pm_u8 == 1)
        {

            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl3, "AM");


        }
        else if (g_display_am_pm_u8 == 2)
        {
         
            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl3, "PM");

        

        }
        else if (g_display_am_pm_u8 == 3)
        {
           
            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl3, "");

        }
		else{}
		
		if(g_Clock_Format_Selection_Cmd == 0)//24
		{
			lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_3,LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_3,LV_OBJ_FLAG_HIDDEN);
		}
		else if(g_Clock_Format_Selection_Cmd == 1)//12
		{
			// lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_up_arr_3,LV_OBJ_FLAG_HIDDEN);
			// lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_down_arr_3,LV_OBJ_FLAG_HIDDEN);
		}
}


void Display_min_Time_Setting_Day_During(void)
{

	if(g_Display_min_Arrow_status == 1)
	{
		lv_img_set_src(guider_ui.Setting_Screen_time_day_up_arr_2,&day_up_btn_pressed);
		lv_img_set_src(guider_ui.Setting_Screen_time_day_down_arr_2,&_day_down_arrow_20x11);

		g_Display_min_Arrow_status = 0;
	}
	else if(g_Display_min_Arrow_status == 2)
	{
		lv_img_set_src(guider_ui.Setting_Screen_time_day_up_arr_2,&_day_up_arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_time_day_down_arr_2,&day_down_btn_pressed);
		g_Display_min_Arrow_status = 0;
	}
	else
	{
		lv_img_set_src(guider_ui.Setting_Screen_time_day_up_arr_2,&_day_up_arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_time_day_down_arr_2,&_day_down_arrow_20x11);
		g_Display_min_Arrow_status = 0;
	}

	if(g_display_time_hr <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl1, "0%d", g_display_time_hr);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl1, "%d", g_display_time_hr);
	}

	if(g_display_time_min <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl2, "0%d", g_display_time_min);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl2, "%d", g_display_time_min);
	}
   
   
	
        if (g_display_am_pm_u8 == 1)
        {

            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl3, "AM");


        }
        else if (g_display_am_pm_u8 == 2)
        {
         
            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl3, "PM");

        

        }
        else if (g_display_am_pm_u8 == 3)
        {
           
            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl3, "");

        }
		else{}
		
		if(g_Clock_Format_Selection_Cmd == 0)//24
		{
			lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_3,LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_3,LV_OBJ_FLAG_HIDDEN);
		}
		else if(g_Clock_Format_Selection_Cmd == 1)//12
		{
			// lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_up_arr_3,LV_OBJ_FLAG_HIDDEN);
			// lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_down_arr_3,LV_OBJ_FLAG_HIDDEN);
		}
}

void Display_ampm_Time_Setting_Day_During(void)
{
	if(g_display_time_hr <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl1, "0%d", g_display_time_hr);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl1, "%d", g_display_time_hr);
	}

	if(g_display_time_min <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl2, "0%d", g_display_time_min);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl2, "%d", g_display_time_min);
	}
   
  
        if (g_display_am_pm_u8 == 1)
        {

            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl3, "AM");


        }
        else if (g_display_am_pm_u8 == 2)
        {
         
            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl3, "PM");

        

        }
        else if (g_display_am_pm_u8 == 3)
        {
           
            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl3, "");		
			
        }

			if(g_Clock_Format_Selection_Cmd == 0)//24
			{
				lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_3,LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_3,LV_OBJ_FLAG_HIDDEN);
			}
			else if(g_Clock_Format_Selection_Cmd == 1)//12
			{


				// lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_up_arr_3,LV_OBJ_FLAG_HIDDEN);
				// lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_down_arr_3,LV_OBJ_FLAG_HIDDEN);
			}

			if(g_Display_ampm_Arrow_status == 1)
		{
			lv_img_set_src(guider_ui.Setting_Screen_time_day_up_arr_3,&day_up_btn_pressed);
			lv_img_set_src(guider_ui.Setting_Screen_time_day_down_arr_3,&_day_down_arrow_20x11);

			g_Display_ampm_Arrow_status = 0;
		}
		else if(g_Display_ampm_Arrow_status == 2)
		{
			lv_img_set_src(guider_ui.Setting_Screen_time_day_up_arr_3,&_day_up_arrow_20x11);
			lv_img_set_src(guider_ui.Setting_Screen_time_day_down_arr_3,&day_down_btn_pressed);
			g_Display_ampm_Arrow_status = 0;
		}
		else
		{
			lv_img_set_src(guider_ui.Setting_Screen_time_day_up_arr_3,&_day_up_arrow_20x11);
			lv_img_set_src(guider_ui.Setting_Screen_time_day_down_arr_3,&_day_down_arrow_20x11);
			g_Display_ampm_Arrow_status = 0;
		}

}

void Display_hr_Time_Setting_Night_During(void)
{
	
	if(g_Display_hr_Arrow_status == 1)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_time_night_up_arr_1,&night_up_btn_pressed_);
		lv_img_set_src(guider_ui.Setting_Screen_time_night_down_arr_1,&_Setting_Drow_Arrow_20x11);
		g_Display_hr_Arrow_status = 0;
	}
	else if(g_Display_hr_Arrow_status == 2)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_time_night_up_arr_1,&_Setting_Up_Arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_time_night_down_arr_1,&night_down_btn_pressed_);
		g_Display_hr_Arrow_status = 0;
	}
	else
	{
		 lv_img_set_src(guider_ui.Setting_Screen_time_night_up_arr_1,&_Setting_Up_Arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_time_night_down_arr_1,&_Setting_Drow_Arrow_20x11);
		g_Display_hr_Arrow_status = 0;
	}



	if(g_display_time_hr <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl1, "0%d", g_display_time_hr);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl1, "%d", g_display_time_hr);
	}

	if(g_display_time_min <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl2, "0%d", g_display_time_min);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl2, "%d", g_display_time_min);
	}
   
   
	
        if (g_display_am_pm_u8 == 1)
        {

            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl3, "AM");


        }
        else if (g_display_am_pm_u8 == 2)
        {
         
            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl3, "PM");

        

        }
        else if (g_display_am_pm_u8 == 3)
        {
           
            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl3, "");

        }
		else{}
		
		if(g_Clock_Format_Selection_Cmd == 0)//24
		{
			lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_3,LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_3,LV_OBJ_FLAG_HIDDEN);
		}
		else if(g_Clock_Format_Selection_Cmd == 1)//12
		{
			// lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_up_arr_3,LV_OBJ_FLAG_HIDDEN);
			// lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_down_arr_3,LV_OBJ_FLAG_HIDDEN);
		}
}
void Display_min_Time_Setting_Night_During(void)
{

	if(g_Display_min_Arrow_status == 1)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_time_night_up_arr_2,&night_up_btn_pressed_);
		lv_img_set_src(guider_ui.Setting_Screen_time_night_down_arr_2,&_Setting_Drow_Arrow_20x11);
		g_Display_min_Arrow_status = 0;
	}
	else if(g_Display_min_Arrow_status == 2)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_time_night_up_arr_2,&_Setting_Up_Arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_time_night_down_arr_2,&night_down_btn_pressed_);
		g_Display_min_Arrow_status = 0;
	}
	else
	{
		 lv_img_set_src(guider_ui.Setting_Screen_time_night_up_arr_2,&_Setting_Up_Arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_time_night_down_arr_2,&_Setting_Drow_Arrow_20x11);
		g_Display_min_Arrow_status = 0;
	}

	if(g_display_time_hr <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl1, "0%d", g_display_time_hr);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl1, "%d", g_display_time_hr);
	}

	if(g_display_time_min <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl2, "0%d", g_display_time_min);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl2, "%d", g_display_time_min);
	}
   
   
	
        if (g_display_am_pm_u8 == 1)
        {

            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl3, "AM");


        }
        else if (g_display_am_pm_u8 == 2)
        {
         
            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl3, "PM");

        

        }
        else if (g_display_am_pm_u8 == 3)
        {
           
            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl3, "");

        }
		else{}
		
		if(g_Clock_Format_Selection_Cmd == 0)//24
		{
			lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_3,LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_3,LV_OBJ_FLAG_HIDDEN);
		}
		else if(g_Clock_Format_Selection_Cmd == 1)//12
		{
			// lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_up_arr_3,LV_OBJ_FLAG_HIDDEN);
			// lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_down_arr_3,LV_OBJ_FLAG_HIDDEN);
		}
}

void Display_ampm_Time_Setting_Night_During(void)
{
  	if(g_display_time_hr <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl1, "0%d", g_display_time_hr);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl1, "%d", g_display_time_hr);
	}

	if(g_display_time_min <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl2, "0%d", g_display_time_min);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl2, "%d", g_display_time_min);
	}
        if (g_display_am_pm_u8 == 1)
        {

            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl3, "AM");


        }
        else if (g_display_am_pm_u8 == 2)
        {
         
            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl3, "PM");

        

        }
        else if (g_display_am_pm_u8 == 3)
        {
           
            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_night_lbl3, "");		
			
        }

		if(g_Clock_Format_Selection_Cmd == 0)//24
		{
			lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_3,LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_3,LV_OBJ_FLAG_HIDDEN);
		}
		else if(g_Clock_Format_Selection_Cmd == 1)//12
		{


			// lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_up_arr_3,LV_OBJ_FLAG_HIDDEN);
			// lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_down_arr_3,LV_OBJ_FLAG_HIDDEN);
		}
		else
		{

		}

			if(g_Display_ampm_Arrow_status == 1)
			{
				lv_img_set_src(guider_ui.Setting_Screen_time_night_up_arr_3,&night_up_btn_pressed_);
				lv_img_set_src(guider_ui.Setting_Screen_time_night_down_arr_3,&_Setting_Drow_Arrow_20x11);
				g_Display_ampm_Arrow_status = 0;
			}
			else if(g_Display_ampm_Arrow_status == 2)
			{
				lv_img_set_src(guider_ui.Setting_Screen_time_night_up_arr_3,&_Setting_Up_Arrow_20x11);
				lv_img_set_src(guider_ui.Setting_Screen_time_night_down_arr_3,&night_down_btn_pressed_);
				g_Display_ampm_Arrow_status = 0;
			}
			else
			{
				lv_img_set_src(guider_ui.Setting_Screen_time_night_up_arr_3,&_Setting_Up_Arrow_20x11);
				lv_img_set_src(guider_ui.Setting_Screen_time_night_down_arr_3,&_Setting_Drow_Arrow_20x11);
				g_Display_ampm_Arrow_status = 0;
			}

}



uint8_t GUI_Check_12Hr_Time_Format(void)
{
	uint8_t fl_return_status;

	if (g_Clock_Format_Selection_Cmd == CLOCK_24HR_FORMAT)
	{
		SetCrntScreen(HOME_SET_DISP_DATE_TIME_TIME_SET_HR);
		fl_return_status = 1;
	}
	else
	{
		fl_return_status = 0;
	}

	return fl_return_status;
}

uint8_t GUI_Check_24Hr_Time_Format(void)
{
	uint8_t fl_return_status;

	if (g_Clock_Format_Selection_Cmd == CLOCK_24HR_FORMAT)
	{
		 fl_return_status = 0;
	}
	else
	{
		fl_return_status = 1;
	}
	return fl_return_status;
}

uint8_t RTC_Set_Time_Hour_Min(void)//Long press
{
	/* Update current Time to variable used for Time setting */
	RTC_Set_User_Selected_Time(g_display_time_hr, g_display_time_min);
	return 0;
}




uint8_t Get_Date_variable(void)
{
	g_Crnt_TimeSt = RTC_Time_Display();
	g_Display_Date_Day_Timer_u8 = g_Crnt_TimeSt.day;
    g_Display_Month_Timer_u8 = g_Crnt_TimeSt.month;
    g_Display_Year_Timer_u16 = g_Crnt_TimeSt.year;
	return 0;
}

uint8_t Get_Time_variable(void)
{
	g_Crnt_TimeSt = RTC_Time_Display();
	g_display_time_hr =Get_display_Hr();
	g_display_time_min = g_Crnt_TimeSt.minute;
	g_display_am_pm_u8 = Get_Time_Meridian_Sel();
	return 0;
}

void Display_Date_Setting_Night_During(void)
{

	if(g_Display_Date_Arrow_status == 1)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_night_up_arr_1,&night_up_btn_pressed_);
		lv_img_set_src(guider_ui.Setting_Screen_date_night_down_arr_1,&_Setting_Drow_Arrow_20x11);
		g_Display_Date_Arrow_status = 0;
	}
	else if(g_Display_Date_Arrow_status == 2)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_night_up_arr_1,&_Setting_Up_Arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_date_night_down_arr_1,&night_down_btn_pressed_);
		g_Display_Date_Arrow_status = 0;
	}
	else
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_night_up_arr_1,&_Setting_Up_Arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_date_night_down_arr_1,&_Setting_Drow_Arrow_20x11);
		g_Display_Date_Arrow_status = 0;
	}

	if(g_Display_Month_Timer_u8 <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl2, "0%d", g_Display_Month_Timer_u8);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl2, "%d", g_Display_Month_Timer_u8);
	}

	if(g_Display_Date_Day_Timer_u8 <= 9)
	{
		  lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl1, "0%d", g_Display_Date_Day_Timer_u8);
	}
	else
	{
	 	 lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl1, "%d", g_Display_Date_Day_Timer_u8);
	}

    
  
    lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl3, "%d", g_Display_Year_Timer_u16);
}
void Display_Month_Setting_Night_During(void)
{

	if(g_Display_Month_Arrow_status == 1)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_night_up_arr_2,&night_up_btn_pressed_);
		lv_img_set_src(guider_ui.Setting_Screen_date_night_down_arr_2,&_Setting_Drow_Arrow_20x11);
		g_Display_Month_Arrow_status = 0;
	}
	else if(g_Display_Month_Arrow_status == 2)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_night_up_arr_2,&_Setting_Up_Arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_date_night_down_arr_2,&night_down_btn_pressed_);
		g_Display_Month_Arrow_status = 0;
	}
	else
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_night_up_arr_2,&_Setting_Up_Arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_date_night_down_arr_2,&_Setting_Drow_Arrow_20x11);
		g_Display_Month_Arrow_status = 0;
	}

	if(g_Display_Month_Timer_u8 <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl2, "0%d", g_Display_Month_Timer_u8);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl2, "%d", g_Display_Month_Timer_u8);
	}

	if(g_Display_Date_Day_Timer_u8 <= 9)
	{
		  lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl1, "0%d", g_Display_Date_Day_Timer_u8);
	}
	else
	{
	 	 lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl1, "%d", g_Display_Date_Day_Timer_u8);
	}

    
  
    lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl3, "%d", g_Display_Year_Timer_u16);
}
void Display_Year_Setting_Night_During(void)
{

	if(g_Display_Year_Arrow_status == 1)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_night_up_arr_3,&night_up_btn_pressed_);
		lv_img_set_src(guider_ui.Setting_Screen_date_night_down_arr_3,&_Setting_Drow_Arrow_20x11);
		g_Display_Year_Arrow_status = 0;
	}
	else if(g_Display_Year_Arrow_status == 2)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_night_up_arr_3,&_Setting_Up_Arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_date_night_down_arr_3,&night_down_btn_pressed_);
		g_Display_Year_Arrow_status = 0;
	}
	else
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_night_up_arr_3,&_Setting_Up_Arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_date_night_down_arr_3,&_Setting_Drow_Arrow_20x11);
		g_Display_Year_Arrow_status = 0;
	}

	if(g_Display_Month_Timer_u8 <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl2, "0%d", g_Display_Month_Timer_u8);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl2, "%d", g_Display_Month_Timer_u8);
	}

	if(g_Display_Date_Day_Timer_u8 <= 9)
	{
		  lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl1, "0%d", g_Display_Date_Day_Timer_u8);
	}
	else
	{
	 	 lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl1, "%d", g_Display_Date_Day_Timer_u8);
	}

    
  
    lv_label_set_text_fmt(guider_ui.Setting_Screen_date_night_lbl3, "%d", g_Display_Year_Timer_u16);
}


/*DAY*/
void Display_Date_Setting_Day_During(void)
{

	if(g_Display_Date_Arrow_status == 1)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_day_up_arr_1,&day_up_btn_pressed);
		lv_img_set_src(guider_ui.Setting_Screen_date_day_down_arr_1,&_day_down_arrow_20x11);
		g_Display_Date_Arrow_status = 0;
	}
	else if(g_Display_Date_Arrow_status == 2)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_day_up_arr_1,&_day_up_arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_date_day_down_arr_1,&day_down_btn_pressed);
		g_Display_Date_Arrow_status = 0;
	}
	else
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_day_up_arr_1,&_day_up_arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_date_day_down_arr_1,&_day_down_arrow_20x11);
		g_Display_Date_Arrow_status = 0;
	}

	if(g_Display_Month_Timer_u8 <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl2, "0%d", g_Display_Month_Timer_u8);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl2, "%d", g_Display_Month_Timer_u8);
	}

	if(g_Display_Date_Day_Timer_u8 <= 9)
	{
		 lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl1, "0%d", g_Display_Date_Day_Timer_u8);
	}
	else
	{
	 	lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl1, "%d", g_Display_Date_Day_Timer_u8);
	}

    lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl3, "%d", g_Display_Year_Timer_u16);
}

void Display_Month_Setting_Day_During(void)
{

	if(g_Display_Month_Arrow_status == 1)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_day_up_arr_2,&day_up_btn_pressed);
		lv_img_set_src(guider_ui.Setting_Screen_date_day_down_arr_2,&_day_down_arrow_20x11);
		g_Display_Month_Arrow_status = 0;
	}
	else if(g_Display_Month_Arrow_status == 2)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_day_up_arr_2,&_day_up_arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_date_day_down_arr_2,&day_down_btn_pressed);
		g_Display_Month_Arrow_status = 0;
	}
	else
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_day_up_arr_2,&_day_up_arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_date_day_down_arr_2,&_day_down_arrow_20x11);
		g_Display_Month_Arrow_status = 0;
	}

	if(g_Display_Month_Timer_u8 <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl2, "0%d", g_Display_Month_Timer_u8);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl2, "%d", g_Display_Month_Timer_u8);
	}

	if(g_Display_Date_Day_Timer_u8 <= 9)
	{
		 lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl1, "0%d", g_Display_Date_Day_Timer_u8);
	}
	else
	{
	 	lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl1, "%d", g_Display_Date_Day_Timer_u8);
	}

    lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl3, "%d", g_Display_Year_Timer_u16);
}

void Display_Year_Setting_Day_During(void)
{

	if(g_Display_Year_Arrow_status == 1)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_day_up_arr_3,&day_up_btn_pressed);
		lv_img_set_src(guider_ui.Setting_Screen_date_day_down_arr_3,&_day_down_arrow_20x11);
		g_Display_Year_Arrow_status = 0;
	}
	else if(g_Display_Year_Arrow_status == 2)
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_day_up_arr_3,&_day_up_arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_date_day_down_arr_3,&day_down_btn_pressed);
		g_Display_Year_Arrow_status = 0;
	}
	else
	{
		 lv_img_set_src(guider_ui.Setting_Screen_date_day_up_arr_3,&_day_up_arrow_20x11);
		lv_img_set_src(guider_ui.Setting_Screen_date_day_down_arr_3,&_day_down_arrow_20x11);
		g_Display_Year_Arrow_status = 0;
	}


	if(g_Display_Month_Timer_u8 <= 9)
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl2, "0%d", g_Display_Month_Timer_u8);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl2, "%d", g_Display_Month_Timer_u8);
	}

	if(g_Display_Date_Day_Timer_u8 <= 9)
	{
		 lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl1, "0%d", g_Display_Date_Day_Timer_u8);
	}
	else
	{
	 	lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl1, "%d", g_Display_Date_Day_Timer_u8);
	}

    lv_label_set_text_fmt(guider_ui.Setting_Screen_date_day_lbl3, "%d", g_Display_Year_Timer_u16);
}



void Display_Time_Setting_Day_During(void)
{
	
    lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl1, "%d", g_display_time_hr);
	lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl2, "%d", g_display_time_min);
        if (g_display_am_pm_u8 == 1)
        {

            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl3, "AM");


        }
        else if (g_display_am_pm_u8 == 2)
        {
         
            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl3, "PM");

        

        }
        else if (g_display_am_pm_u8 == 3)
        {
           
            lv_label_set_text_fmt(guider_ui.Setting_Screen_time_day_lbl3, "");		
			
        }

		if(g_Clock_Format_Selection_Cmd == 0)//24
		{
			lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_3,LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_3,LV_OBJ_FLAG_HIDDEN);
		}
		else if(g_Clock_Format_Selection_Cmd == 1)//12
		{


		// 	lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_up_arr_3,LV_OBJ_FLAG_HIDDEN);
		// 	lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_down_arr_3,LV_OBJ_FLAG_HIDDEN);
		}

}

void HMI_Change_Valid_Day_based_On_Month_Year_Setting(void)
{
	/* check Is day valid for selected month */
	if(g_Display_Month_Timer_u8 == 2)
	{
		/* Leap year , feburary month should have max of 29 */
		if ((Is_Leap_year() != FALSE) && (g_Display_Date_Day_Timer_u8 > 29))
		{
			g_Display_Date_Day_Timer_u8 = 29;
		}
		else if ((Is_Leap_year() == FALSE) && (g_Display_Date_Day_Timer_u8 > 28))
		{
			g_Display_Date_Day_Timer_u8 = 28;
		}
	}
	else if(Days_In_Month[(g_Display_Month_Timer_u8 - 1)][1] < g_Display_Date_Day_Timer_u8)
	{
		/* change day to valid one */
		g_Display_Date_Day_Timer_u8 = Days_In_Month[(g_Display_Month_Timer_u8 - 1)][1];
	} 
}


bool Is_Leap_year(void)
{
	bool fl_ret_Status = FALSE;

	/* leap year check */
	if ((((g_Display_Year_Timer_u16 & 3U) == 0U) && 
	    (g_Display_Year_Timer_u16 % 100U != 0U)) || 
		 (g_Display_Year_Timer_u16 % 400U == 0U))
	{
		/* CURRENT YEAR IS LEAP YEAR */
		fl_ret_Status = TRUE;
	}	 

	return (fl_ret_Status);
}
void GUI_Leap_year_check_And_Month_end_St(void)
{
	if (g_Display_Month_Timer_u8 == 2)
	{
		if (((g_Display_Date_Day_Timer_u8 > 29) && (Is_Leap_year() != FALSE)) ||
			((g_Display_Date_Day_Timer_u8 > 28) && (Is_Leap_year() == FALSE)))
		{
			g_Display_Date_Day_Timer_u8 = 1;
		}
		else if ((Is_Leap_year() != FALSE) && (g_Display_Date_Day_Timer_u8 == 0))
		{
			g_Display_Date_Day_Timer_u8 = 29;
		}
		else if ((Is_Leap_year() == FALSE) && (g_Display_Date_Day_Timer_u8 == 0))
		{
			g_Display_Date_Day_Timer_u8 = 28;
		}
	}
	else
	{
		for (int i = 0; i < 12; i++)
		{
			/* Go to selected month */
			if (g_Display_Month_Timer_u8 == Days_In_Month[i][0])
			{
				/* check selected day value is greater than actual max day of ths month */
				if (g_Display_Date_Day_Timer_u8 > Days_In_Month[i][1])
				{
					g_Display_Date_Day_Timer_u8 = 1;
				}
				else if (g_Display_Date_Day_Timer_u8 <= 0)
				{
					g_Display_Date_Day_Timer_u8 = Days_In_Month[i][1];
				}
			}
		}
	}
}



uint8_t RTC_Set_Date_Month_year(void)//Long press
{
	/* Update current Date to variable used for date setting */
	RTC_Set_User_Selected_Date(g_Display_Date_Day_Timer_u8, g_Display_Month_Timer_u8, g_Display_Year_Timer_u16);
	return 0;
}


void Setting_Screen_During_Fn(void)
{
	GUI_HMI_Setting_Screen_Clk_Handler();
	GUI_Setting_Screen_Telltale_Handler();
}

bool HMI_Setting_Screen_Is_Exit_Cond_Met(void)
{
	bool fl_Ret_Status_bl = FALSE;
	uint16_t fl_Speedo_Value_u16 = 0;

	/* Get vehicle speed */
	fl_Speedo_Value_u16 = Get_display_Speed();

	/* displayed vehicle speed greater than 10kms, 
	 *cluster shall exit from setting screen and move to home screen */
	if(fl_Speedo_Value_u16 > HMI_USM_ALLOWED_VEHICLE_SPEED)
	{
		fl_Ret_Status_bl = TRUE;
	}
	else
	{
		fl_Ret_Status_bl = FALSE;
	}	

	/* Return */
	return (fl_Ret_Status_bl);
}

/***********************************************************************************************************************
											  E N D   O F   S O F T W A R E
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
	REVISION NUMBER      : v1.0.0
	REVISION DATE        : 06/09/2022
	CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)
	DESCRIPTION          : Initial version
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! FILE NAME */
