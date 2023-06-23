/* @file UART_DATAMANAGER_C */
#ifndef UART_DATAMANAGER_C
#define UART_DATAMANAGER_C
/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : MOHAMED IBRAHIM M  (ibrahim@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : UART_DataManager.c
 *  Version                         : v1.0.0
 *  Micros supported                : Micro Supported
 *  Compilers supported             : J link
 *  Platforms supported             : Platform Independent
 *  Description                     : This file consists of definitions of UART_DataManager
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "UART_DataManager.h"
#include "Button_Manager.h"
#include "HMI_Main_Screen.h"
#include "HMI_Phone.h"
#include "HMI_GUI_Interface.h"
/***********************************************************************************************************************
 *                                               I N C L U D E  LIBRARY F I L E S
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/
/* This macro is used to configure to convert the ASCII Value of data to Decimal*/
#define DECIMAL_VALUE 48
/* This Macro is used to config the Dummy packet size of data*/
#define SIZE_OF_DUMMY_PKT 0

#define UART_BUFFER_SIZE 100

/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*
 * @brief: This variable is used to define the size of each packet.
 */
const UART_FRAME_INFO_TYPE_ST UART_Frame_Details_St[MAX_PKT] = {
    (sizeof(HERO_SMARTPHONE_NAVIGATION_PKT_TYPE_ST) + 1),
    sizeof(HERO_SMARTPHONE_STATUS_PKT_TYPE_ST),
    sizeof(HERO_SMARTPHONE_TIME_PKT_TYPE_ST),
    sizeof(HERO_SMARTPHONE_MISSED_CALL_PKT_TYPE_ST),
    sizeof(HERO_SMARTPHONE_SMS_NUMBER_PKT_TYPE_ST),
    sizeof(HERO_SMARTPHONE_CALL_STATUS_PKT_TYPE_ST),
    sizeof(HERO_SMARTPHONE_CALL_NUMBER_PKT_TYPE_ST),
    sizeof(HERO_SMARTPHONE_MUSIC_PKT_TYPE_ST),
    sizeof(HERO_CLUSTER_JOYSTICK_PKT_TYPE_ST),
    sizeof(HERO_SMARTPHONE_JOYSTICK_ACK_PKT_TYPE_ST),
    sizeof(CLUSTER_PASSCODE_PKT_TYPE_ST)};

/*This variable is used to define the state of rx set data.*/
volatile uint8_t g_Set_RX_Data_state_u8;

/*This buffer variable is used to hold the data of receiving packet*/
uint8_t g_UART_RX_Buffer_u8[MAX_RX_DATA_SIZE];

/*This structure variable is used to receive the data*/
UART_RX_DATA_TYPE_ST Uart_Rx_Data_st;

uint8_t UART_buffer[UART_BUFFER_SIZE] = {0};
volatile uint8_t Uart_buffer_index = 0;
volatile uint32_t Total_byte_Count = 0;
uint16_t fr_counter = 0;

uint16_t g_Uart_Timeout_Counter_u16;
uint8_t g_BLE_Connection_Status_u8 = 0;
bool g_CallEvent_Bl = FALSE;
bool g_VolumeEvent_Bl = FALSE;
uint8_t  g_VolumeLevel_U8 = 0;

UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST UART_DataMgr_Pkt_St[MAX_PKT];

UART_DATA_MGR_CLUSTER_PKT_TYPE_ST g_UART_DataMgr_Cl_Pkt_St;

UARTFrameTimeoutStatusTypeSt UARTFrameTimeoutStatusSt[MAX_PKT] = 
{
   /*     NAV_PKT */ 			{30000/TASK_PERIOD, 0, 0, NULL},
   /*     STS_PKT */ 			{30000/TASK_PERIOD, 0, 0, NULL},
   /*     TIME_PKT*/ 			{30000/TASK_PERIOD, 0, 0, NULL},
   /*     MISSED_CALL_PKT */ 	{30000/TASK_PERIOD, 0, 0, NULL},
   /*     SMS_NUM_PKT */ 		{30000/TASK_PERIOD, 0, 0, NULL},
   /*     CALL_STS_PKT */ 		{30000/TASK_PERIOD, 0, 0, NULL},
   /*     CALL_NUM_PKT */ 		{30000/TASK_PERIOD, 0, 0, NULL},
   /*     MUSIC_PKT */ 			{30000/TASK_PERIOD, 0, 0, NULL},
   /*     JOYSTICK_PKT */ 		{30000/TASK_PERIOD, 0, 0, NULL},
   /*     JOYSTICK_ACK_PKT */	{30000/TASK_PERIOD, 0, 0, NULL},
   /*     PASSCODE_PKT */ 		{30000/TASK_PERIOD, 0, 0, &Passcode_return},
};

BLE_Frame_Details_Type_St BLE_Frame_Details_St[MAX_PKT] = 
{
    /*     NAV_PKT */ 			{0x31},
    /*     STS_PKT */ 			{0x33},
    /*     TIME_PKT*/ 			{0x34},
    /*     MISSED_CALL_PKT */ 	{0x35},
    /*     SMS_NUM_PKT */ 		{0x36},
    /*     CALL_STS_PKT */ 		{0x37},
    /*     CALL_NUM_PKT */ 		{0x38},
    /*     MUSIC_PKT */ 		{0x39},
    /*     JOYSTICK_PKT */ 		{0x41},
    /*     JOYSTICK_ACK_PKT */	{0x42},
    /*     PASSCODE_PKT */ 		{0x45},
};


const Cluster_Event_Type_St g_Cluster_Event_St[Max_Joystick_Event] = {
    /*EVENT_TYPE*/ /*JOYSTICK_DATA*/
    {JOYSTICK_EVENT, 0x00},
    {JOYSTICK_EVENT, 0x0A},
    {JOYSTICK_EVENT, 0X0F},
    {JOYSTICK_EVENT, 0x14},
    {JOYSTICK_EVENT, 0x19},
    {JOYSTICK_EVENT, 0x1E},
    {JOYSTICK_EVENT, 0x23},
    {JOYSTICK_EVENT, 0x28},
    {JOYSTICK_EVENT, 0x2D},
    {JOYSTICK_EVENT, 0x32},
    {JOYSTICK_EVENT, 0x37},
    {JOYSTICK_EVENT, 0x3C},
    {JOYSTICK_EVENT, 0x41},
    {JOYSTICK_EVENT, 0x46},
    {JOYSTICK_EVENT, 0x4B},
    {MUSIC_META_DATA_2, 0x30},
    {MUSIC_META_DATA_2, 0x31},
    {MUSIC_META_DATA_2, 0x32},
    {CONTACT_INDEX, 0x64},
    {CONTACT_INDEX, 0x65},
    {CONTACT_INDEX, 0x66},
    {CONTACT_INDEX, 0x67},
    {CONTACT_INDEX, 0x68},
    {CONTACT_INDEX, 0x69}

};

/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    This enum processes the flag for joystick event, music meta, contact
 * @param    Nil
 * @return   Nil
 */

typedef enum
{
    Joystick_Event,
    Music_Meta_2,
    Contact_Index,
    Max_Flag

} FLAG_EN;

/*
 * @brief    This structure processes the member for joystick event, music meta, contact
 * @param    Nil
 * @return   Nil
 */

typedef struct
{
    uint32_t Joystick_Event : 1;
    uint32_t Music_Meta_2 : 1;
    uint32_t Contact_Index : 1;

} Cluster_Flag_St;

/*
 * @brief    This structure processes the flag structure in the cluster flag structure datatype
 * @param    Nil
 * @return   Nil
 */
Cluster_Flag_St g_Flag_st;

/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/* API is used to initialize the init variables with its defaukt values. */
void UART_DataManager_Init(void)
{
    /* DO NOTHING */
}

/* API is used to initialize the peripherals */
void UART_DataManager_DeInit(void)
{
    /* DO NOTHING */
}

/* API is used to initialize the peripherals */
void UART_DataManager_Activate(void)
{
    /* DO NOTHING */
}

/* API is used to reset the peripherals */
void UART_DataManager_DeActivate(void)
{
    /* DO NOTHING */
}

/* API is used to execute the UART manager activity */
void UART_DataManager_MainFunction(void)
{
    /* LOCAL VARIABLE */
    uint8_t fl_Loop_u8 = 0;

    /* CHECK ALL THE FRAME TIMEOUT VALUE */
    for(fl_Loop_u8 = 0; fl_Loop_u8 < MAX_PKT; fl_Loop_u8++)
    {
        /* CHECK FOR THE FRAME ACTIVE STATUS - TIMEOUT COUNT ONLY IF MESSAGE IS ACTIVE */
        if(UARTFrameTimeoutStatusSt[fl_Loop_u8].FrameActiveSts == 1)
        {
            /* INCREMENT CRNT TIMEOUT VALUE */
            UARTFrameTimeoutStatusSt[fl_Loop_u8].CrntValue++;

            /* CHECK FOR THE TIMEOUT ELAPSED */
            if(UARTFrameTimeoutStatusSt[fl_Loop_u8].CrntValue > UARTFrameTimeoutStatusSt[fl_Loop_u8].TimerElapseValue)
            {
                /* TIMEOUT CALLBACK CHECK FOR VALID FUNCTION CONFIGURED */
                if(UARTFrameTimeoutStatusSt[fl_Loop_u8].UARTEventCallBackFn != NULL)
                {
                    /* INVOKE CALLBACK FUNCTION */
                    UARTFrameTimeoutStatusSt[fl_Loop_u8].UARTEventCallBackFn();
                }
                /* CLEAR THE TIMEOUT STATUS */
                UARTFrameTimeoutStatusSt[fl_Loop_u8].FrameActiveSts = 0;

                /* CLEAR MESSAGE INFORMATION */
                memset(&UART_DataMgr_Pkt_St[fl_Loop_u8], 0x00, sizeof(UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST));
            }
        }
        else
        {
            /* CLEAR COUNTER ONCE STATUS IS INACTIVE */
            UARTFrameTimeoutStatusSt[fl_Loop_u8].CrntValue = 0;
        }
    }

    /* CHECK FOR THE STATE MACHINE WAS NOT IDLE STATE - WAITING FOR FRAME COMPLETE */
    if(g_Set_RX_Data_state_u8 != WAIT_FOR_SOF)
    {
        g_Uart_Timeout_Counter_u16++;
    }

    /* CHECK FOR THE INCOMPLETE FRAME STILL PENDING - TIMEOUT STATE MACHINE (20ms) */
    if(g_Uart_Timeout_Counter_u16 > UART_FRAME_TIMEOUT)
    {
        /* CLEAR TIMEOUT */
        g_Uart_Timeout_Counter_u16 = 0;

        /* CLEAR BYTE COUNTER */
        Uart_Rx_Data_st.RX_Data_Counter = 0;

        /* CHANGE UART RECEIVE STATE */
        g_Set_RX_Data_state_u8 = WAIT_FOR_SOF;
    }
}

#if 0
/* API is used to get connectivity information from UART data manager */
void UART_DataManager_Set_Rx_Data(void)
{
    uint8_t fl_RX_Data_u8 = 0;

    switch (g_Set_RX_Data_state_u8)
    {
    case WAIT_FOR_SOF:
        fl_RX_Data_u8 = (LPUART_ReadByte(UART_CHANNEL) /*- DECIMAL_VALUE*/);
        g_Uart_Timeout_Counter_u16 = 0;
        if (fl_RX_Data_u8 == 0x0A)
        {
            Uart_Rx_Data_st.RX_Buffer[Uart_Rx_Data_st.RX_Data_Counter] = (LPUART_ReadByte(UART_CHANNEL) /*- DECIMAL_VALUE*/);
            Uart_Rx_Data_st.RX_Data_Counter++;
            g_Set_RX_Data_state_u8 = WAIT_FOR_ID;
        }
        break;

    case WAIT_FOR_ID:
        Uart_Rx_Data_st.RX_Buffer[Uart_Rx_Data_st.RX_Data_Counter] = (LPUART_ReadByte(UART_CHANNEL) /*-DECIMAL_VALUE*/);
        Uart_Rx_Data_st.RX_Data_Counter++;
        g_Set_RX_Data_state_u8 = WAIT_FOR_DATA;

        break;

    case WAIT_FOR_DATA:

        Uart_Rx_Data_st.RX_Buffer[Uart_Rx_Data_st.RX_Data_Counter] = (LPUART_ReadByte(UART_CHANNEL) /*-DECIMAL_VALUE*/);
        Uart_Rx_Data_st.RX_Data_Counter++;

        if ((Uart_Rx_Data_st.RX_Data_Counter) >= (UART_Frame_Details_St[(Uart_Rx_Data_st.RX_Buffer[1] - DECIMAL_VALUE)].UART_Frame_Length))
        {
            Uart_Rx_Data_st.RX_Data_Counter = 0;
            Memory_Copy(&g_UART_RX_Buffer_u8[0], &Uart_Rx_Data_st.RX_Buffer[0], UART_Frame_Details_St[(Uart_Rx_Data_st.RX_Buffer[1] - DECIMAL_VALUE)].UART_Frame_Length);
            UART_DataManager_Frame_Data(&g_UART_RX_Buffer_u8[0]);

            g_Set_RX_Data_state_u8 = WAIT_FOR_SOF;
        }
        else
        {
            /* Do Nothing*/
        }
        break;

    default:
        break;
    }
}
#endif
/* API is used to get connectivity information from UART data manager */
UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST UART_DataManager_Get_Connectivity_Info(CONNECTIVITY_PKT_EN fl_Connectivity_Pkt_En)
{
    return UART_DataMgr_Pkt_St[fl_Connectivity_Pkt_En];
}

/* API is used to clear the pin information from UART data manager */
void UART_DataManager_Clear_pin_Info(void)
{
    UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.ID = 0;
}

/* API is used to get data frames from UART datamanager */
void UART_DataManager_Frame_Data(uint8_t *Data_Ptr)
{
    uint8_t fl_Pkt_ID_u8 = (Data_Ptr[1] /*- (uint8_t)DECIMAL_VALUE*/);

    Memory_Copy((uint8_t *)&UART_DataMgr_Pkt_St[fl_Pkt_ID_u8], &Data_Ptr[0], UART_Frame_Details_St[fl_Pkt_ID_u8].UART_Frame_Length);
}

/* API is used to set connectivity information from UART data manager */
void Memory_Copy(uint8_t *destination, const uint8_t *source, uint16_t(size))
{
    uint16_t i = 0;

    for (i = 0; i < size; i++)
    {
        destination[i] = source[i];
    }
}

/* API is used to set connectivity information from UART data manager */
void UART_DataManager_Set_Connectivity_Info(Cluster_Joystick_Info_En fl_Event_En)
{
    g_UART_DataMgr_Cl_Pkt_St.Hero_Cluster_Joystick_Pkt_St.ID = 0x41;
    g_UART_DataMgr_Cl_Pkt_St.Hero_Cluster_Joystick_Pkt_St.StartOfFrame = 0x0A;
    g_UART_DataMgr_Cl_Pkt_St.Hero_Cluster_Joystick_Pkt_St.EndOfFrame = 0x0A;

    switch (g_Cluster_Event_St[fl_Event_En].Event_Type)
    {
    case JOYSTICK_EVENT:

        g_UART_DataMgr_Cl_Pkt_St.Hero_Cluster_Joystick_Pkt_St.JOYSTICK_EVENT = g_Cluster_Event_St[fl_Event_En].Joystick_Data;

        break;

    case MUSIC_META_DATA_2:
        g_UART_DataMgr_Cl_Pkt_St.Hero_Cluster_Joystick_Pkt_St.MUSIC_META_DATA_2_CL_INFO = g_Cluster_Event_St[fl_Event_En].Joystick_Data;

        break;

    case CONTACT_INDEX:
        g_UART_DataMgr_Cl_Pkt_St.Hero_Cluster_Joystick_Pkt_St.CONTACT_INDEX = g_Cluster_Event_St[fl_Event_En].Joystick_Data;

        break;
    }

    LPUART_WriteBlocking(UART_CHANNEL, (uint8_t *)&g_UART_DataMgr_Cl_Pkt_St.Hero_Cluster_Joystick_Pkt_St, sizeof(g_UART_DataMgr_Cl_Pkt_St.Hero_Cluster_Joystick_Pkt_St));
}

void LPUART10_IRQHandler(void)
{
    uint8_t fl_RX_Data_u8 = 0;
    uint8_t fl_Size_Of_Frame_u8 = 0;
    uint8_t fl_messageIdx_u8 = 0;

    /* If new data arrived. */
    if ((kLPUART_RxDataRegFullFlag)&LPUART_GetStatusFlags(UART_CHANNEL))
    {
        switch (g_Set_RX_Data_state_u8)
        {
        case WAIT_FOR_SOF:
            fl_RX_Data_u8 = (LPUART_ReadByte(UART_CHANNEL) /*- DECIMAL_VALUE*/);
            /* COUNTER CLEAR */
            g_Uart_Timeout_Counter_u16 = 0;
            if (fl_RX_Data_u8 == 0x0A)
            {
                Total_byte_Count = 0;
                UART_buffer[Total_byte_Count] = fl_RX_Data_u8;
                Total_byte_Count++;
                g_Set_RX_Data_state_u8 = WAIT_FOR_PAYLOAD;
            }
            break;

        case WAIT_FOR_PAYLOAD:
            UART_buffer[Total_byte_Count] = (LPUART_ReadByte(UART_CHANNEL) /*- DECIMAL_VALUE*/);
            Total_byte_Count++;
            g_Set_RX_Data_state_u8 = WAIT_FOR_DATA;
            break;
        case WAIT_FOR_ID:

            break;
            break;
        case WAIT_FOR_DATA:
            UART_buffer[Total_byte_Count] = (LPUART_ReadByte(UART_CHANNEL) /*- DECIMAL_VALUE*/);
            Total_byte_Count++;
            if (Total_byte_Count >= (UART_buffer[1] + 2)) /*UART_Frame_Details_St[(UART_buffer[1] - 48)].UART_Frame_Length)*/
            {
                /* CLEAR THE COUNTER ONCE ANY DATA RECIEVED FROM THE BLE */
                g_Uart_Timeout_Counter_u16 = 0u;

                /* GET THE MESSAGE INDEX FROM THE  */
                fl_messageIdx_u8 = Get_Message_Index(UART_buffer[3]);

                Memory_Copy((uint8_t *)&UART_DataMgr_Pkt_St[fl_messageIdx_u8], &UART_buffer[2], (Total_byte_Count - 2));
                g_Set_RX_Data_state_u8 = WAIT_FOR_SOF;
                Total_byte_Count = 0;
                fr_counter++;
            
                /* CHECK FOR THE VALID MESSAGE ID */
                if(fl_messageIdx_u8 < MAX_PKT)
                {
                    /* CLEAR THE TIMEOUT VALUE */
                    UARTFrameTimeoutStatusSt[fl_messageIdx_u8].CrntValue = 0;
                    /* SET THE STATUS FLAG - THIS SHALL TRIGGER POINT FOR THE FRAME TIMEOUT */
                    UARTFrameTimeoutStatusSt[fl_messageIdx_u8].FrameActiveSts = 1;
                }

                if (UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.ID == 0x45)
                {
                    if (UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.Ble_Status == BLE_PASSCODE_DISPLAY)
                    {
                        Set_Event(BLE_PASSCODE_EVENT);
                    }
                    else if (UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.Ble_Status == BLE_CONNECTED)
                    {
                        Set_Event(LEFT_BUTTON_LONG_PRESS);
                        /* CLEAR STATUS ONCE EVENT ADDRESSED */
                        UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.Ble_Status = 0xFF;
                        UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.ID = 0xFF;
                        g_BLE_Connection_Status_u8 = 1;
                        UARTFrameTimeoutStatusSt[PASSCODE_PKT].FrameActiveSts = 0;
                    }
                    else
                    {
                        /* RETURN BACK - IF DISCONECTED */
                        Set_Event(LEFT_BUTTON_LONG_PRESS);
                        ResetBLE();
                        /* CLEAR STATUS ONCE EVENT ADDRESSED */
                        UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.Ble_Status = 0xFF;
                        UART_DataMgr_Pkt_St[PASSCODE_PKT].Cluster_Passcode_Pkt_st.ID = 0xFF;
                        g_BLE_Connection_Status_u8 = 0;
                        memset(&UART_DataMgr_Pkt_St[0], 0x00, sizeof(UART_DataMgr_Pkt_St));
                    }
                    g_CallEvent_Bl = FALSE;
                }
                /* Event For Incoming Call */
                else if (UART_DataMgr_Pkt_St[CALL_STS_PKT].Hero_SmartPhone_Call_Status_Pkt_St.ID == 0x37)
                {
                    if ((UART_DataMgr_Pkt_St[CALL_STS_PKT].Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == 0x31 ||
                        UART_DataMgr_Pkt_St[CALL_STS_PKT].Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == 0x31) )
                    {       
                        if (g_CallEvent_Bl == FALSE)
                        {
                            g_VolumeLevel_U8 = UART_DataMgr_Pkt_St[CALL_STS_PKT].Hero_SmartPhone_Call_Status_Pkt_St.PH_VOLUME;
                        }
                        g_CallEvent_Bl = TRUE;            	
                        Set_Event(BLE_CALL_EVENT);
                       /* */
                    }
                    /* Return to Home Screen */
                    if (g_CallEvent_Bl == TRUE && ( UART_DataMgr_Pkt_St[CALL_STS_PKT].Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1 == 0x30 &&
                        UART_DataMgr_Pkt_St[CALL_STS_PKT].Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2 == 0x30 ))
                    {
                        Set_Event(LEFT_BUTTON_LONG_PRESS);
                        g_CallEvent_Bl = FALSE;
                    }
                    /* Event For Volume Call*/
                    if (g_VolumeEvent_Bl == FALSE && g_VolumeLevel_U8 != UART_DataMgr_Pkt_St[CALL_STS_PKT].Hero_SmartPhone_Call_Status_Pkt_St.PH_VOLUME)
                    {
                        g_VolumeEvent_Bl = TRUE;
                        g_VolumeLevel_U8 = UART_DataMgr_Pkt_St[CALL_STS_PKT].Hero_SmartPhone_Call_Status_Pkt_St.PH_VOLUME;
                        Set_Event(BLE_CALL_VOLUME_EVENT);
                    }
                    else
                    {
                       /* Do Nothing */
                    }
                }                
                else
                {
                    g_CallEvent_Bl = FALSE;
                }
            }
            break;
        default:
            break;
        }
    }
}


/*
* @brief		This function shall return the frame index from the frame details
* @param		Message_Id - message id which was populated in the frame 
* @return	index value in the table
*/
uint8_t Get_Message_Index(uint8_t Message_Id)
{
	/* Repeat until the pointers low and high meet each other */ 
	uint16_t fl_StartIndex = 0;
	uint16_t fl_MidIndex = 0;
	uint16_t value = 0;
	uint32_t fl_Array_Size_u32 = (sizeof(BLE_Frame_Details_St)/sizeof(BLE_Frame_Details_Type_St));

	while (fl_StartIndex <= fl_Array_Size_u32)
	{

		fl_MidIndex = fl_StartIndex + ((fl_Array_Size_u32 - fl_StartIndex) / 2);


		value = BLE_Frame_Details_St[fl_MidIndex].BLE_Frame_Id;
		if (value == Message_Id)
		{
			return fl_MidIndex;
		}

		if (value < Message_Id)
		{
			fl_StartIndex = fl_MidIndex + 1;
		}
		else
		{
			fl_Array_Size_u32 = fl_MidIndex - 1;
		}
	}

/* RETURN 0XFF VALUE NOT FOUND */
return 0xFF;
}

/*
 * @brief    THIS SHALL RETURN THE BLE CONNECTION STATUS - RETURN TRUE ONLY IF SYSTEM CONNECTED WITH PASSCODE
 * @param    void
 * @return   ble connection status
 * @invocation BLE_implementation
 */
uint8_t BLE_Get_Connection_Status(void)
{
    /* RETURN STATUS */
    return g_BLE_Connection_Status_u8;
}

void Passcode_return(void)
{
    Set_Event(LEFT_BUTTON_LONG_PRESS);
}

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0
    REVISION DATE        : 07/18/2022
    CREATED / REVISED BY : MOHAMED IBRAHIM M (ibrahim@niyatainfotech.com)
    DESCRIPTION          : Initial version
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! UART_DATAMANAGER_C */
