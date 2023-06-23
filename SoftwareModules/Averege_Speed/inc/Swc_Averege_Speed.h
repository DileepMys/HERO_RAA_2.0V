/* @file AVERAGE_SPEED_H */
#ifndef AVERAGE_SPEED_H
#define AVERAGE_SPEED_H

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
*  File name                       : Average speed cfg
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : J-Link
*  Platforms supported             : Platform independent
*  Description                     : This file contains Macros, Typdef and Function Declarations for gear_position files
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/

#include "Swc_Average_Speed_cfg.h"
#include "stdint.h"
#include "hal_stdtypes.h"
#include "Swc_Trip_Timer_cfg.h"
/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
/*
 * @brief    This structure is used to define for Trip timer
 * @param    Nil 
 **/
typedef struct 
{
    uint8_t g_Average_Speed_Ret_Triger_Setting;
    uint8_t g_Average_Speed__SW_Ret_Cmd;
    uint32_t g_Average_Speed_KM;
    uint8_t g_Displayed_Avg_Speed_Unit;
    uint16_t g_Displayed_Trip_Average_Speed;
    uint8_t g_Trip_Timer_KM;
    uint32_t Sample_Average[20];
    uint32_t average_odo_time_value;
    uint8_t sample_counter;
    bool Pre_Cond_Status;
    uint8_t display_update_time;
    uint32_t g_sample_average_speed_u32[10];
}Avereage_Speed_Ctrl_St;



/*
* @brief This macro is used to define for advisory 
* @Unit: Kilometer 
* @Resolution: 1km
* @Range: 0-199
* @Applicability: Speedometer display 
* @Note:  
*/
typedef enum
{
   Average_Speed_KM_1 = 0,
   Average_Speed_KM_2,
   AVERAGE_SPEED_MAX
}Average_Speed_Lt_Type_En;

/*
* @brief This macro is used to define for advisory 
* @Unit: Kilometer 
* @Resolution: 1km
* @Range: 0-199
* @Applicability: Speedometer display 
* @Note:  
*/
typedef enum
{
	AVERAGE_SPEED_KMPH = 0u,
	AVERAGE_SPEED_MPH  = 1u
} Average_Speed_unit_List_Type_en;


/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/




/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/
/*
* @brief    This API is used to initiate the variable with default value
* @param    Nil 
* @return   Nil
* @invocation Speedo initialization
*/
void Average_Speed_Init(void);

/*
* @brief    This API is used to reset the initital value of the variable
* @param    Nil  
* @return   Nil
* @invocation Speedo initialization
*/
void Average_Speed_Deinit(void);

/*
* @brief    This API is used to activate the peripherals
* @param    Nil
* @return   Nil
* @invocation NA
*/
void Average_Speed_Activate(void);

/*
* @brief    This API is used to deactivate the peripherals
* @param    Nil
* @return   Nil
* @invocation NA
*/
void Average_Speed_Deactivate(void);

/*
* @brief    This API is used to get current status of average speed range
* @param    Nil
* @return   Nil
* @invocation Speedo meter & trip Odo implementation 
*/
void Average_Speed_MainFunction(void);

/*
* @brief    This API is used to get average speed of the system 
* @param    average speed 
* @return   nil
* @invocation  Speedo meter & trip Odo implementation 
*/
void Average_Speed_Function(uint8_t p_Average_Speed_ID_u8);

/*
* @brief    This API is used to get current status of average speed 
* @param    Nil
* @return   Boolean value
* @invocation  Speedo meter & trip Odo implementation 
*/
bool Swc_Check_Average_Speed_Pre_Condition(void);

/*
* @brief    This API is used to get current status of average speed 
* @param    p_Average_Speed_ID
* @return   Nil
* @invocation  Speedo meter & trip Odo implementation 
*/
void Swc_Average_Speed_Reset(Trip_Timer_Acc_Lt_Type_En  p_Average_Speed_ID);

/*
* @brief    This API is used to get current status of average speed 
* @param    p_Average_Speed_ID_u8
* @return   Average speed parameters in the structure
* @invocation Speedo meter & trip Odo implementation 
*/
uint16_t Swc_Avereage_Speed_Get_value(uint8_t p_Average_Speed_ID_u8);

/*
* @brief    This API is used to get current status of average speed 
* @param    Odo parameters
* @return   Nil
* @invocation Speedo meter & trip Odo implementation 
*/
void Swc_Sampling_Trip_Odo_Time(uint64_t get_odo, uint32_t get_time, uint8_t Trip_id);

/*
* @brief    This API is used to get current status of average speed 
* @param    Trip_id 
* @return   Trip_odo_accumulation
* @invocation Speedo meter & trip Odo implementation 
*/
uint64_t AVS_TRIP_ODO_CM(uint8_t trip_id);

/*
* @brief    This API is used to get current status of average speed 
* @param    Speedo values input and its resolution
* @return   processed_input
* @invocation Speedo meter & trip Odo implementation 
*/
uint32_t round_int(uint32_t actual_input, uint32_t resolution);

/*
* @brief    This API is used to get current status of average speed 
* @param    Input of previous and actual,hysteresis
* @return   previous and actual input
* @invocation  Speedo meter & trip Odo implementation 
*/
uint32_t hysteresis_int(uint32_t actual_input, uint32_t previous_input, uint16_t hysteresis);

/*
* @brief    This API is used to get current status of average speed 
* @param    trip_id
* @return   Tripcount value
* @invocation  Speedo meter & trip Odo implementation 
*/
uint64_t AVS_Accu_Value(uint8_t trip_id);

/*
* @brief    This API is used to reset the average distance 
* @param    trip_id
* @return   Nil
* @invocation Speedo meter & trip Odo implementation 
*/
void AVS_Distn_Acc_reset(uint8_t trip_id);

/*
* @brief    This API is used to get current status of average speed 
* @param    nil 
* @return   Boolean
* @invocation  Speedo meter & trip Odo implementation 
*/
bool Swc_Average_Speed_Get_Status(void);
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0
    REVISION DATE        : MONTH/DATE/YEAR                              
    CREATED / REVISED BY : Balasubramaniyan (balasubramaniyan.s@niyatainfotech.com)
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! AVERAGE_SPEED_H */
