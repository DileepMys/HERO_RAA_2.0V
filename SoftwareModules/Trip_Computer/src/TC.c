/* @file TC_C */
#ifndef TC_C
#define TC_C
/*********************************************************************************************************************
*    DISCLAIMER
*    Copyright © , 2021 Niyata Infotech Pvt. Ltd. All rights reserved.                                           
*********************************************************************************************************************/

/*********************************************************************************************************************
* @author              Author : Maheswari R (maheswari@niyatainfotech.com)
*********************************************************************************************************************/

/*********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                       
**--------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : TC.c
*  Version                         : V1.0.3
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent
*  Description                     : This file contains the Implementation of Trip Computer  
*  @bug                         
--------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/


/*********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                             
*********************************************************************************************************************/
#include "TC.h"
#include "math.h"
#include "fuel03.h"

/*********************************************************************************************************************
*                                             M A C R O   D E F I N I T I O N S                                          
*********************************************************************************************************************/

/*
 * @brief: This variable is used to define  the Activate
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
#define TC_ACTIVATE 				 	1u

/*
 * @brief: This variable is used to define  the Deactivate
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
#define TC_DEACTIVATE 			   		0u

#define TC_E_OK            1u

#define TC_E_NOK           0u



#define MAX_VAL     (uint32)       10000


/*
* @brief          : This macro is used to configure the function of Get IGN mode
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 1
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define IGN_MODE()                                  Sys_Service_Get_Ignition_State()

/*
* @brief          : This macro is used to configure the function of Get LVSD Enable flag
* @Unit           : NA
* @Resolution:    : NA
* @Range          : 0 to 8 bit
* @Applicability  : Store the HVSD Enable status
* @Note           : Do not modify this macro value or name
*/
#define GET_HSVD_STATUS()                           Sys_Service_Get_High_Voltage_State()

/*
* @brief          : This macro is used to configure the function of Get HVSD Enable flag
* @Unit           : NA
* @Resolution:    : NA
* @Range          : 0 to 8 bit
* @Applicability  : Store the LVSD Enable status
* @Note           : Do not modify this macro value or name
*/

#define GET_LSVD_STATUS()                           Sys_Service_Get_Low_Voltage_State()



/*
* @brief          : This macro is used to configure the function of Get odo value
* @Unit           : KM
* @Resolution:    : 0.1
* @Range          : 0 to 32 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define GET_TRIP_ODO_VALUE(x)                       ODO_Get_TripOdometer(x)
/*
* @brief          : This macro is used to configure the function of Get Fuel level
* @Unit           : Litre
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define GET_UNIT_SELCETION                        TC_UNIT_SELECTION_KML



/*
* @brief          : This macro is used to configure the function of Get Speed fault status
* @Unit           : Revolution per minute
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define SPEED_FAULT_STATUS()                        Swc_Get_Speedometer_Fault_Status()

/*
* @brief          : This macro is used to configure the function of Get Speed of the vehicle
* @Unit           : Revolution per minute
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define INPUT_SPEED_VALUE()                         Get_display_Speed()

/*
* @brief          : This macro is used to configure the function of Get Speed of the vehicle
* @Unit           : Revolution per minute
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define GET_I2C_ERROR_STATUS()                      Swc_Get_ODO_NVM_Error_Status()

/*
* @brief          : This macro is used to configure the function of Get odo value
* @Unit           : KM
* @Resolution:    : 0.1
* @Range          : 0 to 32 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define GET_ODO_VALUE_KM()                             IFE_ODO_value()

/*
* @brief          : This macro is used to configure the function of Get Odo data reset value
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define GET_ODO_DATA_RESET()                      0

/*
* @brief          : This macro is used to configure the function of Get Odo data write value
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define GET_ODO_DATA_WRITE()                      0
/*
* @brief          : This macro is used to configure the function of Get Fuel Init status value
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : N/A
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define GET_FUEL_INIT_STATUS()                        Fuel_Gauge_Ready_Status()

/*
* @brief          : This macro is used to configure the function of Get Fuel status value
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : N/A
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define GET_FUEL_STATUS()                          1

/*
* @brief          : This macro is used to configure the function of Get Fuelbar value
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : N/A
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define GET_FUELBAR_VALUE()                         Fuel_Guage_Get_Current_Bar_Level()

/*
* @brief          : This macro is used to configure the function of Get Fuelbar capacity value
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : N/A
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define GET_FUELBAR_CAPACITY_VALUE(x)                         Fuel_Guage_Table(x)

/*
* @brief          : This macro is used to configure the Minimum Speed  
* @Unit           : KMPH
* @Resolution:    : 1
* @Range          : 0 to 10
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define IFE_MIN_SPEED                               5 

/*
* @brief          : This macro is used to configure the update initial display time
* @Unit           : sec
* @Resolution:    : 0.1
* @Range          : 0 to 30
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define IFE_INITIAL_DISPLAY_UPDATE_TIME              10

/*
* @brief          : This macro is used to configure the update display time
* @Unit           : sec
* @Resolution:    : 0.1
* @Range          : 0 to 200
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define IFE_DISPLAY_TIME                             3

/*
* @brief          : This macro is used to configure the IFE Maximum value
* @Unit           : None
* @Resolution:    : 0.1
* @Range          : 0 to 120
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define IFE_MAX                                     1200

/*
* @brief          : This macro is used to configure the US MPG conversion Factor
* @Unit           : None
* @Resolution:    : 1/10000
* @Range          : 0 to 32 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define US_MPG_CONV_FACTOR                          23521

/*
* @brief          : This macro is used to configure the UK MPG conversion Factor 
* @Unit           : None
* @Resolution:    : 1/10000
* @Range          : 0 to 32 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define UK_MPG_CONV_FACTOR                          28248

/*
* @brief          : This macro is used to configure the Max Index counts  
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 255
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define IFE_MAX_INDEX_CNT                           10

/*
* @brief          : This macro is used to configure the Max Sample counts  
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 100
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define IFE_MAX_SAMPLES_CNT                         9

/*
* @brief          : This macro is used to configure the IFE Index counts  
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 100
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define IFE_INDEX_COUNT								10

/*
* @brief          : This macro is used to configure the overflow distance  
* @Unit           : None
* @Resolution:    : 0.001
* @Range          : 0 to 1 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define IFE_FUELACCU_RES                            597

/*
* @brief          : This macro is used to configure the Trip Reset trigger status
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 1 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define AFE_TRIP_RESET_TRIGGER_STATUS               0

/*
* @brief          : This macro is used to configure the Trip Sw Reset Status
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 1 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define AFE_TRIP_SW_RESET_STATUS                    0

/*
* @brief          : This macro is used to configure the AFE maximum Accumulation value
* @Unit           : Km
* @Resolution:    : 0.1
* @Range          : 0-20000
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define AFE_ACCU_MAX                                100000000

/*
* @brief          : This macro is used to configure the AFE Accumulation Rollback value
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0-10
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define AFE_ACCU_ROLLBACK                           4

/*
* @brief          : This macro is used to configure the AFE Min Speed
* @Unit           : Kmph
* @Resolution:    : 1
* @Range          : 0-5
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define AFE_MIN_SPEED                               0

/*
* @brief          : This macro is used to configure the AFE Max Speed
* @Unit           : Kmph
* @Resolution:    : 1
* @Range          : 190-255
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define AFE_MAX_SPEED                               199

/*
* @brief          : This macro is used to configure the update display time
* @Unit           : sec
* @Resolution:    : AFE processing Rate
* @Range          : 0 to 20
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define AFE_DISPLAY_UPDATE_TIME                     10

/*
* @brief          : This macro is used to configure the AFE Maximum value
* @Unit           : None
* @Resolution:    : 0.1
* @Range          : 0 to 999
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define AFE_MAX                                     12000

/*
* @brief          : This macro is used to configure the AFE Bias factor value
* @Unit           : None
* @Resolution:    : 0.1
* @Range          : 5 to 20
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define AFE_BIAS_FACTOR                             10

/*
* @brief          : This macro is used to configure the AFE Init distance value
* @Unit           : meter
* @Resolution:    : 0.1 km
* @Range          : 0 to 1000
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define AFE_INIT_DIST              (uint64)                 100000

/*
* @brief          : This macro is used to configure the AFE Init distance value
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 1
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define AFE_NVM_FUEL_ACC_CALC_IDLE                  0

/*
* @brief          : This macro is used to configure the AFE Init distance value
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 1
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define FUEL_TIME_FACTOR                            0.2

/*
* @brief          : This macro is used to configure the RAFE distance Max value
* @Unit           : KM
* @Resolution:    : 0.1km
* @Range          : 0 to 20000
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define DTE_RAFE_DIST_MAX         (uint64)                  10000000

/*
* @brief          : This macro is used to configure the Max DTE Difference
* @Unit           : KM
* @Resolution:    : 0.1km
* @Range          : 0 to 5
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define MAX_DTE_DIFF                                50

/*
* @brief          : This macro is used to configure the Minimum Speed  
* @Unit           : KMPH
* @Resolution:    : 1kmph
* @Range          : 0 to 5
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define RAFE_MIN_SPEED             (uint8_t)                  0

/*
* @brief          : This macro is used to configure the Max Speed  
* @Unit           : KMPH
* @Resolution:    : 1kmph
* @Range          : 190 - 255
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define RAFE_MAX_SPEED           (uint8_t)                    199

/*
* @brief          : This macro is used to configure the update display time
* @Unit           : sec
* @Resolution:    : None
* @Range          : 0 to 1000
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define DTE_DISPLAY_UPDATE_TIME                     100

/*
* @brief          : This macro is used to configure the DTE Min
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 100
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define DTE_MIN             (uint32)                        25

/*
* @brief          : This macro is used to configure the DTE Max
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 999
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define DTE_MAX             (uint32)                         999

/*
* @brief          : This macro is used to configure the RAFE Scale factor
* @Unit           : None
* @Resolution:    : 0.1
* @Range          : 5 - 20
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define RAFE_SCALE_FACTOR                           4

/*
* @brief          : This macro is used to configure the RAFE Scale factor
* @Unit           : None
* @Resolution:    : 0.1
* @Range          : 0.5 - 2
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define RAFE_BIAS                                   1

/*
* @brief          : This macro is used to configure the RAFE Scale factor
* @Unit           : KM
* @Resolution:    : 0.1
* @Range          : 0 - 20000
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define RAFE_ACCU_MAX            (uint64)                   100000000

/*
* @brief          : This macro is used to configure the RAFE Scale factor
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 - 10
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define RAFE_ACCU_ROLLBACK       (uint64)                    4

/*
* @brief          : This macro is used to configure the Min RAFE
* @Unit           : None
* @Resolution:    : 0.1Km/l
* @Range          : 0 - 200
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define MIN_RAFE                 (uint32)                    50

/*
* @brief          : This macro is used to configure the DEAD Vol
* @Unit           : Boolean
* @Resolution:    : 0.1l
* @Range          : 0 - 100
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define DEAD_VOL                                     0

/*
* @brief          : This macro is used to configure the DTE Inc allowed
* @Unit           : None
* @Resolution:    : Boolean
* @Range          : True/False
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define DTE_INC_ALLOWED                               FALSE
/*
* @brief          : This macro is used to configure the Default RAFE
* @Unit           : Km/l
* @Resolution:    : 1km/l
* @Range          : 0 - 200
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define DEFAULT_RAFE                                   300

/*
* @brief          : This macro is used to configure the unit selection for US
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 8 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define TC_UNIT_SELECTION_US_MPG        (uint8_t)            4

/*
* @brief          : This macro is used to configure the unit selection for UK
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 8 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define TC_UNIT_SELECTION_UK_MPG        (uint8_t)            3

/*
* @brief          : This macro is used to configure the unit selection for KML
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 8 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define TC_UNIT_SELECTION_KML         (uint8_t)              2

/*
* @brief          : This macro is used to configure the unit selection for L/Km
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 8 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/
#define TC_UNIT_SELECTION_L_KM     (uint8_t)                 1

/*
* @brief          : This macro is used to configure CAN bus off status
* @Unit           : None
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name
*/

#define TC_CAN_BUS_OFF_STATUS          (uint8_t)             0
/*
* @brief          : This macro is used to configure factor value to be multiply by fuel capacity get from fuel table 
*                   to convert it into Micro litres.
* @Unit           : None
* @Resolution:    : 
* @Range          : 0 to 32 bit
* @Applicability  : YES
* @Note           : Do not modify this macro value or name.  Currently in fuel table ,  fuel capacity is in 0.1L resolution,
*                   Ex:  For Fuel bar 4,  Fuel capacity configured is 87 (8.7 L)  ,  87 * 100000 = 8700000 micro litres.
*/
#define FUEL_CAPACITY_UL_CONVERSTION_FACTOR   (uint32)      100000



#define AFE_RESOULTION_FACTOR    (uint64)   1675

/*********************************************************************************************************************
*                                          G L O B A L   V A R I A B L E    D E C L A R A T I O N S                                    
*********************************************************************************************************************/
/*
* @brief: This variable is used to hold the the precondition status
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint8_t g_IFE_Precondition_Status_u8;


afe_sample_type_st afe_sample_st[TRIP_MAX];

/*
* @brief: This variable is used to hold the the precondition status
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255
  @Applicability: YES
*/
static uint8_t g_AFE_Precondition_Status_u8;

/*
* @brief: This variable is used to hold the the precondition status
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint8_t g_DTE_Precondition_Status_u8;

/*
* @brief: This variable is used to CAN_ECM_Status
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint8_t g_CAN_ECM_Status_u8;

static uint8_t g_CAN_Missing_Detect;

/*
@brief: This variable is used to store  AFE_FUEL_CALC_Status
  @Unit: uint8_t
  @Resolution: 1
  @Range: 0 to 1
  @Applicability: YES
*/
static uint8_t  g_AFE_NVM_FUEL_ACC_CALC_IDLE;

/* @brief: This variable is used to CAN_ABS_Vehicle_Speed_Status
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint8_t g_CAN_ABD_Vehicle_Speed_Status_u8;

/*
* @brief: This variable is used to CAN_ECM_Status
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint8_t g_IFE_Display_Update_time_u8;

/*
* @brief: This variable is used to store the current odo value
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 32 bit 
  @Applicability: YES
*/
static uint32_t g_Cur_odo_u32;

/*
* @brief: This variable is used to store the previous odo value
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 32 bit
  @Applicability: YES
*/
static uint32_t g_prv_odo_u32;

/*
* @brief: This variable is used to store the CAN message value of IFE
  @Unit: N/A
  @Resolution: N/A
  @Range: 32 bit
  @Applicability: YES
*/
static float g_Get_CAN_value_fl;

/*
* @brief: This variable is used to store the CAN message value of IFE
  @Unit: N/A
  @Resolution: N/A
  @Range: 32 bit
  @Applicability: YES
*/
static float g_Get_IFE_CAN_value_fl;

/*
* @brief: This variable is used to store the CAN message value of AFE
  @Unit: N/A
  @Resolution: N/A
  @Range: 32 bit 
  @Applicability: YES
*/
static float g_Get_AFE_CAN_value;

/*
* @brief: This variable is used to Store the AFE display update timer
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint8_t g_AFE_Display_Update_time_u8;

/*
* @brief: This variable is used to store the CAN message value of AFE
  @Unit: N/A
  @Resolution: 1
  @Range: 32 bit 
  @Applicability: YES
*/
static uint16_t g_Get_DTE_CAN_value;

/*
* @brief: This variable is used to Store the AFE display update timer
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint8_t g_DTE_Display_Update_time_u8;

/*
* @brief: This variable is used to store the Odo value
  @Unit: N/A
  @Resolution: 1
  @Range: 32bit
  @Applicability: YES
*/
static uint32_t g_Delta_Dist_Accu_u32;

/*
* @brief: This variable is used to store the DTE value
  @Unit: N/A
  @Resolution: 1
  @Range: 32bit
  @Applicability: YES
*/
static uint32_t g_Value_DTE;

/*
* @brief: This variable is used to store the DTE Inc Allowed
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint8_t g_DTE_Inc_allowed_u8;
/*
* @brief: This variable is used to samples
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255
  @Applicability: YES
*/
static uint8_t g_sample_u8;

/*
* @brief: This variable is used to index
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint8_t g_IFE_index_u8;

/*
* @brief: This variable is used to store the IFE value
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
//static float g_IFE_u32;
static uint32_t g_IFE_u32;

/*
* @brief: This variable is used to store the IFE ODO value
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint32_t g_IFE_ODO_u32;

/*
* @brief: This variable is used to store the IFE Calculation value
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255
  @Applicability: YES
*/
static float g_IFE_CAL_f32[IFE_MAX_SAMPLES_CNT];

static float g_IFE_CALCULATION;

/*
* @brief: This variable is used to set the unit
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint8_t g_current_fuel_cons_unit_set_u8;

/*
* @brief: This variable is used to display the value of IFE
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint32_t g_Display_IFE_Value = 0;

/*
* @brief: This variable is used to display the value of IFE
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint32_t Displayed_IFE_value_u32;

/*
* @brief: This variable is used to store the previous value of IFE
  @Unit: N/A
  @Resolution: 1
  @Range: 32bit 
  @Applicability: YES
*/
static uint32_t g_IFE_Previous_KM_Per_Litre_u32;

/*
* @brief: This variable is used to store the value of IFE Pre Litre
  @Unit: N/A
  @Resolution: 1
  @Range: 32bit 
  @Applicability: YES
*/
static uint32_t g_IFE_KM_Per_Litre_u32 = 0;

/*
* @brief: This variable is used to store the Trip km value
  @Unit: N/A
  @Resolution: 1
  @Range: 32bit
  @Applicability: YES
*/
uint32_t g_Trip_Km_u32[TRIP_MAX];

/*
* @brief: This variable is used to Store the Trip_Dist_N km
  @Unit: N/A
  @Resolution: 1
  @Range: 32bit 
  @Applicability: YES
*/
static uint32_t g_Trip_Dist_N_u32[TRIP_MAX];

/*
* @brief: This variable is used to Store the Trip_Dist km
  @Unit: N/A
  @Resolution: 1
  @Range: 32bit
  @Applicability: YES
*/
static uint32_t g_Trip_Dist_u32[TRIP_MAX];

/*
* @brief: This variable is used to Store the Trip delta value
  @Unit: N/A
  @Resolution: 1
  @Range: 32bit 
  @Applicability: YES
*/
static uint32_t g_Trip_delta_u32[TRIP_MAX];

/*
* @brief: This variable is used to store the Trip reset trigger status
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint8_t g_Trip_AFE_Reset_Trigger_u8[TRIP_MAX];

/*
* @brief: This variable is used to store the Trip Sw reset status
  @Unit: N/A
  @Resolution: 1
  @Range: 0 to 255 
  @Applicability: YES
*/
static uint8_t g_Trip_AFE_Sw_Reset_u8[TRIP_MAX];

/*
* @brief: This variable is used to store AFE distance Accumulation value
  @Unit: KM
  @Resolution: 1
  @Range: 0 to 16 bit 
  @Applicability: YES
*/
static uint64_t g_AFE_Dist_ACCU_u64[TRIP_MAX];

/*
* @brief: This variable is used to store AFE Fuel Accumulation value
  @Unit: KM
  @Resolution: 1
  @Range: 0 to 16 bit 
  @Applicability: YES
*/
static uint32_t g_AFE_Fuel_Cons_ACCU_u32[TRIP_MAX];

/*
* @brief: This variable is used to store AFE Calculate value
  @Unit: Kmpl
  @Resolution: 0.1
  @Range: 0 to 32bit
  @Applicability: YES
*/
static uint64_t g_AFE_Cal_u64[TRIP_MAX];

/*
* @brief: This variable is used to store AFE Calculate value
  @Unit: Kmpl
  @Resolution: 0.1
  @Range: 0 to 32bit
  @Applicability: YES
*/
static uint32_t g_AFE_Display_value_u32[TRIP_MAX];

/*
* @brief: This variable is used to display the value of AFE
  @Unit: N/A
  @Resolution: 1
  @Range: 32bit 
  @Applicability: YES
*/
static uint32_t g_Displayed_AFE_u32[TRIP_MAX];

/*
* @brief: This variable is used to Read the Distance from NVM
  @Unit: N/A
  @Resolution: 1
  @Range: 32bit 
  @Applicability: YES
*/
static uint32_t g_Dist_Readsync_u32[TRIP_MAX];

/*
* @brief: This variable is used to Fuel the Distance from NVM
  @Unit: N/A
  @Resolution: 1
  @Range: 32bit 
  @Applicability: YES
*/
static uint32_t g_Fuel_Readsync_u32[TRIP_MAX];

/*
* @brief: This variable is used to define the Active function flag
  @Unit:  N/A
  @Resolution: N/A
  @Range: Activate or Deactivate 
  @Applicability: YES
*/
static _Bool g_TC_ActiveFlag_u8;

/*
* @brief: This function is used to find the IFE compute for Trip Computer 
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES
*/
static void TC_IFE_Compute(uint8_t unit_selection_u8);

/*
* @brief: This function is used to find the AFE compute for Trip Computer 
  @Unit:  N/A
  @Resolution: N/A
  @Range: 0 - 255 
  @Applicability: YES
*/
static uint8_t g_Odo_data_reset;

/*
* @brief: This variable is used to define the odo data write value
  @Unit:  N/A
  @Resolution: N/A
  @Range: 0 - 255 
  @Applicability: YES
*/
static uint8_t g_Odo_data_write;

/*
* @brief: This variable is used to define the the Odo value
  @Unit:  N/A
  @Resolution: N/A
  @Range: 32bit 
  @Applicability: YES
*/
static uint32_t g_Get_Odo_km_value_u32;

/*
* @brief: This variable is used to define the the Previous Odo value
  @Unit:  N/A
  @Resolution: N/A
  @Range: 32bit 
  @Applicability: YES
*/
static uint32_t g_Prev_Odo_Km_val_u32;

/*
* @brief: This variable is used to store DTE Fuel Accumulation value
  @Unit: KM
  @Resolution: 1
  @Range: 32 bit 
  @Applicability: YES
*/
static uint32_t g_RAFE_Fuel_Cons_ACCU_u32;

/*
* @brief: This variable is used to store the RAFE Distance accumulator value
  @Unit: KM
  @Resolution: 1
  @Range: 32bit 
  @Applicability: YES
*/
static uint64_t g_RAFE_Dist_Accu_u64;

/*
* @brief: This variable is used to store the current RAFE Value
  @Unit: KM
  @Resolution: 1
  @Range: 32 bit 
  @Applicability: YES
*/
static uint32_t	g_Current_RAFE_u32;

/*
* @brief: This variable is used to store the Rollover value
  @Unit: KM
  @Resolution: 1
  @Range: 0 to 16 bit 
  @Applicability: YES
*/
static uint8_t g_RAFE_Rollover_Done_u8;

/*
* @brief: This variable is used to store the RAFE value
  @Unit: KM
  @Resolution: 1
  @Range: 0 to 16 bit 
  @Applicability: YES
*/
static uint32_t g_RAFE_u32;

/*
* @brief: This variable is used to store the calculate DTE value
  @Unit: KM
  @Resolution: 1
  @Range: 0 to 32 bit 
  @Applicability: YES
*/
static uint32_t g_Calc_DTE_u32;

/*
* @brief: This variable is used to store the calculate DTE value
  @Unit: KM
  @Resolution: 1
  @Range: 0 to 64 bit 
  @Applicability: YES
*/
static uint64_t g_CAL_RAFE_FUEL_REM_u64;

bool g_CAN_BUS_OFF_Det_Status;

/*
* @brief: This variable is used to store the Displayed DTE value
  @Unit: KM
  @Resolution: 1
  @Range: 0 to 16 bit 
  @Applicability: YES
*/
static uint32_t g_Disp_DTE_u32;

/*
* @brief: This variable is used to store the DTE Init
  @Unit: KM
  @Resolution: 1
  @Range: 0 to 16 bit 
  @Applicability: YES
*/
static uint8_t g_DTE_Init_u8;

static uint8_t g_fuel_Previous_Status;
/*
* @brief: This variable is used to store the fuel bar value
  @Unit: litre
  @Resolution: 1
  @Range: uint8_t 
  @Applicability: YES
*/
static uint8_t g_FuelBar_u8;

/*
* @brief: This variable is used to store the Previous fuel bar value
  @Unit: NA
  @Resolution: 1
  @Range: 8bit 
  @Applicability: YES
*/
static uint8_t g_Prev_FuelBar_u8;

/*
* @brief: This variable is used to store the Fuel init status
  @Unit: NA
  @Resolution: 1
  @Range: 8bit
  @Applicability: YES
*/
static uint8_t g_Fuel_Init_Status;

/*
* @brief: This variable is used to store the DTE Fuel consum processing time
  @Unit: NA
  @Resolution: 1
  @Range: 0 to 8 bit 
  @Applicability: YES
*/
static uint8_t g_Fuel_Consum_process_time_u8;

/*
* @brief: This variable is used to store the DTE calculation processing time
  @Unit: NA
  @Resolution: 1
  @Range: 0 to 8 bit 
  @Applicability: YES
*/
static uint8_t g_Cal_DTE_Processing_Time;

/*
* @brief: This variable is used to store the IFE CAN calculation processing time
  @Unit: NA
  @Resolution: 1
  @Range: 0 to 8 bit 
  @Applicability: YES
*/
static uint8_t g_IFE_CAN_Process_Time_u8;

/*
* @brief: This variable is used to store the AFE CAN calculation processing time
  @Unit: NA
  @Resolution: 1
  @Range: 0 to 8 bit 
  @Applicability: YES
*/
static uint8_t g_AFE_CAN_Process_Time_u8;

/*
* @brief: This variable is used to store the DTE CAN calculation processing time
  @Unit: NA
  @Resolution: 1
  @Range: 0 to 8 bit 
  @Applicability: YES
*/
static uint8_t g_DTE_CAN_Process_Time_u8;

static uint32_t g_fuel_capacity_Litre_Val_u32;

/*
* @brief: This variable is used to store the fuel used value
  @Unit: litre
  @Resolution: 0.1
  @Range: float 
  @Applicability: YES
*/
static uint32_t g_FuelUsed_u32;

static float g_Fuel_Used_val;

/*
* @brief: This variable is used to store the fuel Remaining value
  @Unit: litre
  @Resolution: 0.1
  @Range: float 
  @Applicability: YES
*/
static uint32_t g_Fuel_Remaining_u32;

bool g_TC_IGN_ON_Status;

/*
* @brief	This function is used to find the IFE compute for Trip Computer 
* @param    void
* @return   uint8_t
* @note:    N/A
*/
static void TC_IFE_Compute(uint8_t unit_selection_u8);

/*
* @brief	This function is used to find the AFE compute for Trip Computer
* @param    void
* @return   uint8_t , uint8_t
* @note:    N/A
*/
static void TC_AFE_Compute(uint8_t unit_selection_u8, uint8_t trip_id);

/*
* @brief	This function is used to find the AFE compute for Trip Computer 
* @param    void
* @return   uint8_t
* @note:    N/A
*/
static void TC_DTE_Compute(uint8_t unit_selection_u8, uint32_t Cal_DTE_value);

/*
* @brief    This function is used for IFE preconditions
* @param    void
* @return   uint8_t
* @note:    N/A
*/
uint8_t IFE_Pre_Condition(void);

/*
* @brief    This function is used for AFE preconditions
* @param    void
* @return   uint8_t
* @note:    N/A
*/
uint8_t AFE_Pre_Condition(void);

/*
* @brief    This function is used for IFE Status
* @param    void
* @return   void
* @note:    N/A
*/
void TC_IFE_Status(void);


/*
* @brief    This function is used for AFE preconditions
* @param    void
* @return   uint8_t
* @note:    N/A
*/
uint8_t DTE_Pre_Condition(void);

/*
* @brief    This function is used for RAFE distance and fuel Calculation
* @param    void
* @return   void
* @note:    N/A
*/
void DTE_RAFE_Dist_Fuel_Calculation(void);

/*
* @brief    This function is used for Calculation DTE Processing
* @param    void
* @return   void
* @note:    N/A
*/
void Cal_DTE_Processing(void);

/*
* @brief    This function is used for DTE Init
* @param    void
* @return   uint8_t
* @note:    N/A
*/
uint8_t DTE_Init(void);

/*
* @brief    This function is used for DTE Displayed calculation
* @param    void
* @return   void
* @note:    N/A
*/
void DTE_DisplayCalculation(void);

/*
* @brief    This function is used for RAFE Fuel Consumption Accu processing
* @param    void
* @return   void
* @note:    N/A
*/
void RAFE_Fuel_Consumption_Acc_Processing(void);

/*
* @brief    This function is used for Delta DTE DistanceComp calculation
* @param    uint32_t
* @return   float
* @note:    N/A
*/
uint16_t DeltaDTE_DistanceComp(int16_t delta_dist_s16);

static uint16_t g_DTE_Cur_odo_u16;
static uint16_t g_DTE_prv_odo_u16;
static uint16_t g_DTE_Delta_u16;

static uint32_t g_DTE_delta_Dist_Accu_u32;

/*********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N S                     
*********************************************************************************************************************/

/*
* @brief    This function is used to initialize the Trip computer
* @param    None 
* @return   None
*/
void TC_Warm_init(void)
{
	uint8_t fl_Loop_Idx = 0;

	/*To Init the IFE precondition value*/
	g_IFE_Precondition_Status_u8 = FALSE;
	
	/*To init the Previous odo value*/
	g_prv_odo_u32 = 0;

	/*To init the Current odo value*/
	g_Cur_odo_u32 = 0;

	/*To Init the IFE ODO value*/
	g_IFE_ODO_u32 = 0;

	/*To Init the index of IFE */
	g_IFE_index_u8 = 0;

	/*To Init the IFE value*/
	g_IFE_u32 = 0;

	g_IFE_CALCULATION = 0;

	/*To Init the Process time*/
	g_IFE_CAN_Process_Time_u8 = 0;

	/*To Init the CAN message value of IFE*/
	g_Get_IFE_CAN_value_fl = 0;

	g_TC_IGN_ON_Status = TRUE;

	/*Hold the display time*/
	g_IFE_Display_Update_time_u8 = 0;

	/*To Init the IFE Display value*/
	g_Display_IFE_Value = 0;

	/*To Init the IFE Display value*/
	Displayed_IFE_value_u32 = 0;

	/*To Init the Previous IFE value*/
	g_IFE_Previous_KM_Per_Litre_u32 = 0;

	/*To Init the IFE Km litre value*/
	g_IFE_KM_Per_Litre_u32 = 0;

	/*To Init the AFE precondition value*/
	g_AFE_Precondition_Status_u8 = FALSE;

	/*To read the data of AFE Value*/
	Swc_AFE_Readsync();

	for(uint8_t trip_id = 0; trip_id < TRIP_MAX; trip_id++)
	{
		/*To Init store the Trip km value*/
		g_Trip_Km_u32[trip_id] = 0;
		
		/*To Init store the Trip km value*/
		g_Trip_Dist_N_u32[trip_id] = IFE_ODO_value();

		afe_sample_st[trip_id].index = 0;

		memset(&afe_sample_st[trip_id].array[0], 0, sizeof(uint32_t)*10);
	}

	/*To Init the Process time*/
	g_AFE_CAN_Process_Time_u8 = 0;

	/*To Init the CAN message value of AFE*/
	g_Get_AFE_CAN_value = 0;

	/*Hold the display time*/
	g_AFE_Display_Update_time_u8 = 0;
	
	/*To Init the AFE precondition value*/
	g_DTE_Precondition_Status_u8 = FALSE;

	/*To store the DTE Init value*/
	g_DTE_Init_u8 = FALSE;

	/*To store the Rollover Init value*/
	g_RAFE_Rollover_Done_u8 = FALSE;

	Swc_DTE_Readsync();	
	
	/*Hold the display time of DTE*/
	g_DTE_Display_Update_time_u8 = IFE_INITIAL_DISPLAY_UPDATE_TIME;

	/*To Init the DTE Odo value*/
	g_Delta_Dist_Accu_u32 = 0;  

	g_DTE_delta_Dist_Accu_u32 = 0;

	g_fuel_Previous_Status = 0;

	/*To Init the DTE value*/
	g_Value_DTE = 0;

	/*To Init the Odo data reset value*/
	g_Odo_data_reset = 0;

	/*To Init the Odo data write value*/
	g_Odo_data_write = 0;
	
	/*To Init the CAN ECM status as FALSE*/
	g_CAN_ECM_Status_u8 = FALSE;
	
	/*To Init the ABS Vehicle speed status as FALSE*/
	g_CAN_ABD_Vehicle_Speed_Status_u8 = TRUE;
	
	/*To Init the Odo Value in Km*/
	g_Get_Odo_km_value_u32 = 0;

	/*To Init the current RAFE Value*/
	g_Current_RAFE_u32 = 0;
	
	/*To Init the fuel bar value*/
	g_FuelBar_u8 = 0;

	/*To Init the Previous fuel bar value*/
	g_Prev_FuelBar_u8 = 0;

	/*To init the Fuel init status*/
	g_Fuel_Init_Status = 1;
	
	/*To Init the DTE Inc Allowed value*/
	g_DTE_Inc_allowed_u8 = FALSE;

	/*To Init the Process time*/
	g_Fuel_Consum_process_time_u8 = 1;

	/*To Init the Process time*/
	g_Cal_DTE_Processing_Time = 1;

	/*To Init the Fuel used value*/
	g_FuelUsed_u32 = 0;

	/*To call the activate the IFE*/
	TC_Activate();

	/* Update previous odo value */
	g_Prev_Odo_Km_val_u32 = GET_ODO_VALUE_KM();

	for(fl_Loop_Idx = 0 ; fl_Loop_Idx < IFE_MAX_INDEX_CNT; fl_Loop_Idx++)
	{
		/*To Init the IFE Calculation value*/
		g_IFE_CAL_f32[fl_Loop_Idx] = 0;
	}

	g_CAN_BUS_OFF_Det_Status = FALSE;
}

/*
* @brief    This function is used to cold initialize the Trip computer
* @param    None 
* @return   None
*/
void TC_Cold_init(void)
{
	uint8_t fl_Loop_Idx = 0;

	/*To Init the IFE precondition value*/
	g_IFE_Precondition_Status_u8 = FALSE;
	
	/*To init the Previous odo value*/
	g_prv_odo_u32 = 0;

	/*To init the Current odo value*/
	g_Cur_odo_u32 = 0;

	/*To Init the IFE ODO value*/
	g_IFE_ODO_u32 = 0;

	/*To Init the index of IFE */
	g_IFE_index_u8 = 0;

	/*To Init the IFE value*/
	g_IFE_u32 = 0;

	g_IFE_CALCULATION = 0;

	/*To Init the Process time*/
	g_IFE_CAN_Process_Time_u8 = 0;

	/*To Init the CAN message value of IFE*/
	g_Get_IFE_CAN_value_fl = 0;

	g_TC_IGN_ON_Status = TRUE;

	/*Hold the display time*/
	g_IFE_Display_Update_time_u8 = 0;

	/*To Init the IFE Display value*/
	g_Display_IFE_Value = 0;

	/*To Init the IFE Display value*/
	Displayed_IFE_value_u32 = 0;

	/*To Init the Previous IFE value*/
	g_IFE_Previous_KM_Per_Litre_u32 = 0;

	/*To Init the IFE Km litre value*/
	g_IFE_KM_Per_Litre_u32 = 0;

	/*To Init the AFE precondition value*/
	g_AFE_Precondition_Status_u8 = FALSE;

	/*To read the data of AFE Value*/
	Swc_AFE_Readsync();

	for(uint8_t trip_id = 0; trip_id < TRIP_MAX; trip_id++)
	{
		/*To Init store the Trip km value*/
		g_Trip_Km_u32[trip_id] = 0;
		
		/*To Init store the Trip km value*/
		g_Trip_Dist_N_u32[trip_id] = IFE_ODO_value();

		afe_sample_st[trip_id].index = 0;

		memset(&afe_sample_st[trip_id].array[0], 0, sizeof(uint32_t)*10);
	}

	/*To Init the Process time*/
	g_AFE_CAN_Process_Time_u8 = 0;

	/*To Init the CAN message value of AFE*/
	g_Get_AFE_CAN_value = 0;

	/*Hold the display time*/
	g_AFE_Display_Update_time_u8 = 0;
	
	/*To Init the AFE precondition value*/
	g_DTE_Precondition_Status_u8 = FALSE;

	/*To store the DTE Init value*/
	g_DTE_Init_u8 = TRUE;

	/*To store the Rollover Init value*/
	g_RAFE_Rollover_Done_u8 = FALSE;

    /* Initialize distance accumulator for DTE*/
	g_RAFE_Dist_Accu_u64 = 0;

    /* Initialize fuel accumulator for DTE*/
	g_RAFE_Fuel_Cons_ACCU_u32 = 0;
	
	/* fuel remaining initialize to zero*/
	g_Fuel_Remaining_u32 = 0;

	/*Hold the display time of DTE*/
	g_DTE_Display_Update_time_u8 = IFE_INITIAL_DISPLAY_UPDATE_TIME;

	/*To Init the DTE Odo value*/
	g_DTE_delta_Dist_Accu_u32 = 0;

	g_fuel_Previous_Status = 0;

	/*To Init the DTE value*/
	g_Value_DTE = 0;

	/*To Init the Odo data reset value*/
	g_Odo_data_reset = 0;

	/*To Init the Odo data write value*/
	g_Odo_data_write = 0;

	/*To Init the RAFE value*/
	g_RAFE_u32 = DEFAULT_RAFE;
	
	/*To Init the CAN ECM status as TRUE*/
	g_CAN_ECM_Status_u8 = FALSE;
	
	/*To Init the ABS Vehicle speed status as FALSE*/
	g_CAN_ABD_Vehicle_Speed_Status_u8 = TRUE;
	
	/*To Init the Odo Value in Km*/
	g_Get_Odo_km_value_u32 = 0;

	/*To Init the current RAFE Value*/
	g_Current_RAFE_u32 = 0;
	
	/*To Init the fuel bar value*/
	g_FuelBar_u8 = 0;

	/*To Init the Previous fuel bar value*/
	g_Prev_FuelBar_u8 = 0;

	/*To init the Fuel init status*/
	g_Fuel_Init_Status = 1;
	
	/*To Init the DTE Inc Allowed value*/
	g_DTE_Inc_allowed_u8 = FALSE;

	/*To Init the Process time*/
	g_Fuel_Consum_process_time_u8 = 1;

	/*To Init the Process time*/
	g_Cal_DTE_Processing_Time = 1;

	/*To Init the Fuel used value*/
	g_FuelUsed_u32 = 0;

	/* Displya DTE */
	g_Disp_DTE_u32 = TC_INVALID;

	g_Value_DTE = TC_INVALID;

	/*To call the activate the IFE*/
	TC_Activate();

	/* Update previous odo value */
	g_Prev_Odo_Km_val_u32 = GET_ODO_VALUE_KM();

	for(fl_Loop_Idx = 0 ; fl_Loop_Idx < IFE_MAX_INDEX_CNT; fl_Loop_Idx++)
	{
		/*To Init the IFE Calculation value*/
		g_IFE_CAL_f32[fl_Loop_Idx] = 0;
	}

	g_CAN_BUS_OFF_Det_Status = FALSE;
}

/*
* @brief    This function is Active function or main function of the IFE
* @param    None 
* @return   None
*/
void IFE_Active(void)
{
	/*Store the precondition value*/
	g_IFE_Precondition_Status_u8 = IFE_Pre_Condition();

	/*To increment the CAN Process time*/
	g_IFE_CAN_Process_Time_u8 = g_IFE_CAN_Process_Time_u8 + 1;

	/*To check the process time*/
	if (g_TC_ActiveFlag_u8 == TC_ACTIVATE)
	{
		TC_IFE_Status();
	}
		
}

/*
* @brief    This function is used to Calculate the IFE Status
* @param    None 
* @return   None
*/
void TC_IFE_Status(void)
{
	/*To store the Acc Fuel Value*/
	static float64 fl_Read_Acc_Fuel_Inj_Value_f64 = 0;

	static float64 fl_Get_IFE_CAN_value_fl = 0;
		
	/*To store the addition sample value*/
	uint32_t fl_add_IFE_f32 = 0;

	float64 fl_Get_IFE_CAL_f32 = 0;

	/*To Store the samples*/
	uint8_t fl_sample_u8 = 0;
	
	/*To store the displayed IFE Unit*/
	uint8_t fl_Displayed_IFE_unit = 0;
	
	/*Check the precondition status*/
	if(g_IFE_Precondition_Status_u8 == TRUE)
	{
		/*To get the odo value*/
		g_Cur_odo_u32 = GET_ODO_VALUE();

		/*Store the CAN message value*/
		(void) CanMgr_Read_accumulat_fuel_inj_time_fuel_qty_0x135_s(&fl_Read_Acc_Fuel_Inj_Value_f64);
		
		/*Check the index count*/
		if(g_IFE_index_u8 >= IFE_INDEX_COUNT)
		{
			g_IFE_index_u8 = 0;
		}

		/*Check the current and Previous Odo value*/
		if(g_prv_odo_u32 > g_Cur_odo_u32)
		{
			/*Hold the ODO value*/
			g_IFE_ODO_u32 = (g_Cur_odo_u32 + 10000) - g_prv_odo_u32;
		}
		else
		{
			/*Hold the ODO value*/
			g_IFE_ODO_u32 = g_Cur_odo_u32 - g_prv_odo_u32;
		}
		
		/*Store the current odo value*/
		g_prv_odo_u32 = g_Cur_odo_u32;

		/*To store the CAN Value*/
		fl_Get_IFE_CAN_value_fl = fl_Read_Acc_Fuel_Inj_Value_f64;

		/*To store the CAN Value*/
		g_Get_IFE_CAN_value_fl = fl_Get_IFE_CAN_value_fl;
	
		/*Hold the IFE CAL value*/
		fl_Get_IFE_CAL_f32 = (g_IFE_ODO_u32 / g_Get_IFE_CAN_value_fl);

		/*To check the CAN Missing is Detected or not*/
		if(g_CAN_Missing_Detect == FALSE)
		{
			/*To change the missing flag*/
			g_CAN_Missing_Detect = TRUE;

		}
		else
		{
			/*To Calculate IFE Value*/
			g_IFE_CAL_f32[g_IFE_index_u8] = fl_Get_IFE_CAL_f32;

			/*increment index count*/
			g_IFE_index_u8++;

			
			for(fl_sample_u8 = 0; fl_sample_u8 < IFE_MAX_INDEX_CNT; fl_sample_u8++)
			{
				/*add the samples*/
				fl_add_IFE_f32 += g_IFE_CAL_f32[fl_sample_u8];
			}
			
			g_IFE_u32 = (float)fl_add_IFE_f32 / IFE_MAX_INDEX_CNT;

			/*To get the unit selection from user*/
			g_current_fuel_cons_unit_set_u8 = GET_UNIT_SELCETION;
			
			/*To hold the current fuel unit*/
			fl_Displayed_IFE_unit = g_current_fuel_cons_unit_set_u8;
			
			/*Check the display timer and sample count*/
			if(g_IFE_Display_Update_time_u8 == 0)
			{
				/*Hold the display time*/
				g_IFE_Display_Update_time_u8 = IFE_DISPLAY_TIME;

				/*Call the calculation function*/
				TC_IFE_Compute(fl_Displayed_IFE_unit);
		
			}
			else if(g_IFE_Display_Update_time_u8 != 0)
			{
				/*Decrement the update timer count*/
				g_IFE_Display_Update_time_u8--;

			}
		}
	}
	else
	{
		/*Store the fuel value*/
		g_Get_IFE_CAN_value_fl = 0;

		/*Store the displayed value*/
		g_Display_IFE_Value = TC_INVALID;

		/*Store the displayed value*/
		Displayed_IFE_value_u32 = TC_INVALID;

		/*To Init the IFE Km litre value*/
		g_IFE_KM_Per_Litre_u32 = TC_INVALID;
	}
}

/*
* @brief    This function is used to compute the IFE
* @param    None 
* @return   None
*/
static void TC_IFE_Compute(uint8_t unit_selection_u8)
{
	/*To store the displayed IFE Unit*/
	uint8_t Displayed_IFE_unit_u8;

	uint32_t fl_IFE_Current_KM_Per_Litre_u32 = 0;

	uint32_t fl_IFE_Delta_KM_Per_Litre_u32 = 0;

	/*To store the unit selection*/
	Displayed_IFE_unit_u8 = TC_UNIT_SELECTION_KML;

	fl_IFE_Current_KM_Per_Litre_u32 = g_IFE_u32 / 10000;

	/*CHeck the unit selection*/
	if(Displayed_IFE_unit_u8 == TC_UNIT_SELECTION_US_MPG)
	{
		/*This variable is to display the IFE Value*/
		//g_Display_IFE_Value = (fl_IFE_KM_Per_Litre_f32) * (UK_MPG_CONV_FACTOR);
		Displayed_IFE_value_u32 = (g_IFE_Previous_KM_Per_Litre_u32) * (UK_MPG_CONV_FACTOR);
	}
	
	/*CHeck the unit selection*/
	else if(Displayed_IFE_unit_u8 == TC_UNIT_SELECTION_UK_MPG)
	{
		/*This variable is to display the IFE Value*/
		//g_Display_IFE_Value = (fl_IFE_KM_Per_Litre_f32) * (US_MPG_CONV_FACTOR);
		Displayed_IFE_value_u32 = (g_IFE_Previous_KM_Per_Litre_u32) * (US_MPG_CONV_FACTOR);
	}
	
	/*CHeck the unit selection*/
	else if(Displayed_IFE_unit_u8 == TC_UNIT_SELECTION_KML)
	{
		/*This variable is to display the IFE Value*/
		Displayed_IFE_value_u32 = fl_IFE_Current_KM_Per_Litre_u32;
	}
	else if(Displayed_IFE_unit_u8 == TC_UNIT_SELECTION_L_KM)
	{
		/*This variable is to display the IFE Value*/
		Displayed_IFE_value_u32 = fl_IFE_Current_KM_Per_Litre_u32;
	}
	
	else
	{
		/*Do Nothing*/
	}

	if(Displayed_IFE_value_u32 > IFE_MAX)
	{
		Displayed_IFE_value_u32 = IFE_MAX;
	}
}

/*
* @brief    This function is used to display the IFE Value
* @param    None 
* @return   None
*/
uint32_t display_IFE(void)
{
	return g_Display_IFE_Value;
}


uint32_t displayed_IFE(void)
{
    uint32_t fl_Displayed_IFE = 0;

    fl_Displayed_IFE = Displayed_IFE_value_u32;

    if(fl_Displayed_IFE != TC_INVALID)
    {
        fl_Displayed_IFE = fl_Displayed_IFE;
    }
    else
    {
        fl_Displayed_IFE = TC_INVALID;
    }
    return fl_Displayed_IFE;
}


/*
* @brief    This function is Active function or main function of the AFE
* @param    None 
* @return   None
*/
void AFE_Active(void)
{
	/*To store the Acc Fuel Value*/
	static float64 fl_Read_Acc_Fuel_Inj_Value_f64 = 0;

	/*Store the Speed fault status*/
	bool fl_AFE_Speedfault_status_bool = TRUE;

	static float64 fl_Get_AFE_CAN_value_fl = 0;

	/*This variable is used to store the CAN message value*/
	float64 fl_Get_CAN_status[TRIP_MAX] = {0};

	/*Store the Speed of the vehicle*/
	uint32_t fl_AFE_input_Speed_u32 = 0;
	
	/*To Store the index*/
	uint8_t trip_id;

	uint8_t sample_index;

	uint32_t fl_AFE_Cal_u32[TRIP_MAX] = {0};

	/*To store the displayed IFE Unit*/
	uint8_t fl_Displayed_AFE_unit_u8 = 0;

	uint8_t fl_CAN_Bus_off_Status_u8 = 0;

	static uint32_t fl_get_del_Tripodo_km_u32[TRIP_MAX] = {0};

	/*Store the precondition value*/
	g_AFE_Precondition_Status_u8 = AFE_Pre_Condition();

	if(g_AFE_Precondition_Status_u8 == TRUE)
	{
		/*Store the CAN message value*/
		(void) CanMgr_Read_accumulat_fuel_inj_time_fuel_qty_0x135_s(&fl_Read_Acc_Fuel_Inj_Value_f64);
		
		/*This loop for iteration the Trip Id*/
		for (trip_id = 0; trip_id < TRIP_MAX; trip_id++)
		{
			/*To store the Trip km value*/
			g_Trip_Km_u32[trip_id] = GET_ODO_VALUE();

			fl_CAN_Bus_off_Status_u8 = App_Can_bus_off_Get_indication();

			/*Check the CAN Bus off Status*/
			if((g_CAN_ECM_Status_u8 != TRUE) && (TC_CAN_BUS_OFF_STATUS == fl_CAN_Bus_off_Status_u8)&& (Swc_Get_CAN_BUS_OFF_Recovery_Counter() >= 20))
			{
				/*Check the current and Previous Odo value*/
				if(g_Trip_Dist_N_u32[trip_id] > g_Trip_Km_u32[trip_id])
				{
					/*Hold the ODO value*/
					g_Trip_delta_u32[trip_id] = (g_Trip_Km_u32[trip_id] + 10000) - g_Trip_Dist_N_u32[trip_id];
				}
				else
				{
					/*Hold the ODO value*/
					g_Trip_delta_u32[trip_id] = g_Trip_Km_u32[trip_id] - g_Trip_Dist_N_u32[trip_id];
				}

				g_AFE_Dist_ACCU_u64[trip_id] = g_AFE_Dist_ACCU_u64[trip_id] + g_Trip_delta_u32[trip_id];
		
				/*Store the current odo value*/
				g_Trip_Dist_N_u32[trip_id] = g_Trip_Km_u32[trip_id];
		
				/*To store the CAN Value*/
				g_Get_AFE_CAN_value =(float)((fl_Read_Acc_Fuel_Inj_Value_f64 * 10000000)/ 5.97);

				/*Check the distance value*/
				if(g_AFE_Dist_ACCU_u64[trip_id] > AFE_ACCU_MAX)
				{
					/*To store AFE Distance accumulation*/
					g_AFE_Dist_ACCU_u64[trip_id] = (float)(g_AFE_Dist_ACCU_u64[trip_id] / AFE_ACCU_ROLLBACK);
					
					/*To store AFE Fuel cons accumulation*/
					g_AFE_Fuel_Cons_ACCU_u32[trip_id] = (float)(g_AFE_Fuel_Cons_ACCU_u32[trip_id] / AFE_ACCU_ROLLBACK);
				}

				/*This variable is to store the Speed fault status*/
				fl_AFE_Speedfault_status_bool = SPEED_FAULT_STATUS();

				/*This variable is to store the input Speed of the vehicle*/
				fl_AFE_input_Speed_u32 = INPUT_SPEED_VALUE();

				/*Check the speed value*/
				if((fl_AFE_input_Speed_u32 > AFE_MIN_SPEED) && (fl_AFE_input_Speed_u32 <= AFE_MAX_SPEED) || 
					((fl_AFE_Speedfault_status_bool == TRUE) || (g_AFE_NVM_FUEL_ACC_CALC_IDLE == TRUE)))
				{
					fl_Get_CAN_status[trip_id] = g_Get_AFE_CAN_value;
				
					/*To store AFE Fuel cons accumulation*/
					g_AFE_Fuel_Cons_ACCU_u32[trip_id] = g_AFE_Fuel_Cons_ACCU_u32[trip_id] + fl_Get_CAN_status[trip_id];
				}
				else
				{
					/*Do Nothing*/
				}

				g_CAN_BUS_OFF_Det_Status = FALSE;
			}
			else
			{
				if((CAN_BUSOFF_INDICATION() != FALSE) && (g_CAN_BUS_OFF_Det_Status == FALSE))
				{
					Swc_Clear_CAN_BUS_RECOVERY_Flag();

					g_CAN_BUS_OFF_Det_Status = TRUE;
				}

			}

			/*Check AFE Fuel cons value*/
			if(g_AFE_Fuel_Cons_ACCU_u32[trip_id] != 0)
			{
				g_AFE_Display_value_u32[trip_id] = ((g_AFE_Dist_ACCU_u64[trip_id] * AFE_RESOULTION_FACTOR) / g_AFE_Fuel_Cons_ACCU_u32[trip_id]);

			}
			
			if(g_TC_IGN_ON_Status == TRUE)
		    {
				g_TC_IGN_ON_Status = FALSE;

				TC_AFE_Compute(fl_Displayed_AFE_unit_u8, 0);
				TC_AFE_Compute(fl_Displayed_AFE_unit_u8, 1);

				g_AFE_Display_Update_time_u8 = AFE_DISPLAY_UPDATE_TIME;
		    }

			/*To get the unit selection from user*/
			g_current_fuel_cons_unit_set_u8 = GET_UNIT_SELCETION;

			/*To hold the current unit selection*/
			fl_Displayed_AFE_unit_u8 = GET_UNIT_SELCETION;
			
			/*Check the Trip Km*/
			if(g_AFE_Dist_ACCU_u64[trip_id] > AFE_INIT_DIST)
			{
				/*Check the AFE Display time*/
				if(g_AFE_Display_Update_time_u8 == 0)
				{
					/*To store the AFE Display time*/
					g_AFE_Display_Update_time_u8 = AFE_DISPLAY_UPDATE_TIME;

					/*Calculate the AFE by unit*/
					TC_AFE_Compute(fl_Displayed_AFE_unit_u8,trip_id);
				}
				else
				{
					/*Decrement timer*/
					g_AFE_Display_Update_time_u8--;

					/*Check the display unit*/
					if(g_current_fuel_cons_unit_set_u8 != fl_Displayed_AFE_unit_u8)
					{
						/*Calculate the AFE by unit*/
						TC_AFE_Compute(fl_Displayed_AFE_unit_u8, trip_id);
					}
					else
					{
						/*Do nothing*/
					}
				}
			}
			else
			{
				/*To store the AFE Display value as Zero*/
				g_AFE_Display_value_u32[trip_id] = 0;

				/*To store the AFE Display value as Zero*/
				g_Displayed_AFE_u32[trip_id] = 0;
			}
		}
	}
	else
	{
		/* Precondition fails , has to display invalid*/
		g_Displayed_AFE_u32[0] = TC_INVALID;
		g_Displayed_AFE_u32[1] = TC_INVALID;
	}
}

bool Swc_TC_Get_CAN_Bus_OFF_Status(void)
{
	return (g_CAN_BUS_OFF_Det_Status);
}

void Swc_AFE_Writesync(void) 
{
	bool fl_NVM_Status_bl = TRUE;

	/* Get NVM Status */
	fl_NVM_Status_bl = Swc_Get_NVM_Status();

	if(fl_NVM_Status_bl == FALSE)
	{
		NVM_Byte_Write_Allocation(NVM_TRIP_A_AFE_DISTANCE_ACCUMULATION,(uint8_t*)&g_AFE_Dist_ACCU_u64[0]);

		NVM_Byte_Write_Allocation(NVM_TRIP_B_AFE_DISTANCE_ACCUMULATION,(uint8_t*)&g_AFE_Dist_ACCU_u64[1]);

		NVM_Byte_Write_Allocation(NVM_TRIP_A_AFE_FUEL_CONS_ACC,(uint8_t*)&g_AFE_Fuel_Cons_ACCU_u32[0]);
		
		NVM_Byte_Write_Allocation(NVM_TRIP_B_AFE_FUEL_CONS_ACC,(uint8_t*)&g_AFE_Fuel_Cons_ACCU_u32[1]);

		NVM_Byte_Write_Allocation(NVM_AFE_FUEL_ACC_CALC_IDLE,(uint8_t*)&g_AFE_NVM_FUEL_ACC_CALC_IDLE);



	}	
}

void Swc_AFE_Readsync(void)
{
	
	NVM_Byte_Read_Allocation(NVM_TRIP_A_AFE_DISTANCE_ACCUMULATION,(uint8_t*)&g_AFE_Dist_ACCU_u64[0]);

	NVM_Byte_Read_Allocation(NVM_TRIP_B_AFE_DISTANCE_ACCUMULATION, (uint8_t*)&g_AFE_Dist_ACCU_u64[1]);


	NVM_Byte_Read_Allocation(NVM_TRIP_A_AFE_FUEL_CONS_ACC,(uint8_t*)&g_AFE_Fuel_Cons_ACCU_u32[0]);


	NVM_Byte_Read_Allocation(NVM_TRIP_B_AFE_FUEL_CONS_ACC, (uint8_t*)&g_AFE_Fuel_Cons_ACCU_u32[1]);

	NVM_Byte_Read_Allocation(NVM_AFE_FUEL_ACC_CALC_IDLE,(uint8_t*)&g_AFE_NVM_FUEL_ACC_CALC_IDLE);
	


}


void Swc_DTE_Readsync(void)
{
	uint32_t fl_DTE_NVM_Read_Data[4] ;

	NVM_Byte_Read_Allocation(NVM_DTE_DATA, (uint8_t*)&fl_DTE_NVM_Read_Data[0]);

	g_RAFE_Dist_Accu_u64 = ((uint64_t)fl_DTE_NVM_Read_Data[0] << 32) | ((uint64_t)fl_DTE_NVM_Read_Data[1]);

	g_RAFE_Fuel_Cons_ACCU_u32 = fl_DTE_NVM_Read_Data[2];

	g_Fuel_Remaining_u32 = fl_DTE_NVM_Read_Data[3];

}


void Swc_DTE_Writesync(void)
{
	uint32_t fl_DTE_NVM_Write_Data[4] ;
	bool fl_NVM_Status_bl = TRUE;

   /* Get NVM Status */
   fl_NVM_Status_bl = Swc_Get_NVM_Status();

   if(fl_NVM_Status_bl == FALSE)
   {

	fl_DTE_NVM_Write_Data[0] = g_RAFE_Dist_Accu_u64 >> 32;
	fl_DTE_NVM_Write_Data[1] = g_RAFE_Dist_Accu_u64 ;
	fl_DTE_NVM_Write_Data[2] = g_RAFE_Fuel_Cons_ACCU_u32 ;
	fl_DTE_NVM_Write_Data[3] = g_Fuel_Remaining_u32 ;

	NVM_Byte_Write_Allocation(NVM_DTE_DATA,(uint8_t*)&fl_DTE_NVM_Write_Data[0]);
   }	

}

/*
* @brief    This function is used to compute the AFE
* @param    None 
* @return   None
*/
static void TC_AFE_Compute(uint8_t unit_selection_u8, uint8_t trip_id)
{
	/*To store the displayed AFE Unit*/
	uint8_t Displayed_AFE_unit_u8;
	
	/*To store the trip id*/
	uint8_t fl_trip_id;

	/*To store the unit selection*/
	Displayed_AFE_unit_u8 = TC_UNIT_SELECTION_KML;

	/*To store the trip id*/
	fl_trip_id = trip_id;

	uint32_t fl_AFE_Cal_Value_u32[TRIP_MAX] = {0};

	fl_AFE_Cal_Value_u32[fl_trip_id] = g_AFE_Display_value_u32[fl_trip_id];

	/*CHeck the unit selection*/
	if(Displayed_AFE_unit_u8 == TC_UNIT_SELECTION_US_MPG)
	{
		/*This variable is to display the AFE Value*/
		g_Displayed_AFE_u32[fl_trip_id] = fl_AFE_Cal_Value_u32[fl_trip_id] * (UK_MPG_CONV_FACTOR);
	}
	/*CHeck the unit selection*/
	else if(Displayed_AFE_unit_u8 == TC_UNIT_SELECTION_UK_MPG)
	{
		/*This variable is to display the AFE Value*/
		g_Displayed_AFE_u32[fl_trip_id] = fl_AFE_Cal_Value_u32[fl_trip_id] * (US_MPG_CONV_FACTOR);
	}
	/*Check the unit selection*/
	else if(Displayed_AFE_unit_u8 == TC_UNIT_SELECTION_KML)
	{
		/*This variable is to display the AFE Value*/
		g_Displayed_AFE_u32[fl_trip_id] = fl_AFE_Cal_Value_u32[fl_trip_id];
	}
	/*Check the unit selection*/
	else if(Displayed_AFE_unit_u8 == TC_UNIT_SELECTION_L_KM)
	{
		/*This variable is to display the AFE Value*/
		g_Displayed_AFE_u32[fl_trip_id] = fl_AFE_Cal_Value_u32[fl_trip_id];
	}
	else
	{
		/*Do Nothing*/
	}
	
	/*Check the display AFE*/
	if(g_Displayed_AFE_u32[fl_trip_id] > AFE_MAX)
	{
		/*To store the AFE Max*/
		g_Displayed_AFE_u32[fl_trip_id] = AFE_MAX;
	}
	else
	{
		/*Do Nothing*/
	}
}

/*
* @brief    This function is used to dispaly the AFE Value
* @param    None 
* @return   None
*/
uint32_t display_AFE(uint8_t trip_id)
{
	/*TO store the trip_id value*/
	uint8_t fl_trip_id = trip_id;
	uint32_t fl_Ret_Val_u32 = 0;

	if( g_Displayed_AFE_u32[fl_trip_id] == TC_INVALID)
	{
		fl_Ret_Val_u32 = TC_INVALID;
	}
	else
	{
		/* change resoultion into 0.1 from 0.01*/
		fl_Ret_Val_u32 = (g_Displayed_AFE_u32[fl_trip_id] / 10);
	}

	/*return the AFE value*/
	return (fl_Ret_Val_u32);
}

/*
* @brief    This function is Active function or main function of the AFE
* @param    None 
* @return   None
*/
void DTE_Active(void)
{
	/*Store the precondition value*/
	g_DTE_Precondition_Status_u8 = DTE_Pre_Condition();

	/*Check the DTE Pre condition is true or false*/
	if(g_DTE_Precondition_Status_u8 == TRUE)
	{
		/*Call the RAFE Distance Calculation function*/
		DTE_RAFE_Dist_Fuel_Calculation();

		/*Call the Calculation DTE Processing function*/
		Cal_DTE_Processing();

		/*Call the DTE Dispaly calculation function*/
		DTE_DisplayCalculation();

	}
	else
	{
		g_Disp_DTE_u32 = TC_INVALID;

		g_Value_DTE = TC_INVALID;
	}
}

/*
* @brief    This function is used for RAFE distance and fuel Calculation
* @param    None 
* @return   None
*/
void DTE_RAFE_Dist_Fuel_Calculation(void)
{
	/*To store the Acc Fuel Value*/
	static float64 fl_Read_Acc_Fuel_Inj_Value_f64 = 0;

	static float fl_Get_DTE_CAN_value = 0;

	static uint32_t fl_get_odo_km_u32 = 0;

	static uint32_t fl_get_del_odo_km_u32 = 0;

	static uint64_t fl_dist_Accu_Cal_u64 = 0;

	static uint64_t fl_Cal_Current_Dist_u64 = 0;

	/*To store the ODO data reset*/
	g_Odo_data_reset = GET_ODO_DATA_RESET();

	/*To store the ODO data write*/
	g_Odo_data_write = GET_ODO_DATA_WRITE();	

	/*This varibale is to store the odod value*/
	g_Get_Odo_km_value_u32 = GET_ODO_VALUE_KM();

	/*Store the CAN message value*/
	(void)CanMgr_Read_accumulat_fuel_inj_time_fuel_qty_0x135_s(&fl_Read_Acc_Fuel_Inj_Value_f64);

	/*To increment the CAN Process time*/
	g_DTE_CAN_Process_Time_u8 = g_DTE_CAN_Process_Time_u8 + 1;

	/*To store the CAN Value*/
	fl_Get_DTE_CAN_value = (float)fl_Read_Acc_Fuel_Inj_Value_f64;

	/*To store the CAN Value*/
	g_Get_DTE_CAN_value = ((fl_Get_DTE_CAN_value * 10000000)/ 5.97);

	/*Check the Odo data reset and Odo data write value*/
	if((g_Odo_data_reset == TRUE) || (g_Odo_data_write == TRUE))
	{
		/*To store the RAFE Distance accumulator value*/
		g_RAFE_Dist_Accu_u64 = 0;

		/*To store the Rollover value*/
		g_RAFE_Rollover_Done_u8 = 0;

		/*To store DTE Fuel Accumulation value*/
		g_RAFE_Fuel_Cons_ACCU_u32 = 0;

		/*To store DTE Fuel Accumulation value*/
		g_Prev_Odo_Km_val_u32 = 0;

		/*To store the Odo data reset value*/
		g_Odo_data_reset = FALSE;

		/*To store the Odo write reset value*/
		g_Odo_data_write = FALSE;
	}
	else
	{
		if(g_Prev_Odo_Km_val_u32 > g_Get_Odo_km_value_u32)
		{
			/*Hold the ODO value*/
			fl_get_del_odo_km_u32 = (g_Get_Odo_km_value_u32 + 10000) - g_Prev_Odo_Km_val_u32;
		}
		else
		{
			/*Hold the ODO value*/
			fl_get_del_odo_km_u32 = g_Get_Odo_km_value_u32 - g_Prev_Odo_Km_val_u32;
		}

		g_Prev_Odo_Km_val_u32 = g_Get_Odo_km_value_u32;
		
		/*To store the RAFE Distance accumulator value*/
		g_RAFE_Dist_Accu_u64 = g_RAFE_Dist_Accu_u64 + fl_get_del_odo_km_u32;

		/*Check the RAFE Distance Accumulation value*/
		if(g_RAFE_Dist_Accu_u64 > RAFE_ACCU_MAX)
		{
			/*To store the RAFE Distance Accumulation value*/
			g_RAFE_Dist_Accu_u64 = g_RAFE_Dist_Accu_u64 / RAFE_ACCU_ROLLBACK;

			/*To store the RAFE Fuel Accumulation value*/
			g_RAFE_Fuel_Cons_ACCU_u32 = g_RAFE_Fuel_Cons_ACCU_u32 / RAFE_ACCU_ROLLBACK;
		}
		else
		{	
			/*To increment the Process time*/
			g_Fuel_Consum_process_time_u8 = g_Fuel_Consum_process_time_u8 + 1;

			/*For 200ms once, fuel accumulation shall be done*/
			if(g_Fuel_Consum_process_time_u8 == 2)
			{
				/*To call the Fuel consumption processing function*/
				RAFE_Fuel_Consumption_Acc_Processing();

				g_Current_RAFE_u32 = (g_RAFE_Dist_Accu_u64 * AFE_RESOULTION_FACTOR) / g_RAFE_Fuel_Cons_ACCU_u32;
				
				g_Current_RAFE_u32 = g_Current_RAFE_u32 / 10; 

				fl_dist_Accu_Cal_u64 = DTE_RAFE_DIST_MAX - g_RAFE_Dist_Accu_u64;

				fl_Cal_Current_Dist_u64 = g_Current_RAFE_u32 * g_RAFE_Dist_Accu_u64;

				/*Check RAFE Rollover is true or false*/
				if(g_RAFE_Rollover_Done_u8 == TRUE)
				{
					/*To store the RAFE value*/
					g_RAFE_u32 = g_Current_RAFE_u32;
				}
				else
				{
					/*To store the RAFE value*/
					g_RAFE_u32 = ((DEFAULT_RAFE * fl_dist_Accu_Cal_u64) + fl_Cal_Current_Dist_u64) / DTE_RAFE_DIST_MAX;
				}

				/*To store process time*/
				g_Fuel_Consum_process_time_u8 = 0;
			}
			else
			{
				/* do nothing*/
			}
		}

		/*Check the RAFE Distance accumulator value*/
		if(g_RAFE_Dist_Accu_u64 > DTE_RAFE_DIST_MAX)
		{

			/*To store the Rollover value*/
			g_RAFE_Rollover_Done_u8 = TRUE;

		}
		else
		{
			/*To store the Rollover value*/
			g_RAFE_Rollover_Done_u8 = FALSE;
		}
		
		/*Check the RAFE value*/
		if(g_RAFE_u32 <= MIN_RAFE)
		{
			/*TO store the RAFE Value as MIN_RAFE*/
			g_RAFE_u32 = MIN_RAFE;
		}
	}
}

/*
* @brief    This function is used for Calculation RAFE_Fuel_Consumption_Acc_Processing
* @param    None 
* @return   None
*/
void RAFE_Fuel_Consumption_Acc_Processing(void)
{
	/*To store the input speed value*/
	uint8_t fl_input_Speed_u8 = 0;

	uint32_t fl_get_fuel_u32 = 0;

	uint32_t fl_del_fuel_u32 = 0;

	/*This variable is to store the input Speed of the vehicle*/
	fl_input_Speed_u8 = INPUT_SPEED_VALUE();

	if((g_Odo_data_reset == TRUE) || (g_Odo_data_write == TRUE))
	{
		/*To store DTE Fuel Accumulation value*/
		g_RAFE_Fuel_Cons_ACCU_u32 = 0;
	}
		
	/*Check the input speed of vehicle betwwen the limit*/
	if((fl_input_Speed_u8 > RAFE_MIN_SPEED) && (fl_input_Speed_u8 <= RAFE_MAX_SPEED))
	{
		fl_get_fuel_u32 = g_Get_DTE_CAN_value / 5;

		fl_del_fuel_u32 = g_RAFE_Fuel_Cons_ACCU_u32;
		
		/*To store DTE Fuel Accumulation value*/
		g_RAFE_Fuel_Cons_ACCU_u32 = fl_get_fuel_u32 + fl_del_fuel_u32;
	}

}

/*
* @brief    This function is used for Calculation DTE Processing  
* @param    None 
* @return   None
*/
void Cal_DTE_Processing(void)
{
	/*To store the fuel Bar status value*/
	uint8_t fl_fuel_Bar_status_u8 = 0;
	
	/*To store the Fuel init status*/
	uint8_t fl_fuel_init_u8 = 0;

	/*To store the fuel capacity value*/
	uint32_t fl_get_fuel_capacity_u32 = 0;

	/*To store the input speed value*/
	uint8_t fl_input_Speed_u8 = 0;

	uint32_t fl_Get_fuel_u32 = 0;

	uint32_t fl_used_fuel_u32 = 0;

	/*To store the Fuel init status*/
	fl_fuel_init_u8 = GET_FUEL_INIT_STATUS();

	/*To store the fuel status value*/
	fl_fuel_Bar_status_u8 = GET_FUELBAR_VALUE();

	/*This variable is to store the input Speed of the vehicle*/
	fl_input_Speed_u8 = INPUT_SPEED_VALUE();

	/*Check the DTE Init Status*/
	if(fl_fuel_init_u8 == TRUE)
	{
		/*To check the processing*/
		if(g_Cal_DTE_Processing_Time == 2)
		{
			/*To store the fuel bar value*/
			g_FuelBar_u8 = fl_fuel_Bar_status_u8;

			/*Check the current and previous fuel bar value*/
			if((g_FuelBar_u8 != g_Prev_FuelBar_u8) || (g_Fuel_Init_Status == 1))
			{
				/*To store the Fuel store value as Zero*/
				g_FuelUsed_u32 = 0;

				/*To get fuel capacity value*/
				fl_get_fuel_capacity_u32 = Fuel_Guage_Table(fl_fuel_Bar_status_u8);

				/*To store the fuel capacity value*/
				g_fuel_capacity_Litre_Val_u32 = fl_get_fuel_capacity_u32 * FUEL_CAPACITY_UL_CONVERSTION_FACTOR;

				g_Fuel_Init_Status = 0;
			}
			else
			{
				/*To store the CAN fuel value*/
				fl_Get_fuel_u32 = (g_Get_DTE_CAN_value * 597) / 1000;

				/*To store the Fuel used value*/
				g_FuelUsed_u32 = fl_Get_fuel_u32 + g_FuelUsed_u32;

				if(g_FuelUsed_u32 < g_fuel_capacity_Litre_Val_u32)
				{
					/*To store the Fuel Remaining value*/
					g_Fuel_Remaining_u32 = g_fuel_capacity_Litre_Val_u32 - g_FuelUsed_u32;
				}
			}

			/*To store the calculated RAFE and Rem Fuel value*/
			g_CAL_RAFE_FUEL_REM_u64 = (((uint64_t)(g_Fuel_Remaining_u32 - DEAD_VOL) * g_RAFE_u32) / 10000000);

			/*To store the DTE Calculated value*/
			g_Calc_DTE_u32 = g_CAL_RAFE_FUEL_REM_u64;

			/*To store the Previous Fuelbar value*/	
			g_Prev_FuelBar_u8 = g_FuelBar_u8;

			/*To initize the value as zero*/
			g_Cal_DTE_Processing_Time = 0;
		}
		else
		{
			/*To increment store the DTE calculation processing time*/
			g_Cal_DTE_Processing_Time = g_Cal_DTE_Processing_Time + 1;
		}
	}
	else
	{
		/*To initize the value as zero*/
		g_Cal_DTE_Processing_Time = 0;
	}
}

uint8_t DTE_Init(void)
{
	/*To store the Fuel Guage Get Fault Status*/
	uint8_t fl_fuel_Current_Status = Swc_Fuel_Gauge_Get_Fault_Status();

	/*Check the DTE Init Status and To Check the Fuel Guage Get Fault Status and To Check the Odo data reset and Odo data write value*/
	if((fl_fuel_Current_Status == FUEL03_STATUS_NO_OPEN_SHORT) && (g_fuel_Previous_Status != FUEL03_STATUS_NO_OPEN_SHORT))
	{
		/*To store the DTE Init value*/
		g_DTE_Init_u8 = TRUE;
	}
	
	g_fuel_Previous_Status = fl_fuel_Current_Status;
	
	/*Return the DTE Init value*/
	return g_DTE_Init_u8;
}

/*
* @brief    This function is used for DTE Displayed calculation
* @param    None
* @return   None
*/
void DTE_DisplayCalculation(void)
{
	/*To store the DTE Status*/
	uint8_t fl_DTE_Status_u8;

	/*To store the calculate DTE Value*/
	uint32_t fl_get_Cal_DTE_Val = 0;

	/*To store the delta DTE value*/
	int16_t fl_Delta_DTE = 0;

	/*To store the DTE dist comp value*/
	uint16_t fl_DistComp_u16 = 0;
	
	/*To store the DTE dist comp * delta accu value*/
	static uint32_t fl_DTE_DistComp_u32 = 0;

	/*To store the DTE display value*/
	static uint32_t fl_Displayed_Val = 0;

	/*To store the DTE uint*/
	uint8_t fl_Displayed_unit_u8;

	/*To get the unit selection from user*/
	g_current_fuel_cons_unit_set_u8 = GET_UNIT_SELCETION;

	/*To hold the current fuel unit*/
	fl_Displayed_unit_u8 = g_current_fuel_cons_unit_set_u8;
	
	/*To hold the Calculated DTE value*/
	fl_get_Cal_DTE_Val = g_Calc_DTE_u32;

	/*To get the DTE Status*/
	fl_DTE_Status_u8 = DTE_Init();

	g_DTE_Cur_odo_u16 = GET_ODO_VALUE();

	if(g_DTE_prv_odo_u16 > g_DTE_Cur_odo_u16)
	{
		/*Hold the ODO value*/
		g_DTE_Delta_u16 = (g_DTE_Cur_odo_u16 + 10000) - g_DTE_prv_odo_u16;
	}
	else
	{
		/*Hold the ODO value*/
		g_DTE_Delta_u16 = g_DTE_Cur_odo_u16 - g_DTE_prv_odo_u16;
	}
			
	/*Store the current odo value*/
	g_DTE_prv_odo_u16 = g_DTE_Cur_odo_u16;

	g_DTE_delta_Dist_Accu_u32 = g_DTE_delta_Dist_Accu_u32 + g_DTE_Delta_u16;

	/*Check the DTE Status*/
	if(fl_DTE_Status_u8 == TRUE)
	{
		/*To store the DTE Init value*/
		g_DTE_Init_u8 = FALSE;

		/*To store the Displayed DTE value*/
		g_Disp_DTE_u32 = fl_get_Cal_DTE_Val;

		g_DTE_delta_Dist_Accu_u32 = 0;

		TC_DTE_Compute(fl_Displayed_unit_u8,g_Disp_DTE_u32);
	}
	
	/*To display the update time*/
	else if(g_DTE_Display_Update_time_u8 == 0)
	{
		/*To store the AFE Display time*/
		g_DTE_Display_Update_time_u8 = DTE_DISPLAY_UPDATE_TIME;

		if(g_Disp_DTE_u32 > fl_get_Cal_DTE_Val)
		{
			/*To store the Delta DTE value*/
			fl_Delta_DTE = g_Disp_DTE_u32 - fl_get_Cal_DTE_Val;
		}
		else
		{
			/*To store the Delta DTE value*/
			fl_Delta_DTE = fl_get_Cal_DTE_Val - g_Disp_DTE_u32;
		}
		
		/*Check the Delta DTE*/
		if(abs(fl_Delta_DTE) > MAX_DTE_DIFF)
		{
			g_Disp_DTE_u32 = fl_get_Cal_DTE_Val;

			fl_Displayed_Val = g_Disp_DTE_u32;

			g_DTE_delta_Dist_Accu_u32 = 0;

			TC_DTE_Compute(fl_Displayed_unit_u8,fl_Displayed_Val);
		}
		else
		{

			fl_DistComp_u16 = DeltaDTE_DistanceComp(fl_Delta_DTE);

			fl_DTE_DistComp_u32 = (uint32_t)fl_DistComp_u16 * 1000;

			if(g_DTE_Inc_allowed_u8 == TRUE)
			{
				if(fl_get_Cal_DTE_Val > g_Disp_DTE_u32)
				{
					if(g_DTE_delta_Dist_Accu_u32 > fl_DTE_DistComp_u32)
					{
						if(g_Disp_DTE_u32 >= DTE_MAX)
						{
							fl_Displayed_Val = g_Disp_DTE_u32;

							TC_DTE_Compute(fl_Displayed_unit_u8,fl_Displayed_Val);
						}
						else
						{
							g_Disp_DTE_u32 = g_Disp_DTE_u32 + 1;

							g_DTE_delta_Dist_Accu_u32 = g_DTE_delta_Dist_Accu_u32 % fl_DTE_DistComp_u32;

							fl_Displayed_Val = g_Disp_DTE_u32;

							TC_DTE_Compute(fl_Displayed_unit_u8,fl_Displayed_Val);
						}
					}
				}
				else if(fl_get_Cal_DTE_Val < g_Disp_DTE_u32)
				{
					if(g_DTE_delta_Dist_Accu_u32 > fl_DTE_DistComp_u32)
					{
						if(g_Disp_DTE_u32 <= DTE_MIN)
						{
							fl_Displayed_Val = g_Disp_DTE_u32;

							TC_DTE_Compute(fl_Displayed_unit_u8,fl_Displayed_Val);
						}
						else
						{
							g_Disp_DTE_u32 = g_Disp_DTE_u32 - 1;

							g_DTE_delta_Dist_Accu_u32 = g_DTE_delta_Dist_Accu_u32 % fl_DTE_DistComp_u32;

							fl_Displayed_Val = g_Disp_DTE_u32;

							TC_DTE_Compute(fl_Displayed_unit_u8,fl_Displayed_Val);
						}
					}
				}
				else
				{
					/*Do Nothing*/
				}
			}
			else if(g_DTE_delta_Dist_Accu_u32 > fl_DTE_DistComp_u32)
			{
				if(g_Disp_DTE_u32 <= DTE_MIN)
				{
					fl_Displayed_Val = g_Disp_DTE_u32;

					TC_DTE_Compute(fl_Displayed_unit_u8,fl_Displayed_Val);
				}
				else
				{
					g_Disp_DTE_u32 = g_Disp_DTE_u32 - 1;
				
					g_DTE_delta_Dist_Accu_u32 = g_DTE_delta_Dist_Accu_u32 % fl_DTE_DistComp_u32;

					fl_Displayed_Val = g_Disp_DTE_u32;
							
					TC_DTE_Compute(fl_Displayed_unit_u8,fl_Displayed_Val);
				}
			}
			else
			{
				fl_Displayed_Val = g_Disp_DTE_u32;
							
				TC_DTE_Compute(fl_Displayed_unit_u8,fl_Displayed_Val);
			}
		}
	}
	else
	{
		g_DTE_Display_Update_time_u8--;

		TC_DTE_Compute(fl_Displayed_unit_u8,fl_Displayed_Val);
	}
}

uint16_t DeltaDTE_DistanceComp(int16_t delta_dist_s16)
{
	uint16_t fl_DistComp_Index_u16 = 0;
  	
	int16_t fl_input_s16 = 0;

  	fl_input_s16 = delta_dist_s16;

  	if(g_DTE_Inc_allowed_u8 == FALSE)
  	{
    	if((-MAX_DTE_DIFF < fl_input_s16)  && (fl_input_s16 <= -20))
    	{
      		fl_DistComp_Index_u16 = 500;
    	}
    	else if((-20 < fl_input_s16) && (fl_input_s16 <= -10))
    	{
      		fl_DistComp_Index_u16 = 300;
    	}
    	else if((-10 < fl_input_s16) && (fl_input_s16 <= 10))
    	{
      		fl_DistComp_Index_u16 = 100;
    	}
    	else if((10 < fl_input_s16) && (fl_input_s16 <= 20))
    	{
      		fl_DistComp_Index_u16 = 100/3;
    	}
    	else if((20 < fl_input_s16) && (fl_input_s16 <= MAX_DTE_DIFF))
    	{
      		fl_DistComp_Index_u16 = 100/5;
    	}
		else
		{
			/*Do Nothing*/
		}
  	}
  	else
  	{
    	if((0 < fl_input_s16) && (fl_input_s16 <= 10))
    	{
      		fl_DistComp_Index_u16 = 100;
    	}
    	else if((0 < fl_input_s16) && (fl_input_s16 <= 20))
    	{
      		fl_DistComp_Index_u16 = 100/3;
    	}
    	else if((20 < fl_input_s16) && (fl_input_s16 <= MAX_DTE_DIFF))
    	{
      		fl_DistComp_Index_u16 = 100/5;
    	}
		else
		{
			/*Do Nothing*/
		}
  	}
  return fl_DistComp_Index_u16;
}

/*
* @brief    This function is used to compute the IFE
* @param    None 
* @return   None
*/
static void TC_DTE_Compute(uint8_t unit_selection_u8,uint32_t Cal_DTE_value)
{
	/*To store the displayed IFE Unit*/
	uint8_t Displayed_DTE_unit;

	uint32_t fl_Displayed_DTE = Cal_DTE_value;

	/*To store the unit selection*/
	Displayed_DTE_unit = TC_UNIT_SELECTION_KML;

	/*CHeck the unit selection*/
	if(Displayed_DTE_unit == TC_UNIT_SELECTION_US_MPG)
	{
		/*This variable is to display the DTE Value*/
		fl_Displayed_DTE = (fl_Displayed_DTE) * (UK_MPG_CONV_FACTOR);
	}

	/*Check the unit selection*/
	else if(Displayed_DTE_unit == TC_UNIT_SELECTION_KML)
	{
		/*This variable is to display the DTE Value*/
		fl_Displayed_DTE = fl_Displayed_DTE;
	}
	else if(Displayed_DTE_unit == TC_UNIT_SELECTION_L_KM)
	{
		fl_Displayed_DTE = fl_Displayed_DTE;
	}
	else
	{
		/*Do Nothing*/
	}

	g_Value_DTE = fl_Displayed_DTE;
}

/*
* @brief    This function is used to display the DTE Value
* @param    void
* @return   uint32_t
*/
uint32_t display_DTE(void)
{
	uint32_t fl_display_DTE = 0;

	if(g_Value_DTE != TC_INVALID)
	{
		if(g_Value_DTE < DTE_MIN)
		{
			fl_display_DTE = DTE_MIN;	
		}
		else if(g_Value_DTE < DTE_MAX)
		{
			fl_display_DTE = g_Value_DTE; 
		}
		else
		{
			fl_display_DTE = DTE_MAX;
		}
	}
	else
	{
		fl_display_DTE = TC_INVALID;
	}
	
	/*return the DTE value*/
	return fl_display_DTE;

}

/*
* @brief    This function is used to activate the trip computer
* @param    None
* @return   None
*/
void TC_Activate(void)
{
	/*Activate the Trip computer Active Flag*/
	g_TC_ActiveFlag_u8 = (uint8_t)TC_ACTIVATE;
}

/*
* @brief    This function is used to deactivate the trip computer
* @param    None
* @return   None
*/
void TC_Deactivate(void)
{
	/*Deactivate the Trip computer Active Flag*/
	g_TC_ActiveFlag_u8 = (uint8_t)TC_DEACTIVATE;
}

/*
* @brief    This function is used to Deinit the Trip computer
* @param    None 
* @return   None
*/

void TC_Deinit(void)
{
	/*To Init the IFE precondition value*/
	g_IFE_Precondition_Status_u8 = FALSE;

	/*To Init the IFE Calculation value*/
	g_IFE_CAL_f32[IFE_MAX_INDEX_CNT] = 0;
	
	/*To init the Previous odo value*/
	g_prv_odo_u32 = 0;

	/*To init the Current odo value*/
	g_Cur_odo_u32 = 0;

	/*To Init the IFE ODO value*/
	g_IFE_ODO_u32 = 0;

	/*To Init the index of IFE */
	g_IFE_index_u8 = 0;

	/*To Init the IFE value*/
	g_IFE_u32 = 0;

	/*To Init the CAN message value of IFE*/
	g_Get_IFE_CAN_value_fl = 0;

	/*Hold the display time*/
	g_IFE_Display_Update_time_u8 = 0;

	/*To Init the IFE Display value*/
	g_Display_IFE_Value = 0;

	/*To Init the IFE Display value*/
	Displayed_IFE_value_u32 = 0;

	/*To Init the AFE precondition value*/
	g_AFE_Precondition_Status_u8 = FALSE;

	/*To Init store the Trip km value*/
	g_Trip_Km_u32[TRIP_MAX] = 0;

	/*To Init store the Trip km value*/
	g_Trip_Dist_N_u32[TRIP_MAX] = 0;

	/*To Init the CAN message value of AFE*/
	g_Get_AFE_CAN_value = 0;

	/*To init the AFE Distance Accumulation value*/
	g_AFE_Dist_ACCU_u64[TRIP_MAX] = 0;

	/*To init AFE Fuel Accumulation value*/
	g_AFE_Fuel_Cons_ACCU_u32[TRIP_MAX] = 0;

	/*Hold the display time*/
	g_AFE_Display_Update_time_u8 = AFE_DISPLAY_UPDATE_TIME;
	
	/*To Init the AFE precondition value*/
	g_DTE_Precondition_Status_u8 = FALSE;

	/*To store the Rollover Init value*/
	g_RAFE_Rollover_Done_u8 = FALSE;	
	
	/*Hold the display time of DTE*/
	g_DTE_Display_Update_time_u8 = 0;

	/*To Init the DTE Odo value*/
	g_Delta_Dist_Accu_u32 = 0;

	/*To Init the Odo data reset value*/
	g_Odo_data_reset = 0;

	/*To Init the Odo data write value*/
	g_Odo_data_write = 0;

	/*To Init the RAFE value*/
	g_RAFE_u32 = DEFAULT_RAFE;
	
	/*To Init the CAN ECM status as FALSE*/
	g_CAN_ECM_Status_u8 = FALSE;
	
	/*To Init the ABS Vehicle speed status as FALSE*/
	g_CAN_ABD_Vehicle_Speed_Status_u8 = FALSE;
	
	/*To Init the Odo Value in Km*/
	g_Get_Odo_km_value_u32 = 0;

	/*To Init the current RAFE Value*/
	g_Current_RAFE_u32 = 0;
	
	/*To Init the fuel bar value*/
	g_FuelBar_u8 = 0;

	/*To Init the Previous fuel bar value*/
	g_Prev_FuelBar_u8 = 0;
	
	/*To Init the DTE Inc Allowed value*/
	g_DTE_Inc_allowed_u8 = FALSE;

	/*To Init the Process time*/
	g_Fuel_Consum_process_time_u8 = 0;

	/*To Init the Fuel used value*/
	g_FuelUsed_u32 = 0;
}

/*
* @brief    This function is used for IFE preconditions
* @param    void
* @return   uint8_t
* @note:    N/A
*/
uint8_t IFE_Pre_Condition(void)
{
	/*This variable is used to hold the the precondition status*/
	bool fl_IFE_Precondition_Status_bool;

	/*Store the Ign value of the vehicle*/
  	uint8_t fl_IFE_Ign_Position_u8;
	
	/*Store the low voltage of the vehicle*/
  	uint8_t fl_IFE_Speedo_LVSD_check_u8;
	
	/*Store the high voltage of the vehicle*/
  	uint8_t fl_IFE_Speedo_HVSD_check_u8;

  	/*This variable is to store the CAN Bus off status*/
  	uint8_t fl_CAN_Bus_off_Status_u8;

	/*Store the Speed fault status*/
	bool fl_IFE_Speedfault_status_bool;
	
	/*Store the Speed of the vehicle*/
	uint32_t fl_IFE_inputspeed_u32 = 0;

	uint8_t index = 0;

  	/*Store the Ignition state*/
  	fl_IFE_Ign_Position_u8 = IGN_MODE();

  	/*Store the low voltage state*/
  	fl_IFE_Speedo_LVSD_check_u8 = GET_LSVD_STATUS();

  	/*Store the high voltage state*/
  	fl_IFE_Speedo_HVSD_check_u8 = GET_HSVD_STATUS();

	/*This variable is to store the Speed fault status*/
	fl_IFE_Speedfault_status_bool = SPEED_FAULT_STATUS();

	/*This variable is to store the input Speed of the vehicle*/
	fl_IFE_inputspeed_u32 = Get_display_Speed();

	/*This variable is to store the CAN Bus off status*/
	fl_CAN_Bus_off_Status_u8 = App_Can_bus_off_Get_indication();

  	/*Check the IGN status*/
  	if(fl_IFE_Ign_Position_u8 == IGN_ON)
  	{
	  	/*Check the voltage status OR check the CAN Bus off notication OR check the CAN Message timeout
		  OR check the speed fault status OR check the input vehicle speed*/	
	  	if(((fl_IFE_Speedo_LVSD_check_u8 == 0) || (fl_IFE_Speedo_HVSD_check_u8 == 0)) 
		  || (TC_CAN_BUS_OFF_STATUS != fl_CAN_Bus_off_Status_u8)
		  || (g_CAN_ECM_Status_u8 == TRUE) 
		  || (fl_IFE_Speedfault_status_bool == TRUE)
		  || (fl_IFE_inputspeed_u32 < IFE_MIN_SPEED) )
	   	{
			/*This variable is used to store the display timer */
			g_IFE_Display_Update_time_u8 = IFE_INITIAL_DISPLAY_UPDATE_TIME;

			/*Hold the index count as zero*/
			g_IFE_index_u8 = 0;

			for (index = 0; index < 10; index++)
			{
				/*Hold the IFE Calculation as Zero*/
				g_IFE_CAL_f32[index] = 0;
			}

			/*Hold the pre condition as not ok*/
			fl_IFE_Precondition_Status_bool = TC_E_NOK;
		}
		else
		{		
			/*To set the variable as true*/
			fl_IFE_Precondition_Status_bool = TC_E_OK;
		}
	}
	else
	{
		/*To set the variable as true*/
		fl_IFE_Precondition_Status_bool = TC_E_NOK;
	}

  /*To return the pre condition status*/
  return fl_IFE_Precondition_Status_bool;
}

/*
* @brief    This function is used for IFE preconditions
* @param    void
* @return   uint8_t
* @note:    N/A
*/
uint8_t AFE_Pre_Condition(void)
{	
	/*This variable is used to hold the the precondition status*/
	bool fl_AFE_Precondition_Status_bool;

	/*Store the Ign value of the vehicle*/
  	uint8_t fl_AFE_Ign_Position_u8;
	
	/*Store the low voltage of the vehicle*/
  	uint8_t fl_AFE_Speedo_LVSD_check_u8;
	
	/*Store the high voltage of the vehicle*/
  	uint8_t fl_AFE_Speedo_HVSD_check_u8;
	
  	/*This variable is to store the I2C error Status*/
  	uint8_t fl_AFE_I2C_Error_status_u8 = 0;

  	/*Store the Ignition state*/
  	fl_AFE_Ign_Position_u8 = IGN_MODE();

  	/*Store the low voltage state*/
  	fl_AFE_Speedo_LVSD_check_u8 = GET_LSVD_STATUS();

  	/*Store the high voltage state*/
  	fl_AFE_Speedo_HVSD_check_u8 = GET_HSVD_STATUS();

	/*This variable is to store the I2C error Status*/
	fl_AFE_I2C_Error_status_u8 = GET_I2C_ERROR_STATUS();

  	/*Check the IGN status*/
  	if(fl_AFE_Ign_Position_u8 == IGN_ON)
  	{
	  	/*Check the voltage status OR check the CAN Bus off notication OR check the CAN Message timeout
		  OR check the speed fault status OR check the input vehicle speed*/	
	  	if(((fl_AFE_Speedo_LVSD_check_u8 == 0) || (fl_AFE_Speedo_HVSD_check_u8 == 0)) 
		  || (fl_AFE_I2C_Error_status_u8 == TRUE) )
	   	{
			/*Hold the pre condition as not ok*/
			fl_AFE_Precondition_Status_bool = TC_E_NOK;
		}
		else
		{		
			/*To set the variable as true*/
			fl_AFE_Precondition_Status_bool = TC_E_OK;
		}
	}
	else
	{
		/*To set the variable as true*/
		fl_AFE_Precondition_Status_bool = TC_E_NOK;

		g_TC_IGN_ON_Status = TRUE;
	}

  /*To return the pre condition status*/
  return fl_AFE_Precondition_Status_bool;

}


/*
* @brief    This function is used for DTE preconditions
* @param    void
* @return   uint8_t
* @note:    N/A
*/
uint8_t DTE_Pre_Condition(void)
{
	/*This variable is used to hold the the precondition status*/
	bool fl_DTE_Precondition_Status_bool;

	/*Store the Ign value of the vehicle*/
  	uint8_t fl_DTE_Ign_Position_u8;
	
	/*Store the low voltage of the vehicle*/
  	uint8_t fl_DTE_Speedo_LVSD_check_u8;
	
	/*Store the high voltage of the vehicle*/
  	uint8_t fl_DTE_Speedo_HVSD_check_u8;
	
  	/*Store the Ignition state*/
  	uint8_t fl_DTE_I2C_Error_status_u8;
	
	/*This variable is to store the CAN Bus off status*/
  	uint8_t fl_CAN_Bus_off_Status_u8;

	uint8_t fl_CAN_ABD_Vehicle_Speed_Status_u8;

	/*Store the Speed fault status*/
	bool fl_DTE_Speedfault_status_bool;
	
	/*Store the Speed of the vehicle*/
	uint8_t fl_DTE_inputspeed_u8;

	/*To store the Fuel Status*/
	uint8_t g_fuel_Short_open_Status;

  	/*Store the Ignition state*/
  	fl_DTE_Ign_Position_u8 = IGN_MODE();
	  
	/*Store the low voltage state*/
  	fl_DTE_Speedo_LVSD_check_u8 = GET_LSVD_STATUS();

  	/*Store the high voltage state*/
  	fl_DTE_Speedo_HVSD_check_u8 = GET_HSVD_STATUS();

	/*This variable is to store the I2C error Status*/
	fl_DTE_I2C_Error_status_u8 = GET_I2C_ERROR_STATUS();

	/*This variable is to store the Speed fault status*/
	fl_DTE_Speedfault_status_bool = SPEED_FAULT_STATUS();

	/*This variable is to store the input Speed of the vehicle*/
	fl_DTE_inputspeed_u8 = INPUT_SPEED_VALUE();

	/*This variable is to store the CAN Bus off status*/
	fl_CAN_Bus_off_Status_u8 = CAN_BUSOFF_INDICATION();

	fl_CAN_ABD_Vehicle_Speed_Status_u8 = SPEED_FAULT_STATUS();

	/*To store the Fuel Guage Get Fault Status*/
	g_fuel_Short_open_Status = Swc_Fuel_Gauge_Get_Fault_Status();

  	/*Check the IGN status*/
  	if(fl_DTE_Ign_Position_u8 == IGN_ON)
  	{
	  	/*Check the voltage status OR check the CAN Bus off notication OR check the CAN Message timeout
		  OR check the speed fault status OR check the input vehicle speed OR To Check the Fuel Guage Get Fault Status*/	
	  	if(((fl_DTE_Speedo_LVSD_check_u8 == 0) || (fl_DTE_Speedo_HVSD_check_u8 == 0)) 
		  || (TC_CAN_BUS_OFF_STATUS != fl_CAN_Bus_off_Status_u8)
		  || (fl_CAN_ABD_Vehicle_Speed_Status_u8 == TRUE) 
		  || (fl_DTE_Speedfault_status_bool == TRUE)
		  || (g_CAN_ECM_Status_u8 == TRUE)
		  || (g_fuel_Short_open_Status != FUEL03_STATUS_NO_OPEN_SHORT)
		  || (fl_DTE_I2C_Error_status_u8 == TRUE) )	
	   	{
			/*Hold the pre condition as not ok*/
			fl_DTE_Precondition_Status_bool = TC_E_NOK;
		}
		else
		{		
			/*To set the variable as true*/
			fl_DTE_Precondition_Status_bool = TC_E_OK;
		}
	}
	else
	{
		/*To set the variable as true*/
		fl_DTE_Precondition_Status_bool = TC_E_NOK;
	}

  /*To return the pre condition status*/
  return fl_DTE_Precondition_Status_bool;
}

void CanMgr_TC_reception_cbk(void)
{
	g_CAN_ECM_Status_u8 = FALSE;

	g_CAN_Missing_Detect = FALSE;
}


/*
* @brief    This function is ECM_ADDITION_INFO_Timeout_Callback
* @param    void
* @return   void
* @note:    N/A
*/
void ECM_ADDITION_INFO_Timeout_Callback_0x135(void)
{
	/*To set the variable as true*/
	CanMgr_TC_Timeout_Flag();
}


void CanMgr_TC_Timeout_Flag(void)
{

	g_CAN_ECM_Status_u8 = TRUE;

}
/*
* @brief    This function is ECM_ADDITION_INFO_Timeout_Callback
* @param    void
* @return   void
* @note:    N/A
*/
void ABS_Vehicle_Speed_Timeout_Callback_0x130(void)
{
	/*To set the variable as true*/
	g_CAN_ABD_Vehicle_Speed_Status_u8 = TRUE;
}

void Swc_AFE_SW_Reset(uint8_t fl_Trip_Index_u8)
{
	/*To set the Reset trigger as 0*/
	g_Trip_AFE_Reset_Trigger_u8[fl_Trip_Index_u8] = 0;
		
	/*To set the Reset trigger as 0*/
	g_Trip_AFE_Sw_Reset_u8[fl_Trip_Index_u8] = 0;

	/*To set the AFE Distance Accumulation value*/
	g_AFE_Dist_ACCU_u64[fl_Trip_Index_u8] = 0;
				
	/*To set the AFE Fuel Cons accumulation value*/
	g_AFE_Fuel_Cons_ACCU_u32[fl_Trip_Index_u8] = 0;

	g_AFE_Display_value_u32[fl_Trip_Index_u8] = 0;

	/*To set the AFE displayed value*/
	g_Displayed_AFE_u32[fl_Trip_Index_u8] = 0;
}

/*
* @brief    This function is used to validate Current AFE value in L/100km unit 
* @param    uint32_t *p_AVF_Val -  pointer to data
* @return   NONE
* @note:    N/A
*/
void SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(uint32_t *p_AVF_Val)
{
	/* check value in 0.1 resolution*/
	if((*p_AVF_Val) > (AFE_MAX / 10))
	{
		/* assign max value */
		*p_AVF_Val = (AFE_MAX / 10);
	}
	else
	{
		/* do nothig */
	}
}

/*
* @brief    This function is used to validate Current RTMI value in L/100km unit 
* @param    uint32_t *p_AVF_Val -  pointer to data
* @return   NONE
* @note:    N/A
*/
void SWC_TC_Max_Limit_Check_For_RTMI_In_LPer100KM(uint32_t *p_AVF_Val)
{
	/* check value in 0.1 resolution*/
	if((*p_AVF_Val) > IFE_MAX )
	{
		/* assign max value */
		*p_AVF_Val = AFE_MAX;
	}
	else
	{
		/* do nothig */
	}
}


void AFE_NVM_Fuel_Accumulation_Allocate(void)
{
  



}








/**********************************************************************************************************************/
/*                                              E N D   O F   S O F T W A R E                                         */
/**********************************************************************************************************************/


/**********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y                                       
 **********************************************************************************************************************/
/**********************************************************************************************************************
REVISION NUMBER      : V1.0.0
REVISION DATE        : 11-March-2021
CREATED / REVISED BY : Maheswari R(maheswari@niyatainfotech.com)
DESCRIPTION          : Code Implemented and comments Added:

REVISION NUMBER      : V1.0.1
REVISION DATE        : 16-March-2021
CREATED / REVISED BY : Maheswari R(maheswari@niyatainfotech.com)
DESCRIPTION          : Included Alarm task for round robin execution	

REVISION NUMBER      : V1.0.2
REVISION DATE        : 16-November-2022
CREATED / REVISED BY : Palani kumr R(palanikumar@niyatainfotech.com)
DESCRIPTION          : Fuel accumulation process time for DTE calculation updated.

REVISION NUMBER      : V1.0.3
REVISION DATE        : 24/01/2023
CREATED / REVISED BY : Palani kumr R(palanikumar@niyatainfotech.com)
DESCRIPTION          : Max limit validation for AFE , RTMI in L/100Km unit implemented.
------------------------------------------------------------------------------------------------------------------------

**********************************************************************************************************************/
#endif /* ! TC_C */
