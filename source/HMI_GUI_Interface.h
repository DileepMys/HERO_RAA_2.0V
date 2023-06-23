#ifndef HMI_GUI_INTERFACE_H
#define HMI_GUI_INTERFACE_H


typedef struct
{
	uint32_t IntermediateIdx;
	uint32_t ScreenIdx;
}IntermediateMapTblType_St;


uint8_t Set_Music_Enable_Setting(void);
uint8_t Set_Bluetooth_Enable_Setting(void);
uint8_t Set_24HrModeEnable_Setting(void);
uint8_t Set_BrightnessMode_Auto(void);
uint8_t Set_BrightnessMode_LOW(void);
uint8_t Set_BrightnessMode_Medium(void);
uint8_t Set_BrightnessMode_High(void);
uint8_t Set_Fuel_consumption_unit(void);
uint8_t Music_Setting_Screen_Album(void);
uint8_t Music_Setting_Screen_Artist(void);
uint8_t Music_Setting_Screen_Genre(void);
uint8_t ResetTripA(void);
uint8_t ResetTripB(void);
uint8_t SkipIntermediateIfSelected(void);
uint8_t SkipReverseIntermediateIfSelected(void);
void HomeScreenLocalEntry(void);
void HomeScreenEntryFn(void);
void IntermediateScreen_Night_Entry(void);
void Intermediate_Screen_Day_Entry(void);
void GUiTachoHandler(void);
uint8_t IntermediateScreen_Volume_Decrement(void);
uint8_t IntermediateScreen_Volume_Increment(void);
uint8_t IntermediateScreen_Contact_Increment(void);
uint8_t IntermediateScreen_Contact_Decrement(void);
uint8_t IntermediateScreen_Music_PlayPause(void);
uint8_t IntermediateScreen_Music_PrevTrack(void);
uint8_t IntermediateScreen_Music_NextTrack(void);

uint8_t HMI_Get_Possible_Screen_Transition(void);
uint8_t JmpPrevIntermediateScreen(void);
void HomeScreenExitFn(void);

void SettingScreenEntryFn(void);

 void SettingScreenDuringFn(void);


void Hide_container(void);

void Settingmain_exit(void);

//void BikeMenu_during(void);
void BikeMenuExit(void);

void About_Exit(void);

void Conn_Bluetooth_Show(void);

void Connectivity_Exit(void);

void Display_Exit(void);
void Intermediate_Hide_Day_Container(void);
void Intermediate_Hide_Night_Container(void);
void ResetBLE(void);


void SettingMainEntry(void);
void AboutMenuEntry(void);
void Display_Menu_Entry(void);
void Connectivity_Entry(void);
void Display_Menu_Exit(void);

void SettingMain_Day_Entry(void);
void SettingMain_Day_Exit(void);


void BikeMenu_Day_Exit(void);


void AboutMenu_Day_Exit(void);


void DisplayMenu_Day_Exit(void);

void Music_Night_Entry(void);
void Music_Night_Exit(void);


void Music_Day_Entry(void);
void Music_Day_Exit(void);

void Brightness_Night_Entry(void);
void Brightness_Night_Exit(void);

void Brightness_Day_Entry(void);
void Brightness_Day_Exit(void);

void Menu_Night_Entry(void);
void Menu_Night_Exit(void);


void Menu_Day_Exit(void);

void Date_Time_Night_Entry(void);
void Date_Time_Night_Exit(void);

void Date_Time_Day_Entry(void);
void Date_Time_Day_Exit(void);

void Unit_Night_Exit(void);

void Unit_Day_Entry(void);
void Unit_Day_Exit(void);

void Unit_Sub_Night_Exit(void);

void Unit_Sub_Day_Exit(void);

void About_Info_Night_Entry(void);
void About_Info_Night_Exit(void);

void About_Info_Day_Entry(void);
void About_Info_Day_Exit(void);

void Date_Set_Night_Entry(void);
void Date_Set_Night_Exit(void);

void Date_Set_Day_Entry(void);
void Date_Set_Day_Exit(void);

void Time_Set_Night_Entry(void);
void Time_Set_Night_Exit(void);

void Time_Set_Day_Entry(void);
void Time_Set_Day_Exit(void);

void Time_12_Night_Entry(void);
void Time_12_Night_Exit(void);
void Time_12_Day_Entry(void);
void Time_12_Day_Exit(void);

void Batter_Val_Night_Entry(void);
void Battery_Val_Night_Exit(void);

void Battey_Val_Day_Entry(void);
void Battery_Val_Day_Exit(void);


void Trip_Night_Entry(void);
void Trip_Night_Exit(void);
void Trip_Day_Entry(void);
void Trip_Day_Exit(void);

void Battery_Val_Night_During(void);
void TripA_Trip_During(void);


void Battery_Val_Night_During(void);
void TripA_Trip_Night_During(void);
void TripA_Time_Night_During(void);
void TripA_AvSpeed_Night_During(void);
void TripA_AVFuel_Night_During(void);
void TripA_Hold_Night_During(void);

void Battery_val_Day_During(void);

void TripB_Trip_Night_During(void);
void TripB_Time_Night_During(void);
void TripB_AvSpeed_Night_During(void);
void TripB_AVFuel_Night_During(void);
void TripB_Hold_Night_During(void);

void Brightness_Night_Auto_During(void);
void Brightness_Night_Low_During(void);
void Brightness_Night_Med_During(void);
void Brightness_Night_High_During(void);

void Menu_Night_Volume_During(void);
void Menu_Night_Tripb_During(void);
void Menu_Night_FUEL_During(void);
void Menu_Night_Navi_During(void);
void Menu_Night_GeInfo_During(void);
void Menu_Night_Phone_During(void);
void Menu_Night_Music_During(void);

void Datetimeset_Night_Date_During(void);
void Datetimeset_Night_Time_During(void);
void Datetimeset_Night_24Hr_During(void);


void Dateset_Night_During(void);
void Timeset_Night_During(void);
void Timeset_24_Night_During(void);

void Dateset_Night_Entry(void);
void Dateset_Night_Exit(void);

void Timeset_Night_Entry(void);
void Timeset_Night_Exit(void);
void Timeset_12_Night_Entry(void);
void Timeset_12_Night_Exit(void);

void SWInfo_Entry(void);
void SWInfo_Exit(void);

void Unit_Sub_fuel_km_Day_During(void);

void Music_Night_Album_During(void);
void Music_Night_Artist_During(void);
void Music_Night_Genre_During(void);


void Unit_Sub_fuel_km_During(void);
void Unit_Sub_fuel_L100_During(void);

void Unit_Sub_fuel_L100_Day_During(void);
void Unit_Sub_fuel_km__Day_During(void);



void Music_Day_Album_During(void);
void Music_Day_Artist_During(void);
void Music_Day_Genre_During(void);

/*
Day Mode
*/

void Unit_Sub_fuel_L100_Day_During(void);



void TripA_Trip_Day_During(void);
void TripA_Time_Day_During(void);
void TripA_AvSpeed_Day_During(void);
void TripA_AVFuel_Day_During(void);
void TripA_Hold_Day_During(void);
void TripB_Trip_Day_During(void);
void TripB_Time_Day_During(void);
void TripB_AvSpeed_Day_During(void);
void TripB_AVFuel_Day_During(void);
void TripB_Hold_Day_During(void);

void Brightness_Day_Auto_During(void);
void Brightness_Day_Low_During(void);
void Brightness_Day_Med_During(void);
void Brightness_Day_High_During(void);


void Menu_Day_Volume_During(void);
void Menu_Day_Tripb_During(void);
void Menu_Day_FUEL_During(void);
void Menu_Day_Navi_During(void);
void Menu_Day_GeInfo_During(void);
void Menu_Day_Phone_During(void);
void Menu_Day_Music_During(void);



uint8_t	SetMENU_SELECTION_VOLUME(void);
uint8_t SetMENU_SELECTION_TRIPB(void);
uint8_t SetMENU_SELECTION_FUEL(void);
uint8_t SetMENU_SELECTION_NAVIGATION(void);
uint8_t SetMENU_SELECTION_GI(void);
uint8_t SetMENU_SELECTION_PHONE(void);
uint8_t SetMENU_SELECTION_MUSIC(void);

uint8_t	ReadMENU_SELECTION_VOLUME(void);
uint8_t ReadMENU_SELECTION_TRIPB(void);
uint8_t ReadMENU_SELECTION_FUEL(void);
uint8_t ReadMENU_SELECTION_NAVIGATION(void);
uint8_t ReadMENU_SELECTION_GI(void);
uint8_t ReadMENU_SELECTION_PHONE(void);
uint8_t ReadMENU_SELECTION_MUSIC(void);

void Datetimeset_Day_Date_During(void);
void Datetimeset_Day_Time_During(void);
void Datetimeset_Day_24Hr_During(void);




void Timeset_Day_Entry(void);
void Timeset_Day_Exit(void);
void Timeset_12_Day_Entry(void);
void Timeset_12_Day_Exit(void);

void AboutMenuEntry_Day_Entry(void);




void Conn_Bluetooth_Day_Show(void);


void Connect_day_exit(void);
void Connect_day_Entry(void);

void SWInfo_Day_Entry(void);
void SWInfo_Day_Exit(void);

void SettingScreenDuringFn(void);
void HomeScreenMainDuringFn(void);
void HomeScreenDuringFn(void);


void Dateset_Day_Entry(void);
void Dateset_Day_Exit(void);

void HomeScreen_Day_EntryFn(void);

void HomeScreen_Day_DuringFn(void);

void Day_mode_RPM_images(void);


void HomeScreenDay_Exit(void);


void GUI_Time_Format_Night_24Hr_During(void);
void GUI_Time_Format_Night_12Hr_During(void);
void GUI_Time_Format_Night_Exit(void);

void GUI_Time_Format_Day_Entry(void);
void GUI_Time_Format_Day_24Hr_During(void);
void GUI_Time_Format_Day_12Hr_During(void);
void GUI_Time_Format_Day_Exit(void);

void GUI_RiderInfo_Night_Entry(void);
void GUI_RiderInfo_Night_During(void);
void GUI_RiderInfo_Night_Exit(void);

void GUI_RiderInfo_Day_Entry(void);
void GUI_RiderInfo_Day_During(void);
void GUI_RiderInfo_Day_Exit(void);


void GUI_Disclaimer_Details_Night_Exit(void);

void GUI_Disclaimer_Details_Day_Exit(void);

void Monthset_Night_Entry(void);
void Monthset_Night_Exit(void);
void Yearset_Night_Entry(void);
void Yearset_Night_Exit(void);

void Monthset_Day_Entry(void);
void Monthset_Day_Exit(void);
void Yearset_Day_Entry(void);
void Yearset_Day_Exit(void);

void Time_hr_set_Night_Entry(void);
void Time_hr_set_Night_Exit(void);
void Time_min_set_Night_Entry(void);
void Time_min_set_Night_Exit(void);
void Time_ampm_set_Night_Entry(void);
void Time_ampm_set_Night_Exit(void);

void Time_hr_set_Day_Entry(void);
void Time_min_set_Day_Entry(void);
void Time_ampm_set_Day_Entry(void);

void Display_hr_Time_Setting_Day_During(void);
void Display_min_Time_Setting_Day_During(void);
void Display_ampm_Time_Setting_Day_During(void);

void Time_hr_set_Day_Exit(void);
void Time_min_set_Day_Exit(void);
void Time_ampm_set_Day_Exit(void);



/* New Function For Peer Review Command */

void Setting_Main_Connectivity_Night_Entry(void);
void Setting_Main_Bike_Night_Entry(void);
void Setting_Main_Display_Night_Entry(void);
void Setting_Main_About_Night_Entry(void);

void Setting_Main_Connectivity_Day_Entry(void);
void Setting_Main_Bike_Day_Entry(void);
void Setting_Main_Display_Day_Entry(void);
void Setting_Main_About_Day_Entry(void);

void Connect_Bluetooth_Night_Entry(void);
void Connect_Music_Night_Entry(void);

void Connect_Bluetooth_Day_Entry(void);
void Connect_Music_Day_Entry(void);

void Music_Artist_Night_Entry(void);
void Music_Album_Night_Entry(void);
void Music_Genre_Night_Entry(void);

void Music_Artist_Day_Entry(void);
void Music_Album_Day_Entry(void);
void Music_Genre_Day_Entry(void);

void About_Rider_Night_Entry(void);
void About_Software_Night_Entry(void);
void About_Disclaimer_Night_Entry(void);

void About_Rider_Day_Entry(void);
void About_Software_Day_Entry(void);
void About_Disclaimer_Day_Entry(void);


void Disclaimer_Night_Entry(void);

void Disclaimer_Day_Entry(void);

void Unit_Sub_Km_Night_Entry(void);
void Unit_Sub_fuel_km_Night_Entry(void);
void Unit_Sub_fuel_L100_Night_Entry(void);

void Unit_Sub_Km_Day_Entry(void);
void Unit_Sub_fuel_km_Day_Entry(void);
void Unit_Sub_fuel_L100_Day_Entry(void);

void BikeMenu_Night_1_Entry(void);
void BikeMenu_Night_2_Entry(void);
void BikeMenu_Night_3_Entry(void);

void BikeMenu_Day_1_Entry(void);
void BikeMenu_Day_2_Entry(void);
void BikeMenu_Day_3_Entry(void);

void Display_Brightness_Night_Entry(void);
void Display_Menu_Night_Entry(void);
void Display_DateandTime_Night_Entry(void);
void Display_Unit_Night_Entry(void);

void Display_Brightness_Day_Entry(void);
void Display_Menu_Day_Entry(void);
void Display_DateandTime_Day_Entry(void);

void Display_Menu_Day_Exit(void);

void Brightness_Low_Night_Entry(void);
void Brightness_High_Night_Entry(void);
void Brightness_Med_Night_Entry(void);
void Brightness_Auto_Night_Entry(void);

void Brightness_Low_Day_Entry(void);
void Brightness_High_Day_Entry(void);
void Brightness_Med_Day_Entry(void);
void Brightness_Auto_Day_Entry(void);

void Unit_Distance_Night_Entry(void);
void Unit_Fuel_Night_Entry(void);

void Unit_Distance_Day_Entry(void);
void Unit_Fuel_Day_Entry(void);


void Menu_TripB_Night_Entry(void);
void Menu_Fuel_Night_Entry(void);
void Menu_Navi_Night_Entry(void);
void Menu_GeInfo_Night_Entry(void);
void Menu_Phone_Night_Entry(void);
void Menu_Music_Night_Entry(void);
void Menu_Volume_Night_Entry(void);

void Menu_TripB_Day_Entry(void);
void Menu_Fuel_Day_Entry(void);
void Menu_Navi_Day_Entry(void);
void Menu_GeInfo_Day_Entry(void);
void Menu_Phone_Day_Entry(void);
void Menu_Music_Day_Entry(void);
void Menu_Volume_Day_Entry(void);

void Datetimeset_Date_Night_Entry(void);
void Datetimeset_Time_Night_Entry(void);
void Datetimeset_24Hr_Night_Entry(void);

void Datetimeset_Date_Day_Entry(void);
void Datetimeset_Time_Day_Entry(void);
void Datetimeset_24Hr_Day_Entry(void);

void TimeFormat_24Hr_Night_Entry(void);
void TimeFormat_12Hr_Night_Entry(void);

void TimeFormat_24Hr_Day_Entry(void);
void TimeFormat_12_Hr_Day_Entry(void);

void Display_Unit_Day_Entry(void);


void Setting_Main_Color_Event_Night_During(void);
void Setting_Main_Color_Event_Day_During(void);

uint8_t SettingArrow_UpButton_Pressed (void);

uint8_t SettingArrow_DownButton_Pressed (void);

void HomeScreenEntry_Day(void);
void HomeScreenExit_Day(void);
void HomeScreenMain_DayDuring(void);

void HomeScreen_LocalEntry_Day(void);
void GUI_Main_Screen_Entry_Day(void);

void TripB_Night_Entry(void);
void TripB_Day_Entry(void);

void Connect_MUSIC_Night_During(void);
void Connnect_Music_Day_During(void);

void About_Night_During(void);
void About_Day_During(void);

void BikeMenu_Night_During(void);
void BikeMenu_Day_During(void);

void Display_Night_During(void);
void Display_Day_During(void);

void Display_Unit_Night_During(void);
void Display_Unit_Day_During(void);




#endif