/* @file FILE NAME */

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Palani kumar ( palanikumar@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : HMI_Main_Screen.c
 *  Version                         : v1.0.0
 *  Micros supported                : 
 *  Compilers supported             : 
 *  Platforms supported             : 
 *  Description                     : This file consists of button processing and HMI related elements 
 *                                    for Main screen
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/

#include "lvgl_app.h"
#include "HMI_Main_Screen.h"
#include "Button_Manager_Cfg.h"
#include "gui_guider.h"
#include "HMI_Setting_Screen.h"
#include "Fuel_Guage.h"
//#include "Ambient_light_sensor_Cfg.h"
#include "Ambient_light_sensor.h"
#include "BLE_music_module.h"
#include "Button_Manager.h"
#include "Swc_Speedometer_Cfg.h"
#include "HMI_music.h"
#include "HMI_Phone.h"
#include "HMI_TripInfo.h"
#include "HMI_Navigation.h"
#include "HMI_TripA.h"
#include "HMI_TripB.h"
#include "HMI_Clock.h"
#include "Swc_Odometer.h"
#include "BLE_call_module.h"

/***************/
/* HMI ADDED - 
*/

#include "HMI_GUI_Interface.h"





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

#define BLE_EN_REQ	1

#define BLE_EN_NOT_REQ	0


uint8_t DAY_NightMode_Factor = 0;
extern const lv_img_dsc_t _Batt_1_3x8;
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
HMI_MAIN_PST_SCREENS_EN g_HMI_Main_Screen_PST_State_u8;

HMI_MAIN_PST_SCREENS_EN g_HMI_Last_Intermediate_Screen;

uint8_t g_BLE_Connectivity_Status_u8 = 0;



uint8_t NIght = 0;
uint8_t counter = 0;
uint8_t checkpass=0;
uint8_t fl_Get_Current_Time_Foramt;
uint32_t fl_Get_Current_TripA_Time_Foramt;


uint8_t g_Selection_BLE_Screen = 1;

uint8_t  White_Screen =  0;

uint8_t Incoming_var = 0;

g_RTC_DATE_TIME_ST g_Date_Time_Str ;

uint8_t g_Handle_Bar_Btn_St_u8[MAX_BUTTON_LIST];
uint16_t g_intermediate_Speed_val_u16;

bool g_Main_To_Other_Screen_Change_Req_Status;

uint8_t g_Main_Screen_Cnt;

uint8_t g_Phone_Sub_Screen_Sel_Cnt_U8 = 0;

uint8_t g_Intermediate_Screen_List[8][2] = {{HMI_PST_TRIP_B_MAIN_SCREEN, BLE_EN_NOT_REQ},
 											{HMI_PST_FUEL_SCREEN, BLE_EN_NOT_REQ},
 											{HMI_PST_NAVIGATION_MAIN_SCREEEN, BLE_EN_REQ},
										    {HMI_PST_GENERAL_INFO_SCREEN, BLE_EN_NOT_REQ},
										    {HMI_PST_PHONE_MAIN_SCREEN, BLE_EN_REQ},
										    {HMI_PST_MUSIC_MAIN_SCREEEN, BLE_EN_REQ},
											{HMI_PST_VOLUME_MAIN_SCREEN, BLE_EN_REQ},
											{HMI_PST_PASSWORD_SCREEN, BLE_EN_REQ} };
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


void GUI_mainFunction(void);
/*
 * @brief    This function processes the main function of main and intermediate screeen
 * @param    
 * @return   
 */

uint8_t call_debug_variable = 0;
uint8_t count = 0;
uint8_t debug_variable = 0;
uint8_t debug_tacho = 4;
uint16_t debug_timer = 0;
uint8_t debug_Tacho_Direction = 0;
uint8_t debug_ReEntrance_Test = 0;




#define SIZE_OF_GRP(src)		sizeof(src)/sizeof(Image_Grp_Type_St)

typedef enum
{
	DAY_MODE = 0,
	NIGHT_MODE,
	MAX_MODE
}Mode_List_Type_En;

typedef enum
{
	IDLE_SCREEN = 0,
	/*MAIN_SCREEN,
	TRIP_SCREEN,
	MUSIC_SCREEN,
	NAVIGATION,*/
	MAX_NO_SCREEN
}Screen_List_Type_En;

typedef enum
{
	SKIN = 0,
	TACHO,
	MAX_NO_OF_HOME_SCR_FEATURES
}Home_Screen_Feature_List_Type_En;

typedef enum
{
	SONG_TEXT = 0,
	VOLUME,
	MAX_NO_OF_MUSIC_SCR_FEATURES
}Music_Screen_Feature_List_Type_En;

/* IMAGE GRP STRUCTURE */
typedef struct
{
	uint16_t X_Pos;
	uint16_t Y_Pos;
	uint16_t W_Size;
	uint16_t H_Size;
	lv_obj_t* Image_Container;
	lv_img_dsc_t* Image_Info;
}Image_Grp_Type_St;

typedef struct
{
	uint16_t Size_Of_Feature;
	Image_Grp_Type_St* Image_Grp;
}Feature_Grp_Type_St;




#define HMI_STANDARD_JMP 0xFFFFFFFF

typedef uint8_t(*CriteriaConditonTypeFn)(void);
typedef void(*EventCallBackFn) (void);
typedef void(*EventDuringFn) (void);

/* DEFINE AND HOLD THE HMI STATE DETAILS */
typedef struct 
{
	uint32_t HMI_Crnt_State;							/* CURRENT STATE */
	uint32_t HMI_Event_Happend;						/* CHECK FOR THE EVENT */
	uint32_t HMI_Next_State;							/* NEXT STATE */
	CriteriaConditonTypeFn Criteria_Fn;				/* CRITERIA FUNCTION */
}HMIStateDetailsType_St;

/* THIS SHALL HOLD THE SCREEN UNIQUE IDENTIFICATION NUMBER */
typedef struct
{
	uint32_t Screen_ID; 				/* THIS SHALL HOLD THE SCREEN UNIQUE ID - EXTEND THIS VARIABLE WITH NEW ONE IF SUB SCREEN MORE THAN 8 */
	uint32_t NoOfPossibleEvents;	/* THIS SHALL HOLD THE NUMBER OF POSSILE EVENTS FOR THIS STATE - BEAWARE OF CONFIGURE, THIS SHALL DECIDE THE CHECK */
	EventCallBackFn EventEntryCallBack_Fn; 		/* CALLBACK FUNCTION TO DO ON THE ENTRY */
	EventCallBackFn EventDuringCallBack_Fn; /* THIS SHALL HOLD THE FUNCTION TO BE EXECUTED DURING THE EXECUTION OF THIS SCREEN */
	EventCallBackFn EventExitCallBack_Fn; 			/* CALLBACK FUNCTION TO DO ON THE EXIT */
	EventCallBackFn DayEventEntryCallBack_Fn; 		/* CALLBACK FUNCTION TO DO ON THE ENTRY */
	EventCallBackFn DayEventDuringCallBack_Fn; /* THIS SHALL HOLD THE FUNCTION TO BE EXECUTED DURING THE EXECUTION OF THIS SCREEN */
	EventCallBackFn DayEventExitCallBack_Fn; 			/* CALLBACK FUNCTION TO DO ON THE EXIT */
}HMIScreenInfoTypeSt;

/* THIS SHALL HOLD THE SCREEN CHANGE INFORMATION */
typedef struct
{
	uint32_t ScreenIndex;
	EventCallBackFn Init_Screen;
	EventCallBackFn During_Screen;
	EventCallBackFn DeInit_Screen;
	EventCallBackFn Day_Init_Screen;
	EventCallBackFn Day_During_Screen;
	EventCallBackFn Day_DeInit_Screen;
}HMIScreenInit_Deinit_List_Type_St;


/* SCREEN EVENT OFFSET VALUE */
typedef struct
{
	uint16_t Offset_Value;
}HMIScreenEventOffsetTypeSt;


/* THIS IS ACT AS THE CURRENT SCREEN VARIABLE HANDLE BU GUI */
uint32_t g_CurrentScreen_U32 = ANIMATION_SCREEN;
uint32_t g_CurrentScreen_Uniqued_U32 = 0x00000000;
uint32_t g_PrevScreen_U32 = ANIMATION_SCREEN;
uint32_t g_PrevScreen_Uniqued_U32 = 0x00000000;
uint32_t g_CrntScreenIdx_U32 = ANIMATION_SCREEN_INDEX;
uint8_t g_PrevScreenMode_U32 = 1;

/* SCREEN EVENT OFFSET VALUE */
HMIScreenEventOffsetTypeSt HMIScreenEventOffsetSt[GUI_SCREEN_LIST_MAX] = {0};


const HMIScreenInit_Deinit_List_Type_St HMIScreenInit_Deinit_List_St[MAXIMUM_SCREEN_LIST_INDEX] = 
{
	{ANIMATION_SCREEN_INDEX, 		NULL, 								NULL, 						&HomeScreenExitFn, 		NULL, 							          NULL, 						&HomeScreenExitFn},
	{HOME_SCREEN_INDEX, 			&HomeScreenEntryFn, 				&HomeScreenMainDuringFn, 	&HomeScreenExitFn, 		&HomeScreenEntry_Day, 		              &HomeScreenMain_DayDuring, 	&HomeScreenExit_Day},
	{INTERMEDIATE_SCREEN_INDEX, 	&IntermediateScreen_Night_Entry, 	&HomeScreenMainDuringFn, 	&HomeScreenExitFn, 		&Intermediate_Screen_Day_Entry, 		  &HomeScreenMain_DayDuring, 	&HomeScreenExit_Day},
	{SETTING_SCREEN_INDEX, 			&SettingScreenEntryFn, 		        &SettingScreenDuringFn, 	&HomeScreenExitFn, 		&SettingScreenEntryFn, 		              &SettingScreenDuringFn, 		&HomeScreenExitFn}
};	


/* THIS TABLE SHALL HOLD THE SCREEN UNIQUE IDENTIFICATION NUMBER AND NUMBER OF EVENTS */	
const HMIScreenInfoTypeSt HMIScreenInfoSt[GUI_SCREEN_LIST_MAX] = 	
{	
/* 	SCREEN_IDX										UNIQUE_ID 	 *//*	SCREEN_NUMBER				NO_OF_EVENTS	ENTRY_FN 									DURING_FN									EXIT_FN				 						DAY_MODE_ENTRY									DAY_MODEDURING										EXIT_MODE_EXIT			*/
	/*ANIMATION_SCREEN = 0,							{0x00000000, */{	ANIMATION_SCREEN_INDEX,			1, 			NULL, 										NULL,										NULL,				 						NULL, 											NULL,												NULL},						
	/*HOME_SCREEN,									{0x10000000, */{	HOME_SCREEN_INDEX,				2, 			&HomeScreenLocalEntry, 						&HomeScreenDuringFn,						NULL,				 						&HomeScreen_LocalEntry_Day, 					&HomeScreen_Day_DuringFn,							&HomeScreenDay_Exit},
	/*HOME_SCREEN_PASSCODE,							{0x11000000, */{	INTERMEDIATE_SCREEN_INDEX,		1, 			&PASSCODE_SCREEN_ENTRY, 					&GUI_Password_Screen,						&PASSCODE_Screen_Exit,				 		&Passcode_Screen_Day_Entry, 					&Passcode_Screen_Day_During,						&Passcode_Screen_Day_Exit},						
	/*HOME_SCREEN_CALL,								{0x12000000, */{	INTERMEDIATE_SCREEN_INDEX,		5, 			&GUI_Phone_Contact_Call_Night_Entry, 		&GUI_Phone_Contact_Call_Night_During,		&GUI_Phone_Contact_Call_Night_Exit,	 		&GUI_Phone_Contact_Call_Day_Entry,				&GUI_Phone_Contact_Call_Day_During,					&GUI_Phone_Contact_Call_Day_Exit},						
	/*HOME_SCREEN_VOLUME,							{0x12000000, */{	INTERMEDIATE_SCREEN_INDEX,		5, 			&GUI_Phone_Volume_Night_Entry,  	  		&GUI_Volume_Screen_Night_Show_During,		&GUI_Phone_Volume_Night_Exit,	 			&GUI_Phone_Volume_Day_Entry,					&GUI_Volume_Sub_Screen_Main_Day_Mode_During,		&GUI_Phone_Volume_Day_Exit},						
	/*INTERMED_TRIPA,								{0x11100000, */{	INTERMEDIATE_SCREEN_INDEX,		5,			&GUI_TripA_Main_Screen_Night_Entry, 		&GUI_TripA_Main_Screen_Night_During,		&GUI_TripA_Main_Screen_Night_Exit,	 		&TripA_Main_Day_Entry,							&TripA_Main_Day_During,								&TripA_Main_Day_Exit},
	/*INTERMED_TRIPB,								{0x11200000, */{	INTERMEDIATE_SCREEN_INDEX,		5,			&GUI_TripB_Main_Screen_Night_Entry, 		&GUI_TripB_Main_Screen_Night_During,		&GUI_TripB_Main_Screen_Night_Exit,	 		&GUI_TripB_Main_Screen_Day_Entry,				&GUI_TripB_Main_Screen_Day_During,					&GUI_TripB_Main_Screen_Day_Exit},
	/*INTERMED_RTMI,								{0x11300000, */{	INTERMEDIATE_SCREEN_INDEX,		5,			&RTMI_Range_Night_Entry, 					&RTMI_Range_Night_During,					&RTMI_Range_Night_Exit,	 					&GUI_RTMI_Range_Day_Entry,						&GUI_RTMI_Range_Day_During,							&GUI_RTMI_Range_Day_Exit},
	/*INTERMED_NAVIGATION_ETA,						{0x11400000, */{	INTERMEDIATE_SCREEN_INDEX,		5, 			&GUI_Navigation_Night_Entry, 				&GUI_Navigation_Night_During,				&GUI_Navigation_Night_Exit,	 				&GUI_Navigation_Entry_Screen_Main_Day_Mode,		&GUI_Navigation_During_Screen_Main_Day_Mode,		&GUI_Navigation_Exit_Screen_Main_Day_Mode},
	/*INTERMED_SERVICE_REMINDER,					{0x11500000, */{	INTERMEDIATE_SCREEN_INDEX,		5, 			&GUI_Service_Remainder_Night_Entry, 		&GUI_Service_Remainder_Night_During,		&GUI_Service_Remainder_Night_Exit,	 		&GUI_Service_Remainder_Day_Entry,				&GUI_Service_Remainder_Day_During,					&GUI_Service_Remainder_Day_Exit},
	/*INTERMED_CONTACTS,							{0x11600000, */{	INTERMEDIATE_SCREEN_INDEX,		5, 			&GUI_Contact_screen_Night_Entry, 			&GUI_Contact_screen_Night_During,			&GUI_Contact_screen__Night_Exit,	 		&GUI_Phone_Screen_Main_Day_Mode_Entry,			&GUI_Phone_Screen_Main_Day_Mode_During,				&GUI_Phone_Screen_Main_Day_Mode_Exit},
	/*INTERMED_MUSIC,								{0x11700000, */{	INTERMEDIATE_SCREEN_INDEX,		6, 			&GUI_Music_screen_Night_Entry, 				&GUI_Music_screen_Night_During,				&GUI_Music_screen_Night_Exit,	 			&GUI_Music_Main_Day_Entry,						&GUI_Music_screen_Day_During,						&GUI_Music_Screen_Main_Day_Exit},
	/*INTERMED_VOLUME,								{0x11800000, */{	INTERMEDIATE_SCREEN_INDEX,		5, 			&GUI_Volume_screen_Night_Entry, 			&GUI_Volume_screen_Night_During,			&GUI_Volume_screen_Night_Exit,	 			&GUI_Volume_Screen_Main_Day_Mode_Entry,			&GUI_Volume_Screen_Main_Day_Mode_During,			&GUI_Volume_Screen_Day_Mode_Exit},
	/*INTERMED_TRIPA_SUB_TIME_DIST,					{0x11110000, */{	INTERMEDIATE_SCREEN_INDEX,		6, 			&GUI_TripA_Trip_Time_Screen_Entry, 			&GUI_TripA_Trip_Time_Screen_During,			&GUI_TripA_Trip_Time_Screen_Exit,	 		&TripA_Time_Day_Entry,							&GUI_TripA_Time_Day_During,							&TripA_Time_Day_Exit},
	/*INTERMED_TRIPA_SUB_AVF_ASD,					{0x11120000, */{	INTERMEDIATE_SCREEN_INDEX,		6, 			&GUI_TripA_AVF_AVS_Screen_Entry, 			&GUI_TripA_AVF_AVS_Screen_During,			&GUI_TripA_AVF_AVS_Screen_Exit,	 			&TripA_AVF_Day_Entry,							&TripA_AVF_Day_During,								&TripA_AVF_Day_Exit},
	/*INTERMED_TRIPB_SUB_TIME_DIST,					{0x11210000, */{	INTERMEDIATE_SCREEN_INDEX,		6, 			&GUI_TripB_Trip_Time_Screen_Night_Entry, 	&GUI_TripB_Trip_Time_Screen_Night_During,	&GUI_TripB_Trip_Time_Screen_Night_Exit,	 	&GUI_TripB_Time_Day_Enty,						&GUI_TripB_Time_Day_During,							&GUI_TripB_Time_Day_Exit},
	/*INTERMED_TRIPB_SUB_AVF_ASD,					{0x11220000, */{	INTERMEDIATE_SCREEN_INDEX,		6, 			&GUI_TripB_AVF_AVS_Screen_Night_Entry, 		&GUI_TripB_AVF_AVS_Screen_Night_During,		&GUI_TripB_AVF_AVS_Screen_Night_Exit,	 	&GUI_TripB_AVF_Day_Entry,						&GUI_TripB_AVF_Day_During,							&GUI_TripB_AVF_Day_Exit},
	/*INTERMED_CONTACTS_SELECT,						{0x11800000, */{	INTERMEDIATE_SCREEN_INDEX,		5, 			&GUI_Phone_Contact_List_Night_Entry, 		&GUI_Phone_Contact_List_Night_During,		&GUI_phone_Contact_List_Night_Exit,	 		&GUI_Phone_Contact_List_Day_Entry,				&GUI_Phone_Contact_List_Day_During,					&GUI_Phone_contact_List_Day_Exit},
	/*INTERMED_CONTACTS_CALL,						{0x11800000, */{	INTERMEDIATE_SCREEN_INDEX,		4, 			&GUI_Phone_Contact_Call_Night_Entry, 		&GUI_Phone_Contact_Call_Night_During,		&GUI_Phone_Contact_Call_Night_Exit,	 		&GUI_Phone_Contact_Call_Day_Entry,				&GUI_Phone_Contact_Call_Day_During,					&GUI_Phone_Contact_Call_Day_Exit},
	/*INTERMED_MUSIC_DETAILS,						{0x11800000, */{	INTERMEDIATE_SCREEN_INDEX,		5, 			&GUI_Music_Show_Night_Entry, 				&GUI_Music_Screen_Show_During,				&GUI_Music_Screen_Show_Night_Exit,	 		&GUI_Music_Screen_Show_Entry_Day,				&GUI_Music_Screen_Show_During_Day,					&GUI_Music_Screen_Show_Exit_Day},
	/*INTERMED_VOLUME_ADJUST,						{0x11800000, */{	INTERMEDIATE_SCREEN_INDEX,		5, 			&GUI_Volume_Screen_Night_Show_Entry, 		&GUI_Volume_Screen_Night_Show_During,		&GUI_Volume_Screen_Night_Show_Exit,	 		&GUI_Volume_Sub_Screen_Main_Day_Mode_Entry,		&GUI_Volume_Sub_Screen_Main_Day_Mode_During,		&GUI_Volume_Sub_Screen_Day_Mode_Exit},
	
	/*HOME_SET_CONNECT,								{0x21000000, */{	SETTING_SCREEN_INDEX,			4, 			&Setting_Main_Connectivity_Night_Entry, 	&Setting_Main_Color_Event_Night_During,		&Settingmain_exit,	 						&Setting_Main_Connectivity_Day_Entry,			&Setting_Main_Color_Event_Day_During,				&SettingMain_Day_Exit},	
	/*HOME_SET_BIKE,								{0x22000000, */{	SETTING_SCREEN_INDEX,			4, 			&Setting_Main_Bike_Night_Entry, 			&Setting_Main_Color_Event_Night_During,		&Settingmain_exit,	 						&Setting_Main_Bike_Day_Entry,					&Setting_Main_Color_Event_Day_During,				&SettingMain_Day_Exit},	
	/*HOME_SET_DISPLAY,								{0x23000000, */{	SETTING_SCREEN_INDEX,			4, 			&Setting_Main_Display_Night_Entry, 			&Setting_Main_Color_Event_Night_During,		&Settingmain_exit,	 						&Setting_Main_Display_Day_Entry,				&Setting_Main_Color_Event_Day_During,				&SettingMain_Day_Exit},	
	/*HOME_SET_ABOUT,								{0x24000000, */{	SETTING_SCREEN_INDEX,			4, 			&Setting_Main_About_Night_Entry, 			&Setting_Main_Color_Event_Night_During,		&Settingmain_exit,	 						&Setting_Main_About_Day_Entry,					&Setting_Main_Color_Event_Day_During,				&SettingMain_Day_Exit},	
	
	/*HOME_SET_CONNECT_BLUETOOTH,					{0x21100000, */{	SETTING_SCREEN_INDEX,			5, 			&Connect_Bluetooth_Night_Entry, 			&Conn_Bluetooth_Show,						&Connectivity_Exit,	 						&Connect_Bluetooth_Day_Entry, 					&Conn_Bluetooth_Day_Show,							&Connect_day_exit}, 	
	/*HOME_SET_CONNECT_MUSIC,						{0x21200000, */{	SETTING_SCREEN_INDEX,			5, 			&Connect_Music_Night_Entry, 				&Connect_MUSIC_Night_During,				&Connectivity_Exit,	 						&Connect_Music_Day_Entry, 						&Connnect_Music_Day_During,							&Connect_day_exit}, 	

	/*HOME_SET_BIKE_TRIPA,							{0x22100000, */{	SETTING_SCREEN_INDEX,			5, 			&BikeMenu_Night_1_Entry, 					&BikeMenu_Night_During,						&BikeMenuExit,       						&BikeMenu_Day_1_Entry, 							&BikeMenu_Day_During,								&BikeMenu_Day_Exit},	      
	/*HOME_SET_BIKE_TRIPB,							{0x22200000, */{	SETTING_SCREEN_INDEX,			5, 			&BikeMenu_Night_2_Entry, 					&BikeMenu_Night_During,						&BikeMenuExit,       						&BikeMenu_Day_2_Entry, 							&BikeMenu_Day_During,								&BikeMenu_Day_Exit},	      
	/*HOME_SET_BIKE_BATTERY,						{0x22300000, */{	SETTING_SCREEN_INDEX,			5, 			&BikeMenu_Night_3_Entry, 					&BikeMenu_Night_During,						&BikeMenuExit,       						&BikeMenu_Day_3_Entry, 							&BikeMenu_Day_During,								&BikeMenu_Day_Exit},	      

	/*HOME_SET_DISP_BRIGHT,							{0x23100000, */{	SETTING_SCREEN_INDEX,			5, 			&Display_Brightness_Night_Entry, 			&Display_Night_During,						&Display_Menu_Exit,	 						&Display_Brightness_Day_Entry, 					&Display_Day_During,								&Display_Menu_Day_Exit},
	/*HOME_SET_DISP_MENU,							{0x23200000, */{	SETTING_SCREEN_INDEX,			5, 			&Display_Menu_Night_Entry, 					&Display_Night_During,						&Display_Menu_Exit,	 						&Display_Menu_Day_Entry, 						&Display_Day_During,								&Display_Menu_Day_Exit},
	/*HOME_SET_DISP_DATE_TIME,						{0x23300000, */{	SETTING_SCREEN_INDEX,			5, 			&Display_DateandTime_Night_Entry, 			&Display_Night_During,						&Display_Menu_Exit,	 						&Display_DateandTime_Day_Entry, 				&Display_Day_During,								&Display_Menu_Day_Exit},
	/*HOME_SET_DISP_UNIT,							{0x23400000, */{	SETTING_SCREEN_INDEX,			5, 			&Display_Unit_Night_Entry, 					&Display_Night_During,						&Display_Menu_Exit,	 						&Display_Unit_Day_Entry, 						&Display_Day_During,								&Display_Menu_Day_Exit},

	/*HOME_SET_ABOUT_RIDER_INFO,					{0x24100000, */{	SETTING_SCREEN_INDEX,			5, 			&About_Rider_Night_Entry, 					&About_Night_During,						&About_Exit,         						&About_Rider_Day_Entry, 						&About_Day_During,									&AboutMenu_Day_Exit},	      
	/*HOME_SET_ABOUT_SW_INFO,						{0x24200000, */{	SETTING_SCREEN_INDEX,			5, 			&About_Software_Night_Entry, 				&About_Night_During,						&About_Exit,         						&About_Software_Day_Entry, 						&About_Day_During,									&AboutMenu_Day_Exit},	      
	/*HOME_SET_ABOUT_REGULA_INFO,					{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&About_Disclaimer_Night_Entry, 				&About_Night_During,						&About_Exit,         						&About_Disclaimer_Day_Entry, 					&About_Day_During,									&AboutMenu_Day_Exit},	      
	
	/*HOME_SET_BIKE_TRIPA_TRIP_INFO,				{0x22110000, */{	SETTING_SCREEN_INDEX,			5, 			&Trip_Night_Entry, 							&TripA_Trip_Night_During,					&Trip_Night_Exit,    						&Trip_Day_Entry, 								&TripA_Trip_Day_During,								&Trip_Day_Exit},					       
	/*HOME_SET_BIKE_TRIPA_TRIP_TIME,				{0x22120000, */{	SETTING_SCREEN_INDEX,			5, 			&Trip_Night_Entry, 							&TripA_Time_Night_During,					&Trip_Night_Exit,    						&Trip_Day_Entry, 								&TripA_Time_Day_During,								&Trip_Day_Exit},					       
	/*HOME_SET_BIKE_TRIPA_TRIP_AVG_SPD,				{0x22130000, */{	SETTING_SCREEN_INDEX,			5, 			&Trip_Night_Entry, 							&TripA_AvSpeed_Night_During,				&Trip_Night_Exit,    						&Trip_Day_Entry, 								&TripA_AvSpeed_Day_During,							&Trip_Day_Exit},					       
	/*HOME_SET_BIKE_TRIPA_TRIP_AVGFUEL,				{0x22140000, */{	SETTING_SCREEN_INDEX,			5, 			&Trip_Night_Entry, 							&TripA_AVFuel_Night_During,					&Trip_Night_Exit,    						&Trip_Day_Entry, 								&TripA_AVFuel_Day_During,							&Trip_Day_Exit},					       
	/*HOME_SET_BIKE_TRIPA_TRIP_HOLD,				{0x22150000, */{	SETTING_SCREEN_INDEX,			5, 			&Trip_Night_Entry, 							&TripA_Hold_Night_During,					&Trip_Night_Exit,    						&Trip_Day_Entry, 								&TripA_Hold_Day_During,								&Trip_Day_Exit},					       

	/*HOME_SET_BIKE_TRIPB_TRIP_INFO,				{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&TripB_Night_Entry, 						&TripB_Trip_Night_During,					&Trip_Night_Exit,    						&TripB_Day_Entry, 								&TripB_Trip_Day_During,								&Trip_Day_Exit},					       
	/*HOME_SET_BIKE_TRIPB_TRIP_TIME,				{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&TripB_Night_Entry, 						&TripB_Time_Night_During,					&Trip_Night_Exit,    						&TripB_Day_Entry, 								&TripB_Time_Day_During,								&Trip_Day_Exit},					       
	/*HOME_SET_BIKE_TRIPB_TRIP_AVG_SPD,				{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&TripB_Night_Entry, 						&TripB_AvSpeed_Night_During,				&Trip_Night_Exit,    						&TripB_Day_Entry, 								&TripB_AvSpeed_Day_During,							&Trip_Day_Exit},					       
	/*HOME_SET_BIKE_TRIPB_TRIP_AVGFUEL,				{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&TripB_Night_Entry, 						&TripB_AVFuel_Night_During,					&Trip_Night_Exit,    						&TripB_Day_Entry, 								&TripB_AVFuel_Day_During,							&Trip_Day_Exit},					       
	/*HOME_SET_BIKE_TRIPB_TRIP_HOLD,				{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&TripB_Night_Entry, 						&TripB_Hold_Night_During,					&Trip_Night_Exit,    						&TripB_Day_Entry, 								&TripB_Hold_Day_During,								&Trip_Day_Exit},					       

	/*HOME_SET_BIKE_BATTERY_INFO,					{0x24300000, */{	SETTING_SCREEN_INDEX,			3, 			&Batter_Val_Night_Entry,					&Battery_Val_Night_During,					&Battery_Val_Night_Exit,					&Battey_Val_Day_Entry, 							&Battery_val_Day_During,							&Battery_Val_Day_Exit},					       
	
	/*HOME_SET_DISP_BRIGHT_LOW,						{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Brightness_Low_Night_Entry, 				&Brightness_Night_Low_During,				&Brightness_Night_Exit, 					&Brightness_Low_Day_Entry, 						&Brightness_Day_Low_During,							&Brightness_Day_Exit},					       
	/*HOME_SET_DISP_BRIGHT_MEDIUM,					{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Brightness_Med_Night_Entry, 				&Brightness_Night_Med_During,				&Brightness_Night_Exit, 					&Brightness_Med_Day_Entry, 						&Brightness_Day_Med_During,							&Brightness_Day_Exit},					       
	/*HOME_SET_DISP_BRIGHT_HIGH,					{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Brightness_High_Night_Entry, 				&Brightness_Night_High_During,				&Brightness_Night_Exit, 					&Brightness_High_Day_Entry, 					&Brightness_Day_High_During,						&Brightness_Day_Exit},					       
	/*HOME_SET_DISP_BRIGHT_AUTO,					{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Brightness_Auto_Night_Entry, 				&Brightness_Night_Auto_During,				&Brightness_Night_Exit, 					&Brightness_Auto_Day_Entry, 					&Brightness_Day_Auto_During,						&Brightness_Day_Exit},		
	
	/*HOME_SET_DISP_MENU_TRIPB,						{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Menu_TripB_Night_Entry, 					&Menu_Night_Tripb_During,       			&Menu_Night_Exit, 	  						&Menu_TripB_Day_Entry,							&Menu_Day_Tripb_During,								&Menu_Day_Exit},					       			       
	/*HOME_SET_DISP_MENU_FUEL,						{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Menu_Fuel_Night_Entry, 					&Menu_Night_FUEL_During,					&Menu_Night_Exit,     						&Menu_Fuel_Day_Entry, 							&Menu_Day_FUEL_During,								&Menu_Day_Exit},
	/*HOME_SET_DISP_MENU_NAVIGATION,				{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Menu_Navi_Night_Entry, 					&Menu_Night_Navi_During,					&Menu_Night_Exit,     						&Menu_Navi_Day_Entry, 							&Menu_Day_Navi_During,								&Menu_Day_Exit},					       
	/*HOME_SET_DISP_MENU_GEN_INFO,					{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Menu_GeInfo_Night_Entry, 					&Menu_Night_GeInfo_During,					&Menu_Night_Exit,     						&Menu_GeInfo_Day_Entry, 						&Menu_Day_GeInfo_During,							&Menu_Day_Exit},					       
	/*HOME_SET_DISP_MENU_PHONE,						{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Menu_Phone_Night_Entry, 					&Menu_Night_Phone_During,					&Menu_Night_Exit,     						&Menu_Phone_Day_Entry, 							&Menu_Day_Phone_During,								&Menu_Day_Exit},					       
	/*HOME_SET_DISP_MENU_MUSIC,						{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Menu_Music_Night_Entry, 					&Menu_Night_Music_During,					&Menu_Night_Exit,     						&Menu_Music_Day_Entry, 							&Menu_Day_Music_During,								&Menu_Day_Exit},					       
	/*HOME_SET_DISP_MENU_VOLUME,					{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Menu_Volume_Night_Entry, 					&Menu_Night_Volume_During,					&Menu_Night_Exit,     						&Menu_Volume_Day_Entry, 						&Menu_Day_Volume_During,							&Menu_Day_Exit},					       
	
	/*HOME_SET_DISP_DATE_TIME_DATE_SET,				{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Datetimeset_Date_Night_Entry, 				&Datetimeset_Night_Date_During,				&Date_Time_Night_Exit,  					&Datetimeset_Date_Day_Entry, 					&Datetimeset_Day_Date_During,						&Date_Time_Day_Exit},					       
	/*HOME_SET_DISP_DATE_TIME_TIME_SET,				{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Datetimeset_Time_Night_Entry, 				&Datetimeset_Night_Time_During,				&Date_Time_Night_Exit,  					&Datetimeset_Time_Day_Entry, 					&Datetimeset_Day_Time_During,						&Date_Time_Day_Exit},					       
	/*HOME_SET_DISP_DATE_TIME_24_SET,				{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Datetimeset_24Hr_Night_Entry, 				&Datetimeset_Night_24Hr_During,				&Date_Time_Night_Exit,  					&Datetimeset_24Hr_Day_Entry, 					&Datetimeset_Day_24Hr_During,						&Date_Time_Day_Exit},					       
	
	/*HOME_SET_DISP_UNIT_DISTANCE,				 	{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Unit_Distance_Night_Entry, 				&Display_Unit_Night_During,					&Unit_Night_Exit,       					&Unit_Distance_Day_Entry, 						&Display_Unit_Day_During,							&Unit_Day_Exit},					       
	/*HOME_SET_DISP_UNIT_FUELCONS,				 	{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Unit_Fuel_Night_Entry, 					&Display_Unit_Night_During,					&Unit_Night_Exit,       					&Unit_Fuel_Day_Entry, 							&Display_Unit_Day_During,							&Unit_Day_Exit},					       
	/*HOME_SET_ABOUT_SW_INFO_DETAILS,			 	{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&SWInfo_Entry, 								NULL,										&SWInfo_Exit,      				 			&SWInfo_Day_Entry, 								NULL,												&SWInfo_Day_Exit},
	
	/*HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		{0x24300000, */{	SETTING_SCREEN_INDEX,			10, 		&Dateset_Night_Entry, 						&Display_Date_Setting_Night_During,			&Dateset_Night_Exit,						&Dateset_Day_Entry,								&Display_Date_Setting_Day_During,					&Dateset_Day_Exit},
	/*HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,		{0x24300000, */{	SETTING_SCREEN_INDEX,			10, 		&Monthset_Night_Entry, 						&Display_Month_Setting_Night_During,		&Monthset_Night_Exit,						&Monthset_Day_Entry,							&Display_Month_Setting_Day_During,					&Monthset_Day_Exit},
	/*HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		{0x24300000, */{	SETTING_SCREEN_INDEX,			10, 		&Yearset_Night_Entry, 						&Display_Year_Setting_Night_During,			&Yearset_Night_Exit,						&Yearset_Day_Entry,								&Display_Year_Setting_Day_During,					&Yearset_Day_Exit},
	/*HOME_SET_DISP_DATE_TIME_TIME_SET_HR,	    	{0x24300000, */{	SETTING_SCREEN_INDEX,			10, 		&Time_hr_set_Night_Entry, 					&Display_hr_Time_Setting_Night_During,		&Time_hr_set_Night_Exit,					&Time_hr_set_Day_Entry,							&Display_hr_Time_Setting_Day_During,				&Time_hr_set_Day_Exit},
	/*HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,	    	{0x24300000, */{	SETTING_SCREEN_INDEX,			10, 		&Time_min_set_Night_Entry, 					&Display_min_Time_Setting_Night_During,		&Time_min_set_Night_Exit,					&Time_min_set_Day_Entry,						&Display_min_Time_Setting_Day_During,				&Time_min_set_Day_Exit},
	/*HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,		{0x24300000, */{	SETTING_SCREEN_INDEX,			10, 		&Time_ampm_set_Night_Entry, 				&Display_ampm_Time_Setting_Night_During,	&Time_ampm_set_Night_Exit,					&Time_ampm_set_Day_Entry,						&Display_ampm_Time_Setting_Day_During,				&Time_ampm_set_Day_Exit},
	
	/*HOME_SET_DISP_UNIT_DISTANCE_KM,	 		 	{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Unit_Sub_Km_Night_Entry, 					NULL,										&Unit_Sub_Night_Exit,						&Unit_Sub_Km_Day_Entry,							NULL,												&Unit_Sub_Day_Exit},
	/*HOME_SET_DISP_UNIT_FUELCONS_KMPL,	 		 	{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Unit_Sub_fuel_km_Night_Entry, 				&Unit_Sub_fuel_km_During,					&Unit_Sub_Night_Exit,						&Unit_Sub_fuel_km_Day_Entry,					&Unit_Sub_fuel_km_Day_During,						&Unit_Sub_Day_Exit},
	/*HOME_SET_DISP_UNIT_FURLCONS_L1000			 	{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Unit_Sub_fuel_L100_Night_Entry, 			&Unit_Sub_fuel_L100_During,					&Unit_Sub_Night_Exit,						&Unit_Sub_fuel_L100_Day_Entry,					&Unit_Sub_fuel_L100_Day_During,						&Unit_Sub_Day_Exit},
	
	/*HOME_SET_MUSIC_ARTIST						 	{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Music_Artist_Night_Entry, 					&Music_Night_Artist_During,					&Music_Night_Exit,							&Music_Artist_Day_Entry,						&Music_Day_Artist_During,							&Music_Day_Exit},
	/*HOME_SET_MUSIC_ALBUM						 	{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Music_Album_Night_Entry, 					&Music_Night_Album_During,					&Music_Night_Exit,							&Music_Album_Day_Entry,							&Music_Day_Album_During,							&Music_Day_Exit},
	/*HOME_SET_MUSIC_GENRE						 	{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Music_Genre_Night_Entry, 					&Music_Night_Genre_During,					&Music_Night_Exit,							&Music_Genre_Day_Entry,							&Music_Day_Genre_During,							&Music_Day_Exit},
	
	/*HOME_SET_TIME_FORMAT						 	{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&TimeFormat_24Hr_Night_Entry, 				&GUI_Time_Format_Night_24Hr_During,			&GUI_Time_Format_Night_Exit,				&TimeFormat_24Hr_Day_Entry,						&GUI_Time_Format_Day_24Hr_During,					&GUI_Time_Format_Day_Exit},
	/*HOME_SET_TIME_FORMAT_12HR					 	{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&TimeFormat_12Hr_Night_Entry, 				&GUI_Time_Format_Night_12Hr_During,			&GUI_Time_Format_Night_Exit,				&TimeFormat_12_Hr_Day_Entry,					&GUI_Time_Format_Day_12Hr_During,					&GUI_Time_Format_Day_Exit},
	
	/*HOME_SET_RIDER_INFO_SHOW					 	{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&GUI_RiderInfo_Night_Entry, 				&GUI_RiderInfo_Night_During,				&GUI_RiderInfo_Night_Exit,					&GUI_RiderInfo_Day_Entry,						&GUI_RiderInfo_Day_During,							&GUI_RiderInfo_Day_Exit},
	
	/*HOME_DISCLAIMER_SHOW						 	{0x24300000, */{	SETTING_SCREEN_INDEX,			5, 			&Disclaimer_Night_Entry, 					NULL,										&GUI_Disclaimer_Details_Night_Exit,			&Disclaimer_Day_Entry,							NULL,												&GUI_Disclaimer_Details_Day_Exit}
};                                                                                                                                                                                                             

/* MAIN STATE MACHINE - THIS SHALL HOLD ALL THE SCREEN STATE CONFIGURATION */
const HMIStateDetailsType_St HMIStateDetailsSt[] =
{
/* 	CRNT_SCREEN									CRNT_EVENT 		 						NXT_SCREEN									CRITERIA_FN		*/
	{ANIMATION_SCREEN,							TIME_EXPIRY_EVENT,						HOME_SCREEN,								NULL			},	
	{HOME_SCREEN,								RIGHT_BUTTON_LONG_PRESS,				HOME_SET_CONNECT,							&HMI_Setting_Screen_Navigation			},	
	{HOME_SCREEN,								RIGHT_BUTTON_SHORT_PRESS,				INTERMED_TRIPA,								&JmpPrevIntermediateScreen			},
	
	{HOME_SCREEN_PASSCODE,						LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SCREEN_CALL,							LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},
	{HOME_SCREEN_CALL,	 						RIGHT_BUTTON_SHORT_PRESS,				HOME_SCREEN_CALL,							&GUI_Contact_Right_button_Click			},	
	{HOME_SCREEN_CALL,	 						LEFT_BUTTON_SHORT_PRESS,				HOME_SCREEN_CALL,							&GUI_Contact_Left_button_Click		},	
	{HOME_SCREEN_CALL,	 						UP_BUTTON_SHORT_PRESS,					HOME_SCREEN_CALL,							&GUI_Contact_Up_button_Click			},	
	{HOME_SCREEN_CALL,	 						DOWN_BUTTON_SHORT_PRESS,				HOME_SCREEN_CALL,							&GUI_Contact_Down_button_Click			},		
	
	{HOME_SCREEN_VOLUME,						LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	{HOME_SCREEN_VOLUME,	 					RIGHT_BUTTON_SHORT_PRESS,				HOME_SCREEN_VOLUME,							NULL		},	
	{HOME_SCREEN_VOLUME,	 					LEFT_BUTTON_SHORT_PRESS,				HOME_SCREEN_VOLUME,							NULL			},	
	{HOME_SCREEN_VOLUME,	 					UP_BUTTON_SHORT_PRESS,					HOME_SCREEN_VOLUME,							&IntermediateScreen_Volume_Increment	},	
	{HOME_SCREEN_VOLUME,	 					DOWN_BUTTON_SHORT_PRESS,				HOME_SCREEN_VOLUME,							&IntermediateScreen_Volume_Decrement	},	
	
	{INTERMED_TRIPA,	 						RIGHT_BUTTON_SHORT_PRESS,				INTERMED_TRIPA_SUB_TIME_DIST,				NULL			},	
	{INTERMED_TRIPA,	 						RIGHT_BUTTON_LONG_PRESS,				HOME_SET_CONNECT,							&HMI_Setting_Screen_Navigation			},	
	{INTERMED_TRIPA,	 						LEFT_BUTTON_SHORT_PRESS,				HOME_SCREEN,								NULL			},	
	{INTERMED_TRIPA,	 						UP_BUTTON_SHORT_PRESS,					INTERMED_TRIPA,								&SkipReverseIntermediateIfSelected			},	
	{INTERMED_TRIPA,	 						DOWN_BUTTON_SHORT_PRESS,				INTERMED_TRIPA,								&SkipIntermediateIfSelected			},	
	
	{INTERMED_TRIPB,	 						RIGHT_BUTTON_SHORT_PRESS,				INTERMED_TRIPB_SUB_TIME_DIST,				NULL			},	
	{INTERMED_TRIPB,	 						RIGHT_BUTTON_LONG_PRESS,				HOME_SET_CONNECT,							&HMI_Setting_Screen_Navigation			},	
	{INTERMED_TRIPB,	 						LEFT_BUTTON_SHORT_PRESS,				HOME_SCREEN,								NULL			},	
	{INTERMED_TRIPB,	 						UP_BUTTON_SHORT_PRESS,					INTERMED_TRIPA,								&SkipReverseIntermediateIfSelected			},	
	{INTERMED_TRIPB,	 						DOWN_BUTTON_SHORT_PRESS,				INTERMED_TRIPA,								&SkipIntermediateIfSelected			},	
	
	{INTERMED_RTMI,	 							RIGHT_BUTTON_SHORT_PRESS,				INTERMED_RTMI,								NULL			},	
	{INTERMED_RTMI,	 							RIGHT_BUTTON_LONG_PRESS,				HOME_SET_CONNECT,							&HMI_Setting_Screen_Navigation			},	
	{INTERMED_RTMI,	 							LEFT_BUTTON_SHORT_PRESS,				HOME_SCREEN,								NULL			},	
	{INTERMED_RTMI,	 							UP_BUTTON_SHORT_PRESS,					INTERMED_TRIPA,								&SkipReverseIntermediateIfSelected			},	
	{INTERMED_RTMI,	 							DOWN_BUTTON_SHORT_PRESS,				INTERMED_TRIPA,								&SkipIntermediateIfSelected			},	
	
	{INTERMED_NAVIGATION_ETA,					RIGHT_BUTTON_SHORT_PRESS,				INTERMED_NAVIGATION_ETA,					NULL			},	
	{INTERMED_NAVIGATION_ETA,					RIGHT_BUTTON_LONG_PRESS,				HOME_SET_CONNECT,							&HMI_Setting_Screen_Navigation			},	
	{INTERMED_NAVIGATION_ETA,					LEFT_BUTTON_SHORT_PRESS,				HOME_SCREEN,								NULL			},	
	{INTERMED_NAVIGATION_ETA,					UP_BUTTON_SHORT_PRESS,					INTERMED_TRIPA,								&SkipReverseIntermediateIfSelected			},	
	{INTERMED_NAVIGATION_ETA,					DOWN_BUTTON_SHORT_PRESS,				INTERMED_TRIPA,								&SkipIntermediateIfSelected			},	
	
	{INTERMED_SERVICE_REMINDER,					RIGHT_BUTTON_SHORT_PRESS,				INTERMED_SERVICE_REMINDER,					NULL			},	
	{INTERMED_SERVICE_REMINDER,					RIGHT_BUTTON_LONG_PRESS,				HOME_SET_CONNECT,							&HMI_Setting_Screen_Navigation			},	
	{INTERMED_SERVICE_REMINDER,					LEFT_BUTTON_SHORT_PRESS,				HOME_SCREEN,								NULL			},	
	{INTERMED_SERVICE_REMINDER,					UP_BUTTON_SHORT_PRESS,					INTERMED_TRIPA,								&SkipReverseIntermediateIfSelected			},	
	{INTERMED_SERVICE_REMINDER,					DOWN_BUTTON_SHORT_PRESS,				INTERMED_TRIPA,								&SkipIntermediateIfSelected			},	
	
	{INTERMED_CONTACTS,	 						RIGHT_BUTTON_SHORT_PRESS,				INTERMED_CONTACTS_SELECT,					NULL			},	
	{INTERMED_CONTACTS,	 						RIGHT_BUTTON_LONG_PRESS,				HOME_SET_CONNECT,							&HMI_Setting_Screen_Navigation			},	
	{INTERMED_CONTACTS,	 						LEFT_BUTTON_SHORT_PRESS,				HOME_SCREEN,								NULL			},	
	{INTERMED_CONTACTS,	 						UP_BUTTON_SHORT_PRESS,					INTERMED_TRIPA,								&SkipReverseIntermediateIfSelected			},	
	{INTERMED_CONTACTS,	 						DOWN_BUTTON_SHORT_PRESS,				INTERMED_TRIPA,								&SkipIntermediateIfSelected			},	
	
	{INTERMED_MUSIC,	 						RIGHT_BUTTON_SHORT_PRESS,				INTERMED_MUSIC_DETAILS,						NULL			},	
	{INTERMED_MUSIC,	 						RIGHT_BUTTON_LONG_PRESS,				HOME_SET_CONNECT,							&HMI_Setting_Screen_Navigation			},	
	{INTERMED_MUSIC,	 						LEFT_BUTTON_SHORT_PRESS,				HOME_SCREEN,								NULL			},	
	{INTERMED_MUSIC,	 						UP_BUTTON_SHORT_PRESS,					INTERMED_TRIPA,								&SkipReverseIntermediateIfSelected			},	
	{INTERMED_MUSIC,	 						DOWN_BUTTON_SHORT_PRESS,				INTERMED_TRIPA,								&SkipIntermediateIfSelected			},	
	{INTERMED_MUSIC,                            LEFT_BUTTON_LONG_PRESS,      			HOME_SCREEN,                    			NULL            },
	
	{INTERMED_VOLUME,	 						RIGHT_BUTTON_SHORT_PRESS,				INTERMED_VOLUME_ADJUST,						NULL			},	
	{INTERMED_VOLUME,	 						RIGHT_BUTTON_LONG_PRESS,				HOME_SET_CONNECT,							&HMI_Setting_Screen_Navigation			},	
	{INTERMED_VOLUME,	 						LEFT_BUTTON_SHORT_PRESS,				HOME_SCREEN,								NULL			},	
	{INTERMED_VOLUME,	 						UP_BUTTON_SHORT_PRESS,					INTERMED_TRIPA,								&SkipReverseIntermediateIfSelected			},	
	{INTERMED_VOLUME,	 						DOWN_BUTTON_SHORT_PRESS,				INTERMED_TRIPA,								&SkipIntermediateIfSelected			},	
	
	{INTERMED_TRIPA_SUB_TIME_DIST,				RIGHT_BUTTON_SHORT_PRESS,				INTERMED_TRIPA_SUB_TIME_DIST,				NULL			},	
	{INTERMED_TRIPA_SUB_TIME_DIST,				RIGHT_BUTTON_LONG_PRESS,				INTERMED_TRIPA_SUB_TIME_DIST,				&ResetTripA			},	
	{INTERMED_TRIPA_SUB_TIME_DIST,				LEFT_BUTTON_SHORT_PRESS,				INTERMED_TRIPA,								NULL			},	
	{INTERMED_TRIPA_SUB_TIME_DIST,				UP_BUTTON_SHORT_PRESS,					INTERMED_TRIPA_SUB_AVF_ASD,					&TripA_Button_UpEvent			},	
	{INTERMED_TRIPA_SUB_TIME_DIST,				DOWN_BUTTON_SHORT_PRESS,				INTERMED_TRIPA_SUB_AVF_ASD,					&TripA_Button_DownEvent			},	
	{INTERMED_TRIPA_SUB_TIME_DIST,          	LEFT_BUTTON_LONG_PRESS,         		HOME_SCREEN,                    			NULL         },
	
	{INTERMED_TRIPA_SUB_AVF_ASD,	 			RIGHT_BUTTON_SHORT_PRESS,				INTERMED_TRIPA_SUB_AVF_ASD,					NULL			},	
	{INTERMED_TRIPA_SUB_AVF_ASD,	 			RIGHT_BUTTON_LONG_PRESS,				INTERMED_TRIPA_SUB_AVF_ASD,					&ResetTripA			},	
	{INTERMED_TRIPA_SUB_AVF_ASD,	 			LEFT_BUTTON_SHORT_PRESS,				INTERMED_TRIPA,								NULL			},	
	{INTERMED_TRIPA_SUB_AVF_ASD,	 			UP_BUTTON_SHORT_PRESS,					INTERMED_TRIPA_SUB_TIME_DIST,				&TripA_Button_UpEvent			},	
	{INTERMED_TRIPA_SUB_AVF_ASD,	 			DOWN_BUTTON_SHORT_PRESS,				INTERMED_TRIPA_SUB_TIME_DIST,				&TripA_Button_DownEvent			},	
	{INTERMED_TRIPA_SUB_AVF_ASD,                LEFT_BUTTON_LONG_PRESS,         		HOME_SCREEN,                    			NULL           },
	
	{INTERMED_TRIPB_SUB_TIME_DIST,				RIGHT_BUTTON_SHORT_PRESS,				INTERMED_TRIPB_SUB_TIME_DIST,				NULL			},	
	{INTERMED_TRIPB_SUB_TIME_DIST,				RIGHT_BUTTON_LONG_PRESS,				INTERMED_TRIPB_SUB_TIME_DIST,				&ResetTripB			},	
	{INTERMED_TRIPB_SUB_TIME_DIST,				LEFT_BUTTON_SHORT_PRESS,				INTERMED_TRIPB,								NULL			},	
	{INTERMED_TRIPB_SUB_TIME_DIST,				UP_BUTTON_SHORT_PRESS,					INTERMED_TRIPB_SUB_AVF_ASD,					&TripB_Button_UpEvent			},	
	{INTERMED_TRIPB_SUB_TIME_DIST,				DOWN_BUTTON_SHORT_PRESS,				INTERMED_TRIPB_SUB_AVF_ASD,					&TripB_Button_DownEvent			},	
	{INTERMED_TRIPB_SUB_TIME_DIST,          	LEFT_BUTTON_LONG_PRESS,         		HOME_SCREEN,                    			NULL            },
	
	{INTERMED_TRIPB_SUB_AVF_ASD,	 			RIGHT_BUTTON_SHORT_PRESS,				INTERMED_TRIPB_SUB_AVF_ASD,					NULL			},	
	{INTERMED_TRIPB_SUB_AVF_ASD,	 			RIGHT_BUTTON_LONG_PRESS,				INTERMED_TRIPB_SUB_AVF_ASD,					&ResetTripB			},	
	{INTERMED_TRIPB_SUB_AVF_ASD,	 			LEFT_BUTTON_SHORT_PRESS,				INTERMED_TRIPB,								NULL			},	
	{INTERMED_TRIPB_SUB_AVF_ASD,	 			UP_BUTTON_SHORT_PRESS,					INTERMED_TRIPB_SUB_TIME_DIST,				&TripB_Button_UpEvent			},	
	{INTERMED_TRIPB_SUB_AVF_ASD,	 			DOWN_BUTTON_SHORT_PRESS,				INTERMED_TRIPB_SUB_TIME_DIST,				&TripB_Button_DownEvent			},	
	{INTERMED_TRIPB_SUB_AVF_ASD,                LEFT_BUTTON_LONG_PRESS,         		HOME_SCREEN,                    			NULL                            },
	
	{INTERMED_CONTACTS_SELECT,	 				RIGHT_BUTTON_SHORT_PRESS,				INTERMED_CONTACTS_CALL,						&Call_Selectbtn_click},	
	{INTERMED_CONTACTS_SELECT,	 				LEFT_BUTTON_SHORT_PRESS,				INTERMED_CONTACTS,							NULL			},	
	{INTERMED_CONTACTS_SELECT,	 				UP_BUTTON_SHORT_PRESS,					INTERMED_CONTACTS_SELECT,					&GUI_Down_Phone_contact_list },	
	{INTERMED_CONTACTS_SELECT,	 				DOWN_BUTTON_SHORT_PRESS,				INTERMED_CONTACTS_SELECT,					&GUI_Up_Phone_contact_list },	
	{INTERMED_CONTACTS_SELECT,                  LEFT_BUTTON_LONG_PRESS,         		HOME_SCREEN,                    			NULL          },
	
	{INTERMED_CONTACTS_CALL,	 				RIGHT_BUTTON_SHORT_PRESS,				INTERMED_CONTACTS_CALL,						&GUI_Contact_Right_button_Click			},	
	{INTERMED_CONTACTS_CALL,	 				LEFT_BUTTON_SHORT_PRESS,				INTERMED_CONTACTS_SELECT,					&GUI_Contact_Left_button_Click		},	
	{INTERMED_CONTACTS_CALL,	 				UP_BUTTON_SHORT_PRESS,					INTERMED_CONTACTS_CALL,						&GUI_Contact_Up_button_Click			},	
	{INTERMED_CONTACTS_CALL,	 				DOWN_BUTTON_SHORT_PRESS,				INTERMED_CONTACTS_CALL,						&GUI_Contact_Down_button_Click			},	
	
	{INTERMED_MUSIC_DETAILS,	 				RIGHT_BUTTON_SHORT_PRESS,				INTERMED_MUSIC_DETAILS,						&IntermediateScreen_Music_PlayPause			},	
	{INTERMED_MUSIC_DETAILS,	 				LEFT_BUTTON_SHORT_PRESS,				INTERMED_MUSIC,								NULL			},	
	{INTERMED_MUSIC_DETAILS,	 				UP_BUTTON_SHORT_PRESS,					INTERMED_MUSIC_DETAILS,						&IntermediateScreen_Music_PrevTrack			},	
	{INTERMED_MUSIC_DETAILS,	 				DOWN_BUTTON_SHORT_PRESS,				INTERMED_MUSIC_DETAILS,						&IntermediateScreen_Music_NextTrack			},
	{INTERMED_MUSIC_DETAILS,                    LEFT_BUTTON_LONG_PRESS,         		HOME_SCREEN,                    			NULL                                       },
	
	{INTERMED_VOLUME_ADJUST,	 				RIGHT_BUTTON_SHORT_PRESS,				INTERMED_VOLUME_ADJUST,						&GUI_Volume_Mute			},	
	{INTERMED_VOLUME_ADJUST,	 				LEFT_BUTTON_SHORT_PRESS,				INTERMED_VOLUME,							NULL			},	
	{INTERMED_VOLUME_ADJUST,	 				UP_BUTTON_SHORT_PRESS,					INTERMED_VOLUME_ADJUST,						&IntermediateScreen_Volume_Increment	},	
	{INTERMED_VOLUME_ADJUST,	 				DOWN_BUTTON_SHORT_PRESS,				INTERMED_VOLUME_ADJUST,						&IntermediateScreen_Volume_Decrement	},	
	{INTERMED_VOLUME_ADJUST,                    LEFT_BUTTON_LONG_PRESS,         		HOME_SCREEN,                  				NULL      },
	
	{HOME_SET_CONNECT,	 						RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_CONNECT_BLUETOOTH,					NULL			},	
	{HOME_SET_CONNECT,	 						LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	{HOME_SET_CONNECT,	 						UP_BUTTON_SHORT_PRESS,					HOME_SET_ABOUT,								&SettingArrow_UpButton_Pressed			},	
	{HOME_SET_CONNECT,	 						DOWN_BUTTON_SHORT_PRESS,				HOME_SET_BIKE,								&SettingArrow_DownButton_Pressed			},	
	
	{HOME_SET_BIKE,								RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA,						NULL			},	
	{HOME_SET_BIKE,								LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	{HOME_SET_BIKE,								UP_BUTTON_SHORT_PRESS,					HOME_SET_CONNECT,							&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_BIKE,								DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISPLAY,							&SettingArrow_DownButton_Pressed			},	
	
	{HOME_SET_DISPLAY,							RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT,						NULL			},	
	{HOME_SET_DISPLAY,							LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	{HOME_SET_DISPLAY,							UP_BUTTON_SHORT_PRESS,					HOME_SET_BIKE,								&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISPLAY,							DOWN_BUTTON_SHORT_PRESS,				HOME_SET_ABOUT,								&SettingArrow_DownButton_Pressed			},	
	
	{HOME_SET_ABOUT,							RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_ABOUT_RIDER_INFO,					NULL			},	
	{HOME_SET_ABOUT,							LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	{HOME_SET_ABOUT,							UP_BUTTON_SHORT_PRESS,					HOME_SET_DISPLAY,							&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_ABOUT,							DOWN_BUTTON_SHORT_PRESS,				HOME_SET_CONNECT,							&SettingArrow_DownButton_Pressed			},	
	
	{HOME_SET_CONNECT_BLUETOOTH,				RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_CONNECT_BLUETOOTH,					&Set_Bluetooth_Enable_Setting			},	
	{HOME_SET_CONNECT_BLUETOOTH,				LEFT_BUTTON_SHORT_PRESS,				HOME_SET_CONNECT,							NULL			},	
	{HOME_SET_CONNECT_BLUETOOTH,				UP_BUTTON_SHORT_PRESS,					HOME_SET_CONNECT_MUSIC,						&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_CONNECT_BLUETOOTH,				DOWN_BUTTON_SHORT_PRESS,				HOME_SET_CONNECT_MUSIC,						&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_CONNECT_BLUETOOTH,				LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_CONNECT_MUSIC,					RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_MUSIC_ARTIST,						&Set_Music_Enable_Setting			},	
	{HOME_SET_CONNECT_MUSIC,					LEFT_BUTTON_SHORT_PRESS,				HOME_SET_CONNECT,							NULL			},	
	{HOME_SET_CONNECT_MUSIC,					UP_BUTTON_SHORT_PRESS,					HOME_SET_CONNECT_BLUETOOTH,					&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_CONNECT_MUSIC,					DOWN_BUTTON_SHORT_PRESS,				HOME_SET_CONNECT_BLUETOOTH,					&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_CONNECT_MUSIC,					LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_BIKE_TRIPA,						RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA_TRIP_INFO,				NULL			},	
	{HOME_SET_BIKE_TRIPA,						LEFT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE,								NULL			},	
	{HOME_SET_BIKE_TRIPA,						UP_BUTTON_SHORT_PRESS,					HOME_SET_BIKE_BATTERY,						&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_BIKE_TRIPA,						DOWN_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB,						&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_BIKE_TRIPA,						LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_BIKE_TRIPB,						RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB_TRIP_INFO,				NULL			},	
	{HOME_SET_BIKE_TRIPB,						LEFT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE,								NULL			},	
	{HOME_SET_BIKE_TRIPB,						UP_BUTTON_SHORT_PRESS,					HOME_SET_BIKE_TRIPA,						&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_BIKE_TRIPB,						DOWN_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_BATTERY,						&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_BIKE_TRIPB,						LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_BIKE_BATTERY,						RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_BATTERY_INFO,					NULL			},	
	{HOME_SET_BIKE_BATTERY,						LEFT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE,								NULL			},	
	{HOME_SET_BIKE_BATTERY,						UP_BUTTON_SHORT_PRESS,					HOME_SET_BIKE_TRIPB,						&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_BIKE_BATTERY,						DOWN_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA,						&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_BIKE_BATTERY,						LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_DISP_BRIGHT,						RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT_AUTO,					NULL			},	
	{HOME_SET_DISP_BRIGHT,						LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISPLAY,							NULL			},	
	{HOME_SET_DISP_BRIGHT,						UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_UNIT,							&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_BRIGHT,						DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU,							&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_BRIGHT,						LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_MENU,						RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_TRIPB,					NULL			},	
	{HOME_SET_DISP_MENU,						LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISPLAY,							NULL			},	
	{HOME_SET_DISP_MENU,						UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_BRIGHT,						&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_MENU,						DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME,					&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_MENU,						LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_DATE_TIME,					RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_24_SET,				NULL			},	
	{HOME_SET_DISP_DATE_TIME,					LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISPLAY,							NULL			},	
	{HOME_SET_DISP_DATE_TIME,					UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_MENU,							&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_DATE_TIME,					DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT,							&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_DATE_TIME,					LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_UNIT,						RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT_DISTANCE,				NULL			},	
	{HOME_SET_DISP_UNIT,						LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISPLAY,							NULL			},	
	{HOME_SET_DISP_UNIT,						UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_DATE_TIME,					&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_UNIT,						DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT,						&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_UNIT,						LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_ABOUT_RIDER_INFO,					RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_RIDER_INFO_SHOW,					NULL			},	
	{HOME_SET_ABOUT_RIDER_INFO,					LEFT_BUTTON_SHORT_PRESS,				HOME_SET_ABOUT,								NULL			},	
	{HOME_SET_ABOUT_RIDER_INFO,					UP_BUTTON_SHORT_PRESS,					HOME_SET_ABOUT_REGULA_INFO,					&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_ABOUT_RIDER_INFO,					DOWN_BUTTON_SHORT_PRESS,				HOME_SET_ABOUT_SW_INFO,						&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_ABOUT_RIDER_INFO,					LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_ABOUT_SW_INFO,					RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_ABOUT_SW_INFO_DETAILS,				NULL			},	
	{HOME_SET_ABOUT_SW_INFO,					LEFT_BUTTON_SHORT_PRESS,				HOME_SET_ABOUT,								NULL			},	
	{HOME_SET_ABOUT_SW_INFO,					UP_BUTTON_SHORT_PRESS,					HOME_SET_ABOUT_RIDER_INFO,					&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_ABOUT_SW_INFO,					DOWN_BUTTON_SHORT_PRESS,				HOME_SET_ABOUT_REGULA_INFO,					&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_ABOUT_SW_INFO,					LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		

	{HOME_SET_ABOUT_REGULA_INFO,				RIGHT_BUTTON_SHORT_PRESS,				HOME_DISCLAIMER_SHOW,						NULL			},	
	{HOME_SET_ABOUT_REGULA_INFO,				LEFT_BUTTON_SHORT_PRESS,				HOME_SET_ABOUT,								NULL			},	
	{HOME_SET_ABOUT_REGULA_INFO,				UP_BUTTON_SHORT_PRESS,					HOME_SET_ABOUT_SW_INFO,						&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_ABOUT_REGULA_INFO,				DOWN_BUTTON_SHORT_PRESS,				HOME_SET_ABOUT_RIDER_INFO,					&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_ABOUT_REGULA_INFO,				LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_BIKE_TRIPA_TRIP_INFO,				RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA_TRIP_INFO,				NULL			},	
	{HOME_SET_BIKE_TRIPA_TRIP_INFO,				LEFT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA,						NULL			},	
	{HOME_SET_BIKE_TRIPA_TRIP_INFO,				UP_BUTTON_SHORT_PRESS,					HOME_SET_BIKE_TRIPA_TRIP_HOLD,				&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_BIKE_TRIPA_TRIP_INFO,				DOWN_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA_TRIP_TIME,				&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_BIKE_TRIPA_TRIP_INFO,				LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_BIKE_TRIPA_TRIP_TIME,				RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA_TRIP_TIME,				NULL			},	
	{HOME_SET_BIKE_TRIPA_TRIP_TIME,				LEFT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA,						NULL			},	
	{HOME_SET_BIKE_TRIPA_TRIP_TIME,				UP_BUTTON_SHORT_PRESS,					HOME_SET_BIKE_TRIPA_TRIP_INFO,				&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_BIKE_TRIPA_TRIP_TIME,				DOWN_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA_TRIP_AVG_SPD,			&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_BIKE_TRIPA_TRIP_TIME,				LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_BIKE_TRIPA_TRIP_AVG_SPD,			RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA_TRIP_AVG_SPD,			NULL			},	
	{HOME_SET_BIKE_TRIPA_TRIP_AVG_SPD,			LEFT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA,						NULL			},	
	{HOME_SET_BIKE_TRIPA_TRIP_AVG_SPD,			UP_BUTTON_SHORT_PRESS,					HOME_SET_BIKE_TRIPA_TRIP_TIME,				&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_BIKE_TRIPA_TRIP_AVG_SPD,			DOWN_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA_TRIP_AVGFUEL,			&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_BIKE_TRIPA_TRIP_AVG_SPD,			LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_BIKE_TRIPA_TRIP_AVGFUEL,			RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA_TRIP_AVGFUEL,			NULL			},	
	{HOME_SET_BIKE_TRIPA_TRIP_AVGFUEL,			LEFT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA,						NULL			},	
	{HOME_SET_BIKE_TRIPA_TRIP_AVGFUEL,			UP_BUTTON_SHORT_PRESS,					HOME_SET_BIKE_TRIPA_TRIP_AVG_SPD,			&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_BIKE_TRIPA_TRIP_AVGFUEL,			DOWN_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA_TRIP_HOLD,				&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_BIKE_TRIPA_TRIP_AVGFUEL,			LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_BIKE_TRIPA_TRIP_HOLD,				RIGHT_BUTTON_LONG_PRESS,				HOME_SET_BIKE_TRIPA_TRIP_HOLD,				&ResetTripA			},	
	{HOME_SET_BIKE_TRIPA_TRIP_HOLD,				LEFT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA,						NULL			},	
	{HOME_SET_BIKE_TRIPA_TRIP_HOLD,				UP_BUTTON_SHORT_PRESS,					HOME_SET_BIKE_TRIPA_TRIP_AVGFUEL,			&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_BIKE_TRIPA_TRIP_HOLD,				DOWN_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPA_TRIP_INFO,				&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_BIKE_TRIPA_TRIP_HOLD,				LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_BIKE_TRIPB_TRIP_INFO,				RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB_TRIP_INFO,				NULL			},	
	{HOME_SET_BIKE_TRIPB_TRIP_INFO,				LEFT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB,						NULL			},	
	{HOME_SET_BIKE_TRIPB_TRIP_INFO,				UP_BUTTON_SHORT_PRESS,					HOME_SET_BIKE_TRIPB_TRIP_HOLD,				&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_BIKE_TRIPB_TRIP_INFO,				DOWN_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB_TRIP_TIME,				&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_BIKE_TRIPB_TRIP_INFO,				LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_BIKE_TRIPB_TRIP_TIME,				RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB_TRIP_TIME,				NULL			},	
	{HOME_SET_BIKE_TRIPB_TRIP_TIME,				LEFT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB,						NULL			},	
	{HOME_SET_BIKE_TRIPB_TRIP_TIME,				UP_BUTTON_SHORT_PRESS,					HOME_SET_BIKE_TRIPB_TRIP_INFO,				&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_BIKE_TRIPB_TRIP_TIME,				DOWN_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB_TRIP_AVG_SPD,			&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_BIKE_TRIPB_TRIP_TIME,				LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_BIKE_TRIPB_TRIP_AVG_SPD,			RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB_TRIP_AVG_SPD,			NULL			},	
	{HOME_SET_BIKE_TRIPB_TRIP_AVG_SPD,			LEFT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB,						NULL			},	
	{HOME_SET_BIKE_TRIPB_TRIP_AVG_SPD,			UP_BUTTON_SHORT_PRESS,					HOME_SET_BIKE_TRIPB_TRIP_TIME,				&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_BIKE_TRIPB_TRIP_AVG_SPD,			DOWN_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB_TRIP_AVGFUEL,			&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_BIKE_TRIPB_TRIP_AVG_SPD,			LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_BIKE_TRIPB_TRIP_AVGFUEL,			RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB_TRIP_AVGFUEL,			NULL			},	
	{HOME_SET_BIKE_TRIPB_TRIP_AVGFUEL,			LEFT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB,						NULL			},	
	{HOME_SET_BIKE_TRIPB_TRIP_AVGFUEL,			UP_BUTTON_SHORT_PRESS,					HOME_SET_BIKE_TRIPB_TRIP_AVG_SPD,			&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_BIKE_TRIPB_TRIP_AVGFUEL,			DOWN_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB_TRIP_HOLD,				&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_BIKE_TRIPB_TRIP_AVGFUEL,			LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL				},		
	
	{HOME_SET_BIKE_TRIPB_TRIP_HOLD,				RIGHT_BUTTON_LONG_PRESS,				HOME_SET_BIKE_TRIPB_TRIP_HOLD,				&ResetTripB			},	
	{HOME_SET_BIKE_TRIPB_TRIP_HOLD,				LEFT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB,						NULL			},	
	{HOME_SET_BIKE_TRIPB_TRIP_HOLD,				UP_BUTTON_SHORT_PRESS,					HOME_SET_BIKE_TRIPB_TRIP_AVGFUEL,			&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_BIKE_TRIPB_TRIP_HOLD,				DOWN_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_TRIPB_TRIP_INFO,				&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_BIKE_TRIPB_TRIP_HOLD,				LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_BIKE_BATTERY_INFO,				RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_BATTERY_INFO,					NULL			},	
	{HOME_SET_BIKE_BATTERY_INFO,				LEFT_BUTTON_SHORT_PRESS,				HOME_SET_BIKE_BATTERY,						NULL			},	
	{HOME_SET_BIKE_BATTERY_INFO,				LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_BRIGHT_LOW,					RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT_LOW,					&Set_BrightnessMode_LOW			},	
	{HOME_SET_DISP_BRIGHT_LOW,					LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT,						NULL			},	
	{HOME_SET_DISP_BRIGHT_LOW,					UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_BRIGHT_AUTO,					&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_BRIGHT_LOW,					DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT_MEDIUM,				&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_BRIGHT_LOW,					LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_BRIGHT_MEDIUM,				RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT_MEDIUM,				&Set_BrightnessMode_Medium			},	
	{HOME_SET_DISP_BRIGHT_MEDIUM,				LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT,						NULL			},	
	{HOME_SET_DISP_BRIGHT_MEDIUM,				UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_BRIGHT_LOW,					&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_BRIGHT_MEDIUM,				DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT_HIGH,					&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_BRIGHT_MEDIUM,				LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_BRIGHT_HIGH,					RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT_HIGH,					&Set_BrightnessMode_High			},	
	{HOME_SET_DISP_BRIGHT_HIGH,					LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT,						NULL			},	
	{HOME_SET_DISP_BRIGHT_HIGH,					UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_BRIGHT_MEDIUM,				&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_BRIGHT_HIGH,					DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT_AUTO,					&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_BRIGHT_HIGH,					LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_BRIGHT_AUTO,					RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT_AUTO,					&Set_BrightnessMode_Auto			},	
	{HOME_SET_DISP_BRIGHT_AUTO,					LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT,						NULL			},	
	{HOME_SET_DISP_BRIGHT_AUTO,					UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_BRIGHT_HIGH,					&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_BRIGHT_AUTO,					DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_BRIGHT_LOW,					&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_BRIGHT_AUTO,					LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_MENU_TRIPB,					RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_TRIPB,					&SetMENU_SELECTION_TRIPB			},	
	{HOME_SET_DISP_MENU_TRIPB,					LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU,							NULL			},	
	{HOME_SET_DISP_MENU_TRIPB,					UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_MENU_VOLUME,					&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_MENU_TRIPB,					DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_FUEL,					&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_MENU_TRIPB,					LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_MENU_FUEL,					RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_FUEL,					&SetMENU_SELECTION_FUEL			},	
	{HOME_SET_DISP_MENU_FUEL,					LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU,							NULL			},	
	{HOME_SET_DISP_MENU_FUEL,					UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_MENU_TRIPB,					&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_MENU_FUEL,					DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_NAVIGATION,				&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_MENU_FUEL,					LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_MENU_NAVIGATION,				RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_NAVIGATION,				&SetMENU_SELECTION_NAVIGATION			},	
	{HOME_SET_DISP_MENU_NAVIGATION,				LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU,							NULL			},	
	{HOME_SET_DISP_MENU_NAVIGATION,				UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_MENU_FUEL,					&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_MENU_NAVIGATION,				DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_GEN_INFO,				&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_MENU_NAVIGATION,				LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_DISP_MENU_GEN_INFO,				RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_GEN_INFO,				&SetMENU_SELECTION_GI			},	
	{HOME_SET_DISP_MENU_GEN_INFO,				LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU,							NULL			},	
	{HOME_SET_DISP_MENU_GEN_INFO,				UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_MENU_NAVIGATION,				&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_MENU_GEN_INFO,				DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_PHONE,					&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_MENU_GEN_INFO,				LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_DISP_MENU_PHONE,					RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_PHONE,					&SetMENU_SELECTION_PHONE			},	
	{HOME_SET_DISP_MENU_PHONE,					LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU,							NULL			},	
	{HOME_SET_DISP_MENU_PHONE,					UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_MENU_GEN_INFO,				&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_MENU_PHONE,					DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_MUSIC,					&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_MENU_PHONE,					LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_DISP_MENU_MUSIC,					RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_MUSIC,					&SetMENU_SELECTION_MUSIC			},	
	{HOME_SET_DISP_MENU_MUSIC,					LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU,							NULL			},	
	{HOME_SET_DISP_MENU_MUSIC,					UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_MENU_PHONE,					&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_MENU_MUSIC,					DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_VOLUME,					&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_MENU_MUSIC,					LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_MENU_VOLUME,					RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_VOLUME,					&SetMENU_SELECTION_VOLUME			},	
	{HOME_SET_DISP_MENU_VOLUME,					LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU,							NULL			},	
	{HOME_SET_DISP_MENU_VOLUME,					UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_MENU_MUSIC,					&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_MENU_VOLUME,					DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_MENU_TRIPB,					&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_MENU_VOLUME,					LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_DATE_TIME_DATE_SET,			RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		&Get_Date_variable			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET,			LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME,					NULL			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET,			UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_DATE_TIME_24_SET,				&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET,			DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_TIME_SET,			&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET,			LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_DATE_TIME_TIME_SET,			RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		&Get_Time_variable			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET,			LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME,					NULL			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET,			UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_DATE_TIME_DATE_SET,			&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET,			DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_24_SET,				&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET,			LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_DATE_TIME_24_SET,			RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_TIME_FORMAT,						NULL			},	
	{HOME_SET_DISP_DATE_TIME_24_SET,			LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME,					NULL			},	
	{HOME_SET_DISP_DATE_TIME_24_SET,			UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_DATE_TIME_TIME_SET,			&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_DATE_TIME_24_SET,			DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_DATE_SET,			&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_DATE_TIME_24_SET,			LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_UNIT_DISTANCE,				RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT_DISTANCE_KM,				NULL			},	
	{HOME_SET_DISP_UNIT_DISTANCE,				LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT,							NULL			},	
	{HOME_SET_DISP_UNIT_DISTANCE,				UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_UNIT_FUELCONS,				&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_UNIT_DISTANCE,				DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT_FUELCONS,				&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_UNIT_DISTANCE,				LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_UNIT_FUELCONS,				RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT_FUELCONS_KMPL,			NULL			},	
	{HOME_SET_DISP_UNIT_FUELCONS,				LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT,							NULL			},	
	{HOME_SET_DISP_UNIT_FUELCONS,				UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_UNIT_DISTANCE,				&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_UNIT_FUELCONS,				DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT_DISTANCE,				&SettingArrow_DownButton_Pressed			},	
	{HOME_SET_DISP_UNIT_FUELCONS,				LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_ABOUT_SW_INFO_DETAILS,			RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_ABOUT_SW_INFO_DETAILS,				NULL			},	
	{HOME_SET_ABOUT_SW_INFO_DETAILS,			LEFT_BUTTON_SHORT_PRESS,				HOME_SET_ABOUT_SW_INFO,						NULL			},	
	{HOME_SET_ABOUT_SW_INFO_DETAILS,			UP_BUTTON_SHORT_PRESS,					HOME_SET_ABOUT_SW_INFO_DETAILS,				NULL			},	
	{HOME_SET_ABOUT_SW_INFO_DETAILS,			DOWN_BUTTON_SHORT_PRESS,				HOME_SET_ABOUT_SW_INFO_DETAILS,				NULL			},
	{HOME_SET_ABOUT_SW_INFO_DETAILS,			LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		RIGHT_BUTTON_LONG_PRESS,				HOME_SET_DISP_DATE_TIME_DATE_SET,			&RTC_Set_Date_Month_year			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,		NULL			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_DATE_SET,			NULL			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		&GUI_Up_Button_Date_Setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		UP_BUTTON_LONG_PRESS,					HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		&GUI_Up_Button_Date_Setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		UP_BUTTON_CONTINUOUS_LONG_PRESS,		HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		&GUI_Up_Button_Date_Setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		&GUI_Down_button_Date_Setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		DOWN_BUTTON_LONG_PRESS,					HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		&GUI_Down_button_Date_Setting			},
	{HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		DOWN_BUTTON_CONTINUOUS_LONG_PRESS,		HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		&GUI_Down_button_Date_Setting			},
	{HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,	RIGHT_BUTTON_LONG_PRESS,				HOME_SET_DISP_DATE_TIME_DATE_SET,			&RTC_Set_Date_Month_year			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,	RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		NULL			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,	LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_DATE_SET,			NULL			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,	UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,		&GUI_Up_Button_Month_Setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,	UP_BUTTON_LONG_PRESS,					HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,		&GUI_Up_Button_Month_Setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,	UP_BUTTON_CONTINUOUS_LONG_PRESS,		HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,		&GUI_Up_Button_Month_Setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,	DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,		&GUI_Down_Button_Month_setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,	DOWN_BUTTON_LONG_PRESS,					HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,		&GUI_Down_Button_Month_setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,	DOWN_BUTTON_CONTINUOUS_LONG_PRESS,		HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,		&GUI_Down_Button_Month_setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_MONTH,	LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},
	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		RIGHT_BUTTON_LONG_PRESS,				HOME_SET_DISP_DATE_TIME_DATE_SET,			&RTC_Set_Date_Month_year			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_DATE_SET_DATE,		NULL			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_DATE_SET,			NULL			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		&GUI_Up_Button_year_Setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		UP_BUTTON_LONG_PRESS,					HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		&GUI_Up_Button_year_Setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		UP_BUTTON_CONTINUOUS_LONG_PRESS,		HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		&GUI_Up_Button_year_Setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		&GUI_Down_Button_Year_setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		DOWN_BUTTON_LONG_PRESS,					HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		&GUI_Down_Button_Year_setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		DOWN_BUTTON_CONTINUOUS_LONG_PRESS,		HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		&GUI_Down_Button_Year_setting			},	
	{HOME_SET_DISP_DATE_TIME_DATE_SET_YEAR,		LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		RIGHT_BUTTON_LONG_PRESS,				HOME_SET_DISP_DATE_TIME_TIME_SET,			&RTC_Set_Time_Hour_Min			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		NULL			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_TIME_SET,			NULL			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		&GUI_Up_Button_Hr_Set_time			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		UP_BUTTON_LONG_PRESS,					HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		&GUI_Up_Button_Hr_Set_time			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		UP_BUTTON_CONTINUOUS_LONG_PRESS,		HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		&GUI_Up_Button_Hr_Set_time			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		&GUI_Down_Button_Hr_Set_time			},
	{HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		DOWN_BUTTON_LONG_PRESS,					HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		&GUI_Down_Button_Hr_Set_time			},
	{HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		DOWN_BUTTON_CONTINUOUS_LONG_PRESS,		HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		&GUI_Down_Button_Hr_Set_time			},
	{HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		RIGHT_BUTTON_LONG_PRESS,				HOME_SET_DISP_DATE_TIME_TIME_SET,			&RTC_Set_Time_Hour_Min			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	&GUI_Check_12Hr_Time_Format			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_TIME_SET,			NULL			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		&GUI_Up_Button_Min_Set_time			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		UP_BUTTON_LONG_PRESS,					HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		&GUI_Up_Button_Min_Set_time			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		UP_BUTTON_CONTINUOUS_LONG_PRESS,		HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		&GUI_Up_Button_Min_Set_time			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		&GUI_Down_Button_Min_Set_time			},
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		DOWN_BUTTON_LONG_PRESS,					HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		&GUI_Down_Button_Min_Set_time			},
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		DOWN_BUTTON_CONTINUOUS_LONG_PRESS,		HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		&GUI_Down_Button_Min_Set_time			},
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MIN,		LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	RIGHT_BUTTON_LONG_PRESS,				HOME_SET_DISP_DATE_TIME_TIME_SET,			&RTC_Set_Time_Hour_Min			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_TIME_SET_HR,		NULL		},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_TIME_SET,			NULL			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	&GUI_UP_Button_Merdian_Set_time			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	UP_BUTTON_LONG_PRESS,					HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	&GUI_UP_Button_Merdian_Set_time			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	UP_BUTTON_CONTINUOUS_LONG_PRESS,		HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	&GUI_UP_Button_Merdian_Set_time			},	
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	&GUI_Down_Button_Merdian_Set_time			},
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	DOWN_BUTTON_LONG_PRESS,					HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	&GUI_Down_Button_Merdian_Set_time			},
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	DOWN_BUTTON_CONTINUOUS_LONG_PRESS,		HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	&GUI_Down_Button_Merdian_Set_time			},
	{HOME_SET_DISP_DATE_TIME_TIME_SET_MERDIAN,	LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_DISP_UNIT_DISTANCE_KM,			RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT_DISTANCE_KM,				NULL			},	
	{HOME_SET_DISP_UNIT_DISTANCE_KM,			LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT_DISTANCE,				NULL			},	
	{HOME_SET_DISP_UNIT_DISTANCE_KM,			UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_UNIT_DISTANCE_KM,				NULL					},	
	{HOME_SET_DISP_UNIT_DISTANCE_KM,			DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT_DISTANCE_KM,				NULL			},	
	{HOME_SET_DISP_UNIT_DISTANCE_KM,			LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},		
	
	{HOME_SET_DISP_UNIT_FUELCONS_KMPL,			RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT_FUELCONS_KMPL,			&Set_Fuel_consumption_unit			},	
	{HOME_SET_DISP_UNIT_FUELCONS_KMPL,			LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT_FUELCONS,				NULL			},	
	{HOME_SET_DISP_UNIT_FUELCONS_KMPL,			UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_UNIT_FURLCONS_L1000,	   		&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_UNIT_FUELCONS_KMPL,			DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT_FURLCONS_L1000,			&SettingArrow_DownButton_Pressed			},
	{HOME_SET_DISP_UNIT_FUELCONS_KMPL,			LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_DISP_UNIT_FURLCONS_L1000,			RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT_FURLCONS_L1000,			&Set_Fuel_consumption_unit			},	
	{HOME_SET_DISP_UNIT_FURLCONS_L1000,			LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT_FUELCONS,				NULL			},	
	{HOME_SET_DISP_UNIT_FURLCONS_L1000,			UP_BUTTON_SHORT_PRESS,					HOME_SET_DISP_UNIT_FUELCONS_KMPL,			&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_DISP_UNIT_FURLCONS_L1000,			DOWN_BUTTON_SHORT_PRESS,				HOME_SET_DISP_UNIT_FUELCONS_KMPL,			&SettingArrow_DownButton_Pressed			},
	{HOME_SET_DISP_UNIT_FURLCONS_L1000,			LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_MUSIC_ARTIST,						RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_MUSIC_ARTIST,						&Music_Setting_Screen_Artist			},	
	{HOME_SET_MUSIC_ARTIST,						LEFT_BUTTON_SHORT_PRESS,				HOME_SET_CONNECT_MUSIC,						NULL			},	
	{HOME_SET_MUSIC_ARTIST,						UP_BUTTON_SHORT_PRESS,					HOME_SET_MUSIC_ALBUM,						&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_MUSIC_ARTIST,						DOWN_BUTTON_SHORT_PRESS,				HOME_SET_MUSIC_GENRE,						&SettingArrow_DownButton_Pressed			},
	{HOME_SET_MUSIC_ARTIST,						LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_MUSIC_ALBUM,						RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_MUSIC_ALBUM,						&Music_Setting_Screen_Album			},	
	{HOME_SET_MUSIC_ALBUM,						LEFT_BUTTON_SHORT_PRESS,				HOME_SET_CONNECT_MUSIC,						NULL			},	
	{HOME_SET_MUSIC_ALBUM,						UP_BUTTON_SHORT_PRESS,					HOME_SET_MUSIC_GENRE,						&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_MUSIC_ALBUM,						DOWN_BUTTON_SHORT_PRESS,				HOME_SET_MUSIC_ARTIST,						&SettingArrow_DownButton_Pressed			},
	{HOME_SET_MUSIC_ALBUM,						LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},	
	
	{HOME_SET_MUSIC_GENRE,						RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_MUSIC_GENRE,						&Music_Setting_Screen_Genre			},	
	{HOME_SET_MUSIC_GENRE,						LEFT_BUTTON_SHORT_PRESS,				HOME_SET_CONNECT_MUSIC,						NULL			},	
	{HOME_SET_MUSIC_GENRE,						UP_BUTTON_SHORT_PRESS,					HOME_SET_MUSIC_ARTIST,						&SettingArrow_UpButton_Pressed					},	
	{HOME_SET_MUSIC_GENRE,						DOWN_BUTTON_SHORT_PRESS,				HOME_SET_MUSIC_ALBUM,						&SettingArrow_DownButton_Pressed			},
	{HOME_SET_MUSIC_GENRE,						LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},
	
	{HOME_SET_TIME_FORMAT,						UP_BUTTON_SHORT_PRESS,					HOME_SET_TIME_FORMAT_12HR,					&SettingArrow_UpButton_Pressed					},
	{HOME_SET_TIME_FORMAT,						DOWN_BUTTON_SHORT_PRESS,				HOME_SET_TIME_FORMAT_12HR,					&SettingArrow_DownButton_Pressed			},
	{HOME_SET_TIME_FORMAT,						LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_24_SET,				NULL			},
	{HOME_SET_TIME_FORMAT,						RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_TIME_FORMAT,						&Set_24HrModeEnable_Setting			},
	{HOME_SET_TIME_FORMAT,						LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL			},
	
	{HOME_SET_TIME_FORMAT_12HR,					UP_BUTTON_SHORT_PRESS,					HOME_SET_TIME_FORMAT,						&SettingArrow_UpButton_Pressed								},
	{HOME_SET_TIME_FORMAT_12HR,					DOWN_BUTTON_SHORT_PRESS,				HOME_SET_TIME_FORMAT,						&SettingArrow_DownButton_Pressed						},
	{HOME_SET_TIME_FORMAT_12HR,					LEFT_BUTTON_SHORT_PRESS,				HOME_SET_DISP_DATE_TIME_24_SET,				NULL						},
	{HOME_SET_TIME_FORMAT_12HR,					RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_TIME_FORMAT_12HR,					&Set_24HrModeEnable_Setting	},
	{HOME_SET_TIME_FORMAT_12HR,					LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL	},
	
	{HOME_SET_RIDER_INFO_SHOW,					UP_BUTTON_SHORT_PRESS,					HOME_SET_RIDER_INFO_SHOW,					NULL						},
	{HOME_SET_RIDER_INFO_SHOW,					DOWN_BUTTON_SHORT_PRESS,				HOME_SET_RIDER_INFO_SHOW,					NULL						},
	{HOME_SET_RIDER_INFO_SHOW,					LEFT_BUTTON_SHORT_PRESS,				HOME_SET_ABOUT_RIDER_INFO,					NULL						},
	{HOME_SET_RIDER_INFO_SHOW,					RIGHT_BUTTON_SHORT_PRESS,				HOME_SET_RIDER_INFO_SHOW,					NULL						},
	{HOME_SET_RIDER_INFO_SHOW,					LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL						},

	{HOME_DISCLAIMER_SHOW,						UP_BUTTON_SHORT_PRESS,					HOME_DISCLAIMER_SHOW,						NULL						},
	{HOME_DISCLAIMER_SHOW,						DOWN_BUTTON_SHORT_PRESS,				HOME_DISCLAIMER_SHOW,						NULL						},
	{HOME_DISCLAIMER_SHOW,						LEFT_BUTTON_SHORT_PRESS,				HOME_SET_ABOUT_REGULA_INFO,					NULL						},
	{HOME_DISCLAIMER_SHOW,						RIGHT_BUTTON_SHORT_PRESS,				HOME_DISCLAIMER_SHOW,						NULL						},
	{HOME_DISCLAIMER_SHOW,						LEFT_BUTTON_LONG_PRESS,					HOME_SCREEN,								NULL						},
	
};



uint8_t ScreenChangeActionIfRequired(void);
extern uint8_t g_NVM_Menu_Selection_Data_u8;

/* 
*	THIS FUNCTION SHALL BE INVOKE IN THE INIT FUNCTION
*/
void CalAndCntEventForScrn(void)
{
	/* LOCAL VARIBALE */
	uint32_t fl_Screen_Index_U32 = 0;

	/* SET THE FIRST EVENT FROM ZERO */
	HMIScreenEventOffsetSt[fl_Screen_Index_U32].Offset_Value = 0;

	/* TRAVERSE AND COUNT FOR ALL THE LOOP */
	for(fl_Screen_Index_U32 = 0u; fl_Screen_Index_U32 < (GUI_SCREEN_LIST_MAX-1) ; fl_Screen_Index_U32++)
	{
		HMIScreenEventOffsetSt[(fl_Screen_Index_U32+1)].Offset_Value = HMIScreenEventOffsetSt[fl_Screen_Index_U32].Offset_Value + HMIScreenInfoSt[fl_Screen_Index_U32].NoOfPossibleEvents;
	}

	SET_BIT(g_NVM_Menu_Selection_Data_u8, MENU_SELECTION_TRIPA);
}


uint8_t Debug_DayNight_mode = 1;

void GUI_mainFunction(void)
{
	/* LOCAL VARIABLES */
	uint32_t fl_StateIDx_Loop_U32 = 0;
	uint32_t fl_StateStartOffset_U32 = 0;
	uint32_t fl_StateSize_U32 = 0;
	uint32_t fl_CrntEvent_U32 = 0;
	uint32_t fl_HMICriteriaRet_U32 = 0;
	uint8_t fl_ScreenChangedStatus_u8 = 0;
	uint8_t fl_CrntScreenMode_U8 = Get_day_night_mode_status();

	/* GET THE CURRENT EVENT FROM THE BUTTON HANDLER */
	fl_CrntEvent_U32 = Get_Event();

	/* CHECK FOR NEW EVENT */
	if(fl_CrntEvent_U32 != 0xFF)
	{
		/*  NEED TO CHANGE THE LOGIC - FOR TIMEBIENG CHECK AND SWITCH CRNT STATE */
		if((fl_CrntEvent_U32 == BLE_PASSCODE_EVENT) || (fl_CrntEvent_U32 == BLE_CALL_EVENT) || (fl_CrntEvent_U32 == BLE_CALL_VOLUME_EVENT))
		{
			/* CHECK FOR THE PASSCODE EVENT */
			if(fl_CrntEvent_U32 == BLE_PASSCODE_EVENT)
			{
				/* SET THE PASSCODE SCREEN */
				SetCrntScreen(HOME_SCREEN_PASSCODE);		
			}
			else if (fl_CrntEvent_U32 == BLE_CALL_EVENT)
			{
				/* SET THE CALLSCREEN */
				SetCrntScreen(HOME_SCREEN_CALL);
			}
			else if (fl_CrntEvent_U32 == BLE_CALL_VOLUME_EVENT)
			{
				/* SET THE CALLSCREEN */
				SetCrntScreen(HOME_SCREEN_VOLUME);				
			}
			else 
			{
				/* Do Nothing */
			}

			/* CHANGE THE SCREEN IF REQUIRED */
			ScreenChangeActionIfRequired();
		}
		else
		{
			/* GET THE START INDEX FOR THE CURRENT INDEX TO TRAVESE AND THE SIZE OF THE STATE*/
			fl_StateStartOffset_U32 = HMIScreenEventOffsetSt[g_CurrentScreen_U32].Offset_Value;
			fl_StateSize_U32 = (HMIScreenEventOffsetSt[g_CurrentScreen_U32].Offset_Value + HMIScreenInfoSt[g_CurrentScreen_U32].NoOfPossibleEvents);

			/* CHECK FOR VALID CONFIGURATION TABLE */
			if(HMIStateDetailsSt[fl_StateStartOffset_U32].HMI_Crnt_State == g_CurrentScreen_U32)
			{
				/* TRAVERSE AND FIND THE CURRENT EVENT AND TAKE CURRESPONDING ACTION */
				for(fl_StateIDx_Loop_U32 = fl_StateStartOffset_U32; fl_StateIDx_Loop_U32 < fl_StateSize_U32; fl_StateIDx_Loop_U32++)
				{
					/* CHECK FOR THE CURRENT EVENT MATCH WITH THE EVENT MAPPED TO THE TABLE */
					if(HMIStateDetailsSt[fl_StateIDx_Loop_U32].HMI_Event_Happend == fl_CrntEvent_U32)
					{
						/* CHECK FOR THE CRITERIA FUNCTION VALID */
						if(HMIStateDetailsSt[fl_StateIDx_Loop_U32].Criteria_Fn != NULL)
						{
							/* CHECK FOR THE CRITERIA FUNCTION JUMP IF VALUE TRUE */
							fl_HMICriteriaRet_U32 = HMIStateDetailsSt[fl_StateIDx_Loop_U32].Criteria_Fn();
						}

						if(fl_HMICriteriaRet_U32 == 0)
						{
							/* CHANGE THE SCREEN INDEX */
							g_PrevScreen_U32 = g_CurrentScreen_U32;
							g_CurrentScreen_U32 = HMIStateDetailsSt[fl_StateIDx_Loop_U32].HMI_Next_State;
						}

						/* SET THE UNIQUE NUMBER AS PER THE CURRENT SCREEN INDEX */
						g_CurrentScreen_Uniqued_U32 = HMIScreenInfoSt[g_CurrentScreen_U32].Screen_ID;

						/* SCREEN CHANGE ACTION IF REQUIRED	*/
						fl_ScreenChangedStatus_u8 = ScreenChangeActionIfRequired();

						break;
					}
				}
			}
		}
		/* CLEAR EVENT FOR NEXT ITERATION */
		Clear_Event();
	}

	//else /* ELSE REMOVED TO EXECUTE DURING ONCE SCREEN CHANGED */	/* NORMAL OPERATION */
	{
		/* CHECK FOR THE CHANGE IN SCREEN MODE */
		if(g_PrevScreenMode_U32 != fl_CrntScreenMode_U8)
		{
			if((fl_CrntScreenMode_U8 == 1) && (fl_ScreenChangedStatus_u8 == 0))
			{

				/* CHECK FOR VALID FUNCTION */
				if(HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_PrevScreen_U32].Screen_ID].DeInit_Screen != NULL)
				{
					/* DELETE THE SCREEN OBJECTS */
					HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_PrevScreen_U32].Screen_ID].DeInit_Screen();
				}

				/* CHECK FOR VALID FUNCTION */
				if(HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_CurrentScreen_U32].Screen_ID].Init_Screen != NULL)
				{
					/* CREATE THE SCREEN OBJECTS */
					HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_CurrentScreen_U32].Screen_ID].Init_Screen();
				}

			}
			else if( (fl_CrntScreenMode_U8 == 2) && (fl_ScreenChangedStatus_u8 == 0))
			{

				/* CHECK FOR VALID FUNCTION */
				if(HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_PrevScreen_U32].Screen_ID].Day_DeInit_Screen != NULL)
				{
					/* DELETE THE SCREEN OBJECTS */
					HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_PrevScreen_U32].Screen_ID].Day_DeInit_Screen();
				}

				/* CHECK FOR VALID FUNCTION */
				if(HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_CurrentScreen_U32].Screen_ID].Day_Init_Screen != NULL)
				{
					/* CREATE THE SCREEN OBJECTS */
					HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_CurrentScreen_U32].Screen_ID].Day_Init_Screen();
				}

			}
			else{}

			if(fl_CrntScreenMode_U8 == 1)
			{
				if(HMIScreenInfoSt[g_CurrentScreen_U32].EventEntryCallBack_Fn != NULL)
				{
					/* ENTRY CALLBACK FUNCTION INVOKATION */
					HMIScreenInfoSt[g_CurrentScreen_U32].EventEntryCallBack_Fn();
				}
			}
			else
			{
				if(HMIScreenInfoSt[g_CurrentScreen_U32].DayEventEntryCallBack_Fn != NULL)
				{
					/* ENTRY CALLBACK FUNCTION INVOKATION */
					HMIScreenInfoSt[g_CurrentScreen_U32].DayEventEntryCallBack_Fn();
				}
			}
			/* REMEMBER THE CHANGED THE SCREEN MODE */
			g_PrevScreenMode_U32 = fl_CrntScreenMode_U8;
		}


		/* CHECK FOR THE VALID FUCNTION */
		if(fl_CrntScreenMode_U8 == 1)
		{
			/* EXECUTE SCREEN DURING FUNCTION */
			if(HMIScreenInit_Deinit_List_St[g_CrntScreenIdx_U32].During_Screen != NULL)
			{
				/* EXECUTE FUNCTION */
				HMIScreenInit_Deinit_List_St[g_CrntScreenIdx_U32].During_Screen();
			}
			if(HMIScreenInfoSt[g_CurrentScreen_U32].EventDuringCallBack_Fn != NULL)
			{
				/* FUNCTION INVOKED TO EXECUTION ON THAT SCREEN */
				HMIScreenInfoSt[g_CurrentScreen_U32].EventDuringCallBack_Fn();
			}
			
		}
		else
		{
			/* EXECUTE SCREEN DURING FUNCTION */
			if(HMIScreenInit_Deinit_List_St[g_CrntScreenIdx_U32].Day_During_Screen != NULL)
			{
				/* EXECUTE FUNCTION */
				HMIScreenInit_Deinit_List_St[g_CrntScreenIdx_U32].Day_During_Screen();
			}

			if(HMIScreenInfoSt[g_CurrentScreen_U32].DayEventDuringCallBack_Fn != NULL)
			{
				/* FUNCTION INVOKED TO EXECUTION ON THAT SCREEN */
				HMIScreenInfoSt[g_CurrentScreen_U32].DayEventDuringCallBack_Fn();
			}
		}
	}
}


void SetCrntScreen(uint32_t RequestedScrn)
{
	g_PrevScreen_U32 = g_CurrentScreen_U32;
	g_CurrentScreen_U32 = RequestedScrn;
}

uint32_t GetCrntScreen(void)
{
	return g_CurrentScreen_U32;
}

uint8_t ScreenChangeActionIfRequired(void)
{
	/* LOCAL VARIABLE */
	uint8_t fl_ret_u8 = 0u;
	uint8_t fl_CrntScreenMode_U8 = Get_day_night_mode_status();


	/* CHECK FOR SCREEN CHANGE */
	if(HMIScreenInfoSt[g_CurrentScreen_U32].Screen_ID != HMIScreenInfoSt[g_PrevScreen_U32].Screen_ID)
	{
		/* SET THE CURRENT SCREEN INDEX */
		g_CrntScreenIdx_U32 = HMIScreenInfoSt[g_CurrentScreen_U32].Screen_ID;

		/* CHECK IF CRNT MODE IS NIGHT MODE - PROPER EXIT SEQUENCE */
		if(fl_CrntScreenMode_U8 == 1)
		{
			/* CHECK FOR VALID FUNCTION */
			if(HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_PrevScreen_U32].Screen_ID].DeInit_Screen != NULL)
			{
				/* DELETE THE SCREEN OBJECTS */
				HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_PrevScreen_U32].Screen_ID].DeInit_Screen();
			}

			/* CHECK FOR VALID FUNCTION */
			if(HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_CurrentScreen_U32].Screen_ID].Init_Screen != NULL)
			{
				/* CREATE THE SCREEN OBJECTS */
				HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_CurrentScreen_U32].Screen_ID].Init_Screen();
			}
		}
		else
		{
			/* CHECK FOR VALID FUNCTION */
			if(HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_PrevScreen_U32].Screen_ID].Day_DeInit_Screen != NULL)
			{
				/* DELETE THE SCREEN OBJECTS */
				HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_PrevScreen_U32].Screen_ID].Day_DeInit_Screen();
			}

			/* CHECK FOR VALID FUNCTION */
			if(HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_CurrentScreen_U32].Screen_ID].Day_Init_Screen != NULL)
			{
				/* CREATE THE SCREEN OBJECTS */
				HMIScreenInit_Deinit_List_St[HMIScreenInfoSt[g_CurrentScreen_U32].Screen_ID].Day_Init_Screen();
			}
		
		}

		fl_ret_u8 = 1;
	}

	/* CHECK FOR THE SCREEN CHANGED STATUS - IF SCREEN CHANGED EXIT FINCTION SHALL NOT BE INVOKED BECAUSE THE OBJECT WILL BE DEINIT IN TJE SCREEN CHANGE ACTIVITY */
	if(fl_ret_u8 != 1)
	{
		/* CHECK IF CRNT MODE IS NIGHT MODE - PROPER EXIT SEQUENCE */
		if(fl_CrntScreenMode_U8 == 1)
		{
			/* CHECK FOR VALID EXIT CALLBACK */
			if(HMIScreenInfoSt[g_PrevScreen_U32].EventExitCallBack_Fn != NULL)
			{
				/* EXIT CALLBACK FUNCTION INVOKATION */
				HMIScreenInfoSt[g_PrevScreen_U32].EventExitCallBack_Fn();
			}
		}
		else
		{
			/* CHECK FOR VALID EXIT CALLBACK */
			if(HMIScreenInfoSt[g_PrevScreen_U32].DayEventExitCallBack_Fn != NULL)
			{
				/* EXIT CALLBACK FUNCTION INVOKATION */
				HMIScreenInfoSt[g_PrevScreen_U32].DayEventExitCallBack_Fn();
			}
		}
	}

	/* CHECK IF CRNT MODE IS NIGHT MODE - PROPER ENTRY SEQUENCE */
	if(fl_CrntScreenMode_U8 == 1)
	{
		/* CHECK FOR VALID FUNCTION MAPPED */
		if(HMIScreenInfoSt[g_CurrentScreen_U32].EventEntryCallBack_Fn != NULL)
		{
			/* ENTRY CALLBACK FUNCTION INVOKATION */
			HMIScreenInfoSt[g_CurrentScreen_U32].EventEntryCallBack_Fn();
		}
	}
	else
	{
		if(HMIScreenInfoSt[g_CurrentScreen_U32].DayEventEntryCallBack_Fn != NULL)
		{
			/* ENTRY CALLBACK FUNCTION INVOKATION */
			HMIScreenInfoSt[g_CurrentScreen_U32].DayEventEntryCallBack_Fn();
		}
	}

	return fl_ret_u8;
}
/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/

void HMI_Main_Screen_Init(void)
{
    /* Initialize home screen as default screen when move to Main screen in display*/
    g_HMI_Main_Screen_PST_State_u8 = HMI_PST_HOME_MAIN_SCREEN;

    g_HMI_Last_Intermediate_Screen = HMI_PST_TRIP_A_MAIN_SCREEN;    

	g_Main_To_Other_Screen_Change_Req_Status = FALSE;

	g_Main_Screen_Cnt = 0;

	/* MOVE THIS AND INVOKE IN THE INIT FUNCTION */
	CalAndCntEventForScrn();
}


void HMI_Main_Screen_Cold_Init(void)
{
    /* Restore last screen was alive in main screen before move to other screen */
    g_HMI_Main_Screen_PST_State_u8 = HMI_PST_HOME_MAIN_SCREEN;

	g_Main_To_Other_Screen_Change_Req_Status = FALSE;
}

void HMI_Intermediate_Screen_Cold_Init(void)
{
	/* Restore last screen was alive in main screen before move to other screen */
    g_HMI_Main_Screen_PST_State_u8 = g_HMI_Last_Intermediate_Screen;

	g_Main_To_Other_Screen_Change_Req_Status = FALSE;
}


uint8_t Test_fun(void)
{
	return (g_Main_Screen_Cnt);
}


void HMI_Load_Intermediate_Screen(void)
{

	lv_obj_set_pos(guider_ui.screen_trip_spedo_s1, 76, 2);
	lv_obj_set_size(guider_ui.screen_trip_spedo_s1, 24, 47);

    lv_obj_set_pos(guider_ui.screen_trip_spedo_s2, 46,2 );
    lv_obj_set_size(guider_ui.screen_trip_spedo_s2, 24, 47);

	lv_obj_set_pos(guider_ui.screen_trip_spedo_s3, 17, 2);
	lv_obj_set_size(guider_ui.screen_trip_spedo_s3, 24, 47);

	lv_img_set_src(guider_ui.screen_imgKmph,&_txt_night_speed_unit_33x19);
	
	set_obj_opa(guider_ui.screen_imgKmph,255);

}



/***************************************************************************************************************************/
/*HOME_SCREEN_ADDED*/
/***************************************************************************************************************************/


void GUI_Speed_Day_Entry(void)
{
    lv_img_set_src(guider_ui.screen_SC_3,&txt_night_speed_line_3_white0);	

	lv_img_set_src(guider_ui.screen_SC_2,&txt_night_speed_line_3_grey0);

	lv_img_set_src(guider_ui.screen_SC_1,&txt_night_speed_line_3_grey0);
}

void GUI_Speed_Night_Entry(void)
{
     lv_img_set_src(guider_ui.screen_SC_3,&txt_night_speed_line_3_white0);	

	lv_img_set_src(guider_ui.screen_SC_2,&txt_night_speed_line_3_grey0);

	lv_img_set_src(guider_ui.screen_SC_1,&txt_night_speed_line_3_grey0);
}


void GUI_Main_Screen_Night_Exit(void)
{
	lv_obj_add_flag(guider_ui.screen_D_B_Icon,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_navi_container,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_navi_container,LV_OBJ_FLAG_HIDDEN);

	lv_obj_add_flag(guider_ui.screen_bl_pass_container,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_bl_pass_container,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_container,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_phone_container,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_volume_container,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_ghost_image,LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_Sub_Button,LV_OBJ_FLAG_HIDDEN);	
}



void GUI_Gear_Day_Entry(void)
{
    lv_label_set_text(guider_ui.screen_Gear_Position_Number,"N");
	lv_obj_set_style_text_color(guider_ui.screen_Gear_Position_Number, lv_color_Green(), 0);
	set_obj_opa_S(guider_ui.screen_Gear_Position_Number,0);
}

void GUI_Gear_Night_Entry(void)
{

    lv_label_set_text(guider_ui.screen_Gear_Position_Number,"N");
	lv_obj_set_style_text_color(guider_ui.screen_Gear_Position_Number, lv_color_Green(), 0);
	set_obj_opa_S(guider_ui.screen_Gear_Position_Number,0);

}

void Main_Screen_night_obj_create(lv_ui *ui)
{
	ui->screen = lv_obj_create(NULL);
	
	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	lv_style_reset(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_screen_main_main_default, 255);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	ui->screen_skin = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_skin, 0, 0);
	lv_obj_set_size(ui->screen_skin, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_screen_skin_main_main_default
	static lv_style_t style_screen_skin_main_main_default;
	lv_style_reset(&style_screen_skin_main_main_default);
	lv_style_set_img_recolor(&style_screen_skin_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_skin_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_skin_main_main_default, 255);
	lv_obj_add_style(ui->screen_skin, &style_screen_skin_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_skin, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_skin,&_Skin_BG_240x320);
	lv_img_set_pivot(ui->screen_skin, 0,0);
	lv_img_set_angle(ui->screen_skin, 0);

	//Write codes screen_FogLampTT
	ui->screen_FogLampTT = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_FogLampTT, 10, 11);
	lv_obj_set_size(ui->screen_FogLampTT, 24, 21);

	//Write style state: LV_STATE_DEFAULT for style_screen_foglamptt_main_main_default
	static lv_style_t style_screen_foglamptt_main_main_default;
	lv_style_reset(&style_screen_foglamptt_main_main_default);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_foglamptt_main_main_default, 255);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_foglamptt_main_main_pressed
	static lv_style_t style_screen_foglamptt_main_main_pressed;
	lv_style_reset(&style_screen_foglamptt_main_main_pressed);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_foglamptt_main_main_checked
	static lv_style_t style_screen_foglamptt_main_main_checked;
	lv_style_reset(&style_screen_foglamptt_main_main_checked);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_checked, 0);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_FogLampTT, LV_IMGBTN_STATE_RELEASED, NULL, &_Layer_0_alpha_24x20, NULL);
	lv_imgbtn_set_src(ui->screen_FogLampTT, LV_IMGBTN_STATE_PRESSED, NULL, &new_header_fog_telltale, NULL);
	lv_obj_add_flag(ui->screen_FogLampTT, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_imgEngineTT
	ui->screen_imgEngineTT = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgEngineTT, 204, 12);
	lv_obj_set_size(ui->screen_imgEngineTT, 26, 18);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgenginett_main_main_default
	static lv_style_t style_screen_imgenginett_main_main_default;
	lv_style_reset(&style_screen_imgenginett_main_main_default);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgenginett_main_main_default, 255);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgenginett_main_main_pressed
	static lv_style_t style_screen_imgenginett_main_main_pressed;
	lv_style_reset(&style_screen_imgenginett_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgenginett_main_main_checked
	static lv_style_t style_screen_imgenginett_main_main_checked;
	lv_style_reset(&style_screen_imgenginett_main_main_checked);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgEngineTT, LV_IMGBTN_STATE_RELEASED, NULL, &new_engine_telltale, NULL);
	lv_imgbtn_set_src(ui->screen_imgEngineTT, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_25x17, NULL);
	lv_obj_add_flag(ui->screen_imgEngineTT, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_imgKmph
	ui->screen_imgKmph = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgKmph, 189, 150);
	lv_obj_set_size(ui->screen_imgKmph, 33, 19);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgkmph_main_main_default
	static lv_style_t style_screen_imgkmph_main_main_default;
	lv_style_reset(&style_screen_imgkmph_main_main_default);
	lv_style_set_img_recolor(&style_screen_imgkmph_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgkmph_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgkmph_main_main_default, 0);
	lv_obj_add_style(ui->screen_imgKmph, &style_screen_imgkmph_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_imgKmph, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_imgKmph,&_txt_night_speed_unit_33x19);
	lv_img_set_pivot(ui->screen_imgKmph, 0,0);
	lv_img_set_angle(ui->screen_imgKmph, 0);	


	//Write codes screen_E_F_Img
	ui->screen_E_F_Img = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_E_F_Img, 38, 254);
	lv_obj_set_size(ui->screen_E_F_Img, 13, 15);

	//Write style state: LV_STATE_DEFAULT for style_screen_e_f_img_main_main_default
	static lv_style_t style_screen_e_f_img_main_main_default;
	lv_style_reset(&style_screen_e_f_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_e_f_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_e_f_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_e_f_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_E_F_Img, &style_screen_e_f_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_E_F_Img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_E_F_Img,&_img_night_fuel_E_13x15);
	lv_img_set_pivot(ui->screen_E_F_Img, 0,0);
	lv_img_set_angle(ui->screen_E_F_Img, 0);

	//Write codes screen_F_Img
	ui->screen_F_Img = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_F_Img, 190, 252);
	lv_obj_set_size(ui->screen_F_Img, 10, 16);

	//Write style state: LV_STATE_DEFAULT for style_screen_f_img_main_main_default
	static lv_style_t style_screen_f_img_main_main_default;
	lv_style_reset(&style_screen_f_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_f_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_f_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_f_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_F_Img, &style_screen_f_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_F_Img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_F_Img,&_img_night_fuel_F_10x16);
	lv_img_set_pivot(ui->screen_F_Img, 0,0);
	lv_img_set_angle(ui->screen_F_Img, 0);	

	//Write codes screen_Fuelbar0
	ui->screen_Fuelbar0 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuelbar0, 41, 266);
	lv_obj_set_size(ui->screen_Fuelbar0, 158, 43);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuelbar0_main_main_default
	static lv_style_t style_screen_fuelbar0_main_main_default;
	lv_style_reset(&style_screen_fuelbar0_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuelbar0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuelbar0_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuelbar0_main_main_default, 255);
	lv_obj_add_style(ui->screen_Fuelbar0, &style_screen_fuelbar0_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuelbar0, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuelbar0,&img_fuel_grey_bg_white_icon);
	lv_img_set_pivot(ui->screen_Fuelbar0, 0,0);
	lv_img_set_angle(ui->screen_Fuelbar0, 0);

	//Write codes screen_Clock_hour
	ui->screen_Clock_hour = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Clock_hour, 86, 69);
	lv_obj_set_size(ui->screen_Clock_hour, 13, 12);
	lv_label_set_text(ui->screen_Clock_hour, "24");
	lv_label_set_long_mode(ui->screen_Clock_hour, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Clock_hour, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_hour_main_main_default
	static lv_style_t style_screen_clock_hour_main_main_default;
	lv_style_reset(&style_screen_clock_hour_main_main_default);
	lv_style_set_radius(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_clock_hour_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_clock_hour_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_clock_hour_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_text_color(&style_screen_clock_hour_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_clock_hour_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_clock_hour_main_main_default, 0);
	lv_obj_add_style(ui->screen_Clock_hour, &style_screen_clock_hour_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Clock_min
	ui->screen_Clock_min = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Clock_min, 113, 69);
	lv_obj_set_size(ui->screen_Clock_min, 15, 12);
	lv_label_set_text(ui->screen_Clock_min, "60");
	lv_label_set_long_mode(ui->screen_Clock_min, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Clock_min, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_min_main_main_default
	static lv_style_t style_screen_clock_min_main_main_default;
	lv_style_reset(&style_screen_clock_min_main_main_default);
	lv_style_set_radius(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_clock_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_clock_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_clock_min_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_text_color(&style_screen_clock_min_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_clock_min_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_clock_min_main_main_default, 0);
	lv_obj_add_style(ui->screen_Clock_min, &style_screen_clock_min_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Clock_Colan
	ui->screen_Clock_Colan = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Clock_Colan, 109, 69);
	lv_obj_set_size(ui->screen_Clock_Colan, 3, 10);
	lv_label_set_text(ui->screen_Clock_Colan, ":");
	lv_label_set_long_mode(ui->screen_Clock_Colan, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Clock_Colan, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_colan_main_main_default
	static lv_style_t style_screen_clock_colan_main_main_default;
	lv_style_reset(&style_screen_clock_colan_main_main_default);
	lv_style_set_radius(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_clock_colan_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_clock_colan_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_clock_colan_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_text_color(&style_screen_clock_colan_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_clock_colan_main_main_default, &lv_font_FjallaOne_Regular_15);
	lv_style_set_text_letter_space(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_clock_colan_main_main_default, 0);
	lv_obj_add_style(ui->screen_Clock_Colan, &style_screen_clock_colan_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_TachoBarBlank
	ui->screen_TachoBarBlank = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBarBlank, 3, 8);
	lv_obj_set_size(ui->screen_TachoBarBlank, 231, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobarblank_main_main_default
	static lv_style_t style_screen_tachobarblank_main_main_default;
	lv_style_reset(&style_screen_tachobarblank_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobarblank_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobarblank_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobarblank_main_main_default, 0);
	lv_obj_add_style(ui->screen_TachoBarBlank, &style_screen_tachobarblank_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBarBlank, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBarBlank,&_Layer_0_231x78);
	lv_img_set_pivot(ui->screen_TachoBarBlank, 0,0);
	lv_img_set_angle(ui->screen_TachoBarBlank, 0);

	//Write codes screen_Gear_UP_Advisory
	ui->screen_Gear_UP_Advisory = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_Gear_UP_Advisory, 30, 134);
	lv_obj_set_size(ui->screen_Gear_UP_Advisory, 15, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_up_advisory_main_main_default
	static lv_style_t style_screen_gear_up_advisory_main_main_default;
	lv_style_reset(&style_screen_gear_up_advisory_main_main_default);
	lv_style_set_text_color(&style_screen_gear_up_advisory_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_gear_up_advisory_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_up_advisory_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_up_advisory_main_main_default, 254);
	lv_obj_add_style(ui->screen_Gear_UP_Advisory, &style_screen_gear_up_advisory_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_gear_up_advisory_main_main_pressed
	static lv_style_t style_screen_gear_up_advisory_main_main_pressed;
	lv_style_reset(&style_screen_gear_up_advisory_main_main_pressed);
	lv_style_set_text_color(&style_screen_gear_up_advisory_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_gear_up_advisory_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_gear_up_advisory_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_Gear_UP_Advisory, &style_screen_gear_up_advisory_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_gear_up_advisory_main_main_checked
	static lv_style_t style_screen_gear_up_advisory_main_main_checked;
	lv_style_reset(&style_screen_gear_up_advisory_main_main_checked);
	lv_style_set_text_color(&style_screen_gear_up_advisory_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_gear_up_advisory_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_gear_up_advisory_main_main_checked, 0);
	lv_obj_add_style(ui->screen_Gear_UP_Advisory, &style_screen_gear_up_advisory_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_Gear_UP_Advisory, LV_IMGBTN_STATE_RELEASED, NULL, &_img_night_gear_arrows_up_grey_13x9, NULL);
	lv_imgbtn_set_src(ui->screen_Gear_UP_Advisory, LV_IMGBTN_STATE_PRESSED, NULL, &new_night_gear_arrows_up_white, NULL);
	lv_obj_add_flag(ui->screen_Gear_UP_Advisory, LV_OBJ_FLAG_CHECKABLE);


	//Write codes screen_Gear_Down_Advisory
	ui->screen_Gear_Down_Advisory = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_Gear_Down_Advisory, 30, 177);
	lv_obj_set_size(ui->screen_Gear_Down_Advisory, 15, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_down_advisory_main_main_default
	static lv_style_t style_screen_gear_down_advisory_main_main_default;
	lv_style_reset(&style_screen_gear_down_advisory_main_main_default);
	lv_style_set_text_color(&style_screen_gear_down_advisory_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_gear_down_advisory_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_down_advisory_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_down_advisory_main_main_default, 253);
	lv_obj_add_style(ui->screen_Gear_Down_Advisory, &style_screen_gear_down_advisory_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_gear_down_advisory_main_main_pressed
	static lv_style_t style_screen_gear_down_advisory_main_main_pressed;
	lv_style_reset(&style_screen_gear_down_advisory_main_main_pressed);
	lv_style_set_text_color(&style_screen_gear_down_advisory_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_gear_down_advisory_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_gear_down_advisory_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_Gear_Down_Advisory, &style_screen_gear_down_advisory_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_gear_down_advisory_main_main_checked
	static lv_style_t style_screen_gear_down_advisory_main_main_checked;
	lv_style_reset(&style_screen_gear_down_advisory_main_main_checked);
	lv_style_set_text_color(&style_screen_gear_down_advisory_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_gear_down_advisory_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_gear_down_advisory_main_main_checked, 0);
	lv_obj_add_style(ui->screen_Gear_Down_Advisory, &style_screen_gear_down_advisory_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_Gear_Down_Advisory, LV_IMGBTN_STATE_RELEASED, NULL, &_img_night_gear_arrows_down_grey_13x9, NULL);
	lv_imgbtn_set_src(ui->screen_Gear_Down_Advisory, LV_IMGBTN_STATE_PRESSED, NULL, &new_night_gear_arrows_down_white, NULL);
	lv_obj_add_flag(ui->screen_Gear_Down_Advisory, LV_OBJ_FLAG_CHECKABLE);

	
	//Write codes screen_Service_Due
	ui->screen_Service_Due = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_Service_Due, 207, 234);
	lv_obj_set_size(ui->screen_Service_Due, 25, 25);

	//Write style state: LV_STATE_DEFAULT for style_screen_service_due_main_main_default
	static lv_style_t style_screen_service_due_main_main_default;
	lv_style_reset(&style_screen_service_due_main_main_default);
	lv_style_set_text_color(&style_screen_service_due_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_default, 3);
	lv_style_set_img_opa(&style_screen_service_due_main_main_default, 255);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_move_foreground(ui->screen_Service_Due);
	

	//Write style state: LV_STATE_PRESSED for style_screen_service_due_main_main_pressed
	static lv_style_t style_screen_service_due_main_main_pressed;
	lv_style_reset(&style_screen_service_due_main_main_pressed);
	lv_style_set_text_color(&style_screen_service_due_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_service_due_main_main_checked
	static lv_style_t style_screen_service_due_main_main_checked;
	lv_style_reset(&style_screen_service_due_main_main_checked);
	lv_style_set_text_color(&style_screen_service_due_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_checked, 0);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_Service_Due, LV_IMGBTN_STATE_RELEASED, NULL, &img_Service_Remainder_25x25, NULL);
	lv_imgbtn_set_src(ui->screen_Service_Due, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_22x25, NULL);
	lv_obj_add_flag(ui->screen_Service_Due, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_TachoBar0
	ui->screen_TachoBar0 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBar0, 7, 6);
	lv_obj_set_size(ui->screen_TachoBar0, 227, 75);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobar0_main_main_default
	static lv_style_t style_screen_tachobar0_main_main_default;
	lv_style_reset(&style_screen_tachobar0_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobar0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobar0_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobar0_main_main_default, 255);
	lv_obj_add_style(ui->screen_TachoBar0, &style_screen_tachobar0_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBar0, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBar0,&img_tacho_chaplets);
	lv_img_set_pivot(ui->screen_TachoBar0, 0,0);
	lv_img_set_angle(ui->screen_TachoBar0, 0);


	//Write codes screen_TachoBar0_1
	ui->screen_TachoBar0_1 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBar0_1, 3, 8);
	lv_obj_set_size(ui->screen_TachoBar0_1, 231, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobar0_1_main_main_default
	static lv_style_t style_screen_tachobar0_1_main_main_default;
	lv_style_reset(&style_screen_tachobar0_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobar0_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobar0_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobar0_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_TachoBar0_1, &style_screen_tachobar0_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBar0_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBar0_1,&_img_night_tacho_fill_001_231x78);
	lv_img_set_pivot(ui->screen_TachoBar0_1, 0,0);
	lv_img_set_angle(ui->screen_TachoBar0_1, 0);
	//set_obj_opa(ui->screen_TachoBar0_1, 255);

	//Write codes screen_Fuel_Img_Icon
	ui->screen_Fuel_Img_Icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuel_Img_Icon, 105, 248);
	lv_obj_set_size(ui->screen_Fuel_Img_Icon, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuel_img_icon_main_main_default
	static lv_style_t style_screen_fuel_img_icon_main_main_default;
	lv_style_reset(&style_screen_fuel_img_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuel_img_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuel_img_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuel_img_icon_main_main_default, 0);
	lv_obj_add_style(ui->screen_Fuel_Img_Icon, &style_screen_fuel_img_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuel_Img_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuel_Img_Icon,&_img_night_display_units_fuel_icon_30x30);
	lv_img_set_pivot(ui->screen_Fuel_Img_Icon, 0,0);
	lv_img_set_angle(ui->screen_Fuel_Img_Icon, 0);

	//Write codes screen_imgOilTelltale
	ui->screen_imgOilTelltale = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgOilTelltale, 4, 290);
	lv_obj_set_size(ui->screen_imgOilTelltale, 34, 14);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgoiltelltale_main_main_default
	static lv_style_t style_screen_imgoiltelltale_main_main_default;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_default);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgoiltelltale_main_main_default, 254);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgoiltelltale_main_main_pressed
	static lv_style_t style_screen_imgoiltelltale_main_main_pressed;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgoiltelltale_main_main_checked
	static lv_style_t style_screen_imgoiltelltale_main_main_checked;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_checked);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgOilTelltale, LV_IMGBTN_STATE_RELEASED, NULL, &new_oil_telltale, NULL);
	lv_imgbtn_set_src(ui->screen_imgOilTelltale, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_32x13, NULL);
	lv_obj_add_flag(ui->screen_imgOilTelltale, LV_OBJ_FLAG_CHECKABLE);

		//Write codes screen_x1000RPM_Img
	ui->screen_x1000RPM_Img = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_x1000RPM_Img, 94, 53);
	lv_obj_set_size(ui->screen_x1000RPM_Img, 51, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_x1000rpm_img_main_main_default
	static lv_style_t style_screen_x1000rpm_img_main_main_default;
	lv_style_reset(&style_screen_x1000rpm_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_x1000rpm_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_x1000rpm_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_x1000rpm_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_x1000RPM_Img, &style_screen_x1000rpm_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_x1000RPM_Img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_x1000RPM_Img,&_1000_RPM_49x13);
	lv_img_set_pivot(ui->screen_x1000RPM_Img, 0,0);
	lv_img_set_angle(ui->screen_x1000RPM_Img, 0);

	//Write codes screen_Batt_Outline
		ui->screen_Batt_Outline = lv_img_create(ui->screen);
		lv_obj_set_pos(ui->screen_Batt_Outline, 26, 111);
		lv_obj_set_size(ui->screen_Batt_Outline, 20, 12);

		//Write style state: LV_STATE_DEFAULT for style_screen_batt_outline_main_main_default
		static lv_style_t style_screen_batt_outline_main_main_default;
		lv_style_reset(&style_screen_batt_outline_main_main_default);
		lv_style_set_img_recolor(&style_screen_batt_outline_main_main_default, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_img_recolor_opa(&style_screen_batt_outline_main_main_default, 0);
		lv_style_set_img_opa(&style_screen_batt_outline_main_main_default, 255);
		lv_obj_add_style(ui->screen_Batt_Outline, &style_screen_batt_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_add_flag(ui->screen_Batt_Outline, LV_OBJ_FLAG_CLICKABLE);
		lv_img_set_src(ui->screen_Batt_Outline,&_Layer_0_9x9);
		lv_img_set_pivot(ui->screen_Batt_Outline, 0,0);
		lv_img_set_angle(ui->screen_Batt_Outline, 0);		

		//Write codes screen_Signal_1
		ui->screen_Signal_1 = lv_img_create(ui->screen);
		lv_obj_set_pos(ui->screen_Signal_1, 200, 111);
		lv_obj_set_size(ui->screen_Signal_1, 14, 12);

		//Write style state: LV_STATE_DEFAULT for style_screen_signal_1_main_main_default
		static lv_style_t style_screen_signal_1_main_main_default;
		lv_style_reset(&style_screen_signal_1_main_main_default);
		lv_style_set_img_recolor(&style_screen_signal_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_img_recolor_opa(&style_screen_signal_1_main_main_default, 0);
		lv_style_set_img_opa(&style_screen_signal_1_main_main_default, 255);
		lv_obj_add_style(ui->screen_Signal_1, &style_screen_signal_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_add_flag(ui->screen_Signal_1, LV_OBJ_FLAG_CLICKABLE);
		lv_img_set_src(ui->screen_Signal_1,&_Layer_0_9x9);
		lv_img_set_pivot(ui->screen_Signal_1, 0,0);
		lv_img_set_angle(ui->screen_Signal_1, 0);

		//Write codes screen_contSp_Main_2
	ui->screen_contSp_Main_2 = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_contSp_Main_2, 56, 120);
	lv_obj_set_size(ui->screen_contSp_Main_2, 136, 123);

	//Write style state: LV_STATE_DEFAULT for style_screen_contsp_main_2_main_main_default
	static lv_style_t style_screen_contsp_main_2_main_main_default;
	lv_style_reset(&style_screen_contsp_main_2_main_main_default);
	lv_style_set_radius(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_contsp_main_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_contsp_main_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_contsp_main_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_contsp_main_2_main_main_default, 255);
	lv_style_set_border_color(&style_screen_contsp_main_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_contsp_main_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_contSp_Main_2, &style_screen_contsp_main_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_con_odo_val
	ui->screen_con_odo_val = lv_label_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_con_odo_val, 38, 99);
	lv_obj_set_size(ui->screen_con_odo_val, 69, 19);
	lv_label_set_text(ui->screen_con_odo_val, "0");
	lv_label_set_long_mode(ui->screen_con_odo_val, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_con_odo_val, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_con_odo_val_main_main_default
	static lv_style_t style_screen_con_odo_val_main_main_default;
	lv_style_reset(&style_screen_con_odo_val_main_main_default);
	lv_style_set_radius(&style_screen_con_odo_val_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_con_odo_val_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_con_odo_val_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_con_odo_val_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_con_odo_val_main_main_default, 255);
	lv_style_set_text_color(&style_screen_con_odo_val_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_con_odo_val_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_con_odo_val_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_con_odo_val_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_con_odo_val_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_con_odo_val_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_con_odo_val_main_main_default, 0);
	lv_obj_add_style(ui->screen_con_odo_val, &style_screen_con_odo_val_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Codo
	ui->screen_Codo = lv_img_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_Codo, 2, 103);
	lv_obj_set_size(ui->screen_Codo, 27, 14);

	//Write style state: LV_STATE_DEFAULT for style_screen_codo_main_main_default
	static lv_style_t style_screen_codo_main_main_default;
	lv_style_reset(&style_screen_codo_main_main_default);
	lv_style_set_img_recolor(&style_screen_codo_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_codo_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_codo_main_main_default, 255);
	lv_obj_add_style(ui->screen_Codo, &style_screen_codo_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Codo, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Codo,&_txt_night_odo_27x14);
	lv_img_set_pivot(ui->screen_Codo, 0,0);
	lv_img_set_angle(ui->screen_Codo, 0);

	//Write codes screen_conkm
	ui->screen_conkm = lv_img_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_conkm, 110, 102);
	lv_obj_set_size(ui->screen_conkm, 20, 15);

	//Write style state: LV_STATE_DEFAULT for style_screen_conkm_main_main_default
	static lv_style_t style_screen_conkm_main_main_default;
	lv_style_reset(&style_screen_conkm_main_main_default);
	lv_style_set_img_recolor(&style_screen_conkm_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_conkm_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_conkm_main_main_default, 255);
	lv_obj_add_style(ui->screen_conkm, &style_screen_conkm_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_conkm, LV_OBJ_FLAG_CLICKABLE);
	//lv_img_set_src(ui->screen_conkm,&_txt_night_odo_unit_20x15);
	lv_img_set_src(ui->screen_conkm,&txt_night_odo_unit);
	lv_img_set_pivot(ui->screen_conkm, 0,0);
	lv_img_set_angle(ui->screen_conkm, 0);

	//Write codes screen_SC_1
	ui->screen_SC_1 = lv_img_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_SC_1, 1, 3);
	lv_obj_set_size(ui->screen_SC_1, 41, 73);

	//Write style state: LV_STATE_DEFAULT for style_screen_sc_1_main_main_default
	static lv_style_t style_screen_sc_1_main_main_default;
	lv_style_reset(&style_screen_sc_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_sc_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_sc_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_sc_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_SC_1, &style_screen_sc_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_SC_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_SC_1,&txt_night_speed_line_3_grey0);
	lv_img_set_pivot(ui->screen_SC_1, 0,0);
	lv_img_set_angle(ui->screen_SC_1, 0);

	//Write codes screen_SC_2
	ui->screen_SC_2 = lv_img_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_SC_2, 42, 3);
	lv_obj_set_size(ui->screen_SC_2, 41, 73);

	//Write style state: LV_STATE_DEFAULT for style_screen_sc_2_main_main_default
	static lv_style_t style_screen_sc_2_main_main_default;
	lv_style_reset(&style_screen_sc_2_main_main_default);
	lv_style_set_img_recolor(&style_screen_sc_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_sc_2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_sc_2_main_main_default, 255);
	lv_obj_add_style(ui->screen_SC_2, &style_screen_sc_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_SC_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_SC_2,&txt_night_speed_line_3_grey0);
	lv_img_set_pivot(ui->screen_SC_2, 0,0);
	lv_img_set_angle(ui->screen_SC_2, 0);

	//Write codes screen_SC_3
	ui->screen_SC_3 = lv_img_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_SC_3, 84, 3);
	lv_obj_set_size(ui->screen_SC_3, 41, 73);

	//Write style state: LV_STATE_DEFAULT for style_screen_sc_3_main_main_default
	static lv_style_t style_screen_sc_3_main_main_default;
	lv_style_reset(&style_screen_sc_3_main_main_default);
	lv_style_set_img_recolor(&style_screen_sc_3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_sc_3_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_sc_3_main_main_default, 255);
	lv_obj_add_style(ui->screen_SC_3, &style_screen_sc_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_SC_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_SC_3,&txt_night_speed_line_3_white0);
	lv_img_set_pivot(ui->screen_SC_3, 0,0);
	lv_img_set_angle(ui->screen_SC_3, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_si_2_main_main_default
	static lv_style_t style_screen_si_2_main_main_default;
	lv_style_reset(&style_screen_si_2_main_main_default);
	lv_style_set_img_recolor(&style_screen_si_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_si_2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_si_2_main_main_default, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_si_3_main_main_default
	static lv_style_t style_screen_si_3_main_main_default;
	lv_style_reset(&style_screen_si_3_main_main_default);
	lv_style_set_img_recolor(&style_screen_si_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_si_3_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_si_3_main_main_default, 0);

	//Write codes screen_Sub_Button
	ui->screen_Sub_Button = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_Sub_Button, 200, 150);
	lv_obj_set_size(ui->screen_Sub_Button, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_screen_sub_button_main_main_default
	static lv_style_t style_screen_sub_button_main_main_default;
	lv_style_reset(&style_screen_sub_button_main_main_default);
	lv_style_set_text_color(&style_screen_sub_button_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_sub_button_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_sub_button_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_sub_button_main_main_default, 255);
	lv_obj_add_style(ui->screen_Sub_Button, &style_screen_sub_button_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_sub_button_main_main_pressed
	static lv_style_t style_screen_sub_button_main_main_pressed;
	lv_style_reset(&style_screen_sub_button_main_main_pressed);
	lv_style_set_text_color(&style_screen_sub_button_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_sub_button_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_sub_button_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_Sub_Button, &style_screen_sub_button_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_sub_button_main_main_checked
	static lv_style_t style_screen_sub_button_main_main_checked;
	lv_style_reset(&style_screen_sub_button_main_main_checked);
	lv_style_set_text_color(&style_screen_sub_button_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_sub_button_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_sub_button_main_main_checked, 0);
	lv_obj_add_style(ui->screen_Sub_Button, &style_screen_sub_button_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_Sub_Button, LV_IMGBTN_STATE_PRESSED, NULL, &_Button_alpha_20x20, NULL);
	lv_imgbtn_set_src(ui->screen_Sub_Button, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_20x20, NULL);
	lv_obj_add_flag(ui->screen_Sub_Button, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_Sub_Button_Intermediate

	//Write style state: LV_STATE_DEFAULT for style_screen_sub_button_intermediate_main_main_default
	static lv_style_t style_screen_sub_button_intermediate_main_main_default;
	lv_style_reset(&style_screen_sub_button_intermediate_main_main_default);
	lv_style_set_img_recolor(&style_screen_sub_button_intermediate_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_sub_button_intermediate_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_sub_button_intermediate_main_main_default, 255);

	//Write codes screen_Clock_Am
	ui->screen_Clock_Am = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Clock_Am, 118, 69);
	lv_obj_set_size(ui->screen_Clock_Am, 16, 12);
	lv_label_set_text(ui->screen_Clock_Am, "AM");
	lv_label_set_long_mode(ui->screen_Clock_Am, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Clock_Am, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_am_main_main_default
	static lv_style_t style_screen_clock_am_main_main_default;
	lv_style_reset(&style_screen_clock_am_main_main_default);
	lv_style_set_radius(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_clock_am_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_clock_am_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_clock_am_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_text_color(&style_screen_clock_am_main_main_default, lv_color_make(0xfa, 0xfa, 0xfa));
	lv_style_set_text_font(&style_screen_clock_am_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_clock_am_main_main_default, 0);
	lv_obj_add_style(ui->screen_Clock_Am, &style_screen_clock_am_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Fuel_low_mMarker
	ui->screen_Fuel_low_mMarker = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuel_low_mMarker, 35, 276);
	lv_obj_set_size(ui->screen_Fuel_low_mMarker, 11, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuel_low_mmarker_main_main_default
	static lv_style_t style_screen_fuel_low_mmarker_main_main_default;
	lv_style_reset(&style_screen_fuel_low_mmarker_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuel_low_mmarker_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuel_low_mmarker_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuel_low_mmarker_main_main_default, 255);
	lv_obj_add_style(ui->screen_Fuel_low_mMarker, &style_screen_fuel_low_mmarker_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuel_low_mMarker, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuel_low_mMarker,&_img_night_fuel_low_marker_11x13);
	lv_img_set_pivot(ui->screen_Fuel_low_mMarker, 0,0);
	lv_img_set_angle(ui->screen_Fuel_low_mMarker, 0);

	//Write codes screen_Sub_Con
	ui->screen_Sub_Con = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Sub_Con, 198, 147);
	lv_obj_set_size(ui->screen_Sub_Con, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_screen_sub_con_main_main_default
	static lv_style_t style_screen_sub_con_main_main_default;
	lv_style_reset(&style_screen_sub_con_main_main_default);
	lv_style_set_img_recolor(&style_screen_sub_con_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_sub_con_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_sub_con_main_main_default, 255);
	lv_obj_add_style(ui->screen_Sub_Con, &style_screen_sub_con_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Sub_Con, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Sub_Con,&subbtn_night_24x24);
	lv_img_set_pivot(ui->screen_Sub_Con, 0,0);
	lv_img_set_angle(ui->screen_Sub_Con, 0);

		//Write codes screen_Gear_Symbol
	ui->screen_Gear_Symbol = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Gear_Symbol, 17, 148);
	lv_obj_set_size(ui->screen_Gear_Symbol, 10, 24);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_symbol_main_main_default
	static lv_style_t style_screen_gear_symbol_main_main_default;
	lv_style_reset(&style_screen_gear_symbol_main_main_default);
	lv_style_set_img_recolor(&style_screen_gear_symbol_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_symbol_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_symbol_main_main_default, 255);
	lv_obj_add_style(ui->screen_Gear_Symbol, &style_screen_gear_symbol_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Gear_Symbol, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Gear_Symbol,&_Ge_i_10x24);
	lv_img_set_pivot(ui->screen_Gear_Symbol, 0,0);
	lv_img_set_angle(ui->screen_Gear_Symbol, 0);

	//Write codes screen_Gear_Position_Number
	ui->screen_Gear_Position_Number = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Gear_Position_Number, 29, 144);
	lv_obj_set_size(ui->screen_Gear_Position_Number, 14, 26);
	lv_label_set_text(ui->screen_Gear_Position_Number, "2");
	lv_label_set_long_mode(ui->screen_Gear_Position_Number, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Gear_Position_Number, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_position_number_main_main_default
	static lv_style_t style_screen_gear_position_number_main_main_default;
	lv_style_reset(&style_screen_gear_position_number_main_main_default);
	lv_style_set_radius(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_gear_position_number_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_gear_position_number_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_gear_position_number_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_text_color(&style_screen_gear_position_number_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_gear_position_number_main_main_default, &lv_font_FjallaOne_Regular_30);
	lv_style_set_text_letter_space(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_gear_position_number_main_main_default, 0);
	lv_obj_add_style(ui->screen_Gear_Position_Number, &style_screen_gear_position_number_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_gear_N_img_night
	ui->screen_gear_N_img_night = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_gear_N_img_night, 30, 150);
	lv_obj_set_size(ui->screen_gear_N_img_night, 15, 23);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_n_img_night_main_main_default
	static lv_style_t style_screen_gear_n_img_night_main_main_default;
	lv_style_reset(&style_screen_gear_n_img_night_main_main_default);
	lv_style_set_img_recolor(&style_screen_gear_n_img_night_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_n_img_night_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_n_img_night_main_main_default, 255);
	lv_obj_add_style(ui->screen_gear_N_img_night, &style_screen_gear_n_img_night_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_gear_N_img_night,&img_night_gear_neutral);

	//Write codes screen_blu_msg_icon
	ui->screen_blu_msg_icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_blu_msg_icon, 42, 87);
	lv_obj_set_size(ui->screen_blu_msg_icon, 20, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_blu_msg_icon_main_main_default
	static lv_style_t style_screen_blu_msg_icon_main_main_default;
	lv_style_reset(&style_screen_blu_msg_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_blu_msg_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_blu_msg_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_blu_msg_icon_main_main_default, 255);
	lv_obj_add_style(ui->screen_blu_msg_icon, &style_screen_blu_msg_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_blu_msg_icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_blu_msg_icon,&_night_Message_black_20x12);
	lv_img_set_pivot(ui->screen_blu_msg_icon, 0,0);
	lv_img_set_angle(ui->screen_blu_msg_icon, 0);

	//Write codes screen_blu_mis_call_icon
	ui->screen_blu_mis_call_icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_blu_mis_call_icon, 183, 87);
	lv_obj_set_size(ui->screen_blu_mis_call_icon, 15, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_blu_mis_call_icon_main_main_default
	static lv_style_t style_screen_blu_mis_call_icon_main_main_default;
	lv_style_reset(&style_screen_blu_mis_call_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_blu_mis_call_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_blu_mis_call_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_blu_mis_call_icon_main_main_default, 255);
	lv_obj_add_style(ui->screen_blu_mis_call_icon, &style_screen_blu_mis_call_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_blu_mis_call_icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_blu_mis_call_icon,&_night_Missed_Call_15x12);
	lv_img_set_pivot(ui->screen_blu_mis_call_icon, 0,0);
	lv_img_set_angle(ui->screen_blu_mis_call_icon, 0);

	//Write codes screen_Tacho_Mid_grey
	ui->screen_Tacho_Mid_grey = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Tacho_Mid_grey, 0, 7);
	lv_obj_set_size(ui->screen_Tacho_Mid_grey, 240, 306);

	//Write style state: LV_STATE_DEFAULT for style_screen_tacho_mid_grey_main_main_default
	static lv_style_t style_screen_tacho_mid_grey_main_main_default;
	lv_style_reset(&style_screen_tacho_mid_grey_main_main_default);
	lv_style_set_img_recolor(&style_screen_tacho_mid_grey_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tacho_mid_grey_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tacho_mid_grey_main_main_default, 255);
	lv_obj_add_style(ui->screen_Tacho_Mid_grey, &style_screen_tacho_mid_grey_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_Tacho_Mid_grey,&Red_night_middle_grey_circler);

}

void Main_Screen_Day_obj_create(lv_ui *ui)
{
	ui->screen = lv_obj_create(NULL);
	
	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	lv_style_reset(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_screen_main_main_default, 255);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	ui->screen_skin = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_skin, 0, 0);
	lv_obj_set_size(ui->screen_skin, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_screen_skin_main_main_default
	static lv_style_t style_screen_skin_main_main_default;
	lv_style_reset(&style_screen_skin_main_main_default);
	lv_style_set_img_recolor(&style_screen_skin_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_skin_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_skin_main_main_default, 255);
	lv_obj_add_style(ui->screen_skin, &style_screen_skin_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_skin, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_skin,&_Skin_BG_240x320);
	lv_img_set_pivot(ui->screen_skin, 0,0);
	lv_img_set_angle(ui->screen_skin, 0);

	//Write codes screen_FogLampTT
	ui->screen_FogLampTT = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_FogLampTT, 10, 11);
	lv_obj_set_size(ui->screen_FogLampTT, 24, 21);

	//Write style state: LV_STATE_DEFAULT for style_screen_foglamptt_main_main_default
	static lv_style_t style_screen_foglamptt_main_main_default;
	lv_style_reset(&style_screen_foglamptt_main_main_default);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_foglamptt_main_main_default, 255);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_foglamptt_main_main_pressed
	static lv_style_t style_screen_foglamptt_main_main_pressed;
	lv_style_reset(&style_screen_foglamptt_main_main_pressed);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_foglamptt_main_main_checked
	static lv_style_t style_screen_foglamptt_main_main_checked;
	lv_style_reset(&style_screen_foglamptt_main_main_checked);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_checked, 0);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_FogLampTT, LV_IMGBTN_STATE_RELEASED, NULL, &_Layer_0_alpha_24x20, NULL);
	lv_imgbtn_set_src(ui->screen_FogLampTT, LV_IMGBTN_STATE_PRESSED, NULL, &new_header_fog_telltale, NULL);
	lv_obj_add_flag(ui->screen_FogLampTT, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_imgEngineTT
	ui->screen_imgEngineTT = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgEngineTT, 204, 12);
	lv_obj_set_size(ui->screen_imgEngineTT, 26, 18);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgenginett_main_main_default
	static lv_style_t style_screen_imgenginett_main_main_default;
	lv_style_reset(&style_screen_imgenginett_main_main_default);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgenginett_main_main_default, 255);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgenginett_main_main_pressed
	static lv_style_t style_screen_imgenginett_main_main_pressed;
	lv_style_reset(&style_screen_imgenginett_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgenginett_main_main_checked
	static lv_style_t style_screen_imgenginett_main_main_checked;
	lv_style_reset(&style_screen_imgenginett_main_main_checked);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgEngineTT, LV_IMGBTN_STATE_RELEASED, NULL, &new_engine_telltale, NULL);
	lv_imgbtn_set_src(ui->screen_imgEngineTT, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_25x17, NULL);
	lv_obj_add_flag(ui->screen_imgEngineTT, LV_OBJ_FLAG_CHECKABLE);

		//Write codes screen_day_base_container
	ui->screen_day_base_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_day_base_container, 0, 0);
	lv_obj_set_size(ui->screen_day_base_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_base_container_main_main_default
	static lv_style_t style_screen_day_base_container_main_main_default;
	lv_style_reset(&style_screen_day_base_container_main_main_default);
	lv_style_set_radius(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_base_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_day_base_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_day_base_container_main_main_default, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_day_base_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_day_base_container_main_main_default, 255);
	lv_style_set_pad_left(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_base_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_base_container, &style_screen_day_base_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_white_img
	ui->screen_white_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_white_img, 7, 47);
	lv_obj_set_size(ui->screen_white_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_screen_white_img_main_main_default
	static lv_style_t style_screen_white_img_main_main_default;
	lv_style_reset(&style_screen_white_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_white_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_white_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_white_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_white_img, &style_screen_white_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_white_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_white_img,&day_white_Grey_circle);
	//lv_img_set_src(ui->screen_white_img,&_circle_226x226);	
	lv_img_set_pivot(ui->screen_white_img, 0,0);
	lv_img_set_angle(ui->screen_white_img, 0);

	//Write codes screen_kmimage
	ui->screen_kmimage = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_kmimage, 189, 150);
	lv_obj_set_size(ui->screen_kmimage, 33, 19);

	//Write style state: LV_STATE_DEFAULT for style_screen_kmimage_main_main_default
	static lv_style_t style_screen_kmimage_main_main_default;
	lv_style_reset(&style_screen_kmimage_main_main_default);
	lv_style_set_img_recolor(&style_screen_kmimage_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_kmimage_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_kmimage_main_main_default, 255);
	lv_obj_add_style(ui->screen_kmimage, &style_screen_kmimage_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_kmimage, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_kmimage,&kmimage_day);
	lv_img_set_pivot(ui->screen_kmimage, 0,0);
	lv_img_set_angle(ui->screen_kmimage, 0);	


	//Write codes screen_E_F_Img
	ui->screen_E_F_Img = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_E_F_Img, 38, 254);
	lv_obj_set_size(ui->screen_E_F_Img, 13, 15);

	//Write style state: LV_STATE_DEFAULT for style_screen_e_f_img_main_main_default
	static lv_style_t style_screen_e_f_img_main_main_default;
	lv_style_reset(&style_screen_e_f_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_e_f_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_e_f_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_e_f_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_E_F_Img, &style_screen_e_f_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_E_F_Img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_E_F_Img,&_img_night_fuel_E_13x15);
	lv_img_set_pivot(ui->screen_E_F_Img, 0,0);
	lv_img_set_angle(ui->screen_E_F_Img, 0);

	//Write codes screen_F_Img
	ui->screen_F_Img = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_F_Img, 190, 252);
	lv_obj_set_size(ui->screen_F_Img, 10, 16);

	//Write style state: LV_STATE_DEFAULT for style_screen_f_img_main_main_default
	static lv_style_t style_screen_f_img_main_main_default;
	lv_style_reset(&style_screen_f_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_f_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_f_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_f_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_F_Img, &style_screen_f_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_F_Img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_F_Img,&_img_night_fuel_F_10x16);
	lv_img_set_pivot(ui->screen_F_Img, 0,0);
	lv_img_set_angle(ui->screen_F_Img, 0);	

	//Write codes screen_Fuelbar0
	ui->screen_Fuelbar0 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuelbar0, 41, 266);
	lv_obj_set_size(ui->screen_Fuelbar0, 158, 43);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuelbar0_main_main_default
	static lv_style_t style_screen_fuelbar0_main_main_default;
	lv_style_reset(&style_screen_fuelbar0_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuelbar0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuelbar0_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuelbar0_main_main_default, 255);
	lv_obj_add_style(ui->screen_Fuelbar0, &style_screen_fuelbar0_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuelbar0, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuelbar0,&img_fuel_grey_bg_white_icon);
	lv_img_set_pivot(ui->screen_Fuelbar0, 0,0);
	lv_img_set_angle(ui->screen_Fuelbar0, 0);

	//Write codes screen_Day_hour
	ui->screen_Day_hour = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_hour, 86, 81);
	lv_obj_set_size(ui->screen_Day_hour, 13, 12);
	lv_label_set_text(ui->screen_Day_hour, "24");
	lv_label_set_long_mode(ui->screen_Day_hour, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_hour, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_hour_main_main_default
	static lv_style_t style_screen_day_hour_main_main_default;
	lv_style_reset(&style_screen_day_hour_main_main_default);
	lv_style_set_radius(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_hour_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_hour_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_hour_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_hour_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_hour_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_hour_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_hour, &style_screen_day_hour_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_min
	ui->screen_Day_min = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_min, 113, 81);
	lv_obj_set_size(ui->screen_Day_min, 15, 12);
	lv_label_set_text(ui->screen_Day_min, "24");
	lv_label_set_long_mode(ui->screen_Day_min, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_min, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_min_main_main_default
	static lv_style_t style_screen_day_min_main_main_default;
	lv_style_reset(&style_screen_day_min_main_main_default);
	lv_style_set_radius(&style_screen_day_min_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_min_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_min_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_min_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_min_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_day_min_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_min_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_min_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_min_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_min_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_min, &style_screen_day_min_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_colon
	ui->screen_Day_colon = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_colon, 109, 85);
	lv_obj_set_size(ui->screen_Day_colon, 3, 10);
	lv_label_set_text(ui->screen_Day_colon, ":");
	lv_label_set_long_mode(ui->screen_Day_colon, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_colon, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_colon_main_main_default
	static lv_style_t style_screen_day_colon_main_main_default;
	lv_style_reset(&style_screen_day_colon_main_main_default);
	lv_style_set_radius(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_colon_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_colon_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_colon_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_colon_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_colon_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_colon_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_colon, &style_screen_day_colon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_TachoBarBlank
	ui->screen_TachoBarBlank = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBarBlank, 3, 8);
	lv_obj_set_size(ui->screen_TachoBarBlank, 231, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobarblank_main_main_default
	static lv_style_t style_screen_tachobarblank_main_main_default;
	lv_style_reset(&style_screen_tachobarblank_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobarblank_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobarblank_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobarblank_main_main_default, 0);
	lv_obj_add_style(ui->screen_TachoBarBlank, &style_screen_tachobarblank_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBarBlank, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBarBlank,&_Layer_0_231x78);
	lv_img_set_pivot(ui->screen_TachoBarBlank, 0,0);
	lv_img_set_angle(ui->screen_TachoBarBlank, 0);

	//Write codes screen_Service_Due
	ui->screen_Service_Due = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_Service_Due, 207, 234);
	lv_obj_set_size(ui->screen_Service_Due, 25, 25);

	//Write style state: LV_STATE_DEFAULT for style_screen_service_due_main_main_default
	static lv_style_t style_screen_service_due_main_main_default;
	lv_style_reset(&style_screen_service_due_main_main_default);
	lv_style_set_text_color(&style_screen_service_due_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_default, 3);
	lv_style_set_img_opa(&style_screen_service_due_main_main_default, 255);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_move_foreground(ui->screen_Service_Due);
	

	//Write style state: LV_STATE_PRESSED for style_screen_service_due_main_main_pressed
	static lv_style_t style_screen_service_due_main_main_pressed;
	lv_style_reset(&style_screen_service_due_main_main_pressed);
	lv_style_set_text_color(&style_screen_service_due_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_service_due_main_main_checked
	static lv_style_t style_screen_service_due_main_main_checked;
	lv_style_reset(&style_screen_service_due_main_main_checked);
	lv_style_set_text_color(&style_screen_service_due_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_checked, 0);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_Service_Due, LV_IMGBTN_STATE_RELEASED, NULL, &img_Service_Remainder_25x25, NULL);
	lv_imgbtn_set_src(ui->screen_Service_Due, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_22x25, NULL);
	lv_obj_add_flag(ui->screen_Service_Due, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_day_gear
	ui->screen_day_gear = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_gear, 17, 148);
	lv_obj_set_size(ui->screen_day_gear, 10, 24);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_gear_main_main_default
	static lv_style_t style_screen_day_gear_main_main_default;
	lv_style_reset(&style_screen_day_gear_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_gear_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_gear_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_gear_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_gear, &style_screen_day_gear_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_gear, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_gear,&_White_gear_10x24);
	lv_img_set_pivot(ui->screen_day_gear, 0,0);
	lv_img_set_angle(ui->screen_day_gear, 0);

	//Write codes screen_day_gear_up
	ui->screen_day_gear_up = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_gear_up, 30, 134);
	lv_obj_set_size(ui->screen_day_gear_up, 15, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_gear_up_main_main_default
	static lv_style_t style_screen_day_gear_up_main_main_default;
	lv_style_reset(&style_screen_day_gear_up_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_gear_up_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_gear_up_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_gear_up_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_gear_up, &style_screen_day_gear_up_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_gear_up, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_gear_up,&new_day_gear_arrows_up_white);
	lv_img_set_pivot(ui->screen_day_gear_up, 0,0);
	lv_img_set_angle(ui->screen_day_gear_up, 0);

	//Write codes screen_day_gear_down
	ui->screen_day_gear_down = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_gear_down, 30, 177);
	lv_obj_set_size(ui->screen_day_gear_down, 15, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_gear_down_main_main_default
	static lv_style_t style_screen_day_gear_down_main_main_default;
	lv_style_reset(&style_screen_day_gear_down_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_gear_down_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_gear_down_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_gear_down_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_gear_down, &style_screen_day_gear_down_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_gear_down, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_gear_down,&new_day_gear_arrows_down_white);
	lv_img_set_pivot(ui->screen_day_gear_down, 0,0);
	lv_img_set_angle(ui->screen_day_gear_down, 0);

		//Write codes screen_gear_N_img_Day
	ui->screen_gear_N_img_Day = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_gear_N_img_Day, 30, 150);
	lv_obj_set_size(ui->screen_gear_N_img_Day, 15, 23);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_n_img_day_main_main_default
	static lv_style_t style_screen_gear_n_img_day_main_main_default;
	lv_style_reset(&style_screen_gear_n_img_day_main_main_default);
	lv_style_set_img_recolor(&style_screen_gear_n_img_day_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_n_img_day_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_n_img_day_main_main_default, 255);
	lv_obj_add_style(ui->screen_gear_N_img_Day, &style_screen_gear_n_img_day_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_gear_N_img_Day,&img_day_gear_neutral);

	//Write codes screen_Day_Gear_pos_Num
	ui->screen_Day_Gear_pos_Num = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_Gear_pos_Num, 31, 142);
	lv_obj_set_size(ui->screen_Day_Gear_pos_Num, 12, 28);
	lv_label_set_text(ui->screen_Day_Gear_pos_Num, "2");
	lv_label_set_long_mode(ui->screen_Day_Gear_pos_Num, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_Gear_pos_Num, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_gear_pos_num_main_main_default
	static lv_style_t style_screen_day_gear_pos_num_main_main_default;
	lv_style_reset(&style_screen_day_gear_pos_num_main_main_default);
	lv_style_set_radius(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_gear_pos_num_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_gear_pos_num_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_gear_pos_num_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_gear_pos_num_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_gear_pos_num_main_main_default, &lv_font_FjallaOne_Regular_30);
	lv_style_set_text_letter_space(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_Gear_pos_Num, &style_screen_day_gear_pos_num_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_TachoBar0
	ui->screen_TachoBar0 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBar0, 7, 6);
	lv_obj_set_size(ui->screen_TachoBar0, 227, 75);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobar0_main_main_default
	static lv_style_t style_screen_tachobar0_main_main_default;
	lv_style_reset(&style_screen_tachobar0_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobar0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobar0_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobar0_main_main_default, 255);
	lv_obj_add_style(ui->screen_TachoBar0, &style_screen_tachobar0_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBar0, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBar0,&img_tacho_chaplets);
	lv_img_set_pivot(ui->screen_TachoBar0, 0,0);
	lv_img_set_angle(ui->screen_TachoBar0, 0);


	//Write codes screen_TachoBar0_1
	ui->screen_TachoBar0_1 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBar0_1, 3, 8);
	lv_obj_set_size(ui->screen_TachoBar0_1, 231, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobar0_1_main_main_default
	static lv_style_t style_screen_tachobar0_1_main_main_default;
	lv_style_reset(&style_screen_tachobar0_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobar0_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobar0_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobar0_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_TachoBar0_1, &style_screen_tachobar0_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBar0_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBar0_1,&_img_night_tacho_fill_001_231x78);
	lv_img_set_pivot(ui->screen_TachoBar0_1, 0,0);
	lv_img_set_angle(ui->screen_TachoBar0_1, 0);

	//Write codes screen_Fuel_Img_Icon
	ui->screen_Fuel_Img_Icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuel_Img_Icon, 105, 248);
	lv_obj_set_size(ui->screen_Fuel_Img_Icon, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuel_img_icon_main_main_default
	static lv_style_t style_screen_fuel_img_icon_main_main_default;
	lv_style_reset(&style_screen_fuel_img_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuel_img_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuel_img_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuel_img_icon_main_main_default, 0);
	lv_obj_add_style(ui->screen_Fuel_Img_Icon, &style_screen_fuel_img_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuel_Img_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuel_Img_Icon,&_img_night_display_units_fuel_icon_30x30);
	lv_img_set_pivot(ui->screen_Fuel_Img_Icon, 0,0);
	lv_img_set_angle(ui->screen_Fuel_Img_Icon, 0);

	//Write codes screen_imgOilTelltale
	ui->screen_imgOilTelltale = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgOilTelltale, 4, 290);
	lv_obj_set_size(ui->screen_imgOilTelltale, 34, 14);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgoiltelltale_main_main_default
	static lv_style_t style_screen_imgoiltelltale_main_main_default;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_default);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgoiltelltale_main_main_default, 254);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgoiltelltale_main_main_pressed
	static lv_style_t style_screen_imgoiltelltale_main_main_pressed;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgoiltelltale_main_main_checked
	static lv_style_t style_screen_imgoiltelltale_main_main_checked;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_checked);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgOilTelltale, LV_IMGBTN_STATE_RELEASED, NULL, &new_oil_telltale, NULL);
	lv_imgbtn_set_src(ui->screen_imgOilTelltale, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_32x13, NULL);
	lv_obj_add_flag(ui->screen_imgOilTelltale, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_Day_1000_rpm
	ui->screen_Day_1000_rpm = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_1000_rpm, 94, 53);
	lv_obj_set_size(ui->screen_Day_1000_rpm, 51, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_1000_rpm_main_main_default
	static lv_style_t style_screen_day_1000_rpm_main_main_default;
	lv_style_reset(&style_screen_day_1000_rpm_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_1000_rpm_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_1000_rpm_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_1000_rpm_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_1000_rpm, &style_screen_day_1000_rpm_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_1000_rpm, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_1000_rpm,&img_day_x1000_RPM_new);
	lv_img_set_pivot(ui->screen_Day_1000_rpm, 0,0);
	lv_img_set_angle(ui->screen_Day_1000_rpm, 0);

	//Write codes screen_day_battery_img
	ui->screen_day_battery_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_battery_img, 26, 111);
	lv_obj_set_size(ui->screen_day_battery_img, 20, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_battery_img_main_main_default
	static lv_style_t style_screen_day_battery_img_main_main_default;
	lv_style_reset(&style_screen_day_battery_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_battery_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_battery_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_battery_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_battery_img, &style_screen_day_battery_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_signal_img
	ui->screen_day_signal_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_signal_img, 200, 111);
	lv_obj_set_size(ui->screen_day_signal_img, 14, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_signal_img_main_main_default
	static lv_style_t style_screen_day_signal_img_main_main_default;
	lv_style_reset(&style_screen_day_signal_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_signal_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_signal_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_signal_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_signal_img, &style_screen_day_signal_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_sub_btn
	ui->screen_day_sub_btn = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_sub_btn, 198, 147);
	lv_obj_set_size(ui->screen_day_sub_btn, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_sub_btn_main_main_default
	static lv_style_t style_screen_day_sub_btn_main_main_default;
	lv_style_reset(&style_screen_day_sub_btn_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_sub_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_sub_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_sub_btn_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_sub_btn, &style_screen_day_sub_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_sub_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_sub_btn,&subbtn_day_24x24);
	lv_img_set_pivot(ui->screen_day_sub_btn, 0,0);
	lv_img_set_angle(ui->screen_day_sub_btn, 0);
	

	//Write codes screen_main_white_container
	ui->screen_main_white_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_main_white_container, 56, 120);
	lv_obj_set_size(ui->screen_main_white_container, 136, 123);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_white_container_main_main_default
	static lv_style_t style_screen_main_white_container_main_main_default;
	lv_style_reset(&style_screen_main_white_container_main_main_default);
	lv_style_set_radius(&style_screen_main_white_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_white_container_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_main_white_container_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_main_white_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_main_white_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_main_white_container_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_screen_main_white_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_white_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_white_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_white_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_white_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_white_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_white_container, &style_screen_main_white_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_odo_lbl
	ui->screen_main_odo_lbl = lv_label_create(ui->screen_main_white_container);
	lv_obj_set_pos(ui->screen_main_odo_lbl, 37, 96);
	lv_obj_set_size(ui->screen_main_odo_lbl, 69, 19);
	lv_label_set_text(ui->screen_main_odo_lbl, "0");
	lv_label_set_long_mode(ui->screen_main_odo_lbl, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_main_odo_lbl, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_odo_lbl_main_main_default
	static lv_style_t style_screen_main_odo_lbl_main_main_default;
	lv_style_reset(&style_screen_main_odo_lbl_main_main_default);
	lv_style_set_radius(&style_screen_main_odo_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_odo_lbl_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_main_odo_lbl_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_main_odo_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_main_odo_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_odo_lbl_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_main_odo_lbl_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_main_odo_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_odo_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_odo_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_odo_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_odo_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_odo_lbl, &style_screen_main_odo_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_odo_img
	ui->screen_main_odo_img = lv_img_create(ui->screen_main_white_container);
	lv_obj_set_pos(ui->screen_main_odo_img, 2, 103);
	lv_obj_set_size(ui->screen_main_odo_img, 27, 14);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_odo_img_main_main_default
	static lv_style_t style_screen_main_odo_img_main_main_default;
	lv_style_reset(&style_screen_main_odo_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_main_odo_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_main_odo_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_main_odo_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_main_odo_img, &style_screen_main_odo_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_main_odo_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_odo_img,&txt_day_odo);
	lv_img_set_pivot(ui->screen_main_odo_img, 0,0);
	lv_img_set_angle(ui->screen_main_odo_img, 0);

	//Write codes screen_main_odo_km
	ui->screen_main_odo_km = lv_img_create(ui->screen_main_white_container);
	lv_obj_set_pos(ui->screen_main_odo_km, 110, 102);
	lv_obj_set_size(ui->screen_main_odo_km, 20, 15);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_odo_km_main_main_default
	static lv_style_t style_screen_main_odo_km_main_main_default;
	lv_style_reset(&style_screen_main_odo_km_main_main_default);
	lv_style_set_img_recolor(&style_screen_main_odo_km_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_main_odo_km_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_main_odo_km_main_main_default, 255);
	lv_obj_add_style(ui->screen_main_odo_km, &style_screen_main_odo_km_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_main_odo_km, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_odo_km,&txt_day_odo_unit);
	lv_img_set_pivot(ui->screen_main_odo_km, 0,0);
	lv_img_set_angle(ui->screen_main_odo_km, 0);

//Write codes screen_contSp_Main_2
	ui->screen_contSp_Main_2 = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_contSp_Main_2, 56, 120);
	lv_obj_set_size(ui->screen_contSp_Main_2, 136, 123);

	//Write style state: LV_STATE_DEFAULT for style_screen_contsp_main_2_main_main_default
	static lv_style_t style_screen_contsp_main_2_main_main_default;
	lv_style_reset(&style_screen_contsp_main_2_main_main_default);
	lv_style_set_radius(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_contsp_main_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_contsp_main_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_contsp_main_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_contsp_main_2_main_main_default, 255);
	lv_style_set_border_color(&style_screen_contsp_main_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_contsp_main_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_contSp_Main_2, &style_screen_contsp_main_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_con_odo_val
	ui->screen_con_odo_val = lv_label_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_con_odo_val, 38, 99);
	lv_obj_set_size(ui->screen_con_odo_val, 69, 19);
	lv_label_set_text(ui->screen_con_odo_val, "0");
	lv_label_set_long_mode(ui->screen_con_odo_val, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_con_odo_val, LV_TEXT_ALIGN_RIGHT, 0);

	//Write codes screen_Codo
	ui->screen_Codo = lv_img_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_Codo, 2, 103);
	lv_obj_set_size(ui->screen_Codo, 27, 14);

	//Write style state: LV_STATE_DEFAULT for style_screen_codo_main_main_default
	static lv_style_t style_screen_codo_main_main_default;
	lv_style_reset(&style_screen_codo_main_main_default);
	lv_style_set_img_recolor(&style_screen_codo_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_codo_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_codo_main_main_default, 255);
	lv_obj_add_style(ui->screen_Codo, &style_screen_codo_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Codo, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Codo,&_txt_night_odo_27x14);
	lv_img_set_pivot(ui->screen_Codo, 0,0);
	lv_img_set_angle(ui->screen_Codo, 0);

	//Write codes screen_conkm
	ui->screen_conkm = lv_img_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_conkm, 110, 102);
	lv_obj_set_size(ui->screen_conkm, 20, 15);

	//Write style state: LV_STATE_DEFAULT for style_screen_conkm_main_main_default
	static lv_style_t style_screen_conkm_main_main_default;
	lv_style_reset(&style_screen_conkm_main_main_default);
	lv_style_set_img_recolor(&style_screen_conkm_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_conkm_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_conkm_main_main_default, 255);
	lv_obj_add_style(ui->screen_conkm, &style_screen_conkm_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_conkm, LV_OBJ_FLAG_CLICKABLE);
	//lv_img_set_src(ui->screen_conkm,&_txt_night_odo_unit_20x15);
	lv_img_set_src(ui->screen_conkm,&txt_night_odo_unit);
	lv_img_set_pivot(ui->screen_conkm, 0,0);
	lv_img_set_angle(ui->screen_conkm, 0);

	//Write codes screen_main_sc_3
	ui->screen_main_sc_3 = lv_img_create(ui->screen_main_white_container);
	lv_obj_set_pos(ui->screen_main_sc_3, 2, 3);
	lv_obj_set_size(ui->screen_main_sc_3, 41, 73);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_sc_3_main_main_default
	static lv_style_t style_screen_main_sc_3_main_main_default;
	lv_style_reset(&style_screen_main_sc_3_main_main_default);
	lv_style_set_img_recolor(&style_screen_main_sc_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_main_sc_3_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_main_sc_3_main_main_default, 255);
	lv_obj_add_style(ui->screen_main_sc_3, &style_screen_main_sc_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_main_sc_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_sc_3,&txt_day_speed_line_3_grey0);
	lv_img_set_pivot(ui->screen_main_sc_3, 0,0);
	lv_img_set_angle(ui->screen_main_sc_3, 0);

	//Write codes screen_main_sc_2
	ui->screen_main_sc_2 = lv_img_create(ui->screen_main_white_container);
	lv_obj_set_pos(ui->screen_main_sc_2, 43, 3);
	lv_obj_set_size(ui->screen_main_sc_2, 41, 73);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_sc_2_main_main_default
	static lv_style_t style_screen_main_sc_2_main_main_default;
	lv_style_reset(&style_screen_main_sc_2_main_main_default);
	lv_style_set_img_recolor(&style_screen_main_sc_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_main_sc_2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_main_sc_2_main_main_default, 255);
	lv_obj_add_style(ui->screen_main_sc_2, &style_screen_main_sc_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_main_sc_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_sc_2,&txt_day_speed_line_3_grey0);
	lv_img_set_pivot(ui->screen_main_sc_2, 0,0);
	lv_img_set_angle(ui->screen_main_sc_2, 0);

	//Write codes screen_main_sc_1
	ui->screen_main_sc_1 = lv_img_create(ui->screen_main_white_container);
	lv_obj_set_pos(ui->screen_main_sc_1, 85, 3);
	lv_obj_set_size(ui->screen_main_sc_1, 41, 73);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_sc_1_main_main_default
	static lv_style_t style_screen_main_sc_1_main_main_default;
	lv_style_reset(&style_screen_main_sc_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_main_sc_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_main_sc_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_main_sc_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_main_sc_1, &style_screen_main_sc_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_main_sc_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_sc_1,&txt_day_speed_line_3_white0);
	lv_img_set_pivot(ui->screen_main_sc_1, 0,0);
	lv_img_set_angle(ui->screen_main_sc_1, 0);

	//Write codes screen_Sub_Button̥̥̥
	ui->screen_Sub_Button = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_Sub_Button, 200, 150);
	lv_obj_set_size(ui->screen_Sub_Button, 20, 20);

	//Write codes screen_Day_Am_pm
	ui->screen_Day_Am_pm = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_Am_pm, 118, 81);
	lv_obj_set_size(ui->screen_Day_Am_pm, 16, 12);
	lv_label_set_text(ui->screen_Day_Am_pm, "Pm");
	lv_label_set_long_mode(ui->screen_Day_Am_pm, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_Am_pm, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_am_pm_main_main_default
	static lv_style_t style_screen_day_am_pm_main_main_default;
	lv_style_reset(&style_screen_day_am_pm_main_main_default);
	lv_style_set_radius(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_am_pm_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_am_pm_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_am_pm_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_am_pm_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_am_pm_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_am_pm_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_Am_pm, &style_screen_day_am_pm_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Fuel_low_mMarker
	ui->screen_Fuel_low_mMarker = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuel_low_mMarker, 35, 276);
	lv_obj_set_size(ui->screen_Fuel_low_mMarker, 11, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuel_low_mmarker_main_main_default
	static lv_style_t style_screen_fuel_low_mmarker_main_main_default;
	lv_style_reset(&style_screen_fuel_low_mmarker_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuel_low_mmarker_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuel_low_mmarker_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuel_low_mmarker_main_main_default, 255);
	lv_obj_add_style(ui->screen_Fuel_low_mMarker, &style_screen_fuel_low_mmarker_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuel_low_mMarker, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuel_low_mMarker,&_img_night_fuel_low_marker_11x13);
	lv_img_set_pivot(ui->screen_Fuel_low_mMarker, 0,0);
	lv_img_set_angle(ui->screen_Fuel_low_mMarker, 0);

	//Write codes screen_day_msg_img
	ui->screen_day_msg_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_msg_img, 42, 87);
	lv_obj_set_size(ui->screen_day_msg_img, 20, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_msg_img_main_main_default
	static lv_style_t style_screen_day_msg_img_main_main_default;
	lv_style_reset(&style_screen_day_msg_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_msg_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_msg_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_msg_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_msg_img, &style_screen_day_msg_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_day_msg_img,&day_msg_icon);

	//Write codes screen_day_mis_call_img
	ui->screen_day_mis_call_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_mis_call_img, 183, 87);
	lv_obj_set_size(ui->screen_day_mis_call_img, 15, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_mis_call_img_main_main_default
	static lv_style_t style_screen_day_mis_call_img_main_main_default;
	lv_style_reset(&style_screen_day_mis_call_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_mis_call_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_mis_call_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_mis_call_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_mis_call_img, &style_screen_day_mis_call_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_day_mis_call_img,&day_mis_call_icon);

	//Write codes screen_Tacho_Mid_grey
	ui->screen_Tacho_Mid_grey = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Tacho_Mid_grey, 0, 7);
	lv_obj_set_size(ui->screen_Tacho_Mid_grey, 240, 306);

	//Write style state: LV_STATE_DEFAULT for style_screen_tacho_mid_grey_main_main_default
	static lv_style_t style_screen_tacho_mid_grey_main_main_default;
	lv_style_reset(&style_screen_tacho_mid_grey_main_main_default);
	lv_style_set_img_recolor(&style_screen_tacho_mid_grey_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tacho_mid_grey_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tacho_mid_grey_main_main_default, 255);
	lv_obj_add_style(ui->screen_Tacho_Mid_grey, &style_screen_tacho_mid_grey_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_Tacho_Mid_grey,&Red_night_middle_grey_circler);

}


void Inter_Screen_night_obj_create(lv_ui *ui)
{
	ui->screen = lv_obj_create(NULL);
	
	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	lv_style_reset(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_screen_main_main_default, 255);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	ui->screen_skin = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_skin, 0, 0);
	lv_obj_set_size(ui->screen_skin, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_screen_skin_main_main_default
	static lv_style_t style_screen_skin_main_main_default;
	lv_style_reset(&style_screen_skin_main_main_default);
	lv_style_set_img_recolor(&style_screen_skin_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_skin_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_skin_main_main_default, 255);
	lv_obj_add_style(ui->screen_skin, &style_screen_skin_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_skin, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_skin,&_Skin_BG_240x320);
	lv_img_set_pivot(ui->screen_skin, 0,0);
	lv_img_set_angle(ui->screen_skin, 0);

	//Write codes screen_FogLampTT
	ui->screen_FogLampTT = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_FogLampTT, 10, 11);
	lv_obj_set_size(ui->screen_FogLampTT, 24, 21);

	//Write style state: LV_STATE_DEFAULT for style_screen_foglamptt_main_main_default
	static lv_style_t style_screen_foglamptt_main_main_default;
	lv_style_reset(&style_screen_foglamptt_main_main_default);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_foglamptt_main_main_default, 255);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_foglamptt_main_main_pressed
	static lv_style_t style_screen_foglamptt_main_main_pressed;
	lv_style_reset(&style_screen_foglamptt_main_main_pressed);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_foglamptt_main_main_checked
	static lv_style_t style_screen_foglamptt_main_main_checked;
	lv_style_reset(&style_screen_foglamptt_main_main_checked);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_checked, 0);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_FogLampTT, LV_IMGBTN_STATE_RELEASED, NULL, &_Layer_0_alpha_24x20, NULL);
	lv_imgbtn_set_src(ui->screen_FogLampTT, LV_IMGBTN_STATE_PRESSED, NULL, &new_header_fog_telltale, NULL);
	lv_obj_add_flag(ui->screen_FogLampTT, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_imgEngineTT
	ui->screen_imgEngineTT = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgEngineTT, 204, 12);
	lv_obj_set_size(ui->screen_imgEngineTT, 26, 18);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgenginett_main_main_default
	static lv_style_t style_screen_imgenginett_main_main_default;
	lv_style_reset(&style_screen_imgenginett_main_main_default);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgenginett_main_main_default, 255);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgenginett_main_main_pressed
	static lv_style_t style_screen_imgenginett_main_main_pressed;
	lv_style_reset(&style_screen_imgenginett_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgenginett_main_main_checked
	static lv_style_t style_screen_imgenginett_main_main_checked;
	lv_style_reset(&style_screen_imgenginett_main_main_checked);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgEngineTT, LV_IMGBTN_STATE_RELEASED, NULL, &new_engine_telltale, NULL);
	lv_imgbtn_set_src(ui->screen_imgEngineTT, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_25x17, NULL);
	lv_obj_add_flag(ui->screen_imgEngineTT, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_imgKmph
	ui->screen_imgKmph = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgKmph, 189, 150);
	lv_obj_set_size(ui->screen_imgKmph, 33, 19);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgkmph_main_main_default
	static lv_style_t style_screen_imgkmph_main_main_default;
	lv_style_reset(&style_screen_imgkmph_main_main_default);
	lv_style_set_img_recolor(&style_screen_imgkmph_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgkmph_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgkmph_main_main_default, 0);
	lv_obj_add_style(ui->screen_imgKmph, &style_screen_imgkmph_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_imgKmph, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_imgKmph,&_txt_night_speed_unit_33x19);
	lv_img_set_pivot(ui->screen_imgKmph, 0,0);
	lv_img_set_angle(ui->screen_imgKmph, 0);	


	//Write codes screen_E_F_Img
	ui->screen_E_F_Img = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_E_F_Img, 38, 254);
	lv_obj_set_size(ui->screen_E_F_Img, 13, 15);

	//Write style state: LV_STATE_DEFAULT for style_screen_e_f_img_main_main_default
	static lv_style_t style_screen_e_f_img_main_main_default;
	lv_style_reset(&style_screen_e_f_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_e_f_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_e_f_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_e_f_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_E_F_Img, &style_screen_e_f_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_E_F_Img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_E_F_Img,&_img_night_fuel_E_13x15);
	lv_img_set_pivot(ui->screen_E_F_Img, 0,0);
	lv_img_set_angle(ui->screen_E_F_Img, 0);

	//Write codes screen_F_Img
	ui->screen_F_Img = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_F_Img, 190, 252);
	lv_obj_set_size(ui->screen_F_Img, 10, 16);

	//Write style state: LV_STATE_DEFAULT for style_screen_f_img_main_main_default
	static lv_style_t style_screen_f_img_main_main_default;
	lv_style_reset(&style_screen_f_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_f_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_f_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_f_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_F_Img, &style_screen_f_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_F_Img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_F_Img,&_img_night_fuel_F_10x16);
	lv_img_set_pivot(ui->screen_F_Img, 0,0);
	lv_img_set_angle(ui->screen_F_Img, 0);	

	//Write codes screen_Fuelbar0
	ui->screen_Fuelbar0 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuelbar0, 41, 266);
	lv_obj_set_size(ui->screen_Fuelbar0, 158, 43);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuelbar0_main_main_default
	static lv_style_t style_screen_fuelbar0_main_main_default;
	lv_style_reset(&style_screen_fuelbar0_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuelbar0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuelbar0_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuelbar0_main_main_default, 255);
	lv_obj_add_style(ui->screen_Fuelbar0, &style_screen_fuelbar0_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuelbar0, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuelbar0,&img_fuel_grey_bg_white_icon);
	lv_img_set_pivot(ui->screen_Fuelbar0, 0,0);
	lv_img_set_angle(ui->screen_Fuelbar0, 0);

	//Write codes screen_TachoBarBlank
	ui->screen_TachoBarBlank = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBarBlank, 3, 8);
	lv_obj_set_size(ui->screen_TachoBarBlank, 231, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobarblank_main_main_default
	static lv_style_t style_screen_tachobarblank_main_main_default;
	lv_style_reset(&style_screen_tachobarblank_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobarblank_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobarblank_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobarblank_main_main_default, 0);
	lv_obj_add_style(ui->screen_TachoBarBlank, &style_screen_tachobarblank_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBarBlank, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBarBlank,&_Layer_0_231x78);
	lv_img_set_pivot(ui->screen_TachoBarBlank, 0,0);
	lv_img_set_angle(ui->screen_TachoBarBlank, 0);

	// Write codes screen_x1000RPM_Img
	ui->screen_x1000RPM_Img = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_x1000RPM_Img, 94, 53);
	lv_obj_set_size(ui->screen_x1000RPM_Img, 51, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_x1000rpm_img_main_main_default
	static lv_style_t style_screen_x1000rpm_img_main_main_default;
	lv_style_reset(&style_screen_x1000rpm_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_x1000rpm_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_x1000rpm_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_x1000rpm_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_x1000RPM_Img, &style_screen_x1000rpm_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_x1000RPM_Img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_x1000RPM_Img,&_1000_RPM_49x13);
	lv_img_set_pivot(ui->screen_x1000RPM_Img, 0,0);
	lv_img_set_angle(ui->screen_x1000RPM_Img, 0);

	
	//Write codes screen_Gear_Symbol
	ui->screen_Gear_Symbol = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Gear_Symbol, 17, 148);
	lv_obj_set_size(ui->screen_Gear_Symbol, 10, 24);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_symbol_main_main_default
	static lv_style_t style_screen_gear_symbol_main_main_default;
	lv_style_reset(&style_screen_gear_symbol_main_main_default);
	lv_style_set_img_recolor(&style_screen_gear_symbol_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_symbol_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_symbol_main_main_default, 255);
	lv_obj_add_style(ui->screen_Gear_Symbol, &style_screen_gear_symbol_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Gear_Symbol, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Gear_Symbol,&_Ge_i_10x24);
	lv_img_set_pivot(ui->screen_Gear_Symbol, 0,0);
	lv_img_set_angle(ui->screen_Gear_Symbol, 0);

	//Write codes screen_Gear_Position_Number
	ui->screen_Gear_Position_Number = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Gear_Position_Number, 29, 144);
	lv_obj_set_size(ui->screen_Gear_Position_Number, 14, 26);
	lv_label_set_text(ui->screen_Gear_Position_Number, "2");
	lv_label_set_long_mode(ui->screen_Gear_Position_Number, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Gear_Position_Number, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_position_number_main_main_default
	static lv_style_t style_screen_gear_position_number_main_main_default;
	lv_style_reset(&style_screen_gear_position_number_main_main_default);
	lv_style_set_radius(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_gear_position_number_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_gear_position_number_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_gear_position_number_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_text_color(&style_screen_gear_position_number_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_gear_position_number_main_main_default, &lv_font_FjallaOne_Regular_30);
	lv_style_set_text_letter_space(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_gear_position_number_main_main_default, 0);
	lv_obj_add_style(ui->screen_Gear_Position_Number, &style_screen_gear_position_number_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_gear_N_img_night
	ui->screen_gear_N_img_night = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_gear_N_img_night, 30, 150);
	lv_obj_set_size(ui->screen_gear_N_img_night, 15, 23);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_n_img_night_main_main_default
	static lv_style_t style_screen_gear_n_img_night_main_main_default;
	lv_style_reset(&style_screen_gear_n_img_night_main_main_default);
	lv_style_set_img_recolor(&style_screen_gear_n_img_night_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_n_img_night_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_n_img_night_main_main_default, 255);
	lv_obj_add_style(ui->screen_gear_N_img_night, &style_screen_gear_n_img_night_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_gear_N_img_night,&img_night_gear_neutral);

	//Write codes screen_Gear_UP_Advisory
	ui->screen_Gear_UP_Advisory = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_Gear_UP_Advisory, 30, 134);
	lv_obj_set_size(ui->screen_Gear_UP_Advisory, 15, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_up_advisory_main_main_default
	static lv_style_t style_screen_gear_up_advisory_main_main_default;
	lv_style_reset(&style_screen_gear_up_advisory_main_main_default);
	lv_style_set_text_color(&style_screen_gear_up_advisory_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_gear_up_advisory_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_up_advisory_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_up_advisory_main_main_default, 254);
	lv_obj_add_style(ui->screen_Gear_UP_Advisory, &style_screen_gear_up_advisory_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_gear_up_advisory_main_main_pressed
	static lv_style_t style_screen_gear_up_advisory_main_main_pressed;
	lv_style_reset(&style_screen_gear_up_advisory_main_main_pressed);
	lv_style_set_text_color(&style_screen_gear_up_advisory_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_gear_up_advisory_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_gear_up_advisory_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_Gear_UP_Advisory, &style_screen_gear_up_advisory_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_gear_up_advisory_main_main_checked
	static lv_style_t style_screen_gear_up_advisory_main_main_checked;
	lv_style_reset(&style_screen_gear_up_advisory_main_main_checked);
	lv_style_set_text_color(&style_screen_gear_up_advisory_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_gear_up_advisory_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_gear_up_advisory_main_main_checked, 0);
	lv_obj_add_style(ui->screen_Gear_UP_Advisory, &style_screen_gear_up_advisory_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_Gear_UP_Advisory, LV_IMGBTN_STATE_RELEASED, NULL, &_img_night_gear_arrows_up_grey_13x9, NULL);
	lv_imgbtn_set_src(ui->screen_Gear_UP_Advisory, LV_IMGBTN_STATE_PRESSED, NULL, &new_night_gear_arrows_up_white, NULL);
	lv_obj_add_flag(ui->screen_Gear_UP_Advisory, LV_OBJ_FLAG_CHECKABLE);


	//Write codes screen_Gear_Down_Advisory
	ui->screen_Gear_Down_Advisory = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_Gear_Down_Advisory, 30, 177);
	lv_obj_set_size(ui->screen_Gear_Down_Advisory, 15, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_down_advisory_main_main_default
	static lv_style_t style_screen_gear_down_advisory_main_main_default;
	lv_style_reset(&style_screen_gear_down_advisory_main_main_default);
	lv_style_set_text_color(&style_screen_gear_down_advisory_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_gear_down_advisory_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_down_advisory_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_down_advisory_main_main_default, 253);
	lv_obj_add_style(ui->screen_Gear_Down_Advisory, &style_screen_gear_down_advisory_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_gear_down_advisory_main_main_pressed
	static lv_style_t style_screen_gear_down_advisory_main_main_pressed;
	lv_style_reset(&style_screen_gear_down_advisory_main_main_pressed);
	lv_style_set_text_color(&style_screen_gear_down_advisory_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_gear_down_advisory_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_gear_down_advisory_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_Gear_Down_Advisory, &style_screen_gear_down_advisory_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_gear_down_advisory_main_main_checked
	static lv_style_t style_screen_gear_down_advisory_main_main_checked;
	lv_style_reset(&style_screen_gear_down_advisory_main_main_checked);
	lv_style_set_text_color(&style_screen_gear_down_advisory_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_gear_down_advisory_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_gear_down_advisory_main_main_checked, 0);
	lv_obj_add_style(ui->screen_Gear_Down_Advisory, &style_screen_gear_down_advisory_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_Gear_Down_Advisory, LV_IMGBTN_STATE_RELEASED, NULL, &_img_night_gear_arrows_down_grey_13x9, NULL);
	lv_imgbtn_set_src(ui->screen_Gear_Down_Advisory, LV_IMGBTN_STATE_PRESSED, NULL, &new_night_gear_arrows_down_white, NULL);
	lv_obj_add_flag(ui->screen_Gear_Down_Advisory, LV_OBJ_FLAG_CHECKABLE);

	
	//Write codes screen_Service_Due
	ui->screen_Service_Due = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_Service_Due, 207, 234);
	lv_obj_set_size(ui->screen_Service_Due, 25, 25);

	//Write style state: LV_STATE_DEFAULT for style_screen_service_due_main_main_default
	static lv_style_t style_screen_service_due_main_main_default;
	lv_style_reset(&style_screen_service_due_main_main_default);
	lv_style_set_text_color(&style_screen_service_due_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_default, 3);
	lv_style_set_img_opa(&style_screen_service_due_main_main_default, 255);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_move_foreground(ui->screen_Service_Due);
	

	//Write style state: LV_STATE_PRESSED for style_screen_service_due_main_main_pressed
	static lv_style_t style_screen_service_due_main_main_pressed;
	lv_style_reset(&style_screen_service_due_main_main_pressed);
	lv_style_set_text_color(&style_screen_service_due_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_service_due_main_main_checked
	static lv_style_t style_screen_service_due_main_main_checked;
	lv_style_reset(&style_screen_service_due_main_main_checked);
	lv_style_set_text_color(&style_screen_service_due_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_checked, 0);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_Service_Due, LV_IMGBTN_STATE_RELEASED, NULL, &img_Service_Remainder_25x25, NULL);
	lv_imgbtn_set_src(ui->screen_Service_Due, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_22x25, NULL);
	lv_obj_add_flag(ui->screen_Service_Due, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_TachoBar0
	ui->screen_TachoBar0 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBar0, 7, 6);
	lv_obj_set_size(ui->screen_TachoBar0, 227, 75);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobar0_main_main_default
	static lv_style_t style_screen_tachobar0_main_main_default;
	lv_style_reset(&style_screen_tachobar0_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobar0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobar0_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobar0_main_main_default, 255);
	lv_obj_add_style(ui->screen_TachoBar0, &style_screen_tachobar0_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBar0, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBar0,&img_tacho_chaplets);
	lv_img_set_pivot(ui->screen_TachoBar0, 0,0);
	lv_img_set_angle(ui->screen_TachoBar0, 0);


	//Write codes screen_TachoBar0_1
	ui->screen_TachoBar0_1 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBar0_1, 3, 8);
	lv_obj_set_size(ui->screen_TachoBar0_1, 231, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobar0_1_main_main_default
	static lv_style_t style_screen_tachobar0_1_main_main_default;
	lv_style_reset(&style_screen_tachobar0_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobar0_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobar0_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobar0_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_TachoBar0_1, &style_screen_tachobar0_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBar0_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBar0_1,&_img_night_tacho_fill_001_231x78);
	lv_img_set_pivot(ui->screen_TachoBar0_1, 0,0);
	lv_img_set_angle(ui->screen_TachoBar0_1, 0);

	//Write codes screen_Fuel_Img_Icon
	ui->screen_Fuel_Img_Icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuel_Img_Icon, 105, 248);
	lv_obj_set_size(ui->screen_Fuel_Img_Icon, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuel_img_icon_main_main_default
	static lv_style_t style_screen_fuel_img_icon_main_main_default;
	lv_style_reset(&style_screen_fuel_img_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuel_img_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuel_img_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuel_img_icon_main_main_default, 0);
	lv_obj_add_style(ui->screen_Fuel_Img_Icon, &style_screen_fuel_img_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuel_Img_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuel_Img_Icon,&_img_night_display_units_fuel_icon_30x30);
	lv_img_set_pivot(ui->screen_Fuel_Img_Icon, 0,0);
	lv_img_set_angle(ui->screen_Fuel_Img_Icon, 0);

	//Write codes screen_imgOilTelltale
	ui->screen_imgOilTelltale = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgOilTelltale, 4, 290);
	lv_obj_set_size(ui->screen_imgOilTelltale, 34, 14);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgoiltelltale_main_main_default
	static lv_style_t style_screen_imgoiltelltale_main_main_default;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_default);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgoiltelltale_main_main_default, 254);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgoiltelltale_main_main_pressed
	static lv_style_t style_screen_imgoiltelltale_main_main_pressed;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgoiltelltale_main_main_checked
	static lv_style_t style_screen_imgoiltelltale_main_main_checked;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_checked);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgOilTelltale, LV_IMGBTN_STATE_RELEASED, NULL, &new_oil_telltale, NULL);
	lv_imgbtn_set_src(ui->screen_imgOilTelltale, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_32x13, NULL);
	lv_obj_add_flag(ui->screen_imgOilTelltale, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_Batt_Outline
	ui->screen_Batt_Outline = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Batt_Outline, 26, 111);
	lv_obj_set_size(ui->screen_Batt_Outline, 20, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_batt_outline_main_main_default
	static lv_style_t style_screen_batt_outline_main_main_default;
	lv_style_reset(&style_screen_batt_outline_main_main_default);
	lv_style_set_img_recolor(&style_screen_batt_outline_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_batt_outline_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_batt_outline_main_main_default, 255);
	lv_obj_add_style(ui->screen_Batt_Outline, &style_screen_batt_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Batt_Outline, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Batt_Outline,&_Layer_0_9x9);
	lv_img_set_pivot(ui->screen_Batt_Outline, 0,0);
	lv_img_set_angle(ui->screen_Batt_Outline, 0);		

	//Write codes screen_Signal_1
	ui->screen_Signal_1 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Signal_1, 200, 111);
	lv_obj_set_size(ui->screen_Signal_1, 14, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_signal_1_main_main_default
	static lv_style_t style_screen_signal_1_main_main_default;
	lv_style_reset(&style_screen_signal_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_signal_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_signal_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_signal_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_Signal_1, &style_screen_signal_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Signal_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Signal_1,&_Layer_0_9x9);
	lv_img_set_pivot(ui->screen_Signal_1, 0,0);
	lv_img_set_angle(ui->screen_Signal_1, 0);

    //Write codes screen_Fuel_low_mMarker
	ui->screen_Fuel_low_mMarker = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuel_low_mMarker, 35, 276);
	lv_obj_set_size(ui->screen_Fuel_low_mMarker, 11, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuel_low_mmarker_main_main_default
	static lv_style_t style_screen_fuel_low_mmarker_main_main_default;
	lv_style_reset(&style_screen_fuel_low_mmarker_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuel_low_mmarker_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuel_low_mmarker_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuel_low_mmarker_main_main_default, 255);
	lv_obj_add_style(ui->screen_Fuel_low_mMarker, &style_screen_fuel_low_mmarker_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuel_low_mMarker, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuel_low_mMarker,&_img_night_fuel_low_marker_11x13);
	lv_img_set_pivot(ui->screen_Fuel_low_mMarker, 0,0);
	lv_img_set_angle(ui->screen_Fuel_low_mMarker, 0);


	/*Intermediate changes only*/

	//Write codes screen_trip_container
	ui->screen_trip_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_trip_container, 30, 167);
	lv_obj_set_size(ui->screen_trip_container, 195, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_container_main_main_default
	static lv_style_t style_screen_trip_container_main_main_default;
	lv_style_reset(&style_screen_trip_container_main_main_default);
	lv_style_set_radius(&style_screen_trip_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_trip_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_trip_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_trip_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_trip_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_trip_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_container, &style_screen_trip_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

     	//Write codes screen_trip_val_1
	ui->screen_trip_val_1 = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_val_1, 71, 14);
	lv_obj_set_size(ui->screen_trip_val_1, 49, 18);
	lv_label_set_text(ui->screen_trip_val_1, "999.9");
	lv_label_set_long_mode(ui->screen_trip_val_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_val_1, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_val_1_main_main_default
	static lv_style_t style_screen_trip_val_1_main_main_default;
	lv_style_reset(&style_screen_trip_val_1_main_main_default);
	lv_style_set_radius(&style_screen_trip_val_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_val_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_val_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_val_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_val_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_val_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_trip_val_1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_trip_val_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_val_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_val_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_val_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_val_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_val_1, &style_screen_trip_val_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


    //Write codes screen_trip_lbl1
	ui->screen_trip_lbl1 = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_lbl1, 37, 15);
	lv_obj_set_size(ui->screen_trip_lbl1, 26, 21);
	lv_label_set_text(ui->screen_trip_lbl1, "Trip");
	lv_label_set_long_mode(ui->screen_trip_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_lbl1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_lbl1_main_main_default
	static lv_style_t style_screen_trip_lbl1_main_main_default;
	lv_style_reset(&style_screen_trip_lbl1_main_main_default);
	lv_style_set_radius(&style_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_lbl1_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_trip_lbl1_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_lbl1, &style_screen_trip_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);




    //Write codes screen_trip_unit_1
	ui->screen_trip_unit_1 = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_unit_1, 124, 16);
	lv_obj_set_size(ui->screen_trip_unit_1, 56, 18);
	lv_label_set_text(ui->screen_trip_unit_1, "L/100km");
	lv_label_set_long_mode(ui->screen_trip_unit_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_unit_1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_unit_1_main_main_default
	static lv_style_t style_screen_trip_unit_1_main_main_default;
	lv_style_reset(&style_screen_trip_unit_1_main_main_default);
	lv_style_set_radius(&style_screen_trip_unit_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_unit_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_unit_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_unit_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_unit_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_unit_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_trip_unit_1_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_screen_trip_unit_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_unit_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_unit_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_unit_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_unit_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_unit_1, &style_screen_trip_unit_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes screen_trip_lbl_2
	ui->screen_trip_lbl_2 = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_lbl_2, 34, 43);
	lv_obj_set_size(ui->screen_trip_lbl_2, 33, 21);
	lv_label_set_text(ui->screen_trip_lbl_2, "Time");
	lv_label_set_long_mode(ui->screen_trip_lbl_2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_lbl_2, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_lbl_2_main_main_default
	static lv_style_t style_screen_trip_lbl_2_main_main_default;
	lv_style_reset(&style_screen_trip_lbl_2_main_main_default);
	lv_style_set_radius(&style_screen_trip_lbl_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_lbl_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_lbl_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_lbl_2_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_trip_lbl_2_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_trip_lbl_2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_lbl_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_lbl_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_lbl_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_lbl_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_lbl_2, &style_screen_trip_lbl_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


		//Write codes screen_trip_hh_lbl
	ui->screen_trip_hh_lbl = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_hh_lbl, 98, 44);
	lv_obj_set_size(ui->screen_trip_hh_lbl, 11, 12);
	lv_label_set_text(ui->screen_trip_hh_lbl, "h");
	lv_label_set_long_mode(ui->screen_trip_hh_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_hh_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_hh_lbl_main_main_default
	static lv_style_t style_screen_trip_hh_lbl_main_main_default;
	lv_style_reset(&style_screen_trip_hh_lbl_main_main_default);
	lv_style_set_radius(&style_screen_trip_hh_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_hh_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_hh_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_hh_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_hh_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_hh_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_trip_hh_lbl_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_trip_hh_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_hh_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_hh_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_hh_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_hh_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_hh_lbl, &style_screen_trip_hh_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


   //Write codes screen_trip_mm_lbl
	ui->screen_trip_mm_lbl = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_mm_lbl, 135, 44);
	lv_obj_set_size(ui->screen_trip_mm_lbl, 12, 12);
	lv_label_set_text(ui->screen_trip_mm_lbl, "m");
	lv_label_set_long_mode(ui->screen_trip_mm_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_mm_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_mm_lbl_main_main_default
	static lv_style_t style_screen_trip_mm_lbl_main_main_default;
	lv_style_reset(&style_screen_trip_mm_lbl_main_main_default);
	lv_style_set_radius(&style_screen_trip_mm_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_mm_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_mm_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_mm_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_mm_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_mm_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_trip_mm_lbl_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_trip_mm_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_mm_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_mm_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_mm_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_mm_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_mm_lbl, &style_screen_trip_mm_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);



 	//Write codes screen_trip_up_arrow
	ui->screen_trip_up_arrow = lv_img_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_up_arrow, 82, 0);
	lv_obj_set_size(ui->screen_trip_up_arrow, 14, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_up_arrow_main_main_default
	static lv_style_t style_screen_trip_up_arrow_main_main_default;
	lv_style_reset(&style_screen_trip_up_arrow_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_up_arrow_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_up_arrow_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_trip_up_arrow_main_main_default, 255);
	lv_obj_add_style(ui->screen_trip_up_arrow, &style_screen_trip_up_arrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_trip_up_arrow, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_trip_up_arrow,&new_trip_up_arrow);
	lv_img_set_pivot(ui->screen_trip_up_arrow, 0,0);
	lv_img_set_angle(ui->screen_trip_up_arrow, 0);



   //Write codes screen_trip_down_arrow
	ui->screen_trip_down_arrow = lv_img_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_down_arrow, 82, 68);
	lv_obj_set_size(ui->screen_trip_down_arrow, 14, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_down_arrow_main_main_default
	static lv_style_t style_screen_trip_down_arrow_main_main_default;
	lv_style_reset(&style_screen_trip_down_arrow_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_down_arrow_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_down_arrow_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_trip_down_arrow_main_main_default, 255);
	lv_obj_add_style(ui->screen_trip_down_arrow, &style_screen_trip_down_arrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_trip_down_arrow, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_trip_down_arrow,&new_trip_down_arrow);
	lv_img_set_pivot(ui->screen_trip_down_arrow, 0,0);
	lv_img_set_angle(ui->screen_trip_down_arrow, 0);


    //Write codes screen_Sub_Con
	ui->screen_Sub_Con = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Sub_Con, 198, 147);
	lv_obj_set_size(ui->screen_Sub_Con, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_screen_sub_con_main_main_default
	static lv_style_t style_screen_sub_con_main_main_default;
	lv_style_reset(&style_screen_sub_con_main_main_default);
	lv_style_set_img_recolor(&style_screen_sub_con_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_sub_con_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_sub_con_main_main_default, 255);
	lv_obj_add_style(ui->screen_Sub_Con, &style_screen_sub_con_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Sub_Con, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Sub_Con,&subbtn_night_24x24);
	lv_img_set_pivot(ui->screen_Sub_Con, 0,0);
    lv_img_set_angle(ui->screen_Sub_Con, 0);


   	//Write codes screen_Clock_hour
	ui->screen_Clock_hour = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Clock_hour, 86, 69);
	lv_obj_set_size(ui->screen_Clock_hour, 13, 12);
	lv_label_set_text(ui->screen_Clock_hour, "24");
	lv_label_set_long_mode(ui->screen_Clock_hour, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Clock_hour, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_hour_main_main_default
	static lv_style_t style_screen_clock_hour_main_main_default;
	lv_style_reset(&style_screen_clock_hour_main_main_default);
	lv_style_set_radius(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_clock_hour_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_clock_hour_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_clock_hour_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_text_color(&style_screen_clock_hour_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_clock_hour_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_clock_hour_main_main_default, 0);
	lv_obj_add_style(ui->screen_Clock_hour, &style_screen_clock_hour_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


   
	//Write codes screen_Clock_Colan
	ui->screen_Clock_Colan = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Clock_Colan, 109, 69);
	lv_obj_set_size(ui->screen_Clock_Colan, 3, 10);
	lv_label_set_text(ui->screen_Clock_Colan, ":");
	lv_label_set_long_mode(ui->screen_Clock_Colan, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Clock_Colan, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_colan_main_main_default
	static lv_style_t style_screen_clock_colan_main_main_default;
	lv_style_reset(&style_screen_clock_colan_main_main_default);
	lv_style_set_radius(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_clock_colan_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_clock_colan_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_clock_colan_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_text_color(&style_screen_clock_colan_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_clock_colan_main_main_default, &lv_font_FjallaOne_Regular_15);
	lv_style_set_text_letter_space(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_clock_colan_main_main_default, 0);
	lv_obj_add_style(ui->screen_Clock_Colan, &style_screen_clock_colan_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);



  //Write codes screen_Clock_min
	ui->screen_Clock_min = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Clock_min, 113, 69);
	lv_obj_set_size(ui->screen_Clock_min, 15, 12);
	lv_label_set_text(ui->screen_Clock_min, "60");
	lv_label_set_long_mode(ui->screen_Clock_min, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Clock_min, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_min_main_main_default
	static lv_style_t style_screen_clock_min_main_main_default;
	lv_style_reset(&style_screen_clock_min_main_main_default);
	lv_style_set_radius(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_clock_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_clock_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_clock_min_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_text_color(&style_screen_clock_min_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_clock_min_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_clock_min_main_main_default, 0);
	lv_obj_add_style(ui->screen_Clock_min, &style_screen_clock_min_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);




   //Write codes screen_Clock_Am
	ui->screen_Clock_Am = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Clock_Am, 118, 69);
	lv_obj_set_size(ui->screen_Clock_Am, 16, 12);
	lv_label_set_text(ui->screen_Clock_Am, "AM");
	lv_label_set_long_mode(ui->screen_Clock_Am, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Clock_Am, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_am_main_main_default
	static lv_style_t style_screen_clock_am_main_main_default;
	lv_style_reset(&style_screen_clock_am_main_main_default);
	lv_style_set_radius(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_clock_am_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_clock_am_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_clock_am_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_text_color(&style_screen_clock_am_main_main_default, lv_color_make(0xfa, 0xfa, 0xfa));
	lv_style_set_text_font(&style_screen_clock_am_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_clock_am_main_main_default, 0);
	lv_obj_add_style(ui->screen_Clock_Am, &style_screen_clock_am_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);



   //Write codes screen_trip_hr_lbl
	ui->screen_trip_hr_lbl = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_hr_lbl, 71, 42);
	lv_obj_set_size(ui->screen_trip_hr_lbl, 21, 18);
	lv_label_set_text(ui->screen_trip_hr_lbl, "99");
	lv_label_set_long_mode(ui->screen_trip_hr_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_hr_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_hr_lbl_main_main_default
	static lv_style_t style_screen_trip_hr_lbl_main_main_default;
	lv_style_reset(&style_screen_trip_hr_lbl_main_main_default);
	lv_style_set_radius(&style_screen_trip_hr_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_hr_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_hr_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_hr_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_hr_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_hr_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_trip_hr_lbl_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_trip_hr_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_hr_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_hr_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_hr_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_hr_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_hr_lbl, &style_screen_trip_hr_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


    //Write codes screen_trip_mi_lbl
	ui->screen_trip_mi_lbl = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_mi_lbl, 109, 42);
	lv_obj_set_size(ui->screen_trip_mi_lbl, 21, 18);
	lv_label_set_text(ui->screen_trip_mi_lbl, "99");
	lv_label_set_long_mode(ui->screen_trip_mi_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_mi_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_mi_lbl_main_main_default
	static lv_style_t style_screen_trip_mi_lbl_main_main_default;
	lv_style_reset(&style_screen_trip_mi_lbl_main_main_default);
	lv_style_set_radius(&style_screen_trip_mi_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_mi_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_mi_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_mi_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_mi_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_mi_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_trip_mi_lbl_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_trip_mi_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_mi_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_mi_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_mi_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_mi_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_mi_lbl, &style_screen_trip_mi_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	
	//Write codes screen_contscr_1
	ui->screen_contscr_1 = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_contscr_1, 30, 167);
	lv_obj_set_size(ui->screen_contscr_1, 210, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_contscr_1_main_main_default
	static lv_style_t style_screen_contscr_1_main_main_default;
	lv_style_reset(&style_screen_contscr_1_main_main_default);
	lv_style_set_radius(&style_screen_contscr_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_contscr_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_contscr_1_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_contscr_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_contscr_1_main_main_default, 0);
	lv_style_set_border_color(&style_screen_contscr_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_contscr_1_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_contscr_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_contscr_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_contscr_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_contscr_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_contscr_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_contscr_1, &style_screen_contscr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
   
   //Write codes screen_L2_val
	ui->screen_L2_val = lv_label_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_L2_val, 81, 45);
	lv_obj_set_size(ui->screen_L2_val, 104, 18);
	lv_label_set_text(ui->screen_L2_val, "00 h 00m");
	lv_label_set_long_mode(ui->screen_L2_val, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_L2_val, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_l2_val_main_main_default
	static lv_style_t style_screen_l2_val_main_main_default;
	lv_style_reset(&style_screen_l2_val_main_main_default);
	lv_style_set_radius(&style_screen_l2_val_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_l2_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_l2_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_l2_val_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_l2_val_main_main_default, 0);
	lv_style_set_text_color(&style_screen_l2_val_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_l2_val_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_l2_val_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_l2_val_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_l2_val_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_l2_val_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_l2_val_main_main_default, 0);
	lv_obj_add_style(ui->screen_L2_val, &style_screen_l2_val_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

   //Write codes screen_trip_spedo_cont
	ui->screen_trip_spedo_cont = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_trip_spedo_cont, 57, 97);
	lv_obj_set_size(ui->screen_trip_spedo_cont, 160, 67);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_spedo_cont_main_main_default
	static lv_style_t style_screen_trip_spedo_cont_main_main_default;
	lv_style_reset(&style_screen_trip_spedo_cont_main_main_default);
	lv_style_set_radius(&style_screen_trip_spedo_cont_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_spedo_cont_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_trip_spedo_cont_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_trip_spedo_cont_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_spedo_cont_main_main_default, 0);
	lv_style_set_border_color(&style_screen_trip_spedo_cont_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_trip_spedo_cont_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_trip_spedo_cont_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_spedo_cont_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_spedo_cont_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_spedo_cont_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_spedo_cont_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_spedo_cont, &style_screen_trip_spedo_cont_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

		//Write codes screen_SPD_Int_0
	ui->screen_SPD_Int_0 = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_SPD_Int_0, 76, -1);
	lv_obj_set_size(ui->screen_SPD_Int_0, 24, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_spd_int_0_main_main_default
	static lv_style_t style_screen_spd_int_0_main_main_default;
	lv_style_reset(&style_screen_spd_int_0_main_main_default);
	lv_style_set_img_recolor(&style_screen_spd_int_0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_spd_int_0_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_spd_int_0_main_main_default, 0);
	lv_obj_add_style(ui->screen_SPD_Int_0, &style_screen_spd_int_0_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_SPD_Int_0, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_SPD_Int_0,&_ISP0_24x47);
	lv_img_set_pivot(ui->screen_SPD_Int_0, 0,0);
	lv_img_set_angle(ui->screen_SPD_Int_0, 0);


	//Write codes screen_trip_spedo_line
	ui->screen_trip_spedo_line = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_trip_spedo_line, 0, 63);
	lv_obj_set_size(ui->screen_trip_spedo_line, 134, 2);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_spedo_line_main_main_default
	static lv_style_t style_screen_trip_spedo_line_main_main_default;
	lv_style_reset(&style_screen_trip_spedo_line_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_spedo_line_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_spedo_line_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_trip_spedo_line_main_main_default, 255);
	lv_obj_add_style(ui->screen_trip_spedo_line, &style_screen_trip_spedo_line_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_trip_spedo_line, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_trip_spedo_line,&_img_center_divider_line_134x2);
	lv_img_set_pivot(ui->screen_trip_spedo_line, 0,0);
	lv_img_set_angle(ui->screen_trip_spedo_line, 0);




	//Write codes screen_trip_spedo_s1
	ui->screen_trip_spedo_s1 = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_trip_spedo_s1, 76, 2);
	lv_obj_set_size(ui->screen_trip_spedo_s1, 24, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_spedo_s1_main_main_default
	static lv_style_t style_screen_trip_spedo_s1_main_main_default;
	lv_style_reset(&style_screen_trip_spedo_s1_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_spedo_s1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_spedo_s1_main_main_default, 176);
	lv_style_set_img_opa(&style_screen_trip_spedo_s1_main_main_default, 255);
	lv_obj_add_style(ui->screen_trip_spedo_s1, &style_screen_trip_spedo_s1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_trip_spedo_s1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_trip_spedo_s1,&_ISP0_24x47);
	lv_img_set_pivot(ui->screen_trip_spedo_s1, 0,0);
	lv_img_set_angle(ui->screen_trip_spedo_s1, 0);
	lv_obj_set_style_img_opa(ui->screen_trip_spedo_s1,255, 0);
	lv_obj_set_style_img_recolor(ui->screen_trip_spedo_s1, lv_color_white(), 0);



	//Write codes screen_trip_spedo_s2
	ui->screen_trip_spedo_s2 = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_trip_spedo_s2, 46, 2);
	lv_obj_set_size(ui->screen_trip_spedo_s2, 24, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_spedo_s2_main_main_default
	static lv_style_t style_screen_trip_spedo_s2_main_main_default;
	lv_style_reset(&style_screen_trip_spedo_s2_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_spedo_s2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_spedo_s2_main_main_default, 176);
	lv_style_set_img_opa(&style_screen_trip_spedo_s2_main_main_default, 255);
	lv_obj_add_style(ui->screen_trip_spedo_s2, &style_screen_trip_spedo_s2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_trip_spedo_s2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_trip_spedo_s2,&_ISP0_24x47);
	lv_img_set_pivot(ui->screen_trip_spedo_s2, 0,0);
	lv_img_set_angle(ui->screen_trip_spedo_s2, 0);
	lv_obj_set_style_img_opa(ui->screen_trip_spedo_s2,255, 0);
	lv_obj_set_style_img_recolor(ui->screen_trip_spedo_s2, lv_color_Intermediate_Grey(), 0);
	set_obj_opa(ui->screen_trip_spedo_s2,50);

    	//Write codes screen_trip_spedo_s3
	ui->screen_trip_spedo_s3 = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_trip_spedo_s3, 17, 2);
	lv_obj_set_size(ui->screen_trip_spedo_s3, 24, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_spedo_s3_main_main_default
	static lv_style_t style_screen_trip_spedo_s3_main_main_default;
	lv_style_reset(&style_screen_trip_spedo_s3_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_spedo_s3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_spedo_s3_main_main_default, 176);
	lv_style_set_img_opa(&style_screen_trip_spedo_s3_main_main_default, 255);
	lv_obj_add_style(ui->screen_trip_spedo_s3, &style_screen_trip_spedo_s3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_trip_spedo_s3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_trip_spedo_s3,&_ISP0_24x47);
	lv_img_set_pivot(ui->screen_trip_spedo_s3, 0,0);
	lv_img_set_angle(ui->screen_trip_spedo_s3, 0);
	lv_obj_set_style_img_opa(ui->screen_trip_spedo_s3,255, 0);
	lv_obj_set_style_img_recolor(ui->screen_trip_spedo_s3, lv_color_Intermediate_Grey(), 0);
	set_obj_opa(ui->screen_trip_spedo_s3,50);



    //Write codes screen_L1_lbl
	ui->screen_L1_lbl = lv_label_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_L1_lbl, 0, 21);
	lv_obj_set_size(ui->screen_L1_lbl, 79, 17);
	lv_label_set_text(ui->screen_L1_lbl, "Av Speed");
	lv_label_set_long_mode(ui->screen_L1_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_L1_lbl, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_l1_lbl_main_main_default
	static lv_style_t style_screen_l1_lbl_main_main_default;
	lv_style_reset(&style_screen_l1_lbl_main_main_default);
	lv_style_set_radius(&style_screen_l1_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_l1_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_l1_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_l1_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_l1_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_l1_lbl_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_l1_lbl_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_l1_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_l1_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_l1_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_l1_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_l1_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_L1_lbl, &style_screen_l1_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);






	//Write codes screen_L1_val
	ui->screen_L1_val = lv_label_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_L1_val, 81, 18);
	lv_obj_set_size(ui->screen_L1_val, 48, 18);
	lv_label_set_text(ui->screen_L1_val, "123.9");
	lv_label_set_long_mode(ui->screen_L1_val, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_L1_val,LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_l1_val_main_main_default
	static lv_style_t style_screen_l1_val_main_main_default;
	lv_style_reset(&style_screen_l1_val_main_main_default);
	lv_style_set_radius(&style_screen_l1_val_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_l1_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_l1_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_l1_val_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_l1_val_main_main_default, 0);
	lv_style_set_text_color(&style_screen_l1_val_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_l1_val_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_l1_val_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_l1_val_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_l1_val_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_l1_val_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_l1_val_main_main_default, 0);
	lv_obj_add_style(ui->screen_L1_val, &style_screen_l1_val_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);




		//Write codes screen_L1_unit
	ui->screen_L1_unit = lv_label_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_L1_unit, 131, 21);
	lv_obj_set_size(ui->screen_L1_unit, 56, 19);
	lv_label_set_text(ui->screen_L1_unit, "L/100km");
	lv_label_set_long_mode(ui->screen_L1_unit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_L1_unit, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_l1_unit_main_main_default
	static lv_style_t style_screen_l1_unit_main_main_default;
	lv_style_reset(&style_screen_l1_unit_main_main_default);
	lv_style_set_radius(&style_screen_l1_unit_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_l1_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_l1_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_l1_unit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_l1_unit_main_main_default, 0);
	lv_style_set_text_color(&style_screen_l1_unit_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_l1_unit_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_screen_l1_unit_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_l1_unit_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_l1_unit_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_l1_unit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_l1_unit_main_main_default, 0);
	lv_obj_add_style(ui->screen_L1_unit, &style_screen_l1_unit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    

	 
	//Write codes screen_L2_lbl
	ui->screen_L2_lbl = lv_label_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_L2_lbl, 0, 47);
	lv_obj_set_size(ui->screen_L2_lbl, 79, 17);
	lv_label_set_text(ui->screen_L2_lbl, "Service Due");
	lv_label_set_long_mode(ui->screen_L2_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_L2_lbl, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_l2_lbl_main_main_default
	static lv_style_t style_screen_l2_lbl_main_main_default;
	lv_style_reset(&style_screen_l2_lbl_main_main_default);
	lv_style_set_radius(&style_screen_l2_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_l2_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_l2_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_l2_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_l2_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_l2_lbl_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_l2_lbl_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_l2_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_l2_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_l2_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_l2_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_l2_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_L2_lbl, &style_screen_l2_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_L2_unit
	ui->screen_L2_unit = lv_label_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_L2_unit, 131, 46);
	lv_obj_set_size(ui->screen_L2_unit, 56, 19);
	lv_label_set_text(ui->screen_L2_unit, "L/100km");
	lv_label_set_long_mode(ui->screen_L2_unit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_L2_unit, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_l2_unit_main_main_default
	static lv_style_t style_screen_l2_unit_main_main_default;
	lv_style_reset(&style_screen_l2_unit_main_main_default);
	lv_style_set_radius(&style_screen_l2_unit_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_l2_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_l2_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_l2_unit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_l2_unit_main_main_default, 0);
	lv_style_set_text_color(&style_screen_l2_unit_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_l2_unit_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_screen_l2_unit_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_l2_unit_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_l2_unit_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_l2_unit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_l2_unit_main_main_default, 0);
	lv_obj_add_style(ui->screen_L2_unit, &style_screen_l2_unit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes screen_up_arr
	ui->screen_up_arr = lv_img_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_up_arr, 82, 0);
	lv_obj_set_size(ui->screen_up_arr, 14, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_up_arr_main_main_default
	static lv_style_t style_screen_up_arr_main_main_default;
	lv_style_reset(&style_screen_up_arr_main_main_default);
	lv_style_set_img_recolor(&style_screen_up_arr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_up_arr_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_up_arr_main_main_default, 255);
	lv_obj_add_style(ui->screen_up_arr, &style_screen_up_arr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_up_arr, LV_OBJ_FLAG_CLICKABLE);
	//lv_img_set_src(ui->screen_up_arr,&_white_12x7);
	lv_img_set_src(ui->screen_up_arr,&new_trip_up_arrow);
	lv_img_set_pivot(ui->screen_up_arr, 0,0);
	lv_img_set_angle(ui->screen_up_arr, 0);

	//Write codes screen_dw_arr
	ui->screen_dw_arr = lv_img_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_dw_arr, 82, 68);
	lv_obj_set_size(ui->screen_dw_arr, 14, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_dw_arr_main_main_default
	static lv_style_t style_screen_dw_arr_main_main_default;
	lv_style_reset(&style_screen_dw_arr_main_main_default);
	lv_style_set_img_recolor(&style_screen_dw_arr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_dw_arr_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_dw_arr_main_main_default, 255);
	lv_obj_add_style(ui->screen_dw_arr, &style_screen_dw_arr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_dw_arr, LV_OBJ_FLAG_CLICKABLE);
	//lv_img_set_src(ui->screen_dw_arr,&_DowAre_12x7);
	lv_img_set_src(ui->screen_dw_arr,&new_trip_down_arrow);
	lv_img_set_pivot(ui->screen_dw_arr, 0,0);
	lv_img_set_angle(ui->screen_dw_arr, 0);

	
	//Write codes screen_trip_km_unit_Img
	ui->screen_trip_km_unit_Img = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_trip_km_unit_Img, 108, 33);
	lv_obj_set_size(ui->screen_trip_km_unit_Img, 27, 16);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_km_unit_img_main_main_default
	static lv_style_t style_screen_trip_km_unit_img_main_main_default;
	lv_style_reset(&style_screen_trip_km_unit_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_km_unit_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_km_unit_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_trip_km_unit_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_trip_km_unit_Img, &style_screen_trip_km_unit_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_trip_km_unit_Img,&km_text_unit_night_Img);

	
	//Write codes screen_Trip_blank
	ui->screen_Trip_blank = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Trip_blank, 105, 255);
	lv_obj_set_size(ui->screen_Trip_blank, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_blank_main_main_default
	static lv_style_t style_screen_trip_blank_main_main_default;
	lv_style_reset(&style_screen_trip_blank_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_blank_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_blank_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_trip_blank_main_main_default, 255);
	lv_obj_add_style(ui->screen_Trip_blank, &style_screen_trip_blank_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Trip_blank, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Trip_blank,&_BlankTrip_30x30);
	lv_img_set_pivot(ui->screen_Trip_blank, 0,0);
	lv_img_set_angle(ui->screen_Trip_blank, 0);

	//Write codes screen_blu_msg_icon
	ui->screen_blu_msg_icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_blu_msg_icon, 42, 87);
	lv_obj_set_size(ui->screen_blu_msg_icon, 20, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_blu_msg_icon_main_main_default
	static lv_style_t style_screen_blu_msg_icon_main_main_default;
	lv_style_reset(&style_screen_blu_msg_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_blu_msg_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_blu_msg_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_blu_msg_icon_main_main_default, 255);
	lv_obj_add_style(ui->screen_blu_msg_icon, &style_screen_blu_msg_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_blu_msg_icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_blu_msg_icon,&_night_Message_black_20x12);
	lv_img_set_pivot(ui->screen_blu_msg_icon, 0,0);
	lv_img_set_angle(ui->screen_blu_msg_icon, 0);

	//Write codes screen_blu_mis_call_icon
	ui->screen_blu_mis_call_icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_blu_mis_call_icon, 183, 87);
	lv_obj_set_size(ui->screen_blu_mis_call_icon, 15, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_blu_mis_call_icon_main_main_default
	static lv_style_t style_screen_blu_mis_call_icon_main_main_default;
	lv_style_reset(&style_screen_blu_mis_call_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_blu_mis_call_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_blu_mis_call_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_blu_mis_call_icon_main_main_default, 255);
	lv_obj_add_style(ui->screen_blu_mis_call_icon, &style_screen_blu_mis_call_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_blu_mis_call_icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_blu_mis_call_icon,&_night_Missed_Call_15x12);
	lv_img_set_pivot(ui->screen_blu_mis_call_icon, 0,0);
	lv_img_set_angle(ui->screen_blu_mis_call_icon, 0);

	/*BLE SCREENS */

   //Write codes screen_navi_container
	ui->screen_navi_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_navi_container, 30, 167);
	lv_obj_set_size(ui->screen_navi_container, 195, 95);

	//Write style state: LV_STATE_DEFAULT for style_screen_navi_container_main_main_default
	static lv_style_t style_screen_navi_container_main_main_default;
	lv_style_reset(&style_screen_navi_container_main_main_default);
	lv_style_set_radius(&style_screen_navi_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_navi_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_navi_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_navi_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_navi_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_navi_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_navi_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_navi_container_main_main_default, 255);
	lv_style_set_pad_left(&style_screen_navi_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_navi_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_navi_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_navi_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_navi_container, &style_screen_navi_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes screen_navi_lbl
	ui->screen_navi_lbl = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_navi_lbl, 5, 6);
	lv_obj_set_size(ui->screen_navi_lbl, 100, 10);
	lv_label_set_text(ui->screen_navi_lbl, "");
	lv_label_set_long_mode(ui->screen_navi_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_navi_lbl, LV_TEXT_ALIGN_CENTER, 0);

    //Write codes screen_navi_val
	ui->screen_navi_val = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_navi_val, 20, 8);
	lv_obj_set_size(ui->screen_navi_val, 30, 17);
	lv_label_set_text(ui->screen_navi_val, "9999");
	lv_label_set_long_mode(ui->screen_navi_val, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_navi_val, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_navi_val_main_main_default
	static lv_style_t style_screen_navi_val_main_main_default;
	lv_style_reset(&style_screen_navi_val_main_main_default);
	lv_style_set_radius(&style_screen_navi_val_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_navi_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_navi_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_navi_val_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_navi_val_main_main_default, 0);
	lv_style_set_text_color(&style_screen_navi_val_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_navi_val_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_navi_val_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_navi_val_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_navi_val_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_navi_val_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_navi_val_main_main_default, 0);
	lv_obj_add_style(ui->screen_navi_val, &style_screen_navi_val_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    
	//Write codes screen_navi_unit
	ui->screen_navi_unit = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_navi_unit, 30, 35);
	lv_obj_set_size(ui->screen_navi_unit, 26, 11);
	lv_label_set_text(ui->screen_navi_unit, "km");
	lv_label_set_long_mode(ui->screen_navi_unit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_navi_unit, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_navi_unit_main_main_default
	static lv_style_t style_screen_navi_unit_main_main_default;
	lv_style_reset(&style_screen_navi_unit_main_main_default);
	lv_style_set_radius(&style_screen_navi_unit_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_navi_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_navi_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_navi_unit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_navi_unit_main_main_default, 0);
	lv_style_set_text_color(&style_screen_navi_unit_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_navi_unit_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_screen_navi_unit_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_navi_unit_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_navi_unit_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_navi_unit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_navi_unit_main_main_default, 0);
	lv_obj_add_style(ui->screen_navi_unit, &style_screen_navi_unit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    //Write codes screen_nav_est
	ui->screen_nav_est = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_nav_est, 143, 35);
	lv_obj_set_size(ui->screen_nav_est, 26, 14);
	lv_label_set_text(ui->screen_nav_est, "ETA");
	lv_label_set_long_mode(ui->screen_nav_est, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_nav_est, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_nav_est_main_main_default
	static lv_style_t style_screen_nav_est_main_main_default;
	lv_style_reset(&style_screen_nav_est_main_main_default);
	lv_style_set_radius(&style_screen_nav_est_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_nav_est_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_nav_est_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_nav_est_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_nav_est_main_main_default, 0);
	lv_style_set_text_color(&style_screen_nav_est_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_nav_est_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_nav_est_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_nav_est_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_nav_est_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_nav_est_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_nav_est_main_main_default, 0);
	lv_obj_add_style(ui->screen_nav_est, &style_screen_nav_est_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


    //Write codes screen_nav_clo_hr
	ui->screen_nav_clo_hr = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_nav_clo_hr, 130, 8);
	lv_obj_set_size(ui->screen_nav_clo_hr, 18, 15);
	lv_label_set_text(ui->screen_nav_clo_hr, "99");
	lv_label_set_long_mode(ui->screen_nav_clo_hr, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_nav_clo_hr, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_nav_clo_hr_main_main_default
	static lv_style_t style_screen_nav_clo_hr_main_main_default;
	lv_style_reset(&style_screen_nav_clo_hr_main_main_default);
	lv_style_set_radius(&style_screen_nav_clo_hr_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_nav_clo_hr_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_nav_clo_hr_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_nav_clo_hr_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_nav_clo_hr_main_main_default, 0);
	lv_style_set_text_color(&style_screen_nav_clo_hr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_nav_clo_hr_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_nav_clo_hr_main_main_default, 0);
	lv_obj_add_style(ui->screen_nav_clo_hr, &style_screen_nav_clo_hr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_nav_clo_colon
	ui->screen_nav_clo_colon = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_nav_clo_colon, 148, 8);
	lv_obj_set_size(ui->screen_nav_clo_colon, 4, 13);
	lv_label_set_text(ui->screen_nav_clo_colon, ":");
	lv_label_set_long_mode(ui->screen_nav_clo_colon, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_nav_clo_colon, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_nav_clo_colon_main_main_default
	static lv_style_t style_screen_nav_clo_colon_main_main_default;
	lv_style_reset(&style_screen_nav_clo_colon_main_main_default);
	lv_style_set_radius(&style_screen_nav_clo_colon_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_nav_clo_colon_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_nav_clo_colon_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_nav_clo_colon_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_nav_clo_colon_main_main_default, 0);
	lv_style_set_text_color(&style_screen_nav_clo_colon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_nav_clo_colon_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_nav_clo_colon_main_main_default, 0);
	lv_obj_add_style(ui->screen_nav_clo_colon, &style_screen_nav_clo_colon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_nav_clo_min
	ui->screen_nav_clo_min = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_nav_clo_min, 153, 8);
	lv_obj_set_size(ui->screen_nav_clo_min, 17, 15);
	lv_label_set_text(ui->screen_nav_clo_min, "99");
	lv_label_set_long_mode(ui->screen_nav_clo_min, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_nav_clo_min, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_nav_clo_min_main_main_default
	static lv_style_t style_screen_nav_clo_min_main_main_default;
	lv_style_reset(&style_screen_nav_clo_min_main_main_default);
	lv_style_set_radius(&style_screen_nav_clo_min_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_nav_clo_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_nav_clo_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_nav_clo_min_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_nav_clo_min_main_main_default, 0);
	lv_style_set_text_color(&style_screen_nav_clo_min_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_nav_clo_min_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_nav_clo_min_main_main_default, 0);
	lv_obj_add_style(ui->screen_nav_clo_min, &style_screen_nav_clo_min_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


    //Write codes screen_nav_clo_am
	ui->screen_nav_clo_am = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_nav_clo_am, 174, 8);
	lv_obj_set_size(ui->screen_nav_clo_am, 19, 15);
	lv_label_set_text(ui->screen_nav_clo_am, "AM");
	lv_label_set_long_mode(ui->screen_nav_clo_am, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_nav_clo_am, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_nav_clo_am_main_main_default
	static lv_style_t style_screen_nav_clo_am_main_main_default;
	lv_style_reset(&style_screen_nav_clo_am_main_main_default);
	lv_style_set_radius(&style_screen_nav_clo_am_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_nav_clo_am_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_nav_clo_am_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_nav_clo_am_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_nav_clo_am_main_main_default, 0);
	lv_style_set_text_color(&style_screen_nav_clo_am_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_nav_clo_am_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_nav_clo_am_main_main_default, 0);
	lv_obj_add_style(ui->screen_nav_clo_am, &style_screen_nav_clo_am_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_No_Sig_Nyt
	ui->screen_No_Sig_Nyt = lv_img_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_No_Sig_Nyt, 67, 54);
	lv_obj_set_size(ui->screen_No_Sig_Nyt, 46, 16);

	//Write style state: LV_STATE_DEFAULT for style_screen_no_sig_nyt_main_main_default
	static lv_style_t style_screen_no_sig_nyt_main_main_default;
	lv_style_reset(&style_screen_no_sig_nyt_main_main_default);
	lv_style_set_img_recolor(&style_screen_no_sig_nyt_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_no_sig_nyt_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_no_sig_nyt_main_main_default, 255);
	lv_obj_add_style(ui->screen_No_Sig_Nyt, &style_screen_no_sig_nyt_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

   //Write codes screen_nav_img
	ui->screen_nav_img = lv_img_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_nav_img, 55, 5);
	lv_obj_set_size(ui->screen_nav_img, 70, 70);

	//Write style state: LV_STATE_DEFAULT for style_screen_nav_img_main_main_default
	static lv_style_t style_screen_nav_img_main_main_default;
	lv_style_reset(&style_screen_nav_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_nav_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_nav_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_nav_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_nav_img, &style_screen_nav_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	/* Music screen objects */
	
	//Write codes screen_music_container
	ui->screen_music_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_music_container, 30, 167);
	lv_obj_set_size(ui->screen_music_container, 197, 84);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_container_main_main_default
	static lv_style_t style_screen_music_container_main_main_default;
	lv_style_reset(&style_screen_music_container_main_main_default);
	lv_style_set_radius(&style_screen_music_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_music_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_music_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_music_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_music_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_music_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_music_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_music_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_music_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_music_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_music_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_music_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_music_container, &style_screen_music_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_slider_whitebase_img
	ui->screen_music_slider_whitebase_img = lv_img_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_slider_whitebase_img, 25, 62);
	lv_obj_set_size(ui->screen_music_slider_whitebase_img, 130, 2);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_slider_whitebase_img_main_main_default
	static lv_style_t style_screen_music_slider_whitebase_img_main_main_default;
	lv_style_reset(&style_screen_music_slider_whitebase_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_music_slider_whitebase_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_music_slider_whitebase_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_music_slider_whitebase_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_music_slider_whitebase_img, &style_screen_music_slider_whitebase_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_music_slider_whitebase_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_music_slider_whitebase_img,&_night_slider_white_100x2);
	lv_img_set_pivot(ui->screen_music_slider_whitebase_img, 0,0);
	lv_img_set_angle(ui->screen_music_slider_whitebase_img, 0);  

	//Write codes screen_music_slider_orange_img
	ui->screen_music_slider_orange_img = lv_img_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_slider_orange_img, 25, 62);
	lv_obj_set_size(ui->screen_music_slider_orange_img, 40, 2);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_slider_orange_img_main_main_default
	static lv_style_t style_screen_music_slider_orange_img_main_main_default;
	lv_style_reset(&style_screen_music_slider_orange_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_music_slider_orange_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_music_slider_orange_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_music_slider_orange_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_music_slider_orange_img, &style_screen_music_slider_orange_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_music_slider_orange_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_music_slider_orange_img,&_night_slider_orange_40x2);
	lv_img_set_pivot(ui->screen_music_slider_orange_img, 0,0);
	lv_img_set_angle(ui->screen_music_slider_orange_img, 0);

	//Write codes screen_music_slide_dot
	ui->screen_music_slide_dot = lv_img_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_slide_dot, 81, 56);
	lv_obj_set_size(ui->screen_music_slide_dot, 14, 14);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_slide_dot_main_main_default
	static lv_style_t style_screen_music_slide_dot_main_main_default;
	lv_style_reset(&style_screen_music_slide_dot_main_main_default);
	lv_style_set_img_recolor(&style_screen_music_slide_dot_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_music_slide_dot_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_music_slide_dot_main_main_default, 255);
	lv_obj_add_style(ui->screen_music_slide_dot, &style_screen_music_slide_dot_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_music_slide_dot, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_music_slide_dot,&_night_slider_dot_14x14);
	lv_img_set_pivot(ui->screen_music_slide_dot, 0,0);
	lv_img_set_angle(ui->screen_music_slide_dot, 0);

	//Write codes screen_music_lbl_1
	ui->screen_music_lbl_1 = lv_label_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_lbl_1, 24, 9);
	lv_obj_set_size(ui->screen_music_lbl_1, 153, 20);
	lv_label_set_text(ui->screen_music_lbl_1, "");
	lv_label_set_long_mode(ui->screen_music_lbl_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_music_lbl_1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_lbl_1_main_main_default
	static lv_style_t style_screen_music_lbl_1_main_main_default;
	lv_style_reset(&style_screen_music_lbl_1_main_main_default);
	lv_style_set_radius(&style_screen_music_lbl_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_music_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_music_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_music_lbl_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_music_lbl_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_music_lbl_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_music_lbl_1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_music_lbl_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_music_lbl_1, &style_screen_music_lbl_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_lbl_2
	ui->screen_music_lbl_2 = lv_label_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_lbl_2, 21, 29);
	lv_obj_set_size(ui->screen_music_lbl_2, 153, 16);
	lv_label_set_text(ui->screen_music_lbl_2, "");
	lv_label_set_long_mode(ui->screen_music_lbl_2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_music_lbl_2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_lbl_2_main_main_default
	static lv_style_t style_screen_music_lbl_2_main_main_default;
	lv_style_reset(&style_screen_music_lbl_2_main_main_default);
	lv_style_set_radius(&style_screen_music_lbl_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_music_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_music_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_music_lbl_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_music_lbl_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_music_lbl_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_music_lbl_2_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_music_lbl_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_music_lbl_2, &style_screen_music_lbl_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_lbl_3
	ui->screen_music_lbl_3 = lv_label_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_lbl_3, 15, 34);
	lv_obj_set_size(ui->screen_music_lbl_3, 153, 15);
	lv_label_set_text(ui->screen_music_lbl_3, "");
	lv_label_set_long_mode(ui->screen_music_lbl_3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_music_lbl_3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_lbl_3_main_main_default
	static lv_style_t style_screen_music_lbl_3_main_main_default;
	lv_style_reset(&style_screen_music_lbl_3_main_main_default);
	lv_style_set_radius(&style_screen_music_lbl_3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_music_lbl_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_music_lbl_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_music_lbl_3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_music_lbl_3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_music_lbl_3_main_main_default, lv_color_make(0x70, 0x6f, 0x6f));
	lv_style_set_text_font(&style_screen_music_lbl_3_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_music_lbl_3_main_main_default, 0);
	lv_obj_add_style(ui->screen_music_lbl_3, &style_screen_music_lbl_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_up_img
	ui->screen_music_up_img = lv_img_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_up_img, 85, 6);
	lv_obj_set_size(ui->screen_music_up_img, 10, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_up_img_main_main_default
	static lv_style_t style_screen_music_up_img_main_main_default;
	lv_style_reset(&style_screen_music_up_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_music_up_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_music_up_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_music_up_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_music_up_img, &style_screen_music_up_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_down_img
	ui->screen_music_down_img = lv_img_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_down_img, 85, 61);
	lv_obj_set_size(ui->screen_music_down_img, 9, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_down_img_main_main_default
	static lv_style_t style_screen_music_down_img_main_main_default;
	lv_style_reset(&style_screen_music_down_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_music_down_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_music_down_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_music_down_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_music_down_img, &style_screen_music_down_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_sub_button
	ui->screen_music_sub_button = lv_img_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_sub_button, 150, 22);
	lv_obj_set_size(ui->screen_music_sub_button, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_sub_button_main_main_default
	static lv_style_t style_screen_music_sub_button_main_main_default;
	lv_style_reset(&style_screen_music_sub_button_main_main_default);
	lv_style_set_img_recolor(&style_screen_music_sub_button_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_music_sub_button_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_music_sub_button_main_main_default, 255);
	lv_obj_add_style(ui->screen_music_sub_button, &style_screen_music_sub_button_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	/* Volume screen objects */

	//Write codes screen_volume_container
	ui->screen_volume_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_volume_container, 30, 167);
	lv_obj_set_size(ui->screen_volume_container, 197, 84);

	//Write style state: LV_STATE_DEFAULT for style_screen_volume_container_main_main_default
	static lv_style_t style_screen_volume_container_main_main_default;
	lv_style_reset(&style_screen_volume_container_main_main_default);
	lv_style_set_radius(&style_screen_volume_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_volume_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_volume_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_volume_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_volume_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_volume_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_volume_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_volume_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_volume_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_volume_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_volume_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_volume_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_volume_container, &style_screen_volume_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_volume_plus
	ui->screen_volume_plus = lv_img_create(ui->screen_volume_container);
	lv_obj_set_pos(ui->screen_volume_plus, 85, 5);
	lv_obj_set_size(ui->screen_volume_plus, 11, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_volume_plus_main_main_default
	static lv_style_t style_screen_volume_plus_main_main_default;
	lv_style_reset(&style_screen_volume_plus_main_main_default);
	lv_style_set_img_recolor(&style_screen_volume_plus_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_volume_plus_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_volume_plus_main_main_default, 255);
	lv_obj_add_style(ui->screen_volume_plus, &style_screen_volume_plus_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_volume_minus
	ui->screen_volume_minus = lv_img_create(ui->screen_volume_container);
	lv_obj_set_pos(ui->screen_volume_minus, 85, 75);
	lv_obj_set_size(ui->screen_volume_minus, 11, 3);

	//Write style state: LV_STATE_DEFAULT for style_screen_volume_minus_main_main_default
	static lv_style_t style_screen_volume_minus_main_main_default;
	lv_style_reset(&style_screen_volume_minus_main_main_default);
	lv_style_set_img_recolor(&style_screen_volume_minus_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_volume_minus_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_volume_minus_main_main_default, 255);
	lv_obj_add_style(ui->screen_volume_minus, &style_screen_volume_minus_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_volume_signbtn
	ui->screen_volume_signbtn = lv_img_create(ui->screen_volume_container);
	lv_obj_set_pos(ui->screen_volume_signbtn, 150, 22);
	lv_obj_set_size(ui->screen_volume_signbtn, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_volume_signbtn_main_main_default
	static lv_style_t style_screen_volume_signbtn_main_main_default;
	lv_style_reset(&style_screen_volume_signbtn_main_main_default);
	lv_style_set_img_recolor(&style_screen_volume_signbtn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_volume_signbtn_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_volume_signbtn_main_main_default, 255);
	lv_obj_add_style(ui->screen_volume_signbtn, &style_screen_volume_signbtn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_volume_base
	ui->screen_volume_base = lv_img_create(ui->screen_volume_container);
	lv_obj_set_pos(ui->screen_volume_base, 40, 40);
	lv_obj_set_size(ui->screen_volume_base, 110, 27);

	//Write style state: LV_STATE_DEFAULT for style_screen_volume_base_main_main_default
	static lv_style_t style_screen_volume_base_main_main_default;
	lv_style_reset(&style_screen_volume_base_main_main_default);
	lv_style_set_img_recolor(&style_screen_volume_base_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_volume_base_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_volume_base_main_main_default, 255);
	lv_obj_add_style(ui->screen_volume_base, &style_screen_volume_base_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_volume_label
	ui->screen_volume_label = lv_label_create(ui->screen_volume_container);
	lv_obj_set_pos(ui->screen_volume_label, 59, 16);
	lv_obj_set_size(ui->screen_volume_label, 70, 20);
	lv_label_set_text(ui->screen_volume_label, "Volume");
	lv_label_set_long_mode(ui->screen_volume_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_volume_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_volume_label_main_main_default
	static lv_style_t style_screen_volume_label_main_main_default;
	lv_style_reset(&style_screen_volume_label_main_main_default);
	lv_style_set_radius(&style_screen_volume_label_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_volume_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_volume_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_volume_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_volume_label_main_main_default, 0);
	lv_style_set_text_color(&style_screen_volume_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_volume_label_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_volume_label_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_volume_label_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_volume_label_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_volume_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_volume_label_main_main_default, 0);
	lv_obj_add_style(ui->screen_volume_label, &style_screen_volume_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


      /*PHONE SCREEN*/

      //Write codes screen_phone_container
	ui->screen_phone_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_phone_container, 30, 167);
	lv_obj_set_size(ui->screen_phone_container, 197, 84);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_container_main_main_default
	static lv_style_t style_screen_phone_container_main_main_default;
	lv_style_reset(&style_screen_phone_container_main_main_default);
	lv_style_set_radius(&style_screen_phone_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_phone_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_phone_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_phone_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_phone_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_phone_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_phone_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_phone_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_phone_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_phone_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_phone_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_phone_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_phone_container, &style_screen_phone_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


    //Write codes screen_phone_up_arrow
	ui->screen_phone_up_arrow = lv_img_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_up_arrow, 84, 4);
	lv_obj_set_size(ui->screen_phone_up_arrow, 12, 7);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_up_arrow_main_main_default
	static lv_style_t style_screen_phone_up_arrow_main_main_default;
	lv_style_reset(&style_screen_phone_up_arrow_main_main_default);
	lv_style_set_img_recolor(&style_screen_phone_up_arrow_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_phone_up_arrow_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_phone_up_arrow_main_main_default, 255);
	lv_obj_add_style(ui->screen_phone_up_arrow, &style_screen_phone_up_arrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_phone_up_arrow, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_phone_up_arrow,&_Setting_Up_Arrow_12x7);
	lv_img_set_pivot(ui->screen_phone_up_arrow, 0,0);
	lv_img_set_angle(ui->screen_phone_up_arrow, 0);


    	//Write codes screen_phone_down_arrow
	ui->screen_phone_down_arrow = lv_img_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_down_arrow, 84, 62);
	lv_obj_set_size(ui->screen_phone_down_arrow, 12, 7);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_down_arrow_main_main_default
	static lv_style_t style_screen_phone_down_arrow_main_main_default;
	lv_style_reset(&style_screen_phone_down_arrow_main_main_default);
	lv_style_set_img_recolor(&style_screen_phone_down_arrow_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_phone_down_arrow_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_phone_down_arrow_main_main_default, 255);
	lv_obj_add_style(ui->screen_phone_down_arrow, &style_screen_phone_down_arrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_phone_down_arrow, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_phone_down_arrow,&_Setting_Drow_Arrow_12x7);
	lv_img_set_pivot(ui->screen_phone_down_arrow, 0,0);
	lv_img_set_angle(ui->screen_phone_down_arrow, 0);


	 
     
	//Write codes screen_phone_lbl_1
	ui->screen_phone_lbl_1 = lv_label_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_lbl_1, 8, 7);
	lv_obj_set_size(ui->screen_phone_lbl_1, 183, 20);
	lv_label_set_text(ui->screen_phone_lbl_1, "");
	lv_label_set_long_mode(ui->screen_phone_lbl_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_phone_lbl_1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_lbl_1_main_main_default
	static lv_style_t style_screen_phone_lbl_1_main_main_default;
	lv_style_reset(&style_screen_phone_lbl_1_main_main_default);
	lv_style_set_radius(&style_screen_phone_lbl_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_phone_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_phone_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_phone_lbl_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_phone_lbl_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_phone_lbl_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_phone_lbl_1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_phone_lbl_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_phone_lbl_1, &style_screen_phone_lbl_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


    //Write codes screen_phone_lbl_2
	ui->screen_phone_lbl_2 = lv_label_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_lbl_2, 42, 20);
	lv_obj_set_size(ui->screen_phone_lbl_2, 100, 16);
	lv_label_set_text(ui->screen_phone_lbl_2, "");
	lv_label_set_long_mode(ui->screen_phone_lbl_2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_phone_lbl_2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_lbl_2_main_main_default
	static lv_style_t style_screen_phone_lbl_2_main_main_default;
	lv_style_reset(&style_screen_phone_lbl_2_main_main_default);
	lv_style_set_radius(&style_screen_phone_lbl_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_phone_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_phone_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_phone_lbl_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_phone_lbl_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_phone_lbl_2_main_main_default, lv_color_make(0x41, 0x41, 0x41));
	lv_style_set_text_font(&style_screen_phone_lbl_2_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_screen_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_phone_lbl_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_phone_lbl_2, &style_screen_phone_lbl_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    
	
	//Write codes screen_phone_btn1
	ui->screen_phone_btn1 = lv_img_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_btn1, 28, 49);
	lv_obj_set_size(ui->screen_phone_btn1, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_btn1_main_main_default
	static lv_style_t style_screen_phone_btn1_main_main_default;
	lv_style_reset(&style_screen_phone_btn1_main_main_default);
	lv_style_set_img_recolor(&style_screen_phone_btn1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_phone_btn1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_phone_btn1_main_main_default, 255);
	lv_obj_add_style(ui->screen_phone_btn1, &style_screen_phone_btn1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_phone_btn1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_phone_btn1,&_img_night_call_declined_decline_30x30);
	lv_img_set_pivot(ui->screen_phone_btn1, 0,0);
	lv_img_set_angle(ui->screen_phone_btn1, 0);


   	//Write codes screen_phone_btn2
	ui->screen_phone_btn2 = lv_img_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_btn2, 75, 49);
	lv_obj_set_size(ui->screen_phone_btn2, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_btn2_main_main_default
	static lv_style_t style_screen_phone_btn2_main_main_default;
	lv_style_reset(&style_screen_phone_btn2_main_main_default);
	lv_style_set_img_recolor(&style_screen_phone_btn2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_phone_btn2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_phone_btn2_main_main_default, 255);
	lv_obj_add_style(ui->screen_phone_btn2, &style_screen_phone_btn2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_phone_btn2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_phone_btn2,&_img_night_call_declined_decline_30x30);
	lv_img_set_pivot(ui->screen_phone_btn2, 0,0);
	lv_img_set_angle(ui->screen_phone_btn2, 0);


    //Write codes screen_phone_btn3
	ui->screen_phone_btn3 = lv_img_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_btn3, 122, 49);
	lv_obj_set_size(ui->screen_phone_btn3, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_btn3_main_main_default
	static lv_style_t style_screen_phone_btn3_main_main_default;
	lv_style_reset(&style_screen_phone_btn3_main_main_default);
	lv_style_set_img_recolor(&style_screen_phone_btn3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_phone_btn3_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_phone_btn3_main_main_default, 255);
	lv_obj_add_style(ui->screen_phone_btn3, &style_screen_phone_btn3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_phone_btn3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_phone_btn3,&call_accept_darkgreen_icon);
	lv_img_set_pivot(ui->screen_phone_btn3, 0,0);
	lv_img_set_angle(ui->screen_phone_btn3, 0);


     
	//Write codes screen_phone_call_btn
	ui->screen_phone_call_btn = lv_img_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_call_btn, 146, 19);
	lv_obj_set_size(ui->screen_phone_call_btn, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_call_btn_main_main_default
	static lv_style_t style_screen_phone_call_btn_main_main_default;
	lv_style_reset(&style_screen_phone_call_btn_main_main_default);
	lv_style_set_img_recolor(&style_screen_phone_call_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_phone_call_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_phone_call_btn_main_main_default, 255);
	lv_obj_add_style(ui->screen_phone_call_btn, &style_screen_phone_call_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_phone_call_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_phone_call_btn,&_img_night_contacts_l1_call_icon_30x30);
	lv_img_set_pivot(ui->screen_phone_call_btn, 0,0);
	lv_img_set_angle(ui->screen_phone_call_btn, 0);

	
		//Write codes screen_bl_pass_container
	ui->screen_bl_pass_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_bl_pass_container, 30, 167);
	lv_obj_set_size(ui->screen_bl_pass_container, 195, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_bl_pass_container_main_main_default
	static lv_style_t style_screen_bl_pass_container_main_main_default;
	lv_style_reset(&style_screen_bl_pass_container_main_main_default);
	lv_style_set_radius(&style_screen_bl_pass_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_bl_pass_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_bl_pass_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_bl_pass_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_bl_pass_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_bl_pass_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_bl_pass_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_bl_pass_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_bl_pass_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_bl_pass_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_bl_pass_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_bl_pass_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_bl_pass_container, &style_screen_bl_pass_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pass_label
	ui->screen_pass_label = lv_label_create(ui->screen_bl_pass_container);
	lv_obj_set_pos(ui->screen_pass_label, 46, 9);
	lv_obj_set_size(ui->screen_pass_label, 98, 18);
	lv_label_set_text(ui->screen_pass_label, "Passcode");
	lv_label_set_long_mode(ui->screen_pass_label, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_pass_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_pass_label_main_main_default
	static lv_style_t style_screen_pass_label_main_main_default;
	lv_style_reset(&style_screen_pass_label_main_main_default);
	lv_style_set_radius(&style_screen_pass_label_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_pass_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_pass_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_pass_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_pass_label_main_main_default, 0);
	lv_style_set_text_color(&style_screen_pass_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_pass_label_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_pass_label_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_pass_label_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_pass_label_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_pass_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_pass_label_main_main_default, 0);
	lv_obj_add_style(ui->screen_pass_label, &style_screen_pass_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pass_unit
	ui->screen_pass_unit = lv_label_create(ui->screen_bl_pass_container);
	lv_obj_set_pos(ui->screen_pass_unit, 68, 35);
	lv_obj_set_size(ui->screen_pass_unit, 51, 16);
	lv_label_set_text(ui->screen_pass_unit, "123456");
	lv_label_set_long_mode(ui->screen_pass_unit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_pass_unit, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_pass_unit_main_main_default
	static lv_style_t style_screen_pass_unit_main_main_default;
	lv_style_reset(&style_screen_pass_unit_main_main_default);
	lv_style_set_radius(&style_screen_pass_unit_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_pass_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_pass_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_pass_unit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_pass_unit_main_main_default, 0);
	lv_style_set_text_color(&style_screen_pass_unit_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_pass_unit_main_main_default, &lv_font_FjallaOne_Regular_16);
	lv_style_set_text_letter_space(&style_screen_pass_unit_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_pass_unit_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_pass_unit_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_pass_unit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_pass_unit_main_main_default, 0);
	lv_obj_add_style(ui->screen_pass_unit, &style_screen_pass_unit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pass_larrow
	ui->screen_pass_larrow = lv_label_create(ui->screen_bl_pass_container);
	lv_obj_set_pos(ui->screen_pass_larrow, 60, 38);
	lv_obj_set_size(ui->screen_pass_larrow, 7, 9);
	lv_label_set_text(ui->screen_pass_larrow, "<");
	lv_label_set_long_mode(ui->screen_pass_larrow, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_pass_larrow, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_pass_larrow_main_main_default
	static lv_style_t style_screen_pass_larrow_main_main_default;
	lv_style_reset(&style_screen_pass_larrow_main_main_default);
	lv_style_set_radius(&style_screen_pass_larrow_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_pass_larrow_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_pass_larrow_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_pass_larrow_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_pass_larrow_main_main_default, 0);
	lv_style_set_text_color(&style_screen_pass_larrow_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_pass_larrow_main_main_default, &lv_font_FjallaOne_Regular_10);
	lv_style_set_text_letter_space(&style_screen_pass_larrow_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_pass_larrow_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_pass_larrow_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_pass_larrow_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_pass_larrow_main_main_default, 0);
	lv_obj_add_style(ui->screen_pass_larrow, &style_screen_pass_larrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pass_rarrow
	ui->screen_pass_rarrow = lv_label_create(ui->screen_bl_pass_container);
	lv_obj_set_pos(ui->screen_pass_rarrow, 121, 38);
	lv_obj_set_size(ui->screen_pass_rarrow, 7, 9);
	lv_label_set_text(ui->screen_pass_rarrow, ">");
	lv_label_set_long_mode(ui->screen_pass_rarrow, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_pass_rarrow, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_pass_rarrow_main_main_default
	static lv_style_t style_screen_pass_rarrow_main_main_default;
	lv_style_reset(&style_screen_pass_rarrow_main_main_default);
	lv_style_set_radius(&style_screen_pass_rarrow_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_pass_rarrow_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_pass_rarrow_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_pass_rarrow_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_pass_rarrow_main_main_default, 0);
	lv_style_set_text_color(&style_screen_pass_rarrow_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_pass_rarrow_main_main_default, &lv_font_FjallaOne_Regular_10);
	lv_style_set_text_letter_space(&style_screen_pass_rarrow_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_pass_rarrow_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_pass_rarrow_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_pass_rarrow_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_pass_rarrow_main_main_default, 0);
	lv_obj_add_style(ui->screen_pass_rarrow, &style_screen_pass_rarrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Tacho_Mid_grey
	ui->screen_Tacho_Mid_grey = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Tacho_Mid_grey, 0, 7);
	lv_obj_set_size(ui->screen_Tacho_Mid_grey, 240, 306);

	//Write style state: LV_STATE_DEFAULT for style_screen_tacho_mid_grey_main_main_default
	static lv_style_t style_screen_tacho_mid_grey_main_main_default;
	lv_style_reset(&style_screen_tacho_mid_grey_main_main_default);
	lv_style_set_img_recolor(&style_screen_tacho_mid_grey_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tacho_mid_grey_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tacho_mid_grey_main_main_default, 255);
	lv_obj_add_style(ui->screen_Tacho_Mid_grey, &style_screen_tacho_mid_grey_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_Tacho_Mid_grey,&Red_night_middle_grey_circler);

}



void Intermediate_Screen_Day_obj_create (lv_ui *ui)
{
	
	ui->screen = lv_obj_create(NULL);
	
	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	lv_style_reset(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_screen_main_main_default, 255);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	ui->screen_skin = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_skin, 0, 0);
	lv_obj_set_size(ui->screen_skin, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_screen_skin_main_main_default
	static lv_style_t style_screen_skin_main_main_default;
	lv_style_reset(&style_screen_skin_main_main_default);
	lv_style_set_img_recolor(&style_screen_skin_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_skin_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_skin_main_main_default, 255);
	lv_obj_add_style(ui->screen_skin, &style_screen_skin_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_skin, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_skin,&_Skin_BG_240x320);
	lv_img_set_pivot(ui->screen_skin, 0,0);
	lv_img_set_angle(ui->screen_skin, 0);

	//Write codes screen_FogLampTT
	ui->screen_FogLampTT = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_FogLampTT, 10, 11);
	lv_obj_set_size(ui->screen_FogLampTT, 24, 21);

	//Write style state: LV_STATE_DEFAULT for style_screen_foglamptt_main_main_default
	static lv_style_t style_screen_foglamptt_main_main_default;
	lv_style_reset(&style_screen_foglamptt_main_main_default);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_foglamptt_main_main_default, 255);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_foglamptt_main_main_pressed
	static lv_style_t style_screen_foglamptt_main_main_pressed;
	lv_style_reset(&style_screen_foglamptt_main_main_pressed);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_foglamptt_main_main_checked
	static lv_style_t style_screen_foglamptt_main_main_checked;
	lv_style_reset(&style_screen_foglamptt_main_main_checked);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_checked, 0);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_FogLampTT, LV_IMGBTN_STATE_RELEASED, NULL, &_Layer_0_alpha_24x20, NULL);
	lv_imgbtn_set_src(ui->screen_FogLampTT, LV_IMGBTN_STATE_PRESSED, NULL, &new_header_fog_telltale, NULL);
	lv_obj_add_flag(ui->screen_FogLampTT, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_imgEngineTT
	ui->screen_imgEngineTT = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgEngineTT, 204, 12);
	lv_obj_set_size(ui->screen_imgEngineTT, 26, 18);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgenginett_main_main_default
	static lv_style_t style_screen_imgenginett_main_main_default;
	lv_style_reset(&style_screen_imgenginett_main_main_default);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgenginett_main_main_default, 255);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgenginett_main_main_pressed
	static lv_style_t style_screen_imgenginett_main_main_pressed;
	lv_style_reset(&style_screen_imgenginett_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgenginett_main_main_checked
	static lv_style_t style_screen_imgenginett_main_main_checked;
	lv_style_reset(&style_screen_imgenginett_main_main_checked);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgEngineTT, LV_IMGBTN_STATE_RELEASED, NULL, &new_engine_telltale, NULL);
	lv_imgbtn_set_src(ui->screen_imgEngineTT, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_25x17, NULL);
	lv_obj_add_flag(ui->screen_imgEngineTT, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_E_F_Img
	ui->screen_E_F_Img = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_E_F_Img, 38, 254);
	lv_obj_set_size(ui->screen_E_F_Img, 13, 15);

	//Write style state: LV_STATE_DEFAULT for style_screen_e_f_img_main_main_default
	static lv_style_t style_screen_e_f_img_main_main_default;
	lv_style_reset(&style_screen_e_f_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_e_f_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_e_f_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_e_f_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_E_F_Img, &style_screen_e_f_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_E_F_Img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_E_F_Img,&_img_night_fuel_E_13x15);
	lv_img_set_pivot(ui->screen_E_F_Img, 0,0);
	lv_img_set_angle(ui->screen_E_F_Img, 0);

	//Write codes screen_F_Img
	ui->screen_F_Img = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_F_Img, 190, 252);
	lv_obj_set_size(ui->screen_F_Img, 10, 16);

	//Write style state: LV_STATE_DEFAULT for style_screen_f_img_main_main_default
	static lv_style_t style_screen_f_img_main_main_default;
	lv_style_reset(&style_screen_f_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_f_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_f_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_f_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_F_Img, &style_screen_f_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_F_Img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_F_Img,&_img_night_fuel_F_10x16);
	lv_img_set_pivot(ui->screen_F_Img, 0,0);
	lv_img_set_angle(ui->screen_F_Img, 0);	

	//Write codes screen_Fuelbar0
	ui->screen_Fuelbar0 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuelbar0, 41, 266);
	lv_obj_set_size(ui->screen_Fuelbar0, 158, 43);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuelbar0_main_main_default
	static lv_style_t style_screen_fuelbar0_main_main_default;
	lv_style_reset(&style_screen_fuelbar0_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuelbar0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuelbar0_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuelbar0_main_main_default, 255);
	lv_obj_add_style(ui->screen_Fuelbar0, &style_screen_fuelbar0_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuelbar0, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuelbar0,&img_fuel_grey_bg_white_icon);
	lv_img_set_pivot(ui->screen_Fuelbar0, 0,0);
	lv_img_set_angle(ui->screen_Fuelbar0, 0);

		//Write codes screen_TachoBarBlank
	ui->screen_TachoBarBlank = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBarBlank, 3, 8);
	lv_obj_set_size(ui->screen_TachoBarBlank, 231, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobarblank_main_main_default
	static lv_style_t style_screen_tachobarblank_main_main_default;
	lv_style_reset(&style_screen_tachobarblank_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobarblank_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobarblank_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobarblank_main_main_default, 0);
	lv_obj_add_style(ui->screen_TachoBarBlank, &style_screen_tachobarblank_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBarBlank, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBarBlank,&_Layer_0_231x78);
	lv_img_set_pivot(ui->screen_TachoBarBlank, 0,0);
	lv_img_set_angle(ui->screen_TachoBarBlank, 0);

		//Write codes screen_Service_Due
	ui->screen_Service_Due = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_Service_Due, 207, 234);
	lv_obj_set_size(ui->screen_Service_Due, 25, 25);

	//Write style state: LV_STATE_DEFAULT for style_screen_service_due_main_main_default
	static lv_style_t style_screen_service_due_main_main_default;
	lv_style_reset(&style_screen_service_due_main_main_default);
	lv_style_set_text_color(&style_screen_service_due_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_default, 3);
	lv_style_set_img_opa(&style_screen_service_due_main_main_default, 255);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_move_foreground(ui->screen_Service_Due);
	

	//Write style state: LV_STATE_PRESSED for style_screen_service_due_main_main_pressed
	static lv_style_t style_screen_service_due_main_main_pressed;
	lv_style_reset(&style_screen_service_due_main_main_pressed);
	lv_style_set_text_color(&style_screen_service_due_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_service_due_main_main_checked
	static lv_style_t style_screen_service_due_main_main_checked;
	lv_style_reset(&style_screen_service_due_main_main_checked);
	lv_style_set_text_color(&style_screen_service_due_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_checked, 0);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_Service_Due, LV_IMGBTN_STATE_RELEASED, NULL, &img_Service_Remainder_25x25, NULL);
	lv_imgbtn_set_src(ui->screen_Service_Due, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_22x25, NULL);
	lv_obj_add_flag(ui->screen_Service_Due, LV_OBJ_FLAG_CHECKABLE);


	//Write codes screen_TachoBar0
	ui->screen_TachoBar0 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBar0, 7, 6);
	lv_obj_set_size(ui->screen_TachoBar0, 227, 75);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobar0_main_main_default
	static lv_style_t style_screen_tachobar0_main_main_default;
	lv_style_reset(&style_screen_tachobar0_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobar0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobar0_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobar0_main_main_default, 255);
	lv_obj_add_style(ui->screen_TachoBar0, &style_screen_tachobar0_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBar0, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBar0,&img_tacho_chaplets);
	lv_img_set_pivot(ui->screen_TachoBar0, 0,0);
	lv_img_set_angle(ui->screen_TachoBar0, 0);


	//Write codes screen_TachoBar0_1
	ui->screen_TachoBar0_1 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBar0_1, 3, 8);
	lv_obj_set_size(ui->screen_TachoBar0_1, 231, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobar0_1_main_main_default
	static lv_style_t style_screen_tachobar0_1_main_main_default;
	lv_style_reset(&style_screen_tachobar0_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobar0_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobar0_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobar0_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_TachoBar0_1, &style_screen_tachobar0_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBar0_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBar0_1,&_img_night_tacho_fill_001_231x78);
	lv_img_set_pivot(ui->screen_TachoBar0_1, 0,0);
	lv_img_set_angle(ui->screen_TachoBar0_1, 0);

	//Write codes screen_Fuel_Img_Icon
	ui->screen_Fuel_Img_Icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuel_Img_Icon, 105, 248);
	lv_obj_set_size(ui->screen_Fuel_Img_Icon, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuel_img_icon_main_main_default
	static lv_style_t style_screen_fuel_img_icon_main_main_default;
	lv_style_reset(&style_screen_fuel_img_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuel_img_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuel_img_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuel_img_icon_main_main_default, 0);
	lv_obj_add_style(ui->screen_Fuel_Img_Icon, &style_screen_fuel_img_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuel_Img_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuel_Img_Icon,&_img_night_display_units_fuel_icon_30x30);
	lv_img_set_pivot(ui->screen_Fuel_Img_Icon, 0,0);
	lv_img_set_angle(ui->screen_Fuel_Img_Icon, 0);

	//Write codes screen_imgOilTelltale
	ui->screen_imgOilTelltale = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgOilTelltale, 4, 290);
	lv_obj_set_size(ui->screen_imgOilTelltale, 34, 14);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgoiltelltale_main_main_default
	static lv_style_t style_screen_imgoiltelltale_main_main_default;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_default);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgoiltelltale_main_main_default, 254);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgoiltelltale_main_main_pressed
	static lv_style_t style_screen_imgoiltelltale_main_main_pressed;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgoiltelltale_main_main_checked
	static lv_style_t style_screen_imgoiltelltale_main_main_checked;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_checked);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgOilTelltale, LV_IMGBTN_STATE_RELEASED, NULL, &new_oil_telltale, NULL);
	lv_imgbtn_set_src(ui->screen_imgOilTelltale, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_32x13, NULL);
	lv_obj_add_flag(ui->screen_imgOilTelltale, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_Trip_blank
	ui->screen_Trip_blank = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Trip_blank, 105, 255);
	lv_obj_set_size(ui->screen_Trip_blank, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_blank_main_main_default
	static lv_style_t style_screen_trip_blank_main_main_default;
	lv_style_reset(&style_screen_trip_blank_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_blank_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_blank_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_trip_blank_main_main_default, 255);
	lv_obj_add_style(ui->screen_Trip_blank, &style_screen_trip_blank_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Trip_blank, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Trip_blank,&_BlankTrip_30x30);
	lv_img_set_pivot(ui->screen_Trip_blank, 0,0);
	lv_img_set_angle(ui->screen_Trip_blank, 0);

	//Write codes screen_Fuel_low_mMarker
	ui->screen_Fuel_low_mMarker = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuel_low_mMarker, 35, 276);
	lv_obj_set_size(ui->screen_Fuel_low_mMarker, 11, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuel_low_mmarker_main_main_default
	static lv_style_t style_screen_fuel_low_mmarker_main_main_default;
	lv_style_reset(&style_screen_fuel_low_mmarker_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuel_low_mmarker_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuel_low_mmarker_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuel_low_mmarker_main_main_default, 255);
	lv_obj_add_style(ui->screen_Fuel_low_mMarker, &style_screen_fuel_low_mmarker_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuel_low_mMarker, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuel_low_mMarker,&_img_night_fuel_low_marker_11x13);
	lv_img_set_pivot(ui->screen_Fuel_low_mMarker, 0,0);
	lv_img_set_angle(ui->screen_Fuel_low_mMarker, 0);

	// Write codes screen_day_base_container
	ui->screen_day_base_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_day_base_container, 0, 0);
	lv_obj_set_size(ui->screen_day_base_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_base_container_main_main_default
	static lv_style_t style_screen_day_base_container_main_main_default;
	lv_style_reset(&style_screen_day_base_container_main_main_default);
	lv_style_set_radius(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_base_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_day_base_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_day_base_container_main_main_default, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_day_base_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_day_base_container_main_main_default, 255);
	lv_style_set_pad_left(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_base_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_base_container, &style_screen_day_base_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_white_img
	ui->screen_white_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_white_img, 7, 47);
	lv_obj_set_size(ui->screen_white_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_screen_white_img_main_main_default
	static lv_style_t style_screen_white_img_main_main_default;
	lv_style_reset(&style_screen_white_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_white_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_white_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_white_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_white_img, &style_screen_white_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_white_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_white_img,&day_white_Grey_circle);
	//lv_img_set_src(ui->screen_white_img,&_circle_226x226);	
	lv_img_set_pivot(ui->screen_white_img, 0,0);
	lv_img_set_angle(ui->screen_white_img, 0);	

	//Write codes screen_Day_hour
	ui->screen_Day_hour = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_hour, 86, 81);
	lv_obj_set_size(ui->screen_Day_hour, 13, 12);
	lv_label_set_text(ui->screen_Day_hour, "24");
	lv_label_set_long_mode(ui->screen_Day_hour, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_hour, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_hour_main_main_default
	static lv_style_t style_screen_day_hour_main_main_default;
	lv_style_reset(&style_screen_day_hour_main_main_default);
	lv_style_set_radius(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_hour_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_hour_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_hour_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_hour_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_hour_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_hour_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_hour, &style_screen_day_hour_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_min
	ui->screen_Day_min = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_min, 113, 81);
	lv_obj_set_size(ui->screen_Day_min, 15, 12);
	lv_label_set_text(ui->screen_Day_min, "24");
	lv_label_set_long_mode(ui->screen_Day_min, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_min, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_min_main_main_default
	static lv_style_t style_screen_day_min_main_main_default;
	lv_style_reset(&style_screen_day_min_main_main_default);
	lv_style_set_radius(&style_screen_day_min_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_min_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_min_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_min_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_min_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_day_min_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_min_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_min_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_min_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_min_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_min, &style_screen_day_min_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_colon
	ui->screen_Day_colon = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_colon, 109, 85);
	lv_obj_set_size(ui->screen_Day_colon, 3, 10);
	lv_label_set_text(ui->screen_Day_colon, ":");
	lv_label_set_long_mode(ui->screen_Day_colon, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_colon, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_colon_main_main_default
	static lv_style_t style_screen_day_colon_main_main_default;
	lv_style_reset(&style_screen_day_colon_main_main_default);
	lv_style_set_radius(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_colon_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_colon_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_colon_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_colon_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_colon_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_colon_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_colon, &style_screen_day_colon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_gear
	ui->screen_day_gear = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_gear, 17, 148);
	lv_obj_set_size(ui->screen_day_gear, 10, 24);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_gear_main_main_default
	static lv_style_t style_screen_day_gear_main_main_default;
	lv_style_reset(&style_screen_day_gear_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_gear_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_gear_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_gear_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_gear, &style_screen_day_gear_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_gear, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_gear,&_White_gear_10x24);
	lv_img_set_pivot(ui->screen_day_gear, 0,0);
	lv_img_set_angle(ui->screen_day_gear, 0);

	//Write codes screen_day_gear_up
	ui->screen_day_gear_up = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_gear_up, 30, 134);
	lv_obj_set_size(ui->screen_day_gear_up, 15, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_gear_up_main_main_default
	static lv_style_t style_screen_day_gear_up_main_main_default;
	lv_style_reset(&style_screen_day_gear_up_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_gear_up_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_gear_up_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_gear_up_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_gear_up, &style_screen_day_gear_up_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_gear_up, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_gear_up,&new_day_gear_arrows_up_white);
	lv_img_set_pivot(ui->screen_day_gear_up, 0,0);
	lv_img_set_angle(ui->screen_day_gear_up, 0);

	//Write codes screen_day_gear_down
	ui->screen_day_gear_down = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_gear_down, 30, 177);
	lv_obj_set_size(ui->screen_day_gear_down, 15, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_gear_down_main_main_default
	static lv_style_t style_screen_day_gear_down_main_main_default;
	lv_style_reset(&style_screen_day_gear_down_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_gear_down_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_gear_down_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_gear_down_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_gear_down, &style_screen_day_gear_down_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_gear_down, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_gear_down,&new_day_gear_arrows_down_white);
	lv_img_set_pivot(ui->screen_day_gear_down, 0,0);
	lv_img_set_angle(ui->screen_day_gear_down, 0);

		//Write codes screen_gear_N_img_Day
	ui->screen_gear_N_img_Day = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_gear_N_img_Day, 30, 150);
	lv_obj_set_size(ui->screen_gear_N_img_Day, 15, 23);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_n_img_day_main_main_default
	static lv_style_t style_screen_gear_n_img_day_main_main_default;
	lv_style_reset(&style_screen_gear_n_img_day_main_main_default);
	lv_style_set_img_recolor(&style_screen_gear_n_img_day_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_n_img_day_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_n_img_day_main_main_default, 255);
	lv_obj_add_style(ui->screen_gear_N_img_Day, &style_screen_gear_n_img_day_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_gear_N_img_Day,&img_day_gear_neutral);

	//Write codes screen_Day_Gear_pos_Num
	ui->screen_Day_Gear_pos_Num = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_Gear_pos_Num, 31, 142);
	lv_obj_set_size(ui->screen_Day_Gear_pos_Num, 12, 28);
	lv_label_set_text(ui->screen_Day_Gear_pos_Num, "2");
	lv_label_set_long_mode(ui->screen_Day_Gear_pos_Num, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_Gear_pos_Num, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_gear_pos_num_main_main_default
	static lv_style_t style_screen_day_gear_pos_num_main_main_default;
	lv_style_reset(&style_screen_day_gear_pos_num_main_main_default);
	lv_style_set_radius(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_gear_pos_num_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_gear_pos_num_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_gear_pos_num_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_gear_pos_num_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_gear_pos_num_main_main_default, &lv_font_FjallaOne_Regular_30);
	lv_style_set_text_letter_space(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_Gear_pos_Num, &style_screen_day_gear_pos_num_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_1000_rpm
	ui->screen_Day_1000_rpm = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_1000_rpm, 94, 53);
	lv_obj_set_size(ui->screen_Day_1000_rpm, 51, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_1000_rpm_main_main_default
	static lv_style_t style_screen_day_1000_rpm_main_main_default;
	lv_style_reset(&style_screen_day_1000_rpm_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_1000_rpm_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_1000_rpm_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_1000_rpm_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_1000_rpm, &style_screen_day_1000_rpm_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_1000_rpm, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_1000_rpm,&img_day_x1000_RPM_new);
	lv_img_set_pivot(ui->screen_Day_1000_rpm, 0,0);
	lv_img_set_angle(ui->screen_Day_1000_rpm, 0);

	//Write codes screen_day_battery_img
	ui->screen_day_battery_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_battery_img, 26, 111);
	lv_obj_set_size(ui->screen_day_battery_img, 20, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_battery_img_main_main_default
	static lv_style_t style_screen_day_battery_img_main_main_default;
	lv_style_reset(&style_screen_day_battery_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_battery_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_battery_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_battery_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_battery_img, &style_screen_day_battery_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_signal_img
	ui->screen_day_signal_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_signal_img, 200, 111);
	lv_obj_set_size(ui->screen_day_signal_img, 14, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_signal_img_main_main_default
	static lv_style_t style_screen_day_signal_img_main_main_default;
	lv_style_reset(&style_screen_day_signal_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_signal_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_signal_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_signal_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_signal_img, &style_screen_day_signal_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_sub_btn
	ui->screen_day_sub_btn = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_sub_btn, 198, 147);
	lv_obj_set_size(ui->screen_day_sub_btn, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_sub_btn_main_main_default
	static lv_style_t style_screen_day_sub_btn_main_main_default;
	lv_style_reset(&style_screen_day_sub_btn_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_sub_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_sub_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_sub_btn_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_sub_btn, &style_screen_day_sub_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_sub_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_sub_btn,&subbtn_day_24x24);
	lv_img_set_pivot(ui->screen_day_sub_btn, 0,0);
	lv_img_set_angle(ui->screen_day_sub_btn, 0);

	//Write codes screen_Day_Am_pm
	ui->screen_Day_Am_pm = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_Am_pm, 118, 81);
	lv_obj_set_size(ui->screen_Day_Am_pm, 16, 12);
	lv_label_set_text(ui->screen_Day_Am_pm, "Pm");
	lv_label_set_long_mode(ui->screen_Day_Am_pm, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_Am_pm, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_am_pm_main_main_default
	static lv_style_t style_screen_day_am_pm_main_main_default;
	lv_style_reset(&style_screen_day_am_pm_main_main_default);
	lv_style_set_radius(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_am_pm_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_am_pm_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_am_pm_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_am_pm_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_am_pm_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_am_pm_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_Am_pm, &style_screen_day_am_pm_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	// Write codes screen_day_msg_img
	ui->screen_day_msg_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_msg_img, 42, 87);
	lv_obj_set_size(ui->screen_day_msg_img, 20, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_msg_img_main_main_default
	static lv_style_t style_screen_day_msg_img_main_main_default;
	lv_style_reset(&style_screen_day_msg_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_msg_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_msg_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_msg_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_msg_img, &style_screen_day_msg_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_day_msg_img,&day_msg_icon);

	//Write codes screen_day_mis_call_img
	ui->screen_day_mis_call_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_mis_call_img, 183, 87);
	lv_obj_set_size(ui->screen_day_mis_call_img, 15, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_mis_call_img_main_main_default
	static lv_style_t style_screen_day_mis_call_img_main_main_default;
	lv_style_reset(&style_screen_day_mis_call_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_mis_call_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_mis_call_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_mis_call_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_mis_call_img, &style_screen_day_mis_call_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_day_mis_call_img,&day_mis_call_icon);

	/* Speedometer objects */

	//Write codes screen_dat_inter_con
	ui->screen_dat_inter_con = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_dat_inter_con, 57, 97);
	lv_obj_set_size(ui->screen_dat_inter_con, 160, 67);

	//Write style state: LV_STATE_DEFAULT for style_screen_dat_inter_con_main_main_default
	static lv_style_t style_screen_dat_inter_con_main_main_default;
	lv_style_reset(&style_screen_dat_inter_con_main_main_default);
	lv_style_set_radius(&style_screen_dat_inter_con_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_dat_inter_con_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_dat_inter_con_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_dat_inter_con_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_dat_inter_con_main_main_default, 0);
	lv_style_set_border_color(&style_screen_dat_inter_con_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_dat_inter_con_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_dat_inter_con_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_dat_inter_con_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_dat_inter_con_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_dat_inter_con_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_dat_inter_con_main_main_default, 0);
	lv_obj_add_style(ui->screen_dat_inter_con, &style_screen_dat_inter_con_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_km_unit_Img
	ui->screen_day_km_unit_Img = lv_img_create(ui->screen_dat_inter_con);
	lv_obj_set_pos(ui->screen_day_km_unit_Img, 108, 33);
	lv_obj_set_size(ui->screen_day_km_unit_Img, 27, 16);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_km_unit_img_main_main_default
	static lv_style_t style_screen_day_km_unit_img_main_main_default;
	lv_style_reset(&style_screen_day_km_unit_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_km_unit_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_km_unit_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_km_unit_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_km_unit_Img, &style_screen_day_km_unit_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_day_km_unit_Img,&km_text_unit_day_Img);

	//Write codes screen_day_line_img
	ui->screen_day_line_img = lv_img_create(ui->screen_dat_inter_con);
	lv_obj_set_pos(ui->screen_day_line_img, 0, 63);
	lv_obj_set_size(ui->screen_day_line_img, 134, 2);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_line_img_main_main_default
	static lv_style_t style_screen_day_line_img_main_main_default;
	lv_style_reset(&style_screen_day_line_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_line_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_line_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_line_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_line_img, &style_screen_day_line_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_line_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_line_img,&img_day_center_divider_line_gray);
	lv_img_set_pivot(ui->screen_day_line_img, 0,0);
	lv_img_set_angle(ui->screen_day_line_img, 0);

	//Write codes screen_day_in_sc1
	ui->screen_day_in_sc1 = lv_img_create(ui->screen_dat_inter_con);
	lv_obj_set_pos(ui->screen_day_in_sc1, 76, 2);
	lv_obj_set_size(ui->screen_day_in_sc1, 27, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_sc1_main_main_default
	static lv_style_t style_screen_day_in_sc1_main_main_default;
	lv_style_reset(&style_screen_day_in_sc1_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_in_sc1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_in_sc1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_in_sc1_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_in_sc1, &style_screen_day_in_sc1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_in_sc1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_in_sc1,&black0_24x47);
	lv_img_set_pivot(ui->screen_day_in_sc1, 0,0);
	lv_img_set_angle(ui->screen_day_in_sc1, 0);
	lv_obj_set_style_img_opa(ui->screen_day_in_sc1, 255, 0);
	lv_obj_set_style_img_recolor(ui->screen_day_in_sc1, lv_color_black(), 0);

	//Write codes screen_day_in_sc2
	ui->screen_day_in_sc2 = lv_img_create(ui->screen_dat_inter_con);
	lv_obj_set_pos(ui->screen_day_in_sc2, 46, 2);
	lv_obj_set_size(ui->screen_day_in_sc2, 27, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_sc2_main_main_default
	static lv_style_t style_screen_day_in_sc2_main_main_default;
	lv_style_reset(&style_screen_day_in_sc2_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_in_sc2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_in_sc2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_in_sc2_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_in_sc2, &style_screen_day_in_sc2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_in_sc2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_in_sc2,&black0_24x47);
	lv_img_set_pivot(ui->screen_day_in_sc2, 0,0);
	lv_img_set_angle(ui->screen_day_in_sc2, 0);
	lv_obj_set_style_img_opa(ui->screen_day_in_sc2, 255, 0);
	lv_obj_set_style_img_recolor(ui->screen_day_in_sc2, lv_color_Day_Grey(), 0);
	set_obj_opa(ui->screen_day_in_sc2, 50);

	//Write codes screen_day_in_sc3
	ui->screen_day_in_sc3 = lv_img_create(ui->screen_dat_inter_con);
	lv_obj_set_pos(ui->screen_day_in_sc3, 17, 2);
	lv_obj_set_size(ui->screen_day_in_sc3, 27, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_sc3_main_main_default
	static lv_style_t style_screen_day_in_sc3_main_main_default;
	lv_style_reset(&style_screen_day_in_sc3_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_in_sc3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_in_sc3_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_in_sc3_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_in_sc3, &style_screen_day_in_sc3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_in_sc3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_in_sc3,&black0_24x47);
	lv_img_set_pivot(ui->screen_day_in_sc3, 0,0);
	lv_img_set_angle(ui->screen_day_in_sc3, 0);
	lv_obj_set_style_img_opa(ui->screen_day_in_sc3, 255, 0);
	lv_obj_set_style_img_recolor(ui->screen_day_in_sc3, lv_color_Day_Grey(), 0);
	set_obj_opa(ui->screen_day_in_sc3, 50);

	/* Trip container */
		
	//Write codes screen_day_trip_con
	ui->screen_day_trip_con = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_day_trip_con, 30, 167);
	lv_obj_set_size(ui->screen_day_trip_con, 195, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_trip_con_main_main_default
	static lv_style_t style_screen_day_trip_con_main_main_default;
	lv_style_reset(&style_screen_day_trip_con_main_main_default);
	lv_style_set_radius(&style_screen_day_trip_con_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_trip_con_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_day_trip_con_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_day_trip_con_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_trip_con_main_main_default, 0);
	lv_style_set_border_color(&style_screen_day_trip_con_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_day_trip_con_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_day_trip_con_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_trip_con_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_trip_con_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_trip_con_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_trip_con_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_trip_con, &style_screen_day_trip_con_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_Trip_up_arr
	ui->screen_day_Trip_up_arr = lv_img_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_Trip_up_arr, 82, 0);
	lv_obj_set_size(ui->screen_day_Trip_up_arr, 14, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_trip_up_arr_main_main_default
	static lv_style_t style_screen_day_trip_up_arr_main_main_default;
	lv_style_reset(&style_screen_day_trip_up_arr_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_trip_up_arr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_trip_up_arr_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_trip_up_arr_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_Trip_up_arr, &style_screen_day_trip_up_arr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_day_Trip_up_arr,&new_day_trip_up_arrow_normal);

	//Write codes screen_day_Trip_down_arr
	ui->screen_day_Trip_down_arr = lv_img_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_Trip_down_arr, 82, 68);
	lv_obj_set_size(ui->screen_day_Trip_down_arr, 14, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_trip_down_arr_main_main_default
	static lv_style_t style_screen_day_trip_down_arr_main_main_default;
	lv_style_reset(&style_screen_day_trip_down_arr_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_trip_down_arr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_trip_down_arr_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_trip_down_arr_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_Trip_down_arr, &style_screen_day_trip_down_arr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_day_Trip_down_arr,&new_day_trip_down_arrow_normal);

	//Write codes screen_day_lbl1
	ui->screen_day_lbl1 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl1, 37, 15);
	lv_obj_set_size(ui->screen_day_lbl1, 26, 21);
	lv_label_set_text(ui->screen_day_lbl1, "Trip");
	lv_label_set_long_mode(ui->screen_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl1_main_main_default
	static lv_style_t style_screen_day_lbl1_main_main_default;
	lv_style_reset(&style_screen_day_lbl1_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl1_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl1, &style_screen_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl2
	ui->screen_day_lbl2 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl2, 71, 14);
	lv_obj_set_size(ui->screen_day_lbl2, 49, 18);
	lv_label_set_text(ui->screen_day_lbl2, "999.9");
	lv_label_set_long_mode(ui->screen_day_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl2, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl2_main_main_default
	static lv_style_t style_screen_day_lbl2_main_main_default;
	lv_style_reset(&style_screen_day_lbl2_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl2, &style_screen_day_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl3
	ui->screen_day_lbl3 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl3, 124, 16);
	lv_obj_set_size(ui->screen_day_lbl3, 56, 19);
	lv_label_set_text(ui->screen_day_lbl3, "L/100km");
	lv_label_set_long_mode(ui->screen_day_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl3_main_main_default
	static lv_style_t style_screen_day_lbl3_main_main_default;
	lv_style_reset(&style_screen_day_lbl3_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl3_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_screen_day_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl3, &style_screen_day_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl4
	ui->screen_day_lbl4 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl4, 34, 43);
	lv_obj_set_size(ui->screen_day_lbl4, 33, 21);
	lv_label_set_text(ui->screen_day_lbl4, "Time");
	lv_label_set_long_mode(ui->screen_day_lbl4, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl4, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl4_main_main_default
	static lv_style_t style_screen_day_lbl4_main_main_default;
	lv_style_reset(&style_screen_day_lbl4_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl4_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl4_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl4_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl4_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl4_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_lbl4_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl4_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl4_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl4_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl4_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl4, &style_screen_day_lbl4_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl5
	ui->screen_day_lbl5 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl5, 71, 42);
	lv_obj_set_size(ui->screen_day_lbl5, 21, 18);
	lv_label_set_text(ui->screen_day_lbl5, "99");
	lv_label_set_long_mode(ui->screen_day_lbl5, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl5, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl5_main_main_default
	static lv_style_t style_screen_day_lbl5_main_main_default;
	lv_style_reset(&style_screen_day_lbl5_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl5_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl5_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl5_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl5_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl5_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl5_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl5_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_lbl5_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl5_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl5_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl5_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl5_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl5, &style_screen_day_lbl5_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl_6
	ui->screen_day_lbl_6 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl_6, 98, 44);
	lv_obj_set_size(ui->screen_day_lbl_6, 11, 12);
	lv_label_set_text(ui->screen_day_lbl_6, "h");
	lv_label_set_long_mode(ui->screen_day_lbl_6, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl_6, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl_6_main_main_default
	static lv_style_t style_screen_day_lbl_6_main_main_default;
	lv_style_reset(&style_screen_day_lbl_6_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl_6_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl_6_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl_6_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl_6_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl_6_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl_6_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl_6_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_lbl_6_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl_6_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl_6_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl_6_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl_6_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl_6, &style_screen_day_lbl_6_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl_7
	ui->screen_day_lbl_7 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl_7, 109, 42);
	lv_obj_set_size(ui->screen_day_lbl_7, 21, 18);
	lv_label_set_text(ui->screen_day_lbl_7, "99");
	lv_label_set_long_mode(ui->screen_day_lbl_7, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl_7, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl_7_main_main_default
	static lv_style_t style_screen_day_lbl_7_main_main_default;
	lv_style_reset(&style_screen_day_lbl_7_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl_7_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl_7_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl_7_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl_7_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl_7_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl_7_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl_7_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_lbl_7_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl_7_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl_7_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl_7_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl_7_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl_7, &style_screen_day_lbl_7_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl_8
	ui->screen_day_lbl_8 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl_8, 135, 44);
	lv_obj_set_size(ui->screen_day_lbl_8, 12, 12);
	lv_label_set_text(ui->screen_day_lbl_8, "m");
	lv_label_set_long_mode(ui->screen_day_lbl_8, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl_8, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl_8_main_main_default
	static lv_style_t style_screen_day_lbl_8_main_main_default;
	lv_style_reset(&style_screen_day_lbl_8_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl_8_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl_8_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl_8_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl_8_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl_8_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl_8_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl_8_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_lbl_8_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl_8_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl_8_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl_8_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl_8_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl_8, &style_screen_day_lbl_8_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	/* container used for Trip Avf Avs screen , Fuel , service remainder*/
	//Write codes screen_day_inter_con2
	ui->screen_day_inter_con2 = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_day_inter_con2, 30, 167);
	lv_obj_set_size(ui->screen_day_inter_con2, 210, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_inter_con2_main_main_default
	static lv_style_t style_screen_day_inter_con2_main_main_default;
	lv_style_reset(&style_screen_day_inter_con2_main_main_default);
	lv_style_set_radius(&style_screen_day_inter_con2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_inter_con2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_day_inter_con2_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_day_inter_con2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_inter_con2_main_main_default, 0);
	lv_style_set_border_color(&style_screen_day_inter_con2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_day_inter_con2_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_day_inter_con2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_inter_con2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_inter_con2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_inter_con2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_inter_con2_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_inter_con2, &style_screen_day_inter_con2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_lb1
	ui->screen_day_in_lb1 = lv_label_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_lb1, 0, 21);
	lv_obj_set_size(ui->screen_day_in_lb1, 79, 17);
	lv_label_set_text(ui->screen_day_in_lb1, "Av Speed");
	lv_label_set_long_mode(ui->screen_day_in_lb1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_in_lb1, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_lb1_main_main_default
	static lv_style_t style_screen_day_in_lb1_main_main_default;
	lv_style_reset(&style_screen_day_in_lb1_main_main_default);
	lv_style_set_radius(&style_screen_day_in_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_in_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_in_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_in_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_in_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_in_lb1_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_day_in_lb1_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_in_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_in_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_in_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_in_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_in_lb1_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_lb1, &style_screen_day_in_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_lb2
	ui->screen_day_in_lb2 = lv_label_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_lb2, 81, 18);
	lv_obj_set_size(ui->screen_day_in_lb2, 48, 18);
	lv_label_set_text(ui->screen_day_in_lb2, "123.9");
	lv_label_set_long_mode(ui->screen_day_in_lb2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_in_lb2, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_lb2_main_main_default
	static lv_style_t style_screen_day_in_lb2_main_main_default;
	lv_style_reset(&style_screen_day_in_lb2_main_main_default);
	lv_style_set_radius(&style_screen_day_in_lb2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_in_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_in_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_in_lb2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_in_lb2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_in_lb2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_in_lb2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_in_lb2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_in_lb2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_in_lb2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_in_lb2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_in_lb2_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_lb2, &style_screen_day_in_lb2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_lb3
	ui->screen_day_in_lb3 = lv_label_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_lb3, 131, 21);
	lv_obj_set_size(ui->screen_day_in_lb3, 56, 19);
	lv_label_set_text(ui->screen_day_in_lb3, "L/100km");
	lv_label_set_long_mode(ui->screen_day_in_lb3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_in_lb3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_lb3_main_main_default
	static lv_style_t style_screen_day_in_lb3_main_main_default;
	lv_style_reset(&style_screen_day_in_lb3_main_main_default);
	lv_style_set_radius(&style_screen_day_in_lb3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_in_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_in_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_in_lb3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_in_lb3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_in_lb3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_in_lb3_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_screen_day_in_lb3_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_in_lb3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_in_lb3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_in_lb3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_in_lb3_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_lb3, &style_screen_day_in_lb3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_lb4
	ui->screen_day_in_lb4 = lv_label_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_lb4, 0, 47);
	lv_obj_set_size(ui->screen_day_in_lb4, 79, 17);
	lv_label_set_text(ui->screen_day_in_lb4, "Service Due");
	lv_label_set_long_mode(ui->screen_day_in_lb4, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_in_lb4, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_lb4_main_main_default
	static lv_style_t style_screen_day_in_lb4_main_main_default;
	lv_style_reset(&style_screen_day_in_lb4_main_main_default);
	lv_style_set_radius(&style_screen_day_in_lb4_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_in_lb4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_in_lb4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_in_lb4_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_in_lb4_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_in_lb4_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_day_in_lb4_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_in_lb4_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_in_lb4_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_in_lb4_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_in_lb4_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_in_lb4_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_lb4, &style_screen_day_in_lb4_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_lb5
	ui->screen_day_in_lb5 = lv_label_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_lb5, 81, 45);
	lv_obj_set_size(ui->screen_day_in_lb5, 104, 18);
	lv_label_set_text(ui->screen_day_in_lb5, "00 h 00m");
	lv_label_set_long_mode(ui->screen_day_in_lb5, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_in_lb5, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_lb5_main_main_default
	static lv_style_t style_screen_day_in_lb5_main_main_default;
	lv_style_reset(&style_screen_day_in_lb5_main_main_default);
	lv_style_set_radius(&style_screen_day_in_lb5_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_in_lb5_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_in_lb5_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_in_lb5_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_in_lb5_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_in_lb5_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_in_lb5_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_in_lb5_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_in_lb5_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_in_lb5_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_in_lb5_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_in_lb5_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_lb5, &style_screen_day_in_lb5_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_lb6
	ui->screen_day_in_lb6 = lv_label_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_lb6, 131, 46);
	lv_obj_set_size(ui->screen_day_in_lb6, 56, 19);
	lv_label_set_text(ui->screen_day_in_lb6, "L/100km");
	lv_label_set_long_mode(ui->screen_day_in_lb6, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_in_lb6, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_lb6_main_main_default
	static lv_style_t style_screen_day_in_lb6_main_main_default;
	lv_style_reset(&style_screen_day_in_lb6_main_main_default);
	lv_style_set_radius(&style_screen_day_in_lb6_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_in_lb6_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_in_lb6_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_in_lb6_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_in_lb6_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_in_lb6_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_in_lb6_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_screen_day_in_lb6_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_in_lb6_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_in_lb6_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_in_lb6_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_in_lb6_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_lb6, &style_screen_day_in_lb6_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_arr1
	ui->screen_day_in_arr1 = lv_img_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_arr1, 82, 0);
	lv_obj_set_size(ui->screen_day_in_arr1, 14, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_arr1_main_main_default
	static lv_style_t style_screen_day_in_arr1_main_main_default;
	lv_style_reset(&style_screen_day_in_arr1_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_in_arr1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_in_arr1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_in_arr1_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_in_arr1, &style_screen_day_in_arr1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_in_arr1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_in_arr1,&new_day_trip_up_arrow_normal);
	lv_img_set_pivot(ui->screen_day_in_arr1, 0,0);
	lv_img_set_angle(ui->screen_day_in_arr1, 0);

	//Write codes screen_day_in_arr2
	ui->screen_day_in_arr2 = lv_img_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_arr2, 82, 68);
	lv_obj_set_size(ui->screen_day_in_arr2, 14, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_arr2_main_main_default
	static lv_style_t style_screen_day_in_arr2_main_main_default;
	lv_style_reset(&style_screen_day_in_arr2_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_in_arr2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_in_arr2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_in_arr2_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_in_arr2, &style_screen_day_in_arr2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_in_arr2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_in_arr2,&new_day_trip_down_arrow_normal);
	lv_img_set_pivot(ui->screen_day_in_arr2, 0,0);
	lv_img_set_angle(ui->screen_day_in_arr2, 0);

	//Write codes screen_day_in_lb8
	ui->screen_day_in_lb8 = lv_img_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_lb8, 82, 70);
	lv_obj_set_size(ui->screen_day_in_lb8, 12, 7);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_lb8_main_main_default
	static lv_style_t style_screen_day_in_lb8_main_main_default;
	lv_style_reset(&style_screen_day_in_lb8_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_in_lb8_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_in_lb8_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_in_lb8_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_lb8, &style_screen_day_in_lb8_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_in_lb8, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_in_lb8,&new_day_trip_down_arrow_normal);
	lv_img_set_pivot(ui->screen_day_in_lb8, 0,0);
	lv_img_set_angle(ui->screen_day_in_lb8, 0);

	/* Navigation day objects */

	//Write codes screen_Main_day_Navigation
	ui->screen_Main_day_Navigation = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_Main_day_Navigation, 30, 167);
	lv_obj_set_size(ui->screen_Main_day_Navigation, 195, 95);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_day_navigation_main_main_default
	static lv_style_t style_screen_main_day_navigation_main_main_default;
	lv_style_reset(&style_screen_main_day_navigation_main_main_default);
	lv_style_set_radius(&style_screen_main_day_navigation_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_day_navigation_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_main_day_navigation_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_main_day_navigation_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_main_day_navigation_main_main_default, 0);
	lv_style_set_border_color(&style_screen_main_day_navigation_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_main_day_navigation_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_day_navigation_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_day_navigation_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_day_navigation_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_day_navigation_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_day_navigation_main_main_default, 0);
	lv_obj_add_style(ui->screen_Main_day_Navigation, &style_screen_main_day_navigation_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

		//Write codes screen_No_Sig_Day
	ui->screen_No_Sig_Day = lv_img_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_No_Sig_Day, 67, 54);
	lv_obj_set_size(ui->screen_No_Sig_Day, 46, 16);

	//Write style state: LV_STATE_DEFAULT for style_screen_no_sig_day_main_main_default
	static lv_style_t style_screen_no_sig_day_main_main_default;
	lv_style_reset(&style_screen_no_sig_day_main_main_default);
	lv_style_set_img_recolor(&style_screen_no_sig_day_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_no_sig_day_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_no_sig_day_main_main_default, 255);
	lv_obj_add_style(ui->screen_No_Sig_Day, &style_screen_no_sig_day_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_navi_lbl
	ui->screen_Day_navi_lbl = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_navi_lbl, 5, 6);
	lv_obj_set_size(ui->screen_Day_navi_lbl, 100, 15);
	lv_label_set_text(ui->screen_Day_navi_lbl, "");
	lv_label_set_long_mode(ui->screen_Day_navi_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_navi_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_navi_lbl_main_main_default
	static lv_style_t style_screen_day_navi_lbl_main_main_default;
	lv_style_reset(&style_screen_day_navi_lbl_main_main_default);
	lv_style_set_radius(&style_screen_day_navi_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_navi_lbl_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_day_navi_lbl_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_day_navi_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_navi_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_navi_lbl_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_navi_lbl_main_main_default, &lv_font_FjallaOne_Regular_15);
	lv_style_set_text_letter_space(&style_screen_day_navi_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_navi_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_navi_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_navi_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_navi_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_navi_lbl, &style_screen_day_navi_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_navi_val
	ui->screen_Day_navi_val = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_navi_val, 20, 8);
	lv_obj_set_size(ui->screen_Day_navi_val, 30, 17);
	lv_label_set_text(ui->screen_Day_navi_val, "9999");
	lv_label_set_long_mode(ui->screen_Day_navi_val, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_navi_val, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_navi_val_main_main_default
	static lv_style_t style_screen_day_navi_val_main_main_default;
	lv_style_reset(&style_screen_day_navi_val_main_main_default);
	lv_style_set_radius(&style_screen_day_navi_val_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_navi_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_navi_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_navi_val_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_navi_val_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_navi_val_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_day_navi_val_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_navi_val_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_navi_val_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_navi_val_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_navi_val_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_navi_val_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_navi_val, &style_screen_day_navi_val_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_navi_unit
	ui->screen_Day_navi_unit = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_navi_unit, 24, 35);
	lv_obj_set_size(ui->screen_Day_navi_unit, 26, 11);
	lv_label_set_text(ui->screen_Day_navi_unit, "km");
	lv_label_set_long_mode(ui->screen_Day_navi_unit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_navi_unit, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_navi_unit_main_main_default
	static lv_style_t style_screen_day_navi_unit_main_main_default;
	lv_style_reset(&style_screen_day_navi_unit_main_main_default);
	lv_style_set_radius(&style_screen_day_navi_unit_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_navi_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_navi_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_navi_unit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_navi_unit_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_navi_unit_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_day_navi_unit_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_screen_day_navi_unit_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_navi_unit_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_navi_unit_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_navi_unit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_navi_unit_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_navi_unit, &style_screen_day_navi_unit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_nav_est
	ui->screen_Day_nav_est = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_nav_est, 143, 35);
	lv_obj_set_size(ui->screen_Day_nav_est, 26, 14);
	lv_label_set_text(ui->screen_Day_nav_est, "ETA");
	lv_label_set_long_mode(ui->screen_Day_nav_est, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_nav_est, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_nav_est_main_main_default
	static lv_style_t style_screen_day_nav_est_main_main_default;
	lv_style_reset(&style_screen_day_nav_est_main_main_default);
	lv_style_set_radius(&style_screen_day_nav_est_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_nav_est_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_nav_est_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_nav_est_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_nav_est_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_nav_est_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_day_nav_est_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_nav_est_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_nav_est_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_nav_est_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_nav_est_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_nav_est_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_nav_est, &style_screen_day_nav_est_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_nav_clo_hr
	ui->screen_Day_nav_clo_hr = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_nav_clo_hr, 130, 8);
	lv_obj_set_size(ui->screen_Day_nav_clo_hr, 18, 15);
	lv_label_set_text(ui->screen_Day_nav_clo_hr, "99");
	lv_label_set_long_mode(ui->screen_Day_nav_clo_hr, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_nav_clo_hr, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_nav_clo_hr_main_main_default
	static lv_style_t style_screen_day_nav_clo_hr_main_main_default;
	lv_style_reset(&style_screen_day_nav_clo_hr_main_main_default);
	lv_style_set_radius(&style_screen_day_nav_clo_hr_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_nav_clo_hr_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_nav_clo_hr_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_nav_clo_hr_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_nav_clo_hr_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_nav_clo_hr_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_nav_clo_hr_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_nav_clo_hr_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_nav_clo_hr, &style_screen_day_nav_clo_hr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_nav_clo_colon
	ui->screen_Day_nav_clo_colon = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_nav_clo_colon, 148, 8);
	lv_obj_set_size(ui->screen_Day_nav_clo_colon, 4, 13);
	lv_label_set_text(ui->screen_Day_nav_clo_colon, ":");
	lv_label_set_long_mode(ui->screen_Day_nav_clo_colon, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_nav_clo_colon, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_nav_clo_colon_main_main_default
	static lv_style_t style_screen_day_nav_clo_colon_main_main_default;
	lv_style_reset(&style_screen_day_nav_clo_colon_main_main_default);
	lv_style_set_radius(&style_screen_day_nav_clo_colon_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_nav_clo_colon_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_nav_clo_colon_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_nav_clo_colon_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_nav_clo_colon_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_nav_clo_colon_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_nav_clo_colon_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_nav_clo_colon_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_nav_clo_colon, &style_screen_day_nav_clo_colon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_nav_clo_min
	ui->screen_Day_nav_clo_min = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_nav_clo_min, 153, 8);
	lv_obj_set_size(ui->screen_Day_nav_clo_min, 17, 15);
	lv_label_set_text(ui->screen_Day_nav_clo_min, "99");
	lv_label_set_long_mode(ui->screen_Day_nav_clo_min, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_nav_clo_min, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_nav_clo_min_main_main_default
	static lv_style_t style_screen_day_nav_clo_min_main_main_default;
	lv_style_reset(&style_screen_day_nav_clo_min_main_main_default);
	lv_style_set_radius(&style_screen_day_nav_clo_min_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_nav_clo_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_nav_clo_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_nav_clo_min_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_nav_clo_min_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_nav_clo_min_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_nav_clo_min_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_nav_clo_min_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_nav_clo_min, &style_screen_day_nav_clo_min_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_nav_clo_am
	ui->screen_Day_nav_clo_am = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_nav_clo_am, 174, 8);
	lv_obj_set_size(ui->screen_Day_nav_clo_am, 19, 15);
	lv_label_set_text(ui->screen_Day_nav_clo_am, "AM");
	lv_label_set_long_mode(ui->screen_Day_nav_clo_am, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_nav_clo_am, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_nav_clo_am_main_main_default
	static lv_style_t style_screen_day_nav_clo_am_main_main_default;
	lv_style_reset(&style_screen_day_nav_clo_am_main_main_default);
	lv_style_set_radius(&style_screen_day_nav_clo_am_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_nav_clo_am_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_nav_clo_am_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_nav_clo_am_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_nav_clo_am_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_nav_clo_am_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_day_nav_clo_am_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_nav_clo_am_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_nav_clo_am, &style_screen_day_nav_clo_am_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_nav_img
	ui->screen_Day_nav_img = lv_img_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_nav_img, 55, 5);
	lv_obj_set_size(ui->screen_Day_nav_img, 70, 70);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_nav_img_main_main_default
	static lv_style_t style_screen_day_nav_img_main_main_default;
	lv_style_reset(&style_screen_day_nav_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_nav_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_nav_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_nav_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_nav_img, &style_screen_day_nav_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	/* Day Music screen objects */

	//Write codes screen_Main_day_music_container
	ui->screen_Main_day_music_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_Main_day_music_container, 30, 167);
	lv_obj_set_size(ui->screen_Main_day_music_container, 195, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_day_music_container_main_main_default
	static lv_style_t style_screen_main_day_music_container_main_main_default;
	lv_style_reset(&style_screen_main_day_music_container_main_main_default);
	lv_style_set_radius(&style_screen_main_day_music_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_day_music_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_main_day_music_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_main_day_music_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_main_day_music_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_main_day_music_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_main_day_music_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_day_music_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_day_music_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_day_music_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_day_music_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_day_music_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_Main_day_music_container, &style_screen_main_day_music_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_music_slider_whitebase_img
	ui->screen_Day_music_slider_whitebase_img = lv_img_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_slider_whitebase_img, 25, 62);
	lv_obj_set_size(ui->screen_Day_music_slider_whitebase_img, 130, 2);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_slider_whitebase_img_main_main_default
	static lv_style_t style_screen_day_music_slider_whitebase_img_main_main_default;
	lv_style_reset(&style_screen_day_music_slider_whitebase_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_music_slider_whitebase_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_music_slider_whitebase_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_music_slider_whitebase_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_music_slider_whitebase_img, &style_screen_day_music_slider_whitebase_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_music_slider_whitebase_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_music_slider_whitebase_img,&black_line_music_day_img);
	lv_img_set_pivot(ui->screen_Day_music_slider_whitebase_img, 0,0);
	lv_img_set_angle(ui->screen_Day_music_slider_whitebase_img, 0);

	//Write codes screen_Day_music_slider_orange_img
	ui->screen_Day_music_slider_orange_img = lv_img_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_slider_orange_img, 25, 62);
	lv_obj_set_size(ui->screen_Day_music_slider_orange_img, 40, 2);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_slider_orange_img_main_main_default
	static lv_style_t style_screen_day_music_slider_orange_img_main_main_default;
	lv_style_reset(&style_screen_day_music_slider_orange_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_music_slider_orange_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_music_slider_orange_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_music_slider_orange_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_music_slider_orange_img, &style_screen_day_music_slider_orange_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_music_slider_orange_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_music_slider_orange_img,&orangeline_music_day_img);
	lv_img_set_pivot(ui->screen_Day_music_slider_orange_img, 0,0);
	lv_img_set_angle(ui->screen_Day_music_slider_orange_img, 0);

	//Write codes screen_Day_music_slide_dot
	ui->screen_Day_music_slide_dot = lv_img_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_slide_dot, 81, 56);
	lv_obj_set_size(ui->screen_Day_music_slide_dot, 14, 14);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_slide_dot_main_main_default
	static lv_style_t style_screen_day_music_slide_dot_main_main_default;
	lv_style_reset(&style_screen_day_music_slide_dot_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_music_slide_dot_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_music_slide_dot_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_music_slide_dot_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_music_slide_dot, &style_screen_day_music_slide_dot_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_music_slide_dot, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_music_slide_dot,&blackdot_music_day_img);
	lv_img_set_pivot(ui->screen_Day_music_slide_dot, 0,0);
	lv_img_set_angle(ui->screen_Day_music_slide_dot, 0);

	//Write codes screen_Day_music_lbl_1
	ui->screen_Day_music_lbl_1 = lv_label_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_lbl_1, 15, 9);
	lv_obj_set_size(ui->screen_Day_music_lbl_1, 153, 20);
	lv_label_set_text(ui->screen_Day_music_lbl_1, "XX XXXXXX");
	lv_label_set_long_mode(ui->screen_Day_music_lbl_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_music_lbl_1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_lbl_1_main_main_default
	static lv_style_t style_screen_day_music_lbl_1_main_main_default;
	lv_style_reset(&style_screen_day_music_lbl_1_main_main_default);
	lv_style_set_radius(&style_screen_day_music_lbl_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_music_lbl_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_day_music_lbl_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_day_music_lbl_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_music_lbl_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_music_lbl_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_music_lbl_1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_music_lbl_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_music_lbl_1, &style_screen_day_music_lbl_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_music_lbl_2
	ui->screen_Day_music_lbl_2 = lv_label_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_lbl_2, 21, 29);
	lv_obj_set_size(ui->screen_Day_music_lbl_2, 153, 15);
	lv_label_set_text(ui->screen_Day_music_lbl_2, "XX XXXXXX");
	lv_label_set_long_mode(ui->screen_Day_music_lbl_2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_music_lbl_2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_lbl_2_main_main_default
	static lv_style_t style_screen_day_music_lbl_2_main_main_default;
	lv_style_reset(&style_screen_day_music_lbl_2_main_main_default);
	lv_style_set_radius(&style_screen_day_music_lbl_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_music_lbl_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_day_music_lbl_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_day_music_lbl_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_music_lbl_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_music_lbl_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_music_lbl_2_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_music_lbl_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_music_lbl_2, &style_screen_day_music_lbl_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_music_lbl_3
	ui->screen_Day_music_lbl_3 = lv_label_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_lbl_3, 15, 34);
	lv_obj_set_size(ui->screen_Day_music_lbl_3, 153, 15);
	lv_label_set_text(ui->screen_Day_music_lbl_3, "XX XXXXXX");
	lv_label_set_long_mode(ui->screen_Day_music_lbl_3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_music_lbl_3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_lbl_3_main_main_default
	static lv_style_t style_screen_day_music_lbl_3_main_main_default;
	lv_style_reset(&style_screen_day_music_lbl_3_main_main_default);
	lv_style_set_radius(&style_screen_day_music_lbl_3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_music_lbl_3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_day_music_lbl_3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_day_music_lbl_3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_music_lbl_3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_music_lbl_3_main_main_default, lv_color_make(0xB8, 0xB8, 0xB8));
	lv_style_set_text_font(&style_screen_day_music_lbl_3_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_music_lbl_3_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_music_lbl_3, &style_screen_day_music_lbl_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_music_up_img
	ui->screen_Day_music_up_img = lv_img_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_up_img, 85, 6);
	lv_obj_set_size(ui->screen_Day_music_up_img, 10, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_up_img_main_main_default
	static lv_style_t style_screen_day_music_up_img_main_main_default;
	lv_style_reset(&style_screen_day_music_up_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_music_up_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_music_up_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_music_up_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_music_up_img, &style_screen_day_music_up_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_music_down_img
	ui->screen_Day_music_down_img = lv_img_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_down_img, 85, 61);
	lv_obj_set_size(ui->screen_Day_music_down_img, 9, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_down_img_main_main_default
	static lv_style_t style_screen_day_music_down_img_main_main_default;
	lv_style_reset(&style_screen_day_music_down_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_music_down_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_music_down_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_music_down_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_music_down_img, &style_screen_day_music_down_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_music_sub_button
	ui->screen_Day_music_sub_button = lv_img_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_sub_button, 150, 22);
	lv_obj_set_size(ui->screen_Day_music_sub_button, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_sub_button_main_main_default
	static lv_style_t style_screen_day_music_sub_button_main_main_default;
	lv_style_reset(&style_screen_day_music_sub_button_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_music_sub_button_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_music_sub_button_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_music_sub_button_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_music_sub_button, &style_screen_day_music_sub_button_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	/* Volume screen day objects */

		//Write codes screen_Main_day_volume_container
	ui->screen_Main_day_volume_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_Main_day_volume_container, 30, 167);
	lv_obj_set_size(ui->screen_Main_day_volume_container, 195, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_day_volume_container_main_main_default
	static lv_style_t style_screen_main_day_volume_container_main_main_default;
	lv_style_reset(&style_screen_main_day_volume_container_main_main_default);
	lv_style_set_radius(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_day_volume_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_main_day_volume_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_main_day_volume_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_main_day_volume_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_Main_day_volume_container, &style_screen_main_day_volume_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_volume_plus
	ui->screen_Day_volume_plus = lv_img_create(ui->screen_Main_day_volume_container);
	lv_obj_set_pos(ui->screen_Day_volume_plus, 85, 5);
	lv_obj_set_size(ui->screen_Day_volume_plus, 11, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_volume_plus_main_main_default
	static lv_style_t style_screen_day_volume_plus_main_main_default;
	lv_style_reset(&style_screen_day_volume_plus_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_volume_plus_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_volume_plus_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_volume_plus_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_volume_plus, &style_screen_day_volume_plus_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_volume_minus
	ui->screen_Day_volume_minus = lv_img_create(ui->screen_Main_day_volume_container);
	lv_obj_set_pos(ui->screen_Day_volume_minus, 85, 75);
	lv_obj_set_size(ui->screen_Day_volume_minus, 11, 3);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_volume_minus_main_main_default
	static lv_style_t style_screen_day_volume_minus_main_main_default;
	lv_style_reset(&style_screen_day_volume_minus_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_volume_minus_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_volume_minus_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_volume_minus_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_volume_minus, &style_screen_day_volume_minus_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_volume_signbtn
	ui->screen_Day_volume_signbtn = lv_img_create(ui->screen_Main_day_volume_container);
	lv_obj_set_pos(ui->screen_Day_volume_signbtn, 150, 22);
	lv_obj_set_size(ui->screen_Day_volume_signbtn, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_volume_signbtn_main_main_default
	static lv_style_t style_screen_day_volume_signbtn_main_main_default;
	lv_style_reset(&style_screen_day_volume_signbtn_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_volume_signbtn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_volume_signbtn_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_volume_signbtn_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_volume_signbtn, &style_screen_day_volume_signbtn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_volume_base
	ui->screen_Day_volume_base = lv_img_create(ui->screen_Main_day_volume_container);
	lv_obj_set_pos(ui->screen_Day_volume_base, 40, 40);
	lv_obj_set_size(ui->screen_Day_volume_base, 110, 27);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_volume_base_main_main_default
	static lv_style_t style_screen_day_volume_base_main_main_default;
	lv_style_reset(&style_screen_day_volume_base_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_volume_base_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_volume_base_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_volume_base_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_volume_base, &style_screen_day_volume_base_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_Day_volume_base,&img_day_volume_bar_base);

	//Write codes screen_Day_volume_val_img
	ui->screen_Day_volume_val_img = lv_img_create(ui->screen_Main_day_volume_container);
	lv_obj_set_pos(ui->screen_Day_volume_val_img, 40, 40);
	lv_obj_set_size(ui->screen_Day_volume_val_img, 110, 27);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_volume_val_img_main_main_default
	static lv_style_t style_screen_day_volume_val_img_main_main_default;
	lv_style_reset(&style_screen_day_volume_val_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_volume_val_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_volume_val_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_volume_val_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_volume_val_img, &style_screen_day_volume_val_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_volume_label
	ui->screen_Day_volume_label = lv_label_create(ui->screen_Main_day_volume_container);
	lv_obj_set_pos(ui->screen_Day_volume_label, 59, 16);
	lv_obj_set_size(ui->screen_Day_volume_label, 70, 20);
	lv_label_set_text(ui->screen_Day_volume_label, "Volume");
	lv_label_set_long_mode(ui->screen_Day_volume_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Day_volume_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_volume_label_main_main_default
	static lv_style_t style_screen_day_volume_label_main_main_default;
	lv_style_reset(&style_screen_day_volume_label_main_main_default);
	lv_style_set_radius(&style_screen_day_volume_label_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_volume_label_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_day_volume_label_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_day_volume_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_volume_label_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_volume_label_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_volume_label_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_volume_label_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_volume_label_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_volume_label_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_volume_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_volume_label_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_volume_label, &style_screen_day_volume_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	/* PHONE DAY SCREEN OBJECTS */

	//Write codes screen_Main_day_phone_container
	ui->screen_Main_day_phone_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_Main_day_phone_container, 30, 167);
	lv_obj_set_size(ui->screen_Main_day_phone_container, 195, 80);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_day_phone_container_main_main_default
	static lv_style_t style_screen_main_day_phone_container_main_main_default;
	lv_style_reset(&style_screen_main_day_phone_container_main_main_default);
	lv_style_set_radius(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_day_phone_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_main_day_phone_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_main_day_phone_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_main_day_phone_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_Main_day_phone_container, &style_screen_main_day_phone_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_phone_up_arrow
	ui->screen_Day_phone_up_arrow = lv_img_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_up_arrow, 84, 4);
	lv_obj_set_size(ui->screen_Day_phone_up_arrow, 12, 7);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_up_arrow_main_main_default
	static lv_style_t style_screen_day_phone_up_arrow_main_main_default;
	lv_style_reset(&style_screen_day_phone_up_arrow_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_phone_up_arrow_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_phone_up_arrow_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_phone_up_arrow_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_phone_up_arrow, &style_screen_day_phone_up_arrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_phone_up_arrow, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_phone_up_arrow,&new_day_trip_up_arrow_normal);
	lv_img_set_pivot(ui->screen_Day_phone_up_arrow, 0,0);
	lv_img_set_angle(ui->screen_Day_phone_up_arrow, 0);

	//Write codes screen_Day_phone_down_arrow
	ui->screen_Day_phone_down_arrow = lv_img_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_down_arrow, 84, 62);
	lv_obj_set_size(ui->screen_Day_phone_down_arrow, 12, 7);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_down_arrow_main_main_default
	static lv_style_t style_screen_day_phone_down_arrow_main_main_default;
	lv_style_reset(&style_screen_day_phone_down_arrow_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_phone_down_arrow_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_phone_down_arrow_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_phone_down_arrow_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_phone_down_arrow, &style_screen_day_phone_down_arrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_phone_down_arrow, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_phone_down_arrow,&new_day_trip_down_arrow_normal);
	lv_img_set_pivot(ui->screen_Day_phone_down_arrow, 0,0);
	lv_img_set_angle(ui->screen_Day_phone_down_arrow, 0);

	//Write codes screen_Day_phone_lbl_1
	ui->screen_Day_phone_lbl_1 = lv_label_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_lbl_1, 8, 7);
	lv_obj_set_size(ui->screen_Day_phone_lbl_1, 183, 20);
	lv_label_set_text(ui->screen_Day_phone_lbl_1, "");
	lv_label_set_long_mode(ui->screen_Day_phone_lbl_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_phone_lbl_1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_lbl_1_main_main_default
	static lv_style_t style_screen_day_phone_lbl_1_main_main_default;
	lv_style_reset(&style_screen_day_phone_lbl_1_main_main_default);
	lv_style_set_radius(&style_screen_day_phone_lbl_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_phone_lbl_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_day_phone_lbl_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_day_phone_lbl_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_phone_lbl_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_phone_lbl_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_phone_lbl_1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_phone_lbl_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_phone_lbl_1, &style_screen_day_phone_lbl_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_phone_lbl_2
	ui->screen_Day_phone_lbl_2 = lv_label_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_lbl_2, 42, 31);
	lv_obj_set_size(ui->screen_Day_phone_lbl_2, 100, 16);
	lv_label_set_text(ui->screen_Day_phone_lbl_2, "");
	lv_label_set_long_mode(ui->screen_Day_phone_lbl_2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_phone_lbl_2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_lbl_2_main_main_default
	static lv_style_t style_screen_day_phone_lbl_2_main_main_default;
	lv_style_reset(&style_screen_day_phone_lbl_2_main_main_default);
	lv_style_set_radius(&style_screen_day_phone_lbl_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_phone_lbl_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_day_phone_lbl_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_day_phone_lbl_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_phone_lbl_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_phone_lbl_2_main_main_default, lv_color_make(0xB8, 0xB8, 0xB8));
	lv_style_set_text_font(&style_screen_day_phone_lbl_2_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_screen_day_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_phone_lbl_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_phone_lbl_2, &style_screen_day_phone_lbl_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_phone_btn1
	ui->screen_Day_phone_btn1 = lv_img_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_btn1, 28, 49);
	lv_obj_set_size(ui->screen_Day_phone_btn1, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_btn1_main_main_default
	static lv_style_t style_screen_day_phone_btn1_main_main_default;
	lv_style_reset(&style_screen_day_phone_btn1_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_phone_btn1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_phone_btn1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_phone_btn1_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_phone_btn1, &style_screen_day_phone_btn1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_phone_btn1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_phone_btn1,&_img_night_call_declined_decline_30x30);
	lv_img_set_pivot(ui->screen_Day_phone_btn1, 0,0);
	lv_img_set_angle(ui->screen_Day_phone_btn1, 0);

	//Write codes screen_Day_phone_btn2
	ui->screen_Day_phone_btn2 = lv_img_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_btn2, 75, 49);
	lv_obj_set_size(ui->screen_Day_phone_btn2, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_btn2_main_main_default
	static lv_style_t style_screen_day_phone_btn2_main_main_default;
	lv_style_reset(&style_screen_day_phone_btn2_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_phone_btn2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_phone_btn2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_phone_btn2_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_phone_btn2, &style_screen_day_phone_btn2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_phone_btn2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_phone_btn2,&_img_night_call_declined_decline_30x30);
	lv_img_set_pivot(ui->screen_Day_phone_btn2, 0,0);
	lv_img_set_angle(ui->screen_Day_phone_btn2, 0);

	//Write codes screen_Day_phone_btn3
	ui->screen_Day_phone_btn3 = lv_img_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_btn3, 122, 49);
	lv_obj_set_size(ui->screen_Day_phone_btn3, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_btn3_main_main_default
	static lv_style_t style_screen_day_phone_btn3_main_main_default;
	lv_style_reset(&style_screen_day_phone_btn3_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_phone_btn3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_phone_btn3_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_phone_btn3_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_phone_btn3, &style_screen_day_phone_btn3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_phone_btn3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_phone_btn3,&call_accept_darkgreen_icon);
	lv_img_set_pivot(ui->screen_Day_phone_btn3, 0,0);
	lv_img_set_angle(ui->screen_Day_phone_btn3, 0);

	//Write codes screen_Day_phone_call_btn
	ui->screen_Day_phone_call_btn = lv_img_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_call_btn, 146, 19);
	lv_obj_set_size(ui->screen_Day_phone_call_btn, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_call_btn_main_main_default
	static lv_style_t style_screen_day_phone_call_btn_main_main_default;
	lv_style_reset(&style_screen_day_phone_call_btn_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_phone_call_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_phone_call_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_phone_call_btn_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_phone_call_btn, &style_screen_day_phone_call_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_phone_call_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_phone_call_btn,&_img_night_contacts_l1_call_icon_30x30);
	lv_img_set_pivot(ui->screen_Day_phone_call_btn, 0,0);
	lv_img_set_angle(ui->screen_Day_phone_call_btn, 0);


    /*Passcode Screen*/
    
    //Write codes screen_Passcode_Day_container
	ui->screen_Passcode_Day_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_Passcode_Day_container, 30, 167);
	lv_obj_set_size(ui->screen_Passcode_Day_container, 195, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_passcode_day_container_main_main_default
	static lv_style_t style_screen_passcode_day_container_main_main_default;
	lv_style_reset(&style_screen_passcode_day_container_main_main_default);
	lv_style_set_radius(&style_screen_passcode_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_passcode_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_passcode_day_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_passcode_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_passcode_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_passcode_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_passcode_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_passcode_day_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_passcode_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_passcode_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_passcode_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_passcode_day_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_Passcode_Day_container, &style_screen_passcode_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_passcode_day_lbl1
	ui->screen_passcode_day_lbl1 = lv_label_create(ui->screen_Passcode_Day_container);
	lv_obj_set_pos(ui->screen_passcode_day_lbl1, 46, 9);
	lv_obj_set_size(ui->screen_passcode_day_lbl1, 98, 18);
	lv_label_set_text(ui->screen_passcode_day_lbl1, "Passcode");
	lv_label_set_long_mode(ui->screen_passcode_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_passcode_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_passcode_day_lbl1_main_main_default
	static lv_style_t style_screen_passcode_day_lbl1_main_main_default;
	lv_style_reset(&style_screen_passcode_day_lbl1_main_main_default);
	lv_style_set_radius(&style_screen_passcode_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_passcode_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_passcode_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_passcode_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_passcode_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_passcode_day_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_passcode_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_passcode_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_passcode_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_passcode_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_passcode_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_passcode_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->screen_passcode_day_lbl1, &style_screen_passcode_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_passcode_day_lbl2
	ui->screen_passcode_day_lbl2 = lv_label_create(ui->screen_Passcode_Day_container);
	lv_obj_set_pos(ui->screen_passcode_day_lbl2, 68, 35);
	lv_obj_set_size(ui->screen_passcode_day_lbl2, 51, 16);
	lv_label_set_text(ui->screen_passcode_day_lbl2, "123456");
	lv_label_set_long_mode(ui->screen_passcode_day_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_passcode_day_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_passcode_day_lbl2_main_main_default
	static lv_style_t style_screen_passcode_day_lbl2_main_main_default;
	lv_style_reset(&style_screen_passcode_day_lbl2_main_main_default);
	lv_style_set_radius(&style_screen_passcode_day_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_passcode_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_passcode_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_passcode_day_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_passcode_day_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_passcode_day_lbl2_main_main_default, lv_color_make(0x70, 0x6f, 0x6f));
	lv_style_set_text_font(&style_screen_passcode_day_lbl2_main_main_default, &lv_font_FjallaOne_Regular_16);
	lv_style_set_text_letter_space(&style_screen_passcode_day_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_passcode_day_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_passcode_day_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_passcode_day_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_passcode_day_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->screen_passcode_day_lbl2, &style_screen_passcode_day_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_passcode_day_lbl3
	ui->screen_passcode_day_lbl3 = lv_label_create(ui->screen_Passcode_Day_container);
	lv_obj_set_pos(ui->screen_passcode_day_lbl3, 60, 38);
	lv_obj_set_size(ui->screen_passcode_day_lbl3, 7, 9);
	lv_label_set_text(ui->screen_passcode_day_lbl3, "<");
	lv_label_set_long_mode(ui->screen_passcode_day_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_passcode_day_lbl3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_passcode_day_lbl3_main_main_default
	static lv_style_t style_screen_passcode_day_lbl3_main_main_default;
	lv_style_reset(&style_screen_passcode_day_lbl3_main_main_default);
	lv_style_set_radius(&style_screen_passcode_day_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_passcode_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_passcode_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_passcode_day_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_passcode_day_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_passcode_day_lbl3_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_passcode_day_lbl3_main_main_default, &lv_font_FjallaOne_Regular_10);
	lv_style_set_text_letter_space(&style_screen_passcode_day_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_passcode_day_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_passcode_day_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_passcode_day_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_passcode_day_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->screen_passcode_day_lbl3, &style_screen_passcode_day_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_passcode_day_lbl4
	ui->screen_passcode_day_lbl4 = lv_label_create(ui->screen_Passcode_Day_container);
	lv_obj_set_pos(ui->screen_passcode_day_lbl4, 121, 38);
	lv_obj_set_size(ui->screen_passcode_day_lbl4, 7, 9);
	lv_label_set_text(ui->screen_passcode_day_lbl4, ">");
	lv_label_set_long_mode(ui->screen_passcode_day_lbl4, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_passcode_day_lbl4, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_passcode_day_lbl4_main_main_default
	static lv_style_t style_screen_passcode_day_lbl4_main_main_default;
	lv_style_reset(&style_screen_passcode_day_lbl4_main_main_default);
	lv_style_set_radius(&style_screen_passcode_day_lbl4_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_passcode_day_lbl4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_passcode_day_lbl4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_passcode_day_lbl4_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_passcode_day_lbl4_main_main_default, 0);
	lv_style_set_text_color(&style_screen_passcode_day_lbl4_main_main_default, lv_color_make(0x70, 0x6f, 0x6f));
	lv_style_set_text_font(&style_screen_passcode_day_lbl4_main_main_default, &lv_font_FjallaOne_Regular_10);
	lv_style_set_text_letter_space(&style_screen_passcode_day_lbl4_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_passcode_day_lbl4_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_passcode_day_lbl4_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_passcode_day_lbl4_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_passcode_day_lbl4_main_main_default, 0);
	lv_obj_add_style(ui->screen_passcode_day_lbl4, &style_screen_passcode_day_lbl4_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Tacho_Mid_grey
	ui->screen_Tacho_Mid_grey = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Tacho_Mid_grey, 0, 7);
	lv_obj_set_size(ui->screen_Tacho_Mid_grey, 240, 306);

	//Write style state: LV_STATE_DEFAULT for style_screen_tacho_mid_grey_main_main_default
	static lv_style_t style_screen_tacho_mid_grey_main_main_default;
	lv_style_reset(&style_screen_tacho_mid_grey_main_main_default);
	lv_style_set_img_recolor(&style_screen_tacho_mid_grey_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tacho_mid_grey_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tacho_mid_grey_main_main_default, 255);
	lv_obj_add_style(ui->screen_Tacho_Mid_grey, &style_screen_tacho_mid_grey_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_Tacho_Mid_grey,&Red_night_middle_grey_circler);

}

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : v1.0.0                          
    REVISION DATE        : 06/09/2022        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/


