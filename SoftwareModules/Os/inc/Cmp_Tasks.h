/* @file FILE NAME */
#ifndef CMP_TASK_H
#define CMP_TASK_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Name (mail-id)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : 
*  Version                         : 
*  Micros supported                : 
*  Compilers supported             : 
*  Platforms supported             :                 
*  Description                     : This header file contains the declarations of 
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include"main_init.h"
#include "Cmp_Init.h"
#include"pin_mux.h"
#include "stdbool.h"
#include "MIMXRT1172.h"
#include "fsl_flexcan.h"
/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/
#if SYSTEM_1
# include "system_1.h"
#elif SYSTEM_2
# include "system_2.h"
#elif SYSTEM_3
#endif


/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
/**
* @brief This macro is used to define 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/



#define RX_MESSAGE_BUFFER_NUM (0)
#define TX_MESSAGE_BUFFER_NUM (0)
#define DLC                   (8)

extern unsigned char g_Check_Telltale_status;


#define DEMO_LPADC_BASE         LPADC1
#define ADC_BASE2         LPADC2
/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef is used to define 
 * @param    
 * @return
 **/


/*
 * @brief    This typedef enum is used to define 
 * @param    
 * @param
 **/


/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/


/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to 
* @param    
* @return  
* @invocation 
*/
void Cmp_Tasks_Create(void);

void Speedo_Periodic_Task(void *pvparameters);

/*
* @brief    This API is used to 
* @param    
* @return  
* @invocation 
*/

void Odometer_Periodic_Task(void *pvparameters);

void TT_Mgr_Periodic_Task(void *pvparameters);

void Fuel_Guage_Periodic_Task(void *pvparameters);

void Service_Remainder_Periodic_Task(void *pvparameters);


void Fog_Lamp_Periodic_Task(void *pvparameters);

void TT_Oil_Pressure_Periodic_Task(void *pvparameters);

void TFT_Illum_Periodic_Task(void *pvparameters);

/*
* @brief    This API is used to 
* @param    
* @return  
* @invocation 
*/
void ABS_Periodic_Task(void *pvparameters);

void DTE_Periodic_Task(void *pvparameters);


/*
* @brief    This API is used to 
* @param    
* @return  
* @invocation 
*/
void AFE_Periodic_Task(void *pvparameters);

void Trip_Timer_Periodic_Task(void *pvparameters);

void GUI_Tacho_Period_Task(void *pvparameters);

void RTC_Periodic_Task(void *pvparameters);

void Trip_Avg_Speed_Periodic_Task(void *pvparameters);

void MIL_TT_Periodic_Task(void *pvparameters);

void fsl_lpadc_Periodic_Task(void *pvparameters);

void Sys_Service(void *pvparameters);

void NVM_Handler_Task(void *pvparameters);

void Gear_Position_Periodic_Task(void *pvparameters);

void HMI_Handler_Task(void *pvparameters);

void Button_Mgr(void *pvparameters);

void IFE_Periodic_Task(void *pvparameters);

void AFT_Periodic_Task(void *pvparameters);

void Dio_Handler_Periodic_Task(void *pvparameters);

void CanGateway_Status_Periodic_Task(void *pvparameters);

 void ALS_100ms_Periodic_Task(void *pvparameters);

 void Lvgl_Sys_Tick(void *pvparameters);

 void UART_Mgr(void *pvparameters);
void UDS_10ms_Periodic_Task(void *pvparameters);

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
***********************************************************************************************************************
    REVISION NUMBER      : Major.Minor.Patch                                                
    REVISION DATE        : MONTH/DATE/YEAR                              
    CREATED / REVISED BY : NAME (EMAIL-ID)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! CMP_TASK_H */
