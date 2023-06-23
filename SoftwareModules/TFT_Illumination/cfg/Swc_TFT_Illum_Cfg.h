/* @file FILE NAME */
#ifndef SWC_TFT_ILLUM_CFG_H
#define SWC_TFT_ILLUM_CFG_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Palani kumar (palanikumar@niyatainfotech.com)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : Swc_TFT_Illum_Cfg.h
*  Version                         : v1.0.1
*  Micros supported                : Micro Independent
*  Compilers supported             : J link
*  Platforms supported             : Platform Independent
*  Description                     : This file contains the configuration declarations of TFT illumination process
*  @bug                            : 
*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S 
***********************************************************************************************************************/
#include "Swc_TFT_Illum.h"
#include "Cmp_Init.h"
#include "HMI_Setting_Screen.h"
#include "Ambient_light_sensor.h"
/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                    C O N F I G U R A T I O N     M A C R O S                      
***********************************************************************************************************************/
/*
* @brief: This macro is used to configure the invalid value of illuminance 
* @Unit:  NA
* @Resolution: NA
* @Range: NA
* @Applicability: NA
* @Note: NA
*/
#define TFT_ILLUM_INVALID_VALUE                    0xFFFF

/*
* @brief: This macro is used to configure the number of levels 
* @Unit:  NA
* @Resolution: NA
* @Range: NA
* @Applicability: NA
* @Note: NA
*/
#define NUMBER_OF_LEVELS              8
/*
* @brief: This macro is used to configure value of duty cycle by which PWM out will be varied to reach target PWM
* @Unit:  NA
* @Resolution: NA
* @Range: 0 to 100%
* @Applicability: NA
* @Note: duty cycle will be incremented or decremented by configured value.
*/
#define ILLUM_SLEW_RATE                   1u
/*
* @brief: This macro is used to configure value of default duty cycle 
* @Unit:  Duty cycle
* @Resolution: 1
* @Range: 0 to 100%
* @Applicability: until welcome animation completes, Default brightness shall be used. 
* @Note: N/A
*/
#define TFT_DEFAULT_PWM_DUTY_CYCLE                   (uint8_t)30u
/***********************************************************************************************************************
*                             C O N F I G U R A T I O N    C O N S T A N T S    D E C L A R A T I O N                       
***********************************************************************************************************************/
/*
* @brief: This variable is used to configure pwm duty's in auto brightness level
* @Unit: NIL 
* @Resolution: NIL
* @Range: NA
* @Applicability: this will be used when user selects Auto brightness level
* @Note: 
*/
#define AUTO_LEVEL_PWM_DUTY          (int[]){100,80,60,40,20,15,10,5}
/***********************************************************************************************************************
*                            C O N F I G U R A T I O N    V A R I A B L E S    D E C L A R A T I O N                  
***********************************************************************************************************************/
/*
* @brief: This variable is used to configure illuminance value and its corresponding PWM Duty cycle for different 
*         User brightness selection levels
* @Unit:  NA
* @Resolution: NA
* @Range: NA
* @Applicability: NIL
* @Note: Based on User selected brightness level in setting screen, The pwm duty cycle for corresponding readed illuminance 
*        value will be feed to TFT.
*/
typedef struct 
{
  uint16_t Lux_value;
  uint8_t Low_Duty_Cycle;
  uint8_t Medium_Duty_Cycle;
  uint8_t High_Duty_Cycle;
}TFT_ILLUM_BRIGHTNESS_ST;


/*
* @brief: This structure is used to define TFT illumination brightness levels
* @Unit: NIL 
* @Resolution: NIL
* @Range: NA
* @Applicability: this will be used when user selects Auto brightness level
* @Note: 
*/
extern const TFT_ILLUM_BRIGHTNESS_ST g_TFT_Illum_vs_Manual_level_pwm_cfg_St[NUMBER_OF_LEVELS];
/*********************************************************************************************************************
*                         C O N F I G U R A T I O N     F U N C T I O N    D E C L A R A T I O N S                      
*********************************************************************************************************************/
/*
* @brief    This function is used to get ignition status from syster service 
* @param    None
* @return   IGN_ON - ignition turned ON,  IGN_OFF - ignition turned OFF
* @note:  
*/
#define TFT_ILLUM_GET_IGN_STATUS                Sys_Service_Get_Ignition_State()

/*
* @brief    This function is used to get LVSD status from syster service 
* @param    None
* @return   LVSD_SET - Low voltage state set,  LVSD_NOT_SET - Low volage state not set
* @note:  
*/
#define TFT_ILLUM_GET_LVSD_STATUS                 Sys_Service_Get_Low_Voltage_State()

/*
* @brief    This function is used to get HVSD status from syster service 
* @param    None
* @return   hVSD_SET - High voltage state set,  HVSD_NOT_SET - High volage state not set
* @note:  
*/
#define TFT_ILLUM_GET_HVSD_STATUS                Sys_Service_Get_High_Voltage_State()

/*
* @brief    This function is used to get user selected brightness from setting screen
* @param    None
* @return   
* @note:  
*/
#define TFT_ILLUM_GET_USER_BRIGHTNESS_SEL         HMI_Setting_Screen_Get_Brightness_Level()

/*
* @brief    This function is used to get current illuminance value from ambient light sensor 
* @param    None
* @return   
* @note:  
*/
#define TFT_ILLUM_GET_ALS_LUX_VALUE          Swc_ALS_Get_Luminance_Value()

/*
* @brief    This function is used to get current ambient mode from ambient light sensor 
* @param    None
* @return   
* @note:  
*/
#define TFT_ILLUM_GET_CURRENT_AMBIENT_MODE         Get_day_night_mode_status()
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                          
    REVISION DATE        : 07/18/2022        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)      
    DESCRIPTION          : Initial version       

    REVISION NUMBER      : V1.0.1                          
    REVISION DATE        : 12/21/2022        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)      
    DESCRIPTION          : Macro for TFT Default PWM Duty cycle added                                 
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! SWC_TFT_ILLUM_CFG_H */
