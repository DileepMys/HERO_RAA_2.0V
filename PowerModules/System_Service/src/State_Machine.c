#ifndef STATE_MACHINE_C
#define STATE_MACHINE_C
/***********************************************************************************************************************
 * @author              Author : Bakyaraj (bakyaraj@niyatainfotech.com)                                                                        
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N                                           
 *---------------------------------------------------------------------------------------------------------------------
 *  @brief                                                                                                             
 *                                                                                                                     
 *  File name                       : State_Machine.c                                                                                 
 *  Version                         : V1.0.0                                                                                 
 *  Micros supported                : Micro Agnostic (Independant)                                                                               
 *  Compilers supported             : XXXX                                                                                
 *  Platforms supported             : XXXX                                                                                
 *  Description                     : This file contains Macros, Typdef and Function Declarations for EcuM
 *                                    state machine files                                                                                 
 *                                                                                                                     
 *                                                                                                                     
 *  @bug                                                                                                               
 *---------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                               I N C L U D E  CONDITION BASED F I L E S                              
 ***********************************************************************************************************************/
#include "State_Machine.h"
#include "State_Machine_cfg.h"


/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S                                          
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                      F U N C T I O N S    D E C L A R A T I O N                             
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                       V A R I A B L E S    D E C L A R A T I O N                             
 ***********************************************************************************************************************/
/*
* @breif : declare variable used to get the current state status
*/
static uint8_t l_StateMgr_current_context_State_u8 = BATT_CONNECT ; 

/*
* @breif : declare variable used to get the max transition state size
*/
static uint8_t l_StateMgr_Transition_State_u8[MAX_TRANSITION];

/***********************************************************************************************************************
 *                                       S T R U C T U R E   D E C L A R A T I O N                             
 ***********************************************************************************************************************/



/**********************************************************************************************************************
 *                                      S T A R T  O F   S O F T W A R E                                         
 **********************************************************************************************************************/

/*
* @breif : function handles Init the state machine of the System
* @param : None
* @return: None
*/
void State_Machine_Init(void)
{
     uint8_t fl_statemgr_Transition_index_u8;;

     for(fl_statemgr_Transition_index_u8 = 0;
        fl_statemgr_Transition_index_u8 < (sizeof(l_StateMgr_Transition_State_u8)/sizeof(l_StateMgr_Transition_State_u8[0]));
        fl_statemgr_Transition_index_u8++)
        {
           
            l_StateMgr_current_context_State_u8 = BATT_CONNECT; 

        }


}
/*
* @breif : function handles main funtion of the state machine
* @param : None
* @return: None
*/
void State_Machine_Main_Function(void)
{

   uint8_t fl_get_num_of_allowed_context_u8;
   uint8_t fl_StateMgr_TableSize_u8;
   state_mgr_struct_t *fl_StateMgr_Table_ptr;

   /*Get State manger table Size*/
   fl_StateMgr_TableSize_u8 = sizeof(l_StateMgr_Transition_State_u8) / 
                               sizeof(l_StateMgr_Transition_State_u8[0]);

   fl_StateMgr_Table_ptr = &State_machine_Table[0];

   for(fl_get_num_of_allowed_context_u8 = 0;
       fl_get_num_of_allowed_context_u8 < fl_StateMgr_TableSize_u8;
       fl_get_num_of_allowed_context_u8++)
    {
       if ( (fl_StateMgr_Table_ptr->Current_Context == l_StateMgr_current_context_State_u8) &&
             (fl_StateMgr_Table_ptr->Guard_func() != STATE_MGR_FALSE) )
        {
        	   /* Execute the Transition function, upon State Transition  */
            fl_StateMgr_Table_ptr->Transition_Action_func();

            /* Modify the current Context  */
            l_StateMgr_current_context_State_u8 = fl_StateMgr_Table_ptr->Target_Context;

            /*Set the Sheduler context*/
            //Sched_Set_Context(l_StateMgr_current_context_State_u8);
            
            /* Stop the Traversing, since we just executed a transition */
            break;
        }

        fl_StateMgr_Table_ptr++;
        
    }
 }

/*
* @breif : function handle shutdown of the state machine
* @param : None
* @return: None
*/
void State_Machine_Shutdown(void)
{

   //  if((l_StateMgr_current_context_State_u8 == SCHED_BIT_1) || \
   //    (l_StateMgr_current_context_State_u8  == SCHED_BIT_2) || \
   //    (l_StateMgr_current_context_State_u8  == SCHED_BIT_3) || \
   //    (l_StateMgr_current_context_State_u8  == SCHED_BIT_4) || \
   //    (l_StateMgr_current_context_State_u8  == SCHED_BIT_5) || \
	//   (l_StateMgr_current_context_State_u8  == SCHED_BIT_6) || \
	//   (l_StateMgr_current_context_State_u8  == SCHED_BIT_7) || \
   //    (l_StateMgr_current_context_State_u8  == SCHED_BIT_8))
   //   {

        l_StateMgr_current_context_State_u8 = SHUTDOWN_STATE;
       
   //  }

}

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
