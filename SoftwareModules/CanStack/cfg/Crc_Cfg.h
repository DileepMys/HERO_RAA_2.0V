#ifndef CRC_CFG_H_
#define CRC_CFG_H_


/***********************************************************************************************************************
*    DISCLAIMER                                                                                                        
*   Copyright (C) 2011, 2016 Niyata Infotech Ptv. Ltd. All rights reserved.                                              
***********************************************************************************************************************/

/***********************************************************************************************************************
 * @author              Author :    Sharmili N (sharmili@niyatainfotech.com)                                                                        
***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N                                           
 *---------------------------------------------------------------------------------------------------------------------
 *  @brief                                                                                                             
 * 
*  File name                       :  Crc_Cfg.h                                                                         
*  Version                         : V4.2.3   
*  Micros supported                :  Micro Agnostic (Independent)
*  Compilers supported             :  XXXXX                                                                           
*  Platforms supported             :  XXXXX
*  Description                     : This file contains the configuration declarations of Crc                             
*                                                                                                                     
*                                                                                                                     
*  @bug                                                                                                               
*---------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/
/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S      
***********************************************************************************************************************/
#include "CrcTypes.h"


/**********************************************************************************************************************
*                                    C O N F I G U R A T I O N     M A C R O S      
**********************************************************************************************************************/
/**********************************************************************************************************************
* @brief : This macro is used to configure the CRC calculation standards like SAE J1850
* @Unit:  N/A
* @Resolution: N/A
* @Range: CRC8_SAE_J1850
* @Applicability: Yes
* @Note: Currently only SAE J1850 standard is available to be configured 
*/

#define CRC_CALCULATION_METHOD      CRC8_SAE_J1850

#if(CRC_CALCULATION_METHOD == CRC8_SAE_J1850)
/*
* @brief: This macro is used to configure the Polynomial value for the CRC8 calculation
* @Unit:  N/A
* @Resolution: N/A
* @Range: 0x00 to 0xFF
* @Applicability: Yes
*/
#define CRC8_POLYNOMIAL_VALUE        (uint8_t)0x1D

/*
* @brief: This macro is used to configure the Initial value for the CRC8 calculation
* @Unit:  N/A
* @Resolution: N/A
* @Range: 0x00 to 0xFF
* @Applicability: Yes
*/
#define CRC8_INIT_VALUE        (uint8_t)0xFF

/*
* @brief: This macro is used to configure the XOR value for the CRC8 calculation
* @Unit:  N/A
* @Resolution: N/A
* @Range: 0x00 to 0xFF
* @Applicability: Yes
*/
#define CRC8_XOR_VALUE        (uint8_t)0xFF

/*
* @brief: This macro is used to configure the mode of calculating CRC as per SAE J1850's standard
* @Unit:  N/A
* @Resolution: N/A
* @Range: CRC8_RUNTIME_CALCULATE/ CRC8_HASHTABLE_CALCULATE
* @Applicability: Yes
*/
#define CRC8_CALCULATE_MODE        CRC8_HASHTABLE_CALCULATE

/*
* @brief: This macro is used to calculate DATA ID used in CRC Calculation 
* @Unit:  uint16_t
* @Resolution: N/A
* @Range: 0xF008
* @Applicability: Yes
*/
#define HERO_DEFAULT_ID                 0xF008

#endif /*CRC_CALCULATION_METHOD*/


/**********************************************************************************************************************
*                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/**********************************************************************************************************************
                                                R E V I S I O N   H I S T O R Y                                        
***********************************************************************************************************************
**********************************************************************************************************************
**********************************************************************************************************************
     REVISION NUMBER      : V1.0.0                                                                                   
     REVISION DATE        : 24-Feb-2021
     CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)                                        
     DESCRIPTION          : Initial version                                                                          
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
#endif /* CRC_CFG_H */
