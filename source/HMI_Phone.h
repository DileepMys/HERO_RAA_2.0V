

/* @file FILE NAME */
#ifndef HMI_PHONE_H
#define HMI_PHONE_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Balasubramanina (balasubramanian@niyatainfotech.com)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : HMI_Phone.h
*  Version                         : 
*  Micros supported                : 
*  Compilers supported             : 
*  Platforms supported             :                 
*  Description                     : This header file contains the declarations of phone design
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/**********************************************************************************************************************/
/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/

#include "hal_stdtypes.h"
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
* @brief This macro is used to define 
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
 * @brief    This typedef enum is used to define 
 * @param    
 * @param
 **/


/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/

typedef enum
{
    BLE_PASSCODE_DISPLAY = 0,
    BLE_CONNECTED,
    BLE_DISCONNECTED,
    BLE_MAX_STATE
}BLE_Connectectivity_Status_TypeEn;

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/
/*
* @brief    This API is used to define the phone images
* @param1    Day_Night_Mode_u8 - used to define day or night mode
* @return  
* @invocation 
*/
void GUI_Phone_Main_Screen(uint8_t Screen_Main_Int_u8, uint8_t Day_Night_Mode_u8);

/*
* @brief    This API is used to define the phone images
* @param1    Day_Night_Mode_u8 - used to define day or night mode
* @return  
* @invocation 
*/
void GUI_Phone_Screen(void);


void GUI_Signal(void);
void GUI_Phone_Contact_List(void);
void GUI_Phone_Volume_Control(void);

void GUI_Phone_SMS_info(void);

void GUI_Phone_Missed_call_Info(void);

void GUI_Phone_Incoming_Call_Info(void);
void GUI_Contact_screen_Night_Entry(void);
void GUI_Contact_screen__Night_Exit(void);
void GUI_Contact_screen_Night_During(void);
void GUI_Volume_screen_Night_Entry(void);
void GUI_Volume_screen_Night_Exit(void);
void GUI_Volume_screen_Night_During(void);

void GUI_Volume_Screen_Night_Show_Entry(void);;
void GUI_Volume_Screen_Night_Show_Exit(void);
void GUI_Volume_Screen_Night_Show_During(void);

void GUI_Volume_Screen_Main_Day_Mode_Entry(void);
void GUI_Volume_Screen_Main_Day_Mode_During(void);
void GUI_Volume_Screen_Day_Mode_Exit(void);

void GUI_Phone_Screen_Main_Day_Mode_Entry(void);
void GUI_Phone_Screen_Main_Day_Mode_During(void);
void GUI_Phone_Screen_Main_Day_Mode_Exit(void);

void GUI_Volume_Sub_Screen_Main_Day_Mode_Entry(void);
void GUI_Volume_Sub_Screen_Main_Day_Mode_During(void);
void GUI_Volume_Sub_Screen_Day_Mode_Exit(void);

void GUI_Phone_Sub_Screen_Main_Day_Mode_Entry(void);
void GUI_Phone_Sub_Screen_Main_Day_Mode_During(void);
void GUI_Phone_Sub_Screen_Main_Day_Mode_Exit(void);

void GUI_Password_Screen(void);
void PASSCODE_Screen_Exit(void);

void GUI_BLE_Events_Entry(void);

void GUI_Phone_Contact_List_Night_Entry(void);
void GUI_Phone_Contact_List_Night_During(void);
void GUI_phone_Contact_List_Night_Exit(void);

void GUI_Phone_Contact_Call_Night_Entry(void);
void GUI_Phone_Contact_Call_Night_During(void);
void GUI_Phone_Contact_Call_Night_Exit(void);

void GUI_Phone_Contact_List_Day_Entry(void);
void GUI_Phone_Contact_List_Day_During(void);
void GUI_Phone_contact_List_Day_Exit(void);

void GUI_Phone_Contact_Call_Day_Entry(void);
void GUI_Phone_Contact_Call_Day_During(void);
void GUI_Phone_Contact_Call_Day_Exit(void);

uint8_t GUI_Up_Phone_contact_list(void);
uint8_t GUI_Down_Phone_contact_list(void);

void PASSCODE_SCREEN_ENTRY(void);

/* Contact Calling Button Features*/
uint8_t GUI_Contact_Right_button_Click(void);
uint8_t GUI_Contact_Left_button_Click(void);
uint8_t GUI_Contact_Up_button_Click(void);
uint8_t GUI_Contact_Down_button_Click(void);
uint8_t	GUI_Volume_Mute(void);
uint8_t Call_Selectbtn_click(void);

/* Passcode Screen Day Fuctions */
void Passcode_Screen_Day_Entry();
void Passcode_Screen_Day_Exit();
void Passcode_Screen_Day_During();

/* Phone Volume Screen Functions*/

void GUI_Phone_Volume_Night_Entry();
void GUI_Phone_Volume_Night_Exit();
void GUI_Phone_Volume_Day_Entry();
void GUI_Phone_Volume_Day_Exit();

void GUI_Phone_SMS_info_Day(void);
void GUI_Phone_Missed_call_Info_Day(void);

void GUI_Phone_Screen_Day(void);
void GUI_Signal_Day(void);

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.1                                                
    REVISION DATE        : 8/22/2022                              
    CREATED / REVISED BY : Balasubramaninan (balasubramanian@niyatainfotech.com)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! HMI_PHONE */



