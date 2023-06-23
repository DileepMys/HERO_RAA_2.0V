/* @file FILE NAME */
#ifndef GEAR_POSITION_C
#define GEAR_POSITION_C

/***********************************************************************************************************************
 *   DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Balasubramaniyan (balasubramaniyan.s@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : Gear position.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : J link
 *  Platforms supported             : Platform Independent
 *  Description                     : This file contains implementations of gear_position

 *  @bug
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/

#include "SWC_Gear_position.h"
#include "hal_stdtypes.h"
#include "fsl_gpio.h"
#include "Swc_System_Service.h"
#include "pin_mux.h"
#include "CanMgr_cfg.h"
#include "Swc_Service_Remainder.h"
#include "Abs_Telltale.h"
#include "TTMgr.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*  
 * @brief: This macro is used to get the status of the ignition off state
 * @Unit: N/A  
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: N/A 
 */
#define IGN_OFF  1

/*  
 * @brief: This macro is used to get the status of the ignition on state
 * @Unit: N/A  
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: N/A  
 */
//#define IGN_ON    0


/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */


/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This enum is used to get the gear shift position state
 * @Unit: N/A  
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: N/A 
 */
GEAR_SHIFT_ADVISORY_LIST_EN g_CAN_Gear_shift_advisory_u8;
/*
 * @brief: This enum is used to show the gear shift / no shift position state on the dispaly 
 * @Unit: N/A  
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: N/A 
 */
GEAR_SHIFT_IND_DISPLAY_LIST_EN g_Gear_Shift_Ind_Display;

/*
 * @brief: This variable is used to know the status of the telltale missing status
 * @Unit: N/A  
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: N/A 
 */
uint8_t g_Gear_TElltale_Missing_Status_bool;


/*
 * @brief: This variable is used to get the status of telltale missing status during gear shift
 * @Unit: N/A  
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: N/A 
 */
uint8_t g_GearShift_TElltale_Missing_Status_bool;

/*
 * @brief: This macro is used to know the exact number of the gear position state 
 * @Unit: N/A  
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: N/A 
 */
GEAR_POS_LIST_EN g_Gear_Pos_Ind_Display;

/*
 * @brief: This variable is used to pass the gear position information the CAN unit
 * @Unit: Float 
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: N/A 
 */
float64 g_gear_Position_CAN_64;

/*
 * @brief: This macro is used to know the gear advisory 
 * @Unit: Float
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: N/A 
 */
float64 g_gear_Advisory_CAN_64;
/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    This function processes the 
 * @param    
 * @return   
 */

/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/* To initialize the  function to be called in the main function*/
void gear_position_Init(void)
{

  g_CAN_Gear_shift_advisory_u8 = GEAR_NO_SHIFT_ADVISORY; 

  g_Gear_Shift_Ind_Display = NO_DISPLAY;

  g_Gear_Pos_Ind_Display = GEAR_NEUTRAL;

  g_Gear_TElltale_Missing_Status_bool = TRUE;

  g_GearShift_TElltale_Missing_Status_bool = TRUE;

  g_gear_Position_CAN_64 = 0;

  g_gear_Advisory_CAN_64 = 0;
}

/* API is used to reset the initial values of the init variables */ 
void gear_position_DeInit(void)
{
   /* do nothing */
}

/* API is used to activate the peripherals */
void gear_position_Activate(void)
{
   /* do nothing */
}

/* API is used to de-activate the peripherals */
void gear_position_DeActivate(void)
{
   /* do nothing */
}

/* API is used to provide information as this is day mode */
void gear_position_MainFunction(void)
{
   /* LOCAL VARIABLE DECLARATION */
   bool fl_Pre_Condition_Ck_State = FALSE;
   uint8_t fl_CAN_Gear_Pos_Sensor_u8 = 0;
   uint8_t fl_CAN_Bus_State_u8 = 0;
   uint8_t fl_CAN_Time_status_u8 = 0;
   uint8_t fl_CAN_gear_pos_check_status_u8;

   uint8_t fl_Advisory_value = NO_DISPLAY;



   /* Get pre condition status */
   fl_Pre_Condition_Ck_State = Swc_Check_Pre_Condition();
   

   /* Process if pre condition statisfied */
   if(fl_Pre_Condition_Ck_State == TRUE)
   {
      /* Get CAN Bus current status */
       fl_CAN_Bus_State_u8 = GET_CAN_BUS_STATUS();

      /* Get CAN Msg time out status */
      if(FALSE ==  g_GearShift_TElltale_Missing_Status_bool)
      {

         if((fl_CAN_Bus_State_u8 == CAN_BUS_ON) && (g_GearShift_TElltale_Missing_Status_bool == FALSE))
         { 
            /* get current gear positon from CAN Msg (0x131) */
            fl_CAN_Gear_Pos_Sensor_u8 = CanMgr_Read_gear_position_sensor_0x131_s(&g_gear_Position_CAN_64);

            /* check if received gear positon is valid  (0 to 6) */
            if(g_gear_Position_CAN_64 <= GEAR_POS_6)
            {
               /* get gear advisory status from CAN signal */
               CanMgr_Read_gear_shift_advisory_0x131_s(&g_gear_Advisory_CAN_64);

               fl_CAN_gear_pos_check_status_u8 = (uint8_t)g_gear_Advisory_CAN_64;


               if(g_gear_Position_CAN_64 != 0u) 
               {
               
                  /* process state machine */
                  switch (fl_CAN_gear_pos_check_status_u8)
                  {
                     case GEAR_NO_SHIFT_ADVISORY:
                     
                        /* Not valid gear shift advisory requested */
                        fl_Advisory_value = NO_DISPLAY;

                        break;
                     case GEAR_SHIFT_UP_ADVISORY:

                        /* do process if gear advisory received for up signal indication */
                        if(g_Gear_Pos_Ind_Display < GEAR_POS_6)
                        {
                           /* Transmit the Gear up indication to HMI */ 
                           fl_Advisory_value = DISPLAY_GEAR_UP;

                        }
                        else
                        {

                           fl_Advisory_value = NO_DISPLAY;
                           
                        }

                        break;
                     case GEAR_SHIFT_DOWN_ADVISORY:

                        /* do process if gear advisory received for signal signal indication */
                        if(g_Gear_Pos_Ind_Display > GEAR_POS_1)
                        {
                           /* Transmit the Gear up indication to HMI */ 
                           fl_Advisory_value = DISPLAY_GEAR_DOWN;

                        }
                        else
                        {

                           fl_Advisory_value = NO_DISPLAY;

                        }

                        break;
                     default:
                        /* Not valid gear shift advisory requested */
                        fl_Advisory_value = NO_DISPLAY;
                        break;
                  }  
                  
               }
               else
               {

                  /* Not valid gear shift advisory requested */
                  fl_Advisory_value = NO_DISPLAY;

               }

               /* store gear positon sensor valur in gear indication display value*/
               g_Gear_Pos_Ind_Display = g_gear_Position_CAN_64;
         
            }    
            else
            {
               /* gear postion 7 meas blink 1hz with 50% duty cycle */
               g_Gear_Pos_Ind_Display = GEAR_POS_INVALID;

               /* Not valid gear shift advisory requested */
               fl_Advisory_value = NO_DISPLAY;

            }
         
         }
         else
         {
            /* gear postion 7 meas blink 1hz with 50% duty cycle */
            g_Gear_Pos_Ind_Display = GEAR_POS_INVALID;
         }
      }   
      else
      {
          fl_Advisory_value = NO_DISPLAY;
           g_Gear_Pos_Ind_Display = GEAR_POS_INVALID;
      }
   }  
   else
   {

      /* gear postion 7 meas blink 1hz with 50% duty cycle */
      g_Gear_Pos_Ind_Display = GEAR_POS_INVALID;

      /* Not valid gear shift advisory requested */
      fl_Advisory_value = NO_DISPLAY;

   }   

   g_Gear_Shift_Ind_Display = fl_Advisory_value; 

     if(g_Gear_Pos_Ind_Display == GEAR_POS_INVALID)
   {
      TT_Mgr_Command(Gear_Position,TT_FLASH);
   }
   else 
   {
      TT_Mgr_Command(Gear_Position,TT_NO_ACTION);
      
   }

}

/* API is used to provide information as this is day mode */
uint8_t Swc_Check_Pre_Condition(void)
{
   bool fl_Precondition_Status = FALSE;
   
   uint8_t fl_Gear_HVSD_check_u8;

   uint8_t fl_Ign_Position_u8;

   uint8_t fl_Gear_LVSD_check_u8;

   uint8_t fl_Gear_Voltage_check_u8 = 0;
 
  fl_Ign_Position_u8 = Sys_Service_Get_Ignition_State();

  fl_Gear_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

  fl_Gear_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

  if( (fl_Ign_Position_u8   == IGN_OFF) || 
      (fl_Gear_LVSD_check_u8 == SET) || 
      (fl_Gear_HVSD_check_u8 == SET) )
  {
     fl_Precondition_Status = FALSE;
  }
  else
  {
      fl_Precondition_Status = TRUE;
  }

  return fl_Precondition_Status;
}


/*  This Function is used to get gear position number and returns to HMI */
uint8_t Get_Gear_Position_Number_Indication(void)
{
    /* Transmit the Gear Position Data to HMI */
      return (g_Gear_Pos_Ind_Display);
}

/* Function is used transfer the gear up indication to HMI */
uint8_t Get_Gear_Position_Shift_Advisory_Indication(void)
{
       /* Transmit the Gear up indication to HMI */ 
       return (g_Gear_Shift_Ind_Display);
}

/* Function is used to get time out call back information of the gear position */
void CanMgr_Gear_Timeout_Callback_0x130(void)
{

	CanMgr_Gear_Position_Timeout_Flag();
}

/* Function is used to get time out call back information of the gear position */
void CanMgr_Gear_Position_Timeout_Flag(void)
{

	g_GearShift_TElltale_Missing_Status_bool = TRUE;
}

/* Function is used to get the gear position status */
void CanMgr_Gear_Position_reception_cbk(void)
{

	g_GearShift_TElltale_Missing_Status_bool = FALSE;
}

/* Function is used to get time out call back information of the gear shift */
void CanMgr_GearShift_Timeout_Callback_0x130(void)
{

	CanMgr_Gear_Position_Timeout_Flag();
}

/* Function is used to send gear shift timeout flag to CAN as a input */
void CanMgr_Gear_Shift_Timeout_Flag(void)
{

	g_GearShift_TElltale_Missing_Status_bool = TRUE;
}


void CanMgr_Gear_Shift_reception_cbk(void)
{

	g_GearShift_TElltale_Missing_Status_bool = FALSE;
}



/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                          
    REVISION DATE        : 2/19/2021        
    CREATED / REVISED BY : Balsubramaniyan (balasubramaniayan.s@niyatainfoteh.com)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! GEAR_POSITION_C */
