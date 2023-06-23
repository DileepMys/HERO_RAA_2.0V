/* @file HMI */
#ifndef BUTTON_MGR_H
#define BUTTON_MGR_H

/*********************************************************************************************************************
* @author              Author : karthikeyan vijayan(v.karthikeyan@niyatainfotech.com)
*********************************************************************************************************************/

/*********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                       
**--------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : Button_Manager.h
*  Version                         : V1.0.1
*  Micros supported                : Micro Independent
*  Compilers supported             : J link
*  Platforms supported             : PLatform Independent
*  Description                     : This file contains the APIs for the button manager
*
*  @bug there is no bug                         
--------------------------------------------------------------------------------------------------------------------*/


/*********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                             
*********************************************************************************************************************/

#include "Button_Manager_Cfg.h"
/*********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                      
*********************************************************************************************************************/

#include "fsl_gpio.h"
/*********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                               
*********************************************************************************************************************/
/*********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                   
*********************************************************************************************************************/
/*********************************************************************************************************************
*                                          M A C R O   D E F I N I T I O N S                                          
*********************************************************************************************************************/

/* SWITCH SENSE STATE */
#define ACTIVE_LOW   0
#define ACTIVE_HIGH  1

/*********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                            
*********************************************************************************************************************/
/*
 * @brief: This ENUM is used to handle state of button press detect process
 * @Unit:  Nil
 * @Resolution: Nil
 * @Range: Nil
 * @Applicability: Nil
 */
 typedef enum
{
  CHECK_BUTTON_STATUS = 0u,
  SERVE_DEBOUNCE_TIME,
  BUTTON_PRESS_CONFIRMATION,
  CHECK_IS_SHORT_PRESS_TIME,
  CHECK_IS_LONG_PRESS_TIME,
  CHECK_CONTINUOUS_LONG_PRESS,
  CHECK_FOR_BUTTON_RELEASED,
  BUTTON_STUCK_STATE,
  BUTTON_MANAGER_MAINSTATES_MAX
}BM_StateMachine_State_Type_En;


/*
 * @brief: THIS STRUCTURE SHALL GIVE THE DETAILS AND EVENTS HANDLING ELEMTS
 * @Unit:  Nil
 * @Resolution: Nil 
 * @Range: Nil
 * @Applicability: Nil
 */

/* THIS STRUCTURE SHALL GIVE THE DETAILS AND EVENTS HANDLING ELEMTS */
typedef struct
{
  uint16_t EventCounter;
  uint8_t  ButtonState;
  uint16_t  Long_Press_Repeat_Counter;
}Button_Event_Handling_Type_St;

/*********************************************************************************************************************
*                                          P R I V A T E   D E C L A R A T I O N S                                    
*********************************************************************************************************************/
/*********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N S                     
*********************************************************************************************************************/
/** @defgroup  Button_Manager
 *  This is the Button_Manager module
 *  @{
 */
/** @defgroup  
 *  This is the function used to initialize the variables with default values
 *  @{
 */
void Button_Mgr_Init(void);

/** @defgroup  
 *  This is the function used to reset the initial values
 *  @{
 */
void Button_Mgr_DeInit(void);

/** @defgroup  
 *  This is the activate function used to initiate the peripherals
 *  @{
 */
void Button_Mgr_Activate(void);

/** @defgroup  
 *  This is the deactivate function used to de reset the peripheral
 *  @{
 */
void Button_Mgr_Deactivate(void);
/** @defgroup  
 *  This is the 
 *  @{
 */
void Button_Mgr_MainFunction(void);

uint8_t Get_Event(void);

void Clear_Event(void);

void Set_Event(uint8_t Event);
/**********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                          
**********************************************************************************************************************/

/*********************************************************************************************************************
 *                                                R E V I S I O N   H I S T O R Y
**********************************************************************************************************************/

/*********************************************************************************************************************
    REVISION NUMBER      : 1.0.0                                                                                      
    REVISION DATE        : 18/09/2021                                                                                 
    CREATED / REVISED BY : karthikeyan vijayan(v.karthikeyan@niyatainfotech.com)
    DESCRIPTION          : Initial Version                                                                            
----------------------------------------------------------------------------------------------------------------------
*********************************************************************************************************************/

#endif 


