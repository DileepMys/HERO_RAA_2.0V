/* @file FILE NAME */
#ifndef TELL_TALE_FOG_LAMP_H
#define TELL_TALE_FOG_LAMP_H

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
*  File name                       : gear_position.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : COSMIC
*  Platforms supported             : Platform Independent
*  Description                     : This file contains Macros, Typdef and Function Declarations for gear_position files
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/
/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/

#include "Swc_TT_Fog_Lamp_Cfg.h"
#include "stdint.h"
#include "hal_stdtypes.h"
/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/

/*
 * @brief    This function processes to initialize the init variables with default values
 * @param    NA
 * @return   NA
 */
void TT_Fog_Lamp_Init(void);

/*
 * @brief    This function processes to reset the init variables with default values
 * @param    NA
 * @return   NA
 */
void TT_Fog_Lamp_DeInit(void);

/*
 * @brief    This function processes to initialize the peripherals
 * @param    NA
 * @return   NA
 */
void TT_Fog_Lamp_Activate(void);

/*
 * @brief    This function processes to Deinitialize the peripherals
 * @param    NA
 * @return   NA
 */
void TT_Fog_Lamp_DeActivate(void);

/*
 * @brief    This API processes the foglamp telltale process 
 * @param    NA
 * @return   NA
 */
void TT_Fog_Lamp_MainFunction(void);

/*
 * @brief    This API is used to check the pre condition status such as ignition on/off, LVSD/HVSD 
 * @param    NA
 * @return   bool
 */
bool TT_Fog_Lamp_Pre_Condition(void);

/*
 * @brief    This API is used to get the value for foglamp telltale unit
 * @param    NA
 * @return   uint8
 */
uint8_t Swc_Fog_LAmp_Get_Value(void);

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

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/



/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0
    REVISION DATE        : 2/19/2021        
    CREATED / REVISED BY : Balasubramaniyan (balasubramaniyan.s@niyatainfotech.com)
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! FOG_LAMP_H */
