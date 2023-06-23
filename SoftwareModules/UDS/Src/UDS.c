/* @file UDS_C */
#ifndef UDS_C
#define UDS_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Ptv. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Sharmili N (sharmili@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : UDS.c
 *  Version                         : V2.0.0
 *  Micros supported                : Micro Agnostic (Independent)
 *  Compilers supported             : XXXXX
 *  Platforms supported             : XXXXX
 *  Description                     : This file consists of function definitions of UDS Core Layer


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
#include "UDS_Cfg.h"
#include"UDS.h"
#include <stdio.h>
#include "UdsApp.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*  
 * @brief: This macro is used to execute the Post handler function of each service after main handler is executed
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
 */
#define POSTHANDLER   (g_UDS_ServiceInfoTable_st[l_UDS_Service_Index_u8].FuncHandler.PostFuncHandler)

/*  
 * @brief: This macro is used to decrement P2 timer value
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
 */
#define UDS_DECREMENT_P2_TIMER()    l_UDS_P2_TimerCount_u32--

/*  
 * @brief: This macro is used to decrement S3 timer value
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
 */
#define UDS_DECREMENT_S3_TIMER()          l_UDS_S3_TimerCount_u32--

/*  
 * @brief: This macro is used to decrement P4 timer value
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
 */
#define UDS_DECREMENT_P4_TIMER()          l_UDS_P4_TimerCount_u32--

/*  
 * @brief: This macro is used to decrement P2 * timer value
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
 */
#define UDS_DECREMENT_P2STAR_TIMER()       l_UDS_P2STAR_TimerCount_u32--

/*  
 * @brief: This macro is used to define the negative response length
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
 */
#define UDS_NEGRESP_LENGTH                0x03u

/*  
 * @brief: This macro is used to define the invalid service request
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: 
 */
#define UDS_INVALID_SERVICE               0xFFu

/*  
 * @brief: This macro is used to run the Delay Timer by decrementing it
  @Unit:  milliseconds
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES 
  @Note:  Do not modify this macro value or name
 */
#define UDS_DECREMENT_DELAY_TIMER()                 (l_DelayTimer_Count_u32--)

/*  
 * @brief: This macro is used to calculate the RCRRP NRC's enhanced response timing
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES 
  @Note:  Do not modify this macro value or name
          During the enhanced response timing, the minimum time between the transmission of 
          consecutive negative messages (each with negative response code 0x78) shall be 0.3 * P2*Server_max
 */
#define UDS_RCRRP_ENHANCEMENT_FORMULA                ((0.3f) * UDS_P2STAR_TIMER_MAXCNT)

/*
 * @brief: This macro is used to define the max value of FRC for RCRRP
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability:
 */
#define UDS_RCRRP_FRC_MAX_VAL           (uint32_t)0xFFFFFFFFu

/*
 * @brief: This macro is used to run the RCRRP FRC by decrementing it
  @Unit:  milliseconds
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
  @Note:  Do not modify this macro value or name
 */
#define UDS_DECREMENT_RCRRP_FRC()                 (l_RCRRP_FRC_u32--)

// bool g_UDS_pre_condition_Status;

// UDS_UINT8 g_UDS_Ign_Position_u8;
// UDS_UINT8 g_UDS_LVSD_check_u8;
// UDS_UINT8 g_UDS_HVSD_check_u8;


/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************//*
 * @brief: This variable is used to maintain the Buffer controlling each service behaviour
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
 */
static UDS_BufferCtrl_st l_BufferCtrl_st[UDS_NUMREQ];

/*
 * @brief: This variable is used to hold the P2 timer counter values
  @Unit:  milliseconds
  @Resolution: N/A
  @Range: 0 to 65535
  @Applicability: YES
 */
static UDS_UINT32 l_UDS_P2_TimerCount_u32;

/*
 * @brief: This variable is used to hold the P4 timer counter values
  @Unit:  milliseconds
  @Resolution: N/A
  @Range: 0 to 65535
  @Applicability: YES
 */
static UDS_UINT32 l_UDS_P4_TimerCount_u32;

/*
 * @brief: This variable is used to hold the S3 timer counter values
  @Unit:  milliseconds
  @Resolution: N/A
  @Range: 0 to 65535
  @Applicability: YES
 */
static UDS_UINT32 l_UDS_S3_TimerCount_u32;

/*
 * @brief: This variable is used to hold the P2 * timer counter values
  @Unit:  milliseconds
  @Resolution: N/A
  @Range: 0 to 65535
  @Applicability: YES
 */
static UDS_UINT32 l_UDS_P2STAR_TimerCount_u32;

/*
 * @brief: This variable is used to hold the Delay timer counter values
  @Unit:  milliseconds
  @Resolution: N/A
  @Range: 0 to 65535
  @Applicability: YES
 */
static UDS_UINT32 l_DelayTimer_Count_u32;

/*
 * @brief: This variable is used to store the Current session of the UDS layer
  @Unit:  N/A
  @Resolution: N/A
  @Range: 0 to 255
  @Applicability: YES
 */
static UDS_UINT8 l_UDS_Current_Session_u8;

/*
 * @brief: This variable is used to store the Current Service Request Type of the UDS layer
  @Unit:  N/A
  @Resolution: N/A
  @Range: 0 to 255
  @Applicability: YES
 */
static UDS_UINT8 l_UDS_Current_RequestType_u8;

/*
 * @brief: This variable is used to maintain the Buffer Error status for each service behaviour
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
 */
static UDS_UINT8 l_BufferError_u8[UDS_NUMREQ];

/*
 * @brief: This variable is used to maintain the Buffer length from TP
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
 */
static UDS_UINT16 l_BufferLen_u16[UDS_NUMREQ];

/*
 * @brief: This variable is used to maintain the service index based on the number of services supported
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
 */
static UDS_UINT8 l_UDS_Service_Index_u8;

/*
 * @brief: This variable is used to maintain the Physical request message buffer
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
 */
static UDS_UINT8 l_UDS_PrimaryBuff_u8[UDS_PRIMARYBUFF_LENGTHMAX];

/*
 * @brief: This variable is used to maintain the functional request message buffer
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
 */
static UDS_UINT8 l_UDS_SecondaryBuff_u8[UDS_SECONDARYBUFF_LENGTHMAX];

/*
 * @brief: This variable is used to maintain the UDS request message received through CAN
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
 */
static UDS_UINT8 * l_UDSDiag_Buffer_u8[UDS_NUMREQ] =
{
 &l_UDS_PrimaryBuff_u8[BUFF_INDEX_ZERO],
 &l_UDS_SecondaryBuff_u8[BUFF_INDEX_ZERO]
};

/*
 * @brief: This variable is used to maintain the RCRRP coounnter value
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
 */
static UDS_UINT8 l_RCRRP_Counter_u8;

/*
 * @brief: This variable is used to maintain Free running Counter for RCRRP
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
 */
static UDS_UINT32 l_RCRRP_FRC_u32;

/*
 * @brief: This variable is used to maintain previous Time stamp for RCRRP
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
 */
static UDS_UINT32 l_RCRRRP_PreviousTimeStamp_u32;

/*
 * @brief: This variable is used to maintain current Time stamp for RCRRP
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
 */
static UDS_UINT32 l_RCRRRP_CurrentTimeStamp_u32;
/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    This function processes the diagnostic request messages & their responses
 * @param    BufferIndex - Message buffer index (0 to 255)
 * @return   None
 */
static void UDS_Dispatcher(UDS_UINT8 BufferIndex);

/*
 * @brief    This function indicates the core layer to start the P2 timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_StartP2Timer(void);

/*
 * @brief    This function indicates the core layer to stop P2 timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_StopP2Timer(void);

/*
 * @brief    This function is used to get the P2 timer current value
 * @param    NULL
 * @return   uint8_t - CurrentTimerValue
 */
static UDS_UINT32 UDS_GetP2_TimerValue(void);

/*
 * @brief    This function is used to convey the core layer for P2 time out
 * @param    NULL
 * @return   NULL
 */
static void UDS_P2TimeOut(void);

/*
 * @brief    This function is used to Start the P2 * Timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_Start_P2Star_Timer(void);

/*
 * @brief    This function is used to Stop the P2 * Timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_Stop_P2Star_Timer(void);

/*
 * @brief    This function is used to Get the P2 * timer value
 * @param    NULL
 * @return   NULL
 */
static UDS_UINT32 UDS_Get_P2Star_TimerValue(void);

/*
 * @brief    This function is used to convey the core layer for P2* (Response Pending) time out
 * @param    NULL
 * @return   NULL
 */
static void UDS_P2Star_TimeOut(void);

/*
 * @brief    This function indicates the core layer to start P4 timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_StartP4Timer(void);

/*
 * @brief    This function indicates the core layer to stop P4 timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_StopP4Timer(void);

/*
 * @brief    This function is used to get the P4 timer current value
 * @param    NULL
 * @return   uint8_t - CurrentTimerValue
 */
static UDS_UINT32 UDS_GetP4_TimerValue(void);

/*
 * @brief    This function is used to convey the core layer for P4 time out
 * @param    NULL
 * @return   NULL
 */
static void UDS_P4TimeOut(void);

/*
 * @brief    This function indicates the core layer to stop S3 timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_StopS3Timer(void);

/*
 * @brief    This function is used to get the S3 timer current value
 * @param    NULL
 * @return   uint32_t - CurrentTimerValue
 */
static UDS_UINT32 UDS_GetS3_TimerValue(void);

/*
 * @brief    This function is used to convey the core layer for S3 time out
 * @param    NULL
 * @return   NULL
 */
static void UDS_S3TimeOut(void);

/*
 * @brief    This function is used to stop the delay timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_Stop_DelayTimer(void);

/*
 * @brief    This function is used to get the RCRRP FRC current value
 * @param    NULL
 * @return   uint32_t - Current Counter Value
 */
static UDS_UINT32 UDS_Get_RCCRRP_FRC_Value(void);

/*
 * @brief    This function is used to reset the RCRRP FRC current value
 * @param    NULL
 * @return   NULL
 */
static void UDS_Reset_RCCRRP_FRC_Value(void);
/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief    This API will initialiaze all the UDS Layer variables & session status
 * @param    None
 * @return   None
 */


void UDS_Init(void)
{
    UDS_UINT8 fl_index_u8;
    UDS_StopP2Timer();
    UDS_StopS3Timer();

    /*Initialize the buffer control elements for all types of message*/
    for(fl_index_u8 = UDS_COUNTER_ZERO; fl_index_u8 < UDS_NUMREQ; fl_index_u8++)
    {
        /*Initialize the Service index element for new iteration*/
        l_BufferCtrl_st[fl_index_u8].CurrentSrvIdx = UDS_INIT;
        /*Initialize the flag to make response for new Iteration*/
        l_BufferCtrl_st[fl_index_u8].MakeResponse = UDS_INIT;
        /*Initialize the flag for transmission confirmation done new iteration*/
        l_BufferCtrl_st[fl_index_u8].Confirmation_Txed = UDS_INIT;
        /*Initialize the Tx ready flag*/
        l_BufferCtrl_st[fl_index_u8].Tx_Ready = UDS_INIT;
        /*Initialize the indication flag for new iteration*/
        l_BufferCtrl_st[fl_index_u8].Ind_Flag = UDS_INIT;
    }
    /*Initializing with Default Session*/
    l_UDS_Current_Session_u8 = UDS_DEFAULT_SESS;
    /*Initializing as no service request currently*/
    l_UDS_Current_RequestType_u8 = UDS_NO_SERVICE_REQ;
    /*Start Delay timer on PowerUp/ Reset*/
    UDS_Start_DelayTimer();
    /*Load the FRC for RCRRP sending operation*/
    l_RCRRP_FRC_u32 = UDS_RCRRP_FRC_MAX_VAL;
}

/*
 * @brief    This API is used to handle the incoming Diagnostic requests with
            Timing Parameters monitored internally
 * @param    None
 * @return   None
 * @Note     This API should be executed periodically as a Time Task to check for the incoming
            service requests
 */
void UDS_Main(void)
{   
    UDS_UINT8 fl_index_u8 = UDS_INIT;



    for(fl_index_u8 = UDS_COUNTER_ZERO; fl_index_u8 < UDS_NUMREQ; fl_index_u8++)
    {
        /*Check whether the Confirmation of transmission flag is set for current iteration*/
        if(l_BufferCtrl_st[fl_index_u8].Confirmation_Txed == UDS_TRUE)
        {
            /*Reset the Confirmation of transmission flag to handle the post handler for next iteration*/
            l_BufferCtrl_st[fl_index_u8].Confirmation_Txed = UDS_FALSE;
            /*Check for Post Handling function configuration in Service Information list*/
            if((POSTHANDLER != ((void *) 0U) )&&(l_UDS_Service_Index_u8 < MAX_NO_OF_SRV))
            {
                /*Execute the Post Handling Function as per Service information List*/
                g_UDS_ServiceInfoTable_st[l_UDS_Service_Index_u8].FuncHandler.PostFuncHandler();
            }
            else
            {
                /*Do nothing*/
            }
        }
    }
    /*Check for Session Timer S3 elapse*/
    if(UDS_GetS3_TimerValue() != UDS_COUNTER_ZERO)
    {
        /*Decrement  until the counter is elapsed*/
        UDS_DECREMENT_S3_TIMER();
        if(UDS_GetS3_TimerValue() == UDS_COUNTER_ZERO)
        {
            /*Return to DEFAULT session due to S3 timeout*/
            //UDS_S3TimeOut();
        }
    }

    /*Check for Performance timer P4 elapse*/
    if(UDS_GetP4_TimerValue() != UDS_COUNTER_ZERO)
    {
        /*Decrement until the counter is elapsed*/
        UDS_DECREMENT_P4_TIMER();
        if(UDS_GetP4_TimerValue() == UDS_COUNTER_ZERO)
        {
            UDS_P4TimeOut();
        }
    }

    /*Check whether P2 timer has elapsed*/
    if(UDS_GetP2_TimerValue() > UDS_COUNTER_ZERO)
    {
        UDS_DECREMENT_P2_TIMER();
        if(UDS_GetP2_TimerValue() == UDS_COUNTER_ZERO)
        {
            /* Respond with busy/repeat request NRC */
            UDS_P2TimeOut();
        }
    }

    /*Check whether P2* timer has elapsed*/
    if(UDS_Get_P2Star_TimerValue() > UDS_COUNTER_ZERO)
    {
        UDS_DECREMENT_P2STAR_TIMER();
        if(UDS_Get_P2Star_TimerValue() == UDS_COUNTER_ZERO)
        {
            /* Respond with busy/repeat request NRC */
            UDS_P2Star_TimeOut();
        }
    }

    /*Check whether Delay Timer has elapsed*/
    if(UDS_GET_DELAYTIMER_CNT() > UDS_COUNTER_ZERO)
    {
        UDS_DECREMENT_DELAY_TIMER();
        if(UDS_Get_DelayTimer_Value() == UDS_COUNTER_ZERO)
        {
            /*Stop Delay Timer*/
            UDS_Stop_DelayTimer();
        }
    }

    /*RCRRP Free Running Counter*/
    if(UDS_Get_RCCRRP_FRC_Value() != UDS_COUNTER_ZERO)
    {
        UDS_DECREMENT_RCRRP_FRC();
        if(UDS_Get_RCCRRP_FRC_Value() == UDS_COUNTER_ZERO)
        {
            UDS_Reset_RCCRRP_FRC_Value();
        }
    }

    for(fl_index_u8 = UDS_COUNTER_ZERO; fl_index_u8 < UDS_NUMREQ; fl_index_u8++)
    {
        /*Check whether the data request received indication flag is set */
        if(l_BufferCtrl_st[fl_index_u8].Ind_Flag == UDS_TRUE)
        {
            /*Stop S3 timer*/
            UDS_StopS3Timer();
            /*Reset the indication flag fro next iteration*/
            l_BufferCtrl_st[fl_index_u8].Ind_Flag = UDS_FALSE;
            /*All checks passed, start processing the received request*/
            UDS_Dispatcher(fl_index_u8);
        }
    }

	UDS_ROUTINE_HANDLER();
}

void UDS_ROUTINE_HANDLER (void)
{
	uint8_t return_status = 0;

	/* TRAVERSE ALL THE ROUINES CONTROL ID */
	for(uint8_t index =0; index<MAX_NO_OF_ROUTINE; index++)
	{
		if(g_Routine_List_st[index].RoutineState == UDS_ROUTINE_STARTED)
		{
			/* CHECK FOR THE VALID FUNCTION PTR */
			if(g_Routine_List_st[index].start_fnptr != NULL)
			{
				/* EXECUTE THE FUNCTION & GET THE RETURN STATUS */
				return_status = g_Routine_List_st[index].start_fnptr();

				/* CHECK FOR THE RETURN STATUS */
				if(return_status == UDS_TRUE)
				{
					g_Routine_List_st[index].RoutineState = UDS_ROUTINE_STOPPED;
				}
			}
		}
	}
}

/*
 * @brief    This function processes the diagnostic request messages & their responses
 * @param    BufferIndex - Message buffer index (0 to 255)
 * @return   None
 */
static void UDS_Dispatcher(UDS_UINT8 BufferIndex)
{
    UDS_UINT8 *fl_MsgPtr;
    UDS_UINT8 fl_index_u8;
    UDS_UINT16 fl_ReqLen_u16;
    UDS_UINT8 fl_SID_matchedflag_u8 = UDS_FALSE;
    l_UDS_Service_Index_u8 = UDS_INVALID_SERVICE;

    fl_ReqLen_u16 = l_BufferLen_u16[BufferIndex];
    fl_MsgPtr = l_UDSDiag_Buffer_u8[BufferIndex];
    /*Check whether Length of the request received in invalid*/
    if(fl_ReqLen_u16 == UDS_FALSE)
    {
        /*Update the buffer error so that MainFunction execution doesn't happen*/
        l_BufferError_u8[BufferIndex] = UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH;
        /*Send NRC 0x11 for unsupported service request type*/
        UDS_SendNegativeResponse(UDS_NRC_INVALID_FORMAT_OR_MSG_LENGTH, fl_MsgPtr[BUFF_INDEX_ONE]);
    }
    else
    {
        for(fl_index_u8 = UDS_COUNTER_ZERO; ((fl_index_u8 < MAX_NO_OF_SRV) && (l_UDS_Service_Index_u8 == UDS_INVALID_SERVICE)); fl_index_u8++)
        {
            /*Check whether SID requested is matching with Server available SIDs*/
            if(fl_MsgPtr[BUFF_INDEX_ZERO] == g_UDS_ServiceInfoTable_st[fl_index_u8].RequestSID)
            {
                /*Set the flag for SID match found to check for NRC*/
                fl_SID_matchedflag_u8 = UDS_TRUE;
                l_UDS_Service_Index_u8 = fl_index_u8;
                /*Session Check for matching SID in the Info table*/
                if((g_UDS_ServiceInfoTable_st[fl_index_u8].SupportedSession == UDS_NO_SESSION_CHECK) || \
                        (((l_UDS_Current_Session_u8) & (g_UDS_ServiceInfoTable_st[fl_index_u8].SupportedSession)) != UDS_NO_SESSION_CHECK))
                {
                    /*Check whether the request received from current address is supported for this SID*/
                    if((l_UDS_Current_RequestType_u8 & g_UDS_ServiceInfoTable_st[fl_index_u8].RequestTypeSupported) != UDS_FALSE)

                    {
                            /*No session check for this match*/
                            l_BufferCtrl_st[BufferIndex].CurrentSrvIdx = fl_index_u8;
                    }
                    else
                    {
                        /*Trigger NRC 0x10 since Request received through an address is not supported
                          for the requested SID by the Server*/
                          UDS_SendNegativeResponse(UDS_NRC_SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION, fl_MsgPtr[BUFF_INDEX_ZERO]);

                    }
                }
                else
                {
                    /*Update the buffer error so that MainFunction execution doesn't happen*/
                    l_BufferError_u8[BufferIndex] = UDS_NRC_SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
                    /*Requested Service not supported in current session, Update NRC accordingly*/
                    UDS_SendNegativeResponse(UDS_NRC_SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION, fl_MsgPtr[BUFF_INDEX_ZERO]);

                }
            }
            else
            {
                /*Do Nothing*/
            }
        }
        if(fl_SID_matchedflag_u8 == UDS_FALSE)
        {
            /*Update the buffer error so that MainFunction execution doesn't happen*/
            l_BufferError_u8[BufferIndex] = UDS_NRC_SERVICE_NOT_SUPPORTED;
            /*Send NRC 0x11 for unsupported service request type*/
            UDS_SendNegativeResponse(UDS_NRC_SERVICE_NOT_SUPPORTED, fl_MsgPtr[BUFF_INDEX_ZERO]);
        }
        else
        {
            /*Do Nothing*/
        }
        if((l_BufferError_u8[BufferIndex] == UDS_NOERROR))
        {
            fl_MsgPtr++;
            g_UDS_ServiceInfoTable_st[l_UDS_Service_Index_u8].FuncHandler.MainFuncHandler(fl_MsgPtr, (fl_ReqLen_u16 - LENGTH_ONE));
        }
    }
}

/*
 * @brief    This function processes the Negative response to be sent by the core layer
 * @param    ErrorNRC - Error Code to be sent as Negative Response
 * @param    ServiceID - Service Identifier for which the NRC is to be transmitted
 * @return   NULL
 */
void UDS_SendNegativeResponse( UDS_UINT8 ErrorNRC, UDS_UINT8 ServiceID)
{
    static UDS_UINT8 fl_MsgBfr_u8[BUFF_INDEX_FOUR];

    /*Restart the Session timer only if the NRC isn't RCRRP*/
    if(ErrorNRC != UDS_NRC_REQUEST_CORRECTLY_RECEIVED_RESPONSE_PENDING)
    {
        /*Start the S3 timer upon transmission of a response*/
        UDS_StartS3Timer();

        /* Reset P2 and P2* timers if NRC is not equal to RCRRP*/
        UDS_StopP2Timer();
        UDS_Stop_P2Star_Timer();
    }

    /*Reset P4 Timers*/
    UDS_StopP4Timer();

    /*Check whether the NRC to be be transmitted is for a Functionally addressed request*/
    if(l_UDS_Current_RequestType_u8 == UDS_FUNCTIONAL_REQ)
    {
        /*Since Functionally addressed requests need not send NRC 0x31, 0x11, 0x12, 0x7F (suppression).
          Check for such NRCs & reset the Response to be sent indication flag.
          0x10 is triggered for requested SID through physical or functional address not supported
          as per Server's configurations.
          Suppressing 0x10 as well to avoid bombarding the client with unwanted responses*/
        if((ErrorNRC == UDS_NRC_REQUEST_OUT_OF_RANGE) || (ErrorNRC == UDS_NRC_SERVICE_NOT_SUPPORTED) || \
                (ErrorNRC == UDS_NRC_SUBFUNCTION_NOT_SUPPORTED) || (ErrorNRC == UDS_NRC_GENERAL_REJECT) || \
                (ErrorNRC == UDS_NRC_SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION))
        {
            /*Response not to be sent for Functionally Addressed request message with above NRCs*/
            l_BufferCtrl_st[l_UDS_Current_RequestType_u8 - 1u].MakeResponse = UDS_FALSE;
        }
        else
        {
            /*Response to be sent indication flag is set for other NRCs*/
            l_BufferCtrl_st[l_UDS_Current_RequestType_u8 - 1u].MakeResponse = UDS_TRUE;
        }
    }
    else
    {
        /*No constraints for sending NRCs for any Physically addressed diagnostic request*/
    }

    /*Process the buffer to be sent through CAN as response*/
    fl_MsgBfr_u8[BUFF_INDEX_ZERO] = UDS_NEG_RESP_ID;
    fl_MsgBfr_u8[BUFF_INDEX_ONE] = ServiceID;
    fl_MsgBfr_u8[BUFF_INDEX_TWO] = ErrorNRC;

    /*Verify whether response to be sent to the client or to be suppressed*/
    if(l_BufferCtrl_st[l_UDS_Current_RequestType_u8 - 1u].MakeResponse != UDS_FALSE)
    {
        /*Transmit the Response processed to the client*/
        (void)UDS_TX_RESPONSE(&fl_MsgBfr_u8[BUFF_INDEX_ZERO], UDS_NEGRESP_LENGTH);
        l_BufferCtrl_st[l_UDS_Current_RequestType_u8 - 1u].Confirmation_Txed = UDS_TRUE;
    }
}

/*
 * @brief    This function processes the Positive response to be sent by the core layer
 * @param    DataBuffer - Data buffer carrying the response to be sent
 * @param    RespLen - Length of the response to be sent(0 TO 0xFF)
 * @return   NULL
 */
void UDS_SendPositiveResponse(UDS_UINT8 *DataBuffer, UDS_UINT16 RespLen)
{
    /*Start the S3 timer upon transmission of a response*/
    UDS_StartS3Timer();
    /*Reset P2, P2* & P4 Timers*/
    UDS_StopP2Timer();
    UDS_Stop_P2Star_Timer();
    UDS_StopP4Timer();
    /*Buffer Handling to transmit the data to CAN layer*/

    if(l_BufferCtrl_st[l_UDS_Current_RequestType_u8 - 1u].MakeResponse != UDS_FALSE)
    {
        /*Transmitp the Response processed to the client*/
        (void)UDS_TX_RESPONSE(DataBuffer, RespLen);
        l_BufferCtrl_st[l_UDS_Current_RequestType_u8 - 1u].Confirmation_Txed = UDS_TRUE;
    }
}

/*
 * @brief    This function indicates the core layer to start the P2 timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_StartP2Timer(void)
{
    l_UDS_P2_TimerCount_u32 = UDS_P2_TIMER_MAXCNT;
}

/*
 * @brief    This function indicates the core layer to stop P2 timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_StopP2Timer(void)
{
    l_UDS_P2_TimerCount_u32 = UDS_TIMER_RESET_VALUE;
}

/*
 * @brief    This function indicates the core layer to start S3 timer
 * @param    NULL
 * @return   NULL
 */
void UDS_StartS3Timer(void)
{
    l_UDS_S3_TimerCount_u32 = UDS_S3_TIMER_MAXCNT;
}

/*
 * @brief    This function indicates the core layer to stop S3 timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_StopS3Timer(void)
{
    l_UDS_S3_TimerCount_u32 = UDS_TIMER_RESET_VALUE;
}

/*
 * @brief    This function is used to get the S3 timer current value
 * @param    NULL
 * @return   uint32_t - CurrentTimerValue
 */
static UDS_UINT32 UDS_GetS3_TimerValue(void)
{
    return l_UDS_S3_TimerCount_u32;
}

/*
 * @brief    This function indicates the core layer to start P4 timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_StartP4Timer(void)
{
    l_UDS_P4_TimerCount_u32 = UDS_P4_TIMER_MAXCNT;
}

/*
 * @brief    This function indicates the core layer to stop P4 timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_StopP4Timer(void)
{
    l_UDS_P4_TimerCount_u32 = UDS_TIMER_RESET_VALUE;
}

/*
 * @brief    This function is used to convey the core layer for P2 time out
 * @param    NULL
 * @return   NULL
 */
static void UDS_P2TimeOut(void)
{
    /*Send NRC 0x78 for RCRRP when  P2 timeout occurs */
    UDS_SendRCRRP();

    /*Start P2* timer after sending RCRRP NRC*/
    UDS_Start_P2Star_Timer();

    /*Stop P2 timer*/
    UDS_StopP2Timer();

    /*User-Specific timeout action execution*/
    //UDS_P2_TIMEOUT_ACTION_USER();
}

/*
 * @brief    This function is used to convey the core layer for S3 time out
 * @param    NULL
 * @return   NULL
 */
static void UDS_S3TimeOut(void)
{
    /*Stop diagnostic request timer since session time out has occurred*/
    UDS_StopP2Timer();

    /*Since current session timeout has occurred, bring it back to default session*/
    if(l_UDS_Current_Session_u8 != UDS_DEFAULT_SESS)
    {
        /*Return to default session*/
        l_UDS_Current_Session_u8 = UDS_DEFAULT_SESS;

        /*Relock the security access*/
        UdsApp_SecurityLock();

        /*User-Specific timeout action execution*/
        UDS_S3_TIMEOUT_ACTION_USER();
    }
    else
    {
        /*Do nothing*/
    }
}

/*
 * @brief    This function is used to convey the core layer for P4 time out
 * @param    NULL
 * @return   NULL
 */
static void UDS_P4TimeOut(void)
{
    /*User-Specific timeout action execution*/
    UDS_P4_TIMEOUT_ACTION_USER();
}

/*
 * @brief    This function is used to Start the P2* (Response Pending) timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_Start_P2Star_Timer(void)
{
    l_UDS_P2STAR_TimerCount_u32 = UDS_P2STAR_TIMER_MAXCNT;
}

/*
 * @brief    This function is used to Stop the P2 * timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_Stop_P2Star_Timer(void)
{
    l_UDS_P2STAR_TimerCount_u32 = UDS_TIMER_RESET_VALUE;
}

/*
 * @brief    This function is used to Get the P2 * timer value
 * @param    NULL
 * @return   NULL
 */
static UDS_UINT32 UDS_Get_P2Star_TimerValue(void)
{
    return l_UDS_P2STAR_TimerCount_u32;
}

/*
 * @brief    This function is used to convey the core layer for P2* (Response Pending) time out
 * @param    NULL
 * @return   NULL
 */
static void UDS_P2Star_TimeOut(void)
{
    /*Send RCRRP */
    UDS_SendRCRRP();
    /*User-Specific timeout action execution*/
    //UDS_P2STAR_TIMEOUT_ACTION_USER();

}

/*
 * @brief    This function is used to send the NRC (0x78) for RequestCorrectlyReceivedResponsePending
 * @param    NULL
 * @return   NULL
 */
void UDS_SendRCRRP(void)
{
    /*Load the Data Buffer */
    const UDS_UINT8 *fl_MsgPtr_u8 = l_UDSDiag_Buffer_u8[l_UDS_Current_RequestType_u8 - 1u];

    if(l_RCRRP_Counter_u8 == UDS_TIMER_RESET_VALUE)
    {
        /*Transmit the RCRRP NRC - 0x78 */
        UDS_SendNegativeResponse(UDS_NRC_REQUEST_CORRECTLY_RECEIVED_RESPONSE_PENDING, \
                                 fl_MsgPtr_u8[BUFF_INDEX_ZERO]);

        /*Preserve the FRC for RCRRP to compare in the next iteration*/
        l_RCRRRP_PreviousTimeStamp_u32 = UDS_Get_RCCRRP_FRC_Value();

        /*Increment the RCRRP counter*/
        l_RCRRP_Counter_u8++;
    }
    else
    {
        /*Get the FRC for RCRRP at that instance*/
        l_RCRRRP_CurrentTimeStamp_u32 = UDS_Get_RCCRRP_FRC_Value();

        /*Check whether the RCRRP counter has been reloaded with maximum value after the previous RCRRP call*/
        if(l_RCRRRP_PreviousTimeStamp_u32 < l_RCRRRP_CurrentTimeStamp_u32)
        {
            /*Check whether the RCRRP has reached its maximum count*/
            if(l_RCRRP_Counter_u8 < UDS_RCRRP_MAX_COUNT)
            {
                /*Increment the RCRRP counter*/
                l_RCRRP_Counter_u8++;

                /*Transmit the RCRRP NRC */
                UDS_SendNegativeResponse(UDS_NRC_REQUEST_CORRECTLY_RECEIVED_RESPONSE_PENDING, \
                                         fl_MsgPtr_u8[BUFF_INDEX_ZERO]);
            }
            else
            {
                /*Transmit the General Reject 0x10 NRC */
                UDS_SendNegativeResponse(UDS_NRC_GENERAL_REJECT, fl_MsgPtr_u8[BUFF_INDEX_ZERO]);
            }
        }
        /*RCRRP FRCC has been reloaded after previous time stamp*/
        else
        {
            /*Check whether the RCRRP counter has been reloaded with maximum value after the previous RCRRP call*/
            if(((UDS_RCRRP_FRC_MAX_VAL - l_RCRRRP_CurrentTimeStamp_u32) + l_RCRRRP_PreviousTimeStamp_u32) > \
                UDS_RCRRP_ENHANCEMENT_FORMULA)
            {
                /*Check whether the RCRRP has reached its maximum count*/
                if(l_RCRRP_Counter_u8 < UDS_RCRRP_MAX_COUNT)
                {
                    /*Increment the RCRRP counter*/
                    l_RCRRP_Counter_u8++;

                    /*Transmit the RCRRP NRC */
                    UDS_SendNegativeResponse(UDS_NRC_REQUEST_CORRECTLY_RECEIVED_RESPONSE_PENDING, \
                                             fl_MsgPtr_u8[BUFF_INDEX_ZERO]);

                    l_RCRRRP_PreviousTimeStamp_u32 = l_RCRRRP_CurrentTimeStamp_u32;

                    UDS_Start_P2Star_Timer();
                }
                else
                {
                    /*Transmit the General Reject 0x10 NRC */
                    UDS_SendNegativeResponse(UDS_NRC_GENERAL_REJECT, fl_MsgPtr_u8[BUFF_INDEX_ZERO]);
                }
            }
        }
    }
}

/*
 * @brief    This function is used to get the P2 timer current value
 * @param    NULL
 * @return   uint8_t - CurrentTimerValue
 */
static UDS_UINT32 UDS_GetP2_TimerValue(void)
{
    return l_UDS_P2_TimerCount_u32;
}

/*
 * @brief    This function is used to get the P4 timer current value
 * @param    NULL
 * @return   uint8_t - CurrentTimerValue
 */
static UDS_UINT32 UDS_GetP4_TimerValue(void)
{
    return l_UDS_P4_TimerCount_u32;
}

/*
 * @brief    This function is used to indicate the reception of physical request
 * @param    Result - TP layer message Rx status
 * @param    DataLen - Length of the data
 * @return   NULL
 */
void UDS_PhysicalReq_Indication(uint8_t Result,UDS_UINT16 DataLen)
{
    if(E_NOT_OK != Result)
    {
        /*Start the P2 timer*/
        UDS_StartP2Timer();

        /*Start the P4 performance timer*/
        UDS_StartP4Timer();

        /*Update the Global variable for notifying current request is a physical request*/
        l_UDS_Current_RequestType_u8 = UDS_PHYSICAL_REQ;

        /*Initialize Buffer for physical request type as no error before starting to process the received data*/
        l_BufferError_u8[BUFF_INDEX_ZERO] = UDS_NOERROR;

        /*Store the data length in corresponding buffer*/
        l_BufferLen_u16[BUFF_INDEX_ZERO] = DataLen;

        /*Set the request received indication flag*/
        l_BufferCtrl_st[BUFF_INDEX_ZERO].Ind_Flag = UDS_TRUE;

        /*Set the flag to start response framing*/
        l_BufferCtrl_st[BUFF_INDEX_ZERO].MakeResponse = UDS_TRUE;

        /*Initialize the counter for the new request received*/
        l_RCRRP_Counter_u8 = UDS_INIT;
    }

}

/*
 * @brief    This function is used to indicate the reception of functional request
 * @param    Result - TP layer message Rx status
 * @param    DataLen - Length of the data
 * @return   NULL
 */
void UDS_FunctionalReq_Indication(uint8_t Result,UDS_UINT16 DataLen)
{
    if(E_NOT_OK != Result)
    {
        UDS_StartP2Timer();
        /*Update the Global variable for notifying current request is a functional request*/
        l_UDS_Current_RequestType_u8 = UDS_FUNCTIONAL_REQ;

        /*Initialize Buffer for functional request type as no error before starting to process the received data*/
        l_BufferError_u8[BUFF_INDEX_ONE] = UDS_NOERROR;

        /*Store the data length in corresponding buffer*/
        l_BufferLen_u16[BUFF_INDEX_ONE] = DataLen;

        /*Set the request received indication flag*/
        l_BufferCtrl_st[BUFF_INDEX_ONE].Ind_Flag = UDS_TRUE;

        /*Set the flag to start response framing*/
        l_BufferCtrl_st[BUFF_INDEX_ONE].MakeResponse = UDS_TRUE;

        /*Initialize the counter for the new request received*/
        l_RCRRP_Counter_u8 = UDS_INIT;
    }
}

/*
 * @brief    This function is used to get the functional reception buffer from TP layer
 * @param    DataLen - Length of the data
 * @return   UDS_UINT8* - Address Diagnostic Buffer for receiving data from TP layer
 */
UDS_UINT8* UDS_FunctionalGetBuffer(UDS_UINT16 DataLen)
{
    UDS_UINT8* fl_BuffPtr_u8;

    /*Check whether the data length is invalid*/
    if(DataLen > UDS_SECONDARYBUFF_LENGTHMAX)
    {
        /*Store NULLL pointer into the Pointer that returns for invalid length case*/
        fl_BuffPtr_u8 = ((void*)0);
    }
    else
    {
        /*Store actual data buffer into the Pointer that returns for valid length case*/
        fl_BuffPtr_u8 = l_UDSDiag_Buffer_u8[BUFF_INDEX_ONE];
    }
    /*Return the pointer buffer*/
    return fl_BuffPtr_u8;
}


/*
 * @brief    This function is used to get the physical reception buffer from TP layer
 * @param    DataLen - Length of the data
 * @return   UDS_UINT8* - Address Diagnostic Buffer for receiving data from TP layer
 */
UDS_UINT8* UDS_PhysicalGetBuffer(UDS_UINT16 DataLen)
{
    UDS_UINT8* fl_BuffPtr_u8;
    /*Check whether the data length is invalid*/
    if(DataLen > UDS_PRIMARYBUFF_LENGTHMAX)
    {
        /*Store NULLL pointer into the Pointer that returns for invalid length case*/
        fl_BuffPtr_u8 = ((void*)0);
    }
    else
    {
        /*Store actual data buffer into the Pointer that returns for valid length case*/
        fl_BuffPtr_u8 = l_UDSDiag_Buffer_u8[BUFF_INDEX_ZERO];
    }
    /*Return the address of buffer where the received data will be stored from TP*/
    return fl_BuffPtr_u8;
}

/*
 * @brief    This function is used to suppress the positive response on receiving a request
 * @param    BuffIndex - Index of the buffer to get the current request type
 * @return   NULL
 */
void UDS_SuppressPosResponse(UDS_UINT8 BuffIndex)
{
    /*Stop P2 timer since it is response suppression*/
    UDS_StopP2Timer();

    /*Restart S3 session timer */
    UDS_StartS3Timer();

    /*Clear the flag that is responsible for transmitting responses*/
    l_BufferCtrl_st[BuffIndex - 1u].MakeResponse = UDS_FALSE;
}

/*
 * @brief    This function is used to get the current request type
 * @param    NULL
 * @return   uint8_t - CurrentRequestType
 */
UDS_UINT8 UDS_GetCurrentRequestType(void)
{
    return l_UDS_Current_RequestType_u8;
}

/*
 * @brief    This function is used to get the buffer length of current request
 * @param    fl_RequestType_u8 - Physical/ Functional
 * @return   uint32_t - DLC of the request received
 */
UDS_UINT32 UDS_GetBufferLength(uint8_t fl_RequestType_u8)
{
    return l_BufferLen_u16[fl_RequestType_u8 - 1u];
}

/*
 * @brief    This function is used to get the delay timer current value
 * @param    NULL
 * @return   uint32_t - CurrentTimerValue
 */
UDS_UINT32 UDS_Get_DelayTimer_Value(void)
{
    return l_DelayTimer_Count_u32;
}

/*
 * @brief    This function is used to start the delay timer
 * @param    NULL
 * @return   NULL
 */
void UDS_Start_DelayTimer(void)
{
    l_DelayTimer_Count_u32 = UDS_DELAY_TIMER_MAXCNT;
}

/*
 * @brief    This function is used to start the delay timer
 * @param    NULL
 * @return   NULL
 */
static void UDS_Stop_DelayTimer(void)
{
    l_DelayTimer_Count_u32 = UDS_TIMER_RESET_VALUE;
}

/*
 * @brief    This function is used to get the current session of the server
 * @param    NULL
 * @return   uint8_t - Current session value
 */
UDS_UINT8 UDS_Get_Current_Session(void)
{
    UDS_UINT8 fl_session_u8;
    /*Check whether it is DEFAULT session's masked value 0x08*/
    if(l_UDS_Current_Session_u8 == UDS_DEFAULT_SESS)
    {
        /*Update with Default session's unmasked value 0x01*/
        fl_session_u8 = UDS_DEFAULT_SESSION;
    }
    /*Check whether it is PROGRAMMING session's masked value 0x04*/
    else if(l_UDS_Current_Session_u8 == UDS_PROG_SESS)
    {
        /*Update with Default session's unmasked value 0x02*/
        fl_session_u8 = UDS_PROGRAMMING_SESSION;
    }
    /*Check whether it is EXTENDED session's masked value 0x02*/
    else if(l_UDS_Current_Session_u8 == UDS_EXTND_SESS)
    {
        /*Update with Default session's unmasked value 0x03*/
        fl_session_u8 = UDS_EXTENDED_DIAGNOSTIC_SESSION;
    }
    /*Check whether it is SAFETY SYSTEM session's masked value 0x01*/
    else if(l_UDS_Current_Session_u8 == UDS_SAFETY_SYS_DIAG_SESS)
    {
        /*Update with Default session's unmasked value 0x04*/
        fl_session_u8 = UDS_SAFETY_SYSTEM_DIAGNOSTIC_SESSION;
    }
    else
    {
        /*Do nothing*/
        /*Should not reach this part of code since only 4 possible sessions are available*/
    }

    /*Return the user with current session data*/
    return fl_session_u8;
}

/*
 * @brief    This function is used to get the RCRRP FRC current value
 * @param    NULL
 * @return   uint32_t - Current Counter Value
 */
static UDS_UINT32 UDS_Get_RCCRRP_FRC_Value(void)
{
    return l_RCRRP_FRC_u32;
}

/*
 * @brief    This function is used to reset the RCRRP FRC current value
 * @param    NULL
 * @return   NULL
 */
static void UDS_Reset_RCCRRP_FRC_Value(void)
{
    l_RCRRP_FRC_u32 = UDS_RCRRP_FRC_MAX_VAL;
}

/*
 * @brief    This function is used to get the current session of the server
 * @param    fl_current_sess_u8 - Current session value
 * @return   NULL
 */
void UDS_Update_Current_Session(UDS_UINT8 fl_current_sess_u8)
{
    l_UDS_Current_Session_u8 = fl_current_sess_u8;
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
    REVISION NUMBER      : V2.0.0
    REVISION DATE        : 30-July-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : RCRRP & P2* timer handling implemented & Code alignment
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.9
    REVISION DATE        : 02-July-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Service implementation done & below Defects fixed:
                           1. Renamed UDS_GetPrimaryBufferLength as UDS_GetBufferLength to accommodate any type of
                           addressing's length
                           2. S3 timer handling done for Supress response Use-case.
                           3. Send_RCRRP API altered to handle timing parameters for Bootloader
                           4. P2* Timer action implemented for Bootloader
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.8
    REVISION DATE        : 27-May-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)  
    DESCRIPTION          : Removed existing Functional Addressing logic in Dispatcher function & reimplemented. 
                           Below Defects fixed:
                           1. NRC 0x12 filtering(suppression) done for Functionally addressed request
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.7
    REVISION DATE        : 16-May-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)  
    DESCRIPTION          : Removed existing Functional Addressing logic in Dispatcher function & reimplemented. 
                           Below Defects fixed:
                           1. P2 timeout action on suppressing.
                           2. Prefetch entry on DataLength 0x00
                           3. Prefetch entry on invalid SID reception from client.
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.6
    REVISION DATE        : 14-May-2020                                  
    CREATED / REVISED BY : Pavithra R(Pavithra.r@niyatainfotech.com)   
    DESCRIPTION          : Functional Addressing Check added in dispatcher
                           Functional Req indication  E_NOT_Ok condition and Result parameter added                              
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.5
    REVISION DATE        : 16-Apr-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Comments updated & below Defects fixed:
                            1. GIT-#341 Macro values of sessions updated according to masked values to trigger NRC 0x7F
                            2. GIT-#341 Current session update to Core Layer from App Layer on session transition
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.4
    REVISION DATE        : 04-Apr-2020                                  
    CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)   
    DESCRIPTION          : Static Analysis Fixes done                                 
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.3
    REVISION DATE        : 30-Mar-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Peer Review Comments Fixed                                 
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.2                                                           
    REVISION DATE        : 27-Mar-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Peer Review Comments Fixed                                 
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.1                                                           
    REVISION DATE        : 20-Mar-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Code Fixed after initial High Level testing                                 
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.0                                                           
    REVISION DATE        : 11-Mar-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! UDS_C */
