/* @file FILE NAME */
#ifndef HMI_SETTING_SCREEN_H
#define HMI_SETTING_SCREEN_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Palani kumar ( palanikumar@niyatainfotech.com)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : HMI_Setting_Screen.h
*  Version                         : v1.0.0
*  Micros supported                : 
*  Compilers supported             : 
*  Platforms supported             :                 
*  Description                     : This header file contains the declarations of setting screen
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/

#include "lvgl_app.h"
#include "gui_guider.h"
/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
/**
* @brief This macro is used to get handle bar button status
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef is used to define 
 * @param    
 * @return
 **/


/*
 * @brief    This typedef enum is used to define different state for setting screen
 * @param    
 * @param
 **/
typedef enum
{
    HMI_PST_SETTING_MAIN_SCREEN = 0,        /* Setting screen */
    HMI_PST_CONNECTIVITY_MAIN_SCREEN,
    HMI_PST_BIKE_MAIN_SCREEN,
    HMI_PST_DISPLAY_SETTING_MAIN_SCREEN,
    HMI_PST_ABOUT_MAIN_SCREEN,
    HMI_PST_MUSIC_SETTING_SCREEN,
    HMI_PST_SETTING_BIKE_TRIPA_SCREEN,
    HMI_PST_SETTING_BIKE_TRIPB_SCREEN,
    HMI_PST_BIKE_BATTERY_STATUS_SCREEN,
    HMI_DISPLAY_BRIGHTNESS_SETTING,
    HMI_DISPLAY_MENU_SETTING,
    HMI_DISPLAY_DATE_CLOCK_SETTING,
    HMI_DISPLAY_UNITS_SETTING,
    HMI_DISPLAY_SET_DATE_SCREEN,
    HMI_DISPLAY_SET_TIME_SCREEN,
    HMI_DISPLAY_DISTANCE_SETTING,
    HMI_DISPLAY_FUEL_CONSUMPTION_SETTING,
    HMI_DISPLAY_SOFTWARE_VERSION_SCREEN,
    HMI_DISPLAY_MUSIC_SELECTION_SCREEN
}HMI_SETTING_PST_SCREENS_EN;


typedef enum
{
    MiperL = 0,
    Lper100km,
    KmperL
}HMI_SETTING_PST_EN;

typedef enum
{
    ARTIST = 1,
    GENRE,
    ALBUM
}HMI_SETTING_MUSIC_SELECTION_EN;

typedef enum
{
    Km = 0,
    Miles
}HMI_SETTING_PST_UNITS_EN;



typedef enum
{
    Bluetooth = 0,
    Music
}HMI_BLE_SETTING_PST_UNITS_EN;

typedef enum
{
    BLUETOOTH_ON = 1,
    BLUETOOTH_OFF,
}HMI_BLE_SET_PST_EN;

typedef enum
{
    MENU_ON = 0,
    MENU_OFF
}HMI_MENU_SET_PST_EN;

typedef enum
{
    MUSIC_ON = 0,
    MUSIC_OFF
}HMI_MUSIC_SET_PST_EN;

typedef enum
{
    RADIO_BTN_ON = 0,
    RADIO_BTN_OFF
}HMI_RADIO_SET_PST_EN;

typedef enum
{
	CLOCK_24HR_FORMAT = 0,
	CLOCK_12HR_FORMAT
}CLOCK_FORMAT_SELECTION_EN;



typedef enum
{
    MENU_SELECTION_TRIPA = 0,
	MENU_SELECTION_TRIPB,
	MENU_SELECTION_FUEL,
	MENU_SELECTION_NAVIGATION,
	MENU_SELECTION_GI,
	MENU_SELECTION_PHONE,
	MENU_SELECTION_MUSIC,
	MENU_SELECTION_VOLUME,
	MAX_MENU_SELECTION
}MENU_Selection_Type_En;


#define SET_BIT(SRC_VALUE, BIT_TO_SET)			(SRC_VALUE |= (1 << BIT_TO_SET))
#define CLR_BIT(SRC_VALUE, BIT_TO_CLR)			(SRC_VALUE &= !(1 << BIT_TO_CLR))
#define HMI_TOGGLE_BIT(SRC_VALUE, BIT_TO_TOGGLE) (SRC_VALUE ^= (1 << BIT_TO_TOGGLE))
#define READ_BIT(SRC_VALUE, BIT_TO_READ)		((SRC_VALUE >> BIT_TO_READ) & 0x01)


/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/
void HMI_Setting_Screen_Warm_Init(void);

void HMI_Setting_Screen_Cold_Init(void);


void GUI_Setting_mainscr_night_entry(void);
void GUI_Setting_mainscr_night_exit(void);
void SettingConnectScrnEntry(void);

/*
* @brief    This API is used to load setting screen
* @param    NONE
* @return   NONE
* @invocation by LVGL MAIN TASK
*/
void HMI_Load_Setting_Screen(void);

void Idle_Setting_Screen(lv_ui *ui);
uint8_t Distance_fn(void);
uint8_t Fuel_Consumption_fn(void);
uint8_t GUI_am_pm_Setting(void);
uint8_t GUI_Get_Time_Format(void);
uint8_t GUI_BLE_Enable_Status(void);
uint8_t HMI_Setting_Screen_Get_Brightness_Level(void);
uint8_t HMI_Menu_Setting_Get_NVM_Data(void);
void GUI_Day_Mode(void);
uint8_t get_Counter(void);

void GUI_Leap_year_check_And_Month_end_St(void);
void HMI_CLK_NVM_check(void);
void Setting_Screen_During_Fn(void);

void GUI_NightEntry_Base(void);

void Display_Date_Setting_Night_During(void);
void Display_Month_Setting_Night_During(void);
void Display_Year_Setting_Night_During(void);

void Display_Date_Setting_Day_During(void);
void Display_Month_Setting_Day_During(void);
void Display_Year_Setting_Day_During(void);

void Display_hr_Time_Setting_Night_During(void);
void Display_min_Time_Setting_Night_During(void);
void Display_ampm_Time_Setting_Night_During(void);



uint8_t GUI_Up_Button_Date_Setting(void);
uint8_t GUI_Up_Button_Month_Setting(void);
uint8_t GUI_Up_Button_year_Setting(void);


uint8_t GUI_Down_button_Date_Setting(void);
uint8_t  GUI_Down_Button_Month_setting(void);
uint8_t GUI_Down_Button_Year_setting(void);


uint8_t GUI_UPDown_Button_Merdian_Set_time(void);
uint8_t GUI_Down_Button_Min_Set_time(void);
uint8_t GUI_Down_Button_Hr_Set_time(void);

uint8_t GUI_Up_Button_Min_Set_time(void);
uint8_t GUI_Up_Button_Hr_Set_time(void);


uint8_t RTC_Set_Time_Hour_Min(void);
uint8_t RTC_Set_Date_Month_year(void);


uint8_t Get_Date_variable(void);
uint8_t Get_Time_variable(void);

void Display_Date_Month_Yaer_Setting_Day_During(void);
void Display_Time_Setting_Day_During(void);
uint8_t GUI_Check_Time_Format(void);

uint8_t GUI_Check_24Hr_Time_Format(void);

uint8_t GUI_Check_12Hr_Time_Format(void);

uint8_t GUI_UP_Button_Merdian_Set_time(void);
uint8_t GUI_Down_Button_Merdian_Set_time(void);

void HMI_Change_Valid_Day_based_On_Month_Year_Setting(void);

bool Is_Leap_year(void);

bool HMI_Setting_Screen_Is_Exit_Cond_Met(void);
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : v1.0.0                          
    REVISION DATE        : 06/09/2022        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)      
    DESCRIPTION          : Initial version                                         
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! FILE NAME */
