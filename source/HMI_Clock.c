
/* @file FILE NAME */
#ifndef HMI_CLOCK_C
#define HMI_CLOCK_C

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
#include <gen/events_init.h>
#include <gen/gui_guider.h>
#include "peripherals.h"

#include "../lvgl/lvgl.h"

#include "custom.h"
#include "fsl_gpio.h"

#include "HMI_Clock.h"

#include "rtc.h"

#include "HMI_Setting_Screen.h"

#include "Ambient_light_sensor.h"

#include "Ambient_light_sensor_Cfg.h"



#include "lvgl_app.h"

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
	uint8_t g_display_Hr;

	uint8_t g_HMI_blink_u8;

	uint8_t g_Time_Meridian_Sel_u8;

	

	signed int Mainscr_12hr_x_val[4] = {80, 105, 110, 125};
	signed int Mainscr_12hr_y_val[4] = {78, 78, 78, 78};

	signed int Mainscr_24hr_x_val[3] = {93, 118, 125};
	signed int Mainscr_24hr_y_val[3] = {78, 78, 78};

	signed int Clockposition_x_val[4] = {86, 109, 113, 118};
	signed int Clockposition_y_val[4] = {69, 69, 69, 69};

	signed int Clockposition_Setting_12_x_val[4]={88,111,115,130};
	signed int Clockposition_Setting_12_y_val[4]={280,280,280,280};

	signed int Clockposition_Setting_24_x_val[3] = {94, 118, 123};
	signed int Clockposition_Setting_24_y_val[3] = {280, 280, 280};

	signed int Clockposition_Setting_Fnt_x_val[4] = {80, 107, 113, 125};
	signed int Clockposition_Setting_Fnt_y_val[4] = {69, 69, 69, 69};

	signed int Clockposition_24_x_val[3] = {98, 117, 122};
	signed int Clockposition_24_y_val[3] = {69, 69, 69};

	bool g_Clk_Colon_Flash_Staus;

	uint8_t g_previous_Time_Foramt_Clock_u8;
	uint8_t g_previous_RTC_TIME_STAMP_ST = 0;
	RTC_TIME_STAMP_ST g_previous_l_display_datetime_u8;

	extern  bool g_Img_Blink_bl;

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
	void Gui_HMI_Clock_Init(void)
	{
		g_display_Hr = 0;

		g_HMI_blink_u8 = 0;

		g_Time_Meridian_Sel_u8 = 0;
	}

	void Gui_HMI_Clock_Deinit(void)
	{
		g_display_Hr = 0;

		g_HMI_blink_u8 = 0;

		g_Time_Meridian_Sel_u8 = 0;
	}

	void GUI_HMI_CLK_Night_Handler(void)
	{		
		
		SNVS_Type *base_add;
		RTC_TIME_STAMP_ST fl_present_l_display_datetime_u32; // fl_present_l_display_datetime_u32;

		uint8_t l_time_set_u8 = 0;
		// uint8_t fl_Get_Current_Time_Foramt_Clock;
		uint8_t fl_Time_Meridian_Sel_u8;
		RTC_TIME_STAMP_ST fl_present_l_display_datetime_u8;

		/*Get the RTC value*/
		uint8_t fl_present_Time_Foramt_Clock = GUI_Get_Time_Format(); // g_previous_Time_Foramt_Clock_u32;
		fl_present_l_display_datetime_u8 = RTC_Time_Display();

		if ((g_previous_Time_Foramt_Clock_u8 != fl_present_Time_Foramt_Clock) || (g_previous_l_display_datetime_u8.hour != fl_present_l_display_datetime_u8.hour) || (g_previous_l_display_datetime_u8.minute != fl_present_l_display_datetime_u8.minute))
		{
			g_previous_Time_Foramt_Clock_u8 = fl_present_Time_Foramt_Clock;
			g_previous_l_display_datetime_u8.hour = fl_present_l_display_datetime_u8.hour;
			g_previous_l_display_datetime_u8.minute = fl_present_l_display_datetime_u8.minute;

			if (g_previous_Time_Foramt_Clock_u8 == CLOCK_12HR_FORMAT)
			{
				if (g_previous_l_display_datetime_u8.hour == 0)
				{
					g_display_Hr = 12;
					fl_Time_Meridian_Sel_u8 = 1;
				}
				else if (g_previous_l_display_datetime_u8.hour < 12)
				{
					g_display_Hr = g_previous_l_display_datetime_u8.hour;

					fl_Time_Meridian_Sel_u8 = 1;
				}
				else
				{
					if (g_previous_l_display_datetime_u8.hour > 12)
					{
						g_display_Hr = g_previous_l_display_datetime_u8.hour - 12;
					}
					else
					{
						g_display_Hr = g_previous_l_display_datetime_u8.hour;
					}

					fl_Time_Meridian_Sel_u8 = 2;
				}
			}
			else
			{
				g_display_Hr = g_previous_l_display_datetime_u8.hour;

				fl_Time_Meridian_Sel_u8 = 3;
				//GUI_Main24hr_position();
				//	flag_24hr = 1;
			}

			lv_label_set_text_fmt(guider_ui.screen_Clock_hour, "%d%d", (g_display_Hr / 10), (g_display_Hr % 10));

			lv_label_set_text_fmt(guider_ui.screen_Clock_Colan, "%c", ':');
			lv_label_set_text_fmt(guider_ui.screen_Clock_min, "%d%d", (g_previous_l_display_datetime_u8.minute / 10), (g_previous_l_display_datetime_u8.minute % 10));

				if (fl_Time_Meridian_Sel_u8 == 1)
				{
					lv_label_set_text_fmt(guider_ui.screen_Clock_Am, "AM");

				}
				else if (fl_Time_Meridian_Sel_u8 == 2)
				{
					lv_label_set_text_fmt(guider_ui.screen_Clock_Am, "PM");

				}
				else
				{
					lv_label_set_text_fmt(guider_ui.screen_Clock_Am, "");

				}
			
		}

		if (g_Clk_Colon_Flash_Staus != FALSE)
		{
			lv_label_set_text_fmt(guider_ui.screen_Clock_Colan, "%c", ':');

		}
		else if (g_Clk_Colon_Flash_Staus == FALSE)
		{
			lv_label_set_text_fmt(guider_ui.screen_Clock_Colan, "");

		}
	}
	void GUI_HMI_Clk_Day_Handler(void)
	{		
		
		SNVS_Type *base_add;
		RTC_TIME_STAMP_ST fl_present_l_display_datetime_u32; // fl_present_l_display_datetime_u32;

		uint8_t l_time_set_u8 = 0;
		// uint8_t fl_Get_Current_Time_Foramt_Clock;
		uint8_t fl_Time_Meridian_Sel_u8;
		RTC_TIME_STAMP_ST fl_present_l_display_datetime_u8;

		/*Get the RTC value*/
		uint8_t fl_present_Time_Foramt_Clock = GUI_Get_Time_Format(); // g_previous_Time_Foramt_Clock_u32;
		fl_present_l_display_datetime_u8 = RTC_Time_Display();

		if ((g_previous_Time_Foramt_Clock_u8 != fl_present_Time_Foramt_Clock) || (g_previous_l_display_datetime_u8.hour != fl_present_l_display_datetime_u8.hour) || (g_previous_l_display_datetime_u8.minute != fl_present_l_display_datetime_u8.minute))
		{
			g_previous_Time_Foramt_Clock_u8 = fl_present_Time_Foramt_Clock;
			g_previous_l_display_datetime_u8.hour = fl_present_l_display_datetime_u8.hour;
			g_previous_l_display_datetime_u8.minute = fl_present_l_display_datetime_u8.minute;

			if (g_previous_Time_Foramt_Clock_u8 == CLOCK_12HR_FORMAT)
			{
				if (g_previous_l_display_datetime_u8.hour == 0)
				{
					g_display_Hr = 12;
					fl_Time_Meridian_Sel_u8 = 1;
				}
				else if (g_previous_l_display_datetime_u8.hour < 12)
				{
					g_display_Hr = g_previous_l_display_datetime_u8.hour;

					fl_Time_Meridian_Sel_u8 = 1;
				}
				else
				{
					if (g_previous_l_display_datetime_u8.hour > 12)
					{
						g_display_Hr = g_previous_l_display_datetime_u8.hour - 12;
					}
					else
					{
						g_display_Hr = g_previous_l_display_datetime_u8.hour;
					}

					fl_Time_Meridian_Sel_u8 = 2;
				}
			}
			else
			{
				g_display_Hr = g_previous_l_display_datetime_u8.hour;

				fl_Time_Meridian_Sel_u8 = 3;
			}

			lv_label_set_text_fmt(guider_ui.screen_Day_hour, "%d%d", (g_display_Hr / 10), (g_display_Hr % 10));

			lv_label_set_text_fmt(guider_ui.screen_Day_colon, "%c", ':');
			lv_label_set_text_fmt(guider_ui.screen_Day_min, "%d%d", (g_previous_l_display_datetime_u8.minute / 10), (g_previous_l_display_datetime_u8.minute % 10));

				if (fl_Time_Meridian_Sel_u8 == 1)
				{

					lv_label_set_text_fmt(guider_ui.screen_Day_Am_pm, "AM");
				}
				else if (fl_Time_Meridian_Sel_u8 == 2)
				{

					lv_label_set_text_fmt(guider_ui.screen_Day_Am_pm, "PM");
				}
				else
				{

					lv_label_set_text_fmt(guider_ui.screen_Day_Am_pm, "");
				}
			
		}

		//
		if (g_Clk_Colon_Flash_Staus != FALSE)
		{
			lv_label_set_text_fmt(guider_ui.screen_Day_colon, "%c", ':');

		}
		else if (g_Clk_Colon_Flash_Staus == FALSE)
		{
			lv_label_set_text_fmt(guider_ui.screen_Day_colon, "");

		}
	}

	void GUI_Clock_Entry(void)
	{
		g_previous_Time_Foramt_Clock_u8 = 0xFF;
		g_previous_l_display_datetime_u8.hour = 0xFF;
		g_previous_l_display_datetime_u8.minute = 0xFF;
	}

	/* GUI Handlders */
	void GUI_HMI_Setting_Screen_Clk_Handler(void)
	{
		SNVS_Type *base_add;
		RTC_TIME_STAMP_ST fl_present_l_display_datetime_u8;
		uint8_t l_time_set_u8 = 0;
		//	uint8_t fl_Get_Current_Time_Foramt_Clock;

		fl_present_l_display_datetime_u8 = RTC_Time_Display();
		uint8_t fl_present_Time_Foramt_Clock = GUI_Get_Time_Format();

		if ((g_previous_Time_Foramt_Clock_u8 != fl_present_Time_Foramt_Clock) || (g_previous_l_display_datetime_u8.hour != fl_present_l_display_datetime_u8.hour) || (g_previous_l_display_datetime_u8.minute != fl_present_l_display_datetime_u8.minute) )
		{
			g_previous_Time_Foramt_Clock_u8 = fl_present_Time_Foramt_Clock;
			g_previous_l_display_datetime_u8.hour = fl_present_l_display_datetime_u8.hour;
			g_previous_l_display_datetime_u8.minute = fl_present_l_display_datetime_u8.minute;

			if (g_previous_Time_Foramt_Clock_u8 == CLOCK_12HR_FORMAT)
			{
				if (g_previous_l_display_datetime_u8.hour == 0)
				{
					g_display_Hr = 12;
					g_Time_Meridian_Sel_u8 = 1;
					GUI_Setting12hr_position();
				}
				else if (g_previous_l_display_datetime_u8.hour < 12)
				{
					g_display_Hr = g_previous_l_display_datetime_u8.hour;

					g_Time_Meridian_Sel_u8 = 1;
					GUI_Setting12hr_position();
				}
				else
				{
					if (g_previous_l_display_datetime_u8.hour > 12)
					{
						/* PM calculation form 24 hrs format value */
						g_display_Hr = g_previous_l_display_datetime_u8.hour - 12;
						GUI_Setting12hr_position();
					}
					else
					{
						g_display_Hr = g_previous_l_display_datetime_u8.hour;
						GUI_Setting12hr_position();
					}

					g_Time_Meridian_Sel_u8 = 2;
				}
			}
			else
			{
				g_display_Hr = g_previous_l_display_datetime_u8.hour;

				g_Time_Meridian_Sel_u8 = 3;
				GUI_Setting24hr_position();
			}

			/*Get the RTC value*/

			lv_label_set_text_fmt(guider_ui.Setting_Screen_Clock_hour, "%d%d", (g_display_Hr / 10), (g_display_Hr % 10));

			lv_label_set_text_fmt(guider_ui.Setting_Screen_Clock_Colan, "%c", ':');
			lv_label_set_text_fmt(guider_ui.Setting_Screen_Clock_min, "%d%d", (g_previous_l_display_datetime_u8.minute / 10), (g_previous_l_display_datetime_u8.minute % 10));

			if (g_Time_Meridian_Sel_u8 == 1)
			{
				lv_label_set_text_fmt(guider_ui.Setting_Screen_Clock_AM, "AM");
			}
			else if (g_Time_Meridian_Sel_u8 == 2)
			{
				lv_label_set_text_fmt(guider_ui.Setting_Screen_Clock_AM, "PM");
			}
			else
			{
				lv_label_set_text_fmt(guider_ui.Setting_Screen_Clock_AM, "");
			}
			
		}

		if (g_Clk_Colon_Flash_Staus != FALSE)
		{
			lv_label_set_text_fmt(guider_ui.Setting_Screen_Clock_Colan, "%c", ':');
		}
		else if (g_Clk_Colon_Flash_Staus == FALSE)
		{
			lv_label_set_text_fmt(guider_ui.Setting_Screen_Clock_Colan, "");
		}

		
	}

	uint8_t Get_display_Hr(void)
	{
		return g_display_Hr;
	}

	uint8_t Get_Time_Meridian_Sel(void)
	{
		return g_Time_Meridian_Sel_u8;
	}

	void GUI_Setting24hr_position(void)
	{
		lv_obj_set_style_text_font(guider_ui.Setting_Screen_Clock_hour, &lv_font_FjallaOne_Regular_17, 0);
		lv_obj_set_style_text_font(guider_ui.Setting_Screen_Clock_hour, &lv_font_FjallaOne_Regular_17, 0);
		lv_obj_set_style_text_font(guider_ui.Setting_Screen_Clock_Colan, &lv_font_FjallaOne_Regular_17, 0);
		lv_obj_set_style_text_font(guider_ui.Setting_Screen_Clock_min, &lv_font_FjallaOne_Regular_17, 0);

		lv_obj_set_pos(guider_ui.Setting_Screen_Clock_hour, Clockposition_Setting_24_x_val[0], Clockposition_Setting_24_y_val[0]);
		lv_obj_set_size(guider_ui.Setting_Screen_Clock_hour, 23, 16);
		lv_obj_set_pos(guider_ui.Setting_Screen_Clock_Colan, Clockposition_Setting_24_x_val[1], Clockposition_Setting_24_y_val[1]);
		lv_obj_set_size(guider_ui.Setting_Screen_Clock_Colan, 5, 16);
		lv_obj_set_pos(guider_ui.Setting_Screen_Clock_min, Clockposition_Setting_24_x_val[2], Clockposition_Setting_24_y_val[2]);
		lv_obj_set_size(guider_ui.Setting_Screen_Clock_min, 24, 16);
	}

	void GUI_Main24hr_position(void)
	{
		uint8_t fl_ambient_mode;

		fl_ambient_mode = Get_day_night_mode_status();

		/* Night Mode clock position */
		if(fl_ambient_mode == NIGHT)
		{

		lv_img_set_src(guider_ui.screen_x1000RPM_Img, &img_night_x1000_RPM_white);

		lv_obj_set_style_text_font(guider_ui.screen_Clock_hour, &lv_font_FjallaOne_Regular_17, 0);
		lv_obj_set_style_text_font(guider_ui.screen_Clock_hour, &lv_font_FjallaOne_Regular_17, 0);
		lv_obj_set_style_text_font(guider_ui.screen_Clock_Colan, &lv_font_FjallaOne_Regular_17, 0);
		lv_obj_set_style_text_font(guider_ui.screen_Clock_min, &lv_font_FjallaOne_Regular_17, 0);
		lv_obj_set_style_text_font(guider_ui.screen_Clock_Am, &lv_font_FjallaOne_Regular_17, 0);

		lv_obj_set_pos(guider_ui.screen_Clock_hour, Mainscr_24hr_x_val[0], Mainscr_24hr_y_val[0]);
		lv_obj_set_size(guider_ui.screen_Clock_hour, 23, 16);
		lv_obj_set_pos(guider_ui.screen_Clock_Colan, Mainscr_24hr_x_val[1], Mainscr_24hr_y_val[1]);
		lv_obj_set_size(guider_ui.screen_Clock_Colan, 5, 16);
		lv_obj_set_pos(guider_ui.screen_Clock_min, Mainscr_24hr_x_val[2], Mainscr_24hr_y_val[2]);
		lv_obj_set_size(guider_ui.screen_Clock_min, 24, 16);

		}
		else if( fl_ambient_mode == DAY)
		{
			/* Day Mode clock position */
			lv_obj_set_style_text_font(guider_ui.screen_Day_hour, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_hour, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_colon, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_min, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_Am_pm, &lv_font_FjallaOne_Regular_17, 0);

			lv_obj_set_pos(guider_ui.screen_Day_hour, Mainscr_24hr_x_val[0], Mainscr_24hr_y_val[0]);
			lv_obj_set_size(guider_ui.screen_Day_hour, 23, 16);
			lv_obj_set_pos(guider_ui.screen_Day_colon, Mainscr_24hr_x_val[1], Mainscr_24hr_y_val[1]);
			lv_obj_set_size(guider_ui.screen_Day_colon, 5, 16);
			lv_obj_set_pos(guider_ui.screen_Day_min, Mainscr_24hr_x_val[2], Mainscr_24hr_y_val[2]);
			lv_obj_set_size(guider_ui.screen_Day_min, 24, 16);
		}
	}

	void GUI_Setting12hr_position(void)
	{
		lv_obj_set_style_text_font(guider_ui.Setting_Screen_Clock_hour, &lv_font_FjallaOne_Regular_17, 0);
		lv_obj_set_style_text_font(guider_ui.Setting_Screen_Clock_hour, &lv_font_FjallaOne_Regular_17, 0);
		lv_obj_set_style_text_font(guider_ui.Setting_Screen_Clock_Colan, &lv_font_FjallaOne_Regular_17, 0);
		lv_obj_set_style_text_font(guider_ui.Setting_Screen_Clock_min, &lv_font_FjallaOne_Regular_17, 0);
		lv_obj_set_style_text_font(guider_ui.Setting_Screen_Clock_AM, &lv_font_FjallaOne_Regular_17, 0);

		lv_obj_set_pos(guider_ui.Setting_Screen_Clock_hour, Clockposition_Setting_12_x_val[0], Clockposition_Setting_12_y_val[0]);
		lv_obj_set_size(guider_ui.Setting_Screen_Clock_hour, 23, 16);
		lv_obj_set_pos(guider_ui.Setting_Screen_Clock_Colan, Clockposition_Setting_12_x_val[1], Clockposition_Setting_12_y_val[1]);
		lv_obj_set_size(guider_ui.Setting_Screen_Clock_Colan, 5, 16);
		lv_obj_set_pos(guider_ui.Setting_Screen_Clock_min, Clockposition_Setting_12_x_val[2], Clockposition_Setting_12_y_val[2]);
		lv_obj_set_size(guider_ui.Setting_Screen_Clock_min, 24, 16);
		lv_obj_set_pos(guider_ui.Setting_Screen_Clock_AM, Clockposition_Setting_12_x_val[3], Clockposition_Setting_12_y_val[3]);
		lv_obj_set_size(guider_ui.Setting_Screen_Clock_AM, 35, 16);
	}

	void GUI_Main12hr_position(void)
	{
		uint8_t fl_ambient_mode;

		fl_ambient_mode = Get_day_night_mode_status();

		if(fl_ambient_mode == NIGHT)
		{
			/* Night Mode clock position */
			lv_img_set_src(guider_ui.screen_x1000RPM_Img, &img_night_x1000_RPM_white);

			lv_obj_set_style_text_font(guider_ui.screen_Clock_hour, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Clock_hour, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Clock_Colan, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Clock_min, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Clock_Am, &lv_font_FjallaOne_Regular_17, 0);

			lv_obj_set_pos(guider_ui.screen_Clock_hour, Mainscr_12hr_x_val[0], Mainscr_12hr_y_val[0]);
			lv_obj_set_size(guider_ui.screen_Clock_hour, 23, 16);
			lv_obj_set_pos(guider_ui.screen_Clock_Colan, Mainscr_12hr_x_val[1], Mainscr_12hr_y_val[1]);
			lv_obj_set_size(guider_ui.screen_Clock_Colan, 5, 16);
			lv_obj_set_pos(guider_ui.screen_Clock_min, Mainscr_12hr_x_val[2], Mainscr_12hr_y_val[2]);
			lv_obj_set_size(guider_ui.screen_Clock_min, 24, 16);
			lv_obj_set_pos(guider_ui.screen_Clock_Am, Mainscr_12hr_x_val[3], Mainscr_12hr_y_val[3]);
			lv_obj_set_size(guider_ui.screen_Clock_Am, 35, 16);
		}
		else if(fl_ambient_mode == DAY)
		{
			/* Day Mode clock position */
			lv_obj_set_style_text_font(guider_ui.screen_Day_hour, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_hour, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_colon, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_min, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_Am_pm, &lv_font_FjallaOne_Regular_17, 0);

			lv_obj_set_style_text_font(guider_ui.screen_Day_hour, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_hour, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_colon, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_min, &lv_font_FjallaOne_Regular_17, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_Am_pm, &lv_font_FjallaOne_Regular_17, 0);

			lv_obj_set_pos(guider_ui.screen_Day_hour, Mainscr_12hr_x_val[0], Mainscr_12hr_y_val[0]);
			lv_obj_set_size(guider_ui.screen_Day_hour, 23, 16);
			lv_obj_set_pos(guider_ui.screen_Day_colon, Mainscr_12hr_x_val[1], Mainscr_12hr_y_val[1]);
			lv_obj_set_size(guider_ui.screen_Day_colon, 5, 16);
			lv_obj_set_pos(guider_ui.screen_Day_min, Mainscr_12hr_x_val[2], Mainscr_12hr_y_val[2]);
			lv_obj_set_size(guider_ui.screen_Day_min, 24, 16);
			lv_obj_set_pos(guider_ui.screen_Day_Am_pm, Mainscr_12hr_x_val[3], Mainscr_12hr_y_val[3]);
			lv_obj_set_size(guider_ui.screen_Day_Am_pm, 35, 16);
			
		}
	}

	void GUI_Intermediate12hr_position(void)
	{
		uint8_t fl_ambient_mode;

		fl_ambient_mode = Get_day_night_mode_status();

		/* Night Mode clock position */
		if(fl_ambient_mode == NIGHT)
		{

			lv_img_set_src(guider_ui.screen_x1000RPM_Img, &img_night_x1000_RPM_grey);

			lv_obj_set_style_text_font(guider_ui.screen_Clock_hour, &lv_font_FjallaOne_Regular_13, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Clock_hour, &lv_font_FjallaOne_Regular_13, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Clock_Colan, &lv_font_FjallaOne_Regular_13, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Clock_min, &lv_font_FjallaOne_Regular_13, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Clock_Am, &lv_font_FjallaOne_Regular_13, 0);

			lv_obj_set_pos(guider_ui.screen_Clock_hour, Clockposition_x_val[0], Clockposition_y_val[0]);
			lv_obj_set_pos(guider_ui.screen_Clock_Colan, Clockposition_x_val[1], Clockposition_y_val[1]);
			lv_obj_set_pos(guider_ui.screen_Clock_min, Clockposition_x_val[2], Clockposition_y_val[2]);
			lv_obj_set_pos(guider_ui.screen_Clock_Am, Clockposition_x_val[3], Clockposition_y_val[3]);

		}
		else if(fl_ambient_mode == DAY)
		{
			/* Day Mode clock position */
			lv_obj_set_style_text_font(guider_ui.screen_Day_hour, &lv_font_FjallaOne_Regular_13, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_hour, &lv_font_FjallaOne_Regular_13, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_colon, &lv_font_FjallaOne_Regular_13, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_min, &lv_font_FjallaOne_Regular_13, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_Am_pm, &lv_font_FjallaOne_Regular_13, 0);

			lv_obj_set_pos(guider_ui.screen_Day_hour, Clockposition_x_val[0], Clockposition_y_val[0]);
			lv_obj_set_size(guider_ui.screen_Day_hour, 23, 16);
			lv_obj_set_pos(guider_ui.screen_Day_colon, Clockposition_x_val[1], Clockposition_y_val[1]);
			lv_obj_set_size(guider_ui.screen_Day_colon, 5, 16);
			lv_obj_set_pos(guider_ui.screen_Day_min, Clockposition_x_val[2], Clockposition_y_val[2]);
			lv_obj_set_size(guider_ui.screen_Day_min, 24, 16);
			lv_obj_set_pos(guider_ui.screen_Day_Am_pm, Clockposition_x_val[3], Clockposition_y_val[3]);
			lv_obj_set_size(guider_ui.screen_Day_Am_pm, 35, 16);
		}
	}

	void GUI_Intermediate24hr_position(void)
	{
		uint8_t fl_ambient_mode;

		fl_ambient_mode = Get_day_night_mode_status();

		if(fl_ambient_mode == NIGHT)
		{
			/* Night Mode clock position */
			lv_img_set_src(guider_ui.screen_x1000RPM_Img, &img_night_x1000_RPM_grey);

			lv_obj_set_style_text_font(guider_ui.screen_Clock_hour, &lv_font_FjallaOne_Regular_14, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Clock_hour, &lv_font_FjallaOne_Regular_14, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Clock_Colan, &lv_font_FjallaOne_Regular_14, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Clock_min, &lv_font_FjallaOne_Regular_14, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Clock_Am, &lv_font_FjallaOne_Regular_14, 0);

			lv_obj_set_pos(guider_ui.screen_Clock_hour, Clockposition_24_x_val[0], Clockposition_24_y_val[0]);
			lv_obj_set_size(guider_ui.screen_Clock_hour, 18, 12);
			lv_obj_set_pos(guider_ui.screen_Clock_Colan, Clockposition_24_x_val[1], Clockposition_24_y_val[1]);
			lv_obj_set_size(guider_ui.screen_Clock_Colan, 3, 12);
			lv_obj_set_pos(guider_ui.screen_Clock_min, Clockposition_24_x_val[2], Clockposition_24_y_val[2]);
			lv_obj_set_size(guider_ui.screen_Clock_min, 18, 12);
		}
		else if(fl_ambient_mode == DAY)
		{
			/* Day Mode clock position */
			lv_obj_set_style_text_font(guider_ui.screen_Day_hour, &lv_font_FjallaOne_Regular_14, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_hour, &lv_font_FjallaOne_Regular_14, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_colon, &lv_font_FjallaOne_Regular_14, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_min, &lv_font_FjallaOne_Regular_14, 0);
			lv_obj_set_style_text_font(guider_ui.screen_Day_Am_pm, &lv_font_FjallaOne_Regular_14, 0);

			lv_obj_set_pos(guider_ui.screen_Day_hour, Clockposition_24_x_val[0], Clockposition_24_y_val[0]);
			lv_obj_set_size(guider_ui.screen_Day_hour, 18, 12);
			lv_obj_set_pos(guider_ui.screen_Day_colon, Clockposition_24_x_val[1], Clockposition_24_y_val[1]);
			lv_obj_set_size(guider_ui.screen_Day_colon, 3, 12);
			lv_obj_set_pos(guider_ui.screen_Day_min, Clockposition_24_x_val[2], Clockposition_24_y_val[2]);
			lv_obj_set_size(guider_ui.screen_Day_min, 18, 12);
		}
	}

	void HMI_Set_CLK_COLON_ON(void)
	{
		g_Clk_Colon_Flash_Staus = TRUE;
		g_Img_Blink_bl = TRUE;
	}

	void HMI_Set_CLK_COLON_OFF(void)
	{
		g_Clk_Colon_Flash_Staus = FALSE;
		g_Img_Blink_bl = FALSE;
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
	DESCRIPTION          : Initial version
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! FILE NAME */
