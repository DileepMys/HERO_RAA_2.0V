/* @file FILE NAME */
#ifndef HMI_MUSIC_C
#define HMI_MUSIC_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Balasubramanian (balasubramaninan@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : HMI_Music.c
 *  Version                         : 
 *  Micros supported                : 
 *  Compilers supported             : 
 *  Platforms supported             : 
 *  Description                     : This file consists of definitions of music packets
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "../lvgl/lvgl.h"

#include "lvgl_app.h"


#include "custom.h"

#include "HMI_Music.h"
#include "BLE_music_module.h"
#include "HMI_Clock.h"
#include "HMI_Setting_Screen.h"
#include "HMI_GUI_Interface.h"
#include "UART_DataManager.h"

/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                     
***********************************************************************************************************************/


signed int Date_Lb1_val_1[2]={92,18};

signed int Day_Date_Lb1_val_1[2]={92,18};

signed int Slider_org_val[2]={40,81};

signed int Day_Slider_org_val[2]={40,81};

signed int music_lbl_pos[2]={15, 5};

signed int Day_music_lbl_pos[2]={15, 5};

uint8_t bluetooth_pair=0;


uint8_t scrollbar_Value=0;

uint8_t fl_Get_clock_music_Foramt;

uint8_t music_slider_x_y[2] = {46, 62};



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

static HMI_Music_Main_Screen_Type_St  g_Music_Main_MainScreen_Info_St;
HMI_Music_Main_Screen_Type_St g_Music_Main_MainScreen_Info_St_Ptr;
char g_artistname_str[20];
char g_songname_str[20];
int16_t g_pinvalue_I16;
extern uint8_t g_User_Music_Select_Level_U8;
int16_t g_Dot_Decimal_I16 = 0;
uint8_t g_UpKeypressed_U8 = 0;
uint8_t g_DownKeypressed_U8 = 0;

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

void GUI_Music_screen_Night_Entry(void)
{
	/* Music Label image */
	lv_obj_move_foreground(guider_ui.screen_Trip_blank);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
	lv_img_set_src(guider_ui.screen_Trip_blank,&_grp_night_common_30x30);

	/* enable music container */
	lv_obj_clear_flag(guider_ui.screen_music_container,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_up_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_down_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_sub_button,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_lbl_2,LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_pos(guider_ui.screen_music_slide_dot,15,56);
	lv_obj_set_pos(guider_ui.screen_music_lbl_1,music_lbl_pos[0],music_lbl_pos[1]);
	lv_obj_clear_flag(guider_ui.screen_music_lbl_1,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_music_lbl_2,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_music_lbl_3,LV_OBJ_FLAG_HIDDEN);

	lv_img_set_src(guider_ui.screen_Sub_Con,&subbtn_night_24x24);
	lv_obj_clear_flag(guider_ui.screen_Sub_Con,LV_OBJ_FLAG_HIDDEN);


	lv_obj_clear_flag(guider_ui.screen_music_slider_orange_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_music_slider_whitebase_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_music_slide_dot,LV_OBJ_FLAG_HIDDEN);

	fl_Get_clock_music_Foramt = GUI_Get_Time_Format();
	
	if (fl_Get_clock_music_Foramt == CLOCK_12HR_FORMAT)
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

void GUI_Music_Show_Night_Entry(void)
{

	lv_obj_clear_flag(guider_ui.screen_music_container,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_music_up_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_music_down_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
	lv_obj_set_pos(guider_ui.screen_music_slide_dot,15,56);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
	lv_obj_set_pos(guider_ui.screen_music_lbl_1,music_lbl_pos[0],music_lbl_pos[1]);
	lv_obj_add_flag(guider_ui.screen_music_lbl_1,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_music_lbl_2,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_lbl_3,LV_OBJ_FLAG_HIDDEN);
	lv_img_set_src(guider_ui.screen_Trip_blank,&_grp_night_common_30x30);
	
	lv_obj_clear_flag(guider_ui.screen_music_sub_button,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_slider_whitebase_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_slider_orange_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_slide_dot,LV_OBJ_FLAG_HIDDEN);

	lv_img_set_src(guider_ui.screen_music_sub_button,&play_white_30x30);

	lv_obj_add_flag(guider_ui.screen_Sub_Con,LV_OBJ_FLAG_HIDDEN);  

	lv_img_set_src(guider_ui.screen_music_down_img,&next_white_9x12);
	lv_img_set_src(guider_ui.screen_music_up_img,&pre_white_10x13);

	fl_Get_clock_music_Foramt = GUI_Get_Time_Format();
	if (fl_Get_clock_music_Foramt == CLOCK_12HR_FORMAT)
 	{
		GUI_Main12hr_position();
		GUI_Intermediate12hr_position();
 	}
 	else
 	{
		GUI_Main24hr_position();
		GUI_Intermediate24hr_position();
 	}

	lv_obj_set_style_text_color(guider_ui.screen_music_lbl_1,lv_color_Nightmode_Whitetext(),0);	

	lv_obj_set_pos(guider_ui.screen_music_lbl_2,14,27);
}

void GUI_Music_Screen_Show_Night_Exit(void)
{
	/* Hide music containter*/
    lv_obj_add_flag(guider_ui.screen_music_container,LV_OBJ_FLAG_HIDDEN);
}

void GUI_Music_Screen_Show_During(void)
{
	uint8_t fl_Get_Battery_Connect_Status = 0;
	fl_Get_Battery_Connect_Status = BLE_Get_Connection_Status();
	
	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST fl_MusicPkt_st = {0};

	/* GET MUSIC PKT */

	fl_MusicPkt_st = UART_DataManager_Get_Connectivity_Info(MUSIC_PKT);
	/* CHECK FOR THE BLE CONNECTION STATUS */
	if((fl_Get_Battery_Connect_Status == 1) && (fl_MusicPkt_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_ACT_STATUS == MUSIC_ACTIVE))
	{

		/* GET THE SONG AND ARTIST STATUS */
		for(uint8_t i=0; i<20; i++)
		{
			g_songname_str[i] = fl_MusicPkt_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_META_DATA_1[i];
		}
		
		/* CHECK FOR THE PLAY/PAUSE STATE FROM THE MUSIC PKT */
		if(fl_MusicPkt_st.Hero_SmartPhone_Music_Pkt_St.PLYBCK_STATE == 0x30)
		{
			/* SET THE IMAGE FOR PLAY */
			lv_img_set_src(guider_ui.screen_music_sub_button,&play_white_30x30);
		}
		else
		{
			/* SET THE IMAGE FOR PAUSE */
			lv_img_set_src(guider_ui.screen_music_sub_button,&pause_white_30x30);
		}

		/* SONG STRING */
		lv_label_set_text_fmt(guider_ui.screen_music_lbl_2,"%s",g_songname_str);
	}
	else
	{
		/* SHOW "Play Music" TEXT IF THERE IS NO MUSIC POCKET RECEIVED */	
		lv_obj_add_flag(guider_ui.screen_music_lbl_1,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_music_lbl_2,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_music_lbl_3,LV_OBJ_FLAG_HIDDEN);
		lv_label_set_text_fmt(guider_ui.screen_music_lbl_2,"%s","");
	}

	switch (g_DownKeypressed_U8)
	{
		case Pressed_State:
			lv_img_set_src(guider_ui.screen_music_down_img,&nextmusic_orange_icon_pressed);
			g_DownKeypressed_U8 = 2;
			break;
		case UnPressed_State:
			lv_img_set_src(guider_ui.screen_music_down_img,&next_white_9x12);
			g_DownKeypressed_U8 = 0;
			break;
		default:
			g_DownKeypressed_U8 = 0;
			break;
	}

	switch (g_UpKeypressed_U8)
	{
		case Pressed_State:
			lv_img_set_src(guider_ui.screen_music_up_img,&permusic_icon_orange);
			g_UpKeypressed_U8 = 2;
			break;
		case UnPressed_State:
			lv_img_set_src(guider_ui.screen_music_up_img,&pre_white_10x13);
			g_UpKeypressed_U8 = 0;
			break;
		default:
			g_UpKeypressed_U8 = 0;
			break;
	}
	
	
}

void GUI_Music_screen_Night_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_music_up_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_down_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_sub_button,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_lbl_2,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_slider_whitebase_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_slider_orange_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_slide_dot,LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.screen_music_container,LV_OBJ_FLAG_HIDDEN);  
}

void GUI_Music_screen_Night_During(void)
{
	uint8_t fl_Get_Battery_Connect_Status = 0;
	
	fl_Get_Battery_Connect_Status = BLE_Get_Connection_Status();
	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST fl_MusicPkt_st = {0};

	/* GET MUSIC PKT */
	fl_MusicPkt_st = UART_DataManager_Get_Connectivity_Info(MUSIC_PKT);


	/* CHECK FOR BLE CONNECTION STATUS & MUSIC ACTIVE STATUS */
	if((fl_Get_Battery_Connect_Status == 1) && (fl_MusicPkt_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_ACT_STATUS == MUSIC_ACTIVE))
	{
		/* GET THE SONG AND ARTIST STATUS */
		for(uint8_t i=0; i<20; i++)
		{
			g_songname_str[i] = fl_MusicPkt_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_META_DATA_1[i];
			g_artistname_str[i] = fl_MusicPkt_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_META_DATA_2[i];
		}

		lv_obj_set_style_text_color(guider_ui.screen_music_lbl_1,lv_color_Nightmode_Whitetext(),0);		
		lv_obj_clear_flag(guider_ui.screen_music_lbl_1,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_music_lbl_2,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_music_lbl_3,LV_OBJ_FLAG_HIDDEN);	
		lv_label_set_text_fmt(guider_ui.screen_music_lbl_1,"%s", &g_songname_str[0]);
		lv_label_set_text_fmt(guider_ui.screen_music_lbl_3,"%s", &g_artistname_str[0]);

		/* GET DECIMAL VALUE FOR THE DOT 
		*  Calculation : ((Slider Orange Color Width (130 Max) * Elapsed Time ) / 100 ) 
		*/		
		int iv = lv_obj_get_width(guider_ui.screen_music_slider_whitebase_img);
		g_Dot_Decimal_I16 = ((130 * fl_MusicPkt_st.Hero_SmartPhone_Music_Pkt_St.ELAPSED_TIME) / 100);
		/* DOT OFFSET TO PALCE IN START POSITION */
		g_pinvalue_I16 = (g_Dot_Decimal_I16 + 15);
	
		/* MAX CEILING CHECK */
		if (g_Dot_Decimal_I16 <=130)
		{
			lv_obj_clear_flag(guider_ui.screen_music_slider_orange_img,LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_music_slider_whitebase_img,LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_music_slide_dot,LV_OBJ_FLAG_HIDDEN);
			lv_obj_set_size(guider_ui.screen_music_slider_orange_img, g_Dot_Decimal_I16,2);	
			lv_obj_set_pos(guider_ui.screen_music_slide_dot,g_pinvalue_I16,56);
		}
		else 
		{
			/* Do Nothing*/
		}
	}
	else
	{
		/* label */
		lv_obj_clear_flag(guider_ui.screen_music_lbl_1,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_music_lbl_2,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_music_lbl_3,LV_OBJ_FLAG_HIDDEN);

		/* Change Font Color */
		lv_obj_set_style_text_color(guider_ui.screen_music_lbl_1,lv_color_Nightmode_Greytext(),0);		

		/*SLIEDER*/
		lv_obj_add_flag(guider_ui.screen_music_slider_orange_img,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_music_slider_whitebase_img,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_music_slide_dot,LV_OBJ_FLAG_HIDDEN);

		lv_label_set_text_fmt(guider_ui.screen_music_lbl_1,"%s","Activate");
		lv_label_set_text_fmt(guider_ui.screen_music_lbl_3,"%s","Music");
	}

}

/****************************************************************************************************/

void GUI_Music_Screen_Show_Entry_Day(void)
{
    lv_obj_clear_flag(guider_ui.screen_Main_day_music_container,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_day_sub_btn,LV_OBJ_FLAG_HIDDEN);
	lv_img_set_src(guider_ui.screen_Day_music_sub_button,&play_music_day_img);
	
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

	lv_obj_add_flag(guider_ui.screen_Day_music_slider_whitebase_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_music_slider_orange_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_music_slide_dot,LV_OBJ_FLAG_HIDDEN);

	lv_obj_set_pos(guider_ui.screen_Day_music_lbl_2, 14, 27);
	lv_obj_set_size(guider_ui.screen_Day_music_lbl_2, 153, 17);

	lv_img_set_src(guider_ui.screen_Trip_blank,&music_day_icon);

	lv_obj_move_foreground(guider_ui.screen_Trip_blank);

	lv_obj_clear_flag(guider_ui.screen_Day_music_up_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_music_down_img,LV_OBJ_FLAG_HIDDEN);	

	lv_img_set_src(guider_ui.screen_Day_music_up_img,&img_day_music_L1_previous_btn);
	lv_img_set_src(guider_ui.screen_Day_music_down_img,&img_day_music_L1_next_btn);

	lv_obj_set_style_text_color(guider_ui.screen_Day_music_lbl_1,lv_color_Daymode_Blacktext(),0);	

	lv_obj_clear_flag(guider_ui.screen_Day_music_lbl_1,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_music_lbl_2,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_music_lbl_3,LV_OBJ_FLAG_HIDDEN);

	/* Label 2 alone required for music sub screen where song name will be shown */
	lv_label_set_text_fmt(guider_ui.screen_Day_music_lbl_1,"%s","");
	lv_label_set_text_fmt(guider_ui.screen_Day_music_lbl_3,"%s","");

	lv_obj_clear_flag(guider_ui.screen_Day_music_sub_button,LV_OBJ_FLAG_HIDDEN);

}

void GUI_Music_Screen_Show_During_Day(void)
{
	uint8_t fl_Get_Battery_Connect_Status = 0;
	fl_Get_Battery_Connect_Status = BLE_Get_Connection_Status();
	
	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST fl_MusicPkt_st = {0};
	
	/* GET MUSIC PKT */
   fl_MusicPkt_st = UART_DataManager_Get_Connectivity_Info(MUSIC_PKT);
	
	if((fl_Get_Battery_Connect_Status == 1) && (fl_MusicPkt_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_ACT_STATUS == MUSIC_ACTIVE))
	{
		HMI_music_main_screen_info(&g_Music_Main_MainScreen_Info_St_Ptr);
		
		for(uint8_t i=0; i<20; i++)
		{
			g_songname_str[i] = fl_MusicPkt_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_META_DATA_1[i];
		}
		

		/* CHECK FOR THE PLAY/PAUSE STATE FROM THE MUSIC PKT */
		if(fl_MusicPkt_st.Hero_SmartPhone_Music_Pkt_St.PLYBCK_STATE == 0x30)
		{
			/* SET THE IMAGE FOR PLAY */
			lv_img_set_src(guider_ui.screen_Day_music_sub_button,&day_L1_Play_Btn);
		}
		else
		{
			/* SET THE IMAGE FOR PAUSE */
			lv_img_set_src(guider_ui.screen_Day_music_sub_button,&day_L1_Pause_Btn);
		}

		lv_label_set_text_fmt(guider_ui.screen_Day_music_lbl_2,"%s",&g_songname_str[0]);
	}
	else
	{
		lv_label_set_text_fmt(guider_ui.screen_Day_music_lbl_2,"%s","");
	}

	switch (g_DownKeypressed_U8)
	{
		case Pressed_State:
			lv_img_set_src(guider_ui.screen_Day_music_down_img,&nextmusic_orange_icon_pressed);
			g_DownKeypressed_U8 = 2;
			break;
		case UnPressed_State:
			lv_img_set_src(guider_ui.screen_Day_music_down_img,&img_day_music_L1_next_btn);
			g_DownKeypressed_U8 = 0;
			break;
		default:
			g_DownKeypressed_U8 = 0;
			break;
	}

	switch (g_UpKeypressed_U8)
	{
		case Pressed_State:
			lv_img_set_src(guider_ui.screen_Day_music_up_img,&permusic_icon_orange);
			g_UpKeypressed_U8 = 2;
			break;
		case UnPressed_State:
			lv_img_set_src(guider_ui.screen_Day_music_up_img,&img_day_music_L1_previous_btn);
			g_UpKeypressed_U8 = 0;
			break;
		default:
			g_UpKeypressed_U8 = 0;
			break;
	}
	

}

void GUI_Music_Screen_Show_Exit_Day(void)
{
	lv_obj_add_flag(guider_ui.screen_Day_music_sub_button,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_Main_day_music_container,LV_OBJ_FLAG_HIDDEN);
}

/**************************************************************************************/


void GUI_Music_Main_Day_Entry(void)
{
	lv_obj_clear_flag(guider_ui.screen_Main_day_music_container,LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.screen_day_sub_btn,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_music_down_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_music_up_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_music_slider_orange_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_music_slider_whitebase_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_music_slide_dot,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_music_sub_button,LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

	lv_obj_set_pos(guider_ui.screen_Day_music_slide_dot,g_pinvalue_I16,56);

	lv_obj_set_pos(guider_ui.screen_Day_music_lbl_1,Day_music_lbl_pos[0],Day_music_lbl_pos[1]);

	lv_img_set_src(guider_ui.screen_Trip_blank,&music_day_icon);
	lv_obj_move_foreground(guider_ui.screen_Trip_blank);

	lv_obj_clear_flag(guider_ui.screen_Day_music_lbl_1,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_music_lbl_2,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_music_lbl_3,LV_OBJ_FLAG_HIDDEN);

	/* Change Font Color */
	lv_obj_set_style_text_color(guider_ui.screen_Day_music_lbl_1,lv_color_Daymode_Blacktext(),0);
	
}


void GUI_Music_screen_Day_During(void)
{
	uint8_t fl_Get_Battery_Connect_Status = 0;
	fl_Get_Battery_Connect_Status = BLE_Get_Connection_Status();
	UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST fl_MusicPkt_st = {0};

		/* GET MUSIC PKT */
	fl_MusicPkt_st = UART_DataManager_Get_Connectivity_Info(MUSIC_PKT);
	/* CHECK FOR BLE CONNECTION STATUS & MUSIC ACTIVE STATUS */
	if((fl_Get_Battery_Connect_Status == 1) && (fl_MusicPkt_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_ACT_STATUS == MUSIC_ACTIVE))
	{
		/* GET THE SONG AND ARTIST STATUS */
		for(uint8_t i=0; i<20; i++)
		{
			g_songname_str[i] = fl_MusicPkt_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_META_DATA_1[i];
			g_artistname_str[i] = fl_MusicPkt_st.Hero_SmartPhone_Music_Pkt_St.MUSIC_META_DATA_2[i];
		}	

		lv_label_set_text_fmt(guider_ui.screen_Day_music_lbl_1,"%s", &g_songname_str[0]);
		lv_label_set_text_fmt(guider_ui.screen_Day_music_lbl_3,"%s", &g_artistname_str[0]);

		/* GET DECIMAL VALUE FOR THE DOT 
		*  Calculation : ((Slider Orange Color Width (130 Max) * Elapsed Time ) / 100 ) 
		*/		
		g_Dot_Decimal_I16 = ((130 * fl_MusicPkt_st.Hero_SmartPhone_Music_Pkt_St.ELAPSED_TIME) / 100);
		/* DOT OFFSET TO PALCE IN START POSITION */
		g_pinvalue_I16 = (g_Dot_Decimal_I16 + 15);
		
		/* MAX CEILING CHECK */
		if (g_Dot_Decimal_I16 <=130)
		{
			lv_obj_clear_flag(guider_ui.screen_Day_music_slider_whitebase_img,LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_Day_music_slider_orange_img,LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_Day_music_slide_dot,LV_OBJ_FLAG_HIDDEN);
			lv_obj_set_size(guider_ui.screen_Day_music_slider_orange_img, g_Dot_Decimal_I16,2);	
			lv_obj_set_pos(guider_ui.screen_Day_music_slide_dot,g_pinvalue_I16,56);
		}
		else
		{
			/* Do Nothing */
		}
	}
	else
	{	

		lv_label_set_text_fmt(guider_ui.screen_Day_music_lbl_1,"%s","Activate");
		lv_label_set_text_fmt(guider_ui.screen_Day_music_lbl_3,"%s","Music");

		lv_obj_add_flag(guider_ui.screen_Day_music_slider_whitebase_img,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_Day_music_slider_orange_img,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_Day_music_slide_dot,LV_OBJ_FLAG_HIDDEN);
	}

}

void GUI_Music_Screen_Main_Day_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_Main_day_music_container,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_music_slider_whitebase_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_music_slider_orange_img,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Day_music_slide_dot,LV_OBJ_FLAG_HIDDEN);
	
}

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : v1.0.1                          
    REVISION DATE        : 8/23/2022        
    CREATED / REVISED BY : Balasubramanina (balasubramanian@niyatainfotech.com)      
    DESCRIPTION          : Initial version            lv_style_set_text_font
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! HMI_MUSIC_C */




