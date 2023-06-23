/* @file HMI */
#ifndef BUTTON_MGR_CFG_H
#define BUTTON_MGR_CFG_H

/*********************************************************************************************************************
* @author              Author : Karthikeyan vijayan(v.karthikeyan@niyatainfotech.com))
*********************************************************************************************************************/

/*********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                       
**--------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : Button_Manager_Cfg.h
*  Version                         : V1.0.1
*  Micros supported                : Micro Independent
*  Compilers supported             : J link
*  Platforms supported             : Platform Independent
*  Description                     : This file contains the APIs for the button manager
*
*  @bug there is no bug                        
--------------------------------------------------------------------------------------------------------------------*/


/*********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                             
*********************************************************************************************************************/
#include "Button_Manager.h"
#include "Swc_System_Service.h"
/*********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                      
*********************************************************************************************************************/
#include "Cmp_Init.h"
/*********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                               
*********************************************************************************************************************/
/*********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                   
*********************************************************************************************************************/

/*********************************************************************************************************************
*                                          M A C R O   D E F I N I T I O N S                                          
*********************************************************************************************************************/

/* CONFIGURATION PARAMETER */

/*
* @brief: This macro is used to configure task rate configured for main function
* @Unit:  ms
* @Resolution: na
* @Range: na
* @Applicability: na 
* @Note:nil
*/
#define BUTTON_MANAGER_TASK_RATE                     8

/*
* @brief: This macro is used to configure debounce time to detect button press event 
* @Unit:  ms
* @Resolution: na
* @Range: na
* @Applicability: na 
* @Note:nil
*/
#define BUTTON_MANAGER_DEBOUNCE_TIMER                 64


/*
* @brief: This macro is used to configure debounce time to detect button press event 
* @Unit:  ms
* @Resolution: na
* @Range: na
* @Applicability: na
* @Note:nil
*/
#define BUTTON_MANAGER_SHORT_PRESS_TIMER                 200

/*
* @brief: This macro is used to configure debounce time to detect button press event 
* @Unit:  ms
* @Resolution: na
* @Range: na
* @Applicability: na 
* @Note: nil
*/
#define BUTTON_MANAGER_LONGPRESS_TIMER                  2000


/*
* @brief: This macro is used to configure debounce time to detect button press event 
* @Unit:  ms
* @Resolution: na
* @Range: na
* @Applicability: na
* @Note:nil
*/
#define BUTTON_MANAGER_STRUCK_TIMER                  120000

/*
* @brief: This macro is used to configure timer value to detect long press repeat event
* @Unit:  ms
* @Resolution: 1ms
* @Range: 0 to 65535
* @Applicability: In Date and Time setting, after long press, for every 250ms of continuous long press The value shall be incremented/decremented 
* @Note:nil
*/
#define BUTTON_MANAGER_LONG_PRESS_REPEAT_TIMER                  250

/*
* @brief: This macro is used to configure normal pressing time of button
* @Unit:  ms
* @Resolution: na
* @Range: na
* @Applicability: na 
* @Note:nil
*/
#define BUTTON_MANAGER_NORMALPRESS_TIMER        200
/*
* @brief: This macro is used to configure function to read ignition status
* @Unit:  ms
* @Resolution: na
* @Range: na
* @Applicability: na
* @Note:nil
*/
#define BUTTON_MGR_READ_IGN_STATUS        Sys_Service_Get_Ignition_State()
/*
* @brief: This macro is used to configure function to read low voltage status flag
* @Unit:  ms
* @Resolution: na
* @Range: na
* @Applicability: na 
* @Note: nil
*/
#define BUTTON_MGR_READ_LVDS_STATUS  Sys_Service_Get_Low_Voltage_State()
/*
* @brief: This macro is used to configure function to read high voltage status flag
* @Unit:  ms
* @Resolution: na
* @Range: na
* @Applicability: na 
* @Note:nil
*/
#define BUTTON_MGR_READ_HVDS_STATUS   Sys_Service_Get_High_Voltage_State()
/*
* @brief: This function pointer is used to configure call back to be called when corresponding button is pressed
* @Unit:  na
* @Resolution:na 
* @Range: na 
* @Applicability: na
* @Note: nil
*/
typedef void (*HMI_EventClBackType)(uint8_t);

/* THIS ENUM SHALL GIVE THE INDEX FOR THE NUMBER OF BUTTONS TO BE MONITORED */
typedef enum
{
	HANDLER_BAR_SET_BUTTON = 0,
	HANDLER_BAR_RETURN_BUTTON,
	HANDLER_BAR_UP_BUTTON,
	HANDLER_BAR_DOWN_BUTTON,
	MAX_BUTTON_LIST
}BM_List_Index_Type_En;

/* THIS ENUM SHALL GIVE THE INDEX FOR THE TRIP BUTTONS */
typedef enum
{
  EEPROM_RESET = 0u,
  TRIPA_RESET,
  TRIPB_RESET,
  MAXIMUM_HMI_EVENTS
}Button_Event_List_en;

/* This enum shall give the details about how long the button has been pressed */
typedef enum
{
  BUTTON_NORMAL_PRESS = BUTTON_MANAGER_NORMALPRESS_TIMER,
  BUTTON_1SEC_PRESS = 1000,
  BUTTON_2SEC_PRESS = 2000,
  BUTTON_5SEC_PRESS = 5000,
  BUTTON_10SEC_PRESS = 10000,
  BUTTON_MAXIMUM_EVENT
}Butten_Press_Type_List_En;

/* THIS STRUCTURE SHALL GIVE THE LIST OF INPUT SWITCHES */
typedef struct
{
  BM_List_Index_Type_En BTN_EVENT_EN;
  uint8_t Gpio_Pin;
  uint8_t ButtonSenseLogic;
  Butten_Press_Type_List_En  Press_Type_En;
  HMI_EventClBackType Button_EventClBack; 
}Button_Config_Type_St;

/*
 * @brief: This variable is used to  congifure the buttons
 * @Unit:  na
 * @Resolution: na
 * @Range: na
 * @Applicability: nil
 */
extern const Button_Config_Type_St Button_Config_St[MAX_BUTTON_LIST];

/**********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                          
**********************************************************************************************************************/

/*********************************************************************************************************************
 *                                                R E V I S I O N   H I S T O R Y
**********************************************************************************************************************/
/*********************************************************************************************************************
    REVISION NUMBER      : 1.0.1                                                                                      
    REVISION DATE        : 04/13/2022                                                                                 
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)
    DESCRIPTION          : button list enum changed                                                                            
----------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : 1.0.0                                                                                      
    REVISION DATE        : 05/09/2018                                                                                 
    CREATED / REVISED BY : v.karthikeyan(v.karthikeyan@niyatainfotech.com)
    DESCRIPTION          : Initial Version                                                                            
----------------------------------------------------------------------------------------------------------------------
*********************************************************************************************************************/
#endif /* ! HMI_CFG_H */

