/* @file TTMGR_C */
#ifndef TTMGR_C
#define TTMGR_C
/*********************************************************************************************************************
*    DISCLAIMER
*    Copyright © , 2021 Niyata Infotech Pvt. Ltd. All rights reserved.
*********************************************************************************************************************/

/*********************************************************************************************************************
* @author              Author : Balaji pandurangan (balaji.pandurangan@niyatainfotech.com)
*********************************************************************************************************************/

/*********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N
**--------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : Abs_Telltale.c
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent
*  Description                     : This file contains the Implementation of Abs Tell-Tale
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
#include "TTMgr.h"
#include "Abs_Telltale.h"
#include "hal_stdtypes.h"
#include "CanMgr_cfg.h"
#include "Swc_System_Service.h"
#include "pin_mux.h"
#include "CanMgr.h"
/*********************************************************************************************************************
*                                             M A C R O   D E F I N I T I O N S
*********************************************************************************************************************/

/*********************************************************************************************************************
*                                          G L O B A L   V A R I A B L E    D E C L A R A T I O N S                                    
*********************************************************************************************************************/
/*
* @brief: This variable is used to store Abs value which needs to be displayed
  @Unit:  Uint8_t
  @Resolution: NA
  @Range: NA
  @Applicability: NIL
*/
uint8_t g_Abs_Displayable_Value_u8;

/*
* @brief: This variable is is used to check the pre condition status whether its true or false
  @Unit:  NA
  @Resolution: NA
  @Range: NA
  @Applicability: NIL
*/
static uint8_t g_Precondition_Status;

/*
* @brief: This variable is used to get ABS value from CAN manager
  @Unit:  NA
  @Resolution: NA
  @Range: NA
  @Applicability: NIL 
*/
float64 g_Abs_CanSignal_Value_f64;

/*
* @brief: This variable is used to get missing status for ABS telltale
  @Unit:  NA
  @Resolution: NA
  @Range: NA
  @Applicability: NIL 
*/
bool g_Abs_TElltale_Missing_Status_bool;
/*********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D	E F I N I T I O N
*********************************************************************************************************************/

/*
* @brief    This function is used to initialize the Tell-Tale Manager
* @param    None 
* @return   None
*/
void Abs_TT_init(void)
{
	g_Abs_Displayable_Value_u8 = 0;

	g_Abs_CanSignal_Value_f64 = 0;

	g_Abs_TElltale_Missing_Status_bool = TRUE;

}

/* This API is used to reinitialize the init variables */
void Abs_TT_Deinit(void)
{
  /* DO NOTHING */
}


/* API is used to Deactivate the peripherals */
void Abs_TT_DeActive(void)
{
  /* do nothing */
}


uint8_t Get_TimeoutStatus(void)
{
  uint8_t Get_Status =0;

  return Get_Status;
}


/*
* @brief    This function is used to initialize the Tell-Tale Manager
* @param    None 
* @return   None
*/
void Abs_TT_Active(void)
{
  uint8_t fl_Check_Ign_Mode;

  uint8_t fl_Check_Hvsd_flag;

  uint8_t fl_Check_Lvsd_flag;

  uint8_t fl_Get_Abs_Status;

  

    g_Precondition_Status = Swc_Abs_Pre_Condition();

 if(g_Precondition_Status == TRUE)
 {

      if(CAN_BUS_ON != App_Can_bus_off_Get_indication())
      {
        g_Abs_Displayable_Value_u8 = TT_ON;
      }
      else if(FALSE != g_Abs_TElltale_Missing_Status_bool)
      {
        g_Abs_Displayable_Value_u8 = TT_ON;

      }
      else
      {
        fl_Get_Abs_Status = CanMgr_Read_abs_telltale_status_0x205_s(&g_Abs_CanSignal_Value_f64);

      if(g_Abs_CanSignal_Value_f64 == THREE)
      {
        g_Abs_Displayable_Value_u8 = TT_ON;
       
      }
      else if(g_Abs_CanSignal_Value_f64 == ONE)
      {
        g_Abs_Displayable_Value_u8 = TT_FLASH;
      }
      else if((g_Abs_CanSignal_Value_f64 == ZER0) || (g_Abs_CanSignal_Value_f64 == TWO))
      {
        g_Abs_Displayable_Value_u8 = TT_OFF;
      }
      else
      {
        /* Do nothing */
      }

      }
  }
  else
  {
    g_Abs_Displayable_Value_u8 = TT_OFF;
  }
  
     TT_Mgr_Command( 0,  g_Abs_Displayable_Value_u8);
}

/* CANMGR_ABS_CRC_TRQ_0X142_TIMEOUT_CBK */
void CanMgr_ABS_Timeout_Callback_0x205(void)
{
	CanMgr_Abs_Timeout_Flag();
}

/* API is used to get ABS telltale timeout flag */
void CanMgr_Abs_Timeout_Flag(void)
{
	g_Abs_TElltale_Missing_Status_bool = TRUE;
}

/* API is used to get ABS callback on reception from CAN manager*/
void CanMgr_Abs_reception_cbk(void)
{
	g_Abs_TElltale_Missing_Status_bool = FALSE;
}

/* API is used to get ABS telltale status */
uint8_t Get_ABS_TT_Status(void)
{
  return g_Abs_Displayable_Value_u8;
}

/* API is used to get ABS precondition check such as ignition On/Off,LVSD/HVSD */
uint8_t Swc_Abs_Pre_Condition(void)
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
			REVISION DATE        : MONTH/DATE/YEAR
			CREATED / REVISED BY : Balaji pandurangan (balaji.pandurangan@niyatainfotech.com)
			DESCRIPTION          : Initial Version                        
 **********************************************************************************************************************/
#endif /* ! TTMGR_C */
