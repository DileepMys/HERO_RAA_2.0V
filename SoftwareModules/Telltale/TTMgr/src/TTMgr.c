/* @file TTMGR_C */
#ifndef TTMGR_C
#define TTMGR_C
/*********************************************************************************************************************
*    DISCLAIMER
*    Copyright © , 2021 Niyata Infotech Pvt. Ltd. All rights reserved.                                           
*********************************************************************************************************************/

/*********************************************************************************************************************
* @author              Author : Maheswari R (maheswari@niyatainfotech.com)
*********************************************************************************************************************/

/*********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                       
**--------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : TTMgr.c
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent
*  Description                     : This file contains the Implementation of Tell-Tale Manager  
*  @bug                         
--------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/********************************************************************************************************************/

/*********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                             
*********************************************************************************************************************/
#include"TTMgr.h"
#include "pin_mux.h"
#include "cmp_Tasks.h"
#include "Swc_System_Service.h"
#include "lvgl_app.h"
/*********************************************************************************************************************
*                                             M A C R O   D E F I N I T I O N S                                          
*********************************************************************************************************************/
/*
 * @brief: this configuration shall configure the Tell-Tale Mode
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
typedef enum
{
	TT_DRIVE_TYPE_GPIO =0u,
	TT_DRIVE_TYPE_TFT  =1u
}TT_DRIVE_TYPE_En;


/*
 * @brief: This macro is used to define the state of Tell-Tale self check start
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
#define TT_SELFCHECK_START 		 1u

/*
 * @brief: This macro is used to define the  state of Tell-Tale self check delay
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
#define TT_SELFCHECK_INPROGRESS	 2u

/*
 * @brief: This macro is used to define  state of Tell-Tale normal(After execution of self check state)
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
#define TT_NORMAL 		         3u

/**
* @brief This macro is used to define  the Activate
*/
/*
 * @brief: This macro is used to define  the Activate
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
#define TT_ACTIVATE              1u

/*
 * @brief: This macro is used to define  the Deactivate
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
#define TT_DEACTIVATE            0u

/*
 * @brief: This macro is used to define  the milliseconds
 * @Unit:  milliseconds
 * @Resolution: 1
 * @Range: 0 to 65535
 * @Applicability: YES
 */
#define TT_MILLISECONDS        1000u

/**
* @brief This macro is used to define  the percentage
*/
/*
 * @brief: This macro is used to define  the percentage
 * @Unit: N/A
 * @Resolution: 1
 * @Range: 0 to 255
 * @Applicability: YES
 */
#define TT_PERCENTAGE          100u

/**
* @brief This macro is used to define  the Safety Tell-Tale
*/
/*
 * @brief: This macro is used to define  the Safety Tell-Tale
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
#define TT_SAFETY                1u



/*********************************************************************************************************************
*                                          G L O B A L   V A R I A B L E    D E C L A R A T I O N S                                    
*********************************************************************************************************************/
/*
* @brief: This variable is used to hold the current state of Tell-Tale Manager
  @Unit:  N/A
  @Resolution: N/A
  @Range: TT_SELFCHECK_START,TT_SELFCHECK_INPROGRESS,TT_NORMAL
  @Applicability: YES
*/
static uint8_t g_TT_Mgr_State_u8;

/*
* @brief: This variable is used to define the Active function flag
  @Unit:  N/A
  @Resolution: N/A
  @Range: Activate or Deactivate 
  @Applicability: YES
*/
static uint8_t g_TT_Mgr_ActiveFlag_u8;

/*
* @brief: This variable is used to hold the ON Count Value of Flash Functionality Tell-Tale
  @Unit:  N/A
  @Resolution: 1
  @Range: 0 to 255
  @Applicability: YES
*/
static uint8_t g_TT_Flash_ONCount_u8[TT_MAX];

/*
* @brief: This variable is used to hold the OFF Count Value of Flash Functionality Tell-Tale
  @Unit:  N/A
  @Resolution: 1
  @Range: 0 to 255
  @Applicability: YES
*/
static uint8_t g_TT_Flash_OFFCount_u8[TT_MAX];

/*
* @brief: This variable is used to store the Demanded status of Tell-Tale
  @Unit:  N/A
  @Resolution: N/A
  @Range: ON,OFF and FLASH
  @Applicability: YES
*/
static uint8_t g_TT_Demanded_Status_u8[TT_MAX];

/*
* @brief: This variable is used to store the Tell-Tale status
  @Unit:  N/A
  @Resolution: N/A
  @Range: ON,OFF and FLASH
  @Applicability: YES
*/
static uint8_t g_TT_Status_u8[TT_MAX];
/*
* @brief: This variable is used to store previous the Tell-Tale status
  @Unit:  N/A
  @Resolution: N/A
  @Range: ON,OFF and FLASH
  @Applicability: YES
*/
static uint8_t g_TT_Prev_Status_u8[TT_MAX];
/*
* @brief: This variable is used to store previous the Tell-Tale status
  @Unit:  N/A
  @Resolution: N/A
  @Range: ON,OFF and FLASH
  @Applicability: YES
*/
static bool g_TT_Sync_Status[TT_MAX];

/*
* @brief: This variable is used to store the self check count value of Tell-Tales
  @Unit:  N/A
  @Resolution:1
  @Range: 0 to 255
  @Applicability: YES
*/
static uint8_t g_TT_Mgr_SelfCheckCount_u8=0; 

/*
* @brief: This variable is used to store the current status of Tell-Tale for Diagnostic
  @Unit:  N/A
  @Resolution: N/A
  @Range: ON,OFF and FLASH
  @Applicability: YES
*/
static uint8_t g_TT_Current_Status_u8[TT_MAX];

/*
* @brief: This variable is used to store ON timer value of Tell-Tale Flash Functionality
  @Unit:  milliseconds
  @Resolution: 1
  @Range: 0 to 255
  @Applicability: YES
*/
static uint8_t g_TT_Flash_TimerValue_u8[TT_MAX];

/*
* @brief: This variable is used to store OFF timer value of Tell-Tale Flash Functionality
  @Unit:  milliseconds
  @Resolution: 1
  @Range: 0 to 255
  @Applicability: YES
*/
static uint8_t g_TT_Flash_OFFTimerValue_u8[TT_MAX];

/*
* @brief: This function is used to find the Flash Tell-Tale ON status 
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
static bool g_TT_Flash_ON_InProgress;

/*
* @brief: This function is used to find the Flash Tell-Tale OFF status 
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
static bool g_TT_Flash_OFF_InProgress;

/*
* @brief: This function is used to get the Flash Tell-Tale Timer value 
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
static uint8_t g_TT_Flash_Timer_Val_u8;

/*
* @brief: This function is used to find the Flash count for Tell-Tale Flash Functionality
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
static void TT_Mgr_FlashCount(void);

/*
* @brief: This API is used to get current flasing Telltale status
  @parm:  p_TT_ID_u8
  @return:uint8_t
*/
static uint8_t Swc_Get_Current_Flashing_TT(uint8_t p_TT_ID_u8);

/*
* @brief: This function is used to check whether the telltale is flashed or not
  @parm:  p_TT_ID_u8
  @return:bool
*/
bool Swc_Check_Is_Flash_TT(uint8_t p_TT_ID_u8);




/*********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N S                     
*********************************************************************************************************************/
/*
* @brief    This function is used to initialize the Tell-Tale Manager
* @param    None 
* @return   None
*/
void TT_Mgr_init(void)
{
	/*Initialize the Tell-Tale Index value*/
 	uint8_t fl_TT_Index_u8 ;
	/*Loop execution upto maximum Tell-Tale*/ 
	for(fl_TT_Index_u8=0; fl_TT_Index_u8<(uint8_t) TT_MAX; fl_TT_Index_u8++)
	{	
		/*Clear the demanaded status value*/	
		g_TT_Demanded_Status_u8[fl_TT_Index_u8] = 0;
		/*Clear the Tell-Tale status value*/
		g_TT_Status_u8[fl_TT_Index_u8]=0;
		/*Clear the Current status value*/
		g_TT_Current_Status_u8[fl_TT_Index_u8]=0;
		/*Clear the self check current value*/
		g_TT_Mgr_SelfCheckCount_u8=0; 
		/*Clear the ON timer value */
		g_TT_Flash_TimerValue_u8[fl_TT_Index_u8]=0;

		g_TT_Prev_Status_u8[fl_TT_Index_u8] = 0;

		g_TT_Sync_Status[fl_TT_Index_u8] = 0;
	}

	/* Clock colon always has blink state only */
	g_TT_Demanded_Status_u8[CLOCK_COLON] = TT_FLASH;

	g_TT_Flash_ON_InProgress = FALSE;

	g_TT_Flash_OFF_InProgress = FALSE;

}

/*
* @brief    This function is Active function or main function of the Tell-Tale Manager
* @param    None 
* @return   None
*/
void TT_Mgr_Active(void)
{
	/*Initialize the Tell-Tale Index value*/
	uint8_t fl_TT_Index_u8 = 0;

	bool fl_Is_Flash_Already_there = FALSE;

	uint8_t fl_TT_ID_U8 = 0;

    /*Check the Active Flag status*/
     if((g_TT_Mgr_ActiveFlag_u8==TT_ACTIVATE) && (Swc_TT_Pre_Condition() != FALSE))
     {
		/*Switch the Tell-Tale state*/ 
     	switch(g_TT_Mgr_State_u8)
		{
			/*Tell-Tale state with self check start*/
			case TT_SELFCHECK_START:
				/*Set All Tell-Tales*/
				TT_Mgr_SetAll();
				/*Tell-Tale state with self check delay*/
				g_TT_Mgr_State_u8=TT_NORMAL;
			break;
				/*Tell-Tale state with self check delay*/
			case TT_SELFCHECK_INPROGRESS	:
			    /*Check Self check count with threshold value of self check count*/
				if(g_TT_Mgr_SelfCheckCount_u8<=TT_SELFCHECK_COUNT)
				{		
					/*increment Self check count*/
					g_TT_Mgr_SelfCheckCount_u8=g_TT_Mgr_SelfCheckCount_u8+(uint8_t)1;
					/*Store Tell-Tale state with self check delay*/
					g_TT_Mgr_State_u8=TT_SELFCHECK_INPROGRESS	;
				}
				else
				{
					/*Clear All Tell-Tales*/
					TT_Mgr_ClearAll();
					/*Store Tell-Tale state with normal*/
					g_TT_Mgr_State_u8=TT_NORMAL;
				}
			break;	
			/* Tell-Tale state with normal*/
			case TT_NORMAL:
				/*Loop execution upto maximum Tell-Tale*/ 
				for(fl_TT_Index_u8=0; fl_TT_Index_u8< (uint8_t)TT_MAX; fl_TT_Index_u8++)
				{
					g_TT_Prev_Status_u8[fl_TT_Index_u8] = g_TT_Status_u8[fl_TT_Index_u8];

					/*Store current Tell-Tale status*/ 
					g_TT_Status_u8[fl_TT_Index_u8]=g_TT_Const_Details_St[fl_TT_Index_u8].TT_Status &
					g_TT_Demanded_Status_u8[fl_TT_Index_u8];
					/*Switch the Tell-Tale status*/
					switch(g_TT_Status_u8[fl_TT_Index_u8])
					{
						/*Tell-Tale status with OFF Functionality*/ 
						case TT_OFF:
						    /*Check Tell-Tale mode with GPIO*/ 
							if (g_TT_Const_Details_St[fl_TT_Index_u8].TT_Mode==(uint8_t) TT_DRIVE_TYPE_GPIO)
							{
								/*Tell-Tale OFF functionality with GPIO*/ 
								/*GPIO*/
								GPIO_PinWrite(g_TT_Const_Details_St[fl_TT_Index_u8].Port_Name, g_TT_Const_Details_St[fl_TT_Index_u8].pin, 0U);
								g_Check_Telltale_status = 1;
							}
							else if((g_TT_Const_Details_St[fl_TT_Index_u8].TT_Mode==(uint8_t) TT_DRIVE_TYPE_TFT))
							{
								if(Lvgl_Get_Active_Screen() != FALSE)
								{
									if(g_TT_Const_Details_St[fl_TT_Index_u8].HMI_TT_OFF_CBK != NULL)
									{
										g_TT_Const_Details_St[fl_TT_Index_u8].HMI_TT_OFF_CBK();

									}

								}
							}
							else
							{
								/* Do nothing */
							}

							g_TT_Sync_Status[fl_TT_Index_u8] = FALSE;


						break;
						/*Tell-Tale status with ON Functionality*/ 
						case TT_ON:
							/*Check Tell-Tale mode with GPIO*/ 
							if (g_TT_Const_Details_St[fl_TT_Index_u8].TT_Mode==(uint8_t) TT_DRIVE_TYPE_GPIO)
							
							{
								
							

								/*Tell-Tale ON functionality with GPIO*/ 
								/*ABs Led On*/

						       GPIO_PinWrite(g_TT_Const_Details_St[fl_TT_Index_u8].Port_Name, g_TT_Const_Details_St[fl_TT_Index_u8].pin, 1U);
						        g_Check_Telltale_status = 1;
							}
							else if((g_TT_Const_Details_St[fl_TT_Index_u8].TT_Mode==(uint8_t) TT_DRIVE_TYPE_TFT))
							{
								if(Lvgl_Get_Active_Screen() != FALSE)
								{
									if(g_TT_Const_Details_St[fl_TT_Index_u8].HMI_TT_ON_CBK != NULL)
									{
										g_TT_Const_Details_St[fl_TT_Index_u8].HMI_TT_ON_CBK();

									}
									
								}
							}
							else
							{
								/* Do nothing */
							}

							g_TT_Sync_Status[fl_TT_Index_u8] = FALSE;

				   
						break;
						/*Tell-Tale status with FLASH Functionality*/ 
						case TT_FLASH:

							/* check already flash is available */
							fl_Is_Flash_Already_there = Swc_Check_Is_Flash_TT(fl_TT_Index_u8);

							if((fl_Is_Flash_Already_there == TRUE) && (g_TT_Sync_Status[fl_TT_Index_u8] == FALSE))
							{
								/* check new flash request */
								if((g_TT_Status_u8[fl_TT_Index_u8] == TT_FLASH) && (g_TT_Prev_Status_u8[fl_TT_Index_u8] != TT_FLASH))
								{
									
									fl_TT_ID_U8 = Swc_Get_Current_Flashing_TT(fl_TT_Index_u8);

									if(fl_TT_Index_u8 > fl_TT_ID_U8)
									{
									/* synce up flash counter */
									g_TT_Flash_TimerValue_u8[fl_TT_Index_u8] = g_TT_Flash_TimerValue_u8[fl_TT_ID_U8] - 1;

									}
									else	
									{

									/* synce up flash counter */
									g_TT_Flash_TimerValue_u8[fl_TT_Index_u8] = g_TT_Flash_TimerValue_u8[fl_TT_ID_U8];
									}

									/* SYNC DONE */
									g_TT_Sync_Status[fl_TT_Index_u8] = TRUE;
								}
							}
							else
							{
								if(fl_Is_Flash_Already_there == FALSE) 
								{
									g_TT_Sync_Status[fl_TT_Index_u8] = TRUE;
								}
							}

							/*increment Tell-Tale Flash ON timer value*/
							g_TT_Flash_TimerValue_u8[fl_TT_Index_u8]=g_TT_Flash_TimerValue_u8[fl_TT_Index_u8]
							+(uint8_t)1;

							/*Check Tell-Tale Flash ON timer value with Tell-Tale Flash ON Count*/
							if(g_TT_Flash_TimerValue_u8[fl_TT_Index_u8] <= g_TT_Flash_ONCount_u8[fl_TT_Index_u8])
							{
								
								/*Tell-Tale OFF functionality with GPIO*/ 
								if (g_TT_Const_Details_St[fl_TT_Index_u8].TT_Mode==(uint8_t) TT_DRIVE_TYPE_GPIO)
								{
									/* Make HIGH HW TT */
									GPIO_PinWrite(g_TT_Const_Details_St[fl_TT_Index_u8].Port_Name, g_TT_Const_Details_St[fl_TT_Index_u8].pin, 1U);
			
								}
								else if(g_TT_Const_Details_St[fl_TT_Index_u8].TT_Mode==(uint8_t) TT_DRIVE_TYPE_TFT)
								{
									if(g_TT_Const_Details_St[fl_TT_Index_u8].HMI_TT_ON_CBK != NULL)
									{
										g_TT_Const_Details_St[fl_TT_Index_u8].HMI_TT_ON_CBK();

									}	
								}	
							}
							else
							{
								
								/*Tell-Tale OFF functionality with GPIO*/ 
								if (g_TT_Const_Details_St[fl_TT_Index_u8].TT_Mode==(uint8_t) TT_DRIVE_TYPE_GPIO)
								{
									/* Low HW TT */
									GPIO_PinWrite(g_TT_Const_Details_St[fl_TT_Index_u8].Port_Name, g_TT_Const_Details_St[fl_TT_Index_u8].pin, 0U);
						
								}
								else if(g_TT_Const_Details_St[fl_TT_Index_u8].TT_Mode==(uint8_t) TT_DRIVE_TYPE_TFT)
								{
									if(g_TT_Const_Details_St[fl_TT_Index_u8].HMI_TT_OFF_CBK != NULL)
									{
										g_TT_Const_Details_St[fl_TT_Index_u8].HMI_TT_OFF_CBK();
									}
								}	
								/*Check Tell-Tale Flash OFF timer value with Tell-Tale Flash OFF Count*/
								if(g_TT_Flash_TimerValue_u8[fl_TT_Index_u8] == (g_TT_Flash_OFFCount_u8[fl_TT_Index_u8] + g_TT_Flash_ONCount_u8[fl_TT_Index_u8]))
								{
									/*Clear  Tell-Tale Flash ON and OFF timer value*/
									g_TT_Flash_TimerValue_u8[fl_TT_Index_u8]=0;
								}
							}
					
						break;

						case TT_NO_ACTION:

								/* this is applicable for TFT TT */
								/*Clear  Tell-Tale Flash ON and OFF timer value*/
								g_TT_Sync_Status[fl_TT_Index_u8] = FALSE;
						
								
								break;

						default:
						/* do nothing */
						break;
			
					}
				}
				
		    break;
			default:
			/* do nothing */
			break;
		
		}
		
	}
	else
	{
		TT_Mgr_ClearAll();
	}

}

/* function is used to check whether the telltale is flashed or not */
bool Swc_Check_Is_Flash_TT(uint8_t p_TT_ID_u8)
{
	uint8_t fl_Loop_Idx = 0;
	bool fl_Ret_Status = FALSE;

	for(fl_Loop_Idx = 0; fl_Loop_Idx < TT_MAX; fl_Loop_Idx++)
	{
		if((g_TT_Status_u8[fl_Loop_Idx] == TT_FLASH) && (p_TT_ID_u8 != fl_Loop_Idx))
		{
			fl_Ret_Status = TRUE;

			break;
		}
		else
		{
			fl_Ret_Status = FALSE;

		}
	}

	return (fl_Ret_Status);
}

/* API is used to get current flasing Telltale status */
uint8_t Swc_Get_Current_Flashing_TT(uint8_t p_TT_ID_u8)
{
	uint8_t fl_Loop_Idx = 0;
	uint8_t fl_Flashing_TT_ID_u8;

	for(fl_Loop_Idx = 0; fl_Loop_Idx < TT_MAX; fl_Loop_Idx++)
	{
		if((g_TT_Status_u8[fl_Loop_Idx] == TT_FLASH) && (p_TT_ID_u8 != fl_Loop_Idx))
		{
			fl_Flashing_TT_ID_u8 = fl_Loop_Idx;

			break;
		}
	}

	return (fl_Flashing_TT_ID_u8);
}

/*
* @brief    This function is used to set the all Tell-Tales in the Tell-Tale Manager
* @param    None 
* @return   None
*/
void TT_Mgr_SetAll( void)
{
	
	/*Initialize the Tell-Tale Index value*/
	uint8_t fl_TT_ID_u8 ;
	
	/*Loop execution upto maximum Tell-Tale*/ 
	for(fl_TT_ID_u8=0; fl_TT_ID_u8< (uint8_t)TT_MAX; fl_TT_ID_u8++)
	{
	    /*Check the Tell-Tale Mode with GPIO*/
		if (g_TT_Const_Details_St[fl_TT_ID_u8].TT_Mode==(uint8_t) TT_DRIVE_TYPE_GPIO)
		{
		/* Set Tell-Tale through GPIO*/
		/*GPIO*/

		}
		else
		{	
		/* Set Tell-Tale through SPI*/
		/*SPI*/
		}
	}
}


/*
* @brief    This function is used to Clear the all Tell-Tales in the Tell-Tale Manager
* @param    None 
* @return   None
*/
void TT_Mgr_ClearAll( void)
{
	
	/*Initialize the Tell-Tale Index value*/
	uint8_t fl_TT_ID_u8;
	
	/*Loop execution upto maximum Tell-Tale*/ 
	for(fl_TT_ID_u8=0; fl_TT_ID_u8< (uint8_t)TT_MAX; fl_TT_ID_u8++)
	{
	    /*Check the Tell-Tale Mode with GPIO*/
		if (g_TT_Const_Details_St[fl_TT_ID_u8].TT_Mode == (uint8_t) TT_DRIVE_TYPE_GPIO)
		{
		/* Clear Tell-Tale through GPIO*/
		GPIO_PinWrite(g_TT_Const_Details_St[fl_TT_ID_u8].Port_Name, g_TT_Const_Details_St[fl_TT_ID_u8].pin, 0U);
		}
		else
		{	
		/* Clear Tell-Tale through SPI*/
		/*SPI*/
		}
	}
}

/*
* @brief    This function is used to store the demanaded status of Tell-Tale
* @param    fl_TT_ID_u8  - TellTale_Id,fl_TT_Status_u8  - TellTale_Status 
* @return   None
*/
void TT_Mgr_Command( uint8_t fl_TT_ID_u8,  uint8_t fl_TT_Status_u8)
{
	/*Store the Tell-tale status */
	g_TT_Demanded_Status_u8[fl_TT_ID_u8] = fl_TT_Status_u8;
	
}



/*
* @brief    This function is used to activate the state of the Tell-Tale self check
* @param    None 
* @return   None
*/
void TT_Mgr_Proveout(void)
{
	/*Store the Tell-Tale Self Check start state */
	g_TT_Mgr_State_u8=TT_SELFCHECK_START;
}


/*
* @brief    This function is used to calculate the ON and OFF timer count value of Tell-tale Flash Functionality
* @param    None 
* @return   None
*/
static void TT_Mgr_FlashCount(void)
{
	/*Initialize the Tell-Tale Index value*/
	uint8_t fl_TT_Index_u8;

	/*Initialize the Tell-Tale Flash Timer Count value*/
	uint8_t fl_TT_Flash_TimerCount_u8=0;
	
    /*Initialize the Tell-Tale Flash Timer value*/
	uint16_t fl_TT_Flash_TimerValue_u16=0;
	
	/*Loop execution upto maximum Tell-Tale*/ 
	for(fl_TT_Index_u8=0; fl_TT_Index_u8< (uint8_t)TT_MAX; fl_TT_Index_u8++)
	{
		/*Store the Flash Timer Value in Milliseconds*/	
		fl_TT_Flash_TimerValue_u16=((uint16_t)1*(uint16_t)TT_MILLISECONDS/(uint16_t)g_TT_Const_Details_St
		[fl_TT_Index_u8].TellTale_Flash_Config_St.TT_Frequency);
		/*Store the Flash Timer Count Value*/
		fl_TT_Flash_TimerCount_u8=(uint8_t)(fl_TT_Flash_TimerValue_u16/(uint16_t)TT_TIMETASK);
		/*Store the Flash ON count value*/
		g_TT_Flash_ONCount_u8[fl_TT_Index_u8]=(uint8_t)((fl_TT_Flash_TimerCount_u8*g_TT_Const_Details_St
		[fl_TT_Index_u8].TellTale_Flash_Config_St.TT_Duty)/TT_PERCENTAGE);
		/*Store the Flash OFF Count value*/
		g_TT_Flash_OFFCount_u8[fl_TT_Index_u8]=fl_TT_Flash_TimerCount_u8-g_TT_Flash_ONCount_u8[fl_TT_Index_u8];
	}
}


/*
* @brief    This function is used to Activate the Tell-Tale Manager
* @param    None 
* @return   None
*/
void TT_Mgr_Activate(void)
{
	/*Activate the Tell-Tale Manager Active Flag*/
	g_TT_Mgr_ActiveFlag_u8=TT_ACTIVATE;
	/*Call the Flash Count Function*/
	TT_Mgr_FlashCount();
	
}


/*
* @brief    This function is used to Deactivate the Tell-Tale Manager
* @param    None 
* @return   None
*/
void TT_Mgr_Deactivate(void)
{
	/*Deactivate the Tell-Tale Manager Active Flag*/
	g_TT_Mgr_ActiveFlag_u8=TT_DEACTIVATE;
}


/*
* @brief    This function is used to Deinit the Tell-Tale Manager
* @param    None 
* @return   None
*/
void TT_Mgr_Deinit(void)
{
	/*Initialize the Tell-Tale Index value*/
	 uint8_t fl_TT_Index_u8;
	/*Loop execution upto maximum Tell-Tale*/ 
	for(fl_TT_Index_u8=0; fl_TT_Index_u8< (uint8_t)(TT_MAX); fl_TT_Index_u8++)
	{	
		/*Clear the demanaded status value*/	
		g_TT_Demanded_Status_u8[fl_TT_Index_u8]=0;
		/*Clear the Tell-Tale status value*/
		g_TT_Status_u8[fl_TT_Index_u8]=0;
		/*Clear the Current status value*/
		g_TT_Current_Status_u8[fl_TT_Index_u8]=0;
		/*Clear the self check current value*/
		g_TT_Mgr_SelfCheckCount_u8=0; 
		/*Clear the ON timer value */
		g_TT_Flash_TimerValue_u8[fl_TT_Index_u8]=0;
		/*Clear the OFF timer value*/
		g_TT_Flash_OFFTimerValue_u8[fl_TT_Index_u8]=0;
	}
}


/*
* @brief    This function is used to Diagnostic the Tell-Tale Manager
* @param    fl_TT_ID_u8  - TellTale_Id
* @return   g_TT_Current_Status_u8 - TellTale_Current_Status
*/
uint8_t TT_Mgr_Diagnostic(uint8_t fl_TT_ID_u8)
{
	uint8_t ret = 0;
	/*Check Tell-Tale operation with safety*/
	if(g_TT_Const_Details_St[fl_TT_ID_u8].TT_Operation==(uint8_t)TT_SAFETY)
	{
		/*Store current Tell-Tale status */
		/*g_TT_Current_Status_u8[fl_TT_ID_u8]= GPIOreadbit()*/
		/*Return current Tell-Tale status */
		ret = g_TT_Current_Status_u8[fl_TT_ID_u8];
	}
	else
	{
		/*do nothing*/
	}
	
	return (uint8_t)(ret);
}

uint8_t Swc_TT_Pre_Condition(void)
{
   bool fl_Precondition_Status = FALSE;
   
   uint8_t fl_HVSD_check_u8;

   uint8_t fl_Ign_Position_u8;

   uint8_t fl_LVSD_check_u8;
 
  fl_Ign_Position_u8 = Sys_Service_Get_Ignition_State();

  fl_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

  fl_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

  if( (fl_Ign_Position_u8   == IGN_OFF) || 
      (fl_LVSD_check_u8 == SYSTEM_SERVICE_SET) ||
      (fl_HVSD_check_u8 == SYSTEM_SERVICE_SET) )
  {
     fl_Precondition_Status = FALSE;
  }
  else
  {
      fl_Precondition_Status = TRUE;
  }

  return (fl_Precondition_Status);
}

void SIDE_STAND_LED_ON(void)
{
	GPIO_PinWrite(GPIO9,BOARD_INITPINS_TT_SS_DIG_MCU_OUT_GPIO_PIN,1);
}

void SIDE_STAND_LED_OFF(void)
{
	GPIO_PinWrite(GPIO9,BOARD_INITPINS_TT_SS_DIG_MCU_OUT_GPIO_PIN,0);
}

/**********************************************************************************************************************/
/*                                              E N D   O F   S O F T W A R E                                         */
/**********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/**********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y                                       
 **********************************************************************************************************************/
/**********************************************************************************************************************
			REVISION NUMBER      : V1.0.0
			REVISION DATE        : 29-December-2020
			CREATED / REVISED BY : R Maheswari (maheswari@niyatainfotech.com
			DESCRIPTION          : Code Implemented and comments Added                          
------------------------------------------------------------------------------------------------------------------------
			REVISION NUMBER      : V1.0.1                                                
			REVISION DATE        : 20-01-2021                              
			CREATED / REVISED BY : R Maheswari (maheswari@niyatainfotech.com  
			DESCRIPTION          : Peer reveiew comments fixed 
 **********************************************************************************************************************/
#endif /* ! TTMGR_C */
