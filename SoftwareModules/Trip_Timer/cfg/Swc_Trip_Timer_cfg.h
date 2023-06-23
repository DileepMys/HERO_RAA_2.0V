/* @GPIO */
#ifndef TIMER_TRIP_CFG_H
#define TIMER_TRIP_CFG_H

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
 *  Micros supported                : Micro independent
 *  Compilers supported             : Ride and Cosmic
 *  Platforms supported             : Platform independent
 *  Description                     : This file contains the APIs for the GPIO module  
 *  @bug                                N/A
*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                            
***********************************************************************************************************************/
/*
* @brief: This macro is used to configure the trip timer enable status
* @Unit:  NA
* @Resolution: NIL
* @Range: NA
* @Applicability: NA
* @Note:
*/
#define SWC_TT_CONFIGURATION_ENABLE              (STD_OFF)



/*
* @brief: This macro defines the low voltage shut down status as it is OFF state
* @Unit:  NA
* @Resolution: NIL
* @Range: NA
* @Applicability: NA
* @Note:
*/
/*#define SWC_TT_LVSD_STATUS                       (STD_OFF) */

/*
* @brief: This macro defines the high voltage shut down status as it is OFF state
* @Unit:  NA
* @Resolution: NIL
* @Range: NA
* @Applicability: NA
* @Note:
*/
/*#define SWC_TT_HVSD_STATUS                       (STD_OFF) */

/*
* @brief: This macro defines the total trip count
* @Unit:  NA
* @Resolution: NIL
* @Range: 3
* @Applicability: NA
* @Note:
*/
#define TOTAL_TRIP_COUNT                         (uint8_t)  2u

/*
* @brief: This variable is used to configure delta trip time to accumulate 
* @Unit:  NA
* @Resolution: NIL
* @Range: NA
* @Applicability: NA
* @Note:
*/
#define MAX_DELTA_TRIP_TIME                        2

/*
* @brief: This macro defines maximum trip timer accumulation rate
* @Unit:  NA
* @Resolution: NIL
* @Range: NA
* @Applicability: NA
* @Note:
*/
#define TRIP_TIMER_ACC_MAX                     0xFFFFFFFF

/*
* @brief: This variable is used to configure 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:
*/
#define TRIP_TIME_DISP_MAX              (uint32)        0x57E40

/*
* @brief: This macro defines the minimum engine RPM value
* @Unit:  RPM
* @Resolution: 100
* @Range: 0-200
* @Applicability: NA
* @Note:
*/
#define MIN_ENGINE_RPM                           200

/*
* @brief: This macro defines the maximum engine RPM value
* @Unit:  RPM
* @Resolution: 100
* @Range: NA
* @Applicability: NA
* @Note:
*/
#define MAX_ENGINE_RPM                           8000

/*
* @brief: This macro defines the time value in seconds
* @Unit:  seconds
* @Resolution: 60
* @Range: NA
* @Applicability: NA
* @Note:
*/
#define SEC_60                                    60

/*
* @brief: This macro is used get the NVM block ID for trip timer
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:
*/
#define TRIP_TIMER_NVM_BLOCK_ID           12u



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




/*********************************************************************************************************************
*                         C O N F I G U R A T I O N     F U N C T I O N    D E F I N I T I O N S                      
*********************************************************************************************************************/
/*
* @brief    This function is used to 
* @param    
* @return 
* @note:  
*/
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
#endif /* ! TIMER_TRIP_CFG_H */


