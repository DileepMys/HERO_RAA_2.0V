/* @file FILE NAME */
#ifndef TELL_TALE_SERVICE_REMAINDER_C
#define TELL_TALE_SERVICE_REMAINDER_C

/***********************************************************************************************************************
 *    DISCLAIMER
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
 *  File name                       : Swc_Service_Remainder.c
 *  Version                         : V1.0.2
 *  Micros supported                : Micro Independent
 *  Compilers supported             : Compiler Independent
 *  Platforms supported             : Platform Independent
 *  Description                     : This file contains implementations of Swc_Service_Remainder

 *  @bug
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/

#include "Swc_Service_Remainder.h"
#include "Abs_Telltale.h"
#include "fsl_gpio.h"
#include "hal_stdtypes.h"
#include "TTMgr.h"
#include "Swc_System_Service.h"
#include "Swc_Nvm_Handler.h"
#include "Swc_Speedometer.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to store the info about  next service on NVM
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display
 */
uint32_t g_NVM_Next_service_Odo;
/*
 * @brief: This variable is used to show the next service due information on the display
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint8_t g_Next_Service_Due;
/*
 * @brief: This variable is used to show the state of the service Icon
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint8_t g_NVM_Service_Icon_State;

/*
 * @brief: This variable is used to define the button press timer event info
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */

uint16_t g_Btn_Press_Timer_u16 = 0;

/*
 * @brief: This variable is used to give information about the position of the ignition switch
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint8_t g_Ign_Position_u8;

/*
 * @brief: This variable is used to give information about the Low voltage shutdown state
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint8_t g_Service_Remainder_LVSD_check_u8;

/*
 * @brief: This variable is used to give information about the High voltage shutdown state
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint8_t g_Service_Remainder_HVSD_check_u8;

/*
 * @brief: This variable is used to give information about the current odo value on the odometer
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint8_t g_Current_Odometer;

/*
 * @brief: This variable is used to give the timer for the service reminder
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint8_t Service_Reminder_Timer;

/*
 * @brief: This variable is used to give information about the current kilometer on the odometer
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint32_t ODO_Current_ODO_Km;

/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to store the flag for first service on NVM 
 * @Unit:  km
 * @Resolution: NIL
 * @Range: NIl
 * @Applicability: Odometer info on NVM
 */
uint8_t g_NVM_First_Time_Service_flag;

/*
 * @brief: This variable is used to show the EEPROM failure status if it fails the datas wont store on the NVM
 * @Unit:  km
 * @Resolution: NIL
 * @Range: NIl
 * @Applicability: Odometer info on NVM
 */
uint8_t g_EEPROM_Failure_u8;


/*
 * @brief: This variable is used to give the timer for the service reminder
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint8_t g_Service_Remainder_Timer_u8;

/*
 * @brief: This variable is used to give the next service information details on NVM
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint16_t g_NVM_Next_Service_Odometer;



/*
 * @brief: This variable is used to store the next service information details on RAM
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint16_t g_RAM_Next_Service_Odometer_u16;
/*
 * @brief: This variable is used store counter value used to calculate next service due upon Service Reset
 * @Unit:  uint16_t
 * @Resolution: 1
 * @Range: 1 to 333
 * @Applicability: Odo meter info display 
 */
uint16_t g_NVM_Next_Service_Reset_Cnt_u16;


/*
 * @brief: This variable is used to 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint8_t Set_Switch;

/*
 * @brief: This variable is used to give 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
int16_t g_Srv_Dist_Val;

/*
 * @brief: This variable is used to give the information about ignition on off state detection 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: TFT info display 
 */
bool g_Ign_Off_ON_Transition_Detected_bl = FALSE;

/*
 * @brief: This variable is used to give the information of set button status whether its pressed or not
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint8_t Set_Btn_Pressed = 0;

/*
 * @brief: This variable is used to give the information of button pressed status
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
bool g_Is_Button_Pressed = FALSE;

/*
 * @brief: This variable is used to give information for service reminder based on the due distance reached 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint16_t g_Service_Due_Distance_u16;

/*
 * @brief: This variable is used to give the information of resetting elapsed time of the due distance 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: NIL
 * @Applicability: Odo meter info display 
 */
uint16_t g_Is_Due_Distance_Reset_Time_Elasped = 0;

/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/* To initialize the  function to be called in the main function*/
void TT_Service_Remainder_Init(void)
{
   g_Btn_Press_Timer_u16 = 0;

    g_RAM_Next_Service_Odometer_u16 = 0;

   g_Srv_Dist_Val = 0;

   ODO_Current_ODO_Km = 0;

   g_Ign_Off_ON_Transition_Detected_bl = TRUE;

   g_Is_Due_Distance_Reset_Time_Elasped = 0;

   /* read service remainder due distance value from NVM */
   swc_Service_Remainder_Data_NVM_Read();

}

/* Function is used to reset the gear position init variable  */ 
void TT_Service_Remainder_DeInit(void)
{
   g_Btn_Press_Timer_u16 = 0;

   g_Srv_Dist_Val = 0;

   g_Ign_Off_ON_Transition_Detected_bl = FALSE;

   g_Is_Due_Distance_Reset_Time_Elasped = 0;

    /* Write service remainder due distance value from NVM */
   swc_Service_Remainder_Data_NVM_Write();
}

/* Function is used to initialize the gear position peripherals */
void TT_Service_Remainder_Activate(void)
{
   /* do nothing */
}

/* Function is used to reset the gear position peripherals */
void TT_Service_Remainder_DeActivate(void)
{
   /* do nothing */
}

/* Function is used to execute the service reminder main functions  */
void TT_Service_Remainder_MainFunction(void)
{
   bool fl_EEPROM_Failure_bl = FALSE;

   uint8_t fl_CAN_Bus_State_u8 = 1;

   uint16_t fl_Srv_Dist_Val_temp;

   uint8_t fl_Pre_Condition_state = FALSE;
   uint8_t fl_Ser_Remainder_Ret =0;

   fl_Pre_Condition_state = TT_Service_Remainder_Pre_Condition();

   ODO_Current_ODO_Km = GET_ODO_KM;

   if(g_Is_Due_Distance_Reset_Time_Elasped <= 3000)
   {

      Swc_Service_Remainder_Reset_Button_Sense();

      Service_Remainder_Reset_Logic();

      g_Is_Due_Distance_Reset_Time_Elasped = g_Is_Due_Distance_Reset_Time_Elasped + 100;
   }
   else
   {
      /* reset  status flag */
      g_Ign_Off_ON_Transition_Detected_bl = FALSE;

      g_Is_Due_Distance_Reset_Time_Elasped = 0;
   }


   if(fl_Pre_Condition_state == TRUE)
   {
      /* Get CAN Bus current status */
      fl_CAN_Bus_State_u8 = GET_CAN_BUS_STATUS();

      if(fl_CAN_Bus_State_u8 != CAN_BUS_OFF)
      {

         /* Get CAN Msg time out status */      
         if(Swc_Speedo_Get_Msg_TimeOut_Staus() == FALSE)
         {
            /* Get NVM Error status*/
            fl_EEPROM_Failure_bl = Swc_Get_ODO_NVM_Error_Status();

            if(fl_EEPROM_Failure_bl == FALSE)
            {
                  g_Srv_Dist_Val = g_NVM_Next_service_Odo - ODO_Current_ODO_Km;

               if ( ((g_NVM_Next_service_Odo == ODO_Current_ODO_Km) && (ODO_Current_ODO_Km != 0))||
               ((g_RAM_Next_Service_Odometer_u16 == ODO_Current_ODO_Km) && (ODO_Current_ODO_Km != 0)))
               {
               g_RAM_Next_Service_Odometer_u16 = ODO_Current_ODO_Km + 3000;

               }
               if(g_Srv_Dist_Val >= 0)
               {
                  fl_Srv_Dist_Val_temp = (abs(g_Srv_Dist_Val))% NEXT_SERVICE_DUE;
               }
               else
               {
                  fl_Srv_Dist_Val_temp = 3000 - ((abs(g_Srv_Dist_Val))% NEXT_SERVICE_DUE);
               }

               g_Service_Due_Distance_u16 = fl_Srv_Dist_Val_temp;

               if(g_NVM_First_Time_Service_flag == 1)
               {
                  if((g_Srv_Dist_Val <= FIRST_SERVICE_REMAINDER_BLINK_VAL)&&
                  (g_Srv_Dist_Val > SERVICE_REMAINDER_ON_VALUE))
                  {
                     g_NVM_Service_Icon_State = Blink;
                  }
                  else
                  {
                     if(g_Srv_Dist_Val <= SERVICE_REMAINDER_ON_VALUE)
                     {

                           if((fl_Srv_Dist_Val_temp <= SERVICE_REMAINDER_BLINK_VAL) &&
                           (fl_Srv_Dist_Val_temp > SRV_REMAINDER_ON_VALUE))
                           {

                           g_NVM_Service_Icon_State = Blink;
                           }
                           else
                           {
                              g_NVM_Service_Icon_State = ON;
                           }
                     }
                     else
                     {
                        g_NVM_Service_Icon_State = OFF;
                     }
                  }
               }
               else
               {
                  if((g_Srv_Dist_Val <= SERVICE_REMAINDER_BLINK_VAL) &&
                  (g_Srv_Dist_Val > SERVICE_REMAINDER_ON_VALUE))
                  {
                     g_NVM_Service_Icon_State = Blink;
                  }
                  else
                  {
                     if(g_Srv_Dist_Val <= SERVICE_REMAINDER_ON_VALUE)
                     {

                        if((fl_Srv_Dist_Val_temp <= SERVICE_REMAINDER_BLINK_VAL) && (fl_Srv_Dist_Val_temp > SRV_REMAINDER_ON_VALUE))
                        {
                           g_NVM_Service_Icon_State = Blink;
                        }
                        else
                        {
                           g_NVM_Service_Icon_State = ON;
                        }

                        
                     }
                     else
                     {
                        g_NVM_Service_Icon_State = OFF;
                     }

                  }

               }
            }
            else
            {
               /* NVM ERROR */
               g_Service_Due_Distance_u16 = (uint16_t)0xFFFF;
            }
         }  
      }

   }

   if(g_NVM_Service_Icon_State == Blink)
   {
      TT_Mgr_Command(Service_Remainder,TT_FLASH);

   }    
   else if(g_NVM_Service_Icon_State == ON)
   {

      TT_Mgr_Command(Service_Remainder,TT_ON);
   }
   else if(g_NVM_Service_Icon_State == OFF)
   {

      TT_Mgr_Command(Service_Remainder,TT_OFF);
   }

}
        
void Service_Remainder_Reset_Logic(void)
{

	uint8_t fl_NVM_Service_Icon;
	uint8_t fl_Pre_To_Current_Ignition_Mode = 1;
	uint8_t g_Service_Remainder_LVSD_check_u8;
	uint8_t g_Service_Remainder_HVSD_check_u8;
	uint8_t Clear_Service_Remainder_Timer;
	uint8_t fl_NVM_Service_Odometer;

   /* ignition status */
   if((g_Ign_Off_ON_Transition_Detected_bl == TRUE) && (Set_Btn_Pressed == 1))
   {
      /* clear button status */
      Set_Btn_Pressed = 0;

      if((g_NVM_Service_Icon_State != OFF) && (g_EEPROM_Failure_u8 == 0) )
      {
         /*Check KMph or Mph Selection*/
         if(((SPEED_KM == CURRENT_SPEED_UNIT_SELECTION) && (ODO_Current_ODO_Km < MAXIMUM_ODOMETER_KM_VALUE)) ||
         ((SPEED_MH == CURRENT_SPEED_UNIT_SELECTION) && (ODO_Current_ODO_Km < MAXIMUM_ODOMETER_KM_VALUE)))
         {
            if( ODO_Current_ODO_Km > g_NVM_Next_service_Odo - SERVICE_DUE_BLINK_TO_ON_HYST)
            {
               g_NVM_Next_service_Odo = (NEXT_SERVICE_DUE * g_NVM_Next_Service_Reset_Cnt_u16)+(SERVICE_DUE_BLINK_TO_ON_HYST);

               g_NVM_Next_Service_Reset_Cnt_u16++;

            }
            
            /* Clear Service remainder TT status*/
            g_NVM_Service_Icon_State = OFF;

            /* First service is done,  clear that flag */
            if(g_NVM_First_Time_Service_flag == 1)
            {
               g_NVM_First_Time_Service_flag = 0;
            }
            else
            {
               /* do nothing */
            }
         }

         /* Write next service details in NVM */
         swc_Service_Remainder_Data_NVM_Write();
      }

      /* Reset ign ON to OFF transition detected flag */
      g_Ign_Off_ON_Transition_Detected_bl = FALSE;
   }
   else
   {
       /* do nothing */
   }

   if(g_NVM_Service_Icon_State == Blink)
   {
      TT_Mgr_Command(Service_Remainder,TT_FLASH);
   }
   else if(g_NVM_Service_Icon_State == ON)
   {
      TT_Mgr_Command(Service_Remainder,TT_ON);

   }  
   else
   {
      TT_Mgr_Command(Service_Remainder,TT_OFF);

   } 

}

/* API is used to read the service remainder data from NVM  */
void swc_Service_Remainder_Data_NVM_Read (void)
{
   uint8_t fl_Service_Due_Distance_Var[4] = {0,0,0,0};

   NVM_Byte_Read_Allocation(NVM_SERVICE_DUE_VALUE,(uint8_t*)&g_NVM_Next_service_Odo);

   NVM_Byte_Read_Allocation(NVM_SERVICE_REMAINDER_AUXILIARY_DATA,&fl_Service_Due_Distance_Var[0]);

   /* range 1 to 333 */
   g_NVM_Next_Service_Reset_Cnt_u16 = (fl_Service_Due_Distance_Var[0] << 8) | (fl_Service_Due_Distance_Var[1]);

   /* first time servie flag  0 or 1*/
   g_NVM_First_Time_Service_flag = fl_Service_Due_Distance_Var[2];

   /* TT ICON state ON/OFF/BLINK */
   g_NVM_Service_Icon_State = fl_Service_Due_Distance_Var[3];
}

/* API is used to define the service reminder reset button status */
void Swc_Service_Remainder_Reset_Button_Sense(void)
{
   uint8_t fl_Btn_Staus_u8 = 0;

   /* read set buttton status */
   fl_Btn_Staus_u8 =  GPIO_PinRead(GPIO10,6);

   /* button pressed */
   if(fl_Btn_Staus_u8 == 1 &&(g_Is_Button_Pressed != TRUE))
   {
      g_Btn_Press_Timer_u16 = g_Btn_Press_Timer_u16 + 100;
      /* wait for debounce completion */
      if(g_Btn_Press_Timer_u16 == 100)
      {
            g_Is_Button_Pressed = TRUE;
      }
   }
   else if((g_Is_Button_Pressed == TRUE) && (fl_Btn_Staus_u8 == 1))
   {
     
      g_Btn_Press_Timer_u16 = g_Btn_Press_Timer_u16 + 100;

      if(g_Btn_Press_Timer_u16 >= 3000)
      {
         /* set button pressed for 3sec */
         Set_Btn_Pressed = 1;
      }
   }
   else
   {
      Set_Btn_Pressed = 0;
      g_Btn_Press_Timer_u16 = 0;
      g_Is_Button_Pressed = 0;
   }
}

/* API is used to write the service reminder data in NVM */
void swc_Service_Remainder_Data_NVM_Write(void)
{

   uint8_t fl_Service_Due_Distance_Var[4] = {0,0,0,0};
   bool fl_NVM_Status_bl = TRUE;

   /* Get NVM Status */
   fl_NVM_Status_bl = Swc_Get_NVM_Status();

   if(fl_NVM_Status_bl == FALSE)
   {

   /* range 1 to 333 */
   /* 2nd byte of next service reset counter value*/
   fl_Service_Due_Distance_Var[0] = (g_NVM_Next_Service_Reset_Cnt_u16 >> 8) & 0x00FF;

   /* 1st byte of next service reset counter value*/
   fl_Service_Due_Distance_Var[1] = g_NVM_Next_Service_Reset_Cnt_u16 & 0x00FF;

    /* first time servie flag  0 or 1*/
   fl_Service_Due_Distance_Var[2] = g_NVM_First_Time_Service_flag;

    /* TT ICON state ON/OFF/BLINK */
   fl_Service_Due_Distance_Var[3] = g_NVM_Service_Icon_State;

   /* service due distance max 999999 */
  NVM_Byte_Write_Allocation(NVM_SERVICE_DUE_VALUE,(uint8_t*)&g_NVM_Next_service_Odo);

   NVM_Byte_Write_Allocation(NVM_SERVICE_REMAINDER_AUXILIARY_DATA,&fl_Service_Due_Distance_Var[0]);

   }
}

/* API is used to check the pre condition such as ignition position ,LVSD/HVSD state */   
bool TT_Service_Remainder_Pre_Condition(void)
{

   uint8_t fl_Precondition_Status;

   g_Ign_Position_u8 = SYS_SERVICE_GET_IGNITION_STATE;

   g_Service_Remainder_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

   g_Service_Remainder_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

  if((g_Ign_Position_u8 == IGN_OFF) ||
      (g_Service_Remainder_LVSD_check_u8 == SET) || 
      (g_Service_Remainder_HVSD_check_u8 == SET))
  {
     fl_Precondition_Status = FALSE;
  }
  else
  {
      fl_Precondition_Status = TRUE;
  }

  return fl_Precondition_Status;
}

/* API is used to get Tell Tale staus for service remainder */
uint8_t Swc_Service_Remainder_Get_TT_Status(void)
{

   return (g_NVM_Service_Icon_State);
}

/* API is used to get due distance for service reminder */
uint16_t Swc_Service_Remainder_Get_Due_Distance(void)
{

return g_Service_Due_Distance_u16;
}

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.2
    REVISION DATE        : 04/06/2023        
    CREATED / REVISED BY : palani kumar R (palanikumar@niyatainfoteh.com)      
    DESCRIPTION          : NVM Write removed from happening in IGN Cycle , implemented immediate upon SERVICE RESET    

    REVISION NUMBER      : V1.0.1
    REVISION DATE        : 12/10/2022        
    CREATED / REVISED BY : palani kumar R (palanikumar@niyatainfoteh.com)      
    DESCRIPTION          : Service remainder issues addressed    

    REVISION NUMBER      : V1.0.0
    REVISION DATE        : 05/10/2022        
    CREATED / REVISED BY : Balsubramaniyan (balasubramaniayan.s@niyatainfoteh.com)      
    DESCRIPTION          : Initial version 
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! TELL_TALE_SERVICE_REMAINDER_C */
