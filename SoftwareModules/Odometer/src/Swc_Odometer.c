/* @file FILE NAME */
#ifndef ODO_C
#define ODO_C
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
*  File name                       : ODO.c
*  Version                         : V1.0.2
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent
*  Description                     : This file contains the Implementation of Odometer 
*  @bug                         
--------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/


/*********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                             
*********************************************************************************************************************/
#include "Swc_Odometer.h"
#include "Swc_Odometer_cfg.h"
#include "Swc_Averege_Speed.h"
#include "Swc_Speedometer.h"
#include "fsl_gpio.h"
#include "Cmp_Tasks.h"
#include "CanMgr_cfg.h"
#include "TC.h"
#include "task.h"
#include "Swc_Service_Remainder.h"
#include "I2C_Handler.h"
#include "HMI_Setting_Screen.h"
#include "lvgl_app.h"
#include "Fuel_Guage.h"
#include"Swc_Nvm_Handler.h"

/*********************************************************************************************************************
*                                             M A C R O   D E F I N I T I O N S                                          
*********************************************************************************************************************/
/*Check Distance compute method with out of range*/
#if (ODO_DISTANCE_COMPUTE_METHOD > 2u)
#error Distance compute method selection is out of range
#endif

/*
* @brief		: This enum is used to define active flag status
* @Unit			: N/A
* @Resolution	: 1
* @Range		: 0 to 8 bit
* @Applicability: ODO_ACTIVE function is activated or deactivated based on this configuration
*/
typedef enum
{
	ODO_DEACTIVATE = 0u,
	ODO_ACTIVATE   = 1u

} ODO_ActiveFlag_List_Type_en;


/*Check distance compute method with speed input*/
#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_SPEED)
/*
* @brief		: This variable is used to define  conversion from kilometer per hour to centimeter per milliseconds
* @Unit			: N/A
* @Resolution	: 1
* @Range		: 0 to 8 bit 
* @Applicability: This configuration is used in distance computation for speed input
*/
#define ODO_KMPH_CMPMS_DIVIDE_FACTOR    36u
#endif

/*Check distance compute method with frequency input*/
#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_FREQUENCY)
/*
* @brief		: This variable is used to define  resolution for the pi value
* @Unit			: N/A
* @Resolution	: 0.01
* @Range		: 0 t0 32 bit
* @Applicability: This configuration is used in distance computation for frequency input
*/
#define ODO_PI_VALUE                   (uint32_t)3.14

/*
* @brief		: This variable is used to define  time task in seconds by divide factor
* @Unit			: seconds
* @Resolution	: 1
* @Rang			: 0 to 8 bit 
* @Applicability: This configuration is used in  distance computation for frequency input
*/
#define ODO_TIMETASK_DIVIDE_FACTOR     (1000u / ODO_TIMETASK_MS)

/*
* @brief		: This variable is used to define  minute to second conversion factor
* @Unit			: N/A
* @Resolution	: 1
* @Range		: 0 to 8 bit
* @Applicability: This configuration is used in  distance computation for frequency input
*/
#define ODO_MIN_SEC_CONV_FACTOR       60u
#endif

/*
* @brief		: This variable is used to define kilometer to centimeter conversion factor
* @Unit			: Centimeter
* @Resolution	: 0.1
* @Range		: 0 to 32 bit
* @Applicability: This configuration is used to check accumulate distance in km with this configuration
*/
#define ODO_KM_CM_CONV_FACTOR        (uint32_t)10000u

/*
* @brief		: This variable is used to define distance data size
* @Unit			: N/A
* @Resolution	: 1
* @Range		: 0 to 8 bit
* @Applicability: This configuration is used to retrive the data from NVM
*/
#define ODO_DISTANCE_DATA_SIZE       3u

/*
* @brief		: This macro is used to configure the maximum distance
* @Unit			: Kilometer
* @Resolution	: 0.1
* @Range		: 0 to 32 bit
* @Applicability:Compute the odomter distance upto this maximum value 
*/
#define ODO_MAX_DISTANCE_KM         (uint32_t)9999999u

/*
* @brief		: This variable is used to define NVM block size
* @Unit			: N/A
* @Resolution	: 1
* @Range		: 0 to 32 bit
* @Applicability: This configuration is used to store distance data set in NVM block size
*/
#define ODO_NVM_BLOCK_SIZE         10

/*
* @brief		: This variable is used to define Encrypt data set size
* @Unit			: N/A
* @Resolution	: 1
* @Range		: 0 to 8 bit
* @Applicability: This configuration is used to store Encrypt data set in NVM
*/
#define ODO_NVM_STORAGE_BYTES     16u

/*
* @brief          : This macro is used to configure the NVM block id for Trip
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : Store Trip distance from NVM block id
*/
#define ODO_TRIP_NVM_BLOCK_ID    (uint32_t)10u

/*
* @brief          : This macro is used to configure the NVM start id
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : Store the computed distance in NVM start block Id
*/
#define ODO_NVM_START_BLOCK_ID   0u

/*
* @brief		  : This variable is used to CRC init value
* @Unit			  : N/A
* @Resolution     : 1
* @Range          : 0 to 8 bit
* @Applicability  : This configuration is used in CRC computation for distance
*/
#define ODO_CRC_INIT_VALUE      (uint8_t)0xFF

/*
* @brief		 : This variable is used to define CRC polynomial value
* @Unit			 : N/A
* @Resolution    : 1
* @Range         : 0 to 8 bit
* @Applicability : This configuration is used in CRC computation for distance
*/
#define ODO_CRC_POLYNOMIAL_VALUE (uint8_t)0x1D


/*
* @brief          : This macro is used to GET the periodicity of ODO_Active() method
* @Unit           : milliseconds
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : Execution of ODO_Active Function with this time task 
* @Note           : Do not modify this macro value or name
*/
#define ODO_TIMETASK_MS               50u

/*
* @brief          : This macro is used to configure NVM storage resolution
* @Unit           : Kilometer
* @Resolution:    : 0.1
* @Range          : 0 to 32 bit
* @Applicability  : Store the odometer value to NVM with this resolution
* @Note           : Do not modify this macro value or name
*/
#define ODO_DISTANCE_NVM_RESOLUTION    1

/*
* @brief          : This macro is used to configure the timetask in milliseconds
* @Unit           : Kilometer 
* @Resolution:    : 0.1
* @Range          : 0 to 32 bit
* @Applicability  : Added this value to NVM highest data set
* @Note           : Do not modify this macro value or name
*/
#define ODO_NVM_LOSS_GAIN             0u
/*
* @brief          : This macro is used to configure the function for write distance to NVM
* @Unit           : N/A
* @Resolution:    : N/A
* @Range          : N/A
* @Applicability  : Computed Distance store in NVM with configurable resolution
* @Note           : X-ODOMETER DATA SET NVM INDEX 
                    Y-DISTANCE DATA (pointer)
                    Z - Data size
*/
#define  ODO_NVM_WRITE_DATA(X,Y)    NVM_Byte_Write_Allocation(X,Y)

/*
* @brief          : This macro is used to configure the function for read distance from NVM
* @Unit           : N/A
* @Resolution:    : N/A
* @Range          : N/A
* @Applicability  : Computed Distance Read from NVM with configurable resolution
* @Note           : X-ODOMETER DATA SET NVM INDEX 
                    Y-DISTANCE DATA(pointer)
                    Z - Data size
*/
#define   ODO_NVM_READ_DATA(X,Y)     NVM_Byte_Read_Allocation(X,Y)

/*
* @brief          : This macro is used to configure Max Trip distance value 
* @Unit           : Kilometer 
* @Resolution:    : 0.1
* @Range          : 0 to 32 bit
* @Applicability  : To detect Max Distance accumulation and do rollback to zero
* @Note           : Do not modify this macro value or name
*/
#define TRIP_ODO_MAX_DISTANCE               (uint16_t) 9999

/*
* @brief          : This macro is used to configure the Minimum Init valid samples required 
* @Unit           : uint8_t
* @Resolution:    : 1
* @Range          : 0 to 8 bit
* @Applicability  : CRC and Parity check of Odo
* @Note           : Do not modify this macro value or name
*/
#define ODO_INIT_VALID_DATA_REQUIRED        (uint8_t) 7



/*
* @brief          : This macro is used to configure the selection of compute method
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : 0 to 8 bit
* @Applicability  : Compute the distance based on this selection method
* @Note           : Do not modify this macro value or name
*/
#define ODO_DISTANCE_COMPUTE_METHOD ODO_INPUT_METHOD_SPEED

#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_SPEED)
/*
* @brief          : This macro is used to configure the function of Get speed
* @Unit           : Kilometer per hour
* @Resolution:    : 0.01
* @Range          : 0 to 32 bit
* @Applicability  : Only if ODO_INPUT_METHOD_SPEED is selected in ODO_DISTANCE_COMPUTE_METHOD
* @Note           : Do not modify this macro value or name
*/
#define ODO_GET_SPEED_KMPH                Get_Speed_KMPH
#endif

#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_DISTANCE)
/*
* @brief          : This macro is used to configure the function of Get Distance 
* @Unit           : Centimetre
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : Only if ODO_INPUT_METHOD_DISTANCE is selected in ODO_DISTANCE_COMPUTE_METHOD
* @Note           : Do not modify this macro value or name
*/
#define ODO_GET_DISTANCE_CM               Get_Distance_CM

/*
* @brief          : This macro is used to configure the CAN overflow distance
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : This value is used to compute distance using distance input
* @Note           : Do not modify this macro value or name
*/
#define ODO_CAN_OVERFLOW_DISTANCE_VALUE    255u
#endif

#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_FREQUENCY)
/*
* @brief          : This macro is used to configure the function of Get Frequency
* @Unit           : Hz
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : Only if ODO_INPUT_METHOD_FREQUENCY is selected in ODO_DISTANCE_COMPUTE_METHOD
* @Note           : Do not modify this macro value or name
*/
#define ODO_GET_FREQUENCY_HZ             Get_Frequency

/*
* @brief          : This macro is used to configure the wheel diameter
* @Unit           : centimeter
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : This value is used to compute the distance in frequency input
* @Note           : Do not modify this macro value or name
*/
#define ODO_WHEEL_DIAMETER_CM           66u

/*
* @brief          : This macro is used to configure the values of the Frequency and RPM
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : This value is used to compute the distance using frequency input
* @Note           : Do not modify this macro value or name
*/
#define ODO_MAX_FR_RPM_VALUES          (uint32_t)5u

/*
* @brief        : This variable is used to configure the frequency  and RPM values
* @Unit         : Hz
* @Resolution   : 1
* @Range        : 0 to 32 bit
* @Applicability: This configuration is used for distance computation using frequency input
* @Note         : Do not modify this macro value or name
*/
 #define ODO_RPM_FR_VALUES            {{5,80},{12,160},{20,241},{25,322},{30,402}}
 #endif


/*
* @brief          : This macro is used to configure the input method speed
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : 0 to 8 bit
* @Applicability  : Selection of ODO_INPUT_METHOD_SPEED in ODO_DISTANCE_COMPUTE_METHOD
* @Note           : Do not modify this macro value or name
*/
#define ODO_INPUT_METHOD_SPEED     0u

/*
* @brief          : This macro is used to configure the input method Distance
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : 0 to 8 bit
* @Applicability  : Selection of ODO_INPUT_METHOD_DISTANCE in ODO_DISTANCE_COMPUTE_METHOD
* @Note           : Do not modify this macro value or name
*/
#define ODO_INPUT_METHOD_DISTANCE   1u

/*
* @brief          : This macro is used to configure the input method frequency
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : 0 to 8 bit
* @Applicability  : Selection of ODO_INPUT_METHOD_FREQUENCY in ODO_DISTANCE_COMPUTE_METHOD
* @Note           : Do not modify this macro value or name
*/
#define ODO_INPUT_METHOD_FREQUENCY  2u

/*********************************************************************************************************************
*                                          G L O B A L   V A R I A B L E    D E C L A R A T I O N S                                    
*********************************************************************************************************************/
/*Check distance compute method with speed input*/
#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_SPEED)
/*
*@brief     	: This variable is used to hold the speed in KMPH
*@Unit      	: KMPH
*@Resolution	: 1
*@Range     	: 0 to 32 bit 
*@Applicability	: This variable is used for distance computation using speed input
*/
static uint32_t g_ODO_Speed_KMPH_u32;

/*
* @brief		: This function is used to compute distance from speed
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: N/A
*@Applicability	: This function is executed when speed input is selected. 
*/
static uint32_t ODO_Convert_Speed_To_Distance(uint32_t fl_ODO_Speed_KMPH_u32);
#endif

/*Check distance compute method with distance input*/
#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_DISTANCE)
/*
* @brief		: This variable is used to hold the previous distance through CAN signal 
*@Unit			: Centimeter
*@Resolution	: 1
*@Range			: 0 to 8 bit
*@Applicability	: This variable is used in distance computation using distance input
*/
static uint8_t g_ODO_Previous_Distance_CM_u8;

/*
* @brief		: This variable is used to hold the Current distance through CAN signal 
*@Unit			: Centimeter
*@Resolution	: 1
*@Range			: 0 to 8 bit
*@Applicability	: This variable is used in distance computation using distance input
*/
static uint8_t g_ODO_Current_Distance_CM_u8;

/*
* @brief		: This function is used to find the Distance from Delta Distance
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: N/A
*@Applicability	: This function is executed when Distance input is selected. 
*/
static uint32_t ODO_Convert_Distance_To_DeltaDistance(uint8_t fl_ODO_Current_Distance_CM_u8);
#endif

/*Check distance compute method with frequency input*/
#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_FREQUENCY)
/*
* @brief		: This variable is used to hold the frequency
*@Unit			: Hz
*@Resolution	: 1
*@Range			: 0 to 32 bit
*@Applicability	: This variable is used in distance computation for frequency input
*/
static uint32_t g_ODO_Frequecy_Hz_u32;

/*
* @brief		: This function is used to find the Distance from frequency
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: N/A
*@Applicability	: This function is executed when frequency input is selected. 
*/
static uint32_t ODO_Convert_Frequency_To_Distance(uint32_t fl_ODO_Frequency_u32);

/*
* @brief		: This variable is used to define Frequency RPM values
* @Unit			: N/A
* @Resolution	: 1
* @Range		: 0 to 32 bit
* @Applicability: This configuration is used in  distance computation for frequency input
*/
static  uint32_t ODO_Fr_RPM_Values[ODO_MAX_FR_RPM_VALUES][2] = ODO_RPM_FR_VALUES;
#endif

/*
*@brief			: This variable is used to define the Active function flag
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: Activate or Deactivate 
*@Applicability	: This variable is used in ODO_ACTIVE function to Check Activated or Deactivated
*/
static uint8_t g_ODO_ActiveFlag_u8;

/*
* @brief		: This variable is used to hold the Trip swich number
*@Unit			: N/A
*@Resolution	: 1
*@Range			: Trip switch Number
*@Applicability	: This variable is used to find Trip distance for the corrsponding Trip ID
*/
static uint8_t g_ODO_Trip_ID_u8;

/*
* @brief		: This variable is used to hold Trip Distance
*@Unit			: Kilometer
*@Resolution	: 1
*@Range			: 0 to 32 bit
*@Applicability	: This variable is used store Trip distance in ODO_Compute_TripDistance function.
*/
static uint32_t g_ODO_TripDistance_KM_u32[ODO_TRIP_MAX];

/*
* @brief		: This variable is used to hold distance when Trip is reset
*@Unit			:  Kilometer
*@Resolution	: 1
*@Range			: 0 to 32 bit
*@Applicability	: Store computed distance for the corresponding Trip ID
*/
static uint32_t g_ODO_Distance_TripReset[ODO_TRIP_MAX];

static uint32_t g_Trip_ODO_Cm_Var[ODO_TRIP_MAX];

/*
* @brief		: This variable is used to specify the  index value for Trip distance
*@Unit			: N/A
*@Resolution	: 1
*@Range			: 0 to 8 bit
*@Applicability	: Store computed Trip distance for the corresponding Trip Id in the index value
*/
static uint8_t g_ODO_Trip_Index_u8;

/*
* @brief		: This variable is used to hold the accumulate distance 
@Unit			: Centimeter
@Resolution		: 1
@Range			: 0 to 32 bit
@Applicability	: This variable is used to check distance in kilometer
*/
static uint32_t g_ODO_Accumulate_Distance_CM_u32;

/*
* @brief		: This variable is used to hold the distance in kilometer
*@Unit			:  Kilometer
*@Resolution	: 1
*@Range			: 0 to 32 bit
*@Applicability	: This variable is used to store distance data for NVM write
*/
static uint32_t g_ODO_Distance_Write_Data_KM_u32;

/*
* @brief		: This variable is used to hold distance valid data from NVM
*@Unit			: Kilometer
*@Resolution	: 1
*@Range			: 0 to 32 bit
*@Applicability	: This variable is used to get all Distance from NVM in Init function
*/
static uint32_t g_ODO_Distance_ValidData_KM_u32[ODO_NVM_BLOCK_SIZE];

/*
* @brief		: This variable is used to hold distance
*@Unit			: Kilometer
*@Resolution	: 0.1
*@Range			: 0 to 32 bit
*@Applicability	: Computed distance in KM and send to Application layer 
*/
static uint32_t g_ODO_Distance_KM_u32;

/*
* @brief		: This variable is used to hold highest value of distnace from NVM
*@Unit			:  Kilometer
*@Resolution	: 0.1
*@Range			: 0 to 32 bit
*@Applicability	: Find Highest value from NVM data set and store in this this variable
*/
static uint32_t g_ODO_Distance_Highest_Value_u32;

/*
* @brief		: This variable is used to specify the  index value for odometer distance
*@Unit			: N/A
*@Resolution	: 1
*@Range			:0 t0 32 bit
*@Applicability	: Store computed  distance in the index value
*/
static uint32_t g_ODO_Index_u32;

/*
* @brief		: This variable is used to hold the Encrypt data set for NVM write
@Unit			: N/A
@Resolution		: 1
@Range			: 0 to 8 bit
@Applicability	: This variable is used to write the Encrypt distance data to NVM
*/
static uint8_t g_ODO_NVM_Write_data_u8[ODO_NVM_STORAGE_BYTES];

/*
* @brief		: This variable is used to hold NVM block Id
*@Unit			:  N/A
*@Resolution	: 1
*@Range			: 0 to 32 bit
*@Applicability	: This variable is used to write the Encrypt distance data in this NVM block Id
*/
static uint32_t g_ODO_NVM_Block_Id_u32;

/*
* @brief		: This variable is used to hold check data for high value in NVM
*@Unit			:  N/A
*@Resolution	: 1
*@Range			: 0 to 32 bit
*@Applicability	: Find the highest value from NVM data sets in ODO_Init Function
*/
static uint32_t g_ODO_NVM_Check_Data_u32;

/*
* @brief		: This variable is used to hold NVM End Block Id
*@Unit			: N/A
*@Resolution	: 1
*@Range			: 0 to 32 bit
*@Applicability	: This variable is used to store Distance in NVM upto this block Id
*/
static uint32_t g_ODO_NVM_End_Block_Id_u32;

/*
* @brief		: This variable is used to check distance in kilometer
*@Unit			: N/A
*@Resolution	: 0.1
*@Range			:0 t0 32 bit
*@Applicability	: This variable is used to write distance distance to NVM 
*/
static uint8_t g_ODO_NVMData_u8;
/*
* @brief		: This variable is used to hold initial array size for distance
*@Unit			: N/A
*@Resolution	: 1
*@Range			: 0 to 32 bit
*@Applicability	: This variable is used to store Distance in NVM storage size
*/
static uint32_t g_ODO_Init_Index_u32 =ODO_NVM_STORAGE_BYTES-(uint32_t)1;

/*
* @brief		: This variable is used to get initial accumulatefor distance
*@Unit			: N/A
*@Resolution	: 0.1
*@Range			: 0 t0 32 bit
*@Applicability	: This variable is used to write distance distance to NVM 
*/
uint32_t g_Get_AccumulateValue =0;

/*
* @brief		: This variable is used to hold initial array size for distance
*@Unit			: N/A
*@Resolution	: 0.1
*@Range			: 0 t0 32 bit
*@Applicability	: This variable is used to write distance distance to NVM 
*/
static uint8_t g_ODO_TRIP_Init_Index_u32=(uint8_t)ODO_TRIP_MAX-(uint8_t)1;

/*
* @brief		: This variable is used to show the ODO distance accumulate remainder
*@Unit			: N/A
*@Resolution	: 0.1
*@Range			: 0 to 32 bit
*@Applicability	: This variable is used to write distance distance to NVM 
*/
static uint16_t g_ODO_Distance_Acc_Remainder_CM_u16 = 0;

/*
* @brief		: This variable is used to store CAN Bus OFF recovery counter used for sync up
*@Unit			: uint8_t
*@Resolution	: 1
*@Range			: 0 to 20
*@Applicability	: N/A
*/
uint8_t g_CAN_BUS_Off_Recovery_counter;

/*
* @brief		: This variable is used to store Trip ODO value in cm resolution for Averge speed
*@Unit			: uint16_t
*@Resolution	: 1cm
*@Range			: 0 to 64 bit
*@Applicability	: This variable is used to write distance distance to NVM 
*/
uint64_t g_TripOdo_Reset_Value_u64[TOTAL_TRIP_COUNT];

/*
* @brief		: This variable is used to count No. of valid data readed from NVM
*@Unit			: uint8_t
*@Resolution	: 1
*@Range			: 0 to ODO_INIT_VALID_DATA_REQUIRED
*@Applicability	: 
*/
static uint8_t g_ODO_Init_Valid_Data_Counter_u8;
/*
* @brief		: This variable is used to store status of NVM Error
*@Unit			: bool
*@Resolution	: N/A
*@Range			: TRUE OR FALSE
*@Applicability	: Used as Preconditon in odomter
*/
static bool g_ODO_NVM_Error_Status_bl;

/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E  D E C L A R A T I O N S  
 ***********************************************************************************************************************/
/*
* @brief		: This variable is used to find the Trip Distance
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: N/A
*@Applicability	: Store the computed trip distance for the corresponding Trip Id
*/
static uint32_t ODO_Compute_TripDistance(uint8_t Trip_Id);

/*
* @brief		: This function is used to find the CRC
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: N/A
*@Applicability	: Store the computed CRC for Encrypt distance data
*/
static uint8_t ODO_Compute_CRC(const uint8_t *MsgPtr, uint32_t Ptr_Length);

/*
* @brief		: This function is used to find the Parity
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: N/A
*@Applicability	: Store the computed parity for Encrypt distance data
*/
static uint8_t ODO_Compute_Parity(uint32_t fl_ODO_Distance_u32);

/*
* @brief		: This function is used to validate the odometer value
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: N/A
*@Applicability	: Store the valid data from NVM data set
*/
static uint32_t ODO_Validate_Odometer_Value(uint32_t fl_ODO_NVM_Block_Id_u32);

/*
* @brief	  	: This function is used to find the Highest Odometer value
*@Unit		  	: N/A
*@Resolution  	: N/A
*@Range       	: N/A
*@Applicability	: Store the highest value from NVM data set
*/
static uint32_t ODO_Find_Highest_Odometer_Value(const uint32_t *fl_ODO_Distance_CM_u32);

/*
* @brief		: This function is used to find Encrypt data 
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: N/A
*@Applicability	: Store the Encrypted data for the computed distance
*/
static void ODO_Compute_EncryptData(void);

/*
* @brief		: This function is used to store Encrypt data to NVM
*@Unit			: N/A
*@Resolution	: N/A
*@Range			: N/A
*@Applicability	: Store the Encrypted data  to the NVM block Id
*/
static void ODO_EncryptData_To_NVM(void);
/*********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N S                     
*********************************************************************************************************************/
/*
* @brief    This function is used to initialize the Odometer
* @param    None 
* @return   None
*/
void ODO_Init(void)
{
	uint8_t fl_ReadData_u8[3] = {0};


	/*Initialize the loop index for NVM block id*/
	uint32_t fl_loop_Index_u32;

	/*Initialize the loop index for Trip switch*/
	uint8_t fl_ODO_Trip_Index_u8;

	/*Initialize the Trip Block Id*/
	uint32_t fl_ODO_Trip_NVM_Block_Id_u32;

	/*Check distance compute method with speed input*/
    #if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_SPEED)
		/*Clear the speed value in KMPH*/
		g_ODO_Speed_KMPH_u32 = 0;
    #endif

    /*Check distance compute method with Distance input*/
    #if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_DISTANCE)
		/*Clear the Previous Distance value*/
		g_ODO_Previous_Distance_CM_u8 = 0;

		/*Clear the Current Distance value*/
		g_ODO_Current_Distance_CM_u8 = 0;
	#endif

	/*Check distance compute method with frequency input*/
	#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_FREQUENCY)
		/*Clear the Frequency value */
		g_ODO_Frequecy_Hz_u32 = 0;
		
	#endif

	/*Clear the Active flag*/
	g_ODO_ActiveFlag_u8 = 0;

	/*Clear the Trip Id*/
	g_ODO_Trip_ID_u8 = 0;

	/*Clear the Accumulate Distance value*/
	g_ODO_Accumulate_Distance_CM_u32 = 0;

	/*Clear the Distance value in KM*/
	g_ODO_Distance_Write_Data_KM_u32 = 0;

	/*Clear the write Distance value to NVM */
	g_ODO_NVM_Write_data_u8[g_ODO_Init_Index_u32] = 0;

	/*Clear the NVM Block Id*/
	g_ODO_NVM_Block_Id_u32 = ODO_NVM_START_BLOCK_ID;

	/*Clear the NVM check data*/
	g_ODO_NVM_Check_Data_u32 = 0;

	/*Clear the Trip Distace value*/
	g_ODO_TripDistance_KM_u32[g_ODO_TRIP_Init_Index_u32] = 0;

	/*Clear the Index value*/
	g_ODO_Trip_Index_u8 = 0;

	/*Clear the Index value*/
	g_ODO_Index_u32 = 0;

	g_ODO_NVMData_u8 = 0;

	/* Initialize the counter*/
	g_ODO_Init_Valid_Data_Counter_u8 = 0;

	ODO_Activate();
	/*Store NVM end block Id*/
	g_ODO_NVM_End_Block_Id_u32 = (uint32_t)(ODO_NVM_START_BLOCK_ID + ODO_NVM_BLOCK_SIZE);

	/*Loop Execution for TripIndex */
	for (fl_ODO_Trip_Index_u8 = (uint8_t)0; fl_ODO_Trip_Index_u8 < (uint8_t)ODO_TRIP_MAX; fl_ODO_Trip_Index_u8++)
	{
		/*Store the NVM block Id*/
		fl_ODO_Trip_NVM_Block_Id_u32 = ODO_TRIP_NVM_BLOCK_ID + fl_ODO_Trip_Index_u8;

	 	/*Read Odometer distance from NVM*/
		ODO_NVM_READ_DATA(fl_ODO_Trip_NVM_Block_Id_u32, &fl_ReadData_u8[0]);

		/*Store the trip distance when TRIP switch reset*/
		g_ODO_Distance_TripReset[fl_ODO_Trip_Index_u8] |= ((fl_ReadData_u8[0] << 16) | (fl_ReadData_u8[1] << 8) | (fl_ReadData_u8[2]));

	}

	/*Loop Execution to read Odometer distance from NVM Block ID */
	for (fl_loop_Index_u32 = (uint32_t)ODO_NVM_START_BLOCK_ID; fl_loop_Index_u32 < g_ODO_NVM_End_Block_Id_u32; fl_loop_Index_u32++)
	{
		/*Store valid distance data*/
		g_ODO_Distance_ValidData_KM_u32[g_ODO_Index_u32] = ODO_Validate_Odometer_Value(fl_loop_Index_u32);

		/*Increment the index value*/
		g_ODO_Index_u32 = g_ODO_Index_u32 + (uint32_t)1;
	}

	/* No of valid data read from NVM should be greater than or equal to Valid data required */
	if(g_ODO_Init_Valid_Data_Counter_u8 >= ODO_INIT_VALID_DATA_REQUIRED)
	{

		/*Store highest value from NVM*/
		g_ODO_Distance_Highest_Value_u32 = ODO_Find_Highest_Odometer_Value(&g_ODO_Distance_ValidData_KM_u32[0]);

		/* ODO NVM DATA ARE GOOD */
		g_ODO_NVM_Error_Status_bl = FALSE; 

	}
	else
	{
		/* ODO NVM CORRUPTION OCCURED*/
		g_ODO_NVM_Error_Status_bl = TRUE; 
	}

	/*Compare the Distance highest value*/
	if (g_ODO_Distance_Highest_Value_u32 > (uint32_t)0)
	{
		/*Store the Distance value with loss /gain*/
		g_ODO_Distance_KM_u32 = (g_ODO_Distance_Highest_Value_u32 * ODO_DISTANCE_NVM_RESOLUTION) + ODO_NVM_LOSS_GAIN;
	}
	else
	{
		/*Distance value with zero*/
		g_ODO_Distance_KM_u32 = 0;
	}

	Swc_Odo_CM_NVM_Read();

	g_CAN_BUS_Off_Recovery_counter = 20;

	Clear_NVM_Status();
}

/*
* @brief    This function is Deinit of the Odometer
* @param    None 
* @return   None
*/
void ODO_Deinit(void)
{
/*Check distance compute method with speed input*/
    #if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_SPEED)
		/*Clear the speed value in KMPH*/
		g_ODO_Speed_KMPH_u32 = 0;
    #endif

    /*Check distance compute method with Distance input*/
    #if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_DISTANCE)
		/*Clear the Previous Distance value*/
		g_ODO_Previous_Distance_CM_u8 = 0;

		/*Clear the Current Distance value*/
		g_ODO_Current_Distance_CM_u8 = 0;
	#endif

	/*Check distance compute method with frequency input*/
	#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_FREQUENCY)
		/*Clear the Frequency value */
		g_ODO_Frequecy_Hz_u32 = 0;
	#endif

	/*Clear the Active flag*/
	g_ODO_ActiveFlag_u8 = 0;

	/*Clear the Trip Id*/
	g_ODO_Trip_ID_u8 = 0;

	/*Clear the Accumulate Distance value*/
	g_ODO_Accumulate_Distance_CM_u32 = 0;

	/*Clear the Distance value in KM*/
	g_ODO_Distance_Write_Data_KM_u32 = 0;

	/*Clear the write Distance value to NVM */
	g_ODO_NVM_Write_data_u8[g_ODO_Init_Index_u32] = 0;

	/*Clear the NVM Block Id*/
	g_ODO_NVM_Block_Id_u32 = ODO_NVM_START_BLOCK_ID;

	/*Clear the NVM check data*/
	g_ODO_NVM_Check_Data_u32 = 0;

	/*Clear the Trip Distace value*/
	g_ODO_TripDistance_KM_u32[g_ODO_TRIP_Init_Index_u32] = 0;
}

/*
* @brief    This function is activate of the Odometer
* @param    None 
* @return   None
*/
void ODO_Activate(void)
{
	/*Activate the Odometer Active Flag*/
	g_ODO_ActiveFlag_u8 = (uint8_t)ODO_ACTIVATE;

}

/*
* @brief    This function is Deactivate of the Odometer
* @param    None 
* @return   None
*/
void ODO_Deactivate(void)
{
	/*Deactivate the Odometer Activate Flag*/
	g_ODO_ActiveFlag_u8 = (uint8_t)ODO_DEACTIVATE;
}

/*
* @brief    This function is main or active of the Odometer
* @param    None 
* @return   None
*/


void ODO_Active(void)
{
	uint8_t g_var_u8 = 0;

	uint8_t g_Write[3] = {0};
	uint8_t g_Read[3] = {0};
	uint8_t g_debug_varable = 0;
	uint8_t fl_loop_Idx_u8 = 0;	
	uint32_t fl_Odo_CAN_TX_U32 = 0;

	/*Initialze the Distance in CM*/
	uint32_t fl_ODO_Distance_CM_u32;
	uint8_t fl_PreCondition_Status_u8;

	fl_PreCondition_Status_u8 = Swc_Odometer_PreCondition();

	/* Check the Active flag status*/
	if ((g_ODO_ActiveFlag_u8 == (uint8_t)ODO_ACTIVATE) && (fl_PreCondition_Status_u8 == 1))
	{

		for(fl_loop_Idx_u8 = 0;fl_loop_Idx_u8 < ODO_TRIP_MAX; fl_loop_Idx_u8++)
		{
			/*Store the computed Trip Diatnce*/
			g_ODO_TripDistance_KM_u32[fl_loop_Idx_u8] = ODO_Compute_TripDistance(fl_loop_Idx_u8);
		}

        /*Check distance compute method with speed input*/
        #if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_SPEED)

			/*Store the speed value*/
			g_ODO_Speed_KMPH_u32 = Swc_Get_RAW_Speedo_Val();

			/*Store the distance from speed input*/
			fl_ODO_Distance_CM_u32 = (ODO_Convert_Speed_To_Distance(g_ODO_Speed_KMPH_u32));

			/*Comput the accumumated distance*/
			g_ODO_Accumulate_Distance_CM_u32 = g_ODO_Accumulate_Distance_CM_u32 + fl_ODO_Distance_CM_u32;
		#endif

		/*Check distance compute method with distance input*/
		#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_DISTANCE)

			/*Store the current distance */
			g_ODO_Current_Distance_CM_u8 = ODO_GET_DISTANCE_CM();

			/*Store the distance from delta distance*/
			fl_ODO_Distance_CM_u32 = ODO_Convert_Distance_To_DeltaDistance(g_ODO_Current_Distance_CM_u8);

			/*Store the accumulated distance*/
			g_ODO_Accumulate_Distance_CM_u32 = g_ODO_Accumulate_Distance_CM_u32 + fl_ODO_Distance_CM_u32;
		#endif

		/*Check distance compute method with frequency input*/
		#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_FREQUENCY)

			/*Store the current frequency */
			g_ODO_Frequecy_Hz_u32 = ODO_GET_FREQUENCY_HZ();

			/*Store distance from frequency*/
			fl_ODO_Distance_CM_u32 = ODO_Convert_Frequency_To_Distance(g_ODO_Frequecy_Hz_u32);

			/*Store the accumulated distance*/
			g_ODO_Accumulate_Distance_CM_u32 = g_ODO_Accumulate_Distance_CM_u32 + fl_ODO_Distance_CM_u32;
		#endif

		fl_Odo_CAN_TX_U32 = g_ODO_Distance_KM_u32/10;

		CanMgr_Write_odo_signal_0x321_s(fl_Odo_CAN_TX_U32);

		if(CAN_BUSOFF_INDICATION() == FALSE)
		{
			if(g_CAN_BUS_Off_Recovery_counter < 20)
			{
				g_CAN_BUS_Off_Recovery_counter = g_CAN_BUS_Off_Recovery_counter + 1;

			}
		}
	}

	/*Compute Encrypt data for the computed distance*/
	ODO_Compute_EncryptData();
}

/* API is used to clear the CAN bus recovery flag */
void Swc_Clear_CAN_BUS_RECOVERY_Flag(void)
{
	g_CAN_BUS_Off_Recovery_counter = 0;
}

/* API is used to clear the CAN bus off recovery flag */
uint8_t Swc_Get_CAN_BUS_OFF_Recovery_Counter(void)
{
	return (g_CAN_BUS_Off_Recovery_counter);
}
/*Check distance compute method with speed input*/
#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_SPEED)
/*
* @brief    This function is to convert the speed to distance
* @param    Speed in KMPH -fl_ODO_Speed_KMPH_u32
* @return   distance-fl_ODO_Distance_CM_u32
*/
static uint32_t ODO_Convert_Speed_To_Distance(uint32_t fl_ODO_Speed_KMPH_u32)
{
	/*Initialize the Distance */
	uint32_t fl_ODO_Distance_CM_u32 ;

	uint16_t fl_ODO_Distance_Remainder_u16;

	/*Compute distance from speed input*/
	fl_ODO_Distance_CM_u32 = (fl_ODO_Speed_KMPH_u32 * ODO_TIMETASK_MS) / ODO_KMPH_CMPMS_DIVIDE_FACTOR;

	fl_ODO_Distance_Remainder_u16 = (fl_ODO_Speed_KMPH_u32 * ODO_TIMETASK_MS) % ODO_KMPH_CMPMS_DIVIDE_FACTOR;

	g_ODO_Distance_Acc_Remainder_CM_u16 = g_ODO_Distance_Acc_Remainder_CM_u16 + fl_ODO_Distance_Remainder_u16;

	if( g_ODO_Distance_Acc_Remainder_CM_u16 >= ODO_KMPH_CMPMS_DIVIDE_FACTOR)
	{
		/*odo dostance*/
		fl_ODO_Distance_CM_u32 = fl_ODO_Distance_CM_u32 + 1;

		g_ODO_Distance_Acc_Remainder_CM_u16 = g_ODO_Distance_Acc_Remainder_CM_u16 % ODO_KMPH_CMPMS_DIVIDE_FACTOR;
	}
	/*return distnace*/
	return fl_ODO_Distance_CM_u32;
}
#endif

/*Check distance compute method with distance input*/
#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_DISTANCE)
/*
* @brief    This function is to convert the distance to deltadistance
* @param    Distance in CM -fl_ODO_Current_Distance_u32
* @return   Delta distance in CM-fl_ODO_Distance_CM_u32
*/
static uint32_t ODO_Convert_Distance_To_DeltaDistance(uint8_t fl_ODO_Current_Distance_CM_u8)
{
	/*Initialize the Distance*/
	uint8_t fl_ODO_Distance_CM_u32 = 0;

	/*Check current distance with previous distance*/
	if (fl_ODO_Current_Distance_CM_u8 < g_ODO_Previous_Distance_CM_u8)
	{

		/*Compute  Distance from Delta Distance*/
		fl_ODO_Distance_CM_u32 = (ODO_CAN_OVERFLOW_DISTANCE_VALUE - g_ODO_Previous_Distance_CM_u8) +
								 fl_ODO_Current_Distance_CM_u8;
	}
	else
	{
		/*Compute Distance from Delta Distance*/
		fl_ODO_Distance_CM_u32 = fl_ODO_Current_Distance_CM_u8 - g_ODO_Previous_Distance_CM_u8;
	}

	/*Store previous distance*/
	g_ODO_Previous_Distance_CM_u8 = fl_ODO_Current_Distance_CM_u8;

	/*return distance*/
	return fl_ODO_Distance_CM_u32;
}
#endif

/*Check distance compute method with frequency input*/
#if (ODO_DISTANCE_COMPUTE_METHOD == ODO_INPUT_METHOD_FREQUENCY)
/*
* @brief    This function is to convert the frequency  to distance
* @param    Frequency in Hz -fl_ODO_Frequency_u16
* @return   Distance in CM-fl_ODO_Distance_CM_u32
*/
static uint32_t ODO_Convert_Frequency_To_Distance(uint32_t fl_ODO_Frequency_u32)
{
	/*Initialize the loop index value*/
	uint32_t fl_loop_Index_u32 = 0;

	/*Initialize the RPM value*/
	uint32_t fl_ODO_RPM_u32 = 0;

	/*Initialize the distance value*/
	uint32_t fl_ODO_Distance_CM_u32 ;

	/*Initialize the Frequency Difference variable*/
	uint32_t fl_ODO_Freq_Diff_u32 = 0;

	/*Initialize the RPM Difference variable*/
	uint32_t fl_ODO_RPM_Diff_u32 = 0;

	/*Initialize the segment find variable*/
	uint32_t fl_ODO_Segment_u32 = 0;

	/*Check frequency with inital value of the frequency in the configuration table*/
	if (fl_ODO_Frequency_u32 < (uint32_t)ODO_Fr_RPM_Values[0][0])
	{
		/*Store the RPM value*/
		fl_ODO_RPM_u32 = (uint32_t)ODO_Fr_RPM_Values[0][1];
	}

	/*Check frequency with final value of the frequency in the configuration table*/
	else if (fl_ODO_Frequency_u32 > ODO_Fr_RPM_Values[ODO_MAX_FR_RPM_VALUES - (uint32_t)1][0])
	{
		/*Store the RPM value*/
		fl_ODO_RPM_u32 = (uint32_t)ODO_Fr_RPM_Values[ODO_MAX_FR_RPM_VALUES - (uint32_t)1][1];
	}

	else
	{
		/*Loop exectuion for max frequency values*/
		for (fl_loop_Index_u32 = 0; fl_loop_Index_u32 < (uint32_t)ODO_MAX_FR_RPM_VALUES; fl_loop_Index_u32++)
		{
			/*Check Frequency  in the configuration table*/
			if (fl_ODO_Frequency_u32 == (uint32_t)ODO_Fr_RPM_Values[fl_loop_Index_u32][0])
			{
				/*Store RPM values*/
				fl_ODO_RPM_u32 = (uint32_t)ODO_Fr_RPM_Values[fl_loop_Index_u32][1];
			}

			/*Check Frequency  in the configuration table*/
			else if (fl_loop_Index_u32 <= (ODO_MAX_FR_RPM_VALUES - (uint32_t)2))
			{
				/*Check frequency in the configuration table*/
				if ((fl_ODO_Frequency_u32 > (uint32_t)ODO_Fr_RPM_Values[fl_loop_Index_u32][0]) &&
					(fl_ODO_Frequency_u32 < (uint32_t)ODO_Fr_RPM_Values[fl_loop_Index_u32 + (uint32_t)1][0]))
				{

					/*Store the frequency difference*/
					fl_ODO_Freq_Diff_u32 = (uint32_t)(ODO_Fr_RPM_Values[fl_loop_Index_u32 + (uint32_t)1][0] -
											ODO_Fr_RPM_Values[fl_loop_Index_u32][0]);

					/*Store RPM difference*/
					fl_ODO_RPM_Diff_u32 = (uint32_t)(ODO_Fr_RPM_Values[fl_loop_Index_u32 + (uint32_t)1][1] -
										  ODO_Fr_RPM_Values[fl_loop_Index_u32][1]);

					/*Store the segment value for RPM*/
					fl_ODO_Segment_u32 = (uint32_t)(fl_ODO_RPM_Diff_u32 / fl_ODO_Freq_Diff_u32);

					/*Store RPM value*/
					fl_ODO_RPM_u32 = (uint32_t)(ODO_Fr_RPM_Values[fl_loop_Index_u32][1] + ((fl_ODO_Frequency_u32 -
									 ODO_Fr_RPM_Values[fl_loop_Index_u32][0]) * fl_ODO_Segment_u32));													
				}
			}
			else
			{
				/*do nothing*/
			}
		}
	}

	/*Store the Computed Distance value*/
	fl_ODO_Distance_CM_u32 = (fl_ODO_RPM_u32 * ODO_PI_VALUE * ODO_WHEEL_DIAMETER_CM) /
							 (ODO_TIMETASK_DIVIDE_FACTOR * ODO_MIN_SEC_CONV_FACTOR);

	/*return distance*/
	return fl_ODO_Distance_CM_u32;
}
#endif

/*
* @brief    This function is to compute the CRC
* @param    message pointer ,pointer length
* @return   CRC value
*/
static uint8_t ODO_Compute_CRC(const uint8_t *MsgPtr, uint32_t Ptr_Length)
{
	/*Initialize the CRC value*/
	uint8_t fl_crc_u8 = ODO_CRC_INIT_VALUE;

	/*Initialize the shift index value*/
	uint8_t fl_shiftindex_u8;

	/*Initialize the loop index value*/
	uint32_t fl_loopindex_u32;

	/*loop execution for CRC compute data*/
	for (fl_loopindex_u32 = (uint32_t)0; fl_loopindex_u32 < Ptr_Length; fl_loopindex_u32++)
	{
		/*Store the CRC value with xor of the message*/
		fl_crc_u8 = (fl_crc_u8 ^ MsgPtr[fl_loopindex_u32]);

		/*Loop execution for 8 bits*/
		for (fl_shiftindex_u8 = (uint8_t)0; fl_shiftindex_u8 < (uint8_t)8; ++fl_shiftindex_u8)
		{
			/* CRC value with zero*/
			if ((fl_crc_u8 & (uint8_t)0x80) != (uint8_t)0)
			{
				/*XOR with CRC polynomial*/
				fl_crc_u8 = ((fl_crc_u8 << (uint8_t)1) ^ ODO_CRC_POLYNOMIAL_VALUE);
			}
			else
			{
				/*CRC shift operation*/
				fl_crc_u8 = (fl_crc_u8 << (uint8_t)1);
			}
		}
	}
	
	/*retur CRC value*/
	return fl_crc_u8;
}

/*
* @brief    This function is to compute the Parity
* @param    Distance -fl_ODO_Distance_u32
* @return   Parity value-fl_ODO_Parity_u8
*/
static uint8_t ODO_Compute_Parity(uint32_t fl_ODO_Distance_u32)
{
	/*Initailize the Parity value*/
	uint8_t fl_ODO_Parity_u8 = 0u;

	/*Store the Value of the distance*/
	uint32_t fl_ODO_Dist_u32 = fl_ODO_Distance_u32;

	/*Check Distance value*/
	while (fl_ODO_Dist_u32 > (uint32_t)0)
	{
		/*Not operation of the parity*/
		fl_ODO_Parity_u8 = ~fl_ODO_Parity_u8;
		if (fl_ODO_Parity_u8 == (uint8_t)0xFF)
		{
			fl_ODO_Parity_u8 = 1;
		}
		else
		{
			fl_ODO_Parity_u8 = 0;
		}
		fl_ODO_Dist_u32 = fl_ODO_Dist_u32 & (fl_ODO_Dist_u32 - (uint32_t)1);
	}
	/*return parity*/
	return fl_ODO_Parity_u8;
}

/*
* @brief    This function is to compute EncrptData
* @param    NULL
* @return   NULL
*/
static void ODO_Compute_EncryptData(void)
{
	/*Initialize the distance*/
	uint32_t fl_ODO_Distance_KM_u32;

	/*Initialize the CRC*/
	uint32_t fl_ODO_CRC_u8;

	/*Initialize the parity*/
	uint8_t fl_ODO_Parity_u8 = 0;

	uint16_t fl_ODO_Distance_Remainder_KM_u32 = 0;

	/*Check accumulated distance with distance KM value*/
	if (g_ODO_Accumulate_Distance_CM_u32 >= ODO_KM_CM_CONV_FACTOR)
	{
		/*Store the distance*/
		fl_ODO_Distance_KM_u32 = (uint32_t)(g_ODO_Accumulate_Distance_CM_u32)/ ODO_KM_CM_CONV_FACTOR;

		fl_ODO_Distance_Remainder_KM_u32 = (uint32_t)(g_ODO_Accumulate_Distance_CM_u32)% ODO_KM_CM_CONV_FACTOR;

		/*Store the accumulated distance*/
		g_ODO_Distance_KM_u32 = g_ODO_Distance_KM_u32 + fl_ODO_Distance_KM_u32;

		/*Store the NVM Data in kilometer*/
		g_ODO_NVMData_u8 = g_ODO_NVMData_u8 + (uint8_t)1;

		/*Check the Odometer distance with max distance vaue*/
		if (g_ODO_Distance_KM_u32 > (uint32_t)ODO_MAX_DISTANCE_KM)
		{
			/*Store Odometer distance with zero value*/
			g_ODO_Distance_KM_u32 = (uint32_t)ODO_MAX_DISTANCE_KM;
		}
		/*Compute the distance write data */
		if (g_ODO_NVMData_u8 == ODO_DISTANCE_NVM_RESOLUTION)
		{
			 g_ODO_Distance_Write_Data_KM_u32 = g_ODO_Distance_KM_u32 / ODO_DISTANCE_NVM_RESOLUTION;

			/*Compute CRC*/
			fl_ODO_CRC_u8 = ODO_Compute_CRC((uint8_t *)&g_ODO_Distance_Write_Data_KM_u32, ODO_DISTANCE_DATA_SIZE);

			/*Compute Parity*/
			fl_ODO_Parity_u8 = ODO_Compute_Parity(g_ODO_Distance_Write_Data_KM_u32);

			/*Clear the NVM data in kilometer*/
			g_ODO_NVMData_u8 = 0;

			/*Store the NVM write data byte*/
			g_ODO_NVM_Write_data_u8[0] = (uint8_t)((g_ODO_Distance_Write_Data_KM_u32)>>16);

			/*Store the NVM write data byte*/
			g_ODO_NVM_Write_data_u8[1] = (uint8_t)((g_ODO_Distance_Write_Data_KM_u32 & 0xFF00)>>8);

			/*Store the NVM write data byte*/
			g_ODO_NVM_Write_data_u8[2] = (uint8_t)(g_ODO_Distance_Write_Data_KM_u32);

			/*Store the NVM write data byte*/
			g_ODO_NVM_Write_data_u8[3] = fl_ODO_Parity_u8;

			/*Store the NVM write data byte*/
			g_ODO_NVM_Write_data_u8[4] = (uint8_t)fl_ODO_CRC_u8;

			/*function call for store Encrypt data to NVM*/
			ODO_EncryptData_To_NVM();
		}

		/*Clear the Accumulate Distance*/
		g_ODO_Accumulate_Distance_CM_u32 = fl_ODO_Distance_Remainder_KM_u32;

		g_Get_AccumulateValue = 0;
	}
}

/*
* @brief    This function is to store the Encrypt data to NVM
* @param    NULL
* @return   NULL
*/
static void ODO_EncryptData_To_NVM(void)
{
	if (g_ODO_NVM_Block_Id_u32 == g_ODO_NVM_End_Block_Id_u32)
	{
		/*Store NVM start Block id*/
		g_ODO_NVM_Block_Id_u32 = ODO_NVM_START_BLOCK_ID;
	}
	

	NVM_Byte_Write_Allocation(g_ODO_NVM_Block_Id_u32,&g_ODO_NVM_Write_data_u8[0]);
	/*Store NVM block id*/
	g_ODO_NVM_Block_Id_u32 = g_ODO_NVM_Block_Id_u32 + (uint8_t)1;
}

/*
* @brief    This function is to get the highest value from NVM.
* @param    NVM distance data-fl_ODO_Distance_CM_u32
* @return   High value distance-g_ODO_NVM_Check_Data_u32
*/
static uint32_t ODO_Find_Highest_Odometer_Value(const uint32_t *fl_ODO_Distance_CM_u32)
{
	/*Initialize the loop index value*/
	uint32_t fl_loop_Index_u32;

	for (fl_loop_Index_u32 = (uint32_t)0; fl_loop_Index_u32 < (uint32_t)ODO_NVM_BLOCK_SIZE; fl_loop_Index_u32++)
	{
		/*Check with NVM start block id value*/
		if (fl_loop_Index_u32 == (uint32_t)0)
		{
			/*Store check value distance*/
			g_ODO_NVM_Check_Data_u32 = fl_ODO_Distance_CM_u32[fl_loop_Index_u32];
		}
		else
		{
			/*Check Distance to get highest value*/
			if (fl_ODO_Distance_CM_u32[fl_loop_Index_u32] > g_ODO_NVM_Check_Data_u32)
			{
				g_ODO_NVM_Check_Data_u32 = fl_ODO_Distance_CM_u32[fl_loop_Index_u32];
			}
		}
	}
	/*return the g_ODO_NVM_Check_Data_u32*/
	return g_ODO_NVM_Check_Data_u32;
}

/*
* @brief    This function is to validate the odometer value
* @param    NVM Id-fl_ODO_NVM_Block_Id_u32
* @return   Distance fl_ODO_Distance_u32
*/
static uint32_t ODO_Validate_Odometer_Value(uint32_t fl_ODO_NVM_Block_Id_u32)
{
	/*Initialize the Read data value*/
	uint8_t fl_ReadData_u8[5] = {0};

	/*Initialize the distance data*/
	uint32_t fl_ODO_Distance_Data_u32[ODO_DISTANCE_DATA_SIZE] = {0};

	/*Initialize the distance*/
    static uint32_t fl_ODO_Distance_u32=0;

	/* Initialize the loop index*/
	uint8_t fl_loop_Index_u8;

	/*Initialize the parity vaue*/
	uint8_t fl_ODO_Parity_u8 ;

	/*Initialize the CRC va;ue*/
	uint8_t fl_ODO_CRC_u8;

	/*store the vlaid data*/
	uint32_t fl_ODO_ValidData_u32 = 0;

	/*Store NVM data*/
	static uint8_t data_rd[16] = {0};
	
	static uint8_t arr[5] = {0};

 	/*Read Odometer distance from NVM*/
	ODO_NVM_READ_DATA(fl_ODO_NVM_Block_Id_u32, &data_rd[0]);

	arr[0] = data_rd[2];
	arr[1] = data_rd[1];
	arr[2] = data_rd[0];
	arr[3] = data_rd[3];  /* Parity byte*/
	arr[4] = data_rd[4];  /* CRC DATA*/

	/*loop execution for NVM bytes storage*/
	for (fl_loop_Index_u8 = 0; fl_loop_Index_u8 < (uint8_t)5 ; fl_loop_Index_u8++)
	{
		/*data pointer for read data*/
		fl_ReadData_u8[fl_loop_Index_u8] = arr[fl_loop_Index_u8];
	}

	/*Store the distance*/
	fl_ODO_Distance_u32 = ((fl_ReadData_u8[2] << 16) | (fl_ReadData_u8[1] << 8) |( fl_ReadData_u8[0]));
	
	/* calculate CRC for odo readed from NVM*/
	fl_ODO_CRC_u8 = ODO_Compute_CRC((uint8_t *)&fl_ODO_Distance_u32, ODO_DISTANCE_DATA_SIZE);

	/* Compute Parity */
	fl_ODO_Parity_u8 = ODO_Compute_Parity(fl_ODO_Distance_u32);

	/* check - valid data condition As Calculated CRC and parity should match with NVM Read data*/
	if( ( fl_ODO_CRC_u8 == fl_ReadData_u8[4]) && ( fl_ODO_Parity_u8 == fl_ReadData_u8[3]))
	{
		/* Data is valid */
		fl_ODO_ValidData_u32 = fl_ODO_Distance_u32;

		/* Increament the good samples count */
		g_ODO_Init_Valid_Data_Counter_u8 = g_ODO_Init_Valid_Data_Counter_u8 + 1;
	}
	else
	{
		/* Data is invalid */
		fl_ODO_ValidData_u32 = (uint32_t)0;
	}

	/*return distance*/
	return fl_ODO_ValidData_u32;
}

/*
* @brief    This function is to store distance when trip is reset.
* @param    Trip_Id
* @return   Trip Distance-fl_ODO_TripDistance[Trip_Id]
*/
void ODO_TripSwitch_Reset(uint8_t fl_ODO_Trip_Index_u8)
{
	/*Initialize the Trip NVM block id*/
	uint32_t fl_ODO_Trip_NVM_Block_Id_u32 ;
	uint8_t fl_ODO_NVM_Write_data_u8[3];

	/*Store the NVM block id*/
	fl_ODO_Trip_NVM_Block_Id_u32 = ODO_TRIP_NVM_BLOCK_ID + fl_ODO_Trip_Index_u8;
	
	/*Store the NVM write data byte*/
	fl_ODO_NVM_Write_data_u8[0] = (uint8_t)((g_ODO_Distance_KM_u32 >> 16) & 0xFF);

	/*Store the NVM write data byte*/
	fl_ODO_NVM_Write_data_u8[1] = (uint8_t)((g_ODO_Distance_KM_u32 >> 8) & 0xFF);

	/*Store the NVM write data byte*/
	fl_ODO_NVM_Write_data_u8[2] = (uint8_t)(g_ODO_Distance_KM_u32 & 0xFF);

	/*Store Diatance in NVM when Trip is reset*/
	ODO_NVM_WRITE_DATA(fl_ODO_Trip_NVM_Block_Id_u32 , &fl_ODO_NVM_Write_data_u8[0]);

	g_ODO_Distance_TripReset[fl_ODO_Trip_Index_u8] = g_ODO_Distance_KM_u32;

	g_Trip_ODO_Cm_Var[fl_ODO_Trip_Index_u8] = g_ODO_Accumulate_Distance_CM_u32;
}

/*
* @brief    This function is to compute the Trip Distance
* @param    Trip_Id
* @return   Trip Distance-fl_ODO_TripDistance[Trip_Id]
*/
static uint32_t ODO_Compute_TripDistance(uint8_t Trip_Id)
{
	uint32_t fl_ODO_TripDistance[2];
	int16_t fl_ODO_Trip_Var;

	/* Max trip odo value is 999.9km , it will reset when reaches MAX VALUE */
	if((g_ODO_Distance_KM_u32 - g_ODO_Distance_TripReset[Trip_Id]) > TRIP_ODO_MAX_DISTANCE)
	{
		ODO_TripSwitch_Reset(Trip_Id);
	}

	fl_ODO_Trip_Var = g_ODO_Accumulate_Distance_CM_u32 - g_Trip_ODO_Cm_Var[Trip_Id];
	
	/*Compute Trip Distance*/
	fl_ODO_TripDistance[Trip_Id] = (((g_ODO_Distance_KM_u32 - g_ODO_Distance_TripReset[Trip_Id]) * 10000) + 
									(fl_ODO_Trip_Var / 10))/10000;

	/*Return Trip Distance*/
	return fl_ODO_TripDistance[Trip_Id];
}

/*
* @brief    This function is to get the trip distance.
* @param    Trip_Id
* @return   Trip Distance-fl_ODO_TripDistance[Trip_Id]
*/
uint32_t ODO_Get_TripOdometer(uint8_t Trip_Id)
{
	uint32_t fl_Trip_Odo_Val_u32 = 0;

	/* NVM Data are good to process*/
	if(g_ODO_NVM_Error_Status_bl == FALSE)
	{
		/*Get current Trip Distance*/
		fl_Trip_Odo_Val_u32 = g_ODO_TripDistance_KM_u32[Trip_Id];
	}
	else
	{
		/* ODO NVM DATA'S ARE CORRUPTED */
		fl_Trip_Odo_Val_u32 = ODO_INVALID_STATE;
	}

	/* Return trip odo distance */
	return (fl_Trip_Odo_Val_u32);
}

/*
* @brief    This function is to get the  distance.
* @param    NULL
* @return   g_ODO_Distance_KM_u32
*/
uint32_t ODO_Get_Odometer(void)
{
	/*Return the ODO_Distance*/
	return (g_ODO_Distance_KM_u32);
}

/* API is used to get the trip distance  */
uint8_t Swc_Odometer_PreCondition(void)
{
   uint8_t fl_Ign_Position_u8;

   uint8_t fl_Odo_LVSD_check_u8;

   uint8_t fl_Odo_HVSD_check_u8;

	bool fl_Precondition_Status;
 
   fl_Ign_Position_u8 = Sys_Service_Get_Ignition_State();

   fl_Odo_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

   fl_Odo_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

	/* Preconditin check*/
	if((fl_Ign_Position_u8 == IGN_OFF)  || (fl_Odo_HVSD_check_u8 == 0) ||
	(fl_Odo_HVSD_check_u8 == 0) || (g_ODO_NVM_Error_Status_bl == TRUE))
	{
		/* Condition not ok to execute Main function*/
		fl_Precondition_Status = FALSE;
	}
	else
	{
		/* Condition ok to execute Main function*/
		fl_Precondition_Status = TRUE;
	}

	/* Preconditon status return*/
	return (fl_Precondition_Status);
}

/* API is used to display the odo value  */
uint32_t Swc_Get_Display_ODO_Value(void)
{
	uint32_t fl_displayable_Odo_Value_u32;
	uint32_t fl_Selected_Odo_Value_u32 = Distance_fn();

	/* NVM Data are good to process*/
	if(g_ODO_NVM_Error_Status_bl == FALSE)
	{
		/* return display odo value in 1km resolution */
		if (fl_Selected_Odo_Value_u32 == 0)
		{
			fl_displayable_Odo_Value_u32 = (g_ODO_Distance_KM_u32)/10;
		}
		else
		{
			fl_displayable_Odo_Value_u32 = (g_ODO_Distance_KM_u32 / 16);
		}
	}
	else
	{
		/* ODO NVM DATA'S ARE CORRUPTED */
		fl_displayable_Odo_Value_u32 = ODO_INVALID_STATE;

	}	
	return (fl_displayable_Odo_Value_u32);
}

/* API is used to get the trip distance  */
uint32_t IFE_ODO_value(void)
{
	return (g_ODO_Accumulate_Distance_CM_u32);
}

/* API is used to get the trip distance  */
void Swc_Odo_CM_NVM_Write(void)
{
	uint16_t fl_index_array_u16[3];

	bool  fl_NVM_Status_bl = TRUE;
	
	fl_NVM_Status_bl = Swc_Get_NVM_Status();

	if(fl_NVM_Status_bl == FALSE)
	{
	
	  Swc_TripOdo_CM_NVM_Write();

	}  

	fl_index_array_u16[0] = g_ODO_Accumulate_Distance_CM_u32;
	fl_index_array_u16[1] = g_Trip_ODO_Cm_Var[0];
	fl_index_array_u16[2] = g_Trip_ODO_Cm_Var[1];

	fl_NVM_Status_bl = Swc_Get_NVM_Status();

	if(fl_NVM_Status_bl == FALSE)
	{
		NVM_Byte_Write_Allocation(NVM_ODO_CENTIMETER_AND_TRIp_ODO_RESET_DISTANCE_CM_RESOLUTION_DATA,(uint8_t*)&fl_index_array_u16[0]);

	}

}

/* API is used to get the trip distance  */
void Swc_Odo_CM_NVM_Read(void)
{
	uint16_t fl_index_array_u16[3];
	
	NVM_Byte_Read_Allocation(NVM_ODO_CENTIMETER_AND_TRIp_ODO_RESET_DISTANCE_CM_RESOLUTION_DATA,(uint8_t*)&fl_index_array_u16[0]);

	g_ODO_Accumulate_Distance_CM_u32 = fl_index_array_u16[0];
	g_Trip_ODO_Cm_Var[0] = fl_index_array_u16[1];
	g_Trip_ODO_Cm_Var[1] = fl_index_array_u16[2];

	Swc_TripOdo_CM_NVM_Read();
}

void Swc_TripOdo_CM_NVM_Write(void)
{
	uint32_t fl_index_array_u32[4];
	
	g_TripOdo_Reset_Value_u64[0] = AVS_Accu_Value(0);
	g_TripOdo_Reset_Value_u64[1] = AVS_Accu_Value(1);

	fl_index_array_u32[0] = g_TripOdo_Reset_Value_u64[0] >> 32;
	fl_index_array_u32[1] = g_TripOdo_Reset_Value_u64[0];

	fl_index_array_u32[2] = g_TripOdo_Reset_Value_u64[1] >> 32;
	fl_index_array_u32[3] = g_TripOdo_Reset_Value_u64[1];

	NVM_Byte_Write_Allocation(NVM_AVEREGE_SPEED_TRIP_CM_ACC,(uint8_t*)&fl_index_array_u32[0]);
}


void Swc_TripOdo_CM_NVM_Read(void)
{
	uint32_t fl_index_array_u32[4];

	NVM_Byte_Read_Allocation(NVM_AVEREGE_SPEED_TRIP_CM_ACC,(uint8_t*)&fl_index_array_u32[0]);

	g_TripOdo_Reset_Value_u64[0] = ((uint64_t)fl_index_array_u32[0] << 32) | ((uint64_t)fl_index_array_u32[1]);
	
	g_TripOdo_Reset_Value_u64[1] = ((uint64_t)fl_index_array_u32[2] << 32) | ((uint64_t)fl_index_array_u32[3]);
}

/* API is used to get the trip distance  */
uint64_t TripOdo_Acc_value(uint8_t trip_id)
{
	return g_TripOdo_Reset_Value_u64[trip_id];
}

bool Swc_Get_ODO_NVM_Error_Status(void)
{
	bool fl_Ret_Status_bl = FALSE;

	/* Check nvm error status */
	if(g_ODO_NVM_Error_Status_bl == TRUE)
	{
		fl_Ret_Status_bl = TRUE;
	}
	else
	{
		/* NVM data is good*/
		fl_Ret_Status_bl = FALSE;
	}

	/* Return nvm error status*/
	return (fl_Ret_Status_bl);
}

/**********************************************************************************************************************/
/*                                              E N D   O F   S O F T W A R E                                         */
/**********************************************************************************************************************/


/**********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y                                       
 **********************************************************************************************************************/
/**********************************************************************************************************************
REVISION NUMBER      : V1.0.0
REVISION DATE        : 30-April-2021
CREATED / REVISED BY : Maheswari R(maheswari@niyatainfotech.com)
DESCRIPTION          : Initial Version

REVISION NUMBER      : V1.0.1
REVISION DATE        : 26-May-2021
CREATED / REVISED BY : Maheswari R(maheswari@niyatainfotech.com)
DESCRIPTION          : Peer Review comments fixed

REVISION NUMBER      : V1.0.2
REVISION DATE        : 11-Dec-2022
CREATED / REVISED BY : Palani kumar R(palanikumar@niyatainfotech.com)
DESCRIPTION          : CRC and Parity check in Init sequence added
------------------------------------------------------------------------------------------------------------------------

**********************************************************************************************************************/
#endif /* ! ODO_C */
