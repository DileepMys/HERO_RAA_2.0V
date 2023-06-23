/* @file FILE NAME */
#ifndef TELL_TALE_OIL_PRESSURE_H
#define TELL_TALE_OIL_PRESSURE_H

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
*  File name                       : oil Pressure.h
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

#include "Swc_TT_Oil_Pressure_cfg.h"
#include "stdint.h"
/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/
/*
 * @brief: This API shall is used to initialize the init variables with defult values
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
void TT_Oil_Pressure_Init(void);


/*
 * @brief: This configuration shall configure the NVM Functionality  
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
void TT_Oil_Pressure_DeInit(void);

/*
 * @brief: This API is used to configure the intial variables  
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
void TT_Oil_Pressure_Activate(void);

/*
 * @brief: This API is used to reset the  intial variables  
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
void TT_Oil_Pressure_DeActivate(void);

/*
 * @brief: This API is used to configure the main  telltale oil pressure functions  
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
void TT_Oil_Pressure_MainFunction(void);

/*
 * @brief: This configuration shall configure the NVM Functionality  
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
uint8_t TT_Oil_Pressure_Pre_Condition(void);

/*
 * @brief: This API is used to actual value of the telltale oil pressure 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
uint8_t Swc_Oil_Pressure_Get_Value(void);

/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

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
#endif /* ! TELL_TALE_OIL_PRESSURE_H */
