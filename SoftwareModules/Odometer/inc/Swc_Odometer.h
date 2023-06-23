
/* @file ODO_H */
#ifndef ODO_H
#define ODO_H

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
*  File name                       : ODO.h
*  Version                         : V1.0.1
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

#include "stdbool.h"
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

/*
* @brief          : This macro is used to configure Invalid value for Odometer
* @Unit           : uint32_t
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : Used to declare invalid state when NVM Error occurs and to display ----- 
* @Note           : Do not modify this macro value or name
*/
#define ODO_INVALID_STATE            (uint32_t)0xFFFFFFFF

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/
/*
* @brief     :This API is used to initialize the Odometer
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void ODO_Init(void);

/*
* @brief     :This API is used to Deinit the Odometer 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void ODO_Deinit(void);

/*
* @brief     :This API is used to Activate the Odometer 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void ODO_Activate(void);

/*
* @brief     :This API is used to Deactivate the Odometer
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void ODO_Deactivate(void);

/*
* @brief     :This API is used to Active the Odometer
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by scheduler
*/
void ODO_Active(void);

/*
* @brief     :This API is used to get distance 
* @param     :NULL
* @return    :Distance (0.1KM Resolution)
* @invocation:This function is called by HMI manager
*/
uint32_t  ODO_Get_Odometer(void);


/*
* @brief     :This API is used to display the odo value 
* @param     :NULL
* @return    :Distance (0.1KM Resolution)
* @invocation:This function is called by HMI manager
*/
uint32_t  Swc_Get_Display_ODO_Value(void);

/*
* @brief     :This API is used to get the trip distance 
* @param     :Trip_Id
* @return    :Trip Distance (0.1KM Resolution)
* @invocation:This function is called by HMI manager
*/
uint32_t  ODO_Get_TripOdometer(uint8_t Trip_Id);

/*
* @brief     :This API is used to get the trip distance 
* @param     :Trip_Id
* @return    :Trip Distance (0.1KM Resolution)
* @invocation:This function is called by HMI manager
*/
void ODO_TripSwitch_Reset(uint8_t fl_ODO_Trip_Index_u8);

/*
* @brief     :This API is used to get the trip distance 
* @param     :Trip_Id
* @return    :Trip Distance (0.1KM Resolution)
* @invocation:This function is called by HMI manager
*/
uint8_t Swc_Odometer_PreCondition(void);

/*
* @brief     :This API is used to get the trip distance 
* @param     :Trip_Id
* @return    :Trip Distance (0.1KM Resolution)
* @invocation:This function is called by HMI manager
*/
uint32_t IFE_ODO_value(void);

/*
* @brief     :This API is used to get the trip distance 
* @param     :Trip_Id
* @return    :Trip Distance (0.1KM Resolution)
* @invocation:This function is called by HMI manager
*/
void Swc_Odo_CM_NVM_Write(void);

/*
* @brief     :This API is used to get the trip distance 
* @param     :Trip_Id
* @return    :Trip Distance (0.1KM Resolution)
* @invocation:This function is called by HMI manager
*/
void Swc_Odo_CM_NVM_Read(void);

/*
* @brief     :This API is used to clear the CAN bus recovery flag
* @param     :Trip_Id
* @return    :Trip Distance (0.1KM Resolution)
* @invocation:This function is called by HMI manager
*/
void Swc_Clear_CAN_BUS_RECOVERY_Flag(void);

/*
* @brief     :This API is used to clear the CAN bus off recovery flag
* @param     :Trip_Id
* @return    :Trip Distance (0.1KM Resolution)
* @invocation:This function is called by HMI manager
*/
uint8_t Swc_Get_CAN_BUS_OFF_Recovery_Counter(void);

/*
* @brief     :This API is used to get the trip distance 
* @param     :Trip_Id
* @return    :Trip Distance (0.1KM Resolution)
* @invocation:This function is called by HMI manager
*/
uint64_t TripOdo_Acc_value(uint8_t trip_id);



void Swc_TripOdo_CM_NVM_Write(void);
void Swc_TripOdo_CM_NVM_Read(void);

/*
* @brief     :This API is used to get Odo nvm error status
* @param     :NONE
* @return    : TRUE OR FALSE
* @invocation:This function is called by Trip computer
*/
bool Swc_Get_ODO_NVM_Error_Status(void);
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
#endif /* ! ODO_H */
