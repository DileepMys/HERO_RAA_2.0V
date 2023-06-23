/* @file OPT3001_DRIVER_H */
#ifndef OPT3001_DRIVER_H
#define OPT3001_DRIVER_H

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
*  File name                       : OPT3001_driver
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent
*  Description                     : This file consists of definition of I2C sensor function declarations.
*  @bug
--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include "Cmp_Init.h"
/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/
/* perform integrity check when it is necessary */

/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
/*
* @brief This macro is used to define 
* @Unit: nil 
* @Resolution: nil
* @Range: nil
* @Applicability: I2C sensor performance
* @Note:  
*/
#define ALS_LPI2C_MASTER_BASEADDR LPI2C6

/*
* @brief This macro is used to define the register addresses
* @Unit:  nil
* @Resolution: nil 
* @Range: nil
* @Applicability: I2C register address
* @Note:  
*/
/* Register addresses */
#define REG_RESULT                      0x00
#define REG_CONFIGURATION               0x01
//#define REG_LOW_LIMIT                   0x02
//#define REG_HIGH_LIMIT                  0x03
//#define REG_MANUFACTURER_ID             0x7E
//#define REG_DEVICE_ID                   0x7F
#define Range_field 					0XC610




/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/
/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/

struct ti_opt3007_deviceRegister{
	uint8_t msb;
	uint8_t lsb;
	uint8_t address;
};

typedef struct ti_opt3007_deviceRegister ti_opt3007_deviceRegister;

struct ti_opt3007_registers{
	ti_opt3007_deviceRegister R;
	ti_opt3007_deviceRegister E;
	ti_opt3007_deviceRegister RN;
	ti_opt3007_deviceRegister CT;
	ti_opt3007_deviceRegister M;
	ti_opt3007_deviceRegister OVF;
	ti_opt3007_deviceRegister CRF;
	ti_opt3007_deviceRegister FH;
	ti_opt3007_deviceRegister FL;
	ti_opt3007_deviceRegister L;
	ti_opt3007_deviceRegister POL;
	ti_opt3007_deviceRegister ME;
	ti_opt3007_deviceRegister FC;
	ti_opt3007_deviceRegister LE;
	ti_opt3007_deviceRegister TL;
	ti_opt3007_deviceRegister HE;
	ti_opt3007_deviceRegister TH;
	ti_opt3007_deviceRegister ID;
	ti_opt3007_deviceRegister DID;
};

typedef struct ti_opt3007_registers      ti_opt3007_registers;

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to intialize the variables with default values
* @param   nil 
* @return  nil
* @invocation na 
*/

void OPT3001_Init(void);

/*
* @brief    This API is used to reset the initial variables
* @param   nil 
* @return  nil
* @invocation  nil 
*/

void OPT3001_DeInit_(void);

/*
* @brief    This API is used to activate the peripherals
* @param 	nil   
* @return   nil
* @invocation nil
*/
void OPT3001_Active(void);

/*
* @brief    This API is used to deactivate the peripherals
* @param   nil 
* @return  nil
* @invocation nil
*/
void OPT3001_De_active(void);

/*
* @brief    This API is used to get the lux value from I2C sensor
* @param    configuration register and data 
* @return  	lux value
* @invocation used to perfor the day or noght status
*/
uint16_t OPT3001_Get_Lux_Value(uint8_t Configure_reg,uint16_t Config_data);

/*
* @brief    This API is used to read the ambient light sensor value
* @param   	Nil 
* @return  	Sensor value which is received from the I2C sensor
* @invocation day/night mode staus
*/
uint16_t ALS_read (void);

/*
* @brief    This API is used to toggle the pin configuration
* @param    
* @return  
* @invocation 
*/
void pin_toggle(void);

/*
* @brief    This API is used to 
* @param    
* @return  
* @invocation 
*/
float I2C_Sensor_value_lux_conversion();
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      :	v1.0.0                         
    REVISION DATE        :  08/12/2022        
    CREATED / REVISED BY : Jeevajothi (jeevajothi@niyatainfotech.com)
    DESCRIPTION          : This file consisits of day or night mode status                                   
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! OPT3001_DRIVER_H */
