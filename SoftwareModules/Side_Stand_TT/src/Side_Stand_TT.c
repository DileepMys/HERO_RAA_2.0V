/* @file FILE NAME */
#ifndef SIDE_STAND_TT_C
#define SIDE_STAND_TT_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Rubina Josphine  (rubinajosphine@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : Side_Stand_TT.c
 *  Version                         : v1.0.0
 *  Micros supported                : Micro independent
 *  Compilers supported             : J link
 *  Platforms supported             : Platform Independent
 *  Description                     : This file consists of definitions of side stand telltale
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

/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                     
***********************************************************************************************************************/
#include "Side_Stand_TT.h"
#include "Side_Stand_TT_Cfg.h"
#include "fsl_lpadc.h"
#include "fsl_gpio.h"
#include "mpu_wrappers.h"
#include "Cmp_Tasks.h"
#include "CanMgr_cfg.h"
#include "TTMgr.h"

/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to preserve the Pre-Condition
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: TRUE/FALSE
 * @Applicability: Yes
 */
bool g_Pre_condition_Status_bool;

/*
 * @brief: This variable is used to preserve the Sampling Status
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: TRUE/FALSE
 * @Applicability: Yes
 */
bool g_SS_TT_ADC_Sampling_Is_Done_Bool;

/*
 * @brief: This variable is used to read the ignition status of the system
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability: 
 */

uint8_t g_Read_IGN_Status_u8;

/*
 * @brief: This variable is used to store the Side stand TT status
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
uint8_t g_SS_TT_Displayable_Value_u8;


/*
 * @brief: This variable is used to store the previous side stand displayable value
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
uint8_t g_SS_TT_Prev_Displayable_Value_u8;


/*
 * @brief: This variable is used to store the Delay counter of the first sample
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
uint8_t g_SS_TT_First_Sample_Delay_Counter_u8;

/*
 * @brief: This variable is used to get the Side stand TT fault value from CAN
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
uint8_t g_SS_TT_fault_value_u8;


/*
 * @brief: This variable is used to get the Side stand TT value from CAN
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
uint8_t g_SS_TT_value_u8;


/*
 * @brief: This variable is used to get the Side stand TT status
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
uint8_t g_SS_TT_status_value_u8;


/*
 * @brief: This variable is used to get the Side stand TT error status
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
uint8_t g_SS_TT_error_status_value_u8;

/*
 * @brief: This variable is used to get the missing status of telltale
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */

bool g_SS_Telltale_Missing_Status_bool;


/*
 * @brief: This variable is used to get the missing status of telltale
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */

bool g_SS_Telltale_Missing_Status_CRC_cbk_bool;

/*
 * @brief: This variable is used to get the missing status of telltale
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */


bool g_SS_Telltale_Missing_Status_CRC_Error_bool;
/*
 * @brief: This variable is used to get the missing status of telltale
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */


bool g_SS_Telltale_Missing_Status_Alive_cntr_cbk_bool;


/*
 * @brief: This variable is used to get the missing status of telltale
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */

bool g_SS_Telltale_Missing_Status_Alive_cntr_Error_cbk_bool;


/*
 * @brief: This variable is used to get the CRC value
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
uint8_t g_SS_TT_CRC_u8;

/*
 * @brief: This variable is used to read the ADC value for side stand feed back
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
uint32_t g_SS_TT_ADCResult_u32 = 0;

/*
 * @brief: This variable is used to get the ADC sample index
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
uint8_t g_SS_TT_ADC_Sample_Index_u8 = 0;

/*
 * @brief: This variable is used to store the sample ADC result
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
uint32_t g_SS_TT_Sample_ADCResult_u32;

/*
 * @brief: This variable is used to store the sample ADC result
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
const uint32_t g_ss_tt_LpadcResultShift = 3U;

/*
 * @brief: This variable is used to store the sample ADC result
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
lpadc_conv_result_t ss_tt_mLpadcResultConfigStruct;

/*
 * @brief: This variable is used to store the sample ADC result
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
float64 g_TT_value_f64;

/*
 * @brief: This variable is used to store the sample ADC result
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
float64 g_TT_fault_value_f64;

/*
 * @brief: This variable is used to store the sample ADC result
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
uint16_t g_SS_ACCU_RAD_Count_u16;

/*
 * @brief: This variable is used to store the sample ADC result
 * @Unit:  nil
 * @Resolution: nil
 * @Range: nil
 * @Applicability:  
 */
uint16_t g_SS_TT_Mov_Avg_Sample_u16[SIDESTAND_SAMPLE_INDEX] = {0,0,0,0,0,0};
/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    This function processes the pre-condition to check the LVSD and HVSD status
 * @param    void
 * @return   bool - g_Pre_condition_Status_bool- status 
 */
static bool Side_Stand_TT_Pre_Condition(void);

#if ENABLE_SS_CRC
/*
 * @brief    This function processes the side stand Telltale CRC
 * @param    void
 * @return   uint8_t
 */
static uint8_t Side_Stand_TT_CRC_Check(void);
#endif

/*
 * @brief    This function processes the Adc Value and checking the Side stand Telltale to short and open condition
 * @param    void
 * @return   void
 */
static void Get_Acc_Value(void);

/*
* @brief            This function processes the side stand feedback and this is the periodic fucntion
* @param            void
* @return           void
* @invocation 
*/
static void SS_ADC_Get_Value(void);




/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/

/*
* @brief            This function processes the intialization of Side stand Telltale
* @param            void
* @return           void
* @invocation 
*/
void Side_Stand_TT_init(void)
{
    g_SS_TT_Displayable_Value_u8 = Side_Stand_TT_OFF;

    g_SS_TT_Prev_Displayable_Value_u8 = Side_Stand_TT_OFF;

    g_SS_TT_fault_value_u8 = 0;

    g_SS_TT_value_u8 = 0;

    g_SS_TT_error_status_value_u8 = NO_ERROR;

    g_SS_Telltale_Missing_Status_bool = TRUE;

    g_SS_Telltale_Missing_Status_CRC_cbk_bool =FALSE;

   

    g_SS_Telltale_Missing_Status_Alive_cntr_cbk_bool=FALSE;

   

    g_SS_TT_ADC_Sampling_Is_Done_Bool = FALSE;

    g_SS_TT_First_Sample_Delay_Counter_u8 = 0;     
}

/*
* @brief            This function processes the De-intialization of Side stand Telltale
* @param            void
* @return           void
* @invocation 
*/
void Side_Stand_TT_Deinit(void)
{
    /*Do Nothing*/
}

/*
* @brief            This function processes the Side Stand Telltale and this the periodic function
* @param            void
* @return           void
* @invocation 
*/
void Side_Stand_TT_Main_Function(void)
{
	

    uint8_t fl_Check_Busoff_u8;

    bool Side_Stand_TT_Pre_Condition_St = FALSE;
#if ENABLE_SS_CRC
    /* For securtiy check Need to Implement */
   g_SS_TT_CRC_u8 = Side_Stand_TT_CRC_Check();
#endif

    (void) CanMgr_Read_side_stand_sensor_fault_0x131_s(&g_TT_fault_value_f64);

    (void) CanMgr_Read_side_stand_sensor_0x131_s(&g_TT_value_f64);   


    Side_Stand_TT_Pre_Condition_St = Side_Stand_TT_Pre_Condition();
    
    /*Check if the precondition is true or false*/
    if(Side_Stand_TT_Pre_Condition_St == TRUE)
    {
        fl_Check_Busoff_u8 = App_Can_bus_off_Get_indication();

        /*If the precondition is true check the CAN bus OFF status and the CAN timeout missing status*/
        if((fl_Check_Busoff_u8 == FALSE) && (FALSE == g_SS_Telltale_Missing_Status_bool)&&
        (FALSE ==g_SS_Telltale_Missing_Status_CRC_cbk_bool) &&
        (FALSE==g_SS_Telltale_Missing_Status_Alive_cntr_cbk_bool))
        {
            
            /*To read the side sensor fault value through CAN*/       
        
            if((g_TT_fault_value_f64 != FALSE) || (g_TT_value_f64 != FALSE))
            {
            /*If falut value is true needs to blink the telltale*/
            g_SS_TT_Displayable_Value_u8 = Side_Stand_TT_ON;

            g_SS_TT_status_value_u8 = IC_SS_TELL_TELL_ON;

            }
            else
            {
                g_SS_TT_Displayable_Value_u8 = Side_Stand_TT_OFF;
                g_SS_TT_status_value_u8 = IC_SS_TELL_TELL_OFF;
            }
           
            
        }
        
       else
        {
            g_SS_TT_Displayable_Value_u8 = Side_Stand_TT_ON;

            g_SS_TT_status_value_u8 = IC_SS_TELL_TELL_ON;

        }
    }
    else
    {
        g_SS_TT_Displayable_Value_u8 = Side_Stand_TT_OFF;

        g_SS_TT_status_value_u8 = IC_SS_TELL_TELL_OFF;
    }

    CanMgr_Write_ic_ss_tell_tell_status_0x321_s(g_SS_TT_Displayable_Value_u8);

    TT_Mgr_Command( 1,  g_SS_TT_status_value_u8);

    /* Sense the change in Telltale status */
    if (g_SS_TT_Displayable_Value_u8 != g_SS_TT_Prev_Displayable_Value_u8)
    {
         
       g_SS_TT_ADC_Sample_Index_u8 = 0;

       g_SS_TT_First_Sample_Delay_Counter_u8 = 5;

       g_SS_TT_Prev_Displayable_Value_u8 = g_SS_TT_Displayable_Value_u8;
    }

        if (g_SS_TT_First_Sample_Delay_Counter_u8 != 0)
        {
          

            g_SS_TT_First_Sample_Delay_Counter_u8--;
        }
        else
        {
              
        /* Handle the feedback */
        Side_Stand_TT_Feedback();
        }
}

/*
 * @brief    This function processes the pre-condition to check the LVSD and HVSD status
 * @param    void
 * @return   bool - g_Pre_condition_Status_bool- status 
 */
bool Side_Stand_TT_Pre_Condition(void)
{
   uint8_t fl_Ign_Position_u8 = 0;
   uint8_t fl_Side_Stand_TT_LVSD_check_u8;
   uint8_t fl_Side_Stand_TT_HVSD_check_u8;
 
   fl_Ign_Position_u8 = Sys_Service_Get_Ignition_State();

   fl_Side_Stand_TT_LVSD_check_u8 = Sys_Service_Get_Low_Voltage_State();

   fl_Side_Stand_TT_HVSD_check_u8 = Sys_Service_Get_High_Voltage_State();

  if((fl_Ign_Position_u8 == IGN_OFF)  || (fl_Side_Stand_TT_LVSD_check_u8 == 0) ||
      (fl_Side_Stand_TT_HVSD_check_u8 == 0))
  {
	  g_Pre_condition_Status_bool = FALSE;
  }
  else
  {
	  g_Pre_condition_Status_bool = TRUE;
  }

  return g_Pre_condition_Status_bool;
}


/*
 * @brief    This function processes the it is used for future purpose
 * @param    void
 * @return   uint8_t
 */
#if ENABLE_SS_CRC
uint8_t Side_Stand_TT_CRC_Check(void)
{
    /* For securtiy check Need to Implement */
}
#endif

/*
* @brief            This function processes the side stand feedback and this is the periodic fucntion
* @param            void
* @return           void
* @invocation 
*/
void Side_Stand_TT_Feedback(void)
{

    SS_ADC_Get_Value();
}

/*
 * @brief    This function processes the Adc Value and checking the Side stand Telltale to short and open condition
 * @param    void
 * @return   void
 */
void Get_Acc_Value(void)
{
    if (g_SS_TT_ADC_Sample_Index_u8 >= 6)
    {
        /* Move the data for every sample */
        g_SS_TT_Mov_Avg_Sample_u16[0] = g_SS_TT_Mov_Avg_Sample_u16[1];
        g_SS_TT_Mov_Avg_Sample_u16[1] = g_SS_TT_Mov_Avg_Sample_u16[2];
        g_SS_TT_Mov_Avg_Sample_u16[2] = g_SS_TT_Mov_Avg_Sample_u16[3];
        g_SS_TT_Mov_Avg_Sample_u16[3] = g_SS_TT_Mov_Avg_Sample_u16[4];
        g_SS_TT_Mov_Avg_Sample_u16[4] = g_SS_TT_Mov_Avg_Sample_u16[5];

        g_SS_TT_Mov_Avg_Sample_u16[5] = g_SS_TT_ADCResult_u32;

        g_SS_TT_Sample_ADCResult_u32 = g_SS_TT_Mov_Avg_Sample_u16[0] +
                                    g_SS_TT_Mov_Avg_Sample_u16[1] +
                                    g_SS_TT_Mov_Avg_Sample_u16[2] +
                                    g_SS_TT_Mov_Avg_Sample_u16[3] +
                                    g_SS_TT_Mov_Avg_Sample_u16[4] +
                                    g_SS_TT_Mov_Avg_Sample_u16[5];
    
        g_SS_TT_Sample_ADCResult_u32 = g_SS_TT_Sample_ADCResult_u32 / 6;    

        g_SS_TT_ADC_Sample_Index_u8 = 0;

        g_SS_TT_ADC_Sampling_Is_Done_Bool = TRUE;
    }
    else
    {
    	g_SS_TT_Mov_Avg_Sample_u16[g_SS_TT_ADC_Sample_Index_u8] = g_SS_TT_ADCResult_u32;

    	g_SS_TT_ADC_Sample_Index_u8++;

        g_SS_TT_ADC_Sampling_Is_Done_Bool = FALSE;
    }

    if (g_SS_TT_ADC_Sampling_Is_Done_Bool != FALSE)
    {
        if(g_SS_TT_Displayable_Value_u8 == Side_Stand_TT_ON)
        {

            if(g_SS_TT_Sample_ADCResult_u32 >= 900)
            {
                /*LED Open Circuit*/
                g_SS_TT_error_status_value_u8 = LED_OPEN;
            }
            else if((g_SS_TT_Sample_ADCResult_u32 >= 418) && (g_SS_TT_Sample_ADCResult_u32 <= 776))
            {
                /*LED ON Normal Operation*/
                g_SS_TT_error_status_value_u8 = NO_ERROR;
            }
            else if(g_SS_TT_Sample_ADCResult_u32 <= 108)
            {
                /*LED Short*/
                g_SS_TT_error_status_value_u8 = LED_SHORT;

            }
            else if(g_SS_TT_Sample_ADCResult_u32 == 0)
            {
                g_SS_TT_error_status_value_u8 = COMMON_ERROR;
            }
            else
            {

            }
        }
        else if(g_SS_TT_Displayable_Value_u8 == Side_Stand_TT_OFF)
        {
            if(g_SS_TT_Sample_ADCResult_u32 >= 900)
            {
                /*LED OFF Normal Condition*/
                g_SS_TT_error_status_value_u8 = NO_ERROR;
            }
            else if(g_SS_TT_Sample_ADCResult_u32 >= 418)
            {
                /*LED Short circuit*/
                g_SS_TT_error_status_value_u8 = LED_SHORT;
            }
            else if(g_SS_TT_Sample_ADCResult_u32 == 0)
            {
                g_SS_TT_error_status_value_u8 = COMMON_ERROR;
            }
            else
            {

            }
        }
       
    }
     CanMgr_Write_ic_ss_tell_tell_error_0x321_s(g_SS_TT_error_status_value_u8);

}

/*
 * @brief           This function processes the Intialization of Adc configuration
 * @param           void 
 * @return          void
 */
void SS_TT_ADC_Config_Init(void)
{
	lpadc_config_t mLpadcConfigStruct;
	lpadc_conv_trigger_config_t mLpadcTriggerConfigStruct;
	lpadc_conv_command_config_t mLpadcCommandConfigStruct;

	LPADC_GetDefaultConvCommandConfig(&mLpadcCommandConfigStruct);

	mLpadcCommandConfigStruct.channelNumber = 0;

    mLpadcCommandConfigStruct.sampleChannelMode = kLPADC_SampleChannelSingleEndSideA;

	LPADC_SetConvCommandConfig(SIDESTAND_LPADC_BASE, 1U, &mLpadcCommandConfigStruct);
	LPADC_GetDefaultConvTriggerConfig(&mLpadcTriggerConfigStruct);

	mLpadcTriggerConfigStruct.targetCommandId = 1U;

	mLpadcTriggerConfigStruct.enableHardwareTrigger = false;

	LPADC_SetConvTriggerConfig(SIDESTAND_LPADC_BASE, 1U, &mLpadcTriggerConfigStruct);
}

/*
* @brief            This function processes the side stand feedback and this is the periodic fucntion
* @param            void
* @return           void
* @invocation 
*/
void SS_ADC_Get_Value(void)
{
    uint32_t Convertion_Value = 0;

    LPADC_DoSoftwareTrigger(SIDESTAND_LPADC_BASE, 2U);

    while (!LPADC_GetConvResult(SIDESTAND_LPADC_BASE, &ss_tt_mLpadcResultConfigStruct));

    Convertion_Value = ((ss_tt_mLpadcResultConfigStruct.convValue) >> g_ss_tt_LpadcResultShift);

    /* Converts the 12bit to 10bit Adc */
    g_SS_TT_ADCResult_u32 = Convertion_Value / 4;

    Get_Acc_Value();

    
}

/*
 * @brief    This function processes the Canmgr side stand telltale timeout callback
 * @param    
 * @return   
 */
void CanMgr_SideStand_Telltale_Timeout_Callback_0x131(void)
{
	CanMgr_SideStand_Telltale_Timeout_Cbk();
}

/*
* @brief            This function processes the Can Message Missing TimeOut callback which invokes when the message is missing
* @param            void       
* @return           void
* @invocation 
*/
void CanMgr_SideStand_Telltale_Timeout_Cbk(void)
{
	g_SS_Telltale_Missing_Status_bool = TRUE;
}

/*
* @brief            This function processes the Can Message reception callback which invokes when the message is received
* @param            void
* @return           void
* @invocation 
*/
void CanMgr_SideStand_Telltale_reception_cbk(void)
{

	g_SS_Telltale_Missing_Status_bool = FALSE;
}


/*
 * @brief    This function processes the side stand sensor fault timeout callback
 * @param    
 * @return   
 */
void CanMgr_SideStand_Sensor_Fault_Timeout_Callback_0x131(void)
{
	CanMgr_SideStand_Sensor_Fault_Timeout_Cbk();
}

/*
* @brief            This function processes the Can Message Missing TimeOut callback which invokes when the message is missing
* @param            void       
* @return           void
* @invocation 
*/
void CanMgr_SideStand_Sensor_Fault_Timeout_Cbk(void)
{
	g_SS_Telltale_Missing_Status_bool = TRUE;
}

/*
* @brief            This function processes the Can Message reception callback which invokes when the message is received
* @param            void
* @return           void
* @invocation 
*/
void CanMgr_SideStand_Sensor_Fault_reception_cbk(void)
{

	g_SS_Telltale_Missing_Status_bool = FALSE;
}

/*
* @brief            This function processes the  Checksum error recovery indication callback which invokes when the message is received
* @param            void
* @return           void  
* @invocation 
*/
void canMgr_SideStand_Sensor_CRC_recovery_indication_callback(uint8_t msgId,uint8_t UserId)
{
   g_SS_Telltale_Missing_Status_CRC_cbk_bool = FALSE;
}


/*
* @brief            This function processes the CRC Error Message Missing TimeOut callback which invokes when the message is missing
* @param            void       
* @return           void
* @invocation 
*/

void canMgr_SideStand_Sensor_CRC_ERROR_indication_callback(uint8_t msgId,uint8_t UserId)
{

  g_SS_Telltale_Missing_Status_CRC_cbk_bool =TRUE;

}

/*
* @brief            This function processes the  Alive Counter recovery indication callback which invokes when the message is received
* @param            void
* @return           void  
* @invocation 
*/
void canMgr_SideStand_Sensor_Alive_Counter_recovery_indication_callback(uint8_t msgId,uint8_t UserId)
{
   g_SS_Telltale_Missing_Status_Alive_cntr_cbk_bool = FALSE;
}

/*
* @brief            This function processes the CRC Error Message Missing TimeOut callback which invokes when the message is missing
* @param            void       
* @return           void
* @invocation 
*/
void canMgr_SideStand_Sensor_Alive_Counter_Error_recovery_indication_callback(uint8_t msgId,uint8_t UserId)
{
    g_SS_Telltale_Missing_Status_Alive_cntr_cbk_bool = TRUE;
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
    REVISION NUMBER      : v1.0.0                          
    REVISION DATE        : July/01/2022        
    CREATED / REVISED BY : Rubina Josphine (rubinajosphine@niyatainfotech.com)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

    REVISION NUMBER      : v1.0.0                          
    REVISION DATE        : July/02/2022        
    CREATED / REVISED BY : Balaji Pandurangan (balaji.pandurangan@niyatainfotech.com)      
    DESCRIPTION          : Updated Trigger value and software Trigger      
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------

    REVISION NUMBER      : v1.0.0                          
    REVISION DATE        : Jan/17/2023       
    CREATED / REVISED BY : Yuvaraj (yuvaraj@niyatainfotech.com)      
    DESCRIPTION          : Updated CRC and Alive counter call back functions     
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! Side_Stand_TT.c */
