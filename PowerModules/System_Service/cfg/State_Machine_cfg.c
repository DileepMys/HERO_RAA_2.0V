#ifndef STATE_MACHINE_CFG_C
#define STATE_MACHINE_CFG_C
/***********************************************************************************************************************
 * @author              Author : Bakyaraj (bakyaraj@niyatainfotech.com)                                                                        
 ***********************************************************************************************************************/

/***********************************************************************************************************************
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
 *                                                                                                                     
 *  @bug                                                                                                               
 *---------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                      I N C L U D E     F I L E S                              
 ***********************************************************************************************************************/

#include "State_Machine_cfg.h"
#include "Dio_Handler.h"
#include "Cmp_Init.h"
#include "swc_system_service.h"

/************************************************************************************************************************
 *                                      M A C R O   D E F I N I T I O N S                                          
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                      F U N C T I O N S    D E C L A R A T I O N                             
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                      V A R I A B L E S    D E C L A R A T I O N                             
 ***********************************************************************************************************************/

uint8_t g_Battary_Connect_u8 = 0u ;

static uint8_t init_start = 2;

_Bool TT_IGN_OFF;
_Bool IGN_OFF_TT;

/***********************************************************************************************************************
 *                                      S T R U C T U R E   D E C L A R A T I O N                             
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 *                                      S T A R T  O F   S O F T W A R E                                         
 **********************************************************************************************************************/

/*
* @breif : function handles the state machine of the System
* @param : None
* @return: None
*/

state_mgr_struct_t State_machine_Table[MAX_TRANSITION] =
{

 /* Current Context        Target Context           Guard_function                                  Transition Action Function    */
 {  BATT_CONNECT,          COLD_INIT,		        &Read_BatteryConnect_Status,                    &Set_Cold_Init_function	            },
 {  COLD_INIT,             INPUT_DEBOUNCE_MODE,		&Read_Cold_Init_Completed_Status,               &Set_Input_Debounce_function	    },
 {  INPUT_DEBOUNCE_MODE,   NORMAL_MODE,		        &Read_WakeUpMet_ColdInitCompleted_Status,       &Set_NormalMode_function	        },
 { 	INPUT_DEBOUNCE_MODE,   WAKEUP_INIT,		        &Read_WakeUpMet_ColdInitNotComplted_Status,     &Set_WakeUp_InitMode_function	 	},
 { 	INPUT_DEBOUNCE_MODE,   LIMITED_MODE,	        &Read_Limited_Mode_Condition_Met_Status,        &Set_LimitedMode_function	 	    },
 { 	LIMITED_MODE,          NORMAL_MODE,			    &Read_WakeUpMet_Abonrmalcondtion_NotMet_Status, &Set_NormalMode_function	 		},
 { 	LIMITED_MODE,          ABNORMAL_MODE,			&Read_WakeUpMet_AbonrmalcondtionMet_Status,     &Set_AbNormalMode_function	 	    },
 {  LIMITED_MODE,          SLEEP_MODE,		        &Read_Sleep_Mode_Condition_Met_Status,          &Set_sleep_mode_function	        },
 { 	ABNORMAL_MODE,         LIMITED_MODE,		    &Read_Limited_Mode_Condition_Met_Status,        &Set_LimitedMode_function	 		},
 { 	ABNORMAL_MODE,         NORMAL_MODE,		        &Read_WakeUpMet_Abonrmalcondtion_NotMet_Status, &Set_NormalMode_function	 		},
 { 	NORMAL_MODE,           LIMITED_MODE,		    &Read_Limited_Mode_Condition_Met_Status,        &Set_LimitedMode_function	 		}, 
 { 	NORMAL_MODE,           ABNORMAL_MODE,		    &Read_WakeUpMet_AbonrmalcondtionMet_Status,     &Set_AbNormalMode_function	 		}, 
 {  NORMAL_MODE,           COLD_INIT,		        &Read_EOL_Exit_Condition_Met_Status,            &Set_De_Init_function	 		    },
 { 	WAKEUP_INIT,           NORMAL_MODE,		        &Read_WakeUp_Init_Completed_Status,             &Set_NormalMode_function	 	    }, 
 {  SLEEP_MODE,            INPUT_DEBOUNCE_MODE,		&Read_WakeUp_Condition_Met_Status,              &Set_Input_Debounce_function	    },  
   
};





#define SET_WAKEUP           1u
#define NO_WAKEUP            0u
#define IMO_TT_ON            1u
#define IMO_TT_OFF           0u

/*
* @breif : define variable used to get the input status
*/
#define IGN_Status         0u
#define WAKEUP_Status      0U
#define IMO_TT_ON_Status   0U

/*
* @breif : function handles read  the BatteryConnect Status 
* @param : None
* @return: None
*/
uint8_t Read_BatteryConnect_Status(void)
{
    uint8_t status = STATE_MGR_FALSE;
    uint8_t l_IgnitionStatus_u8 = IGN_OFF;


    l_IgnitionStatus_u8 = Dio_Handler_Read_Pin_Status();

    /*Based on system state need to implementation*/
    if((l_IgnitionStatus_u8 == IGN_ON) && (g_Battary_Connect_u8 == 0u))
    {

        g_Battary_Connect_u8 = 1u;      

        status = STATE_MGR_TRUE;


    }

    return status;    
}

/*
* @breif : function handles read  the Cold Init Complted Status 
* @param : None
* @return: None
*/
uint8_t Read_Cold_Init_Completed_Status(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/

    return status;    
}

/*
* @breif : function handles read  the WakeUp met and Cold init not Completed
* @param : None
* @return: None
*/
uint8_t Read_WakeUpMet_ColdInitCompleted_Status(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
   

    return status;    
}

/*
* @breif : function handles read  the WakeUp met and Cold init not Completed
* @param : None
* @return: None
*/
uint8_t Read_WakeUpMet_ColdInitNotComplted_Status(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
   

    return status;    
}

/*
* @breif : function handles read  the Limited Mode Condition Met status 
* @param : None
* @return: None
*/
uint8_t Read_Limited_Mode_Condition_Met_Status(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
    
   
    return status;    
}


/*
* @breif : function handles read  the wakeup met and Abnormal Voltage Not Met status 
* @param : None
* @return: None
*/
uint8_t Read_WakeUpMet_Abonrmalcondtion_NotMet_Status(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
    
   
    return status;    
}


/*
* @breif : function handles read  the wakeup met and Abnormal Voltage Not Met status 
* @param : None
* @return: None
*/
uint8_t Read_WakeUpMet_AbonrmalcondtionMet_Status(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
    
   
    return status;    
}



/*
* @breif : function handles read  the Sleep Mode Condition Met status 
* @param : None
* @return: None
*/
uint8_t Read_Sleep_Mode_Condition_Met_Status(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
    
   
    return status;    
}


/*
* @breif : function handles read  the EOL Exit Condition Met status 
* @param : None
* @return: None
*/
uint8_t Read_EOL_Exit_Condition_Met_Status(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
    
   
    return status;    
}


/*
* @breif : function handles read  the WakeUp Init Completed status 
* @param : None
* @return: None
*/
uint8_t Read_WakeUp_Init_Completed_Status(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
    
   
    return status;    
}

/*
* @breif : function handles read  the WakeUp Condition Met status 
* @param : None
* @return: None
*/
uint8_t Read_WakeUp_Condition_Met_Status(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
    
   
    return status;    
}


/*
* @breif : function handles  Cold Init  
* @param : None
* @return: None
*/
uint8_t Set_Cold_Init_function(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
  
   
    return status;    
}


/*
* @breif : function handles  De Init
* @param : None
* @return: None
*/
uint8_t Set_De_Init_function(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
    
   
    return status;    
}

/*
* @breif : function declare Transition Input Debounce  
* @param : None
* @return: None
*/
uint8_t Set_Input_Debounce_function(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
    
   
    return status;    
}

/*
* @breif : function declare Transition Sleep Mode 
* @param : None
* @return: None
*/
uint8_t Set_sleep_mode_function(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
    
   
    return status;    
}

/*
* @breif : function declare Transition Limited Mode 
* @param : None
* @return: None
*/
uint8_t Set_LimitedMode_function(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
    
   
    return status;    
}

/*
* @breif : function declare Transition Abnormal Mode
* @param : None
* @return: None
*/
uint8_t Set_AbNormalMode_function(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
    
   
    return status;    
}

/*
* @breif : function declare Transition WakeUp Init Mode 
* @param : None
* @return: None
*/
uint8_t Set_WakeUp_InitMode_function(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
    
   
    return status;    
}

/*
* @breif : function handles Transition Normal Mode
* @param : None
* @return: None
*/
uint8_t Set_NormalMode_function(void)
{
    uint8_t status = STATE_MGR_FALSE;

    /*Based on system state need to implementation*/
    
   
    return status;    
}

/**********************************************************************************************************************
 *                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

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




