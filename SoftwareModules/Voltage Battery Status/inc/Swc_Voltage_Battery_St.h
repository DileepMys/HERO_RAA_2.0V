/* @file FILE NAME */
#ifndef VOLTAGE_BATTERY_STATUS_H
#define VOLTAGE_BATTERY_STATUS_H

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
*  File name                       : Voltage BAttery.h
*  Version                         : V1.0.0
*  Micros supported                : 
*  Compilers supported             : J link
*  Platforms supported             : 
*  Description                     : This file contains Macros, Typdef and Function Declarations for gear_position files
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/

#include "Swc_Voltage_Battery_St_Cfg.h"
#include "stdbool.h"
#include "hal_stdtypes.h"

/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/

/*
* @brief    This API is used to initialize the variables with default initial values
* @param    NA
* @return   NA
* @invocation  This function is invoked by OS
*/
void Voltage_Battery_Init(void);

/*
* @brief    This API is used to reset the variables with default initial values
* @param    NA
* @return   NA
* @invocation  This function is invoked by OS
*/
void Voltage_Battery_DeInit(void);

/*
* @brief    This API is used to initialize the peripherals
* @param    NA
* @return   NA
* @invocation  This function is invoked by OS
*/
void Voltage_Battery_Activate(void);

/*
* @brief    This API is used to de-initialize the peripherals
* @param    NA
* @return   NA
* @invocation  This function is invoked by OS
*/
void Voltage_Battery_DeActivate(void);

/*
* @brief    This API is used to execute the battery voltage main system 
* @param    NA
* @return   NA
* @invocation  This function is invoked by OS
*/
void Voltage_Battery_MainFunction(void);

/*
* @brief    This API is used to check the pre condition status of the  battery voltage status
* @param    NA
* @return   bool
* @invocation  This function is invoked by OS
*/
bool Voltage_Battery_Pre_Condition(void);

/*
* @brief    This API is used to get the battery voltage value
* @param    NA
* @return   uint32_t
* @invocation  This function is invoked by OS
*/
uint32_t Voltage_Battery_Get_Value(void);










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
* @brief This macro is used to define for advisory
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/
#define    NINE   (uint32_t)   9



/**
* @brief This macro is used to define for advisory 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/




/**
* @brief This macro is used to define  for advisory
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/

#define   TEN  (uint32_t)     10


/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef is used to define for gear position
 * @param    
 * @return
 **/


/*
 * @brief    This Function is used to define gear shift advisory
 * @param    
 * @param
 **/


/*
 * @brief    This Function is used to define gear position
 * @param    
 * @param    
 **/






/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/



/*
 * @brief    This structure is used to define for indication
 * @param    
 * @param    
 **/



/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/

/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/

/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/

/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/

/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/







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
    REVISION NUMBER      : Major.Minor.Patch                                                
    REVISION DATE        : MONTH/DATE/YEAR                              
    CREATED / REVISED BY : Balasubramaniyan (balasubramaniyan.s@niyatainfotech.com)
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! FILE NAME */
