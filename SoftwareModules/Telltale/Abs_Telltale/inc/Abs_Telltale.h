/* @file TTMGR_H */
#ifndef ABS_TELLTALE_H
#define ABS_TELLTALE_H

/***********************************************************************************************************************
*   DISCLAIMER
*   Copyright © , 2021 Niyata Infotech Pvt. Ltd. All rights reserved.
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Balaji Pandurangan (Balaji.Pandurangan@niyatainfotech.com)
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : TTMgr.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent
*  Description                     : This file contains the Implementation of header implementation of Abs Tell-Tale
*  @bug                            :
--------------------------------------------------------------------------------------------------------------------*/
/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
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
/*
* @brief This macro is used to define ignition ON and Ignition OFF state
* @Unit:  NA
* @Resolution: NA
* @Range: NA
* @Applicability: During pre condition check
* @Note:  
*/
typedef enum
{
	Ign_ON = 1,
	Ign_OFF = 2

}Ignition_Mode;


/*
* @brief This macro is used to define shutdown voltage state such as LVSD and HVSD
* @Unit:  voltage
* @Resolution: NA
* @Range: NA
* @Applicability: During pre condition check
* @Note:  
*/
typedef enum
{
	LVSD = 0,
	HVSD = 1

}Voltage_Mode;

/*
* @brief This macro is used to define ABS status whether it is ON/OFF
* @Unit:  NA
* @Resolution: NA
* @Range: NA
* @Applicability: During ABS telltale status
* @Note:  
*/
typedef enum
{
	ABS_ON = 1,
	ABS_OFF = 2,
	ABS_BLINK
}Abs_Status;

/*
* @brief This macro is used to define the ABS value
* @Unit:  NA
* @Resolution: NA
* @Range: Nil
* @Applicability: Nil
* @Note:  
*/
typedef enum
{
	ZER0 = 0x0,
	ONE = 0x1,
	TWO = 0x2,
	THREE = 0x3
}Abs_Value;

/*
* @brief This macro is used to define CAN bus status
* @Unit:  NA
* @Resolution: NA
* @Range: Nil
* @Applicability: Nil
* @Note:  
*/
typedef enum
{
	CAN_BUS_ON = 0,
	CAN_BUS_OFF = 1
	
}BusOff_Mode;


/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N
***********************************************************************************************************************/
/*
* @brief         :This API is used to initiallize the init variables with default initial values
* @param         : Nil
* @return        : Nil
* @invocation    : Nil
*/
void Abs_TT_init(void);

/*
* @brief         :This API is used to reset the init variables with default initial values
* @param         : Nil
* @return        : Nil
* @invocation    : Nil
*/
void Abs_TT_Deinit(void);

/*
* @brief         :This API is used to activate the peripherals
* @param         : Nil
* @return        : Nil
* @invocation    : Nil
*/
void Abs_TT_Active(void);

/*
* @brief         :This API is used to Deactivate the peripherals
* @param         : Nil
* @return        : Nil
* @invocation    : Nil
*/
void Abs_TT_DeActive(void);

/*
* @brief         :This API is used to get CAN bus off status
* @param         : Nil
* @return        : Nil
* @invocation    : Nil
*/
uint8_t Get_CanBusOff(void);

/*
* @brief         :This API is used to get timeout call back for ABS from CAN manager
* @param         : Nil
* @return        : Nil
* @invocation    : Nil
*/
void CanMgr_ABS_Timeout_Callback_0x205(void);

/*
* @brief         :This API is used to get ABS telltale status
* @param         : Nil
* @return        : Nil
* @invocation    : Nil
*/
uint8_t Get_ABS_TT_Status(void);

/*
* @brief         :This API is used to get ABS telltale timeout flag
* @param         : Nil
* @return        : Nil
* @invocation    : Nil
*/
void CanMgr_Abs_Timeout_Flag(void);

/*
* @brief         :This API is used to get ABS callback on reception from CAN manager
* @param         : Nil
* @return        : Nil
* @invocation    : Nil
*/
void CanMgr_Abs_reception_cbk(void);

/*
* @brief         :This API is used to get ABS precondition check such as ignition On/Off,LVSD/HVSD
* @param         : Nil
* @return        : Nil
* @invocation    : Nil
*/
uint8_t Swc_Abs_Pre_Condition(void);

void CanMgr_Abs_Timeout_Flag(void);

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E
*********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y
***********************************************************************************************************************
			REVISION NUMBER      : V1.0.1
			REVISION DATE        : 28-12-2020
			CREATED / REVISED BY : R Maheswari (maheswari@niyatainfotech.com)
			DESCRIPTION          : Initial version
***********************************************************************************************************************/
#endif /* ! ABS_TELLTALE_H */

