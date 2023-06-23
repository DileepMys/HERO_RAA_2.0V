/* @file FILE NAME */
#ifndef SPEEDO_C
#define SPEEDO_C
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
*  File name                       : Speedo.c
*  Version                         : V1.0.3
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent
*  Description                     : This file contains definition of speedometer
*  @bug                         
--------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/


/*********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                             
*********************************************************************************************************************/
#include "Swc_Speedometer_Cfg.h"
#include "stdint.h"
#include "hal_stdtypes.h"
#include "Abs_Telltale.h"
#include "CanMgr.h"
#include "Swc_Averege_Speed.h"
/*********************************************************************************************************************
*                                             M A C R O   D E F I N I T I O N S                                          
*********************************************************************************************************************/
/*
* @brief		: This enum is used to define active flag status
* @Unit			: N/A
* @Resolution	: 1
* @Range		: 0 to 8 bit
* @Applicability: Speedometer_Active function is activated or deactivated based on this configuration
*/
typedef enum
{
	SPEEDO_DEACTIVATE = 0u,
	SPEEDO_ACTIVATE   = 1u

} Speedo_ActiveFlag_List_Type_en;


/*
* @brief		: This enum is used to define Speed precondition
* @Unit			: N/A
* @Resolution	: 1
* @Range		: 0 to 8 bit
* @Applicability: SSpeedometer precondition
*/
typedef enum
{
	NOK = 0u,
	OK   = 1u

} Speedo_Precondition_List_Type_en;

/*
* @brief		: This enum is used to define Speed Configuration enabling
* @Unit			: N/A
* @Resolution	: 1
* @Range		: 0 to 8 bit
* @Applicability: SSpeedometer Enbale
*/
typedef enum
{
	DISABLE = 0u,
	ENABLE   = 1u

} Speedo_Enable_List_Type_en;


/*
* @brief		: This enum is used to define Speed unit selection
* @Unit			: N/A
* @Resolution	: 1
* @Range		: 0 to 8 bit
* @Applicability: SSpeedometer Speed unit selection
*/
typedef enum
{
	SPEED_KMPH = 0u,
	SPEED_MPG   = 1u

} Speedo_unit_List_Type_en;

/*
* @brief		: This macro is used to define IGN mode
* @Unit			: N/A
* @Resolution	: 1
* @Range		: 0 to 8 bit
* @Applicability: Speedometer  power mode selction
*/
/*#define SPEEDO_IGN_MODE()                                          Sys_Service_Get_Ignition_State()*/

/*
* @brief        : This macro is used to configure the nominal speedo value range
* @Unit         : KMPH
* @Resolution   : 1
* @Range        : NA
* @Applicability: This configuration is used for actual speed
* @Note         : Do not modify this macro value or name
*/
  #define SPEEDO_NOMINAL			    (int[]){0,2200,4300,6450,8600,10750,12900,15050,17200,19350,20425,21500}
/*********************************************************************************************************************
*                                          G L O B A L   V A R I A B L E    D E C L A R A T I O N S                                    
*********************************************************************************************************************/
/*
*@brief			: This variable is used to define the Active function flag
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: Activate or Deactivate 
*@Applicability	: This variable is used in Speedo_ACTIVE function to Check Activated or Deactivated
*/
static uint8_t g_Speedo_ActiveFlag_u8;

/*
*@brief			: This variable is used to define the Speedo precondition
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: OK/NOTOK 
*@Applicability	: This variable is used in Speedometer Precondition
*/
static uint8_t g_Speedo_Precondition_u8;

/*
*@brief			: This variable is used to define the Speedo Input
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_16
*@Applicability	: This variable is used in Speedometer Input
*/
static uint16_t g_Speedo_Input_u16;


/*
*@brief			: This variable is used to define the Speedo Fault
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_8
*@Applicability	: This variable is used in Speedometer Fault
*/
static uint8_t g_Speedo_Fault_u8;


/*
*@brief			: This variable is used to define the Speedo value
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_16
*@Applicability	: This variable is used in Speedometer value
*/
static uint32_t g_Dispalyed_Speed_Value_u32;


/*
*@brief			: This variable is used to define the Speedo value
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_8
*@Applicability	: This variable is used in Speedometer unit value
*/
static uint8_t g_Dispalyed_Unit_u8;


/*
*@brief			: This variable is used to define the Speedo value
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_32
*@Applicability	: This variable is used in Speedometer Actual value
*/
static uint32_t g_Actual_Speed_u32;

/*
*@brief			: This variable is used to define the Speedo value
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_32
*@Applicability	: This variable is used in Speedometer Actual value
*/
static uint32_t g_Speed_Diff_KMPH[10];

/*
*@brief			: This variable is used to define the Speedo value
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_32
*@Applicability	: This variable is used in Speedometer Actual value
*/
static uint32_t g_Speed_Diff_MPG[7];
/*
*@brief			: This variable is used to define the Speedo value
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_32
*@Applicability	: This variable is used in Speedometer Actual value
*/
static uint32_t g_Speed_Actual_Diff[10];

static uint8_t g_Precondition_Status;

/*
*@brief			: This variable is used to define the Speedo value
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_32
*@Applicability	: This variable is used in Speedometer Actual value
*/
static uint32_t g_Speed_Actual_Factor;

/*
*@brief			: This variable is used to define the status of  Speed missing signal 
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: N/A
*@Applicability	: This variable is used in Speedometer Actual value
*/
bool g_Is_speed_Signal_Missing_bool;

/*
*@brief			: This variable is used to get the Speedo value from CAN signal
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_32
*@Applicability	: This variable is used in Speedometer Actual value
*/
float64  g_Speedo_CanSignal_Value_f64;
/*********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N S                     
*********************************************************************************************************************/
/*
* @brief    This function is used to initialize the Speedometer
* @param    None 
* @return   None
*/
void Speedometer_Init(void)
{
	Speedometer_Activate();
	
	g_Is_speed_Signal_Missing_bool = TRUE;
}

/*
* @brief    This function is Deinit of the Speedometer
* @param    None 
* @return   None
*/
void Speedometer_Deinit(void)
{

}

/*
* @brief    This function is activate of the Speedometer
* @param    None 
* @return   None
*/
void Speedometer_Activate(void)
{
	/*Activate the Speedometer Active Flag*/
	g_Speedo_ActiveFlag_u8 = (uint8_t)SPEEDO_ACTIVATE;
}

/*
* @brief    This function is Deactivate of the Speedometer
* @param    None 
* @return   None
*/
void Speedometer_Deactivate(void)
{
	/*Deactivate the Speedometer Activate Flag*/
	g_Speedo_ActiveFlag_u8 = (uint8_t)SPEEDO_DEACTIVATE;
}

/*
* @brief    This function is main or active of the Speedometer
* @param    None 
* @return   None
*/
void Speedometer_Active(void)
{

    uint8_t fl_loop_index_u8;
	uint32_t fl_Actual_Speed_First_Row_u32;
	uint32_t fl_Actual_Speed_Second_Row_u32;

	uint32_t fl_Indicated_Speed_First_Row_u32;
	uint32_t fl_Indicated_Speed_Second_Row_u32;

	uint32_t fl_Actual_Speed_Delta_u32;
	uint32_t fl_Indicated_Speed_Delta_u32;

   g_Precondition_Status = Swc_Speedometer_Pre_Condition();

	/* Check the Active flag status*/
	if (g_Speedo_ActiveFlag_u8 == (uint8_t)SPEEDO_ACTIVATE)
	{		

		if (g_Precondition_Status == TRUE)
		{
			
			if(CAN_BUS_ON == App_Can_bus_off_Get_indication() )
			{
				if(TRUE != g_Is_speed_Signal_Missing_bool)
				 {
					uint16_t CAN_ID =126;
					/*Get from CAN vehicle speed*/
					CanMgr_Read_vehicle_speed_0x206_s(&g_Speedo_CanSignal_Value_f64);

					g_Speedo_Input_u16= (uint16_t )g_Speedo_CanSignal_Value_f64;

					g_Speedo_Fault_u8=FALSE;
				 }
				 else
				 {
					g_Speedo_Input_u16=0x00;
					g_Speedo_Fault_u8=TRUE;
				 }
			}
			
			else
			{
				g_Speedo_Input_u16=0x00;
				g_Speedo_Fault_u8=TRUE;
			}
		}
		
		else 
		{
			g_Speedo_Input_u16=0x00;
			
		}
		
		if (g_Precondition_Status == TRUE)
		{
			/*Check speed Fault true*/
				if(TRUE == g_Speedo_Fault_u8)
				{
					g_Dispalyed_Speed_Value_u32=0x00;
					g_Dispalyed_Unit_u8=SPEEDO_UNIT_SELECTION;
				}
				else
				{
					/*selection process KMPH or MPH*/
					if( SPEED_KMPH == SPEEDO_UNIT_SELECTION)
					{
						if(g_Speedo_Input_u16 > 199)
						{
							g_Dispalyed_Speed_Value_u32=SPEED_MAX;
						}
					}
									
					else
					{
						/*Speed input from CAN*/
						if(g_Speedo_Input_u16 > AVEREAGE_SPEED)
						{
							g_Dispalyed_Speed_Value_u32=SPEED_MAX;
						}
					}
					/*selection process KMPH or MPH*/
					if( SPEED_KMPH == SPEEDO_UNIT_SELECTION)
					{
						g_Dispalyed_Unit_u8=SPEED_KMPH;
						g_Actual_Speed_u32=g_Speedo_Input_u16*100;

						/* Table Boundary Verification */
						  if (g_Actual_Speed_u32 <= SPEEDO_ACTUAL_SPEED[0])
						  {
							  g_Dispalyed_Speed_Value_u32 = SPEEDO_NOMINAL[0];

						  }
						  else if (g_Actual_Speed_u32 >= SPEEDO_ACTUAL_SPEED[11])
						  {
							  g_Dispalyed_Speed_Value_u32 = SPEED_MAX;

						  }
						  else
						  {

							for (fl_loop_index_u8 = 0; fl_loop_index_u8 < SPEEDO_VALUES_KMPH; fl_loop_index_u8++)
							{
							fl_Actual_Speed_First_Row_u32 = SPEEDO_ACTUAL_SPEED[fl_loop_index_u8];
							fl_Actual_Speed_Second_Row_u32 = SPEEDO_ACTUAL_SPEED[fl_loop_index_u8 + 1];

							fl_Indicated_Speed_First_Row_u32 = SPEEDO_NOMINAL[fl_loop_index_u8];
							fl_Indicated_Speed_Second_Row_u32 = SPEEDO_NOMINAL[fl_loop_index_u8 + 1];
		
							if(g_Actual_Speed_u32 == SPEEDO_ACTUAL_SPEED[fl_loop_index_u8])
							{
								g_Dispalyed_Speed_Value_u32 = SPEEDO_NOMINAL[fl_loop_index_u8];
								
								break;
							}				  
							/* Linear Interpolation */
							else if ( (g_Actual_Speed_u32 > fl_Actual_Speed_First_Row_u32) &&
										(g_Actual_Speed_u32 < fl_Actual_Speed_Second_Row_u32) )
							{
								fl_Actual_Speed_Delta_u32 = fl_Actual_Speed_Second_Row_u32 - fl_Actual_Speed_First_Row_u32;
								fl_Indicated_Speed_Delta_u32 = fl_Indicated_Speed_Second_Row_u32 - fl_Indicated_Speed_First_Row_u32;

								g_Dispalyed_Speed_Value_u32 = fl_Indicated_Speed_First_Row_u32 + ((float)(g_Actual_Speed_u32 - fl_Actual_Speed_First_Row_u32) / (float)fl_Actual_Speed_Delta_u32) * fl_Indicated_Speed_Delta_u32;



								break;
							}
							else
							{

							}

							}

							/* round off displayed speedo value */
							g_Dispalyed_Speed_Value_u32 = round_int(g_Dispalyed_Speed_Value_u32,100);

							/* Convert speedo value into 1km/h resolution*/
							g_Dispalyed_Speed_Value_u32 = g_Dispalyed_Speed_Value_u32 / 100;
							
						  }
																	
					}
					else
					{
						g_Dispalyed_Unit_u8=SPEED_MPG;
						g_Actual_Speed_u32=g_Speedo_Input_u16*100;
						g_Actual_Speed_u32 =(g_Actual_Speed_u32 *1000)/ 1609;
						
						for (fl_loop_index_u8=0;fl_loop_index_u8<SPEEDO_VALUES_MPG ; fl_loop_index_u8++)
						{
							if (SPEEDO_MPG_MIN[fl_loop_index_u8] ==0)
							{
								g_Speed_Diff_MPG[fl_loop_index_u8]=0;
								g_Speed_Actual_Diff[fl_loop_index_u8]=0;
								g_Speed_Actual_Factor=0;
								
							}
							else
							{
								g_Speed_Diff_MPG[fl_loop_index_u8]=SPEEDO_MPG_MIN[fl_loop_index_u8]-SPEEDO_MPG_MIN[fl_loop_index_u8-1];
								g_Speed_Actual_Diff[fl_loop_index_u8]=SPEEDO_ACTUAL_SPEED[fl_loop_index_u8]-SPEEDO_ACTUAL_SPEED[fl_loop_index_u8-1];
								g_Speed_Actual_Factor=(g_Speed_Diff_MPG[fl_loop_index_u8]*100)/g_Speed_Actual_Diff[fl_loop_index_u8];
								
							}
						}
						g_Dispalyed_Speed_Value_u32=(g_Actual_Speed_u32*g_Speed_Actual_Factor)/100;
						
					}
					
				}				
			}
		
		
		else 
		{
			/* Do Nothing */
		}
		
}
	
}

/* This API is used to check pre condition status of the Speedometer */
uint8_t Swc_Speedometer_Pre_Condition(void)
{
   uint8_t fl_Ign_Position_u8 = 0;
   uint8_t fl_Speedo_LVSD_check_u8;
   uint8_t fl_Speedo_HVSD_check_u8;
   bool fl_Precondition_Status;
 
  fl_Ign_Position_u8 = Sys_Service_Get_Ignition_State();

  fl_Speedo_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

  fl_Speedo_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

  if( (fl_Ign_Position_u8   == IGN_OFF) || 
      (fl_Speedo_LVSD_check_u8 == 0) ||
      (fl_Speedo_HVSD_check_u8 == 0) )
  {
     g_Precondition_Status = FALSE;
  }
  else
  {
      g_Precondition_Status = TRUE;
  }

  return g_Precondition_Status;
}

/* API is used to get call back for CAN signal timeout */
void CanMgr_Speedo_Timeout_Callback_0x206(void)

{
	CanMgr_Speedo_Timeout_Flag();

}

/* API is used to get timeout flag for CAN speedo value */
void CanMgr_Speedo_Timeout_Flag(void)
{
	g_Is_speed_Signal_Missing_bool = TRUE;
}

/* API is used to callback the CANMGR speedo value */
void CanMgr_Speedo_reception_cbk(void)
{

	g_Is_speed_Signal_Missing_bool = FALSE;
}

/*
* @brief     :This API is used to get raw speed value 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by applicaton layer
*/
bool Swc_Speedo_Get_Msg_TimeOut_Staus(void)
{
	/* Vehicle speed message timeout status */
	return (g_Is_speed_Signal_Missing_bool);
}

/* API is used to get spped value which needs to be display on the speedo meter */
uint32_t Get_display_Speed(void)
{
	if(g_Dispalyed_Speed_Value_u32>SPEED_MAX)
	{
		g_Dispalyed_Speed_Value_u32 = SPEED_MAX;
	}
	else
	{
		/* do nothing */
	}

	return (g_Dispalyed_Speed_Value_u32);
}

/*
* @brief    This function is used to get fault status of speedometer if CAN signal is not received
* @param    None 
* @return   uint8_t status of speedometer fault
*/
uint8_t Swc_Get_Speedometer_Fault_Status(void)
{
	return (g_Speedo_Fault_u8);
}

/* API is used to get raw speed value  */
uint16_t Swc_Get_RAW_Speedo_Val(void)
{
	return (g_Speedo_Input_u16);
}
/**********************************************************************************************************************/
/*                                              E N D   O F   S O F T W A R E                                         */
/**********************************************************************************************************************/


/**********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y                                       
 **********************************************************************************************************************/
/**********************************************************************************************************************
REVISION NUMBER      : V1.0.0
REVISION DATE        : 30-April-2021
CREATED / REVISED BY : Maheswari R(maheswari@niyatainfotech.com)
DESCRIPTION          : Initial Version

REVISION NUMBER      : V1.0.1
REVISION DATE        : 26-May-2021
CREATED / REVISED BY : Maheswari R(maheswari@niyatainfotech.com)
DESCRIPTION          : Peer Review comments fixed

REVISION NUMBER      : V1.0.2
REVISION DATE        : 07-Nov-2022
CREATED / REVISED BY : Palani kumar R(palanikumar@niyatainfotech.com)
DESCRIPTION          : Round OFF of Calculated speedo value is removed as per SPEEDO SRD V1.1

REVISION NUMBER      : V1.0.3
REVISION DATE        : 07-Nov-2022
CREATED / REVISED BY : Palani kumar R(palanikumar@niyatainfotech.com)
DESCRIPTION          : Round OFF of Calculated speedo value is rolled back
------------------------------------------------------------------------------------------------------------------------

**********************************************************************************************************************/
#endif /* ! SPEEDO_C */
