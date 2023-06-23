/* @file FILE NAME */
#ifndef TACHO_CFG_H
#define TACHO_CFG_H

/***********************************************************************************************************************
*   DISCLAIMER
*   Copyright © , 2021 Niyata Infotech Ptv. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : R.Maheswari (maheswari@niyatainfotech.com)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : TACHO_Cfg.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent
*  Description                     : This file contains the configuration declarations of Odometer
*  @bug                            : N/A
----------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/


/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S 
***********************************************************************************************************************/
#include "Swc_Tachometer.h"

/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                     C O N F I G U R A T I O N     M A C R O S                      
***********************************************************************************************************************/

/*
* @brief          : This macro is used to LVSD Enable flag
* @Unit           : NA
* @Resolution:    : NA
* @Range          : 0 to 8 bit
* @Applicability  : Store the TACHOmeter LVSD Enable status
* @Note           : Do not modify this macro value or name
*/
#define TACHO_CONFIG_HVSD_STATUS                               Sys_Service_Get_High_Voltage_State()

/*
* @brief          : This macro is used to HVSD Enable flag
* @Unit           : NA
* @Resolution:    : NA
* @Range          : 0 to 8 bit
* @Applicability  : Store the TACHOmeter HVSD Enable status
* @Note           : Do not modify this macro value or name
*/
#define TACHO_CONFIG_LVSD_STATUS                                    Sys_Service_Get_Low_Voltage_State()

/*
* @brief          : This macro is used to power mode
* @Unit           : NA
* @Resolution:    : NA
* @Range          : 0 to 8 bit
* @Applicability  : Store the TACHOmeter power mode
* @Note           : Do not modify this macro value or name
*/
#define TACHO_POWER_MODE 1u

/*
* @brief        : This variable is used to timing fault of TACHO
* @Unit         : KMPH
* @Resolution   : 1
* @Range        : 0 to 32 bit
* @Applicability: This configuration is used for actual speed
* @Note         : Do not modify this macro value or name
*/
#define TACHO_TIMING_FAULT 0u

/*
* @brief        : This variable is used to configure the tacho RPM value
* @Unit         : KMPH
* @Resolution   : 1
* @Range        : 0 to 32 bit
* @Applicability: This configuration is used for actual speed
* @Note         : Do not modify this macro value or name
*/
#define TOTAL_TABLE_INDEX 10u
/*
* @brief        : This variable is used to configure the tacho ECU RPM
* @Unit         : KMPH
* @Resolution   : 1
* @Range        : 0 to 32 bit
* @Applicability: This configuration is used for actual speed
* @Note         : Do not modify this macro value or name
*/
 #define TACHO_ECU_RPM          (int[]){0,1000,2000,3000,4000,5000,6000,7000,8000}
 
 /*
* @brief        : This variable is used to configure the TACHO pinter
* @Unit         : KMPH
* @Resolution   : 1
* @Range        : 0 to 32 bit
* @Applicability: This configuration is used for actual speed
* @Note         : Do not modify this macro value or name
*/
 #define TACHO_POINTER         (int[]){0,1125,2250,3375,4500,5625,6750,7875,9000}


/*
* @brief        : This variable is used to configure the  minimum TACHO values
* @Unit         : KMPH
* @Resolution   : 1
* @Range        : 0 to 32 bit
* @Applicability: This configuration is used for actual speed
* @Note         : Do not modify this macro value or name
*/
 #define  TACHO_MIN  0


 /*
* @brief        : This variable is used to configure the maximum TACHO values
* @Unit         : KMPH
* @Resolution   : 1
* @Range        : 0 to 32 bit
* @Applicability: This configuration is used for actual speed
* @Note         : Do not modify this macro value or name
*/
 #define   TACHO_MAX  9000

 /*
* @brief        : This variable is used to configure the TACHO can signal off
* @Unit         : KMPH
* @Resolution   : 1
* @Range        : 0 to 32 bit
* @Applicability: This configuration is used for actual speed
* @Note         : Do not modify this macro value or name
*/
 #define TACHO_CAN_SIGNAL_OFF 0u
 
#define TACHO_RPM_VS_POINTER     \
                                {{0 ,   8000},\
                                 {0 ,   0},\
                                {1000, 1125},\
                                {2000, 2250},\
                                {3000, 3375},\
                                {4000, 4500},\
                                {5000, 5625},\
                                {6000, 6750},\
                                {7000, 7875},\
                                {8000, 9000} }


#define MAX_TACHO_ENGINE_RPM        8000                                
/***********************************************************************************************************************
*                             C O N F I G U R A T I O N    C O N S T A N T S    D E C L A R A T I O N                       
***********************************************************************************************************************/

/***********************************************************************************************************************
*                            C O N F I G U R A T I O N    V A R I A B L E S    D E C L A R A T I O N                  
***********************************************************************************************************************/

/*********************************************************************************************************************
*                         C O N F I G U R A T I O N     F U N C T I O N    D E C L A R A T I O N S                      
*********************************************************************************************************************/

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
************************************************************************************************************************
REVISION NUMBER      : V1.0.0
REVISION DATE        : 30-April-2021
CREATED / REVISED BY : Maheswari R(maheswari@niyatainfotech.com)
DESCRIPTION          : Initial Version


REVISION NUMBER      : V1.0.1
REVISION DATE        : 26-May-2021
CREATED / REVISED BY : Maheswari R(maheswari@niyatainfotech.com)
DESCRIPTION          : Peer Review comments fixed 
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* !TACHO_CFG_H */
