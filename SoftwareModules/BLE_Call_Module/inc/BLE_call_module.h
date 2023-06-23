/* @file FILE NAME */
#ifndef BLE_CALL_MODULE_H
#define BLE_CALL_MODULE_H
/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Jeevajothi (jeevajothi@niyatainfotech.com)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : BLE_music_module.h
*  Version                         : v1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent                
*  Description                     : BLE_call module performance
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
//#include "BLE_music_module_cfg.h"
//#include "hal_stdtypes.h"
#include "UART_DataManager.h"


/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/



/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief   this structure is extracted from contact  packet information 
 * @param    
 * @param
 **/
typedef struct               
{
  unsigned char Contact_number1[18];
  unsigned char Contact_number2[18];
  unsigned char Contact_number3[18];
  unsigned char Contact_number4[18];
  unsigned char Contact_number5[18];
  unsigned char Contact_number6[18];
}HMI_contact_number_st;


/*
 * @brief   this structure is extracted from missed sms information 
 * @param    
 * @param
 **/

typedef struct
{
  uint8_t Number_of_SMS[2];  
}HMI_SMS_info_st;

/*
 * @brief   this structure is extracted from missed calls information 
 * @param    
 * @param
 **/


typedef struct
{
  uint8_t NUmber_of_missed_call[2];  
}HMI_missed_call_INFO_st;

typedef struct
{
  uint8_t USER_NAME[18];
}HMI_USERNAME_Info_st;


/*
 * @brief   this structure is extracted from current call active screen 
 * @param    
 * @param
 **/

typedef struct
{
  uint8_t First_caller_name[18];
  uint8_t First_call_status;
  uint8_t Second_caller_name[18];
  uint8_t Second_call_status;
  uint8_t call_duration[6];
  uint8_t PH_volume_level;  
}HMI_Active_call_screen_st;


/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/
/*
* @brief   This API is used to declare the initialization of the call module.
* @param    NA
* @return   NA
* @invocation NA
*/
void BLE_Call_module_init(void);


/*
* @brief   This API is used to reset the initial values of the  of the call module.
* @param    NA
* @return  NA
* @invocation NA
*/
void BLE_Call_module_de_init(void);

/*
* @brief   This API is used to initialize the peripheral of the call module.
* @param    NA
* @return  NA
* @invocation NA
*/
void BLE_call_activate(void);

/*
* @brief   This API is used to reset the peripheral of the call module.
* @param    NA
* @return  NA
* @invocation NA
*/
void BLE_call_deactivate(void);

/*
* @brief   This API is used to check pre condition status such as ign on/off lvsd/hvsd  
* @param   NA 
* @return  boolean
* @invocation To occur on the system  startup state condition.
*/
uint8_t BLE_call_Pre_Condition_check(void);

/*
* @brief   This API is used to check the BLE connectivity information status 
* @param   NA 
* @return  boolean
* @invocation To occur on the system BLE startup state condition.
*/
uint8_t Check_BLE_call_Connectivity_status(void);

/*
* @brief   This API is used to declare main functions of the call module 
* @param   NA 
* @return  boolean
* @invocation To occur on the system BLE startup state condition.
*/
void BLE_Call_Mainfunction(void);

/*
* @brief   This API is used to decrease the volume level of the call 
* @param   NA 
* @return  structure type
* @invocation Funtion occurs on the call main screen.
*/
void BLE_call_function_screen(Cluster_Joystick_Info_En CAll_Info);

/*
* @brief   This API is used to get the contact list from BLE
* @param   NA 
* @return  structure type
* @invocation Funtion occurs on the call main screen.
*/
HERO_SMARTPHONE_CALL_NUMBER_PKT_TYPE_ST BLE_contact_index_screen(void);

/*
* @brief   This API is used to get the missed call information from BLE
* @param   NA 
* @return  structure type
* @invocation Funtion occurs on the call main screen.
*/
HERO_SMARTPHONE_MISSED_CALL_PKT_TYPE_ST BLE_missedcall_screen(void);


/*
* @brief   This API is used to get the NUMBER OF UNREAD information from BLE
* @param   NA 
* @return  structure type
* @invocation Funtion occurs on the call main screen.
*/
HERO_SMARTPHONE_SMS_NUMBER_PKT_TYPE_ST BLE_UNREAD_SMS_screen(void);

/*
* @brief   This API is used to get the actiive call screen information from BLE
* @param   NA 
* @return  structure type
* @invocation Funtion occurs on the call main screen.
*/
HERO_SMARTPHONE_CALL_STATUS_PKT_TYPE_ST BLE_active_call_info_screen(void);


/*
* @brief   This API is used to pass the contact information to the hmi through pointer.
* @param   NA 
* @return  structure type
* @invocation Funtion occurs on the call main screen.
*/
void HMI_contact_info_screen_info(HMI_contact_number_st *g_call_main_screen_info_st_ptr);

/*
* @brief   This API is used to pass the SMS information to the hmi through pointer.
* @param   NA 
* @return  structure type
* @invocation Funtion occurs on the call main screen.
*/
void HMI_unread_SMS_screen_info(HMI_SMS_info_st *g_sms_info_ptr);
/*
* @brief   This API is used to pass the MISSED CALL information to the hmi through pointer.
* @param   NA 
* @return  structure type
* @invocation Funtion occurs on the call main screen.
*/
void HMI_missed_call_screen_info(HMI_missed_call_INFO_st *g_missed_call_info_ptr);

/*
* @brief   This API is used to pass the ACTIVE CALL  information to the hmi through pointer.
* @param   NA 
* @return  structure type
* @invocation Funtion occurs on the call main screen.
*/
void HMI_active_call_screen_info(HMI_Active_call_screen_st *g_active_call_screen_info_ptr);

/*
* @brief   This API is used to pass the contact information to the hmi through pointer.
* @param   NA 
* @return  structure type
* @invocation Funtion occurs on the call main screen.
*/
void BLE_call_index0_screen(Cluster_Joystick_Info_En CAll_Info);

/*
* @brief   This API is used to pass the contact information to the hmi through pointer.
* @param   NA 
* @return  structure type
* @invocation Funtion occurs on the call main screen.
*/
void HMI_UserName_info(HMI_USERNAME_Info_st *g_username_info_ptr);



/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : v1.0.0
    REVISION DATE        : MONTH/DATE/YEAR                              
    CREATED / REVISED BY : Jeevajothi (jeevajothi@niyatainfotech.com)
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! BLE_CALL_MODULE_H */
