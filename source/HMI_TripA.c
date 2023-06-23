/* @file FILE NAME */
#ifndef HMI_TRIP_A_C
#define HMI_TRIP_A_C

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

#include "lvgl_app.h"

#include "custom.h"
#include "fsl_gpio.h"
#include "Swc_Trip_Timer.h"
#include "Swc_Trip_Timer_cfg.h"
#include "Swc_Averege_Speed.h"
#include "Swc_Service_Remainder.h"
#include "HMI_Setting_Screen.h"
#include "Swc_Speedometer_Cfg.h"
#include "rtc.h"
#include "TC.h"
#include "Ambient_light_sensor_Cfg.h"
#include "HMI_Clock.h"
#include "HMI_GUI_Interface.h"
#include "HMI_TripA.h"

#define Pressed_State 1
#define UnPressed_State 2

	uint8_t g_TripA_DownKeypressed_U8 = 0;
	uint8_t g_TripA_UpKeypressed_U8 = 0;
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

	typedef enum
	{
		TRIP_LBL_1 = 0,
		TRIP_VALUE_1,
		TRIP_UNIT_1,
		TRIP_LBL_2,
		TRIP_HR_Val,
		TRIP_MI_Val,
		TRIP_HH_Val,
		TRIP_MM_Val,
		TRIP_AVF_LBL_1,
		TRIP_AVF_VALUE_1,
		TRIP_AVF_UNIT_1,
		TRIP_AVF_LBL_2,
		TRIP_AVF_VALUE_2,
		TRIP_AVF_UNIT_2,
		TRIP_MAX_DETAILS
	} Trip_Details_Enum;

	typedef struct
	{
		signed int X_Pos;
		signed int Y_Pos;
	} TripPosDetailsTypeSt;

	const TripPosDetailsTypeSt TripPosDetailsSt[TRIP_MAX_DETAILS] =
		{
			{40, 14},
			{70, 10},
			{124, 16},
			{34, 42},
			{75, 38},
			{115, 38},
			{100, 42},
			{141, 42},
			{5, 15},
			{72, 11},
			{125, 17},
			{-15, 42},
			{10, 38},
			{116, 44}};

	g_Trip_Time_Pos g_Trip_Time_Pos_Table[28] = {
		{(lv_obj_t *)&guider_ui.screen_trip_lbl1, (signed int *)&TripPosDetailsSt[TRIP_LBL_1].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_LBL_1].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_trip_val_1, (signed int *)&TripPosDetailsSt[TRIP_VALUE_1].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_VALUE_1].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_trip_unit_1, (signed int *)&TripPosDetailsSt[TRIP_UNIT_1].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_UNIT_1].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_trip_lbl_2, (signed int *)&TripPosDetailsSt[TRIP_LBL_2].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_LBL_2].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_trip_hr_lbl, (signed int *)&TripPosDetailsSt[TRIP_HR_Val].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_HR_Val].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_trip_mi_lbl, (signed int *)&TripPosDetailsSt[TRIP_MI_Val].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_MI_Val].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_trip_hh_lbl, (signed int *)&TripPosDetailsSt[TRIP_HH_Val].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_HH_Val].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_trip_mm_lbl, (signed int *)&TripPosDetailsSt[TRIP_MM_Val].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_MM_Val].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_day_lbl1, (signed int *)&TripPosDetailsSt[TRIP_LBL_1].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_LBL_1].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_day_lbl2, (signed int *)&TripPosDetailsSt[TRIP_VALUE_1].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_VALUE_1].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_day_lbl3, (signed int *)&TripPosDetailsSt[TRIP_UNIT_1].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_UNIT_1].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_day_lbl4, (signed int *)&TripPosDetailsSt[TRIP_LBL_2].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_LBL_2].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_day_lbl5, (signed int *)&TripPosDetailsSt[TRIP_HR_Val].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_HR_Val].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_day_lbl_7, (signed int *)&TripPosDetailsSt[TRIP_MI_Val].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_MI_Val].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_day_lbl_6, (signed int *)&TripPosDetailsSt[TRIP_HH_Val].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_HH_Val].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_day_lbl_8, (signed int *)&TripPosDetailsSt[TRIP_MM_Val].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_MM_Val].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_L1_lbl, (signed int *)&TripPosDetailsSt[TRIP_AVF_LBL_1].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_AVF_LBL_1].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_L1_val, (signed int *)&TripPosDetailsSt[TRIP_AVF_VALUE_1].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_AVF_VALUE_1].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_L1_unit, (signed int *)&TripPosDetailsSt[TRIP_AVF_UNIT_1].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_AVF_UNIT_1].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_L2_lbl, (signed int *)&TripPosDetailsSt[TRIP_AVF_LBL_2].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_AVF_LBL_2].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_L2_val, (signed int *)&TripPosDetailsSt[TRIP_AVF_VALUE_2].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_AVF_VALUE_2].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_L2_unit, (signed int *)&TripPosDetailsSt[TRIP_AVF_UNIT_2].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_AVF_UNIT_2].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_day_in_lb1, (signed int *)&TripPosDetailsSt[TRIP_AVF_LBL_1].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_AVF_LBL_1].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_day_in_lb2, (signed int *)&TripPosDetailsSt[TRIP_AVF_VALUE_1].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_AVF_VALUE_1].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_day_in_lb3, (signed int *)&TripPosDetailsSt[TRIP_AVF_UNIT_1].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_AVF_UNIT_1].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_day_in_lb4, (signed int *)&TripPosDetailsSt[TRIP_AVF_LBL_2].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_AVF_LBL_2].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_day_in_lb5, (signed int *)&TripPosDetailsSt[TRIP_AVF_VALUE_2].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_AVF_VALUE_2].Y_Pos},
		{(lv_obj_t *)&guider_ui.screen_day_in_lb6, (signed int *)&TripPosDetailsSt[TRIP_AVF_UNIT_2].X_Pos, (signed int *)&TripPosDetailsSt[TRIP_AVF_UNIT_2].Y_Pos}};

	/***********************************************************************************************************************
	 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
	 ***********************************************************************************************************************/
	/*
	 * @brief: This variable is used to preserve the trip odo
	 * @Unit:
	 * @Resolution:
	 * @Range:
	 * @Applicability:
	 */

	uint32_t g_previous_trip_value_Night_u32 = 0;
	uint32_t g_previous_Trip_time_hour_Night_u8 = 0;
	uint32_t g_previous_Trip_time_Minute_Night_u8 = 0;

	uint32_t g_previous_trip_value_Day_u32 = 0;
	uint32_t g_previous_Trip_time_hour_Day_u8 = 0;
	uint32_t g_previous_Trip_time_Minute_Day_u8 = 0;

	extern uint32_t fl_Get_Current_TripA_Time_Foramt;

	uint32_t g_previous_TripA_AVSValue_Night_u32 = 0;
	uint32_t g_previous_TripA_AVFValue_Night_u32 = 0;
	uint32_t g_previous_TripA_AVFValue_Unit_Set_Night_u32 = 0;

	uint32_t g_previous_TripA_AVSValue_Day_u32 = 0;
	uint32_t g_previous_TripA_AVFValue_Day_u32 = 0;
	uint32_t g_previous_TripA_AVFValue_Unit_Set_Day_u32 = 0;

	uint8_t fl_Trip_time_hour_u8;

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
	void GUI_TripA_Init(void)
	{
		g_previous_trip_value_Night_u32 = 0;
	}

	void GUI_TripA_DeInit(void)
	{
		g_previous_trip_value_Night_u32 = 0;
	}

	void GUI_TripA_Activate(void)
	{
	}

	void GUI_TripA_DeActivate(void)
	{
	}

	/* Trip A Main Screen Handling */

	void GUI_TripA_Main_Screen_Night_Entry(void)
	{
		/* Clean Up the ealirer content */
		lv_obj_move_foreground(guider_ui.screen_Trip_blank);
		lv_obj_add_flag(guider_ui.screen_contscr_1, LV_OBJ_FLAG_HIDDEN);

		lv_obj_clear_flag(guider_ui.screen_trip_container, LV_OBJ_FLAG_HIDDEN);
		
		lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

		for (int i = 0; i <= 7; i++)
		{
			lv_obj_set_pos((lv_obj_t *)g_Trip_Time_Pos_Table[i].Label_Name->class_p, g_Trip_Time_Pos_Table[i].Label_X_Pos[0], g_Trip_Time_Pos_Table[i].Label_Y_Pos[0]);
		}

		lv_img_set_src(guider_ui.screen_Trip_blank, &_img_trip_A_icon_30x30);
		
		lv_label_set_text_fmt(guider_ui.screen_L2_unit, "");

		lv_img_set_src(guider_ui.screen_Sub_Con, &subbtn_night_24x24);

		lv_label_set_text(guider_ui.screen_trip_lbl1, "Trip");
		lv_label_set_text(guider_ui.screen_trip_unit_1, "km");
		lv_label_set_text(guider_ui.screen_trip_lbl_2, "Time");

		/* Modify the Characteristcis of L1 & L2 */
		lv_label_set_text_fmt(guider_ui.screen_trip_lbl1, "Trip");

		lv_label_set_text_fmt(guider_ui.screen_trip_val_1, "%d", g_previous_trip_value_Night_u32);
		lv_obj_set_style_text_color(guider_ui.screen_trip_val_1, lv_color_white(), 0);
		set_obj_opa_S(guider_ui.screen_trip_val_1, 0);

		lv_label_set_text_fmt(guider_ui.screen_trip_unit_1, "km");
		lv_obj_set_style_text_color(guider_ui.screen_trip_unit_1, lv_color_white(), 0);
		set_obj_opa_S(guider_ui.screen_trip_unit_1, 0);
		lv_label_set_text_fmt(guider_ui.screen_trip_lbl_2, "Time");

		lv_label_set_text_fmt(guider_ui.screen_trip_hh_lbl, "h");
		lv_obj_set_style_text_color(guider_ui.screen_trip_hh_lbl, lv_color_white(), 0);
		set_obj_opa_S(guider_ui.screen_trip_hh_lbl, 0);

		lv_label_set_text_fmt(guider_ui.screen_trip_mm_lbl, "m");
		lv_obj_set_style_text_color(guider_ui.screen_trip_mm_lbl, lv_color_white(), 0);
		set_obj_opa_S(guider_ui.screen_trip_mm_lbl, 0);

		lv_obj_add_flag(guider_ui.screen_trip_up_arrow, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_trip_down_arrow, LV_OBJ_FLAG_HIDDEN);

		lv_img_set_src(guider_ui.screen_Sub_Con, &subbtn_night_24x24);
		lv_obj_clear_flag(guider_ui.screen_Sub_Con, LV_OBJ_FLAG_HIDDEN);

		fl_Get_Current_TripA_Time_Foramt = GUI_Get_Time_Format();

		if (fl_Get_Current_TripA_Time_Foramt == CLOCK_12HR_FORMAT)
		{
			GUI_Main12hr_position();
			GUI_Intermediate12hr_position();
		}
		else
		{
			GUI_Main24hr_position();
			GUI_Intermediate24hr_position();
		}

		/* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
		g_previous_trip_value_Night_u32 = 0xFF;
		g_previous_Trip_time_hour_Night_u8 = 0xFF;
		g_previous_Trip_time_Minute_Night_u8 = 0xFF;
	}

	void GUI_TripA_Main_Screen_Night_Exit(void)
	{
		lv_obj_add_flag(guider_ui.screen_trip_container, LV_OBJ_FLAG_HIDDEN);
	}

	void GUI_TripA_Main_Screen_Night_During(void)
	{
		uint32_t fl_present_trip_value_Night_u32 = ODO_Get_TripOdometer(0);
		bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
		uint32_t fl_present_Trip_time_hour_Night_u8 = Swc_Trip_Timer_Get_Hour_value(0);
		uint32_t fl_present_Trip_time_Minute_Night_u8 = Swc_Trip_Timer_Get_Min_value(0);

		/*update the Trip odometer value only if there is a change*/
		if (fl_present_trip_value_Night_u32 == ODO_INVALID_STATE)
		{
			lv_label_set_text_fmt(guider_ui.screen_trip_val_1, "---.-");
		}
		else if ((g_previous_trip_value_Night_u32 != fl_present_trip_value_Night_u32))
		{
			g_previous_trip_value_Night_u32 = fl_present_trip_value_Night_u32;
			lv_label_set_text_fmt(guider_ui.screen_trip_val_1, "%d.%d", (g_previous_trip_value_Night_u32 / 10), (g_previous_trip_value_Night_u32 % 10));
		}
		else
		{
			/*Do nothing*/
		}

		/*update the Trip time value only if there is a change*/

		if (fl_Trip_Timer_St == TRUE)
		{

			if ((g_previous_Trip_time_hour_Night_u8 != fl_present_Trip_time_hour_Night_u8) ||
				(g_previous_Trip_time_Minute_Night_u8 != fl_present_Trip_time_Minute_Night_u8))
			{
				g_previous_Trip_time_hour_Night_u8 = fl_present_Trip_time_hour_Night_u8;
				g_previous_Trip_time_Minute_Night_u8 = fl_present_Trip_time_Minute_Night_u8;

				if (g_previous_Trip_time_hour_Night_u8 <= 9)
				{
					if (g_previous_Trip_time_Minute_Night_u8 <= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "0%d", g_previous_Trip_time_hour_Night_u8);
						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "0%d", g_previous_Trip_time_Minute_Night_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "0%d", g_previous_Trip_time_hour_Night_u8);
						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "%d", g_previous_Trip_time_Minute_Night_u8);
					}
				}
				else
				{
					if (g_previous_Trip_time_Minute_Night_u8 <= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "%d", g_previous_Trip_time_hour_Night_u8);
						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "0%d", g_previous_Trip_time_Minute_Night_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "%d", g_previous_Trip_time_hour_Night_u8);

						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "%d", g_previous_Trip_time_Minute_Night_u8);
					}
				}
				lv_label_set_text(guider_ui.screen_trip_hh_lbl, "h");
				lv_label_set_text(guider_ui.screen_trip_mm_lbl, "m");
			}
			else
			{
				/*Do Nothing*/
			}
		}
		else
		{
			g_previous_Trip_time_hour_Night_u8 = 0xffff;
			lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "--", g_previous_Trip_time_hour_Night_u8);
			lv_label_set_text_fmt(guider_ui.screen_trip_hh_lbl, "h");
			lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "--", g_previous_Trip_time_Minute_Night_u8);
			lv_label_set_text_fmt(guider_ui.screen_trip_mm_lbl, "m");
		}

		lv_img_set_src(guider_ui.screen_Sub_Con, &subbtn_night_24x24);
		lv_obj_clear_flag(guider_ui.screen_Sub_Con, LV_OBJ_FLAG_HIDDEN);
	}

	void GUI_TripA_Trip_Time_Screen_Entry(void)
	{
		lv_obj_move_foreground(guider_ui.screen_Trip_blank);
	
		lv_obj_clear_flag(guider_ui.screen_trip_spedo_cont, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_L1_unit, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_up_arr, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_dw_arr, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_trip_container, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_trip_up_arrow, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_trip_down_arrow, LV_OBJ_FLAG_HIDDEN);

		lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

		lv_obj_set_size(guider_ui.screen_L1_val, 50, 18);

		lv_img_set_src(guider_ui.screen_Trip_blank, &_img_trip_A_icon_30x30);
		lv_label_set_text(guider_ui.screen_trip_lbl1, "Trip");
		lv_label_set_text(guider_ui.screen_trip_unit_1, "km");

		for (int i = 0; i <= 7; i++)
		{
			lv_obj_set_pos((lv_obj_t *)g_Trip_Time_Pos_Table[i].Label_Name->class_p, g_Trip_Time_Pos_Table[i].Label_X_Pos[0], g_Trip_Time_Pos_Table[i].Label_Y_Pos[0]);
		}

		lv_img_set_src(guider_ui.screen_Sub_Con, &_Layer_0_9x9);

		lv_img_set_src(guider_ui.screen_trip_up_arrow, &new_trip_up_arrow);
		lv_img_set_src(guider_ui.screen_trip_down_arrow, &new_trip_down_arrow);

		lv_obj_clear_flag(guider_ui.screen_Sub_Con, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_imgKmph, LV_OBJ_FLAG_HIDDEN);

		fl_Get_Current_TripA_Time_Foramt = GUI_Get_Time_Format();

		if (fl_Get_Current_TripA_Time_Foramt == CLOCK_12HR_FORMAT)
		{
			GUI_Main12hr_position();
			GUI_Intermediate12hr_position();
		}
		else
		{
			GUI_Main24hr_position();
			GUI_Intermediate24hr_position();
		}
		/* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
		g_previous_trip_value_Night_u32 = 0xFF;
		g_previous_Trip_time_hour_Night_u8 = 0xFF;
		g_previous_Trip_time_Minute_Night_u8 = 0xFF;
	}

	void GUI_TripA_Trip_Time_Screen_Exit(void)
	{

		lv_obj_add_flag(guider_ui.screen_trip_container, LV_OBJ_FLAG_HIDDEN);

		lv_obj_add_flag(guider_ui.screen_trip_up_arrow, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_trip_down_arrow, LV_OBJ_FLAG_HIDDEN);
	}

	void GUI_TripA_Trip_Time_Screen_During(void)
	{

		uint32_t fl_present_TripA_Value_Night_u32 = ODO_Get_TripOdometer(0);
		bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
		uint8_t fl_present_Trip_time_hour_Night_u8 = Swc_Trip_Timer_Get_Hour_value(0);
		uint8_t fl_present_Trip_time_Minute_Night_u8 = Swc_Trip_Timer_Get_Min_value(0);

		if (fl_present_TripA_Value_Night_u32 == ODO_INVALID_STATE)
		{
			lv_label_set_text_fmt(guider_ui.screen_trip_val_1, "---.-");
			lv_obj_set_style_text_align(guider_ui.screen_L2_val, LV_TEXT_ALIGN_RIGHT, 0);
		}
		else if ((g_previous_trip_value_Night_u32 != fl_present_TripA_Value_Night_u32))
		{
			g_previous_trip_value_Night_u32 = fl_present_TripA_Value_Night_u32;

			lv_label_set_text_fmt(guider_ui.screen_trip_val_1, "%d.%d", (g_previous_trip_value_Night_u32 / 10), (g_previous_trip_value_Night_u32 % 10));
			lv_obj_set_style_text_align(guider_ui.screen_L2_val, LV_TEXT_ALIGN_RIGHT, 0);
		}
		else
		{
			/*Do nothing*/
		}

		lv_label_set_text(guider_ui.screen_trip_lbl_2, "Time");

		if (fl_Trip_Timer_St == TRUE)
		{
			if ((fl_present_Trip_time_hour_Night_u8 != g_previous_Trip_time_hour_Night_u8) ||
				(fl_present_Trip_time_Minute_Night_u8 != g_previous_Trip_time_Minute_Night_u8))
			{
				g_previous_Trip_time_hour_Night_u8 = fl_present_Trip_time_hour_Night_u8;
				g_previous_Trip_time_Minute_Night_u8 = fl_present_Trip_time_Minute_Night_u8;
				if (g_previous_Trip_time_hour_Night_u8 <= 9)
				{
					if (g_previous_Trip_time_Minute_Night_u8 <= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "0%d", g_previous_Trip_time_hour_Night_u8);
						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "0%d", g_previous_Trip_time_Minute_Night_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "0%d", g_previous_Trip_time_hour_Night_u8);
						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "%d", g_previous_Trip_time_Minute_Night_u8);
					}
				}
				else
				{
					if (g_previous_Trip_time_Minute_Night_u8 <= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "%d", g_previous_Trip_time_hour_Night_u8);
						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "0%d", g_previous_Trip_time_Minute_Night_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "%d", g_previous_Trip_time_hour_Night_u8);

						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "%d", g_previous_Trip_time_Minute_Night_u8);
					}
				}
				lv_label_set_text(guider_ui.screen_trip_hh_lbl, "h");
				lv_label_set_text(guider_ui.screen_trip_mm_lbl, "m");
			}
			else
			{
				/*Do Nothing*/
			}
		}
		else
		{
			g_previous_Trip_time_hour_Night_u8 = 0xffff;
			lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "--", g_previous_Trip_time_hour_Night_u8);
			lv_label_set_text_fmt(guider_ui.screen_trip_hh_lbl, "h");
			lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "--", g_previous_Trip_time_Minute_Night_u8);
			lv_label_set_text_fmt(guider_ui.screen_trip_mm_lbl, "m");
		}

		/* Chang Color For Trip If It is Pressed */
		switch (g_TripA_UpKeypressed_U8)
		{
		case Pressed_State:
			lv_img_set_src(guider_ui.screen_trip_up_arrow, &new_night_trip_up_arrow_pressed);
			g_TripA_UpKeypressed_U8 = 2;
			break;
		case UnPressed_State:
			lv_img_set_src(guider_ui.screen_trip_up_arrow, &new_trip_up_arrow);
			g_TripA_UpKeypressed_U8 = 0;
			break;
		default:
			g_TripA_UpKeypressed_U8 = 0;
			break;
		}

		/* Chang Color For Trip Btn If It is Pressed */

		switch (g_TripA_DownKeypressed_U8)
		{
		case Pressed_State:
			lv_img_set_src(guider_ui.screen_trip_down_arrow, &new_night_trip_down_arrow_pressed);
			g_TripA_DownKeypressed_U8 = 2;
			break;
		case UnPressed_State:
			lv_img_set_src(guider_ui.screen_trip_down_arrow, &new_trip_down_arrow);
			g_TripA_DownKeypressed_U8 = 0;
			break;
		default:
			g_TripA_DownKeypressed_U8 = 0;
			break;
		}
	}

	static uint32_t fl_TripA_AVFValue_u32 = 0;

	void set_AVF_Trip_A_Display_Value(uint32_t fl_displayed_AFE_Value)
	{
		fl_TripA_AVFValue_u32 = fl_displayed_AFE_Value;
	}

	void GUI_TripA_AVF_AVS_Screen_Entry(void)
	{
		lv_img_set_src(guider_ui.screen_Trip_blank, &_img_trip_A_icon_30x30);
		lv_obj_set_size(guider_ui.screen_L1_val, 50, 18);

		/* Hide Trip Main container */
        lv_obj_add_flag(guider_ui.screen_trip_container,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_contscr_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_trip_spedo_cont, LV_OBJ_FLAG_HIDDEN);

		lv_obj_clear_flag(guider_ui.screen_L2_unit, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_L1_unit, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_L1_val, LV_OBJ_FLAG_HIDDEN);
		lv_obj_move_foreground(guider_ui.screen_Trip_blank);

		lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
		set_obj_opa_S(guider_ui.screen_L2_val, 0);

		lv_label_set_text_fmt(guider_ui.screen_L2_lbl, "Av Fuel");
		lv_label_set_text(guider_ui.screen_L1_lbl, "Av Speed");
		lv_label_set_text(guider_ui.screen_L2_unit, "L/100km");
		lv_label_set_text(guider_ui.screen_L1_unit, "km/h");

		lv_obj_set_style_text_font(guider_ui.screen_L1_unit, &lv_font_FjallaOne_Regular_14, 0);
		lv_obj_set_style_text_font(guider_ui.screen_L2_unit, &lv_font_FjallaOne_Regular_14, 0);

		for (int i = 16; i <= 21; i++)
		{
			lv_obj_set_pos((lv_obj_t *)g_Trip_Time_Pos_Table[i].Label_Name->class_p, g_Trip_Time_Pos_Table[i].Label_X_Pos[0], g_Trip_Time_Pos_Table[i].Label_Y_Pos[0]);
		}

		fl_Get_Current_TripA_Time_Foramt = GUI_Get_Time_Format();

		if (fl_Get_Current_TripA_Time_Foramt == CLOCK_12HR_FORMAT)
		{
			GUI_Main12hr_position();
			GUI_Intermediate12hr_position();
		}
		else
		{
			GUI_Main24hr_position();
			GUI_Intermediate24hr_position();
		}

		/* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
		g_previous_TripA_AVSValue_Night_u32 = 0xFF;
		g_previous_TripA_AVFValue_Night_u32 = 0xFF;
		g_previous_TripA_AVFValue_Unit_Set_Night_u32 = 0xFF;
	}

	void GUI_TripA_AVF_AVS_Screen_Exit(void)
	{

		/* Hide AVF AVS Screen container */
		 lv_obj_add_flag(guider_ui.screen_contscr_1, LV_OBJ_FLAG_HIDDEN);
	}

	void GUI_TripA_AVF_AVS_Screen_During(void)
	{
		uint32_t fl_present_TripA_AVSValue_Night_u32 = Swc_Avereage_Speed_Get_value(0);
		uint32_t fl_present_TripA_AVFValue_Night_u32 = display_AFE(0);
		uint32_t fl_present_TripA_AVFValue_Unit_Set_Night_u32 = Fuel_Consumption_fn();
		bool fl_TripA_Av_Speed_Status_bl = Swc_Average_Speed_Get_Status();

		if ((g_previous_TripA_AVSValue_Night_u32 != fl_present_TripA_AVSValue_Night_u32))
		{
			g_previous_TripA_AVSValue_Night_u32 = fl_present_TripA_AVSValue_Night_u32;

			if (fl_TripA_Av_Speed_Status_bl == FALSE)
			{
				lv_label_set_text_fmt(guider_ui.screen_L1_val, "---");
			}
			else
			{
				lv_label_set_text_fmt(guider_ui.screen_L1_val, "%d", (g_previous_TripA_AVSValue_Night_u32));
			}
		}
		else
		{
			/*Do nothing*/
		}
		if ((g_previous_TripA_AVFValue_Night_u32 != fl_present_TripA_AVFValue_Night_u32) ||
			(g_previous_TripA_AVFValue_Unit_Set_Night_u32 != fl_present_TripA_AVFValue_Unit_Set_Night_u32))
		{

			g_previous_TripA_AVFValue_Night_u32 = fl_present_TripA_AVFValue_Night_u32;
			g_previous_TripA_AVFValue_Unit_Set_Night_u32 = fl_present_TripA_AVFValue_Unit_Set_Night_u32;

			if (g_previous_TripA_AVFValue_Night_u32 == TC_INVALID)
			{
				lv_label_set_text_fmt(guider_ui.screen_L2_val, "---.-");

				if (fl_present_TripA_AVFValue_Unit_Set_Night_u32 == Lper100km)
				{

					lv_label_set_text(guider_ui.screen_L2_unit, "L/100km");
				}
				else
				{

					lv_label_set_text(guider_ui.screen_L2_unit, "km/L");
				}
			}
			else
			{
				if (fl_present_TripA_AVFValue_Unit_Set_Night_u32 == Lper100km)
				{
					lv_label_set_text(guider_ui.screen_L2_unit, "L/100km");

					if (g_previous_TripA_AVFValue_Night_u32 == 0)
					{
						g_previous_TripA_AVFValue_Night_u32 = 0;
					}
					else
					{
						g_previous_TripA_AVFValue_Night_u32 = 10000 / g_previous_TripA_AVFValue_Night_u32;
					}

					/* Limit AVF value if it exceeds max limit */
					SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&g_previous_TripA_AVFValue_Night_u32);
				}
				else if (fl_present_TripA_AVFValue_Unit_Set_Night_u32 == KmperL)
				{
					lv_label_set_text(guider_ui.screen_L2_unit, "km/L");
				}
				else
				{
					/* do nothing*/
				}

				lv_label_set_text_fmt(guider_ui.screen_L2_val, "%d.%d", (g_previous_TripA_AVFValue_Night_u32 / 10), (g_previous_TripA_AVFValue_Night_u32 % 10));
			}
		}
		else
		{
			/*Do Nothing*/
		}
		lv_img_set_src(guider_ui.screen_Sub_Con, &_Layer_0_9x9);

		/* Chang Color For Trip If It is Pressed */
		switch (g_TripA_UpKeypressed_U8)
		{
		case Pressed_State:
			lv_img_set_src(guider_ui.screen_up_arr, &new_night_trip_up_arrow_pressed);
			g_TripA_UpKeypressed_U8 = 2;
			break;
		case UnPressed_State:
			lv_img_set_src(guider_ui.screen_up_arr, &new_trip_up_arrow);
			g_TripA_UpKeypressed_U8 = 0;
			break;
		default:
			g_TripA_UpKeypressed_U8 = 0;
			break;
		}

		/* Chang Color For Trip Btn If It is Pressed */

		switch (g_TripA_DownKeypressed_U8)
		{
		case Pressed_State:
			lv_img_set_src(guider_ui.screen_dw_arr, &new_night_trip_down_arrow_pressed);
			g_TripA_DownKeypressed_U8 = 2;
			break;
		case UnPressed_State:
			lv_img_set_src(guider_ui.screen_dw_arr, &new_trip_down_arrow);
			g_TripA_DownKeypressed_U8 = 0;
			break;
		default:
			g_TripA_DownKeypressed_U8 = 0;
			break;
		}
	}

	void TripA_Main_Day_Entry(void)
	{		
		
		lv_obj_clear_flag(guider_ui.screen_day_trip_con, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_Trip_up_arr, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_Trip_down_arr, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

		for (int i = 8; i <= 15; i++)
		{
			lv_obj_set_pos((lv_obj_t *)g_Trip_Time_Pos_Table[i].Label_Name->class_p, g_Trip_Time_Pos_Table[i].Label_X_Pos[0], g_Trip_Time_Pos_Table[i].Label_Y_Pos[0]);
		}

		lv_img_set_src(guider_ui.screen_Trip_blank, &tripA_day_icon);
		lv_obj_move_foreground(guider_ui.screen_Trip_blank);
		lv_label_set_text(guider_ui.screen_day_lbl3, "km");

		/* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
		g_previous_trip_value_Day_u32 = 0xFF;
		g_previous_Trip_time_hour_Day_u8 = 0xFF;
		g_previous_Trip_time_Minute_Day_u8 = 0xFF;
	}

	void TripA_Main_Day_During(void)
	{
		uint32_t fl_present_trip_value_Day_u32 = ODO_Get_TripOdometer(0);
		bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
		uint32_t fl_present_Trip_time_hour_Day_u8 = Swc_Trip_Timer_Get_Hour_value(0);
		uint32_t fl_present_Trip_time_Minute_Day_u8 = Swc_Trip_Timer_Get_Min_value(0);

		if (fl_present_trip_value_Day_u32 == ODO_INVALID_STATE)
		{
			lv_label_set_text_fmt(guider_ui.screen_day_lbl2, "---.-");
		}
		else if ((g_previous_trip_value_Day_u32 != fl_present_trip_value_Day_u32))
		{
			g_previous_trip_value_Day_u32 = fl_present_trip_value_Day_u32;
			lv_label_set_text_fmt(guider_ui.screen_day_lbl2, "%d.%d", (g_previous_trip_value_Day_u32 / 10), (g_previous_trip_value_Day_u32 % 10));
		}
		else
		{
			/*Do Nothing*/
		}

		if (fl_Trip_Timer_St == TRUE)
		{
			if ((g_previous_Trip_time_hour_Day_u8 != fl_present_Trip_time_hour_Day_u8) ||
				(g_previous_Trip_time_Minute_Day_u8 != fl_present_Trip_time_Minute_Day_u8))
			{
				g_previous_Trip_time_hour_Day_u8 = fl_present_Trip_time_hour_Day_u8;
				g_previous_Trip_time_Minute_Day_u8 = fl_present_Trip_time_Minute_Day_u8;

				if (g_previous_Trip_time_hour_Day_u8 <= 9)
				{
					if (g_previous_Trip_time_Minute_Day_u8 <= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "0%d", g_previous_Trip_time_hour_Day_u8);
						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "0%d", g_previous_Trip_time_Minute_Day_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "0%d", g_previous_Trip_time_hour_Day_u8);
						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "%d", g_previous_Trip_time_Minute_Day_u8);
					}
				}
				else
				{
					if (g_previous_Trip_time_Minute_Day_u8 <= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "%d", g_previous_Trip_time_hour_Day_u8);
						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "0%d", g_previous_Trip_time_Minute_Day_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "%d", g_previous_Trip_time_hour_Day_u8);

						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "%d", g_previous_Trip_time_Minute_Day_u8);
					}
				}
				lv_label_set_text(guider_ui.screen_day_lbl_6, "h");
				lv_label_set_text(guider_ui.screen_day_lbl_8, "m");
			}
			else
			{
				/*Do Nothing*/
			}
		}
		else
		{
			g_previous_Trip_time_hour_Day_u8 = 0xffff;
			lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "--", g_previous_Trip_time_hour_Day_u8);
			lv_label_set_text_fmt(guider_ui.screen_day_lbl_6, "h", g_previous_Trip_time_hour_Day_u8);
			lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "--", g_previous_Trip_time_Minute_Day_u8);
			lv_label_set_text_fmt(guider_ui.screen_day_lbl_8, "m", g_previous_Trip_time_Minute_Day_u8);
		}
	}
	void TripA_Main_Day_Exit(void)
	{
		lv_obj_add_flag(guider_ui.screen_day_trip_con, LV_OBJ_FLAG_HIDDEN);
	}

	void TripA_Time_Day_Entry(void)
	{
		/* Enable trip container and its objects */
		lv_obj_clear_flag(guider_ui.screen_day_trip_con, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_day_Trip_up_arr, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_day_Trip_down_arr, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

		for (int i = 8; i <= 15; i++)
		{
			lv_obj_set_pos((lv_obj_t *)g_Trip_Time_Pos_Table[i].Label_Name->class_p, g_Trip_Time_Pos_Table[i].Label_X_Pos[0], g_Trip_Time_Pos_Table[i].Label_Y_Pos[0]);
		}

		lv_img_set_src(guider_ui.screen_Trip_blank, &tripA_day_icon);
		lv_obj_move_foreground(guider_ui.screen_Trip_blank);

		lv_label_set_text(guider_ui.screen_day_lbl3, "km");

		/* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
		g_previous_trip_value_Day_u32 = 0xFF;
		g_previous_Trip_time_hour_Day_u8 = 0xFF;
		g_previous_Trip_time_Minute_Day_u8 = 0xFF;
	}

	void GUI_TripA_Time_Day_During(void)
	{
		uint8_t fl_Get_Current_TripA_Time_Foramt = 0;
		uint32_t fl_present_TripA_Value_Day_u32 = ODO_Get_TripOdometer(0);
		bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
		uint8_t fl_present_Trip_time_hour_Day_u8 = Swc_Trip_Timer_Get_Hour_value(0);
		uint8_t fl_present_Trip_time_Minute_Day_u8 = Swc_Trip_Timer_Get_Min_value(0);

		if (fl_present_TripA_Value_Day_u32 == ODO_INVALID_STATE)
		{
			lv_label_set_text_fmt(guider_ui.screen_day_lbl2, "---.-");
		}
		else if ((g_previous_trip_value_Day_u32 != fl_present_TripA_Value_Day_u32))
		{
			g_previous_trip_value_Day_u32 = fl_present_TripA_Value_Day_u32;
			lv_label_set_text_fmt(guider_ui.screen_day_lbl2, "%d.%d", (g_previous_trip_value_Day_u32 / 10), (g_previous_trip_value_Day_u32 % 10));
		}

		if (fl_Trip_Timer_St == TRUE)
		{
			if ((g_previous_Trip_time_hour_Day_u8 |= fl_present_Trip_time_hour_Day_u8) ||
				(g_previous_Trip_time_Minute_Day_u8 != fl_present_Trip_time_Minute_Day_u8))
			{
				g_previous_Trip_time_hour_Day_u8 = fl_present_Trip_time_hour_Day_u8;
				g_previous_Trip_time_Minute_Day_u8 = fl_present_Trip_time_Minute_Day_u8;

				if (g_previous_Trip_time_hour_Day_u8 <= 9)
				{
					if (g_previous_Trip_time_Minute_Day_u8 <= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "0%d", g_previous_Trip_time_hour_Day_u8);
						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "0%d", g_previous_Trip_time_Minute_Day_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "0%d", g_previous_Trip_time_hour_Day_u8);
						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "%d", g_previous_Trip_time_Minute_Day_u8);
					}
				}
				else
				{
					if (g_previous_Trip_time_Minute_Day_u8 <= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "%d", g_previous_Trip_time_hour_Day_u8);
						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "0%d", g_previous_Trip_time_Minute_Day_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "%d", g_previous_Trip_time_hour_Day_u8);

						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "%d", g_previous_Trip_time_Minute_Day_u8);
					}
				}
				lv_label_set_text(guider_ui.screen_day_lbl_6, "h");
				lv_label_set_text(guider_ui.screen_day_lbl_8, "m");
			}

			else
			{
				/*Do Nothing*/
			}
		}
		else
		{
			g_previous_Trip_time_hour_Day_u8 = 0xffff;
			lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "--", g_previous_Trip_time_hour_Day_u8);
			lv_label_set_text_fmt(guider_ui.screen_day_lbl_6, "h");
			lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "--", g_previous_Trip_time_Minute_Day_u8);
			lv_label_set_text_fmt(guider_ui.screen_day_lbl_8, "m");
		}

		/* Chang Color For Trip If It is Pressed */
		switch (g_TripA_UpKeypressed_U8)
		{
		case Pressed_State:
			lv_img_set_src(guider_ui.screen_day_Trip_up_arr, &new_day_trip_up_arrow_pressed);
			g_TripA_UpKeypressed_U8 = 2;
			break;
		case UnPressed_State:
			lv_img_set_src(guider_ui.screen_day_Trip_up_arr, &new_day_trip_up_arrow_normal);
			g_TripA_UpKeypressed_U8 = 0;
			break;
		default:
			g_TripA_UpKeypressed_U8 = 0;
			break;
		}

		/* Chang Color For Trip Btn If It is Pressed */

		switch (g_TripA_DownKeypressed_U8)
		{
		case Pressed_State:
			lv_img_set_src(guider_ui.screen_day_Trip_down_arr, &new_day_trip_down_arrow_pressed);
			g_TripA_DownKeypressed_U8 = 2;
			break;
		case UnPressed_State:
			lv_img_set_src(guider_ui.screen_day_Trip_down_arr, &new_day_trip_down_arrow_normal);
			g_TripA_DownKeypressed_U8 = 0;
			break;
		default:
			g_TripA_DownKeypressed_U8 = 0;
			break;
		}
	}

	void TripA_Time_Day_Exit(void)
	{
		lv_obj_add_flag(guider_ui.screen_day_trip_con, LV_OBJ_FLAG_HIDDEN);

		lv_obj_add_flag(guider_ui.screen_day_Trip_up_arr, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_Trip_down_arr, LV_OBJ_FLAG_HIDDEN);

		g_previous_trip_value_Day_u32 = 0;
		g_previous_Trip_time_hour_Day_u8 = 0;
		g_previous_Trip_time_Minute_Day_u8 = 0;
	}

	signed int TripA_AVF_Day_x_pos[6] = {5, 72, 125, -15, 11, 116};
	signed int TripA_AVF_Day_y_pos[6] = {12, 9, 14, 42, 38, 41};

	void TripA_AVF_Day_Entry(void)
	{
		lv_obj_set_size(guider_ui.screen_day_in_lb2, 50, 18);
		// lv_obj_clear_flag(guider_ui.screen_dat_inter_con, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_day_inter_con2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
		lv_label_set_text(guider_ui.screen_day_in_lb1, "Av Speed");
		lv_label_set_text(guider_ui.screen_day_in_lb4, "Av Fuel");
		lv_label_set_text(guider_ui.screen_day_in_lb3, "km/h");
		lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

		lv_img_set_src(guider_ui.screen_Trip_blank, &tripA_day_icon);
		lv_obj_move_foreground(guider_ui.screen_Trip_blank);

		lv_obj_clear_flag(guider_ui.screen_day_in_arr1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_day_in_arr2, LV_OBJ_FLAG_HIDDEN);
		// lv_obj_add_flag(guider_ui.screen_kmimage, LV_OBJ_FLAG_HIDDEN);

		lv_img_set_src(guider_ui.screen_day_in_arr2, &new_day_trip_down_arrow_normal);
		lv_img_set_src(guider_ui.screen_day_in_arr1, &new_day_trip_up_arrow_normal);

		lv_obj_set_style_text_font(guider_ui.screen_day_in_lb3, &lv_font_FjallaOne_Regular_14, 0);
		lv_obj_set_style_text_font(guider_ui.screen_day_in_lb6, &lv_font_FjallaOne_Regular_14, 0);

		for (int i = 22; i <= 27; i++)
		{
			lv_obj_set_pos((lv_obj_t *)g_Trip_Time_Pos_Table[i].Label_Name->class_p, g_Trip_Time_Pos_Table[i].Label_X_Pos[0], g_Trip_Time_Pos_Table[i].Label_Y_Pos[0]);
		}

		/* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
		g_previous_TripA_AVSValue_Day_u32 = 0xFF;
		g_previous_TripA_AVFValue_Day_u32 = 0xFF;
		g_previous_TripA_AVFValue_Unit_Set_Day_u32 = 0xFF;
	}
	void TripA_AVF_Day_During(void)
	{

		uint32_t fl_present_TripA_AVSValue_Day_u32 = Swc_Avereage_Speed_Get_value(0);
		uint32_t fl_present_TripA_AVFValue_Day_u32 = display_AFE(0);
		uint32_t fl_present_TripA_AVFValue_Unit_Set_Day_u32 = Fuel_Consumption_fn();
		bool fl_TripA_Av_Speed_Status_bl = Swc_Average_Speed_Get_Status();

		if ((g_previous_TripA_AVSValue_Day_u32 != fl_present_TripA_AVSValue_Day_u32))
		{
			g_previous_TripA_AVSValue_Day_u32 = fl_present_TripA_AVSValue_Day_u32;

			if (fl_TripA_Av_Speed_Status_bl == FALSE)
			{
				lv_label_set_text_fmt(guider_ui.screen_day_in_lb2, "---");
			}
			else
			{
				lv_label_set_text_fmt(guider_ui.screen_day_in_lb2, "%d", (g_previous_TripA_AVSValue_Day_u32));
			}
		}
		else
		{
			/*Do Nothing*/
		}

		if ((g_previous_TripA_AVFValue_Day_u32 != fl_present_TripA_AVFValue_Day_u32) ||
			(g_previous_TripA_AVFValue_Unit_Set_Day_u32 != fl_present_TripA_AVFValue_Unit_Set_Day_u32))
		{
			g_previous_TripA_AVFValue_Day_u32 = fl_present_TripA_AVFValue_Day_u32;
			g_previous_TripA_AVFValue_Unit_Set_Day_u32 = fl_present_TripA_AVFValue_Unit_Set_Day_u32;

			if (g_previous_TripA_AVFValue_Day_u32 == TC_INVALID)
			{
				lv_label_set_text_fmt(guider_ui.screen_day_in_lb5, "---.-");

				if (g_previous_TripA_AVFValue_Unit_Set_Day_u32 == Lper100km)
				{

					lv_label_set_text(guider_ui.screen_day_in_lb6, "L/100km");
				}
				else
				{

					lv_label_set_text(guider_ui.screen_day_in_lb6, "km/L");
				}
			}
			else
			{
				if (g_previous_TripA_AVFValue_Unit_Set_Day_u32 == Lper100km)
				{
					lv_label_set_text(guider_ui.screen_day_in_lb6, "L/100km");
					if (g_previous_TripA_AVFValue_Day_u32 == 0)
					{
						g_previous_TripA_AVFValue_Day_u32 = 0;
					}
					else
					{
						g_previous_TripA_AVFValue_Day_u32 = 10000 / g_previous_TripA_AVFValue_Day_u32;
					}

					/* Limit AVF value if it exceeds max limit */
					SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&g_previous_TripA_AVFValue_Day_u32);
				}
				else if (g_previous_TripA_AVFValue_Unit_Set_Day_u32 == KmperL)
				{
					lv_label_set_text(guider_ui.screen_day_in_lb6, "km/L");
				}
				else
				{
					/* do nothing*/
				}

				lv_label_set_text_fmt(guider_ui.screen_day_in_lb5, "%d.%d", (g_previous_TripA_AVFValue_Day_u32 / 10), (g_previous_TripA_AVFValue_Day_u32 % 10));
			}
		}
		else
		{
			/*Do Nothing*/
		}

		/* Chang Color For Trip If It is Pressed */
		switch (g_TripA_UpKeypressed_U8)
		{
		case Pressed_State:
			lv_img_set_src(guider_ui.screen_day_in_arr1, &new_day_trip_up_arrow_pressed);
			g_TripA_UpKeypressed_U8 = 2;
			break;
		case UnPressed_State:
			lv_img_set_src(guider_ui.screen_day_in_arr1, &new_day_trip_up_arrow_normal);
			g_TripA_UpKeypressed_U8 = 0;
			break;
		default:
			g_TripA_UpKeypressed_U8 = 0;
			break;
		}

		/* Chang Color For Trip Btn If It is Pressed */

		switch (g_TripA_DownKeypressed_U8)
		{
		case Pressed_State:
			lv_img_set_src(guider_ui.screen_day_in_arr2, &new_day_trip_down_arrow_pressed);
			g_TripA_DownKeypressed_U8 = 2;
			break;
		case UnPressed_State:
			lv_img_set_src(guider_ui.screen_day_in_arr2, &new_day_trip_down_arrow_normal);
			g_TripA_DownKeypressed_U8 = 0;
			break;
		default:
			g_TripA_DownKeypressed_U8 = 0;
			break;
		}		
	}
	void TripA_AVF_Day_Exit(void)
	{
		lv_obj_add_flag(guider_ui.screen_day_inter_con2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_in_arr1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_in_arr2, LV_OBJ_FLAG_HIDDEN);
	}

	uint8_t TripA_Button_UpEvent(void)
	{
		g_TripA_UpKeypressed_U8 = Pressed_State;
		return 0;
	}

	uint8_t TripA_Button_DownEvent(void)
	{
		g_TripA_DownKeypressed_U8 = Pressed_State;
		return 0;
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
