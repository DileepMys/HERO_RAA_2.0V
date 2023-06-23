/* @file FILE NAME */
#ifndef GEAR_POSITION_H
#define GEAR_POSITION_H

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
*  File name                       : Gear position.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : J Link
*  Platforms supported             : Platform Independent
*  Description                     : This file contains Macros, Typdef and Function Declarations for gear_position files
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/

#include "SWC_Gear_position_Cfg.h"
#include "stdint.h"

/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/
/*
* @brief: This macro is used to get the CAN time status
* @Resolution: nil
* @Range: nil
* @Applicability: nil
* @Note: 
*/
#define GET_CAN_TIME_STATUS                             NULL

/*
* @brief: This macro is used to provide information whether the ignition is ON 
* @Resolution: nil
* @Range: nil
* @Applicability: 
* @Note: 
*/
/*#define IGNITION_ON      1*/

/*
* @brief: This macro is used to provide information whether the ignition is OFF 
* @Resolution: nil
* @Range: nil
* @Applicability: 
* @Note: 
*/
/*#define IGNITION_OFF     0*/

/*
* @brief: This macro is used to provide information of number of gear max positions availble in the system
* @Resolution: nil
* @Range: 1-6
* @Applicability: nil
* @Note: 
*/
/*#define MAX_GEAR_POS      6*/

/*
* @brief: This macro is get to know the geat shift UP position status
* @Resolution: nil
* @Range: nil
* @Applicability: nil
* @Note: 
*/
/*#define SHIFT_UP_ADVISORY  0x01*/

/*
* @brief: This macro is get to Know the maximum voltage range of the system
* @Resolution: nil
* @Range: nil
* @Applicability: nil
* @Note: 
*/
/*#define MAX_Vge 5*/

/*
* @brief: This macro is get to know the geat shift down position status
* @Resolution: nil
* @Range: nil
* @Applicability: 
* @Note: 
*/
/*#define SHIFT_DOWN_ADVISORY  0x02*/

/*
* @brief: This API is used to initialte the variables by its default values
* @Resolution: nil
* @Range: nil
* @Applicability: nil
* @Note: 
*/

void gear_position_Init(void);

/*
* @brief: This API is used to reset the initial values of the init variables
* @Resolution: nil
* @Range: nil
* @Applicability: nil
* @Note: 
*/
void gear_position_DeInit(void);

/*
* @brief: This API is used to activate the peripherals
* @Resolution: nil
* @Range: nil
* @Applicability: 
* @Note: 
*/
void gear_position_Activate(void);

/*
* @brief: This API is used to de-activate the peripherals
* @Resolution: nil
* @Range: nil
* @Applicability: 
* @Note: 
*/
void gear_position_DeActivate(void);

/*
* @brief: This API is used to provide information as this is day mode
* @Resolution: nil
* @Range: nil
* @Applicability: 
* @Note: 
*/
void gear_position_MainFunction(void);

/*
* @brief: This API is used to provide information as this is day mode
* @Resolution: nil
* @Range: nil
* @Applicability: 
* @Note: 
*/
uint8_t Swc_Check_Pre_Condition(void);




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
* @brief This macro is used to define for advisory list of the gear position
* @Unit:  n/a
* @Resolution: n/a 
* @Range: n/a
* @Applicability: nil 
* @Note:  
*/

typedef enum
{
   GEAR_Shift_Advisory_NO_Shift = 0u,
   GEAR_Shift_Advisory_Shift_UP,
   GEAR_Shift_Advisory_Shift_Down,
   GEAR_Shift_Advisory_Not_used,
   GEAR_Shift_Advisory_MAX
}GEAR_Shift_Advisory_List_Type_En;




/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef is used to define the number of gear position in the system
 * @param    nil
 * @return   nil
 **/

typedef enum
{
   GEAR_NEUTRAL = 0u,
   GEAR_POS_1,
   GEAR_POS_2,
   GEAR_POS_3,
   GEAR_POS_4,
   GEAR_POS_5,
   GEAR_POS_6,
   GEAR_POS_INVALID
}GEAR_POS_LIST_EN;

/*
 * @brief    This Function is used transfer the gear up indication to HMI
 * @param    Nil
 * @return   Uint8_t (gear up position state)
 **/
 uint8_t Get_Gear_Position_Shift_Advisory_Indication(void);

/*
 * @brief    This Function is used to get gear position number and returns to HMI
 * @param    Nil
 * @return    Uint8_t (gear position number)
 **/
 uint8_t Get_Gear_Position_Number_Indication(void);

/*
 * @brief    This Function is used to get time out call back information of the gear position
 * @param    nil
 * @return    nil
 **/
 void CanMgr_Gear_Timeout_Callback_0x130(void);

/*
 * @brief    This Function is used to get the gear position status
 * @param    nil
 * @return   nil
 **/
void CanMgr_Gear_Position_reception_cbk(void);

/*
 * @brief    This Function is used to get time out call back information of the gear shift
 * @param    nil
 * @return   nil
 **/
void CanMgr_GearShift_Timeout_Callback_0x130(void);

/*
 * @brief    This Function is used to send gear shift timeout flag to CAN as a input
 * @param    nil
 * @return   nil 
 **/
void CanMgr_Gear_Shift_Timeout_Flag(void);

/*
 * @brief    This Function is used to define gear position
 * @param    nil
 * @return   nil
 **/
void CanMgr_Gear_Shift_reception_cbk(void);


/*
 * @brief    This enum is used to define for indication of gear position whether it is up or down 
 * @param    nil   
 * @return   nil 
 **/
typedef enum
{
   NO_DISPLAY = 0,
   DISPLAY_GEAR_UP,
   DISPLAY_GEAR_DOWN,
   GP_MAX
}GEAR_SHIFT_IND_DISPLAY_LIST_EN;


/*
 * @brief    This enum is used to define for indication of gear shift advisory
 * @param    
 * @return    
 **/
typedef enum
{
    GEAR_NO_SHIFT_ADVISORY = 0x0u,
    GEAR_SHIFT_UP_ADVISORY = 0x01,
    GEAR_SHIFT_DOWN_ADVISORY = 0x02
}GEAR_SHIFT_ADVISORY_LIST_EN;

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to 
* @param    
* @return  
* @invocation 
*/

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                                                
    REVISION DATE        : 2/19/2021        
    CREATED / REVISED BY : Balasubramaniyan (balasubramaniyan.s@niyatainfotech.com)
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! GEAR_POSITION_H */
