/*********************************************************************************************************************** 
  *    DISCLAIMER                                                                                                        
  *    Copyright (C) 2011, 2016 Niyata Infotech Ptv. Ltd. All rights reserved.                                              
  ***********************************************************************************************************************/

/***********************************************************************************************************************
  * @author              Author : Mahendran L (mahendranl@niyatainfotech.com)                                                                         
***********************************************************************************************************************/
/***********************************************************************************************************************
  *                                                F I L E  D E S C R I P T I O N                                           
  *---------------------------------------------------------------------------------------------------------------------
*  @brief                                                                                                             
 * 
*  File name                       : CanMgr_cfg.c                                                                         
*  Version                         : v4.3.20   
*  Micros supported                : Micro Agnostic (Independant)     
*  Compilers supported             : XXXX                                                                           
*  Platforms supported             : XXXX                                                                            
*  Description            		 : This file contains functions definitions of CanMgr                                                                          
*
*
*
* @bug
  *---------------------------------------------------------------------------------------------------------------------*/
/**********************************************************************************************************************/
/* ====================================================================================================================
*                          I N C L U D E   F I L E S
* ===================================================================================================================*/
/**********************************************************************************************************************/


#ifndef CANMGR_CFG_H_
#define CANMGR_CFG_H_

#include "CanMgr_Types.h"
#include "hal_stdtypes.h"
#include "Swc_TT_Mil_Tft.h"
#include "Abs_Telltale.h"
#include "Swc_Speedometer_Cfg.h"
#include "SWC_Gear_position.h"
#include "Swc_Tachometer.h"
#include "TC.h"
#include "Side_Stand_TT.h"
#include "CanMgr.h"

#define CANMGR_ON_CHANGE_RECEPTION_CALLBACK  STD_ON
#define CANMGR_WAKEUP_INDICATION   STD_OFF
#define CANMGR_PERIODIC_MESSAGE_TRANSMISSION  STD_ON
#define CANMGR_MESSAGE_MISSING_CALLBACK  STD_ON
#define CANMGR_CANTP_FUNCTIONS  STD_ON
/*Enable or Disable the Functional Safety Function*/
#define CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS    STD_OFF


/**Reception data Callback function mapping table*/



#define CANMGR_DIAGNOSTIC_ANSWER_ABS_0X629_S_RXCBK     NULL
#define CANMGR_REQ_DIAG_ANS_IC_0X632_S_RXCBK     NULL
#define CANMGR_DIAGNOSTIC_ANSWER_TCU_0X641_S_RXCBK     NULL
#define CANMGR_DIAGNOSTIC_ANSWER_IC_0X642_S_RXCBK     NULL
#define CANMGR_DIAGNOSTIC_ANSWER_BCM_0X644_S_RXCBK     NULL
#define CANMGR_DIAGNOSTIC_ANSWER_ECM_0X7E8_S_RXCBK     NULL
#define CANMGR_ENGINE_SPEED_0X130_S_RXCBK           &CanMgr_Tacho_reception_cbk
#define CANMGR_ENGINE_RUN_STATUS_0X130_S_RXCBK     NULL
#define CANMGR_THROTTLE_POSITION_SENSOR_0X130_S_RXCBK     NULL
#define CANMGR_THROTTLE_POSITION_SENSOR_FAULT_0X130_S_RXCBK     NULL
#define CANMGR_REMOTE_MOBILIZE_IMMOBLIZE_STATUS_0X130_S_RXCBK     NULL
#define CANMGR_MIL_0X130_S_RXCBK                      &CanMgr_MIL_reception_cbk
#define CANMGR_ABS_CRC_TRQ_0X142_S_RXCBK      NULL
#define CANMGR_ALIVE_COUNTER_ABS_TRQ_0X142_S_RXCBK     NULL
#define CANMGR_TORQUE_REQUEST_STATUS_0X142_S_RXCBK     NULL
#define CANMGR_TC_TELLTALE_STATUS_0X142_S_RXCBK     NULL
#define CANMGR_TRQ_REQ_MTC_0X142_S_RXCBK     NULL
#define CANMGR_TRQ_REQ_DTC_0X142_S_RXCBK     NULL
#define CANMGR_ALIVE_COUNTER_ECM_SENSOR_0X131_S_RXCBK     NULL
#define CANMGR_ECM_CRC_SENSOR_0X131_S_RXCBK     NULL
#define CANMGR_ROLL_OVER_DETECTION_0X131_S_RXCBK     NULL
#define CANMGR_ROLL_OVER_DETECTION_FAULT_STATUS_0X131_S_RXCBK     NULL
#define CANMGR_SIDE_STAND_SENSOR_0X131_S_RXCBK     &CanMgr_SideStand_Telltale_reception_cbk
#define CANMGR_SIDE_STAND_SENSOR_FAULT_0X131_S_RXCBK     &CanMgr_SideStand_Sensor_Fault_reception_cbk
#define CANMGR_GEAR_POSITION_SENSOR_0X131_S_RXCBK       &CanMgr_Gear_Position_reception_cbk
#define CANMGR_GEAR_SHIFT_ADVISORY_0X131_S_RXCBK     &CanMgr_Gear_Shift_reception_cbk
#define CANMGR_ENGINE_KILL_SWITCH_STATUS_0X131_S_RXCBK     NULL
#define CANMGR_THROTTLE_GRIP_SENSOR_0X131_S_RXCBK     NULL
#define CANMGR_STATUS_ABS_0X205_S_RXCBK     NULL
#define CANMGR_ABS_TELLTALE_STATUS_0X205_S_RXCBK     &CanMgr_Abs_reception_cbk
#define CANMGR_VEHICLE_SPEED_0X206_S_RXCBK     &CanMgr_Speedo_reception_cbk
#define CANMGR_DISTANCE_TRAVELLED_WITH_MIL_0X135_S_RXCBK     NULL
#define CANMGR_ACCUMULAT_FUEL_INJ_TIME_FUEL_QTY_0X135_S_RXCBK   &CanMgr_TC_reception_cbk  

#define CANMGR_REQ_DIAG_ANS_TCU_0X631_S_RXCBK     NULL
#define CANMGR_REQ_DIAG_ANS_IC_0X632_S_RXCBK     NULL
#define CANMGR_REQ_DIAG_ANS_ABS_0X6F0_S_RXCBK     NULL
#define CANMGR_REQ_DIAG_ANS_BCM_0X6F1_S_RXCBK     NULL
#define CANMGR_FUNCTIONAL_DIAGNOSTIC_REQUEST_0X7DF_S_RXCBK     NULL
#define CANMGR_REQ_DIAG_ANS_ECM_0X7E0_S_RXCBK     NULL




/*Reception timeout Callback function mapping table*/

#define CANMGR_DIAGNOSTIC_ANSWER_ABS_0X629_S_TIMEOUT_CBK       NULL
#define CANMGR_REQ_DIAG_ANS_IC_0X632_S_TIMEOUT_CBK       NULL
#define CANMGR_DIAGNOSTIC_ANSWER_TCU_0X641_S_TIMEOUT_CBK       NULL
#define CANMGR_DIAGNOSTIC_ANSWER_IC_0X642_S_TIMEOUT_CBK       NULL
#define CANMGR_DIAGNOSTIC_ANSWER_BCM_0X644_S_TIMEOUT_CBK       NULL
#define CANMGR_DIAGNOSTIC_ANSWER_ECM_0X7E8_S_TIMEOUT_CBK       NULL
#define CANMGR_ENGINE_SPEED_0X130_S_TIMEOUT_CBK       &CanMgr_Tacho_Timeout_Callback_0x130
#define CANMGR_ENGINE_RUN_STATUS_0X130_S_TIMEOUT_CBK       NULL
#define CANMGR_THROTTLE_POSITION_SENSOR_0X130_S_TIMEOUT_CBK       NULL
#define CANMGR_THROTTLE_POSITION_SENSOR_FAULT_0X130_S_TIMEOUT_CBK       NULL
#define CANMGR_REMOTE_MOBILIZE_IMMOBLIZE_STATUS_0X130_S_TIMEOUT_CBK       NULL
#define CANMGR_MIL_0X130_S_TIMEOUT_CBK       &CanMgr_MIL_Timeout_Callback_0x130
#define CANMGR_ABS_CRC_TRQ_0X142_S_TIMEOUT_CBK       NULL
#define CANMGR_ALIVE_COUNTER_ABS_TRQ_0X142_S_TIMEOUT_CBK       NULL
#define CANMGR_TORQUE_REQUEST_STATUS_0X142_S_TIMEOUT_CBK       NULL
#define CANMGR_TC_TELLTALE_STATUS_0X142_S_TIMEOUT_CBK       NULL
#define CANMGR_TRQ_REQ_MTC_0X142_S_TIMEOUT_CBK       NULL
#define CANMGR_TRQ_REQ_DTC_0X142_S_TIMEOUT_CBK       NULL
#define CANMGR_ALIVE_COUNTER_ECM_SENSOR_0X131_S_TIMEOUT_CBK       NULL
#define CANMGR_ECM_CRC_SENSOR_0X131_S_TIMEOUT_CBK       NULL
#define CANMGR_ROLL_OVER_DETECTION_0X131_S_TIMEOUT_CBK       NULL
#define CANMGR_ROLL_OVER_DETECTION_FAULT_STATUS_0X131_S_TIMEOUT_CBK       NULL
#define CANMGR_SIDE_STAND_SENSOR_0X131_S_TIMEOUT_CBK       &CanMgr_SideStand_Telltale_Timeout_Callback_0x131
#define CANMGR_SIDE_STAND_SENSOR_FAULT_0X131_S_TIMEOUT_CBK       &CanMgr_SideStand_Sensor_Fault_Timeout_Callback_0x131
#define CANMGR_GEAR_POSITION_SENSOR_0X131_S_TIMEOUT_CBK       &CanMgr_Gear_Timeout_Callback_0x130
#define CANMGR_GEAR_SHIFT_ADVISORY_0X131_S_TIMEOUT_CBK       &CanMgr_GearShift_Timeout_Callback_0x130
#define CANMGR_ENGINE_KILL_SWITCH_STATUS_0X131_S_TIMEOUT_CBK       NULL
#define CANMGR_THROTTLE_GRIP_SENSOR_0X131_S_TIMEOUT_CBK       NULL
#define CANMGR_STATUS_ABS_0X205_S_TIMEOUT_CBK       NULL
#define CANMGR_ABS_TELLTALE_STATUS_0X205_S_TIMEOUT_CBK       &CanMgr_ABS_Timeout_Callback_0x205
#define CANMGR_VEHICLE_SPEED_0X206_S_TIMEOUT_CBK       &CanMgr_Speedo_Timeout_Callback_0x206
#define CANMGR_DISTANCE_TRAVELLED_WITH_MIL_0X135_S_TIMEOUT_CBK       NULL
#define CANMGR_ACCUMULAT_FUEL_INJ_TIME_FUEL_QTY_0X135_S_TIMEOUT_CBK       &ECM_ADDITION_INFO_Timeout_Callback_0x135

#define CANMGR_REQ_DIAG_ANS_TCU_0X631_S_TIMEOUT_CBK       NULL
#define CANMGR_REQ_DIAG_ANS_IC_0X632_S_TIMEOUT_CBK       NULL
#define CANMGR_REQ_DIAG_ANS_ABS_0X6F0_S_TIMEOUT_CBK       NULL
#define CANMGR_REQ_DIAG_ANS_BCM_0X6F1_S_TIMEOUT_CBK       NULL
#define CANMGR_FUNCTIONAL_DIAGNOSTIC_REQUEST_0X7DF_S_TIMEOUT_CBK       NULL
#define CANMGR_REQ_DIAG_ANS_ECM_0X7E0_S_TIMEOUT_CBK       NULL






/*Remote wakeup callback function*/
#define APPLICATION_WAKEUP_CBK(x)   Can_Bus_WakeUp_Notification(x) 
/*Network request confirmation callback function*/
#define APPLICATION_NETWORK_REQUEST_CBK_FUNC(channel,NetworkRequest_Result) NULL
/*Bus off indication callback function*/
#define APPLICATION_BUSOFF_INDICATION(x) App_Can_bus_off_indication(x)
/*Error Service Call back Function
Error value mention which error indicated Passive Error =0x20,Ewarn Error = 0x40, & Parity Bit Error = 0x100 */
#define APPLICATION_ERRORSTATE_INDICATION(x,y)  NULL

/*Check the functional safety macro enable or Disable*/
#if CAN_MGR_FUNCTIONAL_SAFETY_FUNCTIONS==STD_ON
 /*call the control flow status function*/
#define  CAN_CONTROL_FLOW_STATUS(x)     NULL
#endif

#define INIT_DATA_VALUE    &Init_data_value[0][0]

/*Enable or Disable the Maximum signal value validation for Channel1*/
#define CHANNEL1_MAX_SIGNAL_VALIDATION      STD_ON
/*Enable or Disable the Minimum signal value validation for Channel1*/
#define CHANNEL1_MIN_SIGNAL_VALIDATION      STD_ON
/*Enable or Disable the Maximum signal value validation for Channel2*/
#define CHANNEL2_MAX_SIGNAL_VALIDATION      STD_ON
/*Enable or Disable the Minimum signal value validation for Channel2*/
#define CHANNEL2_MIN_SIGNAL_VALIDATION      STD_ON


/*CAN Manager mainfuncion periodicity*/
#define CANMGR_MAINFUNCTION_PERIOD       100


/*Maximum number of RX signals*/
#define MAX_RX_SIGNALS        39u


/*
 * @brief: This macro defines whether Checksum feature is Enabled or Disabled for both channel
 * @param: STD_ON : The service shall be enabled
 *         STD_OFF: The service shall be disabled
 * @Unit:  N/A
 * @Resolution: N/A
 * */

#define CHECKSUM_FEATURE_GLOBAL          STD_ON

/*
 * @brief: This macro defines whether Alive counter feature is Enabled or Disabled for both channel
 * @param: STD_ON : The service shall be enabled
 *         STD_OFF: The service shall be disabled
 * @Unit:  N/A
 * @Resolution: N/A
 * */

#define ALIVE_COUNTER_FEATURE_GLOBAL      STD_ON

/**********************************************************************************************************************
 * CAN_TOTAL_NUMBER_OF_CHANNELS - Number of CAN Channels
 **********************************************************************************************************************
 * @brief           Total Number of CAN channels used
 * @param           Only One channel is supported
 * @ValidCheck      NO
 * @Required        YES
 */

#define CAN_TOTAL_NUMBER_OF_CHANNELS    2U


#if(CHECKSUM_FEATURE_GLOBAL == STD_ON )
/*Checksum error indication callback function*/

#define CHECKSUM_ERROR_CALLBACK(x, y)                              &canMgr_SideStand_Sensor_CRC_ERROR_indication_callback

/*Checksum error recovery indication callback function*/
#define CHECKSUM_ERROR_RECOVERY_CALLBACK(x, y)                     &canMgr_SideStand_Sensor_CRC_recovery_indication_callback
#endif

#if(ALIVE_COUNTER_FEATURE_GLOBAL == STD_ON )
/*Alive counter error indication callback function*/

#define ALIVE_COUNTER_ERROR_CALLBACK(x, y)                         &canMgr_SideStand_Sensor_Alive_Counter_Error_recovery_indication_callback

/*Alive counter error recovery indication callback function*/
#define ALIVE_COUNTER_ERROR_RECOVERY_CALLBACK(x, y)               &canMgr_SideStand_Sensor_Alive_Counter_recovery_indication_callback
#endif


/*TX messages in the network node*/
typedef enum
{
      IC_INFO_MSG_0X321=0u,
      REQ_DIAGN_ANS_TCU_0X631=1u,
      REQ_DIAGN_ANS_ABS_0X6F0=2u,
      REQ_DIAGN_ANS_BCM_0X6F1=3u,
      REQ_DIAGN_ANS_ECM_0X7E0=4u,
  //    IC_INFO_MSG_0X321=4u,
      DIAG_ANSW_ABS_0X629=5u,
      DIA_ANSW_TCU_0X641=6u,
      DIAG_ANSW_IC_0X642=7u,
      DIAG_ANSW_BCM_0X644=8u,
      DIAG_ANSW_ECM_0X7E8=9u,
       CANMGR_MAX_NO_OF_TX_MSGS =10u

}Tx_Msg_Id;




/*RX messages in the network node*/
typedef enum
{
  ECM_ENGINE_PARAMETER_0X130=0u,
  ECM_SENSOR_PARAMETER_0X131=1u,
  ECM_ADDITIONAL_INFO_0X135=2u,
  ABS_TRQ_REQ_0X142=3u,
  ABS_STATUS_0X205=4u,
  ABS_VEHICLE_SPEED_0X206=5u,
  DIAG_ANS_ABS_0X629=6u,
  REQ_DIAG_ANSW_IC_0X632=7u,
  DIAG_ANSW_TCU_0X641=8u,
  DIAG_ANS_IC_0X642=9u,
  DIAG_ANS_BCM_0X644=10u,
  DIAG_ANS_ECM_0X7E8=11u,
  REQ_DIAG_ANSW_TCU_0X631=12u,
  REQ_DIAG_ANS_IC_0X632=13u,
  REQ_DIAG_ANSW_ABS_0X6F0=14u,
  REQ_DIAG_ANSW_BCM_0X6F1=15u,
  FUNCTIONAL_DIAG_REQUEST_0X7DF=16u,
  REQ_DIAG_ANSW_ECM_0X7E0=17u,
  CANMGR_MAX_NO_OF_RX_MSGS= 18u
}Rx_Msg_Id;



/*TX messages indentifier*/
typedef enum
{
      REQ_DIAGN_ANS_TCU_0X631_FRAME_ID = (0x631),
      REQ_DIAGN_ANS_ABS_0X6F0_FRAME_ID = (0x6f0),
      REQ_DIAGN_ANS_BCM_0X6F1_FRAME_ID = (0x6f1),
      REQ_DIAGN_ANS_ECM_0X7E0_FRAME_ID = (0x7e0),
      IC_INFO_MSG_0X321_FRAME_ID = (0x321),
      DIAG_ANSW_ABS_0X629_FRAME_ID = (0x629),
      DIA_ANSW_TCU_0X641_FRAME_ID = (0x641),
      DIAG_ANSW_IC_0X642_FRAME_ID = (0x642),
      DIAG_ANSW_BCM_0X644_FRAME_ID = (0x644),
      DIAG_ANSW_ECM_0X7E8_FRAME_ID = (0x7e8)


}Tx_Mxg_Frame_Id;


/*RX messages indentifier*/
typedef enum
{
      DIAG_ANS_ABS_0X629_FRAME_ID = (0x629),
      REQ_DIAG_ANS_IC_0X632_FRAME_ID = (0x632),
      DIAG_ANSW_TCU_0X641_FRAME_ID = (0x641),
      DIAG_ANS_IC_0X642_FRAME_ID = (0x642),
      DIAG_ANS_BCM_0X644_FRAME_ID = (0x644),
      DIAG_ANS_ECM_0X7E8_FRAME_ID = (0x7e8),
      ECM_ENGINE_PARAMETER_0X130_FRAME_ID = (0x130),
      ABS_TRQ_REQ_0X142_FRAME_ID = (0x142),
      ECM_SENSOR_PARAMETER_0X131_FRAME_ID = (0x131),
      ABS_STATUS_0X205_FRAME_ID = (0x205),
      ABS_VEHICLE_SPEED_0X206_FRAME_ID = (0x206),
      ECM_ADDITIONAL_INFO_0X135_FRAME_ID = (0x135),
      REQ_DIAG_ANSW_TCU_0X631_FRAME_ID = (0x631),
      REQ_DIAG_ANSW_IC_0X632_FRAME_ID = (0x632),
      REQ_DIAG_ANSW_ABS_0X6F0_FRAME_ID = (0x6f0),
      REQ_DIAG_ANSW_BCM_0X6F1_FRAME_ID = (0x6f1),
      FUNCTIONAL_DIAG_REQUEST_0X7DF_FRAME_ID = (0x7df),
      REQ_DIAG_ANSW_ECM_0X7E0_FRAME_ID = (0x7e0)


}Rx_Mxg_Frame_Id;

/* Tx Frame lengths in bytes. */


typedef enum
{
      REQ_DIAGN_ANS_TCU_0X631_LENGTH = (8u),
      REQ_DIAGN_ANS_ABS_0X6F0_LENGTH = (8u),
      REQ_DIAGN_ANS_BCM_0X6F1_LENGTH = (8u),
      REQ_DIAGN_ANS_ECM_0X7E0_LENGTH = (8u),
      IC_INFO_MSG_0X321_LENGTH = (8u),
      DIAG_ANSW_ABS_0X629_LENGTH = (8u),
      DIA_ANSW_TCU_0X641_LENGTH = (8u),
      DIAG_ANSW_IC_0X642_LENGTH = (8u),
      DIAG_ANSW_BCM_0X644_LENGTH = (8u),
      DIAG_ANSW_ECM_0X7E8_LENGTH = (8u)


}Tx_Mxg_Length;

/* Rx Frame lengths in bytes. */


typedef enum
{
      DIAG_ANS_ABS_0X629_LENGTH = (8u),
      REQ_DIAG_ANS_IC_0X632_LENGTH = (8u),
      DIAG_ANSW_TCU_0X641_LENGTH = (8u),
      DIAG_ANS_IC_0X642_LENGTH = (8u),
      DIAG_ANS_BCM_0X644_LENGTH = (8u),
      DIAG_ANS_ECM_0X7E8_LENGTH = (8u),
      ECM_ENGINE_PARAMETER_0X130_LENGTH = (8u),
      ABS_TRQ_REQ_0X142_LENGTH = (8u),
      ECM_SENSOR_PARAMETER_0X131_LENGTH = (8u),
      ABS_STATUS_0X205_LENGTH = (8u),
      ABS_VEHICLE_SPEED_0X206_LENGTH = (8u),
      ECM_ADDITIONAL_INFO_0X135_LENGTH = (8u),
      REQ_DIAG_ANSW_TCU_0X631_LENGTH = (8u),
      REQ_DIAG_ANSW_IC_0X632_LENGTH = (8u),
      REQ_DIAG_ANSW_ABS_0X6F0_LENGTH = (8u),
      REQ_DIAG_ANSW_BCM_0X6F1_LENGTH = (8u),
      FUNCTIONAL_DIAG_REQUEST_0X7DF_LENGTH = (8u),
      REQ_DIAG_ANSW_ECM_0X7E0_LENGTH = (8u)


}Rx_Mxg_Length;

/* Tx CLC Time. */


typedef enum
{
      REQ_DIAGN_ANS_TCU_0X631_CLC_TIME = (0u),
      REQ_DIAGN_ANS_ABS_0X6F0_CLC_TIME = (0u),
      REQ_DIAGN_ANS_BCM_0X6F1_CLC_TIME = (0u),
      REQ_DIAGN_ANS_ECM_0X7E0_CLC_TIME = (0u),
      IC_INFO_MSG_0X321_CLC_TIME = (100u),
      DIAG_ANSW_ABS_0X629_CLC_TIME = (0u),
      DIA_ANSW_TCU_0X641_CLC_TIME = (0u),
      DIAG_ANSW_IC_0X642_CLC_TIME = (0u),
      DIAG_ANSW_BCM_0X644_CLC_TIME = (0u),
      DIAG_ANSW_ECM_0X7E8_CLC_TIME = (0u)


}Tx_Message_cycle_time;

/* Tx CLC fast Time. */


typedef enum
{
      REQ_DIAGN_ANS_TCU_0X631_CLC_TIME_FAST = (0u),
      REQ_DIAGN_ANS_ABS_0X6F0_CLC_TIME_FAST = (0u),
      REQ_DIAGN_ANS_BCM_0X6F1_CLC_TIME_FAST = (0u),
      REQ_DIAGN_ANS_ECM_0X7E0_CLC_TIME_FAST = (0u),
      IC_INFO_MSG_0X321_CLC_TIME_FAST = (100u),
      DIAG_ANSW_ABS_0X629_CLC_TIME_FAST = (0u),
      DIA_ANSW_TCU_0X641_CLC_TIME_FAST = (0u),
      DIAG_ANSW_IC_0X642_CLC_TIME_FAST = (0u),
      DIAG_ANSW_BCM_0X644_CLC_TIME_FAST = (0u),
      DIAG_ANSW_ECM_0X7E8_CLC_TIME_FAST = (0u)


}Tx_Message_FastCycleTime;

/* Rx CLC Time. */


typedef enum
{
      DIAG_ANS_ABS_0X629_CLC_TIME = (0u),
      REQ_DIAG_ANS_IC_0X632_CLC_TIME = (0u),
      DIAG_ANSW_TCU_0X641_CLC_TIME = (0u),
      DIAG_ANS_IC_0X642_CLC_TIME = (0u),
      DIAG_ANS_BCM_0X644_CLC_TIME = (0u),
      DIAG_ANS_ECM_0X7E8_CLC_TIME = (0u),
      ECM_ENGINE_PARAMETER_0X130_CLC_TIME = (10u),
      ABS_TRQ_REQ_0X142_CLC_TIME = (10u),
      ECM_SENSOR_PARAMETER_0X131_CLC_TIME = (50u),
      ABS_STATUS_0X205_CLC_TIME = (50u),
      ABS_VEHICLE_SPEED_0X206_CLC_TIME = (100u),
      ECM_ADDITIONAL_INFO_0X135_CLC_TIME = (200u),
      REQ_DIAG_ANSW_TCU_0X631_CLC_TIME = (0u),
      REQ_DIAG_ANSW_IC_0X632_CLC_TIME = (0u),
      REQ_DIAG_ANSW_ABS_0X6F0_CLC_TIME = (0u),
      REQ_DIAG_ANSW_BCM_0X6F1_CLC_TIME = (0u),
      FUNCTIONAL_DIAG_REQUEST_0X7DF_CLC_TIME = (0u),
      REQ_DIAG_ANSW_ECM_0X7E0_CLC_TIME = (0u)


}Rx_Message_cycle_time;

/* Extended or standard frame types.. */


typedef enum
{
      REQ_DIAGN_ANS_TCU_0X631_IS_EXTENDED = 1,
      REQ_DIAGN_ANS_ABS_0X6F0_IS_EXTENDED = 1,
      REQ_DIAGN_ANS_BCM_0X6F1_IS_EXTENDED = 1,
      REQ_DIAGN_ANS_ECM_0X7E0_IS_EXTENDED = 1,
      IC_INFO_MSG_0X321_IS_EXTENDED = 1,
      DIAG_ANSW_ABS_0X629_IS_EXTENDED = 1,
      DIA_ANSW_TCU_0X641_IS_EXTENDED = 1,
      DIAG_ANSW_IC_0X642_IS_EXTENDED = 1,
      DIAG_ANSW_BCM_0X644_IS_EXTENDED = 1,
      DIAG_ANSW_ECM_0X7E8_IS_EXTENDED = 1


}Tx_Msg_Identifier_Type;

typedef enum
{
      DIAG_ANS_ABS_0X629_IS_EXTENDED = 1,
      REQ_DIAG_ANS_IC_0X632_IS_EXTENDED = 1,
      DIAG_ANSW_TCU_0X641_IS_EXTENDED = 1,
      DIAG_ANS_IC_0X642_IS_EXTENDED = 1,
      DIAG_ANS_BCM_0X644_IS_EXTENDED = 1,
      DIAG_ANS_ECM_0X7E8_IS_EXTENDED = 1,
      ECM_ENGINE_PARAMETER_0X130_IS_EXTENDED = 1,
      ABS_TRQ_REQ_0X142_IS_EXTENDED = 1,
      ECM_SENSOR_PARAMETER_0X131_IS_EXTENDED = 1,
      ABS_STATUS_0X205_IS_EXTENDED = 1,
      ABS_VEHICLE_SPEED_0X206_IS_EXTENDED = 1,
      ECM_ADDITIONAL_INFO_0X135_IS_EXTENDED = 1,
      REQ_DIAG_ANSW_TCU_0X631_IS_EXTENDED = 1,
      REQ_DIAG_ANSW_IC_0X632_IS_EXTENDED = 1,
      REQ_DIAG_ANSW_ABS_0X6F0_IS_EXTENDED = 1,
      REQ_DIAG_ANSW_BCM_0X6F1_IS_EXTENDED = 1,
      FUNCTIONAL_DIAG_REQUEST_0X7DF_IS_EXTENDED = 1,
      REQ_DIAG_ANSW_ECM_0X7E0_IS_EXTENDED = 1


}Rx_Msg_Identifier_Type;

/* Tx Methods. */


typedef enum
{
      REQ_DIAGN_ANS_TCU_0X631_TX_METHOD = ONWRITE,
      REQ_DIAGN_ANS_ABS_0X6F0_TX_METHOD = ONWRITE,
      REQ_DIAGN_ANS_BCM_0X6F1_TX_METHOD = ONWRITE,
      REQ_DIAGN_ANS_ECM_0X7E0_TX_METHOD = ONWRITE,
      IC_INFO_MSG_0X321_TX_METHOD = CYCLIC,
      DIAG_ANSW_ABS_0X629_TX_METHOD = CYCLIC,
      DIA_ANSW_TCU_0X641_TX_METHOD = CYCLIC,
      DIAG_ANSW_IC_0X642_TX_METHOD = CYCLIC,
      DIAG_ANSW_BCM_0X644_TX_METHOD = CYCLIC,
      DIAG_ANSW_ECM_0X7E8_TX_METHOD = CYCLIC


}Tx_Msg_Method;

/* Enum to hold all the signals of all messages in an orderly manner. */


typedef enum
{
      REQ_DIAG_ANS_TCU_1_0X631_S = (uint16_t)0,
      REQ_DIAG_ANS_ABS_1_0X6F0_S,
      REQ_DIAG_ANS_BCM_1_0X6F1_S,
      REQ_DIAG_ANS_ECM_1_0X7E0_S,
      IC_CRC_INFO_0X321_S,
      ALIVE_COUNTER_IC_INFO_0X321_S,
      IC_SS_TELL_TELL_ERROR_0X321_S,
      IC_SS_TELL_TELL_STATUS_0X321_S,
      ODO_SIGNAL_0X321_S,
      AMBIANT_LIGHT_DATA_0X321_S,
      DIAGNOSTIC_ANSWER_ABS_0X629_S,
      DIAGNOSTIC_ANSWER_TCU_0X641_S,
      DIAGNOSTIC_ANSWER_IC_0X642_S,
      DIAGNOSTIC_ANSWER_BCM_0X644_S,
      DIAGNOSTIC_ANSWER_ECM_0X7E8_S,

      MAX_TX_SIGNALS
}Tx_Msg_SignalList;

/* Tx Signal Send type*/


typedef enum
{
      REQ_DIAG_ANS_TCU_1_0X631_S_SIGNAL_TX_METHODS = EVENT_SIGNAL,
      REQ_DIAG_ANS_ABS_1_0X6F0_S_SIGNAL_TX_METHODS = EVENT_SIGNAL,
      REQ_DIAG_ANS_BCM_1_0X6F1_S_SIGNAL_TX_METHODS = EVENT_SIGNAL,
      REQ_DIAG_ANS_ECM_1_0X7E0_S_SIGNAL_TX_METHODS = EVENT_SIGNAL,
      IC_CRC_INFO_0X321_S_SIGNAL_TX_METHODS = CYCLIC,
      ALIVE_COUNTER_IC_INFO_0X321_S_SIGNAL_TX_METHODS = CYCLIC,
      IC_SS_TELL_TELL_ERROR_0X321_S_SIGNAL_TX_METHODS = CYCLIC,
      IC_SS_TELL_TELL_STATUS_0X321_S_SIGNAL_TX_METHODS = CYCLIC,
      ODO_SIGNAL_0X321_S_SIGNAL_TX_METHODS = CYCLIC,
      AMBIANT_LIGHT_DATA_0X321_S_SIGNAL_TX_METHODS = CYCLIC,
      DIAGNOSTIC_ANSWER_ABS_0X629_S_SIGNAL_TX_METHODS = EVENT_SIGNAL,
      DIAGNOSTIC_ANSWER_TCU_0X641_S_SIGNAL_TX_METHODS = EVENT_SIGNAL,
      DIAGNOSTIC_ANSWER_IC_0X642_S_SIGNAL_TX_METHODS = EVENT_SIGNAL,
      DIAGNOSTIC_ANSWER_BCM_0X644_S_SIGNAL_TX_METHODS = EVENT_SIGNAL,
      DIAGNOSTIC_ANSWER_ECM_0X7E8_S_SIGNAL_TX_METHODS = EVENT_SIGNAL

}Tx_Signal_SendType;

/* Rx Methods. */


typedef enum
{
      DIAG_ANS_ABS_0X629_RX_METHOD = ONWRITE,
      REQ_DIAG_ANS_IC_0X632_RX_METHOD = ONWRITE,
      DIAG_ANSW_TCU_0X641_RX_METHOD = ONWRITE,
      DIAG_ANS_IC_0X642_RX_METHOD = ONWRITE,
      DIAG_ANS_BCM_0X644_RX_METHOD = ONWRITE,
      DIAG_ANS_ECM_0X7E8_RX_METHOD = ONWRITE,
      ECM_ENGINE_PARAMETER_0X130_RX_METHOD = CYCLIC,
      ABS_TRQ_REQ_0X142_RX_METHOD = CYCLIC,
      ECM_SENSOR_PARAMETER_0X131_RX_METHOD = CYCLIC,
      ABS_STATUS_0X205_RX_METHOD = CYCLIC,
      ABS_VEHICLE_SPEED_0X206_RX_METHOD = CYCLIC,
      ECM_ADDITIONAL_INFO_0X135_RX_METHOD = CYCLIC,
      REQ_DIAG_ANSW_TCU_0X631_RX_METHOD = CYCLIC,
      REQ_DIAG_ANSW_IC_0X632_RX_METHOD = CYCLIC,
      REQ_DIAG_ANSW_ABS_0X6F0_RX_METHOD = CYCLIC,
      REQ_DIAG_ANSW_BCM_0X6F1_RX_METHOD = CYCLIC,
      FUNCTIONAL_DIAG_REQUEST_0X7DF_RX_METHOD = CYCLIC,
      REQ_DIAG_ANSW_ECM_0X7E0_RX_METHOD = CYCLIC


}Rx_Msg_Method;


extern uint8_t Init_data_value[CANMGR_MAX_NO_OF_TX_MSGS][8];


typedef struct
{
  uint8_t channel;
  Tx_Msg_Method  frame_type;
  Tx_Message_cycle_time period;
  Tx_Message_FastCycleTime FastPeriodTime;
  Tx_Mxg_Length  length;
  uint16_t counter;
  uint8_t checksum_enable;
  uint8_t alive_counter_enable;
  uint8_t alive_counter_rollback_min_val;
  uint8_t alive_counter_rollback_max_val;
  uint8_t Msg_NumberOfRepetition;
}CanMgr_TxInfoTable_t;

typedef uint8_t(*CanMgr_Read)(float64* data);


typedef struct 
{
   uint8_t Message_Index;
  CanMgr_Read Message_funcptr;
}Rx_Dispatcher_t;

typedef void (*Rx_SignalIndication)(void);

typedef struct
{
  Rx_SignalIndication Rx_SignalIndication_cbkFuncPtr; 
}Rx_SignalIndication_t;


typedef struct 
{
  uint8_t  Message_Index;
  Rx_SignalIndication RxSignal_ReceptionTimeout_cbkFuncPtr;
  }ReceptionTimeout_t;


extern ReceptionTimeout_t Rx_ReceptionTimeoutCbk_Table[MAX_RX_SIGNALS];
extern Rx_SignalIndication_t RxCbk_SignalIndication_Table[MAX_RX_SIGNALS];
extern Rx_Dispatcher_t Rx_Dispatcher[MAX_RX_SIGNALS];



typedef struct
{
   uint8_t User_idx;
   Rx_Msg_Method frame_type;
   Rx_Mxg_Length length;
   uint16_t timeout;
   uint16_t timeout_counter;
   uint8_t checksum_enable;
   uint8_t checksum_debounce_counter;
   uint8_t checksum_error_recovery_counter;
   uint8_t checksum_byte_pos;
   uint8_t alive_counter_enable;
   uint8_t alive_debounce_counter;
   uint8_t alive_error_recovery_counter;
   uint8_t alive_counter_byte_Pos;
   uint8_t alive_counter_bit_pos;
   const void *msg_default_safe_value;
   void *msg_last_received_data;
}CanMgr_RxInfoTable_t;


extern const CanMgr_TxInfoTable_t CanMgr_TxInfoTable[CANMGR_MAX_NO_OF_TX_MSGS];


extern CanMgr_RxInfoTable_t CanMgr_RxInfoTable[CANMGR_MAX_NO_OF_RX_MSGS];

/*Structure to maintain the flags for IfActive variant
 * Message_Index - Index of the message to which the signal belongs to
 * SignalIfActiveFlag - Flag to maintain whether the signal of that particular message is active/inactive*/
typedef struct 
{
   uint8_t Message_Index;
   boolean SignalIfActiveFlag;
   Tx_Signal_SendType Signal_SendType;
}CanMgr_Tx_Signal_st;

/*Structured table to iterate the Active value status of each and every signal*/
extern CanMgr_Tx_Signal_st CanMgr_TxSignalInfoTable_t[MAX_TX_SIGNALS];

void CanMgr_cfgInit(void);


/* 
  * @Brief  : The following functions shall be used by the application to update signal to be transmitted
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 

uint8_t CanMgr_Write_ic_crc_info_0x321_s(float64 data);
uint8_t CanMgr_Write_alive_counter_ic_info_0x321_s(float64 data);
uint8_t CanMgr_Write_ic_ss_tell_tell_error_0x321_s(float64 data);
uint8_t CanMgr_Write_ic_ss_tell_tell_status_0x321_s(float64 data);
uint8_t CanMgr_Write_odo_signal_0x321_s(float64 data);
uint8_t CanMgr_Write_ambiant_light_data_0x321_s(float64 data);

/* 
  * @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : NONE                                                                               
  * @return : Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                               
*/ 

uint8_t CanMgr_ic_crc_info_0x321_s_cbk_0x321(void);
uint8_t CanMgr_alive_counter_ic_info_0x321_s_cbk_0x321(void);
uint8_t CanMgr_ic_ss_tell_tell_error_0x321_s_cbk_0x321(void);
uint8_t CanMgr_ic_ss_tell_tell_status_0x321_s_cbk_0x321(void);
uint8_t CanMgr_odo_signal_0x321_s_cbk_0x321(void);
uint8_t CanMgr_ambiant_light_data_0x321_s_cbk_0x321(void);



/* 
  * @Brief  : The following functions shall be used by the application to update signal to be transmitted
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 

uint8_t CanMgr_Write_req_diag_ans_tcu_1_0x631_s(float64 data);

/* 
  * @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : NONE                                                                               
  * @return : Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                               
*/ 

uint8_t CanMgr_req_diag_ans_tcu_1_0x631_s_cbk_0x631(void);



/* 
  * @Brief  : The following functions shall be used by the application to update signal to be transmitted
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 

uint8_t CanMgr_Write_req_diag_ans_abs_1_0x6f0_s(float64 data);

/* 
  * @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : NONE                                                                               
  * @return : Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                               
*/ 

uint8_t CanMgr_req_diag_ans_abs_1_0x6f0_s_cbk_0x6f0(void);



/* 
  * @Brief  : The following functions shall be used by the application to update signal to be transmitted
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 

uint8_t CanMgr_Write_req_diag_ans_bcm_1_0x6f1_s(float64 data);

/* 
  * @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : NONE                                                                               
  * @return : Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                               
*/ 

uint8_t CanMgr_req_diag_ans_bcm_1_0x6f1_s_cbk_0x6f1(void);



/* 
  * @Brief  : The following functions shall be used by the application to update signal to be transmitted
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 

uint8_t CanMgr_Write_req_diag_ans_ecm_1_0x7e0_s(float64 data);

/* 
  * @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : NONE                                                                               
  * @return : Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                               
*/ 

uint8_t CanMgr_req_diag_ans_ecm_1_0x7e0_s_cbk_0x7e0(void);



/* 
  * @Brief  : The following functions shall be used by the application to update signal to be transmitted
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 

uint8_t CanMgr_Write_diagnostic_answer_abs_0x629_s(float64 data);

/* 
  * @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : NONE                                                                               
  * @return : Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                               
*/ 

uint8_t CanMgr_diagnostic_answer_abs_0x629_s_cbk_0x629(void);



/* 
  * @Brief  : The following functions shall be used by the application to update signal to be transmitted
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 

uint8_t CanMgr_Write_diagnostic_answer_tcu_0x641_s(float64 data);

/* 
  * @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : NONE                                                                               
  * @return : Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                               
*/ 

uint8_t CanMgr_diagnostic_answer_tcu_0x641_s_cbk_0x641(void);



/* 
  * @Brief  : The following functions shall be used by the application to update signal to be transmitted
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 

uint8_t CanMgr_Write_diagnostic_answer_ic_0x642_s(float64 data);

/* 
  * @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : NONE                                                                               
  * @return : Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                               
*/ 

uint8_t CanMgr_diagnostic_answer_ic_0x642_s_cbk_0x642(void);



/* 
  * @Brief  : The following functions shall be used by the application to update signal to be transmitted
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 

uint8_t CanMgr_Write_diagnostic_answer_bcm_0x644_s(float64 data);

/* 
  * @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : NONE                                                                               
  * @return : Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                               
*/ 

uint8_t CanMgr_diagnostic_answer_bcm_0x644_s_cbk_0x644(void);



/* 
  * @Brief  : The following functions shall be used by the application to update signal to be transmitted
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 

uint8_t CanMgr_Write_diagnostic_answer_ecm_0x7e8_s(float64 data);

/* 
  * @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : NONE                                                                               
  * @return : Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                               
*/ 

uint8_t CanMgr_diagnostic_answer_ecm_0x7e8_s_cbk_0x7e8(void);






/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_engine_speed_0x130_s(float64* data);
uint8_t CanMgr_Read_engine_run_status_0x130_s(float64* data);
uint8_t CanMgr_Read_throttle_position_sensor_0x130_s(float64* data);
uint8_t CanMgr_Read_throttle_position_sensor_fault_0x130_s(float64* data);
uint8_t CanMgr_Read_remote_mobilize_immoblize_status_0x130_s(float64* data);
uint8_t CanMgr_Read_mil_0x130_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_alive_counter_ecm_sensor_0x131_s(float64* data);
uint8_t CanMgr_Read_ecm_crc_sensor_0x131_s(float64* data);
uint8_t CanMgr_Read_roll_over_detection_0x131_s(float64* data);
uint8_t CanMgr_Read_roll_over_detection_fault_status_0x131_s(float64* data);
uint8_t CanMgr_Read_side_stand_sensor_0x131_s(float64* data);
uint8_t CanMgr_Read_side_stand_sensor_fault_0x131_s(float64* data);
uint8_t CanMgr_Read_gear_position_sensor_0x131_s(float64* data);
uint8_t CanMgr_Read_gear_shift_advisory_0x131_s(float64* data);
uint8_t CanMgr_Read_engine_kill_switch_status_0x131_s(float64* data);
uint8_t CanMgr_Read_throttle_grip_sensor_0x131_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_distance_travelled_with_mil_0x135_s(float64* data);
uint8_t CanMgr_Read_accumulat_fuel_inj_time_fuel_qty_0x135_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_abs_crc_trq_0x142_s(float64* data);
uint8_t CanMgr_Read_alive_counter_abs_trq_0x142_s(float64* data);
uint8_t CanMgr_Read_torque_request_status_0x142_s(float64* data);
uint8_t CanMgr_Read_tc_telltale_status_0x142_s(float64* data);
uint8_t CanMgr_Read_trq_req_mtc_0x142_s(float64* data);
uint8_t CanMgr_Read_trq_req_dtc_0x142_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_status_abs_0x205_s(float64* data);
uint8_t CanMgr_Read_abs_telltale_status_0x205_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_vehicle_speed_0x206_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_diagnostic_answer_abs_0x629_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_req_diag_ans_ic_0x632_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_diagnostic_answer_tcu_0x641_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_diagnostic_answer_ic_0x642_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_diagnostic_answer_bcm_0x644_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_diagnostic_answer_ecm_0x7e8_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_req_diag_ans_tcu_0x631_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_req_diag_answ_ic_0x632_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_req_diag_ans_abs_0x6f0_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_req_diag_ans_bcm_0x6f1_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_functional_diagnostic_request_0x7df_s(float64* data);

/* 
* @Brief  : The following functions shall be used by the application to check transmission status
  * @param  : pointer to store the data                                                                                
  * @return : Reception status (MSG_RECEIVED / MSG_MISSING /MSG_NEVER_RECEIVED)                                                                               
*/ 

uint8_t CanMgr_Read_req_diag_ans_ecm_0x7e0_s(float64* data);


   /**********************************************************************************************************************
  *                                                R E V I S I O N   H I S T O R Y             
***********************************************************************************************************************/
 /**********************************************************************************************************************
    REVISION NUMBER      : V1.0.3                                                                                   
    REVISION DATE        : 26/11/2020                                                                              
    CREATED / REVISED BY : Rajasekar T(rajasekar@niyatainfotech.com)                                        
    DESCRIPTION          : Added the Error service support Configuration                                                                       
  ---------------------------------------------------------------------------------------------------------------------
 ***********************************************************************************************************************/
 /**********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                                                                                   
    REVISION DATE        : 30/01/2020                                                                               
    CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
    DESCRIPTION          : Initial Version                                                                       
  ---------------------------------------------------------------------------------------------------------------------
 ***********************************************************************************************************************/
#endif /* CANMGR_CFG_H_ */
