/* @file BLE_MUSIC_MODULE_H */
#ifndef BLE_MUSIC_MODULE_H
#define BLE_MUSIC_MODULE_H

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
*  Description                     : This file consists of implementation of header file such as variable,function declaration
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include "BLE_music_module_cfg.h"
#include "hal_stdtypes.h"
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
 * @brief   this structure is extracted from music packet information 
 * @param    
 * @param
 **/
typedef struct
{
  uint8_t song_name[20];
  uint8_t artist_name[20];
  uint8_t elapsed_time;
  uint8_t playback_state;
  uint8_t Volume_Level;
}HMI_Music_Main_Screen_Type_St;

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/
/*
* @brief   This API is used to declare the initialization of the music module.
* @param    NA
* @return   NA
* @invocation NA
*/
void BLE_Music_module_init(void);

/*
* @brief   This API is used to declare the de-initialization of the music module.
* @param    NA
* @return  NA
* @invocation NA
*/
void BLE_Music_module_de_init(void);


/*
* @brief   This API is used to initialize the peripherals
* @param    NA
* @return  NA
* @invocation NA
*/
void BLE_music_activate(void);


/*
* @brief   This API is used to reset the peripherals
* @param    NA
* @return  NA
* @invocation NA
*/
void BLE_music_deactivate(void);

/*
* @brief   This API is used to hold the music screen information. 
* @param   NA 
* @return  boolean
* @invocation To occur on the system  startup state condition.
*/
boolean BLE_Pre_Condition_check(void);

/*
* @brief   This API is used to check the BLE connectivity information status 
* @param   NA 
* @return  boolean
* @invocation To occur on the system BLE startup state condition.
*/
uint8_t Check_BLE_Connectivity_status(void);

/*
* @brief   This API is used to hold the music screen information 
* @param   NA 
* @return  structure type
* @invocation Funtion occurs on the musc main screen.
*/
HERO_SMARTPHONE_MUSIC_PKT_TYPE_ST  BLE_music_main_screen(void);

/*
* @brief   This API is used to get the music packet inforation from the APP  
* @param    
* @return  
* @invocation 
*/
HERO_SMARTPHONE_MUSIC_PKT_TYPE_ST BLE_music_function_screen(void);

/*
* @brief   This API is used to get the extracted  music packet inforation from the APP  
* @param    
* @return  
* @invocation 
*/
void HMI_music_main_screen_info(HMI_Music_Main_Screen_Type_St* g_music_main_screen_info_st_ptr);


/*
* @brief  This API is used to get the volume inforamtion on the HMI screen.  
* @param    
* @return  boolean
* @invocation 
*/

void BLE_music_setting_screen(Cluster_Joystick_Info_En Music_Info);

/*
* @brief   This API is used to pass the music genre information to the UART  
* @param    
* @return  boolean
* @invocation 
*/

void BLE_setting_MetaData_transmission_Check(Cluster_Joystick_Info_En Meta_Data_Info);

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0
    REVISION DATE        : 09/10/2022
    CREATED / REVISED BY : JEEVAJOTHI(jeevajothi@niyatainfotech.com)
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! BLE_MUSIC_MODULE_H */
