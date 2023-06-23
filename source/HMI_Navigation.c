/* @file FILE NAME */
#ifndef HMI_NAVIGATION_C
#define HMI_NAVIGATION_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Balasubramanian : Name (balasubramanian@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : HMI_Navigation
 *  Version                         : V1.0
 *  Micros supported                :
 *  Compilers supported             :
 *  Platforms supported             :
 *  Description                     : This file consists of definitions of Navigation design implementations
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
#include "UART_DataManager.h"
#include "HMI_Setting_Screen.h"
#include "HMI_Clock.h"
#include "HMI_Phone.h"
#include "HMI_GUI_Interface.h"
#include "HMI_Navigation.h"
#include "Interpolation.h"

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
	 * @brief: This variable is used to get the signal connectivity status
	 * @Unit:
	 * @Resolution:
	 * @Range:
	 * @Applicability:
	 */

	uint8_t g_Get_Signal_Connectivity_Status;

	/*
	 * @brief: This variable is used to get the navigation connectivity status
	 * @Unit:
	 * @Resolution:
	 * @Range:
	 * @Applicability:
	 */
	uint8_t g_Get_Navigation_Connectivity_Status;
	signed int navigation_loc[2] = {50, 60};

	signed int Day_navigation_loc[2] = {55, 5};

	uint8_t fl_Get_Current_Navi_Foramt;

	signed int Day_navloc[2] = {45, 60};
	int16_t navigation_Image[2] = {65, 10};

	static g_Nav_image g_Nav_img_table[46] = {NAVIGATION_IMAGE_TABLE};

	/*
	 * @brief: This variable is used to get the packet type received from Smart phone
	 * @Unit:
	 * @Resolution:
	 * @Range:
	 * @Applicability:
	 */
	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST g_Get_Screen_sts_str;

	bool g_Img_Blink_bl = false;

	uint8_t g_Nav_Table_Column_Index = 0;

	uint8_t g_Navi_Find_Index = 0;

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

	/***********************************************************************************************************************
	 *                                          F U N C T I O N     D E F I N I T I O N S
	 ***********************************************************************************************************************/
	void GUI_Navigation_Night_Entry(void)
	{
		lv_obj_move_foreground(guider_ui.screen_Trip_blank);
		lv_obj_clear_flag(guider_ui.screen_navi_container, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
		lv_label_set_text(guider_ui.screen_navi_unit, "");
		lv_label_set_text(guider_ui.screen_nav_est, "");
		lv_label_set_text_fmt(guider_ui.screen_nav_clo_colon, "");
		lv_obj_clear_flag(guider_ui.screen_navi_lbl, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_pos(guider_ui.screen_navi_lbl, navigation_loc[0], navigation_loc[1]);
		lv_obj_set_size(guider_ui.screen_navi_lbl, 100, 13);

		lv_label_set_text(guider_ui.screen_navi_val, "");
		lv_label_set_text(guider_ui.screen_navi_unit, "");
		lv_label_set_text(guider_ui.screen_nav_clo_hr, "");
		lv_label_set_text(guider_ui.screen_nav_clo_colon, "");
		lv_label_set_text(guider_ui.screen_nav_clo_min, "");
		lv_label_set_text(guider_ui.screen_nav_clo_am, "");
		lv_label_set_text_fmt(guider_ui.screen_nav_clo_colon, "");

		lv_obj_add_flag(guider_ui.screen_Sub_Con, LV_OBJ_FLAG_HIDDEN);

		lv_img_set_src(guider_ui.screen_Trip_blank, &_img_night_navigation_icon_30x30);

		fl_Get_Current_Navi_Foramt = GUI_Get_Time_Format();

		if (fl_Get_Current_Navi_Foramt == CLOCK_12HR_FORMAT)
		{
			GUI_Main12hr_position();
			GUI_Intermediate12hr_position();
		}
		else
		{
			GUI_Main24hr_position();
			GUI_Intermediate24hr_position();
		}
	}

	extern uint8_t g_BLE_Connection_Status_u8;

	void GUI_Navigation_Night_During(void)
	{

		g_Nav_Table_Column_Index = 0;

		lv_obj_add_flag(guider_ui.screen_No_Sig_Nyt, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_pos(guider_ui.screen_nav_img, navigation_Image[0], navigation_Image[1]);

		g_Get_Screen_sts_str = UART_DataManager_Get_Connectivity_Info(NAV_PKT);

		g_Get_Navigation_Connectivity_Status = GUI_BLE_Enable_Status();
		
		if (g_Get_Navigation_Connectivity_Status == BLE_CONNECTED)
		{
			/*BLE connection status*/
			lv_obj_add_flag(guider_ui.screen_navi_lbl, LV_OBJ_FLAG_HIDDEN);

			lv_label_set_text_fmt(guider_ui.screen_navi_val, "%c%c%c", g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.DIST_TO_MANEUVER[2],
								  g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.DIST_TO_MANEUVER[3],
								  g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.DIST_TO_MANEUVER[4]);

			lv_label_set_text_fmt(guider_ui.screen_nav_clo_hr, "%c%c", g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.TIME_AND_UNIT[0],
								  g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.TIME_AND_UNIT[1]);

			if (g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.TIME_AND_UNIT[2] != 0)
			{
				lv_label_set_text_fmt(guider_ui.screen_nav_clo_colon, ":");
			}

			lv_label_set_text_fmt(guider_ui.screen_nav_clo_min, "%c%c", g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.TIME_AND_UNIT[3],
								  g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.TIME_AND_UNIT[4]);

			lv_label_set_text_fmt(guider_ui.screen_nav_clo_am, "%c%c", g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.TIME_AND_UNIT[2],
								  g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.TIME_AND_UNIT[5]);

			if (g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.DIST_UNIT == 0x6B)
			{
				lv_label_set_text(guider_ui.screen_navi_unit, "km");
			}
			else if (g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.DIST_UNIT == 0x31)
			{
				lv_label_set_text(guider_ui.screen_navi_unit, "m");
			}
			else if (g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.DIST_UNIT == 0x32)
			{
				lv_label_set_text(guider_ui.screen_navi_unit, "mi");
			}
			else
			{
				/*do nothing*/
			}
			lv_label_set_text(guider_ui.screen_nav_est, "ETA");
			
			uint8_t fl_Nav_Table_Size = (sizeof(g_Nav_img_table) / sizeof(g_Nav_image));
			g_Nav_Table_Column_Index = 0;

			/* Get Index Number From Navigation Table*/
			for (g_Navi_Find_Index = 0; g_Navi_Find_Index <= fl_Nav_Table_Size; g_Navi_Find_Index++)
			{
				if (g_Nav_img_table[g_Navi_Find_Index].g_Nav_img_num == g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.DIR_SYM)
				{
					g_Nav_Table_Column_Index = g_Navi_Find_Index;
					break;
				}
			}

			/* Check the Index is 0 or Invalid For Display No Signal */
			if (g_Nav_Table_Column_Index == 255 || g_Nav_Table_Column_Index == 0)
			{
				lv_img_set_src(guider_ui.screen_nav_img, g_Nav_img_table[0].g_Nav_Night_img);
				lv_obj_set_pos(guider_ui.screen_nav_img, g_Nav_img_table[0].Nav_Img_X_Pos, g_Nav_img_table[0].Nav_Img_Y_Pos);
				lv_obj_set_size(guider_ui.screen_nav_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

				lv_label_set_text(guider_ui.screen_navi_val, "");
				lv_label_set_text(guider_ui.screen_nav_clo_hr, "");				
				lv_label_set_text(guider_ui.screen_nav_clo_min, "");
				lv_label_set_text(guider_ui.screen_nav_clo_am, "");


				lv_label_set_text(guider_ui.screen_navi_unit, "");
				lv_label_set_text(guider_ui.screen_nav_est, "");
				lv_label_set_text_fmt(guider_ui.screen_nav_clo_colon, "");
				lv_obj_clear_flag(guider_ui.screen_No_Sig_Nyt, LV_OBJ_FLAG_HIDDEN);
				lv_img_set_src(guider_ui.screen_No_Sig_Nyt, &night_no_signal);
			}
			else
			{
				lv_img_set_src(guider_ui.screen_nav_img, g_Nav_img_table[g_Nav_Table_Column_Index].g_Nav_Night_img);
				lv_obj_set_pos(guider_ui.screen_nav_img, g_Nav_img_table[g_Nav_Table_Column_Index].Nav_Img_X_Pos, g_Nav_img_table[g_Nav_Table_Column_Index].Nav_Img_Y_Pos);
				lv_obj_set_size(guider_ui.screen_nav_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
			}

			/* For Blink The Navigation Images*/
			if (g_Img_Blink_bl && g_Nav_img_table[g_Nav_Table_Column_Index].Nav_Blink_Status)
			{
				lv_obj_clear_flag(guider_ui.screen_nav_img, LV_OBJ_FLAG_HIDDEN);
			}
			else if (g_Nav_img_table[g_Nav_Table_Column_Index].Nav_Blink_Status)
			{
				lv_obj_add_flag(guider_ui.screen_nav_img, LV_OBJ_FLAG_HIDDEN);
			}
			else if (!g_Nav_img_table[g_Nav_Table_Column_Index].Nav_Blink_Status)
			{
				lv_obj_clear_flag(guider_ui.screen_nav_img, LV_OBJ_FLAG_HIDDEN);				
			}
			
		}
		else
		{
			lv_obj_clear_flag(guider_ui.screen_nav_img, LV_OBJ_FLAG_HIDDEN);	
			lv_img_set_src(guider_ui.screen_nav_img, &nightnosignalicon_25x25);
			lv_obj_set_pos(guider_ui.screen_nav_img, 80, 15);
			lv_obj_set_size(guider_ui.screen_nav_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

			lv_label_set_text(guider_ui.screen_navi_unit, "");
			lv_label_set_text(guider_ui.screen_nav_est, "");
			lv_label_set_text(guider_ui.screen_navi_val, "");
			lv_label_set_text(guider_ui.screen_nav_clo_hr, "");		
			lv_label_set_text(guider_ui.screen_nav_clo_min, "");
			lv_label_set_text(guider_ui.screen_nav_clo_am, "");
			lv_label_set_text_fmt(guider_ui.screen_nav_clo_colon, "");

			lv_obj_clear_flag(guider_ui.screen_No_Sig_Nyt, LV_OBJ_FLAG_HIDDEN);
			lv_img_set_src(guider_ui.screen_No_Sig_Nyt, &night_no_signal);
		}
		
	}

void GUI_Navigation_Night_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_contscr_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_navi_container, LV_OBJ_FLAG_HIDDEN);

}

void GUI_Navigation_Entry_Screen_Main_Day_Mode(void)
{
	lv_obj_clear_flag(guider_ui.screen_Main_day_Navigation, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);

	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
	lv_label_set_text(guider_ui.screen_Day_navi_unit, "");
	lv_label_set_text(guider_ui.screen_Day_nav_est, "");
	lv_label_set_text_fmt(guider_ui.screen_Day_nav_clo_colon, "");
	lv_obj_clear_flag(guider_ui.screen_Day_navi_lbl, LV_OBJ_FLAG_HIDDEN);

	lv_label_set_text(guider_ui.screen_Day_navi_val, "");
	lv_label_set_text(guider_ui.screen_Day_navi_unit, "");
	lv_label_set_text(guider_ui.screen_Day_nav_clo_hr, "");
	lv_label_set_text(guider_ui.screen_Day_nav_clo_colon, "");
	lv_label_set_text(guider_ui.screen_Day_nav_clo_min, "");
	lv_label_set_text(guider_ui.screen_Day_nav_clo_am, "");
	lv_label_set_text_fmt(guider_ui.screen_Day_nav_clo_colon, "");

	lv_img_set_src(guider_ui.screen_Trip_blank, &nav_day_icon_30x30);

	lv_obj_move_foreground(guider_ui.screen_Trip_blank);

}

	void GUI_Navigation_During_Screen_Main_Day_Mode(void)
	{
		g_Nav_Table_Column_Index =0 ;

		lv_obj_add_flag(guider_ui.screen_No_Sig_Day, LV_OBJ_FLAG_HIDDEN);		

		g_Get_Screen_sts_str = UART_DataManager_Get_Connectivity_Info(NAV_PKT);

		g_Get_Navigation_Connectivity_Status = GUI_BLE_Enable_Status();

		if (g_Get_Navigation_Connectivity_Status == BLE_CONNECTED)
		{
			lv_label_set_text_fmt(guider_ui.screen_Day_navi_val, "%c%c%c", g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.DIST_TO_MANEUVER[2],
								  g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.DIST_TO_MANEUVER[3],
								  g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.DIST_TO_MANEUVER[4]);

			lv_label_set_text_fmt(guider_ui.screen_Day_nav_clo_hr, "%c%c", g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.TIME_AND_UNIT[0],
								  g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.TIME_AND_UNIT[1]);

			if (g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.TIME_AND_UNIT[2] != 0)
			{
				lv_label_set_text_fmt(guider_ui.screen_Day_nav_clo_colon, ":");
			}

			lv_label_set_text_fmt(guider_ui.screen_Day_nav_clo_min, "%c%c", g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.TIME_AND_UNIT[3],
								  g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.TIME_AND_UNIT[4]);

			lv_label_set_text_fmt(guider_ui.screen_Day_nav_clo_am, "%c%c", g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.TIME_AND_UNIT[2],
								  g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.TIME_AND_UNIT[5]);

			if (g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.DIST_UNIT == 0x6B)
			{
				lv_label_set_text(guider_ui.screen_Day_navi_unit, "km");
			}
			else if (g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.DIST_UNIT == 0x31)
			{
				lv_label_set_text(guider_ui.screen_Day_navi_unit, "m");
			}
			else if (g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.DIST_UNIT == 0x32)
			{
				lv_label_set_text(guider_ui.screen_Day_navi_unit, "mi");
			}
			else
			{
				/*do nothing*/
			}

			lv_label_set_text(guider_ui.screen_Day_nav_est, "ETA");

			uint8_t fl_Nav_Table_Size = (sizeof(g_Nav_img_table) / sizeof(g_Nav_image));
			g_Nav_Table_Column_Index = 0;

			/* Get Index Number From Navigation Table*/
			for (g_Navi_Find_Index = 0; g_Navi_Find_Index <= fl_Nav_Table_Size; g_Navi_Find_Index++)
			{
				if (g_Nav_img_table[g_Navi_Find_Index].g_Nav_img_num == g_Get_Screen_sts_str.Hero_SmartPhone_Navigation_Pkt_St.DIR_SYM)
				{
					g_Nav_Table_Column_Index = g_Navi_Find_Index;
					break;
				}
			}  

			/* Check the Index is 0 or Invalid For Display No Signal */
			if (g_Nav_Table_Column_Index == 255 || g_Nav_Table_Column_Index == 0)
			{
				lv_img_set_src(guider_ui.screen_Day_nav_img, g_Nav_img_table[0].g_Nav_Day_img);
				lv_obj_set_pos(guider_ui.screen_Day_nav_img, g_Nav_img_table[0].Nav_Img_X_Pos, g_Nav_img_table[0].Nav_Img_Y_Pos);
				lv_obj_set_size(guider_ui.screen_Day_nav_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

				lv_label_set_text(guider_ui.screen_Day_navi_val, "");
				lv_label_set_text(guider_ui.screen_Day_nav_clo_hr, "");				
				lv_label_set_text(guider_ui.screen_Day_nav_clo_min, "");
				lv_label_set_text(guider_ui.screen_Day_nav_clo_am, "");


				lv_label_set_text(guider_ui.screen_Day_navi_unit, "");
				lv_label_set_text(guider_ui.screen_Day_nav_est, "");
				lv_label_set_text_fmt(guider_ui.screen_Day_nav_clo_colon, "");
				lv_obj_clear_flag(guider_ui.screen_No_Sig_Day, LV_OBJ_FLAG_HIDDEN);
				lv_img_set_src(guider_ui.screen_No_Sig_Day, &img_day_no_signal);
			}
			else
			{
				lv_img_set_src(guider_ui.screen_Day_nav_img, g_Nav_img_table[g_Nav_Table_Column_Index].g_Nav_Day_img);
				lv_obj_set_pos(guider_ui.screen_Day_nav_img, g_Nav_img_table[g_Nav_Table_Column_Index].Nav_Img_X_Pos, g_Nav_img_table[g_Nav_Table_Column_Index].Nav_Img_Y_Pos);
				lv_obj_set_size(guider_ui.screen_Day_nav_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
			}
			
			/* For Blink The Navigation Images*/
			if (g_Img_Blink_bl && g_Nav_img_table[g_Nav_Table_Column_Index].Nav_Blink_Status)
			{
				lv_obj_clear_flag(guider_ui.screen_Day_nav_img, LV_OBJ_FLAG_HIDDEN);
			}
			else if (g_Nav_img_table[g_Nav_Table_Column_Index].Nav_Blink_Status)
			{
				lv_obj_add_flag(guider_ui.screen_Day_nav_img, LV_OBJ_FLAG_HIDDEN);
			}
			else if (!g_Nav_img_table[g_Nav_Table_Column_Index].Nav_Blink_Status)
			{
				lv_obj_clear_flag(guider_ui.screen_Day_nav_img, LV_OBJ_FLAG_HIDDEN);
			}
			
		}
		else
		{
			lv_obj_clear_flag(guider_ui.screen_Day_nav_img, LV_OBJ_FLAG_HIDDEN);
			lv_img_set_src(guider_ui.screen_Day_nav_img, &nightnosignalicon_25x25);
			lv_obj_set_pos(guider_ui.screen_Day_nav_img, 80, 15);
			lv_obj_set_size(guider_ui.screen_Day_nav_img, 25, 25);
			lv_label_set_text(guider_ui.screen_Day_navi_unit, "");
			lv_label_set_text(guider_ui.screen_Day_nav_est, "");
			lv_label_set_text_fmt(guider_ui.screen_Day_nav_clo_colon, "");
			
			lv_obj_clear_flag(guider_ui.screen_No_Sig_Day, LV_OBJ_FLAG_HIDDEN);
			lv_img_set_src(guider_ui.screen_No_Sig_Day, &img_day_no_signal);

			lv_label_set_text(guider_ui.screen_Day_navi_val, "");
			lv_label_set_text(guider_ui.screen_Day_nav_clo_hr, "");				
			lv_label_set_text(guider_ui.screen_Day_nav_clo_min, "");
			lv_label_set_text(guider_ui.screen_Day_nav_clo_am, "");
		}

	}

	void GUI_Navigation_Exit_Screen_Main_Day_Mode(void)
	{
		lv_obj_add_flag(guider_ui.screen_Main_day_Navigation, LV_OBJ_FLAG_HIDDEN);
	}


/***********************************************************************************************************************
											  E N D   O F   S O F T W A R E
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
	REVISION NUMBER      : V1.0.1
	REVISION DATE        : 8/22/2022
	CREATED / REVISED BY : Balasubramanian (balasubramanian@niyatainfotech.com)
	DESCRIPTION          : Initial version
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! HMI_NAVIGATION */
