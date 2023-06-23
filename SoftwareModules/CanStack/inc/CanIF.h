#ifndef CANIF_H
#define CANIF_H
/*********************************************************************************************************************** 
 *    DISCLAIMER                                                                                                        
 *   Copyright (C) 2011, 2016 Niyata Infotech Ptv. Ltd. All rights reserved.                                              
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * @author              Author : Akshay Bavalatti (akshayb@niyatainfotech.com)                                                                         
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N                                           
 *---------------------------------------------------------------------------------------------------------------------
 *  @brief                                                                                                             
 *                                                                                                                     
 *  File name                       : CanIF.h                                                                         
 *  Version                         : V1.0.0                                                                           
 *  Micros supported                : Micro Agnostic (Independant)                                                            
 *  Compilers supported             : XXXX                                                                           
 *  Platforms supported             : XXXX                                                                            
 *  Description                     : This file contains function decalaration for CanIF Layer                                
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
 *                          I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "CanIF_cfg.h"
#include "fsl_flexcan.h"
/***********************************************************************************************************************
 *                          P R O T O T Y P E    D E C L A R A T I O N
 ***********************************************************************************************************************/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
#define CAN_IF_ALIVE_COUNTER()              CAN_IF_INFORM_ALIVE_STATUS()
#endif

void CanIf_Init(void);
void CanIf_DeInit(void);
void CanIF_RxIndication(CAN_Type *base, flexcan_frame_t *CanIF_RxFrame, uint8_t result);
Std_ReturnType CanIf_Transmit(PduIdType Mgr_CanTxPduId,const PduInfoType* PduInfoPtr);
Std_ReturnType CanIf_SetControllerMode(uint8_t Channel, CanIf_ControllerModeType ControllerMode);
Std_ReturnType CanIf_GetControllerMode(uint8_t Channel, CanIf_ControllerModeType* ControllerModePtr);
Std_ReturnType CanIf_SetPduMode(uint8_t Channel, const CanIf_PduModeType PduModeRequest);
Std_ReturnType CanIf_GetPduMode(uint8_t Channel, CanIf_PduModeType* PduModePtr);
Std_ReturnType  CanIF_NetworkRequest(uint8_t Channel,CanIF_Network_Request_Type fl_CanIF_Network_Request);
void flexcan_Diag_callback(CAN_Type * base, flexcan_handle_t * handle, status_t status, uint64_t result, void *userData);
void CanMessage_Vehicle_BusOff_Counter(bool Vehicle_bus_OFF_State);
void CanMessage_Diag_BusOff_Counter(bool Diag_bus_OFF_State);

void Vehicle_flexcan_callback(CAN_Type * base, flexcan_handle_t * handle, status_t status, uint64_t result, void *userData);

#ifdef CANIF_ALL_API_SUPPORTED

Std_ReturnType CanIf_SetBaudrate(uint8_t Channel, uint16_t BaudRateConfigID);
Std_ReturnType CanIf_ChangeBaudrate(uint8_t Channel, const uint16_t Baudrate);
Std_ReturnType CanIf_CheckBaudrate(uint8_t Channel, const uint16_t Baudrate);

#endif

/************************************************************************************************************
 * NAME:  Can_NM_State_Machine_MainFunction
 ************************************************************************************************************
 *  \brief         Process the Network Request given by the function CanIF_NetworkRequest.
 *  \details       Request by CanIF_NetworkRequest is processed here. This function has to be configured in
 *                 TIME TASK with the periodicity of ms. All the states in the functions are configured with
 *                 Timeout, if timeout occurs then a callback will be notified to the upper layer on Request
 *                 not processed.
 *  \param[in]
 *  \pre           CanIf_Init function has to be called.
 *  \context       TIME TASK
***********************************************************************************************************/
void Can_NM_State_Machine_MainFunction(void);


typedef enum {
  CAN_NOT_OK = 0,
  CAN_OK = 1,
  CAN_BUSY = 3,
} Can_ReturnType;


typedef enum Can_ControllerStateType_enum {

    CAN_CS_UNINIT  = 0x00, /* CAN controller state UNINIT.  */
    CAN_CS_STARTED = 0x01, /* CAN controller state STARTED. */
    CAN_CS_STOPPED = 0x02, /* CAN controller state STOPPED. */
    CAN_CS_SLEEP   = 0x03  /* CAN controller state SLEEP.   */

}Can_ControllerStateType;


typedef struct
{
     uint8_t StartIndex;
     uint8_t Size;
	  uint8_t RxTx_TableStartIndex;
}CanMailBoxTableDetailsTypeSt;

typedef struct
{
     uint8_t Network_Enable_Rx;
     uint8_t Network_Enable_Tx;
}Diag_NetworkControl_Type_St;


typedef enum
{
     ENABLE_RX_AND_ENABLE_TX,
     ENABLE_RX_AND_DISABLE_TX,
     DISABLE_RX_AND_ENABLE_TX,
     DISABLE_RX_AND_DISABLE_TX,
     MAX_NM_MODE
}Diag_NM_Enable_Mode_Type_En;

/* Types of communication and encoding was not handled */
typedef enum
{
     ISO_RESERVED = 0,
     Normal_Communication_Msg,
     Network_Management_Communication_Msg,
     Network_Management_And_NormalCommunication_Msg,
     Max_NM_Msg_types_List
}Diag_NM_COMM_Types_Type_En;

extern PduInfoType g_GetBuffer;

extern uint16_t Transmit_Vehicle_Error_Count_u16;

extern uint16_t Transmit_Diag_Error_Count_u16;

#define WAKEUP_E_OK        E_OK

#define CAN_GATEWAY_ENABLE            STD_ON

#define CAN_TP_ENABLE                 STD_OFF


uint8_t DiagGetRXCommControlSts(Diag_NM_COMM_Types_Type_En CommunicationType);
uint8_t DiagGetTXCommControlSts(Diag_NM_COMM_Types_Type_En CommunicationType);
void DiagSetCommControl(Diag_NM_Enable_Mode_Type_En DirectionControl, Diag_NM_COMM_Types_Type_En CommunicationType);

/**********************************************************************************************************************
                                                R E V I S I O N   H I S T O R Y                                        
***********************************************************************************************************************
**********************************************************************************************************************
     REVISION NUMBER      : V1.0.3                                                                                   
     REVISION DATE        : 16/11/2021
     CREATED / REVISED BY : Rajasekar T(rajasekar@niyatainfotech.com)
     DESCRIPTION          : Implementent Functional Safety Features
---------------------------------------------------------------------------------------------------------------------
**********************************************************************************************************************
     REVISION NUMBER      : V1.0.0                                                                                   
     REVISION DATE        : 28/07/2020
     CREATED / REVISED BY : Prabhu R (prabhu.r@niyatainfotech.com)
     DESCRIPTION          : Added the Multi-Channel Configuration
---------------------------------------------------------------------------------------------------------------------
*********************************************************************************************************************************************************************************************************************************************
     REVISION NUMBER      : V1.0.0
     REVISION DATE        : 05/03/2020
     CREATED / REVISED BY : Akshay Bavalatti (akshayb@niyatainfotech.com)
     DESCRIPTION          : Compiler Warning and MISRA fix
---------------------------------------------------------------------------------------------------------------------
**********************************************************************************************************************
     REVISION NUMBER      : V1.0.0                                                                                   
     REVISION DATE        : 13/01/2020                                                                               
     CREATED / REVISED BY : Akshay Bavalatti (akshayb@niyatainfotech.com)                                        
     DESCRIPTION          : Initial version                                                                          
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/

#endif


