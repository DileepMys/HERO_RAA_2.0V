/* @file FILE NAME */
#ifndef DIO_HANDLER_C
#define DIO_HANDLER_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : palani kumar (palanikumar@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : Dio Handler.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : COSMIC
 *  Platforms supported             : Platform Independent
 *  Description                     : This file contains implementations of gear_position

 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "Dio_Handler.h"
#include "stdint.h"
#include "Cmp_Init.h"
#include "fsl_gpio.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*  
 * @brief: This macro is used to set the max speed
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
#define ACTIVE_HIGH       1

/*  
 * @brief: This macro is used to set the max speed
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
#define ACTIVE_LOW        0
/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to know the current status of the pin
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL
 */
uint8_t g_Pin_Current_Status;

/*
 * @brief: This variable is used to the timer update
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL 
 */
uint8_t g_Debounce_timer_u8;
/*
 * @brief: This variable is used to know the status of the dio pin
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL
 */
DIO_PIN_HANDLER_STATE_EN g_Dio_Pin_State;
/*
 * @brief: This variable is used to know the pin activate status 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL: 
 */
uint8_t g_Pin_Active_State;
/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

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
/* API is used to initialize the variables with default values */
void Dio_Handler_Init(void)
{
  /* Default state to check pin status */
  g_Dio_Pin_State = DIO_CHECK_PIN_STATUS;

  g_Debounce_timer_u8 = 0;
}

/* API is used to activate  the initial peripheral variables */
void Dio_Handler_Activate(void)
{

  /* do nothing */
}
/* API is used to reset the peripheral variables */
void Dio_Handler_Deactivate(void)
{

  /* do nothing */
}


/* API is used to activate  the initial peripheral variables */
void Dio_Handler_Mainfunction(void)
{
  uint8_t fl_Read_Pin_Status;

  /* Read pin status */
  fl_Read_Pin_Status = GPIO_PinRead(BOARD_INITPINS_DI_IGN_MCU_IN_GPIO,BOARD_INITPINS_DI_IGN_MCU_IN_GPIO_PIN);

  switch (g_Dio_Pin_State)
  {
  case DIO_CHECK_PIN_STATUS:

            /* check pin status against active pin status */
            if(fl_Read_Pin_Status == ACTIVE_HIGH)
            {
                /* Change state to pin high detection state */
                g_Dio_Pin_State = DIO_PIN_HIGH_DETECTION;
            }
            else
            {
                /* Change state to pin high detection state */
                g_Dio_Pin_State = DIO_PIN_LOW_DETECTION;
            }

    break;

  case DIO_PIN_HIGH_DETECTION: 

          /* check pin status remains high then precess debounce */
          if(fl_Read_Pin_Status == ACTIVE_HIGH)
          { 
            /* change state to debounce process */
            g_Dio_Pin_State = DIO_PROCESS_DEBOUNCE_STATE;

            g_Pin_Active_State = ACTIVE_HIGH;
          }
          else
          {
            /* change state to check pin status */
            g_Dio_Pin_State = DIO_CHECK_PIN_STATUS;
          }  
    break;

  case DIO_PIN_LOW_DETECTION: 

          /* check pin status remains high then precess debounce */
          if(fl_Read_Pin_Status == ACTIVE_LOW)
          { 
            /* change state to debounce process */
            g_Dio_Pin_State = DIO_PROCESS_DEBOUNCE_STATE;

            g_Pin_Active_State = ACTIVE_LOW;
          }
          else
          {
            /* change state to check pin status */
            g_Dio_Pin_State = DIO_CHECK_PIN_STATUS;
          }  
    break; 

  case DIO_PROCESS_DEBOUNCE_STATE: 

          /* check pin status remains high then precess debounce */
          if((fl_Read_Pin_Status == ACTIVE_LOW) && (g_Pin_Active_State == ACTIVE_LOW) ||
             (fl_Read_Pin_Status == ACTIVE_HIGH) && (g_Pin_Active_State == ACTIVE_HIGH)) 
          { 
              /* increment the debounce timer */
              g_Debounce_timer_u8 = g_Debounce_timer_u8 + DIO_HANDLER_TASK_RATE;

              if(g_Debounce_timer_u8 >= PIN_READ_DEBOUNCE_COUNTER)
              {
                  /* pin active detected, confirmed */
                  if(fl_Read_Pin_Status == ACTIVE_LOW)
                  {
                    /* change state to check active low detection state */
                    g_Dio_Pin_State = DIO_PIN_LOW_CONFIRMATION;
                  }
                  else if(fl_Read_Pin_Status == ACTIVE_HIGH)
                  {
                    /* change state to check active HIGH detection state */
                    g_Dio_Pin_State = DIO_PIN_HIGH_CONFIRMATION;
                  }
                  else
                  {
                    /*do nothing*/
                  }

                  g_Debounce_timer_u8 = 0;
              }
          }
          else
          {
            /* change state to check pin status */
            g_Dio_Pin_State = DIO_CHECK_PIN_STATUS;

            g_Debounce_timer_u8 = 0;
          }     
    break; 

  case DIO_PIN_HIGH_CONFIRMATION:

          /* Confirm pin status is high */
          g_Pin_Current_Status = ACTIVE_HIGH;

          /* change state to check pin status */
          g_Dio_Pin_State = DIO_CHECK_PIN_STATUS;

    break;

  case DIO_PIN_LOW_CONFIRMATION:

          /* Confirm pin status is LOW */
          g_Pin_Current_Status = ACTIVE_LOW;

          /* change state to check pin status */
          g_Dio_Pin_State = DIO_CHECK_PIN_STATUS;

    break;

  default:
          /* change state to check pin status */
          g_Dio_Pin_State = DIO_CHECK_PIN_STATUS;  
    break;
  }
}

/* API is used to read the pin status of the Dio handler */
uint8_t Dio_Handler_Read_Pin_Status(void)
{
    return (g_Pin_Current_Status);
}
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                          
    REVISION DATE        : 2/19/2022 
    CREATED / REVISED BY : palani kumar (palanikumar@niyatainfotech.com)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! ADC_C*/
