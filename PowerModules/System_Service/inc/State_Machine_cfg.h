#ifndef STATE_MACHINE_CFG_H
#define STATE_MACHINE_CFG_H
/****************************************************************************************************************
 *@authorAuthor:          bakyaraj@niyatainfotechcom)                                                                      
 ***************************************************************************************************************/

/****************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N                                           
 *---------------------------------------------------------------------------------------------------------------------
 *  @brief                                                                                                             
 *                                                                                                                     
 *  File name                       : State_Machine_cfg.h                                                                                
 *  Version                         : V1.0.0                                                                                 
 *  Micros supported                : Micro Agnostic (Independant)                                                                               
 *  Compilers supported             : XXXX                                                                                
 *  Platforms supported             : XXXX                                                                                
 *  Description                     : This file contains Macros, Typdef and Function Declarations 
 *                                    for State machine cfg files                                                                                 
 *                                                                                                             
 *@bug                                                                                                               
 *-------------------------------------------------------------------------------------------------------------*/

/***************************************************************************************************************/


/***************************************************************************************************************
 *                                      I N C L U D E     F I L E S                              
 ***************************************************************************************************************/
#include "hal_stdtypes.h"
/****************************************************************************************************************
 *                                   M A C R O   D E F I N I T I O N S                                          
 ***************************************************************************************************************/

/*
* @breif : define variable used to get the input status
*/
#define SHUTDOWN_STATE      0xFFu


/*
* @breif : define the how many transition table max size
*/
#define MAX_TRANSITION       15u

/*
* @breif : define variable used to check contition in guard function
*/



/*
* @breif : function handles the state machine of the System
* @param : None
* @return: None
*/
typedef uint8_t (*state_mgr_func_ptr)(void);


/*
* @breif : define variable used to check contition in function
*/
#define STATE_MGR_TRUE 1
#define STATE_MGR_FALSE 0


/*
* @breif : define macro used on States
*/
#define BATT_CONNECT        0u
#define COLD_INIT           1u
#define INPUT_DEBOUNCE_MODE 2u
#define SLEEP_MODE          3u
#define LIMITED_MODE        4u
#define WAKEUP_INIT         5u
#define NORMAL_MODE         6u
#define ABNORMAL_MODE       7u


/***********************************************************************************************************
 *                                      F U N C T I O N S    D E C L A R A T I O N                             
 **************************************************************************************************************/

/*
* @breif : function handles read  the BatteryConnect Status
* @param : None
* @return: None
*/
uint8_t Read_BatteryConnect_Status(void);
/*
* @breif : function handles read  the Cold Init Complted Status 
* @param : None
* @return: None
*/
uint8_t Read_Cold_Init_Completed_Status(void);

/*
* @breif : function handles read  the WakeUp met and Cold init not Completed
* @param : None
* @return: None
*/
uint8_t Read_WakeUpMet_ColdInitCompleted_Status(void);

/*
* @breif : function handles read  the WakeUp met and Cold init not Completed
* @param : None
* @return: None
*/
uint8_t Read_WakeUpMet_ColdInitNotComplted_Status(void);

/*
* @breif : function handles read  the Limited Mode Condition Met status 
* @param : None
* @return: None
*/
uint8_t Read_Limited_Mode_Condition_Met_Status(void);


/*
* @breif : function handles read  the wakeup met and Abnormal Voltage Not Met status 
* @param : None
* @return: None
*/
uint8_t Read_WakeUpMet_Abonrmalcondtion_NotMet_Status(void);


/*
* @breif : function handles read  the wakeup met and Abnormal Voltage Not Met status 
* @param : None
* @return: None
*/
uint8_t Read_WakeUpMet_AbonrmalcondtionMet_Status(void);


/*
* @breif : function handles read  the Sleep Mode Condition Met status 
* @param : None
* @return: None
*/
uint8_t Read_Sleep_Mode_Condition_Met_Status(void);


/*
* @breif : function handles read  the EOL Exit Condition Met status 
* @param : None
* @return: None
*/
uint8_t Read_EOL_Exit_Condition_Met_Status(void);

/*
* @breif : function handles read  the WakeUp Init Completed status 
* @param : None
* @return: None
*/
uint8_t Read_WakeUp_Init_Completed_Status(void);

/*
* @breif : function handles read  the WakeUp Condition Met status 
* @param : None
* @return: None
*/
uint8_t Read_WakeUp_Condition_Met_Status(void);


/*
* @breif : function handles  Cold Init  
* @param : None
* @return: None
*/
extern uint8_t Set_Cold_Init_function(void);

/*
* @breif : function handles  De Init
* @param : None
* @return: None
*/
extern uint8_t Set_De_Init_function(void);

/*
* @breif : function declare Transition Input Debounce  
* @param : None
* @return: None
*/
uint8_t Set_Input_Debounce_function(void);

/*
* @breif : function declare Transition Sleep Mode 
* @param : None
* @return: None
*/
uint8_t Set_sleep_mode_function(void);

/*
* @breif : function declare Transition Limited Mode 
* @param : None
* @return: None
*/
uint8_t Set_LimitedMode_function(void);

/*
* @breif : function declare Transition Abnormal Mode
* @param : None
* @return: None
*/
uint8_t Set_AbNormalMode_function(void);

/*
* @breif : function declare Transition WakeUp Init Mode 
* @param : None
* @return: None
*/
uint8_t Set_WakeUp_InitMode_function(void);

/*
* @breif : function handles Transition Normal Mode
* @param : None
* @return: None
*/
uint8_t Set_NormalMode_function(void);


/****************************************************************************************************************
 *                                      V A R I A B L E S    D E C L A R A T I O N                             
***************************************************************************************************************/

/**************************************************************************************************************/
/*                                     S T R U C T U R E   D E C L A R A T I O N                              */
/**************************************************************************************************************/

/*declare the State manager Structure*/
typedef struct
    {
        uint8_t Current_Context;
        uint8_t Target_Context;
        state_mgr_func_ptr Guard_func;
        state_mgr_func_ptr Transition_Action_func;
    } state_mgr_struct_t;

extern state_mgr_struct_t State_machine_Table[MAX_TRANSITION];

/**********************************************************************************************************************
 *                                      S T A R T  O F   S O F T W A R E                                         
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/**********************************************************************************************************************
                                                R E V I S I O N   H I S T O R Y                                       *
 **********************************************************************************************************************

/**********************************************************************************************************************
     REVISION NUMBER      : V1.0.0                                                                                   
     REVISION DATE        : 17/4/2020                                                                               
     CREATED / REVISED BY : Bakyaraj (bakyaraj@niyatainfotech.com)                                        
     DESCRIPTION          : Initial version                                                                          
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/

#endif

