/* @file FILE NAME */
#ifndef HMI_TRIPB_C
#define HMI_TRIPB_C

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
	uint32_t g_previous_TripB_value_Night_u32 = 0;
	uint32_t g_previous_TripB_value_Day_u32 = 0;

	uint32_t g_previous_TripB_time_hour_Night_u8 = 0;
	uint32_t g_previous_TripB_time_Minute_Night_u8 = 0;

	uint32_t g_previous_TripB_time_hour_Day_u8 = 0;
	uint32_t g_previous_TripB_time_Minute_Day_u8 = 0;

	uint32_t g_previous_TripB_AVSValue_Night_u32 = 0;
	uint32_t g_previous_TripB_AVFValue_Night_u32 = 0;
	uint32_t g_previous_TripB_AVFValue_Unit_Set_Night_u32 = 0;

	uint32_t g_previous_TripB_AVSValue_Day_u32 = 0;
	uint32_t g_previous_TripB_AVFValue_Day_u32 = 0;
	uint32_t g_previous_TripB_AVFValue_Unit_Set_Day_u32 = 0;

	static uint32_t fl_TripB_AVFValue_u32 = 0;

	uint32_t fl_Get_Current_TripB_Time_Foramt;

	uint8_t fl_TripB_time_hour_u8;

	uint8_t g_TripB_UpKeypressed_U8 = 0 ;
	uint8_t g_TripB_DownKeypressed_U8 = 0 ;

	#define Pressed_State    1
	#define UnPressed_State  2 

extern g_Trip_Time_Pos g_Trip_Time_Pos_Table[16];

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
	void GUI_TripB_Init(void)
	{
		g_previous_TripB_value_Night_u32 = 0;
	}

	void GUI_TripB_DeInit(void)
	{
		g_previous_TripB_value_Night_u32 = 0;
	}

	void GUI_TripB_Init_Day(void)
	{
		g_previous_TripB_value_Day_u32 = 0;
	}

	void GUI_TripB_DeInit_Day(void)
	{
		g_previous_TripB_value_Day_u32 = 0;
	}

	void GUI_TripB_Activate(void)
	{
	}

	void GUI_TripB_DeActivate(void)
	{
	}


void GUI_TripB_Main_Screen_Night_Entry(void)
{

	lv_obj_add_flag(guider_ui.screen_contscr_1,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_trip_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_trip_up_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_trip_down_arrow, LV_OBJ_FLAG_HIDDEN);
	
	lv_img_set_src(guider_ui.screen_Sub_Con,&subbtn_night_24x24);
	lv_obj_clear_flag(guider_ui.screen_Sub_Con,LV_OBJ_FLAG_HIDDEN);

	for (int i =0 ; i<=7; i++)
	{
		lv_obj_set_pos((lv_obj_t*)g_Trip_Time_Pos_Table[i].Label_Name->class_p,g_Trip_Time_Pos_Table[i].Label_X_Pos[0],g_Trip_Time_Pos_Table[i].Label_Y_Pos[0]);
	}

	fl_Get_Current_TripB_Time_Foramt = GUI_Get_Time_Format();

	if (fl_Get_Current_TripB_Time_Foramt == CLOCK_12HR_FORMAT)
	{
		GUI_Main12hr_position();
		GUI_Intermediate12hr_position();
	}
	else
	{
		GUI_Main24hr_position();
		GUI_Intermediate24hr_position();
	}

	lv_label_set_text(guider_ui.screen_trip_lbl1, "Trip");
	lv_label_set_text(guider_ui.screen_trip_unit_1, "km");
	lv_label_set_text(guider_ui.screen_trip_lbl_2, "Time");

	lv_img_set_src(guider_ui.screen_Trip_blank, &_img_trip_B_icon_30x30);
	set_obj_opa(guider_ui.screen_Trip_blank, 255);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
	lv_obj_move_foreground(guider_ui.screen_Trip_blank);

	/* hide Up and down arrow , No need to show arrows in Trip B Main screen*/
	lv_obj_add_flag(guider_ui.screen_up_arr, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_dw_arr, LV_OBJ_FLAG_HIDDEN);

	/* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
	g_previous_TripB_value_Night_u32 = 0xFF;
	g_previous_TripB_time_hour_Night_u8 = 0XFF; 
	g_previous_TripB_time_Minute_Night_u8 = 0xFF;
}

void GUI_TripB_Main_Screen_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.screen_trip_container,LV_OBJ_FLAG_HIDDEN);

}

	void GUI_TripB_Main_Screen_Night_During(void)
	{

		uint32_t fl_present_trip_value_Night_u32 = ODO_Get_TripOdometer(1);
		bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
		uint32_t fl_present_Trip_time_hour_Night_u8 = Swc_Trip_Timer_Get_Hour_value(1);
		uint32_t fl_present_Trip_time_Minute_Night_u8 = Swc_Trip_Timer_Get_Min_value(1);

		/*update the Trip odometer value only if there is a change*/
		if( fl_present_trip_value_Night_u32 == ODO_INVALID_STATE)
		{
			lv_label_set_text_fmt(guider_ui.screen_trip_val_1, "---.-");
		}
		else if ((g_previous_TripB_value_Night_u32 != fl_present_trip_value_Night_u32))
		{
			g_previous_TripB_value_Night_u32 = fl_present_trip_value_Night_u32;
			lv_label_set_text_fmt(guider_ui.screen_trip_val_1, "%d.%d", (g_previous_TripB_value_Night_u32 / 10), (g_previous_TripB_value_Night_u32 % 10));
		}
		else
		{
			/*Do nothing*/
		}

		/*update the Trip time value only if there is a change*/
		if (fl_Trip_Timer_St == TRUE)
		{
			if ((g_previous_TripB_time_hour_Night_u8 != fl_present_Trip_time_hour_Night_u8) ||
				(g_previous_TripB_time_Minute_Night_u8 != fl_present_Trip_time_Minute_Night_u8))
			{

				g_previous_TripB_time_hour_Night_u8 = fl_present_Trip_time_hour_Night_u8;
				g_previous_TripB_time_Minute_Night_u8 = fl_present_Trip_time_Minute_Night_u8;

				if (g_previous_TripB_time_hour_Night_u8<= 9)
				{
					if (g_previous_TripB_time_Minute_Night_u8<= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "0%d", g_previous_TripB_time_hour_Night_u8);
						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "0%d", g_previous_TripB_time_Minute_Night_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "0%d", g_previous_TripB_time_hour_Night_u8);
						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "%d", g_previous_TripB_time_Minute_Night_u8);
					}
				}
				else
				{
					if (g_previous_TripB_time_Minute_Night_u8<= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "%d", g_previous_TripB_time_hour_Night_u8);
						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "0%d", g_previous_TripB_time_Minute_Night_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "%d", g_previous_TripB_time_hour_Night_u8);
						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "%d", g_previous_TripB_time_Minute_Night_u8);
					}
				}
				lv_label_set_text(guider_ui.screen_trip_hh_lbl, "h");
				lv_label_set_text(guider_ui.screen_trip_mm_lbl, "m");
			}
			else
			{
				/* do nothing */
			}
		}
		else
		{
			/* Make Data change as invalid state doesn't change value*/
			g_previous_TripB_time_hour_Night_u8 = 0xffff;

			lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "--", g_previous_TripB_time_hour_Night_u8);
			lv_label_set_text_fmt(guider_ui.screen_trip_hh_lbl, "h");
			lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "--", g_previous_TripB_time_Minute_Night_u8);
			lv_label_set_text(guider_ui.screen_trip_mm_lbl, "m");
		}


		lv_label_set_text_fmt(guider_ui.screen_L2_unit, "");

	}



void GUI_TripB_Trip_Time_Screen_Night_Entry(void)
{
	lv_obj_set_size(guider_ui.screen_L1_val,50,18);
	lv_img_set_src(guider_ui.screen_Trip_blank, &_img_trip_B_icon_30x30);
	lv_obj_move_foreground(guider_ui.screen_Trip_blank);
	
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

	for (int i =0 ; i<=7; i++)
	{
		lv_obj_set_pos((lv_obj_t*)g_Trip_Time_Pos_Table[i].Label_Name->class_p,g_Trip_Time_Pos_Table[i].Label_X_Pos[0],g_Trip_Time_Pos_Table[i].Label_Y_Pos[0]);
	}
	
	lv_obj_clear_flag(guider_ui.screen_trip_container,LV_OBJ_FLAG_HIDDEN);		
	lv_obj_clear_flag(guider_ui.screen_trip_up_arrow,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_trip_down_arrow,LV_OBJ_FLAG_HIDDEN);

	fl_Get_Current_TripB_Time_Foramt = GUI_Get_Time_Format();

	if (fl_Get_Current_TripB_Time_Foramt == CLOCK_12HR_FORMAT)
	{
		GUI_Main12hr_position();
		GUI_Intermediate12hr_position();
	}
	else
	{
		GUI_Main24hr_position();
		GUI_Intermediate24hr_position();
	}

	lv_label_set_text(guider_ui.screen_trip_lbl1, "Trip");
	lv_label_set_text(guider_ui.screen_trip_unit_1, "km");
	lv_label_set_text(guider_ui.screen_trip_lbl_2, "Time");

	lv_img_set_src(guider_ui.screen_trip_up_arrow, &new_trip_up_arrow);
	lv_img_set_src(guider_ui.screen_trip_down_arrow, &new_trip_down_arrow);

	/* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
	g_previous_TripB_value_Night_u32 = 0xFF;
	g_previous_TripB_time_hour_Night_u8 = 0XFF; 
	g_previous_TripB_time_Minute_Night_u8 = 0xFF;

}

void GUI_TripB_Trip_Time_Screen_Night_Exit(void)
{

    lv_obj_add_flag(guider_ui.screen_trip_container,LV_OBJ_FLAG_HIDDEN);   

	lv_obj_add_flag(guider_ui.screen_trip_up_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_trip_down_arrow, LV_OBJ_FLAG_HIDDEN);
}

	void GUI_TripB_Trip_Time_Screen_Night_During(void)
	{
	

		uint32_t fl_present_trip_value_Night_u32 = ODO_Get_TripOdometer(1);
		bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
		uint32_t fl_present_Trip_time_hour_Night_u8 = Swc_Trip_Timer_Get_Hour_value(1);
		uint32_t fl_present_Trip_time_Minute_Night_u8 = Swc_Trip_Timer_Get_Min_value(1);

		/*update the Trip odometer value only if there is a change*/
		if( fl_present_trip_value_Night_u32 == ODO_INVALID_STATE)
		{
			lv_label_set_text_fmt(guider_ui.screen_trip_val_1, "---.-");
			
		}
		else if ((g_previous_TripB_value_Night_u32 != fl_present_trip_value_Night_u32))
		{
			g_previous_TripB_value_Night_u32 = fl_present_trip_value_Night_u32;
			lv_label_set_text_fmt(guider_ui.screen_trip_val_1, "%d.%d", (g_previous_TripB_value_Night_u32 / 10), (g_previous_TripB_value_Night_u32 % 10));
		}
		else
		{
			/*Do nothing*/
		}

		/*update the Trip time value only if there is a change*/
		if (fl_Trip_Timer_St == TRUE)
		{
			if ((g_previous_TripB_time_hour_Night_u8 != fl_present_Trip_time_hour_Night_u8) ||
				(g_previous_TripB_time_Minute_Night_u8 != fl_present_Trip_time_Minute_Night_u8))
			{

				g_previous_TripB_time_hour_Night_u8 = fl_present_Trip_time_hour_Night_u8;
				g_previous_TripB_time_Minute_Night_u8 = fl_present_Trip_time_Minute_Night_u8;


				if (g_previous_TripB_time_hour_Night_u8 <= 9)
				{
					if (g_previous_TripB_time_Minute_Night_u8 <= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "0%d", g_previous_TripB_time_hour_Night_u8);
						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "0%d", g_previous_TripB_time_Minute_Night_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "0%d", g_previous_TripB_time_hour_Night_u8);
						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "%d", g_previous_TripB_time_Minute_Night_u8);
					}
				}
				else
				{
					if (g_previous_TripB_time_Minute_Night_u8 <= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "%d", g_previous_TripB_time_hour_Night_u8);
						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "0%d", g_previous_TripB_time_Minute_Night_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "%d", g_previous_TripB_time_hour_Night_u8);
						lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "%d", g_previous_TripB_time_Minute_Night_u8);
					}
				}
				lv_label_set_text(guider_ui.screen_trip_hh_lbl, "h");
				lv_label_set_text(guider_ui.screen_trip_mm_lbl, "m");
			}
		}
		else
		{
			/* Make Data change as invalid state doesn't change value*/
			g_previous_TripB_time_hour_Night_u8 = 0xFFFF;
			lv_label_set_text_fmt(guider_ui.screen_trip_hr_lbl, "--", g_previous_TripB_time_hour_Night_u8);
			lv_label_set_text_fmt(guider_ui.screen_trip_hh_lbl, "h", g_previous_TripB_time_hour_Night_u8);
			lv_label_set_text_fmt(guider_ui.screen_trip_mi_lbl, "--", g_previous_TripB_time_Minute_Night_u8);
			lv_label_set_text(guider_ui.screen_trip_mm_lbl, "m");
		}


			lv_img_set_src(guider_ui.screen_Sub_Con, &_Layer_0_9x9);	

		/* Chang Color For Trip If It is Pressed */

		switch (g_TripB_UpKeypressed_U8)
		{
			case Pressed_State:
				lv_img_set_src(guider_ui.screen_trip_up_arrow,&new_night_trip_up_arrow_pressed);
				g_TripB_UpKeypressed_U8 = 2;
				break;
			case UnPressed_State:
				lv_img_set_src(guider_ui.screen_trip_up_arrow,&new_trip_up_arrow);
				g_TripB_UpKeypressed_U8 = 0;
				break;
			default:
				g_TripB_UpKeypressed_U8 = 0;
				break;
		}

		/* Chang Color For Trip Btn If It is Pressed */

		switch (g_TripB_DownKeypressed_U8)
		{
			case Pressed_State:
				lv_img_set_src(guider_ui.screen_trip_down_arrow, &new_night_trip_down_arrow_pressed);
				g_TripB_DownKeypressed_U8 = 2;
				break;
			case UnPressed_State:
				lv_img_set_src(guider_ui.screen_trip_down_arrow, &new_trip_down_arrow);
				g_TripB_DownKeypressed_U8 = 0;
				break;
			default:
				g_TripB_DownKeypressed_U8 = 0;
				break;
		}
	}

	void GUI_TripB_AVF_AVS_Screen_Night_Entry(void)
	{
		lv_img_set_src(guider_ui.screen_Trip_blank, &_img_trip_B_icon_30x30);
		set_obj_opa(guider_ui.screen_Trip_blank, 255);
		
		lv_obj_set_size(guider_ui.screen_L1_val, 50, 18);

		for (int i = 16; i <= 21; i++)
		{
			lv_obj_set_pos((lv_obj_t*)g_Trip_Time_Pos_Table[i].Label_Name->class_p, g_Trip_Time_Pos_Table[i].Label_X_Pos[0], g_Trip_Time_Pos_Table[i].Label_Y_Pos[0]);
		}
	
		lv_obj_clear_flag(guider_ui.screen_contscr_1,LV_OBJ_FLAG_HIDDEN);

		lv_obj_clear_flag(guider_ui.screen_L2_unit, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_L1_unit, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_L1_val, LV_OBJ_FLAG_HIDDEN);

		lv_obj_move_foreground(guider_ui.screen_Trip_blank);

		lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

		set_obj_opa_S(guider_ui.screen_L2_val, 0);

		lv_obj_clear_flag(guider_ui.screen_up_arr, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_dw_arr, LV_OBJ_FLAG_HIDDEN);
	
		lv_obj_add_flag(guider_ui.screen_Sub_Con,LV_OBJ_FLAG_HIDDEN);

    	lv_label_set_text_fmt(guider_ui.screen_L2_lbl,"Av Fuel");
    	lv_label_set_text(guider_ui.screen_L1_lbl, "Av Speed");
    	lv_label_set_text(guider_ui.screen_L2_unit, "L/100km");
    	lv_label_set_text(guider_ui.screen_L1_unit, "km/h");

		fl_Get_Current_TripB_Time_Foramt = GUI_Get_Time_Format();

		if (fl_Get_Current_TripB_Time_Foramt == CLOCK_12HR_FORMAT)
		{
			GUI_Main12hr_position();
			GUI_Intermediate12hr_position();
		}
		else
		{
			GUI_Main24hr_position();
			GUI_Intermediate24hr_position();
		}

		lv_obj_set_style_text_font(guider_ui.screen_L1_unit, &lv_font_FjallaOne_Regular_14, 0);
		lv_obj_set_style_text_font(guider_ui.screen_L2_unit, &lv_font_FjallaOne_Regular_14, 0);

		lv_img_set_src(guider_ui.screen_Trip_blank, &_img_trip_B_icon_30x30);
		lv_img_set_src(guider_ui.screen_trip_up_arrow, &_day_up_arrow_20x11);
		lv_img_set_src(guider_ui.screen_trip_down_arrow, &_day_down_arrow_20x11);
		lv_img_set_src(guider_ui.screen_Sub_Con, &_Layer_0_9x9);
		/* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
		g_previous_TripB_AVSValue_Night_u32 = 0xFF;
		g_previous_TripB_AVFValue_Night_u32	= 0xFF;
		g_previous_TripB_AVFValue_Unit_Set_Night_u32 = 0xFF;

}

void GUI_TripB_AVF_AVS_Screen_Night_Exit(void)
{

	lv_obj_add_flag(guider_ui.screen_contscr_1,LV_OBJ_FLAG_HIDDEN);
   
}

	void GUI_TripB_AVF_AVS_Screen_Night_During(void)
	{
		uint32_t fl_TripB_AVFValue_u32;
		bool fl_TripA_Av_Speed_Status_bl = Swc_Average_Speed_Get_Status();
		uint32_t fl_present_TripB_AVSValue_Night_u32 = Swc_Avereage_Speed_Get_value(1);
		uint32_t fl_present_TripB_AVFValue_Night_u32 = display_AFE(1);
		uint32_t fl_present_TripB_AVFValue_Unit_Set_Night_u32 = Fuel_Consumption_fn();

		if ((g_previous_TripB_AVSValue_Night_u32 != fl_present_TripB_AVSValue_Night_u32))
		{
			g_previous_TripB_AVSValue_Night_u32 = fl_present_TripB_AVSValue_Night_u32;
		
			if (fl_TripA_Av_Speed_Status_bl == FALSE)
			{
				lv_label_set_text_fmt(guider_ui.screen_L1_val, "---");
			}
			
			else
			{
				lv_label_set_text_fmt(guider_ui.screen_L1_val, "%d", (g_previous_TripB_AVSValue_Night_u32));
			}
		}

		if ((g_previous_TripB_AVFValue_Night_u32 != fl_present_TripB_AVFValue_Night_u32) ||
			(g_previous_TripB_AVFValue_Unit_Set_Night_u32 != fl_present_TripB_AVFValue_Unit_Set_Night_u32))
		{
			g_previous_TripB_AVFValue_Night_u32 = fl_present_TripB_AVFValue_Night_u32;
			g_previous_TripB_AVFValue_Unit_Set_Night_u32 = fl_present_TripB_AVFValue_Unit_Set_Night_u32;

			if (g_previous_TripB_AVFValue_Night_u32 == TC_INVALID)
			{
				lv_label_set_text_fmt(guider_ui.screen_L2_val, "---.-");
				if (g_previous_TripB_AVFValue_Unit_Set_Night_u32  == Lper100km)
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
				if (g_previous_TripB_AVFValue_Unit_Set_Night_u32  == Lper100km)
				{
					lv_label_set_text(guider_ui.screen_L2_unit, "L/100km");
					if (g_previous_TripB_AVFValue_Night_u32 == 0)
					{
						g_previous_TripB_AVFValue_Night_u32 = 0;
					}
					else
					{
						g_previous_TripB_AVFValue_Night_u32 = 10000 / g_previous_TripB_AVFValue_Night_u32 ;
					}

					/* Limit AVF value if it exceeds max limit */
					SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&g_previous_TripB_AVFValue_Night_u32);
				}
				else if (g_previous_TripB_AVFValue_Unit_Set_Night_u32  == KmperL)
				{
					lv_label_set_text(guider_ui.screen_L2_unit, "km/L");
				}
				else
				{
					/* do nothing*/
				}

				lv_label_set_text_fmt(guider_ui.screen_L2_val, "%d.%d", (g_previous_TripB_AVFValue_Night_u32  / 10), (g_previous_TripB_AVFValue_Night_u32  % 10));
			}
		}

		/* Chang Color For Trip If It is Pressed */
		switch (g_TripB_UpKeypressed_U8)
		{
			case Pressed_State:
				lv_img_set_src(guider_ui.screen_up_arr,&new_night_trip_up_arrow_pressed);
				g_TripB_UpKeypressed_U8 = 2;
				break;
			case UnPressed_State:
				lv_img_set_src(guider_ui.screen_up_arr,&new_trip_up_arrow);
				g_TripB_UpKeypressed_U8 = 0;
				break;
			default:
				g_TripB_UpKeypressed_U8 = 0;
				break;
		}

		/* Chang Color For Trip Btn If It is Pressed */

		switch (g_TripB_DownKeypressed_U8)
		{
			case Pressed_State:
				lv_img_set_src(guider_ui.screen_dw_arr, &new_night_trip_down_arrow_pressed);
				g_TripB_DownKeypressed_U8 = 2;
				break;
			case UnPressed_State:
				lv_img_set_src(guider_ui.screen_dw_arr, &new_trip_down_arrow);
				g_TripB_DownKeypressed_U8 = 0;
				break;
			default:
				g_TripB_DownKeypressed_U8 = 0;
				break;
		}				
		
	}

	void GUI_TripB_Main_Screen_Day_Entry(void)
	{
		lv_label_set_text(guider_ui.screen_day_lbl1, "Trip");
		lv_label_set_text(guider_ui.screen_day_lbl3, "km");
		lv_label_set_text(guider_ui.screen_day_lbl4, "Time");

		// lv_obj_clear_flag(guider_ui.screen_day_base_container, LV_OBJ_FLAG_HIDDEN);
		// lv_obj_clear_flag(guider_ui.screen_dat_inter_con, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_day_trip_con, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);

		lv_obj_add_flag(guider_ui.screen_day_Trip_up_arr, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_Trip_down_arr, LV_OBJ_FLAG_HIDDEN);

	for (int i =8 ; i<=15; i++)
	{
		lv_obj_set_pos((lv_obj_t*)g_Trip_Time_Pos_Table[i].Label_Name->class_p,g_Trip_Time_Pos_Table[i].Label_X_Pos[0],g_Trip_Time_Pos_Table[i].Label_Y_Pos[0]);
	}

		lv_img_set_src(guider_ui.screen_Trip_blank, &tripB_day_icon);
		lv_obj_move_foreground(guider_ui.screen_Trip_blank);
		lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

		/* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
		g_previous_TripB_value_Day_u32 = 0xFF;
		g_previous_TripB_time_hour_Day_u8 = 0xFF;
		g_previous_TripB_time_Minute_Day_u8   = 0xFF;
	}
	void GUI_TripB_Main_Screen_Day_During(void)
	{

		uint32_t fl_present_trip_value_Day_u32 = ODO_Get_TripOdometer(1);
		bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
		uint32_t fl_present_Trip_time_hour_Day_u8 = Swc_Trip_Timer_Get_Hour_value(1);
		uint32_t fl_present_Trip_time_Minute_Day_u8 = Swc_Trip_Timer_Get_Min_value(1);

		/*update the Trip odometer value only if there is a change*/
		if( fl_present_trip_value_Day_u32 == ODO_INVALID_STATE)
		{
			lv_label_set_text_fmt(guider_ui.screen_day_lbl2, "---.-");
		}
		else if ((g_previous_TripB_value_Day_u32 != fl_present_trip_value_Day_u32))
		{
			g_previous_TripB_value_Day_u32 = fl_present_trip_value_Day_u32;
			lv_label_set_text_fmt(guider_ui.screen_day_lbl2, "%d.%d", (g_previous_TripB_value_Day_u32 / 10), (g_previous_TripB_value_Day_u32 % 10));
		}

		else
		{
			/*Do nothing*/
		}

		/*update the Trip time value only if there is a change*/
		if (fl_Trip_Timer_St == TRUE)
		{
			if ((g_previous_TripB_time_hour_Day_u8 != fl_present_Trip_time_hour_Day_u8) ||
				(g_previous_TripB_time_Minute_Day_u8 != fl_present_Trip_time_Minute_Day_u8))
			{
				g_previous_TripB_time_hour_Day_u8 = fl_present_Trip_time_hour_Day_u8;
				g_previous_TripB_time_Minute_Day_u8 = fl_present_Trip_time_Minute_Day_u8;

				if (g_previous_TripB_time_hour_Day_u8 <= 9)
				{
					if (g_previous_TripB_time_Minute_Day_u8 <= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "0%d", g_previous_TripB_time_hour_Day_u8);
						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "0%d", g_previous_TripB_time_Minute_Day_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "0%d", g_previous_TripB_time_hour_Day_u8);
						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "%d", g_previous_TripB_time_Minute_Day_u8);
					}
				}
				else
				{
					if (g_previous_TripB_time_Minute_Day_u8 <= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "%d", g_previous_TripB_time_hour_Day_u8);
						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "0%d", g_previous_TripB_time_Minute_Day_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "%d", g_previous_TripB_time_hour_Day_u8);

						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "%d", g_previous_TripB_time_Minute_Day_u8);
					}
				}
				lv_label_set_text(guider_ui.screen_day_lbl_6, "h");
				lv_label_set_text(guider_ui.screen_day_lbl_8, "m");
			}
		}
		else
		{
			/* Make Data change as invalid state doesn't change value*/
			g_previous_TripB_time_hour_Day_u8 = 0xffff;
			lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "--", g_previous_TripB_time_hour_Day_u8);
			lv_label_set_text_fmt(guider_ui.screen_day_lbl_6, "h", g_previous_TripB_time_hour_Day_u8);
			lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "--", g_previous_TripB_time_Minute_Day_u8);
			lv_label_set_text_fmt(guider_ui.screen_day_lbl_8, "m", g_previous_TripB_time_Minute_Day_u8);
		}
	}

	void GUI_TripB_Main_Screen_Day_Exit(void)
	{
		lv_obj_add_flag(guider_ui.screen_day_trip_con, LV_OBJ_FLAG_HIDDEN);

		lv_obj_add_flag(guider_ui.screen_day_Trip_up_arr, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_Trip_down_arr, LV_OBJ_FLAG_HIDDEN);
	}

	void GUI_TripB_Time_Day_Enty(void)
	{
		lv_obj_clear_flag(guider_ui.screen_day_trip_con, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_day_Trip_up_arr, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_day_Trip_down_arr, LV_OBJ_FLAG_HIDDEN);
		lv_label_set_text(guider_ui.screen_day_lbl1, "Trip");
		lv_label_set_text(guider_ui.screen_day_lbl3, "km");
		lv_label_set_text(guider_ui.screen_day_lbl4, "Time");
		lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

		for (int i =8 ; i<=15; i++)
		{
		lv_obj_set_pos((lv_obj_t*)g_Trip_Time_Pos_Table[i].Label_Name->class_p,g_Trip_Time_Pos_Table[i].Label_X_Pos[0],g_Trip_Time_Pos_Table[i].Label_Y_Pos[0]);
		}
	
		lv_img_set_src(guider_ui.screen_Trip_blank,&tripB_day_icon);
		lv_obj_move_foreground(guider_ui.screen_Trip_blank);

		lv_obj_clear_flag(guider_ui.screen_day_Trip_up_arr, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_day_Trip_down_arr, LV_OBJ_FLAG_HIDDEN);

		/* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
		g_previous_TripB_value_Day_u32 = 0xFF;
		g_previous_TripB_time_hour_Day_u8 = 0xFF;
		g_previous_TripB_time_Minute_Day_u8   = 0xFF;

	}

	void GUI_TripB_Time_Day_During(void)
	{
		uint32_t fl_present_trip_value_Day_u32 = ODO_Get_TripOdometer(1);
		bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
		uint32_t fl_present_Trip_time_hour_Day_u8 = Swc_Trip_Timer_Get_Hour_value(1);
		uint32_t fl_present_Trip_time_Minute_Day_u8 = Swc_Trip_Timer_Get_Min_value(1);

		/*update the Trip odometer value only if there is a change*/
		if( fl_present_trip_value_Day_u32 == ODO_INVALID_STATE)
		{
			lv_label_set_text_fmt(guider_ui.screen_day_lbl2, "---.-");
		}
		else if ((g_previous_TripB_value_Day_u32 != fl_present_trip_value_Day_u32))
		{
			g_previous_TripB_value_Day_u32 = fl_present_trip_value_Day_u32;
			lv_label_set_text_fmt(guider_ui.screen_day_lbl2, "%d.%d", (g_previous_TripB_value_Day_u32 / 10), (g_previous_TripB_value_Day_u32 % 10));
		}
		else
		{
			/*Do nothing*/
		}

		/*update the Trip time value only if there is a change*/
		if (fl_Trip_Timer_St == TRUE)
		{
			if ((g_previous_TripB_time_hour_Day_u8 != fl_present_Trip_time_hour_Day_u8) ||
				(g_previous_TripB_time_Minute_Day_u8 != fl_present_Trip_time_Minute_Day_u8))
			{
				g_previous_TripB_time_hour_Day_u8 = fl_present_Trip_time_hour_Day_u8;
				g_previous_TripB_time_Minute_Day_u8 = fl_present_Trip_time_Minute_Day_u8;

				if (g_previous_TripB_time_hour_Day_u8 <= 9)
				{
					if (g_previous_TripB_time_Minute_Day_u8 <= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "0%d", g_previous_TripB_time_hour_Day_u8);
						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "0%d", g_previous_TripB_time_Minute_Day_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "0%d", g_previous_TripB_time_hour_Day_u8);
						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "%d", g_previous_TripB_time_Minute_Day_u8);
					}
				}
				else
				{
					if (g_previous_TripB_time_Minute_Day_u8 <= 9)
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "%d", g_previous_TripB_time_hour_Day_u8);
						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "0%d", g_previous_TripB_time_Minute_Day_u8);
					}
					else
					{
						lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "%d", g_previous_TripB_time_hour_Day_u8);

						lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "%d", g_previous_TripB_time_Minute_Day_u8);
					}
				}
				lv_label_set_text(guider_ui.screen_day_lbl_6, "h");
				lv_label_set_text(guider_ui.screen_day_lbl_8, "m");
			}
		}
		else
		{
			/* Make Data change as invalid state doesn't change value*/
			g_previous_TripB_time_hour_Day_u8 = 0XFFFF;
			lv_label_set_text_fmt(guider_ui.screen_day_lbl5, "--", g_previous_TripB_time_hour_Day_u8);
			lv_label_set_text_fmt(guider_ui.screen_day_lbl_6, "h", g_previous_TripB_time_hour_Day_u8);
			lv_label_set_text_fmt(guider_ui.screen_day_lbl_7, "--", g_previous_TripB_time_Minute_Day_u8);
			lv_label_set_text_fmt(guider_ui.screen_day_lbl_8, "m", g_previous_TripB_time_Minute_Day_u8);
		}

		/* Chang Color For Trip If It is Pressed */
		switch (g_TripB_UpKeypressed_U8)
		{
			case Pressed_State:
				lv_img_set_src(guider_ui.screen_day_Trip_up_arr,&new_day_trip_up_arrow_pressed);
				g_TripB_UpKeypressed_U8 = 2;
				break;
			case UnPressed_State:
				lv_img_set_src(guider_ui.screen_day_Trip_up_arr,&new_day_trip_up_arrow_normal);
				g_TripB_UpKeypressed_U8 = 0;
				break;
			default:
				g_TripB_UpKeypressed_U8 = 0;
				break;
		}

		/* Chang Color For Trip Btn If It is Pressed */
		switch (g_TripB_DownKeypressed_U8)
		{
			case Pressed_State:
				lv_img_set_src(guider_ui.screen_day_Trip_down_arr, &new_day_trip_down_arrow_pressed);
				g_TripB_DownKeypressed_U8 = 2;
				break;
			case UnPressed_State:
				lv_img_set_src(guider_ui.screen_day_Trip_down_arr, &new_day_trip_down_arrow_normal);
				g_TripB_DownKeypressed_U8 = 0;
				break;
			default:
				g_TripB_DownKeypressed_U8 = 0;
				break;
		}
	}

	void GUI_TripB_Time_Day_Exit(void)
	{
		lv_obj_add_flag(guider_ui.screen_day_trip_con, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);

		lv_obj_add_flag(guider_ui.screen_day_Trip_up_arr, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_Trip_down_arr, LV_OBJ_FLAG_HIDDEN);
	}

	void GUI_TripB_AVF_Day_Entry(void)
	{
		
		lv_obj_set_size(guider_ui.screen_day_in_lb2, 48, 18);
		lv_obj_clear_flag(guider_ui.screen_day_inter_con2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
		lv_label_set_text(guider_ui.screen_day_in_lb1, "Av Speed");
		lv_label_set_text(guider_ui.screen_day_in_lb4, "Av Fuel");
		lv_label_set_text(guider_ui.screen_day_in_lb3, "km/h");
		lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

		for (int i = 22; i <= 27; i++)
		{
			lv_obj_set_pos((lv_obj_t*)g_Trip_Time_Pos_Table[i].Label_Name->class_p, g_Trip_Time_Pos_Table[i].Label_X_Pos[0], g_Trip_Time_Pos_Table[i].Label_Y_Pos[0]);
		}

		lv_img_set_src(guider_ui.screen_Trip_blank, &tripB_day_icon);
		lv_obj_move_foreground(guider_ui.screen_Trip_blank);

		lv_obj_clear_flag(guider_ui.screen_day_in_arr1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_day_in_arr2, LV_OBJ_FLAG_HIDDEN);

		lv_obj_set_style_text_font(guider_ui.screen_day_in_lb3, &lv_font_FjallaOne_Regular_14, 0);
		lv_obj_set_style_text_font(guider_ui.screen_day_in_lb6, &lv_font_FjallaOne_Regular_14, 0);

		/* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
		g_previous_TripB_AVSValue_Day_u32 = 0xFF;
		g_previous_TripB_AVFValue_Day_u32 = 0xFF;
		g_previous_TripB_AVFValue_Unit_Set_Day_u32 = 0xFF;
		
	}
	void GUI_TripB_AVF_Day_During(void)
	{
		uint32_t fl_present_TripB_AVSValue_Day_u32 = Swc_Avereage_Speed_Get_value(1);
		uint32_t fl_present_TripB_AVFValue_Day_u32 = display_AFE(1);
		uint32_t fl_present_TripB_AVFValue_Unit_Set_Day_u32 = Fuel_Consumption_fn();
		bool fl_TripA_Av_Speed_Status_bl = Swc_Average_Speed_Get_Status();

		if ((g_previous_TripB_AVSValue_Day_u32 != fl_present_TripB_AVSValue_Day_u32))
		{
			g_previous_TripB_AVSValue_Day_u32 = fl_present_TripB_AVSValue_Day_u32;

			if (fl_TripA_Av_Speed_Status_bl == FALSE)
			{
				lv_label_set_text_fmt(guider_ui.screen_day_in_lb2, "---");
			}
			else
			{
				lv_label_set_text_fmt(guider_ui.screen_day_in_lb2, "%d", (g_previous_TripB_AVSValue_Day_u32));
			}
		}
		else
		{
			/*Do Nothing*/
		}

		if ((g_previous_TripB_AVFValue_Day_u32 != fl_present_TripB_AVFValue_Day_u32) ||
			(g_previous_TripB_AVFValue_Unit_Set_Day_u32 != fl_present_TripB_AVFValue_Unit_Set_Day_u32))
		{
			g_previous_TripB_AVFValue_Day_u32 = fl_present_TripB_AVFValue_Day_u32;
			g_previous_TripB_AVFValue_Unit_Set_Day_u32 = fl_present_TripB_AVFValue_Unit_Set_Day_u32;

			if (g_previous_TripB_AVFValue_Day_u32 == TC_INVALID)
			{
				lv_label_set_text_fmt(guider_ui.screen_day_in_lb5, "---.-");

				if (g_previous_TripB_AVFValue_Unit_Set_Day_u32  == Lper100km)
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
				if (g_previous_TripB_AVFValue_Unit_Set_Day_u32 == Lper100km)
				{
					lv_label_set_text(guider_ui.screen_day_in_lb6, "L/100km");
					if (g_previous_TripB_AVFValue_Day_u32 == 0)
					{
						g_previous_TripB_AVFValue_Day_u32 = 0;
					}
					else
					{
						g_previous_TripB_AVFValue_Day_u32 = 10000 / g_previous_TripB_AVFValue_Day_u32;
					}

					/* Limit AVF value if it exceeds max limit */
					SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&g_previous_TripB_AVFValue_Day_u32);
					
				}
				else if (g_previous_TripB_AVFValue_Unit_Set_Day_u32 == KmperL)
				{
					lv_label_set_text(guider_ui.screen_day_in_lb6, "km/L");
				}
				else
				{
					/* do nothing*/
				}

				lv_label_set_text_fmt(guider_ui.screen_day_in_lb5, "%d.%d", (g_previous_TripB_AVFValue_Day_u32 / 10), (g_previous_TripB_AVFValue_Day_u32 % 10));
			}
		}

		/* Chang Color For Trip If It is Pressed */
		switch (g_TripB_UpKeypressed_U8)
		{
			case Pressed_State:
				lv_img_set_src(guider_ui.screen_day_in_arr1,&new_day_trip_up_arrow_pressed);
				g_TripB_UpKeypressed_U8 = 2;
				break;
			case UnPressed_State:
				lv_img_set_src(guider_ui.screen_day_in_arr1,&new_day_trip_up_arrow_normal);
				g_TripB_UpKeypressed_U8 = 0;
				break;
			default:
				g_TripB_UpKeypressed_U8 = 0;
				break;
		}

		/* Chang Color For Trip Btn If It is Pressed */
		switch (g_TripB_DownKeypressed_U8)
		{
			case Pressed_State:
				lv_img_set_src(guider_ui.screen_day_in_arr2, &new_day_trip_down_arrow_pressed);
				g_TripB_DownKeypressed_U8 = 2;
				break;
			case UnPressed_State:
				lv_img_set_src(guider_ui.screen_day_in_arr2, &new_day_trip_down_arrow_normal);
				g_TripB_DownKeypressed_U8 = 0;
				break;
			default:
				g_TripB_DownKeypressed_U8 = 0;
				break;
		}
	}
	void GUI_TripB_AVF_Day_Exit(void)
	{
		lv_obj_add_flag(guider_ui.screen_day_inter_con2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_in_arr1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_day_in_arr2, LV_OBJ_FLAG_HIDDEN);
	}

	uint8_t TripB_Button_UpEvent(void)
	{
		g_TripB_UpKeypressed_U8 = Pressed_State;
		return 0;
	}

	uint8_t TripB_Button_DownEvent(void)
	{
		g_TripB_DownKeypressed_U8 = Pressed_State;
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
