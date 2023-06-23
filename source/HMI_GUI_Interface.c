/*
 *    ENTRY - DURING - EXIT FUNCTION DEFINITONS
 *
 *
 */

/*
 *   INCLDUE
 */

#include "lvgl_app.h"
#include "gui_guider.h"
#include "HMI_Music.h"
#include "HMI_Setting_Screen.h"
#include "Button_Manager_Cfg.h"
#include "Swc_Voltage_Battery_St.h"
#include "TC.h"
#include "Swc_TFT_Illum.h"
#include "Fuel_Guage.h"
#include "fsl_lpuart.h"
#include "Ambient_light_sensor_Cfg.h"
#include "BLE_music_module.h"
#include "HMI_GUI_Interface.h"
#include "HMI_Main_Screen.h"
#include "task.h"
#include "lvgl_app.h"
#include "HMI_Gear.h"
#include "HMI_Clock.h"
#include "HMI_Phone.h"
#include "HMI_Setting_Screen.h"
#include "Swc_Trip_Timer.h"
#include "Swc_Averege_Speed.h"
#include "BLE_call_module.h"
#include "HMI_Speedometer.h"
#include "Swc_Odometer.h"

#define BLE_CONNECTED 1
#define BLE_DISCONNECTED 0
signed int Holdbtnpos[6] = {95, 100, 95, 195, 95, 148};
signed int var = 0;
signed int Hr24pos[4] = {180, 152, 103, 198};
signed int disrbpos[2] = {180, 150};
extern uint32_t g_HomeScreen_Flag;
extern uint8_t g_NVM_Menu_Selection_Data_u8;
extern uint8_t fl_Get_Current_Time_Foramt;
extern TaskHandle_t TachoHandleTask;

uint32_t g_PrevIntermediateScreen_U32 = INTERMED_TRIPA;

extern uint32_t g_demanded_tacho_value_u8;
extern uint32_t g_current_tacho_index_u8;
extern g_Tacho_image g_tacho_img_table[201];

bool g_RADIOBUTTON_Status = FALSE;
uint32_t g_previous_Bike_TripA_Value_night_u32 = 0;
uint8_t g_previous_Bike_Trip_time_hour_night_u8 = 0;
uint8_t g_previous_Bike_Trip_time_Minute_night_u8 = 0;
uint8_t g_previous_Bike_Trip_time_hour_Day_u8 = 0;
uint8_t g_previous_Bike_Trip_time_Minute_Day_u8 = 0;

uint32_t g_previous_Bike_TripA_AVSValue_night_u32 = 0;
uint32_t g_previous_Bike_TripA_AVFValue_night_u32 = 0;
uint32_t g_previous_Bike_TripA_AVFValue_Unit_Set_night_u32 = 0;

uint32_t g_previous_Bike_TripB_AVFValue_night_u32 = 0;

uint32_t g_previous_Bike_TripB_AVFValue_Day_u32 = 0;
uint32_t g_previous_Bike_TripB_AVFValue_Unit_Set_Day_u32 = 0;
uint32_t g_previous_Bike_TripB_Value_Day_u32 = 0;
uint32_t g_previous_Bike_TripB_AVSValue_Day_u32 = 0;

uint32_t g_previous_Bike_TripA_AVFValue_Day_u32 = 0;
uint32_t g_previous_Bike_TripA_AVFValue_Unit_Set_Day_u32 = 0;
uint32_t g_previous_Bike_TripA_AVSValue_Day_u32 = 0;

uint32_t g_previous_Bike_TripA_Value_Day_u32 = 0;

uint32_t g_previous_Bike_TripB_AVFValue_Unit_Set_night_u32 = 0;
uint32_t g_previous_Bike_TripB_AVSValue_night_u32 = 0;
uint32_t g_previous_Bike_TripB_Value_night_u32 = 0;
uint32_t g_previous_Vehicle_Battery_Day_st_u32 = 0;
uint32_t g_previous_Vehicle_Battery_Night_st_u32 = 0;

uint8_t g_Fuel_Current_Unit;

uint8_t g_BleContactEvent_U8 = Contact_0;
uint8_t g_BLE_Connectivity_Status_U8;

extern uint8_t g_UpKeypressed_U8;
extern uint8_t g_DownKeypressed_U8;

uint8_t g_SettingUpArrowPressed_U8 = 0;
uint8_t g_SettingDownArrowPressed_U8 = 0;

HMI_USERNAME_Info_st g_user_name_Info_ptr;

/* MAPPING TABLE FOR THE INTERMEDIATE SCREEN TO SKIP ONLY ENABLED AND SELECTED */
const IntermediateMapTblType_St IntermediateMapTblSt[MAX_MENU_SELECTION] =
    {
        {MENU_SELECTION_TRIPA, INTERMED_TRIPA},
        {MENU_SELECTION_TRIPB, INTERMED_TRIPB},
        {MENU_SELECTION_FUEL, INTERMED_RTMI},
        {MENU_SELECTION_NAVIGATION, INTERMED_NAVIGATION_ETA},
        {MENU_SELECTION_GI, INTERMED_SERVICE_REMINDER},
        {MENU_SELECTION_PHONE, INTERMED_CONTACTS},
        {MENU_SELECTION_MUSIC, INTERMED_MUSIC},
        {MENU_SELECTION_VOLUME, INTERMED_VOLUME},
};

/* HOLD THE PREV SCREEN VALUE */
extern uint32_t g_PrevScreen_U32;

void HomeScreenEntryFn(void)
{
    uint8_t fl_ambient_mode;

    g_HomeScreen_Flag = 1;
    Main_Screen_night_obj_create(&guider_ui);  /* INIT THE CURRENT SCREEN OBJECTS */
    lv_scr_load(guider_ui.screen); /* LOAD THE CREATED OBJECS */
    vTaskResume(TachoHandleTask);
    Gear_Night_Entry();
    GUI_Clock_Entry();
    /* Init  Events For Onchange Value */
    GUI_SpeedoMeter_Previous_Change();
    Intermediate_Speedo_Entry();
    Odo_MainScreen_Entry();
    Telltale_Previous_Entry();
    GUI_BLE_Events_Entry();
    FuelValueEntry();

    fl_ambient_mode = Get_day_night_mode_status();

    if(fl_ambient_mode == 1)
    {
        lv_obj_move_foreground(guider_ui.screen_imgKmph);
    }
}


void HomeScreenEntry_Day(void)
{
    g_HomeScreen_Flag = 1;
    Main_Screen_Day_obj_create(&guider_ui);  /* INIT THE CURRENT SCREEN OBJECTS */
    lv_scr_load(guider_ui.screen); /* LOAD THE CREATED OBJECS */
    vTaskResume(TachoHandleTask);
    Gear_Day_Entry();
    GUI_Clock_Entry();
    /* Init  Events For Onchange Value */
    GUI_SpeedoMeter_Previous_Change();
    Odo_MainScreen_Entry();
    Telltale_Previous_Entry();
    GUI_BLE_Events_Entry();
    FuelValueEntry();
}

void IntermediateScreen_Night_Entry(void)
{
   g_HomeScreen_Flag = 1;
   Inter_Screen_night_obj_create(&guider_ui); /* INIT THE CURRENT SCREEN OBJECTS */
    lv_scr_load(guider_ui.screen); /* LOAD THE CREATED OBJECS */
    vTaskResume(TachoHandleTask);
    Gear_Night_Entry();
    GUI_Clock_Entry();

    /* Hide all intermediate container. 
     * container shall be enabled/disabled based on screen needs in its entry*/
    Intermediate_Hide_Night_Container();
    lv_obj_add_flag(guider_ui.screen_imgKmph,LV_OBJ_FLAG_HIDDEN);
    /* Init  Events For Onchange Value */
    GUI_SpeedoMeter_Previous_Change();
    Intermediate_Speedo_Entry();
    Telltale_Previous_Entry();
    GUI_BLE_Events_Entry();
    FuelValueEntry();
}


void Intermediate_Screen_Day_Entry(void)
{
    uint8_t fl_Get_Current_Time_Foramt;

    g_HomeScreen_Flag = 1;
    Intermediate_Screen_Day_obj_create(&guider_ui);  /* INIT THE CURRENT SCREEN OBJECTS */
    lv_scr_load(guider_ui.screen); /* LOAD THE CREATED OBJECS */
    vTaskResume(TachoHandleTask);

    /* Hide all intermediate container. 
     * container shall be enabled/disabled based on screen needs in its entry*/
    Intermediate_Hide_Day_Container();

    Gear_Day_Entry();
    GUI_Clock_Entry();
    /* Init  Events For Onchange Value */
    GUI_SpeedoMeter_Previous_Change();
    Telltale_Previous_Entry();
    GUI_BLE_Events_Entry();
    Intermediate_Speedo_Entry();

    fl_Get_Current_Time_Foramt = GUI_Get_Time_Format();

    if (fl_Get_Current_Time_Foramt == CLOCK_12HR_FORMAT)
    {
        GUI_Intermediate12hr_position();
    }
    else
    {
        GUI_Intermediate24hr_position();
    }
    FuelValueEntry();
}

void HomeScreenLocalEntry(void)
{
    /* HOME SCREEN ENTRY FUNCTION */
    GUI_Speed_Night_Entry();
    GUI_Gear_Night_Entry();

    lv_obj_move_foreground(guider_ui.screen_Service_Due);

    fl_Get_Current_Time_Foramt = GUI_Get_Time_Format();

    if (fl_Get_Current_Time_Foramt == CLOCK_12HR_FORMAT)
    {
        GUI_Main12hr_position();
    }
    else
    {
        GUI_Main24hr_position();
    }

    GUI_Main_Screen_Entry();
}

void HomeScreen_LocalEntry_Day(void)
{
    /* HOME SCREEN ENTRY FUNCTION */

    fl_Get_Current_Time_Foramt = GUI_Get_Time_Format();

    if (fl_Get_Current_Time_Foramt == CLOCK_12HR_FORMAT)
    {
        GUI_Main12hr_position();
    }
    else
    {
        GUI_Main24hr_position();
    }

    GUI_Main_Screen_Entry_Day();
    Gear_Day_Entry();
    GUI_Clock_Entry();
}

void GUI_Main_Screen_Entry_Day(void)
{
    Day_mode_RPM_images();
    GUI_Main_Screen_Day();
    lv_obj_add_flag(guider_ui.screen_contSp_Main_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.screen_day_base_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.screen_main_white_container, LV_OBJ_FLAG_HIDDEN);
    fl_Get_Current_Time_Foramt = GUI_Get_Time_Format();

    if (fl_Get_Current_Time_Foramt == CLOCK_12HR_FORMAT)
    {
        GUI_Main12hr_position();
    }
    else
    {
        GUI_Main24hr_position();
    }
    lv_obj_add_flag(guider_ui.screen_day_sub_btn, LV_OBJ_FLAG_HIDDEN);
    
}

void Passcode_Entry(void)
{
    HomeScreenEntryFn();
    HomeScreenLocalEntry();
}

void Intermediate_Hide_Night_Container(void)
{
    lv_obj_add_flag(guider_ui.screen_contscr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_navi_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_bl_pass_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_phone_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_volume_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_music_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_trip_container, LV_OBJ_FLAG_HIDDEN);
}

void Intermediate_Hide_Day_Container(void)
{
    lv_obj_add_flag(guider_ui.screen_day_trip_con, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_day_inter_con2, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.screen_Main_day_music_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_Main_day_volume_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_Main_day_phone_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_Main_day_Navigation, LV_OBJ_FLAG_HIDDEN);
     lv_obj_add_flag(guider_ui.screen_Passcode_Day_container, LV_OBJ_FLAG_HIDDEN);
}

void HomeScreenDay_Exit(void)
{
   
}

void HomeScreenDuringFn(void)
{
    GUI_Main_Screen();
    lv_obj_clear_flag(guider_ui.screen_contSp_Main_2, LV_OBJ_FLAG_HIDDEN);
}

void HomeScreen_Day_DuringFn(void)
{
    GUI_Main_Screen_Day();
}

void Day_mode_RPM_images(void)
{
    lv_img_set_src(guider_ui.screen_Day_1000_rpm, &img_day_x1000_RPM_new);
    lv_img_set_src(guider_ui.screen_day_gear_up, &img_day_gear_arrows_up_white);
    lv_img_set_src(guider_ui.screen_day_gear_down, &img_day_gear_arrows_down_white);
}

void HomeScreenExitFn(void)
{
    lv_obj_del(lv_scr_act()); /* DELETE THE CURRENT SCREEN OBJECT CREATED */
    g_HomeScreen_Flag = 0;
    vTaskSuspend(TachoHandleTask);
}




void SettingScreenEntryFn(void)
{
    setup_scr_Setting_Screen(&guider_ui);
    Hide_container();
    lv_scr_load(guider_ui.Setting_Screen);
    GUI_Clock_Entry();
}

void HomeScreenExit_Day(void)
{
    lv_obj_del(lv_scr_act()); /* DELETE THE CURRENT SCREEN OBJECT CREATED */
    g_HomeScreen_Flag = 0;
    vTaskSuspend(TachoHandleTask);
}

void SettingScreenDuringFn(void)
{
    /* When speed is above 10km/h, then cluster shall exit from setting screen and move to home screen*/
    if (HMI_Setting_Screen_Is_Exit_Cond_Met() == TRUE)
    {
        /* Set event to trigger screen transition*/
        Set_Event(LEFT_BUTTON_LONG_PRESS);
    }
    else
    {
        Setting_Screen_During_Fn();
    }
}

void HomeScreenMain_DayDuring(void)
{
    /* Function For Day Mode During */
    if (GetCrntScreen() == HOME_SCREEN)
    {
        GUI_Day_Speedometer_Handler();
    }
    else
    {
      GUI_Intermediate_Speedometer_Handler_Day();
    }

    GUI_Fuelmeter_Handler();
    GUI_HMI_Clk_Day_Handler();
    GUI_Gear_Poition_Handler_Day();
    GUI_Telltale_Handler();

    /* Screen Handling */
    GUiTachoHandler();

    /* BLE Missed Call, Battery, Signal, SMS Functions*/
    GUI_Phone_Screen_Day();
    GUI_Signal_Day();
    GUI_Phone_SMS_info_Day();
    GUI_Phone_Missed_call_Info_Day();
}

void HomeScreenMainDuringFn(void)
{
    if (GetCrntScreen() == HOME_SCREEN)
    {
        GUI_Speedometer_Handler();
    }
    else
    {
        GUI_Intermediate_Speedometer_Handler();
    }

    GUI_Fuelmeter_Handler();
    GUI_HMI_CLK_Night_Handler();
    GUI_Gear_Poition_Handler();
    GUI_Telltale_Handler();

    /* Screen Handling */
    GUiTachoHandler();

    /* BLE Missed Call, Battery, Signal, SMS Functions*/
    GUI_Phone_Screen();
    GUI_Signal();
    GUI_Phone_SMS_info();
    GUI_Phone_Missed_call_Info();
}

uint8_t ResetTripA(void)
{
    HMI_TRIP_Timer_SW_Reset_Cmd(0);
    return 0;
}

uint8_t ResetTripB(void)
{
    HMI_TRIP_Timer_SW_Reset_Cmd(1);
    return 0;
}

void Hide_container(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_main_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_main_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_bike_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_bike_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_about_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_about_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_display_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_display_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_connect_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_connect_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_music_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_music_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_brightness_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_brightness_day_contain, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_menu_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_menu_day_contain, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_seting_date_time_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_seting_date_time_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_unit_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_bike_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_unit_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_units_sub_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_units_day_sub_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_about_inf_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_about_inf_nigh_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_date_set_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_date_set_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_12_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_12_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_battery_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_battery_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_trip_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_trip_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_disc_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_disc_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Setting_disclaimer_night_new, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Setting_disclaimer_day_new, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_setting_ghost_images, LV_OBJ_FLAG_HIDDEN);
}

/***************************************************************Day Home and Intermediate Screen ****************************/

/********************DAY - NIGHT Criteria *******/
#if 0
uint8_t TestCrteria_DAY(void)
{
    uint8_t Decidsion = 0;
    uint8_t UserSelection = 0;  /* nvm read */
    uint8_t DayNight_mode = 0;

}


uint8_t TestCrteria_NIGHT(void)
{
    uint8_t Decidsion = 0;
    uint8_t UserSelection = 0;
    uint8_t DayNight_mode = 0;

}

#endif

/**********************************************/
extern uint8_t NVM_Setting_Write_request;
extern uint8_t g_BLE_Status_u8;
extern uint8_t g_Music_Status_u8;
extern uint8_t g_User_Brightness_Level_u8;
extern uint8_t g_User_Music_Select_Level_U8;
extern uint8_t g_Clock_Format_Selection_Cmd;
extern uint8_t g_User_Sel_TC_Unit;
extern uint8_t g_Fuel_Consum_Selection_Cnt_u8;
extern uint8_t g_Setting_Music_Selection_U8;

uint8_t Set_Bluetooth_Enable_Setting(void)
{
    NVM_Setting_Write_request = 1;

    if (g_BLE_Status_u8 == BLUETOOTH_OFF)
    {
        g_BLE_Status_u8 = (uint8_t)BLUETOOTH_ON;
        /* Send bluetooth */
        GPIO_PinWrite(GPIO9, 16, 1);
    }
    else
    {
        g_BLE_Status_u8 = (uint8_t)BLUETOOTH_OFF;
        GPIO_PinWrite(GPIO9, 16, 0);
    }

    return 0;
}

void ResetBLE(void)
{
    /* LOCAL VARIABLE */
    uint32_t fl_ResetCounter_u32 = 0;

    /* TURN OFF */
    GPIO_PinWrite(GPIO9, 16, 0);

    /* DUMMY DELAY */
    while (fl_ResetCounter_u32 < 0x100)
    {
        fl_ResetCounter_u32++;
    }

    /* TURN ON */
    GPIO_PinWrite(GPIO9, 16, 1);
}

uint8_t Set_Music_Enable_Setting(void)
{
    NVM_Setting_Write_request = 1;

    if (g_Music_Status_u8 == 0)
    {
        g_Music_Status_u8 = 1;
    }
    else
    {
        g_BLE_Status_u8 = 0;
    }

    return 0;
}

uint8_t Set_24HrModeEnable_Setting(void)
{
    if (g_RADIOBUTTON_Status)
    {
        NVM_Setting_Write_request = 1;

        if (g_Clock_Format_Selection_Cmd == 0)
        {
            g_Clock_Format_Selection_Cmd = 1;
        }
        else
        {
            g_Clock_Format_Selection_Cmd = 0;
        }
    }
    return 0;
}

uint8_t Set_BrightnessMode_Auto(void)
{
    NVM_Setting_Write_request = 1;

    g_User_Brightness_Level_u8 = AUTO_BRIGHTNESS;

    return 0;
}

uint8_t Set_BrightnessMode_LOW(void)
{
    NVM_Setting_Write_request = 1;

    g_User_Brightness_Level_u8 = LOW_BRIGHTNESS;

    return 0;
}

uint8_t Set_BrightnessMode_Medium(void)
{
    NVM_Setting_Write_request = 1;

    g_User_Brightness_Level_u8 = MEDIUM_BRIGHTNESS;

    return 0;
}

uint8_t Set_BrightnessMode_High(void)
{
    NVM_Setting_Write_request = 1;

    g_User_Brightness_Level_u8 = HIGH_BRIGHTNESS;

    return 0;
}

uint8_t Set_Fuel_consumption_unit(void)
{
    if (g_RADIOBUTTON_Status)
    {
        NVM_Setting_Write_request = 1;

        if (g_User_Sel_TC_Unit == Lper100km)
        {
            g_User_Sel_TC_Unit = KmperL;
        }
        else
        {
            g_User_Sel_TC_Unit = Lper100km;
        }
    }

    return 0;
}

uint8_t Music_Setting_Screen_Album(void)
{
    NVM_Setting_Write_request = 1;

    g_User_Music_Select_Level_U8 = ALBUM;

    /* SEND DATA THROUGH BLE - BUTTON EVENT */
    BLE_setting_MetaData_transmission_Check(Album);

    return 0;
}

uint8_t Music_Setting_Screen_Artist(void)
{
    NVM_Setting_Write_request = 1;

    g_User_Music_Select_Level_U8 = ARTIST;

    /* SEND DATA THROUGH BLE - BUTTON EVENT */
    BLE_setting_MetaData_transmission_Check(Artist);

    return 0;
}

uint8_t Music_Setting_Screen_Genre(void)
{
    NVM_Setting_Write_request = 1;

    g_User_Music_Select_Level_U8 = GENRE;

    /* SEND DATA THROUGH BLE - BUTTON EVENT */
    BLE_setting_MetaData_transmission_Check(Genre);

    return 0;
}

uint8_t IntermediateScreen_Volume_Increment(void)
{
    /* SET BLE_UART - JOYSTICK EVENT */
    BLE_music_setting_screen(Music_Volume_Increase);

    /* Key Pressed State*/
    g_UpKeypressed_U8 = Pressed_State;

    /* RETURN STATUS */
    return 0;
}

uint8_t IntermediateScreen_Volume_Decrement(void)
{
    /* SET BLE_UART - JOYSTICK EVENT */
    BLE_music_setting_screen(Music_Volume_Decrease);

    /* Key Pressed State*/
    g_DownKeypressed_U8 = Pressed_State;

    /* RETURN STATUS */
    return 0;
}

uint8_t IntermediateScreen_Contact_Increment(void)
{
    /* LOCAL VARIABLE */

    /* INCREMENT CONTACT INDEX */
    ++g_BleContactEvent_U8;

    /* CHECK FOR THE OVERFLOW */
    if (g_BleContactEvent_U8 >= Contact_4)
    {
        /* RELOAD CONTACT */
        g_BleContactEvent_U8 = Contact_0;
    }

    /* SEND CONTACT UART DATA */
    UART_DataManager_Set_Connectivity_Info(g_BleContactEvent_U8);

    /* RETURN STATUS */
    return 0;
}

uint8_t IntermediateScreen_Contact_Decrement(void)
{
    /* LOCAL VARIABLE */

    /* CHECK FOR THE UNDERFLOW */
    if (g_BleContactEvent_U8 != Contact_0)
    {
        /* DECREMENT CONTACT */
        --g_BleContactEvent_U8;
    }
    else
    {
        /* RELOAD MAX VALUE */
        g_BleContactEvent_U8 = Contact_4;
    }

    /* SEND CONTACT UART DATA */
    UART_DataManager_Set_Connectivity_Info(g_BleContactEvent_U8);

    /* RETURN STATUS */
    return 0;
}

uint8_t IntermediateScreen_Music_NextTrack(void)
{
    /* LOCAL VARIABLE */

    /* SEND DATA TO BLE_UART */
    BLE_music_setting_screen(Next_Track);

    /* Key Pressed Value*/
    g_DownKeypressed_U8 = Pressed_State;

    /* RETURN STATUS */
    return 0;
}

uint8_t IntermediateScreen_Music_PrevTrack(void)
{
    /* LOCAL VARIABLE */

    /* SEND DATA TO BLE_UART */
    BLE_music_setting_screen(Previous_Track);

    /* Key Pressed Value*/
    g_UpKeypressed_U8 = Pressed_State;

    /* RETURN STATUS */
    return 0;
}

uint8_t IntermediateScreen_Music_PlayPause(void)
{
    /* LOCAL VARIABLE */

    /* SEND DATA TO BLE_UART */
    BLE_music_setting_screen(Play_Pause);

    /* RETURN STATUS */
    return 0;
}
void SettingMainEntry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_main_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "SETTINGS");
    GUI_Clock_Entry();
}

void Settingmain_exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_main_container, LV_OBJ_FLAG_HIDDEN);
}

void SettingMain_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_main_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "SETTINGS");
    GUI_Clock_Entry();
}

void SettingMain_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_main_day_container, LV_OBJ_FLAG_HIDDEN);
}

void BikeMenu_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_bike_day_container, LV_OBJ_FLAG_HIDDEN);
}

void BikeMenuExit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_bike_night_container, LV_OBJ_FLAG_HIDDEN);
}

void AboutMenu_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_about_day_container, LV_OBJ_FLAG_HIDDEN);
}

void DisplayMenu_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_display_day_container, LV_OBJ_FLAG_HIDDEN);
}

void AboutMenuEntry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "ABOUT");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_about_night_container, LV_OBJ_FLAG_HIDDEN);
}

void About_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_about_night_container, LV_OBJ_FLAG_HIDDEN);
}

void Connectivity_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_connect_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "CONNECTIVITY");
}

void Conn_Bluetooth_Show(void)
{

    if (g_BLE_Status_u8 == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_connect_switch_btn_night_img, &new_night_toggle_check_btn);
    }
    else if (g_BLE_Status_u8 == 2)
    {
        lv_img_set_src(guider_ui.Setting_Screen_connect_switch_btn_night_img, &img_night_toggle_off_btn);
    }
    else
    {
        /* do nothing */
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_up_arr_night_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_up_arr_night_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_down_arr_night_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_down_arr_night_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Connect_MUSIC_Night_During(void)
{
    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_up_arr_night_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_up_arr_night_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_down_arr_night_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_down_arr_night_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Connnect_Music_Day_During(void)
{
    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_dow_arr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_dow_arr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Conn_Bluetooth_Day_Show(void)
{

    if (g_BLE_Status_u8 == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_connect_switch_btn_day_img, &new_day_toogle_on_Btn);
    }
    else if (g_BLE_Status_u8 == 2)
    {
        lv_img_set_src(guider_ui.Setting_Screen_connect_switch_btn_day_img, &new_day_toogle_off_Btn);
    }
    else
    {
        /* do nothing */
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_dow_arr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_connect_dow_arr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Connectivity_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_connect_night_container, LV_OBJ_FLAG_HIDDEN);
}

void Display_Menu_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_display_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DISPLAY");
}

void Display_Menu_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_display_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DISPLAY");
}

void Display_Menu_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_display_night_container, LV_OBJ_FLAG_HIDDEN);
}

void Music_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_music_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MUSIC");
}
void Music_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_music_day_container, LV_OBJ_FLAG_HIDDEN);
    // lv_label_set_text(guider_ui.Setting_Screen_display_label, "MUSIC");
}

void Brightness_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_brightness_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BRIGHTNESS");
}
void Brightness_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_brightness_night_contain, LV_OBJ_FLAG_HIDDEN);
}

void Brightness_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_brightness_day_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BRIGHTNESS");
}

void Brightness_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_brightness_day_contain, LV_OBJ_FLAG_HIDDEN);
}

void Menu_Night_Entry(void)
{
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_down_arr_day_img, 110, 245);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_down_arr_day_img, 20, 11);
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_up_arr_day_img, 110, 68);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_up_arr_day_img, 20, 11);
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");
    lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
    lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);
}

void Menu_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_menu_night_contain, LV_OBJ_FLAG_HIDDEN);
}

void Menu_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_menu_day_contain, LV_OBJ_FLAG_HIDDEN);
}

void Date_Time_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_seting_date_time_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE AND TIME");
}

void Date_Time_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_seting_date_time_container, LV_OBJ_FLAG_HIDDEN);
}
void Date_Time_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_seting_date_time_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE AND TIME");
}
void Date_Time_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_seting_date_time_day_container, LV_OBJ_FLAG_HIDDEN);
}

void Unit_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_unit_night_container, LV_OBJ_FLAG_HIDDEN);
}
void Unit_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_unit_day_container, LV_OBJ_FLAG_HIDDEN);
}

void Unit_Sub_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_units_sub_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_units_sub_up_arr_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_units_sub_down_arr_img, LV_OBJ_FLAG_HIDDEN);
}

void Unit_Sub_fuel_km_During(void)
{

    if (g_User_Sel_TC_Unit == 2)
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_btn_img, &_radiobtn_night_Checked_20x20);
        g_RADIOBUTTON_Status = FALSE;
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_btn_img, &img_night_radio_active_btn_2_base);
        g_RADIOBUTTON_Status = TRUE;
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Unit_Sub_fuel_L100_During(void)
{

    if (g_User_Sel_TC_Unit == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_btn_img, &_radiobtn_night_Checked_20x20);
        g_RADIOBUTTON_Status = FALSE;
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_btn_img, &img_night_radio_active_btn_2_base);
        g_RADIOBUTTON_Status = TRUE;
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Unit_Sub_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_units_day_sub_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_units_up_arr_day_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_units_up_arr_night_img, LV_OBJ_FLAG_HIDDEN);
}

void About_Info_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_about_inf_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "ABOUT");
}

void About_Info_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_about_inf_container, LV_OBJ_FLAG_HIDDEN);
}

void About_Info_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_about_inf_nigh_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "ABOUT");
}

void About_Info_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_about_inf_nigh_container, LV_OBJ_FLAG_HIDDEN);
}

void Date_Set_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_about_inf_nigh_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE SETTING");
}
void Date_Set_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_about_inf_nigh_container, LV_OBJ_FLAG_HIDDEN);
}

void Date_Set_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_date_set_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE SETTING");
}

void Date_Set_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_date_set_night_container, LV_OBJ_FLAG_HIDDEN);
}

void Time_Set_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_time_set_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE SETTING");
}

void Time_Set_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_container, LV_OBJ_FLAG_HIDDEN);
}

void Time_Set_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_time_set_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_seting_date_time_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME SETTING");
}
void Time_Set_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_night_container, LV_OBJ_FLAG_HIDDEN);
}

void Time_12_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_time_12_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME SETTING");
    lv_obj_add_flag(guider_ui.Setting_Screen_seting_date_time_day_container, LV_OBJ_FLAG_HIDDEN);
}
void Time_12_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_12_container, LV_OBJ_FLAG_HIDDEN);
}
void Time_12_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_time_12_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME SETTING");
    lv_obj_add_flag(guider_ui.Setting_Screen_seting_date_time_day_container, LV_OBJ_FLAG_HIDDEN);
}
void Time_12_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_12_day_container, LV_OBJ_FLAG_HIDDEN);
}

void Batter_Val_Night_Entry(void)
{
    g_previous_Vehicle_Battery_Night_st_u32 = 0xFF;
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_battery_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BATTERY");
}

void Battery_Val_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_battery_container, LV_OBJ_FLAG_HIDDEN);
}

void Battey_Val_Day_Entry(void)
{
    g_previous_Vehicle_Battery_Day_st_u32 = 0xFF;
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_battery_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BATTERY");
}
void Battery_Val_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_battery_day_container, LV_OBJ_FLAG_HIDDEN);
}

void TripB_Night_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TRIP B");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_trip_container, LV_OBJ_FLAG_HIDDEN);
    g_Fuel_Current_Unit = Fuel_Consumption_fn();
    /* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
    g_previous_Bike_TripB_Value_night_u32 = 0xFF;
    g_previous_Bike_Trip_time_hour_night_u8 = 0xFF;
    g_previous_Bike_Trip_time_Minute_night_u8 = 0xFF;
    g_previous_Bike_TripB_AVSValue_night_u32 = 0xFF;
    g_previous_Bike_TripB_AVFValue_night_u32 = 0xFF;
}

void Trip_Night_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TRIP A");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_trip_container, LV_OBJ_FLAG_HIDDEN);
    /* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
    g_previous_Bike_TripA_Value_night_u32 = 0xFF;
    g_previous_Bike_Trip_time_hour_night_u8 = 0xFF;
    g_previous_Bike_Trip_time_Minute_night_u8 = 0xFF;
    g_previous_Bike_TripA_AVSValue_night_u32 = 0xFF;
    g_previous_Bike_TripA_AVFValue_night_u32 = 0xFF;

    g_Fuel_Current_Unit = Fuel_Consumption_fn();
}

void Trip_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_trip_container, LV_OBJ_FLAG_HIDDEN);
}
void Trip_Day_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TRIP A");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_trip_day_container, LV_OBJ_FLAG_HIDDEN);
    g_Fuel_Current_Unit = Fuel_Consumption_fn();
    /* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
    g_previous_Bike_TripA_Value_Day_u32 = 0xFF;
    g_previous_Bike_Trip_time_hour_Day_u8 = 0xFF;
    g_previous_Bike_Trip_time_Minute_Day_u8 = 0xFF;
    g_previous_Bike_TripA_AVFValue_Day_u32 = 0xFF;
    g_previous_Bike_TripA_AVSValue_Day_u32 = 0xFF;
}

void TripB_Day_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TRIP B");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_trip_day_container, LV_OBJ_FLAG_HIDDEN);
    g_Fuel_Current_Unit = Fuel_Consumption_fn();
    /* Set the Previous value to Maximum Range For Chang Value in Label_LVGL */
    g_previous_Bike_TripB_Value_Day_u32 = 0xFF;
    g_previous_Bike_Trip_time_hour_Day_u8 = 0xFF;
    g_previous_Bike_Trip_time_Minute_Day_u8 = 0xFF;
    g_previous_Bike_TripB_AVSValue_Day_u32 = 0xFF;
    g_previous_Bike_TripB_AVFValue_Day_u32 = 0xFF;
}

void Trip_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_trip_day_container, LV_OBJ_FLAG_HIDDEN);
}

void Display_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_display_night_container, LV_OBJ_FLAG_HIDDEN);
}

void Battery_Val_Night_During(void)
{
    lv_img_set_src(guider_ui.Setting_Screen_battery_img, &img_night_battery_icon);

    uint32_t fl_present_Vehicle_Battery_Night_st_u32;
    fl_present_Vehicle_Battery_Night_st_u32 = Voltage_Battery_Get_Value();
    if ((fl_present_Vehicle_Battery_Night_st_u32 != g_previous_Vehicle_Battery_Night_st_u32))
    {
        g_previous_Vehicle_Battery_Night_st_u32 = fl_present_Vehicle_Battery_Night_st_u32;
        lv_label_set_text_fmt(guider_ui.Setting_Screen_battery_lbl1, "%d.%d V", (g_previous_Vehicle_Battery_Night_st_u32 / 10), (g_previous_Vehicle_Battery_Night_st_u32 % 10));
    }
    else
    {
        /* do nothing */
    }
}

void Battery_val_Day_During(void)
{
    lv_img_set_src(guider_ui.Setting_Screen_battery_day_img, &img_day_battery_icon);

    uint32_t fl_present_Vehicle_Battery_Day_st_u32;
    fl_present_Vehicle_Battery_Day_st_u32 = Voltage_Battery_Get_Value();
    if ((fl_present_Vehicle_Battery_Day_st_u32 != g_previous_Vehicle_Battery_Day_st_u32))
    {
        g_previous_Vehicle_Battery_Day_st_u32 = fl_present_Vehicle_Battery_Day_st_u32;
        lv_label_set_text_fmt(guider_ui.Setting_Screen_battery_day_lbl1, "%d.%d V", (g_previous_Vehicle_Battery_Day_st_u32 / 10), (g_previous_Vehicle_Battery_Day_st_u32 % 10));
    }
    else
    {
        /* do nothing */
    }
}

void TripA_Trip_Night_During(void)
{
    uint32_t fl_present_Bike_TripA_Value_night_u32 = ODO_Get_TripOdometer(0);
    uint8_t fl_present_Bike_Trip_time_hour_night_u8 = Swc_Trip_Timer_Get_Hour_value(0);
    uint8_t fl_present_Bike_Trip_time_Minute_night_u8 = Swc_Trip_Timer_Get_Min_value(0);
    bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();

    lv_label_set_text(guider_ui.Setting_Screen_trip_lbl1, "Hold        To RESET");

    if (fl_present_Bike_TripA_Value_night_u32 == ODO_INVALID_STATE)
    {
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Trip ---.- km");
    }
    else if ((g_previous_Bike_TripA_Value_night_u32 != fl_present_Bike_TripA_Value_night_u32))
    {
        g_previous_Bike_TripA_Value_night_u32 = fl_present_Bike_TripA_Value_night_u32;
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Trip %d.%d km", (g_previous_Bike_TripA_Value_night_u32 / 10), (g_previous_Bike_TripA_Value_night_u32 % 10));
    }

    if (fl_Trip_Timer_St != FALSE)
    {
        if ((g_previous_Bike_Trip_time_hour_night_u8 != fl_present_Bike_Trip_time_hour_night_u8) ||
            (fl_present_Bike_Trip_time_Minute_night_u8 != g_previous_Bike_Trip_time_Minute_night_u8))
        {
            g_previous_Bike_Trip_time_hour_night_u8 = fl_present_Bike_Trip_time_hour_night_u8;
            g_previous_Bike_Trip_time_Minute_night_u8 = fl_present_Bike_Trip_time_Minute_night_u8;
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Time %d h %d m", g_previous_Bike_Trip_time_hour_night_u8, g_previous_Bike_Trip_time_Minute_night_u8);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        lv_label_set_text(guider_ui.Setting_Screen_trip_lbl3, "Time  --h--m");
        g_previous_Bike_Trip_time_hour_night_u8 = 0XFF;
    }

    lv_obj_clear_flag(guider_ui.Setting_Screen_trip_hold_btn, LV_OBJ_FLAG_HIDDEN);
    set_obj_opa(guider_ui.Setting_Screen_trip_hold_btn, 50);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_hold_btn, Holdbtnpos[0], Holdbtnpos[1]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripA_Time_Night_During(void)
{
    uint32_t fl_present_Bike_TripA_Value_night_u32 = ODO_Get_TripOdometer(0);
    uint8_t fl_present_Bike_Trip_time_hour_night_u8 = Swc_Trip_Timer_Get_Hour_value(0);
    uint8_t fl_present_Bike_Trip_time_Minute_night_u8 = Swc_Trip_Timer_Get_Min_value(0);
    uint32_t fl_present_Bike_TripA_AVSValue_night_u32 = Swc_Avereage_Speed_Get_value(0);
    bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
    bool fl_Trip_AVS_Status_bl = Swc_Average_Speed_Get_Status();

    if (fl_present_Bike_TripA_Value_night_u32 == ODO_INVALID_STATE)
    {
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Trip ---.- km");
    }
    else if ((g_previous_Bike_TripA_Value_night_u32 != fl_present_Bike_TripA_Value_night_u32))
    {
        g_previous_Bike_TripA_Value_night_u32 = fl_present_Bike_TripA_Value_night_u32;
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Trip %d.%d km", (g_previous_Bike_TripA_Value_night_u32 / 10), (g_previous_Bike_TripA_Value_night_u32 % 10));
    }
    else
    {
        /* do nothing */
    }

    if (fl_Trip_Timer_St != FALSE)
    {
        if ((g_previous_Bike_Trip_time_hour_night_u8 != fl_present_Bike_Trip_time_hour_night_u8) ||
            (fl_present_Bike_Trip_time_Minute_night_u8 != g_previous_Bike_Trip_time_Minute_night_u8))
        {
            g_previous_Bike_Trip_time_hour_night_u8 = fl_present_Bike_Trip_time_hour_night_u8;
            g_previous_Bike_Trip_time_Minute_night_u8 = fl_present_Bike_Trip_time_Minute_night_u8;

            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Time %d h %d m", g_previous_Bike_Trip_time_hour_night_u8, g_previous_Bike_Trip_time_Minute_night_u8);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        lv_label_set_text(guider_ui.Setting_Screen_trip_lbl2, "Time  --h--m");
        g_previous_Bike_Trip_time_hour_night_u8 = 0XFF;
    }
    if ((fl_present_Bike_TripA_AVSValue_night_u32 != g_previous_Bike_TripA_AVSValue_night_u32))
    {
        g_previous_Bike_TripA_AVSValue_night_u32 = fl_present_Bike_TripA_AVSValue_night_u32;

        if ((g_previous_Bike_TripA_AVSValue_night_u32 > AVEREAGE_SPEED) || (fl_Trip_AVS_Status_bl == FALSE))
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Av Speed --- km/h");
        }
        else
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Av Speed %d km/h", (g_previous_Bike_TripA_AVSValue_night_u32));
        }
    }
    else
    {
        /* do nothing */
    }
    lv_obj_add_flag(guider_ui.Setting_Screen_trip_hold_btn, LV_OBJ_FLAG_HIDDEN);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripA_AvSpeed_Night_During(void)
{
    uint32_t fl_present_Bike_TripA_AVSValue_night_u32 = Swc_Avereage_Speed_Get_value(0);
    uint32_t fl_present_Bike_TripA_AVFValue_night_u32 = display_AFE(0);
    uint8_t fl_present_Bike_Trip_time_hour_night_u8 = Swc_Trip_Timer_Get_Hour_value(0);
    uint8_t fl_present_Bike_Trip_time_Minute_night_u8 = Swc_Trip_Timer_Get_Min_value(0);
    bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
    uint32_t AFE_Unit_u32 = 0;
    bool fl_Trip_AVS_Status_bl = Swc_Average_Speed_Get_Status();

    if ((fl_present_Bike_TripA_AVSValue_night_u32 != g_previous_Bike_TripA_AVSValue_night_u32))
    {
        g_previous_Bike_TripA_AVSValue_night_u32 = fl_present_Bike_TripA_AVSValue_night_u32;

        if ((g_previous_Bike_TripA_AVSValue_night_u32 > AVEREAGE_SPEED) || (fl_Trip_AVS_Status_bl == FALSE))
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Av Speed --- km/h");
        }
        else
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Av Speed %d km/h", (g_previous_Bike_TripA_AVSValue_night_u32));
        }
    }
    else
    {
        /* do nothing */
    }

    if (fl_Trip_Timer_St != FALSE)
    {
        if ((g_previous_Bike_Trip_time_hour_night_u8 != fl_present_Bike_Trip_time_hour_night_u8) ||
            (fl_present_Bike_Trip_time_Minute_night_u8 != g_previous_Bike_Trip_time_Minute_night_u8))
        {
            g_previous_Bike_Trip_time_hour_night_u8 = fl_present_Bike_Trip_time_hour_night_u8;
            g_previous_Bike_Trip_time_Minute_night_u8 = fl_present_Bike_Trip_time_Minute_night_u8;
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Time %d h %d m", g_previous_Bike_Trip_time_hour_night_u8, g_previous_Bike_Trip_time_Minute_night_u8);
        }
        else
        {
            /* do nothing */
        }
    }

    else
    {
        lv_label_set_text(guider_ui.Setting_Screen_trip_lbl1, "Time  --h--m");
        g_previous_Bike_Trip_time_hour_night_u8 = 0XFF;
    }

    if (g_Fuel_Current_Unit == Lper100km)
    {
        if ((fl_present_Bike_TripA_AVFValue_night_u32 != 0) && (fl_present_Bike_TripA_AVFValue_night_u32 != TC_INVALID))
        {

            fl_present_Bike_TripA_AVFValue_night_u32 = 10000 / fl_present_Bike_TripA_AVFValue_night_u32;
        }

        /* Limit AVF value if it exceeds max limit */
        SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&fl_present_Bike_TripA_AVFValue_night_u32);
    }
    else
    {
        /* do nothing*/
    }

    if ((g_previous_Bike_TripA_AVFValue_night_u32 != fl_present_Bike_TripA_AVFValue_night_u32))
    {
        g_previous_Bike_TripA_AVFValue_night_u32 = fl_present_Bike_TripA_AVFValue_night_u32;

        if (TC_INVALID != g_previous_Bike_TripA_AVFValue_night_u32)
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Av Fuel %d.%d km/L", (g_previous_Bike_TripA_AVFValue_night_u32 / 10), (g_previous_Bike_TripA_AVFValue_night_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Av Fuel %d.%d L/100km", (g_previous_Bike_TripA_AVFValue_night_u32 / 10), (g_previous_Bike_TripA_AVFValue_night_u32 % 10));
            }
        }
        else
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Av Fuel ---.- km/L", (g_previous_Bike_TripA_AVFValue_night_u32 / 10), (g_previous_Bike_TripA_AVFValue_night_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Av Fuel ---.- L/100km", (g_previous_Bike_TripA_AVFValue_night_u32 / 10), (g_previous_Bike_TripA_AVFValue_night_u32 % 10));
            }
        }
    }
    else
    {
        /* do nothing */
    }
    lv_obj_add_flag(guider_ui.Setting_Screen_trip_hold_btn, LV_OBJ_FLAG_HIDDEN);
    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripA_AVFuel_Night_During(void)
{
    uint32_t fl_present_Bike_TripA_AVSValue_night_u32 = Swc_Avereage_Speed_Get_value(0);
    uint32_t fl_present_Bike_TripA_AVFValue_night_u32 = display_AFE(0);
    uint32_t fl_present_Bike_TripA_AVFValue_Unit_Set_night_u32 = Fuel_Consumption_fn();
    bool fl_Trip_AVS_Status_bl = Swc_Average_Speed_Get_Status();
    uint32_t AFE_Unit_u32 = 0;

    if ((fl_present_Bike_TripA_AVSValue_night_u32 != g_previous_Bike_TripA_AVSValue_night_u32))
    {
        g_previous_Bike_TripA_AVSValue_night_u32 = fl_present_Bike_TripA_AVSValue_night_u32;

        if ((g_previous_Bike_TripA_AVSValue_night_u32 > AVEREAGE_SPEED) || (fl_Trip_AVS_Status_bl == FALSE))
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Av Speed --- km/h");
        }
        else
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Av Speed %d km/h", (g_previous_Bike_TripA_AVSValue_night_u32));
        }
    }
    else
    {
        /* do nothing */
    }
    if (g_Fuel_Current_Unit == Lper100km)
    {
        if ((fl_present_Bike_TripA_AVFValue_night_u32 != 0) && (fl_present_Bike_TripA_AVFValue_night_u32 != TC_INVALID))
        {

            fl_present_Bike_TripA_AVFValue_night_u32 = 10000 / fl_present_Bike_TripA_AVFValue_night_u32;
        }

        /* Limit AVF value if it exceeds max limit */
        SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&fl_present_Bike_TripA_AVFValue_night_u32);
    }
    else
    {
        /* do nothing*/
    }

    if ((g_previous_Bike_TripA_AVFValue_night_u32 != fl_present_Bike_TripA_AVFValue_night_u32))
    {
        g_previous_Bike_TripA_AVFValue_night_u32 = fl_present_Bike_TripA_AVFValue_night_u32;

        if (TC_INVALID != g_previous_Bike_TripA_AVFValue_night_u32)
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Av Fuel %d.%d km/L", (g_previous_Bike_TripA_AVFValue_night_u32 / 10), (g_previous_Bike_TripA_AVFValue_night_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Av Fuel %d.%d L/100km", (g_previous_Bike_TripA_AVFValue_night_u32 / 10), (g_previous_Bike_TripA_AVFValue_night_u32 % 10));
            }
        }
        else
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Av Fuel ---.- km/L", (g_previous_Bike_TripA_AVFValue_night_u32 / 10), (g_previous_Bike_TripA_AVFValue_night_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Av Fuel ---.- L/100km", (g_previous_Bike_TripA_AVFValue_night_u32 / 10), (g_previous_Bike_TripA_AVFValue_night_u32 % 10));
            }
        }
    }
    else
    {
        /* do nothing */
    }

    lv_label_set_text(guider_ui.Setting_Screen_trip_lbl3, "Hold        To RESET");
    lv_obj_clear_flag(guider_ui.Setting_Screen_trip_hold_btn, LV_OBJ_FLAG_HIDDEN);
    set_obj_opa(guider_ui.Setting_Screen_trip_hold_btn, 50);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_hold_btn, Holdbtnpos[2], Holdbtnpos[3]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripA_Hold_Night_During(void)
{
    uint32_t fl_present_Bike_TripA_Value_night_u32 = ODO_Get_TripOdometer(0);
    uint32_t fl_present_Bike_TripA_AVSValue_night_u32 = Swc_Avereage_Speed_Get_value(0);
    uint32_t fl_present_Bike_TripA_AVFValue_night_u32 = display_AFE(0);

    uint32_t AFE_Unit_u32 = 0;

    if (fl_present_Bike_TripA_Value_night_u32 == ODO_INVALID_STATE)
    {
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Trip ---.- km");
    }
    else if ((g_previous_Bike_TripA_Value_night_u32 != fl_present_Bike_TripA_Value_night_u32))
    {
        g_previous_Bike_TripA_Value_night_u32 = fl_present_Bike_TripA_Value_night_u32;
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Trip %d.%d km", (g_previous_Bike_TripA_Value_night_u32 / 10), (g_previous_Bike_TripA_Value_night_u32 % 10));
    }
    else
    {
        /* do nothing */
    }

    if (g_Fuel_Current_Unit == Lper100km)
    {
        if ((fl_present_Bike_TripA_AVFValue_night_u32 != 0) && (fl_present_Bike_TripA_AVFValue_night_u32 != TC_INVALID))
        {

            fl_present_Bike_TripA_AVFValue_night_u32 = 10000 / fl_present_Bike_TripA_AVFValue_night_u32;
        }

        /* Limit AVF value if it exceeds max limit */
        SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&fl_present_Bike_TripA_AVFValue_night_u32);
    }
    else
    {
        /* do nothing*/
    }

    if ((g_previous_Bike_TripA_AVFValue_night_u32 != fl_present_Bike_TripA_AVFValue_night_u32))
    {
        g_previous_Bike_TripA_AVFValue_night_u32 = fl_present_Bike_TripA_AVFValue_night_u32;

        if (TC_INVALID != g_previous_Bike_TripA_AVFValue_night_u32)
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Av Fuel %d.%d km/L", (g_previous_Bike_TripA_AVFValue_night_u32 / 10), (g_previous_Bike_TripA_AVFValue_night_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Av Fuel %d.%d L/100km", (g_previous_Bike_TripA_AVFValue_night_u32 / 10), (g_previous_Bike_TripA_AVFValue_night_u32 % 10));
            }
        }
        else
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Av Fuel ---.- km/L", (g_previous_Bike_TripA_AVFValue_night_u32 / 10), (g_previous_Bike_TripA_AVFValue_night_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Av Fuel ---.- L/100km", (g_previous_Bike_TripA_AVFValue_night_u32 / 10), (g_previous_Bike_TripA_AVFValue_night_u32 % 10));
            }
        }
    }
    else
    {
        /* do nothing */
    }

    lv_label_set_text(guider_ui.Setting_Screen_trip_lbl2, "Hold        To RESET");
    set_obj_opa(guider_ui.Setting_Screen_trip_hold_btn, 255);
    lv_obj_clear_flag(guider_ui.Setting_Screen_trip_hold_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_hold_btn, Holdbtnpos[4], Holdbtnpos[5]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripB_Trip_Night_During(void)
{
    uint32_t fl_present_Bike_TripB_Value_night_u32 = ODO_Get_TripOdometer(1);
    uint8_t fl_present_Bike_Trip_time_hour_night_u8 = Swc_Trip_Timer_Get_Hour_value(1);
    uint8_t fl_present_Bike_Trip_time_Minute_night_u8 = Swc_Trip_Timer_Get_Min_value(1);
    bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();

    lv_label_set_text(guider_ui.Setting_Screen_trip_lbl1, "Hold        To RESET");

    if (fl_present_Bike_TripB_Value_night_u32 == ODO_INVALID_STATE)
    {
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Trip ---.- km");
    }
    else if ((g_previous_Bike_TripB_Value_night_u32 != fl_present_Bike_TripB_Value_night_u32))
    {
        g_previous_Bike_TripB_Value_night_u32 = fl_present_Bike_TripB_Value_night_u32;
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Trip %d.%d km", (g_previous_Bike_TripB_Value_night_u32 / 10), (g_previous_Bike_TripB_Value_night_u32 % 10));
    }
    else
    {
        /* do nothing*/
    }

    if (fl_Trip_Timer_St != FALSE)
    {
        if ((g_previous_Bike_Trip_time_hour_night_u8 != fl_present_Bike_Trip_time_hour_night_u8) ||
            (fl_present_Bike_Trip_time_Minute_night_u8 != g_previous_Bike_Trip_time_Minute_night_u8))
        {
            g_previous_Bike_Trip_time_hour_night_u8 = fl_present_Bike_Trip_time_hour_night_u8;
            g_previous_Bike_Trip_time_Minute_night_u8 = fl_present_Bike_Trip_time_Minute_night_u8;
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Time %d h %d m", g_previous_Bike_Trip_time_hour_night_u8, g_previous_Bike_Trip_time_Minute_night_u8);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        lv_label_set_text(guider_ui.Setting_Screen_trip_lbl3, "Time  --h--m");
        g_previous_Bike_Trip_time_hour_night_u8 = 0XFF;
    }

    lv_obj_clear_flag(guider_ui.Setting_Screen_trip_hold_btn, LV_OBJ_FLAG_HIDDEN);
    set_obj_opa(guider_ui.Setting_Screen_trip_hold_btn, 50);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_hold_btn, Holdbtnpos[0], Holdbtnpos[1]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripB_Time_Night_During(void)
{
    uint32_t fl_present_Bike_TripB_Value_night_u32 = ODO_Get_TripOdometer(1);
    uint8_t fl_present_Bike_Trip_time_hour_night_u8 = Swc_Trip_Timer_Get_Hour_value(1);
    uint8_t fl_present_Bike_Trip_time_Minute_night_u8 = Swc_Trip_Timer_Get_Min_value(1);
    uint32_t fl_present_Bike_TripB_AVSValue_night_u32 = Swc_Avereage_Speed_Get_value(1);
    bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
    bool fl_Trip_AVS_Status_bl = Swc_Average_Speed_Get_Status();

    if (fl_present_Bike_TripB_Value_night_u32 == ODO_INVALID_STATE)
    {
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Trip ---.- km");
    }
    else if ((g_previous_Bike_TripB_Value_night_u32 != fl_present_Bike_TripB_Value_night_u32))
    {
        g_previous_Bike_TripB_Value_night_u32 = fl_present_Bike_TripB_Value_night_u32;
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Trip %d.%d km", (g_previous_Bike_TripB_Value_night_u32 / 10), (g_previous_Bike_TripB_Value_night_u32 % 10));
    }
    else
    {
        /* do nothing */
    }

    if (fl_Trip_Timer_St != FALSE)
    {
        if ((g_previous_Bike_Trip_time_hour_night_u8 != fl_present_Bike_Trip_time_hour_night_u8) ||
            (fl_present_Bike_Trip_time_Minute_night_u8 != g_previous_Bike_Trip_time_Minute_night_u8))
        {
            g_previous_Bike_Trip_time_hour_night_u8 = fl_present_Bike_Trip_time_hour_night_u8;
            g_previous_Bike_Trip_time_Minute_night_u8 = fl_present_Bike_Trip_time_Minute_night_u8;
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Time %d h %d m", g_previous_Bike_Trip_time_hour_night_u8, g_previous_Bike_Trip_time_Minute_night_u8);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        lv_label_set_text(guider_ui.Setting_Screen_trip_lbl2, "Time  --h--m");
        g_previous_Bike_Trip_time_hour_night_u8 = 0XFF;
    }

    if ((fl_present_Bike_TripB_AVSValue_night_u32 != g_previous_Bike_TripB_AVSValue_night_u32))
    {
        g_previous_Bike_TripB_AVSValue_night_u32 = fl_present_Bike_TripB_AVSValue_night_u32;

        if ((g_previous_Bike_TripB_AVSValue_night_u32 > AVEREAGE_SPEED) || (fl_Trip_AVS_Status_bl == FALSE))
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Av Speed --- km/h");
        }
        else
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Av Speed %d km/h", (g_previous_Bike_TripB_AVSValue_night_u32));
        }
    }
    else
    {
        /* do nothing */
    }

    lv_obj_add_flag(guider_ui.Setting_Screen_trip_hold_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_hold_btn, Holdbtnpos[0], Holdbtnpos[1]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripB_AvSpeed_Night_During(void)
{
    uint32_t fl_present_Bike_TripB_AVSValue_night_u32 = Swc_Avereage_Speed_Get_value(1);
    uint32_t fl_present_Bike_TripB_AVFValue_night_u32 = display_AFE(1);
    uint8_t fl_present_Bike_Trip_time_hour_night_u8 = Swc_Trip_Timer_Get_Hour_value(1);
    uint8_t fl_present_Bike_Trip_time_Minute_night_u8 = Swc_Trip_Timer_Get_Min_value(1);
    bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
    uint32_t AFE_Unit_u32 = 0;
    bool fl_Trip_AVS_Status_bl = Swc_Average_Speed_Get_Status();

    if ((fl_present_Bike_TripB_AVSValue_night_u32 != g_previous_Bike_TripB_AVSValue_night_u32))
    {
        g_previous_Bike_TripB_AVSValue_night_u32 = fl_present_Bike_TripB_AVSValue_night_u32;

        if ((g_previous_Bike_TripB_AVSValue_night_u32 > AVEREAGE_SPEED) || (fl_Trip_AVS_Status_bl == FALSE))
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Av Speed --- km/h");
        }
        else
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Av Speed %d km/h", (g_previous_Bike_TripB_AVSValue_night_u32));
        }
    }
    else
    {
        /* do nothing */
    }

    if (fl_Trip_Timer_St != FALSE)
    {
        if ((g_previous_Bike_Trip_time_hour_night_u8 != fl_present_Bike_Trip_time_hour_night_u8) ||
            (fl_present_Bike_Trip_time_Minute_night_u8 != g_previous_Bike_Trip_time_Minute_night_u8))
        {
            g_previous_Bike_Trip_time_hour_night_u8 = fl_present_Bike_Trip_time_hour_night_u8;
            g_previous_Bike_Trip_time_Minute_night_u8 = fl_present_Bike_Trip_time_Minute_night_u8;
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Time %d h %d m", g_previous_Bike_Trip_time_hour_night_u8, g_previous_Bike_Trip_time_Minute_night_u8);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        lv_label_set_text(guider_ui.Setting_Screen_trip_lbl1, "Time  --h--m");
        g_previous_Bike_Trip_time_hour_night_u8 = 0XFF;
    }

    if (g_Fuel_Current_Unit == Lper100km)
    {
        if ((fl_present_Bike_TripB_AVFValue_night_u32 != 0) && (fl_present_Bike_TripB_AVFValue_night_u32 != TC_INVALID))
        {

            fl_present_Bike_TripB_AVFValue_night_u32 = 10000 / fl_present_Bike_TripB_AVFValue_night_u32;
        }

        /* Limit AVF value if it exceeds max limit */
        SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&fl_present_Bike_TripB_AVFValue_night_u32);
    }
    else
    {
    }

    if ((g_previous_Bike_TripB_AVFValue_night_u32 != fl_present_Bike_TripB_AVFValue_night_u32))
    {
        g_previous_Bike_TripB_AVFValue_night_u32 = fl_present_Bike_TripB_AVFValue_night_u32;

        if (TC_INVALID != g_previous_Bike_TripB_AVFValue_night_u32)
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Av Fuel %d.%d km/L", (g_previous_Bike_TripB_AVFValue_night_u32 / 10), (g_previous_Bike_TripB_AVFValue_night_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Av Fuel %d.%d L/100km", (g_previous_Bike_TripB_AVFValue_night_u32 / 10), (g_previous_Bike_TripB_AVFValue_night_u32 % 10));
            }
        }
        else
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Av Fuel ---.- km/L", (g_previous_Bike_TripB_AVFValue_night_u32 / 10), (g_previous_Bike_TripB_AVFValue_night_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Av Fuel ---.- L/100km", (g_previous_Bike_TripB_AVFValue_night_u32 / 10), (g_previous_Bike_TripB_AVFValue_night_u32 % 10));
            }
        }
    }
    else
    {
        /* do nothing */
    }
    lv_obj_add_flag(guider_ui.Setting_Screen_trip_hold_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_hold_btn, Holdbtnpos[0], Holdbtnpos[1]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripB_AVFuel_Night_During(void)
{
    uint32_t fl_present_Bike_TripB_AVSValue_night_u32 = Swc_Avereage_Speed_Get_value(1);
    uint32_t fl_present_Bike_TripB_AVFValue_night_u32 = display_AFE(1);
    uint32_t fl_present_Bike_TripB_AVFValue_Unit_Set_night_u32 = Fuel_Consumption_fn();
    bool fl_Trip_AVS_Status_bl = Swc_Average_Speed_Get_Status();
    uint32_t AFE_Unit_u32 = 0;

    if ((fl_present_Bike_TripB_AVSValue_night_u32 != g_previous_Bike_TripB_AVSValue_night_u32))
    {
        g_previous_Bike_TripB_AVSValue_night_u32 = fl_present_Bike_TripB_AVSValue_night_u32;

        if ((g_previous_Bike_TripB_AVSValue_night_u32 > AVEREAGE_SPEED) || (fl_Trip_AVS_Status_bl == FALSE))
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Av Speed --- km/h");
        }
        else
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Av Speed %d km/h", (g_previous_Bike_TripB_AVSValue_night_u32));
        }
    }
    else
    {
        /* do nothing */
    }

    if (g_Fuel_Current_Unit == Lper100km)
    {
        if ((fl_present_Bike_TripB_AVFValue_night_u32 != 0) && (fl_present_Bike_TripB_AVFValue_night_u32 != TC_INVALID))
        {

            fl_present_Bike_TripB_AVFValue_night_u32 = 10000 / fl_present_Bike_TripB_AVFValue_night_u32;
        }

        /* Limit AVF value if it exceeds max limit */
        SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&fl_present_Bike_TripB_AVFValue_night_u32);
    }
    else
    {
    }

    if ((g_previous_Bike_TripB_AVFValue_night_u32 != fl_present_Bike_TripB_AVFValue_night_u32))
    {
        g_previous_Bike_TripB_AVFValue_night_u32 = fl_present_Bike_TripB_AVFValue_night_u32;

        if (TC_INVALID != g_previous_Bike_TripB_AVFValue_night_u32)
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Av Fuel %d.%d km/L", (g_previous_Bike_TripB_AVFValue_night_u32 / 10), (g_previous_Bike_TripB_AVFValue_night_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Av Fuel %d.%d L/100km", (g_previous_Bike_TripB_AVFValue_night_u32 / 10), (g_previous_Bike_TripB_AVFValue_night_u32 % 10));
            }
        }
        else
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Av Fuel ---.- km/L", (g_previous_Bike_TripB_AVFValue_night_u32 / 10), (g_previous_Bike_TripB_AVFValue_night_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl2, "Av Fuel ---.- L/100km", (g_previous_Bike_TripB_AVFValue_night_u32 / 10), (g_previous_Bike_TripB_AVFValue_night_u32 % 10));
            }
        }
    }
    else
    {
        /* do nothing */
    }

    lv_label_set_text(guider_ui.Setting_Screen_trip_lbl3, "Hold        To RESET");
    lv_obj_clear_flag(guider_ui.Setting_Screen_trip_hold_btn, LV_OBJ_FLAG_HIDDEN);
    set_obj_opa(guider_ui.Setting_Screen_trip_hold_btn, 50);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_hold_btn, Holdbtnpos[2], Holdbtnpos[3]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripB_Hold_Night_During(void)
{
    uint32_t fl_present_Bike_TripB_Value_night_u32 = ODO_Get_TripOdometer(1);
    uint32_t fl_present_Bike_TripB_AVSValue_night_u32 = Swc_Avereage_Speed_Get_value(1);
    uint32_t fl_present_Bike_TripB_AVFValue_night_u32 = display_AFE(1);
    uint32_t AFE_Unit_u32 = 0;

    if (fl_present_Bike_TripB_Value_night_u32 == ODO_INVALID_STATE)
    {
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Trip ---.- km");
    }
    else if ((g_previous_Bike_TripB_Value_night_u32 != fl_present_Bike_TripB_Value_night_u32))
    {
        g_previous_Bike_TripB_Value_night_u32 = fl_present_Bike_TripB_Value_night_u32;
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl3, "Trip %d.%d km", (g_previous_Bike_TripB_Value_night_u32 / 10), (g_previous_Bike_TripB_Value_night_u32 % 10));
    }
    else
    {
        /* do nothing */
    }

    if (g_Fuel_Current_Unit == Lper100km)
    {
        if ((fl_present_Bike_TripB_AVFValue_night_u32 != 0) && (fl_present_Bike_TripB_AVFValue_night_u32 != TC_INVALID))
        {

            fl_present_Bike_TripB_AVFValue_night_u32 = 10000 / fl_present_Bike_TripB_AVFValue_night_u32;
        }

        /* Limit AVF value if it exceeds max limit */
        SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&fl_present_Bike_TripB_AVFValue_night_u32);
    }
    else
    {
        /* Do Nothing */
    }

    if ((g_previous_Bike_TripB_AVFValue_night_u32 != fl_present_Bike_TripB_AVFValue_night_u32))
    {
        g_previous_Bike_TripB_AVFValue_night_u32 = fl_present_Bike_TripB_AVFValue_night_u32;

        if (TC_INVALID != g_previous_Bike_TripB_AVFValue_night_u32)
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Av Fuel %d.%d km/L", (g_previous_Bike_TripB_AVFValue_night_u32 / 10), (g_previous_Bike_TripB_AVFValue_night_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Av Fuel %d.%d L/100km", (g_previous_Bike_TripB_AVFValue_night_u32 / 10), (g_previous_Bike_TripB_AVFValue_night_u32 % 10));
            }
        }
        else
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Av Fuel ---.- km/L", (g_previous_Bike_TripB_AVFValue_night_u32 / 10), (g_previous_Bike_TripB_AVFValue_night_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_lbl1, "Av Fuel ---.- L/100km", (g_previous_Bike_TripB_AVFValue_night_u32 / 10), (g_previous_Bike_TripB_AVFValue_night_u32 % 10));
            }
        }
    }
    else
    {
        /* do nothing */
    }

    lv_label_set_text(guider_ui.Setting_Screen_trip_lbl2, "Hold        To RESET");
    lv_obj_clear_flag(guider_ui.Setting_Screen_trip_hold_btn, LV_OBJ_FLAG_HIDDEN);
    set_obj_opa(guider_ui.Setting_Screen_trip_hold_btn, 255);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_hold_btn, Holdbtnpos[4], Holdbtnpos[5]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Brightness_Night_Auto_During(void)
{

    if (g_User_Brightness_Level_u8 == HIGH_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn1_img, &new_rb_night_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn1_img, &img_night_radio_active_btn_3_base);
    }
    if (g_User_Brightness_Level_u8 == AUTO_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn2_img, &new_rb_night_sel_focus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn2_img, &img_night_radio_active_btn_2_base);
    }
    if (g_User_Brightness_Level_u8 == LOW_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn3_img, &new_rb_night_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn3_img, &img_night_radio_active_btn_3_base);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_night_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_night_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_night_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_night_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Brightness_Night_Low_During(void)
{

    if (g_User_Brightness_Level_u8 == AUTO_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn1_img, &new_rb_night_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn1_img, &img_night_radio_active_btn_3_base);
    }
    if (g_User_Brightness_Level_u8 == LOW_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn2_img, &new_rb_night_sel_focus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn2_img, &img_night_radio_active_btn_2_base);
    }
    if (g_User_Brightness_Level_u8 == MEDIUM_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn3_img, &new_rb_night_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn3_img, &img_night_radio_active_btn_3_base);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_night_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_night_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_night_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_night_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}
void Brightness_Night_Med_During(void)
{
    if (g_User_Brightness_Level_u8 == LOW_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn1_img, &new_rb_night_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn1_img, &img_night_radio_active_btn_3_base);
    }
    if (g_User_Brightness_Level_u8 == MEDIUM_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn2_img, &new_rb_night_sel_focus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn2_img, &img_night_radio_active_btn_2_base);
    }
    if (g_User_Brightness_Level_u8 == HIGH_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn3_img, &new_rb_night_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn3_img, &img_night_radio_active_btn_3_base);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_night_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_night_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_night_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_night_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Brightness_Night_High_During(void)
{

    if (g_User_Brightness_Level_u8 == MEDIUM_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn1_img, &new_rb_night_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn1_img, &img_night_radio_active_btn_3_base);
    }
    if (g_User_Brightness_Level_u8 == HIGH_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn2_img, &new_rb_night_sel_focus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn2_img, &img_night_radio_active_btn_2_base);
    }
    if (g_User_Brightness_Level_u8 == AUTO_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn3_img, &new_rb_night_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_btn3_img, &img_night_radio_active_btn_3_base);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_night_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_night_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_night_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_night_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Menu_Night_Volume_During(void)
{

    if (ReadMENU_SELECTION_MUSIC() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn1_img, &img_night_toggle_on_btn_unfocused);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn1_img, &img_night_toggle_off_btn_unfocused);
    }
    if (ReadMENU_SELECTION_VOLUME() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn2_img, &new_night_toggle_check_btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn2_img, &img_night_toggle_off_btn);
    }
    if (ReadMENU_SELECTION_TRIPB() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn3_img, &img_night_toggle_on_btn_unfocused);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn3_img, &img_night_toggle_off_btn_unfocused);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Menu_Night_Tripb_During(void)
{

    if (ReadMENU_SELECTION_VOLUME() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn1_img, &img_night_toggle_on_btn_unfocused);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn1_img, &img_night_toggle_off_btn_unfocused);
    }
    if (ReadMENU_SELECTION_TRIPB() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn2_img, &new_night_toggle_check_btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn2_img, &img_night_toggle_off_btn);
    }
    if (ReadMENU_SELECTION_FUEL() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn3_img, &img_night_toggle_on_btn_unfocused);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn3_img, &img_night_toggle_off_btn_unfocused);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Menu_Night_FUEL_During(void)
{

    if (ReadMENU_SELECTION_TRIPB() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn1_img, &img_night_toggle_on_btn_unfocused);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn1_img, &img_night_toggle_off_btn_unfocused);
    }
    if (ReadMENU_SELECTION_FUEL() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn2_img, &new_night_toggle_check_btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn2_img, &img_night_toggle_off_btn);
    }
    if (ReadMENU_SELECTION_NAVIGATION() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn3_img, &img_night_toggle_on_btn_unfocused);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn3_img, &img_night_toggle_off_btn_unfocused);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Menu_Night_Navi_During(void)
{

    if (ReadMENU_SELECTION_FUEL() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn1_img, &img_night_toggle_on_btn_unfocused);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn1_img, &img_night_toggle_off_btn_unfocused);
    }
    if (ReadMENU_SELECTION_NAVIGATION() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn2_img, &new_night_toggle_check_btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn2_img, &img_night_toggle_off_btn);
    }
    if (ReadMENU_SELECTION_GI() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn3_img, &img_night_toggle_on_btn_unfocused);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn3_img, &img_night_toggle_off_btn_unfocused);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Menu_Night_GeInfo_During(void)
{

    if (ReadMENU_SELECTION_NAVIGATION() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn1_img, &img_night_toggle_on_btn_unfocused);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn1_img, &img_night_toggle_off_btn_unfocused);
    }
    if (ReadMENU_SELECTION_GI() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn2_img, &new_night_toggle_check_btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn2_img, &img_night_toggle_off_btn);
    }
    if (ReadMENU_SELECTION_PHONE() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn3_img, &img_night_toggle_on_btn_unfocused);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn3_img, &img_night_toggle_off_btn_unfocused);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Menu_Night_Phone_During(void)
{

    if (ReadMENU_SELECTION_GI() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn1_img, &img_night_toggle_on_btn_unfocused);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn1_img, &img_night_toggle_off_btn_unfocused);
    }
    if (ReadMENU_SELECTION_PHONE() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn2_img, &new_night_toggle_check_btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn2_img, &img_night_toggle_off_btn);
    }
    if (ReadMENU_SELECTION_MUSIC() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn3_img, &img_night_toggle_on_btn_unfocused);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn3_img, &img_night_toggle_off_btn_unfocused);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Menu_Night_Music_During(void)
{

    if (ReadMENU_SELECTION_PHONE() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn1_img, &img_night_toggle_on_btn_unfocused);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn1_img, &img_night_toggle_off_btn_unfocused);
    }
    if (ReadMENU_SELECTION_MUSIC() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn2_img, &new_night_toggle_check_btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn2_img, &img_night_toggle_off_btn);
    }
    if (ReadMENU_SELECTION_VOLUME() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn3_img, &img_night_toggle_on_btn_unfocused);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_btn3_img, &img_night_toggle_off_btn_unfocused);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Datetimeset_Night_Date_During(void)
{

    if (g_Clock_Format_Selection_Cmd == 0)
    {
        lv_img_set_src(guider_ui.Setting_Screen_data_time_night_toggl_btn, &_btn_1_29x20);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_data_time_night_toggl_btn, &_off_btn_29x20);
    }
    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_up_arr_nigh_button_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_up_arr_nigh_button_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_do_arr_nigh_button_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_do_arr_nigh_button_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Datetimeset_Night_Time_During(void)
{
    if (g_Clock_Format_Selection_Cmd == 0)
    {
        lv_img_set_src(guider_ui.Setting_Screen_data_time_night_toggl_btn, &_btn_1_29x20);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_data_time_night_toggl_btn, &_off_btn_29x20);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_up_arr_nigh_button_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_up_arr_nigh_button_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_do_arr_nigh_button_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_do_arr_nigh_button_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Datetimeset_Night_24Hr_During(void)
{

    if (g_Clock_Format_Selection_Cmd == 0)
    {
        lv_img_set_src(guider_ui.Setting_Screen_data_time_night_toggl_btn, &_btn_1_29x20);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_data_time_night_toggl_btn, &_off_btn_29x20);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_up_arr_nigh_button_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_up_arr_nigh_button_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_do_arr_nigh_button_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_do_arr_nigh_button_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Dateset_Night_Entry(void)
{

    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_date_set_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE SETTING");

    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_hour,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_min,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_Colan,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_AM,LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(guider_ui.Setting_Screen_date_night_up_arr_1, &night_up_btn_pressed_);
    lv_img_set_src(guider_ui.Setting_Screen_date_night_down_arr_1, &night_down_btn_pressed_);

    lv_obj_clear_flag(guider_ui.Setting_Screen_date_night_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_date_night_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_night_lbl1, lv_color_night_orange(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_night_lbl1, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_night_lbl2, lv_color_white(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_night_lbl2, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_night_lbl3, lv_color_white(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_night_lbl3, 3);

    lv_obj_add_flag(guider_ui.Setting_Screen_setting_date_set_night_container, LV_OBJ_FLAG_HIDDEN);
}

/*Night Date set up arrow for orange color*/
void Dateset_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_date_set_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_hour,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_min,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_Colan,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_AM,LV_OBJ_FLAG_HIDDEN);
}
/*Night month set  arrow for orange color*/
void Monthset_Night_Entry(void)
{

    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_date_set_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE SETTING");

    lv_img_set_src(guider_ui.Setting_Screen_date_night_up_arr_2, &night_up_btn_pressed_);
    lv_img_set_src(guider_ui.Setting_Screen_date_night_down_arr_2, &night_down_btn_pressed_);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_date_night_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_date_night_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_hour,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_min,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_Colan,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_AM,LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_night_lbl1, lv_color_white(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_night_lbl1, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_night_lbl2, lv_color_night_orange(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_night_lbl2, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_night_lbl3, lv_color_white(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_night_lbl3, 3);

    lv_obj_add_flag(guider_ui.Setting_Screen_setting_date_set_night_container, LV_OBJ_FLAG_HIDDEN);
}

/*Night month set  arrow for orange color*/
void Monthset_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_date_set_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    //  lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_hour,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_min,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_Colan,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_AM,LV_OBJ_FLAG_HIDDEN);
}
/*Night year set up arrow for orange color*/
void Yearset_Night_Entry(void)
{

    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_date_set_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE SETTING");

    lv_img_set_src(guider_ui.Setting_Screen_date_night_up_arr_3, &night_up_btn_pressed_);
    lv_img_set_src(guider_ui.Setting_Screen_date_night_down_arr_3, &night_down_btn_pressed_);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_date_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_date_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    //      lv_obj_add_flag(guider_ui.Setting_Screen_Clock_hour,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_min,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_Colan,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_AM,LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_night_lbl1, lv_color_white(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_night_lbl1, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_night_lbl2, lv_color_white(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_night_lbl2, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_night_lbl3, lv_color_night_orange(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_night_lbl3, 3);

    lv_obj_add_flag(guider_ui.Setting_Screen_setting_date_set_night_container, LV_OBJ_FLAG_HIDDEN);
}
/*Night year set up arrow for orange color*/

void Yearset_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_date_set_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    //  lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_hour,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_min,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_Colan,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_AM,LV_OBJ_FLAG_HIDDEN);
}
/*Day Date set up arrow for orange color*/
void Dateset_Day_Entry(void)
{

    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_date_set_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE SETTING");

    lv_img_set_src(guider_ui.Setting_Screen_date_day_up_arr_1, &day_up_btn_pressed);
    lv_img_set_src(guider_ui.Setting_Screen_date_day_down_arr_1, &day_down_btn_pressed);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_hour,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_min,LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_date_day_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_date_day_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_Colan,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_AM,LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_day_lbl1, lv_color_night_orange(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_day_lbl1, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_day_lbl2, lv_color_black(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_day_lbl2, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_day_lbl3, lv_color_black(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_day_lbl3, 3);
}
/*Day Date set  arrow for orange color*/
void Dateset_Day_Exit(void)
{

    lv_obj_add_flag(guider_ui.Setting_Screen_setting_date_set_night_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_hour,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_min,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_Colan,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_AM,LV_OBJ_FLAG_HIDDEN);
}
/*Day month set arrow for orange color*/
void Monthset_Day_Entry(void)
{

    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_date_set_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE SETTING");

    lv_img_set_src(guider_ui.Setting_Screen_date_day_up_arr_2, &day_up_btn_pressed);
    lv_img_set_src(guider_ui.Setting_Screen_date_day_down_arr_2, &day_down_btn_pressed);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_date_day_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_date_day_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    //   lv_obj_add_flag(guider_ui.Setting_Screen_Clock_hour,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_min,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_Colan,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_AM,LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_day_lbl1, lv_color_black(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_day_lbl1, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_day_lbl2, lv_color_night_orange(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_day_lbl2, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_day_lbl3, lv_color_black(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_day_lbl3, 3);
}

/*Day Date month arrow for orange color*/
void Monthset_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_date_set_night_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    //  lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_hour,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_min,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_Colan,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_AM,LV_OBJ_FLAG_HIDDEN);
}
/*Day year set arrow for orange color*/
void Yearset_Day_Entry(void)
{

    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_date_set_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE SETTING");

    lv_img_set_src(guider_ui.Setting_Screen_date_day_up_arr_3, &day_up_btn_pressed);
    lv_img_set_src(guider_ui.Setting_Screen_date_day_down_arr_3, &day_down_btn_pressed);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_date_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_date_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    //   lv_obj_add_flag(guider_ui.Setting_Screen_Clock_hour,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_min,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_Colan,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_flag(guider_ui.Setting_Screen_Clock_AM,LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_day_lbl1, lv_color_black(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_day_lbl1, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_day_lbl2, lv_color_black(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_day_lbl2, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_date_day_lbl3, lv_color_night_orange(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_date_day_lbl3, 0);
}

/*Day year set arrow for orange color*/
void Yearset_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_date_set_night_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_date_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    //  lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_hour,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_min,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_Colan,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_AM,LV_OBJ_FLAG_HIDDEN);
}

/*Day Time set arrow for orange color*/
void Timeset_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_time_set_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME SETTING");
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_time_12_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_12_up_arr_2, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_time_12_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_12_down_arr_2, LV_OBJ_FLAG_HIDDEN);
}

/*Day Time set arrow for orange color*/

void Timeset_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_time_set_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME SETTING");

    lv_obj_set_pos(guider_ui.Setting_Screen_time_12_toset_lbl, 127, 231);
    lv_obj_set_size(guider_ui.Setting_Screen_time_12_toset_lbl, 37, 12);
    // lv_label_set_text(guider_ui.Setting_Screen_time_12_toset_lbl, "toSET");

    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);
}
/*Day Time set arrow for orange color*/
void Timeset_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);
}
/*Day Time set arrow for orange color*/
void Time_hr_set_Night_Entry(void)
{
    /*12HR x,y POSITION*/
    if (g_Clock_Format_Selection_Cmd == CLOCK_12HR_FORMAT)
    {
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl1, 59, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl2, 109, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl3, 148, 148);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_lbl3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_1, 60, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_2, 109, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_3, 159, 133);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_1, 60, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_2, 109, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_3, 159, 177);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);
    }
    /*24HR x,y POSITION*/
    else
    {
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl1, 89, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl2, 139, 148);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_night_lbl3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_1, 90, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_1, 90, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_2, 140, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_2, 140, 177);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);
    }

    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_time_set_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME SETTING");

    lv_obj_set_pos(guider_ui.Setting_Screen_time_12_toset_lbl, 127, 231);
    lv_obj_set_size(guider_ui.Setting_Screen_time_12_toset_lbl, 37, 12);
    // lv_label_set_text(guider_ui.Setting_Screen_time_12_toset_lbl, "toSET");
    lv_img_set_src(guider_ui.Setting_Screen_time_night_up_arr_1, &night_up_btn_pressed_);
    lv_img_set_src(guider_ui.Setting_Screen_time_night_down_arr_1, &night_down_btn_pressed_);

    lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_night_lbl1, lv_color_night_orange(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_night_lbl1, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_night_lbl2, lv_color_white(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_night_lbl2, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_night_lbl3, lv_color_white(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_night_lbl3, 0);

    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_night_container, LV_OBJ_FLAG_HIDDEN);
}
/*Day Time set arrow for orange color*/

void Time_hr_set_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);
}
/*Day Time set arrow for orange color*/
void Time_min_set_Night_Entry(void)
{
    /*12HR x,y POSITION*/
    if (g_Clock_Format_Selection_Cmd == CLOCK_12HR_FORMAT)
    {
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl1, 59, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl2, 109, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl3, 148, 148);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_lbl3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_1, 60, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_2, 109, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_3, 159, 133);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_1, 60, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_2, 109, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_3, 159, 177);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);
    }
    /*24HR x,y POSITION*/
    else
    {
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl1, 89, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl2, 139, 148);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_night_lbl3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_1, 90, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_1, 90, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_2, 140, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_2, 140, 177);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);
    }

    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_time_set_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME SETTING");

    lv_obj_set_pos(guider_ui.Setting_Screen_time_12_toset_lbl, 127, 231);
    lv_obj_set_size(guider_ui.Setting_Screen_time_12_toset_lbl, 37, 12);
    // lv_label_set_text(guider_ui.Setting_Screen_time_12_toset_lbl, "toSET");
    lv_img_set_src(guider_ui.Setting_Screen_time_night_up_arr_2, &night_up_btn_pressed_);
    lv_img_set_src(guider_ui.Setting_Screen_time_night_down_arr_2, &night_down_btn_pressed_);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_night_lbl1, lv_color_white(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_night_lbl1, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_night_lbl2, lv_color_night_orange(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_night_lbl2, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_night_lbl3, lv_color_white(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_night_lbl3, 0);

    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_night_container, LV_OBJ_FLAG_HIDDEN);
}
/*Day Time set arrow for orange color*/

void Time_min_set_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);
}
/*Day Time set arrow for orange color*/
void Time_ampm_set_Night_Entry(void)
{
    /*12HR x,y POSITION*/
    if (g_Clock_Format_Selection_Cmd == CLOCK_12HR_FORMAT)
    {
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl1, 59, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl2, 109, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl3, 148, 148);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_lbl3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_1, 60, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_2, 109, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_3, 159, 133);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_1, 60, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_2, 109, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_3, 159, 177);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);
    }
    /*24HR x,y POSITION*/
    else
    {
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl1, 89, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_lbl2, 139, 148);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_night_lbl3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_1, 90, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_1, 90, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_up_arr_2, 140, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_night_down_arr_2, 140, 177);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);
    }

    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_time_set_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME SETTING");

    lv_obj_set_pos(guider_ui.Setting_Screen_time_12_toset_lbl, 127, 231);
    lv_obj_set_size(guider_ui.Setting_Screen_time_12_toset_lbl, 37, 12);
    // lv_label_set_text(guider_ui.Setting_Screen_time_12_toset_lbl, "toSET");

    lv_img_set_src(guider_ui.Setting_Screen_time_night_up_arr_3, &night_up_btn_pressed_);
    lv_img_set_src(guider_ui.Setting_Screen_time_night_down_arr_3, &night_down_btn_pressed_);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_time_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_night_lbl1, lv_color_white(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_night_lbl1, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_night_lbl2, lv_color_white(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_night_lbl2, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_night_lbl3, lv_color_night_orange(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_night_lbl3, 0);

    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_night_container, LV_OBJ_FLAG_HIDDEN);
}
/*Day Time set arrow for orange color*/

void Time_ampm_set_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_night_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);
}
/*Day Time set arrow for orange color*/

void Time_hr_set_Day_Entry(void)
{
    /*12HR x,y POSITION*/
    if (g_Clock_Format_Selection_Cmd == CLOCK_12HR_FORMAT)
    {
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl1, 59, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl2, 109, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl3, 148, 148);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_lbl3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_1, 60, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_2, 109, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_3, 159, 133);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_1, 60, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_2, 109, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_3, 159, 177);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);
    }
    /*24HR x,y POSITION*/
    else
    {
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl1, 89, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl2, 139, 148);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_day_lbl3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_1, 90, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_1, 90, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_2, 140, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_2, 140, 177);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);
    }

    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_time_set_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME SETTING");

    lv_obj_set_pos(guider_ui.Setting_Screen_time_12_toset_lbl, 127, 231);
    lv_obj_set_size(guider_ui.Setting_Screen_time_12_toset_lbl, 37, 12);
    // lv_label_set_text(guider_ui.Setting_Screen_time_12_toset_lbl, "toSET");
    lv_img_set_src(guider_ui.Setting_Screen_time_day_up_arr_1, &day_up_btn_pressed);
    lv_img_set_src(guider_ui.Setting_Screen_time_day_down_arr_1, &day_down_btn_pressed);

    lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_day_lbl1, lv_color_night_orange(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_day_lbl1, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_day_lbl2, lv_color_black(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_day_lbl2, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_day_lbl3, lv_color_black(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_day_lbl3, 0);
}
/*Day Time set up arrow for orange color*/

void Time_hr_set_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_night_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);
}
/*Day Time set up arrow for orange color*/
void Time_min_set_Day_Entry(void)
{
    /*12HR x,y POSITION*/
    if (g_Clock_Format_Selection_Cmd == CLOCK_12HR_FORMAT)
    {
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl1, 59, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl2, 109, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl3, 148, 148);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_lbl3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_1, 60, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_2, 109, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_3, 159, 133);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_1, 60, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_2, 109, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_3, 159, 177);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);
    }
    /*24HR x,y POSITION*/
    else
    {
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl1, 89, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl2, 139, 148);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_day_lbl3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_1, 90, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_1, 90, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_2, 140, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_2, 140, 177);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);
    }

    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_time_set_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME SETTING");

    lv_obj_set_pos(guider_ui.Setting_Screen_time_12_toset_lbl, 127, 231);
    lv_obj_set_size(guider_ui.Setting_Screen_time_12_toset_lbl, 37, 12);
    // lv_label_set_text(guider_ui.Setting_Screen_time_12_toset_lbl, "toSET");
    lv_img_set_src(guider_ui.Setting_Screen_time_day_up_arr_2, &day_up_btn_pressed);
    lv_img_set_src(guider_ui.Setting_Screen_time_day_down_arr_2, &day_down_btn_pressed);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_day_lbl1, lv_color_black(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_day_lbl1, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_day_lbl2, lv_color_night_orange(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_day_lbl2, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_day_lbl3, lv_color_black(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_day_lbl3, 0);
}

/*Day Time set up arrow for orange color*/
void Time_min_set_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_night_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);
}
/*Day Time set up arrow for orange color*/
void Time_ampm_set_Day_Entry(void)
{
    /*12HR x,y POSITION*/
    if (g_Clock_Format_Selection_Cmd == CLOCK_12HR_FORMAT)
    {
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl1, 59, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl2, 109, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl3, 148, 148);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_lbl3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_1, 60, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_2, 109, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_3, 159, 133);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_1, 60, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_2, 109, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_3, 159, 177);
        lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);
    }
    /*24HR x,y POSITION*/
    else
    {
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl1, 89, 148);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_lbl2, 139, 148);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_day_lbl3, LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_1, 90, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_1, 90, 177);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_up_arr_2, 140, 133);
        lv_obj_set_pos(guider_ui.Setting_Screen_time_day_down_arr_2, 140, 177);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);
    }

    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_time_set_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME SETTING");

    lv_obj_set_pos(guider_ui.Setting_Screen_time_12_toset_lbl, 127, 231);
    lv_obj_set_size(guider_ui.Setting_Screen_time_12_toset_lbl, 37, 12);
    // lv_label_set_text(guider_ui.Setting_Screen_time_12_toset_lbl, "toSET");
    lv_img_set_src(guider_ui.Setting_Screen_time_day_up_arr_3, &day_up_btn_pressed);
    lv_img_set_src(guider_ui.Setting_Screen_time_day_down_arr_3, &day_down_btn_pressed);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_time_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_day_lbl1, lv_color_black(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_day_lbl1, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_day_lbl2, lv_color_black(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_day_lbl2, 0);

    lv_obj_set_style_text_color(guider_ui.Setting_Screen_time_day_lbl3, lv_color_night_orange(), 0);
    set_obj_opa_S(guider_ui.Setting_Screen_time_day_lbl3, 0);
}
/*Day Time set up arrow for orange color*/

void Time_ampm_set_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_night_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_up_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_time_day_down_arr_3, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);
}

void Timeset_12_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_time_12_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME SETTING");
}

void Timeset_12_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_12_container, LV_OBJ_FLAG_HIDDEN);
}

void SWInfo_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_about_inf_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "SW VERSION");
    lv_label_set_text(guider_ui.Setting_Screen_aboutinf_lb1, "02.00.00");
}

void SWInfo_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_about_inf_container, LV_OBJ_FLAG_HIDDEN);
}

void SWInfo_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_about_inf_nigh_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "SW VERSION");
    lv_label_set_text(guider_ui.Setting_Screen_aboutinf_nnight_lbl1, "02.00.00");
}

void SWInfo_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_about_inf_nigh_container, LV_OBJ_FLAG_HIDDEN);
}

void Music_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_music_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MUSIC");
}

void Music_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_music_night_container, LV_OBJ_FLAG_HIDDEN);
}

void Music_Night_Album_During(void)
{

    if (g_User_Music_Select_Level_U8 == GENRE)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn1_img, &new_rb_night_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn1_img, &img_night_radio_active_btn_3_base);
    }
    if (g_User_Music_Select_Level_U8 == ALBUM)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn2_img, &new_rb_night_sel_focus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn2_img, &img_night_radio_active_btn_2_base);
    }
    if (g_User_Music_Select_Level_U8 == ARTIST)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn3_img, &new_rb_night_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn3_img, &img_night_radio_active_btn_3_base);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_up_arr_night_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_up_arr_night_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_down_arr_night_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_down_arr_night_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Music_Night_Artist_During(void)
{
    if (g_User_Music_Select_Level_U8 == ALBUM)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn1_img, &new_rb_night_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn1_img, &img_night_radio_active_btn_3_base);
    }
    if (g_User_Music_Select_Level_U8 == ARTIST)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn2_img, &new_rb_night_sel_focus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn2_img, &img_night_radio_active_btn_2_base);
    }
    if (g_User_Music_Select_Level_U8 == GENRE)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn3_img, &new_rb_night_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn3_img, &img_night_radio_active_btn_3_base);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_up_arr_night_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_up_arr_night_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_down_arr_night_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_down_arr_night_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Music_Night_Genre_During(void)
{

    if (g_User_Music_Select_Level_U8 == ARTIST)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn1_img, &new_rb_night_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn1_img, &img_night_radio_active_btn_3_base);
    }
    if (g_User_Music_Select_Level_U8 == GENRE)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn2_img, &new_rb_night_sel_focus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn2_img, &img_night_radio_active_btn_2_base);
    }
    if (g_User_Music_Select_Level_U8 == ALBUM)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn3_img, &new_rb_night_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_btn3_img, &img_night_radio_active_btn_3_base);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_up_arr_night_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_up_arr_night_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_down_arr_night_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_down_arr_night_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Music_Day_Album_During(void)
{
    if (g_User_Music_Select_Level_U8 == GENRE)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn1_img, &new_rb_day_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn1_img, &Grey_day_radio_active_btn_1_base);
    }
    if (g_User_Music_Select_Level_U8 == ALBUM)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn2_img, &_radiobtn_day_checked_20x20);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn2_img, &Black_day_radio_active_btn_2_base);
    }
    if (g_User_Music_Select_Level_U8 == ARTIST)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn3_img, &new_rb_day_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn3_img, &Grey_day_radio_active_btn_1_base);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_night_arr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_night_arr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Music_Day_Artist_During(void)
{
    if (g_User_Music_Select_Level_U8 == ALBUM)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn1_img, &new_rb_day_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn1_img, &Grey_day_radio_active_btn_1_base);
    }
    if (g_User_Music_Select_Level_U8 == ARTIST)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn2_img, &_radiobtn_day_checked_20x20);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn2_img, &Black_day_radio_active_btn_2_base);
    }
    if (g_User_Music_Select_Level_U8 == GENRE)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn3_img, &new_rb_day_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn3_img, &Grey_day_radio_active_btn_1_base);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_night_arr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_night_arr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Music_Day_Genre_During(void)
{
    if (g_User_Music_Select_Level_U8 == ARTIST)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn1_img, &new_rb_day_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn1_img, &Grey_day_radio_active_btn_1_base);
    }
    if (g_User_Music_Select_Level_U8 == GENRE)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn2_img, &_radiobtn_day_checked_20x20);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn2_img, &Black_day_radio_active_btn_2_base);
    }
    if (g_User_Music_Select_Level_U8 == ALBUM)
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn3_img, &new_rb_day_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_music_sel_day_btn3_img, &Grey_day_radio_active_btn_1_base);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_night_arr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_music_night_arr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Unit_Sub_fuel_L100_Day_During(void)
{
    if (g_User_Sel_TC_Unit == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_day_btn_img, &_radiobtn_day_checked_20x20);
        g_RADIOBUTTON_Status = FALSE;
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_day_btn_img, &Black_day_radio_active_btn_2_base);
        g_RADIOBUTTON_Status = TRUE;
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_night_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_night_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Unit_Sub_fuel_km_Day_During(void)
{

    if (g_User_Sel_TC_Unit == 2)
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_day_btn_img, &_radiobtn_day_checked_20x20);
        g_RADIOBUTTON_Status = FALSE;
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_day_btn_img, &Black_day_radio_active_btn_2_base);
        g_RADIOBUTTON_Status = TRUE;
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_night_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_night_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

/*
    Day  Mode
*/

void TripA_Trip_Day_During(void)
{
    uint32_t fl_present_Bike_TripA_Value_Day_u32 = ODO_Get_TripOdometer(0);
    uint8_t fl_present_Bike_Trip_time_hour_Day_u8 = Swc_Trip_Timer_Get_Hour_value(0);
    uint8_t fl_present_Bike_Trip_time_Minute_Day_u8 = Swc_Trip_Timer_Get_Min_value(0);
    bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();

    lv_label_set_text(guider_ui.Setting_Screen_trip_day_lbl1, "Hold        To RESET");

    if (fl_present_Bike_TripA_Value_Day_u32 == ODO_INVALID_STATE)
    {
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Trip ---.- km");
    }
    else if ((g_previous_Bike_TripA_Value_Day_u32 != fl_present_Bike_TripA_Value_Day_u32))
    {
        g_previous_Bike_TripA_Value_Day_u32 = fl_present_Bike_TripA_Value_Day_u32;
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Trip %d.%d km", (g_previous_Bike_TripA_Value_Day_u32 / 10), (g_previous_Bike_TripA_Value_Day_u32 % 10));
    }

    if (fl_Trip_Timer_St != FALSE)
    {
        if ((g_previous_Bike_Trip_time_hour_Day_u8 != fl_present_Bike_Trip_time_hour_Day_u8) ||
            (fl_present_Bike_Trip_time_Minute_Day_u8 != g_previous_Bike_Trip_time_Minute_Day_u8))
        {
            g_previous_Bike_Trip_time_hour_Day_u8 = fl_present_Bike_Trip_time_hour_Day_u8;
            g_previous_Bike_Trip_time_Minute_Day_u8 = fl_present_Bike_Trip_time_Minute_Day_u8;

            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Time %d h %d m", g_previous_Bike_Trip_time_hour_Day_u8, g_previous_Bike_Trip_time_Minute_Day_u8);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        lv_label_set_text(guider_ui.Setting_Screen_trip_day_lbl3, "Time  --h--m");
        g_previous_Bike_Trip_time_hour_Day_u8 = 0XFF;
    }

    lv_obj_clear_flag(guider_ui.Setting_Screen_trip_day_hold, LV_OBJ_FLAG_HIDDEN);
    set_obj_opa(guider_ui.Setting_Screen_trip_day_hold, 50);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_day_hold, Holdbtnpos[0], Holdbtnpos[1]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripA_Time_Day_During(void)
{
    uint32_t fl_present_Bike_TripA_Value_Day_u32 = ODO_Get_TripOdometer(0);
    uint8_t fl_present_Bike_Trip_time_hour_Day_u8 = Swc_Trip_Timer_Get_Hour_value(0);
    uint8_t fl_present_Bike_Trip_time_Minute_Day_u8 = Swc_Trip_Timer_Get_Min_value(0);
    uint32_t fl_present_Bike_TripA_AVSValue_Day_u32 = Swc_Avereage_Speed_Get_value(0);
    bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
    bool fl_Trip_AVS_Status_bl = Swc_Average_Speed_Get_Status();

    if (fl_present_Bike_TripA_Value_Day_u32 == ODO_INVALID_STATE)
    {
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Trip ---.- km");
    }
    else if ((g_previous_Bike_TripA_Value_Day_u32 != fl_present_Bike_TripA_Value_Day_u32))
    {
        g_previous_Bike_TripA_Value_Day_u32 = fl_present_Bike_TripA_Value_Day_u32;
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Trip %d.%d km", (g_previous_Bike_TripA_Value_Day_u32 / 10), (g_previous_Bike_TripA_Value_Day_u32 % 10));
    }
    else
    {
        /* do nothing */
    }

    if (fl_Trip_Timer_St != FALSE)
    {
        if ((g_previous_Bike_Trip_time_hour_Day_u8 != fl_present_Bike_Trip_time_hour_Day_u8) ||
            (fl_present_Bike_Trip_time_Minute_Day_u8 != g_previous_Bike_Trip_time_Minute_Day_u8))
        {
            g_previous_Bike_Trip_time_hour_Day_u8 = fl_present_Bike_Trip_time_hour_Day_u8;
            g_previous_Bike_Trip_time_Minute_Day_u8 = fl_present_Bike_Trip_time_Minute_Day_u8;

            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Time %d h %d m", g_previous_Bike_Trip_time_hour_Day_u8, g_previous_Bike_Trip_time_Minute_Day_u8);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        lv_label_set_text(guider_ui.Setting_Screen_trip_day_lbl2, "Time  --h--m");
        g_previous_Bike_Trip_time_hour_Day_u8 = 0XFF;
    }

    if ((fl_present_Bike_TripA_AVSValue_Day_u32 != g_previous_Bike_TripA_AVSValue_Day_u32))
    {
        g_previous_Bike_TripA_AVSValue_Day_u32 = fl_present_Bike_TripA_AVSValue_Day_u32;

        if ((g_previous_Bike_TripA_AVSValue_Day_u32 > AVEREAGE_SPEED) || (fl_Trip_AVS_Status_bl == FALSE))
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Av Speed --- km/h");
        }
        else
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Av Speed %d km/h", (g_previous_Bike_TripA_AVSValue_Day_u32));
        }
    }
    else
    {
        /* do nothing */
    }
    lv_obj_add_flag(guider_ui.Setting_Screen_trip_day_hold, LV_OBJ_FLAG_HIDDEN);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripA_AvSpeed_Day_During(void)
{
    uint32_t fl_present_Bike_TripA_AVSValue_Day_u32 = Swc_Avereage_Speed_Get_value(0);
    uint32_t fl_present_Bike_TripA_AVFValue_Day_u32 = display_AFE(0);
    uint8_t fl_present_Bike_Trip_time_hour_Day_u8 = Swc_Trip_Timer_Get_Hour_value(0);
    uint8_t fl_present_Bike_Trip_time_Minute_Day_u8 = Swc_Trip_Timer_Get_Min_value(0);

    bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
    uint32_t AFE_Unit_u32 = 0;
    bool fl_Trip_AVS_Status_bl = Swc_Average_Speed_Get_Status();

    if ((fl_present_Bike_TripA_AVSValue_Day_u32 != g_previous_Bike_TripA_AVSValue_Day_u32))
    {
        g_previous_Bike_TripA_AVSValue_Day_u32 = fl_present_Bike_TripA_AVSValue_Day_u32;

        if ((g_previous_Bike_TripA_AVSValue_Day_u32 > AVEREAGE_SPEED) || (fl_Trip_AVS_Status_bl == FALSE))
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Av Speed --- km/h");
        }
        else
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Av Speed %d km/h", (g_previous_Bike_TripA_AVSValue_Day_u32));
        }
    }
    else
    {
        /* do nothing */
    }

    if (fl_Trip_Timer_St != FALSE)
    {
        if ((g_previous_Bike_Trip_time_hour_Day_u8 != fl_present_Bike_Trip_time_hour_Day_u8) ||
            (fl_present_Bike_Trip_time_Minute_Day_u8 != g_previous_Bike_Trip_time_Minute_Day_u8))
        {
            g_previous_Bike_Trip_time_hour_Day_u8 = fl_present_Bike_Trip_time_hour_Day_u8;
            g_previous_Bike_Trip_time_Minute_Day_u8 = fl_present_Bike_Trip_time_Minute_Day_u8;

            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Time %d h %d m", g_previous_Bike_Trip_time_hour_Day_u8, g_previous_Bike_Trip_time_Minute_Day_u8);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        lv_label_set_text(guider_ui.Setting_Screen_trip_day_lbl1, "Time  --h--m");
        g_previous_Bike_Trip_time_hour_Day_u8 = 0XFF;
    }

    if (g_Fuel_Current_Unit == Lper100km)
    {
        if ((fl_present_Bike_TripA_AVFValue_Day_u32 != 0) && (fl_present_Bike_TripA_AVFValue_Day_u32 != TC_INVALID))
        {

            fl_present_Bike_TripA_AVFValue_Day_u32 = 10000 / fl_present_Bike_TripA_AVFValue_Day_u32;
        }

        /* Limit AVF value if it exceeds max limit */
        SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&fl_present_Bike_TripA_AVFValue_Day_u32);
    }
    else
    {
        /* do nothing*/
    }

    if ((g_previous_Bike_TripA_AVFValue_Day_u32 != fl_present_Bike_TripA_AVFValue_Day_u32))
    {
        g_previous_Bike_TripA_AVFValue_Day_u32 = fl_present_Bike_TripA_AVFValue_Day_u32;

        if (TC_INVALID != g_previous_Bike_TripA_AVFValue_Day_u32)
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Av Fuel %d.%d km/L", (g_previous_Bike_TripA_AVFValue_Day_u32 / 10), (g_previous_Bike_TripA_AVFValue_Day_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Av Fuel %d.%d L/100km", (g_previous_Bike_TripA_AVFValue_Day_u32 / 10), (g_previous_Bike_TripA_AVFValue_Day_u32 % 10));
            }
        }
        else
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Av Fuel ---.- km/L", (g_previous_Bike_TripA_AVFValue_Day_u32 / 10), (g_previous_Bike_TripA_AVFValue_Day_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Av Fuel ---.- L/100km", (g_previous_Bike_TripA_AVFValue_Day_u32 / 10), (g_previous_Bike_TripA_AVFValue_Day_u32 % 10));
            }
        }
    }
    else
    {
        /* do nothing */
    }
    lv_obj_add_flag(guider_ui.Setting_Screen_trip_day_hold, LV_OBJ_FLAG_HIDDEN);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripA_AVFuel_Day_During(void)
{
    uint32_t fl_present_Bike_TripA_AVSValue_Day_u32 = Swc_Avereage_Speed_Get_value(0);
    uint32_t fl_present_Bike_TripA_AVFValue_Day_u32 = display_AFE(0);
    uint32_t fl_present_Bike_TripA_AVFValue_Unit_Set_Day_u32 = Fuel_Consumption_fn();
    bool fl_Trip_AVS_Status_bl = Swc_Average_Speed_Get_Status();
    uint32_t AFE_Unit_u32 = 0;

    if ((fl_present_Bike_TripA_AVSValue_Day_u32 != g_previous_Bike_TripA_AVSValue_Day_u32))
    {
        g_previous_Bike_TripA_AVSValue_Day_u32 = fl_present_Bike_TripA_AVSValue_Day_u32;

        if ((g_previous_Bike_TripA_AVSValue_Day_u32 > AVEREAGE_SPEED) || (fl_Trip_AVS_Status_bl == FALSE))
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Av Speed --- km/h");
        }
        else
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Av Speed %d km/h", (g_previous_Bike_TripA_AVSValue_Day_u32));
        }
    }
    else
    {
        /* do nothing */
    }

    if (g_Fuel_Current_Unit == Lper100km)
    {
        if ((fl_present_Bike_TripA_AVFValue_Day_u32 != 0) && (fl_present_Bike_TripA_AVFValue_Day_u32 != TC_INVALID))
        {

            fl_present_Bike_TripA_AVFValue_Day_u32 = 10000 / fl_present_Bike_TripA_AVFValue_Day_u32;
        }

        /* Limit AVF value if it exceeds max limit */
        SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&fl_present_Bike_TripA_AVFValue_Day_u32);
    }
    else
    {
        /* do nothing*/
    }

    if ((g_previous_Bike_TripA_AVFValue_Day_u32 != fl_present_Bike_TripA_AVFValue_Day_u32))
    {
        g_previous_Bike_TripA_AVFValue_Day_u32 = fl_present_Bike_TripA_AVFValue_Day_u32;

        if (TC_INVALID != g_previous_Bike_TripA_AVFValue_Day_u32)
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Av Fuel %d.%d km/L", (g_previous_Bike_TripA_AVFValue_Day_u32 / 10), (g_previous_Bike_TripA_AVFValue_Day_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Av Fuel %d.%d L/100km", (g_previous_Bike_TripA_AVFValue_Day_u32 / 10), (g_previous_Bike_TripA_AVFValue_Day_u32 % 10));
            }
        }
        else
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Av Fuel ---.- km/L", (g_previous_Bike_TripA_AVFValue_Day_u32 / 10), (g_previous_Bike_TripA_AVFValue_Day_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Av Fuel ---.- L/100km", (g_previous_Bike_TripA_AVFValue_Day_u32 / 10), (g_previous_Bike_TripA_AVFValue_Day_u32 % 10));
            }
        }
    }
    else
    {
        /* do nothing */
    }

    lv_label_set_text(guider_ui.Setting_Screen_trip_day_lbl3, "Hold        To RESET");
    lv_obj_clear_flag(guider_ui.Setting_Screen_trip_day_hold, LV_OBJ_FLAG_HIDDEN);
    set_obj_opa(guider_ui.Setting_Screen_trip_day_hold, 50);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_day_hold, Holdbtnpos[2], Holdbtnpos[3]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripA_Hold_Day_During(void)
{
    uint32_t fl_present_Bike_TripA_Value_Day_u32 = ODO_Get_TripOdometer(0);
    uint32_t fl_present_Bike_TripA_AVSValue_Day_u32 = Swc_Avereage_Speed_Get_value(0);
    uint32_t fl_present_Bike_TripA_AVFValue_Day_u32 = display_AFE(0);

    uint32_t AFE_Unit_u32 = 0;

    if (fl_present_Bike_TripA_Value_Day_u32 == ODO_INVALID_STATE)
    {
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Trip ---.- km");
    }
    else if ((g_previous_Bike_TripA_Value_Day_u32 != fl_present_Bike_TripA_Value_Day_u32))
    {
        g_previous_Bike_TripA_Value_Day_u32 = fl_present_Bike_TripA_Value_Day_u32;
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Trip %d.%d km", (g_previous_Bike_TripA_Value_Day_u32 / 10), (g_previous_Bike_TripA_Value_Day_u32 % 10));
    }
    else
    {
        /* do nothing */
    }

    if (g_Fuel_Current_Unit == Lper100km)
    {
        if ((fl_present_Bike_TripA_AVFValue_Day_u32 != 0) && (fl_present_Bike_TripA_AVFValue_Day_u32 != TC_INVALID))
        {

            fl_present_Bike_TripA_AVFValue_Day_u32 = 10000 / fl_present_Bike_TripA_AVFValue_Day_u32;
        }

        /* Limit AVF value if it exceeds max limit */
        SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&fl_present_Bike_TripA_AVFValue_Day_u32);
    }
    else
    {
        /* do nothing*/
    }

    if ((g_previous_Bike_TripA_AVFValue_Day_u32 != fl_present_Bike_TripA_AVFValue_Day_u32))
    {
        g_previous_Bike_TripA_AVFValue_Day_u32 = fl_present_Bike_TripA_AVFValue_Day_u32;

        if (TC_INVALID != g_previous_Bike_TripA_AVFValue_Day_u32)
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Av Fuel %d.%d km/L", (g_previous_Bike_TripA_AVFValue_Day_u32 / 10), (g_previous_Bike_TripA_AVFValue_Day_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Av Fuel %d.%d L/100km", (g_previous_Bike_TripA_AVFValue_Day_u32 / 10), (g_previous_Bike_TripA_AVFValue_Day_u32 % 10));
            }
        }
        else
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Av Fuel ---.- km/L", (g_previous_Bike_TripA_AVFValue_Day_u32 / 10), (g_previous_Bike_TripA_AVFValue_Day_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Av Fuel ---.- L/100km", (g_previous_Bike_TripA_AVFValue_Day_u32 / 10), (g_previous_Bike_TripA_AVFValue_Day_u32 % 10));
            }
        }
    }
    else
    {
        /* do nothing */
    }

    lv_label_set_text(guider_ui.Setting_Screen_trip_day_lbl2, "Hold        To RESET");
    set_obj_opa(guider_ui.Setting_Screen_trip_day_hold, 255);
    lv_obj_clear_flag(guider_ui.Setting_Screen_trip_day_hold, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_day_hold, Holdbtnpos[4], Holdbtnpos[5]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}
void TripB_Trip_Day_During(void)
{
    uint32_t fl_present_Bike_TripB_Value_Day_u32 = ODO_Get_TripOdometer(1);
    uint8_t fl_present_Bike_Trip_time_hour_Day_u8 = Swc_Trip_Timer_Get_Hour_value(1);
    uint8_t fl_present_Bike_Trip_time_Minute_Day_u8 = Swc_Trip_Timer_Get_Min_value(1);
    bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();

    lv_label_set_text(guider_ui.Setting_Screen_trip_day_lbl1, "Hold        To RESET");

    if (fl_present_Bike_TripB_Value_Day_u32 == ODO_INVALID_STATE)
    {
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Trip ---.- km");
    }
    else if ((g_previous_Bike_TripB_Value_Day_u32 != fl_present_Bike_TripB_Value_Day_u32))
    {
        g_previous_Bike_TripB_Value_Day_u32 = fl_present_Bike_TripB_Value_Day_u32;
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Trip %d.%d km", (g_previous_Bike_TripB_Value_Day_u32 / 10), (g_previous_Bike_TripB_Value_Day_u32 % 10));
    }
    else
    {
        /* do nothing*/
    }

    if (fl_Trip_Timer_St != FALSE)
    {
        if ((g_previous_Bike_Trip_time_hour_Day_u8 != fl_present_Bike_Trip_time_hour_Day_u8) ||
            (fl_present_Bike_Trip_time_Minute_Day_u8 != g_previous_Bike_Trip_time_Minute_Day_u8))
        {
            g_previous_Bike_Trip_time_hour_Day_u8 = fl_present_Bike_Trip_time_hour_Day_u8;
            g_previous_Bike_Trip_time_Minute_Day_u8 = fl_present_Bike_Trip_time_Minute_Day_u8;

            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Time %d h %d m", g_previous_Bike_Trip_time_hour_Day_u8, g_previous_Bike_Trip_time_Minute_Day_u8);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        lv_label_set_text(guider_ui.Setting_Screen_trip_day_lbl3, "Time  --h--m");
        g_previous_Bike_Trip_time_hour_Day_u8 = 0XFF;
    }

    lv_obj_clear_flag(guider_ui.Setting_Screen_trip_day_hold, LV_OBJ_FLAG_HIDDEN);
    set_obj_opa(guider_ui.Setting_Screen_trip_day_hold, 50);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_day_hold, Holdbtnpos[0], Holdbtnpos[1]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripB_Time_Day_During(void)
{
    uint32_t fl_present_Bike_TripB_Value_Day_u32 = ODO_Get_TripOdometer(1);
    uint8_t fl_present_Bike_Trip_time_hour_Day_u8 = Swc_Trip_Timer_Get_Hour_value(1);
    uint8_t fl_present_Bike_Trip_time_Minute_Day_u8 = Swc_Trip_Timer_Get_Min_value(1);
    uint32_t fl_present_Bike_TripB_AVSValue_Day_u32 = Swc_Avereage_Speed_Get_value(1);
    bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
    bool fl_Trip_AVS_Status_bl = Swc_Average_Speed_Get_Status();

    if (fl_present_Bike_TripB_Value_Day_u32 == ODO_INVALID_STATE)
    {
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Trip ---.- km");
    }
    else if ((g_previous_Bike_TripB_Value_Day_u32 != fl_present_Bike_TripB_Value_Day_u32))
    {
        g_previous_Bike_TripB_Value_Day_u32 = fl_present_Bike_TripB_Value_Day_u32;
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Trip %d.%d km", (g_previous_Bike_TripB_Value_Day_u32 / 10), (g_previous_Bike_TripB_Value_Day_u32 % 10));
    }
    else
    {
        /* do nothing */
    }

    if (fl_Trip_Timer_St != FALSE)
    {
        if ((g_previous_Bike_Trip_time_hour_Day_u8 != fl_present_Bike_Trip_time_hour_Day_u8) ||
            (fl_present_Bike_Trip_time_Minute_Day_u8 != g_previous_Bike_Trip_time_Minute_Day_u8))
        {
            g_previous_Bike_Trip_time_hour_Day_u8 = fl_present_Bike_Trip_time_hour_Day_u8;
            g_previous_Bike_Trip_time_Minute_Day_u8 = fl_present_Bike_Trip_time_Minute_Day_u8;

            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Time %d h %d m", g_previous_Bike_Trip_time_hour_Day_u8, g_previous_Bike_Trip_time_Minute_Day_u8);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        lv_label_set_text(guider_ui.Setting_Screen_trip_day_lbl2, "Time  --h--m");
        g_previous_Bike_Trip_time_hour_Day_u8 = 0XFF;
    }

    if ((fl_present_Bike_TripB_AVSValue_Day_u32 != g_previous_Bike_TripB_AVSValue_Day_u32))
    {
        g_previous_Bike_TripB_AVSValue_Day_u32 = fl_present_Bike_TripB_AVSValue_Day_u32;

        if ((g_previous_Bike_TripB_AVSValue_Day_u32 > AVEREAGE_SPEED) || (fl_Trip_AVS_Status_bl == FALSE))
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Av Speed --- km/h");
        }
        else
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Av Speed %d km/h", (g_previous_Bike_TripB_AVSValue_Day_u32));
        }
    }
    else
    {
        /* do nothing */
    }

    lv_obj_add_flag(guider_ui.Setting_Screen_trip_day_hold, LV_OBJ_FLAG_HIDDEN);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripB_AvSpeed_Day_During(void)
{
    uint32_t fl_present_Bike_TripB_AVSValue_Day_u32 = Swc_Avereage_Speed_Get_value(1);
    uint32_t fl_present_Bike_TripB_AVFValue_Day_u32 = display_AFE(1);
    uint8_t fl_present_Bike_Trip_time_hour_Day_u8 = Swc_Trip_Timer_Get_Hour_value(1);
    uint8_t fl_present_Bike_Trip_time_Minute_Day_u8 = Swc_Trip_Timer_Get_Min_value(1);
    bool fl_Trip_Timer_St = Swc_Get_Trip_Timer_Status();
    uint32_t AFE_Unit_u32 = 0;
    bool fl_Trip_AVS_Status_bl = Swc_Average_Speed_Get_Status();

    if ((fl_present_Bike_TripB_AVSValue_Day_u32 != g_previous_Bike_TripB_AVSValue_Day_u32))
    {
        g_previous_Bike_TripB_AVSValue_Day_u32 = fl_present_Bike_TripB_AVSValue_Day_u32;

        if ((g_previous_Bike_TripB_AVSValue_Day_u32 > AVEREAGE_SPEED) || (fl_Trip_AVS_Status_bl == FALSE))
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Av Speed --- km/h");
        }
        else
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Av Speed %d km/h", (g_previous_Bike_TripB_AVSValue_Day_u32));
        }
    }
    else
    {
        /* do nothing */
    }

    if (fl_Trip_Timer_St != FALSE)
    {
        if ((g_previous_Bike_Trip_time_hour_Day_u8 != fl_present_Bike_Trip_time_hour_Day_u8) ||
            (fl_present_Bike_Trip_time_Minute_Day_u8 != g_previous_Bike_Trip_time_Minute_Day_u8))
        {
            g_previous_Bike_Trip_time_hour_Day_u8 = fl_present_Bike_Trip_time_hour_Day_u8;
            g_previous_Bike_Trip_time_Minute_Day_u8 = fl_present_Bike_Trip_time_Minute_Day_u8;

            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Time %d h %d m", g_previous_Bike_Trip_time_hour_Day_u8, g_previous_Bike_Trip_time_Minute_Day_u8);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        lv_label_set_text(guider_ui.Setting_Screen_trip_day_lbl1, "Time  --h--m");
        g_previous_Bike_Trip_time_hour_Day_u8 = 0XFF;
    }

    if (g_Fuel_Current_Unit == Lper100km)
    {
        if ((fl_present_Bike_TripB_AVFValue_Day_u32 != 0) && (fl_present_Bike_TripB_AVFValue_Day_u32 != TC_INVALID))
        {

            fl_present_Bike_TripB_AVFValue_Day_u32 = 10000 / fl_present_Bike_TripB_AVFValue_Day_u32;
        }

        /* Limit AVF value if it exceeds max limit */
        SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&fl_present_Bike_TripB_AVFValue_Day_u32);
    }
    else
    {
        /* do nothing*/
    }

    if ((g_previous_Bike_TripB_AVFValue_Day_u32 != fl_present_Bike_TripB_AVFValue_Day_u32))
    {
        g_previous_Bike_TripB_AVFValue_Day_u32 = fl_present_Bike_TripB_AVFValue_Day_u32;

        if (TC_INVALID != g_previous_Bike_TripB_AVFValue_Day_u32)
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Av Fuel %d.%d km/L", (g_previous_Bike_TripB_AVFValue_Day_u32 / 10), (g_previous_Bike_TripB_AVFValue_Day_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Av Fuel %d.%d L/100km", (g_previous_Bike_TripB_AVFValue_Day_u32 / 10), (g_previous_Bike_TripB_AVFValue_Day_u32 % 10));
            }
        }
        else
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Av Fuel ---.- km/L", (g_previous_Bike_TripB_AVFValue_Day_u32 / 10), (g_previous_Bike_TripB_AVFValue_Day_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Av Fuel ---.- L/100km", (g_previous_Bike_TripB_AVFValue_Day_u32 / 10), (g_previous_Bike_TripB_AVFValue_Day_u32 % 10));
            }
        }
    }
    else
    {
        /* do nothing */
    }
    lv_obj_add_flag(guider_ui.Setting_Screen_trip_day_hold, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_hold_btn, Holdbtnpos[0], Holdbtnpos[1]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripB_AVFuel_Day_During(void)
{
    uint32_t fl_present_Bike_TripB_AVSValue_Day_u32 = Swc_Avereage_Speed_Get_value(1);
    uint32_t fl_present_Bike_TripB_AVFValue_Day_u32 = display_AFE(1);
    bool fl_Trip_AVS_Status_bl = Swc_Average_Speed_Get_Status();
    uint32_t AFE_Unit_u32 = 0;

    if ((fl_present_Bike_TripB_AVSValue_Day_u32 != g_previous_Bike_TripB_AVSValue_Day_u32))
    {
        g_previous_Bike_TripB_AVSValue_Day_u32 = fl_present_Bike_TripB_AVSValue_Day_u32;

        if ((g_previous_Bike_TripB_AVSValue_Day_u32 > AVEREAGE_SPEED) || (fl_Trip_AVS_Status_bl == FALSE))
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Av Speed --- km/h");
        }
        else
        {
            lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Av Speed %d km/h", (g_previous_Bike_TripB_AVSValue_Day_u32));
        }
    }
    else
    {
        /* do nothing */
    }

    if (g_Fuel_Current_Unit == Lper100km)
    {
        if ((fl_present_Bike_TripB_AVFValue_Day_u32 != 0) && (fl_present_Bike_TripB_AVFValue_Day_u32 != TC_INVALID))
        {

            fl_present_Bike_TripB_AVFValue_Day_u32 = 10000 / fl_present_Bike_TripB_AVFValue_Day_u32;
        }

        /* Limit AVF value if it exceeds max limit */
        SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&fl_present_Bike_TripB_AVFValue_Day_u32);
    }
    else
    {
        /* do nothing*/
    }

    if ((g_previous_Bike_TripB_AVFValue_Day_u32 != fl_present_Bike_TripB_AVFValue_Day_u32))
    {
        g_previous_Bike_TripB_AVFValue_Day_u32 = fl_present_Bike_TripB_AVFValue_Day_u32;

        if (TC_INVALID != g_previous_Bike_TripB_AVFValue_Day_u32)
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Av Fuel %d.%d km/L", (g_previous_Bike_TripB_AVFValue_Day_u32 / 10), (g_previous_Bike_TripB_AVFValue_Day_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Av Fuel %d.%d L/100km", (g_previous_Bike_TripB_AVFValue_Day_u32 / 10), (g_previous_Bike_TripB_AVFValue_Day_u32 % 10));
            }
        }
        else
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Av Fuel ---.- km/L", (g_previous_Bike_TripB_AVFValue_Day_u32 / 10), (g_previous_Bike_TripB_AVFValue_Day_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl2, "Av Fuel ---.- L/100km", (g_previous_Bike_TripB_AVFValue_Day_u32 / 10), (g_previous_Bike_TripB_AVFValue_Day_u32 % 10));
            }
        }
    }
    else
    {
        /* do nothing */
    }

    lv_label_set_text(guider_ui.Setting_Screen_trip_day_lbl3, "Hold        To RESET");
    set_obj_opa(guider_ui.Setting_Screen_trip_day_hold, 50);
    lv_obj_clear_flag(guider_ui.Setting_Screen_trip_day_hold, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_day_hold, Holdbtnpos[2], Holdbtnpos[3]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void TripB_Hold_Day_During(void)
{
    uint32_t fl_present_Bike_TripB_Value_Day_u32 = ODO_Get_TripOdometer(1);
    uint32_t fl_present_Bike_TripB_AVSValue_Day_u32 = Swc_Avereage_Speed_Get_value(1);
    uint32_t fl_present_Bike_TripB_AVFValue_Day_u32 = display_AFE(1);

    if (fl_present_Bike_TripB_Value_Day_u32 == ODO_INVALID_STATE)
    {
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Trip ---.- km");
    }
    else if ((g_previous_Bike_TripB_Value_Day_u32 != fl_present_Bike_TripB_Value_Day_u32))
    {
        g_previous_Bike_TripB_Value_Day_u32 = fl_present_Bike_TripB_Value_Day_u32;
        lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl3, "Trip %d.%d km", (g_previous_Bike_TripB_Value_Day_u32 / 10), (g_previous_Bike_TripB_Value_Day_u32 % 10));
    }
    else
    {
        /* do nothing */
    }

    if (g_Fuel_Current_Unit == Lper100km)
    {
        if ((fl_present_Bike_TripB_AVFValue_Day_u32 != 0) && (fl_present_Bike_TripB_AVFValue_Day_u32 != TC_INVALID))
        {

            fl_present_Bike_TripB_AVFValue_Day_u32 = 10000 / fl_present_Bike_TripB_AVFValue_Day_u32;
        }

        /* Limit AVF value if it exceeds max limit */
        SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(&fl_present_Bike_TripB_AVFValue_Day_u32);
    }
    else
    {
    }

    if ((g_previous_Bike_TripB_AVFValue_Day_u32 != fl_present_Bike_TripB_AVFValue_Day_u32))
    {
        g_previous_Bike_TripB_AVFValue_Day_u32 = fl_present_Bike_TripB_AVFValue_Day_u32;

        if (TC_INVALID != g_previous_Bike_TripB_AVFValue_Day_u32)
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Av Fuel %d.%d km/L", (g_previous_Bike_TripB_AVFValue_Day_u32 / 10), (g_previous_Bike_TripB_AVFValue_Day_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Av Fuel %d.%d L/100km", (g_previous_Bike_TripB_AVFValue_Day_u32 / 10), (g_previous_Bike_TripB_AVFValue_Day_u32 % 10));
            }
        }
        else
        {
            if (g_Fuel_Current_Unit == KmperL)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Av Fuel ---.- km/L", (g_previous_Bike_TripB_AVFValue_Day_u32 / 10), (g_previous_Bike_TripB_AVFValue_Day_u32 % 10));
            }
            else if (g_Fuel_Current_Unit == Lper100km)
            {
                lv_label_set_text_fmt(guider_ui.Setting_Screen_trip_day_lbl1, "Av Fuel ---.- L/100km", (g_previous_Bike_TripB_AVFValue_Day_u32 / 10), (g_previous_Bike_TripB_AVFValue_Day_u32 % 10));
            }
        }
    }
    else
    {
        /* do nothing */
    }

    lv_label_set_text(guider_ui.Setting_Screen_trip_day_lbl2, "Hold        To RESET");
    lv_obj_clear_flag(guider_ui.Setting_Screen_trip_day_hold, LV_OBJ_FLAG_HIDDEN);
    set_obj_opa(guider_ui.Setting_Screen_trip_day_hold, 255);
    lv_obj_set_pos(guider_ui.Setting_Screen_trip_day_hold, Holdbtnpos[4], Holdbtnpos[5]);

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_up_arr, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_trip_day_down_arr, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Brightness_Day_Auto_During(void)
{

    if (g_User_Brightness_Level_u8 == HIGH_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn1_img, &new_rb_day_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn1_img, &Grey_day_radio_active_btn_1_base);
    }
    if (g_User_Brightness_Level_u8 == AUTO_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn2_img, &_radiobtn_day_checked_20x20);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn2_img, &Black_day_radio_active_btn_2_base);
    }
    if (g_User_Brightness_Level_u8 == LOW_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn3_img, &new_rb_day_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn3_img, &Grey_day_radio_active_btn_1_base);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Brightness_Day_Low_During(void)
{

    if (g_User_Brightness_Level_u8 == AUTO_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn1_img, &new_rb_day_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn1_img, &Grey_day_radio_active_btn_1_base);
    }
    if (g_User_Brightness_Level_u8 == LOW_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn2_img, &_radiobtn_day_checked_20x20);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn2_img, &Black_day_radio_active_btn_2_base);
    }
    if (g_User_Brightness_Level_u8 == MEDIUM_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn3_img, &new_rb_day_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn3_img, &Grey_day_radio_active_btn_1_base);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}
void Brightness_Day_Med_During(void)
{

    if (g_User_Brightness_Level_u8 == LOW_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn1_img, &new_rb_day_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn1_img, &Grey_day_radio_active_btn_1_base);
    }
    if (g_User_Brightness_Level_u8 == MEDIUM_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn2_img, &_radiobtn_day_checked_20x20);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn2_img, &Black_day_radio_active_btn_2_base);
    }
    if (g_User_Brightness_Level_u8 == HIGH_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn3_img, &new_rb_day_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn3_img, &Grey_day_radio_active_btn_1_base);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Brightness_Day_High_During(void)
{

    if (g_User_Brightness_Level_u8 == MEDIUM_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn1_img, &new_rb_day_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn1_img, &Grey_day_radio_active_btn_1_base);
    }
    if (g_User_Brightness_Level_u8 == HIGH_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn2_img, &_radiobtn_day_checked_20x20);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn2_img, &Black_day_radio_active_btn_2_base);
    }
    if (g_User_Brightness_Level_u8 == AUTO_BRIGHTNESS)
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn3_img, &new_rb_day_sel_unfocus);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_brightness_sel_day_btn3_img, &Grey_day_radio_active_btn_1_base);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_brightness_down_arr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Menu_Day_Volume_During(void)
{

    if (ReadMENU_SELECTION_MUSIC() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn1_img, &new_day_toogle_unfocus_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn1_img, &new_day_toogle_unfocus_off_Btn);
    }
    if (ReadMENU_SELECTION_VOLUME() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn2_img, &new_day_toogle_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn2_img, &new_day_toogle_off_Btn);
    }
    if (ReadMENU_SELECTION_TRIPB() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn3_img, &new_day_toogle_unfocus_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn3_img, &new_day_toogle_unfocus_off_Btn);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_darr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_darr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_darr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_darr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Menu_Day_Tripb_During(void)
{

    if (ReadMENU_SELECTION_VOLUME() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn1_img, &new_day_toogle_unfocus_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn1_img, &new_day_toogle_unfocus_off_Btn);
    }
    if (ReadMENU_SELECTION_TRIPB() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn2_img, &new_day_toogle_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn2_img, &new_day_toogle_off_Btn);
    }
    if (ReadMENU_SELECTION_FUEL() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn3_img, &new_day_toogle_unfocus_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn3_img, &new_day_toogle_unfocus_off_Btn);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_darr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_darr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_darr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_darr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Menu_Day_FUEL_During(void)
{

    if (ReadMENU_SELECTION_TRIPB() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn1_img, &new_day_toogle_unfocus_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn1_img, &new_day_toogle_unfocus_off_Btn);
    }
    if (ReadMENU_SELECTION_FUEL() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn2_img, &new_day_toogle_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn2_img, &new_day_toogle_off_Btn);
    }
    if (ReadMENU_SELECTION_NAVIGATION() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn3_img, &new_day_toogle_unfocus_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn3_img, &new_day_toogle_unfocus_off_Btn);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_darr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_darr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_darr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_darr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Menu_Day_Navi_During(void)
{

    if (ReadMENU_SELECTION_FUEL() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn1_img, &new_day_toogle_unfocus_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn1_img, &new_day_toogle_unfocus_off_Btn);
    }
    if (ReadMENU_SELECTION_NAVIGATION() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn2_img, &new_day_toogle_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn2_img, &new_day_toogle_off_Btn);
    }
    if (ReadMENU_SELECTION_GI() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn3_img, &new_day_toogle_unfocus_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn3_img, &new_day_toogle_unfocus_off_Btn);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_darr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_darr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_darr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_darr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Menu_Day_GeInfo_During(void)
{

    if (ReadMENU_SELECTION_NAVIGATION() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn1_img, &new_day_toogle_unfocus_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn1_img, &new_day_toogle_unfocus_off_Btn);
    }
    if (ReadMENU_SELECTION_GI() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn2_img, &new_day_toogle_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn2_img, &new_day_toogle_off_Btn);
    }
    if (ReadMENU_SELECTION_PHONE() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn3_img, &new_day_toogle_unfocus_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn3_img, &new_day_toogle_unfocus_off_Btn);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_darr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_darr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_darr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_darr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Menu_Day_Phone_During(void)
{

    if (ReadMENU_SELECTION_GI() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn1_img, &new_day_toogle_unfocus_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn1_img, &new_day_toogle_unfocus_off_Btn);
    }
    if (ReadMENU_SELECTION_PHONE() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn2_img, &new_day_toogle_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn2_img, &new_day_toogle_off_Btn);
    }
    if (ReadMENU_SELECTION_MUSIC() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn3_img, &new_day_toogle_unfocus_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn3_img, &new_day_toogle_unfocus_off_Btn);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_darr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_darr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_darr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_darr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

uint8_t SetMENU_SELECTION_VOLUME(void)
{
    /* REQUEST NVM TO WRITE */
    NVM_Setting_Write_request = 1;

    /* TOGGLE BIT */
    HMI_TOGGLE_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_VOLUME);

    return 0;
}
uint8_t SetMENU_SELECTION_TRIPB(void)
{
    /* REQUEST NVM TO WRITE */
    NVM_Setting_Write_request = 1;

    /* TOGGLE BIT */
    HMI_TOGGLE_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_TRIPB);
    return 0;
}
uint8_t SetMENU_SELECTION_FUEL(void)
{
    /* REQUEST NVM TO WRITE */
    NVM_Setting_Write_request = 1;

    /* TOGGLE BIT */
    HMI_TOGGLE_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_FUEL);
    return 0;
}
uint8_t SetMENU_SELECTION_NAVIGATION(void)
{
    /* REQUEST NVM TO WRITE */
    NVM_Setting_Write_request = 1;

    /* TOGGLE BIT */
    HMI_TOGGLE_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_NAVIGATION);
    return 0;
}
uint8_t SetMENU_SELECTION_GI(void)
{
    /* REQUEST NVM TO WRITE */
    NVM_Setting_Write_request = 1;

    /* TOGGLE BIT */
    HMI_TOGGLE_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_GI);
    return 0;
}
uint8_t SetMENU_SELECTION_PHONE(void)
{
    /* REQUEST NVM TO WRITE */
    NVM_Setting_Write_request = 1;

    /* TOGGLE BIT */
    HMI_TOGGLE_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_PHONE);
    return 0;
}
uint8_t SetMENU_SELECTION_MUSIC(void)
{
    /* REQUEST NVM TO WRITE */
    NVM_Setting_Write_request = 1;

    /* TOGGLE BIT */
    HMI_TOGGLE_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_MUSIC);
    return 0;
}

uint8_t ReadMENU_SELECTION_VOLUME(void)
{
    return (READ_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_VOLUME));
}
uint8_t ReadMENU_SELECTION_TRIPB(void)
{
    return (READ_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_TRIPB));
}
uint8_t ReadMENU_SELECTION_FUEL(void)
{
    return (READ_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_FUEL));
}
uint8_t ReadMENU_SELECTION_NAVIGATION(void)
{
    return (READ_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_NAVIGATION));
}
uint8_t ReadMENU_SELECTION_GI(void)
{
    return (READ_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_GI));
}
uint8_t ReadMENU_SELECTION_PHONE(void)
{
    return (READ_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_PHONE));
}
uint8_t ReadMENU_SELECTION_MUSIC(void)
{
    return (READ_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_MUSIC));
}

uint8_t HMI_Get_Possible_Screen_Transition(void)
{
    uint8_t fl_HMI_Menu_Sel_Data_u8;

    g_BLE_Connectivity_Status_U8 = BLE_Get_Connection_Status();

    if (g_BLE_Connectivity_Status_U8 == BLE_CONNECTED && g_BLE_Status_u8 == BLUETOOTH_ON)
    {
        /* able to traverse all screens */
        fl_HMI_Menu_Sel_Data_u8 = g_NVM_Menu_Selection_Data_u8;
    }
    else
    {
        /* As Bluetooth is disabled,  able to go only non bluetooth related screens. */
        fl_HMI_Menu_Sel_Data_u8 = g_NVM_Menu_Selection_Data_u8 & 0x17;
    }

    /* return available screen */
    return (fl_HMI_Menu_Sel_Data_u8);
}

uint8_t JmpPrevIntermediateScreen(void)
{
    /* LOCAL VARIABLE */
    uint8_t fl_intermediateScreenOffset_U8 = (g_PrevIntermediateScreen_U32 - INTERMED_TRIPA);
    uint8_t loop = 0;
    uint8_t fl_ret_u8 = 0;
    uint8_t fl_BitPos_u8 = 0;
    uint8_t fl_Menu_Sel_Data_u8 = 0;

    /* Based on bluetooth status , getting possible screen transitions */
    fl_Menu_Sel_Data_u8 = HMI_Get_Possible_Screen_Transition();

    /* CHECK FOR THE  */
    if (fl_intermediateScreenOffset_U8 == 0)
    {
        fl_intermediateScreenOffset_U8 = MAX_MENU_SELECTION;
    }

    for (loop = fl_intermediateScreenOffset_U8; loop < 8; loop++)
    {
        if (READ_BIT(fl_Menu_Sel_Data_u8, fl_intermediateScreenOffset_U8))
        {
            SetCrntScreen(IntermediateMapTblSt[fl_intermediateScreenOffset_U8].ScreenIdx);
            fl_ret_u8 = 1;
            break;
        }
        else
        {
            fl_intermediateScreenOffset_U8++;
            if (fl_intermediateScreenOffset_U8 > MAX_MENU_SELECTION)
            {
                fl_intermediateScreenOffset_U8 = 0;
            }
        }
    }

    /* RETURN */
    return fl_ret_u8;
}

uint8_t SkipReverseIntermediateIfSelected(void)
{
    /* LOCAL VARIABLE */
    uint32_t fl_CurrentScreenIdx_U32 = GetCrntScreen();
    g_PrevScreen_U32 = fl_CurrentScreenIdx_U32;
    uint8_t fl_intermediateScreenOffset_U8 = (fl_CurrentScreenIdx_U32 - INTERMED_TRIPA);
    uint8_t loop = 0;
    uint8_t fl_ret_u8 = 0;
    uint8_t fl_BitPos_u8 = 0;
    uint8_t fl_Menu_Sel_Data_u8 = 0;

    /* Based on bluetooth status , getting possible screen transitions */
    fl_Menu_Sel_Data_u8 = HMI_Get_Possible_Screen_Transition();

    /* CHECK FOR THE  */
    if (fl_intermediateScreenOffset_U8 == 0)
    {
        fl_intermediateScreenOffset_U8 = MAX_MENU_SELECTION;
    }

    for (loop = fl_intermediateScreenOffset_U8; loop > 0; loop--)
    {
        /* CHECK FOR THE BIT POSITION VALUE */
        if (READ_BIT(fl_Menu_Sel_Data_u8, (fl_intermediateScreenOffset_U8 - 1)))
        {

            SetCrntScreen(IntermediateMapTblSt[(fl_intermediateScreenOffset_U8 - 1)].ScreenIdx);
            fl_ret_u8 = 1;
            break;
        }
        else
        {
            fl_intermediateScreenOffset_U8--;
            if (fl_intermediateScreenOffset_U8 == 0)
            {
                fl_intermediateScreenOffset_U8 = 0;
            }
        }
    }

    /* SET SCREEN INDEX TO STORE THE PREVIOUS INTERMEDIATE SCREEN */
    g_PrevIntermediateScreen_U32 = IntermediateMapTblSt[(fl_intermediateScreenOffset_U8 - 1)].ScreenIdx;

    /* RETURN */
    return fl_ret_u8;
}

uint8_t SkipIntermediateIfSelected(void)
{
    /* LOCAL VARIABLE */
    uint32_t fl_CurrentScreenIdx_U32 = GetCrntScreen();
    g_PrevScreen_U32 = fl_CurrentScreenIdx_U32;
    uint8_t fl_intermediateScreenOffset_U8 = (fl_CurrentScreenIdx_U32 - INTERMED_TRIPA);
    uint8_t loop = 0;
    uint8_t fl_ret_u8 = 0;
    uint8_t fl_Menu_Sel_Data_u8 = 0;

    /* Based on bluetooth status , getting possible screen transitions */
    fl_Menu_Sel_Data_u8 = HMI_Get_Possible_Screen_Transition();

    if (fl_intermediateScreenOffset_U8 == MENU_SELECTION_VOLUME)
    {
        return fl_ret_u8;
    }

    for (loop = fl_intermediateScreenOffset_U8; loop < 8; loop++)
    {
        if (READ_BIT(fl_Menu_Sel_Data_u8, fl_intermediateScreenOffset_U8 + 1))
        {
            SetCrntScreen(IntermediateMapTblSt[fl_intermediateScreenOffset_U8 + 1].ScreenIdx);
            fl_ret_u8 = 1;
            break;
        }
        else
        {
            fl_intermediateScreenOffset_U8++;
            if (fl_intermediateScreenOffset_U8 > MAX_MENU_SELECTION)
            {
                fl_intermediateScreenOffset_U8 = 0;
            }
        }
    }

    /* SET SCREEN INDEX TO STORE THE PREVIOUS INTERMEDIATE SCREEN */
    g_PrevIntermediateScreen_U32 = IntermediateMapTblSt[(fl_intermediateScreenOffset_U8 + 1)].ScreenIdx;

    /* RETURN */
    return fl_ret_u8;
}

void Menu_Day_Music_During(void)
{

    if (ReadMENU_SELECTION_PHONE() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn1_img, &new_day_toogle_unfocus_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn1_img, &new_day_toogle_unfocus_off_Btn);
    }
    if (ReadMENU_SELECTION_MUSIC() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn2_img, &new_day_toogle_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn2_img, &new_day_toogle_off_Btn);
    }
    if (ReadMENU_SELECTION_VOLUME() == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn3_img, &new_day_toogle_unfocus_on_Btn);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_menu_sel_day_btn3_img, &new_day_toogle_unfocus_off_Btn);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_darr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_up_darr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_darr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_menu_down_darr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Datetimeset_Day_Date_During(void)
{

    if (g_Clock_Format_Selection_Cmd == 0)
    {
        lv_img_set_src(guider_ui.Setting_Screen_data_time_day_toggl_btn, &_btn_1_29x20);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_data_time_day_toggl_btn, &_off_btn_29x20);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_up_arr_day_button_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_up_arr_day_button_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_dow_arr_day_button_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_dow_arr_day_button_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Datetimeset_Day_Time_During(void)
{

    if (g_Clock_Format_Selection_Cmd == 0)
    {
        lv_img_set_src(guider_ui.Setting_Screen_data_time_day_toggl_btn, &_btn_1_29x20);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_data_time_day_toggl_btn, &_off_btn_29x20);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_up_arr_day_button_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_up_arr_day_button_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_dow_arr_day_button_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_dow_arr_day_button_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Datetimeset_Day_24Hr_During(void)
{

    if (g_Clock_Format_Selection_Cmd == 0)
    {
        lv_img_set_src(guider_ui.Setting_Screen_data_time_day_toggl_btn, &_btn_1_29x20);
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_data_time_day_toggl_btn, &_off_btn_29x20);
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_up_arr_day_button_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_up_arr_day_button_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_dow_arr_day_button_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_data_time_dow_arr_day_button_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Timeset_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_set_night_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_hour, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_min, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_Colan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_Clock_AM, LV_OBJ_FLAG_HIDDEN);
}

void Timeset_12_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_time_12_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME SETTING");

    lv_obj_set_pos(guider_ui.Setting_Screen_time_12_toset_lbl, 127, 232);
    lv_obj_set_size(guider_ui.Setting_Screen_time_12_toset_lbl, 37, 12);
    // lv_label_set_text(guider_ui.Setting_Screen_time_12_day_sub_btn, "to SET");
}

void Timeset_12_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_time_12_day_container, LV_OBJ_FLAG_HIDDEN);
}

void Connect_day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_connect_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "CONNECTIVITY");
}

void Connect_day_exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_connect_day_container, LV_OBJ_FLAG_HIDDEN);
}

void AboutMenuEntry_Day_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "ABOUT");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_about_day_container, LV_OBJ_FLAG_HIDDEN);
}

void About_SoftverShow_Day_During(void)
{
    lv_img_set_src(guider_ui.Setting_Screen_about_side_day_img, &img_day_about_icon);
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L1, "RIDER INFO");
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L2, "SW VERSION");
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L3, "DISCLAIMER");
}
void About_Regu_Day_During(void)
{
    lv_img_set_src(guider_ui.Setting_Screen_about_side_day_img, &img_day_about_icon);
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L1, "SW VERSION");
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L2, "DISCLAIMER");
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L3, "RIDER INFO");
}

void GUI_Main_Screen_Day_Entry(void)
{
    /* Fill the Inner Circle with White Screen */
    set_obj_opa(guider_ui.screen_Circ, 255);

    /* x1000 RPM Image for Day Mode */

    /* Clock for Day Mode */

    /* Speedo for Day Mode */
    lv_img_set_src(guider_ui.screen_SC_3, &_39x69_9_39x69);
    lv_obj_set_style_img_opa(guider_ui.screen_SC_3, 255, 0);
    lv_obj_set_style_img_recolor(guider_ui.screen_SC_3, lv_color_black(), 0);

    lv_img_set_src(guider_ui.screen_SC_2, &_39x69_9_39x69);
    lv_obj_set_style_img_opa(guider_ui.screen_SC_2, 255, 0);
    lv_obj_set_style_img_recolor(guider_ui.screen_SC_2, lv_color_black(), 0);

    lv_img_set_src(guider_ui.screen_SC_1, &_39x69_1_39x69);
    lv_obj_set_style_img_opa(guider_ui.screen_SC_1, 255, 0);
    lv_obj_set_style_img_recolor(guider_ui.screen_SC_1, lv_color_black(), 0);

    /* Odometer for Day Mode */
    // lv_label_set_text_fmt(guider_ui.screen_con_odo_val, "%d", fl_ODOValue_u32);
    lv_obj_set_style_text_color(guider_ui.screen_con_odo_val, lv_color_night_orange(), 0);
    set_obj_opa_S(guider_ui.screen_con_odo_val, 0);

    /* Gear for Day Mode */

    /* Phone Information for Day Mode*/
}

void GUI_Time_Format_Night_24Hr_During(void)
{
    if (g_Clock_Format_Selection_Cmd == 0)
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_btn_img, &_radiobtn_night_Checked_20x20);
        g_RADIOBUTTON_Status = FALSE;
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_btn_img, &img_night_radio_active_btn_2_base);
        g_RADIOBUTTON_Status = TRUE;
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}
void GUI_Time_Format_Night_12Hr_During(void)
{

    if (g_Clock_Format_Selection_Cmd == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_btn_img, &_radiobtn_night_Checked_20x20);
        g_RADIOBUTTON_Status = FALSE;
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_btn_img, &img_night_radio_active_btn_2_base);
        g_RADIOBUTTON_Status = TRUE;
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_sub_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}
void GUI_Time_Format_Night_Exit(void)
{
    lv_obj_set_style_text_align(guider_ui.Setting_Screen_units_sub_lbl, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_units_sub_container, LV_OBJ_FLAG_HIDDEN);
}

void GUI_Time_Format_Day_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME FORMAT");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_units_day_sub_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_align(guider_ui.Setting_Screen_units_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);
}
void GUI_Time_Format_Day_24Hr_During(void)
{

    if (g_Clock_Format_Selection_Cmd == 0)
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_day_btn_img, &_radiobtn_day_checked_20x20);
        g_RADIOBUTTON_Status = FALSE;
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_day_btn_img, &Black_day_radio_active_btn_2_base);
        g_RADIOBUTTON_Status = TRUE;
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_night_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_night_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}
void GUI_Time_Format_Day_12Hr_During(void)
{

    if (g_Clock_Format_Selection_Cmd == 1)
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_day_btn_img, &_radiobtn_day_checked_20x20);
        g_RADIOBUTTON_Status = FALSE;
    }
    else
    {
        lv_img_set_src(guider_ui.Setting_Screen_units_check_day_btn_img, &Black_day_radio_active_btn_2_base);
        g_RADIOBUTTON_Status = TRUE;
    }

    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_night_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_units_up_arr_night_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}
void GUI_Time_Format_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_units_day_sub_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_align(guider_ui.Setting_Screen_units_day_lbl1, LV_TEXT_ALIGN_LEFT, 0);
}

void GUI_RiderInfo_Night_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "RIDER INFO");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_disc_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_disc_up_arr_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_disc_up_down_img, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_dis_night_lb1, "");
    lv_label_set_text(guider_ui.Setting_Screen_dis_night_lb2, "");
    lv_label_set_text(guider_ui.Setting_Screen_dis_night_lb3, "");
}
void GUI_RiderInfo_Night_During(void)
{
    /* Get BLE Connectin Status*/
    g_BLE_Connectivity_Status_U8 = GUI_BLE_Enable_Status();

    if (g_BLE_Connectivity_Status_U8 == BLE_CONNECTED)
    {
        HMI_UserName_info(&g_user_name_Info_ptr);

        /* Assign User Name Value to Rider Info*/

        lv_label_set_text_fmt(guider_ui.Setting_Screen_dis_night_lb2, "%c%c%c%c%c%c%c%c%c", g_user_name_Info_ptr.USER_NAME[0],
                              g_user_name_Info_ptr.USER_NAME[1],
                              g_user_name_Info_ptr.USER_NAME[2],
                              g_user_name_Info_ptr.USER_NAME[3],
                              g_user_name_Info_ptr.USER_NAME[4],
                              g_user_name_Info_ptr.USER_NAME[5],
                              g_user_name_Info_ptr.USER_NAME[6],
                              g_user_name_Info_ptr.USER_NAME[7],
                              g_user_name_Info_ptr.USER_NAME[8]);

        lv_label_set_text_fmt(guider_ui.Setting_Screen_dis_night_lb3, "%c%c%c%c%c%c%c%c%c", g_user_name_Info_ptr.USER_NAME[9],
                              g_user_name_Info_ptr.USER_NAME[10],
                              g_user_name_Info_ptr.USER_NAME[11],
                              g_user_name_Info_ptr.USER_NAME[12],
                              g_user_name_Info_ptr.USER_NAME[13],
                              g_user_name_Info_ptr.USER_NAME[14],
                              g_user_name_Info_ptr.USER_NAME[15],
                              g_user_name_Info_ptr.USER_NAME[16],
                              g_user_name_Info_ptr.USER_NAME[17]);
    }
    else
    {
        /* Do Nothing */
    }
}
void GUI_RiderInfo_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_disc_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_disc_up_arr_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_disc_up_down_img, LV_OBJ_FLAG_HIDDEN);
}

void GUI_RiderInfo_Day_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "RIDER INFO");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_disc_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_dis_day_up_arr_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_dis_day_down_arr_img, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_dis_day_lb1, "");
    lv_label_set_text(guider_ui.Setting_Screen_dis_day_lb2, "");
    lv_label_set_text(guider_ui.Setting_Screen_dis_day_lb3, "");
}
void GUI_RiderInfo_Day_During(void)
{
    /* Get BLE Connectin Status*/
    g_BLE_Connectivity_Status_U8 = GUI_BLE_Enable_Status();

    if (g_BLE_Connectivity_Status_U8 == BLE_CONNECTED)
    {
        HMI_UserName_info(&g_user_name_Info_ptr);

        /* Assign User Name Value to Rider Info*/

        lv_label_set_text_fmt(guider_ui.Setting_Screen_dis_day_lb2, "%c%c%c%c%c%c%c%c%c", g_user_name_Info_ptr.USER_NAME[0],
                              g_user_name_Info_ptr.USER_NAME[1],
                              g_user_name_Info_ptr.USER_NAME[2],
                              g_user_name_Info_ptr.USER_NAME[3],
                              g_user_name_Info_ptr.USER_NAME[4],
                              g_user_name_Info_ptr.USER_NAME[5],
                              g_user_name_Info_ptr.USER_NAME[6],
                              g_user_name_Info_ptr.USER_NAME[7],
                              g_user_name_Info_ptr.USER_NAME[8]);

        lv_label_set_text_fmt(guider_ui.Setting_Screen_dis_day_lb3, "%c%c%c%c%c%c%c%c%c", g_user_name_Info_ptr.USER_NAME[9],
                              g_user_name_Info_ptr.USER_NAME[10],
                              g_user_name_Info_ptr.USER_NAME[11],
                              g_user_name_Info_ptr.USER_NAME[12],
                              g_user_name_Info_ptr.USER_NAME[13],
                              g_user_name_Info_ptr.USER_NAME[14],
                              g_user_name_Info_ptr.USER_NAME[15],
                              g_user_name_Info_ptr.USER_NAME[16],
                              g_user_name_Info_ptr.USER_NAME[17]);
    }
    else
    {
        /* Do Nothing */
    }
}
void GUI_RiderInfo_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_setting_disc_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_dis_day_up_arr_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_dis_day_down_arr_img, LV_OBJ_FLAG_HIDDEN);
}

void GUI_Disclaimer_Details_Night_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_Setting_disclaimer_night_new, LV_OBJ_FLAG_HIDDEN);
}

void GUI_Disclaimer_Details_Day_Exit(void)
{
    lv_obj_add_flag(guider_ui.Setting_Screen_Setting_disclaimer_day_new, LV_OBJ_FLAG_HIDDEN);
}

/* New Entry Function */

void Setting_Main_Connectivity_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_main_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "SETTINGS");
    lv_label_set_text(guider_ui.Setting_Screen_main_night_L1, "ABOUT");
    lv_label_set_text(guider_ui.Setting_Screen_main_night_L2, "CONNECTIVITY");
    lv_label_set_text(guider_ui.Setting_Screen_main_night_L3, "BIKE");
    lv_img_set_src(guider_ui.Setting_Screen_main_side_night_img, &img_night_connectivity_icon);
    GUI_Clock_Entry();
}

void Setting_Main_Bike_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_main_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "SETTINGS");
    lv_label_set_text(guider_ui.Setting_Screen_main_night_L1, "CONNECTIVITY");
    lv_label_set_text(guider_ui.Setting_Screen_main_night_L2, "BIKE");
    lv_label_set_text(guider_ui.Setting_Screen_main_night_L3, "DISPLAY");
    lv_img_set_src(guider_ui.Setting_Screen_main_side_night_img, &img_night_settingss_bike_icon);
    GUI_Clock_Entry();
}

void Setting_Main_Display_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_main_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "SETTINGS");
    lv_label_set_text(guider_ui.Setting_Screen_main_night_L1, "BIKE");
    lv_label_set_text(guider_ui.Setting_Screen_main_night_L2, "DISPLAY");
    lv_label_set_text(guider_ui.Setting_Screen_main_night_L3, "ABOUT");
    lv_img_set_src(guider_ui.Setting_Screen_main_side_night_img, &img_night_settings_display_icon);
    GUI_Clock_Entry();
}

void Setting_Main_About_Night_Entry(void)
{

    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_main_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "SETTINGS");
    lv_label_set_text(guider_ui.Setting_Screen_main_night_L1, "DISPLAY");
    lv_label_set_text(guider_ui.Setting_Screen_main_night_L2, "ABOUT");
    lv_label_set_text(guider_ui.Setting_Screen_main_night_L3, "CONNECTIVITY");
    lv_img_set_src(guider_ui.Setting_Screen_main_side_night_img, &img_night_about_icon);
    GUI_Clock_Entry();
}

void Setting_Main_Color_Event_Night_During(void)
{
    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_main_up_arrow_night_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_main_up_arrow_night_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_main_down_arr_night_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_main_down_arr_night_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Setting_Main_Color_Event_Day_During(void)
{
    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_main_up_night_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_main_up_night_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_main_down_arr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_main_down_arr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Setting_Main_Connectivity_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_main_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "SETTINGS");
    lv_label_set_text(guider_ui.Setting_Screen_main_day_L1, "ABOUT");
    lv_label_set_text(guider_ui.Setting_Screen_main_day_L2, "CONNECTIVITY");
    lv_label_set_text(guider_ui.Setting_Screen_main_day_L3, "BIKE");
    lv_img_set_src(guider_ui.Setting_Screen_main_side_day_img, &img_day_connectivity_icon);
    GUI_Clock_Entry();
}
void Setting_Main_Bike_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_main_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "SETTINGS");
    lv_label_set_text(guider_ui.Setting_Screen_main_day_L1, "CONNECTIVITY");
    lv_label_set_text(guider_ui.Setting_Screen_main_day_L2, "BIKE");
    lv_label_set_text(guider_ui.Setting_Screen_main_day_L3, "DISPLAY");
    lv_img_set_src(guider_ui.Setting_Screen_main_side_day_img, &img_day_settingss_bike_icon);
    GUI_Clock_Entry();
}
void Setting_Main_Display_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_main_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "SETTINGS");
    lv_label_set_text(guider_ui.Setting_Screen_main_day_L1, "BIKE");
    lv_label_set_text(guider_ui.Setting_Screen_main_day_L2, "DISPLAY");
    lv_label_set_text(guider_ui.Setting_Screen_main_day_L3, "ABOUT");
    lv_img_set_src(guider_ui.Setting_Screen_main_side_day_img, &img_day_settings_display_icon);
    GUI_Clock_Entry();
}
void Setting_Main_About_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_main_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "SETTINGS");
    lv_label_set_text(guider_ui.Setting_Screen_main_day_L1, "DISPLAY");
    lv_label_set_text(guider_ui.Setting_Screen_main_day_L2, "ABOUT");
    lv_label_set_text(guider_ui.Setting_Screen_main_day_L3, "CONNECTIVITY");
    lv_img_set_src(guider_ui.Setting_Screen_main_side_day_img, &img_day_about_icon);
    GUI_Clock_Entry();
}

void Connect_Bluetooth_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_connect_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "CONNECTIVITY");
    lv_obj_add_flag(guider_ui.Setting_Screen_connect_sub_button_night_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_connect_switch_btn_night_img, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(guider_ui.Setting_Screen_connnect_side_night_img, &img_night_bluetooth_icon);
    lv_label_set_text(guider_ui.Setting_Screen_connect_night_L1, "BLUETOOTH");
    lv_obj_set_pos(guider_ui.Setting_Screen_connect_switch_btn_night_img, Hr24pos[0], Hr24pos[1]);
}
void Connect_Music_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_connect_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "CONNECTIVITY");

    lv_img_set_src(guider_ui.Setting_Screen_connnect_side_night_img, &img_night_music_icon);
    lv_label_set_text(guider_ui.Setting_Screen_connect_night_L1, "MUSIC");
    lv_obj_clear_flag(guider_ui.Setting_Screen_connect_sub_button_night_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_connect_switch_btn_night_img, LV_OBJ_FLAG_HIDDEN);
}

void Connect_Bluetooth_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_connect_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "CONNECTIVITY");

    lv_obj_add_flag(guider_ui.Setting_Screen_connect_sub_button_day_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.Setting_Screen_connect_switch_btn_day_img, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(guider_ui.Setting_Screen_connect_side_day_img, &img_day_bluetooth_icon);
    lv_label_set_text(guider_ui.Setting_Screen_connect_day_L1, "BLUETOOTH");
    lv_obj_set_pos(guider_ui.Setting_Screen_connect_switch_btn_day_img, Hr24pos[0], Hr24pos[1]);
}

void Connect_Music_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_connect_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "CONNECTIVITY");

    lv_img_set_src(guider_ui.Setting_Screen_connect_side_day_img, &img_day_music_icon);
    lv_label_set_text(guider_ui.Setting_Screen_connect_day_L1, "MUSIC");
    lv_obj_clear_flag(guider_ui.Setting_Screen_connect_sub_button_day_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_connect_switch_btn_day_img, LV_OBJ_FLAG_HIDDEN);
}

void Music_Artist_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_music_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MUSIC");
    lv_label_set_text(guider_ui.Setting_Screen_music_night_L1, "ALBUM");
    lv_label_set_text(guider_ui.Setting_Screen_music_night_L2, "ARTIST");
    lv_label_set_text(guider_ui.Setting_Screen_music_night_L3, "GENRE");
}

void Music_Album_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_music_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MUSIC");
    lv_label_set_text(guider_ui.Setting_Screen_music_night_L1, "GENRE");
    lv_label_set_text(guider_ui.Setting_Screen_music_night_L2, "ALBUM");
    lv_label_set_text(guider_ui.Setting_Screen_music_night_L3, "ARTIST");
}

void Music_Genre_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_music_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MUSIC");
    lv_label_set_text(guider_ui.Setting_Screen_music_night_L1, "ARTIST");
    lv_label_set_text(guider_ui.Setting_Screen_music_night_L2, "GENRE");
    lv_label_set_text(guider_ui.Setting_Screen_music_night_L3, "ALBUM");
}

void Music_Artist_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_music_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MUSIC");
    lv_label_set_text(guider_ui.Setting_Screen_music_day_L1, "ALBUM");
    lv_label_set_text(guider_ui.Setting_Screen_music_day_L2, "ARTIST");
    lv_label_set_text(guider_ui.Setting_Screen_music_day_L3, "GENRE");
}
void Music_Album_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_music_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MUSIC");
    lv_label_set_text(guider_ui.Setting_Screen_music_day_L1, "GENRE");
    lv_label_set_text(guider_ui.Setting_Screen_music_day_L2, "ALBUM");
    lv_label_set_text(guider_ui.Setting_Screen_music_day_L3, "ARTIST");
}
void Music_Genre_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_music_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MUSIC");
    lv_label_set_text(guider_ui.Setting_Screen_music_day_L1, "ARTIST");
    lv_label_set_text(guider_ui.Setting_Screen_music_day_L2, "GENRE");
    lv_label_set_text(guider_ui.Setting_Screen_music_day_L3, "ALBUM");
}

void About_Rider_Night_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "ABOUT");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_about_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(guider_ui.Setting_Screen_about_side_night_img, &img_night_about_icon);
    lv_label_set_text(guider_ui.Setting_Screen_about_night_L1, "DISCLAIMER");
    lv_label_set_text(guider_ui.Setting_Screen_about_night_L2, "RIDER INFO");
    lv_label_set_text(guider_ui.Setting_Screen_about_night_L3, "SW VERSION");
}

void About_Software_Night_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "ABOUT");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_about_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(guider_ui.Setting_Screen_about_side_night_img, &img_night_about_icon);
    lv_label_set_text(guider_ui.Setting_Screen_about_night_L1, "RIDER INFO");
    lv_label_set_text(guider_ui.Setting_Screen_about_night_L2, "SW VERSION");
    lv_label_set_text(guider_ui.Setting_Screen_about_night_L3, "DISCLAIMER");
}
void About_Disclaimer_Night_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "ABOUT");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_about_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(guider_ui.Setting_Screen_about_side_night_img, &img_night_about_icon);
    lv_label_set_text(guider_ui.Setting_Screen_about_night_L1, "SW VERSION");
    lv_label_set_text(guider_ui.Setting_Screen_about_night_L2, "DISCLAIMER");
    lv_label_set_text(guider_ui.Setting_Screen_about_night_L3, "RIDER INFO");
}

void About_Rider_Day_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "ABOUT");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_about_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(guider_ui.Setting_Screen_about_side_day_img, &img_day_about_icon);
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L1, "DISCLAIMER");
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L2, "RIDER INFO");
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L3, "SW VERSION");
}

void About_Software_Day_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "ABOUT");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_about_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(guider_ui.Setting_Screen_about_side_day_img, &img_day_about_icon);
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L1, "RIDER INFO");
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L2, "SW VERSION");
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L3, "DISCLAIMER");
}
void About_Disclaimer_Day_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "ABOUT");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_about_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(guider_ui.Setting_Screen_about_side_day_img, &img_day_about_icon);
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L1, "SW VERSION");
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L2, "DISCLAIMER");
    lv_label_set_text(guider_ui.Setting_Screen_about_day_L3, "RIDER INFO");
}

void Disclaimer_Night_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DISCLAIMER");
    lv_obj_clear_flag(guider_ui.Setting_Screen_Setting_disclaimer_night_new, LV_OBJ_FLAG_HIDDEN);
}

void Disclaimer_Day_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DISCLAIMER");
    lv_obj_clear_flag(guider_ui.Setting_Screen_Setting_disclaimer_day_new, LV_OBJ_FLAG_HIDDEN);
}

void Unit_Sub_Km_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_units_sub_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "FUEL CONS.");

    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DISTANCE");
    lv_label_set_text(guider_ui.Setting_Screen_units_sub_lbl, "KILOMETERS");
    lv_obj_set_pos(guider_ui.Setting_Screen_units_check_btn_img, disrbpos[0], disrbpos[1]);
    lv_obj_add_flag(guider_ui.Setting_Screen_units_sub_up_arr_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_units_sub_down_arr_img, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(guider_ui.Setting_Screen_units_check_btn_img, &_radiobtn_night_Checked_20x20);
}
void Unit_Sub_fuel_km_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_units_sub_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "FUEL CONS.");
    lv_label_set_text(guider_ui.Setting_Screen_units_sub_lbl, "km/L");
    lv_obj_set_pos(guider_ui.Setting_Screen_units_check_btn_img, disrbpos[0], disrbpos[1]);
}
void Unit_Sub_fuel_L100_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_units_sub_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "FUEL CONS.");
    lv_label_set_text(guider_ui.Setting_Screen_units_sub_lbl, "L/100km");
    lv_obj_set_pos(guider_ui.Setting_Screen_units_check_btn_img, disrbpos[0], disrbpos[1]);
}

void Unit_Sub_Km_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_units_day_sub_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "FUEL CONS.");

    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DISTANCE");
    lv_label_set_text(guider_ui.Setting_Screen_units_day_lbl1, "KILOMETERS");
    lv_obj_set_pos(guider_ui.Setting_Screen_units_check_day_btn_img, disrbpos[0], disrbpos[1]);
    lv_obj_add_flag(guider_ui.Setting_Screen_units_up_arr_day_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_units_up_arr_night_img, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(guider_ui.Setting_Screen_units_check_day_btn_img, &_radiobtn_day_checked_20x20);
}
void Unit_Sub_fuel_km_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_units_day_sub_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "FUEL CONS.");
    lv_label_set_text(guider_ui.Setting_Screen_units_day_lbl1, "km/L");
    lv_obj_set_pos(guider_ui.Setting_Screen_units_check_day_btn_img, disrbpos[0], disrbpos[1]);
}
void Unit_Sub_fuel_L100_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_units_day_sub_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "FUEL CONS.");
    lv_obj_set_pos(guider_ui.Setting_Screen_units_check_day_btn_img, disrbpos[0], disrbpos[1]);
    lv_label_set_text(guider_ui.Setting_Screen_units_day_lbl1, "L/100km");
}

void BikeMenu_Night_1_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_bike_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BIKE");
    lv_img_set_src(guider_ui.Setting_Screen_bike_side_night_img, &img_night_trip_icon);
    lv_label_set_text(guider_ui.Setting_Screen_bike_night_L1, "BATTERY");
    lv_label_set_text(guider_ui.Setting_Screen_bike_night_L2, "TRIP A");
    lv_label_set_text(guider_ui.Setting_Screen_bike_night_L3, "TRIP B");
}
void BikeMenu_Night_2_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_bike_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BIKE");
    lv_img_set_src(guider_ui.Setting_Screen_bike_side_night_img, &img_night_trip_icon);
    lv_label_set_text(guider_ui.Setting_Screen_bike_night_L1, "TRIP A");
    lv_label_set_text(guider_ui.Setting_Screen_bike_night_L2, "TRIP B");
    lv_label_set_text(guider_ui.Setting_Screen_bike_night_L3, "BATTERY");
}
void BikeMenu_Night_3_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_bike_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BIKE");
    lv_img_set_src(guider_ui.Setting_Screen_bike_side_night_img, &img_night_battery_icon);
    lv_label_set_text(guider_ui.Setting_Screen_bike_night_L1, "TRIP B");
    lv_label_set_text(guider_ui.Setting_Screen_bike_night_L2, "BATTERY");
    lv_label_set_text(guider_ui.Setting_Screen_bike_night_L3, "TRIP A");
}

void BikeMenu_Day_1_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_bike_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BIKE");
    lv_img_set_src(guider_ui.Setting_Screen_bike_side_day_img, &img_day_trip_icon);
    lv_label_set_text(guider_ui.Setting_Screen_bike_day_L1, "BATTERY");
    lv_label_set_text(guider_ui.Setting_Screen_bike_day_L2, "TRIP A");
    lv_label_set_text(guider_ui.Setting_Screen_bike_day_L3, "TRIP B");
}
void BikeMenu_Day_2_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_bike_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BIKE");
    lv_img_set_src(guider_ui.Setting_Screen_bike_side_day_img, &img_day_trip_icon);
    lv_label_set_text(guider_ui.Setting_Screen_bike_day_L1, "TRIP A");
    lv_label_set_text(guider_ui.Setting_Screen_bike_day_L2, "TRIP B");
    lv_label_set_text(guider_ui.Setting_Screen_bike_day_L3, "BATTERY");
}
void BikeMenu_Day_3_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_bike_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BIKE");
    lv_img_set_src(guider_ui.Setting_Screen_bike_side_day_img, &img_day_battery_icon);
    lv_label_set_text(guider_ui.Setting_Screen_bike_day_L1, "TRIP B");
    lv_label_set_text(guider_ui.Setting_Screen_bike_day_L2, "BATTERY");
    lv_label_set_text(guider_ui.Setting_Screen_bike_day_L3, "TRIP A");
}

void Display_Brightness_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_display_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DISPLAY");
    lv_obj_set_size(guider_ui.Setting_Screen_display_side_night_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(guider_ui.Setting_Screen_display_side_night_img, 16, 142);
    lv_img_set_src(guider_ui.Setting_Screen_display_side_night_img, &img_night_settings_display_brightness_icon);
    lv_label_set_text(guider_ui.Setting_Screen_display_night_L1, "UNITS");
    lv_label_set_text(guider_ui.Setting_Screen_display_night_L2, "BRIGHTNESS");
    lv_label_set_text(guider_ui.Setting_Screen_display_night_L3, "MENU");
}
void Display_Menu_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_display_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DISPLAY");
    lv_obj_set_pos(guider_ui.Setting_Screen_display_side_night_img, 16, 142);
    lv_obj_set_size(guider_ui.Setting_Screen_display_side_night_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_img_set_src(guider_ui.Setting_Screen_display_side_night_img, &img_night_shortcut_bar_display_menu_icon);
    lv_label_set_text(guider_ui.Setting_Screen_display_night_L1, "BRIGHTNESS");
    lv_label_set_text(guider_ui.Setting_Screen_display_night_L2, "MENU");
    lv_label_set_text(guider_ui.Setting_Screen_display_night_L3, "DATE AND TIME");
}
void Display_DateandTime_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_display_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DISPLAY");
    lv_obj_set_pos(guider_ui.Setting_Screen_display_side_night_img, 16, 142);
    lv_obj_set_size(guider_ui.Setting_Screen_display_side_night_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_img_set_src(guider_ui.Setting_Screen_display_side_night_img, &img_night_date_and_time_icon);
    lv_label_set_text(guider_ui.Setting_Screen_display_night_L1, "MENU");
    lv_label_set_text(guider_ui.Setting_Screen_display_night_L2, "DATE AND TIME");
    lv_label_set_text(guider_ui.Setting_Screen_display_night_L3, "UNITS");
}
void Display_Unit_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_display_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DISPLAY");
    lv_obj_set_pos(guider_ui.Setting_Screen_display_side_night_img, 15, 141);
    lv_obj_set_size(guider_ui.Setting_Screen_display_side_night_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_img_set_src(guider_ui.Setting_Screen_display_side_night_img, &setting_unit_icon_night_42x42);
    lv_label_set_text(guider_ui.Setting_Screen_display_night_L1, "DATE AND TIME");
    lv_label_set_text(guider_ui.Setting_Screen_display_night_L2, "UNITS");
    lv_label_set_text(guider_ui.Setting_Screen_display_night_L3, "BRIGHTNESS");
}

void Display_Brightness_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_display_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DISPLAY");
    lv_obj_set_pos(guider_ui.Setting_Screen_display_side_day_img, 16, 142);
    lv_obj_set_size(guider_ui.Setting_Screen_display_side_day_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_img_set_src(guider_ui.Setting_Screen_display_side_day_img, &img_day_settings_display_brightness_icon);
    lv_label_set_text(guider_ui.Setting_Screen_display_day_L1, "UNITS");
    lv_label_set_text(guider_ui.Setting_Screen_display_day_L2, "BRIGHTNESS");
    lv_label_set_text(guider_ui.Setting_Screen_display_day_L3, "MENU");
}
void Display_Menu_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_display_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DISPLAY");
    lv_obj_set_pos(guider_ui.Setting_Screen_display_side_day_img, 16, 142);
    lv_obj_set_size(guider_ui.Setting_Screen_display_side_day_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_img_set_src(guider_ui.Setting_Screen_display_side_day_img, &img_day_shortcut_bar_display_menu_icon);
    lv_label_set_text(guider_ui.Setting_Screen_display_day_L1, "BRIGHTNESS");
    lv_label_set_text(guider_ui.Setting_Screen_display_day_L2, "MENU");
    lv_label_set_text(guider_ui.Setting_Screen_display_day_L3, "DATE AND TIME");
}
void Display_DateandTime_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_display_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DISPLAY");
    lv_obj_set_pos(guider_ui.Setting_Screen_display_side_day_img, 16, 142);
    lv_obj_set_size(guider_ui.Setting_Screen_display_side_day_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_img_set_src(guider_ui.Setting_Screen_display_side_day_img, &img_day_date_and_time_icon);
    lv_label_set_text(guider_ui.Setting_Screen_display_day_L1, "MENU");
    lv_label_set_text(guider_ui.Setting_Screen_display_day_L2, "DATE AND TIME");
    lv_label_set_text(guider_ui.Setting_Screen_display_day_L3, "UNITS");
}
void Display_Unit_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_display_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DISPLAY");
    lv_obj_set_pos(guider_ui.Setting_Screen_display_side_day_img, 15, 141);
    lv_obj_set_size(guider_ui.Setting_Screen_display_side_day_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_img_set_src(guider_ui.Setting_Screen_display_side_day_img, &setting_unit_icon_day_42x42);
    lv_label_set_text(guider_ui.Setting_Screen_display_day_L1, "DATE AND TIME");
    lv_label_set_text(guider_ui.Setting_Screen_display_day_L2, "UNITS");
    lv_label_set_text(guider_ui.Setting_Screen_display_day_L3, "BRIGHTNESS");
}

void Brightness_Low_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_brightness_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BRIGHTNESS");

    lv_label_set_text(guider_ui.Setting_Screen_brightness_night_L1, "AUTO");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_night_L2, "LOW");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_night_L3, "MEDIUM");
}
void Brightness_High_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_brightness_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BRIGHTNESS");

    lv_label_set_text(guider_ui.Setting_Screen_brightness_night_L1, "MEDIUM");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_night_L2, "HIGH");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_night_L3, "AUTO");
}
void Brightness_Med_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_brightness_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BRIGHTNESS");

    lv_label_set_text(guider_ui.Setting_Screen_brightness_night_L1, "LOW");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_night_L2, "MEDIUM");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_night_L3, "HIGH");
}
void Brightness_Auto_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_brightness_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BRIGHTNESS");

    lv_label_set_text(guider_ui.Setting_Screen_brightness_night_L1, "HIGH");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_night_L2, "AUTO");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_night_L3, "LOW");
}

void Brightness_Low_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_brightness_day_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BRIGHTNESS");

    lv_label_set_text(guider_ui.Setting_Screen_brightness_day_L1, "AUTO");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_day_L2, "LOW");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_day_L3, "MEDIUM");
}
void Brightness_High_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_brightness_day_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BRIGHTNESS");

    lv_label_set_text(guider_ui.Setting_Screen_brightness_day_L1, "MEDIUM");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_day_L2, "HIGH");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_day_L3, "AUTO");
}
void Brightness_Med_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_brightness_day_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BRIGHTNESS");

    lv_label_set_text(guider_ui.Setting_Screen_brightness_day_L1, "LOW");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_day_L2, "MEDIUM");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_day_L3, "HIGH");
}
void Brightness_Auto_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_brightness_day_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "BRIGHTNESS");

    lv_label_set_text(guider_ui.Setting_Screen_brightness_day_L1, "HIGH");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_day_L2, "AUTO");
    lv_label_set_text(guider_ui.Setting_Screen_brightness_day_L3, "LOW");
}

void Unit_Distance_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_unit_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "UNIT");
    lv_img_set_src(guider_ui.Setting_Screen_unit_night_icon_img, &img_night_display_units_distance_icon);
    lv_label_set_text(guider_ui.Setting_Screen_unit_night_Lb1, "DISTANCE");
}
void Unit_Fuel_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_unit_night_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "UNIT");
    lv_img_set_src(guider_ui.Setting_Screen_unit_night_icon_img, &img_night_display_units_fuel_icon);
    lv_label_set_text(guider_ui.Setting_Screen_unit_night_Lb1, "FUEL CONS.");
}

void Unit_Distance_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_unit_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "UNIT");
    lv_img_set_src(guider_ui.Setting_Screen_unit_day_icon_img, &img_day_display_units_distance_icon);
    lv_label_set_text(guider_ui.Setting_Screen_unit_day_lb1, "DISTANCE");
}
void Unit_Fuel_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_unit_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "UNIT");
    lv_img_set_src(guider_ui.Setting_Screen_unit_day_icon_img, &img_day_display_units_fuel_icon);

    lv_label_set_text(guider_ui.Setting_Screen_unit_day_lb1, "FUEL CONS.");
}

void Menu_TripB_Night_Entry(void)
{
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_down_arr_day_img, 110, 245);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_down_arr_day_img, 20, 11);
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_up_arr_day_img, 110, 68);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_up_arr_day_img, 20, 11);
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");
    lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
    lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);

    lv_obj_set_pos(guider_ui.Setting_Screen_connect_switch_btn_day_img, Hr24pos[0], Hr24pos[1]);
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L1, "VOLUME");
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L2, "TRIP B");
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L3, "FUEL");
}

void Menu_Fuel_Night_Entry(void)
{
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_down_arr_day_img, 110, 245);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_down_arr_day_img, 20, 11);
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_up_arr_day_img, 110, 68);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_up_arr_day_img, 20, 11);
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");
    lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
    lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);

    lv_obj_set_pos(guider_ui.Setting_Screen_connect_switch_btn_day_img, Hr24pos[0], Hr24pos[1]);
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L1, "TRIP B");
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L2, "FUEL");
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L3, "NAVIGATION");
}
void Menu_Navi_Night_Entry(void)
{
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_down_arr_day_img, 110, 245);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_down_arr_day_img, 20, 11);
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_up_arr_day_img, 110, 68);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_up_arr_day_img, 20, 11);
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");
    lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
    lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);

    lv_obj_set_pos(guider_ui.Setting_Screen_connect_switch_btn_day_img, Hr24pos[0], Hr24pos[1]);
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L1, "FUEL");
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L2, "NAVIGATION");
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L3, "GENERAL INFO");
}

void Menu_GeInfo_Night_Entry(void)
{
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_down_arr_day_img, 110, 245);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_down_arr_day_img, 20, 11);
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_up_arr_day_img, 110, 68);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_up_arr_day_img, 20, 11);
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");
    lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
    lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);

    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L1, "NAVIGATION");
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L2, "GENERAL INFO");
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L3, "PHONE");
}
void Menu_Phone_Night_Entry(void)
{
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_down_arr_day_img, 110, 245);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_down_arr_day_img, 20, 11);
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_up_arr_day_img, 110, 68);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_up_arr_day_img, 20, 11);
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");
    lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
    lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);

    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L1, "GENERAL INFO");
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L2, "PHONE");
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L3, "MUSIC");
}
void Menu_Music_Night_Entry(void)
{
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_down_arr_day_img, 110, 245);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_down_arr_day_img, 20, 11);
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_up_arr_day_img, 110, 68);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_up_arr_day_img, 20, 11);
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");
    lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
    lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);

    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L1, "PHONE");
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L2, "MUSIC");
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L3, "VOLUME");
}
void Menu_Volume_Night_Entry(void)
{
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_down_arr_day_img, 110, 245);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_down_arr_day_img, 20, 11);
    lv_obj_set_pos(guider_ui.Setting_Screen_menu_up_arr_day_img, 110, 68);
    lv_obj_set_size(guider_ui.Setting_Screen_menu_up_arr_day_img, 20, 11);
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_night_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");
    lv_img_set_src(guider_ui.Setting_Screen_menu_down_arr_day_img, &_Setting_Drow_Arrow_20x11);
    lv_img_set_src(guider_ui.Setting_Screen_menu_up_arr_day_img, &_Setting_Up_Arrow_20x11);

    lv_obj_set_pos(guider_ui.Setting_Screen_connect_switch_btn_day_img, Hr24pos[0], Hr24pos[1]);
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L1, "MUSIC");
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L2, "VOLUME");
    lv_label_set_text(guider_ui.Setting_Screen_menu_night_L3, "TRIP B");
}

void Menu_TripB_Day_Entry(void)
{

    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_day_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");

    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L1, "VOLUME");
    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L2, "TRIP B");
    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L3, "FUEL");
}
void Menu_Fuel_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_day_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");

    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L1, "TRIP B");
    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L2, "FUEL");
    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L3, "NAVIGATION");
}
void Menu_Navi_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_day_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");

    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L1, "FUEL");
    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L2, "NAVIGATION");
    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L3, "GENERAL INFO");
}
void Menu_GeInfo_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_day_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");

    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L1, "NAVIGATION");
    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L2, "GENERAL INFO");
    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L3, "PHONE");
}
void Menu_Phone_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_day_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");

    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L1, "GENERAL INFO");
    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L2, "PHONE");
    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L3, "MUSIC");
}
void Menu_Music_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_day_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");

    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L1, "PHONE");
    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L2, "MUSIC");
    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L3, "VOLUME");
}
void Menu_Volume_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_menu_day_contain, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "MENU");

    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L1, "MUSIC");
    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L2, "VOLUME");
    lv_label_set_text(guider_ui.Setting_Screen_menu_day_L3, "TRIP B");
}

void Datetimeset_Date_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_seting_date_time_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE AND TIME");

    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_nigh_LB1, "TIME FORMAT");
    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_nigh_LB2, "DATE SETTING");
    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_nigh_LB3, "TIME SETTING");
    lv_obj_clear_flag(guider_ui.Setting_Screen_data_time_night_sub_button_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_data_time_night_toggl_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guider_ui.Setting_Screen_data_time_night_toggl_btn, Hr24pos[0], Hr24pos[2]);

    lv_obj_add_flag(guider_ui.Setting_Screen_seting_date_time_day_container, LV_OBJ_FLAG_HIDDEN);
}
void Datetimeset_Time_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_seting_date_time_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE AND TIME");
    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_nigh_LB1, "DATE SETTING");
    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_nigh_LB2, "TIME SETTING");
    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_nigh_LB3, "TIME FORMAT");
    lv_obj_clear_flag(guider_ui.Setting_Screen_data_time_night_sub_button_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_data_time_night_toggl_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guider_ui.Setting_Screen_data_time_night_toggl_btn, Hr24pos[0], Hr24pos[3]);

    lv_obj_add_flag(guider_ui.Setting_Screen_seting_date_time_day_container, LV_OBJ_FLAG_HIDDEN);
}
void Datetimeset_24Hr_Night_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_seting_date_time_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE AND TIME");

    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_nigh_LB1, "TIME SETTING");
    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_nigh_LB2, "TIME FORMAT");
    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_nigh_LB3, "DATE SETTING");
    lv_obj_clear_flag(guider_ui.Setting_Screen_data_time_night_sub_button_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.Setting_Screen_data_time_night_toggl_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guider_ui.Setting_Screen_data_time_night_toggl_btn, Hr24pos[0], Hr24pos[1]);
}

void Datetimeset_Date_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_seting_date_time_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE AND TIME");

    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_day_LB1, "TIME FORMAT");
    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_day_LB2, "DATE SETTING");
    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_day_LB3, "TIME SETTING");
    lv_obj_add_flag(guider_ui.Setting_Screen_data_time_day_toggl_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guider_ui.Setting_Screen_data_time_day_toggl_btn, Hr24pos[0], Hr24pos[2]);
}
void Datetimeset_Time_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_seting_date_time_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE AND TIME");

    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_day_LB1, "DATE SETTING");
    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_day_LB2, "TIME SETTING");
    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_day_LB3, "TIME FORMAT");
    lv_obj_add_flag(guider_ui.Setting_Screen_data_time_day_toggl_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(guider_ui.Setting_Screen_data_time_day_toggl_btn, Hr24pos[0], Hr24pos[3]);
}
void Datetimeset_24Hr_Day_Entry(void)
{
    lv_obj_clear_flag(guider_ui.Setting_Screen_seting_date_time_day_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "DATE AND TIME");

    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_day_LB1, "TIME SETTING");
    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_day_LB2, "TIME FORMAT");
    lv_label_set_text(guider_ui.Setting_Screen_data_time_do_arr_day_LB3, "DATE SETTING");
    lv_obj_add_flag(guider_ui.Setting_Screen_data_time_day_toggl_btn, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_pos(guider_ui.Setting_Screen_data_time_day_toggl_btn, Hr24pos[0], Hr24pos[1]);
}

void TimeFormat_24Hr_Night_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME FORMAT");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_units_sub_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_align(guider_ui.Setting_Screen_units_sub_lbl, LV_TEXT_ALIGN_CENTER, 0);

    lv_label_set_text(guider_ui.Setting_Screen_units_sub_lbl, "24 HOUR");
    lv_obj_set_pos(guider_ui.Setting_Screen_units_check_btn_img, disrbpos[0], disrbpos[1]);
}

void TimeFormat_12Hr_Night_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME FORMAT");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_units_sub_container, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_align(guider_ui.Setting_Screen_units_sub_lbl, LV_TEXT_ALIGN_CENTER, 0);

    lv_label_set_text(guider_ui.Setting_Screen_units_sub_lbl, "12 HOUR");
    lv_obj_set_pos(guider_ui.Setting_Screen_units_check_btn_img, disrbpos[0], disrbpos[1]);
}
void TimeFormat_24Hr_Day_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME FORMAT");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_units_day_sub_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_align(guider_ui.Setting_Screen_units_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(guider_ui.Setting_Screen_units_day_lbl1, "24 HOUR");
    lv_obj_set_pos(guider_ui.Setting_Screen_units_check_day_btn_img, disrbpos[0], disrbpos[1]);
}
void TimeFormat_12_Hr_Day_Entry(void)
{
    lv_label_set_text(guider_ui.Setting_Screen_display_label, "TIME FORMAT");
    lv_obj_clear_flag(guider_ui.Setting_Screen_setting_units_day_sub_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_align(guider_ui.Setting_Screen_units_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(guider_ui.Setting_Screen_units_day_lbl1, "12 HOUR");
    lv_obj_set_pos(guider_ui.Setting_Screen_units_check_day_btn_img, disrbpos[0], disrbpos[1]);
}

uint8_t SettingArrow_UpButton_Pressed(void)
{
    g_SettingUpArrowPressed_U8 = Pressed_State;

    return 0;
}

uint8_t SettingArrow_DownButton_Pressed(void)
{
    g_SettingDownArrowPressed_U8 = Pressed_State;

    return 0;
}

void About_Night_During(void)
{
    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_about_up_arr_night_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_about_up_arr_night_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_about_down_arr_night_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_about_down_arr_night_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void About_Day_During(void)
{
    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_about_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_about_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_about_down_arr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_about_down_arr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void BikeMenu_Night_During(void)
{
    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_bike_up_arrow_night_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_bike_up_arrow_night_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_bike_down_arrow_night_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_bike_down_arrow_night_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void BikeMenu_Day_During(void)
{
    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_bike_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_bike_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_bike_down_arr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_bike_down_arr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Display_Night_During(void)
{
    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_display_up_arr_night_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_display_up_arr_night_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_display_down_arr_night_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_display_down_arr_night_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Display_Day_During(void)
{
    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_display_up_arr_day_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_display_up_arr_day_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_display_down_arr_day_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_display_down_arr_day_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

void Display_Unit_Night_During(void)
{
    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_unit_night_up_arr_img, &night_up_btn_pressed_);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_unit_night_up_arr_img, &_Setting_Up_Arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_unit_night_down_arr_img, &night_down_btn_pressed_);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_unit_night_down_arr_img, &_Setting_Drow_Arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}
void Display_Unit_Day_During(void)
{
    /* Chang Color For Trip If It is Pressed */
    switch (g_SettingUpArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_unit_day_up_arr_img, &day_up_btn_pressed);
        g_SettingUpArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_unit_day_up_arr_img, &_day_up_arrow_20x11);
        g_SettingUpArrowPressed_U8 = 0;
        break;
    default:
        break;
    }

    /* Chang Color For Trip Btn If It is Pressed */
    switch (g_SettingDownArrowPressed_U8)
    {
    case Pressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_unit_day_night_arr_img, &day_down_btn_pressed);
        g_SettingDownArrowPressed_U8 = 2;
        break;
    case UnPressed_State:
        lv_img_set_src(guider_ui.Setting_Screen_unit_day_night_arr_img, &_day_down_arrow_20x11);
        g_SettingDownArrowPressed_U8 = 0;
        break;
    default:
        break;
    }
}

/*********************************************************************************************************************************/
