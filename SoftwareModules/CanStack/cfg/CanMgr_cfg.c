/*
* CanMgr_cfg.c
*
*  Created on:19-7-2022
*      Author: BALAJIPANDURANG
*/

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
#include "CanMgr.h"
#include "CanMgr_cfg.h"



/***********************************************************************************************************************
 *                          M A C R O D E F I N I T I O N S
***********************************************************************************************************************/


#define EINVAL 22


/***********************************************************************************************************************
 *                          V A R I A B L E S D E F I N I  T I O N S
***********************************************************************************************************************/

/**
* Signals in message ECM_ENGINE_PARAMETER_0x130.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint16 engine_speed_0x130_s;
uint8 engine_run_status_0x130_s;
uint8 throttle_position_sensor_0x130_s;
uint8 throttle_position_sensor_fault_0x130_s;
uint8 remote_mobilize_immoblize_status_0x130_s;
uint8 mil_0x130_s;
}ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_t;

static ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_t   ecm_engine_parameter_0x130;

/**
* Signals in message ECM_SENSOR_PARAMETER_0x131.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint8 alive_counter_ecm_sensor_0x131_s;
uint8 ecm_crc_sensor_0x131_s;
uint8 roll_over_detection_0x131_s;
uint8 roll_over_detection_fault_status_0x131_s;
uint8 side_stand_sensor_0x131_s;
uint8 side_stand_sensor_fault_0x131_s;
uint8 gear_position_sensor_0x131_s;
uint8 gear_shift_advisory_0x131_s;
uint8 engine_kill_switch_status_0x131_s;
uint8 throttle_grip_sensor_0x131_s;
}ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_t;

static ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_t   ecm_sensor_parameter_0x131;

/**
* Signals in message ECM_ADDITIONAL_INFO_0x135.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint16 distance_travelled_with_mil_0x135_s;
uint16 accumulat_fuel_inj_time_fuel_qty_0x135_s;
}ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_t;

static ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_t   ecm_additional_info_0x135;

/**
* Signals in message ABS_TRQ_REQ_0x142.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint8 abs_crc_trq_0x142_s;
uint8 alive_counter_abs_trq_0x142_s;
uint8 torque_request_status_0x142_s;
uint8 tc_telltale_status_0x142_s;
sint16 trq_req_mtc_0x142_s;
sint16 trq_req_dtc_0x142_s;
}ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_t;

static ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_t   abs_trq_req_0x142;

/**
* Signals in message ABS_STATUS_0x205.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint8 status_abs_0x205_s;
uint8 abs_telltale_status_0x205_s;
}ch1raaacanmessagestandardv1can1draft_abs_status_0x205_t;

static ch1raaacanmessagestandardv1can1draft_abs_status_0x205_t   abs_status_0x205;

/**
* Signals in message ABS_VEHICLE_SPEED_0x206.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint8 vehicle_speed_0x206_s;
}ch1raaacanmessagestandardv1can1draft_abs_vehicle_speed_0x206_t;

static ch1raaacanmessagestandardv1can1draft_abs_vehicle_speed_0x206_t   abs_vehicle_speed_0x206;

/**
* Signals in message DIAG_ANS_ABS_0x629.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 diagnostic_answer_abs_0x629_s;
}ch1raaacanmessagestandardv1can1draft_diag_ans_abs_0x629_t;

static ch1raaacanmessagestandardv1can1draft_diag_ans_abs_0x629_t   diag_ans_abs_0x629;

/**
* Signals in message REQ_DIAG_ANS_IC_0x632.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 req_diag_ans_ic_0x632_s;
}ch1raaacanmessagestandardv1can1draft_req_diag_ans_ic_0x632_t;

static ch1raaacanmessagestandardv1can1draft_req_diag_ans_ic_0x632_t   req_diag_ans_ic_0x632;

/**
* Signals in message DIAG_ANSW_TCU_0x641.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 diagnostic_answer_tcu_0x641_s;
}ch1raaacanmessagestandardv1can1draft_diag_answ_tcu_0x641_t;

static ch1raaacanmessagestandardv1can1draft_diag_answ_tcu_0x641_t   diag_answ_tcu_0x641;

/**
* Signals in message DIAG_ANS_IC_0x642.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 diagnostic_answer_ic_0x642_s;
}ch1raaacanmessagestandardv1can1draft_diag_ans_ic_0x642_t;

static ch1raaacanmessagestandardv1can1draft_diag_ans_ic_0x642_t   diag_ans_ic_0x642;

/**
* Signals in message DIAG_ANS_BCM_0x644.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 diagnostic_answer_bcm_0x644_s;
}ch1raaacanmessagestandardv1can1draft_diag_ans_bcm_0x644_t;

static ch1raaacanmessagestandardv1can1draft_diag_ans_bcm_0x644_t   diag_ans_bcm_0x644;

/**
* Signals in message DIAG_ANS_ECM_0x7e8.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 diagnostic_answer_ecm_0x7e8_s;
}ch1raaacanmessagestandardv1can1draft_diag_ans_ecm_0x7e8_t;

static ch1raaacanmessagestandardv1can1draft_diag_ans_ecm_0x7e8_t   diag_ans_ecm_0x7e8;

/**
* Signals in message REQ_DIAG_ANSW_TCU_0x631.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 req_diag_ans_tcu_0x631_s;
}ch2raaacanmessagestandardv1can2draft_req_diag_answ_tcu_0x631_t;

static ch2raaacanmessagestandardv1can2draft_req_diag_answ_tcu_0x631_t   req_diag_answ_tcu_0x631;

/**
* Signals in message REQ_DIAG_ANSW_IC_0x632.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 req_diag_ans_ic_0x632_s;
}ch2raaacanmessagestandardv1can2draft_req_diag_answ_ic_0x632_t;

static ch2raaacanmessagestandardv1can2draft_req_diag_answ_ic_0x632_t   req_diag_answ_ic_0x632;

/**
* Signals in message REQ_DIAG_ANSW_ABS_0x6f0.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 req_diag_ans_abs_0x6f0_s;
}ch2raaacanmessagestandardv1can2draft_req_diag_answ_abs_0x6f0_t;

static ch2raaacanmessagestandardv1can2draft_req_diag_answ_abs_0x6f0_t   req_diag_answ_abs_0x6f0;

/**
* Signals in message REQ_DIAG_ANSW_BCM_0x6f1.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 req_diag_ans_bcm_0x6f1_s;
}ch2raaacanmessagestandardv1can2draft_req_diag_answ_bcm_0x6f1_t;

static ch2raaacanmessagestandardv1can2draft_req_diag_answ_bcm_0x6f1_t   req_diag_answ_bcm_0x6f1;

/**
* Signals in message Functional_Diag_Request_0x7df.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 functional_diagnostic_request_0x7df_s;
}ch2raaacanmessagestandardv1can2draft_functional_diag_request_0x7df_t;

static ch2raaacanmessagestandardv1can2draft_functional_diag_request_0x7df_t   functional_diag_request_0x7df;

/**
* Signals in message REQ_DIAG_ANSW_ECM_0x7e0.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 req_diag_ans_ecm_0x7e0_s;
}ch2raaacanmessagestandardv1can2draft_req_diag_answ_ecm_0x7e0_t;

static ch2raaacanmessagestandardv1can2draft_req_diag_answ_ecm_0x7e0_t   req_diag_answ_ecm_0x7e0;




/**
* Signals in message IC_INFO_MSG_0x321.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint8 ic_crc_info_0x321_s;
uint8 alive_counter_ic_info_0x321_s;
uint8 ic_ss_tell_tell_error_0x321_s;
uint8 ic_ss_tell_tell_status_0x321_s;
uint32 odo_signal_0x321_s;
uint8 ambiant_light_data_0x321_s;
}ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_t;

static ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_t   ic_info_msg_0x321;

/**
* Signals in message REQ_DIAGN_ANS_TCU_0x631.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 req_diag_ans_tcu_1_0x631_s;
}ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_t;

static ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_t   req_diagn_ans_tcu_0x631;

/**
* Signals in message REQ_DIAGN_ANS_ABS_0x6f0.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 req_diag_ans_abs_1_0x6f0_s;
}ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_t;

static ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_t   req_diagn_ans_abs_0x6f0;

/**
* Signals in message REQ_DIAGN_ANS_BCM_0x6f1.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 req_diag_ans_bcm_1_0x6f1_s;
}ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_t;

static ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_t   req_diagn_ans_bcm_0x6f1;

/**
* Signals in message REQ_DIAGN_ANS_ECM_0x7e0.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 req_diag_ans_ecm_1_0x7e0_s;
}ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_t;

static ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_t   req_diagn_ans_ecm_0x7e0;

/**
* Signals in message DIAG_ANSW_ABS_0x629.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 diagnostic_answer_abs_0x629_s;
}ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_t;

static ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_t   diag_answ_abs_0x629;

/**
* Signals in message DIA_ANSW_TCU_0x641.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 diagnostic_answer_tcu_0x641_s;
}ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_t;

static ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_t   dia_answ_tcu_0x641;

/**
* Signals in message DIAG_ANSW_IC_0x642.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 diagnostic_answer_ic_0x642_s;
}ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_t;

static ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_t   diag_answ_ic_0x642;

/**
* Signals in message DIAG_ANSW_BCM_0x644.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 diagnostic_answer_bcm_0x644_s;
}ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_t;

static ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_t   diag_answ_bcm_0x644;

/**
* Signals in message DIAG_ANSW_ECM_0x7e8.
*
* All signal values are as on the CAN bus.
*/


typedef struct {
uint64 diagnostic_answer_ecm_0x7e8_s;
}ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_t;

static ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_t   diag_answ_ecm_0x7e8;






static const ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_t default_ic_info_msg_0x321 ={0,0,0,0,0,1};
static const ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_t default_req_diagn_ans_tcu_0x631 ={0};
static const ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_t default_req_diagn_ans_abs_0x6f0 ={0};
static const ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_t default_req_diagn_ans_bcm_0x6f1 ={0};
static const ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_t default_req_diagn_ans_ecm_0x7e0 ={0};
static const ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_t default_diag_answ_abs_0x629 ={0};
static const ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_t default_dia_answ_tcu_0x641 ={0};
static const ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_t default_diag_answ_ic_0x642 ={0};
static const ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_t default_diag_answ_bcm_0x644 ={0};
static const ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_t default_diag_answ_ecm_0x7e8 ={0};



/* Configuration Can Rx Signal Initial  Value or Can Checksum safe error value */
static const ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_t default_ecm_engine_parameter_0x130 ={0,0,0,0,0,0};
static const ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_t default_ecm_sensor_parameter_0x131 ={0,0,0,0,0xFF,0,0xFF,0,0,0};
static const ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_t default_ecm_additional_info_0x135 ={0,0};
static const ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_t default_abs_trq_req_0x142  ={0,0,0,0,0,0};
static const ch1raaacanmessagestandardv1can1draft_abs_status_0x205_t default_abs_status_0x205  ={0xFF,0xFF};
static const ch1raaacanmessagestandardv1can1draft_abs_vehicle_speed_0x206_t default_abs_vehicle_speed_0x206  ={0};
static const ch1raaacanmessagestandardv1can1draft_diag_ans_abs_0x629_t default_diag_ans_abs_0x629  ={0};
static const ch1raaacanmessagestandardv1can1draft_req_diag_ans_ic_0x632_t default_req_diag_ans_ic_0x632  ={0};
static const ch1raaacanmessagestandardv1can1draft_diag_answ_tcu_0x641_t default_diag_answ_tcu_0x641 ={0};
static const ch1raaacanmessagestandardv1can1draft_diag_ans_ic_0x642_t default_diag_ans_ic_0x642  ={0};
static const ch1raaacanmessagestandardv1can1draft_diag_ans_bcm_0x644_t default_diag_ans_bcm_0x644  ={0};
static const ch1raaacanmessagestandardv1can1draft_diag_ans_ecm_0x7e8_t default_diag_ans_ecm_0x7e8  ={0};
static const ch2raaacanmessagestandardv1can2draft_req_diag_answ_tcu_0x631_t default_req_diag_answ_tcu_0x631  ={0};
static const ch2raaacanmessagestandardv1can2draft_req_diag_answ_ic_0x632_t default_req_diag_answ_ic_0x632  ={0};
static const ch2raaacanmessagestandardv1can2draft_req_diag_answ_abs_0x6f0_t default_req_diag_answ_abs_0x6f0  ={0};
static const ch2raaacanmessagestandardv1can2draft_req_diag_answ_bcm_0x6f1_t default_req_diag_answ_bcm_0x6f1  ={0};
static const ch2raaacanmessagestandardv1can2draft_functional_diag_request_0x7df_t default_functional_diag_request_0x7df ={0};
static const ch2raaacanmessagestandardv1can2draft_req_diag_answ_ecm_0x7e0_t default_req_diag_answ_ecm_0x7e0  ={0};



uint8_t Init_data_value[CANMGR_MAX_NO_OF_TX_MSGS][8];


Rx_Dispatcher_t Rx_Dispatcher[MAX_RX_SIGNALS] = {
       {0,&CanMgr_Read_engine_speed_0x130_s},
       {0,&CanMgr_Read_engine_run_status_0x130_s},
       {0,&CanMgr_Read_throttle_position_sensor_0x130_s},
       {0,&CanMgr_Read_throttle_position_sensor_fault_0x130_s},
       {0,&CanMgr_Read_remote_mobilize_immoblize_status_0x130_s},
       {0,&CanMgr_Read_mil_0x130_s},
       {1,&CanMgr_Read_alive_counter_ecm_sensor_0x131_s},
       {1,&CanMgr_Read_ecm_crc_sensor_0x131_s},
       {1,&CanMgr_Read_roll_over_detection_0x131_s},
       {1,&CanMgr_Read_roll_over_detection_fault_status_0x131_s},
       {1,&CanMgr_Read_side_stand_sensor_0x131_s},
       {1,&CanMgr_Read_side_stand_sensor_fault_0x131_s},
       {1,&CanMgr_Read_gear_position_sensor_0x131_s},
       {1,&CanMgr_Read_gear_shift_advisory_0x131_s},
       {1,&CanMgr_Read_engine_kill_switch_status_0x131_s},
       {1,&CanMgr_Read_throttle_grip_sensor_0x131_s},
       {2,&CanMgr_Read_distance_travelled_with_mil_0x135_s},
       {2,&CanMgr_Read_accumulat_fuel_inj_time_fuel_qty_0x135_s},
       {3,&CanMgr_Read_abs_crc_trq_0x142_s},
       {3,&CanMgr_Read_torque_request_status_0x142_s},
       {3,&CanMgr_Read_alive_counter_abs_trq_0x142_s},
       {3,&CanMgr_Read_tc_telltale_status_0x142_s},
       {3,&CanMgr_Read_trq_req_mtc_0x142_s},
       {3,&CanMgr_Read_trq_req_dtc_0x142_s},
       {4,&CanMgr_Read_status_abs_0x205_s},
       {4,&CanMgr_Read_abs_telltale_status_0x205_s},
       {5,&CanMgr_Read_vehicle_speed_0x206_s},
       {6,&CanMgr_Read_diagnostic_answer_abs_0x629_s},
       {7,&CanMgr_Read_req_diag_ans_ic_0x632_s},
       {8,&CanMgr_Read_diagnostic_answer_tcu_0x641_s},
       {9,&CanMgr_Read_diagnostic_answer_ic_0x642_s},
       {10,&CanMgr_Read_diagnostic_answer_bcm_0x644_s},
       {11,&CanMgr_Read_diagnostic_answer_ecm_0x7e8_s},
       {12,&CanMgr_Read_req_diag_ans_tcu_0x631_s},
       {13,&CanMgr_Read_req_diag_answ_ic_0x632_s},
       {14,&CanMgr_Read_req_diag_ans_abs_0x6f0_s},
       {15,&CanMgr_Read_req_diag_ans_bcm_0x6f1_s},
       {16,&CanMgr_Read_functional_diagnostic_request_0x7df_s},
       {17,&CanMgr_Read_req_diag_ans_ecm_0x7e0_s}


};



Rx_SignalIndication_t RxCbk_SignalIndication_Table[MAX_RX_SIGNALS] ={
       { CANMGR_ENGINE_SPEED_0X130_S_RXCBK },
       { CANMGR_ENGINE_RUN_STATUS_0X130_S_RXCBK },
       { CANMGR_THROTTLE_POSITION_SENSOR_0X130_S_RXCBK },
       { CANMGR_THROTTLE_POSITION_SENSOR_FAULT_0X130_S_RXCBK },
       { CANMGR_REMOTE_MOBILIZE_IMMOBLIZE_STATUS_0X130_S_RXCBK },
       { CANMGR_MIL_0X130_S_RXCBK },
       { CANMGR_ALIVE_COUNTER_ECM_SENSOR_0X131_S_RXCBK },
       { CANMGR_ECM_CRC_SENSOR_0X131_S_RXCBK },
       { CANMGR_ROLL_OVER_DETECTION_0X131_S_RXCBK },
       { CANMGR_ROLL_OVER_DETECTION_FAULT_STATUS_0X131_S_RXCBK },
       { CANMGR_SIDE_STAND_SENSOR_0X131_S_RXCBK },
       { CANMGR_SIDE_STAND_SENSOR_FAULT_0X131_S_RXCBK },
       { CANMGR_GEAR_POSITION_SENSOR_0X131_S_RXCBK },
       { CANMGR_GEAR_SHIFT_ADVISORY_0X131_S_RXCBK },
       { CANMGR_ENGINE_KILL_SWITCH_STATUS_0X131_S_RXCBK },
       { CANMGR_THROTTLE_GRIP_SENSOR_0X131_S_RXCBK },
       { CANMGR_DISTANCE_TRAVELLED_WITH_MIL_0X135_S_RXCBK },
       { CANMGR_ACCUMULAT_FUEL_INJ_TIME_FUEL_QTY_0X135_S_RXCBK },
       { CANMGR_ABS_CRC_TRQ_0X142_S_RXCBK },
       { CANMGR_ALIVE_COUNTER_ABS_TRQ_0X142_S_RXCBK },
       { CANMGR_TORQUE_REQUEST_STATUS_0X142_S_RXCBK },
       { CANMGR_TC_TELLTALE_STATUS_0X142_S_RXCBK },
       { CANMGR_TRQ_REQ_MTC_0X142_S_RXCBK },
       { CANMGR_TRQ_REQ_DTC_0X142_S_RXCBK },
       { CANMGR_STATUS_ABS_0X205_S_RXCBK },
       { CANMGR_ABS_TELLTALE_STATUS_0X205_S_RXCBK },
       { CANMGR_VEHICLE_SPEED_0X206_S_RXCBK },
       { CANMGR_DIAGNOSTIC_ANSWER_ABS_0X629_S_RXCBK },
       { CANMGR_REQ_DIAG_ANS_IC_0X632_S_RXCBK },
       { CANMGR_DIAGNOSTIC_ANSWER_TCU_0X641_S_RXCBK },
       { CANMGR_DIAGNOSTIC_ANSWER_IC_0X642_S_RXCBK },
       { CANMGR_DIAGNOSTIC_ANSWER_BCM_0X644_S_RXCBK },
       { CANMGR_DIAGNOSTIC_ANSWER_ECM_0X7E8_S_RXCBK },
       { CANMGR_REQ_DIAG_ANS_TCU_0X631_S_RXCBK },
       { CANMGR_REQ_DIAG_ANS_IC_0X632_S_RXCBK },
       { CANMGR_REQ_DIAG_ANS_ABS_0X6F0_S_RXCBK },
       { CANMGR_REQ_DIAG_ANS_BCM_0X6F1_S_RXCBK },
       { CANMGR_FUNCTIONAL_DIAGNOSTIC_REQUEST_0X7DF_S_RXCBK },
       { CANMGR_REQ_DIAG_ANS_ECM_0X7E0_S_RXCBK }


};


ReceptionTimeout_t Rx_ReceptionTimeoutCbk_Table[MAX_RX_SIGNALS]={
       {0,CANMGR_ENGINE_SPEED_0X130_S_TIMEOUT_CBK},
       {0,CANMGR_ENGINE_RUN_STATUS_0X130_S_TIMEOUT_CBK},
       {0,CANMGR_THROTTLE_POSITION_SENSOR_0X130_S_TIMEOUT_CBK},
       {0,CANMGR_THROTTLE_POSITION_SENSOR_FAULT_0X130_S_TIMEOUT_CBK},
       {0,CANMGR_REMOTE_MOBILIZE_IMMOBLIZE_STATUS_0X130_S_TIMEOUT_CBK},
       {0,CANMGR_MIL_0X130_S_TIMEOUT_CBK},
       {1,CANMGR_ALIVE_COUNTER_ECM_SENSOR_0X131_S_TIMEOUT_CBK},
       {1,CANMGR_ECM_CRC_SENSOR_0X131_S_TIMEOUT_CBK},
       {1,CANMGR_ROLL_OVER_DETECTION_0X131_S_TIMEOUT_CBK},
       {1,CANMGR_ROLL_OVER_DETECTION_FAULT_STATUS_0X131_S_TIMEOUT_CBK},
       {1,CANMGR_SIDE_STAND_SENSOR_0X131_S_TIMEOUT_CBK},
       {1,CANMGR_SIDE_STAND_SENSOR_FAULT_0X131_S_TIMEOUT_CBK},
       {1,CANMGR_GEAR_POSITION_SENSOR_0X131_S_TIMEOUT_CBK},
       {1,CANMGR_GEAR_SHIFT_ADVISORY_0X131_S_TIMEOUT_CBK},
       {1,CANMGR_ENGINE_KILL_SWITCH_STATUS_0X131_S_TIMEOUT_CBK},
       {1,CANMGR_THROTTLE_GRIP_SENSOR_0X131_S_TIMEOUT_CBK},
       {2,CANMGR_DISTANCE_TRAVELLED_WITH_MIL_0X135_S_TIMEOUT_CBK},
       {2,CANMGR_ACCUMULAT_FUEL_INJ_TIME_FUEL_QTY_0X135_S_TIMEOUT_CBK},
       {3,CANMGR_ABS_CRC_TRQ_0X142_S_TIMEOUT_CBK},
       {3,CANMGR_ALIVE_COUNTER_ABS_TRQ_0X142_S_TIMEOUT_CBK},
       {3,CANMGR_TORQUE_REQUEST_STATUS_0X142_S_TIMEOUT_CBK},
       {3,CANMGR_TC_TELLTALE_STATUS_0X142_S_TIMEOUT_CBK},
       {3,CANMGR_TRQ_REQ_MTC_0X142_S_TIMEOUT_CBK},
       {3,CANMGR_TRQ_REQ_DTC_0X142_S_TIMEOUT_CBK},
       {4,CANMGR_STATUS_ABS_0X205_S_TIMEOUT_CBK},
       {4,CANMGR_ABS_TELLTALE_STATUS_0X205_S_TIMEOUT_CBK},
       {5,CANMGR_VEHICLE_SPEED_0X206_S_TIMEOUT_CBK},
       {6,CANMGR_DIAGNOSTIC_ANSWER_ABS_0X629_S_TIMEOUT_CBK},
       {7,CANMGR_REQ_DIAG_ANS_IC_0X632_S_TIMEOUT_CBK},
       {8,CANMGR_DIAGNOSTIC_ANSWER_TCU_0X641_S_TIMEOUT_CBK},
       {9,CANMGR_DIAGNOSTIC_ANSWER_IC_0X642_S_TIMEOUT_CBK},
       {10,CANMGR_DIAGNOSTIC_ANSWER_BCM_0X644_S_TIMEOUT_CBK},
       {11,CANMGR_DIAGNOSTIC_ANSWER_ECM_0X7E8_S_TIMEOUT_CBK},
       {12,CANMGR_REQ_DIAG_ANS_TCU_0X631_S_TIMEOUT_CBK},
       {13,CANMGR_REQ_DIAG_ANS_IC_0X632_S_TIMEOUT_CBK},
       {14,CANMGR_REQ_DIAG_ANS_ABS_0X6F0_S_TIMEOUT_CBK},
       {15,CANMGR_REQ_DIAG_ANS_BCM_0X6F1_S_TIMEOUT_CBK},
       {16,CANMGR_FUNCTIONAL_DIAGNOSTIC_REQUEST_0X7DF_S_TIMEOUT_CBK},
       {17,CANMGR_REQ_DIAG_ANS_ECM_0X7E0_S_TIMEOUT_CBK}


};



const CanMgr_TxInfoTable_t CanMgr_TxInfoTable[CANMGR_MAX_NO_OF_TX_MSGS] = {
      {
          0,
          REQ_DIAGN_ANS_TCU_0X631_TX_METHOD , 
          REQ_DIAGN_ANS_TCU_0X631_CLC_TIME,
          REQ_DIAGN_ANS_TCU_0X631_CLC_TIME_FAST,
          REQ_DIAGN_ANS_TCU_0X631_LENGTH,
          0,
          STD_ON ,
          STD_ON ,
          0,
          0xE,
          0
      }
      ,
      {
          0,
          REQ_DIAGN_ANS_ABS_0X6F0_TX_METHOD , 
          REQ_DIAGN_ANS_ABS_0X6F0_CLC_TIME,
          REQ_DIAGN_ANS_ABS_0X6F0_CLC_TIME_FAST,
          REQ_DIAGN_ANS_ABS_0X6F0_LENGTH,
          0,
          STD_OFF ,
          STD_OFF ,
          0,
          0,
          0
      }
      ,
      {
          0,
          REQ_DIAGN_ANS_BCM_0X6F1_TX_METHOD , 
          REQ_DIAGN_ANS_BCM_0X6F1_CLC_TIME,
          REQ_DIAGN_ANS_BCM_0X6F1_CLC_TIME_FAST,
          REQ_DIAGN_ANS_BCM_0X6F1_LENGTH,
          0,
          STD_OFF ,
          STD_OFF ,
          0,
          0,
          0
      }
      ,
      {
          0,
          REQ_DIAGN_ANS_ECM_0X7E0_TX_METHOD , 
          REQ_DIAGN_ANS_ECM_0X7E0_CLC_TIME,
          REQ_DIAGN_ANS_ECM_0X7E0_CLC_TIME_FAST,
          REQ_DIAGN_ANS_ECM_0X7E0_LENGTH,
          0,
          STD_OFF ,
          STD_OFF ,
          0,
          0,
          0
      }
      ,
      {
          0,
          IC_INFO_MSG_0X321_TX_METHOD , 
          IC_INFO_MSG_0X321_CLC_TIME,
          IC_INFO_MSG_0X321_CLC_TIME_FAST,
          IC_INFO_MSG_0X321_LENGTH,
          0,
          STD_OFF ,
          STD_OFF ,
          0,
          0,
          0
      }
      ,
      {
          1,
          DIAG_ANSW_ABS_0X629_TX_METHOD , 
          DIAG_ANSW_ABS_0X629_CLC_TIME,
          DIAG_ANSW_ABS_0X629_CLC_TIME_FAST,
          DIAG_ANSW_ABS_0X629_LENGTH,
          0,
          STD_OFF ,
          STD_OFF ,
          0,
          0,
          0
      }
      ,
      {
          1,
          DIA_ANSW_TCU_0X641_TX_METHOD , 
          DIA_ANSW_TCU_0X641_CLC_TIME,
          DIA_ANSW_TCU_0X641_CLC_TIME_FAST,
          DIA_ANSW_TCU_0X641_LENGTH,
          0,
          STD_OFF ,
          STD_OFF ,
          0,
          0,
          0
      }
      ,
      {
          1,
          DIAG_ANSW_IC_0X642_TX_METHOD , 
          DIAG_ANSW_IC_0X642_CLC_TIME,
          DIAG_ANSW_IC_0X642_CLC_TIME_FAST,
          DIAG_ANSW_IC_0X642_LENGTH,
          0,
          STD_OFF ,
          STD_OFF ,
          0,
          0,
          0
      }
      ,
      {
          1,
          DIAG_ANSW_BCM_0X644_TX_METHOD , 
          DIAG_ANSW_BCM_0X644_CLC_TIME,
          DIAG_ANSW_BCM_0X644_CLC_TIME_FAST,
          DIAG_ANSW_BCM_0X644_LENGTH,
          0,
          STD_OFF ,
          STD_OFF ,
          0,
          0,
          0
      }
      ,
      {
          1,
          DIAG_ANSW_ECM_0X7E8_TX_METHOD , 
          DIAG_ANSW_ECM_0X7E8_CLC_TIME,
          DIAG_ANSW_ECM_0X7E8_CLC_TIME_FAST,
          DIAG_ANSW_ECM_0X7E8_LENGTH,
          0,
          STD_OFF ,
          STD_OFF ,
          0,
          0,
          0
      }
      

};
CanMgr_RxInfoTable_t CanMgr_RxInfoTable[CANMGR_MAX_NO_OF_RX_MSGS] = {
      {
	        0,
          ECM_ENGINE_PARAMETER_0X130_RX_METHOD , 
          ECM_ENGINE_PARAMETER_0X130_LENGTH,
          5,
          0,
          STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          0,
          0,
          0,//alive counter
          0,
          &default_ecm_engine_parameter_0x130,
          &ecm_engine_parameter_0x130
       }
	   ,
	   {
          0,
          ECM_SENSOR_PARAMETER_0X131_RX_METHOD , 
          ECM_SENSOR_PARAMETER_0X131_LENGTH,
          25,
          0,
          STD_ON,
          1 ,
          0 ,
          2 ,
          STD_ON,
          3,
          0,
          0,
          2,
          &default_ecm_sensor_parameter_0x131,
          &ecm_sensor_parameter_0x131
       }
	   ,
	   {
          0,
          ECM_ADDITIONAL_INFO_0X135_RX_METHOD , 
          ECM_ADDITIONAL_INFO_0X135_LENGTH,
          100,
          0,
         STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          0 ,
          0 ,
          0,
          0,
          &default_ecm_additional_info_0x135,
          &ecm_additional_info_0x135
       }
	   ,
	   
	   {
          0,
          ABS_TRQ_REQ_0X142_RX_METHOD , 
          ABS_TRQ_REQ_0X142_LENGTH,
          10,
          0,
          STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          0 ,
          0,
          0,
          0,
          &default_abs_trq_req_0x142,
          &abs_trq_req_0x142
       }
      ,
	   {
          0,
          ABS_STATUS_0X205_RX_METHOD , 
          ABS_STATUS_0X205_LENGTH,
          25,
          0,
         STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          0 ,
          0,
          0,
          0,
          &default_abs_status_0x205,
          &abs_status_0x205
       }
      ,
	  {
          0,
          ABS_VEHICLE_SPEED_0X206_RX_METHOD , 
          ABS_VEHICLE_SPEED_0X206_LENGTH,
          50,
          0,
          STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          0 ,
          0,
          0,
          0,
          &default_abs_vehicle_speed_0x206,
          &abs_vehicle_speed_0x206
       }
      ,
	   {
          0,
          DIAG_ANS_ABS_0X629_RX_METHOD , 
          DIAG_ANS_ABS_0X629_LENGTH,
          0,
          0,
          STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          2,
          0 ,
          0,
          0,
          &default_diag_ans_abs_0x629,
          &diag_ans_abs_0x629
       }
      ,
	   
      {
          0,
          REQ_DIAG_ANS_IC_0X632_RX_METHOD , 
          REQ_DIAG_ANS_IC_0X632_LENGTH,
          0,
          0,
          STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          0 ,
          0,
          0,
          0,
          &default_req_diag_ans_ic_0x632,
          &req_diag_ans_ic_0x632
       }
      ,
	   {
          0,
          DIAG_ANSW_TCU_0X641_RX_METHOD , 
          DIAG_ANSW_TCU_0X641_LENGTH,
          0,
          0,
          STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          0 ,
          0,
          0,
          0,
          &default_diag_answ_tcu_0x641,
          &diag_answ_tcu_0x641
       }
      ,
	  {
          0,
          DIAG_ANS_IC_0X642_RX_METHOD , 
          DIAG_ANS_IC_0X642_LENGTH,
          0,
          0,
          STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          0 ,
          0,
          0,
          0,
          &default_diag_ans_ic_0x642,
          &diag_ans_ic_0x642
       }
      ,
	   {
          0,
          DIAG_ANS_BCM_0X644_RX_METHOD , 
          DIAG_ANS_BCM_0X644_LENGTH,
          0,
          0,
         STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          0 ,
          0,
          0,
          0,
          &default_diag_ans_bcm_0x644,
          &diag_ans_bcm_0x644
       }
      ,
	   {
          0,
          DIAG_ANS_ECM_0X7E8_RX_METHOD , 
          DIAG_ANS_ECM_0X7E8_LENGTH,
          0,
          0,
          STD_OFF ,
          0 ,
          0 ,
          0,
          STD_OFF ,
          0 ,
          0 ,
          0,
          0,
          &default_diag_ans_ecm_0x7e8,
          &diag_ans_ecm_0x7e8
       }
      ,
	  
	  {
          1,
          REQ_DIAG_ANSW_TCU_0X631_RX_METHOD , 
          REQ_DIAG_ANSW_TCU_0X631_LENGTH,
          0,
          0,
          STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          0,
          0,
          0,
          0,
          &default_req_diag_answ_tcu_0x631,
          &req_diag_answ_tcu_0x631
       }
      ,
	   {
          1,
          REQ_DIAG_ANSW_IC_0X632_RX_METHOD , 
          REQ_DIAG_ANSW_IC_0X632_LENGTH,
          0,
          0,
          STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          0 ,
          0,
          0,
          0,
          &default_req_diag_answ_ic_0x632,
          &req_diag_answ_ic_0x632
       }
      ,
	  {
          1,
          REQ_DIAG_ANSW_ABS_0X6F0_RX_METHOD , 
          REQ_DIAG_ANSW_ABS_0X6F0_LENGTH,
          0,
          0,
          STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          0 ,
          0,
          0,
          0,
          &default_req_diag_answ_abs_0x6f0,
          &req_diag_answ_abs_0x6f0
       }
      ,
	   
	    {
          1,
          REQ_DIAG_ANSW_BCM_0X6F1_RX_METHOD , 
          REQ_DIAG_ANSW_BCM_0X6F1_LENGTH,
          0,
          0,
         STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          0 ,
          0,
          0,
          0,
          &default_req_diag_answ_bcm_0x6f1,
          &req_diag_answ_bcm_0x6f1
       }
      ,
	    {
          1,
          FUNCTIONAL_DIAG_REQUEST_0X7DF_RX_METHOD , 
          FUNCTIONAL_DIAG_REQUEST_0X7DF_LENGTH,
          0,
          0,
          STD_OFF ,
          0 ,
          0 ,
          0 ,
          STD_OFF ,
          0 ,
          0,
          0,
          0,
          &default_functional_diag_request_0x7df,
          &functional_diag_request_0x7df
       }
      ,
	  
	   {
          1,
          REQ_DIAG_ANSW_ECM_0X7E0_RX_METHOD , 
          REQ_DIAG_ANSW_ECM_0X7E0_LENGTH,
          0,
          0,
          STD_OFF ,
          0 ,
          0 ,
          0,
          STD_OFF ,
          0 ,
          0,
          0,
          0,
          &default_req_diag_answ_ecm_0x7e0,
          &req_diag_answ_ecm_0x7e0
       }
      

};

	  
CanMgr_Tx_Signal_st CanMgr_TxSignalInfoTable_t[MAX_TX_SIGNALS] = {

{REQ_DIAGN_ANS_TCU_0X631, FALSE , REQ_DIAG_ANS_TCU_1_0X631_S_SIGNAL_TX_METHODS},
{REQ_DIAGN_ANS_ABS_0X6F0, FALSE , REQ_DIAG_ANS_ABS_1_0X6F0_S_SIGNAL_TX_METHODS},
{REQ_DIAGN_ANS_BCM_0X6F1, FALSE , REQ_DIAG_ANS_BCM_1_0X6F1_S_SIGNAL_TX_METHODS},
{REQ_DIAGN_ANS_ECM_0X7E0, FALSE , REQ_DIAG_ANS_ECM_1_0X7E0_S_SIGNAL_TX_METHODS},
{IC_INFO_MSG_0X321, FALSE , IC_CRC_INFO_0X321_S_SIGNAL_TX_METHODS},
{IC_INFO_MSG_0X321, FALSE , ALIVE_COUNTER_IC_INFO_0X321_S_SIGNAL_TX_METHODS},
{IC_INFO_MSG_0X321, FALSE , IC_SS_TELL_TELL_ERROR_0X321_S_SIGNAL_TX_METHODS},
{IC_INFO_MSG_0X321, FALSE , IC_SS_TELL_TELL_STATUS_0X321_S_SIGNAL_TX_METHODS},
{IC_INFO_MSG_0X321, FALSE , ODO_SIGNAL_0X321_S_SIGNAL_TX_METHODS},
{IC_INFO_MSG_0X321, FALSE , AMBIANT_LIGHT_DATA_0X321_S_SIGNAL_TX_METHODS},
{DIAG_ANSW_ABS_0X629, FALSE , DIAGNOSTIC_ANSWER_ABS_0X629_S_SIGNAL_TX_METHODS},
{DIA_ANSW_TCU_0X641, FALSE , DIAGNOSTIC_ANSWER_TCU_0X641_S_SIGNAL_TX_METHODS},
{DIAG_ANSW_IC_0X642, FALSE , DIAGNOSTIC_ANSWER_IC_0X642_S_SIGNAL_TX_METHODS},
{DIAG_ANSW_BCM_0X644, FALSE , DIAGNOSTIC_ANSWER_BCM_0X644_S_SIGNAL_TX_METHODS},
{DIAG_ANSW_ECM_0X7E8, FALSE , DIAGNOSTIC_ANSWER_ECM_0X7E8_S_SIGNAL_TX_METHODS}

};




/**********************************************************************************************************************
                                  F U N C T I O N S    D E C L A R A T I O N                        
* *********************************************************************************************************************/

/**
* Pack message IC_INFO_MSG_0x321.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_pack(
      uint8_t *dst_p,
      const  ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_t *src_p,
      size_t size);



/**
* Pack message REQ_DIAGN_ANS_TCU_0x631.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_pack(
      uint8_t *dst_p,
      const  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_t *src_p,
      size_t size);



/**
* Pack message REQ_DIAGN_ANS_ABS_0x6f0.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_pack(
      uint8_t *dst_p,
      const  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_t *src_p,
      size_t size);



/**
* Pack message REQ_DIAGN_ANS_BCM_0x6f1.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_pack(
      uint8_t *dst_p,
      const  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_t *src_p,
      size_t size);



/**
* Pack message REQ_DIAGN_ANS_ECM_0x7e0.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_pack(
      uint8_t *dst_p,
      const  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_t *src_p,
      size_t size);



/**
* Pack message DIAG_ANSW_ABS_0x629.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32 ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_pack(
      uint8_t *dst_p,
      const  ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_t *src_p,
      size_t size);



/**
* Pack message DIA_ANSW_TCU_0x641.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32 ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_pack(
      uint8_t *dst_p,
      const  ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_t *src_p,
      size_t size);



/**
* Pack message DIAG_ANSW_IC_0x642.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32 ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_pack(
      uint8_t *dst_p,
      const  ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_t *src_p,
      size_t size);



/**
* Pack message DIAG_ANSW_BCM_0x644.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32 ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_pack(
      uint8_t *dst_p,
      const  ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_t *src_p,
      size_t size);



/**
* Pack message DIAG_ANSW_ECM_0x7e8.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32 ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_pack(
      uint8_t *dst_p,
      const  ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_t *src_p,
      size_t size);




/**
* Unpack message DIAG_ANS_ABS_0x629.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_diag_ans_abs_0x629_unpack(
      ch1raaacanmessagestandardv1can1draft_diag_ans_abs_0x629_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message REQ_DIAG_ANS_IC_0x632.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_req_diag_ans_ic_0x632_unpack(
      ch1raaacanmessagestandardv1can1draft_req_diag_ans_ic_0x632_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message DIAG_ANSW_TCU_0x641.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_diag_answ_tcu_0x641_unpack(
      ch1raaacanmessagestandardv1can1draft_diag_answ_tcu_0x641_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message DIAG_ANS_IC_0x642.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_diag_ans_ic_0x642_unpack(
      ch1raaacanmessagestandardv1can1draft_diag_ans_ic_0x642_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message DIAG_ANS_BCM_0x644.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_diag_ans_bcm_0x644_unpack(
      ch1raaacanmessagestandardv1can1draft_diag_ans_bcm_0x644_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message DIAG_ANS_ECM_0x7e8.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_diag_ans_ecm_0x7e8_unpack(
      ch1raaacanmessagestandardv1can1draft_diag_ans_ecm_0x7e8_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message ECM_ENGINE_PARAMETER_0x130.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_unpack(
      ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message ABS_TRQ_REQ_0x142.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_unpack(
      ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message ECM_SENSOR_PARAMETER_0x131.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_unpack(
      ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message ABS_STATUS_0x205.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_abs_status_0x205_unpack(
      ch1raaacanmessagestandardv1can1draft_abs_status_0x205_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message ABS_VEHICLE_SPEED_0x206.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_abs_vehicle_speed_0x206_unpack(
      ch1raaacanmessagestandardv1can1draft_abs_vehicle_speed_0x206_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message ECM_ADDITIONAL_INFO_0x135.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_unpack(
      ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message REQ_DIAG_ANSW_TCU_0x631.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch2raaacanmessagestandardv1can2draft_req_diag_answ_tcu_0x631_unpack(
      ch2raaacanmessagestandardv1can2draft_req_diag_answ_tcu_0x631_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message REQ_DIAG_ANSW_IC_0x632.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch2raaacanmessagestandardv1can2draft_req_diag_answ_ic_0x632_unpack(
      ch2raaacanmessagestandardv1can2draft_req_diag_answ_ic_0x632_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message REQ_DIAG_ANSW_ABS_0x6f0.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch2raaacanmessagestandardv1can2draft_req_diag_answ_abs_0x6f0_unpack(
      ch2raaacanmessagestandardv1can2draft_req_diag_answ_abs_0x6f0_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message REQ_DIAG_ANSW_BCM_0x6f1.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch2raaacanmessagestandardv1can2draft_req_diag_answ_bcm_0x6f1_unpack(
      ch2raaacanmessagestandardv1can2draft_req_diag_answ_bcm_0x6f1_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message Functional_Diag_Request_0x7df.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch2raaacanmessagestandardv1can2draft_functional_diag_request_0x7df_unpack(
      ch2raaacanmessagestandardv1can2draft_functional_diag_request_0x7df_t *dst_p,
      const uint8_t *src_p,
      size_t size);

/**
* Unpack message REQ_DIAG_ANSW_ECM_0x7e0.
*
* @param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/
static sint32 ch2raaacanmessagestandardv1can2draft_req_diag_answ_ecm_0x7e0_unpack(
      ch2raaacanmessagestandardv1can2draft_req_diag_answ_ecm_0x7e0_t *dst_p,
      const uint8_t *src_p,
      size_t size);


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint64_t ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_req_diag_ans_tcu_1_0x631_s_encode(float64 value); 
static uint64_t ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_req_diag_ans_abs_1_0x6f0_s_encode(float64 value); 
static uint64_t ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_req_diag_ans_bcm_1_0x6f1_s_encode(float64 value); 
static uint64_t ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_req_diag_ans_ecm_1_0x7e0_s_encode(float64 value); 
static uint8_t ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_crc_info_0x321_s_encode(float64 value); 
static uint8_t ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_alive_counter_ic_info_0x321_s_encode(float64 value); 
static uint8_t ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_ss_tell_tell_error_0x321_s_encode(float64 value); 
static uint8_t ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_ss_tell_tell_status_0x321_s_encode(float64 value); 
static uint32_t ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_odo_signal_0x321_s_encode(float64 value); 
static uint8_t ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ambiant_light_data_0x321_s_encode(float64 value); 
static uint64_t ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_diagnostic_answer_abs_0x629_s_encode(float64 value); 
static uint64_t ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_diagnostic_answer_tcu_0x641_s_encode(float64 value); 
static uint64_t ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_diagnostic_answer_ic_0x642_s_encode(float64 value); 
static uint64_t ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_diagnostic_answer_bcm_0x644_s_encode(float64 value); 
static uint64_t ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_diagnostic_answer_ecm_0x7e8_s_encode(float64 value); 




/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64 ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_engine_speed_0x130_s_decode(uint16 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_engine_run_status_0x130_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_throttle_position_sensor_0x130_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_throttle_position_sensor_fault_0x130_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_remote_mobilize_immoblize_status_0x130_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_mil_0x130_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_alive_counter_ecm_sensor_0x131_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_ecm_crc_sensor_0x131_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_roll_over_detection_0x131_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_roll_over_detection_fault_status_0x131_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_side_stand_sensor_0x131_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_side_stand_sensor_fault_0x131_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_gear_position_sensor_0x131_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_gear_shift_advisory_0x131_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_engine_kill_switch_status_0x131_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_throttle_grip_sensor_0x131_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_distance_travelled_with_mil_0x135_s_decode(uint16 value);
static float64 ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_accumulat_fuel_inj_time_fuel_qty_0x135_s_decode(uint16 value);
static float64 ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_abs_crc_trq_0x142_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_alive_counter_abs_trq_0x142_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_torque_request_status_0x142_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_tc_telltale_status_0x142_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_trq_req_mtc_0x142_s_decode(sint16 value);
static float64 ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_trq_req_dtc_0x142_s_decode(sint16 value);
static float64 ch1raaacanmessagestandardv1can1draft_abs_status_0x205_status_abs_0x205_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_abs_status_0x205_abs_telltale_status_0x205_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_abs_vehicle_speed_0x206_vehicle_speed_0x206_s_decode(uint8 value);
static float64 ch1raaacanmessagestandardv1can1draft_diag_ans_abs_0x629_diagnostic_answer_abs_0x629_s_decode(uint64 value);
static float64 ch1raaacanmessagestandardv1can1draft_req_diag_ans_ic_0x632_req_diag_ans_ic_0x632_s_decode(uint64 value);
static float64 ch1raaacanmessagestandardv1can1draft_diag_answ_tcu_0x641_diagnostic_answer_tcu_0x641_s_decode(uint64 value);
static float64 ch1raaacanmessagestandardv1can1draft_diag_ans_ic_0x642_diagnostic_answer_ic_0x642_s_decode(uint64 value);
static float64 ch1raaacanmessagestandardv1can1draft_diag_ans_bcm_0x644_diagnostic_answer_bcm_0x644_s_decode(uint64 value);
static float64 ch1raaacanmessagestandardv1can1draft_diag_ans_ecm_0x7e8_diagnostic_answer_ecm_0x7e8_s_decode(uint64 value);
static float64 ch2raaacanmessagestandardv1can2draft_req_diag_answ_tcu_0x631_req_diag_ans_tcu_0x631_s_decode(uint64 value);
static float64 ch2raaacanmessagestandardv1can2draft_req_diag_answ_ic_0x632_req_diag_ans_ic_0x632_s_decode(uint64 value);
static float64 ch2raaacanmessagestandardv1can2draft_req_diag_answ_abs_0x6f0_req_diag_ans_abs_0x6f0_s_decode(uint64 value);
static float64 ch2raaacanmessagestandardv1can2draft_req_diag_answ_bcm_0x6f1_req_diag_ans_bcm_0x6f1_s_decode(uint64 value);
static float64 ch2raaacanmessagestandardv1can2draft_functional_diag_request_0x7df_functional_diagnostic_request_0x7df_s_decode(uint64 value);
static float64 ch2raaacanmessagestandardv1can2draft_req_diag_answ_ecm_0x7e0_req_diag_ans_ecm_0x7e0_s_decode(uint64 value);




/**
* Check that given signal is in allowed range.
*
* @param[in] value Signal to check.
*
@return true if in range, false otherwise.
*/
static boolean ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_crc_info_0x321_s_is_in_range(uint8 value);
static boolean ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_alive_counter_ic_info_0x321_s_is_in_range(uint8 value);
static boolean ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_ss_tell_tell_error_0x321_s_is_in_range(uint8 value);
static boolean ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_ss_tell_tell_status_0x321_s_is_in_range(uint8 value);
static boolean ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_odo_signal_0x321_s_is_in_range(uint32 value);
static boolean ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ambiant_light_data_0x321_s_is_in_range(uint8 value);
static boolean ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_req_diag_ans_tcu_1_0x631_s_is_in_range(uint64 value);
static boolean ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_req_diag_ans_abs_1_0x6f0_s_is_in_range(uint64 value);
static boolean ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_req_diag_ans_bcm_1_0x6f1_s_is_in_range(uint64 value);
static boolean ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_req_diag_ans_ecm_1_0x7e0_s_is_in_range(uint64 value);
static boolean ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_diagnostic_answer_abs_0x629_s_is_in_range(uint64 value);
static boolean ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_diagnostic_answer_tcu_0x641_s_is_in_range(uint64 value);
static boolean ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_diagnostic_answer_ic_0x642_s_is_in_range(uint64 value);
static boolean ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_diagnostic_answer_bcm_0x644_s_is_in_range(uint64 value);
static boolean ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_diagnostic_answer_ecm_0x7e8_s_is_in_range(uint64 value);


static inline uint8_t pack_left_shift_u8(    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value << shift) & mask);
}

static inline uint8_t pack_left_shift_u16(
    uint16_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value << shift) & mask);
}

static inline uint8_t pack_left_shift_u32(
    uint32_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value << shift) & mask);
}

static inline uint8_t pack_left_shift_u64(
    uint64_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value << shift) & mask);
}

static inline uint8_t pack_right_shift_u16(
    uint16_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value >> shift) & mask);
}

static inline uint8_t pack_right_shift_u32(
    uint32_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value >> shift) & mask);
}

static inline uint8_t pack_right_shift_u64(
    uint64_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value >> shift) & mask);
}

static inline uint16_t unpack_left_shift_u16(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint16_t)((uint16_t)(value & mask) << shift);
}

static inline uint32_t unpack_left_shift_u32(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint32_t)((uint32_t)(value & mask) << shift);
}

static inline uint64_t unpack_left_shift_u64(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint64_t)((uint64_t)(value & mask) << shift);
}

static inline uint8_t unpack_right_shift_u8(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value & mask) >> shift);
}

static inline uint16_t unpack_right_shift_u16(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint16_t)((uint16_t)(value & mask) >> shift);
}

static inline uint32_t unpack_right_shift_u32(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint32_t)((uint32_t)(value & mask) >> shift);
}

static inline uint64_t unpack_right_shift_u64(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint64_t)((uint64_t)(value & mask) >> shift);
}
#if 0
static inline uint8_t pack_left_shift_u64(    uint64_t value,
    uint8_t shift,
    uint8_t mask)
{
    return (uint8_t)((uint8_t)(value << shift) & mask);
}

#endif


/**********************************************************************************************************************
                                    F U N C T I O N S    D E F  I N A T I O N S                        
**********************************************************************************************************************/

/**
* Pack message IC_INFO_MSG_0x321.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32  ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_pack(
    uint8_t *dst_p,
    const  ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8u);

    dst_p[0] |= pack_left_shift_u8(src_p->ic_crc_info_0x321_s, 0u, 0xffu);
    dst_p[1] |= pack_left_shift_u8(src_p->alive_counter_ic_info_0x321_s, 0u, 0x0fu);
    dst_p[1] |= pack_left_shift_u8(src_p->ic_ss_tell_tell_error_0x321_s, 4u, 0x30u);
    dst_p[1] |= pack_left_shift_u8(src_p->ic_ss_tell_tell_status_0x321_s, 6u, 0x40u);
    dst_p[2] |= pack_left_shift_u32(src_p->odo_signal_0x321_s, 0u, 0xffu);
    dst_p[3] |= pack_right_shift_u32(src_p->odo_signal_0x321_s, 8u, 0xffu);
    dst_p[4] |= pack_right_shift_u32(src_p->odo_signal_0x321_s, 16u, 0x0fu);
    dst_p[5] |= pack_left_shift_u8(src_p->ambiant_light_data_0x321_s, 0u, 0x03u);

    return (8);
}
/**
* Pack message REQ_DIAGN_ANS_TCU_0x631.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_pack(
    uint8_t *dst_p,
    const  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8u);

    dst_p[0] |= pack_left_shift_u64(src_p->req_diag_ans_tcu_1_0x631_s, 0u, 0xffu);
    dst_p[1] |= pack_right_shift_u64(src_p->req_diag_ans_tcu_1_0x631_s, 8u, 0xffu);
    dst_p[2] |= pack_right_shift_u64(src_p->req_diag_ans_tcu_1_0x631_s, 16u, 0xffu);
    dst_p[3] |= pack_right_shift_u64(src_p->req_diag_ans_tcu_1_0x631_s, 24u, 0xffu);
    dst_p[4] |= pack_right_shift_u64(src_p->req_diag_ans_tcu_1_0x631_s, 32u, 0xffu);
    dst_p[5] |= pack_right_shift_u64(src_p->req_diag_ans_tcu_1_0x631_s, 40u, 0xffu);
    dst_p[6] |= pack_right_shift_u64(src_p->req_diag_ans_tcu_1_0x631_s, 48u, 0xffu);
    dst_p[7] |= pack_right_shift_u64(src_p->req_diag_ans_tcu_1_0x631_s, 56u, 0xffu);

    return (8);
}
/**
* Pack message REQ_DIAGN_ANS_ABS_0x6f0.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_pack(
    uint8_t *dst_p,
    const  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8u);

    dst_p[0] |= pack_left_shift_u64(src_p->req_diag_ans_abs_1_0x6f0_s, 0u, 0xffu);
    dst_p[1] |= pack_right_shift_u64(src_p->req_diag_ans_abs_1_0x6f0_s, 8u, 0xffu);
    dst_p[2] |= pack_right_shift_u64(src_p->req_diag_ans_abs_1_0x6f0_s, 16u, 0xffu);
    dst_p[3] |= pack_right_shift_u64(src_p->req_diag_ans_abs_1_0x6f0_s, 24u, 0xffu);
    dst_p[4] |= pack_right_shift_u64(src_p->req_diag_ans_abs_1_0x6f0_s, 32u, 0xffu);
    dst_p[5] |= pack_right_shift_u64(src_p->req_diag_ans_abs_1_0x6f0_s, 40u, 0xffu);
    dst_p[6] |= pack_right_shift_u64(src_p->req_diag_ans_abs_1_0x6f0_s, 48u, 0xffu);
    dst_p[7] |= pack_right_shift_u64(src_p->req_diag_ans_abs_1_0x6f0_s, 56u, 0xffu);

    return (8);
}
/**
* Pack message REQ_DIAGN_ANS_BCM_0x6f1.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_pack(
    uint8_t *dst_p,
    const  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8u);

    dst_p[0] |= pack_left_shift_u64(src_p->req_diag_ans_bcm_1_0x6f1_s, 0u, 0xffu);
    dst_p[1] |= pack_right_shift_u64(src_p->req_diag_ans_bcm_1_0x6f1_s, 8u, 0xffu);
    dst_p[2] |= pack_right_shift_u64(src_p->req_diag_ans_bcm_1_0x6f1_s, 16u, 0xffu);
    dst_p[3] |= pack_right_shift_u64(src_p->req_diag_ans_bcm_1_0x6f1_s, 24u, 0xffu);
    dst_p[4] |= pack_right_shift_u64(src_p->req_diag_ans_bcm_1_0x6f1_s, 32u, 0xffu);
    dst_p[5] |= pack_right_shift_u64(src_p->req_diag_ans_bcm_1_0x6f1_s, 40u, 0xffu);
    dst_p[6] |= pack_right_shift_u64(src_p->req_diag_ans_bcm_1_0x6f1_s, 48u, 0xffu);
    dst_p[7] |= pack_right_shift_u64(src_p->req_diag_ans_bcm_1_0x6f1_s, 56u, 0xffu);

    return (8);
}
/**
* Pack message REQ_DIAGN_ANS_ECM_0x7e0.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_pack(
    uint8_t *dst_p,
    const  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8u);

    dst_p[0] |= pack_left_shift_u64(src_p->req_diag_ans_ecm_1_0x7e0_s, 0u, 0xffu);
    dst_p[1] |= pack_right_shift_u64(src_p->req_diag_ans_ecm_1_0x7e0_s, 8u, 0xffu);
    dst_p[2] |= pack_right_shift_u64(src_p->req_diag_ans_ecm_1_0x7e0_s, 16u, 0xffu);
    dst_p[3] |= pack_right_shift_u64(src_p->req_diag_ans_ecm_1_0x7e0_s, 24u, 0xffu);
    dst_p[4] |= pack_right_shift_u64(src_p->req_diag_ans_ecm_1_0x7e0_s, 32u, 0xffu);
    dst_p[5] |= pack_right_shift_u64(src_p->req_diag_ans_ecm_1_0x7e0_s, 40u, 0xffu);
    dst_p[6] |= pack_right_shift_u64(src_p->req_diag_ans_ecm_1_0x7e0_s, 48u, 0xffu);
    dst_p[7] |= pack_right_shift_u64(src_p->req_diag_ans_ecm_1_0x7e0_s, 56u, 0xffu);

    return (8);
}
/**
* Pack message DIAG_ANSW_ABS_0x629.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32  ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_pack(
    uint8_t *dst_p,
    const  ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8u);

    dst_p[0] |= pack_left_shift_u64(src_p->diagnostic_answer_abs_0x629_s, 0u, 0xffu);
    dst_p[1] |= pack_right_shift_u64(src_p->diagnostic_answer_abs_0x629_s, 8u, 0xffu);
    dst_p[2] |= pack_right_shift_u64(src_p->diagnostic_answer_abs_0x629_s, 16u, 0xffu);
    dst_p[3] |= pack_right_shift_u64(src_p->diagnostic_answer_abs_0x629_s, 24u, 0xffu);
    dst_p[4] |= pack_right_shift_u64(src_p->diagnostic_answer_abs_0x629_s, 32u, 0xffu);
    dst_p[5] |= pack_right_shift_u64(src_p->diagnostic_answer_abs_0x629_s, 40u, 0xffu);
    dst_p[6] |= pack_right_shift_u64(src_p->diagnostic_answer_abs_0x629_s, 48u, 0xffu);
    dst_p[7] |= pack_right_shift_u64(src_p->diagnostic_answer_abs_0x629_s, 56u, 0xffu);

    return (8);
}
/**
* Pack message DIA_ANSW_TCU_0x641.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32  ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_pack(
    uint8_t *dst_p,
    const  ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8u);

    dst_p[0] |= pack_left_shift_u64(src_p->diagnostic_answer_tcu_0x641_s, 0u, 0xffu);
    dst_p[1] |= pack_right_shift_u64(src_p->diagnostic_answer_tcu_0x641_s, 8u, 0xffu);
    dst_p[2] |= pack_right_shift_u64(src_p->diagnostic_answer_tcu_0x641_s, 16u, 0xffu);
    dst_p[3] |= pack_right_shift_u64(src_p->diagnostic_answer_tcu_0x641_s, 24u, 0xffu);
    dst_p[4] |= pack_right_shift_u64(src_p->diagnostic_answer_tcu_0x641_s, 32u, 0xffu);
    dst_p[5] |= pack_right_shift_u64(src_p->diagnostic_answer_tcu_0x641_s, 40u, 0xffu);
    dst_p[6] |= pack_right_shift_u64(src_p->diagnostic_answer_tcu_0x641_s, 48u, 0xffu);
    dst_p[7] |= pack_right_shift_u64(src_p->diagnostic_answer_tcu_0x641_s, 56u, 0xffu);

    return (8);
}
/**
* Pack message DIAG_ANSW_IC_0x642.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32  ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_pack(
    uint8_t *dst_p,
    const  ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8u);

    dst_p[0] |= pack_left_shift_u64(src_p->diagnostic_answer_ic_0x642_s, 0u, 0xffu);
    dst_p[1] |= pack_right_shift_u64(src_p->diagnostic_answer_ic_0x642_s, 8u, 0xffu);
    dst_p[2] |= pack_right_shift_u64(src_p->diagnostic_answer_ic_0x642_s, 16u, 0xffu);
    dst_p[3] |= pack_right_shift_u64(src_p->diagnostic_answer_ic_0x642_s, 24u, 0xffu);
    dst_p[4] |= pack_right_shift_u64(src_p->diagnostic_answer_ic_0x642_s, 32u, 0xffu);
    dst_p[5] |= pack_right_shift_u64(src_p->diagnostic_answer_ic_0x642_s, 40u, 0xffu);
    dst_p[6] |= pack_right_shift_u64(src_p->diagnostic_answer_ic_0x642_s, 48u, 0xffu);
    dst_p[7] |= pack_right_shift_u64(src_p->diagnostic_answer_ic_0x642_s, 56u, 0xffu);

    return (8);
}
/**
* Pack message DIAG_ANSW_BCM_0x644.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32  ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_pack(
    uint8_t *dst_p,
    const  ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8u);

    dst_p[0] |= pack_left_shift_u64(src_p->diagnostic_answer_bcm_0x644_s, 0u, 0xffu);
    dst_p[1] |= pack_right_shift_u64(src_p->diagnostic_answer_bcm_0x644_s, 8u, 0xffu);
    dst_p[2] |= pack_right_shift_u64(src_p->diagnostic_answer_bcm_0x644_s, 16u, 0xffu);
    dst_p[3] |= pack_right_shift_u64(src_p->diagnostic_answer_bcm_0x644_s, 24u, 0xffu);
    dst_p[4] |= pack_right_shift_u64(src_p->diagnostic_answer_bcm_0x644_s, 32u, 0xffu);
    dst_p[5] |= pack_right_shift_u64(src_p->diagnostic_answer_bcm_0x644_s, 40u, 0xffu);
    dst_p[6] |= pack_right_shift_u64(src_p->diagnostic_answer_bcm_0x644_s, 48u, 0xffu);
    dst_p[7] |= pack_right_shift_u64(src_p->diagnostic_answer_bcm_0x644_s, 56u, 0xffu);

    return (8);
}
/**
* Pack message DIAG_ANSW_ECM_0x7e8.
*
* @param[out] dst_p Buffer to pack the message into.
* @param[in] src_p Data to pack.
* @param[in] size Size of dst_p.
*
* @return Size of packed data, or negative error code.
*/
static sint32  ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_pack(
    uint8_t *dst_p,
    const  ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(&dst_p[0], 0, 8u);

    dst_p[0] |= pack_left_shift_u64(src_p->diagnostic_answer_ecm_0x7e8_s, 0u, 0xffu);
    dst_p[1] |= pack_right_shift_u64(src_p->diagnostic_answer_ecm_0x7e8_s, 8u, 0xffu);
    dst_p[2] |= pack_right_shift_u64(src_p->diagnostic_answer_ecm_0x7e8_s, 16u, 0xffu);
    dst_p[3] |= pack_right_shift_u64(src_p->diagnostic_answer_ecm_0x7e8_s, 24u, 0xffu);
    dst_p[4] |= pack_right_shift_u64(src_p->diagnostic_answer_ecm_0x7e8_s, 32u, 0xffu);
    dst_p[5] |= pack_right_shift_u64(src_p->diagnostic_answer_ecm_0x7e8_s, 40u, 0xffu);
    dst_p[6] |= pack_right_shift_u64(src_p->diagnostic_answer_ecm_0x7e8_s, 48u, 0xffu);
    dst_p[7] |= pack_right_shift_u64(src_p->diagnostic_answer_ecm_0x7e8_s, 56u, 0xffu);

    return (8);
}

/**
* Unpack message ECM_ENGINE_PARAMETER_0x130.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_unpack(
     ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->engine_speed_0x130_s |= unpack_right_shift_u16(src_p[0], 0u, 0xffu);
    dst_p->engine_speed_0x130_s |= unpack_left_shift_u16(src_p[1], 8u, 0xffu);
    dst_p->engine_run_status_0x130_s |= unpack_right_shift_u8(src_p[4], 0u, 0x01u);
    dst_p->throttle_position_sensor_0x130_s |= unpack_right_shift_u8(src_p[5], 0u, 0xffu);
    dst_p->throttle_position_sensor_fault_0x130_s |= unpack_right_shift_u8(src_p[6], 1u, 0x02u);
    dst_p->remote_mobilize_immoblize_status_0x130_s |= unpack_right_shift_u8(src_p[7], 2u, 0x04u);
    dst_p->mil_0x130_s |= unpack_right_shift_u8(src_p[7], 3u, 0x18u);

    return (0);
}
/**
* Unpack message ECM_SENSOR_PARAMETER_0x131.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_unpack(
     ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->alive_counter_ecm_sensor_0x131_s |= unpack_right_shift_u8(src_p[0], 2u, 0x3cu);
    dst_p->ecm_crc_sensor_0x131_s |= unpack_right_shift_u8(src_p[2], 0u, 0xffu);
    dst_p->roll_over_detection_0x131_s |= unpack_right_shift_u8(src_p[3], 2u, 0x04u);
    dst_p->roll_over_detection_fault_status_0x131_s |= unpack_right_shift_u8(src_p[3], 3u, 0x08u);
    dst_p->side_stand_sensor_0x131_s |= unpack_right_shift_u8(src_p[3], 4u, 0x10u);
    dst_p->side_stand_sensor_fault_0x131_s |= unpack_right_shift_u8(src_p[3], 5u, 0x20u);
    dst_p->gear_position_sensor_0x131_s |= unpack_right_shift_u8(src_p[4], 0u, 0x07u);
    dst_p->gear_shift_advisory_0x131_s |= unpack_right_shift_u8(src_p[4], 3u, 0x18u);
    dst_p->engine_kill_switch_status_0x131_s |= unpack_right_shift_u8(src_p[4], 5u, 0x20u);
    dst_p->throttle_grip_sensor_0x131_s |= unpack_right_shift_u8(src_p[7], 0u, 0xffu);

    return (0);
}
/**
* Unpack message ECM_ADDITIONAL_INFO_0x135.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_unpack(
     ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->distance_travelled_with_mil_0x135_s |= unpack_right_shift_u16(src_p[2], 0u, 0xffu);
    dst_p->distance_travelled_with_mil_0x135_s |= unpack_left_shift_u16(src_p[3], 8u, 0xffu);
    dst_p->accumulat_fuel_inj_time_fuel_qty_0x135_s |= unpack_right_shift_u16(src_p[6], 0u, 0xffu);
    dst_p->accumulat_fuel_inj_time_fuel_qty_0x135_s |= unpack_left_shift_u16(src_p[7], 8u, 0xffu);

    return (0);
}
/**
* Unpack message ABS_TRQ_REQ_0x142.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_unpack(
     ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    uint16_t trq_req_dtc_0x142_s;
    uint16_t trq_req_mtc_0x142_s;

    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->abs_crc_trq_0x142_s |= unpack_right_shift_u8(src_p[0], 0u, 0xffu);
    dst_p->alive_counter_abs_trq_0x142_s |= unpack_right_shift_u8(src_p[1], 0u, 0x0fu);
    dst_p->torque_request_status_0x142_s |= unpack_right_shift_u8(src_p[1], 4u, 0x30u);
    dst_p->tc_telltale_status_0x142_s |= unpack_right_shift_u8(src_p[1], 6u, 0xc0u);
    trq_req_mtc_0x142_s = 0u;
    trq_req_mtc_0x142_s |= unpack_right_shift_u16(src_p[2], 0u, 0xffu);
    trq_req_mtc_0x142_s |= unpack_left_shift_u16(src_p[3], 8u, 0x0fu);

    if ((trq_req_mtc_0x142_s & (1u << 11)) != 0u) {
        trq_req_mtc_0x142_s |= 0xf000u;
    }

    dst_p->trq_req_mtc_0x142_s = (int16_t)trq_req_mtc_0x142_s;
    trq_req_dtc_0x142_s = 0u;
    trq_req_dtc_0x142_s |= unpack_right_shift_u16(src_p[4], 0u, 0xffu);
    trq_req_dtc_0x142_s |= unpack_left_shift_u16(src_p[5], 8u, 0x0fu);

    if ((trq_req_dtc_0x142_s & (1u << 11)) != 0u) {
        trq_req_dtc_0x142_s |= 0xf000u;
    }

    dst_p->trq_req_dtc_0x142_s = (int16_t)trq_req_dtc_0x142_s;

    return (0);
}
/**
* Unpack message ABS_STATUS_0x205.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch1raaacanmessagestandardv1can1draft_abs_status_0x205_unpack(
     ch1raaacanmessagestandardv1can1draft_abs_status_0x205_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->status_abs_0x205_s |= unpack_right_shift_u8(src_p[1], 0u, 0x03u);
    dst_p->abs_telltale_status_0x205_s |= unpack_right_shift_u8(src_p[1], 2u, 0x0cu);

    return (0);
}
/**
* Unpack message ABS_VEHICLE_SPEED_0x206.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch1raaacanmessagestandardv1can1draft_abs_vehicle_speed_0x206_unpack(
     ch1raaacanmessagestandardv1can1draft_abs_vehicle_speed_0x206_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->vehicle_speed_0x206_s |= unpack_right_shift_u8(src_p[2], 0u, 0xffu);

    return (0);
}
/**
* Unpack message DIAG_ANS_ABS_0x629.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch1raaacanmessagestandardv1can1draft_diag_ans_abs_0x629_unpack(
     ch1raaacanmessagestandardv1can1draft_diag_ans_abs_0x629_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->diagnostic_answer_abs_0x629_s |= unpack_right_shift_u64(src_p[0], 0u, 0xffu);
    dst_p->diagnostic_answer_abs_0x629_s |= unpack_left_shift_u64(src_p[1], 8u, 0xffu);
    dst_p->diagnostic_answer_abs_0x629_s |= unpack_left_shift_u64(src_p[2], 16u, 0xffu);
    dst_p->diagnostic_answer_abs_0x629_s |= unpack_left_shift_u64(src_p[3], 24u, 0xffu);
    dst_p->diagnostic_answer_abs_0x629_s |= unpack_left_shift_u64(src_p[4], 32u, 0xffu);
    dst_p->diagnostic_answer_abs_0x629_s |= unpack_left_shift_u64(src_p[5], 40u, 0xffu);
    dst_p->diagnostic_answer_abs_0x629_s |= unpack_left_shift_u64(src_p[6], 48u, 0xffu);
    dst_p->diagnostic_answer_abs_0x629_s |= unpack_left_shift_u64(src_p[7], 56u, 0xffu);

    return (0);
}
/**
* Unpack message REQ_DIAG_ANS_IC_0x632.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch1raaacanmessagestandardv1can1draft_req_diag_ans_ic_0x632_unpack(
     ch1raaacanmessagestandardv1can1draft_req_diag_ans_ic_0x632_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->req_diag_ans_ic_0x632_s |= unpack_right_shift_u64(src_p[0], 0u, 0xffu);
    dst_p->req_diag_ans_ic_0x632_s |= unpack_left_shift_u64(src_p[1], 8u, 0xffu);
    dst_p->req_diag_ans_ic_0x632_s |= unpack_left_shift_u64(src_p[2], 16u, 0xffu);
    dst_p->req_diag_ans_ic_0x632_s |= unpack_left_shift_u64(src_p[3], 24u, 0xffu);
    dst_p->req_diag_ans_ic_0x632_s |= unpack_left_shift_u64(src_p[4], 32u, 0xffu);
    dst_p->req_diag_ans_ic_0x632_s |= unpack_left_shift_u64(src_p[5], 40u, 0xffu);
    dst_p->req_diag_ans_ic_0x632_s |= unpack_left_shift_u64(src_p[6], 48u, 0xffu);
    dst_p->req_diag_ans_ic_0x632_s |= unpack_left_shift_u64(src_p[7], 56u, 0xffu);

    return (0);
}
/**
* Unpack message DIAG_ANSW_TCU_0x641.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch1raaacanmessagestandardv1can1draft_diag_answ_tcu_0x641_unpack(
     ch1raaacanmessagestandardv1can1draft_diag_answ_tcu_0x641_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->diagnostic_answer_tcu_0x641_s |= unpack_right_shift_u64(src_p[0], 0u, 0xffu);
    dst_p->diagnostic_answer_tcu_0x641_s |= unpack_left_shift_u64(src_p[1], 8u, 0xffu);
    dst_p->diagnostic_answer_tcu_0x641_s |= unpack_left_shift_u64(src_p[2], 16u, 0xffu);
    dst_p->diagnostic_answer_tcu_0x641_s |= unpack_left_shift_u64(src_p[3], 24u, 0xffu);
    dst_p->diagnostic_answer_tcu_0x641_s |= unpack_left_shift_u64(src_p[4], 32u, 0xffu);
    dst_p->diagnostic_answer_tcu_0x641_s |= unpack_left_shift_u64(src_p[5], 40u, 0xffu);
    dst_p->diagnostic_answer_tcu_0x641_s |= unpack_left_shift_u64(src_p[6], 48u, 0xffu);
    dst_p->diagnostic_answer_tcu_0x641_s |= unpack_left_shift_u64(src_p[7], 56u, 0xffu);

    return (0);
}
/**
* Unpack message DIAG_ANS_IC_0x642.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch1raaacanmessagestandardv1can1draft_diag_ans_ic_0x642_unpack(
     ch1raaacanmessagestandardv1can1draft_diag_ans_ic_0x642_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->diagnostic_answer_ic_0x642_s |= unpack_right_shift_u64(src_p[0], 0u, 0xffu);
    dst_p->diagnostic_answer_ic_0x642_s |= unpack_left_shift_u64(src_p[1], 8u, 0xffu);
    dst_p->diagnostic_answer_ic_0x642_s |= unpack_left_shift_u64(src_p[2], 16u, 0xffu);
    dst_p->diagnostic_answer_ic_0x642_s |= unpack_left_shift_u64(src_p[3], 24u, 0xffu);
    dst_p->diagnostic_answer_ic_0x642_s |= unpack_left_shift_u64(src_p[4], 32u, 0xffu);
    dst_p->diagnostic_answer_ic_0x642_s |= unpack_left_shift_u64(src_p[5], 40u, 0xffu);
    dst_p->diagnostic_answer_ic_0x642_s |= unpack_left_shift_u64(src_p[6], 48u, 0xffu);
    dst_p->diagnostic_answer_ic_0x642_s |= unpack_left_shift_u64(src_p[7], 56u, 0xffu);

    return (0);
}
/**
* Unpack message DIAG_ANS_BCM_0x644.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch1raaacanmessagestandardv1can1draft_diag_ans_bcm_0x644_unpack(
     ch1raaacanmessagestandardv1can1draft_diag_ans_bcm_0x644_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->diagnostic_answer_bcm_0x644_s |= unpack_right_shift_u64(src_p[0], 0u, 0xffu);
    dst_p->diagnostic_answer_bcm_0x644_s |= unpack_left_shift_u64(src_p[1], 8u, 0xffu);
    dst_p->diagnostic_answer_bcm_0x644_s |= unpack_left_shift_u64(src_p[2], 16u, 0xffu);
    dst_p->diagnostic_answer_bcm_0x644_s |= unpack_left_shift_u64(src_p[3], 24u, 0xffu);
    dst_p->diagnostic_answer_bcm_0x644_s |= unpack_left_shift_u64(src_p[4], 32u, 0xffu);
    dst_p->diagnostic_answer_bcm_0x644_s |= unpack_left_shift_u64(src_p[5], 40u, 0xffu);
    dst_p->diagnostic_answer_bcm_0x644_s |= unpack_left_shift_u64(src_p[6], 48u, 0xffu);
    dst_p->diagnostic_answer_bcm_0x644_s |= unpack_left_shift_u64(src_p[7], 56u, 0xffu);

    return (0);
}
/**
* Unpack message DIAG_ANS_ECM_0x7e8.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch1raaacanmessagestandardv1can1draft_diag_ans_ecm_0x7e8_unpack(
     ch1raaacanmessagestandardv1can1draft_diag_ans_ecm_0x7e8_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->diagnostic_answer_ecm_0x7e8_s |= unpack_right_shift_u64(src_p[0], 0u, 0xffu);
    dst_p->diagnostic_answer_ecm_0x7e8_s |= unpack_left_shift_u64(src_p[1], 8u, 0xffu);
    dst_p->diagnostic_answer_ecm_0x7e8_s |= unpack_left_shift_u64(src_p[2], 16u, 0xffu);
    dst_p->diagnostic_answer_ecm_0x7e8_s |= unpack_left_shift_u64(src_p[3], 24u, 0xffu);
    dst_p->diagnostic_answer_ecm_0x7e8_s |= unpack_left_shift_u64(src_p[4], 32u, 0xffu);
    dst_p->diagnostic_answer_ecm_0x7e8_s |= unpack_left_shift_u64(src_p[5], 40u, 0xffu);
    dst_p->diagnostic_answer_ecm_0x7e8_s |= unpack_left_shift_u64(src_p[6], 48u, 0xffu);
    dst_p->diagnostic_answer_ecm_0x7e8_s |= unpack_left_shift_u64(src_p[7], 56u, 0xffu);

    return (0);
}
/**
* Unpack message REQ_DIAG_ANSW_TCU_0x631.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch2raaacanmessagestandardv1can2draft_req_diag_answ_tcu_0x631_unpack(
     ch2raaacanmessagestandardv1can2draft_req_diag_answ_tcu_0x631_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->req_diag_ans_tcu_0x631_s |= unpack_right_shift_u64(src_p[0], 0u, 0xffu);
    dst_p->req_diag_ans_tcu_0x631_s |= unpack_left_shift_u64(src_p[1], 8u, 0xffu);
    dst_p->req_diag_ans_tcu_0x631_s |= unpack_left_shift_u64(src_p[2], 16u, 0xffu);
    dst_p->req_diag_ans_tcu_0x631_s |= unpack_left_shift_u64(src_p[3], 24u, 0xffu);
    dst_p->req_diag_ans_tcu_0x631_s |= unpack_left_shift_u64(src_p[4], 32u, 0xffu);
    dst_p->req_diag_ans_tcu_0x631_s |= unpack_left_shift_u64(src_p[5], 40u, 0xffu);
    dst_p->req_diag_ans_tcu_0x631_s |= unpack_left_shift_u64(src_p[6], 48u, 0xffu);
    dst_p->req_diag_ans_tcu_0x631_s |= unpack_left_shift_u64(src_p[7], 56u, 0xffu);

    return (0);
}
/**
* Unpack message REQ_DIAG_ANSW_IC_0x632.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch2raaacanmessagestandardv1can2draft_req_diag_answ_ic_0x632_unpack(
     ch2raaacanmessagestandardv1can2draft_req_diag_answ_ic_0x632_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->req_diag_ans_ic_0x632_s |= unpack_right_shift_u64(src_p[0], 0u, 0xffu);
    dst_p->req_diag_ans_ic_0x632_s |= unpack_left_shift_u64(src_p[1], 8u, 0xffu);
    dst_p->req_diag_ans_ic_0x632_s |= unpack_left_shift_u64(src_p[2], 16u, 0xffu);
    dst_p->req_diag_ans_ic_0x632_s |= unpack_left_shift_u64(src_p[3], 24u, 0xffu);
    dst_p->req_diag_ans_ic_0x632_s |= unpack_left_shift_u64(src_p[4], 32u, 0xffu);
    dst_p->req_diag_ans_ic_0x632_s |= unpack_left_shift_u64(src_p[5], 40u, 0xffu);
    dst_p->req_diag_ans_ic_0x632_s |= unpack_left_shift_u64(src_p[6], 48u, 0xffu);
    dst_p->req_diag_ans_ic_0x632_s |= unpack_left_shift_u64(src_p[7], 56u, 0xffu);

    return (0);
}
/**
* Unpack message REQ_DIAG_ANSW_ABS_0x6f0.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch2raaacanmessagestandardv1can2draft_req_diag_answ_abs_0x6f0_unpack(
     ch2raaacanmessagestandardv1can2draft_req_diag_answ_abs_0x6f0_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->req_diag_ans_abs_0x6f0_s |= unpack_right_shift_u64(src_p[0], 0u, 0xffu);
    dst_p->req_diag_ans_abs_0x6f0_s |= unpack_left_shift_u64(src_p[1], 8u, 0xffu);
    dst_p->req_diag_ans_abs_0x6f0_s |= unpack_left_shift_u64(src_p[2], 16u, 0xffu);
    dst_p->req_diag_ans_abs_0x6f0_s |= unpack_left_shift_u64(src_p[3], 24u, 0xffu);
    dst_p->req_diag_ans_abs_0x6f0_s |= unpack_left_shift_u64(src_p[4], 32u, 0xffu);
    dst_p->req_diag_ans_abs_0x6f0_s |= unpack_left_shift_u64(src_p[5], 40u, 0xffu);
    dst_p->req_diag_ans_abs_0x6f0_s |= unpack_left_shift_u64(src_p[6], 48u, 0xffu);
    dst_p->req_diag_ans_abs_0x6f0_s |= unpack_left_shift_u64(src_p[7], 56u, 0xffu);

    return (0);
}
/**
* Unpack message REQ_DIAG_ANSW_BCM_0x6f1.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch2raaacanmessagestandardv1can2draft_req_diag_answ_bcm_0x6f1_unpack(
     ch2raaacanmessagestandardv1can2draft_req_diag_answ_bcm_0x6f1_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->req_diag_ans_bcm_0x6f1_s |= unpack_right_shift_u64(src_p[0], 0u, 0xffu);
    dst_p->req_diag_ans_bcm_0x6f1_s |= unpack_left_shift_u64(src_p[1], 8u, 0xffu);
    dst_p->req_diag_ans_bcm_0x6f1_s |= unpack_left_shift_u64(src_p[2], 16u, 0xffu);
    dst_p->req_diag_ans_bcm_0x6f1_s |= unpack_left_shift_u64(src_p[3], 24u, 0xffu);
    dst_p->req_diag_ans_bcm_0x6f1_s |= unpack_left_shift_u64(src_p[4], 32u, 0xffu);
    dst_p->req_diag_ans_bcm_0x6f1_s |= unpack_left_shift_u64(src_p[5], 40u, 0xffu);
    dst_p->req_diag_ans_bcm_0x6f1_s |= unpack_left_shift_u64(src_p[6], 48u, 0xffu);
    dst_p->req_diag_ans_bcm_0x6f1_s |= unpack_left_shift_u64(src_p[7], 56u, 0xffu);

    return (0);
}
/**
* Unpack message Functional_Diag_Request_0x7df.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch2raaacanmessagestandardv1can2draft_functional_diag_request_0x7df_unpack(
     ch2raaacanmessagestandardv1can2draft_functional_diag_request_0x7df_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->functional_diagnostic_request_0x7df_s |= unpack_right_shift_u64(src_p[0], 0u, 0xffu);
    dst_p->functional_diagnostic_request_0x7df_s |= unpack_left_shift_u64(src_p[1], 8u, 0xffu);
    dst_p->functional_diagnostic_request_0x7df_s |= unpack_left_shift_u64(src_p[2], 16u, 0xffu);
    dst_p->functional_diagnostic_request_0x7df_s |= unpack_left_shift_u64(src_p[3], 24u, 0xffu);
    dst_p->functional_diagnostic_request_0x7df_s |= unpack_left_shift_u64(src_p[4], 32u, 0xffu);
    dst_p->functional_diagnostic_request_0x7df_s |= unpack_left_shift_u64(src_p[5], 40u, 0xffu);
    dst_p->functional_diagnostic_request_0x7df_s |= unpack_left_shift_u64(src_p[6], 48u, 0xffu);
    dst_p->functional_diagnostic_request_0x7df_s |= unpack_left_shift_u64(src_p[7], 56u, 0xffu);

    return (0);
}
/**
* Unpack message REQ_DIAG_ANSW_ECM_0x7e0.
*
*@param[out] dst_p Object to unpack the message into.
* @param[in] src_p Message to unpack.
* @param[in] size Size of src_p.
*
* @return zero(0) or negative error code.
*/ 
static sint32 ch2raaacanmessagestandardv1can2draft_req_diag_answ_ecm_0x7e0_unpack(
     ch2raaacanmessagestandardv1can2draft_req_diag_answ_ecm_0x7e0_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    if (size < 8u) {
        return (-EINVAL);
    }

    memset(dst_p, 0, sizeof(*dst_p));

    dst_p->req_diag_ans_ecm_0x7e0_s |= unpack_right_shift_u64(src_p[0], 0u, 0xffu);
    dst_p->req_diag_ans_ecm_0x7e0_s |= unpack_left_shift_u64(src_p[1], 8u, 0xffu);
    dst_p->req_diag_ans_ecm_0x7e0_s |= unpack_left_shift_u64(src_p[2], 16u, 0xffu);
    dst_p->req_diag_ans_ecm_0x7e0_s |= unpack_left_shift_u64(src_p[3], 24u, 0xffu);
    dst_p->req_diag_ans_ecm_0x7e0_s |= unpack_left_shift_u64(src_p[4], 32u, 0xffu);
    dst_p->req_diag_ans_ecm_0x7e0_s |= unpack_left_shift_u64(src_p[5], 40u, 0xffu);
    dst_p->req_diag_ans_ecm_0x7e0_s |= unpack_left_shift_u64(src_p[6], 48u, 0xffu);
    dst_p->req_diag_ans_ecm_0x7e0_s |= unpack_left_shift_u64(src_p[7], 56u, 0xffu);

    return (0);
}




/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint8_t ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_crc_info_0x321_s_encode(float64 value)
{
    return (uint8_t)(value);
}


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint8_t ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_alive_counter_ic_info_0x321_s_encode(float64 value)
{
    return (uint8_t)(value);
}


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint8_t ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_ss_tell_tell_error_0x321_s_encode(float64 value)
{
    return (uint8_t)(value);
}


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint8_t ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_ss_tell_tell_status_0x321_s_encode(float64 value)
{
    return (uint8_t)(value);
}


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint32_t ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_odo_signal_0x321_s_encode(float64 value)
{
    return (uint32_t)(value);
}


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint8_t ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ambiant_light_data_0x321_s_encode(float64 value)
{
    return (uint8_t)(value);
}


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint64_t ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_req_diag_ans_tcu_1_0x631_s_encode(float64 value)
{
    return (uint64_t)(value);
}


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint64_t ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_req_diag_ans_abs_1_0x6f0_s_encode(float64 value)
{
    return (uint64_t)(value);
}


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint64_t ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_req_diag_ans_bcm_1_0x6f1_s_encode(float64 value)
{
    return (uint64_t)(value);
}


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint64_t ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_req_diag_ans_ecm_1_0x7e0_s_encode(float64 value)
{
    return (uint64_t)(value);
}


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint64_t ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_diagnostic_answer_abs_0x629_s_encode(float64 value)
{
    return (uint64_t)(value);
}


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint64_t ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_diagnostic_answer_tcu_0x641_s_encode(float64 value)
{
    return (uint64_t)(value);
}


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint64_t ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_diagnostic_answer_ic_0x642_s_encode(float64 value)
{
    return (uint64_t)(value);
}


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint64_t ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_diagnostic_answer_bcm_0x644_s_encode(float64 value)
{
    return (uint64_t)(value);
}


/**
  * Encode given signal by applying scaling and offset
  * @param[in] value Signal to encode.
  * @return Encoded signal.
*/ 
static uint64_t ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_diagnostic_answer_ecm_0x7e8_s_encode(float64 value)
{
    return (uint64_t)(value);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_crc_info_0x321_s_is_in_range(uint8_t value)
{
    (void)value;

    return (true);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_alive_counter_ic_info_0x321_s_is_in_range(uint8_t value)
{
    return (value <= 15u);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_ss_tell_tell_error_0x321_s_is_in_range(uint8_t value)
{
    return (value <= 3u);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_ss_tell_tell_status_0x321_s_is_in_range(uint8_t value)
{
    return (value <= 1u);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_odo_signal_0x321_s_is_in_range(uint32_t value)
{
    return (value <= 999999u);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ambiant_light_data_0x321_s_is_in_range(uint8_t value)
{
    return (value <= 2u);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_req_diag_ans_tcu_1_0x631_s_is_in_range(uint64_t value)
{
    (void)value;

    return (true);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_req_diag_ans_abs_1_0x6f0_s_is_in_range(uint64_t value)
{
    (void)value;

    return (true);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_req_diag_ans_bcm_1_0x6f1_s_is_in_range(uint64_t value)
{
    (void)value;

    return (true);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_req_diag_ans_ecm_1_0x7e0_s_is_in_range(uint64_t value)
{
    (void)value;

    return (true);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_diagnostic_answer_abs_0x629_s_is_in_range(uint64_t value)
{
    return (value <= 255ull);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_diagnostic_answer_tcu_0x641_s_is_in_range(uint64_t value)
{
    return (value <= 255ull);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_diagnostic_answer_ic_0x642_s_is_in_range(uint64_t value)
{
    return (value <= 255ull);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_diagnostic_answer_bcm_0x644_s_is_in_range(uint64_t value)
{
    return (value <= 255ull);
}


/* 
  * Check that given signal is in allowed range.                                                                          
  * @param[in] value Signal to check.                                                                            
  * @return true if in range, false otherwise                                                                          
*/ 
static boolean  ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_diagnostic_answer_ecm_0x7e8_s_is_in_range(uint64_t value)
{
    return (value <= 255ull);
}




/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_engine_speed_0x130_s_decode(uint16_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_engine_run_status_0x130_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_throttle_position_sensor_0x130_s_decode(uint8_t value)
{
    return ((float64)value * 0.392);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_throttle_position_sensor_fault_0x130_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_remote_mobilize_immoblize_status_0x130_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_mil_0x130_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_alive_counter_ecm_sensor_0x131_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_ecm_crc_sensor_0x131_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_roll_over_detection_0x131_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_roll_over_detection_fault_status_0x131_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_side_stand_sensor_0x131_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_side_stand_sensor_fault_0x131_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_gear_position_sensor_0x131_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_gear_shift_advisory_0x131_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_engine_kill_switch_status_0x131_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_throttle_grip_sensor_0x131_s_decode(uint8_t value)
{
    return ((float64)value * 0.392156);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_distance_travelled_with_mil_0x135_s_decode(uint16_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_accumulat_fuel_inj_time_fuel_qty_0x135_s_decode(uint16_t value)
{
    return ((float64)value * 5.97E-7);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_abs_crc_trq_0x142_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_alive_counter_abs_trq_0x142_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_torque_request_status_0x142_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_tc_telltale_status_0x142_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_trq_req_mtc_0x142_s_decode(int16_t value)
{
    return ((float64)value * 0.2);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_trq_req_dtc_0x142_s_decode(int16_t value)
{
    return ((float64)value * 0.2);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_abs_status_0x205_status_abs_0x205_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_abs_status_0x205_abs_telltale_status_0x205_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_abs_vehicle_speed_0x206_vehicle_speed_0x206_s_decode(uint8_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_diag_ans_abs_0x629_diagnostic_answer_abs_0x629_s_decode(uint64_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_req_diag_ans_ic_0x632_req_diag_ans_ic_0x632_s_decode(uint64_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_diag_answ_tcu_0x641_diagnostic_answer_tcu_0x641_s_decode(uint64_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_diag_ans_ic_0x642_diagnostic_answer_ic_0x642_s_decode(uint64_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_diag_ans_bcm_0x644_diagnostic_answer_bcm_0x644_s_decode(uint64_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch1raaacanmessagestandardv1can1draft_diag_ans_ecm_0x7e8_diagnostic_answer_ecm_0x7e8_s_decode(uint64_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch2raaacanmessagestandardv1can2draft_req_diag_answ_tcu_0x631_req_diag_ans_tcu_0x631_s_decode(uint64_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch2raaacanmessagestandardv1can2draft_req_diag_answ_ic_0x632_req_diag_ans_ic_0x632_s_decode(uint64_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch2raaacanmessagestandardv1can2draft_req_diag_answ_abs_0x6f0_req_diag_ans_abs_0x6f0_s_decode(uint64_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch2raaacanmessagestandardv1can2draft_req_diag_answ_bcm_0x6f1_req_diag_ans_bcm_0x6f1_s_decode(uint64_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch2raaacanmessagestandardv1can2draft_functional_diag_request_0x7df_functional_diagnostic_request_0x7df_s_decode(uint64_t value)
{
    return ((float64)value);
}


/**
  * Decode given signal by applying scaling and offset
  * @param[in] value Signal to decode.
  * @return Decoded signal.
*/ 
static float64  ch2raaacanmessagestandardv1can2draft_req_diag_answ_ecm_0x7e0_req_diag_ans_ecm_0x7e0_s_decode(uint64_t value)
{
    return ((float64)value);
}




/* 
  * @Brief  : Updates signal IC_CRC_INFO_0x321_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_ic_crc_info_0x321_s(float64 data)
{
		 uint8_t ret;
		 uint8 fl_encoded_data;
		 static uint8_t fl_data[IC_INFO_MSG_0X321_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =255;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_crc_info_0x321_s_encode(fl_value);
		 if(ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_crc_info_0x321_s_is_in_range(fl_encoded_data))
		 {
			 ic_info_msg_0x321.ic_crc_info_0x321_s = fl_encoded_data;
			 (void)ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_pack(fl_data,&ic_info_msg_0x321,(size_t)IC_INFO_MSG_0X321_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[IC_CRC_INFO_0X321_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[IC_CRC_INFO_0X321_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( IC_INFO_MSG_0X321,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}


/* 
  * @Brief  : Updates signal Alive_Counter_IC_INFO_0x321_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_alive_counter_ic_info_0x321_s(float64 data)
{
		 uint8_t ret;
		 uint8 fl_encoded_data;
		 static uint8_t fl_data[IC_INFO_MSG_0X321_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =15;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_alive_counter_ic_info_0x321_s_encode(fl_value);
		 if(ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_alive_counter_ic_info_0x321_s_is_in_range(fl_encoded_data))
		 {
			 ic_info_msg_0x321.alive_counter_ic_info_0x321_s = fl_encoded_data;
			 (void)ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_pack(fl_data,&ic_info_msg_0x321,(size_t)IC_INFO_MSG_0X321_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[ALIVE_COUNTER_IC_INFO_0X321_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[ALIVE_COUNTER_IC_INFO_0X321_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( IC_INFO_MSG_0X321,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}


/* 
  * @Brief  : Updates signal IC_SS_TELL_TELL_ERROR_0x321_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_ic_ss_tell_tell_error_0x321_s(float64 data)
{
		 uint8_t ret;
		 uint8 fl_encoded_data;
		 static uint8_t fl_data[IC_INFO_MSG_0X321_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =3;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_ss_tell_tell_error_0x321_s_encode(fl_value);
		 if(ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_ss_tell_tell_error_0x321_s_is_in_range(fl_encoded_data))
		 {
			 ic_info_msg_0x321.ic_ss_tell_tell_error_0x321_s = fl_encoded_data;
			 (void)ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_pack(fl_data,&ic_info_msg_0x321,(size_t)IC_INFO_MSG_0X321_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[IC_SS_TELL_TELL_ERROR_0X321_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[IC_SS_TELL_TELL_ERROR_0X321_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( IC_INFO_MSG_0X321,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}


/* 
  * @Brief  : Updates signal IC_SS_TELL_TELL_STATUS_0x321_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_ic_ss_tell_tell_status_0x321_s(float64 data)
{
		 uint8_t ret;
		 uint8 fl_encoded_data;
		 static uint8_t fl_data[IC_INFO_MSG_0X321_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =1;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_ss_tell_tell_status_0x321_s_encode(fl_value);
		 if(ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ic_ss_tell_tell_status_0x321_s_is_in_range(fl_encoded_data))
		 {
			 ic_info_msg_0x321.ic_ss_tell_tell_status_0x321_s = fl_encoded_data;
			 (void)ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_pack(fl_data,&ic_info_msg_0x321,(size_t)IC_INFO_MSG_0X321_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[IC_SS_TELL_TELL_STATUS_0X321_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[IC_SS_TELL_TELL_STATUS_0X321_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( IC_INFO_MSG_0X321,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}


/* 
  * @Brief  : Updates signal ODO_Signal_0x321_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_odo_signal_0x321_s(float64 data)
{
		 uint8_t ret;
		 uint32 fl_encoded_data;
		 static uint8_t fl_data[IC_INFO_MSG_0X321_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =999999;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_odo_signal_0x321_s_encode(fl_value);
		 if(ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_odo_signal_0x321_s_is_in_range(fl_encoded_data))
		 {
			 ic_info_msg_0x321.odo_signal_0x321_s = fl_encoded_data;
			 (void)ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_pack(fl_data,&ic_info_msg_0x321,(size_t)IC_INFO_MSG_0X321_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[ODO_SIGNAL_0X321_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[ODO_SIGNAL_0X321_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( IC_INFO_MSG_0X321,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}


/* 
  * @Brief  : Updates signal Ambiant_Light_Data_0x321_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_ambiant_light_data_0x321_s(float64 data)
{
		 uint8_t ret;
		 uint8 fl_encoded_data;
		 static uint8_t fl_data[IC_INFO_MSG_0X321_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =2;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ambiant_light_data_0x321_s_encode(fl_value);
		 if(ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_ambiant_light_data_0x321_s_is_in_range(fl_encoded_data))
		 {
			 ic_info_msg_0x321.ambiant_light_data_0x321_s = fl_encoded_data;
			 (void)ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_pack(fl_data,&ic_info_msg_0x321,(size_t)IC_INFO_MSG_0X321_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[AMBIANT_LIGHT_DATA_0X321_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[AMBIANT_LIGHT_DATA_0X321_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( IC_INFO_MSG_0X321,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}




/* 
  * @Brief  : Returns the transmission status of IC_CRC_INFO_0x321_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_ic_crc_info_0x321_s_cbk_0x321(void)
{
  return (CanMgr_GetTransmissionStatus(IC_INFO_MSG_0X321));
}

/* 
  * @Brief  : Returns the transmission status of Alive_Counter_IC_INFO_0x321_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_alive_counter_ic_info_0x321_s_cbk_0x321(void)
{
  return (CanMgr_GetTransmissionStatus(IC_INFO_MSG_0X321));
}

/* 
  * @Brief  : Returns the transmission status of IC_SS_TELL_TELL_ERROR_0x321_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_ic_ss_tell_tell_error_0x321_s_cbk_0x321(void)
{
  return (CanMgr_GetTransmissionStatus(IC_INFO_MSG_0X321));
}

/* 
  * @Brief  : Returns the transmission status of IC_SS_TELL_TELL_STATUS_0x321_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_ic_ss_tell_tell_status_0x321_s_cbk_0x321(void)
{
  return (CanMgr_GetTransmissionStatus(IC_INFO_MSG_0X321));
}

/* 
  * @Brief  : Returns the transmission status of ODO_Signal_0x321_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_odo_signal_0x321_s_cbk_0x321(void)
{
  return (CanMgr_GetTransmissionStatus(IC_INFO_MSG_0X321));
}

/* 
  * @Brief  : Returns the transmission status of Ambiant_Light_Data_0x321_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_ambiant_light_data_0x321_s_cbk_0x321(void)
{
  return (CanMgr_GetTransmissionStatus(IC_INFO_MSG_0X321));
}

/* 
  * @Brief  : Updates signal REQ_DIAG_ANS_TCU_1_0x631_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_req_diag_ans_tcu_1_0x631_s(float64 data)
{
		 uint8_t ret;
		 uint64 fl_encoded_data;
		 static uint8_t fl_data[REQ_DIAGN_ANS_TCU_0X631_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =1.84467440737096E+19;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_req_diag_ans_tcu_1_0x631_s_encode(fl_value);
		 if(ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_req_diag_ans_tcu_1_0x631_s_is_in_range(fl_encoded_data))
		 {
			 req_diagn_ans_tcu_0x631.req_diag_ans_tcu_1_0x631_s = fl_encoded_data;
			 (void)ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_pack(fl_data,&req_diagn_ans_tcu_0x631,(size_t)REQ_DIAGN_ANS_TCU_0X631_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[REQ_DIAG_ANS_TCU_1_0X631_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[REQ_DIAG_ANS_TCU_1_0X631_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( REQ_DIAGN_ANS_TCU_0X631,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}




/* 
  * @Brief  : Returns the transmission status of REQ_DIAG_ANS_TCU_1_0x631_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_req_diag_ans_tcu_1_0x631_s_cbk_0x631(void)
{
  return (CanMgr_GetTransmissionStatus(REQ_DIAGN_ANS_TCU_0X631));
}

/* 
  * @Brief  : Updates signal REQ_DIAG_ANS_ABS_1_0x6f0_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_req_diag_ans_abs_1_0x6f0_s(float64 data)
{
		 uint8_t ret;
		 uint64 fl_encoded_data;
		 static uint8_t fl_data[REQ_DIAGN_ANS_ABS_0X6F0_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =1.84467440737096E+19;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_req_diag_ans_abs_1_0x6f0_s_encode(fl_value);
		 if(ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_req_diag_ans_abs_1_0x6f0_s_is_in_range(fl_encoded_data))
		 {
			 req_diagn_ans_abs_0x6f0.req_diag_ans_abs_1_0x6f0_s = fl_encoded_data;
			 (void)ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_pack(fl_data,&req_diagn_ans_abs_0x6f0,(size_t)REQ_DIAGN_ANS_ABS_0X6F0_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[REQ_DIAG_ANS_ABS_1_0X6F0_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[REQ_DIAG_ANS_ABS_1_0X6F0_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( REQ_DIAGN_ANS_ABS_0X6F0,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}




/* 
  * @Brief  : Returns the transmission status of REQ_DIAG_ANS_ABS_1_0x6f0_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_req_diag_ans_abs_1_0x6f0_s_cbk_0x6f0(void)
{
  return (CanMgr_GetTransmissionStatus(REQ_DIAGN_ANS_ABS_0X6F0));
}

/* 
  * @Brief  : Updates signal REQ_DIAG_ANS_BCM_1_0x6f1_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_req_diag_ans_bcm_1_0x6f1_s(float64 data)
{
		 uint8_t ret;
		 uint64 fl_encoded_data;
		 static uint8_t fl_data[REQ_DIAGN_ANS_BCM_0X6F1_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =1.84467440737096E+19;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_req_diag_ans_bcm_1_0x6f1_s_encode(fl_value);
		 if(ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_req_diag_ans_bcm_1_0x6f1_s_is_in_range(fl_encoded_data))
		 {
			 req_diagn_ans_bcm_0x6f1.req_diag_ans_bcm_1_0x6f1_s = fl_encoded_data;
			 (void)ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_pack(fl_data,&req_diagn_ans_bcm_0x6f1,(size_t)REQ_DIAGN_ANS_BCM_0X6F1_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[REQ_DIAG_ANS_BCM_1_0X6F1_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[REQ_DIAG_ANS_BCM_1_0X6F1_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( REQ_DIAGN_ANS_BCM_0X6F1,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}




/* 
  * @Brief  : Returns the transmission status of REQ_DIAG_ANS_BCM_1_0x6f1_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_req_diag_ans_bcm_1_0x6f1_s_cbk_0x6f1(void)
{
  return (CanMgr_GetTransmissionStatus(REQ_DIAGN_ANS_BCM_0X6F1));
}

/* 
  * @Brief  : Updates signal REQ_DIAG_ANS_ECM_1_0x7e0_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_req_diag_ans_ecm_1_0x7e0_s(float64 data)
{
		 uint8_t ret;
		 uint64 fl_encoded_data;
		 static uint8_t fl_data[REQ_DIAGN_ANS_ECM_0X7E0_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =1.84467440737096E+19;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_req_diag_ans_ecm_1_0x7e0_s_encode(fl_value);
		 if(ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_req_diag_ans_ecm_1_0x7e0_s_is_in_range(fl_encoded_data))
		 {
			 req_diagn_ans_ecm_0x7e0.req_diag_ans_ecm_1_0x7e0_s = fl_encoded_data;
			 (void)ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_pack(fl_data,&req_diagn_ans_ecm_0x7e0,(size_t)REQ_DIAGN_ANS_ECM_0X7E0_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[REQ_DIAG_ANS_ECM_1_0X7E0_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[REQ_DIAG_ANS_ECM_1_0X7E0_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( REQ_DIAGN_ANS_ECM_0X7E0,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}




/* 
  * @Brief  : Returns the transmission status of REQ_DIAG_ANS_ECM_1_0x7e0_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_req_diag_ans_ecm_1_0x7e0_s_cbk_0x7e0(void)
{
  return (CanMgr_GetTransmissionStatus(REQ_DIAGN_ANS_ECM_0X7E0));
}

/* 
  * @Brief  : Updates signal Diagnostic_Answer_ABS_0x629_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_diagnostic_answer_abs_0x629_s(float64 data)
{
		 uint8_t ret;
		 uint64 fl_encoded_data;
		 static uint8_t fl_data[DIAG_ANSW_ABS_0X629_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =255;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_diagnostic_answer_abs_0x629_s_encode(fl_value);
		 if(ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_diagnostic_answer_abs_0x629_s_is_in_range(fl_encoded_data))
		 {
			 diag_answ_abs_0x629.diagnostic_answer_abs_0x629_s = fl_encoded_data;
			 (void)ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_pack(fl_data,&diag_answ_abs_0x629,(size_t)DIAG_ANSW_ABS_0X629_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[DIAGNOSTIC_ANSWER_ABS_0X629_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[DIAGNOSTIC_ANSWER_ABS_0X629_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( DIAG_ANSW_ABS_0X629,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}




/* 
  * @Brief  : Returns the transmission status of Diagnostic_Answer_ABS_0x629_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_diagnostic_answer_abs_0x629_s_cbk_0x629(void)
{
  return (CanMgr_GetTransmissionStatus(DIAG_ANSW_ABS_0X629));
}

/* 
  * @Brief  : Updates signal Diagnostic_Answer_TCU_0x641_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_diagnostic_answer_tcu_0x641_s(float64 data)
{
		 uint8_t ret;
		 uint64 fl_encoded_data;
		 static uint8_t fl_data[DIA_ANSW_TCU_0X641_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =255;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_diagnostic_answer_tcu_0x641_s_encode(fl_value);
		 if(ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_diagnostic_answer_tcu_0x641_s_is_in_range(fl_encoded_data))
		 {
			 dia_answ_tcu_0x641.diagnostic_answer_tcu_0x641_s = fl_encoded_data;
			 (void)ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_pack(fl_data,&dia_answ_tcu_0x641,(size_t)DIA_ANSW_TCU_0X641_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[DIAGNOSTIC_ANSWER_TCU_0X641_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[DIAGNOSTIC_ANSWER_TCU_0X641_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( DIA_ANSW_TCU_0X641,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}




/* 
  * @Brief  : Returns the transmission status of Diagnostic_Answer_TCU_0x641_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_diagnostic_answer_tcu_0x641_s_cbk_0x641(void)
{
  return (CanMgr_GetTransmissionStatus(DIA_ANSW_TCU_0X641));
}

/* 
  * @Brief  : Updates signal Diagnostic_Answer_IC_0x642_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_diagnostic_answer_ic_0x642_s(float64 data)
{
		 uint8_t ret;
		 uint64 fl_encoded_data;
		 static uint8_t fl_data[DIAG_ANSW_IC_0X642_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =255;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_diagnostic_answer_ic_0x642_s_encode(fl_value);
		 if(ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_diagnostic_answer_ic_0x642_s_is_in_range(fl_encoded_data))
		 {
			 diag_answ_ic_0x642.diagnostic_answer_ic_0x642_s = fl_encoded_data;
			 (void)ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_pack(fl_data,&diag_answ_ic_0x642,(size_t)DIAG_ANSW_IC_0X642_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[DIAGNOSTIC_ANSWER_IC_0X642_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[DIAGNOSTIC_ANSWER_IC_0X642_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( DIAG_ANSW_IC_0X642,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}




/* 
  * @Brief  : Returns the transmission status of Diagnostic_Answer_IC_0x642_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_diagnostic_answer_ic_0x642_s_cbk_0x642(void)
{
  return (CanMgr_GetTransmissionStatus(DIAG_ANSW_IC_0X642));
}

/* 
  * @Brief  : Updates signal Diagnostic_Answer_BCM_0x644_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_diagnostic_answer_bcm_0x644_s(float64 data)
{
		 uint8_t ret;
		 uint64 fl_encoded_data;
		 static uint8_t fl_data[DIAG_ANSW_BCM_0X644_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =255;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_diagnostic_answer_bcm_0x644_s_encode(fl_value);
		 if(ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_diagnostic_answer_bcm_0x644_s_is_in_range(fl_encoded_data))
		 {
			 diag_answ_bcm_0x644.diagnostic_answer_bcm_0x644_s = fl_encoded_data;
			 (void)ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_pack(fl_data,&diag_answ_bcm_0x644,(size_t)DIAG_ANSW_BCM_0X644_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[DIAGNOSTIC_ANSWER_BCM_0X644_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[DIAGNOSTIC_ANSWER_BCM_0X644_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( DIAG_ANSW_BCM_0X644,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}




/* 
  * @Brief  : Returns the transmission status of Diagnostic_Answer_BCM_0x644_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_diagnostic_answer_bcm_0x644_s_cbk_0x644(void)
{
  return (CanMgr_GetTransmissionStatus(DIAG_ANSW_BCM_0X644));
}

/* 
  * @Brief  : Updates signal Diagnostic_Answer_ECM_0x7e8_S                                                                               
  * @param  : data                                                                               
  * @return : E_OK/E_NOT_OK                                                                               
*/ 
uint8_t CanMgr_Write_diagnostic_answer_ecm_0x7e8_s(float64 data)
{
		 uint8_t ret;
		 uint64 fl_encoded_data;
		 static uint8_t fl_data[DIAG_ANSW_ECM_0X7E8_LENGTH]={0};
		 float64 fl_value;
		 fl_value = data;
		 float64 fl_max =255;
		 if(data > fl_max)
		 {
		 fl_value = fl_max;
		 }
		 float64 fl_min = 0;
		 if(data < fl_min )
		 {
		 fl_value = fl_min;
		 }
		 fl_encoded_data = ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_diagnostic_answer_ecm_0x7e8_s_encode(fl_value);
		 if(ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_diagnostic_answer_ecm_0x7e8_s_is_in_range(fl_encoded_data))
		 {
			 diag_answ_ecm_0x7e8.diagnostic_answer_ecm_0x7e8_s = fl_encoded_data;
			 (void)ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_pack(fl_data,&diag_answ_ecm_0x7e8,(size_t)DIAG_ANSW_ECM_0X7E8_LENGTH);
			 if(fl_encoded_data !=0 )
			 {
				 CanMgr_TxSignalInfoTable_t[DIAGNOSTIC_ANSWER_ECM_0X7E8_S].SignalIfActiveFlag = TRUE;
			 }
			 else
			 {
				 CanMgr_TxSignalInfoTable_t[DIAGNOSTIC_ANSWER_ECM_0X7E8_S].SignalIfActiveFlag = FALSE;
			 }
			 ret = CanMgr_SendSignal( DIAG_ANSW_ECM_0X7E8,fl_data);
		 }
		 else
		 {
			 ret = E_NOT_OK;
		 }
		 return  ret;
}




/* 
  * @Brief  : Returns the transmission status of Diagnostic_Answer_ECM_0x7e8_S                                                                               
  * @param  : NONE                                                                               
  * @return :Transmission Status (TRANSMISSION_SUCCESS / TRANSMISSION_FAILED)                                                                                
*/ 
uint8_t CanMgr_diagnostic_answer_ecm_0x7e8_s_cbk_0x7e8(void)
{
  return (CanMgr_GetTransmissionStatus(DIAG_ANSW_ECM_0X7E8));
}



/* 
  * @Brief  : Reads signal Engine_Speed_0x130_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_engine_speed_0x130_s(float64* data)
{
    static uint8_t fl_data[ECM_ENGINE_PARAMETER_0X130_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_ENGINE_PARAMETER_0X130,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_engine_speed_0x130_s_decode(default_ecm_engine_parameter_0x130.engine_speed_0x130_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_unpack(&ecm_engine_parameter_0x130,fl_data,(size_t)ECM_ENGINE_PARAMETER_0X130_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_engine_speed_0x130_s_decode(ecm_engine_parameter_0x130.engine_speed_0x130_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Engine_Run_Status_0x130_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_engine_run_status_0x130_s(float64* data)
{
    static uint8_t fl_data[ECM_ENGINE_PARAMETER_0X130_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_ENGINE_PARAMETER_0X130,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_engine_run_status_0x130_s_decode(default_ecm_engine_parameter_0x130.engine_run_status_0x130_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_unpack(&ecm_engine_parameter_0x130,fl_data,(size_t)ECM_ENGINE_PARAMETER_0X130_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_engine_run_status_0x130_s_decode(ecm_engine_parameter_0x130.engine_run_status_0x130_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Throttle_Position_Sensor_0x130_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_throttle_position_sensor_0x130_s(float64* data)
{
    static uint8_t fl_data[ECM_ENGINE_PARAMETER_0X130_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_ENGINE_PARAMETER_0X130,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_throttle_position_sensor_0x130_s_decode(default_ecm_engine_parameter_0x130.throttle_position_sensor_0x130_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_unpack(&ecm_engine_parameter_0x130,fl_data,(size_t)ECM_ENGINE_PARAMETER_0X130_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_throttle_position_sensor_0x130_s_decode(ecm_engine_parameter_0x130.throttle_position_sensor_0x130_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Throttle_Position_Sensor_Fault_0x130_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_throttle_position_sensor_fault_0x130_s(float64* data)
{
    static uint8_t fl_data[ECM_ENGINE_PARAMETER_0X130_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_ENGINE_PARAMETER_0X130,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_throttle_position_sensor_fault_0x130_s_decode(default_ecm_engine_parameter_0x130.throttle_position_sensor_fault_0x130_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_unpack(&ecm_engine_parameter_0x130,fl_data,(size_t)ECM_ENGINE_PARAMETER_0X130_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_throttle_position_sensor_fault_0x130_s_decode(ecm_engine_parameter_0x130.throttle_position_sensor_fault_0x130_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Remote_Mobilize_Immoblize_Status_0x130_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_remote_mobilize_immoblize_status_0x130_s(float64* data)
{
    static uint8_t fl_data[ECM_ENGINE_PARAMETER_0X130_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_ENGINE_PARAMETER_0X130,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_remote_mobilize_immoblize_status_0x130_s_decode(default_ecm_engine_parameter_0x130.remote_mobilize_immoblize_status_0x130_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_unpack(&ecm_engine_parameter_0x130,fl_data,(size_t)ECM_ENGINE_PARAMETER_0X130_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_remote_mobilize_immoblize_status_0x130_s_decode(ecm_engine_parameter_0x130.remote_mobilize_immoblize_status_0x130_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal MIL_0x130_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_mil_0x130_s(float64* data)
{
    static uint8_t fl_data[ECM_ENGINE_PARAMETER_0X130_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_ENGINE_PARAMETER_0X130,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_mil_0x130_s_decode(default_ecm_engine_parameter_0x130.mil_0x130_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_unpack(&ecm_engine_parameter_0x130,fl_data,(size_t)ECM_ENGINE_PARAMETER_0X130_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_engine_parameter_0x130_mil_0x130_s_decode(ecm_engine_parameter_0x130.mil_0x130_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal Alive_Counter_ECM_sensor_0x131_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_alive_counter_ecm_sensor_0x131_s(float64* data)
{
    static uint8_t fl_data[ECM_SENSOR_PARAMETER_0X131_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_SENSOR_PARAMETER_0X131,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_alive_counter_ecm_sensor_0x131_s_decode(default_ecm_sensor_parameter_0x131.alive_counter_ecm_sensor_0x131_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_unpack(&ecm_sensor_parameter_0x131,fl_data,(size_t)ECM_SENSOR_PARAMETER_0X131_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_alive_counter_ecm_sensor_0x131_s_decode(ecm_sensor_parameter_0x131.alive_counter_ecm_sensor_0x131_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal ECM_CRC_Sensor_0x131_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_ecm_crc_sensor_0x131_s(float64* data)
{
    static uint8_t fl_data[ECM_SENSOR_PARAMETER_0X131_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_SENSOR_PARAMETER_0X131,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_ecm_crc_sensor_0x131_s_decode(default_ecm_sensor_parameter_0x131.ecm_crc_sensor_0x131_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_unpack(&ecm_sensor_parameter_0x131,fl_data,(size_t)ECM_SENSOR_PARAMETER_0X131_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_ecm_crc_sensor_0x131_s_decode(ecm_sensor_parameter_0x131.ecm_crc_sensor_0x131_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Roll_Over_Detection_0x131_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_roll_over_detection_0x131_s(float64* data)
{
    static uint8_t fl_data[ECM_SENSOR_PARAMETER_0X131_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_SENSOR_PARAMETER_0X131,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_roll_over_detection_0x131_s_decode(default_ecm_sensor_parameter_0x131.roll_over_detection_0x131_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_unpack(&ecm_sensor_parameter_0x131,fl_data,(size_t)ECM_SENSOR_PARAMETER_0X131_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_roll_over_detection_0x131_s_decode(ecm_sensor_parameter_0x131.roll_over_detection_0x131_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Roll_Over_Detection_Fault_Status_0x131_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_roll_over_detection_fault_status_0x131_s(float64* data)
{
    static uint8_t fl_data[ECM_SENSOR_PARAMETER_0X131_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_SENSOR_PARAMETER_0X131,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_roll_over_detection_fault_status_0x131_s_decode(default_ecm_sensor_parameter_0x131.roll_over_detection_fault_status_0x131_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_unpack(&ecm_sensor_parameter_0x131,fl_data,(size_t)ECM_SENSOR_PARAMETER_0X131_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_roll_over_detection_fault_status_0x131_s_decode(ecm_sensor_parameter_0x131.roll_over_detection_fault_status_0x131_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Side_Stand_Sensor_0x131_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_side_stand_sensor_0x131_s(float64* data)
{
    static uint8_t fl_data[ECM_SENSOR_PARAMETER_0X131_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_SENSOR_PARAMETER_0X131,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_side_stand_sensor_0x131_s_decode(default_ecm_sensor_parameter_0x131.side_stand_sensor_0x131_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_unpack(&ecm_sensor_parameter_0x131,fl_data,(size_t)ECM_SENSOR_PARAMETER_0X131_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_side_stand_sensor_0x131_s_decode(ecm_sensor_parameter_0x131.side_stand_sensor_0x131_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Side_Stand_Sensor_Fault_0x131_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_side_stand_sensor_fault_0x131_s(float64* data)
{
    static uint8_t fl_data[ECM_SENSOR_PARAMETER_0X131_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_SENSOR_PARAMETER_0X131,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_side_stand_sensor_fault_0x131_s_decode(default_ecm_sensor_parameter_0x131.side_stand_sensor_fault_0x131_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_unpack(&ecm_sensor_parameter_0x131,fl_data,(size_t)ECM_SENSOR_PARAMETER_0X131_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_side_stand_sensor_fault_0x131_s_decode(ecm_sensor_parameter_0x131.side_stand_sensor_fault_0x131_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Gear_Position_Sensor_0x131_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_gear_position_sensor_0x131_s(float64* data)
{
    static uint8_t fl_data[ECM_SENSOR_PARAMETER_0X131_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_SENSOR_PARAMETER_0X131,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_gear_position_sensor_0x131_s_decode(default_ecm_sensor_parameter_0x131.gear_position_sensor_0x131_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_unpack(&ecm_sensor_parameter_0x131,fl_data,(size_t)ECM_SENSOR_PARAMETER_0X131_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_gear_position_sensor_0x131_s_decode(ecm_sensor_parameter_0x131.gear_position_sensor_0x131_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Gear_Shift_Advisory_0x131_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_gear_shift_advisory_0x131_s(float64* data)
{
    static uint8_t fl_data[ECM_SENSOR_PARAMETER_0X131_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_SENSOR_PARAMETER_0X131,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_gear_shift_advisory_0x131_s_decode(default_ecm_sensor_parameter_0x131.gear_shift_advisory_0x131_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_unpack(&ecm_sensor_parameter_0x131,fl_data,(size_t)ECM_SENSOR_PARAMETER_0X131_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_gear_shift_advisory_0x131_s_decode(ecm_sensor_parameter_0x131.gear_shift_advisory_0x131_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Engine_Kill_Switch_Status_0x131_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_engine_kill_switch_status_0x131_s(float64* data)
{
    static uint8_t fl_data[ECM_SENSOR_PARAMETER_0X131_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_SENSOR_PARAMETER_0X131,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_engine_kill_switch_status_0x131_s_decode(default_ecm_sensor_parameter_0x131.engine_kill_switch_status_0x131_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_unpack(&ecm_sensor_parameter_0x131,fl_data,(size_t)ECM_SENSOR_PARAMETER_0X131_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_engine_kill_switch_status_0x131_s_decode(ecm_sensor_parameter_0x131.engine_kill_switch_status_0x131_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Throttle_grip_Sensor_0x131_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_throttle_grip_sensor_0x131_s(float64* data)
{
    static uint8_t fl_data[ECM_SENSOR_PARAMETER_0X131_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_SENSOR_PARAMETER_0X131,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_throttle_grip_sensor_0x131_s_decode(default_ecm_sensor_parameter_0x131.throttle_grip_sensor_0x131_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_unpack(&ecm_sensor_parameter_0x131,fl_data,(size_t)ECM_SENSOR_PARAMETER_0X131_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_sensor_parameter_0x131_throttle_grip_sensor_0x131_s_decode(ecm_sensor_parameter_0x131.throttle_grip_sensor_0x131_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal Distance_Travelled_With_MIL_0x135_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_distance_travelled_with_mil_0x135_s(float64* data)
{
    static uint8_t fl_data[ECM_ADDITIONAL_INFO_0X135_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_ADDITIONAL_INFO_0X135,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_distance_travelled_with_mil_0x135_s_decode(default_ecm_additional_info_0x135.distance_travelled_with_mil_0x135_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_unpack(&ecm_additional_info_0x135,fl_data,(size_t)ECM_ADDITIONAL_INFO_0X135_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_distance_travelled_with_mil_0x135_s_decode(ecm_additional_info_0x135.distance_travelled_with_mil_0x135_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Accumulat_Fuel_Inj_Time_Fuel_Qty_0x135_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_accumulat_fuel_inj_time_fuel_qty_0x135_s(float64* data)
{
    static uint8_t fl_data[ECM_ADDITIONAL_INFO_0X135_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ECM_ADDITIONAL_INFO_0X135,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_accumulat_fuel_inj_time_fuel_qty_0x135_s_decode(default_ecm_additional_info_0x135.accumulat_fuel_inj_time_fuel_qty_0x135_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_unpack(&ecm_additional_info_0x135,fl_data,(size_t)ECM_ADDITIONAL_INFO_0X135_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_ecm_additional_info_0x135_accumulat_fuel_inj_time_fuel_qty_0x135_s_decode(ecm_additional_info_0x135.accumulat_fuel_inj_time_fuel_qty_0x135_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal ABS_CRC_TRQ_0x142_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_abs_crc_trq_0x142_s(float64* data)
{
    static uint8_t fl_data[ABS_TRQ_REQ_0X142_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ABS_TRQ_REQ_0X142,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_abs_crc_trq_0x142_s_decode(default_abs_trq_req_0x142.abs_crc_trq_0x142_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_unpack(&abs_trq_req_0x142,fl_data,(size_t)ABS_TRQ_REQ_0X142_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_abs_crc_trq_0x142_s_decode(abs_trq_req_0x142.abs_crc_trq_0x142_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Alive_Counter_ABS_TRQ_0x142_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_alive_counter_abs_trq_0x142_s(float64* data)
{
    static uint8_t fl_data[ABS_TRQ_REQ_0X142_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ABS_TRQ_REQ_0X142,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_alive_counter_abs_trq_0x142_s_decode(default_abs_trq_req_0x142.alive_counter_abs_trq_0x142_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_unpack(&abs_trq_req_0x142,fl_data,(size_t)ABS_TRQ_REQ_0X142_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_alive_counter_abs_trq_0x142_s_decode(abs_trq_req_0x142.alive_counter_abs_trq_0x142_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Torque_Request_Status_0x142_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_torque_request_status_0x142_s(float64* data)
{
    static uint8_t fl_data[ABS_TRQ_REQ_0X142_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ABS_TRQ_REQ_0X142,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_torque_request_status_0x142_s_decode(default_abs_trq_req_0x142.torque_request_status_0x142_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_unpack(&abs_trq_req_0x142,fl_data,(size_t)ABS_TRQ_REQ_0X142_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_torque_request_status_0x142_s_decode(abs_trq_req_0x142.torque_request_status_0x142_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal TC_Telltale_Status_0x142_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_tc_telltale_status_0x142_s(float64* data)
{
    static uint8_t fl_data[ABS_TRQ_REQ_0X142_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ABS_TRQ_REQ_0X142,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_tc_telltale_status_0x142_s_decode(default_abs_trq_req_0x142.tc_telltale_status_0x142_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_unpack(&abs_trq_req_0x142,fl_data,(size_t)ABS_TRQ_REQ_0X142_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_tc_telltale_status_0x142_s_decode(abs_trq_req_0x142.tc_telltale_status_0x142_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Trq_Req_MTC_0x142_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_trq_req_mtc_0x142_s(float64* data)
{
    static uint8_t fl_data[ABS_TRQ_REQ_0X142_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ABS_TRQ_REQ_0X142,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_trq_req_mtc_0x142_s_decode(default_abs_trq_req_0x142.trq_req_mtc_0x142_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_unpack(&abs_trq_req_0x142,fl_data,(size_t)ABS_TRQ_REQ_0X142_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_trq_req_mtc_0x142_s_decode(abs_trq_req_0x142.trq_req_mtc_0x142_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal Trq_Req_DTC_0x142_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_trq_req_dtc_0x142_s(float64* data)
{
    static uint8_t fl_data[ABS_TRQ_REQ_0X142_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ABS_TRQ_REQ_0X142,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_trq_req_dtc_0x142_s_decode(default_abs_trq_req_0x142.trq_req_dtc_0x142_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_unpack(&abs_trq_req_0x142,fl_data,(size_t)ABS_TRQ_REQ_0X142_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_abs_trq_req_0x142_trq_req_dtc_0x142_s_decode(abs_trq_req_0x142.trq_req_dtc_0x142_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal Status_ABS_0x205_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_status_abs_0x205_s(float64* data)
{
    static uint8_t fl_data[ABS_STATUS_0X205_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ABS_STATUS_0X205,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_abs_status_0x205_status_abs_0x205_s_decode(default_abs_status_0x205.status_abs_0x205_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_abs_status_0x205_unpack(&abs_status_0x205,fl_data,(size_t)ABS_STATUS_0X205_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_abs_status_0x205_status_abs_0x205_s_decode(abs_status_0x205.status_abs_0x205_s);
     }
    return ret;
}
/* 
  * @Brief  : Reads signal ABS_Telltale_Status_0x205_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_abs_telltale_status_0x205_s(float64* data)
{
    static uint8_t fl_data[ABS_STATUS_0X205_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ABS_STATUS_0X205,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_abs_status_0x205_abs_telltale_status_0x205_s_decode(default_abs_status_0x205.abs_telltale_status_0x205_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_abs_status_0x205_unpack(&abs_status_0x205,fl_data,(size_t)ABS_STATUS_0X205_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_abs_status_0x205_abs_telltale_status_0x205_s_decode(abs_status_0x205.abs_telltale_status_0x205_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal Vehicle_Speed_0x206_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_vehicle_speed_0x206_s(float64* data)
{
    static uint8_t fl_data[ABS_VEHICLE_SPEED_0X206_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(ABS_VEHICLE_SPEED_0X206,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_abs_vehicle_speed_0x206_vehicle_speed_0x206_s_decode(default_abs_vehicle_speed_0x206.vehicle_speed_0x206_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_abs_vehicle_speed_0x206_unpack(&abs_vehicle_speed_0x206,fl_data,(size_t)ABS_VEHICLE_SPEED_0X206_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_abs_vehicle_speed_0x206_vehicle_speed_0x206_s_decode(abs_vehicle_speed_0x206.vehicle_speed_0x206_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal Diagnostic_Answer_ABS_0x629_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_diagnostic_answer_abs_0x629_s(float64* data)
{
    static uint8_t fl_data[DIAG_ANS_ABS_0X629_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(DIAG_ANS_ABS_0X629,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_diag_ans_abs_0x629_diagnostic_answer_abs_0x629_s_decode(default_diag_ans_abs_0x629.diagnostic_answer_abs_0x629_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_diag_ans_abs_0x629_unpack(&diag_ans_abs_0x629,fl_data,(size_t)DIAG_ANS_ABS_0X629_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_diag_ans_abs_0x629_diagnostic_answer_abs_0x629_s_decode(diag_ans_abs_0x629.diagnostic_answer_abs_0x629_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal REQ_DIAG_ANS_IC_0x632_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_req_diag_answ_ic_0x632_s(float64* data)
{
    static uint8_t fl_data[REQ_DIAG_ANS_IC_0X632_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(REQ_DIAG_ANS_IC_0X632,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_req_diag_ans_ic_0x632_req_diag_ans_ic_0x632_s_decode(default_req_diag_ans_ic_0x632.req_diag_ans_ic_0x632_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_req_diag_ans_ic_0x632_unpack(&req_diag_ans_ic_0x632,fl_data,(size_t)REQ_DIAG_ANS_IC_0X632_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_req_diag_ans_ic_0x632_req_diag_ans_ic_0x632_s_decode(req_diag_ans_ic_0x632.req_diag_ans_ic_0x632_s);
     }
    return ret;
}



/* 
  * @Brief  : Reads signal Diagnostic_Answer_TCU_0x641_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_diagnostic_answer_tcu_0x641_s(float64* data)
{
    static uint8_t fl_data[DIAG_ANSW_TCU_0X641_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(DIAG_ANSW_TCU_0X641,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_diag_answ_tcu_0x641_diagnostic_answer_tcu_0x641_s_decode(default_diag_answ_tcu_0x641.diagnostic_answer_tcu_0x641_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_diag_answ_tcu_0x641_unpack(&diag_answ_tcu_0x641,fl_data,(size_t)DIAG_ANSW_TCU_0X641_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_diag_answ_tcu_0x641_diagnostic_answer_tcu_0x641_s_decode(diag_answ_tcu_0x641.diagnostic_answer_tcu_0x641_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal Diagnostic_Answer_IC_0x642_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_diagnostic_answer_ic_0x642_s(float64* data)
{
    static uint8_t fl_data[DIAG_ANS_IC_0X642_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(DIAG_ANS_IC_0X642,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_diag_ans_ic_0x642_diagnostic_answer_ic_0x642_s_decode(default_diag_ans_ic_0x642.diagnostic_answer_ic_0x642_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_diag_ans_ic_0x642_unpack(&diag_ans_ic_0x642,fl_data,(size_t)DIAG_ANS_IC_0X642_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_diag_ans_ic_0x642_diagnostic_answer_ic_0x642_s_decode(diag_ans_ic_0x642.diagnostic_answer_ic_0x642_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal Diagnostic_Answer_BCM_0x644_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_diagnostic_answer_bcm_0x644_s(float64* data)
{
    static uint8_t fl_data[DIAG_ANS_BCM_0X644_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(DIAG_ANS_BCM_0X644,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_diag_ans_bcm_0x644_diagnostic_answer_bcm_0x644_s_decode(default_diag_ans_bcm_0x644.diagnostic_answer_bcm_0x644_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_diag_ans_bcm_0x644_unpack(&diag_ans_bcm_0x644,fl_data,(size_t)DIAG_ANS_BCM_0X644_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_diag_ans_bcm_0x644_diagnostic_answer_bcm_0x644_s_decode(diag_ans_bcm_0x644.diagnostic_answer_bcm_0x644_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal Diagnostic_Answer_ECM_0x7e8_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_diagnostic_answer_ecm_0x7e8_s(float64* data)
{
    static uint8_t fl_data[DIAG_ANS_ECM_0X7E8_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(DIAG_ANS_ECM_0X7E8,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch1raaacanmessagestandardv1can1draft_diag_ans_ecm_0x7e8_diagnostic_answer_ecm_0x7e8_s_decode(default_diag_ans_ecm_0x7e8.diagnostic_answer_ecm_0x7e8_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch1raaacanmessagestandardv1can1draft_diag_ans_ecm_0x7e8_unpack(&diag_ans_ecm_0x7e8,fl_data,(size_t)DIAG_ANS_ECM_0X7E8_LENGTH);
      *data =ch1raaacanmessagestandardv1can1draft_diag_ans_ecm_0x7e8_diagnostic_answer_ecm_0x7e8_s_decode(diag_ans_ecm_0x7e8.diagnostic_answer_ecm_0x7e8_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal REQ_DIAG_ANS_TCU_0x631_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_req_diag_ans_tcu_0x631_s(float64* data)
{
    static uint8_t fl_data[REQ_DIAG_ANSW_TCU_0X631_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(REQ_DIAG_ANSW_TCU_0X631,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch2raaacanmessagestandardv1can2draft_req_diag_answ_tcu_0x631_req_diag_ans_tcu_0x631_s_decode(default_req_diag_answ_tcu_0x631.req_diag_ans_tcu_0x631_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch2raaacanmessagestandardv1can2draft_req_diag_answ_tcu_0x631_unpack(&req_diag_answ_tcu_0x631,fl_data,(size_t)REQ_DIAG_ANSW_TCU_0X631_LENGTH);
      *data =ch2raaacanmessagestandardv1can2draft_req_diag_answ_tcu_0x631_req_diag_ans_tcu_0x631_s_decode(req_diag_answ_tcu_0x631.req_diag_ans_tcu_0x631_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal REQ_DIAG_ANS_IC_0x632_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_req_diag_ans_ic_0x632_s(float64* data)
{
    static uint8_t fl_data[REQ_DIAG_ANSW_IC_0X632_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(REQ_DIAG_ANSW_IC_0X632,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch2raaacanmessagestandardv1can2draft_req_diag_answ_ic_0x632_req_diag_ans_ic_0x632_s_decode(default_req_diag_answ_ic_0x632.req_diag_ans_ic_0x632_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch2raaacanmessagestandardv1can2draft_req_diag_answ_ic_0x632_unpack(&req_diag_answ_ic_0x632,fl_data,(size_t)REQ_DIAG_ANSW_IC_0X632_LENGTH);
      *data =ch2raaacanmessagestandardv1can2draft_req_diag_answ_ic_0x632_req_diag_ans_ic_0x632_s_decode(req_diag_answ_ic_0x632.req_diag_ans_ic_0x632_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal REQ_DIAG_ANS_ABS_0x6f0_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_req_diag_ans_abs_0x6f0_s(float64* data)
{
    static uint8_t fl_data[REQ_DIAG_ANSW_ABS_0X6F0_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(REQ_DIAG_ANSW_ABS_0X6F0,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch2raaacanmessagestandardv1can2draft_req_diag_answ_abs_0x6f0_req_diag_ans_abs_0x6f0_s_decode(default_req_diag_answ_abs_0x6f0.req_diag_ans_abs_0x6f0_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch2raaacanmessagestandardv1can2draft_req_diag_answ_abs_0x6f0_unpack(&req_diag_answ_abs_0x6f0,fl_data,(size_t)REQ_DIAG_ANSW_ABS_0X6F0_LENGTH);
      *data =ch2raaacanmessagestandardv1can2draft_req_diag_answ_abs_0x6f0_req_diag_ans_abs_0x6f0_s_decode(req_diag_answ_abs_0x6f0.req_diag_ans_abs_0x6f0_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal REQ_DIAG_ANS_BCM_0x6f1_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_req_diag_ans_bcm_0x6f1_s(float64* data)
{
    static uint8_t fl_data[REQ_DIAG_ANSW_BCM_0X6F1_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(REQ_DIAG_ANSW_BCM_0X6F1,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch2raaacanmessagestandardv1can2draft_req_diag_answ_bcm_0x6f1_req_diag_ans_bcm_0x6f1_s_decode(default_req_diag_answ_bcm_0x6f1.req_diag_ans_bcm_0x6f1_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch2raaacanmessagestandardv1can2draft_req_diag_answ_bcm_0x6f1_unpack(&req_diag_answ_bcm_0x6f1,fl_data,(size_t)REQ_DIAG_ANSW_BCM_0X6F1_LENGTH);
      *data =ch2raaacanmessagestandardv1can2draft_req_diag_answ_bcm_0x6f1_req_diag_ans_bcm_0x6f1_s_decode(req_diag_answ_bcm_0x6f1.req_diag_ans_bcm_0x6f1_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal Functional_Diagnostic_Request_0x7df_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_functional_diagnostic_request_0x7df_s(float64* data)
{
    static uint8_t fl_data[FUNCTIONAL_DIAG_REQUEST_0X7DF_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(FUNCTIONAL_DIAG_REQUEST_0X7DF,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch2raaacanmessagestandardv1can2draft_functional_diag_request_0x7df_functional_diagnostic_request_0x7df_s_decode(default_functional_diag_request_0x7df.functional_diagnostic_request_0x7df_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch2raaacanmessagestandardv1can2draft_functional_diag_request_0x7df_unpack(&functional_diag_request_0x7df,fl_data,(size_t)FUNCTIONAL_DIAG_REQUEST_0X7DF_LENGTH);
      *data =ch2raaacanmessagestandardv1can2draft_functional_diag_request_0x7df_functional_diagnostic_request_0x7df_s_decode(functional_diag_request_0x7df.functional_diagnostic_request_0x7df_s);
     }
    return ret;
}




/* 
  * @Brief  : Reads signal REQ_DIAG_ANS_ECM_0x7e0_S                                                                               
  * @param  : pointer to store the data                                                                               
  * @return : Reception status                                                                               
*/ 
uint8_t CanMgr_Read_req_diag_ans_ecm_0x7e0_s(float64* data)
{
    static uint8_t fl_data[REQ_DIAG_ANSW_ECM_0X7E0_LENGTH];
    uint8_t ret;
    ret = CanMgr_ReceiveSignal(REQ_DIAG_ANSW_ECM_0X7E0,fl_data);
    /*Data is accepted only if there are no negative use-cases*/
    if((ret == RX_ALIVE_CNTR_ERROR_CONFIRMED) || (ret ==  RX_CRC_ERROR_CONFIRMED ))
     {
       *data =ch2raaacanmessagestandardv1can2draft_req_diag_answ_ecm_0x7e0_req_diag_ans_ecm_0x7e0_s_decode(default_req_diag_answ_ecm_0x7e0.req_diag_ans_ecm_0x7e0_s);
     }
    /*CRC confirmed / Alive counter error confirmed / CRC yet to be confirmed*/
    else
     {
      (void)ch2raaacanmessagestandardv1can2draft_req_diag_answ_ecm_0x7e0_unpack(&req_diag_answ_ecm_0x7e0,fl_data,(size_t)REQ_DIAG_ANSW_ECM_0X7E0_LENGTH);
      *data =ch2raaacanmessagestandardv1can2draft_req_diag_answ_ecm_0x7e0_req_diag_ans_ecm_0x7e0_s_decode(req_diag_answ_ecm_0x7e0.req_diag_ans_ecm_0x7e0_s);
     }
    return ret;
}


/**
  * @Brief  : Initializes all the TX message with default value  
  * @param  : NONE                                                                               
  * @return : NONE                                                                               
*/ 

void CanMgr_cfgInit(void)
{
    (void)ch1raaacanmessagestandardv1can1draft_ic_info_msg_0x321_pack(&Init_data_value[IC_INFO_MSG_0X321][0], &default_ic_info_msg_0x321, (size_t)IC_INFO_MSG_0X321_LENGTH);
    (void)ch1raaacanmessagestandardv1can1draft_req_diagn_ans_tcu_0x631_pack(&Init_data_value[REQ_DIAGN_ANS_TCU_0X631][0], &default_req_diagn_ans_tcu_0x631, (size_t)REQ_DIAGN_ANS_TCU_0X631_LENGTH);
    (void)ch1raaacanmessagestandardv1can1draft_req_diagn_ans_abs_0x6f0_pack(&Init_data_value[REQ_DIAGN_ANS_ABS_0X6F0][0], &default_req_diagn_ans_abs_0x6f0, (size_t)REQ_DIAGN_ANS_ABS_0X6F0_LENGTH);
    (void)ch1raaacanmessagestandardv1can1draft_req_diagn_ans_bcm_0x6f1_pack(&Init_data_value[REQ_DIAGN_ANS_BCM_0X6F1][0], &default_req_diagn_ans_bcm_0x6f1, (size_t)REQ_DIAGN_ANS_BCM_0X6F1_LENGTH);
    (void)ch1raaacanmessagestandardv1can1draft_req_diagn_ans_ecm_0x7e0_pack(&Init_data_value[REQ_DIAGN_ANS_ECM_0X7E0][0], &default_req_diagn_ans_ecm_0x7e0, (size_t)REQ_DIAGN_ANS_ECM_0X7E0_LENGTH);
    (void)ch2raaacanmessagestandardv1can2draft_diag_answ_abs_0x629_pack(&Init_data_value[DIAG_ANSW_ABS_0X629][0], &default_diag_answ_abs_0x629, (size_t)DIAG_ANSW_ABS_0X629_LENGTH);
    (void)ch2raaacanmessagestandardv1can2draft_dia_answ_tcu_0x641_pack(&Init_data_value[DIA_ANSW_TCU_0X641][0], &default_dia_answ_tcu_0x641, (size_t)DIA_ANSW_TCU_0X641_LENGTH);
    (void)ch2raaacanmessagestandardv1can2draft_diag_answ_ic_0x642_pack(&Init_data_value[DIAG_ANSW_IC_0X642][0], &default_diag_answ_ic_0x642, (size_t)DIAG_ANSW_IC_0X642_LENGTH);
    (void)ch2raaacanmessagestandardv1can2draft_diag_answ_bcm_0x644_pack(&Init_data_value[DIAG_ANSW_BCM_0X644][0], &default_diag_answ_bcm_0x644, (size_t)DIAG_ANSW_BCM_0X644_LENGTH);
    (void)ch2raaacanmessagestandardv1can2draft_diag_answ_ecm_0x7e8_pack(&Init_data_value[DIAG_ANSW_ECM_0X7E8][0], &default_diag_answ_ecm_0x7e8, (size_t)DIAG_ANSW_ECM_0X7E8_LENGTH);

}


/**********************************************************************************************************************
  *                                                R E V I S I O N   H I S T O R Y             
* **********************************************************************************************************************/
/**********************************************************************************************************************
REVISION NUMBER      : V1.0.0                                                                                   
REVISION DATE        : 30/01/2020                                                                               
CREATED / REVISED BY : Mahendran L (mahendranl@niyatainfotech.com)                                        
DESCRIPTION          : Initial Version                                                                       
---------------------------------------------------------------------------------------------------------------------
***********************************************************************************************************************/
