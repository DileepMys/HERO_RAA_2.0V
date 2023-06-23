/* @file FILE NAME */
#ifndef UART_DATAMANAGER_CFG_H
#define UART_DATAMANAGER_CFG_H

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
*  File name                       : UART_DataManager_Cfg.h
*  Version                         : v1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : J Link
*  Platforms supported             : Platform Independent
*  Description                     : This file contains the configuration declarations of Uart_DataManager.
*  @bug                            : 
*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/**********************************************************************************************************************/
/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S 
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                    C O N F I G U R A T I O N     M A C R O S                      
***********************************************************************************************************************/
/*
* @brief: This macro is used to configure the UART CHANNEL PORT 
*/
#define UART_CHANNEL              LPUART10
/*
* @brief: This macro is used to configure the Max Receiving Size of Data
*/
#define MAX_RX_DATA_SIZE          93
/*
* @brief: This macro is used to configure the Task Rate of Uart Manager in millisecs
*/
#define UART_DATAMGR_TASK_RATE    10
/*
* @brief: This macro is used to configure the UART Data Counter - this being kept as 10seconds
*/
#define UART_TIMEOUT_COUNTER_MAX     (20000/UART_DATAMGR_TASK_RATE)
/*
 * @brief    This typedef enum is used to define the Joystick task events.
 * @param    Nil
 * @return   Nil
 **/
typedef enum{
    No_Action=0u,
    Call_Accept,
    Call_Reject,
    Second_Call_Accepted_Decline_1st_Call,
    Second_Call_Accepted_holding_1st_Call,
    Second_Call_Declined,
    Play_Pause,
    Next_Track,
    Previous_Track,
    Mute,
    Phone_Volume_increase,
    Phone_Volume_Decrease,
    Music_Volume_Increase,
    Music_Volume_Decrease,
    Call_End,
    Album,
    Artist,
    Genre,
    Contact_0,
    Contact_1,
    Contact_2,
    Contact_3,
    Contact_4,
    Contact_5,
    Max_Joystick_Event
}Cluster_Joystick_Info_En;

/*
 * @brief    This typedef enum is used to define the list of event types
 * @param    Nil
 * @return   Nil
 **/
typedef enum{
    JOYSTICK_EVENT,
    MUSIC_META_DATA_2,
    CONTACT_INDEX
}EVENT_TYPE_EN;
/***********************************************************************************************************************
*                             C O N F I G U R A T I O N    C O N S T A N T S    D E C L A R A T I O N                       
***********************************************************************************************************************/


/***********************************************************************************************************************
*                            C O N F I G U R A T I O N    V A R I A B L E S    D E C L A R A T I O N                  
***********************************************************************************************************************/

/*********************************************************************************************************************
*                         C O N F I G U R A T I O N     F U N C T I O N    D E C L A R A T I O N S                      
*********************************************************************************************************************/

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                                                
    REVISION DATE        : 07/18/2022                              
    CREATED / REVISED BY : MOHAMED IBRAHIM M (ibrahim@niyatainfotech.com)   
    DESCRIPTION          : Initial version                              
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! UART_DATAMANAGER_CFG_H */
