/* @file FILE NAME */
#ifndef HMI_MAIN_SCREEN_H
#define HMI_MAIN_SCREEN_H

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
*  File name                       : HMI_Main_Screen.h
*  Version                         : v1.0.0
*  Micros supported                : 
*  Compilers supported             : 
*  Platforms supported             :                 
*  Description                     : This header file contains the declarations of HMI main screen
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/
/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/

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
* @brief This macro is used to define number of handle bar button
* @Unit:  uint8_t 
* @Resolution: 1
* @Range: 1 to 4
* @Applicability:  
* @Note:  
*/

#define TOTAL_BUTTON                4u
/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef is used to define 
 * @param    
 * @return
 **/


/*
 * @brief    This typedef enum is used to define 
 * @param    
 * @param
 **/
typedef enum
{
    HMI_PST_HOME_MAIN_SCREEN  = 0,
    HMI_PST_TRIP_A_MAIN_SCREEN ,                   
    HMI_PST_TRIP_A_INFO_SCREEN_1,
    HMI_PST_TRIP_A_INFO_SCREEN_2,
    HMI_PST_TRIP_B_MAIN_SCREEN ,       
    HMI_PST_TRIP_B_INFO_SCREEN_1,
    HMI_PST_TRIP_B_INFO_SCREEN_2,     
    HMI_PST_FUEL_SCREEN,
    HMI_PST_GENERAL_INFO_SCREEN,  
    HMI_PST_MUSIC_MAIN_SCREEEN,
    HMI_PST_MUSIC_CONTROL_SCREEEN,
    HMI_PST_NAVIGATION_MAIN_SCREEEN,
    HMI_PST_PHONE_MAIN_SCREEN,
    HMI_PST_PHONE_CONTROL_SCREEN,
    HMI_PST_PHONE_DIALING_SCREEN,
    HMI_PST_VOLUME_MAIN_SCREEN,
    HMI_PST_VOLUME_CONTROL_SCREEN,
    HMI_PST_PASSWORD_SCREEN,
}HMI_MAIN_PST_SCREENS_EN;

/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/
typedef struct 
{
    uint8_t Current_Minute;
    uint8_t Current_Hour;
}RTC_TIME_ST;

typedef struct
{
   uint8_t Current_day;
   uint8_t Current_month;
   uint8_t Current_year;    
}RTC_DATE_ST;


typedef enum
{
	TIME_EXPIRY_EVENT = 0,
	RIGHT_BUTTON_SHORT_PRESS, /* ADD ADDITIONAL EVENTS AFTER BUTTON EVENTS - ONLY FOR THIS PROJECT BUTTON MANAGER */
	LEFT_BUTTON_SHORT_PRESS,
	UP_BUTTON_SHORT_PRESS,
	DOWN_BUTTON_SHORT_PRESS,
	RIGHT_BUTTON_LONG_PRESS,
	LEFT_BUTTON_LONG_PRESS,
	UP_BUTTON_LONG_PRESS,
	DOWN_BUTTON_LONG_PRESS,
	RIGHT_BUTTON_CONTINUOUS_SHORT_PRESS,
	LEFT_BUTTON_CONTINUOUS_SHORT_PRESS,
	UP_BUTTON_CONTINUOUS_LONG_PRESS,
	DOWN_BUTTON_CONTINUOUS_LONG_PRESS,
	BLE_PASSCODE_EVENT,
	BLE_CALL_EVENT,
	BLE_CALL_VOLUME_EVENT,
	MAXIMUM_LIST_OF_PRESS_EVENT
}ButtonEventListTypeEn;

typedef enum
{
	ANIMATION_SCREEN = 0,
	HOME_SCREEN,
	HOME_SCREEN_PASSCODE,
	HOME_SCREEN_CALL,
	HOME_SCREEN_VOLUME,
	INTERMED_TRIPA,
	INTERMED_TRIPB,
	INTERMED_RTMI,
	INTERMED_NAVIGATION_ETA,
	INTERMED_SERVICE_REMINDER,
	INTERMED_CONTACTS,
	INTERMED_MUSIC,
	INTERMED_VOLUME,
	INTERMED_TRIPA_SUB_TIME_DIST,
	INTERMED_TRIPA_SUB_AVF_ASD,
	INTERMED_TRIPB_SUB_TIME_DIST,
	INTERMED_TRIPB_SUB_AVF_ASD,
	INTERMED_CONTACTS_SELECT,
	INTERMED_CONTACTS_CALL,
	INTERMED_MUSIC_DETAILS,
	INTERMED_VOLUME_ADJUST,
	HOME_SET_CONNECT,
	HOME_SET_BIKE,
	HOME_SET_DISPLAY,
	HOME_SET_ABOUT,
	HOME_SET_CONNECT_BLUETOOTH,
	HOME_SET_CONNECT_MUSIC,
	HOME_SET_BIKE_TRIPA,
	HOME_SET_BIKE_TRIPB,
	HOME_SET_BIKE_BATTERY,
	HOME_SET_DISP_BRIGHT,
	HOME_SET_DISP_MENU,
	HOME_SET_DISP_DATE_TIME,
	HOME_SET_DISP_UNIT,
	HOME_SET_ABOUT_RIDER_INFO,
	HOME_SET_ABOUT_SW_INFO,
	HOME_SET_ABOUT_REGULA_INFO,
	HOME_SET_BIKE_TRIPA_TRIP_INFO,
	HOME_SET_BIKE_TRIPA_TRIP_TIME,
	HOME_SET_BIKE_TRIPA_TRIP_AVG_SPD,
	HOME_SET_BIKE_TRIPA_TRIP_AVGFUEL,
	HOME_SET_BIKE_TRIPA_TRIP_HOLD,
	HOME_SET_BIKE_TRIPB_TRIP_INFO,
	HOME_SET_BIKE_TRIPB_TRIP_TIME,
	HOME_SET_BIKE_TRIPB_TRIP_AVG_SPD,
	HOME_SET_BIKE_TRIPB_TRIP_AVGFUEL,
	HOME_SET_BIKE_TRIPB_TRIP_HOLD,
	HOME_SET_BIKE_BATTERY_INFO,
	HOME_SET_DISP_BRIGHT_LOW,
	HOME_SET_DISP_BRIGHT_MEDIUM,
	HOME_SET_DISP_BRIGHT_HIGH,
	HOME_SET_DISP_BRIGHT_AUTO,
    HOME_SET_DISP_MENU_TRIPB,
	HOME_SET_DISP_MENU_FUEL,
	HOME_SET_DISP_MENU_NAVIGATION,
	HOME_SET_DISP_MENU_GEN_INFO,
	HOME_SET_DISP_MENU_PHONE,
	HOME_SET_DISP_MENU_MUSIC,
	HOME_SET_DISP_MENU_VOLUME,
	HOME_SET_DISP_DATE_TIME_DATE_SET,
	HOME_SET_DISP_DATE_TIME_TIME_SET,
	HOME_SET_DISP_DATE_TIME_24_SET,
	HOME_SET_DISP_UNIT_DISTANCE,
	HOME_SET_DISP_UNIT_FUELCONS,
	HOME_SET_ABOUT_SW_INFO_DETAILS,
	HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,
	HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,
	HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,
	HOME_SET_DISP_DATE_TIME_TIME_SET_HR,
	HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,
	HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,
	HOME_SET_DISP_UNIT_DISTANCE_KM,
	HOME_SET_DISP_UNIT_FUELCONS_KMPL,
	HOME_SET_DISP_UNIT_FURLCONS_L1000,
	HOME_SET_MUSIC_ARTIST,
	HOME_SET_MUSIC_ALBUM,
	HOME_SET_MUSIC_GENRE,
	HOME_SET_TIME_FORMAT,
	HOME_SET_TIME_FORMAT_12HR,
	HOME_SET_RIDER_INFO_SHOW,
	HOME_DISCLAIMER_SHOW,
	GUI_SCREEN_LIST_MAX
}ScreenListIdxTypeEn;


typedef enum
{
	ANIMATION_SCREEN_INDEX = 0,
	HOME_SCREEN_INDEX,
	INTERMEDIATE_SCREEN_INDEX,
	SETTING_SCREEN_INDEX,
	MAXIMUM_SCREEN_LIST_INDEX
}ScreenListTypeEn;



/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to initialize the main screen
* @param    
* @return  
* @invocation 
*/
void HMI_Main_Screen_Init(void);
/*
* @brief    This API is used to create screen with relevant objects
* @param    lv_ui *ui
* @return   NONE
* @invocation 
*/
void Main_Screen_Day_obj_create(lv_ui *ui);

void Main_Screen_night_obj_create(lv_ui *ui);

void Intermediate_Screen_Day_obj_create(lv_ui *ui);

void Inter_Screen_night_obj_create(lv_ui *ui);


void HMI_Intermediate_Screen_Cold_Init(void);

void HMI_Main_Screen_Cold_Init(void);

void HMI_Load_Intermediate_Screen(void);

void HMI_Load_Main_Screen(void);

void HMI_Load_Black_Screen(void);
void GUI_mainFunction(void);

void Idle_Main_Screen(lv_ui *ui);


void load_test(lv_ui *ui);


void HMI_Idle_Trans_Into_Main_Screen(void);
void idle_fuel(void);

uint8_t Test_fun(void);
void AVF_Alignment(void);
void GUI_TripA_Main_Screen_During(void);
void GUI_TripA_Main_Screen_Entry(void);
void GUI_TripA_Main_Screen_Exit(void);
void SetCrntScreen(uint32_t RequestedScrn);
uint32_t GetCrntScreen(void);

void GUI_TripA_Trip_Time_Screen_During(void);
void GUI_TripA_Trip_Time_Screen_Entry(void);
void GUI_TripA_Trip_Time_Screen_Exit(void);

void GUI_TripA_AVF_AVS_Screen_During(void);
void GUI_TripA_AVF_AVS_Screen_Entry(void);
void GUI_TripA_AVF_AVS_Screen_Exit(void);
void GUI_Contact_screen_Entry(void);
void GUI_Contact_screen_Exit(void);
void GUI_Contact_screen_During(void);
void GUI_Gear_Day_Entry(void);
void GUI_Gear_Night_Entry(void);
void GUI_Speed_Night_Entry(void);
void GUI_Speed_Day_Entry(void);

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

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
