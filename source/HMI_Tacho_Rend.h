/* @file FILE NAME */
#ifndef HMI_TACHO_REND_H
#define HMI_TACHO_REND_H

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
*  File name                       : HMI_Tacho_Rend.c
*  Version                         : v1.0.0
*  Micros supported                : 
*  Compilers supported             : 
*  Platforms supported             :                 
*  Description                     : This header file contains the declarations of Tacho gague rendering process
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/

/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/
#include "Cmp_Init.h"
#include "Swc_Tachometer.h"
#include "Fuel_Guage.h"
/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
/**
* @brief This macro is used to define get current enginer RPM from swc layer
* @Unit:  RPM
* @Resolution: 
* @Range: 0 to 8000
* @Applicability: 
* @Note:  
*/
#define HMI_TACHO_GET_ENGINE_RPM     Tacho_Get_Pointer_Position

#define GA_REND_TACHO_MAXVELG             ((UINT16)300)
#define GA_REND_TACHO_HYSTG               ((UINT16)100)
#define GA_REND_TACHO_T1                  ((UINT8)1)
#define GA_REND_TACHO_T2                  ((UINT8)2)
#define GA_REND_TACHO_GAUGE_COUNT         ((UINT8)1)
#define HMI_TACHO_HYST                    ((UINT16)10)           
/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef is used to define 
 * @param    
 * @return
**/

/*
 * @brief    This typedef enum is used to define ambient modes
 * @param    
 * @param
 **/

/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/
typedef struct
{
   UINT16 MaxVelGx;
   UINT8 HystGx;
   UINT8 Tx1;
   UINT8 Tx2;
   UINT8 Gauge_X_Count;
} GA_REND_CONST_STRUCT;

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to initialize Tacho gauge rendering process
* @param    NONE
* @return   NONE
* @invocation invoked by Os
*/
void HMI_Tacho_Rend_Init(void);

/*
* @brief    This API is used to de initialize Tacho gauge rendering process
* @param    NONE
* @return   NONE
* @invocation invoked by Os
*/
void HMI_Tacho_Rend_DeInit(void);

/*
* @brief    This API is used to do Tacho gauge Rendering process
* @param    NONE
* @return   NONE
* @invocation invoked by Os
*/
void HMI_Tacho_Rend_Mainfunction(void);

/*
* @brief    This API is used to map current Gauge Angle to Image Index 
* @param    Tacho Gauge Pointer angle
* @return   NONE
* @invocation Called Tacho rendering mainfunction
*/
void HMI_Tacho_Image_Mapping(UINT16 p_Current_Gx);

/*
* @brief    This API is used to get current Tacho image index
* @param    NONE
* @return   UINT8_T
* @invocation Called By HMI Layer
*/
uint8_t HMI_Tacho_Rend_Get_Img_Index(void);
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : v1.0.0                          
    REVISION DATE        : 07/18/2022        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)      
    DESCRIPTION          : Initial version                                      
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! FILE NAME */
