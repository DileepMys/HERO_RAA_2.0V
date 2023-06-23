/* @file HMI*/
#ifndef BUTTON_MGR_C
#define BUTTON_MGR_C

/*********************************************************************************************************************
* @author              Author : karthikeyan vijayan(v.karthikeyan@niyatainfotech.com)
*********************************************************************************************************************/

/*********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                       
**--------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : Button_Manager.c
*  Version                         : V1.0.2
*  Micros supported                : Micro Independent
*  Compilers supported             : J Link
*  Platforms supported             : Platform Independent
*  Description                     : This file contains the APIs for button manager
*
*  @bug there is no bug                        
--------------------------------------------------------------------------------------------------------------------*/


/*********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                             
*********************************************************************************************************************/
#include "Button_Manager.h"

/*********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                      
*********************************************************************************************************************/
/*********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                               
*********************************************************************************************************************/
/*********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                   
*********************************************************************************************************************/
/*********************************************************************************************************************
*                                          M A C R O   D E F I N I T I O N S                                          
*********************************************************************************************************************/

/*********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                            
*********************************************************************************************************************/

/*********************************************************************************************************************
 *                             S T A T I C    V A R I A B L E S  D E F I N A T I O N S
 *********************************************************************************************************************/
/*
 * @brief: BUTTON MANAGER EVENT HANDLING STRUCTURE - THIS SHALL BE USED TO HANDLE THE EVENT FOR THE NUMBER OF BUTTON CONFIGURED
 * @Unit:  Nil
 * @Resolution: Nil
 * @Range: Nil
 * @Applicability: Nil
 */
volatile Button_Event_Handling_Type_St Button_Event_Handling_St[MAX_BUTTON_LIST];
/*********************************************************************************************************************
*                                          P R I V A T E   D E C L A R A T I O N S                                    
*********************************************************************************************************************/
/**
  * @brief  This function shall be used to process precondition check.
  * @param  void
  * @retval uint8_t     1 - precondition ok,   0 - precondition not ok
  */
static uint8_t Button_Mgr_PreCondition_Process(void);

static void ButtonResetFn(uint8_t IDx);

inline static void Set_Button_Event_Fn(uint8_t Button_IDx, uint8_t Event_IDx);

uint8_t g_Crnt_Btn_Event_u8 = 0xFF;

uint8_t g_Button_Long_Press_Hold_u8;
/*********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N S                     
*********************************************************************************************************************/

/**
  * @brief  This function shall be used to Initialze the HMI functionality.
  * @param  void
  * @retval void
  */
void Button_Mgr_Init(void)
{
      /* LOCAL VARIABLE */
   uint8_t fl_Button_List_Idx_u8 = 0u;

   /* CHECK ALL THE BUTTONS FOR EVENT */
   for(fl_Button_List_Idx_u8 = 0u; fl_Button_List_Idx_u8 < MAX_BUTTON_LIST; fl_Button_List_Idx_u8++)
   {
      /* CLEAR THE COUNTER */
      Button_Event_Handling_St[fl_Button_List_Idx_u8].EventCounter = 0U;
      Button_Event_Handling_St[fl_Button_List_Idx_u8].ButtonState = CHECK_BUTTON_STATUS;
   }

   g_Button_Long_Press_Hold_u8 = 0u;
}

/**
  * @brief  This function shall be used to DeInitilize the HMI functionality.
  * @param  void
  * @retval void
  */
void Button_Mgr_DeInit(void)
{
    /* LOCAL VARIABLE */
   uint8_t fl_Button_List_Idx_u8 = 0u;
   
   /* CHECK ALL THE BUTTONS FOR EVENT */
   for(fl_Button_List_Idx_u8 = 0u; fl_Button_List_Idx_u8 < MAX_BUTTON_LIST; fl_Button_List_Idx_u8++)
   {
      ButtonResetFn(fl_Button_List_Idx_u8);
   }
}

/**
  * @brief  This function shall be used to manage the configured HMI events.
  * @param  void
  * @retval void
  */
void Button_Mgr_MainFunction(void)
{
   /* LOCAL VARIABLES */
   uint8_t fl_Button_List_Idx_u8 = 0u;
   uint8_t fl_Read_Button_Sts_u8 = 0u;
   uint8_t fl_PreCond_Status_u8 = 0u;

   /* pre condition status */
   fl_PreCond_Status_u8 = Button_Mgr_PreCondition_Process();

   if( fl_PreCond_Status_u8 == 1)
   {

      /* CHECK ALL THE BUTTONS FOR EVENT */
      for(fl_Button_List_Idx_u8 = 0u; fl_Button_List_Idx_u8 < MAX_BUTTON_LIST; fl_Button_List_Idx_u8++)
      {
         /* READ THE CURRENT SWITCH STATUS */
         fl_Read_Button_Sts_u8 = GPIO_PinRead(GPIO10,Button_Config_St[fl_Button_List_Idx_u8].Gpio_Pin);

         /* CHECK FOR THE CURRENT PIN STATE */
         switch(Button_Event_Handling_St[fl_Button_List_Idx_u8].ButtonState)
         {
            
            /* CHECK FOR STATE CASES */
            case CHECK_BUTTON_STATUS:
               
               /* CHECK FOR CONFIGURED EVENT OCCURED */
               if(fl_Read_Button_Sts_u8 == Button_Config_St[fl_Button_List_Idx_u8].ButtonSenseLogic)
               {
                  /* CHANGE THE STATE TO THE DEBOUNCE SERVE STATE */
                  Button_Event_Handling_St[fl_Button_List_Idx_u8].ButtonState = SERVE_DEBOUNCE_TIME;

               }
            break;

            case SERVE_DEBOUNCE_TIME:

               /* CHECK FOR CONFIGURED EVENT OCCURED */
               if(fl_Read_Button_Sts_u8 == Button_Config_St[fl_Button_List_Idx_u8].ButtonSenseLogic)
               {
                  /* INCREMENT THE COUNTER AND WAIT FOR DEBOUNCE TO BE EXPIRE */
                  Button_Event_Handling_St[fl_Button_List_Idx_u8].EventCounter += BUTTON_MANAGER_TASK_RATE;

                  /* CHECK FOR DEBOUNCE COUNTER EXPIRED */
                  if(Button_Event_Handling_St[fl_Button_List_Idx_u8].EventCounter >= BUTTON_MANAGER_DEBOUNCE_TIMER)
                  {
                     /* CHANGE THE STATE TO CHECK THE PIN RELEASED/OTHER EVENT */
                     Button_Event_Handling_St[fl_Button_List_Idx_u8].ButtonState = BUTTON_PRESS_CONFIRMATION;
                  }
               }
               else
               {
                  /* CHANGE STATE TO BUTTON RELEASED*/
                  Button_Event_Handling_St[fl_Button_List_Idx_u8].ButtonState = CHECK_FOR_BUTTON_RELEASED;
               }
            break;
   
            case BUTTON_PRESS_CONFIRMATION:

               /* CHECK FOR CONFIGURED EVENT OCCURED */
               if(fl_Read_Button_Sts_u8 == Button_Config_St[fl_Button_List_Idx_u8].ButtonSenseLogic)
               {
                  /* INCREMENT THE COUNTER AND WAIT FOR DEBOUNCE TO BE EXPIRE */
                  Button_Event_Handling_St[fl_Button_List_Idx_u8].EventCounter += BUTTON_MANAGER_TASK_RATE;

                  /* button pressed for desired amount of time */
                  if(Button_Event_Handling_St[fl_Button_List_Idx_u8].EventCounter >= BUTTON_MANAGER_SHORT_PRESS_TIMER)
                  {
                     /* CHANGE THE STATE TO CHECK THE PIN RELEASED/OTHER EVENT */
                     Button_Event_Handling_St[fl_Button_List_Idx_u8].ButtonState = CHECK_IS_SHORT_PRESS_TIME;
                  }   
               }
               else
               {
                  /* CHANGE STATE TO BUTTON RELEASED*/
                  Button_Event_Handling_St[fl_Button_List_Idx_u8].ButtonState = CHECK_FOR_BUTTON_RELEASED;
               }
				break;

            case CHECK_IS_SHORT_PRESS_TIME:

               /* CHECK FOR CONFIGURED EVENT OCCURED */
               if(fl_Read_Button_Sts_u8 == Button_Config_St[fl_Button_List_Idx_u8].ButtonSenseLogic)
               {
                  /* INCREMENT THE COUNTER AND WAIT FOR DEBOUNCE TO BE EXPIRE */
                  Button_Event_Handling_St[fl_Button_List_Idx_u8].EventCounter += BUTTON_MANAGER_TASK_RATE;

                  /* button pressed for desired amount of time */
                  if(Button_Event_Handling_St[fl_Button_List_Idx_u8].EventCounter >= BUTTON_MANAGER_LONGPRESS_TIMER)
                  {

                     /* CHANGE THE STATE TO CHECK THE PIN RELEASED/OTHER EVENT */
                     Button_Event_Handling_St[fl_Button_List_Idx_u8].ButtonState = CHECK_IS_LONG_PRESS_TIME;
                  
                  }

               }
               else
               {
                  /* CHECK CALL FUNCTION CONFIGURED */
               if(Button_Config_St[fl_Button_List_Idx_u8].Button_EventClBack != 0)
                  {
                     /* BUTTON PRESS APPLICATION CALL BACK */
                     Button_Config_St[fl_Button_List_Idx_u8].Button_EventClBack(1);
                  } 

                  /* SET THE BUTTON EVENT */
                  Set_Button_Event_Fn(fl_Button_List_Idx_u8, 1);

                  /* CHANGE STATE TO BUTTON RELEASED*/
                  Button_Event_Handling_St[fl_Button_List_Idx_u8].ButtonState = CHECK_FOR_BUTTON_RELEASED;

               }

            break;

            case CHECK_IS_LONG_PRESS_TIME:
               /* CHECK CALL FUNCTION CONFIGURED */
               if(Button_Config_St[fl_Button_List_Idx_u8].Button_EventClBack != 0)
               {
                  /* BUTTON PRESS APPLICATION CALL BACK */
                  Button_Config_St[fl_Button_List_Idx_u8].Button_EventClBack(2);
               }

               /* SET HMI EVENT */
               Set_Button_Event_Fn(fl_Button_List_Idx_u8, 2);

               /* CHECK FOR CONFIGURED EVENT OCCURED */
               if(fl_Read_Button_Sts_u8 == Button_Config_St[fl_Button_List_Idx_u8].ButtonSenseLogic)
               {
                  /* CHANGE THE STATE TO CHECK CONTINUOUS LONG PRESS */
                  Button_Event_Handling_St[fl_Button_List_Idx_u8].ButtonState = CHECK_CONTINUOUS_LONG_PRESS;

                  /* INITIALIZE CONTINUOUS LOGN PRESS COUNTER */
                  Button_Event_Handling_St[fl_Button_List_Idx_u8].Long_Press_Repeat_Counter = 0;
               }
               else
               {
                  /* CHANGE STATE TO BUTTON RELEASED*/
                  Button_Event_Handling_St[fl_Button_List_Idx_u8].ButtonState = CHECK_FOR_BUTTON_RELEASED;
               }
            break;

            case CHECK_CONTINUOUS_LONG_PRESS:

               /* CHECK THE BUTTON RELEASED */
               if(fl_Read_Button_Sts_u8 == Button_Config_St[fl_Button_List_Idx_u8].ButtonSenseLogic)
               {
                  /* INCREMENT LONG PRESS REPEAT TIMER */
                  Button_Event_Handling_St[fl_Button_List_Idx_u8].Long_Press_Repeat_Counter = Button_Event_Handling_St[fl_Button_List_Idx_u8].Long_Press_Repeat_Counter + BUTTON_MANAGER_TASK_RATE;

                  /* CHECK COUNTER REACHES LONG PRESS REPEAT TIMER*/
                  if(Button_Event_Handling_St[fl_Button_List_Idx_u8].Long_Press_Repeat_Counter >= BUTTON_MANAGER_LONG_PRESS_REPEAT_TIMER)
                  {
                     /* SET HMI EVENT */
                     Set_Button_Event_Fn(fl_Button_List_Idx_u8, 3);

                     /* INITIALIZE CONTINUOUS LONG PRESS TIMER*/
                     Button_Event_Handling_St[fl_Button_List_Idx_u8].Long_Press_Repeat_Counter = Button_Event_Handling_St[fl_Button_List_Idx_u8].Long_Press_Repeat_Counter 
                                                                                                % BUTTON_MANAGER_LONG_PRESS_REPEAT_TIMER;
                     
                  }

               }
               else
               {
                  /* CHANGE STATE TO BUTTON RELEASED*/
                  Button_Event_Handling_St[fl_Button_List_Idx_u8].ButtonState = CHECK_FOR_BUTTON_RELEASED;
               }   

            break;

				case CHECK_FOR_BUTTON_RELEASED:
					/* CHECK THE BUTTON RELEASED */
					if(fl_Read_Button_Sts_u8 != Button_Config_St[fl_Button_List_Idx_u8].ButtonSenseLogic)
					{
						/* RESET BUTTON STATE */
						ButtonResetFn(fl_Button_List_Idx_u8);
					}
					else
					{
						
						/* INCREMENT THE COUNTER AND WAIT FOR DEBOUNCE TO BE EXPIRE */
						Button_Event_Handling_St[fl_Button_List_Idx_u8].EventCounter += BUTTON_MANAGER_TASK_RATE;
						
						if( Button_Event_Handling_St[fl_Button_List_Idx_u8].EventCounter > BUTTON_MANAGER_STRUCK_TIMER)
						{
							/* CHANGE THE STATE TO CHECK THE NEXT STATE */
							Button_Event_Handling_St[fl_Button_List_Idx_u8].ButtonState = BUTTON_STUCK_STATE;
						}
					}
				break;

				case BUTTON_STUCK_STATE:
					/* CHECK FOR CONFIGURED EVENT OCCURED */
					if(fl_Read_Button_Sts_u8 != Button_Config_St[fl_Button_List_Idx_u8].ButtonSenseLogic)
					{
						/* RESET BUTTON STATE */
						ButtonResetFn(fl_Button_List_Idx_u8);
					}
					else
					{
						/* Button stucked DTC Log */
					}
				break;

				default:
				break;
         }
      }
   }
   else
   {
      /* clear precondition flag */
      fl_PreCond_Status_u8 = 0;
   }
}

/**
  * @brief  This function shall be used to process precondition check.
  * @param  void
  * @retval uint8_t     1 - precondition ok,   0 - precondition not ok
  */
static uint8_t Button_Mgr_PreCondition_Process(void)
{
   /* Local variable */
   uint8_t fl_Ign_Status_u8 = 1;
   uint8_t fl_LVSD_Flag_u8 = 0;
   uint8_t fl_HVDS_Flag_u8 = 0;
   uint8_t fl_preCond_result_u8 = 0;

   /* read iginition status */
   fl_Ign_Status_u8 = BUTTON_MGR_READ_IGN_STATUS;

   /* read low voltage status flag */
   fl_LVSD_Flag_u8 = BUTTON_MGR_READ_LVDS_STATUS;

   /* read High voltage status flag */
   fl_HVDS_Flag_u8 = BUTTON_MGR_READ_HVDS_STATUS;

   /* Pre condition statisfied */
   if( (fl_Ign_Status_u8 == IGN_ON) && (fl_LVSD_Flag_u8 == 1) && (fl_HVDS_Flag_u8 == 1))
   {
      fl_preCond_result_u8 = 1;
   }
   else
   {
      fl_preCond_result_u8 = 0;
   }

   return (fl_preCond_result_u8);
}


static void ButtonResetFn(uint8_t IDx)
{
	/* CLEAR THE DEBOUNCE TIMER */
	Button_Event_Handling_St[IDx].EventCounter = 0U;

	/* CHANGE THE STATE TO CHECK THE PIN RELEASED/OTHER EVENT */
	Button_Event_Handling_St[IDx].ButtonState = CHECK_BUTTON_STATUS;

	/* clear long press and hold variable */
	g_Button_Long_Press_Hold_u8 = 0;

   /* Clear repeat counter*/
   Button_Event_Handling_St[IDx].Long_Press_Repeat_Counter = 0;
}

inline static void Set_Button_Event_Fn(uint8_t Button_IDx, uint8_t Event_IDx)
{
	/* CHECK FOR THE CURRENT BUTTON ID */
	if(Event_IDx == 1)
	{
		/* Short press event triggered */
		g_Crnt_Btn_Event_u8 = Button_IDx + 1;
	}
	else if(Event_IDx == 2)
	{
		/*Long press event triggered */
		g_Crnt_Btn_Event_u8 = Button_IDx + 5;
	}
	else if(Event_IDx == 3)
	{
      /* CONTINUOUS LONG PRESS EVENT*/
		g_Crnt_Btn_Event_u8 = Button_IDx + 9;
	}
   else
   {
      /*do nothing*/
   }
}

uint8_t Get_Event(void)
{
	return g_Crnt_Btn_Event_u8;
}

void Clear_Event(void)
{
	g_Crnt_Btn_Event_u8 = 0xFF;
}

void Set_Event(uint8_t Event)
{
	g_Crnt_Btn_Event_u8 = Event;
}
/**********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                          
**********************************************************************************************************************/

/*********************************************************************************************************************
 *                                                R E V I S I O N   H I S T O R Y
**********************************************************************************************************************/ 

/*********************************************************************************************************************
    REVISION NUMBER      : 1.0.2                                                                                      
    REVISION DATE        : 11/07/2022                                                                                 
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)
    DESCRIPTION          : Continuous Long press event added in state machine.                                                                            
----------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : 1.0.1                                                                                      
    REVISION DATE        : 04/13/2022                                                                                 
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)
    DESCRIPTION          : Press time elasped state added in state machine, configurable press time implementated                                                                            
----------------------------------------------------------------------------------------------------------------------

    REVISION NUMBER      : 1.0.0                                                                                      
    REVISION DATE        : 18/09/2021                                                                                 
    CREATED / REVISED BY : karthikeyan vijayan(v.karthikeyan@niyatainfotech.com)
    DESCRIPTION          : Initial Version                                                                            
----------------------------------------------------------------------------------------------------------------------
*********************************************************************************************************************/
/** @} */ //  
/** @} */ // HMI
#endif /* ! HMI_C */


