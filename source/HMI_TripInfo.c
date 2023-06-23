/* @file FILE NAME */
#ifndef HMI_TRIPAINFO_C
#define HMI_TRIPAINFO_C

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
#include "HMI_TripInfo.h"
#include "HMI_Main_Screen.h"

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

    	typedef enum
	{		
		TRIP_Info_LBL_1 ,
		TRIP_Info_VALUE_1,
		TRIP_Info_UNIT_1,
		TRIP_Info_LBL_2,
		TRIP_Info_VALUE_2,
		TRIP_Info_UNIT_2,
        TRIP_Service_LBL_1 ,
		TRIP_Service_VALUE_1,
		TRIP_Service_UNIT_1,
		TRIP_Service_LBL_2,
		TRIP_Service_VALUE_2,
		TRIP_Service_UNIT_2,
		TRIP_MAX_SIZE
	} Trip_Info_Details_Enum;

	typedef struct
	{
		signed int X_Pos;
		signed int Y_Pos;
	} TripInfoPosDetailsTypeSt;

	const TripInfoPosDetailsTypeSt TripInfoPosDetailsSt[TRIP_MAX_SIZE] =
		{
			{-20, 12},
			{65, 8},
			{125, 12},
			{0, 41},
			{18, 38},
			{125, 42},
			{-20, 10},
			{66, 6},
			{131,20},
			{18,40},
			{40,36},
			{148,42}
		};

       /*TABLE FOR SERVICE REMAINDER AND RTMI SCREEN POSITIONS*/
        g_Trip_Info_Pos g_Trip_Info_Pos_Table[12] = {
                   {(lv_obj_t*)&guider_ui.screen_L1_lbl  ,     (lv_obj_t*)&guider_ui.screen_day_in_lb1   ,  (signed int*)&TripInfoPosDetailsSt[TRIP_Info_LBL_1].X_Pos      ,     (signed int*)&TripInfoPosDetailsSt[TRIP_Info_LBL_1].Y_Pos },
                   {(lv_obj_t*)&guider_ui.screen_L1_val  ,     (lv_obj_t*)&guider_ui.screen_day_in_lb2   ,  (signed int*)&TripInfoPosDetailsSt[TRIP_Info_VALUE_1].X_Pos    ,     (signed int*)&TripInfoPosDetailsSt[TRIP_Info_VALUE_1].Y_Pos },
                   {(lv_obj_t*)&guider_ui.screen_L1_unit ,     (lv_obj_t*)&guider_ui.screen_day_in_lb3   ,  (signed int*)&TripInfoPosDetailsSt[TRIP_Info_UNIT_1].X_Pos     ,     (signed int*)&TripInfoPosDetailsSt[TRIP_Info_UNIT_1].Y_Pos },
                   {(lv_obj_t*)&guider_ui.screen_L2_lbl  ,     (lv_obj_t*)&guider_ui.screen_day_in_lb4   ,  (signed int*)&TripInfoPosDetailsSt[TRIP_Info_LBL_2].X_Pos      ,     (signed int*)&TripInfoPosDetailsSt[TRIP_Info_LBL_2].Y_Pos },
                   {(lv_obj_t*)&guider_ui.screen_L2_val  ,     (lv_obj_t*)&guider_ui.screen_day_in_lb5   ,  (signed int*)&TripInfoPosDetailsSt[TRIP_Info_VALUE_2].X_Pos    ,     (signed int*)&TripInfoPosDetailsSt[TRIP_Info_VALUE_2].Y_Pos },
                   {(lv_obj_t*)&guider_ui.screen_L2_unit ,     (lv_obj_t*)&guider_ui.screen_day_in_lb6   ,  (signed int*)&TripInfoPosDetailsSt[TRIP_Info_UNIT_2].X_Pos     ,     (signed int*)&TripInfoPosDetailsSt[TRIP_Info_UNIT_2].Y_Pos },
                   {(lv_obj_t*)&guider_ui.screen_L1_lbl  ,     (lv_obj_t*)&guider_ui.screen_day_in_lb1   ,  (signed int*)&TripInfoPosDetailsSt[TRIP_Service_LBL_1].X_Pos   ,     (signed int*)&TripInfoPosDetailsSt[TRIP_Service_LBL_1].Y_Pos },
                   {(lv_obj_t*)&guider_ui.screen_L1_val  ,     (lv_obj_t*)&guider_ui.screen_day_in_lb2   ,  (signed int*)&TripInfoPosDetailsSt[TRIP_Service_VALUE_1].X_Pos ,     (signed int*)&TripInfoPosDetailsSt[TRIP_Service_VALUE_1].Y_Pos },
                   {(lv_obj_t*)&guider_ui.screen_L1_unit ,     (lv_obj_t*)&guider_ui.screen_day_in_lb3   ,  (signed int*)&TripInfoPosDetailsSt[TRIP_Service_UNIT_1].X_Pos  ,     (signed int*)&TripInfoPosDetailsSt[TRIP_Service_UNIT_1].Y_Pos },
                   {(lv_obj_t*)&guider_ui.screen_L2_lbl  ,     (lv_obj_t*)&guider_ui.screen_day_in_lb4   ,  (signed int*)&TripInfoPosDetailsSt[TRIP_Service_LBL_2].X_Pos   ,     (signed int*)&TripInfoPosDetailsSt[TRIP_Service_LBL_2].Y_Pos },
                   {(lv_obj_t*)&guider_ui.screen_L2_val  ,     (lv_obj_t*)&guider_ui.screen_day_in_lb5   ,  (signed int*)&TripInfoPosDetailsSt[TRIP_Service_VALUE_2].X_Pos ,     (signed int*)&TripInfoPosDetailsSt[TRIP_Service_VALUE_2].Y_Pos },
                   {(lv_obj_t*)&guider_ui.screen_L2_unit ,     (lv_obj_t*)&guider_ui.screen_day_in_lb6   ,  (signed int*)&TripInfoPosDetailsSt[TRIP_Service_UNIT_2].X_Pos  ,     (signed int*)&TripInfoPosDetailsSt[TRIP_Service_UNIT_2].Y_Pos }};                                   
                                                        
                                            



    uint32_t g_previous_Range_Display_Night_32 = 0;
    uint32_t g_previous_Rtmi_Value_Night_u32 = 0;
    uint32_t g_previous_Range_Display_Unit_Night_32 = 0;

    uint32_t g_previous_Range_Display_Day_32 = 0;
    uint32_t g_previous_Rtmi_Value_Day_u32 = 0;
    uint32_t g_previous_Range_Display_Unit_Day_32 = 0;

    uint32_t g_previous_RTC_TIME_STAMP_ST_Night = 0;
    RTC_TIME_STAMP_ST g_previous_l_display_date_Month_Night_u32;
    uint32_t g_previous_Service_Remainder_Distance_Night_32 = 0;

    uint32_t g_previous_RTC_TIME_STAMP_ST_Day = 0;
    RTC_TIME_STAMP_ST g_previous_l_display_date_Month_Day_u32;
    uint32_t g_previous_Service_Remainder_Distance_Day_32 = 0;

    signed int Date_Lb1_val[2] = {92, 18};
    signed int Date_Night_Lb1_val[2] = {92, 16};

    uint8_t fl_Get_Current_TripInfo_Time_Foramt;
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
    void RTMI_Range_Night_Entry(void)
    {
        lv_obj_clear_flag(guider_ui.screen_contscr_1, LV_OBJ_FLAG_HIDDEN);

        lv_obj_clear_flag(guider_ui.screen_L2_unit, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_L1_unit, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_L1_val, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_trip_container, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_size(guider_ui.screen_L1_val, 50, 18);

        lv_obj_move_foreground(guider_ui.screen_Trip_blank);

        lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
        set_obj_opa_S(guider_ui.screen_L2_val, 0);

        lv_obj_add_flag(guider_ui.screen_up_arr, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_dw_arr, LV_OBJ_FLAG_HIDDEN);

        lv_label_set_text_fmt(guider_ui.screen_L2_lbl, "Range");
        lv_label_set_text(guider_ui.screen_L1_lbl, "RTMi");
        lv_label_set_text(guider_ui.screen_L2_unit, "km");

       lv_obj_set_style_text_font(guider_ui.screen_L1_unit, &lv_font_FjallaOne_Regular_17, 0);
		lv_obj_set_style_text_font(guider_ui.screen_L2_unit, &lv_font_FjallaOne_Regular_17, 0);

        for (int i = 0; i <= 5; i++)
		{
			lv_obj_set_pos((lv_obj_t*)g_Trip_Info_Pos_Table[i].Night_Label_Name->class_p, g_Trip_Info_Pos_Table[i].Label_X_Pos[0], g_Trip_Info_Pos_Table[i].Label_Y_Pos[0]);
  		}

        fl_Get_Current_TripInfo_Time_Foramt = GUI_Get_Time_Format();

        if (fl_Get_Current_TripInfo_Time_Foramt == CLOCK_12HR_FORMAT)
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
        g_previous_Rtmi_Value_Night_u32 = 0xFF;
        g_previous_Range_Display_Unit_Night_32 = 0xFF;
        g_previous_Range_Display_Night_32 = 0xFF;
    }
    void RTMI_Range_Night_Exit(void)
    {

        lv_obj_add_flag(guider_ui.screen_up_arr, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_dw_arr, LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(guider_ui.screen_contscr_1, LV_OBJ_FLAG_HIDDEN);

    }

    void RTMI_Range_Night_During(void)
    {   

        uint32_t fl_present_Rtmi_Value_Night_u32 = displayed_IFE();
        uint32_t fl_present_Range_Display_Night_32 = display_DTE();
        uint32_t fl_present_Range_Display_unit_Night_32 = Fuel_Consumption_fn();

        if ((g_previous_Rtmi_Value_Night_u32 != fl_present_Rtmi_Value_Night_u32) ||
            (g_previous_Range_Display_Unit_Night_32 != fl_present_Range_Display_unit_Night_32) )
        {

            g_previous_Rtmi_Value_Night_u32 = fl_present_Rtmi_Value_Night_u32;
            g_previous_Range_Display_Unit_Night_32 = fl_present_Range_Display_unit_Night_32;

            if (g_previous_Range_Display_Unit_Night_32 == Lper100km)
            {
                lv_label_set_text(guider_ui.screen_L1_unit, "L/100km");
                if (g_previous_Rtmi_Value_Night_u32 == TC_INVALID)
                {

                    lv_label_set_text(guider_ui.screen_L1_val, "---.-");
                }
                else
                {
                    /* To avoid Divide by zero exception */
                    if(g_previous_Rtmi_Value_Night_u32 == 0)
                    {
                       g_previous_Rtmi_Value_Night_u32 = 0;
                    }
                    else
                    {
                        g_previous_Rtmi_Value_Night_u32 = 10000 / g_previous_Rtmi_Value_Night_u32;
  
                    }

                    /* Max limit validate*/
                    SWC_TC_Max_Limit_Check_For_RTMI_In_LPer100KM(&g_previous_Rtmi_Value_Night_u32);
                    
                    lv_label_set_text_fmt(guider_ui.screen_L1_val, "%d.%d", (g_previous_Rtmi_Value_Night_u32 / 10), (g_previous_Rtmi_Value_Night_u32 % 10));
                }
            }

            else if (g_previous_Range_Display_Unit_Night_32 == KmperL)
            {
                lv_label_set_text(guider_ui.screen_L1_unit, "km/L");
                if (g_previous_Rtmi_Value_Night_u32 == TC_INVALID)
                {
                    lv_label_set_text(guider_ui.screen_L1_val, "---.-");
                }
                else
                {
                    lv_label_set_text_fmt(guider_ui.screen_L1_val, "%d.%d", (g_previous_Rtmi_Value_Night_u32 / 10), (g_previous_Rtmi_Value_Night_u32 % 10));
                }
            }
            else if (g_previous_Range_Display_Unit_Night_32 == MiperL)
            {
                lv_label_set_text(guider_ui.screen_L1_unit, "km/L");
                if (g_previous_Rtmi_Value_Night_u32 == TC_INVALID)
                {
                    lv_label_set_text(guider_ui.screen_L1_val, "---.-");
                }
                else
                {
                    lv_label_set_text_fmt(guider_ui.screen_L1_val, "%d.%d", (g_previous_Rtmi_Value_Night_u32 / 10), (g_previous_Rtmi_Value_Night_u32 % 10));
                }
            }
            else
            {
                lv_label_set_text(guider_ui.screen_L1_unit, "km/L");
                if (g_previous_Rtmi_Value_Night_u32 == TC_INVALID)
                {
                    lv_label_set_text(guider_ui.screen_L1_val, "---.-");
                }
                else
                {
                    lv_label_set_text_fmt(guider_ui.screen_L1_val, "%d.%d", (g_previous_Rtmi_Value_Night_u32 / 10), (g_previous_Rtmi_Value_Night_u32 % 10));
                }
            }
        }
        else
        {
            /*Do Nothing*/
        }

        if ((g_previous_Range_Display_Night_32 != fl_present_Range_Display_Night_32))
        {
            g_previous_Range_Display_Night_32 = fl_present_Range_Display_Night_32;

            if (g_previous_Range_Display_Night_32 == TC_INVALID)
            {
                lv_label_set_text(guider_ui.screen_L2_val, "---");
                lv_label_set_text(guider_ui.screen_L2_unit, "km");
            }
            else
            {
                lv_label_set_text_fmt(guider_ui.screen_L2_val, "%d", (g_previous_Range_Display_Night_32));
                lv_label_set_text(guider_ui.screen_L2_unit, "km");
            }
        }

        lv_img_set_src(guider_ui.screen_Trip_blank, &_img_night_display_units_fuel_icon_30x30);
        
    }

    int16_t Debug_date[2] = {-15, 12};

    void GUI_Service_Remainder_Night_Entry(void)
    {
        lv_obj_set_size(guider_ui.screen_L1_val, Date_Night_Lb1_val[0], Date_Night_Lb1_val[1]);

        lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);
        lv_obj_move_foreground(guider_ui.screen_Trip_blank);

        lv_obj_add_flag(guider_ui.screen_trip_container, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_contscr_1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_L1_lbl, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_L2_unit, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_up_arr, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_dw_arr, LV_OBJ_FLAG_HIDDEN);

        lv_label_set_text(guider_ui.screen_L1_lbl, "Date");
        lv_label_set_text(guider_ui.screen_L2_lbl, "Service Due");
        lv_label_set_text_fmt(guider_ui.screen_L2_unit, "km");

        lv_obj_set_pos(guider_ui.screen_L1_lbl, Debug_date[0], Debug_date[1]);

        lv_obj_add_flag(guider_ui.screen_Sub_Con,LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_style_text_font(guider_ui.screen_L1_unit, &lv_font_FjallaOne_Regular_14, 0);
		lv_obj_set_style_text_font(guider_ui.screen_L2_unit, &lv_font_FjallaOne_Regular_14, 0);


        for (int i = 6; i <= 11; i++)
		{
			lv_obj_set_pos((lv_obj_t*)g_Trip_Info_Pos_Table[i].Night_Label_Name->class_p, g_Trip_Info_Pos_Table[i].Label_X_Pos[0], g_Trip_Info_Pos_Table[i].Label_Y_Pos[0]);
		}

        fl_Get_Current_TripInfo_Time_Foramt = GUI_Get_Time_Format();

        if (fl_Get_Current_TripInfo_Time_Foramt == CLOCK_12HR_FORMAT)
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
        g_previous_l_display_date_Month_Night_u32.day = 0xFF;
        g_previous_l_display_date_Month_Night_u32.month = 0xFF;
        g_previous_l_display_date_Month_Night_u32.year = 0xFF;
        g_previous_Service_Remainder_Distance_Night_32 = 0xFF;
        
    }

    void GUI_Service_Remainder_Night_Exit(void)
    {

        lv_obj_clear_flag(guider_ui.screen_up_arr, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_dw_arr, LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(guider_ui.screen_contscr_1, LV_OBJ_FLAG_HIDDEN);

    }

    void GUI_Service_Remainder_Night_During(void)
    {       
       
        SNVS_Type *base_add;

        RTC_TIME_STAMP_ST fl_present_l_display_date_Month_Night_u32;

        fl_present_l_display_date_Month_Night_u32 = RTC_Time_Display();
        uint32_t fl_present_Service_Remainder_Distance_Night_u32 = Swc_Service_Remainder_Get_Due_Distance();
        lv_img_set_src(guider_ui.screen_Trip_blank, &_img_night_service_icon_30x30);

        if ((g_previous_l_display_date_Month_Night_u32.day != fl_present_l_display_date_Month_Night_u32.day) || (g_previous_l_display_date_Month_Night_u32.month != fl_present_l_display_date_Month_Night_u32.month) ||
            (g_previous_l_display_date_Month_Night_u32.year != fl_present_l_display_date_Month_Night_u32.year) )
        {

            g_previous_l_display_date_Month_Night_u32.day = fl_present_l_display_date_Month_Night_u32.day;
            g_previous_l_display_date_Month_Night_u32.month = fl_present_l_display_date_Month_Night_u32.month;
            g_previous_l_display_date_Month_Night_u32.year = fl_present_l_display_date_Month_Night_u32.year;

            if (g_previous_l_display_date_Month_Night_u32.day <= 9)

            {
                if (g_previous_l_display_date_Month_Night_u32.month <= 9)
                {
                    lv_label_set_text_fmt(guider_ui.screen_L1_val, "0%d.0%d.%d", (g_previous_l_display_date_Month_Night_u32.day), (g_previous_l_display_date_Month_Night_u32.month), (g_previous_l_display_date_Month_Night_u32.year));
                }
                else
                {
                    lv_label_set_text_fmt(guider_ui.screen_L1_val, "0%d.%d.%d", (g_previous_l_display_date_Month_Night_u32.day), (g_previous_l_display_date_Month_Night_u32.month), (g_previous_l_display_date_Month_Night_u32.year));
                }
            }
            else
            {
                if (g_previous_l_display_date_Month_Night_u32.month <= 9)
                {
                    lv_label_set_text_fmt(guider_ui.screen_L1_val, "%d.0%d.%d", (g_previous_l_display_date_Month_Night_u32.day), (g_previous_l_display_date_Month_Night_u32.month), (g_previous_l_display_date_Month_Night_u32.year));
                }
                else
                {
                    lv_label_set_text_fmt(guider_ui.screen_L1_val, "%d.%d.%d", (g_previous_l_display_date_Month_Night_u32.day), (g_previous_l_display_date_Month_Night_u32.month), (g_previous_l_display_date_Month_Night_u32.year));
                }
            }
        }

        if(fl_present_Service_Remainder_Distance_Night_u32 == 0xFFFF)
        {
            lv_label_set_text_fmt(guider_ui.screen_L1_unit, "");

            lv_label_set_text_fmt(guider_ui.screen_L2_val, "----");

            lv_img_set_src(guider_ui.screen_Sub_Con, &_Layer_0_9x9);

        }
        else if ((g_previous_Service_Remainder_Distance_Night_32 != fl_present_Service_Remainder_Distance_Night_u32))
        {

            g_previous_Service_Remainder_Distance_Night_32 = fl_present_Service_Remainder_Distance_Night_u32;

            lv_label_set_text_fmt(guider_ui.screen_L1_unit, "");

            lv_label_set_text_fmt(guider_ui.screen_L2_val, "%d", (g_previous_Service_Remainder_Distance_Night_32));

            lv_img_set_src(guider_ui.screen_Sub_Con, &_Layer_0_9x9);
        }
    }

    void GUI_RTMI_Range_Day_Entry(void)
    {

        lv_obj_clear_flag(guider_ui.screen_day_inter_con2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_day_in_arr1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_day_in_arr2, LV_OBJ_FLAG_HIDDEN);

        lv_label_set_text(guider_ui.screen_day_in_lb1, "RTMi");
        lv_label_set_text(guider_ui.screen_day_in_lb4, "Range");
        lv_label_set_text(guider_ui.screen_day_in_lb6, "km");
        lv_obj_set_size(guider_ui.screen_day_in_lb2, 50, 18);
        lv_obj_set_style_text_align(guider_ui.screen_day_in_lb2, LV_TEXT_ALIGN_RIGHT, 0);

        lv_img_set_src(guider_ui.screen_Trip_blank, &fuel_day_icon);
        lv_obj_move_foreground(guider_ui.screen_Trip_blank);
        lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

        lv_obj_set_style_text_font(guider_ui.screen_day_in_lb3, &lv_font_FjallaOne_Regular_17, 0);
		lv_obj_set_style_text_font(guider_ui.screen_day_in_lb6, &lv_font_FjallaOne_Regular_17, 0);

        lv_obj_set_style_text_align(guider_ui.screen_day_in_lb5, LV_TEXT_ALIGN_RIGHT, 0);

        for (int i = 0; i <= 5; i++)
		{
			lv_obj_set_pos((lv_obj_t*)g_Trip_Info_Pos_Table[i].Day_Label_Name->class_p, g_Trip_Info_Pos_Table[i].Label_X_Pos[0], g_Trip_Info_Pos_Table[i].Label_Y_Pos[0]);
		}

        /* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
        g_previous_Rtmi_Value_Day_u32 = 0xFF;
        g_previous_Range_Display_Unit_Day_32 = 0xFF;
        g_previous_Range_Display_Day_32 = 0xFF;
    }

    void GUI_RTMI_Range_Day_During(void)
    {

        uint32_t fl_present_Rtmi_Value_Day_u32 = displayed_IFE();
        uint32_t fl_present_Range_Display_Day_32 = display_DTE();
        uint32_t fl_present_Range_Display_Unit_Day_32 = Fuel_Consumption_fn();

        if ((g_previous_Rtmi_Value_Day_u32 != fl_present_Rtmi_Value_Day_u32) ||
            (g_previous_Range_Display_Unit_Day_32 != fl_present_Range_Display_Unit_Day_32) )
        {

            g_previous_Rtmi_Value_Day_u32 = fl_present_Rtmi_Value_Day_u32;
            g_previous_Range_Display_Unit_Day_32 = fl_present_Range_Display_Unit_Day_32;

            if (g_previous_Range_Display_Unit_Day_32 == Lper100km)
            {
                lv_label_set_text(guider_ui.screen_day_in_lb3, "L/100km");
                if (g_previous_Rtmi_Value_Day_u32 == TC_INVALID)
                {
                    g_previous_Rtmi_Value_Day_u32 = TC_INVALID;
                    lv_label_set_text(guider_ui.screen_day_in_lb2, "---.-");
                }
                else
                {
                    /* To avoid Divide by zero exception */
                    if( g_previous_Rtmi_Value_Day_u32 == 0)
                    {
                       g_previous_Rtmi_Value_Day_u32 = 0;
                    }
                    else
                    {
                        g_previous_Rtmi_Value_Day_u32 = 10000 / g_previous_Rtmi_Value_Day_u32;

                    }

                    /* Max limit validate*/
                    SWC_TC_Max_Limit_Check_For_RTMI_In_LPer100KM(&g_previous_Rtmi_Value_Day_u32);

                    lv_label_set_text_fmt(guider_ui.screen_day_in_lb2, "%d.%d", (g_previous_Rtmi_Value_Day_u32 / 10), (g_previous_Rtmi_Value_Day_u32 % 10));
                }
            }
            else if (g_previous_Range_Display_Unit_Day_32 == KmperL)
            {
                lv_label_set_text(guider_ui.screen_day_in_lb3, "km/L");
                if (g_previous_Rtmi_Value_Day_u32 == TC_INVALID)
                {
                    lv_label_set_text(guider_ui.screen_day_in_lb2, "---.-");
                }
                else
                {
                    lv_label_set_text_fmt(guider_ui.screen_day_in_lb2, "%d.%d", (g_previous_Rtmi_Value_Day_u32 / 10), (g_previous_Rtmi_Value_Day_u32 % 10));
                }
            }
            else if (g_previous_Range_Display_Unit_Day_32 == MiperL)
            {
                lv_label_set_text(guider_ui.screen_day_in_lb3, "km/L");
                if (g_previous_Rtmi_Value_Day_u32 == TC_INVALID)
                {
                    lv_label_set_text(guider_ui.screen_day_in_lb2, "---.-");
                }
                else
                {
                    lv_label_set_text_fmt(guider_ui.screen_day_in_lb2, "%d.%d", g_previous_Rtmi_Value_Day_u32 / 10), (g_previous_Rtmi_Value_Day_u32 % 10);
                }
            }
            else
            {
                lv_label_set_text(guider_ui.screen_day_in_lb3, "km/L");
                if (g_previous_Rtmi_Value_Day_u32 == TC_INVALID)
                {
                    lv_label_set_text(guider_ui.screen_day_in_lb2, "---.-");
                }
                else
                {
                    lv_label_set_text_fmt(guider_ui.screen_day_in_lb2, "%d.%d", (g_previous_Rtmi_Value_Day_u32 / 10), (g_previous_Rtmi_Value_Day_u32 % 10));
                }
            }
        }
        else
        {
            /*Do Nothing*/
        }

        if ((g_previous_Range_Display_Day_32 != fl_present_Range_Display_Day_32))
        {
            g_previous_Range_Display_Day_32 = fl_present_Range_Display_Day_32;

            if (g_previous_Range_Display_Day_32 == TC_INVALID)
            {
                lv_label_set_text(guider_ui.screen_day_in_lb5, "---");
                lv_label_set_text(guider_ui.screen_day_in_lb6, "km");
            }
            else
            {
                lv_label_set_text_fmt(guider_ui.screen_day_in_lb5, "%d", (g_previous_Range_Display_Day_32));
            }
        }

    }
    void GUI_RTMI_Range_Day_Exit(void)
    {
        /* hide container for RTMI screen */
        lv_obj_add_flag(guider_ui.screen_day_inter_con2, LV_OBJ_FLAG_HIDDEN);
    }

    int16_t Day_Debug_date[2] = {-15, 12};
    
    void GUI_Service_Remainder_Day_Entry(void)
    {
        lv_obj_clear_flag(guider_ui.screen_day_inter_con2, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(guider_ui.screen_day_in_lb1, "Date");
        lv_label_set_text(guider_ui.screen_day_in_lb4, "Service Due");
        lv_label_set_text(guider_ui.screen_day_in_lb6, "km");
        lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_day_in_arr1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_day_in_arr2, LV_OBJ_FLAG_HIDDEN);

        lv_img_set_src(guider_ui.screen_Trip_blank, &service_day_Icon);
        lv_obj_move_foreground(guider_ui.screen_Trip_blank);
        lv_obj_set_pos(guider_ui.screen_day_in_lb1, Day_Debug_date[0], Day_Debug_date[1]);
        lv_obj_set_pos(guider_ui.screen_Trip_blank, 105, 252);

        lv_obj_set_style_text_font(guider_ui.screen_day_in_lb3, &lv_font_FjallaOne_Regular_14, 0);
		lv_obj_set_style_text_font(guider_ui.screen_day_in_lb6, &lv_font_FjallaOne_Regular_14, 0);

        for (int i = 6; i <= 11; i++)
		{
			lv_obj_set_pos((lv_obj_t*)g_Trip_Info_Pos_Table[i].Day_Label_Name->class_p, g_Trip_Info_Pos_Table[i].Label_X_Pos[0], g_Trip_Info_Pos_Table[i].Label_Y_Pos[0]);
		}

        /* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
        g_previous_l_display_date_Month_Day_u32.day = 0xFF;
        g_previous_l_display_date_Month_Day_u32.month = 0xFF;
        g_previous_l_display_date_Month_Day_u32.year = 0xFF;
        g_previous_Service_Remainder_Distance_Day_32 = 0xFF;

        lv_obj_set_style_text_align(guider_ui.screen_day_in_lb5, LV_TEXT_ALIGN_RIGHT, 0);
    }
    void GUI_Service_Remainder_Day_During(void)
    {

        SNVS_Type *base_add;
        RTC_TIME_STAMP_ST fl_present_l_display_date_Month_Day_u32;
        fl_present_l_display_date_Month_Day_u32 = RTC_Time_Display();
        uint32_t fl_present_Service_Remainder_Distance_Day_u32 = Swc_Service_Remainder_Get_Due_Distance();       

        if ((g_previous_l_display_date_Month_Day_u32.day != fl_present_l_display_date_Month_Day_u32.day) ||
            (g_previous_l_display_date_Month_Day_u32.month != fl_present_l_display_date_Month_Day_u32.month) ||
            (g_previous_l_display_date_Month_Day_u32.year != fl_present_l_display_date_Month_Day_u32.year))
        {

            g_previous_l_display_date_Month_Day_u32.day = fl_present_l_display_date_Month_Day_u32.day;
            g_previous_l_display_date_Month_Day_u32.month = fl_present_l_display_date_Month_Day_u32.month;
            g_previous_l_display_date_Month_Day_u32.year = fl_present_l_display_date_Month_Day_u32.year;

            if (g_previous_l_display_date_Month_Day_u32.day <= 9)
            {
                if (g_previous_l_display_date_Month_Day_u32.month <= 9)
                {
                    lv_label_set_text_fmt(guider_ui.screen_day_in_lb2, "0%d.0%d.%d", (g_previous_l_display_date_Month_Day_u32.day), (g_previous_l_display_date_Month_Day_u32.month), (g_previous_l_display_date_Month_Day_u32.year));
                }
                else
                {
                    lv_label_set_text_fmt(guider_ui.screen_day_in_lb2, "0%d.%d.%d", (g_previous_l_display_date_Month_Day_u32.day), (g_previous_l_display_date_Month_Day_u32.month), (g_previous_l_display_date_Month_Day_u32.year));
                }
            }
            else
            {
                if (g_previous_l_display_date_Month_Day_u32.month <= 9)
                {
                    lv_label_set_text_fmt(guider_ui.screen_day_in_lb2, "%d.0%d.%d", (g_previous_l_display_date_Month_Day_u32.day), (g_previous_l_display_date_Month_Day_u32.month), (g_previous_l_display_date_Month_Day_u32.year));
                }
                else
                {
                    lv_label_set_text_fmt(guider_ui.screen_day_in_lb2, "%d.%d.%d", (g_previous_l_display_date_Month_Day_u32.day), (g_previous_l_display_date_Month_Day_u32.month), (g_previous_l_display_date_Month_Day_u32.year));
                }
            }
        }

        if(fl_present_Service_Remainder_Distance_Day_u32 == 0xFFFF)
        {
            lv_obj_set_size(guider_ui.screen_day_in_lb2, Date_Lb1_val[0], Date_Lb1_val[1]);
            lv_label_set_text_fmt(guider_ui.screen_day_in_lb3, "");

            lv_label_set_text_fmt(guider_ui.screen_day_in_lb5, "----");

        }
        else if ((g_previous_Service_Remainder_Distance_Day_32 != fl_present_Service_Remainder_Distance_Day_u32) )
        {

            g_previous_Service_Remainder_Distance_Day_32 = fl_present_Service_Remainder_Distance_Day_u32;

            lv_obj_set_size(guider_ui.screen_day_in_lb2, Date_Lb1_val[0], Date_Lb1_val[1]);
            lv_label_set_text_fmt(guider_ui.screen_day_in_lb3, "");

            lv_label_set_text_fmt(guider_ui.screen_day_in_lb5, "%d", (g_previous_Service_Remainder_Distance_Day_32));

        }
        
    }
    void GUI_Service_Remainder_Day_Exit(void)
    {
        lv_obj_add_flag(guider_ui.screen_day_inter_con2, LV_OBJ_FLAG_HIDDEN);
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
