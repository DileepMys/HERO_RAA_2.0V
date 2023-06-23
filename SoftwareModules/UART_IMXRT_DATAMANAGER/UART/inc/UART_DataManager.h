/* @file FILE NAME */
#ifndef UART_DATAMANAGER_H
#define UART_DATAMANAGER_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : MOHAMED IBRAHIM M  (ibrahim@niyatainfotech.com)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : UART_DataManager.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : J link
*  Platforms supported             : Platform Independent                
*  Description                     : This header file contains the declarations of Uart Data manager.
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/**********************************************************************************************************************/
/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include "fsl_lpuart.h"
#include "UART_DataManager_Cfg.h"
#include "Cmp_Init.h"

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
 * @brief    This typedef enum is used to define the list of Data frames packet in the dashboard.
 * @param    Nil
 * @return   Nil
 **/
typedef enum{
    NAV_PKT = 0,
    STS_PKT,
    TIME_PKT,
    MISSED_CALL_PKT,
    SMS_NUM_PKT,
    CALL_STS_PKT,
    CALL_NUM_PKT,
    MUSIC_PKT,
    JOYSTICK_PKT,
    JOYSTICK_ACK_PKT,
    PASSCODE_PKT,
	MAX_PKT
}CONNECTIVITY_PKT_EN;


/*
 * @brief    This typedef enum is used to define the list of receiver data frame states.
 * @param    Nil
 * @return   Nil
 **/
typedef enum{
    WAIT_FOR_SOF =0u,
    WAIT_FOR_ID,
    WAIT_FOR_PAYLOAD,
    WAIT_FOR_DATA

}SET_RX_DATA_STATE_EN;


/*
 * @brief    This typedef enum is used to define the list of cluster passcode packet type states.
 * @param    Nil
 * @return   Nil
 **/
typedef struct 
{
    uint8_t StartOfFrame;
    uint8_t ID;
    uint8_t PASSCODE_NUM[6];
    uint8_t Ble_Status;    
    uint8_t EndOfFrame;
}CLUSTER_PASSCODE_PKT_TYPE_ST;


/*
 * @brief    This structure is used to define the Navigation packet details.
 * @param    Nil
 * @param    Nil
 **/
typedef struct 
{
	uint8_t StartOfFrame;
    uint8_t ID;
    uint8_t DIR_SYM;
    uint8_t DIST_TO_MANEUVER[5];
    uint8_t DIST_UNIT;
    uint8_t TIME_AND_UNIT[6];
    uint8_t EXIT[2];
    uint8_t NAV_STATUS;
    uint8_t REM_DIST[5];
    uint8_t REM_DIST_UNIT;
    uint8_t REM_TIME[4];
    uint8_t NXT_DIR_SYM;
    uint8_t EXIT_NXT_DIR_SYM[2];
    uint8_t ROAD_NAME[18];
    uint8_t EndOfFrame;
}HERO_SMARTPHONE_NAVIGATION_PKT_TYPE_ST;

/*
 * @brief    This structure is used to define the smartphone status packet details.
 * @param    Nil
 * @param    Nil
 **/
typedef struct 
{
    uint8_t StartOfFrame;
    uint8_t ID;
    uint8_t BATT_STATUS;
    uint8_t SIG_STR;
    uint8_t USER_NAME[18];
    uint8_t EndOfFrame;
}HERO_SMARTPHONE_STATUS_PKT_TYPE_ST;

/*
 * @brief    This structure is used to define the smartphone Time packet details.
 * @param    Nil
 * @param    Nil
 **/
typedef struct 
{
    uint8_t StartOfFrame;
    uint8_t ID;
    uint8_t SMRTPH_TIME[10];
    uint8_t EndOfFrame;
}HERO_SMARTPHONE_TIME_PKT_TYPE_ST;

/*
 * @brief    This structure is used to define the smartphone Missed Call packet details.
 * @param    Nil
 * @param    Nil
 **/
typedef struct 
{
    uint8_t StartOfFrame;
    uint8_t ID ;
    uint8_t SMRTPH_MISSED_CALLS[2];
    uint8_t EndOfFrame;

}HERO_SMARTPHONE_MISSED_CALL_PKT_TYPE_ST;

/*
 * @brief    This structure is used to define the smartphone SMS number packet details.
 * @param    Nil
 * @param    Nil
 **/
typedef struct 
{
    uint8_t StartOfFrame;
    uint8_t ID ;
    uint8_t NUMBER_SMS[2];
    uint8_t EndOfFrame;
}HERO_SMARTPHONE_SMS_NUMBER_PKT_TYPE_ST;

/*
 * @brief    This structure is used to define the smartphone Call Status packet details.
 * @param    Nil
 * @param    Nil
 **/
typedef struct
{
    uint8_t StartOfFrame;
    uint8_t ID;
    uint8_t CALLER_NUM_NAME_1[18];
    uint8_t CALL_STATUS_1;
    uint8_t CALLER_NUM_NAME_2[18];
    uint8_t CALL_STATUS_2;
    uint8_t CALL_DURATION[6];
    uint8_t PH_VOLUME;
    uint8_t EndOfFrame; 
}HERO_SMARTPHONE_CALL_STATUS_PKT_TYPE_ST;

/*
 * @brief    This structure is used to define the smartphone Call number packet details.
 * @param    Nil
 * @param    Nil
 **/

typedef struct
{
    uint8_t StartOfFrame;
    uint8_t ID;
    uint8_t CONTACT_1[18];
    uint8_t CONTACT_2[18];
    uint8_t CONTACT_3[18];
    uint8_t CONTACT_4[18];
    uint8_t CONTACT_5[18];
    uint8_t EndOfFrame; 
}HERO_SMARTPHONE_CALL_NUMBER_PKT_TYPE_ST;

/*
 * @brief    This structure is used to define the smartphone Music packet details.
 * @param    Nil
 * @param    Nil
 **/
typedef struct
{
    uint8_t StartOfFrame;
    uint8_t ID;
    uint8_t MUSIC_META_DATA_1[20];
    uint8_t MUSIC_META_DATA_2[20];
    uint8_t MUSIC_META_DATA_2_CFG;
    uint8_t MUSIC_ACT_STATUS;
    uint8_t PLYBCK_STATE;
    uint8_t ELAPSED_TIME;
    uint8_t MUSIC_VOLUME;
    uint8_t EndOfFrame; 
}HERO_SMARTPHONE_MUSIC_PKT_TYPE_ST;

/*
 * @brief    This structure is used to define the Cluster Joystick packet details.
 * @param    Nil
 * @param    Nil
 **/
typedef struct
{
    uint8_t StartOfFrame;
    uint8_t ID;
    uint8_t JOYSTICK_EVENT;
    uint8_t MUSIC_META_DATA_2_CL_INFO;
    uint8_t CONTACT_INDEX;
    uint8_t EndOfFrame; 
}HERO_CLUSTER_JOYSTICK_PKT_TYPE_ST;

/*
 * @brief    This structure is used to define the smartphone joystick ack packet details.
 * @param    Nil
 * @param    Nil   
 **/
typedef struct
{
    uint8_t StartOfFrame;
    uint8_t ID;
    uint8_t JOYSTICK_EVENT_ACK;
    uint8_t MUSIC_META_DATA_2_CL_INFO_ACK;
    uint8_t CONTACT_INDEX;
    uint8_t EndOfFrame; 
}HERO_SMARTPHONE_JOYSTICK_ACK_PKT_TYPE_ST;

/*
 * @brief    This structure is used to define the receive data structure details .
 * @param    Nil
 * @param    Nil    
 **/
typedef struct 
{
   uint8_t RX_Buffer[MAX_RX_DATA_SIZE];
   uint8_t RX_Data_Counter;
   uint8_t RX_Timeout_Time;
}UART_RX_DATA_TYPE_ST;

/*
 * @brief    This structure is used to define the UART frame information type.
 * @param    Nil
 * @param    Nil    
 **/
typedef struct
{
    uint8_t UART_Frame_Length;
}UART_FRAME_INFO_TYPE_ST;

/*
 * @brief    This structure is used to define the number of event type in the cluster.
 * @param    Nil
 * @param    Nil    
 **/
typedef struct {
    EVENT_TYPE_EN Event_Type;
    uint8_t Joystick_Data;    
}Cluster_Event_Type_St;


/*
 * @brief    This structure is used to define the receive data structure details .
 * @param    Nil
 * @param    Nil    
 **/
typedef union 
{
    HERO_SMARTPHONE_NAVIGATION_PKT_TYPE_ST   Hero_SmartPhone_Navigation_Pkt_St;
    HERO_SMARTPHONE_STATUS_PKT_TYPE_ST       Hero_SmartPhone_Status_Pkt_St;
    HERO_SMARTPHONE_TIME_PKT_TYPE_ST         Hero_SmartPhone_Time_Pkt_St;
    HERO_SMARTPHONE_MISSED_CALL_PKT_TYPE_ST  Hero_SmartPhone_Missed_Call_Pkt_St;
    HERO_SMARTPHONE_SMS_NUMBER_PKT_TYPE_ST   Hero_SmartPhone_Sms_Number_Pkt_St;
    HERO_SMARTPHONE_CALL_STATUS_PKT_TYPE_ST  Hero_SmartPhone_Call_Status_Pkt_St;
    HERO_SMARTPHONE_CALL_NUMBER_PKT_TYPE_ST  Hero_SmarPhone_Call_Number_Pkt_St;
    HERO_SMARTPHONE_MUSIC_PKT_TYPE_ST        Hero_SmartPhone_Music_Pkt_St;
    HERO_SMARTPHONE_JOYSTICK_ACK_PKT_TYPE_ST Hero_SmartPhone_Joystick_Ack_Pkt_St;
    CLUSTER_PASSCODE_PKT_TYPE_ST             Cluster_Passcode_Pkt_st;
    
}UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST;

/*
 * @brief    This structure is used to define the receive UART data manager cluster packet structure details .
 * @param    Nil
 * @param    Nil    
 **/
typedef struct
{
    HERO_CLUSTER_JOYSTICK_PKT_TYPE_ST        Hero_Cluster_Joystick_Pkt_St;
}UART_DATA_MGR_CLUSTER_PKT_TYPE_ST;

typedef void(*UARTEventCallBackTypeFn) (void);

/*
 * @brief    This structure is used to define the receive UART data manager cluster packet structure details .
 * @param    Nil
 * @param    Nil    
 **/
typedef struct
{
    uint32_t TimerElapseValue;
    uint32_t CrntValue;
    uint8_t FrameActiveSts;
    UARTEventCallBackTypeFn UARTEventCallBackFn;
}UARTFrameTimeoutStatusTypeSt;


/*
 * @brief    This structure is used to define the receive UART data manager cluster packet structure details .
 * @param    Nil
 * @param    Nil    
 **/
typedef struct
{
    uint8_t BLE_Frame_Id;
}BLE_Frame_Details_Type_St;



#define TASK_PERIOD     10

#define UART_FRAME_TIMEOUT  (20 / TASK_PERIOD)

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to initialize the init variables with its defaukt values.
* @param    NA
* @return   NA
* @invocation BLE_implementation
*/
void UART_DataManager_Init(void);
/*
* @brief    This API is used to reset the init variables.
* @param    NA
* @return   NA
* @invocation BLE_implementation
*/
void UART_DataManager_DeInit(void);
/*
* @brief    This API is used to initialize the peripherals
* @param    NA
* @return   NA
* @invocation BLE_implementation
*/
void UART_DataManager_Activate(void);
/*
* @brief    This API is used to reset the peripherals
* @param    NA
* @return   NA
* @invocation BLE_implementation
*/
void UART_DataManager_DeActivate(void);
/*
* @brief    This API is used to execute the UART manager activity
* @param    Nil
* @return   Nil
* @invocation  BLE_implementation
*/
void UART_DataManager_MainFunction(void);
/*
* @brief    This API is used to set the received data in UART datamanager
* @param    Nil
* @return   Nil
* @invocation BLE_implementation
*/
void UART_DataManager_Set_Rx_Data(void);

/*
* @brief    This API is used to get connectivity information from UART data manager
* @param    fl_Connectivity_Pkt_En
* @return   UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST
* @invocation BLE_implementation
*/
UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST UART_DataManager_Get_Connectivity_Info(CONNECTIVITY_PKT_EN fl_Connectivity_Pkt_En);

/*
* @brief    This API is used to set connectivity information from UART data manager
* @param    fl_Event_En
* @return   Nil
* @invocation BLE_implementation
*/
void UART_DataManager_Set_Connectivity_Info(Cluster_Joystick_Info_En fl_Event_En);

/*
* @brief    This API is used to get data frames from UART datamanager
* @param    *Data_Ptr
* @return   Nil
* @invocation BLE_implementation
*/
void UART_DataManager_Frame_Data(uint8_t* Data_Ptr);

/*
* @brief    This API is used to clear the pin information from UART data manager
* @param    NA
* @return   NA
* @invocation BLE_implementation
*/
void  UART_DataManager_Clear_pin_Info(void);

/*
* @brief    This API is used to set connectivity information from UART data manager
* @param    fl_Event_En
* @return   Nil
* @invocation BLE_implementation
*/
void Memory_Copy(uint8_t* destination, const uint8_t* source, uint16_t (size));

/*
* @brief		This function shall return the frame index from the frame details
* @param		Message_Id - message id which was populated in the frame 
* @return	index value in the table
*/
uint8_t Get_Message_Index(uint8_t Message_Id);

uint8_t BLE_Get_Connection_Status(void);

void Passcode_return(void);
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                                                
    REVISION DATE        : 07/18/2022                              
    CREATED / REVISED BY : MOHAMED IBRAHIM M (ibrahim@niyatainfotech.com)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! UART_DATAMANAGER_H */
