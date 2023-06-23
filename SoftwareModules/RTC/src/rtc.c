
/* @file FILE NAME */
#ifndef RTC_C
#define RTC_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : B.Rubina Josphine (rubinajosphine@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : rtc.c
 *  Version                         : v1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : J link
 *  Platforms supported             : Platform Independent
 *  Description                     : This file consists of definitions of rtc
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "hal_stdtypes.h"
#include "rtc.h"
#include "rtc_Cfg.h"
#include "HMI_Setting_Screen.h"


/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                     
***********************************************************************************************************************/
#include "fsl_snvs_lp.h"


/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*  
 * @brief: This macro is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
/*
* @brief: This macro is used to set the default year range on the starting state
* @Unit:  uint16_t
* @Resolution: 1year
* @Range: 2022 - 2050
* @Applicability: NIL
* @Note: 
*/
#define DEFAULT_YEAR_RANGE_START    (2022U)

/*
* @brief: This macro is used to set the default Month on battery cycle
* @Unit:  uint8_t
* @Resolution: 1 month
* @Range: 1 - 12
* @Applicability: NIL
* @Note: 
*/
#define DEFAULT_MONTH_RANGE_START    (1U)
/*
* @brief: This macro is used to set the default Day on battery cycle
* @Unit:  uint8_t
* @Resolution: 1 day
* @Range: 1 - 31
* @Applicability: NIL
* @Note:  
*/
#define DEFAULT_DAY_RANGE_START    (1U)
/*
* @brief: This macro is used to set the default Hour on battery cycle
* @Unit:  uint8_t
* @Resolution: 1 month
* @Range: 0 - 23
* @Applicability: NIL
* @Note:  As RTC is having clock in 24hr format,  if default value has to be stored in 12hr format,  
*         convert it into 24hr format and configure this macro
*/
#define DEFAULT_HOUR_RANGE_START    (1u)
/*
* @brief: This macro is used to set the default minute on battery cycle
* @Unit:  uint8_t
* @Resolution: 1 minute
* @Range: 0 - 59
* @Applicability: NIL
* @Note:  NIL
*/
#define DEFAULT_MIN_RANGE_START    (0u)
/*
* @brief: This macro is used to set the default seconds on battery cycle
* @Unit:  uint8_t
* @Resolution: 1 sec
* @Range: 0 - 59
* @Applicability: NIL
* @Note: NIL
*/
#define DEFAULT_SEC_RANGE_START    (0u)
/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
   @brief: This variable is used to give the base address for SNVS periperals
   @parm:   
   @return:
*/
#define g_RTC_SNVS_Base_Addr ((SNVS_Type*) 0x40C90000)

/*
   @brief: This variable is used to give the display the date and time
   @parm:  
   @return:
*/
RTC_TIME_STAMP_ST l_to_display_datetime;

/*
   @brief: This variable is used to give the base address for SNVS periperal
   @parm:
   @return:
*/
RTC_TIME_STAMP_ST l_datetime ={0};

/*
   @brief: This variable is used to give the base address for SNVS periperal
   @parm:
   @return:
*/
snvs_lp_srtc_config_t l_rtc_config;
/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    This function is used to get the date and time
 * @param    SNVS peripheral base address
 * @param    datetime Pointer to the structure where the date and time details are stored.
 * @return   
 */
void RTC_Get_Date_Time(SNVS_Type *base_add, snvs_lp_srtc_datetime_t  *datetime);

void RTC_SET_Time(void);

/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
* @brief    This API is used to Initialize the RTC
* @param    NONE
* @return   NONE
* @invocation 
*/

/* API is used to initiate the RTC init variables with default values */
void Rtc_Init(void)
{
    /* This function is to ungates the SNVS clock and configures the peripheral for basic operation*/
    SNVS_LP_Init(g_RTC_SNVS_Base_Addr);
    l_rtc_config.srtcCalEnable = 1;
    l_rtc_config.srtcCalValue = 1;

    SNVS_LP_SRTC_Init(g_RTC_SNVS_Base_Addr,&l_rtc_config );

   SNVS_LP_SRTC_StartTimer(g_RTC_SNVS_Base_Addr);
}

/* API is used to reset the RTC init variables with default values  */
void Rtc_DeInit(void)
{
    SNVS_LP_Deinit(g_RTC_SNVS_Base_Addr);
    SNVS_LP_SRTC_Deinit(g_RTC_SNVS_Base_Addr);

}

/*
* @brief    This API is used to perform cold init of RTC
* @param    NONE
* @return   NONE
* @invocation 
*/   
void RTC_Cold_Init(void)
{
    /* Set Default clock value as 01:00AM 12HR FORMAT, Date as 01/01/2022*/
    l_datetime.hour = DEFAULT_HOUR_RANGE_START;
    l_datetime.minute = DEFAULT_MIN_RANGE_START;
    l_datetime.second = DEFAULT_SEC_RANGE_START;
    l_datetime.year = DEFAULT_YEAR_RANGE_START;
    l_datetime.month = DEFAULT_MONTH_RANGE_START;
    l_datetime.day = DEFAULT_MONTH_RANGE_START;
    
    /* UPDATE DEFAULT VALUE IN RTC PERIPHERAL*/
    RTC_Set_Date_time(g_RTC_SNVS_Base_Addr, &l_datetime);
}

extern uint8_t NVM_Setting_Write_request;
/* API is used to activate the RTC init variables with default values  */
void Rtc_Activate(void)
{
    /* do nothing */
}

/* API is used to reset the RTC init variables with default values  */
void Rtc_DeActivate(void)
{
     /* do nothing */
}

/* This API is used to execute the RTC  */
void Rtc_MainFunction(void)
{
   /*This function is used to get the date and time from the driver*/
    RTC_Get_Date_Time(g_RTC_SNVS_Base_Addr,(snvs_lp_srtc_datetime_t*) &l_datetime);
    if(NVM_Setting_Write_request == 1)
    {
        NVM_Setting_Write_request = 0;

        HMI_CLK_NVM_check();
    }

}

RTC_TIME_STAMP_ST RTC_Time_Display(void)
{

   return (l_to_display_datetime);
}

 /*This function is used to get the date and time from the driver*/
void RTC_Get_Date_Time(SNVS_Type *base_add, snvs_lp_srtc_datetime_t  *datetime)
{

    SNVS_LP_SRTC_GetDatetime(base_add,datetime);
    
    l_to_display_datetime.day = datetime->day;
    l_to_display_datetime.month = datetime->month;
    l_to_display_datetime.year = datetime->year;
    l_to_display_datetime.hour = datetime->hour;
    l_to_display_datetime.minute = datetime->minute;   
    l_to_display_datetime.second = datetime->second;   
    
}

status_t RTC_Set_Date_time(SNVS_Type *base_add, RTC_TIME_STAMP_ST *datetime)
{
    SNVS_LP_SRTC_SetDatetime(base_add,(snvs_lp_srtc_datetime_t *)datetime);
}

void RTC_SET_Time(void)
{
    l_to_display_datetime.hour = 7;
    l_to_display_datetime.minute = 15;

}



/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : v1.0.0                         
    REVISION DATE        : 04-06-2022       
    CREATED / REVISED BY : Rubina Josphine B (rubinajosphine@niyatainfotech.com)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! RTC_C */
