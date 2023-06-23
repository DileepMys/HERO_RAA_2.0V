
/* @file TACHO_H */
#ifndef TACHO_H
#define TACHO_H

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
*  File name                       : TACHO.h
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
#include "Swc_Tachometer_Cfg.h"
#include "hal_stdtypes.h"
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
* @brief     :This API is used to initialize the TACHOmeter
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void Tachometer_Init(void);

/*
* @brief     :This API is used to Deinit the TACHOmeter 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void Tachometer_Deinit(void);

/*
* @brief     :This API is used to Activate the TACHOmeter 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void Tachometer_Activate(void);

/*
* @brief     :This API is used to Deactivate the TACHOmeter
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void Tachometer_Deactivate(void);

/*
* @brief     :This API is used to Active the TACHOmeter
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void Tachometer_Active(void);


/*
* @brief     :This API is used to check the pre condition status such as Ignition on/off, HVSD/LVSD state 
* @param     :NULL
* @return    :uint8_t
* @invocation:This function is invoked by scheduler
*/
uint8_t Swc_Tachometer_Pre_Condition(void);


/*
* @brief     :This API is used to get the call back status TACHOmeter state
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
uint32_t TACHOMETER_GET_CALL_BACK_STATE(void);


/*
* @brief     :This API is used to get timeout call back from CAN mgr 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void CanMgr_Tacho_Timeout_Callback_0x130(void);


/*
* @brief     :This API is used to Activate the tacho timout flag  from CAN
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void CanMgr_Tacho_Timeout_Flag(void);


/*
* @brief     :This API is used to get tacho reception call back from canmgr 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void CanMgr_Tacho_reception_cbk(void);


/*
* @brief     :This API is used to Activate the TACHOmeter 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void CanMgr_Gear_Position_Timeout_Flag(void);


/*
* @brief     :This API is used to get status of TACHO timout 
* @param     :NULL
* @return    :bool
* @invocation:This function is invoked by scheduler
*/
bool Swc_Tacho_CAN_Msg_Timeout_Staus(void);

const uint16_t Tacho_Get_Pointer_Position(void);
/***********************************************************************************************************************
                                             E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/

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
#endif /* ! TACHO_H */
