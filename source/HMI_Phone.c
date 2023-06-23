
/* @file FILE NAME */
#ifndef HMI_PHONE_C
#define HMI_PHONE_C

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

/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/

#include <gen/events_init.h>
#include <gen/gui_guider.h>
#include "peripherals.h"

#include "../lvgl/lvgl.h"

#include "lvgl_app.h"
#include <string.h>

#include "custom.h"
#include "UART_DataManager.h"
#include "HMI_Setting_Screen.h"
#include "BLE_music_module.h"
#include "HMI_Main_Screen.h"
#include "BLE_call_module.h"
#include "HMI_GUI_Interface.h"
#include "HMI_Clock.h"
#include "HMI_Phone.h"
#include "UART_DataManager.h"
#include "HMI_Music.h"
#include "BLE_music_module.h"

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

#define NO_CALL_ACTIVITY 0X30
#define INCOMING_CALL_ACTIVE 0X31
#define CALL_IS_CRNTLY_ACTIVE 0x32
#define CALL_IS_UNDER_HOLD 0x33
#define OUT_GOING_CALL 0x34
#define CALL_FAILED 0x35

#define HMI_CONTACT_NAME_LENGTH_MAX 9
#define HMI_CONTACT_NAME_TOTAL_LENGTH 12
#define UART_ARRAY_LENGTH_MAX 18
#define VOLUMESCREEN_TIMEOUT 30
#define PHONESCREEN_TIMEOUT 25

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
uint8_t g_Battery_Blink_u8;
uint8_t g_Main_Phone_Sub_Screen_Sel_Cnt_U8 = 1;

uint8_t g_Get_Battery_Connect_Status;
UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST g_Get_Screen_sts_st;
UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST g_Get_Screen_Callsts_str;
uint8_t g_Get_Signal_Connect_Status;
uint8_t checkpass1 = 0;
bool g_Is_BLE_Settings_Selected_bool = FALSE;
bool g_Is_BLE_Battery_Status_Received_bool = FALSE;
bool g_Is_BLE_Connection_Established_bool = FALSE;
bool g_Is_BLE_Signal_Status_Received_bool = FALSE;
bool g_SignalScreen_bl = FALSE;
bool g_BattScreen_bl = FALSE;
bool g_SMS_bl = FALSE;
bool g_MIScall_bl = FALSE;

uint8_t g_PreviousSignal_Value_U8 = 0x00;
uint8_t g_PreviousBattery_Value_U8 = 0x00;

extern uint8_t g_HMI_Screen_PST_State_u8;

uint8_t fl_Get_PssTime_Foramt;
signed int contact_menu[2] = {5, 20};
signed int Day_contact_menu[2] = {5, 20};

uint8_t g_volume_value = 0;
signed int volume_base_pos[2] = {25, 25};
signed int Day_volume_base_pos[2] = {25, 25};
signed int volume_pos[2] = {40, 40};
signed int Day_volume_pos[2] = {40, 40};

signed int contact_pos[2] = {42, 30};
signed int Day_contact_pos[2] = {42, 30};

signed int Day_contact_pos_new[2] = {5, 0};

signed int New_contact_pos[2] = {0, 20};

/* Phone Info Battery Icon Enable Status */
boolean g_Is_Phone_Info_Battery_Enabled_bool;

/* Phone Info Signal Strength Icon Enable Status */
boolean g_Is_Phone_Info_Sig_Strength_Enabled_bool;

static HMI_Music_Main_Screen_Type_St g_Volume_Main_Screen_st;

HMI_Active_call_screen_st g_contact_info_st_ptr;

HMI_contact_number_st g_contact_info_st;

extern uint8_t g_Phone_Sub_Screen_Sel_Cnt_U8;

HMI_Active_call_screen_st g_active_call_screen_info_ptr;

HMI_SMS_info_st g_sms_info_ptr;

HMI_missed_call_INFO_st g_missed_call_info_ptr;

char contact_number1_str[18];
char contact_number2_str;
char contact_number3_str[18];
char contact_number4_str;
char contact_number5_str[18];
char contact_number6_str;

char CALLER_NAME_1_str[13];
char CALLER_NAME_2_str[13];

char contact_number1[18];
char contact_number2[18];
char contact_number3[18];
char contact_number4[18];
char contact_number5[18];
char contact_number6[18];

char contact_num_str0[18];
char contact_num_str1[18];
char contact_num_str2[18];
char contact_num_str3[18];
char contact_num_str4[18];
char contact_num_str5[18];

char Active_call_Name[18];
uint8_t Active_call_Status;

extern bool g_VolumeEvent_Bl;

/* EXPORT UART BLE DATA STRUCTURE */
extern UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST UART_DataMgr_Pkt_St[MAX_PKT];
extern bool g_Img_Blink_bl;
extern uint8_t g_DownKeypressed_U8;
extern uint8_t g_UpKeypressed_U8;
uint8_t g_RightKeypressed_U8 = 0;
uint8_t g_LeftKeypressed_U8 = 0;
uint8_t g_RightKeypressed_Call_U8 = 0;
uint8_t g_charIndex_U8 = 0;
uint8_t g_Get_Current_TripInfo_Time_Foramt = 0;
uint8_t g_VolumeCounter_U8 = 0;
uint8_t g_PhoneCounter_U8 = 0;

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
void GUI_Phone_Main_Screen(uint8_t Screen_Main_Int_u8, uint8_t Day_Night_Mode_u8)
{
	HMI_Load_Intermediate_Screen();

	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

	lv_obj_add_flag(guider_ui.screen_L2_unit, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_L1_unit, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_imgKmph, LV_OBJ_FLAG_HIDDEN);

	lv_obj_clear_flag(guider_ui.screen_phone_container, LV_OBJ_FLAG_HIDDEN);

	lv_img_set_src(guider_ui.screen_Trip_blank, &night_contact_30x30);

	lv_obj_add_flag(guider_ui.screen_phone_lbl_2, LV_OBJ_FLAG_HIDDEN);
	lv_label_set_text(guider_ui.screen_phone_lbl_1, "Contacts");
	lv_obj_set_pos(guider_ui.screen_phone_lbl_1, 0, 28);

	lv_obj_add_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_phone_up_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_down_arrow, LV_OBJ_FLAG_HIDDEN);

	lv_obj_set_pos(guider_ui.screen_phone_lbl_1, 0, 28);

	fl_Get_PssTime_Foramt = GUI_Get_Time_Format();

	if (fl_Get_PssTime_Foramt == CLOCK_12HR_FORMAT)
	{
		GUI_Main12hr_position();
		GUI_Intermediate12hr_position();
	}
	else
	{
		GUI_Main24hr_position();
		GUI_Intermediate24hr_position();
	}

	lv_obj_add_flag(guider_ui.screen_phone_call_btn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_pos(guider_ui.screen_phone_call_btn, 146, 19);
	lv_obj_set_size(guider_ui.screen_phone_call_btn, 30, 30);
}

void GUI_BLE_Events_Entry(void)
{
	g_SignalScreen_bl = FALSE;
	g_BattScreen_bl = FALSE;
	g_SMS_bl = FALSE;
	g_MIScall_bl = FALSE;
	g_PreviousSignal_Value_U8 = 0x00;
	g_PreviousBattery_Value_U8 = 0x00;
}

void GUI_Password_Screen(void)
{

	g_Get_Battery_Connect_Status = GUI_BLE_Enable_Status();

	g_Get_Screen_sts_st = UART_DataManager_Get_Connectivity_Info(PASSCODE_PKT);

	if (g_Get_Battery_Connect_Status == BLUETOOTH_ON)
	{
		if ((UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.ID == 0x45) && (UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.Ble_Status == 0x00))
		{
			lv_label_set_text_fmt(guider_ui.screen_pass_unit, "%d%d%d%d%d%d", g_Get_Screen_sts_st.Cluster_Passcode_Pkt_st.PASSCODE_NUM[0],
								  g_Get_Screen_sts_st.Cluster_Passcode_Pkt_st.PASSCODE_NUM[1],
								  g_Get_Screen_sts_st.Cluster_Passcode_Pkt_st.PASSCODE_NUM[2],
								  g_Get_Screen_sts_st.Cluster_Passcode_Pkt_st.PASSCODE_NUM[3],
								  g_Get_Screen_sts_st.Cluster_Passcode_Pkt_st.PASSCODE_NUM[4],
								  g_Get_Screen_sts_st.Cluster_Passcode_Pkt_st.PASSCODE_NUM[5]);

			UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.ID = 0x00;
		}
	}
}

void PASSCODE_SCREEN_ENTRY(void)
{
	GUI_Clock_Entry();

	HMI_Load_Intermediate_Screen();

	lv_obj_move_foreground(guider_ui.screen_bl_pass_container);
	lv_obj_move_foreground(guider_ui.screen_Trip_blank);
	lv_obj_move_foreground(guider_ui.screen_trip_spedo_cont);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
	
	lv_obj_clear_flag(guider_ui.screen_bl_pass_container, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_Sub_Con, LV_OBJ_FLAG_HIDDEN);

	fl_Get_PssTime_Foramt = GUI_Get_Time_Format();

	if (fl_Get_PssTime_Foramt == CLOCK_12HR_FORMAT)
	{

		GUI_Main12hr_position();
		GUI_Intermediate12hr_position();
	}
	else
	{

		GUI_Main24hr_position();
		GUI_Intermediate24hr_position();
	}

	lv_img_set_src(guider_ui.screen_Trip_blank, &warning_night_30x30);
	set_obj_opa(guider_ui.screen_Trip_blank, 255);
	UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.ID = 0x45;
}

void PASSCODE_Screen_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_bl_pass_container, LV_OBJ_FLAG_HIDDEN);
}

void Passcode_Screen_Day_Entry()
{
	GUI_Clock_Entry();

	/* Show The Containers For Passcode Screen*/
	lv_obj_clear_flag(guider_ui.screen_Passcode_Day_container, LV_OBJ_FLAG_HIDDEN);

	/* Show Passcode Icon*/
	lv_obj_move_foreground(guider_ui.screen_Trip_blank);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
	lv_img_set_src(guider_ui.screen_Trip_blank, &warning_night_30x30);
	set_obj_opa(guider_ui.screen_Trip_blank, 255);

	/* Hide KM/h Icon & Subbutton*/
	lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
	// lv_obj_add_flag(guider_ui.screen_kmimage, LV_OBJ_FLAG_HIDDEN);

	UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.ID = 0x45;
}

void Passcode_Screen_Day_Exit()
{
	 /* Hide Passcode Container & Day Containers */
	lv_obj_add_flag(guider_ui.screen_Passcode_Day_container, LV_OBJ_FLAG_HIDDEN);
}

void Passcode_Screen_Day_During()
{

	g_Get_Battery_Connect_Status = GUI_BLE_Enable_Status();

	g_Get_Screen_sts_st = UART_DataManager_Get_Connectivity_Info(PASSCODE_PKT);

	if (g_Get_Battery_Connect_Status == BLUETOOTH_ON)
	{
		if ((UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.ID == 0x45) && (UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.Ble_Status == 0x00))
		{
			lv_label_set_text_fmt(guider_ui.screen_passcode_day_lbl2, "%d%d%d%d%d%d", g_Get_Screen_sts_st.Cluster_Passcode_Pkt_st.PASSCODE_NUM[0],
								  g_Get_Screen_sts_st.Cluster_Passcode_Pkt_st.PASSCODE_NUM[1],
								  g_Get_Screen_sts_st.Cluster_Passcode_Pkt_st.PASSCODE_NUM[2],
								  g_Get_Screen_sts_st.Cluster_Passcode_Pkt_st.PASSCODE_NUM[3],
								  g_Get_Screen_sts_st.Cluster_Passcode_Pkt_st.PASSCODE_NUM[4],
								  g_Get_Screen_sts_st.Cluster_Passcode_Pkt_st.PASSCODE_NUM[5]);
			UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.ID = 0x00;
		}
	}
}

void GUI_Phone_Screen(void)
{
	if (BLE_Get_Connection_Status() == 1)
	{
		g_Is_BLE_Settings_Selected_bool = GUI_BLE_Enable_Status();

		g_Get_Screen_sts_st = UART_DataManager_Get_Connectivity_Info(STS_PKT);

		/* Check the connection establishement status */
		g_Is_BLE_Connection_Established_bool = TRUE;

		/* Validate the Data Packet */
		if ((g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS >= 0x30) &&
			(g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS <= 0X34))
		{
			g_Is_BLE_Battery_Status_Received_bool = TRUE;
		}
		else
		{
			g_Is_BLE_Battery_Status_Received_bool = FALSE;
		}

		/* Decide the Enable / Disable status of the Phone Information ICON */
		if ((g_Is_BLE_Settings_Selected_bool != FALSE) &&
			(g_Is_BLE_Connection_Established_bool != FALSE) &&
			(g_Is_BLE_Battery_Status_Received_bool != FALSE))
		{
			if (g_PreviousBattery_Value_U8 != g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS || g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS == 0x30)
			{
				g_PreviousBattery_Value_U8 = g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS;
				if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS == 0x31)
				{
					/* Set 1st Bar Batter Image*/
					lv_obj_clear_flag(guider_ui.screen_Batt_Outline, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_Batt_Outline, &battery_night_1);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS == 0x32)
				{
					/* Set 2nd Bar Batter Image*/
					lv_obj_clear_flag(guider_ui.screen_Batt_Outline, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_Batt_Outline, &battery_night_2);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS == 0x33)
				{
					/* Set 3rd Bar Batter Image*/
					lv_obj_clear_flag(guider_ui.screen_Batt_Outline, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_Batt_Outline, &battery_night_3);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS == 0x34)
				{
					/* Set 4th Bar Batter Image*/
					lv_obj_clear_flag(guider_ui.screen_Batt_Outline, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_Batt_Outline, &battery_night_4);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS == 0x30)
				{
					lv_obj_clear_flag(guider_ui.screen_Batt_Outline, LV_OBJ_FLAG_HIDDEN);
					/* For Blink Battery*/
					if (g_Img_Blink_bl)
					{
						lv_img_set_src(guider_ui.screen_Batt_Outline, &battery_night_red);
					}
					else
					{
						lv_img_set_src(guider_ui.screen_Batt_Outline, &img_night_connectivity_icons_battery);
					}
				}
				else
				{
					lv_obj_add_flag(guider_ui.screen_Batt_Outline, LV_OBJ_FLAG_HIDDEN);
				}
			}
			else
			{
				/* Do Nothing */
			}
			g_BattScreen_bl = FALSE;
		}
		else if (g_BattScreen_bl == FALSE)
		{
			lv_obj_add_flag(guider_ui.screen_Batt_Outline, LV_OBJ_FLAG_HIDDEN);
			g_PreviousBattery_Value_U8 = 0x00;
			g_BattScreen_bl = TRUE;
		}
		else
		{
			/* No Changes Here */
		}
	}
	else if (g_BattScreen_bl == FALSE)
	{
		lv_obj_add_flag(guider_ui.screen_Batt_Outline, LV_OBJ_FLAG_HIDDEN);
		g_BattScreen_bl = TRUE;
	}
	else
	{
		/* No Changes Here */
	}
}

void GUI_Signal(void)
{

	if (BLE_Get_Connection_Status() == 1)
	{
		g_Get_Screen_sts_st = UART_DataManager_Get_Connectivity_Info(STS_PKT);

		g_Is_BLE_Settings_Selected_bool = GUI_BLE_Enable_Status();

		if ((g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR >= 0x30) &&
			(g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR <= 0X34))
		{
			g_Is_BLE_Signal_Status_Received_bool = TRUE;
		}
		g_Is_BLE_Connection_Established_bool = TRUE;

		/* Decide the Enable / Disable status of the Phone Information ICON */
		if ((g_Is_BLE_Settings_Selected_bool != FALSE) &&
			(g_Is_BLE_Connection_Established_bool != FALSE) &&
			(g_Is_BLE_Signal_Status_Received_bool != FALSE))
		{
			if (g_PreviousSignal_Value_U8 != g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR)
			{
				g_PreviousSignal_Value_U8 = g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR;
				if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR == 0x31)
				{
					/* Signal 1st Bar*/
					lv_obj_clear_flag(guider_ui.screen_Signal_1, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_Signal_1, &night_signal_1_bar);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR == 0x32)
				{
					/* Signal 2nd Bar*/
					lv_obj_clear_flag(guider_ui.screen_Signal_1, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_Signal_1, &night_signal_2bar);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR == 0x33)
				{
					/* Signal 3rd Bar*/
					lv_obj_clear_flag(guider_ui.screen_Signal_1, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_Signal_1, &night_signal_3bar);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR == 0x34)
				{
					/* Signal 4th Bar*/
					lv_obj_clear_flag(guider_ui.screen_Signal_1, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_Signal_1, &night_signal_4bar);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR == 0x30)
				{
					/* Signal Hide No value*/
					lv_obj_add_flag(guider_ui.screen_Signal_1, LV_OBJ_FLAG_HIDDEN);
				}
				else
				{
					/* Signal Hide No value*/
					lv_obj_add_flag(guider_ui.screen_Signal_1, LV_OBJ_FLAG_HIDDEN);
				}

				g_SignalScreen_bl = FALSE;
			}
			else
			{
				/* No Changes Here */
			}
		}
		else if (g_SignalScreen_bl == FALSE)
		{
			/* Signal Hide No value*/
			lv_obj_add_flag(guider_ui.screen_Signal_1, LV_OBJ_FLAG_HIDDEN);
			g_SignalScreen_bl = TRUE;
		}
		else
		{
			/* No Changes Here */
		}
	}
	else if (g_SignalScreen_bl == FALSE)
	{
		/* Signal Hide No value*/
		lv_obj_add_flag(guider_ui.screen_Signal_1, LV_OBJ_FLAG_HIDDEN);
		g_SignalScreen_bl = TRUE;
	}
	else
	{
		/* No Changes Here */
	}
}

uint8_t First_caller_name[18];
uint8_t First_call_status;
uint8_t Second_caller_name[18];
uint8_t Second_call_status;
uint8_t call_duration[6];
uint8_t PH_volume_level;

void GUI_Phone_SMS_info(void)
{
	HMI_unread_SMS_screen_info(&g_sms_info_ptr);

	if ((g_sms_info_ptr.Number_of_SMS[0] > 0 || g_sms_info_ptr.Number_of_SMS[1] > 0) && (g_SMS_bl == TRUE))
	{
		lv_obj_clear_flag(guider_ui.screen_blu_msg_icon, LV_OBJ_FLAG_HIDDEN);
		g_SMS_bl = FALSE;
	}
	else if ((g_sms_info_ptr.Number_of_SMS[0] == 0 || g_sms_info_ptr.Number_of_SMS[1] == 0) && (g_SMS_bl == FALSE))
	{
		lv_obj_add_flag(guider_ui.screen_blu_msg_icon, LV_OBJ_FLAG_HIDDEN);
		g_SMS_bl = TRUE;
	}
	else
	{
		/* Do Nothing */
	}
}

void GUI_Phone_Missed_call_Info(void)
{
	HMI_missed_call_screen_info(&g_missed_call_info_ptr);

	if ((g_missed_call_info_ptr.NUmber_of_missed_call[0] > 0 || g_missed_call_info_ptr.NUmber_of_missed_call[1] > 0) && (g_MIScall_bl == TRUE))
	{
		lv_obj_clear_flag(guider_ui.screen_blu_mis_call_icon, LV_OBJ_FLAG_HIDDEN);
		g_MIScall_bl = FALSE;
	}
	else if ((g_missed_call_info_ptr.NUmber_of_missed_call[0] == 0 || g_missed_call_info_ptr.NUmber_of_missed_call[1] == 0) && (g_MIScall_bl == FALSE))
	{
		lv_obj_add_flag(guider_ui.screen_blu_mis_call_icon, LV_OBJ_FLAG_HIDDEN);
		g_MIScall_bl = TRUE;
	}
	else
	{
		/* Mo Changes Here */
	}
}

void GUI_Phone_SMS_info_Day(void)
{
	HMI_unread_SMS_screen_info(&g_sms_info_ptr);

	if ((g_sms_info_ptr.Number_of_SMS[0] > 0 || g_sms_info_ptr.Number_of_SMS[1] > 0) && (g_SMS_bl == TRUE))
	{
		lv_obj_clear_flag(guider_ui.screen_day_msg_img, LV_OBJ_FLAG_HIDDEN);
		g_SMS_bl = FALSE;
	}
	else if ((g_sms_info_ptr.Number_of_SMS[0] == 0 || g_sms_info_ptr.Number_of_SMS[1] == 0) && (g_SMS_bl == FALSE))
	{
		lv_obj_add_flag(guider_ui.screen_day_msg_img, LV_OBJ_FLAG_HIDDEN);
		g_SMS_bl = TRUE;
	}
	else
	{
		/* Do Nothing */
	}
}

void GUI_Phone_Missed_call_Info_Day(void)
{
	HMI_missed_call_screen_info(&g_missed_call_info_ptr);

	if ((g_missed_call_info_ptr.NUmber_of_missed_call[0] > 0 || g_missed_call_info_ptr.NUmber_of_missed_call[1] > 0) && (g_MIScall_bl == TRUE))
	{
		lv_obj_clear_flag(guider_ui.screen_day_mis_call_img, LV_OBJ_FLAG_HIDDEN);
		g_MIScall_bl = FALSE;
	}
	else if ((g_missed_call_info_ptr.NUmber_of_missed_call[0] == 0 || g_missed_call_info_ptr.NUmber_of_missed_call[1] == 0) && (g_MIScall_bl == FALSE))
	{
		lv_obj_add_flag(guider_ui.screen_day_mis_call_img, LV_OBJ_FLAG_HIDDEN);
		g_MIScall_bl = TRUE;
	}
	else
	{
		/* Do Nothing */
	}
}

void GUI_Contact_screen_Night_Entry(void)
{

	lv_obj_move_foreground(guider_ui.screen_Trip_blank);
	lv_obj_clear_flag(guider_ui.screen_phone_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_call_btn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_phone_up_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_phone_down_arrow, LV_OBJ_FLAG_HIDDEN);

	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
	lv_obj_set_pos(guider_ui.screen_phone_call_btn, 146, 19);
	lv_obj_set_pos(guider_ui.screen_phone_lbl_1, 0, 20);

	/* CONTACT ICON */
	lv_img_set_src(guider_ui.screen_Trip_blank, &night_contact_30x30);

	lv_img_set_src(guider_ui.screen_Sub_Con, &subbtn_night_24x24);

	lv_obj_clear_flag(guider_ui.screen_Sub_Con, LV_OBJ_FLAG_HIDDEN);

	lv_obj_clear_flag(guider_ui.screen_phone_lbl_1, LV_OBJ_FLAG_HIDDEN);
	lv_label_set_text(guider_ui.screen_phone_lbl_1, "Contacts");
	lv_obj_set_style_text_color(guider_ui.screen_phone_lbl_1, lv_color_white(), 0);
	set_obj_opa_S(guider_ui.screen_phone_lbl_1, 0);

	lv_obj_add_flag(guider_ui.screen_phone_up_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_down_arrow, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_phone_lbl_2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);

	g_Get_Current_TripInfo_Time_Foramt = GUI_Get_Time_Format();

	if (g_Get_Current_TripInfo_Time_Foramt == CLOCK_12HR_FORMAT)
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

void GUI_Contact_screen__Night_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_phone_container, LV_OBJ_FLAG_HIDDEN);

}

void GUI_Contact_screen_Night_During(void)
{
	/* In contact main screen , Only contact text alone need to be shown. 
	 * No runtime change in screen */

}

void GUI_Volume_screen_Night_Entry(void)
{
	lv_obj_move_foreground(guider_ui.screen_Trip_blank);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
	lv_img_set_src(guider_ui.screen_Trip_blank, &_grp_night_common_30x30);

	lv_obj_clear_flag(guider_ui.screen_volume_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_volume_plus, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_volume_minus, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_volume_signbtn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_volume_base, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_pos(guider_ui.screen_volume_base, volume_pos[0], volume_pos[1]);
	lv_label_set_text(guider_ui.screen_volume_label, "VOLUME");
	lv_img_set_src(guider_ui.screen_volume_base, &volume_background_110x27);

	lv_obj_clear_flag(guider_ui.screen_Sub_Con, LV_OBJ_FLAG_HIDDEN);

	fl_Get_PssTime_Foramt = GUI_Get_Time_Format();

	if (fl_Get_PssTime_Foramt == CLOCK_12HR_FORMAT)
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

void GUI_Volume_screen_Night_During(void)
{

	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST fl_Music_volume_st = {0};

	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST fl_contact_volume_st = {0};

	/* GET MUSIC PKT */
	fl_Music_volume_st = UART_DataManager_Get_Connectivity_Info(MUSIC_PKT);

	/* GET CALL PKT */
	fl_contact_volume_st = UART_DataManager_Get_Connectivity_Info(CALL_STS_PKT);

	/* process volume data if status value are valid 
	 * Check Call or Music is Active and Assigh Volume */
	if (((fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 >= INCOMING_CALL_ACTIVE) && 
		(fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 <= OUT_GOING_CALL)) || 
		((fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 >= INCOMING_CALL_ACTIVE) && 
		(fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 <= OUT_GOING_CALL)) )
	{

		g_volume_value = fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.PH_VOLUME;
		
	}
	else if (fl_Music_volume_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_ACT_STATUS == MUSIC_ACTIVE)
	{
		g_volume_value = fl_Music_volume_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_VOLUME;
	}
	else
	{
		/* Do Nothing*/
	}

	switch (g_volume_value)
	{
	case 0x64:
		lv_img_set_src(guider_ui.screen_volume_base, &volume_background_110x27);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &mute_30x30);
		break;
	case 0x65:
		lv_img_set_src(guider_ui.screen_volume_base, &night_Volume_1);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x66:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_2);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x67:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_3);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x68:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_4);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x69:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_5);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x6A:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_6);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x6B:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_7);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x6C:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_8);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x6D:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_9);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x6E:
		lv_img_set_src(guider_ui.screen_volume_base, &v10_110x27);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	default:
		lv_img_set_src(guider_ui.screen_volume_base, &volume_background_110x27);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &mute_30x30);
		break;
	}	
}

void GUI_Volume_Screen_Night_Show_Entry(void)
{
	lv_obj_clear_flag(guider_ui.screen_volume_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_volume_plus, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_volume_minus, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_volume_signbtn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_volume_base, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
	lv_obj_set_pos(guider_ui.screen_volume_base, Day_volume_base_pos[0], Day_volume_base_pos[1]);
	lv_obj_add_flag(guider_ui.screen_Sub_Con, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_Sub_Con, LV_OBJ_FLAG_HIDDEN);

	lv_img_set_src(guider_ui.screen_volume_plus, &plus_white_11x11);
	lv_img_set_src(guider_ui.screen_volume_minus, &minus_white_11x3);
	lv_img_set_src(guider_ui.screen_Trip_blank, &_grp_night_common_30x30);
	lv_img_set_src(guider_ui.screen_Sub_Con, &_Layer_0_9x9);
	lv_img_set_src(guider_ui.screen_volume_base, &volume_background_110x27);
	lv_label_set_text(guider_ui.screen_volume_label, "");

	fl_Get_PssTime_Foramt = GUI_Get_Time_Format();

	if (fl_Get_PssTime_Foramt == CLOCK_12HR_FORMAT)
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

void GUI_Volume_Screen_Night_Show_Exit(void)
{
	/* Hide volume screen container*/
	lv_obj_add_flag(guider_ui.screen_volume_container, LV_OBJ_FLAG_HIDDEN);
}

void GUI_Volume_Screen_Night_Show_During(void)
{

	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST fl_Music_volume_st = {0};

	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST fl_contact_volume_st = {0};

	/* GET MUSIC PKT */
	fl_Music_volume_st = UART_DataManager_Get_Connectivity_Info(MUSIC_PKT);

	/* GET CALL PKT */
	fl_contact_volume_st = UART_DataManager_Get_Connectivity_Info(CALL_STS_PKT);

	/* process volume data if status value are valid 
	 * Check Call or Music is Active and Assigh Volume */
	if (((fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 >= INCOMING_CALL_ACTIVE) && 
		(fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 <= OUT_GOING_CALL)) || 
		((fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 >= INCOMING_CALL_ACTIVE) && 
		(fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 <= OUT_GOING_CALL)) )
	{
	
		g_volume_value = fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.PH_VOLUME;
	}
	else if (fl_Music_volume_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_ACT_STATUS == MUSIC_ACTIVE)
	{
		g_volume_value = fl_Music_volume_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_VOLUME;
	}
	else
	{
		/* Do Nothing*/
	}

	switch (g_volume_value)
	{
	case 0x64:
		lv_img_set_src(guider_ui.screen_volume_base, &volume_background_110x27);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &mute_30x30);
		break;
	case 0x65:
		lv_img_set_src(guider_ui.screen_volume_base, &night_Volume_1);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x66:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_2);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x67:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_3);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x68:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_4);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x69:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_5);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x6A:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_6);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x6B:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_7);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x6C:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_8);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x6D:
		lv_img_set_src(guider_ui.screen_volume_base, &night_volume_9);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	case 0x6E:
		lv_img_set_src(guider_ui.screen_volume_base, &v10_110x27);
		lv_obj_set_pos(guider_ui.screen_volume_base, 25, 25);
		lv_obj_set_size(guider_ui.screen_volume_base, 110, 27);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &unmute_30x30);
		break;
	default:
		lv_img_set_src(guider_ui.screen_volume_base, &volume_background_110x27);
		lv_img_set_src(guider_ui.screen_volume_signbtn, &mute_30x30);
		break;
	}

	/* Chang Color For Volume Button If It is Pressed */

	switch (g_DownKeypressed_U8)
	{
	case Pressed_State:
		lv_img_set_src(guider_ui.screen_volume_minus, &volume_minus_ornage);
		g_DownKeypressed_U8 = 2;
		break;
	case UnPressed_State:
		lv_img_set_src(guider_ui.screen_volume_minus, &minus_white_11x3);
		g_DownKeypressed_U8 = 0;
		break;
	default:
		g_DownKeypressed_U8 = 0;
		break;
	}

	/* Chang Color For Volume Button If It is Pressed */

	switch (g_UpKeypressed_U8)
	{
	case Pressed_State:
		lv_img_set_src(guider_ui.screen_volume_plus, &volume_plus_orange);
		g_UpKeypressed_U8 = 2;
		break;
	case UnPressed_State:
		lv_img_set_src(guider_ui.screen_volume_plus, &plus_white_11x11);
		g_UpKeypressed_U8 = 0;
		break;
	default:
		g_UpKeypressed_U8 = 0;
		break;
	}

	/* Revert Volume Screen To CALL */
	if (g_VolumeCounter_U8 == VOLUMESCREEN_TIMEOUT)
	{
		g_VolumeCounter_U8 = 0;
		g_VolumeEvent_Bl = FALSE;
		Set_Event(BLE_CALL_EVENT);
	}
	else if (g_VolumeEvent_Bl == TRUE)
	{
		g_VolumeCounter_U8++;
	}
	else if (g_VolumeEvent_Bl == TRUE && g_VolumeCounter_U8 < VOLUMESCREEN_TIMEOUT)
	{
		g_VolumeCounter_U8 = 0;
	}
	else
	{
		/* Do Nothing */
	}
}

void GUI_Volume_screen_Night_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_volume_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Sub_Con, LV_OBJ_FLAG_HIDDEN);
}


/*Phone*/
void GUI_Phone_Screen_Main_Day_Mode_Entry(void)
{
	lv_obj_clear_flag(guider_ui.screen_Main_day_phone_container, LV_OBJ_FLAG_HIDDEN);

	lv_label_set_text(guider_ui.screen_Day_phone_lbl_1, "Contacts");
	lv_label_set_text(guider_ui.screen_Day_phone_lbl_2, "");
	lv_obj_add_flag(guider_ui.screen_Day_phone_up_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_down_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_phone_lbl_1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_call_btn, LV_OBJ_FLAG_HIDDEN);
	lv_img_set_src(guider_ui.screen_Trip_blank, &contact_day_icon);
	lv_obj_set_pos(guider_ui.screen_Day_phone_lbl_1, New_contact_pos[0], New_contact_pos[1]);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

	lv_obj_clear_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_phone_lbl_2, LV_OBJ_FLAG_HIDDEN);

	lv_obj_move_foreground(guider_ui.screen_Trip_blank);

}

void GUI_Phone_Screen_Main_Day_Mode_During(void)
{

}

void GUI_Phone_Screen_Main_Day_Mode_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_Main_day_phone_container, LV_OBJ_FLAG_HIDDEN);
}
/*Phone Sub Screen*/
void GUI_Phone_Sub_Screen_Main_Day_Mode_Entry(void)
{
	lv_obj_clear_flag(guider_ui.screen_Main_day_phone_container, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
}

void GUI_Phone_Sub_Screen_Main_Day_Mode_During(void)
{
	lv_obj_clear_flag(guider_ui.screen_Day_phone_lbl_2, LV_OBJ_FLAG_HIDDEN);
	lv_label_set_text(guider_ui.screen_Day_phone_lbl_2, "Name");
	lv_obj_set_pos(guider_ui.screen_Day_phone_lbl_2, 40, 30);
	lv_obj_set_size(guider_ui.screen_Day_phone_lbl_2, 100, 12);

	lv_obj_clear_flag(guider_ui.screen_day_Trip_up_arr, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_day_Trip_down_arr, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_Day_phone_lbl_1, LV_OBJ_FLAG_HIDDEN);

	lv_obj_clear_flag(guider_ui.screen_Day_phone_up_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_phone_down_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_phone_call_btn, LV_OBJ_FLAG_HIDDEN);
	lv_img_set_src(guider_ui.screen_Trip_blank, &img_day_contacts_icon);
	lv_obj_move_background(guider_ui.screen_Trip_blank);
	lv_obj_add_flag(guider_ui.screen_phone_lbl_1, LV_OBJ_FLAG_HIDDEN);
	lv_img_set_src(guider_ui.screen_Day_phone_up_arrow, &img_day_trip_up_arrow_normal);
	lv_img_set_src(guider_ui.screen_Day_phone_down_arrow, &img_day_trip_down_arrow_normal);
}

void GUI_Phone_Sub_Screen_Main_Day_Mode_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_Main_day_phone_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_day_base_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_dat_inter_con, LV_OBJ_FLAG_HIDDEN);
}

void GUI_Phone_Contact_List_Night_Entry(void)
{
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

	lv_obj_clear_flag(guider_ui.screen_phone_container, LV_OBJ_FLAG_HIDDEN);

	lv_img_set_src(guider_ui.screen_Trip_blank, &night_contact_30x30);

	lv_obj_add_flag(guider_ui.screen_phone_lbl_2, LV_OBJ_FLAG_HIDDEN);
	lv_label_set_text(guider_ui.screen_phone_lbl_1, "Contact");

	lv_obj_add_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);

	lv_obj_clear_flag(guider_ui.screen_phone_call_btn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_pos(guider_ui.screen_phone_call_btn, 146, 19);
	lv_obj_set_size(guider_ui.screen_phone_call_btn, 30, 30);
	lv_img_set_src(guider_ui.screen_phone_call_btn, &_img_night_contacts_l1_call_icon_30x30);

	lv_obj_clear_flag(guider_ui.screen_phone_up_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_phone_down_arrow, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_Sub_Con, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_pos(guider_ui.screen_phone_lbl_1, 0, 20);


	lv_img_set_src(guider_ui.screen_phone_down_arrow, &_Setting_Drow_Arrow_12x7);
	lv_img_set_src(guider_ui.screen_phone_up_arrow, &_Setting_Up_Arrow_12x7);

	fl_Get_PssTime_Foramt = GUI_Get_Time_Format();

	if (fl_Get_PssTime_Foramt == CLOCK_12HR_FORMAT)
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

void GUI_Phone_Contact_List_Night_During(void)
{

	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST fl_call_num_st = {0};

	/* GET CALL  NUM PKT */
	fl_call_num_st = UART_DataManager_Get_Connectivity_Info(CALL_NUM_PKT);

	for (g_charIndex_U8 = 0; g_charIndex_U8 < UART_ARRAY_LENGTH_MAX; g_charIndex_U8++)
	{
		contact_num_str0[g_charIndex_U8] = fl_call_num_st.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_1[g_charIndex_U8];
		contact_num_str1[g_charIndex_U8] = fl_call_num_st.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_2[g_charIndex_U8];
		contact_num_str2[g_charIndex_U8] = fl_call_num_st.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_3[g_charIndex_U8];
		contact_num_str3[g_charIndex_U8] = fl_call_num_st.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_4[g_charIndex_U8];
		contact_num_str4[g_charIndex_U8] = fl_call_num_st.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_5[g_charIndex_U8];
	}

	switch (g_Main_Phone_Sub_Screen_Sel_Cnt_U8)
	{
	case 1:
		lv_label_set_text(guider_ui.screen_phone_lbl_1, contact_num_str0);

		break;
	case 2:
		lv_label_set_text(guider_ui.screen_phone_lbl_1, contact_num_str1);

		break;
	case 3:
		lv_label_set_text(guider_ui.screen_phone_lbl_1, contact_num_str2);

		break;
	case 4:
		lv_label_set_text(guider_ui.screen_phone_lbl_1, contact_num_str3);

		break;
	case 5:
		lv_label_set_text(guider_ui.screen_phone_lbl_1, contact_num_str4);

		break;
	case 6:
		lv_label_set_text(guider_ui.screen_phone_lbl_1, contact_num_str5);

		break;

	default:
		lv_label_set_text(guider_ui.screen_phone_lbl_1, "No Contact");

		break;
	}

	fl_Get_PssTime_Foramt = GUI_Get_Time_Format();

	if (fl_Get_PssTime_Foramt == CLOCK_12HR_FORMAT)
	{
		GUI_Main12hr_position();
		GUI_Intermediate12hr_position();
	}
	else
	{
		GUI_Main24hr_position();
		GUI_Intermediate24hr_position();
	}

	/* Chang Color For Arrow If It is Pressed */

	switch (g_DownKeypressed_U8)
	{
	case Pressed_State:
		lv_img_set_src(guider_ui.screen_phone_down_arrow, &orange_down_icon_pressed);
		g_DownKeypressed_U8 = 2;
		break;
	case UnPressed_State:
		lv_img_set_src(guider_ui.screen_phone_down_arrow, &_Setting_Drow_Arrow_12x7);
		g_DownKeypressed_U8 = 0;
		break;
	default:
		g_DownKeypressed_U8 = 0;
		break;
	}

	/* Chang Color For Arrow If It is Pressed */

	switch (g_UpKeypressed_U8)
	{
	case Pressed_State:
		lv_img_set_src(guider_ui.screen_phone_up_arrow, &orange_up_icon_pressed);
		g_UpKeypressed_U8 = 2;
		break;
	case UnPressed_State:
		lv_img_set_src(guider_ui.screen_phone_up_arrow, &_Setting_Up_Arrow_12x7);
		g_UpKeypressed_U8 = 0;
		break;
	default:
		g_UpKeypressed_U8 = 0;
		break;
	}

	/* Chang Color For Call Btn If It is Pressed */

	switch (g_RightKeypressed_Call_U8)
	{
	case Pressed_State:
		lv_img_set_src(guider_ui.screen_phone_call_btn, &call_icon_pressed);
		g_RightKeypressed_Call_U8 = 2;
		break;
	case UnPressed_State:
		lv_img_set_src(guider_ui.screen_phone_call_btn, &_img_night_contacts_l1_call_icon_30x30);
		g_RightKeypressed_Call_U8 = 0;
		break;
	default:
		g_RightKeypressed_Call_U8 = 0;
		break;
	}
}

void GUI_phone_Contact_List_Night_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_phone_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_up_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_down_arrow, LV_OBJ_FLAG_HIDDEN);
}


void GUI_Phone_Contact_Call_Night_Entry(void)
{
	GUI_Clock_Entry();

	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
	lv_obj_add_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_call_btn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_up_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_down_arrow, LV_OBJ_FLAG_HIDDEN);

	lv_obj_clear_flag(guider_ui.screen_phone_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Sub_Con, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_Trip_blank, LV_OBJ_FLAG_HIDDEN);

	lv_img_set_src(guider_ui.screen_phone_btn1, &_img_night_call_declined_decline_30x30);
	lv_img_set_src(guider_ui.screen_phone_btn2, &_img_night_call_declined_decline_30x30);
	lv_img_set_src(guider_ui.screen_phone_btn3, &call_accept_darkgreen_icon);

	fl_Get_PssTime_Foramt = GUI_Get_Time_Format();

	if (fl_Get_PssTime_Foramt == CLOCK_12HR_FORMAT)
	{
		GUI_Main12hr_position();
		GUI_Intermediate12hr_position();
	}
	else
	{
		GUI_Main24hr_position();
		GUI_Intermediate24hr_position();
	}

	g_PhoneCounter_U8 = 0;
}

void GUI_Phone_Contact_Call_Night_During(void)
{

	g_Get_Screen_Callsts_str = UART_DataManager_Get_Connectivity_Info(CALL_STS_PKT);

	HMI_active_call_screen_info(&g_contact_info_st_ptr);

	for (g_charIndex_U8 = 0; g_charIndex_U8 < UART_ARRAY_LENGTH_MAX; g_charIndex_U8++)
	{
		contact_number1_str[g_charIndex_U8] = ((char)g_contact_info_st_ptr.First_caller_name[g_charIndex_U8]);
		contact_number2_str = ((char)g_contact_info_st_ptr.First_call_status);
		contact_number3_str[g_charIndex_U8] = ((char)g_contact_info_st_ptr.Second_caller_name[g_charIndex_U8]);
		contact_number4_str = ((char)g_contact_info_st_ptr.Second_call_status);
		contact_number6_str = ((char)g_contact_info_st_ptr.PH_volume_level);

		if (g_charIndex_U8 < HMI_CONTACT_NAME_LENGTH_MAX)
		{
			CALLER_NAME_1_str[g_charIndex_U8] = ((char)g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALLER_NUM_NAME_1[g_charIndex_U8]);
			CALLER_NAME_2_str[g_charIndex_U8] = ((char)g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALLER_NUM_NAME_2[g_charIndex_U8]);
		}
		else if (g_charIndex_U8 < HMI_CONTACT_NAME_TOTAL_LENGTH)
		{
			CALLER_NAME_1_str[g_charIndex_U8] = '.';
			CALLER_NAME_2_str[g_charIndex_U8] = '.';
		}
		else
		{
			/* Do Nothing */
		}
	}

	lv_obj_clear_flag(guider_ui.screen_phone_lbl_1, LV_OBJ_FLAG_HIDDEN);

	lv_obj_clear_flag(guider_ui.screen_phone_lbl_2, LV_OBJ_FLAG_HIDDEN);
	lv_label_set_text(guider_ui.screen_phone_lbl_1, contact_number1_str);
	lv_label_set_text(guider_ui.screen_phone_lbl_1, contact_number3_str);

	if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == NO_CALL_ACTIVITY)
	{
		lv_label_set_text(guider_ui.screen_phone_lbl_1, CALLER_NAME_1_str);
		if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == OUT_GOING_CALL)
		{
			lv_label_set_text(guider_ui.screen_phone_lbl_2, "Dialling");
			lv_obj_add_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == CALL_IS_UNDER_HOLD)
		{
			lv_label_set_text(guider_ui.screen_phone_lbl_2, "Hold");
			lv_obj_add_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == INCOMING_CALL_ACTIVE)
		{
			lv_label_set_text(guider_ui.screen_phone_lbl_2, "Incoming");
			lv_obj_clear_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == CALL_FAILED)
		{
			lv_label_set_text(guider_ui.screen_phone_lbl_1, "Call Failed");
			lv_label_set_text(guider_ui.screen_phone_lbl_2, "");
			lv_obj_add_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == CALL_IS_CRNTLY_ACTIVE)
		{
			/* Display call duration value received from APP with colon */
			lv_label_set_text_fmt(guider_ui.screen_phone_lbl_2, "%c%c%c%c%c%c%c%c", ((char)g_contact_info_st_ptr.call_duration[0]),
								  ((char)g_contact_info_st_ptr.call_duration[1]), ':',
								  ((char)g_contact_info_st_ptr.call_duration[2]),
								  ((char)g_contact_info_st_ptr.call_duration[3]), ':',
								  ((char)g_contact_info_st_ptr.call_duration[4]),
								  ((char)g_contact_info_st_ptr.call_duration[5]));
			lv_obj_add_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else
		{
			lv_label_set_text(guider_ui.screen_phone_lbl_2, "Dialling");
			lv_obj_add_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
	}
	else
	{
		lv_label_set_text(guider_ui.screen_phone_lbl_1, CALLER_NAME_2_str);
		if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == OUT_GOING_CALL)
		{
			lv_label_set_text(guider_ui.screen_phone_lbl_2, "Dialling");
			lv_obj_add_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == CALL_IS_UNDER_HOLD)
		{
			lv_label_set_text(guider_ui.screen_phone_lbl_2, "Hold");
			lv_obj_add_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == INCOMING_CALL_ACTIVE)
		{
			lv_label_set_text(guider_ui.screen_phone_lbl_2, "Incoming");
			lv_obj_clear_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == CALL_FAILED)
		{
			lv_label_set_text(guider_ui.screen_phone_lbl_1, "Call Failed");
			lv_label_set_text(guider_ui.screen_phone_lbl_2, "");
			lv_obj_add_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == CALL_IS_CRNTLY_ACTIVE)
		{
			/* Display call duration value received from APP with colon */
			lv_label_set_text_fmt(guider_ui.screen_phone_lbl_2, "%c%c%c%c%c%c%c%c", ((char)g_contact_info_st_ptr.call_duration[0]),
								  ((char)g_contact_info_st_ptr.call_duration[1]), ':',
								  ((char)g_contact_info_st_ptr.call_duration[2]),
								  ((char)g_contact_info_st_ptr.call_duration[3]), ':',
								  ((char)g_contact_info_st_ptr.call_duration[4]),
								  ((char)g_contact_info_st_ptr.call_duration[5]));
			lv_obj_add_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else
		{
			lv_label_set_text(guider_ui.screen_phone_lbl_2, "Dialling");
			lv_obj_add_flag(guider_ui.screen_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
	}

	lv_obj_set_pos(guider_ui.screen_phone_lbl_1, 0, 0);
	lv_obj_set_pos(guider_ui.screen_phone_lbl_2, contact_pos[0], contact_pos[1]);

	/* Chang Color For Arrow If It is Pressed */

	switch (g_RightKeypressed_U8)
	{
	case Pressed_State:
		lv_img_set_src(guider_ui.screen_phone_btn1, &decline_icon_pressed);
		lv_img_set_src(guider_ui.screen_phone_btn2, &decline_icon_pressed);
		g_RightKeypressed_U8 = 2;
		break;
	case UnPressed_State:
		lv_img_set_src(guider_ui.screen_phone_btn1, &_img_night_call_declined_decline_30x30);
		lv_img_set_src(guider_ui.screen_phone_btn2, &_img_night_call_declined_decline_30x30);
		g_RightKeypressed_U8 = 0;
		break;
	default:
		g_RightKeypressed_U8 = 0;
		break;
	}

	/* Chang Color For Arrow If It is Pressed */

	switch (g_LeftKeypressed_U8)
	{
	case Pressed_State:
		lv_img_set_src(guider_ui.screen_phone_btn3, &call_accept_icon_pressed);
		g_LeftKeypressed_U8 = 2;
		break;
	case UnPressed_State:
		lv_img_set_src(guider_ui.screen_phone_btn3, &call_accept_darkgreen_icon);
		g_LeftKeypressed_U8 = 0;
		break;
	default:
		g_LeftKeypressed_U8 = 0;
		break;
	}

	/* 5 Sec After CALL Failed Retrive to Main Screen*/
	if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == CALL_FAILED || g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == CALL_FAILED)
	{
		/* Revert Volume Screen To CALL */
		if (g_PhoneCounter_U8 == PHONESCREEN_TIMEOUT)
		{
			g_PhoneCounter_U8 = 0;
			Set_Event(LEFT_BUTTON_LONG_PRESS);
		}
		else
		{
			g_PhoneCounter_U8++;
		}
	}
	else
	{
		/* Do Nothing */
	}
}

void GUI_Phone_Contact_Call_Night_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_phone_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Trip_blank, LV_OBJ_FLAG_HIDDEN);
}

  /*Phone Day */
void GUI_Phone_Contact_List_Day_Entry(void)
{
	lv_obj_clear_flag(guider_ui.screen_Main_day_phone_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_phone_up_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_phone_down_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);

	lv_label_set_text(guider_ui.screen_Day_phone_lbl_2, "");
	lv_obj_clear_flag(guider_ui.screen_Day_phone_call_btn, LV_OBJ_FLAG_HIDDEN);

	lv_obj_set_pos(guider_ui.screen_Day_phone_lbl_1, 0, 20);

	lv_img_set_src(guider_ui.screen_Day_phone_down_arrow, &img_day_trip_down_arrow_normal);
	lv_img_set_src(guider_ui.screen_Day_phone_up_arrow, &img_day_trip_up_arrow_normal);
	lv_img_set_src(guider_ui.screen_Day_phone_call_btn, &_img_night_contacts_l1_call_icon_30x30);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

	lv_img_set_src(guider_ui.screen_Trip_blank, &contact_day_icon);
	lv_obj_move_foreground(guider_ui.screen_Trip_blank);

}

void GUI_Phone_Contact_List_Day_During(void)
{
	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST fl_call_num_st = {0};

	/* GET CALL  NUM PKT */
	fl_call_num_st = UART_DataManager_Get_Connectivity_Info(CALL_NUM_PKT);

	for (g_charIndex_U8 = 0; g_charIndex_U8 < UART_ARRAY_LENGTH_MAX; g_charIndex_U8++)
	{
		contact_num_str0[g_charIndex_U8] = fl_call_num_st.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_1[g_charIndex_U8];
		contact_num_str1[g_charIndex_U8] = fl_call_num_st.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_2[g_charIndex_U8];
		contact_num_str2[g_charIndex_U8] = fl_call_num_st.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_3[g_charIndex_U8];
		contact_num_str3[g_charIndex_U8] = fl_call_num_st.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_4[g_charIndex_U8];
		contact_num_str4[g_charIndex_U8] = fl_call_num_st.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_5[g_charIndex_U8];
	}

	switch (g_Main_Phone_Sub_Screen_Sel_Cnt_U8)
	{
	case 1:
		lv_label_set_text(guider_ui.screen_Day_phone_lbl_1, contact_num_str0);

		break;
	case 2:
		lv_label_set_text(guider_ui.screen_Day_phone_lbl_1, contact_num_str1);

		break;
	case 3:
		lv_label_set_text(guider_ui.screen_Day_phone_lbl_1, contact_num_str2);

		break;
	case 4:
		lv_label_set_text(guider_ui.screen_Day_phone_lbl_1, contact_num_str3);

		break;
	case 5:
		lv_label_set_text(guider_ui.screen_Day_phone_lbl_1, contact_num_str4);

		break;
	case 6:
		lv_label_set_text(guider_ui.screen_Day_phone_lbl_1, contact_num_str5);

		break;

	default:
		lv_label_set_text(guider_ui.screen_Day_phone_lbl_1, "No Contact");
		// g_Phone_Sub_Screen_Sel_Cnt_U8 =1;
		break;
	}

	/* Chang Color For Arrow If It is Pressed */

	switch (g_DownKeypressed_U8)
	{
	case Pressed_State:
		lv_img_set_src(guider_ui.screen_Day_phone_down_arrow, &orange_down_icon_pressed);
		g_DownKeypressed_U8 = 2;
		break;
	case UnPressed_State:
		lv_img_set_src(guider_ui.screen_Day_phone_down_arrow, &img_day_trip_down_arrow_normal);
		g_DownKeypressed_U8 = 0;
		break;
	default:
		g_DownKeypressed_U8 = 0;
		break;
	}

	/* Chang Color For Arrow If It is Pressed */

	switch (g_UpKeypressed_U8)
	{
	case Pressed_State:
		lv_img_set_src(guider_ui.screen_Day_phone_up_arrow, &orange_up_icon_pressed);
		g_UpKeypressed_U8 = 2;
		break;
	case UnPressed_State:
		lv_img_set_src(guider_ui.screen_Day_phone_up_arrow, &img_day_trip_up_arrow_normal);
		g_UpKeypressed_U8 = 0;
		break;
	default:
		g_UpKeypressed_U8 = 0;
		break;
	}

	/* Chang Color For Call Btn If It is Pressed */

	switch (g_RightKeypressed_Call_U8)
	{
	case Pressed_State:
		lv_img_set_src(guider_ui.screen_Day_phone_call_btn, &call_icon_pressed);
		g_RightKeypressed_Call_U8 = 2;
		break;
	case UnPressed_State:
		lv_img_set_src(guider_ui.screen_Day_phone_call_btn, &_img_night_contacts_l1_call_icon_30x30);
		g_RightKeypressed_Call_U8 = 0;
		break;
	default:
		g_RightKeypressed_Call_U8 = 0;
		break;
	}
}

void GUI_Phone_contact_List_Day_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_Main_day_phone_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_up_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_down_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_call_btn, LV_OBJ_FLAG_HIDDEN);
}

void GUI_Phone_Contact_Call_Day_Entry(void)
{
	GUI_Clock_Entry();

	lv_obj_clear_flag(guider_ui.screen_Main_day_phone_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_up_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_down_arrow, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);

	lv_label_set_text(guider_ui.screen_Day_phone_lbl_2, "");
	lv_obj_add_flag(guider_ui.screen_Day_phone_call_btn, LV_OBJ_FLAG_HIDDEN);

	lv_obj_clear_flag(guider_ui.screen_Day_phone_lbl_1, LV_OBJ_FLAG_HIDDEN);

	lv_obj_clear_flag(guider_ui.screen_Day_phone_lbl_2, LV_OBJ_FLAG_HIDDEN);

	lv_obj_set_pos(guider_ui.screen_Day_phone_lbl_2, contact_pos[0], contact_pos[1]);
	lv_obj_set_pos(guider_ui.screen_Day_phone_lbl_1, Day_contact_pos_new[0], Day_contact_pos_new[1]);

	lv_obj_clear_flag(guider_ui.screen_Day_phone_lbl_1, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_Trip_blank, LV_OBJ_FLAG_HIDDEN);

	lv_img_set_src(guider_ui.screen_Day_phone_btn1, &_img_night_call_declined_decline_30x30);
	lv_img_set_src(guider_ui.screen_Day_phone_btn2, &_img_night_call_declined_decline_30x30);
	lv_img_set_src(guider_ui.screen_Day_phone_btn3, &call_accept_darkgreen_icon);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

	g_PhoneCounter_U8 = 0;
}

void GUI_Phone_Contact_Call_Day_During(void)
{

	g_Get_Screen_Callsts_str = UART_DataManager_Get_Connectivity_Info(CALL_STS_PKT);
	lv_obj_set_pos(guider_ui.screen_Day_phone_lbl_1, 0, 0);
	HMI_active_call_screen_info(&g_contact_info_st_ptr);

	for (g_charIndex_U8 = 0; g_charIndex_U8 < UART_ARRAY_LENGTH_MAX; g_charIndex_U8++)
	{
		contact_number1_str[g_charIndex_U8] = ((char)g_contact_info_st_ptr.First_caller_name[g_charIndex_U8]);
		contact_number2_str = ((char)g_contact_info_st_ptr.First_call_status);
		contact_number3_str[g_charIndex_U8] = ((char)g_contact_info_st_ptr.Second_caller_name[g_charIndex_U8]);
		contact_number4_str = ((char)g_contact_info_st_ptr.Second_call_status);
		contact_number6_str = ((char)g_contact_info_st_ptr.PH_volume_level);

		if (g_charIndex_U8 < HMI_CONTACT_NAME_LENGTH_MAX)
		{
			CALLER_NAME_1_str[g_charIndex_U8] = ((char)g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALLER_NUM_NAME_1[g_charIndex_U8]);
			CALLER_NAME_2_str[g_charIndex_U8] = ((char)g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALLER_NUM_NAME_2[g_charIndex_U8]);
		}
		else if (g_charIndex_U8 < HMI_CONTACT_NAME_TOTAL_LENGTH)
		{
			CALLER_NAME_1_str[g_charIndex_U8] = '.';
			CALLER_NAME_2_str[g_charIndex_U8] = '.';
		}
		else
		{
			/* Do Nothing */
		}
	}

	if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == NO_CALL_ACTIVITY)
	{
		lv_label_set_text(guider_ui.screen_Day_phone_lbl_1, CALLER_NAME_1_str);
		if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == OUT_GOING_CALL)
		{
			lv_label_set_text(guider_ui.screen_Day_phone_lbl_2, "Dialling");
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == CALL_IS_UNDER_HOLD)
		{
			lv_label_set_text(guider_ui.screen_Day_phone_lbl_2, "Hold");
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == INCOMING_CALL_ACTIVE)
		{
			lv_label_set_text(guider_ui.screen_Day_phone_lbl_2, "Incoming");
			lv_obj_clear_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == CALL_FAILED)
		{
			lv_label_set_text(guider_ui.screen_Day_phone_lbl_1, "Call Failed");
			lv_label_set_text(guider_ui.screen_Day_phone_lbl_2, "");
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == CALL_IS_CRNTLY_ACTIVE)
		{
			/* Display call duration value received from APP with colon */
			lv_label_set_text_fmt(guider_ui.screen_Day_phone_lbl_2, "%c%c%c%c%c%c%c%c", ((char)g_contact_info_st_ptr.call_duration[0]),
								  ((char)g_contact_info_st_ptr.call_duration[1]), ':',
								  ((char)g_contact_info_st_ptr.call_duration[2]),
								  ((char)g_contact_info_st_ptr.call_duration[3]), ':',
								  ((char)g_contact_info_st_ptr.call_duration[4]),
								  ((char)g_contact_info_st_ptr.call_duration[5]));
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else
		{
			lv_label_set_text(guider_ui.screen_Day_phone_lbl_2, "Dialling");
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
	}
	else
	{
		lv_label_set_text(guider_ui.screen_Day_phone_lbl_1, CALLER_NAME_2_str);
		if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == OUT_GOING_CALL)
		{
			lv_label_set_text(guider_ui.screen_Day_phone_lbl_2, "Dialling");
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == CALL_IS_UNDER_HOLD)
		{
			lv_label_set_text(guider_ui.screen_Day_phone_lbl_2, "Hold");
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}

		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == INCOMING_CALL_ACTIVE)
		{
			lv_label_set_text(guider_ui.screen_Day_phone_lbl_2, "Incoming");
			lv_obj_clear_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == CALL_FAILED)
		{
			lv_label_set_text(guider_ui.screen_Day_phone_lbl_1, "Call Failed");
			lv_label_set_text(guider_ui.screen_Day_phone_lbl_2, "");
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == CALL_IS_CRNTLY_ACTIVE)
		{
			/* Display call duration value received from APP with colon */
			lv_label_set_text_fmt(guider_ui.screen_Day_phone_lbl_2, "%c%c%c%c%c%c%c%c", ((char)g_contact_info_st_ptr.call_duration[0]),
								  ((char)g_contact_info_st_ptr.call_duration[1]), ':',
								  ((char)g_contact_info_st_ptr.call_duration[2]),
								  ((char)g_contact_info_st_ptr.call_duration[3]), ':',
								  ((char)g_contact_info_st_ptr.call_duration[4]),
								  ((char)g_contact_info_st_ptr.call_duration[5]));
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
		else
		{
			lv_label_set_text(guider_ui.screen_Day_phone_lbl_2, "Dialling");
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
		}
	}

	/* Chang Color For Arrow If It is Pressed */

	switch (g_RightKeypressed_U8)
	{
	case Pressed_State:
		lv_img_set_src(guider_ui.screen_Day_phone_btn1, &decline_icon_pressed);
		lv_img_set_src(guider_ui.screen_Day_phone_btn2, &decline_icon_pressed);
		g_RightKeypressed_U8 = 2;
		break;
	case UnPressed_State:
		lv_img_set_src(guider_ui.screen_Day_phone_btn1, &_img_night_call_declined_decline_30x30);
		lv_img_set_src(guider_ui.screen_Day_phone_btn2, &_img_night_call_declined_decline_30x30);
		g_RightKeypressed_U8 = 0;
		break;
	default:
		g_RightKeypressed_U8 = 0;
		break;
	}

	/* Chang Color For Arrow If It is Pressed */

	switch (g_LeftKeypressed_U8)
	{
	case Pressed_State:
		lv_img_set_src(guider_ui.screen_Day_phone_btn3, &call_accept_icon_pressed);
		g_LeftKeypressed_U8 = 2;
		break;
	case UnPressed_State:
		lv_img_set_src(guider_ui.screen_Day_phone_btn3, &call_accept_darkgreen_icon);
		g_LeftKeypressed_U8 = 0;
		break;
	default:
		g_LeftKeypressed_U8 = 0;
		break;
	}

	/* 5 Sec After CALL Failed Retrive to Main Screen*/
	if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == CALL_FAILED || g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == CALL_FAILED)
	{
		/* Revert Volume Screen To CALL */
		if (g_PhoneCounter_U8 == PHONESCREEN_TIMEOUT)
		{
			g_PhoneCounter_U8 = 0;
			Set_Event(LEFT_BUTTON_LONG_PRESS);
		}
		else
		{
			g_PhoneCounter_U8++;
		}
	}
	else
	{
		/* Do Nothing */
	}
}

void GUI_Phone_Contact_Call_Day_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_Main_day_phone_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_up_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_down_arrow, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_btn1, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_btn2, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_btn3, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_phone_call_btn, LV_OBJ_FLAG_HIDDEN);

	lv_obj_clear_flag(guider_ui.screen_Trip_blank, LV_OBJ_FLAG_HIDDEN);
}

    /*Volume*/
void GUI_Volume_Screen_Main_Day_Mode_Entry(void)
{
	lv_obj_clear_flag(guider_ui.screen_Main_day_volume_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_volume_label, LV_OBJ_FLAG_HIDDEN);

	lv_obj_set_pos(guider_ui.screen_Day_volume_base, Day_volume_pos[0], Day_volume_pos[1]);

	lv_obj_clear_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);

	lv_label_set_text(guider_ui.screen_Day_volume_label, "VOLUME");
	lv_img_set_src(guider_ui.screen_Day_volume_base, &img_day_volume_bar_base);
	lv_img_set_src(guider_ui.screen_Trip_blank, &music_day_icon);
	lv_obj_move_foreground(guider_ui.screen_Trip_blank);
	lv_obj_add_flag(guider_ui.screen_Day_volume_signbtn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

}

void GUI_Volume_Screen_Main_Day_Mode_During(void)
{

	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST fl_Music_volume_st = {0};

	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST fl_contact_volume_st = {0};

	/* GET MUSIC PKT */
	fl_Music_volume_st = UART_DataManager_Get_Connectivity_Info(MUSIC_PKT);

	/* GET CALL PKT */
	fl_contact_volume_st = UART_DataManager_Get_Connectivity_Info(CALL_STS_PKT);

	/* process volume data if status value are valid 
	 * Check Call or Music is Active and Assigh Volume */
	if (((fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 >= INCOMING_CALL_ACTIVE) && 
		(fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 <= OUT_GOING_CALL)) || 
		((fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 >= INCOMING_CALL_ACTIVE) && 
		(fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 <= OUT_GOING_CALL)) )
	{
		g_volume_value = fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.PH_VOLUME;
	}
	else if (fl_Music_volume_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_ACT_STATUS == MUSIC_ACTIVE)
	{
		g_volume_value = fl_Music_volume_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_VOLUME;
	}
	else
	{
		/* Do Nothing*/
	}

	switch (g_volume_value)
	{
	case 0x64:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_base);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, volume_pos[0], volume_pos[1]);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 110, 27);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_mute_icon_btn);
		break;
	case 0x65:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_1);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 40, 63);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 11, 3);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x66:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_2);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 40, 60);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 22, 6);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x67:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_3);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 40, 57);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 33, 9);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x68:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_4);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 40, 55);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 44, 11);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x69:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_5);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 40, 52);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 55, 14);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x6A:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_6);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 40, 50);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 66, 17);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x6B:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_7);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 40, 48);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 77, 19);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x6C:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_8);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 40, 45);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 88, 22);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x6D:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_9);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 40, 42);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 99, 25);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x6E:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_10);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 40, 40);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 110, 27);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	default:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_base);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, volume_pos[0], volume_pos[1]);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 110, 27);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_mute_icon_btn);
		break;
	}
}

void GUI_Volume_Screen_Day_Mode_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_Main_day_volume_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
}
/*volume sub screen*/
void GUI_Volume_Sub_Screen_Main_Day_Mode_Entry(void)
{
	lv_obj_clear_flag(guider_ui.screen_Main_day_volume_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_pos(guider_ui.screen_Day_volume_base, Day_volume_base_pos[0], Day_volume_base_pos[1]);
	lv_obj_clear_flag(guider_ui.screen_Day_volume_plus, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_volume_minus, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
	lv_img_set_src(guider_ui.screen_Day_volume_base, &img_day_volume_bar_base);
	lv_obj_clear_flag(guider_ui.screen_Day_volume_signbtn, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_Day_volume_label, LV_OBJ_FLAG_HIDDEN);

	lv_img_set_src(guider_ui.screen_Day_volume_plus, &img_day_volume_plus_btn_normal);
	lv_img_set_src(guider_ui.screen_Day_volume_minus, &img_day_volume_minus_btn_normal);

	lv_img_set_src(guider_ui.screen_Trip_blank, &music_day_icon);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
	lv_obj_move_foreground(guider_ui.screen_Trip_blank);

}

void GUI_Volume_Sub_Screen_Main_Day_Mode_During(void)
{

	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST fl_Music_volume_st = {0};

	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST fl_contact_volume_st = {0};

	/* GET MUSIC PKT */
	fl_Music_volume_st = UART_DataManager_Get_Connectivity_Info(MUSIC_PKT);

	/* GET CALL PKT */
	fl_contact_volume_st = UART_DataManager_Get_Connectivity_Info(CALL_STS_PKT);

	if (((fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 >= INCOMING_CALL_ACTIVE) && 
		(fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 <= OUT_GOING_CALL)) || 
		((fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 >= INCOMING_CALL_ACTIVE) && 
		(fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 <= OUT_GOING_CALL)) )
	{
		g_volume_value = fl_contact_volume_st.Hero_SmartPhone_Call_Status_Pkt_St.PH_VOLUME;
	}
	else if (fl_Music_volume_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_ACT_STATUS == MUSIC_ACTIVE)
	{
		g_volume_value = fl_Music_volume_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_VOLUME;
	}
	else
	{
		/* Do Nothing*/
	}

	switch (g_volume_value)
	{
	case 0x64:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_base);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, volume_base_pos[0], volume_base_pos[1]);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 110, 27);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_mute_icon_btn);
		break;
	case 0x65:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_1);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 25, 49);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 11, 3);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x66:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_2);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 25, 46);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 22, 6);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x67:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_3);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 25, 43);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 33, 9);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x68:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_4);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 25, 40);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 44, 11);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x69:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_5);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 25, 38);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 55, 14);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x6A:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_6);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 25, 35);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 66, 17);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x6B:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_7);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 25, 33);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 77, 19);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x6C:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_8);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 25, 30);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 88, 22);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x6D:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_9);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 25, 27);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 99, 25);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	case 0x6E:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_fill_level_10);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, 25, 25);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 110, 27);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_unmute_icon_btn);
		break;
	default:
		lv_img_set_src(guider_ui.screen_Day_volume_val_img, &img_day_volume_bar_base);
		lv_obj_set_pos(guider_ui.screen_Day_volume_val_img, volume_base_pos[0], volume_base_pos[1]);
		lv_obj_set_size(guider_ui.screen_Day_volume_val_img, 110, 27);
		lv_img_set_src(guider_ui.screen_Day_volume_signbtn, &img_day_mute_icon_btn);
		break;
	}

	/* Chang Color For Volume Button If It is Pressed */

	switch (g_DownKeypressed_U8)
	{
	case Pressed_State:
		lv_img_set_src(guider_ui.screen_Day_volume_minus, &volume_minus_ornage);
		g_DownKeypressed_U8 = 2;
		break;
	case UnPressed_State:
		lv_img_set_src(guider_ui.screen_Day_volume_minus, &img_day_volume_minus_btn_normal);
		g_DownKeypressed_U8 = 0;
		break;
	default:
		g_DownKeypressed_U8 = 0;
		break;
	}

	/* Chang Color For Volume Button If It is Pressed */

	switch (g_UpKeypressed_U8)
	{
	case Pressed_State:
		lv_img_set_src(guider_ui.screen_Day_volume_plus, &volume_plus_orange);
		g_UpKeypressed_U8 = 2;
		break;
	case UnPressed_State:
		lv_img_set_src(guider_ui.screen_Day_volume_plus, &img_day_volume_plus_btn_normal);
		g_UpKeypressed_U8 = 0;
		break;
	default:
		g_UpKeypressed_U8 = 0;
		break;
	}

	/* Revert Volume Screen To CALL */
	if (g_VolumeCounter_U8 == VOLUMESCREEN_TIMEOUT)
	{
		g_VolumeCounter_U8 = 0;
		g_VolumeEvent_Bl = FALSE;
		Set_Event(BLE_CALL_EVENT);
	}
	else if (g_VolumeEvent_Bl == TRUE)
	{
		g_VolumeCounter_U8++;
	}
	else if (g_VolumeEvent_Bl == TRUE && g_VolumeCounter_U8 < VOLUMESCREEN_TIMEOUT)
	{
		g_VolumeCounter_U8 = 0;
	}
	else
	{
		/* Do Nothing */
	}
}

void GUI_Volume_Sub_Screen_Day_Mode_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_Main_day_volume_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_volume_plus, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_volume_minus, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Trip_blank, LV_OBJ_FLAG_HIDDEN);
}

void GUI_Phone_Volume_Night_Entry()
{
	GUI_Clock_Entry();
	lv_obj_clear_flag(guider_ui.screen_volume_container, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_volume_plus, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_volume_minus, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_volume_signbtn, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_volume_base, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_volume_label, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_pos(guider_ui.screen_volume_base, Day_volume_base_pos[0], Day_volume_base_pos[1]);

	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
	lv_obj_add_flag(guider_ui.screen_Sub_Con, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_Sub_Con, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_imgKmph, LV_OBJ_FLAG_HIDDEN);

	lv_img_set_src(guider_ui.screen_volume_plus, &plus_white_11x11);
	lv_img_set_src(guider_ui.screen_volume_minus, &minus_white_11x3);
	lv_img_set_src(guider_ui.screen_volume_base, &volume_background_110x27);
	lv_img_set_src(guider_ui.screen_Trip_blank, &_grp_night_common_30x30);
	lv_img_set_src(guider_ui.screen_Sub_Con, &_Layer_0_9x9);

	fl_Get_PssTime_Foramt = GUI_Get_Time_Format();

	if (fl_Get_PssTime_Foramt == CLOCK_12HR_FORMAT)
	{

		GUI_Main12hr_position();
		GUI_Intermediate12hr_position();
	}
	else
	{

		GUI_Main24hr_position();
		GUI_Intermediate24hr_position();
	}

	lv_obj_add_flag(guider_ui.screen_Trip_blank, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_volume_signbtn, LV_OBJ_FLAG_HIDDEN);

	g_VolumeCounter_U8 = 0;
}

void GUI_Phone_Volume_Night_Exit()
{

	lv_obj_add_flag(guider_ui.screen_L2_unit, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_L1_unit, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_imgKmph, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_volume_container, LV_OBJ_FLAG_HIDDEN);

	lv_obj_clear_flag(guider_ui.screen_Trip_blank, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_volume_signbtn, LV_OBJ_FLAG_HIDDEN);
	GUI_Clock_Entry();
}

void GUI_Phone_Volume_Day_Entry()
{
	lv_obj_clear_flag(guider_ui.screen_Main_day_volume_container, LV_OBJ_FLAG_HIDDEN);

	lv_obj_set_pos(guider_ui.screen_Day_volume_base, Day_volume_base_pos[0], Day_volume_base_pos[1]);
	lv_obj_clear_flag(guider_ui.screen_Day_volume_plus, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_volume_minus, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
	lv_img_set_src(guider_ui.screen_Day_volume_base, &img_day_volume_bar_base);
	lv_obj_clear_flag(guider_ui.screen_Day_volume_signbtn, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_Day_volume_label, LV_OBJ_FLAG_HIDDEN);

	lv_img_set_src(guider_ui.screen_Day_volume_plus, &img_day_volume_plus_btn_normal);
	lv_img_set_src(guider_ui.screen_Day_volume_minus, &img_day_volume_minus_btn_normal);
	lv_img_set_src(guider_ui.screen_Trip_blank, &music_day_icon);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

	lv_obj_add_flag(guider_ui.screen_Trip_blank, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_volume_signbtn, LV_OBJ_FLAG_HIDDEN);
}

void GUI_Phone_Volume_Day_Exit()
{
	lv_obj_add_flag(guider_ui.screen_Main_day_volume_container, LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_Day_volume_plus, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_volume_minus, LV_OBJ_FLAG_HIDDEN);

	lv_obj_clear_flag(guider_ui.screen_Trip_blank, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_volume_signbtn, LV_OBJ_FLAG_HIDDEN);
}

uint8_t GUI_Up_Phone_contact_list(void)
{
	g_Main_Phone_Sub_Screen_Sel_Cnt_U8 = g_Main_Phone_Sub_Screen_Sel_Cnt_U8 + 1;

	if (g_Main_Phone_Sub_Screen_Sel_Cnt_U8 > 5)
	{
		g_Main_Phone_Sub_Screen_Sel_Cnt_U8 = 1;
	}

	/* Sent Contact Details to BLE */
	switch (g_Main_Phone_Sub_Screen_Sel_Cnt_U8)
	{
	case 1:
		BLE_music_setting_screen(Contact_1);
		break;
	case 2:
		BLE_music_setting_screen(Contact_2);
		break;
	case 3:
		BLE_music_setting_screen(Contact_3);
		break;
	case 4:
		BLE_music_setting_screen(Contact_4);
		break;
	case 5:
		BLE_music_setting_screen(Contact_5);
		break;
	default:
		BLE_music_setting_screen(Contact_0);
		break;
	}

	/* INCREMENT CONTACT EVENT */
	IntermediateScreen_Contact_Increment();

	/* Key Pressed State*/

	g_DownKeypressed_U8 = Pressed_State;

	return 0;
}

uint8_t GUI_Down_Phone_contact_list(void)
{
	g_Main_Phone_Sub_Screen_Sel_Cnt_U8 = g_Main_Phone_Sub_Screen_Sel_Cnt_U8 - 1;

	if (g_Main_Phone_Sub_Screen_Sel_Cnt_U8 <= 0)
	{
		g_Main_Phone_Sub_Screen_Sel_Cnt_U8 = 5;
	}

	/* Sent Contact Details to BLE */
	switch (g_Main_Phone_Sub_Screen_Sel_Cnt_U8)
	{
	case 1:
		BLE_music_setting_screen(Contact_1);
		break;
	case 2:
		BLE_music_setting_screen(Contact_2);
		break;
	case 3:
		BLE_music_setting_screen(Contact_3);
		break;
	case 4:
		BLE_music_setting_screen(Contact_4);
		break;
	case 5:
		BLE_music_setting_screen(Contact_5);
		break;
	default:
		BLE_music_setting_screen(Contact_0);
		break;
	}

	/* DECREMENT CONTACT EVENT */
	IntermediateScreen_Contact_Decrement();

	/* Key Pressed State */

	g_UpKeypressed_U8 = Pressed_State;

	return 0;
}

uint8_t GUI_Contact_Right_button_Click(void)
{
	/* Change Call Details */
	g_Get_Screen_Callsts_str = UART_DataManager_Get_Connectivity_Info(CALL_STS_PKT);

	/* Check Second Call is Active */
	if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == INCOMING_CALL_ACTIVE && g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == NO_CALL_ACTIVITY)
	{
		BLE_music_setting_screen(Call_Reject);
	}
	/* Check First Call is Active & Second Call is Incoming */
	else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == INCOMING_CALL_ACTIVE && g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == CALL_IS_CRNTLY_ACTIVE)
	{
		BLE_music_setting_screen(Second_Call_Accepted_Decline_1st_Call);
	}
	else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == CALL_IS_CRNTLY_ACTIVE)
	{
		BLE_music_setting_screen(Second_Call_Declined);
	}
	else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == CALL_IS_CRNTLY_ACTIVE)
	{
		BLE_music_setting_screen(Call_End);
	}
	else
	{
		/* Do Nothing */
	}

	/* Key Pressed State */
	g_RightKeypressed_U8 = Pressed_State;

	return 0;
}

uint8_t GUI_Contact_Left_button_Click(void)
{
	/* Change Call Details */
	g_Get_Screen_Callsts_str = UART_DataManager_Get_Connectivity_Info(CALL_STS_PKT);

	/* Check Second Call is Active */
	if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == INCOMING_CALL_ACTIVE && g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == NO_CALL_ACTIVITY)
	{
		BLE_music_setting_screen(Call_Accept);
	}
	/* Check First Call is Active & Second Call is Incoming */
	else if (g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == INCOMING_CALL_ACTIVE && g_Get_Screen_Callsts_str.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == CALL_IS_CRNTLY_ACTIVE)
	{
		BLE_music_setting_screen(Second_Call_Accepted_holding_1st_Call);
	}
	else
	{
		/* Do Nothing */
	}

	/* Key Pressed State */
	g_LeftKeypressed_U8 = Pressed_State;

	return 0;
}

uint8_t GUI_Contact_Up_button_Click(void)
{
	/* Increase Phone Volume */
	BLE_music_setting_screen(Phone_Volume_increase);
	return 0;
}

uint8_t GUI_Contact_Down_button_Click(void)
{
	/* Decrease Phone Volume */
	BLE_music_setting_screen(Phone_Volume_Decrease);
	return 0;
}

uint8_t GUI_Volume_Mute(void)
{
	BLE_music_setting_screen(Mute);
	return 0;
}

uint8_t Call_Selectbtn_click(void)
{
	g_RightKeypressed_Call_U8 = Pressed_State;
	return 0;
}

void GUI_Phone_Screen_Day(void)
{
	if (BLE_Get_Connection_Status() == 1)
	{
		g_Is_BLE_Settings_Selected_bool = GUI_BLE_Enable_Status();

		g_Get_Screen_sts_st = UART_DataManager_Get_Connectivity_Info(STS_PKT);

		/* Check the connection establishement status */
		g_Is_BLE_Connection_Established_bool = TRUE;

		/* Validate the Data Packet */
		if ((g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS >= 0x30) &&
			(g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS <= 0X34))
		{
			g_Is_BLE_Battery_Status_Received_bool = TRUE;
		}

		/* Decide the Enable / Disable status of the Phone Information ICON */
		if ((g_Is_BLE_Settings_Selected_bool != FALSE) &&
			(g_Is_BLE_Connection_Established_bool != FALSE) &&
			(g_Is_BLE_Battery_Status_Received_bool != FALSE))
		{
			if (g_PreviousBattery_Value_U8 != g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS || g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS == 0x30)
			{
				g_PreviousBattery_Value_U8 = g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS;
				if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS == 0x31)
				{
					/* Set 1st Bar Batter Image*/
					lv_obj_clear_flag(guider_ui.screen_day_battery_img, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_day_battery_img, &day_battery_1bar);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS == 0x32)
				{
					/* Set 2nd Bar Batter Image*/
					lv_obj_clear_flag(guider_ui.screen_day_battery_img, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_day_battery_img, &day_battery_2bar);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS == 0x33)
				{
					/* Set 3rd Bar Batter Image*/
					lv_obj_clear_flag(guider_ui.screen_day_battery_img, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_day_battery_img, &day_battery_3bar);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS == 0x34)
				{
					/* Set 4th Bar Batter Image*/
					lv_obj_clear_flag(guider_ui.screen_day_battery_img, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_day_battery_img, &day_battery_4bar);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.BATT_STATUS == 0x30)
				{
					lv_obj_clear_flag(guider_ui.screen_day_battery_img, LV_OBJ_FLAG_HIDDEN);
					/* For Blink Battery*/
					if (g_Img_Blink_bl)
					{
						lv_img_set_src(guider_ui.screen_day_battery_img, &day_battery_red);
					}
					else
					{
						lv_img_set_src(guider_ui.screen_day_battery_img, &day_battery_base);
					}
				}
				else
				{
					lv_obj_add_flag(guider_ui.screen_day_battery_img, LV_OBJ_FLAG_HIDDEN);
				}
			}
			else
			{
				/* No Changes Here */
			}
			g_BattScreen_bl = FALSE;
		}
		else if (g_BattScreen_bl == FALSE)
		{
			lv_obj_add_flag(guider_ui.screen_day_battery_img, LV_OBJ_FLAG_HIDDEN);
			g_PreviousBattery_Value_U8 = 0x00;
			g_BattScreen_bl = TRUE;
		}
		else
		{
			/* No Changes Here */
		}
	}
	else if (g_BattScreen_bl == FALSE)
	{
		lv_obj_add_flag(guider_ui.screen_day_battery_img, LV_OBJ_FLAG_HIDDEN);
		g_BattScreen_bl = TRUE;
	}
	else
	{
		/* No Changes Here */
	}
}

void GUI_Signal_Day(void)
{

	if (BLE_Get_Connection_Status() == 1)
	{
		g_Get_Screen_sts_st = UART_DataManager_Get_Connectivity_Info(STS_PKT);

		g_Is_BLE_Settings_Selected_bool = GUI_BLE_Enable_Status();

		if ((g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR >= 0x30) &&
			(g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR <= 0X34))
		{
			g_Is_BLE_Signal_Status_Received_bool = TRUE;
		}
		g_Is_BLE_Connection_Established_bool = TRUE;

		/* Decide the Enable / Disable status of the Phone Information ICON */
		if ((g_Is_BLE_Settings_Selected_bool != FALSE) &&
			(g_Is_BLE_Connection_Established_bool != FALSE) &&
			(g_Is_BLE_Signal_Status_Received_bool != FALSE))
		{
			if (g_PreviousSignal_Value_U8 != g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR)
			{
				g_PreviousSignal_Value_U8 = g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR;
				if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR == 0x31)
				{
					/* Signal 1st Bar*/
					lv_obj_clear_flag(guider_ui.screen_day_signal_img, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_day_signal_img, &signal_day1);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR == 0x32)
				{
					/* Signal 2nd Bar*/
					lv_obj_clear_flag(guider_ui.screen_day_signal_img, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_day_signal_img, &signal_day2);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR == 0x33)
				{
					/* Signal 3rd Bar*/
					lv_obj_clear_flag(guider_ui.screen_day_signal_img, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_day_signal_img, &signal_day3);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR == 0x34)
				{
					/* Signal 4th Bar*/
					lv_obj_clear_flag(guider_ui.screen_day_signal_img, LV_OBJ_FLAG_HIDDEN);
					lv_img_set_src(guider_ui.screen_day_signal_img, &signal_day4);
				}
				else if (g_Get_Screen_sts_st.Hero_SmartPhone_Status_Pkt_St.SIG_STR == 0x30)
				{
					/* Signal Hide No value*/
					lv_obj_add_flag(guider_ui.screen_day_signal_img, LV_OBJ_FLAG_HIDDEN);
				}
				else
				{
					/* Signal Hide No value*/
					lv_obj_add_flag(guider_ui.screen_day_signal_img, LV_OBJ_FLAG_HIDDEN);
				}
				g_SignalScreen_bl = FALSE;
			}
			else
			{
				/* No Changes Here */
			}
		}
		else if (g_SignalScreen_bl == FALSE)
		{
			/* Signal Hide No value*/
			lv_obj_add_flag(guider_ui.screen_day_signal_img, LV_OBJ_FLAG_HIDDEN);
			g_SignalScreen_bl = TRUE;
		}
		else
		{
			/* No Changes Here */
		}
	}
	else if (g_SignalScreen_bl == FALSE)
	{
		/* Signal Hide No value*/
		lv_obj_add_flag(guider_ui.screen_day_signal_img, LV_OBJ_FLAG_HIDDEN);
		g_SignalScreen_bl = TRUE;
	}
	else
	{
		/* No Changes Here */
	}
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
