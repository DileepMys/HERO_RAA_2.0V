/* @GPIO */

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
 *  File name                       : timer_trip_C
 *  Version                         : V1.0.1
 *  Micros supported                : Micro Independent
 *  Compilers supported             : Ride and Cosmic
 *  Platforms supported             : Platform Independent
 *  Description                     : This file contains the APIs for the GPIO module  
 *  @bug                             N/A
*--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                            
***********************************************************************************************************************/
#include "Swc_Nvm_Handler_cfg.h"


/***********************************************************************************************************************
*                             C O N F I G U R A T I O N    C O N S T A N T S   D E F I N I T I O N                          
***********************************************************************************************************************/


/***********************************************************************************************************************
*                           C O N F I G U R A T I O N    V A R I A B L E S    D E F I N I T I O N                                            
***********************************************************************************************************************/


/*********************************************************************************************************************
*                         C O N F I G U R A T I O N     F U N C T I O N    D E F I N I T I O N S                      
*********************************************************************************************************************/
/*
* @brief    This function is used to 
* @param    
* @return 
* @note:  
*/


/* NVMINPUT CONFIGURATION */
const NVM_Write_Byte_Config_Type_St NVM_Write_Config_St[MAX_NVM_LIST] = 
{
    /*  Index                              		                                        Start Address                        Size                           */
    {NVM_ODO_VALUE_0,                                                                     0x00000000 ,                      0x00000005,                     },
    {NVM_ODO_VALUE_1,                                                                     0x00000005 ,                      0x00000005,                     },
    {NVM_ODO_VALUE_2,                                                                     0x0000000A ,                      0x00000005,                     },
    {NVM_ODO_VALUE_3,                                                                     0x0000000F ,                      0x00000005,                     },
    {NVM_ODO_VALUE_4,                                                                     0x00000014 ,                      0x00000005,                     },
    {NVM_ODO_VALUE_5,                                                                     0x00000019 ,                      0x00000005,                     },
    {NVM_ODO_VALUE_6,                                                                     0x0000001E ,                      0x00000005,                     },
    {NVM_ODO_VALUE_7,                                                                     0x00000023 ,                      0x00000005,                     },
    {NVM_ODO_VALUE_8,                                                                     0x00000028 ,                      0x00000005,                     },
    {NVM_ODO_VALUE_9,                                                                     0x0000002D ,                      0x00000005,                     },
    {NVM_ODO_TRIP_A,                                                                      0x00000032 ,                      0x00000003,                     },
    {NVM_ODO_TRIP_B,                                                                      0x00000035 ,                      0x00000003,                     },                                                            
    {NVM_TRIP_TIME_A,                                                                     0x00000038 ,                      0x00000004,                     },
    {NVM_TRIP_TIME_B,                                                                     0x0000003C ,                      0x00000004,                     },
    {NVM_SERVICE_DUE_VALUE,                                                               0x00000040 ,                      0x00000004,                     },
    {NVM_SERVICE_REMAINDER_AUXILIARY_DATA,                                                0x00000044 ,                      0x00000004,                     },
    {NVM_SETTING_SCREEN_NVM_DATA,                                                         0x00000048 ,                      0x00000006,                     },
    {NVM_FUEL_GUAGE_FLPS_COUNT,                                                           0x0000004E ,                      0x00000004,                     },
    {NVM_TRIP_A_AFE_DISTANCE_ACCUMULATION,                                                0x00000052 ,                      0x00000008,                     },
    {NVM_TRIP_B_AFE_DISTANCE_ACCUMULATION,                                                0x0000005A ,                      0x00000008,                     },
    {NVM_TRIP_A_AFE_FUEL_CONS_ACC,                                                        0x00000062 ,                      0x00000004,                     },
    {NVM_TRIP_B_AFE_FUEL_CONS_ACC,                                                        0x00000066 ,                      0x00000004,                     },
    {FUEL_GAUGE_BAR_LEVEL,                                                                0x0000006A ,                      0x00000001,                     },
    {NVM_ODO_CENTIMETER_AND_TRIp_ODO_RESET_DISTANCE_CM_RESOLUTION_DATA,                   0x0000006B ,                      0x00000006,                     },
    {NVM_DTE_DATA,                                                                        0x00000071 ,                      0x00000010,                     },
    {NVM_AVEREGE_SPEED_TRIP_CM_ACC,                                                       0x00000081 ,                      0x00000010,                     },
    {NVM_AFE_FUEL_ACC_CALC_IDLE,                                                          0x00000091 ,                      0x00000001,                     },
    {NVM_FUEL_GAUGE_BAR_ON_OFF_VAL_CALIBRATION,                                           0x00000092 ,                      0x00000020,                     },
    {NVM_RESERVED_FOR_APPLICATION,                                                        0x000000B2 ,                      0x00000023,                     },
    {NVM_APPLICATION_SOFTWARE_PROGRAMMING_DATE,                                           0x000000D5 ,                      0x00000004,                     },
    {NVM_FINGERPRINT_DATA_DID,                                                            0x000000D9 ,                      0x00000016,                     },
    {NVM_ECU_HARDWARE_NUMBER_DID,                                                         0x000000EF ,                      0x00000018,                     },
    {NVM_ASSEMBLY_MANUFACTUREING_DATE_DID,                                                0x00000107 ,                      0x0000000A,                     },
    {ECU_SERIAL_NUMBER_WITH_MANUFACTURING_DATE_DID,                                       0x00000111 ,                      0x00000013,                     },
    {NVM_CAN_DATA_BASE_VERSION_NUMBER_DATA_IDENTIFIER_F100,                               0x00000124 ,                      0x00000010,                     },
    {NVM_ODOMETER_RESET_FF00,                                                             0x00000134 ,                      0x00000001,                     },
    {NVM_CLOCK_TESTING_FE07,                                                              0x00000135 ,                      0x00000004,                     },
    {NVM_CONFIGURE_BT_MAC_ADDRESS_FDBA,                                                   0x00000139 ,                      0x00000006,                     },
    {NVM_FUEL_CALIBRATION,                                                                0x0000013F ,                      0x0000001E,                     },
    {NVM_PROGRAMMING_ATTEMPT_COUNTER,                                                     0x0000015D ,                      0x00000002,                     },
    {NVM_PROGRAMMING_SUCCESS_COUNTER,                                                     0x0000015F ,                      0x00000002,                     },
    {NVM_BOOTLOADER_VERSION,                                                              0x00000161 ,                      0x00000018,                     },
    {NVM_CRC_31_INTEGRETY_CHECK,                                                          0x00000179 ,                      0x00000005,                     },
    {NVM_RESERVED_FOR_DIAGNOSTICS_1,                                                      0x0000017E ,                      0x00000062,                     },
    {BOOT_FLAG,                                                                           0x000001E0 ,                      0x00000004,                     },
    {NVM_RESERVED_FOR_DIAGNOSTICS_2,                                                      0x000001E4 ,                      0x0000001C,                     }
};


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



