/* @file FILE N/AME */
 #ifndef FUEL_GUAGE_CFG_H
 #define FUEL_GUAGE_CFG_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Palani kumar (palanikumar@niyatainfotech.com)                                                                        
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File N/Ame                       : Fuel_Guage_Cfg.h
*  Version                         : v1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : J link
*  Platforms supported             : PLatform Independent
*  Description                     : This file contains the configuration declarations of fuel guage
*  @bug                            : 
*--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S 
***********************************************************************************************************************/
#include "Fuel_Guage.h"
#include "Cmp_Tasks.h"
/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                    C O N F I G U R A T I O N     M A C R O S                      
***********************************************************************************************************************/
/*
* @brief: This macro is used to configure the fuel sensor open circuit adc value 
* @Unit:  N/A
* @Resolution:N/A 
* @Range: N/A
* @Applicability: fuel filling
* @Note: 
*/
#define FUEL03_OPEN_SENDER_LIMIT                    (100)
/*
* @brief: This macro is used to configure the fuel sensor short circuit adc value
* @Unit:  N/A
* @Resolution:N/A 
* @Range: N/A
* @Applicability: fuel filling
* @Note: 
*/
#define FUEL03_SHORTED_SENDER_LIMIT                 (883)
/*
* @brief: This macro is used to configure the function to get LVSD Status  
* @Unit:  N/A
* @Resolution:N/A 
* @Range: N/A
* @Applicability: fuel filling 
* @Note: 
*/
#define FUEL_GUAGE_LVSD_STATUS()              Sys_Service_Get_Low_Voltage_State()
/*
* @brief: This macro is used to configure the function to get HVSD Status  
* @Unit:  N/A
* @Resolution:N/A 
* @Range: N/A
* @Applicability: fuel filling 
* @Note: 
*/
#define FUEL_GUAGE_HVSD_STATUS()              Sys_Service_Get_High_Voltage_State()
/*
* @brief: This macro is used to configure the function to get Ignition Status  
* @Unit:  N/A
* @Resolution:N/A 
* @Range: N/A
* @Applicability: fuel filling
* @Note: 
*/
#define FUEL_GUAGE_GET_IGN_STATUS()           Sys_Service_Get_Ignition_State()
/*  
 * @brief: This macro is used to store count value after which update fuel bar in display  
 * @Unit:  N/A
 * @Resolution:N/A 
 * @Range: N/A
 * @Applicability: fuel filling
 * @Note: Multiply by fuel gauge task rate. 
 */
#define FUEL_BAR_UPDATE_COUNTER                10U

/*
* @brief: This macro is used to configure the function to get Ignition Status  
* @Unit:  N/A
* @Resolution:N/A 
* @Range: N/A
* @Applicability: fuel filling
* @Note: 
*/

#define FUEL03_KEY_ON_DELAY_TIME                2U

/*  
 * @brief: This macro is used to knoe the number of fuel bars availble on the fuel display
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 * @Note: 
 */
#define FUEL03_SCEM_NUMBER_OF_FUEL_TANKS      1

/*  
 * @brief: This macro is used to initialize the delay count time of the fuel 
 * @Unit:  N/A
 * @Resolution:N/A 
 * @Range: N/A
 * @Applicability: fuel filling 
 * @Note: 
 */
#define FUEL03_INIT_DELAY_COUNT_TIME            3U

/*  
 * @brief: This macro is used to get the open short issue of  fault time of the fuel  
 * @Unit:  N/A
 * @Resolution:N/A 
 * @Range: N/A
 * @Applicability: fuel filling 
 * @Note: 
 */
#define FUEL03_OPEN_SHORT_FAULT_TIME            50U

/*  
 * @brief: This macro is used to store recovery time taking from open short fault 
 * @Unit:  N/A
 * @Resolution:N/A 
 * @Range: NIL
 * @Applicability: 
 * @Note: 
 */
#define FUEL03_OPEN_SHORT_RECOVERY_TIME         50U

/*  
 * @brief: This macro is used to get number of good samples from fuel initialization 
 * @Unit:  N/A
 * @Resolution:N/A 
 * @Range: NIL
 * @Applicability: NIL
 * @Note: 
 */
#define FUEL03_INIT_GOOD_SAMPLES_REQUIRED       1U

/*  
 * @brief: This macro is used to get minimum fast fill time of the fuel tank per minute
 * @Unit: N/A  
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_MIN_FAST_FILL_TIME               0U

/*  
 * @brief: This macro is used to define the fast fill met status of the fuel bar 
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_FAST_FILL_MET_MACRO()          FALSE

/*  
 * @brief: This macro is used shows the status of the fast fill jam recovery eN/Able
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_FF_RECOV_FLTR_JAM_ENABLE       1



/*  
 * @brief: This macro is used to define the status of the power
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_POWER_MODE_MACRO()             FALSE

/*  
 * @brief: This macro is used to get the valid value state of the fuel range 
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_VALID_CONDITION()              TRUE

/*  
 * @brief: This macro is used to define the low voltage of the fuel system 
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_LOW_VOLTAGE()                (FALSE)

/*  
 * @brief: This macro is used to store count value after which update fuel bar in display  
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_AVG_TYPE                       (0)

/*  
 * @brief: This macro is used to get the force fill filter jam condition status  
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_FORCE_FILT_JAM                  (0)

/*  
 * @brief: This macro is used to get the key sample time of the fuel sensor system
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_KEY_OFF_SAMPLE_TIME            (0)

/* 
 * @brief: This macro is used to get the average reference value
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_REF_AVG_TYPE    (0)

/*  
 * @brief: This macro is used to get average sample values of fuel system
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */

#define FUEL03_SMPLS_2_AVG (1)

/*  
 * @brief: This macro is used to get the fuel zero speed counter
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_ZERO_SPEED_COUNTER (5) 

/*  
 * @brief: This macro is used to store delta fast adjust value of the fuel tank  
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: N/A
 * @Note: Multiply by fuel gauge task rate. 
 */
#define FUEL03_DELTA_FAST_ADJUST_A (0x0000)

/*  
 * @brief: This macro is used to get the delta fast base status from fuel sensor 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_DELTA_FAST_BASE_A 40265318uL

/*  
 * @brief: This macro is used to know the status of the clamp position 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL
 * @Note: 
 */
#define FUEL03_DELTA_FAST_CLAMP_A (0x00FFFFFFuL) 

/*  
 * @brief: This macro is used to know the state of the normal adjustment of the fuel delta   
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_DELTA_NORMAL_ADJUST_A (0)

/*  
 * @brief: This macro is used to know the normal base status of the fuel  
 * @Unit: N/A 
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL
 * @Note: 
 */
#define FUEL03_DELTA_NORMAL_BASE_A1 16497596uL 

/*  
 * @brief: This macro is used to know the state of the normal clamp adjustment of the fuel  
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_DELTA_NORMAL_CLAMP_A (0x0FFFFFFFuL)

/*  
 * @brief: This macro is used to know the negative range of fuel fast fill state 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL
 * @Note: 
 */
#define FUEL03_NEGATIVE_FAST_FILL_DELTA_A (30)

/*  
 * @brief: This macro is used to know the negative range of fuel initial fill state 
 * @Unit:  N/A
 * @Resolution: N/A 
 * @Range: N/A
 * @Applicability: NIL
 * @Note: 
 */
#define FUEL03_NEGATIVE_INIT_FILL_DELTA_A (30)

/*  
 * @brief: This macro is used to know the full negative hysterisis percent of the fuel fill   
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: 
 */
#define FUEL03_PERCENT_FULL_NEGATIVE_HYST (0)

/*  
 * @brief: This macro is used to know the full positive hysterisis percent of the fuel fill   
 * @Unit: N/A 
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL
 * @Note: 
 */
#define FUEL03_PERCENT_FULL_POSITIVE_HYST (0)

/*  
 * @brief: This macro is used to know the positive range of fuel fast fill state
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL
 * @Note: 
 */
#define FUEL03_POSITIVE_FAST_FILL_DELTA_A (18)

/*  
 * @brief: This macro is used to know the positive initial range of fuel fast fill state
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 * @Note: Multiply by fuel gauge task rate. 
 */
#define FUEL03_POSITIVE_INIT_FILL_DELTA_A (18)

/*  
 * @brief: This macro is used to know the error state of the fuel sensor
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL
 * @Note: 
 */
#define FUEL03_SENDERA_ERROR  (6)

/*  
 * @brief: This macro is used to know the error state of the fuel fill state
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: Multiply by fuel gauge task rate. 
 */
#define FUEL03_SENDERA_RC_FILL_DELTA (0xFF)

/*  
 * @brief: This macro is used to send the error message on the fuel fill thresold  
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: Multiply by fuel gauge task rate. 
 */
#define FUEL03_SENDERA_RC_FILL_THRESHOLD (0xFF)

/*  
 * @brief: This macro is used to know the weight of sensor error   
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: Multiply by fuel gauge task rate. 
 */
#define FUEL03_SENDERA_WEIGHT (128)

/*  
 * @brief: This macro is used to know the preload state of  the tank before the filter slosh state
  * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: Multiply by fuel gauge task rate. 
 */
#define FUEL03_SLOSH_FILTER_EMPTY_PRELOAD_A (0x00000000uL)

/*  
 * @brief: This macro is used to store count value after which update fuel bar in display  
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: Multiply by fuel gauge task rate. 
 */
#define FUEL03_ZS_DELTA_A  (6)

/*  
 * @brief: This macro is used to 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: Multiply by fuel gauge task rate. 
 */
#define FUEL03_FILTER_RES (2)

/*  
 * @brief: This macro is used to 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL 
 * @Note: Multiply by fuel gauge task rate. 
 */
#define FUEL03_SEC_POS_INIT_FILL_DELTA_A (18)

/*  
 * @brief: This macro is used to 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL: 
 * @Note: Multiply by fuel gauge task rate. 
 */
#define FUEL03_SEC_NEG_INIT_FILL_DELTA_A (18)

/*  
 * @brief: This macro is used to 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL
 * @Note: Multiply by fuel gauge task rate. 
 */
#define FUEL03_KO_DELTA_A  (0)


	   /* ----------------------------------------------------------------------------------
	    ** Define the table to convert the SENDERA from A/D to percent full.
	    **
	    ** This table is stored in Sender_A_TableNVM.
	    **
	    ** This is used if FUEL03_SCEM_NUMBER_OF_FUEL_TANKS is not defined.
	    ** ----------------------------------------------------------------------------------
	    */
#define FUEL03_SENDER_A_AD_TO_PF_TBL_SIZE (17)


#define FUEL_03_NVM_BLOCK_ID             17

/*  
 * @brief: This macro is used to 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: NIL
 * @Note: Multiply by fuel gauge task rate. 
 */

#define NVM_FLPS_BLOCK_SIZE               4
/***********************************************************************************************************************
*                             C O N F I G U R A T I O N    C O N S T A N T S    D E C L A R A T I O N                       
***********************************************************************************************************************/
/*
* @brief: This variable is used to configure 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note: 
*/

/***********************************************************************************************************************
*                            C O N F I G U R A T I O N    V A R I A B L E S    D E C L A R A T I O N                  
***********************************************************************************************************************/

/*
 * @brief    This typedef enum is used to define different Fuel Bar levels
 * @param    
 * @param
 **/

typedef enum
{
  FUEL_BAR_POS_0 = 0,
  FUEL_BAR_POS_1 = 1,
  FUEL_BAR_POS_2,
  FUEL_BAR_POS_3,
  FUEL_BAR_POS_4,
  FUEL_BAR_POS_5,
  FUEL_BAR_POS_6,
  FUEL_BAR_POS_7
}FUEL_BAR_POS_EN;
/*
* @brief This variable is used to configure the Bar ON/OFF resistance value for each Fuel Bar Levels
* @Unit:  FUEL_GUAGE_BAR_RES_CFG
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/
typedef struct 
{
   FUEL_BAR_POS_EN  Fuel_Bar_Level;
   uint16_t Bar_ON_Res_Val;
   uint16_t Bar_OFF_Res_Val;
   uint16_t Fuel_Capacity_Val;
}FUEL_GUAGE_BAR_RES_CFG;

extern FUEL_GUAGE_BAR_RES_CFG g_Fuel_Guage_Res_Bar_Map_Table[8];
/*********************************************************************************************************************
*                         C O N F I G U R A T I O N     F U N C T I O N    D E C L A R A T I O N S                      
*********************************************************************************************************************/
/*
* @brief    This function is used to 
* @param    
* @return 
* @note:  
*/

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : v1.0.0                          
    REVISION DATE        : 03/27/2022        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)    
    DESCRIPTION          : Initial version                                             
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
 #endif /* ! FUEL_GAUGE_CFG_H */
