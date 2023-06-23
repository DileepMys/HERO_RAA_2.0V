/* @file FILE NAME */
#ifndef SPEEDO_CFG_H
#define SPEEDO_CFG_H

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
*  File name                       : Speedo_Cfg.h
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
#include "Swc_Speedometer.h"
#include "Swc_System_Service.h"
/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                     C O N F I G U R A T I O N     M A C R O S                      
***********************************************************************************************************************/
/*
* @brief          : This macro is used to configure flag
* @Unit           : NA
* @Resolution:    : NA
* @Range          : 0 to 8 bit
* @Applicability  : Store the Speedometer Configuration applicable status
* @Note           : Do not modify this macro value or name
*/
/*#define SPEEDO_CONFIG_STATUS    1u*/



/*
* @brief          : This macro is used to power mode
* @Unit           : NA
* @Resolution:    : NA
* @Range          : 0 to 8 bit
* @Applicability  : Store the Speedometer power mode
* @Note           : Do not modify this macro value or name
*/
/*#define SPEEDO_POWER_MODE  1u*/


/*
* @brief          : This macro is used to Speed unit
* @Unit           : NA
* @Resolution:    : NA
* @Range          : 0 to 8 bit
* @Applicability  : Store the Speedometer unit
* @Note           : Do not modify this macro value or name
*/
#define SPEEDO_UNIT_SELECTION 0u

/*
* @brief          : This macro is used to Maximum Speed unit
* @Unit           : NA
* @Resolution:    : NA
* @Range          : 0 to 8 bit
* @Applicability  : Store the Speedometer unit
* @Note           : Do not modify this macro value or name
*/
#define SPEED_MAX 199u

/*
* @brief          : This macro is used to define average Speed 
* @Unit           : NA
* @Resolution:    : NA
* @Range          : 0 to 8 bit
* @Applicability  : Store the Speedometer unit
* @Note           : Do not modify this macro value or name
*/
#define AVEREAGE_SPEED 199u

/*
* @brief          : This macro is used to define the Speed signal from CAN  
* @Unit           : NA
* @Resolution:    : NA
* @Range          : NA
* @Applicability  : Store the Speedometer status
* @Note           : Do not modify this macro value or name
*/
/*#define SPEEDO_CAN_SIGNAL_OFF 1u  */

/*
* @brief          : This macro is used to define the ABS failure status on the Speed 
* @Unit           : NA
* @Resolution:    : NA
* @Range          : NA
* @Applicability  : NIL
* @Note           : Do not modify this macro value or name
*/
/*#define ABS_VEHICLE_SPEED_FAULT 0u*/

/*
* @brief          : This macro is used to define the kilometer per hour Speed value
* @Unit           : NA
* @Resolution:    : NA
* @Range          : NA
* @Applicability  : Store the Speedometer unit
* @Note           : Do not modify this macro value or name
*/
#define SPEEDO_VALUES_KMPH  11u

/*
* @brief          : This macro is used to Speed unit
* @Unit           : NA
* @Resolution:    : NA
* @Range          : 0 to 8 bit
* @Applicability  : Store the Speedometer unit
* @Note           : Do not modify this macro value or name
*/
#define SPEEDO_VALUES_MPG  7u
/*
* @brief        : This variable is used to configure the KMPH minimum values
* @Unit         : KMPH
* @Resolution   : 1
* @Range        : 0 to 32 bit
* @Applicability: This configuration is used for actual speed
* @Note         : Do not modify this macro value or name
*/
  /*#define SPEEDO_KMPH_MIN         (int[]){0,2100,4200,6300,8400,10500,12600,14700,16800,18900}*/


 
 /*
* @brief        : This macro is used to configure the maximum KMPH speed value
* @Unit         : KMPH
* @Resolution   : 1
* @Range        : 0 to 32 bit
* @Applicability: This configuration is used for actual speed
* @Note         : Do not modify this macro value or name
*/
  /*#define SPEEDO_KMPH_MAX          (int[]){0,2300,4400,6600,8800,11000,13200,15400,17600,19800}*/
  
  /*
* @brief        : This variable is used to configure the KMPH minimum values
* @Unit         : KMPH
* @Resolution   : 1
* @Range        : 0 to 32 bit
* @Applicability: This configuration is used for actual speed
* @Note         : Do not modify this macro value or name
*/
  #define SPEEDO_MPG_MIN          (int[]){0,2100,4200,6300,8400,10500,12600}
 
 /* #define SPEEDO_MPG_MAX          (int[]){0,2224,4400,6600,8800,11000,13200}*/
  
  /*
* @brief        : This macro is used to configure the actual speedo value
* @Unit         : KMPH
* @Resolution   : 1
* @Range        : 0 to 32 bit
* @Applicability: This configuration is used for actual speed
* @Note         : Do not modify this macro value or name
*/
  #define SPEEDO_ACTUAL_SPEED    (int[]){0,2000,4000,6000,8000,10000,12000,14000,16000,18000,19000,20000}
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
#endif /* !SPEEDO_CFG_H */
