/* @file AMBIENT_LIGHT_SENSOR_CFG_H */
#ifndef AMBIENT_LIGHT_SENSOR_CFG_H
#define AMBIENT_LIGHT_SENSOR_CFG_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Name (mail-id)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
 *  File name                       : Ambientlight_sensor_cfg.h
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : Compiler Independent
 *  Platforms supported             : Platform Independent
 *  Description                     : This file consists of definitions of configuration macros nd configuration functions
*  @bug                            : 
*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/
/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S 
***********************************************************************************************************************/
//#include "filename.h"

/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/
/* perform integrity check when it is necessary 
#if ( FILE_NAME_H_VERSION != 0x0001 )
    #error "Incorrect version of header file used in filename.h!!!"
#endif*/

/***********************************************************************************************************************
*                                    C O N F I G U R A T I O N     M A C R O S                      
***********************************************************************************************************************/
/*
* @brief: This macro is used to configure the primary time value 
* @Unit: ms
* @Resolution: 0.1
* @Range: 0 to 100
* @Applicability: Yes
* @Note: 
*/
#define ALS_UPDATE_TIME_PRIMARY_MS  15

/*
* @brief: This macro is used to configure the primary time value 
* @Unit: ms 
* @Resolution: 0.1
* @Range: 0-200
* @Applicability: 
* @Note: 
*/
#define ALS_UPDATE_TIME_SECONDARY_MS  50
/*
* @brief: This macro is used to configure the day mode luminance 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note: 
*/
#define ALS_LUX_DAY_THRESHOLD  1400
/*
* @brief: This macro is used to configure the night mode luminance 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note: 
*/
#define ALS_LUX_NIGHT_THRESHOLD 700

/*
* @brief This macro is used to get the average lux sample from I2C sensor for every 10ms
* @Unit: nil 
* @Resolution: 10
* @Range: nil
* @Applicability: nil
* @Note:  nil
*/
#define LUX_AVG_SAMPLE 10

/*
* @brief This macro is used to get the average ALS_initialization_send_statusial lux sample taken from I2C during ALS_initialization_send_statusial stage
* @Unit:  nil
* @Resolution: 1
* @Range: nil
* @Applicability: nil
* @Note:  nil
*/
#define LUX_AVG_INIT_SAMPLE  3

/*
* @brief: This macro is used to  get the whole luminance value from the factor raw input from I2C sensor
* @Unit: nil 
* @Resolution: nil
* @Range: nil
* @Applicability: nil
* @Note: nil
*/
#define ALS_RESOLUTION_FACTOR 10

/*
* @brief: This macro is used to provide information as this is day mode
* @Resolution: nil
* @Range: nil
* @Applicability: TFT backlight uses this information 
* @Note: 
*/
#define DAY        0x02

/*
* @brief: This macro is used to provide information as this is night mode
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: TFT backlight uses this information 
* @Note: 
*/
#define NIGHT 		0x01



/***********************************************************************************************************************
*                             C O N F I G U R A T I O N    C O N S T A N T S    D E C L A R A T I O N                       
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
*                            C O N F I G U R A T I O N    V A R I A B L E S    D E C L A R A T I O N                  
***********************************************************************************************************************/
/*
* @brief: This variable is used to configure 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note: 
*/

/*********************************************************************************************************************
*                         C O N F I G U R A T I O N     F U N C T I O N    D E C L A R A T I O N S                      
*********************************************************************************************************************/
/*
* @brief    This function is used to check the Ambient light sensor igntion position
* @param    NIL
* @return   NIL
* @note:    NIL
*/
#define ALS_GET_IGN_POSITION   Sys_Service_Get_Ignition_State()

/*
* @brief    This function is used to check the Ambient light sensor Low voltage state
* @param    NIL
* @return   NIL
* @note:    NIL
*/
#define ALS_GET_LOW_VOLTAGE_STATE   Sys_Service_Get_Low_Voltage_State()

/*
* @brief    This function is used to check the Ambient light sensor High voltage state
* @param    NIL 
* @return   NIL
* @note:    NIL
*/
#define ALS_GET_HIGH_VOLTAGE_STATE  Sys_Service_Get_High_Voltage_State()




/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      :	v1.0.0                         
    REVISION DATE        : 08/12/2022
    CREATED / REVISED BY : Jeevajothi (jeevajothi@niyatainfotech.com)
    DESCRIPTION          : This file consisits of day or night mode status                                    
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! AMBIENT_LIGHT_SENSOR_CFG_H */
