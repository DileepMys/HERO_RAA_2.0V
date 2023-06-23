/* @file FILE NAME */
#ifndef SWC_TFT_ILLUM_C
#define SWC_TFT_ILLUM_C

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
 *  File name                       : Swc_TFT_Illum.c
 *  Version                         : v1.0.1
 *  Micros supported                : Micro Independent
 *  Compilers supported             : Jlink
 *  Platforms supported             : Platform independent
 *  Description                     : This file consists of definitions of TFT illumination process
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "Swc_TFT_Illum.h"
#include "lvgl_app.h"
#include "HMI_Main_Screen.h"
/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                     
***********************************************************************************************************************/
#include "hal_stdtypes.h"
#include "fsl_pwm.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to store illuminance value
 * @Unit:  uint16_t
 * @Resolution: 
 * @Range: 0 to 65535
 * @Applicability: 
 */
uint16_t g_illuminance_value_u16;

/*
 * @brief: This variable is used to store current ambient mode 
 * @Unit:  uint8_t
 * @Resolution: 
 * @Range: DAY MODE / NIGHT MODE
 * @Applicability: NA
 */
uint8_t g_Current_Ambient_Mode;

/*
 * @brief: This variable is used to store user selected brighness level in setting screen
 * @Unit:  uint8_t
 * @Resolution: 
 * @Range: AUTO / LOW / MEDIUM / HIGH
 * @Applicability: NA
 */
uint8_t g_User_Sel_Brightness_u8;
/*
 * @brief: This variable is used to store illuminance level for illuminance read from sensor
 * @Unit:  uint8_t
 * @Resolution: NIL
 * @Range: 0 to 7
 * @Applicability: NA
 */
uint8_t g_Illuminance_Level_u8;
/*
 * @brief: This variable is used to store target PWM Duty cycle value
 * @Unit:  uint8_t
 * @Resolution: NA
 * @Range: 0 to 100%
 * @Applicability: NA
 */
uint8_t g_Target_PWM_Duty_u8;
/*
 * @brief: This variable is used to store PWM Duty cycle which is to be feed to TFT 
 * @Unit:  uint8_t
 * @Resolution: NA
 * @Range: 0 to 100%
 * @Applicability: NA
 */
uint8_t g_Illum_PWM_Duty_Out_u8;
/*
 * @brief: This variable is used to check status of change in dutycycle, then only push it to PWM Driver
 * @Unit:  bool
 * @Resolution: NA
 * @Range: TRUE OR FALSE
 * @Applicability: NA
 */
bool g_Is_Change_In_PWM_Duty_bl;
/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    This function processes the precondition for TFT Illumination process
 * @param    NONE
 * @return   bool  TRUE - Preconditon Ok,  FALSE - Precondition Nok
 */
static bool SWC_TFT_Illum_PreCondition_Process(void);

/*
 * @brief    This function processes duty cycle computation against illuminance level
 * @param    NONE
 * @return   NONE
 */
static void SWC_TFT_DutyCycle_Computation(void);

/*
 * @brief    This function processes pwm slew rate to achieve target PWM 
 * @param    NONE
 * @return   NONE
 */
static void Swc_Clamp_Illum_PWM_Out(void);

/*
 * @brief    This function processes Target pwm to be generated by calling PWM Driver
 * @param    NONE
 * @return   NONE
 */
static void Swc_TFT_PWM_Update(void);
/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
* @brief    This API is used to initialize tft illumination process
* @param    NONE
* @return   NONE
* @invocation invoked by Os
*/
void SWC_TFT_Illum_Init(void)
{
    g_illuminance_value_u16 = 0;

    g_Illuminance_Level_u8 = 0;

    /* Set default duty cycle */
    g_Target_PWM_Duty_u8 = TFT_DEFAULT_PWM_DUTY_CYCLE;

    /* Set default duty cycle */
    g_Illum_PWM_Duty_Out_u8 = TFT_DEFAULT_PWM_DUTY_CYCLE;

    /* Set flag to drive default pwm dutycycle*/
    g_Is_Change_In_PWM_Duty_bl = TRUE;
}

/*
* @brief    This API is used to de initialize tft illumination process
* @param    NONE
* @return   NONE
* @invocation invoked by Os
*/
void SWC_TFT_Illum_DeInit(void)
{
    g_illuminance_value_u16 = 0;

    g_Illuminance_Level_u8 = 0;

    /* Set default duty cycle */
    g_Target_PWM_Duty_u8 = TFT_DEFAULT_PWM_DUTY_CYCLE;
    
    /* Set default duty cycle */
    g_Illum_PWM_Duty_Out_u8 = TFT_DEFAULT_PWM_DUTY_CYCLE;

    /* Set flag to drive default pwm dutycycle*/
    g_Is_Change_In_PWM_Duty_bl = TRUE;
}

/*
* @brief    This API is used to do TFT illumination process
* @param    NONE
* @return   NONE
* @invocation invoked by Os
*/
void SWC_TFT_Illum_Mainfunction(void)
{
    /* Local variable */
    bool fl_Preconditon_Status_bl = FALSE;
    uint8_t fl_Current_Active_screen;
    uint8_t fl_Loop_Idx;
    bool fl_Sys_Status = FALSE;

    /* Check pre condition */
    fl_Preconditon_Status_bl = SWC_TFT_Illum_PreCondition_Process();

    /* Procondition status check*/
    if(fl_Preconditon_Status_bl == TRUE)
    { 
        /* Until Welcome animation completion, Screen brightness should be default */
        if( HMI_Get_Welcome_Animation_Status() != WELCOME_ANIMATION_COMPLETED)
        {
            /* Assign default value */
            g_Target_PWM_Duty_u8 = TFT_DEFAULT_PWM_DUTY_CYCLE;
        }
        else
        { 
            /* Get Lux value from ambient light sensor */
            g_illuminance_value_u16 = TFT_ILLUM_GET_ALS_LUX_VALUE;

            /* Get user selected brightness level */
            g_User_Sel_Brightness_u8 = TFT_ILLUM_GET_USER_BRIGHTNESS_SEL;

            if(g_illuminance_value_u16 != TFT_ILLUM_INVALID_VALUE)
            {
                /* Get Current Ambient mode from ambient light sensor */
                g_Current_Ambient_Mode = TFT_ILLUM_GET_CURRENT_AMBIENT_MODE;

                if(g_Current_Ambient_Mode == AMBIENT_DAY_MODE)
                {
                    /* From 0th row to 3th row in g_TFT_Illum_vs_Manual_level_pwm_cfg_St are possible 
                        opotions for Day mode */
                    for(fl_Loop_Idx = 0; fl_Loop_Idx < 4; fl_Loop_Idx++)
                    {
                        if(g_illuminance_value_u16 >= g_TFT_Illum_vs_Manual_level_pwm_cfg_St[fl_Loop_Idx].Lux_value)
                        {
                            /* Store Illuminance level */
                            g_Illuminance_Level_u8 = fl_Loop_Idx;

                            /* Calculate duty cycle for respective illuminance level */
                            SWC_TFT_DutyCycle_Computation();  

                            break;                      
                        }
                    }      
                }
                else if(g_Current_Ambient_Mode == AMBIENT_NIGHT_MODE)
                {
                    /* From 4th row to 7th row in g_TFT_Illum_vs_Manual_level_pwm_cfg_St are possible 
                        opotions for Night mode */
                    for(fl_Loop_Idx = 7; fl_Loop_Idx >= 4; fl_Loop_Idx--)
                    {
        
                        if(g_illuminance_value_u16 <= g_TFT_Illum_vs_Manual_level_pwm_cfg_St[fl_Loop_Idx].Lux_value)
                        {
                            /* Store Illuminance level */
                            g_Illuminance_Level_u8 = fl_Loop_Idx;

                            /* Calculate duty cycle for respective illuminance level */
                            SWC_TFT_DutyCycle_Computation();       

                            break;                 
                        }
                    }
                }
                else
                {
                    /* Do nothing */
                }
            }
            else
            {
                /* Set darkest night as illuminance level */
                g_Illuminance_Level_u8 = NUMBER_OF_LEVELS - 1;

                /* Get PWM Duty cycle */
                SWC_TFT_DutyCycle_Computation();
            }
        }

        /* Determine illum PWM Out to be given to TFT */
        Swc_Clamp_Illum_PWM_Out();

        /* Update requested Duty cycle when we receive new data And To avoid continuous call of driver API */
        if(g_Is_Change_In_PWM_Duty_bl == TRUE)
        {
            /* Clear the flag as service processed*/
            g_Is_Change_In_PWM_Duty_bl = FALSE;

            /* PWM Drivel call to feed pwm to TFT */
            Swc_TFT_PWM_Update();
        }
    }
    else
    {
        /* do nothing */
    }
       
}

/*
 * @brief    This function processes duty cycle computation against illuminance level
 * @param    NONE
 * @return   NONE
 */
void SWC_TFT_DutyCycle_Computation(void)
{
    /* Auto brightness control selected by used */
    if(g_User_Sel_Brightness_u8 == AUTO_BRIGHTNESS)
    {
        /* Get PWM Duty from auto duty array */
        g_Target_PWM_Duty_u8 = AUTO_LEVEL_PWM_DUTY[g_Illuminance_Level_u8];
    }
    /* if we are here, then manual level is selected */
    else
    {
        if(g_User_Sel_Brightness_u8 == LOW_BRIGHTNESS)
        {
            g_Target_PWM_Duty_u8 = g_TFT_Illum_vs_Manual_level_pwm_cfg_St[g_Illuminance_Level_u8].Low_Duty_Cycle;
        }
        else if(g_User_Sel_Brightness_u8 == HIGH_BRIGHTNESS)
        {
            g_Target_PWM_Duty_u8 = g_TFT_Illum_vs_Manual_level_pwm_cfg_St[g_Illuminance_Level_u8].High_Duty_Cycle;

        }
        else
        {
            /* Medium brightness level is chosen */
            g_Target_PWM_Duty_u8 = g_TFT_Illum_vs_Manual_level_pwm_cfg_St[g_Illuminance_Level_u8].Medium_Duty_Cycle;
        }
    }
}

/*
 * @brief    This function processes pwm slew rate to achieve target PWM 
 * @param    NONE
 * @return   NONE
 */
void Swc_Clamp_Illum_PWM_Out(void)
{
    /* check both target and actual duty are same */
    if(g_Target_PWM_Duty_u8 != g_Illum_PWM_Duty_Out_u8)
    {
        if(g_Target_PWM_Duty_u8 > g_Illum_PWM_Duty_Out_u8)
        {
            /* Increase TFT pwm out by slew rate to achieve target pwm */ 
            g_Illum_PWM_Duty_Out_u8 = g_Illum_PWM_Duty_Out_u8 + ILLUM_SLEW_RATE;
        }
        else
        {
            /* decrease TFT pwm out by slew rate to achieve target pwm */ 
            g_Illum_PWM_Duty_Out_u8 = g_Illum_PWM_Duty_Out_u8 - ILLUM_SLEW_RATE;
        }

        /* SET FLAG*/
        g_Is_Change_In_PWM_Duty_bl = TRUE;
    }  
    else
    {
        g_Illum_PWM_Duty_Out_u8 = g_Target_PWM_Duty_u8;
    }  
}

/*
 * @brief    This function processes the precondition for TFT Illumination process
 * @param    NONE
 * @return   bool  TRUE - Preconditon Ok,  FALSE - Precondition Nok
 */
bool SWC_TFT_Illum_PreCondition_Process(void)
{
    /* local variable */
    uint8_t fl_IGN_St_u8 = 0;
    uint8_t fl_LVSD_St_u8 = 0;
    uint8_t fl_HVSD_St_u8 = 0;
    bool fl_Precondition_St_bl = FALSE;

    /* Get IGN STATUS */
    fl_IGN_St_u8 = TFT_ILLUM_GET_IGN_STATUS;

    /* Get Low voltage status */
    fl_LVSD_St_u8 = TFT_ILLUM_GET_LVSD_STATUS;

    /* Get High voltage status */
    fl_HVSD_St_u8 = TFT_ILLUM_GET_HVSD_STATUS;

    if((fl_IGN_St_u8 == IGN_ON) && (fl_LVSD_St_u8 == 1) && (fl_HVSD_St_u8 == 1))
    {
        fl_Precondition_St_bl = TRUE;
    }
    else
    {
        fl_Precondition_St_bl = FALSE;
    }

    return (fl_Precondition_St_bl);
}

/*
 * @brief    This function processes Target pwm to be generated by calling PWM Driver
 * @param    NONE
 * @return   NONE
 */
static void Swc_TFT_PWM_Update(void)
{
    /* update current duty cycle value in PWM Driver */
	PWM_UpdatePwmDutycycle(PWM1,kPWM_Module_0,kPWM_PwmA,kPWM_SignedCenterAligned,g_Illum_PWM_Duty_Out_u8);

    /* Load PWM Register */
	PWM_SetPwmLdok(PWM1, (kPWM_Control_Module_0), true);
}
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                          
    REVISION DATE        : 07/18/2022        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)      
    DESCRIPTION          : Initial version 

    REVISION NUMBER      : V1.0.1                          
    REVISION DATE        : 12/21/2022        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)      
    DESCRIPTION          : PWM Update shall happen only when change in duty cycle requested. 
                           Until Welcome animation completion, Screen brightness should be default            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! SWC_TFT_ILLUM_C */
