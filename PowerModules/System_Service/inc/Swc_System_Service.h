/* @file FILE NAME */
#ifndef SYSTEM_SERVICE_H
#define SYSTEM_SERVICE_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Balasubramaniyan (balasubramaniyan.s@niyatainfotech.com)
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
* 
*
*  File name                       : system_service.h
*  Version                         : V1.0.0
*  Micros supported                : 
*  Compilers supported             : COSMIC
*  Platforms supported             : 
*  Description                     : This file contains Macros, Typdef and Function Declarations for System serice
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/

#include "Swc_System_Service_Cfg.h"


/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/




/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/
/* perform integrity check when it is necessary */
/*#if ( FILE_NAME_H_VERSION != 0x0001 )
    #error "Incorrect version of header file used in filename.h!!!"
#endif*/
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

/*  
 * @brief: This macro is used to set the max speed
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
#define IGN_OFF   1

/*  
 * @brief: This macro is used to set the max speed
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
#define IGN_ON  (uint8_t) 0

/*
 * @brief: This macro is used to configure state of software reset upon excepiton states occurs
 * @Unit: N/A
 * @Resolution: N/A
 * @Range: STD_ON or STD_OFF
 * @Applicability: used to choose either software reset or while(1) to be used upon exception states
 */
#define ENABLE_SOFT_RESET_IN_EXCEPTION_STATE        STD_ON

#ifndef ENABLE_SOFT_RESET_IN_EXCEPTION_STATE
    #define ENABLE_SOFT_RESET_IN_EXCEPTION_STATE        STD_ON
    #error "ENABLE_SOFT_RESET_IN_EXCEPTION_STATE must be configured in Swc_System_Serivce.h file"
#endif    
/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef is used to define 
 * @param    
 * @return
 **/

typedef enum
{
	SYSTEM_SERVICE_NORMAL_VOLTAGE = 0,
	SYSTEM_SERVICE_HIGH_VOLTAGE,
    SYSTEM_SERVICE_LOW_VOLTAGE,
	System_service_STATE_MAX
}System_Service_State_Type_En;


typedef enum
{
    RAAA_SYSTEM_IN_NORMAL = 0,
    RAAA_SYSTEM_PREPARE_SLEEP,
    RAAA_SYSTEM_IN_LIMITED_MODE,
    RAAA_SYSTEM_IN_SLEEP_PREPARATION,
    RAAA_SYSTEM_IN_ENTER_SLEEP,
    RAAA_SYSTEM_IN_SLEEP_ENTRY
}Hero_RAAA_System_State_en;


void Sys_Service_Process_Ignition_State(void);
uint32_t Sys_Service_Voltage_Batt_Get_Status(void);


/*
 * @brief    This structure is used to define System service
 * @param    
 * @param    
 **/

typedef enum
{
   SYSTEM_SERVICE_SET = 0u,
   SYSTEM_SERVICE_NOT_SET,
}System_Service_List_Type_En;

typedef void (*NVM_Write_Fun_Ptr) (void);

typedef struct
{
    NVM_Write_Fun_Ptr NVM_WRITE_CBK;
}SLEEP_NVM_WRITE_CBK_ST;



/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/
void AppToBootJmp(void);


/*
* @brief    This API is used to System_Service_Init
* @param    
* @return  
* @invocation 
*/
void System_Service_Init(void);

/*
* @brief    This API is used to System_Service_Deint
* @param    
* @return  
* @invocation 
*/
void System_Service_Deint(void);
/*
* @brief    This API is used to System_Service_MainFunction
* @param    
* @return  
* @invocation 
*/
void System_Service_MainFunction(void);
/*
* @brief    This API is used to Sys_Service_Get_High_Voltage_State
* @param    
* @return  
* @invocation 
*/
uint8_t Sys_Service_Get_High_Voltage_State(void);
/*
* @brief    This API is used to Sys_Service_Get_Low_Voltage_State
* @param    
* @return  
* @invocation 
*/

uint8_t Sys_Service_Get_Low_Voltage_State(void);

void fsl_System_Service_lpadc_Periodic_Task(void *pvparameters);
/*
* @brief    This API is used to Sys_Service_Get_Ignition_State
* @param    
* @return  
* @invocation 
*/
uint8_t Sys_Service_Get_Ignition_State(void);


void Sys_Service_Shutdown_Process(void);

void Sys_Service_WakeUp_Process(void);

uint8_t Sys_Service_Ign_Off_To_ON_Status(void);

bool Sys_Get_Ready_Status(void);

void Enter_Critic_Section(void);

void Exit_Critic_Section(void);

void Get_Adc_Status(void);

void Swc_TripA_Timer_NVM_Write(void);

void Swc_TripB_Timer_NVM_Write(void);

void SNVS_LP_GPR_Write(void);

void SNVS_LP_GPR_Read(void);

bool System_Service_Is_Battery_Cycle_Detected(void);

void SuspendLVGL_ClearBuffer(void);

uint8_t SysService_Get_BatteryVoltageSts(void);

/*
* @brief    This API is used to process core expection states
* @param    NONE
* @return   NONE
* @invocation 
*/
void Core_Exception_Handler(void);
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : Major.Minor.Patch                                                
    REVISION DATE        : MONTH/DATE/YEAR                              
    CREATED / REVISED BY : Balasubramaniyan (balasubramaniyan.s@niyatainfotech.com)
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! FILE NAME */
