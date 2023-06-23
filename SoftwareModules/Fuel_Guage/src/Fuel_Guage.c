/* @file FILE NAME */
#ifndef FUEL_GUAGE_C
#define FUEL_GUAGE_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Palani kumar (palanikumar@niyatainfotech.com) 
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : Fuel_Guage.c
 *  Version                         : v1.0.2
 *  Micros supported                : Micro Independent
 *  Compilers supported             : J link
 *  Platforms supported             : Platform Independent
 *  Description                     : This file consists of definitions of fuel Guage
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "Fuel_Guage.h"
#include "Cmp_Tasks.h"
#include "TTMgr.h"
#include "Swc_Speedometer.h"
#include "Cmp_Init.h"
#include "task.h"
/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                     
***********************************************************************************************************************/
#include "fsl_lpadc.h"
#include "fsl_gpio.h"
//include "mpu_wrappers.h"
#include "fuel03.h"
#include "Swc_NVM_Handler.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*  
 * @brief: This macro is used to SET low fuel indication flag
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */#define DEMO_LPADC_USER_CHANNEL 1U

 /*  
 * @brief: This macro is used to SET low fuel indication flag
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
#define DEMO_LPADC_USER_CMDID   1U /* CMD1 */


/*  
 * @brief: This macro is used to SET low fuel indication flag
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
#define DEMO_LPADC_VREF_SOURCE  kLPADC_ReferenceVoltageAlt1
/*  
 * @brief: This macro is used to SET low fuel indication flag
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
#define SET         1U
/*  
 * @brief: This macro is used to reset the low fuel indication flag
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
#define RESET       0U

/*  
 * @brief: This macro is used to SET low fuel indication flag
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
#define FUEL_ADC_HYST    200u

/*  
 * @brief: This macro is used to SET low fuel indication flag
 * @Unit: N/A 
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
#define FLPS_HYST_VALUE     100u
/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to get adc input from fuel sensor
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint16_t g_Fuel_Sense_ADC_IN_u16;
/*
 * @brief: This variable is used to store low fuel indication status
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
FUEL_LFW_TT_ST_EN g_Low_Fuel_TT_Status;

/*
 * @brief: This variable is used to get initial pre condition check status
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint8_t g_PreConditon_Status;
/*
 * @brief: This variable is used to store calculated fuel bar level
 * @Unit:  FUEL_BAR_POS_EN
 * @Resolution: 1bar
 * @Range: 0 bar - 7 bar
 * @Applicability: Fuel Bar Indication
 */
FUEL_BAR_POS_EN g_Calculated_Fuel_Bar_Level;
/*
 * @brief: This variable is used to store current fuel bar level
 * @Unit:  FUEL_BAR_POS_EN
 * @Resolution: 1bar
 * @Range: 0 bar - 7 bar
 * @Applicability: Fuel Bar Indication
 */
FUEL_BAR_POS_EN g_Displayed_Fuel_Bar_Level;

/*
 * @brief: This variable is used to store timer value to push calculated fuel bar value to display 
 * @Unit:  uint8_t
 * @Resolution: 1
 * @Range: 0 to 150
 * @Applicability: Based on HMI Fuel Bar update time,  this value will be configured. 
 */
uint8_t g_Fuel_Display_Update_Timer_u8;
/*
 * @brief: This variable is used to store fuel sender failure staus
 * @Unit: N/A 
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 * @note: when Open circuit or Close circuit occurs, this flag will be set.
 */
uint8_t g_Fuel_Fault_Ind_Status;

/*
 * @brief: This variable is used to get full range from from fuel sensor
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
const uint32_t g_LpadcFullRange   = 4096U;

/*
 * @brief: This variable is used to shift the resultant value from fuel sensor
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
const uint32_t g_LpadcResultShift = 3U;

/*
 * @brief: This variable is used to get the fuel sensor's ADC resultant value 
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint32_t g_FuelSensorADCResult_u32 = 0u;

/*
 * @brief: This variable is used to get adc input from fuel sensor
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint32_t g_Fuel_SBATT_ADCResult_u32 = 0u;

/*
 * @brief: This variable is used to get ready status of the fuel gauge
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint8_t g_Fuel_Gauge_Ready_Status_u8 = 0;

/*
 * @brief: This variable is used to get fuel radiation count 
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: 20,000 rems per hour
 * @Applicability: Fuel Bar Indication
 */
uint16_t g_Fuel_RAD_Count_u16;

/*
 * @brief: This variable is used to take moving average sample from fuel unit
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint16_t g_Mov_Avg_Sample_u16[10] = {0,0,0,0,0,0,0,0,0,0};

/*
 * @brief: This variable is used to get index of the moving average sample
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint8_t g_Mov_Avg_Sample_Idx_u8;

/*
 * @brief: This variable is used to get accumulate fuel radiation count
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint16_t g_Fuel_ACCU_RAD_Count_u16;

/*
 * @brief: This variable is used to get accumulate radiant timer 
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint8_t g_Fuel_ACCU_RAD_Timer_u8;

/*
 * @brief: This variable is used to get average radiant count of the fuel 
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint16_t g_Fuel_Avg_RAD_Count_u16;

/*
 * @brief: This variable is used to get average fuel moving completion status
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
bool g_Mov_Avg_Completion_Status_bl;

/*
 * @brief: This enum is used to get fuel gauge members details
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
FUEL_GUAGE_ADC_STATE_MACHINE g_Adc_Samplig_State_Machine;

/*
 * @brief: This variable is used to get time taking for fuel cycle
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint8_t g_Fuel_Cycle_ms_u8 = 0;

/*
 * @brief: This variable is used to keep the conversion result 
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
lpadc_conv_result_t mLpadcResultConfigStruct;

/*
 * @brief: This table is used to dispaly the fuel range on the fuel display
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
static UINT16 NVM_Fuel_table_U16[8][2];

/*
 * @brief: This variable is used to get current fuel level in the tank
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint32_t g_current_fuel_percent;

/*
 * @brief: This variable is used to get initial fuel display status
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
bool g_initial_fuel_disp_BOOL;

/*
 * @brief: This variable is used to update the fuel display based the current fuel level
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint8_t g_Fuel_Display_Update_Cnt_u8;

/*
 * @brief: This variable is used to store the previous fuel level 
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint32_t g_Prev_fuel_percent;

/*
 * @brief: This variable is used to get ready status of the fuel NVM 
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint8_t g_Fuel_NVM_Ready_Status_u8;

/*
 * @brief: This variable is used to get the fault recovery status 
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
bool g_Is_Open_Or_Short_Detected_bl;

/*
 * @brief: This variable is used to get initial sample staus of the fuel 
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
uint8_t g_Initial_Sample_Status;

/*
 * @brief: This variable defines the debounce flag of the fuel
 * @Unit:  uint16_t
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Fuel Bar Indication
 */
bool g_Fuel_Inst_Debounce_flag;
/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/
/*
* @brief    This API is used to process precondition check  
* @param    NONE
* @return   bool   True: Fuel Guage Preconditon Ok   ,   False: Fuel Guage Preconditon Not ok
* @invocation 
*/
static bool Fuel_Guage_PreCondition_Process(void);

/*
* @brief    This API is used to process Fuel gauge ADC state machine
* @param    NONE
* @return   nil
* @invocation 
*/
static void Fuel_Guage_ADC_State_Machine(void);

/*
* @brief    This API is used to process calculation of the fuel sensor data
* @param    NONE
* @return   nil
* @invocation 
*/
static void Fuel_Guage_Fuel_Sensor_Data_Calculation(void);

/*
* @brief    This API is used to process averae fuel calculation when system in activate  state
* @param    NONE
* @return   nil
* @invocation 
*/
static void Fuel_Moving_Avg_Calculation (void);

/*
* @brief    This API is used to process radiation caluculation of the fuel gauge
* @param    NONE
* @return   nil
* @invocation 
*/
static void Swc_Fuel_Gauge_Calc_RAD_Value(void);

/*
* @brief    This API is used to process initial fuel display  
* @param    NONE
* @return   nil
* @invocation 
*/

static void ffuel_initial_fuel_display(void);
/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/* This API is used to Initialize the fuel guage */
void Fuel_Guage_Init(void)
{
    uint8_t fl_loop_Idx = 0;
    
    g_Fuel_Sense_ADC_IN_u16 = 0;

    /* initialize fuel cycle value */
    g_Fuel_Cycle_ms_u8 = 0;

    /* Initialize adc sampling state to IDLE */
    g_Adc_Samplig_State_Machine = FUEL_GUAGE_IDLE;

    g_Fuel_RAD_Count_u16 = 0;

    g_Fuel_Gauge_Ready_Status_u8 = 1;

    g_initial_fuel_disp_BOOL = FALSE;

    g_Fuel_Display_Update_Cnt_u8 = 0;

    g_Fuel_Fault_Ind_Status = FUEL03_STATUS_NO_OPEN_SHORT;

    g_Low_Fuel_TT_Status = LOW_FUEL_TT_OFF;

    g_Mov_Avg_Completion_Status_bl = FALSE;

    g_Is_Open_Or_Short_Detected_bl = FALSE;

    g_Initial_Sample_Status = FUEL03_SAMPLE_SHORTED;

    /* Flps NVM Read */
    NVM_Byte_Read_Allocation(NVM_FUEL_GUAGE_FLPS_COUNT,(uint8_t*)&g_Prev_fuel_percent);

    NVM_Byte_Read_Allocation(FUEL_GAUGE_BAR_LEVEL,&g_Calculated_Fuel_Bar_Level);

    NVM_Byte_Read_Allocation(NVM_FUEL_GAUGE_BAR_ON_OFF_VAL_CALIBRATION,(uint8_t*)&NVM_Fuel_table_U16[0][0]);

    /* Assign fuel gauge ON/OFF values to global buffer */
    for(fl_loop_Idx = 0; fl_loop_Idx <= FUEL_BAR_POS_7; fl_loop_Idx++)
    {
        /* store Bar ON RAD Count */
        g_Fuel_Guage_Res_Bar_Map_Table[fl_loop_Idx].Bar_ON_Res_Val = NVM_Fuel_table_U16[fl_loop_Idx][0];

        /* store Bar OFF RAD Count */
        g_Fuel_Guage_Res_Bar_Map_Table[fl_loop_Idx].Bar_OFF_Res_Val = NVM_Fuel_table_U16[fl_loop_Idx][1];
    }

    g_Fuel_Inst_Debounce_flag = TRUE;

    g_Fuel_Display_Update_Timer_u8 = 0;

}


/* This API is used to initialize the fuel guage peripherals */
void Fuel_Guage_Activate(void)
{
    /* do nothing */
}

/* This API is used to De activate  the fuel guage  peripherals */
void Fuel_Guage_Deactivate(void)
{
    /* do nothing */
}

/* This API is used to Get instant debounce flag status  */
bool Swc_Get_Inst_Debounce_Flag_Status(void)
{
    return (g_Fuel_Inst_Debounce_flag);
}

/* This API is used to clear the instant debounce flag status  */
void Swc_Clear_Inst_Debounce_Flag_Status(void)
{
    g_Fuel_Inst_Debounce_flag = FALSE;
}

/* This API is used to get fuel gauge ready status */
bool Fuel_Gauge_Ready_Status(void)
{
    bool fl_Fuel_Ready_Status_bl = FALSE;
 
    if((g_Fuel_NVM_Ready_Status_u8 == kStatus_Success) && 
       (g_initial_fuel_disp_BOOL == TRUE))
    {
        fl_Fuel_Ready_Status_bl = TRUE;
    }

    return (fl_Fuel_Ready_Status_bl);
}

/*  This API is used to De Initialize the fuel guage */
void Fuel_Guage_DeInit(void)
{
    g_Fuel_Sense_ADC_IN_u16 = 0;

    /* initialize fuel cycle value */
    g_Fuel_Cycle_ms_u8 = 0;

    /* Initialize adc sampling state to IDLE */
    g_Adc_Samplig_State_Machine = FUEL_GUAGE_IDLE;
}

/*
* @brief    This API is used to process mainfunction of  fuel guage 
* @param    NONE
* @return   NONE
* @invocation 
*/
void Fuel_Guage_MainFunction(void)
{
    bool fl_Pre_Cond_St = FALSE;
    uint8_t fl_loop_Idx = 1; 
    bool fl_fuel03_Init_Finished_bl = FALSE;   \
    uint8_t fl_Fuel_Open_Short_Status;
    bool fl_Fast_Fill_Status = FALSE;

    /* pre condition processing */
    g_PreConditon_Status = Fuel_Guage_PreCondition_Process();

    /* Get fuel03 package init finished status */
    fl_fuel03_Init_Finished_bl = fuel03_init_finished();

    if( g_PreConditon_Status == TRUE)
    {

        /* Initial Fuel display check */
        /* Check for Ign off to ON happened */
        if(g_initial_fuel_disp_BOOL == FALSE)
        {

            /* This funciton shall call upon Ign ON and after proveout only */
            ffuel_initial_fuel_display();

            if(fl_fuel03_Init_Finished_bl == TRUE)
            {
                fl_Fuel_Open_Short_Status = fuel03_open_short_status();

                if(fl_Fuel_Open_Short_Status == FUEL03_STATUS_OPEN)
                {
                    /* Do short circuit indication to display */ 
                    g_Fuel_Fault_Ind_Status = FUEL03_STATUS_OPEN;

                    g_Low_Fuel_TT_Status = LOW_FUEL_TT_OFF;

                    /* Upon recovery from abnormal state to normal , fuel bar value has to be initialized*/
                    g_Calculated_Fuel_Bar_Level = FUEL_BAR_POS_0;

                    g_Is_Open_Or_Short_Detected_bl = TRUE;

                }
                else if(fl_Fuel_Open_Short_Status == FUEL03_STATUS_SHORT)
                {
                    /* Do short circuit indication to display */ 
                    g_Fuel_Fault_Ind_Status = FUEL03_STATUS_SHORT;

                    g_Low_Fuel_TT_Status = LOW_FUEL_TT_OFF;

                    /* Upon recovery from abnormal state to normal , fuel bar value has to be initialized*/
                    g_Calculated_Fuel_Bar_Level = FUEL_BAR_POS_0;

                    g_Is_Open_Or_Short_Detected_bl = TRUE;

                }
                else
                {

                g_current_fuel_percent = fuel03_get_senderA_PF();

                ffuel_calculate_bars();

                }

                /* initial fuel bar update without 15sec timer*/
                g_Displayed_Fuel_Bar_Level = g_Calculated_Fuel_Bar_Level;

                /* Reserve fuel indication by LOW FUEL WARNING TT ON */
                if(g_Displayed_Fuel_Bar_Level == FUEL_BAR_POS_0)
                {
                    g_Low_Fuel_TT_Status = LOW_FUEL_TT_ON;
                }
                else
                {
                    g_Low_Fuel_TT_Status = LOW_FUEL_TT_OFF;
                }

                /* Initial prove out & display fuel completed */
                g_initial_fuel_disp_BOOL = TRUE;

                g_Fuel_Display_Update_Cnt_u8 = 0;

                g_Fuel_Inst_Debounce_flag = FALSE;
            }
        }
        else
        {
            /* Initial fuel display is not completed */
        }

        if(g_initial_fuel_disp_BOOL == TRUE)
        {

            /* Call fuel03 periodic task */
            fuel03_periodic_processing(g_Fuel_Avg_RAD_Count_u16,FALSE);

            /* Get open circuit status */
            fl_Fuel_Open_Short_Status = fuel03_open_short_status();

            g_current_fuel_percent = fuel03_get_senderA_PF();

            if(fl_Fuel_Open_Short_Status == FUEL03_STATUS_OPEN)
            {
                /* Do short circuit indication to display */ 
                g_Fuel_Fault_Ind_Status = FUEL03_STATUS_OPEN;

                g_Low_Fuel_TT_Status = LOW_FUEL_TT_OFF;

                /* Upon recovery from abnormal state to normal , fuel bar value has to be initialized*/
                g_Calculated_Fuel_Bar_Level = FUEL_BAR_POS_0;

                g_Is_Open_Or_Short_Detected_bl = TRUE;

            }
            else if(fl_Fuel_Open_Short_Status == FUEL03_STATUS_SHORT)
            {
                /* Do short circuit indication to display */ 
                g_Fuel_Fault_Ind_Status = FUEL03_STATUS_SHORT;

                g_Low_Fuel_TT_Status = LOW_FUEL_TT_OFF;

                /* Upon recovery from abnormal state to normal , fuel bar value has to be initialized*/
                g_Calculated_Fuel_Bar_Level = FUEL_BAR_POS_0;

                g_Is_Open_Or_Short_Detected_bl = TRUE;

            }
            else
            {
                g_Fuel_Fault_Ind_Status = FUEL03_STATUS_NO_OPEN_SHORT;

                /* Calculate fuel bar level */
                ffuel_calculate_bars();

                /* Recovery from abnormal state(open/shrot) to short,  fuel bar has to dispaly directly without step wise*/
                if(g_Is_Open_Or_Short_Detected_bl == TRUE)
                {
                    /* Clear flag */
                    g_Is_Open_Or_Short_Detected_bl = FALSE;

                    /* Push calculated fuel bar to display*/
                    g_Displayed_Fuel_Bar_Level = g_Calculated_Fuel_Bar_Level;
                }
                /* there is change in fuel bar, slew update ,then push it to display*/
                else if(g_Displayed_Fuel_Bar_Level != g_Calculated_Fuel_Bar_Level) 
                {
                    /* increment timer value for 15sec*/
                    g_Fuel_Display_Update_Timer_u8 = g_Fuel_Display_Update_Timer_u8 + 1;

                    if(g_Fuel_Display_Update_Timer_u8 == 145)
                    {
                        /* Filling direction*/
                        if(g_Displayed_Fuel_Bar_Level < g_Calculated_Fuel_Bar_Level)
                        {
                            
                            /* Increment fuel bar level by one for every 15sec*/
                            g_Displayed_Fuel_Bar_Level = g_Displayed_Fuel_Bar_Level + 1;

                        }
                        /* Draining direction*/
                        else
                        {
                            /* Decrement fuel bar level by one for every 15sec*/
                            g_Displayed_Fuel_Bar_Level = g_Displayed_Fuel_Bar_Level - 1;

                        }

                        /* clear timer */
                        g_Fuel_Display_Update_Timer_u8 = 0;
                    }

                }

                /* Reserve fuel indication by LOW FUEL WARNING TT ON */
                if(g_Displayed_Fuel_Bar_Level == FUEL_BAR_POS_0)
                {
                    g_Low_Fuel_TT_Status = LOW_FUEL_TT_ON;
                }
                else
                {
                    g_Low_Fuel_TT_Status = LOW_FUEL_TT_OFF;
                }

            }
        
        }    

    }
    else
    {
        /* Clear preconditon flag */
        g_PreConditon_Status = FALSE;
    }

    if((g_Fuel_Fault_Ind_Status != FUEL03_STATUS_NO_OPEN_SHORT) || 
        (g_Low_Fuel_TT_Status == LOW_FUEL_TT_ON))
    {
        TT_Mgr_Command(Fuel_Bar,TT_FLASH);

    }    
    else
    {

        TT_Mgr_Command(Fuel_Bar,TT_NO_ACTION);
    }

}

/* This API is used to process initial fuel display   */
static void ffuel_initial_fuel_display(void)
{

    Swc_Fuel_Gauge_Calc_RAD_Value();

    fuel03_periodic_processing(g_Fuel_RAD_Count_u16,FALSE);
}

/* API is used to Get low fuel level indication status  */
void ffuel_calculate_bars(void)
{
    uint8_t fl_loop_Idx = 0;
    uint8_t fl_Current_Fuel_Bar_u8;

    fl_Current_Fuel_Bar_u8 = (uint8_t)g_Calculated_Fuel_Bar_Level;

    if((g_Fuel_Guage_Res_Bar_Map_Table[g_Calculated_Fuel_Bar_Level].Bar_ON_Res_Val) < g_current_fuel_percent)
    {

        /* Filling portion */

        for(fl_loop_Idx = 8; fl_loop_Idx > (fl_Current_Fuel_Bar_u8); fl_loop_Idx--)
        {
            if((g_Fuel_Guage_Res_Bar_Map_Table[fl_loop_Idx - 1].Bar_ON_Res_Val + FUEL_ADC_HYST) <= g_current_fuel_percent )
            {
                /* Get fuel bar level for corresponding resistance value*/
                g_Calculated_Fuel_Bar_Level = g_Fuel_Guage_Res_Bar_Map_Table[fl_loop_Idx - 1].Fuel_Bar_Level;

                /* store current FLPS vlaue */
                g_Prev_fuel_percent = g_current_fuel_percent;

                break;
            } 
            else
            {

            }
        }    
    }
    else if((g_Fuel_Guage_Res_Bar_Map_Table[g_Calculated_Fuel_Bar_Level].Bar_OFF_Res_Val) > g_current_fuel_percent)
    {
        /* Draining portion */

        for(fl_loop_Idx = (g_Calculated_Fuel_Bar_Level + 1); fl_loop_Idx > 0; fl_loop_Idx--)
        {

            /* check each index to get draining fuel bar level */
            if(( g_Fuel_Guage_Res_Bar_Map_Table[fl_loop_Idx - 1].Bar_OFF_Res_Val + FUEL_ADC_HYST) <= g_current_fuel_percent )
            {
                /* Get fuel bar level for corresponding resistance value*/
                g_Calculated_Fuel_Bar_Level = g_Fuel_Guage_Res_Bar_Map_Table[fl_loop_Idx - 1].Fuel_Bar_Level;

                /* store current FLPS vlaue */
                g_Prev_fuel_percent = g_current_fuel_percent;

                break;
            } 
            else
            {
                /* Current FLPS is lower than bar 0 OFF FLPS, so above condition will not go through*/
                g_Calculated_Fuel_Bar_Level = FUEL_BAR_POS_0 ;
            }      

        }   

    }
    else
    {
        /* do nothing */
    }
   
}

/*
* @brief    This API is used to process precondition check  
* @param    NONE
* @return   bool   True: Fuel Guage Preconditon Ok   ,   False: Fuel Guage Preconditon Not ok
* @invocation 
*/
static bool Fuel_Guage_PreCondition_Process(void)
{
    uint8_t fl_LVSD_ST = 0;
    uint8_t fl_HVSD_ST = 0;
    uint8_t fl_IGN_St = 1;
   
    /* check LVSD Status */
    fl_LVSD_ST = FUEL_GUAGE_LVSD_STATUS();

    /* check HVSD Status */
    fl_HVSD_ST = FUEL_GUAGE_HVSD_STATUS();

    /* check ignition status */
    fl_IGN_St = FUEL_GUAGE_GET_IGN_STATUS();

    if(( fl_LVSD_ST != 0) && ( fl_HVSD_ST != 0) && ( fl_IGN_St == IGN_ON))
    {
        g_PreConditon_Status = TRUE;
    }
    else
    {
        g_PreConditon_Status = FALSE;
    }

    return g_PreConditon_Status;
}

/* periodicity task for fuel syatem for every time period */
void fsl_lpadc_Periodic_Task(void *pvparameters)
{
    if( g_Adc_Samplig_State_Machine == FUEL_GUAGE_IDLE)
    {
        /* enable fuel supply circuit to read adc value */
        g_Adc_Samplig_State_Machine = FUEL_GUAGE_FUEL_SUPPLY_ON;

    }
    
    /* initialize SBATT ADC configuration */
    SBATT_ADC_Config_Init();

    /* Initialize fuel sensor adc configuration */
    Fuel_Sensor_ADC_Config_Init();

 	TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(10);
 	BaseType_t xWasDelayed;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();


	while (1)
	    {
	    	xWasDelayed = xTaskDelayUntil( &xLastWakeTime, xFrequency );
            Fuel_Guage_ADC_State_Machine();
           
	    }
}

/* This API is used to configure the fuel sensor's  ADC configuration  */
void Fuel_Sensor_ADC_Config_Init(void)
{
    
	lpadc_config_t mLpadcConfigStruct;
	lpadc_conv_trigger_config_t mLpadcTriggerConfigStruct;
	lpadc_conv_command_config_t mLpadcCommandConfigStruct;

	//PRINTF("LPADC Polling Example\r\n");

	LPADC_GetDefaultConvCommandConfig(&mLpadcCommandConfigStruct);

	mLpadcCommandConfigStruct.channelNumber = DEMO_LPADC_USER_CHANNEL;

	LPADC_SetConvCommandConfig(DEMO_LPADC_BASE, DEMO_LPADC_USER_CMDID, &mLpadcCommandConfigStruct);
	LPADC_GetDefaultConvTriggerConfig(&mLpadcTriggerConfigStruct);

	mLpadcTriggerConfigStruct.targetCommandId       = DEMO_LPADC_USER_CMDID;

	mLpadcTriggerConfigStruct.enableHardwareTrigger = false;
	LPADC_SetConvTriggerConfig(DEMO_LPADC_BASE, 0U, &mLpadcTriggerConfigStruct);
}

/* This API is used to configure the battery's ADC configuration  */
void SBATT_ADC_Config_Init(void)
{
	lpadc_config_t mLpadcConfigStruct;
	lpadc_conv_trigger_config_t mLpadcTriggerConfigStruct;
	lpadc_conv_command_config_t mLpadcCommandConfigStruct;

	LPADC_GetDefaultConvCommandConfig(&mLpadcCommandConfigStruct);

	mLpadcCommandConfigStruct.channelNumber = 2;

	LPADC_SetConvCommandConfig(DEMO_LPADC_BASE, 3, &mLpadcCommandConfigStruct);
	LPADC_GetDefaultConvTriggerConfig(&mLpadcTriggerConfigStruct);

	mLpadcTriggerConfigStruct.targetCommandId       = 3;

	mLpadcTriggerConfigStruct.enableHardwareTrigger = false;
	LPADC_SetConvTriggerConfig(DEMO_LPADC_BASE, 2u, &mLpadcTriggerConfigStruct);

}

/* This API is used to ready the battery's ADC value */
void Fuel_SBATT_Read_Adc_Value(void)
{
    LPADC_DoSoftwareTrigger(DEMO_LPADC_BASE, 1U<<2);

    while (!LPADC_GetConvResult(DEMO_LPADC_BASE, &mLpadcResultConfigStruct));

    g_Fuel_SBATT_ADCResult_u32 = ((mLpadcResultConfigStruct.convValue) >> g_LpadcResultShift);

    g_Fuel_SBATT_ADCResult_u32 /= 4;

}

/* This API is used to process Fuel gauge ADC state machine */
static void Fuel_Guage_ADC_State_Machine(void)
{
    switch (g_Adc_Samplig_State_Machine)
    {
    case FUEL_GUAGE_IDLE:
        /* code */
        break;

    case FUEL_GUAGE_FUEL_SUPPLY_ON:
        /* activate the fuel supply for fuel sensor */
        GPIO_PinWrite(BOARD_INITPINS_FUEL_SBATT_CTRL_MCUOUT_PERIPHERAL, BOARD_INITPINS_FUEL_SBATT_CTRL_MCUOUT_CHANNEL, 1U);

        /* change state to adc sampling*/
        g_Adc_Samplig_State_Machine = FUEL_GUAGE_ADC_SAMPLING;

        /* fuel cycle increment */
        g_Fuel_Cycle_ms_u8 = g_Fuel_Cycle_ms_u8 + 1;

        break;
    
    case FUEL_GUAGE_ADC_SAMPLING:
        /* read adc value from fuel sensor and sampling it for 1sec */
        Fuel_Guage_Fuel_Sensor_Data_Calculation();

        /* read fuel SBATT adc value */
        Fuel_SBATT_Read_Adc_Value();

        /* calculate RAD Count */
        Fuel_Moving_Avg_Calculation();

        /* change state to fuel supply OFF*/
        //g_Adc_Samplig_State_Machine = FUEL_GUAGE_FUEL_SUPPLY_OFF;

        /* fuel cycle increment */
        g_Fuel_Cycle_ms_u8 = g_Fuel_Cycle_ms_u8 + 1;

        break;
    
    case FUEL_GUAGE_FUEL_SUPPLY_OFF:
        
        /* De-activate the fuel supply for fuel sensor */
        // GPIO_PinWrite(BOARD_INITPINS_FUEL_SBATT_CTRL_MCUOUT_PERIPHERAL, BOARD_INITPINS_FUEL_SBATT_CTRL_MCUOUT_CHANNEL, 1U);

        /* fuel cycle increment */
        g_Fuel_Cycle_ms_u8 = g_Fuel_Cycle_ms_u8 + 1;

        /* change state to fuel supply OFF*/
        g_Adc_Samplig_State_Machine = FUEL_GUAGE_FUEL_SENSOR_COOL_OFF;

        break;
    
    case FUEL_GUAGE_FUEL_SENSOR_COOL_OFF:

        /* fuel cycle increment */
        g_Fuel_Cycle_ms_u8 = g_Fuel_Cycle_ms_u8 + 1;

        if(g_Fuel_Cycle_ms_u8 == 10)
        {
            /* change state to adc sampling*/
            g_Adc_Samplig_State_Machine = FUEL_GUAGE_FUEL_SUPPLY_ON;

            g_Fuel_Cycle_ms_u8 = 0;

        }
        break;

    default:
        break;
    }   
}

/* API is used to process calculation of the fuel sensor data */
static void Fuel_Guage_Fuel_Sensor_Data_Calculation(void)
{
    LPADC_DoSoftwareTrigger(DEMO_LPADC_BASE, 1U); /* 1U is trigger0 mask. */

    while (!LPADC_GetConvResult(DEMO_LPADC_BASE, &mLpadcResultConfigStruct));

    g_FuelSensorADCResult_u32 = ((mLpadcResultConfigStruct.convValue) >> g_LpadcResultShift);

    /* 12bit value to 10bit value */
    g_FuelSensorADCResult_u32 =g_FuelSensorADCResult_u32 / 4;

}

/* API is used to process radiation caluculation of the fuel gauge */
static void Swc_Fuel_Gauge_Calc_RAD_Value(void)
{
    uint16_t fl_RAD_Count_u16 = 0;
    
    /* To avoid divide by zero exception */
    if((g_FuelSensorADCResult_u32 !=0) && (g_Fuel_SBATT_ADCResult_u32 != 0))
    {

        fl_RAD_Count_u16 = ((512 * g_FuelSensorADCResult_u32) / g_Fuel_SBATT_ADCResult_u32);

        if(fl_RAD_Count_u16 > 900)
        {
            /* To avoid overflow */
            g_Fuel_RAD_Count_u16 = 0;
        }
        else
        {
            /* fuel adc and SBATT adc ratioed */ 
            g_Fuel_RAD_Count_u16 = 900 - fl_RAD_Count_u16;

        }

    }

}
 
/* API is used to process averae fuel calculation when system in activate  state */
static void Fuel_Moving_Avg_Calculation (void)
{
    uint32_t fl_Ratioed_Val_u32 = 0;

    /* 10 samples taken , do average */
    if(g_Mov_Avg_Sample_Idx_u8 == FUEL_BAR_UPDATE_COUNTER)
    {
        g_Fuel_RAD_Count_u16 = (g_Mov_Avg_Sample_u16[0] +
                                g_Mov_Avg_Sample_u16[1] +
                                g_Mov_Avg_Sample_u16[2] +
                                g_Mov_Avg_Sample_u16[3] +
                                g_Mov_Avg_Sample_u16[4] +
                                g_Mov_Avg_Sample_u16[5] +
                                g_Mov_Avg_Sample_u16[6] +
                                g_Mov_Avg_Sample_u16[7] +
                                g_Mov_Avg_Sample_u16[8] +
                                g_Mov_Avg_Sample_u16[9] ) / FUEL_BAR_UPDATE_COUNTER;

        g_Mov_Avg_Sample_Idx_u8 = 0;

        /* accumulated RAD count for 15 sec */
        g_Fuel_ACCU_RAD_Count_u16 = g_Fuel_ACCU_RAD_Count_u16 + g_Fuel_RAD_Count_u16;

        g_Fuel_ACCU_RAD_Timer_u8 ++;

        if(g_Fuel_ACCU_RAD_Timer_u8 == FUEL_BAR_UPDATE_COUNTER)
        {
            g_Fuel_Avg_RAD_Count_u16 = (g_Fuel_ACCU_RAD_Count_u16) / (FUEL_BAR_UPDATE_COUNTER);

            /* Set moving average completion flag */
            g_Mov_Avg_Completion_Status_bl = TRUE;

            
            g_Fuel_ACCU_RAD_Timer_u8 = 0;

            g_Fuel_ACCU_RAD_Count_u16 = 0;
        }
    }
    else
    {
        /* To avoid divide by zero exception */
    	if((g_FuelSensorADCResult_u32 !=0) && (g_Fuel_SBATT_ADCResult_u32 != 0))
    	{

            fl_Ratioed_Val_u32 = ((512 * g_FuelSensorADCResult_u32) / g_Fuel_SBATT_ADCResult_u32);

            if(fl_Ratioed_Val_u32 > 900)
            {
                g_Mov_Avg_Sample_u16[g_Mov_Avg_Sample_Idx_u8] = 0;
            }
            else
            {
                /* fuel adc and SBATT adc ratioed */ 
                g_Mov_Avg_Sample_u16[g_Mov_Avg_Sample_Idx_u8] = 900 - fl_Ratioed_Val_u32;

            }

        g_Mov_Avg_Sample_Idx_u8 ++;
        }        
        

    }

}

/* API is used to Get low fuel level indication status  */
uint16_t Swc_Fuel_Gauge_Get_RAD_Value(void)
{
    return (g_Fuel_RAD_Count_u16);
}
/*
* @brief    This API is used to Get low fuel level indication status 
* @param    NONE
* @return   FUEL_LFW_TT_ST_EN
* @invocation 
*/
FUEL_LFW_TT_ST_EN Fuel_Guage_Get_Low_Fuel_Status(void)
{
    /* return low fuel indication status */
    return (g_Low_Fuel_TT_Status);
}

/*
* @brief    This API is used to get current fuel guage bar level 
* @param    NONE
* @return   FUEL_BAR_POS_EN enumeration for different fuel bar level
* @invocation 
*/
uint8_t Fuel_Guage_Get_Current_Bar_Level(void)
{
    /* return current bar level */
    return (g_Displayed_Fuel_Bar_Level);
}

/* @brief    This function is used to compute Fuel guage from table
* @param    uint8_t , uint8_t , uint8_t
* @return   uint8_t
*/
uint16_t Fuel_Guage_Table(uint8_t Fuelbar)
{
   uint16_t fl_fuel_litre_u16 = 0;

	fl_fuel_litre_u16 = g_Fuel_Guage_Res_Bar_Map_Table[Fuelbar].Fuel_Capacity_Val;


   return fl_fuel_litre_u16;
}

/* API is used to Get low fuel level indication status  */
uint8_t Swc_Fuel_Gauge_Get_Fault_Status(void)
{
    return (g_Fuel_Fault_Ind_Status);

}

/* This API is used to Get low fuel level indication status  */
uint32_t swc_get_pf_value(void)
{
    return (g_current_fuel_percent);
}

/* This API is used to Get low fuel level indication status  */
void Fuel_Gauge_NVM_Write (void)
{
      bool fl_NVM_Status_bl = TRUE;

   /* Get NVM Status */
   fl_NVM_Status_bl = Swc_Get_NVM_Status();

   if(fl_NVM_Status_bl == FALSE)
   {

    if(g_current_fuel_percent != 0)
    {

     NVM_Byte_Write_Allocation(NVM_FUEL_GUAGE_FLPS_COUNT,(uint8_t*)&g_current_fuel_percent);

      NVM_Byte_Write_Allocation(FUEL_GAUGE_BAR_LEVEL,&g_Calculated_Fuel_Bar_Level);
    }
   }
}

/* This API is used to Get low fuel level indication status  */
bool Swc_Fuel_Guage_Fast_Fill_Condition(void)
{
    bool fl_Fast_Fill_Cond_St = FALSE;
    uint16_t fl_Vehicle_Speed_u16 = 0;

    if(g_initial_fuel_disp_BOOL == TRUE) 
    {

        fl_Vehicle_Speed_u16 = Swc_Get_RAW_Speedo_Val();

        if((fl_Vehicle_Speed_u16 == 0) || (g_Is_Open_Or_Short_Detected_bl == TRUE))
        {

            fl_Fast_Fill_Cond_St = TRUE;
        }
        else 
        {

            fl_Fast_Fill_Cond_St = FALSE;
        }

    }
    else
    {
        fl_Fast_Fill_Cond_St = FALSE;

    }

    return (fl_Fast_Fill_Cond_St);
}
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : v1.0.2                          
    REVISION DATE        : 11/15/2022        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)    
    DESCRIPTION          : Fuel bar Display update logic updated to achieve bar update timing           
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : v1.0.1                          
    REVISION DATE        : 09/11/2022        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)    
    DESCRIPTION          : Upon recovery from abnormal state to normal , fuel bar value has to be initialized added.          
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : v1.0.0                          
    REVISION DATE        : 03/27/2022        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)    
    DESCRIPTION          : Initial version           
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! FUEL_GUAGE_C */
