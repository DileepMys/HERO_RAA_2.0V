/* @file AMBIENT_LIGHT_SENSOR_H  */
#ifndef AMBIENT_LIGHT_SENSOR_H
#define AMBIENT_LIGHT_SENSOR_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Jeevajothi (jeevajothi@niyatainfotech.com)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : Ambient_light sensor.h
*  Version                         : v1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent                
*  Description                     : This header file contains the declarations of local functions declarations
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include "Ambient_light_sensor_Cfg.h"
#include "hal_stdtypes.h"
#include "Swc_TFT_Illum.h"


/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/



/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef enum is used to define ambient modes
 * @param    
 * @param
 **/




/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to initialize the values for initial variables
* @param    Nil
* @return  boolean
* @invocation 
*/
void I2C_Ambient_Sensor_Init(void);

/*
* @brief    This API is used to find the reset the initial values on the system
* @param    Nil
* @return  boolean
* @invocation 
*/
void I2C_Ambient_Sensor_De_Init(void);

/*
* @brief    This API is used to initiate the peripherals
* @param    Nil
* @return   boolean
* @invocation 
*/
void I2C_Ambient_Sensor_Active(void);

/*
* @brief    This API is used to reset the peripheral variables
* @param    Nil
* @return   boolean
* @invocation 
*/
void I2C_Ambient_Sensor_De_active(void);

/*
* @brief    This API is used to get the luminance value from I2C sensor
* @param    Nil
* @return   Nil
* @invocation TFT Derating (Backlight Control Module)
*/
void ALS_Mainfunction (void);

/*
* @brief    This API is used to provide the luminance value which is derived from I2C sensor
* @return    luminance value
* @invocation TFT Derating (Backlight Control Module)
*/
uint16_t Swc_ALS_Get_Luminance_Value(void);


/*
* @brief    This API is used to provide the day or night mode status to TFT
* @param    Nil
* @return   Returns day or night status as a unit8 variable 
* @invocation TFT Derating (Backlight Control Module)
*/
uint8_t ALS_Get_Day_Night_Mode_Info(void);


/*
* @brief     function is used to calculate the luminance value from I2C Sensor based 
             on this lux value can find the day/night mode state 
* @param     lux
* @return    luminance value in float type    
* @invocation TFT Derating (Backlight Control Module)
*/

float Sensor_Read_Luminance_value(void);
uint8_t Get_day_night_mode_status(void);
void ALS_Accumulate_Sample_Process(void);



/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      :	V1.0.0                         
    REVISION DATE        : 08/12/2022        
    CREATED / REVISED BY : Jeevajothi (jeevajothi@niyatainfotech.com)
    DESCRIPTION          : This file consisits of day or night mode status                                    
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! AMBIENT_LIGHT_SENSOR_H */
