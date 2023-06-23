/* @GPIO */
#ifndef AVERAGE_SPEED_CFG_H
#define AVERAGE_SPEED_CFG_H

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
 *  File name                       : Swc_Average_Speed_Cfg.h
 *  Version                         : V1.0.1
 *  Micros supported                : Micro Independent
 *  Compilers supported             : J-Link
 *  Platforms supported             : Platform Independent
 *  Description                     : This file contains the APIs for Swc_Average_Speed_Cfg  
 *  @bug                                N/A
*--------------------------------------------------------------------------------------------------------------------*/






/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                            
***********************************************************************************************************************/
#include "Swc_Average_Speed_cfg.h"



/***********************************************************************************************************************
*                             C O N F I G U R A T I O N    C O N S T A N T S   D E F I N I T I O N                          
***********************************************************************************************************************/

/*
* @brief: This variable is used to configure the unit for the average speed
* @Unit:  Kmph
* @Resolution: 1km
* @Range: 0-199
* @Applicability: Speedo value
* @Note:
*/

#define  AVERAGE_SPEED_UNIT_SELECTION                 AVERAGE_SPEED_KMPH

/*
* @brief: This variable is used to configure the km to mile conversion
* @Unit:  Miles
* @Resolution: 
* @Range: 
* @Applicability: Speedo value
* @Note:
*/
//#define KM_MILE_CONV_FACTOR                           1609344

/*
* @brief: This variable is used to configure amount of distance particular trip has to be travelled to display average speed 
* @Unit:  KM
* @Resolution: 1
* @Range: 0 to 2
* @Applicability: 
* @Note:
*/
#define INIT_DIST       (uint64) 100000


/*
* @brief: This enum is used to configure trip1 and trip 2 range
* @Unit:  km
* @Resolution: nil
* @Range: nil
* @Applicability: Speedo value
* @Note:
*/

typedef enum
{
   TRIP_1_KM = 0,
   TRIP_2_KM,
   TTRIP_KM_ACC_MAX
}Trip_Km_Acc_Lt_Type_En;



/*
* @brief: This variable is used to configure trip time accumulation
* @Unit:  nil
* @Resolution: nil
* @Range: nil
* @Applicability: nil
* @Note:
*/
typedef enum
{
   TRIP_TIME_ACC_1 = 0,
   TRIP_TIME_ACC_2,
   TRIP_TIME_ACC_MAX
}Trip_Timer_Acc_Lt_Type_En;



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
#endif /* ! AVERAGE_SPEED_CFG_H */


