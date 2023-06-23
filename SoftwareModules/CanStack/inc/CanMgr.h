
#ifndef CANMGR_H_
#define CANMGR_H_
/**********************************************************************************************************************
 *   DISCLAIMER                                                                                                       
 *   Copyright (C) 2011, 2016 Niyata Infotech Ptv. Ltd. All rights reserved.                                             
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * @author              Author : Mahendran L (mahendranl@niyatainfotech.com)                                                                      
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *                                               F I L E  D E S C R I P T I O N                                      
 *--------------------------------------------------------------------------------------------------------------------
 *  @brief                                                                                                            
 *                                                                                                                    
 *  File name                       : CanMgr.h
 *  Version                         : V1.6.0
 *  Micros supported                : Micro Agnostic (Independent)
 *  Compilers supported             : XXXXX
 *  Platforms supported             : XXXXX
 *  Description                     : This file contains functions declarations of CanMgr
 *                                                                                                                    
 *                                                                                                                    
 *  @bug                                                                                                              
 *--------------------------------------------------------------------------------------------------------------------*/
/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *                                          I N C L U D E   F I L E S                                    
 ***********************************************************************************************************************/
#include "CanMgr_cfg.h"
#include "string.h"
#include "CanIF_Types.h"
//#include "CAN_Driver_cfg.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S                                          
 ***********************************************************************************************************************/
/*
* @brief: This Macro is used to indicate that CAN MGR is 
  @brief: in no communication    
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define CANMGR_NO_COMM                          0x00u

/*
* @brief: This Macro is used to indicate that CAN MGR is 
  @brief: in full communication    
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define CANMGR_FULL_COMM                        0x01u
/*
* @brief: This Macro is used to put that CAN MGR in
  @brief: in silent communication    
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
#define CANMGR_SILENT_COMM                      0x05u  

#define VEHICLE_BUS_OFF_DETECTED                 1U

#define DIAG_BUS_OFF_DETECTED                    2U

#define BUSOFF_NOT_DETECTED                      0U
/*
* @brief: This Enum represents the states in CAN Manager
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
/* Maximum count of timer based on Timer task*/
#define MAX_MGR_CALL                    1u
#define MAX_DRV_CALL                    1u
#define MAX_IF_CALL                     1u
#define MAX_TP_CALL                     2u
#define CAN_MGR_ALIVE_COUNTER()               CAN_MGR_INFORM_ALIVE_STATUS()
#endif
typedef enum
{
 CANMGR_NO_COMMUNICATION_REQUESTED     = CANMGR_NO_COMM,
 CANMGR_NO_COMMUNICATION               = 0x02u,
 CANMGR_NO_COMMUNICATION_PREPARE       = 0x03u,
 CANMGR_FULL_COMMUNICATION             = CANMGR_FULL_COMM,
 CANMGR_FULL_COMMUNICATION_REQUESTED   = 0x04u,
 CANMGR_SILENT_COMMUNICATION           = CANMGR_SILENT_COMM,
 CANMGR_SILENT_COMM_REQUESTED          = 0x06u, 
 CANMGR_IDLE                           = 0x0Au                                  
}CanMgr_ModeType;

/*
* @brief: This Enum represents the transmission status of
          a message
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
typedef enum
{
    CANMGR_TX_STATUS_IDLE,
    CANMGR_TX_STATUS_REQUESTED,
    CANMGR_TX_STATUS_IN_MAILBOX,
    CANMGR_TX_STATUS_SUCCESSFUL,
    CANMGR_TX_STATUS_FAILED
}CanMgr_TransmissionStatusType;
/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON

typedef enum
{
    CAN_CONTROL_FLOW_SUCCESS,
    CAN_CONTROL_FLOW_FAILURE
}CanMgr_ControlflowStatusType;
#endif


/*Global variable Declaration*/
/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON 
static uint8_t g_Drv_counter_u8 = 0;
static uint8_t g_If_counter_u8 =  0;
static uint8_t g_Mgr_counter_u8 = 0;
static uint8_t g_Tp_counter_u8 = 0;
#endif
/**
 * @brief    This structure is used to store the data to be transmitted and holds transmission status 
 * @param    data                   - Data to be transmitted
 * @param    transmission_status    - Transmission status of the message
 * @param    Alive_Counter          - Alive counter value to be Txed
 **/

typedef struct
{   
     uint8_t data[8];
     uint8_t Transmission_Requested;
     uint8_t RepetitionCounter;
     uint8_t NoOfSignals;
     #if(ALIVE_COUNTER_FEATURE_GLOBAL == STD_ON)
     uint8_t Alive_Counter;
     #endif
     uint16_t SignalStartIndex;
     uint16_t counter;
     CanMgr_TransmissionStatusType transmission_status;
} CanMgr_TxDataBuffer_t;


/**
 * @brief    This structure is used to store the received data and corressponding message attributes 
 * @param    data                                 - Received data
 * @param    data_change                          - holds infomation about data change (TRUE/FALSE)
 * @param    reception_status                     - holds the reception status
 * @param    Reception_TimeoutCbk_required        - holds info about timeout callback triggred status
 * @param    CRC_Error_debounce_Counter           - holds the checksum error debounce counter value of the corresponding Msg Id
 * @param    CRC_Error_Recovery_Debounce_Counter  - holds the checksum error recovery debounce counter value of the corresponding Msg Id
 * @param    Alive_Cntr_Value                     - Previously received alive counter value of the corresponding Msg Id
 * @param    Alive_Cntr_Error_Debounce_Counter    - holds the alive counter's error debounce counter value of the corresponding Msg Id
 * @param    Alive_Cntr_Error_Recovery_Debounce_Counter - holds the alive counter's error recovery debounce counter value of the corresponding Msg Id
 **/
typedef struct
{
    uint8_t data[8];
    uint8_t data_change;
    uint8_t reception_status;
    uint8_t Reception_TimeoutCbk_required;
    #if(CHECKSUM_FEATURE_GLOBAL == STD_ON)
    uint8_t CRC_Error_debounce_Counter;
    uint8_t CRC_Error_Recovery_Debounce_Counter;
    #endif
    #if(ALIVE_COUNTER_FEATURE_GLOBAL == STD_ON)
    uint8_t Alive_Cntr_Value;
    uint8_t Alive_Cntr_Error_Debounce_Counter;
    uint8_t Alive_Cntr_Error_Recovery_Debounce_Counter;
    #endif
} CanMgr_RxDataBuffer_t;

/*********************************************************************************************************************** 
 *                                          T Y P E   D E F I N I T I O N S                                            *
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                             
 ***********************************************************************************************************************/

/*
 * @breif : This function intializes CanMgr
 * @param : None
 * @return: None
 */
void CanMgr_Init(void);

/*
 * @breif : This function Deintializes CanMgr
 * @param : None
 * @return: None
 */
void CanMgr_DeInit(void);

/*
 * @breif : This function Deinitializes CanMgr Channel specific
 * @param : p_Channel_u8 - CHANNEL INDEX SHALL BE PASSED HERE
 * @return: None
 */
uint8_t CanMgr_Channel_DeInit(uint8_t p_Channel_u8);

/*
 * @breif : This function returns CanMgr status [Initialized or Deinitialized]
 * @param : channel - CAN channel number
 * @return: CanMgr Status
 */
CanMgr_StatusType CanMgr_GetStatus(uint8_t channel);

/*
 * @breif : This function is a period task and process the signals
 * @param : None
 * @return: None
 */
void CanMgr_Mainfunction(void);

/*
 * @breif : The service CanMgr_SendSignal updates the signal object identified by SignalId with
 *          the signal referenced by the SignalDataPtr parameter.
 * @param : SignalId : Id of signal to be sent
 *          SignalDataPtr : Reference to the signal data to be transmitted.
 * @return: E_OK: service has been accepted
 *          E_NOT_OK: Invalid SignalId
 */
uint8_t CanMgr_SendSignal(uint8_t SignalId, const uint8_t *SignalDataPtr);

/*
 * @breif : The service CanMgr_SendSignal updates the signal object identified by SignalId with
 *          the signal referenced by the SignalDataPtr parameter.
 * @param : SignalId : Id of signal to be sent
 *          SignalDataPtr : Reference to the location where the received signal data shall be stored.
 * @return: E_OK: service has been accepted
 *          E_NOT_OK: Invalid SignalId
 */
uint8_t CanMgr_ReceiveSignal(uint8_t SignalId, uint8_t* SignalDataPtr);

/*
 * @breif : The lower layer communication interface module confirms the transmission of a PDU,
 *          or the failure to transmit a PDU..
 * @param : TxPduId : Id of the signal that has been transmitted
 *          result  : E_OK: The PDU was transmitted.
 *                    E_NOT_OK: Transmission of the PDU failed.
 * @return: None
 */
void CanMgr_TxConfirmation( PduIdType TxPduId, Std_ReturnType result);

/*
 * @breif : The lower layer communication interface module confirms the transmission of a PDU,
 *          or the failure to transmit a PDU..
 * @param : RxPduId : ID of the received PDU
 *          PduInfoPtr : Contains the length (SduLength) of the received PDU, a pointer to a
 *           buffer (SduDataPtr) containing the PDU, and the MetaData related to this PDU
 * @return: None
 */
void CanMgr_RxIndication( uint8_t RxPduId, const PduInfoType* PduInfoPtr);

#if(CANMGR_ON_CHANGE_RECEPTION_CALLBACK == STD_ON)
/*
 * @breif : This function is a Round Robin and process the received data and gives a callback when there is a change in
 *          received data
 * @param : None
 * @return: None
 */
void CanMgr_RxSignalDispatcher(void);
#endif

/*
 * @breif : This service is used to get transmission status.
 * @param : SignalId PDU Id of the transmitted signal
 * @return: Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED )
 */
uint8_t CanMgr_GetTransmissionStatus(uint8_t  SignalId );

/*
 * @breif : This function is used to put the CAN into sleep/Normal
 * @param	channel - CAN channel number
 * @param : State (CANMGR_FULL_COMM / CANMGR_NO_COMM)
 *          CANMGR_NO_COMM - Puts CAN into sleep    
 * @return: E_OK / E_NOT_OK
 */

Std_ReturnType CanMgr_SetNetworkMode(uint8_t channel,CanMgr_ModeType NetworkMode);

/*
 * @breif : This function returns the state of CAN 
 * @param : channel - CAN channel number
 * @return: State -(CANMGR_FULL_COMM / CANMGR_NO_COMM)
 */

CanMgr_ModeType CanMgr_GetNetWorkMode(uint8_t channel);

/*
 * @breif : Callback function will be invoked by IF layer.
 * @param	channel - CAN channel number
 * @param : Result - contains the Network request result.
 * @return: None
 */

void CanMgr_NetworkRequestConfirmation(uint8_t channel ,const uint8_t* Result);

#if(CANMGR_WAKEUP_INDICATION == STD_ON)
/*
 * @breif : Callback function will be invoked by IF layer when wakeup happens 
 * @param	channel - CAN channel number
 * @return: NONE
 */

void CanMgr_WakeUpIndication(uint8_t channel);
#endif

/*
 * @breif : Callback function will be invoked by IF layer when busoff happens 
 * @param	channel - CAN channel number
 * @return: NONE
 */
 void CanMgr_BusoffIndication(uint8_t channel);
 /*
 * @breif : Callback function will be invoked by IF layer when busoff happens 
 * @param	channel - CAN channel number
 *          Error_Value- Error register value
 * @return: NONE
 */
void CanMgr_Error_State_Indication(uint32_t Channel,uint32_t Error_Value);
/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
/**
     * @brief    This function is used to get the Driver Watch dog Alive counter.
     * @param   counter- get driver counter value
     * @return   None
     * @note This function is called in Watch dog alive counter
     */

void CAN_DRV_INFORM_ALIVE_STATUS(void);
#endif
/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
/**
     * @brief    This function is used to get the IF Watch dog Alive counter.
     * @param   counter- get driver counter value
     * @return   None
     * @note This function is called in Watch dog alive counter
     */

void CAN_IF_INFORM_ALIVE_STATUS(void);
#endif
/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
/**
     * @brief    This function is used to get the Manager Watch dog Alive counter.
     * @param   counter- get driver counter value
     * @return   None
     * @note This function is called in Watch dog alive counter
     */
void CAN_MGR_INFORM_ALIVE_STATUS(void);
#endif
/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
/**
     * @brief    This function is used to get the TP Watch dog Alive counter.
     * @param   counter- get driver counter value
     * @return   None
     * @note This function is called in Watch dog alive counter
     */
void CAN_TP_INFORM_ALIVE_STATUS(void);
#endif
/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
/**
     * @brief    This function is used to get the status Watch dog Alive counter.
     * @param    None
     * @return   None
     * @note This function is called in Watch dog alive counter
     */

void CANMGR_Alive_Counter_Mainfunction(void);
#endif
#if(CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : This function shall be used to transmit TP messages.
 * @channel: channel - CAN channel number
 * @param : MsgPtr - Reference to the signal data to be transmitted.
 *          Lenght - Lenght of the message to be transmitted.    
 * @return: E_OK / E_NOT_OK
 */
Std_ReturnType CanMgr_CanTp_Transmit(Tx_Msg_Id SignalId, uint8_t * fl_Msgptr, uint16_t length);
#endif

#if(CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : The lower layer communication interface module confirms the transmission of a message,
 *          or the failure to transmit a message..
 * @param : result  : E_OK: The message was transmitted.
 *                    E_NOT_OK: Transmission of the message failed.
 * @return: None
 */
void CanMgr_CanTp_Tx_Confirmation(Std_ReturnType TransmissionResult);
#endif

#if(CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : The lower layer communication interface module indicates the upper layer on
 *          message reception
 * @param : result  : E_OK: The message was transmitted.
 *                    E_NOT_OK: Transmission of the message failed.
 * @return: None
 */
void CanMgr_CanTp_RxIndication(Std_ReturnType Result);
#endif

#if(CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : This service shall be used by TP layer to get the reference of application data buffer
 *          to store the data on message reception.
 * @param : PduId: SiganlID
 *          PduIdLength : Total lenght of the message
 * @return: E_OK : Service accepted
 *          E_NOT_OK : Conditions not met.    
 */
Std_ReturnType CanMgr_CanTpStartOfReception(PduIdType PduId, uint16_t PduIdLength);
#endif

#if(CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : This service shall be used by TP layer to update the received 
 *          data.
 * @param : MsgPtr: refernce to the received data
 *          size_u8 : Size of received data
 * @return: None
 *           
 */
void CanMgr_CanTpRxInProgress(const uint8_t * MsgPtr, uint8_t size_u8);
#endif

#if(CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : This function shall be used to cancel the ongoing TP transmission.
 * @param : NONE
 * @return: E_OK : Service is accepted
 *          E_NOT_OK Service is not accepted
 */
Std_ReturnType CanMgr_CanTp_CancelTransmit(void);
#endif

#if(CANMGR_CANTP_FUNCTIONS == STD_ON)
/*
 * @breif : This function shall be used to cancel the ongoing TP reception.
 * @param : NONE
 * @return: E_OK : Service is accepted
 *          E_NOT_OK Service is not accepted
 */
Std_ReturnType CanMgr_CanTp_CancelReception(void);
#endif

#if (CANMGR_CANTP_FUNCTIONS == STD_ON)
     /*
 * @breif : This function is used to get the CANTP transmit status.
 * @param : NONE
 * @return: Transmission in progress or completed
 */
uint8_t CanMgr_CanTp_Get_Transmit_Status(void);
#endif

// /*
//  * @breif : This function is used for can bus off indication
//  * @param	channel - CAN channel number
//  * @return: None
//  */
 void App_Can_bus_off_indication(uint8_t BusOff);

/*
 * @breif : This function is used for bus off indication
 * @param	void
 * @return: g_Bus_off_detected
 */
uint8_t App_Can_bus_off_Get_indication(void);

void Can_Bus_WakeUp_Notification(uint8_t channel);

/*
 * @breif : This function shall be used to pre-job before send.
 * @param	p_Message_Index_u16 - Message list enumuration index shall be given as parameter.
 * @return: None
 */
void CanMgr_Send_Message(uint16_t p_Message_Index_u16);

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                          
***********************************************************************************************************************/
#ifdef __cplusplus
}
#endif
/**********************************************************************************************************************
 *                                                R E V I S I O N   H I S T O R Y             
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.0.5
     REVISION DATE        : 15/11/2021
     CREATED / REVISED BY : Rajasekar T(rajasekar@niyatainfotech.com)
     DESCRIPTION          : Implementent Functional Safety Features
-------------------------------------------------------------------------------------
      REVISION NUMBER      : V1.0.4
     REVISION DATE        : 28/08/2021
     CREATED / REVISED BY : Rajasekar T(rajasekar@niyatainfotech.com)
     DESCRIPTION          : Silent Mode (Listen only mode) Feature code is integrated(Taken from SPT Branch).
-------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.0.3
     REVISION DATE        : 28/09/2020
     CREATED / REVISED BY : prabhu R(prabhu.r@niyatainfotech.com)
     DESCRIPTION          : Updated the TX status for can timing issue Defect fix in Multi-Channel can stack
-------------------------------------------------------------------------------------
**********************************************************************************************************************
     REVISION NUMBER      : V1.7.0                                                                                   
     REVISION DATE        : 28/07/2020                                                                               
     CREATED / REVISED BY : Bakyaraj (bakyaraj@niyatainfotech.com)                                        
     DESCRIPTION          : Multi - Channel support implemented.                                                                            
---------------------------------------------------------------------------------------------------------------------
     REVISION NUMBER      : V1.6.0                                                                                   
     REVISION DATE        : 30/05/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : MISRA fix                                                                             
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.4.0                                                                                   
     REVISION DATE        : 06/04/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : CAN TP functions MISRA FIX                                                                          
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.3.0                                                                                   
     REVISION DATE        : 01/04/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : CAN TP functions implemented                                                                           
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.2.0                                                                                   
     REVISION DATE        : 14/03/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : MISRA fix                                                                             
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.1.0                                                                                   
     REVISION DATE        : 20/02/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : Added Rx signal dispatcher function                                                                           
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.0.1                                                                                   
     REVISION DATE        : 13/02/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : Added set/ get network mode and network request confirmation functions                                                                         
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
/**********************************************************************************************************************
     REVISION NUMBER      : V1.0.0                                                                                   
     REVISION DATE        : 30/01/2020                                                                               
     CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
     DESCRIPTION          : Initial version                                                                          
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
#endif /* CANMGR_H_ */
