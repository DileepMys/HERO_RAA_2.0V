/* @GPIO */
#ifndef NVM_HANDLER_CFG_H
#define NVM_HANDLER_CFG_H

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Balasubramaniyan.S (balasubramaniyan.s@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : Nvm Hnadler C
 *  Version                         : V1.0.1
 *  Micros supported                : Micro Independent
 *  Compilers supported             : Ride and Cosmic
 *  Platforms supported             : Platform Independent
 *  Description                     : This file contains the APIs for the GPIO module  
 *  @bug                                N/A
*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/


/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                            
***********************************************************************************************************************/
#include "hal_stdtypes.h"



/***********************************************************************************************************************
*                             C O N F I G U R A T I O N    C O N S T A N T S   D E F I N I T I O N                          
***********************************************************************************************************************/
/*
* @brief: This variable is used to configure 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:
*/

/***********************************************************************************************************************
*                           C O N F I G U R A T I O N    V A R I A B L E S    D E F I N I T I O N                                            
***********************************************************************************************************************/
/*
* @brief This variable is used to configure the GPIO pins as per the requirment 
  */

/*#define DEVICE_ADDRESS                  50*/

/*#define TWO_WIRE_SERIAL_EEPROM          2*/




/*********************************************************************************************************************
*                         C O N F I G U R A T I O N     F U N C T I O N    D E F I N I T I O N S                      
*********************************************************************************************************************/
/*
* @brief    This enum is used to specify the function whether it is read or write
* @param    Nil
* @return   Nil
* @note:  
*/
typedef enum
{
   READ = 1u,
   WRITE
}Nvm_Handler_List_Type_En;

typedef struct
{
  uint8_t Index;
  uint32_t NVM_Write_Start_Address;
  uint32_t NVM_Write_Size;
}NVM_Write_Byte_Config_Type_St;





typedef struct
{
 uint32_t variable_32;
}NVM_Byte_Type_St;

typedef enum
{
	NVM_ODO_VALUE_0 = 0,
	NVM_ODO_VALUE_1,
	NVM_ODO_VALUE_2,
	NVM_ODO_VALUE_3,
	NVM_ODO_VALUE_4,
	NVM_ODO_VALUE_5,
	NVM_ODO_VALUE_6,
	NVM_ODO_VALUE_7,
	NVM_ODO_VALUE_8, 
	NVM_ODO_VALUE_9, 
	NVM_ODO_TRIP_A,
	NVM_ODO_TRIP_B,
	NVM_TRIP_TIME_A,
	NVM_TRIP_TIME_B,
   NVM_SERVICE_DUE_VALUE,
   NVM_SERVICE_REMAINDER_AUXILIARY_DATA,
   NVM_SETTING_SCREEN_NVM_DATA,
   NVM_FUEL_GUAGE_FLPS_COUNT,
   NVM_TRIP_A_AFE_DISTANCE_ACCUMULATION,
   NVM_TRIP_B_AFE_DISTANCE_ACCUMULATION,
   NVM_TRIP_A_AFE_FUEL_CONS_ACC,
   NVM_TRIP_B_AFE_FUEL_CONS_ACC,
   FUEL_GAUGE_BAR_LEVEL,
   NVM_ODO_CENTIMETER_AND_TRIp_ODO_RESET_DISTANCE_CM_RESOLUTION_DATA,
   NVM_DTE_DATA,
   NVM_AVEREGE_SPEED_TRIP_CM_ACC, 
   NVM_AFE_FUEL_ACC_CALC_IDLE,
   NVM_FUEL_GAUGE_BAR_ON_OFF_VAL_CALIBRATION,
   NVM_RESERVED_FOR_APPLICATION,
   NVM_APPLICATION_SOFTWARE_PROGRAMMING_DATE,
   NVM_FINGERPRINT_DATA_DID,
   NVM_ECU_HARDWARE_NUMBER_DID,
   NVM_ASSEMBLY_MANUFACTUREING_DATE_DID,
   ECU_SERIAL_NUMBER_WITH_MANUFACTURING_DATE_DID,
   NVM_CAN_DATA_BASE_VERSION_NUMBER_DATA_IDENTIFIER_F100,
   NVM_ODOMETER_RESET_FF00,
   NVM_CLOCK_TESTING_FE07,
   NVM_CONFIGURE_BT_MAC_ADDRESS_FDBA,
   NVM_FUEL_CALIBRATION,
   NVM_PROGRAMMING_ATTEMPT_COUNTER,
   NVM_PROGRAMMING_SUCCESS_COUNTER,
   NVM_BOOTLOADER_VERSION,
   NVM_CRC_31_INTEGRETY_CHECK,
   NVM_RESERVED_FOR_DIAGNOSTICS_1,
   BOOT_FLAG,
   NVM_RESERVED_FOR_DIAGNOSTICS_2,
   MAX_NVM_LIST
}NVM_List_Index_Type_En;

extern const  NVM_Write_Byte_Config_Type_St NVM_Write_Config_St[MAX_NVM_LIST];

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0
    REVISION DATE        : 2/19/2021        
    CREATED / REVISED BY : Balasubramaniyan.S (balasubramaniyan.s@niyatainfotech.com)      
    DESCRIPTION          : Initial version  

------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! GPIO_CFG_C */


