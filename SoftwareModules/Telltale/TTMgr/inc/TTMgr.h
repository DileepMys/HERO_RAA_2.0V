
/* @file TTMGR_H */
#ifndef TTMGR_H
#define TTMGR_H

/***********************************************************************************************************************
*   DISCLAIMER
*   Copyright © , 2021 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Maheswari R (maheswari@niyatainfotech.com)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : TTMgr.h
*  Version                         : V1.0.1
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent                
*  Description                     : This header file contains the declarations of Tell-Tale Manager APIs
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/***********************************************************************************************************************
*                                               I N C L U D E   C O N F I G U R A T I O N   F I L E S 
***********************************************************************************************************************/
#include "TTMgr_Cfg.h"

/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED   F I L E S                             
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                             M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief         :This API is used to send Tell-Tale command
* @param         :TellTale_ID,Status
* @return        :NULL
* @invocation    :This function is invoked by Tell-Tale Application
*/

void TT_Mgr_Command( uint8_t fl_TT_ID_u8,  uint8_t fl_TT_Status_u8 );

/*
* @brief         :This API is used to initialize the Tell-Tale Manager 
* @param         :NULL
* @return        :NULL
* @invocation    :This function is invoked by scheduler 
*/
void TT_Mgr_init( void);

/*
* @brief         :This API is used to deinitialize the Tell-Tale Manager  
* @param         :NULL
* @return        :NULL
* @invocation    :This function is invoked by scheduler 
*/
 void TT_Mgr_Deinit( void);

/*
* @brief         :This API is used to Active the Tell-Tale Manager  
* @param         :NULL
* @return        :NULL
* @invocation    :This function is invoked by scheduler 
*/
 void TT_Mgr_Active( void);

/*
* @brief         :This API is used to Deactivate the Tell-Tale Manager 
* @param         :NULL
* @return        :NULL
* @invocation    :This function is invoked by scheduler 
*/
 void TT_Mgr_Deactivate( void);

/*
* @brief         :This API is used to Activate the Tell-Tale Manager 
* @param         :NULL
* @return        :NULL
* @invocation    :This function is invoked by scheduler 
*/
void TT_Mgr_Activate( void);


/*
* @brief         :This API is used to set the all tell-tales  
* @param         :NULL
* @return        :NULL
* @invocation    :This function is invoked by Tell-Tale Manager
*/
void TT_Mgr_SetAll( void);

/*
* @brief         :This API is used to clear the all tell-tales  
* @param         :NULL
* @return        :NULL
* @invocation    :This function is invoked by Tell-Tale Manager
*/
 void TT_Mgr_ClearAll( void);

/*
* @brief         :This API is used to set the self check state 
* @param         :NULL
* @return        :NULL
* @invocation    :This function is invoked by Tell-Tale application
*/
 void TT_Mgr_Proveout(void);

/*
* @brief         :This API is used to diognostic the tell-tales 
* @param         :uint8_t -TellTale_ID
* @return        :uint8_t -TellTale_Current_Status
* @invocation    :This function is invoked by Tell-Tale application
*/
 uint8_t TT_Mgr_Diagnostic(uint8_t fl_TT_ID_u8);

/*
* @brief         :This API is used to get the tell-tale pre condition
* @param         :uint8_t -TellTale_ID
* @return        :uint8_t -TellTale_Current_Status
* @invocation    :This function is invoked by Tell-Tale application
*/

 uint8_t Swc_TT_Pre_Condition(void);

void SIDE_STAND_LED_ON(void);

void SIDE_STAND_LED_OFF(void);
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
***********************************************************************************************************************
			REVISION NUMBER      : V1.0.1                                                
			REVISION DATE        : 28-12-2020                             
			CREATED / REVISED BY : R Maheswari (maheswari@niyatainfotech.com)  
			DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------
			REVISION NUMBER      : V1.0.1                                                
			REVISION DATE        : 20-01-2021                              
			CREATED / REVISED BY : R Maheswari (maheswari@niyatainfotech.com)   
			DESCRIPTION          : Peer reveiew comments fixed 
***********************************************************************************************************************/
#endif /* ! TTMGR_H */



