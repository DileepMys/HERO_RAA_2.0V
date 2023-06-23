/* @GPIO */
#ifndef GEAR_POSITION_CFG_H
#define GEAR_POSITION_CFG_H

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
 *  File name                       : Gear position_C
 *  Version                         : V1.0.1
 *  Micros supported                : Micro Independent
 *  Compilers supported             : J link
 *  Platforms supported             : Platform Independent
 *  Description                     : This file contains the APIs for the GPIO module  
 *  @bug                                N/A
*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                            
***********************************************************************************************************************/



/*
* @brief: This macro is used to configure the gear position
* @Unit:  nil
* @Resolution: na
* @Range: na
* @Applicability:nil 
* @Note:
*/

#define SWC_GP_CONFIGURATION_ENABLE              (STD_OFF)


/* if gear position enable status is ON it will configure the gear position status */
#if (SWC_GP_CONFIGURATION_ENABLE == STD_ON)

/*
* @brief: This macro is used to configure the gear position
* @Unit:  nil
* @Resolution: na
* @Range: na
* @Applicability:nil 
* @Note:
*/
   #define SWC_GP_CONFIGURATION_STATUS           (STD_OFF)

#endif

/*
* @brief: This macro is used to configure the low voltage shut down status
* @Unit:  nil
* @Resolution: na
* @Range: na
* @Applicability:nil 
* @Note:
*/
#define SWC_GP_LVSD_STATUS                       (STD_OFF) 

/*
* @brief: This macro is used to configure the High voltage shut down status
* @Unit:  nil
* @Resolution: na
* @Range: na
* @Applicability:nil 
* @Note:
*/
#define SWC_GP_HVSD_STATUS                       (STD_OFF) 

/*
* @brief: This macro is used to configure the Ignition position status
* @Unit:  nil
* @Resolution: na
* @Range: na
* @Applicability:nil 
* @Note:
*/
#define SWC_GP_ALLOWED_IGN_MODE                  (IGN_RUN)   

/*
* @brief: This macro is used to send the gear position data into CAN 
* @Unit:  nil
* @Resolution: na
* @Range: na
* @Applicability:nil 
* @Note:
*/
#define SWC_GP_CAN_GEAR_POS_DATA            NULL
/*
* @brief: This variable is used to configure 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:
*/



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
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0
    REVISION DATE        : 2/19/2021        
    CREATED / REVISED BY : Balasubramaniyan.S (balasubramaniyan.s@niyatainfotech.com)      
    DESCRIPTION          : Initial version  

------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! GEAR_POSITION_CFG_H */


