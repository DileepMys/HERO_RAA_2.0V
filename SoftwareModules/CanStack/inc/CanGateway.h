/* @file FILE NAME */
#ifndef CANGATEWAY_H
#define CANGATEWAY_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Balajipandurangan (Balaji.pandurangan@niyatainfotech.com)                                                                        
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : CanGateway.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : MCU Xpresso IDE
*  Platforms supported             : XXXXX                
*  Description                     : This header file contains the declarations of CanGateway
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
#include "CanIF_cfg.h"
#include "CanGateway_cfg.h"

/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
        

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef enum is used to define state machine for can gateway
 * @param    CAN_VEHICLE    - vehicle can message
 * @param    CAN_DIAG       - Diag can message
 **/
typedef enum
{
    CAN_VEHICLE = 0,
    CAN_DIAG
}Gateway_CanBase_en;

/*
 * @brief    This typedef is used to define the cangateway can bus off
 * @param    CANGATEWAY_CAN_BUS_OFF
 * @param    CANGATEWAY_CAN_BUS_ON
 **/
typedef enum
{
	CANGATEWAY_CAN_BUS_OFF = 0,
	CANGATEWAY_CAN_BUS_ON
}CanGateway_BusOff_Mode_en;

/*
 * @brief    This structure is used to define of Vehicle request input and output message ID's
 * @param    Vehicle_Input_ID  - Vehicle Input message ID
 * @param    Vehicle_Output_ID - Vehicle Output message ID
 **/
typedef struct 
{
    /* data */
    uint16_t GateWay_Input_ID_u16;
    uint16_t GateWay_Output_ID_u16;

}CanGateway_ReqRes_ID_st;


/*
* @brief: This variable is used to configure mapping table for Diag can message
* @Unit:  n/a
* @Resolution: n/a
* @Range: 0 - 5
* @Applicability: YES
* @Note: 
*/
extern const CanGateway_ReqRes_ID_st g_CanGateway_Diag_Mapping_Table[REQUEST_GATEWAY_TOTAL_MESSAGES];

/*
* @brief: This variable is used to configure mapping table for vehicle can message
* @Unit:  n/a
* @Resolution: n/a
* @Range: 0 - 5
* @Applicability: YES
* @Note: 
*/
extern const CanGateway_ReqRes_ID_st g_CanGateway_Vehicle_Mapping_Table[RESPONSE_GATEWAY_TOTAL_MESSAGES];

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
 * @brief           This function processes the cangateway initialization
 * @param           void
 * @return          void
 * @invocation      Cmp_init.c will call this function.
 */
void CanGateway_init(void);

/*
 * @brief           This function processes the de-init of cangateway
 * @param           void
 * @return          void
 * @invocation      
 */
void CanGateway_Deinit(void);

/*
 * @brief           This function processes the can gateway request Rx
 * @param           RxPduId         Request Message ID. 
 * @param           PduInfoPtr      Data received from user.     
 * @return          void
 * @invocation      CanIF.c will call this function
 */
void Gateway_Request_Rx(PduIdType CanRxPduId, const uint8_t* CanSduPtr, Can_IdType CanId);


/*
 * @brief           This function processes the can gateway response Rx
 * @param           RxPduId         Request Message ID. 
 * @param           PduInfoPtr      Data received from user.    
 * @return          void
 * @invocation      CanIF.c will call this function
 */
void Gateway_Response_Rx(PduIdType RxPduId, const PduInfoType *PduInfoPtr);

/*
 * @brief           This function processes the can gateway request Tx
 * @param           RxPduId         Request Message ID. 
 * @param           PduInfoPtr      Data received from user.       
 * @return          void
 * @invocation      CanGateway.c will call this function
 */
void Gateway_Request_Tx(PduIdType RxPduId);


/*
 * @brief           This function processes the can gateway response Tx.
 * @param           RxPduId         Request Message ID.    
 * @return          void
 * @invocation      CanGateway.c will call this function
 */
void Gateway_Response_Tx(PduIdType RxPduId);

/*
 * @brief           
 * @param           
 * @return          
 * @invocation      CanGateway.c will call this function
 */
void CanMgr_GateWayPeriodicTask(void);

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
    REVISION DATE        : 07/24/2022                              
    CREATED / REVISED BY : Balaji Pandurangan (balaji.pandurangan@niyatainfotech.com) 
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! CANGATEWAY */
