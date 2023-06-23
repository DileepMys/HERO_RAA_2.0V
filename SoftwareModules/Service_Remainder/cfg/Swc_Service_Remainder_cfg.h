/* @GPIO */
#ifndef SERVICE_REMAINDER_CFG_H
#define SERVICE_REMAINDER_CFG_H

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
 *  File name                       : Swc_Service_Remainder_cfg.h
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : Ride and Cosmic
 *  Platforms supported             : Platform Independent
 *  Description                     : This file contains the APIs for the GPIO module  
 *  @bug                                N/A
*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/


#include "Swc_Odometer.h"
#include "CanMgr.h"
/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                            
***********************************************************************************************************************/
/*
* @brief: This macro defined the blink value for service reminder  
* @Unit:  N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: N/A
* @Note:
*/
/*#define SRV_REMAINDER_BLINK_VALUE                   0*/

/*
* @brief: This macro defines the ON value for service remainder 
* @Unit:  N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: N/A
* @Note:
*/
#define SRV_REMAINDER_ON_VALUE						0

/*
* @brief: This macro defines the distance reange for next service due
* @Unit:  N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: N/A
* @Note:
*/
#define NEXT_SERVICE_DUE                     3000

/*
* @brief: This macro defines maximum odo value in the odometer
* @Unit:  Kilo meter
* @Resolution: N/A
* @Range: 0-999
* @Applicability: N/A
* @Note:
*/
#define MAXIMUM_ODOMETER_KM_VALUE                999999

/*
* @brief: This macro is used to configure the first service remainder blink value at the particular kilometer
* @Unit:  Km
* @Resolution: N/A
* @Range: 250Km
* @Applicability: N/A
* @Note:
*/
#define FIRST_SERVICE_REMAINDER_BLINK_VAL          250

/*
* @brief: This macro is used to configure the service remainder blinking value
* @Unit:  km
* @Resolution: N/A
* @Range: N/A
* @Applicability: N/A
* @Note:
*/
#define SERVICE_REMAINDER_BLINK_VAL                500

/*
* @brief: This macro is used to configure the ON value for service remainder
* @Unit:  N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: N/A
* @Note:
*/
#define SERVICE_REMAINDER_ON_VALUE                 0

/*
* @brief: This macro is used to configure the reset time for service remainder
* @Unit:  N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: N/A
* @Note:
*/
/*#define SERVICE_REMAINDER_RESET_TIME_VALUE         3*/

/*
* @brief: This macro is used to configure the current speed unit 
* @Unit:  Km
* @Resolution: N/A
* @Range: N/A
* @Applicability: N/A
* @Note:
*/
#define CURRENT_SPEED_UNIT_SELECTION               SPEED_KM

/*
* @brief: This macro is used to ON hysteresis for service due blink
* @Unit:  N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: N/A
* @Note:
*/
#define SERVICE_DUE_BLINK_TO_ON_HYST               500

/*
* @brief: This macro is used to reset the counter for next service in NVM
* @Unit:  N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: N/A
* @Note:
*/
/*#define NVM_NEXT_SERVICE_RESET_COUNTER				100*/

/*
* @brief: This macro is used to configure the timeout status of CAN
* @Unit:  N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: N/A
* @Note:
*/
/*#define CAN_TIMEOUT                            FALSE*/


/*
* @brief: This macro is used to configure service remainder list based on the Kilometer and Miles per hour
* @Unit:  N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: N/A
* @Note:
*/
typedef enum
{
	SPEED_KM = 0u,
	SPEED_MH  = 1u

} Service_Remainder_unit_List_Type_en;


/*
* @brief: This macro is used to get current Odo kilometer for displaying current speed 
* @Unit:  N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: N/A
* @Note:
*/
#define GET_ODO_KM			Swc_Get_Display_ODO_Value()

/*
* @brief: This macro is used to get the ignition state for service remainder 
* @Unit:  N/A
* @Resolution: N/A
* @Range: N/A
* @Applicability: N/A
* @Note:
*/
#define SYS_SERVICE_GET_IGNITION_STATE        Sys_Service_Get_Ignition_State()



/***********************************************************************************************************************
*                             C O N F I G U R A T I O N    C O N S T A N T S   D E F I N I T I O N                          
***********************************************************************************************************************/

/***********************************************************************************************************************
*                           C O N F I G U R A T I O N    V A R I A B L E S    D E F I N I T I O N                                            
***********************************************************************************************************************/


/*********************************************************************************************************************
*                         C O N F I G U R A T I O N     F U N C T I O N    D E F I N I T I O N S                      
*********************************************************************************************************************/

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
#endif /* ! SERVICE_REMAINDER_CFG_H */


