/* @file FILE NAME */
#ifndef MAIN_INIT_H
#define MAIN_INIT_H

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
*  File name                       : 
*  Version                         : 
*  Micros supported                : 
*  Compilers supported             : 
*  Platforms supported             :                 
*  Description                     : This header file contains the declarations of 
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
//#include "task.h"
#include "Cmp_Tasks.h"
#include "pin_mux.h"

/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/
#if SYSTEM_1
# include "system_1.h"
#elif SYSTEM_2
# include "system_2.h"
#elif SYSTEM_3
#endif


/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
/**
* @brief This macro is used to define 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef is used to define 
 * @param    
 * @return
 **/


/*
 * @brief    This typedef enum is used to define 
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
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
***********************************************************************************************************************
    REVISION NUMBER      : Major.Minor.Patch                                                
    REVISION DATE        : MONTH/DATE/YEAR                              
    CREATED / REVISED BY : NAME (EMAIL-ID)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! MAIN_INIT_H */
