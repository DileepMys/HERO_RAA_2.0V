/* @file FILE NAME */
#ifndef I2C_HANDLER_H
#define I2C_HANDLER_H

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
*  File name                       : I2C_Handler.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : J-Link
*  Platforms supported             : Platform Independent                
*  Description                     : This header file contains the declarations of I2C handler
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include "I2C_Handler_Cfg.h"
#include "hal_stdtypes.h"
/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
/*
* @brief This macro is used to define master base address 
* @Unit:  na
* @Resolution:n/a 
* @Range: n/a
* @Applicability: nil
* @Note:  
*/
#define EXAMPLE_LPI2C_MASTER_BASEADDR LPI2C5            

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/



/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to initialize the init variables with default values
* @param    nil
* @return   nil
* @invocation  invoked by ALS        
*/
void I2C_Handler_Init(void);

/*
* @brief    This API is used to reset the initial values of the variables
* @param    nil
* @return   nil
* @invocation  invoked by ALS        
*/
void I2C_Handler_De_Init(void);

/*
* @brief    This API is used to activate the peripherals
* @param    nil
* @return   nil
* @invocation  invoked by ALS        
*/
void I2C_Handler_Activate(void);

/*
* @brief    This API is used to de activate the peripherals
* @param    nil
* @return   nil  
* @invocation  invoked by ALS        
*/
void I2C_Handler_DeActivate(void);

/*
* @brief    This API is used to write data on the I2C
* @param    data information (length,data,page)
* @return   data
* @invocation invoked by ALS        
*/
uint8_t i2c_write_page(uint8_t page, uint8_t * data,uint8_t len);

/*
* @brief    This API is used to read the data in the I2C
* @param    data information (length,data,page)
* @return   data
* @invocation invoked by ALS        
*/

uint8_t i2c_read_page (uint8_t page, uint8_t * data,uint8_t len);

uint32_t Get_Delay_Cnt(void);
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                                               
    REVISION DATE        : MONTH/DATE/YEAR                              
    CREATED / REVISED BY : NAME (EMAIL-ID)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! I2C_HANDLER_H */
