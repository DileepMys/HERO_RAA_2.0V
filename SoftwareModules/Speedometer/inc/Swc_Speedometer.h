
/* @file SPEEDO_H */
#ifndef SPEEDO_H
#define SPEEDO_H

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
*  File name                       : Speedo.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent                
*  Description                     : This header file contains the declarations of Odometer APIs
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/
/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   C O N F I G U R A T I O N   F I L E S 
***********************************************************************************************************************/
#include "stdint.h"
#include "hal_stdtypes.h"
#include "Swc_Speedometer_Cfg.h"
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
* @brief     :This API is used to initialize the Speedometer
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void Speedometer_Init(void);

/*
* @brief     :This API is used to Deinit the Speedometer 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void Speedometer_Deinit(void);

/*
* @brief     :This API is used to Activate the Speedometer 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void Speedometer_Activate(void);

/*
* @brief     :This API is used to Deactivate the Speedometer
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void Speedometer_Deactivate(void);

/*
* @brief     :This API is used to Active the Speedometer
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void Speedometer_Active(void);

/*
* @brief     :This API is used to get call back for CAN signal timeout
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void CanMgr_Speedo_Timeout_Callback_0x206(void);

/*
* @brief     :This API is used to get timeout flag for CAN speedo value
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void CanMgr_Speedo_Timeout_Flag(void);

/*
* @brief     :This API is used to callback the CANMGR speedo value
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void CanMgr_Speedo_reception_cbk(void);

/*
* @brief     :This API is used to check pre condition status of the Speedometer
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
uint8_t Swc_Speedometer_Pre_Condition(void);

/*
* @brief     :This API is used to get the Speedometer value
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
uint32_t GET_Speedometer_Value(void);

/*
* @brief     :This API is used to get spped value which needs to be display on the speedo meter
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
uint32_t Get_display_Speed(void);

/*
* @brief     :This API is used to get the Speedometer fault status
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
uint8_t Swc_Get_Speedometer_Fault_Status(void);

/*
* @brief     :This API is used to get raw speed value 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
uint16_t Swc_Get_RAW_Speedo_Val(void);

/*
* @brief     :This API is used to get raw speed value 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by applicaton layer
*/
bool Swc_Speedo_Get_Msg_TimeOut_Staus(void);
/***********************************************************************************************************************
                                             E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/
#ifdef __cplusplus
}
#endif
/***********************************************************************************************************************
                                             E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
***********************************************************************************************************************
REVISION NUMBER      : V1.0.0                                                
REVISION DATE        : 30-04-2021                             
CREATED / REVISED BY : maheswari@niyatainfotech.com   
DESCRIPTION          : Initial version 

REVISION NUMBER      : V1.0.1
REVISION DATE        : 26-May-2021
CREATED / REVISED BY : Maheswari R(maheswari@niyatainfotech.com)
DESCRIPTION          : Peer Review comments fixed 


------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! SPEEDO_H */
