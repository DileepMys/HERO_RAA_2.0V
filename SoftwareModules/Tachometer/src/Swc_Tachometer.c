/* @file FILE NAME */
#ifndef TACHO_C
#define TACHO_C
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
*  File name                       : TACHO.c
*  Version                         : V1.0.2
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent
*  Description                     : This file contains the Implementation of Odometer 
*  @bug                         
--------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/


/*********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                             
*********************************************************************************************************************/
#include "Swc_Tachometer.h"
#include "stdint.h"
#include "hal_stdtypes.h"
#include "Abs_Telltale.h"
#include "Swc_System_Service.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include "CanMgr_cfg.h"
#include "Interpolation.h"
/*********************************************************************************************************************
*                                             M A C R O   D E F I N I T I O N S                                          
*********************************************************************************************************************/
/*
* @brief		: This enum is used to define active flag status
* @Unit			: N/A
* @Resolution	: 1
* @Range		: 0 to 8 bit
* @Applicability: TACHOmeter_Active function is activated or deactivated based on this configuration
*/
typedef enum
{
	TACHO_DEACTIVATE = 0u,
	TACHO_ACTIVATE   = 1u

} TACHO_ActiveFlag_List_Type_en;


/*
* @brief		: This macro is used to define IGN mode
* @Unit			: N/A
* @Resolution	: 1
* @Range		: 0 to 8 bit
* @Applicability: TACHOmeter  power mode selction
*/
#define TACHO_IGN_MODE                                             Sys_Service_Get_Ignition_State()


/*********************************************************************************************************************
*                                          G L O B A L   V A R I A B L E    D E C L A R A T I O N S                                    
*********************************************************************************************************************/
/*
*@brief			: This variable is used to define the Active function flag
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: Activate or Deactivate 
*@Applicability	: This variable is used in TACHO_ACTIVE function to Check Activated or Deactivated
*/
static uint8_t g_TACHO_ActiveFlag_u8;

/* This variable is used to check the pre condition status such as Ignition on/off, HVSD/LVSD state */
static uint8_t g_Precondition_Status;


/*
*@brief			: This variable is used to define the TACHO Input
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_16
*@Applicability	: This variable is used in TACHOmeter Input
*/
static uint16_t g_TACHO_Input_u16;


/*
*@brief			: This variable is used to define the TACHO Fault
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_8
*@Applicability	: This variable is used in TACHOmeter Fault
*/
static uint8_t g_TACHO_Fault_u8;

/*
*@brief			: This variable is used to define the TACHO Fault
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_8
*@Applicability	: This variable is used in TACHOmeter Fault
*/
static uint16_t g_TACHO_Diff_RPM_u16[9];

/*
*@brief			: This variable is used to define the TACHO Fault
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_8
*@Applicability	: This variable is used in TACHOmeter Fault
*/
static uint16_t g_TACHO_Pointer_Diff_u16[9];

/*
*@brief			: This variable is used to define the TACHO Fault
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_8
*@Applicability	: This variable is used in TACHOmeter Fault
*/
static uint32_t g_TACHO_Actual_Factor;
/*
*@brief			: This variable is used to define the TACHO Fault
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_8
*@Applicability	: This variable is used in TACHOmeter Fault
*/
static uint32_t g_TACHO_Cmd_Output;

/* This variable defines the Tcho value from CAN input */
float64 g_Tacho_Can_Value_f64;

/* This variable is used to get tacho missing status */
bool g_Tacho_Missing_Status_bool;

/*
*@brief			: This variable is used to define Engine RPM vs Pointer Poistion
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: uint_8
*@Applicability	: This variable is used in TACHOmeter Fault
*/
uint16_t g_Table_RPM_Vs_Pointer_Tbl[TOTAL_TABLE_INDEX][2] = TACHO_RPM_VS_POINTER;

/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
* @brief    This function is to reset TACHO OUTPUT
* @param    None 
* @return   None
*/
static void Swc_Tacho_Reset_CMD_Output(void);
/*********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N S                     
*********************************************************************************************************************/
/*
* @brief    This function is used to initialize the TACHOmeter
* @param    None 
* @return   None
*/
void Tachometer_Init(void)
{
	g_Tacho_Missing_Status_bool = TRUE;
	Tachometer_Activate();
}

/*
* @brief    This function is Deinit of the TACHOmeter
* @param    None 
* @return   None
*/
void Tachometer_Deinit(void)
{
	/* do nothing */
}

/*
* @brief    This function is activate of the TACHOmeter
* @param    None 
* @return   None
*/
void Tachometer_Activate(void)
{
	/*Activate the TACHOmeter Active Flag*/
	g_TACHO_ActiveFlag_u8 = (uint8_t)TACHO_ACTIVATE;
}

/*
* @brief    This function is Deactivate of the TACHOmeter
* @param    None 
* @return   None
*/
void Tachometer_Deactivate(void)
{
	/*Deactivate the TACHOmeter Activate Flag*/
	g_TACHO_ActiveFlag_u8 = (uint8_t)TACHO_DEACTIVATE;
}

/*
* @brief    This function is main or active of the TACHOmeter
* @param    None 
* @return   None
*/
void Tachometer_Active(void)
{
   float64  *fl_Tacho_data_u64;

    uint8_t fl_loop_index_u8;

	/* Precondtion status */
    g_Precondition_Status = Swc_Tachometer_Pre_Condition();

	/* Check the Active flag status*/
	if ((g_TACHO_ActiveFlag_u8 == (uint8_t)TACHO_ACTIVATE) && (g_Precondition_Status == TRUE))
	{		
		if(CAN_BUS_ON ==  App_Can_bus_off_Get_indication() )
		{
			if(FALSE != g_Tacho_Missing_Status_bool)
			{
				/* Reset Tacho CMD*/
				Swc_Tacho_Reset_CMD_Output();
			}
			else
			{
				/* Get ENGINE RPM Value from CAN*/
				g_TACHO_Input_u16= CanMgr_Read_engine_speed_0x130_s(&g_Tacho_Can_Value_f64);

				/* Linear interpolation ENGINE RPM VS GAUGE POINTER*/
				g_TACHO_Actual_Factor = LinearInterpolateWord(&g_Table_RPM_Vs_Pointer_Tbl[0][0],(uint16_t)g_Tacho_Can_Value_f64);

				/* Raw Engine RPM*/
				g_TACHO_Cmd_Output= g_Tacho_Can_Value_f64;
				
				if (g_TACHO_Actual_Factor > TACHO_MAX)
				{
					/* Max Tacho Gauge Pointer Angle 90 deg  0.1 resoultion*/
					g_TACHO_Actual_Factor = TACHO_MAX;
				}
			}		
					
		}
		else
		{
			/* Reset Tacho CMD*/
			Swc_Tacho_Reset_CMD_Output();
		}
	
    }
	else
	{
		/* Reset Tacho CMD*/
		Swc_Tacho_Reset_CMD_Output();
	}

}

/*
* @brief    This function is to reset TACHO OUTPUT
* @param    None 
* @return   None
*/
static void Swc_Tacho_Reset_CMD_Output(void)
{
	/* Assign Default value */
	g_TACHO_Cmd_Output=TACHO_MIN;

	g_TACHO_Actual_Factor = TACHO_MIN;
}

/* API is used to get the call back status TACHOmeter state */
uint32_t TACHOMETER_GET_CALL_BACK_STATE(void)
{
	uint32_t fl_Tacho_RPM_Val_u32;

	/* Valid Engine RPM */
	if((g_TACHO_Cmd_Output >= 0) && (g_TACHO_Cmd_Output <= MAX_TACHO_ENGINE_RPM))
	{
		fl_Tacho_RPM_Val_u32 = g_TACHO_Cmd_Output;
	}
	else if(g_TACHO_Cmd_Output > MAX_TACHO_ENGINE_RPM)
	{
		/* Max Engine RPM is 8000*/
		fl_Tacho_RPM_Val_u32 = MAX_TACHO_ENGINE_RPM;
	}

	/* Return Engine RPM */
	return (fl_Tacho_RPM_Val_u32);
	
}

/*
* @brief    This function is used to get Pointer Positon
* @param    None 
* @return   uint16_t
*/
const uint16_t Tacho_Get_Pointer_Position(void)
{
	/* Pointer Angle against Engine RPM*/
	return (g_TACHO_Actual_Factor);
}

/* This API is used to get timeout call back from CAN mgr  */
void CanMgr_Tacho_Timeout_Callback_0x130(void)
{

	CanMgr_Tacho_Timeout_Flag();
}

/* API is used to Activate the tacho timout flag  from CAN */
void CanMgr_Tacho_Timeout_Flag(void)
{

	g_Tacho_Missing_Status_bool = TRUE;
}

/* API is used to get tacho reception call back from canmgr  */
void CanMgr_Tacho_reception_cbk(void)
{

	g_Tacho_Missing_Status_bool = FALSE;
}

/* API is used to get status of TACHO timout  */
bool Swc_Tacho_CAN_Msg_Timeout_Staus(void)
{
	return (g_Tacho_Missing_Status_bool);
}

/* API is used to check the pre condition status such as Ignition on/off, HVSD/LVSD state  */
uint8_t Swc_Tachometer_Pre_Condition(void)
{
   uint8_t fl_Ign_Position_u8 = 0;
   uint8_t fl_Tacho_LVSD_check_u8;
   uint8_t fl_Tacho_HVSD_check_u8;
   bool fl_Precondition_Status;
 
  fl_Ign_Position_u8 = Sys_Service_Get_Ignition_State();

  fl_Tacho_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

  fl_Tacho_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

  if( (fl_Ign_Position_u8   == IGN_OFF) || 
      (fl_Tacho_LVSD_check_u8 == 0) ||
      (fl_Tacho_HVSD_check_u8 == 0) )
  {
     g_Precondition_Status = FALSE;
  }
  else
  {
      g_Precondition_Status = TRUE;
  }

  return g_Precondition_Status;
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
REVISION DATE        : 14-Oct-2022
CREATED / REVISED BY : Palani kumar R(palanikumar@niyatainfotech.com)
DESCRIPTION          : Tacho RPM Vs Pointer Angle table updated, liner interpolation added.
------------------------------------------------------------------------------------------------------------------------

**********************************************************************************************************************/
#endif /* ! TACHO_C */
