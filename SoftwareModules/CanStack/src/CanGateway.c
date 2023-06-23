/* @file CAN_GATEWAY*/
#ifndef CANGATEWAY_C
#define CANGATEWAY_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Balaji Pandurangan (balaji.pandurangan@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : CanGateway.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : MCU Xpresso IDE
 *  Platforms supported             : XXXXX
 *  Description                     : This file consists of definitions of CanGateway
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "CanIF.h"
#include "CanMgr.h"
#include "CanTp.h"
#include "CanGateway.h"
#include "fsl_flexcan.h"
#include "CanMgr_cfg.h"
#include "MIMXRT1172.h"
#include "Cmp_Init.h"

/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                     
***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to vehicle and Diag Can of Tx frame
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: YES
 */
extern flexcan_frame_t Vehicle_Tx_frame, Diag_Tx_frame;


/*
 * @brief: This variable is used to data exchange between the Diag Can2 to Vehicle Can1
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 1 - 2
 * @Applicability: YES
 */
flexcan_mb_transfer_t TCh_dataExchange[CAN_TOTAL_NUMBER_OF_CHANNELS];

/*
 * @brief: This variable is used to handle the vehicle frame
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: YES
 */
extern flexcan_handle_t Vehicle_flexcanHandle;

/*
 * @brief: This variable is used to handle the Diag frame
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: YES
 */
extern flexcan_handle_t Diag_flexcanHandle;

CanMgr_TxDataBuffer_t l_TxGataWayBuffer[CANMGR_MAX_NO_OF_TX_MSGS];

extern CanMgr_TxDataBuffer_t l_TxDataBuffer[CANMGR_MAX_NO_OF_TX_MSGS];
/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    This function processes the Pre- condition check IGN condition and LVSD HVSD status
 * @param    void
 * @return   uint8_t fl_Precondition_Status - returns the status of pre-condition
 */
static uint8_t CanGateway_Pre_Condition(void);
/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/

/*
 * @brief           This function processes the cangateway initialization
 * @param           void
 * @return          void
 * @invocation      Cmp_init.c will call this function.
 */
void CanGateway_init(void)
{
    uint8_t fl_index_u8;

    for(fl_index_u8 = 0; fl_index_u8 < CAN_TOTAL_NUMBER_OF_CHANNELS; fl_index_u8++)
    {
        TCh_dataExchange[fl_index_u8].frame = 0;
        TCh_dataExchange[fl_index_u8].mbIdx = 0;
    }
    
}

/*
 * @brief           This function processes the de-init of cangateway
 * @param           void
 * @return          void
 * @invocation      
 */
void CanGateway_Deinit(void)
{

}


/*
 * @brief           This function shall be invoked for the CAN GateWAY periodic function
 * @param           void
 * @return          void
 * @invocation      
 */
void CanMgr_GateWayPeriodicTask(void)
{
    /* LOCAL VARIABLE */
    uint8_t fl_index_u8 = 0;
    const CanGateway_ReqRes_ID_st *CanGateway_ReqRes_ID = NULL;

    /* GET THE DIAG MAPPING TABLE */
    CanGateway_ReqRes_ID = g_CanGateway_Diag_Mapping_Table;

    /* TRAVERSE THROUGH LIST OF GATE WAY MESSAGES */
    for (fl_index_u8 = 0; fl_index_u8 < (uint16_t)RESPONSE_GATEWAY_TOTAL_MESSAGES; fl_index_u8++)
    {
        /* CHECK FOR THE POSTED REQUEST */
        if(l_TxGataWayBuffer[CanGateway_ReqRes_ID[fl_index_u8].GateWay_Output_ID_u16].Transmission_Requested == 1)
        {
            /* COPY DATA TO THE CAN TRANSMISSION BUFFER */
            memcpy(&l_TxDataBuffer[CanGateway_ReqRes_ID[fl_index_u8].GateWay_Output_ID_u16].data[0], &l_TxGataWayBuffer[CanGateway_ReqRes_ID[fl_index_u8].GateWay_Output_ID_u16].data[0], 8);

            /* POST CAN MESSAGE REQUEST */
            CanMgr_Send_Message(CanGateway_ReqRes_ID[fl_index_u8].GateWay_Output_ID_u16);

            /* CLEAR THE FLAG ONCE MESSAGE REQUEST POSTED */
            l_TxGataWayBuffer[CanGateway_ReqRes_ID[fl_index_u8].GateWay_Output_ID_u16].Transmission_Requested = 0;
        }
    }

    /* GET THE VEHICLE MAPPING TABLE */
    CanGateway_ReqRes_ID = g_CanGateway_Vehicle_Mapping_Table;

    /* TRAVERSE THROUGH LIST OF GATE WAY MESSAGES */
    for (fl_index_u8 = 0; fl_index_u8 < (uint16_t)RESPONSE_GATEWAY_TOTAL_MESSAGES; fl_index_u8++)
    {
        /* CHECK FOR THE POSTED REQUEST */
        if(l_TxGataWayBuffer[CanGateway_ReqRes_ID[fl_index_u8].GateWay_Output_ID_u16].Transmission_Requested == 1)
        {
            /* COPY DATA TO THE CAN TRANSMISSION BUFFER */
            memcpy(&l_TxDataBuffer[CanGateway_ReqRes_ID[fl_index_u8].GateWay_Output_ID_u16].data[0], &l_TxGataWayBuffer[CanGateway_ReqRes_ID[fl_index_u8].GateWay_Output_ID_u16].data[0], 8);

            /* POST CAN MESSAGE REQUEST */
            CanMgr_Send_Message(CanGateway_ReqRes_ID[fl_index_u8].GateWay_Output_ID_u16);

            /* CLEAR THE FLAG ONCE MESSAGE REQUEST POSTED */
            l_TxGataWayBuffer[CanGateway_ReqRes_ID[fl_index_u8].GateWay_Output_ID_u16].Transmission_Requested = 0;
        }
    }
}

/*
 * @brief           This function processes the can gateway request Rx
 * @param           RxPduId         Request Message ID. 
 * @param           PduInfoPtr      Data received from user.     
 * @return          void
 * @invocation      CanIF.c will call this function
 */
void Gateway_Request_Rx(PduIdType CanRxPduId, const uint8_t* CanSduPtr, Can_IdType CanId)
{
    /* LOCAL VARIABLES */
    bool fl_Pre_Condition_Check_State_bool = FALSE;
    uint8_t fl_CAN_Bus_State_u8 = 0;
    uint16_t fl_Get_CanBase_u16;
    uint8_t fl_index_u8 = 0;
    uint8_t fl_Diag_Network_Comm_TX_Enable_u8 = 0;
    const CanGateway_ReqRes_ID_st *CanGateway_ReqRes_ID = {0};

    /* Get pre condition status */
    fl_Pre_Condition_Check_State_bool = CanGateway_Pre_Condition();
    fl_Diag_Network_Comm_TX_Enable_u8 = DiagGetTXCommControlSts(Network_Management_Communication_Msg);

    if(fl_Pre_Condition_Check_State_bool == TRUE)
    {

        /* CHECK FOR MESSAGE INDEX */
        if(CanId == 0) /* IF VECHICLE CAN RESPONSE SEARCH IN VECHICLE CAN DATA */
        {
            /* ASSIGN IVN CHANNEL FOR THE SEARCH */
            CanGateway_ReqRes_ID = g_CanGateway_Vehicle_Mapping_Table;
        } 
        else
        {
            /* ASSIGN DIAG REQUEST CHANNEL FOR THE SEARCH */
            CanGateway_ReqRes_ID = g_CanGateway_Diag_Mapping_Table;
        }

        /* SEARCH FOR THE IDX */
        for(fl_index_u8 = 0; fl_index_u8 < RESPONSE_GATEWAY_TOTAL_MESSAGES; fl_index_u8++)
        {
            /* CHECK FOR THE IDX */
            if(CanGateway_ReqRes_ID[fl_index_u8].GateWay_Input_ID_u16 == CanRxPduId)
            {
                /* COPY DATA */
                memcpy(&l_TxGataWayBuffer[CanGateway_ReqRes_ID[fl_index_u8].GateWay_Output_ID_u16].data[0], &CanSduPtr[0], 8);

                /* CHECK FOR THE NETWORK TX IS ENABLED - THIS FLAG WILL INVOKE THE NETWORK TRANSMISSION IN CAN MGR */
                if(fl_Diag_Network_Comm_TX_Enable_u8 == 1)
                {
                    /* SET DATA FLAG */
                    l_TxGataWayBuffer[CanGateway_ReqRes_ID[fl_index_u8].GateWay_Output_ID_u16].Transmission_Requested = 1;
                }

                break;
            }
        }
    }
}

/*
 * @brief           This function processes the can gateway request Tx
 * @param           RxPduId         Request Message ID. 
 * @param           PduInfoPtr      Data received from user.       
 * @return          void
 * @invocation      CanGateway.c will call this function
 */
void Gateway_Request_Tx(PduIdType RxPduId)
{
    uint8_t fl_Vehicle_index_u8;

    uint16_t fl_RxPduId_u16 = RxPduId;

    if(fl_RxPduId_u16 == REQ_DIAG_ANS_IC_0X632)
    {
        fl_RxPduId_u16 = REQ_DIAG_ANSW_IC_0X632;
    }
    else
    {
        /* Do Nothing */
    }
#if 0
    /* Checking the mapping message ID with user ID */
    for(fl_Vehicle_index_u8 = 0; fl_Vehicle_index_u8 < REQUEST_GATEWAY_TOTAL_MESSAGES;fl_Vehicle_index_u8 ++)
    {
        if(g_CanGateway_Diag_Mapping_Table[fl_Vehicle_index_u8].Diag_Input_ID_u16 == fl_RxPduId_u16)
        {
            Diag_Tx_frame.id = FLEXCAN_ID_STD(g_CanGateway_Diag_Mapping_Table[fl_Vehicle_index_u8].Diag_Output_ID_u16);

            // TCh_dataExchange[1].frame = &Diag_Tx_frame;

            // (void)FLEXCAN_TransferSendNonBlocking(VECHILE_CAN, &Vehicle_flexcanHandle, &TCh_dataExchange[1]);

            break;
        }
        else
        {
            /*do nothing*/
        }
    }
#endif

}

/*
 * @brief           This function processes the can gateway response Rx
 * @param           RxPduId         Request Message ID. 
 * @param           PduInfoPtr      Data received from user.    
 * @return          void
 * @invocation      CanIF.c will call this function
 */
void Gateway_Response_Rx(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{

    bool fl_Pre_Condition_Check_State_bool = FALSE;

    uint8_t fl_CAN_Bus_State_u8 = 0;

    uint16_t fl_Get_CanBase_u16;

    uint16_t fl_PudID_u16 = RxPduId;
        /* Get pre condition status */
   fl_Pre_Condition_Check_State_bool = CanGateway_Pre_Condition();


    if(fl_Pre_Condition_Check_State_bool == TRUE)
    {
        /* Get CAN Bus current status */
       fl_CAN_Bus_State_u8 = GET_CAN_BUS_STATUS();

       if(fl_CAN_Bus_State_u8 == CANGATEWAY_CAN_BUS_OFF)
       {
            Vehicle_Tx_frame.length = PduInfoPtr->SduLength;

            Vehicle_Tx_frame.format = (uint8_t)kFLEXCAN_FrameFormatStandard;

            Vehicle_Tx_frame.type   = (uint8_t)kFLEXCAN_FrameTypeData;

            Vehicle_Tx_frame.dataByte0 = PduInfoPtr->SduDataPtr[0];
            Vehicle_Tx_frame.dataByte1 = PduInfoPtr->SduDataPtr[1];
            Vehicle_Tx_frame.dataByte2 = PduInfoPtr->SduDataPtr[2];
            Vehicle_Tx_frame.dataByte3 = PduInfoPtr->SduDataPtr[3];
            Vehicle_Tx_frame.dataByte4 = PduInfoPtr->SduDataPtr[4];
            Vehicle_Tx_frame.dataByte5 = PduInfoPtr->SduDataPtr[5];
            Vehicle_Tx_frame.dataByte6 = PduInfoPtr->SduDataPtr[6];
            Vehicle_Tx_frame.dataByte7 = PduInfoPtr->SduDataPtr[7];
            /* After Gateway Response Rx, send the gateway Response Tx to Tester */
            Gateway_Response_Tx(fl_PudID_u16);
       }
       else
       {
            /* Do Nothing */
       }
       
    }
    else
    {
        /* Do Nothing */
    }
}

/*
 * @brief           This function processes the can gateway response Tx.
 * @param           RxPduId         Request Message ID.    
 * @return          void
 * @invocation      CanGateway.c will call this function
 */
void Gateway_Response_Tx(PduIdType RxPduId)
{

    uint8_t fl_Diag_index_u8;

    uint16_t fl_Rx_ID_u16 = RxPduId;
#if 0
    for(fl_Diag_index_u8 = 0; fl_Diag_index_u8 < RESPONSE_GATEWAY_TOTAL_MESSAGES;fl_Diag_index_u8++)
    { 
        if(g_CanGateway_Vehicle_Mapping_Table[fl_Diag_index_u8].Vehicle_Input_ID_u16 == fl_Rx_ID_u16)
        {
            Vehicle_Tx_frame.id = FLEXCAN_ID_STD(g_CanGateway_Vehicle_Mapping_Table[fl_Diag_index_u8].Vehicle_Output_ID_u16);

            //TCh_dataExchange[2].frame = &Vehicle_Tx_frame;

           // (void)FLEXCAN_TransferSendNonBlocking(DIAG_CAN, &Diag_flexcanHandle, &TCh_dataExchange[2]);

            break;
        }
        else
        {
            /*do nothing*/
        }
    }
#endif
}

/*
 * @brief           This function processes the pre-condition for can gateway 
 * @param           void
 * @return          uint8_t fl_Precondition_Status - returns the status of pre-condition
 */
uint8_t CanGateway_Pre_Condition(void)
{
   bool fl_Precondition_Status = FALSE;
   
   uint8_t fl_CanGateway_HVSD_check_u8;

   uint8_t fl_CanGateway_Ign_Position_u8;

   uint8_t fl_CanGateway_LVSD_check_u8;

   uint8_t fl_CanGateway_Voltage_check_u8 = 0;
 
  fl_CanGateway_Ign_Position_u8 = Sys_Service_Get_Ignition_State();

  fl_CanGateway_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

  fl_CanGateway_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

  if( (fl_CanGateway_Ign_Position_u8   == IGN_OFF) || 
      (fl_CanGateway_LVSD_check_u8 == SYSTEM_SERVICE_SET) || 
      (fl_CanGateway_HVSD_check_u8 == SYSTEM_SERVICE_SET) )
  {
     fl_Precondition_Status = FALSE;
  }
  else
  {
      fl_Precondition_Status = TRUE;
  }

  return fl_Precondition_Status;
}

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                          
    REVISION DATE        : 07/24/2022        
    CREATED / REVISED BY : Balaji Pandurangan (balaji.pandurangan@niyatainfotech.com)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! CANGATEWAY_C */
